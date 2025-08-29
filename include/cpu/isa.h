#ifndef ISA_H
#define ISA_H
#include <ilb_types.h>

typedef enum AddressMode
{
    ADDR_IMPLIED,     // Operand implied by the instruction itself
    ADDR_ACCUMULATOR, // Operand directly on the accumulator (A)
    ADDR_IMMEDIATE,   // Operand is constant 8-bit value
    ADDR_ZEROPAGE,    // Operand is 8-bit address, limited to first 256 bytes of memory
    ADDR_ZEROPAGE_X,  // Operand is ( Zero page address + X register )
    ADDR_ZEROPAGE_Y,  // Operand is ( Zero page address + Y register )
    ADDR_ABSOLUTE,    // Operand is Full 16-bit address
    ADDR_ABSOLUTE_X,  // Operand is ( Absolute address + X register )
    ADDR_ABSOLUTE_Y,  // Operand is ( Absolute address + Y register )
    ADDR_RELATIVE,    // Operand is Relative Offset
    ADDR_INDIRECT,    // Operand is a pointer to the real address
    ADDR_INDIRECT_X,  // Operand is (Zero page address + X register) → pointer → effective address
    ADDR_INDIRECT_Y,  // Operand is Zero page address → (pointer + Y register) → effective address
} AddressMode;

typedef struct Operand
{
    u16  value;     // 16-bit max (covers immediate 8-bit or absolute 16-bit)
    s8   size;      // how many bytes the operand takes (0,1,2)
    char string[7]; // operand string rep
} Operand;

typedef struct
{
    char        mnemonic[4];
    AddressMode addr_mode;
    u8          bytes;
    u8          cycles;
    Operand     operand;
} Instruction;

extern Instruction opcode_table[256];

#endif