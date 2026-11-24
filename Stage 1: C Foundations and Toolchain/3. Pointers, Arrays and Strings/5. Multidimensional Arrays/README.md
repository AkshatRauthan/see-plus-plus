 <div align="center">
  <h1>Multidimensional Arrays</h1>
  Exploring multidimensional array structures, row-major and column-major memory layouts, pointer-to-row types, memory offsets, matrix operations, and cache locality in C.
</div><br />

## Part Overview

This part explores multidimensional arrays in C, focusing on how arrays are structured, stored in memory, accessed through pointers, and passed to functions.

It begins with understanding multidimensional array declarations, initialization, indexing, and nested traversal. It then examines how C stores multidimensional arrays using row-major layout, calculating element indexes, byte offsets, and memory addresses.

Column-major storage is introduced separately to compare the two memory layouts and understand how the same logical matrix can be represented using different linear storage arrangements.

The following exercises explore the relationship between arrays of arrays and pointer types, pointer arithmetic across rows, and passing multidimensional arrays to functions. The final exercises combine these concepts through matrix operations, matrix traversal, and the effect of memory access patterns on cache locality and performance.

The goal is to understand multidimensional arrays beyond their syntax, including their underlying memory structure, pointer types, access rules, and relationship with contiguous memory.

## Topics Covered

### 1. Multidimensional Array Fundamentals

- Declaring multidimensional arrays.
- Understanding arrays of arrays.
- Initializing matrices using nested initializer lists.
- Accessing elements using multiple indexes.
- Traversing matrices using nested loops.
- Understanding rows, columns, and dimensions.
- Calculating array dimensions using `sizeof`.
- Understanding matrix element addresses.
- Comparing total array size, row size, and element size.

**Core syntax**

| Declaration            | Meaning                                               |
| ---------------------- | ----------------------------------------------------- |
| `int matrix[3][4]`     | Array containing 3 rows, each with 4 integers.        |
| `int matrix[2][3][4]`  | 3D array containing 2 arrays of 3 rows and 4 columns. |
| `matrix[0][0]`         | Access the first element.                             |
| `matrix[2][3]`         | Access the element in row 2, column 3.                |
| `sizeof(matrix)`       | Total size of the entire matrix.                      |
| `sizeof(matrix[0])`    | Size of one row.                                      |
| `sizeof(matrix[0][0])` | Size of one element.                                  |

**Example**

```c
#include <stdio.h>

int main(void) {
    int matrix[3][4] = {
        {10, 20, 30, 40},
        {50, 60, 70, 80},
        {90, 100, 110, 120}
    };

    size_t rows = sizeof(matrix) / sizeof(matrix[0]);
    size_t columns = sizeof(matrix[0]) / sizeof(matrix[0][0]);

    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < columns; col++) {
            printf("%d ", matrix[row][col]);
        }
        printf("\n");
    }

    return 0;
}
```

A multidimensional array in C is an array whose elements are themselves arrays. In the case of `int matrix[3][4]`, the outer array contains three inner arrays, each containing four integers.

The dimensions determine the structure and the type of the array. The elements are accessed by specifying the indexes of the nested arrays.

---

### 2. Row-Major Memory Layout

- Understanding row-major memory organization.
- Exploring how multidimensional arrays are stored contiguously.
- Understanding the order in which rows occupy memory.
- Calculating linear element indexes.
- Calculating byte offsets.
- Inspecting element addresses.
- Identifying row boundaries.
- Understanding contiguous row storage.
- Exploring object representation through `unsigned char *`.
- Understanding why physical adjacency does not remove pointer arithmetic bounds.

**Core formulas**

| Formula                            | Purpose                                  |
| ---------------------------------- | ---------------------------------------- |
| `row * COLS + col`                 | Calculate the linear element index.      |
| `(row * COLS + col) * sizeof(int)` | Calculate the byte offset of an element. |
| `sizeof(matrix[0])`                | Calculate the size of one row.           |
| `sizeof(matrix)`                   | Calculate the total size of the matrix.  |

**Example**

