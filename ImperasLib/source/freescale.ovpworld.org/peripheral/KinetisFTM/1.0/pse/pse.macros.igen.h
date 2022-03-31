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
#define BPORT1_AB_SC_POFFSET            0x0
#define BPORT1_AB_SC                    (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SC_POFFSET)
#define BPORT1_AB_SC_CLKS               (0x3 << 3)
#define BPORT1_AB_SC_CLKS_GET(_v)       ((_v >> 3) & 0x3)
#define BPORT1_AB_SC_CPWMS              (0x1 << 5)
#define BPORT1_AB_SC_CPWMS_GET(_v)      ((_v >> 5) & 0x1)
#define BPORT1_AB_SC_PS                 0x7
#define BPORT1_AB_SC_PS_GET(_v)         (_v & 0x7)
#define BPORT1_AB_SC_TOF                (0x1 << 7)
#define BPORT1_AB_SC_TOF_GET(_v)        ((_v >> 7) & 0x1)
#define BPORT1_AB_SC_TOIE               (0x1 << 6)
#define BPORT1_AB_SC_TOIE_GET(_v)       ((_v >> 6) & 0x1)

#define BPORT1_AB_CNT_POFFSET           0x4
#define BPORT1_AB_CNT                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CNT_POFFSET)
#define BPORT1_AB_CNT_COUNT             0xffff
#define BPORT1_AB_CNT_COUNT_GET(_v)     (_v & 0xffff)

#define BPORT1_AB_MOD_POFFSET           0x8
#define BPORT1_AB_MOD                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MOD_POFFSET)
#define BPORT1_AB_MOD_MOD               0xffff
#define BPORT1_AB_MOD_MOD_GET(_v)       (_v & 0xffff)

#define BPORT1_AB_C0SC_POFFSET          0xc
#define BPORT1_AB_C0SC                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C0SC_POFFSET)
#define BPORT1_AB_C0SC_CHF              (0x1 << 7)
#define BPORT1_AB_C0SC_CHF_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_C0SC_CHIE             (0x1 << 6)
#define BPORT1_AB_C0SC_CHIE_GET(_v)     ((_v >> 6) & 0x1)
#define BPORT1_AB_C0SC_DMA              0x1
#define BPORT1_AB_C0SC_DMA_GET(_v)      (_v & 0x1)
#define BPORT1_AB_C0SC_ELSA             (0x1 << 2)
#define BPORT1_AB_C0SC_ELSA_GET(_v)     ((_v >> 2) & 0x1)
#define BPORT1_AB_C0SC_ELSB             (0x1 << 3)
#define BPORT1_AB_C0SC_ELSB_GET(_v)     ((_v >> 3) & 0x1)
#define BPORT1_AB_C0SC_MSA              (0x1 << 4)
#define BPORT1_AB_C0SC_MSA_GET(_v)      ((_v >> 4) & 0x1)
#define BPORT1_AB_C0SC_MSB              (0x1 << 5)
#define BPORT1_AB_C0SC_MSB_GET(_v)      ((_v >> 5) & 0x1)

#define BPORT1_AB_C0V_POFFSET           0x10
#define BPORT1_AB_C0V                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C0V_POFFSET)
#define BPORT1_AB_C0V_VAL               0xffff
#define BPORT1_AB_C0V_VAL_GET(_v)       (_v & 0xffff)

#define BPORT1_AB_C1SC_POFFSET          0x14
#define BPORT1_AB_C1SC                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C1SC_POFFSET)
#define BPORT1_AB_C1SC_CHF              (0x1 << 7)
#define BPORT1_AB_C1SC_CHF_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_C1SC_CHIE             (0x1 << 6)
#define BPORT1_AB_C1SC_CHIE_GET(_v)     ((_v >> 6) & 0x1)
#define BPORT1_AB_C1SC_DMA              0x1
#define BPORT1_AB_C1SC_DMA_GET(_v)      (_v & 0x1)
#define BPORT1_AB_C1SC_ELSA             (0x1 << 2)
#define BPORT1_AB_C1SC_ELSA_GET(_v)     ((_v >> 2) & 0x1)
#define BPORT1_AB_C1SC_ELSB             (0x1 << 3)
#define BPORT1_AB_C1SC_ELSB_GET(_v)     ((_v >> 3) & 0x1)
#define BPORT1_AB_C1SC_MSA              (0x1 << 4)
#define BPORT1_AB_C1SC_MSA_GET(_v)      ((_v >> 4) & 0x1)
#define BPORT1_AB_C1SC_MSB              (0x1 << 5)
#define BPORT1_AB_C1SC_MSB_GET(_v)      ((_v >> 5) & 0x1)

#define BPORT1_AB_C1V_POFFSET           0x18
#define BPORT1_AB_C1V                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C1V_POFFSET)
#define BPORT1_AB_C1V_VAL               0xffff
#define BPORT1_AB_C1V_VAL_GET(_v)       (_v & 0xffff)

