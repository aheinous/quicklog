#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include "qkl/sem.h"


typedef struct {
    qkl_sem_t left_avail;
    qkl_sem_t right_avail;

    qkl_atomic_index_t left_idx;
    qkl_atomic_index_t right_idx;

    uint8_t *data;

    int elem_size;
    size_t num_elems; // pow2


} qkl_lr_buff;


void qkl_lr_buff_init(qkl_lr_buff *buff, void *data, int data_size, int elem_size, int num_elems);

void qkl_lr_buff_left_put(qkl_lr_buff *buff);
void *qkl_lr_buff_left_get(qkl_lr_buff *buff);
int qkl_lr_buff_left_avail(qkl_lr_buff *buff);


void qkl_lr_buff_right_put(qkl_lr_buff *buff);
void *qkl_lr_buff_right_get(qkl_lr_buff *buff);
int qkl_lr_buff_right_avail(qkl_lr_buff *buff);





#ifdef __cplusplus
}
#endif


#if defined(QKL_INCLUDE_TESTS) && defined(__cplusplus)

    #include <pthread.h>
    #include <sched.h>

    #define NUM_ELMS 4


    TEST_SUITE("lr_buff"){

        TEST_CASE("basic") {
            char buff_data[sizeof(int) * NUM_ELMS];
            qkl_lr_buff lr_buff;

            qkl_lr_buff_init(&lr_buff, buff_data, sizeof(buff_data), sizeof(int), NUM_ELMS);

            SUBCASE("no right available after init"){
                CHECK(qkl_lr_buff_right_get(&lr_buff) == nullptr);
            }


            SUBCASE("left available after init"){
                int *pint = (int *) qkl_lr_buff_left_get(&lr_buff);
                CHECK(pint);
            }
            SUBCASE("left put then right get"){
                int *pint = (int *) qkl_lr_buff_left_get(&lr_buff);
                *pint = 5;
                qkl_lr_buff_left_put(&lr_buff);
                int *rpint = (int *) qkl_lr_buff_right_get(&lr_buff);
                CHECK(rpint);
                CHECK(*rpint == 5);

            }
            // qkl_lr_buff_right_put(&lr_buff);

            SUBCASE("multiple puts/gets"){

                for(int i = 1; i <= NUM_ELMS; i++) {
                    int *pint = (int *) qkl_lr_buff_left_get(&lr_buff);
                    *pint = i;
                    qkl_lr_buff_left_put(&lr_buff);
                }
                SUBCASE("left get gives null after getting NUM_ELEMS"){
                    CHECK( qkl_lr_buff_left_get(&lr_buff) == nullptr);
                }

                SUBCASE("NUM_ELEMS items recv'd properly"){
                    for(int i = 1; i <= NUM_ELMS; i++) {
                        int *pint = (int *) qkl_lr_buff_right_get(&lr_buff);
                        CHECK(i == *pint);
                        qkl_lr_buff_right_put(&lr_buff);
                    }
                }
            }
        }




        static void *left_process(void *a) {
            qkl_lr_buff * lr_buff = (qkl_lr_buff *) a;
            for(int i = 0; i < 1000; i++) {
                int done = 0;
                while(!done) {
                    int *pint = (int *) qkl_lr_buff_left_get(lr_buff);
                    if(!pint) {
                        sched_yield();
                        continue;
                    }

                    *pint = i;
                    qkl_lr_buff_left_put(lr_buff);
                    done = 1;

                }

            }
            return NULL;
        }

        static void *right_process(void *a) {
            qkl_lr_buff * lr_buff = (qkl_lr_buff *) a;
            for(int i = 0; i < 1000; i++) {

                int *pint = NULL;

                while(pint == NULL) {
                    pint = (int*) qkl_lr_buff_right_get(lr_buff);
                    if(!pint) {
                        sched_yield();
                    }
                }

                // printf("recvd: %d? %d\n", i, *pint);
                CHECK(i == *pint);
                qkl_lr_buff_right_put(lr_buff);
            }
            return NULL;
        }


        TEST_CASE("producer thread and consumer thread"){

            char buff_data[sizeof(int) * NUM_ELMS];
            qkl_lr_buff lr_buff;
            qkl_lr_buff_init(&lr_buff, buff_data, sizeof(buff_data), sizeof(int), NUM_ELMS);

            pthread_t left;
            pthread_t right;

            pthread_create(&left, NULL, left_process, &lr_buff);
            pthread_create(&right, NULL, right_process, &lr_buff);

            pthread_join(left, NULL);
            pthread_join(right, NULL);
        }
    }
#endif