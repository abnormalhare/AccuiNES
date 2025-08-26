#include "mapper.hpp"

#include "mappers/_mappers.hpp"

namespace Mapper {
    Mapper *mappers[512] = {
        MAPPERS
    };

    uint16_t currentMapper;

    uint8_t read(uint16_t addr, bool &bus) {
        return mappers[currentMapper]->read(addr, bus);
    }

    void write(uint16_t addr, uint8_t value) {
        mappers[currentMapper]->write(addr, value);
    }
}