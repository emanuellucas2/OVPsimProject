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
    } ID;
    union { 
        Uns32 value;
    } SW;
    union { 
        Uns32 value;
    } LED;
    union { 
        Uns32 value;
    } CNT100HZ;
    union { 
        Uns32 value;
    } FLAGSSET;
    union { 
        Uns32 value;
    } FLAGSCLR;
    union { 
        Uns32 value;
    } NVFLAGSSET;
    union { 
        Uns32 value;
    } NVFLAGSCLR;
    union { 
        Uns32 value;
    } MCI;
    union { 
        Uns32 value;
    } FLASH;
    union { 
        Uns32 value;
    } CFGSW;
    union { 
        Uns32 value;
    } CNT24MHZ;
    union { 
        Uns32 value;
    } MISC;
    union { 
        Uns32 value;
    } DMA;
    union { 
        Uns32 value;
    } PROCID0;
    union { 
        Uns32 value;
    } PROCID1;
    union { 
        Uns32 value;
    } CFGDATA;
    union { 
        Uns32 value;
    } CFGCTRL;
    union { 
        Uns32 value;
    } CFGSTAT;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          cardin;
    ppmNetHandle          wprot;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(read100Hz);
PPM_REG_READ_CB(read24MHz);
PPM_REG_READ_CB(readCfgCtrl);
PPM_REG_READ_CB(readCfgStat);
PPM_REG_READ_CB(readFlags);
PPM_REG_READ_CB(readId);
PPM_REG_READ_CB(readMci);
PPM_REG_READ_CB(readMisc);
PPM_REG_READ_CB(readProcId0);
PPM_REG_READ_CB(readProcId1);
PPM_REG_READ_CB(readSw);
PPM_REG_WRITE_CB(writeFlags);
PPM_REG_WRITE_CB(writeLed);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_ID_WIDTH              32
#define BPORT1_AB_SW_WIDTH              32
#define BPORT1_AB_LED_WIDTH             32
#define BPORT1_AB_CNT100HZ_WIDTH        32
#define BPORT1_AB_FLAGSSET_WIDTH        32
#define BPORT1_AB_FLAGSCLR_WIDTH        32
#define BPORT1_AB_NVFLAGSSET_WIDTH      32
#define BPORT1_AB_NVFLAGSCLR_WIDTH      32
#define BPORT1_AB_MCI_WIDTH             32
#define BPORT1_AB_FLASH_WIDTH           32
#define BPORT1_AB_CFGSW_WIDTH           32
#define BPORT1_AB_CNT24MHZ_WIDTH        32
#define BPORT1_AB_MISC_WIDTH            32
#define BPORT1_AB_DMA_WIDTH             32
#define BPORT1_AB_PROCID0_WIDTH         32
#define BPORT1_AB_PROCID1_WIDTH         32
#define BPORT1_AB_CFGDATA_WIDTH         32
#define BPORT1_AB_CFGCTRL_WIDTH         32
#define BPORT1_AB_CFGSTAT_WIDTH         32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
