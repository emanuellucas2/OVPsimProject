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
#include "andesCSR.h"
#include "andesCustomPhases.h"
#include "andesDecode.h"
#include "andesDecodeTypes.h"
#include "andesDisassembleFormats.h"
#include "andesInstructionInfo.h"
#include "andesMessage.h"
#include "andesTypeRefs.h"
#include "andesStructure.h"
#include "andesUtils.h"

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
    return andesGetXlenMode(riscv);
}

//
// Return current XLEN architecture
//
static riscvArchitecture getXLenArch(riscvP riscv) {
    return getXLenBits(riscv)==32 ? ISA_XLEN_32 : ISA_XLEN_64;
}


////////////////////////////////////////////////////////////////////////////////
// FIELD EXTRACTION MACROS
////////////////////////////////////////////////////////////////////////////////

//
// Extract _BITS from _ARG, zero-extending left
//
#define UBITS(_BITS, _ARG)  ((_ARG)&((1<<(_BITS))-1))

//
// Extract _BITS from _ARG, sign-extending left
//
#define SBITS(_BITS, _ARG)  (((Int32)((_ARG)<<(32-_BITS)))>>(32-_BITS))

// unsigned field extraction macros
#define U_2(_I)             UBITS(1, (_I)>> 2)
#define U_3(_I)             UBITS(1, (_I)>> 3)
#define U_4(_I)             UBITS(1, (_I)>> 4)
#define U_6_5(_I)           UBITS(2, (_I)>> 5)
#define U_7(_I)             UBITS(1, (_I)>> 7)
#define U_11_7(_I)          UBITS(5, (_I)>> 7)
#define U_8(_I)             UBITS(1, (_I)>> 8)
#define U_9_8(_I)           UBITS(2, (_I)>> 8)
#define U_11_8(_I)          UBITS(4, (_I)>> 8)
#define U_9(_I)             UBITS(1, (_I)>> 9)
#define U_11_9(_I)          UBITS(3, (_I)>> 9)
#define U_11_10(_I)         UBITS(2, (_I)>>10)
#define U_12(_I)            UBITS(1, (_I)>>12)
#define U_13_12(_I)         UBITS(2, (_I)>>12)
#define U_13(_I)            UBITS(1, (_I)>>13)
#define U_14(_I)            UBITS(1, (_I)>>14)
#define U_16_15(_I)         UBITS(2, (_I)>>15)
#define U_19_15(_I)         UBITS(5, (_I)>>15)
#define U_19_17(_I)         UBITS(3, (_I)>>17)
#define U_20(_I)            UBITS(1, (_I)>>20)
#define U_24_20(_I)         UBITS(5, (_I)>>20)
#define U_25_20(_I)         UBITS(6, (_I)>>20)
#define U_21(_I)            UBITS(1, (_I)>>21)
#define U_22_21(_I)         UBITS(2, (_I)>>21)
#define U_30_21(_I)         UBITS(10,(_I)>>21)
#define U_30_22(_I)         UBITS(9, (_I)>>22)
#define U_30_23(_I)         UBITS(8, (_I)>>23)
#define U_25(_I)            UBITS(1, (_I)>>25)
#define U_26_25(_I)         UBITS(2, (_I)>>25)
#define U_29_25(_I)         UBITS(5, (_I)>>25)
#define U_30_25(_I)         UBITS(6, (_I)>>25)
#define U_31_26(_I)         UBITS(6, (_I)>>26)
#define U_28(_I)            UBITS(1, (_I)>>28)
#define U_30(_I)            UBITS(1, (_I)>>30)

// signed field extraction macros
#define S_31(_I)            SBITS(1, (_I)>>31)
#define S_31_25(_I)         SBITS(7, (_I)>>25)
#define S_31_20(_I)         SBITS(12,(_I)>>20)


////////////////////////////////////////////////////////////////////////////////
// INSTRUCTION DESCRIPTIONS
////////////////////////////////////////////////////////////////////////////////

//
// Define the encoding of memory bit size in an instruction
//
typedef enum memBitsSpecE {
    MBS_NA,             // instruction has no memory bit size
    MBS_13_12,          // memory bit size in bits 13:12
    MBS_26_25,          // memory bit size in bits 26:25
    MBS_B,              // memory bit size 8 (byte)
    MBS_H,              // memory bit size 16 (half word)
    MBS_W,              // memory bit size 32 (word)
    MBS_D,              // memory bit size 64 (double word)
} memBitsSpec;

