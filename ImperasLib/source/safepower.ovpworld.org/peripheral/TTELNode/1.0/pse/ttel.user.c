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
#include <stdlib.h>

#include "pse.igen.h"

#define PREFIX "TTELNODE"

// the configuration Id for this node (cluster|tile|node)
Uns32 thisNodeId = 0;

// Port types
typedef enum {
    TT,
    RC1,
    RC2,
    BE
} portTypeE;

// Port Semantics
typedef enum {
    STATE,
    EVENT
} portSemanticE;

#define TRANSMIT_PORT 0
#define RECEIVE_PORT  1

// configuration parameter names
#define CONFIGFILE_PARAM "configfile"
#define SCHEDINT_PARAM   "scheduledperiod"
#define SCHEDFILE_PARAM  "coreintconfigfile"

// store the delays from configuration file
#define SCHED_LINE_ITEMS 2
#define MAX_SCHED_TIMES  4

static Uns32 coreIntPeriod;
static Uns32 coreIntDelays[MAX_SCHED_TIMES];

#define MAX_QUEUE 32

typedef struct fifoBufferS {
    Uns32  rdp, wrp;          // pointers to read and write points
    Uns32  size;              // size of the fifo
    Uns32 *buffer;            // fifo buffer
    Bool   full, empty;       // flags when full or empty
    Bool   valid;             // flag when containing valid message
} fifoBufferT, *fifoBufferP;

typedef struct portS {
    Uns32           direction;          // input or output
    Uns32           bufferSize;         // size of one buffer
    Uns32           queueLength;        // number of buffers in port
    portTypeE       type;
    portSemanticE   semantic;
    Uns32           node;               // the source node when input, destination when output
    Uns32           number;             // the destination (output) or source (input) port number
    Uns32           enabled;            // port is enabled
    Uns32           mint;               // periodic send time (uS)
    fifoBufferT     fifo[MAX_QUEUE];    // fifo pointers (max queue)
    Uns32           inFifo;             // the current input FIFO (read by host)
    Uns32           outFifo;            // the current output FIFO (send to NoC)
    Bool            full;               // the port is full (all FIFOs contain messages)
    Bool            empty;              // the port is empty (no FIFOs contain messages)
} portT, *portP;

// The ports
// reconfiguration, data and error ports local
// accessed using callbacks
//    #0 is reconfiguration port
//    #1 to #253 are data ports
//    #254 is Error FIFO
// monitor port uses slave port memory directly to allow memory reads without callbacks
//    #255 is MON registers (status)
#define MAX_DATA_PORTS 254
#define ERROR_PORTS      1

static portT port[MAX_DATA_PORTS+ERROR_PORTS];

////////////////////////////////////////////////////////////////////////////////
// FIFO OPERATIONS //
////////////////////////////////////////////////////////////////////////////////

//
// Reset the indicated fifo buffer
//
static void resetFifo(fifoBufferP fifo) {
    fifo->rdp   = 0;
    fifo->wrp   = 0;
    fifo->full  = False;
    fifo->empty = True;
    fifo->valid = False;
}

//
// Push element onto fifo buffer and update full and empty flags
// Return False if unable to complete because fifo is full
//
static Bool pushFifo (fifoBufferP fifo, Uns32 value) {
    if (fifo->full) {
        return False;
    } else {
        fifo->buffer[fifo->wrp] = value;
        fifo->wrp = (fifo->wrp + 1) % fifo->size;

        // Test for buffer now being full
        fifo->full  = (fifo->rdp == fifo->wrp);
        fifo->empty = False;

        return True;
    }
}

//
// View element on top of fifo buffer
// Return False if unable to complete because fifo is empty
//
static Bool viewFifo (fifoBufferP fifo, Uns32 *value) {
    if (fifo->empty) {
        return False;
    } else {
        *value = fifo->buffer[fifo->rdp];
        return True;
    }
}

//
// Pop element from fifo buffer and update full and empty flags
// Return False if unable to complete because fifo is empty
//
static Bool popFifo (fifoBufferP fifo, Uns32 *value) {

    if (!viewFifo(fifo, value)) {

        return False;

    } else {

        fifo->rdp = (fifo->rdp + 1) % fifo->size;

        // Test for buffer now being empty
        fifo->empty = (fifo->rdp == fifo->wrp);
        fifo->full  = False;

        return True;
    }
}

//
// Return number of entries in the fifo
//
static Uns32 getFifoCount(fifoBufferP fifo) {

    Uns32 size = fifo->size;

    if (fifo->full) {
        return size;
    } else if (fifo->empty) {
        return 0;
    } else if (fifo->wrp < fifo->rdp) {
        return (size - fifo->rdp + fifo->wrp);
    } else {
        return(fifo->wrp - fifo->rdp);
    }
}


