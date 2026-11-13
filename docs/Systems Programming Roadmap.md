# Systems Programming Roadmap: C to C++ in 79 Weeks

Prepared for Akshat Rauthan · Starts mid-November 2026

## How to use this plan

You already know C++ and DSA, so this plan skips beginner material and goes deeper than a typical roadmap: nine stages over 79 weeks (about 18 months at 10–12 hours a week), then optional specialization tracks. The order is deliberate: C first (to see the machine), then C craft and debugging, the operating system, hardware and memory, concurrency, networking, modern C++, performance engineering, and finally a capstone that ties everything together.

Ground rules for every stage:

- Compile with `-Wall -Wextra -Wpedantic -g` and test with `-fsanitize=address,undefined`. Zero warnings is the standard.
- Read man pages (`man 2 read`, `man 7 epoll`) before tutorials. Learning to read them is itself a core skill.
- Keep every project in git with a README, a Makefile or CMakeLists, and tests.
- Write the core of each project yourself. Read reference code only after you are stuck or finished.
- Keep a short engineering journal: what broke, why, and how you debugged it.
- If you slip, extend the stage. Never skip its big project.

## How every stage is organized

Each stage is a ladder. Climb it in this order and do not skip rungs.

1. Modules. A stage has 3 to 5 numbered modules (3.1, 3.2 and so on). Finish one before starting the next.
2. Inside a module, work top to bottom: Learn (an ordered topic list), then Practice (ordered assignments), then the Mini project that combines them.
3. After the last module, build the stage's Big Project in milestone order.
4. Pass the exit test before moving on. If you cannot, repeat the weakest module.

Weekly rhythm at 10–12 hours: about 4 hours learning, 3 hours practice, 4 hours on the project, 30 minutes of review and journal. If you can spend more time, finish sooner rather than adding stages.

Book editions and course pages change, so check the current edition or link before you buy or enroll. Resources in each stage are listed in the order you will use them.

## Timeline at a glance

Nine stages take you from your first C program to a durable network server in 79 weeks, from mid-November 2026 to late May 2028.

| Stage | Weeks | Theme | Big project | Exit gate |
| --- | --- | --- | --- | --- |
| 1 | 1–7 | C foundations and toolchain | Unix utilities + libds | Diagnose any memory bug with ASan and gdb |
| 2 | 8–12 | C craft: design, testing, debugging | minijson parser + jq-lite CLI | Fuzz-clean library with tests and CI |
| 3 | 13–22 | Unix systems programming | mysh job-control shell | Explain fork, exec, pipe and signal flow end to end |
| 4 | 23–32 | Computer systems and memory | mymalloc allocator | Read assembly and predict cache behaviour |
| 5 | 33–40 | Concurrency | cpool thread pool + concurrent map | TSan-clean code that scales with cores |
| 6 | 41–50 | Networking and I/O at scale | mini-httpd on epoll | 10,000 connections with measured numbers |
| 7 | 51–59 | Modern C++ core | C++20 port of mysh or mini-httpd | No raw owning pointers, clang-tidy clean |
| 8 | 60–67 | Advanced C++ and performance engineering | libfast toolkit | Two components beat std baselines |
| 9 | 68–79 | Capstone | Persistent key-value server | Survives random kill -9 tests, fully documented |

## Stage 1: C Foundations and Toolchain (Weeks 1–7)

This stage gives you an accurate mental model of memory and a working C toolchain, so you can write C without leaning on C++ habits.

### Stage goals

- Write correct C with no classes, references, templates or RAII to lean on.
- Draw the stack, heap and pointer relationships of any snippet from memory.
- Run the full build, debug and sanitizer workflow without thinking about it.

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

## Stage 2: C Craft: Design, Testing, Debugging (Weeks 8–12)

This stage turns C that merely works into C you can maintain: clean APIs, real tests, fuzzing and fast debugging.

### Stage goals

- Design modular C libraries with opaque types and consistent error handling.
- Test, fuzz and statically analyze everything you write.
- Debug unfamiliar crashes methodically with gdb and sanitizers.

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