//
// Define the encoding of 32-bit unsigned extend boolean in an instruction
//
typedef enum ze32SpecE {
    ZE32_NA,            // instruction has no extension specification
    ZE32_28,            // extension specification in bit 28
} ze32Spec;

//
// Define the encoding of unsigned extend boolean in an instruction
//
typedef enum unsExtSpecE {
    USX_NA,             // instruction has no extension specification
    USX_13,             // extension specification in bit 13
    USX_14,             // extension specification in bit 14
    USX_20,             // extension specification in bit 20
} unsExtSpec;

//
// Define the encoding of a constant in an instruction
//
typedef enum constSpecE {
    CS_NA,              // instruction has no constant
    CS_LBGP_IMM,        // signed imm (LBGP encoding)
    CS_LHGP_IMM,        // signed imm (LHGP encoding)
    CS_LWGP_IMM,        // signed imm (LWGP encoding)
    CS_LDGP_IMM,        // signed imm (LDGP encoding)
    CS_SBGP_IMM,        // signed imm (SBGP encoding)
    CS_SHGP_IMM,        // signed imm (SHGP encoding)
    CS_SWGP_IMM,        // signed imm (SWGP encoding)
    CS_SDGP_IMM,        // signed imm (SDGP encoding)
    CS_BBC_IMM,         // signed imm (BCC encoding)
    CU_BBC_SHAMT,       // unsigned cimm shift (BCC encoding)
    CU_BEQC_CIMM,       // unsigned cimm (BEQC encoding)
    CU_BFOS_LSB,        // unsigned lsb (BFOS encoding)
    CU_BFOS_MSB,        // unsigned msb (BFOS encoding)
    CU_EXEC_IT_IMM,     // unsigned imm (EXEC_IT encoding)
    CS_S_31_20,         // signed value in 31:20
    CS_S_31_25_11_7,    // signed value in 31:25,11:7
} constSpec;

//
// Define the encoding of register in an instruction
//
typedef enum rSpecE {
    R_NA,               // no register
    RS_X_11_7,          // X register in 11:7
    RS_X_19_15,         // X register in 19:15
    RS_X_24_20,         // X register in 24:20
    RS_GP,              // implicit GP register
    RS_F_11_7,          // 32-bit floating point register in 11:7
    RS_F_19_15,         // 32-bit floating point register in 19:15
    RS_F_24_20,         // 32-bit floating point register in 24:20
    RS_V_11_7,          // vector register in 11:7
    RS_V_24_20,         // vector register in 24:20
    RS_V_M_25,          // vector mask register in bit 25
} rSpec;

//
// Define the encoding of X register width specifier in an instruction
//
typedef enum wxSpecE {
    WX_NA,              // no width
} wxSpec;

//
// Define the encoding of X register width specifier in an instruction
//
typedef enum elemBitsSpecE {
    EBS_NA,             // no element bits
    EBS_21,             // element bits in bit 21
} elemBitsSpec;

//
// Structure defining characteristics of each opcode type
//
typedef struct opAttrsS {
    const char       *opcode;           // opcode name
    const char       *pattern;          // decode pattern
    const char       *format;           // format string
    riscvArchitecture arch;             // architectural requirements
    andesIType        type     :  8;    // equivalent generic instruction
    rSpec             r1       :  8;    // specification of r1
    rSpec             r2       :  8;    // specification of r2
    rSpec             r3       :  8;    // specification of r3
    rSpec             r4       :  8;    // specification of r4
    rSpec             mask     :  8;    // specification of vector mask
    constSpec         cs1      :  8;    // location of constant 1
    constSpec         cs2      :  8;    // location of constant 2
    wxSpec            wX       :  4;    // X register width specification
    memBitsSpec       memBits  :  4;    // load/store size specification
    unsExtSpec        unsExt   :  4;    // unsigned extend specification
    Uns32             priDelta :  4;    // decode priority delta
    ze32Spec          ze32     :  1;    // zero-extend 32-bit argument?
    Bool              cvtF32   :  1;    // includes implicit F32 conversion?
    elemBitsSpec      elemBits :  1;    // element bits specification
    Bool              unsExtQ  :  1;    // whether extend unsigned implicit
} opAttrs;

typedef const struct opAttrsS *opAttrsCP;


////////////////////////////////////////////////////////////////////////////////
// 32-BIT INSTRUCTION TYPES
////////////////////////////////////////////////////////////////////////////////

