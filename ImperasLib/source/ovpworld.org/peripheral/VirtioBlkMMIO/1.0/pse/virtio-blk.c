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
// This model implements a VIRTIO Legacy (Device Version 1) MMIO block device
// as described in:
//      http://docs.oasis-open.org/virtio/virtio/v1.0/virtio-v1.0.pdf
//

#define BPORT1 handles.bport1

#include "pse.igen.h"
#include "pse.macros.igen.h"
#include "virtq.h"
#include "delta.h"

#define PREFIX "VIRTIO-BLK"

#define RVAL(_N)       (bport1_ab_data._N.value)
#define RFIELD(_N, _F) (bport1_ab_data._N.bits._F)

// VIRTIO Block Device block size
#define SECT_SIZE   512

// VIRTIO Max buffers per command
#define MAX_BUFFERS 16

//
// VIRTIO Block Request Types
//
#define VIRTIO_BLK_T_IN 0
#define VIRTIO_BLK_T_OUT 1
#define VIRTIO_BLK_T_FLUSH 4
#define VIRTIO_BLK_T_FLUSH_OUT 5
// This is undocumented but used by Linux Kernel!
#define VIRTIO_BLK_T_GET_BLK_ID 8

//
// VIRTIO Block Status
//
#define VIRTIO_BLK_S_OK 0
#define VIRTIO_BLK_S_IOERR 1
#define VIRTIO_BLK_S_UNSUPP 2

//
// Block request structure
//
typedef struct virtio_blk_req {
    Uns32 type;                 // Request type
    Uns32 ioprio;               // Ignored
    Uns64 sector;               // Sector on disk
} virtioBlkReq, *virtioBlkReqP;

//
// Device configuration
//
typedef struct virtio_blk_config {
    Uns64 capacity;
    Uns32 size_max;
    Uns32 seg_max;
    struct virtio_blk_geometry {
        Uns16 cylinders;
        Uns8 heads;
        Uns8 sectors;
    } geometry;
    Uns32 blk_size;
    struct virtio_blk_topology {
        // # of logical blocks per physical block (log2)
        Uns8 physical_block_exp;
        // offset of first aligned logical block
        Uns8 alignment_offset;
        // suggested minimum I/O size in blocks
        Uns16 min_io_size;
        // optimal (suggested maximum) I/O size in blocks
        Uns32 opt_io_size;
    } topology;
    Uns8 reserved;
} virtioBlkCfg, *virtioBlkCfgP;

//
// Static variables
//
int           imageFD        = -1;    // simulated disk file handle
hashTableP    deltaHandle    = NULL;  // Handle for delta table if enabled
Bool          interruptState = False; // current state of int net
virtioBlkCfg  blkCfg         = { 0 }; // config data (initialized in constructor)

// Levels of status required to do operations
typedef enum {
    STATUS_ACK,
    STATUS_DRIVER,
    STATUS_RUNNING
} statusE;

//
// fstat64() and lseek64() are supported by PSE semi-hosting intercepts.
// Define these here for now as they are not in the standard PSE/newlib toolchain.
//
struct stat64 {
    Uns64 st_size;
    Uns32 st_mode;
    Uns32 st_blksize;
    Uns32 st_blocks;
    Uns32 st_atime;
    Uns32 st_mtime;
    Uns32 st_ctime;
};

FUNCTOHOST(int, fstat64, int fd, struct stat64 *s)

FUNCTOHOST(_off64_t, lseek64, int fd, _off64_t offset, int whence)

//
// work around bug in PSE newlib code
//
static char *uns64ToString(Uns64 val) {
    static char buf[32];
    union { Uns64 u64; Uns32 u32[2]; } u={.u64=val};
    snprintf (buf, sizeof(buf), "0x%08x%08x", u.u32[1], u.u32[0]);
    return buf;
}


////////////////////////////////////////////////////////////////////////////////
// PRIMITIVE DISK OPERATIONS (WRAPPED BY RECORD/REPLAY)
////////////////////////////////////////////////////////////////////////////////

//
// This enumerates primitive disk operations
//
typedef enum drEventTypeE {
    DR_OPEN = 1,        // open() call
    DR_CLOSE,           // close() call
    DR_READ,            // read() call
    DR_READ_DATA,       // read() data block
    DR_WRITE,           // write() call
    DR_FSTAT64,         // fstat64() call
    DR_FSTAT64_DATA,    // fstat64() data block
    DR_LSEEK64,         // lseek64() call
    DR_ARGUMENT         // Argument check
} drEventType;

