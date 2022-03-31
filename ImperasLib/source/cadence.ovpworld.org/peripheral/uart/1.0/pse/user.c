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
//                          Fri Jan  6 11:38:59 2012
//
////////////////////////////////////////////////////////////////////////////////

#include "pse.igen.h"

#define PREFIX "CDNS_UART"

#include "pse.igen.h"

#define BPORT1 0
#include "pse.macros.igen.h"

#define MAX_FIFO_SIZE 64

// Internal state
static Uns32 read_fifo[MAX_FIFO_SIZE];
static Int32 read_pos;
static Int32 read_count;
static Int32 channel;        // serial socket/log channel
static bhmEventHandle charReceived, charSent;

#define DEFAULT_RX_DELAY 20000

// map generated names to shorthand
#define int_status         bport1_ab_data.Chnl_int_sts.value
#define read_trigger       bport1_ab_data.Rcvr_FIFO_trigger_level.bits.RTRIG
#define read_idle_trigger  bport1_ab_data.Rcvr_timeout.bits.RTO
#define channel_status     bport1_ab_data.Channel_sts.value

static Uns32 int_mask;      // interrupts enabled mask

//////////////////////////////// behavior utility functions ////////////////////////////////

void update(void)
{
    Bool f = (int_status & int_mask) && 1;
    static Bool current = 0;
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX"_UPDATE", "Int %d->%d (level 0x%02x enabled 0x%02x)", current, f, int_status, int_mask);
    }
    if (f != current) {
        current = f;
        if(PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX"_INT", "%d", current);
        }
        ppmWriteNet(handles.irq, current);
    }
}

Bool can_receive(void) {
    return read_count < MAX_FIFO_SIZE;
}

void chr_write(Uns8 *data, Uns32 bytes){
    if(PSE_DIAG_HIGH) {
        if (bytes == 1) {
            bhmMessage("I", PREFIX"_TX", "Tx %c", (char)*data);
        } else {
            bhmMessage("W", PREFIX"_TX", "Sending multiple characters, first Tx %c", (char)*data);
        }
    }

    bhmSerWriteN(channel, data, bytes);
    bhmTriggerEvent(charSent);
}

