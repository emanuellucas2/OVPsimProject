/*
 * QEMU MALTA FPGA
 *
 * Copyright (c) 2003-2004 Fabrice Bellard
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
// *78
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

#define PREFIX "MaltaFPGA"

#include <stdio.h>
#include <string.h>

#include "pse.igen.h"

#include "maltaFpga.h"

static unsigned char eeprom24c0x_read(void);
static void eeprom24c0x_write(int scl, int sda);

static unsigned char fpga_Window [0x1000];

// The UART is modelled separately to the Malta FPGA
// so the following mapping is applied
#define HIGH_WINDOW 0x600
#define HIGH_WINDOW_BASE 0xa00
// 0x0a00-0x0fff    Malta FPGA
// 0x0900-0x09ff    external UART (CBUS)
#define LOW_WINDOW 0x900
// 0x0000-0x08ff    Malta FPGA

static MaltaFPGAState fpgaState;

static Bool finishOnReset = False;

/*************************************************************
 * Byte Swapping Functions
 *************************************************************/

Bool endianBig = False;


static PPM_READ_CB(regs_Read_portCB){

    Uns32 start = PTR_TO_UNS32(user);
    Uns32 off = (unsigned char*)addr - &fpga_Window[start];
    Int32 val = 0;

    switch(off) {
        /* SWITCH Register */
        case 0x00200:
            if (BHM_DIAG_HIGH) bhmMessage("I", PREFIX, " SWITCH Register 0x%08x\n", fpgaState.switches);
            val = fpgaState.switches;
        break;

        /* NMISTATUS Register */
        case 0x00024:
            if (BHM_DIAG_HIGH) bhmMessage("I", PREFIX, " NMISTATUS Register\n");
            val = 0x00000000;
        break;

        /* NMIACK Register */
        case 0x00104:
            if (BHM_DIAG_HIGH) bhmMessage("I", PREFIX, " NMIACK Register\n");
            val = 0x00000000;
        break;

        /* STATUS Register */
        case 0x00208:
            if (BHM_DIAG_HIGH) bhmMessage("I", PREFIX, " STATUS Register\n");
            val = 0x00000010;
            break;

        /* JMPRS Register */
        case 0x00210:
            if (BHM_DIAG_HIGH) bhmMessage("I", PREFIX, " JMPRS Register\n");
            val = 0x00;
            break;

        /* LEDBAR Register */
        case 0x00408:
            val = fpgaState.leds;
            if (BHM_DIAG_HIGH) bhmMessage("I", PREFIX, " LEDBAR Register (0x%02x)\n",fpgaState.leds);
            break;

        /* BRKRES Register */
        case 0x00508:
            if (BHM_DIAG_HIGH) bhmMessage("I", PREFIX, " BRKRES Register (0x%02x)\n",fpgaState.brk);
            val = fpgaState.brk;
            break;

        /* UART Registers are handled directly by the serial device */

        /* GPOUT Register */
        case 0x00a00:
            if (BHM_DIAG_HIGH) bhmMessage("I", PREFIX, " GPOUT Register (0x%02x)\n",fpgaState.gpout);
            val = fpgaState.gpout;
            break;

        /* XXX: implement a real I2C controller */

        /* GPINP Register */
        case 0x00a08:
            if (BHM_DIAG_HIGH) bhmMessage("I", PREFIX, " GPINP Register (0x%02x)\n",fpgaState.i2cout);
            /* IN = OUT until a real I2C control is implemented */
             if (fpgaState.i2csel)
                 val = fpgaState.i2cout;
             else
                 val = 0x00;
            break;

        /* I2CINP Register */
        case 0x00b00:
            val = ((fpgaState.i2cin & ~1) | eeprom24c0x_read());
            break;

        /* I2COE Register */
        case 0x00b08:
            val = fpgaState.i2coe;
            break;

        /* I2COUT Register */
        case 0x00b10:
            val = fpgaState.i2cout;
            break;

        /* I2CSEL Register */
        case 0x00b18:
            val = fpgaState.i2csel;
            break;

        default:
            bhmMessage("F", PREFIX, "malta_fpga_read: Bad register offset 0x%08x\n", off);
            break;
    }

    return val;
}

