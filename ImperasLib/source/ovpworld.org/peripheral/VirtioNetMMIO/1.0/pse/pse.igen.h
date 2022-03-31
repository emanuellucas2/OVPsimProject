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
    } MagicValue;
    union { 
        Uns32 value;
    } Version;
    union { 
        Uns32 value;
    } DeviceID;
    union { 
        Uns32 value;
    } VendorID;
    union { 
        Uns32 value;
    } HostFeatures;
    union { 
        Uns32 value;
    } HostFSel;
    union { 
        Uns32 value;
    } GuestFeatures;
    union { 
        Uns32 value;
    } GuestFSel;
    union { 
        Uns32 value;
    } GuestPageSz;
    union { 
        Uns32 value;
    } QueueSel;
    union { 
        Uns32 value;
    } QueueNumMax;
    union { 
        Uns32 value;
    } QueueNum;
    union { 
        Uns32 value;
    } QueueAlign;
    union { 
        Uns32 value;
    } QueuePFN;
    union { 
        Uns32 value;
    } QueueNotify;
    union { 
        Uns32 value;
        struct {
            Uns32 UsedRingUpdate : 1;
            Uns32 ConfigChange : 1;
        } bits;
    } IntStatus;
    union { 
        Uns32 value;
        struct {
            Uns32 UsedRingUpdate : 1;
            Uns32 ConfigChange : 1;
        } bits;
    } IntAck;
    union { 
        Uns32 value;
        struct {
            Uns32 Ack : 1;
            Uns32 Driver : 1;
            Uns32 DriverOk : 1;
            Uns32 __pad3 : 4;
            Uns32 Failed : 1;
        } bits;
    } Status;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    ppmAddressSpaceHandle dma;
    void                 *bport1;
    ppmNetHandle          Interrupt;
    ppmPacketnetHandle    phy;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NBYTE_READ_CB(rdHostF);
PPM_NBYTE_READ_CB(rdIntStat);
PPM_NBYTE_READ_CB(rdMagic);
PPM_NBYTE_READ_CB(rdQPFN);
PPM_NBYTE_READ_CB(rdStatus);
PPM_NBYTE_WRITE_CB(wrGPgSz);
PPM_NBYTE_WRITE_CB(wrGuestF);
PPM_NBYTE_WRITE_CB(wrIntAck);
PPM_NBYTE_WRITE_CB(wrQAlign);
PPM_NBYTE_WRITE_CB(wrQNotify);
PPM_NBYTE_WRITE_CB(wrQNum);
PPM_NBYTE_WRITE_CB(wrQPFN);
PPM_NBYTE_WRITE_CB(wrSel);
PPM_NBYTE_WRITE_CB(wrStatus);
PPM_NBYTE_READ_CB(readCfg);
PPM_NBYTE_WRITE_CB(writeCfg);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


///////////////////////////////// Local memory /////////////////////////////////

// To access local memory bport1/ab/NetConfig : (for example)
// char value = ((char*)handles.bport1)[BPORT1_AB_NETCONFIG_OFFSET + myAddress];

#define BPORT1_AB_NETCONFIG_OFFSET      0x100
#define BPORT1_AB_NETCONFIG_SIZE        0x100

////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_MAGICVALUE_WIDTH      32
#define BPORT1_AB_VERSION_WIDTH         32
#define BPORT1_AB_DEVICEID_WIDTH        32
#define BPORT1_AB_VENDORID_WIDTH        32
#define BPORT1_AB_HOSTFEATURES_WIDTH    32
#define BPORT1_AB_HOSTFSEL_WIDTH        32
#define BPORT1_AB_GUESTFEATURES_WIDTH   32
#define BPORT1_AB_GUESTFSEL_WIDTH       32
#define BPORT1_AB_GUESTPAGESZ_WIDTH     32
#define BPORT1_AB_QUEUESEL_WIDTH        32
#define BPORT1_AB_QUEUENUMMAX_WIDTH     32
#define BPORT1_AB_QUEUENUM_WIDTH        32
#define BPORT1_AB_QUEUEALIGN_WIDTH      32
#define BPORT1_AB_QUEUEPFN_WIDTH        32
#define BPORT1_AB_QUEUENOTIFY_WIDTH     32
#define BPORT1_AB_INTSTATUS_WIDTH       32
#define BPORT1_AB_INTACK_WRMASK         0x3
#define BPORT1_AB_INTACK_WRNMASK        (0xfffffffc)
#define BPORT1_AB_INTACK_WIDTH          32
#define BPORT1_AB_STATUS_WIDTH          32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
