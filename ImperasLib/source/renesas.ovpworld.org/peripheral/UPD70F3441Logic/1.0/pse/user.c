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
//                          Tue Sep 18 12:45:17 2012
//
////////////////////////////////////////////////////////////////////////////////

#include "pse.igen.h"
//////////////////////////////// Callback stubs ////////////////////////////////

typedef struct outputPinS {
    const char  *name;
    ppmNetHandle netP;
    Uns32        value;
} outputPin, *outputPinP;

static outputPin NMIOUT  = { "NMIOUT", 0, 0 };
static outputPin INT0    = { "INT0",   0, 0 };
static outputPin INT1    = { "INT1",   0, 0 };
static outputPin INT6    = { "INT6",   0, 0 };
static outputPin INT7    = { "INT7",   0, 0 };
static outputPin INT75   = { "INT75",  0, 0 };
static outputPin INT99   = { "INT99",  0, 0 };
static outputPin INT100  = { "INT100", 0, 0 };
static outputPin INT101  = { "INT101", 0, 0 };
static outputPin INT116  = { "INT116", 0, 0 };

//
// Only write when a value change occurs
//
static void doWriteNet(outputPinP pin, Uns32 value) {
    if (value != pin->value) {
        pin->value = value;
        ppmWriteNet(pin->netP, pin->value);
    }
}

typedef Uns32 input;
typedef Uns32 output;
static struct {
    // INT NMI / INT0
    input  NMIIN, INTDEDF, INTDEDR, INTDEDFR, INTOSD;

    // INT6
    input INTP4, INTUC0R;

    // INT7
    input INTP5, INTUC1R;

    // INT75
    input INTBRG0, INTBRG1;

    // INT99
    input INTCB0T, INTUC2T;

    // INT100
    input INTCB0R, INTUC2R, INTP13;

    // INT101
    input INTCB0RE, INTUC2RE;

    // INT116
    input INTDMA3, INTFL;
} inputPin;

static void update_nets0 () {
    output pNMIOUT, pINT0, pINT1;
    Uns8 n1, n2, n3, n4;

    n4 = inputPin.INTDEDF | inputPin.INTDEDR | inputPin.INTDEDFR;
    n2 = n4 | inputPin.INTOSD;
    n3 = ~(LOGICP0_reg0_data.INTSEL.bits.ISR);
    n1 = LOGICP0_reg0_data.INTSEL.bits.ISR & n2;

    pNMIOUT = inputPin.NMIIN | n1;
    pINT0 = n3 & n4;
    pINT1 = n3 & inputPin.INTOSD;

    doWriteNet(&NMIOUT, pNMIOUT);
    doWriteNet(&INT0,   pINT0);
    doWriteNet(&INT1,   pINT1);
}

static void update_nets6 () {
    output pINT6 = inputPin.INTP4 | inputPin.INTUC0R;
    doWriteNet(&INT6, pINT6);
}

static void update_nets7 () {
    output pINT7 = inputPin.INTP5 | inputPin.INTUC1R;
    doWriteNet(&INT7, pINT7);
}

static void update_nets75 () {
    output pINT75;
    if (LOGICP0_reg0_data.INTSEL.bits.BRGSSR == 0) {
        pINT75 = inputPin.INTBRG0;
    } else {
        pINT75 = inputPin.INTBRG1;
    }
    doWriteNet(&INT75, pINT75);
}

static void update_nets99 () {
    output pINT99;
    if (LOGICP1_reg0_data.PFC4.bits.PFC40 == 0) {
        pINT99 = inputPin.INTCB0T;
    } else {
        pINT99 = inputPin.INTUC2T;
    }
    doWriteNet(&INT99, pINT99);
}

static void update_nets100 () {
    output pINT100;
    if (LOGICP1_reg0_data.PFC4.bits.PFC40 == 0) {
        pINT100 = inputPin.INTCB0R;
    } else {
        pINT100 = inputPin.INTP13 | inputPin.INTUC2R;
    }
    doWriteNet(&INT100, pINT100);
}

static void update_nets101 () {
    output pINT101;
    if (LOGICP1_reg0_data.PFC4.bits.PFC41 == 0) {
        pINT101 = inputPin.INTCB0RE;
    } else {
        pINT101 = inputPin.INTUC2RE;
    }
    doWriteNet(&INT101, pINT101);
}

