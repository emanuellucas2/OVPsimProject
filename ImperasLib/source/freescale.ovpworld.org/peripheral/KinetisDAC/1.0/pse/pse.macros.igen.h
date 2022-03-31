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
#define BPORT1_AB_DAT0L_POFFSET         0x0
#define BPORT1_AB_DAT0L                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT0L_POFFSET)
#define BPORT1_AB_DAT0L_DATA            0xff
#define BPORT1_AB_DAT0L_DATA_GET(_v)    (_v & 0xff)

#define BPORT1_AB_DAT0H_POFFSET         0x1
#define BPORT1_AB_DAT0H                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT0H_POFFSET)
#define BPORT1_AB_DAT0H_DATA            0xf
#define BPORT1_AB_DAT0H_DATA_GET(_v)    (_v & 0xf)

#define BPORT1_AB_DAT1L_POFFSET         0x2
#define BPORT1_AB_DAT1L                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT1L_POFFSET)
#define BPORT1_AB_DAT1L_DATA            0xff
#define BPORT1_AB_DAT1L_DATA_GET(_v)    (_v & 0xff)

#define BPORT1_AB_DAT1H_POFFSET         0x3
#define BPORT1_AB_DAT1H                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT1H_POFFSET)
#define BPORT1_AB_DAT1H_DATA            0xf
#define BPORT1_AB_DAT1H_DATA_GET(_v)    (_v & 0xf)

#define BPORT1_AB_DAT2L_POFFSET         0x4
#define BPORT1_AB_DAT2L                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT2L_POFFSET)
#define BPORT1_AB_DAT2L_DATA            0xff
#define BPORT1_AB_DAT2L_DATA_GET(_v)    (_v & 0xff)

#define BPORT1_AB_DAT2H_POFFSET         0x5
#define BPORT1_AB_DAT2H                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT2H_POFFSET)
#define BPORT1_AB_DAT2H_DATA            0xf
#define BPORT1_AB_DAT2H_DATA_GET(_v)    (_v & 0xf)

#define BPORT1_AB_DAT3L_POFFSET         0x6
#define BPORT1_AB_DAT3L                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT3L_POFFSET)
#define BPORT1_AB_DAT3L_DATA            0xff
#define BPORT1_AB_DAT3L_DATA_GET(_v)    (_v & 0xff)

#define BPORT1_AB_DAT3H_POFFSET         0x7
#define BPORT1_AB_DAT3H                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT3H_POFFSET)
#define BPORT1_AB_DAT3H_DATA            0xf
#define BPORT1_AB_DAT3H_DATA_GET(_v)    (_v & 0xf)

#define BPORT1_AB_DAT4L_POFFSET         0x8
#define BPORT1_AB_DAT4L                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT4L_POFFSET)
#define BPORT1_AB_DAT4L_DATA            0xff
#define BPORT1_AB_DAT4L_DATA_GET(_v)    (_v & 0xff)

#define BPORT1_AB_DAT4H_POFFSET         0x9
#define BPORT1_AB_DAT4H                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT4H_POFFSET)
#define BPORT1_AB_DAT4H_DATA            0xf
#define BPORT1_AB_DAT4H_DATA_GET(_v)    (_v & 0xf)

#define BPORT1_AB_DAT5L_POFFSET         0xa
#define BPORT1_AB_DAT5L                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT5L_POFFSET)

#define BPORT1_AB_DAT5H_POFFSET         0xb
#define BPORT1_AB_DAT5H                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT5H_POFFSET)
#define BPORT1_AB_DAT5H_DATA            0xf
#define BPORT1_AB_DAT5H_DATA_GET(_v)    (_v & 0xf)

#define BPORT1_AB_DAT6L_POFFSET         0xc
#define BPORT1_AB_DAT6L                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT6L_POFFSET)
#define BPORT1_AB_DAT6L_DATA            0xff
#define BPORT1_AB_DAT6L_DATA_GET(_v)    (_v & 0xff)

#define BPORT1_AB_DAT6H_POFFSET         0xd
#define BPORT1_AB_DAT6H                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT6H_POFFSET)
#define BPORT1_AB_DAT6H_DATA            0xf
#define BPORT1_AB_DAT6H_DATA_GET(_v)    (_v & 0xf)

