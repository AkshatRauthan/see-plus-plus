
CC := clang
SOURCE := hello.c
BUILD_DIR := build
TARGET := $(BUILD_DIR)/hello

.PHONY: all preprocess compile assemble link clean

all: link

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

preprocess: $(BUILD_DIR)/hello.i

$(BUILD_DIR)/hello.i: $(SOURCE) | $(BUILD_DIR)
	$(CC) -E $< -o $@

compile: $(BUILD_DIR)/hello.s

$(BUILD_DIR)/hello.s: $(BUILD_DIR)/hello.i
	$(CC) -S $< -o $@

assemble: $(BUILD_DIR)/hello.o

$(BUILD_DIR)/hello.o: $(BUILD_DIR)/hello.s
	$(CC) -c $< -o $@

link: $(TARGET)

$(TARGET): $(BUILD_DIR)/hello.o
	$(CC) $< -o $@

clean:
	rm -rf $(BUILD_DIR)
