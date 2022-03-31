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
#include "vmi/vmiRt.h"

// model header files
#include "andesCSR.h"
#include "andesDoc.h"
#include "andesStructure.h"
#include "andesTypeRefs.h"
#include "andesUtils.h"
#include "andesVariant.h"

// base model header files
#include "riscvStructure.h"


//
// Define target of snprintf with correct size
//
#define SNPRINTF_TGT(_S) _S, sizeof(_S)

//
// Custom instruction macros
//
#define CUSTOM0     "Custom0 0001011",  0, 7
#define CUSTOM1     "Custom1 0101011",  0, 7
#define CUSTOM2     "Custom2 1011011",  0, 7
#define LOAD_FP     "LOAD-FP 0000111",  0, 7
#define STORE_FP    "STORE-FP 0100111", 0, 7

//
// Return current XLEN bits
//
inline static Uns32 getXLenBits(riscvP riscv) {
    return andesGetXlenMode(riscv);
}

//
// Add documentation for ADDIGP instruction
//
static void docADDIGP(vmiDocNodeP insts) {

    vmiDocNodeP inst = vmidocAddFields(insts, "ADDIGP", 32);

    // fields
    vmidocAddField(inst, CUSTOM0);
    vmidocAddField(inst, "Rd",          7,  5);
    vmidocAddField(inst, "01",         12,  2);
    vmidocAddField(inst, "imm[0]",     14,  1);
    vmidocAddField(inst, "imm[16:15]", 15,  2);
    vmidocAddField(inst, "imm[14:12]", 17,  3);
    vmidocAddField(inst, "imm[11]",    20,  1);
    vmidocAddField(inst, "imm[10:1]",  21, 10);
    vmidocAddField(inst, "imm[17]",    31,  1);

    // description
    vmidocAddText(
        inst,
        "Add the content of the implied GP (x3) register with a signed "
        "constant."
    );
}

//
// Add documentation for BBC/BBS instructions
//
static void docBBx(
    vmiDocNodeP insts,
    const char *opcode,
    const char *decode,
    Bool        xlen32,
    const char *desc
) {
    vmiDocNodeP inst = vmidocAddFields(insts, opcode, 32);

    // fields
    vmidocAddField(inst, CUSTOM2);
    vmidocAddField(inst, xlen32?"0":"cimm[5]",  7,  1);
    vmidocAddField(inst, "imm[4:1]",            8,  4);
    vmidocAddField(inst, "111",                12,  3);
    vmidocAddField(inst, "Rs1",                15,  5);
    vmidocAddField(inst, "cimm[4:0]",          20,  5);
    vmidocAddField(inst, "imm[9:5]",           25,  5);
    vmidocAddField(inst, decode,               30,  1);
    vmidocAddField(inst, "imm[10]",            31,  1);

    // description
    vmidocAddText(inst, desc);
}

//
// Add documentation for BEQC/BNEC instructions
//
static void docBxxC(
    vmiDocNodeP insts,
    const char *opcode,
    const char *decode,
    const char *desc
) {
    vmiDocNodeP inst = vmidocAddFields(insts, opcode, 32);

    // fields
    vmidocAddField(inst, CUSTOM2);
    vmidocAddField(inst, "cimm[5]",    7,  1);
    vmidocAddField(inst, "imm[4:1]",   8,  4);
    vmidocAddField(inst, decode,      12,  3);
    vmidocAddField(inst, "Rs1",       15,  5);
    vmidocAddField(inst, "cimm[4:0]", 20,  5);
    vmidocAddField(inst, "imm[9:5]",  25,  5);
    vmidocAddField(inst, "cimm[6]",   30,  1);
    vmidocAddField(inst, "imm[10]",   31,  1);

    // description
    vmidocAddText(inst, desc);
}

//
// Add documentation for BFOS/BFOZ instructions
//
static void docBFOx(
    vmiDocNodeP insts,
    const char *opcode,
    const char *decode,
    Bool        xlen32,
    const char *desc
) {
    vmiDocNodeP inst = vmidocAddFields(insts, opcode, 32);

    // fields
    vmidocAddField(inst, CUSTOM2);
    vmidocAddField(inst, "Rd",            7,  5);
    vmidocAddField(inst, decode,         12,  3);
    vmidocAddField(inst, "Rs1",          15,  5);

    if(xlen32) {
        vmidocAddField(inst, "lsb[4:0]", 20,  5);
        vmidocAddField(inst, "0",        25,  1);
        vmidocAddField(inst, "msb[4:0]", 26,  5);
        vmidocAddField(inst, "0",        31,  1);
    } else {
        vmidocAddField(inst, "lsb[5:0]", 20,  6);
        vmidocAddField(inst, "msb[5:0]", 26,  6);
    }

    // description
    vmidocAddText(inst, desc);
}

//
// Add documentation for LEA instructions
//
static void docLEA(
    vmiDocNodeP insts,
    const char *opcode,
    const char *decode,
    const char *desc
) {
    vmiDocNodeP inst = vmidocAddFields(insts, opcode, 32);

    // fields
    vmidocAddField(inst, CUSTOM2);
    vmidocAddField(inst, "Rd",     7, 5);
    vmidocAddField(inst, "000",   12, 3);
    vmidocAddField(inst, "Rs1",   15, 5);
    vmidocAddField(inst, "Rs2",   20, 5);
    vmidocAddField(inst, decode,  25, 7);

    // description
    vmidocAddText(inst, desc);
}

