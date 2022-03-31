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

// Set the macro 'BP1' to the base of port 'bp1'
#ifndef BP1
#error BP1 is undefined. It needs to be set to the port base address
#endif


#define BP1_REG_POFFSET                 0x0
#define BP1_REG_TC_CCR0_POFFSET         0x0
#define BP1_REG_TC_CCR0                 (BP1 + BP1_REG_POFFSET + BP1_REG_TC_CCR0_POFFSET)
#define BP1_REG_TC_CCR0_SWTRG           (0x1 << 2)
#define BP1_REG_TC_CCR0_SWTRG_GET(_v)   ((_v >> 2) & 0x1)
#define BP1_REG_TC_CCR0_CLKDIS          (0x1 << 1)
#define BP1_REG_TC_CCR0_CLKDIS_GET(_v)  ((_v >> 1) & 0x1)
#define BP1_REG_TC_CCR0_CLKEN           0x1
#define BP1_REG_TC_CCR0_CLKEN_GET(_v)   (_v & 0x1)

#define BP1_REG_TC_CMR0_POFFSET         0x4
#define BP1_REG_TC_CMR0                 (BP1 + BP1_REG_POFFSET + BP1_REG_TC_CMR0_POFFSET)
#define BP1_REG_TC_CMR0_LDRB            (0x3 << 18)
#define BP1_REG_TC_CMR0_LDRB_GET(_v)    ((_v >> 18) & 0x3)
#define BP1_REG_TC_CMR0_LDRA            (0x3 << 16)
#define BP1_REG_TC_CMR0_LDRA_GET(_v)    ((_v >> 16) & 0x3)
#define BP1_REG_TC_CMR0_WAVE            (0x1 << 15)
#define BP1_REG_TC_CMR0_WAVE_GET(_v)    ((_v >> 15) & 0x1)
#define BP1_REG_TC_CMR0_CPCTRG          (0x1 << 14)
#define BP1_REG_TC_CMR0_CPCTRG_GET(_v)  ((_v >> 14) & 0x1)
#define BP1_REG_TC_CMR0_ABETRG          (0x1 << 10)
#define BP1_REG_TC_CMR0_ABETRG_GET(_v)  ((_v >> 10) & 0x1)
#define BP1_REG_TC_CMR0_ETRGEDG         (0x3 << 8)
#define BP1_REG_TC_CMR0_ETRGEDG_GET(_v)  ((_v >> 8) & 0x3)
#define BP1_REG_TC_CMR0_LDBDIS          (0x1 << 7)
#define BP1_REG_TC_CMR0_LDBDIS_GET(_v)  ((_v >> 7) & 0x1)
#define BP1_REG_TC_CMR0_LDBSTOP         (0x1 << 6)
#define BP1_REG_TC_CMR0_LDBSTOP_GET(_v)  ((_v >> 6) & 0x1)
#define BP1_REG_TC_CMR0_BURST           (0x3 << 4)
#define BP1_REG_TC_CMR0_BURST_GET(_v)   ((_v >> 4) & 0x3)
#define BP1_REG_TC_CMR0_CLKI            (0x1 << 3)
#define BP1_REG_TC_CMR0_CLKI_GET(_v)    ((_v >> 3) & 0x1)
#define BP1_REG_TC_CMR0_TCCLKS          0x7
#define BP1_REG_TC_CMR0_TCCLKS_GET(_v)  (_v & 0x7)

#define BP1_REG_TC_CVR0_POFFSET         0x10
#define BP1_REG_TC_CVR0                 (BP1 + BP1_REG_POFFSET + BP1_REG_TC_CVR0_POFFSET)
#define BP1_REG_TC_CVR0_CV              0xffff
#define BP1_REG_TC_CVR0_CV_GET(_v)      (_v & 0xffff)

#define BP1_REG_TC_RA0_POFFSET          0x14
#define BP1_REG_TC_RA0                  (BP1 + BP1_REG_POFFSET + BP1_REG_TC_RA0_POFFSET)
#define BP1_REG_TC_RA0_RA               0xffff
#define BP1_REG_TC_RA0_RA_GET(_v)       (_v & 0xffff)

#define BP1_REG_TC_RB0_POFFSET          0x18
#define BP1_REG_TC_RB0                  (BP1 + BP1_REG_POFFSET + BP1_REG_TC_RB0_POFFSET)
#define BP1_REG_TC_RB0_RB               0xffff
#define BP1_REG_TC_RB0_RB_GET(_v)       (_v & 0xffff)

#define BP1_REG_TC_RC0_POFFSET          0x1c
#define BP1_REG_TC_RC0                  (BP1 + BP1_REG_POFFSET + BP1_REG_TC_RC0_POFFSET)
#define BP1_REG_TC_RC0_RC               0xffff
#define BP1_REG_TC_RC0_RC_GET(_v)       (_v & 0xffff)

