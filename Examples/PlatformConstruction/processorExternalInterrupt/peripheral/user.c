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

#include "pse.igen.h"
//////////////////////////////// Callback stubs ////////////////////////////////

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();

    Uns32 delayRate;        //default in uSeconds set by tcl default
    if(bhmUns32ParamValue("rate", &delayRate)) {
        bhmMessage("I", "TIMER_PSE", "Tick rate set at %g seconds", (double) (delayRate/1000000));
    }

    while (1) {
        // delay for tick rate
        bhmWaitDelay(delayRate);

        if(PSE_DIAG_LOW)
            bhmMessage("I", "TIMER_PSE", "Generating tick at %g seconds", (double) (bhmGetCurrentTime()/1000000));
        ppmWriteNet(handles.tickOut, 1);
    }
}

// interrupt acknowledge (used to clear interrupt)
PPM_REG_WRITE_CB(intAck) {

    *(Uns32*)user = data;

    if(ppmReadNet(handles.tickOut)) {
        if(PSE_DIAG_HIGH)
            bhmMessage("I", "TIMER_PSE", "Interrupt Acknowledge, clear interrupt");
        ppmWriteNet(handles.tickOut, 0);
    }

}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    bhmMessage("W", "PPM_RSNI", "Model does not implement additional save state function");
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    bhmMessage("W", "PPM_RSNI", "Model does not implement additional restore state function");
}

