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

// Imperas header files
#include "hostapi/typeMacros.h"

// VMI header files
#include "vmi/vmiMessage.h"
#include "vmi/vmiMt.h"
#include "vmi/vmiRt.h"

// model header files
#include "sifiveConfig.h"
#include "sifiveCSR.h"
#include "sifiveMessage.h"
#include "sifiveStructure.h"
#include "sifiveTypeRefs.h"
#include "sifiveUtils.h"
#include "sifiveVariant.h"

// base model header files
#include "riscvStructure.h"


////////////////////////////////////////////////////////////////////////////////
// TYPES
////////////////////////////////////////////////////////////////////////////////

//
// This type defines CSR attributes together with SiFive-specific configuration
// information
//
typedef struct sifiveCSRAttrsS {
    riscvCSRAttrs baseAttrs;    // base attributes (KEEP FIRST)
    sifiveVariant extension;    // extension requirements
} sifiveCSRAttrs;

DEFINE_CS(sifiveCSRAttrs);


////////////////////////////////////////////////////////////////////////////////
// CSRS
////////////////////////////////////////////////////////////////////////////////

//
// Derate processor by factor implied by PowerDial CSR
//
static void refreshPowerDial(vmiosObjectP object) {

    Uns32 IssueRate = RD_XCSR_FIELD(object, PowerDial, IssueRate);

    vmirtSetDerateFactor((vmiProcessorP)object->riscv, (IssueRate*100.0)/16);
}

//
// Write mcounterovf
//
static RISCV_CSR_WRITEFN(PowerDialW) {

    vmiosObjectP object   = attrs->object;
    Uns32        oldValue = RD_XCSR(object, PowerDial);

    // mask value
    newValue &= WM64_PowerDial;

    // handle any change to power state
    if(newValue != oldValue) {
        WR_XCSR(object, PowerDial, newValue);
        refreshPowerDial(object);
    }

    return newValue;
}

//
// CSR table
//
static const extCSRAttrs csrs[XCSR_ID(LAST)] = {

    //            name            num                 arch extension attrs    description                      rCB rwCB wCB
    XCSR_ATTR_TC_(bpm,            NUM_bpm,            0,   S5V_BPM,  0,0,0,0, "SiFive Branch Prediction Mode", 0,  0,   0         ),
    XCSR_ATTR_TV_(featureDisable, NUM_featureDisable, 0,   S5V_FDCP, 0,0,0,0, "SiFive FeatureDisable",         0,  0,   0         ),
    XCSR_ATTR_TC_(PowerDial,      NUM_PowerDial,      0,   S5V_PWRD, 0,0,0,0, "SiFive PowerDial",              0,  0,   PowerDialW),
};


////////////////////////////////////////////////////////////////////////////////
// INITIALIZATION
////////////////////////////////////////////////////////////////////////////////

//
// Reset SiFive-specific CSRs
//
static RISCV_RESET_NOTIFIER_FN(CSRReset) {

    vmiosObjectP object = clientData;

    // reset CSRs
    WR_XCSR(object, bpm,            0);
    WR_XCSR(object, featureDisable, 0);
    WR_XCSR(object, PowerDial,      0);

    // refresh power state
    refreshPowerDial(object);
}

//
// Initialize CSR state
//
void sifiveCSRInit(vmiosObjectP object) {

    riscvP   riscv = object->riscv;
    extCSRId id;

    // initialize write masks
    SET_XCSR_MASK_V(object, featureDisable, 0);

    // register each CSR with the base model
    for(id=0; id<XCSR_ID(LAST); id++) {

        extCSRAttrsCP  src = &csrs[id];
        riscvCSRAttrs *dst = &object->csrs[id];

        if((src->extension & object->variant) == src->extension) {
            riscv->cb.newCSR(dst, &src->baseAttrs, riscv, object);
        }
    }

    // call reset notifier explicitly the first time (main processor reset has
    // already taken place)
    CSRReset(riscv, object);
}

