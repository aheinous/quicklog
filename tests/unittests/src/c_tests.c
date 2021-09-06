#include "c_tests.h"

#include <string.h>

#include "qkl/decode.h"
#include "qkl/encode.h"

#define C_CHECK(cond) \
	if(!(cond)) {     \
		return 0;     \
	}

static char buff[128] = {0};

static inline void decode_wrapper(int dummy, const char *fmt, uint8_t *bytes, int len) {
	(void)dummy;
	(void)len;
	qkl_printf_decode(buff, sizeof(buff), fmt, bytes);
}


// these are the same tests that are run in C++, but compiling them in C
// tests a different implementation.

int run_c_tests() {
	// TEST_CASE("string literal and const char*") {
	const char *s = "abc";
	QKL_PRINTF_ENCODE(decode_wrapper, 0, "fmt string %s %s", "abc", s);
	C_CHECK(strncmp(buff, "fmt string abc abc", sizeof(buff)) == 0);
	// }

	// TEST_CASE("signed int types") {
	QKL_PRINTF_ENCODE(
	    decode_wrapper, 0, "fmt string %c %d %d %ld %lld", (char)'a', (short)23, 24, -3453534L, -43435ll);
	C_CHECK(strncmp(buff, "fmt string a 23 24 -3453534 -43435", sizeof(buff)) == 0);
	// }

	// TEST_CASE("unsigned char") {
	QKL_PRINTF_ENCODE(decode_wrapper, 0, "fmt string %c", (unsigned char)'a');
	C_CHECK(strncmp(buff, "fmt string a", sizeof(buff)) == 0);
	// }

	// TEST_CASE("unsigned int types") {
	QKL_PRINTF_ENCODE(
	    decode_wrapper, 0, "fmt string %u %lu %llu", 1234567890, 1234567890lu, 12345678901234567890llu);
	C_CHECK(strncmp(buff, "fmt string 1234567890 1234567890 12345678901234567890", sizeof(buff)) == 0);
	// }

	// TEST_CASE("double") {
	QKL_PRINTF_ENCODE(decode_wrapper, 0, "fmt string %g", 123.456);
	C_CHECK(strncmp(buff, "fmt string 123.456", sizeof(buff)) == 0);
	// }

	// TEST_CASE("float") {
	QKL_PRINTF_ENCODE(decode_wrapper, 0, "fmt string %f", 123.456f);
	C_CHECK(strncmp(buff, "fmt string 123.456001", sizeof(buff)) == 0);
	// }

	return 1;
}