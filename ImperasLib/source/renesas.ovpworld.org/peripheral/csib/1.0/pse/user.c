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
//                          Thu Sep 13 11:38:00 2012
//
////////////////////////////////////////////////////////////////////////////////

#include "pse.igen.h"

#define UNUSED __attribute__((unused))

typedef struct outputPinS {
    const char  *name;
    ppmNetHandle netP;
    Uns32        value;
} outputPin, *outputPinP;

static outputPin INTCBT  = { "INTCBT"  , 0, 0 };
static outputPin INTCBR  = { "INTCBR"  , 0, 0 };
static outputPin INTCBRE = { "INTCBRE" , 0, 0 };
static outputPin SOB     = { "SOB"     , 0, 0 };

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
    Uns32 SIB;
    Uns32 SCKB;
    Uns32 SSB;
} inputPin;

static Int32 channel;
static Uns8  txFull;
static Uns8  rxFull;
static Bool  writeError;       // An error has occurred on most recent write

bhmEventHandle evWriteTX;

static Uns32  PCLK[10];
static double PCLKS;            // This is the selector clock
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
    Int32 bytes = 0;
    while(CSIBP0_reg0_data.CTL0.bits.RXE) {
        //
        // This determines how often to read the serial channel
        // If connected to a terminal - this really should be polled slowly
        // so that the polling does not dominate the simulation
        //
        double delay = USE_BAUDRATE ? (microSecCB) : DEFAULT_DELAY;

        Uns8 rxbits = CSIBP0_reg0_data.CTL2.bits.CL + 8;
        Uns8 len = (rxbits >= 16) ? 2 : 1;

        bhmWaitDelay(delay * rxbits);  //  rxbits delay

        //
        // keep getting chars, may get 0, 1 or 2 back
        // we are finished when bytes = len
        //
        Uns8 c[2];
        bytes += readInput(&c[bytes], 1);
        if (bytes == len) {
            //
            // Transfer received byte(s) to RX - ignoring overrun P.348
            //
            CSIBP0_reg1_data.RX.bits.RXL = c[0];
            CSIBP0_reg1_data.RX.bits.RXH = c[1];
            if (rxFull) {
                //
                // If the receiver is not empty generate an overrun
                //
                posPulseNet(&INTCBRE);
            } else {
                posPulseNet(&INTCBR);
            }
            rxFull = 1;
            bytes = 0;
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
    while (CSIBP0_reg0_data.CTL0.bits.TXE) {
        bhmWaitEvent(evWriteTX);            // This event is triggered on write to TX buffer

        Uns8 txbits = CSIBP0_reg0_data.CTL2.bits.CL + 8;
        Uns8 len = (txbits >= 16) ? 2 : 1;

        bhmWaitDelay(microSecCB * txbits);  // txbits delay

        //
        // check for enable, also need to handle 16bit or 8bit data
        //
        Uns8 c[2];
        if (txFull) {
            txFull = 0;

            c[0] = CSIBP0_reg1_data.TX.bits.TXL;
            if (len == 2) {
                c[1] = CSIBP0_reg1_data.TX.bits.TXH;
            }

            //
            // Send the TX register
            //
            writeOutput(c, len);

            posPulseNet(&INTCBT);
            CSIBP0_reg0_data.STR.bits.TSF = 0;
        }
    }
}

void update_timer () {
    //
    // Calculate the Baud Rate
    //
    Uns8 cks = CSIBP0_reg0_data.CTL1.bits.CKS;
    switch (cks) {
    //
    // Drop through modes 2-6
    //
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        // PCLK2 .. PCLK6
        PCLKS = PCLK[CSIBP0_reg0_data.CTL1.bits.CKS];
        break;

    //
    // Default unsupported modes to PCLK6
    //
    case 0:
        // PCLK1 -> BRG0 - unsupported
    case 1:
        // PCLK1 -> BRG1 - unsupported
    case 7:
        // SCKB - unsupported
        bhmMessage("W", "CKS", "Unsupported, BRG0, BRG1, SCKB - defaulting to PCLK6");
        PCLKS = PCLK[6];
        break;
    }

    microSecCB = (1 / PCLKS) * 2 * 1000000;
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_NET_CB(P_SCKB) {
    inputPin.SCKB = value;
}

PPM_NET_CB(P_SIB) {
    inputPin.SIB = value;
}

PPM_NET_CB(P_SSB) {
    inputPin.SSB = value;
}

PPM_REG_READ_CB(readRX) {
    rxFull = 0;
    return readByteOrShort(addr, bytes, user);
}

PPM_REG_READ_CB(readTX) {
    return readByteOrShort(addr, bytes, user);
}

PPM_REG_WRITE_CB(writeCTL0) {
    //
    // Check legal values
    //
    if (data & 0x08) {
        bhmMessage("W", "CSIB", "Register CTL0 Illegal value 0x%02x\n", data);
    }

    Uns8 oldPWR  = CSIBP0_reg0_data.CTL0.bits.PWR;
    Uns8 oldRXE  = CSIBP0_reg0_data.CTL0.bits.RXE;
    Uns8 oldTXE  = CSIBP0_reg0_data.CTL0.bits.TXE;
    Uns8 oldCTL0 = CSIBP0_reg0_data.CTL0.value;
    *(Uns8*)user = (data & ~(0x08));

    if (CSIBP0_reg0_data.CTL0.bits.PWR) {
        if (oldPWR==0) {
            //
            // Valid write
            //
        } else {
            //
            // Invalid write
            //
            if ((oldCTL0 & 0x7f) != (CSIBP0_reg0_data.CTL0.value & 0x7f)) {
                bhmMessage("W", "CSIB", "Register CTL0 ignoring rewrite values due to PWR setting\n");
                CSIBP0_reg0_data.CTL0.value = oldCTL0;
            }
        }
    } else {
        //
        // Reset
        //
        CSIBP0_reg0_data.STR.value = 0;
    }

    //
    // If either RXE or TXE Enabled, then update the timer
    //
    if (CSIBP0_reg0_data.CTL0.bits.RXE || CSIBP0_reg0_data.CTL0.bits.TXE) {
        update_timer();
    }

    //
    // have the RX or TX Enable changed state
    //
    if (CSIBP0_reg0_data.CTL0.bits.RXE != oldRXE) {
        if (CSIBP0_reg0_data.CTL0.bits.RXE) {
            rxThreadHandle = bhmCreateThread(rxThread, NULL, "RX", 0);
        } else {
            bhmDeleteThread(rxThreadHandle);
        }
    }
    if (CSIBP0_reg0_data.CTL0.bits.TXE != oldTXE) {
        if (CSIBP0_reg0_data.CTL0.bits.TXE) {
            txThreadHandle = bhmCreateThread(txThread, NULL, "TX", 0);
        } else {
            bhmDeleteThread(txThreadHandle);
        }
    }

    //
    // Potential transmitter event ?
    //
    bhmTriggerEvent(evWriteTX);

}

PPM_REG_WRITE_CB(writeCTL1) {
    //
    // Check legal values
    //
    if (data & 0xe0) {
        bhmMessage("W", "CSIB", "Register CTL1 Illegal value 0x%02x\n", data);
    }
    Uns8 oldCTL1 = *(Uns8*)user;

    *(Uns8*)user = (data & ~(0xe0));

    //
    // Legal Write ? PWR==0
    // illegal Write PWR && (RXE || TXE)
    Uns8 PWR = CSIBP0_reg0_data.CTL0.bits.PWR;
    if (PWR) {
        bhmMessage("W", "CSIB", "Register CTL1 Illegal write CTL0[PWR]=%d\n", PWR);
        *(Uns8*)user = oldCTL1;
    }

    //
    // This will set the PCLK selection
    //
    update_timer();
}

PPM_REG_WRITE_CB(writeCTL2) {
    //
    // Check legal values
    //
    if (data & 0xf0) {
        bhmMessage("W", "CSIB", "Register CTL2 Illegal value 0x%02x\n", data);
    }

    Uns8 oldCTL2 = *(Uns8*)user;
    *(Uns8*)user = (data & ~(0xf0));

    //
    // Legal Write ? PWR==0 || (RXE==0 && TXE==0)
    // illegal Write PWR && (RXE || TXE)
    Uns8 RXE = CSIBP0_reg0_data.CTL0.bits.RXE;
    Uns8 TXE = CSIBP0_reg0_data.CTL0.bits.TXE;
    Uns8 PWR = CSIBP0_reg0_data.CTL0.bits.PWR;
    if (PWR && (RXE || TXE)) {
        bhmMessage("W", "CSIB", "Register CTL2 Illegal write CTL0[PWR]=%d CTL0[RXE]=%d CTL0[TXE]=%d\n", PWR, RXE, TXE);
        *(Uns8*)user = oldCTL2;
    }
}

PPM_REG_WRITE_CB(writeSTR) {
    //
    // Check legal values
    //
    if (data & 0x7e) {
        bhmMessage("W", "CSIB", "Register STR Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (data & ~(0x7e));
}

PPM_REG_WRITE_CB(writeTX) {
    writeByteOrShort(addr, bytes, user, data);

    //
    // Write to TX buffer, signal the thread
    //
    txFull = 1;
    CSIBP0_reg0_data.STR.bits.TSF = 1;

    //
    // Potential transmitter event
    //
    bhmTriggerEvent(evWriteTX);
}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();

    INTCBT.netP  = handles.INTCBT;
    INTCBR.netP  = handles.INTCBR;
    INTCBRE.netP = handles.INTCBRE;
    SOB.netP     = handles.SOB;

    //
    // Flags to indicate state of TX/RX Buffers
    //
    txFull = 0;
    rxFull = 0;
    evWriteTX   = bhmCreateNamedEvent("tx", "transmitter event");

    //
    // Get the PCLKx attributes
    //
    bhmUns32ParamValue("PCLK1", &PCLK[1]);
    bhmUns32ParamValue("PCLK2", &PCLK[2]);
    bhmUns32ParamValue("PCLK3", &PCLK[3]);
    bhmUns32ParamValue("PCLK4", &PCLK[4]);
    bhmUns32ParamValue("PCLK5", &PCLK[5]);
    bhmUns32ParamValue("PCLK6", &PCLK[6]);

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

