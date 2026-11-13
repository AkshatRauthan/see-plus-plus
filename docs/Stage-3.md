## Stage 3: Unix Systems Programming (Weeks 13–22)

This stage teaches you to talk to the kernel directly, and ends with a shell that exercises nearly every concept in it.

### Stage goals

- Use system calls directly and know roughly what each one costs.
- Understand processes, file descriptors, signals, pipes and terminals well enough to build a shell.
- Use strace and /proc to see what any program is really doing.

### Module 3.1: Syscalls and file I/O (Weeks 13–14)

**Learn, in this order**

1. User space vs kernel space; how a syscall happens; strace
2. File descriptors, the fd table, open flags, `read` and `write` semantics
3. Partial reads and writes, `EINTR`, short counts
4. `lseek`, `pread`, `pwrite`; `dup`, `dup2`, `fcntl`
5. Inodes, `stat`, hard links vs symlinks, permissions and umask
6. Directories: `opendir`, `readdir`, `nftw`
7. Buffering layers: stdio, the page cache, `fsync`

**Practice, in this order**

1. `cp` with a read/write loop that handles partial I/O and errors
2. `tee`, plus a test that redirects with `dup2`
3. `ln`, `stat` and `ls -l` clones that print mode, owner, size and times
4. `find` with your own recursion, then again with `nftw`
5. Benchmark copy speed for buffer sizes from 1 byte to 1 MB and plot it
6. Run strace on your tools and compare their syscalls with the real ones

**Mini project:** `minitar`, which creates and extracts archives in a simplified tar-like format, preserving permissions, times and symlinks.

### Module 3.2: Processes and signals (Weeks 15–17)

**Learn, in this order**

1. Process model: pid, ppid, address space, environment
2. `fork` semantics and copy-on-write
3. The `exec` family, `argv`, `envp`, `PATH` lookup
4. `wait`, `waitpid` and the status macros; zombies and orphans
5. Process groups, sessions, the controlling terminal
6. Signals: `sigaction`, masks, pending signals, async-signal-safe functions
7. `SIGCHLD`, `SIGINT`, `SIGTSTP`, `SIGPIPE`; the self-pipe trick
8. Basic termios: canonical vs raw mode

**Practice, in this order**

1. Fork N children, exec a command in each, collect every exit status
2. Implement `system()` yourself
3. Build `ls | grep foo | wc -l` by hand with fork, pipe and dup2
4. Show a non-reentrancy bug in a signal handler, then fix it
5. `mytimeout`: run a command and kill it after N seconds
6. Daemonize a program correctly (setsid, double fork, closing fds)

**Mini project:** `supervisor`, which runs a command, restarts it on crash with exponential backoff, forwards signals and logs events.

### Module 3.3: IPC and memory mapping (Weeks 18–19)

**Learn, in this order**

1. Pipes and FIFOs
2. `mmap`: file-backed, anonymous and shared; `munmap`, `msync`
3. POSIX shared memory and semaphores
4. Unix domain sockets
5. `/proc` and `/sys` for inspecting processes
6. Virtual memory from user space: page faults, `madvise`, `mincore`
7. Time and limits: `clock_gettime`, `timerfd`, `rlimit`

**Practice, in this order**

1. Parent-child ping-pong over two pipes; measure the latency
2. File copy via `mmap`; compare with read/write
3. A shared-memory ring buffer between two processes
4. A Unix domain socket echo server and client
5. Read `/proc/self/maps` and explain every region
6. Measure the cost of a minor page fault

**Mini project:** `ipc-bench`, which measures throughput and latency of pipes vs Unix sockets vs shared memory.

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
