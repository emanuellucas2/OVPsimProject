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

// Standard header files
#include <stdio.h>      // for sprintf

// Imperas header files
#include "hostapi/typeMacros.h"

// VMI header files
#include "vmi/vmiMessage.h"
#include "vmi/vmiMt.h"
#include "vmi/vmiRt.h"

// model header files
#include "andesACE.h"
#include "andesConfig.h"
#include "andesCSR.h"
#include "andesExceptions.h"
#include "andesMessage.h"
#include "andesMode.h"
#include "andesStructure.h"
#include "andesTypeRefs.h"
#include "andesUtils.h"
#include "andesVariant.h"

// base model header files
#include "riscvStructure.h"
#include "riscvVMUtils.h"


////////////////////////////////////////////////////////////////////////////////
// UTILITIES
////////////////////////////////////////////////////////////////////////////////

//
// Return current program counter
//
inline static Uns64 getPC(riscvP riscv) {
    return vmirtGetPC((vmiProcessorP)riscv);
}


////////////////////////////////////////////////////////////////////////////////
// ANDES BLOCK MASK
////////////////////////////////////////////////////////////////////////////////

//
// Refresh Andes block mask
//
static void updateBlockMask(riscvP riscv, vmiosObjectP object) {

    andesMode mode = 0;

    // derive new block mask
    if(RD_XCSR_FIELD(object, mmisc_ctl, RVCOMPM)) {mode |= ANM_RVCOMPM;}
    if(RD_XCSR_FIELD(object, mmisc_ctl, MSA_UNA)) {mode |= ANM_MSA_UNA;}
    if(RD_XCSR_FIELD(object, mhsp_ctl,  M))       {mode |= ANM_MHSP;}
    if(RD_XCSR_FIELD(object, mhsp_ctl,  S))       {mode |= ANM_SHSP;}
    if(RD_XCSR_FIELD(object, mhsp_ctl,  U))       {mode |= ANM_UHSP;}

    // handle change in Andes mode
    if(mode != object->mode) {

        void *modeP = &object->mode;

        // update current block mask to match mode
        vmirtSetBlockMask32((vmiProcessorP)riscv, modeP, mode);
    }
}


////////////////////////////////////////////////////////////////////////////////
// ANDES-ENHANCED PERFORMANCE MONITORING
////////////////////////////////////////////////////////////////////////////////

//
// HPM interrupts use id 18
//
#define HPMIntMask (1<<18)

//
// Generate HPM interrupt if required
//
static void refreshHPMInterrupt(vmiosObjectP object) {

    riscvP riscv         = object->riscv;
    Uns32  mcounterovf   = RD_XCSR(object, mcounterovf);
    Uns32  mcounterinten = RD_XCSR(object, mcounterinten);
    Uns64  ip            = riscv->ip[0];

    // get new pending state
    if(mcounterovf & mcounterinten) {
        ip |= HPMIntMask;
    } else {
        ip &= ~HPMIntMask;
    }

    // handle any change to pending state
    if(riscv->ip[0] != ip) {
        riscv->ip[0] = ip;
        andesTestInterrupt(riscv);
    }
}

//
// Read CSR from base model
//
inline static Uns64 baseR(riscvP riscv, riscvCSRId id) {
    return riscv->cb.readBaseCSR(riscv, id);
}

//
// Return register index for CSR
//
inline static Uns32 getCSRNum(riscvCSRAttrsCP attrs) {
    return attrs->csrNum;
}

//
// Return mask of readable Performance Monitor registers in the current mode
//
static Uns32 getHPMMaskR(vmiosObjectP object) {

    riscvP    riscv = object->riscv;
    riscvMode mode  = getCurrentMode3(riscv);
    Uns32     valid = RD_CSR_MASKC(riscv, mcounteren);

    if(mode<RISCV_MODE_MACHINE) {
        valid &= RD_CSRC(riscv, mcounteren);
    }
    if(mode<RISCV_MODE_SUPERVISOR) {
        valid &= RD_CSRC(riscv, scounteren);
    }

    return valid;
}

//
// Return mask of writeable Performance Monitor registers in the current mode
//
inline static Uns32 getHPMMaskW(vmiosObjectP object) {
    return RD_XCSR(object, mcounterwen);
}

//
// Return mask of possibly-readable Performance Monitor registers
//
static Uns32 getHPMMaskAllR(vmiosObjectP object) {
    return RD_CSR_MASKC(object->riscv, mcounteren);
}

//
// Return mask of possibly-writeable Performance Monitor registers
//
static Uns32 getHPMMaskAllW(vmiosObjectP object) {
    return RD_XCSR_MASK(object, mcounterwen);
}

//
// Return a Boolean indicating if an access to the indicated Performance
// Monitor register is valid (and take an Undefined Instruction exception
// if not)
//
static Bool hpmAccessValid(
    riscvCSRAttrsCP attrs,
    riscvP          riscv,
    Bool            isWrite
) {
    vmiosObjectP object = attrs->object;
    Uns32        index  = getCSRNum(attrs);
    Uns32        mask   = (1<<(index&31));
    Uns32        valid  = isWrite ? getHPMMaskW(object) : getHPMMaskR(object);

    if(riscv->artifactAccess) {

        // all artifact accesses are allowed
        return True;

    } else if(mask & valid) {

        // access allowed by current mask settings
        return True;

    } else {

        Uns32 all = isWrite ? getHPMMaskAllW(object) : getHPMMaskAllR(object);

        // report the disabled instruction
        if(!riscv->verbose) {
            // no action
        } else if(mask & all) {
            vmiMessage("W", CPU_PREFIX "_IHPMA",
                SRCREF_FMT "Illegal instruction (access disallowed in current mode)",
                SRCREF_ARGS(riscv, getPC(riscv))
            );
        } else {
            vmiMessage("W", CPU_PREFIX "_IHPMU",
                SRCREF_FMT "Illegal instruction (CSR unimplemented)",
                SRCREF_ARGS(riscv, getPC(riscv))
            );
        }

        // take Illegal Instruction exception
        andesIllegalInstruction(riscv);

        return False;
    }
}

//
// Return value created by modifying indexed half of oldValue with newValue
//
inline static Uns64 setHalf(Uns32 newValue, Uns64 oldValue, Uns32 index) {

    union {Uns64 u64; Uns32 u32[2];} u = {oldValue};

    u.u32[index] = newValue;

    return u.u64;
}

//
// Return value created by modifying lower half of oldValue with newValue
//
inline static Uns64 setLower(Uns32 newValue, Uns64 oldValue) {
    return setHalf(newValue, oldValue, 0);
}

//
// Return value created by modifying upper half of oldValue with newValue
//
inline static Uns64 setUpper(Uns32 newValue, Uns64 oldValue) {
    return setHalf(newValue, oldValue, 1);
}

//
// Return value based in current XLEN
//
inline static Uns64 getXLENValue(riscvP riscv, Uns64 result) {
    return RISCV_XLEN_IS_32(riscv) ? (Uns32)result : result;
}

//
// Return current value of an uninhibited counter
//
inline static Uns64 getCurrentCount(andesCounterP counter) {
    return vmirtGetModelTimerCurrentCount(counter->vmi, False);
}

//
// Is the counter inactive?
//
inline static Bool counterInactive(andesCounterP counter) {
    return counter->mode==ACM_INACTIVE;
}

//
// Common routine to read counter
//
static Uns64 counterR(andesCounterP counter) {

    Uns64 result = counter->base;

    if(!counterInactive(counter)) {
        result = getCurrentCount(counter) - result;
    }

    return result;
}

//
// Common routine to write counter (NOTE: count is notionally incremented
// *before* the write if this is the result of a CSR write)
//
static void counterW(andesCounterP counter, Uns64 newValue, Bool preIncrement) {

    if(!counterInactive(counter)) {

        // handle notional increment (by setting *current* count to one less
        // than the indicated value)
        if(preIncrement && !counter->object->riscv->artifactAccess) {
            newValue--;
        }

        // schedule timer expiry as near as possible to overflow
        Uns64 delta = -newValue;
        vmirtSetModelTimer(counter->vmi, delta ? delta : -1);

        // derive new counter base value
        newValue = getCurrentCount(counter) - newValue;
    }

    counter->base = newValue;
}

//
// Function called when performance monitor timer expires
//
static VMI_ICOUNT_FN(counterExpired) {

    andesCounterP counter = userData;

    if(!counterInactive(counter)) {

        // get counter value
        Uns64 value = counterR(counter);

        // handle timer wraparound
        if(!value) {

            vmiosObjectP object   = counter->object;
            Uns32        oldValue = RD_XCSR(object, mcounterovf);
            Uns32        newValue = oldValue | (1<<counter->id);

            // handle any change to interrupt state
            if(newValue != oldValue) {
                WR_XCSR(object, mcounterovf, newValue);
                refreshHPMInterrupt(object);
            }
        }

        // set counter value to reschedule timer
        counterW(counter, value, False);
    }
}

//
// Common routine to read counter
//
static Uns64 counterLR(
    riscvCSRAttrsCP attrs,
    riscvP          riscv,
    andesCounterID  id
) {
    vmiosObjectP  object  = attrs->object;
    andesCounterP counter = &object->counters[id];

    return getXLENValue(riscv, counterR(counter));
}

//
// Common routine to write counter
//
static Uns64 counterLW(
    riscvCSRAttrsCP attrs,
    riscvP          riscv,
    Uns64           newValue,
    andesCounterID  id
) {
    vmiosObjectP  object  = attrs->object;
    andesCounterP counter = &object->counters[id];

    if(RISCV_XLEN_IS_32(riscv)) {
        counterW(counter, setLower(newValue, counterR(counter)), True);
    } else {
        counterW(counter, newValue, True);
    }

    return newValue;
}

//
// Common routine to read high half of counter
//
static Uns64 counterHR(
    riscvCSRAttrsCP attrs,
    riscvP          riscv,
    andesCounterID  id
) {
    vmiosObjectP  object  = attrs->object;
    andesCounterP counter = &object->counters[id];

    return counterR(counter) >> 32;
}

//
// Common routine to write high half of counter
//
static Uns64 counterHW(
    riscvCSRAttrsCP attrs,
    riscvP          riscv,
    Uns64           newValue,
    andesCounterID  id
) {
    vmiosObjectP  object  = attrs->object;
    andesCounterP counter = &object->counters[id];

    counterW(counter, setUpper(newValue, counterR(counter)), True);

    return newValue;
}

//
// Common routine to read counter if access to it is valid
//
static Uns64 counterLValidR(
    riscvCSRAttrsCP attrs,
    riscvP          riscv,
    andesCounterID  id
) {
    Uns64 result = 0;

    if(hpmAccessValid(attrs, riscv, False)) {
        result = counterLR(attrs, riscv, id);
    }

    return result;
}

//
// Common routine to write counter if access to it is valid
//
static Uns64 counterLValidW(
    riscvCSRAttrsCP attrs,
    riscvP          riscv,
    Uns64           newValue,
    andesCounterID  id
) {
    if(hpmAccessValid(attrs, riscv, True)) {
        newValue = counterLW(attrs, riscv, newValue, id);
    }

    return newValue;
}

//
// Common routine to read high half of counter if access to it is valid
//
static Uns64 counterHValidR(
    riscvCSRAttrsCP attrs,
    riscvP          riscv,
    andesCounterID  id
) {
    Uns64 result = 0;

    if(hpmAccessValid(attrs, riscv, False)) {
        result = counterHR(attrs, riscv, id);
    }

    return result;
}

//
// Common routine to write high half of counter if access to it is valid
//
static Uns64 counterHValidW(
    riscvCSRAttrsCP attrs,
    riscvP          riscv,
    Uns64           newValue,
    andesCounterID  id
) {
    if(hpmAccessValid(attrs, riscv, True)) {
        newValue = counterHW(attrs, riscv, newValue, id);
    }

    return newValue;
}

