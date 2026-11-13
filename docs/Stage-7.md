## Stage 7: Modern C++ Core (Weeks 51–59)

This stage shows you how C++ automates the patterns you wrote by hand in C, and ends with you porting an earlier system to idiomatic C++20.

### Stage goals

- Write idiomatic C++20 that is as fast as the C equivalent and much harder to misuse.
- Express ownership and lifetimes in types instead of comments.
- Know what each abstraction costs at the machine level.

### Module 7.1: From C to C++: classes, RAII, exceptions (Weeks 51–52)

**Learn, in this order**

1. The C++ build model: headers, the one-definition rule, namespaces, `inline`
2. References vs pointers; `const` correctness
3. Classes, constructors, destructors; initialization (member initializer lists, brace init)
4. RAII as the core idiom
5. The rule of zero, three and five
6. Exceptions and the three exception-safety guarantees; `noexcept`
7. Virtual functions, vtables and what dynamic dispatch costs

**Practice, in this order**

1. RAII wrappers for `FILE *`, file descriptors, `malloc` memory and mutex locks
2. Port your `libds` vector to a C++ class that follows the rule of five
3. Inspect a vtable and an object's layout in gdb
4. Review one of your classes for exception safety and fix the leaks

**Mini project:** `sysraii`, with `fd`, `mapped_file` and `socket` RAII classes.

### Module 7.2: Move semantics and smart pointers (Weeks 53–54)

**Learn, in this order**

1. Lvalues, rvalues and value categories
2. `std::move` and `std::forward`; move constructors and move assignment
3. `unique_ptr`, `shared_ptr` (and its control block), `weak_ptr`; custom deleters
4. Ownership design guidelines; passing and returning by value
5. Copy elision; `emplace` vs `push`
6. Perfect forwarding

**Practice, in this order**

1. Implement `unique_ptr`
2. Implement `shared_ptr` with `weak_ptr` support
3. Implement `vector<T>` with move-aware growth; count copies and moves in tests
4. Benchmark `push_back` vs `emplace_back`, and pass-by-value-then-move

**Mini project:** `mini-stl`, your own `unique_ptr`, `shared_ptr`, `vector` and `string`, tested under ASan.

### Module 7.3: Templates, constexpr and generic code (Weeks 55–56)

**Learn, in this order**

1. Function and class templates; deduction; specialization
2. Variadic templates and fold expressions
3. Type traits, SFINAE basics, concepts (C++20)
4. `constexpr`, `consteval`, `constinit`
5. Lambdas and callable objects; what `std::function` costs
6. CRTP and static polymorphism

**Practice, in this order**

1. A `ring_buffer<T, N>` constrained with concepts
2. A `flat_map` (sorted vector) with a `std::map`-like interface
3. A `small_vector` with inline storage
4. A compile-time lookup table built with `constexpr`
5. A type-erased callable that avoids the heap for small captures
6. A state machine using `std::variant` and `std::visit`

**Mini project:** `containers`, the ring buffer, flat map and small vector with tests and benchmarks.

### Module 7.4: The standard library in depth (Week 57)

**Learn, in this order**

1. Container complexity, iterator categories, invalidation rules
2. Algorithms and ranges and views (C++20)
3. `string_view`, `span`, `optional`, `variant`; `std::expected` (awareness)
4. `chrono`, `filesystem`, `std::format`
5. `std::pmr` and allocators
6. Modules and coroutines (awareness)

**Practice, in this order**

1. Rewrite `mycat`, `mywc` and `mygrep` in idiomatic C++
2. Benchmark vector vs list vs deque vs flat_map on a realistic workload
3. Use a `pmr` arena with `std::vector` and measure the allocations saved
4. Re-implement `mydu` with `std::filesystem`

**Mini project:** `cpp-utils`, the four tools above in idiomatic C++.

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