#define BP1_REG_TC_SR0_POFFSET          0x20
#define BP1_REG_TC_SR0                  (BP1 + BP1_REG_POFFSET + BP1_REG_TC_SR0_POFFSET)
#define BP1_REG_TC_SR0_MTIOB            (0x1 << 18)
#define BP1_REG_TC_SR0_MTIOB_GET(_v)    ((_v >> 18) & 0x1)
#define BP1_REG_TC_SR0_MTIOA            (0x1 << 17)
#define BP1_REG_TC_SR0_MTIOA_GET(_v)    ((_v >> 17) & 0x1)
#define BP1_REG_TC_SR0_CLKSTA           (0x1 << 16)
#define BP1_REG_TC_SR0_CLKSTA_GET(_v)   ((_v >> 16) & 0x1)
#define BP1_REG_TC_SR0_ETRGS            (0x1 << 7)
#define BP1_REG_TC_SR0_ETRGS_GET(_v)    ((_v >> 7) & 0x1)
#define BP1_REG_TC_SR0_LDRBS            (0x1 << 6)
#define BP1_REG_TC_SR0_LDRBS_GET(_v)    ((_v >> 6) & 0x1)
#define BP1_REG_TC_SR0_LDRAS            (0x1 << 5)
#define BP1_REG_TC_SR0_LDRAS_GET(_v)    ((_v >> 5) & 0x1)
#define BP1_REG_TC_SR0_CPCS             (0x1 << 4)
#define BP1_REG_TC_SR0_CPCS_GET(_v)     ((_v >> 4) & 0x1)
#define BP1_REG_TC_SR0_CPBS             (0x1 << 3)
#define BP1_REG_TC_SR0_CPBS_GET(_v)     ((_v >> 3) & 0x1)
#define BP1_REG_TC_SR0_CPAS             (0x1 << 2)
#define BP1_REG_TC_SR0_CPAS_GET(_v)     ((_v >> 2) & 0x1)
#define BP1_REG_TC_SR0_LOVRS            (0x1 << 1)
#define BP1_REG_TC_SR0_LOVRS_GET(_v)    ((_v >> 1) & 0x1)
#define BP1_REG_TC_SR0_COVFS            0x1
#define BP1_REG_TC_SR0_COVFS_GET(_v)    (_v & 0x1)

#define BP1_REG_TC_IER0_POFFSET         0x24
#define BP1_REG_TC_IER0                 (BP1 + BP1_REG_POFFSET + BP1_REG_TC_IER0_POFFSET)
#define BP1_REG_TC_IER0_ETRGS           (0x1 << 7)
#define BP1_REG_TC_IER0_ETRGS_GET(_v)   ((_v >> 7) & 0x1)
#define BP1_REG_TC_IER0_LDRBS           (0x1 << 6)
#define BP1_REG_TC_IER0_LDRBS_GET(_v)   ((_v >> 6) & 0x1)
#define BP1_REG_TC_IER0_LDRAS           (0x1 << 5)
#define BP1_REG_TC_IER0_LDRAS_GET(_v)   ((_v >> 5) & 0x1)
#define BP1_REG_TC_IER0_CPCS            (0x1 << 4)
#define BP1_REG_TC_IER0_CPCS_GET(_v)    ((_v >> 4) & 0x1)
#define BP1_REG_TC_IER0_CPBS            (0x1 << 3)
#define BP1_REG_TC_IER0_CPBS_GET(_v)    ((_v >> 3) & 0x1)
#define BP1_REG_TC_IER0_CPAS            (0x1 << 2)
#define BP1_REG_TC_IER0_CPAS_GET(_v)    ((_v >> 2) & 0x1)
#define BP1_REG_TC_IER0_LOVRS           (0x1 << 1)
#define BP1_REG_TC_IER0_LOVRS_GET(_v)   ((_v >> 1) & 0x1)
#define BP1_REG_TC_IER0_COVFS           0x1
#define BP1_REG_TC_IER0_COVFS_GET(_v)   (_v & 0x1)

