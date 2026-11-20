#include "../include/file_operations.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>

#define LARGE_FILE_SIZE 100000

/*
 * Generates deterministic binary data.
 *
 * This provides a mixture of printable and non-printable bytes
 * for testing binary reading, writing, and copying.
 */
static void generate_test_data(
    unsigned char *buffer,
    size_t size
) {
    for (size_t i = 0; i < size; i++) {
        buffer[i] = (unsigned char)((i * 37 + 13) % 256);
    }
}

/*
 * Compares two files byte by byte.
 *
 * Returns:
 *    1 if both files contain identical data.
 *    0 otherwise.
 */
static int files_are_equal(
    const char *first_path,
    const char *second_path
) {
    FILE *first = fopen(first_path, "rb");

    if (first == NULL) {
        return 0;
    }

    FILE *second = fopen(second_path, "rb");

    if (second == NULL) {
        fclose(first);
        return 0;
    }

    unsigned char first_buffer[4096];
    unsigned char second_buffer[4096];

    int equal = 1;

    while (1) {
        size_t first_count = fread(
            first_buffer, 1, sizeof(first_buffer), first
        );

        size_t second_count = fread(
            second_buffer, 1, sizeof(second_buffer), second
        );

        if (first_count != second_count ||
            memcmp(first_buffer, second_buffer, first_count) != 0) {
            equal = 0;
            break;
        }

        if (ferror(first) || ferror(second)) {
            equal = 0;
            break;
        }

        if (first_count == 0) {
            break;
        }
    }

    if (fclose(first) != 0) {
        equal = 0;
    }

    if (fclose(second) != 0) {
        equal = 0;
    }

    return equal;
}

/*
 * Tests basic file opening and closing.
 */
static void test_file_open_and_close(void) {
    FILE *file = file_open("build/test.txt", "w");

    assert(file != NULL);
    assert(file_close(file) == 0);
    assert(file_close(NULL) == -1);
}

/*
 * Tests text file reading, writing, and appending.
 */
static void test_text_operations(void) {
    const char *path = "build/test.txt";

    assert(write_text_file(path, "Hello, C!\n") == 0);

    char buffer[128];
    size_t bytes_read = 0;

    assert(read_text_file(
        path,
        buffer,
        sizeof(buffer),
        &bytes_read
    ) == 0);

    assert(strcmp(buffer, "Hello, C!\n") == 0);
    assert(bytes_read == strlen("Hello, C!\n"));

    assert(append_text_file(path, "File operations.\n") == 0);

    assert(read_text_file(
        path,
        buffer,
        sizeof(buffer),
        &bytes_read
    ) == 0);

    assert(strcmp(
        buffer,
        "Hello, C!\nFile operations.\n"
    ) == 0);

    long file_size = 0;

    assert(get_file_size(path, &file_size) == 0);
    assert(file_size == (long)strlen(buffer));

    // A buffer that cannot hold the complete file must be rejected.
    char small_buffer[4];
    size_t small_bytes = 0;

    assert(read_text_file(
        path,
        small_buffer,
        sizeof(small_buffer),
        &small_bytes
    ) == -1);

    assert(small_bytes == 0);
}

/*
 * Tests binary file reading and writing.
 */
static void test_binary_operations(void) {
    const char *path = "build/test.bin";

    const unsigned char data[] = {
        0x00, 0x01, 0x02, 0x7F,
        0x80, 0xFE, 0xFF
    };

    const size_t data_size = sizeof(data);

    assert(write_binary_file(path, data, data_size) == 0);

    unsigned char buffer[32];
    size_t bytes_read = 0;

    assert(read_binary_file(
        path,
        buffer,
        sizeof(buffer),
        &bytes_read
    ) == 0);

    assert(bytes_read == data_size);
    assert(memcmp(buffer, data, data_size) == 0);

    // A buffer that is too small must be rejected.
    unsigned char small_buffer[4];
    size_t small_bytes = 0;

    assert(read_binary_file(
        path,
        small_buffer,
        sizeof(small_buffer),
        &small_bytes
    ) == -1);

    assert(small_bytes == 0);
}

/*
 * Tests copying a binary file.
 */
static void test_file_copying(void) {
    const char *source = "build/test.bin";
    const char *destination = "build/test_copy.bin";

    assert(copy_file(source, destination) == 0);

    assert(files_are_equal(source, destination));

    // Copying a file onto itself must fail.
    assert(copy_file(source, source) == -1);

    // A nonexistent source must fail.
    assert(copy_file(
        "build/nonexistent.bin",
        "build/invalid_copy.bin"
    ) == -1);

    // Invalid arguments must fail.
    assert(copy_file(NULL, destination) == -1);
    assert(copy_file(source, NULL) == -1);
}

/*
 * Tests copying an empty file.
 */
static void test_empty_file_copying(void) {
    const char *source = "build/empty.bin";
    const char *destination = "build/empty_copy.bin";

    FILE *file = fopen(source, "wb");

    assert(file != NULL);
    assert(fclose(file) == 0);

    assert(copy_file(source, destination) == 0);
    assert(files_are_equal(source, destination));

    long size = -1;

    assert(get_file_size(destination, &size) == 0);
    assert(size == 0);
}

/*
 * Tests copying a large file.
 *
 * The file is larger than the internal 4096-byte copy buffer.
 * This verifies that copying continues across multiple iterations.
 */
