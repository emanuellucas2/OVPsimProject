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
#define BPORT1_AB_CTRL_POFFSET          0x0
#define BPORT1_AB_CTRL                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CTRL_POFFSET)
#define BPORT1_AB_CTRL_FORCE_RST        (0x1 << 31)
#define BPORT1_AB_CTRL_FORCE_RST_GET(_v)  ((_v >> 31) & 0x1)
#define BPORT1_AB_CTRL_PCFG_PROG_B      (0x1 << 30)
#define BPORT1_AB_CTRL_PCFG_PROG_B_GET(_v)  ((_v >> 30) & 0x1)
#define BPORT1_AB_CTRL_PCFG_POR_CNT_4K  (0x1 << 29)
#define BPORT1_AB_CTRL_PCFG_POR_CNT_4K_GET(_v)  ((_v >> 29) & 0x1)
#define BPORT1_AB_CTRL_PCAP_PR          (0x1 << 27)
#define BPORT1_AB_CTRL_PCAP_PR_GET(_v)  ((_v >> 27) & 0x1)
#define BPORT1_AB_CTRL_PCAP_MODE        (0x1 << 26)
#define BPORT1_AB_CTRL_PCAP_MODE_GET(_v)  ((_v >> 26) & 0x1)
#define BPORT1_AB_CTRL_PCAP_RATE_EN     (0x1 << 25)
#define BPORT1_AB_CTRL_PCAP_RATE_EN_GET(_v)  ((_v >> 25) & 0x1)
#define BPORT1_AB_CTRL_MULTIBOOT_EN     (0x1 << 24)
#define BPORT1_AB_CTRL_MULTIBOOT_EN_GET(_v)  ((_v >> 24) & 0x1)
#define BPORT1_AB_CTRL_JTAG_CHAIN_DIS   (0x1 << 23)
#define BPORT1_AB_CTRL_JTAG_CHAIN_DIS_GET(_v)  ((_v >> 23) & 0x1)
#define BPORT1_AB_CTRL_PCFG_AES_FUSE    (0x1 << 12)
#define BPORT1_AB_CTRL_PCFG_AES_FUSE_GET(_v)  ((_v >> 12) & 0x1)
#define BPORT1_AB_CTRL_PCFG_AES_EN      (0x7 << 9)
#define BPORT1_AB_CTRL_PCFG_AES_EN_GET(_v)  ((_v >> 9) & 0x7)
#define BPORT1_AB_CTRL_SEU_EN           (0x1 << 8)
#define BPORT1_AB_CTRL_SEU_EN_GET(_v)   ((_v >> 8) & 0x1)
#define BPORT1_AB_CTRL_SEC_EN           (0x1 << 7)
#define BPORT1_AB_CTRL_SEC_EN_GET(_v)   ((_v >> 7) & 0x1)
#define BPORT1_AB_CTRL_SPNIDEN          (0x1 << 6)
#define BPORT1_AB_CTRL_SPNIDEN_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_CTRL_SPIDEN           (0x1 << 5)
#define BPORT1_AB_CTRL_SPIDEN_GET(_v)   ((_v >> 5) & 0x1)
#define BPORT1_AB_CTRL_NIDEN            (0x1 << 4)
#define BPORT1_AB_CTRL_NIDEN_GET(_v)    ((_v >> 4) & 0x1)
#define BPORT1_AB_CTRL_DBGEN            (0x1 << 3)
#define BPORT1_AB_CTRL_DBGEN_GET(_v)    ((_v >> 3) & 0x1)
#define BPORT1_AB_CTRL_DAP_EN           0x7
#define BPORT1_AB_CTRL_DAP_EN_GET(_v)   (_v & 0x7)

#define BPORT1_AB_LOCK_POFFSET          0x4
#define BPORT1_AB_LOCK                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_LOCK_POFFSET)
#define BPORT1_AB_LOCK_AES_FUSE_LOCK    (0x1 << 4)
#define BPORT1_AB_LOCK_AES_FUSE_LOCK_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_LOCK_AES_EN_LOCK      (0x1 << 3)
#define BPORT1_AB_LOCK_AES_EN_LOCK_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_LOCK_SEU_LOCK         (0x1 << 2)
#define BPORT1_AB_LOCK_SEU_LOCK_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_LOCK_SEC_LOCK         (0x1 << 1)
#define BPORT1_AB_LOCK_SEC_LOCK_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_LOCK_DBG_LOCK         0x1
#define BPORT1_AB_LOCK_DBG_LOCK_GET(_v)  (_v & 0x1)

#define BPORT1_AB_CFG_POFFSET           0x8
#define BPORT1_AB_CFG                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CFG_POFFSET)

