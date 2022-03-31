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
    } dr;
    union { 
        Uns32 value;
    } mr;
    union { 
        Uns32 value;
    } lr;
    union { 
        Uns32 value;
    } cr;
    union { 
        Uns32 value;
    } im;
    union { 
        Uns32 value;
    } is;
    union { 
        Uns32 value;
    } mis;
    union { 
        Uns32 value;
    } icr;
    union { 
        Uns32 value;
    } id[8];
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          irq;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(readCR);
PPM_REG_READ_CB(readDR);
PPM_NBYTE_READ_CB(readID);
PPM_REG_READ_CB(readMIS);
PPM_REG_WRITE_CB(writeCR);
PPM_REG_WRITE_CB(writeICR);
PPM_REG_WRITE_CB(writeIM);
PPM_REG_WRITE_CB(writeLR);
PPM_REG_WRITE_CB(writeMR);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_DR_WIDTH              32
#define BPORT1_AB_MR_WIDTH              32
#define BPORT1_AB_LR_WIDTH              32
#define BPORT1_AB_CR_WIDTH              32
#define BPORT1_AB_IM_WIDTH              32
#define BPORT1_AB_IS_WIDTH              32
#define BPORT1_AB_MIS_WIDTH             32
#define BPORT1_AB_ICR_WIDTH             32
#define BPORT1_AB_ID_WIDTH              32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
