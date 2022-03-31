/*
 * Copyright (c) 2011-2014 Posedge Software Inc., www.posedgesoft.com
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
#include "m16cDecode.h"
#include "m16cInstructions.h"
#include "m16cStructure.h"
#include "m16cMorphEntries.h"




typedef struct addrModeLookupS {
    addrModeSpec    mode;
    addrModeSpec    mode_jump;
    Uns8            reg_B;
    Uns8            reg_W;
    Uns8            reg_A;
} addrModeLookup;

//
// Static array holding information about the address modes in the m16c.
//
static const addrModeLookup addr_mode_lookup[16] = {
//   Mode,        Mode (Jump)  size=B Reg,    size=W Reg,    size=A Reg
    {MODE_REG,    MODE_REG,    M16C_REG_R0L,  M16C_REG_R0,   M16C_REG_R2R0, },  // |0000|  // Register direct
    {MODE_REG,    MODE_REG,    M16C_REG_R0H,  M16C_REG_R1,   M16C_REG_R3R1, },  // |0001|
    {MODE_REG,    MODE_REG,    M16C_REG_R1L,  M16C_REG_R2,   M16C_REG_NONE, },  // |0010|
    {MODE_REG,    MODE_REG,    M16C_REG_R1H,  M16C_REG_R3,   M16C_REG_NONE, },  // |0011|
    {MODE_REG,    MODE_REG,    M16C_REG_A0,   M16C_REG_A0,   M16C_REG_A1A0, },  // |0100|
    {MODE_REG,    MODE_REG,    M16C_REG_A1,   M16C_REG_A1,   M16C_REG_NONE, },  // |0101|
    {MODE_REGO,   MODE_REGO,   M16C_REG_A0,   M16C_REG_A0,   M16C_REG_A0,   },  // |0110|  // Register indirect
    {MODE_REGO,   MODE_REGO,   M16C_REG_A1,   M16C_REG_A1,   M16C_REG_A1,   },  // |0111|
    {MODE_DSP8,   MODE_DSP8,   M16C_REG_A0,   M16C_REG_A0,   M16C_REG_A0,   },  // |1000|  // Register offset
    {MODE_DSP8,   MODE_DSP8,   M16C_REG_A1,   M16C_REG_A1,   M16C_REG_A1,   },  // |1001|
    {MODE_DSP8,   MODE_DSP8,   M16C_REG_SB,   M16C_REG_SB,   M16C_REG_SB,   },  // |1010|
    {MODE_DSP8,   MODE_DSP8,   M16C_REG_FB,   M16C_REG_FB,   M16C_REG_FB,   },  // |1011|
    {MODE_DSP16,  MODE_DSP20,  M16C_REG_A0,   M16C_REG_A0,   M16C_REG_A0,   },  // |1100|
    {MODE_DSP16,  MODE_DSP20,  M16C_REG_A1,   M16C_REG_A1,   M16C_REG_A1,   },  // |1101|
    {MODE_DSP16,  MODE_DSP16,  M16C_REG_SB,   M16C_REG_SB,   M16C_REG_SB,   },  // |1110|
    {MODE_ABS16,  MODE_ABS16,  M16C_REG_NONE, M16C_REG_NONE, M16C_REG_NONE, },  // |1111|  // Absolute
};

#define ADDR_MODE_LOOKUP(_MODE, _REG, _FIELD) \
     _MODE = attrs->morphtype == M16C_MT_JMPU ? addr_mode_lookup[_FIELD].mode_jump : addr_mode_lookup[_FIELD].mode; \
     _REG = (attrs->size == B ? addr_mode_lookup[_FIELD].reg_B : \
            (attrs->size == W ? addr_mode_lookup[_FIELD].reg_W : \
            attrs->size == BIT ? addr_mode_lookup[_FIELD].reg_W : \
            addr_mode_lookup[_FIELD].reg_A))






static const Int32 imm4_lookup[16] = {  // ADD_F2, ADD_F7, ADJNZ, CMP_F2, MOV_F2, SBJNZ
     0,      // |0000|
     1,      // |0001|
     2,      // |0010|
     3,      // |0011|
     4,      // |0100|
     5,      // |0101|
     6,      // |0110|
     7,      // |0111|
     -8,     // |1000|
     -7,     // |1001|
     -6,     // |1010|
     -5,     // |1011|
     -4,     // |1100|
     -3,     // |1101|
     -2,     // |1110|
     -1      // |1111|
};

static const Int32 imm4_2_lookup[16] = {   // ROT_F1, SHA_F1, SHA_F3, SHL_F1, SHL_F3
     1,      // |0000|
     2,      // |0001|
     3,      // |0010|
     4,      // |0011|
     5,      // |0100|
     6,      // |0101|
     7,      // |0110|
     8,      // |0111|
     -1,     // |1000|
     -2,     // |1001|
     -3,     // |1010|
     -4,     // |1011|
     -5,     // |1100|
     -6,     // |1101|
     -7,     // |1110|
     -8      // |1111|
};




//
// Define the location of a constant in an instruction
//
typedef enum constSpecE {
    CS_NA,          // instruction has no constant
    CONST_LABEL,
    OFFSET8,
    LABEL8,
    LABEL16,
    LABEL20,
    DSP8_1,
    CONST_P1,
    CONST_P2,
    CONST_N1,
    CONST_N2,
    CONST_COND8
} constSpec;



//
// Structure defining characteristics of each opcode type
//
typedef struct opAttrsS {
    const char   *opcode;           // opcode name
    Uns8          fmt;              // opcode fmt
    Uns8          dreg;             // Destination Registers ?
    Uns8          sreg;             // Source Registers ?
    constSpec     cons;             // constant
    addrModeSpec  src;              // constant
    addrModeSpec  dest;             // constant
    sizeSpec      size;             // constant
    condSpec      cond;             // condition
    dirSpec       dir;              // condition
    Uns8          bit;              // condition
    Uns32         dsp;              // condition
    Uns32         morphtype;
    Uns32         optype;
    vmiFlagsCP    flags;
} opAttrs;

typedef const struct opAttrsS *opAttrsCP;

//
// This macro adds a decode table entry for a specific instruction class
//
#define DECODE_ENTRY(_PRIORITY, _NAME, _FMT) \
    vmidNewEntryFmtBin(     \
        table,              \
        #_NAME,             \
        M16C_IT_##_NAME,    \
        _FMT,               \
        _PRIORITY           \
    )


static vmidDecodeTableP createDecodeTable8(void) {
    vmidDecodeTableP table = vmidNewDecodeTable(8, M16C_IT_LAST);

    // 8-bit opcodes
    DECODE_ENTRY(1, ADD_F3_R0H,     "|1000|0011|");  //  P.144 m16c   Form 3: Syntax:  ADD.B:S #IMM8, dest
    DECODE_ENTRY(1, ADD_F3_R0L,     "|1000|0100|");  //  P.144 m16c   Form 3: Syntax:  ADD.B:S #IMM8, dest
    DECODE_ENTRY(1, ADD_F3_SB,      "|1000|0101|");  //  P.144 m16c   Form 3: Syntax:  ADD.B:S #IMM8, dest
    DECODE_ENTRY(1, ADD_F3_FB,      "|1000|0110|");  //  P.144 m16c   Form 3: Syntax:  ADD.B:S #IMM8, dest
    DECODE_ENTRY(1, ADD_F3_ABS,     "|1000|0111|");  //  P.144 m16c   Form 3: Syntax:  ADD.B:S #IMM8, dest
    DECODE_ENTRY(1, ADD_F5_R0H_R0L, "|0010|0000|");  //  P.146 m16c   Form 5: Syntax:  ADD.B:S src, R0L/R0H
    DECODE_ENTRY(1, ADD_F5_SB_R0L,  "|0010|0001|");  //  P.146 m16c   Form 5: Syntax:  ADD.B:S src, R0L/R0H
    DECODE_ENTRY(1, ADD_F5_FB_R0L,  "|0010|0010|");  //  P.146 m16c   Form 5: Syntax:  ADD.B:S src, R0L/R0H
    DECODE_ENTRY(1, ADD_F5_ABS_R0L, "|0010|0011|");  //  P.146 m16c   Form 5: Syntax:  ADD.B:S src, R0L/R0H
    DECODE_ENTRY(1, ADD_F5_R0L_R0H, "|0010|0100|");  //  P.146 m16c   Form 5: Syntax:  ADD.B:S src, R0L/R0H
    DECODE_ENTRY(1, ADD_F5_SB_R0H,  "|0010|0101|");  //  P.146 m16c   Form 5: Syntax:  ADD.B:S src, R0L/R0H
    DECODE_ENTRY(1, ADD_F5_FB_R0H,  "|0010|0110|");  //  P.146 m16c   Form 5: Syntax:  ADD.B:S src, R0L/R0H
    DECODE_ENTRY(1, ADD_F5_ABS_R0H, "|0010|0111|");  //  P.146 m16c   Form 5: Syntax:  ADD.B:S src, R0L/R0H
    DECODE_ENTRY(1, AND_F2_R0H,     "|1001|0011|");  //  P.149 m16c   Form 2: Syntax:  AND.B:S #IMM8, dest
    DECODE_ENTRY(1, AND_F2_R0L,     "|1001|0100|");  //  P.149 m16c   Form 2: Syntax:  AND.B:S #IMM8, dest
    DECODE_ENTRY(1, AND_F2_SB,      "|1001|0101|");  //  P.149 m16c   Form 2: Syntax:  AND.B:S #IMM8, dest
    DECODE_ENTRY(1, AND_F2_FB,      "|1001|0110|");  //  P.149 m16c   Form 2: Syntax:  AND.B:S #IMM8, dest
    DECODE_ENTRY(1, AND_F2_ABS,     "|1001|0111|");  //  P.149 m16c   Form 2: Syntax:  AND.B:S #IMM8, dest
    DECODE_ENTRY(1, AND_F4_R0H_R0L, "|0001|0000|");  //  P.151 m16c   Form 4: Syntax:  AND.B:S src, R0L/R0H
    DECODE_ENTRY(1, AND_F4_SB_R0L,  "|0001|0001|");  //  P.151 m16c   Form 4: Syntax:  AND.B:S src, R0L/R0H
    DECODE_ENTRY(1, AND_F4_FB_R0L,  "|0001|0010|");  //  P.151 m16c   Form 4: Syntax:  AND.B:S src, R0L/R0H
    DECODE_ENTRY(1, AND_F4_ABS_R0L, "|0001|0011|");  //  P.151 m16c   Form 4: Syntax:  AND.B:S src, R0L/R0H
    DECODE_ENTRY(1, AND_F4_R0L_R0H, "|0001|0100|");  //  P.151 m16c   Form 4: Syntax:  AND.B:S src, R0L/R0H
    DECODE_ENTRY(1, AND_F4_SB_R0H,  "|0001|0101|");  //  P.151 m16c   Form 4: Syntax:  AND.B:S src, R0L/R0H
    DECODE_ENTRY(1, AND_F4_FB_R0H,  "|0001|0110|");  //  P.151 m16c   Form 4: Syntax:  AND.B:S src, R0L/R0H
    DECODE_ENTRY(1, AND_F4_ABS_R0H, "|0001|0111|");  //  P.151 m16c   Form 4: Syntax:  AND.B:S src, R0L/R0H
    DECODE_ENTRY(1, BCLR_F2_0,      "|0100|0000|");  //  P.153 m16c   Form 2: Syntax:  BCLR:S bit, base:11[SB]
    DECODE_ENTRY(1, BCLR_F2_1,      "|0100|0001|");  //  P.153 m16c   Form 2: Syntax:  BCLR:S bit, base:11[SB]
    DECODE_ENTRY(1, BCLR_F2_2,      "|0100|0010|");  //  P.153 m16c   Form 2: Syntax:  BCLR:S bit, base:11[SB]
    DECODE_ENTRY(1, BCLR_F2_3,      "|0100|0011|");  //  P.153 m16c   Form 2: Syntax:  BCLR:S bit, base:11[SB]
    DECODE_ENTRY(1, BCLR_F2_4,      "|0100|0100|");  //  P.153 m16c   Form 2: Syntax:  BCLR:S bit, base:11[SB]
    DECODE_ENTRY(1, BCLR_F2_5,      "|0100|0101|");  //  P.153 m16c   Form 2: Syntax:  BCLR:S bit, base:11[SB]
    DECODE_ENTRY(1, BCLR_F2_6,      "|0100|0110|");  //  P.153 m16c   Form 2: Syntax:  BCLR:S bit, base:11[SB]
    DECODE_ENTRY(1, BCLR_F2_7,      "|0100|0111|");  //  P.153 m16c   Form 2: Syntax:  BCLR:S bit, base:11[SB]
    DECODE_ENTRY(1, BNOT_F2_0,      "|0101|0000|");  //  P.157 m16c   Form 2: Syntax:  BNOT:S bit, base:11[SB]
    DECODE_ENTRY(1, BNOT_F2_1,      "|0101|0001|");  //  P.157 m16c   Form 2: Syntax:  BNOT:S bit, base:11[SB]
    DECODE_ENTRY(1, BNOT_F2_2,      "|0101|0010|");  //  P.157 m16c   Form 2: Syntax:  BNOT:S bit, base:11[SB]
    DECODE_ENTRY(1, BNOT_F2_3,      "|0101|0011|");  //  P.157 m16c   Form 2: Syntax:  BNOT:S bit, base:11[SB]
    DECODE_ENTRY(1, BNOT_F2_4,      "|0101|0100|");  //  P.157 m16c   Form 2: Syntax:  BNOT:S bit, base:11[SB]
    DECODE_ENTRY(1, BNOT_F2_5,      "|0101|0101|");  //  P.157 m16c   Form 2: Syntax:  BNOT:S bit, base:11[SB]
    DECODE_ENTRY(1, BNOT_F2_6,      "|0101|0110|");  //  P.157 m16c   Form 2: Syntax:  BNOT:S bit, base:11[SB]
    DECODE_ENTRY(1, BNOT_F2_7,      "|0101|0111|");  //  P.157 m16c   Form 2: Syntax:  BNOT:S bit, base:11[SB]
    DECODE_ENTRY(1, BRK_F1,         "|0000|0000|");  //  P.159 m16c   Form 1: Syntax:  BRK
    DECODE_ENTRY(1, BSET_F2_0,      "|0100|1000|");  //  P.160 m16c   Form 2: Syntax:  BSET:S bit, base:11[SB]
    DECODE_ENTRY(1, BSET_F2_1,      "|0100|1001|");  //  P.160 m16c   Form 2: Syntax:  BSET:S bit, base:11[SB]
    DECODE_ENTRY(1, BSET_F2_2,      "|0100|1010|");  //  P.160 m16c   Form 2: Syntax:  BSET:S bit, base:11[SB]
    DECODE_ENTRY(1, BSET_F2_3,      "|0100|1011|");  //  P.160 m16c   Form 2: Syntax:  BSET:S bit, base:11[SB]
    DECODE_ENTRY(1, BSET_F2_4,      "|0100|1100|");  //  P.160 m16c   Form 2: Syntax:  BSET:S bit, base:11[SB]
    DECODE_ENTRY(1, BSET_F2_5,      "|0100|1101|");  //  P.160 m16c   Form 2: Syntax:  BSET:S bit, base:11[SB]
    DECODE_ENTRY(1, BSET_F2_6,      "|0100|1110|");  //  P.160 m16c   Form 2: Syntax:  BSET:S bit, base:11[SB]
    DECODE_ENTRY(1, BSET_F2_7,      "|0100|1111|");  //  P.160 m16c   Form 2: Syntax:  BSET:S bit, base:11[SB]
    DECODE_ENTRY(1, BTST_F2_0,      "|0101|1000|");  //  P.161 m16c   Form 2: Syntax:  BTST:S bit, base:11[SB]
    DECODE_ENTRY(1, BTST_F2_1,      "|0101|1001|");  //  P.161 m16c   Form 2: Syntax:  BTST:S bit, base:11[SB]
    DECODE_ENTRY(1, BTST_F2_2,      "|0101|1010|");  //  P.161 m16c   Form 2: Syntax:  BTST:S bit, base:11[SB]
    DECODE_ENTRY(1, BTST_F2_3,      "|0101|1011|");  //  P.161 m16c   Form 2: Syntax:  BTST:S bit, base:11[SB]
    DECODE_ENTRY(1, BTST_F2_4,      "|0101|1100|");  //  P.161 m16c   Form 2: Syntax:  BTST:S bit, base:11[SB]
    DECODE_ENTRY(1, BTST_F2_5,      "|0101|1101|");  //  P.161 m16c   Form 2: Syntax:  BTST:S bit, base:11[SB]
    DECODE_ENTRY(1, BTST_F2_6,      "|0101|1110|");  //  P.161 m16c   Form 2: Syntax:  BTST:S bit, base:11[SB]
    DECODE_ENTRY(1, BTST_F2_7,      "|0101|1111|");  //  P.161 m16c   Form 2: Syntax:  BTST:S bit, base:11[SB]
    DECODE_ENTRY(1, CMP_F3_R0H,     "|1110|0011|");  //  P.165 m16c   Form 3: Syntax:  CMP.B:S #IMM8, dest
    DECODE_ENTRY(1, CMP_F3_R0L,     "|1110|0100|");  //  P.165 m16c   Form 3: Syntax:  CMP.B:S #IMM8, dest
    DECODE_ENTRY(1, CMP_F3_SB,      "|1110|0101|");  //  P.165 m16c   Form 3: Syntax:  CMP.B:S #IMM8, dest
    DECODE_ENTRY(1, CMP_F3_FB,      "|1110|0110|");  //  P.165 m16c   Form 3: Syntax:  CMP.B:S #IMM8, dest
    DECODE_ENTRY(1, CMP_F3_ABS,     "|1110|0111|");  //  P.165 m16c   Form 3: Syntax:  CMP.B:S #IMM8, dest
    DECODE_ENTRY(1, CMP_F5_R0H_R0L, "|0011|1000|");  //  P.167 m16c   Form 5: Syntax:  CMP.B:S src, R0L/R0H
    DECODE_ENTRY(1, CMP_F5_SB_R0L,  "|0011|1001|");  //  P.167 m16c   Form 5: Syntax:  CMP.B:S src, R0L/R0H
    DECODE_ENTRY(1, CMP_F5_FB_R0L,  "|0011|1010|");  //  P.167 m16c   Form 5: Syntax:  CMP.B:S src, R0L/R0H
    DECODE_ENTRY(1, CMP_F5_ABS_R0L, "|0011|1011|");  //  P.167 m16c   Form 5: Syntax:  CMP.B:S src, R0L/R0H
    DECODE_ENTRY(1, CMP_F5_R0L_R0H, "|0011|1100|");  //  P.167 m16c   Form 5: Syntax:  CMP.B:S src, R0L/R0H
    DECODE_ENTRY(1, CMP_F5_SB_R0H,  "|0011|1101|");  //  P.167 m16c   Form 5: Syntax:  CMP.B:S src, R0L/R0H
    DECODE_ENTRY(1, CMP_F5_FB_R0H,  "|0011|1110|");  //  P.167 m16c   Form 5: Syntax:  CMP.B:S src, R0L/R0H
    DECODE_ENTRY(1, CMP_F5_ABS_R0H, "|0011|1111|");  //  P.167 m16c   Form 5: Syntax:  CMP.B:S src, R0L/R0H
    DECODE_ENTRY(1, DEC_F1_R0H,     "|1010|1011|");  //  P.171 m16c   Form 1: Syntax:  DEC.B dest
    DECODE_ENTRY(1, DEC_F1_R0L,     "|1010|1100|");  //  P.171 m16c   Form 1: Syntax:  DEC.B dest
    DECODE_ENTRY(1, DEC_F1_SB,      "|1010|1101|");  //  P.171 m16c   Form 1: Syntax:  DEC.B dest
    DECODE_ENTRY(1, DEC_F1_FB,      "|1010|1110|");  //  P.171 m16c   Form 1: Syntax:  DEC.B dest
    DECODE_ENTRY(1, DEC_F1_ABS,     "|1010|1111|");  //  P.171 m16c   Form 1: Syntax:  DEC.B dest
    DECODE_ENTRY(1, DEC_F2_A0,      "|1111|0010|");  //  P.172 m16c   Form 2: Syntax:  DEC.W dest
    DECODE_ENTRY(1, DEC_F2_A1,      "|1111|1010|");  //  P.172 m16c   Form 2: Syntax:  DEC.W dest
    DECODE_ENTRY(1, INC_F1_R0H,     "|1010|0011|");  //  P.182 m16c   Form 1: Syntax:  INC.B dest
    DECODE_ENTRY(1, INC_F1_R0L,     "|1010|0100|");  //  P.182 m16c   Form 1: Syntax:  INC.B dest
    DECODE_ENTRY(1, INC_F1_SB,      "|1010|0101|");  //  P.182 m16c   Form 1: Syntax:  INC.B dest
    DECODE_ENTRY(1, INC_F1_FB,      "|1010|0110|");  //  P.182 m16c   Form 1: Syntax:  INC.B dest
    DECODE_ENTRY(1, INC_F1_ABS,     "|1010|0111|");  //  P.182 m16c   Form 1: Syntax:  INC.B dest
    DECODE_ENTRY(2, INC_F2_A0,      "|1011|0010|");  //  P.183 m16c   Form 2: Syntax:  INC.W dest
    DECODE_ENTRY(2, INC_F2_A1,      "|1011|1010|");  //  P.183 m16c   Form 2: Syntax:  INC.W dest
    DECODE_ENTRY(1, INTO_F1,        "|1111|0110|");  //  P.184 m16c   Form 1: Syntax:  INTO
    DECODE_ENTRY(1, JCND_F1_GEU,    "|0110|1000|");  //  P.184 m16c   Form 1: Syntax:  JCnd label
    DECODE_ENTRY(1, JCND_F1_GTU,    "|0110|1001|");  //  P.184 m16c   Form 1: Syntax:  JCnd label
    DECODE_ENTRY(1, JCND_F1_EQ,     "|0110|1010|");  //  P.184 m16c   Form 1: Syntax:  JCnd label
    DECODE_ENTRY(1, JCND_F1_N,      "|0110|1011|");  //  P.184 m16c   Form 1: Syntax:  JCnd label
    DECODE_ENTRY(1, JCND_F1_LTU,    "|0110|1100|");  //  P.184 m16c   Form 1: Syntax:  JCnd label
    DECODE_ENTRY(1, JCND_F1_LEU,    "|0110|1101|");  //  P.184 m16c   Form 1: Syntax:  JCnd label
    DECODE_ENTRY(1, JCND_F1_NE,     "|0110|1110|");  //  P.184 m16c   Form 1: Syntax:  JCnd label
    DECODE_ENTRY(1, JCND_F1_PZ,     "|0110|1111|");  //  P.184 m16c   Form 1: Syntax:  JCnd label
    DECODE_ENTRY(1, JMP_F1_0,       "|0110|0000|");  //  P.185 m16c   Form 1: Syntax:  JMP.S label
    DECODE_ENTRY(1, JMP_F1_1,       "|0110|0001|");  //  P.185 m16c   Form 1: Syntax:  JMP.S label
    DECODE_ENTRY(1, JMP_F1_2,       "|0110|0010|");  //  P.185 m16c   Form 1: Syntax:  JMP.S label
    DECODE_ENTRY(1, JMP_F1_3,       "|0110|0011|");  //  P.185 m16c   Form 1: Syntax:  JMP.S label
    DECODE_ENTRY(1, JMP_F1_4,       "|0110|0100|");  //  P.185 m16c   Form 1: Syntax:  JMP.S label
    DECODE_ENTRY(1, JMP_F1_5,       "|0110|0101|");  //  P.185 m16c   Form 1: Syntax:  JMP.S label
    DECODE_ENTRY(1, JMP_F1_6,       "|0110|0110|");  //  P.185 m16c   Form 1: Syntax:  JMP.S label
    DECODE_ENTRY(1, JMP_F1_7,       "|0110|0111|");  //  P.185 m16c   Form 1: Syntax:  JMP.S label
    DECODE_ENTRY(1, JMP_F2,         "|1111|1110|");  //  P.186 m16c   Form 2: Syntax:  JMP.B label
    DECODE_ENTRY(1, JMP_F3,         "|1111|0100|");  //  P.186 m16c   Form 3: Syntax:  JMP.W label
    DECODE_ENTRY(1, JMP_F4,         "|1111|1100|");  //  P.187 m16c   Form 4: Syntax:  JMP.A label
    DECODE_ENTRY(1, JMPS_F1,        "|1110|1110|");  //  P.188 m16c   Form 1: Syntax:  JMPS #IMM8
    DECODE_ENTRY(1, JSR_F1,         "|1111|0101|");  //  P.189 m16c   Form 1: Syntax:  JSR.W label
    DECODE_ENTRY(1, JSR_F2,         "|1111|1101|");  //  P.189 m16c   Form 2: Syntax:  JSR.A label
    DECODE_ENTRY(1, JSRS_F1,        "|1110|1111|");  //  P.191 m16c   Form 1: Syntax:  JSRS #IMM8
    DECODE_ENTRY(1, MOV_F3_R0H,     "|1100|0011|");  //  P.197 m16c   Form 3: Syntax:  MOV.B:S #IMM8, dest
    DECODE_ENTRY(1, MOV_F3_R0L,     "|1100|0100|");  //  P.197 m16c   Form 3: Syntax:  MOV.B:S #IMM8, dest
    DECODE_ENTRY(1, MOV_F3_SB,      "|1100|0101|");  //  P.197 m16c   Form 3: Syntax:  MOV.B:S #IMM8, dest
    DECODE_ENTRY(1, MOV_F3_FB,      "|1100|0110|");  //  P.197 m16c   Form 3: Syntax:  MOV.B:S #IMM8, dest
    DECODE_ENTRY(1, MOV_F3_ABS,     "|1100|0111|");  //  P.197 m16c   Form 3: Syntax:  MOV.B:S #IMM8, dest
    DECODE_ENTRY(2, MOV_F4_B_A0,    "|1010|0010|");  //  P.198 m16c   Form 4: Syntax:  MOV.size:S #IMM, dest
    DECODE_ENTRY(2, MOV_F4_B_A1,    "|1010|1010|");  //  P.198 m16c   Form 4: Syntax:  MOV.size:S #IMM, dest
    DECODE_ENTRY(2, MOV_F4_W_A0,    "|1110|0010|");  //  P.198 m16c   Form 4: Syntax:  MOV.size:S #IMM, dest
    DECODE_ENTRY(2, MOV_F4_W_A1,    "|1110|1010|");  //  P.198 m16c   Form 4: Syntax:  MOV.size:S #IMM, dest
    DECODE_ENTRY(1, MOV_F5_R0H,     "|1011|0011|");  //  P.198 m16c   Form 5: Syntax:  MOV.B:Z #0, dest
    DECODE_ENTRY(1, MOV_F5_R0L,     "|1011|0100|");  //  P.198 m16c   Form 5: Syntax:  MOV.B:Z #0, dest
    DECODE_ENTRY(1, MOV_F5_SB,      "|1011|0101|");  //  P.198 m16c   Form 5: Syntax:  MOV.B:Z #0, dest
    DECODE_ENTRY(1, MOV_F5_FB,      "|1011|0110|");  //  P.198 m16c   Form 5: Syntax:  MOV.B:Z #0, dest
    DECODE_ENTRY(1, MOV_F5_ABS,     "|1011|0111|");  //  P.198 m16c   Form 5: Syntax:  MOV.B:Z #0, dest
    DECODE_ENTRY(1, MOV_F7_R0H_A0,  "|0011|0000|");  //  P.200 m16c   Form 7: Syntax:  MOV.B:S src, dest
    DECODE_ENTRY(1, MOV_F7_SB_A0,   "|0011|0001|");  //  P.200 m16c   Form 7: Syntax:  MOV.B:S src, dest
    DECODE_ENTRY(1, MOV_F7_FB_A0,   "|0011|0010|");  //  P.200 m16c   Form 7: Syntax:  MOV.B:S src, dest
    DECODE_ENTRY(1, MOV_F7_ABS_A0,  "|0011|0011|");  //  P.200 m16c   Form 7: Syntax:  MOV.B:S src, dest
    DECODE_ENTRY(1, MOV_F7_R0L_A1,  "|0011|0100|");  //  P.200 m16c   Form 7: Syntax:  MOV.B:S src, dest
    DECODE_ENTRY(1, MOV_F7_SB_A1,   "|0011|0101|");  //  P.200 m16c   Form 7: Syntax:  MOV.B:S src, dest
    DECODE_ENTRY(1, MOV_F7_FB_A1,   "|0011|0110|");  //  P.200 m16c   Form 7: Syntax:  MOV.B:S src, dest
    DECODE_ENTRY(1, MOV_F7_ABS_A1,  "|0011|0111|");  //  P.200 m16c   Form 7: Syntax:  MOV.B:S src, dest
    DECODE_ENTRY(2, MOV_F8_R0L_SB,  "|0000|0001|");  //  P.200 m16c   Form 8: Syntax:  MOV.B:S R0L/R0H, dest
    DECODE_ENTRY(2, MOV_F8_R0L_FB,  "|0000|0010|");  //  P.200 m16c   Form 8: Syntax:  MOV.B:S R0L/R0H, dest
    DECODE_ENTRY(2, MOV_F8_R0L_ABS, "|0000|0011|");  //  P.200 m16c   Form 8: Syntax:  MOV.B:S R0L/R0H, dest
    DECODE_ENTRY(2, MOV_F8_R0H_SB,  "|0000|0101|");  //  P.200 m16c   Form 8: Syntax:  MOV.B:S R0L/R0H, dest
    DECODE_ENTRY(2, MOV_F8_R0H_FB,  "|0000|0110|");  //  P.200 m16c   Form 8: Syntax:  MOV.B:S R0L/R0H, dest
    DECODE_ENTRY(2, MOV_F8_R0H_ABS, "|0000|0111|");  //  P.200 m16c   Form 8: Syntax:  MOV.B:S R0L/R0H, dest
    DECODE_ENTRY(1, MOV_F9_R0H_R0L, "|0000|1000|");  //  P.201 m16c   Form 9: Syntax:  MOV.B:S src, R0L/R0H
    DECODE_ENTRY(1, MOV_F9_SB_R0L,  "|0000|1001|");  //  P.201 m16c   Form 9: Syntax:  MOV.B:S src, R0L/R0H
    DECODE_ENTRY(1, MOV_F9_FB_R0L,  "|0000|1010|");  //  P.201 m16c   Form 9: Syntax:  MOV.B:S src, R0L/R0H
    DECODE_ENTRY(1, MOV_F9_ABS_R0L, "|0000|1011|");  //  P.201 m16c   Form 9: Syntax:  MOV.B:S src, R0L/R0H
    DECODE_ENTRY(1, MOV_F9_R0L_R0H, "|0000|1100|");  //  P.201 m16c   Form 9: Syntax:  MOV.B:S src, R0L/R0H
    DECODE_ENTRY(1, MOV_F9_SB_R0H,  "|0000|1101|");  //  P.201 m16c   Form 9: Syntax:  MOV.B:S src, R0L/R0H
    DECODE_ENTRY(1, MOV_F9_FB_R0H,  "|0000|1110|");  //  P.201 m16c   Form 9: Syntax:  MOV.B:S src, R0L/R0H
    DECODE_ENTRY(1, MOV_F9_ABS_R0H, "|0000|1111|");  //  P.201 m16c   Form 9: Syntax:  MOV.B:S src, R0L/R0H
    DECODE_ENTRY(1, NOP_F1,         "|0000|0100|");  //  P.209 m16c   Form 1: Syntax:  NOP
    DECODE_ENTRY(1, NOT_F2_R0H,     "|1011|1011|");  //  P.210 m16c   Form 2: Syntax:  NOT.B:S dest
    DECODE_ENTRY(1, NOT_F2_R0L,     "|1011|1100|");  //  P.210 m16c   Form 2: Syntax:  NOT.B:S dest
    DECODE_ENTRY(1, NOT_F2_SB,      "|1011|1101|");  //  P.210 m16c   Form 2: Syntax:  NOT.B:S dest
    DECODE_ENTRY(1, NOT_F2_FB,      "|1011|1110|");  //  P.210 m16c   Form 2: Syntax:  NOT.B:S dest
    DECODE_ENTRY(1, NOT_F2_ABS,     "|1011|1111|");  //  P.210 m16c   Form 2: Syntax:  NOT.B:S dest
    DECODE_ENTRY(1, OR_F2_R0H,      "|1001|1011|");  //  P.211 m16c   Form 2: Syntax:  OR.B:S #IMM8, dest
    DECODE_ENTRY(1, OR_F2_R0L,      "|1001|1100|");  //  P.211 m16c   Form 2: Syntax:  OR.B:S #IMM8, dest
    DECODE_ENTRY(1, OR_F2_SB,       "|1001|1101|");  //  P.211 m16c   Form 2: Syntax:  OR.B:S #IMM8, dest
    DECODE_ENTRY(1, OR_F2_FB,       "|1001|1110|");  //  P.211 m16c   Form 2: Syntax:  OR.B:S #IMM8, dest
    DECODE_ENTRY(1, OR_F2_ABS,      "|1001|1111|");  //  P.211 m16c   Form 2: Syntax:  OR.B:S #IMM8, dest
    DECODE_ENTRY(1, OR_F4_R0H_R0L,  "|0001|1000|");  //  P.213 m16c   Form 4: Syntax:  OR.B:S src, R0L/R0H
    DECODE_ENTRY(1, OR_F4_SB_R0L,   "|0001|1001|");  //  P.213 m16c   Form 4: Syntax:  OR.B:S src, R0L/R0H
    DECODE_ENTRY(1, OR_F4_FB_R0L,   "|0001|1010|");  //  P.213 m16c   Form 4: Syntax:  OR.B:S src, R0L/R0H
    DECODE_ENTRY(1, OR_F4_ABS_R0L,  "|0001|1011|");  //  P.213 m16c   Form 4: Syntax:  OR.B:S src, R0L/R0H
    DECODE_ENTRY(1, OR_F4_R0L_R0H,  "|0001|1100|");  //  P.213 m16c   Form 4: Syntax:  OR.B:S src, R0L/R0H
    DECODE_ENTRY(1, OR_F4_SB_R0H,   "|0001|1101|");  //  P.213 m16c   Form 4: Syntax:  OR.B:S src, R0L/R0H
    DECODE_ENTRY(1, OR_F4_FB_R0H,   "|0001|1110|");  //  P.213 m16c   Form 4: Syntax:  OR.B:S src, R0L/R0H
    DECODE_ENTRY(1, OR_F4_ABS_R0H,  "|0001|1111|");  //  P.213 m16c   Form 4: Syntax:  OR.B:S src, R0L/R0H
    DECODE_ENTRY(2, POP_F2_R0L,     "|1001|0010|");  //  P.214 m16c   Form 2: Syntax:  POP.B:S dest
    DECODE_ENTRY(2, POP_F2_R0H,     "|1001|1010|");  //  P.214 m16c   Form 2: Syntax:  POP.B:S dest
    DECODE_ENTRY(1, POP_F3_A0,      "|1101|0010|");  //  P.214 m16c   Form 3: Syntax:  POP.W:S dest
    DECODE_ENTRY(1, POP_F3_A1,      "|1101|1010|");  //  P.214 m16c   Form 3: Syntax:  POP.W:S dest
    DECODE_ENTRY(1, POPM_F1,        "|1110|1101|");  //  P.215 m16c   Form 1: Syntax:  POPM dest
    DECODE_ENTRY(2, PUSH_F3_R0L,    "|1000|0010|");  //  P.217 m16c   Form 3: Syntax:  PUSH.B:S src
    DECODE_ENTRY(2, PUSH_F3_R0H,    "|1000|1010|");  //  P.217 m16c   Form 3: Syntax:  PUSH.B:S src
    DECODE_ENTRY(1, PUSH_F4_A0,     "|1100|0010|");  //  P.217 m16c   Form 4: Syntax:  PUSH.W:S src
    DECODE_ENTRY(1, PUSH_F4_A1,     "|1100|1010|");  //  P.217 m16c   Form 4: Syntax:  PUSH.W:S src
    DECODE_ENTRY(1, PUSHM_F1,       "|1110|1100|");  //  P.219 m16c   Form 1: Syntax:  PUSHM src
    DECODE_ENTRY(1, REIT_F1,        "|1111|1011|");  //  P.219 m16c   Form 1: Syntax:  REIT
    DECODE_ENTRY(1, RTS_F1,         "|1111|0011|");  //  P.223 m16c   Form 1: Syntax:  RTS
    DECODE_ENTRY(1, STNZ_F1_R0H,    "|1101|0011|");  //  P.237 m16c   Form 1: Syntax:  STNZ #IMM8, dest
    DECODE_ENTRY(1, STNZ_F1_R0L,    "|1101|0100|");  //  P.237 m16c   Form 1: Syntax:  STNZ #IMM8, dest
    DECODE_ENTRY(1, STNZ_F1_SB,     "|1101|0101|");  //  P.237 m16c   Form 1: Syntax:  STNZ #IMM8, dest
    DECODE_ENTRY(1, STNZ_F1_FB,     "|1101|0110|");  //  P.237 m16c   Form 1: Syntax:  STNZ #IMM8, dest
    DECODE_ENTRY(1, STNZ_F1_ABS,    "|1101|0111|");  //  P.237 m16c   Form 1: Syntax:  STNZ #IMM8, dest
    DECODE_ENTRY(1, STZ_F1_R0H,     "|1100|1011|");  //  P.237 m16c   Form 1: Syntax:  STZ #IMM8, dest
    DECODE_ENTRY(1, STZ_F1_R0L,     "|1100|1100|");  //  P.237 m16c   Form 1: Syntax:  STZ #IMM8, dest
    DECODE_ENTRY(1, STZ_F1_SB,      "|1100|1101|");  //  P.237 m16c   Form 1: Syntax:  STZ #IMM8, dest
    DECODE_ENTRY(1, STZ_F1_FB,      "|1100|1110|");  //  P.237 m16c   Form 1: Syntax:  STZ #IMM8, dest
    DECODE_ENTRY(1, STZ_F1_ABS,     "|1100|1111|");  //  P.237 m16c   Form 1: Syntax:  STZ #IMM8, dest
    DECODE_ENTRY(1, STZX_F1_R0H,    "|1101|1011|");  //  P.238 m16c   Form 1: Syntax:  STZX #IMM81, #IMM82, dest
    DECODE_ENTRY(1, STZX_F1_R0L,    "|1101|1100|");  //  P.238 m16c   Form 1: Syntax:  STZX #IMM81, #IMM82, dest
    DECODE_ENTRY(1, STZX_F1_SB,     "|1101|1101|");  //  P.238 m16c   Form 1: Syntax:  STZX #IMM81, #IMM82, dest
    DECODE_ENTRY(1, STZX_F1_FB,     "|1101|1110|");  //  P.238 m16c   Form 1: Syntax:  STZX #IMM81, #IMM82, dest
    DECODE_ENTRY(1, STZX_F1_ABS,    "|1101|1111|");  //  P.238 m16c   Form 1: Syntax:  STZX #IMM81, #IMM82, dest
    DECODE_ENTRY(1, SUB_F2_R0H,     "|1000|1011|");  //  P.239 m16c   Form 2: Syntax:  SUB.B:S #IMM8, dest
    DECODE_ENTRY(1, SUB_F2_R0L,     "|1000|1100|");  //  P.239 m16c   Form 2: Syntax:  SUB.B:S #IMM8, dest
    DECODE_ENTRY(1, SUB_F2_SB,      "|1000|1101|");  //  P.239 m16c   Form 2: Syntax:  SUB.B:S #IMM8, dest
    DECODE_ENTRY(1, SUB_F2_FB,      "|1000|1110|");  //  P.239 m16c   Form 2: Syntax:  SUB.B:S #IMM8, dest
    DECODE_ENTRY(1, SUB_F2_ABS,     "|1000|1111|");  //  P.239 m16c   Form 2: Syntax:  SUB.B:S #IMM8, dest
    DECODE_ENTRY(1, SUB_F4_R0H_R0L, "|0010|1000|");  //  P.241 m16c   Form 4: Syntax:  SUB.B:S src, R0L/R0H
    DECODE_ENTRY(1, SUB_F4_SB_R0L,  "|0010|1001|");  //  P.241 m16c   Form 4: Syntax:  SUB.B:S src, R0L/R0H
    DECODE_ENTRY(1, SUB_F4_FB_R0L,  "|0010|1010|");  //  P.241 m16c   Form 4: Syntax:  SUB.B:S src, R0L/R0H
    DECODE_ENTRY(1, SUB_F4_ABS_R0L, "|0010|1011|");  //  P.241 m16c   Form 4: Syntax:  SUB.B:S src, R0L/R0H
    DECODE_ENTRY(1, SUB_F4_R0L_R0H, "|0010|1100|");  //  P.241 m16c   Form 4: Syntax:  SUB.B:S src, R0L/R0H
    DECODE_ENTRY(1, SUB_F4_SB_R0H,  "|0010|1101|");  //  P.241 m16c   Form 4: Syntax:  SUB.B:S src, R0L/R0H
    DECODE_ENTRY(1, SUB_F4_FB_R0H,  "|0010|1110|");  //  P.241 m16c   Form 4: Syntax:  SUB.B:S src, R0L/R0H
    DECODE_ENTRY(1, SUB_F4_ABS_R0H, "|0010|1111|");  //  P.241 m16c   Form 4: Syntax:  SUB.B:S src, R0L/R0H
    DECODE_ENTRY(1, UND_F1,         "|1111|1111|");  //  P.243 m16c   Form 1: Syntax:  UND


    return table;
}


static vmidDecodeTableP createDecodeTable16(void) {
    vmidDecodeTableP table = vmidNewDecodeTable(16, M16C_IT_LAST);

    // 16-bit opcodes
    DECODE_ENTRY(1, ABS_F1_B,       "|0111|0110|1111|....|");  //  P.140 m16c   Form 1: Syntax:  ABS.size dest
    DECODE_ENTRY(1, ABS_F1_W,       "|0111|0111|1111|....|");  //  P.140 m16c   Form 1: Syntax:  ABS.size dest
    DECODE_ENTRY(1, ADC_F1_B,       "|0111|0110|0110|....|");  //  P.140 m16c   Form 1: Syntax:  ADC.size #IMM, dest
    DECODE_ENTRY(1, ADC_F1_W,       "|0111|0111|0110|....|");  //  P.140 m16c   Form 1: Syntax:  ADC.size #IMM, dest
    DECODE_ENTRY(1, ADC_F2_B,       "|1011|0000|....|....|");  //  P.141 m16c   Form 2: Syntax:  ADC.size src, dest
    DECODE_ENTRY(1, ADC_F2_W,       "|1011|0001|....|....|");  //  P.141 m16c   Form 2: Syntax:  ADC.size src, dest
    DECODE_ENTRY(1, ADCF_F1_B,      "|0111|0110|1110|....|");  //  P.142 m16c   Form 1: Syntax:  ADCF.size dest
    DECODE_ENTRY(1, ADCF_F1_W,      "|0111|0111|1110|....|");  //  P.142 m16c   Form 1: Syntax:  ADCF.size dest
    DECODE_ENTRY(1, ADD_F1_B,       "|0111|0110|0100|....|");  //  P.142 m16c   Form 1: Syntax:  ADD.size:G #IMM, dest
    DECODE_ENTRY(1, ADD_F1_W,       "|0111|0111|0100|....|");  //  P.142 m16c   Form 1: Syntax:  ADD.size:G #IMM, dest
    DECODE_ENTRY(2, ADD_F2_B,       "|1100|1000|....|....|");  //  P.143 m16c   Form 2: Syntax:  ADD.size:Q #IMM, dest
    DECODE_ENTRY(2, ADD_F2_W,       "|1100|1001|....|....|");  //  P.143 m16c   Form 2: Syntax:  ADD.size:Q #IMM, dest
    DECODE_ENTRY(1, ADD_F4_B,       "|1010|0000|....|....|");  //  P.145 m16c   Form 4: Syntax:  ADD.size:G src, dest
    DECODE_ENTRY(1, ADD_F4_W,       "|1010|0001|....|....|");  //  P.145 m16c   Form 4: Syntax:  ADD.size:G src, dest
    DECODE_ENTRY(1, ADD_F6_B,       "|0111|1100|1110|1011|");  //  P.146 m16c   Form 6: Syntax:  ADD.size:G #IMM, SP
    DECODE_ENTRY(1, ADD_F6_W,       "|0111|1101|1110|1011|");  //  P.146 m16c   Form 6: Syntax:  ADD.size:G #IMM, SP
    DECODE_ENTRY(1, ADD_F7,         "|0111|1101|1011|....|");  //  P.147 m16c   Form 7: Syntax:  ADD.size:Q #IMM, SP
    DECODE_ENTRY(2, ADJNZ_F1_B,     "|1111|1000|....|....|");  //  P.148 m16c   Form 1: Syntax:  ADJNZ.size #IMM, dest, label
    DECODE_ENTRY(2, ADJNZ_F1_W,     "|1111|1001|....|....|");  //  P.148 m16c   Form 1: Syntax:  ADJNZ.size #IMM, dest, label
    DECODE_ENTRY(1, AND_F1_B,       "|0111|0110|0010|....|");  //  P.149 m16c   Form 1: Syntax:  AND.size:G #IMM, dest
    DECODE_ENTRY(1, AND_F1_W,       "|0111|0111|0010|....|");  //  P.149 m16c   Form 1: Syntax:  AND.size:G #IMM, dest
    DECODE_ENTRY(1, AND_F3_B,       "|1001|0000|....|....|");  //  P.150 m16c   Form 3: Syntax:  AND.size:G src, dest
    DECODE_ENTRY(1, AND_F3_W,       "|1001|0001|....|....|");  //  P.150 m16c   Form 3: Syntax:  AND.size:G src, dest
    DECODE_ENTRY(1, BAND_F1,        "|0111|1110|0100|....|");  //  P.152 m16c   Form 1: Syntax:  BAND src
    DECODE_ENTRY(1, BCLR_F1,        "|0111|1110|1000|....|");  //  P.152 m16c   Form 1: Syntax:  BCLR:G dest
    DECODE_ENTRY(1, BMCND_F1,       "|0111|1110|0010|....|");  //  P.154 m16c   Form 1: Syntax:  BMCnd dest
    DECODE_ENTRY(1, BMCND_F2_GEU,   "|0111|1101|1101|0000|");  //  P.155 m16c   Form 2: Syntax:  BMCnd C
    DECODE_ENTRY(1, BMCND_F2_GTU,   "|0111|1101|1101|0001|");  //  P.155 m16c   Form 2: Syntax:  BMCnd C
    DECODE_ENTRY(1, BMCND_F2_EQ,    "|0111|1101|1101|0010|");  //  P.155 m16c   Form 2: Syntax:  BMCnd C
    DECODE_ENTRY(1, BMCND_F2_N,     "|0111|1101|1101|0011|");  //  P.155 m16c   Form 2: Syntax:  BMCnd C
    DECODE_ENTRY(1, BMCND_F2_LTU,   "|0111|1101|1101|0100|");  //  P.155 m16c   Form 2: Syntax:  BMCnd C
    DECODE_ENTRY(1, BMCND_F2_LEU,   "|0111|1101|1101|0101|");  //  P.155 m16c   Form 2: Syntax:  BMCnd C
    DECODE_ENTRY(1, BMCND_F2_NE,    "|0111|1101|1101|0110|");  //  P.155 m16c   Form 2: Syntax:  BMCnd C
    DECODE_ENTRY(1, BMCND_F2_PZ,    "|0111|1101|1101|0111|");  //  P.155 m16c   Form 2: Syntax:  BMCnd C
    DECODE_ENTRY(1, BMCND_F2_LE,    "|0111|1101|1101|1000|");  //  P.155 m16c   Form 2: Syntax:  BMCnd C
    DECODE_ENTRY(1, BMCND_F2_O,     "|0111|1101|1101|1001|");  //  P.155 m16c   Form 2: Syntax:  BMCnd C
    DECODE_ENTRY(1, BMCND_F2_GE,    "|0111|1101|1101|1010|");  //  P.155 m16c   Form 2: Syntax:  BMCnd C
    DECODE_ENTRY(1, BMCND_F2_GT,    "|0111|1101|1101|1100|");  //  P.155 m16c   Form 2: Syntax:  BMCnd C
    DECODE_ENTRY(1, BMCND_F2_NO,    "|0111|1101|1101|1101|");  //  P.155 m16c   Form 2: Syntax:  BMCnd C
    DECODE_ENTRY(1, BMCND_F2_LT,    "|0111|1101|1101|1110|");  //  P.155 m16c   Form 2: Syntax:  BMCnd C
    DECODE_ENTRY(1, BNAND_F1,       "|0111|1110|0101|....|");  //  P.155 m16c   Form 1: Syntax:  BNAND src
    DECODE_ENTRY(1, BNOR_F1,        "|0111|1110|0111|....|");  //  P.156 m16c   Form 1: Syntax:  BNOR src
    DECODE_ENTRY(1, BNOT_F1,        "|0111|1110|1010|....|");  //  P.156 m16c   Form 1: Syntax:  BNOT:G dest
    DECODE_ENTRY(1, BNTST_F1,       "|0111|1110|0011|....|");  //  P.157 m16c   Form 1: Syntax:  BNTST src
    DECODE_ENTRY(1, BNXOR_F1,       "|0111|1110|1101|....|");  //  P.158 m16c   Form 1: Syntax:  BNXOR src
    DECODE_ENTRY(1, BOR_F1,         "|0111|1110|0110|....|");  //  P.158 m16c   Form 1: Syntax:  BOR src
    DECODE_ENTRY(1, BSET_F1,        "|0111|1110|1001|....|");  //  P.159 m16c   Form 1: Syntax:  BSET:G dest
    DECODE_ENTRY(1, BTST_F1,        "|0111|1110|1011|....|");  //  P.160 m16c   Form 1: Syntax:  BTST:G src
    DECODE_ENTRY(1, BTSTC_F1,       "|0111|1110|0000|....|");  //  P.161 m16c   Form 1: Syntax:  BTSTC dest
    DECODE_ENTRY(1, BTSTS_F1,       "|0111|1110|0001|....|");  //  P.162 m16c   Form 1: Syntax:  BTSTS dest
    DECODE_ENTRY(1, BXOR_F1,        "|0111|1110|1100|....|");  //  P.162 m16c   Form 1: Syntax:  BXOR src
    DECODE_ENTRY(1, CMP_F1_B,       "|0111|0110|1000|....|");  //  P.163 m16c   Form 1: Syntax:  CMP.size:G #IMM, dest
    DECODE_ENTRY(1, CMP_F1_W,       "|0111|0111|1000|....|");  //  P.163 m16c   Form 1: Syntax:  CMP.size:G #IMM, dest
    DECODE_ENTRY(2, CMP_F2_B,       "|1101|0000|....|....|");  //  P.164 m16c   Form 2: Syntax:  CMP.size:Q #IMM, dest
    DECODE_ENTRY(2, CMP_F2_W,       "|1101|0001|....|....|");  //  P.164 m16c   Form 2: Syntax:  CMP.size:Q #IMM, dest
    DECODE_ENTRY(2, CMP_F4_B,       "|1100|0000|....|....|");  //  P.166 m16c   Form 4: Syntax:  CMP.size:G src, dest
    DECODE_ENTRY(2, CMP_F4_W,       "|1100|0001|....|....|");  //  P.166 m16c   Form 4: Syntax:  CMP.size:G src, dest
    DECODE_ENTRY(1, DADC_F1,        "|0111|1100|1110|1110|");  //  P.167 m16c   Form 1: Syntax:  DADC.B #IMM8, R0L
    DECODE_ENTRY(1, DADC_F2,        "|0111|1101|1110|1110|");  //  P.168 m16c   Form 2: Syntax:  DADC.W #IMM16, R0
    DECODE_ENTRY(1, DADC_F3,        "|0111|1100|1110|0110|");  //  P.168 m16c   Form 3: Syntax:  DADC.B R0H, R0L
    DECODE_ENTRY(1, DADC_F4,        "|0111|1101|1110|0110|");  //  P.169 m16c   Form 4: Syntax:  DADC.W R1, R0
    DECODE_ENTRY(1, DADD_F1,        "|0111|1100|1110|1100|");  //  P.169 m16c   Form 1: Syntax:  DADD.B #IMM8, R0L
    DECODE_ENTRY(1, DADD_F2,        "|0111|1101|1110|1100|");  //  P.170 m16c   Form 2: Syntax:  DADD.W #IMM16, R0
    DECODE_ENTRY(1, DADD_F3,        "|0111|1100|1110|0100|");  //  P.170 m16c   Form 3: Syntax:  DADD.B R0H, R0L
    DECODE_ENTRY(1, DADD_F4,        "|0111|1101|1110|0100|");  //  P.171 m16c   Form 4: Syntax:  DADD.W R1, R0
    DECODE_ENTRY(1, DIV_F1_B,       "|0111|1100|1110|0001|");  //  P.172 m16c   Form 1: Syntax:  DIV.size #IMM
    DECODE_ENTRY(1, DIV_F1_W,       "|0111|1101|1110|0001|");  //  P.172 m16c   Form 1: Syntax:  DIV.size #IMM
    DECODE_ENTRY(1, DIV_F2_B,       "|0111|0110|1101|....|");  //  P.173 m16c   Form 2: Syntax:  DIV.size src
    DECODE_ENTRY(1, DIV_F2_W,       "|0111|0111|1101|....|");  //  P.173 m16c   Form 2: Syntax:  DIV.size src
    DECODE_ENTRY(1, DIVU_F1_B,      "|0111|1100|1110|0000|");  //  P.173 m16c   Form 1: Syntax:  DIVU.size #IMM
    DECODE_ENTRY(1, DIVU_F1_W,      "|0111|1101|1110|0000|");  //  P.173 m16c   Form 1: Syntax:  DIVU.size #IMM
    DECODE_ENTRY(1, DIVU_F2_B,      "|0111|0110|1100|....|");  //  P.174 m16c   Form 2: Syntax:  DIVU.size src
    DECODE_ENTRY(1, DIVU_F2_W,      "|0111|0111|1100|....|");  //  P.174 m16c   Form 2: Syntax:  DIVU.size src
    DECODE_ENTRY(1, DIVX_F1_B,      "|0111|1100|1110|0011|");  //  P.174 m16c   Form 1: Syntax:  DIVX.size #IMM
    DECODE_ENTRY(1, DIVX_F1_W,      "|0111|1101|1110|0011|");  //  P.174 m16c   Form 1: Syntax:  DIVX.size #IMM
    DECODE_ENTRY(1, DIVX_F2_B,      "|0111|0110|1001|....|");  //  P.175 m16c   Form 2: Syntax:  DIVX.size src
    DECODE_ENTRY(1, DIVX_F2_W,      "|0111|0111|1001|....|");  //  P.175 m16c   Form 2: Syntax:  DIVX.size src
    DECODE_ENTRY(1, DSBB_F1,        "|0111|1100|1110|1111|");  //  P.175 m16c   Form 1: Syntax:  DSBB.B #IMM8, R0L
    DECODE_ENTRY(1, DSBB_F2,        "|0111|1101|1110|1111|");  //  P.176 m16c   Form 2: Syntax:  DSBB.W #IMM16, R0
    DECODE_ENTRY(1, DSBB_F3,        "|0111|1100|1110|0111|");  //  P.176 m16c   Form 3: Syntax:  DSBB.B R0H, R0L
    DECODE_ENTRY(1, DSBB_F4,        "|0111|1101|1110|0111|");  //  P.177 m16c   Form 4: Syntax:  DSBB.W R1, R0
    DECODE_ENTRY(1, DSUB_F1,        "|0111|1100|1110|1101|");  //  P.177 m16c   Form 1: Syntax:  DSUB.B #IMM8, R0L
    DECODE_ENTRY(1, DSUB_F2,        "|0111|1101|1110|1101|");  //  P.178 m16c   Form 2: Syntax:  DSUB.W #IMM16, R0
    DECODE_ENTRY(1, DSUB_F3,        "|0111|1100|1110|0101|");  //  P.178 m16c   Form 3: Syntax:  DSUB.B R0H, R0L
    DECODE_ENTRY(1, DSUB_F4,        "|0111|1101|1110|0101|");  //  P.179 m16c   Form 4: Syntax:  DSUB.W R1, R0
    DECODE_ENTRY(1, ENTER_F1,       "|0111|1100|1111|0010|");  //  P.179 m16c   Form 1: Syntax:  ENTER #IMM8
    DECODE_ENTRY(1, EXITD_F1,       "|0111|1101|1111|0010|");  //  P.180 m16c   Form 1: Syntax:  EXITD
    DECODE_ENTRY(1, EXTS_F1,        "|0111|1100|0110|....|");  //  P.180 m16c   Form 1: Syntax:  EXTS.B dest
    DECODE_ENTRY(1, EXTS_F2,        "|0111|1100|1111|0011|");  //  P.181 m16c   Form 2: Syntax:  EXTS.W R0
    DECODE_ENTRY(3, FCLR_F1_C,      "|1110|1011|0000|0101|");  //  P.181 m16c   Form 1: Syntax:  FCLR dest
    DECODE_ENTRY(3, FCLR_F1_D,      "|1110|1011|0001|0101|");  //  P.181 m16c   Form 1: Syntax:  FCLR dest
    DECODE_ENTRY(3, FCLR_F1_Z,      "|1110|1011|0010|0101|");  //  P.181 m16c   Form 1: Syntax:  FCLR dest
    DECODE_ENTRY(3, FCLR_F1_S,      "|1110|1011|0011|0101|");  //  P.181 m16c   Form 1: Syntax:  FCLR dest
    DECODE_ENTRY(3, FCLR_F1_B,      "|1110|1011|0100|0101|");  //  P.181 m16c   Form 1: Syntax:  FCLR dest
    DECODE_ENTRY(3, FCLR_F1_O,      "|1110|1011|0101|0101|");  //  P.181 m16c   Form 1: Syntax:  FCLR dest
    DECODE_ENTRY(3, FCLR_F1_I,      "|1110|1011|0110|0101|");  //  P.181 m16c   Form 1: Syntax:  FCLR dest
    DECODE_ENTRY(3, FCLR_F1_U,      "|1110|1011|0111|0101|");  //  P.181 m16c   Form 1: Syntax:  FCLR dest
    DECODE_ENTRY(3, FSET_F1_C,      "|1110|1011|0000|0100|");  //  P.182 m16c   Form 1: Syntax:  FSET dest
    DECODE_ENTRY(3, FSET_F1_D,      "|1110|1011|0001|0100|");  //  P.182 m16c   Form 1: Syntax:  FSET dest
    DECODE_ENTRY(3, FSET_F1_Z,      "|1110|1011|0010|0100|");  //  P.182 m16c   Form 1: Syntax:  FSET dest
    DECODE_ENTRY(3, FSET_F1_S,      "|1110|1011|0011|0100|");  //  P.182 m16c   Form 1: Syntax:  FSET dest
    DECODE_ENTRY(3, FSET_F1_B,      "|1110|1011|0100|0100|");  //  P.182 m16c   Form 1: Syntax:  FSET dest
    DECODE_ENTRY(3, FSET_F1_O,      "|1110|1011|0101|0100|");  //  P.182 m16c   Form 1: Syntax:  FSET dest
    DECODE_ENTRY(3, FSET_F1_I,      "|1110|1011|0110|0100|");  //  P.182 m16c   Form 1: Syntax:  FSET dest
    DECODE_ENTRY(3, FSET_F1_U,      "|1110|1011|0111|0100|");  //  P.182 m16c   Form 1: Syntax:  FSET dest
    DECODE_ENTRY(1, INT_F1,         "|1110|1011|11..|....|");  //  P.183 m16c   Form 1: Syntax:  INT #IMM
    DECODE_ENTRY(1, JCND_F2_LE,     "|0111|1101|1100|1000|");  //  P.185 m16c   Form 2: Syntax:  JCnd label
    DECODE_ENTRY(1, JCND_F2_O,      "|0111|1101|1100|1001|");  //  P.185 m16c   Form 2: Syntax:  JCnd label
    DECODE_ENTRY(1, JCND_F2_GE,     "|0111|1101|1100|1010|");  //  P.185 m16c   Form 2: Syntax:  JCnd label
    DECODE_ENTRY(1, JCND_F2_GT,     "|0111|1101|1100|1100|");  //  P.185 m16c   Form 2: Syntax:  JCnd label
    DECODE_ENTRY(1, JCND_F2_NO,     "|0111|1101|1100|1101|");  //  P.185 m16c   Form 2: Syntax:  JCnd label
    DECODE_ENTRY(1, JCND_F2_LT,     "|0111|1101|1100|1110|");  //  P.185 m16c   Form 2: Syntax:  JCnd label
    DECODE_ENTRY(1, JMPI_F1,        "|0111|1101|0010|....|");  //  P.187 m16c   Form 1: Syntax:  JMPI.W src
    DECODE_ENTRY(1, JMPI_F2,        "|0111|1101|0000|....|");  //  P.188 m16c   Form 2: Syntax:  JMPI.A src
    DECODE_ENTRY(1, JSRI_F1,        "|0111|1101|0011|....|");  //  P.190 m16c   Form 1: Syntax:  JSRI.W src
    DECODE_ENTRY(1, JSRI_F2,        "|0111|1101|0001|....|");  //  P.190 m16c   Form 2: Syntax:  JSRI.A src
    DECODE_ENTRY(3, LDC_F1_INTBL,   "|1110|1011|0001|0000|");  //  P.191 m16c   Form 1: Syntax:  LDC #IMM16, dest
    DECODE_ENTRY(3, LDC_F1_INTBH,   "|1110|1011|0010|0000|");  //  P.191 m16c   Form 1: Syntax:  LDC #IMM16, dest
    DECODE_ENTRY(3, LDC_F1_FLG,     "|1110|1011|0011|0000|");  //  P.191 m16c   Form 1: Syntax:  LDC #IMM16, dest
    DECODE_ENTRY(3, LDC_F1_ISP,     "|1110|1011|0100|0000|");  //  P.191 m16c   Form 1: Syntax:  LDC #IMM16, dest
    DECODE_ENTRY(3, LDC_F1_SP,      "|1110|1011|0101|0000|");  //  P.191 m16c   Form 1: Syntax:  LDC #IMM16, dest
    DECODE_ENTRY(3, LDC_F1_SB,      "|1110|1011|0110|0000|");  //  P.191 m16c   Form 1: Syntax:  LDC #IMM16, dest
    DECODE_ENTRY(3, LDC_F1_FB,      "|1110|1011|0111|0000|");  //  P.191 m16c   Form 1: Syntax:  LDC #IMM16, dest
    DECODE_ENTRY(1, LDC_F2_INTBL,   "|0111|1010|1001|....|");  //  P.192 m16c   Form 2: Syntax:  LDC src, dest
    DECODE_ENTRY(1, LDC_F2_INTBH,   "|0111|1010|1010|....|");  //  P.192 m16c   Form 2: Syntax:  LDC src, dest
    DECODE_ENTRY(1, LDC_F2_FLG,     "|0111|1010|1011|....|");  //  P.192 m16c   Form 2: Syntax:  LDC src, dest
    DECODE_ENTRY(1, LDC_F2_ISP,     "|0111|1010|1100|....|");  //  P.192 m16c   Form 2: Syntax:  LDC src, dest
    DECODE_ENTRY(1, LDC_F2_SP,      "|0111|1010|1101|....|");  //  P.192 m16c   Form 2: Syntax:  LDC src, dest
    DECODE_ENTRY(1, LDC_F2_SB,      "|0111|1010|1110|....|");  //  P.192 m16c   Form 2: Syntax:  LDC src, dest
    DECODE_ENTRY(1, LDC_F2_FB,      "|0111|1010|1111|....|");  //  P.192 m16c   Form 2: Syntax:  LDC src, dest
    DECODE_ENTRY(1, LDCTX_F1,       "|0111|1100|1111|0000|");  //  P.192 m16c   Form 1: Syntax:  LDCTX abs16, abs20
    DECODE_ENTRY(1, LDE_F1_B,       "|0111|0100|1000|....|");  //  P.193 m16c   Form 1: Syntax:  LDE.size abs20, dest
    DECODE_ENTRY(1, LDE_F1_W,       "|0111|0101|1000|....|");  //  P.193 m16c   Form 1: Syntax:  LDE.size abs20, dest
    DECODE_ENTRY(1, LDE_F2_B,       "|0111|0100|1001|....|");  //  P.193 m16c   Form 2: Syntax:  LDE.size dsp:20[A0], dest
    DECODE_ENTRY(1, LDE_F2_W,       "|0111|0101|1001|....|");  //  P.193 m16c   Form 2: Syntax:  LDE.size dsp:20[A0], dest
    DECODE_ENTRY(1, LDE_F3_B,       "|0111|0100|1010|....|");  //  P.194 m16c   Form 3: Syntax:  LDE.size [A1A0], dest
    DECODE_ENTRY(1, LDE_F3_W,       "|0111|0101|1010|....|");  //  P.194 m16c   Form 3: Syntax:  LDE.size [A1A0], dest
    DECODE_ENTRY(1, LDINTB_F1,      "|1110|1011|0010|0000|");  //  P.194 m16c   Form 1: Syntax:  LDINTB #IMM
    DECODE_ENTRY(1, LDIPL_F1,       "|0111|1101|1010|0...|");  //  P.195 m16c   Form 1: Syntax:  LDIPL #IMM
    DECODE_ENTRY(1, MOV_F1_B,       "|0111|0100|1100|....|");  //  P.195 m16c   Form 1: Syntax:  MOV.size:G #IMM, dest
    DECODE_ENTRY(1, MOV_F1_W,       "|0111|0101|1100|....|");  //  P.195 m16c   Form 1: Syntax:  MOV.size:G #IMM, dest
    DECODE_ENTRY(1, MOV_F10_B,      "|0111|0100|1011|....|");  //  P.201 m16c   Form 10: Syntax:  MOV.size:G dsp:8[SP], dest
    DECODE_ENTRY(1, MOV_F10_W,      "|0111|0101|1011|....|");  //  P.201 m16c   Form 10: Syntax:  MOV.size:G dsp:8[SP], dest
    DECODE_ENTRY(1, MOV_F11_B,      "|0111|0100|0011|....|");  //  P.202 m16c   Form 11: Syntax:  MOV.size:G src, dsp:8[SP]
    DECODE_ENTRY(1, MOV_F11_W,      "|0111|0101|0011|....|");  //  P.202 m16c   Form 11: Syntax:  MOV.size:G src, dsp:8[SP]
    DECODE_ENTRY(2, MOV_F2_B,       "|1101|1000|....|....|");  //  P.196 m16c   Form 2: Syntax:  MOV.size:Q #IMM, dest
    DECODE_ENTRY(2, MOV_F2_W,       "|1101|1001|....|....|");  //  P.196 m16c   Form 2: Syntax:  MOV.size:Q #IMM, dest
    DECODE_ENTRY(1, MOV_F6_B,       "|0111|0010|....|....|");  //  P.199 m16c   Form 6: Syntax:  MOV.size:G src, dest
    DECODE_ENTRY(1, MOV_F6_W,       "|0111|0011|....|....|");  //  P.199 m16c   Form 6: Syntax:  MOV.size:G src, dest
    DECODE_ENTRY(2, MOVA_F1_R0,     "|1110|1011|0000|....|");  //  P.202 m16c   Form 1: Syntax:  MOVA src, dest
    DECODE_ENTRY(2, MOVA_F1_R1,     "|1110|1011|0001|....|");  //  P.202 m16c   Form 1: Syntax:  MOVA src, dest
    DECODE_ENTRY(2, MOVA_F1_R2,     "|1110|1011|0010|....|");  //  P.202 m16c   Form 1: Syntax:  MOVA src, dest
    DECODE_ENTRY(2, MOVA_F1_R3,     "|1110|1011|0011|....|");  //  P.202 m16c   Form 1: Syntax:  MOVA src, dest
    DECODE_ENTRY(2, MOVA_F1_A0,     "|1110|1011|0100|....|");  //  P.202 m16c   Form 1: Syntax:  MOVA src, dest
    DECODE_ENTRY(2, MOVA_F1_A1,     "|1110|1011|0101|....|");  //  P.202 m16c   Form 1: Syntax:  MOVA src, dest
    DECODE_ENTRY(1, MOVDIR_F1_LL,   "|0111|1100|1000|....|");  //  P.203 m16c   Form 1: Syntax:  MOVDir R0L, dest
    DECODE_ENTRY(1, MOVDIR_F1_LH,   "|0111|1100|1010|....|");  //  P.203 m16c   Form 1: Syntax:  MOVDir R0L, dest
    DECODE_ENTRY(1, MOVDIR_F1_HL,   "|0111|1100|1001|....|");  //  P.203 m16c   Form 1: Syntax:  MOVDir R0L, dest
    DECODE_ENTRY(1, MOVDIR_F1_HH,   "|0111|1100|1011|....|");  //  P.203 m16c   Form 1: Syntax:  MOVDir R0L, dest
    DECODE_ENTRY(1, MOVDIR_F2_LL,   "|0111|1100|0000|....|");  //  P.204 m16c   Form 2: Syntax:  MOVDir src, R0L
    DECODE_ENTRY(1, MOVDIR_F2_LH,   "|0111|1100|0010|....|");  //  P.204 m16c   Form 2: Syntax:  MOVDir src, R0L
    DECODE_ENTRY(1, MOVDIR_F2_HL,   "|0111|1100|0001|....|");  //  P.204 m16c   Form 2: Syntax:  MOVDir src, R0L
    DECODE_ENTRY(1, MOVDIR_F2_HH,   "|0111|1100|0011|....|");  //  P.204 m16c   Form 2: Syntax:  MOVDir src, R0L
    DECODE_ENTRY(1, MUL_F1_B,       "|0111|1100|0101|....|");  //  P.205 m16c   Form 1: Syntax:  MUL.size #IMM, dest
    DECODE_ENTRY(1, MUL_F1_W,       "|0111|1101|0101|....|");  //  P.205 m16c   Form 1: Syntax:  MUL.size #IMM, dest
    DECODE_ENTRY(1, MUL_F2_B,       "|0111|1000|....|....|");  //  P.206 m16c   Form 2: Syntax:  MUL.size src, dest
    DECODE_ENTRY(1, MUL_F2_W,       "|0111|1001|....|....|");  //  P.206 m16c   Form 2: Syntax:  MUL.size src, dest
    DECODE_ENTRY(1, MULU_F1_B,      "|0111|1100|0100|....|");  //  P.207 m16c   Form 1: Syntax:  MULU.size #IMM, dest
    DECODE_ENTRY(1, MULU_F1_W,      "|0111|1101|0100|....|");  //  P.207 m16c   Form 1: Syntax:  MULU.size #IMM, dest
    DECODE_ENTRY(1, MULU_F2_B,      "|0111|0000|....|....|");  //  P.208 m16c   Form 2: Syntax:  MULU.size src, dest
    DECODE_ENTRY(1, MULU_F2_W,      "|0111|0001|....|....|");  //  P.208 m16c   Form 2: Syntax:  MULU.size src, dest
    DECODE_ENTRY(1, NEG_F1_B,       "|0111|0100|0101|....|");  //  P.209 m16c   Form 1: Syntax:  NEG.size dest
    DECODE_ENTRY(1, NEG_F1_W,       "|0111|0101|0101|....|");  //  P.209 m16c   Form 1: Syntax:  NEG.size dest
    DECODE_ENTRY(1, NOT_F1_B,       "|0111|0100|0111|....|");  //  P.210 m16c   Form 1: Syntax:  NOT.size:G dest
    DECODE_ENTRY(1, NOT_F1_W,       "|0111|0101|0111|....|");  //  P.210 m16c   Form 1: Syntax:  NOT.size:G dest
    DECODE_ENTRY(1, OR_F1_B,        "|0111|0110|0011|....|");  //  P.211 m16c   Form 1: Syntax:  OR.size:G #IMM, dest
    DECODE_ENTRY(1, OR_F1_W,        "|0111|0111|0011|....|");  //  P.211 m16c   Form 1: Syntax:  OR.size:G #IMM, dest
    DECODE_ENTRY(1, OR_F3_B,        "|1001|1000|....|....|");  //  P.212 m16c   Form 3: Syntax:  OR.size:G src, dest
    DECODE_ENTRY(1, OR_F3_W,        "|1001|1001|....|....|");  //  P.212 m16c   Form 3: Syntax:  OR.size:G src, dest
    DECODE_ENTRY(1, POP_F1_B,       "|0111|0100|1101|....|");  //  P.213 m16c   Form 1: Syntax:  POP.size:G dest
    DECODE_ENTRY(1, POP_F1_W,       "|0111|0101|1101|....|");  //  P.213 m16c   Form 1: Syntax:  POP.size:G dest
    DECODE_ENTRY(3, POPC_F1_INTBL,  "|1110|1011|0001|0011|");  //  P.215 m16c   Form 1: Syntax:  POPC dest
    DECODE_ENTRY(3, POPC_F1_INTBH,  "|1110|1011|0010|0011|");  //  P.215 m16c   Form 1: Syntax:  POPC dest
    DECODE_ENTRY(3, POPC_F1_FLG,    "|1110|1011|0011|0011|");  //  P.215 m16c   Form 1: Syntax:  POPC dest
    DECODE_ENTRY(3, POPC_F1_ISP,    "|1110|1011|0100|0011|");  //  P.215 m16c   Form 1: Syntax:  POPC dest
    DECODE_ENTRY(3, POPC_F1_SP,     "|1110|1011|0101|0011|");  //  P.215 m16c   Form 1: Syntax:  POPC dest
    DECODE_ENTRY(3, POPC_F1_SB,     "|1110|1011|0110|0011|");  //  P.215 m16c   Form 1: Syntax:  POPC dest
    DECODE_ENTRY(3, POPC_F1_FB,     "|1110|1011|0111|0011|");  //  P.215 m16c   Form 1: Syntax:  POPC dest
    DECODE_ENTRY(1, PUSH_F1_B,      "|0111|1100|1110|0010|");  //  P.216 m16c   Form 1: Syntax:  PUSH.size:G #IMM
    DECODE_ENTRY(1, PUSH_F1_W,      "|0111|1101|1110|0010|");  //  P.216 m16c   Form 1: Syntax:  PUSH.size:G #IMM
    DECODE_ENTRY(1, PUSH_F2_B,      "|0111|0100|0100|....|");  //  P.216 m16c   Form 2: Syntax:  PUSH.size:G src
    DECODE_ENTRY(1, PUSH_F2_W,      "|0111|0101|0100|....|");  //  P.216 m16c   Form 2: Syntax:  PUSH.size:G src
    DECODE_ENTRY(1, PUSHA_F1,       "|0111|1101|1001|....|");  //  P.218 m16c   Form 1: Syntax:  PUSHA src
    DECODE_ENTRY(3, PUSHC_F1_INTBL, "|1110|1011|0001|0010|");  //  P.218 m16c   Form 1: Syntax:  PUSHC src
    DECODE_ENTRY(3, PUSHC_F1_INTBH, "|1110|1011|0010|0010|");  //  P.218 m16c   Form 1: Syntax:  PUSHC src
    DECODE_ENTRY(3, PUSHC_F1_FLG,   "|1110|1011|0011|0010|");  //  P.218 m16c   Form 1: Syntax:  PUSHC src
    DECODE_ENTRY(3, PUSHC_F1_ISP,   "|1110|1011|0100|0010|");  //  P.218 m16c   Form 1: Syntax:  PUSHC src
    DECODE_ENTRY(3, PUSHC_F1_SP,    "|1110|1011|0101|0010|");  //  P.218 m16c   Form 1: Syntax:  PUSHC src
    DECODE_ENTRY(3, PUSHC_F1_SB,    "|1110|1011|0110|0010|");  //  P.218 m16c   Form 1: Syntax:  PUSHC src
    DECODE_ENTRY(3, PUSHC_F1_FB,    "|1110|1011|0111|0010|");  //  P.218 m16c   Form 1: Syntax:  PUSHC src
    DECODE_ENTRY(1, RMPA_F1_B,      "|0111|1100|1111|0001|");  //  P.220 m16c   Form 1: Syntax:  RMPA.size
    DECODE_ENTRY(1, RMPA_F1_W,      "|0111|1101|1111|0001|");  //  P.220 m16c   Form 1: Syntax:  RMPA.size
    DECODE_ENTRY(1, ROLC_F1_B,      "|0111|0110|1010|....|");  //  P.220 m16c   Form 1: Syntax:  ROLC.size dest
    DECODE_ENTRY(1, ROLC_F1_W,      "|0111|0111|1010|....|");  //  P.220 m16c   Form 1: Syntax:  ROLC.size dest
    DECODE_ENTRY(1, RORC_F1_B,      "|0111|0110|1011|....|");  //  P.221 m16c   Form 1: Syntax:  RORC.size dest
    DECODE_ENTRY(1, RORC_F1_W,      "|0111|0111|1011|....|");  //  P.221 m16c   Form 1: Syntax:  RORC.size dest
    DECODE_ENTRY(1, ROT_F1_B,       "|1110|0000|....|....|");  //  P.222 m16c   Form 1: Syntax:  ROT.size #IMM, dest
    DECODE_ENTRY(1, ROT_F1_W,       "|1110|0001|....|....|");  //  P.222 m16c   Form 1: Syntax:  ROT.size #IMM, dest
    DECODE_ENTRY(1, ROT_F2_B,       "|0111|0100|0110|....|");  //  P.223 m16c   Form 2: Syntax:  ROT.size R1H, dest
    DECODE_ENTRY(1, ROT_F2_W,       "|0111|0101|0110|....|");  //  P.223 m16c   Form 2: Syntax:  ROT.size R1H, dest
    DECODE_ENTRY(1, SBB_F1_B,       "|0111|0110|0111|....|");  //  P.224 m16c   Form 1: Syntax:  SBB.size #IMM, dest
    DECODE_ENTRY(1, SBB_F1_W,       "|0111|0111|0111|....|");  //  P.224 m16c   Form 1: Syntax:  SBB.size #IMM, dest
    DECODE_ENTRY(1, SBB_F2_B,       "|1011|1000|....|....|");  //  P.225 m16c   Form 2: Syntax:  SBB.size src, dest
    DECODE_ENTRY(1, SBB_F2_W,       "|1011|1001|....|....|");  //  P.225 m16c   Form 2: Syntax:  SBB.size src, dest
    DECODE_ENTRY(1, SBJNZ_F1_B,     "|1111|1000|....|....|");  //  P.226 m16c   Form 1: Syntax:  SBJNZ.size #IMM, dest, label
    DECODE_ENTRY(1, SBJNZ_F1_W,     "|1111|1001|....|....|");  //  P.226 m16c   Form 1: Syntax:  SBJNZ.size #IMM, dest, label
    DECODE_ENTRY(1, SHA_F1_B,       "|1111|0000|....|....|");  //  P.227 m16c   Form 1: Syntax:  SHA.size #IMM, dest
    DECODE_ENTRY(1, SHA_F1_W,       "|1111|0001|....|....|");  //  P.227 m16c   Form 1: Syntax:  SHA.size #IMM, dest
    DECODE_ENTRY(1, SHA_F2_B,       "|0111|0100|1111|....|");  //  P.228 m16c   Form 2: Syntax:  SHA.size R1H, dest
    DECODE_ENTRY(1, SHA_F2_W,       "|0111|0101|1111|....|");  //  P.228 m16c   Form 2: Syntax:  SHA.size R1H, dest
    DECODE_ENTRY(1, SHA_F3_R2R0,    "|1110|1011|1010|....|");  //  P.228 m16c   Form 3: Syntax:  SHA.L #IMM, dest
    DECODE_ENTRY(1, SHA_F3_R3R1,    "|1110|1011|1011|....|");  //  P.228 m16c   Form 3: Syntax:  SHA.L #IMM, dest
    DECODE_ENTRY(3, SHA_F4_R2R0,    "|1110|1011|0010|0001|");  //  P.229 m16c   Form 4: Syntax:  SHA.L R1H, dest
    DECODE_ENTRY(3, SHA_F4_R3R1,    "|1110|1011|0011|0001|");  //  P.229 m16c   Form 4: Syntax:  SHA.L R1H, dest
    DECODE_ENTRY(1, SHL_F1_B,       "|1110|1000|....|....|");  //  P.230 m16c   Form 1: Syntax:  SHL.size #IMM, dest
    DECODE_ENTRY(1, SHL_F1_W,       "|1110|1001|....|....|");  //  P.230 m16c   Form 1: Syntax:  SHL.size #IMM, dest
    DECODE_ENTRY(1, SHL_F2_B,       "|0111|0100|1110|....|");  //  P.231 m16c   Form 2: Syntax:  SHL.size R1H, dest
    DECODE_ENTRY(1, SHL_F2_W,       "|0111|0101|1110|....|");  //  P.231 m16c   Form 2: Syntax:  SHL.size R1H, dest
    DECODE_ENTRY(1, SHL_F3_R2R0,    "|1110|1011|1000|....|");  //  P.231 m16c   Form 3: Syntax:  SHL.L #IMM, dest
    DECODE_ENTRY(1, SHL_F3_R3R1,    "|1110|1011|1001|....|");  //  P.231 m16c   Form 3: Syntax:  SHL.L #IMM, dest
    DECODE_ENTRY(3, SHL_F4_R2R0,    "|1110|1011|0000|0001|");  //  P.232 m16c   Form 4: Syntax:  SHL.L R1H, dest
    DECODE_ENTRY(3, SHL_F4_R3R1,    "|1110|1011|0001|0001|");  //  P.232 m16c   Form 4: Syntax:  SHL.L R1H, dest
    DECODE_ENTRY(1, SMOVB_F1_B,     "|0111|1100|1110|1001|");  //  P.232 m16c   Form 1: Syntax:  SMOVB.size
    DECODE_ENTRY(1, SMOVB_F1_W,     "|0111|1101|1110|1001|");  //  P.232 m16c   Form 1: Syntax:  SMOVB.size
    DECODE_ENTRY(1, SMOVF_F1_B,     "|0111|1100|1110|1000|");  //  P.233 m16c   Form 1: Syntax:  SMOVF.size
    DECODE_ENTRY(1, SMOVF_F1_W,     "|0111|1101|1110|1000|");  //  P.233 m16c   Form 1: Syntax:  SMOVF.size
    DECODE_ENTRY(1, SSTR_F1_B,      "|0111|1100|1110|1010|");  //  P.233 m16c   Form 1: Syntax:  SSTR.size
    DECODE_ENTRY(1, SSTR_F1_W,      "|0111|1101|1110|1010|");  //  P.233 m16c   Form 1: Syntax:  SSTR.size
    DECODE_ENTRY(1, STC_F1_INTBL,   "|0111|1011|1001|....|");  //  P.234 m16c   Form 1: Syntax:  STC src, dest
    DECODE_ENTRY(1, STC_F1_INTBH,   "|0111|1011|1010|....|");  //  P.234 m16c   Form 1: Syntax:  STC src, dest
    DECODE_ENTRY(1, STC_F1_FLG,     "|0111|1011|1011|....|");  //  P.234 m16c   Form 1: Syntax:  STC src, dest
    DECODE_ENTRY(1, STC_F1_ISP,     "|0111|1011|1100|....|");  //  P.234 m16c   Form 1: Syntax:  STC src, dest
    DECODE_ENTRY(1, STC_F1_SP,      "|0111|1011|1101|....|");  //  P.234 m16c   Form 1: Syntax:  STC src, dest
    DECODE_ENTRY(1, STC_F1_SB,      "|0111|1011|1110|....|");  //  P.234 m16c   Form 1: Syntax:  STC src, dest
    DECODE_ENTRY(1, STC_F1_FB,      "|0111|1011|1111|....|");  //  P.234 m16c   Form 1: Syntax:  STC src, dest
    DECODE_ENTRY(1, STC_F2,         "|0111|1100|1100|....|");  //  P.234 m16c   Form 2: Syntax:  STC PC, dest
    DECODE_ENTRY(1, STCTX_F1,       "|0111|1101|1111|0000|");  //  P.235 m16c   Form 1: Syntax:  STCTX abs16, abs20
    DECODE_ENTRY(1, STE_F1_B,       "|0111|0100|0000|....|");  //  P.235 m16c   Form 1: Syntax:  STE.size src, abs20
    DECODE_ENTRY(1, STE_F1_W,       "|0111|0101|0000|....|");  //  P.235 m16c   Form 1: Syntax:  STE.size src, abs20
    DECODE_ENTRY(1, STE_F2_B,       "|0111|0100|0001|....|");  //  P.236 m16c   Form 2: Syntax:  STE.size src, dsp:20[A0]
    DECODE_ENTRY(1, STE_F2_W,       "|0111|0101|0001|....|");  //  P.236 m16c   Form 2: Syntax:  STE.size src, dsp:20[A0]
    DECODE_ENTRY(1, STE_F3_B,       "|0111|0100|0010|....|");  //  P.236 m16c   Form 3: Syntax:  STE.size src, [A1A0]
    DECODE_ENTRY(1, STE_F3_W,       "|0111|0101|0010|....|");  //  P.236 m16c   Form 3: Syntax:  STE.size src, [A1A0]
    DECODE_ENTRY(1, SUB_F1_B,       "|0111|0110|0101|....|");  //  P.238 m16c   Form 1: Syntax:  SUB.size:G #IMM, dest
    DECODE_ENTRY(1, SUB_F1_W,       "|0111|0111|0101|....|");  //  P.238 m16c   Form 1: Syntax:  SUB.size:G #IMM, dest
    DECODE_ENTRY(1, SUB_F3_B,       "|1010|1000|....|....|");  //  P.240 m16c   Form 3: Syntax:  SUB.size:G src, dest
    DECODE_ENTRY(1, SUB_F3_W,       "|1010|1001|....|....|");  //  P.240 m16c   Form 3: Syntax:  SUB.size:G src, dest
    DECODE_ENTRY(1, TST_F1_B,       "|0111|0110|0000|....|");  //  P.241 m16c   Form 1: Syntax:  TST.size #IMM, dest
    DECODE_ENTRY(1, TST_F1_W,       "|0111|0111|0000|....|");  //  P.241 m16c   Form 1: Syntax:  TST.size #IMM, dest
    DECODE_ENTRY(1, TST_F2_B,       "|1000|0000|....|....|");  //  P.242 m16c   Form 2: Syntax:  TST.size src, dest
    DECODE_ENTRY(1, TST_F2_W,       "|1000|0001|....|....|");  //  P.242 m16c   Form 2: Syntax:  TST.size src, dest
    DECODE_ENTRY(1, WAIT_F1,        "|0111|1101|1111|0011|");  //  P.243 m16c   Form 1: Syntax:  WAIT
    DECODE_ENTRY(1, XCHG_F1_B_R0L,  "|0111|1010|0000|....|");  //  P.244 m16c   Form 1: Syntax:  XCHG.size src, dest
    DECODE_ENTRY(1, XCHG_F1_B_R0H,  "|0111|1010|0001|....|");  //  P.244 m16c   Form 1: Syntax:  XCHG.size src, dest
    DECODE_ENTRY(1, XCHG_F1_B_R1L,  "|0111|1010|0010|....|");  //  P.244 m16c   Form 1: Syntax:  XCHG.size src, dest
    DECODE_ENTRY(1, XCHG_F1_B_R1H,  "|0111|1010|0011|....|");  //  P.244 m16c   Form 1: Syntax:  XCHG.size src, dest
    DECODE_ENTRY(1, XCHG_F1_W_R0,   "|0111|1011|0000|....|");  //  P.244 m16c   Form 1: Syntax:  XCHG.size src, dest
    DECODE_ENTRY(1, XCHG_F1_W_R1,   "|0111|1011|0001|....|");  //  P.244 m16c   Form 1: Syntax:  XCHG.size src, dest
    DECODE_ENTRY(1, XCHG_F1_W_R2,   "|0111|1011|0010|....|");  //  P.244 m16c   Form 1: Syntax:  XCHG.size src, dest
    DECODE_ENTRY(1, XCHG_F1_W_R3,   "|0111|1011|0011|....|");  //  P.244 m16c   Form 1: Syntax:  XCHG.size src, dest
    DECODE_ENTRY(1, XOR_F1_B,       "|0111|0110|0001|....|");  //  P.245 m16c   Form 1: Syntax:  XOR.size #IMM, dest
    DECODE_ENTRY(1, XOR_F1_W,       "|0111|0111|0001|....|");  //  P.245 m16c   Form 1: Syntax:  XOR.size #IMM, dest
    DECODE_ENTRY(2, XOR_F2_B,       "|1000|1000|....|....|");  //  P.246 m16c   Form 2: Syntax:  XOR.size src, dest
    DECODE_ENTRY(2, XOR_F2_W,       "|1000|1001|....|....|");  //  P.246 m16c   Form 2: Syntax:  XOR.size src, dest

    return table;
}


//
// This specifies attributes for each opcode
//
const static opAttrs attrsArray[M16C_IT_LAST+1] = {
/*                         opcode reg1 reg2 reg3 reg4 c cond */
    [M16C_IT_ABS_F1_B]           = {fmt:1, opcode:"abs.b", dest:MODE_4BIT, size:B, morphtype:M16C_MT_UNOP, optype:vmi_ABS, },
    [M16C_IT_ABS_F1_W]           = {fmt:1, opcode:"abs.w", dest:MODE_4BIT, size:W, morphtype:M16C_MT_UNOP, optype:vmi_ABS, },
    [M16C_IT_ADCF_F1_B]          = {fmt:1, opcode:"adcf.b", dest:MODE_4BIT, size:B, morphtype:M16C_MT_BINOP, optype:vmi_ADC, },
    [M16C_IT_ADCF_F1_W]          = {fmt:1, opcode:"adcf.w", dest:MODE_4BIT, size:W, morphtype:M16C_MT_BINOP, optype:vmi_ADC, },
    [M16C_IT_ADC_F1_B]           = {fmt:1, opcode:"adc.b", dest:MODE_4BIT, size:B, src:MODE_IMM8, morphtype:M16C_MT_BINOP, optype:vmi_ADC, },
    [M16C_IT_ADC_F1_W]           = {fmt:1, opcode:"adc.w", dest:MODE_4BIT, size:W, src:MODE_IMM16, morphtype:M16C_MT_BINOP, optype:vmi_ADC, },
    [M16C_IT_ADC_F2_B]           = {fmt:2, opcode:"adc.b", src:MODE_4BIT, dest:MODE_4BIT, size:B, morphtype:M16C_MT_BINOP, optype:vmi_ADC, },
    [M16C_IT_ADC_F2_W]           = {fmt:2, opcode:"adc.w", src:MODE_4BIT, dest:MODE_4BIT, size:W, morphtype:M16C_MT_BINOP, optype:vmi_ADC, },
    [M16C_IT_ADD_F1_B]           = {fmt:1, opcode:"add.b:g", dest:MODE_4BIT, size:B, src:MODE_IMM8, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_ADD_F1_W]           = {fmt:1, opcode:"add.w:g", dest:MODE_4BIT, size:W, src:MODE_IMM16, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_ADD_F2_B]           = {fmt:2, opcode:"add.b:q", src:MODE_IMM4, dest:MODE_4BIT, size:B, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_ADD_F2_W]           = {fmt:2, opcode:"add.w:q", src:MODE_IMM4, dest:MODE_4BIT, size:W, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_ADD_F3_ABS]         = {fmt:3, opcode:"add.b:s", size:B, src:MODE_IMM8, dest:MODE_ABS16, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_ADD_F3_FB]          = {fmt:3, opcode:"add.b:s", size:B, src:MODE_IMM8, dest:MODE_DSP8, dreg:M16C_REG_FB, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_ADD_F3_R0H]         = {fmt:3, opcode:"add.b:s", size:B, src:MODE_IMM8, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_ADD_F3_R0L]         = {fmt:3, opcode:"add.b:s", size:B, src:MODE_IMM8, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_ADD_F3_SB]          = {fmt:3, opcode:"add.b:s", size:B, src:MODE_IMM8, dest:MODE_DSP8, dreg:M16C_REG_SB, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_ADD_F4_B]           = {fmt:4, opcode:"add.b:g", src:MODE_4BIT, dest:MODE_4BIT, size:B, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_ADD_F4_W]           = {fmt:4, opcode:"add.w:g", src:MODE_4BIT, dest:MODE_4BIT, size:W, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_ADD_F5_ABS_R0H]     = {fmt:5, opcode:"add.b:s", size:B, src:MODE_ABS16, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_ADD_F5_ABS_R0L]     = {fmt:5, opcode:"add.b:s", size:B, src:MODE_ABS16, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_ADD_F5_FB_R0H]      = {fmt:5, opcode:"add.b:s", size:B, src:MODE_DSP8, sreg:M16C_REG_FB, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_ADD_F5_FB_R0L]      = {fmt:5, opcode:"add.b:s", size:B, src:MODE_DSP8, sreg:M16C_REG_FB, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_ADD_F5_R0H_R0L]     = {fmt:5, opcode:"add.b:s", size:B, src:MODE_REG, sreg:M16C_REG_R0H, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_ADD_F5_R0L_R0H]     = {fmt:5, opcode:"add.b:s", size:B, src:MODE_REG, sreg:M16C_REG_R0L, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_ADD_F5_SB_R0H]      = {fmt:5, opcode:"add.b:s", size:B, src:MODE_DSP8, sreg:M16C_REG_SB, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_ADD_F5_SB_R0L]      = {fmt:5, opcode:"add.b:s", size:B, src:MODE_DSP8, sreg:M16C_REG_SB, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_ADD_F6_B]           = {fmt:6, opcode:"add.b:g", dest:MODE_REG, dreg:M16C_REG_SP, size:B, src:MODE_IMM8, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_ADD_F6_W]           = {fmt:6, opcode:"add.w:g", dest:MODE_REG, dreg:M16C_REG_SP, size:W, src:MODE_IMM16, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_ADD_F7]             = {fmt:7, opcode:"add.b:q", src:MODE_IMM4, dest:MODE_REG, dreg:M16C_REG_SP, size:W, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_ADJNZ_F1_B]         = {fmt:1, opcode:"adjnz.b", src:MODE_IMM4, dest:MODE_4BIT, cons:LABEL8, size:B, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_ADJNZ_F1_W]         = {fmt:1, opcode:"adjnz.w", src:MODE_IMM4, dest:MODE_4BIT, cons:LABEL8, size:W, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_AND_F1_B]           = {fmt:1, opcode:"and.b:g", dest:MODE_4BIT, size:B, src:MODE_IMM8, morphtype:M16C_MT_BINOP, optype:vmi_AND, flags:&flagsZS},
    [M16C_IT_AND_F1_W]           = {fmt:1, opcode:"and.w:g", dest:MODE_4BIT, size:W, src:MODE_IMM16, morphtype:M16C_MT_BINOP, optype:vmi_AND, flags:&flagsZS},
    [M16C_IT_AND_F2_ABS]         = {fmt:2, opcode:"and.b:s", size:B, src:MODE_IMM8, dest:MODE_ABS16, morphtype:M16C_MT_BINOP, optype:vmi_AND, flags:&flagsZS},
    [M16C_IT_AND_F2_FB]          = {fmt:2, opcode:"and.b:s", size:B, src:MODE_IMM8, dest:MODE_DSP8, dreg:M16C_REG_FB, morphtype:M16C_MT_BINOP, optype:vmi_AND, flags:&flagsZS},
    [M16C_IT_AND_F2_R0H]         = {fmt:2, opcode:"and.b:s", size:B, src:MODE_IMM8, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_BINOP, optype:vmi_AND, flags:&flagsZS},
    [M16C_IT_AND_F2_R0L]         = {fmt:2, opcode:"and.b:s", size:B, src:MODE_IMM8, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_AND, flags:&flagsZS},
    [M16C_IT_AND_F2_SB]          = {fmt:2, opcode:"and.b:s", size:B, src:MODE_IMM8, dest:MODE_DSP8, dreg:M16C_REG_SB, morphtype:M16C_MT_BINOP, optype:vmi_AND, flags:&flagsZS},
    [M16C_IT_AND_F3_B]           = {fmt:3, opcode:"and.b:g", size:B, src:MODE_4BIT, dest:MODE_4BIT, size:B, morphtype:M16C_MT_BINOP, optype:vmi_AND, flags:&flagsZS},
    [M16C_IT_AND_F3_W]           = {fmt:3, opcode:"and.w:g", size:W, src:MODE_4BIT, dest:MODE_4BIT, size:W, morphtype:M16C_MT_BINOP, optype:vmi_AND, flags:&flagsZS},
    [M16C_IT_AND_F4_ABS_R0H]     = {fmt:4, opcode:"and.b:s", size:B, src:MODE_ABS16, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_BINOP, optype:vmi_AND, flags:&flagsZS},
    [M16C_IT_AND_F4_ABS_R0L]     = {fmt:4, opcode:"and.b:s", size:B, src:MODE_ABS16, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_AND, flags:&flagsZS},
    [M16C_IT_AND_F4_FB_R0H]      = {fmt:4, opcode:"and.b:s", size:B, src:MODE_DSP8, sreg:M16C_REG_FB, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_BINOP, optype:vmi_AND, flags:&flagsZS},
    [M16C_IT_AND_F4_FB_R0L]      = {fmt:4, opcode:"and.b:s", size:B, src:MODE_DSP8, sreg:M16C_REG_FB, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_AND, flags:&flagsZS},
    [M16C_IT_AND_F4_R0H_R0L]     = {fmt:4, opcode:"and.b:s", size:B, src:MODE_REG, sreg:M16C_REG_R0H, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_AND, flags:&flagsZS},
    [M16C_IT_AND_F4_R0L_R0H]     = {fmt:4, opcode:"and.b:s", size:B, src:MODE_REG, sreg:M16C_REG_R0L, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_BINOP, optype:vmi_AND, flags:&flagsZS},
    [M16C_IT_AND_F4_SB_R0H]      = {fmt:4, opcode:"and.b:s", size:B, src:MODE_DSP8, sreg:M16C_REG_SB, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_BINOP, optype:vmi_AND, flags:&flagsZS},
    [M16C_IT_AND_F4_SB_R0L]      = {fmt:4, opcode:"and.b:s", size:B, src:MODE_DSP8, sreg:M16C_REG_SB, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_AND, flags:&flagsZS},
    [M16C_IT_BAND_F1]            = {fmt:1, opcode:"band", morphtype:M16C_MT_BINOP, optype:vmi_AND, },
    [M16C_IT_BCLR_F1]            = {fmt:1, opcode:"bclr:g", dest:MODE_4BIT, size:BIT, morphtype:M16C_MT_BITOP, optype:vmi_ANDN, },
    [M16C_IT_BCLR_F2_0]          = {fmt:2, opcode:"bclr:s", cons:OFFSET8, bit:0, morphtype:M16C_MT_BITOP, optype:vmi_ANDN, },
    [M16C_IT_BCLR_F2_1]          = {fmt:2, opcode:"bclr:s", cons:OFFSET8, bit:1, morphtype:M16C_MT_BITOP, optype:vmi_ANDN, },
    [M16C_IT_BCLR_F2_2]          = {fmt:2, opcode:"bclr:s", cons:OFFSET8, bit:2, morphtype:M16C_MT_BITOP, optype:vmi_ANDN, },
    [M16C_IT_BCLR_F2_3]          = {fmt:2, opcode:"bclr:s", cons:OFFSET8, bit:3, morphtype:M16C_MT_BITOP, optype:vmi_ANDN, },
    [M16C_IT_BCLR_F2_4]          = {fmt:2, opcode:"bclr:s", cons:OFFSET8, bit:4, morphtype:M16C_MT_BITOP, optype:vmi_ANDN, },
    [M16C_IT_BCLR_F2_5]          = {fmt:2, opcode:"bclr:s", cons:OFFSET8, bit:5, morphtype:M16C_MT_BITOP, optype:vmi_ANDN, },
    [M16C_IT_BCLR_F2_6]          = {fmt:2, opcode:"bclr:s", cons:OFFSET8, bit:6, morphtype:M16C_MT_BITOP, optype:vmi_ANDN, },
    [M16C_IT_BCLR_F2_7]          = {fmt:2, opcode:"bclr:s", cons:OFFSET8, bit:7, morphtype:M16C_MT_BITOP, optype:vmi_ANDN, },
    [M16C_IT_BMCND_F1]           = {fmt:1, opcode:"bm", size:BIT, dest:MODE_4BIT, cons:CONST_COND8, morphtype:M16C_MT_BITOPC, },
    [M16C_IT_BMCND_F2_EQ]        = {fmt:2, opcode:"bm", cond:EQ, morphtype:M16C_MT_BITOP, dest:MODE_C, },
    [M16C_IT_BMCND_F2_GE]        = {fmt:2, opcode:"bm", cond:GE, morphtype:M16C_MT_BITOP, dest:MODE_C, },
    [M16C_IT_BMCND_F2_GEU]       = {fmt:2, opcode:"bm", cond:GEU, morphtype:M16C_MT_BITOP, dest:MODE_C, },
    [M16C_IT_BMCND_F2_GT]        = {fmt:2, opcode:"bm", cond:GT, morphtype:M16C_MT_BITOP, dest:MODE_C, },
    [M16C_IT_BMCND_F2_GTU]       = {fmt:2, opcode:"bm", cond:GTU, morphtype:M16C_MT_BITOP, dest:MODE_C, },
    [M16C_IT_BMCND_F2_LE]        = {fmt:2, opcode:"bm", cond:LE, morphtype:M16C_MT_BITOP, dest:MODE_C, },
    [M16C_IT_BMCND_F2_LEU]       = {fmt:2, opcode:"bm", cond:LEU, morphtype:M16C_MT_BITOP, dest:MODE_C, },
    [M16C_IT_BMCND_F2_LT]        = {fmt:2, opcode:"bm", cond:LT, morphtype:M16C_MT_BITOP, dest:MODE_C, },
    [M16C_IT_BMCND_F2_LTU]       = {fmt:2, opcode:"bm", cond:LTU, morphtype:M16C_MT_BITOP, dest:MODE_C, },
    [M16C_IT_BMCND_F2_N]         = {fmt:2, opcode:"bm", cond:N, morphtype:M16C_MT_BITOP, dest:MODE_C, },
    [M16C_IT_BMCND_F2_NE]        = {fmt:2, opcode:"bm", cond:NE, morphtype:M16C_MT_BITOP, dest:MODE_C, },
    [M16C_IT_BMCND_F2_NO]        = {fmt:2, opcode:"bm", cond:NO, morphtype:M16C_MT_BITOP, dest:MODE_C, },
    [M16C_IT_BMCND_F2_O]         = {fmt:2, opcode:"bm", cond:O, morphtype:M16C_MT_BITOP, dest:MODE_C, },
    [M16C_IT_BMCND_F2_PZ]        = {fmt:2, opcode:"bm", cond:PZ, morphtype:M16C_MT_BITOP, dest:MODE_C, },
    [M16C_IT_BNAND_F1]           = {fmt:1, opcode:"bnand", morphtype:M16C_MT_BITOP, optype:vmi_NAND, },
    [M16C_IT_BNOR_F1]            = {fmt:1, opcode:"bnor", morphtype:M16C_MT_BITOP, optype:vmi_NOR, },
    [M16C_IT_BNOT_F1]            = {fmt:1, opcode:"bnot:g", morphtype:M16C_MT_BITOP, },
    [M16C_IT_BNOT_F2_0]          = {fmt:2, opcode:"bnot:s", cons:OFFSET8, bit:0, morphtype:M16C_MT_BITOP, },
    [M16C_IT_BNOT_F2_1]          = {fmt:2, opcode:"bnot:s", cons:OFFSET8, bit:1, morphtype:M16C_MT_BITOP, },
    [M16C_IT_BNOT_F2_2]          = {fmt:2, opcode:"bnot:s", cons:OFFSET8, bit:2, morphtype:M16C_MT_BITOP, },
    [M16C_IT_BNOT_F2_3]          = {fmt:2, opcode:"bnot:s", cons:OFFSET8, bit:3, morphtype:M16C_MT_BITOP, },
    [M16C_IT_BNOT_F2_4]          = {fmt:2, opcode:"bnot:s", cons:OFFSET8, bit:4, morphtype:M16C_MT_BITOP, },
    [M16C_IT_BNOT_F2_5]          = {fmt:2, opcode:"bnot:s", cons:OFFSET8, bit:5, morphtype:M16C_MT_BITOP, },
    [M16C_IT_BNOT_F2_6]          = {fmt:2, opcode:"bnot:s", cons:OFFSET8, bit:6, morphtype:M16C_MT_BITOP, },
    [M16C_IT_BNOT_F2_7]          = {fmt:2, opcode:"bnot:s", cons:OFFSET8, bit:7, morphtype:M16C_MT_BITOP, },
    [M16C_IT_BNTST_F1]           = {fmt:1, opcode:"bntst", morphtype:M16C_MT_BITOP, },
    [M16C_IT_BNXOR_F1]           = {fmt:1, opcode:"bnxor", morphtype:M16C_MT_BITOP, optype:vmi_XNOR, },
    [M16C_IT_BOR_F1]             = {fmt:1, opcode:"bor", morphtype:M16C_MT_BITOP, optype:vmi_OR, },
    [M16C_IT_BRK_F1]             = {fmt:1, opcode:"brk", morphtype:M16C_MT_BRK, },
    [M16C_IT_BSET_F1]            = {fmt:1, opcode:"bset:g", dest:MODE_4BIT, size:BIT, morphtype:M16C_MT_BITOP, optype:vmi_OR, },
    [M16C_IT_BSET_F2_0]          = {fmt:2, opcode:"bset:s", size:BIT, cons:OFFSET8, bit:0, morphtype:M16C_MT_BITOP, optype:vmi_OR, },
    [M16C_IT_BSET_F2_1]          = {fmt:2, opcode:"bset:s", size:BIT, cons:OFFSET8, bit:1, morphtype:M16C_MT_BITOP, optype:vmi_OR, },
    [M16C_IT_BSET_F2_2]          = {fmt:2, opcode:"bset:s", size:BIT, cons:OFFSET8, bit:2, morphtype:M16C_MT_BITOP, optype:vmi_OR, },
    [M16C_IT_BSET_F2_3]          = {fmt:2, opcode:"bset:s", size:BIT, cons:OFFSET8, bit:3, morphtype:M16C_MT_BITOP, optype:vmi_OR, },
    [M16C_IT_BSET_F2_4]          = {fmt:2, opcode:"bset:s", size:BIT, cons:OFFSET8, bit:4, morphtype:M16C_MT_BITOP, optype:vmi_OR, },
    [M16C_IT_BSET_F2_5]          = {fmt:2, opcode:"bset:s", size:BIT, cons:OFFSET8, bit:5, morphtype:M16C_MT_BITOP, optype:vmi_OR, },
    [M16C_IT_BSET_F2_6]          = {fmt:2, opcode:"bset:s", size:BIT, cons:OFFSET8, bit:6, morphtype:M16C_MT_BITOP, optype:vmi_OR, },
    [M16C_IT_BSET_F2_7]          = {fmt:2, opcode:"bset:s", size:BIT, cons:OFFSET8, bit:7, morphtype:M16C_MT_BITOP, optype:vmi_OR, },
    [M16C_IT_BTSTC_F1]           = {fmt:1, opcode:"btstc", morphtype:M16C_MT_BITOP, optype:vmi_AND, },
    [M16C_IT_BTSTS_F1]           = {fmt:1, opcode:"btsts", morphtype:M16C_MT_BITOP, optype:vmi_OR, },
    [M16C_IT_BTST_F1]            = {fmt:1, opcode:"btst:g", morphtype:M16C_MT_BITOP, },
    [M16C_IT_BTST_F2_0]          = {fmt:2, opcode:"btst:s", cons:OFFSET8, bit:0, morphtype:M16C_MT_BITOP, },
    [M16C_IT_BTST_F2_1]          = {fmt:2, opcode:"btst:s", cons:OFFSET8, bit:1, morphtype:M16C_MT_BITOP, },
    [M16C_IT_BTST_F2_2]          = {fmt:2, opcode:"btst:s", cons:OFFSET8, bit:2, morphtype:M16C_MT_BITOP, },
    [M16C_IT_BTST_F2_3]          = {fmt:2, opcode:"btst:s", cons:OFFSET8, bit:3, morphtype:M16C_MT_BITOP, },
    [M16C_IT_BTST_F2_4]          = {fmt:2, opcode:"btst:s", cons:OFFSET8, bit:4, morphtype:M16C_MT_BITOP, },
    [M16C_IT_BTST_F2_5]          = {fmt:2, opcode:"btst:s", cons:OFFSET8, bit:5, morphtype:M16C_MT_BITOP, },
    [M16C_IT_BTST_F2_6]          = {fmt:2, opcode:"btst:s", cons:OFFSET8, bit:6, morphtype:M16C_MT_BITOP, },
    [M16C_IT_BTST_F2_7]          = {fmt:2, opcode:"btst:s", cons:OFFSET8, bit:7, morphtype:M16C_MT_BITOP, },
    [M16C_IT_BXOR_F1]            = {fmt:1, opcode:"bxor", morphtype:M16C_MT_BITOP, },
    [M16C_IT_CMP_F1_B]           = {fmt:1, opcode:"cmp.b:g", dest:MODE_4BIT, size:B, src:MODE_IMM8, morphtype:M16C_MT_BINOP, optype:vmi_CMP, },
    [M16C_IT_CMP_F1_W]           = {fmt:1, opcode:"cmp.w:g", dest:MODE_4BIT, size:W, src:MODE_IMM16, morphtype:M16C_MT_BINOP, optype:vmi_CMP, },
    [M16C_IT_CMP_F2_B]           = {fmt:2, opcode:"cmp.b:q", src:MODE_IMM4, dest:MODE_4BIT, size:B, morphtype:M16C_MT_BINOP, optype:vmi_CMP, },
    [M16C_IT_CMP_F2_W]           = {fmt:2, opcode:"cmp.w:q", src:MODE_IMM4, dest:MODE_4BIT, size:W, morphtype:M16C_MT_BINOP, optype:vmi_CMP, },
    [M16C_IT_CMP_F3_ABS]         = {fmt:3, opcode:"cmp.b:s", src:MODE_IMM8, dest:MODE_ABS16, size:B, morphtype:M16C_MT_BINOP, optype:vmi_CMP, },
    [M16C_IT_CMP_F3_FB]          = {fmt:3, opcode:"cmp.b:s", src:MODE_IMM8, dest:MODE_DSP8, dreg:M16C_REG_FB, size:B, morphtype:M16C_MT_BINOP, optype:vmi_CMP, },
    [M16C_IT_CMP_F3_R0H]         = {fmt:3, opcode:"cmp.b:s", src:MODE_IMM8, dest:MODE_REG, dreg:M16C_REG_R0H, size:B, morphtype:M16C_MT_BINOP, optype:vmi_CMP, },
    [M16C_IT_CMP_F3_R0L]         = {fmt:3, opcode:"cmp.b:s", src:MODE_IMM8, dest:MODE_REG, dreg:M16C_REG_R0L, size:B, morphtype:M16C_MT_BINOP, optype:vmi_CMP, },
    [M16C_IT_CMP_F3_SB]          = {fmt:3, opcode:"cmp.b:s", src:MODE_IMM8, dest:MODE_DSP8, dreg:M16C_REG_SB, size:B, morphtype:M16C_MT_BINOP, optype:vmi_CMP, },
    [M16C_IT_CMP_F4_B]           = {fmt:4, opcode:"cmp.b:g", src:MODE_4BIT, dest:MODE_4BIT, size:B, morphtype:M16C_MT_BINOP, optype:vmi_CMP, },
    [M16C_IT_CMP_F4_W]           = {fmt:4, opcode:"cmp.w:g", src:MODE_4BIT, dest:MODE_4BIT, size:W, morphtype:M16C_MT_BINOP, optype:vmi_CMP, },
    [M16C_IT_CMP_F5_ABS_R0H]     = {fmt:5, opcode:"cmp.b:s", size:B, src:MODE_ABS16, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_BINOP, optype:vmi_CMP, },
    [M16C_IT_CMP_F5_ABS_R0L]     = {fmt:5, opcode:"cmp.b:s", size:B, src:MODE_ABS16, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_CMP, },
    [M16C_IT_CMP_F5_FB_R0H]      = {fmt:5, opcode:"cmp.b:s", size:B, src:MODE_DSP8, sreg:M16C_REG_FB, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_BINOP, optype:vmi_CMP, },
    [M16C_IT_CMP_F5_FB_R0L]      = {fmt:5, opcode:"cmp.b:s", size:B, src:MODE_DSP8, sreg:M16C_REG_FB, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_CMP, },
    [M16C_IT_CMP_F5_R0H_R0L]     = {fmt:5, opcode:"cmp.b:s", size:B, src:MODE_REG, sreg:M16C_REG_R0H, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_CMP, },
    [M16C_IT_CMP_F5_R0L_R0H]     = {fmt:5, opcode:"cmp.b:s", size:B, src:MODE_REG, sreg:M16C_REG_R0L, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_BINOP, optype:vmi_CMP, },
    [M16C_IT_CMP_F5_SB_R0H]      = {fmt:5, opcode:"cmp.b:s", size:B, src:MODE_DSP8, sreg:M16C_REG_SB, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_BINOP, optype:vmi_CMP, },
    [M16C_IT_CMP_F5_SB_R0L]      = {fmt:5, opcode:"cmp.b:s", size:B, src:MODE_DSP8, sreg:M16C_REG_SB, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_CMP, },
    [M16C_IT_DADC_F1]            = {fmt:1, opcode:"dadc.b", size:B, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_DADC_F2]            = {fmt:2, opcode:"dadc.w", size:W, dest:MODE_REG, dreg:M16C_REG_R0, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_DADC_F3]            = {fmt:3, opcode:"dadc.b", size:B, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_DADC_F4]            = {fmt:4, opcode:"dadc.w", size:W, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_DADD_F1]            = {fmt:1, opcode:"dadd.b", size:B, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_DADD_F2]            = {fmt:2, opcode:"dadd.w", size:W, dest:MODE_REG, dreg:M16C_REG_R0, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_DADD_F3]            = {fmt:3, opcode:"dadd.b", size:B, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_DADD_F4]            = {fmt:4, opcode:"dadd.w", size:W, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_DEC_F1_ABS]         = {fmt:1, opcode:"dec.b", size:B, src:MODE_IMM_1, dest:MODE_ABS16, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_DEC_F1_FB]          = {fmt:1, opcode:"dec.b", size:B, src:MODE_IMM_1, dest:MODE_DSP8, dreg:M16C_REG_FB, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_DEC_F1_R0H]         = {fmt:1, opcode:"dec.b", size:B, src:MODE_IMM_1, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_DEC_F1_R0L]         = {fmt:1, opcode:"dec.b", size:B, src:MODE_IMM_1, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_DEC_F1_SB]          = {fmt:1, opcode:"dec.b", size:B, src:MODE_IMM_1, dest:MODE_DSP8, dreg:M16C_REG_SB, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_DEC_F2_A0]          = {fmt:2, opcode:"dec.w", size:W, src:MODE_IMM_1, dest:MODE_REG, dreg:M16C_REG_A0, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_DEC_F2_A1]          = {fmt:2, opcode:"dec.w", size:W, src:MODE_IMM_1, dest:MODE_REG, dreg:M16C_REG_A1, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_DIVU_F1_B]          = {fmt:1, opcode:"divu.b", size:B, src:MODE_IMM8, morphtype:M16C_MT_DIV, optype:vmi_DIV, },
    [M16C_IT_DIVU_F1_W]          = {fmt:1, opcode:"divu.w", size:W, src:MODE_IMM16, morphtype:M16C_MT_DIV, optype:vmi_DIV, },
    [M16C_IT_DIVU_F2_B]          = {fmt:2, opcode:"divu.b", src:MODE_4BIT, size:B, morphtype:M16C_MT_DIV, optype:vmi_DIV, },
    [M16C_IT_DIVU_F2_W]          = {fmt:2, opcode:"divu.w", src:MODE_4BIT, size:W, morphtype:M16C_MT_DIV, optype:vmi_DIV, },
    [M16C_IT_DIVX_F1_B]          = {fmt:1, opcode:"divx.b", size:B, src:MODE_IMM8, morphtype:M16C_MT_DIV, optype:vmi_DIV, },
    [M16C_IT_DIVX_F1_W]          = {fmt:1, opcode:"divx.w", size:W, src:MODE_IMM16, morphtype:M16C_MT_DIV, optype:vmi_IDIV, },
    [M16C_IT_DIVX_F2_B]          = {fmt:2, opcode:"divx.b", src:MODE_4BIT, size:B, morphtype:M16C_MT_DIV, optype:vmi_IDIV, },
    [M16C_IT_DIVX_F2_W]          = {fmt:2, opcode:"divx.w", src:MODE_4BIT, size:W, morphtype:M16C_MT_DIV, optype:vmi_IDIV, },
    [M16C_IT_DIV_F1_B]           = {fmt:1, opcode:"div.b", size:B, src:MODE_IMM8, morphtype:M16C_MT_DIV, optype:vmi_IDIV, },
    [M16C_IT_DIV_F1_W]           = {fmt:1, opcode:"div.w", size:W, src:MODE_IMM16, morphtype:M16C_MT_DIV, optype:vmi_IDIV, },
    [M16C_IT_DIV_F2_B]           = {fmt:2, opcode:"div.b", src:MODE_4BIT, size:B, morphtype:M16C_MT_DIV, optype:vmi_IDIV, },
    [M16C_IT_DIV_F2_W]           = {fmt:2, opcode:"div.w", src:MODE_4BIT, size:W, morphtype:M16C_MT_DIV, optype:vmi_IDIV, },
    [M16C_IT_DSBB_F1]            = {fmt:1, opcode:"dsbb.b", size:B, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_DSBB_F2]            = {fmt:2, opcode:"dsbb.w", dest:MODE_REG, dreg:M16C_REG_R0, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_DSBB_F3]            = {fmt:3, opcode:"dsbb.b", size:B, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_DSBB_F4]            = {fmt:4, opcode:"dsbb.w", morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_DSUB_F1]            = {fmt:1, opcode:"dsub.b", size:B, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_DSUB_F2]            = {fmt:2, opcode:"dsub.w", dest:MODE_REG, dreg:M16C_REG_R0, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_DSUB_F3]            = {fmt:3, opcode:"dsub.b", size:B, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_DSUB_F4]            = {fmt:4, opcode:"dsub.w", morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_ENTER_F1]           = {fmt:1, opcode:"enter", src:MODE_IMM8, morphtype:M16C_MT_ENTER, },
    [M16C_IT_EXITD_F1]           = {fmt:1, opcode:"exitd", morphtype:M16C_MT_EXIT, },
    [M16C_IT_EXTS_F1]            = {fmt:1, opcode:"exts.b", size:B, src:MODE_4BIT, morphtype:M16C_MT_EXTS, },
    [M16C_IT_EXTS_F2]            = {fmt:2, opcode:"exts.w", size:W, src:MODE_REG, sreg:M16C_REG_R0, morphtype:M16C_MT_EXTS, },
    [M16C_IT_FCLR_F1_B]          = {fmt:1, opcode:"fclr", src:MODE_ZERO, dest:MODE_B, morphtype:M16C_MT_MOVEF, },
    [M16C_IT_FCLR_F1_C]          = {fmt:1, opcode:"fclr", src:MODE_ZERO, dest:MODE_C, morphtype:M16C_MT_MOVEF, },
    [M16C_IT_FCLR_F1_D]          = {fmt:1, opcode:"fclr", src:MODE_ZERO, dest:MODE_D, morphtype:M16C_MT_MOVEF, },
    [M16C_IT_FCLR_F1_I]          = {fmt:1, opcode:"fclr", src:MODE_ZERO, dest:MODE_I, morphtype:M16C_MT_MOVEF, },
    [M16C_IT_FCLR_F1_O]          = {fmt:1, opcode:"fclr", src:MODE_ZERO, dest:MODE_O, morphtype:M16C_MT_MOVEF, },
    [M16C_IT_FCLR_F1_S]          = {fmt:1, opcode:"fclr", src:MODE_ZERO, dest:MODE_S, morphtype:M16C_MT_MOVEF, },
    [M16C_IT_FCLR_F1_U]          = {fmt:1, opcode:"fclr", src:MODE_ZERO, dest:MODE_U, morphtype:M16C_MT_MOVEF, },
    [M16C_IT_FCLR_F1_Z]          = {fmt:1, opcode:"fclr", src:MODE_ZERO, dest:MODE_Z, morphtype:M16C_MT_MOVEF, },
    [M16C_IT_FSET_F1_B]          = {fmt:1, opcode:"fset", src:MODE_IMM_1, dest:MODE_B, morphtype:M16C_MT_MOVEF, },
    [M16C_IT_FSET_F1_C]          = {fmt:1, opcode:"fset", src:MODE_IMM_1, dest:MODE_C, morphtype:M16C_MT_MOVEF, },
    [M16C_IT_FSET_F1_D]          = {fmt:1, opcode:"fset", src:MODE_IMM_1, dest:MODE_D, morphtype:M16C_MT_MOVEF, },
    [M16C_IT_FSET_F1_I]          = {fmt:1, opcode:"fset", src:MODE_IMM_1, dest:MODE_I, morphtype:M16C_MT_MOVEF, },
    [M16C_IT_FSET_F1_O]          = {fmt:1, opcode:"fset", src:MODE_IMM_1, dest:MODE_O, morphtype:M16C_MT_MOVEF, },
    [M16C_IT_FSET_F1_S]          = {fmt:1, opcode:"fset", src:MODE_IMM_1, dest:MODE_S, morphtype:M16C_MT_MOVEF, },
    [M16C_IT_FSET_F1_U]          = {fmt:1, opcode:"fset", src:MODE_IMM_1, dest:MODE_U, morphtype:M16C_MT_MOVEF, },
    [M16C_IT_FSET_F1_Z]          = {fmt:1, opcode:"fset", src:MODE_IMM_1, dest:MODE_Z, morphtype:M16C_MT_MOVEF, },
    [M16C_IT_INC_F1_ABS]         = {fmt:1, opcode:"inc.b", size:B, src:MODE_IMM_1, dest:MODE_ABS16, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_INC_F1_FB]          = {fmt:1, opcode:"inc.b", size:B, src:MODE_IMM_1, dest:MODE_DSP8, dreg:M16C_REG_FB, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_INC_F1_R0H]         = {fmt:1, opcode:"inc.b", size:B, src:MODE_IMM_1, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_INC_F1_R0L]         = {fmt:1, opcode:"inc.b", size:B, src:MODE_IMM_1, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_INC_F1_SB]          = {fmt:1, opcode:"inc.b", size:B, src:MODE_IMM_1, dest:MODE_DSP8, dreg:M16C_REG_SB, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_INC_F2_A0]          = {fmt:2, opcode:"inc.w", size:W, src:MODE_IMM_1, dest:MODE_REG, dreg:M16C_REG_A0, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_INC_F2_A1]          = {fmt:2, opcode:"inc.w", size:W, src:MODE_IMM_1, dest:MODE_REG, dreg:M16C_REG_A1, morphtype:M16C_MT_BINOP, optype:vmi_ADD, },
    [M16C_IT_INTO_F1]            = {fmt:1, opcode:"into", morphtype:M16C_MT_INTO, },
    [M16C_IT_INT_F1]             = {fmt:1, opcode:"int", src:MODE_IMM6, morphtype:M16C_MT_INT, },
    [M16C_IT_JCND_F1_EQ]         = {fmt:1, opcode:"j", cons:LABEL8, cond:EQ, cons:LABEL8, morphtype:M16C_MT_JMP, },
    [M16C_IT_JCND_F1_GEU]        = {fmt:1, opcode:"j", cons:LABEL8, cond:GEU, cons:LABEL8, morphtype:M16C_MT_JMP, },
    [M16C_IT_JCND_F1_GTU]        = {fmt:1, opcode:"j", cons:LABEL8, cond:GTU, cons:LABEL8, morphtype:M16C_MT_JMP, },
    [M16C_IT_JCND_F1_LEU]        = {fmt:1, opcode:"j", cons:LABEL8, cond:LEU, cons:LABEL8, morphtype:M16C_MT_JMP, },
    [M16C_IT_JCND_F1_LTU]        = {fmt:1, opcode:"j", cons:LABEL8, cond:LTU, cons:LABEL8, morphtype:M16C_MT_JMP, },
    [M16C_IT_JCND_F1_N]          = {fmt:1, opcode:"j", cons:LABEL8, cond:N, cons:LABEL8, morphtype:M16C_MT_JMP, },
    [M16C_IT_JCND_F1_NE]         = {fmt:1, opcode:"j", cons:LABEL8, cond:NE, cons:LABEL8, morphtype:M16C_MT_JMP, },
    [M16C_IT_JCND_F1_PZ]         = {fmt:1, opcode:"j", cons:LABEL8, cond:PZ, cons:LABEL8, morphtype:M16C_MT_JMP, },
    [M16C_IT_JCND_F2_GE]         = {fmt:2, opcode:"j", cond:GE, cons:LABEL8, morphtype:M16C_MT_JMP, },
    [M16C_IT_JCND_F2_GT]         = {fmt:2, opcode:"j", cond:GT, cons:LABEL8, morphtype:M16C_MT_JMP, },
    [M16C_IT_JCND_F2_LE]         = {fmt:2, opcode:"j", cond:LE, cons:LABEL8, morphtype:M16C_MT_JMP, },
    [M16C_IT_JCND_F2_LT]         = {fmt:2, opcode:"j", cond:LT, cons:LABEL8, morphtype:M16C_MT_JMP, },
    [M16C_IT_JCND_F2_NO]         = {fmt:2, opcode:"j", cond:NO, cons:LABEL8, morphtype:M16C_MT_JMP, },
    [M16C_IT_JCND_F2_O]          = {fmt:2, opcode:"j", cond:O, cons:LABEL8, morphtype:M16C_MT_JMP, },
    [M16C_IT_JMPI_F1]            = {fmt:1, opcode:"jmpi.w", size:W, src:MODE_4BIT, morphtype:M16C_MT_JMPI, },
    [M16C_IT_JMPI_F2]            = {fmt:2, opcode:"jmpi.a", size:A, src:MODE_4BIT, morphtype:M16C_MT_JMPI, },
    [M16C_IT_JMPS_F1]            = {fmt:1, opcode:"jmps", src:MODE_IMM8, morphtype:M16C_MT_JMPU, },
    [M16C_IT_JMP_F1_0]           = {fmt:1, opcode:"jmp:s", cons:LABEL8, morphtype:M16C_MT_JMPU, },
    [M16C_IT_JMP_F1_1]           = {fmt:1, opcode:"jmp:s", cons:LABEL8, morphtype:M16C_MT_JMPU, },
    [M16C_IT_JMP_F1_2]           = {fmt:1, opcode:"jmp:s", cons:LABEL8, morphtype:M16C_MT_JMPU, },
    [M16C_IT_JMP_F1_3]           = {fmt:1, opcode:"jmp:s", cons:LABEL8, morphtype:M16C_MT_JMPU, },
    [M16C_IT_JMP_F1_4]           = {fmt:1, opcode:"jmp:s", cons:LABEL8, morphtype:M16C_MT_JMPU, },
    [M16C_IT_JMP_F1_5]           = {fmt:1, opcode:"jmp:s", cons:LABEL8, morphtype:M16C_MT_JMPU, },
    [M16C_IT_JMP_F1_6]           = {fmt:1, opcode:"jmp:s", cons:LABEL8, morphtype:M16C_MT_JMPU, },
    [M16C_IT_JMP_F1_7]           = {fmt:1, opcode:"jmp:s", cons:LABEL8, morphtype:M16C_MT_JMPU, },
    [M16C_IT_JMP_F2]             = {fmt:2, opcode:"jmp.b", cons:LABEL8, morphtype:M16C_MT_JMPU, },
    [M16C_IT_JMP_F3]             = {fmt:3, opcode:"jmp.w", cons:LABEL16, morphtype:M16C_MT_JMPU, },
    [M16C_IT_JMP_F4]             = {fmt:4, opcode:"jmp.a", cons:LABEL20, morphtype:M16C_MT_JMPU, },
    [M16C_IT_JSRI_F1]            = {fmt:1, opcode:"jsri.w", size:W, src:MODE_4BIT, morphtype:M16C_MT_JSRI, },
    [M16C_IT_JSRI_F2]            = {fmt:2, opcode:"jsri.a", size:A, src:MODE_4BIT, morphtype:M16C_MT_JSRI, },
    [M16C_IT_JSRS_F1]            = {fmt:1, opcode:"jsrs", src:MODE_IMM8, morphtype:M16C_MT_JSRS, },
    [M16C_IT_JSR_F1]             = {fmt:1, opcode:"jsr.w", cons:LABEL16, morphtype:M16C_MT_JSR, },
    [M16C_IT_JSR_F2]             = {fmt:2, opcode:"jsr.a", cons:LABEL20, morphtype:M16C_MT_JSR, },
    [M16C_IT_LDCTX_F1]           = {fmt:1, opcode:"ldctx", morphtype:M16C_MT_LDCTX, },
    [M16C_IT_LDC_F1_FB]          = {fmt:1, opcode:"ldc", size:W, src:MODE_IMM16, dest:MODE_REG, dreg:M16C_REG_FB, morphtype:M16C_MT_MOVE, flags:&flagsNONE},
    [M16C_IT_LDC_F1_FLG]         = {fmt:1, opcode:"ldc", size:W, src:MODE_IMM16, dest:MODE_REG, dreg:M16C_REG_FLG, morphtype:M16C_MT_MOVE, flags:&flagsNONE},
    [M16C_IT_LDC_F1_INTBH]       = {fmt:1, opcode:"ldc", size:W, src:MODE_IMM16, dest:MODE_REG, dreg:M16C_REG_INTBH, morphtype:M16C_MT_MOVE, flags:&flagsNONE},
    [M16C_IT_LDC_F1_INTBL]       = {fmt:1, opcode:"ldc", size:W, src:MODE_IMM16, dest:MODE_REG, dreg:M16C_REG_INTBL, morphtype:M16C_MT_MOVE, flags:&flagsNONE},
    [M16C_IT_LDC_F1_ISP]         = {fmt:1, opcode:"ldc", size:W, src:MODE_IMM16, dest:MODE_REG, dreg:M16C_REG_ISP, morphtype:M16C_MT_MOVE, flags:&flagsNONE},
    [M16C_IT_LDC_F1_SB]          = {fmt:1, opcode:"ldc", size:W, src:MODE_IMM16, dest:MODE_REG, dreg:M16C_REG_SB, morphtype:M16C_MT_MOVE, flags:&flagsNONE},
    [M16C_IT_LDC_F1_SP]          = {fmt:1, opcode:"ldc", size:W, src:MODE_IMM16, dest:MODE_REG, dreg:M16C_REG_SP, morphtype:M16C_MT_MOVE, flags:&flagsNONE},
    [M16C_IT_LDC_F2_FB]          = {fmt:2, opcode:"ldc", size:W, src:MODE_4BIT, dest:MODE_REG, dreg:M16C_REG_FB, morphtype:M16C_MT_MOVE, flags:&flagsNONE},
    [M16C_IT_LDC_F2_FLG]         = {fmt:2, opcode:"ldc", size:W, src:MODE_4BIT, dest:MODE_REG, dreg:M16C_REG_FLG, morphtype:M16C_MT_MOVE, flags:&flagsNONE},
    [M16C_IT_LDC_F2_INTBH]       = {fmt:2, opcode:"ldc", size:W, src:MODE_4BIT, dest:MODE_REG, dreg:M16C_REG_INTBH, morphtype:M16C_MT_MOVE, flags:&flagsNONE},
    [M16C_IT_LDC_F2_INTBL]       = {fmt:2, opcode:"ldc", size:W, src:MODE_4BIT, dest:MODE_REG, dreg:M16C_REG_INTBL, morphtype:M16C_MT_MOVE, flags:&flagsNONE},
    [M16C_IT_LDC_F2_ISP]         = {fmt:2, opcode:"ldc", size:W, src:MODE_4BIT, dest:MODE_REG, dreg:M16C_REG_ISP, morphtype:M16C_MT_MOVE, flags:&flagsNONE},
    [M16C_IT_LDC_F2_SB]          = {fmt:2, opcode:"ldc", size:W, src:MODE_4BIT, dest:MODE_REG, dreg:M16C_REG_SB, morphtype:M16C_MT_MOVE, flags:&flagsNONE},
    [M16C_IT_LDC_F2_SP]          = {fmt:2, opcode:"ldc", size:W, src:MODE_4BIT, dest:MODE_REG, dreg:M16C_REG_SP, morphtype:M16C_MT_MOVE, flags:&flagsNONE},
    [M16C_IT_LDE_F1_B]           = {fmt:1, opcode:"lde.b", src:MODE_ABS20, dest:MODE_4BIT, size:B, morphtype:M16C_MT_MOVE, },
    [M16C_IT_LDE_F1_W]           = {fmt:1, opcode:"lde.w", src:MODE_ABS20, dest:MODE_4BIT, size:W, morphtype:M16C_MT_MOVE, },
    [M16C_IT_LDE_F2_B]           = {fmt:2, opcode:"lde.b", src:MODE_DSP20, dest:MODE_4BIT, size:B, morphtype:M16C_MT_MOVE, },
    [M16C_IT_LDE_F2_W]           = {fmt:2, opcode:"lde.w", src:MODE_DSP20, dest:MODE_4BIT, size:W, morphtype:M16C_MT_MOVE, },
    [M16C_IT_LDE_F3_B]           = {fmt:3, opcode:"lde.b", size:B, src:MODE_ADDRI, sreg:M16C_REG_A1A0, dest:MODE_4BIT, morphtype:M16C_MT_MOVE, },
    [M16C_IT_LDE_F3_W]           = {fmt:3, opcode:"lde.w", size:W, src:MODE_ADDRI, sreg:M16C_REG_A1A0, dest:MODE_4BIT, morphtype:M16C_MT_MOVE, },
    [M16C_IT_LDINTB_F1]          = {fmt:1, opcode:"ldintb", morphtype:M16C_MT_MOVE, },
    [M16C_IT_LDIPL_F1]           = {fmt:1, opcode:"ldipl", morphtype:M16C_MT_LDIPL, },
    [M16C_IT_MOVA_F1_A0]         = {fmt:1, opcode:"mova", src:MODE_4BIT, dest:MODE_REG, dreg:M16C_REG_A0, morphtype:M16C_MT_MOVEA, },
    [M16C_IT_MOVA_F1_A1]         = {fmt:1, opcode:"mova", src:MODE_4BIT, dest:MODE_REG, dreg:M16C_REG_A1, morphtype:M16C_MT_MOVEA, },
    [M16C_IT_MOVA_F1_R0]         = {fmt:1, opcode:"mova", src:MODE_4BIT, dest:MODE_REG, dreg:M16C_REG_R0, morphtype:M16C_MT_MOVEA, },
    [M16C_IT_MOVA_F1_R1]         = {fmt:1, opcode:"mova", src:MODE_4BIT, dest:MODE_REG, dreg:M16C_REG_R1, morphtype:M16C_MT_MOVEA, },
    [M16C_IT_MOVA_F1_R2]         = {fmt:1, opcode:"mova", src:MODE_4BIT, dest:MODE_REG, dreg:M16C_REG_R2, morphtype:M16C_MT_MOVEA, },
    [M16C_IT_MOVA_F1_R3]         = {fmt:1, opcode:"mova", src:MODE_4BIT, dest:MODE_REG, dreg:M16C_REG_R3, morphtype:M16C_MT_MOVEA, },
    [M16C_IT_MOVDIR_F1_HH]       = {fmt:1, opcode:"mov", src:MODE_REG, sreg:M16C_REG_R0L, dest:MODE_4BIT, size:B, dir:HH, morphtype:M16C_MT_MOVE, },
    [M16C_IT_MOVDIR_F1_HL]       = {fmt:1, opcode:"mov", src:MODE_REG, sreg:M16C_REG_R0L, dest:MODE_4BIT, size:B, dir:HL, morphtype:M16C_MT_MOVE, },
    [M16C_IT_MOVDIR_F1_LH]       = {fmt:1, opcode:"mov", src:MODE_REG, sreg:M16C_REG_R0L, dest:MODE_4BIT, size:B, dir:LH, morphtype:M16C_MT_MOVE, },
    [M16C_IT_MOVDIR_F1_LL]       = {fmt:1, opcode:"mov", src:MODE_REG, sreg:M16C_REG_R0L, dest:MODE_4BIT, size:B, dir:LL, morphtype:M16C_MT_MOVE, },
    [M16C_IT_MOVDIR_F2_HH]       = {fmt:2, opcode:"mov", src:MODE_4BIT, size:B, dest:MODE_REG, dreg:M16C_REG_R0L, dir:HH, morphtype:M16C_MT_MOVE, },
    [M16C_IT_MOVDIR_F2_HL]       = {fmt:2, opcode:"mov", src:MODE_4BIT, size:B, dest:MODE_REG, dreg:M16C_REG_R0L, dir:HL, morphtype:M16C_MT_MOVE, },
    [M16C_IT_MOVDIR_F2_LH]       = {fmt:2, opcode:"mov", src:MODE_4BIT, size:B, dest:MODE_REG, dreg:M16C_REG_R0L, dir:LH, morphtype:M16C_MT_MOVE, },
    [M16C_IT_MOVDIR_F2_LL]       = {fmt:2, opcode:"mov", src:MODE_4BIT, size:B, dest:MODE_REG, dreg:M16C_REG_R0L, dir:LL, morphtype:M16C_MT_MOVE, },
    [M16C_IT_MOV_F10_B]          = {fmt:10, opcode:"mov.b:g", src:MODE_DSP8, sreg:M16C_REG_SP, dest:MODE_4BIT, size:B, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F10_W]          = {fmt:10, opcode:"mov.w:g", src:MODE_DSP8, sreg:M16C_REG_SP, dest:MODE_4BIT, size:W, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F11_B]          = {fmt:11, opcode:"mov.b:g", size:B, src:MODE_4BIT, dest:MODE_DSP8, dreg:M16C_REG_SP, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F11_W]          = {fmt:11, opcode:"mov.w:g", size:W, src:MODE_4BIT, dest:MODE_DSP8, dreg:M16C_REG_SP, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F1_B]           = {fmt:1, opcode:"mov.b:g", dest:MODE_4BIT, size:B, src:MODE_IMM8, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F1_W]           = {fmt:1, opcode:"mov.w:g", dest:MODE_4BIT, size:W, src:MODE_IMM16, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F2_B]           = {fmt:2, opcode:"mov.b:q", src:MODE_IMM4, dest:MODE_4BIT, size:B, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F2_W]           = {fmt:2, opcode:"mov.w:q", src:MODE_IMM4, dest:MODE_4BIT, size:W, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F3_ABS]         = {fmt:3, opcode:"mov.b:s", size:B, src:MODE_IMM8, dest:MODE_ABS16, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F3_FB]          = {fmt:3, opcode:"mov.b:s", size:B, src:MODE_IMM8, dest:MODE_DSP8, dreg:M16C_REG_FB, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F3_R0H]         = {fmt:3, opcode:"mov.b:s", size:B, src:MODE_IMM8, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F3_R0L]         = {fmt:3, opcode:"mov.b:s", size:B, src:MODE_IMM8, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F3_SB]          = {fmt:3, opcode:"mov.b:s", size:B, src:MODE_IMM8, dest:MODE_DSP8, dreg:M16C_REG_SB, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F4_B_A0]        = {fmt:4, opcode:"mov.b:s", size:B, src:MODE_IMM8, dest:MODE_REG, dreg:M16C_REG_A0, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F4_B_A1]        = {fmt:4, opcode:"mov.b:s", size:B, src:MODE_IMM8, dest:MODE_REG, dreg:M16C_REG_A1, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F4_W_A0]        = {fmt:4, opcode:"mov.w:s", size:W, src:MODE_IMM16, dest:MODE_REG, dreg:M16C_REG_A0, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F4_W_A1]        = {fmt:4, opcode:"mov.w:s", size:W, src:MODE_IMM16, dest:MODE_REG, dreg:M16C_REG_A1, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F5_ABS]         = {fmt:5, opcode:"mov.b:z", size:B, src:MODE_ZERO, dest:MODE_ABS16, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F5_FB]          = {fmt:5, opcode:"mov.b:z", size:B, src:MODE_ZERO, dest:MODE_DSP8, dreg:M16C_REG_FB, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F5_R0H]         = {fmt:5, opcode:"mov.b:z", size:B, src:MODE_ZERO, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F5_R0L]         = {fmt:5, opcode:"mov.b:z", size:B, src:MODE_ZERO, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F5_SB]          = {fmt:5, opcode:"mov.b:z", size:B, src:MODE_ZERO, dest:MODE_DSP8, dreg:M16C_REG_SB, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F6_B]           = {fmt:6, opcode:"mov.b:g", src:MODE_4BIT, dest:MODE_4BIT, size:B, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F6_W]           = {fmt:6, opcode:"mov.w:g", src:MODE_4BIT, dest:MODE_4BIT, size:W, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F7_ABS_A0]      = {fmt:7, opcode:"mov.b:s", size:B, src:MODE_ABS16, dest:MODE_REG, dreg:M16C_REG_A0, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F7_ABS_A1]      = {fmt:7, opcode:"mov.b:s", size:B, src:MODE_ABS16, dest:MODE_REG, dreg:M16C_REG_A1, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F7_FB_A0]       = {fmt:7, opcode:"mov.b:s", size:B, src:MODE_DSP8, sreg:M16C_REG_FB, dest:MODE_REG, dreg:M16C_REG_A0, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F7_FB_A1]       = {fmt:7, opcode:"mov.b:s", size:B, src:MODE_DSP8, sreg:M16C_REG_FB, dest:MODE_REG, dreg:M16C_REG_A1, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F7_R0H_A0]      = {fmt:7, opcode:"mov.b:s", size:B, src:MODE_REG, sreg:M16C_REG_R0H, dest:MODE_REG, dreg:M16C_REG_A0, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F7_R0L_A1]      = {fmt:7, opcode:"mov.b:s", size:B, src:MODE_REG, sreg:M16C_REG_R0L, dest:MODE_REG, dreg:M16C_REG_A1, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F7_SB_A0]       = {fmt:7, opcode:"mov.b:s", size:B, src:MODE_DSP8, sreg:M16C_REG_SB, dest:MODE_REG, dreg:M16C_REG_A0, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F7_SB_A1]       = {fmt:7, opcode:"mov.b:s", size:B, src:MODE_DSP8, sreg:M16C_REG_SB, dest:MODE_REG, dreg:M16C_REG_A1, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F8_R0H_ABS]     = {fmt:8, opcode:"mov.b:s", src:MODE_REG, sreg:M16C_REG_R0H, dest:MODE_ABS16, size:B, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F8_R0H_FB]      = {fmt:8, opcode:"mov.b:s", src:MODE_REG, sreg:M16C_REG_R0H, dest:MODE_DSP8, dreg:M16C_REG_FB, size:B, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F8_R0H_SB]      = {fmt:8, opcode:"mov.b:s", src:MODE_REG, sreg:M16C_REG_R0H, dest:MODE_DSP8, dreg:M16C_REG_SB, size:B, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F8_R0L_ABS]     = {fmt:8, opcode:"mov.b:s", src:MODE_REG, sreg:M16C_REG_R0L, dest:MODE_ABS16, size:B, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F8_R0L_FB]      = {fmt:8, opcode:"mov.b:s", src:MODE_REG, sreg:M16C_REG_R0L, dest:MODE_DSP8, dreg:M16C_REG_FB, size:B, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F8_R0L_SB]      = {fmt:8, opcode:"mov.b:s", src:MODE_REG, sreg:M16C_REG_R0L, dest:MODE_DSP8, dreg:M16C_REG_SB, size:B, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F9_ABS_R0H]     = {fmt:9, opcode:"mov.b:s", src:MODE_ABS16, dest:MODE_REG, dreg:M16C_REG_R0H, size:B, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F9_ABS_R0L]     = {fmt:9, opcode:"mov.b:s", src:MODE_ABS16, dest:MODE_REG, dreg:M16C_REG_R0L, size:B, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F9_FB_R0H]      = {fmt:9, opcode:"mov.b:s", src:MODE_DSP8, sreg:M16C_REG_FB, dest:MODE_REG, dreg:M16C_REG_R0H, size:B, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F9_FB_R0L]      = {fmt:9, opcode:"mov.b:s", src:MODE_DSP8, sreg:M16C_REG_FB, dest:MODE_REG, dreg:M16C_REG_R0L, size:B, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F9_R0H_R0L]     = {fmt:9, opcode:"mov.b:s", src:MODE_REG, sreg:M16C_REG_R0H, dest:MODE_REG, dreg:M16C_REG_R0L, size:B, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F9_R0L_R0H]     = {fmt:9, opcode:"mov.b:s", src:MODE_REG, sreg:M16C_REG_R0L, dest:MODE_REG, dreg:M16C_REG_R0H, size:B, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F9_SB_R0H]      = {fmt:9, opcode:"mov.b:s", src:MODE_DSP8, sreg:M16C_REG_SB, dest:MODE_REG, dreg:M16C_REG_R0H, size:B, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MOV_F9_SB_R0L]      = {fmt:9, opcode:"mov.b:s", src:MODE_DSP8, sreg:M16C_REG_SB, dest:MODE_REG, dreg:M16C_REG_R0L, size:B, morphtype:M16C_MT_MOVE, flags:&flagsZS},
    [M16C_IT_MULU_F1_B]          = {fmt:1, opcode:"mulu.b", dest:MODE_4BIT, size:B, src:MODE_IMM8, morphtype:M16C_MT_BINOP, optype:vmi_MUL, flags:&flagsNONE},
    [M16C_IT_MULU_F1_W]          = {fmt:1, opcode:"mulu.w", dest:MODE_4BIT, size:W, src:MODE_IMM16, morphtype:M16C_MT_BINOP, optype:vmi_MUL, flags:&flagsNONE},
    [M16C_IT_MULU_F2_B]          = {fmt:2, opcode:"mulu.b", src:MODE_4BIT, dest:MODE_4BIT, size:B, morphtype:M16C_MT_BINOP, optype:vmi_MUL, flags:&flagsNONE},
    [M16C_IT_MULU_F2_W]          = {fmt:2, opcode:"mulu.w", src:MODE_4BIT, dest:MODE_4BIT, size:W, morphtype:M16C_MT_BINOP, optype:vmi_MUL, flags:&flagsNONE},
    [M16C_IT_MUL_F1_B]           = {fmt:1, opcode:"mul.b", dest:MODE_4BIT, size:B, src:MODE_IMM8, morphtype:M16C_MT_BINOP, optype:vmi_MUL, flags:&flagsNONE},
    [M16C_IT_MUL_F1_W]           = {fmt:1, opcode:"mul.w", dest:MODE_4BIT, size:W, src:MODE_IMM16, morphtype:M16C_MT_BINOP, optype:vmi_MUL, flags:&flagsNONE},
    [M16C_IT_MUL_F2_B]           = {fmt:2, opcode:"mul.b", src:MODE_4BIT, dest:MODE_4BIT, size:B, morphtype:M16C_MT_BINOP, optype:vmi_MUL, flags:&flagsNONE},
    [M16C_IT_MUL_F2_W]           = {fmt:2, opcode:"mul.w", src:MODE_4BIT, dest:MODE_4BIT, size:W, morphtype:M16C_MT_BINOP, optype:vmi_MUL, flags:&flagsNONE},
    [M16C_IT_NEG_F1_B]           = {fmt:1, opcode:"neg.b", dest:MODE_4BIT, size:B, morphtype:M16C_MT_UNOP, optype:vmi_NEG},
    [M16C_IT_NEG_F1_W]           = {fmt:1, opcode:"neg.w", dest:MODE_4BIT, size:W, morphtype:M16C_MT_UNOP, optype:vmi_NEG},
    [M16C_IT_NOP_F1]             = {fmt:1, opcode:"nop", morphtype:M16C_MT_NOP, },
    [M16C_IT_NOT_F1_B]           = {fmt:1, opcode:"not.b:g", dest:MODE_4BIT, size:B, morphtype:M16C_MT_UNOP, optype:vmi_NOT, flags:&flagsZS},
    [M16C_IT_NOT_F1_W]           = {fmt:1, opcode:"not.w:g", dest:MODE_4BIT, size:W, morphtype:M16C_MT_UNOP, optype:vmi_NOT, flags:&flagsZS},
    [M16C_IT_NOT_F2_ABS]         = {fmt:2, opcode:"not.b:s", dest:MODE_ABS16, morphtype:M16C_MT_UNOP, optype:vmi_NOT, flags:&flagsZS},
    [M16C_IT_NOT_F2_FB]          = {fmt:2, opcode:"not.b:s", dest:MODE_DSP8, dreg:M16C_REG_FB, morphtype:M16C_MT_UNOP, optype:vmi_NOT, flags:&flagsZS},
    [M16C_IT_NOT_F2_R0H]         = {fmt:2, opcode:"not.b:s", dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_UNOP, optype:vmi_NOT, flags:&flagsZS},
    [M16C_IT_NOT_F2_R0L]         = {fmt:2, opcode:"not.b:s", dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_UNOP, optype:vmi_NOT, flags:&flagsZS},
    [M16C_IT_NOT_F2_SB]          = {fmt:2, opcode:"not.b:s", dest:MODE_DSP8, dreg:M16C_REG_SB, morphtype:M16C_MT_UNOP, optype:vmi_NOT, flags:&flagsZS},
    [M16C_IT_OR_F1_B]            = {fmt:1, opcode:"or.b:g", dest:MODE_4BIT, size:B, src:MODE_IMM8, morphtype:M16C_MT_BINOP, optype:vmi_OR, flags:&flagsZS},
    [M16C_IT_OR_F1_W]            = {fmt:1, opcode:"or.w:g", dest:MODE_4BIT, size:W, src:MODE_IMM16, morphtype:M16C_MT_BINOP, optype:vmi_OR, flags:&flagsZS},
    [M16C_IT_OR_F2_ABS]          = {fmt:2, opcode:"or.b:s", src:MODE_IMM8, dest:MODE_ABS16, morphtype:M16C_MT_BINOP, optype:vmi_OR, flags:&flagsZS},
    [M16C_IT_OR_F2_FB]           = {fmt:2, opcode:"or.b:s", src:MODE_IMM8, dest:MODE_DSP8, dreg:M16C_REG_FB, morphtype:M16C_MT_BINOP, optype:vmi_OR, flags:&flagsZS},
    [M16C_IT_OR_F2_R0H]          = {fmt:2, opcode:"or.b:s", src:MODE_IMM8, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_BINOP, optype:vmi_OR, flags:&flagsZS},
    [M16C_IT_OR_F2_R0L]          = {fmt:2, opcode:"or.b:s", src:MODE_IMM8, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_OR, flags:&flagsZS},
    [M16C_IT_OR_F2_SB]           = {fmt:2, opcode:"or.b:s", src:MODE_IMM8, dest:MODE_DSP8, dreg:M16C_REG_SB, morphtype:M16C_MT_BINOP, optype:vmi_OR, flags:&flagsZS},
    [M16C_IT_OR_F3_B]            = {fmt:3, opcode:"or.b:g", src:MODE_4BIT, dest:MODE_4BIT, size:B, morphtype:M16C_MT_BINOP, optype:vmi_OR, flags:&flagsZS},
    [M16C_IT_OR_F3_W]            = {fmt:3, opcode:"or.w:g", src:MODE_4BIT, dest:MODE_4BIT, size:W, morphtype:M16C_MT_BINOP, optype:vmi_OR, flags:&flagsZS},
    [M16C_IT_OR_F4_ABS_R0H]      = {fmt:4, opcode:"or.b:s", src:MODE_ABS16, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_BINOP, optype:vmi_OR, flags:&flagsZS},
    [M16C_IT_OR_F4_ABS_R0L]      = {fmt:4, opcode:"or.b:s", src:MODE_ABS16, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_OR, flags:&flagsZS},
    [M16C_IT_OR_F4_FB_R0H]       = {fmt:4, opcode:"or.b:s", src:MODE_DSP8, sreg:M16C_REG_FB, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_BINOP, optype:vmi_OR, flags:&flagsZS},
    [M16C_IT_OR_F4_FB_R0L]       = {fmt:4, opcode:"or.b:s", src:MODE_DSP8, sreg:M16C_REG_FB, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_OR, flags:&flagsZS},
    [M16C_IT_OR_F4_R0H_R0L]      = {fmt:4, opcode:"or.b:s", src:MODE_REG, sreg:M16C_REG_R0H, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_OR, flags:&flagsZS},
    [M16C_IT_OR_F4_R0L_R0H]      = {fmt:4, opcode:"or.b:s", src:MODE_REG, sreg:M16C_REG_R0L, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_BINOP, optype:vmi_OR, flags:&flagsZS},
    [M16C_IT_OR_F4_SB_R0H]       = {fmt:4, opcode:"or.b:s", src:MODE_DSP8, sreg:M16C_REG_SB, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_BINOP, optype:vmi_OR, flags:&flagsZS},
    [M16C_IT_OR_F4_SB_R0L]       = {fmt:4, opcode:"or.b:s", src:MODE_DSP8, sreg:M16C_REG_SB, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_OR, flags:&flagsZS},
    [M16C_IT_POPC_F1_FB]         = {fmt:1, opcode:"popc", dest:MODE_REG, dreg:M16C_REG_FB, size:W, morphtype:M16C_MT_POP, },
    [M16C_IT_POPC_F1_FLG]        = {fmt:1, opcode:"popc", dest:MODE_REG, dreg:M16C_REG_FLG, size:W, morphtype:M16C_MT_POP, },
    [M16C_IT_POPC_F1_INTBH]      = {fmt:1, opcode:"popc", dest:MODE_REG, dreg:M16C_REG_INTBH, size:W, morphtype:M16C_MT_POP, },
    [M16C_IT_POPC_F1_INTBL]      = {fmt:1, opcode:"popc", dest:MODE_REG, dreg:M16C_REG_INTBL, size:W, morphtype:M16C_MT_POP, },
    [M16C_IT_POPC_F1_ISP]        = {fmt:1, opcode:"popc", dest:MODE_REG, dreg:M16C_REG_ISP, size:W, morphtype:M16C_MT_POP, },
    [M16C_IT_POPC_F1_SB]         = {fmt:1, opcode:"popc", dest:MODE_REG, dreg:M16C_REG_SB, size:W, morphtype:M16C_MT_POP, },
    [M16C_IT_POPC_F1_SP]         = {fmt:1, opcode:"popc", dest:MODE_REG, dreg:M16C_REG_SP, size:W, morphtype:M16C_MT_POP, },
    [M16C_IT_POPM_F1]            = {fmt:1, opcode:"popm", src: MODE_IMM8, size:W, morphtype:M16C_MT_POP_M, },
    [M16C_IT_POP_F1_B]           = {fmt:1, opcode:"pop.b:g", dest:MODE_4BIT, size:B, morphtype:M16C_MT_POP, },
    [M16C_IT_POP_F1_W]           = {fmt:1, opcode:"pop.w:g", dest:MODE_4BIT, size:W, morphtype:M16C_MT_POP, },
    [M16C_IT_POP_F2_R0H]         = {fmt:2, opcode:"pop.b:s", dest:MODE_REG, dreg:M16C_REG_R0H, size:B, morphtype:M16C_MT_POP, },
    [M16C_IT_POP_F2_R0L]         = {fmt:2, opcode:"pop.b:s", dest:MODE_REG, dreg:M16C_REG_R0L, size:B, morphtype:M16C_MT_POP, },
    [M16C_IT_POP_F3_A0]          = {fmt:3, opcode:"pop.w:s", dest:MODE_REG, dreg:M16C_REG_A0, size:W, morphtype:M16C_MT_POP, },
    [M16C_IT_POP_F3_A1]          = {fmt:3, opcode:"pop.w:s", dest:MODE_REG, dreg:M16C_REG_A1, size:W, morphtype:M16C_MT_POP, },
    [M16C_IT_PUSHA_F1]           = {fmt:1, opcode:"pusha", src:MODE_4BIT, morphtype:M16C_MT_PUSH, },
    [M16C_IT_PUSHC_F1_FB]        = {fmt:1, opcode:"pushc", src:MODE_REG, sreg:M16C_REG_FB, size:W, morphtype:M16C_MT_PUSH, },
    [M16C_IT_PUSHC_F1_FLG]       = {fmt:1, opcode:"pushc", src:MODE_REG, sreg:M16C_REG_FLG, size:W, morphtype:M16C_MT_PUSH, },
    [M16C_IT_PUSHC_F1_INTBH]     = {fmt:1, opcode:"pushc", src:MODE_REG, sreg:M16C_REG_INTBH, size:W, morphtype:M16C_MT_PUSH, },
    [M16C_IT_PUSHC_F1_INTBL]     = {fmt:1, opcode:"pushc", src:MODE_REG, sreg:M16C_REG_INTBL, size:W, morphtype:M16C_MT_PUSH, },
    [M16C_IT_PUSHC_F1_ISP]       = {fmt:1, opcode:"pushc", src:MODE_REG, sreg:M16C_REG_ISP, size:W, morphtype:M16C_MT_PUSH, },
    [M16C_IT_PUSHC_F1_SB]        = {fmt:1, opcode:"pushc", src:MODE_REG, sreg:M16C_REG_SB, size:W, morphtype:M16C_MT_PUSH, },
    [M16C_IT_PUSHC_F1_SP]        = {fmt:1, opcode:"pushc", src:MODE_REG, sreg:M16C_REG_SP, size:W, morphtype:M16C_MT_PUSH, },
    [M16C_IT_PUSHM_F1]           = {fmt:1, opcode:"pushm", src: MODE_IMM8, size:W, morphtype:M16C_MT_PUSH_M, },
    [M16C_IT_PUSH_F1_B]          = {fmt:1, opcode:"push.b:g", size:B, src:MODE_IMM8, morphtype:M16C_MT_PUSH, },
    [M16C_IT_PUSH_F1_W]          = {fmt:1, opcode:"push.w:g", size:W, src:MODE_IMM16, morphtype:M16C_MT_PUSH, },
    [M16C_IT_PUSH_F2_B]          = {fmt:2, opcode:"push.b:g", src:MODE_4BIT, size:B, morphtype:M16C_MT_PUSH, },
    [M16C_IT_PUSH_F2_W]          = {fmt:2, opcode:"push.w:g", src:MODE_4BIT, size:W, morphtype:M16C_MT_PUSH, },
    [M16C_IT_PUSH_F3_R0H]        = {fmt:3, opcode:"push.b:s", src:MODE_REG, sreg:M16C_REG_R0H, size:B, morphtype:M16C_MT_PUSH, },
    [M16C_IT_PUSH_F3_R0L]        = {fmt:3, opcode:"push.b:s", src:MODE_REG, sreg:M16C_REG_R0L, size:B, morphtype:M16C_MT_PUSH, },
    [M16C_IT_PUSH_F4_A0]         = {fmt:4, opcode:"push.w:s", src:MODE_REG, sreg:M16C_REG_A0, size:W, morphtype:M16C_MT_PUSH, },
    [M16C_IT_PUSH_F4_A1]         = {fmt:4, opcode:"push.w:s", src:MODE_REG, sreg:M16C_REG_A1, size:W, morphtype:M16C_MT_PUSH, },
    [M16C_IT_REIT_F1]            = {fmt:1, opcode:"reit", morphtype:M16C_MT_REIT, },
    [M16C_IT_RMPA_F1_B]          = {fmt:1, opcode:"rmpa.b", size:B, morphtype:M16C_MT_RMPA, },
    [M16C_IT_RMPA_F1_W]          = {fmt:1, opcode:"rmpa.w", size:W, morphtype:M16C_MT_RMPA, },
    [M16C_IT_ROLC_F1_B]          = {fmt:1, opcode:"rolc.b", src:MODE_IMM_1, dest:MODE_4BIT, size:B, morphtype:M16C_MT_ROT, optype:vmi_RCL, flags:&flagsC_CZS},
    [M16C_IT_ROLC_F1_W]          = {fmt:1, opcode:"rolc.w", src:MODE_IMM_1, dest:MODE_4BIT, size:W, morphtype:M16C_MT_ROT, optype:vmi_RCL, flags:&flagsC_CZS},
    [M16C_IT_RORC_F1_B]          = {fmt:1, opcode:"rorc.b", src:MODE_IMM_1, dest:MODE_4BIT, size:B, morphtype:M16C_MT_ROT, optype:vmi_RCR, flags:&flagsC_CZS},
    [M16C_IT_RORC_F1_W]          = {fmt:1, opcode:"rorc.w", src:MODE_IMM_1, dest:MODE_4BIT, size:W, morphtype:M16C_MT_ROT, optype:vmi_RCR, flags:&flagsC_CZS},
    [M16C_IT_ROT_F1_B]           = {fmt:1, opcode:"rot.b", src:MODE_IMM4_2, dest:MODE_4BIT, size:B, morphtype:M16C_MT_ROT, optype:vmi_ROL, flags:&flagsCZS},
    [M16C_IT_ROT_F1_W]           = {fmt:1, opcode:"rot.w", src:MODE_IMM4_2, dest:MODE_4BIT, size:W, morphtype:M16C_MT_ROT, optype:vmi_ROL, flags:&flagsCZS},
    [M16C_IT_ROT_F2_B]           = {fmt:2, opcode:"rot.b", src:MODE_REGB, sreg:M16C_REG_R1H, dest:MODE_4BIT, size:B, morphtype:M16C_MT_ROT, optype:vmi_ROL, flags:&flagsCZS},
    [M16C_IT_ROT_F2_W]           = {fmt:2, opcode:"rot.w", src:MODE_REGB, sreg:M16C_REG_R1H, dest:MODE_4BIT, size:W, morphtype:M16C_MT_ROT, optype:vmi_ROL, flags:&flagsCZS},
    [M16C_IT_RTS_F1]             = {fmt:1, opcode:"rts", morphtype:M16C_MT_RTS, },
    [M16C_IT_SBB_F1_B]           = {fmt:1, opcode:"sbb.b", dest:MODE_4BIT, size:B, src:MODE_IMM8, morphtype:M16C_MT_BINOP, optype:vmi_SBB, flags:&flagsC_CZSO},
    [M16C_IT_SBB_F1_W]           = {fmt:1, opcode:"sbb.w", dest:MODE_4BIT, size:W, src:MODE_IMM16, morphtype:M16C_MT_BINOP, optype:vmi_SBB, flags:&flagsC_CZSO},
    [M16C_IT_SBB_F2_B]           = {fmt:2, opcode:"sbb.b", src:MODE_4BIT, dest:MODE_4BIT, size:B, morphtype:M16C_MT_BINOP, optype:vmi_SBB, flags:&flagsC_CZSO},
    [M16C_IT_SBB_F2_W]           = {fmt:2, opcode:"sbb.w", src:MODE_4BIT, dest:MODE_4BIT, size:W, morphtype:M16C_MT_BINOP, optype:vmi_SBB, flags:&flagsC_CZSO},
    [M16C_IT_SBJNZ_F1_B]         = {fmt:1, opcode:"sbjnz.b", src:MODE_IMM4, dest:MODE_4BIT, cons:LABEL8, size:B, morphtype:M16C_MT_SBJNZ, optype:vmi_SUB, },
    [M16C_IT_SBJNZ_F1_W]         = {fmt:1, opcode:"sbjnz.w", src:MODE_IMM4, dest:MODE_4BIT, cons:LABEL8, size:W, morphtype:M16C_MT_SBJNZ, optype:vmi_SUB, },
    [M16C_IT_SHA_F1_B]           = {fmt:1, opcode:"sha.b", src:MODE_IMM4_2, dest:MODE_4BIT, size:B, morphtype:M16C_MT_ROT, optype:vmi_SAR, flags:&flagsCZS},
    [M16C_IT_SHA_F1_W]           = {fmt:1, opcode:"sha.w", src:MODE_IMM4_2, dest:MODE_4BIT, size:W, morphtype:M16C_MT_ROT, optype:vmi_SAR, flags:&flagsCZS},
    [M16C_IT_SHA_F2_B]           = {fmt:2, opcode:"sha.b", src:MODE_REGB, sreg:M16C_REG_R1H, dest:MODE_4BIT, size:B, morphtype:M16C_MT_ROT, optype:vmi_SAR, flags:&flagsCZS},
    [M16C_IT_SHA_F2_W]           = {fmt:2, opcode:"sha.w", src:MODE_REGB, sreg:M16C_REG_R1H, dest:MODE_4BIT, size:W, morphtype:M16C_MT_ROT, optype:vmi_SAR, flags:&flagsCZS},
    [M16C_IT_SHA_F3_R2R0]        = {fmt:3, opcode:"sha", src:MODE_IMM4_2, dest:MODE_REG, dreg:M16C_REG_R2R0, size:L, morphtype:M16C_MT_ROT, optype:vmi_SAR, flags:&flagsS},
    [M16C_IT_SHA_F3_R3R1]        = {fmt:3, opcode:"sha", src:MODE_IMM4_2, dest:MODE_REG, dreg:M16C_REG_R3R1, size:L, morphtype:M16C_MT_ROT, optype:vmi_SAR, flags:&flagsS},
    [M16C_IT_SHA_F4_R2R0]        = {fmt:4, opcode:"sha", src:MODE_REGB, sreg:M16C_REG_R1H, dest:MODE_REG, dreg:M16C_REG_R2R0, size:L, morphtype:M16C_MT_ROT, optype:vmi_SAR, flags:&flagsS},
    [M16C_IT_SHA_F4_R3R1]        = {fmt:4, opcode:"sha", src:MODE_REGB, sreg:M16C_REG_R1H, dest:MODE_REG, dreg:M16C_REG_R3R1, size:L, morphtype:M16C_MT_ROT, optype:vmi_SAR, flags:&flagsS},
    [M16C_IT_SHL_F1_B]           = {fmt:1, opcode:"shl.b", src:MODE_IMM4_2, dest:MODE_4BIT, size:B, morphtype:M16C_MT_ROT, optype:vmi_SHL, flags:&flagsCZS},
    [M16C_IT_SHL_F1_W]           = {fmt:1, opcode:"shl.w", src:MODE_IMM4_2, dest:MODE_4BIT, size:W, morphtype:M16C_MT_ROT, optype:vmi_SHL, flags:&flagsCZS},
    [M16C_IT_SHL_F2_B]           = {fmt:2, opcode:"shl.b", src:MODE_REGB, sreg:M16C_REG_R1H, dest:MODE_4BIT, size:B, morphtype:M16C_MT_ROT, optype:vmi_SHL, flags:&flagsCZS},
    [M16C_IT_SHL_F2_W]           = {fmt:2, opcode:"shl.w", src:MODE_REGB, sreg:M16C_REG_R1H, dest:MODE_4BIT, size:W, morphtype:M16C_MT_ROT, optype:vmi_SHL, flags:&flagsCZS},
    [M16C_IT_SHL_F3_R2R0]        = {fmt:3, opcode:"shl", src:MODE_IMM4_2, dest:MODE_REG, dreg:M16C_REG_R2R0, size:L, morphtype:M16C_MT_ROT, optype:vmi_SHL, flags:&flagsS},
    [M16C_IT_SHL_F3_R3R1]        = {fmt:3, opcode:"shl", src:MODE_IMM4_2, dest:MODE_REG, dreg:M16C_REG_R3R1, size:L, morphtype:M16C_MT_ROT, optype:vmi_SHL, flags:&flagsS},
    [M16C_IT_SHL_F4_R2R0]        = {fmt:4, opcode:"shl", src:MODE_REGB, sreg:M16C_REG_R1H, dest:MODE_REG, dreg:M16C_REG_R2R0, size:L, morphtype:M16C_MT_ROT, optype:vmi_SHL, flags:&flagsS},
    [M16C_IT_SHL_F4_R3R1]        = {fmt:4, opcode:"shl", src:MODE_REGB, sreg:M16C_REG_R1H, dest:MODE_REG, dreg:M16C_REG_R3R1, size:L, morphtype:M16C_MT_ROT, optype:vmi_SHL, flags:&flagsS},
    [M16C_IT_SMOVB_F1_B]         = {fmt:1, opcode:"smovb.b", size:B, cons:CONST_N1, morphtype:M16C_MT_SMOV, },
    [M16C_IT_SMOVB_F1_W]         = {fmt:1, opcode:"smovb.w", size:W, cons:CONST_N2, morphtype:M16C_MT_SMOV, },
    [M16C_IT_SMOVF_F1_B]         = {fmt:1, opcode:"smovf.b", size:B, cons:CONST_P1, morphtype:M16C_MT_SMOV, },
    [M16C_IT_SMOVF_F1_W]         = {fmt:1, opcode:"smovf.w", size:W, cons:CONST_P2, morphtype:M16C_MT_SMOV, },
    [M16C_IT_SSTR_F1_B]          = {fmt:1, opcode:"sstr.b", size:B, morphtype:M16C_MT_SSTR, },
    [M16C_IT_SSTR_F1_W]          = {fmt:1, opcode:"sstr.w", size:W, morphtype:M16C_MT_SSTR, },
    [M16C_IT_STCTX_F1]           = {fmt:1, opcode:"stctx", morphtype:M16C_MT_STCTX, },
    [M16C_IT_STC_F1_FB]          = {fmt:1, opcode:"stc", dest:MODE_4BIT, src:MODE_REG, sreg:M16C_REG_FB, size:W, morphtype:M16C_MT_MOVE, flags:&flagsNONE},
    [M16C_IT_STC_F1_FLG]         = {fmt:1, opcode:"stc", dest:MODE_4BIT, src:MODE_REG, sreg:M16C_REG_FLG, size:W, morphtype:M16C_MT_MOVE, flags:&flagsNONE},
    [M16C_IT_STC_F1_INTBH]       = {fmt:1, opcode:"stc", dest:MODE_4BIT, src:MODE_REG, sreg:M16C_REG_INTBH, size:W, morphtype:M16C_MT_MOVE, flags:&flagsNONE},
    [M16C_IT_STC_F1_INTBL]       = {fmt:1, opcode:"stc", dest:MODE_4BIT, src:MODE_REG, sreg:M16C_REG_INTBL, size:W, morphtype:M16C_MT_MOVE, flags:&flagsNONE},
    [M16C_IT_STC_F1_ISP]         = {fmt:1, opcode:"stc", dest:MODE_4BIT, src:MODE_REG, sreg:M16C_REG_ISP, size:W, morphtype:M16C_MT_MOVE, flags:&flagsNONE},
    [M16C_IT_STC_F1_SB]          = {fmt:1, opcode:"stc", dest:MODE_4BIT, src:MODE_REG, sreg:M16C_REG_SB, size:W, morphtype:M16C_MT_MOVE, flags:&flagsNONE},
    [M16C_IT_STC_F1_SP]          = {fmt:1, opcode:"stc", dest:MODE_4BIT, src:MODE_REG, sreg:M16C_REG_SP, size:W, morphtype:M16C_MT_MOVE, flags:&flagsNONE},
    [M16C_IT_STC_F2]             = {fmt:2, opcode:"stc", size:A, src:MODE_REG, dest:MODE_4BIT, morphtype:M16C_MT_MOVE, flags:&flagsNONE},
    [M16C_IT_STE_F1_B]           = {fmt:1, opcode:"ste.b", src:MODE_4BIT, dest:MODE_ABS20, size:B, morphtype:M16C_MT_MOVE, },
    [M16C_IT_STE_F1_W]           = {fmt:1, opcode:"ste.w", src:MODE_4BIT, dest:MODE_ABS20, size:W, morphtype:M16C_MT_MOVE, },
    [M16C_IT_STE_F2_B]           = {fmt:2, opcode:"ste.b", src:MODE_4BIT, dest:MODE_DSP20, dreg:M16C_REG_A0, size:B, morphtype:M16C_MT_MOVE, },
    [M16C_IT_STE_F2_W]           = {fmt:2, opcode:"ste.w", src:MODE_4BIT, dest:MODE_DSP20, dreg:M16C_REG_A0, size:W, morphtype:M16C_MT_MOVE, },
    [M16C_IT_STE_F3_B]           = {fmt:3, opcode:"ste.b", src:MODE_4BIT, dest:MODE_ADDRI, dreg:M16C_REG_A1A0, size:B, morphtype:M16C_MT_MOVE, },
    [M16C_IT_STE_F3_W]           = {fmt:3, opcode:"ste.w", src:MODE_4BIT, dest:MODE_ADDRI, dreg:M16C_REG_A1A0, size:W, morphtype:M16C_MT_MOVE, },
    [M16C_IT_STNZ_F1_ABS]        = {fmt:1, opcode:"stnz", size:B, src:MODE_IMM8, dest:MODE_ABS16, cond:NE, morphtype:M16C_MT_MOVEC, },
    [M16C_IT_STNZ_F1_FB]         = {fmt:1, opcode:"stnz", size:B, src:MODE_IMM8, dest:MODE_DSP8, dreg:M16C_REG_FB, cond:NE, morphtype:M16C_MT_MOVEC, },
    [M16C_IT_STNZ_F1_R0H]        = {fmt:1, opcode:"stnz", size:B, src:MODE_IMM8, dest:MODE_REG, dreg:M16C_REG_R0H, cond:NE, morphtype:M16C_MT_MOVEC, },
    [M16C_IT_STNZ_F1_R0L]        = {fmt:1, opcode:"stnz", size:B, src:MODE_IMM8, dest:MODE_REG, dreg:M16C_REG_R0L, cond:NE, morphtype:M16C_MT_MOVEC, },
    [M16C_IT_STNZ_F1_SB]         = {fmt:1, opcode:"stnz", size:B, src:MODE_IMM8, dest:MODE_DSP8, dreg:M16C_REG_SB, cond:NE, morphtype:M16C_MT_MOVEC, },
    [M16C_IT_STZX_F1_ABS]        = {fmt:1, opcode:"stzx", size:B, src:MODE_IMM8_2, dest:MODE_ABS16, morphtype:M16C_MT_STZX_O, },
    [M16C_IT_STZX_F1_FB]         = {fmt:1, opcode:"stzx", size:B, src:MODE_IMM8_2, dest:MODE_DSP8, dreg:M16C_REG_FB, morphtype:M16C_MT_STZX_O, },
    [M16C_IT_STZX_F1_R0H]        = {fmt:1, opcode:"stzx", size:B, src:MODE_IMM8_2, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_STZX_R, },
    [M16C_IT_STZX_F1_R0L]        = {fmt:1, opcode:"stzx", size:B, src:MODE_IMM8_2, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_STZX_R, },
    [M16C_IT_STZX_F1_SB]         = {fmt:1, opcode:"stzx", size:B, src:MODE_IMM8_2, dest:MODE_DSP8, dreg:M16C_REG_SB, morphtype:M16C_MT_STZX_O, },
    [M16C_IT_STZ_F1_ABS]         = {fmt:1, opcode:"stz", size:B, src:MODE_IMM8, dest:MODE_ABS16, cond:EQ, morphtype:M16C_MT_MOVEC, },
    [M16C_IT_STZ_F1_FB]          = {fmt:1, opcode:"stz", size:B, src:MODE_IMM8, dest:MODE_DSP8, dreg:M16C_REG_FB, cond:EQ, morphtype:M16C_MT_MOVEC, },
    [M16C_IT_STZ_F1_R0H]         = {fmt:1, opcode:"stz", size:B, src:MODE_IMM8, dest:MODE_REG, dreg:M16C_REG_R0H, cond:EQ, morphtype:M16C_MT_MOVEC, },
    [M16C_IT_STZ_F1_R0L]         = {fmt:1, opcode:"stz", size:B, src:MODE_IMM8, dest:MODE_REG, dreg:M16C_REG_R0L, cond:EQ, morphtype:M16C_MT_MOVEC, },
    [M16C_IT_STZ_F1_SB]          = {fmt:1, opcode:"stz", size:B, src:MODE_IMM8, dest:MODE_DSP8, dreg:M16C_REG_SB, cond:EQ, morphtype:M16C_MT_MOVEC, },
    [M16C_IT_SUB_F1_B]           = {fmt:1, opcode:"sub.b:g", dest:MODE_4BIT, size:B, src:MODE_IMM8, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_SUB_F1_W]           = {fmt:1, opcode:"sub.w:g", dest:MODE_4BIT, size:W, src:MODE_IMM16, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_SUB_F2_ABS]         = {fmt:2, opcode:"sub.b:s", size:B, src:MODE_IMM8, dest:MODE_ABS16, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_SUB_F2_FB]          = {fmt:2, opcode:"sub.b:s", size:B, src:MODE_IMM8, dest:MODE_DSP8, dreg:M16C_REG_FB, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_SUB_F2_R0H]         = {fmt:2, opcode:"sub.b:s", size:B, src:MODE_IMM8, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_SUB_F2_R0L]         = {fmt:2, opcode:"sub.b:s", size:B, src:MODE_IMM8, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_SUB_F2_SB]          = {fmt:2, opcode:"sub.b:s", size:B, src:MODE_IMM8, dest:MODE_DSP8, dreg:M16C_REG_SB, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_SUB_F3_B]           = {fmt:3, opcode:"sub.b:g", src:MODE_4BIT, dest:MODE_4BIT, size:B, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_SUB_F3_W]           = {fmt:3, opcode:"sub.w:g", src:MODE_4BIT, dest:MODE_4BIT, size:W, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_SUB_F4_ABS_R0H]     = {fmt:4, opcode:"sub.b:s", size:B, src:MODE_ABS16, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_SUB_F4_ABS_R0L]     = {fmt:4, opcode:"sub.b:s", size:B, src:MODE_ABS16, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_SUB_F4_FB_R0H]      = {fmt:4, opcode:"sub.b:s", size:B, src:MODE_DSP8, sreg:M16C_REG_FB, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_SUB_F4_FB_R0L]      = {fmt:4, opcode:"sub.b:s", size:B, src:MODE_DSP8, sreg:M16C_REG_FB, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_SUB_F4_R0H_R0L]     = {fmt:4, opcode:"sub.b:s", size:B, src:MODE_REG, sreg:M16C_REG_R0H, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_SUB_F4_R0L_R0H]     = {fmt:4, opcode:"sub.b:s", size:B, src:MODE_REG, sreg:M16C_REG_R0L, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_SUB_F4_SB_R0H]      = {fmt:4, opcode:"sub.b:s", size:B, src:MODE_DSP8, sreg:M16C_REG_SB, dest:MODE_REG, dreg:M16C_REG_R0H, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_SUB_F4_SB_R0L]      = {fmt:4, opcode:"sub.b:s", size:B, src:MODE_DSP8, sreg:M16C_REG_SB, dest:MODE_REG, dreg:M16C_REG_R0L, morphtype:M16C_MT_BINOP, optype:vmi_SUB, },
    [M16C_IT_TST_F1_B]           = {fmt:1, opcode:"tst.b", dest:MODE_4BIT, size:B, src:MODE_IMM8, morphtype:M16C_MT_BINOP, optype:vmi_AND, },
    [M16C_IT_TST_F1_W]           = {fmt:1, opcode:"tst.w", dest:MODE_4BIT, size:W, src:MODE_IMM16, morphtype:M16C_MT_BINOP, optype:vmi_AND, },
    [M16C_IT_TST_F2_B]           = {fmt:2, opcode:"tst.b", src:MODE_4BIT, dest:MODE_4BIT, size:B, morphtype:M16C_MT_BINOP, optype:vmi_AND, },
    [M16C_IT_TST_F2_W]           = {fmt:2, opcode:"tst.w", src:MODE_4BIT, dest:MODE_4BIT, size:W, morphtype:M16C_MT_BINOP, optype:vmi_AND, },
    [M16C_IT_UND_F1]             = {fmt:1, opcode:"und", morphtype:M16C_MT_UND, },
    [M16C_IT_WAIT_F1]            = {fmt:1, opcode:"wait", morphtype:M16C_MT_WAIT, },
    [M16C_IT_XCHG_F1_B_R0H]      = {fmt:1, opcode:"xchg.b", dest:MODE_4BIT, size:B, src:MODE_REG, sreg:M16C_REG_R0H, morphtype:M16C_MT_XCHG, },
    [M16C_IT_XCHG_F1_B_R0L]      = {fmt:1, opcode:"xchg.b", dest:MODE_4BIT, size:B, src:MODE_REG, sreg:M16C_REG_R0L, morphtype:M16C_MT_XCHG, },
    [M16C_IT_XCHG_F1_B_R1H]      = {fmt:1, opcode:"xchg.b", dest:MODE_4BIT, size:B, src:MODE_REG, sreg:M16C_REG_R1H, morphtype:M16C_MT_XCHG, },
    [M16C_IT_XCHG_F1_B_R1L]      = {fmt:1, opcode:"xchg.b", dest:MODE_4BIT, size:B, src:MODE_REG, sreg:M16C_REG_R1L, morphtype:M16C_MT_XCHG, },
    [M16C_IT_XCHG_F1_W_R0]       = {fmt:1, opcode:"xchg.w", dest:MODE_4BIT, size:W, src:MODE_REG, sreg:M16C_REG_R0, morphtype:M16C_MT_XCHG, },
    [M16C_IT_XCHG_F1_W_R1]       = {fmt:1, opcode:"xchg.w", dest:MODE_4BIT, size:W, src:MODE_REG, sreg:M16C_REG_R1, morphtype:M16C_MT_XCHG, },
    [M16C_IT_XCHG_F1_W_R2]       = {fmt:1, opcode:"xchg.w", dest:MODE_4BIT, size:W, src:MODE_REG, sreg:M16C_REG_R2, morphtype:M16C_MT_XCHG, },
    [M16C_IT_XCHG_F1_W_R3]       = {fmt:1, opcode:"xchg.w", dest:MODE_4BIT, size:W, src:MODE_REG, sreg:M16C_REG_R3, morphtype:M16C_MT_XCHG, },
    [M16C_IT_XOR_F1_B]           = {fmt:1, opcode:"xor.b", dest:MODE_4BIT, size:B, src:MODE_IMM8, morphtype:M16C_MT_BINOP, optype:vmi_XOR, },
    [M16C_IT_XOR_F1_W]           = {fmt:1, opcode:"xor.w", dest:MODE_4BIT, size:W, src:MODE_IMM16, morphtype:M16C_MT_BINOP, optype:vmi_XOR, },
    [M16C_IT_XOR_F2_B]           = {fmt:2, opcode:"xor.b", src:MODE_4BIT, dest:MODE_4BIT, size:B, morphtype:M16C_MT_BINOP, optype:vmi_XOR, },
    [M16C_IT_XOR_F2_W]           = {fmt:2, opcode:"xor.w", src:MODE_4BIT, dest:MODE_4BIT, size:W, morphtype:M16C_MT_BINOP, optype:vmi_XOR, },
    [M16C_IT_LAST]               = {"BOGUS"}
};


