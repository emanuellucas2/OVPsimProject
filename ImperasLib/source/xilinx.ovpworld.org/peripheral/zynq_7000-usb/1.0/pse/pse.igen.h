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
    } HWGENERAL;
    union { 
        Uns32 value;
    } HWHOST;
    union { 
        Uns32 value;
    } HWDEVICE;
    union { 
        Uns32 value;
    } HWTXBUF;
    union { 
        Uns32 value;
    } HWRXBUF;
    union { 
        Uns32 value;
    } GPTIMER0LD;
    union { 
        Uns32 value;
    } GPTIMER0CTRL;
    union { 
        Uns32 value;
    } GPTIMER1LD;
    union { 
        Uns32 value;
    } GPTIMER1CTRL;
    union { 
        Uns32 value;
    } SBUSCFG;
    union { 
        Uns32 value;
    } CAPLENGTH_HCIVERSION;
    union { 
        Uns32 value;
    } HCSPARAMS;
    union { 
        Uns32 value;
    } HCCPARAMS;
    union { 
        Uns32 value;
    } DCIVERSION;
    union { 
        Uns32 value;
    } DCCPARAMS;
    union { 
        Uns32 value;
    } USBCMD;
    union { 
        Uns32 value;
    } USBSTS;
    union { 
        Uns32 value;
    } USBINTR;
    union { 
        Uns32 value;
    } FRINDEX;
    union { 
        Uns32 value;
    } PERIODICLISTBASE_DEVICEADDR;
    union { 
        Uns32 value;
    } ASYNCLISTADDR_ENDPOINTLISTADDR;
    union { 
        Uns32 value;
    } TTCTRL;
    union { 
        Uns32 value;
    } BURSTSIZE;
    union { 
        Uns32 value;
    } TXFILLTUNING;
    union { 
        Uns32 value;
    } TXTTFILLTUNING;
    union { 
        Uns32 value;
    } IC_USB;
    union { 
        Uns32 value;
    } ULPI_VIEWPORT;
    union { 
        Uns32 value;
    } ENDPTNAK;
    union { 
        Uns32 value;
    } ENDPTNAKEN;
    union { 
        Uns32 value;
    } CONFIGFLAG;
    union { 
        Uns32 value;
    } PORTSC1;
    union { 
        Uns32 value;
    } OTGSC;
    union { 
        Uns32 value;
    } USBMODE;
    union { 
        Uns32 value;
    } ENDPTSETUPSTAT;
    union { 
        Uns32 value;
    } ENDPTPRIME;
    union { 
        Uns32 value;
    } ENDPTFLUSH;
    union { 
        Uns32 value;
    } ENDPTSTAT;
    union { 
        Uns32 value;
    } ENDPTCOMPLETE;
    union { 
        Uns32 value;
    } ENDPTCTRL0;
    union { 
        Uns32 value;
    } ENDPTCTRL1;
    union { 
        Uns32 value;
    } ENDPTCTRL2;
    union { 
        Uns32 value;
    } ENDPTCTRL3;
    union { 
        Uns32 value;
    } ENDPTCTRL4;
    union { 
        Uns32 value;
    } ENDPTCTRL5;
    union { 
        Uns32 value;
    } ENDPTCTRL6;
    union { 
        Uns32 value;
    } ENDPTCTRL7;
    union { 
        Uns32 value;
    } ENDPTCTRL8;
    union { 
        Uns32 value;
    } ENDPTCTRL9;
    union { 
        Uns32 value;
    } ENDPTCTRL10;
    union { 
        Uns32 value;
    } ENDPTCTRL11;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          intOut;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_WRITE_CB(wrVP);
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

#define BPORT1_AB_ID_WIDTH              32
#define BPORT1_AB_HWGENERAL_WIDTH       32
#define BPORT1_AB_HWHOST_WIDTH          32
#define BPORT1_AB_HWDEVICE_WIDTH        32
#define BPORT1_AB_HWTXBUF_WIDTH         32
#define BPORT1_AB_HWRXBUF_WIDTH         32
#define BPORT1_AB_GPTIMER0LD_WIDTH      32
#define BPORT1_AB_GPTIMER0CTRL_WIDTH    32
#define BPORT1_AB_GPTIMER1LD_WIDTH      32
#define BPORT1_AB_GPTIMER1CTRL_WIDTH    32
#define BPORT1_AB_SBUSCFG_WIDTH         32
#define BPORT1_AB_CAPLENGTH_HCIVERSION_WIDTH  32
#define BPORT1_AB_HCSPARAMS_WIDTH       32
#define BPORT1_AB_HCCPARAMS_WIDTH       32
#define BPORT1_AB_DCIVERSION_WIDTH      32
#define BPORT1_AB_DCCPARAMS_WIDTH       32
#define BPORT1_AB_USBCMD_WIDTH          32
#define BPORT1_AB_USBSTS_WIDTH          32
#define BPORT1_AB_USBINTR_WIDTH         32
#define BPORT1_AB_FRINDEX_WIDTH         32
#define BPORT1_AB_PERIODICLISTBASE_DEVICEADDR_WIDTH  32
#define BPORT1_AB_ASYNCLISTADDR_ENDPOINTLISTADDR_WIDTH  32
#define BPORT1_AB_TTCTRL_WIDTH          32
#define BPORT1_AB_BURSTSIZE_WIDTH       32
#define BPORT1_AB_TXFILLTUNING_WIDTH    32
#define BPORT1_AB_TXTTFILLTUNING_WIDTH  32
#define BPORT1_AB_IC_USB_WIDTH          32
#define BPORT1_AB_ULPI_VIEWPORT_WIDTH   32
#define BPORT1_AB_ENDPTNAK_WIDTH        32
#define BPORT1_AB_ENDPTNAKEN_WIDTH      32
#define BPORT1_AB_CONFIGFLAG_WIDTH      32
#define BPORT1_AB_PORTSC1_WIDTH         32
#define BPORT1_AB_OTGSC_WIDTH           32
#define BPORT1_AB_USBMODE_WIDTH         32
#define BPORT1_AB_ENDPTSETUPSTAT_WIDTH  32
#define BPORT1_AB_ENDPTPRIME_WIDTH      32
#define BPORT1_AB_ENDPTFLUSH_WIDTH      32
#define BPORT1_AB_ENDPTSTAT_WIDTH       32
#define BPORT1_AB_ENDPTCOMPLETE_WIDTH   32
#define BPORT1_AB_ENDPTCTRL0_WIDTH      32
#define BPORT1_AB_ENDPTCTRL1_WIDTH      32
#define BPORT1_AB_ENDPTCTRL2_WIDTH      32
#define BPORT1_AB_ENDPTCTRL3_WIDTH      32
#define BPORT1_AB_ENDPTCTRL4_WIDTH      32
#define BPORT1_AB_ENDPTCTRL5_WIDTH      32
#define BPORT1_AB_ENDPTCTRL6_WIDTH      32
#define BPORT1_AB_ENDPTCTRL7_WIDTH      32
#define BPORT1_AB_ENDPTCTRL8_WIDTH      32
#define BPORT1_AB_ENDPTCTRL9_WIDTH      32
#define BPORT1_AB_ENDPTCTRL10_WIDTH     32
#define BPORT1_AB_ENDPTCTRL11_WIDTH     32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
