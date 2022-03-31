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
            Uns8 EWMEN : 1;
            Uns8 ASSIN : 1;
            Uns8 INEN : 1;
            Uns8 INTEN : 1;
        } bits;
    } CTRL;
    union { 
        Uns8 value;
        struct {
            Uns8 SERVICE : 8;
        } bits;
    } SERV;
    union { 
        Uns8 value;
        struct {
            Uns8 COMPAREL : 8;
        } bits;
    } CMPL;
    union { 
        Uns8 value;
        struct {
            Uns8 COMPAREH : 8;
        } bits;
    } CMPH;
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

#define BPORT1_AB_CTRL_WRMASK           0xf
#define BPORT1_AB_CTRL_WRNMASK          (0xf0)
#define BPORT1_AB_CTRL_WIDTH            8
#define BPORT1_AB_SERV_WRMASK           0xff
#define BPORT1_AB_SERV_WRNMASK          (0x0)
#define BPORT1_AB_SERV_WIDTH            8
#define BPORT1_AB_CMPL_WRMASK           0xff
#define BPORT1_AB_CMPL_WRNMASK          (0x0)
#define BPORT1_AB_CMPL_WIDTH            8
#define BPORT1_AB_CMPH_WRMASK           0xff
#define BPORT1_AB_CMPH_WRNMASK          (0x0)
#define BPORT1_AB_CMPH_WIDTH            8

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
