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

// Set the macro 'MPORT1' to the base of port 'mport1'
#ifndef MPORT1
#error MPORT1 is undefined. It needs to be set to the port base address
#endif
// Set the macro 'BPORT1' to the base of port 'bport1'
#ifndef BPORT1
#error BPORT1 is undefined. It needs to be set to the port base address
#endif


#define MPORT1_MEM_POFFSET              0x0
#define MPORT1_MEM_MEM_POFFSET          0x0
#define MPORT1_MEM_MEM                  (MPORT1 + MPORT1_MEM_POFFSET + MPORT1_MEM_MEM_POFFSET)
#define MPORT1_MEM_MEM_BYTES            0x20000000


#define BPORT1_REG_POFFSET              0x0
#define BPORT1_REG_SCKDIV_POFFSET       0x0
#define BPORT1_REG_SCKDIV               (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_SCKDIV_POFFSET)
#define BPORT1_REG_SCKDIV_SCALE         0xfff
#define BPORT1_REG_SCKDIV_SCALE_GET(_v)  (_v & 0xfff)

#define BPORT1_REG_SCKMODE_POFFSET      0x4
#define BPORT1_REG_SCKMODE              (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_SCKMODE_POFFSET)
#define BPORT1_REG_SCKMODE_PHA          0x1
#define BPORT1_REG_SCKMODE_PHA_GET(_v)  (_v & 0x1)
#define BPORT1_REG_SCKMODE_POL          (0x1 << 1)
#define BPORT1_REG_SCKMODE_POL_GET(_v)  ((_v >> 1) & 0x1)

#define BPORT1_REG_CSID_POFFSET         0x10
#define BPORT1_REG_CSID                 (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_CSID_POFFSET)

#define BPORT1_REG_CSDEF_POFFSET        0x14
#define BPORT1_REG_CSDEF                (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_CSDEF_POFFSET)

#define BPORT1_REG_CSMODE_POFFSET       0x18
#define BPORT1_REG_CSMODE               (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_CSMODE_POFFSET)
#define BPORT1_REG_CSMODE_MODE          0x3
#define BPORT1_REG_CSMODE_MODE_GET(_v)  (_v & 0x3)

#define BPORT1_REG_DELAY0_POFFSET       0x28
#define BPORT1_REG_DELAY0               (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_DELAY0_POFFSET)
#define BPORT1_REG_DELAY0_CSSCK         0xff
#define BPORT1_REG_DELAY0_CSSCK_GET(_v)  (_v & 0xff)
#define BPORT1_REG_DELAY0_SCKCS         (0xff << 16)
#define BPORT1_REG_DELAY0_SCKCS_GET(_v)  ((_v >> 16) & 0xff)

#define BPORT1_REG_DELAY1_POFFSET       0x2c
#define BPORT1_REG_DELAY1               (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_DELAY1_POFFSET)
#define BPORT1_REG_DELAY1_INTERCS       0xff
#define BPORT1_REG_DELAY1_INTERCS_GET(_v)  (_v & 0xff)
#define BPORT1_REG_DELAY1_INTERXFR      (0xff << 16)
#define BPORT1_REG_DELAY1_INTERXFR_GET(_v)  ((_v >> 16) & 0xff)

#define BPORT1_REG_FMT_POFFSET          0x40
#define BPORT1_REG_FMT                  (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_FMT_POFFSET)
#define BPORT1_REG_FMT_PROTO            0x3
#define BPORT1_REG_FMT_PROTO_GET(_v)    (_v & 0x3)
#define BPORT1_REG_FMT_ENDIAN           (0x1 << 2)
#define BPORT1_REG_FMT_ENDIAN_GET(_v)   ((_v >> 2) & 0x1)
#define BPORT1_REG_FMT_DIR              (0x1 << 3)
#define BPORT1_REG_FMT_DIR_GET(_v)      ((_v >> 3) & 0x1)
#define BPORT1_REG_FMT_LEN              (0xf << 16)
#define BPORT1_REG_FMT_LEN_GET(_v)      ((_v >> 16) & 0xf)

#define BPORT1_REG_TXDATA_POFFSET       0x48
#define BPORT1_REG_TXDATA               (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_TXDATA_POFFSET)
#define BPORT1_REG_TXDATA_DATA          0xff
#define BPORT1_REG_TXDATA_DATA_GET(_v)  (_v & 0xff)
#define BPORT1_REG_TXDATA_FULL          (0x1 << 31)
#define BPORT1_REG_TXDATA_FULL_GET(_v)  ((_v >> 31) & 0x1)

