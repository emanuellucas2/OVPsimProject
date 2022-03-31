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

#include <ctype.h>

#include "pse.igen.h"

#define PREFIX "I2C"

Uns32 i2cAddress;       // The address of the current I2C access

// ZC702 and ZC706 (common)
#define I2C_ADDRESS_BUSSWITCH   0x74
#define I2C_ADDRESS_CLOCK       0x5c
#define I2C_ADDRESS_HDMI        0x39
#define I2C_ADDRESS_EEPROM      0x34
#define I2C_ADDRESS_PORT_EXP    0x21
#define I2C_ADDRESS_RTC         0x31
#define I2C_ADDRESS_FMCLPCJ3    0x00
#define I2C_ADDRESS_FMCHPCJ4    0x00
// ZC706
#define I2C_ADDRESS_ZC706_PMBUS 0x34
// ZC702
#define I2C_ADDRESS_SFP         0x50
#define I2C_ADDRESS_DDR0        0x50
#define I2C_ADDRESS_DDR1        0x18
#define I2C_ADDRESS_SI5324      0x64
#define I2C_ADDRESS_ZC702_PMBUS 0x64

#define CHANNELADDRESSOFFSET 0x100

Uns32   channelEnable = -1;            // The channel selected for accesses (used as address offset)

#define I2C_SWITCH_CLOCK       0
#define I2C_SWITCH_HDMI        1
#define I2C_SWITCH_EEPROM      2
#define I2C_SWITCH_PORT_EXP    3
#define I2C_SWITCH_RTC         4
#define I2C_SWITCH_FMCLPCJ3    5
#define I2C_SWITCH_FMCHPCJ4    6
#define I2C_SWITCH_PMBUS       7
#define I2C_SWITCH_LAST        I2C_SWITCH_PMBUS

// Names of channel devices for debug output
char *channelDeviceZC702[8] = {"Si570 clock", "ADV7511 HDMI",
                               "I2C EEPROM", "I2C port Expander",
                               "I2C RTC", "FMC HPC",
                               "FMC LPC", "UCD9248 PMBus"};
char *channelDeviceZC706[8] = {"Si570 clock", "ADV7511 HDMI",
                               "I2C EEPROM", "I2C port Expander/DDR3 SODIMM",
                               "I2C RTC / Si5324 clock", "FMC HPC",
                               "FMC LPC", "UCD90120A PMBus"};

Uns32 clockMhz;                 // input clock rate in MHz
double transmitRateDelay;       // The rate of I2C data transfer (generates a delay after each data transfer out)
// the delay is per bit transfer, use the number of data bits and address bits
#define DATA_BITS      8
#define ADDRESSS_BITS 10

typedef struct StatusS {
    union {
        Uns32 value;
        struct {
            Uns32 __pad0 : 3;
            Uns32 RXRW : 1;
            Uns32 __pad4 : 1;
            Uns32 RXDV : 1;
            Uns32 TXDV : 1;
            Uns32 RXOVF : 1;
            Uns32 BA : 1;
        } bits;
    };
} StatusT;

StatusT Status;

typedef struct InterruptStatusS {
    union {
        Uns32 value;
        struct {
            Uns32 COMP     : 1;
            Uns32 DATA     : 1;
            Uns32 NACK     : 1;
            Uns32 TO       : 1;
            Uns32 SLV_RDY  : 1;
            Uns32 RX_OVF   : 1;
            Uns32 TX_OVF   : 1;
            Uns32 RX_UNF   : 1;
            Uns32 __pad8   : 1;
            Uns32 ARB_LOST : 1;
        } bits;
    };
} InterruptStatusT;

InterruptStatusT InterruptStatus;

// Enum to track current state
typedef enum {
    IDLE  = 0x0,
    RX    = 0x1,
    TX    = 0x2
} stateE;

struct {
    Uns32     fifoSize;         // Number of entries available in fifo
    Uns32     rxTrigLvl;        // Number of entries in Rx FIFO to trigger interrupt
    Uns32     txTrigLvl;        // Number of entries in Tx FIFO to trigger interrupt
    stateE    status;           // Indicates the current status IDLE, RX or TX
    Bool      overrunErr;       // Overrun error flag
    Bool      threInterrupt;    // Set when transmit holding reg empty interrupt is active
    Bool      writeError;       // An error has occurred on most recent write
    Bool      readError;        // An error has occurred on most recent read

