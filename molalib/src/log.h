#ifndef __mola_log_h__
#define __mola_log_h__

#include <string.h>
#include <time.h>

static char buf[32];

#define molalog(...)                                                                                                   \
    {                                                                                                                  \
        sprintf(buf, "%.3f", 1.0 * clock() / CLOCKS_PER_SEC);                                                          \
        printf("[%8s]  %-10s: ", buf, 1.0 * clock() / CLOCKS_PER_SEC, strrchr(__FILE__, '/') + 1);                      \
        printf(__VA_ARGS__);                                                                                           \
    }

#endif
