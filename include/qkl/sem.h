#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <qkl_usr_platform.h>

#include "qkl/config.h"

typedef struct {
	qkl_atomic_index_t num_puts;
	qkl_atomic_index_t num_gets;
} qkl_sem_t;

void qkl_sem_init(qkl_sem_t *);
void qkl_sem_put(qkl_sem_t *);
int qkl_sem_peek(qkl_sem_t *);
/**
 * @brief Decrement semaphore count. Assume peek was called already and
 * decrement without checking.
 */
void qkl_sem_get(qkl_sem_t *);

#ifdef __cplusplus
}
#endif