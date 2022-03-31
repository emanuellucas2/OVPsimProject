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

#ifdef _PSE_
#    include "peripheral/impTypes.h"
#else
#    include "hostapi/impTypes.h"
#endif

//
// VIRTIO Virtual Queue Descriptor Flags
//
// This marks a buffer as continuing via the next field
#define VIRTQ_DESC_F_NEXT 1
// This marks a buffer as device write-only (otherwise device read-only)
#define VIRTQ_DESC_F_WRITE 2
// This means the buffer contains a list of buffer descriptors
#define VIRTQ_DESC_F_INDIRECT 4

typedef struct virtq_desc {
    Addr  addr;         // Address in simulated memory of buffer
    Uns32 len;          // Length
    Uns16 flags;        // VIRTIO Virtual Queue Descriptor Flags
    Uns16 next;         // Next field when VIRTQ_DESC_F_NEXT set
    Uns32 currentPos;   // Current position in buffer
} virtqDesc, *virtqDescP;

#define INVALID_IDX ((Uns16) -1)

//
// Select the currently active virtq
// The value of select must be between 0 and MAX_NUM_QUEUES
//
void selectVirtq(Uns32 select);

//
// Set the virtqBase address
// When set to 0 also reset the lastAvailSeen value
//
void setVirtqBase(Addr base);

//
// Get virtual queue descriptor table[index]
//
Bool getVirtqDesc(Uns16 index, virtqDescP desc);

//
// Read the next unread entry from the virtqueue available ring
// If all entries have been read return INVALID_IDX
//
Uns16 getNextAvailEntry();

//
// Write the descIndex and len to the next free entry in virtq used ring
//
Bool putNextUsedEntry(Uns32 descIndex, Uns32 len);

//
// Read data from a virtual queue buffer
//
Bool readVirtqBuffer(virtqDescP desc, Uns32 bytes, void *data);

//
// Write data to a virtual queue buffer
//
Bool writeVirtqBuffer(virtqDescP desc, Uns32 bytes, void *data);

//
// check if virtqueue buffer contains a number of bytes
//
Bool bytesAvailVirtq(virtqDescP desc, Uns32 bytes);

//
// position to last byte of a virtual queue
// return False if queue is already empty
//
Bool seekToEndVirtq(virtqDescP desc);
