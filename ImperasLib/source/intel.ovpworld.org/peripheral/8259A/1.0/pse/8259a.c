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

#include <stdio.h>
#include <string.h>
#include "pse.igen.h"
#include "8259a.h"

static ppmExternalBusHandle cascadeBus;
static Uns8 cascadeWindow[8];

ppmNetHandle intpHandle;
ppmNetHandle irHandle[8];
Bool master, slave;

//
// Helper functions
//
static void icw1Print () {
    bhmMessage("I", PREFIX, "ICW1: A[7-5]=0x%02x LTIM=%d ADI=%d SNGL=%d IC4=%d\n",
            reg.icw1.bits.a7to5, reg.icw1.bits.ltim,
            reg.icw1.bits.adi, reg.icw1.bits.sngl,
            reg.icw1.bits.ic4);
}

static void icw2Print () {
    bhmMessage("I", PREFIX, "ICW2: A[15-11]=0x%02x A[10-8]=0x%02x\n",
            reg.icw2.bits.a15to11, reg.icw2.bits.a10to8);
}

static void icw3Print () {
    if (master) {
        bhmMessage("I", PREFIX, "ICW3: (master) S[7-0]=0x%02x\n", reg.icw3.byte);
    } else {
        bhmMessage("I", PREFIX, "ICW3: (slave) ID[3-0]=0x%01x\n", reg.icw3.byte);
    }
}

static void icw4Print () {
    bhmMessage("I", PREFIX, "ICW4: SFNM=%d BUF=%d M/S=%d AEOI=%d uPM=%d\n",
            reg.icw4.bits.sfnm, reg.icw4.bits.buf,
            reg.icw4.bits.ms, reg.icw4.bits.aeoi,
            reg.icw4.bits.upm);
}

static void ocw1Print () {
    bhmMessage("I", PREFIX, "OCW1: MASK=0x%02x\n", reg.ocw1.byte);
}

static void ocw2Print () {
    bhmMessage("I", PREFIX, "OCW2: R=%d SL=%d EOI=%d L[2-0]=0x%01x\n",
            reg.ocw2.bits.r, reg.ocw2.bits.sl,
            reg.ocw2.bits.eoi, reg.ocw2.bits.l);
}

static void ocw3Print () {
    bhmMessage("I", PREFIX, "OCW3: ESMM=%d SMM=%d POLL=%d RR=%d RIS=%d\n",
            reg.ocw3.bits.esmm, reg.ocw3.bits.smm,
            reg.ocw3.bits.p, reg.ocw3.bits.rr,
            reg.ocw3.bits.ris);
}

static void guard_assign (Uns8 *guard, ppmNetHandle handle, Uns8 value, char *name) {
    if (*guard != value) {
        if (PSE_DIAG_LOW) bhmMessage("I", PREFIX, "guard_assign() PIN %s <= %d\n", name, value);
        ppmWriteNet(handle, value);
        *guard = value;
    }
}

