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
            Uns8 WAKEUP : 1;
            Uns8 LVD : 1;
            Uns8 LOC : 1;
            Uns8 __pad3 : 2;
            Uns8 WDOG : 1;
            Uns8 PIN : 1;
            Uns8 POR : 1;
        } bits;
    } SRS0;
    union { 
        Uns8 value;
        struct {
            Uns8 JTAG : 1;
            Uns8 LOCKUP : 1;
            Uns8 SW : 1;
            Uns8 MDM_AP : 1;
            Uns8 EZPT : 1;
            Uns8 SACKERR : 1;
            Uns8 __pad6 : 1;
            Uns8 TAMPER : 1;
        } bits;
    } SRS1;
    union { 
        Uns8 value;
        struct {
            Uns8 RSTFLTSRW : 2;
            Uns8 RSTFLTSS : 1;
        } bits;
    } RPFC;
    union { 
        Uns8 value;
        struct {
            Uns8 RSTFLTSEL : 5;
        } bits;
    } RPFW;
    union { 
        Uns8 value;
        struct {
            Uns8 __pad0 : 1;
            Uns8 EZP_MS : 1;
        } bits;
    } MR;
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

#define BPORT1_AB_SRS0_WIDTH            8
#define BPORT1_AB_SRS1_WIDTH            8
#define BPORT1_AB_RPFC_WRMASK           0x7
#define BPORT1_AB_RPFC_WRNMASK          (0xf8)
#define BPORT1_AB_RPFC_WIDTH            8
#define BPORT1_AB_RPFW_WRMASK           0x1f
#define BPORT1_AB_RPFW_WRNMASK          (0xe0)
#define BPORT1_AB_RPFW_WIDTH            8
#define BPORT1_AB_MR_WIDTH              8

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