```c
int matrix[3][4] = {
    {10, 20, 30, 40},
    {50, 60, 70, 80},
    {90, 100, 110, 120}
};

size_t row = 2;
size_t col = 1;

size_t element_index = row * 4 + col;
size_t byte_offset = element_index * sizeof(int);

printf("Element: %d\n", matrix[row][col]);
printf("Index: %zu\n", element_index);
printf("Byte offset: %zu\n", byte_offset);
```

C stores multidimensional arrays in row-major order. The entire first row is stored before the second row, followed by the third row.

For a 3 × 4 matrix containing 4-byte integers, the elements occupy offsets 0, 4, 8, 12, 16, and so on, with each row occupying 16 bytes.

**Row-major memory order**

```text
Row 0: 10 → 20 → 30 → 40
Row 1: 50 → 60 → 70 → 80
Row 2: 90 → 100 → 110 → 120
```

**Byte-level inspection**

```c
unsigned char *base = (unsigned char *)&matrix;
```

Using an `unsigned char *` allows traversal of the object's representation one byte at a time. This is useful for understanding physical storage and byte offsets without performing invalid integer-pointer arithmetic across individual row subarrays.

---

### 3. Column-Major Memory Layout

- Understanding column-major memory organization.
- Comparing row-major and column-major storage.
- Exploring column-by-column linear storage.
- Calculating column-major element indexes.
- Calculating column-major byte offsets.
- Representing a matrix using a flat array.
- Mapping 2D coordinates into 1D storage.
- Reconstructing a matrix from column-major storage.
- Understanding that C's native multidimensional arrays remain row-major.
- Exploring storage layouts used by other programming languages and numerical libraries.

**Core formulas**

| Formula                            | Purpose                                  |
| ---------------------------------- | ---------------------------------------- |
| `col * ROWS + row`                 | Calculate the column-major linear index. |
| `(col * ROWS + row) * sizeof(int)` | Calculate the byte offset.               |
| `int storage[ROWS * COLS]`         | Represent the matrix using flat storage. |

**Example**

```c
#define ROWS 3
#define COLS 4

int matrix[ROWS][COLS] = {
    {10, 20, 30, 40},
    {50, 60, 70, 80},
    {90, 100, 110, 120}
};

int columnMajor[ROWS * COLS];

for (size_t col = 0; col < COLS; col++) {
    for (size_t row = 0; row < ROWS; row++) {
        size_t index = col * ROWS + row;

        columnMajor[index] = matrix[row][col];
    }
}
```

Unlike row-major storage, column-major storage places the elements of each column consecutively in the linear array.

**Column-major memory order**

```text
Column 0: 10 → 50 → 90
Column 1: 20 → 60 → 100
Column 2: 30 → 70 → 110
Column 3: 40 → 80 → 120
```

The resulting linear sequence is:

```text
10, 50, 90, 20, 60, 100, 30, 70, 110, 40, 80, 120
```

C does not change its native storage layout to column-major. Instead, the exercise uses a flat array and an explicit indexing formula to demonstrate how column-major representation works.

---

### 4. Array-of-Arrays and Pointer Types

- Understanding multidimensional arrays as nested array types.
- Understanding array-to-pointer decay in multidimensional arrays.
- Identifying the type of `matrix`.
- Identifying the type of `matrix[0]`.
- Identifying the type of `&matrix`.
- Declaring pointers to rows.
- Declaring pointers to complete multidimensional arrays.
- Comparing pointer-to-row and element-pointer arithmetic.
- Understanding pointer sizes versus pointed-to object sizes.
- Distinguishing multidimensional arrays from `int **`.

**Core syntax**

| Declaration                  | Meaning                                            |
| ---------------------------- | -------------------------------------------------- |
| `int matrix[3][4]`           | Array of 3 arrays of 4 integers.                   |
| `int (*rowPtr)[4]`           | Pointer to an array of 4 integers.                 |
| `int *elementPtr`            | Pointer to an individual integer.                  |
| `int (*wholeArrayPtr)[3][4]` | Pointer to an entire 3 × 4 array.                  |
| `matrix`                     | Decays to a pointer to its first row.              |
| `matrix[0]`                  | Decays to a pointer to the first element of row 0. |
| `&matrix`                    | Pointer to the complete matrix.                    |

**Example**