//
// Instruction type enumeration
//
typedef enum andesIType32E {

    // add immediate instruction
    IT32_ADDIGP,

    // branch instructions
    IT32_BBC,
    IT32_BBS,
    IT32_BEQC,
    IT32_BNEC,

    // bit field instructions
    IT32_BFOS,
    IT32_BFOZ,

    // load effective address instructions
    IT32_LEA_H,
    IT32_LEA_W,
    IT32_LEA_D,
    IT32_LEA_B_ZE,
    IT32_LEA_H_ZE,
    IT32_LEA_W_ZE,
    IT32_LEA_D_ZE,

    // load instructions
    IT32_LBGP,
    IT32_LBUGP,
    IT32_LHGP,
    IT32_LHUGP,
    IT32_LWGP,
    IT32_LWUGP,
    IT32_LDGP,

    // store instructions
    IT32_SBGP,
    IT32_SHGP,
    IT32_SWGP,
    IT32_SDGP,

    // find instructions
    IT32_FFB,
    IT32_FFZMISM,
    IT32_FFMISM,
    IT32_FLMISM,

    // half-precision floating-point instructions
    IT32_FLHW,
    IT32_FSHW,

    // int4 vector load extension instructions
    IT32_VLNV,
    IT32_VLNUV,
    IT32_VLN8V,
    IT32_VLNU8V,

    // bfloat16 extension instructions
    IT32_VFWCVT_S_BF16,
    IT32_VFNCVT_BF16_S,
    IT32_FCVT_S_BF16,
    IT32_FCVT_BF16_S,

    // vector packed FP16 extension
    IT32_VFPMADT_VF,
    IT32_VFPMADB_VF,

    // base I-type instructions for load
    IT32_LH_I,
    IT32_LW_I,
    IT32_LD_I,

    // base S-type instructions for store
    IT32_SH_I,
    IT32_SW_I,
    IT32_SD_I,

    // define custom instructions
    #if defined(CUSTOMFILE)
        #define ANDES_CUSTOM_PHASE ANDES_CUSTOM_DECODE32
        #include CUSTOMFILE
        #undef ANDES_CUSTOM_PHASE
    #endif

    // KEEP LAST
    IT32_LAST

} andesIType32;

