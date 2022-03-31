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
#include "peripheral/ppm.h"
#include "peripheral/bhm.h"

// slave port
static void *SP;

Int32          ch = -1;

// read asynchronous mode and value byte
static Bool rxAsync = False;
static Uns8 rxByte;

// write asynchronous mode
static Bool txAsync = False;

static PPM_NBYTE_READ_CB(regRd8) {

    if(ch >= 0) {

        if(rxAsync) {

            // transition to synchronous mode
            rxAsync = False;

        } else {

            // read one character using blocking call (bhmSerReadB)
            bhmThreadHandle h1 = bhmThisThread();
            while(!bhmSerReadB(ch, &rxByte, 1)) {}
            bhmThreadHandle h2 = bhmThisThread();

            // detect switch to asynchronous mode
            rxAsync = (h1!=h2);
        }

        // return value unless in asynchronous mode
        if(!rxAsync) {
            *(Uns8*)data = rxByte;
        }
    } else {
        bhmMessage("I", "PER_UR", "Unable to receive");
    }
}

static PPM_NBYTE_WRITE_CB(regWr8) {

    if(ch >= 0) {

        if(txAsync) {

            // transition to synchronous mode - ignore written character that
            // has already been sent
            txAsync = False;

        } else {

            Uns8 dataByte = *(Uns8*)data;

            // write one character using blocking call (bhmSerWriteB)
            bhmThreadHandle h1 = bhmThisThread();
            while(!bhmSerWriteB(ch, &dataByte, 1)) {}
            bhmThreadHandle h2 = bhmThisThread();

            // detect switch to asynchronous mode
            txAsync = (h1!=h2);
        }
    } else {
        bhmMessage("I", "PER_UT", "Unable to transmit");
    }
}

int main(int argc, char *argv[]) {

    SP = ppmCreateSlaveBusPort("BS1", 2);

    ppmCreateNByteRegister(
        "tx",
        "send data",
        SP,
        0,           // offset
        1,           // bytes
        0,           // read fn
        regWr8,      // write fn
        0,           // view
        0,           // data
        0,           // user data
        1,           // volatile
        1,           // readable
        0,           // writeable
        0            // endian
    );

    ppmCreateNByteRegister(
        "rx",
        "read data",
        SP,
        1,           // offset
        1,           // bytes
        regRd8,      // read fn
        0,           // write fn
        0,           // view
        0,           // data
        0,           // user data
        1,           // volatile
        1,           // readable
        0,           // writeable
        0            // endian
    );

    //bhmWaitEvent(bhmGetSystemEvent(BHM_SE_START_OF_SIMULATION));

    bhmMessage("I", "PER_TX", "Starting service");

    ch = bhmSerOpenAuto();

    bhmMessage("I", "PER_ST", "Started");

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));

    return 0;
}

