#ifndef __mola_gc_h__
#define __mola_gc_h__

#include "../util.h"

struct Object;
struct StringValue;
struct ArrayValue;
struct TypeValue;
struct InstanceValue;
struct MolaFunctionValue;
struct CFunctionValue;

void gcDeclareGarbageObject(struct Object *unit);
void gcDeclareGarbageStringValue(struct StringValue *unit);
void gcDeclareGarbageArrayValue(struct ArrayValue *unit);
void gcDeclareGarbageTypeValue(struct TypeValue *unit);
void gcDeclareGarbageInstanceValue(struct InstanceValue *unit);
void gcDeclareGarbageMolaFunctionValue(struct MolaFunctionValue *unit);
void gcDeclareGarbageCFunctionValue(struct CFunctionValue *unit);

void gcInit();
void gcRunCycle();

// note: tracking an object does not automatically make gc tracking its value
void gcTrackObject(struct Object *unit);
void gcTrackStringValue(struct StringValue *unit);
void gcTrackArrayValue(struct ArrayValue *unit);
void gcTrackTypeValue(struct TypeValue *unit);
void gcTrackInstanceValue(struct InstanceValue *unit);
void gcTrackMolaFunctionValue(struct MolaFunctionValue *unit);
void gcTrackCFunctionValue(struct CFunctionValue *unit);

void gcUntrackObject(struct Object *unit);
void gcUntrackStringValue(struct StringValue *unit);
void gcUntrackArrayValue(struct ArrayValue *unit);
void gcUntrackTypeValue(struct TypeValue *unit);
void gcUntrackInstanceValue(struct InstanceValue *unit);
void gcUntrackMolaFunctionValue(struct MolaFunctionValue *unit);
void gcUntrackCFunctionValue(struct CFunctionValue *unit);


// recycles at most the given amount of bytes
void gcRecycle(size_t bytes);

extern uint gc_mark;
extern size_t instructions_since_gc_cycle;

#endif