////////////////////////////////////////////////////////////////////////////////
// Port Status operations
////////////////////////////////////////////////////////////////////////////////

// Port Status Word
typedef struct portStatusS {
    union {
        Uns32 value;
        struct {
            Uns32  length     :10;  // message length (words)
            Uns32  messages   :8;   // number of messages
            Uns32  bufferEmpty:1;   // buffer empty
            Uns32  bufferFull :1;   // 19: buffer full
            Uns32  portEmpty  :1;   // 20 port empty
            Uns32  portFull   :1;   // 21 port full
            Uns32  res        :10;  // 31:22 reserved
        } bits;
    };
} portStatusT, *portStatusP;

#define GET_WORD(_port)  (_port/32)
#define GET_BIT(_port)   (_port%32)
#define SET_BIT(_port)   (1<<(GET_BIT(_port)))
#define CLR_BIT(_port)  ~(SET_BIT(_port))

#define EMPTY(_port)   ((Uns32*)(handles.hostif + \
                                 HOSTIF_MON_EMPTY_OFFSET + \
                                 (GET_WORD(_port)*sizeof(Uns32))))

#define FULL(_port)   ((Uns32*)(handles.hostif + \
                                HOSTIF_MON_FULL_OFFSET + \
                                (GET_WORD(_port)*sizeof(Uns32))))

#define STATUS(_port) ((Uns32*)(handles.hostif + \
                                HOSTIF_MON_STATUS_OFFSET + \
                                (_port*sizeof(Uns32))))

void setPortEmpty(Uns32 pNum) {
    // write port bit
    Uns32 empty  = *EMPTY(pNum);
    empty       |= SET_BIT(pNum);
    *EMPTY(pNum) = empty;
    if(PSE_DIAG_HIGH) bhmMessage("I", PREFIX "_SPE", "set empty: port %d (0x%x)", pNum, empty);
}

void clrPortEmpty(Uns32 pNum) {
    // write port bit
    Uns32 empty  = *EMPTY(pNum);
    empty       &= CLR_BIT(pNum);
    *EMPTY(pNum) = empty;
    if(PSE_DIAG_HIGH) bhmMessage("I", PREFIX "_CPE", "clr empty: port %d (0x%x)", pNum, empty);
}

void setPortFull(Uns32 pNum) {
    // write port bit
    Uns32 full  = *FULL(pNum);
    full       |= SET_BIT(pNum);
    *FULL(pNum) = (Uns32)full;
    if(PSE_DIAG_HIGH) bhmMessage("I", PREFIX "_SPF", "set full: port %d (0x%x)", pNum, full);
}

void clrPortFull(Uns32 pNum) {
    // write port bit
    Uns32 full  = *FULL(pNum);
    full       &= CLR_BIT(pNum);
    *FULL(pNum) = full;
    if(PSE_DIAG_HIGH) bhmMessage("I", PREFIX "_CPF", "clr full: port %d (0x%x)", pNum, full);
}

//
// Update the status fields associated with the port and fifos as seen by the Host Interface
//
void updatePortStatus(Uns32 pNum) {

    // write status word bit
    portStatusT status;
    status.value = *STATUS(pNum);

    // default
    status.bits.portFull  = 0;
    status.bits.portEmpty = 0;

    // number of words in current FIFO
    Uns32 fifoNum = 0;     // current 'visible' fifo to interface

    if (port[pNum].direction == RECEIVE_PORT) {
        fifoNum = port[pNum].outFifo;
    } else {
        fifoNum = port[pNum].inFifo;
    }

    status.bits.length = getFifoCount(&port[pNum].fifo[fifoNum]);

    // update the number of queued messages
    if (port[pNum].inFifo > port[pNum].outFifo) {
        // messages
        status.bits.messages = port[pNum].inFifo - port[pNum].outFifo;
        clrPortFull(pNum);
        clrPortEmpty(pNum);

    } else if (port[pNum].inFifo < port[pNum].outFifo) {
        // messages
        status.bits.messages = (port[pNum].queueLength - 1) - (port[pNum].outFifo - port[pNum].inFifo);
        clrPortFull(pNum);
        clrPortEmpty(pNum);

        // if pointer the same and fifo contains data
    } else if ((port[pNum].inFifo == port[pNum].outFifo) && (port[pNum].fifo[fifoNum].valid)) {
            // port full
            status.bits.messages = port[pNum].queueLength;
            status.bits.portFull = 1;
            setPortFull(pNum);

    } else {
        // empty
        status.bits.portEmpty = 1;
        status.bits.messages  = 0;
        setPortEmpty(pNum);
    }

    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX "_US", "update status : "
                                "port %d '%s' contains %d messages, "
                                "current fifo %d valid %d length %d inFifo %d outFifo %d",
                pNum,
                (status.bits.portEmpty && status.bits.portFull) ? "error: full/empty both set" :
                                          status.bits.portEmpty ? "empty" :
                                          status.bits.portFull  ? "full" : "messages",
                status.bits.messages, fifoNum, port[pNum].fifo[fifoNum].valid,
                status.bits.length,
                port[pNum].inFifo, port[pNum].outFifo);

    *STATUS(pNum) = status.value;

    // TODO: Check interrupt signal requirements (edge, level etc)
    ppmWriteNet(handles.pIntToCore, 1);
    ppmWriteNet(handles.pIntToCore, 0);
}

