#include "opcode_type.hpp"
#include "cpu.hpp"

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
                cpu->setAB(CPU::HI, false);
                cpu->BI = cpu->getDL();
                break;
            case 3: {
                cpu->read();
                cpu->AI = 0;
                cpu->callALU(SUM, NONE);
                if (cpu->P.c == 0)  { cpu->step = 0; return true; }
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
                cpu->setAB(CPU::HI, false);
                cpu->BI = cpu->getDL();
                break;
            case 3:
                cpu->read();
                cpu->AI = 0;
                cpu->callALU(SUM, NONE);
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
                cpu->setAB(CPU::HI, false);
                cpu->BI = cpu->getDL();
                break;
            case 3:
                cpu->read();
                cpu->AI = 0;
                cpu->callALU(SUM, NONE);
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
                cpu->AI = 0;
                cpu->callALU(SUM, NONE);
            case 2:
                cpu->read();
                if (branch) {
                    cpu->AI = cpu->ADD;
                    cpu->BI = cpu->getPC(nes_u16::LO);
                    cpu->callALU(SUM, NONE);
                    cpu->PCS.set(cpu->ADD, nes_u16::LO);
                } else {
                    cpu->step = 0;
                }
                break;
            case 3:
                cpu->read();
                if (!branch) cpu->step = 0;
                if (cpu->P.c == 0) cpu->step = 0;
                
                cpu->incPC(nes_u16::HI);
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
                cpu->setAB(CPU::SETLO, false);
                cpu->BI = cpu->ADD;
                break;
            case 3:
                cpu->read();
                cpu->P.c = 1;
                cpu->callALU(SUM, NONE);
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
                cpu->setAB(CPU::SETLO, false);
                cpu->BI = cpu->ADD;
                break;
            case 3:
                cpu->read();
                cpu->P.c = 1;
                cpu->callALU(SUM, NONE);
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
                cpu->setAB(CPU::SETLO, false);
                cpu->BI = cpu->ADD;
                break;
            case 3:
                cpu->read();
                cpu->P.c = 1;
                cpu->callALU(SUM, NONE);
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
                cpu->P.c = 1;
                cpu->callALU(SUM, NONE);
                cpu->ALUtoABL();

                cpu->setAB(CPU::LO, true);
                break;
            case 3:
                cpu->read();
                cpu->AI = cpu->Y;
                cpu->setAB(CPU::HI, false);
                cpu->BI = cpu->getDL();
                break;
            case 4:
                cpu->read();
                cpu->AI = 0;
                cpu->callALU(SUM, NONE);
                if (cpu->P.c == 0) { cpu->step = 0; return true; }
                break;
            case 5:
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
                cpu->P.c = 1;
                cpu->callALU(SUM, NONE);
                cpu->ALUtoABL();

                cpu->setAB(CPU::LO, true);
                break;
            case 3:
                cpu->read();
                cpu->AI = cpu->Y;
                cpu->setAB(CPU::HI, false);
                cpu->BI = cpu->getDL();
                break;
            case 4:
                cpu->read();
                cpu->AI = 0;
                cpu->callALU(SUM, NONE);
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
                cpu->P.c = 1;
                cpu->callALU(SUM, NONE);
                cpu->ALUtoABL();

                cpu->setAB(CPU::LO, true);
                break;
            case 3:
                cpu->read();
                cpu->AI = cpu->Y;
                cpu->setAB(CPU::HI, false);
                cpu->BI = cpu->getDL();
                break;
            case 4:
                cpu->read();
                cpu->AI = 0;
                cpu->callALU(SUM, NONE);
                return true;
            case 5:
                cpu->write();
                cpu->step = 0;
                break;
        }

        return false;
    }
}