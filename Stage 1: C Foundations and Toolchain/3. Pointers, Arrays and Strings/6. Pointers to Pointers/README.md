<div align="center">
  <h1>Pointers to Pointers</h1>
  Exploring double pointers, multiple levels of indirection, pointer reassignment, dynamic memory allocation, and pointer safety in C.
</div>

<br />

## Part Overview

This part explores pointers to pointers, commonly known as double pointers, and how they allow programs to access and modify pointer variables.

It begins with multiple levels of indirection, pointer reassignment, and passing double pointers to functions. It then moves into dynamic memory allocation, dynamically allocated arrays and matrices, structures, and function pointers.

The final exercises focus on memory ownership, pointer cleanup, and common pointer-to-pointer mistakes.

### Learning Objectives

- Understand multiple levels of pointer indirection.
- Modify values and caller-owned pointers through double pointers.
- Work with arrays of pointers.
- Allocate, resize, and release dynamic memory.
- Build dynamically allocated matrices.
- Understand pointer ownership and lifetime.
- Recognize common pointer mistakes and undefined behavior.

---

## Topics Covered

| #   | Exercise                                                    | Main Topics                                                  |
| --- | ----------------------------------------------------------- | ------------------------------------------------------------ |
| 1   | Pointer-to-Pointer Fundamentals                             | Double pointer declarations, initialization, dereferencing   |
| 2   | Modifying Values Through Double Pointers                    | Modifying original values through `**`                       |
| 3   | Pointer Reassignment Through Double Pointers                | Local vs caller pointer reassignment                         |
| 4   | Passing Double Pointers to Functions                        | Function parameters and caller-owned pointers                |
| 5   | Multiple Variables and Indirection Chains                   | Multiple pointer levels                                      |
| 6   | Pointer-to-Pointer with Arrays                              | Arrays of pointers and pointer traversal                     |
| 7   | Pointer-to-Pointer and Dynamic Memory Allocation            | Allocation through double pointers                           |
| 8   | Dynamic Arrays Through Double Pointers                      | Dynamic array allocation and access                          |
| 9   | Dynamic 2D Arrays Using Double Pointers                     | Row pointers and dynamic matrices                            |
| 10  | Resizing Dynamic Arrays Through Double Pointers             | `realloc()` and pointer updates                              |
| 11  | Returning Dynamic Memory from Functions                     | Returning heap allocations                                   |
| 12  | Pointer-to-Pointer with Structures                          | Structure pointers and member access                         |
| 13  | Dynamic Arrays of Structures                                | Dynamic structure allocation                                 |
| 14  | Dynamic Memory Ownership and Pointer Cleanup                | Ownership, aliases, cleanup                                  |
| 15  | Generic Pointer-to-Pointer and void Pointers                | `void *`, `void **`, type compatibility                      |
| 16  | Dynamic Arrays of Function Pointers Through Double Pointers | Callback arrays and dynamic allocation                       |
| 17  | Common Pointer-to-Pointer Mistakes                          | Invalid indirection, NULL pointers, leaks, dangling pointers |

---

## Core Syntax

| Declaration / Expression | Meaning                              |
| ------------------------ | ------------------------------------ |
| `int *ptr`               | Pointer to an integer                |
| `int **ptr`              | Pointer to an integer pointer        |
| `int ***ptr`             | Pointer to an integer double pointer |
| `*ptr`                   | Dereference one pointer level        |
| `**ptr`                  | Dereference two pointer levels       |
| `&ptr`                   | Address of a pointer variable        |
| `void **ptr`             | Pointer to a generic pointer         |


### Example: Reassigning a Caller-Owned Pointer

```c
#include <stdio.h>

// Updates the pointer belonging to the caller.
static void ReassignPointer(int **pointer, int *replacement) {
    *pointer = replacement;
}

int main(void) {
    int first = 10;
    int second = 20;

    int *ptr = &first;

    printf("Before: %d\n", *ptr);

    // Pass the address of ptr.
    ReassignPointer(&ptr, &second);

    printf("After: %d\n", *ptr);

    return 0;
}
```

**Output:**

```text
Before: 10
After: 20
```

The function receives the address of the caller's pointer. Assigning to `*pointer` modifies the actual pointer variable.

---

## Key Concepts

- C passes all function arguments by value, including pointers.
- A double pointer stores the address of another pointer.
- `int **` allows a function to modify an `int *` belonging to its caller.
- Every dereference accesses one additional pointer level.
- Dynamic arrays and matrices require careful allocation and cleanup.
- `realloc()` may move an allocation, so the updated pointer must be retained.
- Memory ownership determines which part of a program is responsible for freeing an allocation.
- `void **` is not interchangeable with arbitrary typed double pointers.
- Dereferencing uninitialized, NULL, or dangling pointers can cause undefined behavior.

---

## Tools and Technologies

| Tool                       | Purpose                      |
| -------------------------- | ---------------------------- |
| Clang                      | C compiler                   |
| C11                        | Language standard            |
| Make                       | Build automation             |
| AddressSanitizer           | Detecting memory errors      |
| UndefinedBehaviorSanitizer | Detecting undefined behavior |
| LLDB                       | Debugging                    |

---

## Build System

The Makefile builds each exercise independently and stores executables inside `build/`.

**Build all exercises:**

```bash
make
```

**Build and run a specific exercise:**

```bash
make run N=1
```

**Build and run with sanitizers:**

```bash
make san N=17
```

**Clean generated files:**

```bash
make clean
```

---

## Key Takeaways

Double pointers provide an additional level of indirection that allows programs to modify pointer variables, manage dynamic allocations, and work with complex pointer-based data structures.

Understanding them reinforces important C concepts such as function argument passing, pointer lifetime, memory ownership, allocation management, and safe pointer operations.
