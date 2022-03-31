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

#include "pse.igen.h"
#define FUNC_NAME __FUNCTION__

#define INFO if (PSE_DIAG_HIGH) {bhmMessage("I", "AIC", "val=0x%08x", data);}
#define TODO if (PSE_DIAG_HIGH) {bhmMessage("F", "AIC", "TODO");}
//
// Structure to hold the current value of input interrupt pins
//
enum {
    FIQ,
    SWIRQ,
    US0IRQ,
    US1IRQ,
    TC0IRQ,
    TC1IRQ,
    TC2IRQ,
    WDIRQ,
    PIOIRQ,
    IRQ0=16,
    IRQ1,
    IRQ2
} pinIndex;

struct {
    Uns32 pins;
    Uns32 activeInt;
    Uns32 nfiq, nirq;
} state;

//
// Write the NFIQ if the value changes
//
void write_nfiq(Uns32 value) {
    if (state.nfiq != value) {
        state.nfiq = value;
        if (PSE_DIAG_HIGH) bhmMessage("I", "AIC", "Setting Interrupt NFIQ=%d\n", state.nfiq);
        ppmWriteNet(handles.NFIQ, state.nfiq);
    }
}

//
// Write the NIRQ if the value changes
//
void write_nirq(Uns32 value) {
    if (state.nirq != value) {
        state.nirq = value;
        if (PSE_DIAG_HIGH) bhmMessage("I", "AIC", "Setting Interrupt NIRQ=%d\n", state.nirq);
        ppmWriteNet(handles.NIRQ, state.nirq);
    }
}

Uns32 read_nfiq() {
    return state.nfiq;
}

Uns32 read_nirq() {
    return state.nirq;
}

