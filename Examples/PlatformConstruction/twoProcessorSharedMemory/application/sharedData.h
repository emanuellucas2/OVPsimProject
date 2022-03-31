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

#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include "shared.h"

// define 32 frames of 1024 characters each
#define NUM_FRAMES 32
#define FRAME_SIZE 1024

typedef struct bufferS {
    char frame[NUM_FRAMES][FRAME_SIZE];
} buffer, *bufferP;

// index numbers of frame being encrypted
#define ENCRYPT_INDEX   ((volatile int *)(SHARED_LOW+0))

// address of data block
#define SHARED_BLOCK    ((bufferP)(SHARED_LOW+0x1000))

// seed used for random number generation
#define RAND_SEED 0x12345678

#endif
