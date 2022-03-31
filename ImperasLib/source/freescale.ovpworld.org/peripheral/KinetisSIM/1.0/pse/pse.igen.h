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

#ifndef PSE_IGEN_H
#define PSE_IGEN_H                      

#ifdef _PSE_
#    include "peripheral/impTypes.h"
#    include "peripheral/bhm.h"
#    include "peripheral/bhmHttp.h"
#    include "peripheral/ppm.h"
#else
#    include "hostapi/impTypes.h"
#endif

#ifdef _PSE_
//////////////////////////////////// Externs ///////////////////////////////////

extern Uns32 diagnosticLevel;


/////////////////////////// Dynamic Diagnostic Macros //////////////////////////

// Bottom two bits of word used for PSE diagnostics
#define PSE_DIAG_LOW                    (BHM_DIAG_MASK_LOW(diagnosticLevel))
#define PSE_DIAG_MEDIUM                 (BHM_DIAG_MASK_MEDIUM(diagnosticLevel))

#define PSE_DIAG_HIGH                   (BHM_DIAG_MASK_HIGH(diagnosticLevel))
// Next two bits of word used for PSE semihost/intercept library diagnostics
#define PSE_DIAG_SEMIHOST               (BHM_DIAG_MASK_SEMIHOST(diagnosticLevel))

#endif
/////////////////////////// Register data declaration //////////////////////////