//
// Add documentation for LBGP and LBUGP instructions
//
static void docLBxGP(
    vmiDocNodeP insts,
    const char *opcode,
    const char *decode,
    const char *desc
) {
    vmiDocNodeP inst = vmidocAddFields(insts, opcode, 32);

    // fields
    vmidocAddField(inst, CUSTOM0);
    vmidocAddField(inst, "Rd",          7,  5);
    vmidocAddField(inst, decode,       12,  2);
    vmidocAddField(inst, "imm[0]",     14,  1);
    vmidocAddField(inst, "imm[16:15]", 15,  2);
    vmidocAddField(inst, "imm[14:12]", 17,  3);
    vmidocAddField(inst, "imm[11]",    20,  1);
    vmidocAddField(inst, "imm[10:1]",  21, 10);
    vmidocAddField(inst, "imm[17]",    31,  1);

    // description
    vmidocAddText(inst, desc);
}

//
// Add documentation for LHGP and LHUGP instructions
//
static void docLHxGP(
    vmiDocNodeP insts,
    const char *opcode,
    const char *decode,
    const char *desc
) {
    vmiDocNodeP inst = vmidocAddFields(insts, opcode, 32);

    // fields
    vmidocAddField(inst, CUSTOM1);
    vmidocAddField(inst, "Rd",          7,  5);
    vmidocAddField(inst, decode,       12,  3);
    vmidocAddField(inst, "imm[16:15]", 15,  2);
    vmidocAddField(inst, "imm[14:12]", 17,  3);
    vmidocAddField(inst, "imm[11]",    20,  1);
    vmidocAddField(inst, "imm[10:1]",  21, 10);
    vmidocAddField(inst, "imm[17]",    31,  1);

    // description
    vmidocAddText(inst, desc);
}

//
// Add documentation for LWGP and LWUGP instructions
//
static void docLWxGP(
    vmiDocNodeP insts,
    const char *opcode,
    const char *decode,
    const char *desc
) {
    vmiDocNodeP inst = vmidocAddFields(insts, opcode, 32);

    // fields
    vmidocAddField(inst, CUSTOM1);
    vmidocAddField(inst, "Rd",          7, 5);
    vmidocAddField(inst, decode,       12, 3);
    vmidocAddField(inst, "imm[16:15]", 15, 2);
    vmidocAddField(inst, "imm[14:12]", 17, 3);
    vmidocAddField(inst, "imm[11]",    20, 1);
    vmidocAddField(inst, "imm[17]",    21, 1);
    vmidocAddField(inst, "imm[10:2]",  22, 9);
    vmidocAddField(inst, "imm[18]",    31, 1);

    // description
    vmidocAddText(inst, desc);
}

//
// Add documentation for LDGP instruction
//
static void docLDGP(
    vmiDocNodeP insts,
    const char *opcode,
    const char *decode,
    const char *desc
) {
    vmiDocNodeP inst = vmidocAddFields(insts, opcode, 32);

    // fields
    vmidocAddField(inst, CUSTOM1);
    vmidocAddField(inst, "Rd",          7, 5);
    vmidocAddField(inst, decode,       12, 3);
    vmidocAddField(inst, "imm[16:15]", 15, 2);
    vmidocAddField(inst, "imm[14:12]", 17, 3);
    vmidocAddField(inst, "imm[11]",    20, 1);
    vmidocAddField(inst, "imm[18:17]", 21, 2);
    vmidocAddField(inst, "imm[10:3]",  23, 8);
    vmidocAddField(inst, "imm[19]",    31, 1);

    // description
    vmidocAddText(inst, desc);
}

//
// Add documentation for SBGP instruction
//
static void docSBGP(
    vmiDocNodeP insts,
    const char *opcode,
    const char *decode,
    const char *desc
) {
    vmiDocNodeP inst = vmidocAddFields(insts, opcode, 32);

    // fields
    vmidocAddField(inst, CUSTOM0);
    vmidocAddField(inst, "imm[11]",     7, 1);
    vmidocAddField(inst, "imm[4:1]",    8, 4);
    vmidocAddField(inst, decode,       12, 2);
    vmidocAddField(inst, "imm[0]",     14, 1);
    vmidocAddField(inst, "imm[16:15]", 15, 2);
    vmidocAddField(inst, "imm[14:12]", 17, 3);
    vmidocAddField(inst, "Rs2",        20, 5);
    vmidocAddField(inst, "imm[10:5]",  25, 6);
    vmidocAddField(inst, "imm[17]",    31, 1);

    // description
    vmidocAddText(inst, desc);
}

//
// Add documentation for SHGP instruction
//
static void docSHGP(
    vmiDocNodeP insts,
    const char *opcode,
    const char *decode,
    const char *desc
) {
    vmiDocNodeP inst = vmidocAddFields(insts, opcode, 32);

    // fields
    vmidocAddField(inst, CUSTOM1);
    vmidocAddField(inst, "imm[11]",     7, 1);
    vmidocAddField(inst, "imm[4:1]",    8, 4);
    vmidocAddField(inst, decode,       12, 3);
    vmidocAddField(inst, "imm[16:15]", 15, 2);
    vmidocAddField(inst, "imm[14:12]", 17, 3);
    vmidocAddField(inst, "Rs2",        20, 5);
    vmidocAddField(inst, "imm[10:5]",  25, 6);
    vmidocAddField(inst, "imm[17]",    31, 1);

    // description
    vmidocAddText(inst, desc);
}

