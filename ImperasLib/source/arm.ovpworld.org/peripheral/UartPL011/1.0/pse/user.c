/*
 * QEMU Uart Emulator.
 *
 * Copyright (c) 2003 Fabrice Bellard
 * Copyright (c) 2006 Openedhand Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
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

#include <string.h>

#include "pse.igen.h"

#define BPORT1 0
#include "pse.macros.igen.h"

//////////////////////////////// Callback stubs ////////////////////////////////

// Internal state
variantT    uType;
static Uns32 read_fifo[16];
static Int32 read_pos;
static Int32 read_count;
static Int32 read_trigger;
static Int32 channel = -1;        // serial socket/log channel
static bhmEventHandle charReceived, charSent;

// control for direct read/write
static Bool directRW;
static Uns32 write_fifo[16];
static Int32 write_pos;
static Int32 write_count;

#define DEFAULT_RX_DELAY 20000
#define DEFAULT_TX_DELAY 20000
// map generated names to shorthand
//#define flags          bport1_ab_data.flags.value
#define flags          *(Uns32*)(handles.bport1+BPORT1_AB_FLAGS_OFFSET)
#define BPORT1_AB_FLAGS_TXFE   (0x1 << 7)
#define BPORT1_AB_FLAGS_RXFF   (0x1 << 6)
#define BPORT1_AB_FLAGS_TXFF   (0x1 << 5)
#define BPORT1_AB_FLAGS_RXFE   (0x1 << 4)

#define BPORT1_AB_FLAGS_ECROE  (0x1 << 3)

//#define int_level      bport1_ab_data.int_level.value
#define int_level      *(Uns32*)(handles.bport1+BPORT1_AB_INT_LEVEL_OFFSET)
#define BPORT1_AB_INT_LEVEL_TX   (0x1 << 5)
#define BPORT1_AB_INT_LEVEL_RX   (0x1 << 4)
#define BPORT1_AB_INT_LEVEL_OE   (0x1 << 10)

#define int_enabled    bport1_ab_data.int_enabled.value
#define dmacr          bport1_ab_data.dmacr.value
#define lcr            bport1_ab_data.lcr.value
#define cr             bport1_ab_data.cr.value
#define ifl            bport1_ab_data.ifl.value
#define ecr            bport1_ab_data.ecr.value

#define RXFF           BPORT1_AB_FLAGS_RXFF
#define RXFE           BPORT1_AB_FLAGS_RXFE
#define TXFF           BPORT1_AB_FLAGS_TXFF
#define TXFE           BPORT1_AB_FLAGS_TXFE

#define FEN            BPORT1_AB_LCR_FEN

#define UARTTXINTR     BPORT1_AB_INT_LEVEL_TX
#define UARTRXINTR     BPORT1_AB_INT_LEVEL_RX
#define UARTOEINTR     BPORT1_AB_INT_LEVEL_OE

//
// ID
//
static const unsigned char id[2][8] = {
  { 0x11, 0x10, 0x14, 0x00, 0x0d, 0xf0, 0x05, 0xb1 }, /* VARIANT_ARM */
  { 0x11, 0x00, 0x18, 0x01, 0x0d, 0xf0, 0x05, 0xb1 }, /* PL011_LUMINARY */
};

void update(void)
{
    Bool f = (int_level & int_enabled) && 1;
    static Bool current = 0;
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", "PL011_UPDATE", "Int %d->%d (level 0x%02x enabled 0x%02x)", current, f, int_level, int_enabled);
    }
    if (f != current) {
        current = f;
        if(PSE_DIAG_HIGH) {
            bhmMessage("I", "PL011_INT", "%d", current);
        }
        ppmWriteNet(handles.irq, current);
    }
}

Bool can_receive(void) {
    if (lcr & FEN)      // check FIFO enabled
        return read_count < 16;
    else
        return read_count < 1;
}

void chr_write(Uns8 *data, Uns32 bytes){
    if(PSE_DIAG_HIGH) {
        if (bytes == 1) {
            bhmMessage("I", "PL011_TX", "Tx %c", (char)*data);
        } else {
            bhmMessage("W", "PL011_TX", "Sending multiple characters, first Tx %c", (char)*data);
        }
    }

    bhmSerWriteN(channel, data, bytes);
    bhmTriggerEvent(charSent);
}

