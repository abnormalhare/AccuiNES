#include <cstdint>

namespace Mapper {
    class Mapper {
        protected:
            uint8_t *PRG_ROM;
            uint8_t *CHR_ROM;
            uint8_t *PRG_RAM;
            uint8_t *CHR_RAM;

        public:
            Mapper() {
                this->PRG_ROM = new uint8_t[0x4000];
            }

            virtual uint8_t read(uint16_t addr, bool &bus) = 0;
            virtual void write(uint16_t, uint8_t value) = 0;
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
        
        public:
            NROM();
            
            uint8_t read(uint16_t addr, bool &bus) override;
            void write(uint16_t addr, uint8_t value) override;
    };

#define MAPPERS new NROM(), 0
}