//
// This specifies attributes for each 32-bit opcode
// NOTE: FLHW and FSHW are located illegally in non-custom space
//
const static opAttrs attrsArray32[] = {

    // add immediate instruction                                    |        imm       |op| rd  |custom0|
    ATTR32_ADDIGP    (   ADDIGP, ADDI,    RVANY,  "addi",          "|..................|01|.....|0001011|"),

    // branch instructions                                          | | |imm95|cim40| rs1 |op |im41| |custom2|
    ATTR32_BBC       (      BBC, BBC,     RVANY,  "bbc",           "|.|0|.....|.....|.....|111|....|.|1011011|"),
    ATTR32_BBC       (      BBS, BBS,     RVANY,  "bbs",           "|.|1|.....|.....|.....|111|....|.|1011011|"),
    ATTR32_BEQC      (     BEQC, BEQC,    RVANY,  "beqc",          "|.|.|.....|.....|.....|101|....|.|1011011|"),
    ATTR32_BEQC      (     BNEC, BNEC,    RVANY,  "bnec",          "|.|.|.....|.....|.....|110|....|.|1011011|"),

    // bit field instructions                                       | msb  | lsb  | rs1 |op | rd  |custom2|
    ATTR32_BFOS      (     BFOS, BFOS,    RVANY,  "bfos",          "|......|......|.....|011|.....|1011011|"),
    ATTR32_BFOS      (     BFOZ, BFOZ,    RVANY,  "bfoz",          "|......|......|.....|010|.....|1011011|"),

    // load effective address instructions                          |  op   | rs2 | rs1 |op | rd  |custom2|
    ATTR32_LEA       (    LEA_H, LEA,     RVANY,  "lea.",          "|0000101|.....|.....|000|.....|1011011|"),
    ATTR32_LEA       (    LEA_W, LEA,     RVANY,  "lea.",          "|0000110|.....|.....|000|.....|1011011|"),
    ATTR32_LEA       (    LEA_D, LEA,     RVANY,  "lea.",          "|0000111|.....|.....|000|.....|1011011|"),
    ATTR32_LEA       ( LEA_B_ZE, LEA,     RV64,   "lea.",          "|0001000|.....|.....|000|.....|1011011|"),
    ATTR32_LEA       ( LEA_H_ZE, LEA,     RV64,   "lea.",          "|0001001|.....|.....|000|.....|1011011|"),
    ATTR32_LEA       ( LEA_W_ZE, LEA,     RV64,   "lea.",          "|0001010|.....|.....|000|.....|1011011|"),
    ATTR32_LEA       ( LEA_D_ZE, LEA,     RV64,   "lea.",          "|0001011|.....|.....|000|.....|1011011|"),

    // load instructions                                            |        imm       |op| rd  |custom |
    ATTR32_LBGP      (     LBGP, L,       RVANY,  "l",             "|..................|00|.....|0001011|"),
    ATTR32_LBGP      (    LBUGP, L,       RVANY,  "l",             "|..................|10|.....|0001011|"),
    ATTR32_LHGP      (     LHGP, L,       RVANY,  "l",             "|.................|001|.....|0101011|"),
    ATTR32_LHGP      (    LHUGP, L,       RVANY,  "l",             "|.................|101|.....|0101011|"),
    ATTR32_LWGP      (     LWGP, L,       RVANY,  "l",             "|.................|010|.....|0101011|"),
    ATTR32_LWGP      (    LWUGP, L,       RV64,   "l",             "|.................|110|.....|0101011|"),
    ATTR32_LDGP      (     LDGP, L,       RV64,   "l",             "|.................|011|.....|0101011|"),

    // store instructions                                           |  imm  | rs2 | imm  |op| imm |custom |
    ATTR32_SBGP      (     SBGP, S,       RVANY,  "s",             "|.......|.....|......|11|.....|0001011|"),
    ATTR32_SHGP      (     SHGP, S,       RVANY,  "s",             "|.......|.....|.....|000|.....|0101011|"),
    ATTR32_SWGP      (     SWGP, S,       RVANY,  "s",             "|.......|.....|.....|100|.....|0101011|"),
    ATTR32_SDGP      (     SDGP, S,       RV64,   "s",             "|.......|.....|.....|111|.....|0101011|"),

    // find instructions                                            |  op   | rs2 | rs1 |op | rd  |custom2|
    ATTR32_FFB       (      FFB, FFB,     RVANY,  "ffb",           "|0010000|.....|.....|000|.....|1011011|"),
    ATTR32_FFB       (  FFZMISM, FFZMISM, RVANY,  "ffzmism",       "|0010001|.....|.....|000|.....|1011011|"),
    ATTR32_FFB       (   FFMISM, FFMISM,  RVANY,  "ffmism",        "|0010010|.....|.....|000|.....|1011011|"),
    ATTR32_FFB       (   FLMISM, FLMISM,  RVANY,  "flmism",        "|0010011|.....|.....|000|.....|1011011|"),

    // half-precision floating-point instructions                   |    imm32   | rs1 |fun| rd  |ILLEGAL|
    ATTR32_FLHW      (     FLHW, FLHW,    RVANY,  "fl",            "|............|.....|000|.....|0000111|"),
    ATTR32_FSHW      (     FSHW, FSHW,    RVANY,  "fs",            "|............|.....|000|.....|0100111|"),

    // int4 vector load extension instructions                      |  op  |m| op  | rs1 |op | vd  |custom2|
    ATTR32_VLNV      (     VLNV, VLNV,    RVANYV, "vln.v",         "|000001|.|00000|.....|100|.....|1011011|"),
    ATTR32_VLNV      (    VLNUV, VLNV,    RVANYV, "vlun.v",        "|000001|.|00001|.....|100|.....|1011011|"),
    ATTR32_VLNV      (    VLN8V, VLNV,    RVANYV, "vln8.v",        "|000001|.|00010|.....|100|.....|1011011|"),
    ATTR32_VLNV      (   VLNU8V, VLNV,    RVANYV, "vlnu8.v",       "|000001|.|00011|.....|100|.....|1011011|"),

    // bfloat16 extension instructions                              |  op   | rs  | op  |op | rd  |custom2|
    ATTR32_VFCVT     (  VFWCVT_S_BF16,    RVANYV, "vfwcvt.s.bf16", "|0000000|.....|00000|100|.....|1011011|"),
    ATTR32_VFCVT     (  VFNCVT_BF16_S,    RVANYV, "vfncvt.bf16.s", "|0000000|.....|00001|100|.....|1011011|"),
    ATTR32_FCVT      (    FCVT_S_BF16,    RVANYF, "fcvt.s.bf16",   "|0000000|.....|00010|100|.....|1011011|"),
    ATTR32_FCVT      (    FCVT_BF16_S,    RVANYF, "fcvt.bf16.s",   "|0000000|.....|00011|100|.....|1011011|"),

    // vector packed FP16 extension                                 |  op  |m| vs2 | rs1 |op | vd  |custom2|
    ATTR32_VFPMADT_VF(     VFPMADT_VF,    RVANYV, "vfpmadt.vf",    "|000010|.|.....|.....|100|.....|1011011|"),
    ATTR32_VFPMADT_VF(     VFPMADB_VF,    RVANYV, "vfpmadb.vf",    "|000011|.|.....|.....|100|.....|1011011|"),

    // base I-type instructions for load                            |   imm32    | rs1 |fun| rd  | opcode|
    ATTR32_BASE      (  LH_I, MSA_UNA,    RVANY,  "unaligned",     "|............|.....|.01|.....|0000011|"),
    ATTR32_BASE      (  LW_I, MSA_UNA,    RVANY,  "unaligned",     "|............|.....|.10|.....|0000011|"),
    ATTR32_BASE      (  LD_I, MSA_UNA,    RVANY,  "unaligned",     "|............|.....|011|.....|0000011|"),

    // base S-type instructions for store                           | imm32 | rs2 | rs 1|fun|imm32| opcode|
    ATTR32_BASE      (  SH_I, MSA_UNA,    RVANY,  "unaligned",     "|.......|.....|.....|001|.....|0100011|"),
    ATTR32_BASE      (  SW_I, MSA_UNA,    RVANY,  "unaligned",     "|.......|.....|.....|010|.....|0100011|"),
    ATTR32_BASE      (  SD_I, MSA_UNA,    RVANY,  "unaligned",     "|.......|.....|.....|011|.....|0100011|"),

    // define custom instructions
    #if defined(CUSTOMFILE)
        #define ANDES_CUSTOM_PHASE ANDES_CUSTOM_INSTRUCTION_ATTRS
        #include CUSTOMFILE
        #undef ANDES_CUSTOM_PHASE
    #endif

    // dummy entry for undecoded instruction
    ATTR32_LAST      (     LAST, LAST,    0)
};

