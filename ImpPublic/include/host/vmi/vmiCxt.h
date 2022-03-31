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
#include "vmi/vmiTyperefs.h"


////////////////////////////////////////////////////////////////////////////////
// CPU-MODEL-TO-CONTEXT CALLBACKS
////////////////////////////////////////////////////////////////////////////////

//
// Utility functions for 1, 2, 4 and 8 byte code fetches from the passed address
// The result is read using the current processor endianness
//
Uns8  vmicxtFetch1Byte(vmiProcessorP processor, Addr simAddress);
Uns16 vmicxtFetch2Byte(vmiProcessorP processor, Addr simAddress);
Uns32 vmicxtFetch4Byte(vmiProcessorP processor, Addr simAddress);
Uns64 vmicxtFetch8Byte(vmiProcessorP processor, Addr simAddress);

//
// Fetch an instruction at the given address using the processor-specific
// fetch callback. If successful, the function returns the number of bytes
// fetched and fills by-ref parameter 'value' with the fetched bytes; otherwise,
// zero is returned.
//
Uns32 vmicxtFetch(vmiProcessorP processor, Addr simAddress, void *value);

