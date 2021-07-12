#include "qkl_usr_platform.h"
#include "qkl_usr_config.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void _onFailedAssert(const char *cond, const char *file, int line, ...) {
    va_list vargs;
    va_start(vargs, line);

    fprintf(stderr, "ASSERTION FAILURE: %s evaluates to false.\n", cond);
    fprintf(stderr, "At %s:%d\n", file, line);

    const char *usrFmt = va_arg(vargs, const char *);
    if(usrFmt[0] != '\0') {
        vfprintf(stderr, usrFmt, vargs);
        fprintf(stderr, "\n");
    }


    va_end(vargs);

    fflush(stderr);
    abort();

    exit(EXIT_FAILURE);
}



void qkl_usr_mutex_init(qkl_usr_mutex *usr_mutex){
    pthread_mutex_init(&usr_mutex->mutex, NULL);
}
void qkl_usr_mutex_lock(qkl_usr_mutex *usr_mutex){
    pthread_mutex_lock(&usr_mutex->mutex);

}
void qkl_usr_mutex_unlock(qkl_usr_mutex *usr_mutex){
    pthread_mutex_unlock(&usr_mutex->mutex);

}



void qkl_usr_cond_init(qkl_usr_cond *cond){
    pthread_cond_init(&cond->cond, NULL);
}
void qkl_usr_cond_broadcast(qkl_usr_cond *cond){
    pthread_cond_broadcast(&cond->cond);
}
void qkl_usr_cond_wait(qkl_usr_cond *cond, qkl_usr_mutex *mutex){
    pthread_cond_wait(&cond->cond, &mutex->mutex);
}

