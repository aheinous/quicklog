#include <array>
#include <chrono>
#include <cstdio>
#include <errno.h>
#include <pthread.h>
#include <time.h>

#include "qkl.h"


using std::chrono::high_resolution_clock;

int m_sleep(ssize_t msec) {
	if(msec < 0) {
		return -EINVAL;
	}
	struct timespec ts;
	ts.tv_sec = msec / 1000;
	ts.tv_nsec = (msec % 1000) * 1000000;
	return nanosleep(&ts, &ts);
}


class LogProducer {
public:
	LogProducer(const char *name)
	    : m_name(name) {
	}

	void start() {
		// m_thread = std::thread(call_process, this);
		pthread_create(&m_thread, NULL, call_process, this);
	}

	void join() {
		// m_thread.join();
		pthread_join(m_thread, NULL);
	}

private:
	void process() {
		QKL_CLIENT_DEFINE_INIT(client, m_name, 16 * 1024);

		char buffer[128];

		std::chrono::nanoseconds quicklog_time(0);
		std::chrono::nanoseconds printf_time(0);
		std::chrono::nanoseconds snprintf_time(0);


		for(int i = 0; i < 10 * 1024; i++) {
			auto a = high_resolution_clock::now();
			QKLOG(client, "ql[%s] n: %d\n", m_name, i);

			auto b = high_resolution_clock::now();
			printf("pf[%s] n: %d\n", m_name, i);

			auto c = high_resolution_clock::now();
			volatile int n = snprintf(buffer, sizeof(buffer), "sn[%s] n: %d\n", m_name, i);
			(void)n;

			auto d = high_resolution_clock::now();
			quicklog_time += (b - a);
			printf_time += (c - b);
			snprintf_time += (d - c);
		}

		m_sleep(1000);

		QKLOG(client,
		      "times: %s \n\tquicklog: %ld us\n\tprintf: %ld us\n\tsnprintf: %ld us\n",
		      m_name,
		      std::chrono::duration_cast<std::chrono::microseconds>(quicklog_time).count(),
		      std::chrono::duration_cast<std::chrono::microseconds>(printf_time).count(),
		      std::chrono::duration_cast<std::chrono::microseconds>(snprintf_time).count()

		);

		qkl_unreg(&client); // ensure flushed
	}

	static void *call_process(void *self) {
		static_cast<LogProducer *>(self)->process();
		return nullptr;
	}

	const char *m_name = nullptr;
	// quicklog::LocalLogger<8, 16 * 1024> m_logger;
	pthread_t m_thread;
};


pthread_t process_thd;

void *process_loop(void *a) {
	(void)a;

	while(1) {
		qkl_process();
		m_sleep(50);
	}
}

void quicklog_server_start() {
	pthread_create(&process_thd, NULL, process_loop, NULL);
}


std::array<LogProducer, 4> producers{
    LogProducer("a"),
    LogProducer("b"),
    LogProducer("c"),
    LogProducer("d"),
};


int main() {
	quicklog_server_start();

	for(auto &p : producers) {
		p.start();
	}

	for(auto &p : producers) {
		p.join();
	}

	printf("DONE\n");
}
