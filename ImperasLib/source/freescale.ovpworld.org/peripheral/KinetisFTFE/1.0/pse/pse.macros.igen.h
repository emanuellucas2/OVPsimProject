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
#define BPORT1_AB_FSTAT_POFFSET         0x0
#define BPORT1_AB_FSTAT                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FSTAT_POFFSET)
#define BPORT1_AB_FSTAT_ACCERR          (0x1 << 5)
#define BPORT1_AB_FSTAT_ACCERR_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_FSTAT_CCIF            (0x1 << 7)
#define BPORT1_AB_FSTAT_CCIF_GET(_v)    ((_v >> 7) & 0x1)
#define BPORT1_AB_FSTAT_FPVIOL          (0x1 << 4)
#define BPORT1_AB_FSTAT_FPVIOL_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_FSTAT_MGSTAT0         0x1
#define BPORT1_AB_FSTAT_MGSTAT0_GET(_v)  (_v & 0x1)
#define BPORT1_AB_FSTAT_RDCOLERR        (0x1 << 6)
#define BPORT1_AB_FSTAT_RDCOLERR_GET(_v)  ((_v >> 6) & 0x1)

#define BPORT1_AB_FCNFG_POFFSET         0x1
#define BPORT1_AB_FCNFG                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FCNFG_POFFSET)
#define BPORT1_AB_FCNFG_CCIE            (0x1 << 7)
#define BPORT1_AB_FCNFG_CCIE_GET(_v)    ((_v >> 7) & 0x1)
#define BPORT1_AB_FCNFG_EEERDY          0x1
#define BPORT1_AB_FCNFG_EEERDY_GET(_v)  (_v & 0x1)
#define BPORT1_AB_FCNFG_ERSAREQ         (0x1 << 5)
#define BPORT1_AB_FCNFG_ERSAREQ_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_FCNFG_ERSSUSP         (0x1 << 4)
#define BPORT1_AB_FCNFG_ERSSUSP_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_FCNFG_PFLSH           (0x1 << 2)
#define BPORT1_AB_FCNFG_PFLSH_GET(_v)   ((_v >> 2) & 0x1)
#define BPORT1_AB_FCNFG_RAMRDY          (0x1 << 1)
#define BPORT1_AB_FCNFG_RAMRDY_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_FCNFG_RDCOLLIE        (0x1 << 6)
#define BPORT1_AB_FCNFG_RDCOLLIE_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_FCNFG_SWAP            (0x1 << 3)
#define BPORT1_AB_FCNFG_SWAP_GET(_v)    ((_v >> 3) & 0x1)

#define BPORT1_AB_FSEC_POFFSET          0x2
#define BPORT1_AB_FSEC                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FSEC_POFFSET)
#define BPORT1_AB_FSEC_FSLACC           (0x3 << 2)
#define BPORT1_AB_FSEC_FSLACC_GET(_v)   ((_v >> 2) & 0x3)
#define BPORT1_AB_FSEC_KEYEN            (0x3 << 6)
#define BPORT1_AB_FSEC_KEYEN_GET(_v)    ((_v >> 6) & 0x3)
#define BPORT1_AB_FSEC_MEEN             (0x3 << 4)
#define BPORT1_AB_FSEC_MEEN_GET(_v)     ((_v >> 4) & 0x3)
#define BPORT1_AB_FSEC_SEC              0x3
#define BPORT1_AB_FSEC_SEC_GET(_v)      (_v & 0x3)

#define BPORT1_AB_FOPT_POFFSET          0x3
#define BPORT1_AB_FOPT                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FOPT_POFFSET)
#define BPORT1_AB_FOPT_OPT              0xff
#define BPORT1_AB_FOPT_OPT_GET(_v)      (_v & 0xff)

#define BPORT1_AB_FCCOB3_POFFSET        0x4
#define BPORT1_AB_FCCOB3                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FCCOB3_POFFSET)
#define BPORT1_AB_FCCOB3_CCOBN          0xff
#define BPORT1_AB_FCCOB3_CCOBN_GET(_v)  (_v & 0xff)

#define BPORT1_AB_FCCOB2_POFFSET        0x5
#define BPORT1_AB_FCCOB2                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FCCOB2_POFFSET)
#define BPORT1_AB_FCCOB2_CCOBN          0xff
#define BPORT1_AB_FCCOB2_CCOBN_GET(_v)  (_v & 0xff)

#define BPORT1_AB_FCCOB1_POFFSET        0x6
#define BPORT1_AB_FCCOB1                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FCCOB1_POFFSET)
#define BPORT1_AB_FCCOB1_CCOBN          0xff
#define BPORT1_AB_FCCOB1_CCOBN_GET(_v)  (_v & 0xff)

