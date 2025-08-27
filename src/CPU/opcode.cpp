#include "opcode.hpp"

#include "CPU/cpu.hpp"
#include "CPU/opcode_type.hpp"
#include "cpu.hpp"
#include <cstdlib>

namespace CPU::Opcode {
    opfunc decode_rom[256] = {

// #include "_decode_rom.hpp"

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
                cpu->step = 0;
                break;
        }
    }

    void CLC(CPU *cpu) {
        if (addr_implied(cpu)) cpu->P.c = 0;
    }
    void CLD(CPU *cpu) {
        if (addr_implied(cpu)) cpu->P.d = 0;
    }
    void CLI(CPU *cpu) {
        if (addr_implied(cpu)) cpu->P.i = 0;
    }
    void CLV(CPU *cpu) {
        if (addr_implied(cpu)) cpu->P.v = 0;
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

    void INC_D(CPU *cpu) {
        if (addr_zero_rmw(cpu)) {
            cpu->AI = 1;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, callALU_flags(Z | N));
            cpu->setDOR(cpu->ADD);
        }
    }
    void INC_DX(CPU *cpu) {
        if (addr_zero_index_rmw(cpu, index_value::X)) {
            cpu->AI = 1;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, callALU_flags(Z | N));
            cpu->setDOR(cpu->ADD);
        }
    }
    void INC_A(CPU *cpu) {
        if (addr_absolute_rmw(cpu)) {
            cpu->AI = 1;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, callALU_flags(Z | N));
            cpu->setDOR(cpu->ADD);
        }
    }
    void INC_AX(CPU *cpu) {
        if (addr_absolute_index_rmw(cpu, index_value::X)) {
            cpu->AI = 1;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, callALU_flags(Z | N));
            cpu->setDOR(cpu->ADD);
        }
    }

    void INX(CPU *cpu) {
        if (addr_implied(cpu)) {
            cpu->AI = 1;
            cpu->BI = cpu->X;
            cpu->callALU(SUM, callALU_flags(Z | N));
            cpu->setDOR(cpu->ADD);
        }
    }

    void INY(CPU *cpu) {
        if (addr_implied(cpu)) {
            cpu->AI = 1;
            cpu->BI = cpu->Y;
            cpu->callALU(SUM, callALU_flags(Z | N));
            cpu->setDOR(cpu->ADD);
        }
    }

    void ISC_D(CPU *cpu) {
        if (addr_zero_rmw(cpu)) {
            cpu->AI = 1;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, callALU_flags(Z | N));
            cpu->setDOR(cpu->ADD);

            cpu->AI = cpu->A;
            cpu->BI = -cpu->ADD;
            cpu->callALU(SUM, callALU_flags(B_ALL));
            cpu->A = cpu->ADD;
        }
    }
    void ISC_DX(CPU *cpu) {
        if (addr_zero_index_rmw(cpu, X)) {
            cpu->AI = 1;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, callALU_flags(Z | N));
            cpu->setDOR(cpu->ADD);

            cpu->AI = cpu->A;
            cpu->BI = -cpu->ADD;
            cpu->callALU(SUM, callALU_flags(B_ALL));
            cpu->A = cpu->ADD;
        }
    }
    void ISC_A(CPU *cpu) {
        if (addr_absolute_rmw(cpu)) {
            cpu->AI = 1;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, callALU_flags(Z | N));
            cpu->setDOR(cpu->ADD);

            cpu->AI = cpu->A;
            cpu->BI = -cpu->ADD;
            cpu->callALU(SUM, callALU_flags(B_ALL));
            cpu->A = cpu->ADD;
        }
    }
    void ISC_AX(CPU *cpu) {
        if (addr_absolute_index_rmw(cpu, X)) {
            cpu->AI = 1;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, callALU_flags(Z | N));
            cpu->setDOR(cpu->ADD);

            cpu->AI = cpu->A;
            cpu->BI = -cpu->ADD;
            cpu->callALU(SUM, callALU_flags(B_ALL));
            cpu->A = cpu->ADD;
        }
    }
    void ISC_AY(CPU *cpu) {
        if (addr_absolute_index_rmw(cpu, Y)) {
            cpu->AI = 1;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, callALU_flags(Z | N));
            cpu->setDOR(cpu->ADD);

            cpu->AI = cpu->A;
            cpu->BI = -cpu->ADD;
            cpu->callALU(SUM, callALU_flags(B_ALL));
            cpu->A = cpu->ADD;
        }
    }
    void ISC_NX(CPU *cpu) {
        if (addr_indexed_indirect_rmw(cpu)) {
            cpu->AI = 1;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, callALU_flags(Z | N));
            cpu->setDOR(cpu->ADD);

            cpu->AI = cpu->A;
            cpu->BI = -cpu->ADD;
            cpu->callALU(SUM, callALU_flags(B_ALL));
            cpu->A = cpu->ADD;
        }
    }
    void ISC_NY(CPU *cpu) {
        if (addr_indirect_indexed_rmw(cpu)) {
            cpu->AI = 1;
            cpu->BI = cpu->getDL();
            cpu->callALU(SUM, callALU_flags(Z | N));
            cpu->setDOR(cpu->ADD);

            cpu->AI = cpu->A;
            cpu->BI = -cpu->ADD;
            cpu->callALU(SUM, callALU_flags(B_ALL));
            cpu->A = cpu->ADD;
        }
    }

    void JMP_A(CPU *cpu) {
        switch (cpu->step) {
            default: cpu->step = 0; break;

            case 1:
                cpu->getData();
                cpu->PCS.set(cpu->getDL(), nes_u16::LO);
                break;
            case 2:
                cpu->getData();
                cpu->PCS.set(cpu->getDL(), nes_u16::HI);

                cpu->setPC();
                cpu->step = 0;
                break;
        }
    }
    void JMP_N(CPU *cpu) {
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
                cpu->getData();
                cpu->PCS.set(cpu->getDL(), nes_u16::LO);
                break;
            case 4:
                cpu->getData();
                cpu->PCS.set(cpu->getDL(), nes_u16::HI);

                cpu->setPC();
                cpu->step = 0;
                break;
        }
    }

    void JSR(CPU *cpu) {
        switch (cpu->step) {
            default: cpu->step = 0; break;

            case 1:
                cpu->getData();
                cpu->PCS.set(cpu->getDL(), nes_u16::LO);
                break;
            case 2:
                break;
            case 3:
                cpu->setDOR(cpu->getPC(nes_u16::LO));
                cpu->writeS();

                cpu->BI = -1;
                cpu->AI = cpu->S;
                cpu->callALU(SUM, NONE);
                break;
            case 4:
                cpu->setDOR(cpu->getPC(nes_u16::HI));
                cpu->writeS();

                cpu->BI = -1;
                cpu->AI = cpu->S;
                cpu->callALU(SUM, NONE);
                break;
            case 5:
                cpu->getData();
                cpu->PCS.set(cpu->getDL(), nes_u16::HI);
                cpu->setPC();
                cpu->step = 0;
                break;
        }
    }

    void LAS_AY(CPU *cpu) {
        if (addr_absolute_index_read(cpu, Y)) {
            cpu->A = cpu->X = cpu->S = cpu->getDL() & cpu->S;
        }
    }

    void LAX_I(CPU *cpu) {
        if (addr_immediate(cpu)) {
            cpu->A = cpu->getDL();
            cpu->X = cpu->A ^ uint8_t(rand() & rand());
        }
    }
    void LAX_D(CPU *cpu) {
        if (addr_zero_read(cpu)) {
            cpu->A = cpu->getDL();
            cpu->X = cpu->A;
        }
    }
    void LAX_DY(CPU *cpu) {
        if (addr_zero_index_read(cpu, Y)) {
            cpu->A = cpu->getDL();
            cpu->X = cpu->A;
        }
    }
    void LAX_A(CPU *cpu) {
        if (addr_absolute_read(cpu)) {
            cpu->A = cpu->getDL();
            cpu->X = cpu->A;
        }
    }
    void LAX_AY(CPU *cpu) {
        if (addr_absolute_index_read(cpu, Y)) {
            cpu->A = cpu->getDL();
            cpu->X = cpu->A;
        }
    }
    void LAX_NX(CPU *cpu) {
        if (addr_indexed_indirect_read(cpu)) {
            cpu->A = cpu->getDL();
            cpu->X = cpu->A;
        }
    }
    void LAX_NY(CPU *cpu) {
        if (addr_indirect_indexed_read(cpu)) {
            cpu->A = cpu->getDL();
            cpu->X = cpu->A;
        }
    }

    void LDA_I(CPU *cpu) {
        if (addr_immediate(cpu)) cpu->A = cpu->getDL();
    }
    void LDA_D(CPU *cpu) {
        if (addr_zero_read(cpu)) cpu->A = cpu->getDL();
    }
    void LDA_DX(CPU *cpu) {
        if (addr_zero_index_read(cpu, X)) cpu->A = cpu->getDL();
    }
    void LDA_A(CPU *cpu) {
        if (addr_absolute_read(cpu)) cpu->A = cpu->getDL();
    }
    void LDA_AX(CPU *cpu) {
        if (addr_absolute_index_read(cpu, X)) cpu->A = cpu->getDL();
    }
    void LDA_AY(CPU *cpu) {
        if (addr_absolute_index_read(cpu, Y)) cpu->A = cpu->getDL();
    }
    void LDA_NX(CPU *cpu) {
        if (addr_indexed_indirect_read(cpu)) cpu->A = cpu->getDL();
    }
    void LDA_NY(CPU *cpu) {
        if (addr_indirect_indexed_read(cpu)) cpu->A = cpu->getDL();
    }

    void LDX_I(CPU *cpu) {
        if (addr_immediate(cpu)) cpu->X = cpu->getDL();
    }
    void LDX_D(CPU *cpu) {
        if (addr_zero_read(cpu)) cpu->X = cpu->getDL();
    }
    void LDX_DY(CPU *cpu) {
        if (addr_zero_index_read(cpu, Y)) cpu->X = cpu->getDL();
    }
    void LDX_A(CPU *cpu) {
        if (addr_absolute_read(cpu)) cpu->X = cpu->getDL();
    }
    void LDX_AY(CPU *cpu) {
        if (addr_absolute_index_read(cpu, Y)) cpu->X = cpu->getDL();
    }

    void LDY_I(CPU *cpu) {
        if (addr_immediate(cpu)) cpu->Y = cpu->getDL();
    }
    void LDY_D(CPU *cpu) {
        if (addr_zero_read(cpu)) cpu->Y = cpu->getDL();
    }
    void LDY_DX(CPU *cpu) {
        if (addr_zero_index_read(cpu, X)) cpu->Y = cpu->getDL();
    }
    void LDY_A(CPU *cpu) {
        if (addr_absolute_read(cpu)) cpu->Y = cpu->getDL();
    }
    void LDY_AX(CPU *cpu) {
        if (addr_absolute_index_read(cpu, X)) cpu->Y = cpu->getDL();
    }

    void LSR(CPU *cpu) {
        if (addr_implied(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = 0;
            cpu->callALU(SR, ALL);
        }
    }
    void LSR_D(CPU *cpu) {
        if (addr_zero_rmw(cpu)) {
            cpu->AI = cpu->getDL();
            cpu->BI = 0;
            cpu->callALU(SR, ALL);
            cpu->setDOR(cpu->ADD);
        }
    }
    void LSR_DX(CPU *cpu) {
        if (addr_zero_index_rmw(cpu, X)) {
            cpu->AI = cpu->getDL();
            cpu->BI = 0;
            cpu->callALU(SR, ALL);
            cpu->setDOR(cpu->ADD);
        }
    }
    void LSR_A(CPU *cpu) {
        if (addr_absolute_rmw(cpu)) {
            cpu->AI = cpu->getDL();
            cpu->BI = 0;
            cpu->callALU(SR, ALL);
            cpu->setDOR(cpu->ADD);
        }
    }
    void LSR_AX(CPU *cpu) {
        if (addr_absolute_index_rmw(cpu, X)) {
            cpu->AI = cpu->getDL();
            cpu->BI = 0;
            cpu->callALU(SR, ALL);
            cpu->setDOR(cpu->ADD);
        }
    }

    void NOP(CPU *cpu)    { addr_implied(cpu); }
    void NOP_I(CPU *cpu)  { addr_immediate(cpu); }
    void NOP_D(CPU *cpu)  { addr_zero_read(cpu); }
    void NOP_DX(CPU *cpu) { addr_zero_index_read(cpu, index_value::X); }
    void NOP_A(CPU *cpu)  { addr_absolute_read(cpu); }
    void NOP_AX(CPU *cpu) { addr_absolute_index_read(cpu, index_value::X); }

    void ORA_I(CPU *cpu) {
        if (addr_immediate(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(OR, ALL);
            cpu->A = cpu->ADD;
        }
    }

    void ORA_D(CPU *cpu) {
        if (addr_zero_read(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(OR, ALL);
            cpu->A = cpu->ADD;
        }
    }

    void ORA_DX(CPU *cpu) {
        if (addr_zero_index_read(cpu, X)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(OR, ALL);
            cpu->A = cpu->ADD;
        }
    }

    void ORA_A(CPU *cpu) {
        if (addr_absolute_read(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(OR, ALL);
            cpu->A = cpu->ADD;
        }
    }

    void ORA_AX(CPU *cpu) {
        if (addr_absolute_index_read(cpu, X)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(OR, ALL);
            cpu->A = cpu->ADD;
        }
    }

    void ORA_AY(CPU *cpu) {
        if (addr_absolute_index_read(cpu, Y)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(OR, ALL);
            cpu->A = cpu->ADD;
        }
    }

    void ORA_NX(CPU *cpu) {
        if (addr_indexed_indirect_read(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(OR, ALL);
            cpu->A = cpu->ADD;
        }
    }

    void ORA_NY(CPU *cpu) {
        if (addr_indirect_indexed_read(cpu)) {
            cpu->AI = cpu->A;
            cpu->BI = cpu->getDL();
            cpu->callALU(OR, ALL);
            cpu->A = cpu->ADD;
        }
    }

    void PHA(CPU *cpu) {
        switch (cpu->step) {
            default: cpu->step = 0; break;

            case 1:
                cpu->readData();
                cpu->setDOR(cpu->A);
                break;
            case 2:
                cpu->write();
                cpu->step = 0;
                break;
        }
    }

    void PHP(CPU *cpu) {
        switch (cpu->step) {
            default: cpu->step = 0; break;

            case 1:
                cpu->readData();
                cpu->setDOR(cpu->P.reg);
                break;
            case 2:
                cpu->write();
                cpu->step = 0;
                break;
        }
    }

    void PLA(CPU *cpu) {
        switch (cpu->step) {
            default: cpu->step = 0; break;

            case 1:
                cpu->readData();
                break;
            case 2:
                cpu->readData();
                cpu->BI = 1;
                cpu->AI = cpu->S;
                cpu->callALU(SUM, NONE);
                break;
            case 3:
                cpu->readS();
                cpu->A = cpu->getDL();
        }
    }

    void PLP(CPU *cpu) {
        switch (cpu->step) {
            default: cpu->step = 0; break;

            case 1:
                cpu->readData();
                break;
            case 2:
                cpu->readData();
                cpu->BI = 1;
                cpu->AI = cpu->S;
                cpu->callALU(SUM, NONE);
                break;
            case 3:
                cpu->readS();
                cpu->P.reg = cpu->getDL();
        }
    }

    void ROL(CPU *cpu) {
        if (addr_implied(cpu)) {
            cpu->AI = cpu->BI = cpu->A;
            cpu->callALU(SUM, callALU_flags(C | Z | N | R));
            cpu->A = cpu->ADD;
        }
    }

    void ROL_D(CPU *cpu) {
        if (addr_zero_rmw(cpu)) {
            cpu->AI = cpu->BI = cpu->getDL();
            cpu->callALU(SUM, callALU_flags(C | Z | N | R));
            cpu->setDOR(cpu->ADD);
        }
    }

    void ROL_DX(CPU *cpu) {
        if (addr_zero_index_rmw(cpu, X)) {
            cpu->AI = cpu->BI = cpu->getDL();
            cpu->callALU(SUM, callALU_flags(C | Z | N | R));
            cpu->setDOR(cpu->ADD);
        }
    }

    void ROL_A(CPU *cpu) {
        if (addr_absolute_rmw(cpu)) {
            cpu->AI = cpu->BI = cpu->getDL();
            cpu->callALU(SUM, callALU_flags(C | Z | N | R));
            cpu->setDOR(cpu->ADD);
        }
    }

    void ROL_AX(CPU *cpu) {
        if (addr_absolute_index_rmw(cpu, X)) {
            cpu->AI = cpu->BI = cpu->getDL();
            cpu->callALU(SUM, callALU_flags(C | Z | N | R));
            cpu->setDOR(cpu->ADD);
        }
    }
}