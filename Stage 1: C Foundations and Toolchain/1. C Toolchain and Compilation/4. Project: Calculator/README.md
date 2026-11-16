<p align="center"><br />
	<strong style="font-size: 30px;">Project: Expression Calculator in C</strong> <br />   
	A command-line expression evaluator supporting arithmetic operations, nested brackets, infix-to-postfix conversion, stack-based evaluation, and automated testing.
</p>

## Building the Project

The project uses Clang as its compiler and GNU Make to automate the build process.

```bash
make
```

The Makefile compiles the source files separately and links them into an executable:

```text
build/calc
```

The generated executable and object files are stored inside the `build/` directory.

Run the calculator using:

```bash
./build/calc 5 + 3 '*' '(' 8 - 2 ')'
```

Output:

```text
23
```

### Input Format

The calculator accepts expressions through command-line arguments (`argv`). **Each operand, operator, and bracket must be provided as a separate argument.**

For example:

```bash
./build/calc '{' [ '(' 2.5 + 1.5 ')' '*' -3 ] // 5 '}' + 4 '!' % 7 - 2 ^ 3 ^ 1
```

The shell passes these arguments individually to the program, and the lexer converts them into structured tokens.

Do not pass the entire expression as a single quoted string. Shell-special characters such as `*`, `(`, `)`, `[`, `]`, `{`, `}`, and `!` should be quoted or escaped where necessary.

## Compiler Flags

| Flag         | Description                                         |
| ------------ | --------------------------------------------------- |
| `-Wall`      | Enables common compiler warnings.                   |
| `-Wextra`    | Enables additional compiler warnings.               |
| `-Wpedantic` | Reports language-standard portability issues.       |
| `-std=c11`   | Compiles using the C11 language standard.           |
| `-O2`        | Enables compiler optimizations.                     |
| `-MMD`       | Generates dependency files for header dependencies. |
| `-MP`        | Adds dummy targets for header dependencies.         |
| `-lm`        | Links the mathematical library.                     |

## Supported Operations

The calculator supports the following arithmetic operations:

| Operator | Operation      | Example  | Result |
| -------- | -------------- | -------- | ------ |
| `+`      | Addition       | `5 + 3`  | `8`    |
| `-`      | Subtraction    | `5 - 3`  | `2`    |
| `*`      | Multiplication | `5 * 3`  | `15`   |
| `/`      | Division       | `5 / 2`  | `2.5`  |
| `//`     | Floor Division | `5 // 2` | `2`    |
| `%`      | Modulo         | `5 % 2`  | `1`    |
| `^`      | Exponentiation | `2 ^ 3`  | `8`    |
| `!`      | Factorial      | `5 !`    | `120`  |

The calculator also supports nested round `()`, square `[]`, and curly `{}` brackets.

## Expression Processing

The calculator processes expressions through four stages:

### 1. Lexical Analysis

The lexer processes command-line arguments and converts them into structured tokens.

Each token stores information about its type, numeric value, operator, or bracket.

### 2. Syntax Validation

Before conversion, the parser validates the infix expression to ensure that:

- Operands and operators appear in valid sequences.
- Operators are placed correctly.
- Brackets are properly matched.
- Expressions are neither empty nor incomplete.
- No unexpected tokens are present.

### 3. Infix-to-Postfix Conversion

The parser implements Dijkstra's Shunting-yard algorithm to convert infix expressions into postfix notation.

The algorithm uses an operator stack to handle:

- Operator precedence.
- Operator associativity.
- Nested brackets.
- Postfix factorial operations.

For example:

```text
Infix:   5 + 3 * 2
Postfix: 5 3 2 * +
```

### 4. Postfix Evaluation

The evaluator processes the postfix expression using an operand stack.

- Operands are pushed onto the stack.
- Operators consume their required operands.
- The calculated result is pushed back onto the stack.
- A valid expression must leave exactly one value on the stack.

## Error Handling

The calculator performs validation and runtime checks to handle invalid expressions and arithmetic operations.

These include:

- Invalid expression syntax.
- Mismatched and unclosed brackets.
- Insufficient or excess operands.
- Division and modulo by zero.
- Invalid factorial operands.
- Arithmetic overflow and non-finite results.

## Testing

The project includes a test suite covering individual modules as well as the complete expression-processing pipeline.

Run all test suites using:

```bash
make test
```

The tests are compiled into:

```text
build/tests/
```

### Individual Test Suites

| Command                 | Description                             |
| ----------------------- | --------------------------------------- |
| `make test-lexer`       | Tests lexical analysis.                 |
| `make test-parser`      | Tests syntax validation and parsing.    |
| `make test-evaluator`   | Tests postfix expression evaluation.    |
| `make test-integration` | Tests the complete processing pipeline. |

### Test Coverage

The test suites cover:

- Operand and operator tokenization.
- Numeric and negative operands.
- Operator precedence and associativity.
- Nested and mismatched brackets.
- Syntax errors and incomplete expressions.
- Infix-to-postfix conversion.
- Arithmetic operations and factorial evaluation.
- Division and modulo by zero.
- Invalid operands and arithmetic overflow.
- End-to-end expression evaluation.

## Makefile Commands

| Command                 | Description                               |
| ----------------------- | ----------------------------------------- |
| `make`                  | Builds the calculator.                    |
| `make test`             | Builds and runs all test suites.          |
| `make test-lexer`       | Builds and runs the lexer tests.          |
| `make test-parser`      | Builds and runs the parser tests.         |
| `make test-evaluator`   | Builds and runs the evaluator tests.      |
| `make test-integration` | Builds and runs integration tests.        |
| `make clean`            | Removes the generated `build/` directory. |
| `make rebuild`          | Cleans and rebuilds the project.          |
| `make -j$(nproc)`       | Builds using parallel compilation.        |
| `make CC=gcc`           | Builds using GCC instead of Clang.        |

## Takeaway

Explored the implementation of a command-line expression evaluator in C. Applied lexical analysis, syntax validation, Dijkstra's Shunting-yard algorithm, operator precedence and associativity, and stack-based postfix evaluation.

Also gained practical experience with modular C programming, data structures, memory management, compiler optimizations, automated testing, and build automation using GNU Make.