//
// Adjust base for active instruction counters take into account whether
// the instruction causing a trap has retired
//
static void refreshCountersNotRetired(vmiosObjectP object) {

    andesCounterID id;

    for(id=0; id<AT_LAST; id++) {

        andesCounterP counter = &object->counters[id];

        if(counter->mode==ACM_IR) {
            counter->base++;
        }
    }
}

//
// Refresh the counter state when its configuration or the processor state has
// changed
//
static void refreshCounter(andesCounterP counter) {

    vmiosObjectP     object = counter->object;
    riscvP           riscv  = object->riscv;
    andesCounterMode cmode = ACM_INACTIVE;

    // get raw counter mode
    if(counter->TYPE) {
        // no action
    } else if(counter->SEL==1) {
        cmode = ACM_CY;
    } else if(counter->SEL==2) {
        cmode = riscv->disable ? ACM_INACTIVE : ACM_IR;
    }

    // apply counter masking
    if(cmode) {

        riscvMode mode = getCurrentMode3(riscv);
        Uns32     mask = (1<<counter->id);
        Uns32     inactive;

        // get mask of inactive counters in this mode
        if(mode==RISCV_MODE_MACHINE) {
            inactive = RD_XCSR(object, mcountermask_m);
        } else if(mode==RISCV_MODE_SUPERVISOR) {
            inactive = RD_XCSR(object, mcountermask_s);
        } else {
            inactive = RD_XCSR(object, mcountermask_u);
        }

        // force counter into an inactive state if required
        if(mask&inactive) {
            cmode = ACM_INACTIVE;
        }
    }

    // handle counter mode change
    if(counter->mode != cmode) {

        // get counter value in old mode
        Uns64 value = counterR(counter);

        // update mode
        counter->mode = cmode;

        // set counter value in new mode
        counterW(counter, value, False);
    }
}

//
// Configure a counter given Andes SEL and TYPE codes
//
static void configureTimer(
    vmiosObjectP   object,
    andesCounterID id,
    Uns8           TYPE,
    Uns8           SEL
) {
    andesCounterP counter = &object->counters[id];

    // update configuration
    counter->TYPE = TYPE;
    counter->SEL  = SEL;

    // refresh the timer
    refreshCounter(counter);
}

//
// Refresh all counter objects
//
static void refreshCounters(vmiosObjectP object) {

    andesCounterID id;

    for(id=0; id<AT_LAST; id++) {

        andesCounterP counter = &object->counters[id];

        if(counter->vmi) {
            refreshCounter(counter);
        }
    }
}

//
// Reset all counter objects
//
static void resetCounters(vmiosObjectP object) {

    andesCounterID id;

    for(id=AT_HPM3; id<AT_LAST; id++) {

        andesCounterP counter = &object->counters[id];

        if(counter->vmi) {
            configureTimer(object, id, 0, 0);
        }
    }
}

//
// Refresh counters on halt/restart event
//
static RISCV_HR_NOTIFIER_FN(haltRestartNotifier) {
    refreshCounters(clientData);
}

//
// Create a new counter object
//
static void newCounter(vmiosObjectP object, andesCounterID id) {

    vmiProcessorP processor = (vmiProcessorP)object->riscv;
    andesCounterP counter   = &object->counters[id];

    // save id
    counter->id = id;

    // save container
    counter->object = object;

    // create VMI timer object
    counter->vmi = vmirtCreateModelTimer(processor, counterExpired, 1, counter);
}

//
// Allocate counter objects in this model only if mmsc_cfg.PMNDS is set (if not,
// fall back to the base model implementation)
//
void newCounters(vmiosObjectP object) {

    if(RD_XCSR_FIELD(object, mmsc_cfg, PMNDS)) {

        // allocate counters
        newCounter(object, AT_CY);
        newCounter(object, AT_IR);
        newCounter(object, AT_HPM3);
        newCounter(object, AT_HPM4);
        newCounter(object, AT_HPM5);
        newCounter(object, AT_HPM6);

        // configure always-present cycle and instruction counters
        configureTimer(object, AT_CY, 0, 1);
        configureTimer(object, AT_IR, 0, 2);
    }
}

//
// Free counter objects
//
void freeCounters(vmiosObjectP object) {

    andesCounterID id;

    for(id=0; id<AT_LAST; id++) {

        andesCounterP counter = &object->counters[id];

        if(counter->vmi) {
            vmirtDeleteModelTimer(counter->vmi);
        }
    }
}

//
// Common routine to read counter event selector
//
static Uns64 eventR(
    riscvCSRAttrsCP attrs,
    riscvP          riscv,
    andesCounterID  id
) {
    vmiosObjectP  object  = attrs->object;
    andesCounterP counter = &object->counters[id];

    CSR_REG_DECL(andes_event) = {
        u32 : {
            fields : {
                TYPE : counter->TYPE,
                SEL  : counter->SEL,
            }
        }
    };

    return andes_event.u32.bits;
}

//
// Common routine to write counter event selector
//
static Uns64 eventW(
    riscvCSRAttrsCP attrs,
    riscvP          riscv,
    Uns64           newValue,
    andesCounterID  id
) {
    vmiosObjectP object = attrs->object;

    CSR_REG_DECL(andes_event) = {u32 : {bits : newValue}};

    configureTimer(
        object,
        id,
        andes_event.u32.fields.TYPE,
        andes_event.u32.fields.SEL
    );

    return andes_event.u32.bits;
}

//
// Return ID given CSR index
//
inline static andesCounterID getHPMId(riscvCSRAttrsCP attrs) {
    return AT_CY + (getCSRNum(attrs) & 0x1f);
}

//
// Read M-mode performance event selector
//
static RISCV_CSR_READFN(mhpmeventR) {
    return eventR(attrs, riscv, getHPMId(attrs));
}

//
// Write M-mode performance event counter
//
static RISCV_CSR_WRITEFN(mhpmeventW) {
    return eventW(attrs, riscv, newValue, getHPMId(attrs));
}

//
// Read M-mode performance counter
//
static RISCV_CSR_READFN(mhpmR) {
    return counterLR(attrs, riscv, getHPMId(attrs));
}

//
// Write M-mode performance counter
//
static RISCV_CSR_WRITEFN(mhpmW) {
    return counterLW(attrs, riscv, newValue, getHPMId(attrs));
}

//
// Read M-mode performance counter upper half
//
static RISCV_CSR_READFN(mhpmhR) {
    return counterHR(attrs, riscv, getHPMId(attrs));
}

//
// Write M-mode performance counter upper half
//
static RISCV_CSR_WRITEFN(mhpmhW) {
    return counterHW(attrs, riscv, newValue, getHPMId(attrs));
}

//
// Read U-mode performance counter
//
static RISCV_CSR_READFN(hpmR) {
    return counterLValidR(attrs, riscv, getHPMId(attrs));
}

//
// Write U-mode performance counter
//
static RISCV_CSR_WRITEFN(hpmW) {
    return counterLValidW(attrs, riscv, newValue, getHPMId(attrs));
}

//
// Read U-mode performance counter upper half
//
static RISCV_CSR_READFN(hpmhR) {
    return counterHValidR(attrs, riscv, getHPMId(attrs));
}

//
// Write U-mode performance counter upper half
//
static RISCV_CSR_WRITEFN(hpmhW) {
    return counterHValidW(attrs, riscv, newValue, getHPMId(attrs));
}

//
// Write mcounterinten
//
static RISCV_CSR_WRITEFN(mcounterintenW) {

    vmiosObjectP object   = attrs->object;
    Uns32        oldValue = RD_XCSR(object, mcounterinten);

    // mask value
    newValue &= RD_XCSR_MASK(object, mcounterinten);

    // handle any change to interrupt state
    if(newValue != oldValue) {
        WR_XCSR(object, mcounterinten, newValue);
        refreshHPMInterrupt(object);
    }

    return newValue;
}

//
// Write mcountermask_m
//
static RISCV_CSR_WRITEFN(mcountermask_mW) {

    vmiosObjectP object = attrs->object;

    // mask value
    newValue &= RD_XCSR_MASK(object, mcountermask_m);

    // update mask and refresh counters
    if(RD_XCSR(object, mcountermask_m) != newValue) {
        WR_XCSR(object, mcountermask_m, newValue);
        refreshCounters(object);
    }

    return newValue;
}

//
// Write mcounterovf
//
static RISCV_CSR_WRITEFN(mcounterovfW) {

    vmiosObjectP object   = attrs->object;
    Uns32        oldValue = RD_XCSR(object, mcounterovf);

    // mask value
    newValue &= RD_XCSR_MASK(object, mcounterovf);

    // handle write-1-to-clear semantics
    if(!riscv->artifactAccess) {
        newValue = oldValue & ~newValue;
    }

    // handle any change to interrupt state
    if(newValue != oldValue) {
        WR_XCSR(object, mcounterovf, newValue);
        refreshHPMInterrupt(object);
    }

    return newValue;
}

//
// Read time
//
static RISCV_CSR_READFN(timeR) {

    Uns64 result = 0;

    if(hpmAccessValid(attrs, riscv, False)) {
        result = baseR(riscv, CSR_ID(time));
    }

    return result;
}

//
// Read timeh
//
static RISCV_CSR_READFN(timehR) {

    Uns64 result = 0;

    if(hpmAccessValid(attrs, riscv, False)) {
        result = baseR(riscv, CSR_ID(timeh));
    }

    return result;
}


////////////////////////////////////////////////////////////////////////////////
// CONTROL AND CAUSE
////////////////////////////////////////////////////////////////////////////////

//
// Write mmisc_ctl
//
static RISCV_CSR_WRITEFN(mmisc_ctlW) {

    vmiosObjectP object   = attrs->object;
    Uns32        oldValue = RD_XCSR(object, mmisc_ctl);
    Uns32        mask     = WM32_mmisc_ctl;

    // get new value using writable bit mask
    newValue = ((newValue & mask) | (oldValue & ~mask));

    // update the CSR
    WR_XCSR(object, mmisc_ctl, newValue);

    // The VEC_PLIC field is hardwired to 0 when mmsc_cfg.VPLIC is 0
    if (!RD_XCSR_FIELD(object, mmsc_cfg, VPLIC)) {
        WR_XCSR_FIELD(object, mmisc_ctl, VEC_PLIC, 0);
    }

    // derive new Andes mode
    updateBlockMask(riscv, object);

    // return written value
    return newValue;
}

//
// Read mdcause
//
static RISCV_CSR_READFN(mdcauseR) {

    vmiosObjectP     object  = attrs->object;
    Uns64            result  = RD_XCSR(object, mdcause);
    riscvAccessFault AFError = riscv->AFErrorOut;

    // derive result unless mdcause has been explicitly written
    if(AFError!=riscv_AFault_Explicit) {

        // map from riscvAccessFault to mdcause equivalent
        const static Uns8 map[] = {
            [riscv_AFault_None]    = 0,     // last exception not access fault
            [riscv_AFault_PMP]     = 2,     // PMP access violation
            [riscv_AFault_Bus]     = 3,     // bus error
            [riscv_AFault_Device]  = 7,     // PMA NAMO violation
            [riscv_AFault_Custom1] = 4,     // PMA code violation
            [riscv_AFault_Custom2] = 5,     // PMA data violation
        };

        result = map[AFError];
    }

    return result;
}

//
// Write mdcause
//
static RISCV_CSR_WRITEFN(mdcauseW) {

    vmiosObjectP object = attrs->object;

    // assign explicit value to mdcause
    riscv->AFErrorOut = riscv_AFault_Explicit;
    WR_XCSR(object, mdcause, newValue);

    return newValue;
}


////////////////////////////////////////////////////////////////////////////////
// HARDWARE STACK PROTECTION
////////////////////////////////////////////////////////////////////////////////

