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
            Uns32 STPE : 1;
            Uns32 STM : 1;
            Uns32 __pad2 : 2;
            Uns32 ESOR : 1;
            Uns32 ERIE : 1;
            Uns32 TSIIE : 1;
            Uns32 TSIEN : 1;
            Uns32 SWTS : 1;
            Uns32 SCNIP : 1;
            Uns32 __pad10 : 2;
            Uns32 OVRF : 1;
            Uns32 EXTERF : 1;
            Uns32 OUTRGF : 1;
            Uns32 EOSF : 1;
            Uns32 PS : 3;
            Uns32 NSCN : 5;
            Uns32 LPSCNITV : 4;
            Uns32 LPCLKS : 1;
        } bits;
    } GENCS;
    union { 
        Uns32 value;
        struct {
            Uns32 AMPSC : 3;
            Uns32 AMCLKS : 2;
            Uns32 __pad5 : 3;
            Uns32 SMOD : 8;
            Uns32 EXTCHRG : 4;
            Uns32 __pad20 : 4;
            Uns32 REFCHRG : 4;
        } bits;
    } SCANC;
    union { 
        Uns32 value;
        struct {
            Uns32 PEN0 : 1;
            Uns32 PEN1 : 1;
            Uns32 PEN2 : 1;
            Uns32 PEN3 : 1;
            Uns32 PEN4 : 1;
            Uns32 PEN5 : 1;
            Uns32 PEN6 : 1;
            Uns32 PEN7 : 1;
            Uns32 PEN8 : 1;
            Uns32 PEN9 : 1;
            Uns32 PEN10 : 1;
            Uns32 PEN11 : 1;
            Uns32 PEN12 : 1;
            Uns32 PEN13 : 1;
            Uns32 PEN14 : 1;
            Uns32 PEN15 : 1;
            Uns32 LPSP : 4;
        } bits;
    } PEN;
    union { 
        Uns32 value;
        struct {
            Uns32 WUCNT : 16;
        } bits;
    } WUCNTR;
    union { 
        Uns32 value;
        struct {
            Uns32 CTN1 : 16;
            Uns32 CTN : 16;
        } bits;
    } CNTR1;
    union { 
        Uns32 value;
        struct {
            Uns32 CTN1 : 16;
            Uns32 CTN : 16;
        } bits;
    } CNTR3;
    union { 
        Uns32 value;
        struct {
            Uns32 CTN1 : 16;
            Uns32 CTN : 16;
        } bits;
    } CNTR5;
    union { 
        Uns32 value;
        struct {
            Uns32 CTN1 : 16;
            Uns32 CTN : 16;
        } bits;
    } CNTR7;
    union { 
        Uns32 value;
        struct {
            Uns32 CTN1 : 16;
            Uns32 CTN : 16;
        } bits;
    } CNTR9;
    union { 
        Uns32 value;
        struct {
            Uns32 CTN1 : 16;
            Uns32 CTN : 16;
        } bits;
    } CNTR11;
    union { 
        Uns32 value;
        struct {
            Uns32 CTN1 : 16;
            Uns32 CTN : 16;
        } bits;
    } CNTR13;
    union { 
        Uns32 value;
        struct {
            Uns32 CTN1 : 16;
            Uns32 CTN : 16;
        } bits;
    } CNTR15;
    union { 
        Uns32 value;
        struct {
            Uns32 HTHH : 16;
            Uns32 LTHH : 16;
        } bits;
    } THRESHOLD;
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

#define BPORT1_AB_GENCS_WRMASK          0x1ffff1f3
#define BPORT1_AB_GENCS_WRNMASK         (0xe0000e0c)
#define BPORT1_AB_GENCS_WIDTH           32
#define BPORT1_AB_SCANC_WRMASK          0xf0fff1f
#define BPORT1_AB_SCANC_WRNMASK         (0xf0f000e0)
#define BPORT1_AB_SCANC_WIDTH           32
#define BPORT1_AB_PEN_WRMASK            0xfffff
#define BPORT1_AB_PEN_WRNMASK           (0xfff00000)
#define BPORT1_AB_PEN_WIDTH             32
#define BPORT1_AB_WUCNTR_WIDTH          32
#define BPORT1_AB_CNTR1_WIDTH           32
#define BPORT1_AB_CNTR3_WIDTH           32
#define BPORT1_AB_CNTR5_WIDTH           32
#define BPORT1_AB_CNTR7_WIDTH           32
#define BPORT1_AB_CNTR9_WIDTH           32
#define BPORT1_AB_CNTR11_WIDTH          32
#define BPORT1_AB_CNTR13_WIDTH          32
#define BPORT1_AB_CNTR15_WIDTH          32
#define BPORT1_AB_THRESHOLD_WRMASK      0xfffffff
#define BPORT1_AB_THRESHOLD_WRNMASK     (0xf0000000)
#define BPORT1_AB_THRESHOLD_WIDTH       32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
