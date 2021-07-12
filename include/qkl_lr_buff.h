#pragma once
#ifdef __CPLUSPLUS
extern "C" {
#endif

#include "qkl_sem.h"


typedef struct {
    qkl_sem_t left_avail;
    qkl_sem_t right_avail;

    uint8_t left_idx;
    uint8_t right_idx;

    uint8_t *data;

    int elem_size;
    uint8_t num_elems; // pow2


} qkl_lr_buff;


void qkl_lr_buff_init(qkl_lr_buff *buff, void *data, int data_size, int elem_size, int num_elems);

void qkl_lr_buff_left_put(qkl_lr_buff *buff);
void *qkl_lr_buff_left_get(qkl_lr_buff *buff);

void qkl_lr_buff_right_put(qkl_lr_buff *buff);
void *qkl_lr_buff_right_get(qkl_lr_buff *buff);





#ifdef __CPLUSPLUS
}
#endif