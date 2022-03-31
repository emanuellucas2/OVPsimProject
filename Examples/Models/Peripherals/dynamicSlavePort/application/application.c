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
#define DYNAMICPSE(_off)  ((volatile unsigned int *) (0x10000000 + _off))


int main(int argc, char **argv) {

    printf("APP: Starting ..\n");

    // Read from peripheral dynamically based at 0x10000000
    printf("APP: Read Re-Map Reg 0x%08x\n", *DYNAMICPSE(0x000));


    // Write to peripheral remap register to dynamically based at 0x10000100
    printf("APP: Write Re-Map Reg : Move to 0x10000100\n");
    *DYNAMICPSE(0) = 0x10000100;

    // Read from peripheral dynamically based at 0x10000100
    printf("APP: Read Re-Map Reg 0x%08x\n", *DYNAMICPSE(0x100));


    // Read from original peripheral address 0x10000000 which should fail
    printf("APP: Attempt to access old mapping at 0x10000000 - expect failure\n");
    printf("APP: Read Re-Map Reg 0x%08x\n", *DYNAMICPSE(0x000));

    printf("APP: Complete ..\n");
    doDelay(100000);

    return 0;
}
