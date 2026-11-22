 <div align="center">
  <h1>Pointer Declarations</h1>
  Exploring pointer declaration syntax, arrays of pointers, pointers to arrays, function pointers, and complex pointer type interpretation in C.
</div><br />

## Part Overview

This part explores how pointers are declared and how their types become more complex when combined with arrays and functions.

It begins with understanding how to read C pointer declarations, followed by arrays of pointers and pointers to arrays. It then introduces function pointer declarations and explores how pointers, arrays, and functions can be combined into more complex types.

The final section focuses on interpreting complex declarations through practical exercises.

The goal is to become comfortable reading, writing, and understanding complex C declarations without confusing arrays of pointers, pointers to arrays, and pointers to functions.

## Topics Covered

### 1. Reading Pointer Declarations

- Understanding C declaration syntax.
- Reading declarations from the identifier outward.
- Understanding operator precedence in declarations.
- Understanding how parentheses affect declaration meaning.
- Distinguishing pointers, arrays, and functions.
- Reading declarations containing multiple pointer operators.
- Understanding how identifiers relate to their declared types.

**Core syntax**

| Declaration           | Meaning                                                              |
| --------------------- | -------------------------------------------------------------------- |
| `int *pointer`        | Pointer to an integer.                                               |
| `int **pointer`       | Pointer to a pointer to an integer.                                  |
| `int pointer[5]`      | Array of 5 integers.                                                 |
| `int *pointer[5]`     | Array of 5 pointers to integers.                                     |
| `int (*pointer)[5]`   | Pointer to an array of 5 integers.                                   |
| `int (*pointer)(int)` | Pointer to a function accepting an integer and returning an integer. |

**Example**

```c
int number = 42;

int *pointer = &number;
int **double_pointer = &pointer;

printf("%d\n", **double_pointer);
```

The declaration `int **double_pointer` describes a pointer to another pointer, which ultimately points to an integer.

Understanding how to read declarations from the identifier outward makes complex pointer types easier to interpret.

### 2. Arrays of Pointers

- Understanding arrays containing pointer elements.
- Declaring and initializing arrays of pointers.
- Assigning different object addresses to array elements.
- Accessing pointer elements using array indexing.
- Dereferencing individual pointer elements.
- Modifying pointed-to objects through array elements.
- Reassigning individual pointer elements.
- Understanding pointer aliasing.
- Working with arrays of string pointers.
- Distinguishing arrays of pointers from pointers to arrays.

**Core syntax**

| Declaration                | Meaning                                     |
| -------------------------- | ------------------------------------------- |
| `int *pointers[3]`         | Array of 3 pointers to integers.            |
| `char *strings[3]`         | Array of 3 pointers to characters.          |
| `const char *languages[3]` | Array of 3 pointers to constant characters. |
| `void *pointers[3]`        | Array of 3 generic object pointers.         |

**Example**

```c
int first = 10;
int second = 20;
int third = 30;

int *pointers[3] = {
    &first,
    &second,
    &third
};

// Access pointed-to objects.
printf("%d\n", *pointers[0]);
printf("%d\n", *pointers[1]);
printf("%d\n", *pointers[2]);

// Modify an object through a pointer.
*pointers[0] = 100;
```

Each element of `pointers` stores an independent pointer value. These pointers can refer to different objects or even the same object.

**Pointer aliasing**

Multiple pointers can refer to the same object.

```c
int number = 10;

int *first_pointer = &number;
int *second_pointer = &number;

*first_pointer = 100;

printf("%d\n", *second_pointer); // 100
```

Modifying an object through one pointer is observable through another pointer that refers to the same object.

### 3. Pointers to Arrays

- Understanding pointers to complete array objects.
- Declaring pointers to arrays.
- Initializing pointers using array addresses.
- Understanding parentheses in pointer-to-array declarations.
- Accessing array elements through pointer-to-array variables.
- Understanding pointer arithmetic with array pointers.
- Comparing pointer-to-array and array-of-pointer declarations.
- Understanding pointers to multidimensional array rows.
- Using `sizeof` with pointers to arrays.

**Core syntax**

