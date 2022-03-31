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
 * This is a simple program to display a switch on an led
 */

#include <stdio.h>
#include <string.h>

#define LOG(_FMT, ...)  printf( "Application: " _FMT "\n",  ## __VA_ARGS__)

void delay(unsigned int d) {
    unsigned int i, j;
    for(i=0; i < d; i++)
        for(j=0; j < 2000; j++);
}


int main(int argc, char **argv)
{
    unsigned int status;
    LOG("Starting user application");

    unsigned int counter  = 0;

    for(;;) {
        LOG("  counter=%d", counter++);
        delay (5000);
    }
    return 1;
}