```c
int matrix[3][4] = {
    {10, 20, 30, 40},
    {50, 60, 70, 80},
    {90, 100, 110, 120}
};

int (*rowPtr)[4] = matrix;
int *elementPtr = matrix[0];
int (*wholeArrayPtr)[3][4] = &matrix;

printf("%d\n", rowPtr[1][2]);
printf("%d\n", *(elementPtr + 2));
printf("%d\n", (*wholeArrayPtr)[2][3]);
```

The declaration `int (*rowPtr)[4]` describes a pointer to a row containing four integers. Pointer arithmetic on it advances by an entire row rather than by an individual integer.

A multidimensional array is not interchangeable with `int **`. A true 2D array contains its nested arrays directly in contiguous storage, while a pointer-to-pointer represents a pointer that leads to other pointer objects.

---

### 5. Pointer Arithmetic Across Rows

- Understanding pointer arithmetic with multidimensional arrays.
- Advancing pointer-to-row variables.
- Advancing individual element pointers.
- Calculating row offsets.
- Understanding pointer scaling.
- Accessing rows through pointer arithmetic.
- Traversing matrices using pointers.
- Understanding the relationship between `rowPtr + row` and `rowPtr[row]`.
- Respecting array boundaries and one-past pointers.
- Understanding the restrictions of pointer arithmetic across nested arrays.

**Core syntax**

| Expression               | Meaning                                   |
| ------------------------ | ----------------------------------------- |
| `rowPtr + 1`             | Advance by one complete row.              |
| `rowPtr + row`           | Point to a particular row.                |
| `*(rowPtr + row)`        | Access the row array.                     |
| `(*(rowPtr + row))[col]` | Access a column within the selected row.  |
| `rowPtr[row][col]`       | Access an element using pointer indexing. |
| `matrix[0] + 4`          | One-past the first row.                   |
| `matrix + 3`             | One-past the outer array of three rows.   |

**Example**

```c
int matrix[3][4] = {
    {10, 20, 30, 40},
    {50, 60, 70, 80},
    {90, 100, 110, 120}
};

int (*rowPtr)[4] = matrix;

for (size_t row = 0; row < 3; row++) {
    for (size_t col = 0; col < 4; col++) {
        printf("%d ", (*(rowPtr + row))[col]);
    }
    printf("\n");
}
```

Because `rowPtr` is a pointer to a four-element integer array, advancing it by one moves to the next row. The inner indexing operates within the selected row.

Pointer arithmetic is still constrained by the array object being traversed. Physical adjacency between rows does not permit an `int *` to move outside the bounds of its individual row subarray.

---

### 6. Passing Multidimensional Arrays to Functions

- Passing multidimensional arrays to functions.
- Understanding parameter type adjustment.
- Specifying column dimensions in function parameters.
- Passing row counts separately.
- Accessing matrix elements within functions.
- Traversing matrices through pointer-to-row parameters.
- Modifying matrix contents through function parameters.
- Understanding `sizeof` on array parameters.
- Comparing array sizes in caller and callee scopes.
- Using `const` with multidimensional array parameters.

**Core syntax**

| Declaration                                       | Meaning                                                    |
| ------------------------------------------------- | ---------------------------------------------------------- |
| `void PrintMatrix(int matrix[][4], size_t rows)`  | Accepts a matrix with 4 columns.                           |
| `void PrintMatrix(int (*matrix)[4], size_t rows)` | Equivalent pointer-to-row parameter form.                  |
| `const int matrix[][4]`                           | Matrix elements cannot be modified through this parameter. |
| `sizeof(matrix)` inside function                  | Size of the adjusted pointer parameter.                    |
| `sizeof(matrix[0])` inside function               | Size of one row.                                           |

**Example**

```c
#define COLS 4

void PrintMatrix(const int matrix[][COLS], size_t rows) {
    for (size_t row = 0; row < rows; row++) {
        for (size_t col = 0; col < COLS; col++) {
            printf("%d ", matrix[row][col]);
        }
        printf("\n");
    }
}
```

When a multidimensional array is passed to a function, the outermost array dimension is adjusted to a pointer parameter. The column dimension must still be known so the compiler can calculate the correct row stride.

The number of rows is passed separately because the function parameter no longer retains the outer array's original size.

---

### 7. Multidimensional Array Practical Exercises

