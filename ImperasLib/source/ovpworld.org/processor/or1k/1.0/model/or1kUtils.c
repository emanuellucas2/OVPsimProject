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

// VMI header files
#include "vmi/vmiDbg.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiRt.h"

// model header files
#include "or1kExceptions.h"
#include "or1kExceptionTypes.h"
#include "or1kFunctions.h"
#include "or1kStructure.h"
#include "or1kUtils.h"


//
// Set the value of a bit in a word
//
#define SET_BIT(_R, _C, _M) \
    if(_C) {                    \
        (_R) = (_R) | (_M);     \
    } else {                    \
        (_R) = (_R) & ~(_M);    \
    }

//
// Get the value of a bit in a word
//
#define GET_BIT(_R, _M) \
    (((_R) & (_M)) ? 1 : 0)

//
// Mode decription helper
//
#define OR1K_MODE_INFO(_D) [OR1K_MODE_##_D] = {name:#_D, code:OR1K_MODE_##_D}

//
// Table of processor mode descriptions
//
static const vmiModeInfo modes[OR1K_MODE_LAST] = {
    OR1K_MODE_INFO(SUPERVISOR),
    OR1K_MODE_INFO(USER)
};

//
// Exception decription helper
//
#define OR1K_EXCEPTION_INFO(_D,_DESC) [OR1K_EXCPT_##_D] = { \
    name        : #_D,          \
    code        : _D##_ADDRESS, \
    description : _DESC         \
}

//
// Table of exception mode descriptors
//
static const vmiExceptionInfo exceptions[OR1K_EXCPT_LAST] = {
    OR1K_EXCEPTION_INFO(RST, "Reset"),
    OR1K_EXCEPTION_INFO(BUS, "Bus error"),
    OR1K_EXCEPTION_INFO(DPF, "Data privilege"),
    OR1K_EXCEPTION_INFO(IPF, "Instruction privilege"),
    OR1K_EXCEPTION_INFO(TTI, "Tick timer"),
    OR1K_EXCEPTION_INFO(ILL, "Illegal instruction"),
    OR1K_EXCEPTION_INFO(EXI, "External interrupt"),
    OR1K_EXCEPTION_INFO(SYS, "System call"),
};

//
// Fill the full current value of the SR register, including bits normally
// maintained in separate flags fields
//
inline static void fillSR(or1kP or1k) {
    SET_BIT(or1k->SR, or1k->branchFlag,   SPR_SR_F);
    SET_BIT(or1k->SR, or1k->carryFlag,    SPR_SR_CY);
    SET_BIT(or1k->SR, or1k->overflowFlag, SPR_SR_OV);
}

//
// Return the current value of the SR register
//
Uns32 or1kGetSR(or1kP or1k) {
    fillSR(or1k);
    return or1k->SR;
}

//
// Assign a new value to the SR field and switch processor mode if required
//
static void setSRSwitchMode(or1kP or1k, Uns32 value) {

    Uns32 oldSM = or1k->SR & SPR_SR_SM;
    Uns32 newSM = value    & SPR_SR_SM;

    // set the SR field
    or1k->SR = value;

    // switch mode if required
    if(oldSM != newSM) {
        or1kMode newMode = newSM ? OR1K_MODE_SUPERVISOR : OR1K_MODE_USER;
        vmirtSetMode((vmiProcessorP)or1k, newMode);
    }
}

//
// Set the current value of the SR register
//
void or1kSetSR(or1kP or1k, Uns32 value) {

    // it is never possible to clear the fixed-one (FO) bit
    value |= SPR_SR_FO;

    // set the SR
    setSRSwitchMode(or1k, value);

    // set the current branch flag, carry flag and overflow flag from the SR
    or1k->branchFlag   = GET_BIT(value, SPR_SR_F);
    or1k->carryFlag    = GET_BIT(value, SPR_SR_CY);
    or1k->overflowFlag = GET_BIT(value, SPR_SR_OV);

    // ensure any pending interrupt is taken before the next instruction
    if(value & (SPR_SR_IEE|SPR_SR_TEE)) {
        or1kInterruptNext(or1k);
    }
}

//
// Enter supervisor mode on OR1K
//
void or1kEnterSupervisorMode(or1kP or1k) {

    const Uns32 clearBits = (
        SPR_SR_IEE |    // interrupt enable
        SPR_SR_TEE |    // tick timer enable
        SPR_SR_DME |    // data MMU enable
        SPR_SR_IME |    // instruction MMU enable
        SPR_SR_OVE      // overflow exception enable
    );

    // save the current status register in esr
    or1k->ESR = or1kGetSR(or1k);

    // mask out the 'clear' bits and mask in supervisor mode
    setSRSwitchMode(or1k, (or1k->ESR & ~clearBits) | SPR_SR_SM);
}