//
// Evaluate the state based upon changes input changes and register callbacks
//
void evaluate () {
    Uns8 intp;

    /*
     * Firstly look at pins to see if we need to update the irr
     */
    int i;
    if (reg.icw1.bits.ltim) {
        // level sensitive set
        bhmMessage("F", PREFIX, "evaluate() icw1.ltim = 1 - unsupported");
        for (i=0; i<8; i++) {
            Uns8 mask = 1;
            if (pin.ir[i].value) {
                // set irr bit, clear occurs when the irr bit is transferred to the isr
                reg.irr |= (mask << i);
            }
        }

    } else {
        // edge sensitive set
        for (i=0; i<8; i++) {
            Uns8 mask = 1;
            if (pin.ir[i].value /* && !pin.ir[i].last */) {
                // set irr bit, clear occurs when the irr bit is transferred to the isr
                reg.irr |= (mask << i);
            }
        }
    }

    /*
     *  Compare through the mask (if special mask mode)
     */
    Uns8 irr_postmask = reg.irr & ~(reg.ocw1.byte);
    if (PSE_DIAG_LOW) bhmMessage("I", PREFIX, "evaluate() irr=0x%02x mask=0x%02x irr_postmask=0x%02x\n",
            reg.irr, reg.ocw1.byte, irr_postmask);

    /*
     * Now go through the priority resolver to get highest priority request
     */
    Uns8 maxp = 255;
    Uns8 p;
    Uns8 irq, irqhi = 255;
    if (irr_postmask) {
        for(i=0; i<8; i++) {
            irq = (irr_postmask >> i) & 0x1;
            p = reg.priority[i];
            if (irq && (p < maxp)) {
                if (PSE_DIAG_LOW) bhmMessage("I", PREFIX, "evaluate() Candidate irq=%d priority=%d\n", i, p);
                maxp = p;
                irqhi = i;
            }
        }
        if (PSE_DIAG_LOW) bhmMessage("I", PREFIX, "evaluate() Selected irq=%d priority=%d\n", irqhi, maxp);

        //
        // Now potentially generate an interrupt request
        //
        intp = 1;
    } else {
        //
        // Now potentially clear an interrupt request
        //
        intp = 0;
    }

    //
    // Have we received an acknowledge ?
    // if so put highest priority irr into the isr
    //
    if (pin.intack == True) {

        Uns8 index = 1 << irqhi;
        if (irqhi < 8) {
            //
            // set the interrupt service register, clear the interrupt request register
            //
            reg.isr |= (1 << irqhi);
            reg.irr &= ~(1 << irqhi);

            if (PSE_DIAG_LOW) bhmMessage("I", PREFIX, "evaluate() INTACK irq=%d irr=0x%02x isr=0x%02x\n", irqhi, reg.irr, reg.isr);

            // Get the acknowledged irq, read from slave if necessary
            if (master) {
                if ((index & reg.icw3.byte) == 0) {
                    reg.irqack = (reg.icw2.byte & 0xf8) + irqhi;
                } else {
                    reg.irqack = cascadeWindow[irqhi];
                }
            } else {
                reg.irqack = (reg.icw2.byte & 0xf8) + irqhi;
            }
        }
    }

    //
    // Have we received an end of interrupt ?
    // or an automatic end of interrupt
    // if so clear the mask bit encoded in L2-0
    //
    if (pin.eoi == True || (pin.intack && reg.icw4.bits.aeoi)) {
        if (PSE_DIAG_LOW) bhmMessage("I", PREFIX, "evaluate(0) EOI irr=0x%02x isr=0x%02x\n", reg.irr, reg.isr);

        // Specific or non specific ?
        if (reg.ocw2.bits.sl) {
            if (PSE_DIAG_LOW) bhmMessage("I", PREFIX, "Performing Specific EOI L=%d", reg.ocw2.bits.l);
            Uns8 mask = 1 << reg.ocw2.bits.l;
            reg.isr &= ~mask;

        // Non-specific highest is bit
        } else {
            if (PSE_DIAG_LOW) bhmMessage("I", PREFIX, "Performing Non-Specific EOI");
            for (i=0; i<8; i++) {
                Uns8 mask = 1 << i;
                if (reg.isr & mask) {
                    reg.isr &= ~mask;
                    break;
                }
            }
        }
        if (PSE_DIAG_LOW) bhmMessage("I", PREFIX, "evaluate(1) EOI irr=0x%02x isr=0x%02x\n", reg.irr, reg.isr);

        //
        // Rotate priority if selected
        //
        if (reg.ocw2.bits.r) {
            bhmMessage("F", PREFIX, "evaluate() Rotate Priority\n");
        }

        // If this is an eoi and no more pending - negate intp
        // The spec says this shoul happen from an intack, but maybe not
        if (reg.irr & ~(reg.ocw1.byte)) intp = 0;
    }

    //
    // Set output values
    //
    guard_assign (&pin.intp, intpHandle, intp, "intp");

    //
    // shift last values from current for edge detection
    // and negate any flags
    //
    for (i=0; i<8; i++) {
        pin.ir[i].last = pin.ir[i].value;
    }
    pin.intack = False;
    pin.eoi = False;
}

