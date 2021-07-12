#include "qkl/qkl_lr_buff.h"
#include "qkl/qkl_usr_platform.h"
#include "qkl/qkl_usr_config.h"


void qkl_lr_buff_init(qkl_lr_buff *buff, void *data, int data_size, int elem_size, int num_elems){
    qkl_sem_init(&buff->left_avail);
    qkl_sem_init(&buff->right_avail);

    QKL_ASSERT(! (num_elems & (num_elems-1) ) ); // pow2
    QKL_ASSERT(num_elems * elem_size == data_size);

    buff->data = data;
    buff->num_elems = num_elems;
    buff->elem_size = elem_size;

    buff->left_idx = 0;
    buff->right_idx = 0;

    for(int i=0; i<num_elems; i++){
        qkl_sem_put(&buff->left_avail);
    }
}


void qkl_lr_buff_left_put(qkl_lr_buff *buff){
    buff->left_idx = (buff->left_idx+1) & (buff->num_elems-1);
    qkl_sem_put(&buff->right_avail);
}

void *qkl_lr_buff_left_get(qkl_lr_buff *buff){
    if(qkl_sem_peek(&buff->left_avail) == 0){
        return NULL;
    }
    qkl_sem_get(&buff->left_avail);
    return (void*) &(buff->data[ buff->left_idx * buff->elem_size ]);
}


int qkl_lr_buff_left_avail(qkl_lr_buff *buff){
    return qkl_sem_peek(&buff->left_avail);
}




void qkl_lr_buff_right_put(qkl_lr_buff *buff) {
    buff->right_idx = (buff->right_idx + 1) & (buff->num_elems - 1);
    qkl_sem_put(&buff->left_avail);
}

void *qkl_lr_buff_right_get(qkl_lr_buff *buff) {
    if(qkl_sem_peek(&buff->right_avail) == 0) {
        return NULL;
    }
    qkl_sem_get(&buff->right_avail);
    return (void *) &(buff->data[buff->right_idx * buff->elem_size]);
}

int qkl_lr_buff_right_avail(qkl_lr_buff *buff){
    return qkl_sem_peek(&buff->right_avail);
}







// void qkl_lr_buff_right_put(qkl_lr_buff *buff){

// }

// void *qkl_lr_buff_right_get(qkl_lr_buff *buff){

// }

