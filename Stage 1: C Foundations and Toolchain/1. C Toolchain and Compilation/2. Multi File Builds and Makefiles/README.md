 <p align="center">
  <strong style="font-size: 1.75em;">Multi-file C Project</strong> <br />
  Exploring multi-file compilation, object files, linking, and automated builds using Clang and Make.
</p>

## Building the Project

The project uses Clang as its compiler and GNU Make to automate the build process.

```bash
make
```

The Makefile compiles each source file independently:

```bash
clang -Iinclude -Wall -Wextra -Wpedantic -g \
    -fsanitize=address,undefined -MMD -MP \
    -c src/main.c -o build/main.o

clang -Iinclude -Wall -Wextra -Wpedantic -g \
    -fsanitize=address,undefined -MMD -MP \
    -c src/calculator.c -o build/calculator.o
```

The resulting object files are linked into the final executable:

```bash
clang build/main.o build/calculator.o -o calculator
```

## Calculator Operations

The calculator supports the following arithmetic operations:

| Operator | Operation      |
| :------: | -------------- |
|   `+`    | Addition       |
|   `-`    | Subtraction    |
|   `*`    | Multiplication |
|   `/`    | Division       |
|   `^`    | Exponentiation |

### Usage

```bash
./calculator <operand1> <operator> <operand2>
```

Examples:

```bash
./calculator -10 + -20
# Result: -30.000000

./calculator 15 - 5
# Result: 10.000000

./calculator 6 '*' 7
# Result: 42.000000

./calculator 2 ^ 3
# Result: 8.000000
```

The multiplication operator is quoted to prevent shell filename expansion.

## Dependency Tracking

The Makefile uses two compiler options to automate dependency management:

- `-MMD`: Generates `.d` files containing header dependencies.
- `-MP`: Adds dummy targets for headers to prevent errors if a header is removed.

These dependency files are included in the Makefile using:

```makefile
-include $(DEPFILES)
```

This allows Make to rebuild only the affected object files when a header changes, rather than recompiling every source file.

## Compiler Flags

| Flag                           | Description                                              |
| ------------------------------ | -------------------------------------------------------- |
| `-Wall`                        | Enables common compiler warnings.                        |
| `-Wextra`                      | Enables additional warnings.                             |
| `-Wpedantic`                   | Reports language-standard portability issues.            |
| `-g`                           | Includes debugging information.                          |
| `-fsanitize=address,undefined` | Enables AddressSanitizer and UndefinedBehaviorSanitizer. |
| `-MMD -MP`                     | Generates automatic header dependency information.       |

## Makefile Commands

| Command      | Description                                 |
| ------------ | ------------------------------------------- |
| `make`       | Builds the calculator.                      |
| `make clean` | Removes generated files and the executable. |
| `make -B`    | Forces a complete rebuild.                  |

## Takeaway

Explored multi-file C project organization, separate compilation, object-file linking, and automated builds using GNU Make. Also implemented automatic header dependency tracking and incremental compilation to avoid unnecessary rebuilds.
