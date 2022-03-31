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

static void initFreeScaleKinetisUart (unsigned char *uartBase) {
    volatile unsigned char *ab_BDH = uartBase + 0x0;
    volatile unsigned char *ab_BDL = uartBase + 0x1;
    volatile unsigned char *ab_C1 = uartBase + 0x2;
    volatile unsigned char *ab_C2 = uartBase + 0x3;
    volatile unsigned char *ab_S1 = uartBase + 0x4;
    volatile unsigned char *ab_C3 = uartBase + 0x6;
    volatile unsigned char *ab_D = uartBase + 0x7;
    volatile unsigned char *ab_MA1 = uartBase + 0x8;
    volatile unsigned char *ab_MA2 = uartBase + 0x9;
    volatile unsigned char *ab_C4 = uartBase + 0xa;
    volatile unsigned char *ab_MODEM = uartBase + 0xd;
    volatile unsigned char *ab_PFIFO = uartBase + 0x10;
    volatile unsigned char *ab_CFIFO = uartBase + 0x10;
    volatile unsigned char *ab_TWFIFO = uartBase + 0x13;
    volatile unsigned char *ab_RWFIFO = uartBase + 0x15;

    // programmers guide at https://www.element14.com/community/servlet/JiveServlet/previewBody/39326-102-1-223995/freescale.User_Guide_3.pdf
    //     page 103
    printf ("Initializing KinetisUART\n");
    // sequence got from watching MQX use the UART
    *ab_BDH = 0x00;
    *ab_BDL = 0x20;
    *ab_C4 = 0x12;
    *ab_C1 = 0x00;
    *ab_C2 = 0x00;
    *ab_C4 = 0x12;
    *ab_MA1 = 0x00;
    *ab_MA2 = 0x00;
    *ab_C3 = 0x00;
    *ab_TWFIFO = 0x00;
    *ab_RWFIFO = 0x01;
    *ab_C2 = 0x00;
    *ab_PFIFO = 0x88;
    *ab_CFIFO = 0xc0;
    *ab_C2 = 0x0c;
    *ab_MODEM = 0x00;
    *ab_S1 = 0xd0;
    *ab_D = 0x0d;
}

// defines found at www.keil.com/dd/docs/arm/freescale/kinetis/mkl34z4.h
static void writeMessFreescaleKinetisUart (unsigned char *uartBase,  unsigned const char *myString) {
    volatile unsigned char *ab_S1 = uartBase + 0x4;
    volatile unsigned char *ab_D  = uartBase + 0x7;
    #define UART_S1_TDRE_MASK 0x80

    unsigned int i;
    for(i=0;i<strlen(myString);i++){
        while ((*ab_S1 & UART_S1_TDRE_MASK) == 0) {
            // Wait for TransmitRegister Empty flag
        }
        *ab_D = myString[i];
    }
}

#define UART0_BASE ((unsigned char *) 0x100003f8)

int main(int argc, char **argv) {

    initFreeScaleKinetisUart(UART0_BASE);

    printf ("Writing to uart - see log file\n\n");

    writeMessFreescaleKinetisUart(UART0_BASE, "Hello UART0 world with separate harness and module in C using OP API.\n\n");

    return 0;
}



