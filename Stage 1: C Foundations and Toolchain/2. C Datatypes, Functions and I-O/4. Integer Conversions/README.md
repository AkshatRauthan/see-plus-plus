<div align="center">
  <h1>Integer Conversion</h1>
  Exploring integer and floating-point conversions between numeric values and strings in C, including fixed-width types, standard conversion functions, manual conversion algorithms, and error handling.
</div><br />

## Topics Covered

### 1. Integer to String Conversion

- Converting signed integers into strings.
- Converting unsigned integers into strings.
- Supporting fixed-width integer types:
    - `int32_t`
    - `uint32_t`
    - `int64_t`
    - `uint64_t`
- Formatting integers using `snprintf()`.
- Using `<inttypes.h>` format macros:
    - `PRId32`, `PRIu32`
    - `PRId64`, `PRIu64`
- Checking buffer capacity and detecting truncation.
- Understanding null termination and string buffers.
- Implementing manual integer-to-string conversion.

**Core functions and macros**

| Function / Macro   | Purpose                                             |
| ------------------ | --------------------------------------------------- |
| `snprintf()`       | Formats an integer into a bounded character buffer. |
| `vsnprintf()`      | Performs formatted output using a `va_list`.        |
| `PRId32`, `PRIu32` | Portable format specifiers for 32-bit integers.     |
| `PRId64`, `PRIu64` | Portable format specifiers for 64-bit integers.     |

**Example: Using `snprintf()`**

```c
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

int main(void) {
    int32_t value = -12345;
    char buffer[32];

    // Format the integer using its portable format specifier.
    int length = snprintf(buffer, sizeof(buffer), "%" PRId32, value);

    if (length < 0 || (size_t)length >= sizeof(buffer)) {
        return 1;
    }

    printf("String: %s\n", buffer);

    return 0;
}
```

`snprintf()` writes the formatted value into the supplied buffer while respecting its capacity. Unlike `sprintf()`, it prevents writing beyond the specified buffer size.

**Example: Manual conversion**

```c
#include <stdint.h>
#include <stdio.h>

int main(void) {
    int64_t value = -12345;
    char buffer[32];

    // A project-defined function that converts an integer manually.
    manual_i64_to_string(value, buffer, sizeof(buffer));

    printf("String: %s\n", buffer);

    return 0;
}
```

Manual conversion extracts decimal digits using division and modulo operations, stores them in reverse order, and then reverses the sequence to produce the final string. It also needs special handling for `INT64_MIN`, because negating that value cannot be represented by `int64_t`.

**Advantages**

- `snprintf()` is concise, readable, and handles formatting details.
- `<inttypes.h>` macros provide portable format specifiers for fixed-width types.
- Bounded formatting helps prevent buffer overflows.
- Manual conversion demonstrates how numeric values are transformed into character digits.

**Disadvantages**

- `snprintf()` has formatting overhead and requires a correctly sized buffer.
- Format specifiers must match the corresponding argument types.
- Manual conversion requires additional logic for signs, digit ordering, and minimum values.
- Manual implementations are easier to get wrong than standard library functions.

### 2. String to Integer Conversion

- Converting strings into signed integers.
- Converting strings into unsigned integers.
- Supporting fixed-width integer types:
    - `int32_t`
    - `uint32_t`
    - `int64_t`
    - `uint64_t`
- Converting integers using different number bases:
    - Binary (base 2)
    - Octal (base 8)
    - Decimal (base 10)
    - Hexadecimal (base 16)
- Automatically detecting the base using base `0`.
- Handling positive and negative values.
- Detecting invalid characters and incomplete conversions.
- Detecting integer overflow and underflow.
- Validating values before narrowing conversions.

**Core functions**

| Function      | Purpose                                                  |
| ------------- | -------------------------------------------------------- |
| `strtoimax()` | Converts a string into the widest signed integer type.   |
| `strtoumax()` | Converts a string into the widest unsigned integer type. |
| `strtol()`    | Converts a string into a `long`.                         |
| `strtoul()`   | Converts a string into an `unsigned long`.               |
| `strtoll()`   | Converts a string into a `long long`.                    |
| `strtoull()`  | Converts a string into an `unsigned long long`.          |

**Supporting mechanisms**

| Function / Variable      | Purpose                                                            |
| ------------------------ | ------------------------------------------------------------------ |
| `errno`                  | Reports conversion errors such as range violations.                |
| `ERANGE`                 | Indicates that the converted value is outside the supported range. |
| `endptr`                 | Identifies where parsing stopped.                                  |
| `INT32_MIN`, `INT32_MAX` | Define the limits of a 32-bit signed integer.                      |
| `UINT32_MAX`             | Defines the maximum 32-bit unsigned value.                         |
| `INT64_MIN`, `INT64_MAX` | Define the limits of a 64-bit signed integer.                      |
| `UINT64_MAX`             | Defines the maximum 64-bit unsigned value.                         |

**Example: Using `strtoimax()`**