- Printing matrices.
- Traversing matrices using pointer-to-row variables.
- Calculating the sum of all elements.
- Calculating individual row sums.
- Calculating individual column sums.
- Searching for matrix elements.
- Modifying matrix values.
- Transposing matrices.
- Accessing elements through pointer-to-row declarations.
- Comparing matrix and row sizes.
- Combining array indexing, nested loops, and pointer arithmetic.

**Core operations**

| Operation         | Description                                      |
| ----------------- | ------------------------------------------------ |
| Matrix printing   | Display elements using nested loops.             |
| Matrix sum        | Calculate the sum of all elements.               |
| Row sums          | Calculate the sum of each row.                   |
| Column sums       | Calculate the sum of each column.                |
| Search            | Locate a target value.                           |
| Modification      | Change elements using a specified value.         |
| Transpose         | Convert rows into columns and columns into rows. |
| Pointer traversal | Access elements using pointer-to-row variables.  |

**Example: Matrix Transposition**

```c
int matrix[3][4] = {
    {10, 20, 30, 40},
    {50, 60, 70, 80},
    {90, 100, 110, 120}
};

int transpose[4][3];

for (size_t row = 0; row < 3; row++) {
    for (size_t col = 0; col < 4; col++) {
        transpose[col][row] = matrix[row][col];
    }
}
```

Transposition changes the logical arrangement of the elements. The original matrix has three rows and four columns, while the transposed matrix has four rows and three columns.

---

### 8. Matrix Traversal and Cache Locality

- Understanding traversal order.
- Comparing row-wise and column-wise traversal.
- Connecting traversal order with row-major storage.
- Understanding memory stride.
- Exploring sequential versus non-sequential memory access.
- Introducing cache locality.
- Understanding spatial locality.
- Exploring why contiguous memory access is generally more cache-friendly.
- Comparing traversal performance through benchmarking.
- Understanding the influence of memory access patterns on performance.
- Using compiler optimizations when measuring performance.

**Traversal patterns**

| Traversal   | Access pattern                                               | Memory behavior in C                    |
| ----------- | ------------------------------------------------------------ | --------------------------------------- |
| Row-wise    | `matrix[row][col]`, with columns changing in the inner loop. | Sequential element access.              |
| Column-wise | `matrix[row][col]`, with rows changing in the inner loop.    | Larger memory strides between accesses. |

**Example**

```c
/* Row-wise traversal */
for (size_t row = 0; row < ROWS; row++) {
    for (size_t col = 0; col < COLS; col++) {
        sum += matrix[row][col];
    }
}

/* Column-wise traversal */
for (size_t col = 0; col < COLS; col++) {
    for (size_t row = 0; row < ROWS; row++) {
        sum += matrix[row][col];
    }
}
```

Both loops visit the same logical elements and produce the same sum. However, their access patterns differ.

C stores matrix elements consecutively across each row. Row-wise traversal therefore accesses neighboring elements in memory, while column-wise traversal jumps between rows.

For a matrix with 2048 columns and 4-byte integers, accessing the same column in consecutive rows produces an 8192-byte stride:

\[
2048 \times 4 = 8192 \text{ bytes}
\]

This introduces the concept of cache locality. A cache line brings a block of neighboring memory into the CPU cache. Accessing adjacent elements makes better use of that fetched data, whereas large strides can result in less effective cache utilization.

**Benchmarking**

The exercise uses `clock()` from `<time.h>` to measure CPU time consumed by each traversal.

```c
clock_t start = clock();

/* Code being measured */

clock_t end = clock();

double elapsed =
    (double)(end - start) / CLOCKS_PER_SEC;
```

| Function / Macro | Purpose                                          |
| ---------------- | ------------------------------------------------ |
| `clock()`        | Returns the approximate processor time consumed. |
| `clock_t`        | Type used to store clock ticks.                  |
| `CLOCKS_PER_SEC` | Converts clock ticks into seconds.               |

The benchmark:

- Initializes a 2048 × 2048 integer matrix.
- Runs row-wise traversal five times.
- Runs column-wise traversal five times.
- Accumulates checksums to ensure the results are used.
- Compares the measured CPU times.
- Calculates the column-wise to row-wise time ratio.

