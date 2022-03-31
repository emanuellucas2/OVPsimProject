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

//
// Read/Write VIRTIO Legacy (Device Version 1) MMIO virtual queues
// as described in:
//      http://docs.oasis-open.org/virtio/virtio/v1.0/virtio-v1.0.pdf
//

#include "pse.igen.h"

#include "virtq.h"

#define PREFIX "VIRTQUEUE"

#define RVAL(_N)       (bport1_ab_data._N.value)
#define RFIELD(_N, _F) (bport1_ab_data._N.bits._F)

//
// VIRTIO Virtual Queue Layout
//
#define QUEUE_SIZE        (RVAL(QueueNum))
#define QUEUE_ALIGN       (RVAL(QueueAlign))
#define ALIGN(_N, _S)     (((_N) + ((_S)-1)) & ~((_S)-1))

// Macros for locating a descriptor table entry
#define DESC_SIZE         16
#define DESC_TABLE_SIZE   (DESC_SIZE*QUEUE_SIZE)
#define DESC_OFFSET(_N)   (((_N)%QUEUE_SIZE)*DESC_SIZE)

// Macros for locating an Available ring entry
#define AVAIL_SIZE        2
#define AVAIL_BASE        (DESC_TABLE_SIZE)
#define AVAIL_RING_SIZE   (6+(AVAIL_SIZE*QUEUE_SIZE))
#define AVAIL_OFFSET(_N)  (AVAIL_BASE+4+(((_N)%QUEUE_SIZE)*AVAIL_SIZE))

// Macros for locating the Available ring Flags value
#define AVAIL_FLAGS_SIZE   2
#define AVAIL_FLAGS_OFFSET (AVAIL_BASE)

// Macros for locating the Available ring idx value
#define AVAIL_IDX_SIZE     2
#define AVAIL_IDX_OFFSET   (AVAIL_BASE+AVAIL_FLAGS_SIZE)

// Macros for locating a Used ring entry
#define USED_SIZE         8
#define USED_BASE         (ALIGN(DESC_TABLE_SIZE+AVAIL_RING_SIZE, QUEUE_ALIGN))
#define USED_OFFSET(_N)   (USED_BASE+4+(((_N)%QUEUE_SIZE)*USED_SIZE))

// Macros for locating the Used ring Flags value
#define USED_FLAGS_SIZE   2
#define USED_FLAGS_OFFSET (USED_BASE)

// Macros for locating the Used ring idx value
#define USED_IDX_SIZE     2
#define USED_IDX_OFFSET   (USED_BASE+USED_FLAGS_SIZE)

//
// virtqueue used ring structure
//
typedef struct virtq_used_elem {
    Uns32 id;    // Index of start of used descriptor chain
    Uns32 len;   // Length of the descriptor chain which was used (written to)
} virtqUsedElem, *virtqUsedElemP;



#define MAX_NUM_QUEUES 2
//
// Static variables
//

Uns32 selectedQueue = 0;
Addr  virtqBase[MAX_NUM_QUEUES] = {0,0};
Uns16 lastAvailSeen[MAX_NUM_QUEUES] = {INVALID_IDX,INVALID_IDX};

//
// work around bug in PSE newlib code
//
static char *uns64ToString(Uns64 val) {
    static char buf[32];
    union { Uns64 u64; Uns32 u32[2]; } u={.u64=val};
    snprintf (buf, sizeof(buf), "0x%08x%08x", u.u32[1], u.u32[0]);
    return buf;
}

//
// Read a value from simulated memory
//
Bool readSimMemory(Addr address, Uns32 bytes, void *data) {
    return ppmReadAddressSpace(handles.dma, address, bytes, data);
}

//
// Write a value to simulated memory
//
Bool writeSimMemory(Addr address, Uns32 bytes, void *data) {
    return ppmWriteAddressSpace(handles.dma, address, bytes, data);
}

