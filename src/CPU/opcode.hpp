#pragma once

#include "cpu.hpp"

namespace CPU::Opcode {

    void ADC_I(CPU *);
    void ADC_D(CPU *);
    void ADC_DX(CPU *);
    void ADC_A(CPU *);
    void ADC_AX(CPU *);
    void ADC_AY(CPU *);
    void ADC_NX(CPU *);
    void ADC_NY(CPU *);

    void ADC_I2(CPU *);

    void AHX_AY(CPU *);
    void AHX_NY(CPU *);
    
    void ALR_I(CPU *);
    
    void ANC_I(CPU *);

    void AND_I(CPU *);
    void AND_D(CPU *);
    void AND_DX(CPU *);
    void AND_A(CPU *);
    void AND_AX(CPU *);
    void AND_AY(CPU *);
    void AND_NX(CPU *);
    void AND_NY(CPU *);

    void ASL(CPU *);
    void ASL_D(CPU *);
    void ASL_DX(CPU *);
    void ASL_A(CPU *);
    void ASL_AX(CPU *);
    
    void ARR_I(CPU *);
    
    void AXS_I(CPU *);
    
    void BCC(CPU *);
    void BCS(CPU *);
    void BEQ(CPU *);
    void BMI(CPU *);
    void BNE(CPU *);
    void BPL(CPU *);
    void BVC(CPU *);
    void BVS(CPU *);

    void BIT_D(CPU *);
    void BIT_A(CPU *);

    void BRK(CPU *);

    void CLC(CPU *);
    void CLD(CPU *);
    void CLI(CPU *);
    void CLV(CPU *);

    void CMP_I(CPU *);
    void CMP_D(CPU *);
    void CMP_DX(CPU *);
    void CMP_A(CPU *);
    void CMP_AX(CPU *);
    void CMP_AY(CPU *);
    void CMP_NX(CPU *);
    void CMP_NY(CPU *);
    
    void CPX_I(CPU *);
    void CPX_D(CPU *);
    void CPX_A(CPU *);

    void CPY_I(CPU *);
    void CPY_D(CPU *);
    void CPY_A(CPU *);
    
    void DCP_D(CPU *);
    void DCP_DX(CPU *);
    void DCP_A(CPU *);
    void DCP_AX(CPU *);
    void DCP_AY(CPU *);
    void DCP_NX(CPU *);
    void DCP_NY(CPU *);
    
    void DEC_D(CPU *);
    void DEC_DX(CPU *);
    void DEC_A(CPU *);
    void DEC_AX(CPU *);
    
    void DEX(CPU *);
    void DEY(CPU *);
    
    void EOR_I(CPU *);
    void EOR_D(CPU *);
    void EOR_DX(CPU *);
    void EOR_A(CPU *);
    void EOR_AX(CPU *);
    void EOR_AY(CPU *);
    void EOR_NX(CPU *);
    void EOR_NY(CPU *);
    
    void INC_D(CPU *);
    void INC_DX(CPU *);
    void INC_A(CPU *);
    void INC_AX(CPU *);
    
    void INX(CPU *);
    void INY(CPU *);
    
    void ISC_D(CPU *);
    void ISC_DX(CPU *);
    void ISC_A(CPU *);
    void ISC_AX(CPU *);
    void ISC_AY(CPU *);
    void ISC_NX(CPU *);
    void ISC_NY(CPU *);
    
    void JMP_A(CPU *);
    void JMP_N(CPU *);
    void JSR(CPU *);

    void LAS_AY(CPU *);

    void LAX_I(CPU *);
    void LAX_D(CPU *);
    void LAX_DY(CPU *);
    void LAX_A(CPU *);
    void LAX_AY(CPU *);
    void LAX_NX(CPU *);
    void LAX_NY(CPU *);
    
    void LDA_I(CPU *);
    void LDA_D(CPU *);
    void LDA_DX(CPU *);
    void LDA_A(CPU *);
    void LDA_AX(CPU *);
    void LDA_AY(CPU *);
    void LDA_NX(CPU *);
    void LDA_NY(CPU *);
    
