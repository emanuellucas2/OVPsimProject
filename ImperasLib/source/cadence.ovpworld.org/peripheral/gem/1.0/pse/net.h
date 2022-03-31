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

/*
 *  2014-03-31 - Initial version - Posedge Software, Inc.
 *
 */

#ifndef GEM_NET_H
#define GEM_NET_H

#ifdef _PSE_
#    include "peripheral/impTypes.h"
#else
#    include "hostapi/impTypes.h"
#endif


// IEEE 802.3 Ethernet constants

#ifndef ETH_ALEN

#define ETH_ALEN        6        // octets in one Ethernet addr
#define ETH_HLEN        14        // total octets in header
#define ETH_ZLEN        60        // min octets in frame (without FCS)
#define ETH_DATA_LEN    1500        // max octets in payload
#define ETH_FRAME_LEN   1514        // max octets in frame (without FCS)
#define ETH_FCS_LEN     4        // octets in the FCS

#endif

#ifndef ETHER_ADDR_LEN

#define    ETHER_ADDR_LEN  ETH_ALEN            // size of Ethernet addr
#define    ETHER_TYPE_LEN  2                // bytes in type field
#define    ETHER_CRC_LEN   4                // bytes in FCS field
#define    ETHER_HDR_LEN   ETH_HLEN            // total octets in header
#define    ETHER_MIN_LEN   (ETH_ZLEN + ETHER_CRC_LEN)    // min frame length
#define    ETHER_MAX_LEN   (ETH_FRAME_LEN + ETHER_CRC_LEN)    // max frame length

// Ethenet frame length check
#define    ETHER_IS_VALID_LEN(foo)    \
        (ETHER_MIN_LEN <= (foo) && (foo) <= ETHER_MAX_LEN)

#define ETH_IP_CRC_OFFSET 24
#define ETH_TCP_CRC_OFFSET 16
#define ETH_P_IP  0x0800        /* Internet Protocol packet  */
#define ETH_P_TCP 0x06

#endif


// MII (MDIO) definitions

#ifndef MII_BMCR

// Generic MII registers
#define    MII_BMCR                0x00        // Basic Mode Control Register
#define    MII_BMSR                0x01        // Basic Mode Status Register
#define    MII_PHYSID1             0x02        // PHYS ID 1
#define    MII_PHYSID2             0x03        // PHYS ID 2

// Basic Mode Status Register
#define BMSR_ERCAP              0x0001        // ext-reg capability
#define BMSR_JCD                0x0002        // jabber detected
#define BMSR_LSTATUS            0x0004        // link status
#define BMSR_ANEGCAPABLE        0x0008        // able to do auto-negotiation
#define BMSR_RFAULT             0x0010        // remote fault detected
#define BMSR_ANEGCOMPLETE       0x0020        // auto-negotiation complete
#define BMSR_ESTATEN            0x0100        // extended Status in R15
#define BMSR_100HALF2           0x0200        // can do 100BASE-T2 HDX
#define BMSR_100FULL2           0x0400        // can do 100BASE-T2 FDX
#define BMSR_10HALF             0x0800        // can do 10mbps, half-duplex
#define BMSR_10FULL             0x1000        // can do 10mbps, full-duplex
#define BMSR_100HALF            0x2000        // can do 100mbps, half-duplex
#define BMSR_100FULL            0x4000        // can do 100mbps, full-duplex
#define BMSR_100BASE4           0x8000        // can do 100mbps, 4k packets

#endif


// Endianness utility functions

static inline Uns16 byteSwap16(Uns16 data)
{
    return
        ((data & 0xff00) >>  8) |
        ((data & 0x00ff) <<  8);
}

static inline Uns32 byteSwap32(Uns32 data)
{
    return
        ((data & 0xff000000) >> 24) |
        ((data & 0x00ff0000) >>  8) |
        ((data & 0x0000ff00) <<  8) |
        ((data & 0x000000ff) << 24);
}

static inline Uns32 byteSwapReg(Uns32 data)
{
#ifdef ENDIANBIG
    return byteSwap32(data);
#else
    return data;
#endif
}

static inline Uns32 byteSwapDescWord(Uns32 data)
{
#if defined(ENDIANBIG) != defined(DESC_ENDIANREV)
    return byteSwap32(data);
#else
    return data;
#endif
}

#ifndef htonl
#    define htons(data)  byteSwap16(data)
#    define htonl(data)  byteSwap32(data)
#endif


#endif
