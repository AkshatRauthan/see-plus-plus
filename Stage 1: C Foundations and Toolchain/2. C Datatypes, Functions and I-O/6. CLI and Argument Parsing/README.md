<div align="center">
  <h1>CLI and Argument Parsing</h1>
  Exploring command-line interfaces in C through argument handling, custom option parsing, POSIX getopt, numeric validation, command dispatching, and error handling.
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

| Concept | Purpose |
| ------- | ------- |
| `argc` | Contains the number of command-line arguments. |
| `argv` | Contains the argument strings. |
| `argv[0]` | Usually contains the program name or invocation path. |
| `argv[1]` | Contains the first argument supplied after the program name. |
| `argv[argc]` | Always contains a null pointer. |

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

Command-line arguments are represented as strings regardless of their intended meaning. Even numeric input such as `123` must be converted before it can be used in arithmetic operations.

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

| Format | Description |
| ------ | ----------- |
| `--name Akshat` | Long option with a separate value. |
| `--name=Akshat` | Long option with an attached value. |
| `-n Akshat` | Short option with a separate value. |
| `-n=Akshat` | Short option with an attached value. |
| `--uppercase` | Boolean flag. |
| `--` | Marks the end of option parsing. |

**Example: Comparing named options**

```bash
# Long option
./build/ccli greet --name Akshat

# Long option with an attached value
./build/ccli greet --name=Akshat

# Short option
./build/ccli greet -n Akshat

# Boolean flag
./build/ccli greet --uppercase
```

Named options make command-line interfaces more readable because users can identify the purpose of each supplied value.

An option definition typically contains metadata describing its name, short alias, whether it requires a value, and its parsing state.

The project represents this information using the `CliOption` structure:

```c
typedef struct {
    const char *long_name;
    char short_name;
    bool requires_value;
    bool seen;
    const char *value;
} CliOption;
```

This allows the parser to work with different option definitions without depending on individual commands.

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
- Validating option definitions.
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

| Function | Purpose |
| -------- | ------- |
| `cli_parse_options()` | Parses options and collects positional arguments. |
| `FindLongOption()` | Locates an option using its long name. |
| `FindShortOption()` | Locates an option using its short character. |
| `SetOption()` | Validates and stores a parsed option value. |
| `ValidateOptions()` | Checks option definitions for invalid or duplicate names. |
| `strcmp()` | Compares complete strings. |
| `strncmp()` | Compares a specified number of characters. |
| `strlen()` | Retrieves the length of a string. |
| `strchr()` | Locates a character inside a string. |

The helper functions are declared `static` because they are implementation details of the parser and should not be exposed to other source files.

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

**How the project parser works**

The manual parser processes arguments sequentially.

1. It validates the option definitions and resets their parsing state.
2. It checks whether an argument is a long option, short option, or positional argument.
3. It locates the corresponding option definition.
4. It retrieves an attached value or consumes the next argument when a value is required.
5. It rejects duplicate options, unknown options, invalid values, and missing arguments.
6. It collects positional arguments into a caller-provided array.

The parser also recognizes `--`, after which every remaining argument is treated as positional input.

Short-option clustering, such as `-abc`, is deliberately not supported by this implementation.

**Example: Using the project parser**

```c
#include <stdio.h>
#include "../include/cli.h"

int main(void) {
    char *argv[] = {
        "--name=Akshat",
        "--uppercase"
    };

    CliOption options[] = {
        {
            .long_name = "name",
            .short_name = 'n',
            .requires_value = true
        },
        {
            .long_name = "uppercase",
            .short_name = 'u',
            .requires_value = false
        }
    };

    const char *positionals[2];
    size_t positional_count = 0;

    if (cli_parse_options(
        2,
        argv,
        options,
        2,
        positionals,
        2,
        &positional_count
    ) != 0) {
        perror("cli_parse_options");
        return 1;
    }

    printf("Name: %s\n", options[0].value);
    printf("Uppercase: %s\n", options[1].seen ? "yes" : "no");

    return 0;
}
```

The parser receives option definitions separately from the argument strings. This makes the parsing logic reusable across different commands.

**Why implement a custom parser?**

A custom parser provides control over the accepted command-line syntax and allows us to understand how argument parsing works internally.

It is particularly useful when building command-based applications such as Bitview, where commands and their arguments need to be dispatched independently.

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

### 5. POSIX Argument Parsing with `getopt()`

- Understanding the POSIX `getopt()` function.
- Parsing short options.
- Defining required option arguments.
- Handling boolean flags.
- Supporting short-option clustering.
- Supporting attached option values.
- Detecting unknown options.
- Handling missing option arguments.
- Understanding `optarg`, `optind`, `optopt`, and `opterr`.
- Collecting positional arguments.

**Core function and variables**

| Function / Variable | Purpose |
| ------------------- | ------- |
| `getopt()` | Parses short command-line options. |
| `optarg` | Points to the value of an option that requires an argument. |
| `optind` | Identifies the next argument to be processed. |
| `optopt` | Contains the option character associated with an option error. |
| `opterr` | Controls automatic error messages from `getopt()`. |
| `optstring` | Defines supported option characters and which ones require values. |

