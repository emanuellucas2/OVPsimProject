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

typedef struct busPort_A_dataS { 
    union { 
        Uns8 value;
        struct {
            Uns8 enable : 1;
            Uns8 clear : 1;
            Uns8 set : 1;
            Uns8 invert : 1;
        } bits;
    } control;
    union { 
        Uns8 value;
    } address;
    union { 
        Uns8 value;
        struct {
            Uns8 busy : 1;
            Uns8 enable : 1;
        } bits;
    } status;
    union { 
        Uns8 value;
    } data;
} busPort_A_dataT, *busPort_A_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern busPort_A_dataT busPort_A_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *busPort;
    ppmNetHandle          interrupt;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_WRITE_CB(controlWrite);
PPM_REG_READ_CB(dataRead);
PPM_REG_WRITE_CB(dataWrite);
PPM_REG_WRITE_CB(statusWriteError);
PPM_NET_CB(reset_resetNet);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(userStart);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BUSPORT_A_CONTROL_WIDTH         8
#define BUSPORT_A_ADDRESS_WIDTH         8
#define BUSPORT_A_STATUS_WIDTH          8
#define BUSPORT_A_DATA_WIDTH            8

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
