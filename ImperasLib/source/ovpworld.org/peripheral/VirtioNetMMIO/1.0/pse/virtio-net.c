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


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                           Imperas/OVP Generated
//                          Thu May 15 23:03:31 2014
//
////////////////////////////////////////////////////////////////////////////////

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

//
// This model implements a VIRTIO Legacy (Device Version 1) MMIO net device
// as described in:
//      http://docs.oasis-open.org/virtio/virtio/v1.0/virtio-v1.0.pdf
//

#define BPORT1 handles.bport1

#include "pse.igen.h"
#include "pse.macros.igen.h"
#include "virtq.h"

#define PREFIX "VIRTIO-NET"

#define RVAL(_N)       (bport1_ab_data._N.value)
#define RFIELD(_N, _F) (bport1_ab_data._N.bits._F)

#define VIRTQ_RX 0
#define VIRTQ_TX 1

#define NUM_VIRTQUEUES 2

//
// VIRTIO Net Status
//
#define VIRTIO_NET_S_ERR -1
#define VIRTIO_NET_S_OK 0
#define VIRTIO_NET_S_LINK_UP 1
#define VIRTIO_NET_S_ANNOUNCE 2

//
// VIRTIO Net Hdr flags
//
#define VIRTIO_NET_HDR_F_NEEDS_CSUM 1

//
// VIRTIO Net GSO types
//
#define VIRTIO_NET_HDR_GSO_NONE 0
#define VIRTIO_NET_HDR_GSO_TCPV4 1
#define VIRTIO_NET_HDR_GSO_UDP 3
#define VIRTIO_NET_HDR_GSO_TCPV6 4
#define VIRTIO_NET_HDR_GSO_ECN 0x80


typedef struct virtio_net_hdr {
Uns8 flags;
Uns8 gso_type;
Uns16 hdr_len;
Uns16 gso_size;
Uns16 csum_start;
Uns16 csum_offset;
//Uns16 num_buffers;
} virtioNetReq, *virtioNetReqP;

//
// Device configuration
//
typedef struct virtio_net_config {
    Uns8 mac[6];
    Uns16 status;
    Uns16 max_virtqueue_pairs;
} virtioNetCfg, *virtioNetCfgP;

//
// Static variables
//
Bool          interruptState = False;   // current state of int net
virtioNetCfg  netCfg         = {{ 0 }}; // config data (initialized in constructor)

bhmEtherCh     ethHandle;
bhmEventHandle rx_event;

// Levels of status required to do operations
typedef enum {
    STATUS_ACK,
    STATUS_DRIVER,
    STATUS_RUNNING
} statusE;

typedef struct virtio_queue_select {
    Uns32 QueueNumMax;
    Uns32 QueueNum;
    Uns32 QueueAlign;
    Uns32 QueuePFN;
} virtioQueueSel, *virtioQueueSelP;

virtioQueueSel vqueues[NUM_VIRTQUEUES];

//
// work around bug in PSE newlib code
//
static char *uns64ToString(Uns64 val) {
    static char buf[32];
    union { Uns64 u64; Uns32 u32[2]; } u={.u64=val};
    snprintf (buf, sizeof(buf), "0x%08x%08x", u.u32[1], u.u32[0]);
    return buf;
}

// Todo: Removed any explicit record/replay functionality as should most be
//       implemented with the bhm backend.


////////////////////////////////////////////////////////////////////////////////
// MODEL CODE
////////////////////////////////////////////////////////////////////////////////

//
// Update the interrupt line according to the IntStatus register
//
static void updateInterrupt() {

    Bool interruptActive = (RVAL(IntStatus) != 0);

    // Has interrupt changed?
    if (interruptState != interruptActive) {

        ppmWriteNet(handles.Interrupt, interruptActive);
        interruptState = interruptActive;

        if (PSE_DIAG_HIGH) {
            bhmMessage(
                "I", PREFIX"_INT",
                "Interrupt %s",
                interruptState ? "set" : "cleared"
            );
        }
    }
}

//
// Turn an alignment value to a shift
// (align assumed to be a power of 2)
//
static Uns32 alignToShift(Uns32 align) {
    Uns32 shift = 0;
    if (align) {
        while ((align & 1) == 0) {
            shift++;
            align >>= 1;
        }
    }
    return shift;
}