void updatePortInPointer(Uns32 pNum) {
    port[pNum].inFifo++;
    if(port[pNum].inFifo >= port[pNum].queueLength)
        port[pNum].inFifo = 0;
}

void updatePortOutPointer(Uns32 pNum) {
    port[pNum].outFifo++;
    if(port[pNum].outFifo >= port[pNum].queueLength)
        port[pNum].outFifo = 0;
}

////////////////////////////////////////////////////////////////////////////////
// Error Generation
////////////////////////////////////////////////////////////////////////////////
#define ERR_RESERVED        0
#define ERR_CRASH_READ      1
#define ERR_CRASH_WRITE     2
#define ERR_PORT_EMPTY      3
#define ERR_PORT_OVERFLOW   4
#define ERR_BUFFER_EMPTY    5
#define ERR_BUFFER_OVERFLOW 6
#define ERR_CONFIGURATION   7

// port 254 is the error port
#define ERROR_PORT 254

void reportError(Uns32 pNum, Uns32 error) {
    Uns32 current = port[ERROR_PORT].inFifo;
    Uns32 errWord = (error << 8) | pNum;

    pushFifo(&port[ERROR_PORT].fifo[current], errWord);

    // indicate message in buffer
    port[ERROR_PORT].fifo[current].valid = True;

    if(PSE_DIAG_LOW)
        bhmMessage("I", PREFIX "_RE", "Report Error %d for port %d (Port %d FIFO %d)",
                error, pNum, ERROR_PORT, port[ERROR_PORT].inFifo);


    updatePortInPointer(ERROR_PORT);        // increment the inFiFo pointer

    updatePortStatus(ERROR_PORT);
}

////////////////////////////////////////////////////////////////////////////////
// Port Re-Configuration operations
////////////////////////////////////////////////////////////////////////////////

// port 0 is the re-configuration port
#define RECONFIG_PORT 0

#define CONFIG_MINT_CHANGE  1
#define DESTINATION_CHANGE  2
#define PORT_ENABLE_CHANGE  4