//
// Update the state following a pin change, and raise interrupts accordingly
//
static void updateState() {
    if (PSE_DIAG_HIGH) bhmMessage("I", "AIC", "updateState state.pins=0x%08x", state.pins);
    
    //
    // Test against the Source Mode Register for the active level
    // of the pin, if the pin is the active level this will be set at 1, else 0
    // Internal sources are active High and cannot be overridden P.76/doc6410.pdf
    // 
    Bool rFIQ    = ((state.pins >> FIQ)    & 0x1);
    Bool rSWIRQ  = ((state.pins >> SWIRQ)  & 0x1);
    Bool rUS0IRQ = ((state.pins >> US0IRQ) & 0x1);
    Bool rUS1IRQ = ((state.pins >> US1IRQ) & 0x1);
    Bool rTC0IRQ = ((state.pins >> TC0IRQ) & 0x1);
    Bool rTC1IRQ = ((state.pins >> TC1IRQ) & 0x1);
    Bool rTC2IRQ = ((state.pins >> TC2IRQ) & 0x1);
    Bool rWDIRQ  = ((state.pins >> WDIRQ)  & 0x1);
    Bool rPIOIRQ = ((state.pins >> PIOIRQ) & 0x1);
    //
    // External source active level is programmable
    //
    Bool rIRQ0   = !(((bp1_REG_data.AIC_SMR[16].bits.SRCTYPE) >> 1) & 0x1) ^ ((state.pins >> IRQ0)   & 0x1);
    Bool rIRQ1   = !(((bp1_REG_data.AIC_SMR[17].bits.SRCTYPE) >> 1) & 0x1) ^ ((state.pins >> IRQ1)   & 0x1);
    Bool rIRQ2   = !(((bp1_REG_data.AIC_SMR[18].bits.SRCTYPE) >> 1) & 0x1) ^ ((state.pins >> IRQ2)   & 0x1);
    rIRQ0 = 0;
    rIRQ1 = 0;
    rIRQ2 = 0;
    
    //
    // Get priority of each of the Interrupts
    //
    Uns32 pFIQ    = bp1_REG_data.AIC_SMR[0].bits.PRIOR;
    Uns32 pSWIRQ  = bp1_REG_data.AIC_SMR[1].bits.PRIOR;
    Uns32 pUS0IRQ = bp1_REG_data.AIC_SMR[2].bits.PRIOR;
    Uns32 pUS1IRQ = bp1_REG_data.AIC_SMR[3].bits.PRIOR;
    Uns32 pTC0IRQ = bp1_REG_data.AIC_SMR[4].bits.PRIOR;
    Uns32 pTC1IRQ = bp1_REG_data.AIC_SMR[5].bits.PRIOR;
    Uns32 pTC2IRQ = bp1_REG_data.AIC_SMR[6].bits.PRIOR;
    Uns32 pWDIRQ  = bp1_REG_data.AIC_SMR[7].bits.PRIOR;
    Uns32 pPIOIRQ = bp1_REG_data.AIC_SMR[8].bits.PRIOR;
    Uns32 pIRQ0   = bp1_REG_data.AIC_SMR[16].bits.PRIOR;
    Uns32 pIRQ1   = bp1_REG_data.AIC_SMR[17].bits.PRIOR;
    Uns32 pIRQ2   = bp1_REG_data.AIC_SMR[18].bits.PRIOR;
    
    //
    // Get source Vector register
    //
    Uns32 vFIQ    = bp1_REG_data.AIC_SVR[0].value;
    Uns32 vSWIRQ  = bp1_REG_data.AIC_SVR[1].value;
    Uns32 vUS0IRQ = bp1_REG_data.AIC_SVR[2].value;
    Uns32 vUS1IRQ = bp1_REG_data.AIC_SVR[3].value;
    Uns32 vTC0IRQ = bp1_REG_data.AIC_SVR[4].value;
    Uns32 vTC1IRQ = bp1_REG_data.AIC_SVR[5].value;
    Uns32 vTC2IRQ = bp1_REG_data.AIC_SVR[6].value;
    Uns32 vWDIRQ  = bp1_REG_data.AIC_SVR[7].value;
    Uns32 vPIOIRQ = bp1_REG_data.AIC_SVR[8].value;
    Uns32 vIRQ0   = bp1_REG_data.AIC_SVR[16].value;
    Uns32 vIRQ1   = bp1_REG_data.AIC_SVR[17].value;
    Uns32 vIRQ2   = bp1_REG_data.AIC_SVR[18].value;
    
    //
    // Reassemble to a vector to apply mask, latching behavior
    // 
    state.activeInt |= 
        (rFIQ<<FIQ)       |
        (rSWIRQ<<SWIRQ)   |
        (rUS0IRQ<<US0IRQ) |
        (rUS1IRQ<<US1IRQ) |
        (rTC0IRQ<<TC0IRQ) |
        (rTC1IRQ<<TC1IRQ) |
        (rTC2IRQ<<TC2IRQ) |
        (rWDIRQ<<WDIRQ)   |
        (rPIOIRQ<<PIOIRQ) |
        (rIRQ0<<IRQ0)     |
        (rIRQ1<<IRQ1)     |
        (rIRQ2<<IRQ2);
        
    // Test against the Mask
    state.activeInt &= bp1_REG_data.AIC_IMR.value;
    bp1_REG_data.AIC_IPR.value = state.activeInt;
    
    //
    // If there is an interrupt, get highest priority, if it is FIQ, then only set that
    // TODO: What happens if a new interrupt arrives, whilst one is being serviced ?
    if (state.activeInt) {
        if (PSE_DIAG_HIGH) bhmMessage("I", "AIC", "updateState state.activeInt=%08x", state.activeInt);

        //
        // Update the AIC_IVR by iterating through the highest priority Interrupt
        //
        Uns32 priority=0;
        Uns32 sig=0;
        Uns32 vec=0;
        //#define PRIORITY(_name) if (r##_name && (p##_name > priority)) {priority = p##_name; sig = _name; vec = v##_name;}
        #define PRIORITY(_name) if ((state.activeInt & (1 << _name)) && (p##_name >= priority)) {priority = p##_name; sig = _name; vec = v##_name;}
        PRIORITY(FIQ);
        PRIORITY(SWIRQ);
        PRIORITY(US0IRQ);
        PRIORITY(US1IRQ);
        PRIORITY(TC0IRQ);
        PRIORITY(TC1IRQ);
        PRIORITY(TC2IRQ);
        PRIORITY(WDIRQ);
        PRIORITY(PIOIRQ);
        PRIORITY(IRQ0);
        PRIORITY(IRQ1);
        PRIORITY(IRQ2);
        
        // Set the IVR to be the highest priority SVR
        bp1_REG_data.AIC_IVR.value = vec;
        bp1_REG_data.AIC_ISR.value = sig;
    }
    
    // Assert FIQ
    Uns32 fiqState = (state.activeInt & 0x1) ? 1 : 0;
    write_nfiq(fiqState);

    // Assert FIQ
    Uns32 irqState = (state.activeInt & ~0x1) ? 1 : 0;
    write_nirq(irqState);
}

// Update the pins structure
// Only set to a 1 if this is the active state
#define MACRO_CHECK_INT(_name) \
    Uns32 pins = state.pins; \
    ppmNetValue next = ppmReadNet(handles. _name); \
    if (next) { \
        state.pins |= (1 << _name); \
    } else { \
        state.pins &= ~(1 << _name); \
    } \
    if (pins != state.pins) updateState();

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_NBYTE_WRITE_CB(AIC_SMR_wcb) {
    Uns32 index = PTR_TO_UNS32(userData);
    bp1_REG_data.AIC_SMR[index].value = *(Uns32*)data;
}

PPM_NBYTE_WRITE_CB(AIC_SVR_wcb) {
    Uns32 index = PTR_TO_UNS32(userData);
    bp1_REG_data.AIC_SVR[index].value = *(Uns32*)data;
}

