#include "qkl_usr_platform.h"

#include <zephyr.h>

#include "qkl/config.h"


void qkl_usr_mutex_init(qkl_usr_mutex *usr_mutex) {
	k_mutex_init(&usr_mutex->mutex);
}
void qkl_usr_mutex_lock(qkl_usr_mutex *usr_mutex) {
	k_mutex_lock(&usr_mutex->mutex, K_FOREVER);
}
void qkl_usr_mutex_unlock(qkl_usr_mutex *usr_mutex) {
	k_mutex_unlock(&usr_mutex->mutex);
}


void qkl_usr_cond_init(qkl_usr_cond *cond) {
	k_condvar_init(&cond->cond);
}
void qkl_usr_cond_broadcast(qkl_usr_cond *cond) {
	k_condvar_broadcast(&cond->cond);
}
void qkl_usr_cond_wait(qkl_usr_cond *cond, qkl_usr_mutex *mutex) {
	k_condvar_wait(&cond->cond, &mutex->mutex, K_FOREVER);
}
