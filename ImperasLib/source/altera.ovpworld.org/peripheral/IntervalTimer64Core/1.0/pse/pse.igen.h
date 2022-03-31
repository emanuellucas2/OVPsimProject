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

typedef struct sp1_reg0_dataS { 
    union { 
        Uns16 value;
        struct {
            Uns16 TO : 1;
            Uns16 RUN : 1;
        } bits;
    } status;
    union { 
        Uns16 value;
        struct {
            Uns16 ITO : 1;
            Uns16 CONT : 1;
            Uns16 START : 1;
            Uns16 STOP : 1;
        } bits;
    } control;
    union { 
        Uns16 value;
    } period_0;
    union { 
        Uns16 value;
    } period_1;
    union { 
        Uns16 value;
    } period_2;
    union { 
        Uns16 value;
    } period_3;
    union { 
        Uns16 value;
    } snap_0;
    union { 
        Uns16 value;
    } snap_1;
    union { 
        Uns16 value;
    } snap_2;
    union { 
        Uns16 value;
    } snap_3;
} sp1_reg0_dataT, *sp1_reg0_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern sp1_reg0_dataT sp1_reg0_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *sp1;
    ppmNetHandle          irq;
    ppmNetHandle          resetrequest;
    ppmNetHandle          timeout_pulse;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(read_control);
PPM_REG_READ_CB(read_period);
PPM_REG_READ_CB(read_snap);
PPM_REG_READ_CB(read_status);
PPM_REG_WRITE_CB(write_control);
PPM_REG_WRITE_CB(write_period);
PPM_REG_WRITE_CB(write_snap);
PPM_REG_WRITE_CB(write_status);
PPM_NET_CB(reset_IRESET);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define SP1_REG0_STATUS_WIDTH           16
#define SP1_REG0_CONTROL_WIDTH          16
#define SP1_REG0_PERIOD_0_WIDTH         16
#define SP1_REG0_PERIOD_1_WIDTH         16
#define SP1_REG0_PERIOD_2_WIDTH         16
#define SP1_REG0_PERIOD_3_WIDTH         16
#define SP1_REG0_SNAP_0_WIDTH           16
#define SP1_REG0_SNAP_1_WIDTH           16
#define SP1_REG0_SNAP_2_WIDTH           16
#define SP1_REG0_SNAP_3_WIDTH           16

//////////////////////////// Parameters of enum type ///////////////////////////

typedef enum timeoutConfigE {
    TIMEOUTCONFIG_SIMPLE = 0,
    TIMEOUTCONFIG_FULL = 1,
    TIMEOUTCONFIG_WATCHDOG = 2,
} timeoutConfigT;

#endif

#endif
