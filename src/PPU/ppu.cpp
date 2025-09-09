#include "ppu.hpp"
#include <cstdlib>

#include "Mapper/mapper.hpp"
#include "main.hpp"

namespace PPU {
    int pixels[32 * 8][30 * 8];

    PPU::PPU() {
        this->flags.all = 0;
        this->flags.vblank   = (rand() % 3) ? 1 : 0;
        this->flags.spr_over = (rand() % 3) ? 1 : 0;
        this->oamaddr = 0;
        this->frame = 0;
        this->w = 0;
        this->read_buf = 0;
        this->v.reg = 0;
        this->t.reg = 0;

        this->addr = 0;
        this->rw = 0;
        this->bus = 0;

        this->rendering = false;
    }

    uint8_t PPU::_get(uint16_t addr) {
        uint16_t return_addr;
        uint8_t ret = Mapper::readPPU(addr, return_addr);
        if (return_addr != 0) {
            return this->vram[return_addr];
        }

        return ret;
    }

    void PPU::_set(uint16_t addr, uint8_t val) {
        uint16_t return_addr;
        Mapper::writePPU(addr, val, return_addr);
        if (return_addr != 0) {
            this->vram[return_addr] = val;
        }
    }

    void PPU::tick() {
        SDL_Texture *display = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 128, 128);
        for (int row = 0; row < 30; row++) {
            for (int column = 0; column < 32; column++) {
                for (int y = 0; y < 8; y++) {
                    uint16_t ret_addr;
                    char lo = this->_get((row * 256) + (column * 16) + y);
                    char hi = this->_get((row * 256) + (column * 16) + y + 8);

                    for (int x = 0; x < 8; x++) {
                        int colorNum = ((lo >> (7 - x)) & 1) + 2 * ((hi >> (7 - x)) & 1);
                        int color = (0xFF << 24) + ((colorNum * 85) << 16) + ((colorNum * 85) << 8) + ((colorNum * 85) << 0);
                        pixels[(row * 8) + y][(column * 8) + x] = color;
                    }
                }
            }
        }

        SDL_UpdateTexture(display, NULL, pixels, 128 * sizeof(unsigned int));
        SDL_RenderCopy(renderer, display, NULL, NULL);
    }

    uint8_t PPU::read(uint8_t addr) {
        this->rw = 0;
        this->addr = addr;
        this->tick();

        switch (addr) {
            case 2: {
                this->w = 0;

                uint8_t temp = 
                    (this->flags.vblank   == 1) * 0b10000000 +
                    (this->flags.spr0     == 1) * 0b01000000 +
                    (this->flags.spr_over == 1) * 0b00100000;
                
                this->bus = (temp & 0xE0) | (this->bus & ~0xE0);
                break;
            } case 4:
                this->bus = this->OAM[this->oamaddr]; // this isnt always true
                break;
            case 7:
                this->bus = this->read_buf;
                break;
        }

        return this->bus;
    }

    void PPU::write(uint8_t addr, uint8_t value) {
        this->rw = 1;
        this->addr = addr;
        this->tick();

        this->bus = value;

        switch (addr) {
            case 0:
                this->t.nametable    = (value & 0b00000011) >> 0;
                this->flags.inc_mode = (value & 0b00000100) >> 2;
                this->flags.spr_tile = (value & 0b00001000) >> 3;
                this->flags.bg_tile  = (value & 0b00010000) >> 4;
                this->flags.spr_h    = (value & 0b00100000) >> 5;
                this->flags.slave    = (value & 0b01000000) >> 6;
                this->flags.nmi      = (value & 0b10000000) >> 7;
                break;
            case 1:
                this->flags.grey     = (value & 0b00000001) >> 0;
                this->flags.bg_left  = (value & 0b00000010) >> 1;
                this->flags.spr_left = (value & 0b00000100) >> 2;
                this->flags.bg       = (value & 0b00001000) >> 3;
                this->flags.spr      = (value & 0b00010000) >> 4;
                this->flags.clr      = (value & 0b11100000) >> 5;
                break;
            case 3:
                this->oamaddr = value;
                break;
            case 4:
                this->OAM[this->oamaddr++] = value; // this isnt always true
                break;
            case 5:
                if (this->w == 0) {
                    this->x          = (value & 0b00000111) >> 0;
                    this->t.coarse_x = (value & 0b11111000) >> 3;
                    this->w = 1;
                } else {
                    this->t.fine_y   = (value & 0b00000111) >> 0;
                    this->t.coarse_y = (value & 0b11111000) >> 3;
                    this->w = 0;
                }
                break;
            case 6:
                if (this->w == 0) {
                    this->t.reg = ((value & 0x3F) << 8) | (this->t.reg & 0xFF);
                    this->t.reg &= ~0x40;
                    this->w = 1;
                } else {
                    this->t.reg = (this->t.reg & 0xFF00) + value;
                    this->v.reg = this->t.reg;
                    this->w = 0;
                }
            case 7:
                if (this->v.reg < 0x3F00) {
                    uint16_t return_addr = 0;
                    this->_set(this->v.reg, value);
                } else {
                    if ((this->v.reg & 3) == 0) {
                        this->palettes[this->v.reg & 0x0F] = value;
                    } else {
                        this->palettes[this->v.reg & 0x1F] = value;
                    }
                }
                break;
        }
    }
}