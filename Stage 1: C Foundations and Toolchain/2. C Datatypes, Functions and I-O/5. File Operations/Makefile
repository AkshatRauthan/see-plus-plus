CC       := clang
CFLAGS   := -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
SANFLAGS := -fsanitize=address,undefined -fno-omit-frame-pointer

BUILD := build

.PHONY: all test san clean

all: test

test:
	mkdir -p "$(BUILD)"

	$(CC) $(CFLAGS) \
		tests/test_file_operations.c \
		"src/1. File Handling Fundamentals.c" \
		"src/2. Text File Reading.c" \
		"src/3. Text File Writing.c" \
		"src/4. Binary File Operations.c" \
		"src/5. File Positioning.c" \
		-o "$(BUILD)/test_file_operations"

	"$(BUILD)/test_file_operations"

san: clean
	$(MAKE) CFLAGS="$(CFLAGS) $(SANFLAGS)" test

clean:
	rm -rf "$(BUILD)"
	