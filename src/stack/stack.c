#include <stack/stack.h>

void push(MOS6502 *cpu, u8 value)
{
    memory.mem[STACK_BASE + cpu->regs.SP] = value;
    cpu->regs.SP--;
};

u8 pop(MOS6502 *cpu)
{
    cpu->regs.SP++;
    return memory.mem[STACK_BASE + cpu->regs.SP];
};