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

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#include "pse.igen.h"

#include "constants.h"

#define BUFFERLENGTH 16
#define DEBUG 0
#define PREFIX "16450"

#define REG_8BIT_BOUNDARY    1
#define REG_16BIT_BOUNDARY   2
#define REG_32BIT_BOUNDARY   4
#define REG_64BIT_BOUNDARY   8
#define MAX_BOUNDARY         REG_64BIT_BOUNDARY

#define WINDOW               8

#define CRYSTAL              18432000
#define PRESCALE             (8 * 2)

#define DEFAULT_RX_DELAY     20000

//
// All device statics are contained in this structure. Although there is no
// need to do this (file statics and program globals will work just as well in
// a PSE) this style makes it easy to locate the model's state and adds zero
// overhead to its execution.
//
typedef struct uart16450S {
    Uns32 registerAlign;         // default alignment on byte boundary

    // interrupt
    ppmNetHandle    intPortHandle;
    Bool            intState;

    // user events
    bhmEventHandle  gotChar;
    bhmEventHandle  sentChar;
    bhmEventHandle  txChar;
    bhmEventHandle  overrun;
    bhmEventHandle  interrupt;

    // duplex channel connection
    Int32    channel;

    // true means write to the simulator log
    Bool     log;

    // UART model state
    Uns16 divider;
    Uns8  rbr; /* receive register */
    Uns8  tbr; /* tx register */
    Uns8  ier;
    Uns8  iir; /* read only */
    Uns8  lcr;
    Uns8  mcr;
    Uns8  lsr; /* read only */
    Uns8  msr; /* read only */
    Uns8  scr;
    /* NOTE: this hidden state is necessary for tx irq generation as
       it can be reset while reading iir */
    Int32 thr_ipending;
    Int32 last_break_enable;

    Bool  uart16550;        // not used yet
    Bool  simulateBaud;     // delay tx characters, rather than sending immediately
    Bool  charMode;         // Ask client to run in character mode
    Bool  writeError;       // An error has occurred on most recent write
    Uns32 usec_delay;       // time between characters

} uart16450;

//
// Statics
//
static  uart16450 device;  // only one uart, but could support several

////////////////////////////////// RECORD / REPLAY ////////////////////////////////////

//
// extract register bits and calculate baud rate
//
static inline Uns32 data_bits   (void) { return (device.lcr & 0x03) + 5;     }
static inline Uns32 parity_bits (void) { return (device.lcr & 0x08) != 0;    }
static inline Uns32 parity_sense(void) { return (device.lcr & 0x10) != 0;    }
static inline Uns32 stop_bits   (void) { return (device.lcr & 0x04) ? 2 : 1; }
static inline Uns32 start_bits  (void) { return 1;                           }

static inline Uns32 baud_rate   (void) { return CRYSTAL / ((device.divider ?: 1)  * PRESCALE); }

static inline char  parity      (void) { return parity_bits() ? (parity_sense() ? 'E' : 'O') : 'N'; }

static inline Uns32 bits(void) {
    return start_bits() + data_bits() + parity_bits() + stop_bits();
}


static inline Uns32 microseconds_per_char(void) {
    return (bits() * 1000000) /  baud_rate();
}

static void serial_update_parameters(void)
{
    device.usec_delay = microseconds_per_char();
    if (PSE_DIAG_MEDIUM) {
        bhmMessage("I", PREFIX, "speed=%d  parity=%c  data bits=%d  total bits=%d\n",
           baud_rate(),
           parity(),
           data_bits(),
           bits()
        );
        bhmMessage("I", PREFIX, "character delay=%dusec\n", device.usec_delay);
    }
}

static NOINLINE void updateNet(Bool set){
    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "interrupt=%d", set);
    ppmWriteNet(device.intPortHandle, set);
}

//
// propagate the interrupt
//
static void setInt(Bool set)
{
    if(device.intPortHandle && set != device.intState){
        device.intState = set;
        updateNet(set);
        if (set) {
            if (PSE_DIAG_HIGH) {
                bhmMessage("I", PREFIX, "Trigger device.interrupt");
            }
            bhmTriggerEvent(device.interrupt);
        }
    }
}

