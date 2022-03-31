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
#define BPORT1_AB_CGH1_POFFSET          0x0
#define BPORT1_AB_CGH1                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CGH1_POFFSET)
#define BPORT1_AB_CGH1_PH               0xff
#define BPORT1_AB_CGH1_PH_GET(_v)       (_v & 0xff)

#define BPORT1_AB_CGL1_POFFSET          0x1
#define BPORT1_AB_CGL1                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CGL1_POFFSET)
#define BPORT1_AB_CGL1_PL               0xff
#define BPORT1_AB_CGL1_PL_GET(_v)       (_v & 0xff)

#define BPORT1_AB_CGH2_POFFSET          0x2
#define BPORT1_AB_CGH2                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CGH2_POFFSET)
#define BPORT1_AB_CGH2_SH               0xff
#define BPORT1_AB_CGH2_SH_GET(_v)       (_v & 0xff)

#define BPORT1_AB_CGL2_POFFSET          0x3
#define BPORT1_AB_CGL2                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CGL2_POFFSET)
#define BPORT1_AB_CGL2_SL               0xff
#define BPORT1_AB_CGL2_SL_GET(_v)       (_v & 0xff)

#define BPORT1_AB_OC_POFFSET            0x4
#define BPORT1_AB_OC                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_OC_POFFSET)
#define BPORT1_AB_OC_CMTPOL             (0x1 << 6)
#define BPORT1_AB_OC_CMTPOL_GET(_v)     ((_v >> 6) & 0x1)
#define BPORT1_AB_OC_IROL               (0x1 << 7)
#define BPORT1_AB_OC_IROL_GET(_v)       ((_v >> 7) & 0x1)
#define BPORT1_AB_OC_IROPEN             (0x1 << 5)
#define BPORT1_AB_OC_IROPEN_GET(_v)     ((_v >> 5) & 0x1)

#define BPORT1_AB_MSC_POFFSET           0x5
#define BPORT1_AB_MSC                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MSC_POFFSET)
#define BPORT1_AB_MSC_BASE              (0x1 << 3)
#define BPORT1_AB_MSC_BASE_GET(_v)      ((_v >> 3) & 0x1)
#define BPORT1_AB_MSC_CMTDIV            (0x3 << 5)
#define BPORT1_AB_MSC_CMTDIV_GET(_v)    ((_v >> 5) & 0x3)
#define BPORT1_AB_MSC_EOCF              (0x1 << 7)
#define BPORT1_AB_MSC_EOCF_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_MSC_EOCIE             (0x1 << 1)
#define BPORT1_AB_MSC_EOCIE_GET(_v)     ((_v >> 1) & 0x1)
#define BPORT1_AB_MSC_EXSPC             (0x1 << 4)
#define BPORT1_AB_MSC_EXSPC_GET(_v)     ((_v >> 4) & 0x1)
#define BPORT1_AB_MSC_FSK               (0x1 << 2)
#define BPORT1_AB_MSC_FSK_GET(_v)       ((_v >> 2) & 0x1)
#define BPORT1_AB_MSC_MCGEN             0x1
#define BPORT1_AB_MSC_MCGEN_GET(_v)     (_v & 0x1)

#define BPORT1_AB_CMD1_POFFSET          0x6
#define BPORT1_AB_CMD1                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CMD1_POFFSET)
#define BPORT1_AB_CMD1_MB               0xff
#define BPORT1_AB_CMD1_MB_GET(_v)       (_v & 0xff)

#define BPORT1_AB_CMD2_POFFSET          0x7
#define BPORT1_AB_CMD2                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CMD2_POFFSET)
#define BPORT1_AB_CMD2_MB               0xff
#define BPORT1_AB_CMD2_MB_GET(_v)       (_v & 0xff)

#define BPORT1_AB_CMD3_POFFSET          0x8
#define BPORT1_AB_CMD3                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CMD3_POFFSET)
#define BPORT1_AB_CMD3_SB               0xff
#define BPORT1_AB_CMD3_SB_GET(_v)       (_v & 0xff)

#define BPORT1_AB_CMD4_POFFSET          0x9
#define BPORT1_AB_CMD4                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CMD4_POFFSET)
#define BPORT1_AB_CMD4_SB               0xff
#define BPORT1_AB_CMD4_SB_GET(_v)       (_v & 0xff)

#define BPORT1_AB_PPS_POFFSET           0xa
#define BPORT1_AB_PPS                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PPS_POFFSET)
#define BPORT1_AB_PPS_PPSDIV            0xf
#define BPORT1_AB_PPS_PPSDIV_GET(_v)    (_v & 0xf)

#define BPORT1_AB_DMA_POFFSET           0xb
#define BPORT1_AB_DMA                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DMA_POFFSET)
#define BPORT1_AB_DMA_DMA               0x1
#define BPORT1_AB_DMA_DMA_GET(_v)       (_v & 0x1)


#endif
