#include "opcode_type.hpp"
#include "cpu.hpp"
#include <iostream>

namespace CPU::Opcode {
    // CALCULATION STEP: 1
    bool addr_implied(CPU *cpu) {
        switch (cpu->step) {
            default: cpu->step = 0; break;

            case 1: return true;
        }

        return false;
    }

    // CALCULATION STEP: 1
    bool addr_immediate(CPU *cpu) {
        switch (cpu->step) {
            default: cpu->step = 0; break;

            case 1:
                cpu->getData();
                cpu->step = 0;
                return true;
        }

        return false;
    }

    // CALCULATION STEP: 3
    bool addr_absolute_read(CPU *cpu) {
        switch (cpu->step) {
            default: cpu->step = 0; break;

            case 1:
                cpu->getData();
                cpu->setAB(CPU::LO, true);
                break;
            case 2:
                cpu->getData();
                cpu->setAB(CPU::HI, true);
                break;
            case 3:
                cpu->read();
                cpu->step = 0;
                return true;
        }

        return false;
    }

    // CALCULATION STEP: 4
    bool addr_absolute_rmw(CPU *cpu) {
        switch (cpu->step) {
            default: cpu->step = 0; break;

            case 1:
                cpu->getData();
                cpu->setAB(CPU::LO, true);
                break;
            case 2:
                cpu->getData();
                cpu->setAB(CPU::HI, true);
                break;
            case 3:
                cpu->read();
                break;
            case 4:
                cpu->write();
                return true;
            case 5:
                cpu->write();
                cpu->step = 0;
                break;
                
        }

        return false;
    }

    // CALCULATION STEP: 2
    bool addr_absolute_write(CPU *cpu) {
        switch (cpu->step) {
            default: cpu->step = 0; break;

            case 1:
                cpu->getData();
                cpu->setAB(CPU::LO, true);
                break;
            case 2:
                cpu->getData();
                cpu->setAB(CPU::HI, true);
                return true;
            case 3:
                cpu->write();
                cpu->step = 0;
                break;
        }

        return false;
    }
    
    // CALCULATION STEP: 2
    bool addr_zero_read(CPU *cpu) {
        switch (cpu->step) {
            default: cpu->step = 0; break;

            case 1:
                cpu->getData();
                cpu->setAB(CPU::SETLO, true);
                cpu->clearABHi();
                break;
            case 2:
                cpu->read();
                cpu->step = 0;
                return true;
        }

        return false;
    }

    // CALCULATION STEP: 3
    bool addr_zero_rmw(CPU *cpu) {
        switch (cpu->step) {
            default: cpu->step = 0; break;

            case 1:
                cpu->getData();
                cpu->setAB(CPU::SETLO, true);
                cpu->clearABHi();
                break;
            case 2:
                cpu->read();
                break;
            case 3:
                cpu->write();
                return true;
            case 4:
                cpu->write();
                cpu->step = 0;
                break;
        }

        return false;
    }

    // CALCULATION STEP: 1
    bool addr_zero_write(CPU *cpu) {
        switch (cpu->step) {
            default: cpu->step = 0; break;

            case 1:
                cpu->getData();
                cpu->setAB(CPU::SETLO, true);
                cpu->clearABHi();
                return true;
            case 2:
                cpu->write();
                cpu->step = 0;
                break;
        }

        return false;
    }

    // CALCULATION STEP: 3
    bool addr_zero_index_read(CPU *cpu, index_value value) {
        switch (cpu->step) {
            default: cpu->step = 0; break;

            case 1:
                cpu->getData();
                break;
            case 2:
                cpu->read();

                cpu->AI = (value == index_value::X) ? cpu->X : cpu->Y;
                cpu->setAB(CPU::SETLO, false);
                cpu->clearABHi();
                break;
            case 3:
                cpu->read();
                cpu->step = 0;
                return true;
        }

        return false;
    }

    // CALCULATION STEP: 4
    bool addr_zero_index_rmw(CPU *cpu, index_value value) {
        switch (cpu->step) {
            default: cpu->step = 0; break;

            case 1:
                cpu->getData();
                break;
            case 2:
                cpu->read();

                cpu->AI = (value == index_value::X) ? cpu->X : cpu->Y;
                cpu->setAB(CPU::SETLO, false);
                cpu->clearABHi();
                break;
            case 3:
                cpu->read();
                break;
            case 4:
                cpu->write();
                return true;
            case 5:
                cpu->write();
                cpu->step = 0;
                break;
        }

        return false;
    }

    // CALCULATION STEP: 2
    bool addr_zero_index_write(CPU *cpu, index_value value) {
        switch (cpu->step) {
            default: cpu->step = 0; break;

            case 1:
                cpu->getData();
                break;
            case 2:
                cpu->read();

                cpu->AI = (value == index_value::X) ? cpu->X : cpu->Y;
                cpu->setAB(CPU::SETLO, false);
                cpu->clearABHi();
                return true;
            case 3:
                cpu->write();
                cpu->step = 0;
                break;
        }

        return false;
    }

    bool _index_did_overflow = false;