#define BPORT1_AB_C2SC_POFFSET          0x1c
#define BPORT1_AB_C2SC                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C2SC_POFFSET)
#define BPORT1_AB_C2SC_CHF              (0x1 << 7)
#define BPORT1_AB_C2SC_CHF_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_C2SC_CHIE             (0x1 << 6)
#define BPORT1_AB_C2SC_CHIE_GET(_v)     ((_v >> 6) & 0x1)
#define BPORT1_AB_C2SC_DMA              0x1
#define BPORT1_AB_C2SC_DMA_GET(_v)      (_v & 0x1)
#define BPORT1_AB_C2SC_ELSA             (0x1 << 2)
#define BPORT1_AB_C2SC_ELSA_GET(_v)     ((_v >> 2) & 0x1)
#define BPORT1_AB_C2SC_ELSB             (0x1 << 3)
#define BPORT1_AB_C2SC_ELSB_GET(_v)     ((_v >> 3) & 0x1)
#define BPORT1_AB_C2SC_MSA              (0x1 << 4)
#define BPORT1_AB_C2SC_MSA_GET(_v)      ((_v >> 4) & 0x1)
#define BPORT1_AB_C2SC_MSB              (0x1 << 5)
#define BPORT1_AB_C2SC_MSB_GET(_v)      ((_v >> 5) & 0x1)

#define BPORT1_AB_C2V_POFFSET           0x20
#define BPORT1_AB_C2V                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C2V_POFFSET)
#define BPORT1_AB_C2V_VAL               0xffff
#define BPORT1_AB_C2V_VAL_GET(_v)       (_v & 0xffff)

#define BPORT1_AB_C3SC_POFFSET          0x24
#define BPORT1_AB_C3SC                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C3SC_POFFSET)
#define BPORT1_AB_C3SC_CHF              (0x1 << 7)
#define BPORT1_AB_C3SC_CHF_GET(_v)      ((_v >> 7) & 0x1)
#define BPORT1_AB_C3SC_CHIE             (0x1 << 6)
#define BPORT1_AB_C3SC_CHIE_GET(_v)     ((_v >> 6) & 0x1)
#define BPORT1_AB_C3SC_DMA              0x1
#define BPORT1_AB_C3SC_DMA_GET(_v)      (_v & 0x1)
#define BPORT1_AB_C3SC_ELSA             (0x1 << 2)
#define BPORT1_AB_C3SC_ELSA_GET(_v)     ((_v >> 2) & 0x1)
#define BPORT1_AB_C3SC_ELSB             (0x1 << 3)
#define BPORT1_AB_C3SC_ELSB_GET(_v)     ((_v >> 3) & 0x1)
#define BPORT1_AB_C3SC_MSA              (0x1 << 4)
#define BPORT1_AB_C3SC_MSA_GET(_v)      ((_v >> 4) & 0x1)
#define BPORT1_AB_C3SC_MSB              (0x1 << 5)
#define BPORT1_AB_C3SC_MSB_GET(_v)      ((_v >> 5) & 0x1)

#define BPORT1_AB_C3V_POFFSET           0x28
#define BPORT1_AB_C3V                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C3V_POFFSET)
#define BPORT1_AB_C3V_VAL               0xffff
#define BPORT1_AB_C3V_VAL_GET(_v)       (_v & 0xffff)

#define BPORT1_AB_C4SC_POFFSET          0x2c
#define BPORT1_AB_C4SC                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C4SC_POFFSET)

#define BPORT1_AB_C4V_POFFSET           0x30
#define BPORT1_AB_C4V                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C4V_POFFSET)
#define BPORT1_AB_C4V_VAL               0xffff
#define BPORT1_AB_C4V_VAL_GET(_v)       (_v & 0xffff)

#define BPORT1_AB_C5SC_POFFSET          0x34
#define BPORT1_AB_C5SC                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C5SC_POFFSET)

#define BPORT1_AB_C5V_POFFSET           0x38
#define BPORT1_AB_C5V                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C5V_POFFSET)
#define BPORT1_AB_C5V_VAL               0xffff
#define BPORT1_AB_C5V_VAL_GET(_v)       (_v & 0xffff)

#define BPORT1_AB_C6SC_POFFSET          0x3c
#define BPORT1_AB_C6SC                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C6SC_POFFSET)

#define BPORT1_AB_C6V_POFFSET           0x40
#define BPORT1_AB_C6V                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C6V_POFFSET)
#define BPORT1_AB_C6V_VAL               0xffff
#define BPORT1_AB_C6V_VAL_GET(_v)       (_v & 0xffff)

#define BPORT1_AB_C7SC_POFFSET          0x44
#define BPORT1_AB_C7SC                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C7SC_POFFSET)

#define BPORT1_AB_C7V_POFFSET           0x48
#define BPORT1_AB_C7V                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_C7V_POFFSET)
#define BPORT1_AB_C7V_VAL               0xffff
#define BPORT1_AB_C7V_VAL_GET(_v)       (_v & 0xffff)

#define BPORT1_AB_CNTIN_POFFSET         0x4c
#define BPORT1_AB_CNTIN                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CNTIN_POFFSET)
#define BPORT1_AB_CNTIN_INIT            0xffff
#define BPORT1_AB_CNTIN_INIT_GET(_v)    (_v & 0xffff)

