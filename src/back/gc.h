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

void gcDeclareGarbageObject(struct Object *unit);
void gcDeclareGarbageBoolValue(struct BoolValue *unit);
void gcDeclareGarbageIntValue(struct IntValue *unit);
void gcDeclareGarbageCharValue(struct CharValue *unit);
void gcDeclareGarbageFloatValue(struct FloatValue *unit);
void gcDeclareGarbageStringValue(struct StringValue *unit);
void gcDeclareGarbageArrayValue(struct ArrayValue *unit);
void gcDeclareGarbageTypeValue(struct TypeValue *unit);
void gcDeclareGarbageInstanceValue(struct InstanceValue *unit);
void gcDeclareGarbageMolaFunctionValue(struct MolaFunctionValue *unit);
void gcDeclareGarbageCFunctionValue(struct CFunctionValue *unit);
void gcDeclareGarbageModuleValue(struct ModuleValue *unit);

struct VM;

void gcInit(struct VM *vm);
void gcRunCycle(struct VM *vm);

#endif
