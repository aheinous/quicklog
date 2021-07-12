#include <time.h>
#include "qkl/qkl_encode.h"
#include "qkl/qkl_decode.h"
#include "qkl/qkl_usr_config.h"

#include "qkl/qkl_usr_platform.h"
#include "qkl/qkl_prod.h"
#include "qkl/qkl_server.h"
#include <pthread.h>
#include <sched.h>

#include "qkl/qkl_lr_buff.h"

#include <stdio.h>


#include <errno.h>

#include <stdlib.h>


#define countof(arr) (sizeof(arr) / sizeof(arr[0]))

// #ifndef __USE_POSIX199309

// #error
// #endif

int m_sleep(size_t msec){
    if(msec < 0){
        return -EINVAL;
    }
    struct timespec ts;
    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;
    return nanosleep(&ts, &ts);
}

void byte_array_print(int dummy,const char*fmt, uint8_t* bytes, int len){
    char buff[128];
    qkl_printf_decode(buff, sizeof(buff), fmt, bytes);

    printf("buff: ```%s```\n", buff);
}

void encode_decode_test(){

    const char * s = "abc";


    QKL_PRINTF_ENCODE(byte_array_print,0, "fmt string %s %s ", "abc", s);
    QKL_PRINTF_ENCODE(byte_array_print,0, "fmt string %c %d %d, %ld %lld", (char)'a', (short)23, 24, -3453534L, -43435ll);
    QKL_PRINTF_ENCODE(byte_array_print,0, "fmt string %u , %lu %llu", 1234567890, 1234567890, 12345678901234567890llu);
    QKL_PRINTF_ENCODE(byte_array_print,0, "fmt string %g", 123.456);
    QKL_PRINTF_ENCODE(byte_array_print,0, "fmt string %f", 123.456f);

}


pthread_t left;
pthread_t right;
qkl_lr_buff buff;

void * left_process(void*a){
    for(int i=0; i<1000; i++){
        int done = 0;
        while(! done){
            int *pint = (int *) qkl_lr_buff_left_get(&buff);
            if(!pint){
                sched_yield();
                continue;
            }

            *pint = i;
            qkl_lr_buff_left_put(&buff);
            done = 1;

        }

    }
}

void * right_process(void*a){
    for(int i=0; i<1000; i++){

        int * pint = NULL;

        while(pint == NULL){
            pint = qkl_lr_buff_right_get(&buff);
            if(!pint){
                sched_yield();
            }
        }

        printf("recvd: %d? %d\n", i, *pint);
        qkl_lr_buff_right_put(&buff);
    }

}

#define NUM_ELMS 4

char buff_data[sizeof(int) * NUM_ELMS];

void ringbuff_test(){
    qkl_lr_buff_init(&buff,buff_data, sizeof(buff_data), sizeof(int), NUM_ELMS);


    printf("null? %p\n", qkl_lr_buff_right_get(&buff));
    int* pint = (int*) qkl_lr_buff_left_get(&buff);
    printf("not null? %p\n", pint);
    *pint = 5;
    qkl_lr_buff_left_put(&buff);
    int* rpint = (int*) qkl_lr_buff_right_get(&buff);
    printf("not null? 5? %p %d\n", rpint, *rpint);
    printf("null? %p\n", qkl_lr_buff_right_get(&buff));
    qkl_lr_buff_right_put(&buff);

    for(int i = 1; i<= NUM_ELMS; i++){
        pint = (int *) qkl_lr_buff_left_get(&buff);
        *pint = i;
        qkl_lr_buff_left_put(&buff);
    }
    printf(".null? %p\n", qkl_lr_buff_left_get(&buff));
    for(int i = 1; i<= NUM_ELMS; i++){
        pint = (int *) qkl_lr_buff_right_get(&buff);
        printf("%d? %d\n", i, *pint);
        qkl_lr_buff_right_put(&buff);
    }




    pthread_create(&left, NULL, left_process, NULL);
    pthread_create(&right, NULL, right_process, NULL);

    pthread_join(left, NULL);
    pthread_join(right, NULL);
}