#define BPORT1_AB_STATUS_POFFSET        0x50
#define BPORT1_AB_STATUS                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_STATUS_POFFSET)
#define BPORT1_AB_STATUS_CH0F           0x1
#define BPORT1_AB_STATUS_CH0F_GET(_v)   (_v & 0x1)
#define BPORT1_AB_STATUS_CH1F           (0x1 << 1)
#define BPORT1_AB_STATUS_CH1F_GET(_v)   ((_v >> 1) & 0x1)
#define BPORT1_AB_STATUS_CH2F           (0x1 << 2)
#define BPORT1_AB_STATUS_CH2F_GET(_v)   ((_v >> 2) & 0x1)
#define BPORT1_AB_STATUS_CH3F           (0x1 << 3)
#define BPORT1_AB_STATUS_CH3F_GET(_v)   ((_v >> 3) & 0x1)
#define BPORT1_AB_STATUS_CH4F           (0x1 << 4)
#define BPORT1_AB_STATUS_CH4F_GET(_v)   ((_v >> 4) & 0x1)
#define BPORT1_AB_STATUS_CH5F           (0x1 << 5)
#define BPORT1_AB_STATUS_CH5F_GET(_v)   ((_v >> 5) & 0x1)
#define BPORT1_AB_STATUS_CH6F           (0x1 << 6)
#define BPORT1_AB_STATUS_CH6F_GET(_v)   ((_v >> 6) & 0x1)
#define BPORT1_AB_STATUS_CH7F           (0x1 << 7)
#define BPORT1_AB_STATUS_CH7F_GET(_v)   ((_v >> 7) & 0x1)

#define BPORT1_AB_MODE_POFFSET          0x54
#define BPORT1_AB_MODE                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MODE_POFFSET)
#define BPORT1_AB_MODE_CAPTEST          (0x1 << 4)
#define BPORT1_AB_MODE_CAPTEST_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_MODE_FAULTIE          (0x1 << 7)
#define BPORT1_AB_MODE_FAULTIE_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_MODE_FAULTM           (0x3 << 5)
#define BPORT1_AB_MODE_FAULTM_GET(_v)   ((_v >> 5) & 0x3)
#define BPORT1_AB_MODE_FTMEN            0x1
#define BPORT1_AB_MODE_FTMEN_GET(_v)    (_v & 0x1)
#define BPORT1_AB_MODE_INIT             (0x1 << 1)
#define BPORT1_AB_MODE_INIT_GET(_v)     ((_v >> 1) & 0x1)
#define BPORT1_AB_MODE_PWMSYNC          (0x1 << 3)
#define BPORT1_AB_MODE_PWMSYNC_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_MODE_WPDIS            (0x1 << 2)
#define BPORT1_AB_MODE_WPDIS_GET(_v)    ((_v >> 2) & 0x1)

#define BPORT1_AB_SYNC_POFFSET          0x58
#define BPORT1_AB_SYNC                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SYNC_POFFSET)
#define BPORT1_AB_SYNC_CNTMAX           (0x1 << 1)
#define BPORT1_AB_SYNC_CNTMAX_GET(_v)   ((_v >> 1) & 0x1)
#define BPORT1_AB_SYNC_CNTMIN           0x1
#define BPORT1_AB_SYNC_CNTMIN_GET(_v)   (_v & 0x1)
#define BPORT1_AB_SYNC_REINIT           (0x1 << 2)
#define BPORT1_AB_SYNC_REINIT_GET(_v)   ((_v >> 2) & 0x1)
#define BPORT1_AB_SYNC_SWSYNC           (0x1 << 7)
#define BPORT1_AB_SYNC_SWSYNC_GET(_v)   ((_v >> 7) & 0x1)
#define BPORT1_AB_SYNC_SYNCHOM          (0x1 << 3)
#define BPORT1_AB_SYNC_SYNCHOM_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_SYNC_TRIG0            (0x1 << 4)
#define BPORT1_AB_SYNC_TRIG0_GET(_v)    ((_v >> 4) & 0x1)
#define BPORT1_AB_SYNC_TRIG1            (0x1 << 5)
#define BPORT1_AB_SYNC_TRIG1_GET(_v)    ((_v >> 5) & 0x1)
#define BPORT1_AB_SYNC_TRIG2            (0x1 << 6)
#define BPORT1_AB_SYNC_TRIG2_GET(_v)    ((_v >> 6) & 0x1)

