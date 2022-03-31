// Custom instruction test for Chacha20
#include <stdio.h>

unsigned int processWord(unsigned int input, unsigned int word){
    unsigned int res = input;
    asm __volatile__("mv x10, %0" :: "r"(res));
    asm __volatile__("mv x11, %0" :: "r"(word));
    asm __volatile__(".word 0x00B5050B\n" ::: "x10");     // QR1
    asm __volatile__(".word 0x00B5150B\n" ::: "x10");     // QR2
    asm __volatile__(".word 0x00B5250B\n" ::: "x10");     // QR3
    asm __volatile__(".word 0x00B5350B\n" ::: "x10");     // QR4
    asm __volatile__(".word 0x00B5050B\n" ::: "x10");     // QR1
    asm __volatile__(".word 0x00B5150B\n" ::: "x10");     // QR2
    asm __volatile__(".word 0x00B5250B\n" ::: "x10");     // QR3
    asm __volatile__(".word 0x00B5350B\n" ::: "x10");     // QR4
    asm __volatile__("mv %0,x10" : "=r"(res));
    return res;
}
