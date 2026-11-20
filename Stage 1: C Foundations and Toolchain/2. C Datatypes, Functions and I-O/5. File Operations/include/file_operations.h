#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <stddef.h>
#include <stdio.h>

/*
 * Opens a file using the requested mode.
 *
 * Returns:
 *   FILE pointer on success.
 *   NULL on failure.
 */
FILE *file_open(const char *path, const char *mode);

/*
 * Closes an open file.
 *
 * Returns:
 *    0 on success.
 *   -1 on failure.
 */
int file_close(FILE *file);

/*
 * Reads an entire text file into a character buffer.
 *
 * The buffer is always null-terminated on success.
 * bytes_read receives the number of characters read,
 * excluding the terminating null character.
 *
 * Returns:
 *    0 on success.
 *   -1 on failure or insufficient buffer capacity.
 */
int read_text_file(const char *path, char *buffer, size_t capacity,
				   size_t *bytes_read);

/*
 * Creates or overwrites a text file.
 *
 * Returns:
 *    0 on success.
 *   -1 on failure.
 */
int write_text_file(const char *path, const char *text);

/*
 * Appends text to an existing file or creates it if necessary.
 *
 * Returns:
 *    0 on success.
 *   -1 on failure.
 */
int append_text_file(const char *path, const char *text);

/*
 * Reads binary data into a buffer.
 *
 * bytes_read receives the number of bytes read.
 * Fails if the file contains more bytes than the buffer can hold.
 *
 * Returns:
 *    0 on success.
 *   -1 on failure or insufficient buffer capacity.
 */
int read_binary_file(const char *path, void *buffer, size_t capacity,
					 size_t *bytes_read);

/*
 * Writes binary data to a file, replacing its contents.
 *
 * Returns:
 *    0 on success.
 *   -1 on failure.
 */
int write_binary_file(const char *path, const void *data, size_t size);

/*
 * Copies a file byte by byte.
 *
 * The source and destination must refer to different files.
 *
 * Returns:
 *    0 on success.
 *   -1 on failure.
 */
int copy_file(const char *source, const char *destination);

/*
 * Retrieves the size of a file in bytes.
 *
 * The result is stored in size.
 *
 * Returns:
 *    0 on success.
 *   -1 on failure.
 */
int get_file_size(const char *path, long *size);

#endif
