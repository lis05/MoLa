#include "alloc.h"

// TEMPORARY SOLUTION

void *memalloc(size_t bytes) {
    return malloc(bytes);
}

void memfree(void *ptr) {
    free(ptr);
}

void *memallocsafe(size_t bytes, int *error) {
    *error = 0;
    return malloc(bytes);
}

void memfreesafe(void *ptr, int *error) {
    *error = 0;
    free(ptr);
}
