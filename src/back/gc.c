#include "gc.h"
#include "object.h"

void gcDeclareGarbageObject(struct Object *unit) {}

void gcDeclareGarbageNullValue(struct NullValue *unit) {}

void gcDeclareGarbageBoolValue(struct BoolValue *unit) {}

void gcDeclareGarbageIntValue(struct IntValue *unit) {}

void gcDeclareGarbageCharValue(struct CharValue *unit) {}

void gcDeclareGarbageFloatValue(struct FloatValue *unit) {}

void gcDeclareGarbageStringValue(struct StringValue *unit) {}

void gcDeclareGarbageArrayValue(struct ArrayValue *unit) {}

void gcDeclareGarbageTypeValue(struct TypeValue *unit) {}

void gcDeclareGarbageInstanceValue(struct InstanceValue *unit) {}

void gcDeclareGarbageMolaFunctionValue(struct MolaFunctionValue *unit) {}

void gcDeclareGarbageCFunctionValue(struct CFunctionValue *unit) {}

void gcDeclareGarbageModuleValue(struct ModuleValue *unit) {}

int CHECKPHASE_RATIO() {}

void gcInit(struct VM *vm) {}

void gcRunCycle(struct VM *vm) {}

// note: tracking an object does not automatically make gc tracking its value
void gcTrackObject(struct Object *unit) {}

void gcTrackNullValue(struct NullValue *unit) {}

void gcTrackBoolValue(struct BoolValue *unit) {}

void gcTrackIntValue(struct IntValue *unit) {}

void gcTrackCharValue(struct CharValue *unit) {}

void gcTrackFloatValue(struct FloatValue *unit) {}

void gcTrackStringValue(struct StringValue *unit) {}

void gcTrackArrayValue(struct ArrayValue *unit) {}

void gcTrackTypeValue(struct TypeValue *unit) {}

void gcTrackInstanceValue(struct InstanceValue *unit) {}

void gcTrackMolaFunctionValue(struct MolaFunctionValue *unit) {}

void gcTrackCFunctionValue(struct CFunctionValue *unit) {}

void gcMaybeGarbageObject(struct Object *unit) {
    assert(unit != NULL);
    if (unit->ref_count == 0) {
        // add to garbage list
    }
}

static int gc_lock = 0;

void gcLock() {
    gc_lock++;
}

void gcUnlock() {
    gc_lock--;
}

int gcIsLocked() {
    return gc_lock;
}
