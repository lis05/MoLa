#ifndef __mola_object_h_
#define __mola_object_h_

#include "../util.h"
#include "types.h"

// if type is RETURN_ADDRESS_TYPE, the object is just a meaningless shell containing the return address in value
typedef struct Object {
    enum Type type;
    void     *value;

    uint32_t ref_count;
    uint     is_rvalue : 1;
    uint     gc_mark   : 1;
} Object;

Object *objectCreate(enum Type type, void *value);
void    objectDestroy(Object *object);    // used by gc
void    ref(Object *unit);
void    unref(Object *unit);

#endif
