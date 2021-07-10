#pragma once



#ifdef __CPLUSPLUS
extern "C" {
#endif


#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

// int ql_snprintf(char *str, size_t size, const char *format, ...);
// int ql_vsnprintf(char *str, size_t size, const char *format, va_list arg);


int qkl_printf_decode(char *str, size_t size, const char *format, uint8_t *bytes);

#ifdef __CPLUSPLUS
}
#endif
