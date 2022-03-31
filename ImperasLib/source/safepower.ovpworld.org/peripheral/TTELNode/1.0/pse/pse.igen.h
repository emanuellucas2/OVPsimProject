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

typedef struct hostif_rec_dataS { 
} hostif_rec_dataT, *hostif_rec_dataTP;

typedef struct hostif_port_dataS { 
} hostif_port_dataT, *hostif_port_dataTP;

typedef struct hostif_err_dataS { 
} hostif_err_dataT, *hostif_err_dataTP;

typedef struct hostif_mon_dataS { 
} hostif_mon_dataT, *hostif_mon_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern hostif_rec_dataT hostif_rec_data;

extern hostif_port_dataT hostif_port_data[253];

extern hostif_err_dataT hostif_err_data;

extern hostif_mon_dataT hostif_mon_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *hostif;
    ppmNetHandle          PeriodInterrupt;
    ppmNetHandle          CoreInterrupt;
    ppmNetHandle          pIntToCore;
    ppmPacketnetHandle    network;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_PACKETNET_CB(networkReceiveMsg);
PPM_NBYTE_READ_CB(readData);
PPM_READ_CB(readGlobalTime);
PPM_NBYTE_READ_CB(readPortLength);
PPM_NBYTE_WRITE_CB(writeData);
PPM_NBYTE_WRITE_CB(writePortTerminate);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


///////////////////////////////// Local memory /////////////////////////////////

// To access local memory hostif/rec/port : (for example)
// char value = ((char*)handles.hostif)[HOSTIF_REC_PORT_OFFSET + myAddress];

#define HOSTIF_REC_PORT_OFFSET          0x0
#define HOSTIF_REC_PORT_SIZE            0x10000

// To access local memory hostif/rec/term : (for example)
// char value = ((char*)handles.hostif)[HOSTIF_REC_TERM_OFFSET + myAddress];

#define HOSTIF_REC_TERM_OFFSET          0x8000
#define HOSTIF_REC_TERM_SIZE            0x1fff

// To access local memory hostif/port%u/data : (for example)
// char value = ((char*)handles.hostif)[HOSTIF_PORT_DATA_OFFSET + myAddress];

#define HOSTIF_PORT_DATA_OFFSET         0x10000
#define HOSTIF_PORT_DATA_SIZE           0x1fff

// To access local memory hostif/port%u/length : (for example)
// char value = ((char*)handles.hostif)[HOSTIF_PORT_LENGTH_OFFSET + myAddress];

#define HOSTIF_PORT_LENGTH_OFFSET       0x14000
#define HOSTIF_PORT_LENGTH_SIZE         0x1fff

// To access local memory hostif/port%u/term : (for example)
// char value = ((char*)handles.hostif)[HOSTIF_PORT_TERM_OFFSET + myAddress];

#define HOSTIF_PORT_TERM_OFFSET         0x18000
#define HOSTIF_PORT_TERM_SIZE           0x1fff

// To access local memory hostif/err/err : (for example)
// char value = ((char*)handles.hostif)[HOSTIF_ERR_ERR_OFFSET + myAddress];

#define HOSTIF_ERR_ERR_OFFSET           0xfe0000
#define HOSTIF_ERR_ERR_SIZE             0x10000

// To access local memory hostif/mon/empty : (for example)
// char value = ((char*)handles.hostif)[HOSTIF_MON_EMPTY_OFFSET + myAddress];

#define HOSTIF_MON_EMPTY_OFFSET         0xff0000
#define HOSTIF_MON_EMPTY_SIZE           0x20

// To access local memory hostif/mon/full : (for example)
// char value = ((char*)handles.hostif)[HOSTIF_MON_FULL_OFFSET + myAddress];

#define HOSTIF_MON_FULL_OFFSET          0xff0020
#define HOSTIF_MON_FULL_SIZE            0x20

// To access local memory hostif/mon/status : (for example)
// char value = ((char*)handles.hostif)[HOSTIF_MON_STATUS_OFFSET + myAddress];

#define HOSTIF_MON_STATUS_OFFSET        0xff0040
#define HOSTIF_MON_STATUS_SIZE          0x400

// To access local memory hostif/mon/gbltim0 : (for example)
// char value = ((char*)handles.hostif)[HOSTIF_MON_GBLTIM0_OFFSET + myAddress];

#define HOSTIF_MON_GBLTIM0_OFFSET       0xff0440
#define HOSTIF_MON_GBLTIM0_SIZE         0x4

// To access local memory hostif/mon/gbltim1 : (for example)
// char value = ((char*)handles.hostif)[HOSTIF_MON_GBLTIM1_OFFSET + myAddress];

#define HOSTIF_MON_GBLTIM1_OFFSET       0xff0444
#define HOSTIF_MON_GBLTIM1_SIZE         0x4

////////////////////////////////// Mask macros /////////////////////////////////


//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