void reconfigurePort() {
    Uns32 fifo     = port[RECONFIG_PORT].outFifo;
    Uns32 length   = getFifoCount(&port[RECONFIG_PORT].fifo[fifo]);

    Uns32 data = 0;
    Uns64 value;
    popFifo(&port[RECONFIG_PORT].fifo[fifo], &data);    // get low value
    value = data;
    popFifo(&port[RECONFIG_PORT].fifo[fifo], &data);    // get high value
    value = value | ((Uns64)data<< 32);
    popFifo(&port[RECONFIG_PORT].fifo[fifo], &data);    // get command and port
    Uns32 command  = (data       ) & 0xff;
    Uns32 pNum     = (data >>  8 ) & 0xff;
    popFifo(&port[RECONFIG_PORT].fifo[fifo], &data);    // get reserved and pre-amble
    Uns32 preamble = (data >> 24 ) & 0xff;

    if(PSE_DIAG_LOW)
        bhmMessage("I", PREFIX "_RC", "Port Reconfiguration Message "
                                "Command %d Port %d length %d preamble 0x%x Value 0x%llx",
                                    command, pNum, length, preamble, value);

    switch (command) {
        case CONFIG_MINT_CHANGE:
        {
            if(PSE_DIAG_LOW)
                bhmMessage("W", PREFIX "_RCM", "MINT Change - Not Supported");
            break;
        }
        case DESTINATION_CHANGE:
        {
            Uns32 newNode = (value >> 8) & 0x00ffffff;
            Uns32 newPort =  value       & 0x000000ff;
            if(PSE_DIAG_LOW)
                bhmMessage("I", PREFIX "_RCD", "Destination, port %d %d/%d -> %d/%d",
                                        pNum,
                                        port[pNum].node, port[pNum].number,
                                        newNode, newPort);
            port[pNum].node   = newNode;
            port[pNum].number = newPort;
            break;
        }
        case PORT_ENABLE_CHANGE:
        {
            Uns32 newEnable = value & 0x000000ff;
            if(PSE_DIAG_LOW)
                bhmMessage("I", PREFIX "_RCE", "Port Activation, port %d, %s -> %s",
                                        pNum,
                                        port[pNum].enabled ? "enabled" : "disabled",
                                        newEnable ? "enabled" : "disabled");
            port[pNum].enabled = newEnable;
            break;
        }
        default:
        {
            if(PSE_DIAG_LOW)
                bhmMessage("I", PREFIX "_RCF", "Error - Unknown Command %d", command);
            reportError(RECONFIG_PORT, ERR_CONFIGURATION);
            break;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// Network Transmit and Receive
////////////////////////////////////////////////////////////////////////////////

typedef struct networkDataS {
    Uns32 toId;
    Uns32 toPort;
    Uns32 fromId;
    Uns32 fromPort;
    Uns32 length;
    Uns32 data[256/4];
} networkDataT, *networkDataP;

networkDataT networkTx;
networkDataP networkRxP;

void networkTransmitMsg(Uns32 pNum, Uns32 fifo) {
    networkTx.toId     = port[pNum].node;
    networkTx.toPort   = port[pNum].number;
    networkTx.fromId   = thisNodeId;
    networkTx.fromPort = pNum;
    networkTx.length   = getFifoCount(&port[pNum].fifo[fifo]);
    Uns32 i;
    for (i=0; i< networkTx.length;i++) {
        networkTx.data[i] = port[pNum].fifo[fifo].buffer[i];
    }

    if(PSE_DIAG_LOW)
        bhmMessage("I", PREFIX "_NTX", "Network Tx Message Node %d Port %d Length %d",
                networkTx.toId, networkTx.toPort, networkTx.length);

    ppmPacketnetWrite(handles.network, &networkTx, sizeof(networkTx));

    // we send messages immediately so this is only required so that the
    // input is aware if the port is full
    // move to the next buffer
    port[pNum].fifo[fifo].valid = False;
    resetFifo(&port[pNum].fifo[fifo]);  // reset FIFO pointers

    updatePortOutPointer(pNum);        // increment the inFiFo pointer
}

PPM_PACKETNET_CB(networkReceiveMsg) {
    // receive packet if for this node and update status register
    networkRxP = data;

    if(networkRxP->toId == thisNodeId) {

        if(PSE_DIAG_MEDIUM)
            bhmMessage("I", PREFIX "_NRX",
                    "Network Rx Message Destination Node %d(0x%x) "
                    "Port %d Length %d : Source Node %d(0x%x) Port %d",
                    networkRxP->toId, networkRxP->toId,
                    networkRxP->toPort, networkRxP->length,
                    networkRxP->fromId, networkRxP->fromId,
                    networkRxP->fromPort);

        Uns32 pNum    = networkRxP->toPort;
        if (port[pNum].direction != RECEIVE_PORT) {
            if(PSE_DIAG_LOW)
                bhmMessage("W", PREFIX "_RXF",
                        "Message received for port %d which is not configured for receive", pNum);

        } else {

            Uns32 current = port[pNum].inFifo;

            Uns32 i, length;
            if (networkRxP->length > port[pNum].bufferSize) {
                // message too big for buffer - set status bufferFull
                length = port[pNum].bufferSize;
                if(PSE_DIAG_LOW)
                    bhmMessage("W", PREFIX "_RXO",
                            "Buffer overflow port %d buffer size %d message length %d",
                            pNum, port[pNum].bufferSize, networkRxP->length);
                portStatusT status;
                status.value = *STATUS(pNum);
                status.bits.bufferFull = 1;
                *STATUS(pNum) = status.value;

            } else {
                length = networkRxP->length;
            }

            if (port[pNum].fifo[current].valid) {
                if(PSE_DIAG_LOW)
                    bhmMessage("W", PREFIX "_RXO",
                            "Port overflow port %d", pNum);
                portStatusT status;
                status.value = *STATUS(pNum);
                status.bits.portFull = 1;
                *STATUS(pNum) = status.value;
            } else {

                for (i=0; i< length;i++) {
                    pushFifo(&port[pNum].fifo[current], networkRxP->data[i]);
                }
                // indicate message in buffer
                port[pNum].fifo[current].valid = True;

                if(PSE_DIAG_LOW)
                    bhmMessage("I", PREFIX "_RX",
                            "Received Network Rx Message in Port %d Fifo %d Length %d",
                                    pNum, port[pNum].inFifo, length);


                updatePortInPointer(pNum);        // increment the inFiFo pointer

                updatePortStatus(pNum);
            }
        }
    } else {
        if(PSE_DIAG_MEDIUM)
            bhmMessage("I", PREFIX "_RXI", "Ignored Network Rx Message "
                            "Destination Node %d(0x%x) Port %d Length %d : "
                            "Source Node %d(0x%x) Port %d",
                    networkRxP->toId, networkRxP->toId,
                    networkRxP->toPort, networkRxP->length,
                    networkRxP->fromId, networkRxP->fromId,
                    networkRxP->fromPort);
    }
}

////////////////////////////////////////////////////////////////////////////////
// Callback stubs
////////////////////////////////////////////////////////////////////////////////

PPM_READ_CB(readGlobalTime) {
    Uns32 word = PTR_TO_UNS32(user);
    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX "_RGT", "%s: %s", __FUNCTION__, word ? "high" : "low");
    return 0;
}

PPM_NBYTE_READ_CB(readPortLength) {

    Uns32 pNum     = PTR_TO_UNS32(userData+1);
    Uns32 count    = 0;
    Uns32 nextFifo = 0;

    if(port[pNum].direction == TRANSMIT_PORT) {
        if(PSE_DIAG_LOW)
            bhmMessage("W", PREFIX "_RPLT",
                    "%s: port %d reading length from transmit port", __FUNCTION__, pNum);
        // TODO: Is this an error??
        *(Uns32*)data = 0;
        return;
    } else {
        // when input we want the count for the next fifo to read
        nextFifo = port[pNum].outFifo;
        count    = getFifoCount(&port[pNum].fifo[nextFifo]);
    }
    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX "_RPL",
                "%s: port %d fifo %d count %d", __FUNCTION__, pNum, nextFifo, count);

    *(Uns32*)data = count;
}

// The port is a FIFO?
// need a structure for head/tail pointers for each buffer?
// needs to record for each message in a buffer, the start location and length?
PPM_NBYTE_READ_CB(readData) {
    Uns32 pNum = PTR_TO_UNS32(userData+1);

    // read from the current buffer
    Uns32 next = port[pNum].outFifo;

    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX "_RD", "%s: port %d, FIFO %d", __FUNCTION__, pNum, next);

    if (port[pNum].direction != RECEIVE_PORT) {
        if(PSE_DIAG_LOW)
            bhmMessage("W", PREFIX "_RDFD",
                    "%s: port %d : Attempting to read from an output port", __FUNCTION__, pNum);
        *(Uns32*)data = 0;
        return;
    } else if (port[pNum].enabled == 0 ) {
        if(PSE_DIAG_LOW)
            bhmMessage("W", PREFIX "_RDD",
                    "%s: port %d : Attempting to read disabled port", __FUNCTION__, pNum);
        *(Uns32*)data = 0;
        return ;
    } else if (getFifoCount(&port[pNum].fifo[next]) == 0) {
        if(PSE_DIAG_LOW)
            bhmMessage("W", PREFIX "_REF",
                    "%s: port %d : Reading empty FIFO", __FUNCTION__, pNum);
        *(Uns32*)data = 0;
        return;
    }

    Uns32 tmpData;
    Bool rtn = popFifo(&port[pNum].fifo[next], &tmpData);

    // Data in FIFO and word has been read
    if(rtn) {
        // check to see if FIFO now empty
        if(getFifoCount(&port[pNum].fifo[next]) == 0) {
            port[pNum].fifo[next].valid = False;
            resetFifo(&port[pNum].fifo[next]);  // reset FIFO pointers

            // no more data, move to next FIFO
            updatePortOutPointer(pNum);         // increment the inFiFo pointer
        }
        updatePortStatus(pNum);

        *(Uns32*)data = tmpData;
        return;
    }

    if(PSE_DIAG_LOW)
        bhmMessage("W", PREFIX "_RDF", "%s: port %d : Failed to read data", __FUNCTION__, pNum);
    *(Uns32*)data = 0;
}