//
// Add documentation for SWGP instruction
//
static void docSWGP(
    vmiDocNodeP insts,
    const char *opcode,
    const char *decode,
    const char *desc
) {
    vmiDocNodeP inst = vmidocAddFields(insts, opcode, 32);

    // fields
    vmidocAddField(inst, CUSTOM1);
    vmidocAddField(inst, "imm[11]",     7, 1);
    vmidocAddField(inst, "imm[17]",     8, 1);
    vmidocAddField(inst, "imm[4:2]",    9, 3);
    vmidocAddField(inst, decode,       12, 3);
    vmidocAddField(inst, "imm[16:15]", 15, 2);
    vmidocAddField(inst, "imm[14:12]", 17, 3);
    vmidocAddField(inst, "Rs2",        20, 5);
    vmidocAddField(inst, "imm[10:5]",  25, 6);
    vmidocAddField(inst, "imm[18]",    31, 1);

    // description
    vmidocAddText(inst, desc);
}

//
// Add documentation for SDGP instruction
//
static void docSDGP(
    vmiDocNodeP insts,
    const char *opcode,
    const char *decode,
    const char *desc
) {
    vmiDocNodeP inst = vmidocAddFields(insts, opcode, 32);

    // fields
    vmidocAddField(inst, CUSTOM1);
    vmidocAddField(inst, "imm[11]",     7, 1);
    vmidocAddField(inst, "imm[18:17]",  8, 2);
    vmidocAddField(inst, "imm[4:3]",   10, 2);
    vmidocAddField(inst, decode,       12, 3);
    vmidocAddField(inst, "imm[16:15]", 15, 2);
    vmidocAddField(inst, "imm[14:12]", 17, 3);
    vmidocAddField(inst, "Rs2",        20, 5);
    vmidocAddField(inst, "imm[10:5]",  25, 6);
    vmidocAddField(inst, "imm[19]",    31, 1);

    // description
    vmidocAddText(inst, desc);
}

//
// Add documentation for FFB, FFZMISM, FFMISM and FLMISM instructions
//
static void docFFx(
    vmiDocNodeP insts,
    const char *opcode,
    const char *decode,
    const char *desc
) {
    vmiDocNodeP inst = vmidocAddFields(insts, opcode, 32);

    // fields
    vmidocAddField(inst, CUSTOM2);
    vmidocAddField(inst, "Rd",    7, 5);
    vmidocAddField(inst, "000",  12, 3);
    vmidocAddField(inst, "Rs1",  15, 5);
    vmidocAddField(inst, "Rs2",  20, 5);
    vmidocAddField(inst, decode, 25, 7);

    // description
    vmidocAddText(inst, desc);
}

//
// Add documentation for EXEC.IT and EX9.IT instructions
//
static void docEXECIT(vmiDocNodeP insts, Bool isEX9) {

    vmiDocNodeP inst = vmidocAddFields(insts, isEX9 ? "EX9.IT" : "EXEC.IT", 16);

    // fields
    vmidocAddField(inst, "00",              0, 2);
    vmidocAddField(inst, "imm[7:6|2|9|5]",  2, 5);

    if(isEX9) {
        vmidocAddField(inst, "00",          7, 2);
    } else {
        vmidocAddField(inst, "0",           7, 1);
        vmidocAddField(inst, "imm[11]",     8, 1);
    }

    vmidocAddField(inst, "imm[10|4:3|8]",   9, 4);
    vmidocAddField(inst, "100",            13, 3);

    // description
    vmidocAddText(
        inst,
        "Execute an instruction fetched from the instruction table."
    );
}

//
// Add documentation for FLHW instruction
//
static void docFLHW(vmiDocNodeP insts) {

    vmiDocNodeP inst = vmidocAddFields(insts, "FLHW", 32);

    // fields
    vmidocAddField(inst, LOAD_FP);
    vmidocAddField(inst, "FRd",        7,  5);
    vmidocAddField(inst, "000",       12,  3);
    vmidocAddField(inst, "Rs1",       15,  5);
    vmidocAddField(inst, "imm[11:0]", 20, 12);

    // description
    vmidocAddText(
        inst,
        "Load half-precision floating-point value from memory and convert it "
        "to a single-precision value."
    );
}

//
// Add documentation for FSHW instruction
//
static void docFSHW(vmiDocNodeP insts) {

    vmiDocNodeP inst = vmidocAddFields(insts, "FSHW", 32);

    // fields
    vmidocAddField(inst, STORE_FP);
    vmidocAddField(inst, "imm[4:0]",   7, 5);
    vmidocAddField(inst, "000",       12, 3);
    vmidocAddField(inst, "Rs1",       15, 5);
    vmidocAddField(inst, "FRs2",      20, 5);
    vmidocAddField(inst, "imm[11:5]", 25, 7);

    // description
    vmidocAddText(
        inst,
        "Store half-precision floating-point data to memory. The "
        "half-precision floating-point value is converted from a "
        "single-precision value source."
    );
}

