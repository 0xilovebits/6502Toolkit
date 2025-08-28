#ifndef STACK_H
#define STACK_H

#include <cpu/cpu.h>
#include <memory/memory.h>

void push(MOS6502 *cpu, u8 value);
u8   pop(MOS6502 *cpu);

#endif //