#define BP1_REG_TC_IDR0_POFFSET         0x28
#define BP1_REG_TC_IDR0                 (BP1 + BP1_REG_POFFSET + BP1_REG_TC_IDR0_POFFSET)
#define BP1_REG_TC_IDR0_ETRGS           (0x1 << 7)
#define BP1_REG_TC_IDR0_ETRGS_GET(_v)   ((_v >> 7) & 0x1)
#define BP1_REG_TC_IDR0_LDRBS           (0x1 << 6)
#define BP1_REG_TC_IDR0_LDRBS_GET(_v)   ((_v >> 6) & 0x1)
#define BP1_REG_TC_IDR0_LDRAS           (0x1 << 5)
#define BP1_REG_TC_IDR0_LDRAS_GET(_v)   ((_v >> 5) & 0x1)
#define BP1_REG_TC_IDR0_CPCS            (0x1 << 4)
#define BP1_REG_TC_IDR0_CPCS_GET(_v)    ((_v >> 4) & 0x1)
#define BP1_REG_TC_IDR0_CPBS            (0x1 << 3)
#define BP1_REG_TC_IDR0_CPBS_GET(_v)    ((_v >> 3) & 0x1)
#define BP1_REG_TC_IDR0_CPAS            (0x1 << 2)
#define BP1_REG_TC_IDR0_CPAS_GET(_v)    ((_v >> 2) & 0x1)
#define BP1_REG_TC_IDR0_LOVRS           (0x1 << 1)
#define BP1_REG_TC_IDR0_LOVRS_GET(_v)   ((_v >> 1) & 0x1)
#define BP1_REG_TC_IDR0_COVFS           0x1
#define BP1_REG_TC_IDR0_COVFS_GET(_v)   (_v & 0x1)

#define BP1_REG_TC_IMR0_POFFSET         0x2c
#define BP1_REG_TC_IMR0                 (BP1 + BP1_REG_POFFSET + BP1_REG_TC_IMR0_POFFSET)
#define BP1_REG_TC_IMR0_ETRGS           (0x1 << 7)
#define BP1_REG_TC_IMR0_ETRGS_GET(_v)   ((_v >> 7) & 0x1)
#define BP1_REG_TC_IMR0_LDRBS           (0x1 << 6)
#define BP1_REG_TC_IMR0_LDRBS_GET(_v)   ((_v >> 6) & 0x1)
#define BP1_REG_TC_IMR0_LDRAS           (0x1 << 5)
#define BP1_REG_TC_IMR0_LDRAS_GET(_v)   ((_v >> 5) & 0x1)
#define BP1_REG_TC_IMR0_CPCS            (0x1 << 4)
#define BP1_REG_TC_IMR0_CPCS_GET(_v)    ((_v >> 4) & 0x1)
#define BP1_REG_TC_IMR0_CPBS            (0x1 << 3)
#define BP1_REG_TC_IMR0_CPBS_GET(_v)    ((_v >> 3) & 0x1)
#define BP1_REG_TC_IMR0_CPAS            (0x1 << 2)
#define BP1_REG_TC_IMR0_CPAS_GET(_v)    ((_v >> 2) & 0x1)
#define BP1_REG_TC_IMR0_LOVRS           (0x1 << 1)
#define BP1_REG_TC_IMR0_LOVRS_GET(_v)   ((_v >> 1) & 0x1)
#define BP1_REG_TC_IMR0_COVFS           0x1
#define BP1_REG_TC_IMR0_COVFS_GET(_v)   (_v & 0x1)

#define BP1_REG_TC_CCR1_POFFSET         0x40
#define BP1_REG_TC_CCR1                 (BP1 + BP1_REG_POFFSET + BP1_REG_TC_CCR1_POFFSET)
#define BP1_REG_TC_CCR1_SWTRG           (0x1 << 2)
#define BP1_REG_TC_CCR1_SWTRG_GET(_v)   ((_v >> 2) & 0x1)
#define BP1_REG_TC_CCR1_CLKDIS          (0x1 << 1)
#define BP1_REG_TC_CCR1_CLKDIS_GET(_v)  ((_v >> 1) & 0x1)
#define BP1_REG_TC_CCR1_CLKEN           0x1
#define BP1_REG_TC_CCR1_CLKEN_GET(_v)   (_v & 0x1)

