#pragma once
#ifdef __CPLUSPLUS
extern "C" {
#endif


#include "qkl/lr_buff.h"
#include "qkl/entry.h"
#include "qkl/usr/config.h"

#define QKLOG(prod, ...) QKL_PRINTF_ENCODE(qkl_prod_new_entry, &prod, __VA_ARGS__)

typedef struct {
    qkl_lr_buff buff;
    int dropped;
} qkl_prod;


void qkl_prod_init(qkl_prod* log_prod, void*data, int data_size, int num_elems);
void qkl_prod_new_entry(qkl_prod* log_prod, const char*fmt, uint8_t*data, int len);


#define QKL_PROD(var, name, num_elems) \
    char _qkl_mk_prod_ ## var ## _data [ (num_elems) * sizeof(qkl_entry) ]; \
    qkl_prod var; \
    qkl_prod_init(&var, _qkl_mk_prod_ ## var ## _data, (num_elems) * sizeof(qkl_entry), (num_elems)); \
    qkl_reg(&var, name)


#ifdef __CPLUSPLUS
}
#endif