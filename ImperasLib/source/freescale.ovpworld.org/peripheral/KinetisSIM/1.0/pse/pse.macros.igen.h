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
#define BPORT1_AB_SOPT1_POFFSET         0x0
#define BPORT1_AB_SOPT1                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SOPT1_POFFSET)
#define BPORT1_AB_SOPT1_OSC32KSEL       (0x1 << 19)
#define BPORT1_AB_SOPT1_OSC32KSEL_GET(_v)  ((_v >> 19) & 0x1)
#define BPORT1_AB_SOPT1_USBREGEN        (0x1 << 31)
#define BPORT1_AB_SOPT1_USBREGEN_GET(_v)  ((_v >> 31) & 0x1)
#define BPORT1_AB_SOPT1_USBSSTBY        (0x1 << 30)
#define BPORT1_AB_SOPT1_USBSSTBY_GET(_v)  ((_v >> 30) & 0x1)
#define BPORT1_AB_SOPT1_USBVSTBY        (0x1 << 29)
#define BPORT1_AB_SOPT1_USBVSTBY_GET(_v)  ((_v >> 29) & 0x1)
#define BPORT1_AB_SOPT1_RAMSIZE         (0xf << 12)
#define BPORT1_AB_SOPT1_RAMSIZE_GET(_v)  ((_v >> 12) & 0xf)

#define BPORT1_AB_SOPT1CFG_POFFSET      0x4
#define BPORT1_AB_SOPT1CFG              (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SOPT1CFG_POFFSET)
#define BPORT1_AB_SOPT1CFG_URWE         (0x1 << 24)
#define BPORT1_AB_SOPT1CFG_URWE_GET(_v)  ((_v >> 24) & 0x1)
#define BPORT1_AB_SOPT1CFG_USSWE        (0x1 << 26)
#define BPORT1_AB_SOPT1CFG_USSWE_GET(_v)  ((_v >> 26) & 0x1)
#define BPORT1_AB_SOPT1CFG_UVSWE        (0x1 << 25)
#define BPORT1_AB_SOPT1CFG_UVSWE_GET(_v)  ((_v >> 25) & 0x1)

#define BPORT1_AB_SOPT2_POFFSET         0x1004
#define BPORT1_AB_SOPT2                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SOPT2_POFFSET)
#define BPORT1_AB_SOPT2_CLKOUTSEL       (0x7 << 5)
#define BPORT1_AB_SOPT2_CLKOUTSEL_GET(_v)  ((_v >> 5) & 0x7)
#define BPORT1_AB_SOPT2_CMTUARTPAD      (0x1 << 11)
#define BPORT1_AB_SOPT2_CMTUARTPAD_GET(_v)  ((_v >> 11) & 0x1)
#define BPORT1_AB_SOPT2_ESDHCSRC        (0x3 << 28)
#define BPORT1_AB_SOPT2_ESDHCSRC_GET(_v)  ((_v >> 28) & 0x3)
#define BPORT1_AB_SOPT2_FBSL            (0x3 << 8)
#define BPORT1_AB_SOPT2_FBSL_GET(_v)    ((_v >> 8) & 0x3)
#define BPORT1_AB_SOPT2_NFC_CLKSEL      (0x1 << 15)
#define BPORT1_AB_SOPT2_NFC_CLKSEL_GET(_v)  ((_v >> 15) & 0x1)
#define BPORT1_AB_SOPT2_NFCSRC          (0x3 << 30)
#define BPORT1_AB_SOPT2_NFCSRC_GET(_v)  ((_v >> 30) & 0x3)
#define BPORT1_AB_SOPT2_PLLFLLSEL       (0x3 << 16)
#define BPORT1_AB_SOPT2_PLLFLLSEL_GET(_v)  ((_v >> 16) & 0x3)
#define BPORT1_AB_SOPT2_RTCCLKOUTSEL    (0x1 << 4)
#define BPORT1_AB_SOPT2_RTCCLKOUTSEL_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_SOPT2_TIMESRC         (0x3 << 20)
#define BPORT1_AB_SOPT2_TIMESRC_GET(_v)  ((_v >> 20) & 0x3)
#define BPORT1_AB_SOPT2_TRACECLKSEL     (0x1 << 12)
#define BPORT1_AB_SOPT2_TRACECLKSEL_GET(_v)  ((_v >> 12) & 0x1)
#define BPORT1_AB_SOPT2_USBF_CLKSEL     (0x1 << 18)
#define BPORT1_AB_SOPT2_USBF_CLKSEL_GET(_v)  ((_v >> 18) & 0x1)
#define BPORT1_AB_SOPT2_USBFSRC         (0x3 << 22)
#define BPORT1_AB_SOPT2_USBFSRC_GET(_v)  ((_v >> 22) & 0x3)
#define BPORT1_AB_SOPT2_USBH_CLKSEL     (0x1 << 10)
#define BPORT1_AB_SOPT2_USBH_CLKSEL_GET(_v)  ((_v >> 10) & 0x1)
#define BPORT1_AB_SOPT2_USBHSRC         (0x3 << 2)
#define BPORT1_AB_SOPT2_USBHSRC_GET(_v)  ((_v >> 2) & 0x3)

