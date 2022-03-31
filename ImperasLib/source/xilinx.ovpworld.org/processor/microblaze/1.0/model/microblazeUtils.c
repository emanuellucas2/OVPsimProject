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

#include "vmi/vmiCxt.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiRt.h"

#include "microblazeFunctions.h"
#include "microblazeDecode.h"
#include "microblazeUtils.h"

VMI_ENDIAN_FN(microblazeGetEndian) {
    memEndian endian;
    microblazeP microblaze = (microblazeP)processor;

    endian = (microblaze->SPR_PVR0.ENDI == 0) ? MEM_ENDIAN_BIG : MEM_ENDIAN_LITTLE;
    return endian;
}

Addr microblazeNextInstructionUser(vmiProcessorP processor, Addr thisPC) {
    microblazeInstructionInfo info;
    microblazeDecode((microblazeP)processor, thisPC, &info);
    microblazeAddr nextAddress = info.nextPC;
    return nextAddress;
}

VMI_NEXT_PC_FN(microblazenextPC) {
    return microblazeNextInstructionUser(processor, thisPC);
}

////////////////////////////////////////////////////////////////////////////////
// PROCESSOR RUN STATE TRANSITION HANDLING
////////////////////////////////////////////////////////////////////////////////

static void microblazeAbortExclusiveAccess(microblazeP microblaze);

//
// If this memory access callback is triggered, abort any active load linked
//
static VMI_MEM_WATCH_FN(abortEA) {
    if(processor) {
        microblazeAbortExclusiveAccess((microblazeP)userData);
    }
}

//
// Install or remove the exclusive access monitor callback
//
static void updateExclusiveAccessCallback(microblazeP microblaze, Bool install) {

    memDomainP domain  = vmirtGetProcessorDataDomain((vmiProcessorP)microblaze);
    Uns64      simLow  = microblaze->reservation_addr;
    Uns64      simHigh = simLow + microblaze->reservation_length;

    // install or remove a watchpoint on the current exclusive access address
    if(install) {
        vmirtAddWriteCallback(domain, 0, simLow, simHigh, abortEA, microblaze);
    } else {
        vmirtRemoveWriteCallback(domain, 0, simLow, simHigh, abortEA, microblaze);
    }
}

//
// Abort any active exclusive access
//
static void microblazeAbortExclusiveAccess(microblazeP microblaze) {

    if(microblaze->reservation == True) {

        // remove callback on exclusive access monitor region
        updateExclusiveAccessCallback(microblaze, False);

        // clear exclusive tag (AFTER updateExclusiveAccessCallback)
        microblaze->reservation = False;
    }
}

//
// Install or remove the exclusive access monitor callback if required
//
void microblazeUpdateExclusiveAccessCallback(microblazeP microblaze, Bool install) {
    if(microblaze->reservation == True) {
        updateExclusiveAccessCallback(microblaze, install);
    }
}

//
// This is called on simulator context switch (when this processor is either
// about to start or about to stop simulation)
//
VMI_IASSWITCH_FN(microblazeSwitch) {
    microblazeP microblaze = (microblazeP) processor;
    if (microblaze->SPR_PVR2.AXI4DP && microblaze->SPR_PVR5.AXI4DC) {
        microblazeUpdateExclusiveAccessCallback((microblazeP)processor, state==RS_SUSPEND);
    }
}

//
// Table of processor mode descriptions
//
static const vmiModeInfo modes[] = {
    { "REAL",         VM_MODE_REAL,         "Real mode" },
    { "VIRTUAL_PRIV", VM_MODE_VIRTUAL_PRIV, "Virtual privileged mode" },
    { "VIRTUAL_USER", VM_MODE_VIRTUAL_USER, "Virtual user mode" },
    { 0, 0, 0 }
};

VMI_GET_MODE_FN(microblazeGetMode) {
    return &modes[microblazeGetVMMode((microblazeP)processor)];
}

VMI_MODE_INFO_FN(microblazeModeInfo) {

    // on the first call, start with the first member of the table
    if(!prev) {
        prev = modes-1;
    }

    // get the next member
    vmiModeInfoCP this = prev+1;

    // return the next member, or NULL if at the end of the list
    return (this->name) ? this : 0;
}

