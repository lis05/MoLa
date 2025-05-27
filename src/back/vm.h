#ifndef __mola_vm_h__
#define __mola_vm_h__

#include "gen.h"

struct Instruction;

struct Instruction *vmCurrentInstruction();
struct Instruction *vmInstruction(int64_t ip);
void                vmExecute(ivec instructions);

struct Object;
typedef struct ReferencedObject {
    struct Object *obj;
    int64_t ip;
} ReferencedObject;

struct Env;
ivec compileProgram(char *filename, int64_t *env_id);

#endif