//
// Create the 32-bit instruction decode table
//
static vmidDecodeTableP createDecodeTable32(Bool addFLSHP) {

    // create the table
    vmidDecodeTableP table = vmidNewDecodeTable(32, IT32_LAST);
    andesIType32     i;

    for(i=0; i<IT32_LAST; i++) {

        opAttrsCP entry = &attrsArray32[i];

        VMI_ASSERT(entry->opcode, "invalid attribute entry (index %u)", i);

        // NOTE: FLHW and FSHW are added only if that feature is enabled (these
        // instructions conflict with the standard vector extension)
        if(addFLSHP || ((i!=IT32_FLHW) && (i!=IT32_FSHW))) {
            vmidNewEntryFmtBin(
                table,
                entry->opcode,
                i,
                entry->pattern,
                VMID_DERIVE_PRIORITY + entry->priDelta
            );
        }
    }

    return table;
}

//
// Classify 32-bit instruction
//
static andesIType32 getInstructionType32(
    riscvP          riscv,
    vmiosObjectP    object,
    andesInstrInfoP info
) {
    Bool addFLSHP = RD_XCSR_FIELD(object, mmsc_cfg, EFHW);

    static vmidDecodeTableP decodeTable[2];

    // create instruction decode table if required
    if(!decodeTable[addFLSHP]) {
        decodeTable[addFLSHP] = createDecodeTable32(addFLSHP);
    }

    // decode the instruction using decode table
    return vmidDecode(decodeTable[addFLSHP], info->instruction);
}


////////////////////////////////////////////////////////////////////////////////
// 16-BIT INSTRUCTION TYPES
////////////////////////////////////////////////////////////////////////////////

//
// Instruction type enumeration
//
typedef enum andesIType16E {

    // execute table instruction
    IT16_EXEC_IT,
    IT16_EX9_IT,

    // base I-type instructions
    IT16_MSA_UNA,

    // KEEP LAST
    IT16_LAST

} andesIType16;

//
// This specifies attributes for each 32-bit opcode
//
const static opAttrs attrsArray16[] = {

    // execute table instructions                           |op |imm |op| imm |op|
    ATTR16_EXEC_IT ( EXEC_IT, EXEC_IT, RVANY, "exec.it",   "|100|....|.0|.....|00|"),
    ATTR16_EXEC_IT ( EX9_IT,  EXEC_IT, RVANY, "ex9.it",    "|100|....|00|.....|00|"),

    // base I-type instructions
    ATTR16_BASE    ( MSA_UNA, MSA_UNA, RVANY, "unaligned", "|.1.|......|.....|.0|"),

    // dummy entry for undecoded instruction
    ATTR16_LAST    ( LAST,    LAST,    0)
};

