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

// Imperas

#include <stdio.h>

#include "uart.h"

#define LOG(_FMT, ...)                            \
    printf( "TEST: " _FMT,  ## __VA_ARGS__)

static int int_rcvd;

void int_handler()
{
    char c, t;
    int_rcvd++;

    t = *(volatile char *)(UART_BASE+UART_IIR);
    printf("Interrupt Handler 0x%02x (%u)\n",t, int_rcvd);
    if(t & UART_IIR_RDI){
        c = *(volatile char *)(UART_BASE+UART_RBR);
        printf("Character received %c\n", c);
    }
    if(t & UART_IIR_THRI){
        printf("Character sent\n");
    }
}

static void enableUart()
{
    LOG("Enable UART:\n");

    // enable interrupts
   *(volatile char *)(UART_BASE+UART_IER) = (UART_IER_RDI | UART_IER_THRI);
}

static void sendString(const char * string)
{
    char * out = (char *)string;
    LOG("Send String: %s\n", out);

    while(*out != 0) {
        unsigned int retry = 100;
        while (retry--) {
            char lsr;
            if ((lsr = *(volatile char *)(UART_BASE+UART_LSR)) & (UART_LSR_TEMT|UART_LSR_THRE)) {
                // Transmit buffer empty
                break;
            }
            printf("LSR 0x%02x\n", lsr);
        }
        printf("Send char %c (0x%02x)\n", *out, *out);
        *(volatile char *)(UART_BASE+UART_TBR) = *out;
        out++;
    }
}

static int initialise()
{
    LOG("Initialise:\n");

    int_rcvd = 0;
   return 1;
}


int main(int argc, char **argv)
{
    LOG("main starts\n");

    initialise();
    enableUart();

    LOG("main send string\n");

    sendString("Hello World\n");

    LOG("main done\n");

    return 1;
}

