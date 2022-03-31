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

typedef struct CSIEP0_reg0_dataS { 
    union { 
        Uns8 value;
        struct {
            Uns8 CSM : 1;
            Uns8 WE : 1;
            Uns8 SIT : 1;
            Uns8 DIR : 1;
            Uns8 TMS : 1;
            Uns8 RXE : 1;
            Uns8 TXE : 1;
            Uns8 PWR : 1;
        } bits;
    } CTL0;
    union { 
        Uns8 value;
        struct {
            Uns8 CKS : 3;
            Uns8 DAP : 1;
            Uns8 CKP : 1;
            Uns8 MDL : 3;
        } bits;
    } CTL1;
} CSIEP0_reg0_dataT, *CSIEP0_reg0_dataTP;

typedef struct CSIEP0_reg1_dataS { 
    union { 
        Uns16 value;
    } RX;
    union { 
        Uns16 value;
        struct {
            Uns16 CS : 4;
        } bits;
    } CS;
    union { 
        Uns16 value;
    } TX;
} CSIEP0_reg1_dataT, *CSIEP0_reg1_dataTP;

typedef struct CSIEP0_reg2_dataS { 
    union { 
        Uns8 value;
        struct {
            Uns8 SFP : 4;
            Uns8 TSF : 1;
            Uns8 EMF : 1;
            Uns8 FLF : 1;
            Uns8 PCT : 1;
        } bits;
    } STR;
    union { 
        Uns8 value;
        struct {
            Uns8 DL : 4;
            Uns8 CSL : 4;
        } bits;
    } CTL2;
    union { 
        Uns8 value;
        struct {
            Uns8 SFN : 4;
        } bits;
    } CTL3;
    union { 
        Uns8 value;
        struct {
            Uns8 MD : 1;
            Uns8 OPE : 1;
            Uns8 DPA : 1;
            Uns8 CPA : 1;
            Uns8 CSL : 4;
        } bits;
    } CTL4;
} CSIEP0_reg2_dataT, *CSIEP0_reg2_dataTP;

typedef struct CSIEP0_reg3_dataS { 
    union { 
        Uns16 value;
    } OPT[8];
} CSIEP0_reg3_dataT, *CSIEP0_reg3_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern CSIEP0_reg0_dataT CSIEP0_reg0_data;

extern CSIEP0_reg1_dataT CSIEP0_reg1_data;

extern CSIEP0_reg2_dataT CSIEP0_reg2_data;

extern CSIEP0_reg3_dataT CSIEP0_reg3_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *CSIEP0;
    ppmNetHandle          INTCEOF;
    ppmNetHandle          INTCEC;
    ppmNetHandle          SOE;
    ppmNetHandle          SCSE0;
    ppmNetHandle          SCSE1;
    ppmNetHandle          SCSE2;
    ppmNetHandle          SCSE3;
    ppmNetHandle          SCSE4;
    ppmNetHandle          SCSE5;
    ppmNetHandle          SCSE6;
    ppmNetHandle          SCSE7;
    ppmNetHandle          SIE;
    ppmNetHandle          SCKE;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(P_SCKE);
PPM_NET_CB(P_SIE);
PPM_REG_READ_CB(readRX);
PPM_REG_READ_CB(readTX);
PPM_REG_WRITE_CB(writeCS);
PPM_REG_WRITE_CB(writeCTL0);
PPM_REG_WRITE_CB(writeCTL1);
PPM_REG_WRITE_CB(writeCTL2);
PPM_REG_WRITE_CB(writeCTL3);
PPM_REG_WRITE_CB(writeCTL4);
PPM_NBYTE_WRITE_CB(writeOPT);
PPM_REG_WRITE_CB(writeSTR);
PPM_REG_WRITE_CB(writeTX);
PPM_NET_CB(reset_IRESET);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define CSIEP0_REG0_CTL0_WIDTH          8
#define CSIEP0_REG0_CTL1_WIDTH          8
#define CSIEP0_REG1_RX_WIDTH            16
#define CSIEP0_REG1_CS_WRMASK           0xf
#define CSIEP0_REG1_CS_WRNMASK          (0xfff0)
#define CSIEP0_REG1_CS_WIDTH            16
#define CSIEP0_REG1_TX_WIDTH            16
#define CSIEP0_REG2_STR_WIDTH           8
#define CSIEP0_REG2_CTL2_WIDTH          8
#define CSIEP0_REG2_CTL3_WRMASK         0xf
#define CSIEP0_REG2_CTL3_WRNMASK        (0xf0)
#define CSIEP0_REG2_CTL3_WIDTH          8
#define CSIEP0_REG2_CTL4_WIDTH          8
#define CSIEP0_REG3_OPT_WIDTH           16

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
