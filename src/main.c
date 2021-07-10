#include "qkl_encode.h"
#include "qkl_decode.h"
#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include <stdarg.h>






void byte_array_print(const char*fmt, uint8_t* bytes){
    char buff[128];
    qkl_printf_decode(buff, sizeof(buff), fmt, bytes);

    printf("buff: ```%s```\n", buff);
}



int main(int argc, char**argv){
    // float fl = 3.14159f;
    // QL_LOG1(argc, f);


    // long long unsigned llu = (long long unsigned) "sub string";

    // // QL_LOG("fmt string");
    // QL_LOG("fmt string %d", (unsigned long long)-1);

    const char * s = "abc";


    // int d = get_byte_n(0, (void *) &s, SIZE_OF(*(&s)));
    // printf("%d:\n", d);

    // d = get_byte_n(0, (void *) &("abc"), SIZE_OF(*(&"abc")));
    // printf("%d:\n", d);

    // QL_LOG("fmt string %s", "sub string");


    // QL_LOG("fmt string %c", 'b');
    // QL_LOG("fmt string %c", (char)'b');
    // // QL_LOG("fmt string %s", s);
    // // QL_LOG("fmt string %hd", (short)23);
    // QL_LOG("fmt string %s %s ", "abc", s);
    // // QL_LOG("fmt string %llu %llu",23, 24);


    // QL_LOG("fmt string %c %d %d, %ld %lld", (char)'a', (short)23, 24, -3453534L, -43435ll);
    // QL_LOG("fmt string %u , %lu %llu", 1234567890, 1234567890, 12345678901234567890llu);
    // QL_LOG("fmt string %g", 123.456);
    // QL_LOG("fmt string %f", 123.456f);

    // QL_LOG("fmt string %f %c",23.154, 'a');

    // typeof(42) a1 = 42;






    // uint8_t b = GET_BYTE_N(0,fl);

    // printf("%s\n", _Generic(f, float:"float", default:"other"));


}


void takes_byte_array(uint8_t *p){

}

float get_float(){
    return 3.2f;
}