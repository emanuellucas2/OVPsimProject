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

#define PREFIX "IMX6_UART"

#include "pse.igen.h"

#define BPORT1 0
#include "pse.macros.igen.h"

#define MAX_FIFO_SIZE 32

// Internal state
static Uns32 read_fifo[MAX_FIFO_SIZE];
static Int32 read_pos;       // next location to add a received character
static Int32 read_count;     // number of characters to be read from rx fifo
static Int32 channel;        // serial socket/log channel
static bhmEventHandle charReceived, charSent;

#define DEFAULT_RX_DELAY 20000

// map generated names to shorthand
#define USR1         bport1_ab_data.UART_USR1
#define USR2         bport1_ab_data.UART_USR2
#define UCR1         bport1_ab_data.UART_UCR1
#define UCR2         bport1_ab_data.UART_UCR2
#define UTS          bport1_ab_data.UART_UTS
#define UFCR         bport1_ab_data.UART_UFCR
#define UTXD         bport1_ab_data.UART_UTXD
#define UMCR         bport1_ab_data.UART_UMCR

//////////////////////////////// behavior utility functions ////////////////////////////////

void updateInterrupt(void)
{
    // Interrupt generated when
    Bool f = 1 &&
             ((USR1.bits.TRDY & UCR1.bits.TRDYEN) ||
              (USR1.bits.RRDY & UCR1.bits.RRDYEN & (read_count >= UFCR.bits.RXTL)));
    static Bool current = 0;
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX"_UPDATE", "Int %d->%d (USR1 0x%02x USR2 0x%02x)", current, f, USR1.value, USR2.value);
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
            slot = MAX_FIFO_SIZE;
        if(PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX"_RX", "Rx fifo[%d] = 0x%x (%c)", slot, (char)value, (char)value);
        }
        read_fifo[slot] = value;
        read_count++;

        // set full flag
        if (read_count == MAX_FIFO_SIZE) {
            UTS.bits.RXFULL = 1;
        }

        // character received
        USR1.bits.RRDY = 1;
        USR2.bits.RDR  = 1;

    } else {
        if(PSE_DIAG_MEDIUM) {
            bhmMessage("I", PREFIX"_ROVR", "Rx fifo Overrun (lost %c)", (char)value);
        }
    }
    updateInterrupt();
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

//
// TX/RX Functions
//

PPM_REG_READ_CB(ReadUART_URXD) {
    // indicate data valid
    Uns32 flags = 0;
    // read fifo
    Uns32 c = read_fifo[read_pos];
    if (read_count > 0) {
        // read a character
        flags |= BPORT1_AB_UART_URXD_CHARRDY;

        read_count--;
        // character was received into last fifo position
        if(read_pos == MAX_FIFO_SIZE) {
            flags |= BPORT1_AB_UART_URXD_OVRRUN;
        }
        if (++read_pos == MAX_FIFO_SIZE)
            read_pos = 0;
    }

    if (read_count == 0) {
        UTS.bits.RXEMPTY = 1;          // signal Rx Empty
        USR2.bits.RDR    = 0;
    } else {
        // character received
        USR1.bits.RRDY = 1;
    }

    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX"_RR", "USR1 0x08%x USR2 0x08%x", USR1.value, USR2.value);
    }

    updateInterrupt();

    return (c | flags);
}

PPM_REG_WRITE_CB(WriteUART_UTXD) {
    // YOUR CODE HERE (WriteUART_UTXD)
    *(Uns32*)user = (*(Uns32*)user & 0xffffff00) | (data & 0xff);

    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX"_WR", "UTXD 0x02%x", UTXD.bits.DATA);
    }

     Uns8 ch = UTXD.bits.DATA;
     chr_write(&ch, 1);

     // interrupt TX FIFO empty
     // no output baud rate modeling - characters always sent immediately
     UTS.bits.TXEMPTY = 1;
     USR1.bits.TRDY   = 1;
     updateInterrupt();
}

//
// Control/Status Functions
//
PPM_REG_WRITE_CB(WriteUART_UMCR) {

    *(Uns32*)user = (*(Uns32*)user & 0xffff0000) | (data & 0xffff);
    if(UMCR.bits.MDEN ||
       UCR1.bits.IREN) {
       bhmMessage("W", PREFIX, "Only RS-232 UART Mode Supported");
    }
}

PPM_REG_WRITE_CB(WriteUART_UCR1) {

    *(Uns32*)user = (*(Uns32*)user & 0xffff0000) | (data & 0xffff);
    if(UMCR.bits.MDEN || UCR1.bits.IREN) {
        bhmMessage("W", PREFIX, "Only RS-232 UART Mode Supported");
        UMCR.bits.MDEN = 0;
        UCR1.bits.IREN = 0;
    }

    updateInterrupt();
}

PPM_REG_WRITE_CB(WriteUART_UCR2) {
    // YOUR CODE HERE (WriteUART_UCR2)
    *(Uns32*)user = (*(Uns32*)user & 0xffff0000) | (data & 0xffff);
}

PPM_REG_WRITE_CB(WriteUART_UCR3) {
    // YOUR CODE HERE (WriteUART_UCR3)
    *(Uns32*)user = (*(Uns32*)user & 0xffff0000) | (data & 0xffff);
}

PPM_REG_WRITE_CB(WriteUART_UCR4) {
    // YOUR CODE HERE (WriteUART_UCR4)
    *(Uns32*)user = (*(Uns32*)user & 0xffff0000) | (data & 0xffff);
}

PPM_REG_WRITE_CB(WriteUART_UFCR) {
    // YOUR CODE HERE (WriteUART_UFCR)
    *(Uns32*)user = (*(Uns32*)user & 0xffff0000) | (data & 0xffff);
}

PPM_REG_WRITE_CB(WriteUART_USR1) {

    // clear bits that are set
    *(Uns32*)user = (*(Uns32*)user & 0xffff624b) & ~(data & 0x9db8);
}

PPM_REG_WRITE_CB(WriteUART_USR2) {

    // clear bits that are set
    *(Uns32*)user = (*(Uns32*)user & 0xffff4229) & ~(data & 0xbdd6);
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


PPM_CONSTRUCTOR_CB(constructor) {
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX"_CONSTRUCT", "Start Constructor");
    }

    periphConstructor();

    // open serial channel
    channel = bhmSerOpenAuto();

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

