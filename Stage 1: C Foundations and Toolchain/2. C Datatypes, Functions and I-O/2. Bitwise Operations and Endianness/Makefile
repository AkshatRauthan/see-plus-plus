
CC       := clang
CFLAGS   := -std=c11 -Wall -Wextra -Wpedantic

SRC_DIR  := src
BUILD_DIR := build

# Discover all C source files.
SOURCES := $(wildcard $(SRC_DIR)/*.c)

# Generate corresponding executable paths.
TARGETS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%,$(SOURCES))

.PHONY: all run clean list

# Build every experiment.
all: $(TARGETS)

# Compile each source file independently.
$(BUILD_DIR)/%: $(SRC_DIR)/%.c
	@mkdir -p "$(BUILD_DIR)"
	$(CC) $(CFLAGS) "$<" -o "$@"

# Run every compiled experiment.
run: all
	@for program in $(TARGETS); do \
		printf '\n===== %s =====\n' "$$(basename "$$program")"; \
		"$$program" || exit $$?; \
	done

# Run a specific experiment.
# Usage: make run-one FILE="1. Binary Representations"
run-one:
	@$(MAKE) "$(BUILD_DIR)/$(FILE)"
	@"$(BUILD_DIR)/$(FILE)"

# Display discovered source files.
list:
	@printf '%s\n' $(SOURCES)

# Remove generated executables.
clean:
	rm -rf "$(BUILD_DIR)"
