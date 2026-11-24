<div align="center">
  <h1>Arrays and Pointers</h1>
  Exploring the relationship between arrays and pointers, array decay, indexing, pointer arithmetic, function parameters, and array memory behavior in C.
</div>

<br />

## Part Overview

This part explores the close relationship between arrays and pointers in C, while establishing that they are fundamentally different types of objects.

It begins with understanding how array expressions decay into pointers to their first elements, then examines why array names behave differently from pointer variables. It explores array indexing as pointer arithmetic and dereferencing, array sizes, passing arrays to functions, and modifying arrays through pointers.

The final exercises investigate array decay exceptions, including `sizeof`, the unary `&` operator, and array initialization, before combining these concepts in practical exercises.

## Learning Objectives

By completing this part, you will understand:

- How arrays decay into pointers in most expressions.
- Why an array is not a pointer variable.
- How array names differ from pointer variables in assignment and reassignment.
- How `sizeof` behaves differently on arrays and pointers.
- The relationship between array indexing, pointer arithmetic, and dereferencing.
- How arrays are passed to functions in C.
- How pointers can modify array elements.
- How pointer-to-array types differ from ordinary pointers.
- When array-to-pointer decay does not occur.
- How to work safely with array boundaries and one-past-the-end pointers.

## Topics Covered

### 1. Array-to-Pointer Decay

**File:** `1. Array-to-Pointer Decay.c`

Introduces array-to-pointer decay, the conversion of an array expression into a pointer to its first element in most expression contexts.

- Array expressions and pointer conversion.
- Accessing the first element through an array and pointer.
- Initializing a pointer from an array.
- Traversing array elements through pointer indexing.
- Understanding that decay does not convert the array object into a pointer variable.

### 2. Array Names vs Pointer Variables

**File:** `2. Array Names vs Pointer Variables.c`

Examines why arrays and pointers behave similarly when accessing elements, but differ in their object identity and operations.

- Array objects vs pointer variables.
- Array names in expressions.
- Array assignment restrictions.
- Pointer reassignment.
- `ptr++` vs `numbers++`.
- Modifying array elements vs changing pointer addresses.
- Address of an array vs address of a pointer variable.

### 3. `sizeof` on Arrays vs Pointers

**File:** `3. sizeof on Arrays vs Pointers.c`

Explores how `sizeof` determines storage sizes and why array size information is not automatically retained by pointers.

- `sizeof(array)` — entire array size.
- `sizeof(array[0])` — element size.
- `sizeof(pointer)` — pointer variable size.
- `sizeof(*pointer)` — pointed-to type size.
- Calculating array element counts.
- Why array-length calculations fail after decay.
- Array addresses vs pointer addresses.

### 4. Array Indexing and Pointer Dereferencing

**File:** `4. Array Indexing and Pointer Dereferencing.c`

Explains how indexing is defined in terms of pointer arithmetic and dereferencing.

- `array[index]` and `*(array + index)`.
- Pointer indexing.
- Pointer arithmetic scaling by element type.
- Accessing and modifying elements through pointers.
- The unusual but valid `index[array]` syntax.
- Array bounds and one-past-the-end restrictions.

### 5. Arrays as Function Parameters

**File:** `5. Arrays as Function Parameters.c`

Investigates what actually happens when arrays are passed to functions.

- Array parameter adjustment to pointer parameters.
- `int arr[]` vs `int *arr` in function declarations.
- Passing array lengths separately.
- Modifying original arrays through function parameters.
- Pointer parameters passed by value.
- Why `sizeof` inside a function does not provide the original array size.
- Read-only array parameters using `const`.

### 6. Pointer Reassignment vs Array Modification

**File:** `6. Pointer Reassignment vs Array Modification.c`

Distinguishes pointer reassignment from modifying the data pointed to by the pointer.

- Reassigning pointers to different arrays.
- Modifying elements through dereferencing.
- `ptr = other` vs `*ptr = value`.
- Pointer movement vs data modification.
- Understanding how a pointer's current target determines which object is accessed.

### 7. Array Decay Exceptions

**File:** `7. Array Decay Exceptions.c`

Explores important contexts where array-to-pointer decay does not occur.

- `sizeof` applied to an array.
- Unary `&` applied to an array.
- Pointer-to-array types.
- Array initialization.
- Character arrays initialized from string literals.
- Array address vs first-element address.
- Different pointer arithmetic behavior for pointer-to-array types.

### 8. Arrays and Pointers Practical Exercises

**File:** `8. Arrays and Pointers Practical Exercises.c`

Combines the concepts from the entire part in a practical program.

