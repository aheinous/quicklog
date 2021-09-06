#pragma once
#ifdef __cplusplus
extern "C" {
#endif


#include <log_out_buffer.h>
// Modify this file, or provide your own version elsewhere
// to configure Quicklog


// function called by qkl to outputs logs
void qkl_usr_log_out(char *s);


void qkl_on_failed_assert(const char *cond, const char *file, int line, ...);


// maximum number of clients
#define QKL_MAX_CLIENTS 4


typedef unsigned int qkl_index_t;


#ifdef __cplusplus
}
#endif