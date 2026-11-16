CC := clang

TARGET := build/calc
SRC_DIR := src
BUILD_DIR := build
TEST_DIR := tests
TEST_BUILD_DIR := $(BUILD_DIR)/tests

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

CPPFLAGS := -Iinclude
CFLAGS := -Wall -Wextra -Wpedantic -std=c11 -O2 -MMD -MP
LDLIBS := -lm

TEST_CFLAGS := $(filter-out -MMD -MP,$(CFLAGS))

TESTS := \
	$(TEST_BUILD_DIR)/test_lexer \
	$(TEST_BUILD_DIR)/test_parser \
	$(TEST_BUILD_DIR)/test_evaluator \
	$(TEST_BUILD_DIR)/test_integration

.PHONY: all clean rebuild test \
	test-lexer test-parser test-evaluator test-integration

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

$(TEST_BUILD_DIR):
	mkdir -p $@

$(TEST_BUILD_DIR)/test_lexer: $(TEST_DIR)/test_lexer.c $(TEST_DIR)/test_common.h src/lexer.c | $(TEST_BUILD_DIR)
	$(CC) $(CPPFLAGS) $(TEST_CFLAGS) $(TEST_DIR)/test_lexer.c src/lexer.c -o $@

$(TEST_BUILD_DIR)/test_parser: $(TEST_DIR)/test_parser.c $(TEST_DIR)/test_common.h src/parser.c src/stack.c | $(TEST_BUILD_DIR)
	$(CC) $(CPPFLAGS) $(TEST_CFLAGS) $(TEST_DIR)/test_parser.c src/parser.c src/stack.c $(LDLIBS) -o $@

$(TEST_BUILD_DIR)/test_evaluator: $(TEST_DIR)/test_evaluator.c $(TEST_DIR)/test_common.h src/evaluator.c src/stack.c | $(TEST_BUILD_DIR)
	$(CC) $(CPPFLAGS) $(TEST_CFLAGS) $(TEST_DIR)/test_evaluator.c src/evaluator.c src/stack.c $(LDLIBS) -o $@

$(TEST_BUILD_DIR)/test_integration: $(TEST_DIR)/test_integration.c $(TEST_DIR)/test_common.h src/lexer.c src/parser.c src/evaluator.c src/stack.c | $(TEST_BUILD_DIR)
	$(CC) $(CPPFLAGS) $(TEST_CFLAGS) $(TEST_DIR)/test_integration.c src/lexer.c src/parser.c src/evaluator.c src/stack.c $(LDLIBS) -o $@

test: $(TESTS)
	@echo "\nRunning all tests...\n"
	@for test in $(TESTS); do ./$$test || exit $$?; done
	@echo "All test suites passed."

test-lexer: $(TEST_BUILD_DIR)/test_lexer
	./$<

test-parser: $(TEST_BUILD_DIR)/test_parser
	./$<

test-evaluator: $(TEST_BUILD_DIR)/test_evaluator
	./$<

test-integration: $(TEST_BUILD_DIR)/test_integration
	./$<

-include $(DEPS)

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean all
