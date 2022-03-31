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
//                          Fri Feb  6 13:14:14 2015
//
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>

#include "pse.igen.h"

#include "exchangeData.h"

#ifndef PREFIX
#  define PREFIX "SOCKET_INTERFACE"
#endif

typedef struct socketInterfaceS {

    Int32          channel;         // duplex socket channel connection

    bhmEventHandle readyToReceive;    // input DMA is enabled and can start accepting messages
    bhmEventHandle messageReceived;   // input message is available in buffer
    bhmEventHandle messageToSend;     // output message is available in memmory
    bhmEventHandle synch;
} socketInterface;

#define STEPTIME 1000

//
// Statics
//
static socketInterface device;

static tExchangeDataStruct Outgoing;
static tExchangeDataStruct Incoming;
static tExchangeDataStruct *OutgoingP = &Outgoing;
static tExchangeDataStruct *IncomingP = &Incoming;


static Uns32 readInput(Uns8 *buffer, Uns32 length) {
    Uns32 bytes       = 0;
    Uns32 transferred = 0;

    if (device.channel >= 0) {
        do {
            Uns32 remaining = length - transferred;
            bytes = bhmSerReadN(device.channel, buffer, remaining);
            transferred += bytes;

            if(bytes == length) // transferred all bytes in one read
                break;

            bhmWaitDelay(QUANTUM_DELAY); // allow simulator to re-schedule

            // keep polling if transfer starts until length transferred
        } while (transferred < length);

        if (PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX, "Received Input %d", transferred);
            bhmPrintf("Info (" PREFIX ") Message In : ");
            unsigned int i;
            for (i=0; i<transferred;i++) {
                bhmPrintf("0x%02x ", buffer[i]);
            }
            bhmPrintf("\n");
        }
    }
    return transferred;
}

static Uns32 writeOutput(Uns8 *buffer, Uns32 length)
{
    if (device.channel >= 0) {
        if (PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX, "Send Output %d", length);
            bhmPrintf("Info (" PREFIX ") Message Out : ");
            unsigned int i;
            for (i=0; i<length;i++) {
                bhmPrintf("0x%02x ", buffer[i]);
            }
            bhmPrintf("\n");
        }
        Uns32 bytes       = 0;
        Uns32 transferred = 0;
        do {
            Uns32 remaining = length - transferred;
            bytes = bhmSerWriteN(device.channel, buffer, remaining);
            transferred += bytes;

            if(bytes == length) // transferred all bytes in one write
                break;

            if(bytes == 0) {
                Uns32 error = bhmSerLastError(device.channel);
                if(error != 0) {
                    if (PSE_DIAG_LOW) {
                        bhmMessage("W", PREFIX, "Socket error code %d", error);
                    }
                }
            }

            bhmWaitDelay(QUANTUM_DELAY); // allow simulator to re-schedule

            // keep writing until length transferred
        } while (transferred < length);

        return bytes;
    } else {
        return 0;
    }
}

static void getSocketMessage(void *user)
{

    while(1) {

        if(!sp_abs_data.Control.bits.dmaInEn) {
            // wait until DMA setup and enabled
            bhmWaitEvent(device.readyToReceive);
        }

        // read message
        readInput((Uns8 *)(IncomingP), sizeof(tExchangeDataStruct));

        if (PSE_DIAG_MEDIUM)
            bhmMessage("I", PREFIX, "Message %d (%f uS): Simulation State '%s'",
                    IncomingP->num, (double)IncomingP->time,
                    IncomingP->endSimulation ? "end" : "running");

        // trigger update for message received
        bhmTriggerEvent(device.messageReceived);

        if (IncomingP->endSimulation) {

            // indicate no more messages
            sp_abs_data.Status.bits.end = 1 ;

            if (PSE_DIAG_HIGH)
                bhmMessage("I", PREFIX, "Send end of simulation achnowledgment");

            // send end of simulation acknowledgement
            OutgoingP->fd.length     = 0;                   // no data
            OutgoingP->time          = bhmGetLocalTime();   // time of end
            OutgoingP->endSimulation = 1;                   // terminate

            writeOutput((Uns8 *)(OutgoingP), sizeof(tExchangeDataStruct));

        }
    }
}

static void putSocketMessage(void *user)
{
    if(PSE_DIAG_LOW) bhmMessage("I", PREFIX, "Put Socket Messages Ready");

    while(1) {

        if(PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX, "Wait for message to send");

        // wait for message to send
        bhmWaitEvent(device.messageToSend);

        if (sp_abs_data.Control.bits.count) {
            Uns32 size = sp_abs_data.Control.bits.count*4;
            Uns32 src  = sp_abs_data.DMAAddressOut.value;
            if(PSE_DIAG_HIGH)
                bhmMessage("I", PREFIX, "Read Message (%d) from 0x%08x %d",
                                   IncomingP->fd.length, src, size);

            ppmReadAddressSpace (handles.mp,  src, size , OutgoingP->fd.data);
        }

        //Message to send
        OutgoingP->fd.length = sp_abs_data.Control.bits.count;
        OutgoingP->time      = bhmGetLocalTime();

        if(PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX, "Send Socket Header at %f (sim %d)",
                        (double)OutgoingP->time, OutgoingP->endSimulation);

        if(writeOutput((Uns8 *)(OutgoingP), sizeof(tExchangeDataStruct)) != sizeof(tExchangeDataStruct))
            break;

        // indicate message sent
        sp_abs_data.Control.bits.messageToSend = 0;
        sp_abs_data.Status.bits.messageSent    = 1;

        OutgoingP->num++;

        // maximum message send time
        bhmWaitDelay(STEPTIME);
    }
    if(PSE_DIAG_MEDIUM) bhmMessage("W", PREFIX, "Put Socket Messages - socket closed");
}