#define BP1_REG_TC_CMR1_POFFSET         0x44
#define BP1_REG_TC_CMR1                 (BP1 + BP1_REG_POFFSET + BP1_REG_TC_CMR1_POFFSET)
#define BP1_REG_TC_CMR1_LDRB            (0x3 << 18)
#define BP1_REG_TC_CMR1_LDRB_GET(_v)    ((_v >> 18) & 0x3)
#define BP1_REG_TC_CMR1_LDRA            (0x3 << 16)
#define BP1_REG_TC_CMR1_LDRA_GET(_v)    ((_v >> 16) & 0x3)
#define BP1_REG_TC_CMR1_WAVE            (0x1 << 15)
#define BP1_REG_TC_CMR1_WAVE_GET(_v)    ((_v >> 15) & 0x1)
#define BP1_REG_TC_CMR1_CPCTRG          (0x1 << 14)
#define BP1_REG_TC_CMR1_CPCTRG_GET(_v)  ((_v >> 14) & 0x1)
#define BP1_REG_TC_CMR1_ABETRG          (0x1 << 10)
#define BP1_REG_TC_CMR1_ABETRG_GET(_v)  ((_v >> 10) & 0x1)
#define BP1_REG_TC_CMR1_ETRGEDG         (0x3 << 8)
#define BP1_REG_TC_CMR1_ETRGEDG_GET(_v)  ((_v >> 8) & 0x3)
#define BP1_REG_TC_CMR1_LDBDIS          (0x1 << 7)
#define BP1_REG_TC_CMR1_LDBDIS_GET(_v)  ((_v >> 7) & 0x1)
#define BP1_REG_TC_CMR1_LDBSTOP         (0x1 << 6)
#define BP1_REG_TC_CMR1_LDBSTOP_GET(_v)  ((_v >> 6) & 0x1)
#define BP1_REG_TC_CMR1_BURST           (0x3 << 4)
#define BP1_REG_TC_CMR1_BURST_GET(_v)   ((_v >> 4) & 0x3)
#define BP1_REG_TC_CMR1_CLKI            (0x1 << 3)
#define BP1_REG_TC_CMR1_CLKI_GET(_v)    ((_v >> 3) & 0x1)
#define BP1_REG_TC_CMR1_TCCLKS          0x7
#define BP1_REG_TC_CMR1_TCCLKS_GET(_v)  (_v & 0x7)

#define BP1_REG_TC_CVR1_POFFSET         0x50
#define BP1_REG_TC_CVR1                 (BP1 + BP1_REG_POFFSET + BP1_REG_TC_CVR1_POFFSET)
#define BP1_REG_TC_CVR1_CV              0xffff
#define BP1_REG_TC_CVR1_CV_GET(_v)      (_v & 0xffff)

#define BP1_REG_TC_RA1_POFFSET          0x54
#define BP1_REG_TC_RA1                  (BP1 + BP1_REG_POFFSET + BP1_REG_TC_RA1_POFFSET)
#define BP1_REG_TC_RA1_RA               0xffff
#define BP1_REG_TC_RA1_RA_GET(_v)       (_v & 0xffff)

#define BP1_REG_TC_RB1_POFFSET          0x58
#define BP1_REG_TC_RB1                  (BP1 + BP1_REG_POFFSET + BP1_REG_TC_RB1_POFFSET)
#define BP1_REG_TC_RB1_RB               0xffff
#define BP1_REG_TC_RB1_RB_GET(_v)       (_v & 0xffff)

#define BP1_REG_TC_RC1_POFFSET          0x5c
#define BP1_REG_TC_RC1                  (BP1 + BP1_REG_POFFSET + BP1_REG_TC_RC1_POFFSET)
#define BP1_REG_TC_RC1_RC               0xffff
#define BP1_REG_TC_RC1_RC_GET(_v)       (_v & 0xffff)

#define BP1_REG_TC_SR1_POFFSET          0x60
#define BP1_REG_TC_SR1                  (BP1 + BP1_REG_POFFSET + BP1_REG_TC_SR1_POFFSET)
#define BP1_REG_TC_SR1_MTIOB            (0x1 << 18)
#define BP1_REG_TC_SR1_MTIOB_GET(_v)    ((_v >> 18) & 0x1)
#define BP1_REG_TC_SR1_MTIOA            (0x1 << 17)
#define BP1_REG_TC_SR1_MTIOA_GET(_v)    ((_v >> 17) & 0x1)
#define BP1_REG_TC_SR1_CLKSTA           (0x1 << 16)
#define BP1_REG_TC_SR1_CLKSTA_GET(_v)   ((_v >> 16) & 0x1)
#define BP1_REG_TC_SR1_ETRGS            (0x1 << 7)
#define BP1_REG_TC_SR1_ETRGS_GET(_v)    ((_v >> 7) & 0x1)
#define BP1_REG_TC_SR1_LDRBS            (0x1 << 6)
#define BP1_REG_TC_SR1_LDRBS_GET(_v)    ((_v >> 6) & 0x1)
#define BP1_REG_TC_SR1_LDRAS            (0x1 << 5)
#define BP1_REG_TC_SR1_LDRAS_GET(_v)    ((_v >> 5) & 0x1)
#define BP1_REG_TC_SR1_CPCS             (0x1 << 4)
#define BP1_REG_TC_SR1_CPCS_GET(_v)     ((_v >> 4) & 0x1)
#define BP1_REG_TC_SR1_CPBS             (0x1 << 3)
#define BP1_REG_TC_SR1_CPBS_GET(_v)     ((_v >> 3) & 0x1)
#define BP1_REG_TC_SR1_CPAS             (0x1 << 2)
#define BP1_REG_TC_SR1_CPAS_GET(_v)     ((_v >> 2) & 0x1)
#define BP1_REG_TC_SR1_LOVRS            (0x1 << 1)
#define BP1_REG_TC_SR1_LOVRS_GET(_v)    ((_v >> 1) & 0x1)
#define BP1_REG_TC_SR1_COVFS            0x1
#define BP1_REG_TC_SR1_COVFS_GET(_v)    (_v & 0x1)