#define BPORT1_AB_OUTINIT_POFFSET       0x5c
#define BPORT1_AB_OUTINIT               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_OUTINIT_POFFSET)
#define BPORT1_AB_OUTINIT_CH0OI         0x1
#define BPORT1_AB_OUTINIT_CH0OI_GET(_v)  (_v & 0x1)
#define BPORT1_AB_OUTINIT_CH1OI         (0x1 << 1)
#define BPORT1_AB_OUTINIT_CH1OI_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_OUTINIT_CH2OI         (0x1 << 2)
#define BPORT1_AB_OUTINIT_CH2OI_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_OUTINIT_CH3OI         (0x1 << 3)
#define BPORT1_AB_OUTINIT_CH3OI_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_OUTINIT_CH4OI         (0x1 << 4)
#define BPORT1_AB_OUTINIT_CH4OI_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_OUTINIT_CH5OI         (0x1 << 5)
#define BPORT1_AB_OUTINIT_CH5OI_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_OUTINIT_CH6OI         (0x1 << 6)
#define BPORT1_AB_OUTINIT_CH6OI_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_OUTINIT_CH7OI         (0x1 << 7)
#define BPORT1_AB_OUTINIT_CH7OI_GET(_v)  ((_v >> 7) & 0x1)

#define BPORT1_AB_OUTMASK_POFFSET       0x60
#define BPORT1_AB_OUTMASK               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_OUTMASK_POFFSET)
#define BPORT1_AB_OUTMASK_CH0OM         0x1
#define BPORT1_AB_OUTMASK_CH0OM_GET(_v)  (_v & 0x1)
#define BPORT1_AB_OUTMASK_CH1OM         (0x1 << 1)
#define BPORT1_AB_OUTMASK_CH1OM_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_OUTMASK_CH2OM         (0x1 << 2)
#define BPORT1_AB_OUTMASK_CH2OM_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_OUTMASK_CH3OM         (0x1 << 3)
#define BPORT1_AB_OUTMASK_CH3OM_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_OUTMASK_CH4OM         (0x1 << 4)
#define BPORT1_AB_OUTMASK_CH4OM_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_OUTMASK_CH5OM         (0x1 << 5)
#define BPORT1_AB_OUTMASK_CH5OM_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_OUTMASK_CH6OM         (0x1 << 6)
#define BPORT1_AB_OUTMASK_CH6OM_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_OUTMASK_CH7OM         (0x1 << 7)
#define BPORT1_AB_OUTMASK_CH7OM_GET(_v)  ((_v >> 7) & 0x1)

#define BPORT1_AB_COMBINE_POFFSET       0x64
#define BPORT1_AB_COMBINE               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_COMBINE_POFFSET)
#define BPORT1_AB_COMBINE_COMBINE0      0x1
#define BPORT1_AB_COMBINE_COMBINE0_GET(_v)  (_v & 0x1)
#define BPORT1_AB_COMBINE_COMBINE1      (0x1 << 8)
#define BPORT1_AB_COMBINE_COMBINE1_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_COMBINE_COMBINE2      (0x1 << 16)
#define BPORT1_AB_COMBINE_COMBINE2_GET(_v)  ((_v >> 16) & 0x1)
#define BPORT1_AB_COMBINE_COMBINE3      (0x1 << 24)
#define BPORT1_AB_COMBINE_COMBINE3_GET(_v)  ((_v >> 24) & 0x1)
#define BPORT1_AB_COMBINE_COMP0         (0x1 << 1)
#define BPORT1_AB_COMBINE_COMP0_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_COMBINE_COMP1         (0x1 << 9)
#define BPORT1_AB_COMBINE_COMP1_GET(_v)  ((_v >> 9) & 0x1)
#define BPORT1_AB_COMBINE_COMP2         (0x1 << 17)
#define BPORT1_AB_COMBINE_COMP2_GET(_v)  ((_v >> 17) & 0x1)
#define BPORT1_AB_COMBINE_COMP3         (0x1 << 25)
#define BPORT1_AB_COMBINE_COMP3_GET(_v)  ((_v >> 25) & 0x1)
#define BPORT1_AB_COMBINE_DECAP0        (0x1 << 3)
#define BPORT1_AB_COMBINE_DECAP0_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_COMBINE_DECAP1        (0x1 << 11)
#define BPORT1_AB_COMBINE_DECAP1_GET(_v)  ((_v >> 11) & 0x1)
#define BPORT1_AB_COMBINE_DECAP2        (0x1 << 19)
#define BPORT1_AB_COMBINE_DECAP2_GET(_v)  ((_v >> 19) & 0x1)
#define BPORT1_AB_COMBINE_DECAP3        (0x1 << 27)
#define BPORT1_AB_COMBINE_DECAP3_GET(_v)  ((_v >> 27) & 0x1)
#define BPORT1_AB_COMBINE_DECAPEN0      (0x1 << 2)
#define BPORT1_AB_COMBINE_DECAPEN0_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_COMBINE_DECAPEN1      (0x1 << 10)
#define BPORT1_AB_COMBINE_DECAPEN1_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_AB_COMBINE_DECAPEN2      (0x1 << 18)
#define BPORT1_AB_COMBINE_DECAPEN2_GET(_v)  ((_v >> 18) & 0x1)
#define BPORT1_AB_COMBINE_DECAPEN3      (0x1 << 26)
#define BPORT1_AB_COMBINE_DECAPEN3_GET(_v)  ((_v >> 26) & 0x1)
#define BPORT1_AB_COMBINE_DTEN0         (0x1 << 4)
#define BPORT1_AB_COMBINE_DTEN0_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_COMBINE_DTEN1         (0x1 << 12)
#define BPORT1_AB_COMBINE_DTEN1_GET(_v)  ((_v >> 12) & 0x1)
#define BPORT1_AB_COMBINE_DTEN2         (0x1 << 20)
#define BPORT1_AB_COMBINE_DTEN2_GET(_v)  ((_v >> 20) & 0x1)
#define BPORT1_AB_COMBINE_DTEN3         (0x1 << 28)
#define BPORT1_AB_COMBINE_DTEN3_GET(_v)  ((_v >> 28) & 0x1)
#define BPORT1_AB_COMBINE_FAULTEN0      (0x1 << 6)
#define BPORT1_AB_COMBINE_FAULTEN0_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_COMBINE_FAULTEN1      (0x1 << 14)
#define BPORT1_AB_COMBINE_FAULTEN1_GET(_v)  ((_v >> 14) & 0x1)
#define BPORT1_AB_COMBINE_FAULTEN2      (0x1 << 22)
#define BPORT1_AB_COMBINE_FAULTEN2_GET(_v)  ((_v >> 22) & 0x1)
#define BPORT1_AB_COMBINE_FAULTEN3      (0x1 << 30)
#define BPORT1_AB_COMBINE_FAULTEN3_GET(_v)  ((_v >> 30) & 0x1)
#define BPORT1_AB_COMBINE_SYNCEN0       (0x1 << 5)
#define BPORT1_AB_COMBINE_SYNCEN0_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_COMBINE_SYNCEN1       (0x1 << 13)
#define BPORT1_AB_COMBINE_SYNCEN1_GET(_v)  ((_v >> 13) & 0x1)
#define BPORT1_AB_COMBINE_SYNCEN2       (0x1 << 21)
#define BPORT1_AB_COMBINE_SYNCEN2_GET(_v)  ((_v >> 21) & 0x1)
#define BPORT1_AB_COMBINE_SYNCEN3       (0x1 << 29)
#define BPORT1_AB_COMBINE_SYNCEN3_GET(_v)  ((_v >> 29) & 0x1)

