#pragma once
#ifdef __CPLUSPLUS
extern "C" {
#endif

#include <pthread.h>

#define QKL_MEMBAR() __asm__ volatile ("" : : : "memory")


#define QKL_ASSERT(cond, ...) do{												\
	if(!(cond)){															\
		_onFailedAssert( #cond, __FILE__, __LINE__, "" __VA_ARGS__);  		\
	}																		\
} while(0)



void _onFailedAssert(const char *cond, const char *file, int line, ...) ;



typedef struct{
	pthread_mutex_t mutex;
} qkl_usr_mutex;

void qkl_usr_mutex_init(qkl_usr_mutex* usr_mutex);
void qkl_usr_mutex_lock(qkl_usr_mutex* usr_mutex);
void qkl_usr_mutex_unlock(qkl_usr_mutex* usr_mutex);


typedef struct{
	pthread_cond_t cond;
}qkl_usr_cond;

void qkl_usr_cond_init(qkl_usr_cond* cond);
void qkl_usr_cond_broadcast(qkl_usr_cond* cond);
void qkl_usr_cond_wait(qkl_usr_cond* cond, qkl_usr_mutex*mutex);


#ifdef __CPLUSPLUS
}
#endif