/*
 * There are 2 registers which can be read/written. The ordering and values
 * control a statemachine for the initialisation state variable nextState
 */

PPM_REG_READ_CB(CB_intack) {
    if(PSE_DIAG_LOW)
        bhmMessage("I", PREFIX, "EVENT %f: intack", bhmGetCurrentTime());

    pin.intack = True;
    evaluate();

    if(PSE_DIAG_LOW)
        bhmMessage("I", PREFIX, "EVENT %f: irqack=%d", bhmGetCurrentTime(), reg.irqack);

    return reg.irqack;
}

PPM_REG_READ_CB(CB_ior0) {
    Uns8 ret = 0;

    //
    // Poll command
    //
    if (reg.ocw3.bits.p) {
        bhmMessage("F", PREFIX, "CB_ior0 poll mode unsupported");
    } else {
        if (reg.ocw3.bits.rr) {
            if (reg.ocw3.bits.ris) {
                ret = reg.isr;
                if(PSE_DIAG_LOW)
                    bhmMessage("I", PREFIX, "EVENT %f: CB_ior0 read isr=0x%02x", bhmGetCurrentTime(), ret);
            } else {
                ret = reg.irr;
                if(PSE_DIAG_LOW)
                    bhmMessage("I", PREFIX, "EVENT %f: CB_ior0 read irr=0x%02x", bhmGetCurrentTime(), ret);
            }
        } else {
            bhmMessage("F", PREFIX, "CB_ior1 illegal mode reg.ocw3.bits.rr=0");
        }
    }

    return ret;

}

PPM_REG_READ_CB(CB_ior1) {
    Uns32 ret = 0;

    //
    // Poll command
    //
    if (reg.ocw3.bits.p) {
        bhmMessage("F", PREFIX, "CB_ior1 poll mode unsupported");
    } else {
        ret = reg.ocw1.byte;
        if(PSE_DIAG_LOW)
            bhmMessage("I", PREFIX, "EVENT %f: CB_ior1 read imr=0x%02x", bhmGetCurrentTime(), ret);
    }

    return ret;
}

PPM_REG_WRITE_CB(CB_iow0) {

    //
    // Init :: bit D4 set to 1
    //
    if (D4 & data) {
        reg.icw1.byte = data;
        if (PSE_DIAG_LOW) icw1Print();
        nextState = icw2;
    } else {

        if (nextState == ready) {
            // otherwise it is an opw
            // ocw1 = A0
            // ocw2 = !A0 & !D4 & !D3
            // ocw3 = !A0 & !D4 & D3
            if (!(D3 & data)) {
                reg.ocw2.byte = data;
                if (reg.ocw2.bits.eoi) {
                    pin.eoi = True;
                }
                if (PSE_DIAG_LOW) ocw2Print();
            } else {
                reg.ocw3.byte = data;
                if (PSE_DIAG_LOW) ocw3Print();
            }
        } else {
            if (PSE_DIAG_LOW) {
                bhmMessage("F", PREFIX, "Attempting to write  without correct initialisation");
            }
        }
    }

    evaluate();
}

PPM_REG_WRITE_CB(CB_iow1) {

    if (nextState == ready) {
        reg.ocw1.byte = data;
        if (PSE_DIAG_LOW) ocw1Print();
    } else {
        switch (nextState) {
        case icw2:
            reg.icw2.byte = data;
            if (PSE_DIAG_LOW) icw2Print();
            if (reg.icw1.bits.sngl == 0) {
                nextState = icw3;
            } else {
                if (reg.icw1.bits.ic4 == 0) {
                    nextState = ready;
                } else {
                    nextState = icw4;
                }
            }
            break;

        case icw3:
            reg.icw3.byte = data;
            if (PSE_DIAG_LOW) icw3Print();
            if (reg.icw1.bits.ic4 == 0) {
                nextState = ready;
            } else {
                nextState = icw4;
            }
            break;

        case icw4:
            reg.icw4.byte = data;
            if (PSE_DIAG_LOW) icw4Print();
            nextState = ready;
            //if (reg.icw4.bits.aeoi) bhmMessage("F", PREFIX, "AEOI=1 unsupported");
            break;

        default:
            if (PSE_DIAG_HIGH) {
                bhmMessage("F", PREFIX, "Bad state in initialisation nextState=%d", nextState);
            }
            break;
        }
    }

    evaluate();
}