void receiveByte(Uns32 value)
{
    if ( can_receive() ) {
        Int32 slot = read_pos + read_count;
        if (slot >= MAX_FIFO_SIZE)
            slot -= MAX_FIFO_SIZE;
        if(PSE_DIAG_MEDIUM) {
            bhmMessage("I", PREFIX"_RX", "Rx fifo[%d] = 0x%x (%c)", slot, (char)value, (char)value);
        }
        read_fifo[slot] = value;
        read_count++;

        if (read_count == MAX_FIFO_SIZE) {
            int_status |= BPORT1_AB_CHNL_INT_STS_RFUL;
        }
        // TODO: Specification is a little confusing here
        //       it appears that RTRIG is always set but only generates
        //       an interrupt if level >= trigger level
        //       This works with Linux kernel
//        if (read_count >= read_trigger) {
            int_status |= BPORT1_AB_CHNL_INT_STS_RTRIG;
//        }
    } else {
        if(PSE_DIAG_MEDIUM) {
            bhmMessage("I", PREFIX"_ROVR", "Rx fifo Overrun (lost %c)", (char)value);
        }
        int_status |= BPORT1_AB_CHNL_INT_STS_ROVR;
    }
    update();
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_WRITE_CB(regNoDefinitionRead) {
    Uns32 offset = addr - handles.bport1;
    bhmMessage("W", PREFIX, "No Write Register Defined at offset 0x%04x", offset);
}

PPM_READ_CB(regNoDefinitionWrite) {
    Uns32 offset = addr - handles.bport1;
    bhmMessage("W", PREFIX, "No Read Register Defined at offset 0x%04x", offset);
    return 0;
}

PPM_REG_READ_CB(ReadTX_RX_FIFO) {
    Uns32 c = read_fifo[read_pos];
    if (read_count > 0) {
        read_count--;
        if (++read_pos == MAX_FIFO_SIZE)
            read_pos = 0;
    }
    if (read_count == 0) {
        int_status |= BPORT1_AB_CHNL_INT_STS_REMPTY;       // signal Rx Empty
    }
    // TODO: Specification is a little confusing here
    //       it appears that RTRIG is always set but only generates
    //       an interrupt if level >= trigger level
    //       This works with Linux kernel
//    if (read_count >= read_trigger) {
        int_status |= BPORT1_AB_CHNL_INT_STS_RTRIG;        // Rx above trigger level
//    }

    update();

    return c;
}

PPM_REG_READ_CB(ReadIntrpt_mask) {
    // return the current state of interrupt
    return int_mask;
}

void setChannelStatus(){
    channel_status = BPORT1_AB_CHANNEL_STS_TEMPTY;            // Tx always empty
    if (read_count == 0) {
        channel_status |= BPORT1_AB_CHANNEL_STS_REMPTY;       // Rx empty
    }
    if (read_count >= read_trigger) {
        channel_status |= BPORT1_AB_CHANNEL_STS_RTRIG;        // Rx above trigger level
    }
}

PPM_REG_READ_CB(ReadChannel_sts) {
    setChannelStatus();

    return channel_status;
}

PPM_REG_WRITE_CB(WriteControl) {
    *(Uns32*)user = (*(Uns32*)user & 0xffffffe0) | (data & 0x1f);

    *(Uns32*)user &= ~0x3;    // clear reset bits (could just be masked on write?)
}

PPM_REG_WRITE_CB(WriteChnl_int_sts) {
    Uns32 clearBits = (data & 0x1fff);

    // clear the interrupt level bits corresponding to a 1 in this write
    int_status &= ~clearBits;
    update();
}

PPM_REG_WRITE_CB(WriteIntrpt_dis) {
    *(Uns32*)user = (*(Uns32*)user & 0xffffe000) | (data & 0x1fff);

    // disable interrupt bits set to 1
    int_mask &= ~(*(Uns32*)user);
    update();
}

PPM_REG_WRITE_CB(WriteIntrpt_en) {
    *(Uns32*)user = (*(Uns32*)user & 0xffffe000) | (data & 0x1fff);

    // enable interrupt bits set to 1
    int_mask |= *(Uns32*)user;
    update();
}

PPM_REG_WRITE_CB(WriteTX_RX_FIFO) {
    /* ??? Check if transmitter is enabled.  */
     Uns8 ch = data;
     chr_write(&ch, 1);

     // interrupt TX FIFO empty
     int_status |= BPORT1_AB_CHNL_INT_STS_TEMPTY;
     update();
}

//
// The polling process that gets characters
//
void getChars(void *user)
{
    while(1) {
        double d = DEFAULT_RX_DELAY;

        bhmWaitDelay(d);
        Uns8 c;
        if (bhmSerReadN(channel, &c, 1)) {
            bhmTriggerEvent(charReceived);
            receiveByte(c);
        }
    }
}

void openFiles(void)
{
    channel = bhmSerOpenAuto();
}

void initialState() {
    // Set the initial state of registers
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX"_INIT", "Initialize registers");
    }
    setChannelStatus();
}

PPM_CONSTRUCTOR_CB(constructor) {
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX"_CONSTRUCT", "Start Constructor");
    }

    periphConstructor();
    openFiles();

    Bool charMode;
    bhmBoolParamValue("charmode", &charMode);
    if (charMode) {
        if (PSE_DIAG_LOW) {
            bhmMessage("I", PREFIX"_MODE", "Asking client to run in Char Mode");
        }

        // IAC WILL ECHO IAC WILL SUPPRESS_GO_AHEAD IAC WONT LINEMODE
        // 255  251    1 255  251                 3 255  252       34
        Uns8 buffer[] = {255, 251, 1, 255, 251, 3, 255, 252, 34};
        Uns32 rc = bhmSerWriteN(channel, buffer, 9);

        if (PSE_DIAG_LOW) {
            bhmMessage("I", PREFIX"_MODE_INIT", "Sent %d initialisation chars to socket", rc);
        }
    }

    bhmCreateThread(getChars, NULL, "getchars", 0);
    charReceived = bhmCreateNamedEvent("Rx", "Character received");
    charSent     = bhmCreateNamedEvent("Tx", "Character sent");

    // Set initial state of registers
    initialState();
}

PPM_DESTRUCTOR_CB(destructor) {
    if(channel >= 0) {
        bhmSerClose(channel);
    }
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

