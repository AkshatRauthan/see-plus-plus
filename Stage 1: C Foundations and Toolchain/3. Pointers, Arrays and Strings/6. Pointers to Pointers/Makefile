# Compiler and flags
CC       := clang
CFLAGS   := -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
SANFLAGS := -fsanitize=address,undefined -fno-sanitize-recover=undefined

# Directories
SRC_DIR   := src
BUILD_DIR := build

# Exercise number
N ?= 1

# Use Bash for safe handling of filenames containing spaces.
SHELL := /bin/bash

# Build all exercises.
.PHONY: all
all: | $(BUILD_DIR)
	@set -e; \
	for source in "$(SRC_DIR)"/*.c; do \
		[[ -f "$$source" ]] || continue; \
		name=$$(basename "$$source" .c); \
		echo "Building: $$name"; \
		$(CC) $(CFLAGS) "$$source" -o "$(BUILD_DIR)/$$name"; \
	done

# Create build directory.
$(BUILD_DIR):
	mkdir -p "$(BUILD_DIR)"

# Build and run a specific exercise.
.PHONY: run
run: all
	@set -e; \
	matches=( "$(SRC_DIR)/$(N)."*.c ); \
	if [[ ! -f "$${matches[0]}" ]]; then \
		echo "Exercise $(N) not found."; \
		exit 1; \
	fi; \
	name=$$(basename "$${matches[0]}" .c); \
	echo "Running: $$name"; \
	"$(BUILD_DIR)/$$name"

# Build and run a specific exercise with sanitizers.
.PHONY: san
san: | $(BUILD_DIR)
	@set -e; \
	matches=( "$(SRC_DIR)/$(N)."*.c ); \
	if [[ ! -f "$${matches[0]}" ]]; then \
		echo "Exercise $(N) not found."; \
		exit 1; \
	fi; \
	source="$${matches[0]}"; \
	name=$$(basename "$$source" .c); \
	echo "Building with sanitizers: $$name"; \
	$(CC) $(CFLAGS) $(SANFLAGS) "$$source" -o "$(BUILD_DIR)/$$name"; \
	echo "Running with sanitizers: $$name"; \
	"$(BUILD_DIR)/$$name"

# Remove generated files.
.PHONY: clean
clean:
	rm -rf "$(BUILD_DIR)"

# Available commands:
# make                  - Build all exercises
# make run N=1          - Build and run exercise 1
# make run N=17         - Build and run exercise 17
# make san N=17         - Build and run exercise 17 with sanitizers
# make clean            - Remove generated files
