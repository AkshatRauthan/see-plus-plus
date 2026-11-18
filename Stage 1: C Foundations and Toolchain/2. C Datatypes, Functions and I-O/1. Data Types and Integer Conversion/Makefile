CC       := clang
CFLAGS   := -std=c11 -Wall -Wextra -Wpedantic
SANFLAGS := -fsanitize=undefined -fno-sanitize-recover=undefined

SRC_DIR  := src
BUILD_DIR := build

SOURCES := $(wildcard $(SRC_DIR)/*.c)
TARGETS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%,$(SOURCES))

.PHONY: all clean list

all: $(TARGETS)

$(BUILD_DIR)/%: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o "$@"

# Build and run every experiment.
run: all
	@for program in $(TARGETS); do \
		echo "\n===== $$(basename "$$program") ====="; \
		"$$program" || exit $$?; \
	done

# Build the signed overflow experiment with UBSan.
ubsan: $(BUILD_DIR)/6. Signed Integer Overflow
	$(CC) $(CFLAGS) $(SANFLAGS) \
		"$(SRC_DIR)/6. Signed Integer Overflow.c" \
		-o "$(BUILD_DIR)/signed_overflow_ubsan"

clean:
	rm -rf $(BUILD_DIR)

list:
	@printf '%s\n' $(SOURCES)
