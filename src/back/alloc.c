#include "alloc.h"
#include "object.h"
#include "xmempool.h"

static xmem_pool_handle objects_mempool;

void allocInit() {
    objects_mempool = xmem_create_pool(sizeof(Object));
}

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

void *memallocObject() {
    return xmem_alloc(objects_mempool);
}

void memfreeObject(struct Object *ptr) {
    xmem_free(objects_mempool, ptr);
}
