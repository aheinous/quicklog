#pragma once
#ifdef __CPLUSPLUS
extern "C" {
#endif


#include "qkl_usr_config.h"


typedef struct {
    const char *fmt;
    uint8_t data[64];
} qkl_entry;



#ifdef __CPLUSPLUS
}
#endif