CC := clang
SHELL := /bin/bash

CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
SANFLAGS := -fsanitize=address,undefined -fno-sanitize-recover=undefined

BUILD_DIR := build

# Keep filenames quoted because they contain spaces.
SOURCES := \
	'1. Pointer Arithmetic Fundamentals.c' \
	'2. Pointer Addition and Subtraction.c' \
	'3. Pointer Comparisons.c' \
	'4. Pointer Arithmetic with Structures.c' \
	'5. Pointer Arithmetic with Multidimensional Arrays.c' \
	'6. Pointer Arithmetic and Byte-Level Memory Access.c' \
	'7. Pointer Arithmetic Restrictions and Undefined Behavior.c' \
	'8. Pointer Arithmetic Practical Exercises.c'

.PHONY: all build run san run-san clean

all: build

build:
	@mkdir -p "$(BUILD_DIR)"
	@set -e; \
	for source in $(SOURCES); do \
		name=$$(basename "$$source" .c); \
		output="$(BUILD_DIR)/$$name"; \
		echo "Building: $$source"; \
		$(CC) $(CFLAGS) "$$source" -o "$$output"; \
	done
	@echo "All exercises built successfully."

run: build
	@if [ -z "$(N)" ]; then \
		echo "Usage: make run N=1"; \
		exit 1; \
	fi
	@source=$$(find . -maxdepth 1 -type f -name "$(N).*c" -print -quit); \
	if [ -z "$$source" ]; then \
		echo "Exercise $(N) not found."; \
		exit 1; \
	fi; \
	name=$$(basename "$$source" .c); \
	"$(BUILD_DIR)/$$name"

san:
	@mkdir -p "$(BUILD_DIR)"
	@set -e; \
	for source in $(SOURCES); do \
		name=$$(basename "$$source" .c); \
		output="$(BUILD_DIR)/$$name-san"; \
		echo "Building with sanitizers: $$source"; \
		$(CC) $(CFLAGS) $(SANFLAGS) "$$source" -o "$$output"; \
	done
	@echo "All sanitizer builds completed successfully."

run-san: san
	@if [ -z "$(N)" ]; then \
		echo "Usage: make run-san N=1"; \
		exit 1; \
	fi
	@source=$$(find . -maxdepth 1 -type f -name "$(N).*c" -print -quit); \
	if [ -z "$$source" ]; then \
		echo "Exercise $(N) not found."; \
		exit 1; \
	fi; \
	name=$$(basename "$$source" .c); \
	"$(BUILD_DIR)/$$name-san"

clean:
	rm -rf "$(BUILD_DIR)"
	@echo "Build directory cleaned."
