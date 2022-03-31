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


#define PREFIX "NOC_NODE"

#define MAXLINE    4096
#define MAXSTRING   128

typedef struct networkDataS {
    Uns32 toid;
    Uns32 fromid;
    Uns32 length;
    char  pS[8];
    char  pD[8];
    Uns32 data[256/4];
} networkDataT, *networkDataP;

Uns32 thisNodeId = 0;

#define CONFIG_LINE_ITEMS 8

typedef struct channelS {
    Uns32  number;  // channel number
    Uns32  length;  // message length in buffer
    Uns32  status;  // status information
    char  *pSP;     // pointer to info string
    Uns32  pSN;     // the source node
    char  *pDP;     // pointer to info string
    Uns32  pDN;     // the destination node
} channelT, *channelP;

channelT channelRx[10];
channelT channelTx[10];

Uns32 sizeSendChannels;     // controls position of fields in control word
Uns32 sizeMBox;             // controls stride between message boxes in message buffers inbox/outbox
Uns32 regStatus = 0;
Uns32 regHeartbeat = 0;

static volatile Bool syncFlagUpdate = False;
void clearSyncFlag() {
    if(!syncFlagUpdate) {
        if(PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX "_MEM", "Clear Sync");
        }
        *((Uns32*)(handles.hostif + HOSTIF_REG_SYNCH_OFFSET)) = 0;
    }
}
void setSyncFlag() {
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_NET_SYNC", "Synchronize Heartbeat");
    }

    syncFlagUpdate = True;
    *((Uns32*)(handles.hostif + HOSTIF_REG_SYNCH_OFFSET)) = 1;
    syncFlagUpdate = False;
}

//////////////////////////////// Callback stubs ////////////////////////////////

//#define regs hostif_reg_data

networkDataT networkTx;
networkDataP networkRxP;

PPM_PACKETNET_CB(networkReceiveMsg) {

    // receive packet if for this node and update status register
    networkRxP = data;

    if(networkRxP->toid == thisNodeId) {

        Uns32 channelNumber = 0;
        Bool found = False;
        while (channelRx[channelNumber].pDP) {
            if(strcmp(networkRxP->pD,channelRx[channelNumber].pDP) == 0) {
                found = True;
                break;
            } else
                channelNumber++;
        }
        if (found) {
            if(PSE_DIAG_HIGH) {
                bhmMessage("I", PREFIX, "Node %d: "
                                        "Found receive channel %d for process S %s D %s",
                        thisNodeId, channelNumber, networkRxP->pS, networkRxP->pD);
            }

            Uns32 offset = channelRx[channelNumber].number * sizeMBox;
            Uns32  *inMData = (Uns32 *)(handles.hostif + HOSTIF_INBOX_BUF_OFFSET + offset);

            Uns32 i;
            for (i=0;i<networkRxP->length;i++) {
                inMData[i] = networkRxP->data[i];
            }
            channelRx[channelNumber].length = networkRxP->length;     // length of message
            channelRx[channelNumber].status = 1;                      // message available

            if(PSE_DIAG_LOW) {
                bhmMessage("I", PREFIX, "Node %d: Received Message from %d to %d length %d"
                                        " channel %d process s %s d %s",
                        thisNodeId, networkRxP->fromid, networkRxP->toid,
                        networkRxP->length,
                        channelNumber, networkRxP->pS, networkRxP->pD);
            }
            if(PSE_DIAG_MEDIUM) {
                bhmPrintf("-- Data --\n");
                for (i=0;i<channelRx[channelNumber].length;i++) {
                    bhmPrintf("(%d) 0x%02x ", i, inMData[i]);
                }
                bhmPrintf("\n-- End Data --\n");
            }
        } else {
            if(PSE_DIAG_HIGH) {
                bhmMessage("W", PREFIX, "Node %d: "
                                        "Cannot find receive channel for process S %s D %s",
                        thisNodeId, networkRxP->pS, networkRxP->pD);
            }
        }
    } else {
        if(PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX, "node %d: Ignore Message from %d to %d",
                    thisNodeId, networkRxP->fromid, networkRxP->toid);
        }
    }
}

void networkTransmitMsg(Uns32 channel, Uns32 length, Uns32 dpid, Uns32 spid) {

    Uns32  offset   = channel * sizeMBox;
    Uns32 *outMData = (Uns32 *)(handles.hostif + HOSTIF_OUTBOX_BUF_OFFSET + offset);

    networkTx.fromid = channelTx[channel].pSN;  // should be same as thisNode
    networkTx.toid   = channelTx[channel].pDN;
    networkTx.length = length;
    strncpy(networkTx.pD, channelTx[channel].pDP, 7);
    strncpy(networkTx.pS, channelTx[channel].pSP, 7);

    Uns32 i;
    for (i=0;i<networkTx.length;i++) {
        networkTx.data[i] = outMData[i];
    }

    if(PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX, "Node %d: Sending Message from %d to %d length %d"
                                " channel %d spid %d dpid %d process S %s D %s",
                   thisNodeId, networkTx.fromid, networkTx.toid, networkTx.length,
                   channel, spid, dpid, networkTx.pS, networkTx.pD);
    }
    if(PSE_DIAG_MEDIUM) {
        bhmPrintf("-- Data --\n");
        for (i=0;i<networkTx.length;i++) {
            bhmPrintf("(%d) 0x%02x ", i, networkTx.data[i]);
        }
        bhmPrintf("\n-- End Data --\n");
    }

    ppmPacketnetWrite(handles.network, &networkTx, sizeof(networkTx));
}

