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
#include <stdio.h>
#include <string.h>

// Imperas header files
#include "hostapi/typeMacros.h"

// VMI header files
#include "vmi/vmiOSAttrs.h"
#include "vmi/vmiDoc.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiRt.h"

// model header files
#include "sifiveCSR.h"
#include "sifiveDoc.h"
#include "sifiveStructure.h"
#include "sifiveTypeRefs.h"
#include "sifiveUtils.h"
#include "sifiveVariant.h"

// base model header files
#include "riscvStructure.h"


//
// Define target of snprintf with correct size
//
#define SNPRINTF_TGT(_S) _S, sizeof(_S)

//
// Return current XLEN bits
//
inline static Uns32 getXLenBits(riscvP riscv) {
    return sifiveGetXlenMode(riscv);
}

const char *csrHeader(const char *csrName, Uns32 csrNum) {
    static char buf[64];
    snprintf(buf, sizeof(buf), "%s (csr num 0x%x)", csrName, csrNum);
    return buf;
}

//
// Add documentation for Branch Prediction Mode CSR
//
static void docBPM(vmiDocNodeP section) {

    vmiDocNodeP fdcp = vmidocAddSection(
        section,
        csrHeader("bpm", NUM_bpm)
    );

    vmidocAddText(
        fdcp,
        "Reading and writing the SiFive custom M-Mode Branch Prediction Mode "
        "CSR is supported. Since this register controls only micro-"
        "architectural behavior, which is not modeled, the setting of this "
        "register has no effect."
    );
}

//
// Add documentation for Feature Disable CSR
//
static void docFDCP(vmiDocNodeP section) {

    vmiDocNodeP fdcp = vmidocAddSection(
        section,
        csrHeader("featureDisable", NUM_featureDisable)
    );

    vmidocAddText(
        fdcp,
        "Reading and writing the SiFive custom M-Mode Feature Disable CSR is "
        "supported. Since this register controls only micro-architectural "
        "behavior, which is not modeled, the setting of this register has no "
        "effect, and all fields are hardwired to 0."
    );
}

//
// Add documentation for PowerDial CSR
//
static void docPWRD(vmiDocNodeP section) {

    vmiDocNodeP pwrd = vmidocAddSection(
        section,
        csrHeader("pwrd", NUM_PowerDial)
    );

    vmidocAddText(
        pwrd,
        "Reading and writing the SiFive custom M-Mode PowerDial CSR is "
        "supported. Processor execution speed is immediately reduced by the "
        "factor implied by the CSR."
    );
}

//
// Add documentation for CFLUSH instruction
//
static void docCFLUSH(
    vmiDocNodeP section,
    const char *name,
    const char *CSR,
    const char *operation
) {
    vmiDocNodeP inst = vmidocAddFields(section, name, 32);
    char        tmp[256];

    // fields
    vmidocAddField(inst, "1110011 (System)",   0,  7);
    vmidocAddField(inst, "00000",              7,  5);
    vmidocAddField(inst, "000",               12,  3);
    vmidocAddField(inst, "Rs1",               15,  5);
    vmidocAddField(inst, CSR,                 20, 12);

    // description
    sprintf(
        tmp,
        "Instruction to %s the DCACHE L1 line for the address in Rs1. "
        "This instruction will generate exceptions for attempts to flush "
        "addresses that are not writable, but since caches are not "
        "modeled will otherwise have no effect.",
        operation
    );
    vmidocAddText(inst, tmp);
}

//
// Add documentation for CEASE instruction
//
static void docCEASE(vmiDocNodeP section) {

    vmiDocNodeP inst = vmidocAddFields(section, "CEASE", 32);

    // fields
    vmidocAddField(inst, "1110011 (System)",   0,  7);
    vmidocAddField(inst, "00000",              7,  5);
    vmidocAddField(inst, "000",               12,  3);
    vmidocAddField(inst, "00000",             15,  5);
    vmidocAddField(inst, "001100000101",      20, 12);

    // description
    vmidocAddText(
        inst,
        "Instruction to cease execution until the hart is reset."
    );
}

//
// Add documentation for SiFive instructions
//
VMIOS_DOC_FN(sifiveDoc) {

    vmiDocNodeP sifive      = vmidocAddSection(0, "SiFive-Specific Extensions");
    vmiDocNodeP csrSection  = 0;
    vmiDocNodeP codeSection = 0;

    // if nothing enabled do not add any documentation
    if(!object->variant) {
        return;
    }

    // introduce SiFive-specific extensions
    {
        // description
        vmidocAddText(
            sifive,
            "SiFive processors can add various custom extensions to the basic "
            "RISC-V architecture. This model implements the following:"
        );
    }

    if(object->variant & S5V_CSR) {

        csrSection = vmidocAddSection(sifive, "SiFive-Specific CSRs");

        // description
        vmidocAddText(
            csrSection,
            "This section describes SiFive-specific CSRs implemented by "
            "this variant. Refer to SiFive reference documentation for more "
            "information."
        );

        if(object->variant & S5V_BPM) {
            docBPM(csrSection);
        }
        if(object->variant & S5V_FDCP) {
            docFDCP(csrSection);
        }
        if(object->variant & S5V_PWRD) {
            docPWRD(csrSection);
        }
    }

    if(object->variant & S5V_INST) {

        codeSection = vmidocAddSection(sifive, "SiFive-Specific Instructions");

        // description
        vmidocAddText(
            codeSection,
            "This section describes SiFive-specific instructions implemented by "
            "this variant. Refer to SiFive reference documentation for more "
            "information."
        );

        if(object->variant & S5V_CFLUSH) {
            docCFLUSH(codeSection, "CFLUSH.D.L1",   "111111000000", "flush");
            docCFLUSH(codeSection, "CDISCARD.D.L1", "111111000010", "discard");
        }
        if(object->variant & S5V_CEASE) {
            docCEASE(codeSection);
        }
    }

    vmidocProcessor((vmiProcessorP)object->riscv, sifive);
}
