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

typedef struct bport1_REG_dataS { 
    union { 
        Uns32 value;
    } MSEL;
} bport1_REG_dataT, *bport1_REG_dataTP;

typedef struct bport1_CODE_dataS { 
} bport1_CODE_dataT, *bport1_CODE_dataTP;

typedef struct bport1_TABLE_dataS { 
} bport1_TABLE_dataT, *bport1_TABLE_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_REG_dataT bport1_REG_data;

extern bport1_CODE_dataT bport1_CODE_data;

extern bport1_TABLE_dataT bport1_TABLE_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


///////////////////////////////// Local memory /////////////////////////////////

// To access local memory bport1/CODE/RESET : (for example)
// char value = ((char*)handles.bport1)[BPORT1_CODE_RESET_OFFSET + myAddress];

#define BPORT1_CODE_RESET_OFFSET        0x4
#define BPORT1_CODE_RESET_SIZE          0x20

// To access local memory bport1/TABLE/JUMPADDR : (for example)
// char value = ((char*)handles.bport1)[BPORT1_TABLE_JUMPADDR_OFFSET + myAddress];

#define BPORT1_TABLE_JUMPADDR_OFFSET    0x100
#define BPORT1_TABLE_JUMPADDR_SIZE      0x80

////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_REG_MSEL_WRMASK          0xf
#define BPORT1_REG_MSEL_WRNMASK         (0xfffffff0)
#define BPORT1_REG_MSEL_WIDTH           32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
