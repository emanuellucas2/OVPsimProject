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


#include <string.h>
#include <stdlib.h>

#include "op/op.h"


#define MODULE_NAME "testpacketnet"


typedef struct optModuleObjectS {
    // insert module persistent data here
} optModuleObject;

//
// This code defines how the packetnet carries data.
// It is shared by this test module and all models that use the packetnet.
//
#include "../common/common.h"

//
// This callback is attached to the packetnet so can be used to monitor
// the traffic and maybe check the protocol for correctness.
// This example simply prints the packet contents, and by incrementing the
// tail value, pretends to be another device on the packetnet.
//
static OP_PACKETNET_WRITE_FN(packetnetFunction) {
    netPacketP p = data;
    if(p && bytes) {
        opMessage("I", MODULE_NAME "_PKT_RXD",
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
    optPacketnetP pkn = opObjectByName(mi, "pktNet", OP_PACKETNET_EN).Packetnet;

    netPacket p = { 1, {'A', 'P', 'I', 'T', 'X', 0 }, 0 };

    opMessage("I", MODULE_NAME "_PKT_TXS",
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

    opMessage("I", MODULE_NAME "_PKT_TXE",
        "%s: writePkt DONE {%02x}, {%s}, {%02x}",
        opObjectHierName(pkn),
        p.head,
        p.data,
        p.tail
    );
}

// forward declaration of component constructor
static OP_CONSTRUCT_FN(instantiateComponents);

static OP_CONSTRUCT_FN(moduleConstructor) {

    // instantiate module components
    instantiateComponents(mi, object);

    // insert constructor code here
}

static OP_PRE_SIMULATE_FN(modulePreSimulate) {
    //
    // Add callback onto the packetnet connection
    //
    optPacketnetP pkn = opObjectByName(mi, "pktNet", OP_PACKETNET_EN).Packetnet;
    opPacketnetWriteMonitorAdd(pkn, packetnetFunction, 0);
}

static OP_SIMULATE_STARTING_FN(moduleSimulateStart) {
// insert simulation starting code here
}

static OP_POST_SIMULATE_FN(modulePostSimulate) {
    //
    // Write to the packetnet
    //
    packetWrite(mi);
}

static OP_DESTRUCT_FN(moduleDestruct) {
// insert destructor code here
}

#include "module.igen.h"
