#include "qkl_server.h"
#include "qkl_decode.h"
#include "qkl_usr_platform.h"

#include <stdio.h>

qkl_prod *log_prods[QKL_MAX_LOG_PROD];
int num_log_prods = 0;



qkl_usr_mutex mutex;
qkl_usr_cond cycle_cond;

void qkl_init(){
    qkl_usr_mutex_init(&mutex);
    qkl_usr_cond_init(&cycle_cond);
}

void qkl_reg(qkl_prod *log_prod){
    qkl_usr_mutex_lock(&mutex);
    QKL_ASSERT(num_log_prods < QKL_MAX_LOG_PROD);
    log_prods[num_log_prods] = log_prod;
    num_log_prods++;
    qkl_usr_mutex_unlock(&mutex);
}

void qkl_unreg(qkl_prod *log_prod){
        qkl_usr_mutex_lock(&mutex);

        // wait for flush
        qkl_usr_cond_wait(&cycle_cond, &mutex);

        for(int i=0; i< num_log_prods; i++){
            if(log_prods[i] == log_prod){
                log_prods[i] = log_prods[num_log_prods-1];
                num_log_prods --;
                goto success;
            }
        }
        QKL_ASSERT(0);

    success:
        qkl_usr_mutex_unlock(&mutex);
}



void qkl_process(){
    qkl_usr_mutex_lock(&mutex);

    for(int i=0; i< num_log_prods; i++){
        while(1){
            qkl_entry *ent = (qkl_entry*) qkl_lr_buff_right_get(&log_prods[i]->buff);
            if(!ent){
                break;
            }
            char s[128];
            qkl_printf_decode(s, sizeof(s), ent->fmt, ent->data);

            printf("[log entry]: %s", s);

            qkl_lr_buff_right_put(&log_prods[i]->buff);
        }
    }
    qkl_usr_cond_broadcast(&cycle_cond);
    qkl_usr_mutex_unlock(&mutex);
}

