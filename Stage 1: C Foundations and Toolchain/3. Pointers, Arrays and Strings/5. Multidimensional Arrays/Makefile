
CC := clang

CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
OPTFLAGS := -O2
SANFLAGS := -fsanitize=address,undefined -fno-sanitize-recover=undefined

BUILD_DIR := build
SHELL := /bin/bash

.PHONY: all build run run-opt san run-san clean

all: build

# Build every exercise
build:
	@mkdir -p $(BUILD_DIR)
	@while IFS= read -r -d '' source; do \
		name="$${source##*/}"; \
		name="$${name%.c}"; \
		echo "Building: $$source"; \
		$(CC) $(CFLAGS) "$$source" -o "$(BUILD_DIR)/$$name" || exit 1; \
	done < <(find . -maxdepth 1 -type f -name '*.c' -print0)

# Build and run a specific exercise
run:
	@mkdir -p $(BUILD_DIR); \
	source_file=$$(find . -maxdepth 1 -type f -name "$(N).*c" -print -quit); \
	if [[ -z "$$source_file" ]]; then \
		echo "No source file found for N=$(N)"; \
		exit 1; \
	fi; \
	name="$${source_file##*/}"; \
	name="$${name%.c}"; \
	$(CC) $(CFLAGS) "$$source_file" -o "$(BUILD_DIR)/$$name" && \
	"$(BUILD_DIR)/$$name"

# Build and run a specific exercise with optimizations
run-opt:
	@mkdir -p $(BUILD_DIR); \
	source_file=$$(find . -maxdepth 1 -type f -name "$(N).*c" -print -quit); \
	if [[ -z "$$source_file" ]]; then \
		echo "No source file found for N=$(N)"; \
		exit 1; \
	fi; \
	name="$${source_file##*/}"; \
	name="$${name%.c}"; \
	echo "Building with optimization: $$source_file"; \
	$(CC) $(CFLAGS) $(OPTFLAGS) "$$source_file" -o "$(BUILD_DIR)/$$name-opt" && \
	"$(BUILD_DIR)/$$name-opt"

# Build every exercise with sanitizers
san:
	@mkdir -p $(BUILD_DIR)
	@while IFS= read -r -d '' source; do \
		name="$${source##*/}"; \
		name="$${name%.c}"; \
		echo "Building with sanitizers: $$source"; \
		$(CC) $(CFLAGS) $(SANFLAGS) "$$source" -o "$(BUILD_DIR)/$$name-san" || exit 1; \
	done < <(find . -maxdepth 1 -type f -name '*.c' -print0)

# Build and run a specific exercise with sanitizers
run-san:
	@mkdir -p $(BUILD_DIR); \
	source_file=$$(find . -maxdepth 1 -type f -name "$(N).*c" -print -quit); \
	if [[ -z "$$source_file" ]]; then \
		echo "No source file found for N=$(N)"; \
		exit 1; \
	fi; \
	name="$${source_file##*/}"; \
	name="$${name%.c}"; \
	$(CC) $(CFLAGS) $(SANFLAGS) "$$source_file" -o "$(BUILD_DIR)/$$name-san" && \
	"$(BUILD_DIR)/$$name-san"

# Remove generated files
clean:
	rm -rf $(BUILD_DIR)

# ==========================================
# Commands
# ==========================================

# Build all programs
# make
# make build

# Build and run a specific program
# make run N=1
# make run N=2
# make run N=3
# make run N=4
# make run N=5
# make run N=6
# make run N=7
# make run N=8

# Build and run File 8 with optimization (-O2)
# make run-opt N=8

# Build all programs with sanitizers
# make san

# Build and run a specific program with sanitizers
# make run-san N=1
# make run-san N=2
# make run-san N=3
# make run-san N=4
# make run-san N=5
# make run-san N=6
# make run-san N=7
# make run-san N=8

# Remove generated executables
# make clean