```c
#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *text = "-12345";
    char *endptr;

    // Reset errno before attempting conversion.
    errno = 0;

    // Convert the string into the widest signed integer type.
    intmax_t value = strtoimax(text, &endptr, 10);

    // Check for conversion errors.
    if (errno == ERANGE || endptr == text || *endptr != '\0') {
        fprintf(stderr, "Invalid integer\n");
        return 1;
    }

    printf("Value: %" PRIdMAX "\n", value);

    return 0;
}
```

`strtoimax()` converts the input into `intmax_t`, which can represent any value supported by the standard signed integer types. The `endptr` parameter allows us to detect whether the entire input was successfully consumed.

**Example: Using `strtoumax()` with hexadecimal input**

```c
#include <errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *text = "0xFF";
    char *endptr;

    errno = 0;

    // Base 0 automatically recognizes the hexadecimal prefix.
    uintmax_t value = strtoumax(text, &endptr, 0);

    if (errno == ERANGE || endptr == text || *endptr != '\0') {
        fprintf(stderr, "Invalid unsigned integer\n");
        return 1;
    }

    printf("Value: %" PRIuMAX "\n", value);

    return 0;
}
```

A base of `0` allows the conversion function to infer the number base from the input prefix. For example, `0xFF` is interpreted as hexadecimal, while an unprefixed number is interpreted as decimal.

**Converting into fixed-width types**

The widest conversion functions can be reused to implement conversions into smaller fixed-width types.

```c
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>

int parse_i32(const char *text, int base, int32_t *result) {
    char *endptr;

    errno = 0;

    intmax_t value = strtoimax(text, &endptr, base);

    if (errno == ERANGE || endptr == text || *endptr != '\0') {
        return -1;
    }

    // Validate the target type's range before casting.
    if (value < INT32_MIN || value > INT32_MAX) {
        return -1;
    }

    *result = (int32_t)value;

    return 0;
}
```

This approach avoids directly casting a potentially out-of-range value into a smaller integer type. The range is checked first, and the cast happens only after validation.

**Why prefer `strtoimax()` and `strtoumax()`?**

- They provide access to the widest standard signed and unsigned integer types.
- They support different number bases.
- They expose the parsing endpoint through `endptr`.
- They report range errors through `errno`.
- They allow reusable conversion functions for multiple fixed-width integer types.

**Advantages**

- Supports multiple number bases.
- Provides reliable error detection.
- Detects overflow and underflow.
- Allows validation of partially parsed input.
- Can be reused for fixed-width integer types.

**Disadvantages**

- Requires additional validation using `errno` and `endptr`.
- Does not automatically enforce the range of a smaller target type.
- Base `0` follows prefix-based interpretation rules that may need documenting.
- Unsigned conversion functions can accept a leading minus sign according to C conversion rules, so applications requiring non-negative input must reject it explicitly.

**Why avoid `atoi()`?**

```c
int value = atoi("123");
```

Although `atoi()` is shorter, it does not provide a reliable way to distinguish invalid input from a valid zero or detect range errors. The `strto*()` family is preferred when input validation matters.

### 3. Float to String Conversion

- Converting `float` values into strings.
- Converting `double` values into strings.
- Converting `long double` values into strings.
- Formatting floating-point values using `snprintf()`.
- Understanding decimal precision and round-trip conversion.
- Using the appropriate precision for each floating-point type.
- Handling positive and negative values.
- Representing special values such as infinity and NaN.
- Detecting insufficient output buffer capacity.

**Core functions and macros**

| Function / Macro   | Purpose                                                                                 |
| ------------------ | --------------------------------------------------------------------------------------- |
| `snprintf()`       | Formats floating-point values into a bounded string buffer.                             |
| `FLT_DECIMAL_DIG`  | Decimal digits needed to distinguish `float` values during round-trip conversion.       |
| `DBL_DECIMAL_DIG`  | Decimal digits needed to distinguish `double` values during round-trip conversion.      |
| `LDBL_DECIMAL_DIG` | Decimal digits needed to distinguish `long double` values during round-trip conversion. |
| `DECIMAL_DIG`      | Provides a general decimal precision requirement for floating-point types.              |

**Example: Converting a `float` into a string**

```c
#include <float.h>
#include <stdio.h>

int main(void) {
    float value = 3.1415926f;
    char buffer[64];

    // Use sufficient decimal precision for a float round trip.
    int length = snprintf(
        buffer,
        sizeof(buffer),
        "%.*g",
        FLT_DECIMAL_DIG,
        (double)value
    );

    if (length < 0 || (size_t)length >= sizeof(buffer)) {
        return 1;
    }

    printf("String: %s\n", buffer);

    return 0;
}
```

The `%g` conversion specifier chooses between ordinary decimal and scientific notation. The precision is supplied through `FLT_DECIMAL_DIG`, providing enough decimal digits to preserve a `float` value when converted back.

**Precision requirements**

| Type          | Precision macro    |
| ------------- | ------------------ |
| `float`       | `FLT_DECIMAL_DIG`  |
| `double`      | `DBL_DECIMAL_DIG`  |
| `long double` | `LDBL_DECIMAL_DIG` |

