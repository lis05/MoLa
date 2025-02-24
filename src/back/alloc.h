#ifndef __mola_alloc_h__
#define __mola_alloc_h__

#include "../util.h"

// if error happens, jumps to handler
void *memalloc(size_t bytes);
// if error happens, jumps to handler
void  memfree(void *ptr);

// if error happens, outputs 1 to error. 0 otherwise
void *memallocsafe(size_t bytes, int *error);
// if error happens, outputs 1 to error. 0 otherwise
void  memfreesafe(void *ptr, int *error);

#endif
