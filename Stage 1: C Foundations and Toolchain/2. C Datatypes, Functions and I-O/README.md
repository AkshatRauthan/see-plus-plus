<div align="center">
  <h1>Module 2: C Datatypes, Functions and I/O</h1>
  Exploring C data types, integer representations, bitwise operations, type conversions, file handling, and command-line application development.
</div><br />

<div align="center">
  <img src="https://img.shields.io/badge/Started_On-17_Nov_2026-2EA44F?style=for-the-badge&logo=calendar&logoColor=white" alt="Started On" />
  <img src="https://img.shields.io/badge/Progress-Completed-FF69A0?style=for-the-badge&logo=progress&logoColor=white" alt="Progress" />
  <img src="https://img.shields.io/badge/Completed_On-20_Nov_2026-2976BB?style=for-the-badge&logo=checkmarx&logoColor=white" alt="Completed On" />
</div>

## Module Overview

This module focuses on understanding how C represents, converts, manipulates, and processes data.

It begins with fundamental and fixed-width integer types, explores integer promotions and arithmetic conversions, and progresses into bitwise operations and endianness.

The concepts are then applied through Bitview, a command-line project for examining integer representations and performing bit-level operations. The remaining parts explore numeric conversion utilities, file handling, and command-line argument parsing.

It is divided into six parts:

| Part | Topic                             | Description                                                                                                                              |
| ---- | --------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------- |
| 1    | Data Types and Integer Conversion | Understanding fundamental and fixed-width integer types, integer promotions, arithmetic conversions, and signed and unsigned arithmetic. |
| 2    | Bitwise Operations and Endianness | Exploring bitwise operators, bit manipulation, integer representations, and byte ordering.                                               |
| 3    | Project: Bitview                  | Building a command-line utility for inspecting integer representations and performing bit-level operations.                              |
| 4    | Integer Conversions               | Implementing integer and floating-point conversions between numeric values and strings.                                                  |
| 5    | File Operations                   | Working with text and binary files, file positioning, buffered copying, hexdumps, and error handling.                                    |
| 6    | CLI and Argument Parsing          | Implementing custom argument parsing, POSIX `getopt()`, numeric validation, and command dispatching.                                     |

## Topics Covered

### 1. Data Types and Integer Conversion

Explored how C represents integer values and how the language handles conversions between different integer types.

- Understanding fundamental integer types.
- Signed and unsigned integer types.
- Integer widths and value ranges.
- Fixed-width integer types from `<stdint.h>`.
- Exact-width, minimum-width, and fastest-width integer types.
- Integer promotions.
- Usual arithmetic conversions.
- Implicit and explicit type conversions.
- Signed integer overflow.
- Unsigned integer arithmetic and wraparound.
- Integer conversion rules and their consequences.

**Core types and definitions**

| Type / Macro                                  | Purpose                                                                   |
| --------------------------------------------- | ------------------------------------------------------------------------- |
| `char`, `short`, `int`, `long`, `long long`   | Fundamental integer types.                                                |
| `unsigned`                                    | Represents non-negative integer values.                                   |
| `int8_t`, `int16_t`, `int32_t`, `int64_t`     | Exact-width signed integer types when provided by the implementation.     |
| `uint8_t`, `uint16_t`, `uint32_t`, `uint64_t` | Exact-width unsigned integer types when provided by the implementation.   |
| `int_fastN_t`                                 | Integer type providing at least N bits with preference for speed.         |
| `int_leastN_t`                                | Integer type providing at least N bits with minimum storage requirements. |
| `INT32_MAX`, `INT64_MIN`                      | Integer limit macros.                                                     |

**Core concepts**

| Concept                      | Purpose                                                                           |
| ---------------------------- | --------------------------------------------------------------------------------- |
| Integer promotions           | Convert certain integer types to `int` or `unsigned int` before operations.       |
| Usual arithmetic conversions | Determine a common type for arithmetic operands.                                  |
| Implicit conversion          | Automatically converts a value between types.                                     |
| Explicit conversion          | Uses a cast to request a conversion.                                              |
| Signed overflow              | An unrepresentable result of signed integer arithmetic causes undefined behavior. |
| Unsigned arithmetic          | Arithmetic is performed modulo one more than the maximum representable value.     |

