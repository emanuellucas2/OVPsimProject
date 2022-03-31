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

// Utility routines and structures for the RL78 decoder

#ifndef RL78DECODE_H
#define RL78DECODE_H

#include "hostapi/impTypes.h"
#include "vmi/vmiTypes.h"

#include "rl78Structure.h"
//typedef struct rl78S rl78, *rl78P;        // rl78Structure.h


// Dispatcher callback type
#define RL78_DISPATCH_FN(_NAME) void _NAME( \
    rl78P rl78,         \
    Uns32 thisPC,       \
    Uns8* instr,        \
    void* userData      \
)
typedef RL78_DISPATCH_FN((*rl78DispatchFn));

//
// Instruction type enumeration
//
typedef enum rl78InstructionTypeE {

    // 1st MAP
    RL78_IT_1_00_NOP      ,    // No Operation
    RL78_IT_1_02_ADDW     ,    // Word Data Addition
    RL78_IT_1_04_ADDW     ,    // Word Data Addition
    RL78_IT_1_06_ADDW     ,    // Word Data Addition
    RL78_IT_1_0X_ADDW     ,    // Word Data Addition
    RL78_IT_1_08_XCH      ,    // Byte Data Transfer
    RL78_IT_1_09_MOV      ,    // Byte Data Transfer
    RL78_IT_1_0A_ADD      ,    // Byte Data Addition
    RL78_IT_1_0B_ADD      ,    // Byte Data Addition
    RL78_IT_1_0C_ADD      ,    // Byte Data Addition
    RL78_IT_1_0D_ADD      ,    // Byte Data Addition
    RL78_IT_1_0E_ADD      ,    // Byte Data Addition
    RL78_IT_1_0F_ADD      ,    // Byte Data Addition
    RL78_IT_1_10_ADDW     ,    // Word Data Addition
    RL78_IT_1_11_PREFIX   ,
    RL78_IT_1_1X_MOVW     ,    // Word Data Transfer
    RL78_IT_1_1Y_MOVW     ,    // Word Data Transfer
    RL78_IT_1_18_MOV      ,    // Byte Data Transfer
    RL78_IT_1_19_MOV      ,    // Byte Data Transfer
    RL78_IT_1_1A_ADDC     ,    // Addition of Byte Data with Carry
    RL78_IT_1_1B_ADDC     ,    // Addition of Byte Data with Carry
    RL78_IT_1_1C_ADDC     ,    // Addition of Byte Data with Carry
    RL78_IT_1_1D_ADDC     ,    // Addition of Byte Data with Carry
    RL78_IT_1_1E_ADDC     ,    // Addition of Byte Data with Carry
    RL78_IT_1_1F_ADDC     ,    // Addition of Byte Data with Carry
    RL78_IT_1_20_SUBW     ,    // Word Data Subtraction
    RL78_IT_1_22_SUBW     ,    // Word Data Subtraction
    RL78_IT_1_24_SUBW     ,    // Word Data Subtraction
    RL78_IT_1_26_SUBW     ,    // Word Data Subtraction
    RL78_IT_1_2X_SUBW     ,    // Word Data Subtraction
    RL78_IT_1_28_MOV      ,    // Byte Data Transfer
    RL78_IT_1_29_MOV      ,    // Byte Data Transfer
    RL78_IT_1_2A_SUB      ,    // Byte Data Subtraction
    RL78_IT_1_2B_SUB      ,    // Byte Data Subtraction
    RL78_IT_1_2C_SUB      ,    // Byte Data Subtraction
    RL78_IT_1_2D_SUB      ,    // Byte Data Subtraction
    RL78_IT_1_2E_SUB      ,    // Byte Data Subtraction
    RL78_IT_1_2F_SUB      ,    // Byte Data Subtraction
    RL78_IT_1_31_4thmap   ,
    RL78_IT_1_3X_XCHW     ,    // Word Data Exchange
    RL78_IT_1_3Y_MOVW     ,    // Word Data Transfer
    RL78_IT_1_38_MOV      ,    // Byte Data Transfer
    RL78_IT_1_39_MOV      ,    // Byte Data Transfer
    RL78_IT_1_3A_SUBC     ,    // Subtraction of Byte Data with Carry
    RL78_IT_1_3B_SUBC     ,    // Subtraction of Byte Data with Carry
    RL78_IT_1_3C_SUBC     ,    // Subtraction of Byte Data with Carry
    RL78_IT_1_3D_SUBC     ,    // Subtraction of Byte Data with Carry
    RL78_IT_1_3E_SUBC     ,    // Subtraction of Byte Data with Carry
    RL78_IT_1_3F_SUBC     ,    // Subtraction of Byte Data with Carry
    RL78_IT_1_40_CMP      ,    // Byte Data Comparison
    RL78_IT_1_41_MOV      ,    // Byte Data Transfer
    RL78_IT_1_42_CMPW     ,    // Word Data Comparison
    RL78_IT_1_44_CMPW     ,    // Word Data Comparison
    RL78_IT_1_46_CMPW     ,    // Word Data Comparison
    RL78_IT_1_4X_CMPW     ,    // Word Data Comparison
    RL78_IT_1_48_MOV      ,    // Byte Data Transfer
    RL78_IT_1_49_MOV      ,    // Byte Data Transfer
    RL78_IT_1_4A_CMP      ,    // Byte Data Comparison
    RL78_IT_1_4B_CMP      ,    // Byte Data Comparison
    RL78_IT_1_4C_CMP      ,    // Byte Data Comparison
    RL78_IT_1_4D_CMP      ,    // Byte Data Comparison
    RL78_IT_1_4E_CMP      ,    // Byte Data Comparison
    RL78_IT_1_4F_CMP      ,    // Byte Data Comparison
    RL78_IT_1_5X_MOV      ,    // Byte Data Transfer
    RL78_IT_1_58_MOVW     ,    // Word Data Transfer
    RL78_IT_1_59_MOVW     ,    // Word Data Transfer
    RL78_IT_1_5A_AND      ,    // Logical Product of Byte Data
    RL78_IT_1_5B_AND      ,    // Logical Product of Byte Data
    RL78_IT_1_5C_AND      ,    // Logical Product of Byte Data
    RL78_IT_1_5D_AND      ,    // Logical Product of Byte Data
    RL78_IT_1_5E_AND      ,    // Logical Product of Byte Data
    RL78_IT_1_5F_AND      ,    // Logical Product of Byte Data
    RL78_IT_1_61_2ndmap   ,
    RL78_IT_1_6X_MOV      ,    // Byte Data Transfer
    RL78_IT_1_68_MOVW     ,    // Word Data Transfer
    RL78_IT_1_69_MOVW     ,    // Word Data Transfer
    RL78_IT_1_6A_OR       ,    // Logical Sum of Byte Data
    RL78_IT_1_6B_OR       ,    // Logical Sum of Byte Data
    RL78_IT_1_6C_OR       ,    // Logical Sum of Byte Data
    RL78_IT_1_6D_OR       ,    // Logical Sum of Byte Data
    RL78_IT_1_6E_OR       ,    // Logical Sum of Byte Data
    RL78_IT_1_6F_OR       ,    // Logical Sum of Byte Data
    RL78_IT_1_71_3rdmap   ,
    RL78_IT_1_7X_MOV      ,    // Byte Data Transfer
    RL78_IT_1_78_MOVW     ,    // Word Data Transfer
    RL78_IT_1_79_MOVW     ,    // Word Data Transfer
    RL78_IT_1_7A_XOR      ,    // Exclusive Logical Sum of Byte Data
    RL78_IT_1_7B_XOR      ,    // Exclusive Logical Sum of Byte Data
    RL78_IT_1_7C_XOR      ,    // Exclusive Logical Sum of Byte Data
    RL78_IT_1_7D_XOR      ,    // Exclusive Logical Sum of Byte Data
    RL78_IT_1_7E_XOR      ,    // Exclusive Logical Sum of Byte Data
    RL78_IT_1_7F_XOR      ,    // Exclusive Logical Sum of Byte Data
    RL78_IT_1_8X_INC      ,    // Byte Data Increment
    RL78_IT_1_88_MOV      ,    // Byte Data Transfer
    RL78_IT_1_89_MOV      ,    // Byte Data Transfer
    RL78_IT_1_8A_MOV      ,    // Byte Data Transfer
    RL78_IT_1_8B_MOV      ,    // Byte Data Transfer
    RL78_IT_1_8C_MOV      ,    // Byte Data Transfer
    RL78_IT_1_8D_MOV      ,    // Byte Data Transfer
    RL78_IT_1_8E_MOV      ,    // Byte Data Transfer
    RL78_IT_1_8F_MOV      ,    // Byte Data Transfer
    RL78_IT_1_9X_DEC      ,    // Byte Data Decrement
    RL78_IT_1_98_MOV      ,    // Byte Data Transfer
    RL78_IT_1_99_MOV      ,    // Byte Data Transfer
    RL78_IT_1_9A_MOV      ,    // Byte Data Transfer
    RL78_IT_1_9B_MOV      ,    // Byte Data Transfer
    RL78_IT_1_9C_MOV      ,    // Byte Data Transfer
    RL78_IT_1_9D_MOV      ,    // Byte Data Transfer
    RL78_IT_1_9E_MOV      ,    // Byte Data Transfer
    RL78_IT_1_9F_MOV      ,    // Byte Data Transfer
    RL78_IT_1_A0_INC      ,    // Byte Data Increment
    RL78_IT_1_A2_INCW     ,    // Word Data Increment
    RL78_IT_1_A4_INC      ,    // Byte Data Increment
    RL78_IT_1_A6_INCW     ,    // Word Data Increment
    RL78_IT_1_AX_INCW     ,    // Word Data Increment
    RL78_IT_1_A8_MOVW     ,    // Word Data Transfer
    RL78_IT_1_A9_MOVW     ,    // Word Data Transfer
    RL78_IT_1_AA_MOVW     ,    // Word Data Transfer
    RL78_IT_1_AB_MOVW     ,    // Word Data Transfer
    RL78_IT_1_AC_MOVW     ,    // Word Data Transfer
    RL78_IT_1_AD_MOVW     ,    // Word Data Transfer
    RL78_IT_1_AE_MOVW     ,    // Word Data Transfer
    RL78_IT_1_AF_MOVW     ,    // Word Data Transfer
    RL78_IT_1_B0_DEC      ,    // Byte Data Decrement
    RL78_IT_1_B2_DECW     ,    // Word Data Decrement
    RL78_IT_1_B4_DEC      ,    // Byte Data Decrement
    RL78_IT_1_B6_DECW     ,    // Word Data Decrement
    RL78_IT_1_BX_DECW     ,    // Word Data Decrement
    RL78_IT_1_B8_MOVW     ,    // Word Data Transfer
    RL78_IT_1_B9_MOVW     ,    // Word Data Transfer
    RL78_IT_1_BA_MOVW     ,    // Word Data Transfer
    RL78_IT_1_BB_MOVW     ,    // Word Data Transfer
    RL78_IT_1_BC_MOVW     ,    // Word Data Transfer
    RL78_IT_1_BD_MOVW     ,    // Word Data Transfer
    RL78_IT_1_BE_MOVW     ,    // Word Data Transfer
    RL78_IT_1_BF_MOVW     ,    // Word Data Transfer
    RL78_IT_1_CX_POP      ,    // Pop
    RL78_IT_1_CY_PUSH     ,    // Push
    RL78_IT_1_C8_MOV      ,    // Byte Data Transfer
    RL78_IT_1_C9_MOVW     ,    // Word Data Transfer
    RL78_IT_1_CA_MOV      ,    // Byte Data Transfer
    RL78_IT_1_CB_MOVW     ,    // Word Data Transfer
    RL78_IT_1_CC_MOV      ,    // Byte Data Transfer
    RL78_IT_1_CD_MOV      ,    // Byte Data Transfer
    RL78_IT_1_CE_MOV_SFR  ,    // Byte Data Transfer
    RL78_IT_1_CE_MOV_PSW  ,    // Byte Data Transfer
    RL78_IT_1_CE_MOV_CS   ,    // Byte Data Transfer
    RL78_IT_1_CE_MULHU    ,    // Unsigned Multiplication of Data
    RL78_IT_1_CE_MULH     ,    // Signed Multiplication of Data
    RL78_IT_1_CE_DIVHU    ,    // Unsigned Division of Data
    RL78_IT_1_CE_DIVWU    ,    // Unsigned Division of Data
    RL78_IT_1_CE_MACHU    ,    // Unsigned Multipication and Accumulation of Data
    RL78_IT_1_CE_MACH     ,    // Signed Multipication and Accumulation of Data
    RL78_IT_1_CF_MOV      ,    // Byte Data Transfer
    RL78_IT_1_DX_CMP0     ,    // Byte Data Zero Comparison
    RL78_IT_1_D4_CMP0     ,    // Byte Data Zero Comparison
    RL78_IT_1_D5_CMP0     ,    // Byte Data Zero Comparison
    RL78_IT_1_D6_MULU     ,    // Unsigned Multiplication of Data
    RL78_IT_1_D7_RET      ,    // Return from Subroutine
    RL78_IT_1_D8_MOV      ,    // Byte Data Transfer
    RL78_IT_1_D9_MOV      ,    // Byte Data Transfer
    RL78_IT_1_DC_BC       ,    // Conditional Branch with Carry Flag (CY = 1)
    RL78_IT_1_DD_BZ       ,    // Conditional Branch with Zero Flag (Z = 1)
    RL78_IT_1_DE_BNC      ,    // Conditional Branch with Carry Flag (CY = 0)
    RL78_IT_1_DF_BNZ      ,    // Conditional Branch with Zero Flag (Z = 0)
    RL78_IT_1_EX_ONEB     ,    // Byte Data 01H Set
    RL78_IT_1_E4_ONEB     ,    // Byte Data 01H Set
    RL78_IT_1_E5_ONEB     ,    // Byte Data 01H Set
    RL78_IT_1_E6_ONEW     ,    // Word Data 0001 Set
    RL78_IT_1_E7_ONEW     ,    // Word Data 0001 Set
    RL78_IT_1_E8_MOV      ,    // Byte Data Transfer
    RL78_IT_1_E9_MOV      ,    // Byte Data Transfer
    RL78_IT_1_EC_BR       ,    // Unconditional Branch
    RL78_IT_1_ED_BR       ,    // Unconditional Branch
    RL78_IT_1_EE_BR       ,    // Unconditional Branch
    RL78_IT_1_EF_BR       ,    // Unconditional Branch
    RL78_IT_1_FX_CLRB     ,    // Byte Data Clear
    RL78_IT_1_F4_CLRB     ,    // Byte Data Clear
    RL78_IT_1_F5_CLRB     ,    // Byte Data Clear
    RL78_IT_1_F6_CLRW     ,    // Word Data Clear
    RL78_IT_1_F7_CLRW     ,    // Word Data Clear
    RL78_IT_1_F8_MOV      ,    // Byte Data Transfer
    RL78_IT_1_F9_MOV      ,    // Byte Data Transfer
    RL78_IT_1_FC_CALL     ,    // Subroutine Call
    RL78_IT_1_FD_CALL     ,    // Subroutine Call
    RL78_IT_1_FE_CALL     ,    // Subroutine Call
    RL78_IT_1_XA_MOVW     ,    // Word Data Transfer
    RL78_IT_1_XB_MOVW     ,    // Word Data Transfer

    RL78_IT_2_0X_ADD      ,    // Byte Data Addition
    RL78_IT_2_09_ADDW     ,    // Word Data Addition
    RL78_IT_2_0Y_ADD      ,    // Byte Data Addition
    RL78_IT_2_1X_ADDC     ,    // Addition of Byte Data with Carry
    RL78_IT_2_1Y_ADDC     ,    // Addition of Byte Data with Carry
    RL78_IT_2_2X_SUB      ,    // Byte Data Subtraction
    RL78_IT_2_29_SUBW     ,    // Word Data Subtraction
    RL78_IT_2_2Y_SUB      ,    // Byte Data Subtraction
    RL78_IT_2_3X_SUBC     ,    // Subtraction of Byte Data with Carry
    RL78_IT_2_3Y_SUBC     ,    // Subtraction of Byte Data with Carry
    RL78_IT_2_4X_CMP      ,    // Byte Data Comparison
    RL78_IT_2_49_CMPW     ,    // Word Data Comparison
    RL78_IT_2_4Y_CMP      ,    // Byte Data Comparison
    RL78_IT_2_5X_AND      ,    // Logical Product of Byte Data
    RL78_IT_2_59_INC      ,    // Byte Data Increment
    RL78_IT_2_5Y_AND      ,    // Logical Product of Byte Data
    RL78_IT_2_6X_OR       ,    // Logical Sum of Byte Data
    RL78_IT_2_69_DEC      ,    // Byte Data Decrement
    RL78_IT_2_6Y_OR       ,    // Logical Sum of Byte Data
    RL78_IT_2_7X_XOR      ,    // Exclusive Logical Sum of Byte Data
    RL78_IT_2_79_INCW     ,    // Word Data Increment
    RL78_IT_2_7Y_XOR      ,    // Exclusive Logical Sum of Byte Data
    RL78_IT_2_80_ADD      ,    // Byte Data Addition
    RL78_IT_2_82_ADD      ,    // Byte Data Addition
    RL78_IT_2_89_DECW     ,    // Word Data Decrement
    RL78_IT_2_8X_XCH      ,    // Byte Data Transfer
    RL78_IT_2_90_ADDC     ,    // Addition of Byte Data with Carry
    RL78_IT_2_92_ADDC     ,    // Addition of Byte Data with Carry
    RL78_IT_2_A0_SUB      ,    // Byte Data Subtraction
    RL78_IT_2_A2_SUB      ,    // Byte Data Subtraction
    RL78_IT_2_A8_XCH      ,    // Byte Data Transfer
    RL78_IT_2_A9_XCH      ,    // Byte Data Transfer
    RL78_IT_2_AA_XCH      ,    // Byte Data Transfer
    RL78_IT_2_AB_XCH      ,    // Byte Data Transfer
    RL78_IT_2_AC_XCH      ,    // Byte Data Transfer
    RL78_IT_2_AD_XCH      ,    // Byte Data Transfer
    RL78_IT_2_AE_XCH      ,    // Byte Data Transfer
    RL78_IT_2_AF_XCH      ,    // Byte Data Transfer
    RL78_IT_2_B0_SUBC     ,    // Subtraction of Byte Data with Carry
    RL78_IT_2_B2_SUBC     ,    // Subtraction of Byte Data with Carry
    RL78_IT_2_B8_MOV      ,    // Byte Data Transfer
    RL78_IT_2_B9_XCH      ,    // Byte Data Transfer
    RL78_IT_2_C0_CMP      ,    // Byte Data Comparison
    RL78_IT_2_C2_CMP      ,    // Byte Data Comparison
    RL78_IT_2_C3_BH       ,    // Conditional branch by numeric value comparison ((Z V CY) = 0)
    RL78_IT_2_C8_SKC      ,
    RL78_IT_2_C9_MOV      ,    // Byte Data Transfer
    RL78_IT_2_CB_BR       ,    // Unconditional Branch
    RL78_IT_2_CC_BRK      ,    // Software Vectored Interrupt
    RL78_IT_2_CD_POP      ,    // Pop
    RL78_IT_2_CE_MOVS     ,    // Byte Data Transfer and PSW Change
    RL78_IT_2_D0_AND      ,    // Logical Product of Byte Data
    RL78_IT_2_D2_AND      ,    // Logical Product of Byte Data
    RL78_IT_2_D3_BNH      ,    // Conditional branch by numeric value comparison ((Z V CY) = 1)
    RL78_IT_2_D8_SKNC     ,
    RL78_IT_2_D9_MOV      ,    // Byte Data Transfer
    RL78_IT_2_DB_ROR      ,    // Byte Data Rotation to the Right
    RL78_IT_2_DC_ROLC     ,    // Byte Data Rotation to the Left with Carry
    RL78_IT_2_DD_PUSH     ,    // Push
    RL78_IT_2_DE_CMPS     ,    // Byte Data Comparison
    RL78_IT_2_E0_OR       ,    // Logical Sum of Byte Data
    RL78_IT_2_E2_OR       ,    // Logical Sum of Byte Data
    RL78_IT_2_E3_SKH      ,
    RL78_IT_2_E8_SKZ      ,
    RL78_IT_2_E9_MOV      ,    // Byte Data Transfer
    RL78_IT_2_EB_ROL      ,    // Byte Data Rotation to the Left
    RL78_IT_2_EC_RETB     ,    // Return from Software Vectored Interrupt
    RL78_IT_2_ED_HALT     ,    // HALT Mode Set
    RL78_IT_2_F0_XOR      ,    // Exclusive Logical Sum of Byte Data
    RL78_IT_2_F2_XOR      ,    // Exclusive Logical Sum of Byte Data
    RL78_IT_2_F3_SKNH     ,
    RL78_IT_2_F8_SKNZ     ,
    RL78_IT_2_F9_MOV      ,    // Byte Data Transfer
    RL78_IT_2_FB_RORC     ,    // Byte Data Rotation to the Right with Carry
    RL78_IT_2_FC_RETI     ,    // Return from Hardware Vectored Interrupt
    RL78_IT_2_FD_STOP     ,    // STOP Mode Set
    RL78_IT_2_XE_ROLWC    ,    // Word Data Rotation to the Left with Carry
    RL78_IT_2_XF_SEL      ,    // Register Bank Selection
    RL78_IT_2_XA_CALL     ,    // Subroutine Call
    RL78_IT_2_XX_CALLT    ,    // Subroutine Call (Refer to the Call Table)

    RL78_IT_3_X0_SET1     ,    // 1 Bit Data Set
    RL78_IT_3_X1_MOV1     ,    // 1 Bit Data Transfer
    RL78_IT_3_X2_SET1     ,    // 1 Bit Data Set
    RL78_IT_3_X3_CLR1     ,    // 1 Bit Data Clear
    RL78_IT_3_X4_MOV1     ,    // 1 Bit Data Transfer
    RL78_IT_3_X5_AND1     ,    // 1 Bit Data Logical Product
    RL78_IT_3_X6_OR1      ,    // 1 Bit Data Logical Sum
    RL78_IT_3_X7_XOR1     ,    // 1 Bit Data Exclusive Logical Sum
    RL78_IT_3_X8_CLR1     ,    // 1 Bit Data Clear
    RL78_IT_3_X9_MOV1     ,    // 1 Bit Data Transfer
    RL78_IT_3_XA_SET1     ,    // 1 Bit Data Set
    RL78_IT_3_XB_CLR1     ,    // 1 Bit Data Clear
    RL78_IT_3_XC_MOV1     ,    // 1 Bit Data Transfer
    RL78_IT_3_XD_AND1     ,    // 1 Bit Data Logical Product
    RL78_IT_3_XE_OR1      ,    // 1 Bit Data Logical Sum
    RL78_IT_3_XF_XOR1     ,    // 1 Bit Data Exclusive Logical Sum
    RL78_IT_3_7A_EI       ,    // Interrupt Enabled
    RL78_IT_3_7B_DI       ,    // Interrupt Disabled
    RL78_IT_3_80_SET1     ,    // 1 Bit Data Set
    RL78_IT_3_88_CLR1     ,    // 1 Bit Data Clear
    RL78_IT_3_C0_NOT1     ,    // 1 Bit Data Logical Negation
    RL78_IT_3_Y1_MOV1     ,    // 1 Bit Data Transfer
    RL78_IT_3_Y2_SET1     ,    // 1 Bit Data Set
    RL78_IT_3_Y3_CLR1     ,    // 1 Bit Data Clear
    RL78_IT_3_Y4_MOV1     ,    // 1 Bit Data Transfer
    RL78_IT_3_Y5_AND1     ,    // 1 Bit Data Logical Product
    RL78_IT_3_Y6_OR1      ,    // 1 Bit Data Logical Sum
    RL78_IT_3_Y7_XOR1     ,    // 1 Bit Data Exclusive Logical Sum
    RL78_IT_3_Y9_MOV1     ,    // 1 Bit Data Transfer
    RL78_IT_3_YA_SET1     ,    // 1 Bit Data Set
    RL78_IT_3_YB_CLR1     ,    // 1 Bit Data Clear
    RL78_IT_3_YC_MOV1     ,    // 1 Bit Data Transfer
    RL78_IT_3_YD_AND1     ,    // 1 Bit Data Logical Product
    RL78_IT_3_YE_OR1      ,    // 1 Bit Data Logical Sum
    RL78_IT_3_YF_XOR1     ,    // 1 Bit Data Exclusive Logical Sum

    RL78_IT_4_X0_BTCLR    ,    // Conditional Branch and Clear by Bit Test (Byte Data Bit = 1)
    RL78_IT_4_X1_BTCLR    ,    // Conditional Branch and Clear by Bit Test (Byte Data Bit = 1)
    RL78_IT_4_X2_BT       ,    // Conditional Branch by Bit Test (Byte Data Bit = 1)
    RL78_IT_4_X3_BT       ,    // Conditional Branch by Bit Test (Byte Data Bit = 1)
    RL78_IT_4_X4_BF       ,    // Conditional Branch by Bit Test (Byte Data Bit = 0)
    RL78_IT_4_X5_BF       ,    // Conditional Branch by Bit Test (Byte Data Bit = 0)
    RL78_IT_4_X7_SHL      ,    // Logical Shift to the Left
    RL78_IT_4_X8_SHL      ,    // Logical Shift to the Left
    RL78_IT_4_X9_SHL      ,    // Logical Shift to the Left
    RL78_IT_4_XA_SHR      ,    // Logical Shift to the Right
    RL78_IT_4_XB_SAR      ,    // Arithmetric Shift to the Right
    RL78_IT_4_Y0_BTCLR    ,    // Conditional Branch and Clear by Bit Test (Byte Data Bit = 1)
    RL78_IT_4_Y1_BTCLR    ,    // Conditional Branch and Clear by Bit Test (Byte Data Bit = 1)
    RL78_IT_4_Y2_BT       ,    // Conditional Branch by Bit Test (Byte Data Bit = 1)
    RL78_IT_4_Y3_BT       ,    // Conditional Branch by Bit Test (Byte Data Bit = 1)
    RL78_IT_4_Y4_BF       ,    // Conditional Branch by Bit Test (Byte Data Bit = 0)
    RL78_IT_4_Y5_BF       ,    // Conditional Branch by Bit Test (Byte Data Bit = 0)
    RL78_IT_4_XC_SHLW     ,    // Logical Shift to the Left
    RL78_IT_4_XD_SHLW     ,    // Logical Shift to the Left
    RL78_IT_4_XE_SHRW     ,    // Logical Shift to the Right
    RL78_IT_4_XF_SARW     ,    // Arithmetric Shift to the Right

    // KEEP LAST: for sizing the array
    RL78_IT_LAST          
    
} rl78InstructionType;

// Dispatch table
typedef const rl78DispatchFn rl78DispatchTableC[RL78_IT_LAST];
typedef rl78DispatchTableC *rl78DispatchTableCP;


// Decode the RL78 instruction at the passed address. If the decode succeeds,
// dispatch it to the corresponding function in the dispatch table and return
// True; otherwise, dispatch using the defaultCB and return False.
Bool rl78Decode(
    rl78P               rl78,
    Uns32               thisPC,
    rl78DispatchTableCP table,
    rl78DispatchFn      defaultCB,
    void               *userData
);

#endif

