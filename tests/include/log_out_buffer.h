#pragma once
#ifdef __cplusplus
extern "C" {
#endif

void usr_log_out(const char *s);

#ifdef __cplusplus
} // extern "C"

    extern "C++"{
        #include <string>
        std::string get_usr_log(int);

    }
#endif  //__cplusplus


