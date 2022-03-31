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
#include <string.h>

#include "multicore2.h"

int munge(int mungeIn) {

    int result = 0;
    int i;

    for(i=0; i<mungeIn; i++) {
        result += i;
    }
    return result;
}

int main(int argc, char **argv) {

    int done = 0;

    printf("CPU (reader): starting...\n");

    do {
        int mungeIn, mungeRes;

        while(!sharedMemP->flag) {}
        mungeIn  = sharedMemP->fibres;
        done     = (sharedMemP->flag==FINISH);
        mungeRes = munge(mungeIn);
        printf("CPU (reader): munge(%d) = %d\n", mungeIn, mungeRes);
        sharedMemP->flag    = DONE;
    } while(!done);

    printf("CPU (reader): finished\n");

    return 0;
}

