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

#include "sharedData.h"

#define TIMEOUT 100000

//
// Wait until the next frame is ready
//
void waitForFrame(int findex) {

    int idleCount = 0;

    while(findex == *ENCRYPT_INDEX) {
        if (idleCount++ >= TIMEOUT) {
            printf ("Timeout waiting for frame %d\n", findex);
            exit(-1);
        }
    }
}

//
// Main routine
//
int main(int argc, char **argv) {

    bufferP buffer = SHARED_BLOCK;
    int     findex = 0;
    int     ch     = -1;
    char    writeBuf[FRAME_SIZE+1];

    // seed random number generator
    srand(RAND_SEED);

    // write each decrypted frame as it is ready until entire message is sent
    while(ch && (findex<NUM_FRAMES)) {

        int i;

        // spin until encrypted frame is prepared
        waitForFrame(findex);

        // decrypt each character in the frame
        for(i=0; (i<FRAME_SIZE) && ch; i++) {
            ch = writeBuf[i] = (buffer->frame[findex][i] ^ rand());
        }

        // terminate the string to write
        writeBuf[i] = 0;

        // write output
        printf("\n**** FRAME %i ****\n\n", findex);
        puts(writeBuf);
        fflush(0);

        // step to next frame
        findex++;
    }

    return 0;
}