//
// Return mode mask to be used to determine if hardware stack protection is
// currently enabled
//
static andesMode getModeMaskHSP(riscvP riscv) {

    static const andesMode map[] = {
        [RISCV_MODE_USER]       = ANM_UHSP,
        [RISCV_MODE_SUPERVISOR] = ANM_SHSP,
        [RISCV_MODE_MACHINE]    = ANM_MHSP,
    };

    return map[getCurrentMode3(riscv)];
}

//
// Is hardware stack protection currently enabled? (morph time, controlled by
// block mask)
//
static Bool isHSPEnabledMT(riscvP riscv, vmiosObjectP object) {

    andesMode mode    = getModeMaskHSP(riscv);
    vmiReg    modeReg = andesObjectReg(object, EXT_REG(mode));

    // validate block mask for hardware stack protection enable
    vmimtValidateBlockMaskR(32, modeReg, mode);

    return (object->mode & mode);
}

//
// Write mhsp_ctl
//
static RISCV_CSR_WRITEFN(mhsp_ctlW) {

    vmiosObjectP object = attrs->object;

    // update value
    WR_XCSR(object, mhsp_ctl, newValue & WM64_mhsp_ctl);

    // derive new Andes mode
    updateBlockMask(riscv, object);

    return newValue;
}

//
// Take hardware stack protection exception
//
static void doHSPException(
    riscvP         riscv,
    vmiosObjectP   object,
    andesException exception
) {
    // revert SP to its value prior to instruction execution
    riscv->x[RV_REG_X_SP] = object->oldSP;

    // clear stack protection enables
    WR_XCSR_FIELD(object, mhsp_ctl, OVF_EN, 0);
    WR_XCSR_FIELD(object, mhsp_ctl, UDF_EN, 0);

    // do standard exception actions
    andesTakeException(riscv, exception, 0);
}

//
// Implement hardware stack protection check
//
static void doHSPCheck(riscvP riscv, vmiosObjectP object) {

    andesMode mode = getModeMaskHSP(riscv);
    Uns64     SP   = riscv->x[RV_REG_X_SP];

    // sanity check HSP is indeed enabled
    VMI_ASSERT(object->mode & mode, "HSP check unexpectedly disabled");

    if(RD_XCSR_FIELD(object, mhsp_ctl, SCHM)) {

        // top-of-stack recording scheme selected
        if(!RD_XCSR_FIELD(object, mhsp_ctl, OVF_EN)) {
            // recording disabled
        } else if(RD_XCSR(object, msp_bound) > SP) {
            WR_XCSR(object, msp_bound, SP);
        }

    } else {

        Bool checkOVF = RD_XCSR_FIELD(object, mhsp_ctl, OVF_EN);
        Bool checkUDF = RD_XCSR_FIELD(object, mhsp_ctl, UDF_EN);

        // exception on stack overflow if required
        if(checkOVF && (RD_XCSR(object, msp_bound) > SP)) {
            doHSPException(riscv, object, andes_E_HSP_OVF);
            checkUDF = False;
        }

        // exception on stack underflow if required
        if(checkUDF && (RD_XCSR(object, msp_base) < SP)) {
            doHSPException(riscv, object, andes_E_HSP_UDF);
        }
    }
}

//
// Record old value of SP if hardware stack protection check if required
//
void andesRecordSP(riscvP riscv, vmiosObjectP object) {

    if(!isHSPEnabledMT(riscv, object)) {

        // no action if feature is currently disabled

    } else {

        Uns32  bits     = andesGetXlenArch(riscv);
        vmiReg oldSPReg = andesObjectReg(object, EXT_REG(oldSP));

        // move current stack pointer to a temporary
        vmimtMoveRR(bits, oldSPReg, RISCV_GPR(RV_REG_X_SP));
    }
}

//
// Add hardware stack protection check if required
//
void andesCheckHSP(riscvP riscv, vmiosObjectP object) {

    if(!isHSPEnabledMT(riscv, object)) {

        // no action if feature is currently disabled

    } else if(riscv->writtenXMask & (1<<RV_REG_X_SP)) {

        // check is required only if the instruction updates SP
        vmimtArgProcessor();
        vmimtArgNatAddress(object);
        vmimtCallAttrs((vmiCallFn)doHSPCheck, VMCA_NA);
    }
}


////////////////////////////////////////////////////////////////////////////////
// PHYSICAL MEMORY ATTRIBUTE SUPPORT
////////////////////////////////////////////////////////////////////////////////

//
// Return privilege name for the given privilege
//
static const char *privName(memPriv priv) {

    static const char *map[] = {
        "---", "r--", "-w-", "rw-", "--x", "r-x", "-wx", "rwx"
    };

    // ignore NAMO management bit
    priv &= ~MEM_PRIV_USER1;

    // sanity check given privilege
    VMI_ASSERT(priv<8, "unexpected privilege %u", priv);

    return map[priv];
}

//
// Read the indexed PMP configuration register (internal routine)
//
inline static Uns64 readPMACFGInt(
    riscvP       riscv,
    vmiosObjectP object,
    Uns32        index
) {
    riscvArchitecture arch = riscv->currentArch;

    // return either 32-bit or 64-bit view
    if(arch & ISA_XLEN_64) {
        return object->pmacfg.u64[index/2];
    } else {
        return object->pmacfg.u32[index];
    }
}

//
// Return the indexed PMA configuration register
//
inline static pmacfgElem getPMACFGElem(vmiosObjectP object, Uns8 index) {
    return (pmacfgElem){u8:object->pmacfg.u8[index]};
}

//
// Return the effective value of a PMA address register
//
static Uns64 getEffectivePMAAddr(vmiosObjectP object, Uns8 index) {

    pmacfgElem e      = getPMACFGElem(object, index);
    Uns32      G      = object->csrDefaults.PMA_grain;
    Uns64      result = object->pmaaddr[index];

    if((G>=2) && (e.ETYP==PMAET_NAPOT)) {

        // when G>=2 and pmpcfgi.A[1] is set, i.e. the mode is NAPOT, then bits
        // pmaaddri[G-2:0] read as all ones
        result |= ((1ULL << (G-1)) - 1);

    } else if((G>=1) && (e.ETYP!=PMAET_NAPOT)) {

        // when G>=1 and pmpcfgi.A[1] is clear, i.e. the mode is OFF or TOR,
        // then bits pmaaddri[G-1:0] read as all zeros
        result &= (-1ULL << G);
    }

    return result;
}

//
// Is the indexed PMA region active?
//
static Bool getPMARegionActive(vmiosObjectP object, pmacfgElem e, Uns8 index) {

    if(e.ETYP==PMAET_OFF) {

        // region is disabled
        return False;

    } else if(e.ETYP!=PMAET_TOR) {

        // region is enabled with no range constraint
        return True;

    } else {

        // TOR region is effectively enabled only if the associated address is
        // non-zero (a zero address will always fail the bounds check)
        return getEffectivePMAAddr(object, index);
    }
}

//
// Set privileges in the given domain set
//
static void setDomainPriv(
    riscvP            riscv,
    riscvDomainSetBMP domainSetB,
    Uns64             low,
    Uns64             high,
    memPriv           priv,
    const char       *name,
    Bool              verbose
) {
    riscvMode mode;

    // emit debug if required
    if(verbose && RISCV_DEBUG_MMU(riscv)) {
        vmiPrintf(
            "%s PRIV=%s 0x"FMT_6408x":0x"FMT_6408x"\n",
            name, privName(priv), low, high
        );
    }

    for(mode=RISCV_MODE_S; mode<RISCV_MODE_LAST_BASE; mode++) {

        memDomainP dataDomain = (*domainSetB)[mode][0];
        memDomainP codeDomain = (*domainSetB)[mode][1];

        if(mode==RISCV_MODE_H) {

            // ignore artifact mode

        } else if(dataDomain==codeDomain) {

            // set permissions in unified domain
            vmirtProtectMemory(dataDomain, low, high, priv, MEM_PRIV_SET);

        } else {

            // set permissions in data domain if required
            if((priv==MEM_PRIV_NONE) || (priv&MEM_PRIV_RW)) {
                vmirtProtectMemory(
                    dataDomain, low, high, priv&MEM_PRIV_RW, MEM_PRIV_SET
                );
            }

            // set permissions in code domain if required
            if((priv==MEM_PRIV_NONE) || (priv&MEM_PRIV_X)) {
                vmirtProtectMemory(
                    codeDomain, low, high, priv&MEM_PRIV_X, MEM_PRIV_SET
                );
            }
        }
    }
}

//
// Set privileges in PMA domain
//
static void setPMAPriv(
    riscvP  riscv,
    Uns64   low,
    Uns64   high,
    memPriv priv,
    Bool    verbose
) {
    setDomainPriv(riscv, &riscv->pmaDomains, low, high, priv, "PMA", verbose);
}

//
// Return the bounds of the indexed PMA entry
//
static void getPMAEntryBounds(
    vmiosObjectP object,
    Uns32        index,
    Uns64       *lowP,
    Uns64       *highP
) {
    pmacfgElem e   = getPMACFGElem(object, index);
    Uns64      low = getEffectivePMAAddr(object, index)<<2;
    Uns64      high;

    if(e.ETYP==PMAET_NA4) {

        // 4-byte range (NOTE: not currently available)
        high = low + 3;

    } else if(e.ETYP==PMAET_NAPOT) {

        // naturally-aligned power of two range (NOTE: not currently available)
        Uns64 notLow = ~(low+3);
        Uns64 mask   = ((notLow & -notLow) << 1) - 1;

        low  = low & ~mask;
        high = low |  mask;

    } else {

        // top-of-range
        high = low-1;
        low  = index ? object->pmaaddr[index-1]<<2 : 0;

        // mask low address to implemented grain size
        low &= (-4ULL << object->csrDefaults.PMA_grain);
    }

    // assign results
    *lowP  = low;
    *highP = high;
}

//
// Update the bounds in lowPAP/highPAP and privilege to reflect the effect of
// region i
//
static void refinePMARegionRange(
    vmiosObjectP object,
    Uns64       *lowPAP,
    Uns64       *highPAP,
    Uns64        PA,
    Uns32        index,
    memPriv     *privP
) {
    pmacfgElem e  = getPMACFGElem(object, index);

    // only handle active regions
    if(getPMARegionActive(object, e, index)) {

        Uns64 lowPAEntry;
        Uns64 highPAEntry;

        // get bounds of the entry
        getPMAEntryBounds(object, index, &lowPAEntry, &highPAEntry);

        if(lowPAEntry>highPAEntry) {

            // ignore TOR region with low bound > high bound

        } else if((lowPAEntry<=PA) && (PA<=highPAEntry)) {

            // match in this region
            *lowPAP  = lowPAEntry;
            *highPAP = highPAEntry;

            // refine privilege
            if(e.MTYP==PMAMT_Black_Hole) {
                *privP = MEM_PRIV_NONE;
            } else if(!e.NAMO) {
                *privP = MEM_PRIV_RWX;
            } else {
                *privP = MEM_PRIV_RWX|MEM_PRIV_USER1;
            }

        } else if((lowPAEntry>PA) && (lowPAEntry<*highPAP)) {

            // remove part of region ABOVE matching address
            *highPAP = lowPAEntry-1;

        } else if((highPAEntry<PA) && (highPAEntry>*lowPAP)) {

            // remove part of region BELOW matching address
            *lowPAP = highPAEntry+1;
        }
    }
}