//
// Read data from the virtqueue buffer
//
static Bool readVirtq(Uns32 offset, Uns32 bytes, void *data) {

    if (virtqBase[selectedQueue] == 0) {

        bhmMessage(
            "W", PREFIX"_VQI",
            "Attempt to access virtq without valid QueuePFN set"
        );
        return False;

    } else if (!readSimMemory(virtqBase[selectedQueue]+offset, bytes, data)) {

        bhmMessage(
            "W", PREFIX"_USM",
            "Unable to read %d bytes at offset %d of virtq at %s",
            bytes, offset, uns64ToString(virtqBase[selectedQueue])
        );
        return False;

    }

    return True;

}

//
// Write data to the virtqueue buffer
//
Bool writeVirtq(Uns32 offset, Uns32 bytes, void *data) {

    if (virtqBase[selectedQueue] == 0) {

        bhmMessage(
            "W", PREFIX"_VQI",
            "Attempt to access virtqueue without valid QueuePFN set"
        );
        return False;

    } else if (!writeSimMemory(virtqBase[selectedQueue]+offset, bytes, data)) {

        bhmMessage(
            "W", PREFIX"_USM",
            "Unable to write %d bytes at offset %d of virtq at %s",
            bytes, offset, uns64ToString(virtqBase[selectedQueue])
        );
        return False;

    }

    return True;

}


void selectVirtq(Uns32 select) {
    if (select >= MAX_NUM_QUEUES) {
        bhmMessage(
            "W", PREFIX"_SVQ",
            "Unable to select Virtq %d",select
        );
        return;
    }
    selectedQueue = select;

}


//
// Set the virtqBase address
// When set to 0 also reset the lastAvailSeen value
//
void setVirtqBase(Addr base) {

    virtqBase[selectedQueue] = base;

    if (base == 0) {

        // Reset the Available ring pointer
        lastAvailSeen[selectedQueue] = 0;

    } else {

        // Set the Used ring flags value to 0
        // indicating we require notification of updates
        Uns8 flags = 0;
        writeVirtq(USED_FLAGS_OFFSET, sizeof(flags), &flags);

    }
}

//
// Read the next unread entry from the virtqueue available ring
// If all entries have been read return INVALID_IDX
//
Uns16 getNextAvailEntry() {

    Uns16 availIndex;
    Uns16 entry;

    if (
        (readVirtq(AVAIL_IDX_OFFSET, sizeof(availIndex), &availIndex)) &&
        (availIndex != lastAvailSeen[selectedQueue]) &&
        (readVirtq(AVAIL_OFFSET(lastAvailSeen[selectedQueue]), sizeof(entry), &entry))
       ) {

       if (PSE_DIAG_HIGH) {
           bhmMessage(
               "I", PREFIX"_RVA",
               "Read Virtqueue Available[%d] = %d",
               lastAvailSeen[selectedQueue], entry
           );
       }

       lastAvailSeen[selectedQueue]++;
       return (entry);


    }

    return INVALID_IDX;
}

//
// Write the id and len to the next free entry in virtq used ring
//
Bool putNextUsedEntry(Uns32 descIndex, Uns32 len) {

    Uns16 usedIndex;

    if (readVirtq(USED_IDX_OFFSET, sizeof(usedIndex), &usedIndex)) {

        Uns16         freeEntry  = usedIndex % QUEUE_SIZE;
        Uns16         newFreeIdx = usedIndex + 1;
        virtqUsedElem used       = {.id = descIndex, .len = len};

        if (
            writeVirtq(USED_OFFSET(freeEntry), sizeof(used), &used) &&
            writeVirtq(USED_IDX_OFFSET, sizeof(newFreeIdx), &(newFreeIdx))
           ) {

            if (PSE_DIAG_HIGH) {
                bhmMessage(
                    "I", PREFIX"_WVU",
                    "Write Virtqueue Used[%d] <= id=%d, len=%d",
                    freeEntry, used.id, used.len
                );
            }

            return True;

        }
    }

    return False;
}

//
// Get virtio descriptor table[index]
//
Bool getVirtqDesc(Uns16 index, virtqDescP desc) {

    // Set current position to beginning
    desc->currentPos = 0;

    if (index != INVALID_IDX && readVirtq(DESC_OFFSET(index), DESC_SIZE, desc)) {

        if (PSE_DIAG_MEDIUM) {
            bhmMessage(
                "I", PREFIX"_DTE",
                "virtqDesc[%d]: Addr=%s, Len=%d, Pos=%d, Flags=0x%x, Next=%d",
                index,
                uns64ToString(desc->addr),
                desc->len,
                desc->currentPos,
                desc->flags,
                desc->next
            );
        }

        return True;

    }

    // Clear data if error
    desc->addr  = 0;
    desc->len   = 0;
    desc->flags = 0;
    desc->next  = 0;

    return False;

}