static void serial_update_irq(void)
{
    if ((device.lsr & UART_LSR_DR) && (device.ier & UART_IER_RDI)) {
        device.iir = UART_IIR_RDI;
    } else if (device.thr_ipending && (device.ier & UART_IER_THRI)) {
        device.iir = UART_IIR_THRI;
    } else {
        device.iir = UART_IIR_NO_INT;
    }
    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Update interrupts (%s) IIR 0x%x (IER 0x%x) - Int State %s",
                (device.iir == UART_IIR_NO_INT) ? "-": "INT",
                device.iir,
                device.ier,
                ((device.intPortHandle) ? ((ppmReadNet(device.intPortHandle) != 0) ? "SET": "CLEAR") : "-"));
    }
    if (device.iir != UART_IIR_NO_INT) {
        setInt(1);
    } else {
        setInt(0);
    }
}

void overrun(void)
{
    device.lsr |= UART_LSR_OE;
    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Trigger device.overrun");
    }
    bhmTriggerEvent(device.overrun);
}

void receiveByte(Int32 ch)
{
    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Receive Data Byte '%c'", ch);
    }
    device.rbr = ch;
    if (device.lsr & UART_LSR_DR) {
        overrun();
    }
    device.lsr |= UART_LSR_DR;
    serial_update_irq();
}

static void uartReset (void)
{
    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Reset");
    }
    device.lsr = UART_LSR_TEMT | UART_LSR_THRE;
    device.iir = UART_IIR_NO_INT;
    device.msr = UART_MSR_DCD | UART_MSR_DSR | UART_MSR_CTS;
}

static void openFiles(void)
{
    device.channel = bhmSerOpenAuto();
}

static void writeOutput(Uns8 ch)
{

    if (device.channel >= 0) {

        Uns32 rc = bhmSerWriteN(device.channel, &ch, 1);

        if (rc == 1) {
            return;
        }
        // closed or broken?
        Uns32 error = bhmSerLastError(device.channel);
        if (error) {
            if (!device.writeError) {
                bhmMessage("W", PREFIX, "Serial channel write error. Channel closed?");
                device.writeError = True;
            }
        } else {
            bhmMessage("W", PREFIX, "Serial channel closed");
        }
    }
}

//
// The polling process that gets characters at the specified baud-rate
//
#define MAXREAD 256
static void getChars(void *user)
{

    while(1) {
        Uns8  buffer[MAXREAD];
        Int32 bytes;

        double d = device.simulateBaud
            ? device.usec_delay
            : DEFAULT_RX_DELAY;

        //
        // Blocking read
        //
        bytes = bhmSerReadB(device.channel, buffer, MAXREAD);

        if(bytes == 0 && bhmSerLastError(device.channel) > 0) {
            bhmMessage("W", PREFIX, "Serial channel closed");
            break;
        }
        //
        // Do not allow overruns
        //
        if (device.charMode && (device.lsr & UART_LSR_DR)) {
            continue;
        }

        Uns32 i;
        for(i=0; i<bytes; i++) {
            if (PSE_DIAG_HIGH) {
                bhmMessage("I", PREFIX, "waiting...'");
            }
            bhmWaitDelay(d);
            Uns8 c = buffer[i];

            if (PSE_DIAG_HIGH) {
                bhmMessage("I", PREFIX, "Get Character Input '%c'", c);
            }

            // If Character Mode strip Null characters
            // charMode c :: ignore
            //    0     0 :: False
            //    0     1 :: False
            //    1     0 :: True
            //    1     1 :: False
            if (device.charMode && (c==0)) {
            } else {
                bhmTriggerEvent(device.gotChar);
                receiveByte(c);
            }
        }
    }
}

//
// Used by either the register callback (if not simulating timing)
// Or by the putchars task if (simulating timing).
// Completes the transmit character operation.
//
static void transmitByte() {

    writeOutput(device.tbr);

    device.thr_ipending = 1;
    device.lsr |= UART_LSR_THRE;
    device.lsr |= UART_LSR_TEMT;

    bhmTriggerEvent(device.sentChar);

    serial_update_irq();
}

