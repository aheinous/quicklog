#include "qkl_prod.h"
#include "qkl_usr_platform.h"

// void qkl_lr_buff_init(qkl_lr_buff *buff, void *data, int data_size, int elem_size, int num_elems);

void qkl_prod_init(qkl_prod *log_prod, void *data, int data_size, int num_elems){
    QKL_ASSERT(num_elems * sizeof(qkl_entry) == data_size);
    qkl_lr_buff_init(&log_prod->buff, data, data_size, sizeof(qkl_entry), num_elems);
}

void qkl_prod_new_entry(qkl_prod *log_prod, const char *fmt, uint8_t *data, int len){
    qkl_entry *ent = (qkl_entry *) qkl_lr_buff_left_get(&log_prod->buff);
    if(!ent){
        return;
    }
    ent->fmt = fmt;
    // memcpy(ent->data, data, len);

    for(int i=0; i<len; i++){
        uint8_t v = data[i];
        ent->data[i] = v;
    }
    qkl_lr_buff_left_put(&log_prod->buff);
}
