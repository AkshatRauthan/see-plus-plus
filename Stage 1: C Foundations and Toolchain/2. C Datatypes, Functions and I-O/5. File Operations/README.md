<div align="center">
  <h1>File Operations</h1>
  Exploring file handling in C through text and binary file operations, file positioning, buffered I/O, and error handling.
</div><br />

## Topics Covered

### 1. File Handling Fundamentals

- Understanding files and file streams.
- Working with the `FILE` type.
- Opening and closing files.
- Understanding file access modes.
- Creating and accessing files.
- Understanding buffered file I/O.
- Handling file opening and closing failures.

**Core functions**

| Function | Purpose |
|---|---|
| `fopen()` | Opens a file and returns a file stream. |
| `fclose()` | Closes a file stream and flushes buffered output. |

**Example: Opening and closing a file**

```c
#include <stdio.h>

int main(void) {
    // Open an existing file for reading.
    FILE *file = fopen("example.txt", "r");

    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    // Perform file operations here.

    // Close the file and release its resources.
    if (fclose(file) != 0) {
        perror("fclose");
        return 1;
    }

    return 0;
}
```

`fopen()` creates a file stream associated with the requested file and access mode. The returned `FILE *` is used by subsequent file operations.

`fclose()` closes the stream and flushes buffered output. It is important to check its return value because errors can occur while buffered data is being written.

**File access modes**

| Mode | Description |
|---|---|
| `r` | Opens an existing file for reading. |
| `w` | Opens a file for writing; creates it or truncates existing contents. |
| `a` | Opens a file for appending; creates it if necessary. |
| `r+` | Opens an existing file for reading and writing. |
| `w+` | Opens a file for reading and writing; creates or truncates it. |
| `a+` | Opens a file for reading and appending; creates it if necessary. |
| `rb` | Opens a binary file for reading. |
| `wb` | Opens a binary file for writing. |
| `ab` | Opens a binary file for appending. |

The `+` modes allow both reading and writing. The `b` character requests binary mode, which is significant on systems that distinguish text and binary streams.

**Advantages**
- The standard I/O library provides a consistent interface for file operations.
- File streams provide buffering, reducing the need for individual low-level I/O operations.
- Access modes make the intended file operation explicit.

**Disadvantages**
- File streams require proper resource management.
- Incorrect modes can unintentionally truncate existing files.
- Buffered output means some write errors may only become visible during flushing or closing.

### 2. Text File Reading

- Reading text files character by character.
- Reading individual lines.
- Reading multiple characters at once.
- Understanding newline characters.
- Working with null-terminated strings.
- Detecting end-of-file.
- Checking for read errors.
- Handling insufficient buffer capacity.

**Core functions**

| Function | Purpose |
|---|---|
| `fgetc()` | Reads one character from a file. |
| `fgets()` | Reads a line or a specified number of characters. |
| `fread()` | Reads a specified number of elements from a file. |
| `feof()` | Checks whether the end-of-file indicator is set. |
| `ferror()` | Checks whether a file stream has encountered an error. |

**Example: Reading a character using `fgetc()`**

```c
#include <stdio.h>

int main(void) {
    FILE *file = fopen("example.txt", "r");

    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    int character;

    // Read characters until EOF is returned.
    while ((character = fgetc(file)) != EOF) {
        putchar(character);
    }

    if (ferror(file)) {
        perror("fgetc");
        fclose(file);
        return 1;
    }

    fclose(file);

    return 0;
}
```

`fgetc()` returns the next character as an `unsigned char` converted to `int`, or `EOF` when the end of the file is reached or a read error occurs. Using `int` rather than `char` allows the program to distinguish every possible byte value from `EOF`.

**Example: Reading a line using `fgets()`**

```c
#include <stdio.h>

int main(void) {
    FILE *file = fopen("example.txt", "r");

    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    char buffer[128];

    // Read one line at a time.
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    if (ferror(file)) {
        perror("fgets");
        fclose(file);
        return 1;
    }

    fclose(file);

    return 0;
}
```

`fgets()` reads at most `capacity - 1` characters and adds a terminating null character. If it encounters a newline before reaching the limit, the newline is included in the resulting string.

**Example: Reading multiple bytes using `fread()`**