    // Programmers view events
    bhmEventHandle  charOut;
    bhmEventHandle  charOutAck;
    bhmEventHandle  charIn;     // Character received by I2C
    bhmEventHandle  charRead;   // Char read from Fifo
    bhmEventHandle  overrun;
    bhmEventHandle  interrupt;

} state;

#define MAX_FIFO       64
#define DEFAULT_FIFO   16

typedef struct fifoBufferS {
    Uns8  buffer[MAX_FIFO];  // fifo buffer
    Uns8  rdp, wrp;          // pointers to read and write points
    Bool  full, empty;       // flags when full or empty
} fifoBufferT, *fifoBufferP;

static fifoBufferT Rx, Tx;

//
// Thread handling functions
//
static void channelWriteThread(void *user);

bhmThreadHandle txThreadHandle = 0;

static void stopTxThread() {
    if (txThreadHandle) {
        bhmDeleteThread(txThreadHandle);
        txThreadHandle = 0;
    }
}
static void startTxThread() {
    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_TX","Check Start Tx Thread");
    }
    if (!txThreadHandle) {
        txThreadHandle = bhmCreateThread(channelWriteThread, NULL, "channelWriteThread", 0);

    } else if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_TX","Tx Thread already running");
    }

}

static void channelReadThread(void *user);

bhmThreadHandle rxThreadHandle = 0;

static void stopRxThread() {
    if (rxThreadHandle) {
        bhmDeleteThread(rxThreadHandle);
        rxThreadHandle = 0;
    }
}
static void startRxThread() {
    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_RX","Check Start Rx Thread");
    }

    if(!rxThreadHandle) {
        rxThreadHandle = bhmCreateThread(channelReadThread, NULL, "channelReadThread", 0);

    } else if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_RX","Rx Thread already running");
    }

}

/////////////////////
// FIFO OPERATIONS //
/////////////////////

//
// Set the fifoSize, adjusting if out of range
//
static void setFifoSize(Uns32 size) {
    if (size > MAX_FIFO) {
        bhmMessage(
            "W", PREFIX "_FTL",
            "Specified fifoSize=%d too large. Using max value %d",
            state.fifoSize,
            MAX_FIFO
        );
        size = MAX_FIFO;
    }
    state.fifoSize = size;
}

//
// Return size of the fifo
//
static Uns32 getFifoSize() {
    return state.fifoSize;
}

//
// Reset the indicated fifo buffer
//
static void resetFifo(fifoBufferP fifo) {
    fifo->rdp = 0;
    fifo->wrp = 0;
    fifo->full = False;
    fifo->empty = True;

    if (fifo == &Tx) {
        stopTxThread();
    }
    if (fifo == &Rx) {
        stopRxThread();
    }
    state.status = IDLE;
}

//
// Push element onto fifo buffer and update full and empty flags
// Return False if unable to complete because fifo is full
//
static Bool pushFifo (fifoBufferP fifo, Uns8 value) {
    if (fifo->full) {
        return False;
    } else {
        fifo->buffer[fifo->wrp] = value;
        fifo->wrp = (fifo->wrp + 1) % getFifoSize();

        // Test for buffer now being full
        fifo->full  = (fifo->rdp == fifo->wrp);
        fifo->empty = False;

        return True;
    }
}

static Bool pushRxFifo(Uns8 value) {
    return pushFifo(&Rx, value);
}

static Bool pushTxFifo(Uns8 value) {
    if(state.status == TX) {
        startTxThread();
    }
    return pushFifo(&Tx, value);
}

//
// View element on top of fifo buffer
// Return False if unable to complete because fifo is empty
//
static Bool viewFifo (fifoBufferP fifo, Uns8 *value) {
    if (fifo->empty) {
        return False;
    } else {
        *value = fifo->buffer[fifo->rdp];
        return True;
    }
}

//
// Pop element from fifo buffer and update full and empty flags
// Return False if unable to complete because fifo is empty
//
static Bool popFifo (fifoBufferP fifo, Uns8 *value) {

    if (!viewFifo(fifo, value)) {

        return False;

    } else {

        fifo->rdp = (fifo->rdp + 1) % getFifoSize();

        // Test for buffer now being empty
        fifo->empty = (fifo->rdp == fifo->wrp);
        fifo->full  = False;

        return True;
    }
}