static Bool statusOK(statusE state) {

    if (RFIELD(Status, Failed)) {
        bhmMessage("W", PREFIX"_AAF", "Device accessed after initialization failed");
// Disable for u-boot driver, which does not set this bit
//    } else if ((state >= STATUS_ACK) && !RFIELD(Status, Ack)) {
//        bhmMessage("W", PREFIX"_IBA", "Invalid access before status.Acknowledge set");
    } else if ((state >= STATUS_DRIVER) && !RFIELD(Status, Driver)) {
        bhmMessage("W", PREFIX"_IBD", "Invalid access before status.Driver set");
   } else {
        return True;
    }
    return False;
}

Bool isLinkUp(void)
{
    return ethHandle != (Uns32)(-1);
}

void phyWriteData(void *data, unsigned int len)
{
    if (PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX, "Writing %u bytes to the PHY\n", len);

    // TODO: loopback when enabled

    // check link status?
    if (!isLinkUp()) {
        if (PSE_DIAG_LOW)
            bhmMessage("I", PREFIX, "Link is down while writing to PHY; dropping\n");
        return;
    }

    // write to the backend
    bhmEthernetWriteFrame(ethHandle, data, len);
}

//
// Read a virtio net request header (first DESC_SIZE bytes)
//
static Bool getNetReqHeader(virtqDescP queue, virtioNetReqP netReq) {

    if (readVirtqBuffer(queue, sizeof(*netReq), netReq)) {

        if (PSE_DIAG_MEDIUM) {
            bhmMessage(
                "I", PREFIX"_DTE",
                "VirtioNetReq: Type=%d, flags=%d, L=%d, S=%d",
                netReq->gso_type, netReq->flags, netReq->hdr_len, netReq->gso_size
            );
        }
        return True;

    }
    return False;
}

//
// Do write command
//
static Uns8 doCommand(virtqDescP queue, virtioNetReqP netReq, Uns32 *written) {
    virtqDesc    desc;

    Uns16 next = queue->next;

    if (next == INVALID_IDX || !getVirtqDesc(next, &desc)) {
        bhmMessage("W", PREFIX"_EBD", "getVirtqDesc returned FALSE");
        return VIRTIO_NET_S_ERR;
    }

    void *buffer;
    buffer = malloc(desc.len);
    readVirtqBuffer(&desc, desc.len, buffer);

    phyWriteData(buffer, desc.len);



    *written = desc.len;

    seekToEndVirtq(&desc);
    return VIRTIO_NET_S_OK;

}

//
// Write the status byte into last byte of queue
//
static void writeStatus(virtqDescP queue, Uns8 status) {

    if ((status!=VIRTIO_NET_S_OK) && bytesAvailVirtq(queue, 2)) {
        // Strange - not at last byte of buffer when status is OK
        bhmMessage("W", PREFIX"_USM", "Unused space at end of buffer");
    }

    if (PSE_DIAG_HIGH) {
        bhmMessage(
            "I", PREFIX"_WSB",
            "Write Status=%d to last byte of virtqueue",
            status
        );
    }

    seekToEndVirtq(queue);
    writeVirtqBuffer(queue, 1, &status);


}

//
// Process a descriptor
//
static Uns32 processDescriptor(Uns32 head) {

    virtqDesc    queue;
    virtioNetReq netReq;
    Uns32        bytesWritten = 0;
    Uns8         status = VIRTIO_NET_S_ERR;


    if (getVirtqDesc(head, &queue)) {

        if (!getNetReqHeader(&queue, &netReq)) {

            bhmMessage("W", PREFIX"_EBD", "Unable to read virtioNetReq");

        } else {
            if (PSE_DIAG_HIGH) {
                bhmMessage("I", PREFIX"_EBD", "Process Descriptor");
            }
            switch (netReq.gso_type) {
                case VIRTIO_NET_HDR_GSO_NONE:
                    if (PSE_DIAG_HIGH) {
                        bhmMessage("I", PREFIX"_EBD", "GSO_NONE");
                     }
                    doCommand(&queue,&netReq, &bytesWritten);
                    status = VIRTIO_NET_S_OK;
                    break;
                case VIRTIO_NET_HDR_GSO_TCPV4:
                    if (PSE_DIAG_HIGH) {
                        bhmMessage("I", PREFIX"_EBD", "GSO_TCPV4");
                    }
                    //doCommand()  //TODO: Support other packet types
                    break;
                case VIRTIO_NET_HDR_GSO_UDP:
                    if (PSE_DIAG_HIGH) {
                        bhmMessage("I", PREFIX"_EBD", "GSO_UDP");
                    }
                    //doCommand()  //TODO: Support other packet types
                    break;
                case VIRTIO_NET_HDR_GSO_TCPV6:
                    if (PSE_DIAG_HIGH) {
                        bhmMessage("I", PREFIX"_EBD", "GSO_TCPV6");
                    }
                    //doCommand() //TODO: Support other packet types
                    break;
                case VIRTIO_NET_HDR_GSO_ECN:
                    if (PSE_DIAG_HIGH) {
                        bhmMessage("I", PREFIX"_EBD", "GSO_ECN");
                    }
                    //doCommand()  //TODO: Support other packet types
                    break;
                default:
                    bhmMessage(
                        "W", PREFIX"_INR",
                        "Invalid net request type %d",
                        netReq.gso_type
                    );
                    status = VIRTIO_NET_S_ERR;
                    break;
            }
            writeStatus(&queue, status);
        }
    }

    return bytesWritten;
}

