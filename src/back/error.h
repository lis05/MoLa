#ifndef __mola_error_h__
#define __mola_error_h__

#include "../util.h"
#include <setjmp.h>

#define INTERNAL_ERROR_CODE                  0
#define IMPORT_ERROR_CODE                    1
#define NAME_COLLISION_ERROR_CODE            2
#define DUPLICATE_NAME_ERROR_CODE            3
#define VALUE_ERROR_CODE                     4
#define NAME_ERROR_CODE                      5
#define WRONG_NUMBER_OF_ARGUMENTS_ERROR_CODE 6
#define OUT_OF_BOUNDS_ERROR_CODE             7
#define ZERO_DIVISION_ERROR_CODE             8
#define OUT_OF_MEMORY_ERROR_CODE             9

struct Scope;

/*

If an error happens during the execution of an instruction, it only makes sense to abort that instruction immidiately.
Therefore, after a signalError(), a jongjump is performed to the place in the vm.c where the instruction has been executed.

Note that signalling an error may cause memory leaks. The caller is responsible for handling that.

*/

extern jmp_buf __mola_errorbuf;

#define setErrorReturnPoint()    setjmp(__mola_errorbuf)
#define jumpToErrorReturnPoint() longjmp(__mola_errorbuf, 1)

// error located in vmCurrentInstruction()
// DOES NOT RETURN!
void signalError(int64_t code, char *reason);
void printError(int64_t code, char *reason);
void errorInit();

extern char __mola_errstrfmtbuf[1024];
#define errstrfmt(...)                                                                                                           \
    ({                                                                                                                           \
        snprintf(__mola_errstrfmtbuf, 1024, __VA_ARGS__);                                                                        \
        __mola_errstrfmtbuf;                                                                                                     \
    })

#endif
