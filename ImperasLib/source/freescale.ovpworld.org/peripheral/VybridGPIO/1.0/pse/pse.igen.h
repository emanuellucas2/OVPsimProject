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
            Uns32 PDO : 32;
        } bits;
    } PDOR;
    union { 
        Uns32 value;
        struct {
            Uns32 PTSO : 32;
        } bits;
    } PSOR;
    union { 
        Uns32 value;
        struct {
            Uns32 PTCO : 32;
        } bits;
    } PCOR;
    union { 
        Uns32 value;
        struct {
            Uns32 PTTO : 32;
        } bits;
    } PTOR;
    union { 
        Uns32 value;
        struct {
            Uns32 PDI : 32;
        } bits;
    } PDIR;
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

PPM_REG_WRITE_CB(writePCOR);
PPM_REG_WRITE_CB(writePSOR);
PPM_REG_WRITE_CB(writePTOR);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_PDOR_WRMASK           0xffffffff
#define BPORT1_AB_PDOR_WRNMASK          (0x0)
#define BPORT1_AB_PDOR_WIDTH            32
#define BPORT1_AB_PSOR_WRMASK           0xffffffff
#define BPORT1_AB_PSOR_WRNMASK          (0x0)
#define BPORT1_AB_PSOR_WIDTH            32
#define BPORT1_AB_PCOR_WRMASK           0xffffffff
#define BPORT1_AB_PCOR_WRNMASK          (0x0)
#define BPORT1_AB_PCOR_WIDTH            32
#define BPORT1_AB_PTOR_WRMASK           0xffffffff
#define BPORT1_AB_PTOR_WRNMASK          (0x0)
#define BPORT1_AB_PTOR_WIDTH            32
#define BPORT1_AB_PDIR_WIDTH            32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