Both traversal methods should produce the same checksum. Their execution times may differ depending on the processor, cache hierarchy, compiler, optimization level, and system load.

For meaningful performance measurements, compile with optimization enabled:

```bash
make run-opt N=8
```

This uses `-O2` in addition to the regular compiler flags. Benchmark timings are machine-dependent and should not be treated as fixed expected values.

---

## Key Concepts

| Concept                | Description                                                                                      |
| ---------------------- | ------------------------------------------------------------------------------------------------ |
| Multidimensional array | Array containing nested arrays as elements.                                                      |
| Matrix                 | Common representation of a two-dimensional array.                                                |
| Row-major layout       | Storage arrangement where each row is stored consecutively.                                      |
| Column-major layout    | Storage arrangement where each column is stored consecutively.                                   |
| Linear index           | Index representing an element within flat storage.                                               |
| Byte offset            | Distance in bytes from a storage base address.                                                   |
| Array-of-arrays        | The actual structure of native multidimensional C arrays.                                        |
| Pointer-to-row         | Pointer to a complete row array.                                                                 |
| Row stride             | Memory distance between the starts of consecutive rows.                                          |
| Pointer scaling        | Pointer arithmetic advances in units of the pointed-to type.                                     |
| Array decay            | Conversion of an array expression to a pointer to its first element in most expression contexts. |
| Matrix transpose       | Operation that exchanges row and column positions.                                               |
| Cache locality         | Property of accessing memory locations close together in time or address.                        |
| Spatial locality       | Tendency to access nearby memory locations.                                                      |
| Memory stride          | Distance between consecutive memory accesses.                                                    |
| Cache line             | A block of memory transferred between memory and cache.                                          |
| Cache hit              | Requested data is found in cache.                                                                |
| Cache miss             | Requested data must be fetched into cache.                                                       |

## Tools and Technologies

| Tool / Technology          | Purpose                                                          |
| -------------------------- | ---------------------------------------------------------------- |
| C (C11)                    | Programming language.                                            |
| Clang                      | Compiler for building standalone programs.                       |
| GNU Make                   | Automating compilation and execution.                            |
| LLDB                       | Inspecting addresses, pointer values, and array layout.          |
| AddressSanitizer           | Detecting invalid memory accesses.                               |
| UndefinedBehaviorSanitizer | Detecting undefined behavior.                                    |
| `clock()`                  | Measuring CPU execution time.                                    |
| `-O2`                      | Enabling compiler optimizations for performance-oriented builds. |
| Linux                      | Development environment.                                         |

## Build System

The individual programs are standalone demonstrations compiled separately using Clang.

**Compiler:** Clang  
**Language Standard:** C11  
**Debug Information:** `-g`  
**Warning Flags:** `-Wall -Wextra -Wpedantic -Wconversion -Wshadow`  
**Sanitizers:** AddressSanitizer and UndefinedBehaviorSanitizer

### Build all programs

```bash
make
```

or

```bash
make build
```

### Run a specific exercise

```bash
make run N=1
make run N=2
make run N=3
make run N=4
make run N=5
make run N=6
make run N=7
make run N=8
```

### Run the cache locality benchmark with optimization

```bash
make run-opt N=8
```

This adds `-O2` to the regular compiler flags and creates an optimized executable with the `-opt` suffix inside `build/`.

### Build all programs with sanitizers

```bash
make san
```

### Run a specific program with sanitizers

```bash
make run-san N=1
make run-san N=2
make run-san N=3
make run-san N=4
make run-san N=5
make run-san N=6
make run-san N=7
make run-san N=8
```

### Clean generated files

```bash
make clean
```

## Key Takeaways

Developed a deeper understanding of multidimensional arrays in C, including their nested array structure, contiguous storage, row-major layout, and relationship with pointers.

Learned how to calculate linear indexes, byte offsets, and row boundaries; compare row-major and column-major storage; declare and use pointers to array rows; pass multidimensional arrays to functions; and perform matrix operations using nested loops and pointer arithmetic.

Also explored how memory traversal patterns affect access behavior, introducing cache locality, spatial locality, memory stride, and the importance of sequential memory access for performance.

These concepts provide the foundation for working with matrices, multidimensional data, memory layouts, pointer-based algorithms, and performance-aware systems programming.
