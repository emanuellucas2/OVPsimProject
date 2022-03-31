/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */


// VMI header files
#include "vmi/vmiAttrs.h"
#include "vmi/vmiMt.h"

// model header files
#include "or1kFunctions.h"
#include "or1kStructure.h"


//
// Morph return from an opaque intercepted function
//
VMI_INT_RETURN_FN(or1kIntReturnCB) {
    vmimtUncondJumpReg(0, OR1K_REG(OR1K_LINK), VMI_NOREG, vmi_JH_RETURN);
}