#define BPORT1_AB_SOPT4_POFFSET         0x100c
#define BPORT1_AB_SOPT4                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SOPT4_POFFSET)
#define BPORT1_AB_SOPT4_FTM0CLKSEL      (0x1 << 24)
#define BPORT1_AB_SOPT4_FTM0CLKSEL_GET(_v)  ((_v >> 24) & 0x1)
#define BPORT1_AB_SOPT4_FTM0FLT0        0x1
#define BPORT1_AB_SOPT4_FTM0FLT0_GET(_v)  (_v & 0x1)
#define BPORT1_AB_SOPT4_FTM0FLT1        (0x1 << 1)
#define BPORT1_AB_SOPT4_FTM0FLT1_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_SOPT4_FTM0FLT2        (0x1 << 2)
#define BPORT1_AB_SOPT4_FTM0FLT2_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_SOPT4_FTM0FLT3        (0x1 << 3)
#define BPORT1_AB_SOPT4_FTM0FLT3_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_SOPT4_FTM0TRG0SRC     (0x1 << 28)
#define BPORT1_AB_SOPT4_FTM0TRG0SRC_GET(_v)  ((_v >> 28) & 0x1)
#define BPORT1_AB_SOPT4_FTM0TRG1SRC     (0x1 << 29)
#define BPORT1_AB_SOPT4_FTM0TRG1SRC_GET(_v)  ((_v >> 29) & 0x1)
#define BPORT1_AB_SOPT4_FTM1CH0SRC      (0x3 << 18)
#define BPORT1_AB_SOPT4_FTM1CH0SRC_GET(_v)  ((_v >> 18) & 0x3)
#define BPORT1_AB_SOPT4_FTM1CLKSEL      (0x1 << 25)
#define BPORT1_AB_SOPT4_FTM1CLKSEL_GET(_v)  ((_v >> 25) & 0x1)
#define BPORT1_AB_SOPT4_FTM1FLT0        (0x1 << 4)
#define BPORT1_AB_SOPT4_FTM1FLT0_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_SOPT4_FTM2CH0SRC      (0x3 << 20)
#define BPORT1_AB_SOPT4_FTM2CH0SRC_GET(_v)  ((_v >> 20) & 0x3)
#define BPORT1_AB_SOPT4_FTM2CLKSEL      (0x1 << 26)
#define BPORT1_AB_SOPT4_FTM2CLKSEL_GET(_v)  ((_v >> 26) & 0x1)
#define BPORT1_AB_SOPT4_FTM2FLT0        (0x1 << 8)
#define BPORT1_AB_SOPT4_FTM2FLT0_GET(_v)  ((_v >> 8) & 0x1)
#define BPORT1_AB_SOPT4_FTM3CLKSEL      (0x1 << 27)
#define BPORT1_AB_SOPT4_FTM3CLKSEL_GET(_v)  ((_v >> 27) & 0x1)
#define BPORT1_AB_SOPT4_FTM3FLT0        (0x1 << 12)
#define BPORT1_AB_SOPT4_FTM3FLT0_GET(_v)  ((_v >> 12) & 0x1)
#define BPORT1_AB_SOPT4_FTM3TRG0SRC     (0x1 << 30)
#define BPORT1_AB_SOPT4_FTM3TRG0SRC_GET(_v)  ((_v >> 30) & 0x1)
#define BPORT1_AB_SOPT4_FTM3TRG1SRC     (0x1 << 31)
#define BPORT1_AB_SOPT4_FTM3TRG1SRC_GET(_v)  ((_v >> 31) & 0x1)

