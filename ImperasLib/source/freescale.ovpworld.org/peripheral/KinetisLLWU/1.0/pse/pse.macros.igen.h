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
#define BPORT1_AB_PE1_POFFSET           0x0
#define BPORT1_AB_PE1                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PE1_POFFSET)
#define BPORT1_AB_PE1_WUPE0             0x3
#define BPORT1_AB_PE1_WUPE0_GET(_v)     (_v & 0x3)
#define BPORT1_AB_PE1_WUPE1             (0x3 << 2)
#define BPORT1_AB_PE1_WUPE1_GET(_v)     ((_v >> 2) & 0x3)
#define BPORT1_AB_PE1_WUPE2             (0x3 << 4)
#define BPORT1_AB_PE1_WUPE2_GET(_v)     ((_v >> 4) & 0x3)
#define BPORT1_AB_PE1_WUPE3             (0x3 << 6)
#define BPORT1_AB_PE1_WUPE3_GET(_v)     ((_v >> 6) & 0x3)

#define BPORT1_AB_PE2_POFFSET           0x1
#define BPORT1_AB_PE2                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PE2_POFFSET)
#define BPORT1_AB_PE2_WUPE4             0x3
#define BPORT1_AB_PE2_WUPE4_GET(_v)     (_v & 0x3)
#define BPORT1_AB_PE2_WUPE5             (0x3 << 2)
#define BPORT1_AB_PE2_WUPE5_GET(_v)     ((_v >> 2) & 0x3)
#define BPORT1_AB_PE2_WUPE6             (0x3 << 4)
#define BPORT1_AB_PE2_WUPE6_GET(_v)     ((_v >> 4) & 0x3)
#define BPORT1_AB_PE2_WUPE7             (0x3 << 6)
#define BPORT1_AB_PE2_WUPE7_GET(_v)     ((_v >> 6) & 0x3)

#define BPORT1_AB_PE3_POFFSET           0x2
#define BPORT1_AB_PE3                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PE3_POFFSET)
#define BPORT1_AB_PE3_WUPE10            (0x3 << 4)
#define BPORT1_AB_PE3_WUPE10_GET(_v)    ((_v >> 4) & 0x3)
#define BPORT1_AB_PE3_WUPE11            (0x3 << 6)
#define BPORT1_AB_PE3_WUPE11_GET(_v)    ((_v >> 6) & 0x3)
#define BPORT1_AB_PE3_WUPE8             0x3
#define BPORT1_AB_PE3_WUPE8_GET(_v)     (_v & 0x3)
#define BPORT1_AB_PE3_WUPE9             (0x3 << 2)
#define BPORT1_AB_PE3_WUPE9_GET(_v)     ((_v >> 2) & 0x3)

#define BPORT1_AB_PE4_POFFSET           0x3
#define BPORT1_AB_PE4                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PE4_POFFSET)
#define BPORT1_AB_PE4_WUPE12            0x3
#define BPORT1_AB_PE4_WUPE12_GET(_v)    (_v & 0x3)
#define BPORT1_AB_PE4_WUPE13            (0x3 << 2)
#define BPORT1_AB_PE4_WUPE13_GET(_v)    ((_v >> 2) & 0x3)
#define BPORT1_AB_PE4_WUPE14            (0x3 << 4)
#define BPORT1_AB_PE4_WUPE14_GET(_v)    ((_v >> 4) & 0x3)
#define BPORT1_AB_PE4_WUPE15            (0x3 << 6)
#define BPORT1_AB_PE4_WUPE15_GET(_v)    ((_v >> 6) & 0x3)

#define BPORT1_AB_ME_POFFSET            0x4
#define BPORT1_AB_ME                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ME_POFFSET)
#define BPORT1_AB_ME_WUME0              0x1
#define BPORT1_AB_ME_WUME0_GET(_v)      (_v & 0x1)
#define BPORT1_AB_ME_WUME1              (0x1 << 1)
#define BPORT1_AB_ME_WUME1_GET(_v)      ((_v >> 1) & 0x1)
#define BPORT1_AB_ME_WUME2              (0x1 << 2)
#define BPORT1_AB_ME_WUME2_GET(_v)      ((_v >> 2) & 0x1)
#define BPORT1_AB_ME_WUME3              (0x1 << 3)
#define BPORT1_AB_ME_WUME3_GET(_v)      ((_v >> 3) & 0x1)
#define BPORT1_AB_ME_WUME4              (0x1 << 4)
#define BPORT1_AB_ME_WUME4_GET(_v)      ((_v >> 4) & 0x1)
#define BPORT1_AB_ME_WUME5              (0x1 << 5)
#define BPORT1_AB_ME_WUME5_GET(_v)      ((_v >> 5) & 0x1)
#define BPORT1_AB_ME_WUME6              (0x1 << 6)
#define BPORT1_AB_ME_WUME6_GET(_v)      ((_v >> 6) & 0x1)
#define BPORT1_AB_ME_WUME7              (0x1 << 7)
#define BPORT1_AB_ME_WUME7_GET(_v)      ((_v >> 7) & 0x1)

