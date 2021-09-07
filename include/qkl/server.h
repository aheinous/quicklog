#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "qkl/client_t.h"


void qkl_init();
void qkl_reg(qkl_client *client, const char *name);
void qkl_process();
void qkl_unreg(qkl_client *client);

#ifdef __cplusplus
}
#endif


#if defined(QKL_INCLUDE_TESTS) && defined(__cplusplus)
	#include <doctest/doctest.h>
	#include <time.h>
	#include "qkl/client.h"



int m_sleep(ssize_t msec) {
	if(msec < 0) {
		return -EINVAL;
	}
	struct timespec ts;
	ts.tv_sec = msec / 1000;
	ts.tv_nsec = (msec % 1000) * 1000000;
	return nanosleep(&ts, &ts);
}

volatile bool unreg_complete = false;
pthread_t unreg_thd;

void *unreg_main(void *arg) {
	qkl_client* client = (qkl_client*) arg;
	qkl_unreg(client);
	unreg_complete = true;
	return NULL;
}

TEST_CASE("client server") {
	qkl_init();
	clear_log_buffer();

	QKL_CLIENT_DEFINE_INIT(client, "first client", 4);
	SUBCASE("cases where qkl_unreg() called after"){
		SUBCASE("no crash on first qkl_process call") {
			qkl_process();
		}

		SUBCASE("one log works") {
			const char *s = "abc";
			QKLOG(client, "fmt string %s %s\n", "abc", s);
			qkl_process();

			CHECK(get_usr_log(-1) == "[first client]: fmt string abc abc\n");
		}

		SUBCASE("1 dropped msg") {
			QKLOG(client, "%d\n", 0);
			QKLOG(client, "%d\n", 1);
			QKLOG(client, "%d\n", 2);
			QKLOG(client, "%d\n", 3);
			QKLOG(client, "%d\n", 4);

			qkl_process();

			CHECK(get_usr_log(-4) == "[first client]: 0\n");
			CHECK(get_usr_log(-3) == "[first client]: 1\n");
			CHECK(get_usr_log(-2) == "[first client]: 2\n");
			CHECK(get_usr_log(-1) == "[first client]: 3\n");

			QKLOG(client, "%d\n", 5);
			qkl_process();
			CHECK(get_usr_log(-2) == "[first client]: <1 msg dropped>\n");
			CHECK(get_usr_log(-1) == "[first client]: 5\n");
		}

		SUBCASE("multiple dropped msgs") {
			for(int i = 0; i < 9; i++) {
				QKLOG(client, "%d\n", i);
			}
			qkl_process();
			QKLOG(client, "%d\n", 9);
			qkl_process();
			CHECK(get_usr_log(-2) == "[first client]: <5 msgs dropped>\n");
			CHECK(get_usr_log(-1) == "[first client]: 9\n");
		}
		qkl_unreg(&client);
	}

	SUBCASE("_flush flushes msgs on qkl_unreg()"){
		for(int i = 0; i < 6; i++) {
			QKLOG(client, "%d\n", i);
		}
		// unreg in different thread some we can call process
		pthread_create(&unreg_thd, NULL, unreg_main, &client);
		m_sleep(10);


		qkl_process();

		CHECK(get_usr_log(-4) == "[first client]: 0\n");
		CHECK(get_usr_log(-3) == "[first client]: 1\n");
		CHECK(get_usr_log(-2) == "[first client]: 2\n");
		CHECK(get_usr_log(-1) == "[first client]: 3\n");
		while(!unreg_complete){
			qkl_process();
			pthread_yield();
		}
		pthread_join(unreg_thd, NULL);
		CHECK(get_usr_log(-1) == "[first client]: <2 msgs dropped>\n");

	}
}
#endif