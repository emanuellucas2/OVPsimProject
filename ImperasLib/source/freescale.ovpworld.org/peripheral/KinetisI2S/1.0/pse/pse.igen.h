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
            Uns32 FRDE : 1;
            Uns32 FWDE : 1;
            Uns32 __pad2 : 6;
            Uns32 FRIE : 1;
            Uns32 FWIE : 1;
            Uns32 FEIE : 1;
            Uns32 SEIE : 1;
            Uns32 WSIE : 1;
            Uns32 __pad13 : 3;
            Uns32 FRF : 1;
            Uns32 FWF : 1;
            Uns32 FEF : 1;
            Uns32 SEF : 1;
            Uns32 WSF : 1;
            Uns32 __pad21 : 3;
            Uns32 SR : 1;
            Uns32 FR : 1;
            Uns32 __pad26 : 2;
            Uns32 BCE : 1;
            Uns32 DBGE : 1;
            Uns32 STOPE : 1;
            Uns32 TE : 1;
        } bits;
    } TCSR;
    union { 
        Uns32 value;
        struct {
            Uns32 TFW : 3;
        } bits;
    } TCR1;
    union { 
        Uns32 value;
        struct {
            Uns32 DIV : 8;
            Uns32 __pad8 : 16;
            Uns32 BCD : 1;
            Uns32 BCP : 1;
            Uns32 MSEL : 2;
            Uns32 BCI : 1;
            Uns32 BCS : 1;
            Uns32 SYNC : 2;
        } bits;
    } TCR2;
    union { 
        Uns32 value;
        struct {
            Uns32 WDFL : 5;
            Uns32 __pad5 : 11;
            Uns32 TCE : 2;
        } bits;
    } TCR3;
    union { 
        Uns32 value;
        struct {
            Uns32 FSD : 1;
            Uns32 FSP : 1;
            Uns32 __pad2 : 1;
            Uns32 FSE : 1;
            Uns32 MF : 1;
            Uns32 __pad5 : 3;
            Uns32 SYWD : 5;
            Uns32 __pad13 : 3;
            Uns32 FRSZ : 5;
        } bits;
    } TCR4;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 8;
            Uns32 FBT : 5;
            Uns32 __pad13 : 3;
            Uns32 W0W : 5;
            Uns32 __pad21 : 3;
            Uns32 WNW : 5;
        } bits;
    } TCR5;
    union { 
        Uns32 value;
        struct {
            Uns32 TDR : 32;
        } bits;
    } TDR0;
    union { 
        Uns32 value;
        struct {
            Uns32 TDR : 32;
        } bits;
    } TDR1;
    union { 
        Uns32 value;
        struct {
            Uns32 RFP : 4;
            Uns32 __pad4 : 12;
            Uns32 WFP : 4;
        } bits;
    } TFR0;
    union { 
        Uns32 value;
        struct {
            Uns32 RFP : 4;
            Uns32 __pad4 : 12;
            Uns32 WFP : 4;
        } bits;
    } TFR1;
    union { 
        Uns32 value;
        struct {
            Uns32 TWM : 32;
        } bits;
    } TMR;
    union { 
        Uns32 value;
        struct {
            Uns32 FRDE : 1;
            Uns32 FWDE : 1;
            Uns32 __pad2 : 6;
            Uns32 FRIE : 1;
            Uns32 FWIE : 1;
            Uns32 FEIE : 1;
            Uns32 SEIE : 1;
            Uns32 WSIE : 1;
            Uns32 __pad13 : 3;
            Uns32 FRF : 1;
            Uns32 FWF : 1;
            Uns32 FEF : 1;
            Uns32 SEF : 1;
            Uns32 WSF : 1;
            Uns32 __pad21 : 3;
            Uns32 SR : 1;
            Uns32 FR : 1;
            Uns32 __pad26 : 2;
            Uns32 BCE : 1;
            Uns32 DBGE : 1;
            Uns32 STOPE : 1;
            Uns32 RE : 1;
        } bits;
    } RCSR;
    union { 
        Uns32 value;
        struct {
            Uns32 RFW : 3;
        } bits;
    } RCR1;
    union { 
        Uns32 value;
        struct {
            Uns32 DIV : 8;
            Uns32 __pad8 : 16;
            Uns32 BCD : 1;
            Uns32 BCP : 1;
            Uns32 MSEL : 2;
            Uns32 BCI : 1;
            Uns32 BCS : 1;
            Uns32 SYNC : 2;
        } bits;
    } RCR2;
    union { 
        Uns32 value;
        struct {
            Uns32 WDFL : 5;
            Uns32 __pad5 : 11;
            Uns32 RCE : 2;
        } bits;
    } RCR3;
    union { 
        Uns32 value;
        struct {
            Uns32 FSD : 1;
            Uns32 FSP : 1;
            Uns32 __pad2 : 1;
            Uns32 FSE : 1;
            Uns32 MF : 1;
            Uns32 __pad5 : 3;
            Uns32 SYWD : 5;
            Uns32 __pad13 : 3;
            Uns32 FRSZ : 5;
        } bits;
    } RCR4;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 8;
            Uns32 FBT : 5;
            Uns32 __pad13 : 3;
            Uns32 W0W : 5;
            Uns32 __pad21 : 3;
            Uns32 WNW : 5;
        } bits;
    } RCR5;
    union { 
        Uns32 value;
        struct {
            Uns32 RDR : 32;
        } bits;
    } RDR0;
    union { 
        Uns32 value;
        struct {
            Uns32 RDR : 32;
        } bits;
    } RDR1;
    union { 
        Uns32 value;
        struct {
            Uns32 RFP : 4;
            Uns32 __pad4 : 12;
            Uns32 WFP : 4;
        } bits;
    } RFR0;
    union { 
        Uns32 value;
        struct {
            Uns32 RFP : 4;
            Uns32 __pad4 : 12;
            Uns32 WFP : 4;
        } bits;
    } RFR1;
    union { 
        Uns32 value;
        struct {
            Uns32 RWM : 32;
        } bits;
    } RMR;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 24;
            Uns32 MICS : 2;
            Uns32 __pad26 : 4;
            Uns32 MOE : 1;
            Uns32 DUF : 1;
        } bits;
    } MCR;
    union { 
        Uns32 value;
        struct {
            Uns32 DIVIDE : 12;
            Uns32 FRACT : 8;
        } bits;
    } MDR;
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