#define BPORT1_AB_F1_POFFSET            0x5
#define BPORT1_AB_F1                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_F1_POFFSET)
#define BPORT1_AB_F1_WUF0               0x1
#define BPORT1_AB_F1_WUF0_GET(_v)       (_v & 0x1)
#define BPORT1_AB_F1_WUF1               (0x1 << 1)
#define BPORT1_AB_F1_WUF1_GET(_v)       ((_v >> 1) & 0x1)
#define BPORT1_AB_F1_WUF2               (0x1 << 2)
#define BPORT1_AB_F1_WUF2_GET(_v)       ((_v >> 2) & 0x1)
#define BPORT1_AB_F1_WUF3               (0x1 << 3)
#define BPORT1_AB_F1_WUF3_GET(_v)       ((_v >> 3) & 0x1)
#define BPORT1_AB_F1_WUF4               (0x1 << 4)
#define BPORT1_AB_F1_WUF4_GET(_v)       ((_v >> 4) & 0x1)
#define BPORT1_AB_F1_WUF5               (0x1 << 5)
#define BPORT1_AB_F1_WUF5_GET(_v)       ((_v >> 5) & 0x1)
#define BPORT1_AB_F1_WUF6               (0x1 << 6)
#define BPORT1_AB_F1_WUF6_GET(_v)       ((_v >> 6) & 0x1)
#define BPORT1_AB_F1_WUF7               (0x1 << 7)
#define BPORT1_AB_F1_WUF7_GET(_v)       ((_v >> 7) & 0x1)

#define BPORT1_AB_F2_POFFSET            0x6
#define BPORT1_AB_F2                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_F2_POFFSET)
#define BPORT1_AB_F2_WUF10              (0x1 << 2)
#define BPORT1_AB_F2_WUF10_GET(_v)      ((_v >> 2) & 0x1)
#define BPORT1_AB_F2_WUF11              (0x1 << 3)
#define BPORT1_AB_F2_WUF11_GET(_v)      ((_v >> 3) & 0x1)
#define BPORT1_AB_F2_WUF12              (0x1 << 4)
#define BPORT1_AB_F2_WUF12_GET(_v)      ((_v >> 4) & 0x1)
#define BPORT1_AB_F2_WUF13              (0x1 << 5)
#define BPORT1_AB_F2_WUF13_GET(_v)      ((_v >> 5) & 0x1)
#define BPORT1_AB_F2_WUF14              (0x1 << 6)
#define BPORT1_AB_F2_WUF14_GET(_v)      ((_v >> 6) & 0x1)
#define BPORT1_AB_F2_WUF15              (0x1 << 7)
#define BPORT1_AB_F2_WUF15_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_F2_WUF8               0x1
#define BPORT1_AB_F2_WUF8_GET(_v)       (_v & 0x1)
#define BPORT1_AB_F2_WUF9               (0x1 << 1)
#define BPORT1_AB_F2_WUF9_GET(_v)       ((_v >> 1) & 0x1)

#define BPORT1_AB_F3_POFFSET            0x7
#define BPORT1_AB_F3                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_F3_POFFSET)
#define BPORT1_AB_F3_MWUF0              0x1
#define BPORT1_AB_F3_MWUF0_GET(_v)      (_v & 0x1)
#define BPORT1_AB_F3_MWUF1              (0x1 << 1)
#define BPORT1_AB_F3_MWUF1_GET(_v)      ((_v >> 1) & 0x1)
#define BPORT1_AB_F3_MWUF2              (0x1 << 2)
#define BPORT1_AB_F3_MWUF2_GET(_v)      ((_v >> 2) & 0x1)
#define BPORT1_AB_F3_MWUF3              (0x1 << 3)
#define BPORT1_AB_F3_MWUF3_GET(_v)      ((_v >> 3) & 0x1)
#define BPORT1_AB_F3_MWUF4              (0x1 << 4)
#define BPORT1_AB_F3_MWUF4_GET(_v)      ((_v >> 4) & 0x1)
#define BPORT1_AB_F3_MWUF5              (0x1 << 5)
#define BPORT1_AB_F3_MWUF5_GET(_v)      ((_v >> 5) & 0x1)
#define BPORT1_AB_F3_MWUF6              (0x1 << 6)
#define BPORT1_AB_F3_MWUF6_GET(_v)      ((_v >> 6) & 0x1)
#define BPORT1_AB_F3_MWUF7              (0x1 << 7)
#define BPORT1_AB_F3_MWUF7_GET(_v)      ((_v >> 7) & 0x1)

#define BPORT1_AB_FILT1_POFFSET         0x8
#define BPORT1_AB_FILT1                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FILT1_POFFSET)
#define BPORT1_AB_FILT1_FILTE           (0x3 << 5)
#define BPORT1_AB_FILT1_FILTE_GET(_v)   ((_v >> 5) & 0x3)
#define BPORT1_AB_FILT1_FILTF           (0x1 << 7)
#define BPORT1_AB_FILT1_FILTF_GET(_v)   ((_v >> 7) & 0x1)
#define BPORT1_AB_FILT1_FILTSEL         0xf
#define BPORT1_AB_FILT1_FILTSEL_GET(_v)  (_v & 0xf)

#define BPORT1_AB_FILT2_POFFSET         0x9
#define BPORT1_AB_FILT2                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FILT2_POFFSET)
#define BPORT1_AB_FILT2_FILTE           (0x3 << 5)
#define BPORT1_AB_FILT2_FILTE_GET(_v)   ((_v >> 5) & 0x3)
#define BPORT1_AB_FILT2_FILTF           (0x1 << 7)
#define BPORT1_AB_FILT2_FILTF_GET(_v)   ((_v >> 7) & 0x1)
#define BPORT1_AB_FILT2_FILTSEL         0xf
#define BPORT1_AB_FILT2_FILTSEL_GET(_v)  (_v & 0xf)

#define BPORT1_AB_RST_POFFSET           0xa
#define BPORT1_AB_RST                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_RST_POFFSET)
#define BPORT1_AB_RST_LLRSTE            (0x1 << 1)
#define BPORT1_AB_RST_LLRSTE_GET(_v)    ((_v >> 1) & 0x1)
#define BPORT1_AB_RST_RSTFILT           0x1
#define BPORT1_AB_RST_RSTFILT_GET(_v)   (_v & 0x1)


#endif