#define BPORT1_AB_SOPT5_POFFSET         0x1010
#define BPORT1_AB_SOPT5                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SOPT5_POFFSET)
#define BPORT1_AB_SOPT5_UART0RXSRC      (0x3 << 2)
#define BPORT1_AB_SOPT5_UART0RXSRC_GET(_v)  ((_v >> 2) & 0x3)
#define BPORT1_AB_SOPT5_UART0TXSRC      0x3
#define BPORT1_AB_SOPT5_UART0TXSRC_GET(_v)  (_v & 0x3)
#define BPORT1_AB_SOPT5_UART1RXSRC      (0x3 << 6)
#define BPORT1_AB_SOPT5_UART1RXSRC_GET(_v)  ((_v >> 6) & 0x3)
#define BPORT1_AB_SOPT5_UART1TXSRC      (0x3 << 4)
#define BPORT1_AB_SOPT5_UART1TXSRC_GET(_v)  ((_v >> 4) & 0x3)

#define BPORT1_AB_SOPT6_POFFSET         0x1014
#define BPORT1_AB_SOPT6                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SOPT6_POFFSET)
#define BPORT1_AB_SOPT6_MCC             0xffff
#define BPORT1_AB_SOPT6_MCC_GET(_v)     (_v & 0xffff)
#define BPORT1_AB_SOPT6_PCR             (0xf << 16)
#define BPORT1_AB_SOPT6_PCR_GET(_v)     ((_v >> 16) & 0xf)
#define BPORT1_AB_SOPT6_RSTFLTEN        (0x7 << 29)
#define BPORT1_AB_SOPT6_RSTFLTEN_GET(_v)  ((_v >> 29) & 0x7)
#define BPORT1_AB_SOPT6_RSTFLTSEL       (0x1f << 24)
#define BPORT1_AB_SOPT6_RSTFLTSEL_GET(_v)  ((_v >> 24) & 0x1f)

#define BPORT1_AB_SOPT7_POFFSET         0x1018
#define BPORT1_AB_SOPT7                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SOPT7_POFFSET)
#define BPORT1_AB_SOPT7_ADC0ALTTRGEN    (0x1 << 7)
#define BPORT1_AB_SOPT7_ADC0ALTTRGEN_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_SOPT7_ADC0PRETRGSEL   (0x1 << 4)
#define BPORT1_AB_SOPT7_ADC0PRETRGSEL_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_SOPT7_ADC0TRGSEL      0xf
#define BPORT1_AB_SOPT7_ADC0TRGSEL_GET(_v)  (_v & 0xf)
#define BPORT1_AB_SOPT7_ADC1ALTTRGEN    (0x1 << 15)
#define BPORT1_AB_SOPT7_ADC1ALTTRGEN_GET(_v)  ((_v >> 15) & 0x1)
#define BPORT1_AB_SOPT7_ADC1PRETRGSEL   (0x1 << 12)
#define BPORT1_AB_SOPT7_ADC1PRETRGSEL_GET(_v)  ((_v >> 12) & 0x1)
#define BPORT1_AB_SOPT7_ADC1TRGSEL      (0xf << 8)
#define BPORT1_AB_SOPT7_ADC1TRGSEL_GET(_v)  ((_v >> 8) & 0xf)
#define BPORT1_AB_SOPT7_ADC2ALTTRGEN    (0x1 << 23)
#define BPORT1_AB_SOPT7_ADC2ALTTRGEN_GET(_v)  ((_v >> 23) & 0x1)
#define BPORT1_AB_SOPT7_ADC2PRETRGSEL   (0x1 << 20)
#define BPORT1_AB_SOPT7_ADC2PRETRGSEL_GET(_v)  ((_v >> 20) & 0x1)
#define BPORT1_AB_SOPT7_ADC2TRGSEL      (0xf << 16)
#define BPORT1_AB_SOPT7_ADC2TRGSEL_GET(_v)  ((_v >> 16) & 0xf)
#define BPORT1_AB_SOPT7_ADC3ALTTRGEN    (0x1 << 31)
#define BPORT1_AB_SOPT7_ADC3ALTTRGEN_GET(_v)  ((_v >> 31) & 0x1)
#define BPORT1_AB_SOPT7_ADC3PRETRGSEL   (0x1 << 28)
#define BPORT1_AB_SOPT7_ADC3PRETRGSEL_GET(_v)  ((_v >> 28) & 0x1)
#define BPORT1_AB_SOPT7_ADC3TRGSEL      (0xf << 24)
#define BPORT1_AB_SOPT7_ADC3TRGSEL_GET(_v)  ((_v >> 24) & 0xf)

