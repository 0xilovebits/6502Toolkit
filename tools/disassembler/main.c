#include <disassembler.h>
#include <memory/memory.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define C_RESET "\x1b[0m"
#define C_CYAN "\x1b[36m"
#define C_YELLOW "\x1b[33m"
#define C_DIM "\x1b[2m"

void usage(const char *prog)
{
    fprintf(stderr,
            "Usage: %s <binary-file> [options]\n"
            "Options:\n"
            "  -l <hex>   Load address (default 0x0600)\n"
            "  -s <hex>   Start address (default = load address)\n"
            "  -n <num>   Number of instructions to disassemble (default 0x100)\n"
            "  -b         Show raw bytes of each instruction\n"
            "  -C         Disable colors\n",
            prog);
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        usage(argv[0]);
        return 1;
    }

    const char *file         = argv[1];
    u16         load_addr    = 0x0600;
    u16         start_addr   = 0x0600;
    u16         disasm_count = 0x100;
    bool        show_bytes   = false;
    bool        use_color    = true;

    for (int i = 2; i < argc; i++)
    {
        if (!strcmp(argv[i], "-l") && i + 1 < argc)
        {
            load_addr = (u16) strtoul(argv[++i], NULL, 0);
        }
        else if (!strcmp(argv[i], "-s") && i + 1 < argc)
        {
            start_addr = (u16) strtoul(argv[++i], NULL, 0);
        }
        else if (!strcmp(argv[i], "-n") && i + 1 < argc)
        {
            disasm_count = (u16) strtoul(argv[++i], NULL, 0);
        }
        else if (!strcmp(argv[i], "-b"))
        {
            show_bytes = true;
        }
        else if (!strcmp(argv[i], "-C"))
        {
            use_color = false;
        }
        else
        {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            usage(argv[0]);
            return 1;
        }
    }

    if (start_addr == 0xFFFF) start_addr = load_addr;

    mem_init();

    u16 bytes_loaded = mem_load_file(file, load_addr);
    if (bytes_loaded == (u16) -1)
    {
        fprintf(stderr, "failed to open %s\n", file);
        return 2;
    }

    char out[128];
    char bytes_str[32];

    u16 pc       = start_addr;
    u16 file_end = load_addr + bytes_loaded;
    if (pc < load_addr) pc = load_addr;
    u16 available = (pc < file_end) ? (file_end - pc) : 0;
    u16 end       = (disasm_count == 0) ? file_end : ((disasm_count <= available) ? pc + disasm_count : pc + available);

    while (pc < end)
    {
        int size = disassemble(pc, out, sizeof(out));
        if (size <= 0)
        {
            if (use_color)
                printf(C_CYAN "%04X: " C_RESET C_DIM ".db $%02X" C_RESET "\n", pc, mem_read(pc));
            else
                printf("%04X: .db $%02X\n", pc, mem_read(pc));
            pc++;
            continue;
        }

        if (show_bytes)
        {
            bytes_str[0] = 0;
            for (int i = 0; i < size; i++)
            {
                char tmp[4];
                snprintf(tmp, sizeof(tmp), "%02X ", mem_read(pc + i));
                strncat(bytes_str, tmp, sizeof(bytes_str) - strlen(bytes_str) - 1);
            }
        }

        if (use_color)
        {
            if (show_bytes)
                printf(C_CYAN "%04X: " C_DIM "%-10s" C_RESET C_YELLOW "%s" C_RESET "\n", pc, bytes_str, out);
            else
                printf(C_CYAN "%04X: " C_RESET C_YELLOW "%s" C_RESET "\n", pc, out);
        }
        else
        {
            if (show_bytes)
                printf("%04X: %-10s %s\n", pc, bytes_str, out);
            else
                printf("%04X: %s\n", pc, out);
        }

        pc += (u16) size;
    }

    return 0;
}
