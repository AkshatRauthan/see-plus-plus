<div align="center">
  <h1>Pointer Fundamentals</h1>
  Exploring memory addresses, pointer declarations, dereferencing, pointer types, generic pointers, null pointers, and pointer sizes in C.
</div><br />

## Part Overview

This part introduces pointers, one of the most important concepts in C programming.

It begins with understanding how variables occupy memory and how their addresses can be retrieved. It then explores pointer declarations, initialization, dereferencing, and modifying variables through pointers.

The remaining topics cover pointer types, generic pointers, null pointers, and the relationship between pointer sizes and the `sizeof` operator.

The goal is to understand how pointers represent addresses, how they provide access to objects, and how they enable functions to interact with memory indirectly.

## Topics Covered

### 1. Memory Addresses

- Understanding how variables are stored in memory.
- Understanding object addresses.
- Retrieving addresses using the address-of operator.
- Printing memory addresses using `%p`.
- Understanding object sizes using `sizeof`.
- Distinguishing variable values from their memory addresses.

**Core operators and expressions**

| Operator / Expression | Purpose |
| --------------------- | ------- |
| `&variable` | Retrieves the address of a variable. |
| `sizeof(variable)` | Retrieves the size of an object in bytes. |
| `%p` | Formats a pointer value for output. |

**Example**

```c
#include <stdio.h>

int main(void) {
    int number = 42;

    printf("Value: %d\n", number);
    printf("Address: %p\n", (void *)&number);
    printf("Size: %zu bytes\n", sizeof(number));

    return 0;
}
```

A variable has a value, occupies storage, and has an address. Understanding this distinction provides the foundation for working with pointers.

### 2. Pointer Declaration and Initialization

- Understanding pointer declaration syntax.
- Declaring pointers to different types.
- Initializing pointers with object addresses.
- Separating declaration and initialization.
- Reassigning pointers.
- Understanding uninitialized pointers.
- Understanding how pointer variables store addresses.

**Core syntax**

| Declaration | Meaning |
| ----------- | ------- |
| `int *pointer` | Pointer to an integer. |
| `char *pointer` | Pointer to a character. |
| `float *pointer` | Pointer to a float. |
| `double *pointer` | Pointer to a double. |

**Example**

```c
int number = 42;

// Initialize a pointer with number's address.
int *pointer = &number;

// Reassign the pointer to another object.
int another_number = 100;
pointer = &another_number;
```

A pointer must be initialized with a valid address or a null pointer value before it is used. An uninitialized pointer contains an indeterminate value.

### 3. Address-of Operator (`&`)

- Understanding the address-of operator.
- Retrieving object addresses.
- Understanding the types of address expressions.
- Matching pointer types with object types.
- Comparing addresses and pointer values.
- Passing addresses to functions.
- Understanding address-of operator restrictions.

**Example**

```c
int number = 42;

int *pointer = &number;
```

`&number` produces the address of `number`. Its type is `int *`, which is compatible with the declared pointer.

The address-of operator is also commonly used with functions such as `scanf()`, where the function needs an address at which to store a converted value.

### 4. Dereference Operator (`*`)

- Understanding pointer dereferencing.
- Accessing objects through pointers.
- Reading values through pointers.
- Modifying pointed-to objects.
- Understanding dereferenced expressions.
- Dereferencing different pointer types.
- Identifying invalid pointer dereferencing.

**Example**

```c
int number = 42;
int *pointer = &number;

// Read the pointed-to value.
printf("%d\n", *pointer);

// Modify the original object.
*pointer = 100;
```

The dereference operator accesses the object designated by a valid pointer. It can be used both to read and modify an object, provided the object is modifiable.

### 5. Modifying Variables Through Pointers

- Understanding pass-by-value in C.
- Passing addresses to functions.
- Using pointer parameters.
- Modifying caller-owned variables.
- Modifying multiple variables through pointers.
- Understanding output parameters.
- Validating pointer arguments.

**Example: Modifying a variable through a function**

```c
#include <stdio.h>

static void increment(int *value) {
    if (value == NULL) {
        return;
    }

    (*value)++;
}

int main(void) {
    int number = 10;

    increment(&number);

    printf("Number: %d\n", number);

    return 0;
}
```

C passes arguments by value, including pointers. However, when a copied pointer refers to the caller's object, dereferencing it allows the function to modify that original object.

### 6. Pointer Types

- Understanding typed pointers.
- Pointers to different object types.
- Pointer and object type compatibility.
- Dereferencing typed pointers.
- Incompatible pointer assignments.
- Understanding why explicit casts do not guarantee valid memory access.
- Distinguishing object pointers from function pointers.

**Common pointer types**

| Type | Points to |
| ---- | --------- |
| `int *` | Integer objects. |
| `char *` | Character objects. |
| `float *` | Float objects. |
| `double *` | Double objects. |
| `void *` | Objects of unspecified type. |

