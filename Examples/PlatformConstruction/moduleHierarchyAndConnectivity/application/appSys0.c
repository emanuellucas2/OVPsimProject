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

#include "common.h"

#define SYSTEM "Sys0"
#define SYSID  (1<<23)

int main(int argc, char **argv) {

    printf("%s: Application Started\n", SYSTEM);
    int j;
    for (j = 0 ; j < 10 ; j++ ) {

        int i = DELAY;
        while(i--) {
            // delay
        }
        unsigned int mbVal  = *LOCAL_MB;
        unsigned int mbxVal = *EXT_MB;
        unsigned int smVal  = *SHARED_MEM;
        printf("%s: Current Values "
                       "local MB %2d (write Id %d), "
                       "external MB %2d (write Id %d), "
                       "Shared Memory %2d (write Id %d). "
                       "Increment all.\n",
                       SYSTEM,
                       mbVal & 0xff,  mbVal  >> 23,
                       mbxVal & 0xff, mbxVal >> 23,
                       smVal & 0xff,  smVal  >> 23);
        *LOCAL_MB   = SYSID | ((mbVal  & 0xff) + 1);
        *EXT_MB     = SYSID | ((mbxVal & 0xff) + 1);
        *SHARED_MEM = SYSID | ((smVal  & 0xff) + 1);
    }
    printf("%s: Application Finished\n", SYSTEM);
    return 0;
}
