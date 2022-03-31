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

#include "vmi/vmiMessage.h"
#include "vmi/vmiRt.h"
#include "ppc32Exceptions.h"
#include "ppc32Functions.h"
#include "ppc32Instructions.h"
#include "ppc32Structure.h"
#include "ppc32SPR.h"
#include "ppc32SPR_isa.h"

VMI_RD_PRIV_EXCEPT_FN(ppc32RdPrivExcept) {
    ppc32P ppc32 = (ppc32P)processor;
    ppc32->exception = ppc32_E_RdPriv;
    vmiMessage("F", "PRIV", "ppc32RdPrivExcept Address=0x%08x", (Uns32)address);
}

VMI_WR_PRIV_EXCEPT_FN(ppc32WrPrivExcept) {
    ppc32P ppc32 = (ppc32P)processor;
    ppc32->exception = ppc32_E_WrPriv;
    vmiMessage("F", "PRIV", "ppc32WrPrivExcept Address=0x%08x", (Uns32)address);
}

VMI_RD_ALIGN_EXCEPT_FN(ppc32RdAlignExcept) {
    ppc32P ppc32 = (ppc32P)processor;
    ppc32->exception = ppc32_E_RdAlign;
    vmiMessage("F", "ALIGN", "ppc32RdAlignExcept Address=0x%08x", (Uns32)address);
    return 0;
}

VMI_WR_ALIGN_EXCEPT_FN(ppc32WrAlignExcept) {
    ppc32P ppc32 = (ppc32P)processor;
    ppc32->exception = ppc32_E_WrAlign;
    vmiMessage("F", "ALIGN", "ppc32WrAlignExcept Address=0x%08x", (Uns32)address);
    return 0;
}

VMI_RD_ABORT_EXCEPT_FN(ppc32RdAbortExcept) {
    ppc32P ppc32 = (ppc32P)processor;
    ppc32->exception = ppc32_E_RdAbort;
    vmiMessage("F", "ABORT", "ppc32RdAbortExcept Address=0x%08x", (Uns32)address);
}

VMI_WR_ABORT_EXCEPT_FN(ppc32WrAbortExcept) {
    ppc32P ppc32 = (ppc32P)processor;
    ppc32->exception = ppc32_E_WrAbort;
    vmiMessage("F", "ABORT", "ppc32WrAbortExcept Address=0x%08x", (Uns32)address);
}

VMI_ARITH_EXCEPT_FN(ppc32ArithExcept) {
    ppc32P ppc32 = (ppc32P)processor;

    switch(exceptionType) {
        // integer divide-by-zero and overflow should not generate exceptions
        // but instead set various flags
        case VMI_INTEGER_DIVIDE_BY_ZERO:
            switch (ppc32->TEMP[1]) {
                case 0: // FLAGUPDATE_NONE
                    break;

                case 2: // FLAGUPDATE_RC
                    //
                    // CR Flags
                    //
                    ppc32->LT[0] = 0;
                    ppc32->GT[0] = 0;
                    ppc32->EQ[0] = 1;
                    ppc32->SO[0] = ppc32->XER_SO;
                    break;

                case 1: // FLAGUPDATE_OE
                    //
                    // XER Flags
                    //
                    ppc32->XER_OV = 1;
                    ppc32->XER_SO = 1;
                    break;

                case 3: // FLAGUPDATE_OERC
                    //
                    // XER Flags
                    //
                    ppc32->XER_OV = 1;
                    ppc32->XER_SO = 1;

                    //
                    // CR Flags
                    //
                    ppc32->LT[0] = 0;
                    ppc32->GT[0] = 0;
                    ppc32->EQ[0] = 1;
                    ppc32->SO[0] = ppc32->XER_SO;
                    break;
            }
            return VMI_INTEGER_ABORT;

        case VMI_INTEGER_OVERFLOW:
            ppc32->TEMP[0] = 1;
            return VMI_INTEGER_CONTINUE;

        // not expecting any other arithmetic exception types
        default:
            vmiPrintf("VMI_INTEGER_UNHANDLED\n");
            return VMI_INTEGER_UNHANDLED;
    }
}

VMI_FP_ARITH_EXCEPT_FN(ppc32FPArithExcept) {
    return VMI_FLOAT_UNHANDLED;
}

VMI_IFETCH_FN(ppc32IfetchExcept) {
    ppc32P ppc32 = (ppc32P)processor;
    ppc32->exception = ppc32_E_Fetch;
    return VMI_FETCH_NONE;
}

VMI_ICOUNT_FN(ppc32IcountExcept) {
}

//
// Table of exception mode descriptors
//
static const vmiExceptionInfo exceptions[] = {
    { "Reset",    ppc32_E_Reset     },
    { "Undefined",ppc32_E_Undefined },
    { "Arith",    ppc32_E_Arith     },
    { "RdAlign",  ppc32_E_RdAlign   },
    { "WrAlign",  ppc32_E_WrAlign   },
    { "RdAbort",  ppc32_E_RdAbort   },
    { "WrAbort",  ppc32_E_WrAbort   },
    { "RdPriv",   ppc32_E_RdPriv    },
    { "WrPriv",   ppc32_E_WrPriv    },
    { "Fetch",    ppc32_E_Fetch     },
    { 0 }
};

VMI_GET_EXCEPTION_FN(ppc32GetException) {
    ppc32P ppc32 = (ppc32P)processor;
    return &exceptions[ppc32->exception];
}

VMI_EXCEPTION_INFO_FN(ppc32ExceptionInfo) {

    // on the first call, start with the first member of the table
    if(!prev) {
        return exceptions;
    }
    prev++;
    return prev->name ? prev : 0;
}

VMI_FETCH_SNAP_FN(ppc32FetchSnap) {
    return thisPC;
}

VMI_RD_WR_SNAP_FN(ppc32RdSnap) {
    return MEM_SNAP(1, 0);
}

VMI_RD_WR_SNAP_FN(ppc32WrSnap) {
    return MEM_SNAP(1, 0);
}

void ppc32ProcessException (vmiProcessorP processor, Addr address, Uns64 exc) {
}
