/*
 * QEMU System Controller.
 *
 * Copyright (c) 2003 Fabrice Bellard
 * Copyright (c) 2006 Openedhand Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
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

#ifndef SYSCONTROL_H_
#define SYSCONTROL_H_

// number of registers
#define GT_REGS             (0x1000 >> 2)

/* CPU Configuration */
#define GT_CPU              (0x000 >> 2)
#define GT_MULTI            (0x120 >> 2)

/* CPU Address Decode */
#define GT_SCS10LD          (0x008 >> 2)
#define GT_SCS10HD          (0x010 >> 2)
#define GT_SCS32LD          (0x018 >> 2)
#define GT_SCS32HD          (0x020 >> 2)
#define GT_CS20LD           (0x028 >> 2)
#define GT_CS20HD           (0x030 >> 2)
#define GT_CS3BOOTLD        (0x038 >> 2)
#define GT_CS3BOOTHD        (0x040 >> 2)
#define GT_PCI0IOLD         (0x048 >> 2)
#define GT_PCI0IOHD         (0x050 >> 2)
#define GT_PCI0M0LD         (0x058 >> 2)
#define GT_PCI0M0HD         (0x060 >> 2)
#define GT_PCI0M1LD         (0x080 >> 2)
#define GT_PCI0M1HD         (0x088 >> 2)
#define GT_PCI1IOLD         (0x090 >> 2)
#define GT_PCI1IOHD         (0x098 >> 2)
#define GT_PCI1M0LD         (0x0a0 >> 2)
#define GT_PCI1M0HD         (0x0a8 >> 2)
#define GT_PCI1M1LD         (0x0b0 >> 2)
#define GT_PCI1M1HD         (0x0b8 >> 2)
#define GT_ISD              (0x068 >> 2)

#define GT_SCS10AR          (0x0d0 >> 2)
#define GT_SCS32AR          (0x0d8 >> 2)
#define GT_CS20R            (0x0e0 >> 2)
#define GT_CS3BOOTR         (0x0e8 >> 2)

#define GT_PCI0IOREMAP      (0x0f0 >> 2)
#define GT_PCI0M0REMAP      (0x0f8 >> 2)
#define GT_PCI0M1REMAP      (0x100 >> 2)
#define GT_PCI1IOREMAP      (0x108 >> 2)
#define GT_PCI1M0REMAP      (0x110 >> 2)
#define GT_PCI1M1REMAP      (0x118 >> 2)

/* CPU Error Report */
#define GT_CPUERR_ADDRLO        (0x070 >> 2)
#define GT_CPUERR_ADDRHI        (0x078 >> 2)
#define GT_CPUERR_DATALO        (0x128 >> 2)        /* GT-64120A only  */
#define GT_CPUERR_DATAHI        (0x130 >> 2)        /* GT-64120A only  */
#define GT_CPUERR_PARITY        (0x138 >> 2)        /* GT-64120A only  */

/* CPU Sync Barrier */
#define GT_PCI0SYNC         (0x0c0 >> 2)
#define GT_PCI1SYNC         (0x0c8 >> 2)

/* SDRAM and Device Address Decode */
#define GT_SCS0LD           (0x400 >> 2)
#define GT_SCS0HD           (0x404 >> 2)
#define GT_SCS1LD           (0x408 >> 2)
#define GT_SCS1HD           (0x40c >> 2)
#define GT_SCS2LD           (0x410 >> 2)
#define GT_SCS2HD           (0x414 >> 2)
#define GT_SCS3LD           (0x418 >> 2)
#define GT_SCS3HD           (0x41c >> 2)
#define GT_CS0LD            (0x420 >> 2)
#define GT_CS0HD            (0x424 >> 2)
#define GT_CS1LD            (0x428 >> 2)
#define GT_CS1HD            (0x42c >> 2)
#define GT_CS2LD            (0x430 >> 2)
#define GT_CS2HD            (0x434 >> 2)
#define GT_CS3LD            (0x438 >> 2)
#define GT_CS3HD            (0x43c >> 2)
#define GT_BOOTLD           (0x440 >> 2)
#define GT_BOOTHD           (0x444 >> 2)
#define GT_ADERR            (0x470 >> 2)

/* SDRAM Configuration */
#define GT_SDRAM_CFG        (0x448 >> 2)
#define GT_SDRAM_OPMODE     (0x474 >> 2)
#define GT_SDRAM_BM         (0x478 >> 2)
#define GT_SDRAM_ADDRDEC    (0x47c >> 2)

