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
            Uns32 TSR : 32;
        } bits;
    } TSR;
    union { 
        Uns32 value;
        struct {
            Uns32 TPR : 16;
        } bits;
    } TPR;
    union { 
        Uns32 value;
        struct {
            Uns32 TAR : 32;
        } bits;
    } TAR;
    union { 
        Uns32 value;
        struct {
            Uns32 TCR : 8;
            Uns32 CIR : 8;
            Uns32 TCV : 8;
            Uns32 CIC : 8;
        } bits;
    } TCR;
    union { 
        Uns32 value;
        struct {
            Uns32 SWR : 1;
            Uns32 WPE : 1;
            Uns32 SUP : 1;
            Uns32 UM : 1;
            Uns32 __pad4 : 4;
            Uns32 OSCE : 1;
            Uns32 CLKO : 1;
            Uns32 SC16P : 1;
            Uns32 SC8P : 1;
            Uns32 SC4P : 1;
            Uns32 SC2P : 1;
        } bits;
    } CR;
    union { 
        Uns32 value;
        struct {
            Uns32 TIF : 1;
            Uns32 TOF : 1;
            Uns32 TAF : 1;
            Uns32 MOF : 1;
            Uns32 TCE : 1;
        } bits;
    } SR;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 3;
            Uns32 TCL : 1;
            Uns32 CRL : 1;
            Uns32 SRL : 1;
            Uns32 LRL : 1;
            Uns32 __pad7 : 1;
            Uns32 TTSL : 1;
            Uns32 MEL : 1;
            Uns32 MCLL : 1;
            Uns32 MCHL : 1;
            Uns32 TEL : 1;
            Uns32 TDL : 1;
            Uns32 TTL : 1;
            Uns32 TIL : 1;
        } bits;
    } LR;
    union { 
        Uns32 value;
        struct {
            Uns32 TIIE : 1;
            Uns32 TOIE : 1;
            Uns32 TAIE : 1;
            Uns32 MOIE : 1;
            Uns32 TSIE : 1;
        } bits;
    } IER;
    union { 
        Uns32 value;
        struct {
            Uns32 TTS : 32;
        } bits;
    } TTSR;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 4;
            Uns32 MCE : 1;
        } bits;
    } MER;
    union { 
        Uns32 value;
        struct {
            Uns32 MCL : 32;
        } bits;
    } MCLR;
    union { 
        Uns32 value;
        struct {
            Uns32 MCH : 32;
        } bits;
    } MCHR;
    union { 
        Uns32 value;
        struct {
            Uns32 DTE : 1;
            Uns32 VTE : 1;
            Uns32 CTE : 1;
            Uns32 TTE : 1;
            Uns32 FSE : 1;
            Uns32 TME : 1;
        } bits;
    } TER;
    union { 
        Uns32 value;
        struct {
            Uns32 DTF : 1;
            Uns32 VTF : 1;
            Uns32 CTF : 1;
            Uns32 TTF : 1;
            Uns32 FSF : 1;
            Uns32 TMF : 1;
        } bits;
    } TDR;
    union { 
        Uns32 value;
        struct {
            Uns32 VDTL : 3;
            Uns32 VDTH : 3;
            Uns32 CDTH : 3;
            Uns32 CDTL : 3;
            Uns32 TDTH : 3;
            Uns32 TDTL : 3;
        } bits;
    } TTR;
    union { 
        Uns32 value;
        struct {
            Uns32 DTIE : 1;
            Uns32 VTIE : 1;
            Uns32 CTIE : 1;
            Uns32 TTIE : 1;
            Uns32 FSIE : 1;
            Uns32 TMIE : 1;
        } bits;
    } TIR;
    union { 
        Uns32 value;
        struct {
            Uns32 TSRW : 1;
            Uns32 TPRW : 1;
            Uns32 TARW : 1;
            Uns32 TCRW : 1;
            Uns32 CRW : 1;
            Uns32 SRW : 1;
            Uns32 LRW : 1;
            Uns32 IERW : 1;
            Uns32 TTSW : 1;
            Uns32 MERW : 1;
            Uns32 MCLW : 1;
            Uns32 MCHW : 1;
            Uns32 TERW : 1;
            Uns32 TDRW : 1;
            Uns32 TTRW : 1;
            Uns32 TIRW : 1;
        } bits;
    } WAR;
    union { 
        Uns32 value;
        struct {
            Uns32 TSRR : 1;
            Uns32 TPRR : 1;
            Uns32 TARR : 1;
            Uns32 TCRR : 1;
            Uns32 CRR : 1;
            Uns32 SRR : 1;
            Uns32 LRR : 1;
            Uns32 IERR : 1;
            Uns32 TTSR : 1;
            Uns32 MERR : 1;
            Uns32 MCLR : 1;
            Uns32 MCHR : 1;
            Uns32 TERR : 1;
            Uns32 TDRR : 1;
            Uns32 TTRR : 1;
            Uns32 TIRR : 1;
        } bits;
    } RAR;
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

