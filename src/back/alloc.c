#include "alloc.h"
#include "error.h"
#include "gc.h"
#include "object.h"
#include "scope.h"
#include "xmempool.h"

static size_t bytes_allocated = 0;

void allocInit() {}

void *allocBytesOrNULL(size_t bytes) {
    static uint16_t cnt = 0;
    cnt++;
    if (cnt == 0) {
        //molalog("Allocated %zumb (%d%%)\n", bytes_allocated / 1000000, (int)(bytes_allocated * 100 / ALLOCATION_LIMIT));
    }

    bytes += sizeof(size_t);
    if (bytes_allocated + bytes > ALLOCATION_LIMIT) {
        return NULL;
    }
    void *res        = malloc(bytes);
    *((size_t *)res) = bytes;
    if (res != NULL) {
        bytes_allocated += bytes;
    }
    return (uint8_t *)res + sizeof(size_t);
}

void *allocBytesOrError(size_t bytes) {
    void *res = allocBytesOrNULL(bytes);

    if (res == NULL) {
        signalError(OUT_OF_MEMORY_ERROR_CODE, "Failed to allocate bytes");
    }

    return res;
}

void *allocBytesOrExit(size_t bytes) {
    void *res = allocBytesOrNULL(bytes);

    if (res == NULL) {
        signalError(INTERNAL_ERROR_CODE, "Failed to allocate internal bytes");
    }

    return res;
}

void freeBytes(void *ptr) {
    size_t n = *((char *)ptr - sizeof(size_t));

    bytes_allocated -= n;
    free((char *)ptr - sizeof(size_t));
}

size_t getAllocatedBytes() {
    return bytes_allocated;
}

size_t getRecycleAmount() {
    double x  = bytes_allocated / ALLOCATION_LIMIT;
    x        *= x;
    x        *= x;
    return (x + 0.001) * bytes_allocated;
}
