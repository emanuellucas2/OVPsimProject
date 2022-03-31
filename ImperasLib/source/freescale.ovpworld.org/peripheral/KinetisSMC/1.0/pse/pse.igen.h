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
            Uns8 AVLLS : 1;
            Uns8 __pad2 : 1;
            Uns8 ALLS : 1;
            Uns8 __pad4 : 1;
            Uns8 AVLP : 1;
        } bits;
    } PMPROT;
    union { 
        Uns8 value;
        struct {
            Uns8 STOPM : 3;
            Uns8 STOPA : 1;
            Uns8 __pad4 : 1;
            Uns8 RUNM : 2;
            Uns8 LPWUI : 1;
        } bits;
    } PMCTRL;
    union { 
        Uns8 value;
        struct {
            Uns8 VLLSM : 3;
        } bits;
    } VLLSCTRL;
    union { 
        Uns8 value;
        struct {
            Uns8 PMSTAT : 7;
        } bits;
    } PMSTAT;
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

#define BPORT1_AB_PMPROT_WRMASK         0x2a
#define BPORT1_AB_PMPROT_WRNMASK        (0xd5)
#define BPORT1_AB_PMPROT_WIDTH          8
#define BPORT1_AB_PMCTRL_WRMASK         0xe7
#define BPORT1_AB_PMCTRL_WRNMASK        (0x18)
#define BPORT1_AB_PMCTRL_WIDTH          8
#define BPORT1_AB_VLLSCTRL_WRMASK       0x7
#define BPORT1_AB_VLLSCTRL_WRNMASK      (0xf8)
#define BPORT1_AB_VLLSCTRL_WIDTH        8
#define BPORT1_AB_PMSTAT_WIDTH          8

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
