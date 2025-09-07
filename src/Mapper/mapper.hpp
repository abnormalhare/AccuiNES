#pragma once

#include <cstdint>
#include <fstream>

namespace Mapper {
    void determineMapper(std::ifstream&);
    uint8_t read(uint16_t addr, bool &bus);
    uint8_t readPPU(uint16_t addr, uint16_t &return_addr);
    void write(uint16_t addr, uint8_t value);
    void writePPU(uint16_t addr, uint8_t value, uint16_t &return_addr);
}