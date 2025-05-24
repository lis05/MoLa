#include "object.h"
#include "alloc.h"
#include "gc.h"
#include "stat.h"
#include "types.h"

Object *objectCreate(enum Type type, uint64_t value) {
    stat_created_objects++;
    Object *obj = allocBytesOrError(sizeof(Object));

    obj->type  = type;
    obj->value = (void *)value;

    switch (type) {
    case NULL_TYPE : {
        stat_created_nulls++;
        break;
    }
    case BOOL_TYPE :
        obj->bool_value = cooked64(value, int);
        stat_created_bools++;
        break;
    case INT_TYPE :
        obj->int_value = cooked64(value, int64_t);
        stat_created_ints++;
        break;
    case CHAR_TYPE :
        obj->char_value = cooked64(value, char);
        stat_created_chars++;
        break;
    case FLOAT_TYPE :
        obj->float_value = cooked64(value, double);
        stat_created_floats++;
        break;
    case STRING_TYPE : stringValueRef((void *)value); break;
    case ARRAY_TYPE : arrayValueRef((void *)value); break;
    case TYPE_TYPE : typeValueRef((void *)value); break;
    case INSTANCE_TYPE : instanceValueRef((void *)value); break;
    case MOLA_FUNCTION_TYPE : molaFunctionValueRef((void *)value); break;
    case C_FUNCTION_TYPE : cFunctionValueRef((void *)value); break;
    case MODULE_TYPE : obj->value = (void *)value; break;
    case RETURN_ADDRESS_TYPE : obj->return_address = cooked64(value, int64_t); break;    // no need
    }

    obj->ref_count = 0;
    obj->gc_mark   = 0;
    obj->is_rvalue = 0;

    gcTrackObject(obj);

    return obj;
}

void objectDestroy(Object *obj) {
    stat_created_objects--;
    switch (obj->type) {
    case NULL_TYPE : stat_created_nulls--; break;
    case BOOL_TYPE : stat_created_bools--; break;
    case INT_TYPE : stat_created_ints--; break;
    case CHAR_TYPE : stat_created_chars--; break;
    case FLOAT_TYPE : stat_created_floats--; break;
    case STRING_TYPE : stringValueUnref(obj->value); break;
    case ARRAY_TYPE : arrayValueUnref(obj->value); break;
    case TYPE_TYPE : typeValueUnref(obj->value); break;
    case INSTANCE_TYPE : instanceValueUnref(obj->value); break;
    case MOLA_FUNCTION_TYPE : molaFunctionValueUnref(obj->value); break;
    case C_FUNCTION_TYPE : cFunctionValueUnref(obj->value); break;
    case MODULE_TYPE : break;
    case RETURN_ADDRESS_TYPE : break;    // no need
    }

    freeBytes(obj);
}

void ref(Object *unit) {
    unit->ref_count++;
}

void unref(Object *unit) {
    if (--unit->ref_count == 0) {
        gcDeclareGarbageObject(unit);
    }
}