//
// Any change on ir[0-7] calls this function
// This must call all subsequent functions
//
static void CB_ir(Uns64 value, void *user)
{

    Uns32 index = PTR_TO_UNS32(user);
    if(PSE_DIAG_LOW)
        bhmMessage("I", PREFIX, "EVENT %f: ir%d=%d", bhmGetCurrentTime(), index, (Uns32)value);

    pin.ir[index].value = value;
    evaluate();
}

static PPM_VIEW_CB(viewReg8) {
    *(Uns8*)data = *(Uns8*)user;
}

static void busPortConnections(void)
{
    ppmCreateRegister("PCIackS", "PCIackS", handles.PCIackS,   0,    1, CB_intack,    NULL, NULL,     NULL,    True);

    ppmCreateInternalRegister("icw1", "Initialization Control Word 1", 1, viewReg8, &reg.icw1.byte);
    ppmCreateInternalRegister("icw2", "Initialization Control Word 2", 1, viewReg8, &reg.icw2.byte);
    ppmCreateInternalRegister("icw3", "Initialization Control Word 3", 1, viewReg8, &reg.icw3.byte);
    ppmCreateInternalRegister("icw4", "Initialization Control Word 4", 1, viewReg8, &reg.icw4.byte);

    ppmCreateInternalRegister("ocw1", "Operation Control Word 1", 1, viewReg8, &reg.ocw1.byte);
    ppmCreateInternalRegister("ocw2", "Operation Control Word 2", 1, viewReg8, &reg.ocw2.byte);
    ppmCreateInternalRegister("ocw3", "Operation Control Word 3", 1, viewReg8, &reg.ocw3.byte);

    cascadeBus = ppmOpenMasterBusPort("cascade", cascadeWindow, sizeof(cascadeWindow), 0);
}

static void getSpen() {
    char spenString[8];

    // check for Master / Slave mode
    master = True;  slave = False;

    Bool setSpen = bhmStringParamValue("spen", spenString, sizeof(spenString));
    if(setSpen){
        if(!strcmp(spenString, "slave")){
            master = False; slave = True;
        }
    }
}

static void netPortConnections(void) {

    intpHandle = ppmOpenNetPort("intp");
    if (!intpHandle) {
        bhmMessage("F", "I8259", "'intp' pin must be connected");
    }

    irHandle[0] = ppmOpenNetPort("ir0");
    irHandle[1] = ppmOpenNetPort("ir1");
    irHandle[2] = ppmOpenNetPort("ir2");
    irHandle[3] = ppmOpenNetPort("ir3");
    irHandle[4] = ppmOpenNetPort("ir4");
    irHandle[5] = ppmOpenNetPort("ir5");
    irHandle[6] = ppmOpenNetPort("ir6");
    irHandle[7] = ppmOpenNetPort("ir7");

    int i;
    for(i=0; i < 8; i++) {
        if(irHandle[i]) {
            // if port is connected in platform, install the std callback
            ppmInstallNetCallback(irHandle[i], CB_ir, UNS32_TO_PTR(i));
            if(PSE_DIAG_MEDIUM) {
                bhmMessage("I", PREFIX, "'ir%d' is connected", i);
            }
        }
    }
}

PPM_CONSTRUCTOR_CB(constructor) {
    // YOUR CODE HERE (pre constructor)
    periphConstructor();
    // YOUR CODE HERE (post constructor)

    busPortConnections();
    netPortConnections();
    getSpen();

    //
    // Initialise the priority encoder
    // lowest number = highest priority
    //
    int i;
    for (i=0; i<=7; i++) {
        reg.priority[i] = i;
        pin.ir[i].byte = 0;
    }
    pin.intp = 0;
    pin.intack = False;
    pin.eoi = False;

}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