//
// Return number of entries in the fifo
//
static Uns32 getFifoCount(fifoBufferP fifo) {

    Uns32 size = getFifoSize();

    if (fifo->full) {
        return size;
    } else if (fifo->empty) {
        return 0;
    } else if (fifo->wrp < fifo->rdp) {
        return (size - fifo->rdp + fifo->wrp);
    } else {
        return(fifo->wrp - fifo->rdp);
    }
}


void updateStatusRegisters() {
    // Update Status Registers
    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX"_STS","Write Interrupt Status Register 0x%04x",
                                InterruptStatus.value);
    }

    // This access will cause the ISR Write callback to trigger, so must be ignored
    ((Uns32*)handles.bport1)[BPORT1_AB_INTERRUPTSTATUS_OFFSET/(sizeof(Uns32))] = InterruptStatus.value;

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX"_STS","Write Status Register 0x%04x",
                                Status.value);
    }

    ((Uns32*)handles.bport1)[BPORT1_AB_STATUS_OFFSET/(sizeof(Uns32))] = Status.value;
}

static void updateInterrupt() {

    Uns32 intState = InterruptStatus.value & ~bport1_ab_data.InterruptMask.value;
    static Uns32 intStateLast = 0;

    if(intState != intStateLast) {
        intStateLast = intState;
        if (PSE_DIAG_MEDIUM) {
            bhmMessage("I", PREFIX"_INT","Update Interrupt (status 0x%04x / mask 0x%04x)",
                                    InterruptStatus.value,
                                    bport1_ab_data.InterruptMask.value);
        }
        if(intState) {
            // set
            ppmWriteNet(handles.intOut, 1);
        } else {
            // clear
            ppmWriteNet(handles.intOut, 0);
        }
    }
}

/////////////////////
// SERIAL DATA I/O //
/////////////////////

//
// Write data to the channel
// return 0 if channel is not available
//
static Int32 writeOutput(Uns8 *buffer, Uns32 length) {

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_WO","Output to channel %d I2C address 0x%x (Address 0x%08x) data 0x%02x (%d)",
                channelEnable, i2cAddress, (channelEnable*CHANNELADDRESSOFFSET)+i2cAddress, *buffer, *buffer);
    }

    // trigger character output event
    bhmTriggerEvent(state.charOut);

    int rc = 0;

    if (handles.I2C_Master) {
        if(ppmTryWriteAddressSpace(handles.I2C_Master, (channelEnable*CHANNELADDRESSOFFSET)+i2cAddress, length)) {
            rc = ppmWriteAddressSpace(handles.I2C_Master, (channelEnable*CHANNELADDRESSOFFSET)+i2cAddress, length, buffer);
        }
    }

    if (!rc) {
        if (!state.writeError) {
            // Only report error once
            bhmMessage("W", PREFIX"_IWE",
                                "I2C Master write Failed "
                                "at I2C address 0x%02x (channel base 0x%08x)",
                                i2cAddress,
                                channelEnable*CHANNELADDRESSOFFSET);
            state.writeError = True;
        }
    } else {
        state.writeError = False;
    }

    return rc;

}

Uns32 selectChannel(Uns8 data) {
    Uns32 channelEnable = 0;
    switch(data) {
        case 0x00:
            // default
        case 0x01:
            channelEnable = 0;
            break;
        case 0x02:
            channelEnable = 1;
            break;
        case 0x04:
            channelEnable = 2;
            break;
        case 0x08:
            channelEnable = 3;
            break;
        case 0x10:
            channelEnable = 4;
            break;
        case 0x20:
            channelEnable = 5;
            break;
        case 0x40:
            channelEnable = 6;
            break;
        case 0x80:
            channelEnable = 7;
            break;
        default:
            bhmMessage("W", PREFIX "_ISC", "Invalid Channel Select Value %d", data);
            break;
    }

    if (PSE_DIAG_MEDIUM) {
        bhmMessage("I", PREFIX "_CS","Selected channel %d zc702 %s zc706 %s",
                                    channelEnable,
                                    channelDeviceZC702[channelEnable],
                                    channelDeviceZC706[channelEnable]);
    }

    return channelEnable;
}