//
// Create the 16-bit instruction decode table
//
static vmidDecodeTableP createDecodeTable16(void) {

    // create the table
    vmidDecodeTableP table = vmidNewDecodeTable(16, IT16_LAST);
    andesIType16     i;

    for(i=0; i<IT16_LAST; i++) {

        opAttrsCP entry = &attrsArray16[i];

        VMI_ASSERT(entry->opcode, "invalid attribute entry (index %u)", i);

        vmidNewEntryFmtBin(
            table,
            entry->opcode,
            i,
            entry->pattern,
            VMID_DERIVE_PRIORITY + entry->priDelta
        );
    }

    return table;
}

//
// Classify 16-bit instruction
//
static andesIType16 getInstructionType16(riscvP riscv, andesInstrInfoP info) {

    static vmidDecodeTableP decodeTable;

    // create instruction decode table if required
    if(!decodeTable) {
        decodeTable = createDecodeTable16();
    }

    // decode the instruction using decode table
    return vmidDecode(decodeTable, info->instruction);
}


////////////////////////////////////////////////////////////////////////////////
// INSTRUCTION INTERPRETATION
////////////////////////////////////////////////////////////////////////////////

//
// Return X register width specifier encoded in the instruction
//
static riscvRegDesc getXWidth(riscvP riscv, andesInstrInfoP info, wxSpec w) {

    riscvRegDesc current = (getXLenBits(riscv)==32) ? RV_RD_32 : RV_RD_64;
    riscvRegDesc result;

    switch(w) {
        case WX_NA:
            result = current;
            break;
        default:
            VMI_ABORT("unimplemented case"); // LCOV_EXCL_LINE
            break;
    }

    return result;
}

//
// Force undefined instructon if shift amount >= XLEN
//
static void bitValueConstraint(riscvP riscv, andesInstrInfoP info, Uns32 c) {
    if(c>=getXLenBits(riscv)) {
        info->arch &= ~getXLenArch(riscv);
    }
}

//
// Return a constant encoded within the instruction
//
static Uns64 getConstant(riscvP riscv, andesInstrInfoP info, constSpec c) {

    Uns64 result = 0;
    Uns32 instr  = info->instruction;

    switch(c) {
        case CS_NA:
            break;
        case CS_LBGP_IMM:
            result  = S_31(instr)    << 17;
            result += U_16_15(instr) << 15;
            result += U_19_17(instr) << 12;
            result += U_20(instr)    << 11;
            result += U_30_21(instr) <<  1;
            result += U_14(instr)    <<  0;
            break;
        case CS_LHGP_IMM:
            result  = S_31(instr)    << 16;
            result += U_16_15(instr) << 14;
            result += U_19_17(instr) << 11;
            result += U_20(instr)    << 10;
            result += U_30_21(instr) <<  0;
            break;
        case CS_LWGP_IMM:
            result  = S_31(instr)    << 16;
            result += U_21(instr)    << 15;
            result += U_16_15(instr) << 13;
            result += U_19_17(instr) << 10;
            result += U_20(instr)    <<  9;
            result += U_30_22(instr) <<  0;
            break;
        case CS_LDGP_IMM:
            result  = S_31(instr)    << 16;
            result += U_22_21(instr) << 14;
            result += U_16_15(instr) << 12;
            result += U_19_17(instr) <<  9;
            result += U_20(instr)    <<  8;
            result += U_30_23(instr) <<  0;
            break;
        case CS_SBGP_IMM:
            result  = S_31(instr)    << 17;
            result += U_16_15(instr) << 15;
            result += U_19_17(instr) << 12;
            result += U_7(instr)     << 11;
            result += U_30_25(instr) <<  5;
            result += U_11_8(instr)  <<  1;
            result += U_14(instr)    <<  0;
            break;
        case CS_SHGP_IMM:
            result  = S_31(instr)    << 16;
            result += U_16_15(instr) << 14;
            result += U_19_17(instr) << 11;
            result += U_7(instr)     << 10;
            result += U_30_25(instr) <<  4;
            result += U_11_8(instr)  <<  0;
            break;
        case CS_SWGP_IMM:
            result  = S_31(instr)    << 16;
            result += U_8(instr)     << 15;
            result += U_16_15(instr) << 13;
            result += U_19_17(instr) << 10;
            result += U_7(instr)     <<  9;
            result += U_30_25(instr) <<  3;
            result += U_11_9(instr)  <<  0;
            break;
        case CS_SDGP_IMM:
            result  = S_31(instr)    << 16;
            result += U_9_8(instr)   << 14;
            result += U_16_15(instr) << 12;
            result += U_19_17(instr) <<  9;
            result += U_7(instr)     <<  8;
            result += U_30_25(instr) <<  2;
            result += U_11_10(instr) <<  0;
            break;
        case CS_BBC_IMM:
            result  = S_31(instr)    << 10;
            result += U_29_25(instr) <<  5;
            result += U_11_8(instr)  <<  1;
            result += info->thisPC;
            break;
        case CU_BBC_SHAMT:
            result  = U_7(instr)     << 5;
            result += U_24_20(instr) << 0;
            // undefined if shift amount >= XLEN
            bitValueConstraint(riscv, info, result);
            break;
        case CU_BEQC_CIMM:
            result  = U_30(instr)    << 6;
            result += U_7(instr)     << 5;
            result += U_24_20(instr) << 0;
            break;
        case CU_BFOS_LSB:
            result = U_25_20(instr) << 0;
            // undefined if shift amount >= XLEN
            bitValueConstraint(riscv, info, result);
            break;
        case CU_BFOS_MSB:
            result = U_31_26(instr) << 0;
            // undefined if shift amount >= XLEN
            bitValueConstraint(riscv, info, result);
            break;
        case CU_EXEC_IT_IMM:
            result  = U_8(instr)     << 9;
            result += U_12(instr)    << 8;
            result += U_3(instr)     << 7;
            result += U_9(instr)     << 6;
            result += U_6_5(instr)   << 4;
            result += U_2(instr)     << 3;
            result += U_11_10(instr) << 1;
            result += U_4(instr)     << 0;
            break;
        case CS_S_31_20:
            result = S_31_20(instr);
            break;
        case CS_S_31_25_11_7:
            result  = S_31_25(instr) << 5;
            result += U_11_7(instr);
            break;
        default:
            VMI_ABORT("unimplemented case"); // LCOV_EXCL_LINE
            break;
    }

    // scale by memory bit size
    if(info->memBits && !info->cvtF32) {
        result *= (info->memBits/8);
    }

    return result;
}

