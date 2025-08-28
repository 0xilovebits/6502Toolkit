#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define C_RESET "\x1b[0m"
#define C_DIM "\x1b[2m"
#define C_GREEN "\x1b[32m"
#define C_CYAN "\x1b[36m"
#define C_YELLOW "\x1b[33m"
#define C_MAGENTA "\x1b[35m"

static void print_header(void)
{
    printf(C_CYAN "== ILoveBits 6502 Toolkit ==\n" C_RESET);
    printf(C_DIM "Status: " C_RESET C_YELLOW "Under Development" C_RESET "\n");
    printf("Available tools: " C_GREEN "disassembler (dis6502)" C_RESET "\n");
    printf("More coming soon: assembler, emulator, debugger...\n\n");
}


int main(void)
{
    print_header();
    printf("Welcome to ILoveBits 6502 toolkit.\n");
    printf("Main CLI is minimal for now, check " C_GREEN "/tools" C_RESET " for the disassembler.\n\n");
    printf(C_DIM "Tip: run " C_RESET C_YELLOW "dis6502 <bin> [load hex] [start hex] [count]" C_RESET C_DIM " to disassemble.\n" C_RESET);
    return 0;
}
