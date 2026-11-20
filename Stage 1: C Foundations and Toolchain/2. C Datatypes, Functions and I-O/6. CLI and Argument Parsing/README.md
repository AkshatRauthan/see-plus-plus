<div align="center">
  <h1>CLI and Argument Parsing</h1>
  Exploring command-line interfaces in C through argument handling, option parsing, numeric validation, command dispatching, and error reporting.
</div><br />

## Topics Covered

### 1. Command-Line Argument Fundamentals

- Understanding command-line interfaces.
- Receiving arguments through `argc` and `argv`.
- Understanding the argument count.
- Accessing individual arguments.
- Understanding argument indexing.
- Handling missing arguments.
- Handling extra arguments.
- Understanding why command-line arguments are strings.
- Separating commands from their arguments.

**Core concepts**

| Concept   | Purpose                                                      |
| --------- | ------------------------------------------------------------ |
| `argc`    | Contains the number of command-line arguments.               |
| `argv`    | Contains the argument strings.                               |
| `argv[0]` | Usually contains the program name or invocation path.        |
| `argv[1]` | Contains the first argument supplied after the program name. |

**Example: Inspecting command-line arguments**

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Argument count: %d\n", argc);

    // Display every argument supplied to the program.
    for (int i = 0; i < argc; i++) {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    return 0;
}
```

For the following invocation:

```bash
./program hello 123
```

The argument structure is:

```text
argc = 3

argv[0] = "./program"
argv[1] = "hello"
argv[2] = "123"
argv[3] = NULL
```

`argc` tells us how many arguments are available, while `argv` provides access to their string representations.

**Advantages**

- Provides a simple interface for passing input to programs.
- Allows programs to be automated through scripts.
- Supports commands, options, flags, and positional arguments.
- Avoids requiring interactive input for every operation.

**Disadvantages**

- Arguments are received as strings and require validation.
- Argument ordering can become difficult to manage in larger applications.
- Missing or malformed arguments must be handled explicitly.

### 2. Positional Arguments

- Understanding positional arguments.
- Accessing arguments by index.
- Validating argument counts.
- Handling required arguments.
- Handling optional positional arguments.
- Implementing commands with multiple operands.
- Separating subcommands from their arguments.

**Example: A command with positional arguments**

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    // Expected: program add NUMBER1 NUMBER2
    if (argc != 4) {
        fprintf(stderr, "Usage: %s add NUMBER1 NUMBER2\n", argv[0]);
        return 1;
    }

    const char *command = argv[1];
    const char *first = argv[2];
    const char *second = argv[3];

    printf("Command: %s\n", command);
    printf("First argument: %s\n", first);
    printf("Second argument: %s\n", second);

    return 0;
}
```

For:

```bash
./program add 10 20
```

The command is `add`, and the two positional operands are `10` and `20`.

Positional arguments are useful when the order of arguments has a clear meaning.

**Advantages**

- Simple to implement.
- Suitable for commands with a small number of required arguments.
- Easy to use in shell scripts.

**Disadvantages**

- Users must remember the correct argument order.
- Optional arguments can make the syntax harder to understand.
- Adding new positional arguments can complicate an existing interface.

### 3. Named Options and Boolean Flags

- Understanding named options.
- Long options such as `--name`.
- Short options such as `-n`.
- Options that require values.
- Boolean flags that do not require values.
- Supporting `--option=value`.
- Supporting `-o=value`.
- Detecting duplicate options.
- Detecting unknown options.
- Handling missing option values.
- Using `--` to terminate option parsing.

**Common option formats**

| Format          | Description                          |
| --------------- | ------------------------------------ |
| `--name Akshat` | Long option with a separate value.   |
| `--name=Akshat` | Long option with an attached value.  |
| `-n Akshat`     | Short option with a separate value.  |
| `-n=Akshat`     | Short option with an attached value. |
| `--verbose`     | Boolean flag.                        |
| `--`            | Marks the end of option parsing.     |

**Example: Comparing named options**

```bash
# Long option
./program greet --name Akshat

# Long option with an attached value
./program greet --name=Akshat

# Short option
./program greet -n Akshat

# Boolean flag
./program greet --uppercase
```

Named options make command-line interfaces more readable because users can identify the purpose of each supplied value.

**Advantages**

- Arguments are more descriptive than positional values.
- Options can be supplied in different orders.
- Boolean flags provide convenient feature toggles.
- Short and long forms support both compact and readable commands.

**Disadvantages**

- Parsing requires additional validation.
- Duplicate and conflicting options need defined behavior.
- Supporting different option formats increases implementation complexity.

### 4. Custom Argument Parsing

