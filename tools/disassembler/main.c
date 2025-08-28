#include <disassembler.h>
#include <memory/memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define C_RESET "\x1b[0m"
#define C_CYAN "\x1b[36m"
#define C_YELLOW "\x1b[33m"
#define C_DIM "\x1b[2m"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "usage: %s <binary-file> [load_addr hex] [start_addr hex] [disasm_count]\n", argv[0]);
        return 1;
    }

    const char *file              = argv[1];
    u16         load_addr         = (argc > 2) ? (u16) strtoul(argv[2], NULL, 0) : 0x0600;
    u16         start_addr        = (argc > 3) ? (u16) strtoul(argv[3], NULL, 0) : load_addr;
    u16         user_disasm_count = (argc > 4) ? (u16) strtoul(argv[4], NULL, 0) : 0x100;

    mem_init();

    u16 bytes_loaded = mem_load_file(file, load_addr);
    if (bytes_loaded == (u16) -1)
    {
        fprintf(stderr, "failed to open %s\n", file);
        return 2;
    }

    char out[128];

    u16 pc = start_addr;
    if (pc < load_addr) pc = load_addr;
    u16 file_end  = load_addr + bytes_loaded;
    u16 available = 0;
    if (pc < file_end) available = file_end - pc;
    u16 end;
    if (user_disasm_count == 0)
    {
        end = file_end;
    }
    else
    {
        if (user_disasm_count <= available)
            end = pc + user_disasm_count;
        else
            end = pc + available;
    }

    while (pc < end)
    {
        int size = disassemble(pc, out, sizeof(out));
        if (size <= 0)
        {
            printf(C_CYAN "%04X: " C_RESET C_DIM ".db $%02X" C_RESET "\n", pc, mem_read(pc));
            pc += 1;
            continue;
        }
        printf(C_CYAN "%04X: " C_RESET C_YELLOW "%s" C_RESET "\n", pc, out);

        pc += (u16) size;
    }
    return 0;
}