#define BPORT1_AB_DEADTIME_POFFSET      0x68
#define BPORT1_AB_DEADTIME              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_DEADTIME_POFFSET)
#define BPORT1_AB_DEADTIME_DTPS         (0x3 << 6)
#define BPORT1_AB_DEADTIME_DTPS_GET(_v)  ((_v >> 6) & 0x3)
#define BPORT1_AB_DEADTIME_DTVAL        0x3f
#define BPORT1_AB_DEADTIME_DTVAL_GET(_v)  (_v & 0x3f)

#define BPORT1_AB_EXTTRIG_POFFSET       0x6c
#define BPORT1_AB_EXTTRIG               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_EXTTRIG_POFFSET)
#define BPORT1_AB_EXTTRIG_CH0TRIG       (0x1 << 4)
#define BPORT1_AB_EXTTRIG_CH0TRIG_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_EXTTRIG_CH1TRIG       (0x1 << 5)
#define BPORT1_AB_EXTTRIG_CH1TRIG_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_EXTTRIG_CH2TRIG       0x1
#define BPORT1_AB_EXTTRIG_CH2TRIG_GET(_v)  (_v & 0x1)
#define BPORT1_AB_EXTTRIG_CH3TRIG       (0x1 << 1)
#define BPORT1_AB_EXTTRIG_CH3TRIG_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_EXTTRIG_CH4TRIG       (0x1 << 2)
#define BPORT1_AB_EXTTRIG_CH4TRIG_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_EXTTRIG_CH5TRIG       (0x1 << 3)
#define BPORT1_AB_EXTTRIG_CH5TRIG_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_EXTTRIG_INITTRIGEN    (0x1 << 6)
#define BPORT1_AB_EXTTRIG_INITTRIGEN_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_EXTTRIG_TRIGF         (0x1 << 7)
#define BPORT1_AB_EXTTRIG_TRIGF_GET(_v)  ((_v >> 7) & 0x1)

#define BPORT1_AB_POL_POFFSET           0x70
#define BPORT1_AB_POL                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_POL_POFFSET)
#define BPORT1_AB_POL_POL0              0x1
#define BPORT1_AB_POL_POL0_GET(_v)      (_v & 0x1)
#define BPORT1_AB_POL_POL1              (0x1 << 1)
#define BPORT1_AB_POL_POL1_GET(_v)      ((_v >> 1) & 0x1)
#define BPORT1_AB_POL_POL2              (0x1 << 2)
#define BPORT1_AB_POL_POL2_GET(_v)      ((_v >> 2) & 0x1)
#define BPORT1_AB_POL_POL3              (0x1 << 3)
#define BPORT1_AB_POL_POL3_GET(_v)      ((_v >> 3) & 0x1)
#define BPORT1_AB_POL_POL4              (0x1 << 4)
#define BPORT1_AB_POL_POL4_GET(_v)      ((_v >> 4) & 0x1)
#define BPORT1_AB_POL_POL5              (0x1 << 5)
#define BPORT1_AB_POL_POL5_GET(_v)      ((_v >> 5) & 0x1)
#define BPORT1_AB_POL_POL6              (0x1 << 6)
#define BPORT1_AB_POL_POL6_GET(_v)      ((_v >> 6) & 0x1)
#define BPORT1_AB_POL_POL7              (0x1 << 7)
#define BPORT1_AB_POL_POL7_GET(_v)      ((_v >> 7) & 0x1)