//
// Write tx data fifo to I2C master
//
static void channelWriteThread(void *user) {

    Uns8 c;
    Uns32 bitsToTransfer = DATA_BITS+ADDRESSS_BITS;     // used to calculate delay
                                                        // initially address and data to transfer

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_TS","Start Tx Thread (address 0x%x)", i2cAddress);
    }

    // Indicate status I2C active
    Status.bits.TXDV = 1;
    updateStatusRegisters();    // Write back the Interrupt Status and Status Registers

    if(i2cAddress == I2C_ADDRESS_BUSSWITCH) {
        // Programming the channel address
        if (popFifo(&Tx, &c)) {
            channelEnable = selectChannel(c);
        } else {
            bhmMessage("W", PREFIX "_ISC", "No Channel Select Data in FIFO");
        }

        if (PSE_DIAG_MEDIUM) {
            bhmMessage("I", PREFIX "_SC", "Set Channel %d", channelEnable);
        }

    } else {

        if (PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX "_TX","Start Process Tx FIFO (address 0x%x)", i2cAddress);
        }

        while (popFifo(&Tx, &c)) {

            if (PSE_DIAG_HIGH) {
                bhmMessage("I", PREFIX "_WR", "FiFo data %d (0x%x)", c, c);
            }

            // Software driver expects the I2C to be a slow interface
            // it assumes it can set interrupt control registers and send further data after starting a transfer
            // delay to ensure it can
            bhmWaitDelay(transmitRateDelay*bitsToTransfer);
            // sub-sequent transfers are only data
            bitsToTransfer = DATA_BITS;

            // Depending upon address decide device accessed and what to do
            switch (channelEnable) {
                case I2C_SWITCH_PMBUS :
                    if (PSE_DIAG_LOW) {
                        bhmMessage("I", PREFIX "_PMBUS", "Write I2C Addr 0x%x data %d (0x%x)", i2cAddress, c, c);
                    }
                    writeOutput(&c, sizeof(Uns8));
                    break;
                case I2C_SWITCH_PORT_EXP:
                    if(i2cAddress == I2C_ADDRESS_PORT_EXP) {
                        if (PSE_DIAG_LOW) {
                            bhmMessage("I", PREFIX "_PE", "Write I2C Addr 0x%x data %d (0x%x)", i2cAddress, c, c);
                        }
                    }
                    if (PSE_DIAG_HIGH) {
                        bhmMessage("I", PREFIX "_AWR", "Attempt write to channel %d I2C Addr 0x%x data %d (0x%x)", channelEnable, i2cAddress, c, c);
                    }
                    writeOutput(&c, sizeof(Uns8));
                    break;
                case -1 :
                    bhmMessage("W", PREFIX "_NA", "Attempting write before channel selected. I2C Addr 0x%x data %d (0x%x)", i2cAddress, c, c);
                    break;
                default:
                    if (PSE_DIAG_LOW) {
                        bhmMessage("I", PREFIX "_AWR", "Attempt write to channel %d I2C Addr 0x%x data %d (0x%x)", channelEnable, i2cAddress, c, c);
                    }
                    writeOutput(&c, sizeof(Uns8));
                    break;
            }

            updateInterrupt();

            if (PSE_DIAG_HIGH) {
                bhmMessage("I", PREFIX "_WRC", "Write Complete channel %d I2C Addr 0x%x", channelEnable, i2cAddress);
            }

            if (PSE_DIAG_HIGH) {
                bhmMessage("I", PREFIX "_WRF", "Check Tx FiFo");
            }

        }
    }

    // thread will terminate
    txThreadHandle = 0;

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_TC","Tx Transfer Complete");
    }

    // if no more data set end of transfer
    InterruptStatus.bits.COMP = 1;

    // Transmit not in progress, I2C inactive
    Status.bits.TXDV = 0;
    state.status = IDLE;

    updateStatusRegisters();    // Write back the Interrupt Status and Status Registers
    updateInterrupt();

}

