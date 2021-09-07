
// compile these headers in C++ to enable unittests

#include <qkl/decode.h>
#include <qkl/encode.h>
#include <qkl/lr_buff.h>
#include <qkl/sem.h>
#include <qkl/server.h>


// run tests written in C

#include "c_tests.h"
#include <doctest/doctest.h>


TEST_CASE("C tests") {
	CHECK(run_c_tests());
}