#define BPORT1_AB_TCSR_WRMASK           0xf31c1f03
#define BPORT1_AB_TCSR_WRNMASK          (0xce3e0fc)
#define BPORT1_AB_TCSR_WIDTH            32
#define BPORT1_AB_TCR1_WRMASK           0x7
#define BPORT1_AB_TCR1_WRNMASK          (0xfffffff8)
#define BPORT1_AB_TCR1_WIDTH            32
#define BPORT1_AB_TCR2_WRMASK           0xff0000ff
#define BPORT1_AB_TCR2_WRNMASK          (0xffff00)
#define BPORT1_AB_TCR2_WIDTH            32
#define BPORT1_AB_TCR3_WRMASK           0x3001f
#define BPORT1_AB_TCR3_WRNMASK          (0xfffcffe0)
#define BPORT1_AB_TCR3_WIDTH            32
#define BPORT1_AB_TCR4_WRMASK           0x1f1f1b
#define BPORT1_AB_TCR4_WRNMASK          (0xffe0e0e4)
#define BPORT1_AB_TCR4_WIDTH            32
#define BPORT1_AB_TCR5_WRMASK           0x1f1f1f00
#define BPORT1_AB_TCR5_WRNMASK          (0xe0e0e0ff)
#define BPORT1_AB_TCR5_WIDTH            32
#define BPORT1_AB_TDR0_WRMASK           0xffffffff
#define BPORT1_AB_TDR0_WRNMASK          (0x0)
#define BPORT1_AB_TDR0_WIDTH            32
#define BPORT1_AB_TDR1_WRMASK           0xffffffff
#define BPORT1_AB_TDR1_WRNMASK          (0x0)
#define BPORT1_AB_TDR1_WIDTH            32
#define BPORT1_AB_TFR0_WIDTH            32
#define BPORT1_AB_TFR1_WIDTH            32
#define BPORT1_AB_TMR_WRMASK            0xffffffff
#define BPORT1_AB_TMR_WRNMASK           (0x0)
#define BPORT1_AB_TMR_WIDTH             32
#define BPORT1_AB_RCSR_WRMASK           0xf31c1f03
#define BPORT1_AB_RCSR_WRNMASK          (0xce3e0fc)
#define BPORT1_AB_RCSR_WIDTH            32
#define BPORT1_AB_RCR1_WRMASK           0x7
#define BPORT1_AB_RCR1_WRNMASK          (0xfffffff8)
#define BPORT1_AB_RCR1_WIDTH            32
#define BPORT1_AB_RCR2_WRMASK           0xff0000ff
#define BPORT1_AB_RCR2_WRNMASK          (0xffff00)
#define BPORT1_AB_RCR2_WIDTH            32
#define BPORT1_AB_RCR3_WRMASK           0x3001f
#define BPORT1_AB_RCR3_WRNMASK          (0xfffcffe0)
#define BPORT1_AB_RCR3_WIDTH            32
#define BPORT1_AB_RCR4_WRMASK           0x1f1f1b
#define BPORT1_AB_RCR4_WRNMASK          (0xffe0e0e4)
#define BPORT1_AB_RCR4_WIDTH            32
#define BPORT1_AB_RCR5_WRMASK           0x1f1f1f00
#define BPORT1_AB_RCR5_WRNMASK          (0xe0e0e0ff)
#define BPORT1_AB_RCR5_WIDTH            32
#define BPORT1_AB_RDR0_WIDTH            32
#define BPORT1_AB_RDR1_WIDTH            32
#define BPORT1_AB_RFR0_WIDTH            32
#define BPORT1_AB_RFR1_WIDTH            32
#define BPORT1_AB_RMR_WRMASK            0xffffffff
#define BPORT1_AB_RMR_WRNMASK           (0x0)
#define BPORT1_AB_RMR_WIDTH             32
#define BPORT1_AB_MCR_WRMASK            0x43000000
#define BPORT1_AB_MCR_WRNMASK           (0xbcffffff)
#define BPORT1_AB_MCR_WIDTH             32
#define BPORT1_AB_MDR_WRMASK            0xfffff
#define BPORT1_AB_MDR_WRNMASK           (0xfff00000)
#define BPORT1_AB_MDR_WIDTH             32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