#define BP1_REG_TC_IER1_POFFSET         0x64
#define BP1_REG_TC_IER1                 (BP1 + BP1_REG_POFFSET + BP1_REG_TC_IER1_POFFSET)
#define BP1_REG_TC_IER1_ETRGS           (0x1 << 7)
#define BP1_REG_TC_IER1_ETRGS_GET(_v)   ((_v >> 7) & 0x1)
#define BP1_REG_TC_IER1_LDRBS           (0x1 << 6)
#define BP1_REG_TC_IER1_LDRBS_GET(_v)   ((_v >> 6) & 0x1)
#define BP1_REG_TC_IER1_LDRAS           (0x1 << 5)
#define BP1_REG_TC_IER1_LDRAS_GET(_v)   ((_v >> 5) & 0x1)
#define BP1_REG_TC_IER1_CPCS            (0x1 << 4)
#define BP1_REG_TC_IER1_CPCS_GET(_v)    ((_v >> 4) & 0x1)
#define BP1_REG_TC_IER1_CPBS            (0x1 << 3)
#define BP1_REG_TC_IER1_CPBS_GET(_v)    ((_v >> 3) & 0x1)
#define BP1_REG_TC_IER1_CPAS            (0x1 << 2)
#define BP1_REG_TC_IER1_CPAS_GET(_v)    ((_v >> 2) & 0x1)
#define BP1_REG_TC_IER1_LOVRS           (0x1 << 1)
#define BP1_REG_TC_IER1_LOVRS_GET(_v)   ((_v >> 1) & 0x1)
#define BP1_REG_TC_IER1_COVFS           0x1
#define BP1_REG_TC_IER1_COVFS_GET(_v)   (_v & 0x1)

#define BP1_REG_TC_IDR1_POFFSET         0x68
#define BP1_REG_TC_IDR1                 (BP1 + BP1_REG_POFFSET + BP1_REG_TC_IDR1_POFFSET)
#define BP1_REG_TC_IDR1_ETRGS           (0x1 << 7)
#define BP1_REG_TC_IDR1_ETRGS_GET(_v)   ((_v >> 7) & 0x1)
#define BP1_REG_TC_IDR1_LDRBS           (0x1 << 6)
#define BP1_REG_TC_IDR1_LDRBS_GET(_v)   ((_v >> 6) & 0x1)
#define BP1_REG_TC_IDR1_LDRAS           (0x1 << 5)
#define BP1_REG_TC_IDR1_LDRAS_GET(_v)   ((_v >> 5) & 0x1)
#define BP1_REG_TC_IDR1_CPCS            (0x1 << 4)
#define BP1_REG_TC_IDR1_CPCS_GET(_v)    ((_v >> 4) & 0x1)
#define BP1_REG_TC_IDR1_CPBS            (0x1 << 3)
#define BP1_REG_TC_IDR1_CPBS_GET(_v)    ((_v >> 3) & 0x1)
#define BP1_REG_TC_IDR1_CPAS            (0x1 << 2)
#define BP1_REG_TC_IDR1_CPAS_GET(_v)    ((_v >> 2) & 0x1)
#define BP1_REG_TC_IDR1_LOVRS           (0x1 << 1)
#define BP1_REG_TC_IDR1_LOVRS_GET(_v)   ((_v >> 1) & 0x1)
#define BP1_REG_TC_IDR1_COVFS           0x1
#define BP1_REG_TC_IDR1_COVFS_GET(_v)   (_v & 0x1)

#define BP1_REG_TC_IMR1_POFFSET         0x6c
#define BP1_REG_TC_IMR1                 (BP1 + BP1_REG_POFFSET + BP1_REG_TC_IMR1_POFFSET)
#define BP1_REG_TC_IMR1_ETRGS           (0x1 << 7)
#define BP1_REG_TC_IMR1_ETRGS_GET(_v)   ((_v >> 7) & 0x1)
#define BP1_REG_TC_IMR1_LDRBS           (0x1 << 6)
#define BP1_REG_TC_IMR1_LDRBS_GET(_v)   ((_v >> 6) & 0x1)
#define BP1_REG_TC_IMR1_LDRAS           (0x1 << 5)
#define BP1_REG_TC_IMR1_LDRAS_GET(_v)   ((_v >> 5) & 0x1)
#define BP1_REG_TC_IMR1_CPCS            (0x1 << 4)
#define BP1_REG_TC_IMR1_CPCS_GET(_v)    ((_v >> 4) & 0x1)
#define BP1_REG_TC_IMR1_CPBS            (0x1 << 3)
#define BP1_REG_TC_IMR1_CPBS_GET(_v)    ((_v >> 3) & 0x1)
#define BP1_REG_TC_IMR1_CPAS            (0x1 << 2)
#define BP1_REG_TC_IMR1_CPAS_GET(_v)    ((_v >> 2) & 0x1)
#define BP1_REG_TC_IMR1_LOVRS           (0x1 << 1)
#define BP1_REG_TC_IMR1_LOVRS_GET(_v)   ((_v >> 1) & 0x1)
#define BP1_REG_TC_IMR1_COVFS           0x1
#define BP1_REG_TC_IMR1_COVFS_GET(_v)   (_v & 0x1)

