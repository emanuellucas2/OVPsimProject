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

// basic types
#include "hostapi/simAddrTypes.h"

// Imperas common library includes
#include "ocl/ocliaTypes.h"

// VMI types
#include "vmi/vmiTypes.h"


//
// Return instruction attribute object for the instruction at the given
// simulated address. Data gathered is chosen by the 'select' bit field
// enumeration. 'applyDFA' specifies whether data flow optimization should be
// performed before deriving attributes (may result in elimination of some
// apparent dependencies).
//
octiaAttrP vmiiaGetAttrs(
    vmiProcessorP   processor,
    Addr            simPC,
    octiaDataSelect select,
    Bool            applyDFA
);

//
// Return equivalent vmiRegInfoCP for octiaRegInfoP
//
vmiRegInfoCP vmiiaConvertRegInfo(octiaRegInfoP regInfo);



