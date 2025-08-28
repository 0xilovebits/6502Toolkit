#include <cpu/cpu.h>

void cpu_init(MOS6502 *cpu)
{
    cpu->regs.SP    = (u8) 0xFF;
    cpu->regs.PC    = (u16) 0;
    cpu->regs.A     = 0;
    cpu->regs.P.all = 0x34;
    cpu->regs.X     = 0;
    cpu->regs.Y     = 0;
};