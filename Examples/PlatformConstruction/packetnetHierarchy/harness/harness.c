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
//                           Imperas/OVP Generated
//
////////////////////////////////////////////////////////////////////////////////


// This file declares functions to be implemented by the user.
// Be careful to avoid overwriting any edits should igen be re-run.


#include <string.h>
#include <stdlib.h>

#include "op/op.h"
#include "../common/common.h"


// Change the name here if required.

#define HARNESS_NAME "harness"


////////////////////////////////////////////////////////////////////////////////
//                         U S E R   F U N C T I O N S
////////////////////////////////////////////////////////////////////////////////

//
// This function is called when a packetnet is received
//
static OP_PACKETNET_WRITE_FN(packetnetFunction) {
    netPacketP p = data;
    if(p && bytes) {
        opMessage("I", HARNESS_NAME "_PKT_RXD",
            "Platform PKT testbench Trigger bytes=%u {%02x}, {%s}, {%02x} UD=0x%x\n",
            bytes,
            p->head,
            p->data,
            p->tail,
            (Uns32)(UnsPS)userData
        );

        // increment this tail value. In our simple protocol this tells anyone
        // watching the packet that we received it.
        p->tail++;
    }
}

//
// Send a packetnet and reports the fact
//
static void packetWrite(optModuleP mi) {
    optPacketnetP pkn = opObjectByName(mi, "pktnet", OP_PACKETNET_EN).Packetnet;

    netPacket p = { 1, {'I', 'C', 'M', 0, 0, 0 }, 0 };

    opMessage("I", HARNESS_NAME "_PKT_TXS",
        "%s: writePkt START {%02x}, {%s}, {%02x}",
        opObjectHierName(pkn),
        p.head,
        p.data,
        p.tail
    );

    // This is the function that triggers the packetnet.
    // All models with a callback installed on this packetnet
    // will be notified while this function is active.

    opPacketnetWrite(pkn, &p, sizeof(netPacket));

    // Now that the function has returned, we are certain that all
    // models have been notified. Their notifier callbacks have finished,
    // and if thet chose to modify the data in the packet, we can see the
    // modification here.

    opMessage("I", HARNESS_NAME "_PKT_TXE",
        "%s: writePkt DONE {%02x}, {%s}, {%02x}",
        opObjectHierName(pkn),
        p.head,
        p.data,
        p.tail
    );
    opPrintf("\n");
}


////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char *argv[]) {

    opSessionInit(OP_VERSION);
    opCmdParseStd(HARNESS_NAME, OP_AC_ALL, argc, argv);

    optModuleP top = opRootModuleNew(0, 0, 0);

    //
    // Add packetnet for connection to module packetnetPort
    //
    optPacketnetP pktnet_pkn = opPacketnetNew(top, "pktnet", 0, 0);

    //
    // Add new module containing
    //
    opModuleNew(
        top,              // parent module
        "module",         // modelfile
        "uut",            // name
        OP_CONNECTIONS(
            OP_PACKETNET_CONNECTIONS(
                OP_PACKETNET_CONNECT(pktnet_pkn, "pktnetPort")
            )
        ),
        0        // parameters
    );

    //
    // Add callback onto the packetnet connection
    //
    opPacketnetWriteMonitorAdd(pktnet_pkn, packetnetFunction, 0);

    opRootModuleSimulate(top);

    //
    // Write to the packetnet
    //
    packetWrite(top);
    
    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

