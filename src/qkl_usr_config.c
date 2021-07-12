#include "qkl/qkl_usr_config.h"


#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>


void usr_log_out(const char *s){
    printf("%s", s);
}



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