- Building an argument parser manually.
- Defining option metadata.
- Matching long option names.
- Matching short option characters.
- Separating option names from values.
- Collecting positional arguments.
- Rejecting unknown options.
- Rejecting duplicate options.
- Detecting missing values.
- Handling the `--` terminator.
- Separating parsing logic from command implementations.

**Core functions**

| Function    | Purpose                                            |
| ----------- | -------------------------------------------------- |
| `strcmp()`  | Compares complete strings.                         |
| `strncmp()` | Compares a specified number of characters.         |
| `strlen()`  | Retrieves the length of a string.                  |
| `strchr()`  | Locates a character, such as `=`, inside a string. |

**Example: Matching an option**

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    const char *argument = "--verbose";

    if (strcmp(argument, "--verbose") == 0) {
        printf("Verbose mode enabled.\n");
    }

    return 0;
}
```

`strcmp()` compares two strings and returns zero when they are equal. It is commonly used to identify commands and option names.

**Example: Splitting an option and its value**

```c
#include <stdio.h>
#include <string.h>

int main(void) {
    const char *argument = "--name=Akshat";

    const char *equals = strchr(argument, '=');

    if (equals != NULL) {
        printf("Option: --name\n");
        printf("Value: %s\n", equals + 1);
    }

    return 0;
}
```

`strchr()` locates the separator, allowing the parser to distinguish the option name from its value.

**Why implement a custom parser?**

A custom parser provides control over the accepted command-line syntax and allows us to understand how argument parsing works internally.

It is particularly useful when building a command-based application such as Bitview, where commands and their arguments need to be dispatched independently.

**Advantages**

- Full control over accepted argument formats.
- No dependency on external parsing libraries.
- Can be adapted to application-specific command syntax.
- Helps develop an understanding of argument parsing and validation.

**Disadvantages**

- Requires manual handling of edge cases.
- More code must be maintained.
- Advanced features such as option clustering and automatic help generation require additional implementation.
- An incomplete parser may behave differently from established CLI conventions.

### 5. Standard Argument Parsing with `getopt()`

- Understanding the POSIX `getopt()` function.
- Parsing short options.
- Defining required option arguments.
- Handling boolean flags.
- Detecting unknown options.
- Handling missing option arguments.
- Understanding `optarg`, `optind`, and `optopt`.

**Core functions and variables**

| Function / Variable | Purpose                                                     |
| ------------------- | ----------------------------------------------------------- |
| `getopt()`          | Parses short command-line options.                          |
| `optarg`            | Points to the value of an option that requires an argument. |
| `optind`            | Identifies the next argument to be processed.               |
| `optopt`            | Contains the option character that caused an error.         |

**Example: Using `getopt()`**

```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int option;

    // 'n:' means -n requires a value.
    // 'v' means -v is a boolean flag.
    while ((option = getopt(argc, argv, "n:v")) != -1) {
        switch (option) {
        case 'n':
            printf("Name: %s\n", optarg);
            break;

        case 'v':
            printf("Verbose mode enabled.\n");
            break;

        case '?':
            fprintf(stderr, "Unknown or incomplete option.\n");
            return 1;
        }
    }

    // Remaining arguments are positional.
    for (int i = optind; i < argc; i++) {
        printf("Argument: %s\n", argv[i]);
    }

    return 0;
}
```

For example:

```bash
./program -n Akshat -v input.txt
```

`getopt()` processes `-n` and `-v`. The remaining positional argument can be accessed using `optind`.

`getopt()` is a POSIX interface, not part of ISO C. It is commonly available on Linux and other POSIX-compatible systems.

**Advantages**

- Avoids implementing basic short-option parsing manually.
- Handles common option syntax.
- Provides built-in support for required option values.
- Well established on POSIX systems.

**Disadvantages**

- Primarily designed for short options.
- Not part of the ISO C standard.
- Uses global parsing variables.
- Behavior and extensions can vary between implementations.

### 6. Long Option Parsing with `getopt_long()`

- Understanding GNU long-option parsing.
- Supporting options such as `--name`.
- Supporting short and long options together.
- Defining required and optional option arguments.
- Handling long-option identifiers.
- Understanding the `struct option` interface.

**Core function and structure**

| Function / Structure | Purpose                                             |
| -------------------- | --------------------------------------------------- |
| `getopt_long()`      | Parses short and long options.                      |
| `struct option`      | Defines long-option names and their behavior.       |
| `required_argument`  | Indicates that an option requires a value.          |
| `no_argument`        | Indicates that an option is a boolean flag.         |
| `optional_argument`  | Indicates that an option accepts an optional value. |

**Example: Using `getopt_long()`**

```c
#include <stdio.h>
#include <getopt.h>

