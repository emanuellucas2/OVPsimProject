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

#pragma once

#include "hostapi/simAddrTypes.h"
#include "vmi/vmiTypes.h"

//
// Allocate a new decode table object to decode instructions 'bits' wide ('bits'
// is currently restricted to 8, 16 or 32 only)
//
vmidDecodeTableP vmidNewDecodeTable(Uns32 bits, Uns32 defaultValue);

//
// Add a new entry to the decode table. 'mask' is a bitmask which is applied to
// a candidate instruction, and 'value' is compared with the masked value. If
// the masked value matches, 'matchValue' is returned.
//
// Sometimes it is required to create conflicting decode entries in a table
// (for example, a particular instruction variant may have a different
// mnemonic or special functionality different to the general case). In such
// cases, use the 'priority' argument to specify which of the conflicting
// decodes should be used (larger 'priority' value are chosen in preference)
//
Bool vmidNewEntry(
    vmidDecodeTableP table,
    const char      *name,
    Uns32            matchValue,
    Uns64            mask,
    Uns64            value,
    Int32            priority
);

//
// Add a new entry to the decode table using a format string, which describes
// the bit pattern of an opcode from MSB to LSB. The characters in the string
// are as follows:
//
//      '1': corresponding bit must be 1
//      '0': corresponding bit must be 0
//      '|', ',', '/', ' ', tab: ignored
//      any other character: corresponding bit can be either 0 or 1
//
// As an example, this format string specifies a 16-bit opcode with the
// most-significant 5 bits and least-significant 3 bits having fixed values,
// with other bit values unconstrained. Note that the spacer character '|' is
// ignored, and the value '.' is used in this case to denote an unconstrained
// bit value:
//
//      "|10001|........|101|"
//
Bool vmidNewEntryFmtBin(
    vmidDecodeTableP table,
    const char      *name,
    Uns32            matchValue,
    const char      *format,
    Int32            priority
);

//
// Decode the passed instruction using the decode table, returning the
// matchValue registered with the matching entry (or defaultValue registered
// with the table if no entry matches)
//
Uns32 vmidDecode(vmidDecodeTableP table, Uns64 instr);

//
// If this value is specified as a priority then the priority is derived
// automatically from the number of non-zero bits in the mask, or 0 and 1 bits
// in the format string, depending which API call is used
//
#define VMID_DERIVE_PRIORITY 0x80000000


