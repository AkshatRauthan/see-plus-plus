## Stage 1: C Foundations and Toolchain (Weeks 1–7)

This stage gives you an accurate mental model of memory and a working C toolchain, so you can write C without leaning on C++ habits.

### Stage goals

- Write correct C with no classes, references, templates or RAII to lean on.
- Draw the stack, heap and pointer relationships of any snippet from memory.
- Run the full build, debug and sanitizer workflow without thinking about it.

### Module 1.1: Toolchain and the shape of a C program (Week 1)

**Learn, in this order**

1. Linux dev setup: shell basics, git, an editor with clangd
2. The four compile phases: preprocess, compile, assemble, link (`gcc -E`, `-S`, `-c`)
3. Flags: `-Wall -Wextra -Wpedantic -g`, `-O0` vs `-O2`
4. Multi-file programs and Makefiles with automatic header dependencies (`-MMD`)
5. gdb basics: breakpoints, backtrace, print, watch, step and next

**Practice, in this order**

1. Take a hello.c through each compile phase by hand and open every output file
2. Split a program into three files with a Makefile
3. Debug a deliberate segfault in gdb using only backtrace, print and watch

**Mini project:** `calc`, a command-line expression evaluator (+, -, \*, / and parentheses) split into lexer.c, parser.c and main.c.

### Module 1.2: Types, functions, stdio and errors (Week 2)

**Learn, in this order**

1. Fixed-width integers (`stdint.h`), `sizeof`, integer promotion and conversion
2. Signed overflow as undefined behaviour; unsigned wraparound
3. Bitwise operators, masks, shifts; endianness
4. Functions, call by value, recursion, `static`
5. stdio: `printf` formats, `fgets` vs `scanf`, buffering
6. Files: `fopen`, `fread`, `fwrite`, `fseek`; errors: `errno`, `perror`, exit codes
7. `argc`, `argv` and `getopt`

**Practice, in this order**

1. Set, clear, toggle and test bits; popcount; power-of-two test
2. Trigger signed overflow under UBSan and read the report
3. Write itoa and atoi with full error handling
4. File copy and hexdump with every error checked
5. A small CLI that parses flags with getopt

**Mini project:** `bitview`, which prints the bits of an int and the sign, exponent and mantissa fields of a float.

### Module 1.3: Pointers, arrays and strings (Week 3)

**Learn, in this order**

1. Addresses, `&`, `*`, pointer types and `void *`
2. Pointer arithmetic; arrays decaying to pointers
3. Pointers to pointers; const placement (`const char *` vs `char *const`)
4. C strings and the null terminator; the `string.h` functions and their traps
5. Function pointers and callbacks (`qsort`)

**Practice, in this order**

1. Reimplement strlen, strcpy, strcmp, strchr, memcpy and memmove
2. Reverse a string in place; split a string on a delimiter into a `char **`
3. Write a generic swap with `memcpy`
4. Sort an array of structs with `qsort` and a comparator
5. Draw the memory diagram for each program above on paper

**Mini project:** `wordfreq`, which reads text, counts word frequencies and prints the top k.

### Module 1.4: Memory, structs and ownership (Weeks 4–5)

**Learn, in this order**

1. Stack frames and object lifetimes
2. `malloc`, `calloc`, `realloc`, `free`; checking for NULL
3. Bug classes: leak, dangling pointer, double free, use-after-free, buffer overflow
4. Ownership conventions: who allocates, who frees, who only borrows
5. Structs, padding, alignment, `offsetof`; unions, enums, bit fields
6. Headers vs sources, opaque types, include guards
7. ASan, UBSan and Valgrind

**Practice, in this order**

1. Trigger each bug class on purpose and explain the sanitizer report line by line
2. Dynamic array (vector) with a generic void pointer API
3. Singly linked list with iterator-style traversal
4. Open-addressing hash map with resizing
5. Binary heap (priority queue) built on your vector
6. Print the layout and padding of five different structs

**Mini project:** `libds`, the four containers behind a clean header API, with assert-based tests that run under ASan.

### Big Project 1: Unix utilities suite on libds (Weeks 6–7)

Build in this order:

1. `mycat`
2. `mywc`
3. `myhexdump` (xxd-style output)
4. `mygrep` with -n, -i and -v (fixed strings first)
5. `mytail` with -n and -f
6. `mydu` (recursive directory sizes using stat and opendir)

Expectations: about 1,500–2,500 lines; zero warnings; clean under ASan, UBSan and Valgrind; tests comparing output with the GNU tools; large files, binary data, missing files and permission errors handled; a README with usage.

Done when: you can explain every malloc and free pair, `mygrep` runs within roughly 5–10x of GNU grep on a 1 GB file, and a stranger can build everything with one `make`.

### Focus areas

- Undefined behaviour and why compilers exploit it
- For every allocation, who owns it and who frees it
- Draw memory diagrams before writing pointer-heavy code
- Learn gdb properly now: watchpoints, the `x` command, tbreak

### Resources, in order of use

1. Beej's Guide to C (free) for a quick language start
2. C Programming: A Modern Approach by K.N. King: skim the early chapters, read pointers through advanced topics
3. Jacob Sorber on YouTube for short topic videos
4. CS50 lectures on memory and pointers for refreshers
5. Modern C by Jens Gustedt (free): read alongside Module 1.4
6. cppreference.com (C section) and Compiler Explorer (godbolt.org)
7. Exercism C track for extra drills

### Exit test

You pass when you can do all four without notes:

1. Read an ASan report and point to the bug
2. Explain why `INT_MAX + 1` on a signed int is undefined
3. Draw the memory of a linked list of structs after three inserts and one free
4. Write a Makefile for a four-file project from scratch