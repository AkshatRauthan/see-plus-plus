 <div align="center">
  <h1>Data Types and Integer Conversions</h1>
  Exploring C's fundamental integer types, integer representations, type conversions, and arithmetic behavior.
</div><br />

## Integer Types

Explored C's fundamental integer types, including their sizes, ranges, and signedness.

- Fundamental integer types: `char`, `short`, `int`, `long`, and `long long`.
- Signed and unsigned integer variants.
- Type sizes using `sizeof`.
- Minimum value ranges defined by the C standard.

## Fixed-Width Integer Types

Explored integer types provided by `<stdint.h>`:

- Exact-width types: `intN_t` and `uintN_t`.
- Minimum-width types: `int_leastN_t` and `uint_leastN_t`.
- Fast integer types: `int_fastN_t` and `uint_fastN_t`.
- Pointer-sized integer types: `intptr_t` and `uintptr_t`.

Compared minimum-width and fast-width types and examined their implementation-dependent sizes.

## Integer Promotions

Studied how integer types with rank lower than `int` are promoted before arithmetic and other operations.

- Promotion of `char` and `short` to `int` or `unsigned int`.
- Integer promotions in arithmetic expressions.
- Integer promotions in comparisons.
- Resulting expression types using `sizeof`.

## Usual Arithmetic Conversions

Explored how C converts arithmetic operands to a common type before evaluating expressions.

- Conversions between different integer ranks.
- Signed and unsigned arithmetic conversions.
- Integer and floating-point conversions.
- Effects of conversions on comparisons and arithmetic results.

## Implicit and Explicit Conversions

Examined automatic conversions and conversions requested through cast operators.

- Implicit conversions between integer and floating-point types.
- Explicit conversions using casts.
- Narrowing conversions and potential data loss.
- Signed-to-unsigned and unsigned-to-signed conversions.
- Floating-point to integer conversions and truncation.

## Signed Overflow and Unsigned Arithmetic

Studied the different arithmetic rules for signed and unsigned integer types.

- Signed integer overflow and undefined behavior (UB).
- Unsigned integer overflow and modular arithmetic.
- Unsigned underflow and wraparound.
- Integer limits using `<limits.h>`.
- Detecting signed overflow using UndefinedBehaviorSanitizer (UBSan).

## Build System

Created a Makefile to compile and manage the individual experiments.

- Compiling each source file independently.
- Using Clang with `-std=c11`, `-Wall`, `-Wextra`, and `-Wpedantic`.
- Building all experiments into a dedicated `build/` directory.
- Running experiments through Makefile targets.
- Building the signed overflow experiment with UBSan.

## Takeaway

Explored C's integer type system, integer promotions, arithmetic conversions, and the distinction between defined unsigned wraparound and undefined signed overflow. Gained practical experience examining how the C language handles integer values and expressions across different types.