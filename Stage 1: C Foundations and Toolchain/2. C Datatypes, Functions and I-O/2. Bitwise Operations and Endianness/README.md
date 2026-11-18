<div align="center">
	<h1>Bitwise Operations and Endianness</h1> 
	Exploring binary representations, bitwise operations, memory layouts, byte manipulation, and endianness in C. 
</div><br />

## Topics Covered

### 1. Binary Representation

- Binary number system and positional representation.
- Bits, bytes, and integer representations.
- Signed and unsigned integer representations.
- Two's complement representation.
- Object representation in C.

### 2. Bitwise Operators

- Bitwise AND (`&`), OR (`|`), XOR (`^`), and NOT (`~`).
- Left shift (`<<`) and right shift (`>>`).
- Integer promotions in bitwise expressions.
- Shift-related undefined and implementation-defined behavior.

### 3. Bit Masks and Bit Manipulation

- Creating bit masks.
- Setting, clearing, toggling, and testing individual bits.
- Extracting and inserting bit fields.
- Combining flags and common bit manipulation patterns.

### 4. Bit Fields

- Declaring bit fields in structures.
- Specifying field widths and types.
- Accessing and modifying bit fields.
- Implementation-defined allocation and layout.
- Use cases and limitations.

### 5. Endianness

- Little-endian and big-endian byte ordering.
- Detecting host byte order.
- Inspecting memory byte by byte.
- Network byte order.
- Host-to-network and network-to-host conversions.

### 6. Object Representation and Memory Inspection

- Inspecting object representations using `unsigned char`.
- Examining memory through pointers.
- Using `memcpy()` to inspect object representations.
- Structure padding and alignment.
- Strict aliasing considerations.
- Integer representation versus byte order.

### 7. Byte Manipulation

- Extracting individual bytes.
- Combining bytes into integers.
- Byte swapping.
- Portable byte-order handling.

### 8. Serialization and Deserialization

- Converting integers into byte sequences.
- Reconstructing integers from serialized data.
- Defining explicit byte order.
- Understanding portable binary representations.

### 9. Practical Exercises

- Counting set bits.
- Checking powers of two.
- Extracting and inserting bit fields.
- Byte swapping.
- Detecting host endianness.
- Combining bit manipulation techniques.

## Build System

The experiments are implemented as independent C programs and compiled using Clang.

**Compiler:** Clang
**Language Standard:** C11
**Warning Flags:** `-Wall -Wextra -Wpedantic`

```bash
# Build all experiments
make

# Run all experiments
make run

# List source files
make list

# Remove generated binaries
make clean
```

## Takeaway

This module develops a practical understanding of how C represents and manipulates data at the bit and byte levels. These concepts are fundamental to systems programming, memory inspection, binary protocols, serialization, and low-level data handling.