    // CALCULATION STEP: when func returns true
    bool addr_absolute_index_read(CPU *cpu, index_value value) {
        switch (cpu->step) {
            default: cpu->step = 0; break;

            case 1:
                cpu->getData();
                cpu->setAB(CPU::LO, true);
                break;
            case 2:
                cpu->getData();
                cpu->AI = (value == index_value::X) ? cpu->X : cpu->Y;
                _index_did_overflow = cpu->setAB(CPU::HI, false);
                cpu->BI = cpu->getDL();
                break;
            case 3: {
                cpu->read();
                if (!_index_did_overflow)  { cpu->step = 0; return true; }

                cpu->AI = 0;
                cpu->callALU(SUM, I);
                cpu->AB.set(cpu->ADD, nes_u16::HI);
                break;
            } case 4:
                cpu->read();
                cpu->step = 0;
                return true;
        }
        return false;
    }

    // CALCULATION STEP: 5
    bool addr_absolute_index_rmw(CPU *cpu, index_value value) {
        switch (cpu->step) {
            default: cpu->step = 0; break;

            case 1:
                cpu->getData();
                cpu->setAB(CPU::LO, true);
                break;
            case 2:
                cpu->getData();
                cpu->AI = (value == index_value::X) ? cpu->X : cpu->Y;
                _index_did_overflow = cpu->setAB(CPU::HI, false);
                cpu->BI = cpu->getDL();
                break;
            case 3:
                cpu->read();
                cpu->AI = 0;
                cpu->callALU(SUM, _index_did_overflow ? I : NONE);
                cpu->AB.set(cpu->ADD, nes_u16::HI);
                break;
            case 4:
                cpu->read();
                break;
            case 5:
                cpu->write();
                return true;
            case 6:
                cpu->write();
                cpu->step = 0;
                break;
        }

        return false;
    }

    // CALCULATION STEP: 3
    bool addr_absolute_index_write(CPU *cpu, index_value value) {
        switch (cpu->step) {
            default: cpu->step = 0; break;

            case 1:
                cpu->getData();
                cpu->setAB(CPU::LO, true);
                break;
            case 2:
                cpu->getData();
                cpu->AI = (value == index_value::X) ? cpu->X : cpu->Y;
                _index_did_overflow = cpu->setAB(CPU::HI, false);
                cpu->BI = cpu->getDL();
                break;
            case 3:
                cpu->read();
                cpu->AI = 0;
                cpu->callALU(SUM, _index_did_overflow ? I : NONE);
                cpu->AB.set(cpu->ADD, nes_u16::HI);
                return true;
            case 4:
                cpu->write();
                cpu->step = 0;
                break;
        }

        return false;
    }

    // CALCULATION STEP: 1
    void addr_relative(CPU *cpu, bool branch) {
        switch (cpu->step) {
            default: cpu->step = 0; break;

            case 1:
                cpu->getData();
                cpu->BI = cpu->getDL();
            case 2:
                cpu->read();
                if (branch) {
                    cpu->AI = cpu->getPC(nes_u16::LO);
                    bool co = cpu->callALU(SUM, NONE);
                    cpu->PCS.set(cpu->ADD, nes_u16::LO);
                    cpu->PCS.set(cpu->getPC(nes_u16::HI), nes_u16::HI);
                    if (!(co ^ ((cpu->BI & 0x80) == 0x80))) {
                        cpu->setPC();
                        cpu->step = 0;
                    }
                } else {
                    cpu->step = 0;
                }
                break;
            case 3:
                cpu->read();
                if (!branch) cpu->step = 0;
                
                if (!(cpu->BI & 0x80)) {
                    cpu->PCS.set(((cpu->PCS.get() & 0xFF00) >> 8) + 1, nes_u16::HI);
                } else {
                    cpu->PCS.set(((cpu->PCS.get() & 0xFF00) >> 8) - 1, nes_u16::HI);
                }
                cpu->setPC();
                cpu->step = 0;
                break;
        }
    }

    // (d,x)
    // CALCULATION STEP: 5
    bool addr_indexed_indirect_read(CPU *cpu) {
        switch (cpu->step) {
            default: cpu->step = 0; break;

            case 1:
                cpu->getData();
                cpu->setAB(CPU::SETLO, true);
                cpu->clearABHi();
                break;
            case 2:
                cpu->read();
                cpu->AI = cpu->X;
                cpu->callALU(SUM, NONE);
                cpu->AB.set(cpu->ADD, nes_u16::LO);
                cpu->BI = cpu->ADD;
                break;
            case 3:
                cpu->read();
                cpu->AI = 0;
                cpu->callALU(SUM, I);
                cpu->setAB(CPU::LO, true);
                cpu->ALUtoABL();
                break;
            case 4:
                cpu->read();
                cpu->setAB(CPU::HI, true);
                break;
            case 5:
                cpu->read();
                cpu->step = 0;
                return true;
        }

        return false;
    }

