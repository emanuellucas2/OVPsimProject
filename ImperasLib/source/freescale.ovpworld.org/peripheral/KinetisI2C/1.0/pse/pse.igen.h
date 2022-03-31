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
        Uns8 value;
        struct {
            Uns8 __pad0 : 1;
            Uns8 AD : 7;
        } bits;
    } A1;
    union { 
        Uns8 value;
        struct {
            Uns8 ICR : 6;
            Uns8 MULT : 2;
        } bits;
    } F;
    union { 
        Uns8 value;
        struct {
            Uns8 DMAEN : 1;
            Uns8 WUEN : 1;
            Uns8 RSTA : 1;
            Uns8 TXAK : 1;
            Uns8 TX : 1;
            Uns8 MST : 1;
            Uns8 IICIE : 1;
            Uns8 IICEN : 1;
        } bits;
    } C1;
    union { 
        Uns8 value;
        struct {
            Uns8 RXAK : 1;
            Uns8 IICIF : 1;
            Uns8 SRW : 1;
            Uns8 RAM : 1;
            Uns8 ARBL : 1;
            Uns8 BUSY : 1;
            Uns8 IAAS : 1;
            Uns8 TCF : 1;
        } bits;
    } S;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 8;
        } bits;
    } D;
    union { 
        Uns8 value;
        struct {
            Uns8 AD : 3;
            Uns8 RMEN : 1;
            Uns8 SBRC : 1;
            Uns8 HDRS : 1;
            Uns8 ADEXT : 1;
            Uns8 GCAEN : 1;
        } bits;
    } C2;
    union { 
        Uns8 value;
        struct {
            Uns8 FLT : 5;
        } bits;
    } FLT;
    union { 
        Uns8 value;
        struct {
            Uns8 __pad0 : 1;
            Uns8 RAD : 7;
        } bits;
    } RA;
    union { 
        Uns8 value;
        struct {
            Uns8 SHTF2IE : 1;
            Uns8 SHTF2 : 1;
            Uns8 SHTF1 : 1;
            Uns8 SLTF : 1;
            Uns8 TCKSEL : 1;
            Uns8 SIICAEN : 1;
            Uns8 ALERTEN : 1;
            Uns8 FACK : 1;
        } bits;
    } SMB;
    union { 
        Uns8 value;
        struct {
            Uns8 __pad0 : 1;
            Uns8 SAD : 7;
        } bits;
    } A2;
    union { 
        Uns8 value;
        struct {
            Uns8 SSLT : 8;
        } bits;
    } SLTH;
    union { 
        Uns8 value;
        struct {
            Uns8 SSLT : 8;
        } bits;
    } SLTL;
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

#define BPORT1_AB_A1_WRMASK             0xfe
#define BPORT1_AB_A1_WRNMASK            (0x1)
#define BPORT1_AB_A1_WIDTH              8
#define BPORT1_AB_F_WRMASK              0xff
#define BPORT1_AB_F_WRNMASK             (0x0)
#define BPORT1_AB_F_WIDTH               8
#define BPORT1_AB_C1_WRMASK             0xff
#define BPORT1_AB_C1_WRNMASK            (0x0)
#define BPORT1_AB_C1_WIDTH              8
#define BPORT1_AB_S_WRMASK              0x56
#define BPORT1_AB_S_WRNMASK             (0xa9)
#define BPORT1_AB_S_WIDTH               8
#define BPORT1_AB_D_WRMASK              0xff
#define BPORT1_AB_D_WRNMASK             (0x0)
#define BPORT1_AB_D_WIDTH               8
#define BPORT1_AB_C2_WRMASK             0xff
#define BPORT1_AB_C2_WRNMASK            (0x0)
#define BPORT1_AB_C2_WIDTH              8
#define BPORT1_AB_FLT_WRMASK            0x1f
#define BPORT1_AB_FLT_WRNMASK           (0xe0)
#define BPORT1_AB_FLT_WIDTH             8
#define BPORT1_AB_RA_WRMASK             0xfe
#define BPORT1_AB_RA_WRNMASK            (0x1)
#define BPORT1_AB_RA_WIDTH              8
#define BPORT1_AB_SMB_WRMASK            0xfb
#define BPORT1_AB_SMB_WRNMASK           (0x4)
#define BPORT1_AB_SMB_WIDTH             8
#define BPORT1_AB_A2_WRMASK             0xfe
#define BPORT1_AB_A2_WRNMASK            (0x1)
#define BPORT1_AB_A2_WIDTH              8
#define BPORT1_AB_SLTH_WRMASK           0xff
#define BPORT1_AB_SLTH_WRNMASK          (0x0)
#define BPORT1_AB_SLTH_WIDTH            8
#define BPORT1_AB_SLTL_WRMASK           0xff
#define BPORT1_AB_SLTL_WRNMASK          (0x0)
#define BPORT1_AB_SLTL_WIDTH            8

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
