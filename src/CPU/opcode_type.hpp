#include "./cpu.hpp"

namespace CPU::Opcode {
    enum index_value {
        X, Y
    };

    // CALCULATION STEP: 1
    bool addr_implied(CPU *cpu);
    // CALCULATION STEP: 1
    bool addr_immediate(CPU *cpu);
    
    // CALCULATION STEP: 3
    bool addr_absolute_read (CPU *cpu);
    // CALCULATION STEP: 4
    bool addr_absolute_rmw  (CPU *cpu);
    // CALCULATION STEP: 2
    bool addr_absolute_write(CPU *cpu);
    
    // CALCULATION STEP: 2
    bool addr_zero_read (CPU *cpu);
    // CALCULATION STEP: 3
    bool addr_zero_rmw  (CPU *cpu);
    // CALCULATION STEP: 1
    bool addr_zero_write(CPU *cpu);
    
    // CALCULATION STEP: 3
    bool addr_zero_index_read (CPU *cpu, index_value value);
    // CALCULATION STEP: 4
    bool addr_zero_index_rmw  (CPU *cpu, index_value value);
    // CALCULATION STEP: 2
    bool addr_zero_index_write(CPU *cpu, index_value value);
    
    // CALCULATION STEP: when func returns true
    bool addr_absolute_index_read (CPU *cpu, index_value value);
    // CALCULATION STEP: 5
    bool addr_absolute_index_rmw  (CPU *cpu, index_value value);
    // CALCULATION STEP: 3
    bool addr_absolute_index_write(CPU *cpu, index_value value);

    // CALCULATION STEP: 1
    void addr_relative(CPU *cpu, bool branch);
    
    // (d,x)  
    // CALCULATION STEP: 5
    bool addr_indexed_indirect_read (CPU *cpu);
    // (d,x)  
    // CALCULATION STEP: 6
    bool addr_indexed_indirect_rmw  (CPU *cpu);
    // (d,x)  
    // CALCULATION STEP: 4
    bool addr_indexed_indirect_write(CPU *cpu);
    
    // (d),y  
    // CALCULATION STEP: when func returns true
    bool addr_indirect_indexed_read (CPU *cpu);
    // (d),y  
    // CALCULATION STEP: 6
    bool addr_indirect_indexed_rmw  (CPU *cpu);
    // (d),y  
    // CALCULATION STEP: 4
    bool addr_indirect_indexed_write(CPU *cpu);
}