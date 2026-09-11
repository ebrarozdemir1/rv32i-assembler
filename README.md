# RV32I Assembler

A two-pass assembler written in C that translates RV32I RISC-V assembly instructions into 32-bit machine code and generates memory initialization files.

## Overview

This project implements an assembler for the RV32I instruction set architecture.

The assembler reads an assembly source file, processes labels and symbols, parses instructions and directives, encodes instructions into 32-bit machine code, and generates hexadecimal and memory initialization outputs.

The project was developed in C with a modular structure separating parsing, instruction encoding, symbol management, opcode definitions, and utility functions.

## Features

- Two-pass assembly process
- RV32I instruction encoding
- Label and symbol support
- Instruction parsing
- R-type instruction support
- I-type instruction support
- S-type instruction support
- B-type instruction support
- Assembly directive support
- Hexadecimal machine code generation
- Instruction memory generation
- Data memory generation
- Modular C implementation

## Supported Assembly Directives

The assembler supports the following directives:

- `.text`
- `.data`
- `.org`
- `.word`
- `.byte`
- `.end`

These directives allow the assembly source to define code sections, data sections, memory locations, word values, byte values, and the end of the assembly program.

## Two-Pass Assembly Process

The assembler uses a two-pass approach.

### Pass 1

The first pass analyzes the assembly source and collects labels and symbols together with their corresponding addresses.

This allows the assembler to resolve symbolic references during the second pass.

### Pass 2

The second pass parses the instructions and directives, resolves symbols, encodes the instructions into 32-bit machine code, and generates the output files.

This approach allows forward references to labels to be resolved correctly.

## Instruction Encoding

The assembler converts supported RV32I assembly instructions into their corresponding 32-bit machine code representations.

Instruction fields such as opcode, destination register, source registers, function fields, and immediate values are parsed and placed into the appropriate bit positions according to the instruction format.

The project includes separate modules for instruction parsing and instruction encoding.

## Input and Output

The assembler takes an assembly source file as input.

Example input:

    input.asm

The generated outputs include:

    output.hex
    instr.mem
    data.mem

`output.hex` contains the generated hexadecimal machine code.

`instr.mem` and `data.mem` provide memory initialization data for instruction and data memory usage.

## Project Structure

    rv32i-assembler/
    ├── assembler.c
    ├── assembler.h
    ├── encoder.c
    ├── encoder.h
    ├── parser.c
    ├── parser.h
    ├── symbol_table.c
    ├── symbol_table.h
    ├── opcode_table.c
    ├── opcode_table.h
    ├── utils.c
    ├── utils.h
    ├── main.c
    ├── input.asm
    ├── output.hex
    ├── instr.mem
    ├── data.mem
    ├── README.md
    └── .gitignore

## Compilation

The project can be compiled using a standard C compiler such as GCC.

Example:

    gcc main.c assembler.c encoder.c parser.c symbol_table.c opcode_table.c utils.c -o assembler

After compilation, the generated executable can be used to run the assembler.

The compiled executable is intentionally excluded from the repository through `.gitignore`.

## Example Workflow

A typical assembly workflow is:

    Assembly Source
          |
          v
      Parser
          |
          v
    Symbol / Label Resolution
          |
          v
    Instruction Encoder
          |
          v
    32-bit Machine Code
          |
          +--------> output.hex
          |
          +--------> instr.mem
          |
          +--------> data.mem

## Technologies

- C
- RISC-V
- RV32I
- Assembly Language
- Compiler Construction
- Instruction Encoding
- Data Structures

## Relationship to RISC-V Projects

This assembler can be used as a software tool for generating machine code for RV32I-based systems.

It is also relevant to FPGA and processor projects where RISC-V programs need to be converted from assembly language into machine-readable instruction data.

## Learning Outcomes

This project provided practical experience with:

- RISC-V instruction formats
- Assembly language processing
- Two-pass assembler design
- Symbol table implementation
- Instruction encoding
- Parsing techniques
- Memory initialization formats
- Modular C programming
- Low-level computer architecture concepts

## Author

Ebrar Özdemir

Computer Engineering Student

Sakarya University of Applied Sciences

GitHub: [github.com/ebrarozdemir1](https://github.com/ebrarozdemir1)