#define BPORT1_AB_DAT7L_POFFSET         0xe
#define BPORT1_AB_DAT7L                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT7L_POFFSET)
#define BPORT1_AB_DAT7L_DATA            0xff
#define BPORT1_AB_DAT7L_DATA_GET(_v)    (_v & 0xff)

#define BPORT1_AB_DAT7H_POFFSET         0xf
#define BPORT1_AB_DAT7H                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT7H_POFFSET)
#define BPORT1_AB_DAT7H_DATA            0xf
#define BPORT1_AB_DAT7H_DATA_GET(_v)    (_v & 0xf)

#define BPORT1_AB_DAT8L_POFFSET         0x10
#define BPORT1_AB_DAT8L                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT8L_POFFSET)
#define BPORT1_AB_DAT8L_DATA            0xff
#define BPORT1_AB_DAT8L_DATA_GET(_v)    (_v & 0xff)

#define BPORT1_AB_DAT8H_POFFSET         0x11
#define BPORT1_AB_DAT8H                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT8H_POFFSET)
#define BPORT1_AB_DAT8H_DATA            0xf
#define BPORT1_AB_DAT8H_DATA_GET(_v)    (_v & 0xf)

#define BPORT1_AB_DAT9L_POFFSET         0x12
#define BPORT1_AB_DAT9L                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT9L_POFFSET)
#define BPORT1_AB_DAT9L_DATA            0xff
#define BPORT1_AB_DAT9L_DATA_GET(_v)    (_v & 0xff)

#define BPORT1_AB_DAT9H_POFFSET         0x13
#define BPORT1_AB_DAT9H                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT9H_POFFSET)
#define BPORT1_AB_DAT9H_DATA            0xf
#define BPORT1_AB_DAT9H_DATA_GET(_v)    (_v & 0xf)

#define BPORT1_AB_DAT10L_POFFSET        0x14
#define BPORT1_AB_DAT10L                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT10L_POFFSET)
#define BPORT1_AB_DAT10L_DATA           0xff
#define BPORT1_AB_DAT10L_DATA_GET(_v)   (_v & 0xff)

#define BPORT1_AB_DAT10H_POFFSET        0x15
#define BPORT1_AB_DAT10H                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT10H_POFFSET)
#define BPORT1_AB_DAT10H_DATA           0xf
#define BPORT1_AB_DAT10H_DATA_GET(_v)   (_v & 0xf)

#define BPORT1_AB_DAT11L_POFFSET        0x16
#define BPORT1_AB_DAT11L                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT11L_POFFSET)
#define BPORT1_AB_DAT11L_DATA           0xff
#define BPORT1_AB_DAT11L_DATA_GET(_v)   (_v & 0xff)

#define BPORT1_AB_DAT11H_POFFSET        0x17
#define BPORT1_AB_DAT11H                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT11H_POFFSET)
#define BPORT1_AB_DAT11H_DATA           0xf
#define BPORT1_AB_DAT11H_DATA_GET(_v)   (_v & 0xf)

#define BPORT1_AB_DAT12L_POFFSET        0x18
#define BPORT1_AB_DAT12L                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT12L_POFFSET)
#define BPORT1_AB_DAT12L_DATA           0xff
#define BPORT1_AB_DAT12L_DATA_GET(_v)   (_v & 0xff)

#define BPORT1_AB_DAT12H_POFFSET        0x19
#define BPORT1_AB_DAT12H                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT12H_POFFSET)
#define BPORT1_AB_DAT12H_DATA           0xf
#define BPORT1_AB_DAT12H_DATA_GET(_v)   (_v & 0xf)

#define BPORT1_AB_DAT13L_POFFSET        0x1a
#define BPORT1_AB_DAT13L                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT13L_POFFSET)
#define BPORT1_AB_DAT13L_DATA           0xff
#define BPORT1_AB_DAT13L_DATA_GET(_v)   (_v & 0xff)

#define BPORT1_AB_DAT13H_POFFSET        0x1b
#define BPORT1_AB_DAT13H                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT13H_POFFSET)
#define BPORT1_AB_DAT13H_DATA           0xf
#define BPORT1_AB_DAT13H_DATA_GET(_v)   (_v & 0xf)

#define BPORT1_AB_DAT14L_POFFSET        0x1c
#define BPORT1_AB_DAT14L                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT14L_POFFSET)
#define BPORT1_AB_DAT14L_DATA           0xff
#define BPORT1_AB_DAT14L_DATA_GET(_v)   (_v & 0xff)

