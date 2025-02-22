#ifndef __mola_object_h_
#define __mola_object_h_

#include "../util.h"
#include "types.h"

typedef struct Object {
    enum Type type;
    void     *value;    // not null

    uint32_t ref_count : 31;
    int      gc_mark   : 1;
} Object;

Object *objectCreate(enum Type type, void *value);
void    objectDestroy(Object *object);
void    ref(Object *unit);
void    unref(Object *unit);

#endif
