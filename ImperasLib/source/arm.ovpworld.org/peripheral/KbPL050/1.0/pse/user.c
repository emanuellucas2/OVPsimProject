/*
 * Keyboard Controller
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

#include "pse.igen.h"
#include "ps2Interface.c.h"

#define BPORT1 0
#include "pse.macros.igen.h"

#define DEFAULT_RX_DELAY  2000

#define cr      bport1_ab_data.cr.value
#define stat    bport1_ab_data.stat.value
#define flags   bport1_ab_data.flags.value
#define clk     bport1_ab_data.clk.value
#define iir     bport1_ab_data.iir.value

static Uns32    last     = 0;
static Uns32    pending  = 0;

static bhmEventHandle inEvent, outEvent;


///////////////////////////////////////////////////////////////////////////////

static void update(Bool level)
{
    pending = level; // ???

    Bool raise = (pending && (cr & 0x10) != 0)
              || (cr & 0x08) != 0;
    static Bool current = 0;
    if (raise != current) {
        current = raise;
        ppmWriteNet(handles.irq, raise);
    }
}


PPM_REG_READ_CB(readDATA) {
    if (pending) {
        last = ps2ReadByte(isMouse);
    }
    return last;

}

PPM_NBYTE_READ_CB(readID) {
    static const Uns8 id[] ={ 0x50, 0x10, 0x04, 0x00, 0x0d, 0xf0, 0x05, 0xb1 };
    Uns32 reg   = (offset-0xfe0)/0x4;
    *(Uns32*)data = id[reg];
}

PPM_REG_READ_CB(readIIR) {
    return pending | 2;
}

PPM_REG_READ_CB(readSTAT) {

    Uns8 val = last;
    val = val ^ (val >> 4);
    val = val ^ (val >> 2);
    val = (val ^ (val >> 1)) & 1;

    Uns32 st = BPORT1_AB_STAT_TXEMPTY;
    if (val)
        st |= BPORT1_AB_STAT_RXPARITY;
    if (pending)
        st |= BPORT1_AB_STAT_RXFULL;

    return st;

}

PPM_REG_WRITE_CB(writeCR) {
    cr = data;
    update(pending);
}

PPM_REG_WRITE_CB(writeDATA) {
    bhmTriggerEvent(outEvent);
    if (isMouse) {
        ps2WriteByte(data, 1);
    } else {
        ps2WriteByte(data, 0);
    }
}

//
// The polling process that gets characters
//
static void getData(void *user)
{
    while(1) {
        double d = DEFAULT_RX_DELAY;

        bhmWaitDelay(d);
        ps2Poll(False);
    }
}

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    Bool grabDisable, cursorEnable;

    bhmBoolParamValue("isMouse", &isMouse);
    bhmBoolParamValue("isKeyboard", &isKeyboard);
    bhmBoolParamValue("grabDisable", &grabDisable);
    bhmBoolParamValue("cursorEnable", &cursorEnable);

    bhmCreateThread(getData, NULL, "getdata", 0);

    kbMouse = (!isKeyboard & !isMouse) ? 0 : (isMouse ? 1 : 2);

    if (isMouse) {
        inEvent    = bhmCreateNamedEvent("mouseEvent", "Mouse has produced data");
        outEvent   = bhmCreateNamedEvent("mouseWrite", "Written to mouse");
        ps2Init((Uns32)grabDisable, (Uns32)cursorEnable, NULL, update);
    } else {
        inEvent    = bhmCreateNamedEvent("keyEvent", "Keyboard has produced data");
        outEvent   = bhmCreateNamedEvent("keyWrite", "Write to keyboard");
        ps2Init((Uns32)grabDisable, (Uns32)cursorEnable, update, NULL);
    }
}

PPM_DESTRUCTOR_CB(destructor) {
    ps2Finish();
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    if(phase==PPM_POST_SAVE_RESTORE) {
        ps2Restore();
    }
}

