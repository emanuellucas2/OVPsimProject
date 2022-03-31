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
#define BPORT1_REG_HFXOSCCFG_POFFSET    0x0
#define BPORT1_REG_HFXOSCCFG            (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_HFXOSCCFG_POFFSET)
#define BPORT1_REG_HFXOSCCFG_XOSC_RDY   (0x1 << 30)
#define BPORT1_REG_HFXOSCCFG_XOSC_RDY_GET(_v)  ((_v >> 30) & 0x1)
#define BPORT1_REG_HFXOSCCFG_XOSCCFG_EN  (0x1 << 31)
#define BPORT1_REG_HFXOSCCFG_XOSCCFG_EN_GET(_v)  ((_v >> 31) & 0x1)

#define BPORT1_REG_COREPLLCFG0_POFFSET  0x4
#define BPORT1_REG_COREPLLCFG0          (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_COREPLLCFG0_POFFSET)
#define BPORT1_REG_COREPLLCFG0_DIVR     0x3f
#define BPORT1_REG_COREPLLCFG0_DIVR_GET(_v)  (_v & 0x3f)
#define BPORT1_REG_COREPLLCFG0_DIVF     (0x1ff << 6)
#define BPORT1_REG_COREPLLCFG0_DIVF_GET(_v)  ((_v >> 6) & 0x1ff)
#define BPORT1_REG_COREPLLCFG0_DIVQ     (0x7 << 15)
#define BPORT1_REG_COREPLLCFG0_DIVQ_GET(_v)  ((_v >> 15) & 0x7)
#define BPORT1_REG_COREPLLCFG0_RANGE    (0x7 << 18)
#define BPORT1_REG_COREPLLCFG0_RANGE_GET(_v)  ((_v >> 18) & 0x7)
#define BPORT1_REG_COREPLLCFG0_BYPASS   (0x1 << 24)
#define BPORT1_REG_COREPLLCFG0_BYPASS_GET(_v)  ((_v >> 24) & 0x1)
#define BPORT1_REG_COREPLLCFG0_FSE      (0x1 << 25)
#define BPORT1_REG_COREPLLCFG0_FSE_GET(_v)  ((_v >> 25) & 0x1)
#define BPORT1_REG_COREPLLCFG0_LOCK     (0x1 << 31)
#define BPORT1_REG_COREPLLCFG0_LOCK_GET(_v)  ((_v >> 31) & 0x1)

#define BPORT1_REG_DDRPLLCFG0_POFFSET   0xc
#define BPORT1_REG_DDRPLLCFG0           (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_DDRPLLCFG0_POFFSET)
#define BPORT1_REG_DDRPLLCFG0_DIVR      0x3f
#define BPORT1_REG_DDRPLLCFG0_DIVR_GET(_v)  (_v & 0x3f)
#define BPORT1_REG_DDRPLLCFG0_DIVF      (0x1ff << 6)
#define BPORT1_REG_DDRPLLCFG0_DIVF_GET(_v)  ((_v >> 6) & 0x1ff)
#define BPORT1_REG_DDRPLLCFG0_DIVQ      (0x7 << 15)
#define BPORT1_REG_DDRPLLCFG0_DIVQ_GET(_v)  ((_v >> 15) & 0x7)
#define BPORT1_REG_DDRPLLCFG0_RANGE     (0x7 << 18)
#define BPORT1_REG_DDRPLLCFG0_RANGE_GET(_v)  ((_v >> 18) & 0x7)
#define BPORT1_REG_DDRPLLCFG0_BYPASS    (0x1 << 24)
#define BPORT1_REG_DDRPLLCFG0_BYPASS_GET(_v)  ((_v >> 24) & 0x1)
#define BPORT1_REG_DDRPLLCFG0_FSE       (0x1 << 25)
#define BPORT1_REG_DDRPLLCFG0_FSE_GET(_v)  ((_v >> 25) & 0x1)
#define BPORT1_REG_DDRPLLCFG0_LOCK      (0x1 << 31)
#define BPORT1_REG_DDRPLLCFG0_LOCK_GET(_v)  ((_v >> 31) & 0x1)