#define BPORT1_AB_SDID_POFFSET          0x1024
#define BPORT1_AB_SDID                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SDID_POFFSET)
#define BPORT1_AB_SDID_PINID            0xf
#define BPORT1_AB_SDID_PINID_GET(_v)    (_v & 0xf)
#define BPORT1_AB_SDID_FAMID            (0x7 << 4)
#define BPORT1_AB_SDID_FAMID_GET(_v)    ((_v >> 4) & 0x7)
#define BPORT1_AB_SDID_REVID            (0xf << 12)
#define BPORT1_AB_SDID_REVID_GET(_v)    ((_v >> 12) & 0xf)

#define BPORT1_AB_SCGC1_POFFSET         0x1028
#define BPORT1_AB_SCGC1                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SCGC1_POFFSET)
#define BPORT1_AB_SCGC1_UART4           (0x1 << 10)
#define BPORT1_AB_SCGC1_UART4_GET(_v)   ((_v >> 10) & 0x1)
#define BPORT1_AB_SCGC1_UART5           (0x1 << 11)
#define BPORT1_AB_SCGC1_UART5_GET(_v)   ((_v >> 11) & 0x1)
#define BPORT1_AB_SCGC1_OSC1            (0x1 << 5)
#define BPORT1_AB_SCGC1_OSC1_GET(_v)    ((_v >> 5) & 0x1)

#define BPORT1_AB_SCGC2_POFFSET         0x102c
#define BPORT1_AB_SCGC2                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SCGC2_POFFSET)
#define BPORT1_AB_SCGC2_DAC0            (0x1 << 12)
#define BPORT1_AB_SCGC2_DAC0_GET(_v)    ((_v >> 12) & 0x1)
#define BPORT1_AB_SCGC2_DAC1            (0x1 << 13)
#define BPORT1_AB_SCGC2_DAC1_GET(_v)    ((_v >> 13) & 0x1)
#define BPORT1_AB_SCGC2_ENET            0x1
#define BPORT1_AB_SCGC2_ENET_GET(_v)    (_v & 0x1)

#define BPORT1_AB_SCGC3_POFFSET         0x1030
#define BPORT1_AB_SCGC3                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SCGC3_POFFSET)
#define BPORT1_AB_SCGC3_ADC1            (0x1 << 27)
#define BPORT1_AB_SCGC3_ADC1_GET(_v)    ((_v >> 27) & 0x1)
#define BPORT1_AB_SCGC3_ADC3            (0x1 << 28)
#define BPORT1_AB_SCGC3_ADC3_GET(_v)    ((_v >> 28) & 0x1)
#define BPORT1_AB_SCGC3_DDR             (0x1 << 14)
#define BPORT1_AB_SCGC3_DDR_GET(_v)     ((_v >> 14) & 0x1)
#define BPORT1_AB_SCGC3_DSPI2           (0x1 << 12)
#define BPORT1_AB_SCGC3_DSPI2_GET(_v)   ((_v >> 12) & 0x1)
#define BPORT1_AB_SCGC3_ESDHC           (0x1 << 17)
#define BPORT1_AB_SCGC3_ESDHC_GET(_v)   ((_v >> 17) & 0x1)
#define BPORT1_AB_SCGC3_FLEXCAN1        (0x1 << 4)
#define BPORT1_AB_SCGC3_FLEXCAN1_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_SCGC3_FTM2            (0x1 << 24)
#define BPORT1_AB_SCGC3_FTM2_GET(_v)    ((_v >> 24) & 0x1)
#define BPORT1_AB_SCGC3_FTM3            (0x1 << 25)
#define BPORT1_AB_SCGC3_FTM3_GET(_v)    ((_v >> 25) & 0x1)
#define BPORT1_AB_SCGC3_NFC             (0x1 << 8)
#define BPORT1_AB_SCGC3_NFC_GET(_v)     ((_v >> 8) & 0x1)
#define BPORT1_AB_SCGC3_RNGA            0x1
#define BPORT1_AB_SCGC3_RNGA_GET(_v)    (_v & 0x1)
#define BPORT1_AB_SCGC3_SAI1            (0x1 << 15)
#define BPORT1_AB_SCGC3_SAI1_GET(_v)    ((_v >> 15) & 0x1)

