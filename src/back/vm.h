#ifndef __mola_vm_h__
#define __mola_vm_h__

struct Instruction;

struct Instruction *vmCurrentInstruction();
void                vmExecute(ivec instructions);

#endif
