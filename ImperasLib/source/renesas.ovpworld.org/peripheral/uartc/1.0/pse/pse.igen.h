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

typedef struct UARTP0_reg0_dataS { 
    union { 
        Uns8 value;
        struct {
            Uns8 SL : 1;
            Uns8 CL : 1;
            Uns8 PS : 2;
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
            Uns8 BRS : 8;
        } bits;
    } CTL2;
    union { 
        Uns8 value;
        struct {
            Uns8 RDL : 1;
            Uns8 TDL : 1;
            Uns8 SLS : 3;
            Uns8 STT : 1;
            Uns8 SRT : 1;
            Uns8 SRF : 1;
        } bits;
    } OPT0;
    union { 
        Uns8 value;
        struct {
            Uns8 OVE : 1;
            Uns8 FE : 1;
            Uns8 PE : 1;
            Uns8 __pad3 : 4;
            Uns8 TSF : 1;
        } bits;
    } STR;
} UARTP0_reg0_dataT, *UARTP0_reg0_dataTP;

typedef struct UARTP0_reg1_dataS { 
    union { 
        Uns16 value;
        struct {
            Uns16 RXL : 8;
            Uns16 B9 : 1;
        } bits;
    } RX;
    union { 
        Uns16 value;
        struct {
            Uns16 TXL : 8;
            Uns16 B9 : 1;
        } bits;
    } TX;
} UARTP0_reg1_dataT, *UARTP0_reg1_dataTP;

typedef struct UARTP0_reg2_dataS { 
    union { 
        Uns8 value;
        struct {
            Uns8 EBE : 1;
        } bits;
    } OPT1;
    union { 
        Uns8 value;
        struct {
            Uns8 RSF : 1;
        } bits;
    } OPT2;
} UARTP0_reg2_dataT, *UARTP0_reg2_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern UARTP0_reg0_dataT UARTP0_reg0_data;

extern UARTP0_reg1_dataT UARTP0_reg1_data;

extern UARTP0_reg2_dataT UARTP0_reg2_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *UARTP0;
    ppmNetHandle          INTUCT;
    ppmNetHandle          INTUCR;
    ppmNetHandle          INTUCRE;
    ppmNetHandle          TXDC;
    ppmNetHandle          RXDC;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(P_RXDC);
PPM_REG_READ_CB(readRX);
PPM_REG_READ_CB(readTX);
PPM_REG_WRITE_CB(writeCTL0);
PPM_REG_WRITE_CB(writeCTL1);
PPM_REG_WRITE_CB(writeCTL2);
PPM_REG_WRITE_CB(writeOPT0);
PPM_REG_WRITE_CB(writeOPT1);
PPM_REG_WRITE_CB(writeSTR);
PPM_REG_WRITE_CB(writeTX);
PPM_NET_CB(reset_IRESET);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define UARTP0_REG0_CTL0_WIDTH          8
#define UARTP0_REG0_CTL1_WIDTH          8
#define UARTP0_REG0_CTL2_WIDTH          8
#define UARTP0_REG0_OPT0_WIDTH          8
#define UARTP0_REG0_STR_WRMASK          0x87
#define UARTP0_REG0_STR_WRNMASK         (0x78)
#define UARTP0_REG0_STR_WIDTH           8
#define UARTP0_REG1_RX_WIDTH            16
#define UARTP0_REG1_TX_WIDTH            16
#define UARTP0_REG2_OPT1_WRMASK         0x1
#define UARTP0_REG2_OPT1_WRNMASK        (0xfe)
#define UARTP0_REG2_OPT1_WIDTH          8
#define UARTP0_REG2_OPT2_WIDTH          8

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
