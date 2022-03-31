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

#define ITERATIONS 36

static int
fib(int i)
{
    return (i > 1) ? fib(i - 1) + fib(i - 2) : i;
}

// The label of _start for creation of reset vector
extern _start;

int
main(int argc, char *argv[])
{

    // On first execution we wish to create code at the reset vector
    // to branch to _start
    // This code is for this example only and would normally
    // be part of application reset code.
    static int init = 0;
    if (!init) {
        // reset vector
        unsigned int *reset = (void *) 0x0;
        // branch instruction encoding
        unsigned int instr = 0xea000000;
        // _start symbol address
        unsigned int start = (unsigned int)(void*)&_start;
        // convert _start to imm24 instruction encoding
        start = ((start-8)>>2) & 0x00ffffff;
        // write reset vector
        *reset = (instr | start);
        init = 1;
    }

    int i, j;
    printf("starting...\n");

    for (j = 0; j < 10; j++) {

        for (i = 0; i < ITERATIONS; i++) {
            printf("fib(%d) = %d\n", i, fib(i));
        }

    }
    printf("finishing...\n");

    return 0;
}
