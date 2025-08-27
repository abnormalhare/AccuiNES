#pragma once

#include <cstdint>

namespace CPU {
    enum callALU_outtype {
        SUM, AND, EOR, OR, SR,
    };
    enum callALU_flags {
        NONE = 0,
        C = 1 << 0, // carry out enable
        Z = 1 << 1, // zero enable
        V = 1 << 2, // overflow enable
        N = 1 << 3, // negative enable
        ALL = C | Z | V | N,
        R = 1 << 4, // rotate carry (carry in) enable
        B = 1 << 5, // borrow (negate carry) enable
        S_ALL = C | Z | V | N | R,
        B_ALL = C | Z | V | N | B,
    };

struct Status {
    union {
        struct {
            uint8_t c : 1;
            uint8_t z : 1;
            uint8_t i : 1;
            uint8_t d : 1;
            uint8_t b : 1;
            uint8_t v : 1;
            uint8_t o : 1;
            uint8_t n : 1;
        };
        uint8_t reg;
    };
};

class nes_u16 {
private:
    union {
        uint16_t x;
        union {
            uint8_t lo;
            uint8_t hi;
        };
    };

public:
    uint16_t operator=(const uint16_t &other) noexcept {
        this->x = other;
        return this->x;
    }

    nes_u16 &operator=(const nes_u16 &other) noexcept {
        this->x = other.x;
        return *this;
    }

    uint16_t operator%(uint16_t other) noexcept {
        return this->x % other;
    }
    uint16_t operator++(int other) noexcept {
        return this->x++;
    }

    enum Step {
        LO, HI
    };
    void set(uint8_t value, Step step) {
        switch (step) {
            case LO:
                this->lo = value;
                break;
                
            case HI:
                this->hi = value;
                break;
        }
    }

    uint16_t get() { return this->x; }
};

class CPU {
protected:
    nes_u16 PC;
    
    uint8_t DL;
    nes_u16 AB;
    uint8_t IR;

    uint8_t DOR;

    uint8_t RAM[0x800];

    bool running;

    uint8_t readAB();

public:
    uint8_t step : 3;

    uint8_t A;
    uint8_t X;
    uint8_t Y;
    
    uint8_t S;
    Status P;
    
    nes_u16 PCS;
    
    uint8_t AI;
    uint8_t BI;
    uint8_t ADD;

    bool RESET;
    bool NMI;
    bool IRQ;
    bool BRK;
    
    CPU();

    void simulate();

    void read();
    void write();
    void readS();
    void writeS();

    void getInstr();
    void getData();
    void readData();
    void setDOR(uint8_t value);
    uint8_t getDL();
    void DORtoDL();
    void ALUtoABL();

    void callALU(callALU_outtype type, callALU_flags flags);

    void clearABHi() {
        this->AB.set(0, nes_u16::HI);
    }
    
    enum Step {
        LO, HI, SETLO
    };
    void setAB(Step step, bool clear_ai);
    uint8_t getPC(nes_u16::Step step);
    void setPC();
    void incPC(nes_u16::Step step);
    void incPC();
    
private:
    void tick();
    void reset();
};

}