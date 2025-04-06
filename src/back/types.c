#include "types.h"
#include "../util.h"
#include "alloc.h"
#include "error.h"
#include "gc.h"

StringValue *stringValueCreate(size_t length, char *string) {
    StringValue *res = memalloc(sizeof(StringValue));
    res->length      = length;
    res->string      = memalloc(sizeof(char) * length + 1);
    strcpy(res->string, string);

    res->gc_mark   = 0;
    res->ref_count = 0;
}

StringValue *stringValueCopy(StringValue *val) {
    return stringValueCreate(val->length, val->string);
}

void stringValueDestroy(StringValue *val) {
    memfree(val->string);
    memfree(val);
}

char stringValueIndexAccess(StringValue *val, int64_t index) {
    if (!(0 <= index && index < val->length)) {
        gcUnlock();    // what if I was called without a gc lock?
        signalError(OUT_OF_BOUNDS_ERROR_CODE, "Index out of bounds");
    }
    return val->string[index];
}

struct Object *stringValueLookupField(StringValue *val, ident name) {}

struct Object *stringValueLookupMethod(StringValue *val, ident name) {}

int stringCompare(StringValue *first, StringValue *second) {
    size_t m = (first->length < second->length) ? first->length : second->length;
    for (size_t i = 0; i < m; i++) {
        if (first->string[i] < second->string[i]) {
            return -1;
        }
        else if (first->string[i] > second->string[i]) {
            return 1;
        }
    }
    if (first->length < second->length) {
        return -1;
    }
    else if (first->length > second->length) {
        return 1;
    }
    return 0;
}

StringValue *stringConcat(StringValue *first, StringValue *second) {
    char *str = memalloc(first->length + second->length + 1);
    memcpy(str, first->string, first->length);
    memcpy(str + first->length, second->string, second->length);
    str[first->length + second->length] = '\0';

    StringValue *res = stringValueCreate(first->length + second->length, str);
    memfree(str);
    return res;
}

void stringValueRef(StringValue *unit) {
    unit->ref_count++;
}

void stringValueUnref(StringValue *unit) {
    unit->ref_count--;
}

ArrayValue *arrayValueCreate(char *string) {}

ArrayValue *arrayValueCopy(ArrayValue *val) {}

void arrayValueDestroy(ArrayValue *val) {}

struct Object *arrayValueIndexAccess(ArrayValue *val, int64_t index) {}

struct Object *arrayValueLookupField(ArrayValue *val, ident name) {}

struct Object *arrayValueLookupMethod(ArrayValue *val, ident name) {}

void arrayValueRef(ArrayValue *unit) {}

void arrayValueUnref(ArrayValue *unit) {}

TypeValue *typeValueCreate() {}

TypeValue *typeValueCopy(TypeValue *val) {}

void typeValueDestroy(TypeValue *val) {}

void typeValueAddMethod(TypeValue *val, ident name, struct MolaFunctionValue *method) {}

struct Object *typeValueLookupMethod(TypeValue *val, ident name) {}

void typeValueRef(TypeValue *unit) {}

void typeValueUnref(TypeValue *unit) {}

InstanceValue *instanceValueCreate(struct TypeValue *type) {}

InstanceValue *instanceValueCopy(InstanceValue *val) {}

void instanceValueDestroy(InstanceValue *val) {}

struct Object *instanceValueLookupField(InstanceValue *val, ident name) {}

struct Object *instanceValueLookupMethod(InstanceValue *val, ident name) {}

void instanceValueRef(InstanceValue *unit) {}

void instanceValueUnref(InstanceValue *unit) {}

MolaFunctionValue *molaFunctionValueCreate(struct Env *env, int64_t rel_offset, size_t n_args, ident *args) {
    MolaFunctionValue *res = memalloc(sizeof(MolaFunctionValue));
    res->env               = env;
    res->relative_offset   = rel_offset;
    res->n_args            = n_args;
    res->args              = args;

    res->ref_count = 0;
    res->gc_mark   = 0;
    res->is_method = 0;
}

MolaFunctionValue *molaFunctionValueCopy(MolaFunctionValue *val) {
    return val;    // copy by ref
}

void molaFunctionValueDestroy(MolaFunctionValue *val) {
    memfree(val->args);
    memfree(val);
}

void molaFunctionValueRef(MolaFunctionValue *unit) {
    unit->ref_count++;
}

void molaFunctionValueUnref(MolaFunctionValue *unit) {
    unit->ref_count--;
}

CFunctionValue *cFunctionValueCreate(struct Env *env, size_t n_args, CFunction function) {
    CFunctionValue *res = memalloc(sizeof(CFunctionValue));
    res->env            = env;
    res->n_args         = n_args;
    res->function       = function;

    res->ref_count = 0;
    res->gc_mark   = 0;
    res->is_method = 0;
}

CFunctionValue *cFunctionValueCopy(CFunctionValue *val) {
    return val;
}

void cFunctionValueDestroy(CFunctionValue *val) {
    memfree(val);
}

void cFunctionValueRef(CFunctionValue *unit) {
    unit->ref_count++;
}

void cFunctionValueUnref(CFunctionValue *unit) {
    unit->ref_count--;
}
