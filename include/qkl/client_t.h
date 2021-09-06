#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "qkl/lr_buff.h"

typedef struct {
	qkl_lr_buff buff;
	int dropped;
} qkl_client;


#ifdef __cplusplus
}
#endif