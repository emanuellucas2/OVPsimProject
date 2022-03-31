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
        struct {
            Uns32 DATA : 8;
            Uns32 FE : 1;
            Uns32 PE : 1;
            Uns32 BE : 1;
            Uns32 OE : 1;
        } bits;
    } dr;
    union { 
        Uns32 value;
        struct {
            Uns32 FE : 1;
            Uns32 PE : 1;
            Uns32 BE : 1;
            Uns32 OE : 1;
        } bits;
    } rsrecr;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 3;
            Uns32 BUSY : 1;
            Uns32 RXFE : 1;
            Uns32 TXFF : 1;
            Uns32 RXFF : 1;
            Uns32 TXFE : 1;
        } bits;
    } fr;
    union { 
        Uns32 value;
        struct {
            Uns32 DIVFRAC : 6;
        } bits;
    } fbrd;
    union { 
        Uns32 value;
        struct {
            Uns32 DIVINT : 16;
        } bits;
    } ibrd;
    union { 
        Uns32 value;
        struct {
            Uns32 BRK : 1;
            Uns32 PEN : 1;
            Uns32 EPS : 1;
            Uns32 STP2 : 1;
            Uns32 FEN : 1;
            Uns32 WLEN : 2;
            Uns32 SPS : 1;
        } bits;
    } lcrh;
    union { 
        Uns32 value;
        struct {
            Uns32 UARTEN : 1;
            Uns32 __pad1 : 6;
            Uns32 LBE : 1;
            Uns32 TXE : 1;
            Uns32 RXE : 1;
        } bits;
    } ctl;
    union { 
        Uns32 value;
        struct {
            Uns32 TXIFLSEL : 3;
            Uns32 RXIFLSEL : 3;
        } bits;
    } ifls;
    union { 
        Uns32 value;
        struct {
            Uns32 RXIM : 1;
            Uns32 TXIM : 1;
            Uns32 RTIM : 1;
            Uns32 FEIM : 1;
            Uns32 PEIM : 1;
            Uns32 BEIM : 1;
            Uns32 OEIM : 1;
        } bits;
    } im;
    union { 
        Uns32 value;
        struct {
            Uns32 RXRIS : 1;
            Uns32 TXRIS : 1;
            Uns32 RTRIS : 1;
            Uns32 FERIS : 1;
            Uns32 PERIS : 1;
            Uns32 BERIS : 1;
            Uns32 OERIS : 1;
        } bits;
    } ris;
    union { 
        Uns32 value;
        struct {
            Uns32 RXMIS : 1;
            Uns32 TXMIS : 1;
            Uns32 RTMIS : 1;
            Uns32 FEMIS : 1;
            Uns32 PEMIS : 1;
            Uns32 BEMIS : 1;
            Uns32 OEMIS : 1;
        } bits;
    } mis;
    union { 
        Uns32 value;
        struct {
            Uns32 RXIC : 1;
            Uns32 TXIC : 1;
            Uns32 RTIC : 1;
            Uns32 FEIC : 1;
            Uns32 PEIC : 1;
            Uns32 BEIC : 1;
            Uns32 OEIC : 1;
        } bits;
    } icr;
    union { 
        Uns32 value;
    } pid0;
    union { 
        Uns32 value;
    } pid1;
    union { 
        Uns32 value;
    } pid2;
    union { 
        Uns32 value;
    } pid3;
    union { 
        Uns32 value;
    } pid4;
    union { 
        Uns32 value;
    } pid5;
    union { 
        Uns32 value;
    } pid6;
    union { 
        Uns32 value;
    } pid7;
    union { 
        Uns32 value;
    } cid0;
    union { 
        Uns32 value;
    } cid1;
    union { 
        Uns32 value;
    } cid2;
    union { 
        Uns32 value;
    } cid3;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          irq;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(readCTL);
PPM_REG_READ_CB(readDR);
PPM_REG_READ_CB(readICR);
PPM_REG_READ_CB(readIM);
PPM_REG_READ_CB(readMIS);
PPM_REG_READ_CB(readRIS);
PPM_REG_READ_CB(readSR);
PPM_REG_READ_CB(readSRRECR);
PPM_REG_WRITE_CB(writeCTL);
PPM_REG_WRITE_CB(writeDR);
PPM_REG_WRITE_CB(writeICR);
PPM_REG_WRITE_CB(writeIM);
PPM_REG_WRITE_CB(writeMIS);
PPM_REG_WRITE_CB(writeRIS);
PPM_REG_WRITE_CB(writeSRRECR);
PPM_NET_CB(reset_reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_DR_WIDTH              32
#define BPORT1_AB_RSRECR_WIDTH          32
#define BPORT1_AB_FR_WIDTH              32
#define BPORT1_AB_FBRD_WIDTH            32
#define BPORT1_AB_IBRD_WIDTH            32
#define BPORT1_AB_LCRH_WIDTH            32
#define BPORT1_AB_CTL_WIDTH             32
#define BPORT1_AB_IFLS_WIDTH            32
#define BPORT1_AB_IM_WIDTH              32
#define BPORT1_AB_RIS_WIDTH             32
#define BPORT1_AB_MIS_WIDTH             32
#define BPORT1_AB_ICR_WIDTH             32
#define BPORT1_AB_PID0_WIDTH            32
#define BPORT1_AB_PID1_WIDTH            32
#define BPORT1_AB_PID2_WIDTH            32
#define BPORT1_AB_PID3_WIDTH            32
#define BPORT1_AB_PID4_WIDTH            32
#define BPORT1_AB_PID5_WIDTH            32
#define BPORT1_AB_PID6_WIDTH            32
#define BPORT1_AB_PID7_WIDTH            32
#define BPORT1_AB_CID0_WIDTH            32
#define BPORT1_AB_CID1_WIDTH            32
#define BPORT1_AB_CID2_WIDTH            32
#define BPORT1_AB_CID3_WIDTH            32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