#define BPORT1_REG_DDRPLLCFG1_POFFSET   0x10
#define BPORT1_REG_DDRPLLCFG1           (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_DDRPLLCFG1_POFFSET)
#define BPORT1_REG_DDRPLLCFG1_CKE       (0x1 << 31)
#define BPORT1_REG_DDRPLLCFG1_CKE_GET(_v)  ((_v >> 31) & 0x1)

#define BPORT1_REG_GEMGXLPLLCFG0_POFFSET  0x1c
#define BPORT1_REG_GEMGXLPLLCFG0        (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_GEMGXLPLLCFG0_POFFSET)
#define BPORT1_REG_GEMGXLPLLCFG0_DIVR   0x3f
#define BPORT1_REG_GEMGXLPLLCFG0_DIVR_GET(_v)  (_v & 0x3f)
#define BPORT1_REG_GEMGXLPLLCFG0_DIVF   (0x1ff << 6)
#define BPORT1_REG_GEMGXLPLLCFG0_DIVF_GET(_v)  ((_v >> 6) & 0x1ff)
#define BPORT1_REG_GEMGXLPLLCFG0_DIVQ   (0x7 << 15)
#define BPORT1_REG_GEMGXLPLLCFG0_DIVQ_GET(_v)  ((_v >> 15) & 0x7)
#define BPORT1_REG_GEMGXLPLLCFG0_RANGE  (0x7 << 18)
#define BPORT1_REG_GEMGXLPLLCFG0_RANGE_GET(_v)  ((_v >> 18) & 0x7)
#define BPORT1_REG_GEMGXLPLLCFG0_BYPASS  (0x1 << 24)
#define BPORT1_REG_GEMGXLPLLCFG0_BYPASS_GET(_v)  ((_v >> 24) & 0x1)
#define BPORT1_REG_GEMGXLPLLCFG0_FSE    (0x1 << 25)
#define BPORT1_REG_GEMGXLPLLCFG0_FSE_GET(_v)  ((_v >> 25) & 0x1)
#define BPORT1_REG_GEMGXLPLLCFG0_LOCK   (0x1 << 31)
#define BPORT1_REG_GEMGXLPLLCFG0_LOCK_GET(_v)  ((_v >> 31) & 0x1)

#define BPORT1_REG_GEMGXLPLLCFG1_POFFSET  0x20
#define BPORT1_REG_GEMGXLPLLCFG1        (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_GEMGXLPLLCFG1_POFFSET)
#define BPORT1_REG_GEMGXLPLLCFG1_CKE    (0x1 << 24)
#define BPORT1_REG_GEMGXLPLLCFG1_CKE_GET(_v)  ((_v >> 24) & 0x1)

#define BPORT1_REG_CORECLKSEL_POFFSET   0x24
#define BPORT1_REG_CORECLKSEL           (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_CORECLKSEL_POFFSET)
#define BPORT1_REG_CORECLKSEL_CORECLKSEL  0x1
#define BPORT1_REG_CORECLKSEL_CORECLKSEL_GET(_v)  (_v & 0x1)

#define BPORT1_REG_DEVICESRESETREG_POFFSET  0x28
#define BPORT1_REG_DEVICESRESETREG      (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_DEVICESRESETREG_POFFSET)
#define BPORT1_REG_DEVICESRESETREG_DDR_CTRL_RST_N  0x1
#define BPORT1_REG_DEVICESRESETREG_DDR_CTRL_RST_N_GET(_v)  (_v & 0x1)
#define BPORT1_REG_DEVICESRESETREG_DDR_AXI_RST_N  (0x1 << 1)
#define BPORT1_REG_DEVICESRESETREG_DDR_AXI_RST_N_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_REG_DEVICESRESETREG_DDR_AHB_RST_N  (0x1 << 2)
#define BPORT1_REG_DEVICESRESETREG_DDR_AHB_RST_N_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_REG_DEVICESRESETREG_DDR_PHY_RST_N  (0x1 << 3)
#define BPORT1_REG_DEVICESRESETREG_DDR_PHY_RST_N_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_REG_DEVICESRESETREG_GEMGXL_RST_N  (0x1 << 5)
#define BPORT1_REG_DEVICESRESETREG_GEMGXL_RST_N_GET(_v)  ((_v >> 5) & 0x1)

#define BPORT1_REG_RSVD_POFFSET         0x0
#define BPORT1_REG_RSVD                 (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_RSVD_POFFSET)
#define BPORT1_REG_RSVD_BYTES           0x1000


#endif
