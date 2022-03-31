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

#ifndef RL78MORPH_H
#define RL78MORPH_H

// VMI header files
#include "vmi/vmiCxt.h"

// model header files
#include "rl78Decode.h"


//RL78_DISPATCH_FN(rl78Morph_1_00_NOP      );
//RL78_DISPATCH_FN(rl78Morph_1_02_ADDW     );
//RL78_DISPATCH_FN(rl78Morph_1_04_ADDW     );
//RL78_DISPATCH_FN(rl78Morph_1_06_ADDW     );
//RL78_DISPATCH_FN(rl78Morph_1_0X_ADDW     );
//RL78_DISPATCH_FN(rl78Morph_1_08_XCH      );
//RL78_DISPATCH_FN(rl78Morph_1_09_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_0A_ADD      );
//RL78_DISPATCH_FN(rl78Morph_1_0B_ADD      );
//RL78_DISPATCH_FN(rl78Morph_1_0C_ADD      );
//RL78_DISPATCH_FN(rl78Morph_1_0D_ADD      );
//RL78_DISPATCH_FN(rl78Morph_1_0E_ADD      );
//RL78_DISPATCH_FN(rl78Morph_1_0F_ADD      );
//RL78_DISPATCH_FN(rl78Morph_1_10_ADDW     );
//RL78_DISPATCH_FN(rl78Morph_1_11_PREFIX   );
//RL78_DISPATCH_FN(rl78Morph_1_1X_MOVW     );
//RL78_DISPATCH_FN(rl78Morph_1_1Y_MOVW     );
//RL78_DISPATCH_FN(rl78Morph_1_18_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_19_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_1A_ADDC     );
//RL78_DISPATCH_FN(rl78Morph_1_1B_ADDC     );
//RL78_DISPATCH_FN(rl78Morph_1_1C_ADDC     );
//RL78_DISPATCH_FN(rl78Morph_1_1D_ADDC     );
//RL78_DISPATCH_FN(rl78Morph_1_1E_ADDC     );
//RL78_DISPATCH_FN(rl78Morph_1_1F_ADDC     );
//RL78_DISPATCH_FN(rl78Morph_1_20_SUBW     );
//RL78_DISPATCH_FN(rl78Morph_1_22_SUBW     );
//RL78_DISPATCH_FN(rl78Morph_1_24_SUBW     );
//RL78_DISPATCH_FN(rl78Morph_1_26_SUBW     );
//RL78_DISPATCH_FN(rl78Morph_1_2X_SUBW     );
//RL78_DISPATCH_FN(rl78Morph_1_28_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_29_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_2A_SUB      );
//RL78_DISPATCH_FN(rl78Morph_1_2B_SUB      );
//RL78_DISPATCH_FN(rl78Morph_1_2C_SUB      );
//RL78_DISPATCH_FN(rl78Morph_1_2D_SUB      );
//RL78_DISPATCH_FN(rl78Morph_1_2E_SUB      );
//RL78_DISPATCH_FN(rl78Morph_1_2F_SUB      );
//RL78_DISPATCH_FN(rl78Morph_1_31_4thmap   );
//RL78_DISPATCH_FN(rl78Morph_1_3X_XCHW     );
//RL78_DISPATCH_FN(rl78Morph_1_3Y_MOVW     );
//RL78_DISPATCH_FN(rl78Morph_1_38_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_39_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_3A_SUBC     );
//RL78_DISPATCH_FN(rl78Morph_1_3B_SUBC     );
//RL78_DISPATCH_FN(rl78Morph_1_3C_SUBC     );
//RL78_DISPATCH_FN(rl78Morph_1_3D_SUBC     );
//RL78_DISPATCH_FN(rl78Morph_1_3E_SUBC     );
//RL78_DISPATCH_FN(rl78Morph_1_3F_SUBC     );
//RL78_DISPATCH_FN(rl78Morph_1_40_CMP      );
//RL78_DISPATCH_FN(rl78Morph_1_41_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_42_CMPW     );
//RL78_DISPATCH_FN(rl78Morph_1_44_CMPW     );
//RL78_DISPATCH_FN(rl78Morph_1_46_CMPW     );
//RL78_DISPATCH_FN(rl78Morph_1_4X_CMPW     );
//RL78_DISPATCH_FN(rl78Morph_1_48_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_49_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_4A_CMP      );
//RL78_DISPATCH_FN(rl78Morph_1_4B_CMP      );
//RL78_DISPATCH_FN(rl78Morph_1_4C_CMP      );
//RL78_DISPATCH_FN(rl78Morph_1_4D_CMP      );
//RL78_DISPATCH_FN(rl78Morph_1_4E_CMP      );
//RL78_DISPATCH_FN(rl78Morph_1_4F_CMP      );
//RL78_DISPATCH_FN(rl78Morph_1_5X_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_58_MOVW     );
//RL78_DISPATCH_FN(rl78Morph_1_59_MOVW     );
//RL78_DISPATCH_FN(rl78Morph_1_5A_AND      );
//RL78_DISPATCH_FN(rl78Morph_1_5B_AND      );
//RL78_DISPATCH_FN(rl78Morph_1_5C_AND      );
//RL78_DISPATCH_FN(rl78Morph_1_5D_AND      );
//RL78_DISPATCH_FN(rl78Morph_1_5E_AND      );
//RL78_DISPATCH_FN(rl78Morph_1_5F_AND      );
//RL78_DISPATCH_FN(rl78Morph_1_61_2ndmap   );
//RL78_DISPATCH_FN(rl78Morph_1_6X_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_68_MOVW     );
//RL78_DISPATCH_FN(rl78Morph_1_69_MOVW     );
//RL78_DISPATCH_FN(rl78Morph_1_6A_OR       );
//RL78_DISPATCH_FN(rl78Morph_1_6B_OR       );
//RL78_DISPATCH_FN(rl78Morph_1_6C_OR       );
//RL78_DISPATCH_FN(rl78Morph_1_6D_OR       );
//RL78_DISPATCH_FN(rl78Morph_1_6E_OR       );
//RL78_DISPATCH_FN(rl78Morph_1_6F_OR       );
//RL78_DISPATCH_FN(rl78Morph_1_71_3rdmap   );
//RL78_DISPATCH_FN(rl78Morph_1_7X_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_78_MOVW     );
//RL78_DISPATCH_FN(rl78Morph_1_79_MOVW     );
//RL78_DISPATCH_FN(rl78Morph_1_7A_XOR      );
//RL78_DISPATCH_FN(rl78Morph_1_7B_XOR      );
//RL78_DISPATCH_FN(rl78Morph_1_7C_XOR      );
//RL78_DISPATCH_FN(rl78Morph_1_7D_XOR      );
//RL78_DISPATCH_FN(rl78Morph_1_7E_XOR      );
//RL78_DISPATCH_FN(rl78Morph_1_7F_XOR      );
//RL78_DISPATCH_FN(rl78Morph_1_8X_INC      );
//RL78_DISPATCH_FN(rl78Morph_1_88_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_89_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_8A_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_8B_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_8C_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_8D_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_8E_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_8F_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_9X_DEC      );
//RL78_DISPATCH_FN(rl78Morph_1_98_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_99_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_9A_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_9B_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_9C_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_9D_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_9E_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_9F_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_A0_INC      );
//RL78_DISPATCH_FN(rl78Morph_1_A2_INCW     );
//RL78_DISPATCH_FN(rl78Morph_1_A4_INC      );
//RL78_DISPATCH_FN(rl78Morph_1_A6_INCW     );
//RL78_DISPATCH_FN(rl78Morph_1_AX_INCW     );
//RL78_DISPATCH_FN(rl78Morph_1_A8_MOVW     );
//RL78_DISPATCH_FN(rl78Morph_1_A9_MOVW     );
//RL78_DISPATCH_FN(rl78Morph_1_AA_MOVW     );
//RL78_DISPATCH_FN(rl78Morph_1_AB_MOVW     );
//RL78_DISPATCH_FN(rl78Morph_1_AC_MOVW     );
//RL78_DISPATCH_FN(rl78Morph_1_AD_MOVW     );
//RL78_DISPATCH_FN(rl78Morph_1_AE_MOVW     );
//RL78_DISPATCH_FN(rl78Morph_1_AF_MOVW     );
//RL78_DISPATCH_FN(rl78Morph_1_B0_DEC      );
//RL78_DISPATCH_FN(rl78Morph_1_B2_DECW     );
//RL78_DISPATCH_FN(rl78Morph_1_B4_DEC      );
//RL78_DISPATCH_FN(rl78Morph_1_B6_DECW     );
//RL78_DISPATCH_FN(rl78Morph_1_BX_DECW     );
//RL78_DISPATCH_FN(rl78Morph_1_B8_MOVW     );
//RL78_DISPATCH_FN(rl78Morph_1_B9_MOVW     );
//RL78_DISPATCH_FN(rl78Morph_1_BA_MOVW     );
//RL78_DISPATCH_FN(rl78Morph_1_BB_MOVW     );
//RL78_DISPATCH_FN(rl78Morph_1_BC_MOVW     );
//RL78_DISPATCH_FN(rl78Morph_1_BD_MOVW     );
//RL78_DISPATCH_FN(rl78Morph_1_BE_MOVW     );
//RL78_DISPATCH_FN(rl78Morph_1_BF_MOVW     );
//RL78_DISPATCH_FN(rl78Morph_1_CX_POP      );
//RL78_DISPATCH_FN(rl78Morph_1_CY_PUSH     );
//RL78_DISPATCH_FN(rl78Morph_1_C8_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_C9_MOVW     );
//RL78_DISPATCH_FN(rl78Morph_1_CA_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_CB_MOVW     );
//RL78_DISPATCH_FN(rl78Morph_1_CC_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_CD_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_CE_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_CF_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_DX_CMP0     );
//RL78_DISPATCH_FN(rl78Morph_1_D4_CMP0     );
//RL78_DISPATCH_FN(rl78Morph_1_D5_CMP0     );
//RL78_DISPATCH_FN(rl78Morph_1_D6_MULU     );
//RL78_DISPATCH_FN(rl78Morph_1_D7_RET      );
//RL78_DISPATCH_FN(rl78Morph_1_D8_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_D9_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_DC_BC       );
//RL78_DISPATCH_FN(rl78Morph_1_DD_BZ       );
//RL78_DISPATCH_FN(rl78Morph_1_DE_BNC      );
//RL78_DISPATCH_FN(rl78Morph_1_DF_BNZ      );
//RL78_DISPATCH_FN(rl78Morph_1_EX_ONEB     );
//RL78_DISPATCH_FN(rl78Morph_1_E4_ONEB     );
//RL78_DISPATCH_FN(rl78Morph_1_E5_ONEB     );
//RL78_DISPATCH_FN(rl78Morph_1_E6_ONEW     );
//RL78_DISPATCH_FN(rl78Morph_1_E7_ONEW     );
//RL78_DISPATCH_FN(rl78Morph_1_E8_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_E9_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_EC_BR       );
//RL78_DISPATCH_FN(rl78Morph_1_ED_BR       );
//RL78_DISPATCH_FN(rl78Morph_1_EE_BR       );
//RL78_DISPATCH_FN(rl78Morph_1_EF_BR       );
//RL78_DISPATCH_FN(rl78Morph_1_FX_CLRB     );
//RL78_DISPATCH_FN(rl78Morph_1_F4_CLRB     );
//RL78_DISPATCH_FN(rl78Morph_1_F5_CLRB     );
//RL78_DISPATCH_FN(rl78Morph_1_F6_CLRW     );
//RL78_DISPATCH_FN(rl78Morph_1_F7_CLRW     );
//RL78_DISPATCH_FN(rl78Morph_1_F8_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_F9_MOV      );
//RL78_DISPATCH_FN(rl78Morph_1_FC_CALL     );
//RL78_DISPATCH_FN(rl78Morph_1_FD_CALL     );
//RL78_DISPATCH_FN(rl78Morph_1_FE_CALL     );
//RL78_DISPATCH_FN(rl78Morph_1_XA_MOVW     );
//RL78_DISPATCH_FN(rl78Morph_1_XB_MOVW     );

//
// Default disassembler callback
//
//RL78_DISPATCH_FN(rl78MorphDefault);


#endif