//
// Map region starting at lowPA, hopefully extending to highPA
//
static void mapPMAInt(
    riscvP       riscv,
    vmiosObjectP object,
    memPriv      requiredPriv,
    Uns64        lowPA,
    Uns64        highPA,
    Uns64       *lowMapP,
    Uns64       *highMapP
) {
    Uns64   PA   = *lowMapP;
    memPriv priv = MEM_PRIV_RWX;
    Int32 i;

    // set widest possible range initially
    *lowMapP = 0;

    // handle all regions in lowest-to-highest priority order
    for(i=PMA_NUM-1; i>=0; i--) {
        refinePMARegionRange(object, lowMapP, highMapP, PA, i, &priv);
    }

    // indicate PMA failure if required
    if(priv) {
        // no failure
    } else if(riscv->AFErrorIn==riscv_AFault_PMP) {
        // PMP error already active
    } else if(requiredPriv & MEM_PRIV_X) {
        riscv->AFErrorIn = riscv_AFault_Custom1;
    } else {
        riscv->AFErrorIn = riscv_AFault_Custom2;
    }

    // get PMA region range
    Uns64 lowMap  = *lowMapP;
    Uns64 highMap = *highMapP;

    // clamp physical range to maximum page size
    riscvClampPage(riscv, lowPA, highPA, &lowMap, &highMap);

    // update PMA privileges
    setPMAPriv(riscv, lowMap, highMap, priv, True);
}

//
// Refresh physical mappings for the given physical address range
//
static void mapPMA(
    riscvP       riscv,
    vmiosObjectP object,
    memPriv      requiredPriv,
    Uns64        lowPA,
    Uns64        highPA
) {
    Uns64 mask    = getAddressMask(riscv->extBits);
    Uns64 highMap = lowPA-1;
    Uns64 lowMap;

    // iterate while unprocessed regions remain
    do {

        // get next region bounds to try
        lowMap  = highMap+1;
        highMap = mask;

        // attempt PMA privilege change for regions in implemented range
        if(lowMap<=highMap) {
            mapPMAInt(riscv, object, requiredPriv, lowPA, highPA, &lowMap, &highMap);
        } else {
            highMap = highPA;
        }

    } while(highMap<highPA);
}

//
// Invalidate PMP entry 'index'
//
static void invalidatePMAEntry(riscvP riscv, vmiosObjectP object, Uns32 index) {

    pmacfgElem e = getPMACFGElem(object, index);

    if(getPMARegionActive(object, e, index)) {

        Uns64 low;
        Uns64 high;

        // get the entry bounds
        getPMAEntryBounds(object, index, &low, &high);

        // remove access, unless TOR entry with low>high
        if(low<=high) {
            setPMAPriv(riscv, low, high, MEM_PRIV_NONE, True);
        }
    }
}

//
// Read the indexed PMP configuration register
//
static Uns64 readPMACFG(riscvP riscv, vmiosObjectP object, Uns32 index) {
    return readPMACFGInt(riscv, object, index);
}

//
// Write the indexed PMP configuration register with the new value and return
// the new effective value
//
static Uns64 writePMACFG(
    riscvP       riscv,
    vmiosObjectP object,
    Uns32        index,
    Uns64        newValue
) {
    riscvArchitecture arch          = riscv->currentArch;
    Uns32             entriesPerCFG = (arch & ISA_XLEN_64) ? 8 : 4;
    Uns32             numPMA        = PMA_NUM;
    Uns32             numCFG        = ((numPMA+entriesPerCFG-1)/entriesPerCFG);

    // get offset into PMA bank allowing for the fact that when in 64-bit mode
    // the second set of PMA registers are controlled by pmacfg2 (not pmacfg1,
    // which is unimplemented)
    Uns32 offset = (arch & ISA_XLEN_64) ? index/2 : index;

    if(offset<numCFG) {

        Uns32       numBytes = numPMA-(offset*entriesPerCFG);
        Uns64       mask     = (numBytes>=8) ? -1 : (1ULL<<(numBytes*8))-1;
        riscvPMACFG oldValue = object->pmacfg;
        Int32       i;

        // mask writable bits
        newValue &= (WM64_pmacfg & mask);

        // update register
        if(arch & ISA_XLEN_64) {
            object->pmacfg.u64[offset] = newValue;
        } else {
            object->pmacfg.u32[offset] = newValue;
        }

        // invalidate any modified entries in lowest-to-highest priority order
        for(i=PMA_NUM-1; i>=0; i--) {

            // get old and new values
            pmacfgElem oldCFG = {u8:oldValue.u8[i]};
            pmacfgElem newCFG = {u8:object->pmacfg.u8[i]};

            // clamp entry mode to legal values
            if((newCFG.ETYP==PMAET_TOR) || (newCFG.ETYP==PMAET_NA4)) {
                newCFG.ETYP = PMAET_OFF;
                object->pmacfg.u8[i] = newCFG.u8;
            }

            // clamp memory type to legal values
            if(newCFG.MTYP>PMAMT_Memory_Write_back_Read_and_Write_allocate) {
                newCFG.MTYP = PMAMT_Black_Hole;
                object->pmacfg.u8[i] = newCFG.u8;
            } else if(newCFG.MTYP==PMAMT_Memory_Write_through_Write_allocate) {
                newCFG.MTYP = PMAMT_Memory_Write_through_No_allocate;
                object->pmacfg.u8[i] = newCFG.u8;
            } else if(newCFG.MTYP==PMAMT_Memory_Write_through_Read_Write_allocate) {
                newCFG.MTYP = PMAMT_Memory_Write_through_Read_allocate;
                object->pmacfg.u8[i] = newCFG.u8;
            }

            if(oldCFG.u8!=newCFG.u8) {

                // revert value (perhaps temporarily)
                object->pmacfg.u8[i] = oldCFG.u8;

                // invalidate entry using its original specification
                invalidatePMAEntry(riscv, object, i);

                // set new value
                object->pmacfg.u8[i] = newCFG.u8;

                // invalidate entry using its new specification
                invalidatePMAEntry(riscv, object, i);
            }
        }
    }

    // return updated value
    return readPMACFGInt(riscv, object, index);
}

//
// Read the indexed PMP address register
//
static Uns64 readPMAAddr(riscvP riscv, vmiosObjectP object, Uns32 index) {
    return getEffectivePMAAddr(object, index);
}

//
// Write the indexed PMP address register with the new value and return
// the new effective value
//
static Uns64 writePMAAddr(
    riscvP       riscv,
    vmiosObjectP object,
    Uns32        index,
    Uns64        newValue
) {
    Uns32 numRegs = PMA_NUM;
    Uns32 G       = object->csrDefaults.PMA_grain;

    // mask writable bits to implemented external bits
    newValue &= (getAddressMask(riscv->extBits) >> 2);

    // also mask writable bits if grain is set
    if(G) {
        newValue &= (-1ULL << (G-1));
    }

    if((index<numRegs) && (object->pmaaddr[index]!=newValue)) {

        // invalidate entry using its original specification
        invalidatePMAEntry(riscv, object, index);

        // set new value
        object->pmaaddr[index] = newValue;

        // invalidate entry using its new specification
        invalidatePMAEntry(riscv, object, index);
    }

    return getEffectivePMAAddr(object, index);
}

//
// Reset PMA registers
//
static void resetPMA(riscvP riscv, vmiosObjectP object) {

    Uns32 i;

    for(i=0; i<PMA_NUM; i++) {

        if(object->pmaaddr[i] || object->pmacfg.u8[i]) {

            // invalidate entry using its current specification
            invalidatePMAEntry(riscv, object, i);

            // reset entry fields
            object->pmaaddr[i]   = 0;
            object->pmacfg.u8[i] = 0;
        }
    }
}

//
// Indicate whether PMA protection is implemented
//
RISCV_PMA_ENABLE_FN(andesPMAEnable) {

    vmiosObjectP object = clientData;

    return RD_XCSR_FIELD(object, mmsc_cfg, DPMA);
}

//
// Implement PMA check for the given address range
//
RISCV_PMA_CHECK_FN(andesPMACheck) {

    vmiosObjectP object = clientData;

    // apply PMA-refined privileges
    if(RD_XCSR_FIELD(object, mmsc_cfg, DPMA)) {
        mapPMA(riscv, object, requiredPriv, lowPA, highPA);
    }
}


////////////////////////////////////////////////////////////////////////////////
// ILM/DLM SUPPORT
////////////////////////////////////////////////////////////////////////////////

//
// Return local memory size for memory configuration register
//
inline static Uns32 getLMSize(Uns32 LMSZ) {
    return LMSZ ? (0x200<<LMSZ) : 0;
}

//
// Return bounds of ILM or DLM
//
inline static void getLMBounds(
    Uns32  LMSZ,
    Uns64  mlmb,
    Uns64 *lowPAP,
    Uns64 *highPAP
) {
    // mask selecting BPA field from milmb/mdlmb
    static const CSR_REG_TYPE(mlmb) BPAmask = {u64:{fields:{BPA:-1}}};

    *lowPAP  = mlmb & BPAmask.u64.bits;
    *highPAP = *lowPAP + getLMSize(LMSZ) - 1;
}

//
// Return bounds of ILM
//
static void getILMBounds(vmiosObjectP object, Uns64 *lowPAP, Uns64 *highPAP) {
    getLMBounds(
        RD_XCSR_FIELD(object, micm_cfg, LMSZ),
        RD_XCSR(object, milmb),
        lowPAP,
        highPAP
    );
}

//
// Return bounds of DLM
//
static void getDLMBounds(vmiosObjectP object, Uns64 *lowPAP, Uns64 *highPAP) {
    getLMBounds(
        RD_XCSR_FIELD(object, mdcm_cfg, LMSZ),
        RD_XCSR(object, mdlmb),
        lowPAP,
        highPAP
    );
}

//
// Do memory ranges low1:high1 and low2:high2 overlap?
//
static Bool overlapRange(Uns64 low1, Uns64 high1, Uns64 low2, Uns64 high2) {
    return !((high1<low2) || (high2<low1));
}

//
// Do ILM and DLM ranges overlap?
//
static Bool LMOverlap(vmiosObjectP object) {

    Uns32 DLMSz = object->LM[False].bytes;
    Uns32 ILMSz = object->LM[True].bytes;
    Uns64 loDLM;
    Uns64 hiDLM;
    Uns64 loILM;
    Uns64 hiILM;

    // get local memory bounds
    getDLMBounds(object, &loDLM, &hiDLM);
    getILMBounds(object, &loILM, &hiILM);

    // do DLM and ILM ranges overlap?
    return DLMSz && ILMSz && overlapRange(loDLM, hiDLM, loILM, hiILM);
}

//
// Update local memory mapping when ILM/DLM is enabled or disabled or the given
// mode
//
static void updateLocalMemoryInt(
    vmiosObjectP object,
    riscvMode    mode,
    Bool         isCode,
    Bool         ILM,
    Bool         EN
) {
    riscvP     riscv       = object->riscv;
    memDomainP physDomain  = riscv->physDomains [mode][isCode];
    memDomainP uninstalled = object->physDomains[mode][isCode];
    memDomainP LMDomain    = object->LM[ILM].LMDomain;
    Uns64      loLM;
    Uns64      hiLM;

    // get local memory bounds and enable state
    if(ILM) {
        getILMBounds(object, &loLM, &hiLM);
    } else {
        getDLMBounds(object, &loLM, &hiLM);
    }

    if(EN) {

        // enable local memory
        vmirtAliasMemoryPriv(
            LMDomain,
            physDomain,
            0,
            hiLM-loLM,
            loLM,
            ILM ? MEM_PRIV_RWX : MEM_PRIV_RW
        );

    } else {

        // disable local memory
        vmirtAliasMemory(
            uninstalled,
            physDomain,
            loLM,
            hiLM,
            loLM,
            0
        );
    }
}