static PPM_WRITE_CB(regs_Write_portCB){

    Uns32 start = PTR_TO_UNS32(user);
    Uns32 off = (unsigned char*)addr - &fpga_Window[start];
    Uns8 val = data & 0xff;        // byte registers

    switch(off) {
        /* NMISTATUS Register */
        case 0x00024:
            if (BHM_DIAG_HIGH) bhmMessage("I", PREFIX, " NMISTATUS Register\n");
        break;

        /* NMIACK Register */
        case 0x00104:
            if (BHM_DIAG_HIGH) bhmMessage("I", PREFIX, " NMIACK Register\n");
        break;

        /* SWITCH Register */
        case 0x00200:
            if (BHM_DIAG_HIGH) bhmMessage("I", PREFIX, " SWITCH Register\n");
            break;

        /* JMPRS Register */
        case 0x00210:
            if (BHM_DIAG_HIGH) bhmMessage("I", PREFIX, " JMPRS Register\n");
            break;

        /* LEDBAR Register */
        /* XXX: implement a 8-LED array */
        case 0x00408:
            if (BHM_DIAG_HIGH) bhmMessage("I", PREFIX, " LEDBAR Register %02x (0x%02x)\n",val,fpgaState.leds);
            fpgaState.leds = val;
            break;

        /* ASCIIWORD Register */
        case 0x00410:
            if (BHM_DIAG_HIGH) bhmMessage("I", PREFIX, " ASCIIWORD Register %08X\n",data);
            snprintf(fpgaState.display_text, 9, "%08X", data);
            if (BHM_DIAG_LOW) bhmMessage("I", PREFIX, "DISPLAY '%s'\n",fpgaState.display_text);
            break;

        /* ASCIIPOS0 to ASCIIPOS7 Registers */
        case 0x00418:
        case 0x00420:
        case 0x00428:
        case 0x00430:
        case 0x00438:
        case 0x00440:
        case 0x00448:
        case 0x00450: {
            Uns32 charOff = (off - 0x00418) >> 3;
            if (fpgaState.display_text[charOff] != val) {
                fpgaState.display_text[charOff] = val;
                if (BHM_DIAG_LOW) bhmMessage("I", PREFIX, "DISPLAY '%s'\n",fpgaState.display_text);
            }
            break;
        }

        /* SOFTRES Register */
        case 0x00500:
            if (BHM_DIAG_HIGH) bhmMessage("I", PREFIX, "SOFTRES Register\n");
            if (val == 0x42) {
                if(finishOnReset) {
                    if (BHM_DIAG_HIGH) bhmMessage("I", PREFIX, "SOFTRES DO RESET: Simulation will finish\n");
                    bhmFinish();
                }
    /*             qemu_system_reset_request (); */
            }
            break;

        /* BRKRES Register */
        case 0x00508:
             fpgaState.brk = val & 0xff;
             if (BHM_DIAG_HIGH) bhmMessage("I", PREFIX, "BRKRES Register (0x%02x)\n",fpgaState.brk);
             break;

        /* UART Registers are handled directly by the serial device */

        /* GPOUT Register */
        case 0x00a00:
             fpgaState.gpout = val & 0xff;
             if (BHM_DIAG_HIGH) bhmMessage("I", PREFIX, " GPOUT Register (0x%02x)\n",fpgaState.gpout);
             break;

        /* I2COE Register */
        case 0x00b08:
            fpgaState.i2coe = val & 0x03;
            if (BHM_DIAG_HIGH) bhmMessage("I", PREFIX, " I2COE Register\n");
            break;

        /* I2COUT Register */
        case 0x00b10:
            eeprom24c0x_write(val & 0x02, val & 0x01);
            fpgaState.i2cout = val;
            if (BHM_DIAG_HIGH) bhmMessage("I", PREFIX, " I2COUT Register\n");
            break;

        /* I2CSEL Register */
        case 0x00b18:
            fpgaState.i2csel = val & 0x01;
            if (BHM_DIAG_HIGH) bhmMessage("I", PREFIX, " I2CSEL Register\n");
            break;

        default:
            bhmMessage("F", PREFIX, "Writing bad register offset 0x%08x\n",
            off);
            break;
    }

}