#define BPORT1_AB_SCGC4_POFFSET         0x1034
#define BPORT1_AB_SCGC4                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SCGC4_POFFSET)
#define BPORT1_AB_SCGC4_CMP             (0x1 << 19)
#define BPORT1_AB_SCGC4_CMP_GET(_v)     ((_v >> 19) & 0x1)
#define BPORT1_AB_SCGC4_CMT             (0x1 << 2)
#define BPORT1_AB_SCGC4_CMT_GET(_v)     ((_v >> 2) & 0x1)
#define BPORT1_AB_SCGC4_EWM             (0x1 << 1)
#define BPORT1_AB_SCGC4_EWM_GET(_v)     ((_v >> 1) & 0x1)
#define BPORT1_AB_SCGC4_IIC1            (0x1 << 7)
#define BPORT1_AB_SCGC4_IIC1_GET(_v)    ((_v >> 7) & 0x1)
#define BPORT1_AB_SCGC4_IIC0            (0x1 << 6)
#define BPORT1_AB_SCGC4_IIC0_GET(_v)    ((_v >> 6) & 0x1)
#define BPORT1_AB_SCGC4_LLWU            (0x1 << 28)
#define BPORT1_AB_SCGC4_LLWU_GET(_v)    ((_v >> 28) & 0x1)
#define BPORT1_AB_SCGC4_MCG             (0x1 << 4)
#define BPORT1_AB_SCGC4_MCG_GET(_v)     ((_v >> 4) & 0x1)
#define BPORT1_AB_SCGC4_OSC             (0x1 << 5)
#define BPORT1_AB_SCGC4_OSC_GET(_v)     ((_v >> 5) & 0x1)
#define BPORT1_AB_SCGC4_PMC             (0x1 << 29)
#define BPORT1_AB_SCGC4_PMC_GET(_v)     ((_v >> 29) & 0x1)
#define BPORT1_AB_SCGC4_RCM             (0x1 << 31)
#define BPORT1_AB_SCGC4_RCM_GET(_v)     ((_v >> 31) & 0x1)
#define BPORT1_AB_SCGC4_SMC             (0x1 << 30)
#define BPORT1_AB_SCGC4_SMC_GET(_v)     ((_v >> 30) & 0x1)
#define BPORT1_AB_SCGC4_UART0           (0x1 << 10)
#define BPORT1_AB_SCGC4_UART0_GET(_v)   ((_v >> 10) & 0x1)
#define BPORT1_AB_SCGC4_UART1           (0x1 << 11)
#define BPORT1_AB_SCGC4_UART1_GET(_v)   ((_v >> 11) & 0x1)
#define BPORT1_AB_SCGC4_UART2           (0x1 << 12)
#define BPORT1_AB_SCGC4_UART2_GET(_v)   ((_v >> 12) & 0x1)
#define BPORT1_AB_SCGC4_UART3           (0x1 << 13)
#define BPORT1_AB_SCGC4_UART3_GET(_v)   ((_v >> 13) & 0x1)
#define BPORT1_AB_SCGC4_USBFS           (0x1 << 18)
#define BPORT1_AB_SCGC4_USBFS_GET(_v)   ((_v >> 18) & 0x1)
#define BPORT1_AB_SCGC4_VREF            (0x1 << 20)
#define BPORT1_AB_SCGC4_VREF_GET(_v)    ((_v >> 20) & 0x1)

