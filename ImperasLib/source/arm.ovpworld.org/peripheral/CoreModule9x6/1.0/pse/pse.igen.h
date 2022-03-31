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
    } id;
    union { 
        Uns32 value;
    } proc;
    union { 
        Uns32 value;
    } osc;
    union { 
        Uns32 value;
    } ctrl;
    union { 
        Uns32 value;
    } stat;
    union { 
        Uns32 value;
    } lock;
    union { 
        Uns32 value;
    } lmbuscnt;
    union { 
        Uns32 value;
    } auxosc;
    union { 
        Uns32 value;
    } sdram;
    union { 
        Uns32 value;
    } init;
    union { 
        Uns32 value;
    } refct;
    union { 
        Uns32 value;
    } flags;
    union { 
        Uns32 value;
    } flagsc;
    union { 
        Uns32 value;
    } nvflags;
    union { 
        Uns32 value;
    } nvflagss;
    union { 
        Uns32 value;
    } irqstat;
    union { 
        Uns32 value;
    } irqrstat;
    union { 
        Uns32 value;
    } irqenset;
    union { 
        Uns32 value;
    } irqenclr;
    union { 
        Uns32 value;
    } softintset;
    union { 
        Uns32 value;
    } softintclr;
    union { 
        Uns32 value;
    } fiqstat;
    union { 
        Uns32 value;
    } fiqrstat;
    union { 
        Uns32 value;
    } fiqenset;
    union { 
        Uns32 value;
    } fiqenclr;
    union { 
        Uns32 value;
    } volt0;
    union { 
        Uns32 value;
    } volt1;
    union { 
        Uns32 value;
    } volt2;
    union { 
        Uns32 value;
    } volt3;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(readID);
PPM_REG_READ_CB(readLock);
PPM_REG_READ_CB(readProc);
PPM_REG_READ_CB(readStat);
PPM_REG_WRITE_CB(writeCtrl);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_ID_WIDTH              32
#define BPORT1_AB_PROC_WIDTH            32
#define BPORT1_AB_OSC_WIDTH             32
#define BPORT1_AB_CTRL_WIDTH            32
#define BPORT1_AB_STAT_WIDTH            32
#define BPORT1_AB_LOCK_WIDTH            32
#define BPORT1_AB_LMBUSCNT_WIDTH        32
#define BPORT1_AB_AUXOSC_WIDTH          32
#define BPORT1_AB_SDRAM_WIDTH           32
#define BPORT1_AB_INIT_WIDTH            32
#define BPORT1_AB_REFCT_WIDTH           32
#define BPORT1_AB_FLAGS_WIDTH           32
#define BPORT1_AB_FLAGSC_WIDTH          32
#define BPORT1_AB_NVFLAGS_WIDTH         32
#define BPORT1_AB_NVFLAGSS_WIDTH        32
#define BPORT1_AB_IRQSTAT_WIDTH         32
#define BPORT1_AB_IRQRSTAT_WIDTH        32
#define BPORT1_AB_IRQENSET_WIDTH        32
#define BPORT1_AB_IRQENCLR_WIDTH        32
#define BPORT1_AB_SOFTINTSET_WIDTH      32
#define BPORT1_AB_SOFTINTCLR_WIDTH      32
#define BPORT1_AB_FIQSTAT_WIDTH         32
#define BPORT1_AB_FIQRSTAT_WIDTH        32
#define BPORT1_AB_FIQENSET_WIDTH        32
#define BPORT1_AB_FIQENCLR_WIDTH        32
#define BPORT1_AB_VOLT0_WIDTH           32
#define BPORT1_AB_VOLT1_WIDTH           32
#define BPORT1_AB_VOLT2_WIDTH           32
#define BPORT1_AB_VOLT3_WIDTH           32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
