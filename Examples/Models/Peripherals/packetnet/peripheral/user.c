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


/*
 * This file was originally created by Imperas iGen, then modified by a
 * user by the addition of a body to the packetnet notifier function
 * pktTrigger()
 *
 * The txWrite function, called when the memory mapped register 'tx' is
 * written by the application processor, has been modified to transmit data
 * on the packetnet via the packetnet port defined in the TCL for this model.
 */


#include "pse.igen.h"
#include "../common/common.h"

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_PACKETNET_CB(pktTrigger) {
    netPacketP p = data;
    bhmMessage("I", "PKT_PSERXD",
            "Peripheral PKT model Trigger bytes=%d {%02x}, {%s}, {%02x} UD=%d\n",
            bytes,
            p->head,
            p->data,
            p->tail,
            PTR_TO_UNS32(userData)
    );
    p->tail++;
}

PPM_REG_READ_CB(txRead) {
    // no change to this function
    return *(Uns8*)user;
}

PPM_REG_WRITE_CB(txWrite) {
    netPacket packet = { data, {'P','S','E', 'T','X',0}, 0 };
    bhmMessage("I", "PKT_PSETXS", "PSE to packetnet START {%02x} {%s} {%02x} \n", packet.head, packet.data, packet.tail);

    ppmPacketnetWrite(handles.pktPort, &packet, sizeof(packet));

    bhmMessage("I", "PKT_PSETXE", "PSE to packetnet DONE  {%02x} {%s} {%02x} \n", packet.head, packet.data, packet.tail);
    bhmPrintf("\n");

    *(Uns8*)user = data;
}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();
}

PPM_DESTRUCTOR_CB(destructor) {
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}





