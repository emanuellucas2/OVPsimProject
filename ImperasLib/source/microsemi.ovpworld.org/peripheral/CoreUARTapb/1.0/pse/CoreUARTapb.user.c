/*
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                           Imperas/OVP Generated
//
////////////////////////////////////////////////////////////////////////////////

#include "pse.igen.h"

static Int32 channel;
static Uns8  txFull;
static Uns8  rxFull;
static Bool  writeError;       // An error has occurred on most recent write

bhmEventHandle evWriteTX;

static double microSecCB;

static bhmThreadHandle rxThreadHandle = 0;
static bhmThreadHandle txThreadHandle = 0;


static Int32 readInput(Uns8 *buffer, Uns32 length) {
    Int32 bytes = 0;
    if (channel >= 0) {
        bytes = bhmSerReadN(channel, buffer, length);
    }
    return bytes;
}

#define DEFAULT_DELAY 20000
#define USE_BAUDRATE 0
static void rxThread(void *user) {
    while(1) {
        //
        // This determines how often to read the serial channel
        // If connected to a terminal - this really should be polled slowly
        // so that the polling does not dominate the simulation
        //
        double d = USE_BAUDRATE ? (microSecCB * 10) : DEFAULT_DELAY;
        bhmWaitDelay(d);  // 1 start bit, 8 bits data, 1 parity bit = 10

        //
        // keep getting chars, do not allow overruns
        //
        Uns8 c;
        Int32 bytes = readInput(&c, 1);

        if (bytes > 0) {
            if(rxFull) {
                if(PSE_DIAG_LOW)
                    bhmMessage("W","SRO" , "Rx Buffer full - Data receive overflow - discarded (%c)", c);
                port0_Reg_data.Status.bits.OVERFLOW = 1;
            } else {
                port0_Reg_data.RxData.value = c;
                port0_Reg_data.Status.bits.RXRDY = 1;
                rxFull = 1;
            }
        }
    }
}

static Uns32 writeOutput(Uns8 *buffer, Uns32 length)
{
    Uns32 rc = 0;

    if (channel >= 0) {

        rc = bhmSerWriteN(channel, buffer, length);

        if (rc != length) {
            if (!writeError) {
                bhmMessage("W", "SWE", "Serial channel write error (%u). Channel closed?", bhmSerLastError(channel));
                writeError = True;
            }
        } else {
            writeError = False;
        }
    }

    return rc;
}

static void txThread(void *user) {
    while(1) {
        bhmWaitEvent(evWriteTX);            // This event is triggered on write to TX buffer

        //
        // check for enable
        //
        Uns8 c;
        if (txFull) {
            txFull = 0;

            c = port0_Reg_data.TxData.value;
            //
            // Send the TX register value
            //
            writeOutput(&c, 1);
        }
    }
}

void update_timer () {
    //
    // Calculate the Baud Rate
    //
    microSecCB = 10;
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_READ_CB(Ctrl1Read) {
    return *(Uns32*)user;
}

PPM_REG_WRITE_CB(Ctrl1Write) {
    update_timer();
}

PPM_REG_READ_CB(Ctrl2Read) {
    return *(Uns32*)user;
}

PPM_REG_WRITE_CB(Ctrl2Write) {
    update_timer();
}

PPM_REG_READ_CB(Ctrl3Read) {
    return *(Uns32*)user;
}

PPM_REG_WRITE_CB(Ctrl3Write) {
    update_timer();
}

PPM_REG_READ_CB(RxDataRead) {
	// data is being read clear rx ready flag
    port0_Reg_data.Status.bits.RXRDY = 0;
    rxFull = 0;
    return *(Uns32*)user;
}

PPM_REG_READ_CB(StatusRead) {
	// data is immediately sent so always set tx ready flag
    port0_Reg_data.Status.bits.TXRDY = 1;

    return port0_Reg_data.Status.value;
}

PPM_REG_WRITE_CB(TxDataWrite) {
    // place into register
    port0_Reg_data.TxData.value = data;
    txFull = 1;

    //
    // transmitter event
    //
    bhmTriggerEvent(evWriteTX);

}

PPM_CONSTRUCTOR_CB(constructor) {
    // YOUR CODE HERE (pre constructor)
    periphConstructor();
    // YOUR CODE HERE (post constructor)

    //
    // Setup the channel
    //
    channel = bhmSerOpenAuto();

    //
    // Start the threads
    //
    evWriteTX      = bhmCreateNamedEvent("tx",  "transmitter write event");
    rxThreadHandle = bhmCreateThread(rxThread, NULL, "RX", 0);
    txThreadHandle = bhmCreateThread(txThread, NULL, "TX", 0);
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

