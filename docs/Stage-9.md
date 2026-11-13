## Stage 9: Capstone: Persistent Networked Key-Value Store (Weeks 68–79)

In this final stage you build one durable key-value server, a small Redis and LevelDB hybrid, from the components you made in earlier stages.

### Stage goals

- Integrate allocators, event loops, thread pools and parsers into one substantial system.
- Learn crash consistency by breaking your own database on purpose.
- Produce portfolio-grade documentation, benchmarks and a postmortem.

### Module 9.1: Storage engine fundamentals (Weeks 68–70)

**Learn, in this order**

1. What `fsync` guarantees; the page cache and torn writes
2. Write-ahead logging and crash recovery
3. Checksums (CRC32) and record framing
4. In-memory indexes: hash table and skip list
5. Snapshots and log compaction
6. LSM trees and B-trees at a conceptual level

**Practice, in this order**

1. An append-only log with CRC checks that detects a torn last record
2. A crash-test harness that kills your process with `kill -9` at random points
3. A skip list with ordered iteration
4. Snapshot to disk and reload
5. Benchmark three fsync policies: every write, every second, never

**Mini project:** `wal-lib`, a log library with recovery and a crash harness.

### Module 9.2: Server and protocol (Weeks 71–73)

**Learn, in this order**

1. RESP-style protocol design and pipelining
2. Command dispatch tables
3. Integrating your reactor (`evloop`) with the storage layer
4. TTL expiry: lazy and active
5. Memory limits and eviction (LRU and LFU approximations)
6. Client library design

**Practice, in this order**

1. A protocol parser, fuzzed for 30 minutes
2. A command table with GET, SET, DEL, EXISTS, EXPIRE, TTL and INCR
3. Expiry using a timer heap
4. An LRU cache built from a hash map and a linked list
5. A CLI client with line editing

**Mini project:** `kv-v0`, an in-memory server over TCP with pipelining and TTL.

### Module 9.3: Persistence, concurrency and reliability (Weeks 74–76)

**Learn, in this order**

1. Threading models: single-threaded core vs sharding
2. Background snapshot and compaction threads
3. Locking strategy and consistency under concurrent clients
4. Recovery procedure and startup time
5. Observability: metrics, structured logs, an INFO command
6. Configuration and operational limits

**Practice, in this order**

1. Integrate the WAL and make writes durable under your chosen policy
2. Snapshot, then truncate the log safely
3. Shard by key hash with one worker per shard
4. Differential test: random operations compared against a `std::map` oracle
5. Randomized crash tests that verify no acknowledged write is lost

**Mini project:** `kv-v1`, a durable, concurrent server with recovery.

### Module 9.4: Performance, hardening and presentation (Weeks 77–79)

**Learn, in this order**

1. Server benchmark methodology: closed vs open loop, coordinated omission
2. Reading flame graphs for a networked system
3. Causes of tail latency: allocation, fsync, lock contention, compaction
4. Security hygiene: input validation, size limits, resource limits
5. Writing a design doc, a README and a postmortem

**Practice, in this order**

1. Build a benchmark tool in the spirit of redis-benchmark
2. Remove your top three bottlenecks and measure each change
3. Write a design document covering architecture, invariants and tradeoffs
4. Record a short demo

**Mini project:** `kv-final`, the tagged release with full documentation.

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