| Declaration            | Meaning                               |
| ---------------------- | ------------------------------------- |
| `int (*pointer)[5]`    | Pointer to an array of 5 integers.    |
| `int (*pointer)[3]`    | Pointer to an array of 3 integers.    |
| `int (*pointer)[3][4]` | Pointer to a 3 × 4 array of integers. |
| `char (*pointer)[20]`  | Pointer to an array of 20 characters. |

**Example**

```c
int numbers[5] = {10, 20, 30, 40, 50};

int (*pointer)[5] = &numbers;

// Access elements through the array pointer.
printf("%d\n", (*pointer)[0]);
printf("%d\n", (*pointer)[2]);
printf("%d\n", (*pointer)[4]);
```

The parentheses are important. Without them, `int *pointer[5]` would declare an array of five integer pointers instead.

**Array of pointers vs pointer to array**

| Declaration         | Meaning                                     |
| ------------------- | ------------------------------------------- |
| `int *pointer[5]`   | Array containing 5 integer pointers.        |
| `int (*pointer)[5]` | Pointer to one array containing 5 integers. |

**Pointers to multidimensional arrays**

```c
int matrix[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
};

int (*row_pointer)[3] = matrix;

printf("%d\n", row_pointer[0][1]); // 2
printf("%d\n", row_pointer[1][2]); // 6
```

Here, `row_pointer` points to an array of three integers. Incrementing it advances to the next row.

### 4. Function Pointer Declarations

- Understanding function pointer syntax.
- Declaring pointers to functions.
- Initializing function pointers with function addresses.
- Understanding function pointer type compatibility.
- Calling functions through pointers.
- Understanding function pointer parameters.
- Reassigning function pointers.
- Distinguishing function pointers from object pointers.
- Understanding the difference between pointers to functions and functions returning pointers.

**Core syntax**

| Declaration                           | Meaning                                                                |
| ------------------------------------- | ---------------------------------------------------------------------- |
| `int (*operation)(int, int)`          | Pointer to a function accepting two integers and returning an integer. |
| `void (*callback)(void)`              | Pointer to a function accepting no arguments and returning nothing.    |
| `char *(*function)(void)`             | Pointer to a function returning a character pointer.                   |
| `double (*operation)(double, double)` | Pointer to a function accepting two doubles and returning a double.    |

**Example**

```c
#include <stdio.h>

static int add(int a, int b) {
    return a + b;
}

static int subtract(int a, int b) {
    return a - b;
}

int main(void) {
    int (*operation)(int, int) = add;

    printf("%d\n", operation(10, 5));

    operation = subtract;

    printf("%d\n", operation(10, 5));

    return 0;
}
```

The `operation` variable stores a function pointer. It can be reassigned to another function with a compatible signature.

**Calling through a function pointer**

Both expressions invoke the pointed-to function:

```c
operation(10, 5);

(*operation)(10, 5);
```

Function pointers are useful for callbacks, dispatch tables, event handling, and selecting operations at runtime.

### 5. Complex Pointer Declarations

- Combining pointers and arrays.
- Combining pointers and function types.
- Understanding arrays of function pointers.
- Understanding functions returning pointers.
- Understanding pointers to function pointers.
- Interpreting declarations with multiple levels of indirection.
- Understanding how parentheses change declaration meaning.
- Reading complex declarations from the identifier outward.

**Complex declaration examples**

| Declaration             | Meaning                                                 |
| ----------------------- | ------------------------------------------------------- |
| `int **p`               | Pointer to pointer to integer.                          |
| `int *p[5]`             | Array of 5 pointers to integers.                        |
| `int (*p)[5]`           | Pointer to an array of 5 integers.                      |
| `int (*p)(int, int)`    | Pointer to a function returning integer.                |
| `int (*p[5])(int, int)` | Array of 5 pointers to functions returning integer.     |
| `int *(*p)(int)`        | Pointer to a function returning a pointer to integer.   |
| `char *(*p)(void)`      | Pointer to a function returning a pointer to character. |
| `int (**p)(int, int)`   | Pointer to a function pointer.                          |

**Example: Array of function pointers**

```c
static int add(int a, int b) {
    return a + b;
}

static int subtract(int a, int b) {
    return a - b;
}

int (*operations[2])(int, int) = {
    add,
    subtract
};

printf("%d\n", operations[0](10, 5));
printf("%d\n", operations[1](10, 5));
```

`operations` is an array containing two function pointers. Each function accepts two integers and returns an integer.