//
// Save message into DMA buffer
//
static void dataUpdate(void *user)
{
    while(1) {

        // wait for an input message
        bhmWaitEvent(device.messageReceived);

        if(PSE_DIAG_MEDIUM)
            bhmMessage("I", PREFIX, "UpdateMessage (%d) length %d @ %d uS",
                    IncomingP->num, IncomingP->fd.length, IncomingP->time);

        if (sp_abs_data.Status.bits.messageReceived) {
            // buffer still contains previous message
            if(PSE_DIAG_MEDIUM)
                bhmMessage("W", PREFIX, "Message (%d) Lost Overflow", IncomingP->num);

            sp_abs_data.Status.bits.messageOverflow = 1;

        } else {
            // read message
            if (IncomingP->fd.length) {
                if (sp_abs_data.Control.bits.dmaInEn) {
                    Uns32 size = IncomingP->fd.length * 4;
                    Uns32 dest = sp_abs_data.DMAAddressIn.value;

                    if(PSE_DIAG_HIGH)
                        bhmMessage("I", PREFIX, "Write Message (%d) to 0x%08x %d",
                                           IncomingP->fd.length, dest, size);

                    ppmWriteAddressSpace (handles.mp,  dest, size , IncomingP->fd.data);

                    if(PSE_DIAG_MEDIUM)
                        bhmMessage("I", PREFIX, "Message (%d) Received Length %d",
                                IncomingP->num, IncomingP->fd.length);

                    sp_abs_data.Status.bits.count           = IncomingP->fd.length;
                    sp_abs_data.Status.bits.messageReceived = 1;

                } else {
                    if(PSE_DIAG_MEDIUM)
                        bhmMessage("W", PREFIX, "Message (%d) Lost dma not enabled", IncomingP->num);

                    sp_abs_data.Status.bits.messageOverflow = 1;
                }
            }
        }
    }
}

/////////////////////////////// Default Access ////////////////////////////////

PPM_NBYTE_READ_CB(defaultMemRead) {
    bhmMessage("I", "PPM_DFRD",
        "Default Read   bytes:%u  Offset:0x%x",
        bytes,
        offset
    );
    memset(data, 0, bytes);
}

PPM_NBYTE_WRITE_CB(defaultMemWrite) {
    bhmMessage("I", "PPM_DFWR",
        "Default Write   bytes:%u  Offset:0x%x",
        bytes,
        offset
    );
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_READ_CB(rdStatus) {
    return *(Uns32*)user;
}
PPM_REG_WRITE_CB(wrStatus) {

    // clear bits set to '1'
    Uns32 current = *(Uns32*)user;
    Uns32 mask    = ~data;
    *(Uns32*)user = current & mask;
}

PPM_REG_WRITE_CB(wrControl) {
    *(Uns32*)user = data;

    if(sp_abs_data.Control.bits.dmaInEn) {
        // dma enabled start requesting messages
        bhmTriggerEvent(device.readyToReceive);
    }

    if(sp_abs_data.Control.bits.messageToSend && sp_abs_data.Control.bits.dmaOutEn) {
        // message ready to send
        bhmTriggerEvent(device.messageToSend);
    }
}


PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    device.channel = bhmSerOpenAuto();


    device.readyToReceive  = bhmCreateNamedEvent("readyToReceive",  "The DMA is enabled an dcan start accepting messages from socket interface");
    device.messageReceived = bhmCreateNamedEvent("messageReceived", "Received message is available in buffer");
    device.messageToSend   = bhmCreateNamedEvent("messageToSend",   "Message ready to be sent over interface");
    device.synch           = bhmCreateNamedEvent("synch",           "perform synchronisation");

    // Initialise initial state
    OutgoingP->time          = 0;
    OutgoingP->endSimulation = 0;
    OutgoingP->num           = 0;

    // wait for simulation to start
    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_START_OF_SIMULATION));

    // create the thread which causes messages to come in.
    bhmCreateThread(getSocketMessage, NULL, "getSocketMessage", 0);

    // create the thread which sends messages.
    bhmCreateThread(putSocketMessage, NULL, "putSocketMessage", 0);

    // create the thread to update messages into simulation.
    bhmCreateThread(dataUpdate, NULL, "dataUpdate", 0);

}

PPM_DESTRUCTOR_CB(destructor) {
    if(device.channel >= 0) {
        bhmSerClose(device.channel);
    }
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

