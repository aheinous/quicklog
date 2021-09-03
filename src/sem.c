
#include "qkl/sem.h"
#include <qkl_usr_platform.h>
#include "qkl/config.h"

void qkl_sem_init(qkl_sem_t *sem){
    sem->num_puts = 0;
    sem->num_gets = 0;
}

void qkl_sem_put(qkl_sem_t *sem){
    QKL_MEMBAR();
    sem->num_puts++;
}

int qkl_sem_peek(qkl_sem_t *sem) {
    QKL_MEMBAR();
    return sem->num_puts - sem->num_gets;
}

void qkl_sem_get(qkl_sem_t *sem){
    QKL_MEMBAR();
    QKL_ASSERT(qkl_sem_peek(sem) != 0);
    sem->num_gets++;
}

