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
#include "ppc32MorphFP.h"
#include "ppc32SPR.h"
#include "ppc32SPR_400.h"

#define TRC 0

VMI_RD_PRIV_EXCEPT_FN(ppc32RdPrivExcept) {
    ppc32P ppc32 = (ppc32P)processor;
    ppc32->exception = ppc32_E_RdPriv;
    vmiMessage("F", "PRIV", "ppc32RdPrivExcept");
}

VMI_WR_PRIV_EXCEPT_FN(ppc32WrPrivExcept) {
    ppc32P ppc32 = (ppc32P)processor;
    ppc32->exception = ppc32_E_WrPriv;
    vmiMessage("F", "PRIV", "ppc32WrPrivExcept");
}

VMI_RD_ALIGN_EXCEPT_FN(ppc32RdAlignExcept) {
    ppc32P ppc32 = (ppc32P)processor;
    ppc32->exception = ppc32_E_RdAlign;

    ppc32->FLG_ST = 0;
    ppc32ProcessException(processor, address, EXC_ALIGNMENT);

    return 0;
}

VMI_WR_ALIGN_EXCEPT_FN(ppc32WrAlignExcept) {
    ppc32P ppc32 = (ppc32P)processor;
    ppc32->exception = ppc32_E_WrAlign;

    ppc32->FLG_ST = 1;
    ppc32ProcessException(processor, address, EXC_ALIGNMENT);

    return 0;
}

VMI_RD_ABORT_EXCEPT_FN(ppc32RdAbortExcept) {
    ppc32P ppc32 = (ppc32P)processor;
    ppc32->exception = ppc32_E_RdAbort;
    vmiMessage("F", "ABORT", "ppc32RdAbortExcept");
}

VMI_WR_ABORT_EXCEPT_FN(ppc32WrAbortExcept) {
    ppc32P ppc32 = (ppc32P)processor;
    ppc32->exception = ppc32_E_WrAbort;
    vmiMessage("F", "ABORT", "ppc32WrAbortExcept");
}

static vmiFloatExceptionResult ppc32HandleFPexceptions (ppc32P ppc32, vmiFPFlagsP flags) {

    vmiFloatExceptionResult result;

//    vmiFBinop       fbinOp = (ppc32->FPU_OP >>  8) & 0xff;
//    vmiFUnop         funOp = (ppc32->FPU_OP >>  8) & 0xff;
    ppc32fpuOpTypeE  fpuOp = (ppc32->FPU_OP >>  0) & 0xff;

    Uns8 FE = (ppc32->SPR->MSR.bits.FE0 << 1) | ppc32->SPR->MSR.bits.FE1;
#if (TRC==1)
    vmiPrintf("VMI_ARITH_EXCEPT_FN / VMI_FLOAT_EXCEPTION\n");
    vmiPrintf("FE=%d\n",FE);
    vmiPrintf("invalid operation flag I = %d\n", flags->f.I);
    vmiPrintf("denormal          flag D = %d\n", flags->f.D);
    vmiPrintf("divide-by-zero    flag Z = %d\n", flags->f.Z);
    vmiPrintf("overflow          flag O = %d\n", flags->f.O);
    vmiPrintf("underflow         flag U = %d\n", flags->f.U);
    vmiPrintf("precision         flag P = %d\n", flags->f.P);
#endif

    //
    // Inexact / Precision exception
    //
    result = VMI_FLOAT_UNHANDLED;
    if (flags->f.I) {
        switch(fpuOp) {
        case FPUOP_BinopRRR:
            ppc32->FPU_REL = 0;
            result = VMI_FLOAT_CONTINUE;
            break;
        default:
            break;
        }
    } else if (flags->f.D) {
    } else if (flags->f.Z) {
    } else if (flags->f.O) {
    } else if (flags->f.U) {
    } else if (flags->f.P) {
    }

    //
    // Exception Action
    //
    switch (FE) {
    case 0:
        //
        // Ignore Exceptions Mode
        //
        break;
    case 1:
        //
        // Imprecise Nonrecoverable Mode
        //
    case 2:
        //
        // Imprecise Recoverable Mode
        //
    case 3:
        //
        // Precise Mode
        //
        vmiMessage("F", "UNHANDLED", "FE MODE");
        break;
    }

    //
    // Try all possibilities
    //
    result = VMI_FLOAT_CONTINUE;
#if (TRC==1)
    vmiPrintf("return result = %d\n", result);
#endif
    return result;
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
            vmiPrintf("VMI_INTEGER_default\n");
            return VMI_INTEGER_UNHANDLED;
    }
}

