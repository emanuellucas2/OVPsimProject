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


#define BPORT1_REG_POFFSET              0x0
#define BPORT1_REG_PWMCFG_POFFSET       0x0
#define BPORT1_REG_PWMCFG               (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_PWMCFG_POFFSET)
#define BPORT1_REG_PWMCFG_PWMSCALE      0xf
#define BPORT1_REG_PWMCFG_PWMSCALE_GET(_v)  (_v & 0xf)
#define BPORT1_REG_PWMCFG_PWMSTICKY     (0x1 << 8)
#define BPORT1_REG_PWMCFG_PWMSTICKY_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_REG_PWMCFG_PWMZEROCMP    (0x1 << 9)
#define BPORT1_REG_PWMCFG_PWMZEROCMP_GET(_v)  ((_v >> 9) & 0x1)
#define BPORT1_REG_PWMCFG_PWMDEGLITCH   (0x1 << 10)
#define BPORT1_REG_PWMCFG_PWMDEGLITCH_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_REG_PWMCFG_PWMENALWAYS   (0x1 << 12)
#define BPORT1_REG_PWMCFG_PWMENALWAYS_GET(_v)  ((_v >> 12) & 0x1)
#define BPORT1_REG_PWMCFG_PWMENONESHOT  (0x1 << 13)
#define BPORT1_REG_PWMCFG_PWMENONESHOT_GET(_v)  ((_v >> 13) & 0x1)
#define BPORT1_REG_PWMCFG_PWMCMP0CENTER  (0x1 << 16)
#define BPORT1_REG_PWMCFG_PWMCMP0CENTER_GET(_v)  ((_v >> 16) & 0x1)
#define BPORT1_REG_PWMCFG_PWMCMP1CENTER  (0x1 << 17)
#define BPORT1_REG_PWMCFG_PWMCMP1CENTER_GET(_v)  ((_v >> 17) & 0x1)
#define BPORT1_REG_PWMCFG_PWMCMP2CENTER  (0x1 << 18)
#define BPORT1_REG_PWMCFG_PWMCMP2CENTER_GET(_v)  ((_v >> 18) & 0x1)
#define BPORT1_REG_PWMCFG_PWMCMP3CENTER  (0x1 << 19)
#define BPORT1_REG_PWMCFG_PWMCMP3CENTER_GET(_v)  ((_v >> 19) & 0x1)
#define BPORT1_REG_PWMCFG_PWMCMP0GANG   (0x1 << 24)
#define BPORT1_REG_PWMCFG_PWMCMP0GANG_GET(_v)  ((_v >> 24) & 0x1)
#define BPORT1_REG_PWMCFG_PWMCMP1GANG   (0x1 << 25)
#define BPORT1_REG_PWMCFG_PWMCMP1GANG_GET(_v)  ((_v >> 25) & 0x1)
#define BPORT1_REG_PWMCFG_PWMCMP2GANG   (0x1 << 26)
#define BPORT1_REG_PWMCFG_PWMCMP2GANG_GET(_v)  ((_v >> 26) & 0x1)
#define BPORT1_REG_PWMCFG_PWMCMP3GANG   (0x1 << 27)
#define BPORT1_REG_PWMCFG_PWMCMP3GANG_GET(_v)  ((_v >> 27) & 0x1)
#define BPORT1_REG_PWMCFG_PWMCMP0IP     (0x1 << 28)
#define BPORT1_REG_PWMCFG_PWMCMP0IP_GET(_v)  ((_v >> 28) & 0x1)
#define BPORT1_REG_PWMCFG_PWMCMP1IP     (0x1 << 29)
#define BPORT1_REG_PWMCFG_PWMCMP1IP_GET(_v)  ((_v >> 29) & 0x1)
#define BPORT1_REG_PWMCFG_PWMCMP2IP     (0x1 << 30)
#define BPORT1_REG_PWMCFG_PWMCMP2IP_GET(_v)  ((_v >> 30) & 0x1)
#define BPORT1_REG_PWMCFG_PWMCMP3IP     (0x1 << 31)
#define BPORT1_REG_PWMCFG_PWMCMP3IP_GET(_v)  ((_v >> 31) & 0x1)

#define BPORT1_REG_PWMCOUNT_POFFSET     0x8
#define BPORT1_REG_PWMCOUNT             (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_PWMCOUNT_POFFSET)

#define BPORT1_REG_PWMS_POFFSET         0x10
#define BPORT1_REG_PWMS                 (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_PWMS_POFFSET)

#define BPORT1_REG_PWMCMP0_POFFSET      0x20
#define BPORT1_REG_PWMCMP0              (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_PWMCMP0_POFFSET)
#define BPORT1_REG_PWMCMP0_CMP          0xffff
#define BPORT1_REG_PWMCMP0_CMP_GET(_v)  (_v & 0xffff)

#define BPORT1_REG_PWMCMP1_POFFSET      0x24
#define BPORT1_REG_PWMCMP1              (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_PWMCMP1_POFFSET)
#define BPORT1_REG_PWMCMP1_CMP          0xffff
#define BPORT1_REG_PWMCMP1_CMP_GET(_v)  (_v & 0xffff)

#define BPORT1_REG_PWMCMP2_POFFSET      0x28
#define BPORT1_REG_PWMCMP2              (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_PWMCMP2_POFFSET)
#define BPORT1_REG_PWMCMP2_CMP          0xffff
#define BPORT1_REG_PWMCMP2_CMP_GET(_v)  (_v & 0xffff)

#define BPORT1_REG_PWMCMP3_POFFSET      0x2c
#define BPORT1_REG_PWMCMP3              (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_PWMCMP3_POFFSET)
#define BPORT1_REG_PWMCMP3_CMP          0xffff
#define BPORT1_REG_PWMCMP3_CMP_GET(_v)  (_v & 0xffff)


#endif
