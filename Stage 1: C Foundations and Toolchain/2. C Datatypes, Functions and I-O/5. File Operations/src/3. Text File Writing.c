#include "../include/file_operations.h"

#include <errno.h>
#include <stdio.h>

/*
 * Creates a new text file or replaces the contents of an existing one.
 *
 * The "w" mode truncates an existing file to zero length.
 */
int write_text_file(const char *path, const char *text) {
    if (path == NULL || text == NULL) {
        errno = EINVAL;
        return -1;
    }

    FILE *file = fopen(path, "w");

    if (file == NULL) {
        return -1;
    }

    /*
     * fputs() writes a null-terminated string.
     * It does not write the terminating '\0' to the file.
     */
    if (fputs(text, file) == EOF) {
        fclose(file);
        return -1;
    }

    /*
     * fclose() flushes buffered output.
     * Checking its return value helps detect delayed write errors.
     */
    if (fclose(file) != 0) {
        return -1;
    }

    return 0;
}

/*
 * Appends text to a file.
 *
 * If the file does not exist, "a" mode creates it.
 * Existing contents are preserved.
 */
int append_text_file(const char *path, const char *text) {
    if (path == NULL || text == NULL) {
        errno = EINVAL;
        return -1;
    }

    FILE *file = fopen(path, "a");

    if (file == NULL) {
        return -1;
    }

    if (fputs(text, file) == EOF) {
        fclose(file);
        return -1;
    }

    if (fclose(file) != 0) {
        return -1;
    }

    return 0;
}
