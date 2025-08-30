#include "./cpu.hpp"

#include "./opcode.hpp"
#include "Mapper/mapper.hpp"
#include "header.hpp"

#include "main.hpp"
#include <SDL_pixels.h>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>

Header header;

namespace CPU {

CPU::CPU() : debugFile("debug/debug.txt") {

    this->reset();

    this->A = this->X = this->Y = 0;
    this->S = 0xFD;
    this->PC = this->PCS = 0xC000;
    this->P.c = this->P.z = this->P.d = this->P.b = this->P.v = this->P.n = 0;
    this->P.i = 1; this->P.o = 1;

    this->step = 0;

    this->running = true;
    this->debug_step = false;
}

CPU::~CPU() {
    this->debugFile.close();
}

void renderSDLText(char *text, SDL_Color& color, int x, int y) {
    SDL_Surface *text_surf = TTF_RenderText_Solid(font, text, color);
    SDL_Texture *text_tex = SDL_CreateTextureFromSurface(renderer, text_surf);
    SDL_Rect dest = {
        .x = x + 5,
        .y = y + 5,
        .w = text_surf->w,
        .h = text_surf->h,
    };
    SDL_RenderCopy(renderer, text_tex, nullptr, &dest);
    SDL_DestroyTexture(text_tex);
    SDL_FreeSurface(text_surf);
}

void renderSDLTextF(SDL_Color& color, int x, int y, const char *text, ...) {
    va_list list;
    va_start(list, text);

    char *new_text = (char *)malloc(256 * sizeof(char));
    vsnprintf(new_text, 256, text, list);

    renderSDLText(new_text, color, x, y);
    free(new_text);

    va_end(list);
}

void CPU::debugPrint() {
    SDL_Color black = {0,0,0};

    renderSDLTextF(black, 0, 0, "INST: %s", this->getInstrName());

    renderSDLTextF(black,  0, 20, "PC: %04X", this->PC.get());
    renderSDLTextF(black, 75, 20, "PCS: %04X", this->PCS.get());
    renderSDLTextF(black,  0, 35, "IR: %02X", this->IR);
    renderSDLTextF(black,  0, 50, "STEP: %d", this->step);
    renderSDLTextF(black,  0, 65, "AB: %04X", this->AB.get());
    renderSDLTextF(black,  0, 80, "DL: %02X", this->DL);

    renderSDLTextF(black,  0,100, "A: %02X", this->A);
    renderSDLTextF(black, 40,100, "X: %02X", this->X);
    renderSDLTextF(black, 80,100, "Y: %02X", this->Y);
    renderSDLTextF(black,120,100, "P: %d%d%d%d%d%d%d%d",
        this->P.n, this->P.v, this->P.o, this->P.b, this->P.d, this->P.i, this->P.z, this->P.c
    );

    renderSDLTextF(black,  0,120, "AI: %02X", this->AI);
    renderSDLTextF(black, 45,120, "BI: %02X", this->BI);
    renderSDLTextF(black, 90,120, "ADD: %02X", this->ADD);

    renderSDLTextF(black,200,  0, "ZERO PAGE");
    renderSDLTextF(black,200, 20, "%02X%02X%02X%02X%02X%02X%02X%02X", 
        this->RAM[0x00], this->RAM[0x01], this->RAM[0x02], this->RAM[0x03], this->RAM[0x04], this->RAM[0x05], this->RAM[0x06], this->RAM[0x07]
    );
    renderSDLTextF(black,200, 35, "%02X%02X%02X%02X%02X%02X%02X%02X", 
        this->RAM[0x08], this->RAM[0x09], this->RAM[0x0A], this->RAM[0x0B], this->RAM[0x0C], this->RAM[0x0D], this->RAM[0x0E], this->RAM[0x0F]
    );
    renderSDLTextF(black,200, 50, "%02X%02X%02X%02X%02X%02X%02X%02X", 
        this->RAM[0x10], this->RAM[0x11], this->RAM[0x12], this->RAM[0x13], this->RAM[0x14], this->RAM[0x15], this->RAM[0x16], this->RAM[0x17]
    );
    renderSDLTextF(black,200, 65, "%02X%02X%02X%02X%02X%02X%02X%02X", 
        this->RAM[0x18], this->RAM[0x19], this->RAM[0x1A], this->RAM[0x1B], this->RAM[0x1C], this->RAM[0x1D], this->RAM[0x1E], this->RAM[0x1F]
    );

    renderSDLTextF(black,200,200,  "STACK: %02X%02X%02X%02X%02X%02X%02X%02X",
        this->RAM[0x1F8], this->RAM[0x1F9], this->RAM[0x1FA], this->RAM[0x1FB], this->RAM[0x1FC], this->RAM[0x1FD], this->RAM[0x1FE], this->RAM[0x1FF]
    );
}

inline uint8_t CPU::read(uint16_t index) {
    switch (index) {
        case 0x0000 ... 0x1FFF:
            return this->RAM[this->AB % 0x800];
            break;
        case 0x2000 ... 0x3FFF: // TODO
            return this->DL;
        case 0x4000 ... 0x401F: // TODO
            return this->DL;
        case 0x4020 ... 0xFFFF:
            bool bus = false;
            uint8_t val = Mapper::read(index, bus);
            if (!bus) return val;
            else return this->DL;
    }

    return this->DL;
}

inline uint8_t CPU::readAB() {
    return this->read(this->AB.get());
}

void CPU::read() {
    this->DL = this->readAB();
}

void CPU::write() {
    switch (this->AB.get()) {
        case 0x0000 ... 0x1FFF:
            this->RAM[this->AB % 0x800] = this->DOR;
            break;
        case 0x2000 ... 0x3FFF: // TODO
            break;
        case 0x4000 ... 0x401F: // TODO
            break;
        case 0x4020 ... 0xFFFF:
            Mapper::write(this->AB.get(), this->DOR);
            break;
    }
}

void CPU::readS() {
    this->AB.set(this->S, nes_u16::LO);
    this->AB.set(1, nes_u16::HI);
    this->read();
}

void CPU::writeS() {
    this->AB.set(this->S, nes_u16::LO);
    this->AB.set(1, nes_u16::HI);
    this->write();
}

void CPU::getInstr() {
    this->AB = this->PC;
    this->IR = this->readAB();
    this->PCS = this->PC;
    this->PC = this->PCS + 1;
    this->currPC++;
}

const char *instr_names[256] = {

#include "_instr_name.hpp"

};

const char *CPU::getInstrName() {
    return instr_names[this->IR];
}

void CPU::getData() {
    this->AB = this->PC;
    this->DL = this->readAB();
    this->PC++;
    this->currPC++;
}

void CPU::readData() {
    this->AB = this->PC;
    this->DL = this->readAB();
}

void CPU::setDOR(uint8_t value) {
    this->DOR = value;
}

uint8_t CPU::getDL() {
    return this->DL;
}

void CPU::DORtoDL() {
    this->DL = this->DOR;
}

void CPU::ALUtoABL() {
    this->AB.set(this->ADD, nes_u16::LO);
}

// returns carry out
bool CPU::callALU(callALU_outtype type, callALU_flags flags) {
    uint16_t val = 0;
    uint8_t carry =
        (flags & R) ?  this->P.c :
        (flags & I) ? 1          :
        0;

    switch (type) {
        case callALU_outtype::SUM:
            val = (uint16_t)this->AI + (uint16_t)this->BI + (uint16_t)carry;
            if (flags & C) this->P.c = (val > 0xFF);
            if (flags & Z) this->P.z = ((val & 0xFF) == 0);
            if (flags & V) this->P.v = (((val ^ this->AI) & (val ^ this->BI) & 0x80) == 0x80);
            if (flags & N) this->P.n = ((val & 0x80) == 0x80);
            this->ADD = val;
            return (val > 0xFF);
        case callALU_outtype::AND:
            this->ADD = this->AI & this->BI;
            if (flags & Z) this->P.z = (this->ADD == 0);
            if (flags & N) this->P.n = ((this->ADD & 0x80) == 0x80);
            break;
        case callALU_outtype::EOR:
            this->ADD = this->AI ^ this->BI;
            if (flags & Z) this->P.z = (this->ADD == 0);
            if (flags & N) this->P.n = ((this->ADD & 0x80) == 0x80);
            break;
        case callALU_outtype::OR:
            this->ADD = this->AI | this->BI;
            if (flags & Z) this->P.z = (this->ADD == 0);
            if (flags & N) this->P.n = ((this->ADD & 0x80) == 0x80);
            break;
        case callALU_outtype::SR:
            this->ADD = this->AI >> 1;
            if (flags & R) this->ADD += this->P.c * 0b10000000;
            if (flags & C) this->P.c = ((this->AI & 1) == 1);
            if (flags & Z) this->P.z = (this->ADD == 0);
            if (flags & N) this->P.n = ((this->ADD & 0x80) == 0x80);
            return ((this->AI & 1) == 1);
    }

    return false;
}

void CPU::setAB(CPU::Step step, bool clear_ai) {
    switch (step) {
        case Step::LO:
            this->BI = this->DL;
            if (clear_ai) this->AI = 0;
            break;
        case Step::HI:
            this->callALU(SUM, NONE);
            this->AB.set(this->ADD, nes_u16::LO);
            this->AB.set(this->DL,  nes_u16::HI);
            break;

        // should only be used when hi AB is set elsewhere, e.g. clearABHi
        case Step::SETLO:
            this->BI = this->DL;
            if (clear_ai) this->AI = 0;
            this->callALU(SUM, NONE);
            this->AB.set(this->ADD, nes_u16::LO);
            break;
    }
}

uint8_t CPU::getPC(nes_u16::Step step) {
    switch (step) {
        case nes_u16::LO:
            return this->PC.get() & 0x00FF;
        case nes_u16::HI:
            return (this->PC.get() & 0xFF00) >> 8;
    }

    return 0;
}

void CPU::setPC() {
    this->PC = this->PCS;
}

void CPU::incPC(nes_u16::Step step) {
    this->PC.set(this->getPC(step) + 1, step);
}

void CPU::incPC() {
    this->PC++;
}

void CPU::tick() {
    this->debugPrint();

    // if (!this->debug_step && this->IR == 0xA1) return;
    this->debug_step = false;

    switch (this->step) {
        case 0:
            this->currPC = this->prevPC = this->PC.get();
            this->getInstr();
            break;

        default:
            Opcode::decode_rom[this->IR](this);
            if (this->step == 0) {
                this->debugWrite();
                this->tick();
                return;
            }
    }
    
    this->step++;
}

void CPU::debugWrite() {
    this->debugFile << std::hex << std::uppercase << std::setw(4) << std::setfill('0') 
                    << static_cast<int>(this->prevPC) << "  ";

    bool compare_check = false;
    for (int i = 0; i < 3; i++) {
        uint16_t pc = this->prevPC + i;

        if (pc >= this->currPC) {
            this->debugFile << "   ";
        } else {
            this->debugFile << std::hex << std::uppercase << std::setw(2) << std::setfill('0') 
                            << static_cast<int>(this->read(pc)) << " ";
        }
    }

    // this->debugFile << std::setw(7) << std::setfill(' ') << this->getInstrName() << "  ";

    this->debugFile << "A:" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') 
                    << static_cast<int>(this->A) << " ";
    this->debugFile << "X:" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') 
                    << static_cast<int>(this->X) << " ";
    this->debugFile << "Y:" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') 
                    << static_cast<int>(this->Y) << " ";
    this->debugFile << "P:" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') 
                    << static_cast<int>(this->P.reg) << " ";
    this->debugFile << "SP:" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') 
                    << static_cast<int>(this->S);
    
    this->debugFile << std::endl;
}

void CPU::reset() {
    this->PC = 0xFFFC;
    this->S -= 3;
    this->P.i = 1;
}

} // namespace CPU