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

#define MAXREAD 32
unsigned char startMessage[] = "Example Peripheral Reset Generation\ntype 'r' to force reset\n     'q' to finish simulation\n";

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();

    // open a tcp/ip socket using standard socket features
    // set parameter 'console' to open terminal and connect to port
    // set parameter 'portnum' to a port number to open and await manual connection
    Int32 channel = bhmSerOpenAuto();

    if (channel) {

        bhmSerWriteN(channel, startMessage, sizeof(startMessage));

        while (1) {
            //
            // Non Blocking read
            //
            Uns8 buffer[MAXREAD];
            Uns8 bytes = bhmSerReadN(channel, buffer, 1);

            if (bytes) {
                // echo value back to terminal
                bhmSerWriteN(channel, buffer, 1);

                if (buffer[0] == 'r') {
                    bhmMessage("I", "RESET", "Generate Reset");
                    ppmWriteNet(handles.resetOut, 1);
                    ppmWriteNet(handles.resetOut, 0);
                }
                if (buffer[0] == 'q') {
                    bhmFinish();
                }
            }
            // polling delay
            bhmWaitDelay(100);

        }
    }
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