pthread_t thd_a;
pthread_t thd_b;
pthread_t server;

qkl_prod prod_a;
qkl_prod prod_b;




void * prod_process(void *arg){
    qkl_prod *prod = (qkl_prod*) arg;

    const int ent_count = 32;

    void * data = malloc(sizeof(qkl_entry) * ent_count);

    qkl_prod_init(prod,data, sizeof(qkl_entry)*ent_count, ent_count);

    qkl_reg(prod, "");

    for(int i =0; i<100; i++){
        QKLOG(*prod, "prod_process: %s, %d\n", prod==&prod_a ? "A" : "\tB", i);
        if(i%10 == 0){
            m_sleep(i/1);
        }
    }
    qkl_unreg(prod);

    free(data);
    return NULL;
}

void* server_process(void*args){
    while(1){
        qkl_process();
        m_sleep(50);
    }
    return NULL;
}

void integ_test(){

    qkl_init();

    // char buff[4 * sizeof(qkl_entry)];
    // qkl_prod prod;
    // qkl_prod_init(&prod, buff, sizeof(buff), 4);
    // qkl_reg(&prod, "");

    QKL_PROD(prod, "first prod", 4);

    qkl_process();

    const char*s = "abc";


    qkl_process();
    QKLOG(prod, "fmt string %s %s \n", "abc", s);
    QKLOG(prod, "fmt string %c %d %d, %ld %lld\n", (char) 'a', (short) 23, 24, -3453534L, -43435ll);
    QKLOG(prod, "fmt string %u , %lu %llu\n", 1234567890, 1234567890, 12345678901234567890llu);
    QKLOG(prod, "fmt string %g\n", 123.456);
    QKLOG(prod, "fmt string %f\n", 123.456f);
    qkl_process();
    QKLOG(prod, "fmt string %s %s \n", "abc", s);
    QKLOG(prod, "fmt string %c %d %d, %ld %lld\n", (char) 'a', (short) 23, 24, -3453534L, -43435ll);
    QKLOG(prod, "fmt string %u , %lu %llu\n", 1234567890, 1234567890, 12345678901234567890llu);
    QKLOG(prod, "fmt string %g\n", 123.456);
    QKLOG(prod, "fmt string %f\n", 123.456f);
    QKLOG(prod, "fmt string %f\n", 123.456f);
    QKLOG(prod, "fmt string %f\n", 123.456f);
    QKLOG(prod, "fmt string %f\n", 123.456f);
    qkl_process();
    QKLOG(prod, "fmt string %f\n", 123.456f);
    qkl_process();

    pthread_create(&thd_a, NULL, prod_process, &prod_a);
    pthread_create(&thd_b, NULL, prod_process, &prod_b);
    pthread_create(&server, NULL, server_process, NULL);


    pthread_join(thd_a, NULL);
    pthread_join(thd_b, NULL);

    qkl_unreg(&prod);

    // reg/unreg


    const char *spell[] = {"zero", "one", "two", "three"};
    #define  buff_cnt  16
    #define n_prods 4
    {
        qkl_prod prods[n_prods];
        char buff[n_prods][buff_cnt * sizeof(qkl_entry)];
        for(int i=0; i<n_prods; i++){
            qkl_prod_init(&prods[i], buff[i], sizeof(buff[0]), buff_cnt);
            qkl_reg(&prods[i], spell[i]);


        }
        for(int i=0; i<2; i++){
            qkl_unreg(&prods[i]);
        }
        for(int i=2; i<n_prods; i++){
            for(int j = 0; j < 50; j++) {
                QKLOG(prods[i], "reg unreg %d %d\n", i, j);
            }
        }
        for(int i=2; i<n_prods; i++){
            qkl_unreg(&prods[i]);
        }
    }
}

int main(int argc, char**argv){

    ringbuff_test();
    integ_test();


}


