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
    } Config;
    union { 
        Uns32 value;
    } Intr_status;
    union { 
        Uns32 value;
    } Intrpt_en;
    union { 
        Uns32 value;
    } Intrpt_dis;
    union { 
        Uns32 value;
    } Intrpt_mask;
    union { 
        Uns32 value;
    } En;
    union { 
        Uns32 value;
    } Delay;
    union { 
        Uns32 value;
    } Tx_data;
    union { 
        Uns32 value;
    } Rx_data;
    union { 
        Uns32 value;
    } Slave_Idle_count;
    union { 
        Uns32 value;
    } TX_thres;
    union { 
        Uns32 value;
    } RX_thres;
    union { 
        Uns32 value;
    } Mod_id;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    ppmAddressSpaceHandle SPI;
    void                 *bport1;
    ppmNetHandle          intOut;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(rdData);
PPM_REG_WRITE_CB(wrData);
PPM_READ_CB(regNoDefinitionRead);
PPM_WRITE_CB(regNoDefinitionWrite);
PPM_NET_CB(reset_resetNet);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


///////////////////////////////// Local memory /////////////////////////////////

// To access local memory bport1/ab/buffer : (for example)
// char value = ((char*)handles.bport1)[BPORT1_AB_BUFFER_OFFSET + myAddress];

#define BPORT1_AB_BUFFER_OFFSET         0x0
#define BPORT1_AB_BUFFER_SIZE           0x1000

////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_CONFIG_WIDTH          32
#define BPORT1_AB_INTR_STATUS_WIDTH     32
#define BPORT1_AB_INTRPT_EN_WIDTH       32
#define BPORT1_AB_INTRPT_DIS_WIDTH      32
#define BPORT1_AB_INTRPT_MASK_WIDTH     32
#define BPORT1_AB_EN_WIDTH              32
#define BPORT1_AB_DELAY_WIDTH           32
#define BPORT1_AB_TX_DATA_WIDTH         32
#define BPORT1_AB_RX_DATA_WIDTH         32
#define BPORT1_AB_SLAVE_IDLE_COUNT_WIDTH  32
#define BPORT1_AB_TX_THRES_WIDTH        32
#define BPORT1_AB_RX_THRES_WIDTH        32
#define BPORT1_AB_MOD_ID_WIDTH          32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
