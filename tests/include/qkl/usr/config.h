#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "log_out_buffer.h"

// extern char usr_log_buffer[128];


// void usr_log_out(const char * s);

#define QKL_USR_LOG_OUT(s) usr_log_out(s)
#define QKL_MAX_CLIENTS 4
#define QKL_ASSERT(cond, ...) ((void) sizeof(cond))



#ifdef __cplusplus
}
#endif