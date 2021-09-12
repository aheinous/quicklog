#pragma once
#ifdef __cplusplus
extern "C" {
#endif


#include "qkl/config.h"
#include "qkl/platform.h"


typedef struct {
	const char *fmt;
	uint8_t data[64];
} qkl_entry;


#ifdef __cplusplus
}
#endif