**Understanding the option string**

The option string passed to `getopt()` describes the supported short options.

| Option string | Meaning |
| ------------- | ------- |
| `"v"` | `-v` is a flag. |
| `"n:"` | `-n` requires a value. |
| `"nv:"` | `-n` is a flag and `-v` requires a value. |
| `":n:"` | A leading colon changes missing-argument error handling. |

A colon immediately after an option character indicates that the option requires an argument.

**Example: Using `getopt()`**

```c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int option;

    // -n requires a value.
    // -v is a boolean flag.
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

**Example: Short-option clustering**

```bash
./program -vn Akshat
```

When multiple short options are grouped together, `getopt()` processes them individually.

If an option requires a value, the remaining characters in the same argument can supply that value.

**Project implementation**

The project provides a separate function:

```c
int cli_parse_options_getopt(
    int argc,
    char *argv[],
    CliOption options[],
    size_t option_count,
    const char *positionals[],
    size_t positional_capacity,
    size_t *positional_count
);
```

This function uses the same `CliOption` definitions as the manual parser, allowing both implementations to populate the same data structure.

Since `getopt()` expects the program name at `argv[0]`, while the project's parser interface receives only the arguments to parse, the implementation creates a temporary argument vector.

It also disables automatic error output and handles errors through the function's return value and `errno`.

**Manual parser versus POSIX `getopt()`**

| Feature | Manual parser | POSIX `getopt()` |
| ------- | ------------- | ---------------- |
| `-n value` | Supported | Supported |
| `-nvalue` | Not supported | Supported |
| `-n=value` | Supported | Parsed as `=value` |
| `-nv` | Not supported | Supported as clustered options |
| `--name` | Supported | Not supported |
| `--name=value` | Supported | Not supported |
| `--` | Supported | Supported |
| Duplicate detection | Implemented | Added by project wrapper |
| Long-option definitions | Supported | Not supported |

`getopt()` is a POSIX interface, not part of ISO C. It is commonly available on Linux and other POSIX-compatible systems.

The `getopt()` implementation uses global variables such as `optind` and `optarg`. Consequently, it is not naturally reentrant and requires care when multiple parsers are used in the same process.

**Advantages**

- Avoids implementing basic short-option parsing manually.
- Handles common option syntax.
- Provides built-in support for required option values.
- Supports short-option clustering.
- Well established on POSIX systems.

**Disadvantages**

- Primarily designed for short options.
- Not part of the ISO C standard.
- Uses global parsing variables.
- Its behavior and available extensions can vary between implementations.

### 6. Numeric Argument Parsing

- Understanding why command-line values are strings.
- Converting strings into signed integers.
- Converting strings into unsigned integers.
- Parsing decimal, hexadecimal, octal, and binary values.
- Detecting invalid numeric input.
- Detecting overflow and underflow.
- Checking incomplete conversions.
- Rejecting negative unsigned input.
- Validating values before using them.

**Project functions**

| Function | Purpose |
| -------- | ------- |
| `cli_parse_i64()` | Parses a string into a signed 64-bit integer. |
| `cli_parse_u64()` | Parses a string into an unsigned 64-bit integer. |

**Core functions**

| Function | Purpose |
| -------- | ------- |
| `strtoll()` | Converts a string into a `long long` integer. |
| `strtoull()` | Converts a string into an `unsigned long long` integer. |
| `isspace()` | Checks whether a character is whitespace. |
| `errno` | Reports conversion errors. |
| `ERANGE` | Indicates a range error. |

**Supporting mechanisms**

| Mechanism | Purpose |
| --------- | ------- |
| `endptr` | Identifies where parsing stopped. |
| `INT64_MIN` / `INT64_MAX` | Define signed 64-bit boundaries. |
| `UINT64_MAX` | Defines the unsigned 64-bit maximum. |
| `base` | Controls the numeric base used for conversion. |

**Example: Parsing a signed integer**

```c
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *text = "-12345";
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

`strtoll()` converts the supplied string into a signed integer.

Three important checks are performed:

- `errno == ERANGE` detects overflow and underflow.
- `endptr == text` detects input containing no valid number.
- `*endptr != '\0'` detects trailing characters and incomplete conversions.

**Example: Parsing an unsigned integer**

```c
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *text = "255";
    char *endptr;

    errno = 0;

    unsigned long long value = strtoull(text, &endptr, 10);

    if (errno == ERANGE || endptr == text || *endptr != '\0') {
        fprintf(stderr, "Invalid unsigned integer.\n");
        return 1;
    }

    if (value > UINT64_MAX) {
        fprintf(stderr, "Value exceeds uint64_t range.\n");
        return 1;
    }

    printf("Value: %llu\n", value);

    return 0;
}
```

`strtoull()` converts strings into unsigned integers. However, it accepts a leading minus sign according to its conversion rules, so the project explicitly rejects negative input before conversion.

