#ifndef ISA_H
#define ISA_H
#include <ilb_types.h>

typedef enum AddressMode
{
    ADDR_MODE_IMPLICIT,    // source and destination are directly implied with instruction itself
    ADDR_MODE_ACCUMULATOR, // Some instructions have an option to operate directly upon the accumulator
    ADDR_MODE_IMMEDIATE,   // opreand is specified directly with prefix #
    ADDR_MODE_ZERO_PAGE,   // opreand is only 8-bit addr limit to acces first 256-bytes


    ADDR_MODE_ZERO_PAGE_X, // addressing is calculated by taking the 8 bit zero page address from the instruction and adding the current value of the
                           // X register to it.
    ADDR_MODE_ZERO_PAGE_Y, // addressing is calculated by taking the 8 bit zero page address from the instruction and adding the current value of the
                           // Y register to it.

    ADDR_MODE_ABSOLUTE,   // absolute addressing contain a full 16 bit address to identify the target location.
    ADDR_MODE_ABSOLUTE_X, // absolute addressing contain a full 16 bit address + value of X register to identify the target location.
    ADDR_MODE_ABSOLUTE_Y, // absolute addressing contain a full 16 bit address + value of Y register to identify the target location.

    ADDR_MODE_RELATIVE,
    ADDR_MODE_INDIRECT,
    ADDR_MODE_INDEXED_INDIRECT,
    ADDR_MODE_INDIRECT_INDEXED,
} AddressMode;


typedef enum OperandType
{
    OPERAND_IMPLICIT,         // no operand (CLC, RTS...)
    OPERAND_ACCUMULATOR,      // A
    OPERAND_IMMEDIATE,        // e.g. #$10
    OPERAND_ZERO_PAGE,        // e.g. $45
    OPERAND_ZERO_PAGE_X,      // e.g. $45,X
    OPERAND_ZERO_PAGE_Y,      // e.g. $45,Y
    OPERAND_ABSOLUTE,         // e.g. $1234
    OPERAND_ABSOLUTE_X,       // e.g. $1234,X
    OPERAND_ABSOLUTE_Y,       // e.g. $1234,Y
    OPERAND_RELATIVE,         // e.g. BEQ label
    OPERAND_INDIRECT,         // e.g. JMP ($1234)
    OPERAND_INDEXED_INDIRECT, // e.g. ($40,X)
    OPERAND_INDIRECT_INDEXED  // e.g. ($40),Y
} OperandType;

typedef struct Operand
{
    u16  value;     // 16-bit max (covers immediate 8-bit or absolute 16-bit)
    u8   size;      // how many bytes the operand takes (0,1,2)
    char string[7]; // operand string rep
} Operand;

typedef struct
{
    char        mnemonic[4];
    AddressMode addr_mode;
    u8          size;
    u8          cycles;
    OperandType op_type;
    Operand     operand;
} Instruction;

extern Instruction opcode_table[256];

#endif