//
// Take an exception
//
void or1kTakeException(or1kP or1k, or1kException exception, Uns32 pcOffset) {

    Uns8  simD;
    Uns32 simPC = (Uns32)vmirtGetPCDS((vmiProcessorP)or1k, &simD);

    or1kEnterSupervisorMode(or1k);
    or1k->EPC = simPC + pcOffset;

    // set sr[DSX] for exception in a delay slot
    if(simD) {
        or1k->SR |= SPR_SR_DSX;
    }

    // save the exception index on the processor and jump to the vector
    or1k->exception = exception;
    vmirtSetPCException((vmiProcessorP)or1k, exceptions[exception].code);
}

//
// Return the current processor mode
//
VMI_GET_MODE_FN(or1kGetMode) {

    or1kP    or1k    = (or1kP)processor;
    Uns32    SM      = or1k->SR & SPR_SR_SM;
    or1kMode newMode = SM ? OR1K_MODE_SUPERVISOR : OR1K_MODE_USER;

    return modes+newMode;
}

//
// Processor mode iterator
//
VMI_MODE_INFO_FN(or1kModeInfo) {

    vmiModeInfoCP end = modes+OR1K_MODE_LAST;

    // on the first call, start with the first member of the table
    if(!prev) {
        prev = modes-1;
    }

    // get the next member
    vmiModeInfoCP this = prev+1;

    // return the next member, or NULL if at the end of the list
    return (this==end) ? 0 : this;
}

//
// Return the current processor exception
//
VMI_GET_EXCEPTION_FN(or1kGetException) {
    or1kP or1k = (or1kP)processor;
    return &exceptions[or1k->exception];
}

//
// Exception mode iterator
//
VMI_EXCEPTION_INFO_FN(or1kExceptionInfo) {

    vmiExceptionInfoCP end = exceptions+OR1K_EXCPT_LAST;

    // on the first call, start with the first member of the table
    if(!prev) {
        prev = exceptions-1;
    }

    // get the next member
    vmiExceptionInfoCP this = prev+1;

    // return the next member, or NULL if at the end of the list
    return (this==end) ? 0 : this;
}

//
// Dump OR1K registers
//
VMI_DEBUG_FN(or1kDumpRegisters) {

    or1kP or1k = (or1kP)processor;
    Uns32 i    = 0;

    vmiPrintf("--------------- --------------- --------------- ---------------\n");

    // print general-purpose registers
    while(i<OR1K_REGS) {
        vmiPrintf(" R%-2u: %08x", i, or1k->regs[i]);
        i++;
        if(!(i&3)) {
            vmiPrintf("\n");
        } else {
            vmiPrintf("  ");
        }
    }

    // newline if required before status registers
    if(i&3) {
        vmiPrintf("\n");
    }

    // program counter
    vmiPrintf(" PC : %08x  ", (Uns32)vmirtGetPC(processor));

    // status register
    vmiPrintf(" SR : %08x  ", or1kGetSR(or1k));

    // exception status register
    vmiPrintf(" ESR: %08x  ", or1k->ESR);

    // exception program counter
    vmiPrintf(" EPC: %08x  ", or1k->EPC);

    // newline before time and PIC registers
    vmiPrintf("\n");

    // tick timer registers
    vmiPrintf(" TCR: %08x  ", or1kGetTTCR(or1k));
    vmiPrintf(" TMR: %08x  ", or1k->TTMR);

    // PIC registers
    vmiPrintf(" PSR: %08x  ", or1k->PICSR);
    vmiPrintf(" PMR: %08x  ", or1k->PICMR);

    // newline before flags
    vmiPrintf("\n");

    // flags
    vmiPrintf(
        " BF:%u CF:%u OF:%u ",
        or1k->branchFlag,
        or1k->carryFlag,
        or1k->overflowFlag
    );

    vmiPrintf("\n--------------- --------------- --------------- ---------------\n\n");
}

//
// This returns the endianness of the OR1K processor
//
VMI_ENDIAN_FN(or1kGetEndian) {
    return MEM_ENDIAN_BIG;
}

//
// Return the next instruction address after 'thisPC'.
//
VMI_NEXT_PC_FN(or1kNextInstruction) {
    Uns32 nextAddress = (Uns32)(thisPC + 4);
    return nextAddress;
}

