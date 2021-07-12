#pragma once
#ifdef __CPLUSPLUS
extern "C" {
#endif


// #include "qkl/qkl_usr_config.h"
#include "qkl/qkl_usr_platform.h"


typedef struct {
    volatile uint8_t num_puts;
    volatile uint8_t num_gets;
} qkl_sem_t;


void qkl_sem_init(qkl_sem_t*);
void qkl_sem_put(qkl_sem_t*);
uint8_t qkl_sem_peek(qkl_sem_t*);
/**
 * @brief Decrement semaphore count. Assume peek was called already and
 * decrement without checking.
 */
void qkl_sem_get(qkl_sem_t*);

#ifdef __CPLUSPLUS
}
#endif