```c
#include <stdio.h>

int main(void) {
    FILE *file = fopen("example.txt", "r");

    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    char buffer[128];

    // Read up to 128 bytes.
    size_t bytes_read = fread(buffer, 1, sizeof(buffer), file);

    printf("Bytes read: %zu\n", bytes_read);

    if (ferror(file)) {
        perror("fread");
    }

    fclose(file);

    return 0;
}
```

`fread()` reads a specified number of elements. Its return value represents the number of complete elements successfully read. When the element size is `1`, this is also the number of bytes read.

**Advantages**
- `fgetc()` is useful for character-by-character processing.
- `fgets()` is convenient for reading lines while respecting buffer limits.
- `fread()` efficiently reads larger blocks of data.
- Buffered input reduces the number of underlying I/O operations.

**Disadvantages**
- `fgetc()` can be inefficient when processing large amounts of data one character at a time.
- `fgets()` may return only part of a long line when the buffer is too small.
- `fread()` does not automatically add a null terminator.
- The caller must distinguish normal end-of-file from actual read errors.

### 3. Text File Writing

- Creating new text files.
- Overwriting existing file contents.
- Appending data to existing files.
- Writing individual characters.
- Writing strings.
- Writing formatted output.
- Understanding buffered output.
- Detecting write and flush failures.

**Core functions**

| Function | Purpose |
|---|---|
| `fputc()` | Writes one character to a file. |
| `fputs()` | Writes a null-terminated string to a file. |
| `fprintf()` | Writes formatted output to a file. |
| `fwrite()` | Writes blocks of data to a file. |
| `fflush()` | Flushes buffered output to the underlying file. |

**Example: Writing a string using `fputs()`**

```c
#include <stdio.h>

int main(void) {
    // Create the file or overwrite its existing contents.
    FILE *file = fopen("example.txt", "w");

    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    // Write a string to the file.
    if (fputs("Hello, C!\n", file) == EOF) {
        perror("fputs");
        fclose(file);
        return 1;
    }

    if (fclose(file) != 0) {
        perror("fclose");
        return 1;
    }

    return 0;
}
```

`fputs()` writes the characters in a string but does not write the terminating null character. The newline must be included explicitly if required.

**Example: Appending using `fprintf()`**

```c
#include <stdio.h>

int main(void) {
    // Open the file in append mode.
    FILE *file = fopen("example.txt", "a");

    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    // Append formatted output.
    if (fprintf(file, "Temperature: %.2f\n", 25.75) < 0) {
        perror("fprintf");
        fclose(file);
        return 1;
    }

    fclose(file);

    return 0;
}
```

`fprintf()` works like `printf()`, but writes formatted output to a specified file stream instead of standard output.

**Advantages**
- `fputs()` and `fprintf()` make text output straightforward.
- `fprintf()` supports formatting numbers, strings, and other values.
- Append mode preserves existing contents.
- Buffered output can improve performance.

**Disadvantages**
- Write operations can fail because of storage, permission, or filesystem errors.
- Write mode truncates existing files.
- Output may remain buffered until the stream is flushed or closed.
- Formatted output requires correct format specifiers and matching argument types.

### 4. Binary File Operations

- Understanding binary files.
- Reading raw bytes.
- Writing raw bytes.
- Handling data that contains null bytes.
- Using `fread()` and `fwrite()`.
- Copying files in fixed-size chunks.
- Understanding the difference between text and binary streams.
- Avoiding unnecessary memory allocation when processing large files.

**Core functions**

| Function | Purpose |
|---|---|
| `fread()` | Reads blocks of data from a file. |
| `fwrite()` | Writes blocks of data to a file. |
| `fopen()` | Opens a file using binary modes such as `rb` and `wb`. |
| `fclose()` | Closes the file stream. |

**Example: Writing binary data**

```c
#include <stdio.h>

int main(void) {
    // Binary data can contain any byte value.
    unsigned char data[] = {
        0x00, 0x01, 0x7F, 0x80, 0xFF
    };

    FILE *file = fopen("data.bin", "wb");

    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    // Write five elements, each one byte in size.
    size_t written = fwrite(data, 1, sizeof(data), file);

    if (written != sizeof(data)) {
        perror("fwrite");
        fclose(file);
        return 1;
    }

    fclose(file);

    return 0;
}
```