**Key takeaways**

- C integer types do not all have the same width or range.
- Fixed-width types are useful when an exact number of bits is required.
- Integer promotions can change the type in which an arithmetic operation is performed.
- The usual arithmetic conversions determine how mixed-type expressions are evaluated.
- Signed overflow and unsigned wraparound have fundamentally different behavior.
- Explicit casts do not automatically make an otherwise unsafe conversion valid.

### 2. Bitwise Operations and Endianness

Explored how integer values are represented at the bit level and how individual bits can be examined and manipulated.

- Understanding binary integer representation.
- Bitwise AND (`&`).
- Bitwise OR (`|`).
- Bitwise XOR (`^`).
- Bitwise NOT (`~`).
- Left shift (`<<`).
- Right shift (`>>`).
- Constructing bit masks.
- Setting individual bits.
- Clearing individual bits.
- Toggling individual bits.
- Testing individual bits.
- Extracting bit fields.
- Understanding signed and unsigned bitwise operations.
- Understanding logical and arithmetic right shifts.
- Exploring integer byte representations.
- Understanding little-endian and big-endian byte ordering.
- Inspecting memory representations.

**Core operators**

| Operator | Name        | Purpose                                                         |
| -------- | ----------- | --------------------------------------------------------------- |
| `&`      | Bitwise AND | Sets a result bit when both corresponding operand bits are set. |
| `\|`     | Bitwise OR  | Sets a result bit when either corresponding operand bit is set. |
| `^`      | Bitwise XOR | Sets a result bit when corresponding operand bits differ.       |
| `~`      | Bitwise NOT | Inverts the bits of its operand.                                |
| `<<`     | Left shift  | Shifts bits toward higher bit positions.                        |
| `>>`     | Right shift | Shifts bits toward lower bit positions.                         |

**Common bit manipulation techniques**

| Operation    | Expression                   |
| ------------ | ---------------------------- | ------------------- |
| Set bit      | `value                       | = (1u << position)` |
| Clear bit    | `value &= ~(1u << position)` |
| Toggle bit   | `value ^= (1u << position)`  |
| Test bit     | `(value >> position) & 1u`   |
| Extract bits | `(value >> offset) & mask`   |

**Understanding endianness**

Endianness describes the order in which the bytes of a multi-byte value are stored in memory.

| Byte order    | Description                                                     |
| ------------- | --------------------------------------------------------------- |
| Little-endian | Stores the least significant byte at the lowest memory address. |
| Big-endian    | Stores the most significant byte at the lowest memory address.  |

For example, consider the 32-bit hexadecimal value:

```text
0x12345678
```

Its byte representation differs depending on the byte order:

```text
Big-endian:
Address →  0x00  0x01  0x02  0x03
Bytes   →   12    34    56    78

Little-endian:
Address →  0x00  0x01  0x02  0x03
Bytes   →   78    56    34    12
```

**Key takeaways**

- Bitwise operators work directly with integer representations.
- Bit masks provide a convenient way to manipulate specific bits.
- Shifts are useful for extracting and positioning bit fields.
- Signed and unsigned operands can behave differently during bitwise operations.
- Endianness describes byte ordering in memory, not the order in which bits are displayed within a byte.
- Understanding byte order is important when processing binary formats, network protocols, and low-level data.

### 3. Project: Bitview

Developed Bitview, a command-line utility that brings together integer representation, type handling, and bitwise manipulation concepts.

The project applies the concepts explored in the previous parts through reusable C modules, command handling, and a structured command-line interface.

**Core functionality**

- Representing signed and unsigned integer values.
- Handling different integer widths.
- Inspecting integer representations.
- Displaying hexadecimal and binary representations.
- Examining individual bits.
- Performing bit-level analysis.
- Manipulating integer bits.
- Separating parsing, data representation, and command execution.
- Organizing functionality into reusable source and header files.
- Testing individual components.

**Project architecture**

The implementation separates its responsibilities into distinct components:

| Component             | Responsibility                                       |
| --------------------- | ---------------------------------------------------- |
| Integer module        | Handles integer values and their representations.    |
| Floating-point module | Handles floating-point representation functionality. |
| Parser module         | Processes command-line input.                        |
| CLI module            | Provides application-level command-line handling.    |
| Command modules       | Implement individual application commands.           |
| Main module           | Acts as the program entry point.                     |

