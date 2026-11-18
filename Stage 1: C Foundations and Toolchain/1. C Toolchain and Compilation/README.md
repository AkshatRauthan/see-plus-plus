<div align="center">
  <h1>Module 1: C Toolchain and Compilation</h1>
  Exploring the C compilation pipeline, multi-file builds, Makefiles, debugging with LLDB, and building a complete command-line calculator.
</div><br />

<div align="center">
  <img src="https://img.shields.io/badge/Started_On-14_Nov_2026-2EA44F?style=for-the-badge&logo=calendar&logoColor=white" alt="Started On" />
  <img src="https://img.shields.io/badge/Progress-Completed-FF69A0?style=for-the-badge&logo=progress&logoColor=white" alt="Progress" />
  <img src="https://img.shields.io/badge/Completed_On-16_Nov_2026-2976BB?style=for-the-badge&logo=checkmarx&logoColor=white" alt="Completed On" />
</div>

## Module Overview

This module focuses on understanding the C development toolchain, from compiling a simple source file to building and debugging a multi-file C project.

It is divided into four parts:

| Part | Topic                              | Description                                                                                                                                    |
| ---- | ---------------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------- |
| 1    | C Compilation Pipeline             | Understanding the stages of compilation and examining preprocessed, assembly, object, and executable files.                                    |
| 2    | Multi File Builds and Makefiles    | Working with multiple source files, header files, object files, dependency generation, and automated builds using GNU Make.                    |
| 3    | Using LLDB Toolchain For Debugging | Learning to debug C programs using LLDB, including breakpoints, stepping through execution, inspecting variables, and examining program state. |
| 4    | Project: Calculator                | Applying the toolchain concepts to build a command-line expression evaluator in C.                                                             |

## Topics Covered

### 1. C Compilation Pipeline

Explored how a C source file is transformed into an executable through the compilation pipeline.

- Preprocessing and macro expansion.
- Compilation and assembly generation.
- Assembly and object file generation.
- Linking and executable generation.
- Inspecting intermediate compilation outputs.
- Understanding compiler flags and optimization levels.

### 2. Multi File Builds and Makefiles

Learned how to organize and build C projects containing multiple source and header files.

- Separating declarations and implementations.
- Using header files and include guards.
- Compiling source files independently.
- Linking object files into executables.
- Writing Makefiles with targets, prerequisites, and recipes.
- Generating and tracking header dependencies.
- Using GNU Make for incremental and parallel builds.

### 3. Debugging with LLDB

Explored the LLDB debugging toolchain and its role in understanding program execution.

- Compiling programs with debugging symbols.
- Setting and managing breakpoints.
- Stepping through program execution.
- Inspecting variables and expressions.
- Examining stack frames and call stacks.
- Identifying and investigating runtime errors.

### 4. Project: Expression Calculator in C

Developed a command-line expression evaluator supporting arithmetic operations and nested brackets.

The project brings together concepts from the previous parts:

- **Lexical Analysis:** Converting command-line arguments into structured tokens.
- **Syntax Validation:** Checking expression structure and bracket matching.
- **Infix-to-Postfix Conversion:** Implementing Dijkstra's Shunting-yard algorithm.
- **Stack-Based Evaluation:** Evaluating postfix expressions using an operand stack.
- **Error Handling:** Handling invalid expressions and arithmetic errors.
- **Automated Testing:** Writing unit and integration tests for individual modules and the complete processing pipeline.
- **Build Automation:** Organizing compilation and testing through GNU Make.

## Tools and Technologies

| Tool / Technology | Purpose                 |
| ----------------- | ----------------------- |
| C (C11)           | Programming language    |
| Clang             | C compiler              |
| GNU Make          | Build automation        |
| LLDB              | Debugging               |
| Git               | Version control         |
| Linux             | Development environment |

## Key Takeaways

Developed an understanding of the C compilation pipeline, multi-file project organization, linking, build automation, and debugging with LLDB.

Applied these concepts by building a modular command-line calculator with lexical analysis, syntax validation, infix-to-postfix conversion, stack-based evaluation, and automated tests.

Gained practical experience with compiler toolchains, object files, dependency management, debugging workflows, data structures, memory management, and software testing.