## Stage 3: Unix Systems Programming (Weeks 13–22)

This stage teaches you to talk to the kernel directly, and ends with a shell that exercises nearly every concept in it.

### Stage goals

- Use system calls directly and know roughly what each one costs.
- Understand processes, file descriptors, signals, pipes and terminals well enough to build a shell.
- Use strace and /proc to see what any program is really doing.

### Big Project 3: mysh, a job-control shell (Weeks 20–22)

Build in this order:

1. A REPL that runs one simple command with fork, exec and wait
2. Tokenizer with quotes and escapes
3. Builtins: `cd`, `exit`, `export`, `pwd`
4. Redirection: `<`, `>`, `>>`, `2>`
5. Pipelines of any length
6. Variable expansion and `$?`
7. Background jobs with `&` and SIGCHLD reaping
8. Job control: process groups, terminal handoff, `fg`, `bg`, `jobs`, Ctrl-C and Ctrl-Z
9. Stretch: `&&`, `||`, globbing, history and line editing, script files
10. A test script comparing mysh with bash on at least 50 cases

Expectations: 2,000–3,000 lines; zero zombie processes; no leaked descriptors (check with lsof); clean under ASan and UBSan; built on libcore and libds where they fit.

Done when: you can run a three-stage pipeline, suspend it with Ctrl-Z, resume it in the background, bring it back to the foreground, and the terminal behaves correctly throughout.

### Focus areas

- Check the return value of every system call (write small wrappers)
- Async-signal-safety, and why most functions are unsafe inside handlers
- File descriptor hygiene: close what you do not need and set close-on-exec
- Partial reads and writes, and EINTR

### Resources, in order of use

1. The Linux Programming Interface by Michael Kerrisk: the chapters on file I/O, processes, signals, pipes and memory mappings, in the order of the modules
2. Operating Systems: Three Easy Pieces (free): the virtualization section alongside Modules 3.2 and 3.3
3. man7.org man pages (`man 2 open`, `man 7 signal`, `man 7 pipe`)
4. Stephen Brennan's blog post Write a Shell in C, as a gentle read before Big Project 3
5. Beej's Guide to Unix IPC (free)
6. MIT 6.S081 lectures on YouTube (the early OS interface lectures)
7. Advanced Programming in the UNIX Environment by Stevens and Rago, as a second reference
8. Optional: Linux System Programming by Robert Love

### Exit test

You pass when you can do all three:

1. Explain step by step what happens between typing `ls | wc -l` and seeing the output
2. Use strace to show which syscalls a program makes and why
3. Write a correct SIGCHLD handler with no race conditions

## Stage 4: Computer Systems and Memory (Weeks 23–32)

This stage connects your C code to the machine code and hardware that run it, and ends with you writing your own memory allocator.

### Stage goals

- Connect any line of C to the machine code and hardware behind it.
- Reason about performance through caches, locality and the memory hierarchy.
- Understand linking and loading well enough to debug symbol and ABI problems.

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

## Stage 5: Concurrency (Weeks 33–40)

This stage teaches you to write multithreaded code whose correctness you can argue, not just hope for, and ends with a reusable thread pool library.

### Stage goals

- Write multithreaded code and be able to explain why it is correct.
- Know when to reach for mutexes, condition variables, semaphores or atomics.
- Find races and deadlocks with ThreadSanitizer and disciplined design.

### Big Project 5: cpool, a thread pool library (Weeks 39–40)

Build in this order:

1. Bounded MPMC task queue (mutex and condition variables)
2. Worker threads with start, stop and drain
3. Futures: submit a function and wait for its result
4. `parallel_for` that splits a range across workers
5. A striped concurrent hash map
6. Stress tests and TSan runs in CI
7. Scaling benchmarks and a report
8. Stretch: work stealing with per-worker deques

Expectations: 1,200–2,000 lines; TSan clean; no deadlock in a 10-minute stress test; near-linear speedup on CPU-bound tasks up to your physical core count; clear docs on the thread-safety guarantee of each function.

Done when: the tests pass 100 times in a row, and your report shows scaling graphs and explains where scaling stops.