VMI_FP_ARITH_EXCEPT_FN(ppc32FPArithExcept) {
    ppc32P ppc32 = (ppc32P)processor;

    return ppc32HandleFPexceptions(ppc32, flags);
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
    ppc32P ppc32 = (ppc32P)processor;

    //
    // Test CCR0[DLSTM], CCR0[DLSTS], CCR0[FLSTA]
    //

    //
    // What type of instruction generated this alignment check
    // Floating Point or Integer ?
    //
    if (ppc32->FLG_FP_LDST) {
    } else {
        //
        // Load instruction
        //
        if (ppc32->SPR->CCR0.bits.FLSTA == 0) {
            //
            // Force Load Store Alignment, disabled
            //
            return MEM_SNAP(1, 0);
        }
    }
    return 0;
}

VMI_RD_WR_SNAP_FN(ppc32WrSnap) {
    ppc32P ppc32 = (ppc32P)processor;

    //
    // Test CCR0[DLSTM], CCR0[DLSTS], CCR0[FLSTA]
    //

    //
    // What type of instruction generated this alignment check
    // Floating Point or Integer ?
    //
    if (ppc32->FLG_FP_LDST) {
    } else {
        //
        // Load instruction
        //
        if (ppc32->SPR->CCR0.bits.FLSTA == 0) {
            //
            // Force Load Store Alignment, disabled
            //
            return MEM_SNAP(1, 0);
        }
    }
    return 0;
}

static void commonExcept(ppc32P ppc32, Addr rfiaddr, Uns32 IVOR) {
    vmiProcessorP processor = (vmiProcessorP) ppc32;

    //
    // Calculate the Vector Address = IVPR | IVORxx
    //
    Addr vectorPC = ppc32->SPR->IVPR.reg | IVOR;

    //
    // Save PC -> SRR0
    //
    ppc32->SPR->SRR0.reg = rfiaddr;

    //
    // Save MSR -> SRR1
    //
    ppc32->SPR->SRR1.reg = ppc32->SPR->MSR.reg;

    //
    // Reset MSR - except CE, ME, DE
    //
    TYPE_MSR MSR = ppc32->SPR->MSR;
    ppc32->SPR->MSR.reg = 0;
    ppc32->SPR->MSR.bits.CE = MSR.bits.CE;
    ppc32->SPR->MSR.bits.ME = MSR.bits.ME;
    ppc32->SPR->MSR.bits.DE = MSR.bits.DE;

    //
    // Vector Address
    //
    vmirtSetPCException(processor, vectorPC);
}

static void printExceptionInfo(vmiProcessorP processor, char *exc_info) {
#if (TRC==1)
    vmiPrintf("Exception: %s\n", exc_info);
#endif
}