#define BPORT1_AB_FMS_POFFSET           0x74
#define BPORT1_AB_FMS                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FMS_POFFSET)
#define BPORT1_AB_FMS_FAULTF            (0x1 << 7)
#define BPORT1_AB_FMS_FAULTF_GET(_v)    ((_v >> 7) & 0x1)
#define BPORT1_AB_FMS_FAULTF0           0x1
#define BPORT1_AB_FMS_FAULTF0_GET(_v)   (_v & 0x1)
#define BPORT1_AB_FMS_FAULTF1           (0x1 << 1)
#define BPORT1_AB_FMS_FAULTF1_GET(_v)   ((_v >> 1) & 0x1)
#define BPORT1_AB_FMS_FAULTF2           (0x1 << 2)
#define BPORT1_AB_FMS_FAULTF2_GET(_v)   ((_v >> 2) & 0x1)
#define BPORT1_AB_FMS_FAULTF3           (0x1 << 3)
#define BPORT1_AB_FMS_FAULTF3_GET(_v)   ((_v >> 3) & 0x1)
#define BPORT1_AB_FMS_FAULTIN           (0x1 << 5)
#define BPORT1_AB_FMS_FAULTIN_GET(_v)   ((_v >> 5) & 0x1)
#define BPORT1_AB_FMS_WPEN              (0x1 << 6)
#define BPORT1_AB_FMS_WPEN_GET(_v)      ((_v >> 6) & 0x1)

#define BPORT1_AB_FILTER_POFFSET        0x78
#define BPORT1_AB_FILTER                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FILTER_POFFSET)
#define BPORT1_AB_FILTER_CH0FVAL        0xf
#define BPORT1_AB_FILTER_CH0FVAL_GET(_v)  (_v & 0xf)
#define BPORT1_AB_FILTER_CH1FVAL        (0xf << 4)
#define BPORT1_AB_FILTER_CH1FVAL_GET(_v)  ((_v >> 4) & 0xf)
#define BPORT1_AB_FILTER_CH2FVAL        (0xf << 8)
#define BPORT1_AB_FILTER_CH2FVAL_GET(_v)  ((_v >> 8) & 0xf)
#define BPORT1_AB_FILTER_CH3FVAL        (0xf << 12)
#define BPORT1_AB_FILTER_CH3FVAL_GET(_v)  ((_v >> 12) & 0xf)

#define BPORT1_AB_FLTCTRL_POFFSET       0x7c
#define BPORT1_AB_FLTCTRL               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FLTCTRL_POFFSET)
#define BPORT1_AB_FLTCTRL_FAULT0EN      0x1
#define BPORT1_AB_FLTCTRL_FAULT0EN_GET(_v)  (_v & 0x1)
#define BPORT1_AB_FLTCTRL_FAULT1EN      (0x1 << 1)
#define BPORT1_AB_FLTCTRL_FAULT1EN_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_FLTCTRL_FAULT2EN      (0x1 << 2)
#define BPORT1_AB_FLTCTRL_FAULT2EN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_FLTCTRL_FAULT3EN      (0x1 << 3)
#define BPORT1_AB_FLTCTRL_FAULT3EN_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_FLTCTRL_FFLTR0EN      (0x1 << 4)
#define BPORT1_AB_FLTCTRL_FFLTR0EN_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_FLTCTRL_FFLTR1EN      (0x1 << 5)
#define BPORT1_AB_FLTCTRL_FFLTR1EN_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_FLTCTRL_FFLTR2EN      (0x1 << 6)
#define BPORT1_AB_FLTCTRL_FFLTR2EN_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_FLTCTRL_FFLTR3EN      (0x1 << 7)
#define BPORT1_AB_FLTCTRL_FFLTR3EN_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_FLTCTRL_FFVAL         (0xf << 8)
#define BPORT1_AB_FLTCTRL_FFVAL_GET(_v)  ((_v >> 8) & 0xf)

#define BPORT1_AB_QDCTRL_POFFSET        0x80
#define BPORT1_AB_QDCTRL                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_QDCTRL_POFFSET)
#define BPORT1_AB_QDCTRL_PHAFLTREN      (0x1 << 7)
#define BPORT1_AB_QDCTRL_PHAFLTREN_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_QDCTRL_PHAPOL         (0x1 << 5)
#define BPORT1_AB_QDCTRL_PHAPOL_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_QDCTRL_PHBFLTREN      (0x1 << 6)
#define BPORT1_AB_QDCTRL_PHBFLTREN_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_QDCTRL_PHBPOL         (0x1 << 4)
#define BPORT1_AB_QDCTRL_PHBPOL_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_QDCTRL_QUADEN         0x1
#define BPORT1_AB_QDCTRL_QUADEN_GET(_v)  (_v & 0x1)
#define BPORT1_AB_QDCTRL_QUADIR         (0x1 << 2)
#define BPORT1_AB_QDCTRL_QUADIR_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_QDCTRL_QUADMODE       (0x1 << 3)
#define BPORT1_AB_QDCTRL_QUADMODE_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_QDCTRL_TOFDIR         (0x1 << 1)
#define BPORT1_AB_QDCTRL_TOFDIR_GET(_v)  ((_v >> 1) & 0x1)