typedef struct bport1_ab_dataS { 
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 12;
            Uns32 RAMSIZE : 4;
            Uns32 __pad16 : 3;
            Uns32 OSC32KSEL : 1;
            Uns32 __pad20 : 9;
            Uns32 USBVSTBY : 1;
            Uns32 USBSSTBY : 1;
            Uns32 USBREGEN : 1;
        } bits;
    } SOPT1;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 24;
            Uns32 URWE : 1;
            Uns32 UVSWE : 1;
            Uns32 USSWE : 1;
        } bits;
    } SOPT1CFG;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 2;
            Uns32 USBHSRC : 2;
            Uns32 RTCCLKOUTSEL : 1;
            Uns32 CLKOUTSEL : 3;
            Uns32 FBSL : 2;
            Uns32 USBH_CLKSEL : 1;
            Uns32 CMTUARTPAD : 1;
            Uns32 TRACECLKSEL : 1;
            Uns32 __pad13 : 2;
            Uns32 NFC_CLKSEL : 1;
            Uns32 PLLFLLSEL : 2;
            Uns32 USBF_CLKSEL : 1;
            Uns32 __pad19 : 1;
            Uns32 TIMESRC : 2;
            Uns32 USBFSRC : 2;
            Uns32 __pad24 : 4;
            Uns32 ESDHCSRC : 2;
            Uns32 NFCSRC : 2;
        } bits;
    } SOPT2;
    union { 
        Uns32 value;
        struct {
            Uns32 FTM0FLT0 : 1;
            Uns32 FTM0FLT1 : 1;
            Uns32 FTM0FLT2 : 1;
            Uns32 FTM0FLT3 : 1;
            Uns32 FTM1FLT0 : 1;
            Uns32 __pad5 : 3;
            Uns32 FTM2FLT0 : 1;
            Uns32 __pad9 : 3;
            Uns32 FTM3FLT0 : 1;
            Uns32 __pad13 : 5;
            Uns32 FTM1CH0SRC : 2;
            Uns32 FTM2CH0SRC : 2;
            Uns32 __pad22 : 2;
            Uns32 FTM0CLKSEL : 1;
            Uns32 FTM1CLKSEL : 1;
            Uns32 FTM2CLKSEL : 1;
            Uns32 FTM3CLKSEL : 1;
            Uns32 FTM0TRG0SRC : 1;
            Uns32 FTM0TRG1SRC : 1;
            Uns32 FTM3TRG0SRC : 1;
            Uns32 FTM3TRG1SRC : 1;
        } bits;
    } SOPT4;
    union { 
        Uns32 value;
        struct {
            Uns32 UART0TXSRC : 2;
            Uns32 UART0RXSRC : 2;
            Uns32 UART1TXSRC : 2;
            Uns32 UART1RXSRC : 2;
        } bits;
    } SOPT5;
    union { 
        Uns32 value;
        struct {
            Uns32 MCC : 16;
            Uns32 PCR : 4;
            Uns32 __pad20 : 4;
            Uns32 RSTFLTSEL : 5;
            Uns32 RSTFLTEN : 3;
        } bits;
    } SOPT6;
    union { 
        Uns32 value;
        struct {
            Uns32 ADC0TRGSEL : 4;
            Uns32 ADC0PRETRGSEL : 1;
            Uns32 __pad5 : 2;
            Uns32 ADC0ALTTRGEN : 1;
            Uns32 ADC1TRGSEL : 4;
            Uns32 ADC1PRETRGSEL : 1;
            Uns32 __pad13 : 2;
            Uns32 ADC1ALTTRGEN : 1;
            Uns32 ADC2TRGSEL : 4;
            Uns32 ADC2PRETRGSEL : 1;
            Uns32 __pad21 : 2;
            Uns32 ADC2ALTTRGEN : 1;
            Uns32 ADC3TRGSEL : 4;
            Uns32 ADC3PRETRGSEL : 1;
            Uns32 __pad29 : 2;
            Uns32 ADC3ALTTRGEN : 1;
        } bits;
    } SOPT7;
    union { 
        Uns32 value;
        struct {
            Uns32 PINID : 4;
            Uns32 FAMID : 3;
            Uns32 __pad7 : 5;
            Uns32 REVID : 4;
        } bits;
    } SDID;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 5;
            Uns32 OSC1 : 1;
            Uns32 __pad6 : 4;
            Uns32 UART4 : 1;
            Uns32 UART5 : 1;
        } bits;
    } SCGC1;
    union { 
        Uns32 value;
        struct {
            Uns32 ENET : 1;
            Uns32 __pad1 : 11;
            Uns32 DAC0 : 1;
            Uns32 DAC1 : 1;
        } bits;
    } SCGC2;
    union { 
        Uns32 value;
        struct {
            Uns32 RNGA : 1;
            Uns32 __pad1 : 3;
            Uns32 FLEXCAN1 : 1;
            Uns32 __pad5 : 3;
            Uns32 NFC : 1;
            Uns32 __pad9 : 3;
            Uns32 DSPI2 : 1;
            Uns32 __pad13 : 1;
            Uns32 DDR : 1;
            Uns32 SAI1 : 1;
            Uns32 __pad16 : 1;
            Uns32 ESDHC : 1;
            Uns32 __pad18 : 6;
            Uns32 FTM2 : 1;
            Uns32 FTM3 : 1;
            Uns32 __pad26 : 1;
            Uns32 ADC1 : 1;
            Uns32 ADC3 : 1;
        } bits;
    } SCGC3;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 1;
            Uns32 EWM : 1;
            Uns32 CMT : 1;
            Uns32 __pad3 : 1;
            Uns32 MCG : 1;
            Uns32 OSC : 1;
            Uns32 IIC0 : 1;
            Uns32 IIC1 : 1;
            Uns32 __pad8 : 2;
            Uns32 UART0 : 1;
            Uns32 UART1 : 1;
            Uns32 UART2 : 1;
            Uns32 UART3 : 1;
            Uns32 __pad14 : 4;
            Uns32 USBFS : 1;
            Uns32 CMP : 1;
            Uns32 VREF : 1;
            Uns32 __pad21 : 7;
            Uns32 LLWU : 1;
            Uns32 PMC : 1;
            Uns32 SMC : 1;
            Uns32 RCM : 1;
        } bits;
    } SCGC4;
    union { 
        Uns32 value;
        struct {
            Uns32 LPTIMER : 1;
            Uns32 REGFILE : 1;
            Uns32 DRYICE : 1;
            Uns32 DRYICESECREG : 1;
            Uns32 __pad4 : 1;
            Uns32 TSI : 1;
            Uns32 ATX : 1;
            Uns32 SIMDGO : 1;
            Uns32 SIM : 1;
            Uns32 PORTA : 1;
            Uns32 PORTB : 1;
            Uns32 PORTC : 1;
            Uns32 PORTD : 1;
            Uns32 PORTE : 1;
            Uns32 PORTF : 1;
            Uns32 __pad15 : 3;
            Uns32 WDT : 1;
        } bits;
    } SCGC5;
    union { 
        Uns32 value;
        struct {
            Uns32 FTF : 1;
            Uns32 DMAMUX0 : 1;
            Uns32 DMAMUX1 : 1;
            Uns32 __pad3 : 1;
            Uns32 FLEXCAN0 : 1;
            Uns32 __pad5 : 7;
            Uns32 DSPI0 : 1;
            Uns32 DSPI1 : 1;
            Uns32 __pad14 : 1;
            Uns32 SAI0 : 1;
            Uns32 __pad16 : 2;
            Uns32 CRC : 1;
            Uns32 __pad19 : 1;
            Uns32 USBHS : 1;
            Uns32 USBDCD : 1;
            Uns32 PDB : 1;
            Uns32 PIT : 1;
            Uns32 FTM0 : 1;
            Uns32 FTM1 : 1;
            Uns32 __pad26 : 1;
            Uns32 ADC0 : 1;
            Uns32 ADC2 : 1;
            Uns32 RTC : 1;
        } bits;
    } SCGC6;
    union { 
        Uns32 value;
        struct {
            Uns32 FLEXBUS : 1;
            Uns32 DMA : 1;
            Uns32 MPU : 1;
        } bits;
    } SCGC7;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 16;
            Uns32 OUTDIV4 : 4;
            Uns32 OUTDIV3 : 4;
            Uns32 OUTDIV2 : 4;
            Uns32 OUTDIV1 : 4;
        } bits;
    } CLKDIV1;
    union { 
        Uns32 value;
        struct {
            Uns32 USBFSFRAC : 1;
            Uns32 USBFSDIV : 3;
            Uns32 __pad4 : 4;
            Uns32 USBHSFRAC : 1;
            Uns32 USBHSDIV : 3;
        } bits;
    } CLKDIV2;
    union { 
        Uns32 value;
        struct {
            Uns32 FTFDIS : 1;
            Uns32 __pad1 : 7;
            Uns32 DEPART : 4;
            Uns32 __pad12 : 4;
            Uns32 EESIZE : 4;
            Uns32 __pad20 : 4;
            Uns32 PFSIZE : 4;
            Uns32 NVMSIZE : 4;
        } bits;
    } FCFG1;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 16;
            Uns32 MAXADDR23 : 6;
            Uns32 __pad22 : 2;
            Uns32 MAXADDR01 : 6;
        } bits;
    } FCFG2;
    union { 
        Uns32 value;
        struct {
            Uns32 UID : 32;
        } bits;
    } UIDH;
    union { 
        Uns32 value;
        struct {
            Uns32 UID : 32;
        } bits;
    } UIDMH;
    union { 
        Uns32 value;
        struct {
            Uns32 UID : 32;
        } bits;
    } UIDML;
    union { 
        Uns32 value;
        struct {
            Uns32 UID : 32;
        } bits;
    } UIDL;
    union { 
        Uns32 value;
        struct {
            Uns32 TRACEFRAC : 1;
            Uns32 TRACEDIV : 3;
            Uns32 __pad4 : 20;
            Uns32 NFCFRAC : 3;
            Uns32 NFCDIV : 5;
        } bits;
    } CLKDIV4;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 29;
            Uns32 PDBLOOP : 1;
            Uns32 ULPICLKOBE : 1;
            Uns32 TRACECLKDIS : 1;
        } bits;
    } MCR;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          Reset;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_SOPT1_WRMASK          0xe0080000