//
// update fifo with read data and update flags
//
void readComplete(Uns8 * value) {

    Uns8 buffer = *value;
    // read ok or no read performed but must update with dummy data
    state.readError = False;

    // Push character into fifo
    pushRxFifo(buffer);

    if (PSE_DIAG_HIGH) {
        bhmMessage(
            "I", PREFIX "_URS",
            "read data ready: 0x%02x ('%c') @ %0.2fuS%s",
            buffer, isprint(buffer) ? buffer : ' ',
            bhmGetCurrentTime(),
            Rx.full ? " (RX now full)" : ""
        );
    }

    // Trigger charIn event on each character read
    bhmTriggerEvent(state.charIn);

    // data in fifo
    Status.bits.RXDV = 1;

    // decrement transfer count
    if(bport1_ab_data.TransferSize.value) {
        bport1_ab_data.TransferSize.value--;
    }

    if(bport1_ab_data.TransferSize.value) {
        // data being received
        InterruptStatus.bits.DATA = 1;
    } else {
        // data complete
        InterruptStatus.bits.COMP = 1;
    }
    updateStatusRegisters();    // Write back the Interrupt Status and Status Registers

}

//
// write rx data fifo from I2C slave
//
static void channelReadThread(void *user) {

    Uns32 bitsToTransfer = DATA_BITS;     // used to calculate delay, only data read

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_SR", "Started Rx Thread (%d)", bport1_ab_data.TransferSize.value);
    }

    if(i2cAddress == I2C_ADDRESS_BUSSWITCH) {
        // read back the channel address
        Uns8 channelValue = 1 << channelEnable;
        if (PSE_DIAG_LOW) {
            bhmMessage("I", PREFIX "_SC", "Read Channel %d (0x%x)", channelEnable, channelValue);
        }

        readComplete(&channelValue);

    } else {

        // how many words to read
        while(bport1_ab_data.TransferSize.value) {

            // Software driver expects the I2C to be a slow interface
            // it assumes it can set interrupt control registers after starting a transfer
            bhmWaitDelay(transmitRateDelay*bitsToTransfer);

            Uns8  buffer = 0;   // default data read value
            int   rc = 1;       // default to read ok

            // Depending upon address decide device accessed and what to do
            switch (channelEnable) {
                case I2C_SWITCH_PMBUS :
                    if (PSE_DIAG_LOW) {
                        bhmMessage("I", PREFIX "_PMBUS", "Read I2C Addr 0x%x", i2cAddress);
                    }
                    if (handles.I2C_Master && ppmTryReadAddressSpace(handles.I2C_Master, (channelEnable*CHANNELADDRESSOFFSET)+i2cAddress, 1)) {
                        rc = ppmReadAddressSpace(handles.I2C_Master, (channelEnable*CHANNELADDRESSOFFSET)+i2cAddress, 1, &buffer);
                    }
                    break;
                case -1 :
                    bhmMessage("W", PREFIX "_NA", "Attempting read before channel selected. I2C Addr 0x%x", i2cAddress);
                    break;
                default:
                    if (PSE_DIAG_LOW) {
                        bhmMessage("I", PREFIX "_RNS", "Attempt read from channel %d I2C Addr 0x%x", channelEnable, i2cAddress);
                    }
                    if (handles.I2C_Master && ppmTryReadAddressSpace(handles.I2C_Master, (channelEnable*CHANNELADDRESSOFFSET)+i2cAddress, 1)) {
                        rc = ppmReadAddressSpace(handles.I2C_Master, (channelEnable*CHANNELADDRESSOFFSET)+i2cAddress, 1, &buffer);
                    } else {
                        rc = 0; // cannot read
                    }
                    break;
            }
            if(!rc) {
                // read failed
                if (!state.readError) {
                    bhmMessage("W", PREFIX"_IWE",
                                        "I2C Master read Failed "
                                        "at I2C Addr 0x%02x (channel base 0x%08x)",
                                        i2cAddress,
                                        channelEnable*CHANNELADDRESSOFFSET);
                    state.readError = True;
                }

            } else {

                readComplete(&buffer);
            }

            // Update based on new state of fifo
            updateInterrupt();

            if (PSE_DIAG_HIGH) {
                bhmMessage("I", PREFIX "_WRC", "Read Complete channel %d I2C Addr 0x%x", channelEnable, i2cAddress);
            }

            if (PSE_DIAG_HIGH) {
                bhmMessage("I", PREFIX "_WRF", "Check Rx Transfer");
            }
        }
    }

    // thread will terminate
    rxThreadHandle = 0;

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_RC", "Rx thread Complete");
    }

}

////////////////////
// INITIALIZATION //
////////////////////

static void initFifos() {

    setFifoSize(DEFAULT_FIFO);

    // Initialize the fifos
    resetFifo(&Rx);
    resetFifo(&Tx);
}