The required decimal precision differs between floating-point types. Using an appropriate macro avoids relying on hardcoded precision values.

**Advantages**

- `snprintf()` provides a standard and flexible formatting mechanism.
- Precision can be selected according to the floating-point type.
- `%g` avoids unnecessarily long decimal output.
- Sufficient precision allows reliable round-trip conversion.

**Disadvantages**

- Floating-point formatting can produce long strings.
- Decimal output may use scientific notation.
- Formatting is affected by the active numeric locale.
- A string representation cannot eliminate the inherent precision limitations of floating-point values.

### 4. String to Float Conversion

- Converting strings into `float` values.
- Converting strings into `double` values.
- Converting strings into `long double` values.
- Parsing decimal and scientific notation.
- Handling positive and negative values.
- Parsing infinity and NaN representations.
- Detecting invalid characters and incomplete conversions.
- Detecting overflow and underflow.
- Validating input before storing converted values.

**Core functions**

| Function    | Purpose                                 |
| ----------- | --------------------------------------- |
| `strtof()`  | Converts a string into a `float`.       |
| `strtod()`  | Converts a string into a `double`.      |
| `strtold()` | Converts a string into a `long double`. |

These functions are the floating-point equivalents of the integer `strto*()` family.

**Example: Using `strtod()`**

```c
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *text = "3.141592653589793";
    char *endptr;

    errno = 0;

    // Convert the string into a double.
    double value = strtod(text, &endptr);

    if (errno == ERANGE || endptr == text || *endptr != '\0') {
        fprintf(stderr, "Invalid floating-point number\n");
        return 1;
    }

    printf("Value: %.15g\n", value);

    return 0;
}
```

`strtod()` converts the input into a `double`. The `endptr` parameter identifies where parsing stopped, allowing the program to reject inputs containing invalid trailing characters.

**Example: Scientific notation**

```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char *endptr;

    // Scientific notation: 1.25 × 10^3.
    double value = strtod("1.25e3", &endptr);

    printf("Value: %.2f\n", value);

    return 0;
}
```

The `e` notation represents a power of ten. Here, `1.25e3` represents `1.25 × 10³`, which evaluates to `1250`.

**Choosing the conversion function**

| Function    | Destination type |
| ----------- | ---------------- |
| `strtof()`  | `float`          |
| `strtod()`  | `double`         |
| `strtold()` | `long double`    |

The conversion function should match the destination type. Using `strtod()` and then casting to `float`, for example, performs the conversion at `double` precision first and then narrows the result.

**Advantages**

- Provides separate conversion functions for each floating-point type.
- Supports decimal and scientific notation.
- Provides parsing endpoint information.
- Reports range errors through `errno`.
- Supports special representations such as infinity and NaN.

**Disadvantages**

- Requires explicit validation of the parsed input.
- Floating-point overflow and underflow require careful handling.
- Floating-point values may not represent decimal fractions exactly.
- Parsing behavior can depend on the active numeric locale.

## Error Handling and Validation

All conversion operations require careful handling of input, output buffers, and numeric ranges.

### Integer Parsing

- Reset `errno` before calling a conversion function.
- Check `ERANGE` to detect range errors.
- Check whether `endptr` points to the beginning of the input.
- Verify that the entire input was consumed.
- Validate the destination type's range before casting.
- Reject negative input when the application requires unsigned values.

### Floating-Point Parsing

- Reset `errno` before calling `strtof()`, `strtod()`, or `strtold()`.
- Check `ERANGE` for range errors.
- Check `endptr` to detect invalid or incomplete input.
- Reject trailing characters when complete input is required.
- Decide explicitly whether special values such as NaN and infinity are acceptable.

### Output Buffer Validation

- Check that the buffer pointer is not `NULL`.
- Ensure that the buffer capacity is greater than zero.
- Check whether `snprintf()` returns a negative value.
- Check whether the returned length is greater than or equal to the buffer capacity.
- Ensure that the output is not used after a failed conversion.

## Build System

The project is implemented in C and compiled using Clang.

**Compiler:** Clang  
**Language Standard:** C11  
**Debug Information:** `-g`  
**Warning Flags:** `-Wall -Wextra -Wpedantic -Wconversion -Wshadow`  
**Sanitizers:** AddressSanitizer and UndefinedBehaviorSanitizer

```bash
# Build and run the tests
make

# Run the tests with AddressSanitizer and UndefinedBehaviorSanitizer
make san

# Remove generated binaries and build files
make clean
```

## Takeaway

Integer and floating-point conversion is an essential part of handling external input and producing readable output in C. The standard library provides reliable conversion functions through `snprintf()`, `strtoimax()`, `strtoumax()`, `strtof()`, `strtod()`, and `strtold()`.

Understanding these functions also means understanding their limitations: numeric ranges, precision, parsing endpoints, buffer capacities, and error reporting. Using the appropriate functions and validating their results makes conversion code safer, more portable, and easier to maintain.

These concepts are particularly useful in command-line applications, configuration parsing, file processing, serialization, network protocols, and systems programming.