//
// Add documentation for INT4 instruction
//
static void docINT4(
    vmiDocNodeP insts,
    const char *opcode,
    const char *decode,
    const char *desc
) {
    vmiDocNodeP inst = vmidocAddFields(insts, opcode, 32);

    // fields
    vmidocAddField(inst, CUSTOM2);
    vmidocAddField(inst, "Vd",      7, 5);
    vmidocAddField(inst, "100",    12, 3);
    vmidocAddField(inst, "Rs1",    15, 5);
    vmidocAddField(inst, decode,   20, 5);
    vmidocAddField(inst, "M",      25, 1);
    vmidocAddField(inst, "000001", 26, 6);

    // description
    vmidocAddText(inst, desc);
}

//
// Add documentation for BFLOAT16 conversion instructions
//
static void docFCVT(
    vmiDocNodeP insts,
    const char *opcode,
    const char *decode,
    const char *rd,
    const char *rs,
    const char *desc
) {
    vmiDocNodeP inst = vmidocAddFields(insts, opcode, 32);

    // fields
    vmidocAddField(inst, CUSTOM2);
    vmidocAddField(inst, rd,        7, 5);
    vmidocAddField(inst, "100",     12, 3);
    vmidocAddField(inst, decode,    15, 5);
    vmidocAddField(inst, rs,        20, 5);
    vmidocAddField(inst, "0000001", 25, 7);

    // description
    vmidocAddText(inst, desc);
}

//
// Add documentation for VPFH instruction
//
static void docVPFH(
    vmiDocNodeP insts,
    const char *opcode,
    const char *decode,
    const char *desc
) {
    vmiDocNodeP inst = vmidocAddFields(insts, opcode, 32);

    // fields
    vmidocAddField(inst, CUSTOM2);
    vmidocAddField(inst, "Vd",    7, 5);
    vmidocAddField(inst, "100",  12, 3);
    vmidocAddField(inst, "Rs1",  15, 5);
    vmidocAddField(inst, "Vs2",  20, 5);
    vmidocAddField(inst, "M",    25, 1);
    vmidocAddField(inst, decode, 26, 6);

    // description
    vmidocAddText(inst, desc);
}

//
// Document mmsc_cfg parameter
//
static void doc_mmsc_cfg(vmiDocNodeP section) {

    vmiDocNodeP param = vmidocAddSection(
        section, "Parameter andesExtensions/mmsc_cfg"
    );

    vmidocAddText(
        param,
        "This parameter allows the value of the read-only mmsc_cfg "
        "register to be specified. Bits that affect behavior of the "
        "model are:"
    );
    vmidocAddText(
        param,
        "bit 3 (ECD): enables CodeDense instructions and uitb CSR."
    );
    vmidocAddText(
        param,
        "bit 4 (PFT): determines presence of mpft_ctl register and "
        "affects implemented fields in mxstatus."
    );
    vmidocAddText(
        param,
        "bit 5 (HSP): enables HW Stack protection, relevant CSRs and "
        "affects implemented fields in mxstatus."
    );
    vmidocAddText(
        param,
        "bit 12 (VPLIC): enables Vectored Interrupts support."
    );
    vmidocAddText(
        param,
        "bit 13 (EV5PE): enables Performance Extension support."
    );
    vmidocAddText(
        param,
        "bit 15 (PMNDS): enables Andes-enhanced Performance Monitoring."
    );
    vmidocAddText(
        param,
        "bit 16 (CCTLCSR): enables CCTL CSRs."
    );
    vmidocAddText(
        param,
        "bit 30 (DPMA): enables the Physical Memory Attribute Unit and "
        "relevant CSRs."
    );
    vmidocAddText(
        param,
        "bit 32 (BF16CVT): enables BFLOAT16 conversion extension."
    );
    vmidocAddText(
        param,
        "bit 33 (ZFH): enables FP16 half-precision extension."
    );
    vmidocAddText(
        param,
        "bit 34 (VL4): enables vector INT4 load extension."
    );
    vmidocAddText(
        param,
        "bit 44 (VPFH): enables vector packed FP16 extension."
    );
    vmidocAddText(
        param,
        "bit 45 (L2CMP_CFG): enables cluster configuration fields. "
        "CORE_PCLUS field will be set to floor(numharts-1, 1)."
    );
    vmidocAddText(
        param,
        "bit 46 (L2C): enables ml2c_ctl_base CSR if both "
        "L2C and L2CMP_CFG are not zero"
    );
    vmidocAddText(
        param,
        "Other bits can be set or cleared but do not affect model "
        "behavior."
    );
    vmidocAddText(
        param,
        "Example: --override iss/cpu0/andesExtensions/mmsc_cfg=0x2028"
    );
}

