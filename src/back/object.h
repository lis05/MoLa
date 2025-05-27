#ifndef __mola_object_h_
#define __mola_object_h_

#include "../util.h"
#include "types.h"

// Null, Bool, Char, Int, Float, Module(environment_ptr), ReturnAddress are stored in the union
typedef struct Object {
    enum Type type;

    union {
        int     bool_value;
        char    char_value;
        int64_t int_value;
        double  float_value;
        int64_t return_address;
        void   *value;
    };

    uint32_t ref_count;

    uint is_rvalue       : 1;
    uint gc_mark         : 1;
    uint is_gc_protected : 1;
} Object;

#define raw64(x)          (*((uint64_t *)&(x)))
#define cooked64(x, type) *((type *)&(x))

Object *objectCreate(enum Type type, uint64_t value);    // for basic types the value has to be passed in value
void    objectDestroy(Object *object);                   // used by gc
void    objectGCOnlyUnref(Object *object);               
void    objectGCDestroy(Object *object);
void    ref(Object *unit);
void    unref(Object *unit);

#endif
