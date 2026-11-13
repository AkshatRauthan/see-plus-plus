## Stage 2: C Craft: Design, Testing, Debugging (Weeks 8–12)

This stage turns C that merely works into C you can maintain: clean APIs, real tests, fuzzing and fast debugging.

### Stage goals

- Design modular C libraries with opaque types and consistent error handling.
- Test, fuzz and statically analyze everything you write.
- Debug unfamiliar crashes methodically with gdb and sanitizers.

### Module 2.1: Modular C design (Week 8)

**Learn, in this order**

1. API design: headers as contracts, opaque pointers, naming conventions
2. Error handling patterns: return codes, out parameters, `goto cleanup`
3. Ownership patterns: arenas (region allocation) and string builders
4. Macros done safely: `static inline`, X-macros, `_Generic`, variadic functions
5. Coding style and `clang-format`; the Linux kernel coding style as a reference

**Practice, in this order**

1. Refactor `libds` to opaque types with `goto cleanup` error paths
2. Write an arena allocator (bump allocation with block chaining)
3. Write a string builder with amortized O(1) append
4. Write a logging macro using `__FILE__`, `__LINE__` and varargs

**Mini project:** `libcore`, containing the arena, string builder, logging and a small error type that later projects reuse.

### Module 2.2: Testing, debugging and analysis (Weeks 9–10)

**Learn, in this order**

1. Unit testing in C: asserts, a minimal test runner, or Unity
2. gdb in depth: conditional breakpoints, watchpoints, core dumps, `x`, `info frame`
3. Valgrind memcheck and massif; sanitizer options
4. Static analysis: `-fanalyzer`, clang-tidy, cppcheck
5. Code coverage with gcov
6. Fuzzing basics with libFuzzer or AFL++: corpus, crashers, minimization
7. CI: GitHub Actions running tests under sanitizers

**Practice, in this order**

1. Add tests to libds and libcore until you reach 80 percent line coverage
2. Fix three deliberately buggy programs using only gdb
3. Fuzz one of your own string-handling functions until it crashes, then fix it
4. Wire GitHub Actions to build, test and run sanitizers on every push

**Mini project:** `bug-zoo`, ten tiny programs with ten different bug classes, plus a write-up of which tool catches each one and how.

### Module 2.3: Parsing and text processing (Week 11)

**Learn, in this order**

1. Lexing vs parsing; recursive descent
2. The JSON grammar (RFC 8259) and its edge cases
3. UTF-8 encoding and validation
4. Number parsing pitfalls: `strtod`, overflow, locale
5. Error reporting with line and column

**Practice, in this order**

1. A JSON tokenizer with position tracking
2. A recursive descent parser that builds a tree in an arena
3. A pretty printer and a compact serializer
4. Path queries such as `.a.b[0]`

**Mini project:** the tokenizer-parser pair itself; it becomes the core of Big Project 2.

### Big Project 2: minijson and jq-lite (Weeks 11–12)

Build in this order:

1. Tokenizer
2. Parser into an arena-backed tree
3. Serializer (compact and pretty)
4. Path query engine
5. `jq-lite` CLI with stdin and file input and meaningful exit codes
6. Fuzz harness plus the JSONTestSuite cases
7. Benchmark against a mature C JSON library

Expectations: about 1,500–2,500 lines; a documented public header; tests at 80 percent coverage; zero crashes after one hour of fuzzing; CI green.

Done when: you handle the accept and reject cases the RFC requires, throughput lands within roughly 2–3x of a mature library such as cJSON, and someone else can use it from the header and README alone.

### Focus areas

- API clarity: what each function promises and who owns what
- Write a failing test for every bug you find, then fix it
- Treat every compiler warning and sanitizer report as a failure
- Fuzz early, on any code that parses input

### Resources, in order of use

1. Effective C by Robert Seacord (modern, security-minded C)
2. Modern C by Jens Gustedt (continue from Stage 1)
3. SEI CERT C Coding Standard (free online)
4. Beej's Quick Guide to GDB (free) and the gdb manual
5. Crafting Interpreters (free online): the scanning and parsing chapters
6. AFL++ and libFuzzer documentation
7. The Linux kernel coding style document at kernel.org

### Exit test

You pass when you can do all three:

1. Pick any function in your code and state who owns its inputs and outputs
2. Reproduce a fuzzer-found crash in gdb and fix it
3. Show coverage and sanitizer results in CI for both libraries
