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

#include "pse.igen.h"

#define PREFIX "BLK_TST"

//
// The user might wish to downgrade this to a warning then take action in the model.
//
static void checkAccessSize(Uns32 bytes) {
    if (bytes != 4) {
        bhmMessage("F", PREFIX, "Detected %u-byte access. This model supports only 4-byte.", bytes);
    }
}


//////////////////////////////// Callback stubs ////////////////////////////////

//
// This indicates CONTROL data is available
//
static Bool  CONTROLTready;

//
// This callback is called when register CONTROL is read. It operates in two
// modes:
//
// 1. If CONTROLTready is True, this indicates that data is available to be
//    read immediately. In this case, CONTROLTready is set to False and the
//    current value of CONTROL is returned.
//
// 2. If CONTROLTready is False, bhmWaitDelay(0) is called to wait for a delta
//    cycle delay. This has the following effects:
//    a. A PSE thread is implictly created to manage the delay. The state of
//       the PSE thread is cloned from the callback thread;
//    b. The callback thread is cancelled and returns immediately to the
//       initiating processor;
//    c. The initiating processor is blocked in a state in which, on resumption,
//       it will re-execute the read of the CONTROL register
//    d. After a delta cycle has elapsed, the implictly-created thread awakens.
//       It runs to its conclusion, preparing a new value for CONTROL and
//       indicating data is valid by setting CONTROLTready to True;
//    e. On return from the implictly-created thread, the initiating processor
//       is unblocked. It re-executes the read of the CONTROL register. Because
//       CONTROLTready is now True, execution proceeds as described in case 1
//       above, returning the new value of CONTROL.
//
// NOTE: in this example, bhmWaitDelay(0) is used to wait for a delta cycle. It
// is possible to use a non-zero delay here, or also wait for some other action
// (e.g. an event, using bhmWaitEvent).
//
PPM_NBYTE_READ_CB(rCONTROL) {

    checkAccessSize(bytes);

    if(artifactAccess) {

        // no blocking and no side effects
        *(Uns32*)data = bport1_REG_data.CONTROL.value;

    } else {

        if(CONTROLTready) {

            CONTROLTready = False;

            bhmMessage("I", PREFIX, "%s read: %u", __FUNCTION__, bport1_REG_data.CONTROL.value);

            // callback requires explicit data transfer
            *(Uns32*)data = bport1_REG_data.CONTROL.value;

        } else {

            // wait for arbitrary delay
            bhmMessage("I", PREFIX, "%s BEFORE TIME: %.2e", __FUNCTION__, bhmGetLocalTime());

            bhmWaitDelay(0);

            bport1_REG_data.CONTROL.value++;

            CONTROLTready = True;
            bhmMessage("I", PREFIX, "%s AFTER  TIME: %.2e", __FUNCTION__, bhmGetLocalTime());

            // If delayed, then (importantly) no transfer of data and no side effects.
        }
    }
}

//
// This callback is called when register CONTROL is written. See the description
// above for the semantics.
//
PPM_NBYTE_WRITE_CB(wCONTROL) {

    checkAccessSize(bytes);

    if(artifactAccess) {

        // no blocking and no side effects
        bport1_REG_data.CONTROL.value = *(Uns32*)data;

    } else {

        if(CONTROLTready) {

            CONTROLTready = False;

            // callback requires explicit data transfer
            bport1_REG_data.CONTROL.value = *(Uns32*)data;

            bhmMessage("I", PREFIX, "%s write:%u", __FUNCTION__, bport1_REG_data.CONTROL.value);
        } else {

            // wait for arbitrary delay
            bhmMessage("I", PREFIX, "%s BEFORE TIME: %.2e",
                __FUNCTION__, bhmGetLocalTime()
            );

            bhmWaitDelay(0);
            CONTROLTready = True;

            // wait for arbitrary delay
            bhmMessage("I", PREFIX, "%s AFTER  TIME: %.2e",
                __FUNCTION__, bhmGetLocalTime()
            );

            // No data transfer in the delay branch
        }
    }
}

PPM_NBYTE_READ_CB(regNoDefinitionRead) {

    checkAccessSize(bytes);

    bhmMessage("I", PREFIX, "%sDoes nothing", __FUNCTION__);
    *(Uns32*)data = 0;
}
 
PPM_NBYTE_WRITE_CB(regNoDefinitionWrite) {
     bhmMessage("I", PREFIX, "%s Does nothing", __FUNCTION__);
}


PPM_CONSTRUCTOR_CB(constructor) {
    // YOUR CODE HERE (pre constructor)
    periphConstructor();
    // YOUR CODE HERE (post constructor)
}

PPM_DESTRUCTOR_CB(destructor) {
    // YOUR CODE HERE (destructor)
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}