#define BPORT1_REG_RXDATA_POFFSET       0x4c
#define BPORT1_REG_RXDATA               (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_RXDATA_POFFSET)
#define BPORT1_REG_RXDATA_DATA          0xff
#define BPORT1_REG_RXDATA_DATA_GET(_v)  (_v & 0xff)
#define BPORT1_REG_RXDATA_EMPTY         (0x1 << 31)
#define BPORT1_REG_RXDATA_EMPTY_GET(_v)  ((_v >> 31) & 0x1)

#define BPORT1_REG_TXMARK_POFFSET       0x50
#define BPORT1_REG_TXMARK               (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_TXMARK_POFFSET)
#define BPORT1_REG_TXMARK_TXMARK        0x7
#define BPORT1_REG_TXMARK_TXMARK_GET(_v)  (_v & 0x7)

#define BPORT1_REG_RXMARK_POFFSET       0x54
#define BPORT1_REG_RXMARK               (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_RXMARK_POFFSET)
#define BPORT1_REG_RXMARK_RXMARK        0x7
#define BPORT1_REG_RXMARK_RXMARK_GET(_v)  (_v & 0x7)

#define BPORT1_REG_FCTRL_POFFSET        0x60
#define BPORT1_REG_FCTRL                (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_FCTRL_POFFSET)
#define BPORT1_REG_FCTRL_EN             0x1
#define BPORT1_REG_FCTRL_EN_GET(_v)     (_v & 0x1)

#define BPORT1_REG_FFMT_POFFSET         0x64
#define BPORT1_REG_FFMT                 (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_FFMT_POFFSET)
#define BPORT1_REG_FFMT_CMD_EN          0x1
#define BPORT1_REG_FFMT_CMD_EN_GET(_v)  (_v & 0x1)
#define BPORT1_REG_FFMT_ADDR_LEN        (0x7 << 1)
#define BPORT1_REG_FFMT_ADDR_LEN_GET(_v)  ((_v >> 1) & 0x7)
#define BPORT1_REG_FFMT_PAD_CNT         (0xf << 4)
#define BPORT1_REG_FFMT_PAD_CNT_GET(_v)  ((_v >> 4) & 0xf)
#define BPORT1_REG_FFMT_CMD_PROTO       (0x3 << 8)
#define BPORT1_REG_FFMT_CMD_PROTO_GET(_v)  ((_v >> 8) & 0x3)
#define BPORT1_REG_FFMT_ADDR_PROTO      (0x3 << 10)
#define BPORT1_REG_FFMT_ADDR_PROTO_GET(_v)  ((_v >> 10) & 0x3)
#define BPORT1_REG_FFMT_DATA_PROTO      (0x3 << 12)
#define BPORT1_REG_FFMT_DATA_PROTO_GET(_v)  ((_v >> 12) & 0x3)
#define BPORT1_REG_FFMT_CMD_CODE        (0xff << 16)
#define BPORT1_REG_FFMT_CMD_CODE_GET(_v)  ((_v >> 16) & 0xff)
#define BPORT1_REG_FFMT_PAD_CODE        (0xff << 24)
#define BPORT1_REG_FFMT_PAD_CODE_GET(_v)  ((_v >> 24) & 0xff)

#define BPORT1_REG_IE_POFFSET           0x70
#define BPORT1_REG_IE                   (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_IE_POFFSET)
#define BPORT1_REG_IE_TXWM              0x1
#define BPORT1_REG_IE_TXWM_GET(_v)      (_v & 0x1)
#define BPORT1_REG_IE_RXWM              (0x1 << 1)
#define BPORT1_REG_IE_RXWM_GET(_v)      ((_v >> 1) & 0x1)

#define BPORT1_REG_IP_POFFSET           0x74
#define BPORT1_REG_IP                   (BPORT1 + BPORT1_REG_POFFSET + BPORT1_REG_IP_POFFSET)
#define BPORT1_REG_IP_TXWM              0x1
#define BPORT1_REG_IP_TXWM_GET(_v)      (_v & 0x1)
#define BPORT1_REG_IP_RXWM              (0x1 << 1)
#define BPORT1_REG_IP_RXWM_GET(_v)      ((_v >> 1) & 0x1)


#endif