static void test_large_file_copying(void) {
    const char *source = "build/large.bin";
    const char *destination = "build/large_copy.bin";

    unsigned char buffer[LARGE_FILE_SIZE];

    generate_test_data(buffer, sizeof(buffer));

    assert(write_binary_file(
        source,
        buffer,
        sizeof(buffer)
    ) == 0);

    assert(copy_file(source, destination) == 0);

    assert(files_are_equal(source, destination));

    long size = 0;

    assert(get_file_size(destination, &size) == 0);
    assert(size == LARGE_FILE_SIZE);
}

/*
 * Counts the number of newline characters in a string.
 */
static size_t count_lines(const char *text) {
    size_t lines = 0;

    for (size_t i = 0; text[i] != '\0'; i++) {
        if (text[i] == '\n') {
            lines++;
        }
    }

    return lines;
}

/*
 * Tests hexadecimal and ASCII output.
 */
static void test_hexdump(void) {
    const char *path = "build/hexdump.bin";

    const unsigned char data[] = {
        0x48, 0x65, 0x6C, 0x6C,
        0x6F, 0x00, 0xFF
    };

    assert(write_binary_file(path, data, sizeof(data)) == 0);

    FILE *output = tmpfile();

    assert(output != NULL);

    assert(hexdump_file(path, output) == 0);

    assert(fseek(output, 0, SEEK_SET) == 0);

    char result[256];

    size_t count = fread(result, 1, sizeof(result) - 1, output);
    result[count] = '\0';

    // Verify the hexadecimal bytes and ASCII representation.
    assert(strstr(
        result,
        "00000000  48 65 6c 6c 6f 00 ff"
    ) != NULL);

    assert(strstr(result, "|Hello..|") != NULL);
    assert(count_lines(result) == 1);

    assert(fclose(output) == 0);

    // An empty file should produce no output.
    FILE *empty_output = tmpfile();

    assert(empty_output != NULL);

    assert(hexdump_file("build/empty.bin", empty_output) == 0);

    assert(fflush(empty_output) == 0);
    assert(fseek(empty_output, 0, SEEK_END) == 0);
    assert(ftell(empty_output) == 0);

    assert(fclose(empty_output) == 0);

    // Invalid arguments must fail.
    assert(hexdump_file(NULL, stdout) == -1);
    assert(hexdump_file(path, NULL) == -1);
    assert(hexdump_file("build/nonexistent.bin", stdout) == -1);
}

/*
 * Tests hexdump row boundaries.
 *
 * A 17-byte file must produce:
 * - One complete 16-byte row.
 * - One final row containing a single byte.
 */
static void test_hexdump_row_boundaries(void) {
    const char *path = "build/hexdump_rows.bin";

    unsigned char data[17];

    generate_test_data(data, sizeof(data));

    assert(write_binary_file(path, data, sizeof(data)) == 0);

    FILE *output = tmpfile();

    assert(output != NULL);

    assert(hexdump_file(path, output) == 0);

    assert(fseek(output, 0, SEEK_SET) == 0);

    char result[512];

    size_t count = fread(result, 1, sizeof(result) - 1, output);
    result[count] = '\0';

    assert(count_lines(result) == 2);

    // Verify the offset of the second row.
    assert(strstr(result, "00000010") != NULL);

    assert(fclose(output) == 0);
}

/*
 * Tests invalid arguments across the public API.
 */
static void test_invalid_arguments(void) {
    char buffer[16];
    size_t bytes_read = 0;
    long size = 0;

    assert(file_open(NULL, "r") == NULL);
    assert(file_open("build/test.txt", NULL) == NULL);

    assert(read_text_file(
        NULL, buffer, sizeof(buffer), &bytes_read
    ) == -1);

    assert(read_text_file(
        "build/test.txt", NULL, sizeof(buffer), &bytes_read
    ) == -1);

    assert(read_text_file(
        "build/test.txt", buffer, 0, &bytes_read
    ) == -1);

    assert(write_text_file(NULL, "text") == -1);
    assert(write_text_file("build/test.txt", NULL) == -1);

    assert(append_text_file(NULL, "text") == -1);
    assert(append_text_file("build/test.txt", NULL) == -1);

    assert(read_binary_file(
        NULL, buffer, sizeof(buffer), &bytes_read
    ) == -1);

    assert(read_binary_file(
        "build/test.bin", NULL, sizeof(buffer), &bytes_read
    ) == -1);

    assert(read_binary_file(
        "build/test.bin", buffer, 0, &bytes_read
    ) == -1);

    assert(write_binary_file(NULL, buffer, sizeof(buffer)) == -1);
    assert(write_binary_file("build/test.bin", NULL, 1) == -1);

    assert(get_file_size(NULL, &size) == -1);
    assert(get_file_size("build/nonexistent.bin", &size) == -1);
}

int main(void) {
    test_file_open_and_close();
    test_text_operations();
    test_binary_operations();

    test_file_copying();
    test_empty_file_copying();
    test_large_file_copying();

    test_hexdump();
    test_hexdump_row_boundaries();

    test_invalid_arguments();

    // Remove generated test files.
    assert(remove("build/test.txt") == 0);
    assert(remove("build/test.bin") == 0);
    assert(remove("build/test_copy.bin") == 0);
    assert(remove("build/empty.bin") == 0);
    assert(remove("build/empty_copy.bin") == 0);
    assert(remove("build/large.bin") == 0);
    assert(remove("build/large_copy.bin") == 0);
    assert(remove("build/hexdump.bin") == 0);
    assert(remove("build/hexdump_rows.bin") == 0);

    printf("All file operation tests passed.\n");

    return 0;
}
