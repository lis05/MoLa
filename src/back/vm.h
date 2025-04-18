#ifndef __mola_vm_h__
#define __mola_vm_h__

#include "gen.h"

struct Instruction;

struct Instruction *vmCurrentInstruction();
struct Instruction *vmInstruction(int64_t ip);
void                vmExecute(ivec instructions);

#endif