//
// Update local memory mapping when ILM/DLM is enabled or disabled
//
static void updateLocalMemory(vmiosObjectP object, Bool ILM, Bool EN) {

    Uns32 DLMSz = object->LM[False].bytes;
    Uns32 ILMSz = object->LM[True].bytes;

    // handle unconnected external ILM/DLM
    if((ILM && ILMSz) || (!ILM && DLMSz)) {

        riscvP    riscv = object->riscv;
        riscvMode mode;

        // debug action if required
        if(RISCV_DEBUG_MMU(riscv)) {

            Uns64 loLM;
            Uns64 hiLM;

            if(ILM) {
                getILMBounds(object, &loLM, &hiLM);
            } else {
                getDLMBounds(object, &loLM, &hiLM);
            }

            vmiPrintf(
                "%s %s 0x"FMT_6408x":0x"FMT_6408x"\n",
                EN  ? "ENABLE" : "DISABLE",
                ILM ? "ILM" : "DLM",
                loLM,
                hiLM
            );
        }

        // update mappings in all non-User modes
        for(mode=RISCV_MODE_S; mode<=RISCV_MODE_M; mode++) {

            if(!riscv->physDomains[mode][0]) {

                // ignore artifact mode

            } else if(LMOverlap(object)) {

                // ILM and DLM overlap - uninstall both ILM and DLM in both code
                // and data domains (NOTE: DLM does not affect code domain)
                updateLocalMemoryInt(object, mode, False, False, False);
                updateLocalMemoryInt(object, mode, False, True,  False);
                updateLocalMemoryInt(object, mode, True,  True,  False);

                // insert ILM in code and data domain (low priority)
                if(RD_XCSR_FIELD(object, milmb, EN)) {
                    updateLocalMemoryInt(object, mode, False, True,  True);
                    updateLocalMemoryInt(object, mode, True,  True,  True);
                }

                // insert DLM in data domain (high priority)
                if(RD_XCSR_FIELD(object, mdlmb, EN)) {
                    updateLocalMemoryInt(object, mode, False, False, True);
                }

            } else if(ILM) {

                // ILM enable change, in code and data domains
                updateLocalMemoryInt(object, mode, False, ILM, EN);
                updateLocalMemoryInt(object, mode, True,  ILM, EN);

            } else {

                // DLM enable change, in data domain only
                updateLocalMemoryInt(object, mode, False, ILM, EN);
            }
        }
    }
}

//
// Create ILM or DLM if required
//
static Uns32 createLocalMemory(
    vmiosObjectP          object,
    CSR_REG_TYPE(mcm_cfg) mcm_cfg,
    Bool                  isCode
) {
    Uns32 size = getLMSize(mcm_cfg.u32.fields.LMSZ);

    // save size of this local memory in bytes
    object->LM[isCode].bytes = size;

    // create local memory if required
    if(size) {

        // create local memory domain
        memDomainP LM = vmirtNewDomain(isCode ? "ILM" : "DLM", 32);

        // map it as RAM
        vmirtMapMemory(LM, 0, size-1, MEM_RAM);

        // save in structure
        object->LM[isCode].LMDomain = LM;
    }

    return size;
}

//
// Create local memory domain
//
static memDomainP createLMDomain(riscvMode mode, Uns32 bits, Bool isCode) {

    char name[64];

    // names for each mode
    static const char *modeNames[] = {
        [RISCV_MODE_U] = "User",
        [RISCV_MODE_S] = "Supervisor",
        [RISCV_MODE_H] = "Hypervisor",
        [RISCV_MODE_M] = "Machine",
    };

    // fill domain name
    sprintf(
        name, "%s %s %s",
        modeNames[mode],
        isCode ? "ILM" : "DLM",
        isCode ? "code" : "data"
    );

    // create the domain
    return vmirtNewDomain(name, bits);
}

//
// Create local memory physical alias domain for the given mode and access type
//
static void newLMDomain(vmiosObjectP object, riscvMode mode, Bool isCode) {

    riscvP     riscv = object->riscv;
    memDomainP base  = riscv->physDomains[mode][isCode];
    Uns32      bits  = vmirtGetDomainAddressBits(base);

    // create local memory domain
    memDomainP result = createLMDomain(mode, bits, isCode);

    // initially make it an alias of the physical domain
    vmirtAliasMemory(base, result, 0, getAddressMask(bits), 0, 0);

    // replace physical domain
    riscv->physDomains[mode][isCode] = result;
}

//
// Install local memory domains in the domain hierarchy
//
static void installLocalMemoryDomains(vmiosObjectP object) {

    riscvP    riscv = object->riscv;
    riscvMode mode;

    // create physical domain aliases for all non-User modes
    for(mode=RISCV_MODE_S; mode<=RISCV_MODE_M; mode++) {

        memDomainP dataDomain = riscv->physDomains[mode][0];
        memDomainP codeDomain = riscv->physDomains[mode][1];

        // save current physical domain to allow aliasing to it later
        object->physDomains[mode][0] = dataDomain;
        object->physDomains[mode][1] = codeDomain;

        if(dataDomain) {
            newLMDomain(object, mode, False);
            newLMDomain(object, mode, True);
        }
    }

    // use Supervisor aliases for User mode
    riscv->physDomains[RISCV_MODE_U][0] = riscv->physDomains[RISCV_MODE_S][0];
    riscv->physDomains[RISCV_MODE_U][1] = riscv->physDomains[RISCV_MODE_S][1];
}

//
// Install ILM/DLM domains if required
//
RISCV_PHYS_MEM_FN(andesInstallPhysicalMem) {

    vmiosObjectP object = clientData;

    // create local memories if required
    Uns32 ILMSize = createLocalMemory(object, object->csr.micm_cfg, True);
    Uns32 DLMSize = createLocalMemory(object, object->csr.mdcm_cfg, False);

    // if either local memory is present, insert ILM domains into the memory
    // domain hierarchy
    if(ILMSize || DLMSize) {
        installLocalMemoryDomains(object);
    }

    // enable ILM if required
    if(RD_XCSR_FIELD(object, milmb, EN)) {
        updateLocalMemory(object, True, True);
    }

    // enable DLM if required
    if(RD_XCSR_FIELD(object, mdlmb, EN)) {
        updateLocalMemory(object, False, True);
    }
}

//
// Write milmb (internal interface)
//
static Uns64 milmbWInt(vmiosObjectP object, Uns64 newValue) {

    Uns64 mask     = RD_XCSR_MASK(object, milmb);
    Uns64 oldValue = RD_XCSR(object, milmb);

    // update writable bits in register
    Bool oldEN = RD_XCSR_FIELD(object, milmb, EN);
    WR_XCSR(object, milmb, (newValue & mask) | (oldValue & ~mask));
    Bool newEN = RD_XCSR_FIELD(object, milmb, EN);

    // handle enable bit change
    if(oldEN != newEN) {
        updateLocalMemory(object, True, newEN);
    }

    return RD_XCSR(object, milmb);
}

//
// Write mdlmb (internal interface)
//
static Uns64 mdlmbWInt(vmiosObjectP object, Uns64 newValue) {

    Uns64 mask     = RD_XCSR_MASK(object, mdlmb);
    Uns64 oldValue = RD_XCSR(object, mdlmb);

    // update writable bits in register
    Bool oldEN = RD_XCSR_FIELD(object, mdlmb, EN);
    WR_XCSR(object, mdlmb, (newValue & mask) | (oldValue & ~mask));
    Bool newEN = RD_XCSR_FIELD(object, mdlmb, EN);

    // handle enable bit change
    if(oldEN != newEN) {
        updateLocalMemory(object, False, newEN);
    }

    return RD_XCSR(object, mdlmb);
}

//
// Write milmb
//
static RISCV_CSR_WRITEFN(milmbW) {
    return milmbWInt(attrs->object, newValue);
}

//
// Write mdlmb
//
static RISCV_CSR_WRITEFN(mdlmbW) {
    return mdlmbWInt(attrs->object, newValue);
}


////////////////////////////////////////////////////////////////////////////////
// MXSTATUS STATE UPDATE
////////////////////////////////////////////////////////////////////////////////

//
// Copy a field in a CSR to another field
//
#define COPY_FIELD(_OBJECT, _REG, _DST, _SRC) \
    WR_XCSR_FIELD(_OBJECT, _REG, _DST, RD_XCSR_FIELD(_OBJECT, _REG, _SRC))

//
// Notifier called when trap is taken
//
static RISCV_TRAP_NOTIFIER_FN(trapNotifier) {

    vmiosObjectP object = clientData;

    // acknowledge interrupt if required
    andesAcknowledgeInterrupt(object);

    if(mode==RISCV_MODE_MACHINE) {

        // preserve mxstatus fields when trap is taken
        COPY_FIELD(object, mxstatus, PPFT_EN, PFT_EN);
        COPY_FIELD(object, mxstatus, PIME,    IME);
        COPY_FIELD(object, mxstatus, PDME,    DME);

        // clear mxstatus.PFT_EN if required
        if(RD_XCSR_FIELD(object, mpft_ctl, FAST_INT)) {
            WR_XCSR_FIELD(object, mxstatus, PFT_EN, 0);
        }
    }

    // adjust base for active instruction counters take into account whether
    // the instruction causing the trap has retired
    if(!isInterrupt(riscv->exception)) {
        refreshCountersNotRetired(object);
    }

    // refresh all counter objects
    refreshCounters(object);
}

//
// Notifier called on return from trap
//
static RISCV_TRAP_NOTIFIER_FN(ERETNotifier) {

    vmiosObjectP object = clientData;

    if(mode==RISCV_MODE_MACHINE) {

        // restore mxstatus fields when MRET is executed
        COPY_FIELD(object, mxstatus, PFT_EN, PPFT_EN);
        COPY_FIELD(object, mxstatus, IME,    PIME);
        COPY_FIELD(object, mxstatus, DME,    PDME);
    }

    // refresh all counter objects
    refreshCounters(object);
}


////////////////////////////////////////////////////////////////////////////////
// USER MODE CCTL ACCESS
////////////////////////////////////////////////////////////////////////////////

//
// Enumeration of CCTL commands
//
typedef enum CCTLCmdE {
    CCTLC_L1D_VA_INVAL    = 0,
    CCTLC_L1D_VA_WB       = 1,
    CCTLC_L1D_VA_WBINVAL  = 2,
    CCTLC_L1D_VA_LOCK     = 3,
    CCTLC_L1D_VA_UNLOCK   = 4,
    CCTLC_L1D_WBINVAL_ALL = 6,
    CCTLC_L1D_WB_ALL      = 7,
    CCTLC_L1I_VA_INVAL    = 8,
    CCTLC_L1I_VA_LOCK     = 11,
    CCTLC_L1I_VA_UNLOCK   = 12,
    CCTLC_L1D_IX_INVAL    = 16,
    CCTLC_L1D_IX_WB       = 17,
    CCTLC_L1D_IX_WBINVAL  = 18,
    CCTLC_L1D_IX_RTAG     = 19,
    CCTLC_L1D_IX_RDATA    = 20,
    CCTLC_L1D_IX_WTAG     = 21,
    CCTLC_L1D_IX_WDATA    = 22,
    CCTLC_L1D_INVAL_ALL   = 23,
    CCTLC_L1I_IX_INVAL    = 24,
    CCTLC_L1I_IX_RTAG     = 27,
    CCTLC_L1I_IX_RDATA    = 28,
    CCTLC_L1I_IX_WTAG     = 29,
    CCTLC_L1I_IX_WDATA    = 30,
    CCTLC_LAST            = 32      // KEEP LAST: for sizing
} CCTLCmd;

//
// Return a Boolean indicating whether User CCTL access is possible (and take
// Illegal Instruction trap if not)
//
static Bool accessUserCCTL(vmiosObjectP object, riscvP riscv) {

    if(riscv->artifactAccess) {

        // all artifact accesses are allowed
        return True;

    } else if(getCurrentMode3(riscv)==RISCV_MODE_MACHINE) {

        // access always possible in Machine mode
        return True;

    } else if(RD_XCSR_FIELD(object, mcache_ctl, CCTL_SUEN)) {

        // access possible in Supervisor and User mode if mcache_ctl.CCTL_SUEN=1
        return True;

    } else {

        // take Illegal Instruction exception
        andesIllegalInstruction(riscv);
        return False;
    }
}