PPM_NBYTE_WRITE_CB(writeData) {
    Uns32 pNum = PTR_TO_UNS32(userData+1);
    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX "_WTXD",
                "%s: port %d : 0x%08x", __FUNCTION__, pNum, *(Uns32*)data);

    if (port[pNum].direction != TRANSMIT_PORT) {
        if(PSE_DIAG_LOW)
            bhmMessage("W", PREFIX "_WIP",
                    "%s: port %d : Attempting to write to an input port", __FUNCTION__, pNum);
    } else if (port[pNum].enabled == 0 ) {
        if(PSE_DIAG_LOW)
            bhmMessage("W", PREFIX "_WDP",
                    "%s: port %d : Attempting to write a disabled port", __FUNCTION__, pNum);
    } else {
        // write to the current buffer
        Uns32 current = port[pNum].inFifo;
        if (!pushFifo(&port[pNum].fifo[current], *(Uns32*)data)) {
            if(PSE_DIAG_LOW)
                bhmMessage("W", PREFIX "_WFF", "%s: port %d : Write to Full FIFO, data lost", __FUNCTION__, pNum);
            // TODO: Should this set error flags?
        }
    }
}

PPM_NBYTE_WRITE_CB(writePortTerminate) {
    Uns32 pNum = PTR_TO_UNS32(userData+1);
    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX "_TXC", "%s: port %d", __FUNCTION__, pNum);

    // indicate valid message received
    Uns32 txFifo = port[pNum].inFifo;
    port[pNum].fifo[txFifo].valid = True;

    if(pNum == RECONFIG_PORT) {
        reconfigurePort();
    } else {
        // TODO:
        // Messages are sent on a Time Schedule
        // The time schedule aspects need to be implemented

        // send message to NoC
        networkTransmitMsg(pNum, txFifo);
    }

    // move to the next buffer
    updatePortInPointer(pNum);        // increment the inFiFo pointer

    // update status
    updatePortStatus(pNum);
}

