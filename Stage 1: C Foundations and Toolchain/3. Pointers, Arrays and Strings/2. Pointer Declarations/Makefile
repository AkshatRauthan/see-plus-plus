CC := clang

CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
SANFLAGS := -fsanitize=address,undefined -fno-sanitize-recover=undefined

BUILD_DIR := build

SOURCES := \
	1. Reading Pointer Declarations.c \
	2. Arrays of Pointers.c \
	3. Pointers to Arrays.c \
	4. Function Pointer Declarations.c \
	5. Complex Pointer Declarations.c \
	6. Declaration Exercises and Type Interpretation.c

.PHONY: all build run san run-san clean

all: build

build:
	@mkdir -p "$(BUILD_DIR)"
	@set -e; \
	for source in $(foreach file,$(SOURCES),"$(file)"); do \
		name=$$(basename "$$source" .c); \
		output="$(BUILD_DIR)/$$name"; \
		echo "Building $$source"; \
		$(CC) $(CFLAGS) "$$source" -o "$$output"; \
	done

run: build
	@if [ -z "$(N)" ]; then \
		echo "Usage: make run N=1"; exit 1; \
	fi
	@source=$$(find . -maxdepth 1 -type f -name "$(N).*\.c" -print -quit); \
	if [ -z "$$source" ]; then \
		echo "Exercise $(N) not found"; exit 1; \
	fi; \
	name=$$(basename "$$source" .c); \
	"$(BUILD_DIR)/$$name"

san:
	@mkdir -p "$(BUILD_DIR)"
	@set -e; \
	for source in $(foreach file,$(SOURCES),"$(file)"); do \
		name=$$(basename "$$source" .c); \
		output="$(BUILD_DIR)/$$name-san"; \
		echo "Building with sanitizers: $$source"; \
		$(CC) $(CFLAGS) $(SANFLAGS) "$$source" -o "$$output"; \
	done

run-san: san
	@if [ -z "$(N)" ]; then \
		echo "Usage: make run-san N=1"; exit 1; \
	fi
	@source=$$(find . -maxdepth 1 -type f -name "$(N).*\.c" -print -quit); \
	if [ -z "$$source" ]; then \
		echo "Exercise $(N) not found"; exit 1; \
	fi; \
	name=$$(basename "$$source" .c); \
	"$(BUILD_DIR)/$$name-san"

clean:
	rm -rf "$(BUILD_DIR)"
