/*
 * Copyright (c)      2016 eSOL TRINITY, www.esol-trinity.co.jp
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
#include "vmi/vmiTypes.h"
#include "vmi/vmiRt.h"            // vmirtExit
#include <string.h>                // memset

// model header files
#include "rl78Decode.h"
#include "rl78Structure.h"
#include "rl78Message.h"        // MY_ASSERT




//
// This macro adds a decode table entry for a specific instruction class
//
#define DECODE_ENTRY(_PRIORITY, _NAME, _FMT) \
    vmidNewEntryFmtBin(        \
        table,                \
        #_NAME,                \
        RL78_IT_##_NAME,    \
        _FMT,                \
        _PRIORITY            \
    )

//
// Create the RL78 decode table
//
static vmidDecodeTableP createDecodeTable_1stmap(void) {

    // Allocate a new decode table object to decode instructions 'bits' wide ('bits'
    // is currently restricted to 8, 16 or 32 only)
    // vmidDecodeTableP vmidNewDecodeTable(Uns32 bits, Uns32 defaultValue);
    vmidDecodeTableP table = vmidNewDecodeTable(32, RL78_IT_LAST);

    // The instruction format string, format, contains three kinds of characters:
    //   1. constrained characters (either '0' or '1') - the corresponding bit in the instruction
    //      must have the same value;
    //   2. spacer characters (any of '|', '/', comma, space or tab) - these are ignored and can
    //      be freely used to improve readability of the format string;
    //   3. don't care characters (any character not listed above) - these characters can be
    //      either 0 or 1 in the instruction and it will still match.

    DECODE_ENTRY(1, 1_00_NOP      ,  "|00000000 00000000 00000000 0000 0000|");    // 00
    DECODE_ENTRY(1, 1_02_ADDW     ,  "|00000000 00000000 00000000 0000 0010|");    // 02
    DECODE_ENTRY(1, 1_04_ADDW     ,  "|00000000 00000000 00000000 0000 0100|");    // 04
    DECODE_ENTRY(1, 1_06_ADDW     ,  "|00000000 00000000 00000000 0000 0110|");    // 06
    DECODE_ENTRY(0, 1_0X_ADDW     ,  "|00000000 00000000 00000000 0000 0..1|");    // 0.
    DECODE_ENTRY(1, 1_08_XCH      ,  "|00000000 00000000 00000000 0000 1000|");    // 08
    DECODE_ENTRY(1, 1_09_MOV      ,  "|00000000 00000000 00000000 0000 1001|");    // 09
    DECODE_ENTRY(1, 1_0A_ADD      ,  "|00000000 00000000 00000000 0000 1010|");    // 0A
    DECODE_ENTRY(1, 1_0B_ADD      ,  "|00000000 00000000 00000000 0000 1011|");    // 0B
    DECODE_ENTRY(1, 1_0C_ADD      ,  "|00000000 00000000 00000000 0000 1100|");    // 0C
    DECODE_ENTRY(1, 1_0D_ADD      ,  "|00000000 00000000 00000000 0000 1101|");    // 0D
    DECODE_ENTRY(1, 1_0E_ADD      ,  "|00000000 00000000 00000000 0000 1110|");    // 0E
    DECODE_ENTRY(1, 1_0F_ADD      ,  "|00000000 00000000 00000000 0000 1111|");    // 0F
    DECODE_ENTRY(1, 1_10_ADDW     ,  "|00000000 00000000 00000000 0001 0000|");    // 10
    DECODE_ENTRY(1, 1_11_PREFIX   ,  "|00000000 00000000 00000000 0001 0001|");    // 11
    DECODE_ENTRY(0, 1_1X_MOVW     ,  "|00000000 00000000 00000000 0001 0..0|");    // 1.
    DECODE_ENTRY(0, 1_1Y_MOVW     ,  "|00000000 00000000 00000000 0001 0..1|");    // 1.
    DECODE_ENTRY(1, 1_18_MOV      ,  "|00000000 00000000 00000000 0001 1000|");    // 18
    DECODE_ENTRY(1, 1_19_MOV      ,  "|00000000 00000000 00000000 0001 1001|");    // 19
    DECODE_ENTRY(1, 1_1A_ADDC     ,  "|00000000 00000000 00000000 0001 1010|");    // 1A
    DECODE_ENTRY(1, 1_1B_ADDC     ,  "|00000000 00000000 00000000 0001 1011|");    // 1B
    DECODE_ENTRY(1, 1_1C_ADDC     ,  "|00000000 00000000 00000000 0001 1100|");    // 1C
    DECODE_ENTRY(1, 1_1D_ADDC     ,  "|00000000 00000000 00000000 0001 1101|");    // 1D
    DECODE_ENTRY(1, 1_1E_ADDC     ,  "|00000000 00000000 00000000 0001 1110|");    // 1E
    DECODE_ENTRY(1, 1_1F_ADDC     ,  "|00000000 00000000 00000000 0001 1111|");    // 1F
    DECODE_ENTRY(1, 1_20_SUBW     ,  "|00000000 00000000 00000000 0010 0000|");    // 20
    DECODE_ENTRY(1, 1_22_SUBW     ,  "|00000000 00000000 00000000 0010 0010|");    // 22
    DECODE_ENTRY(1, 1_24_SUBW     ,  "|00000000 00000000 00000000 0010 0100|");    // 24
    DECODE_ENTRY(1, 1_26_SUBW     ,  "|00000000 00000000 00000000 0010 0110|");    // 26
    DECODE_ENTRY(0, 1_2X_SUBW     ,  "|00000000 00000000 00000000 0010 0..1|");    // 2.
    DECODE_ENTRY(1, 1_28_MOV      ,  "|00000000 00000000 00000000 0010 1000|");    // 28
    DECODE_ENTRY(1, 1_29_MOV      ,  "|00000000 00000000 00000000 0010 1001|");    // 29
    DECODE_ENTRY(1, 1_2A_SUB      ,  "|00000000 00000000 00000000 0010 1010|");    // 2A
    DECODE_ENTRY(1, 1_2B_SUB      ,  "|00000000 00000000 00000000 0010 1011|");    // 2B
    DECODE_ENTRY(1, 1_2C_SUB      ,  "|00000000 00000000 00000000 0010 1100|");    // 2C
    DECODE_ENTRY(1, 1_2D_SUB      ,  "|00000000 00000000 00000000 0010 1101|");    // 2D
    DECODE_ENTRY(1, 1_2E_SUB      ,  "|00000000 00000000 00000000 0010 1110|");    // 2E
    DECODE_ENTRY(1, 1_2F_SUB      ,  "|00000000 00000000 00000000 0010 1111|");    // 2F
    DECODE_ENTRY(1, 1_31_4thmap   ,  "|00000000 00000000 00000000 0011 0001|");    // 31        // 4th map
    DECODE_ENTRY(0, 1_3X_XCHW     ,  "|00000000 00000000 00000000 0011 0..1|");    // 3.
    DECODE_ENTRY(0, 1_3Y_MOVW     ,  "|00000000 00000000 00000000 0011 0..0|");    // 3.
    DECODE_ENTRY(1, 1_38_MOV      ,  "|00000000 00000000 00000000 0011 1000|");    // 38
    DECODE_ENTRY(1, 1_39_MOV      ,  "|00000000 00000000 00000000 0011 1001|");    // 39
    DECODE_ENTRY(1, 1_3A_SUBC     ,  "|00000000 00000000 00000000 0011 1010|");    // 3A
    DECODE_ENTRY(1, 1_3B_SUBC     ,  "|00000000 00000000 00000000 0011 1011|");    // 3B
    DECODE_ENTRY(1, 1_3C_SUBC     ,  "|00000000 00000000 00000000 0011 1100|");    // 3C
    DECODE_ENTRY(1, 1_3D_SUBC     ,  "|00000000 00000000 00000000 0011 1101|");    // 3D
    DECODE_ENTRY(1, 1_3E_SUBC     ,  "|00000000 00000000 00000000 0011 1110|");    // 3E
    DECODE_ENTRY(1, 1_3F_SUBC     ,  "|00000000 00000000 00000000 0011 1111|");    // 3F
    DECODE_ENTRY(1, 1_40_CMP      ,  "|00000000 00000000 00000000 0100 0000|");    // 40
    DECODE_ENTRY(1, 1_41_MOV      ,  "|00000000 00000000 00000000 0100 0001|");    // 41
    DECODE_ENTRY(1, 1_42_CMPW     ,  "|00000000 00000000 00000000 0100 0010|");    // 42
    DECODE_ENTRY(1, 1_44_CMPW     ,  "|00000000 00000000 00000000 0100 0100|");    // 44
    DECODE_ENTRY(1, 1_46_CMPW     ,  "|00000000 00000000 00000000 0100 0110|");    // 46
    DECODE_ENTRY(0, 1_4X_CMPW     ,  "|00000000 00000000 00000000 0100 0..1|");    // 4.
    DECODE_ENTRY(1, 1_48_MOV      ,  "|00000000 00000000 00000000 0100 1000|");    // 48
    DECODE_ENTRY(1, 1_49_MOV      ,  "|00000000 00000000 00000000 0100 1001|");    // 49
    DECODE_ENTRY(1, 1_4A_CMP      ,  "|00000000 00000000 00000000 0100 1010|");    // 4A
    DECODE_ENTRY(1, 1_4B_CMP      ,  "|00000000 00000000 00000000 0100 1011|");    // 4B
    DECODE_ENTRY(1, 1_4C_CMP      ,  "|00000000 00000000 00000000 0100 1100|");    // 4C
    DECODE_ENTRY(1, 1_4D_CMP      ,  "|00000000 00000000 00000000 0100 1101|");    // 4D
    DECODE_ENTRY(1, 1_4E_CMP      ,  "|00000000 00000000 00000000 0100 1110|");    // 4E
    DECODE_ENTRY(1, 1_4F_CMP      ,  "|00000000 00000000 00000000 0100 1111|");    // 4F
    DECODE_ENTRY(0, 1_5X_MOV      ,  "|00000000 00000000 00000000 0101 0...|");    // 5.
    DECODE_ENTRY(1, 1_58_MOVW     ,  "|00000000 00000000 00000000 0101 1000|");    // 58
    DECODE_ENTRY(1, 1_59_MOVW     ,  "|00000000 00000000 00000000 0101 1001|");    // 59
    DECODE_ENTRY(1, 1_5A_AND      ,  "|00000000 00000000 00000000 0101 1010|");    // 5A
    DECODE_ENTRY(1, 1_5B_AND      ,  "|00000000 00000000 00000000 0101 1011|");    // 5B
    DECODE_ENTRY(1, 1_5C_AND      ,  "|00000000 00000000 00000000 0101 1100|");    // 5C
    DECODE_ENTRY(1, 1_5D_AND      ,  "|00000000 00000000 00000000 0101 1101|");    // 5D
    DECODE_ENTRY(1, 1_5E_AND      ,  "|00000000 00000000 00000000 0101 1110|");    // 5E
    DECODE_ENTRY(1, 1_5F_AND      ,  "|00000000 00000000 00000000 0101 1111|");    // 5F
    DECODE_ENTRY(1, 1_61_2ndmap   ,  "|00000000 00000000 00000000 0110 0001|");    // 61        // 2nd map
    DECODE_ENTRY(0, 1_6X_MOV      ,  "|00000000 00000000 00000000 0110 0...|");    // 6.
    DECODE_ENTRY(1, 1_68_MOVW     ,  "|00000000 00000000 00000000 0110 1000|");    // 68
    DECODE_ENTRY(1, 1_69_MOVW     ,  "|00000000 00000000 00000000 0110 1001|");    // 69
    DECODE_ENTRY(1, 1_6A_OR       ,  "|00000000 00000000 00000000 0110 1010|");    // 6A
    DECODE_ENTRY(1, 1_6B_OR       ,  "|00000000 00000000 00000000 0110 1011|");    // 6B
    DECODE_ENTRY(1, 1_6C_OR       ,  "|00000000 00000000 00000000 0110 1100|");    // 6C
    DECODE_ENTRY(1, 1_6D_OR       ,  "|00000000 00000000 00000000 0110 1101|");    // 6D
    DECODE_ENTRY(1, 1_6E_OR       ,  "|00000000 00000000 00000000 0110 1110|");    // 6E
    DECODE_ENTRY(1, 1_6F_OR       ,  "|00000000 00000000 00000000 0110 1111|");    // 6F
    DECODE_ENTRY(1, 1_71_3rdmap   ,  "|00000000 00000000 00000000 0111 0001|");    // 71        // 3rd map
    DECODE_ENTRY(0, 1_7X_MOV      ,  "|00000000 00000000 00000000 0111 0...|");    // 7.
    DECODE_ENTRY(1, 1_78_MOVW     ,  "|00000000 00000000 00000000 0111 1000|");    // 78
    DECODE_ENTRY(1, 1_79_MOVW     ,  "|00000000 00000000 00000000 0111 1001|");    // 79
    DECODE_ENTRY(1, 1_7A_XOR      ,  "|00000000 00000000 00000000 0111 1010|");    // 7A
    DECODE_ENTRY(1, 1_7B_XOR      ,  "|00000000 00000000 00000000 0111 1011|");    // 7B
    DECODE_ENTRY(1, 1_7C_XOR      ,  "|00000000 00000000 00000000 0111 1100|");    // 7C
    DECODE_ENTRY(1, 1_7D_XOR      ,  "|00000000 00000000 00000000 0111 1101|");    // 7D
    DECODE_ENTRY(1, 1_7E_XOR      ,  "|00000000 00000000 00000000 0111 1110|");    // 7E
    DECODE_ENTRY(1, 1_7F_XOR      ,  "|00000000 00000000 00000000 0111 1111|");    // 7F
    DECODE_ENTRY(0, 1_8X_INC      ,  "|00000000 00000000 00000000 1000 0...|");    // 8.
    DECODE_ENTRY(1, 1_88_MOV      ,  "|00000000 00000000 00000000 1000 1000|");    // 88
    DECODE_ENTRY(1, 1_89_MOV      ,  "|00000000 00000000 00000000 1000 1001|");    // 89
    DECODE_ENTRY(1, 1_8A_MOV      ,  "|00000000 00000000 00000000 1000 1010|");    // 8A
    DECODE_ENTRY(1, 1_8B_MOV      ,  "|00000000 00000000 00000000 1000 1011|");    // 8B
    DECODE_ENTRY(1, 1_8C_MOV      ,  "|00000000 00000000 00000000 1000 1100|");    // 8C
    DECODE_ENTRY(1, 1_8D_MOV      ,  "|00000000 00000000 00000000 1000 1101|");    // 8D
    DECODE_ENTRY(1, 1_8E_MOV      ,  "|00000000 00000000 00000000 1000 1110|");    // 8E
    DECODE_ENTRY(1, 1_8F_MOV      ,  "|00000000 00000000 00000000 1000 1111|");    // 8F
    DECODE_ENTRY(0, 1_9X_DEC      ,  "|00000000 00000000 00000000 1001 0...|");    // 9.
    DECODE_ENTRY(1, 1_98_MOV      ,  "|00000000 00000000 00000000 1001 1000|");    // 98
    DECODE_ENTRY(1, 1_99_MOV      ,  "|00000000 00000000 00000000 1001 1001|");    // 99
    DECODE_ENTRY(1, 1_9A_MOV      ,  "|00000000 00000000 00000000 1001 1010|");    // 9A
    DECODE_ENTRY(1, 1_9B_MOV      ,  "|00000000 00000000 00000000 1001 1011|");    // 9B
    DECODE_ENTRY(1, 1_9C_MOV      ,  "|00000000 00000000 00000000 1001 1100|");    // 9C
    DECODE_ENTRY(1, 1_9D_MOV      ,  "|00000000 00000000 00000000 1001 1101|");    // 9D
    DECODE_ENTRY(1, 1_9E_MOV      ,  "|00000000 00000000 00000000 1001 1110|");    // 9E
    DECODE_ENTRY(1, 1_9F_MOV      ,  "|00000000 00000000 00000000 1001 1111|");    // 9F
    DECODE_ENTRY(1, 1_A0_INC      ,  "|00000000 00000000 00000000 1010 0000|");    // A0
    DECODE_ENTRY(1, 1_A2_INCW     ,  "|00000000 00000000 00000000 1010 0010|");    // A2
    DECODE_ENTRY(1, 1_A4_INC      ,  "|00000000 00000000 00000000 1010 0100|");    // A4
    DECODE_ENTRY(1, 1_A6_INCW     ,  "|00000000 00000000 00000000 1010 0110|");    // A6
    DECODE_ENTRY(0, 1_AX_INCW     ,  "|00000000 00000000 00000000 1010 0..1|");    // A.
    DECODE_ENTRY(1, 1_A8_MOVW     ,  "|00000000 00000000 00000000 1010 1000|");    // A8
    DECODE_ENTRY(1, 1_A9_MOVW     ,  "|00000000 00000000 00000000 1010 1001|");    // A9
    DECODE_ENTRY(1, 1_AA_MOVW     ,  "|00000000 00000000 00000000 1010 1010|");    // AA
    DECODE_ENTRY(1, 1_AB_MOVW     ,  "|00000000 00000000 00000000 1010 1011|");    // AB
    DECODE_ENTRY(1, 1_AC_MOVW     ,  "|00000000 00000000 00000000 1010 1100|");    // AC
    DECODE_ENTRY(1, 1_AD_MOVW     ,  "|00000000 00000000 00000000 1010 1101|");    // AD
    DECODE_ENTRY(1, 1_AE_MOVW     ,  "|00000000 00000000 00000000 1010 1110|");    // AE
    DECODE_ENTRY(1, 1_AF_MOVW     ,  "|00000000 00000000 00000000 1010 1111|");    // AF
    DECODE_ENTRY(1, 1_B0_DEC      ,  "|00000000 00000000 00000000 1011 0000|");    // B0
    DECODE_ENTRY(1, 1_B2_DECW     ,  "|00000000 00000000 00000000 1011 0010|");    // B2
    DECODE_ENTRY(1, 1_B4_DEC      ,  "|00000000 00000000 00000000 1011 0100|");    // B4
    DECODE_ENTRY(1, 1_B6_DECW     ,  "|00000000 00000000 00000000 1011 0110|");    // B6
    DECODE_ENTRY(0, 1_BX_DECW     ,  "|00000000 00000000 00000000 1011 0..1|");    // B.
    DECODE_ENTRY(1, 1_B8_MOVW     ,  "|00000000 00000000 00000000 1011 1000|");    // B8
    DECODE_ENTRY(1, 1_B9_MOVW     ,  "|00000000 00000000 00000000 1011 1001|");    // B9
    DECODE_ENTRY(1, 1_BA_MOVW     ,  "|00000000 00000000 00000000 1011 1010|");    // BA
    DECODE_ENTRY(1, 1_BB_MOVW     ,  "|00000000 00000000 00000000 1011 1011|");    // BB
    DECODE_ENTRY(1, 1_BC_MOVW     ,  "|00000000 00000000 00000000 1011 1100|");    // BC
    DECODE_ENTRY(1, 1_BD_MOVW     ,  "|00000000 00000000 00000000 1011 1101|");    // BD
    DECODE_ENTRY(1, 1_BE_MOVW     ,  "|00000000 00000000 00000000 1011 1110|");    // BE
    DECODE_ENTRY(1, 1_BF_MOVW     ,  "|00000000 00000000 00000000 1011 1111|");    // BF
    DECODE_ENTRY(0, 1_CX_POP      ,  "|00000000 00000000 00000000 1100 0..0|");    // C.
    DECODE_ENTRY(0, 1_CY_PUSH     ,  "|00000000 00000000 00000000 1100 0..1|");    // C.
    DECODE_ENTRY(1, 1_C8_MOV      ,  "|00000000 00000000 00000000 1100 1000|");    // C8
    DECODE_ENTRY(1, 1_C9_MOVW     ,  "|00000000 00000000 00000000 1100 1001|");    // C9
    DECODE_ENTRY(1, 1_CA_MOV      ,  "|00000000 00000000 00000000 1100 1010|");    // CA
    DECODE_ENTRY(1, 1_CB_MOVW     ,  "|00000000 00000000 00000000 1100 1011|");    // CB
    DECODE_ENTRY(1, 1_CC_MOV      ,  "|00000000 00000000 00000000 1100 1100|");    // CC
    DECODE_ENTRY(1, 1_CD_MOV      ,  "|00000000 00000000 00000000 1100 1101|");    // CD
    DECODE_ENTRY(1, 1_CE_MOV_SFR  ,  "|00000000 00000000 00000000 1100 1110|");    // CE
    //                1_CE_MOV_PSW
    //                1_CE_MOV_CS
    DECODE_ENTRY(1, 1_CF_MOV      ,  "|00000000 00000000 00000000 1100 1111|");    // CF
    DECODE_ENTRY(0, 1_DX_CMP0     ,  "|00000000 00000000 00000000 1101 00..|");    // D.
    DECODE_ENTRY(1, 1_D4_CMP0     ,  "|00000000 00000000 00000000 1101 0100|");    // D4
    DECODE_ENTRY(1, 1_D5_CMP0     ,  "|00000000 00000000 00000000 1101 0101|");    // D5
    DECODE_ENTRY(1, 1_D6_MULU     ,  "|00000000 00000000 00000000 1101 0110|");    // D6
    DECODE_ENTRY(1, 1_D7_RET      ,  "|00000000 00000000 00000000 1101 0111|");    // D7
    DECODE_ENTRY(1, 1_D8_MOV      ,  "|00000000 00000000 00000000 1101 1000|");    // D8
    DECODE_ENTRY(1, 1_D9_MOV      ,  "|00000000 00000000 00000000 1101 1001|");    // D9
    DECODE_ENTRY(1, 1_DC_BC       ,  "|00000000 00000000 00000000 1101 1100|");    // DC
    DECODE_ENTRY(1, 1_DD_BZ       ,  "|00000000 00000000 00000000 1101 1101|");    // DD
    DECODE_ENTRY(1, 1_DE_BNC      ,  "|00000000 00000000 00000000 1101 1110|");    // DE
    DECODE_ENTRY(1, 1_DF_BNZ      ,  "|00000000 00000000 00000000 1101 1111|");    // DF
    DECODE_ENTRY(0, 1_EX_ONEB     ,  "|00000000 00000000 00000000 1110 00..|");    // E.
    DECODE_ENTRY(1, 1_E4_ONEB     ,  "|00000000 00000000 00000000 1110 0100|");    // E4
    DECODE_ENTRY(1, 1_E5_ONEB     ,  "|00000000 00000000 00000000 1110 0101|");    // E5
    DECODE_ENTRY(1, 1_E6_ONEW     ,  "|00000000 00000000 00000000 1110 0110|");    // E6
    DECODE_ENTRY(1, 1_E7_ONEW     ,  "|00000000 00000000 00000000 1110 0111|");    // E7
    DECODE_ENTRY(1, 1_E8_MOV      ,  "|00000000 00000000 00000000 1110 1000|");    // E8
    DECODE_ENTRY(1, 1_E9_MOV      ,  "|00000000 00000000 00000000 1110 1001|");    // E9
    DECODE_ENTRY(1, 1_EC_BR       ,  "|00000000 00000000 00000000 1110 1100|");    // EC
    DECODE_ENTRY(1, 1_ED_BR       ,  "|00000000 00000000 00000000 1110 1101|");    // ED
    DECODE_ENTRY(1, 1_EE_BR       ,  "|00000000 00000000 00000000 1110 1110|");    // EE
    DECODE_ENTRY(1, 1_EF_BR       ,  "|00000000 00000000 00000000 1110 1111|");    // EF
    DECODE_ENTRY(0, 1_FX_CLRB     ,  "|00000000 00000000 00000000 1111 00..|");    // F.
    DECODE_ENTRY(1, 1_F4_CLRB     ,  "|00000000 00000000 00000000 1111 0100|");    // F4
    DECODE_ENTRY(1, 1_F5_CLRB     ,  "|00000000 00000000 00000000 1111 0101|");    // F5
    DECODE_ENTRY(1, 1_F6_CLRW     ,  "|00000000 00000000 00000000 1111 0110|");    // F6
    DECODE_ENTRY(1, 1_F7_CLRW     ,  "|00000000 00000000 00000000 1111 0111|");    // F7
    DECODE_ENTRY(1, 1_F8_MOV      ,  "|00000000 00000000 00000000 1111 1000|");    // F8
    DECODE_ENTRY(1, 1_F9_MOV      ,  "|00000000 00000000 00000000 1111 1001|");    // F9
    DECODE_ENTRY(1, 1_FC_CALL     ,  "|00000000 00000000 00000000 1111 1100|");    // FC
    DECODE_ENTRY(1, 1_FD_CALL     ,  "|00000000 00000000 00000000 1111 1101|");    // FD
    DECODE_ENTRY(1, 1_FE_CALL     ,  "|00000000 00000000 00000000 1111 1110|");    // FE
    DECODE_ENTRY(0, 1_XA_MOVW     ,  "|00000000 00000000 00000000 11.. 1010|");    // .A
    DECODE_ENTRY(0, 1_XB_MOVW     ,  "|00000000 00000000 00000000 11.. 1011|");    // .B

    return table;
}

static vmidDecodeTableP createDecodeTable_2ndmap(void) {
    vmidDecodeTableP table = vmidNewDecodeTable(32, RL78_IT_LAST);

    DECODE_ENTRY(0, 2_0X_ADD      ,  "|00000000 00000000 00000000 0000 0...|");    // 61 0.
    DECODE_ENTRY(1, 2_09_ADDW     ,  "|00000000 00000000 00000000 0000 1001|");    // 61 09
    DECODE_ENTRY(0, 2_0Y_ADD      ,  "|00000000 00000000 00000000 0000 1...|");    // 61 0.
    DECODE_ENTRY(0, 2_1X_ADDC     ,  "|00000000 00000000 00000000 0001 0...|");    // 61 1.
    DECODE_ENTRY(0, 2_1Y_ADDC     ,  "|00000000 00000000 00000000 0001 1...|");    // 61 1.
    DECODE_ENTRY(0, 2_2X_SUB      ,  "|00000000 00000000 00000000 0010 0...|");    // 61 2.
    DECODE_ENTRY(1, 2_29_SUBW     ,  "|00000000 00000000 00000000 0010 1001|");    // 61 29
    DECODE_ENTRY(0, 2_2Y_SUB      ,  "|00000000 00000000 00000000 0010 1...|");    // 61 2.
    DECODE_ENTRY(0, 2_3X_SUBC     ,  "|00000000 00000000 00000000 0011 0...|");    // 61 3.
    DECODE_ENTRY(0, 2_3Y_SUBC     ,  "|00000000 00000000 00000000 0011 1...|");    // 61 3.
    DECODE_ENTRY(0, 2_4X_CMP      ,  "|00000000 00000000 00000000 0100 0...|");    // 61 4.
    DECODE_ENTRY(1, 2_49_CMPW     ,  "|00000000 00000000 00000000 0100 1001|");    // 61 49
    DECODE_ENTRY(0, 2_4Y_CMP      ,  "|00000000 00000000 00000000 0100 1...|");    // 61 4.
    DECODE_ENTRY(0, 2_5X_AND      ,  "|00000000 00000000 00000000 0101 0...|");    // 61 5.
    DECODE_ENTRY(1, 2_59_INC      ,  "|00000000 00000000 00000000 0101 1001|");    // 61 59
    DECODE_ENTRY(0, 2_5Y_AND      ,  "|00000000 00000000 00000000 0101 1...|");    // 61 5.
    DECODE_ENTRY(0, 2_6X_OR       ,  "|00000000 00000000 00000000 0110 0...|");    // 61 6.
    DECODE_ENTRY(1, 2_69_DEC      ,  "|00000000 00000000 00000000 0110 1001|");    // 61 69
    DECODE_ENTRY(0, 2_6Y_OR       ,  "|00000000 00000000 00000000 0110 1...|");    // 61 6.
    DECODE_ENTRY(0, 2_7X_XOR      ,  "|00000000 00000000 00000000 0111 0...|");    // 61 7.
    DECODE_ENTRY(1, 2_79_INCW     ,  "|00000000 00000000 00000000 0111 1001|");    // 61 79
    DECODE_ENTRY(0, 2_7Y_XOR      ,  "|00000000 00000000 00000000 0111 1...|");    // 61 7.
    DECODE_ENTRY(1, 2_80_ADD      ,  "|00000000 00000000 00000000 1000 0000|");    // 61 80
    DECODE_ENTRY(1, 2_82_ADD      ,  "|00000000 00000000 00000000 1000 0010|");    // 61 82
    DECODE_ENTRY(1, 2_89_DECW     ,  "|00000000 00000000 00000000 1000 1001|");    // 61 89
    DECODE_ENTRY(0, 2_8X_XCH      ,  "|00000000 00000000 00000000 1000 1...|");    // 61 8.
    DECODE_ENTRY(1, 2_90_ADDC     ,  "|00000000 00000000 00000000 1001 0000|");    // 61 90
    DECODE_ENTRY(1, 2_92_ADDC     ,  "|00000000 00000000 00000000 1001 0010|");    // 61 92
    DECODE_ENTRY(1, 2_A0_SUB      ,  "|00000000 00000000 00000000 1010 0000|");    // 61 A0
    DECODE_ENTRY(1, 2_A2_SUB      ,  "|00000000 00000000 00000000 1010 0010|");    // 61 A2
    DECODE_ENTRY(1, 2_A8_XCH      ,  "|00000000 00000000 00000000 1010 1000|");    // 61 A8
    DECODE_ENTRY(1, 2_A9_XCH      ,  "|00000000 00000000 00000000 1010 1001|");    // 61 A9
    DECODE_ENTRY(1, 2_AA_XCH      ,  "|00000000 00000000 00000000 1010 1010|");    // 61 AA
    DECODE_ENTRY(1, 2_AB_XCH      ,  "|00000000 00000000 00000000 1010 1011|");    // 61 AB
    DECODE_ENTRY(1, 2_AC_XCH      ,  "|00000000 00000000 00000000 1010 1100|");    // 61 AC
    DECODE_ENTRY(1, 2_AD_XCH      ,  "|00000000 00000000 00000000 1010 1101|");    // 61 AD
    DECODE_ENTRY(1, 2_AE_XCH      ,  "|00000000 00000000 00000000 1010 1110|");    // 61 AE
    DECODE_ENTRY(1, 2_AF_XCH      ,  "|00000000 00000000 00000000 1010 1111|");    // 61 AF
    DECODE_ENTRY(1, 2_B0_SUBC     ,  "|00000000 00000000 00000000 1011 0000|");    // 61 B0
    DECODE_ENTRY(1, 2_B2_SUBC     ,  "|00000000 00000000 00000000 1011 0010|");    // 61 B2
    DECODE_ENTRY(1, 2_B8_MOV      ,  "|00000000 00000000 00000000 1011 1000|");    // 61 B8
    DECODE_ENTRY(1, 2_B9_XCH      ,  "|00000000 00000000 00000000 1011 1001|");    // 61 B9
    DECODE_ENTRY(1, 2_C0_CMP      ,  "|00000000 00000000 00000000 1100 0000|");    // 61 C0
    DECODE_ENTRY(1, 2_C2_CMP      ,  "|00000000 00000000 00000000 1100 0010|");    // 61 C2
    DECODE_ENTRY(1, 2_C3_BH       ,  "|00000000 00000000 00000000 1100 0011|");    // 61 C3
    DECODE_ENTRY(1, 2_C8_SKC      ,  "|00000000 00000000 00000000 1100 1000|");    // 61 C8
    DECODE_ENTRY(1, 2_C9_MOV      ,  "|00000000 00000000 00000000 1100 1001|");    // 61 C9
    DECODE_ENTRY(1, 2_CB_BR       ,  "|00000000 00000000 00000000 1100 1011|");    // 61 CB
    DECODE_ENTRY(1, 2_CC_BRK      ,  "|00000000 00000000 00000000 1100 1100|");    // 61 CC
    DECODE_ENTRY(1, 2_CD_POP      ,  "|00000000 00000000 00000000 1100 1101|");    // 61 CD
    DECODE_ENTRY(1, 2_CE_MOVS     ,  "|00000000 00000000 00000000 1100 1110|");    // 61 CE
    DECODE_ENTRY(1, 2_D0_AND      ,  "|00000000 00000000 00000000 1101 0000|");    // 61 D0
    DECODE_ENTRY(1, 2_D2_AND      ,  "|00000000 00000000 00000000 1101 0010|");    // 61 D2
    DECODE_ENTRY(1, 2_D3_BNH      ,  "|00000000 00000000 00000000 1101 0011|");    // 61 D3
    DECODE_ENTRY(1, 2_D8_SKNC     ,  "|00000000 00000000 00000000 1101 1000|");    // 61 D8
    DECODE_ENTRY(1, 2_D9_MOV      ,  "|00000000 00000000 00000000 1101 1001|");    // 61 D9
    DECODE_ENTRY(1, 2_DB_ROR      ,  "|00000000 00000000 00000000 1101 1011|");    // 61 DB
    DECODE_ENTRY(1, 2_DC_ROLC     ,  "|00000000 00000000 00000000 1101 1100|");    // 61 DC
    DECODE_ENTRY(1, 2_DD_PUSH     ,  "|00000000 00000000 00000000 1101 1101|");    // 61 DD
    DECODE_ENTRY(1, 2_DE_CMPS     ,  "|00000000 00000000 00000000 1101 1110|");    // 61 DE
    DECODE_ENTRY(1, 2_E0_OR       ,  "|00000000 00000000 00000000 1110 0000|");    // 61 E0
    DECODE_ENTRY(1, 2_E2_OR       ,  "|00000000 00000000 00000000 1110 0010|");    // 61 E2
    DECODE_ENTRY(1, 2_E3_SKH      ,  "|00000000 00000000 00000000 1110 0011|");    // 61 E3
    DECODE_ENTRY(1, 2_E8_SKZ      ,  "|00000000 00000000 00000000 1110 1000|");    // 61 E8
    DECODE_ENTRY(1, 2_E9_MOV      ,  "|00000000 00000000 00000000 1110 1001|");    // 61 E9
    DECODE_ENTRY(1, 2_EB_ROL      ,  "|00000000 00000000 00000000 1110 1011|");    // 61 EB
    DECODE_ENTRY(1, 2_EC_RETB     ,  "|00000000 00000000 00000000 1110 1100|");    // 61 EC
    DECODE_ENTRY(1, 2_ED_HALT     ,  "|00000000 00000000 00000000 1110 1101|");    // 61 ED
    DECODE_ENTRY(1, 2_F0_XOR      ,  "|00000000 00000000 00000000 1111 0000|");    // 61 F0
    DECODE_ENTRY(1, 2_F2_XOR      ,  "|00000000 00000000 00000000 1111 0010|");    // 61 F2
    DECODE_ENTRY(1, 2_F3_SKNH     ,  "|00000000 00000000 00000000 1111 0011|");    // 61 F3
    DECODE_ENTRY(1, 2_F8_SKNZ     ,  "|00000000 00000000 00000000 1111 1000|");    // 61 F8
    DECODE_ENTRY(1, 2_F9_MOV      ,  "|00000000 00000000 00000000 1111 1001|");    // 61 F9
    DECODE_ENTRY(1, 2_FB_RORC     ,  "|00000000 00000000 00000000 1111 1011|");    // 61 FB
    DECODE_ENTRY(1, 2_FC_RETI     ,  "|00000000 00000000 00000000 1111 1100|");    // 61 FC
    DECODE_ENTRY(1, 2_FD_STOP     ,  "|00000000 00000000 00000000 1111 1101|");    // 61 FD
    DECODE_ENTRY(0, 2_XE_ROLWC    ,  "|00000000 00000000 00000000 111. 1110|");    // 61 .E
    DECODE_ENTRY(0, 2_XF_SEL      ,  "|00000000 00000000 00000000 11.. 1111|");    // 61 .F
    DECODE_ENTRY(0, 2_XA_CALL     ,  "|00000000 00000000 00000000 11.. 1010|");    // 61 .A
    DECODE_ENTRY(0, 2_XX_CALLT    ,  "|00000000 00000000 00000000 1... 01..|");    // 61 ..

    return table;
}

static vmidDecodeTableP createDecodeTable_3rdmap(void) {
    vmidDecodeTableP table = vmidNewDecodeTable(32, RL78_IT_LAST);

    DECODE_ENTRY(0, 3_X0_SET1     ,  "|00000000 00000000 00000000 0... 0000|");    // 71 .0
    DECODE_ENTRY(0, 3_X1_MOV1     ,  "|00000000 00000000 00000000 0... 0001|");    // 71 .1
    DECODE_ENTRY(0, 3_X2_SET1     ,  "|00000000 00000000 00000000 0... 0010|");    // 71 .2
    DECODE_ENTRY(0, 3_X3_CLR1     ,  "|00000000 00000000 00000000 0... 0011|");    // 71 .3
    DECODE_ENTRY(0, 3_X4_MOV1     ,  "|00000000 00000000 00000000 0... 0100|");    // 71 .4
    DECODE_ENTRY(0, 3_X5_AND1     ,  "|00000000 00000000 00000000 0... 0101|");    // 71 .5
    DECODE_ENTRY(0, 3_X6_OR1      ,  "|00000000 00000000 00000000 0... 0110|");    // 71 .6
    DECODE_ENTRY(0, 3_X7_XOR1     ,  "|00000000 00000000 00000000 0... 0111|");    // 71 .7
    DECODE_ENTRY(0, 3_X8_CLR1     ,  "|00000000 00000000 00000000 0... 1000|");    // 71 .8
    DECODE_ENTRY(0, 3_X9_MOV1     ,  "|00000000 00000000 00000000 0... 1001|");    // 71 .9
    DECODE_ENTRY(0, 3_XA_SET1     ,  "|00000000 00000000 00000000 0... 1010|");    // 71 .A
    DECODE_ENTRY(0, 3_XB_CLR1     ,  "|00000000 00000000 00000000 0... 1011|");    // 71 .B
    DECODE_ENTRY(0, 3_XC_MOV1     ,  "|00000000 00000000 00000000 0... 1100|");    // 71 .C
    DECODE_ENTRY(0, 3_XD_AND1     ,  "|00000000 00000000 00000000 0... 1101|");    // 71 .D
    DECODE_ENTRY(0, 3_XE_OR1      ,  "|00000000 00000000 00000000 0... 1110|");    // 71 .E
    DECODE_ENTRY(0, 3_XF_XOR1     ,  "|00000000 00000000 00000000 0... 1111|");    // 71 .F
    DECODE_ENTRY(1, 3_80_SET1     ,  "|00000000 00000000 00000000 1000 0000|");    // 71 80
    DECODE_ENTRY(1, 3_88_CLR1     ,  "|00000000 00000000 00000000 1000 1000|");    // 71 88
    DECODE_ENTRY(1, 3_C0_NOT1     ,  "|00000000 00000000 00000000 1100 0000|");    // 71 C0
    DECODE_ENTRY(0, 3_Y1_MOV1     ,  "|00000000 00000000 00000000 1... 0001|");    // 71 .1
    DECODE_ENTRY(0, 3_Y2_SET1     ,  "|00000000 00000000 00000000 1... 0010|");    // 71 .2
    DECODE_ENTRY(0, 3_Y3_CLR1     ,  "|00000000 00000000 00000000 1... 0011|");    // 71 .3
    DECODE_ENTRY(0, 3_Y4_MOV1     ,  "|00000000 00000000 00000000 1... 0100|");    // 71 .4
    DECODE_ENTRY(0, 3_Y5_AND1     ,  "|00000000 00000000 00000000 1... 0101|");    // 71 .5
    DECODE_ENTRY(0, 3_Y6_OR1      ,  "|00000000 00000000 00000000 1... 0110|");    // 71 .6
    DECODE_ENTRY(0, 3_Y7_XOR1     ,  "|00000000 00000000 00000000 1... 0111|");    // 71 .7
    DECODE_ENTRY(0, 3_Y9_MOV1     ,  "|00000000 00000000 00000000 1... 1001|");    // 71 .9
    DECODE_ENTRY(0, 3_YA_SET1     ,  "|00000000 00000000 00000000 1... 1010|");    // 71 .A
    DECODE_ENTRY(0, 3_YB_CLR1     ,  "|00000000 00000000 00000000 1... 1011|");    // 71 .B
    DECODE_ENTRY(0, 3_YC_MOV1     ,  "|00000000 00000000 00000000 1... 1100|");    // 71 .C
    DECODE_ENTRY(0, 3_YD_AND1     ,  "|00000000 00000000 00000000 1... 1101|");    // 71 .D
    DECODE_ENTRY(0, 3_YE_OR1      ,  "|00000000 00000000 00000000 1... 1110|");    // 71 .E
    DECODE_ENTRY(0, 3_YF_XOR1     ,  "|00000000 00000000 00000000 1... 1111|");    // 71 .F

    return table;
}

static vmidDecodeTableP createDecodeTable_4thmap(void) {
    vmidDecodeTableP table = vmidNewDecodeTable(32, RL78_IT_LAST);

    DECODE_ENTRY(0, 4_X0_BTCLR    ,  "|00000000 00000000 00000000 0... 0000|");    // 31 .0
    DECODE_ENTRY(0, 4_X1_BTCLR    ,  "|00000000 00000000 00000000 0... 0001|");    // 31 .1
    DECODE_ENTRY(0, 4_X2_BT       ,  "|00000000 00000000 00000000 0... 0010|");    // 31 .2
    DECODE_ENTRY(0, 4_X3_BT       ,  "|00000000 00000000 00000000 0... 0011|");    // 31 .3
    DECODE_ENTRY(0, 4_X4_BF       ,  "|00000000 00000000 00000000 0... 0100|");    // 31 .4
    DECODE_ENTRY(0, 4_X5_BF       ,  "|00000000 00000000 00000000 0... 0101|");    // 31 .5
    DECODE_ENTRY(0, 4_X7_SHL      ,  "|00000000 00000000 00000000 0... 0111|");    // 31 .7
    DECODE_ENTRY(0, 4_X8_SHL      ,  "|00000000 00000000 00000000 0... 1000|");    // 31 .8
    DECODE_ENTRY(0, 4_X9_SHL      ,  "|00000000 00000000 00000000 0... 1001|");    // 31 .9
    DECODE_ENTRY(0, 4_XA_SHR      ,  "|00000000 00000000 00000000 0... 1010|");    // 31 .A
    DECODE_ENTRY(0, 4_XB_SAR      ,  "|00000000 00000000 00000000 0... 1011|");    // 31 .B
    DECODE_ENTRY(0, 4_Y0_BTCLR    ,  "|00000000 00000000 00000000 1... 0000|");    // 31 .0
    DECODE_ENTRY(0, 4_Y1_BTCLR    ,  "|00000000 00000000 00000000 1... 0001|");    // 31 .1
    DECODE_ENTRY(0, 4_Y2_BT       ,  "|00000000 00000000 00000000 1... 0010|");    // 31 .2
    DECODE_ENTRY(0, 4_Y3_BT       ,  "|00000000 00000000 00000000 1... 0011|");    // 31 .3
    DECODE_ENTRY(0, 4_Y4_BF       ,  "|00000000 00000000 00000000 1... 0100|");    // 31 .4
    DECODE_ENTRY(0, 4_Y5_BF       ,  "|00000000 00000000 00000000 1... 0101|");    // 31 .5
    DECODE_ENTRY(0, 4_XC_SHLW     ,  "|00000000 00000000 00000000 .... 1100|");    // 31 .C
    DECODE_ENTRY(0, 4_XD_SHLW     ,  "|00000000 00000000 00000000 .... 1101|");    // 31 .D
    DECODE_ENTRY(0, 4_XE_SHRW     ,  "|00000000 00000000 00000000 .... 1110|");    // 31 .E
    DECODE_ENTRY(0, 4_XF_SARW     ,  "|00000000 00000000 00000000 .... 1111|");    // 31 .F

    return table;
}

Uns32 ary_num_operand_fetch[RL78_IT_LAST][2] = {
    [RL78_IT_1_00_NOP      ] = { 0 , 0 },        // NOP
    [RL78_IT_1_02_ADDW     ] = { 0 , 2 },        // ADDW    AX, !addr16
    [RL78_IT_1_04_ADDW     ] = { 0 , 2 },        // ADDW    AX, #word
    [RL78_IT_1_06_ADDW     ] = { 0 , 1 },        // ADDW    AX, saddrp
    [RL78_IT_1_0X_ADDW     ] = { 0 , 0 },        // ADDW    AX, ??
    [RL78_IT_1_08_XCH      ] = { 0 , 0 },        // XCH     A, X
    [RL78_IT_1_09_MOV      ] = { 0 , 2 },        // MOV     A, word[B]
    [RL78_IT_1_0A_ADD      ] = { 1 , 1 },        // ADD     saddr, #byte
    [RL78_IT_1_0B_ADD      ] = { 0 , 1 },        // ADD     A, saddr
    [RL78_IT_1_0C_ADD      ] = { 0 , 1 },        // ADD     A, #byte
    [RL78_IT_1_0D_ADD      ] = { 0 , 0 },        // ADD     A, [HL]
    [RL78_IT_1_0E_ADD      ] = { 0 , 1 },        // ADD     A, [HL+byte]
    [RL78_IT_1_0F_ADD      ] = { 0 , 2 },        // ADD     A, !addr16
    [RL78_IT_1_10_ADDW     ] = { 0 , 1 },        // ADDW    SP, #byte
    [RL78_IT_1_11_PREFIX   ] = { 0 , 0 },        // PREFIX
    [RL78_IT_1_1X_MOVW     ] = { 0 , 0 },        // MOVW    ??, AX
    [RL78_IT_1_1Y_MOVW     ] = { 0 , 0 },        // MOVW    AX, ??
    [RL78_IT_1_18_MOV      ] = { 2 , 0 },        // MOV     word[B], A
    [RL78_IT_1_19_MOV      ] = { 2 , 1 },        // MOV     word[B], #byte
    [RL78_IT_1_1A_ADDC     ] = { 1 , 1 },        // ADDC    saddr, #byte
    [RL78_IT_1_1B_ADDC     ] = { 0 , 1 },        // ADDC    A, saddr
    [RL78_IT_1_1C_ADDC     ] = { 0 , 1 },        // ADDC    A, #byte
    [RL78_IT_1_1D_ADDC     ] = { 0 , 0 },        // ADDC    A, [HL]
    [RL78_IT_1_1E_ADDC     ] = { 0 , 1 },        // ADDC    A, [HL+byte]
    [RL78_IT_1_1F_ADDC     ] = { 0 , 2 },        // ADDC    A, !addr16
    [RL78_IT_1_20_SUBW     ] = { 0 , 1 },        // SUBW    SP, #byte
    [RL78_IT_1_22_SUBW     ] = { 0 , 2 },        // SUBW    AX, !addr16
    [RL78_IT_1_24_SUBW     ] = { 0 , 2 },        // SUBW    AX, #word
    [RL78_IT_1_26_SUBW     ] = { 0 , 1 },        // SUBW    AX, saddrp
    [RL78_IT_1_2X_SUBW     ] = { 0 , 0 },        // SUBW    AX, ??
    [RL78_IT_1_28_MOV      ] = { 2 , 0 },        // MOV     word[C] ,A
    [RL78_IT_1_29_MOV      ] = { 0 , 2 },        // MOV     A, word[C]
    [RL78_IT_1_2A_SUB      ] = { 1 , 1 },        // SUB     saddr, #byte
    [RL78_IT_1_2B_SUB      ] = { 0 , 1 },        // SUB     A, saddr
    [RL78_IT_1_2C_SUB      ] = { 0 , 1 },        // SUB     A, #byte
    [RL78_IT_1_2D_SUB      ] = { 0 , 0 },        // SUB     A, [HL]
    [RL78_IT_1_2E_SUB      ] = { 0 , 1 },        // SUB     A, [HL+byte]
    [RL78_IT_1_2F_SUB      ] = { 0 , 2 },        // SUB     A, !addr16
    [RL78_IT_1_31_4thmap   ] = { 0 , 0 },        // 4thmap
    [RL78_IT_1_3X_XCHW     ] = { 0 , 0 },        // XCHW    AX, ??
    [RL78_IT_1_3Y_MOVW     ] = { 0 , 2 },        // MOVW    ??, #word
    [RL78_IT_1_38_MOV      ] = { 2 , 1 },        // MOV     word[C], #byte
    [RL78_IT_1_39_MOV      ] = { 2 , 1 },        // MOV     word[BC], #byte
    [RL78_IT_1_3A_SUBC     ] = { 1 , 1 },        // SUBC    saddr, #byte            //d <- a - b - C
    [RL78_IT_1_3B_SUBC     ] = { 0 , 1 },        // SUBC    A, saddr
    [RL78_IT_1_3C_SUBC     ] = { 0 , 1 },        // SUBC    A, #byte
    [RL78_IT_1_3D_SUBC     ] = { 0 , 0 },        // SUBC    A, [HL]
    [RL78_IT_1_3E_SUBC     ] = { 0 , 1 },        // SUBC    A, [HL+byte]
    [RL78_IT_1_3F_SUBC     ] = { 0 , 2 },        // SUBC    A, !addr16
    [RL78_IT_1_40_CMP      ] = { 2 , 1 },        // CMP     !addr16, #byte
    [RL78_IT_1_41_MOV      ] = { 0 , 1 },        // MOV     ES, #byte
    [RL78_IT_1_42_CMPW     ] = { 0 , 2 },        // CMPW    AX, !addr16
    [RL78_IT_1_44_CMPW     ] = { 0 , 2 },        // CMPW    AX, #word
    [RL78_IT_1_46_CMPW     ] = { 0 , 1 },        // CMPW    AX, saddrp
    [RL78_IT_1_4X_CMPW     ] = { 0 , 0 },        // CMPW    AX, ??
    [RL78_IT_1_48_MOV      ] = { 2 , 0 },        // MOV     word[BC], A
    [RL78_IT_1_49_MOV      ] = { 0 , 2 },        // MOV     A, word[BC]
    [RL78_IT_1_4A_CMP      ] = { 1 , 1 },        // CMP     saddr, #byte
    [RL78_IT_1_4B_CMP      ] = { 0 , 1 },        // CMP     A, saddr
    [RL78_IT_1_4C_CMP      ] = { 0 , 1 },        // CMP     A, #byte
    [RL78_IT_1_4D_CMP      ] = { 0 , 0 },        // CMP     A, [HL]
    [RL78_IT_1_4E_CMP      ] = { 0 , 1 },        // CMP     A, [HL+byte]
    [RL78_IT_1_4F_CMP      ] = { 0 , 2 },        // CMP     A, !addr16
    [RL78_IT_1_5X_MOV      ] = { 0 , 1 },        // MOV     ?, #byte
    [RL78_IT_1_58_MOVW     ] = { 2 , 0 },        // MOVW    word[B], AX
    [RL78_IT_1_59_MOVW     ] = { 0 , 2 },        // MOVW    AX, word[B]
    [RL78_IT_1_5A_AND      ] = { 1 , 1 },        // AND     saddr, #byte
    [RL78_IT_1_5B_AND      ] = { 0 , 1 },        // AND     A, saddr
    [RL78_IT_1_5C_AND      ] = { 0 , 1 },        // AND     A, #byte
    [RL78_IT_1_5D_AND      ] = { 0 , 0 },        // AND     A, [HL]
    [RL78_IT_1_5E_AND      ] = { 0 , 1 },        // AND     A, [HL+byte]
    [RL78_IT_1_5F_AND      ] = { 0 , 2 },        // AND     A, !addr16
    [RL78_IT_1_61_2ndmap   ] = { 0 , 0 },        // 2ndmap
    [RL78_IT_1_6X_MOV      ] = { 0 , 0 },        // MOV     A, ?
    [RL78_IT_1_68_MOVW     ] = { 2 , 0 },        // MOVW    word[C], AX
    [RL78_IT_1_69_MOVW     ] = { 0 , 2 },        // MOVW    AX, word[C]
    [RL78_IT_1_6A_OR       ] = { 1 , 1 },        // OR      saddr, #byte
    [RL78_IT_1_6B_OR       ] = { 0 , 1 },        // OR      A, saddr
    [RL78_IT_1_6C_OR       ] = { 0 , 1 },        // OR      A, #byte
    [RL78_IT_1_6D_OR       ] = { 0 , 0 },        // OR      A, [HL]
    [RL78_IT_1_6E_OR       ] = { 0 , 1 },        // OR      A, [HL+byte]
    [RL78_IT_1_6F_OR       ] = { 0 , 2 },        // OR      A, !addr16
    [RL78_IT_1_71_3rdmap   ] = { 0 , 0 },        // 3rdmap
    [RL78_IT_1_7X_MOV      ] = { 0 , 0 },        // MOV     ?, A
    [RL78_IT_1_78_MOVW     ] = { 2 , 0 },        // MOVW    word[BC], AX
    [RL78_IT_1_79_MOVW     ] = { 0 , 2 },        // MOVW    AX, word[BC]
    [RL78_IT_1_7A_XOR      ] = { 1 , 1 },        // XOR     saddr, #byte
    [RL78_IT_1_7B_XOR      ] = { 0 , 1 },        // XOR     A, saddr
    [RL78_IT_1_7C_XOR      ] = { 0 , 1 },        // XOR     A, #byte
    [RL78_IT_1_7D_XOR      ] = { 0 , 0 },        // XOR     A, [HL]
    [RL78_IT_1_7E_XOR      ] = { 0 , 1 },        // XOR     A, [HL+byte]
    [RL78_IT_1_7F_XOR      ] = { 0 , 2 },        // XOR     A, !addr16
    [RL78_IT_1_8X_INC      ] = { 0 , 0 },        // INC     ?
    [RL78_IT_1_88_MOV      ] = { 0 , 1 },        // MOV     A, [SP+byte]
    [RL78_IT_1_89_MOV      ] = { 0 , 0 },        // MOV     A, [DE]
    [RL78_IT_1_8A_MOV      ] = { 0 , 1 },        // MOV     A, [DE+byte]
    [RL78_IT_1_8B_MOV      ] = { 0 , 0 },        // MOV     A, [HL]
    [RL78_IT_1_8C_MOV      ] = { 0 , 1 },        // MOV     A, [HL+byte]
    [RL78_IT_1_8D_MOV      ] = { 0 , 1 },        // MOV     A, saddr
    [RL78_IT_1_8E_MOV      ] = { 0 , 1 },        // MOV     A, sfr
    [RL78_IT_1_8F_MOV      ] = { 0 , 2 },        // MOV     A, !addr16
    [RL78_IT_1_9X_DEC      ] = { 0 , 0 },        // DEC     ?
    [RL78_IT_1_98_MOV      ] = { 1 , 0 },        // MOV     [SP+byte], A
    [RL78_IT_1_99_MOV      ] = { 0 , 0 },        // MOV     [DE], A
    [RL78_IT_1_9A_MOV      ] = { 1 , 0 },        // MOV     [DE+byte], A
    [RL78_IT_1_9B_MOV      ] = { 0 , 0 },        // MOV     [HL], A
    [RL78_IT_1_9C_MOV      ] = { 1 , 0 },        // MOV     [HL+byte], A
    [RL78_IT_1_9D_MOV      ] = { 1 , 0 },        // MOV     saddr, A
    [RL78_IT_1_9E_MOV      ] = { 1 , 0 },        // MOV     sfr, A
    [RL78_IT_1_9F_MOV      ] = { 2 , 0 },        // MOV     !addr16, A
    [RL78_IT_1_A0_INC      ] = { 2 , 0 },        // INC     !addr16
    [RL78_IT_1_A2_INCW     ] = { 2 , 0 },        // INCW    !addr16
    [RL78_IT_1_A4_INC      ] = { 1 , 0 },        // INC     saddr
    [RL78_IT_1_A6_INCW     ] = { 1 , 0 },        // INCW    saddrp
    [RL78_IT_1_AX_INCW     ] = { 0 , 0 },        // INCW    ??
    [RL78_IT_1_A8_MOVW     ] = { 0 , 1 },        // MOVW    AX, [SP+byte]
    [RL78_IT_1_A9_MOVW     ] = { 0 , 0 },        // MOVW    AX, [DE]
    [RL78_IT_1_AA_MOVW     ] = { 0 , 1 },        // MOVW    AX, [DE+byte]
    [RL78_IT_1_AB_MOVW     ] = { 0 , 0 },        // MOVW    AX, [HL]
    [RL78_IT_1_AC_MOVW     ] = { 0 , 1 },        // MOVW    AX, [HL+byte]
    [RL78_IT_1_AD_MOVW     ] = { 0 , 1 },        // MOVW    AX, saddrp
    [RL78_IT_1_AE_MOVW     ] = { 0 , 1 },        // MOVW    AX, sfrp
    [RL78_IT_1_AF_MOVW     ] = { 0 , 2 },        // MOVW    AX, !addr16
    [RL78_IT_1_B0_DEC      ] = { 2 , 0 },        // DEC     !addr16
    [RL78_IT_1_B2_DECW     ] = { 2 , 0 },        // DECW    !addr16
    [RL78_IT_1_B4_DEC      ] = { 1 , 0 },        // DEC     saddr
    [RL78_IT_1_B6_DECW     ] = { 1 , 0 },        // DECW    saddrp
    [RL78_IT_1_BX_DECW     ] = { 0 , 0 },        // DECW    ??
    [RL78_IT_1_B8_MOVW     ] = { 1 , 0 },        // MOVW    [SP+byte], AX
    [RL78_IT_1_B9_MOVW     ] = { 0 , 0 },        // MOVW    [DE], AX
    [RL78_IT_1_BA_MOVW     ] = { 1 , 0 },        // MOVW    [DE+byte], AX
    [RL78_IT_1_BB_MOVW     ] = { 0 , 0 },        // MOVW    [HL], AX
    [RL78_IT_1_BC_MOVW     ] = { 1 , 0 },        // MOVW    [HL+byte], AX
    [RL78_IT_1_BD_MOVW     ] = { 1 , 0 },        // MOVW    saddrp, AX
    [RL78_IT_1_BE_MOVW     ] = { 1 , 0 },        // MOVW    sfrp, AX
    [RL78_IT_1_BF_MOVW     ] = { 2 , 0 },        // MOVW    !addr16, AX
    [RL78_IT_1_CX_POP      ] = { 0 , 0 },        // POP     ??
    [RL78_IT_1_CY_PUSH     ] = { 0 , 0 },        // PUSH    ??
    [RL78_IT_1_C8_MOV      ] = { 1 , 1 },        // MOV     [SP+byte], #byte
    [RL78_IT_1_C9_MOVW     ] = { 1 , 2 },        // MOVW    saddrp, #word
    [RL78_IT_1_CA_MOV      ] = { 1 , 1 },        // MOV     [DE+byte], #byte
    [RL78_IT_1_CB_MOVW     ] = { 1 , 2 },        // MOVW    sfrp, #word
    [RL78_IT_1_CC_MOV      ] = { 1 , 1 },        // MOV     [HL+byte], #byte
    [RL78_IT_1_CD_MOV      ] = { 1 , 1 },        // MOV     saddr, #byte
    [RL78_IT_1_CE_MOV_SFR  ] = { 1 , 1 },        // MOV     sfr, #byte
    //       1_CE_MOV_PSW                        // MOV     PSW, #byte
    //       1_CE_MOV_CS                        // MOV     CS, #byte
    [RL78_IT_1_CF_MOV      ] = { 2 , 1 },        // MOV     !addr16, #byte
    [RL78_IT_1_DX_CMP0     ] = { 0 , 0 },        // CMP0    ?
    [RL78_IT_1_D4_CMP0     ] = { 1 , 0 },        // CMP0    saddr
    [RL78_IT_1_D5_CMP0     ] = { 2 , 0 },        // CMP0    !addr16
    [RL78_IT_1_D6_MULU     ] = { 0 , 0 },        // MULU    X
    [RL78_IT_1_D7_RET      ] = { 0 , 0 },        // RET
    [RL78_IT_1_D8_MOV      ] = { 0 , 1 },        // MOV     X, saddr
    [RL78_IT_1_D9_MOV      ] = { 0 , 2 },        // MOV     X, !addr16
    [RL78_IT_1_DC_BC       ] = { 1 , 0 },        // BC      $addr20
    [RL78_IT_1_DD_BZ       ] = { 1 , 0 },        // BZ      $addr20
    [RL78_IT_1_DE_BNC      ] = { 1 , 0 },        // BNC     $addr20
    [RL78_IT_1_DF_BNZ      ] = { 1 , 0 },        // BNZ     $addr20
    [RL78_IT_1_EX_ONEB     ] = { 0 , 0 },        // ONEB    ?
    [RL78_IT_1_E4_ONEB     ] = { 1 , 0 },        // ONEB    saddr
    [RL78_IT_1_E5_ONEB     ] = { 2 , 0 },        // ONEB    !addr16
    [RL78_IT_1_E6_ONEW     ] = { 0 , 0 },        // ONEW    AX
    [RL78_IT_1_E7_ONEW     ] = { 0 , 0 },        // ONEW    BC
    [RL78_IT_1_E8_MOV      ] = { 0 , 1 },        // MOV     B, saddr
    [RL78_IT_1_E9_MOV      ] = { 0 , 2 },        // MOV     B, !addr16
    [RL78_IT_1_EC_BR       ] = { 3 , 0 },        // BR      !!addr20
    [RL78_IT_1_ED_BR       ] = { 2 , 0 },        // BR      !addr16
    [RL78_IT_1_EE_BR       ] = { 2 , 0 },        // BR      $!addr20
    [RL78_IT_1_EF_BR       ] = { 1 , 0 },        // BR      $addr20
    [RL78_IT_1_FX_CLRB     ] = { 0 , 0 },        // CLRB    ?
    [RL78_IT_1_F4_CLRB     ] = { 1 , 0 },        // CLRB    saddr
    [RL78_IT_1_F5_CLRB     ] = { 2 , 0 },        // CLRB    !addr16
    [RL78_IT_1_F6_CLRW     ] = { 0 , 0 },        // CLRW    AX
    [RL78_IT_1_F7_CLRW     ] = { 0 , 0 },        // CLRW    BC
    [RL78_IT_1_F8_MOV      ] = { 0 , 1 },        // MOV     C, saddr
    [RL78_IT_1_F9_MOV      ] = { 0 , 2 },        // MOV     C, !addr16
    [RL78_IT_1_FC_CALL     ] = { 3 , 0 },        // CALL    !!addr20
    [RL78_IT_1_FD_CALL     ] = { 2 , 0 },        // CALL    !addr16
    [RL78_IT_1_FE_CALL     ] = { 2 , 0 },        // CALL    $!addr20
    [RL78_IT_1_XA_MOVW     ] = { 0 , 1 },        // MOVW    ??, saddrp
    [RL78_IT_1_XB_MOVW     ] = { 0 , 2 },        // MOVW    ??, !addr16

    [RL78_IT_2_0X_ADD      ] = { 0 , 0 },        // ADD     ?, A
    [RL78_IT_2_09_ADDW     ] = { 0 , 1 },        // ADDW    AX, [HL+byte]
    [RL78_IT_2_0Y_ADD      ] = { 0 , 0 },        // ADD     A, ?
    [RL78_IT_2_1X_ADDC     ] = { 0 , 0 },        // ADDC    ?, A
    [RL78_IT_2_1Y_ADDC     ] = { 0 , 0 },        // ADDC    A, ?
    [RL78_IT_2_2X_SUB      ] = { 0 , 0 },        // SUB     ?, A
    [RL78_IT_2_29_SUBW     ] = { 0 , 1 },        // SUBW    AX, [HL+byte]
    [RL78_IT_2_2Y_SUB      ] = { 0 , 0 },        // SUB     A, ?
    [RL78_IT_2_3X_SUBC     ] = { 0 , 0 },        // SUBC    ?, A
    [RL78_IT_2_3Y_SUBC     ] = { 0 , 0 },        // SUBC    A, ?
    [RL78_IT_2_4X_CMP      ] = { 0 , 0 },        // CMP     ?, A
    [RL78_IT_2_49_CMPW     ] = { 0 , 1 },        // CMPW    AX, [HL+byte]
    [RL78_IT_2_4Y_CMP      ] = { 0 , 0 },        // CMP     A, ?
    [RL78_IT_2_5X_AND      ] = { 0 , 0 },        // AND     ?, A
    [RL78_IT_2_59_INC      ] = { 1 , 0 },        // INC     [HL+byte]
    [RL78_IT_2_5Y_AND      ] = { 0 , 0 },        // AND     A, ?
    [RL78_IT_2_6X_OR       ] = { 0 , 0 },        // OR      ?, A
    [RL78_IT_2_69_DEC      ] = { 1 , 0 },        // DEC     [HL+byte]
    [RL78_IT_2_6Y_OR       ] = { 0 , 0 },        // OR      A, ?
    [RL78_IT_2_7X_XOR      ] = { 0 , 0 },        // XOR     ?, A
    [RL78_IT_2_79_INCW     ] = { 1 , 0 },        // INCW    [HL+byte]
    [RL78_IT_2_7Y_XOR      ] = { 0 , 0 },        // XOR     A, ?
    [RL78_IT_2_80_ADD      ] = { 0 , 0 },        // ADD     A, [HL+B]
    [RL78_IT_2_82_ADD      ] = { 0 , 0 },        // ADD     A, [HL+C]
    [RL78_IT_2_89_DECW     ] = { 1 , 0 },        // DECW    [HL+byte]
    [RL78_IT_2_8X_XCH      ] = { 0 , 0 },        // XCH     A, ?
    [RL78_IT_2_90_ADDC     ] = { 0 , 0 },        // ADDC    A, [HL+B]
    [RL78_IT_2_92_ADDC     ] = { 0 , 0 },        // ADDC    A, [HL+C]
    [RL78_IT_2_A0_SUB      ] = { 0 , 0 },        // SUB     A, [HL+B]
    [RL78_IT_2_A2_SUB      ] = { 0 , 0 },        // SUB     A, [HL+C]
    [RL78_IT_2_A8_XCH      ] = { 0 , 1 },        // XCH     A, saddr
    [RL78_IT_2_A9_XCH      ] = { 0 , 0 },        // XCH     A, [HL+C]
    [RL78_IT_2_AA_XCH      ] = { 0 , 2 },        // XCH     A, !addr16
    [RL78_IT_2_AB_XCH      ] = { 0 , 1 },        // XCH     A, sfr
    [RL78_IT_2_AC_XCH      ] = { 0 , 0 },        // XCH     A, [HL]
    [RL78_IT_2_AD_XCH      ] = { 0 , 1 },        // XCH     A, [HL+byte]
    [RL78_IT_2_AE_XCH      ] = { 0 , 0 },        // XCH     A, [DE]
    [RL78_IT_2_AF_XCH      ] = { 0 , 1 },        // XCH     A, [DE+byte]
    [RL78_IT_2_B0_SUBC     ] = { 0 , 0 },        // SUBC    A, [HL+B]
    [RL78_IT_2_B2_SUBC     ] = { 0 , 0 },        // SUBC    A, [HL+C]
    [RL78_IT_2_B8_MOV      ] = { 0 , 1 },        // MOV     ES, saddr
    [RL78_IT_2_B9_XCH      ] = { 0 , 0 },        // XCH     A, [HL+B]
    [RL78_IT_2_C0_CMP      ] = { 0 , 0 },        // CMP     A, [HL+B]
    [RL78_IT_2_C2_CMP      ] = { 0 , 0 },        // CMP     A, [HL+C]
    [RL78_IT_2_C3_BH       ] = { 1 , 0 },        // BH      $addr20
    [RL78_IT_2_C8_SKC      ] = { 0 , 0 },        // SKC
    [RL78_IT_2_C9_MOV      ] = { 0 , 0 },        // MOV     A, [HL+B]
    [RL78_IT_2_CB_BR       ] = { 0 , 0 },        // BR      AX
    [RL78_IT_2_CC_BRK      ] = { 0 , 0 },        // BRK
    [RL78_IT_2_CD_POP      ] = { 0 , 0 },        // POP     PSW
    [RL78_IT_2_CE_MOVS     ] = { 1 , 0 },        // MOVS    [HL+byte], X
    [RL78_IT_2_D0_AND      ] = { 0 , 0 },        // AND     A, [HL+B]
    [RL78_IT_2_D2_AND      ] = { 0 , 0 },        // AND     A, [HL+C]
    [RL78_IT_2_D3_BNH      ] = { 1 , 0 },        // BNH     $addr20
    [RL78_IT_2_D8_SKNC     ] = { 0 , 0 },        // SKNC
    [RL78_IT_2_D9_MOV      ] = { 0 , 0 },        // MOV     [HL+B], A
    [RL78_IT_2_DB_ROR      ] = { 0 , 0 },        // ROR     A, 1
    [RL78_IT_2_DC_ROLC     ] = { 0 , 0 },        // ROLC    A, 1
    [RL78_IT_2_DD_PUSH     ] = { 0 , 0 },        // PUSH    PSW
    [RL78_IT_2_DE_CMPS     ] = { 0 , 1 },        // CMPS    X, [HL+byte]
    [RL78_IT_2_E0_OR       ] = { 0 , 0 },        // OR      A, [HL+B]
    [RL78_IT_2_E2_OR       ] = { 0 , 0 },        // OR      A, [HL+C]
    [RL78_IT_2_E3_SKH      ] = { 0 , 0 },        // SKH
    [RL78_IT_2_E8_SKZ      ] = { 0 , 0 },        // SKZ
    [RL78_IT_2_E9_MOV      ] = { 0 , 0 },        // MOV     A, [HL+C]
    [RL78_IT_2_EB_ROL      ] = { 0 , 0 },        // ROL     A, 1
    [RL78_IT_2_EC_RETB     ] = { 0 , 0 },        // RETB
    [RL78_IT_2_ED_HALT     ] = { 0 , 0 },        // HALT
    [RL78_IT_2_F0_XOR      ] = { 0 , 0 },        // XOR     A, [HL+B]
    [RL78_IT_2_F2_XOR      ] = { 0 , 0 },        // XOR     A, [HL+C]
    [RL78_IT_2_F3_SKNH     ] = { 0 , 0 },        // SKNH
    [RL78_IT_2_F8_SKNZ     ] = { 0 , 0 },        // SKNZ
    [RL78_IT_2_F9_MOV      ] = { 0 , 0 },        // MOV     [HL+C], A
    [RL78_IT_2_FB_RORC     ] = { 0 , 0 },        // RORC    A, 1
    [RL78_IT_2_FC_RETI     ] = { 0 , 0 },        // RETI
    [RL78_IT_2_FD_STOP     ] = { 0 , 0 },        // STOP
    [RL78_IT_2_XE_ROLWC    ] = { 0 , 0 },        // ROLWC   ??, 1
    [RL78_IT_2_XF_SEL      ] = { 0 , 0 },        // SEL     RBn
    [RL78_IT_2_XA_CALL     ] = { 0 , 0 },        // CALL    ??
    [RL78_IT_2_XX_CALLT    ] = { 0 , 0 },        // CALLT   [00nnh]

    [RL78_IT_3_X0_SET1     ] = { 2 , 0 },        // SET1    !addr16.n
    [RL78_IT_3_X1_MOV1     ] = { 1 , 0 },        // MOV1    saddr.n, CY
    [RL78_IT_3_X2_SET1     ] = { 1 , 0 },        // SET1    saddr.n
    [RL78_IT_3_X3_CLR1     ] = { 1 , 0 },        // CLR1    saddr.n
    [RL78_IT_3_X4_MOV1     ] = { 0 , 1 },        // MOV1    CY, saddr.n
    [RL78_IT_3_X5_AND1     ] = { 0 , 1 },        // AND1    CY, saddr.n
    [RL78_IT_3_X6_OR1      ] = { 0 , 1 },        // OR1     CY, saddr.n
    [RL78_IT_3_X7_XOR1     ] = { 0 , 1 },        // XOR1    CY, saddr.n
    [RL78_IT_3_X8_CLR1     ] = { 2 , 0 },        // CLR1    !addr16.n
    [RL78_IT_3_X9_MOV1     ] = { 1 , 0 },        // MOV1    sfr.n, CY
    [RL78_IT_3_XA_SET1     ] = { 1 , 0 },        // SET1    sfr.n
    [RL78_IT_3_XB_CLR1     ] = { 1 , 0 },        // CLR1    sfr.n
    [RL78_IT_3_XC_MOV1     ] = { 0 , 1 },        // MOV1    CY, sfr.n
    [RL78_IT_3_XD_AND1     ] = { 0 , 1 },        // AND1    CY, sfr.n
    [RL78_IT_3_XE_OR1      ] = { 0 , 1 },        // OR1     CY, sfr.n
    [RL78_IT_3_XF_XOR1     ] = { 0 , 1 },        // XOR1    CY, sfr.n
    [RL78_IT_3_80_SET1     ] = { 0 , 0 },        // SET1    CY
    [RL78_IT_3_88_CLR1     ] = { 0 , 0 },        // CLR1    CY
    [RL78_IT_3_C0_NOT1     ] = { 0 , 0 },        // NOT1    CY
    [RL78_IT_3_Y1_MOV1     ] = { 0 , 0 },        // MOV1    [HL].n, CY
    [RL78_IT_3_Y2_SET1     ] = { 0 , 0 },        // SET1    [HL].n
    [RL78_IT_3_Y3_CLR1     ] = { 0 , 0 },        // CLR1    [HL].n
    [RL78_IT_3_Y4_MOV1     ] = { 0 , 0 },        // MOV1    CY, [HL].n
    [RL78_IT_3_Y5_AND1     ] = { 0 , 0 },        // AND1    CY, [HL].n
    [RL78_IT_3_Y6_OR1      ] = { 0 , 0 },        // OR1     CY, [HL].n
    [RL78_IT_3_Y7_XOR1     ] = { 0 , 0 },        // XOR1    CY, [HL].n
    [RL78_IT_3_Y9_MOV1     ] = { 0 , 0 },        // MOV1    A.n, CY
    [RL78_IT_3_YA_SET1     ] = { 0 , 0 },        // SET1    A.n
    [RL78_IT_3_YB_CLR1     ] = { 0 , 0 },        // CLR1    A.n
    [RL78_IT_3_YC_MOV1     ] = { 0 , 0 },        // MOV1    CY, A.n
    [RL78_IT_3_YD_AND1     ] = { 0 , 0 },        // AND1    CY, A.n
    [RL78_IT_3_YE_OR1      ] = { 0 , 0 },        // OR1     CY, A.n
    [RL78_IT_3_YF_XOR1     ] = { 0 , 0 },        // XOR1    CY, A.n

    [RL78_IT_4_X0_BTCLR    ] = { 1 , 1 },        // BTCLR   saddr.n, $addr20
    [RL78_IT_4_X1_BTCLR    ] = { 0 , 1 },        // BTCLR   A.n, $addr20
    [RL78_IT_4_X2_BT       ] = { 1 , 1 },        // BT      saddr.n, $addr20
    [RL78_IT_4_X3_BT       ] = { 0 , 1 },        // BT      A.n, $addr20
    [RL78_IT_4_X4_BF       ] = { 1 , 1 },        // BF      saddr.n, $addr20
    [RL78_IT_4_X5_BF       ] = { 0 , 1 },        // BF      A.n, $addr20
    [RL78_IT_4_X7_SHL      ] = { 0 , 0 },        // SHL     C, n
    [RL78_IT_4_X8_SHL      ] = { 0 , 0 },        // SHL     B, n
    [RL78_IT_4_X9_SHL      ] = { 0 , 0 },        // SHL     A, n
    [RL78_IT_4_XA_SHR      ] = { 0 , 0 },        // SHR     A, n
    [RL78_IT_4_XB_SAR      ] = { 0 , 0 },        // SAR     A, n
    [RL78_IT_4_Y0_BTCLR    ] = { 1 , 1 },        // BTCLR   sfr.n, $addr20
    [RL78_IT_4_Y1_BTCLR    ] = { 0 , 1 },        // BTCLR   [HL].n, $addr20
    [RL78_IT_4_Y2_BT       ] = { 1 , 1 },        // BT      sfr.n, $addr20
    [RL78_IT_4_Y3_BT       ] = { 0 , 1 },        // BT      [HL].n, $addr20
    [RL78_IT_4_Y4_BF       ] = { 1 , 1 },        // BF      sfr.n, $addr20
    [RL78_IT_4_Y5_BF       ] = { 0 , 1 },        // BF      [HL].n, $addr20
    [RL78_IT_4_XC_SHLW     ] = { 0 , 0 },        // SHLW    BC, nn
    [RL78_IT_4_XD_SHLW     ] = { 0 , 0 },        // SHLW    AX, nn
    [RL78_IT_4_XE_SHRW     ] = { 0 , 0 },        // SHRW    AX, nn
    [RL78_IT_4_XF_SARW     ] = { 0 , 0 }         // SARW    AX, nn
};


//
// Decode an instruction and return the instruction type (or RL78_IT_LAST if
// the decode failed)
//
static rl78InstructionType decodeInt(rl78P rl78, Uns32 thisPC, Uns8 *instr) {

    static vmidDecodeTableP decodeTable_1stmap;
    static vmidDecodeTableP decodeTable_2ndmap;
    static vmidDecodeTableP decodeTable_3rdmap;
    static vmidDecodeTableP decodeTable_4thmap;

    if (!decodeTable_1stmap) {
        decodeTable_1stmap = createDecodeTable_1stmap();
        decodeTable_2ndmap = createDecodeTable_2ndmap();
        decodeTable_3rdmap = createDecodeTable_3rdmap();
        decodeTable_4thmap = createDecodeTable_4thmap();
    }

    vmiProcessorP       processor = (vmiProcessorP)rl78;
    Uns32               iii;
    Uns32               fetchByte;
    rl78InstructionType type;

    // clear decode-related fields
    memset(instr, 0, 8);
    rl78->len_instByte = 0;            // instruction length (byte)
    rl78->len_instMnem = 0;            // mnemonic length
    rl78->len_instPrefix = 0;        // prefix length

    // 1st byte
    fetchByte = vmicxtFetch1Byte(processor, thisPC + rl78->len_instByte);
    type      = vmidDecode(decodeTable_1stmap, fetchByte);
    instr[rl78->len_instByte] = fetchByte;
    rl78->len_instByte += 1;
    rl78->len_instMnem = 1;

    // handle ES prefix specification
    if (type == RL78_IT_1_11_PREFIX) {
        rl78->len_instPrefix = 1;
        fetchByte = vmicxtFetch1Byte(processor, thisPC + rl78->len_instByte);
        type      = vmidDecode(decodeTable_1stmap, fetchByte);
        instr[rl78->len_instByte] = fetchByte;
        rl78->len_instByte += 1;
    }

    // special case decode failure
    if (type == RL78_IT_1_2X_SUBW) {            // SUBW    AX, ??
        if (instr[rl78->len_instPrefix + 0] == 0x21) {
            return RL78_IT_LAST;
        }
    }

    // 2nd byte
    if        (type == RL78_IT_1_61_2ndmap) {
        fetchByte = vmicxtFetch1Byte(processor, thisPC + rl78->len_instByte);
        type      = vmidDecode(decodeTable_2ndmap, fetchByte);
        instr[rl78->len_instByte] = fetchByte;
        rl78->len_instByte += 1;
        rl78->len_instMnem = 2;

    } else if (type == RL78_IT_1_71_3rdmap) {
        fetchByte = vmicxtFetch1Byte(processor, thisPC + rl78->len_instByte);
        type      = vmidDecode(decodeTable_3rdmap, fetchByte);
        instr[rl78->len_instByte] = fetchByte;
        rl78->len_instByte += 1;
        rl78->len_instMnem = 2;

    } else if (type == RL78_IT_1_31_4thmap) {
        fetchByte = vmicxtFetch1Byte(processor, thisPC + rl78->len_instByte);
        type      = vmidDecode(decodeTable_4thmap, fetchByte);
        instr[rl78->len_instByte] = fetchByte;
        rl78->len_instByte += 1;
        rl78->len_instMnem = 2;
    }

    // operands
    if (type != RL78_IT_LAST) {

        Uns32 int_oper = ary_num_operand_fetch[type][0] + ary_num_operand_fetch[type][1];

        for (iii = 0; iii < int_oper; iii++) {
            fetchByte = vmicxtFetch1Byte(processor, thisPC + rl78->len_instByte);
            instr[rl78->len_instByte] = fetchByte;
            rl78->len_instByte += 1;
        }

        if (type == RL78_IT_1_CE_MOV_SFR) {            // len_instByte == 3                // MOV     sfr, #byte

            switch (instr[rl78->len_instPrefix + 1]) {
                case 0xFA: type = RL78_IT_1_CE_MOV_PSW; rl78->len_instMnem = 2; break;    // MOV     PSW, #byte
                case 0xFC: type = RL78_IT_1_CE_MOV_CS ; rl78->len_instMnem = 2; break;    // MOV     CS, #byte
                case 0xFB: {
                    switch (instr[rl78->len_instPrefix + 2]) {
                        case 0x01: type = RL78_IT_1_CE_MULHU; rl78->len_instMnem = 3; break;    // MULHU
                        case 0x02: type = RL78_IT_1_CE_MULH ; rl78->len_instMnem = 3; break;    // MULH
                        case 0x03: type = RL78_IT_1_CE_DIVHU; rl78->len_instMnem = 3; break;    // DIVHU
                        case 0x0B: type = RL78_IT_1_CE_DIVWU; rl78->len_instMnem = 3; break;    // DIVWU
                        case 0x05: type = RL78_IT_1_CE_MACHU; rl78->len_instMnem = 3; break;    // MACHU
                        case 0x06: type = RL78_IT_1_CE_MACH ; rl78->len_instMnem = 3; break;    // MACH
                        default: break;
                    }
                }
                default: break;
            }
        }

        if (instr[0] == 0x71) {        // RL78_IT_1_71_3rdmap
            if ((instr[1] == 0x7A) && (instr[2] == 0xFA)) {
                type = RL78_IT_3_7A_EI;
                rl78->len_instMnem = 3;
            } else if ((instr[1] == 0x7B) && (instr[2] == 0xFA)) {
                type = RL78_IT_3_7B_DI;
                rl78->len_instMnem = 3;
            }
        }
    }

    return type;
}

//
// If this is a skil prefix instruction, return the equivalent condition
//
static en_Cond getSkipPrefixCondition(rl78InstructionType type) {
    switch(type) {
        case RL78_IT_2_C8_SKC:  return en_Cond_C;
        case RL78_IT_2_D8_SKNC: return en_Cond_NC;
        case RL78_IT_2_E3_SKH:  return en_Cond_H;
        case RL78_IT_2_E8_SKZ:  return en_Cond_Z;
        case RL78_IT_2_F3_SKNH: return en_Cond_NH;
        case RL78_IT_2_F8_SKNZ: return en_Cond_NZ;
        default:                return en_Cond_T;
    }
}

//
// Decode the RL78 instruction at the passed address. If the decode succeeds,
// dispatch it to the corresponding function in the dispatch table and return
// True; otherwise, dispatch using the defaultCB and return False.
//
Bool rl78Decode(
    rl78P               rl78,
    Uns32               thisPC,
    rl78DispatchTableCP table,
    rl78DispatchFn      defaultCB,
    void               *userData) {

    Uns8                instr[8];
    rl78InstructionType type;
    en_Cond             cond = en_Cond_T;

    // initialize full instruction size including skip prefix and assume that
    // this instruction will not have a SKIP prefix
    rl78->len_instByteAndSkip = 0;
    rl78->skipCondition       = cond;

    do {

        // perform decode
        type = decodeInt(rl78, thisPC, instr);

        // accumulated full instruction size
        rl78->len_instByteAndSkip += rl78->len_instByte;

        // get any condition if this is a skip instruction
        cond = getSkipPrefixCondition(type);

        // decode next instruction as well if this is a skip instruction
        // (skip and following instruction must be treated atomically for
        // interrupt purposes, so it is effectively another kind of prefix)
        if (cond != en_Cond_T) {
            rl78->skipCondition = cond;
            thisPC += rl78->len_instByte;
        }

    } while (cond != en_Cond_T);

    if (type != RL78_IT_LAST) {

        // decode succeeded
        if (table) {
            ((*table)[type])(rl78, thisPC, instr, userData);
        }

        return True;

    } else {

        // decode failed
        if (defaultCB) {
            defaultCB(rl78, thisPC, instr, userData);
        }

        return False;
    }
}