PPM_NET_CB(syncInput) {
    // Set sync flag
    setSyncFlag();
}

PPM_REG_WRITE_CB(writeCommand) {
// Command definition    (priority<<(10+SIZE_SEND_CHANNELS))+(spid<<(6+SIZE_SEND_CHANNELS))+(dpid<<(2+SIZE_SEND_CHANNELS))+(buf<<2)+msg_size)
    Uns32 priority = ((data>>(10+sizeSendChannels)) & 0xf );
    Uns32 spid     = ((data>>( 6+sizeSendChannels)) & 0xf );
    Uns32 dpid     = ((data>>( 2+sizeSendChannels)) & 0xf  );
    Uns32 chanNo   = ((data>>( 2                 )) & ((1<<sizeSendChannels)-1));
    Uns32 msgSize  =   data                         & 0x0003;

    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_REG", "Write Command (0x%x), pri %d, spid %d, dpid %d, chanNo %d, sz %d, buffSz %d",
                         data, priority, spid, dpid, chanNo, msgSize , sizeSendChannels);
    }

    networkTransmitMsg(chanNo, msgSize, spid, dpid);
}


PPM_WRITE_CB(writeSyncFlag) {
    clearSyncFlag();
}

PPM_REG_READ_CB(readIntStatus) {
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_REG", "Read Interrupt Status");
    }
    return *(Uns32*)user;
}

PPM_REG_READ_CB(readNodeId) {
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_REG", "Read Node Id (%d)", thisNodeId);
    }
    return thisNodeId;
}

PPM_REG_READ_CB(readStatus) {
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_REG", "Read Status (0x%x)", regStatus);
    }
    return regStatus;
}

PPM_REG_WRITE_CB(writeHeartbeat) {
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_REG", "Write Heartbeat (%d)", data);
    }
    regHeartbeat = data;
}

PPM_REG_WRITE_CB(writeIntClr) {
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_REG", "Write Interrupt Control (0x%x)", data);
    }
    *(Uns32*)user = data;
}

PPM_READ_CB(readMsgLength) {
    Uns32 index  = (addr - handles.hostif) & 0x1f;
    Uns32 length = channelRx[index].length;
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_MSG_LEN", "index %d length %d", index, length);
    }
    return length;
}

PPM_READ_CB(readMsgStatus) {
    Uns32 index  = (addr - handles.hostif) & 0x1f;
    Uns32 status = channelRx[index].status;
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_MSG_LEN", "index %d status %d", index, status);
    }
    return status;
}

//
// thread only gets launched at next quantum boundary
//
bhmThreadHandle thread;

#define DEFAULT_SYNC  1000

void syncThread(void* user) {

    if(PSE_DIAG_LOW) {
        bhmMessage("I", PREFIX "_THRD", "Initialized");
    }

    while(1) {
        if(regHeartbeat) {
            if(PSE_DIAG_MEDIUM) {
                bhmMessage("I", PREFIX "_THRD_DLY", "%f", (double)(regHeartbeat));
            }
            bhmWaitDelay(regHeartbeat);
        } else {
            if(PSE_DIAG_MEDIUM) {
                bhmMessage("I", PREFIX "_THRD_DLY", "%f", (double)(DEFAULT_SYNC));
            }
            bhmWaitDelay(DEFAULT_SYNC);
        }

        if(PSE_DIAG_MEDIUM) {
            bhmMessage("I", PREFIX "_THRD", "Sync (%f)", bhmGetCurrentTime());
        }

        setSyncFlag();
        ppmWriteNet(handles.syncOut, 1);    // generate external sync signal
    }
}

