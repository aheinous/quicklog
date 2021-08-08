#pragma once
#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>	// used by qkl
#include <stddef.h>	// used by qkl
#include <string.h>	// used by qkl
#include <stdarg.h> // used by qkl


#define QKL_MEMBAR() __asm__ volatile ("" : : : "memory")


#define QKL_USR_SYNC_PRIMITIVES_PROVIDED 0


#if QKL_USR_SYNC_PRIMITIVES_PROVIDED

typedef struct{
} qkl_usr_mutex;

void qkl_usr_mutex_init(qkl_usr_mutex* usr_mutex);
void qkl_usr_mutex_lock(qkl_usr_mutex* usr_mutex);
void qkl_usr_mutex_unlock(qkl_usr_mutex* usr_mutex);


typedef struct{
}qkl_usr_cond;

void qkl_usr_cond_init(qkl_usr_cond* cond);
void qkl_usr_cond_broadcast(qkl_usr_cond* cond);
void qkl_usr_cond_wait(qkl_usr_cond* cond, qkl_usr_mutex*mutex);


#else //  QKL_USR_SYNC_PRIMITIVES_PROVIDED

typedef struct {
	char x; // empty structs are not allowd
} qkl_usr_mutex;



static void qkl_usr_mutex_init(qkl_usr_mutex *usr_mutex){
		(void*) usr_mutex;
}
static void qkl_usr_mutex_lock(qkl_usr_mutex *usr_mutex){
		(void*) usr_mutex;
}
static void qkl_usr_mutex_unlock(qkl_usr_mutex *usr_mutex){
		(void*) usr_mutex;
}

typedef struct {
	char x;
}qkl_usr_cond;

static void qkl_usr_cond_init(qkl_usr_cond *cond){
	(void) cond;
}
static void qkl_usr_cond_broadcast(qkl_usr_cond *cond){
	(void) cond;
}
static void qkl_usr_cond_wait(qkl_usr_cond *cond, qkl_usr_mutex *mutex){
	(void) cond;
	(void) mutex;
}

#endif //  QKL_USR_SYNC_PRIMITIVES_PROVIDED



#ifdef __cplusplus
}
#endif



