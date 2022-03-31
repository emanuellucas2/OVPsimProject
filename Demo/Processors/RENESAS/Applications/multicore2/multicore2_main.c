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
#include "simulatorIntercepts.h"

#define NUM_VALUES 35

volatile int flag;
volatile int fibres;

// The writer function defined in multicore2_writer.c
int writer(int id, int numValues);
// The reader function defined in multicore2_reader.c
int reader(int id);


int main(int argc, char **argv) {

    int id = impProcessorId();

    printf("CPU %d starting...\n", id);

    switch(id) {

        case 0:
            writer(id, NUM_VALUES);
            break;

        case 1:
            reader(id);
            break;

        case 2:
            break;
    }

    printf("CPU %d: finished\n",id);

    return 1;
}
