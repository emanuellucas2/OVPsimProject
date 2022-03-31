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

#define ITERATIONS 40

static int
fib(int i)
{
    return (i > 1) ? fib(i - 1) + fib(i - 2) : i;
}

// The label of start for creation of reset vector
extern start;

int
main(int argc, char **argv)
{

    // On first execution we wish to create code at the reset vector
    // to branch to start
    // This code is for this example only and would normally
    // be part of application reset code.
    static int init = 0;
    if (!init) {
        // reset vector
        unsigned int *reset = (void *) 0x0;
        // start symbol address
        unsigned int lstart = (unsigned int)(void*)&start;
        // convert start to imm16 instruction encoding
        lstart = ((lstart-8)>>2) & 0x00ffff;
        // write reset vector
        *(reset+ 0) = 0x9c400000;            // l.addi r2,r0,0x0
        *(reset+ 4) = (0x9f400000 | lstart); // load address to r2
        *(reset+ 8) = 0x44004000;            // l.jr r2
        *(reset+12) = 0x15000000;            // l.nop
        init = 1;
    }

    int i, j;
    printf("CPU1: starting...\n");
    for (j = 0; j < 4; j++) {

        for (i = 0; i < ITERATIONS; i++) {
            printf("CPU1: fib(%d) = %d\n", i, fib(i));
        }
    }
    printf("CPU1: finishing...\n");

    return 0;
}
