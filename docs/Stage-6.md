## Stage 6: Networking and I/O at Scale (Weeks 41–50)

This stage takes you from your first socket to an event-driven HTTP server whose performance you can measure and explain.

### Stage goals

- Understand the TCP/IP stack well enough to debug with tcpdump and Wireshark.
- Build network servers with non-blocking I/O and an event loop.
- Measure server performance honestly: throughput, latency percentiles and bottlenecks.

### Module 6.1: Networking fundamentals and sockets (Weeks 41–43)

**Learn, in this order**

1. TCP/IP layers, IP addressing, ports
2. TCP handshake, retransmission, flow control, congestion control basics
3. UDP and when to use it
4. The sockets API: `socket`, `bind`, `listen`, `accept`, `connect`
5. Byte order, `getaddrinfo`, IPv4 and IPv6
6. Stream framing: length prefixes and delimiters; partial reads and writes
7. Socket options: `SO_REUSEADDR`, `TCP_NODELAY`, listen backlog
8. DNS basics

**Practice, in this order**

1. Capture a TCP session with tcpdump or Wireshark and label every packet
2. A blocking echo server and client
3. A chat server using one forked process per connection
4. A UDP ping with loss and round-trip statistics
5. Send a file over TCP with a length-prefixed protocol
6. Add a listen mode to your client so it behaves like netcat

**Mini project:** `mynetcat`, a netcat clone with TCP client and server modes.

### Module 6.2: I/O models and event loops (Weeks 44–46)

**Learn, in this order**

1. Blocking vs non-blocking I/O; `EAGAIN`
2. `select` and `poll`, and why they do not scale
3. `epoll`: level-triggered vs edge-triggered
4. Event loop design: one state machine per connection
5. Timers: `timerfd`, heap or timer wheel
6. Read and write buffers; backpressure
7. Concurrency models: thread per connection, thread pool, reactor, multi-reactor
8. `sendfile`, `splice` and zero-copy; `io_uring` (awareness)

**Practice, in this order**

1. An echo server built four ways: select, poll, epoll level-triggered, epoll edge-triggered
2. A chat server on epoll with per-connection buffers
3. Idle-connection timeouts using a timer heap
4. Load test with wrk or your own generator at 1k, 5k and 10k connections
5. Raise the file descriptor limit and explain what breaks first

**Mini project:** `evloop`, a reusable event loop library with fd callbacks and timers.

### Module 6.3: Application protocols and HTTP (Weeks 47–48)

**Learn, in this order**

1. HTTP/1.1 messages, methods, status codes, headers
2. Incremental parsing as a state machine
3. Keep-alive, chunked encoding, `Range`
4. MIME types and caching headers (`ETag`, `If-Modified-Since`)
5. Security: path traversal, header injection, slowloris, request limits
6. TLS concepts and a first OpenSSL client (awareness)
7. Designing a simple binary or RESP-like protocol

**Practice, in this order**

1. An HTTP request parser, fuzzed
2. A single-threaded static file server
3. Add keep-alive and pipelining
4. Add `Range` and conditional requests
5. Write a path-traversal test suite and make the server pass it

**Mini project:** `cget`, a small HTTP client that downloads files with Range requests and resume, a C counterpart of your Go downloader.

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