//
// return next desc index , or INVALID_IDX if end of list
//
static Uns16 nextDesc(virtqDescP desc) {
    return (desc->flags & VIRTQ_DESC_F_NEXT) ? desc->next : INVALID_IDX;
}

//
// Read data from a virtual queue buffer
//
Bool readVirtqBuffer(virtqDescP desc, Uns32 bytes, void *data) {

    while (bytes > 0) {

        Uns32 avail = desc->len - desc->currentPos;

        if (PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX"_BOR", "readVirtqBuffer() avail=%d, bytes=%d", avail,bytes); //Todo:
        }

        if (avail == 0 && !getVirtqDesc(nextDesc(desc), desc)) {
            bhmMessage("W", PREFIX"_BOR", "Buffer overflow on read");
            return False;
        }

        Uns32 this = (avail >= bytes) ? bytes : avail;

        if (!readSimMemory(desc->addr + desc->currentPos, this, data)) {
            bhmMessage(
                "W", PREFIX"_USM",
                "Unable to read %d bytes from simulated memory address %s",
                this, uns64ToString(desc->addr + desc->currentPos)
            );
            return False;
        }

        desc->currentPos += this;
        bytes            -= this;

    }

    return True;

}

//
// Write data to a virtual queue buffer
//
Bool writeVirtqBuffer(virtqDescP desc, Uns32 bytes, void *data) {

    while (bytes > 0) {

        Uns32 avail = desc->len - desc->currentPos;

        if (PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX"_WVQ", "Write queue buffer bytes=%d, len=%d, pos=%d",bytes,desc->len,desc->currentPos);
        }

        if ((avail==0) && !getVirtqDesc(nextDesc(desc), desc)) {
            bhmMessage("W", PREFIX"_BOW", "Buffer overflow on write, avail=%d",avail);
            return False;
        }

        if (!(desc->flags & VIRTQ_DESC_F_WRITE)) {
            bhmMessage("W", PREFIX"_WRO", "Write to read-only buffer");
            return False;
        }

        Uns32 this = (avail >= bytes) ? bytes : avail;

        if (!writeSimMemory(desc->addr + desc->currentPos, this, data)) {
            bhmMessage(
                "W", PREFIX"_USM",
                "Unable to write %d bytes to simulated memory address %s",
                this, uns64ToString(desc->addr + desc->currentPos)
            );
            return False;
        }

        desc->currentPos += this;
        bytes            -= this;

    }

    return True;

}

//
// check if queue's buffer contains a number of bytes
//
Bool bytesAvailVirtq(virtqDescP desc, Uns32 bytes) {

    Uns32 avail = desc->len - desc->currentPos;

    if (avail == 0) {
        // If this descr is used up move to the next
        // (avoids unnecessary duplicate reads for peeking)
        getVirtqDesc(nextDesc(desc), desc);
        avail = desc->len - desc->currentPos;
    }

    if (bytes <= avail) {

        // Current desc contains enough bytes
        return True;

    } else {

        // Peek ahead to see if there are enough bytes in descr chain
        virtqDesc peek = *desc;

        bytes -= avail;
        while (bytes!=0 && getVirtqDesc(nextDesc(&peek), &peek)) {

            avail = peek.len;

            if (bytes <= avail) {
                return True;
            }
            bytes -= avail;

        }
    }

    // Reached end of descriptor chain
    return False;

}

//
// position to last byte of a virtual queue
// return False if queue is already empty
//
Bool seekToEndVirtq(virtqDescP desc) {

    Uns16 next;

    // get to the last desc
    while ((next = nextDesc(desc)) != INVALID_IDX) {
        getVirtqDesc(next, desc);
    }

    if (desc->len <= desc->currentPos) {

        // Queue is empty
        return False;

    } else {

        // position to last byte in last descriptor
        desc->currentPos = desc->len - 1;

        return True;

    }

}
