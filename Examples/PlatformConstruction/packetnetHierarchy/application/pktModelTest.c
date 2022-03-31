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


/*
 * This is a test harness to stimulate a simple peripheral model that uses
 *  the packetnet.
 */

#include <stdio.h>
#include <string.h>

typedef unsigned int  Uns32;
typedef unsigned char Uns8;

#define LOG(_FMT, ...)  printf( "Info " _FMT,  ## __VA_ARGS__)

static inline void writeReg8(Uns32 address, Uns32 offset, Uns8 value)
{
    *(volatile Uns8*) (address + offset) = value;
}

void delay(Uns32 d) {
    Uns32 i;
    for(i=0; i < d; i++) {
        i++;
    }
}

int main(int argc, char **argv)
{

    LOG("PACKETNET TEST Application\n\n");
    delay(1000);

    // Write to the transmit register of the first instance, causing the model
    // to transmit. The value 0x77 goes in the packet header, so we can see which
    // instance was triggered.
    writeReg8(0x80000000, 0, 0x77);

    delay(1000);
    // Write to the transmit register of the second instance, causing the model
    // to transmit. The value 0x88 goes in the packet header, so we can see which
    // instance was triggered.
    writeReg8(0x80000010, 0, 0x88);

    delay(1000);
    LOG("PACKETNET TEST Application DONE\n\n");
    return 1;
}

