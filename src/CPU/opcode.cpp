#include "opcode.hpp"

#include "CPU/cpu.hpp"
#include "CPU/opcode_type.hpp"

namespace CPU::Opcode {
    opfunc decode_rom[256] = {

#include "_decode_rom.hpp"

    };

    void ADC_I(CPU *cpu) {
        if (addr_immediate(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, S_ALL);
        }
    }

    void ADC_D(CPU *cpu) {
        if (addr_zero_read(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, S_ALL);
        }
    }

    void ADC_DX(CPU *cpu) {
        if (addr_zero_index_read(cpu, X)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, S_ALL);
        }
    }

    void ADC_A(CPU *cpu) {
        if (addr_absolute_read(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, S_ALL);
        }
    }

    void ADC_AX(CPU *cpu) {
        if (addr_absolute_index_read(cpu, X)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, S_ALL);
        }
    }

    void ADC_AY(CPU *cpu) {
        if (addr_absolute_index_read(cpu, Y)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, S_ALL);
        }
    }

    void ADC_NX(CPU *cpu) {
        if (addr_indexed_indirect_read(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, S_ALL);
        }
    }

    void ADC_NY(CPU *cpu) {
        if (addr_indirect_indexed_read(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, S_ALL);
        }
    }

    void AHX_AY(CPU *cpu) {
        if (addr_absolute_index_write(cpu, Y)) {
            cpu->setDOR(cpu->A & cpu->X & cpu->ADD);
        }
    }

    void AHX_NY(CPU *cpu) {
        if (addr_indirect_indexed_write(cpu)) {
            cpu->setDOR(cpu->A & cpu->X & cpu->ADD);
        }
    }

    void ALR_I(CPU *cpu) {
        if (addr_immediate(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(AND, ALL);

            cpu->AI = cpu->BI = cpu->ADD;
            cpu->callALU(SUM, ALL);
            cpu->A = cpu->ADD;
        }
    }

    void ANC_I(CPU *cpu) {
        if (addr_immediate(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(AND, ALL);
            cpu->A = cpu->ADD;
            cpu->P.c = cpu->P.n;
        }
    }

    void AND_I(CPU *cpu) {
        if (addr_immediate(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(AND, ALL);

            cpu->A = cpu->ADD;
        }
    }

    void AND_D(CPU *cpu) {
        if (addr_zero_read(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(AND, ALL);
            
            cpu->A = cpu->ADD;
        }
    }

    void AND_DX(CPU *cpu) {
        if (addr_zero_index_read(cpu, X)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(AND, ALL);
            
            cpu->A = cpu->ADD;
        }
    }

    void AND_A(CPU *cpu) {
        if (addr_absolute_read(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(AND, ALL);
            
            cpu->A = cpu->ADD;
        }
    }

    void AND_AX(CPU *cpu) {
        if (addr_absolute_index_read(cpu, X)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(AND, ALL);
            
            cpu->A = cpu->ADD;
        }
    }

    void AND_AY(CPU *cpu) {
        if (addr_absolute_index_read(cpu, Y)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(AND, ALL);
            
            cpu->A = cpu->ADD;
        }
    }

    void AND_NX(CPU *cpu) {
        if (addr_indexed_indirect_read(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(AND, ALL);
            
            cpu->A = cpu->ADD;
        }
    }

    void AND_NY(CPU *cpu) {
        if (addr_indirect_indexed_read(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(AND, ALL);
            
            cpu->A = cpu->ADD;
        }
    }

    void ASL(CPU *cpu) {
        if (addr_implied(cpu)) {
            cpu->AI = cpu->BI = cpu->A;
            cpu->callALU(SUM, callALU_flags(C | Z | N));
            cpu->A = cpu->ADD;
        }
    }

    void ASL_D(CPU *cpu) {
        if (addr_zero_rmw(cpu)) {
            cpu->AI = cpu->BI = cpu->A;
            cpu->callALU(SUM, callALU_flags(C | Z | N));
            cpu->setDOR(cpu->ADD);
        }
    }

    void ASL_DX(CPU *cpu) {
        if (addr_zero_index_rmw(cpu, X)) {
            cpu->AI = cpu->BI = cpu->A;
            cpu->callALU(SUM, callALU_flags(C | Z | N));
            cpu->setDOR(cpu->ADD);
        }
    }

    void ASL_A(CPU *cpu) {
        if (addr_absolute_rmw(cpu)) {
            cpu->AI = cpu->BI = cpu->A;
            cpu->callALU(SUM, callALU_flags(C | Z | N));
            cpu->setDOR(cpu->ADD);
        }
    }

    void ASL_AX(CPU *cpu) {
        if (addr_absolute_index_rmw(cpu, X)) {
            cpu->AI = cpu->BI = cpu->A;
            cpu->callALU(SUM, callALU_flags(C | Z | N));
            cpu->setDOR(cpu->ADD);
        }
    }

    void ARR_I(CPU *cpu) {
        if (addr_immediate(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(AND, ALL);

            cpu->AI = cpu->A = cpu->ADD;
            cpu->callALU(SR, S_ALL);
            cpu->P.c = ((cpu->ADD & 0x40) == 0x40);
            cpu->P.v = ((cpu->ADD & 0x40) == 0x40) ^ ((cpu->ADD & 0x20) == 0x20);
        }
    }

    void AXS_I(CPU *cpu) {
        if (addr_immediate(cpu)) {
            cpu->AI = cpu->X & cpu->A;
            cpu->BI = -cpu->getDL();
            cpu->callALU(SUM, callALU_flags(C | Z | N));
        }
    }

    void BCC(CPU *cpu) {
        addr_relative(cpu, cpu->P.c == 0);
    }
    void BCS(CPU *cpu) {
        addr_relative(cpu, cpu->P.c == 1);
    }
    void BEQ(CPU *cpu) {
        addr_relative(cpu, cpu->P.z == 1);
    }
    void BMI(CPU *cpu) {
        addr_relative(cpu, cpu->P.n == 1);
    }
    void BNE(CPU *cpu) {
        addr_relative(cpu, cpu->P.z == 0);
    }
    void BPL(CPU *cpu) {
        addr_relative(cpu, cpu->P.n == 0);
    }
    void BVC(CPU *cpu) {
        addr_relative(cpu, cpu->P.v == 0);
    }
    void BVS(CPU *cpu) {
        addr_relative(cpu, cpu->P.v == 1);
    }

    void BIT_D(CPU *cpu) {
        if (addr_zero_read(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(AND, Z);
            cpu->P.v = ((cpu->BI & 0x40) == 0x40);
            cpu->P.n = ((cpu->BI & 0x80) == 0x80);
        }
    }

    void BIT_A(CPU *cpu) {
        if (addr_absolute_read(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(AND, Z);
            cpu->P.v = ((cpu->BI & 0x40) == 0x40);
            cpu->P.n = ((cpu->BI & 0x80) == 0x80);
        }
    }
    
    void BRK(CPU *cpu) {
        switch (cpu->step) {
            case 1:
                cpu->getData();
                break;
            case 2:
                cpu->setDOR(cpu->getPC(nes_u16::LO));
                cpu->writeS();
                break;
            case 3:
                cpu->AI = cpu->ADD;
                cpu->BI = -1;
                cpu->callALU(SUM, NONE);

                cpu->ALUtoABL();
                cpu->setDOR(cpu->getPC(nes_u16::HI));
                cpu->write();
                break;
            case 4:
                cpu->AI = cpu->ADD;
                cpu->BI = -1;
                cpu->callALU(SUM, NONE);

                if (cpu->RESET) cpu->setDOR(0xFC);
                if (cpu->NMI)   cpu->setDOR(0xFA);
                if (cpu->IRQ || cpu->BRK) cpu->setDOR(0xFE);

                cpu->ALUtoABL();
                cpu->setDOR(cpu->P.reg | 0x30);
                cpu->write();
                break;
            case 5:
                cpu->AI = cpu->S;
                cpu->BI = -3;
                cpu->callALU(SUM, NONE);
                cpu->S = cpu->ADD;

                cpu->DORtoDL();
                cpu->PCS.set(cpu->getDL(), nes_u16::LO);
                break;
            case 6:
                cpu->P.reg |=  0x04;
                cpu->P.reg &= ~0x10;

                cpu->PCS.set(0xFF, nes_u16::HI);
                break;
            case 7:
                cpu->setPC();
                break;
        }
    }

    void CLC(CPU *cpu) {
        if (addr_implied(cpu)) {
            cpu->P.c = 0;
        }
    }

    void CLD(CPU *cpu) {
        if (addr_implied(cpu)) {
            cpu->P.d = 0;
        }
    }

    void CLI(CPU *cpu) {
        if (addr_implied(cpu)) {
            cpu->P.i = 0;
        }
    }

    void CLV(CPU *cpu) {
        if (addr_implied(cpu)) {
            cpu->P.v = 0;
        }
    }

    void CMP_I(CPU *cpu) {
        if (addr_immediate(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = -cpu->getDL();
            cpu->callALU(SUM, callALU_flags(C | Z | N));
        }
    }

    void CMP_D(CPU *cpu) {
        if (addr_zero_read(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = -cpu->getDL();
            cpu->callALU(SUM, callALU_flags(C | Z | N));
        }
    }

    void CMP_DX(CPU *cpu) {
        if (addr_zero_index_read(cpu, X)) {
            cpu->AI = cpu->A;
            cpu->BI = -cpu->getDL();
            cpu->callALU(SUM, callALU_flags(C | Z | N));
        }
    }

    void CMP_A(CPU *cpu) {
        if (addr_absolute_read(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = -cpu->getDL();
            cpu->callALU(SUM, callALU_flags(C | Z | N));
        }
    }

    void CMP_AX(CPU *cpu) {
        if (addr_absolute_index_read(cpu, X)) {
            cpu->AI = cpu->A;
            cpu->BI = -cpu->getDL();
            cpu->callALU(SUM, callALU_flags(C | Z | N));
        }
    }

    void CMP_AY(CPU *cpu) {
        if (addr_absolute_index_read(cpu, Y)) {
            cpu->AI = cpu->A;
            cpu->BI = -cpu->getDL();
            cpu->callALU(SUM, callALU_flags(C | Z | N));
        }
    }

    void CMP_NX(CPU *cpu) {
        if (addr_indexed_indirect_read(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = -cpu->getDL();
            cpu->callALU(SUM, callALU_flags(C | Z | N));
        }
    }

    void CMP_NY(CPU *cpu) {
        if (addr_indirect_indexed_read(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = -cpu->getDL();
            cpu->callALU(SUM, callALU_flags(C | Z | N));
        }
    }

    void CPX_I(CPU *cpu) {
        if (addr_immediate(cpu)) {
            cpu->AI = cpu->X;
            cpu->BI = -cpu->getDL();
            cpu->callALU(SUM, callALU_flags(C | Z | N));
        }
    }

    void CPX_D(CPU *cpu) {
        if (addr_zero_read(cpu)) {
            cpu->AI = cpu->X;
            cpu->BI = -cpu->getDL();
            cpu->callALU(SUM, callALU_flags(C | Z | N));
        }
    }

    void CPX_A(CPU *cpu) {
        if (addr_absolute_read(cpu)) {
            cpu->AI = cpu->X;
            cpu->BI = -cpu->getDL();
            cpu->callALU(SUM, callALU_flags(C | Z | N));
        }
    }

    void CPY_I(CPU *cpu) {
        if (addr_immediate(cpu)) {
            cpu->AI = cpu->Y;
            cpu->BI = -cpu->getDL();
            cpu->callALU(SUM, callALU_flags(C | Z | N));
        }
    }

    void CPY_D(CPU *cpu) {
        if (addr_zero_read(cpu)) {
            cpu->AI = cpu->Y;
            cpu->BI = -cpu->getDL();
            cpu->callALU(SUM, callALU_flags(C | Z | N));
        }
    }

    void CPY_A(CPU *cpu) {
        if (addr_absolute_read(cpu)) {
            cpu->AI = cpu->Y;
            cpu->BI = -cpu->getDL();
            cpu->callALU(SUM, callALU_flags(C | Z | N));
        }
    }

    void DCP_D(CPU *cpu) {
        if (addr_zero_rmw(cpu)) {
            cpu->AI = -1;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, callALU_flags(Z | N));
            cpu->setDOR(cpu->ADD);
            
            cpu->BI = -cpu->ADD;
            cpu->AI = cpu->A;
            cpu->callALU(SUM, callALU_flags(C | Z | N));
        }
    }

    void DCP_DX(CPU *cpu) {
        if (addr_zero_index_rmw(cpu, index_value::X)) {
            cpu->AI = -1;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, callALU_flags(Z | N));
            cpu->setDOR(cpu->ADD);
            
            cpu->BI = -cpu->ADD;
            cpu->AI = cpu->A;
            cpu->callALU(SUM, callALU_flags(C | Z | N));
        }
    }

    void DCP_A(CPU *cpu) {
        if (addr_absolute_rmw(cpu)) {
            cpu->AI = -1;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, callALU_flags(Z | N));
            cpu->setDOR(cpu->ADD);
            
            cpu->BI = -cpu->ADD;
            cpu->AI = cpu->A;
            cpu->callALU(SUM, callALU_flags(C | Z | N));
        }
    }

    void DCP_AX(CPU *cpu) {
        if (addr_absolute_index_rmw(cpu, index_value::X)) {
            cpu->AI = -1;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, callALU_flags(Z | N));
            cpu->setDOR(cpu->ADD);
            
            cpu->BI = -cpu->ADD;
            cpu->AI = cpu->A;
            cpu->callALU(SUM, callALU_flags(C | Z | N));
        }
    }

    void DCP_AY(CPU *cpu) {
        if (addr_absolute_index_rmw(cpu, index_value::Y)) {
            cpu->AI = -1;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, callALU_flags(Z | N));
            cpu->setDOR(cpu->ADD);
            
            cpu->BI = -cpu->ADD;
            cpu->AI = cpu->A;
            cpu->callALU(SUM, callALU_flags(C | Z | N));
        }
    }

    void DCP_NX(CPU *cpu) {
        if (addr_indexed_indirect_rmw(cpu)) {
            cpu->AI = -1;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, callALU_flags(Z | N));
            cpu->setDOR(cpu->ADD);
            
            cpu->BI = -cpu->ADD;
            cpu->AI = cpu->A;
            cpu->callALU(SUM, callALU_flags(C | Z | N));
        }
    }

    void DCP_NY(CPU *cpu) {
        if (addr_indirect_indexed_rmw(cpu)) {
            cpu->AI = -1;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, callALU_flags(Z | N));
            cpu->setDOR(cpu->ADD);
            
            cpu->BI = -cpu->ADD;
            cpu->AI = cpu->A;
            cpu->callALU(SUM, callALU_flags(C | Z | N));
        }
    }

    void DEC_D(CPU *cpu) {
        if (addr_zero_rmw(cpu)) {
            cpu->AI = -1;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, callALU_flags(Z | N));
            cpu->setDOR(cpu->ADD);
        }
    }

    void DEC_DX(CPU *cpu) {
        if (addr_zero_index_rmw(cpu, index_value::X)) {
            cpu->AI = -1;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, callALU_flags(Z | N));
            cpu->setDOR(cpu->ADD);
        }
    }

    void DEC_A(CPU *cpu) {
        if (addr_absolute_rmw(cpu)) {
            cpu->AI = -1;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, callALU_flags(Z | N));
            cpu->setDOR(cpu->ADD);
        }
    }

    void DEC_AX(CPU *cpu) {
        if (addr_absolute_index_rmw(cpu, index_value::X)) {
            cpu->AI = -1;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, callALU_flags(Z | N));
            cpu->setDOR(cpu->ADD);
        }
    }

    void DEX(CPU *cpu) {
        if (addr_implied(cpu)) {
            cpu->AI = -1;
            cpu->BI = cpu->X;
            cpu->callALU(SUM, callALU_flags(Z | N));
            cpu->setDOR(cpu->ADD);
        }
    }

    void DEY(CPU *cpu) {
        if (addr_implied(cpu)) {
            cpu->AI = -1;
            cpu->BI = cpu->Y;
            cpu->callALU(SUM, callALU_flags(Z | N));
            cpu->setDOR(cpu->ADD);
        }
    }

    void EOR_I(CPU *cpu) {
        if (addr_immediate(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(EOR, callALU_flags(ALL));
            cpu->A = cpu->ADD;
        }
    }

    void EOR_D(CPU *cpu) {
        if (addr_zero_read(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(EOR, callALU_flags(ALL));
            cpu->A = cpu->ADD;
        }
    }

    void EOR_DX(CPU *cpu) {
        if (addr_zero_index_read(cpu, index_value::X)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(EOR, callALU_flags(ALL));
            cpu->A = cpu->ADD;
        }
    }

    void EOR_A(CPU *cpu) {
        if (addr_absolute_read(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(EOR, callALU_flags(ALL));
            cpu->A = cpu->ADD;
        }
    }

    void EOR_AX(CPU *cpu) {
        if (addr_absolute_index_read(cpu, index_value::X)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(EOR, callALU_flags(ALL));
            cpu->A = cpu->ADD;
        }
    }

    void EOR_AY(CPU *cpu) {
        if (addr_absolute_index_read(cpu, index_value::Y)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(EOR, callALU_flags(ALL));
            cpu->A = cpu->ADD;
        }
    }

    void EOR_NX(CPU *cpu) {
        if (addr_indexed_indirect_read(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(EOR, callALU_flags(ALL));
            cpu->A = cpu->ADD;
        }
    }

    void EOR_NY(CPU *cpu) {
        if (addr_indirect_indexed_read(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(EOR, callALU_flags(ALL));
            cpu->A = cpu->ADD;
        }
    }
}