A pointer's type determines how the compiler interprets the pointed-to object when dereferencing it.

### 7. Generic Pointers (`void *`)

- Understanding generic object pointers.
- Assigning addresses of different object types.
- Converting between object pointers and `void *`.
- Dereferencing generic pointers through appropriate types.
- Using generic pointers in reusable functions.
- Understanding `const void *`.
- Understanding restrictions on generic pointers.
- Distinguishing object pointers from function pointers.

**Example**

```c
int number = 42;

// Store an integer address in a generic pointer.
void *pointer = &number;

// Convert back to the appropriate object pointer type.
int *integer_pointer = pointer;

printf("%d\n", *integer_pointer);
```

A `void *` can hold the address of an object of different types. However, it cannot be directly dereferenced or used for standard C pointer arithmetic because `void` does not describe an object size.

Generic pointers are widely used in standard library interfaces such as `memcpy()`, `memmove()`, `qsort()`, and `bsearch()`.

### 8. Null Pointers (`NULL`)

- Understanding null pointer values.
- Initializing pointers with `NULL`.
- Checking pointer values.
- Null pointers versus uninitialized pointers.
- Null pointers versus integer zero and `'\0'`.
- Returning `NULL` from functions.
- Using optional pointer parameters.
- Resetting pointers.
- Static and automatic pointer initialization.
- Understanding null pointer representations.

**Example**

```c
#include <stddef.h>
#include <stdio.h>

int main(void) {
    int *pointer = NULL;

    if (pointer == NULL) {
        puts("Pointer does not refer to an object.");
    }

    return 0;
}
```

A null pointer does not designate an object or function. It must not be dereferenced.

An important distinction is that a null pointer is initialized, whereas an uninitialized automatic pointer has an indeterminate value.

### 9. Pointer Sizes and `sizeof`

- Understanding pointer storage size.
- Comparing sizes of different object pointer types.
- Understanding `sizeof(pointer)`.
- Understanding `sizeof(*pointer)`.
- Pointer size versus pointed-to object size.
- Array size versus pointer size.
- Calculating array lengths using `sizeof`.
- Understanding array parameters and pointer adjustment.
- Recognizing implementation-dependent pointer sizes.

**Example**

```c
#include <stdio.h>

int main(void) {
    int number = 42;
    int *pointer = &number;

    printf("Pointer size: %zu bytes\n", sizeof(pointer));
    printf("Object size: %zu bytes\n", sizeof(*pointer));

    return 0;
}
```

`sizeof(pointer)` retrieves the size of the pointer variable, while `sizeof(*pointer)` retrieves the size of the pointed-to integer object.

The size of a pointer is implementation-dependent and should not be assumed from the size of the object it references.

## Key Concepts

| Concept | Description |
| ------- | ----------- |
| Object address | Identifies the memory location of an object. |
| Pointer | An object that stores a pointer value. |
| Address-of | Produces a pointer to an object. |
| Dereferencing | Accesses the object designated by a pointer. |
| Typed pointer | A pointer associated with a particular pointed-to type. |
| Generic pointer | A `void *` capable of holding an object pointer. |
| Null pointer | A pointer value that does not designate an object or function. |
| Pointer size | Storage required by a pointer object. |

## Tools and Technologies

| Tool / Technology | Purpose |
| ----------------- | ------- |
| C (C11) | Programming language. |
| Clang | C compiler. |
| GNU Make | Build automation. |
| LLDB | Inspecting pointer values and program memory. |
| AddressSanitizer | Detecting invalid memory accesses. |
| UndefinedBehaviorSanitizer | Detecting undefined behavior. |
| Linux | Development environment. |

## Build System

The individual programs are standalone demonstrations compiled separately using Clang.

**Compiler:** Clang  
**Language Standard:** C11  
**Debug Information:** `-g`  
**Warning Flags:** `-Wall -Wextra -Wpedantic -Wconversion -Wshadow`  
**Sanitizers:** AddressSanitizer and UndefinedBehaviorSanitizer

```bash
# Build all nine programs
make

# Build and execute a specific program
make run N=1

# Build all programs with sanitizers
make san

# Build with sanitizers and execute a specific program
make run-san N=1

# Remove generated executables
make clean
```

Replace `N=1` with a number from `1` to `9` to select another program.


## Key Takeaways

Developed an understanding of how C represents memory addresses and how pointers provide indirect access to objects.

Learned to declare, initialize, and dereference pointers, modify caller-owned variables through pointer parameters, work with different pointer types, and use generic pointers for reusable operations.

Explored null pointer handling, pointer initialization, and the relationship between pointer storage and pointed-to object sizes.

These concepts provide the foundation for pointer arithmetic, arrays, multidimensional arrays, strings, memory operations, and function-pointer callbacks in the remaining parts of Module 1.3.
