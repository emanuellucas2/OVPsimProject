/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */

////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
////////////////////////////////////////////////////////////////////////////////

#include <string.h>

#include "pse.igen.h"

#define CHANNELS 2
#define INPUTS   32

Uns32 diags = 0;

static inline void setCurrentPriority(Uns32 ch, Uns32 priority) {
    sp1_ch_data[ch].channelControl.bits.currentPriority = priority;
}

static inline Uns32 getCurrentPriority(Uns32 ch) {
    return sp1_ch_data[ch].channelControl.bits.currentPriority;
}

static inline Bool usePriority(Uns32 ch) {
    return sp1_ch_data[ch].channelControl.bits.usePriority;
}

static inline Bool requesting(Uns32 ch, Uns32 input) {
    return sp1_ch_data[ch].pinControl[input].bits.raw != sp1_ch_data[ch].pinControl[input].bits.invert;
}

static inline Bool asserted(Uns32 ch, Uns32 input) {
    return sp1_ch_data[ch].pinControl[input].bits.asserted;
}

static inline Uns8 priority(Uns32 ch, Uns32 input) {
    return sp1_ch_data[ch].pinControl[input].bits.priority;
}

static void raiseInterrupt(Uns32 ch, Uns32 input) {
    if(diags) {
        bhmMessage("I", "INTC", "raise interrupt ch:%u   input:%u", ch, input);
    }
    sp1_ch_data[ch].pinControl[input].bits.asserted = 1;
    ppmWriteNet(handles.intout[ch], 1);
}

//
// Decide is an interrupt is to be generated
//
static void evaluateInterrupts(Uns32 ch, Uns32 input) {

    if(usePriority(ch)) {
        Uns32 current = getCurrentPriority(ch);
        Uns32 req     = priority(ch, input);
        if(diags) {
            bhmMessage("I", "INTC", "interrupt priority: current:%u  requested:%u   %s\n", current, req, (req > current) ? "Trigger" : "Non");
        }
        if(req > current) {

            raiseInterrupt(ch, input);

            // adjust current priority
            setCurrentPriority(ch, priority(ch, input));
        }
    } else {
        // No priorities
        if(diags) {
            bhmMessage("I", "INTC", "interrupt (no priority)\n");
        }
        raiseInterrupt(ch, input);
    }
}

static void nextLowestInterrupt(Uns32 ch) {
    // look for pending interrupts
    Int32 highestInput    = -1;
    Int32 highestPriority = -1;

    Uns32 input;
    for(input = 0; input < INPUTS; input++) {
        if(requesting(ch, input) && !asserted(ch, input)) {
            Uns32 p =  priority(ch, input);
            if(p > highestPriority) {
                highestPriority = p;
                highestInput    = input;
            }
        }
    }
    if(highestInput >= 0) {
        // found at least one
        evaluateInterrupts(ch, input);
    }
}

//
// Register callback
//
PPM_NBYTE_WRITE_CB(writeChannelControl) {
    Uns32 block = (offset-0x0)/0x40;
    memcpy(&(sp1_ch_data[block].channelControl.value), data, bytes);

    if(diags) {
        bhmMessage("I", "INTC", "writeChannelControl: ch:%u  value:0x%x\n", block, sp1_ch_data[block].channelControl.value);
    }
}


//
// Register callback
//
PPM_NBYTE_WRITE_CB(writePinControl) {
    Uns32 block = (offset-0x0) / 0x40;
    Uns32 regb  = (offset-0x0) % 0x40;
    Uns32 reg   = (regb-0x20) / 1;

    Uns32 prevAssert = asserted(block, reg);

    memcpy(&(sp1_ch_data[block].pinControl[reg].value), data, bytes);

    if(diags) {
        bhmMessage("I", "INTC", "writePinControl: ch:%u  reg:%u  value:0x%x\n", block, reg, sp1_ch_data[block].pinControl[reg].value);
    }

    if(prevAssert && !asserted(block, reg)) {

        if(diags) {
            bhmMessage("I", "INTC", "interrupt: cancelled  channel:%u   input:%u\n", block, reg);
        }
        // de-assert requested
        sp1_ch_data[block].pinControl[reg].bits.asserted = 0;
        ppmWriteNet(handles.intout[block], 0);
        setCurrentPriority(block, 0);

        nextLowestInterrupt(block);
    }
}

//
// The callback activated when the interrupt net is written
//
PPM_NET_CB(interruptArrived) {
    Uns32 input = PTR_TO_UNS32(userData);
    Uns32 ch  = input / INPUTS ;
    Uns32 pin = input % INPUTS;

    Uns32 old = sp1_ch_data[ch].pinControl[pin].bits.raw;

    if(value != old) {
        sp1_ch_data[ch].pinControl[pin].bits.raw = value;
        if(diags) {
            bhmMessage("I", "INTC", "interrupt: channel:%u   input:%u   new:%u\n", ch, pin, (Uns32)value);
        }
        if(requesting(ch, pin)) {
            evaluateInterrupts(ch, pin);
        }
    } else {
        if(diags) {
            bhmMessage("I", "INTC", "interrupt: channel:%u   input:%u  (no change)\n", ch, pin);
        }
    }
}

PPM_NET_CB(resetDevice) {
    // YOUR CODE HERE (resetDevice)
    reset_systemReset(1,0);
}

PPM_CONSTRUCTOR_CB(constructor) {
    // YOUR CODE HERE (pre constructor)
    periphConstructor();
    // YOUR CODE HERE (post constructor)

    diags = bhmGetDiagnosticLevel();
}

PPM_DESTRUCTOR_CB(destructor) {
    // YOUR CODE HERE (destructor)
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
    bhmMessage("E", "INTC_RSNI", "Model does not implement save/restore");
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    bhmMessage("E", "INTC_RSNI", "Model does not implement save/restore");
}