//
// Return register index encoded in the instruction
//
static riscvRegDesc getRegister(
    riscvP          riscv,
    andesInstrInfoP info,
    rSpec           r,
    riscvRegDesc    wX
) {
    riscvRegDesc result   = RV_RD_NA;
    Uns32        instr    = info->instruction;
    Bool         implicit = False;

    switch(r) {
        case R_NA:
            break;
        case RS_X_11_7:
            result = RV_RD_X | U_11_7(instr);
            break;
        case RS_X_19_15:
            result = RV_RD_X | U_19_15(instr);
            break;
        case RS_X_24_20:
            result = RV_RD_X | U_24_20(instr);
            break;
        case RS_GP:
            result = RV_RD_X | RV_REG_X_GP;
            implicit = True;
            break;
        case RS_F_11_7:
            result = RV_RD_F | RV_RD_32 | U_11_7(instr);
            break;
        case RS_F_19_15:
            result = RV_RD_F | RV_RD_32 | U_19_15(instr);
            break;
        case RS_F_24_20:
            result = RV_RD_F | RV_RD_32 | U_24_20(instr);
            break;
        case RS_V_11_7:
            result = RV_RD_V | U_11_7(instr);
            break;
        case RS_V_24_20:
            result = RV_RD_V | U_24_20(instr);
            break;
        case RS_V_M_25:
            result = U_25(instr) ? 0 : (RV_RD_V|0);
            break;
        default:
            VMI_ABORT("unimplemented case"); // LCOV_EXCL_LINE
            break;
    }

    // fill register widths using width encoded in instruction
    if(result && !getRBits(result)) {
        result |= wX;
    }

    // validate X register width if required (floating-point registers require
    // dynamic width validation)
    if(isXReg(result) && (getRBits(result)>getXLenBits(riscv))) {
        info->arch &= ~getXLenArch(riscv);
    }

    // indicate this register is implicit if required
    if(implicit) {
        info->rImplicit = result;
    }

    return result;
}

//
// Return width specifier encoded in the instruction
//
static Uns32 getMemBits(andesInstrInfoP info, memBitsSpec memBits) {

    Uns32 result = 0;
    Uns32 instr  = info->instruction;

    switch(memBits) {
        case MBS_NA:
            break;
        case MBS_13_12:
            result = 8<<U_13_12(instr);
            break;
        case MBS_26_25:
            result = 8<<U_26_25(instr);
            break;
        case MBS_B:
            result = 8;
            break;
        case MBS_H:
            result = 16;
            break;
        case MBS_W:
            result = 32;
            break;
        case MBS_D:
            result = 64;
            break;
        default:
            VMI_ABORT("unimplemented case"); // LCOV_EXCL_LINE
            break;
    }

    return result;
}

