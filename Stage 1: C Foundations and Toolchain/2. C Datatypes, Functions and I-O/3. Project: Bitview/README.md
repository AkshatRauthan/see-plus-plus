 <div align="center">
  <h1>Bitview</h1>
  Exploring integer representations, bitwise operations, bit manipulation, memory layouts, floating-point representations, and low-level data inspection in C.
</div><br />

## Topics Covered

### 1. Integer Representation

- Signed and unsigned integer types.
- Fixed-width integer types from `<stdint.h>`.
- Integer widths: 8, 16, 32, and 64 bits.
- Two's complement representation.
- Integer ranges and value boundaries.
- Choosing the appropriate integer type.
- Converting and interpreting integer values.

### 2. Binary Representation

- Binary number system and positional representation.
- Bits, bytes, and integer representations.
- Converting integers into binary.
- Inspecting individual bits.
- Signed and unsigned binary representations.
- Understanding bit patterns independently of their numeric interpretation.

### 3. Bitwise Operations

- Bitwise AND (`&`), OR (`|`), XOR (`^`), and NOT (`~`).
- Left shift (`<<`) and right shift (`>>`).
- Arithmetic and logical right shifts.
- Width-dependent bitwise operations.
- Shift boundaries and invalid shift counts.

### 4. Bit Manipulation

- Creating and applying bit masks.
- Setting individual bits.
- Clearing individual bits.
- Toggling individual bits.
- Testing individual bits.
- Extracting bit fields.
- Inserting bit fields.
- Validating bit positions and ranges.

### 5. Bit Analysis

- Counting set bits (population count).
- Counting leading zeros.
- Counting trailing zeros.
- Checking whether a number is a power of two.
- Analyzing binary patterns.

### 6. Memory Inspection and Endianness

- Understanding object representations in memory.
- Inspecting integer bytes.
- Little-endian and big-endian byte ordering.
- Detecting host endianness.
- Understanding the relationship between integer values and memory layouts.
- Inspecting memory using byte-level representations.

### 7. Byte Manipulation

- Extracting individual bytes.
- Inspecting byte sequences.
- Byte swapping.
- Understanding byte order independently of bit order.
- Working with fixed-width integer representations.

### 8. Floating-Point Representation

- IEEE 754 floating-point representation.
- Single-precision (`float`) and double-precision (`double`).
- Sign, exponent, and fraction fields.
- Inspecting floating-point bit patterns.
- Converting between floating-point values and their binary representations.
- Understanding special values: positive and negative zero, infinity, and NaN.
- Floating-point precision and representation limitations.

### 9. Command-Line Interface

- Designing a command-based CLI.
- Parsing command-line arguments.
- Validating numeric input.
- Supporting signed and unsigned integer input.
- Selecting integer widths.
- Handling invalid commands and arguments.
- Separating command dispatching from operation implementations.

### 10. Testing and Validation

- Unit testing individual modules.
- Testing valid and invalid inputs.
- Testing integer boundaries and overflow conditions.
- Testing bit positions and shift boundaries.
- Testing floating-point edge cases.
- Testing CLI argument validation.
- Measuring code coverage with LLVM tools.

## Build System

The project is implemented in C and compiled using Clang.

**Compiler:** Clang  
**Language Standard:** C11  
**Optimization:** `-O2`  
**Debug Information:** `-g`  
**Warning Flags:** `-Wall -Wextra -Wpedantic`

```bash
# Build the project
make

# Run the application
make run

# Run all tests
make test

# Generate coverage data and report
make coverage

# Generate an HTML coverage report
make coverage-html

# Remove generated binaries and build files
make clean
```

## Usage

```bash
# Inspect an integer
./bitview int 42

# Inspect a signed integer with a specific width
./bitview int --signed --width 16 -42

# Inspect an unsigned integer
./bitview int --unsigned 255

# Perform bitwise operations
./bitview and 12 10
./bitview or 12 10
./bitview xor 12 10
./bitview not 12

# Perform bit shifts
./bitview shl 12 2
./bitview shr 12 2

# Manipulate individual bits
./bitview set 10 2
./bitview clear 10 1
./bitview toggle 10 3
./bitview test 10 2

# Extract and insert bit fields
./bitview extract 255 2 4
./bitview insert 0 15 4 4

# Analyze integer bit patterns
./bitview popcount 255
./bitview leading-zeros 16
./bitview trailing-zeros 16
./bitview power-of-two 128

# Inspect memory and byte order
./bitview memory 305419896
./bitview bytes 305419896
./bitview byteswap 305419896
./bitview endian

# Inspect floating-point representations
./bitview float 3.14
./bitview double 3.141592653589793
```

## Takeaway

Bitview provides a practical exploration of how C represents, interprets, analyzes, and manipulates integer and floating-point data at the bit and byte levels. It brings together integer conversions, bitwise operations, memory inspection, endianness, and IEEE 754 representations in a single command-line application.

These concepts form an important foundation for systems programming, debugging, memory analysis, binary protocols, serialization, and low-level software development.