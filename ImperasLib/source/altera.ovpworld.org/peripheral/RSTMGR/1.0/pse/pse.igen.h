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

typedef struct bport1_REGS_dataS { 
    union { 
        Uns32 value;
    } stat;
    union { 
        Uns32 value;
    } ctrl;
    union { 
        Uns32 value;
    } counts;
    union { 
        Uns32 value;
        struct {
            Uns32 cpu0 : 1;
            Uns32 cpu1 : 1;
        } bits;
    } mpumodrst;
    union { 
        Uns32 value;
    } permodrst;
    union { 
        Uns32 value;
    } per2modrst;
    union { 
        Uns32 value;
    } brgmodrst;
    union { 
        Uns32 value;
    } miscmodrst;
} bport1_REGS_dataT, *bport1_REGS_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_REGS_dataT bport1_REGS_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          cpu0Reset;
    ppmNetHandle          cpu1Reset;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_WRITE_CB(Writempumodrst);
PPM_NET_CB(reset_resetNet);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_REGS_STAT_WIDTH          32
#define BPORT1_REGS_CTRL_WIDTH          32
#define BPORT1_REGS_COUNTS_WIDTH        32
#define BPORT1_REGS_MPUMODRST_WIDTH     32
#define BPORT1_REGS_PERMODRST_WIDTH     32
#define BPORT1_REGS_PER2MODRST_WIDTH    32
#define BPORT1_REGS_BRGMODRST_WIDTH     32
#define BPORT1_REGS_MISCMODRST_WIDTH    32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