static BHM_ETHER_PACKET_CB(rxPacket) {
    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX"_RXT", "rxPacket() process packet, len = %d", bytes);
    }

    selectVirtq(VIRTQ_RX);

    virtqDesc  queue;
    Uns16      head;

    // Process all new entrys in the Available ring
    if ((head = getNextAvailEntry()) != INVALID_IDX) {

        if (getVirtqDesc(head, &queue)) {
            if (PSE_DIAG_MEDIUM) {
                bhmMessage("I", PREFIX"_RXT", "getVirtqDesc returned TRUE len=%d, pos=%d",queue.len,queue.currentPos);
            }

            virtioNetReq hdr;
            hdr.flags = 0;
            hdr.gso_type = VIRTIO_NET_HDR_GSO_NONE;
            writeVirtqBuffer(&queue, sizeof(hdr), &hdr);

            writeVirtqBuffer(&queue, bytes, data);

            putNextUsedEntry(head, sizeof(hdr) + bytes);
            // Send interrupt
            RFIELD(IntStatus, UsedRingUpdate) = 1;
            updateInterrupt();
        }
    } else {
        bhmMessage("W", PREFIX"_RXT", "getNextAvailEntry Failed");
    }
    selectVirtq(RVAL(QueueSel));
}

#define CHECK_READ_NBYTES(_B) \
    if((offset & ((_B) - 1)) != 0 || bytes != (_B)) { \
        bhmMessage("E", "PPM_RNB", "Invalid %d byte read with offset %d. " \
                   "Only aligned %d byte accesses supported", bytes, offset, _B); \
        memset(data, 0, bytes); \
        return; \
    }

#define CHECK_WRITE_NBYTES(_B) \
    if((offset & ((_B) - 1)) != 0 || bytes != (_B)) { \
        bhmMessage("E", "PPM_RNB", "Invalid %d byte read with offset %d. " \
                   "Only aligned %d byte accesses supported", bytes, offset, _B); \
        return; \
    }

// Guaranteed safe to use after calling CHECK_READ_NBYTES(4) or CHECK_WRITE_NBYTES(4)
#define DATA4 (*(Uns32 *)data)

PPM_NBYTE_READ_CB(rdMagic) {
    CHECK_READ_NBYTES(4)
    DATA4 = RVAL(MagicValue);
}

PPM_NBYTE_READ_CB(rdHostF) {
    CHECK_READ_NBYTES(4)
    if (statusOK(STATUS_DRIVER)) {
        DATA4 = RVAL(HostFeatures);
    } else {
        DATA4 = 0;
    }
}

PPM_NBYTE_READ_CB(rdIntStat) {
    CHECK_READ_NBYTES(4)
    if (statusOK(STATUS_RUNNING)) {
        DATA4 = RVAL(IntStatus);
    } else {
        DATA4 = 0;
    }
}

PPM_NBYTE_READ_CB(rdQPFN) {
    CHECK_READ_NBYTES(4)
    if (statusOK(STATUS_DRIVER)) {
        DATA4 = RVAL(QueuePFN);
    } else {
        DATA4 = 0;
    }
}

PPM_NBYTE_READ_CB(rdStatus) {
    CHECK_READ_NBYTES(4)
    DATA4 = RVAL(Status);
}

