#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H

#include <ilb_types.h>
#include <stddef.h>
int disassemble(u16 addr, char *out, size_t out_len);

#endif