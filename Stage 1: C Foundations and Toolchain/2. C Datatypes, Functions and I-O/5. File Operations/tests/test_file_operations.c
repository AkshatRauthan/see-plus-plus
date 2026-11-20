#include "../include/file_operations.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

int main(void) {
	const char *text_path = "build/test.txt";
	const char *binary_path = "build/test.bin";
	const char *copy_path = "build/test_copy.bin";

	// Test opening and closing a file.
	FILE *file = file_open(text_path, "w");
	assert(file != NULL);
	assert(file_close(file) == 0);

	// Test writing text.
	assert(write_text_file(text_path, "Hello, C!\n") == 0);

	// Test reading text.
	char text_buffer[128];
	size_t text_bytes = 0;

	assert(read_text_file(text_path, text_buffer, sizeof(text_buffer),
						  &text_bytes) == 0);

	assert(strcmp(text_buffer, "Hello, C!\n") == 0);
	assert(text_bytes == strlen("Hello, C!\n"));

	// Test appending text.
	assert(append_text_file(text_path, "File operations.\n") == 0);

	assert(read_text_file(text_path, text_buffer, sizeof(text_buffer),
						  &text_bytes) == 0);

	assert(strcmp(text_buffer, "Hello, C!\nFile operations.\n") == 0);

	// Test retrieving file size.
	long file_size = 0;

	assert(get_file_size(text_path, &file_size) == 0);
	assert(file_size == (long)strlen(text_buffer));

	// Binary data can contain zero bytes and non-text values.
	const unsigned char binary_data[] = {0x00, 0x01, 0x02, 0x7F,
										 0x80, 0xFE, 0xFF};

	const size_t binary_size = sizeof(binary_data);

	// Test writing binary data.
	assert(write_binary_file(binary_path, binary_data, binary_size) == 0);

	// Test reading binary data.
	unsigned char binary_buffer[32];
	size_t binary_bytes = 0;

	assert(read_binary_file(binary_path, binary_buffer, sizeof(binary_buffer),
							&binary_bytes) == 0);

	assert(binary_bytes == binary_size);
	assert(memcmp(binary_buffer, binary_data, binary_size) == 0);

	// Test copying a binary file.
	assert(copy_file(binary_path, copy_path) == 0);

	unsigned char copied_data[32];
	size_t copied_bytes = 0;

	assert(read_binary_file(copy_path, copied_data, sizeof(copied_data),
							&copied_bytes) == 0);

	assert(copied_bytes == binary_size);
	assert(memcmp(copied_data, binary_data, binary_size) == 0);

	// Test that a buffer that is too small is rejected.
	char small_buffer[4];
	size_t small_bytes = 0;

	assert(read_text_file(text_path, small_buffer, sizeof(small_buffer),
						  &small_bytes) == -1);

	// Remove test files.
	assert(remove(text_path) == 0);
	assert(remove(binary_path) == 0);
	assert(remove(copy_path) == 0);

	printf("All file operation tests passed.\n");

	return 0;
}