PPM_NBYTE_WRITE_CB(wrGuestF) {
    CHECK_WRITE_NBYTES(4)

    if (statusOK(STATUS_DRIVER)) {

        RVAL(GuestFeatures) = DATA4;

        if (RVAL(GuestFeatures) & ~RVAL(HostFeatures)) {
            bhmMessage(
                "W", PREFIX"_IGF",
                "Invalid GuestFeatures 0x%x set by driver. May only include 0x%x.",
                RVAL(GuestFeatures), RVAL(HostFeatures)
            );
            RFIELD(Status, Failed) = 1;
        }
    }
}

PPM_NBYTE_WRITE_CB(wrIntAck) {
    CHECK_WRITE_NBYTES(4)

    if (statusOK(STATUS_RUNNING)) {

        RVAL(IntAck) = (RVAL(IntAck) & ~0x3) | (DATA4 & 0x3);

        RVAL(IntStatus) &= ~RVAL(IntAck);

        updateInterrupt();
    }
}

PPM_NBYTE_WRITE_CB(wrQNotify) {
    CHECK_WRITE_NBYTES(4)

    if (statusOK(STATUS_DRIVER)) {

        RVAL(QueueNotify) = DATA4;

        // RX Virtq
        if (DATA4 == VIRTQ_RX) {


        //TX Virtq
        } else if (DATA4 == VIRTQ_TX) { //Todo: data <= 1

            Uns16 head;

            selectVirtq(DATA4);

            // Process all new entrys in the Available ring
            while ((head = getNextAvailEntry()) != INVALID_IDX) {

                Uns32 written = processDescriptor(head);

                // Update the used ring
                putNextUsedEntry(head, written);

                // Send interrupt
                RFIELD(IntStatus, UsedRingUpdate) = 1;
                updateInterrupt();

            }


        } else {

            bhmMessage(
                "W", PREFIX"_IQS",
                "Invalid QueueNotify value %d written. Must be 0.",
                DATA4
            );

        }
    }
}

PPM_NBYTE_WRITE_CB(wrQNum) {
    CHECK_WRITE_NBYTES(4)

    if (statusOK(STATUS_DRIVER)) {

        if (DATA4 == 0) {

            bhmMessage(
                "W", PREFIX"_QNZ",
                "Invalid QueueNum value %d ignored. Must not be 0.",
                DATA4
            );

        } else {

            if (DATA4 > RVAL(QueueNumMax)) {
                bhmMessage(
                    "W", PREFIX"_IQN",
                    "Invalid Queuenum value %d written. Exceeds QueueNumMax=%d.",
                    DATA4, RVAL(QueueNumMax)
                );
            }
            RVAL(QueueNum) = DATA4;

        }
    }
}

static void wrAlign(char *regName, Uns32 bytes, Uns32 data, Uns32 *value) {
    if ((data & (data-1)) != 0) {
        bhmMessage(
            "W", PREFIX"_IQA",
            "Write of non-power of 2 value %d to %s ignored",
            data, regName
        );
    } else {
        *value = data;
    }
}

PPM_NBYTE_WRITE_CB(wrQAlign) {
    CHECK_WRITE_NBYTES(4)
    wrAlign("QueueAlign", bytes, DATA4, &RVAL(QueueAlign));
}

PPM_NBYTE_WRITE_CB(wrGPgSz) {
    CHECK_WRITE_NBYTES(4)
    wrAlign("GuestPageSz", bytes, DATA4, &RVAL(GuestPageSz));
}

PPM_NBYTE_WRITE_CB(wrQPFN) {
    CHECK_WRITE_NBYTES(4)

    if (statusOK(STATUS_DRIVER)) {

        Uns32 align = RVAL(QueueAlign);

        if (DATA4 == 0) {

            if (PSE_DIAG_LOW) {
                bhmMessage(
                    "I", PREFIX"_VQR",
                    "Virtqueue reset by writing 0 to QueuePFN"
                );
            }

        } else if (align==0) {

            bhmMessage(
                "W", PREFIX"_VQR",
                "Invalid write to QueuePFN with QueueAlign=0 ignored"
            );
            return;

        } else {

            // Convert data to 64 bits, then shift
            Addr virtqBase = DATA4;
            virtqBase <<= alignToShift(align);

            if (PSE_DIAG_LOW) {
                bhmMessage(
                    "I", PREFIX"_VQR",
                    "Virtqueue at address %s",
                    uns64ToString(virtqBase)
                );
            }
            selectVirtq(RVAL(QueueSel));
            setVirtqBase(virtqBase);

        }
        RVAL(QueuePFN) = DATA4;
    }

}


