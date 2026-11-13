## Stage 4: Computer Systems and Memory (Weeks 23–32)

This stage connects your C code to the machine code and hardware that run it, and ends with you writing your own memory allocator.

### Stage goals

- Connect any line of C to the machine code and hardware behind it.
- Reason about performance through caches, locality and the memory hierarchy.
- Understand linking and loading well enough to debug symbol and ABI problems.

### Module 4.1: Data and machine-level programming (Weeks 23–25)

**Learn, in this order**

1. Two's complement, bit-level tricks, IEEE 754 floating point and rounding
2. x86-64 registers, addressing modes, common instructions
3. Control flow in assembly: conditions, loops, switch jump tables
4. Procedures: stack frames and the System V AMD64 calling convention
5. Arrays, structs and unions in memory; alignment
6. Reading compiler output at `-O0` vs `-O2` (Compiler Explorer, `objdump -d`)
7. Stack buffer overflows, canaries, ASLR, NX

**Practice, in this order**

1. CS:APP Data Lab
2. CS:APP Bomb Lab
3. CS:APP Attack Lab
4. Annotate the assembly of one function at `-O0`, `-O2` and `-O3` and explain each difference
5. Write the same function in C and in hand-written assembly, and call one from the other

**Mini project:** `asm-playground`, a C program that calls hand-written assembly for sum, strlen and memcpy and benchmarks them against libc.

### Module 4.2: Linking, loading and ELF (Weeks 26–27)

**Learn, in this order**

1. Object files, symbols, relocations
2. Static libraries (archives) and the link-order problem
3. ELF structure: sections vs segments, headers
4. Shared libraries, position-independent code, PLT and GOT, lazy binding
5. `dlopen`, `dlsym`, `LD_PRELOAD`
6. Process startup: `_start`, crt files, libc initialization
7. Symbol visibility; API vs ABI compatibility

**Practice, in this order**

1. Walk a hello binary with `readelf`, `objdump` and `nm`
2. Build the same code as a static and as a shared library and compare them
3. Write an `LD_PRELOAD` library that logs `malloc`, `free` and `open` calls
4. Build a small plugin system with `dlopen`
5. Parse an ELF header by hand using a C struct

**Mini project:** `elfpeek`, a tiny readelf that prints headers, sections and symbols.

### Module 4.3: CPU, caches and performance (Weeks 28–29)

**Learn, in this order**

1. Pipelines, branch prediction, instruction-level parallelism
2. Memory hierarchy: cache lines, associativity, replacement
3. Locality, blocking and tiling
4. Prefetching, false sharing, TLB and huge pages
5. Microbenchmarking pitfalls: warmup, dead-code elimination, timers
6. Profiling workflow: `perf stat`, `perf record`, flame graphs, cachegrind

**Practice, in this order**

1. CS:APP Cache Lab (the simulator, then the transpose optimization)
2. Matrix multiply: naive vs loop-reordered vs tiled
3. Sorted vs unsorted data behind a branch; then a branchless rewrite
4. Array of structs vs struct of arrays
5. Pointer-chasing latency across working sets from 4 KB to 1 GB

**Mini project:** `memlat`, which plots latency against working-set size and shows your CPU's L1, L2, L3 and DRAM steps.

### Module 4.4: Dynamic memory allocation (Week 30)

**Learn, in this order**

1. Allocator goals: throughput, utilization, locality
2. Internal and external fragmentation
3. Implicit free lists, boundary tags, coalescing
4. Explicit and segregated free lists, size classes
5. `brk` and `sbrk` vs `mmap`
6. Arena, pool and slab allocators

**Practice, in this order**

1. A bump allocator
2. A fixed-size pool allocator
3. A first-fit free-list allocator with splitting
4. Add coalescing and a heap consistency checker

**Mini project:** `pool-arena`, reusable pool and arena allocators with benchmarks against malloc.

### Big Project 4: mymalloc (Weeks 31–32)

Build in this order:

1. Trace file format and a replay harness
2. Heap consistency checker
3. Implicit free list with first fit
4. Splitting and coalescing
5. Explicit free list with a LIFO policy
6. Segregated free lists
7. In-place `realloc`, and `calloc`
8. `mmap` for large blocks
9. Thread safety with one global lock
10. Build as a shared library and run real programs under `LD_PRELOAD`
11. Benchmark against glibc malloc and write the report

Expectations: 1,000–1,800 lines; 16-byte alignment; the checker passes after every operation in debug mode; a one-page design report with tradeoffs and graphs.

Done when: it passes all traces, reaches throughput within roughly 2–3x of glibc with utilization above 70 percent on your traces, and runs a real program (for example the sqlite3 shell) under preload.

### Focus areas

- Reading assembly fluently, even if you never write much of it
- Thinking in cache lines and locality
- Measure first, optimize second; never guess where the time goes
- Heap invariants: write the checker before the allocator

### Resources, in order of use

1. Computer Systems: A Programmer's Perspective by Bryant and O'Hallaron, following its chapters on data representation, machine-level programming, the memory hierarchy, linking, virtual memory and dynamic memory allocation
2. CMU 15-213 lecture recordings on YouTube, matched to those chapters
3. The CS:APP student labs at csapp.cs.cmu.edu (Data, Bomb, Attack, Cache, Malloc)
4. What Every Programmer Should Know About Memory by Ulrich Drepper (the caches and virtual memory sections)
5. Compiler Explorer and Matt Godbolt's talks on what the compiler does for you
6. Brendan Gregg's pages on perf and flame graphs
7. Optional depth: Agner Fog's optimization manuals, Hacker's Delight by Henry Warren, Computer Architecture: A Quantitative Approach

### Exit test

You pass when you can do all three:

1. Read the compiler output of a small function and predict its performance behaviour
2. Explain why row-major traversal beats column-major and show the measurement
3. Explain what the dynamic linker does the first time a program calls `printf`
