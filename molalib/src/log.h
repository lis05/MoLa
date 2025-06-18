#ifndef __mola_log_h__
#define __mola_log_h__

#include <string.h>
#include <time.h>

static char __molalog_protected_buf_dont_touch_dont_you_dare[32];

#define molalog(...)                                                                                                             \
    {                                                                                                                            \
        sprintf(__molalog_protected_buf_dont_touch_dont_you_dare, "%.3f", 1.0 * clock() / CLOCKS_PER_SEC);                       \
        printf("[%8s]  %-10s: ",                                                                                                 \
               __molalog_protected_buf_dont_touch_dont_you_dare,                                                                 \
               1.0 * clock() / CLOCKS_PER_SEC,                                                                                   \
               strrchr(__FILE__, '/') + 1);                                                                                      \
        printf(__VA_ARGS__);                                                                                                     \
    }

#endif