    void LDX_I(CPU *);
    void LDX_D(CPU *);
    void LDX_DY(CPU *);
    void LDX_A(CPU *);
    void LDX_AY(CPU *);
    
    void LDY_I(CPU *);
    void LDY_D(CPU *);
    void LDY_DX(CPU *);
    void LDY_A(CPU *);
    void LDY_AX(CPU *);
    
    void LSR(CPU *);
    void LSR_D(CPU *);
    void LSR_DX(CPU *);
    void LSR_A(CPU *);
    void LSR_AX(CPU *);

    void NOP(CPU *);
    void NOP_I(CPU *);
    void NOP_D(CPU *);
    void NOP_DX(CPU *);
    void NOP_A(CPU *);
    void NOP_AX(CPU *);

    void ORA_I(CPU *);
    void ORA_D(CPU *);
    void ORA_DX(CPU *);
    void ORA_A(CPU *);
    void ORA_AX(CPU *);
    void ORA_AY(CPU *);
    void ORA_NX(CPU *);
    void ORA_NY(CPU *);

    void PHA(CPU *);
    void PHP(CPU *);
    void PLA(CPU *);
    void PLP(CPU *);
    
    void ROL(CPU *);
    void ROL_D(CPU *);
    void ROL_DX(CPU *);
    void ROL_A(CPU *);
    void ROL_AX(CPU *);
    
    void ROR(CPU *);
    void ROR_D(CPU *);
    void ROR_DX(CPU *);
    void ROR_A(CPU *);
    void ROR_AX(CPU *);
    
    void RLA_D(CPU *);
    void RLA_DX(CPU *);
    void RLA_A(CPU *);
    void RLA_AX(CPU *);
    void RLA_AY(CPU *);
    void RLA_NX(CPU *);
    void RLA_NY(CPU *);
    
    void RRA_D(CPU *);
    void RRA_DX(CPU *);
    void RRA_A(CPU *);
    void RRA_AX(CPU *);
    void RRA_AY(CPU *);
    void RRA_NX(CPU *);
    void RRA_NY(CPU *);

    void RTI(CPU *);
    void RTS(CPU *);

    void SAX_D(CPU *);
    void SAX_DY(CPU *);
    void SAX_A(CPU *);
    void SAX_NX(CPU *);
    
    void SEC(CPU *);
    void SED(CPU *);
    void SEI(CPU *);
    
    void SBC_I(CPU *);
    void SBC_D(CPU *);
    void SBC_DX(CPU *);
    void SBC_A(CPU *);
    void SBC_AX(CPU *);
    void SBC_AY(CPU *);
    void SBC_NX(CPU *);
    void SBC_NY(CPU *);

    void SHX_AY(CPU *);
    void SHY_AX(CPU *);
    
    void SLO_D(CPU *);
    void SLO_DX(CPU *);
    void SLO_A(CPU *);
    void SLO_AX(CPU *);
    void SLO_AY(CPU *);
    void SLO_NX(CPU *);
    void SLO_NY(CPU *);
    
    void SRE_D(CPU *);
    void SRE_DX(CPU *);
    void SRE_A(CPU *);
    void SRE_AX(CPU *);
    void SRE_AY(CPU *);
    void SRE_NX(CPU *);
    void SRE_NY(CPU *);
    
    void STP(CPU *);
    
    void STA_D(CPU *);
    void STA_DX(CPU *);
    void STA_A(CPU *);
    void STA_AX(CPU *);
    void STA_AY(CPU *);
    void STA_NX(CPU *);
    void STA_NY(CPU *);
    
    void STX_D(CPU *);
    void STX_DY(CPU *);
    void STX_A(CPU *);
    
    void STY_D(CPU *);
    void STY_DX(CPU *);
    void STY_A(CPU *);

    void TAS_AY(CPU *);
    
    void TAX(CPU *);
    void TAY(CPU *);
    void TSX(CPU *);
    void TXA(CPU *);
    void TXS(CPU *);
    void TYA(CPU *);

    void XAA_I(CPU *);

    typedef void (*opfunc)(CPU *);

    extern opfunc decode_rom[256];
}