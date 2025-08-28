#include <cpu/isa.h>

/*

{
    char        mnemonic[4];
    AddressMode addr_mode;
    u8          size;
    u8          cycles;
    OperandType op_type;
    Operand     operand; // not define in the table
} Instruction;
*/
Instruction opcode_table[256] = {

    [0x69] = {"ADC", ADDR_MODE_IMMEDIATE, 2, 2},   [0x65] = {"ADC", ADDR_MODE_ZERO_PAGE, 2, 3},
    [0x75] = {"ADC", ADDR_MODE_ZERO_PAGE_X, 2, 4}, [0x6D] = {"ADC", ADDR_MODE_ABSOLUTE, 3, 4},
    [0x7D] = {"ADC", ADDR_MODE_ABSOLUTE_X, 3, 4}, // (+1 if page crossed)
    [0x79] = {"ADC", ADDR_MODE_ABSOLUTE_Y, 3, 4}, // (+1 if page crossed)
    [0x29] = {"AND", ADDR_MODE_IMMEDIATE, 2, 2},   [0x2D] = {"AND", ADDR_MODE_ABSOLUTE, 3, 4},
    [0x3D] = {"AND", ADDR_MODE_ABSOLUTE_X, 3, 4}, // (+1 if page crossed)
    [0x39] = {"AND", ADDR_MODE_ABSOLUTE_Y, 3, 4}, // (+1 if page crossed)
    [0x0A] = {"ASL", ADDR_MODE_ACCUMULATOR, 1, 2}, [0x0E] = {"ASL", ADDR_MODE_ABSOLUTE, 3, 6},
    [0x1E] = {"ASL", ADDR_MODE_ABSOLUTE_X, 3, 7},  [0x90] = {"BCC", ADDR_MODE_RELATIVE, 2, 2}, // (+1 if branch succeeds +2 if to a new page)
    [0xB0] = {"BCS", ADDR_MODE_RELATIVE, 2, 2},                                                // (+1 if branch succeeds +2 if to a new page)
    [0xF0] = {"BEQ", ADDR_MODE_RELATIVE, 2, 2},                                                // (+1 if branch succeeds +2 if to a new page)
    [0x2C] = {"BIT", ADDR_MODE_ABSOLUTE, 3, 4},    [0x30] = {"BMI", ADDR_MODE_RELATIVE, 2, 2}, // (+1 if branch succeeds +2 if to a new page)
    [0xD0] = {"BNE", ADDR_MODE_RELATIVE, 2, 2},                                                // (+1 if branch succeeds +2 if to a new page)
    [0x10] = {"BPL", ADDR_MODE_RELATIVE, 2, 2},                                                // (+1 if branch succeeds +2 if to a new page)
    [0x00] = {"BRK", ADDR_MODE_IMPLICIT, 1, 7},    [0x50] = {"BVC", ADDR_MODE_RELATIVE, 2, 2}, // (+1 if branch succeeds +2 if to a new page)
    [0x70] = {"BVS", ADDR_MODE_RELATIVE, 2, 2},                                                // (+1 if branch succeeds +2 if to a new page)
    [0x18] = {"CLC", ADDR_MODE_IMPLICIT, 1, 2},    [0xD8] = {"CLD", ADDR_MODE_IMPLICIT, 1, 2},
    [0x58] = {"CLI", ADDR_MODE_IMPLICIT, 1, 2},    [0xB8] = {"CLV", ADDR_MODE_IMPLICIT, 1, 2},
    [0xC9] = {"CMP", ADDR_MODE_IMMEDIATE, 2, 2},   [0xC5] = {"CMP", ADDR_MODE_ZERO_PAGE, 2, 3},
    [0xD5] = {"CMP", ADDR_MODE_ZERO_PAGE_X, 2, 4}, [0xCD] = {"CMP", ADDR_MODE_ABSOLUTE, 3, 4},
    [0xDD] = {"CMP", ADDR_MODE_ABSOLUTE_X, 3, 4}, // (+1 if page crossed)
    [0xD9] = {"CMP", ADDR_MODE_ABSOLUTE_Y, 3, 4}, // (+1 if page crossed)
    [0xE0] = {"CPX", ADDR_MODE_IMMEDIATE, 2, 2},   [0xE4] = {"CPX", ADDR_MODE_ZERO_PAGE, 2, 3},
    [0xEC] = {"CPX", ADDR_MODE_ABSOLUTE, 3, 4},    [0xC0] = {"CPY", ADDR_MODE_IMMEDIATE, 2, 2},
    [0xC4] = {"CPY", ADDR_MODE_ZERO_PAGE, 2, 3},   [0xCC] = {"CPY", ADDR_MODE_ABSOLUTE, 3, 4},
    [0xC6] = {"DEC", ADDR_MODE_ZERO_PAGE, 2, 5},   [0xD6] = {"DEC", ADDR_MODE_ZERO_PAGE_X, 2, 6},
    [0xCE] = {"DEC", ADDR_MODE_ABSOLUTE, 3, 6},    [0xDE] = {"DEC", ADDR_MODE_ABSOLUTE_X, 3, 7},
    [0xCA] = {"DEX", ADDR_MODE_IMPLICIT, 1, 2},    [0x88] = {"DEY", ADDR_MODE_IMPLICIT, 1, 2},
    [0x49] = {"EOR", ADDR_MODE_IMMEDIATE, 2, 2},   [0x4D] = {"EOR", ADDR_MODE_ABSOLUTE, 3, 4},
    [0x5D] = {"EOR", ADDR_MODE_ABSOLUTE_X, 3, 4}, // (+1 if page crossed)
    [0x59] = {"EOR", ADDR_MODE_ABSOLUTE_Y, 3, 4}, // (+1 if page crossed)
    [0xE6] = {"INC", ADDR_MODE_ZERO_PAGE, 2, 5},   [0xF6] = {"INC", ADDR_MODE_ZERO_PAGE_X, 2, 6},
    [0xEE] = {"INC", ADDR_MODE_ABSOLUTE, 3, 6},    [0xFE] = {"INC", ADDR_MODE_ABSOLUTE_X, 3, 7},
    [0xE8] = {"INX", ADDR_MODE_IMPLICIT, 1, 2},    [0xC8] = {"INY", ADDR_MODE_IMPLICIT, 1, 2},
    [0x4C] = {"JMP", ADDR_MODE_ABSOLUTE, 3, 3},    [0x6C] = {"JMP", ADDR_MODE_INDIRECT, 3, 5},
    [0x20] = {"JSR", ADDR_MODE_ABSOLUTE, 3, 6},    [0xA9] = {"LDA", ADDR_MODE_IMMEDIATE, 2, 2},
    [0xA5] = {"LDA", ADDR_MODE_ZERO_PAGE, 2, 3},   [0xB5] = {"LDA", ADDR_MODE_ZERO_PAGE_X, 2, 4},
    [0xAD] = {"LDA", ADDR_MODE_ABSOLUTE, 3, 4},    [0xBD] = {"LDA", ADDR_MODE_ABSOLUTE_X, 3, 4}, // (+1 if page crossed)
    [0xB9] = {"LDA", ADDR_MODE_ABSOLUTE_Y, 3, 4},                                                // (+1 if page crossed)
    [0xA2] = {"LDX", ADDR_MODE_IMMEDIATE, 2, 2},   [0xA6] = {"LDX", ADDR_MODE_ZERO_PAGE, 2, 3},
    [0xB6] = {"LDX", ADDR_MODE_ZERO_PAGE_Y, 2, 4}, [0xAE] = {"LDX", ADDR_MODE_ABSOLUTE, 3, 4},
    [0xBE] = {"LDX", ADDR_MODE_ABSOLUTE_Y, 3, 4}, // (+1 if page crossed)
    [0xA0] = {"LDY", ADDR_MODE_IMMEDIATE, 2, 2},   [0xA4] = {"LDY", ADDR_MODE_ZERO_PAGE, 2, 3},
    [0xB4] = {"LDY", ADDR_MODE_ZERO_PAGE_X, 2, 4}, [0xAC] = {"LDY", ADDR_MODE_ABSOLUTE, 3, 4},
    [0xBC] = {"LDY", ADDR_MODE_ABSOLUTE_X, 3, 4}, // (+1 if page crossed)
    [0x4A] = {"LSR", ADDR_MODE_ACCUMULATOR, 1, 2}, [0x4E] = {"LSR", ADDR_MODE_ABSOLUTE, 3, 6},
    [0x5E] = {"LSR", ADDR_MODE_ABSOLUTE_X, 3, 7},  [0xEA] = {"NOP", ADDR_MODE_IMPLICIT, 1, 2},
    [0x09] = {"ORA", ADDR_MODE_IMMEDIATE, 2, 2},   [0x05] = {"ORA", ADDR_MODE_ZERO_PAGE, 2, 3},
    [0x15] = {"ORA", ADDR_MODE_ZERO_PAGE_X, 2, 4}, [0x0D] = {"ORA", ADDR_MODE_ABSOLUTE, 3, 4},
    [0x1D] = {"ORA", ADDR_MODE_ABSOLUTE_X, 3, 4}, // (+1 if page crossed)
    [0x19] = {"ORA", ADDR_MODE_ABSOLUTE_Y, 3, 4}, // (+1 if page crossed)
    [0x48] = {"PHA", ADDR_MODE_IMPLICIT, 1, 3},    [0x08] = {"PHP", ADDR_MODE_IMPLICIT, 1, 3},
    [0x68] = {"PLA", ADDR_MODE_IMPLICIT, 1, 4},    [0x28] = {"PLP", ADDR_MODE_IMPLICIT, 1, 4},
    [0x2A] = {"ROL", ADDR_MODE_ACCUMULATOR, 1, 2}, [0x2E] = {"ROL", ADDR_MODE_ABSOLUTE, 3, 6},
    [0x3E] = {"ROL", ADDR_MODE_ABSOLUTE_X, 3, 7},  [0x6A] = {"ROR", ADDR_MODE_ACCUMULATOR, 1, 2},
    [0x6E] = {"ROR", ADDR_MODE_ABSOLUTE, 3, 6},    [0x7E] = {"ROR", ADDR_MODE_ABSOLUTE_X, 3, 7},
    [0x40] = {"RTI", ADDR_MODE_IMPLICIT, 1, 6},    [0x60] = {"RTS", ADDR_MODE_IMPLICIT, 1, 6},
    [0xE9] = {"SBC", ADDR_MODE_IMMEDIATE, 2, 2},   [0xE5] = {"SBC", ADDR_MODE_ZERO_PAGE, 2, 3},
    [0xF5] = {"SBC", ADDR_MODE_ZERO_PAGE_X, 2, 4}, [0xED] = {"SBC", ADDR_MODE_ABSOLUTE, 3, 4},
    [0xFD] = {"SBC", ADDR_MODE_ABSOLUTE_X, 3, 4}, // (+1 if page crossed)
    [0xF9] = {"SBC", ADDR_MODE_ABSOLUTE_Y, 3, 4}, // (+1 if page crossed)
    [0x38] = {"SEC", ADDR_MODE_IMPLICIT, 1, 2},    [0xF8] = {"SED", ADDR_MODE_IMPLICIT, 1, 2},
    [0x78] = {"SEI", ADDR_MODE_IMPLICIT, 1, 2},    [0x85] = {"STA", ADDR_MODE_ZERO_PAGE, 2, 3},
    [0x95] = {"STA", ADDR_MODE_ZERO_PAGE_X, 2, 4}, [0x8D] = {"STA", ADDR_MODE_ABSOLUTE, 3, 4},
    [0x9D] = {"STA", ADDR_MODE_ABSOLUTE_X, 3, 5},  [0x99] = {"STA", ADDR_MODE_ABSOLUTE_Y, 3, 5},
    [0x86] = {"STX", ADDR_MODE_ZERO_PAGE, 2, 3},   [0x96] = {"STX", ADDR_MODE_ZERO_PAGE_Y, 2, 4},
    [0x8E] = {"STX", ADDR_MODE_ABSOLUTE, 3, 4},    [0x84] = {"STY", ADDR_MODE_ZERO_PAGE, 2, 3},
    [0x94] = {"STY", ADDR_MODE_ZERO_PAGE_X, 2, 4}, [0x8C] = {"STY", ADDR_MODE_ABSOLUTE, 3, 4},
    [0xAA] = {"TAX", ADDR_MODE_IMPLICIT, 1, 2},    [0xA8] = {"TAY", ADDR_MODE_IMPLICIT, 1, 2},
    [0xBA] = {"TSX", ADDR_MODE_IMPLICIT, 1, 2},    [0x8A] = {"TXA", ADDR_MODE_IMPLICIT, 1, 2},
    [0x9A] = {"TXS", ADDR_MODE_IMPLICIT, 1, 2},    [0x98] = {"TYA", ADDR_MODE_IMPLICIT, 1, 2},
};