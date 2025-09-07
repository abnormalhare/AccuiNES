#include "header.hpp"
#include "mapper.hpp"

#include "mappers/mappers.hpp"
#include <iostream>

namespace Mapper {
    Mapper *currentMapper;

    uint8_t read(uint16_t addr, bool &bus) {
        return currentMapper->read(addr, bus);
    }

    void write(uint16_t addr, uint8_t value) {
        currentMapper->write(addr, value);
    }

    uint8_t readPPU(uint16_t addr, uint16_t &return_addr) {
        return currentMapper->readPPU(addr, return_addr);
    }

    void writePPU(uint16_t addr, uint8_t value, uint16_t &return_addr) {
        currentMapper->writePPU(addr, value, return_addr);
    }

    void determineMapper(std::ifstream& rom) {
        switch (header.mapper_num) {
            default:
                std::cout << "ERROR: Unimplemented Mapper: " << static_cast<int>(header.mapper_num) << std::endl;
                break;

            case 0: currentMapper = new NROM(rom); break;
        }
    }
}