//
// Clear current interrupt and roll down to next priority interrupt
//
PPM_REG_WRITE_CB(AIC_EOICR_wcb) {
    // YOUR CODE HERE (AIC_EOICR_wcb)
    bp1_REG_data.AIC_EOICR.value = data;

    //
    // Clear the current IRQ and update.
    //
    write_nirq(0);
    write_nfiq(0);
    bp1_REG_data.AIC_ISR.value = 0; // This needs fixing
    //
    // Now remove the current Interrupt
    //
    updateState();
}

//
// Interrupt Clear Command Register
// 0 = no effect
// 1 = disable (Cleared)
//
PPM_REG_WRITE_CB(AIC_ICCR_wcb) {
    // YOUR CODE HERE (AIC_ICCR_wcb)
    bp1_REG_data.AIC_ICCR.value = data;

    bp1_REG_data.AIC_IPR.value &= ~bp1_REG_data.AIC_ICCR.value;
    INFO;
}

//
// Interrupt Disable Command Register
// 0 = no effect
// 1 = disabled (Masked)
//
PPM_REG_WRITE_CB(AIC_IDCR_wcb) {
    // YOUR CODE HERE (AIC_IDCR_wcb)
    bp1_REG_data.AIC_IDCR.value = data;
    
    bp1_REG_data.AIC_IMR.value &= ~bp1_REG_data.AIC_IDCR.value;
    updateState();
    INFO;
}

//
// Interrupt Enable Command Register
// 0 = no effect
// 1 = disable (unMasked)
//
PPM_REG_WRITE_CB(AIC_IECR_wcb) {
    // YOUR CODE HERE (AIC_IECR_wcb)
    bp1_REG_data.AIC_IECR.value = data;
    
    bp1_REG_data.AIC_IMR.value |= bp1_REG_data.AIC_IECR.value;
    updateState();
    INFO;
}

PPM_REG_WRITE_CB(AIC_ISCR_wcb) {
    // YOUR CODE HERE (AIC_ISCR_wcb)
    bp1_REG_data.AIC_ISCR.value = data;
    
    bp1_REG_data.AIC_IPR.value = bp1_REG_data.AIC_ISCR.value;
    INFO;
}

PPM_REG_WRITE_CB(AIC_SPU_wcb) {
    // YOUR CODE HERE (AIC_SPU_wcb)
    bp1_REG_data.AIC_SPU.value = data;
    INFO;
}

PPM_NET_CB(FIQ_wcb) {
    // YOUR CODE HERE (FIQ_wcb)
    MACRO_CHECK_INT(FIQ);
}

PPM_NET_CB(IRQ0_wcb) {
    // YOUR CODE HERE (IRQ0_wcb)
    MACRO_CHECK_INT(IRQ0);
}

PPM_NET_CB(IRQ1_wcb) {
    // YOUR CODE HERE (IRQ1_wcb)
    MACRO_CHECK_INT(IRQ1);
}

PPM_NET_CB(IRQ2_wcb) {
    // YOUR CODE HERE (IRQ2_wcb)
    MACRO_CHECK_INT(IRQ2);
}

PPM_NET_CB(PIOIRQ_wcb) {
    // YOUR CODE HERE (PIOIRQ_wcb)
    MACRO_CHECK_INT(PIOIRQ);
}

PPM_NET_CB(SWIRQ_wcb) {
    // YOUR CODE HERE (SWIRQ_wcb)
    MACRO_CHECK_INT(SWIRQ);
}

PPM_NET_CB(TC0IRQ_wcb) {
    // YOUR CODE HERE (TC0IRQ_wcb)
    MACRO_CHECK_INT(TC0IRQ);
}

PPM_NET_CB(TC1IRQ_wcb) {
    // YOUR CODE HERE (TC1IRQ_wcb)
    MACRO_CHECK_INT(TC1IRQ);
}

PPM_NET_CB(TC2IRQ_wcb) {
    // YOUR CODE HERE (TC2IRQ_wcb)
    MACRO_CHECK_INT(TC2IRQ);
}

PPM_NET_CB(US0IRQ_wcb) {
    // YOUR CODE HERE (US0IRQ_wcb)
    MACRO_CHECK_INT(US0IRQ);
}

PPM_NET_CB(US1IRQ_wcb) {
    // YOUR CODE HERE (US1IRQ_wcb)
    MACRO_CHECK_INT(US1IRQ);
}

PPM_NET_CB(WDIRQ_wcb) {
    // YOUR CODE HERE (WDIRQ_wcb)
    MACRO_CHECK_INT(WDIRQ);
}

PPM_REG_READ_CB(AIC_IVR_rcb) {
    // YOUR CODE HERE (AIC_IVR_rcb)
    
    // Deassert Interrupts
    //write_nirq(0);
    updateState();

    return *(Uns32*)user;
}

PPM_CONSTRUCTOR_CB(constructor) {
    // YOUR CODE HERE (pre constructor)
    periphConstructor();
    // YOUR CODE HERE (post constructor)
    
    // Initialise the Pin states
    state.pins = 0x0;
    
    // Deassert Interrupts
    write_nirq(0);
    write_nfiq(0);
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