static void initEvents() {
    state.charOut    = bhmCreateNamedEvent("charOut",    "I2C data output event");
    state.charOutAck = bhmCreateNamedEvent("charOutAck", "I2C data output event acknowledged");
    state.charIn     = bhmCreateNamedEvent("charIn",     "I2C data input event");
    state.charRead   = bhmCreateNamedEvent("charRead",   "I2C data read event");
    state.overrun    = bhmCreateNamedEvent("overrun",    "Transmit or Receive overrun");
    state.interrupt  = bhmCreateNamedEvent("interrupt",  "Interrupt generated");
}


//////////////////////////////// Callback stubs ////////////////////////////////

PPM_READ_CB(regNoDefinitionRead) {
    Uns32 offset = addr - handles.bport1;
    bhmMessage("W", PREFIX, "No Read Register Defined at offset 0x%04x", offset);
    return 0;
}

PPM_WRITE_CB(regNoDefinitionWrite) {
    Uns32 offset = addr - handles.bport1;
    bhmMessage("W", PREFIX, "No Write Register Defined at offset 0x%04x", offset);
}

PPM_WRITE_CB(i2cSlaveWrite) {
    bhmMessage("W", PREFIX "_SLVRD", "I2C Slave Mode not supported");
}

PPM_READ_CB(i2cSlaveRead) {
    bhmMessage("W", PREFIX "_SLVWR", "I2C Slave Mode not supported");
    return 0;
}

PPM_REG_WRITE_CB(intDisable) {

    bport1_ab_data.InterruptDisable.value &= 0xfffffd00;        // clear bits
    bport1_ab_data.InterruptDisable.value |= (data & 0x2ff);    // set bits
    bport1_ab_data.InterruptMask.value |= bport1_ab_data.InterruptDisable.value;

    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX "_ID", "Interrupt disable, 0x%02x/0x%02x",
                bport1_ab_data.InterruptDisable.value, bport1_ab_data.InterruptMask.value);
}

PPM_REG_WRITE_CB(intEnable) {

    bport1_ab_data.InterruptEnable.value &= 0xfffffd00;         // clear bits
    bport1_ab_data.InterruptEnable.value |= (data & 0x2ff);     // set bits
    bport1_ab_data.InterruptMask.value &= ~bport1_ab_data.InterruptEnable.value;

    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX "_IE", "Interrupt enable 0x%02x/0x%02x",
                bport1_ab_data.InterruptEnable.value, bport1_ab_data.InterruptMask.value);

}

PPM_REG_WRITE_CB(intClear) {

    InterruptStatus.value &= ~(data & 0x2ff);    // clear set bits

    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX "_ICLR", "Interrupt Clear (0x%04x) ISR 0x%04x",
                (data & 0x2ff), InterruptStatus.value);

    updateInterrupt();
}

PPM_REG_READ_CB(rdZero) {
    // intDiasable and intClear registers always read zero
    return 0;
}

PPM_REG_WRITE_CB(wrControl) {

    bport1_ab_data.Control.value &= 0xffff0080;
    bport1_ab_data.Control.value |= (data & 0xff7f);

    // calculate the byte transfer delay
     // clock = clockMHz*1000000;
    //  bit rate = clock/((A+1)*(B+1)
    // byte rate = bit rate/8
    // delay = 1/byte rate
    transmitRateDelay = ((double)((bport1_ab_data.Control.bits.DIV_A + 1) * (bport1_ab_data.Control.bits.DIV_B + 1)) / (double)clockMhz);

    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX "_SC", "Write Control 0x%04x : %s : %s : delay %0.0fuS)",
                    bport1_ab_data.Control.value,
                    bport1_ab_data.Control.bits.RW ? "RD"     : "WR",
                    bport1_ab_data.Control.bits.MS ? "Master" : "Slave",
                    transmitRateDelay);

//    if (!bport1_ab_data.Control.bits.MS) {
//        bhmMessage("E", PREFIX "_SLV", "Slave Mode Operation is not supported");
//    }

    if (bport1_ab_data.Control.bits.CLR_FIFO) {
        if(PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX "_SCCF", "Clear FIFOs");
        bport1_ab_data.Control.bits.CLR_FIFO = 0;
        // Initialize the fifos
        resetFifo(&Rx);
        resetFifo(&Tx);
        // clear transfer size
        bport1_ab_data.TransferSize.value = 0;
    }
}

