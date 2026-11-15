
CC := clang

TARGET := debug-exercise
BUILD_DIR := build
SOURCE := src/main.c
EXECUTABLE := $(BUILD_DIR)/$(TARGET)

CFLAGS := -Wall -Wextra -Wpedantic -g -O0

.PHONY: all run debug clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCE) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: all
	./$(EXECUTABLE)

debug: all
	lldb ./$(EXECUTABLE)

clean:
	rm -rf $(BUILD_DIR)
