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
            Uns32 VLD : 1;
            Uns32 __pad1 : 7;
            Uns32 NRGD : 4;
            Uns32 NSP : 4;
            Uns32 HRL : 4;
            Uns32 __pad20 : 4;
            Uns32 SPERR : 8;
        } bits;
    } CESR;
    union { 
        Uns32 value;
        struct {
            Uns32 EADDR : 32;
        } bits;
    } EAR0;
    union { 
        Uns32 value;
        struct {
            Uns32 ERW : 1;
            Uns32 EATTR : 3;
            Uns32 EMN : 4;
            Uns32 EPID : 8;
            Uns32 EACD : 16;
        } bits;
    } EDR0;
    union { 
        Uns32 value;
        struct {
            Uns32 EADDR : 32;
        } bits;
    } EAR1;
    union { 
        Uns32 value;
        struct {
            Uns32 ERW : 1;
            Uns32 EATTR : 3;
            Uns32 EMN : 4;
            Uns32 EPID : 8;
            Uns32 EACD : 16;
        } bits;
    } EDR1;
    union { 
        Uns32 value;
        struct {
            Uns32 EADDR : 32;
        } bits;
    } EAR2;
    union { 
        Uns32 value;
        struct {
            Uns32 ERW : 1;
            Uns32 EATTR : 3;
            Uns32 EMN : 4;
            Uns32 EPID : 8;
            Uns32 EACD : 16;
        } bits;
    } EDR2;
    union { 
        Uns32 value;
        struct {
            Uns32 EADDR : 32;
        } bits;
    } EAR3;
    union { 
        Uns32 value;
        struct {
            Uns32 ERW : 1;
            Uns32 EATTR : 3;
            Uns32 EMN : 4;
            Uns32 EPID : 8;
            Uns32 EACD : 16;
        } bits;
    } EDR3;
    union { 
        Uns32 value;
        struct {
            Uns32 EADDR : 32;
        } bits;
    } EAR4;
    union { 
        Uns32 value;
        struct {
            Uns32 ERW : 1;
            Uns32 EATTR : 3;
            Uns32 EMN : 4;
            Uns32 EPID : 8;
            Uns32 EACD : 16;
        } bits;
    } EDR4;
} bport1_ab_dataT, *bport1_ab_dataTP;

typedef struct bport1_RGD_dataS { 
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 5;
            Uns32 SRTADDR : 27;
        } bits;
    } WORD0;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 5;
            Uns32 ENDADDR : 27;
        } bits;
    } WORD1;
    union { 
        Uns32 value;
        struct {
            Uns32 M0UM : 3;
            Uns32 M0SM : 2;
            Uns32 M0PE : 1;
            Uns32 M1UM : 3;
            Uns32 M1SM : 2;
            Uns32 M1PE : 1;
            Uns32 M2UM : 3;
            Uns32 M2SM : 2;
            Uns32 M2PE : 1;
            Uns32 M3UM : 3;
            Uns32 M3SM : 2;
            Uns32 M3PE : 1;
            Uns32 M4WE : 1;
            Uns32 M4RE : 1;
            Uns32 M5WE : 1;
            Uns32 M5RE : 1;
            Uns32 M6WE : 1;
            Uns32 M6RE : 1;
            Uns32 M7WE : 1;
            Uns32 M7RE : 1;
        } bits;
    } WORD2;
    union { 
        Uns32 value;
        struct {
            Uns32 VLD : 1;
            Uns32 __pad1 : 15;
            Uns32 PIDMASK : 8;
            Uns32 PID : 8;
        } bits;
    } WORD3;
} bport1_RGD_dataT, *bport1_RGD_dataTP;

typedef struct bport1_AAC_dataS { 
    union { 
        Uns32 value;
        struct {
            Uns32 M0UM : 3;
            Uns32 M0SM : 2;
            Uns32 M0PE : 1;
            Uns32 M1UM : 3;
            Uns32 M1SM : 2;
            Uns32 M1PE : 1;
            Uns32 M2UM : 3;
            Uns32 M2SM : 2;
            Uns32 M2PE : 1;
            Uns32 M3UM : 3;
            Uns32 M3SM : 2;
            Uns32 M3PE : 1;
            Uns32 M4WE : 1;
            Uns32 M4RE : 1;
            Uns32 M5WE : 1;
            Uns32 M5RE : 1;
            Uns32 M6WE : 1;
            Uns32 M6RE : 1;
            Uns32 M7WE : 1;
            Uns32 M7RE : 1;
        } bits;
    } RGDAAC[16];
} bport1_AAC_dataT, *bport1_AAC_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

extern bport1_RGD_dataT bport1_RGD_data[16];

extern bport1_AAC_dataT bport1_AAC_data;

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

#define BPORT1_AB_CESR_WRMASK           0xff000001
#define BPORT1_AB_CESR_WRNMASK          (0xfffffe)
#define BPORT1_AB_CESR_WIDTH            32
#define BPORT1_AB_EAR0_WIDTH            32
#define BPORT1_AB_EDR0_WIDTH            32
#define BPORT1_AB_EAR1_WIDTH            32
#define BPORT1_AB_EDR1_WIDTH            32
#define BPORT1_AB_EAR2_WIDTH            32
#define BPORT1_AB_EDR2_WIDTH            32
#define BPORT1_AB_EAR3_WIDTH            32
#define BPORT1_AB_EDR3_WIDTH            32
#define BPORT1_AB_EAR4_WIDTH            32
#define BPORT1_AB_EDR4_WIDTH            32
#define BPORT1_RGD_WORD0_WRMASK         0xffffffe0
#define BPORT1_RGD_WORD0_WRNMASK        (0x1f)
#define BPORT1_RGD_WORD0_WIDTH          32
#define BPORT1_RGD_WORD1_WRMASK         0xffffffe0
#define BPORT1_RGD_WORD1_WRNMASK        (0x1f)
#define BPORT1_RGD_WORD1_WIDTH          32
#define BPORT1_RGD_WORD2_WIDTH          32
#define BPORT1_RGD_WORD3_WRMASK         0xffff0001
#define BPORT1_RGD_WORD3_WRNMASK        (0xfffe)
#define BPORT1_RGD_WORD3_WIDTH          32
#define BPORT1_AAC_RGDAAC_WIDTH         32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
