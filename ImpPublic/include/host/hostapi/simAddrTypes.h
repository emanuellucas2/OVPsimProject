/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License Agreement
 * that you accepted before downloading this file.
 *
 * This header forms part of the Software but may be included and used unaltered
 * in derivative works.
 *
 * For more information, please visit www.OVPworld.org or www.imperas.com
 */

// Simulated address types

#ifndef SIMADDRTYPES_H
#define SIMADDRTYPES_H

#include "hostapi/impTypes.h"

#define MIN_ADDR          ((Addr)0)
#define MAX_ADDR          (MIN_ADDR-1)
#define MAX_ADDR_BITS(_B) ((_B)==ADDRESS_SIZE?MAX_ADDR:((((Addr)1)<<(_B))-1))
#define BITS_TO_BYTES(_B) (((_B)+7)/8)
#define BITS_TO_WORDS(_B) (((_B)+31)/32)

typedef union {Addr a; Uns32 u32[sizeof(Addr)/sizeof(Uns32)];} AddrToUns32;
typedef union {Addr a; UnsPS ups[sizeof(Addr)/sizeof(UnsPS)];} AddrToUnsPS;

#endif
