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

#include <string.h>

////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                           Imperas/OVP Generated
//                          Tue Feb  8 12:12:21 2011
//
////////////////////////////////////////////////////////////////////////////////

#include "pse.igen.h"
//////////////////////////////// Callback stubs ////////////////////////////////

#define PREFIX "I8253"

typedef struct counterS {
    union {
       Uns16 value;
       struct {
           unsigned lo : 8;
           unsigned hi : 8;
       } bits;
    } COUNT;
    Uns8 mode;
    Uns8 bcd;
    Uns8 read, write;
} counterT, *counterP;

counterT counter[3];

PPM_NBYTE_READ_CB(readCNTL) {
    // if(PSE_DIAG_HIGH)
    bhmMessage("F", PREFIX, "Read Control Unsupported\n");
    memcpy(data, &(bport1_reg_data.CNTL.value), 1);
}

PPM_NBYTE_WRITE_CB(writeCNTL) {

    memcpy( &(bport1_reg_data.CNTL.value), data, 1);

    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Write Control %f SC=%x RW=%x M=%x BCD=%x\n",
                bhmGetCurrentTime(),
                bport1_reg_data.CNTL.bits.SC, bport1_reg_data.CNTL.bits.RW,
                bport1_reg_data.CNTL.bits.M, bport1_reg_data.CNTL.bits.BCD);
    }

    Uns8 select = bport1_reg_data.CNTL.bits.SC;
    Uns8 mode   = bport1_reg_data.CNTL.bits.M;
    Uns8 bcd    = bport1_reg_data.CNTL.bits.BCD;
    Uns8 rw     = bport1_reg_data.CNTL.bits.RW;

    ppmNetHandle outP = NULL;

    switch (select) {
    case 0:
    case 1:
    case 2:
        outP = handles.out[select];
        counter[select].mode = mode;
        counter[select].bcd  = bcd;
        break;

    case 3:
        bhmMessage("F", PREFIX, "Read BackCommand\n");
        break;
    }

    switch (mode) {
    case 0:
        // Output is initially low
        if (outP) ppmWriteNet(outP, 0);
        if(PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Mode 0\n");

    case 2:
        // Output is initially high
        if (outP) ppmWriteNet(outP, 1);
        if(PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Mode 2\n");
        break;

    default:
        bhmMessage("F", PREFIX, "Mode %d Unsupported\n", mode);
        break;
    }

    counter[select].read  = rw;
    counter[select].write = rw;
}

PPM_NBYTE_READ_CB(readCTR) {

    Uns32 reg   = (offset-0x0)/0x1;
    memcpy(data, &(bport1_reg_data.CTR[reg].value), 1);

    bhmMessage("E", PREFIX, "Unsupported Read from CTR[%u\n", reg);
}

void updateCounterWrite (counterP cP, Uns8 data) {
    switch (cP->write) {
    case 0:
        cP->write = -1;
        bhmMessage("F", PREFIX, "Unsupported Write latch\n");
        break;

    case 1: // lo
        cP->COUNT.bits.lo = data;
        cP->write = -1;
        break;

    case 2: // hi
        cP->COUNT.bits.hi = data;
        cP->write = -1;
        break;

    case 3: // lo, then hi
        cP->COUNT.bits.lo = data;
        cP->write = 2;
        break;

    default: // error
        bhmMessage("F", PREFIX, "Illegal Write Counter %f data=0x%02x\n", bhmGetCurrentTime(), data);
    }
}

PPM_NBYTE_WRITE_CB(writeCTR) {

    Uns32 reg   = (offset-0x0)/0x1;

    memcpy(&(bport1_reg_data.CTR[reg].value), data, 1);

    updateCounterWrite(&counter[reg], bport1_reg_data.CTR[reg].value );

    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "%f: Write Counter[%u] = 0x%04x\n", bhmGetCurrentTime(), reg, counter[reg].COUNT.value);
    }
}

PPM_CONSTRUCTOR_CB(constructor) {
    // YOUR CODE HERE (pre constructor)
    periphConstructor();
    // YOUR CODE HERE (post constructor)

    // Set all outputs low
    Uns32 i;
    for(i = 0; i < 2; i++) {
        if (handles.out[i]) {
        	ppmWriteNet(handles.out[i], 0);
        }
    }
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}