#define BPORT1_AB_CONF_POFFSET          0x84
#define BPORT1_AB_CONF                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CONF_POFFSET)
#define BPORT1_AB_CONF_BDMMODE          (0x3 << 6)
#define BPORT1_AB_CONF_BDMMODE_GET(_v)  ((_v >> 6) & 0x3)
#define BPORT1_AB_CONF_GTBEEN           (0x1 << 9)
#define BPORT1_AB_CONF_GTBEEN_GET(_v)   ((_v >> 9) & 0x1)
#define BPORT1_AB_CONF_GTBEOUT          (0x1 << 10)
#define BPORT1_AB_CONF_GTBEOUT_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_AB_CONF_NUMTOF           0x1f
#define BPORT1_AB_CONF_NUMTOF_GET(_v)   (_v & 0x1f)

#define BPORT1_AB_FLTPOL_POFFSET        0x88
#define BPORT1_AB_FLTPOL                (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FLTPOL_POFFSET)
#define BPORT1_AB_FLTPOL_FLT0POL        0x1
#define BPORT1_AB_FLTPOL_FLT0POL_GET(_v)  (_v & 0x1)
#define BPORT1_AB_FLTPOL_FLT1POL        (0x1 << 1)
#define BPORT1_AB_FLTPOL_FLT1POL_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_FLTPOL_FLT2POL        (0x1 << 2)
#define BPORT1_AB_FLTPOL_FLT2POL_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_FLTPOL_FLT3POL        (0x1 << 3)
#define BPORT1_AB_FLTPOL_FLT3POL_GET(_v)  ((_v >> 3) & 0x1)

#define BPORT1_AB_SYNCONF_POFFSET       0x8c
#define BPORT1_AB_SYNCONF               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SYNCONF_POFFSET)
#define BPORT1_AB_SYNCONF_CNTINC        (0x1 << 2)
#define BPORT1_AB_SYNCONF_CNTINC_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_SYNCONF_HWINVC        (0x1 << 19)
#define BPORT1_AB_SYNCONF_HWINVC_GET(_v)  ((_v >> 19) & 0x1)
#define BPORT1_AB_SYNCONF_HWOM          (0x1 << 18)
#define BPORT1_AB_SYNCONF_HWOM_GET(_v)  ((_v >> 18) & 0x1)
#define BPORT1_AB_SYNCONF_HWRSTCNT      (0x1 << 16)
#define BPORT1_AB_SYNCONF_HWRSTCNT_GET(_v)  ((_v >> 16) & 0x1)
#define BPORT1_AB_SYNCONF_HWSOC         (0x1 << 20)
#define BPORT1_AB_SYNCONF_HWSOC_GET(_v)  ((_v >> 20) & 0x1)
#define BPORT1_AB_SYNCONF_HWTRIGMODE    0x1
#define BPORT1_AB_SYNCONF_HWTRIGMODE_GET(_v)  (_v & 0x1)
#define BPORT1_AB_SYNCONF_HWWRBUF       (0x1 << 17)
#define BPORT1_AB_SYNCONF_HWWRBUF_GET(_v)  ((_v >> 17) & 0x1)
#define BPORT1_AB_SYNCONF_INVC          (0x1 << 4)
#define BPORT1_AB_SYNCONF_INVC_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_SYNCONF_SWINVC        (0x1 << 11)
#define BPORT1_AB_SYNCONF_SWINVC_GET(_v)  ((_v >> 11) & 0x1)
#define BPORT1_AB_SYNCONF_SWOC          (0x1 << 5)
#define BPORT1_AB_SYNCONF_SWOC_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_SYNCONF_SWOM          (0x1 << 10)
#define BPORT1_AB_SYNCONF_SWOM_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_AB_SYNCONF_SWRSTCNT      (0x1 << 8)
#define BPORT1_AB_SYNCONF_SWRSTCNT_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_SYNCONF_SWSOC         (0x1 << 12)
#define BPORT1_AB_SYNCONF_SWSOC_GET(_v)  ((_v >> 12) & 0x1)
#define BPORT1_AB_SYNCONF_SWWRBUF       (0x1 << 9)
#define BPORT1_AB_SYNCONF_SWWRBUF_GET(_v)  ((_v >> 9) & 0x1)
#define BPORT1_AB_SYNCONF_SYNCMODE      (0x1 << 7)
#define BPORT1_AB_SYNCONF_SYNCMODE_GET(_v)  ((_v >> 7) & 0x1)

