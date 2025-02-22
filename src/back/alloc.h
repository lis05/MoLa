#ifndef __mola_alloc_h__
#define __mola_alloc_h__

#include "../util.h"

void *memalloc(size_t bytes);
void  memfree(void *ptr);

#endif