`fwrite()` writes raw data without interpreting it as a string. This makes it suitable for binary files containing arbitrary byte values, including `0x00`.

**Example: Reading binary data**

```c
#include <stdio.h>

int main(void) {
    unsigned char buffer[128];

    FILE *file = fopen("data.bin", "rb");

    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    size_t bytes_read = fread(buffer, 1, sizeof(buffer), file);

    if (ferror(file)) {
        perror("fread");
        fclose(file);
        return 1;
    }

    printf("Bytes read: %zu\n", bytes_read);

    fclose(file);

    return 0;
}
```

**Example: Copying a file in chunks**

```c
#include <stdio.h>

int main(void) {
    FILE *source = fopen("source.bin", "rb");

    if (source == NULL) {
        perror("source");
        return 1;
    }

    FILE *destination = fopen("destination.bin", "wb");

    if (destination == NULL) {
        perror("destination");
        fclose(source);
        return 1;
    }

    unsigned char buffer[4096];

    while (1) {
        size_t count = fread(buffer, 1, sizeof(buffer), source);

        if (count > 0) {
            if (fwrite(buffer, 1, count, destination) != count) {
                perror("fwrite");
                break;
            }
        }

        if (ferror(source)) {
            perror("fread");
            break;
        }

        if (feof(source)) {
            break;
        }
    }

    fclose(destination);
    fclose(source);

    return 0;
}
```

Reading and writing in fixed-size chunks allows files to be copied without loading their entire contents into memory.

**Text files versus binary files**

| Feature | Text mode | Binary mode |
|---|---|---|
| Opening modes | `r`, `w`, `a` | `rb`, `wb`, `ab` |
| Data interpretation | Text characters | Raw bytes |
| Newline handling | May involve platform-specific translation | No text newline translation |
| Null bytes | Not suitable for ordinary C strings | Supported |
| Typical uses | Configuration files, logs, source code | Images, executables, serialized data |

**Advantages**
- Binary operations preserve arbitrary byte sequences.
- `fread()` and `fwrite()` support efficient block-based processing.
- Chunk-based copying keeps memory usage predictable.
- Binary files are suitable for structured data and non-text formats.

**Disadvantages**
- Binary data requires knowledge of its format before it can be interpreted.
- Raw structures may contain padding and platform-dependent representations.
- Integer byte order and floating-point representation can differ between systems.
- Writing a C structure directly to a file does not automatically create a portable file format.

### 5. File Positioning

- Understanding the file position indicator.
- Moving to a specific file position.
- Retrieving the current file position.
- Moving to the beginning of a file.
- Moving to the end of a file.
- Calculating file size.
- Performing random access on seekable files.

**Core functions**

| Function | Purpose |
|---|---|
| `fseek()` | Changes the file position indicator. |
| `ftell()` | Retrieves the current file position. |
| `rewind()` | Moves the file position to the beginning. |

**File positioning constants**

| Constant | Description |
|---|---|
| `SEEK_SET` | Position relative to the beginning of the file. |
| `SEEK_CUR` | Position relative to the current position. |
| `SEEK_END` | Position relative to the end of the file. |

**Example: Moving through a file**

```c
#include <stdio.h>

int main(void) {
    FILE *file = fopen("example.txt", "r");

    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    // Move to the fifth byte from the beginning.
    if (fseek(file, 4, SEEK_SET) != 0) {
        perror("fseek");
        fclose(file);
        return 1;
    }

    // Retrieve the current position.
    long position = ftell(file);

    if (position < 0) {
        perror("ftell");
        fclose(file);
        return 1;
    }

    printf("Current position: %ld\n", position);

    // Read from the current position.
    int character = fgetc(file);

    if (character != EOF) {
        printf("Character: %c\n", character);
    }

    // Return to the beginning.
    rewind(file);

    fclose(file);

    return 0;
}
```

`fseek()` changes the position from which subsequent reads or writes occur. `ftell()` reports the current position, while `rewind()` returns the stream to the beginning and clears its error and end-of-file indicators.

**Example: Retrieving file size**

