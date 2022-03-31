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

#define ITERATIONS 34

// address of the peripheral register
#define RESETPERIPHERAL  0xe0000000

#define DELAY 100000000
void delayLoop (int delay) {
    printf("CPU1: delay (%d)\n", delay);
    for (delay = DELAY; delay ; delay--) {
    }
}

int
main(int argc, char **argv)
{
    volatile int delay;
    printf("CPU1: starting...\n");

    delayLoop(1000000);

    printf("CPU1: release cpu2 reset\n");
    *(unsigned int *) RESETPERIPHERAL = 2;

    delayLoop(1000000);

    printf("CPU1: reset cpu2\n");
    *(unsigned int *) RESETPERIPHERAL = 2;
    *(unsigned int *) RESETPERIPHERAL = 2;

    delayLoop(1000000);

    printf("CPU1: finishing...\n");

    return 0;
}
