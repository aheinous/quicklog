#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "qkl/encode.h"
#include "qkl/lr_buff.h"
#include "qkl/entry.h"
#include "qkl/config.h"
#include "qkl/client_t.h"
#include "qkl/server.h"


#define QKLOG(client, ...) QKL_PRINTF_ENCODE(qkl_client_new_entry, &client, __VA_ARGS__)


void qkl_client_init(qkl_client* client, void*data, int data_size, int num_elems);
void qkl_client_new_entry(qkl_client* client, const char*fmt, uint8_t*data, int len);



#define QKL_CLIENT_DEFINE(var, num_elems)                                        \
    char _qkl_client_define_ ## var ## _data [ (num_elems) * sizeof(qkl_entry) ]; \
    qkl_client var;

#define QKL_CLIENT_INIT(var, name)                                      \
    qkl_client_init(&var, _qkl_client_define_ ## var ## _data,              \
        sizeof(_qkl_client_define_ ## var ## _data),                        \
        sizeof(_qkl_client_define_ ## var ## _data) / sizeof(qkl_entry));   \
    qkl_reg(&var, name)



#define QKL_CLIENT_DEFINE_INIT(var, name, num_elems)   \
    QKL_CLIENT_DEFINE(var, num_elems);                 \
    QKL_CLIENT_INIT(var, name)


#ifdef __cplusplus
}
#endif