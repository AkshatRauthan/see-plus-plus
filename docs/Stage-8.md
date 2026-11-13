## Stage 8: Advanced C++ and Performance Engineering (Weeks 60–67)

This stage combines everything so far into performance work you can trust: C++20 concurrency, cache-aware design, rigorous benchmarking, and a toolkit of fast components.

### Stage goals

- Port and improve your earlier concurrency work with C++20 facilities.
- Design data layouts and allocation strategies around cache behaviour.
- Benchmark and profile with enough rigor that your numbers can be trusted.

### Module 8.1: Concurrency in C++ (Weeks 60–61)

**Learn, in this order**

1. `std::thread`, `std::jthread`, `std::stop_token`
2. `mutex`, `lock_guard`, `unique_lock`, `scoped_lock`
3. `condition_variable`, `std::latch`, `std::barrier`, `std::counting_semaphore`
4. `std::atomic` and `memory_order` in C++; the C++ memory model
5. `future`, `promise`, `async` and their costs
6. Coroutines (C++20) as a concept for async I/O

**Practice, in this order**

1. Port `cpool` to C++20 with `jthread` and typed futures
2. An SPSC queue with `alignas` padding to avoid false sharing
3. Compare your pool with the parallel standard algorithms where your toolchain supports them
4. Run everything under TSan

**Mini project:** `cppool`, the C++20 thread pool.

### Module 8.2: Memory and data-oriented design (Weeks 62–63)

**Learn, in this order**

1. What an allocation costs; custom allocators and `std::pmr`
2. Arena, pool and slab allocators in C++
3. Data-oriented design: struct of arrays, hot and cold splitting
4. Small buffer optimization and intrusive containers
5. Alignment: `alignas` and cache-line padding
6. Compiler help: inlining, LTO, PGO, `-march=native`, branch hints

**Practice, in this order**

1. An arena allocator that implements `std::pmr::memory_resource`
2. A pool allocator benchmarked against `new` and `delete`
3. Convert an array-of-structs particle simulation to struct-of-arrays and measure
4. Try LTO and PGO on one of your projects and record the effect
5. Use `perf` to find the top three hot spots in `mini-httpd` or `cppsys`

**Mini project:** `fast-alloc`, arena and pool allocators with benchmarks.

### Module 8.3: Benchmarking, profiling and build tooling (Week 64)

**Learn, in this order**

1. Google Benchmark: fixtures, `DoNotOptimize`, counters
2. Statistical rigor: warmup, variance, pinning CPUs, noise sources
3. `perf stat`, `perf record`, `perf annotate`, flame graphs
4. cachegrind and callgrind
5. CMake targets and presets; dependency management (FetchContent, awareness of vcpkg and Conan)
6. CI with sanitizers and clang-tidy

**Practice, in this order**

1. Build a CMake project template with tests, benchmarks and sanitizer presets
2. Write a microbenchmark that lies (dead-code elimination, cold cache), then fix it
3. Benchmark your containers against the standard ones with proper statistics
4. Publish the template and start the next project from it

**Mini project:** `project-template`, a reusable repository for every later project.

### Module 8.4: Lock-free and low-latency structures (Week 65)

**Learn, in this order**

1. SPSC and bounded MPMC queues
2. Sequence locks and RCU (awareness)
3. Hazard pointers and epoch-based reclamation (awareness)
4. Allocation-free hot paths
5. Latency measurement: HDR histograms and coordinated omission

**Practice, in this order**

1. A bounded MPMC queue in the Vyukov style
2. Compare it with a mutex-protected queue at 1, 2, 4 and 8 threads
3. Record p50, p99 and p99.9 latencies, not just throughput

**Mini project:** `lowlat-queue`, a queue with a latency histogram harness.

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
