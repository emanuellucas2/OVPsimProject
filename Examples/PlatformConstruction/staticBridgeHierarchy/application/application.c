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

#define MEMBASE 0x10000000
#define TEST    0x125534aa

int main(int argc, char **argv) {

    unsigned int mem;

    printf("\nApplication Starting\n");

    printf("Access memory through bridge at 0x%08x, using test data 0x%08x\n", MEMBASE, TEST);

    mem = *(unsigned int *) MEMBASE;

    printf("read 0x%08x\n", mem);

    printf("write 0x%08x\n", TEST);

    *(unsigned int *) MEMBASE = TEST;

    mem = *(unsigned int *) MEMBASE;

    printf("read 0x%08x\n", mem);

    return 0;
}

