#pragma once
#ifdef __cplusplus
extern "C" {
#endif

#include <qkl_usr_config.h>

#define QKL_ASSERT(cond, ...) do{												\
	if(!(cond)){															\
		qkl_on_failed_assert( #cond, __FILE__, __LINE__, "" __VA_ARGS__);  		\
	}																		\
} while(0)


#ifndef __cplusplus
typedef volatile _Atomic qkl_index_t qkl_atomic_index_t;
#else
extern "C++" {
    #include <atomic>
    typedef volatile std::atomic<qkl_index_t> qkl_atomic_index_t;
}
#endif




#ifdef __cplusplus
}
#endif