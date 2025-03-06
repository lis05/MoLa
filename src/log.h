#ifndef __mola_log_h__
#define __mola_log_h__

#include <string.h>

#define molalog(...)                                                                                                   \
    {                                                                                                                  \
        printf("... %-10s: ", strrchr(__FILE__, '/') + 1);                                                             \
        printf(__VA_ARGS__);                                                                                           \
    }

#endif