#define BPORT1_AB_SOPT1_WRNMASK         (0x1ff7ffff)
#define BPORT1_AB_SOPT1_WIDTH           32
#define BPORT1_AB_SOPT1CFG_WRMASK       0x7000000
#define BPORT1_AB_SOPT1CFG_WRNMASK      (0xf8ffffff)
#define BPORT1_AB_SOPT1CFG_WIDTH        32
#define BPORT1_AB_SOPT2_WRMASK          0xf0f79bfc
#define BPORT1_AB_SOPT2_WRNMASK         (0xf086403)
#define BPORT1_AB_SOPT2_WIDTH           32
#define BPORT1_AB_SOPT4_WRMASK          0xff3c111f
#define BPORT1_AB_SOPT4_WRNMASK         (0xc3eee0)
#define BPORT1_AB_SOPT4_WIDTH           32
#define BPORT1_AB_SOPT5_WRMASK          0xff
#define BPORT1_AB_SOPT5_WRNMASK         (0xffffff00)
#define BPORT1_AB_SOPT5_WIDTH           32
#define BPORT1_AB_SOPT6_WRMASK          0xfffff
#define BPORT1_AB_SOPT6_WRNMASK         (0xfff00000)
#define BPORT1_AB_SOPT6_WIDTH           32
#define BPORT1_AB_SOPT7_WRMASK          0x9f9f9f9f
#define BPORT1_AB_SOPT7_WRNMASK         (0x60606060)
#define BPORT1_AB_SOPT7_WIDTH           32
#define BPORT1_AB_SDID_WIDTH            32
#define BPORT1_AB_SCGC1_WRMASK          0xc20
#define BPORT1_AB_SCGC1_WRNMASK         (0xfffff3df)
#define BPORT1_AB_SCGC1_WIDTH           32
#define BPORT1_AB_SCGC2_WRMASK          0x3001
#define BPORT1_AB_SCGC2_WRNMASK         (0xffffcffe)
#define BPORT1_AB_SCGC2_WIDTH           32
#define BPORT1_AB_SCGC3_WRMASK          0x1b029111
#define BPORT1_AB_SCGC3_WRNMASK         (0xe4fd6eee)
#define BPORT1_AB_SCGC3_WIDTH           32
#define BPORT1_AB_SCGC4_WRMASK          0x101c3cc6
#define BPORT1_AB_SCGC4_WRNMASK         (0xefe3c339)
#define BPORT1_AB_SCGC4_WIDTH           32
#define BPORT1_AB_SCGC5_WRMASK          0x7e23
#define BPORT1_AB_SCGC5_WRNMASK         (0xffff81dc)
#define BPORT1_AB_SCGC5_WIDTH           32
#define BPORT1_AB_SCGC6_WRMASK          0x3bf4b016
#define BPORT1_AB_SCGC6_WRNMASK         (0xc40b4fe9)
#define BPORT1_AB_SCGC6_WIDTH           32
#define BPORT1_AB_SCGC7_WRMASK          0x7
#define BPORT1_AB_SCGC7_WRNMASK         (0xfffffff8)
#define BPORT1_AB_SCGC7_WIDTH           32
#define BPORT1_AB_CLKDIV1_WRMASK        0xffff0000
#define BPORT1_AB_CLKDIV1_WRNMASK       (0xffff)
#define BPORT1_AB_CLKDIV1_WIDTH         32
#define BPORT1_AB_CLKDIV2_WRMASK        0xf0f
#define BPORT1_AB_CLKDIV2_WRNMASK       (0xfffff0f0)
#define BPORT1_AB_CLKDIV2_WIDTH         32
#define BPORT1_AB_FCFG1_WRMASK          0x1
#define BPORT1_AB_FCFG1_WRNMASK         (0xfffffffe)
#define BPORT1_AB_FCFG1_WIDTH           32
#define BPORT1_AB_FCFG2_WIDTH           32
#define BPORT1_AB_UIDH_WIDTH            32
#define BPORT1_AB_UIDMH_WIDTH           32
#define BPORT1_AB_UIDML_WIDTH           32
#define BPORT1_AB_UIDL_WIDTH            32
#define BPORT1_AB_CLKDIV4_WRMASK        0xff00000f
#define BPORT1_AB_CLKDIV4_WRNMASK       (0xfffff0)
#define BPORT1_AB_CLKDIV4_WIDTH         32
#define BPORT1_AB_MCR_WRMASK            0xe0000000
#define BPORT1_AB_MCR_WRNMASK           (0x1fffffff)
#define BPORT1_AB_MCR_WIDTH             32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
