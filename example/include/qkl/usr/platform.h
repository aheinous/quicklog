#pragma once
#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>	// used by qkl
#include <stddef.h>	// used by qkl
#include <string.h>	// used by qkl
#include <stdarg.h>// used by qkl

#include <pthread.h> // for usr impl

#define QKL_MEMBAR() __asm__ volatile ("" : : : "memory")

#define QKL_USR_SYNC_PRIMITIVES_PROVIDED 1


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


#ifdef __cplusplus
}
#endif



