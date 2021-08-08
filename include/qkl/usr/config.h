#pragma once
#ifdef __cplusplus
extern "C" {
#endif

// Modify this file, or provide your own version elsewhere
// to configure Quicklog



// function called by qkl to outputs logs
#define QKL_USR_LOG_OUT(s) usr_log_out(s)
static void usr_log_out(const char* s) {
    (void) s;
}


// maximum number of clients
#define QKL_MAX_CLIENTS 4



// assert macro
#define QKL_ASSERT(cond, ...) do{											\
	if(!(cond)){															\
		_onFailedAssert( #cond, __FILE__, __LINE__, "" __VA_ARGS__);  		\
	}																		\
} while(0)
static void _onFailedAssert(const char *cond, const char *file, int line, ...){
    (void) cond;
    (void) file;
    (void) line;
}



#ifdef __cplusplus
}
#endif