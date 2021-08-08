#pragma once
#ifdef __cplusplus
extern "C" {
#endif



// Modify this file, or provide your own version elsewhere
// to provide Quicklog with platform specific implementations


// Headers used by quicklog. On some (embedded) platforms
// the needed definitions may be located elsewhere
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <stdarg.h>


// memory barrior
#define QKL_MEMBAR() __asm__ volatile ("" : : : "memory")
// suppress fallthrough warning for switch statements
#define FALLTHROUGH() __attribute__((fallthrough))

#define ALWAYS_INLINE() __attribute__((always_inline))



// These sync primitaves are only used when registering
// and deregistering qkl clients. If you can guarentee
// that qkl_process, qkl_reg and qkl_unreg will not be
// called concurrently then these
// can be left as is.
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



#define qkl_usr_mutex_init(usr_mutex)
#define qkl_usr_mutex_lock(usr_mutex)
#define qkl_usr_mutex_unlock(usr_mutex)



#define qkl_usr_cond_init(cond)
#define qkl_usr_cond_broadcast(cond)
#define qkl_usr_cond_wait(cond)


#endif //  else QKL_USR_SYNC_PRIMITIVES_PROVIDED



#ifdef __cplusplus
}
#endif



