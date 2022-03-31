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

static inline void writeReg8(unsigned int address, unsigned char value)
{
    *(volatile unsigned char*) (address) = value;
}

void delay(unsigned int d) {
    unsigned int i, j;
    for(i=0; i < d; i++)
        for(j=0; j < 2000; j++);
}

#define LCD_MEM_BASE     0x80000000

static void write32Chars( unsigned char *str, unsigned int offset, unsigned int len) {
    unsigned int i;
    char buffer [32];
    unsigned int remain=len-offset;     // chars available from offset in str

    strncpy(&buffer[0], &str[offset], remain);         // copy from offset
    if (remain<32) {
        strncpy(&buffer[remain], &str[0], 32-remain);  // remaining copy from 0
    }

    buffer[32]=0;       // ensure string termination character
    LOG("Write lcd '%s'", buffer);
    for (i = 0; i < 32; i++) {
        writeReg8(LCD_MEM_BASE+i, buffer[i]);
    }
}

int main(int argc, char **argv)
{
    LOG("Starting LCD display");

    unsigned int index           = 0;
    unsigned char *lcd2x16_0_str = "0123456789ABCDEF" "The Quick Brown Fox Jumped Over ...";
    unsigned int   len           = strlen(lcd2x16_0_str);

    for(;;) {
        write32Chars (lcd2x16_0_str, index, len);
        index = (index + 1) % len;
        delay (5000);
    }
    return 1;
}

