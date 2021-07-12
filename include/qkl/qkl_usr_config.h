#pragma once
#ifdef __CPLUSPLUS
extern "C" {
#endif


void usr_log_out(const char* s);

#define QKL_USR_LOG_OUT(s) usr_log_out(s)


#define QKL_MAX_LOG_PROD 4



#define QKL_ASSERT(cond, ...) do{												\
	if(!(cond)){															\
		_onFailedAssert( #cond, __FILE__, __LINE__, "" __VA_ARGS__);  		\
	}																		\
} while(0)



void _onFailedAssert(const char *cond, const char *file, int line, ...);



#ifdef __CPLUSPLUS
}
#endif