### Focus areas

- Write the invariant a lock protects in a comment before writing the code
- Always wait on a condition in a loop with a predicate
- Run every concurrent program under TSan
- Reason in happens-before, not in it worked on my machine

### Resources, in order of use

1. The Linux Programming Interface: the chapters on threads, synchronization and POSIX semaphores
2. Operating Systems: Three Easy Pieces (free): the concurrency section
3. The Little Book of Semaphores by Allen Downey (free)
4. Preshing on Programming (blog): the lock-free and memory ordering articles
5. Herb Sutter's talk atomic Weapons
6. Is Parallel Programming Hard, And, If So, What Can You Do About It? by Paul McKenney (free)
7. Optional: The Art of Multiprocessor Programming by Herlihy and Shavit
8. Reference: `pthreads(7)`, `futex(2)` and the ThreadSanitizer documentation

### Exit test

You pass when you can do all three:

1. Find a planted race and a planted deadlock using only TSan and reasoning
2. Explain acquire vs release with a concrete example
3. Show a scaling plot of your own code and explain its shape

## Stage 6: Networking and I/O at Scale (Weeks 41–50)

This stage takes you from your first socket to an event-driven HTTP server whose performance you can measure and explain.

### Stage goals

- Understand the TCP/IP stack well enough to debug with tcpdump and Wireshark.
- Build network servers with non-blocking I/O and an event loop.
- Measure server performance honestly: throughput, latency percentiles and bottlenecks.

### Big Project 6: mini-httpd (Weeks 49–50)

Build in this order:

1. Accept loop on `evloop` plus the incremental parser
2. Static file serving with MIME types
3. Keep-alive and idle timeouts
4. Worker pool (cpool) for blocking disk work
5. Range and conditional requests
6. Access log, config flags, graceful shutdown on SIGINT
7. Benchmark with wrk and capture a flame graph
8. Optimize the top bottleneck and re-measure
9. Stretch: sendfile, reverse proxy mode, TLS through OpenSSL

Expectations: 2,500–4,000 lines; clean under TSan and ASan; a fuzzed request parser; 10,000 concurrent idle connections handled; a README with wrk results (requests per second and latency percentiles).

Done when: you can point to the top bottleneck in your flame graph, explain it, and show one measured optimization.

### Focus areas

- Handle partial reads and writes and EAGAIN correctly everywhere
- One state machine per connection; no hidden blocking calls
- Limits on everything: header size, body size, connections, time
- Benchmark with real tools and report percentiles, not just averages

### Resources, in order of use

1. Beej's Guide to Network Programming (free)
2. The Linux Programming Interface: the sockets, I/O multiplexing and epoll chapters
3. Computer Networking: A Top-Down Approach by Kurose and Ross, with Kurose's lecture videos, for theory
4. UNIX Network Programming, Volume 1 by Stevens, as a reference
5. `man 7 epoll`, `man 7 socket`, `man 7 tcp`, `man 7 ip`
6. The C10K problem by Dan Kegel (classic article)
7. RFC 9110 and RFC 9112 (HTTP semantics and HTTP/1.1)
8. Build Your Own Redis with C/C++ at build-your-own.org: the event loop chapters
9. Optional: TCP/IP Illustrated, Volume 1

### Exit test

You pass when you can do all three:

1. Explain why epoll scales better than poll and when edge-triggered mode bites
2. Read a packet capture and explain a retransmission
3. Show wrk numbers for your server and explain its bottleneck

## Stage 7: Modern C++ Core (Weeks 51–59)

This stage shows you how C++ automates the patterns you wrote by hand in C, and ends with you porting an earlier system to idiomatic C++20.

### Stage goals

- Write idiomatic C++20 that is as fast as the C equivalent and much harder to misuse.
- Express ownership and lifetimes in types instead of comments.
- Know what each abstraction costs at the machine level.

### Big Project 7: cppsys, a C++20 port of mysh or mini-httpd (Weeks 58–59)

Build in this order:

1. RAII layer for descriptors, sockets or processes
2. Port the core logic
3. Replace hand-rolled containers with standard ones
4. Choose and document an error handling policy (exceptions or expected-style results)
5. Run clang-tidy with the C++ Core Guidelines checks and fix the findings
6. Run ASan, UBSan and TSan
7. Compare with the C version: lines of code, bugs found, speed

Expectations: no raw owning pointers; no manual `new` or `delete`; a CMake build with tests; a short comparison write-up.

Done when: performance is within about 10 percent of the C version, and the write-up states what the abstractions bought you and what they cost.

### Focus areas

- Ownership and lifetimes expressed in types
- Zero-cost abstractions: know exactly what each one costs
- Avoid writing C with classes, and avoid over-engineering
- Read compiler errors patiently; template errors are a skill

### Resources, in order of use

1. A Tour of C++ by Bjarne Stroustrup (current edition): read it first for the whole picture
2. learncpp.com for gaps, following the order of the modules
3. The Cherno's C++ series on YouTube for visual walkthroughs
4. Effective Modern C++ by Scott Meyers, alongside Module 7.2
5. The C++ Core Guidelines (isocpp.github.io) as your style reference
6. CppCon Back to Basics talks and Jason Turner's C++ Weekly on YouTube
7. cppreference.com and Compiler Explorer
8. Optional: C++ Templates: The Complete Guide, and C++20: The Complete Guide by Nicolai Josuttis

### Exit test

You pass when you can do all three:

1. Explain, for any class you wrote, which of the five special members it needs and why
2. Show that your `vector` moves instead of copies when it grows
3. Explain what a `shared_ptr` costs compared with a `unique_ptr`

## Stage 8: Advanced C++ and Performance Engineering (Weeks 60–67)

This stage combines everything so far into performance work you can trust: C++20 concurrency, cache-aware design, rigorous benchmarking, and a toolkit of fast components.

### Stage goals

- Port and improve your earlier concurrency work with C++20 facilities.
- Design data layouts and allocation strategies around cache behaviour.
- Benchmark and profile with enough rigor that your numbers can be trusted.

### Big Project 8: libfast, a high-performance C++ toolkit (Weeks 66–67)

Build in this order:

1. Project skeleton from `project-template`
2. Arena and pool allocators
3. SPSC ring buffer
4. Thread pool (from `cppool`)
5. Asynchronous logger built on the ring buffer
6. Benchmarks against naive standard-library equivalents
7. Documentation of complexity, memory-order choices and tradeoffs
8. CI with sanitizers and a benchmark job
9. Stretch: bounded MPMC queue, work stealing, `pmr` compatibility throughout

Expectations: C++20; unit tests with GoogleTest or Catch2; a Google Benchmark suite; clean under TSan and ASan; a short design note per component.

Done when: at least two components measurably beat naive standard-library equivalents in documented benchmarks, and you can explain why in terms of cache behaviour, allocation counts or contention.

### Focus areas

- Measure, then explain, then optimize
- Count allocations and cache misses before micro-tweaking instructions
- Report latency percentiles, not only averages
- Write down the reasoning behind every memory-order choice

### Resources, in order of use

1. C++ Concurrency in Action by Anthony Williams (2nd edition)
2. Preshing on Programming for lock-free design
3. CppCon talks: Mike Acton on data-oriented design, Chandler Carruth on performance, Matt Godbolt on compilers
4. The Art of Writing Efficient Programs by Fedor Pikus
5. Performance Analysis and Tuning on Modern CPUs by Denis Bakhvalov (free)
6. Systems Performance by Brendan Gregg
7. Optional: Daniel Lemire's and Travis Downs's blogs for low-level performance case studies

### Exit test

You pass when you can do all three:

1. Show a benchmark with warmup, variance reporting and CPU pinning
2. Demonstrate false sharing with a measurement
3. Explain every memory order used in your SPSC queue

## Stage 9: Capstone: Persistent Networked Key-Value Store (Weeks 68–79)

In this final stage you build one durable key-value server, a small Redis and LevelDB hybrid, from the components you made in earlier stages.

### Stage goals