#define BPORT1_AB_DAT14H_POFFSET        0x1d
#define BPORT1_AB_DAT14H                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT14H_POFFSET)
#define BPORT1_AB_DAT14H_DATA           0xf
#define BPORT1_AB_DAT14H_DATA_GET(_v)   (_v & 0xf)

#define BPORT1_AB_DAT15L_POFFSET        0x1e
#define BPORT1_AB_DAT15L                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT15L_POFFSET)
#define BPORT1_AB_DAT15L_DATA           0xff
#define BPORT1_AB_DAT15L_DATA_GET(_v)   (_v & 0xff)

#define BPORT1_AB_DAT15H_POFFSET        0x1f
#define BPORT1_AB_DAT15H                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DAT15H_POFFSET)
#define BPORT1_AB_DAT15H_DATA           0xf
#define BPORT1_AB_DAT15H_DATA_GET(_v)   (_v & 0xf)

#define BPORT1_AB_SR_POFFSET            0x20
#define BPORT1_AB_SR                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SR_POFFSET)
#define BPORT1_AB_SR_DACBFRPBF          0x1
#define BPORT1_AB_SR_DACBFRPBF_GET(_v)  (_v & 0x1)
#define BPORT1_AB_SR_DACBFRPTF          (0x1 << 1)
#define BPORT1_AB_SR_DACBFRPTF_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_SR_DACBFWMF           (0x1 << 2)
#define BPORT1_AB_SR_DACBFWMF_GET(_v)   ((_v >> 2) & 0x1)

#define BPORT1_AB_C0_POFFSET            0x21
#define BPORT1_AB_C0                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C0_POFFSET)
#define BPORT1_AB_C0_DACBBIEN           0x1
#define BPORT1_AB_C0_DACBBIEN_GET(_v)   (_v & 0x1)
#define BPORT1_AB_C0_DACBTIEN           (0x1 << 1)
#define BPORT1_AB_C0_DACBTIEN_GET(_v)   ((_v >> 1) & 0x1)
#define BPORT1_AB_C0_DACBWIEN           (0x1 << 2)
#define BPORT1_AB_C0_DACBWIEN_GET(_v)   ((_v >> 2) & 0x1)
#define BPORT1_AB_C0_LPEN               (0x1 << 3)
#define BPORT1_AB_C0_LPEN_GET(_v)       ((_v >> 3) & 0x1)
#define BPORT1_AB_C0_DACSWTRG           (0x1 << 4)
#define BPORT1_AB_C0_DACSWTRG_GET(_v)   ((_v >> 4) & 0x1)
#define BPORT1_AB_C0_DACTRGSEL          (0x1 << 5)
#define BPORT1_AB_C0_DACTRGSEL_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_C0_DACRFS             (0x1 << 6)
#define BPORT1_AB_C0_DACRFS_GET(_v)     ((_v >> 6) & 0x1)
#define BPORT1_AB_C0_DACEN              (0x1 << 7)
#define BPORT1_AB_C0_DACEN_GET(_v)      ((_v >> 7) & 0x1)

#define BPORT1_AB_C1_POFFSET            0x22
#define BPORT1_AB_C1                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C1_POFFSET)
#define BPORT1_AB_C1_DACBFEN            0x1
#define BPORT1_AB_C1_DACBFEN_GET(_v)    (_v & 0x1)
#define BPORT1_AB_C1_DACBFMD            (0x3 << 1)
#define BPORT1_AB_C1_DACBFMD_GET(_v)    ((_v >> 1) & 0x3)
#define BPORT1_AB_C1_DACBFWM            (0x3 << 3)
#define BPORT1_AB_C1_DACBFWM_GET(_v)    ((_v >> 3) & 0x3)
#define BPORT1_AB_C1_DMAEN              (0x1 << 7)
#define BPORT1_AB_C1_DMAEN_GET(_v)      ((_v >> 7) & 0x1)

#define BPORT1_AB_C2_POFFSET            0x23
#define BPORT1_AB_C2                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C2_POFFSET)
#define BPORT1_AB_C2_DACBFUP            0xf
#define BPORT1_AB_C2_DACBFUP_GET(_v)    (_v & 0xf)
#define BPORT1_AB_C2_DACBFRP            (0xf << 4)
#define BPORT1_AB_C2_DACBFRP_GET(_v)    ((_v >> 4) & 0xf)


#endif