static void update_nets116 () {
    output pINT116;
    if (LOGICP0_reg0_data.INTSEL.bits.INTSEL4 == 0) {
        pINT116 = inputPin.INTDMA3;
    } else {
        pINT116 = inputPin.INTFL;
    }
    doWriteNet(&INT116, pINT116);
}

PPM_NET_CB(P_INTBRG0) {
    inputPin.INTBRG0 = value;
    update_nets75();
}

PPM_NET_CB(P_INTBRG1) {
    inputPin.INTBRG1 = value;
    update_nets75();
}

PPM_NET_CB(P_INTCB0R) {
    inputPin.INTCB0R = value;
    update_nets100();
}

PPM_NET_CB(P_INTCB0RE) {
    inputPin.INTCB0RE = value;
    update_nets101();
}

PPM_NET_CB(P_INTCB0T) {
    inputPin.INTCB0T = value;
    update_nets99();
}

PPM_NET_CB(P_INTDEDF) {
    inputPin.INTDEDF = value;
    update_nets0();
}

PPM_NET_CB(P_INTDEDFR) {
    inputPin.INTDEDFR = value;
    update_nets0();
}

PPM_NET_CB(P_INTDEDR) {
    inputPin.INTDEDR = value;
    update_nets0();
}

PPM_NET_CB(P_INTDMA3) {
    inputPin.INTDMA3 = value;
    update_nets116();
}

PPM_NET_CB(P_INTFL) {
    inputPin.INTFL = value;
    update_nets116();
}

PPM_NET_CB(P_INTOSD) {
    inputPin.INTOSD = value;
    update_nets0();
}

PPM_NET_CB(P_INTP13) {
    inputPin.INTP13 = value;
    update_nets100();
}

PPM_NET_CB(P_INTP4) {
    inputPin.INTP4 = value;
    update_nets6();
}

PPM_NET_CB(P_INTP5) {
    inputPin.INTP5 = value;
    update_nets7();
}

PPM_NET_CB(P_INTUC0R) {
    inputPin.INTUC0R = value;
    update_nets6();
}

PPM_NET_CB(P_INTUC1R) {
    inputPin.INTUC1R = value;
    update_nets7();
}

PPM_NET_CB(P_INTUC2R) {
    inputPin.INTUC2R = value;
    update_nets100();
}

PPM_NET_CB(P_INTUC2RE) {
    inputPin.INTUC2RE = value;
    update_nets101();
}

PPM_NET_CB(P_INTUC2T) {
    inputPin.INTUC2T = value;
    update_nets99();
}

PPM_NET_CB(P_NMIIN) {
    inputPin.NMIIN = value;
    update_nets0();
}

PPM_REG_WRITE_CB(writeERR) {
    //
    // Check legal values
    //
    if (data & 0x78) {
        bhmMessage("W", "LOGIC", "Register ERRF Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0x78) | (data & 0x87);
}

PPM_REG_WRITE_CB(writeP) {
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writePFC) {
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writePM) {
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writePMC) {
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writeSEL) {
    //
    // Check legal values
    //
    if (data & 0x62) {
        // illegal {6,5,1} == 1
        bhmMessage("W", "LOGIC", "Register SEL Illegal value 0x%02x\n", data);
    }
    if (~data & 0x0c) {
        // illegal {3,2} == 0
        bhmMessage("W", "LOGIC", "Register SEL Illegal value 0x%02x\n", data);
    }
    *(Uns8*)user = (*(Uns8*)user & 0x62) | (data & 0x9d);
}

PPM_REG_WRITE_CB(writeESOST5) {
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writeESOST6) {
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writePESC5) {
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writePESC6) {
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writePESMK5) {
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writePESMK6) {
    *(Uns8*)user = data;
}

PPM_REG_WRITE_CB(writePRCMD) {
    *(Uns8*)user = data;
}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();

    NMIOUT.netP = handles.NMIOUT;
    INT0.netP   = handles.INT0;
    INT1.netP   = handles.INT1;
    INT6.netP   = handles.INT6;
    INT7.netP   = handles.INT7;
    INT75.netP  = handles.INT75;
    INT99.netP  = handles.INT99;
    INT100.netP = handles.INT100;
    INT101.netP = handles.INT101;
    INT116.netP = handles.INT116;
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

