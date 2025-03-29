#ifndef __mola_gc_h__
#define __mola_gc_h__

#include "../util.h"

struct Object;
struct NullValue;
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
void gcDeclareGarbageStringValue(struct StringValue *unit);
void gcDeclareGarbageArrayValue(struct ArrayValue *unit);
void gcDeclareGarbageTypeValue(struct TypeValue *unit);
void gcDeclareGarbageInstanceValue(struct InstanceValue *unit);
void gcDeclareGarbageMolaFunctionValue(struct MolaFunctionValue *unit);
void gcDeclareGarbageCFunctionValue(struct CFunctionValue *unit);
void gcDeclareGarbageModuleValue(struct ModuleValue *unit);

struct VM;

#define CHECKPHASE_THRESHOLD       100000
#define GC_CYCLE_THRESHOLD         6
#define GC_CYCLE_CHECKPHASES_LIMIT 100
int CHECKPHASE_RATIO();

void gcInit(struct VM *vm);
void gcRunCycle(struct VM *vm);

// note: tracking an object does not automatically make gc tracking its value
void gcTrackObject(struct Object *unit);
void gcTrackStringValue(struct StringValue *unit);
void gcTrackArrayValue(struct ArrayValue *unit);
void gcTrackTypeValue(struct TypeValue *unit);
void gcTrackInstanceValue(struct InstanceValue *unit);
void gcTrackMolaFunctionValue(struct MolaFunctionValue *unit);
void gcTrackCFunctionValue(struct CFunctionValue *unit);
void gcTrackModuleValue(struct ModuleValue *unit);

// even if gc is locked, unit will be added to the garbage list if it is indeed garbage
void gcMaybeGarbageObject(struct Object *unit);

void gcLock();    // lock intended to prevent destruction of objects when executing an instruction
void gcUnlock();
int  gcIsLocked();

#endif