#define BPORT1_AB_TSR_WRMASK            0xffffffff
#define BPORT1_AB_TSR_WRNMASK           (0x0)
#define BPORT1_AB_TSR_WIDTH             32
#define BPORT1_AB_TPR_WRMASK            0xffff
#define BPORT1_AB_TPR_WRNMASK           (0xffff0000)
#define BPORT1_AB_TPR_WIDTH             32
#define BPORT1_AB_TAR_WRMASK            0xffffffff
#define BPORT1_AB_TAR_WRNMASK           (0x0)
#define BPORT1_AB_TAR_WIDTH             32
#define BPORT1_AB_TCR_WRMASK            0xffff
#define BPORT1_AB_TCR_WRNMASK           (0xffff0000)
#define BPORT1_AB_TCR_WIDTH             32
#define BPORT1_AB_CR_WRMASK             0x3f0f
#define BPORT1_AB_CR_WRNMASK            (0xffffc0f0)
#define BPORT1_AB_CR_WIDTH              32
#define BPORT1_AB_SR_WRMASK             0x10
#define BPORT1_AB_SR_WRNMASK            (0xffffffef)
#define BPORT1_AB_SR_WIDTH              32
#define BPORT1_AB_LR_WRMASK             0xff78
#define BPORT1_AB_LR_WRNMASK            (0xffff0087)
#define BPORT1_AB_LR_WIDTH              32
#define BPORT1_AB_IER_WRMASK            0x1f
#define BPORT1_AB_IER_WRNMASK           (0xffffffe0)
#define BPORT1_AB_IER_WIDTH             32
#define BPORT1_AB_TTSR_WIDTH            32
#define BPORT1_AB_MER_WRMASK            0x1f
#define BPORT1_AB_MER_WRNMASK           (0xffffffe0)
#define BPORT1_AB_MER_WIDTH             32
#define BPORT1_AB_MCLR_WRMASK           0xffffffff
#define BPORT1_AB_MCLR_WRNMASK          (0x0)
#define BPORT1_AB_MCLR_WIDTH            32
#define BPORT1_AB_MCHR_WRMASK           0xffffffff
#define BPORT1_AB_MCHR_WRNMASK          (0x0)
#define BPORT1_AB_MCHR_WIDTH            32
#define BPORT1_AB_TER_WRMASK            0x3e
#define BPORT1_AB_TER_WRNMASK           (0xffffffc1)
#define BPORT1_AB_TER_WIDTH             32
#define BPORT1_AB_TDR_WRMASK            0x3e
#define BPORT1_AB_TDR_WRNMASK           (0xffffffc1)
#define BPORT1_AB_TDR_WIDTH             32
#define BPORT1_AB_TTR_WRMASK            0x3ffff
#define BPORT1_AB_TTR_WRNMASK           (0xfffc0000)
#define BPORT1_AB_TTR_WIDTH             32
#define BPORT1_AB_TIR_WRMASK            0x3e
#define BPORT1_AB_TIR_WRNMASK           (0xffffffc1)
#define BPORT1_AB_TIR_WIDTH             32
#define BPORT1_AB_WAR_WRMASK            0xffff
#define BPORT1_AB_WAR_WRNMASK           (0xffff0000)
#define BPORT1_AB_WAR_WIDTH             32
#define BPORT1_AB_RAR_WRMASK            0xffff
#define BPORT1_AB_RAR_WRNMASK           (0xffff0000)
#define BPORT1_AB_RAR_WIDTH             32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
