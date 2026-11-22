CC       := clang
CFLAGS   := -std=c11 -Wall -Wextra -Wpedantic -Wconversion -Wshadow -g
SANFLAGS := -fsanitize=address,undefined -fno-omit-frame-pointer

BUILD := build

N ?= 1

TARGETS := \
	$(BUILD)/1-memory-addresses \
	$(BUILD)/2-pointer-declaration \
	$(BUILD)/3-address-of \
	$(BUILD)/4-dereference \
	$(BUILD)/5-modifying-variables \
	$(BUILD)/6-pointer-types \
	$(BUILD)/7-generic-pointers \
	$(BUILD)/8-null-pointers \
	$(BUILD)/9-pointer-sizes

.PHONY: all run san run-san clean

all: $(TARGETS)

$(BUILD):
	mkdir -p "$(BUILD)"

# 1. Memory Addresses
$(BUILD)/1-memory-addresses: src/1.\ Memory\ Addresses.c | $(BUILD)
	$(CC) $(CFLAGS) "$<" -o "$@"

# 2. Pointer Declaration and Initialization
$(BUILD)/2-pointer-declaration: src/2.\ Pointer\ Declaration\ and\ Initialization.c | $(BUILD)
	$(CC) $(CFLAGS) "$<" -o "$@"

# 3. Address-of Operator
$(BUILD)/3-address-of: src/3.\ Address-of\ Operator.c | $(BUILD)
	$(CC) $(CFLAGS) "$<" -o "$@"

# 4. Dereference Operator
$(BUILD)/4-dereference: src/4.\ Dereference\ Operator.c | $(BUILD)
	$(CC) $(CFLAGS) "$<" -o "$@"

# 5. Modifying Variables Through Pointers
$(BUILD)/5-modifying-variables: src/5.\ Modifying\ Variables\ Through\ Pointers.c | $(BUILD)
	$(CC) $(CFLAGS) "$<" -o "$@"

# 6. Pointer Types
$(BUILD)/6-pointer-types: src/6.\ Pointer\ Types.c | $(BUILD)
	$(CC) $(CFLAGS) "$<" -o "$@"

# 7. Generic Pointers
$(BUILD)/7-generic-pointers: src/7.\ Generic\ Pointers\ \(void\ \*\).c | $(BUILD)
	$(CC) $(CFLAGS) "$<" -o "$@"

# 8. Null Pointers
$(BUILD)/8-null-pointers: src/8.\ Null\ Pointers\ \(NULL\).c | $(BUILD)
	$(CC) $(CFLAGS) "$<" -o "$@"

# 9. Pointer Sizes and sizeof
$(BUILD)/9-pointer-sizes: src/9.\ Pointer\ Sizes\ and\ sizeof.c | $(BUILD)
	$(CC) $(CFLAGS) "$<" -o "$@"

# Build and execute a selected program.
# Usage: make run N=1
run:
	@case "$(N)" in \
		1) target="$(BUILD)/1-memory-addresses" ;; \
		2) target="$(BUILD)/2-pointer-declaration" ;; \
		3) target="$(BUILD)/3-address-of" ;; \
		4) target="$(BUILD)/4-dereference" ;; \
		5) target="$(BUILD)/5-modifying-variables" ;; \
		6) target="$(BUILD)/6-pointer-types" ;; \
		7) target="$(BUILD)/7-generic-pointers" ;; \
		8) target="$(BUILD)/8-null-pointers" ;; \
		9) target="$(BUILD)/9-pointer-sizes" ;; \
		*) echo "Usage: make run N=1..9"; exit 2 ;; \
	esac; \
	$(MAKE) "$$target" && "$$target"

# Rebuild all programs with sanitizers.
san: clean
	$(MAKE) CFLAGS="$(CFLAGS) $(SANFLAGS)" all

# Build with sanitizers and execute a selected program.
run-san: san
	$(MAKE) run N="$(N)"

# Remove generated executables.
clean:
	rm -rf "$(BUILD)"