**Key takeaways**

- Applied integer representation and bitwise concepts in a practical application.
- Practiced separating declarations and implementations.
- Used structures and enumerations to organize different integer types.
- Built reusable functions for inspecting and manipulating values.
- Applied modular source organization and command dispatching.
- Combined multiple concepts from earlier parts into one application.

### 4. Integer Conversions

Explored how numeric values are converted into strings and how strings are converted back into numeric values.

The implementations cover both integer and floating-point conversions, including validation, range checking, and buffer management.

**Topics covered**

- Integer-to-string conversion.
- String-to-integer conversion.
- Floating-point-to-string conversion.
- String-to-floating-point conversion.
- Signed and unsigned conversions.
- Different integer widths.
- Numeric base handling.
- Buffer capacity validation.
- Null-terminated string handling.
- Invalid input detection.
- Overflow and underflow handling.
- End-pointer validation.
- Manual integer-to-string conversion.

**Core functions**

| Function      | Purpose                                                 |
| ------------- | ------------------------------------------------------- |
| `snprintf()`  | Formats numeric values into bounded character buffers.  |
| `strtoimax()` | Converts strings into the widest signed integer type.   |
| `strtoumax()` | Converts strings into the widest unsigned integer type. |
| `strtof()`    | Converts strings into `float` values.                   |
| `strtod()`    | Converts strings into `double` values.                  |
| `strtold()`   | Converts strings into `long double` values.             |

**Project functions**

| Function                 | Purpose                                                         |
| ------------------------ | --------------------------------------------------------------- |
| `format_i32()`           | Formats a signed 32-bit integer.                                |
| `format_u32()`           | Formats an unsigned 32-bit integer.                             |
| `format_i64()`           | Formats a signed 64-bit integer.                                |
| `format_u64()`           | Formats an unsigned 64-bit integer.                             |
| `format_f32()`           | Formats a `float` value.                                        |
| `format_f64()`           | Formats a `double` value.                                       |
| `format_fld()`           | Formats a `long double` value.                                  |
| `parse_i32()`            | Parses a signed 32-bit integer.                                 |
| `parse_u32()`            | Parses an unsigned 32-bit integer.                              |
| `parse_i64()`            | Parses a signed 64-bit integer.                                 |
| `parse_u64()`            | Parses an unsigned 64-bit integer.                              |
| `parse_f32()`            | Parses a `float` value.                                         |
| `parse_f64()`            | Parses a `double` value.                                        |
| `parse_fld()`            | Parses a `long double` value.                                   |
| `manual_i64_to_string()` | Implements signed 64-bit integer-to-string conversion manually. |

**Example: Integer-to-string conversion**

```c
#include <stdint.h>
#include <stdio.h>

int main(void) {
    int64_t value = -12345;
    char buffer[32];

    int length = snprintf(
        buffer,
        sizeof(buffer),
        "%lld",
        (long long)value
    );

    if (length < 0 || (size_t)length >= sizeof(buffer)) {
        fprintf(stderr, "Conversion failed.\n");
        return 1;
    }

    printf("String: %s\n", buffer);

    return 0;
}
```

`snprintf()` writes formatted output into a character buffer while respecting its specified capacity.

**Example: String-to-integer conversion**

```c
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *text = "12345";
    char *endptr;

    errno = 0;

    long long value = strtoll(text, &endptr, 10);

    if (errno == ERANGE || endptr == text || *endptr != '\0') {
        fprintf(stderr, "Invalid integer.\n");
        return 1;
    }

    printf("Value: %lld\n", value);

    return 0;
}
```

The conversion functions use `endptr` to verify that the complete input was consumed and `errno` to detect range errors.

**Key takeaways**

- Formatting and parsing are two different conversion processes.
- Buffer capacity must be checked when writing formatted output.
- String conversion functions provide useful error-detection mechanisms.
- Numeric input must be validated before the resulting value is used.
- Manual conversion algorithms help explain how numeric representations are translated into character sequences.

### 5. File Operations

Explored file handling in C through text and binary streams, file positioning, buffered copying, hexadecimal inspection, and error handling.

**Topics covered**