// Morph dispatch table does not use instruction type (M16C_IT_*) as index.  Instead, a base
// index is given as an attribute, and offset is calculated from source and destination addressing modes.
static m16cMorphType get_morph_index(opAttrsCP attrs, addrModeSpec src_mode, addrModeSpec dest_mode) {
    m16cMorphType index;

    index = attrs->morphtype;

    if (index < M16C_MT_BRK) {
        if (dest_mode == MODE_REGO && src_mode != MODE_NA) {
            index = index + 3;
        } else if (dest_mode == MODE_REGO && src_mode == MODE_NA) {
            index++;
        }

        if (src_mode == MODE_IMM) {
            index++;
        } else if (src_mode == MODE_REGO) {
            index = index + 2;
        }
    }
    return index;  // M16C_MT_NOP;
}


//
// Do simple decode of instruction
//
static m16cInstructionType getInstructionType8(
    m16cP   m16c,
    Uns32  instr
) {
    static vmidDecodeTableP decodeTable8;

    // create normal instruction decode table if required
    if (!decodeTable8) {
        decodeTable8 = createDecodeTable8();
    }

    // decode the instruction using normal decode table
    return vmidDecode(decodeTable8, instr);
}

static m16cInstructionType getInstructionType16(
    m16cP   m16c,
    Uns32  instr
) {
    static vmidDecodeTableP decodeTable16;

    // create normal instruction decode table if required
    if (!decodeTable16) {
        decodeTable16 = createDecodeTable16();
    }

    // decode the instruction using normal decode table
    return vmidDecode(decodeTable16, instr);
}