**Example: Automatic base detection**

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *endptr;

    // Decimal representation.
    long long decimal = strtoll("42", &endptr, 0);

    // Hexadecimal representation.
    long long hexadecimal = strtoll("0xFF", &endptr, 0);

    // Octal representation.
    long long octal = strtoll("077", &endptr, 0);

    printf("Decimal: %lld\n", decimal);
    printf("Hexadecimal: %lld\n", hexadecimal);
    printf("Octal: %lld\n", octal);

    return 0;
}
```

Passing a base of `0` enables automatic base detection according to the conversion function's rules. A base of `2` can be provided explicitly for binary input.

**Advantages**

- Uses standard C conversion functions.
- Supports different numeric types and bases.
- Allows reliable validation of user input.
- Detects incomplete conversions and range errors.
- Provides reusable conversion functions for multiple commands.

**Disadvantages**

- Requires explicit error checking.
- Conversion functions do not automatically validate application-specific constraints.
- Additional checks are required when converting into narrower integer types.
- Unsigned conversion requires special care around negative input.

### 7. Command Dispatching

- Understanding subcommands.
- Separating command identification from command execution.
- Implementing a command dispatcher.
- Mapping command names to functions.
- Passing command-specific arguments.
- Handling unknown commands.
- Separating CLI parsing from application logic.

**Project functions**

| Function | Purpose |
| -------- | ------- |
| `cli_dispatch()` | Identifies a command and calls its handler. |
| `cli_run_greet()` | Executes the greeting command. |
| `cli_run_calc()` | Executes the calculator command. |
| `cli_run_inspect()` | Inspects an integer's binary representation. |
| `cli_print_usage()` | Displays application usage information. |
| `cli_print_version()` | Displays application version information. |

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

**Project command examples**

```bash
# Display a greeting
./build/ccli greet --name Akshat

# Add two integers
./build/ccli calc add 10 20

# Inspect an integer
./build/ccli inspect -42
```

The application's `main()` function handles global help and version options before passing the selected command and its arguments to `cli_dispatch()`.

Each command handler is responsible for validating its own arguments and performing its operation.

**Advantages**

- Improves code organization.
- Makes individual commands easier to maintain and test.
- Allows new commands to be added independently.
- Prevents the main function from becoming overloaded with application logic.

**Disadvantages**

- Requires a clear command structure.
- Poorly organized dispatch logic can become difficult to maintain as commands grow.
- Each command still needs its own argument validation.

### 8. Error Handling and Validation

- Detecting missing commands.
- Detecting unknown commands.
- Rejecting unknown options.
- Detecting duplicate options.
- Validating option definitions.
- Detecting missing option values.
- Validating positional argument counts.
- Detecting invalid numeric values.
- Detecting integer overflow.
- Producing useful usage messages.
- Returning meaningful exit statuses.

**Core functions and mechanisms**

| Function / Mechanism | Purpose |
| -------------------- | ------- |
| `fprintf()` | Prints error messages to standard error. |
| `perror()` | Prints a description of an error stored in `errno`. |
| `strcmp()` | Validates command and option names. |
| `errno` | Communicates conversion and library errors. |
| `ERANGE` | Indicates numeric range errors. |
| Return values | Communicate success or failure to the caller and shell. |

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

The project follows this convention across its parser, numeric conversion functions, and command handlers.

**Advantages**

- Prevents malformed input from reaching application logic.
- Makes failures easier to understand and debug.
- Produces predictable behavior for scripts and automation.
- Helps prevent invalid numeric values and integer overflow.

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
│   ├── 4. POSIX getopt Parsing.c
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

# Use an attached long-option value
./build/ccli greet --name=Akshat

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

The project includes tests for both argument parsing implementations.

**Manual parser tests**

- Long-option parsing.
- Short-option parsing.
- Attached option values.
- Positional argument collection.
- The `--` option terminator.
- Duplicate option detection.
- Invalid option definitions.
- Unknown options.
- Missing and empty option values.
- Unsupported short-option clustering.
- Positional argument capacity limits.

**POSIX `getopt()` tests**

- Short-option parsing.
- Short-option clustering.
- Separate option values.
- Attached option values.
- The `--` option terminator.
- Missing option values.
- Unknown options.
- Duplicate option detection.
- Positional argument collection and capacity limits.

**Numeric parsing tests**

- Signed integer parsing.
- Unsigned integer parsing.
- Automatic base detection.
- Invalid numeric input.
- Invalid numeric bases.
- Negative unsigned input.
- Signed integer minimum and maximum boundaries.
- Unsigned integer maximum boundary.
- Overflow and underflow detection.

The project also builds with AddressSanitizer and UndefinedBehaviorSanitizer to help detect memory errors and undefined behavior during execution.

## Takeaway

Command-line argument parsing is an important part of building practical C applications. It provides the interface through which users interact with programs, supply input, select operations, and configure application behavior.

Understanding `argc`, `argv`, positional arguments, named options, numeric conversion, and command dispatching makes it possible to build structured and maintainable CLI applications.

Implementing a manual parser provides control over application-specific syntax and helps explain how option parsing works internally. POSIX `getopt()` provides an established alternative for parsing short options and demonstrates how standard system interfaces reduce the amount of custom parsing code.

These concepts are particularly useful when developing developer tools, system utilities, compilers, debuggers, build tools, and command-based applications such as Bitview.
