#include "error.h"

jmp_buf __mola_errorbuf;
char    __mola_errstrfmtbuf[1024];

void signalError(int64_t code, char *reason) {
    // temporary
}