//
// Return a Boolean indicating whether User CCTL command is possible (and take
// Illegal Instruction trap if not)
//
static Bool accessUserCCTLCmd(vmiosObjectP object, riscvP riscv, CCTLCmd cmd) {

    // legal commands in User mode
    static const Bool map[CCTLC_LAST] = {
        [CCTLC_L1D_VA_INVAL]   = True,
        [CCTLC_L1D_VA_WB]      = True,
        [CCTLC_L1D_VA_WBINVAL] = True,
        [CCTLC_L1I_VA_INVAL]   = True,
    };

    if(riscv->artifactAccess) {

        // all artifact accesses are allowed
        return True;

    } else if(!accessUserCCTL(object, riscv)) {

        // access not enabled in User or Supervisor mode
        return False;

    } else if(getCurrentMode3(riscv)!=RISCV_MODE_USER) {

        // access legal if in Machine or Supervisor mode
        return True;

    } else if(map[cmd]) {

        // legal User command
        return True;

    } else {

        // take Illegal Instruction exception
        andesIllegalInstruction(riscv);
        return False;
    }
}

//
// Write ucctlbeginaddr
//
static RISCV_CSR_WRITEFN(ucctlbeginaddrW) {

    vmiosObjectP object = attrs->object;

    if(accessUserCCTL(object, riscv)) {
        WR_XCSR(object, ucctlbeginaddr, newValue);
    } else {
        newValue = RD_XCSR(object, ucctlbeginaddr);
    }

    return newValue;
}

//
// Read ucctlbeginaddr
//
static RISCV_CSR_READFN(ucctlbeginaddrR) {

    vmiosObjectP object = attrs->object;

    return accessUserCCTL(object, riscv) ? RD_XCSR(object, ucctlbeginaddr) : 0;
}

//
// Write ucctlcommand
//
static RISCV_CSR_WRITEFN(ucctlcommandW) {

    vmiosObjectP object = attrs->object;
    CCTLCmd      cmd    = newValue & WM32_mcctlcommand;

    if(accessUserCCTLCmd(object, riscv, cmd)) {
        WR_XCSR(object, ucctlcommand, newValue);
    } else {
        cmd = RD_XCSR(object, ucctlcommand);
    }

    return cmd;
}

//
// Read ucctlcommand
//
static RISCV_CSR_READFN(ucctlcommandR) {

    vmiosObjectP object = attrs->object;

    return accessUserCCTL(object, riscv) ? RD_XCSR(object, ucctlcommand) : 0;
}


////////////////////////////////////////////////////////////////////////////////
// PHYSICAL MEMORY ATTRIBUTE REGISTERS
////////////////////////////////////////////////////////////////////////////////

//
// Return index of the given pmacfg register
//
inline static Uns32 getPMACFGId(riscvCSRAttrsCP attrs) {
    return attrs->csrNum - 0xBC0;
}

//
// Return index of the given pmaaddr register
//
inline static Uns32 getPMAADDRId(riscvCSRAttrsCP attrs) {
    return attrs->csrNum - 0xBD0;
}

//
// Read pmpcfg0-pmpcfg3
//
static RISCV_CSR_READFN(pmacfgR) {

    vmiosObjectP object = attrs->object;

    return readPMACFG(riscv, object, getPMACFGId(attrs));
}

//
// Write pmpcfg0-pmpcfg3
//
static RISCV_CSR_WRITEFN(pmacfgW) {

    vmiosObjectP object = attrs->object;

    return writePMACFG(riscv, object, getPMACFGId(attrs), newValue);
}

//
// Read pmpaddr0-pmpaddr15
//
static RISCV_CSR_READFN(pmaaddrR) {

    vmiosObjectP object = attrs->object;

    return readPMAAddr(riscv, object, getPMAADDRId(attrs));
}

//
// Write pmpaddr0-pmpaddr15
//
static RISCV_CSR_WRITEFN(pmaaddrW) {

    vmiosObjectP object = attrs->object;

    return writePMAAddr(riscv, object, getPMAADDRId(attrs), newValue);
}


////////////////////////////////////////////////////////////////////////////////
// MACROS FOR IMPLEMENTED CSRS
////////////////////////////////////////////////////////////////////////////////

//
// Implemented using callbacks only, append number
//
#define XCSR_ATTR_P__NUM( \
    _ID, _NUM, _I, _ARCH, _EXT, _ENDB,_ENDRM,_NOTR,_TVMT, _DESC, \
    _RCB, _RWCB, _WCB                                \
) \
    XCSR_ATTR_P__( \
        _ID##_I, _NUM+_I, _ARCH, _EXT, _ENDB,_ENDRM,_NOTR,_TVMT, _DESC, \
        _RCB, _RWCB, _WCB                                               \
    )

//
// Implemented using callbacks only, numbers 3..6
//
#define XCSR_ATTR_P__3_6( \
    _ID, _NUM, _ARCH, _EXT, _ENDB,_ENDRM,_NOTR,_TVMT, _DESC, _RCB, _RWCB, _WCB \
) \
    XCSR_ATTR_P__NUM(_ID, _NUM,  3, _ARCH, _EXT, _ENDB,_ENDRM,_NOTR,_TVMT, _DESC, _RCB, _RWCB, _WCB), \
    XCSR_ATTR_P__NUM(_ID, _NUM,  4, _ARCH, _EXT, _ENDB,_ENDRM,_NOTR,_TVMT, _DESC, _RCB, _RWCB, _WCB), \
    XCSR_ATTR_P__NUM(_ID, _NUM,  5, _ARCH, _EXT, _ENDB,_ENDRM,_NOTR,_TVMT, _DESC, _RCB, _RWCB, _WCB), \
    XCSR_ATTR_P__NUM(_ID, _NUM,  6, _ARCH, _EXT, _ENDB,_ENDRM,_NOTR,_TVMT, _DESC, _RCB, _RWCB, _WCB)

//
// Implemented using callbacks only, numbers 0..15
//
#define XCSR_ATTR_P__0_15( \
    _ID, _NUM, _ARCH, _EXT, _ENDB,_ENDRM,_NOTR,_TVMT, _DESC, _RCB, _RWCB, _WCB \
) \
    XCSR_ATTR_P__NUM(_ID, _NUM,  0, _ARCH, _EXT, _ENDB,_ENDRM,_NOTR,_TVMT, _DESC, _RCB, _RWCB, _WCB), \
    XCSR_ATTR_P__NUM(_ID, _NUM,  1, _ARCH, _EXT, _ENDB,_ENDRM,_NOTR,_TVMT, _DESC, _RCB, _RWCB, _WCB), \
    XCSR_ATTR_P__NUM(_ID, _NUM,  2, _ARCH, _EXT, _ENDB,_ENDRM,_NOTR,_TVMT, _DESC, _RCB, _RWCB, _WCB), \
    XCSR_ATTR_P__NUM(_ID, _NUM,  3, _ARCH, _EXT, _ENDB,_ENDRM,_NOTR,_TVMT, _DESC, _RCB, _RWCB, _WCB), \
    XCSR_ATTR_P__NUM(_ID, _NUM,  4, _ARCH, _EXT, _ENDB,_ENDRM,_NOTR,_TVMT, _DESC, _RCB, _RWCB, _WCB), \
    XCSR_ATTR_P__NUM(_ID, _NUM,  5, _ARCH, _EXT, _ENDB,_ENDRM,_NOTR,_TVMT, _DESC, _RCB, _RWCB, _WCB), \
    XCSR_ATTR_P__NUM(_ID, _NUM,  6, _ARCH, _EXT, _ENDB,_ENDRM,_NOTR,_TVMT, _DESC, _RCB, _RWCB, _WCB), \
    XCSR_ATTR_P__NUM(_ID, _NUM,  7, _ARCH, _EXT, _ENDB,_ENDRM,_NOTR,_TVMT, _DESC, _RCB, _RWCB, _WCB), \
    XCSR_ATTR_P__NUM(_ID, _NUM,  8, _ARCH, _EXT, _ENDB,_ENDRM,_NOTR,_TVMT, _DESC, _RCB, _RWCB, _WCB), \
    XCSR_ATTR_P__NUM(_ID, _NUM,  9, _ARCH, _EXT, _ENDB,_ENDRM,_NOTR,_TVMT, _DESC, _RCB, _RWCB, _WCB), \
    XCSR_ATTR_P__NUM(_ID, _NUM, 10, _ARCH, _EXT, _ENDB,_ENDRM,_NOTR,_TVMT, _DESC, _RCB, _RWCB, _WCB), \
    XCSR_ATTR_P__NUM(_ID, _NUM, 11, _ARCH, _EXT, _ENDB,_ENDRM,_NOTR,_TVMT, _DESC, _RCB, _RWCB, _WCB), \
    XCSR_ATTR_P__NUM(_ID, _NUM, 12, _ARCH, _EXT, _ENDB,_ENDRM,_NOTR,_TVMT, _DESC, _RCB, _RWCB, _WCB), \
    XCSR_ATTR_P__NUM(_ID, _NUM, 13, _ARCH, _EXT, _ENDB,_ENDRM,_NOTR,_TVMT, _DESC, _RCB, _RWCB, _WCB), \
    XCSR_ATTR_P__NUM(_ID, _NUM, 14, _ARCH, _EXT, _ENDB,_ENDRM,_NOTR,_TVMT, _DESC, _RCB, _RWCB, _WCB), \
    XCSR_ATTR_P__NUM(_ID, _NUM, 15, _ARCH, _EXT, _ENDB,_ENDRM,_NOTR,_TVMT, _DESC, _RCB, _RWCB, _WCB)

