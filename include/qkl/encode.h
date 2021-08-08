
#pragma once

#include "qkl/usr/platform.h"
#include "qkl/usr/config.h"


#if  defined(QKL_INCLUDE_TESTS) && defined(__cplusplus)
    #include "doctest.h"
#endif



typedef long long unsigned ql_llu;

#define QKL_FIRST_ARG(...) _QKL_FIRST_ARG(__VA_ARGS__, dummy)
#define _QKL_FIRST_ARG( a1, ...) a1


#define QKL_MK_VARG_FUNC(fn,...) QKL_MK_VARG_FUNC_N(fn,##__VA_ARGS__,9,8,7,6,5,4,3,2,1,0)(__VA_ARGS__)
#define QKL_MK_VARG_FUNC_N(fn,n0,n1,n2,n3,n4,n5,n6,n7,n8,n,...) fn##n

#define QKL_TO_BYTE_REP(...) QKL_MK_VARG_FUNC(QKL_TO_BYTE_REP, ##__VA_ARGS__)
#define QKL_MAKE_TMPS(...) QKL_MK_VARG_FUNC(QKL_MAKE_TMPS, ##__VA_ARGS__)



#ifdef __cplusplus
    #define QKL_TYPEOF decltype
#else
    #define QKL_TYPEOF __typeof__
#endif

#define QKL_MAKE_TMPS1(fmt)
#define QKL_MAKE_TMPS2(fmt, a1) QKL_TYPEOF(a1) t1 = (a1);
#define QKL_MAKE_TMPS3(fmt, a1, a2) QKL_TYPEOF(a1) t1 = (a1); QKL_TYPEOF(a2) t2 = (a2);
#define QKL_MAKE_TMPS4(fmt, a1, a2, a3) QKL_TYPEOF(a1) t1 = (a1); QKL_TYPEOF(a2) t2 = (a2); QKL_TYPEOF(a3) t3 = (a3);
#define QKL_MAKE_TMPS5(fmt, a1, a2, a3, a4) QKL_TYPEOF(a1) t1 = (a1); QKL_TYPEOF(a2) t2 = (a2); QKL_TYPEOF(a3) t3 = (a3); QKL_TYPEOF(a4) t4 = (a4);
#define QKL_MAKE_TMPS6(fmt, a1, a2, a3, a4, a5) QKL_TYPEOF(a1) t1 = (a1); QKL_TYPEOF(a2) t2 = (a2); QKL_TYPEOF(a3) t3 = (a3); QKL_TYPEOF(a4) t4 = (a4); QKL_TYPEOF(a5) t5 = (a5);
#define QKL_MAKE_TMPS7(fmt, a1, a2, a3, a4, a5, a6) QKL_TYPEOF(a1) t1 = (a1); QKL_TYPEOF(a2) t2 = (a2); QKL_TYPEOF(a3) t3 = (a3); QKL_TYPEOF(a4) t4 = (a4); QKL_TYPEOF(a5) t5 = (a5); QKL_TYPEOF(a6) t6 = (a6);
#define QKL_MAKE_TMPS8(fmt, a1, a2, a3, a4, a5, a6, a7) QKL_TYPEOF(a1) t1 = (a1); QKL_TYPEOF(a2) t2 = (a2); QKL_TYPEOF(a3) t3 = (a3); QKL_TYPEOF(a4) t4 = (a4); QKL_TYPEOF(a5) t5 = (a5); QKL_TYPEOF(a6) t6 = (a6); QKL_TYPEOF(a7) t7 = (a7);
#define QKL_MAKE_TMPS9(fmt, a1, a2, a3, a4, a5, a6, a7, a8) QKL_TYPEOF(a1) t1 = (a1); QKL_TYPEOF(a2) t2 = (a2); QKL_TYPEOF(a3) t3 = (a3); QKL_TYPEOF(a4) t4 = (a4); QKL_TYPEOF(a5) t5 = (a5); QKL_TYPEOF(a6) t6 = (a6); QKL_TYPEOF(a7) t7 = (a7); QKL_TYPEOF(a8) t8 = (a8);


#define QKL_TO_BYTE_REP1(fmt)
#define QKL_TO_BYTE_REP2(fmt, ...) QKL_GET_BYTES(t1)
#define QKL_TO_BYTE_REP3(fmt, ...) QKL_GET_BYTES(t1), QKL_GET_BYTES(t2)
#define QKL_TO_BYTE_REP4(fmt, ...) QKL_GET_BYTES(t1), QKL_GET_BYTES(t2), QKL_GET_BYTES(t3)
#define QKL_TO_BYTE_REP5(fmt, ...) QKL_GET_BYTES(t1), QKL_GET_BYTES(t2), QKL_GET_BYTES(t3), QKL_GET_BYTES(t4)
#define QKL_TO_BYTE_REP6(fmt, ...) QKL_GET_BYTES(t1), QKL_GET_BYTES(t2), QKL_GET_BYTES(t3), QKL_GET_BYTES(t4), QKL_GET_BYTES(t5)
#define QKL_TO_BYTE_REP7(fmt, ...) QKL_GET_BYTES(t1), QKL_GET_BYTES(t2), QKL_GET_BYTES(t3), QKL_GET_BYTES(t4), QKL_GET_BYTES(t5), QKL_GET_BYTES(t6)
#define QKL_TO_BYTE_REP8(fmt, ...) QKL_GET_BYTES(t1), QKL_GET_BYTES(t2), QKL_GET_BYTES(t3), QKL_GET_BYTES(t4), QKL_GET_BYTES(t5), QKL_GET_BYTES(t6), QKL_GET_BYTES(t7)
#define QKL_TO_BYTE_REP9(fmt, ...) QKL_GET_BYTES(t1), QKL_GET_BYTES(t2), QKL_GET_BYTES(t3), QKL_GET_BYTES(t4), QKL_GET_BYTES(t5), QKL_GET_BYTES(t6), QKL_GET_BYTES(t7), QKL_GET_BYTES(t8)

