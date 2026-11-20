CC       := clang
CFLAGS   := -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
SANFLAGS := -fsanitize=address,undefined -fno-omit-frame-pointer

BUILD := build

.PHONY: all test san clean

# Build and run the conversion tests.
all: test

test:
	mkdir -p "$(BUILD)"

	$(CC) $(CFLAGS) \
		tests/test_conversion.c \
		"src/1. Integer to String.c" \
		"src/2. String to Integer.c" \
		"src/3. Float to String.c" \
		"src/4. String to Float.c" \
		-o "$(BUILD)/test_conversion"

	"$(BUILD)/test_conversion"

# Rebuild and run tests with AddressSanitizer and UBSan.
san: clean
	$(MAKE) CFLAGS="$(CFLAGS) $(SANFLAGS)" test

# Remove generated build files.
clean:
	rm -rf "$(BUILD)"