#define BPORT1_AB_INVCTRL_POFFSET       0x90
#define BPORT1_AB_INVCTRL               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_INVCTRL_POFFSET)
#define BPORT1_AB_INVCTRL_INV0EN        0x1
#define BPORT1_AB_INVCTRL_INV0EN_GET(_v)  (_v & 0x1)
#define BPORT1_AB_INVCTRL_INV1EN        (0x1 << 1)
#define BPORT1_AB_INVCTRL_INV1EN_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_INVCTRL_INV2EN        (0x1 << 2)
#define BPORT1_AB_INVCTRL_INV2EN_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_INVCTRL_INV3EN        (0x1 << 3)
#define BPORT1_AB_INVCTRL_INV3EN_GET(_v)  ((_v >> 3) & 0x1)

#define BPORT1_AB_SWOCTRL_POFFSET       0x94
#define BPORT1_AB_SWOCTRL               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SWOCTRL_POFFSET)
#define BPORT1_AB_SWOCTRL_CH0OC         0x1
#define BPORT1_AB_SWOCTRL_CH0OC_GET(_v)  (_v & 0x1)
#define BPORT1_AB_SWOCTRL_CH0OCV        (0x1 << 8)
#define BPORT1_AB_SWOCTRL_CH0OCV_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_SWOCTRL_CH1OC         (0x1 << 1)
#define BPORT1_AB_SWOCTRL_CH1OC_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_SWOCTRL_CH1OCV        (0x1 << 9)
#define BPORT1_AB_SWOCTRL_CH1OCV_GET(_v)  ((_v >> 9) & 0x1)
#define BPORT1_AB_SWOCTRL_CH2OC         (0x1 << 2)
#define BPORT1_AB_SWOCTRL_CH2OC_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_SWOCTRL_CH2OCV        (0x1 << 10)
#define BPORT1_AB_SWOCTRL_CH2OCV_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_AB_SWOCTRL_CH3OC         (0x1 << 3)
#define BPORT1_AB_SWOCTRL_CH3OC_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_SWOCTRL_CH3OCV        (0x1 << 11)
#define BPORT1_AB_SWOCTRL_CH3OCV_GET(_v)  ((_v >> 11) & 0x1)
#define BPORT1_AB_SWOCTRL_CH4OC         (0x1 << 4)
#define BPORT1_AB_SWOCTRL_CH4OC_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_SWOCTRL_CH4OCV        (0x1 << 12)
#define BPORT1_AB_SWOCTRL_CH4OCV_GET(_v)  ((_v >> 12) & 0x1)
#define BPORT1_AB_SWOCTRL_CH5OC         (0x1 << 5)
#define BPORT1_AB_SWOCTRL_CH5OC_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_SWOCTRL_CH5OCV        (0x1 << 13)
#define BPORT1_AB_SWOCTRL_CH5OCV_GET(_v)  ((_v >> 13) & 0x1)
#define BPORT1_AB_SWOCTRL_CH6OC         (0x1 << 6)
#define BPORT1_AB_SWOCTRL_CH6OC_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_SWOCTRL_CH6OCV        (0x1 << 14)
#define BPORT1_AB_SWOCTRL_CH6OCV_GET(_v)  ((_v >> 14) & 0x1)
#define BPORT1_AB_SWOCTRL_CH7OC         (0x1 << 7)
#define BPORT1_AB_SWOCTRL_CH7OC_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_SWOCTRL_CH7OCV        (0x1 << 15)
#define BPORT1_AB_SWOCTRL_CH7OCV_GET(_v)  ((_v >> 15) & 0x1)

#define BPORT1_AB_PWMLOAD_POFFSET       0x98
#define BPORT1_AB_PWMLOAD               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_PWMLOAD_POFFSET)
#define BPORT1_AB_PWMLOAD_CH0SEL        0x1
#define BPORT1_AB_PWMLOAD_CH0SEL_GET(_v)  (_v & 0x1)
#define BPORT1_AB_PWMLOAD_CH1SEL        (0x1 << 1)
#define BPORT1_AB_PWMLOAD_CH1SEL_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_PWMLOAD_CH2SEL        (0x1 << 2)
#define BPORT1_AB_PWMLOAD_CH2SEL_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_PWMLOAD_CH3SEL        (0x1 << 3)
#define BPORT1_AB_PWMLOAD_CH3SEL_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_PWMLOAD_CH4SEL        (0x1 << 4)
#define BPORT1_AB_PWMLOAD_CH4SEL_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_PWMLOAD_CH5SEL        (0x1 << 5)
#define BPORT1_AB_PWMLOAD_CH5SEL_GET(_v)  ((_v >> 5) & 0x1)
#define BPORT1_AB_PWMLOAD_CH6SEL        (0x1 << 6)
#define BPORT1_AB_PWMLOAD_CH6SEL_GET(_v)  ((_v >> 6) & 0x1)
#define BPORT1_AB_PWMLOAD_CH7SEL        (0x1 << 7)
#define BPORT1_AB_PWMLOAD_CH7SEL_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_PWMLOAD_LDOK          (0x1 << 9)
#define BPORT1_AB_PWMLOAD_LDOK_GET(_v)  ((_v >> 9) & 0x1)


#endif