//
// exception routines
//
void ppc32ProcessException (vmiProcessorP processor, Addr address, Uns64 exc) {
    ppc32P ppc32 = (ppc32P)processor;

    Bool handled = False;

    //
    // Priority encoder ref 5.8.2, Interrupt Order
    //

    //
    // Synchronous interrupts
    //
    if        (exc & EXC_DATA_STORAGE) {
        printExceptionInfo(processor, "EXC_DATA_STORAGE");

    } else if (exc & EXC_INSTRUCTION_STORAGE) {
        printExceptionInfo(processor, "EXC_INSTRUCTION_STORAGE");

    } else if (exc & EXC_ALIGNMENT) {
        printExceptionInfo(processor, "EXC_ALIGNMENT");

        handled = True;
        commonExcept(ppc32, vmirtGetPC(processor), ppc32->SPR->IVOR5);

        //
        // Save the Load address to DEAR
        //
        ppc32->SPR->DEAR = address;

        //
        // ESR = FP, ST or AP
        //
        ppc32->SPR->ESR.reg = 0;
        ppc32->SPR->ESR.bits.FP = ppc32->FLG_FP_LDST;
        ppc32->SPR->ESR.bits.ST = ppc32->FLG_ST;
        ppc32->SPR->ESR.bits.AP = 0;

        //
        // Clear Flags set in Morpher for alignment check
        //
        ppc32->FLG_FP_LDST = 0;
        ppc32->FLG_ST = 0;

    } else if (exc & EXC_PROGRAM) {
        printExceptionInfo(processor, "EXC_PROGRAM");

    } else if (exc & EXC_FLOATING_POINT_UNAVAILABLE) {
        printExceptionInfo(processor, "EXC_FLOATING_POINT_UNAVAILABLE");

        handled = True;
        commonExcept(ppc32, address, ppc32->SPR->IVOR7);

    } else if (exc & EXC_AUXILLIARY_PROCESSOR_UNAVAILABLE) {
        printExceptionInfo(processor, "EXC_AUXILLIARY_PROCESSOR_UNAVAILABLE");

    } else if (exc & EXC_SPE_FP_VECTOR_UNAVAILABLE) {
        printExceptionInfo(processor, "EXC_SPE_FP_VECTOR_UNAVAILABLE");

    } else if (exc & EXC_FP_DATA_INTERRUPT) {
        printExceptionInfo(processor, "EXC_FP_DATA_INTERRUPT");

    } else if (exc & EXC_FP_ROUND_INTERRUPT) {
        printExceptionInfo(processor, "EXC_FP_ROUND_INTERRUPT");

    } else if (exc & EXC_SYSTEM_CALL) {
        printExceptionInfo(processor, "EXC_SYSTEM_CALL");

        handled = True;
        commonExcept(ppc32, ppc32nextPC(processor, address), ppc32->SPR->IVOR8);

    } else if (exc & EXC_DATA_TLB_ERROR) {
        printExceptionInfo(processor, "EXC_DATA_TLB_ERROR");

    } else if (exc & EXC_INSTRUCTION_TLB_ERROR) {
        printExceptionInfo(processor, "EXC_INSTRUCTION_TLB_ERROR");

    //
    // Asynchronous interrupts
    //
    } else if (exc & EXC_MACHINE_CHECK) {
        printExceptionInfo(processor, "EXC_MACHINE_CHECK");

    } else if (exc & EXC_DEBUG) {
        printExceptionInfo(processor, "EXC_DEBUG");

    } else if (exc & EXC_CRITICAL_INPUT) {
        printExceptionInfo(processor, "EXC_CRITICAL_INPUT");

    } else if (exc & EXC_WATCHDOG_TIMER) {
        printExceptionInfo(processor, "EXC_WATCHDOG_TIMER");

    } else if (exc & EXC_PROCESSOR_DOORBELL_CRITICAL) {
        printExceptionInfo(processor, "EXC_PROCESSOR_DOORBELL_CRITICAL");

    } else if (exc & EXC_EXTERNAL) {
        printExceptionInfo(processor, "EXC_EXTERNAL");

    } else if (exc & EXC_FIXED_INTERVAL_TIMER) {
        printExceptionInfo(processor, "EXC_FIXED_INTERVAL_TIMER");

    } else if (exc & EXC_DECREMENTER) {
        printExceptionInfo(processor, "EXC_DECREMENTER");

    } else if (exc & EXC_PROCESSOR_DOORBELL) {
        printExceptionInfo(processor, "EXC_PROCESSOR_DOORBELL");

    } else if (exc & EXC_PERFORMANCE_MONITOR) {
        printExceptionInfo(processor, "EXC_PERFORMANCE_MONITOR");

    }

    //
    // If we did not handle the exception - something has gone wrong
    //
    if (!handled) {
        vmiMessage("F", "UNEXP", "ppc32ProcessException exc=" FMT_640Nx, exc);
    }
}
