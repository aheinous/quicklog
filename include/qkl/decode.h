#pragma once


#if defined(QKL_INCLUDE_TESTS) && defined(__cplusplus)
	#include "doctest/doctest.h"
#endif


#ifdef __cplusplus
extern "C" {
#endif

#include "qkl/config.h"
#include "qkl/platform.h"

int qkl_snprintf(char *str, size_t size, const char *format, ...);
int qkl_vsnprintf(char *str, size_t size, const char *format, va_list arg);


int qkl_printf_decode(char *str, size_t size, const char *format, uint8_t *bytes);

#ifdef __cplusplus
}
#endif


#if defined(QKL_INCLUDE_TESTS) && defined(__cplusplus)
	#include "qkl/encode.h"

TEST_SUITE("encode/decode") {
	static char buff[128] = {0};

	static inline void decode_wrapper(int dummy, const char *fmt, uint8_t *bytes, int len) {
		(void)dummy;
		(void)len;
		qkl_printf_decode(buff, sizeof(buff), fmt, bytes);
	}

	TEST_CASE("string literal and const char*") {
		const char *s = "abc";
		QKL_PRINTF_ENCODE(decode_wrapper, 0, "fmt string %s %s", "abc", s);
		CHECK(strncmp(buff, "fmt string abc abc", sizeof(buff)) == 0);
	}

	TEST_CASE("signed int types") {
		QKL_PRINTF_ENCODE(
		    decode_wrapper, 0, "fmt string %c %d %d %ld %lld", (char)'a', (short)23, 24, -3453534L, -43435ll);
		CHECK(strncmp(buff, "fmt string a 23 24 -3453534 -43435", sizeof(buff)) == 0);
	}

	TEST_CASE("unsigned char") {
		QKL_PRINTF_ENCODE(decode_wrapper, 0, "fmt string %c", (unsigned char)'a');
		CHECK(strncmp(buff, "fmt string a", sizeof(buff)) == 0);
	}

	TEST_CASE("unsigned int types") {
		QKL_PRINTF_ENCODE(
		    decode_wrapper, 0, "fmt string %u %lu %llu", 1234567890, 1234567890lu, 12345678901234567890llu);
		CHECK(strncmp(buff, "fmt string 1234567890 1234567890 12345678901234567890", sizeof(buff)) == 0);
	}

	TEST_CASE("double") {
		QKL_PRINTF_ENCODE(decode_wrapper, 0, "fmt string %g", 123.456);
		CHECK(strncmp(buff, "fmt string 123.456", sizeof(buff)) == 0);
	}

	TEST_CASE("float") {
		QKL_PRINTF_ENCODE(decode_wrapper, 0, "fmt string %f", 123.456f);
		CHECK(strncmp(buff, "fmt string 123.456001", sizeof(buff)) == 0);
	}
}

#endif
