#include <stack/stack.h>

void push(MOS6502 *cpu, u8 value)
{
    mem[STACK_BASE + cpu->regs.SP] = value;
    cpu->regs.SP--;
};

u8 pop(MOS6502 *cpu)
{
    cpu->regs.SP++;
    return mem[STACK_BASE + cpu->regs.SP];
};