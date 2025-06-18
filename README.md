# Maman 14: Custom Assembler in C

## Course Information
* [cite_start]**Course:** 20465 - C Programming Lab 
* [cite_start]**Assignment:** Maman 14 
* [cite_start]**Semester:** 2025b 
* [cite_start]**Author:** Liad zeltzer
* [cite_start]**ID:** 322205261

## Project Overview

[cite_start]This project is an implementation of a two-pass assembler for a custom assembly language, as specified for the Maman 14 assignment.  [cite_start]The assembler is written in C and is designed to be compiled and run on an Ubuntu system. 

[cite_start]The program takes one or more assembly source files (`.as`) as input.  [cite_start]It first performs a pre-assembly pass to handle and expand any macros.  [cite_start]It then proceeds with a two-pass assembly process to build a symbol table, resolve addresses, and translate the code into a unique machine code format.  [cite_start]The final output consists of an object file (`.ob`), an entries file (`.ent`), and an externals file (`.ext`). 

## Features

* [cite_start]**Pre-Assembler:** Processes and expands macro definitions before the main assembly begins. 
* [cite_start]**Two-Pass Assembler:** Implements the standard two-pass algorithm to handle forward references and build a complete symbol table. 
* [cite_start]**Custom Assembly Language:** Supports the full instruction set of 16 opcodes specified in the project, including `mov`, `cmp`, `add`, `jmp`, and `rts`. 
* [cite_start]**Addressing Modes:** Correctly parses and encodes all four defined addressing modes: Immediate, Direct, Matrix/Index Access, and Direct Register. 
* [cite_start]**Data Directives:** Handles `.data` [cite: 86, 87][cite_start], `.string` [cite: 96][cite_start], and `.mat`  directives to embed data into the machine code image.
* [cite_start]**Modular Code Support:** Manages symbol visibility between different source files using the `.entry`  [cite_start]and `.extern`  directives.
* [cite_start]**Error Reporting:** Performs extensive validation and reports syntax errors found in the source files, including the line number where the error occurred. 
* [cite_start]**Output Generation:** Produces multiple output files (`.ob`, `.ent`, `.ext`) in the specified text-based format. 

## Getting Started

### Prerequisites
* An Ubuntu-based environment.
* The `gcc` compiler and `make` utility. On a fresh Ubuntu system, these can be installed with:
    ```bash
    sudo apt install build-essential
    ```

### Compilation
The project uses a `makefile` for easy compilation. [cite_start]The code is compiled using `gcc` with the required `-Wall -ansi -pedantic` flags. 

To compile the assembler, simply run the `make` command from the root directory of the project:
```bash
make