#include "log_out_buffer.h"

#include <vector>

std::vector<std::string> log_buffer;

extern "C" void qkl_usr_log_out(char *s) {
	log_buffer.push_back(s);
}

std::string get_usr_log(int i) {
	if(i >= 0) {
		return log_buffer[i];
	} else {
		return log_buffer[log_buffer.size() + i];
	}
}