/* SDRAM Parameters */
#define GT_SDRAM_B0         (0x44c >> 2)
#define GT_SDRAM_B1         (0x450 >> 2)
#define GT_SDRAM_B2         (0x454 >> 2)
#define GT_SDRAM_B3         (0x458 >> 2)

/* Device Parameters */
#define GT_DEV_B0           (0x45c >> 2)
#define GT_DEV_B1           (0x460 >> 2)
#define GT_DEV_B2           (0x464 >> 2)
#define GT_DEV_B3           (0x468 >> 2)
#define GT_DEV_BOOT         (0x46c >> 2)

/* ECC */
#define GT_ECC_ERRDATALO    (0x480 >> 2)        /* GT-64120A only  */
#define GT_ECC_ERRDATAHI    (0x484 >> 2)        /* GT-64120A only  */
#define GT_ECC_MEM      (0x488 >> 2)        /* GT-64120A only  */
#define GT_ECC_CALC     (0x48c >> 2)        /* GT-64120A only  */
#define GT_ECC_ERRADDR      (0x490 >> 2)        /* GT-64120A only  */

/* DMA Record */
#define GT_DMA0_CNT         (0x800 >> 2)
#define GT_DMA1_CNT         (0x804 >> 2)
#define GT_DMA2_CNT         (0x808 >> 2)
#define GT_DMA3_CNT         (0x80c >> 2)
#define GT_DMA0_SA          (0x810 >> 2)
#define GT_DMA1_SA          (0x814 >> 2)
#define GT_DMA2_SA          (0x818 >> 2)
#define GT_DMA3_SA          (0x81c >> 2)
#define GT_DMA0_DA          (0x820 >> 2)
#define GT_DMA1_DA          (0x824 >> 2)
#define GT_DMA2_DA          (0x828 >> 2)
#define GT_DMA3_DA          (0x82c >> 2)
#define GT_DMA0_NEXT        (0x830 >> 2)
#define GT_DMA1_NEXT        (0x834 >> 2)
#define GT_DMA2_NEXT        (0x838 >> 2)
#define GT_DMA3_NEXT        (0x83c >> 2)
#define GT_DMA0_CUR         (0x870 >> 2)
#define GT_DMA1_CUR         (0x874 >> 2)
#define GT_DMA2_CUR         (0x878 >> 2)
#define GT_DMA3_CUR         (0x87c >> 2)

/* DMA Channel Control */
#define GT_DMA0_CTRL        (0x840 >> 2)
#define GT_DMA1_CTRL        (0x844 >> 2)
#define GT_DMA2_CTRL        (0x848 >> 2)
#define GT_DMA3_CTRL        (0x84c >> 2)

/* DMA Arbiter */
#define GT_DMA_ARB          (0x860 >> 2)

/* Timer/Counter */
#define GT_TC0          (0x850 >> 2)
#define GT_TC1          (0x854 >> 2)
#define GT_TC2          (0x858 >> 2)
#define GT_TC3          (0x85c >> 2)
#define GT_TC_CONTROL       (0x864 >> 2)

/* PCI Internal */
#define GT_PCI0_CMD         (0xc00 >> 2)
#define GT_PCI0_TOR         (0xc04 >> 2)
#define GT_PCI0_BS_SCS10        (0xc08 >> 2)
#define GT_PCI0_BS_SCS32        (0xc0c >> 2)
#define GT_PCI0_BS_CS20     (0xc10 >> 2)
#define GT_PCI0_BS_CS3BT        (0xc14 >> 2)
#define GT_PCI1_IACK        (0xc30 >> 2)
#define GT_PCI0_IACK        (0xc34 >> 2)
#define GT_PCI0_BARE        (0xc3c >> 2)
#define GT_PCI0_PREFMBR     (0xc40 >> 2)
#define GT_PCI0_SCS10_BAR       (0xc48 >> 2)
#define GT_PCI0_SCS32_BAR       (0xc4c >> 2)
#define GT_PCI0_CS20_BAR        (0xc50 >> 2)
#define GT_PCI0_CS3BT_BAR       (0xc54 >> 2)
#define GT_PCI0_SSCS10_BAR      (0xc58 >> 2)
#define GT_PCI0_SSCS32_BAR      (0xc5c >> 2)
#define GT_PCI0_SCS3BT_BAR      (0xc64 >> 2)
#define GT_PCI1_CMD         (0xc80 >> 2)
#define GT_PCI1_TOR         (0xc84 >> 2)
#define GT_PCI1_BS_SCS10        (0xc88 >> 2)
#define GT_PCI1_BS_SCS32        (0xc8c >> 2)
#define GT_PCI1_BS_CS20     (0xc90 >> 2)
#define GT_PCI1_BS_CS3BT        (0xc94 >> 2)
#define GT_PCI1_BARE        (0xcbc >> 2)
#define GT_PCI1_PREFMBR     (0xcc0 >> 2)
#define GT_PCI1_SCS10_BAR       (0xcc8 >> 2)
#define GT_PCI1_SCS32_BAR       (0xccc >> 2)
#define GT_PCI1_CS20_BAR        (0xcd0 >> 2)
#define GT_PCI1_CS3BT_BAR       (0xcd4 >> 2)
#define GT_PCI1_SSCS10_BAR      (0xcd8 >> 2)
#define GT_PCI1_SSCS32_BAR      (0xcdc >> 2)
#define GT_PCI1_SCS3BT_BAR      (0xce4 >> 2)
#define GT_PCI1_CFGADDR     (0xcf0 >> 2)
#define GT_PCI1_CFGDATA     (0xcf4 >> 2)
#define GT_PCI0_CFGADDR     (0xcf8 >> 2)
#define GT_PCI0_CFGDATA     (0xcfc >> 2)

