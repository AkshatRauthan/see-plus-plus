## Stage 5: Concurrency (Weeks 33–40)

This stage teaches you to write multithreaded code whose correctness you can argue, not just hope for, and ends with a reusable thread pool library.

### Stage goals

- Write multithreaded code and be able to explain why it is correct.
- Know when to reach for mutexes, condition variables, semaphores or atomics.
- Find races and deadlocks with ThreadSanitizer and disciplined design.

### Module 5.1: Threads and synchronization (Weeks 33–35)

**Learn, in this order**

1. Threads vs processes; `pthread_create`, `join`, `detach`
2. Shared-state hazards: data races, atomicity, visibility
3. Mutexes, critical sections, lock ordering, deadlock
4. Condition variables: predicates, spurious wakeups, signal vs broadcast
5. Semaphores, barriers, read-write locks
6. Thread-local storage; thread safety vs reentrancy
7. Classic problems: producer-consumer, readers-writers, dining philosophers

**Practice, in this order**

1. Race on a shared counter; fix it with a mutex, then with an atomic
2. A bounded buffer with a mutex and condition variables
3. The same bounded buffer with semaphores
4. Dining philosophers: three deadlock-free solutions
5. Readers-writers with a writer-preferring policy
6. Parallel sum and merge sort; plot speedup against thread count
7. Run all of the above under TSan and helgrind

**Mini project:** `parwc`, a parallel word count over many files using a work queue.

### Module 5.2: Atomics and the memory model (Weeks 36–37)

**Learn, in this order**

1. Cache coherence (MESI) in one page
2. Compiler and CPU reordering; why plain variables are not enough
3. C11 atomics: load, store, `fetch_add`, `compare_exchange`
4. Memory orders: relaxed, acquire, release, seq_cst
5. Spinlocks, backoff, futex basics
6. The ABA problem; hazard pointers and epoch reclamation (awareness)
7. False sharing and padding

**Practice, in this order**

1. A spinlock with `atomic_flag`, then a ticket lock
2. A store-buffering litmus test that shows reordering on your CPU
3. A lock-free stack with CAS; reproduce ABA, then avoid it
4. An SPSC ring buffer using acquire and release
5. Counter scaling: global mutex vs atomic vs per-thread shards, plotted

**Mini project:** `lfq`, SPSC and MPSC queues benchmarked against a mutex-protected queue.

### Module 5.3: Concurrent data structures and pools (Week 38)

**Learn, in this order**

1. Coarse vs fine-grained locking; lock striping
2. Concurrent hash table designs
3. Thread pool design: queue, workers, shutdown
4. Futures and promises
5. Testing concurrent code: stress tests, TSan, deterministic replay
6. Scalability: contention and Amdahl's law

**Practice, in this order**

1. A striped-lock hash map
2. A thread pool with graceful shutdown
3. Parallel quicksort on the pool
4. Benchmark with 1 to N threads and plot the speedup

**Mini project:** `futures-lite`, where you submit a task and wait for its result.

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
