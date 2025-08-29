#ifndef CPU_H
#define CPU_H
#define STACK_BASE 0x100
#include <ilb_types.h>
typedef union {
    struct
    {
        u8 C : 1; // Carry
        u8 Z : 1; // Zero
        u8 I : 1; // Interrupt Disable
        u8 D : 1; // Decimal Mode
        u8 B : 1; // Break
        u8 U : 1; // Unused
        u8 V : 1; // Overflow
        u8 N : 1; // Negative
    };
    u8 all;
} ProcessorStatus;

typedef struct
{
    u16             PC; // Program Counter Register (16-bit)
    u8              SP; // Stack Pointer Register (8-bit, points to 0x100–0x1FF)
    u8              A;  // Accumulator Register (8-bit)
    u8              Y;  // General-Purpose Index Y Register (8-bit)
    u8              X;  // General-Purpose Index X Register (8-bit)
    ProcessorStatus P;  // Processor Status Register (8-bit, bit-field)
} registers;

typedef struct
{
    registers regs;
    s64       cycles; // Executed Cycles

} MOS6502;
void cpu_init(MOS6502 *cpu);
#endif