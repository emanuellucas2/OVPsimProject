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

#define PSENAME "RESET_CONTROL"

#define SWAP4(_d) ( \
                    ((_d & 0xff000000) >> 24)  | \
                    ((_d & 0x00ff0000) >>  8)  | \
                    ((_d & 0x0000ff00) <<  8)  | \
                    ((_d & 0x000000ff) << 24)    \
                  )

// Control Register Write
PPM_REG_WRITE_CB(controlRegisterWrite) {

    // if bit one set toggle reset1
    if (SWAP4(data) & 1) {
        if(ppmReadNet(handles.resetOut1)) {
            bhmMessage("I", PSENAME "_CRWC1", " Control Register Write: Release reset1");
            ppmWriteNet(handles.resetOut1, 0);
        } else {
            bhmMessage("I", PSENAME "_CRWS1", " Control Register Write: Reset reset1");
            ppmWriteNet(handles.resetOut1, 1);
        }
    }
    // if bit two set toggle reset2
    if (SWAP4(data) & 2) {
        if(ppmReadNet(handles.resetOut2)) {
            bhmMessage("I", PSENAME "_CRWC2", " Control Register Write: Release reset2");
            ppmWriteNet(handles.resetOut2, 0);
        } else {
            bhmMessage("I", PSENAME "_CRWS2", " Control Register Write: Reset reset2");
            ppmWriteNet(handles.resetOut2, 1);
        }
    }
    // store current write value
    *(Uns32*)user = data;
}

#define MAXREAD 32
unsigned char startMessage[] = "Example Peripheral Reset Generation\ntype 'r<cr>' to force reset\n     'q<cr>' to finish simulation\n";

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
                    bhmMessage("I", PSENAME "_MT", "generate reset on reset1");
                    ppmWriteNet(handles.resetOut1, 1);
                    ppmWriteNet(handles.resetOut1, 0);
                    bhmMessage("I", PSENAME "_MT", "generate reset on reset2");
                    ppmWriteNet(handles.resetOut2, 1);
                    ppmWriteNet(handles.resetOut2, 0);
                }
                if (buffer[0] == 'q') {
                    bhmMessage("I", PSENAME "_MT", "Force Finish Simulation");
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

