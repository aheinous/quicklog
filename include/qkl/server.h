#pragma once
#ifdef __CPLUSPLUS
extern "C" {
#endif

#include "qkl/prod.h"


void qkl_init();
void qkl_reg(qkl_prod *log_prod, const char*name);
void qkl_process();
void qkl_unreg(qkl_prod* prod);

#ifdef __CPLUSPLUS
}
#endif