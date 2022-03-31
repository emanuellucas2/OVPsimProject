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
#include <string.h>

#include "pse.igen.h"

#define PREFIX "NOC_NODE"

typedef struct networkDataS {
    unsigned int toid;
    unsigned int fromid;
    unsigned int nid;
    unsigned int length;
    unsigned int data[0x100/4];
} networkDataT, *networkDataP;

Uns32 thisNodeId = 0;

/*************************************************************
 * Byte Swapping Function
 * PSE interface is always host (little) endian
 *************************************************************/

Bool byteSwap = False;

//
// convert a word for endian
//
static inline Uns32 BSWAP_UNS32(Uns32 p)
{
    return SWAP_4_BYTE_COND(p, byteSwap);
}

//////////////////////////////// Callback stubs ////////////////////////////////

#define regs hostif_reg_data
#define txM  hostif_msgtx_data
#define rxM  hostif_msgrx_data

networkDataT networkTx;
networkDataP networkRxP;

PPM_PACKETNET_CB(networkrx) {

    // receive packet if for this node and update status register
    networkRxP = data;
    Uns32  *rxMData = (Uns32 *)(handles.hostif + 0x210);

    if(networkRxP->toid == thisNodeId) {

        if (BSWAP_UNS32(regs.status.value) & 0x1) {
            // message in buffer, indicate overflow
            regs.status.value = (BSWAP_UNS32(BSWAP_UNS32(regs.status.value) | 0x2));

            if(PSE_DIAG_LOW) {
                bhmMessage("W", PREFIX, "Overflow : Lost received Message from %d to %d data 0x%08x length %d",
                                   networkRxP->fromid, networkRxP->toid, networkRxP->data[0], networkRxP->length);
            }
        } else {
            rxM.id.value      = BSWAP_UNS32(thisNodeId);
            rxM.from.value    = BSWAP_UNS32(networkRxP->fromid);
            rxM.nid.value     = BSWAP_UNS32(networkRxP->nid);
            rxM.msgLen.value  = BSWAP_UNS32(networkRxP->length);
            Uns32 i;
            for (i=0;i<rxM.msgLen.value;i++) {
                rxMData[i]        = BSWAP_UNS32(networkRxP->data[i]);
            }

            // Message received
            regs.status.value = BSWAP_UNS32(1);

            if(PSE_DIAG_LOW) {
                bhmMessage("I", PREFIX, "Received Message from %d to %d data[0] 0x%08x length %d",
                            networkRxP->fromid, networkRxP->toid, networkRxP->data[0], networkRxP->length);
            }
        }
    } else {
        // Message seen but not for this node
        regs.status.value = BSWAP_UNS32(BSWAP_UNS32(regs.status.value) | 0x01000000);

        if(PSE_DIAG_MEDIUM) {
            bhmMessage("I", PREFIX, "Ignore Message from %d to %d",
                               networkRxP->fromid, networkRxP->toid);
        }
    }
}

PPM_REG_WRITE_CB(writeControl) {

    // no need to record control as we send immediately
    //    *(Uns32*)user = data;

    if (BSWAP_UNS32(data) & 1) {
        Uns32  *txMData = (Uns32 *)(handles.hostif + 0x110);

        networkTx.fromid  = thisNodeId;
        networkTx.toid    = BSWAP_UNS32(txM.id.value);
        networkTx.nid     = BSWAP_UNS32(txM.nid.value);
        networkTx.length  = BSWAP_UNS32(txM.msgLen.value);
        Uns32 i;
        for (i=0;i<networkTx.length;i++) {
            networkTx.data[i] = BSWAP_UNS32(txMData[i]);
        }

        Uns32 length = 16 + (4*networkTx.length);

        if(PSE_DIAG_LOW) {
            bhmMessage("I", PREFIX, "Sending Message from %d to %d data[0] 0x%08x length %d",
                       networkTx.fromid, networkTx.toid, networkTx.data[0], networkTx.length);
        }

        ppmPacketnetWrite(handles.network, &networkTx, length);
    } else if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Control Word 0x%08x", BSWAP_UNS32(data));
    }


}

PPM_CONSTRUCTOR_CB(constructor) {
    if(PSE_DIAG_MEDIUM) {
        bhmMessage("I", PREFIX, "Initializing");
    }
    periphConstructor();

    char endianString[8];
    // check for an endian attribute
    Bool setEndian = bhmStringParamValue("endian", endianString, sizeof(endianString));
    if(setEndian && !strcmp(endianString, "big")){
        byteSwap = True;
    }
    if(PSE_DIAG_MEDIUM) {
        bhmMessage("I", PREFIX, "Interface Endian %s", byteSwap ? "BIG" : "LITTLE");
    }

    if (!handles.network) {
        bhmMessage("E", PREFIX, "Packetnet: Network connection not made");
    }

    // get Id for NoC node
    if (!bhmUns32ParamValue("id", &thisNodeId)) {
        bhmMessage("E", PREFIX, "Node Id has not been initialized in hardware design");
    }
}

PPM_DESTRUCTOR_CB(destructor) {
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}