#define BP1_REG_TC_CCR2_POFFSET         0x80
#define BP1_REG_TC_CCR2                 (BP1 + BP1_REG_POFFSET + BP1_REG_TC_CCR2_POFFSET)
#define BP1_REG_TC_CCR2_SWTRG           (0x1 << 2)
#define BP1_REG_TC_CCR2_SWTRG_GET(_v)   ((_v >> 2) & 0x1)
#define BP1_REG_TC_CCR2_CLKDIS          (0x1 << 1)
#define BP1_REG_TC_CCR2_CLKDIS_GET(_v)  ((_v >> 1) & 0x1)
#define BP1_REG_TC_CCR2_CLKEN           0x1
#define BP1_REG_TC_CCR2_CLKEN_GET(_v)   (_v & 0x1)

#define BP1_REG_TC_CMR2_POFFSET         0x84
#define BP1_REG_TC_CMR2                 (BP1 + BP1_REG_POFFSET + BP1_REG_TC_CMR2_POFFSET)
#define BP1_REG_TC_CMR2_LDRB            (0x3 << 18)
#define BP1_REG_TC_CMR2_LDRB_GET(_v)    ((_v >> 18) & 0x3)
#define BP1_REG_TC_CMR2_LDRA            (0x3 << 16)
#define BP1_REG_TC_CMR2_LDRA_GET(_v)    ((_v >> 16) & 0x3)
#define BP1_REG_TC_CMR2_WAVE            (0x1 << 15)
#define BP1_REG_TC_CMR2_WAVE_GET(_v)    ((_v >> 15) & 0x1)
#define BP1_REG_TC_CMR2_CPCTRG          (0x1 << 14)
#define BP1_REG_TC_CMR2_CPCTRG_GET(_v)  ((_v >> 14) & 0x1)
#define BP1_REG_TC_CMR2_ABETRG          (0x1 << 10)
#define BP1_REG_TC_CMR2_ABETRG_GET(_v)  ((_v >> 10) & 0x1)
#define BP1_REG_TC_CMR2_ETRGEDG         (0x3 << 8)
#define BP1_REG_TC_CMR2_ETRGEDG_GET(_v)  ((_v >> 8) & 0x3)
#define BP1_REG_TC_CMR2_LDBDIS          (0x1 << 7)
#define BP1_REG_TC_CMR2_LDBDIS_GET(_v)  ((_v >> 7) & 0x1)
#define BP1_REG_TC_CMR2_LDBSTOP         (0x1 << 6)
#define BP1_REG_TC_CMR2_LDBSTOP_GET(_v)  ((_v >> 6) & 0x1)
#define BP1_REG_TC_CMR2_BURST           (0x3 << 4)
#define BP1_REG_TC_CMR2_BURST_GET(_v)   ((_v >> 4) & 0x3)
#define BP1_REG_TC_CMR2_CLKI            (0x1 << 3)
#define BP1_REG_TC_CMR2_CLKI_GET(_v)    ((_v >> 3) & 0x1)
#define BP1_REG_TC_CMR2_TCCLKS          0x7
#define BP1_REG_TC_CMR2_TCCLKS_GET(_v)  (_v & 0x7)

#define BP1_REG_TC_CVR2_POFFSET         0x90
#define BP1_REG_TC_CVR2                 (BP1 + BP1_REG_POFFSET + BP1_REG_TC_CVR2_POFFSET)
#define BP1_REG_TC_CVR2_CV              0xffff
#define BP1_REG_TC_CVR2_CV_GET(_v)      (_v & 0xffff)

#define BP1_REG_TC_RA2_POFFSET          0x94
#define BP1_REG_TC_RA2                  (BP1 + BP1_REG_POFFSET + BP1_REG_TC_RA2_POFFSET)
#define BP1_REG_TC_RA2_RA               0xffff
#define BP1_REG_TC_RA2_RA_GET(_v)       (_v & 0xffff)

