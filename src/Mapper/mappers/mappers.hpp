#include <cstdint>
#include <fstream>

namespace Mapper {
    class Mapper {
        protected:
            uint8_t *PRG_ROM;
            uint8_t *CHR_ROM;
            uint8_t *PRG_RAM;
            uint8_t *CHR_RAM;

        public:
            virtual uint8_t read(uint16_t addr, bool &bus) = 0;
            virtual void write(uint16_t, uint8_t value) = 0;
            virtual uint8_t readPPU(uint16_t addr, uint16_t &return_addr) = 0;
            virtual void writePPU(uint16_t addr, uint8_t value, uint16_t &return_addr) = 0;
    };

    class NROM : public Mapper {
        private:
            enum Type {
                NROM128,
                NROM256,
                FB_2K,
                FB_4K,
            };

            Type type;
            bool mirroring;
        
        public:
            NROM(std::ifstream& rom);
            
            uint8_t read(uint16_t addr, bool &bus) override;
            void write(uint16_t addr, uint8_t value) override;
            uint8_t readPPU(uint16_t addr, uint16_t &return_addr) override;
            void writePPU(uint16_t addr, uint8_t value, uint16_t &return_addr) override;
    };

#define MAPPERS new NROM(), 0
}