PPM_NBYTE_WRITE_CB(wrSel) {
    CHECK_WRITE_NBYTES(4)

    if (statusOK(STATUS_DRIVER)) {
        if (DATA4 < NUM_VIRTQUEUES) {
            //vqueues[RVAL(QueueSel)].QueueNumMax;
            vqueues[RVAL(QueueSel)].QueueNum = RVAL(QueueNum);
            vqueues[RVAL(QueueSel)].QueueAlign = RVAL(QueueAlign);
            vqueues[RVAL(QueueSel)].QueuePFN = RVAL(QueuePFN);

            //RVAL(QueueNumMax) = 0x100;
            RVAL(QueueNum) = vqueues[DATA4].QueueNum;
            RVAL(QueueAlign) = vqueues[DATA4].QueueAlign;
            RVAL(QueuePFN) = vqueues[DATA4].QueuePFN;

            RVAL(QueueSel) = DATA4;

            selectVirtq(DATA4);
        } else {
            //TODO: Error
        }

    }
}

static void resetDevice() {
    reset_Reset(1,0);
    RVAL(Status)  = 0;
    int i;
    for (i = 0; i < NUM_VIRTQUEUES; i++) {
        selectVirtq(i);
        setVirtqBase(0);
    }

}

// TODO: Remove when iGen is updated to define field masks in pse.macros.igen.h when -nbyteregisters is enabled
#define BPORT1_AB_STATUS_FAILED   (0x1 << 7)

PPM_NBYTE_WRITE_CB(wrStatus) {
    CHECK_WRITE_NBYTES(4)

    if (DATA4 == 0) {

        resetDevice();

    } else {

        if ((DATA4 & BPORT1_AB_STATUS_FAILED) && !RFIELD(Status, Failed)) {
            // Issue warning when driver sets failed bit
            bhmMessage("W", PREFIX"_DIF", "Driver initialization has failed");
        }

        RVAL(Status) |= (DATA4 & 0x87);

    }
}

PPM_NBYTE_READ_CB(readCfg) {

    // Offset passed in is from beginning of port. Adjust to beginning of NetConfig memory
    Uns32 netConfigOffset = BPORT1_AB_NETCONFIG - BPORT1;
    Uns32 i;
    Uns32 cfgidx;

    if ((offset < netConfigOffset) ||
        (offset - netConfigOffset) + (bytes - 1) > BPORT1_AB_NETCONFIG_BYTES) {
        bhmMessage("F", "ASSERT", "Read out of range: offset=%d, bytes=%d", offset, bytes);
    }

    // Copy data from netCfg structure to return value.
    // Return 0's for any bytes above range of netCfg
    for (i = 0, cfgidx = offset - netConfigOffset; i < bytes; i++, cfgidx++) {
        Uns8  val = 0;
        if (cfgidx < sizeof(netCfg)) {
            val = ((Uns8 *)&netCfg)[cfgidx];
        }
        ((Uns8 *)data)[i] = val;
    }

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX"_RDC",
            "readCfg(Uns32 offset=%d, Uns32 bytes=%d, void *user=%p, Bool artifactAccess=%d)\n",
            offset, bytes, userData, artifactAccess);
    }
}
PPM_NBYTE_WRITE_CB(writeCfg) {
    // Just ignore writes to cfg region
    // - Spec states that this is read-only
    // - u-boot writes to them anyway in function virtio_net_write_hwaddr() in virtio_net.c
    // - go figure
}

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();
    resetDevice();

    Uns64  mac;
    bhmUns64ParamValue("macaddress", &mac);

    netCfg.mac[0] = (mac >>  0) & 0xff;
    netCfg.mac[1] = (mac >>  8) & 0xff;
    netCfg.mac[2] = (mac >> 16) & 0xff;
    netCfg.mac[3] = (mac >> 24) & 0xff;
    netCfg.mac[4] = (mac >> 32) & 0xff;
    netCfg.mac[5] = (mac >> 40) & 0xff;

    int i;
    // Set initial value of unselected virtuqueue regs
    for (i = 0; i < NUM_VIRTQUEUES; i++)
    {
        vqueues[i].QueueNum = RVAL(QueueNum);
        vqueues[i].QueueAlign = RVAL(QueueAlign);
        vqueues[i].QueuePFN = RVAL(QueuePFN);
    }

    rx_event = bhmCreateEvent();

    ethHandle = bhmEthernetOpenAuto();
    bhmEthernetInstallCB(ethHandle, rxPacket, 0);

}


PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}

