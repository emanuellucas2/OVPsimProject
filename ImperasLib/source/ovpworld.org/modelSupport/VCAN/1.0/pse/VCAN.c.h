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

#ifndef _BHMVCAN_INCLUDE_H_
#define _BHMVCAN_INCLUDE_H_

#include "peripheral/impTypes.h"
#include "peripheral/bhm.h"

#include "VCAN.h"

#define PREFIX "VCAN"

//void vcanInit(vcanP msg) {
//    memset(msg, 0, sizeof(vcan));
//    msg->frame.data.ack.bits.SLOT = 1;
//}

//
// Polynomial is
// P(X) = x15 + X14 + X10 + X8 + X7 + X4 + X3 + 1
// 1100 0101 1001 1001
//    C    5    9    9
//
static Uns16 vcanCalcCrc(Uns16 crc, Uns8 data)
{
    crc ^= (Uns16) data << 7;

    Uns8 i;
    for (i = 0; i < 8; i++) {
        crc <<= 1;
        if (crc & 0x8000) {
            crc ^= 0xC599;
        }
    }

    return crc & 0x7fff;
}

static void putbits(Uns32 data, Uns8 size) {
}

//
// All the bits from start of frame
// until just before the CRC sequence
//
void vcanInsertCrc(vcanP packet) {
    //
    // Determine packet type Data/Remote
    //
    Uns32 size = 0;
    // Start Of Frame ignore in putbits

    if (packet->frameType == DATA_REMOTE_FRAME_TYPE) {
        //
        // Data Frame
        //
        if (packet->frame.data.arb.bits.IDE==0) {
            //
            // Standard format frame
            // 11-bits ID, 1-bit RTR,
            // 1-bit-IDE
            // 1-bit r0
            size += 14;
            putbits(packet->frame.data.arb.bits.ID_28_18, 11);
            putbits(packet->frame.data.arb.bits.RTR,       1);
            putbits(packet->frame.data.arb.bits.IDE,       1);
            putbits(0,                                     1); // r0

        } else {
            //
            // Extended format frame
            // 29-bits ID, 1-bit SRR, 1-bit RTR, 1-bit-IDE
            // 1-bit r1, 1-bit r0
            size += 34;
            putbits(packet->frame.data.arb.bits.ID_28_18, 11);
            putbits(packet->frame.data.arb.bits.SRR,       1);
            putbits(packet->frame.data.arb.bits.IDE,       1);
            putbits(packet->frame.data.arb.bits.ID_17_00, 18);
            putbits(packet->frame.data.arb.bits.RTR,       1);
            putbits(0,                                     2); // r1, r0

        }

        //
        // CTRL
        //
        size += 4;
        putbits(packet->frame.data.ctrl.bits.DLC, 4);

        //
        // DATA Packet
        //
        Uns8 datasize = packet->frame.data.ctrl.bits.DLC;
        if (packet->frame.data.arb.bits.RTR==0) {
            size += (datasize * 8); // Data Bytes

            Uns8 i;
            for (i=0; i<datasize; i++) {
                putbits(packet->frame.data.data.b[i], 8);
            }
        }

    } else {
        bhmMessage("W", "VCAN_CRC", "Cannot generate CRC for Frames of type ERROR or OVERLOAD");

    }

    int i;
    Uns8  data[] = { 0x02, 0xAA, 0x80 };
    Uns16 crc;

    crc = 0;

    for (i = 0; i < sizeof(data); i++) {
        crc = vcanCalcCrc(crc, data[i]);
    }

    packet->frame.data.crc.bits.CRC = crc;
}

#endif // _BHMVCAN_INCLUDE_H_
