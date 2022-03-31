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

//
// Main routine
//
int main(int argc, char **argv) {

    bufferP      buffer   = SHARED_BLOCK;
    const char  *fileName = argc < 2 ? "constitution.txt" : argv[1];
    FILE        *file     = fopen(fileName, "r");
    int          findex   = 0;
    int          done     = 0;
    size_t       num;

    // seed random number generator
    srand(RAND_SEED);

    // check file can be opened
    if(!file) {
        printf("Unable to open file %s for read\n", fileName);
        return -1;
    }

    // handle each frame of data
    while(!done && (findex<NUM_FRAMES)) {

        int i;

        // read next frame of data from input file
        num = fread(&buffer->frame[findex], 1, FRAME_SIZE, file);

        // identify the last frame being sent
        // note: this assumes input data does not include a 0 (e.g. text file)
        if(num!=FRAME_SIZE) {
            buffer->frame[findex][num] = 0;
            done = 1;
        }

        // encrypt each character in the frame
        for(i=0; i<FRAME_SIZE; i++) {
            buffer->frame[findex][i] ^= rand();
        }

        // step to the next frame
        *ENCRYPT_INDEX = ++findex;
    }

    return 0;
}
