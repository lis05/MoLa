#include "error.h"
#include <stdio.h>

jmp_buf __mola_errorbuf;
char    __mola_errstrfmtbuf[1024];

void signalError(int64_t code, char *reason) {
    // replace
    printf("!!!! ERROR %d: %s\n", code, reason);
    exit(1);
}
