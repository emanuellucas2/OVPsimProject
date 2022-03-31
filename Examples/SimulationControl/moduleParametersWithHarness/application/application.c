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

static void writeMess (unsigned char *uartBase,  unsigned const char *myString) {
    volatile unsigned char *uartTX = uartBase + 0;
    volatile unsigned char *uartLSR = uartBase + 5;
    unsigned int i;

    for(i=0;i<strlen(myString);i++){
        while ((*uartLSR & 0x20) == 0) {
            // Wait for Tx Holding Register Empty flag
        }
        *uartTX = myString[i];
    }
}

#define UART0_BASE ((unsigned char *) 0x100003e8)
#define UART1_BASE ((unsigned char *) 0x100003f8)

int main(int argc, char **argv) {

    printf ("\nWriting to UARTs - see log files\n\n");

    writeMess(UART0_BASE, "Hello UART0 world\n\n");
    writeMess(UART1_BASE, "Hello UART1 world\n\n");

    return 0;
}
