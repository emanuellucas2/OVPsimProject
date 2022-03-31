// Custom instruction test for Chacha20
#include <stdio.h>

// include test data array
#include "data.h"

// forward declaration
unsigned int processWord(unsigned int res, unsigned int word);

unsigned int processData(unsigned int res){
    unsigned int iter=0;
    while (iter++ < 2999) {
        int i;
        for (i=0;i<DATASIZE;i++) {
            res = processWord(res, testData[i]);
        }
    }
    return res;
}

int main(void) {
    unsigned int res = 0x84772366;
    res = processData(res);
    printf("RES = %08X\n", res);

    return 0;
}