#define BPORT1_AB_SCGC5_POFFSET         0x1038
#define BPORT1_AB_SCGC5                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SCGC5_POFFSET)
#define BPORT1_AB_SCGC5_LPTIMER         0x1
#define BPORT1_AB_SCGC5_LPTIMER_GET(_v)  (_v & 0x1)
#define BPORT1_AB_SCGC5_PORTA           (0x1 << 9)
#define BPORT1_AB_SCGC5_PORTA_GET(_v)   ((_v >> 9) & 0x1)
#define BPORT1_AB_SCGC5_PORTB           (0x1 << 10)
#define BPORT1_AB_SCGC5_PORTB_GET(_v)   ((_v >> 10) & 0x1)
#define BPORT1_AB_SCGC5_PORTC           (0x1 << 11)
#define BPORT1_AB_SCGC5_PORTC_GET(_v)   ((_v >> 11) & 0x1)
#define BPORT1_AB_SCGC5_PORTD           (0x1 << 12)
#define BPORT1_AB_SCGC5_PORTD_GET(_v)   ((_v >> 12) & 0x1)
#define BPORT1_AB_SCGC5_PORTE           (0x1 << 13)
#define BPORT1_AB_SCGC5_PORTE_GET(_v)   ((_v >> 13) & 0x1)
#define BPORT1_AB_SCGC5_PORTF           (0x1 << 14)
#define BPORT1_AB_SCGC5_PORTF_GET(_v)   ((_v >> 14) & 0x1)
#define BPORT1_AB_SCGC5_REGFILE         (0x1 << 1)
#define BPORT1_AB_SCGC5_REGFILE_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_SCGC5_TSI             (0x1 << 5)
#define BPORT1_AB_SCGC5_TSI_GET(_v)     ((_v >> 5) & 0x1)
#define BPORT1_AB_SCGC5_ATX             (0x1 << 6)
#define BPORT1_AB_SCGC5_ATX_GET(_v)     ((_v >> 6) & 0x1)
#define BPORT1_AB_SCGC5_DRYICE          (0x1 << 2)
#define BPORT1_AB_SCGC5_DRYICE_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_SCGC5_DRYICESECREG    (0x1 << 3)
#define BPORT1_AB_SCGC5_DRYICESECREG_GET(_v)  ((_v >> 3) & 0x1)
#define BPORT1_AB_SCGC5_SIM             (0x1 << 8)
#define BPORT1_AB_SCGC5_SIM_GET(_v)     ((_v >> 8) & 0x1)
#define BPORT1_AB_SCGC5_SIMDGO          (0x1 << 7)
#define BPORT1_AB_SCGC5_SIMDGO_GET(_v)  ((_v >> 7) & 0x1)
#define BPORT1_AB_SCGC5_WDT             (0x1 << 18)
#define BPORT1_AB_SCGC5_WDT_GET(_v)     ((_v >> 18) & 0x1)

#define BPORT1_AB_SCGC6_POFFSET         0x103c
#define BPORT1_AB_SCGC6                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SCGC6_POFFSET)
#define BPORT1_AB_SCGC6_ADC0            (0x1 << 27)
#define BPORT1_AB_SCGC6_ADC0_GET(_v)    ((_v >> 27) & 0x1)
#define BPORT1_AB_SCGC6_ADC2            (0x1 << 28)
#define BPORT1_AB_SCGC6_ADC2_GET(_v)    ((_v >> 28) & 0x1)
#define BPORT1_AB_SCGC6_CRC             (0x1 << 18)
#define BPORT1_AB_SCGC6_CRC_GET(_v)     ((_v >> 18) & 0x1)
#define BPORT1_AB_SCGC6_DMAMUX0         (0x1 << 1)
#define BPORT1_AB_SCGC6_DMAMUX0_GET(_v)  ((_v >> 1) & 0x1)
#define BPORT1_AB_SCGC6_DMAMUX1         (0x1 << 2)
#define BPORT1_AB_SCGC6_DMAMUX1_GET(_v)  ((_v >> 2) & 0x1)
#define BPORT1_AB_SCGC6_DSPI0           (0x1 << 12)
#define BPORT1_AB_SCGC6_DSPI0_GET(_v)   ((_v >> 12) & 0x1)
#define BPORT1_AB_SCGC6_DSPI1           (0x1 << 13)
#define BPORT1_AB_SCGC6_DSPI1_GET(_v)   ((_v >> 13) & 0x1)
#define BPORT1_AB_SCGC6_FLEXCAN0        (0x1 << 4)
#define BPORT1_AB_SCGC6_FLEXCAN0_GET(_v)  ((_v >> 4) & 0x1)
#define BPORT1_AB_SCGC6_FTM0            (0x1 << 24)
#define BPORT1_AB_SCGC6_FTM0_GET(_v)    ((_v >> 24) & 0x1)
#define BPORT1_AB_SCGC6_FTM1            (0x1 << 25)
#define BPORT1_AB_SCGC6_FTM1_GET(_v)    ((_v >> 25) & 0x1)
#define BPORT1_AB_SCGC6_PDB             (0x1 << 22)
#define BPORT1_AB_SCGC6_PDB_GET(_v)     ((_v >> 22) & 0x1)
#define BPORT1_AB_SCGC6_PIT             (0x1 << 23)
#define BPORT1_AB_SCGC6_PIT_GET(_v)     ((_v >> 23) & 0x1)
#define BPORT1_AB_SCGC6_RTC             (0x1 << 29)
#define BPORT1_AB_SCGC6_RTC_GET(_v)     ((_v >> 29) & 0x1)
#define BPORT1_AB_SCGC6_SAI0            (0x1 << 15)
#define BPORT1_AB_SCGC6_SAI0_GET(_v)    ((_v >> 15) & 0x1)
#define BPORT1_AB_SCGC6_USBHS           (0x1 << 20)
#define BPORT1_AB_SCGC6_USBHS_GET(_v)   ((_v >> 20) & 0x1)
#define BPORT1_AB_SCGC6_USBDCD          (0x1 << 21)
#define BPORT1_AB_SCGC6_USBDCD_GET(_v)  ((_v >> 21) & 0x1)
#define BPORT1_AB_SCGC6_FTF             0x1
#define BPORT1_AB_SCGC6_FTF_GET(_v)     (_v & 0x1)

