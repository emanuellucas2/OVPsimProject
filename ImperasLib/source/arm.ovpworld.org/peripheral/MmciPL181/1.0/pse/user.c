/*
 * Multimedia Card Interface
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

#include "peripheral/bhm.h"
#include "peripheral/ppm.h"

#include "pse.igen.h"

#define BPORT1 0
#include "pse.macros.igen.h"

#include "user.defines.h"

#define STR(_name)   (bport1_ab_data. _name .value)

#define power      STR(power)
#define clock      STR(clock)
#define cmdarg     STR(cmdarg)
#define command    STR(cmd)
#define respcmd    STR(respcmd)
#define response0  STR(response0)
#define response1  STR(response1)
#define response2  STR(response2)
#define response3  STR(response3)
#define datatimer  STR(datatimer)
#define datalength STR(datalength)
#define datactrl   STR(datactrl)
#define datacnt    STR(datacnt)
#define status     STR(status)
#define clear      STR(clear)
#define mask0      STR(mask0)
#define mask1      STR(mask1)
#define fifoCnt    STR(fifoCnt)

#define periphID0  STR(periphID0)
#define periphID1  STR(periphID1)
#define periphID2  STR(periphID2)
#define periphID3  STR(periphID3)
#define pCellID0   STR(pCellID0)
#define pCellID1   STR(pCellID1)
#define pCellID2   STR(pCellID2)
#define pCellID3   STR(pCellID3)


// Diagnostics level for the PSE
#define DIAG_HIGH (diagnosticLevel >= 3)
#define DIAG_MED  (diagnosticLevel >= 2)
#define DIAG_LOW  (diagnosticLevel >= 1)


//static const unsigned char id[] =
//{ 0x81, 0x11, 0x04, 0x00, 0x0d, 0xf0, 0x05, 0xb1 };

//
// Semihosted function: passes initialisation info
//
FUNCTOHOST(Uns32, initNative,
    void        *addressRegisters,
    void        *fifoBase,
    Uns32        fifoSize,
    const char  *driveName,
    Uns32        driveNameLen,
    Uns32        delta,
    ppmNetHandle irq0,
    ppmNetHandle irq1,
    ppmNetHandle cardin,
    ppmNetHandle wprot
)

FUNCTOHOST(void, startSDNative, void)

FUNCTOHOST(void, setNativeDiagnostics, Uns32 *diagP, Uns32 currentDiag)

FUNCTOHOST(void, sendCommandNative, void)

FUNCTOHOST(void, writeDCNative, void)

static void update_interrupts(void)
{
    static Bool currentIRQ0 = False;
    static Bool currentIRQ1 = False;

    Bool i0 = (status & mask0) && True;
    Bool i1 = (status & mask1) && True;

    if(i0 != currentIRQ0) {
        ppmWriteNet(handles.irq0, i0);
        currentIRQ0 = i0;
    }
    if(i1 != currentIRQ1) {
        ppmWriteNet(handles.irq1, i1);
        currentIRQ1 = i1;
    }
}


PPM_REG_READ_CB(readFifoCnt) {
    if(DIAG_HIGH) bhmMessage("I", PREFIX, "%s", __FUNCTION__);
    Uns32 tmp = (datacnt + 3) >> 2;
    return tmp;
}

PPM_REG_READ_CB(readStatus) {
    if(DIAG_HIGH) bhmMessage("I", PREFIX, "%s", __FUNCTION__);
    Uns32 tmp = status;
    return tmp;
}

PPM_REG_WRITE_CB(write8) {
    if(DIAG_HIGH) bhmMessage("I", PREFIX, "%s", __FUNCTION__);
    *(Uns32*)user = data & 0xFF;
}

PPM_REG_WRITE_CB(writeClock) {
    if(DIAG_HIGH) bhmMessage("I", PREFIX, "%s", __FUNCTION__);
    clock &= ~(data & 0x7ff);
}

PPM_REG_WRITE_CB(writeClear) {
    if(DIAG_HIGH) bhmMessage("I", PREFIX, "%s", __FUNCTION__);
    status &= ~(data & 0x7ff);
    update_interrupts();
}

PPM_REG_WRITE_CB(writeArg) {
    if(DIAG_HIGH) bhmMessage("I", PREFIX, "%s", __FUNCTION__);
    cmdarg = data;
}

PPM_REG_WRITE_CB(writeCmd) {
    if(DIAG_HIGH) bhmMessage("I", PREFIX, "%s", __FUNCTION__);
    command = data;
    if (command & BPORT1_AB_CMD_C_ENABLE) {
        if (command & BPORT1_AB_CMD_C_INTERRUPT) {
            bhmMessage("F", PREFIX, "Interrupt mode not implemented");
        }
        if (command & BPORT1_AB_CMD_C_PENDING) {
            bhmMessage("F", PREFIX, "Pending commands not implemented");
        }
        sendCommandNative();
        command &= ~BPORT1_AB_CMD_C_ENABLE;
    }
    update_interrupts();
}

PPM_REG_WRITE_CB(writeDC) {
    if(DIAG_HIGH) bhmMessage("I", PREFIX, "%s", __FUNCTION__);
    datactrl = data & 0xff;
    if (data & BPORT1_AB_DATACTRL_D_ENABLE) {
        datacnt = datalength;
        writeDCNative();
    }
}

PPM_REG_WRITE_CB(writeDL) {
    if(DIAG_HIGH) bhmMessage("I", PREFIX, "%s", __FUNCTION__);
    datalength = data & 0xffff;
}

PPM_REG_WRITE_CB(writeMask0) {
    if(DIAG_HIGH) bhmMessage("I", PREFIX, "%s", __FUNCTION__);
    mask0 = data & 0x003fffff;
    update_interrupts();
}

PPM_REG_WRITE_CB(writeMask1) {
    if(DIAG_HIGH) bhmMessage("I", PREFIX, "%s", __FUNCTION__);
    mask1 = data & 0x003fffff;
    update_interrupts();
}

PPM_REG_READ_CB(reservedRead) {
    Uns32 offset = *(Uns32 *)(UnsPS *)addr - PTR_TO_UNS32(handles.bport1);
    bhmMessage("W", PREFIX, "Read in Reserved Region 0x%08x", offset);

    return 0xdeadbeef;
}

PPM_REG_WRITE_CB(reservedWrite) {
    Uns32 offset = *(Uns32 *)(UnsPS *)addr - PTR_TO_UNS32(handles.bport1);
    bhmMessage("W", PREFIX, "Write in Reserved Region 0x%08x", offset);
}

PPM_CONSTRUCTOR_CB(constructor) {
    // YOUR CODE HERE (pre constructor)

    periphConstructor();

    // YOUR CODE HERE (post constructor)

    char driveName[BHM_MAX_PATH];
    if(bhmStringParamValue("SD_DRIVE", driveName, sizeof(driveName))) {
        bhmMessage("I", PREFIX, "SD Drive '%s' (%d)", driveName, (Uns32)strlen(driveName));
    }
    Bool delta;
    bhmBoolParamValue("SD_DRIVE_DELTA", &delta);
    if (delta) {
        bhmMessage("I", PREFIX, "SD Drive Delta Enabled");
    }

    setNativeDiagnostics(&diagnosticLevel, diagnosticLevel);
    initNative(
        &bport1_ab_data,
        (handles.bport1+0x80), 0x40,
        driveName, strlen(driveName), delta,
        handles.irq0, handles.irq1, handles.cardin, handles.wprot
    );

    // Perform a reset as native memory mapping will overwrite
    reset_reset(1,0);

    startSDNative();

}

PPM_DESTRUCTOR_CB(destructor) {
    // YOUR CODE HERE (destructor)
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

