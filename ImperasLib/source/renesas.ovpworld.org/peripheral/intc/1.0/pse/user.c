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
//                                                                            //
//                W R I T T E N   B Y   I M P E R A S   I G E N               //
//                                                                            //
//                          Wed Feb 24 15:15:28 2010                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#include "pse.igen.h"

#define PREFIX "INTC"

typedef struct outputPinS {
    const char  *name;
    ppmNetHandle netP;
    Uns32        value;
} outputPin, *outputPinP;

static outputPin RESET = { "RESET", 0, 0 };
static outputPin NMI0  = { "NMI0",  0, 0 };
static outputPin NMI1  = { "NMI1",  0, 0 };
static outputPin NMI2  = { "NMI2",  0, 0 };
static outputPin INTP  = { "INTP",  0, 0 };

static struct {
    Uns32 IRESET;
    Uns32 NMI[64];
    Uns32 INT[256];
} inputPin;

//
// Only write when a value change occurs
//
static void doWriteNet(outputPinP pin, Uns32 value) {
    if (value != pin->value) {
        pin->value = value;
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX"_ACT", "doWriteNet active  %s -> 0x%03x\n", pin->name, pin->value);
        ppmWriteNet(pin->netP, pin->value);
//    } else {
//        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX"_IGN", "doWriteNet ignored %s -> 0x%03x\n", pin->name, pin->value);
    }
}

#define BYTE_ACCESS(_addr,_user) *(Uns8*)(UnsPS)(PTR_TO_UNS32(_user) | (PTR_TO_UNS32(_addr) & 1))

static void writeByteOrShort(void *addr, Uns32 bytes, void *user, Uns32 data) {
    if (bytes == 1) {
        BYTE_ACCESS(addr,user) = data;
    } else {
        *(Uns16*)user = data;
    }
}

static Uns32 readByteOrShort(void *addr, Uns32 bytes, void *user) {
    if (bytes == 1) {
        return BYTE_ACCESS(addr,user);
    } else {
        return *(Uns16*)user;
    }
}


#define REGIC(_n)   *(Uns8*)  (UnsPS)(PTR_TO_UNS32(&(INTCP0_reg1_data.IC000.value)) + ((_n)*sizeof(INTCP0_reg1_data.IC000)))
#define REGMR(_n)   *(Uns16*) (UnsPS)(PTR_TO_UNS32(&(INTCP0_reg0_data.IMR0.value))  + ((_n)*sizeof(INTCP0_reg0_data.IMR0)))

typedef union {
    Uns8 value;
    struct {
        unsigned PR : 3;
        unsigned __pad3 : 3;
        unsigned MK : 1;
        unsigned IF : 1;
    } bits;
} ICREG;

static Int32 request = -1;
/*
 * Interrupt priorities go from 0 (highest) to 7 (lowest)
 */
void process_interrupt_requests () {
    //
    // If interrupt pending and enabled set intp to its value
    // only for highest priority
    //
    Int32 icidx;
    ICREG ic;
    Int32 interrupt = -1;
    Int32 priority  = 8;    // set to 8 so even the lowest priority '7' will override

    for (icidx=0; icidx<=116; icidx++) {

        ic.value = REGIC(icidx);

        //
        // Requesting and Enabled ?
        //
        if (ic.bits.IF && !ic.bits.MK) {
            //
            // Ensure this is higher than the current highest priority
            //
            if (ic.bits.PR < priority) {
                priority = ic.bits.PR;
                interrupt = icidx;
            }
        }
    }

    //
    // Now we have the highest priority enabled request
    //
    if (interrupt != -1) {
        request = interrupt;

        Uns32 vector = 0x00000080 + (request << 4);
        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX"_REQ", "Interrupt REQ INTP %d PRI=%d\n", request, priority);
        doWriteNet(&INTP, vector);
    } else {
        doWriteNet(&INTP, 0);
    }
}

void interrupt_acknowledge () {
    //
    // Clear the request bit
    //
    ICREG ic;

    //
    // Hmm something bad happened, an acknowledge to an interrupt not requested !
    //
    if (request == -1) return;
    if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX"_REQ", "Interrupt ACK INTP %d\n", request);

    ic.value = REGIC(request);
    ic.bits.IF = 0;
    INTCP0_reg1_data.ISPR.value = (0x1 << ic.bits.PR);
    REGIC(request) = ic.value;

    //
    // check to see if any other interrupts pending in one cycle
    //
    process_interrupt_requests();
}