//
// Document micm_cfg parameter
//
static void doc_micm_cfg(vmiDocNodeP section) {

    vmiDocNodeP param = vmidocAddSection(
        section, "Parameter andesExtensions/micm_cfg"
    );

    vmidocAddText(
        param,
        "This parameter allows the value of the read-only micm_cfg register to "
        "be specified. Bits that affect behavior of the model are:"
    );
    vmidocAddText(
        param,
        "bits 8:6 (ISZ): enables mcache_ctl CSR if non-zero."
    );
    vmidocAddText(
        param,
        "bits 14:12 (ILMB): enables milmb CSR if non-zero."
    );
    vmidocAddText(
        param,
        "Other bits can be set or cleared but do not affect model behavior, "
        "except that if any bit is non zero then IME/PIME bits in mxstatus are "
        "modeled."
    );
    vmidocAddText(
        param,
        "Example: --override iss/cpu0/andesExtensions/micm_cfg=0"
    );
}

//
// Document mdcm_cfg parameter
//
static void doc_mdcm_cfg(vmiDocNodeP section) {

    vmiDocNodeP param = vmidocAddSection(
        section, "Parameter andesExtensions/mdcm_cfg"
    );

    vmidocAddText(
        param,
        "This parameter allows the value of the read-only mdcm_cfg register to "
        "be specified. Bits that affect behavior of the model are:"
    );
    vmidocAddText(
        param,
        "bits 8:6 (DSZ): enables mcache_ctl CSR if non-zero."
    );
    vmidocAddText(
        param,
        "bits 14:12 (DLMB): enables mdlmb CSR if non-zero."
    );
    vmidocAddText(
        param,
        "Other bits can be set or cleared but do not affect model behavior, "
        "except that if any bit is non zero then DME/DIME bits in mxstatus are "
        "modeled."
    );
    vmidocAddText(
        param,
        "Example: --override iss/cpu0/andesExtensions/mdcm_cfg=0"
    );
}

//
// Document uitb parameter
//
static void doc_uitb(vmiDocNodeP section) {

    vmiDocNodeP param = vmidocAddSection(
        section, "Parameter andesExtensions/uitb"
    );

    vmidocAddText(
        param,
        "This parameter allows the value of the uitb register to be specified."
    );
    vmidocAddText(
        param,
        "Example: --override iss/cpu0/andesExtensions/uitb=0"
    );
}

//
// Document milmb parameter
//
static void doc_milmb(vmiDocNodeP section) {

    vmiDocNodeP param = vmidocAddSection(
        section, "Parameter andesExtensions/milmb"
    );

    vmidocAddText(
        param,
        "This parameter allows the value of the milmb register to be specified."
    );
    vmidocAddText(
        param,
        "Example: --override iss/cpu0/andesExtensions/milmb=0"
    );
}

//
// Document milmbMask parameter
//
static void doc_milmbMask(vmiDocNodeP section) {

    vmiDocNodeP param = vmidocAddSection(
        section, "Parameter andesExtensions/milmbMask"
    );

    vmidocAddText(
        param,
        "This parameter allows the mask of writable bits in the milmb register "
        "to be specified. The default value for this variant is 0xe (RWECC and "
        "ECCEN are writable, all other bits are read-only)."
    );
    vmidocAddText(
        param,
        "Example: --override iss/cpu0/andesExtensions/milmbMask=0xe"
    );
}

//
// Document mdlmb parameter
//
static void doc_mdlmb(vmiDocNodeP section) {

    vmiDocNodeP param = vmidocAddSection(
        section, "Parameter andesExtensions/mdlmb"
    );

    vmidocAddText(
        param,
        "This parameter allows the value of the mdlmb register to be specified."
    );
    vmidocAddText(
        param,
        "Example: --override iss/cpu0/andesExtensions/mdlmb=0"
    );
}

//
// Document mdlmbMask parameter
//
static void doc_mdlmbMask(vmiDocNodeP section) {

    vmiDocNodeP param = vmidocAddSection(
        section, "Parameter andesExtensions/mdlmbMask"
    );

    vmidocAddText(
        param,
        "This parameter allows the mask of writable bits in the mdlmb register "
        "to be specified. The default value for this variant is 0xe (RWECC and "
        "ECCEN are writable, all other bits are read-only)."
    );
    vmidocAddText(
        param,
        "Example: --override iss/cpu0/andesExtensions/mdlmbMask=0xe"
    );
}

//
// Document mdlmbMask parameter
//
static void doc_PMA_grain(vmiDocNodeP section, vmiosObjectP object) {

    char string[1024];

    vmiDocNodeP param = vmidocAddSection(
        section, "Parameter andesExtensions/PMA_grain"
    );

    Uns32 G          = object->csrDefaults.PMA_grain;
    Uns64 grainBytes = 4ULL<<G;

    snprintf(
        SNPRINTF_TGT(string),
        "This parameter allows the grain size of Physical Memory Attribute "
        "regions to be specified. The default value for this variant is %u, "
        "meaning that PMA regions as small as "FMT_Au" bytes are implemented.",
        G,
        grainBytes
    );
    vmidocAddText(param, string);

    vmidocAddText(
        param,
        "Example: --override iss/cpu0/andesExtensions/PMA_grain=16"
    );
}