//
// BusPort handles
//
ppmLocalBusHandle lowPortHandle;
ppmLocalBusHandle highPortHandle;

//
// netPort handles
//


//
// Connect bus ports
//
void busPortConnections(void) {
    lowPortHandle = ppmOpenSlaveBusPort(
        "busPort1",
        &fpga_Window[0x0],
        LOW_WINDOW
    );
    ppmInstallReadCallback(
        regs_Read_portCB,
        0,
        &fpga_Window[0x0],
        LOW_WINDOW
    );
    ppmInstallWriteCallback(
        regs_Write_portCB,
        0,
        &fpga_Window[0x0],
        LOW_WINDOW
    );
    highPortHandle = ppmOpenSlaveBusPort(
        "busPort2",
        &fpga_Window[HIGH_WINDOW_BASE],
        HIGH_WINDOW
    );
    ppmInstallReadCallback(
        regs_Read_portCB,
        0,
        &fpga_Window[HIGH_WINDOW_BASE],
        HIGH_WINDOW
    );
    ppmInstallWriteCallback(
        regs_Write_portCB,
        0,
        &fpga_Window[HIGH_WINDOW_BASE],
        HIGH_WINDOW
    );

}

void userInit(void)
{
    fpgaState.leds     = 0x00;
    if(bhmUns32ParamValue("switches", &fpgaState.switches)){
        fpgaState.switches &= 0xff;        // byte wide register initialisation
        if(BHM_DIAG_MEDIUM) bhmMessage("I", PREFIX, "Switches initialised to 0x%02x\n", fpgaState.switches);
    }
    fpgaState.brk      = 0x0a;
    fpgaState.gpout    = 0x00;
    fpgaState.i2cin    = 0x3;
    fpgaState.i2coe    = 0x0;
    fpgaState.i2cout   = 0x3;
    fpgaState.i2csel   = 0x1;

    fpgaState.display_text[8] = '\0';
    snprintf(fpgaState.display_text, 9, "        ");
    if(BHM_DIAG_LOW) bhmMessage("I", PREFIX, "DISPLAY '%s'\n", fpgaState.display_text);

}

void userMainLoop(void)
{
    bhmEventHandle dummy;

    if (BHM_DIAG_LOW) bhmMessage("I", PREFIX,"User main\n");

    bhmBoolParamValue("stoponsoftreset", &finishOnReset);

    // USER MAIN
    // Block forever. Behavior is triggered by register access
    dummy = bhmCreateEvent();
    bhmWaitEvent(dummy);
}


//
// reset
//
//
// Connect net ports
//
void netPortConnections(void) {
}

//
// Main for  UART
//
PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    busPortConnections();
    netPortConnections();
    userInit();
    userMainLoop();

}

struct _eeprom24c0x_t {
  unsigned char tick;
  unsigned char address;
  unsigned char command;
  unsigned char ack;
  unsigned char scl;
  unsigned char sda;
  unsigned char data;
  //~ uint16_t size;
  unsigned char contents[256];
};

typedef struct _eeprom24c0x_t eeprom24c0x_t;