// /////////////////////////////////////////////////////////////////////////////
// Periodic interrupt generation threads
//


bhmThreadHandle periodInterruptHandle;            // timer thread handle
Uns32           intSchedulePeriod;

// the width in uS for the interrupt signal
#define PULSEWIDTH 5

void periodInterruptThread(void *user) {

    if (PSE_DIAG_LOW)
            bhmMessage("I", PREFIX,
                            "Period Timer enabled (period %duS)",
                            intSchedulePeriod);
    double delay = intSchedulePeriod;

    // This always executes
    while(1){

        bhmWaitDelay(delay);

        if (PSE_DIAG_HIGH) bhmMessage("I", PREFIX, "Period Timer at %10.3f uS",
                                                   bhmGetCurrentTime());

        // TODO: Check interrupt signal requirements (edge, level etc)
        ppmWriteNet(handles.PeriodInterrupt, 1);
        bhmWaitDelay(PULSEWIDTH);    // ensure this can be observed by a model
        ppmWriteNet(handles.PeriodInterrupt, 0);
        // correct the actual delay period according to pulse width
        delay = intSchedulePeriod - PULSEWIDTH;

    };
}

bhmThreadHandle coreInterruptHandle;            // timer thread handle

void coreInterruptThread(void *user) {

    if (PSE_DIAG_LOW)
            bhmMessage("I", PREFIX,
                            "Core Interrupt Timer enabled");

    // This always executes
    Uns32 number  = 0;                 // index into delay table
    Bool  initial = True;              // indicate initial delay
    Uns32 delay   = coreIntDelays[0];  // initial delay
    while(1){

        if(delay == 0) {
            bhmMessage("W", PREFIX,
                    "No valid Core Interrupt Delay (%d) - aborting", number);
            break;
        } else if (PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX,
                    "Next (%d) Core Interrupt at %d uS, delay %d uS",
                    number,
                    coreIntDelays[number],
                    initial ? delay : delay+PULSEWIDTH);
        }

        bhmWaitDelay(delay);
        initial = False;

        if (PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX,
                    "Core Interrupt at %10.3f uS",
                     bhmGetCurrentTime());

        // TODO: Check interrupt signal requirements (edge, level etc)
        ppmWriteNet(handles.CoreInterrupt, 1);
		bhmWaitDelay(PULSEWIDTH);    // ensure this can be observed by a model
        ppmWriteNet(handles.CoreInterrupt, 0);

        if((number >= MAX_SCHED_TIMES) || (coreIntDelays[number+1] == 0)) {
            // delay to end of period plus next delay
            delay = coreIntPeriod - coreIntDelays[number] + coreIntDelays[0] - PULSEWIDTH;
            number=0;
        } else {
            delay = coreIntDelays[number+1] - coreIntDelays[number] - PULSEWIDTH;
            number++;
        }
    };
}

// /////////////////////////////////////////////////////////////////////////////
// Loading configuration files
//

#define MAXLINE    4096
#define MAXSTRING   128

// number of items on a configuration file line
// format of a line is '<enable> <TDS=Type/Direction/Semantic> <Buffer Size> <Queue Length> <destination> <MINT>'
#define CONFIG_LINE_ITEMS 6

