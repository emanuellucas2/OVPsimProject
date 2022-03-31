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


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                             Version 20211118.0
//
////////////////////////////////////////////////////////////////////////////////

#ifndef PSE_MACROS_IGEN_H
#define PSE_MACROS_IGEN_H               

// Before including this file in the application, define the indicated macros
// to fix the base address of each slave port.

// Set the macro 'BPORT1' to the base of port 'bport1'
#ifndef BPORT1
#error BPORT1 is undefined. It needs to be set to the port base address
#endif


#define BPORT1_AB_POFFSET               0x0
#define BPORT1_AB_REG0_CACHE_ID_POFFSET  0x0
#define BPORT1_AB_REG0_CACHE_ID         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG0_CACHE_ID_POFFSET)

#define BPORT1_AB_REG0_CACHE_TYPE_POFFSET  0x4
#define BPORT1_AB_REG0_CACHE_TYPE       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG0_CACHE_TYPE_POFFSET)

#define BPORT1_AB_REG1_CONTROL_POFFSET  0x100
#define BPORT1_AB_REG1_CONTROL          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG1_CONTROL_POFFSET)

#define BPORT1_AB_REG1_AUX_CONTROL_POFFSET  0x104
#define BPORT1_AB_REG1_AUX_CONTROL      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG1_AUX_CONTROL_POFFSET)

#define BPORT1_AB_REG1_TAG_RAM_CONTROL_POFFSET  0x108
#define BPORT1_AB_REG1_TAG_RAM_CONTROL  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG1_TAG_RAM_CONTROL_POFFSET)

#define BPORT1_AB_REG1_DATA_RAM_CONTROL_POFFSET  0x10c
#define BPORT1_AB_REG1_DATA_RAM_CONTROL  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG1_DATA_RAM_CONTROL_POFFSET)

#define BPORT1_AB_REG2_EV_COUNTER_CTRL_POFFSET  0x200
#define BPORT1_AB_REG2_EV_COUNTER_CTRL  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG2_EV_COUNTER_CTRL_POFFSET)

#define BPORT1_AB_REG2_EV_COUNTER1_CFG_POFFSET  0x204
#define BPORT1_AB_REG2_EV_COUNTER1_CFG  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG2_EV_COUNTER1_CFG_POFFSET)

#define BPORT1_AB_REG2_EV_COUNTER0_CFG_POFFSET  0x208
#define BPORT1_AB_REG2_EV_COUNTER0_CFG  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG2_EV_COUNTER0_CFG_POFFSET)

#define BPORT1_AB_REG2_EV_COUNTER1_POFFSET  0x20c
#define BPORT1_AB_REG2_EV_COUNTER1      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG2_EV_COUNTER1_POFFSET)

#define BPORT1_AB_REG2_EV_COUNTER0_POFFSET  0x210
#define BPORT1_AB_REG2_EV_COUNTER0      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG2_EV_COUNTER0_POFFSET)

#define BPORT1_AB_REG2_INT_MASKE_POFFSET  0x214
#define BPORT1_AB_REG2_INT_MASKE        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG2_INT_MASKE_POFFSET)

#define BPORT1_AB_REG2_INT_MASK_STATUSE_POFFSET  0x218
#define BPORT1_AB_REG2_INT_MASK_STATUSE  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG2_INT_MASK_STATUSE_POFFSET)

#define BPORT1_AB_REG2_INT_RAW_STATUSE_POFFSET  0x21c
#define BPORT1_AB_REG2_INT_RAW_STATUSE  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG2_INT_RAW_STATUSE_POFFSET)

#define BPORT1_AB_REG2_INT_CLEARE_POFFSET  0x220
#define BPORT1_AB_REG2_INT_CLEARE       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG2_INT_CLEARE_POFFSET)

#define BPORT1_AB_REG7_CACHE_SYNC_POFFSET  0x730
#define BPORT1_AB_REG7_CACHE_SYNC       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG7_CACHE_SYNC_POFFSET)

#define BPORT1_AB_REG7_INV_PA_POFFSET   0x770
#define BPORT1_AB_REG7_INV_PA           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG7_INV_PA_POFFSET)

#define BPORT1_AB_REG7_INV_WAY_POFFSET  0x77c
#define BPORT1_AB_REG7_INV_WAY          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG7_INV_WAY_POFFSET)

#define BPORT1_AB_REG7_CLEAN_PA_POFFSET  0x7b0
#define BPORT1_AB_REG7_CLEAN_PA         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG7_CLEAN_PA_POFFSET)

#define BPORT1_AB_REG7_CLEAN_INDEX_POFFSET  0x7b8
#define BPORT1_AB_REG7_CLEAN_INDEX      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG7_CLEAN_INDEX_POFFSET)

#define BPORT1_AB_REG7_CLEAN_WAY_POFFSET  0x7bc
#define BPORT1_AB_REG7_CLEAN_WAY        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG7_CLEAN_WAY_POFFSET)

#define BPORT1_AB_REG7_CLEAN_INV_PA_POFFSET  0x7f0
#define BPORT1_AB_REG7_CLEAN_INV_PA     (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG7_CLEAN_INV_PA_POFFSET)

#define BPORT1_AB_REG7_CLEAN_INV_INDEX_POFFSET  0x7f8
#define BPORT1_AB_REG7_CLEAN_INV_INDEX  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG7_CLEAN_INV_INDEX_POFFSET)

