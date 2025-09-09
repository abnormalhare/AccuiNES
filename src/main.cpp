#include "CPU/cpu.hpp"
#include "PPU/ppu.hpp"
#include "header.hpp"
#include "Mapper/mapper.hpp"

#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <ostream>

#include "main.hpp"

SDL_Window *window = nullptr;
SDL_Renderer *renderer = nullptr;
TTF_Font *font = nullptr;

char *filename;

Header header;

const int DISP_WIDTH = 512;
const int DISP_HEIGHT = 512;

bool initialize_sdl() {
    if (SDL_Init(SDL_INIT_AUDIO) != 0) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }
    
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "ERROR: SDL did not initialize: " << SDL_GetError() << std::endl;
        return true;
    }

    if (TTF_Init() < 0) {
        std::cout << "ERROR: SDL TTF did not initialize: " << SDL_GetError() << std::endl;
        return true;
    }

    window = SDL_CreateWindow("AccuiNES", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DISP_WIDTH, DISP_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cout << "ERROR: SDL Window did not initialize: " << SDL_GetError() << std::endl;
        return true;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "ERROR: SDL Renderer did not initialize: " << SDL_GetError() << std::endl;
        return true;
    }

    font = TTF_OpenFont("fonts/CALIBRI.TTF", 16);
    if (!font) {
        std::cout << "ERROR: Calibri font did not initialize: " << SDL_GetError() << std::endl;
        return true;
    }

    return false;
}

bool process_sdl(std::unique_ptr<CPU::CPU>& cpu) {
    static const unsigned char *keys = SDL_GetKeyboardState(nullptr);
    SDL_Event e;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    while (SDL_PollEvent(&e) != 0) {
        switch (e.type) {
            case SDL_QUIT:
                return false;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                    case SDLK_z:        cpu->input_p1 |= 0x01; break;
                    case SDLK_x:        cpu->input_p1 |= 0x02; break;
                    case SDLK_RSHIFT:   cpu->input_p1 |= 0x04; break;
                    case SDLK_RETURN:   cpu->input_p1 |= 0x08; break;
                    case SDLK_UP:       cpu->input_p1 |= 0x10; break;
                    case SDLK_DOWN:     cpu->input_p1 |= 0x20; break;
                    case SDLK_LEFT:     cpu->input_p1 |= 0x40; break;
                    case SDLK_RIGHT:    cpu->input_p1 |= 0x80; break;

                    case SDLK_SPACE:    cpu->debug_step = true; break;
                    case SDLK_ESCAPE:   return false;
                }
                break;
            case SDL_KEYUP:
                switch (e.key.keysym.sym) {
                    case SDLK_z:        cpu->input_p1 &= ~0x01; break;
                    case SDLK_x:        cpu->input_p1 &= ~0x02; break;
                    case SDLK_RSHIFT:   cpu->input_p1 &= ~0x04; break;
                    case SDLK_RETURN:   cpu->input_p1 &= ~0x08; break;
                    case SDLK_UP:       cpu->input_p1 &= ~0x10; break;
                    case SDLK_DOWN:     cpu->input_p1 &= ~0x20; break;
                    case SDLK_LEFT:     cpu->input_p1 &= ~0x40; break;
                    case SDLK_RIGHT:    cpu->input_p1 &= ~0x80; break;
                }
                break;
        }
    }

    return true;
}

void deinit_sdl() {
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = nullptr;
    window = nullptr;
    
    TTF_Quit();
    SDL_Quit();
}

bool initialize_rom() {
    std::ifstream rom(filename, std::ios_base::in | std::ios_base::binary);

    char *uninterp_header = new char[0x10];
    rom.read(uninterp_header, 0x10);

    if (strncmp(uninterp_header, "NES\x1A", 4) != 0) {
        std::cout << "ERROR: File is not an NES file." << std::endl;
        return true;
    }

    header.prg_rom = uninterp_header[4]; // PRG-ROM size LSB
    header.chr_rom = uninterp_header[5]; // CHR-ROM size LSB

    header.nametbl_mirror   = (uninterp_header[6] & 0x01) >> 0;
    header.battery          = (uninterp_header[6] & 0x02) >> 1;
    header.trainer          = (uninterp_header[6] & 0x04) >> 2;
    header.nametbl_mirror  += (uninterp_header[6] & 0x08) >> 2; // >> 3 << 1
    header.mapper_num       = (uninterp_header[6] & 0xF0) >> 4;

    header.console_type     = (uninterp_header[7] & 0x03) >> 0;
    header.header_type      = (uninterp_header[7] & 0x0C) >> 2;

    // deal with the rest later

    delete []uninterp_header;

    Mapper::determineMapper(rom);

    return false;
}

std::unique_ptr<CPU::CPU> cpu;
std::unique_ptr<PPU::PPU> ppu;

void run() {
    cpu = std::make_unique<CPU::CPU>();
    ppu = std::make_unique<PPU::PPU>();

    while (cpu->running && process_sdl(cpu)) {
        cpu->tick(); // simulates a PPU cycle as well
        ppu->tick();
        ppu->tick();
        
        SDL_RenderPresent(renderer);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "AccuiNES: ./AccuiNES.exe <filename>" << std::endl;
        return 0;
    }
    filename = argv[1];
    
    if (initialize_sdl()) {
        return 1;
    }

    std::cout << "SDL initialized" << std::endl;

    if (initialize_rom()) {
        return 2;
    }
    std::cout << "ROM initialized" << std::endl;

    run();

    deinit_sdl();
    return 0;
}