- Array-to-pointer decay.
- Array size and element count.
- Pointer arithmetic and dereferencing.
- Pointer reassignment.
- Modifying arrays through pointers.
- Array parameters and function calls.
- Pointer-to-array declarations.
- One-past-the-end pointers.
- Pointer subtraction and element distance.

## Core Syntax

| Syntax                         | Description                                                           |
| ------------------------------ | --------------------------------------------------------------------- |
| `int arr[5]`                   | Declares an array of 5 integers                                       |
| `int *ptr = arr`               | Initializes a pointer to the first element                            |
| `arr[i]`                       | Accesses the element at index `i`                                     |
| `*(arr + i)`                   | Accesses an element through pointer arithmetic                        |
| `ptr++`                        | Advances the pointer by one element                                   |
| `ptr = other`                  | Reassigns a pointer to another compatible location                    |
| `&arr`                         | Gets the address of the entire array                                  |
| `int (*ptr)[5]`                | Declares a pointer to an array of 5 integers                          |
| `sizeof(arr)`                  | Returns the size of the entire array                                  |
| `sizeof(ptr)`                  | Returns the size of the pointer variable                              |
| `sizeof(arr) / sizeof(arr[0])` | Calculates the array element count when the actual array is available |
| `arr + n`                      | Produces a pointer offset by `n` elements                             |
| `end - start`                  | Calculates the distance between valid related pointers                |

## Array and Pointer Relationship

Arrays and pointers are closely related in C, but they are not interchangeable.

| Arrays                                      | Pointers                                         |
| ------------------------------------------- | ------------------------------------------------ |
| Actual objects containing elements          | Variables storing addresses                      |
| Cannot be reassigned                        | Can be reassigned                                |
| `sizeof` returns the total array size       | `sizeof` returns pointer size                    |
| Array expressions usually decay to pointers | Already pointer values                           |
| Array elements can be modified              | Pointed-to elements can be modified if permitted |
| Array name is not a modifiable lvalue       | Pointer variable is a modifiable lvalue          |

## Pointer Arithmetic

Pointer arithmetic is scaled by the size of the pointed-to type.

For an `int *` pointer, advancing by one moves to the next `int` element rather than the next byte.

```c
int numbers[] = {10, 20, 30, 40, 50};
int *ptr = numbers;

ptr + 1;       // Next int
ptr + 2;       // Two int elements ahead
*(ptr + 2);    // Access third element
ptr[2];         // Equivalent access
```

Pointer arithmetic must remain within the same array object, or at most one element past its end, subject to the C standard's rules.

## Array Parameter Pattern

A common pattern for array-processing functions is:

```c
void ProcessArray(int *arr, size_t length);
```

The pointer provides access to the elements, while `length` provides the number of elements available for processing.

This avoids attempting to determine the array's original length through `sizeof` after it has decayed to a pointer.

## Key Concepts

- Array-to-pointer decay
- Array objects and pointer variables
- Pointer arithmetic
- Dereferencing
- Array indexing
- Pointer reassignment
- Array parameter adjustment
- Pointer-to-array types
- `sizeof` behavior
- Array boundaries
- One-past-the-end pointers
- `ptrdiff_t`
- Array initialization
- Undefined behavior from invalid pointer operations

## Tools and Technologies

- **Language:** C
- **Standard:** C11
- **Compiler:** Clang
- **Debugger:** LLDB
- **Build System:** GNU Make
- **Editor / IDE:** Visual Studio Code
- **Diagnostics:** AddressSanitizer (ASan), UndefinedBehaviorSanitizer (UBSan)

## Build System

Each exercise can be compiled independently using the provided Makefile.

### Build all exercises

```bash
make
```

### Run a specific exercise

```bash
make run N=1
make run N=4
make run N=8
```

### Build with sanitizers

```bash
make san
```

### Run with sanitizers

```bash
make run-san N=8
```

### Clean build files

```bash
make clean
```

The Makefile uses Clang, strict warning flags, and stores compiled binaries inside the `build/` directory.

## Key Takeaways

- Arrays are objects containing elements, while pointers are variables storing addresses.
- Array-to-pointer decay is a conversion that occurs in most expression contexts, not a transformation of the array itself.
- Array indexing is based on pointer arithmetic and dereferencing.
- Pointer arithmetic is type-scaled.
- Arrays cannot be reassigned, but pointer variables can be redirected.
- C passes pointers by value, allowing functions to access and modify the caller's array elements.
- Array lengths should be passed explicitly when working with function parameters.
- Pointer-to-array declarations preserve the array dimension in the pointed-to type.
- Correct pointer arithmetic and boundary handling are essential for writing safe C programs.

---
