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
#include "vmi/vmiMessage.h"
#include "vmi/vmiRt.h"

// model header files
#include "or1kExceptionTypes.h"
#include "or1kFunctions.h"
#include "or1kStructure.h"
#include "or1kUtils.h"

//
// Read privilege exception handler callback function
//
VMI_RD_PRIV_EXCEPT_FN(or1kRdPrivExceptionCB) {
    if(MEM_AA_IS_TRUE_ACCESS(attrs)) {
        or1kP or1k = (or1kP)processor;
        or1k->EEAR = (Uns32)address;
        or1kTakeException(or1k, OR1K_EXCPT_DPF, 0);
    }
}

//
// Write privilege exception handler callback function
//
VMI_WR_PRIV_EXCEPT_FN(or1kWrPrivExceptionCB) {
    if(MEM_AA_IS_TRUE_ACCESS(attrs)) {
        or1kP or1k = (or1kP)processor;
        or1k->EEAR = (Uns32)address;
        or1kTakeException(or1k, OR1K_EXCPT_DPF, 0);
    }
}

//
// Read alignment exception handler callback function
//
VMI_RD_ALIGN_EXCEPT_FN(or1kRdAlignExceptionCB) {
    or1kP or1k = (or1kP)processor;
    or1k->EEAR = (Uns32)address;
    or1kTakeException(or1k, OR1K_EXCPT_BUS, 0);
    return 0;
}

//
// Write alignment exception handler callback function
//
VMI_WR_ALIGN_EXCEPT_FN(or1kWrAlignExceptionCB) {
    or1kP or1k = (or1kP)processor;
    or1k->EEAR = (Uns32)address;
    or1kTakeException(or1k, OR1K_EXCPT_BUS, 0);
    return 0;
}

//
// Arithmetic exception handler callback function
//
VMI_ARITH_EXCEPT_FN(or1kArithExceptionCB) {

    or1kP or1k = (or1kP)processor;

    switch(exceptionType) {

        // integer divide-by-zero and overflow should not generate exceptions
        // but instead set the carry flag
        case VMI_INTEGER_DIVIDE_BY_ZERO:
        case VMI_INTEGER_OVERFLOW:
            or1k->carryFlag = 1;
            return VMI_INTEGER_ABORT;

        // not expecting any other arithmetic exception types
        default:
            return VMI_INTEGER_UNHANDLED;
    }
}