Bool microblazeMMUPrivileged(microblazeP microblaze) {
    return (microblaze->params.C_USE_MMU > 0) && !microblaze->params.C_MMU_PRIVILEGED_INSTR;
}

//
// Return processor mode
//
microblazeVMMode microblazeGetVMMode(microblazeP microblaze) {

    // MMU
    // 0 = None
    // 1 = User Mode
    // 2 = Protection
    // 3 = Virtual
    switch (microblaze->SPR_PVR11.MMU) {
        case 0:
        case 1:
            return VM_MODE_REAL;
            break;

        case 2:
        case 3:
            if (microblaze->SPR_MSR.VM) {
                if (microblaze->SPR_MSR.UM) {
                    return VM_MODE_VIRTUAL_USER;
                } else {
                    return VM_MODE_VIRTUAL_PRIV;
                }
            } else {
                return VM_MODE_REAL;
            }
            break;

        default:
            VMI_ABORT("Unexpected value for PVR11[MMU]");
            break;
    }
}

__attribute__((unused)) inline static void printMode(microblazeP microblaze, const char *msg) {
    Uns8 new = (microblaze->SPR_MSR.UM << 1)  | microblaze->SPR_MSR.VM;
    Uns8 ie  = microblaze->SPR_MSR.IE;
    Uns8 ee  = microblaze->SPR_MSR.EE;
    const char *intr = ie ? "Interrupts Enabled" : "Interrupts Disabled";
    const char *excp = ee ? "Exceptions Enabled" : "Exceptions Disabled";

    switch (new) {
    case 0:
        vmiMessage("I", "VM_MODE", "%s PRIV REAL, %s, %s\n", msg, intr, excp);
        break;
    case 1:
        vmiMessage("I", "VM_MODE", "%s PRIV VIRT, %s, %s\n", msg, intr, excp);
        break;
    case 2:
        vmiMessage("F", "VM_MODE", "%s USER REAL, %s, %s\n", msg, intr, excp);
        break;
    case 3:
        vmiMessage("I", "VM_MODE", "%s USER VIRT, %s, %s\n", msg, intr, excp);
        break;
    default:
        break;
    }
}

void microblazeSaveVMMode(microblazeP microblaze) {
    microblaze->SPR_MSR.UMS = microblaze->SPR_MSR.UM;
    microblaze->SPR_MSR.VMS = microblaze->SPR_MSR.VM;
    microblaze->SPR_MSR.UM = 0;
    microblaze->SPR_MSR.VM = 0;
//    printMode(microblaze, "SAVE");
}

void microblazeRestoreVMMode(microblazeP microblaze) {
    microblaze->SPR_MSR.UM = microblaze->SPR_MSR.UMS;
    microblaze->SPR_MSR.VM = microblaze->SPR_MSR.VMS;
//    printMode(microblaze, "RESTORE");
}

void microblazeExceptionEnter(microblazeP microblaze) {
//    if(microblaze->SPR_MSR.EE) vmiMessage("I", "EXCEPTION", "Enter - Disable Exceptions @ %llu", vmirtGetICount((vmiProcessorP)microblaze));
    microblaze->SPR_MSR.EE  = 0;
    microblaze->SPR_MSR.EIP = 1;
}

void microblazeExceptionReturn(microblazeP microblaze) {
//    if(!microblaze->SPR_MSR.EE) vmiMessage("I", "EXCEPTION", "Return - Enable Exceptions @ %llu", vmirtGetICount((vmiProcessorP)microblaze));
    microblaze->SPR_MSR.EE  = 1;
    microblaze->SPR_MSR.EIP = 0;
}

void microblazeInterruptEnter(microblazeP microblaze) {
//    if(microblaze->SPR_MSR.IE) vmiMessage("I", "EXCEPTION", "Enter - Disable Interrupt @ %llu", vmirtGetICount((vmiProcessorP)microblaze));
    microblaze->SPR_MSR.IE = 0;
}

void microblazeInterruptReturn(microblazeP microblaze) {
//    if(!microblaze->SPR_MSR.IE) vmiMessage("I", "EXCEPTION", "Return - Enable Interrupt @ %llu", vmirtGetICount((vmiProcessorP)microblaze));
    microblaze->SPR_MSR.IE = 1;
}
