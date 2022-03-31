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

// UART Peripheral Base Address
#define UART0_BASE ((unsigned char *) 0x100003f8)

// Peripheral Register Macros Definition
#define BPORT1 UART0_BASE
#include "freescale.ovpworld.org/peripheral/KinetisUART/1.0/pse/pse.macros.igen.h"

volatile unsigned char *ab_BDH    = BPORT1_AB_BDH;
volatile unsigned char *ab_BDL    = BPORT1_AB_BDL;
volatile unsigned char *ab_C1     = BPORT1_AB_C1;
volatile unsigned char *ab_C2     = BPORT1_AB_C2;
volatile unsigned char *ab_S1     = BPORT1_AB_S1;
volatile unsigned char *ab_C3     = BPORT1_AB_C3;
volatile unsigned char *ab_D      = BPORT1_AB_D;
volatile unsigned char *ab_MA1    = BPORT1_AB_MA1;
volatile unsigned char *ab_MA2    = BPORT1_AB_MA2;
volatile unsigned char *ab_C4     = BPORT1_AB_C4;
volatile unsigned char *ab_MODEM  = BPORT1_AB_MODEM;
volatile unsigned char *ab_PFIFO  = BPORT1_AB_PFIFO;
volatile unsigned char *ab_CFIFO  = BPORT1_AB_CFIFO;
volatile unsigned char *ab_TWFIFO = BPORT1_AB_TWFIFO;
volatile unsigned char *ab_RWFIFO = BPORT1_AB_RWFIFO;

static void initFreeScaleKinetisUart () {

    // programmers guide at https://www.element14.com/community/servlet/JiveServlet/previewBody/39326-102-1-223995/freescale.User_Guide_3.pdf
    //     page 103
    printf ("applicationReceive: Initializing KinetisUART\n");
    // Initialization sequence from MQX configuration of the UART
    *ab_BDH    = 0x00;
    *ab_BDL    = 0x20;
    *ab_C4     = 0x12;
    *ab_C1     = 0x00;
    *ab_C2     = 0x00;
    *ab_C4     = 0x12;
    *ab_MA1    = 0x00;
    *ab_MA2    = 0x00;
    *ab_C3     = 0x00;
    *ab_TWFIFO = 0x00;
    *ab_RWFIFO = 0x01;
    *ab_C2     = 0x00;
    *ab_PFIFO  = 0x88;
    *ab_CFIFO  = 0xc0;
    *ab_C2     = 0x0c;
    *ab_MODEM  = 0x00;
    *ab_S1     = 0xd0;
    *ab_D      = 0x0d;
}

static char getChar(void ){
    /* Wait until character has been received */
    while (!(*ab_S1  & BPORT1_AB_S1_RDRF));

    /* Return the 8-bit data from the receiver */
    return  *ab_D;
}

static void putChar(char c) {
    while ((*ab_S1 & BPORT1_AB_S1_TDRE) == 0) { }
    *ab_D = c;
}


int main(int argc, char **argv) {

    initFreeScaleKinetisUart();

    printf ("applicationReceive: Reading from UART\n\n");

    while(1) {
        char c = getChar();
        if (c == '\n') {
            break;
        }
        printf("    got char '%c' \n", c >= ' ' ?c: '-');
    }

    printf ("applicationReceive: sending ACK\n");
    putChar('Y');

    return 0;
}



