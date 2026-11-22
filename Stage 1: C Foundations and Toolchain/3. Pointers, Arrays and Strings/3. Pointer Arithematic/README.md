 <div align="center">
  <h1>Pointer Arithmetic</h1>
  Exploring pointer arithmetic in C, including pointer offsets, comparisons, multidimensional arrays, byte-level memory access, and pointer safety.
</div>

<br />

## Part Overview

This part explores how pointer arithmetic works in C and how pointers move through memory.

Unlike ordinary integer arithmetic, pointer arithmetic is aware of the type being pointed to. Adding one to an `int *`, for example, advances the pointer by one integer element rather than one byte.

The exercises gradually introduce pointer movement, pointer subtraction, comparisons, structure pointers, multidimensional arrays, and byte-level memory inspection.

### Learning Objectives

- Understand how pointer arithmetic is scaled according to the pointed-to type.
- Perform pointer addition and subtraction.
- Understand pointer comparisons and their restrictions.
- Traverse arrays using pointers.
- Work with pointers to structures and multidimensional arrays.
- Inspect object representations using `unsigned char *`.
- Understand one-past-the-end pointers.
- Recognize invalid pointer arithmetic and undefined behavior.

---

## Topics Covered

### 1. Pointer Arithmetic Fundamentals

**File:** `1. Pointer Arithmetic Fundamentals.c`

Introduces the fundamental pointer arithmetic operators and explains how pointers move through arrays.

**Topics Covered:**

- Pointer increment (`++`).
- Pointer decrement (`--`).
- Pointer addition (`+`).
- Pointer subtraction (`-`).
- Compound pointer assignment (`+=`, `-=`).
- Type-scaled pointer movement.
- Array indexing through pointer arithmetic.
- One-past-the-end pointers.

**Core Operations:**

| Expression   | Description                        |
| ------------ | ---------------------------------- |
| `ptr + n`    | Moves forward by `n` elements      |
| `ptr - n`    | Moves backward by `n` elements     |
| `ptr++`      | Advances by one element            |
| `ptr--`      | Moves backward by one element      |
| `ptr += n`   | Advances by `n` elements           |
| `ptr -= n`   | Moves backward by `n` elements     |
| `*(ptr + n)` | Accesses the element at offset `n` |
| `ptr[n]`     | Equivalent to `*(ptr + n)`         |

**Example:**

```c
int numbers[] = {10, 20, 30, 40, 50};

int *ptr = numbers;

printf("%d\n", *ptr);       // 10

ptr++;

printf("%d\n", *ptr);       // 20

printf("%d\n", *(ptr + 2)); // 40
```

Pointer arithmetic is scaled according to the size of the pointed-to type.

For example, if `sizeof(int)` is 4, incrementing an `int *` advances its address by 4 bytes.

---

### 2. Pointer Addition and Subtraction

**File:** `2. Pointer Addition and Subtraction.c`

Explores pointer offsets and pointer subtraction, including calculating distances and array indices.

**Topics Covered:**

- Adding offsets to pointers.
- Subtracting offsets from pointers.
- Pointer subtraction.
- Calculating distances between array elements.
- Using `ptrdiff_t`.
- Calculating array indices through pointer subtraction.
- Subtracting pointers within the same array.

**Core Concepts:**

| Expression    | Description                                        |
| ------------- | -------------------------------------------------- |
| `ptr + n`     | Advances by `n` elements                           |
| `ptr - n`     | Moves backward by `n` elements                     |
| `ptr2 - ptr1` | Calculates the number of elements between pointers |
| `ptr - array` | Calculates an element's array index                |

**Example:**

```c
#include <stddef.h>
#include <stdio.h>

int numbers[] = {10, 20, 30, 40, 50};

int *start = numbers;
int *current = numbers + 3;

ptrdiff_t distance = current - start;

printf("Distance: %td\n", distance);
```

Output:

```text
Distance: 3
```

**Why use `ptrdiff_t`?**

`ptrdiff_t`, declared in `<stddef.h>`, is the signed integer type used to represent the result of subtracting two pointers.

It is preferable to assuming that pointer differences fit into an ordinary `int`.

Use `%td` when printing a `ptrdiff_t` value.

---

### 3. Pointer Comparisons

**File:** `3. Pointer Comparisons.c`

Explores how pointers are compared and distinguishes pointer comparisons from comparisons of the values they reference.

**Topics Covered:**

- Pointer equality (`==`).
- Pointer inequality (`!=`).
- Relational comparisons (`<`, `>`, `<=`, `>=`).
- Comparing pointers within the same array.
- Comparing against one-past-the-end pointers.
- Difference between pointer values and pointed-to values.

**Comparison Operators:**

| Operator | Description                                           |
| -------- | ----------------------------------------------------- |
| `==`     | Checks whether pointers compare equal                 |
| `!=`     | Checks whether pointers compare unequal               |
| `<`      | Checks whether one pointer precedes another           |
| `>`      | Checks whether one pointer follows another            |
| `<=`     | Checks whether one pointer precedes or equals another |
| `>=`     | Checks whether one pointer follows or equals another  |

