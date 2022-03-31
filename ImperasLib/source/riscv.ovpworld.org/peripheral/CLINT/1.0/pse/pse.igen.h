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

typedef struct port0_msip_dataS { 
    union { 
        Uns32 value;
    } msip0;
} port0_msip_dataT, *port0_msip_dataTP;

typedef struct port0_mtime_dataS { 
    union { 
        Uns64 value;
    } mtimecmp0;
    union { 
        Uns64 value;
    } mtime;
} port0_mtime_dataT, *port0_mtime_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern port0_msip_dataT port0_msip_data;

extern port0_mtime_dataT port0_mtime_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *port0;
    ppmNetHandle          MSWInterrupt0;
    ppmNetHandle          MTimerInterrupt0;
    ppmNetHandle          reset;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NBYTE_READ_CB(defaultMemRead);

PPM_NBYTE_WRITE_CB(defaultMemWrite);

PPM_NBYTE_READ_CB(msipRead);
PPM_NBYTE_VIEW_CB(msipView);
PPM_NBYTE_WRITE_CB(msipWrite);
PPM_NBYTE_READ_CB(mtimeRead);
PPM_NBYTE_VIEW_CB(mtimeView);
PPM_NBYTE_WRITE_CB(mtimeWrite);
PPM_NBYTE_READ_CB(mtimecmpRead);
PPM_NBYTE_VIEW_CB(mtimecmpView);
PPM_NBYTE_WRITE_CB(mtimecmpWrite);
PPM_NET_CB(resetCB);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);
PPM_NET_PORT_FN(nextNetPortUser);


////////////////////////////////// Mask macros /////////////////////////////////

#define PORT0_MSIP_MSIP0_WRMASK         0x1
#define PORT0_MSIP_MSIP0_WRNMASK        (0xfffffffe)
#define PORT0_MSIP_MSIP0_WIDTH          32
#define PORT0_MTIME_MTIMECMP0_WIDTH     64
#define PORT0_MTIME_MTIME_WIDTH         64

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
