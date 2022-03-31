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

static void peek (unsigned int a) {
    printf ("Application peek @ 0x%x = %u\n", a, *(char*)a);
}

static void poke (unsigned int a) {
    printf ("Application poke @ 0x%x\n", a);
    *(char*)a = 0xff;
}

int main(int argc, char **argv) {

    peek(0x10000);
    peek(0x20000);
    poke(0x30000);

    peek(0x10000);
    peek(0x20000);
    poke(0x30000);

    return 0;
}



