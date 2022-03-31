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
    } status;
    union { 
        Uns32 value;
    } command;
    union { 
        Uns32 value;
    } intclr;
    union { 
        Uns32 value;
    } intStatus;
    union { 
        Uns32 value;
    } nodeid;
    union { 
        Uns32 value;
    } heartbeat;
} hostif_reg_dataT, *hostif_reg_dataTP;

typedef struct hostif_outbox_dataS { 
} hostif_outbox_dataT, *hostif_outbox_dataTP;

typedef struct hostif_inbox_dataS { 
} hostif_inbox_dataT, *hostif_inbox_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern hostif_reg_dataT hostif_reg_data;

extern hostif_outbox_dataT hostif_outbox_data;

extern hostif_inbox_dataT hostif_inbox_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *hostif;
    ppmNetHandle          syncOut;
    ppmNetHandle          syncIn;
    ppmPacketnetHandle    network;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_PACKETNET_CB(networkReceiveMsg);
PPM_REG_READ_CB(readIntStatus);
PPM_REG_READ_CB(readNodeId);
PPM_REG_READ_CB(readStatus);
PPM_NET_CB(syncInput);
PPM_REG_WRITE_CB(writeCommand);
PPM_REG_WRITE_CB(writeHeartbeat);
PPM_REG_WRITE_CB(writeIntClr);
PPM_READ_CB(readMsgLength);
PPM_READ_CB(readMsgStatus);
PPM_WRITE_CB(writeSyncFlag);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


///////////////////////////////// Local memory /////////////////////////////////

// To access local memory hostif/reg/synch : (for example)
// char value = ((char*)handles.hostif)[HOSTIF_REG_SYNCH_OFFSET + myAddress];

#define HOSTIF_REG_SYNCH_OFFSET         0xc
#define HOSTIF_REG_SYNCH_SIZE           0x4

// To access local memory hostif/reg/msglength : (for example)
// char value = ((char*)handles.hostif)[HOSTIF_REG_MSGLENGTH_OFFSET + myAddress];

#define HOSTIF_REG_MSGLENGTH_OFFSET     0x20
#define HOSTIF_REG_MSGLENGTH_SIZE       0x20

// To access local memory hostif/reg/msgstatus : (for example)
// char value = ((char*)handles.hostif)[HOSTIF_REG_MSGSTATUS_OFFSET + myAddress];

#define HOSTIF_REG_MSGSTATUS_OFFSET     0x40
#define HOSTIF_REG_MSGSTATUS_SIZE       0x20

// To access local memory hostif/outbox/buf : (for example)
// char value = ((char*)handles.hostif)[HOSTIF_OUTBOX_BUF_OFFSET + myAddress];

#define HOSTIF_OUTBOX_BUF_OFFSET        0x8000
#define HOSTIF_OUTBOX_BUF_SIZE          0x1000

// To access local memory hostif/inbox/buf : (for example)
// char value = ((char*)handles.hostif)[HOSTIF_INBOX_BUF_OFFSET + myAddress];

#define HOSTIF_INBOX_BUF_OFFSET         0x10000
#define HOSTIF_INBOX_BUF_SIZE           0x1000

////////////////////////////////// Mask macros /////////////////////////////////

#define HOSTIF_REG_STATUS_WIDTH         32
#define HOSTIF_REG_COMMAND_WIDTH        32
#define HOSTIF_REG_INTCLR_WIDTH         32
#define HOSTIF_REG_INTSTATUS_WIDTH      32
#define HOSTIF_REG_NODEID_WIDTH         32
#define HOSTIF_REG_HEARTBEAT_WIDTH      32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
