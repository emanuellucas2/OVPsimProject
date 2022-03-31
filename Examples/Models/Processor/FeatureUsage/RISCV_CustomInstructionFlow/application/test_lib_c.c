// Custom instruction test for Chacha20
#include <stdio.h>

#define NOINLINE  __attribute__((noinline))

static int qrN_c(unsigned int a, unsigned int b, unsigned int rotl) {
    return ((a ^ b) << rotl) | ((a ^ b) >> (32-rotl));
}

NOINLINE int qr1_c(unsigned int a, unsigned int b) {
    return qrN_c(a, b, 16);
}

NOINLINE int qr2_c(unsigned int a, unsigned int b) {
    return qrN_c(a, b, 12);
}

NOINLINE int qr3_c(unsigned int a, unsigned int b) {
    return qrN_c(a, b, 8);
}

NOINLINE int qr4_c(unsigned int a, unsigned int b) {
    return qrN_c(a, b, 7);
}

NOINLINE unsigned int processWord(unsigned int res, unsigned int word){
    res = qr1_c(res, word);
    res = qr2_c(res, word);
    res = qr3_c(res, word);
    res = qr4_c(res, word);
    res = qr1_c(res, word);
    res = qr2_c(res, word);
    res = qr3_c(res, word);
    res = qr4_c(res, word);
    return res;
}