    // (d,x)
    // CALCULATION STEP: 6
    bool addr_indexed_indirect_rmw(CPU *cpu) {
        switch (cpu->step) {
            default: cpu->step = 0; break;

            case 1:
                cpu->getData();
                cpu->setAB(CPU::SETLO, true);
                cpu->clearABHi();
                break;
            case 2:
                cpu->read();
                cpu->AI = cpu->X;
                cpu->callALU(SUM, NONE);
                cpu->AB.set(cpu->ADD, nes_u16::LO);
                cpu->BI = cpu->ADD;
                break;
            case 3:
                cpu->read();
                cpu->AI = 0;
                cpu->callALU(SUM, I);
                cpu->setAB(CPU::LO, true);
                cpu->ALUtoABL();
                break;
            case 4:
                cpu->read();
                cpu->setAB(CPU::HI, true);
                break;
            case 5:
                cpu->read();
                break;
            case 6:
                cpu->write();
                return true;
            case 7:
                cpu->write();
                cpu->step = 0;
                break;
        }

        return false;
    }

    // (d,x)
    // CALCULATION STEP: 4
    bool addr_indexed_indirect_write(CPU *cpu) {
        switch (cpu->step) {
            default: cpu->step = 0; break;

            case 1:
                cpu->getData();
                cpu->setAB(CPU::SETLO, true);
                cpu->clearABHi();
                break;
            case 2:
                cpu->read();
                cpu->AI = cpu->X;
                cpu->callALU(SUM, NONE);
                cpu->AB.set(cpu->ADD, nes_u16::LO);
                cpu->BI = cpu->ADD;
                break;
            case 3:
                cpu->read();
                cpu->AI = 0;
                cpu->callALU(SUM, I);
                cpu->ALUtoABL();

                cpu->setAB(CPU::LO, true);
                break;
            case 4:
                cpu->read();
                cpu->setAB(CPU::HI, true);
                return true;
            case 5:
                cpu->write();
                cpu->step = 0;
                break;
        }

        return false;
    }

    // (d),y
    // CALCULATION STEP: when func returns true
    bool addr_indirect_indexed_read(CPU *cpu) {
        switch (cpu->step) {
            default: cpu->step = 0; break;

            case 1:
                cpu->getData();
                cpu->setAB(CPU::SETLO, true);
                cpu->clearABHi();
                break;
            case 2:
                cpu->read();
                cpu->callALU(SUM, I);
                cpu->ALUtoABL();

                cpu->setAB(CPU::LO, true);
                break;
            case 3:
                cpu->read();
                cpu->AI = cpu->Y;
                _index_did_overflow = cpu->setAB(CPU::HI, false);
                cpu->BI = cpu->getDL();
                break;
            case 4: {
                cpu->read();
                if (!_index_did_overflow) { cpu->step = 0; return true; }
                
                cpu->AI = 0;
                cpu->callALU(SUM, I);
                cpu->AB.set(cpu->ADD, nes_u16::HI);
                break;
            } case 5:
                cpu->read();
                cpu->step = 0;
                return true;
        }

        return false;
    }

    // (d),y
    // CALCULATION STEP: 6
    bool addr_indirect_indexed_rmw(CPU *cpu) {
        switch (cpu->step) {
            default: cpu->step = 0; break;

            case 1:
                cpu->getData();
                cpu->setAB(CPU::SETLO, true);
                cpu->clearABHi();
                break;
            case 2:
                cpu->read();
                cpu->callALU(SUM, I);
                cpu->ALUtoABL();

                cpu->setAB(CPU::LO, true);
                break;
            case 3:
                cpu->read();
                cpu->AI = cpu->Y;
                _index_did_overflow = cpu->setAB(CPU::HI, false);
                cpu->BI = cpu->getDL();
                break;
            case 4:
                cpu->read();
                cpu->AI = 0;
                cpu->callALU(SUM, _index_did_overflow ? I : NONE);
                cpu->AB.set(cpu->ADD, nes_u16::HI);
                break;
            case 5:
                cpu->read();
                break;
            case 6:
                cpu->write();
                return true;
            case 7:
                cpu->write();
                cpu->step = 0;
                break;
        }

        return false;
    }

    // (d),y
    // CALCULATION STEP: 4
    bool addr_indirect_indexed_write(CPU *cpu) {
        switch (cpu->step) {
            default: cpu->step = 0; break;

            case 1:
                cpu->getData();
                cpu->setAB(CPU::SETLO, true);
                cpu->clearABHi();
                break;
            case 2:
                cpu->read();
                cpu->callALU(SUM, I);
                cpu->ALUtoABL();

                cpu->setAB(CPU::LO, true);
                break;
            case 3:
                cpu->read();
                cpu->AI = cpu->Y;
                _index_did_overflow = cpu->setAB(CPU::HI, false);
                cpu->BI = cpu->getDL();
                break;
            case 4:
                cpu->read();
                cpu->AI = 0;
                cpu->callALU(SUM, _index_did_overflow ? I : NONE);
                cpu->AB.set(cpu->ADD, nes_u16::HI);
                
                return true;
            case 5:
                cpu->write();
                cpu->step = 0;
                break;
        }

        return false;
    }
}