int main(int argc, char *argv[]) {
    static struct option long_options[] = {
        {"name", required_argument, NULL, 'n'},
        {"verbose", no_argument, NULL, 'v'},
        {"help", no_argument, NULL, 'h'},
        {NULL, 0, NULL, 0}
    };

    int option;

    while ((option = getopt_long(
        argc,
        argv,
        "n:vh",
        long_options,
        NULL
    )) != -1) {
        switch (option) {
        case 'n':
            printf("Name: %s\n", optarg);
            break;

        case 'v':
            printf("Verbose mode enabled.\n");
            break;

        case 'h':
            printf("Help requested.\n");
            break;

        case '?':
            return 1;
        }
    }

    return 0;
}
```

Both of the following are supported:

```bash
./program --name Akshat --verbose
./program -n Akshat -v
```

`getopt_long()` is a GNU extension commonly available on Linux. It is not part of ISO C or POSIX, so applications targeting other platforms may need a different parser.

**Advantages**

- Supports both short and long options.
- Provides a standardized option definition structure.
- Reduces the amount of custom parsing code.
- Useful for applications with many command-line options.

**Disadvantages**

- Not part of ISO C or POSIX.
- Depends on GNU-compatible environments.
- Uses global parsing state.
- Less suitable when an application requires highly customized syntax.

### 7. Numeric Argument Parsing

- Understanding why command-line values are strings.
- Converting strings into signed integers.
- Converting strings into unsigned integers.
- Parsing decimal, hexadecimal, octal, and binary values.
- Detecting invalid numeric input.
- Detecting overflow and underflow.
- Checking incomplete conversions.
- Validating values before using them.
- Reusing conversion functions from the Integer Conversions module.

**Core functions**

| Function      | Purpose                                                  |
| ------------- | -------------------------------------------------------- |
| `strtoimax()` | Converts a string into the widest signed integer type.   |
| `strtoumax()` | Converts a string into the widest unsigned integer type. |
| `strtof()`    | Converts a string into a `float`.                        |
| `strtod()`    | Converts a string into a `double`.                       |
| `strtold()`   | Converts a string into a `long double`.                  |

**Supporting mechanisms**

| Mechanism                 | Purpose                              |
| ------------------------- | ------------------------------------ |
| `errno`                   | Reports conversion errors.           |
| `ERANGE`                  | Indicates a range error.             |
| `endptr`                  | Identifies where parsing stopped.    |
| `INT64_MIN` / `INT64_MAX` | Define signed 64-bit boundaries.     |
| `UINT64_MAX`              | Defines the unsigned 64-bit maximum. |

**Example: Parsing a signed integer**

```c
#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *text = "-12345";
    char *endptr;

    errno = 0;

    intmax_t value = strtoimax(text, &endptr, 10);

    if (errno == ERANGE || endptr == text || *endptr != '\0') {
        fprintf(stderr, "Invalid integer.\n");
        return 1;
    }

    printf("Value: %" PRIdMAX "\n", value);

    return 0;
}
```

`strtoimax()` converts the supplied string into an integer. `endptr` verifies that the entire argument was consumed, while `errno` helps detect range errors.

**Example: Parsing a floating-point argument**

```c
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *text = "3.14159";
    char *endptr;

    errno = 0;

    double value = strtod(text, &endptr);

    if (errno == ERANGE || endptr == text || *endptr != '\0') {
        fprintf(stderr, "Invalid floating-point value.\n");
        return 1;
    }

    printf("Value: %f\n", value);

    return 0;
}
```

**Advantages**

- Uses standard conversion functions.
- Supports different numeric types and bases.
- Allows reliable validation of user input.
- Detects incomplete conversions and range errors.

**Disadvantages**

- Requires explicit error checking.
- Conversion functions do not automatically validate application-specific constraints.
- Additional checks are required when converting into narrower integer types.

### 8. Command Dispatching

- Understanding subcommands.
- Separating command identification from command execution.
- Implementing a command dispatcher.
- Mapping command names to functions.
- Passing command-specific arguments.
- Handling unknown commands.
- Separating CLI parsing from application logic.

**Example: A simple command dispatcher**

```c
#include <stdio.h>
#include <string.h>

static void command_greet(void) {
    puts("Hello!");
}

