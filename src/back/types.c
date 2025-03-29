#include "types.h"
#include "alloc.h"
#include "gc.h"

StringValue *stringValueCreate(size_t length, char *string) {}

StringValue *stringValueCopy(StringValue *val) {}

void stringValueDestroy(StringValue *val) {}

char stringValueIndexAccess(StringValue *val, int64_t index) {}

struct Object *stringValueLookupField(StringValue *val, ident name) {}

struct Object *stringValueLookupMethod(StringValue *val, ident name) {}

void stringValueRef(StringValue *unit) {}

void stringValueUnref(StringValue *unit) {}

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

MolaFunctionValue *
molaFunctionValueCreate(struct Env *env, int64_t rel_offset, size_t n_args, ident *args) {}

MolaFunctionValue *molaFunctionValueCopy(MolaFunctionValue *val) {}

void molaFunctionValueDestroy(MolaFunctionValue *val) {}

void molaFunctionValueRef(MolaFunctionValue *unit) {}

void molaFunctionValueUnref(MolaFunctionValue *unit) {}

CFunctionValue *cFunctionValueCreate(struct Env *env, size_t n_args, int8_t *modes, CFunction function) {}

CFunctionValue *cFunctionValueCopy(CFunctionValue *val) {}

void cFunctionValueDestroy(CFunctionValue *val) {}

void cFunctionValueRef(CFunctionValue *unit) {}

void cFunctionValueUnref(CFunctionValue *unit) {}

ModuleValue *moduleValueCreate(struct Env *env, int64_t absolute_offset) {}

ModuleValue *moduleValueCopy(ModuleValue *val) {}

void moduleValueDestroy(ModuleValue *val) {}

void moduleValueRef(ModuleValue *unit) {}

void moduleValueUnref(ModuleValue *unit) {}