static eeprom24c0x_t eeprom = {
    //
    // Straight out of the Malta Board EEPROM
    //
    contents: {
        /* 00000000: */ 0x80, 0x08, 0x07, 0x0D, 0x0A, 0x01, 0x40, 0x00, 0x04, 0x50, 0x50, 0x00, 0x82, 0x08, 0x00, 0x01, // ......@..PP.....
        /* 00000010: */ 0x0E, 0x04, 0x1C, 0x01, 0x02, 0x20, 0xC1, 0x60, 0x50, 0x75, 0x50, 0x3C, 0x28, 0x3C, 0x28, 0x40, // ......Á`PuP<(<(@
        /* 00000020: */ 0x60, 0x60, 0x40, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x37, 0x41, 0x28, 0x28, 0x50, 0x00, 0x00, // ``@@.....7A((P..
        /* 00000030: */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFD, // ................
        /* 00000040: */ 0xC1, 0x49, 0x4E, 0x46, 0x49, 0x4E, 0x45, 0x4F, 0x45, 0x36, 0x34, 0x44, 0x33, 0x32, 0x33, 0x30, // ÁINFINEOE64D3230
        /* 00000050: */ 0x30, 0x47, 0x55, 0x35, 0x42, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x03, 0x0E, 0x04, 0x20, 0x02, // 0GU5B...........
        /* 00000060: */ 0x0F, 0xED, 0x17, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ................
        /* 00000070: */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // ................
        /* 00000080: */ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ................
        /* 00000090: */ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ................
        /* 000000A0: */ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ................
        /* 000000B0: */ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ................
        /* 000000C0: */ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ................
        /* 000000D0: */ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ................
        /* 000000E0: */ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ................
        /* 000000F0: */ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // ................
    },
};

#define logout(format, args...)  {if(BHM_DIAG_HIGH) bhmMessage("I", PREFIX, "eeprom data: " format, ##args);}

static unsigned char eeprom24c0x_read()
{
    if (BHM_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "eeprom24c0x_read");
        logout("%u: scl = %u, sda = %u, data = 0x%02x\n",
            eeprom.tick, eeprom.scl, eeprom.sda, eeprom.data);
    }
    return eeprom.sda;
}

static void eeprom24c0x_write(int scl, int sda)
{
    if (BHM_DIAG_HIGH)
        bhmMessage("I", PREFIX, "eeprom24c0x_write\n");
    if (eeprom.scl && scl && (eeprom.sda != sda)) {
        logout("%u: scl = %u->%u, sda = %u->%u i2c %s\n",
                eeprom.tick, eeprom.scl, scl, eeprom.sda, sda, sda ? "stop" : "start");
        if (!sda) {
            eeprom.tick = 1;
            eeprom.command = 0;
        }
    } else if (eeprom.tick == 0 && !eeprom.ack) {
        /* Waiting for start. */
        logout("%u: scl = %u->%u, sda = %u->%u wait for i2c start\n",
                eeprom.tick, eeprom.scl, scl, eeprom.sda, sda);
    } else if (!eeprom.scl && scl) {
        logout("%u: scl = %u->%u, sda = %u->%u trigger bit\n",
                eeprom.tick, eeprom.scl, scl, eeprom.sda, sda);
        if (eeprom.ack) {
            logout("\ti2c ack bit = 0\n");
            sda = 0;
            eeprom.ack = 0;
        } else if (eeprom.sda == sda) {
            unsigned char bit = (sda != 0);
            logout("\ti2c bit = %d\n", bit);
            if (eeprom.tick < 9) {
                eeprom.command <<= 1;
                eeprom.command += bit;
                eeprom.tick++;
                if (eeprom.tick == 9) {
                    logout("\tcommand 0x%04x, %s\n", eeprom.command, bit ? "read" : "write");
                    eeprom.ack = 1;
                }
            } else if (eeprom.tick < 17) {
                if (eeprom.command & 1) {
                    sda = ((eeprom.data & 0x80) != 0);
                }
                eeprom.address <<= 1;
                eeprom.address += bit;
                eeprom.tick++;
                eeprom.data <<= 1;
                if (eeprom.tick == 17) {
                    eeprom.data = eeprom.contents[eeprom.address];
                    logout("\taddress 0x%04x, data 0x%02x\n", eeprom.address, eeprom.data);
                    eeprom.ack = 1;
                    eeprom.tick = 0;
                }
            } else if (eeprom.tick >= 17) {
                sda = 0;
            }
        } else {
            logout("\tsda changed with raising scl\n");
        }
    } else {
        logout("%u: scl = %u->%u, sda = %u->%u\n", eeprom.tick, eeprom.scl, scl, eeprom.sda, sda);
    }
    eeprom.scl = scl;
    eeprom.sda = sda;
}


PPM_DESTRUCTOR_CB(destructor) {
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}