static void command_version(void) {
    puts("Version 1.0.0");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: program <command>\n");
        return 1;
    }

    if (strcmp(argv[1], "greet") == 0) {
        command_greet();
    } else if (strcmp(argv[1], "version") == 0) {
        command_version();
    } else {
        fprintf(stderr, "Unknown command: %s\n", argv[1]);
        return 1;
    }

    return 0;
}
```

A dispatcher identifies the requested command and invokes its corresponding function. This keeps command selection separate from the implementation of individual operations.

**Advantages**

- Improves code organization.
- Makes individual commands easier to maintain and test.
- Allows new commands to be added independently.
- Prevents the main function from becoming overloaded with application logic.

**Disadvantages**

- Requires a clear command structure.
- Poorly organized dispatch logic can become difficult to maintain as commands grow.
- Each command still needs its own argument validation.

### 9. Error Handling and Validation

- Detecting missing commands.
- Detecting unknown commands.
- Rejecting unknown options.
- Detecting duplicate options.
- Detecting missing option values.
- Validating positional argument counts.
- Detecting invalid numeric values.
- Detecting integer overflow.
- Producing useful usage messages.
- Returning meaningful exit statuses.

**Core functions and mechanisms**

| Function / Mechanism | Purpose                                                 |
| -------------------- | ------------------------------------------------------- |
| `fprintf()`          | Prints error messages to standard error.                |
| `perror()`           | Prints a description of an error stored in `errno`.     |
| `strcmp()`           | Validates command and option names.                     |
| `errno`              | Communicates conversion and library errors.             |
| Return values        | Communicate success or failure to the caller and shell. |

**Example: Handling invalid argument counts**

```c
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(
            stderr,
            "Usage: %s NUMBER1 NUMBER2\n",
            argv[0]
        );

        return 1;
    }

    printf("Arguments received successfully.\n");

    return 0;
}
```

Command-line programs conventionally return `0` for success and a non-zero status for failure. Error messages are written to `stderr` so they remain separate from normal program output.

**Advantages**

- Prevents malformed input from reaching application logic.
- Makes failures easier to understand and debug.
- Produces predictable behavior for scripts and automation.

**Disadvantages**

- Validation increases implementation complexity.
- Every command must define its accepted input and error behavior.
- Error messages need to remain consistent across the application.

## Project Structure

```text
6. CLI and Argument Parsing/
├── include/
│   └── cli.h
├── src/
│   ├── 1. Argument Parsing.c
│   ├── 2. Numeric Arguments.c
│   ├── 3. Command Dispatch.c
│   └── main.c
├── tests/
│   └── test_cli.c
├── build/
├── Makefile
└── README.md
```

## Build System

The project is implemented in C and compiled using Clang.

**Compiler:** Clang  
**Language Standard:** C11  
**Debug Information:** `-g`  
**Warning Flags:** `-Wall -Wextra -Wpedantic -Wconversion -Wshadow`  
**Sanitizers:** AddressSanitizer and UndefinedBehaviorSanitizer

```bash
# Build the CLI application
make

# Run the application
make run

# Run unit tests
make test

# Run tests and build with sanitizers
make san

# Remove generated binaries and build files
make clean
```

## Usage

The application provides three commands: `greet`, `calc`, and `inspect`.

### General Help

```bash
# Display application help
./build/ccli --help

# Display application version
./build/ccli --version
```

### Greeting

```bash
# Default greeting
./build/ccli greet

# Supply a name
./build/ccli greet --name Akshat

# Use a short option
./build/ccli greet -n Akshat

# Enable uppercase output
./build/ccli greet --name Akshat --uppercase

# Use short options
./build/ccli greet -n Akshat -u
```

### Calculator

```bash
# Add two integers
./build/ccli calc add 10 20

# Add negative and positive integers
./build/ccli calc add -10 20

# Add large integers
./build/ccli calc add 1000000000 2000000000
```

### Integer Inspection

```bash
# Inspect a decimal integer
./build/ccli inspect 42

# Inspect a negative integer
./build/ccli inspect -42

# Automatically detect hexadecimal input
./build/ccli inspect 0xFF

# Automatically detect octal input
./build/ccli inspect 077
```

## Testing and Validation

The project includes tests for:

- Long-option parsing.
- Short-option parsing.
- Positional arguments.
- The `--` option terminator.
- Duplicate option detection.
- Signed integer parsing.
- Unsigned integer parsing.
- Automatic base detection.
- Invalid numeric input.
- Integer minimum and maximum boundaries.
- Integer overflow detection.

The project can also be built with AddressSanitizer and UndefinedBehaviorSanitizer to detect memory errors and undefined behavior during execution.

## Takeaway

Command-line argument parsing is an important part of building practical C applications. It provides the interface through which users interact with programs, supply input, select operations, and configure application behavior.

Understanding `argc`, `argv`, positional arguments, named options, numeric parsing, and command dispatching makes it possible to build structured and maintainable CLI applications.

The standard interfaces `getopt()` and `getopt_long()` provide convenient approaches for common option syntax, while custom parsers offer greater control over application-specific command formats.

These concepts are particularly useful when developing developer tools, system utilities, compilers, debuggers, build tools, and command-based applications such as Bitview.
