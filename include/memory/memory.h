#ifndef MEMORY_H
#define MEMORY_H

#include <ilb_types.h>

#define MEMORY_SIZE 0xFFFF
typedef struct
{
    u8   mem[MEMORY_SIZE];
    bool is_read_only[MEMORY_SIZE];
} Memory;

extern Memory memory;

u16  mem_load_file(const char *filename, u16 load_addr);
u8   mem_read(u16 addr);
void mem_write(u16 addr, u8 value);
void mem_init(void);
#endif
