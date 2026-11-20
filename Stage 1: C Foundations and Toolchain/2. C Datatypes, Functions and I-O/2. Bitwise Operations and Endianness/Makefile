SHELL    := /bin/bash
CC       := clang
CFLAGS   := -std=c11 -g -Wall -Wextra -Wpedantic
SANFLAGS := -fsanitize=address,undefined -fno-sanitize-recover=undefined

SRC_DIR   := src
BUILD_DIR := build

.PHONY: all run one san clean list

# Build every experiment, in numeric order.
all:
	@mkdir -p $(BUILD_DIR)
	@while IFS= read -r -u 3 f; do \
		out="$(BUILD_DIR)/$$(basename "$$f" .c)"; \
		echo "CC  $$f"; \
		$(CC) $(CFLAGS) "$$f" -o "$$out" || exit 1; \
	done 3< <(printf '%s\n' $(SRC_DIR)/*.c | sort -V)

# Build and run every experiment, in numeric order.
run: all
	@while IFS= read -r -u 3 f; do \
		out="$(BUILD_DIR)/$$(basename "$$f" .c)"; \
		printf '\n===== %s =====\n' "$$(basename "$$f" .c)"; \
		"$$out" || exit $$?; \
	done 3< <(printf '%s\n' $(SRC_DIR)/*.c | sort -V)

# Build and run one experiment by its number:  make one N=10
one:
	@test -n "$(N)" || { echo "usage: make one N=<number>"; exit 1; }
	@mkdir -p $(BUILD_DIR)
	@set -- $(SRC_DIR)/$(N).\ *.c; \
	test -f "$$1" || { echo "no experiment numbered $(N)"; exit 1; }; \
	out="$(BUILD_DIR)/$$(basename "$$1" .c)"; \
	$(CC) $(CFLAGS) "$$1" -o "$$out" && "$$out"

# Same, with ASan + UBSan:  make san N=6
san:
	@test -n "$(N)" || { echo "usage: make san N=<number>"; exit 1; }
	@mkdir -p $(BUILD_DIR)
	@set -- $(SRC_DIR)/$(N).\ *.c; \
	test -f "$$1" || { echo "no experiment numbered $(N)"; exit 1; }; \
	out="$(BUILD_DIR)/$$(basename "$$1" .c).san"; \
	$(CC) $(CFLAGS) $(SANFLAGS) "$$1" -o "$$out" && "$$out"

clean:
	rm -rf $(BUILD_DIR)

list:
	@printf '%s\n' $(SRC_DIR)/*.c | sort -V