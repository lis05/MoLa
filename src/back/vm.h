#ifndef __mola_vm_h__
#define __mola_vm_h__

#include "gen.h"

struct Instruction;

struct Instruction *vmCurrentInstruction();
void                vmExecute(ivec instructions);

#endif
