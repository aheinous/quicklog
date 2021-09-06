#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "qkl.h"


int m_sleep(ssize_t msec) {
	if(msec < 0) {
		return -EINVAL;
	}
	struct timespec ts;
	ts.tv_sec = msec / 1000;
	ts.tv_nsec = (msec % 1000) * 1000000;
	return nanosleep(&ts, &ts);
}


pthread_t process_thd;

void *process_loop(void *a) {
	(void)a;

	while(1) {
		qkl_process();
		m_sleep(50);
	}
}


QKL_CLIENT_DEFINE(static_client, 4);


pthread_t print_thd_a;
pthread_t print_thd_b;

void *print_thd_loop(void *name) {
	QKL_CLIENT_DEFINE_INIT(client, (const char *)name, 32);

	for(int i = 0; i < 5; i++) {
		QKLOG(client, "iter: %d\n", i);
		m_sleep(100);
	}
	qkl_unreg(&client);
	return NULL;
}


int main(int argc, char **argv) {
	(void)argc;
	(void)argv;

	qkl_init();
	pthread_create(&process_thd, NULL, process_loop, NULL);

	QKL_CLIENT_INIT(static_client, "Static Client");

	QKLOG(static_client, "Hello World\n");
	QKLOG(static_client, "%s %d\n", "abc", 123);
	QKLOG(static_client, "%d %d\n", 1, 2);

	qkl_unreg(&static_client);

	pthread_create(&print_thd_a, NULL, print_thd_loop, "Thread A");
	pthread_create(&print_thd_b, NULL, print_thd_loop, "Thread B");

	pthread_join(print_thd_a, NULL);
	pthread_join(print_thd_b, NULL);
	return 0;
}
