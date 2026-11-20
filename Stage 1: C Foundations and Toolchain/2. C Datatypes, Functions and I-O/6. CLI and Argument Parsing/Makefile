
CC       := clang
CFLAGS   := -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
SANFLAGS := -fsanitize=address,undefined -fno-omit-frame-pointer

BUILD := build

.PHONY: all run test san clean

all: $(BUILD)/ccli

$(BUILD):
	mkdir -p "$(BUILD)"

$(BUILD)/ccli: src/main.c \
               src/1.\ Argument\ Parsing.c \
               src/2.\ Numeric\ Arguments.c \
               src/3.\ Command\ Dispatch.c \
               include/cli.h | $(BUILD)
	$(CC) $(CFLAGS) -Iinclude \
		src/main.c \
		"src/1. Argument Parsing.c" \
		"src/2. Numeric Arguments.c" \
		"src/3. Command Dispatch.c" \
		-o "$(BUILD)/ccli"

$(BUILD)/test_cli: tests/test_cli.c \
                   src/1.\ Argument\ Parsing.c \
                   src/2.\ Numeric\ Arguments.c \
                   include/cli.h | $(BUILD)
	$(CC) $(CFLAGS) -Iinclude \
		tests/test_cli.c \
		"src/1. Argument Parsing.c" \
		"src/2. Numeric Arguments.c" \
		-o "$(BUILD)/test_cli"

run: $(BUILD)/ccli
	./$(BUILD)/ccli

test: $(BUILD)/test_cli
	./$(BUILD)/test_cli

san:
	$(MAKE) clean
	$(MAKE) CFLAGS="$(CFLAGS) $(SANFLAGS)" test
	$(MAKE) CFLAGS="$(CFLAGS) $(SANFLAGS)" all

clean:
	rm -rf "$(BUILD)"
