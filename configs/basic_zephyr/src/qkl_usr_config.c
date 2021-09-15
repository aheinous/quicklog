#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "qkl/config.h"
#include <zephyr.h>


void qkl_usr_log_out(char *s) {
	printk("%s", s);
}

void qkl_on_failed_assert(const char *cond, const char *file, int line, ...) {
    assert_post_action(file, line);
}