#define QKL_GET_BYTES(v) QKL_GET_BYTE_N(0, v),QKL_GET_BYTE_N(1, v),QKL_GET_BYTE_N(2, v),QKL_GET_BYTE_N(3, v),QKL_GET_BYTE_N(4, v),QKL_GET_BYTE_N(5, v),QKL_GET_BYTE_N(6, v),QKL_GET_BYTE_N(7, v)


#if defined(QKL_INCLUDE_TESTS) && defined(__cplusplus)
TEST_CASE("QKL_MAKE_TMPS macro") {
    QKL_MAKE_TMPS("fmt" ,5, 10);
    CHECK(t1 == 5);
    CHECK(t2 == 10);
}
#endif

#define QKL_IS_ARRAY(arg) ((((void *) &arg) == ((void *) (uintptr_t)arg)))

#if defined(QKL_INCLUDE_TESTS) && defined(__cplusplus)
TEST_CASE("QKL_IS_ARRAY") {
    CHECK(QKL_IS_ARRAY("abc"));
    const char * pstr = "def";
    CHECK(!QKL_IS_ARRAY(pstr));
}
#endif

#ifndef __cplusplus

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




    #define QKL_TYPE_ID(v) \
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
                    default:            QKL_IS_ARRAY(v) ? t_array : t_pointer            )


    #define QKL_GET_BYTE_N(n, v) qkl_get_byte_n(n, (void*)&v, QKL_TYPE_ID(v) )

    static inline uint8_t qkl_get_byte_n(int n, const void *v, int ql_type_id) ALWAYS_INLINE(); // Critical
    static inline uint8_t qkl_get_byte_n(int n, const void *v, int ql_type_id) {
        uint8_t buff[8] = {};
        const void *v2 = v;

        switch(ql_type_id) {
            case t_c:
            case t_sc:
            case t_uc: {
                char c = *((char *) v);
                *((ql_llu *) buff) = (ql_llu) c;
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
                v2 = (void *) &v;
                FALLTHROUGH();
            case t_pointer:
            {
                *((ql_llu *) buff) = *((ql_llu *) v2);
                v2 = buff;
                break;
            }
            default:
                QKL_ASSERT(0);


        }
    	return ((uint8_t *) v2)[n];
	}
#endif



#ifdef   __cplusplus
    extern "C++" {

        #define QKL_GET_BYTE_N(n, v) qkl_get_byte_n(n, v)

        template<typename T>
        static inline uint8_t qkl_get_byte_n(int n, T v) ALWAYS_INLINE();


        template<typename T>
        static inline uint8_t qkl_get_byte_n(int n, T v){
            uint8_t buff[8] = {0};
            *((T*)buff) = v;
            return buff[n];
        }


        template<>
        inline uint8_t qkl_get_byte_n<char>(int n, char v) {
            return qkl_get_byte_n<ql_llu>(n, v);
        }

        template<>
        inline uint8_t qkl_get_byte_n<short>(int n, short v) {
            return qkl_get_byte_n<ql_llu>(n, v);
        }

        template<>
        inline uint8_t qkl_get_byte_n<int>(int n, int v) {
            return qkl_get_byte_n<ql_llu>(n, v);
        }

        template<>
        inline uint8_t qkl_get_byte_n<long>(int n, long v) {
            return qkl_get_byte_n<ql_llu>(n, v);
        }



        template<>
        inline uint8_t qkl_get_byte_n<unsigned char>(int n, unsigned char v) {
            return qkl_get_byte_n<ql_llu>(n, v);
        }

        template<>
        inline uint8_t qkl_get_byte_n<unsigned short>(int n, unsigned short v) {
            return qkl_get_byte_n<ql_llu>(n, v);
        }

        template<>
        inline uint8_t qkl_get_byte_n<unsigned int>(int n, unsigned int v) {
            return qkl_get_byte_n<ql_llu>(n, v);
        }

        template<>
        inline uint8_t qkl_get_byte_n<unsigned long>(int n, unsigned long v) {
            return qkl_get_byte_n<ql_llu>(n, v);
        }

        template<>
        inline uint8_t qkl_get_byte_n<float>(int n, float v){
            uint8_t buff[8] = {0};
            *((double*)buff) = (double)v;
            return buff[n];
        }


    }
#endif








#define QKL_PRINTF_ENCODE(func, usr_data, ...) do {                               \
    QKL_MAKE_TMPS(__VA_ARGS__)    /*make tmps so we can use args as l-values */       \
    uint8_t byte_rep[] = {                                                        \
        QKL_TO_BYTE_REP(__VA_ARGS__)                                                  \
    };                                                                            \
    func( usr_data, QKL_FIRST_ARG(__VA_ARGS__), byte_rep, sizeof(byte_rep));          \
}while(0)


