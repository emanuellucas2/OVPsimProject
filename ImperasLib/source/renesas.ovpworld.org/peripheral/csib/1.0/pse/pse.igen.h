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

typedef struct CSIBP0_reg0_dataS { 
    union { 
        Uns8 value;
        struct {
            Uns8 SCE : 1;
            Uns8 TMS : 1;
            Uns8 SSE : 1;
            Uns8 __pad3 : 1;
            Uns8 DIR : 1;
            Uns8 RXE : 1;
            Uns8 TXE : 1;
            Uns8 PWR : 1;
        } bits;
    } CTL0;
    union { 
        Uns8 value;
        struct {
            Uns8 CKS : 4;
        } bits;
    } CTL1;
    union { 
        Uns8 value;
        struct {
            Uns8 CL : 4;
        } bits;
    } CTL2;
    union { 
        Uns8 value;
        struct {
            Uns8 OVE : 1;
            Uns8 __pad1 : 6;
            Uns8 TSF : 1;
        } bits;
    } STR;
} CSIBP0_reg0_dataT, *CSIBP0_reg0_dataTP;

typedef struct CSIBP0_reg1_dataS { 
    union { 
        Uns16 value;
        struct {
            Uns16 RXL : 8;
            Uns16 RXH : 8;
        } bits;
    } RX;
    union { 
        Uns16 value;
        struct {
            Uns16 TXL : 8;
            Uns16 TXH : 8;
        } bits;
    } TX;
} CSIBP0_reg1_dataT, *CSIBP0_reg1_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern CSIBP0_reg0_dataT CSIBP0_reg0_data;

extern CSIBP0_reg1_dataT CSIBP0_reg1_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *CSIBP0;
    ppmNetHandle          INTCBT;
    ppmNetHandle          INTCBR;
    ppmNetHandle          INTCBRE;
    ppmNetHandle          SOB;
    ppmNetHandle          SIB;
    ppmNetHandle          SSB;
    ppmNetHandle          SCKB;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(P_SCKB);
PPM_NET_CB(P_SIB);
PPM_NET_CB(P_SSB);
PPM_REG_READ_CB(readRX);
PPM_REG_READ_CB(readTX);
PPM_REG_WRITE_CB(writeCTL0);
PPM_REG_WRITE_CB(writeCTL1);
PPM_REG_WRITE_CB(writeCTL2);
PPM_REG_WRITE_CB(writeSTR);
PPM_REG_WRITE_CB(writeTX);
PPM_NET_CB(reset_IRESET);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define CSIBP0_REG0_CTL0_WRMASK         0xf7
#define CSIBP0_REG0_CTL0_WRNMASK        (0x8)
#define CSIBP0_REG0_CTL0_WIDTH          8
#define CSIBP0_REG0_CTL1_WRMASK         0x1f
#define CSIBP0_REG0_CTL1_WRNMASK        (0xe0)
#define CSIBP0_REG0_CTL1_WIDTH          8
#define CSIBP0_REG0_CTL2_WRMASK         0xf
#define CSIBP0_REG0_CTL2_WRNMASK        (0xf0)
#define CSIBP0_REG0_CTL2_WIDTH          8
#define CSIBP0_REG0_STR_WRMASK          0x81
#define CSIBP0_REG0_STR_WRNMASK         (0x7e)
#define CSIBP0_REG0_STR_WIDTH           8
#define CSIBP0_REG1_RX_WIDTH            16
#define CSIBP0_REG1_TX_WIDTH            16

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