#define BPORT1_AB_INT_STS_POFFSET       0xc
#define BPORT1_AB_INT_STS               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INT_STS_POFFSET)

#define BPORT1_AB_INT_MASK_POFFSET      0x10
#define BPORT1_AB_INT_MASK              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INT_MASK_POFFSET)

#define BPORT1_AB_STATUS_POFFSET        0x14
#define BPORT1_AB_STATUS                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_STATUS_POFFSET)

#define BPORT1_AB_DMA_SRC_ADDR_POFFSET  0x18
#define BPORT1_AB_DMA_SRC_ADDR          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DMA_SRC_ADDR_POFFSET)

#define BPORT1_AB_DMA_DST_ADDR_POFFSET  0x1c
#define BPORT1_AB_DMA_DST_ADDR          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DMA_DST_ADDR_POFFSET)

#define BPORT1_AB_DMA_SRC_LEN_POFFSET   0x20
#define BPORT1_AB_DMA_SRC_LEN           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DMA_SRC_LEN_POFFSET)

#define BPORT1_AB_DMA_DEST_LEN_POFFSET  0x24
#define BPORT1_AB_DMA_DEST_LEN          (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DMA_DEST_LEN_POFFSET)

#define BPORT1_AB_ROM_SHADOW_POFFSET    0x28
#define BPORT1_AB_ROM_SHADOW            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_ROM_SHADOW_POFFSET)

#define BPORT1_AB_MULTIBOOT_ADDR_POFFSET  0x2c
#define BPORT1_AB_MULTIBOOT_ADDR        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MULTIBOOT_ADDR_POFFSET)

#define BPORT1_AB_UNLOCK_POFFSET        0x34
#define BPORT1_AB_UNLOCK                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_UNLOCK_POFFSET)

#define BPORT1_AB_MCTRL_POFFSET         0x80
#define BPORT1_AB_MCTRL                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MCTRL_POFFSET)

#define BPORT1_AB_XADCIF_CFG_POFFSET    0x100
#define BPORT1_AB_XADCIF_CFG            (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_XADCIF_CFG_POFFSET)
#define BPORT1_AB_XADCIF_CFG_ENABLE     (0x1 << 31)
#define BPORT1_AB_XADCIF_CFG_ENABLE_GET(_v)  ((_v >> 31) & 0x1)
#define BPORT1_AB_XADCIF_CFG_CFIFOTH    (0xf << 20)
#define BPORT1_AB_XADCIF_CFG_CFIFOTH_GET(_v)  ((_v >> 20) & 0xf)
#define BPORT1_AB_XADCIF_CFG_DFIFOTH    (0xf << 16)
#define BPORT1_AB_XADCIF_CFG_DFIFOTH_GET(_v)  ((_v >> 16) & 0xf)
#define BPORT1_AB_XADCIF_CFG_WEDGE      (0x1 << 13)
#define BPORT1_AB_XADCIF_CFG_WEDGE_GET(_v)  ((_v >> 13) & 0x1)
#define BPORT1_AB_XADCIF_CFG_REDGE      (0x1 << 12)
#define BPORT1_AB_XADCIF_CFG_REDGE_GET(_v)  ((_v >> 12) & 0x1)
#define BPORT1_AB_XADCIF_CFG_TCKARTE    (0x3 << 8)
#define BPORT1_AB_XADCIF_CFG_TCKARTE_GET(_v)  ((_v >> 8) & 0x3)
#define BPORT1_AB_XADCIF_CFG_IGAP       0x1f
#define BPORT1_AB_XADCIF_CFG_IGAP_GET(_v)  (_v & 0x1f)

#define BPORT1_AB_XADCIF_INT_STS_POFFSET  0x104
#define BPORT1_AB_XADCIF_INT_STS        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_XADCIF_INT_STS_POFFSET)
#define BPORT1_AB_XADCIF_INT_STS_CFIFO_LTH  (0x1 << 9)
#define BPORT1_AB_XADCIF_INT_STS_CFIFO_LTH_GET(_v)  ((_v >> 9) & 0x1)
#define BPORT1_AB_XADCIF_INT_STS_DFIFO_GTH  (0x1 << 8)
#define BPORT1_AB_XADCIF_INT_STS_DFIFO_GTH_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_XADCIF_INT_STS_OT     (0x1 << 7)
#define BPORT1_AB_XADCIF_INT_STS_OT_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_XADCIF_INT_STS_ALM    0x7f
#define BPORT1_AB_XADCIF_INT_STS_ALM_GET(_v)  (_v & 0x7f)

