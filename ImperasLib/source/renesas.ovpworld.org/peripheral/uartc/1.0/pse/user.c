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

#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                           Imperas/OVP Generated
//                          Wed Sep 12 15:14:22 2012
//
////////////////////////////////////////////////////////////////////////////////

#include "pse.igen.h"

#define UNUSED __attribute__((unused))

typedef struct outputPinS {
    const char  *name;
    ppmNetHandle netP;
    Uns32        value;
} outputPin, *outputPinP;

static outputPin INTUCT  = { "INTUCT"  , 0, 0 };
static outputPin INTUCR  = { "INTUCR"  , 0, 0 };
static outputPin INTUCRE = { "INTUCRE" , 0, 0 };
static outputPin TXDC    = { "TXDC"    , 0, 0 };

//
// Only write when a value change occurs
//
static void doWriteNet(outputPinP pin, Uns32 value) {
    if (value != pin->value) {
        pin->value = value;
        ppmWriteNet(pin->netP, pin->value);
    }
}
static void posPulseNet(outputPinP pin) {
    doWriteNet(pin, 1);
    doWriteNet(pin, 0);
}

static struct {
    Uns32 RXDC;
} inputPin;

static Int32 channel;
static Uns8  txFull;
static Uns8  rxFull;
static Bool  writeError;       // An error has occurred on most recent write

bhmEventHandle evWriteTX;

static Uns32  PCLK[10];
static double PCLKS;            // This is the selector clock
static double fBRGn;
static double microSecCB;

#define BYTE_ACCESS(_addr,_user) *(Uns8*)(UnsPS)(PTR_TO_UNS32(_user) | (PTR_TO_UNS32(_addr) & 1))

static void writeByteOrShort(void *addr, Uns32 bytes, void *user, Uns32 data) {
    if (bytes == 1) {
        BYTE_ACCESS(addr,user) = data;
    } else {
        *(Uns16*)user = data;
    }
}

static Uns32 readByteOrShort(void *addr, Uns32 bytes, void *user) {
    if (bytes == 1) {
        return BYTE_ACCESS(addr,user);
    } else {
        return *(Uns16*)user;
    }
}

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
    while(UARTP0_reg0_data.CTL0.bits.RXE) {
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
            //
            // Data receiving flag
            //
            UARTP0_reg2_data.OPT2.bits.RSF = 1;

            if (rxFull) {
                //
                // If the receiver is not empty generate an overrun
                //
                posPulseNet(&INTUCRE);
                UARTP0_reg0_data.STR.bits.OVE = 1;
            } else {
                //
                // Transfer received byte to RXL, do not overruun buffer p.314
                //
                UARTP0_reg1_data.RX.bits.RXL = c;

                posPulseNet(&INTUCR);
            }
            rxFull = 1;
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
    while(UARTP0_reg0_data.CTL0.bits.TXE) {
        bhmWaitEvent(evWriteTX);            // This event is triggered on write to TX buffer
        bhmWaitDelay(microSecCB * 10);  // 1 start bit, 8 bits data, 1 parity bit = 10

        //
        // check for enable
        //
        Uns8 c;
        if (txFull) {
            txFull = 0;

            c = UARTP0_reg1_data.TX.bits.TXL;

            //
            // Send the TX register value
            //
            writeOutput(&c, 1);

            posPulseNet(&INTUCT);
            UARTP0_reg0_data.STR.bits.TSF = 0;
        }
    }
}