#define BPORT1_AB_SCGC7_POFFSET         0x1040
#define BPORT1_AB_SCGC7                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_SCGC7_POFFSET)
#define BPORT1_AB_SCGC7_FLEXBUS         0x1
#define BPORT1_AB_SCGC7_FLEXBUS_GET(_v)  (_v & 0x1)
#define BPORT1_AB_SCGC7_DMA             (0x1 << 1)
#define BPORT1_AB_SCGC7_DMA_GET(_v)     ((_v >> 1) & 0x1)
#define BPORT1_AB_SCGC7_MPU             (0x1 << 2)
#define BPORT1_AB_SCGC7_MPU_GET(_v)     ((_v >> 2) & 0x1)

#define BPORT1_AB_CLKDIV1_POFFSET       0x1044
#define BPORT1_AB_CLKDIV1               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CLKDIV1_POFFSET)
#define BPORT1_AB_CLKDIV1_OUTDIV1       (0xf << 28)
#define BPORT1_AB_CLKDIV1_OUTDIV1_GET(_v)  ((_v >> 28) & 0xf)
#define BPORT1_AB_CLKDIV1_OUTDIV2       (0xf << 24)
#define BPORT1_AB_CLKDIV1_OUTDIV2_GET(_v)  ((_v >> 24) & 0xf)
#define BPORT1_AB_CLKDIV1_OUTDIV3       (0xf << 20)
#define BPORT1_AB_CLKDIV1_OUTDIV3_GET(_v)  ((_v >> 20) & 0xf)
#define BPORT1_AB_CLKDIV1_OUTDIV4       (0xf << 16)
#define BPORT1_AB_CLKDIV1_OUTDIV4_GET(_v)  ((_v >> 16) & 0xf)

#define BPORT1_AB_CLKDIV2_POFFSET       0x1048
#define BPORT1_AB_CLKDIV2               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CLKDIV2_POFFSET)
#define BPORT1_AB_CLKDIV2_USBFSDIV      (0x7 << 1)
#define BPORT1_AB_CLKDIV2_USBFSDIV_GET(_v)  ((_v >> 1) & 0x7)
#define BPORT1_AB_CLKDIV2_USBFSFRAC     0x1
#define BPORT1_AB_CLKDIV2_USBFSFRAC_GET(_v)  (_v & 0x1)
#define BPORT1_AB_CLKDIV2_USBHSDIV      (0x7 << 9)
#define BPORT1_AB_CLKDIV2_USBHSDIV_GET(_v)  ((_v >> 9) & 0x7)
#define BPORT1_AB_CLKDIV2_USBHSFRAC     (0x1 << 8)
#define BPORT1_AB_CLKDIV2_USBHSFRAC_GET(_v)  ((_v >> 8) & 0x1)