//
// Copy all the IC[MK] bits into the MK registers
// IC000[MK] -> IMR0[00]
// IC001[MK] -> IMR0[01]
// ...
// IC015[MK] -> IMR0[15]
// ...
// IC116[MK] -> IMR7[04]
// or vice versa
//
void copyMKbit (Uns8 toMR) {
    //
    // The IC entries are  word aligned so we need to shift by a  word pointer
    // The MR entries are short aligned so we need to shift by a short pointer
    //
    Uns32 icidx;
    ICREG ic;
    Uns16 mr;
    for (icidx=0; icidx<=116; icidx++) {
        Uns32  mridx = icidx / 16;
        Uns32 bitpos = icidx % 16;

        ic.value = REGIC(icidx);
        mr       = REGMR(mridx);

        if (toMR) {
            Uns16 mask   = 0x1 << bitpos;
            Uns16 mkval  = ic.bits.MK << bitpos;
            mr = (mr & ~mask) | mkval;
            REGMR(mridx) = mr;

        } else {

            ic.bits.MK   = (mr >> bitpos) & 0x1;
            REGIC(icidx) = ic.value;
        }
    }

    //
    // This update may now generate an interrupt request
    //
    process_interrupt_requests();
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_NET_CB(P_INT) {
    Uns32 index = PTR_TO_UNS32(userData);
    ICREG ic;

//    bhmMessage("W", "PIN", "INT_%03d -> %d @%fus\n", index, value, bhmGetCurrentTime());

    ic.value = REGIC(index);

    //
    // Has the input pin changed state ?
    //
    if (inputPin.INT[index] != value) {
        //
        // If an interrupt line changes state look at the corresponding
        // INTF/INTR Register for that bit
        //

        //
        // For all Internal interrupts it is level high active
        //
        if (value) {
            //
            // set the IF flag, this is reset by an acknowledge from the CPU
            //
            if (!ic.bits.IF) {
                ic.bits.IF = 1;
                REGIC(index) = ic.value;
//                bhmMessage("W", "REG", "IC%03d[IF]=1 @%fus\n", index, bhmGetCurrentTime());
                process_interrupt_requests();
            }
        } else {
        }
    }

    inputPin.INT[index] = value;
}

PPM_NET_CB(P_MIRETI) {
    INTCP0_reg1_data.ISPR.value = 0;
}

PPM_NET_CB(P_INTACK) {
    interrupt_acknowledge();

}

PPM_NET_CB(P_IRESET) {
//    bhmMessage("W", "PIN", "IRESET -> %d @%fus\n", value, bhmGetCurrentTime());
}

PPM_NET_CB(P_NMI) {
    Uns32 index = PTR_TO_UNS32(userData);

    Uns32 wire_or = 0;
    if ((inputPin.NMI[index] != value) && value) {
        wire_or = 1;
    }

    doWriteNet(&NMI0, wire_or);
    inputPin.NMI[index] = value;
}

PPM_REG_WRITE_CB(writeIC) {
    ICREG ic;
    ic.value = (data & 0xc7);

    // A write to the IC register also requires that the
    // corresonding bit in IMR is written
    *(Uns8*)user = ic.value;

    copyMKbit(1);
}
PPM_REG_READ_CB(readIC) {
    return *(Uns8*)user;
}

//
// Interrupt mask register can be written as byte or short
//
PPM_REG_WRITE_CB(writeIMR) {
    // A write to the IMR register also requires that the
    // corresonding bit in IC is written
    writeByteOrShort(addr, bytes, user, data);

    copyMKbit(0);
}

PPM_REG_READ_CB(readIMR) {
    return readByteOrShort(addr, bytes, user);
}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();

    RESET.netP = handles.RESET;
    NMI0.netP  = handles.NMI0;
    NMI1.netP  = handles.NMI1;
    NMI2.netP  = handles.NMI2;
    INTP.netP  = handles.INTP;
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

