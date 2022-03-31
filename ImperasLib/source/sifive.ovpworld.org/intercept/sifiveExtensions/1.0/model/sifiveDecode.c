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
#include "vmi/vmiCxt.h"
#include "vmi/vmiDecode.h"
#include "vmi/vmiMessage.h"

// model header files
#include "sifiveCSR.h"
#include "sifiveDecode.h"
#include "sifiveDecodeTypes.h"
#include "sifiveDisassembleFormats.h"
#include "sifiveInstructionInfo.h"
#include "sifiveMessage.h"
#include "sifiveTypeRefs.h"
#include "sifiveStructure.h"
#include "sifiveUtils.h"

// base model header files
#include "riscvStructure.h"
#include "riscvRegisters.h"


////////////////////////////////////////////////////////////////////////////////
// UTILITIES
////////////////////////////////////////////////////////////////////////////////

//
// Return current XLEN bits
//
inline static Uns32 getXLenBits(riscvP riscv) {
    return sifiveGetXlenMode(riscv);
}


////////////////////////////////////////////////////////////////////////////////
// FIELD EXTRACTION MACROS
////////////////////////////////////////////////////////////////////////////////

//
// Extract _BITS from _ARG, zero-extending left
//
#define UBITS(_BITS, _ARG)  ((_ARG)&((1<<(_BITS))-1))

// unsigned field extraction macros
#define U_19_15(_I)         UBITS(5, (_I)>>15)


////////////////////////////////////////////////////////////////////////////////
// INSTRUCTION DESCRIPTIONS
////////////////////////////////////////////////////////////////////////////////

//
// Define the encoding of register in an instruction
//
typedef enum rSpecE {
    R_NA,               // no register
    RS_X_19_15,         // X register in 19:15
} rSpec;

//
// Structure defining characteristics of each opcode type
//
typedef struct opAttrsS {
    const char       *opcode;           // opcode name
    const char       *pattern;          // decode pattern
    const char       *format;           // format string
    riscvArchitecture arch;             // architectural requirements
    sifiveIType       type     :  8;    // equivalent generic instruction
    rSpec             r1       :  8;    // specification of r1
} opAttrs;

typedef const struct opAttrsS *opAttrsCP;


////////////////////////////////////////////////////////////////////////////////
// 32-BIT INSTRUCTION TYPES
////////////////////////////////////////////////////////////////////////////////

//
// Instruction type enumeration
//
typedef enum sifiveIType32E {

    IT32_CFLUSH_D_L1,
    IT32_CDISCARD_D_L1,
    IT32_CEASE,

    // KEEP LAST
    IT32_LAST

} sifiveIType32;

//
// This specifies attributes for each 32-bit opcode
//
const static opAttrs attrsArray32[] = {

    // SiFive custom instructions                                  |   csr      | rs1 |fn3| rd  | SYSTEM|
    ATTR32_CFLUSH(  CFLUSH_D_L1, CFLUSH, RVANY,  "cflush.d.l1",   "|111111000000|.....|000|00000|1110011|"),
    ATTR32_CFLUSH(CDISCARD_D_L1, CFLUSH, RVANY,  "cdiscard.d.l1", "|111111000010|.....|000|00000|1110011|"),
    ATTR32_CEASE (        CEASE,  CEASE, RVANY,  "cease",         "|001100000101|00000|000|00000|1110011|"),

    // dummy entry for undecoded instruction
    ATTR32_LAST  (       LAST,   LAST, 0)
};

//
// Create the 32-bit instruction decode table
//
static vmidDecodeTableP createDecodeTable32() {

    // create the table
    vmidDecodeTableP table = vmidNewDecodeTable(32, IT32_LAST);
    sifiveIType32    i;

    for(i=0; i<IT32_LAST; i++) {

        opAttrsCP entry = &attrsArray32[i];

        VMI_ASSERT(entry->opcode, "invalid attribute entry (index %u)", i);

        vmidNewEntryFmtBin(
            table,
            entry->opcode,
            i,
            entry->pattern,
            0
        );
    }

    return table;
}

//
// Classify 32-bit instruction
//
static sifiveIType32 getInstructionType32(
    riscvP           riscv,
    vmiosObjectP     object,
    sifiveInstrInfoP info
) {
    static vmidDecodeTableP decodeTable;

    // create instruction decode table if required
    if(!decodeTable) {
        decodeTable = createDecodeTable32();
    }

    // decode the instruction using decode table
    return vmidDecode(decodeTable, info->instruction);
}

//
// Return register index encoded in the instruction
//
static riscvRegDesc getRegister(
    riscvP           riscv,
    sifiveInstrInfoP info,
    rSpec            r
) {
    riscvRegDesc result   = RV_RD_NA;
    Uns32        instr    = info->instruction;

    switch(r) {
        case R_NA:
            break;
        case RS_X_19_15:
            result = RV_RD_X | U_19_15(instr);
            break;
        default:
            VMI_ABORT("unimplemented case"); // LCOV_EXCL_LINE
            break;
    }

    // fill register width
    if(result && !getRBits(result)) {
        result |= ((getXLenBits(riscv)==32) ? RV_RD_32 : RV_RD_64);
    }

    return result;
}

//
// Interpret an instruction using the given attributes
//
static void interpretInstruction(
    riscvP           riscv,
    sifiveInstrInfoP info,
    opAttrsCP        attrs
) {
    // fill fields from decoded instruction type
    info->type    = attrs->type;
    info->opcode  = attrs->opcode;
    info->format  = attrs->format;
    info->arch    = attrs->arch;
    info->r[0]    = getRegister(riscv, info, attrs->r1);
}

//
// Decode a 32-bit instruction at the given address
//
static void decode32(riscvP riscv, vmiosObjectP object, sifiveInstrInfoP info) {

    // decode the instruction using decode table
    sifiveIType32 type = getInstructionType32(riscv, object, info);

    // interpret instruction fields
    interpretInstruction(riscv, info, &attrsArray32[type]);
}

//
// Decode instruction at the given address
//
void sifiveDecode(
    riscvP           riscv,
    vmiosObjectP     object,
    riscvAddr        thisPC,
    sifiveInstrInfoP info
) {
    Uns64 instr = 0;

    info->type        = S5_IT_LAST;
    info->bytes       = vmicxtFetch((vmiProcessorP)riscv, thisPC, &instr);
    info->instruction = instr;
    info->thisPC      = thisPC;

    // decode based on instruction size
    if(info->bytes==4) {
        decode32(riscv, object, info);
    }
}

