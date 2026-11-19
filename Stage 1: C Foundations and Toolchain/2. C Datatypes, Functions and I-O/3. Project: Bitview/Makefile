# Compiler
CC := clang

# Directories
SRC_DIR := src
BUILD_DIR := build
INCLUDE_DIR := include
TEST_DIR := tests

# Compiler flags
CPPFLAGS := -I$(INCLUDE_DIR)
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -O2 -g
LDLIBS := -lm

# Production sources
SOURCES := $(wildcard $(SRC_DIR)/*.c) \
           $(wildcard $(SRC_DIR)/commands/*.c)
OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
DEPS := $(OBJECTS:.o=.d)
TARGET := bitview

# Test sources (exclude the production main function)
TEST_SOURCES := $(filter-out $(SRC_DIR)/main.c,$(SOURCES))
TEST_TARGET := $(BUILD_DIR)/tests/test_all

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $@ $(LDLIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

$(TEST_TARGET): $(TEST_DIR)/test_all.c $(TEST_SOURCES)
	mkdir -p $(@D)
	$(CC) $(CPPFLAGS) $(CFLAGS) $^ -o $@ $(LDLIBS)

.PHONY: test
test: $(TEST_TARGET)
	./$(TEST_TARGET)

.PHONY: coverage
coverage:
	rm -rf $(BUILD_DIR)/coverage $(BUILD_DIR)/tests
	mkdir -p $(BUILD_DIR)/coverage $(BUILD_DIR)/tests
	$(CC) $(CPPFLAGS) -std=c11 -Wall -Wextra -Wpedantic -O0 -g \
		-fprofile-instr-generate -fcoverage-mapping \
		$(TEST_DIR)/test_all.c $(TEST_SOURCES) -o $(BUILD_DIR)/tests/test_all_cov $(LDLIBS)
	LLVM_PROFILE_FILE=$(BUILD_DIR)/coverage/bitview.profraw ./$(BUILD_DIR)/tests/test_all_cov
	llvm-profdata merge -sparse $(BUILD_DIR)/coverage/bitview.profraw \
		-o $(BUILD_DIR)/coverage/bitview.profdata
	llvm-cov report $(BUILD_DIR)/tests/test_all_cov \
		-instr-profile=$(BUILD_DIR)/coverage/bitview.profdata $(TEST_SOURCES)

.PHONY: coverage-html
coverage-html: coverage
	llvm-cov show $(BUILD_DIR)/tests/test_all_cov \
		-instr-profile=$(BUILD_DIR)/coverage/bitview.profdata \
		$(TEST_SOURCES) -format=html \
		-output-dir=$(BUILD_DIR)/coverage/html

.PHONY: run
run: $(TARGET)
	./$(TARGET)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

-include $(DEPS)