//
// These indicate whether record or replay mode is active
//
static Bool recording;
static Bool replaying;

//
// Record an event of a specific type
//
static void drRecordEventOfType(drEventType type, Uns32 bytes, const void *data) {
    bhmRecordEvent(type, bytes, data);
}

//
// Replay an event of a required type
//
static void drReplayEventOfType(drEventType type, Uns32 bytes, void *data) {

    drEventType actualType;
    Int32       actualBytes = bhmReplayEvent(NULL, &actualType, bytes, data);

    if(actualBytes<0) {
        bhmMessage("F", PREFIX,
            "Replay file ended: no further replay is possible"
        );
    } else if(type!=actualType) {
        bhmMessage("F", PREFIX,
            "Unexpected record type (required=%u, actual=%u)",
            type,
            actualType
        );
    } else if(bytes!=actualBytes) {
        bhmMessage("F", PREFIX,
            "Unexpected record size (type=%u required=%u, actual=%u)",
            type,
            bytes,
            actualBytes
        );
    }
}

//
// Check an argument on a call
//
static void drCheckArgument(
    Uns32       bytes,
    const void *arg,
    const char *argName,
    const char *function
) {

    Uns8 buf[bytes];

    drReplayEventOfType(DR_ARGUMENT, bytes, buf);

    Uns8 *restoredArg = buf;
    while (bytes--) {
        if (*(Uns8 *)arg++ != *restoredArg++) {
            bhmMessage("F", PREFIX,
                "%s argument value on %s call in replay file does not match value used when recording",
                argName,
                function
            );
        }
    }
}

//
// open() call wrapped by record/replay
//
static Int32 drOpen(const char *fileName, Int32 flags) {

    Int32 result;

    if(replaying) {
        drCheckArgument(strlen(fileName)+1, fileName, "filename", "open");
        drCheckArgument(sizeof(flags),     &flags,    "flags",    "open");
        drReplayEventOfType(DR_OPEN, sizeof(result), &result);
    } else {
        result = open(fileName, flags);
        if(recording) {
            drRecordEventOfType(DR_ARGUMENT, strlen(fileName)+1, fileName);
            drRecordEventOfType(DR_ARGUMENT, sizeof(flags),    &flags);
            drRecordEventOfType(DR_OPEN, sizeof(result), &result);
        }
    }

    return result;
}

//
// close() call wrapped by record/replay
//
static Int32 drClose(Int32 fd, Bool endOfSimulation) {

    Int32 result = 0;

    if(replaying) {
        if(!endOfSimulation) {
            drCheckArgument(sizeof(fd), &fd, "fd", "close");
            drReplayEventOfType(DR_CLOSE, sizeof(result), &result);
        }
    } else {
        result = close(fd);
        if(recording) {
            drRecordEventOfType(DR_ARGUMENT, sizeof(fd),  &fd);
            drRecordEventOfType(DR_CLOSE, sizeof(result), &result);
        }
    }

    return result;
}

//
// read() call wrapped by record/replay
//
static Uns32 drRead(Int32 fd, void *buf, Uns32 count) {

    Uns32 result;

    if(replaying) {
        drCheckArgument(sizeof(fd),    &fd,    "fd",    "read");
        drCheckArgument(sizeof(count), &count, "count", "read");
        drReplayEventOfType(DR_READ, sizeof(result), &result);
        if(result && (result!=-1)) {
            drReplayEventOfType(DR_READ_DATA, result, buf);
        }
    } else {
        result = read(fd, buf, count);
        if(recording) {
            drRecordEventOfType(DR_ARGUMENT, sizeof(fd),     &fd);
            drRecordEventOfType(DR_ARGUMENT, sizeof(count),  &count);
            drRecordEventOfType(DR_READ,     sizeof(result), &result);
            if(result && (result!=-1)) {
                drRecordEventOfType(DR_READ_DATA, result, buf);
            }
        }
    }

    return result;
}

//
// write() call wrapped by record/replay
//
static Uns32 drWrite(Int32 fd, const void *buf, Uns32 count) {

    Uns32 result;

    if(replaying) {
        drCheckArgument(sizeof(fd),    &fd,    "fd",    "write");
        drCheckArgument(sizeof(count), &count, "count", "write");
        drReplayEventOfType(DR_WRITE, sizeof(result), &result);
        // contents of buf are unused in replay mode
    } else {
        result = write(fd, buf, count);
        if(recording) {
            drRecordEventOfType(DR_ARGUMENT, sizeof(fd),     &fd);
            drRecordEventOfType(DR_ARGUMENT, sizeof(count),  &count);
            drRecordEventOfType(DR_WRITE,    sizeof(result), &result);
        }
    }

    return result;
}

