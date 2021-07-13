
#pragma once

#include "qkl/usr/platform.h"
#include "qkl/usr/config.h"


typedef long long unsigned ql_llu;

#define FIRST_ARG(...) _FIRST_ARG(__VA_ARGS__, dummy)
#define _FIRST_ARG( a1, ...) a1


#define MK_VARG_FUNC(fn,...) MK_VARG_FUNC_N(fn,##__VA_ARGS__,9,8,7,6,5,4,3,2,1,0)(__VA_ARGS__)
#define MK_VARG_FUNC_N(fn,n0,n1,n2,n3,n4,n5,n6,n7,n8,n,...) fn##n

#define TO_BYTE_REP(...) MK_VARG_FUNC(TO_BYTE_REP, ##__VA_ARGS__)
#define MAKE_TMPS(...) MK_VARG_FUNC(MAKE_TMPS, ##__VA_ARGS__)



#define TO_BYTE_REP1(fmt)
#define TO_BYTE_REP2(fmt, ...) GET_BYTES(t1)
#define TO_BYTE_REP3(fmt, ...) GET_BYTES(t1), GET_BYTES(t2)
#define TO_BYTE_REP4(fmt, ...) GET_BYTES(t1), GET_BYTES(t2), GET_BYTES(t3)
#define TO_BYTE_REP5(fmt, ...) GET_BYTES(t1), GET_BYTES(t2), GET_BYTES(t3), GET_BYTES(t4)
#define TO_BYTE_REP6(fmt, ...) GET_BYTES(t1), GET_BYTES(t2), GET_BYTES(t3), GET_BYTES(t4), GET_BYTES(t5)
#define TO_BYTE_REP7(fmt, ...) GET_BYTES(t1), GET_BYTES(t2), GET_BYTES(t3), GET_BYTES(t4), GET_BYTES(t5), GET_BYTES(t6)
#define TO_BYTE_REP8(fmt, ...) GET_BYTES(t1), GET_BYTES(t2), GET_BYTES(t3), GET_BYTES(t4), GET_BYTES(t5), GET_BYTES(t6), GET_BYTES(t7)
#define TO_BYTE_REP9(fmt, ...) GET_BYTES(t1), GET_BYTES(t2), GET_BYTES(t3), GET_BYTES(t4), GET_BYTES(t5), GET_BYTES(t6), GET_BYTES(t7), GET_BYTES(t8)


#define MAKE_TMPS1(fmt)
#define MAKE_TMPS2(fmt, a1) __typeof__(a1) t1 = (a1);
#define MAKE_TMPS3(fmt, a1, a2) __typeof__(a1) t1 = (a1); __typeof__(a2) t2 = (a2);
#define MAKE_TMPS4(fmt, a1, a2, a3) __typeof__(a1) t1 = (a1); __typeof__(a2) t2 = (a2); __typeof__(a3) t3 = (a3);
#define MAKE_TMPS5(fmt, a1, a2, a3, a4) __typeof__(a1) t1 = (a1); __typeof__(a2) t2 = (a2); __typeof__(a3) t3 = (a3); __typeof__(a4) t4 = (a4);
#define MAKE_TMPS6(fmt, a1, a2, a3, a4, a5) __typeof__(a1) t1 = (a1); __typeof__(a2) t2 = (a2); __typeof__(a3) t3 = (a3); __typeof__(a4) t4 = (a4); __typeof__(a5) t5 = (a5);
#define MAKE_TMPS7(fmt, a1, a2, a3, a4, a5, a6) __typeof__(a1) t1 = (a1); __typeof__(a2) t2 = (a2); __typeof__(a3) t3 = (a3); __typeof__(a4) t4 = (a4); __typeof__(a5) t5 = (a5); __typeof__(a6) t6 = (a6);
#define MAKE_TMPS8(fmt, a1, a2, a3, a4, a5, a6, a7) __typeof__(a1) t1 = (a1); __typeof__(a2) t2 = (a2); __typeof__(a3) t3 = (a3); __typeof__(a4) t4 = (a4); __typeof__(a5) t5 = (a5); __typeof__(a6) t6 = (a6); __typeof__(a7) t7 = (a7);
#define MAKE_TMPS9(fmt, a1, a2, a3, a4, a5, a6, a7, a8) __typeof__(a1) t1 = (a1); __typeof__(a2) t2 = (a2); __typeof__(a3) t3 = (a3); __typeof__(a4) t4 = (a4); __typeof__(a5) t5 = (a5); __typeof__(a6) t6 = (a6); __typeof__(a7) t7 = (a7); __typeof__(a8) t8 = (a8);



