#pragma once

#include <cstdint>

namespace PPU {
    union ppu_flags {
        struct {
            uint8_t nmi : 1;
            uint8_t slave : 1;
            uint8_t spr_h : 1;
            uint8_t bg_tile : 1;
            uint8_t spr_tile : 1;
            uint8_t inc_mode : 1;
            
            uint8_t clr : 3;
            uint8_t spr : 1;
            uint8_t bg : 1;
            uint8_t spr_left : 1;
            uint8_t bg_left : 1;
            uint8_t grey : 1;
            
            uint8_t vblank : 1;
            uint8_t spr0 : 1;
            uint8_t spr_over : 1;
        };
        uint16_t all;
    };

    union vram_addr_t { // yyy NN YYYYY XXXXX
        struct {
            uint8_t coarse_x : 5;
            uint8_t coarse_y : 5;
            uint8_t nametable : 2;
            uint8_t fine_y : 3;
        };
        uint16_t reg;
    };

    class PPU {
    private:
        vram_addr_t v;
        vram_addr_t t;

        uint8_t x : 3;
        uint8_t w : 1;

        uint8_t frame : 1;

        uint8_t vram[0x1000];
        uint8_t palettes[0x20];
        uint8_t OAM[0x100];
        
        ppu_flags flags;

        uint8_t oamaddr;
        uint8_t read_buf;
        uint8_t vram_addr;

        bool rendering;
        uint16_t dot;
        uint16_t scanline;

        uint8_t _get(uint16_t addr);
        void _set(uint16_t addr, uint8_t val);
        
    protected:
        uint8_t rw : 1;
        uint8_t addr : 3;
        uint8_t bus;

    public:
        PPU();
        void tick();
        uint8_t read(uint8_t addr);
        void write(uint8_t addr, uint8_t value);
    };
}