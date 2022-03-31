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
            Uns32 FRZ : 1;
            Uns32 MDIS : 1;
        } bits;
    } MCR;
} bport1_ab_dataT, *bport1_ab_dataTP;

typedef struct bport1_ab2_dataS { 
    union { 
        Uns32 value;
        struct {
            Uns32 TSV : 32;
        } bits;
    } LDVAL;
    union { 
        Uns32 value;
        struct {
            Uns32 TVL : 32;
        } bits;
    } CVAL;
    union { 
        Uns32 value;
        struct {
            Uns32 TEN : 1;
            Uns32 TIE : 1;
        } bits;
    } TCTRL;
    union { 
        Uns32 value;
        struct {
            Uns32 TIF : 1;
        } bits;
    } TFLG;
} bport1_ab2_dataT, *bport1_ab2_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

extern bport1_ab2_dataT bport1_ab2_data[4];

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          Reset;
    ppmNetHandle          irq[4];
    ppmNetHandle          trg[4];
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NBYTE_READ_CB(readCVAL);
PPM_NBYTE_VIEW_CB(viewCVAL);
PPM_NBYTE_WRITE_CB(writeMCR);
PPM_NBYTE_WRITE_CB(writeTCTRL);
PPM_NBYTE_WRITE_CB(writeTFLG);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_MCR_WRMASK            0x3
#define BPORT1_AB_MCR_WRNMASK           (0xfffffffc)
#define BPORT1_AB_MCR_WIDTH             32
#define BPORT1_AB2_LDVAL_WIDTH          32
#define BPORT1_AB2_CVAL_WIDTH           32
#define BPORT1_AB2_TCTRL_WRMASK         0x3
#define BPORT1_AB2_TCTRL_WRNMASK        (0xfffffffc)
#define BPORT1_AB2_TCTRL_WIDTH          32
#define BPORT1_AB2_TFLG_WRMASK          0x1
#define BPORT1_AB2_TFLG_WRNMASK         (0xfffffffe)
#define BPORT1_AB2_TFLG_WIDTH           32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