//
// fstat64() call wrapped by record/replay
//
static Int32 drFStat64(Int32 fd, struct stat64 *s) {

    Int32 result;

    if(replaying) {
        drCheckArgument(sizeof(fd), &fd, "fd", "fstat64");
        drReplayEventOfType(DR_FSTAT64,      sizeof(result), &result);
        drReplayEventOfType(DR_FSTAT64_DATA, sizeof(*s),     s);
    } else {
        result = fstat64(fd, s);
        if(recording) {
            drRecordEventOfType(DR_ARGUMENT,     sizeof(fd),     &fd);
            drRecordEventOfType(DR_FSTAT64,      sizeof(result), &result);
            drRecordEventOfType(DR_FSTAT64_DATA, sizeof(*s),     s);
        }
    }

    return result;
}

//
// lseek64() call wrapped by record/replay
//
static Uns64 drLSeek64(Int32 fd, Uns64 offset, Int32 whence) {

    Uns64 result;

    if(replaying) {
        drCheckArgument(sizeof(fd),     &fd,     "fd",     "lseek64");
        drCheckArgument(sizeof(offset), &offset, "offset", "lseek64");
        drCheckArgument(sizeof(whence), &whence, "whence", "lseek64");
        drReplayEventOfType(DR_LSEEK64, sizeof(result), &result);
    } else {
        result = lseek64(fd, offset, whence);
        if(recording) {
            drRecordEventOfType(DR_ARGUMENT, sizeof(fd),     &fd);
            drRecordEventOfType(DR_ARGUMENT, sizeof(offset), &offset);
            drRecordEventOfType(DR_ARGUMENT, sizeof(whence), &whence);
            drRecordEventOfType(DR_LSEEK64,  sizeof(result), &result);
        }
    }

    return result;
}


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

    if (RFIELD(Status, Failed) || (imageFD < 0)) {
        bhmMessage("W", PREFIX"_AAF", "Device accessed after initialization failed");
// Disable for u-boot driver, which does not set this bit
//    } else if ((state >= STATUS_ACK) && !RFIELD(Status, Ack)) {
//        bhmMessage("W", PREFIX"_IBA", "Invalid access before status.Acknowledge set");
    } else if ((state >= STATUS_DRIVER) && !RFIELD(Status, Driver)) {
        bhmMessage("W", PREFIX"_IBD", "Invalid access before status.Driver set");
// Don't do this check - Linux does accesses of partition table before setting DriverOK
//    } else if ((state >= STATUS_RUNNING) && !RFIELD(Status, DriverOk)) {
//        bhmMessage("W", PREFIX"_IBR", "Invalid access before status.Driver_OK set");
    } else {
        return True;
    }
    return False;
}

//
// Read a virtio block request header (first DESC_SIZE bytes)
//
static Bool getBlkReqHeader(virtqDescP queue, virtioBlkReqP blkReq) {

    if (readVirtqBuffer(queue, sizeof(*blkReq), blkReq)) {

        if (PSE_DIAG_MEDIUM) {
            bhmMessage(
                "I", PREFIX"_DTE",
                "VirtioBlkReq: Type=%d, ioprio=%d, Sector=%s",
                blkReq->type, blkReq->ioprio, uns64ToString(blkReq->sector)
            );
        }

        return True;

    }

    return False;

}

//
// Read a sector into the virtqueue
// Check for sector in delta table first, if present
//
static Uns8 readSector(virtqDescP queue, Uns64 sector) {

    Uns8 buf[SECT_SIZE];

    if (deltaHandle && deltaRead(deltaHandle, sector, buf)) {

        // Data was in delta table

    } else {

        // Seek to the sector and read it
        drLSeek64(imageFD, sector*SECT_SIZE, SEEK_SET);

        Uns32 rc = drRead(imageFD, buf, SECT_SIZE);

        if (rc != SECT_SIZE) {
            bhmMessage(
                "W", PREFIX"_ERD",
                "Error reading disk: %s",
                rc < 0 ? strerror(errno) : "Wrong number of bytes returned"
            );
            return VIRTIO_BLK_S_IOERR;
        }
    }

    if (!writeVirtqBuffer(queue, SECT_SIZE, buf)) {
        return VIRTIO_BLK_S_IOERR;
    }

    return VIRTIO_BLK_S_OK;

}

