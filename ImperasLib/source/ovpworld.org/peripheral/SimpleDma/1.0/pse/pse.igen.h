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

typedef struct DMACSP_ab8_dataS { 
    union { 
        Uns8 value;
    } intTCstatus;
    union { 
        Uns8 value;
    } rawTCstatus;
    union { 
        Uns8 value;
        struct {
            Uns8 burstSize : 2;
        } bits;
    } config;
} DMACSP_ab8_dataT, *DMACSP_ab8_dataTP;

typedef struct DMACSP_ab32ch0_dataS { 
    union { 
        Uns32 value;
    } srcAddr;
    union { 
        Uns32 value;
    } dstAddr;
    union { 
        Uns32 value;
        struct {
            Uns32 transferSize : 12;
        } bits;
    } control;
    union { 
        Uns32 value;
        struct {
            Uns32 enable : 1;
            Uns32 __pad1 : 14;
            Uns32 inten : 1;
            Uns32 __pad16 : 2;
            Uns32 halt : 1;
        } bits;
    } config;
} DMACSP_ab32ch0_dataT, *DMACSP_ab32ch0_dataTP;

typedef struct DMACSP_ab32ch1_dataS { 
    union { 
        Uns32 value;
    } srcAddr;
    union { 
        Uns32 value;
    } dstAddr;
    union { 
        Uns32 value;
        struct {
            Uns32 transferSize : 12;
        } bits;
    } control;
    union { 
        Uns32 value;
        struct {
            Uns32 enable : 1;
            Uns32 __pad1 : 14;
            Uns32 inten : 1;
            Uns32 __pad16 : 2;
            Uns32 halt : 1;
        } bits;
    } config;
} DMACSP_ab32ch1_dataT, *DMACSP_ab32ch1_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern DMACSP_ab8_dataT DMACSP_ab8_data;

extern DMACSP_ab32ch0_dataT DMACSP_ab32ch0_data;

extern DMACSP_ab32ch1_dataT DMACSP_ab32ch1_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    ppmAddressSpaceHandle MREAD;
    ppmAddressSpaceHandle MWRITE;
    void                 *DMACSP;
    ppmNetHandle          INTTC;
    ppmNetHandle          RESET;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_WRITE_CB(TCclearWr);
PPM_REG_WRITE_CB(configChWr);
PPM_REG_WRITE_CB(configWr);
PPM_NET_CB(uReset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define DMACSP_AB8_INTTCSTATUS_WIDTH    8
#define DMACSP_AB8_RAWTCSTATUS_WIDTH    8
#define DMACSP_AB8_CONFIG_WIDTH         8
#define DMACSP_AB32CH0_SRCADDR_WIDTH    32
#define DMACSP_AB32CH0_DSTADDR_WIDTH    32
#define DMACSP_AB32CH0_CONTROL_WIDTH    32
#define DMACSP_AB32CH0_CONFIG_WIDTH     32
#define DMACSP_AB32CH1_SRCADDR_WIDTH    32
#define DMACSP_AB32CH1_DSTADDR_WIDTH    32
#define DMACSP_AB32CH1_CONTROL_WIDTH    32
#define DMACSP_AB32CH1_CONFIG_WIDTH     32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
