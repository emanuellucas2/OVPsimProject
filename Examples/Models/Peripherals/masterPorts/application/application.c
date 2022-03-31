/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */


#include <stdio.h>
#include <stdlib.h>

void doDelay(unsigned int delay) {
    while (delay--) {
         ;
    }
}

// byte addresses
#define SHARED_BASE   0x10000000
#define SHARED(_off)  ((volatile unsigned int *) (SHARED_BASE + _off))


int main(int argc, char **argv) {

    printf("APP: Starting ..\n");

    unsigned int data = 0;
    unsigned int count = 0;
    unsigned int iterations = 10000;
    while(!data && (iterations > 0)) {
        // Read from peripheral dynamically based at 0x10000000
        data=*SHARED(count);
        if(data) printf("APP: Read (%04d) 0x%08x:0x%08x\n", iterations, SHARED_BASE+count, data);
        iterations--;
        count+=4;
        if(count>0x10) count=0;

        doDelay(1000);
    }

    printf("APP: Complete ..\n");
    doDelay(100000);

    return 0;
}