//
// Write a sector from the virtqueue
// Use delta table if present
//
static Uns8 writeSector(virtqDescP queue, Uns64 sector) {

    Uns8 buf[SECT_SIZE];

    if (!readVirtqBuffer(queue, SECT_SIZE, buf)) {

        // error in virtqueue
        return VIRTIO_BLK_S_IOERR;

    } else if (deltaHandle) {

        // Write to the delta table
        deltaWrite(deltaHandle, sector, buf);

    } else {

        // Seek to the sector and write it
        drLSeek64(imageFD, sector*SECT_SIZE, SEEK_SET);

        Uns32 rc = drWrite(imageFD, buf, SECT_SIZE);

        if (rc!= SECT_SIZE) {
            bhmMessage(
                "W", PREFIX"_ERD",
                "Error writing disk: %s",
                rc < 0 ? strerror(errno) : "Wrong number of bytes returned"
            );
            return VIRTIO_BLK_S_IOERR;
        }
    }

    return VIRTIO_BLK_S_OK;
}

//
// Do read/write block request
// Processes as many 512 byte sectors as are available in the queue
//
static Uns8 doCommand(virtqDescP queue, virtioBlkReqP blkReq, Uns32 *written) {

    assert(blkReq->type==VIRTIO_BLK_T_IN || blkReq->type==VIRTIO_BLK_T_OUT);

    Bool  readCmd = (blkReq->type == VIRTIO_BLK_T_IN);
    Uns64 sector;

    *written = 0;
    for (sector=blkReq->sector; bytesAvailVirtq(queue, SECT_SIZE); sector++) {

        if (sector >= blkCfg.capacity) {
            bhmMessage(
                "W", PREFIX"_OOR",
                "%s past end of disk",
                readCmd ? "Read" : "Write"
            );
            return VIRTIO_BLK_S_IOERR;
        }

        if (readCmd) {

            Uns8 status = readSector(queue, sector);
            if (status != VIRTIO_BLK_S_OK) return status;

        } else {

            Uns8 status = writeSector(queue, sector);
            if (status != VIRTIO_BLK_S_OK) return status;
            *written += SECT_SIZE;
        }

        if (PSE_DIAG_HIGH) {
            bhmMessage(
                "I", PREFIX"_DIO",
                "%d bytes at sector %s %s",
                SECT_SIZE,
                uns64ToString(sector),
                readCmd ? "Read" : "Written"
            );
        }
    }

    return VIRTIO_BLK_S_OK;

}

//
// Write the status byte into last byte of queue
//
static void writeStatus(virtqDescP queue, Uns8 status) {

    if ((status==VIRTIO_BLK_S_OK) && bytesAvailVirtq(queue, 2)) {
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
// Process a descriptor table list.
// VIRTIO_F_ANY_LAYOUT is not supported so descriptors must always be:
//   blkReq  (length=16)
//   data... (length=multiple of 512, can be more than one)
//   status  (length=1)
//
static Uns32 processDescriptor(Uns32 head) {

    virtqDesc    queue;
    virtioBlkReq blkReq;
    Uns32        bytesWritten = 0;
    Uns8         status = VIRTIO_BLK_S_IOERR;

    if (getVirtqDesc(head, &queue)) {

        if (!getBlkReqHeader(&queue, &blkReq)) {

            bhmMessage("W", PREFIX"_EBD", "Unable to read virtioBlkReq");

        } else {

            switch (blkReq.type) {
                case VIRTIO_BLK_T_FLUSH:
                case VIRTIO_BLK_T_FLUSH_OUT:
                    // can ignore
                    status = VIRTIO_BLK_S_OK;
                    break;
                case VIRTIO_BLK_T_IN:
                case VIRTIO_BLK_T_OUT:
                    status = doCommand(&queue, &blkReq, &bytesWritten);
                    break;
                case VIRTIO_BLK_T_GET_BLK_ID:
                    // Not supported, but do not warn
                    break;
                default:
                    bhmMessage(
                        "W", PREFIX"_IBR",
                        "Invalid block request type %d",
                        blkReq.type
                    );
                    status = VIRTIO_BLK_S_UNSUPP;
                    break;
            }

            writeStatus(&queue, status);

        }
    }

    return bytesWritten;
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
    // Indicate device is present only if a disk has been specified
    DATA4 = (imageFD >= 0) ? RVAL(MagicValue) : 0;
}

PPM_NBYTE_READ_CB(rdHostF) {
    CHECK_READ_NBYTES(4)
    Uns32 rVal = 0;
    if (statusOK(STATUS_DRIVER)) {
        Uns32 HostFeaturesSelect = RVAL(HostFSel);
        if (HostFeaturesSelect == 0) {
            // Only HostFeatures[0] is currently supported
            rVal = RVAL(HostFeatures);
        }
    }
    DATA4 = rVal;
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

        if (DATA4 == 0) {

            Uns16 head;


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

            setVirtqBase(virtqBase);

        }
        RVAL(QueuePFN) = DATA4;
    }

}

//
// Only one virtqueue supported by block devices so an attempt to
// write any of the select registers with a non-zero value is invalid
//
PPM_NBYTE_WRITE_CB(wrQSel) {
    CHECK_WRITE_NBYTES(4)

    if (statusOK(STATUS_DRIVER)) {
        if (DATA4 != 0) {
            bhmMessage(
                "W", PREFIX"_IQS",
                "Invalid select %d set by driver. Must be 0.",
                DATA4
            );
        }
    }
}

PPM_NBYTE_READ_CB(readCfg) {

    // Offset passed in is from beginning of port. Adjust to beginning of BlkConfig memory
    Uns32 blkConfigOffset = BPORT1_AB_BLKCONFIG - BPORT1;
    Uns32 i;
    Uns32 cfgidx;

    if ((offset < blkConfigOffset) ||
        (offset - blkConfigOffset) + (bytes - 1) > BPORT1_AB_BLKCONFIG_BYTES) {
        bhmMessage("F", "ASSERT", "Read out of range: offset=%d, bytes=%d", offset, bytes);
    }

    // Copy data from blkCfg structure to return value.
    // Return 0's for any bytes above range of blkCfg
    for (i = 0, cfgidx = offset - blkConfigOffset; i < bytes; i++, cfgidx++) {
        Uns8  val = 0;
        if (cfgidx < sizeof(blkCfg)) {
            val = ((Uns8 *)&blkCfg)[cfgidx];
        }
        ((Uns8 *)data)[i] = val;
    }

    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX"_RDC",
            "readCfg(Uns32 offset=%d, Uns32 bytes=%d, void *user=%p, Bool artifactAccess=%d)\n",
            offset, bytes, userData, artifactAccess);
    }
}

