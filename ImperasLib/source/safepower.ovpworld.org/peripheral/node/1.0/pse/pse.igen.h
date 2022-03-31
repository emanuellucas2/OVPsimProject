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

typedef struct hostif_reg_dataS { 
    union { 
        Uns32 value;
    } control;
    union { 
        Uns32 value;
    } status;
} hostif_reg_dataT, *hostif_reg_dataTP;

typedef struct hostif_msgtx_dataS { 
    union { 
        Uns32 value;
    } id;
    union { 
        Uns32 value;
    } from;
    union { 
        Uns32 value;
    } nid;
    union { 
        Uns32 value;
    } msgLen;
} hostif_msgtx_dataT, *hostif_msgtx_dataTP;

typedef struct hostif_msgrx_dataS { 
    union { 
        Uns32 value;
    } id;
    union { 
        Uns32 value;
    } from;
    union { 
        Uns32 value;
    } nid;
    union { 
        Uns32 value;
    } msgLen;
} hostif_msgrx_dataT, *hostif_msgrx_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern hostif_reg_dataT hostif_reg_data;

extern hostif_msgtx_dataT hostif_msgtx_data;

extern hostif_msgrx_dataT hostif_msgrx_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *hostif;
    ppmPacketnetHandle    network;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_PACKETNET_CB(networkrx);
PPM_REG_WRITE_CB(writeControl);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


///////////////////////////////// Local memory /////////////////////////////////

// To access local memory hostif/msgtx/msgBuf : (for example)
// char value = ((char*)handles.hostif)[HOSTIF_MSGTX_MSGBUF_OFFSET + myAddress];

#define HOSTIF_MSGTX_MSGBUF_OFFSET      0x110
#define HOSTIF_MSGTX_MSGBUF_SIZE        0xf0

// To access local memory hostif/msgrx/msgBuf : (for example)
// char value = ((char*)handles.hostif)[HOSTIF_MSGRX_MSGBUF_OFFSET + myAddress];

#define HOSTIF_MSGRX_MSGBUF_OFFSET      0x210
#define HOSTIF_MSGRX_MSGBUF_SIZE        0xf0

////////////////////////////////// Mask macros /////////////////////////////////

#define HOSTIF_REG_CONTROL_WIDTH        32
#define HOSTIF_REG_STATUS_WIDTH         32
#define HOSTIF_MSGTX_ID_WIDTH           32
#define HOSTIF_MSGTX_FROM_WIDTH         32
#define HOSTIF_MSGTX_NID_WIDTH          32
#define HOSTIF_MSGTX_MSGLEN_WIDTH       32
#define HOSTIF_MSGRX_ID_WIDTH           32
#define HOSTIF_MSGRX_FROM_WIDTH         32
#define HOSTIF_MSGRX_NID_WIDTH          32
#define HOSTIF_MSGRX_MSGLEN_WIDTH       32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
