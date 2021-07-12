#include "qkl_server.h"
#include "qkl_decode.h"
#include "qkl_usr_platform.h"

#include <stdio.h>

static qkl_prod *log_prods[QKL_MAX_LOG_PROD];
static const char *prod_names[QKL_MAX_LOG_PROD];
static int num_log_prods = 0;



static qkl_usr_mutex mutex;
static qkl_usr_cond cycle_cond;

void qkl_init(){
    qkl_usr_mutex_init(&mutex);
    qkl_usr_cond_init(&cycle_cond);
}

void qkl_reg(qkl_prod *log_prod, const char*name){
    qkl_usr_mutex_lock(&mutex);
    QKL_ASSERT(num_log_prods < QKL_MAX_LOG_PROD);

    log_prods[num_log_prods] = log_prod;
    prod_names[num_log_prods] = name;

    num_log_prods++;
    qkl_usr_mutex_unlock(&mutex);
}

void qkl_unreg(qkl_prod *log_prod){
        // make sure any enqueued msgs are flushed
        qkl_usr_mutex_lock(&mutex);
        qkl_usr_cond_wait(&cycle_cond, &mutex);
        qkl_usr_mutex_unlock(&mutex);

        // dummy msg to make dropped msgs notifications go through
        qkl_prod_new_entry(log_prod, "", NULL, 0);


        qkl_usr_mutex_lock(&mutex);

        // wait for flush
        qkl_usr_cond_wait(&cycle_cond, &mutex);

        for(int i=0; i< num_log_prods; i++){
            if(log_prods[i] == log_prod){

                log_prods[i] = log_prods[num_log_prods-1];
                prod_names[i] = prod_names[num_log_prods-1];

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
            // skip dummy msgs
            if(ent->fmt[0] == '\0'){
                continue;
            }
            qkl_printf_decode(s, sizeof(s), ent->fmt, ent->data);
            qkl_lr_buff_right_put(&log_prods[i]->buff);

            char s2[128];
            ql_snprintf(s2, sizeof(s2), "[%s]: %s", prod_names[i], s);
            QKL_USR_LOG_OUT(s2);
        }
    }
    qkl_usr_cond_broadcast(&cycle_cond);
    qkl_usr_mutex_unlock(&mutex);
}



