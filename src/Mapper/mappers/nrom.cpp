#include "mappers.hpp"

#include <cstdint>
#include <iostream>

#include "header.hpp"

namespace Mapper {
    NROM::NROM(std::ifstream& rom) {
        std::cout << "Mapper Type: ";

        switch (header.prg_rom) {
            case 1:
                this->type = NROM::NROM128;
                this->PRG_ROM = new uint8_t[0x4000];
                rom.read((char *)this->PRG_ROM, 0x4000);
                break;
            case 2:
                this->type = NROM::NROM256;
                this->PRG_ROM = new uint8_t[0x8000];
                rom.read((char *)this->PRG_ROM, 0x8000);
                break;
            default:
                std::cout << "ERROR: Mapper of type NROM has illegal PRG ROM size: " << header.prg_rom << std::endl;
        }
        
        this->CHR_ROM = new uint8_t[0x2000];
        rom.read((char *)this->CHR_ROM, 0x2000);

        if (header.header_type != 2) {
            switch (header.nes1.prg_ram) {
                case 0: break;
                case 1:
                    this->type = FB_4K;
                    this->PRG_RAM = new uint8_t[0x1000];
                    break;
                default:
                    std::cout << "ERROR: Mapper of type NROM has illegal PRG RAM size: " << header.nes2.prg_ram_sft << std::endl;
            }
        } else {
            switch (header.nes2.prg_ram_sft) {
                case 0: break;
                case 5:
                    this->type = FB_2K;
                    this->PRG_RAM = new uint8_t[0x800];
                    break;
                case 6:
                    this->type = FB_4K;
                    this->PRG_RAM = new uint8_t[0x1000];
                    break;
                default:
                    std::cout << "ERROR: Mapper of type NROM has illegal PRG RAM size: " << header.nes1.prg_ram << std::endl;
            }
        }

        this->mirroring = (header.nametbl_mirror & 0b01) == 1;

        switch (this->type) {
            case NROM128: std::cout << "NROM128" << std::endl; break;
            case NROM256: std::cout << "NROM256" << std::endl; break;
            case FB_2K:   std::cout << "NROM Family Basic - 2K PRG-RAM" << std::endl; break;
            case FB_4K:   std::cout << "NROM Family Basic - 4K PRG-RAM" << std::endl; break;
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
                switch (this->type) {
                    case NROM::NROM128:
                    case NROM::NROM256:
                    default:
                        return 0;
                    case NROM::FB_2K:
                        bus = false;
                        return this->PRG_RAM[addr % 0x800];
                    case NROM::FB_4K:
                        bus = false;
                        return this->PRG_RAM[addr % 0x1000];
                }
            case 0x8000 ... 0xFFFF:
                bus = false;
                switch (this->type) {
                    case NROM::NROM128:
                        return this->PRG_ROM[addr % 0x4000];
                    case NROM::NROM256:
                        return this->PRG_ROM[addr % 0x8000];
                    default:
                        std::cout << "ERROR: Unimplemented Mapper type: Family Basic NROM" << std::endl;
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

    uint8_t NROM::readPPU(uint16_t addr, uint16_t &return_addr) {
        switch (addr) {
            case 0x0000 ... 0x1FFF:
                return this->CHR_ROM[addr];
            case 0x2000 ... 0x2FFF:
                if (this->mirroring == 0) {
                    return_addr = addr % 0x800;
                } else {
                    return_addr = (addr % 0x400) + ((addr < 0x2800) ? 0 : 0x400);
                }
        }

        return 0;
    }

    void NROM::writePPU(uint16_t addr, uint8_t value, uint16_t &return_addr) {
        switch (addr) {
            case 0x0000 ... 0x1FFF:
                break;
            case 0x2000 ... 0x2FFF:
                if (this->mirroring == 0) {
                    return_addr = addr % 0x800;
                } else {
                    return_addr = (addr % 0x400) + ((addr < 0x2800) ? 0 : 0x400);
                }
        }
    }
}