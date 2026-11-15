 <p align="center">
  <br /><strong style="font-size: 30px;">C Debugging with LLDB</strong> <br />
  Exploring debugging techniques using Clang and LLDB, including breakpoints, stepping, call-stack inspection, and watchpoints.
</p>

## Building the Project

The project uses Clang as its compiler and GNU Make to automate the build process.

```bash
make
```

The Makefile compiles the source file into an executable:

```bash
clang -Wall -Wextra -Wpedantic -g -O0 \
    src/main.c -o build/debug-exercise
```

The generated executable is stored inside the `build/` directory.

## Compiler Flags

| Flag         | Description                                               |
| ------------ | --------------------------------------------------------- |
| `-Wall`      | Enables common compiler warnings.                         |
| `-Wextra`    | Enables additional compiler warnings.                     |
| `-Wpedantic` | Reports language-standard portability issues.             |
| `-g`         | Includes debugging symbols for LLDB.                      |
| `-O0`        | Disables compiler optimizations to make debugging easier. |

## Debugging with LLDB

LLDB is the LLVM debugger and is used to inspect program execution and investigate runtime errors.

Launch LLDB using:

```bash
make debug
```

Alternatively:

```bash
lldb ./build/debug-exercise
```

Start program execution:

```lldb
run
```

The program deliberately triggers a segmentation fault by dereferencing a null pointer.

## Debugging Commands

The following LLDB commands are used to investigate the program:

| Command                          | Description                                                                   |
| -------------------------------- | ----------------------------------------------------------------------------- |
| `bt`                             | Displays the current call stack.                                              |
| `print`                          | Evaluates and displays variable values.                                       |
| `watchpoint set variable`        | Monitors a variable for changes.                                              |
| `breakpoint set`                 | Sets a breakpoint at a function or source location.                           |
| `step`                           | Executes the next source line, entering function calls.                       |
| `next`                           | Executes the next source line without entering function calls.                |
| `finish`                         | Continues execution until the current function returns.                       |
| `breakpoint set --one-shot true` | Creates a breakpoint that automatically disables itself after being hit once. |

## Segmentation Fault Investigation

The program contains a deliberate null-pointer dereference:

```c
void modify(int *ptr) {
    *ptr = 100;
}
```

The function receives a null pointer, making the dereference invalid.

Using LLDB, the crash is investigated by:

- Inspecting the call stack to identify the sequence of function calls.
- Examining pointer values to locate the invalid pointer.
- Setting watchpoints to observe changes in variable values.
- Using breakpoints and stepping commands to follow program execution.

## Makefile Commands

| Command      | Description                                 |
| ------------ | ------------------------------------------- |
| `make`       | Compiles the debugging exercise.            |
| `make run`   | Executes the program.                       |
| `make debug` | Launches LLDB with the compiled executable. |
| `make clean` | Removes generated files and the executable. |

## Takeaway

Explored interactive debugging using LLVM's LLDB debugger. Practised inspecting call stacks, examining variable values, tracking variable modifications with watchpoints, and controlling program execution through breakpoints and stepping commands. Also investigated a deliberate segmentation fault to understand how invalid pointer operations cause runtime failures.