#define BPORT1_AB_XADCIF_INT_MASK_POFFSET  0x108
#define BPORT1_AB_XADCIF_INT_MASK       (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_XADCIF_INT_MASK_POFFSET)
#define BPORT1_AB_XADCIF_INT_MASK_CFIFO_LTH  (0x1 << 9)
#define BPORT1_AB_XADCIF_INT_MASK_CFIFO_LTH_GET(_v)  ((_v >> 9) & 0x1)
#define BPORT1_AB_XADCIF_INT_MASK_DFIFO_GTH  (0x1 << 8)
#define BPORT1_AB_XADCIF_INT_MASK_DFIFO_GTH_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_XADCIF_INT_MASK_OT    (0x1 << 7)
#define BPORT1_AB_XADCIF_INT_MASK_OT_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_XADCIF_INT_MASK_ALM   0x7f
#define BPORT1_AB_XADCIF_INT_MASK_ALM_GET(_v)  (_v & 0x7f)

#define BPORT1_AB_XADCIF_MSTS_POFFSET   0x10c
#define BPORT1_AB_XADCIF_MSTS           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_XADCIF_MSTS_POFFSET)
#define BPORT1_AB_XADCIF_MSTS_CFIFO_LVL  (0xf << 16)
#define BPORT1_AB_XADCIF_MSTS_CFIFO_LVL_GET(_v)  ((_v >> 16) & 0xf)
#define BPORT1_AB_XADCIF_MSTS_DFIFO_LVL  (0xf << 12)
#define BPORT1_AB_XADCIF_MSTS_DFIFO_LVL_GET(_v)  ((_v >> 12) & 0xf)
#define BPORT1_AB_XADCIF_MSTS_CFIFOF    (0x1 << 11)
#define BPORT1_AB_XADCIF_MSTS_CFIFOF_GET(_v)  ((_v >> 11) & 0x1)
#define BPORT1_AB_XADCIF_MSTS_CFIFOE    (0x1 << 10)
#define BPORT1_AB_XADCIF_MSTS_CFIFOE_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_AB_XADCIF_MSTS_DFIFOF    (0x1 << 9)
#define BPORT1_AB_XADCIF_MSTS_DFIFOF_GET(_v)  ((_v >> 9) & 0x1)
#define BPORT1_AB_XADCIF_MSTS_DFIFOE    (0x1 << 8)
#define BPORT1_AB_XADCIF_MSTS_DFIFOE_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_XADCIF_MSTS_OT        (0x1 << 7)
#define BPORT1_AB_XADCIF_MSTS_OT_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_XADCIF_MSTS_ALM       0x3f
#define BPORT1_AB_XADCIF_MSTS_ALM_GET(_v)  (_v & 0x3f)

#define BPORT1_AB_XADCIF_CMDFIFO_POFFSET  0x110
#define BPORT1_AB_XADCIF_CMDFIFO        (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_XADCIF_CMDFIFO_POFFSET)
#define BPORT1_AB_XADCIF_CMDFIFO_CMD    (0xf << 26)
#define BPORT1_AB_XADCIF_CMDFIFO_CMD_GET(_v)  ((_v >> 26) & 0xf)
#define BPORT1_AB_XADCIF_CMDFIFO_ADDR   (0x3ff << 16)
#define BPORT1_AB_XADCIF_CMDFIFO_ADDR_GET(_v)  ((_v >> 16) & 0x3ff)
#define BPORT1_AB_XADCIF_CMDFIFO_DATA   0xffff
#define BPORT1_AB_XADCIF_CMDFIFO_DATA_GET(_v)  (_v & 0xffff)

#define BPORT1_AB_XADCIF_RDFIFO_POFFSET  0x114
#define BPORT1_AB_XADCIF_RDFIFO         (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_XADCIF_RDFIFO_POFFSET)
#define BPORT1_AB_XADCIF_RDFIFO_DATA    0xffff
#define BPORT1_AB_XADCIF_RDFIFO_DATA_GET(_v)  (_v & 0xffff)

#define BPORT1_AB_XADCIF_MCTL_POFFSET   0x118
#define BPORT1_AB_XADCIF_MCTL           (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_XADCIF_MCTL_POFFSET)
#define BPORT1_AB_XADCIF_MCTL_RESET     (0x1 << 4)
#define BPORT1_AB_XADCIF_MCTL_RESET_GET(_v)  ((_v >> 4) & 0x1)

#define BPORT1_AB_BUFFER_POFFSET        0x0
#define BPORT1_AB_BUFFER                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_BUFFER_POFFSET)
#define BPORT1_AB_BUFFER_BYTES          0x1000


#endif