#define FETCH_20BITS(_PROC, _ADDR) (vmicxtFetch1Byte(_PROC, _ADDR) | (vmicxtFetch1Byte(_PROC, _ADDR+1) << 8) | ((vmicxtFetch1Byte(_PROC, _ADDR+2) << 16) & 0x0f0000))


//
// Decode the  instruction at the passed address. The 'info' structure is
// filled with details of the instruction.
//
static void decode(m16cP m16c, m16cInstructionInfoP info, Uns16 instr, Uns8 bytes) {
    vmiProcessorP processor = (vmiProcessorP) m16c;
    // decode the instruction using either 8 or 16 bit decode table
    if (bytes == 1)
        info->type = getInstructionType8(m16c, instr);
    else
        info->type = getInstructionType16(m16c, instr);

    // vmiPrintf(" decode(): type=%d\n",(int) info->type);
    // save instruction
    info->instruction = instr;

    // get instruction attributes based on type
    opAttrsCP attrs = &attrsArray[info->type];

    // specify the name for the opcode / fmt
    info->opcode = attrs->opcode;
    info->fmt = attrs->fmt;

    info->offsetS = 0;
    info->offsetD = 0;
    info->cons = 0;


    if (attrs->flags == 0)
        info->flags = &flagsCZSO;
    else
        info->flags = attrs->flags;

    info->sz = attrs->size;
    info->dir = attrs->dir;
    info->cond = attrs->cond;

     /*
      * M16C instructions can support multiple addressing modes, even with the same base opcode/format.
      * Any of these mode selection fields that are less than 4-bits have already been decoded in the above tables.
      *
      * Many instructions contain a 4-bit field to determine addressing mode for the
      * source and/or destination.  These need to be decoded to determine the length of the
      * instruction, and which constant values or registers to use.
      *
      */

    info->rs1 = attrs->sreg;  // Source register for some instructions is already determined in the attribs table
    info->rd1 = attrs->dreg;  // Destination register for some instructions is already determined in the attribs table

    addrModeSpec src_mode = attrs->src;  // Get source addressing mode or check if it still needs to be decoded (MODE_4BIT)
    addrModeSpec dest_mode = attrs->dest;  // Get dest addressing mode or check if it still needs to be decoded (MODE_4BIT)



    // Check if instruction supports multiple addressing modes that still need to be decoded.

    if (attrs->dest == MODE_4BIT && attrs->src == MODE_4BIT) {  // Both src and dest fields, src is bits 7-4 and dest is it 3-0
        ADDR_MODE_LOOKUP(src_mode, info->rs1, ((instr & 0x00f0) >> 4));  // Get mode and register used, all modes except ABS make use of a reg
        ADDR_MODE_LOOKUP(dest_mode, info->rd1, (instr & 0x000f));  // Get mode and register used, all modes except ABS make use of a reg
    } else if (attrs->src == MODE_4BIT) {  // No Dest field, src address mode is last 4 bits of 16-bit instruction
        ADDR_MODE_LOOKUP(src_mode, info->rs1, (instr & 0x000f));  // Get mode and register used, all modes except ABS make use of a reg
    } else if (attrs->dest == MODE_4BIT) {  // Dest field is always last 4 bits of 16-bit instruction
        ADDR_MODE_LOOKUP(dest_mode, info->rd1, (instr & 0x000f));  // Get mode and register used, all modes except ABS make use of a reg
    }

    if (attrs->src == MODE_ZERO) {
        info->imm = 0;
        src_mode = MODE_IMM;
    }


    /* Byte order:
     *
     * Instruction widths are not fixed, and vary depending on which instruction and also which addressing
     * modes are selected.  Check sequenctially, as they do follow a predetermined order with only a couple
     * variations.
     *
     * IMM4  (in opcode bytes)
     * IMM8_1  (2nd byte when 8-bit opcode)
     * src:DSP8
     * src:DSP16
     * src:ABS16
     * dest:DSP8
     * dest:DSP16
     * dest:ABS16
     * IMM8
     * IMM8_2  (some 8-bit opcode instructions have an immediate value before and after the dest)
     * CND8
     * IMM16
     * DSP20
     * ABS20
     * LABEL8
     * ABS16+ABS20   LDCTX/STCTX
     * LDINTB (6 additional bytes)
    */

    // Check for 4-bit immediate field in byte 2 (opcode)
    if (src_mode == MODE_IMM4) {  // TODO: value is -8 to 7, should be sign extended
        if (attrs->dest == MODE_4BIT) {
            info->imm = imm4_lookup[(instr & 0x000000f0) >> 4];
        } else {
            info->imm = imm4_lookup[instr & 0x0000000f];
        }
        src_mode = MODE_IMM;
    } else if (src_mode == MODE_IMM4_2) {  // TODO: value is -8 to 8 (no zero), should be sign extended
        if (attrs->dest == MODE_4BIT) {
            info->imm = imm4_2_lookup[(instr & 0x000000f0) >> 4];
        } else {
            info->imm = imm4_2_lookup[instr & 0x0000000f];
        }
        src_mode = MODE_IMM;
    } else if (src_mode == MODE_IMM6) {
        info->imm = instr & 0x000003f;
        // src_mode = MODE_NA;
    } else if (src_mode == MODE_IMM_1) {
        info->imm = 1;
        src_mode = MODE_IMM;
    } else if (src_mode == MODE_ZERO) {
        info->imm = 0;
        src_mode = MODE_IMM;
    }
    // 8-bit opcode instructions can have constant (IMM8) as 2nd byte before src/dest  ADD_F3,AND_F2,CMP_F3,MOV_F3,OR_F2,STNZ,STZ,STZX,SUB_F2
    if ((bytes == 1) && ((src_mode == MODE_IMM8) || (src_mode == MODE_IMM8_1) || (src_mode == MODE_IMM8_2))) {
        info->imm = vmicxtFetch1Byte(processor, info->thisPC+bytes) & 0x00FF;
        bytes++;
        if (src_mode == MODE_IMM8_1 || src_mode == MODE_IMM8) {
            src_mode = MODE_IMM;
        }
    // Check 8/16 bit source modes next
    } else if (src_mode == MODE_DSP8 && (info->type != M16C_IT_MOV_F10_W && info->type != M16C_IT_MOV_F10_B)) {
        info->offsetS = /*(Int32) */((Int8)vmicxtFetch1Byte(processor, info->thisPC+bytes));
        bytes++;
        src_mode = MODE_REGO;
    } else if ((src_mode == MODE_ABS16)) {
        info->offsetS = vmicxtFetch2Byte(processor, info->thisPC+bytes);
        bytes = bytes + 2;
        src_mode = MODE_REGO;
        info->rs1 = M16C_REG_NONE;
    } else if ((src_mode == MODE_DSP16)) {
        info->offsetS = (Int16) vmicxtFetch2Byte(processor, info->thisPC+bytes);
        bytes = bytes + 2;
        src_mode = MODE_REGO;
    }

    // Check 8/16 bit destination modes next
    if (dest_mode == MODE_DSP8) {
        info->offsetD = (Int8) vmicxtFetch1Byte(processor, info->thisPC+bytes);
        bytes++;
        dest_mode = MODE_REGO;
    } else if ((dest_mode == MODE_ABS16)) {
        info->offsetD = vmicxtFetch2Byte(processor, info->thisPC+bytes);
        bytes = bytes + 2;
        dest_mode = MODE_REGO;
        info->rd1 = M16C_REG_NONE;
    } else if ((dest_mode == MODE_DSP16)) {
        info->offsetD = (Int16) vmicxtFetch2Byte(processor, info->thisPC+bytes);
        bytes = bytes + 2;
        dest_mode = MODE_REGO;
    }

    // Check for Immediates
    if (src_mode == MODE_IMM8) {
        info->imm = (Uns8) vmicxtFetch1Byte(processor, info->thisPC+bytes);
        bytes++;
        src_mode = MODE_IMM;
    } else if ((src_mode == MODE_IMM16)) {
        info->imm = (Uns16) vmicxtFetch2Byte(processor, info->thisPC+bytes);
        bytes = bytes + 2;
        src_mode = MODE_IMM;
    // Check for 20bit fields.  20-bit values use 3 bytes of memory, but upper 4 bits are ignored.
    } else if (src_mode == MODE_DSP20) {
        info->offsetS = FETCH_20BITS(processor, info->thisPC + bytes);
        bytes = bytes + 3;
        src_mode = MODE_REGO;
    } else if (src_mode == MODE_ABS20) {
        info->offsetS = FETCH_20BITS(processor, info->thisPC + bytes);
        bytes = bytes + 3;
        src_mode = MODE_REGO;
        info->rs1 = M16C_REG_NONE;
    }

    if (dest_mode == MODE_DSP20) {
        info->offsetD = FETCH_20BITS(processor, info->thisPC + bytes);
        bytes = bytes + 3;
        dest_mode = MODE_REGO;
    } else if (dest_mode == MODE_ABS20) {
        info->offsetD = FETCH_20BITS(processor, info->thisPC + bytes);
        bytes = bytes + 3;
        dest_mode = MODE_REGO;
        info->rd1 = M16C_REG_NONE;
    }

    if (src_mode == MODE_DSP8) {  // For MOV_F10, src DSP8 is after DEST
        info->offsetS = (Int8) vmicxtFetch1Byte(processor, info->thisPC+bytes);
        bytes++;
        src_mode = MODE_REGO;
    }

    if (attrs->cons == LABEL8) {
        // info->cons = info->thisPC + 2 + (Int8) vmicxtFetch1Byte(processor, info->thisPC+bytes);
        // bytes++;
        // dest_mode = MODE_LABEL;
        info->offsetS = info->thisPC + bytes + (Int8) vmicxtFetch1Byte(processor, info->thisPC+bytes);
        bytes = bytes + 1;
        src_mode = MODE_REGO;
        info->rs1 = M16C_REG_NONE;
    } else if (attrs->cons == LABEL16) {
        // info->cons = info->thisPC + bytes + (Int16) vmicxtFetch2Byte(processor, info->thisPC+bytes);
        // bytes = bytes + 2;
        // dest_mode = MODE_LABEL;
        info->offsetS = info->thisPC + bytes + (Int16) vmicxtFetch2Byte(processor, info->thisPC+bytes);
        bytes = bytes + 2;
        src_mode = MODE_REGO;
        info->rs1 = M16C_REG_NONE;
    } else if (attrs->cons == LABEL20) {
        info->offsetS = FETCH_20BITS(processor, info->thisPC+bytes);
        bytes = bytes + 3;
        src_mode = MODE_REGO;
        info->rs1 = M16C_REG_NONE;

        // dest_mode = MODE_LABEL;
    } else if (attrs->cons == CONST_N1) {
        info->cons = -1;
    } else if (attrs->cons == CONST_N2) {
        info->cons = -2;
    } else if (attrs->cons == CONST_P1) {
        info->cons = 1;
    } else if (attrs->cons == CONST_P2) {
        info->cons = 2;
    }


    if (attrs->size == BIT && attrs->dest == MODE_4BIT && dest_mode == MODE_REG)
    {
        info->offsetD = vmicxtFetch1Byte(processor, info->thisPC+bytes);
        bytes++;
    }

    if (attrs->cons == CONST_COND8)
    {
        info->cons = vmicxtFetch1Byte(processor, info->thisPC+bytes);
        // info->cons = 0x01 << (info->cons);
        bytes++;
    }


    if (attrs->size == BIT && dest_mode == MODE_REG)
    {
        // info->cons = vmicxtFetch1Byte(processor, info->thisPC+bytes);
        // info->cons = 0x01 << (info->cons);
        // bytes++;
    }

    if (src_mode == MODE_IMM8_2)
    {
        info->cons = vmicxtFetch1Byte(processor, info->thisPC+bytes) & 0x00FF;
        bytes++;
        src_mode = MODE_IMM;
    }

     // Special case for STCTX and LDCTX instructions which contain both a ABS16 and a ABS20
     if (src_mode == MODE_ABS16_ABS20) {
        info->cons = vmicxtFetch2Byte(processor, info->thisPC+bytes);
        bytes = bytes + 2;
        info->imm = FETCH_20BITS(processor, info->thisPC + bytes);
        bytes = bytes + 3;
        bytes++;
     // Special case for instruction LDINTB, which is 8 bytes long
     } else if (src_mode == MODE_LDINTB) {
        info->cons = vmicxtFetch4Byte(processor, info->thisPC+bytes);
        bytes = bytes + 4;
        info->cons = vmicxtFetch2Byte(processor, info->thisPC+bytes);
        bytes = bytes + 2;
     }

     if (src_mode >= MODE_C && src_mode <= MODE_U)
     {
        if (src_mode == MODE_C)
            info->imm = 0x01;
        else if (src_mode == MODE_D)
            info->imm = 0x02;
        else if (src_mode == MODE_Z)
            info->imm = 0x04;
        else if (src_mode == MODE_S)
            info->imm = 0x08;
        else if (src_mode == MODE_B)
            info->imm = 0x10;
        else if (src_mode == MODE_O)
            info->imm = 0x20;
        else if (src_mode == MODE_I)
            info->imm = 0x40;
        else if (src_mode == MODE_U)
            info->imm = 0x80;
        src_mode = MODE_IMM;
    }

     // All bytes of instruction should be read, decode any remaining fields in the instruction.

     info->srcMode = src_mode;
     info->destMode = dest_mode;



    // Calculate branch PC
    if (src_mode == MODE_REGO) {
        if (info->rs1 == M16C_REG_NONE) {  // Absolute Addressing
            info->branchPC = (info->offsetS) & M16C_ADDRESS_MASK;
        } else {
            info->branchPC = (info->thisPC + bytes + info->offsetS) & M16C_ADDRESS_MASK;
        }
    }

    info->morphindex = get_morph_index(attrs, src_mode, dest_mode);

    info->optype = attrs->optype;

    info->bytes = bytes;
}