**Example:**

```c
int numbers[] = {10, 20, 30};

int *first = &numbers[0];
int *second = &numbers[1];

printf("%d\n", first == second);   // 0
printf("%d\n", first < second);    // 1

printf("%d\n", *first == *second); // 0
printf("%d\n", *first < *second);  // 1
```

**Important Distinction:**

| Expression          | What is compared?                         |
| ------------------- | ----------------------------------------- |
| `first == second`   | Pointer values                            |
| `first < second`    | Pointer positions                         |
| `*first == *second` | Values stored at the pointed-to locations |
| `*first < *second`  | Values stored at the pointed-to locations |

Equality comparisons can compare pointers to different objects. Relational comparisons between pointers to unrelated objects are not generally defined by the C standard.

---

### 4. Pointer Arithmetic with Structures

**File:** `4. Pointer Arithmetic with Structures.c`

Explores pointer arithmetic involving structures and arrays of structures.

**Topics Covered:**

- Declaring structure pointers.
- Initializing pointers to structure arrays.
- Incrementing and decrementing structure pointers.
- Accessing members through structure pointers.
- Pointer arithmetic with structure arrays.
- Structure size and memory alignment.
- The relationship between pointer increments and `sizeof`.

**Example:**

```c
typedef struct {
    int id;
    double salary;
    char grade;
} Employee;

Employee employees[] = {
    {101, 45000.0, 'A'},
    {102, 52000.0, 'B'},
    {103, 61000.0, 'A'}
};

Employee *ptr = employees;

printf("%d\n", ptr->id);

ptr++;

printf("%d\n", ptr->id);
```

Output:

```text
101
102
```

**Important Concept:**

When incrementing a structure pointer:

```c
ptr++;
```

The pointer advances by one complete structure.

Conceptually, the address advances by:

```c
sizeof(Employee)
```

This includes any padding introduced by the compiler for alignment.

---

### 5. Pointer Arithmetic with Multidimensional Arrays

**File:** `5. Pointer Arithmetic with Multidimensional Arrays.c`

Explores pointer arithmetic with multidimensional arrays and explains how pointers move between rows and columns.

**Topics Covered:**

- Memory layout of multidimensional arrays.
- Array-to-pointer conversion for multidimensional arrays.
- Pointers to arrays.
- Moving between rows.
- Moving between columns.
- Accessing elements through pointer arithmetic.
- Relationship between array indexing and pointer expressions.
- Difference between `int (*)[N]` and `int **`.

**Example:**

```c
int matrix[3][4] = {
    {10, 20, 30, 40},
    {50, 60, 70, 80},
    {90, 100, 110, 120}
};

int (*row)[4] = matrix;

printf("%d\n", *(*row + 2)); // 30

row++;

printf("%d\n", *(*row + 2)); // 70
```

**Equivalent Expressions:**

| Array indexing | Pointer expression     |
| -------------- | ---------------------- |
| `matrix[0][0]` | `*(*(matrix + 0) + 0)` |
| `matrix[1][2]` | `*(*(matrix + 1) + 2)` |
| `matrix[2][3]` | `*(*(matrix + 2) + 3)` |

**Important Distinction:**

```c
int (*row)[4];
```

This is a pointer to an array of four integers.

It is not equivalent to:

```c
int **row;
```

A normal multidimensional array stores its rows contiguously. It is not automatically an array of pointers.

---

### 6. Pointer Arithmetic and Byte-Level Memory Access

**File:** `6. Pointer Arithmetic and Byte-Level Memory Access.c`

Explores how to inspect an object's memory representation byte by byte using `unsigned char *`.

**Topics Covered:**

- Object representations.
- Character pointer access to object representations.
- `unsigned char *`.
- Byte-level pointer arithmetic.
- Inspecting individual bytes.
- Modifying an object's representation.
- Relationship between byte order and endianness.
- Difference between typed pointer arithmetic and byte-level traversal.

**Example:**

```c
#include <stdint.h>
#include <stdio.h>

uint32_t number = UINT32_C(0x12345678);

unsigned char *bytes = (unsigned char *)&number;

for (size_t i = 0; i < sizeof(number); i++) {
    printf("%02X\n", (unsigned int)bytes[i]);
}
```

On a little-endian machine with 8-bit bytes, the output is:

```text
78
56
34
12
```

On a big-endian machine, the byte order is reversed.

**Why use `unsigned char *`?**

C permits accessing an object's representation through a character type pointer.

`unsigned char *` is particularly useful because:

- It can inspect any object's representation.
- Each pointer increment advances by one C byte.
- It avoids signed character representation issues when displaying byte values.
- Unlike `void *`, it supports standard pointer arithmetic.

---

### 7. Pointer Arithmetic Restrictions and Undefined Behavior

**File:** `7. Pointer Arithmetic Restrictions and Undefined Behavior.c`

Explores the restrictions imposed on pointer arithmetic and identifies operations that lead to undefined behavior.

**Topics Covered:**

