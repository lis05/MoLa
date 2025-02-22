#ifndef __mola_gc_h__
#define __mola_gc_h__

#include "../util.h"

struct Object;
struct BoolValue;
struct IntValue;
struct CharValue;
struct FloatValue;
struct StringValue;
struct ArrayValue;
struct TypeValue;
struct InstanceValue;
struct MolaFunctionValue;
struct CFunctionValue;
struct ModuleValue;

void gcDeclareGarbage(struct Object *unit);
void gcDeclareGarbage(struct BoolValue *unit);
void gcDeclareGarbage(struct IntValue *unit);
void gcDeclareGarbage(struct CharValue *unit);
void gcDeclareGarbage(struct FloatValue *unit);
void gcDeclareGarbage(struct StringValue *unit);
void gcDeclareGarbage(struct ArrayValue *unit);
void gcDeclareGarbage(struct TypeValue *unit);
void gcDeclareGarbage(struct InstanceValue *unit);
void gcDeclareGarbage(struct MolaFunctionValue *unit);
void gcDeclareGarbage(struct CFunctionValue *unit);
void gcDeclareGarbage(struct ModuleValue *unit);

#endif