PPM_REG_WRITE_CB(wrAddress) {

    if(!handles.I2C_Master) {

        if(PSE_DIAG_LOW)
            bhmMessage("W", PREFIX "_SAC", "Setting I2C address but no connection on I2C Master port");

    } else {
        if(state.status == IDLE) {
            *(Uns32*)user = (*(Uns32*)user & 0xfffffd00) | (data & 0x2ff);

            i2cAddress = *(Uns32*)user;

            if(PSE_DIAG_HIGH)
                bhmMessage("I", PREFIX "_SA", "Set I2C Addr 0x%04x (control 0x%04x)",
                                        i2cAddress, bport1_ab_data.Control.value);

            if(bport1_ab_data.Control.bits.RW) {

                // Start Rx Thread
                state.status = RX;
                startRxThread();

            } else {
                state.status = TX;
                if (getFifoCount(&Tx)) {
                    // there is data in TX FIFO but not started
                    // Start Tx Thread
                    startTxThread();
                }
            }

        } else {
            if(PSE_DIAG_LOW)
                bhmMessage("W", PREFIX "_SAE", "Setting I2C address while operation in progress");
        }
    }
}

PPM_REG_WRITE_CB(wrData) {

    Uns8 c = data & 0xff;

    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX "_WD", "I2C Write 0x%04x:0x%04x",
                                       i2cAddress, c);
    if(Tx.full) {
        InterruptStatus.bits.TX_OVF = 1;
        updateStatusRegisters();    // Write back the Interrupt Status and Status Registers
        updateInterrupt();
    } else {
        pushTxFifo(c);
    }

    // If address has been set any new data is written
    if (state.status == TX) {
        // Address is valid but not started yet
        // Start Tx Thread
        startTxThread();
    }
}

PPM_REG_WRITE_CB(wrStatus) {
    if(PSE_DIAG_MEDIUM)
        bhmMessage("W", PREFIX "_WS", "I2C Write read-only Status register (0x%x)", (Uns8)data);
}

PPM_REG_READ_CB(rdData) {

    Uns8 c = 0;

    if(popFifo(&Rx, &c)) {
        if(PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX "_RD", "I2C Read 0x%04x:0x%04x",
                                           i2cAddress, c);

        // Trigger charRead event on each character read
        bhmTriggerEvent(state.charRead);
        if(Rx.empty) {
            Status.bits.RXDV = 0;
            updateStatusRegisters();    // Write back the Interrupt Status and Status Registers
        }

    } else {
        // no receive data - underflow error
        if(PSE_DIAG_MEDIUM)
            bhmMessage("W", PREFIX "_RDU", "I2C Read Underflow");

        InterruptStatus.bits.RX_UNF = 1;

        updateStatusRegisters();    // Write back the Interrupt Status and Status Registers
        updateInterrupt();
    }

    return c;
}

PPM_REG_WRITE_CB(wrXSz) {
    bport1_ab_data.TransferSize.value = (data & 0xff);
    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX "_WXS", "I2C Transfer size %d",
                bport1_ab_data.TransferSize.value);

    // If address has been set any new data is written
    if (state.status == RX) {
        // Address is valid but not started yet
        // Start Rx Thread
        startRxThread();
    }
}

PPM_REG_READ_CB(rdXSz) {
    Uns32 count;
    if(bport1_ab_data.Control.bits.RW) {
        // Master Read - how many bytes still to receive
        count = bport1_ab_data.TransferSize.value;
        if(PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX "_RXS",
                            "I2C Transfer size "
                            "Read Mode - bytes still to receive %d",
                            count);
    } else {
        // Master write - number of bytes in fifo -1
        count = getFifoCount(&Tx);
        if(PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX "_RXS",
                            "I2C Transfer size "
                            "Write Mode - bytes in fifo %d",
                            count);
    }
    return count;
}

PPM_CONSTRUCTOR_CB(constructor) {

    state.status = IDLE;

    // Initialize the fifos
    initFifos();

    // Initialize events
    initEvents();

    periphConstructor();

    bhmUns32ParamValue("PCLK", &clockMhz);

}

PPM_DESTRUCTOR_CB(destructor) {

}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

