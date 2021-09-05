
// compile these headers in C++ to enable unittests

#include <qkl/sem.h>
#include <qkl/encode.h>
#include <qkl/decode.h>
#include <qkl/lr_buff.h>
#include <qkl/server.h>


// run tests written in C


#include <doctest/doctest.h>

#include "c_tests.h"


TEST_CASE("C tests"){
    CHECK(run_c_tests());
}