#define BPORT1_AB_FCFG1_POFFSET         0x104c
#define BPORT1_AB_FCFG1                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FCFG1_POFFSET)
#define BPORT1_AB_FCFG1_DEPART          (0xf << 8)
#define BPORT1_AB_FCFG1_DEPART_GET(_v)  ((_v >> 8) & 0xf)
#define BPORT1_AB_FCFG1_EESIZE          (0xf << 16)
#define BPORT1_AB_FCFG1_EESIZE_GET(_v)  ((_v >> 16) & 0xf)
#define BPORT1_AB_FCFG1_PFSIZE          (0xf << 24)
#define BPORT1_AB_FCFG1_PFSIZE_GET(_v)  ((_v >> 24) & 0xf)
#define BPORT1_AB_FCFG1_NVMSIZE         (0xf << 28)
#define BPORT1_AB_FCFG1_NVMSIZE_GET(_v)  ((_v >> 28) & 0xf)
#define BPORT1_AB_FCFG1_FTFDIS          0x1
#define BPORT1_AB_FCFG1_FTFDIS_GET(_v)  (_v & 0x1)

#define BPORT1_AB_FCFG2_POFFSET         0x1050
#define BPORT1_AB_FCFG2                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_FCFG2_POFFSET)
#define BPORT1_AB_FCFG2_MAXADDR01       (0x3f << 24)
#define BPORT1_AB_FCFG2_MAXADDR01_GET(_v)  ((_v >> 24) & 0x3f)
#define BPORT1_AB_FCFG2_MAXADDR23       (0x3f << 16)
#define BPORT1_AB_FCFG2_MAXADDR23_GET(_v)  ((_v >> 16) & 0x3f)

#define BPORT1_AB_UIDH_POFFSET          0x1054
#define BPORT1_AB_UIDH                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_UIDH_POFFSET)
#define BPORT1_AB_UIDH_UID              0xffffffff
#define BPORT1_AB_UIDH_UID_GET(_v)      (_v & 0xffffffff)

#define BPORT1_AB_UIDMH_POFFSET         0x1058
#define BPORT1_AB_UIDMH                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_UIDMH_POFFSET)
#define BPORT1_AB_UIDMH_UID             0xffffffff
#define BPORT1_AB_UIDMH_UID_GET(_v)     (_v & 0xffffffff)

#define BPORT1_AB_UIDML_POFFSET         0x105c
#define BPORT1_AB_UIDML                 (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_UIDML_POFFSET)
#define BPORT1_AB_UIDML_UID             0xffffffff
#define BPORT1_AB_UIDML_UID_GET(_v)     (_v & 0xffffffff)

#define BPORT1_AB_UIDL_POFFSET          0x1060
#define BPORT1_AB_UIDL                  (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_UIDL_POFFSET)
#define BPORT1_AB_UIDL_UID              0xffffffff
#define BPORT1_AB_UIDL_UID_GET(_v)      (_v & 0xffffffff)

#define BPORT1_AB_CLKDIV4_POFFSET       0x1068
#define BPORT1_AB_CLKDIV4               (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_CLKDIV4_POFFSET)
#define BPORT1_AB_CLKDIV4_NFCDIV        (0x1f << 27)
#define BPORT1_AB_CLKDIV4_NFCDIV_GET(_v)  ((_v >> 27) & 0x1f)
#define BPORT1_AB_CLKDIV4_NFCFRAC       (0x7 << 24)
#define BPORT1_AB_CLKDIV4_NFCFRAC_GET(_v)  ((_v >> 24) & 0x7)
#define BPORT1_AB_CLKDIV4_TRACEDIV      (0x7 << 1)
#define BPORT1_AB_CLKDIV4_TRACEDIV_GET(_v)  ((_v >> 1) & 0x7)
#define BPORT1_AB_CLKDIV4_TRACEFRAC     0x1
#define BPORT1_AB_CLKDIV4_TRACEFRAC_GET(_v)  (_v & 0x1)

#define BPORT1_AB_MCR_POFFSET           0x106c
#define BPORT1_AB_MCR                   (BPORT1 + BPORT1_AB_POFFSET + BPORT1_AB_MCR_POFFSET)
#define BPORT1_AB_MCR_PDBLOOP           (0x1 << 29)
#define BPORT1_AB_MCR_PDBLOOP_GET(_v)   ((_v >> 29) & 0x1)
#define BPORT1_AB_MCR_TRACECLKDIS       (0x1 << 31)
#define BPORT1_AB_MCR_TRACECLKDIS_GET(_v)  ((_v >> 31) & 0x1)
#define BPORT1_AB_MCR_ULPICLKOBE        (0x1 << 30)
#define BPORT1_AB_MCR_ULPICLKOBE_GET(_v)  ((_v >> 30) & 0x1)


#endif
