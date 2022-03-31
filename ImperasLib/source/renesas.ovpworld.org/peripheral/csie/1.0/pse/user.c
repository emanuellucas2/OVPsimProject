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
//                          Thu Sep 13 12:35:37 2012
//
////////////////////////////////////////////////////////////////////////////////

#include "pse.igen.h"

#define UNUSED __attribute__((unused))

typedef struct outputPinS {
    const char  *name;
    ppmNetHandle netP;
    Uns32        value;
} outputPin, *outputPinP;

static outputPin INTCEOF = { "INTCEOF" , 0, 0 };
static outputPin INTCEC  = { "INTCEC"  , 0, 0 };
static outputPin SCKE    = { "SCKE"    , 0, 0 };
static outputPin SOE     = { "SOE"     , 0, 0 };
static outputPin SCSE0   = { "SCSE0"   , 0, 0 };
static outputPin SCSE1   = { "SCSE1"   , 0, 0 };
static outputPin SCSE2   = { "SCSE2"   , 0, 0 };
static outputPin SCSE3   = { "SCSE3"   , 0, 0 };
static outputPin SCSE4   = { "SCSE4"   , 0, 0 };
static outputPin SCSE5   = { "SCSE5"   , 0, 0 };
static outputPin SCSE6   = { "SCSE6"   , 0, 0 };
static outputPin SCSE7   = { "SCSE7"   , 0, 0 };

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

UNUSED static struct {
    Uns32 SIE;
    Uns32 SCKE;
} inputPin;

static Int32 channel;
static Uns8  rxFull;
static Bool  writeError;       // An error has occurred on most recent write

bhmEventHandle evWriteTX;

static Uns32  PCLK0;
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

#define FIFOSZ 16
typedef struct elemS {
    Uns8  select;
    Uns16 data;
} elem, *elemP;
struct {
    elem entry[FIFOSZ];
    Uns8 wptr, rptr;
    Uns8 full, empty;
} fifo;

static void initFifo() {
    fifo.wptr  = 0;
    fifo.rptr  = 0;
    fifo.full  = 0;
    fifo.empty = 1;

    CSIEP0_reg2_data.STR.bits.SFP = 0;
    CSIEP0_reg2_data.STR.bits.FLF = fifo.full;
    CSIEP0_reg2_data.STR.bits.EMF = fifo.empty;
}

static void sfpFifo () {
    //
    // SFP calculation
    //
    if (CSIEP0_reg0_data.CTL0.bits.TMS==1) {
        //
        // Block Transfer mode
        //
        CSIEP0_reg2_data.STR.bits.SFP = fifo.wptr;
    } else {
        //
        // Single Transfer mode
        //
        CSIEP0_reg2_data.STR.bits.SFP = fifo.wptr - fifo.rptr;
    }
}

//
// Return a flag to indicate an overflow
//
static Uns8 pushFifo(Uns16 data) {

    //
    // if we are attempting a write, and the fifo is full
    // then we have caused an overflow
    //
    Uns8 overflow = fifo.full;

    //
    // Data / CS
    //
    if (fifo.wptr < FIFOSZ) {
        fifo.entry[fifo.wptr].data   = data;
        fifo.entry[fifo.wptr].select = CSIEP0_reg1_data.CS.bits.CS;
    }

    //
    // SFP calculation
    //
    sfpFifo();

    //
    // Flags
    //
    fifo.wptr++;
    fifo.full  = (fifo.wptr >= FIFOSZ);
    fifo.empty = (fifo.wptr >= fifo.rptr) ? 1 : 0;

    CSIEP0_reg2_data.STR.bits.FLF = fifo.full;
    CSIEP0_reg2_data.STR.bits.EMF = fifo.empty;

    return overflow;
}