// configure the ports specified in the config file and return
Uns32 getConfigFile(const char *configFile) {
    FILE *configFileFP = NULL;

    // port #0 reconfiguration
    // port #1 to #253 for messages
    // port #254 error messages
    // port #255 status
    Uns32 number = 0;

    // TODO: channel info
    // open config file
    if(!(configFileFP = fopen(configFile, "r"))) {
        if(PSE_DIAG_MEDIUM)
            bhmMessage("E", PREFIX "_NCF", "Could not open config file '%s', "
                                       "specify using '%s' parameter",
                                       configFile, CONFIGFILE_PARAM);
        return 0;
    } else {

        // Read configuration information
        char line[MAXLINE];
        while (fgets(line, MAXLINE, configFileFP) != NULL){
            if (line[0] == '#') {
                // Ignore comment line
            } else {
                Uns32 items, enable, bufferSize, queueLength, mint, TDS_tmp, dest_tmp;
                // line contains
                // format of a line is '<enable> <TDS=Type/Direction/Semantic> <Buffer Size> <Queue Length> <destination> <MINT>'
                if ((items = sscanf(line, "%x %x %x %x %x %x",
                           &enable, &TDS_tmp,
                           &bufferSize, &queueLength,
                           &dest_tmp, &mint)) != CONFIG_LINE_ITEMS) {
                    if(PSE_DIAG_LOW)
                        bhmMessage("W", PREFIX "_FCF", "Ingored line: Expected %d items, "
                                                   "found %d in '%s'",
                                                   CONFIG_LINE_ITEMS, items, line);
                } else {
                    // add to port configuration
                    port[number].node        = (dest_tmp >> 8) & 0x00ffffff;
                    port[number].number      =  dest_tmp       & 0x000000ff;
                    port[number].type        = (TDS_tmp >> 2) & 0x0f;
                    port[number].direction   = (TDS_tmp >> 1) & 0x01;
                    port[number].semantic    =  TDS_tmp       & 0x01;
                    port[number].bufferSize  = bufferSize;
                    port[number].enabled     = enable;
                    port[number].inFifo      = 0;
                    port[number].outFifo     = 0;
                    port[number].mint        = mint;

                    if (queueLength > MAX_QUEUE) {
                        if(PSE_DIAG_LOW)
                            bhmMessage("W", PREFIX "_MQ",
                                       "port %2d Queue request %d not available set to max %d",
                                       number, queueLength, MAX_QUEUE);

                        port[number].queueLength = MAX_QUEUE;
                    } else {
                        port[number].queueLength = queueLength;
                    }

                    if(PSE_DIAG_MEDIUM)
                        bhmMessage("I", PREFIX "_PC",
                                "port %2d en %d destination node 0x%06x (%03d/%03d/%03d) port %3d "
                                "type %2d dir %d sem %d buff Sz %3d Queue %3d",
                            number,
                            port[number].enabled, port[number].node,
                           (port[number].node >> 16) & 0xff,
                           (port[number].node >>  8) & 0xff,
                            port[number].node        & 0xff,
                            port[number].number, port[number].type,
                            port[number].direction, port[number].semantic,
                            port[number].bufferSize, port[number].queueLength);

                    // update all fifos in port
                    Uns32 i;
                    for (i=0;i< port[number].queueLength;i++) {
                        port[number].fifo[i].buffer = malloc(port[number].bufferSize*(sizeof(Uns32)));
                        port[number].fifo[i].size   = port[number].bufferSize;

                        if(PSE_DIAG_HIGH)
                            bhmMessage("I", PREFIX "_PCF",
                                    "malloc %d port %d fifo %d (0x%x)",
                                    port[number].bufferSize, number, i,
                                    PTR_TO_UNS32(port[number].fifo[i].buffer));

                        resetFifo(&port[number].fifo[i]);
                    }
                    // update the port status
                    updatePortStatus(number);

                    // TODO: If port type is STATE the messages are sent at the rate, set by MINT
                    //       Start periodic thread at specified rate

                    number++;
                }
            }
        }
        return number;
    }
}

/// configure the ports specified in the config file and return
Uns32 getScheduleFile(const char *scheduleFile) {
    FILE *scheduleFileFP = NULL;

    Uns32 number = 0;

    // open config file
    if(!(scheduleFileFP = fopen(scheduleFile, "r"))) {
        if(PSE_DIAG_MEDIUM)
            bhmMessage("E", PREFIX "_SCF", "Could not open config file '%s', "
                                       "specify using 'schedulefile' parameter",
                                       scheduleFile);
        return 0;
    } else {

        // Read configuration information
        char line[MAXLINE];
        while (fgets(line, MAXLINE, scheduleFileFP) != NULL){
            if(number > MAX_SCHED_TIMES) {
                bhmMessage("W", PREFIX "_FCO",
                                "Maximum periodic delays available %d reached",
                                MAX_SCHED_TIMES);
                break;
            }
            if (line[0] == '#') {
                // Ignore comment line
            } else {
                Uns32 items, value;
                char type[8];

                // line contains
                // format of a line is '<type period|set> <value>'
                if ((items = sscanf(line, "%s %d", type, &value) != SCHED_LINE_ITEMS)) {
                    if(PSE_DIAG_LOW)
                        bhmMessage("W", PREFIX "_FCF", "Ingored line: Expected %d items, "
                                                   "found %d in '%s'",
                                                   SCHED_LINE_ITEMS, items, line);
                } else {

                    if(strcmp(type, "period") == 0) {
                        // set the repeat period
                        coreIntPeriod = value;

                        if(PSE_DIAG_MEDIUM)
                            bhmMessage("I", PREFIX "_SC", "Core Interrupt Set period to %d uS",
                                coreIntPeriod);

                    } else if(strcmp(type, "set") == 0) {
                        // TODO: Check validity
                        if(PSE_DIAG_MEDIUM)
                            bhmMessage("I", PREFIX "_SC", "Add Core Interrupt (%d) at %d uS",
                                number, value);

                        coreIntDelays[number] = value;

                        number++;
                    } else {
                        bhmMessage("W", PREFIX "_SCF",
                                "Did not recognise type '%s' expected 'period' or 'set'",
                                type);
                    }
                }
            }
        }
        return number;
    }
}



PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    // get Id for NoC node
    Uns32 cluster, tile, node;
    if (!bhmUns32ParamValue("cluster", &cluster) ||
        !bhmUns32ParamValue("tile", &tile) ||
        !bhmUns32ParamValue("node", &node)) {
        bhmMessage("E", PREFIX "_NIF",
                "Node Id has not been initialized in hardware design, please specify cluster, tile and node");
    } else {
        thisNodeId = (cluster << 16) | (tile << 8) | node;
        if(PSE_DIAG_LOW)
            bhmMessage("I", PREFIX "_NI", "Node Id 0x%06x (%d)", thisNodeId, thisNodeId);
    }

    // check network connected
    if (!handles.network) {
        bhmMessage("E", PREFIX "_PKTN", "Packetnet: Network connection not made");
    }

    // Read configuration information
    char configFile[MAXSTRING];
    Uns32 configuredPorts = 1;
    if(!bhmStringParamValue(CONFIGFILE_PARAM, configFile, sizeof(configFile))) {
        bhmMessage("E", PREFIX "_CFF",
                "Parameter '%s' must be specified to define network communication channels",
                CONFIGFILE_PARAM);
    } else {
        // configure all ports specified in the config file
        configuredPorts = getConfigFile(configFile);
    }

    // Configure all remaining ports as empty
    while (configuredPorts < MAX_DATA_PORTS) {
        port[configuredPorts].inFifo      = 0;
        port[configuredPorts].outFifo     = 0;
        port[configuredPorts].node        = 0;
        port[configuredPorts].number      = 0;
        port[configuredPorts].direction   = RECEIVE_PORT;
        port[configuredPorts].bufferSize  = 0;
        port[configuredPorts].queueLength = 0;
        port[configuredPorts].enabled     = 0;

        resetFifo(&port[configuredPorts].fifo[0]);

        // update the port status
        updatePortStatus(configuredPorts);

        configuredPorts++;
    }

    // read any scheduled interrupt information
    if(bhmUns32ParamValue(SCHEDINT_PARAM, &intSchedulePeriod)) {
        // if set start a scheduled interrupt at intSchedulePeriod uS rate
        if(PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX "_SINT", "Starting Period Interrupt Timer at %duS",
                                    intSchedulePeriod);
        periodInterruptHandle = bhmCreateThread(periodInterruptThread, 0,
                                                "Period Interrupt Timer",
                                                0);
    }

    // Read configuration information
    char scheduleFile[MAXSTRING];
    if(bhmStringParamValue(SCHEDFILE_PARAM, scheduleFile, sizeof(scheduleFile))) {
        if(!intSchedulePeriod) {
            bhmMessage("W", PREFIX "_SN",
                    "Cannot set CoreInterrupt Schedule without setting period with parameter '%s'",
                    SCHEDINT_PARAM);
        } else {
            // configure timing schedule specified in the config file
            getScheduleFile(scheduleFile);
            if(PSE_DIAG_HIGH)
                bhmMessage("I", PREFIX "_CINT", "Starting Core Interrupt Timer");
            coreInterruptHandle = bhmCreateThread(coreInterruptThread, 0,
                                                    "Core Interrupt Timer",
                                                    0);
        }
    }


}

PPM_DESTRUCTOR_CB(destructor) {
    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX "_DES", "Free ports");

    // iterate over all ports and fifo queues, freeing memory
    Uns32 fifoNum, portNum;
    for (portNum=0;portNum < MAX_DATA_PORTS ;portNum++) {
        for (fifoNum=0;fifoNum < port[portNum].queueLength;fifoNum++) {
            if (port[portNum].fifo[fifoNum].buffer) {
                if(PSE_DIAG_HIGH)
                    bhmMessage("I", PREFIX, "free port %d fifo %d (0x%x)",
                            portNum, fifoNum, PTR_TO_UNS32(port[portNum].fifo[fifoNum].buffer));
                free(port[portNum].fifo[fifoNum].buffer);
            }
        }
    }
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}

