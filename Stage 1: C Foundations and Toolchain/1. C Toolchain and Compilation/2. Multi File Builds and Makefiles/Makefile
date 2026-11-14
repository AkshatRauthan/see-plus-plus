CC := clang

TARGET := calculator
BUILD_DIR := build

SOURCES := src/main.c src/calculator.c
OBJECTS := $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
DEPFILES := $(OBJECTS:.o=.d)

CPPFLAGS := -Iinclude
CFLAGS := -Wall -Wextra -Wpedantic -g -fsanitize=address,undefined

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: src/%.c | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

-include $(DEPFILES)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)
