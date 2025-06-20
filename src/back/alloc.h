#ifndef __mola_alloc_h__
#define __mola_alloc_h__

#include "../util.h"

#define ALLOCATION_LIMIT   100000000    // 100mb
#define GC_CYCLE_THRESHOLD 100000       // 1e6

void allocInit();

// allocates the number of bytes, returns NULL if fails
// DOES NOT SIGNAL AN ERROR
void *allocOrNULL(size_t bytes);

// allocates the number of bytes, signals and error if fails
void *allocOrError(size_t bytes);

// allocated the number of bytes, signals an InternalError if fails
// is not counted in the total number of bytes allocated by instructions
// so use this one for internal purposes
void *allocBytesOrExit(size_t bytes);

void freeBytes(void *ptr);

size_t getAllocatedBytes();

size_t getRecycleAmount();

size_t getGCCycleThreshold();

// ----

#endif
