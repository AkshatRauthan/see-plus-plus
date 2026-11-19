# Tests

Run the complete test suite:

```sh
make test
```

Run LLVM source-based coverage:

```sh
make coverage
```

Generate an HTML coverage report:

```sh
make coverage-html
```

The test executable is built from `tests/test_all.c` and every production source
file except `src/main.c`, so the CLI dispatcher is exercised directly without
launching a second `main()`.

The suite currently performs 261 checks across parsing, integer helpers,
bitwise operations, bit manipulation, bit analysis, memory/endianness,
floating-point inspection, and CLI argument handling.

Coverage is measured, not assumed. The current report is below 100%; uncovered
lines and branches must be reviewed in the LLVM report before claiming complete
coverage. Some platform-dependent branches (for example, non-IEEE-754 hardware)
cannot be exercised on a platform that does not provide such hardware.
