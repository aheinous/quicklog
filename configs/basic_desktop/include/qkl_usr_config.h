#pragma once
#ifdef __cplusplus
extern "C" {
#endif

// Provide a modified version of this file to configure Quicklog


// usr function called by qkl to outputs logs
void qkl_usr_log_out(char *s);


void qkl_on_failed_assert(const char *cond, const char *file, int line, ...);



// maximum number of clients
#define QKL_MAX_CLIENTS 128


typedef unsigned int qkl_index_t;


#ifdef __cplusplus
}
#endif