//
// Get element bits encoded in instruction
//
static Uns32 getElemBits(andesInstrInfoP info, elemBitsSpec elemBits) {

    Uns32 result = 0;
    Uns32 instr  = info->instruction;

    switch(elemBits) {
        case EBS_NA:
            break;
        case EBS_21:
            result = U_21(instr)*8;
            break;
        default:
            VMI_ABORT("unimplemented case"); // LCOV_EXCL_LINE
            break;
    }

    return result;
}

//
// Return unsigned 32-bit extend specifier encoded in the instruction
//
static Bool getZE32(andesInstrInfoP info, ze32Spec ze32) {

    Bool  result = False;
    Uns32 instr  = info->instruction;

    switch(ze32) {
        case ZE32_NA:
            break;
        case ZE32_28:
            result = U_28(instr);
            break;
        default:
            VMI_ABORT("unimplemented case"); // LCOV_EXCL_LINE
            break;
    }

    return result;
}

//
// Return unsigned extend specifier encoded in the instruction
//
static Bool getUnsExt(andesInstrInfoP info, unsExtSpec unsExt) {

    Bool  result = False;
    Uns32 instr  = info->instruction;

    switch(unsExt) {
        case USX_NA:
            break;
        case USX_13:
            result = U_13(instr);
            break;
        case USX_14:
            result = U_14(instr);
            break;
        case USX_20:
            result = U_20(instr);
            break;
        default:
            VMI_ABORT("unimplemented case"); // LCOV_EXCL_LINE
            break;
    }

    return result;
}

//
// Interpret an instruction using the given attributes
//
static void interpretInstruction(
    riscvP          riscv,
    andesInstrInfoP info,
    opAttrsCP       attrs
) {
    // initialize implicit register
    info->rImplicit = 0;

    // fill fields from decoded instruction type
    info->type    = attrs->type;
    info->opcode  = attrs->opcode;
    info->format  = attrs->format;
    info->arch    = attrs->arch;
    info->cvtF32  = attrs->cvtF32;
    info->unsExtQ = attrs->unsExtQ;

    // get memory width encoded in instruction (prerequisite for getFWidth)
    info->memBits = getMemBits(info, attrs->memBits);

    // get element bits encoded in instruction
    info->elemBits = getElemBits(info, attrs->elemBits);

    // get register widths encoded in instruction
    riscvRegDesc wX = getXWidth(riscv, info, attrs->wX);

    // fill other fields from instruction
    info->ze32   = getZE32(info, attrs->ze32);
    info->unsExt = getUnsExt(info, attrs->unsExt);
    info->c1     = getConstant(riscv, info, attrs->cs1);
    info->c2     = getConstant(riscv, info, attrs->cs2);
    info->r[0]   = getRegister(riscv, info, attrs->r1, wX);
    info->r[1]   = getRegister(riscv, info, attrs->r2, wX);
    info->r[2]   = getRegister(riscv, info, attrs->r3, wX);
    info->r[3]   = getRegister(riscv, info, attrs->r4, wX);
    info->mask   = getRegister(riscv, info, attrs->mask, wX);
}

//
// Decode a 32-bit instruction at the given address
//
static void decode32(riscvP riscv, vmiosObjectP object, andesInstrInfoP info) {

    // decode the instruction using decode table
    andesIType32 type = getInstructionType32(riscv, object, info);

    // interpret instruction fields
    interpretInstruction(riscv, info, &attrsArray32[type]);
}

//
// Decode a 16-bit instruction at the given address
//
static void decode16(riscvP riscv, andesInstrInfoP info) {

    // decode the instruction using decode table
    andesIType16 type = getInstructionType16(riscv, info);

    // interpret instruction fields
    interpretInstruction(riscv, info, &attrsArray16[type]);
}

//
// Decode instruction at the given address
//
void andesDecode(
    riscvP          riscv,
    vmiosObjectP    object,
    riscvAddr       thisPC,
    andesInstrInfoP info
) {
    Uns64 instr = 0;

    info->type        = AN_IT_LAST;
    info->bytes       = vmicxtFetch((vmiProcessorP)riscv, thisPC, &instr);
    info->instruction = instr;
    info->thisPC      = thisPC;

    // decode based on instruction size
    if(info->bytes==4) {
        decode32(riscv, object, info);
    } else {
        decode16(riscv, info);
    }
}