static elem popFifo() {
    //
    // Data
    //
    elem value = { 0 };
    if (fifo.rptr < FIFOSZ) {
        value = fifo.entry[fifo.rptr];
    }

    //
    // SFP calculation
    //
    sfpFifo();

    //
    // Flags
    //
    fifo.rptr++;
    fifo.empty = (fifo.wptr >= fifo.rptr) ? 1 : 0;

    CSIEP0_reg2_data.STR.bits.EMF = fifo.empty;

    return value;
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
    while(CSIEP0_reg0_data.CTL0.bits.RXE) {
        //
        // This determines how often to read the serial channel
        // If connected to a terminal - this really should be polled slowly
        // so that the polling does not dominate the simulation
        //
        double delay = USE_BAUDRATE ? (microSecCB) : DEFAULT_DELAY;

        Uns8 rxbits = 8;
        switch (CSIEP0_reg2_data.CTL2.bits.DL) {
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            rxbits = CSIEP0_reg2_data.CTL2.bits.DL;
            break;
        case 0:
            rxbits = 16;
            break;
        default:
            // already generated warning
            break;
        }

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
            CSIEP0_reg1_data.RX.value = (c[1] << 8) | c[0];
            if (rxFull) {
                //
                // If the receiver is not empty, block
                //
            } else {
                posPulseNet(&INTCEC);
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
    while (CSIEP0_reg0_data.CTL0.bits.TXE) {
        //
        // Are we in block or single transmission mode ?
        //
        if (CSIEP0_reg0_data.CTL0.bits.TMS==1) {
            //
            // CETMS=1, Block Transfer mode
            //

        } else {
            //
            // CETMS=0, Single Transfer mode
            //

        }

        //
        // If the write fifo empty, wait for a new write event
        //
        if (fifo.empty == 1) {
            bhmWaitEvent(evWriteTX); // This event is triggered on write to TX buffer
        }

        //
        Uns8 txbits = 8;
        switch (CSIEP0_reg2_data.CTL2.bits.DL) {
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
            txbits = CSIEP0_reg2_data.CTL2.bits.DL;
            break;
        case 0:
            txbits = 16;
            break;
        default:
            // already generated warning
            break;
        }

        Uns8 len = (txbits >= 16) ? 2 : 1;

        elem entry = popFifo();
        bhmWaitDelay(microSecCB * txbits);  // txbits delay
        Uns8 c[2];
        c[0] = entry.data & 0xff;
        c[1] = (entry.data>>8) & 0xff;
        writeOutput(c, len);

        //
        // Update the status register
        //
        posPulseNet(&INTCEOF);

        //
        // Block/Single Transfer mode
        //
        if (CSIEP0_reg0_data.CTL0.bits.TMS) {
            //
            // Block Transfer
            //
        } else {
            //
            // Single Transfer
            //
            CSIEP0_reg2_data.STR.bits.TSF = 0;
        }
        CSIEP0_reg2_data.STR.bits.TSF = 1;

    }
}

void update_timer () {
    //
    // Calculate the Baud Rate
    //
    Uns8 cks = CSIEP0_reg0_data.CTL1.bits.CKS;
    switch (cks) {
    //
    // Drop through modes 0-6
    //
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        PCLKS = PCLK0 / (0x1 << cks);
        break;

    case 7:
        // SCKE - unsupported slave mode
        bhmMessage("W", "CKS", "Unsupported, BRG0, BRG1, SCKB - defaulting to fQCSI/64");
        PCLKS = PCLK0 / (0x1 << 6);
        break;
    }

    microSecCB = (1 / PCLKS) * 2 * 1000000;
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_NET_CB(P_SCKE) {
    // YOUR CODE HERE (P_SCKE)
}

PPM_NET_CB(P_SIE) {
    // YOUR CODE HERE (P_SIE)
}

PPM_REG_READ_CB(readRX) {
    rxFull = 0;
    return readByteOrShort(addr, bytes, user);
}

PPM_REG_READ_CB(readTX) {
    return readByteOrShort(addr, bytes, user);
}

PPM_REG_WRITE_CB(writeCS) {
    //
    // Check legal values
    //
    if (data & 0xfff0) {
        bhmMessage("W", "CSIE", "Register CS Illegal value 0x%02x\n", data);
    }
    *(Uns16*)user = (data & ~(0xfff0));
}

PPM_REG_WRITE_CB(writeCTL0) {
    Uns8 oldPWR  = CSIEP0_reg0_data.CTL0.bits.PWR;
    Uns8 oldRXE  = CSIEP0_reg0_data.CTL0.bits.RXE;
    Uns8 oldTXE  = CSIEP0_reg0_data.CTL0.bits.TXE;
    Uns8 oldCTL0 = CSIEP0_reg0_data.CTL0.value;

    *(Uns8*)user = data;

    if (CSIEP0_reg0_data.CTL0.bits.PWR) {
        if (oldPWR==0) {
            //
            // Valid write
            //
        } else {
            //
            // Invalid write
            //
            if ((oldCTL0 & 0x7f) != (CSIEP0_reg0_data.CTL0.value & 0x7f)) {
                bhmMessage("W", "CSIB", "Register CTL0 ignoring rewrite values due to PWR setting\n");
                CSIEP0_reg0_data.CTL0.value = oldCTL0;
            }
        }
    }

    //
    // If either RXE or TXE Enabled, then update the timer
    //
    if (CSIEP0_reg0_data.CTL0.bits.RXE || CSIEP0_reg0_data.CTL0.bits.TXE) {
        update_timer();
    }

    //
    // if PWR==0 || (TXE==0 && RXE==0)
    //
    if (CSIEP0_reg0_data.CTL0.bits.PWR==0 || (CSIEP0_reg0_data.CTL0.bits.RXE==0 && CSIEP0_reg0_data.CTL0.bits.TXE==0)) {
        CSIEP0_reg2_data.STR.bits.TSF = 0;
    }

    //
    // have the RX or TX Enable changed state
    //
    if (CSIEP0_reg0_data.CTL0.bits.RXE != oldRXE) {
        if (CSIEP0_reg0_data.CTL0.bits.RXE) {
            rxThreadHandle = bhmCreateThread(rxThread, NULL, "RX", 0);
        } else {
            bhmDeleteThread(rxThreadHandle);
        }
    }
    if (CSIEP0_reg0_data.CTL0.bits.TXE != oldTXE) {
        if (CSIEP0_reg0_data.CTL0.bits.TXE) {
            txThreadHandle = bhmCreateThread(txThread, NULL, "TX", 0);
        } else {
            bhmDeleteThread(txThreadHandle);
        }
    }

    //
    // Potential transmitter event on enable
    //
    bhmTriggerEvent(evWriteTX);
}

PPM_REG_WRITE_CB(writeCTL1) {
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writeCTL2) {
    *(Uns8*)user = data;

    switch (CSIEP0_reg2_data.CTL2.bits.DL) {
    case 0:
    case 8 ... 15:
        break;
    default:
        bhmMessage("W", "LENGTH", "CTL2[CL] Illegal Data Length 0x%04x", CSIEP0_reg2_data.CTL2.bits.DL);
    }
}

PPM_REG_WRITE_CB(writeCTL3) {
    //
    // Check legal values
    //
    if (data & 0xf0) {
        bhmMessage("W", "CSIE", "Register CTL3 Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (data & ~(0xf0));
}

PPM_REG_WRITE_CB(writeCTL4) {
    //
    // Unused in model
    //
    *(Uns8*)user = data;
}

PPM_NBYTE_WRITE_CB(writeOPT) {
    if(bytes != 2) {
        bhmMessage("E", "PPM_WNB", "Only 2 byte access permitted");
        return;
    }
    Uns32 reg   = (offset-(0x10+0x0))/0x2;
    CSIEP0_reg3_data.OPT[reg].value = *(Uns16*)data;
}


PPM_REG_WRITE_CB(writeSTR) {
    *(Uns8*)user = data & 0x80;

    //
    // Clear the pointers and flags on FIFO
    //
    if (CSIEP0_reg2_data.STR.bits.PCT) {
        initFifo();
    }

    CSIEP0_reg2_data.STR.bits.PCT = 0;
}

PPM_REG_WRITE_CB(writeTX) {
    Uns8 overflow;

    writeByteOrShort(addr, bytes, user, data);

    //
    // Push data into fifo if it is a write to TX0L
    //
    if ((PTR_TO_UNS32(addr) & 0x1) == 0x0) {
        overflow = pushFifo(CSIEP0_reg1_data.TX.value);
        if (overflow) {
            posPulseNet(&INTCEOF);
        }
        bhmTriggerEvent(evWriteTX);
    }
}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();

    INTCEOF.netP = handles.INTCEOF;
    INTCEC.netP  = handles.INTCEC;
    SCKE.netP    = handles.SCKE;
    SOE.netP     = handles.SOE;
    SCSE0.netP   = handles.SCSE0;
    SCSE1.netP   = handles.SCSE1;
    SCSE2.netP   = handles.SCSE2;
    SCSE3.netP   = handles.SCSE3;
    SCSE4.netP   = handles.SCSE4;
    SCSE5.netP   = handles.SCSE5;
    SCSE6.netP   = handles.SCSE6;
    SCSE7.netP   = handles.SCSE7;

    //
    // Get the PCLK0 parameter
    //
    if(!bhmUns32ParamValue("PCLK0", &PCLK0)) {
        bhmMessage("W", "CSIE", "PCLK0 parameter should be configured");
    }

    //
    // Initialize the FIFO, and read status
    //
    rxFull = 0;
    initFifo();
    evWriteTX   = bhmCreateNamedEvent("tx", "transmitter event");

}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