static void resetDevice() {
    reset_Reset(1,0);
    RVAL(Status)  = 0;
    setVirtqBase(0);
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

//
// Return the size of a file given its file descriptor
//
static Uns64 fileSize(Int32 fd) {

    struct stat64 st;
    Uns64         size = 0;

    if (drFStat64(fd, &st) >= 0) {
        size = st.st_size;
    }

    return size;
}

//
// Open the hard disk image file, if specified
//
static void initDrive(void) {

    char imageName[BHM_MAX_PATH];
    Bool delta;
    bhmBoolParamValue("VB_DRIVE_DELTA", &delta);
    Uns32 mode  = delta ? O_RDONLY : O_RDWR;

    if(bhmStringParamValue("VB_DRIVE", imageName, sizeof(imageName)) == 0) {

        // No image specified - device will be inert

    } else if ((imageFD = drOpen(imageName, mode)) < 0) {

        bhmMessage(
            "W", PREFIX"_UOI",
            "Unable to open image file '%s'. Block device not available",
            imageName
        );

    } else {

        // Set capacity register according to the number of sectors in the file
        blkCfg.capacity = fileSize(imageFD) / SECT_SIZE;

        if (blkCfg.capacity) {

            if (delta) {
                deltaHandle = deltaNew(SECT_SIZE);
            }

            bhmMessage(
                "I", PREFIX"_UIF",
                "Using %simage file '%s', size %s sectors.%s",
                replaying ? "replay from " : "",
                imageName,
                uns64ToString(blkCfg.capacity),
                delta ? " (Delta mode)" : ""
            );

        } else {

            bhmMessage(
                "W" PREFIX"_EIF",
                "Image file '%s' is empty. Block device not available.",
                imageName
            );
            drClose(imageFD, False);
            imageFD = -1;

        }
    }
}

static void shutdownDrive(Bool endOfSimulation) {

    if (imageFD >= 0) {
        drClose(imageFD, endOfSimulation);
    }

    bhmRecordFinish();
    bhmReplayFinish();

}

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();
    resetDevice();

    // Get record/replay settings
    recording = bhmRecordStart();
    replaying = bhmReplayStart();

    initDrive();
}

PPM_DESTRUCTOR_CB(destructor) {
    shutdownDrive(True);
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    if(phase==PPM_POST_SAVE_RESTORE) {
        recording = bhmRecordStart();
        replaying = bhmReplayStart();
    }
}

