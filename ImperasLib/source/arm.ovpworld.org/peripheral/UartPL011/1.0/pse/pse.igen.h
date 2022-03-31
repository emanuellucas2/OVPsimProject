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
        struct {
            Uns32 __pad0 : 3;
            Uns32 OE : 1;
        } bits;
    } ecr;
    union { 
        Uns32 value;
    } ilpr;
    union { 
        Uns32 value;
    } ibrd;
    union { 
        Uns32 value;
    } vbrd;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 4;
            Uns32 FEN : 1;
        } bits;
    } lcr;
    union { 
        Uns32 value;
    } cr;
    union { 
        Uns32 value;
    } ifl;
    union { 
        Uns32 value;
    } int_enabled;
    union { 
        Uns32 value;
    } mis;
    union { 
        Uns32 value;
    } icr;
    union { 
        Uns32 value;
    } dmacr;
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
    ppmNetHandle          DirectWrite;
    ppmNetHandle          DirectRead;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(directReadCB);
PPM_REG_READ_CB(readDR);
PPM_REG_READ_CB(readECR);
PPM_NBYTE_READ_CB(readID);
PPM_REG_READ_CB(readMIS);
PPM_REG_WRITE_CB(writeDMA);
PPM_REG_WRITE_CB(writeDR);
PPM_REG_WRITE_CB(writeECR);
PPM_REG_WRITE_CB(writeICR);
PPM_REG_WRITE_CB(writeIFL);
PPM_REG_WRITE_CB(writeIMSC);
PPM_REG_WRITE_CB(writeLCR);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(closeDown);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


///////////////////////////////// Local memory /////////////////////////////////

// To access local memory bport1/ab/flags : (for example)
// char value = ((char*)handles.bport1)[BPORT1_AB_FLAGS_OFFSET + myAddress];

#define BPORT1_AB_FLAGS_OFFSET          0x18
#define BPORT1_AB_FLAGS_SIZE            0x4

// To access local memory bport1/ab/int_level : (for example)
// char value = ((char*)handles.bport1)[BPORT1_AB_INT_LEVEL_OFFSET + myAddress];

#define BPORT1_AB_INT_LEVEL_OFFSET      0x3c
#define BPORT1_AB_INT_LEVEL_SIZE        0x4

////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_DR_WIDTH              32
#define BPORT1_AB_ECR_WIDTH             32
#define BPORT1_AB_ILPR_WIDTH            32
#define BPORT1_AB_IBRD_WIDTH            32
#define BPORT1_AB_VBRD_WIDTH            32
#define BPORT1_AB_LCR_WIDTH             32
#define BPORT1_AB_CR_WIDTH              32
#define BPORT1_AB_IFL_WIDTH             32
#define BPORT1_AB_INT_ENABLED_WIDTH     32
#define BPORT1_AB_MIS_WIDTH             32
#define BPORT1_AB_ICR_WIDTH             32
#define BPORT1_AB_DMACR_WIDTH           32
#define BPORT1_AB_ID_WIDTH              32

//////////////////////////// Parameters of enum type ///////////////////////////

typedef enum variantE {
    VARIANT_ARM = 0,
    VARIANT_LUMINARY = 1,
} variantT;

#endif

#endif
