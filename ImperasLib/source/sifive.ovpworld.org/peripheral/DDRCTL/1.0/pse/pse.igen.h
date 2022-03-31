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

typedef struct CONTROL_REGS_dataS { 
    union { 
        Uns32 value;
    } reg33;
} CONTROL_REGS_dataT, *CONTROL_REGS_dataTP;

typedef struct BLOCKER_REGS_dataS { 
} BLOCKER_REGS_dataT, *BLOCKER_REGS_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern CONTROL_REGS_dataT CONTROL_REGS_data;

extern BLOCKER_REGS_dataT BLOCKER_REGS_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *CONTROL;
    void                 *BLOCKER;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NBYTE_WRITE_CB(writeMaskedControlReg);
PPM_NBYTE_READ_CB(readBlockerMem);
PPM_NBYTE_READ_CB(readControlMem);
PPM_NBYTE_WRITE_CB(writeBlockerMem);
PPM_NBYTE_WRITE_CB(writeControlMem);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


///////////////////////////////// Local memory /////////////////////////////////

// To access local memory CONTROL/REGS/ctrlRegs : (for example)
// char value = ((char*)handles.CONTROL)[CONTROL_REGS_CTRLREGS_OFFSET + myAddress];

#define CONTROL_REGS_CTRLREGS_OFFSET    0x0
#define CONTROL_REGS_CTRLREGS_SIZE      0x4000

// To access local memory BLOCKER/REGS/blkRegs : (for example)
// char value = ((char*)handles.BLOCKER)[BLOCKER_REGS_BLKREGS_OFFSET + myAddress];

#define BLOCKER_REGS_BLKREGS_OFFSET     0x0
#define BLOCKER_REGS_BLKREGS_SIZE       0x8

////////////////////////////////// Mask macros /////////////////////////////////

#define CONTROL_REGS_REG33_WIDTH        32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