- Understanding files and file streams.
- Opening and closing files.
- File access modes.
- Text file reading.
- Text file writing.
- Binary file reading and writing.
- Buffered file operations.
- File positioning.
- Retrieving file sizes.
- Copying files using fixed-size buffers.
- Handling partial writes.
- Generating hexadecimal dumps.
- Displaying hexadecimal and ASCII representations.
- Detecting EOF and stream errors.
- Checking failures during file opening, reading, writing, and closing.

**Core functions**

| Function    | Purpose                                           |
| ----------- | ------------------------------------------------- |
| `fopen()`   | Opens a file stream.                              |
| `fclose()`  | Closes a file stream and flushes buffered output. |
| `fgetc()`   | Reads a character from a file.                    |
| `fgets()`   | Reads a line or a specified number of characters. |
| `fputc()`   | Writes a character to a file.                     |
| `fputs()`   | Writes a null-terminated string.                  |
| `fprintf()` | Writes formatted output.                          |
| `fread()`   | Reads blocks of data.                             |
| `fwrite()`  | Writes blocks of data.                            |
| `fseek()`   | Changes the file position.                        |
| `ftell()`   | Retrieves the current file position.              |
| `rewind()`  | Moves the file position to the beginning.         |
| `feof()`    | Checks the end-of-file indicator.                 |
| `ferror()`  | Checks the stream error indicator.                |
| `fflush()`  | Flushes buffered output.                          |

**Project functions**

| Function              | Purpose                                                 |
| --------------------- | ------------------------------------------------------- |
| `file_open()`         | Opens a file after validating its arguments.            |
| `file_close()`        | Closes a file stream.                                   |
| `read_text_file()`    | Reads an entire text file into a buffer.                |
| `write_text_file()`   | Creates or overwrites a text file.                      |
| `append_text_file()`  | Appends text to a file.                                 |
| `read_binary_file()`  | Reads binary data into a buffer.                        |
| `write_binary_file()` | Writes binary data to a file.                           |
| `copy_file()`         | Copies a file using buffered I/O.                       |
| `hexdump_file()`      | Displays a file's hexadecimal and ASCII representation. |
| `get_file_size()`     | Retrieves the size of a seekable file.                  |

**File copying**

The project implements buffered file copying using `fread()` and `fwrite()`.

Instead of loading an entire file into memory, the implementation processes data in fixed-size chunks. It also handles partial writes and checks read, write, and closing failures.

**Hexdump**

The hexdump implementation reads files in 16-byte rows and displays:

- The offset of each row.
- The hexadecimal representation of each byte.
- The corresponding printable ASCII characters.
- A `.` placeholder for non-printable bytes.

**Key takeaways**

- Text and binary streams have different data-handling characteristics.
- Buffered I/O provides a convenient interface for file processing.
- `fread()` and `fwrite()` are useful for processing arbitrary binary data.
- File positioning makes random access possible for seekable files.
- Fixed-size buffers allow large files to be processed with predictable memory usage.
- Hexdumps are useful for inspecting binary data.
- Checking stream errors and closing failures is essential for reliable file operations.

### 6. CLI and Argument Parsing

Developed a command-line interface using custom argument parsing and the POSIX `getopt()` interface.

The module explores how command-line input is received, interpreted, validated, converted, and dispatched to application-specific command handlers.

**Topics covered**

- Command-line argument fundamentals.
- Understanding `argc` and `argv`.
- Positional arguments.
- Named options and boolean flags.
- Long and short option formats.
- Custom argument parsing.
- Option metadata and validation.
- Duplicate and unknown option detection.
- End-of-options handling.
- POSIX `getopt()`.
- Short-option clustering.
- Numeric argument parsing.
- Signed and unsigned integer validation.
- Command dispatching.
- Error reporting and input validation.

**Core functions**

| Function     | Purpose                                     |
| ------------ | ------------------------------------------- |
| `strcmp()`   | Compares command and option names.          |
| `strncmp()`  | Compares a specified number of characters.  |
| `strlen()`   | Retrieves string lengths.                   |
| `strchr()`   | Locates separators within strings.          |
| `strtoll()`  | Converts a string into a signed integer.    |
| `strtoull()` | Converts a string into an unsigned integer. |
| `getopt()`   | Parses POSIX short command-line options.    |

