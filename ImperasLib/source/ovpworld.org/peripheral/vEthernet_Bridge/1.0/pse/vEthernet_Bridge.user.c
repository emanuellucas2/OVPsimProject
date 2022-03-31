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

#include "pse.igen.h"
#include "peripheral/bhm.h"
#include "peripheral/ppm.h"

bhmEtherCh ethernet;

static void printBuffer(Uns8 *data, Uns32 bytes) {
    Uns32 i;
    for(i = 0; i < bytes; i++) {
        bhmPrintf(" %02x", data[i]);
        if(i > 10) {
            bhmPrintf("...");
            break;
        }
    }
    bhmPrintf("\n");
}

static BHM_ETHER_PACKET_CB(rxPacket) {
    if (PSE_DIAG_LOW) {
        bhmMessage( "I", "ETH_BRD_EP", "Ethernet bridge passing %u bytes from ethernet to packetnet", bytes);
        if (PSE_DIAG_HIGH) {
            printBuffer(data, bytes);
        }
    }
    ppmPacketnetWrite(handles.phyBridge, data, bytes);
}

PPM_PACKETNET_CB(pktTrigger) {
    if (PSE_DIAG_LOW) {
        bhmMessage( "I", "ETH_BRD_PE", "Ethernet bridge passing %u bytes from packetnet to ethernet", bytes);
        if (PSE_DIAG_HIGH) {
            printBuffer(data, bytes);
        }
    }
    bhmEthernetWriteFrameN(ethernet, (Uns8*)data, bytes);
}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();
    ethernet = bhmEthernetOpenAuto();
    bhmEthernetInstallCB(ethernet, rxPacket, 0);
}

PPM_DESTRUCTOR_CB(destructor) {
    bhmEthernetClose(ethernet);
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}


