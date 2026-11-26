#include <stdio.h>
#include <stdlib.h>

// Defines a callback type: a function taking no arguments and returning void.
typedef void (*Callback)(void);

// Example callback functions.
void Start(void) {
    printf("Starting application...\n");
}

void Pause(void) {
    printf("Pausing application...\n");
}

void Stop(void) {
    printf("Stopping application...\n");
}

// Dynamically allocates an array of callback pointers.
int CreateCallbacks(Callback **callbacks, size_t count) {
    // Allocate an array containing count function pointers.
    Callback *memory = calloc(count, sizeof *memory);

    // Return failure if allocation was unsuccessful.
    if (memory == NULL) {
        return 0;
    }

    // Store the allocated array in the caller's pointer.
    *callbacks = memory;

    return 1;
}

// Replaces the callback array with a larger allocation.
int ResizeCallbacks(Callback **callbacks, size_t newCount) {
    // Store realloc's result separately to preserve the original on failure.
    Callback *resized = realloc(
        *callbacks,
        newCount * sizeof **callbacks
    );

    if (resized == NULL) {
        return 0;
    }

    // Update the caller's pointer.
    *callbacks = resized;

    return 1;
}

int main(void) {
    size_t count = 2;

    // Initially, there is no callback array.
    Callback *callbacks = NULL;

    // Allocate space for two callback pointers.
    if (!CreateCallbacks(&callbacks, count)) {
        fprintf(stderr, "Callback allocation failed.\n");
        return 1;
    }

    // Register two callbacks.
    callbacks[0] = Start;
    callbacks[1] = Pause;

    printf("Initial Callbacks:\n");

    // Execute each registered callback.
    for (size_t i = 0; i < count; i++) {
        callbacks[i]();
    }

    // Increase the callback array capacity.
    size_t newCount = 3;

    if (!ResizeCallbacks(&callbacks, newCount)) {
        fprintf(stderr, "Callback resizing failed.\n");
        free(callbacks);
        return 1;
    }

    count = newCount;

    // Register another callback in the newly allocated slot.
    callbacks[2] = Stop;

    printf("\nAfter Adding Another Callback:\n");

    // Execute all registered callbacks.
    for (size_t i = 0; i < count; i++) {
        callbacks[i]();
    }

    // Release the dynamically allocated callback array.
    free(callbacks);
    callbacks = NULL;

    return 0;
}
