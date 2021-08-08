#include "log_out_buffer.h"

#include <vector>

std::vector<std::string> log_buffer;

void usr_log_out(const char *s){
    log_buffer.push_back(s);
}

std::string get_usr_log(int i){
    if( i >= 0){
        return log_buffer[i];
    }else{
        return log_buffer[ log_buffer.size() + i ];
    }

}