#define BPORT1_AB_FCCOB0_POFFSET        0x7
#define BPORT1_AB_FCCOB0                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FCCOB0_POFFSET)
#define BPORT1_AB_FCCOB0_CCOBN          0xff
#define BPORT1_AB_FCCOB0_CCOBN_GET(_v)  (_v & 0xff)

#define BPORT1_AB_FCCOB7_POFFSET        0x8
#define BPORT1_AB_FCCOB7                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FCCOB7_POFFSET)
#define BPORT1_AB_FCCOB7_CCOBN          0xff
#define BPORT1_AB_FCCOB7_CCOBN_GET(_v)  (_v & 0xff)

#define BPORT1_AB_FCCOB6_POFFSET        0x9
#define BPORT1_AB_FCCOB6                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FCCOB6_POFFSET)

#define BPORT1_AB_FCCOB5_POFFSET        0xa
#define BPORT1_AB_FCCOB5                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FCCOB5_POFFSET)
#define BPORT1_AB_FCCOB5_CCOBN          0xff
#define BPORT1_AB_FCCOB5_CCOBN_GET(_v)  (_v & 0xff)

#define BPORT1_AB_FCCOB4_POFFSET        0xb
#define BPORT1_AB_FCCOB4                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FCCOB4_POFFSET)
#define BPORT1_AB_FCCOB4_CCOBN          0xff
#define BPORT1_AB_FCCOB4_CCOBN_GET(_v)  (_v & 0xff)

#define BPORT1_AB_FCCOBB_POFFSET        0xc
#define BPORT1_AB_FCCOBB                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FCCOBB_POFFSET)
#define BPORT1_AB_FCCOBB_CCOBN          0xff
#define BPORT1_AB_FCCOBB_CCOBN_GET(_v)  (_v & 0xff)

#define BPORT1_AB_FCCOBA_POFFSET        0xd
#define BPORT1_AB_FCCOBA                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FCCOBA_POFFSET)
#define BPORT1_AB_FCCOBA_CCOBN          0xff
#define BPORT1_AB_FCCOBA_CCOBN_GET(_v)  (_v & 0xff)

#define BPORT1_AB_FCCOB9_POFFSET        0xe
#define BPORT1_AB_FCCOB9                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FCCOB9_POFFSET)
#define BPORT1_AB_FCCOB9_CCOBN          0xff
#define BPORT1_AB_FCCOB9_CCOBN_GET(_v)  (_v & 0xff)

#define BPORT1_AB_FCCOB8_POFFSET        0xf
#define BPORT1_AB_FCCOB8                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FCCOB8_POFFSET)
#define BPORT1_AB_FCCOB8_CCOBN          0xff
#define BPORT1_AB_FCCOB8_CCOBN_GET(_v)  (_v & 0xff)

#define BPORT1_AB_FPROT3_POFFSET        0x10
#define BPORT1_AB_FPROT3                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FPROT3_POFFSET)
#define BPORT1_AB_FPROT3_PROT           0xff
#define BPORT1_AB_FPROT3_PROT_GET(_v)   (_v & 0xff)

#define BPORT1_AB_FPROT2_POFFSET        0x11
#define BPORT1_AB_FPROT2                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FPROT2_POFFSET)
#define BPORT1_AB_FPROT2_PROT           0xff
#define BPORT1_AB_FPROT2_PROT_GET(_v)   (_v & 0xff)

#define BPORT1_AB_FPROT1_POFFSET        0x12
#define BPORT1_AB_FPROT1                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FPROT1_POFFSET)
#define BPORT1_AB_FPROT1_PROT           0xff
#define BPORT1_AB_FPROT1_PROT_GET(_v)   (_v & 0xff)

#define BPORT1_AB_FPROT0_POFFSET        0x13
#define BPORT1_AB_FPROT0                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FPROT0_POFFSET)
#define BPORT1_AB_FPROT0_PROT           0xff
#define BPORT1_AB_FPROT0_PROT_GET(_v)   (_v & 0xff)

#define BPORT1_AB_FEPROT_POFFSET        0x16
#define BPORT1_AB_FEPROT                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FEPROT_POFFSET)
#define BPORT1_AB_FEPROT_EPROT          0xff
#define BPORT1_AB_FEPROT_EPROT_GET(_v)  (_v & 0xff)

#define BPORT1_AB_FDPROT_POFFSET        0x17
#define BPORT1_AB_FDPROT                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FDPROT_POFFSET)
#define BPORT1_AB_FDPROT_DPROT          0xff
#define BPORT1_AB_FDPROT_DPROT_GET(_v)  (_v & 0xff)


#endif