void update_timer () {
    //
    // Calculate the Baud Rate
    //
    PCLKS      = PCLK[UARTP0_reg0_data.CTL1.bits.CKS];
    fBRGn      = PCLKS / (2 * UARTP0_reg0_data.CTL2.bits.BRS);
    microSecCB = 2 * (1 / fBRGn) * 1000000;

    if (PSE_DIAG_LOW) {
        bhmMessage("I", "BAUD", "CKS=%d PCLKS=%f BRS=%d fBRGn=%f CBdelay=%f",
            UARTP0_reg0_data.CTL1.bits.CKS, PCLKS,
            UARTP0_reg0_data.CTL2.bits.BRS, fBRGn, microSecCB);
    }
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_NET_CB(P_RXDC) {
    inputPin.RXDC = value;
}

PPM_REG_READ_CB(readRX) {
    rxFull = 0;
    UARTP0_reg2_data.OPT2.bits.RSF = 0;
    return readByteOrShort(addr, bytes, user);
}

PPM_REG_READ_CB(readTX) {
    return readByteOrShort(addr, bytes, user);
}

PPM_REG_WRITE_CB(writeCTL0) {
    // YOUR CODE HERE (writeCTL0)
    Uns8 oldRXE = UARTP0_reg0_data.CTL0.bits.RXE;
    Uns8 oldTXE = UARTP0_reg0_data.CTL0.bits.TXE;

    *(Uns8*)user = data;

    if (UARTP0_reg0_data.CTL0.bits.PWR) {
        //
        // Transmitter Enable status
        //
        if (UARTP0_reg0_data.CTL0.bits.TXE == 0) {
            UARTP0_reg0_data.STR.bits.TSF = 0;
        }
        //
        // Receiver Enable status
        //
        if (UARTP0_reg0_data.CTL0.bits.RXE == 0) {
            UARTP0_reg0_data.STR.bits.PE   = 0;
            UARTP0_reg0_data.STR.bits.FE   = 0;
            UARTP0_reg0_data.STR.bits.OVE  = 0;
            UARTP0_reg2_data.OPT2.bits.RSF = 0;
        }
    } else {
        //
        // Initialization
        //
        UARTP0_reg0_data.STR.value     = 0;
        UARTP0_reg2_data.OPT2.bits.RSF = 0;

        //
        // Validity Checks
        // PWR must be 1 for TXE and RXE to be valid
        //
        if (UARTP0_reg0_data.CTL0.bits.TXE) {
            bhmMessage("W", "CTL0", "Cannot set TXE when PWR==0");
            UARTP0_reg0_data.CTL0.bits.TXE = oldTXE;
        }
        if (UARTP0_reg0_data.CTL0.bits.RXE) {
            bhmMessage("W", "CTL0", "Cannot set RXE when PWR==0");
            UARTP0_reg0_data.CTL0.bits.RXE = oldRXE;
        }
    }

    //
    // If either RXE or TXE Enabled, then update the timer
    //
    if (UARTP0_reg0_data.CTL0.bits.RXE || UARTP0_reg0_data.CTL0.bits.TXE) {
        update_timer();
    }

    //
    // have the RX or TX Enable changed state
    //
    if (UARTP0_reg0_data.CTL0.bits.RXE != oldRXE) {
        if (UARTP0_reg0_data.CTL0.bits.RXE) {
            rxThreadHandle = bhmCreateThread(rxThread, NULL, "RX", 0);
        } else {
            bhmDeleteThread(rxThreadHandle);
        }
    }
    if (UARTP0_reg0_data.CTL0.bits.TXE != oldTXE) {
        if (UARTP0_reg0_data.CTL0.bits.TXE) {
            txThreadHandle = bhmCreateThread(txThread, NULL, "TX", 0);
        } else {
            bhmDeleteThread(txThreadHandle);
        }
    }

    //
    // Potential transmitter event
    //
    bhmTriggerEvent(evWriteTX);

}

PPM_REG_WRITE_CB(writeCTL1) {
    *(Uns8*)user = data;

    //
    // This will set the PCLK selection
    //
    update_timer ();
}

PPM_REG_WRITE_CB(writeCTL2) {
    *(Uns8*)user = data;

    update_timer ();
}

PPM_REG_WRITE_CB(writeOPT0) {
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writeOPT1) {
    //
    // Check legal values
    //
    if (data & 0xfe) {
        bhmMessage("W", "UARTC", "Register OPT1 Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (data & ~(0xfe));
}

PPM_REG_WRITE_CB(writeSTR) {
    //
    // Check legal values
    //
    if (data & 0x87) {
        bhmMessage("W", "UARTC", "Register STR Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (data & ~(0x87));
}

PPM_REG_WRITE_CB(writeTX) {
    writeByteOrShort(addr, bytes, user, data);

    //
    // Write to TX buffer, signal the thread
    //
    txFull = 1;
    UARTP0_reg0_data.STR.bits.TSF = 1;

    //
    // transmitter event
    //
    bhmTriggerEvent(evWriteTX);
}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();

    INTUCT.netP  = handles.INTUCT;
    INTUCR.netP  = handles.INTUCR;
    INTUCRE.netP = handles.INTUCRE;
    TXDC.netP    = handles.TXDC;

    //
    // Flags to indicate state of TX/RX Buffers
    //
    txFull = 0;
    rxFull = 0;
    evWriteTX   = bhmCreateNamedEvent("tx",  "transmitter write event");

    //
    // Get the PCLKx attributes
    //
    bhmUns32ParamValue("PCLK0", &PCLK[0]);
    bhmUns32ParamValue("PCLK1", &PCLK[1]);
    bhmUns32ParamValue("PCLK2", &PCLK[2]);
    bhmUns32ParamValue("PCLK3", &PCLK[3]);
    bhmUns32ParamValue("PCLK4", &PCLK[4]);
    bhmUns32ParamValue("PCLK5", &PCLK[5]);
    bhmUns32ParamValue("PCLK7", &PCLK[7]);
    bhmUns32ParamValue("PCLK9", &PCLK[9]);

    //
    // Setup the channel
    //
    channel = bhmSerOpenAuto();
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