```c
#include <stdio.h>

int main(void) {
    FILE *file = fopen("example.txt", "rb");

    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    // Move to the end of the file.
    if (fseek(file, 0, SEEK_END) != 0) {
        perror("fseek");
        fclose(file);
        return 1;
    }

    // The position at the end represents the file size.
    long size = ftell(file);

    if (size < 0) {
        perror("ftell");
        fclose(file);
        return 1;
    }

    printf("File size: %ld bytes\n", size);

    fclose(file);

    return 0;
}
```

This approach works for seekable files. The `long` return type of `ftell()` can limit the maximum representable file position, so large-file handling may require platform-specific APIs.

**Advantages**
- Supports random access without reading the entire file sequentially.
- Makes it possible to inspect specific file regions.
- Allows simple file-size calculations for seekable files.
- Useful for binary formats with headers, offsets, and records.

**Disadvantages**
- Seeking is not supported by every stream, such as pipes.
- `fseek()` and `ftell()` use `long`, which may not support very large files on every platform.
- Text-stream positioning has additional restrictions; arbitrary byte offsets should generally be used with binary streams.

### 6. File Error Handling

- Understanding file operation return values.
- Detecting end-of-file conditions.
- Distinguishing end-of-file from read errors.
- Checking write failures.
- Understanding `errno`.
- Reporting errors with `perror()`.
- Handling failures when opening, reading, writing, and closing files.

**Core functions and variables**

| Function / Variable | Purpose |
|---|---|
| `feof()` | Checks whether the end-of-file indicator is set. |
| `ferror()` | Checks whether the stream error indicator is set. |
| `clearerr()` | Clears the end-of-file and error indicators. |
| `perror()` | Prints a description of the current `errno` value. |
| `errno` | Stores an error code set by certain library operations. |
| `EOF` | Special return value used to indicate end-of-file or certain input failures. |

**Example: Handling read errors**

```c
#include <stdio.h>

int main(void) {
    FILE *file = fopen("example.txt", "r");

    if (file == NULL) {
        perror("fopen");
        return 1;
    }

    int character;

    while ((character = fgetc(file)) != EOF) {
        putchar(character);
    }

    // Check for an actual stream error.
    if (ferror(file)) {
        perror("fgetc");
        fclose(file);
        return 1;
    }

    // Otherwise, the read loop ended normally at EOF.
    if (feof(file)) {
        printf("\nReached end of file.\n");
    }

    fclose(file);

    return 0;
}
```

A common mistake is assuming that `EOF` always means the file ended normally. Both an end-of-file condition and a read error can cause an input function to return `EOF`. Use `ferror()` and `feof()` to distinguish them.

**Advantages**
- Explicit error checking makes file operations more reliable.
- `perror()` provides useful diagnostic messages.
- Stream indicators help distinguish normal termination from failures.

**Disadvantages**
- Error handling adds code to otherwise simple operations.
- Not every library failure provides a useful `errno` value.
- Ignoring `fclose()` errors can hide delayed write failures.

## Build System

The project is implemented in C and compiled using Clang.

**Compiler:** Clang  
**Language Standard:** C11  
**Debug Information:** `-g`  
**Warning Flags:** `-Wall -Wextra -Wpedantic -Wconversion -Wshadow`  
**Sanitizers:** AddressSanitizer and UndefinedBehaviorSanitizer

```bash
# Build and run all tests
make

# Run tests with AddressSanitizer and UndefinedBehaviorSanitizer
make san

# Remove generated binaries and build files
make clean
```

## Project Structure

```text
5. File Operations/
├── include/
│   └── file_operations.h
├── src/
│   ├── 1. File Handling Fundamentals.c
│   ├── 2. Text File Reading.c
│   ├── 3. Text File Writing.c
│   ├── 4. Binary File Operations.c
│   └── 5. File Positioning.c
├── tests/
│   └── test_file_operations.c
├── build/
├── Makefile
└── README.md
```

## Takeaway

File handling is an essential part of systems programming. C provides a standard I/O interface through `FILE` streams and functions such as `fopen()`, `fclose()`, `fread()`, `fwrite()`, `fseek()`, and `ftell()`.

Understanding the differences between text and binary files, buffered I/O, file positioning, and error handling makes it possible to work with files safely and efficiently.

These concepts are particularly useful in configuration parsing, logging, serialization, binary file processing, data storage, and systems programming.