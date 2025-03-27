#include "types.h"
#include "alloc.h"
#include "gc.h"

NullValue *nullValueCreate() {
    NullValue *res = memalloc(sizeof(NullValue));
    res->gc_mark   = 0;
    res->ref_count = 0;

    gcTrackNullValue(res);
    return res;
}

NullValue *nullValueCopyByAuto(NullValue *val) {
    return nullValueCreate();
}

void nullValueDestroy(NullValue *val) {
    memfree(val);
}

void nullValueRef(NullValue *unit) {
    unit->ref_count++;
}

void nullValueUnref(NullValue *unit) {
    unit->ref_count--;
}

BoolValue *boolValueCreate(int value) {
    BoolValue *res = memalloc(sizeof(BoolValue));
    res->value     = value;
    res->gc_mark   = 0;
    res->ref_count = 0;

    gcTrackBoolValue(res);
    return res;
}

BoolValue *boolValueCopyByAuto(BoolValue *val) {
    assert(val != NULL);
    return boolValueCreate(val->value);
}

void boolValueDestroy(BoolValue *val) {
    memfree(val);
}

void boolValueRef(BoolValue *unit) {
    unit->ref_count++;
}

void boolValueUnref(BoolValue *unit) {
    unit->ref_count--;
}

IntValue *intValueCreate(int64_t value) {
    IntValue *res  = memalloc(sizeof(IntValue));
    res->value     = value;
    res->gc_mark   = 0;
    res->ref_count = 0;

    gcTrackIntValue(res);
    return res;
}

IntValue *intValueCopyByAuto(IntValue *val) {
    assert(val != NULL);
    return intValueCreate(val->value);
}

void intValueDestroy(IntValue *val) {
    memfree(val);
}

void intValueRef(IntValue *unit) {
    unit->ref_count++;
}

void intValueUnref(IntValue *unit) {
    unit->ref_count--;
}

CharValue *charValueCreate(char value) {}

CharValue *charValueCopyByAuto(CharValue *val) {}

void charValueDestroy(CharValue *val) {}

void charValueRef(CharValue *unit) {}

void charValueUnref(CharValue *unit) {}

FloatValue *floatValueCreate(double value) {}

FloatValue *floatValueCopyByAuto(FloatValue *val) {}

void floatValueDestroy(FloatValue *val) {}

void floatValueRef(FloatValue *unit) {}

void floatValueUnref(FloatValue *unit) {}

StringValue *stringValueCreate(size_t length, char *string) {}

StringValue *stringValueCopyByAuto(StringValue *val) {}

void stringValueDestroy(StringValue *val) {}

char stringValueIndexAccess(StringValue *val, int64_t index) {}

struct Object *stringValueLookupField(StringValue *val, ident name) {}

struct Object *stringValueLookupMethod(StringValue *val, ident name) {}

void stringValueRef(StringValue *unit) {}

void stringValueUnref(StringValue *unit) {}

ArrayValue *arrayValueCreate(char *string) {}

ArrayValue *arrayValueCopyByAuto(ArrayValue *val) {}

void arrayValueDestroy(ArrayValue *val) {}

struct Object *arrayValueIndexAccess(ArrayValue *val, int64_t index) {}

struct Object *arrayValueLookupField(ArrayValue *val, ident name) {}

struct Object *arrayValueLookupMethod(ArrayValue *val, ident name) {}

void arrayValueRef(ArrayValue *unit) {}

void arrayValueUnref(ArrayValue *unit) {}

TypeValue *typeValueCreate() {}

TypeValue *typeValueCopyByAuto(TypeValue *val) {}

void typeValueDestroy(TypeValue *val) {}

void typeValueAddMethod(TypeValue *val, ident name, struct MolaFunctionValue *method) {}

struct Object *typeValueLookupMethod(TypeValue *val, ident name) {}

void typeValueRef(TypeValue *unit) {}

void typeValueUnref(TypeValue *unit) {}

InstanceValue *instanceValueCreate(struct TypeValue *type) {}

InstanceValue *instanceValueCopyByAuto(InstanceValue *val) {}

void instanceValueDestroy(InstanceValue *val) {}

struct Object *instanceValueLookupField(InstanceValue *val, ident name) {}

struct Object *instanceValueLookupMethod(InstanceValue *val, ident name) {}

void instanceValueRef(InstanceValue *unit) {}

void instanceValueUnref(InstanceValue *unit) {}

MolaFunctionValue *
molaFunctionValueCreate(struct Env *env, int64_t rel_offset, size_t n_args, ident *args, int8_t *modes) {}

MolaFunctionValue *molaFunctionValueCopyByAuto(MolaFunctionValue *val) {}

void molaFunctionValueDestroy(MolaFunctionValue *val) {}

void molaFunctionValueRef(MolaFunctionValue *unit) {}

void molaFunctionValueUnref(MolaFunctionValue *unit) {}

CFunctionValue *cFunctionValueCreate(struct Env *env, size_t n_args, int8_t *modes, CFunction function) {}

CFunctionValue *cFunctionValueCopyByAuto(CFunctionValue *val) {}

void cFunctionValueDestroy(CFunctionValue *val) {}

void cFunctionValueRef(CFunctionValue *unit) {}

void cFunctionValueUnref(CFunctionValue *unit) {}

ModuleValue *moduleValueCreate(struct Env *env, int64_t absolute_offset) {}

ModuleValue *moduleValueCopyByAuto(ModuleValue *val) {}

void moduleValueDestroy(ModuleValue *val) {}

void moduleValueRef(ModuleValue *unit) {}

void moduleValueUnref(ModuleValue *unit) {}