- Valid pointer arithmetic boundaries.
- One-past-the-end pointers.
- Dereferencing invalid pointers.
- Moving beyond array boundaries.
- Moving before an array's beginning.
- Subtracting pointers from unrelated arrays.
- Undefined behavior caused by invalid pointer arithmetic.

**Valid and Invalid Operations:**

| Operation                                  | Validity           |
| ------------------------------------------ | ------------------ |
| `ptr + 1` within an array                  | Valid              |
| `ptr - 1` within an array                  | Valid              |
| `array + array_length`                     | Valid              |
| Dereferencing one-past-the-end             | Undefined behavior |
| Moving beyond one-past-the-end             | Undefined behavior |
| Moving before the first element            | Undefined behavior |
| Subtracting pointers from different arrays | Undefined behavior |

**One-Past-the-End Example:**

```c
int numbers[5] = {10, 20, 30, 40, 50};

int *start = numbers;
int *end = numbers + 5;

for (int *current = start; current != end; current++) {
    printf("%d\n", *current);
}
```

`numbers + 5` is valid to form, even though it does not point to an actual array element.

It acts as a boundary marker for array traversal.

However:

```c
*(numbers + 5); // Undefined behavior
```

The one-past-the-end pointer must never be dereferenced.

---

### 8. Pointer Arithmetic Practical Exercises

**File:** `8. Pointer Arithmetic Practical Exercises.c`

Combines the concepts covered throughout this part into practical pointer manipulation exercises.

**Topics Covered:**

- Forward array traversal.
- Reverse array traversal.
- Pointer offsets.
- Pointer subtraction.
- Calculating array indices.
- Pointer comparisons.
- One-past-the-end boundaries.
- Combining pointer arithmetic operations.

**Example:**

```c
int numbers[] = {12, 24, 36, 48, 60, 72};

int *start = numbers;
int *end = numbers + 6;

// Forward traversal
for (int *current = start; current != end; current++) {
    printf("%d ", *current);
}

// Reverse traversal
for (int *current = end; current != start;) {
    current--;
    printf("%d ", *current);
}
```

The reverse traversal starts at the one-past-the-end pointer and decrements before dereferencing.

This avoids forming a pointer before the beginning of the array.

---

## Key Concepts

### Pointer Arithmetic Scaling

Pointer arithmetic is scaled according to the size of the pointed-to type.

| Pointer type | `ptr + 1` advances by |
| ------------ | --------------------- |
| `char *`     | `sizeof(char)`        |
| `int *`      | `sizeof(int)`         |
| `double *`   | `sizeof(double)`      |
| `Employee *` | `sizeof(Employee)`    |
| `int (*)[4]` | `sizeof(int[4])`      |

### Array Boundaries

For an array containing `N` elements:

| Pointer expression | Meaning                  |
| ------------------ | ------------------------ |
| `array + 0`        | First element            |
| `array + 1`        | Second element           |
| `array + (N - 1)`  | Last element             |
| `array + N`        | One-past-the-end pointer |
| `array + (N + 1)`  | Undefined behavior       |

The one-past-the-end pointer is valid to form and use in permitted comparisons and subtraction, but it cannot be dereferenced.

### Pointer Arithmetic Restrictions

- Pointer arithmetic is permitted within an array object and at its one-past-the-end position.
- Pointer subtraction requires pointers into the same array object or its one-past-the-end position.
- The result of pointer subtraction must be representable by `ptrdiff_t`.
- Relational comparisons are defined for pointers into the same array object, including its one-past-the-end position.
- Standard C does not support arithmetic directly on `void *`.
- `unsigned char *` can be used for byte-level access to object representations.

---

## Tools and Technologies

| Tool                       | Purpose                                  |
| -------------------------- | ---------------------------------------- |
| Clang                      | C compiler                               |
| C11                        | C language standard                      |
| Make                       | Build automation                         |
| AddressSanitizer           | Detects many memory errors               |
| UndefinedBehaviorSanitizer | Detects many forms of undefined behavior |
| VS Code                    | Code editor                              |
| clangd                     | C language server                        |
| LLDB                       | Debugging                                |

---

## Build System

The Makefile provides targets for building, running, sanitizing, and cleaning all exercises.

**Build all exercises:**

```bash
make
```

**Run a specific exercise:**

```bash
make run N=1
```

**Build all exercises with sanitizers:**

```bash
make san
```

**Run an exercise with sanitizers:**

```bash
make run-san N=1
```

**Clean generated files:**

```bash
make clean
```

All generated executables are stored inside the `build/` directory.

## Key Takeaways

By completing this part, the following concepts have been explored:

- Pointer arithmetic is scaled according to the pointed-to type.
- Pointer addition and subtraction operate in element units.
- Pointer subtraction produces an element distance represented by `ptrdiff_t`.
- Pointer comparisons and pointed-to value comparisons are different operations.
- Structure pointers advance by the size of the complete structure.
- Multidimensional arrays use pointers to rows rather than automatically becoming arrays of pointers.
- `unsigned char *` provides a way to inspect object representations byte by byte.
- One-past-the-end pointers are valid boundary markers, but cannot be dereferenced.
- Invalid pointer arithmetic can cause undefined behavior.