enum ql_type_id{
    t_c,
    t_sc,
    t_uc,
    t_sint,
    t_suint,
    t_int,
    t_uint,
    t_lint,
    t_luint,
    t_llint,
    t_lluint,
    t_float,
    t_double,
    t_ldouble,
    t_pointer,
    t_array,
};




#define SIZE_OF(v) \
    _Generic( v,            \
                signed char: sizeof(signed char),                   \
                unsigned char : sizeof( unsigned char ),            \
                short: sizeof( short),                                  \
                unsigned short : sizeof( unsigned short ),              \
                int: sizeof( int),                                  \
                unsigned int : sizeof( unsigned int ),               \
                long : sizeof( long ),                               \
                unsigned long : sizeof( unsigned long ),             \
                long long : sizeof( long long ),                     \
                unsigned long long : sizeof( unsigned long long ),   \
                float: sizeof( float),                               \
                double: sizeof( double),                             \
                long double: sizeof( long double),                   \
                default: sizeof(void*))



#define IS_ARRAY(arg) ((((void *) &arg) == ((void *) (long long unsigned)arg)))


#define TYPE_ID(v) \
    _Generic( v,            \
                char:        t_c,                      \
                signed char:        t_sc,                      \
                unsigned char :     t_uc,                    \
                short:              t_sint,        \
                unsigned short :    t_suint,                    \
                int:                t_int,        \
                unsigned int :      t_uint,                \
                long :              t_lint,        \
                unsigned long :     t_luint,                    \
                long long :         t_llint,                \
                unsigned long long :t_lluint,                        \
                float:              t_float,       \
                double:             t_double,           \
                long double:        t_ldouble,                \
                default:            IS_ARRAY(v) ? t_array : t_pointer            )




#define GET_BYTE_N(n, v) get_byte_n(n, (void*)&v, TYPE_ID(v) )

static inline uint8_t get_byte_n(int n, const void *v, int ql_type_id) __attribute__((always_inline)); // Critical
static inline uint8_t get_byte_n(int n, const void *v, int ql_type_id){
    uint8_t buff[8] = {};
    const void *v2 = v;

    switch(ql_type_id){
        case t_c:
        case t_sc:
        case t_uc:{
            char c = *((char*)v);
            *((ql_llu*)buff) = (ql_llu)c;
            v2 = buff;
            break;
        }
        case t_sint:
        case t_suint: {
            short c = *((short *) v);
            *((ql_llu *) buff) = (ql_llu) c;
            v2 = buff;
            break;
        }

        case t_int:
        case t_uint:
        {
            int c = *((int *) v);
            *((ql_llu *) buff) = (ql_llu) c;
            v2 = buff;
            break;
        }
        case t_lint:
        case t_luint:
        {
            long int c = *((long int *) v);
            *((ql_llu *) buff) = (ql_llu) c;
            v2 = buff;
            break;
        }

        case t_llint:
        case t_lluint:
        {
            long long int c = *((long long int *) v);
            *((ql_llu *) buff) = (ql_llu) c;
            v2 = buff;
            break;
        }

        case t_float:
        {
            float c = *((float *) v);
            *((double *) buff) = (double) c;
            v2 = buff;
            break;
        }
        case t_double:
        {
            double c = *((double *) v);
            *((double *) buff) = (double) c;
            v2 = buff;
            break;
        }
        case t_array:
            v2 = (void *)&v;
        case t_pointer:
        {
            *((ql_llu *) buff) = *((ql_llu*) v2);
            v2 = buff;
            break;
        }
        default:
            QKL_ASSERT(0);


    }

    return ((uint8_t*)v2 )[n];
}





#define GET_BYTES(v) GET_BYTE_N(0, v),GET_BYTE_N(1, v),GET_BYTE_N(2, v),GET_BYTE_N(3, v),GET_BYTE_N(4, v),GET_BYTE_N(5, v),GET_BYTE_N(6, v),GET_BYTE_N(7, v)





#define QKL_PRINTF_ENCODE(func, usr_data, ...) do {                               \
    MAKE_TMPS(__VA_ARGS__)                             \
    uint8_t byte_rep[] = {                             \
        TO_BYTE_REP(__VA_ARGS__)                       \
    };                                                 \
    func( usr_data, FIRST_ARG(__VA_ARGS__), byte_rep, sizeof(byte_rep)); \
    }while(0)



