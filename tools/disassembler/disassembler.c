#include <cpu/isa.h>
#include <disassembler.h>
#include <memory/memory.h>
#include <stdio.h>
#include <string.h>

static u8 read8(u16 addr)
{
    return mem_read(addr);
}
static u16 read16(u16 addr)
{
    return (u16) mem_read(addr) | ((u16) mem_read(addr + 1) << 8);
}

int disassemble(u16 addr, char *out, size_t out_len)
{
    if (!out || out_len == 0) return 0;

    u8          opcode = mem_read(addr);
    Instruction instr  = opcode_table[opcode];

    if (instr.mnemonic[0] == '\0')
    {
        // snprintf(out, out_len, "???");
        return 0;
    }

    switch (instr.addr_mode)
    {
        case ADDR_IMPLIED: {
            snprintf(out, out_len, "%s", instr.mnemonic);
            return 1;
        }

        case ADDR_ACCUMULATOR: {
            snprintf(out, out_len, "%s A", instr.mnemonic);
            return 1;
        }

        case ADDR_IMMEDIATE: {
            u8 imm = read8(addr + 1);
            snprintf(out, out_len, "%s #$%02X", instr.mnemonic, imm);
            return 2;
        }

        case ADDR_ZEROPAGE: {
            u8 zp = read8(addr + 1);
            snprintf(out, out_len, "%s $%02X", instr.mnemonic, zp);
            return 2;
        }

        case ADDR_ZEROPAGE_X: {
            u8 zp = read8(addr + 1);
            snprintf(out, out_len, "%s $%02X,X", instr.mnemonic, zp);
            return 2;
        }

        case ADDR_ZEROPAGE_Y: {
            u8 zp = read8(addr + 1);
            snprintf(out, out_len, "%s $%02X,Y", instr.mnemonic, zp);
            return 2;
        }

        case ADDR_RELATIVE: {
            s8  offset = (s8) read8(addr + 1);
            u16 target = addr + 2 + offset;
            snprintf(out, out_len, "%s $%04X", instr.mnemonic, target);
            return 2;
        }

        case ADDR_ABSOLUTE: {
            u16 a = read16(addr + 1);
            snprintf(out, out_len, "%s $%04X", instr.mnemonic, a);
            return 3;
        }

        case ADDR_ABSOLUTE_X: {
            u16 a = read16(addr + 1);
            snprintf(out, out_len, "%s $%04X,X", instr.mnemonic, a);
            return 3;
        }

        case ADDR_ABSOLUTE_Y: {
            u16 a = read16(addr + 1);
            snprintf(out, out_len, "%s $%04X,Y", instr.mnemonic, a);
            return 3;
        }

        case ADDR_INDIRECT: {
            u16 a = read16(addr + 1);
            snprintf(out, out_len, "%s ($%04X)", instr.mnemonic, a);
            return 3;
        }

        case ADDR_INDIRECT_X: {
            u8 zp = read8(addr + 1);
            snprintf(out, out_len, "%s ($%02X,X)", instr.mnemonic, zp);
            return 2;
        }

        case ADDR_INDIRECT_Y: {
            u8 zp = read8(addr + 1);
            snprintf(out, out_len, "%s ($%02X),Y", instr.mnemonic, zp);
            return 2;
        }

        default: {
            snprintf(out, out_len, "%s", instr.mnemonic);
            return 1;
        }
    }
}
