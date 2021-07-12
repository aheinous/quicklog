#include "qkl_prod.h"
#include "qkl_usr_platform.h"
#include "qkl_encode.h"

// void qkl_lr_buff_init(qkl_lr_buff *buff, void *data, int data_size, int elem_size, int num_elems);

void qkl_prod_init(qkl_prod *log_prod, void *data, int data_size, int num_elems){
    QKL_ASSERT(num_elems * sizeof(qkl_entry) == data_size);
    qkl_lr_buff_init(&log_prod->buff, data, data_size, sizeof(qkl_entry), num_elems);
    log_prod->dropped = 0;
}




void qkl_prod_new_entry(qkl_prod *log_prod, const char *fmt, uint8_t *data, int len){

    if(log_prod->dropped && qkl_lr_buff_left_avail(&log_prod->buff)){
        int dropped = log_prod->dropped;
        log_prod->dropped = 0;
        QKL_PRINTF_ENCODE(qkl_prod_new_entry, log_prod,
            "<%d msg%s dropped>\n", dropped, dropped==1? "":"s");
    }


    qkl_entry *ent = (qkl_entry *) qkl_lr_buff_left_get(&log_prod->buff);
    if(!ent){
        log_prod->dropped++;
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
