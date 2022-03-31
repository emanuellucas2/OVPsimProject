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
//                          Wed Jan 12 17:58:14 2011
//
////////////////////////////////////////////////////////////////////////////////

//
// This file was originally created by Imperas iGen, then modified
//
// Description:
// Implements a behavioral model of a data processing node intended to be daisy
// chained together. A data packet can be:
//    a) written by a processor into the txBuffer and then triggered
//       by writing to the control register
// or b) received from the previous node in the chain on the packetNet
//       port "pin"
// When a packet of data is received the model will:
//    a) perform processing, with a simulated delay
//    b) write the processed data to the next node if that node is ready to
//       receive data, otherwise set the status.watingtosend bit and
//       wait for either the next node to become available or for the
//       processor to clear the status.waitingtosend bit (The processor
//       may read the packet data from the RX buffer when status.waitingtosend
//       is active
//

#include <stdio.h>
#include <string.h>

#include "pse.igen.h"

#define BP ((Uns8 *)handles.bp)
#include "pse.macros.igen.h"

#define PREFIX "NODE"

#define BUFFER_SIZE 0x100

#if (BUFFER_SIZE < BP_MEM_TXBUFFER_BYTES) || (BUFFER_SIZE < BP_MEM_RXBUFFER_BYTES)
#error "Local buffer size too small"
#endif

static Uns8  localBuffer[BUFFER_SIZE];
static Uns32 dataLength;
static Bool  receiverReady = False;

// Data structure of the packetnet data
typedef struct netPacketS {
    Uns32 length;               // Length
    Uns8  data[BUFFER_SIZE];    // Payload
}  netPacket, *netPacketP;

// Event handles used to trigger waiting threads
static bhmEventHandle dataToProcess;
static bhmEventHandle dataRead;

// Send the packet out the packetnet port
static void sendPacketData(netPacket outPacket) {
    if(PSE_DIAG_HIGH) {
    	bhmMessage("I", PREFIX, "Sending data to output packetnet");
    }
    ppmPacketnetWrite(handles.pout, &outPacket, sizeof(outPacket));
}

//
// If receiver is ready then send data in localData buffer out the packetnet
// port. If receiver is not ready then set status.waitingtosend and wait for
// either a processor to clear that bit or for the receiver to become ready.
// If the receiver becomes ready then send the packet and clear the
// status.waitingtosend bit.
//
static void sendLocalData() {

	netPacket outPacket;

	// Copy data to RX buffer
	Uns32 i;
	for (i=0; i<dataLength; i++) {
		BP_MEM_RXBUFFER[i] = localBuffer[i];
		outPacket.data[i] = localBuffer[i];
	}
	outPacket.length = bp_regs_data.control.bits.length = dataLength;

	if (receiverReady) {

		// Receiver ready so send the packet now
		sendPacketData(outPacket);

	} else {

    	// Update status.waitingtosend
        bp_regs_data.status.bits.waitingtosend = 1;

        if(PSE_DIAG_HIGH) {
        	bhmMessage("I", PREFIX, "RX Data available for reading/sending");
        }

		bhmWaitEvent(dataRead);

		if (receiverReady) {
			// Packet can be sent now
			sendPacketData(outPacket);
		} else {
			// Data was read from RX Buffer
	        if(PSE_DIAG_HIGH) {
	        	bhmMessage("I", PREFIX, "RX Data read");
	        }
		}

		// data has been read so clear status.waitingtosend
        bp_regs_data.status.bits.waitingtosend = 0;

	}
}

// Sample processing function
static void processData() {
	Uns32 i;
	for (i = 0; i < dataLength; i++) {
		localBuffer[i] += 1;
	}
}


// Define stack for the dataProcessThread
static Uns8 dataProcessStack[1024*4];
#define STACK_TOP(_s) (&_s[sizeof(_s)])

//
// This runs in a PSE thread, processing and sending received data
//
static void dataProcessThread()
{
    if(PSE_DIAG_LOW) {
    	bhmMessage("I", PREFIX, "Started dataProcessThread");
    }

    while(1) {

    	// signal we are ready for data
        bp_regs_data.status.bits.datainready = 1;
        ppmWriteNet(handles.readyOut, 1);

        if(PSE_DIAG_LOW) {
        	bhmMessage("I", PREFIX, "Ready to receive Data...");
        }

        // wait for data
        bhmRestartReason rr = bhmWaitEvent(dataToProcess);
        if(rr == BHM_RR_TRIGGERED) {

            if(PSE_DIAG_LOW) {
            	bhmMessage("I", PREFIX, "Processing Data...");
            }

        	// signal we are not ready for data
            bp_regs_data.status.bits.datainready = 0;
            ppmWriteNet(handles.readyOut, 0);

            // delay for processing time
            bhmWaitDelay(100000);

            processData();

			if(PSE_DIAG_LOW) {
            	bhmMessage("I", PREFIX, "Processing finished - sending Data");
            }

            // Send processed data
			sendLocalData();

        } else {

            bhmMessage("W", PREFIX, "Wait Event returned unexpected restart reason %d", rr);

        }
    }
}

