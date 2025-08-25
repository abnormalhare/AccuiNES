#pragma once

#include <cstdint>

namespace Mapper {
    extern uint16_t currentMapper;

    uint8_t read(uint16_t addr, bool &bus);
    void write(uint16_t addr, uint8_t value);
}