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

#define SP 0x40000000
#include "pse.macros.igen.h"

void delay(unsigned int delay) {
    unsigned int i, j;
    for (i=delay;i;i--) {
        for (j=5000;j;j--) {
            ; // delay
        }
    }
}

#define DMAINBUFFER  0x00001000
#define DMAOUTBUFFER 0x00002000

int main () {

    unsigned int i        =  0;
    unsigned int count    = 16; // initial Tx message length (then we send same length as received)
    unsigned int testData =  0; // incrementing data value
    unsigned int msgCount =  0; // message number

    // register values
    unsigned int control  =  0; // control register value
    unsigned int status   =  0; // status register value

    printf("CPU: Starting...\n");

    //
    // Configure DMA buffers
    //

    // set DMA Out Address
    *(unsigned int *)(SP_ABS_DMAADDRESSOUT) = DMAOUTBUFFER;
    // enable DMA Out
    *(unsigned int *)(SP_ABS_CONTROL) |= SP_ABS_CONTROL_DMAOUTEN;

    // set DMA In Address
    *(unsigned int *)(SP_ABS_DMAADDRESSIN) = DMAINBUFFER;
    // enable DMA In
    *(unsigned int *)(SP_ABS_CONTROL) |= SP_ABS_CONTROL_DMAINEN;

    // Send and receive messages until end flag set
    while (!(status & SP_ABS_STATUS_END)) {

        //
        // Check Output buffer is empty
        //

        do {
            delay(100);

            control = *(unsigned int *)(SP_ABS_CONTROL);
            if(control) printf("Control 0x%x\n", control);

        } while ((control & SP_ABS_CONTROL_MESSAGETOSEND));

        //
        // Send Message
        //

        // Write data to Tx Buffer
        // first byte message number
        *(unsigned char *)(DMAOUTBUFFER) = msgCount++;
        // data
        for (i=4;i<(count*4);i++) {
            *(unsigned char *)(DMAOUTBUFFER+i) = (testData++)+i;
        }
        printf("\nMessage in DMA Out buffer\n");

        // set count
        *(unsigned int *)(SP_ABS_CONTROL) |= (count << 16);
        // message to send
        *(unsigned int *)(SP_ABS_CONTROL) |= SP_ABS_CONTROL_MESSAGETOSEND;


        //
        // Wait for message sent
        //
        do {
            delay(100);

            // check and print status
            status = *(unsigned int *)(SP_ABS_STATUS);
            if(status)
                printf("Status 0x%x\n", status);

        } while (!(status & SP_ABS_STATUS_MESSAGESENT));

        //
        // Clear message sent flag
        //
        *(unsigned int *)(SP_ABS_STATUS) = SP_ABS_STATUS_MESSAGESENT;

        //
        // Wait for a message received
        //
        do {
            delay(100);

            // check and print status
            status = *(unsigned int *)(SP_ABS_STATUS);
            if(status) printf("Status 0x%x\n", status);

        } while (!(status & SP_ABS_STATUS_MESSAGERECEIVED));

        //
        // Receive message
        //

        count = (status & SP_ABS_STATUS_COUNT)>>16;
        printf("\nMessage received (length %d)\n", count);
        for (i=0;i<count;i++) {
            if((i%10)==0) printf("\n %2d: ", i);
            printf(" %8d", *(unsigned int *)(DMAINBUFFER+(4*i)));
        }
        printf("\n");

        //
        // clear received
        //
        *(unsigned int *)(SP_ABS_STATUS) = SP_ABS_STATUS_MESSAGERECEIVED;

    }

    delay(100);
    printf("CPU: finished\n");
}
