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
#include "or1kExceptions.h"
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


////////////////////////////////////////////////////////////////////////////////
// HANDLING PENDING EXCEPTIONS
////////////////////////////////////////////////////////////////////////////////

//
// Is there a pending tick timer interrupt?
//
inline static Uns32 isTEEPending(or1kP or1k) {
    return (or1k->TTMR_IP && or1k->TTMR_IE);
}

//
// Are tick timer interrupts enabled?
//
inline static Bool isTEEEnabled(or1kP or1k) {
    return (or1k->SR & SPR_SR_TEE);
}

//
// Should a tick timer interrupt be taken?
//
inline static Uns32 takeTEE(or1kP or1k) {
    return isTEEPending(or1k) && isTEEEnabled(or1k);
}

//
// Ensure any pending interrupt is taken before the next instruction
//
void or1kInterruptNext(or1kP or1k) {

    if(takeTEE(or1k)) {
        vmirtDoSynchronousInterrupt((vmiProcessorP)or1k);
    }
}

//
// Handler for fetch exceptions - this should ensure any exceptions pending
// before an instruction is executed are taken.
//
VMI_IFETCH_FN(or1kIFetchExceptionCB) {

    or1kP or1k = (or1kP)processor;

    if(takeTEE(or1k)) {

        // tick timer interrupt must be taken
        if(complete) {
            or1kTakeException(or1k, OR1K_EXCPT_TTI, 0);
            return VMI_FETCH_EXCEPTION_COMPLETE;
        } else {
            return VMI_FETCH_EXCEPTION_PENDING;
        }

    } else if(address & 3) {

        // handle misaligned fetch exception
        if(complete) {
            or1k->EEAR = (Uns32)address;
            or1kTakeException(or1k, OR1K_EXCPT_BUS, 0);
            return VMI_FETCH_EXCEPTION_COMPLETE;
        } else {
            return VMI_FETCH_EXCEPTION_PENDING;
        }

    } else if(!vmirtIsExecutable(processor, address)) {

        // handle execute privilege exception
        if(complete) {
            or1k->EEAR = (Uns32)address;
            or1kTakeException(or1k, OR1K_EXCPT_IPF, 0);
            return VMI_FETCH_EXCEPTION_COMPLETE;
        } else {
            return VMI_FETCH_EXCEPTION_PENDING;
        }

    } else {

        // no fetch exception
        return VMI_FETCH_NONE;
    }
}


////////////////////////////////////////////////////////////////////////////////
// TICK TIMER
////////////////////////////////////////////////////////////////////////////////

//
// values for TTMR_M mode bits
//
typedef enum TTMRmodeE {
    TTMR_DISABLED = 0,  //  TTCR does not run
    TTMR_RESTART  = 1,  //  TTCR counts up until TTMR_TP, then restarts at 0
    TTMR_ONCE     = 2,  //  TTCR counts up until TTMR_TP, then stops
    TTMR_FREE     = 3   //  TTCR counts up, overflowing at max
} TTMRmode;

//
// Return lower 32 bits of the OR1K instruction count
//
inline static Uns32 getThisICount(or1kP or1k) {
    return (Uns32)vmirtGetICount((vmiProcessorP)or1k);
}

//
// Return the TTCR register
//
inline static Uns32 getTTCR(or1kP or1k) {
    if(or1k->timerRunning) {
        return or1k->TTCR - or1k->TTCRSetCount + getThisICount(or1k);
    } else {
        return or1k->TTCR;
    }
}

//
// Set the TTCR register
//
static void setTTCR(or1kP or1k, Uns32 TTCR) {

    // update fields dependent on TTCR
    or1k->TTCR         = TTCR;
    or1k->TTCRSetCount = getThisICount(or1k);

    // if the timer is running, calculate the cycle delay to any interrupt
    // (28 bits maximum) and schedule timer interrupt
    if(or1k->timerRunning) {
        Uns32 iCount = (or1k->TTMR_TP-TTCR-1) & 0xfffffff;
        vmirtSetICountInterrupt((vmiProcessorP)or1k, iCount);
    } else {
        vmirtClearICountInterrupt((vmiProcessorP)or1k);
    }
}

//
// Return the TTCR register
//
Uns32 or1kGetTTCR(or1kP or1k) {
    return getTTCR(or1k);
}

//
// Set the TTCR register
//
void or1kSetTTCR(or1kP or1k, Uns32 TTCR) {

    // restart the timer if mode is TTMR_ONCE
    if(or1k->TTMR_M==TTMR_ONCE) {
        or1k->timerRunning = True;
    }

    setTTCR(or1k, TTCR);
}

//
// Set the TTMR register
//
void or1kSetTTMR(or1kP or1k, Uns32 TTMR) {

    Uns32 TTCR = getTTCR(or1k);

    // update TTMR, recording old and new values of TTMR_IP
    Bool oldIP = or1k->TTMR_IP;
    or1k->TTMR = TTMR;
    Bool newIP = or1k->TTMR_IP;

    // TTMR_IP must not be set by l.mtspr!
    if(!oldIP && newIP) {
        or1k->TTMR_IP = 0;
    }

    // start the timer if mode is TTMR_RESTART or TTMR_FREE
    // (for TTMR_ONCE, timer is restarted by write to TTCR)
    if((or1k->TTMR_M==TTMR_RESTART) || (or1k->TTMR_M==TTMR_FREE)) {
        or1k->timerRunning = True;
    }

    setTTCR(or1k, TTCR);
}

//
// This is called when the tick timer has expired. It should set the interrupt
// pending bit for this exception and return a boolean indicating whether the
// exception is enabled. The exception is subsequently handled in the
// instruction fetch handler, or1kIFetchExceptionCB.
//
VMI_ICOUNT_FN(or1kICountPendingCB) {

    or1kP or1k = (or1kP)processor;

    switch(or1k->TTMR_M) {

        case TTMR_RESTART:
            // restart the timer from 0 on the NEXT instruction
            setTTCR(or1k, -1);
            break;

        case TTMR_FREE:
            // schedule the next interrupt event
            setTTCR(or1k, getTTCR(or1k));
            break;

        case TTMR_ONCE:
            // stop the timer on the NEXT instruction count
            or1k->TTCR         = (getTTCR(or1k)+1) & 0xfffffff;
            or1k->timerRunning = False;
            break;

        case TTMR_DISABLED:
            // how did we get here?
            VMI_ABORT("timer interrupt, but timer was disabled");
            break;
    }

    // if interrupt generation is enabled, set TTMR_IP
    if(or1k->TTMR_IE) {
        or1k->TTMR_IP = 1;
    }

    // handle exception if required
    if(takeTEE(or1k)) {
        vmirtDoSynchronousInterrupt(processor);
    }
}