static void reportOverflow() {
	bp_regs_data.status.bits.overflow = 1;
    bhmMessage("W", PREFIX, "Attempt to send data while busy");
}

//////////////////////////////// Callback stubs ////////////////////////////////

//
// Callback when packet sent from previous node in chain
// Note: don't process the packet directly from this callback
//       to avoid logical loops!
//
PPM_PACKETNET_CB(packetReceived) {

    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "Data received from packetnet");
    }

    netPacketP p = data;

    // copy data and start processing
    if (!bp_regs_data.status.bits.datainready) {

    	reportOverflow();

    } else {

        dataLength = p->length;

        // Don't let packet overflow buffer
        if (dataLength >= BUFFER_SIZE) {
        	dataLength = BUFFER_SIZE;
        }

        // Copy packetnet data into local buffer
        Uns32 i;
        for (i=0; i<dataLength; i++) {
            localBuffer[i] = p->data[i];
        }

        if(PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX, "Received Packet: length %d", dataLength);
        }

        // Trigger dataProcessThread to process data in local buffer
        bhmTriggerEvent(dataToProcess);

    }
}

//
// Callback when status register is written
//  - clears any bits that are set in the write data
//  - triggers a dataRead event if waitingtosend bit was cleared
//
PPM_REG_WRITE_CB(clearStatus) {

	Bool waitingtosendPrev = bp_regs_data.status.bits.waitingtosend;

    // when written a high bit clears the representative status bit
	bp_regs_data.status.value &= ~data;

    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX,
        		   "Write status: clear bits: 0x%x: New status=0x%x",
				   data, bp_regs_data.status.value);
    }

    if (waitingtosendPrev && !bp_regs_data.status.bits.waitingtosend) {
    	// waitingtosend bit cleared - trigger dataRead event
    	bhmTriggerEvent(dataRead);
    }
}

//
// Callback when control register is written
//  - When start bit is written as a 1 send data in TX buffer
//
PPM_REG_WRITE_CB(writeControl) {

	bp_regs_data.control.value = data;

    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX,
        		   "Control Write length %d start %d (datainready %d)",
				   bp_regs_data.control.bits.length,
				   bp_regs_data.control.bits.start,
				   bp_regs_data.status.bits.datainready);
    }

    if(bp_regs_data.control.bits.start && bp_regs_data.control.bits.length) {

        if (!bp_regs_data.status.bits.datainready) {

        	// Attempt to write data while still processing previous data
        	reportOverflow();

        } else {

            // copy data from tx buffer to localBuffer and start processing
            Uns32 i;
            dataLength = bp_regs_data.control.bits.length;
            if (dataLength >= BP_MEM_TXBUFFER_SIZE) {
            	dataLength = BP_MEM_TXBUFFER_SIZE;
            }
            for (i=0; i<dataLength ;i++) {
                localBuffer[i] = BP_MEM_TXBUFFER[i];
            }
            bhmTriggerEvent(dataToProcess);

        }
    }
}

//
// Call back when next node writes to its readyOut net port.
// - Keep track of state of next node's readyOut state.
// - If a packet is waiting to write then trigger event to wake up
//   the thread waiting to write
// Note: don't process the packet directly from this callback
//       to avoid logical loops!
// Note: if no thread is waiting for this event then the trigger is a NOP
//
PPM_NET_CB(readyInCB) {

    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX,
                   "readyIn value written: old=%d, new=%d",
                   receiverReady, (Uns32)value);
    }

	receiverReady = (value != 0);

    if (receiverReady && bp_regs_data.status.bits.waitingtosend) {
        bhmTriggerEvent(dataRead);
    }
}

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    // Create event handles
    dataToProcess = bhmCreateNamedEvent("dataToProcess", "Event to trigger processing of written data");
    dataRead      = bhmCreateNamedEvent("dataRead", "Event triggered when data has been read");

    // start data processing thread
    bhmCreateThread(dataProcessThread, NULL, "dataProcess", STACK_TOP(dataProcessStack));

}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // No special handling required. All relevant state for this peripheral
    // model is handled automatically by the simulator
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // No special handling required. All relevant state for this peripheral
    // model is handled automatically by the simulator
}

