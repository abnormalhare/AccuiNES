#pragma once

#include <cstdint>

// not the true structure of the header, but the meaning of it
struct Header1 {
    uint8_t prg_ram;
    uint8_t tv_system : 2;
    uint8_t has_prm_ram : 1;
    uint8_t bus_conflicts : 1;
};

struct Header2 {
    uint8_t submapper : 4;
    uint8_t prg_ram_sft : 4;
    uint8_t prg_nvram_sft : 4;
    uint8_t chr_ram_sft : 4;
    uint8_t chr_nvram_sft : 4;
    uint8_t timing : 2;
    uint8_t ppu_type : 4;
    uint8_t hardware_type : 4;
    uint8_t ext_cons_type : 4;
    uint8_t rom_cnt : 2;
    uint8_t exp_device : 6;
};

struct Header {
    uint16_t prg_rom : 12;
    uint16_t chr_rom : 12;

    uint8_t nametbl_mirror : 2;
    uint8_t battery : 1;
    uint8_t trainer : 1;
    uint16_t mapperNum : 12;
    uint8_t console_type : 2;
    uint8_t header_type : 2;

    Header1 nes1;
    Header2 nes2;
};

extern Header header;