//
// CSR table
//
static const extCSRAttrs csrs[XCSR_ID(LAST)] = {

    //                 name                num    arch         extension       attrs     description                                      rCB              rwCB wCB
    XCSR_ATTR_P__     (cycle,              0xC00, 0,           ANV_PMNDS,      1,0,1,0,  "Cycle Counter",                                 hpmR,            0,   hpmW           ),
    XCSR_ATTR_P__     (time,               0xC01, 0,           ANV_PMNDS,      1,0,1,0,  "Timer",                                         timeR,           0,   0              ),
    XCSR_ATTR_P__     (instret,            0xC02, 0,           ANV_PMNDS,      1,0,1,0,  "Instructions Retired",                          hpmR,            0,   hpmW           ),
    XCSR_ATTR_P__3_6  (hpmcounter,         0xC00, 0,           ANV_PMNDS,      1,0,1,0,  "Performance Monitor Counter ",                  hpmR,            0,   hpmW           ),
    XCSR_ATTR_P__     (cycleh,             0xC80, ISA_XLEN_32, ANV_PMNDS,      1,0,1,0,  "Cycle Counter High",                            hpmhR,           0,   hpmhW          ),
    XCSR_ATTR_P__     (timeh,              0xC81, ISA_XLEN_32, ANV_PMNDS,      1,0,1,0,  "Timer High",                                    timehR,          0,   0              ),
    XCSR_ATTR_P__     (instreth,           0xC82, ISA_XLEN_32, ANV_PMNDS,      1,0,1,0,  "Instructions Retired High",                     hpmhR,           0,   hpmhW          ),
    XCSR_ATTR_P__3_6  (hpmcounterh,        0xC80, ISA_XLEN_32, ANV_PMNDS,      1,0,1,0,  "Performance Monitor High ",                     hpmhR,           0,   hpmhW          ),

    XCSR_ATTR_P__     (mcycle,             0xB00, 0,           ANV_PMNDS,      1,0,1,0,  "Machine Cycle Counter",                         mhpmR,           0,   mhpmW          ),
    XCSR_ATTR_P__     (minstret,           0xB02, 0,           ANV_PMNDS,      1,0,1,0,  "Machine Instructions Retired",                  mhpmR,           0,   mhpmW          ),
    XCSR_ATTR_P__3_6  (mhpmcounter,        0xB00, 0,           ANV_PMNDS,      0,0,0,0,  "Machine Performance Monitor Counter ",          mhpmR,           0,   mhpmW          ),
    XCSR_ATTR_P__     (mcycleh,            0xB80, ISA_XLEN_32, ANV_PMNDS,      1,0,1,0,  "Machine Cycle Counter High",                    mhpmhR,          0,   mhpmhW         ),
    XCSR_ATTR_P__     (minstreth,          0xB82, ISA_XLEN_32, ANV_PMNDS,      1,0,1,0,  "Machine Instructions Retired High",             mhpmhR,          0,   mhpmhW         ),
    XCSR_ATTR_P__3_6  (mhpmcounterh,       0xB80, ISA_XLEN_32, ANV_PMNDS,      0,0,0,0,  "Machine Performance Monitor Counter High ",     mhpmhR,          0,   mhpmhW         ),
    XCSR_ATTR_P__3_6  (mhpmevent,          0x320, 0,           ANV_PMNDS,      0,0,0,0,  "Machine Performance Monitor Event Select ",     mhpmeventR,      0,   mhpmeventW     ),

    //                 name                num    arch         extension       attrs     description                                      rCB              rwCB wCB
    XCSR_ATTR_TV_     (milmb,              0x7C0, 0,           ANV_ILMB,       0,0,0,0,  "Instruction Local Memory Base",                 0,               0,   milmbW         ),
    XCSR_ATTR_TV_     (mdlmb,              0x7C1, 0,           ANV_DLMB,       0,0,0,0,  "Data Local Memory Base",                        0,               0,   mdlmbW         ),
    XCSR_ATTR_T__     (micm_cfg,           0xFC0, 0,           ANV_NA,         0,0,0,0,  "Instruction Cache/Memory Configuration",        0,               0,   0              ),
    XCSR_ATTR_T__     (mdcm_cfg,           0xFC1, 0,           ANV_NA,         0,0,0,0,  "Data Cache/Memory Configuration",               0,               0,   0              ),
    XCSR_ATTR_T__     (mmsc_cfg,           0xFC2, 0,           ANV_NA,         0,0,0,0,  "Miscellaneous Configuration",                   0,               0,   0              ),
    XCSR_ATTR_TH_     (mmsc_cfg2,mmsc_cfg, 0xFC3, ISA_XLEN_32, ANV_MSC_EXT,    0,0,0,0,  "Miscellaneous Configuration 2",                 0,               0,   0              ),
    XCSR_ATTR_T__     (mvec_cfg,           0xFC7, ISA_V,       ANV_VECCFG,     0,0,0,0,  "Vector Configuration",                          0,               0,   0              ),
    XCSR_ATTR_T__     (ml2c_ctl_base,      0xFCF, 0,           ANV_L2C_BASE,   0,0,0,0,  "L2-Cache Control Base Register",                0,               0,   0              ),

    //                 name                num    arch         extension       attrs     description                                      rCB              rwCB wCB
    XCSR_ATTR_TC_     (mnvec,              0x7C3, 0,           ANV_NA,         0,0,0,0,  "NMI Vector Base Address",                       0,               0,   0              ),
    XCSR_ATTR_TC_     (mpft_ctl,           0x7C5, 0,           ANV_PFT,        0,0,0,0,  "Performance Throttling Control",                0,               0,   0              ),
    XCSR_ATTR_TV_     (mcache_ctl,         0x7CA, 0,           ANV_SZ,         0,0,0,0,  "Cache Control",                                 0,               0,   0              ),
    XCSR_ATTR_TC_     (mcctlbeginaddr,     0x7CB, 0,           ANV_CCTLCSR_SZ, 0,0,0,0,  "Machine CCTL Begin Address (register only)",    0,               0,   0              ),
    XCSR_ATTR_TC_     (mcctlcommand,       0x7CC, 0,           ANV_CCTLCSR_SZ, 0,0,0,0,  "Machine CCTL Command (register only)",          0,               0,   0              ),
    XCSR_ATTR_TC_     (mcctldata,          0x7CD, 0,           ANV_CCTLCSR_SZ, 0,0,0,0,  "Machine CCTL Data (register only)",             0,               0,   0              ),
    XCSR_ATTR_TC_     (mmisc_ctl,          0x7D0, 0,           ANV_NA,         0,0,0,0,  "Machine Miscellaneous Control",                 0,               0,   mmisc_ctlW     ),

    //                 name                num    arch         extension       attrs     description                                      rCB              rwCB wCB
    XCSR_ATTR_TV_     (mxstatus,           0x7C4, 0,           ANV_NA,         0,0,0,0,  "Machine Extended Status",                       0,               0,   0              ),
    XCSR_ATTR_P__     (mdcause,            0x7C9, 0,           ANV_NA,         0,0,0,0,  "Machine Detailed Trap Cause",                   mdcauseR,        0,   mdcauseW       ),

    //                 name                num    arch         extension       attrs     description                                      rCB              rwCB wCB
    XCSR_ATTR_TC_     (mhsp_ctl,           0x7C6, 0,           ANV_HSP,        1,0,0,0,  "Machine Hardware Stack Protection Control",     0,               0,   mhsp_ctlW      ),
    XCSR_ATTR_TC_     (msp_bound,          0x7C7, 0,           ANV_HSP,        1,0,0,0,  "Machine SP Bound",                              0,               0,   0              ),
    XCSR_ATTR_TC_     (msp_base,           0x7C8, 0,           ANV_HSP,        1,0,0,0,  "Machine SP Base",                               0,               0,   0              ),

    //                 name                num    arch         extension       attrs     description                                      rCB              rwCB wCB
    XCSR_ATTR_TV_     (mcounterwen,        0x7CE, ISA_U,       ANV_PMNDS,      0,0,0,0,  "Machine Counter Write Enable",                  0,               0,   0              ),
    XCSR_ATTR_TV_     (mcounterinten,      0x7CF, 0,           ANV_PMNDS,      0,0,0,0,  "Machine Counter Interrupt Enable",              0,               0,   mcounterintenW ),
    XCSR_ATTR_TV_     (mcountermask_m,     0x7D1, ISA_U,       ANV_PMNDS,      0,0,0,0,  "Machine Counter Mask for Machine Mode",         0,               0,   mcountermask_mW),
    XCSR_ATTR_TV_     (mcountermask_s,     0x7D2, ISA_S,       ANV_PMNDS,      0,0,0,0,  "Machine Counter Mask for Supervisor Mode",      0,               0,   0              ),
    XCSR_ATTR_TV_     (mcountermask_u,     0x7D3, ISA_U,       ANV_PMNDS,      0,0,0,0,  "Machine Counter Mask for User Mode",            0,               0,   0              ),
    XCSR_ATTR_TV_     (mcounterovf,        0x7D4, 0,           ANV_PMNDS,      0,0,0,0,  "Machine Counter Overflow Status",               0,               0,   mcounterovfW   ),

    //                 name                num    arch         extension       attrs     description                                      rCB              rwCB wCB
    XCSR_ATTR_P__     (scounterinten,      0x9CF, ISA_S,       ANV_PMNDS,      0,0,0,0,  "Supervisor Counter Interrupt Enable",           0,               0,   0              ),
    XCSR_ATTR_P__     (scountermask_m,     0x9D1, ISA_S,       ANV_PMNDS,      0,0,0,0,  "Supervisor Counter Mask for Machine Mode",      0,               0,   0              ),
    XCSR_ATTR_P__     (scountermask_s,     0x9D2, ISA_S,       ANV_PMNDS,      0,0,0,0,  "Supervisor Counter Mask for Supervisor Mode",   0,               0,   0              ),
    XCSR_ATTR_P__     (scountermask_u,     0x9D3, ISA_S,       ANV_PMNDS,      0,0,0,0,  "Supervisor Counter Mask for User Mode",         0,               0,   0              ),
    XCSR_ATTR_P__     (scounterovf,        0x9D4, ISA_S,       ANV_PMNDS,      0,0,0,0,  "Supervisor Counter Overflow Status",            0,               0,   0              ),
    XCSR_ATTR_P__3_6  (shpmevent,          0x9E0, ISA_S,       ANV_PMNDS,      0,0,0,0,  "Supervisor Performance Monitor Event Select ",  0,               0,   0              ),

    //                 name                num    arch         extension       attrs     description                                      rCB              rwCB wCB
    XCSR_ATTR_TV_     (uitb,               0x800, 0,           ANV_ECD,        0,0,0,0,  "Instruction Table Base Address",                0,               0,   0              ),
    XCSR_ATTR_P__     (ucctlbeginaddr,     0x80B, ISA_U,       ANV_CCTLCSR_SZ, 1,0,0,0,  "User CCTL Begin Address (register only)",       ucctlbeginaddrR, 0,   ucctlbeginaddrW),
    XCSR_ATTR_P__     (ucctlcommand,       0x80C, ISA_U,       ANV_CCTLCSR_SZ, 1,0,0,0,  "User CCTL Command (register only)",             ucctlcommandR,   0,   ucctlcommandW  ),

    //                 name                num    arch         extension       attrs     description                                      rCB              rwCB wCB
    XCSR_ATTR_P__     (pmacfg0,            0xBC0, 0,           ANV_DPMA,       0,0,0,0,  "Physical Memory Attributes Configuration 0",    pmacfgR,         0,   pmacfgW        ),
    XCSR_ATTR_P__     (pmacfg1,            0xBC1, ISA_XLEN_32, ANV_DPMA,       0,0,0,0,  "Physical Memory Attributes Configuration 1",    pmacfgR,         0,   pmacfgW        ),
    XCSR_ATTR_P__     (pmacfg2,            0xBC2, 0,           ANV_DPMA,       0,0,0,0,  "Physical Memory Attributes Configuration 2",    pmacfgR,         0,   pmacfgW        ),
    XCSR_ATTR_P__     (pmacfg3,            0xBC3, ISA_XLEN_32, ANV_DPMA,       0,0,0,0,  "Physical Memory Attributes Configuration 3",    pmacfgR,         0,   pmacfgW        ),
    XCSR_ATTR_P__0_15 (pmaaddr,            0xBD0, 0,           ANV_DPMA,       0,0,0,0,  "Physical Memory Attributes Word Address ",      pmaaddrR,        0,   pmaaddrW       ),
};


////////////////////////////////////////////////////////////////////////////////
// INITIALIZATION
////////////////////////////////////////////////////////////////////////////////

// set mask to the given value in 32-bit CSR mask
#define SET_CSR_MASK_V_32(_OBJ, _RNAME, _VALUE) \
    (_OBJ)->csrMask._RNAME.u32.bits = _VALUE

// set mask to the given value in 64-bit CSR mask
#define SET_CSR_MASK_V_64(_OBJ, _RNAME, _VALUE) \
    (_OBJ)->csrMask._RNAME.u64.bits = _VALUE

// set mask to the given value in all CSR masks
#define SET_CSR_MASK_V(_OBJ, _RNAME, _VALUE) \
    SET_CSR_MASK_V_32(_OBJ, _RNAME, _VALUE); \
    SET_CSR_MASK_V_64(_OBJ, _RNAME, _VALUE)

// set field mask to the given value in 32-bit CSR mask
#define SET_CSR_FIELD_MASK_V_32(_OBJ, _RNAME, _FIELD, _VALUE) \
    (_OBJ)->csrMask._RNAME.u32.fields._FIELD = _VALUE

// set field mask to the given value in 64-bit CSR mask
#define SET_CSR_FIELD_MASK_V_64(_OBJ, _RNAME, _FIELD, _VALUE) \
    (_OBJ)->csrMask._RNAME.u64.fields._FIELD = _VALUE

