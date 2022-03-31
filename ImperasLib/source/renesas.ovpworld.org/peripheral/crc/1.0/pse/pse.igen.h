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

typedef struct CRCP0_reg0_dataS { 
    union { 
        Uns32 value;
    } CCRCIN0;
    union { 
        Uns32 value;
    } CCRCD0;
    union { 
        Uns32 value;
    } CCRCIN1;
    union { 
        Uns32 value;
    } CCRCD1;
    union { 
        Uns32 value;
    } CCRCIN2;
    union { 
        Uns32 value;
    } CCRCD2;
    union { 
        Uns32 value;
    } CCRCIN3;
    union { 
        Uns32 value;
    } CCRCD3;
    union { 
        Uns32 value;
    } CCRCIN4;
    union { 
        Uns32 value;
    } CCRCD4;
    union { 
        Uns32 value;
    } DCRCIN;
    union { 
        Uns32 value;
    } DCRCD;
    union { 
        Uns32 value;
        struct {
            Uns32 POL : 1;
            Uns32 ISZ : 2;
            Uns32 __pad3 : 5;
            Uns32 CRCEN0 : 1;
            Uns32 CRCEN1 : 1;
            Uns32 CRCEN2 : 1;
            Uns32 CRCEN3 : 1;
            Uns32 CRCEN4 : 1;
        } bits;
    } CRCC;
} CRCP0_reg0_dataT, *CRCP0_reg0_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern CRCP0_reg0_dataT CRCP0_reg0_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *CRCP0;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_WRITE_CB(writeCCRCD0);
PPM_REG_WRITE_CB(writeCCRCD1);
PPM_REG_WRITE_CB(writeCCRCD2);
PPM_REG_WRITE_CB(writeCCRCD3);
PPM_REG_WRITE_CB(writeCCRCD4);
PPM_REG_WRITE_CB(writeCCRCIN0);
PPM_REG_WRITE_CB(writeCCRCIN1);
PPM_REG_WRITE_CB(writeCCRCIN2);
PPM_REG_WRITE_CB(writeCCRCIN3);
PPM_REG_WRITE_CB(writeCCRCIN4);
PPM_REG_WRITE_CB(writeCRCC);
PPM_REG_WRITE_CB(writeDCRCD);
PPM_REG_WRITE_CB(writeDCRCIN);
PPM_NET_CB(reset_IRESET);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define CRCP0_REG0_CCRCIN0_WIDTH        32
#define CRCP0_REG0_CCRCD0_WIDTH         32
#define CRCP0_REG0_CCRCIN1_WIDTH        32
#define CRCP0_REG0_CCRCD1_WIDTH         32
#define CRCP0_REG0_CCRCIN2_WIDTH        32
#define CRCP0_REG0_CCRCD2_WIDTH         32
#define CRCP0_REG0_CCRCIN3_WIDTH        32
#define CRCP0_REG0_CCRCD3_WIDTH         32
#define CRCP0_REG0_CCRCIN4_WIDTH        32
#define CRCP0_REG0_CCRCD4_WIDTH         32
#define CRCP0_REG0_DCRCIN_WIDTH         32
#define CRCP0_REG0_DCRCD_WIDTH          32
#define CRCP0_REG0_CRCC_WIDTH           32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
