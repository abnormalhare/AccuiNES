#include "./cpu.hpp"

#include "./opcode.hpp"
#include "Mapper/mapper.hpp"
#include "header.hpp"
#include <cstdint>

Header header;

namespace CPU {

CPU::CPU() {

    this->reset();

    this->A = this->X = this->Y = 0;
    this->S = 0xFD;
    this->PC = 0xFFFC;
    this->P.c = this->P.z = this->P.d = this->P.b = this->P.v = this->P.n = 0;

    this->step = 0;

    this->running = true;
}

void CPU::simulate() {
    while (this->running) {
        this->tick();
    }
}

uint8_t CPU::readAB() {
    switch (this->AB.get()) {
        case 0x0000 ... 0x1FFF:
            return this->RAM[this->AB % 0x800];
            break;
        case 0x2000 ... 0x3FFF: // TODO
            return this->DL;
        case 0x4000 ... 0x401F: // TODO
            return this->DL;
        case 0x4020 ... 0xFFFF:
            bool bus = false;
            uint8_t val = Mapper::read(this->AB.get(), bus);
            if (!bus) return val;
            else return this->DL;
    }

    return this->DL;
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
    this->PC++;
}

void CPU::getData() {
    this->AB = this->PC;
    this->DL = this->readAB();
    this->PC++;
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

void CPU::callALU(callALU_outtype type, callALU_flags flags) {
    uint16_t val = 0;
    uint8_t carry =
        (flags & R) ?  this->P.c :
        (flags & B) ? ~this->P.c :
        0;

    switch (type) {
        case callALU_outtype::SUM:
            val = (uint16_t)this->AI + (uint16_t)this->BI + carry;
            if (flags & C) this->P.c = (val > 0xFF);
            if (flags & Z) this->P.z = (val == 0);
            if (flags & V) this->P.v = (val ^ this->AI) & (val ^ this->BI) & 0x80;
            if (flags & N) this->P.n = ((val & 0x80) == 0x80);
            this->ADD = val;
            break;
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
            if (flags & V) this->P.n = 0;
            break;
    }
}

void CPU::setAB(CPU::Step step, bool clear_ai) {
    switch (step) {
        case Step::LO:
            this->BI = this->DL;
            if (clear_ai) this->AI = 0;
            break;
        case Step::HI:
            this->P.c = 0;
            this->callALU(SUM, NONE);
            this->AB.set(this->ADD, nes_u16::LO);
            this->AB.set(this->DL,  nes_u16::HI);
            break;

        // should only be used when hi AB is set elsewhere, e.g. clearABHi
        case Step::SETLO:
            this->BI = this->DL;
            if (clear_ai) this->AI = 0;
            this->P.c = 0;
            this->callALU(SUM, NONE);
            this->AB.set(this->ADD, nes_u16::LO);
            break;
    }
}

uint8_t CPU::getPC(nes_u16::Step step) {
    switch (step) {
        case nes_u16::LO:
            return this->PC.get() & 0x0F;
        case nes_u16::HI:
            return (this->PC.get() & 0xF0) >> 8;
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
    switch (this->step) {
        case 0:
            this->getInstr();
            break;

        default:
            Opcode::decode_rom[this->IR](this);
            if (this->step == 0) {
                this->tick();
                return;
            }
    }
    
    this->step++;
}

void CPU::reset() {
    this->PC = 0xFFFC;
    this->S -= 3;
    this->P.i = 1;
}

} // namespace CPU