PPM_CONSTRUCTOR_CB(constructor) {
    if(PSE_DIAG_MEDIUM) {
        bhmMessage("I", PREFIX, "Initializing");
    }

    periphConstructor();

    // get Id for NoC node
    if (!bhmUns32ParamValue("id", &thisNodeId)) {
        bhmMessage("E", PREFIX, "Node Id has not been initialized in hardware design");
    }
    if (!handles.network) {
        bhmMessage("E", PREFIX, "Packetnet: Network connection not made");
    }

    // get message buffer size (controls fields in control word)
    bhmUns32ParamValue("sendChannelSize", &sizeSendChannels);
    // get input and output mailbox size (controls stride between channels in inbox and outbox)
    bhmUns32ParamValue("mboxSize", &sizeMBox);

    FILE *configFileFP = NULL;

    char configFile[MAXSTRING];
    // check for an endian attribute
    if(!bhmStringParamValue("configfile", configFile, sizeof(configFile))) {
        bhmMessage("E", PREFIX, "Parameter 'configfile' must be specified to define network communication channels");
    } else {
        // TODO: channel info
        // open config file
        if(!(configFileFP = fopen(configFile, "r"))) {
            bhmMessage("E", PREFIX "_NCF", "Could not open config file '%s', "
                                           "specify using 'configfile' parameter",
                                           configFile);
        } else {
            // Read configuration information
            char line[MAXLINE];
            while (fgets(line, MAXLINE, configFileFP) != NULL){
                if (line[0] == '#') {
                    // Ignore comment line
                } else {
                    Uns32 node;
                    char channelDirection[8];
                    char toFrom[8];
                    char processS[8], processD[8];
                    Uns32 nodeS, nodeD;
                    Uns32 channelNumber;
                    Uns32 items;
                    // line contains
                    // <node name> <direction> <process Source> <node Source> <to or from> <process Dest> <node Dest> <channel>
                    if ((items = sscanf(line, "%d %7s %7s %d %7s %7s %d %d",
                                    &node, channelDirection,
                                    processS, &nodeS,
                                    toFrom,
                                    processD, &nodeD,
                                    &channelNumber)) != CONFIG_LINE_ITEMS) {
                        bhmMessage("E", PREFIX "_FCF", "Expected %d items, found %d in '%s'", CONFIG_LINE_ITEMS, items, line);
                    } else {
                        if (node == thisNodeId) {
                            if(strncmp(channelDirection, "send", 4) == 0) {
                                // add to configuration table
                                channelTx[channelNumber].pSP = strdup(processS);
                                channelTx[channelNumber].pSN = nodeS;
                                channelTx[channelNumber].pDP = strdup(processD);
                                channelTx[channelNumber].pDN = nodeD;
                                if(PSE_DIAG_MEDIUM) {
                                    bhmMessage("I", PREFIX "_CC", "Configure Send channel %d for '%s' (%d) to '%s' (%d)",
                                            channelNumber, processS, nodeS, processD, nodeD);
                                }
                            } else if (strncmp(channelDirection, "recv", 4) == 0) {
                                // add to configuration table
                                channelRx[channelNumber].pSP = strdup(processD);
                                channelRx[channelNumber].pSN = nodeD;
                                channelRx[channelNumber].pDP = strdup(processS);
                                channelRx[channelNumber].pDN = nodeS;
                                if(PSE_DIAG_MEDIUM) {
                                    bhmMessage("I", PREFIX "_CC", "Configure Receive channel %d for '%s' (%d) from '%s' (%d)",
                                            channelNumber, processS, nodeS, processD, nodeD);
                                }
                            } else {
                                bhmMessage("E", PREFIX "_DCF", "Direction field '%s' not recognised in '%s'", channelDirection, line);
                            }
                        }
                    }
                }
            }
            // search lines for ones for this node (number of should use 0_0 0_1 etc?)
            // configure channels
            // tx: include p0_to_p12 information in packet channel_info
            // rx: read channel_info, lookup to select channel for message
            if(PSE_DIAG_HIGH) {
                Uns32 channelNumber = 0;
                while (channelRx[channelNumber].pDP) {
                    Uns32 offset = (channelNumber * sizeMBox) + HOSTIF_INBOX_BUF_OFFSET;
                    bhmMessage("I", PREFIX "_RX_CFG", "Node %d: "
                               "Buffer Offset 0x%08x "
                               "Source Process %s Node %d "
                               "Destination Process %s Node %d"
                                ,thisNodeId
                                ,offset
                                ,channelRx[channelNumber].pSP     // pointer to info string
                                ,channelRx[channelNumber].pSN     // the source node
                                ,channelRx[channelNumber].pDP     // pointer to info string
                                ,channelRx[channelNumber].pDN      // the destination node
                    );
                    channelNumber++;
                }
            }

        }
    }

    char endianString[8];
    // check for an endian attribute
    Bool setEndian = bhmStringParamValue("endian", endianString, sizeof(endianString));
    if(setEndian && !strcmp(endianString, "big")){
        byteSwap = True;
    }
    if(PSE_DIAG_MEDIUM) {
        bhmMessage("I", PREFIX, "Interface Endian %s", byteSwap ? "BIG" : "LITTLE");
    }

    Bool genSync;
    if(bhmBoolParamValue("generateSync", &genSync)) {
        // create timer thread
        thread = bhmCreateThread(syncThread, 0, "syncThread", 0);
    }
}

PPM_DESTRUCTOR_CB(destructor) {
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}