**Example: Function returning a pointer**

```c
static char *get_message(void) {
    return "Hello from C";
}

char *(*text_function)(void) = get_message;

printf("%s\n", text_function());
```

Here, `text_function` points to a function that returns a `char *`.

### 6. Declaration Exercises and Type Interpretation

- Interpreting pointer declarations.
- Distinguishing arrays from pointers.
- Distinguishing arrays of pointers from pointers to arrays.
- Interpreting function pointer declarations.
- Understanding pointer-to-pointer declarations.
- Understanding pointer qualifiers.
- Interpreting multidimensional array pointers.
- Reading declarations involving multiple levels of indirection.
- Practising the identifier-outward reading method.

**Declaration exercises**

| Declaration           | Interpretation                                               |
| --------------------- | ------------------------------------------------------------ |
| `int *p`              | Pointer to integer.                                          |
| `int **p`             | Pointer to pointer to integer.                               |
| `int *p[5]`           | Array of 5 pointers to integer.                              |
| `int (*p)[5]`         | Pointer to array of 5 integers.                              |
| `int (*p)(int)`       | Pointer to function accepting integer and returning integer. |
| `int *(*p)(int)`      | Pointer to function returning pointer to integer.            |
| `int (*p[5])(int)`    | Array of 5 pointers to functions.                            |
| `char **argv`         | Pointer to pointer to character.                             |
| `const int *p`        | Pointer to constant integer.                                 |
| `int *const p`        | Constant pointer to integer.                                 |
| `int (*p)[3][4]`      | Pointer to a 3 × 4 array of integers.                        |
| `int (**p)(int, int)` | Pointer to a function pointer.                               |

**Declaration reading strategy**

1. Locate the identifier.
2. Start reading outward from the identifier.
3. Interpret array brackets `[]`.
4. Interpret pointer operators `*`.
5. Interpret function parentheses `()`.
6. Respect parentheses and operator precedence.
7. Continue until the base type is reached.

For example:

```c
int *(*p[3])(double);
```

This declaration describes an array of three pointers to functions that accept a `double` and return a pointer to an integer.

## Key Concepts

| Concept                    | Description                                                                    |
| -------------------------- | ------------------------------------------------------------------------------ |
| Pointer declaration        | Defines a pointer variable and its pointed-to type.                            |
| Array of pointers          | An array whose elements store pointer values.                                  |
| Pointer to array           | A pointer that refers to an entire array object.                               |
| Function pointer           | A pointer that refers to a function with a compatible type.                    |
| Function pointer array     | An array containing multiple function pointers.                                |
| Function returning pointer | A function whose return type is a pointer.                                     |
| Pointer to pointer         | A pointer that stores the address of another pointer.                          |
| Pointer qualifiers         | Qualifiers such as `const` that affect pointer or pointed-to types.            |
| Declaration precedence     | Rules determining how arrays, pointers, and functions combine in declarations. |

## Tools and Technologies

| Tool / Technology          | Purpose                                          |
| -------------------------- | ------------------------------------------------ |
| C (C11)                    | Programming language.                            |
| Clang                      | C compiler.                                      |
| GNU Make                   | Build automation.                                |
| LLDB                       | Inspecting pointer values and program execution. |
| AddressSanitizer           | Detecting invalid memory accesses.               |
| UndefinedBehaviorSanitizer | Detecting undefined behavior.                    |
| Linux                      | Development environment.                         |

## Build System

The individual programs are standalone demonstrations compiled separately using Clang.

**Compiler:** Clang  
**Language Standard:** C11  
**Debug Information:** `-g`  
**Warning Flags:** `-Wall -Wextra -Wpedantic -Wconversion -Wshadow`  
**Sanitizers:** AddressSanitizer and UndefinedBehaviorSanitizer

```bash
# Build all six programs
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

Replace `N=1` with a number from `1` to `6` to select another program.

## Key Takeaways

Developed the ability to read and interpret C declarations involving pointers, arrays, and functions.

Learned the distinction between arrays of pointers and pointers to arrays, how function pointers are declared and invoked, and how multiple pointer, array, and function operators can be combined into complex types.

These concepts provide the foundation for pointer arithmetic, multidimensional arrays, callbacks, and more advanced C programming techniques.