- Integrate allocators, event loops, thread pools and parsers into one substantial system.
- Learn crash consistency by breaking your own database on purpose.
- Produce portfolio-grade documentation, benchmarks and a postmortem.

### Capstone requirements and milestones

Build in this order:

1. Log format and recovery (Module 9.1)
2. In-memory server with the core commands (Module 9.2)
3. Durable, concurrent server (Module 9.3)
4. Benchmarks and optimization (Module 9.4)
5. Final documentation, postmortem and release

Required commands: GET, SET, DEL, EXISTS, EXPIRE, TTL, INCR, SCAN and INFO, plus a durability policy flag and a snapshot command.

Stretch: an LSM tree with SSTables and bloom filters; replication by log shipping; MULTI and EXEC transactions; compatibility with redis-cli.

Expectations: 4,000–6,000 lines of C++20; built on your own `evloop`, `cpool` and `libfast` components where they fit; CI with sanitizers; a fuzzed protocol parser; a design document; published benchmark results; a postmortem of at least three real bugs.

Done when: no acknowledged write is lost across 1,000 random `kill -9` crashes at your chosen durability level, a benchmark of at least a million operations shows stable throughput and p99 latency in your report, and you can defend each design decision in an interview-style walkthrough.

### Focus areas

- Define what must be true after recovery before you write any code
- Test crashes constantly, not at the end
- Keep a decision log: what you chose, what you rejected, and why
- Write the postmortem as you hit bugs, not afterwards

### Resources, in order of use

1. Build Your Own Redis and Build Your Own Database at build-your-own.org
2. Database Internals by Alex Petrov: the storage engine chapters
3. Designing Data-Intensive Applications by Martin Kleppmann: the chapters on storage engines and replication
4. The Bitcask paper, a clean log-structured hash table design
5. CMU 15-445 Database Systems lectures by Andy Pavlo on YouTube
6. Source code to read: Redis (event loop and dict), LevelDB, and the SQLite documentation on its file format and WAL
7. Optional: the original Log-Structured Merge-Tree paper by O'Neil et al.

### Final exit test

You have finished the plan when you can do all three:

1. Run the crash test and show the recovered state matches your model
2. Present the design document and benchmark results
3. Describe three bugs from your postmortem and how you found each

## After the capstone: specialization tracks

Pick one track after Week 79 and go deep for three to four months; each builds directly on stages you have finished.

| Track | Start with | Capstone idea |
| --- | --- | --- |
| Operating systems | MIT 6.S081 (xv6 labs), then Linux Kernel Development by Robert Love | Add a feature to xv6 such as copy-on-write fork or a simple file system, then write a Linux kernel module |
| High-performance networking | Learning eBPF by Liz Rice; the io\_uring man pages | An io\_uring server benchmarked against your epoll mini-httpd |
| Databases and storage engines | CMU 15-445 projects (BusTub); Database Internals by Alex Petrov | An LSM-tree engine with compaction and bloom filters, or a B-tree with a page cache |
| Compilers and runtimes | Crafting Interpreters (the clox half); Writing a C Compiler by Nora Sandler; the LLVM Kaleidoscope tutorial | A bytecode VM with a garbage collector, or a C-subset compiler targeting x86-64 |
| Embedded and firmware | Making Embedded Systems by Elecia White; the Raspberry Pi Pico C SDK documentation | A bare-metal device driver plus a small cooperative scheduler |
| Security | pwn.college (free); Hacking: The Art of Exploitation by Jon Erickson | Exploit intentionally vulnerable binaries, then harden mysh and mini-httpd against the same classes of bug |

## Habits that make the difference

- Code more than you read. A week with no code did not count.
- Do a 30-minute weekly review: what you built, what confused you, what is next.
- Put every project on GitHub with a clear README, build instructions and real benchmark numbers.
- Reuse your own libraries (libds, libcore, evloop, cpool, libfast) in later stages so the stack compounds.
- Read real code regularly: Redis, SQLite and parts of the Linux kernel, about one file a week.
- When stuck for over an hour, reread the man page, then write the question down precisely before asking anyone.