//
// Process that delays the transmission of each character.
//
static void putChars(void *user)
{
    while(1) {
        bhmWaitEvent(device.txChar);
        if (device.usec_delay > 0) {
            bhmWaitDelay(device.usec_delay);
        }
        transmitByte();
    }
}

///////////////////////////////////////////////////////////////////////////////
// VIEW
///////////////////////////////////////////////////////////////////////////////

static PPM_VIEW_CB(viewReg8) {
    *(Uns8*)data = *(Uns8*)user;
}

static PPM_VIEW_CB(viewReg16) {
    *(Uns16*)data = *(Uns16*)user;
}

///////////////////////////////////////////////////////////////////////////////
// READ
///////////////////////////////////////////////////////////////////////////////

static PPM_REG_READ_CB(readRbr) {
    Uns8 ret;
    if (device.lcr & UART_LCR_DLAB) {
        ret = device.divider & 0xff;
    } else {
        ret = device.rbr;
        device.lsr &= ~(UART_LSR_DR | UART_LSR_BI);
        serial_update_irq();
    }
    return ret;
}

static PPM_REG_READ_CB(readIer) {
    Uns8 ret;
    if (device.lcr & UART_LCR_DLAB) {
        ret = (device.divider >> 8) & 0xff;
    } else {
        ret = device.ier;
    }
    return ret;
}

static PPM_REG_READ_CB(readIir) {
    Uns8 ret = device.iir;
    /* reset THR pending bit */
    if ((ret & 0x7) == UART_IIR_THRI)
        device.thr_ipending = 0;
    serial_update_irq();
    return ret;
}

static PPM_REG_READ_CB(readMsr) {
    Uns8 ret;
    if (device.mcr & UART_MCR_LOOP) {
        /* in loopback, the modem output pins are connected to the inputs */
        ret = (device.mcr & 0x0c) << 4;
        ret |= (device.mcr & 0x02) << 3;
        ret |= (device.mcr & 0x01) << 5;
    } else {
        ret = device.msr;
    }
    return ret;
}

static PPM_REG_READ_CB(readReg) {
    return *(Uns8*)user;
}

///////////////////////////////////////////////////////////////////////////////
// WRITE
///////////////////////////////////////////////////////////////////////////////

static PPM_REG_WRITE_CB(writeTbr) {
    if (device.lcr & UART_LCR_DLAB) {
        device.divider = (device.divider & 0xff00) | data;
        serial_update_parameters();
    } else {
        if (!device.thr_ipending) {
            // detecting tx overrun is more complicated than this.
            // overrun();
        }
        device.thr_ipending = 0;
        device.lsr &= ~UART_LSR_THRE;
        serial_update_irq();

        device.tbr = data;
        if (device.simulateBaud) {
            bhmTriggerEvent(device.txChar);
        } else {
            transmitByte();
        }
    }
}

static PPM_REG_WRITE_CB(writeIer) {
    if (device.lcr & UART_LCR_DLAB) {
        device.divider = (device.divider & 0x00ff) | (data << 8);
        serial_update_parameters();
    } else {
        device.ier = data & 0x0f;
        if (device.lsr & UART_LSR_THRE) {
            device.thr_ipending = 1;
        }
        serial_update_irq();
    }
}

static PPM_REG_WRITE_CB(writeMcr) {
    device.mcr = data & 0x1f;
}

static PPM_REG_WRITE_CB(writeScr) {
    device.scr = data;
}

static PPM_REG_WRITE_CB(writeLcr) {
    Int32 break_enable;
    device.lcr = data;
    serial_update_parameters();
    break_enable = (data >> 6) & 1;
    if (break_enable != device.last_break_enable) {
        device.last_break_enable = break_enable;
    }
}

//
// UART has 2 addressing schemes: byte-wise and word-wise
//
static Uns32 winAddr(Uns8 base) {
    return base * device.registerAlign;
}

