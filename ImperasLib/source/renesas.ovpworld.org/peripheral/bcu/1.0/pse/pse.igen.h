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

typedef struct BCUP0_reg0_dataS { 
    union { 
        Uns16 value;
        struct {
            Uns16 CS0 : 4;
            Uns16 CS1 : 4;
            Uns16 CS2 : 4;
            Uns16 CS3 : 4;
        } bits;
    } CSC0;
    union { 
        Uns16 value;
        struct {
            Uns16 CS7 : 4;
            Uns16 CS6 : 4;
            Uns16 CS5 : 4;
            Uns16 CS4 : 4;
        } bits;
    } CSC1;
    union { 
        Uns16 value;
    } BPC;
    union { 
        Uns16 value;
        struct {
            Uns16 BS0 : 2;
            Uns16 BS1 : 2;
            Uns16 BS2 : 2;
            Uns16 BS3 : 2;
            Uns16 BS4 : 2;
            Uns16 BS5 : 2;
            Uns16 BS6 : 2;
            Uns16 BS7 : 2;
        } bits;
    } BSC;
    union { 
        Uns16 value;
        struct {
            Uns16 BE00 : 1;
            Uns16 __pad1 : 1;
            Uns16 BE10 : 1;
            Uns16 __pad3 : 1;
            Uns16 BE20 : 1;
            Uns16 __pad5 : 1;
            Uns16 BE30 : 1;
            Uns16 __pad7 : 1;
            Uns16 BE40 : 1;
            Uns16 __pad9 : 1;
            Uns16 BE50 : 1;
            Uns16 __pad11 : 1;
            Uns16 BE60 : 1;
            Uns16 __pad13 : 1;
            Uns16 BE70 : 1;
        } bits;
    } BEC;
} BCUP0_reg0_dataT, *BCUP0_reg0_dataTP;

typedef struct BCUP0_reg1_dataS { 
    union { 
        Uns8 value;
    } VSWC;
} BCUP0_reg1_dataT, *BCUP0_reg1_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern BCUP0_reg0_dataT BCUP0_reg0_data;

extern BCUP0_reg1_dataT BCUP0_reg1_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *BCUP0;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_WRITE_CB(writeBEC);
PPM_REG_WRITE_CB(writeBPC);
PPM_REG_WRITE_CB(writeBSC);
PPM_REG_WRITE_CB(writeCSC1);
PPM_REG_WRITE_CB(writeCSCO);
PPM_REG_WRITE_CB(writeVSWC);
PPM_NET_CB(reset_IRESET);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BCUP0_REG0_CSC0_WIDTH           16
#define BCUP0_REG0_CSC1_WIDTH           16
#define BCUP0_REG0_BPC_WRMASK           0xbfff
#define BCUP0_REG0_BPC_WRNMASK          (0x4000)
#define BCUP0_REG0_BPC_WIDTH            16
#define BCUP0_REG0_BSC_WIDTH            16
#define BCUP0_REG0_BEC_WRMASK           0x5555
#define BCUP0_REG0_BEC_WRNMASK          (0xaaaa)
#define BCUP0_REG0_BEC_WIDTH            16
#define BCUP0_REG1_VSWC_WIDTH           8

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
