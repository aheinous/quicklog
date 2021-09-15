#pragma once
#ifdef __cplusplus
extern "C" {
#endif


#include <stdarg.h>  // used by qkl
#include <stddef.h>  // used by qkl
#include <stdint.h>  // used by qkl
#include <string.h>  // used by qkl
#include <zephyr.h>

#define QKL_MEMBAR() __asm__ volatile("" : : : "memory")
#define FALLTHROUGH() __attribute__((fallthrough))
#define QKL_ALWAYS_INLINE(func_signature) func_signature __attribute__((always_inline))
#define VALIDATE_PRINTF_ARGS(...) validate_printf_args(__VA_ARGS__)
static inline void validate_printf_args(const char *fmt, ...) __attribute__((format(printf, 1, 2)));
static inline void validate_printf_args(const char *fmt, ...) {
	(void)fmt;
}


#define QKL_USR_SYNC_PRIMITIVES_PROVIDED 1


typedef struct {
	struct k_mutex mutex;
} qkl_usr_mutex;

void qkl_usr_mutex_init(qkl_usr_mutex *usr_mutex);
void qkl_usr_mutex_lock(qkl_usr_mutex *usr_mutex);
void qkl_usr_mutex_unlock(qkl_usr_mutex *usr_mutex);


typedef struct {
	struct k_condvar cond;
} qkl_usr_cond;

void qkl_usr_cond_init(qkl_usr_cond *cond);
void qkl_usr_cond_broadcast(qkl_usr_cond *cond);
void qkl_usr_cond_wait(qkl_usr_cond *cond, qkl_usr_mutex *mutex);


#ifdef __cplusplus
}
#endif
