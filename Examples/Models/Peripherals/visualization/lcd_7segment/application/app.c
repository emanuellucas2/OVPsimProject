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
 * This is a simple program to display an incrementing number on an LCD 7 segment display
 */

#include <stdio.h>
#include <string.h>

#define LOG(_FMT, ...)  printf( "Application: " _FMT "\n",  ## __VA_ARGS__)

// data endian swap
#define SWAP_BYTE4(_d) (((_d & 0xFF000000) >> 24) | \
                        ((_d & 0x00FF0000) >>  8) | \
                        ((_d & 0x0000FF00) <<  8) | \
                        ((_d & 0x000000FF) << 24))

static inline void writeReg32(unsigned int address, unsigned int value)
{
    *(volatile unsigned int*) (address) = SWAP_BYTE4(value);
}

void delay(unsigned int d) {
    unsigned int i, j;
    for(i=0; i < d; i++)
        for(j=0; j < 2000; j++);
}

#define LCD_MEM_BASE     0x80000000

int main(int argc, char **argv)
{
    LOG("Starting LCD display");

    unsigned int lcd = 0x0;

    for(;;) {
        lcd = (lcd +1) & 0xffff;
        LOG("Write lcd 0x%0x", lcd);
        writeReg32(LCD_MEM_BASE, lcd);
        delay (5000);
    }
    return 1;
}

