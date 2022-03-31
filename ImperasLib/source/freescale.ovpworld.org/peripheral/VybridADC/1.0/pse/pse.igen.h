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
            Uns32 ADCH : 5;
            Uns32 __pad5 : 2;
            Uns32 AIEN : 1;
        } bits;
    } HC0;
    union { 
        Uns32 value;
        struct {
            Uns32 ADCH : 5;
            Uns32 __pad5 : 2;
            Uns32 AIEN : 1;
        } bits;
    } HC1;
    union { 
        Uns32 value;
        struct {
            Uns32 COCO1 : 1;
            Uns32 COCO2 : 1;
        } bits;
    } HS;
    union { 
        Uns32 value;
        struct {
            Uns32 D : 12;
        } bits;
    } R0;
    union { 
        Uns32 value;
        struct {
            Uns32 D : 12;
        } bits;
    } R1;
    union { 
        Uns32 value;
        struct {
            Uns32 ADICLK : 2;
            Uns32 MODE : 2;
            Uns32 ADLSMP : 1;
            Uns32 ADIV : 2;
            Uns32 ADLPC : 1;
            Uns32 ADSTS : 2;
            Uns32 ADHSC : 1;
            Uns32 REFSEL : 2;
            Uns32 ADTRG : 1;
            Uns32 AVGS : 2;
            Uns32 OVWREN : 1;
        } bits;
    } CFG;
    union { 
        Uns32 value;
        struct {
            Uns32 ADACKEN : 1;
            Uns32 DMAEN : 1;
            Uns32 ACREN : 1;
            Uns32 ACFGT : 1;
            Uns32 ACFE : 1;
            Uns32 AVGE : 1;
            Uns32 ADCO : 1;
            Uns32 CAL : 1;
        } bits;
    } GC;
    union { 
        Uns32 value;
        struct {
            Uns32 ADACT : 1;
            Uns32 CALF : 1;
            Uns32 AWKST : 1;
        } bits;
    } GS;
    union { 
        Uns32 value;
        struct {
            Uns32 CV1 : 12;
            Uns32 __pad12 : 4;
            Uns32 CV2 : 12;
        } bits;
    } CV;
    union { 
        Uns32 value;
        struct {
            Uns32 OFS : 12;
            Uns32 SIGN : 1;
        } bits;
    } OFS;
    union { 
        Uns32 value;
        struct {
            Uns32 CAL_CODE : 4;
        } bits;
    } CAL;
    union { 
        Uns32 value;
        struct {
            Uns32 ADPC0 : 1;
            Uns32 ADPC1 : 1;
            Uns32 ADPC2 : 1;
            Uns32 ADPC3 : 1;
            Uns32 ADPC4 : 1;
            Uns32 ADPC5 : 1;
            Uns32 ADPC6 : 1;
            Uns32 ADPC7 : 1;
            Uns32 ADPC8 : 1;
            Uns32 ADPC9 : 1;
            Uns32 ADPC10 : 1;
            Uns32 ADPC11 : 1;
            Uns32 ADPC12 : 1;
            Uns32 ADPC13 : 1;
            Uns32 ADPC14 : 1;
            Uns32 ADPC15 : 1;
            Uns32 ADPC16 : 1;
            Uns32 ADPC17 : 1;
            Uns32 ADPC18 : 1;
            Uns32 ADPC19 : 1;
            Uns32 ADPC20 : 1;
            Uns32 ADPC21 : 1;
            Uns32 ADPC22 : 1;
            Uns32 ADPC23 : 1;
        } bits;
    } PCTL;
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

PPM_REG_WRITE_CB(GSWrite1C);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_HC0_WRMASK            0x9f
#define BPORT1_AB_HC0_WRNMASK           (0xffffff60)
#define BPORT1_AB_HC0_WIDTH             32
#define BPORT1_AB_HC1_WRMASK            0x9f
#define BPORT1_AB_HC1_WRNMASK           (0xffffff60)
#define BPORT1_AB_HC1_WIDTH             32
#define BPORT1_AB_HS_WIDTH              32
#define BPORT1_AB_R0_WIDTH              32
#define BPORT1_AB_R1_WIDTH              32
#define BPORT1_AB_CFG_WRMASK            0x1ffff
#define BPORT1_AB_CFG_WRNMASK           (0xfffe0000)
#define BPORT1_AB_CFG_WIDTH             32
#define BPORT1_AB_GC_WRMASK             0xff
#define BPORT1_AB_GC_WRNMASK            (0xffffff00)
#define BPORT1_AB_GC_WIDTH              32
#define BPORT1_AB_GS_WRMASK             0x6
#define BPORT1_AB_GS_WRNMASK            (0xfffffff9)
#define BPORT1_AB_GS_WIDTH              32
#define BPORT1_AB_CV_WRMASK             0xfff0fff
#define BPORT1_AB_CV_WRNMASK            (0xf000f000)
#define BPORT1_AB_CV_WIDTH              32
#define BPORT1_AB_OFS_WRMASK            0x1fff
#define BPORT1_AB_OFS_WRNMASK           (0xffffe000)
#define BPORT1_AB_OFS_WIDTH             32
#define BPORT1_AB_CAL_WRMASK            0xf
#define BPORT1_AB_CAL_WRNMASK           (0xfffffff0)
#define BPORT1_AB_CAL_WIDTH             32
#define BPORT1_AB_PCTL_WRMASK           0xffffff
#define BPORT1_AB_PCTL_WRNMASK          (0xff000000)
#define BPORT1_AB_PCTL_WIDTH            32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