//
// This continuously runs in its own thread,
// checking for data to write in the TX fifo
// when the transmiter is enabled
//
static void directWriteThread(void *user) {

    while (1) {

        double d = DEFAULT_TX_DELAY;

        bhmWaitDelay(d);

        if(write_count) {
            // check characters in fifo
            Uns32 c = write_fifo[write_pos];

            if(PSE_DIAG_HIGH) {
                bhmMessage("I", "PL011_TX", "Tx fifo[%d] = 0x%x (%c)", write_pos, (char)c, (char)c);
            }

            ppmWriteNet(handles.DirectWrite, c );
            bhmTriggerEvent(charSent);

            if (write_count > 0) {
                write_count--;
                if (++write_pos >= 16)
                    write_pos = 0;
            }
            if (write_count == 0) {
                flags |= TXFE;          // signal Tx Empty
                if (!(lcr & FEN) ) {
                    flags &= ~TXFF;     // if Fifo not enabled clear Rx full
                }

                int_level |= UARTTXINTR;

                update();
            }
        }
    }
}

void receiveByte(Uns32 value)
{
    if(read_count == 16) {
        if(PSE_DIAG_MEDIUM) {
            bhmMessage("I", "PL011_RXFF", "Rx fifo full");
        }
        ecr       |= BPORT1_AB_FLAGS_ECROE;	// indicate overflow
        int_level |= UARTOEINTR;
        flags     |= RXFF;                  // indicate Rx Full
        int_level |= UARTRXINTR;

        update();

        return;
    }
    Int32 slot = read_pos + read_count;
    if (slot >= 16) slot -= 16;

    if(PSE_DIAG_HIGH) {
        bhmMessage("I", "PL011_RX", "Rx fifo[%d] = 0x%x (%c)", slot, (char)value, (char)value);
    }
    read_fifo[slot] = value;
    read_count++;
    flags &= ~RXFE;
    if ((cr & 0x10) || (read_count == 16) || (!(lcr & FEN) && read_count >= 1)) {
        flags |= RXFF;
    }
    if (read_count >= read_trigger) {
        int_level |= UARTRXINTR;
        update();
    }
}

PPM_REG_READ_CB(readDR) {
//TODO: is this right??
//    flags &= ~TXFE;
    Uns32 c = read_fifo[read_pos];
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", "PL011_RDR", "Read %c 0x%x Rx Fifo[%d]", c, c, read_pos);
    }

    if (read_count > 0) {
        read_count--;
        if (++read_pos >= 16)
            read_pos = 0;
    }
    if (read_count == 0) {
        flags |= RXFE;          // signal Rx Empty
        if (!(lcr & FEN) ) {
            flags &= ~RXFF;     // if Fifo not enabled clear Rx full
        }
    }
    Uns32 oe = (ecr & BPORT1_AB_FLAGS_ECROE);
    // clear overflow
    ecr &= ~BPORT1_AB_FLAGS_ECROE;

    if (read_count == read_trigger - 1)
        int_level &= ~UARTRXINTR;
    update();
    return c | (oe << 11);	// include overflow flag
}

PPM_REG_READ_CB(readECR) {
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", "PL011_ECR", "Read 0x%x", ecr);
    }

    return ecr;
}

PPM_NBYTE_READ_CB(readID) {

    Uns32 reg  = (offset-0xfe0)/0x4;
    Uns32 v    = id[uType][reg];

    if(PSE_DIAG_HIGH) {
        bhmMessage("I", "PL011_ID", "Read 0x%x", v);
    }

    *(Uns32*)data = v;
}

PPM_REG_READ_CB(readMIS) {
    Uns32 maskedIntState = int_level & int_enabled;
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", "PL011_MIS", "Read 0x%x", maskedIntState);
    }
    return maskedIntState;
}

PPM_REG_WRITE_CB(writeDMA) {
    *(Uns32*)user = data;
    if (dmacr & 3)
        bhmMessage("E", "PL011_DNS", "DMA mode not supported");
}

PPM_REG_WRITE_CB(writeECR) {
	// any write clears
	ecr = 0;
}

