#include "_mappers.hpp"

#include <cstdint>
#include <iostream>

#include "header.hpp"

namespace Mapper {
    NROM::NROM() {
        this->CHR_ROM = new uint8_t[0x2000];
        
        switch (header.prg_rom) {
            case 1:
                this->type = NROM::NROM128;
                this->PRG_ROM = new uint8_t[0x4000];
                break;
            case 2:
                this->type = NROM::NROM256;
                this->PRG_ROM = new uint8_t[0x8000];
                break;
            default:
                std::cout << "ERROR: Mapper of type NROM has illegal PRG ROM size." << std::endl;
        }

        if (header.header_type != 2) {
            switch (header.nes1.prg_ram) {
                case 0: break;
                case 1:
                    this->type = FB_4K;
                    this->PRG_RAM = new uint8_t[0x1000];
                default:
                    std::cout << "ERROR: Mapper of type NROM has illegal PRG RAM size." << std::endl;
            }
        } else {
            switch (header.nes2.prg_ram_sft) {
                case 0: break;
                case 5:
                    this->type = FB_2K;
                    this->PRG_RAM = new uint8_t[0x500];
                case 6:
                    this->type = FB_4K;
                    this->PRG_RAM = new uint8_t[0x1000];
                default:
                    std::cout << "ERROR: Mapper of type NROM has illegal PRG RAM size." << std::endl;
            }
        }
    }

    uint8_t NROM::read(uint16_t addr, bool &bus) {
        bus = true;
        switch (addr) {
            case 0x0000 ... 0x401F:
                return 0; // should not happen
            case 0x4020 ... 0x5FFF:
                return 0; // should happen
            case 0x6000 ... 0x7FFF:
                std::cout << "ERROR: Unimplemented Mapper type." << std::endl;
                return 0;
            case 0x8000 ... 0xFFFF:
                bus = false;
                switch (this->type) {
                    case NROM::NROM128:
                        return this->PRG_ROM[addr % 0x4000];
                    case NROM::NROM256:
                        return this->PRG_ROM[addr % 0x8000];
                    default:
                        std::cout << "ERROR: Unimplemented Mapper type." << std::endl;
                        bus = true;
                        return 0;
                }
        }

        return 0;
    }

    void NROM::write(uint16_t addr, uint8_t value) {
        switch (addr) {
            case 0x0000 ... 0x5FFF:
            case 0x8000 ... 0xFFFF:
                break;

            case 0x6000 ... 0x7FFF:
                switch (this->type) {
                    case NROM::FB_2K:
                        this->PRG_RAM[addr % 0x800] = value;
                        break;
                    case NROM::FB_4K:
                        this->PRG_RAM[addr % 0x1000] = value;
                        break;
                    default: break;
                }
        }
    }
}