#define BP1_REG_TC_RB2_POFFSET          0x98
#define BP1_REG_TC_RB2                  (BP1 + BP1_REG_POFFSET + BP1_REG_TC_RB2_POFFSET)
#define BP1_REG_TC_RB2_RB               0xffff
#define BP1_REG_TC_RB2_RB_GET(_v)       (_v & 0xffff)

#define BP1_REG_TC_RC2_POFFSET          0x9c
#define BP1_REG_TC_RC2                  (BP1 + BP1_REG_POFFSET + BP1_REG_TC_RC2_POFFSET)
#define BP1_REG_TC_RC2_RC               0xffff
#define BP1_REG_TC_RC2_RC_GET(_v)       (_v & 0xffff)

#define BP1_REG_TC_SR2_POFFSET          0xa0
#define BP1_REG_TC_SR2                  (BP1 + BP1_REG_POFFSET + BP1_REG_TC_SR2_POFFSET)
#define BP1_REG_TC_SR2_MTIOB            (0x1 << 18)
#define BP1_REG_TC_SR2_MTIOB_GET(_v)    ((_v >> 18) & 0x1)
#define BP1_REG_TC_SR2_MTIOA            (0x1 << 17)
#define BP1_REG_TC_SR2_MTIOA_GET(_v)    ((_v >> 17) & 0x1)
#define BP1_REG_TC_SR2_CLKSTA           (0x1 << 16)
#define BP1_REG_TC_SR2_CLKSTA_GET(_v)   ((_v >> 16) & 0x1)
#define BP1_REG_TC_SR2_ETRGS            (0x1 << 7)
#define BP1_REG_TC_SR2_ETRGS_GET(_v)    ((_v >> 7) & 0x1)
#define BP1_REG_TC_SR2_LDRBS            (0x1 << 6)
#define BP1_REG_TC_SR2_LDRBS_GET(_v)    ((_v >> 6) & 0x1)
#define BP1_REG_TC_SR2_LDRAS            (0x1 << 5)
#define BP1_REG_TC_SR2_LDRAS_GET(_v)    ((_v >> 5) & 0x1)
#define BP1_REG_TC_SR2_CPCS             (0x1 << 4)
#define BP1_REG_TC_SR2_CPCS_GET(_v)     ((_v >> 4) & 0x1)
#define BP1_REG_TC_SR2_CPBS             (0x1 << 3)
#define BP1_REG_TC_SR2_CPBS_GET(_v)     ((_v >> 3) & 0x1)
#define BP1_REG_TC_SR2_CPAS             (0x1 << 2)
#define BP1_REG_TC_SR2_CPAS_GET(_v)     ((_v >> 2) & 0x1)
#define BP1_REG_TC_SR2_LOVRS            (0x1 << 1)
#define BP1_REG_TC_SR2_LOVRS_GET(_v)    ((_v >> 1) & 0x1)
#define BP1_REG_TC_SR2_COVFS            0x1
#define BP1_REG_TC_SR2_COVFS_GET(_v)    (_v & 0x1)

#define BP1_REG_TC_IER2_POFFSET         0xa4
#define BP1_REG_TC_IER2                 (BP1 + BP1_REG_POFFSET + BP1_REG_TC_IER2_POFFSET)
#define BP1_REG_TC_IER2_ETRGS           (0x1 << 7)
#define BP1_REG_TC_IER2_ETRGS_GET(_v)   ((_v >> 7) & 0x1)
#define BP1_REG_TC_IER2_LDRBS           (0x1 << 6)
#define BP1_REG_TC_IER2_LDRBS_GET(_v)   ((_v >> 6) & 0x1)
#define BP1_REG_TC_IER2_LDRAS           (0x1 << 5)
#define BP1_REG_TC_IER2_LDRAS_GET(_v)   ((_v >> 5) & 0x1)
#define BP1_REG_TC_IER2_CPCS            (0x1 << 4)
#define BP1_REG_TC_IER2_CPCS_GET(_v)    ((_v >> 4) & 0x1)
#define BP1_REG_TC_IER2_CPBS            (0x1 << 3)
#define BP1_REG_TC_IER2_CPBS_GET(_v)    ((_v >> 3) & 0x1)
#define BP1_REG_TC_IER2_CPAS            (0x1 << 2)
#define BP1_REG_TC_IER2_CPAS_GET(_v)    ((_v >> 2) & 0x1)
#define BP1_REG_TC_IER2_LOVRS           (0x1 << 1)
#define BP1_REG_TC_IER2_LOVRS_GET(_v)   ((_v >> 1) & 0x1)
#define BP1_REG_TC_IER2_COVFS           0x1
#define BP1_REG_TC_IER2_COVFS_GET(_v)   (_v & 0x1)

