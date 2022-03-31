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

#ifndef _VCAN_H_
#define _VCAN_H_

#include "peripheral/impTypes.h"

typedef enum {
    DATA_REMOTE_FRAME_TYPE,
    ERROR_FRAME_TYPE,
    OVERLOAD_FRAME_TYPE
} VC_FRAME;

typedef union {
    Uns32 reg;
    struct {
        Uns32 ID_28_18 : 11;    // Standard format mode ID
        Uns32      SRR : 1;     // 1=(Extended format mode)
        Uns32      IDE : 1;     // 0=(Standard format mode), 1=(Extended format mode)
        Uns32 ID_17_00 : 18;    // Extended format mode ID
        Uns32      RTR : 1;     // 0=(Data Frame), 1=(Remote Frame)
    } bits;
} VC_ARB;

typedef union {
    Uns8 reg;
    struct {
        Uns8      DLC : 4;     // Number of Bytes
    } bits;
} VC_CTRL;

typedef union {
    Uns16 reg;
    struct {
        Uns16     CRC : 15;
        Uns16   DELIM : 1;
    } bits;
} VC_CRC;

typedef union {
    Uns8 reg;
    struct {
        Uns8    SLOT : 1;
        Uns8   DELIM : 1;
    } bits;
} VC_ACK;

typedef struct {
    VC_ARB     arb;        // Arbitration Field (standard/Extended)
    VC_CTRL    ctrl;       // Control Field, Data Length
    VC_CRC     crc;        // CRC - Caclulation of Frame CRC
    VC_ACK     ack;        // Ack Field - Set by Target receiving data
    union {
        Uns32  w[2];        // data field words
        Uns8   b[8];        // Data Field - variable between 0 - 8
    } data;
} VC_DATA_REMOTE_FRAME;

typedef union {
    Uns32 reg;
    struct {
        Uns32    FLAG1 : 6;
        Uns32    FLAG2 : 6;
        Uns32    DELIM : 8;
    } bits;
} VC_ERROR_FRAME;

typedef union {
    Uns32 reg;
    struct {
        Uns32    FLAGN : 6;
        Uns32    FLAGM : 6;
        Uns32    DELIM : 8;
    } bits;
} VC_OVERLOAD_FRAME;

//
// Can Message Identifier
//
typedef struct vcanS {
    VC_FRAME    frameType;                  // Type of frame, Data, Remote, Error, Overload
    union {
        VC_DATA_REMOTE_FRAME   data;        // Data Frame
        VC_ERROR_FRAME         error;       // Error Frame
        VC_OVERLOAD_FRAME      overload;    // Overload Frame
    } frame;
    Bool        ack;                        // Acknowledge that a packet received
} vcan, *vcanP;

//
// Function Prototypes
//
void vcanInit(vcanP msg) {
    memset(msg, 0, sizeof(vcan));
    msg->frame.data.ack.bits.SLOT = 1;
}

void vcanInsertCrc(vcanP msg);

#endif  // _VCAN_H_