**Project functions**

| Function                     | Purpose                                              |
| ---------------------------- | ---------------------------------------------------- |
| `cli_parse_options()`        | Parses command-line options using the custom parser. |
| `cli_parse_options_getopt()` | Parses short options using POSIX `getopt()`.         |
| `cli_parse_i64()`            | Parses signed 64-bit integer arguments.              |
| `cli_parse_u64()`            | Parses unsigned 64-bit integer arguments.            |
| `cli_dispatch()`             | Dispatches commands to their handlers.               |
| `cli_run_greet()`            | Executes the greeting command.                       |
| `cli_run_calc()`             | Executes the calculator command.                     |
| `cli_run_inspect()`          | Inspects an integer representation.                  |
| `cli_print_usage()`          | Displays application usage information.              |
| `cli_print_version()`        | Displays application version information.            |

**Custom parser versus POSIX `getopt()`**

| Feature                 | Custom parser       | POSIX `getopt()`               |
| ----------------------- | ------------------- | ------------------------------ |
| Long options            | Supported           | Not supported                  |
| Short options           | Supported           | Supported                      |
| Separate option values  | Supported           | Supported                      |
| Attached option values  | Supports `-n=value` | Supports `-nvalue`             |
| Short-option clustering | Not supported       | Supported                      |
| Duplicate detection     | Implemented         | Implemented in project wrapper |
| `--` terminator         | Supported           | Supported                      |

The custom parser provides control over the application's accepted command-line syntax, while `getopt()` demonstrates how a POSIX interface handles conventional short options.

**Project commands**

The CLI application provides three commands:

| Command   | Functionality                                                                  |
| --------- | ------------------------------------------------------------------------------ |
| `greet`   | Displays a greeting with optional name and uppercase options.                  |
| `calc`    | Performs checked integer addition.                                             |
| `inspect` | Displays a signed integer in decimal, hexadecimal, and binary representations. |

**Example: Using the CLI application**

```bash
# Display application help
./build/ccli --help

# Display application version
./build/ccli --version

# Greeting
./build/ccli greet --name Akshat

# Greeting with uppercase output
./build/ccli greet -n Akshat -u

# Add two integers
./build/ccli calc add 10 20

# Inspect an integer
./build/ccli inspect -42

# Inspect hexadecimal input
./build/ccli inspect 0xFF
```

**Key takeaways**

- Command-line arguments are received as strings and must be validated.
- Positional arguments and named options provide different ways to structure input.
- A custom parser provides control over application-specific syntax.
- POSIX `getopt()` provides an established approach for conventional short options.
- Numeric conversion functions must check incomplete input and range errors.
- Command dispatching separates command selection from command implementation.
- Error handling makes command-line programs more predictable and reliable.

## Tools and Technologies

| Tool / Technology          | Purpose                       |
| -------------------------- | ----------------------------- |
| C (C11)                    | Programming language.         |
| Clang                      | C compiler.                   |
| GNU Make                   | Build automation.             |
| POSIX `getopt()`           | Short-option parsing.         |
| AddressSanitizer           | Detecting memory errors.      |
| UndefinedBehaviorSanitizer | Detecting undefined behavior. |
| Git                        | Version control.              |
| Linux                      | Development environment.      |

## Build and Testing

The individual parts use GNU Make to automate compilation and testing.

Common commands:

```bash
# Build the project
make

# Run tests
make test

# Run tests with AddressSanitizer and UndefinedBehaviorSanitizer
make san

# Clean generated files
make clean
```

## Key Takeaways

Developed an understanding of how C represents and processes integer data, including fundamental and fixed-width types, integer promotions, arithmetic conversions, and signed and unsigned integer behavior.

Explored bitwise operations and endianness to understand how individual bits and bytes are manipulated and represented in memory.

Applied these concepts by developing Bitview, a modular command-line utility for examining integer representations and performing bit-level operations.

Implemented reusable integer and floating-point conversion functions, explored text and binary file handling, developed buffered file copying and hexadecimal inspection functionality, and built a command-line application with custom and POSIX argument parsing.

Gained practical experience with C data types, integer representations, bit manipulation, numeric conversions, buffered I/O, command-line interfaces, modular project organization, error handling, automated testing, and sanitizer-based validation.
