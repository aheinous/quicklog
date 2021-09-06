#include <qkl_usr_platform.h>
#include <stdio.h>
#include <stdlib.h>

void qkl_on_failed_assert(const char *cond, const char *file, int line, ...) {
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
	exit(EXIT_FAILURE);
}