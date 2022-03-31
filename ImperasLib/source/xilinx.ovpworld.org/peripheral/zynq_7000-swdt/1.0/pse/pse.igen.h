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
            Uns32 WDEN : 1;
            Uns32 RSTEN : 1;
            Uns32 IRQEN : 1;
            Uns32 __pad3 : 4;
            Uns32 IRQLN : 2;
            Uns32 __pad9 : 3;
            Uns32 ZKEY : 12;
        } bits;
    } MODE;
    union { 
        Uns32 value;
        struct {
            Uns32 CLKSEL : 2;
            Uns32 CRV : 12;
            Uns32 CKEY : 12;
        } bits;
    } CONTROL;
    union { 
        Uns32 value;
        struct {
            Uns32 RSTKEY : 16;
        } bits;
    } RESTART;
    union { 
        Uns32 value;
        struct {
            Uns32 WDZ : 1;
        } bits;
    } STATUS;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          wdo;
    ppmNetHandle          rst;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(rdControl);
PPM_REG_READ_CB(rdStatus);
PPM_REG_WRITE_CB(wrControl);
PPM_REG_WRITE_CB(wrMode);
PPM_REG_WRITE_CB(wrReStart);
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

#define BPORT1_AB_MODE_WRMASK           0x1f7
#define BPORT1_AB_MODE_WRNMASK          (0xfffffe08)
#define BPORT1_AB_MODE_WIDTH            32
#define BPORT1_AB_CONTROL_WRMASK        0x1ffffff
#define BPORT1_AB_CONTROL_WRNMASK       (0xfe000000)
#define BPORT1_AB_CONTROL_WIDTH         32
#define BPORT1_AB_RESTART_WRMASK        0xffff
#define BPORT1_AB_RESTART_WRNMASK       (0xffff0000)
#define BPORT1_AB_RESTART_WIDTH         32
#define BPORT1_AB_STATUS_WIDTH          32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