PPM_REG_WRITE_CB(writeDR) {
    /* ??? Check if transmitter is enabled.  */
     Uns8 ch = data;
     if(PSE_DIAG_HIGH) {
         bhmMessage("I", "PL011_WDR", "Write %c 0x%x", ch, ch);
     }
     if (!directRW) {
         // all characters sent immediately
         chr_write(&ch, 1);

         int_level |= UARTTXINTR;

         update();
     } else {
         // character added to buffer to send
         Int32 slot = write_pos + write_count;
         if (slot >= 16)
             slot -= 16;
         if(PSE_DIAG_HIGH) {
             bhmMessage("I", "PL011_TX", "Tx fifo[%d] = 0x%x (%c)", slot, (char)ch, (char)ch);
         }
         write_fifo[slot] = ch;
         write_count++;
         flags &= ~TXFE;
         if ((cr & 0x10) || (write_count == 16) || (!(lcr & FEN) && write_count >= 1)) {
             // fifo full
             flags     |= TXFF;
             int_level |= UARTTXINTR;
             update();
         }
     }
}

PPM_REG_WRITE_CB(writeICR) {
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", "PL011_ICR", "Write 0x%x", data);
    }
    int_level &= (~data) & 0x7FF;
    update();
}

PPM_REG_WRITE_CB(writeIMSC) {
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", "PL011_IMSC", "Write 0x%x", data);
    }
    int_enabled = data;
    update();
}

PPM_REG_WRITE_CB(writeIFL) {
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", "PL011_IFL", "Write 0x%x", data);
    }
    ifl = data;
    read_trigger = 1;
}

PPM_REG_WRITE_CB(writeLCR) {
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", "PL011_LCR", "Write 0x%x", data);
    }
    lcr = data;
    read_trigger = 1;
}

//
// The polling process that gets characters
//
void getChars(void *user)
{
    while(1) {
        double d = DEFAULT_RX_DELAY;

        bhmWaitDelay(d);
        if (can_receive()) {
            Uns8 c;
            if (bhmSerReadN(channel, &c, 1)) {
                bhmTriggerEvent(charReceived);
                receiveByte(c);
            }
        }
    }
}

void openFiles(void)
{
    channel = bhmSerOpenAuto();
}

//
// Callback on write to directRead input net
//
PPM_NET_CB(directReadCB) {

    Uns8 c = value & 0xff;

    // just receive into fifo
    receiveByte(c);
    bhmTriggerEvent(charReceived);
}

void initialState() {
    // Set the initial state of registers
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", "PL011_INIT", "Initialize registers");
    }

    // Set Transmit Fifo empty
    flags |= TXFE;
}

PPM_CONSTRUCTOR_CB(constructor) {
    uType = VARIANT_ARM;
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", "PL011_CONSTRUCT", "Start Constructor");
    }

    bhmEnumParamValue("variant", &uType);

    periphConstructor();

    bhmBoolParamValue("directReadWrite", &directRW);

    if(directRW && !(handles.DirectRead && handles.DirectWrite)) {
        bhmMessage(
            "E", "PL011_DRWNC",
            "Uart initialized in direct connect mode but DirectRead/DirectWrite nets are not connected"
        );
    }

    if (directRW) {

        // Create write thread in direct mode
        bhmCreateThread(directWriteThread, NULL, "directWriteThread", 0);

        if (PSE_DIAG_LOW) {
            bhmMessage(
                "I", "PL011_UID",
                "Uart initialized in direct connect mode"
            );
        }

    } else {

        openFiles();

        Bool charMode;
        bhmBoolParamValue("charmode", &charMode);
        if (charMode) {
            if (PSE_DIAG_LOW) {
                bhmMessage("I", "PL011", "Asking client to run in Char Mode");
            }

            // IAC WILL ECHO IAC WILL SUPPRESS_GO_AHEAD IAC WONT LINEMODE
            // 255  251    1 255  251                 3 255  252       34
            Uns8 buffer[] = {255, 251, 1, 255, 251, 3, 255, 252, 34};
            Uns32 rc = bhmSerWriteN(channel, buffer, 9);

            if (PSE_DIAG_LOW) {
                bhmMessage("I", "PL011", "Sent %d initialisation chars to socket", rc);
            }
        }

        read_trigger = 1;
        bhmCreateThread(getChars, NULL, "getchars", 0);

    }   // end direct

    charReceived = bhmCreateNamedEvent("Rx", "Character received");
    charSent     = bhmCreateNamedEvent("Tx", "Character sent");

    // Set initial state of registers
    initialState();

}

PPM_DESTRUCTOR_CB(closeDown) {
    if(!directRW && (channel >= 0)) {
        bhmSerClose(channel);
    }
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

