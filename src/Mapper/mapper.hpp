#pragma once

#include <cstdint>
#include <fstream>

namespace Mapper {
    void determineMapper(std::ifstream&);
    uint8_t read(uint16_t addr, bool &bus);
    void write(uint16_t addr, uint8_t value);
}