#define BP1_REG_TC_IDR2_POFFSET         0xa8
#define BP1_REG_TC_IDR2                 (BP1 + BP1_REG_POFFSET + BP1_REG_TC_IDR2_POFFSET)
#define BP1_REG_TC_IDR2_ETRGS           (0x1 << 7)
#define BP1_REG_TC_IDR2_ETRGS_GET(_v)   ((_v >> 7) & 0x1)
#define BP1_REG_TC_IDR2_LDRBS           (0x1 << 6)
#define BP1_REG_TC_IDR2_LDRBS_GET(_v)   ((_v >> 6) & 0x1)
#define BP1_REG_TC_IDR2_LDRAS           (0x1 << 5)
#define BP1_REG_TC_IDR2_LDRAS_GET(_v)   ((_v >> 5) & 0x1)
#define BP1_REG_TC_IDR2_CPCS            (0x1 << 4)
#define BP1_REG_TC_IDR2_CPCS_GET(_v)    ((_v >> 4) & 0x1)
#define BP1_REG_TC_IDR2_CPBS            (0x1 << 3)
#define BP1_REG_TC_IDR2_CPBS_GET(_v)    ((_v >> 3) & 0x1)
#define BP1_REG_TC_IDR2_CPAS            (0x1 << 2)
#define BP1_REG_TC_IDR2_CPAS_GET(_v)    ((_v >> 2) & 0x1)
#define BP1_REG_TC_IDR2_LOVRS           (0x1 << 1)
#define BP1_REG_TC_IDR2_LOVRS_GET(_v)   ((_v >> 1) & 0x1)
#define BP1_REG_TC_IDR2_COVFS           0x1
#define BP1_REG_TC_IDR2_COVFS_GET(_v)   (_v & 0x1)

#define BP1_REG_TC_IMR2_POFFSET         0xac
#define BP1_REG_TC_IMR2                 (BP1 + BP1_REG_POFFSET + BP1_REG_TC_IMR2_POFFSET)
#define BP1_REG_TC_IMR2_ETRGS           (0x1 << 7)
#define BP1_REG_TC_IMR2_ETRGS_GET(_v)   ((_v >> 7) & 0x1)
#define BP1_REG_TC_IMR2_LDRBS           (0x1 << 6)
#define BP1_REG_TC_IMR2_LDRBS_GET(_v)   ((_v >> 6) & 0x1)
#define BP1_REG_TC_IMR2_LDRAS           (0x1 << 5)
#define BP1_REG_TC_IMR2_LDRAS_GET(_v)   ((_v >> 5) & 0x1)
#define BP1_REG_TC_IMR2_CPCS            (0x1 << 4)
#define BP1_REG_TC_IMR2_CPCS_GET(_v)    ((_v >> 4) & 0x1)
#define BP1_REG_TC_IMR2_CPBS            (0x1 << 3)
#define BP1_REG_TC_IMR2_CPBS_GET(_v)    ((_v >> 3) & 0x1)
#define BP1_REG_TC_IMR2_CPAS            (0x1 << 2)
#define BP1_REG_TC_IMR2_CPAS_GET(_v)    ((_v >> 2) & 0x1)
#define BP1_REG_TC_IMR2_LOVRS           (0x1 << 1)
#define BP1_REG_TC_IMR2_LOVRS_GET(_v)   ((_v >> 1) & 0x1)
#define BP1_REG_TC_IMR2_COVFS           0x1
#define BP1_REG_TC_IMR2_COVFS_GET(_v)   (_v & 0x1)

#define BP1_REG_TC_BCR_POFFSET          0xc0
#define BP1_REG_TC_BCR                  (BP1 + BP1_REG_POFFSET + BP1_REG_TC_BCR_POFFSET)
#define BP1_REG_TC_BCR_SYNC             0x1
#define BP1_REG_TC_BCR_SYNC_GET(_v)     (_v & 0x1)

#define BP1_REG_TC_BMR_POFFSET          0xc4
#define BP1_REG_TC_BMR                  (BP1 + BP1_REG_POFFSET + BP1_REG_TC_BMR_POFFSET)
#define BP1_REG_TC_BMR_TC2X2CS          (0x3 << 4)
#define BP1_REG_TC_BMR_TC2X2CS_GET(_v)  ((_v >> 4) & 0x3)
#define BP1_REG_TC_BMR_TC1X1CS          (0x3 << 2)
#define BP1_REG_TC_BMR_TC1X1CS_GET(_v)  ((_v >> 2) & 0x3)
#define BP1_REG_TC_BMR_TC0X0CS          0x3
#define BP1_REG_TC_BMR_TC0X0CS_GET(_v)  (_v & 0x3)


#endif