static void createRegisters(void) {
    Uns32 windowSize = WINDOW * device.registerAlign;

    void *w = ppmCreateSlaveBusPort("bport1", windowSize);
    //                name    description        base offset size read    write      view      user data
    ppmCreateRegister("rbr", "receive byte",     w, winAddr(0), 1, readRbr, NULL,     viewReg8, &device.rbr, True);
    ppmCreateRegister("tbr", "transmit byte",    w, winAddr(0), 1, NULL,    writeTbr, NULL,     NULL,        True);
    ppmCreateRegister("ier", "interrupt enable", w, winAddr(1), 1, readIer, writeIer, viewReg8, &device.ier, True);
    ppmCreateRegister("iir", "interrupt input",  w, winAddr(2), 1, readIir, NULL,     viewReg8, &device.iir, True);
    ppmCreateRegister("lcr", "line control",     w, winAddr(3), 1, readReg, writeLcr, viewReg8, &device.lcr, True);
    ppmCreateRegister("mcr", "modem control",    w, winAddr(4), 1, readReg, writeMcr, viewReg8, &device.mcr, True);
    ppmCreateRegister("lsr", "line status",      w, winAddr(5), 1, readReg, NULL,     viewReg8, &device.lsr, True);
    ppmCreateRegister("msr", "modem status",     w, winAddr(6), 1, readMsr, NULL,     viewReg8, &device.msr, True);
    ppmCreateRegister("scr", "status/control",   w, winAddr(7), 1, readReg, writeScr, viewReg8, &device.scr, True);
    ppmCreateInternalRegister("div", "baud rate divider", 2, viewReg16, &device.divider);
}

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    device.txChar        = bhmCreateNamedEvent("txChar",    "About to transmit");
    device.sentChar      = bhmCreateNamedEvent("charOut",   "Uart character output event");
    device.overrun       = bhmCreateNamedEvent("overrun",   "Transmit or Receive overrun");
    device.interrupt     = bhmCreateNamedEvent("interrupt", "Interrupt generated");
    device.gotChar       = bhmCreateNamedEvent("charIn",    "Uart character input event");

    Uns32 defaultBaud;
    if (bhmUns32ParamValue("defaultbaud", &defaultBaud) && PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX, "Default Baud, changed to %d.", device.divider);
    }
    device.divider = defaultBaud;

    serial_update_parameters();

    openFiles();
    uartReset();

    device.registerAlign = REG_8BIT_BOUNDARY; // Set default to byte boundary;

    bhmBoolParamValue("simulatebaud", &device.simulateBaud);
    if(device.simulateBaud && PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX, "Simulating transmission delays.");
    }

    bhmBoolParamValue("uart16550", &device.uart16550);
    if (device.uart16550 && PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX, "Simulating 16550A Fifos.");
    }

    Bool charMode;
    bhmBoolParamValue("charmode", &charMode);
    if (charMode) {
        if (PSE_DIAG_LOW) {
            bhmMessage("I", PREFIX, "Asking client to run in Char Mode");
        }
        device.charMode = 1;

        // IAC WILL ECHO IAC WILL SUPPRESS_GO_AHEAD IAC WONT LINEMODE
        // 255  251    1 255  251                 3 255  252       34
        Uns8 buffer[] = {255, 251, 1, 255, 251, 3, 255, 252, 34};
        Uns32 rc = bhmSerWriteN(device.channel, buffer, 9);
        bhmMessage("I", PREFIX, "Sent %d initialisation chars to socket", rc);
    }

    device.intPortHandle = ppmOpenNetPort("intOut");
    if(!device.intPortHandle && PSE_DIAG_MEDIUM) {
        bhmMessage("W", PREFIX, "Net Port intOut not Opened\n");
    }
    createRegisters();

    // create the thread which causes characters to come in.
    bhmCreateThread(getChars, NULL, "getchars", 0);
    if (device.simulateBaud) {
        bhmCreateThread(putChars, NULL, "putchars", 0);
    }

    if(PSE_DIAG_LOW) bhmMessage("I", PREFIX, "main done\n");

    return;
}


PPM_DESTRUCTOR_CB(destructor) {
    if(device.channel >= 0) {
        bhmSerClose(device.channel);
    }
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}

