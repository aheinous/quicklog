#pragma once
#ifdef __CPLUSPLUS
extern "C" {
#endif


#include "qkl_lr_buff.h"
#include "qkl_entry.h"
#include "qkl_usr_config.h"

#define QKLOG(prod, ...) QKL_PRINTF_ENCODE(qkl_prod_new_entry, &prod, __VA_ARGS__)

typedef struct {
    qkl_lr_buff buff;

} qkl_prod;


void qkl_prod_init(qkl_prod* log_prod, void*data, int data_size, int num_elems);
void qkl_prod_new_entry(qkl_prod* log_prod, const char*fmt, uint8_t*data, int len);

#ifdef __CPLUSPLUS
}
#endif