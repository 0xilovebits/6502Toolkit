#include <memory/memory.h>
#include <stdio.h>

Memory memory;

u8 mem_read(u16 addr)
{
    if (addr < MEMORY_SIZE) return memory.mem[addr];
    return 0xFF;
}

void mem_write(u16 addr, u8 value)
{
    if (addr < MEMORY_SIZE && !memory.is_read_only[addr])
    {
        memory.mem[addr] = value;
    }
}

void mem_init(void)
{
    for (size_t i = 0; i < MEMORY_SIZE; ++i)
    {
        memory.mem[i]          = 0;
        memory.is_read_only[i] = 0;
    }
}

u16 mem_load_file(const char *filename, u16 load_addr)
{
    FILE *f = fopen(filename, "rb");
    if (!f) return (u16) -1;

    u16 count = 0;
    u32 addr  = load_addr;
    int byte;

    while ((byte = fgetc(f)) != EOF)
    {
        if (addr >= MEMORY_SIZE) break;
        mem_write((u16) addr, (u8) byte);
        ++addr;
        ++count;
    }

    fclose(f);
    return count;
}