//
// Decode the m16c instruction at the passed address.
//
void m16cDecode(m16cP m16c, Uns32 thisPC, m16cInstructionInfoP info) {
    // get instruction opcode as 1byte and possibly 2byte
    vmiProcessorP processor = (vmiProcessorP)m16c;
    Uns8          instr8   = vmicxtFetch1Byte(processor, thisPC);
    Uns16         instr16;
    Uns8          num_bytes;

    // record current PC in decoded structure
    info->thisPC = thisPC;

    // determine whether this is a 8-bit OR 16-bit opcode
    if (getInstructionType8(m16c, instr8) != M16C_IT_LAST) {
           instr16 = instr8;
           num_bytes = 1;
    } else {
        instr16 = (Uns16)vmicxtFetch1Byte(processor, thisPC+1) | (instr8<<8);
        // vmiPrintf(" not 8-bit try 16-bit '0x'%04x'\n", instr16);
        if (getInstructionType16(m16c, instr16) != M16C_IT_LAST) {
            num_bytes = 2;
        } else {
        //  VMI_ABORT("%s: UNDEF condition unknown instruction 0x%08x:%04x",
        //        FUNC_NAME, thisPC, instr16);
            num_bytes = 0;
        }
    }
    info->bytes = num_bytes;
    decode(m16c, info, instr16, num_bytes);
}