/* Interrupts */
#define GT_INTRCAUSE        (0xc18 >> 2)
#define GT_INTRMASK         (0xc1c >> 2)
#define GT_PCI0_ICMASK      (0xc24 >> 2)
#define GT_PCI0_SERR0MASK       (0xc28 >> 2)
#define GT_CPU_INTSEL       (0xc70 >> 2)
#define GT_PCI0_INTSEL      (0xc74 >> 2)
#define GT_HINTRCAUSE       (0xc98 >> 2)
#define GT_HINTRMASK        (0xc9c >> 2)
#define GT_PCI0_HICMASK     (0xca4 >> 2)
#define GT_PCI1_SERR1MASK       (0xca8 >> 2)

const char *regDesc[0x400] =  {
    [GT_CPU]            = "CPU Interface Configuration",
    [GT_ISD]            = "Internal Space Decode",
    [GT_CS3LD]          = "CS[3]* Low Decode Address",
    [GT_CS3HD]          = "CS[3]* High Decode Address",
    [GT_BOOTLD]         = "Boot CS* Low Decode Address",
    [GT_BOOTHD]         = "Boot CS* High Decode Address",
    [GT_SCS0LD]         = "SCS[0]* Low Decode Address",
    [GT_SCS0HD]         = "SCS[0]* High Decode Address",
    [GT_SCS1LD]         = "SCS[1]* Low Decode Address",
    [GT_SCS1HD]         = "SCS[1]* High Decode Address",
    [GT_SCS2LD]         = "SCS[2]* Low Decode Address",
    [GT_SCS2HD]         = "SCS[2]* High Decode Address",
    [GT_SCS3LD]         = "SCS[3]* Low Decode Address",
    [GT_SCS3HD]         = "SCS[3]* High Decode Address",
    [GT_SCS10LD]        = "SCS[1:0]* Low Decode Address",
    [GT_SCS10HD]        = "SCS[1:0]* High Decode Address",
    [GT_SCS32LD]        = "SCS[3:2]* Low Decode Address",
    [GT_SCS32HD]        = "SCS[3:2]* High Decode Address",

    [GT_PCI0_CMD]       = "PCI Command",
    [GT_PCI0_TOR]       = "PCI TimeOut & ReTry",
    [GT_PCI0_CFGADDR]   = "PCI Configuration Address",
    [GT_PCI0_CFGDATA]   = "PCI Configuration Data",

    [GT_PCI0IOLD]       = "PCI I/O Low Decode Address",
    [GT_PCI0IOHD]       = "PCI I/O High Decode Address",
    [GT_PCI0M0LD]       = "PCI Memory 0 Low Decode Address",
    [GT_PCI0M0HD]       = "PCI Memory 0 High Decode Address",
    [GT_PCI0M1LD]       = "PCI Memory 1 Low Decode Address",
    [GT_PCI0M1HD]       = "PCI Memory 1 High Decode Address",
//    [GT_PCI1IOLD]       = (0x090 >> 2)
//    [GT_PCI1IOHD]       = (0x098 >> 2)
//    [GT_PCI1M0LD]       = (0x0a0 >> 2)
//    [GT_PCI1M0HD]       = (0x0a8 >> 2)
//    [GT_PCI1M1LD]       = (0x0b0 >> 2)
//    [GT_PCI1M1HD]       = (0x0b8 >> 2)
    [GT_PCI0IOREMAP]    = "PCI I/O Address Remap",
    [GT_PCI0M0REMAP]    = "PCI Memory 0 Address Remap",
    [GT_PCI0M1REMAP]    = "PCI Memory 1 Address Remap",
//    [GT_PCI1IOREMAP]    = (0x108 >> 2)
//    [GT_PCI1M0REMAP]    = (0x110 >> 2)
//    [GT_PCI1M1REMAP]    = (0x118 >> 2)


    [GT_SDRAM_CFG]      = "SDRAM Configuration",
    [GT_SDRAM_BM]       = "SDRAM Burst Mode",
    [GT_SDRAM_ADDRDEC]  = "SDRAM Address Decode",
    [GT_SDRAM_B0]       = "SDRAM Bank0 Parameters",
    [GT_SDRAM_B1]       = "SDRAM Bank1 Parameters",
    [GT_SDRAM_B2]       = "SDRAM Bank2 Parameters",
    [GT_SDRAM_B3]       = "SDRAM Bank3 Parameters",


    [GT_INTRCAUSE]      = "Interrupt Cause Register",
//    [GT_INTRMASK]       = (0xc1c >> 2)
//    [GT_PCI0_ICMASK]    = (0xc24 >> 2)
//    [GT_PCI0_SERR0MASK] =     (0xc28 >> 2)
//    [GT_CPU_INTSEL]     = (0xc70 >> 2)
//    [GT_PCI0_INTSEL]    = (0xc74 >> 2)
//    [GT_HINTRCAUSE]     = (0xc98 >> 2)
//    [GT_HINTRMASK]      = (0xc9c >> 2)
//    [GT_PCI0_HICMASK]   = (0xca4 >> 2)
//    [GT_PCI1_SERR1MASK] =     (0xca8 >> 2)

//      [GT_PCI0_CMD]       = (0xc00 >> 2)
//      [GT_PCI0_TOR]       = (0xc04 >> 2)
//      [GT_PCI0_BS_SCS10]  =     (0xc08 >> 2)
//      [GT_PCI0_BS_SCS32]  =     (0xc0c >> 2)
//      [GT_PCI0_BS_CS20]   = (0xc10 >> 2)
//      [GT_PCI0_BS_CS3BT]  =     (0xc14 >> 2)
//      [GT_PCI1_IACK]      = (0xc30 >> 2)
      [GT_PCI0_IACK]      = "PCI Interrupt Acknowledge Virtual Register",
//      [GT_PCI0_BARE]      = (0xc3c >> 2)
//      [GT_PCI0_PREFMBR]   = (0xc40 >> 2)
//      [GT_PCI0_SCS10_BAR] =     (0xc48 >> 2)
//      [GT_PCI0_SCS32_BAR] =     (0xc4c >> 2)
//      [GT_PCI0_CS20_BAR]  =     (0xc50 >> 2)
//      [GT_PCI0_CS3BT_BAR] =     (0xc54 >> 2)
//      [GT_PCI0_SSCS10_BAR]=     (0xc58 >> 2)
//      [GT_PCI0_SSCS32_BAR]=     (0xc5c >> 2)
//      [GT_PCI0_SCS3BT_BAR]=     (0xc64 >> 2)
//      [GT_PCI1_CMD]       = (0xc80 >> 2)
//      [GT_PCI1_TOR]       = (0xc84 >> 2)
//      [GT_PCI1_BS_SCS10]  =     (0xc88 >> 2)
//      [GT_PCI1_BS_SCS32]  =     (0xc8c >> 2)
//      [GT_PCI1_BS_CS20]   = (0xc90 >> 2)
//      [GT_PCI1_BS_CS3BT]  =     (0xc94 >> 2)
//      [GT_PCI1_BARE]      = (0xcbc >> 2)
//      [GT_PCI1_PREFMBR]   = (0xcc0 >> 2)
//      [GT_PCI1_SCS10_BAR] =     (0xcc8 >> 2)
//      [GT_PCI1_SCS32_BAR] =     (0xccc >> 2)
//      [GT_PCI1_CS20_BAR]  =     (0xcd0 >> 2)
//      [GT_PCI1_CS3BT_BAR] =     (0xcd4 >> 2)
//      [GT_PCI1_SSCS10_BAR]=     (0xcd8 >> 2)
//      [GT_PCI1_SSCS32_BAR]=     (0xcdc >> 2)
//      [GT_PCI1_SCS3BT_BAR]=     (0xce4 >> 2)
//      [GT_PCI1_CFGADDR]   = (0xcf0 >> 2)
//      [GT_PCI1_CFGDATA]   = (0xcf4 >> 2)
//      [GT_PCI0_CFGADDR]   = (0xcf8 >> 2)
//      [GT_PCI0_CFGDATA]   = (0xcfc >> 2)

};

#endif /*SYSCONTROL_H_*/
