cmake_minimum_required(VERSION 3.15)
project(ILB_6502 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/tools/disassembler/include)

file(GLOB_RECURSE SRC_FILES src/*/*.c)
set(MAIN_SRCS main.c ${SRC_FILES})
set(DISASM_SRCS tools/disassembler/main.c tools/disassembler/disassembler.c ${SRC_FILES})


add_executable(dis6502 ${DISASM_SRCS})
add_executable(main6502 ${MAIN_SRCS})