//
// Add documentation for Andes instructions (leaf processor objects)
//
static void docInt(vmiProcessorP processor, vmiosObjectP object) {

    Bool        xlen32      = (getXLenBits(object->riscv)==32);
    Bool        HSP         = RD_XCSR_FIELD(object, mmsc_cfg, HSP);
    Bool        DPMA        = RD_XCSR_FIELD(object, mmsc_cfg, DPMA);
    Bool        PFT         = RD_XCSR_FIELD(object, mmsc_cfg, PFT);
    Bool        CCTLCSR     = RD_XCSR_FIELD(object, mmsc_cfg, CCTLCSR);
    Bool        EV5MPE      = RD_XCSR_FIELD(object, mmsc_cfg, EV5MPE);
    Bool        ECD         = RD_XCSR_FIELD(object, mmsc_cfg, ECD);
    Bool        EFHW        = RD_XCSR_FIELD(object, mmsc_cfg, EFHW);
    Bool        PMNDS       = RD_XCSR_FIELD(object, mmsc_cfg, PMNDS);
    Bool        BF16CVT     = RD_XCSR_FIELD(object, mmsc_cfg, BF16CVT);
    Bool        VL4         = RD_XCSR_FIELD(object, mmsc_cfg, VL4);
    Bool        VPFH        = RD_XCSR_FIELD(object, mmsc_cfg, VPFH);
    vmiDocNodeP andes       = vmidocAddSection(0, "Andes-Specific Extensions");
    vmiDocNodeP codeSection = 0;

    // introduce Andes-specific extensions
    {
        // description
        vmidocAddText(
            andes,
            "Andes processors add various custom extensions to the basic "
            "RISC-V architecture. This model implements the following:"
        );
        vmidocAddText(
            andes,
            "1: Hardware Stack Protection (if mmsc_cfg.HSP=1);"
        );
        vmidocAddText(
            andes,
            "2: Physical Memory Attribute Unit (if mmsc_cfg.DPMA=1)."
        );
        vmidocAddText(
            andes,
            "3: Performance Throttling (register interface only, if "
            "mmsc_cfg.PFT=1);"
        );
        vmidocAddText(
            andes,
            "4: CSRs for CCTL Operations (register interface only, if "
            "mmsc_cfg.CCTLCSR=1);"
        );
        vmidocAddText(
            andes,
            "5: Performance Extension instructions (if mmsc_cfg.EV5MPE=1);"
        );
        vmidocAddText(
            andes,
            "6: CodeDense instructions (if mmsc_cfg.ECD=1);"
        );
        vmidocAddText(
            andes,
            "7: Half-precision load/store instructions (if mmsc_cfg.EFHW=1)."
        );
        vmidocAddText(
            andes,
            "8: BFLOAT16 conversion instructions (if mmsc_cfg.BFLOAT16=1)."
        );
        vmidocAddText(
            andes,
            "9: Half-precision arithmetic instructions (if mmsc_cfg.ZFH=1)."
        );
        vmidocAddText(
            andes,
            "10: Vector INT4 load extension (if mmsc_cfg.VL4=1)."
        );
        vmidocAddText(
            andes,
            "11: Vector packed FP16 extension (if mmsc_cfg.VPFH=1)."
        );
        vmidocAddText(
            andes,
            "Other Andes-specific extensions are not currently modeled. "
            "The exact set of supported extensions can be configured using "
            "parameter \"andesExtensions/mmsc_cfg\", which overrides the "
            "default value of the mmsc_cfg register (see detailed description "
            "below)."
        );
    }

    // document Andes-specific parameters
    {
        vmiDocNodeP section = vmidocAddSection(
            andes, "Andes-Specific Parameters"
        );

        // description
        vmidocAddText(
            section,
            "In addition to the base model RISC-V parameters, this model "
            "implements parameters allowing Andes-specific model features "
            "to be controlled. These parameters are documented below."
        );

        doc_mmsc_cfg(section);
        doc_micm_cfg(section);
        doc_mdcm_cfg(section);
        doc_uitb(section);
        doc_milmb(section);
        doc_milmbMask(section);
        doc_mdlmb(section);
        doc_mdlmbMask(section);
        doc_PMA_grain(section, object);
    }

    {
        vmiDocNodeP section = vmidocAddSection(
            andes, "Hardware Stack Protection"
        );

        if(HSP) {
             vmidocAddText(
                section,
                "Hardware Stack Protection is present on this variant "
                "(mmsc_cfg.HSP=1). Registers mhsp_ctl, msp_bound and msp_base "
                "are implemented."
            );
        } else {
            vmidocAddText(
               section,
               "Hardware Stack Protection is not present on this variant "
               "(mmsc_cfg.HSP=0)."
           );
        }
    }

    {
        vmiDocNodeP section = vmidocAddSection(
            andes, "Physical Memory Attribute Unit"
        );

        if(DPMA) {
             vmidocAddText(
                section,
                "The Physical Memory Attribute Unit is present on this variant "
                "(mmsc_cfg.DPMA=1). Registers pmacfg0-pmacfg3 and pmaaddr0-"
                "pmaaddr15 are implemented. Black hole MTYP specification is "
                "implemented."
            );
        } else {
            vmidocAddText(
               section,
               "The Physical Memory Attribute Unit is not present on this "
               "variant (mmsc_cfg.DPMA=0)."
           );
        }
    }

    {
        vmiDocNodeP section = vmidocAddSection(
            andes, "Performance Throttling"
        );

        if(PFT) {
            vmidocAddText(
                section,
                "Performance Throttling registers are present on this variant "
                "(mmsc_cfg.PFT=1). Register mpft_ctl is present but has no "
                "behavior except for the effects on mxstatus, which are modeled."
            );
        } else {
            vmidocAddText(
                section,
                "Performance Throttling registers are not present on this "
                "variant (mmsc_cfg.PFT=0)."
            );
        }
    }

    {
        vmiDocNodeP section = vmidocAddSection(
            andes, "Andes-Enhanced Performance Monitoring"
        );

        if(PMNDS) {
             vmidocAddText(
                section,
                "Andes-Enhanced Performance Monitoring is present on this "
                "variant (mmsc_cfg.PMNDS=1)."
            );
        } else {
            vmidocAddText(
               section,
               "Andes-Enhanced Performance Monitoring is not present on this "
               "variant (mmsc_cfg.PMNDS=0)."
           );
        }
    }

    {
        vmiDocNodeP section = vmidocAddSection(
            andes, "CSRs for CCTL Operations"
        );

        if(CCTLCSR) {
            vmidocAddText(
                section,
                "CSRs for CCTL Operation are present on this variant "
                "(mmsc_cfg.CCTLCSR=1) but have no effect except that trap "
                "behavior for illegal use is modeled."
            );
        } else {
            vmidocAddText(
                section,
                "CSRs for CCTL Operation are not present on this variant "
                "(mmsc_cfg.CCTLCSR=0)."
            );
        }
    }

    if(EV5MPE || ECD || EFHW || BF16CVT || VL4 || VPFH) {

        codeSection = vmidocAddSection(andes, "Andes-Specific Instructions");

        // description
        vmidocAddText(
            codeSection,
            "This section describes Andes-specific instructions implemented by "
            "this variant. Refer to Andes reference documentation for more "
            "information."
        );
    }

    if(EV5MPE) {

        // document Performance Extension instructions
        vmiDocNodeP insts = vmidocAddSection(
            codeSection, "Performance Extension Instructions"
        );

        ////////////////////////////////////////////////////////////////////////
        // ADDIGP
        ////////////////////////////////////////////////////////////////////////

        docADDIGP(insts);

        ////////////////////////////////////////////////////////////////////////
        // BBC, BBS
        ////////////////////////////////////////////////////////////////////////

        docBBx(insts, "BBC", "0", xlen32, "Branch on bit is clear/zero.");
        docBBx(insts, "BBS", "1", xlen32, "Branch on bit is set/non-zero.");

        ////////////////////////////////////////////////////////////////////////
        // BEQC, BNEQ
        ////////////////////////////////////////////////////////////////////////

        docBxxC(insts, "BEQC", "101", "Branch on equal to a constant.");
        docBxxC(insts, "BNEC", "110", "Branch on not-equal to a constant.");

        ////////////////////////////////////////////////////////////////////////
        // BFOS, BFOZ
        ////////////////////////////////////////////////////////////////////////

        docBFOx(insts, "BFOS", "011", xlen32, "Sign-extended bit-field extract or insert operation.");
        docBFOx(insts, "BFOZ", "010", xlen32, "Zero-extended bit-field extract or insert operation.");

        ////////////////////////////////////////////////////////////////////////
        // LEA.h, LEA.w, LEA.d
        ////////////////////////////////////////////////////////////////////////

        docLEA(insts, "LEA.h",    "0000101", "Add a base register with a half-word-aligned offset from an offset register.");
        docLEA(insts, "LEA.w",    "0000110", "Add a base register with a word-aligned offset from an offset register.");
        docLEA(insts, "LEA.d",    "0000111", "Add a base register with a double-word-aligned offset from an offset register.");

        ////////////////////////////////////////////////////////////////////////
        // LEA.b.ze, LEA.h.ze, LEA.w.ze, LEA.d.ze (64-bit only)
        ////////////////////////////////////////////////////////////////////////

        if(!xlen32) {
            docLEA(insts, "LEA.b.ze", "0001000", "Add a base register with an unsigned 32-bit byte offset from an offset register.");
            docLEA(insts, "LEA.h.ze", "0001001", "Add a base register with an unsigned 32-bit half-word offset from an offset register.");
            docLEA(insts, "LEA.w.ze", "0001010", "Add a base register with an unsigned 32-bit word offset from an offset register.");
            docLEA(insts, "LEA.d.ze", "0001011", "Add a base register with an unsigned 32-bit double-word offset from an offset register.");
        }

        ////////////////////////////////////////////////////////////////////////
        // LBGP, LBUGP, LHGP, LHUGP, LWGP
        ////////////////////////////////////////////////////////////////////////

        docLBxGP(insts, "LBGP",  "00",  "Load a sign-extended 8-bit byte from memory into a general register.");
        docLBxGP(insts, "LBUGP", "10",  "Load a zero-extended 8-bit byte from memory into a general register.");
        docLHxGP(insts, "LHGP",  "001", "Load a sign-extended 16-bit half-word from memory into a general register.");
        docLHxGP(insts, "LHUGP", "101", "Load a zero-extended 16-bit half-word from memory into a general register.");
        docLWxGP(insts, "LWGP",  "010", "Load a sign-extended 32-bit word from memory into a general register.");

        ////////////////////////////////////////////////////////////////////////
        // LWUGP, LDGP (64-bit only)
        ////////////////////////////////////////////////////////////////////////

        if(!xlen32) {
            docLWxGP(insts, "LWUGP", "110", "Load a zero-extended 32-bit word from memory into a general register.");
            docLDGP (insts, "LDGP",  "011", "Load a 64-bit double-word from memory into a general register.");
        }

        ////////////////////////////////////////////////////////////////////////
        // SBGP, SHGP, SWGP
        ////////////////////////////////////////////////////////////////////////

        docSBGP(insts, "SBGP", "11",  "Store an 8-bit byte from a general register into a memory location.");
        docSHGP(insts, "SHGP", "000", "Store a 16-bit half-word from a general register into a memory location.");
        docSWGP(insts, "SWGP", "100", "Store a 32-bit word from a general register into a memory location.");

        ////////////////////////////////////////////////////////////////////////
        // SDGP (64-bit only)
        ////////////////////////////////////////////////////////////////////////

        if(!xlen32) {
            docSDGP(insts, "SDGP", "111", "Store a 64-bit double-word from a general register into a memory location.");
        }

        ////////////////////////////////////////////////////////////////////////
        // FFB, FFZMISM, FFMISM, FLMISM
        ////////////////////////////////////////////////////////////////////////

        docFFx(insts, "FFB",     "0010000", "Find the first byte in a first register that matches a value in a second register.");
        docFFx(insts, "FFZMISM", "0010001", "Find the first byte in a register that is zero or fails a corresponding byte comparison.");
        docFFx(insts, "FFMISM",  "0010010", "Find the first byte in a register that fails a corresponding byte comparison.");
        docFFx(insts, "FLMISM",  "0010011", "Find the last byte in a register that fails a corresponding byte comparison.");
    }

    if(ECD) {

        vmiDocNodeP insts = vmidocAddSection(
            codeSection, "CodeDense Instructions"
        );

        ////////////////////////////////////////////////////////////////////////
        // EXEC.IT, EX9.IT
        ////////////////////////////////////////////////////////////////////////

        docEXECIT(insts, False);
        docEXECIT(insts, True);
    }

    if(EFHW) {

        // document Half-Precision Load/Store instructions
        vmiDocNodeP insts = vmidocAddSection(
            codeSection, "Half-Precision Load/Store Instructions"
        );

        ////////////////////////////////////////////////////////////////////////
        // FLHW, FSHW
        ////////////////////////////////////////////////////////////////////////

        docFLHW(insts);
        docFSHW(insts);
    }

    if(BF16CVT) {

        // document BFLOAT16 conversion instructions
        vmiDocNodeP insts = vmidocAddSection(
            codeSection, "BFLOAT16 Conversion Instructions"
        );

        ////////////////////////////////////////////////////////////////////////
        // VFWCVT.S.BF16, VFWCVT.BF16.S, FCVT.S.BF16, FCVT.BF16.S
        ////////////////////////////////////////////////////////////////////////

        docFCVT(insts, "VFWCVT.S.BF16", "00000", "Vd", "Vs1", "Convert vector BFLOAT16 to vector F32");
        docFCVT(insts, "VFWCVT.BF16.S", "00001", "Vd", "Vs1", "Convert vector BFLOAT16 from vector F32");
        docFCVT(insts, "FCVT.S.BF16",   "00010", "Fd", "Fs1", "Convert scalar BFLOAT16 to scalar F32");
        docFCVT(insts, "FCVT.BF16.S",   "00011", "Fd", "Fs1", "Convert scalar BFLOAT16 from scalar F32");
    }

    if(VL4) {

        // document vector INT4 load instructions
        vmiDocNodeP insts = vmidocAddSection(
            codeSection, "Vector INT4 Load Instructions"
        );

        ////////////////////////////////////////////////////////////////////////
        // VLN.V, VLUN.V, VLN8.V, VLNU8.V
        ////////////////////////////////////////////////////////////////////////

        docINT4(insts, "VLN.V",   "00000", "Load signed INT4, active SEW.");
        docINT4(insts, "VLUN.V",  "00001", "Load unsigned INT4, active SEW.");
        docINT4(insts, "VLN8.V",  "00010", "Load signed INT4, SEW=8.");
        docINT4(insts, "VLNU8.V", "00011", "Load unsigned INT4, SEW=8.");
    }

    if(VPFH) {

        // document vector packed FP16 instructions
        vmiDocNodeP insts = vmidocAddSection(
            codeSection, "Vector Packed FP16 Instructions"
        );

        ////////////////////////////////////////////////////////////////////////
        // VLN.V, VLUN.V, VLN8.V, VLNU8.V
        ////////////////////////////////////////////////////////////////////////

        docVPFH(insts, "VFPMADT.VF", "000010", "Vector Single-Width Floating-Point Packed Fused Multiply-Add with Top FP16 as Multiplicand).");
        docVPFH(insts, "VFPMADB.VF", "000011", "Vector Single-Width Floating-Point Packed Fused Multiply-Add with Bottom FP16 as Multiplicand).");
    }

    vmidocProcessor(processor, andes);
}

//
// Add documentation for Andes instructions
//
VMIOS_DOC_FN(andesDoc) {

    if(andesIsLeaf(object->riscv)) {
        docInt(processor, object);
    }
}


