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

typedef struct MEMCP0_reg0_dataS { 
    union { 
        Uns16 value;
        struct {
            Uns16 __pad0 : 3;
            Uns16 ME0 : 1;
            Uns16 __pad4 : 3;
            Uns16 ME1 : 1;
            Uns16 __pad8 : 3;
            Uns16 ME2 : 1;
            Uns16 __pad12 : 3;
            Uns16 ME3 : 1;
        } bits;
    } BCT0;
    union { 
        Uns16 value;
        struct {
            Uns16 __pad0 : 3;
            Uns16 ME4 : 1;
            Uns16 __pad4 : 3;
            Uns16 ME5 : 1;
            Uns16 __pad8 : 3;
            Uns16 ME6 : 1;
            Uns16 __pad12 : 3;
            Uns16 ME7 : 1;
        } bits;
    } BCT1;
    union { 
        Uns16 value;
        struct {
            Uns16 DW0 : 3;
            Uns16 __pad3 : 1;
            Uns16 DW1 : 3;
            Uns16 __pad7 : 1;
            Uns16 DW2 : 3;
            Uns16 __pad11 : 1;
            Uns16 DW3 : 3;
        } bits;
    } DWC0;
    union { 
        Uns16 value;
        struct {
            Uns16 DW4 : 3;
            Uns16 __pad3 : 1;
            Uns16 DW5 : 3;
            Uns16 __pad7 : 1;
            Uns16 DW6 : 3;
            Uns16 __pad11 : 1;
            Uns16 DW7 : 3;
        } bits;
    } DWC1;
    union { 
        Uns16 value;
        struct {
            Uns16 ASW0 : 1;
            Uns16 AHW0 : 1;
            Uns16 ASW1 : 1;
            Uns16 AHW1 : 1;
            Uns16 ASW2 : 1;
            Uns16 AHW2 : 1;
            Uns16 ASW3 : 1;
            Uns16 AHW3 : 1;
            Uns16 ASW4 : 1;
            Uns16 AHW4 : 1;
            Uns16 ASW5 : 1;
            Uns16 AHW5 : 1;
            Uns16 ASW6 : 1;
            Uns16 AHW6 : 1;
            Uns16 ASW7 : 1;
            Uns16 AHW7 : 1;
        } bits;
    } AWC;
    union { 
        Uns16 value;
        struct {
            Uns16 __pad0 : 1;
            Uns16 BC01 : 1;
            Uns16 __pad2 : 1;
            Uns16 BC11 : 1;
            Uns16 __pad4 : 1;
            Uns16 BC21 : 1;
            Uns16 __pad6 : 1;
            Uns16 BC31 : 1;
            Uns16 __pad8 : 1;
            Uns16 BC41 : 1;
            Uns16 __pad10 : 1;
            Uns16 BC51 : 1;
            Uns16 __pad12 : 1;
            Uns16 BC61 : 1;
            Uns16 __pad14 : 1;
            Uns16 BC71 : 1;
        } bits;
    } BCC;
} MEMCP0_reg0_dataT, *MEMCP0_reg0_dataTP;

typedef struct MEMCP0_reg1_dataS { 
    union { 
        Uns8 value;
    } DVC;
} MEMCP0_reg1_dataT, *MEMCP0_reg1_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern MEMCP0_reg0_dataT MEMCP0_reg0_data;

extern MEMCP0_reg1_dataT MEMCP0_reg1_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *MEMCP0;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_WRITE_CB(writeAWC);
PPM_REG_WRITE_CB(writeBCC);
PPM_REG_WRITE_CB(writeBCT0);
PPM_REG_WRITE_CB(writeBCT1);
PPM_REG_WRITE_CB(writeDVC);
PPM_REG_WRITE_CB(writeDWC0);
PPM_REG_WRITE_CB(writeDWC1);
PPM_NET_CB(reset_IRESET);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define MEMCP0_REG0_BCT0_WRMASK         0x8888
#define MEMCP0_REG0_BCT0_WRNMASK        (0x7777)
#define MEMCP0_REG0_BCT0_WIDTH          16
#define MEMCP0_REG0_BCT1_WRMASK         0x8888
#define MEMCP0_REG0_BCT1_WRNMASK        (0x7777)
#define MEMCP0_REG0_BCT1_WIDTH          16
#define MEMCP0_REG0_DWC0_WRMASK         0x7777
#define MEMCP0_REG0_DWC0_WRNMASK        (0x8888)
#define MEMCP0_REG0_DWC0_WIDTH          16
#define MEMCP0_REG0_DWC1_WRMASK         0x7777
#define MEMCP0_REG0_DWC1_WRNMASK        (0x8888)
#define MEMCP0_REG0_DWC1_WIDTH          16
#define MEMCP0_REG0_AWC_WIDTH           16
#define MEMCP0_REG0_BCC_WRMASK          0xaaaa
#define MEMCP0_REG0_BCC_WRNMASK         (0x5555)
#define MEMCP0_REG0_BCC_WIDTH           16
#define MEMCP0_REG1_DVC_WRMASK          0x81
#define MEMCP0_REG1_DVC_WRNMASK         (0x7e)
#define MEMCP0_REG1_DVC_WIDTH           8

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
