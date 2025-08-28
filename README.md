# 6502Toolkit – Disassembly, Emulation, and More

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

**6502Toolkit** is my first disassembler.  

It is designed with a **portable and modular architecture**.  
The goal is to provide a solid foundation that can be reused to build multiple tools (disassembler, assembler, emulator, debugger) without rewriting the core logic.  

---

## Core Modules

- **CPU**  
  Contains the full instruction set architecture definitions: registers, opcodes, addressing modes.  

- **Memory**  
  Provides a simple memory interface (`read`, `write`, `load_file`).  

- **Stack**  
  Implemented for future use in the emulator.  

---

## Tools

- **Disassembler** → Disassembler for 6502 machine code, implemented using the **linear sweep algorithm**.  
- **Emulator, Debugger, Assembler** → Planned, but not implemented yet.  

---

In this project, I created a Python script (`op_gen/main`) to automate scraping and generating the C opcode table directly.  
So instead of copying everything one by one, I can automate the process and finish this step in just one second.


## Why this Design?

- **Portability** → Any tool can reuse the same CPU, Memory, and Stack implementations.  
- **Single Responsibility** → Each module is responsible for one thing only, which helps when improving, adding, or refactoring code.  
- **Extensibility** → Easy to add new tools on top of the foundation.  

This architecture makes the project **scalable**, allowing it to grow from a simple disassembler into a full 6502 toolkit.  

---

## References

- [Obelisk 6502 Guide](https://www.nesdev.org/obelisk-6502-guide/) – For CPU architecture  
- [Single Responsibility Principle](https://en.wikipedia.org/wiki/Single-responsibility_principle)  
---

## Notes

Right now, some modules are very simple. For example:  

- The **CPU module** is not yet fully portable.  
- A proper CPU execution pipeline (fetch → decode → execute) is not implemented inside the CPU module itself, but instead directly in the disassembler tool.  

This is temporary — the plan is to move the pipeline into the CPU module in the future so that it can be reused across the emulator, debugger, and assembler.  

---

## Build & Usage

Make sure you have **GCC, CMake, and Make** installed.  

```bash
# Create a separate build folder (to keep source code clean)
mkdir build
cd build

# Configure the project with CMake
cmake ..

# Build the project
make

# The executables will be available in: build/bin
```

---

## My Blog

👉 [https://0xilovebits.github.io](https://0xilovebits.github.io)

---

## Note

This README was originally written by me.  
Since my English level is not very strong, I used AI assistance to **correct grammar and spelling mistakes only**.  
All the content, design decisions, and ideas are my own.