#define BPORT1_AB_REG7_CLEAN_INV_WAY_POFFSET  0x7fc
#define BPORT1_AB_REG7_CLEAN_INV_WAY    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG7_CLEAN_INV_WAY_POFFSET)

#define BPORT1_AB_REG9_D_LOCKDOWN0_POFFSET  0x900
#define BPORT1_AB_REG9_D_LOCKDOWN0      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG9_D_LOCKDOWN0_POFFSET)

#define BPORT1_AB_REG9_I_LOCKDOWN0_POFFSET  0x904
#define BPORT1_AB_REG9_I_LOCKDOWN0      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG9_I_LOCKDOWN0_POFFSET)

#define BPORT1_AB_REG9_D_LOCKDOWN1F_POFFSET  0x908
#define BPORT1_AB_REG9_D_LOCKDOWN1F     (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG9_D_LOCKDOWN1F_POFFSET)

#define BPORT1_AB_REG9_I_LOCKDOWN1F_POFFSET  0x90c
#define BPORT1_AB_REG9_I_LOCKDOWN1F     (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG9_I_LOCKDOWN1F_POFFSET)

#define BPORT1_AB_REG9_D_LOCKDOWN2F_POFFSET  0x910
#define BPORT1_AB_REG9_D_LOCKDOWN2F     (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG9_D_LOCKDOWN2F_POFFSET)

#define BPORT1_AB_REG9_I_LOCKDOWN2F_POFFSET  0x914
#define BPORT1_AB_REG9_I_LOCKDOWN2F     (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG9_I_LOCKDOWN2F_POFFSET)

#define BPORT1_AB_REG9_D_LOCKDOWN3F_POFFSET  0x918
#define BPORT1_AB_REG9_D_LOCKDOWN3F     (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG9_D_LOCKDOWN3F_POFFSET)

#define BPORT1_AB_REG9_I_LOCKDOWN3F_POFFSET  0x91c
#define BPORT1_AB_REG9_I_LOCKDOWN3F     (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG9_I_LOCKDOWN3F_POFFSET)

#define BPORT1_AB_REG9_D_LOCKDOWN4F_POFFSET  0x920
#define BPORT1_AB_REG9_D_LOCKDOWN4F     (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG9_D_LOCKDOWN4F_POFFSET)

#define BPORT1_AB_REG9_I_LOCKDOWN4F_POFFSET  0x924
#define BPORT1_AB_REG9_I_LOCKDOWN4F     (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG9_I_LOCKDOWN4F_POFFSET)

#define BPORT1_AB_REG9_D_LOCKDOWN5F_POFFSET  0x928
#define BPORT1_AB_REG9_D_LOCKDOWN5F     (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG9_D_LOCKDOWN5F_POFFSET)

#define BPORT1_AB_REG9_I_LOCKDOWN5F_POFFSET  0x92c
#define BPORT1_AB_REG9_I_LOCKDOWN5F     (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG9_I_LOCKDOWN5F_POFFSET)

#define BPORT1_AB_REG9_D_LOCKDOWN6F_POFFSET  0x930
#define BPORT1_AB_REG9_D_LOCKDOWN6F     (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG9_D_LOCKDOWN6F_POFFSET)

#define BPORT1_AB_REG9_I_LOCKDOWN6F_POFFSET  0x934
#define BPORT1_AB_REG9_I_LOCKDOWN6F     (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG9_I_LOCKDOWN6F_POFFSET)

#define BPORT1_AB_REG9_D_LOCKDOWN7F_POFFSET  0x938
#define BPORT1_AB_REG9_D_LOCKDOWN7F     (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG9_D_LOCKDOWN7F_POFFSET)

#define BPORT1_AB_REG9_I_LOCKDOWN7F_POFFSET  0x93c
#define BPORT1_AB_REG9_I_LOCKDOWN7F     (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG9_I_LOCKDOWN7F_POFFSET)

#define BPORT1_AB_REG9_LOCK_LINE_ENG_POFFSET  0x950
#define BPORT1_AB_REG9_LOCK_LINE_ENG    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG9_LOCK_LINE_ENG_POFFSET)

#define BPORT1_AB_REG9_UNLOCK_WAYG_POFFSET  0x954
#define BPORT1_AB_REG9_UNLOCK_WAYG      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG9_UNLOCK_WAYG_POFFSET)

#define BPORT1_AB_REG12_ADDR_FILT_START_POFFSET  0xc00
#define BPORT1_AB_REG12_ADDR_FILT_START  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG12_ADDR_FILT_START_POFFSET)

#define BPORT1_AB_REG12_ADDR_FILT_END_POFFSET  0xc04
#define BPORT1_AB_REG12_ADDR_FILT_END   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG12_ADDR_FILT_END_POFFSET)

#define BPORT1_AB_REG15_DEBUG_CTRL_POFFSET  0xf40
#define BPORT1_AB_REG15_DEBUG_CTRL      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG15_DEBUG_CTRL_POFFSET)

#define BPORT1_AB_REG15_PREFETCH_CTRL_POFFSET  0xf60
#define BPORT1_AB_REG15_PREFETCH_CTRL   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG15_PREFETCH_CTRL_POFFSET)

#define BPORT1_AB_REG15_POWER_CTRL_POFFSET  0xf80
#define BPORT1_AB_REG15_POWER_CTRL      (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_REG15_POWER_CTRL_POFFSET)


#endif