// set field mask to the given value in all CSR masks
#define SET_CSR_FIELD_MASK_V(_OBJ, _RNAME, _FIELD, _VALUE) \
    SET_CSR_FIELD_MASK_V_32(_OBJ, _RNAME, _FIELD, _VALUE); \
    SET_CSR_FIELD_MASK_V_64(_OBJ, _RNAME, _FIELD, _VALUE)

//
// Validate the presence of one extension
//
#define EXTENSION_CHECK(_OBJ, _REQUIRED, _REG, _EXT) \
    if((_REQUIRED & ANV_##_EXT) && !RD_XCSR_FIELD(object, _REG, _EXT)) {    \
        return False;                                                       \
    }

//
// Validate the presence of one extension, mismatched field name
//
#define EXTENSION_CHECK_FIELD(_OBJ, _REQUIRED, _REG, _EXT, _FIELD) \
    if((_REQUIRED & ANV_##_EXT) && !RD_XCSR_FIELD(object, _REG, _FIELD)) {  \
        return False;                                                       \
    }

//
// Validate the presence of either of two I/D extensions
//
#define EXTENSION_CHECK_ID(_OBJ, _REQUIRED, _REG1, _REG2, _EXT) \
    if(                                                                     \
        (_REQUIRED & ANV_##_EXT) &&                                         \
        !RD_XCSR_FIELD(object, _REG1, _EXT) &&                              \
        !RD_XCSR_FIELD(object, _REG2, _EXT)                                 \
    ) {                                                                     \
        return False;                                                       \
    }

//
// Indicate whether the indicate extension or extensions are present
//
static Bool extensionPresent(vmiosObjectP object, andesVariant required) {

    // validate mmsc_cfg-controlled register presence
    EXTENSION_CHECK(object, required, mmsc_cfg, ECD);
    EXTENSION_CHECK(object, required, mmsc_cfg, EV5MPE);
    EXTENSION_CHECK(object, required, mmsc_cfg, HSP);
    EXTENSION_CHECK(object, required, mmsc_cfg, PFT);
    EXTENSION_CHECK(object, required, mmsc_cfg, CCTLCSR);
    EXTENSION_CHECK(object, required, mmsc_cfg, MSC_EXT);
    EXTENSION_CHECK(object, required, mmsc_cfg, BF16CVT);
    EXTENSION_CHECK(object, required, mmsc_cfg, ZFH);
    EXTENSION_CHECK(object, required, mmsc_cfg, VL4);
    EXTENSION_CHECK(object, required, mmsc_cfg, DPMA);
    EXTENSION_CHECK(object, required, mmsc_cfg, PMNDS);
    EXTENSION_CHECK(object, required, mmsc_cfg, VPFH);
    EXTENSION_CHECK(object, required, mmsc_cfg, VECCFG);
    EXTENSION_CHECK(object, required, mmsc_cfg, L2CMP_CFG);
    EXTENSION_CHECK(object, required, mmsc_cfg, L2C);

    // validate micm_cfg-controlled register presence
    EXTENSION_CHECK_FIELD(object, required, micm_cfg, ILMB, LMB);

    // validate mdcm_cfg-controlled register presence
    EXTENSION_CHECK_FIELD(object, required, mdcm_cfg, DLMB, LMB);

    // validate micm_cfg/mdcm_cfg-controlled register presence
    EXTENSION_CHECK_ID(object, required, micm_cfg, mdcm_cfg, SZ);

    return True;
}

//
// Reset Andes-specific CSRs
//
static RISCV_RESET_NOTIFIER_FN(CSRReset) {

    vmiosObjectP object = clientData;

    // reset mmsc_cfg.HSP-controlled registers
    if(RD_XCSR_FIELD(object, mmsc_cfg, HSP)) {
        WR_XCSR(object, mhsp_ctl,   0);
        WR_XCSR(object, msp_bound, -1);
        WR_XCSR(object, msp_base,  -1);
    }

    // reset mmsc_cfg.PMNDS-controlled state
    if(RD_XCSR_FIELD(object, mmsc_cfg, PMNDS)) {

        // reset mmsc_cfg.PMNDS-controlled registers
        WR_XCSR(object, mcounterwen,    0);
        WR_XCSR(object, mcounterinten,  0);
        WR_XCSR(object, mcountermask_m, 0);
        WR_XCSR(object, mcountermask_s, 0);
        WR_XCSR(object, mcountermask_u, 0);
        WR_XCSR(object, mcounterovf,    0);

        // reset configurable counters
        resetCounters(object);

        // refresh all counter objects
        refreshCounters(object);
    }

    // reset micm_cfg.ILMB-controlled registers
    if(RD_XCSR_FIELD(object, micm_cfg, LMB)) {
        milmbWInt(object, object->csrDefaults.csr.milmb.u64.bits);
    }

    // reset mdcm_cfg.DLMB-controlled registers
    if(RD_XCSR_FIELD(object, mdcm_cfg, LMB)) {
        mdlmbWInt(object, object->csrDefaults.csr.mdlmb.u64.bits);
    }

    // reset PMA registers
    resetPMA(riscv, object);

    // reset ACE extension state
    andesACEReset(object);

    // update block mask
    updateBlockMask(riscv, object);
}

//
// Initialize CSR state
//
void andesCSRInit(vmiosObjectP object) {

    riscvP        riscv    = object->riscv;
    riscvP        parent   = riscv->parent ? riscv->parent : riscv;
    riscvConfigCP rvConfig = &riscv->configInfo;
    extCSRId      id;

    // processor is non-standard because interrupt mode is not determined by
    // MODE field in mtvec etc, and is instead obtained from mmisc_ctl.VEC_PLIC
    SET_CSR_FIELD_MASK_V(riscv, mtvec, MODE, 0);
    SET_CSR_FIELD_MASK_V(riscv, stvec, MODE, 0);
    SET_CSR_FIELD_MASK_V(riscv, utvec, MODE, 0);

    // initialize M-mode counter write masks with mcounteren mask (excluding TM
    // bit, which is never writeable)
    Uns32 mcounterMask = RD_CSR_MASKC(riscv, mcounteren) & ~(1<<1);
    SET_CSR_MASK_V(object, mcounterwen,    mcounterMask);
    SET_CSR_MASK_V(object, mcounterinten,  mcounterMask);
    SET_CSR_MASK_V(object, mcountermask_m, mcounterMask);
    SET_CSR_MASK_V(object, mcountermask_s, mcounterMask);
    SET_CSR_MASK_V(object, mcountermask_u, mcounterMask);
    SET_CSR_MASK_V(object, mcounterovf,    mcounterMask);

    // initialize read-only configuration register and pair
    WR_XCSR64(object, mmsc_cfg, object->csrDefaults.csr.mmsc_cfg.u64.bits);

    // initialize read-only configuration registers
    WR_XCSR(object, micm_cfg, object->csrDefaults.csr.micm_cfg.u64.bits);
    WR_XCSR(object, mdcm_cfg, object->csrDefaults.csr.mdcm_cfg.u64.bits);
    WR_XCSR(object, mvec_cfg, object->csrDefaults.csr.mvec_cfg.u32.bits);

    // initialize MP registers and fields
    WR_XCSR(object, ml2c_ctl_base, object->csrDefaults.csr.ml2c_ctl_base.u64.bits);
    if (RD_XCSR_FIELD(object, mmsc_cfg, L2CMP_CFG) && parent->numHarts > 0) {
        WR_XCSR_FIELD(object, mmsc_cfg, CORE_PCLUS, parent->numHarts-1);
    }

    // initialize registers without defined reset value
    WR_XCSR(object, mnvec, rvConfig->nmi_address);
    WR_XCSR(object, uitb,  object->csrDefaults.csr.uitb.u64.bits);

    // initialize write masks
    SET_CSR_MASK_V(object, milmb, object->csrDefaults.csrMask.milmb.u64.bits);
    SET_CSR_MASK_V(object, mdlmb, object->csrDefaults.csrMask.mdlmb.u64.bits);

    // initialize milmb and mdlmb with configured value
    WR_XCSR(object, milmb, object->csrDefaults.csr.milmb.u64.bits);
    WR_XCSR(object, mdlmb, object->csrDefaults.csr.mdlmb.u64.bits);

    // uitb write mask depends on the fixed value of uitb.HW
    if(!RD_XCSR_FIELD(object, uitb, HW)) {
        SET_CSR_FIELD_MASK_V(object, uitb, ADDR, -1);
    }

    // set fields in mxstatus mask dependent on instruction cache & local memory
    if(RD_XCSR(object, micm_cfg)) {
        SET_CSR_FIELD_MASK_V(object, mxstatus, IME,  -1);
        SET_CSR_FIELD_MASK_V(object, mxstatus, PIME, -1);
    }

    // set fields in mxstatus mask dependent on data cache & local memory
    if(RD_XCSR(object, mdcm_cfg)) {
        SET_CSR_FIELD_MASK_V(object, mxstatus, DME,  -1);
        SET_CSR_FIELD_MASK_V(object, mxstatus, PDME, -1);
    }

    // set fields in mxstatus mask dependent on performance throttling
    if(RD_XCSR_FIELD(object, mmsc_cfg, PFT)) {
        SET_CSR_FIELD_MASK_V(object, mxstatus, PFT_EN,  -1);
        SET_CSR_FIELD_MASK_V(object, mxstatus, PPFT_EN, -1);
        SET_CSR_MASK_V(riscv, mie, RD_CSR_MASK(riscv, mie) | (1<<ANDES_PMOVI_INT));
    }

    // set fields in mcache_ctl mask dependent on instruction cache size
    if(RD_XCSR_FIELD(object, micm_cfg, SZ)) {
        SET_CSR_FIELD_MASK_V(object, mcache_ctl, IC_EN,     -1);
        SET_CSR_FIELD_MASK_V(object, mcache_ctl, IC_ECCEN,  -1);
        SET_CSR_FIELD_MASK_V(object, mcache_ctl, IC_RWECC,  -1);
        SET_CSR_FIELD_MASK_V(object, mcache_ctl, CCTL_SUEN, -1);
    }

    // set fields in mcache_ctl mask dependent on data cache size
    if(RD_XCSR_FIELD(object, mdcm_cfg, SZ)) {
        SET_CSR_FIELD_MASK_V(object, mcache_ctl, DC_EN,     -1);
        SET_CSR_FIELD_MASK_V(object, mcache_ctl, DC_ECCEN,  -1);
        SET_CSR_FIELD_MASK_V(object, mcache_ctl, DC_RWECC,  -1);
        SET_CSR_FIELD_MASK_V(object, mcache_ctl, CCTL_SUEN, -1);
    }

    // transfer unaligned configuration to mmisc_ctl.MSA/UNA and force base
    // model to enabled unaligned access (possibly disabled again during
    // instruction translation)
    WR_XCSR_FIELD(object, mmisc_ctl, MSA_UNA, riscv->configInfo.unaligned);
    riscv->configInfo.unaligned = True;

    // register each CSR with the base model
    for(id=0; id<XCSR_ID(LAST); id++) {

        extCSRAttrsCP  src = &csrs[id];
        riscvCSRAttrs *dst = &object->csrs[id];

        if(extensionPresent(object, src->extension)) {
            riscv->cb.newCSR(dst, &src->baseAttrs, riscv, object);
        }
    }

    // install trap notifiers
    object->extCB.resetNotifier = CSRReset;
    object->extCB.trapNotifier  = trapNotifier;
    object->extCB.ERETNotifier  = ERETNotifier;

    // install halt/restart notifier
    object->extCB.haltRestartNotifier = haltRestartNotifier;

    // allocate counter objects
    newCounters(object);

    // call reset notifier explicitly the first time (main processor reset has
    // already taken place)
    CSRReset(riscv, object);
}

//
// Free CSR state
//
void andesCSRFree(vmiosObjectP object) {

    // free counter objects
    freeCounters(object);
}

