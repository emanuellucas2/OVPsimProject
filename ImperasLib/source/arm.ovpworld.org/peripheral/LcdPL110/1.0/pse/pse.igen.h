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
    } timing0;
    union { 
        Uns32 value;
    } timing1;
    union { 
        Uns32 value;
    } timing2;
    union { 
        Uns32 value;
    } timing3;
    union { 
        Uns32 value;
    } upbase;
    union { 
        Uns32 value;
    } lpbase;
    union { 
        Uns32 value;
    } imsc;
    union { 
        Uns32 value;
        struct {
            Uns32 EN : 1;
            Uns32 __pad1 : 7;
            Uns32 BGR : 1;
            Uns32 BEBO : 1;
            Uns32 BEPO : 1;
            Uns32 PWR : 1;
        } bits;
    } control;
    union { 
        Uns32 value;
    } int_status;
    union { 
        Uns32 value;
    } int_mis;
    union { 
        Uns32 value;
    } int_clr;
    union { 
        Uns32 value;
    } upbase2;
    union { 
        Uns32 value;
    } lpbase2;
    union { 
        Uns32 value;
    } id[8];
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *memory;
    void                 *bport1;
    ppmNetHandle          irq;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(readControl);
PPM_NBYTE_READ_CB(readID);
PPM_REG_READ_CB(readIMSC);
PPM_REG_READ_CB(readLP);
PPM_REG_READ_CB(readMIS);
PPM_REG_READ_CB(readTiming);
PPM_REG_READ_CB(readUP);
PPM_REG_WRITE_CB(writeControl);
PPM_REG_WRITE_CB(writeICR);
PPM_REG_WRITE_CB(writeIMSC);
PPM_REG_WRITE_CB(writeLP);
PPM_REG_WRITE_CB(writeTiming);
PPM_REG_WRITE_CB(writeUP);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_TIMING0_WIDTH         32
#define BPORT1_AB_TIMING1_WIDTH         32
#define BPORT1_AB_TIMING2_WIDTH         32
#define BPORT1_AB_TIMING3_WIDTH         32
#define BPORT1_AB_UPBASE_WIDTH          32
#define BPORT1_AB_LPBASE_WIDTH          32
#define BPORT1_AB_IMSC_WIDTH            32
#define BPORT1_AB_CONTROL_WIDTH         32
#define BPORT1_AB_INT_STATUS_WIDTH      32
#define BPORT1_AB_INT_MIS_WIDTH         32
#define BPORT1_AB_INT_CLR_WIDTH         32
#define BPORT1_AB_UPBASE2_WIDTH         32
#define BPORT1_AB_LPBASE2_WIDTH         32
#define BPORT1_AB_ID_WIDTH              32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
