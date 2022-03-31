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
            Uns32 MINOR : 4;
            Uns32 MAJOR : 12;
            Uns32 ID : 16;
        } bits;
    } IDREV;
    union { 
        Uns32 value;
        struct {
            Uns32 FIFO_DEPTH : 2;
        } bits;
    } CFG;
    union { 
        Uns32 value;
        struct {
            Uns32 OSC : 5;
        } bits;
    } OSCR;
    union { 
        Uns32 value;
    } RBR_DLL;
    union { 
        Uns32 value;
    } THR_DLL;
    union { 
        Uns32 value;
        struct {
            Uns32 ERBI : 1;
            Uns32 ETHEI : 1;
            Uns32 ELSI : 1;
            Uns32 EMSI : 1;
        } bits;
    } IER_DLM;
    union { 
        Uns32 value;
        struct {
            Uns32 INTRID : 4;
            Uns32 __pad4 : 2;
            Uns32 FIFOED : 2;
        } bits;
    } IIR;
    union { 
        Uns32 value;
        struct {
            Uns32 FIFOE : 1;
            Uns32 RFIFORST : 1;
            Uns32 TFIFORST : 1;
            Uns32 DMAE : 1;
            Uns32 TFIFOT : 2;
            Uns32 RFIFOT : 2;
        } bits;
    } FCR;
    union { 
        Uns32 value;
        struct {
            Uns32 WLS : 2;
            Uns32 STB : 1;
            Uns32 PEN : 1;
            Uns32 EPS : 1;
            Uns32 SPS : 1;
            Uns32 BC : 1;
            Uns32 DLAB : 1;
        } bits;
    } LCR;
    union { 
        Uns32 value;
    } MCR;
    union { 
        Uns32 value;
        struct {
            Uns32 RDR : 1;
            Uns32 OE : 1;
            Uns32 PE : 1;
            Uns32 FE : 1;
            Uns32 LBreak : 1;
            Uns32 THRE : 1;
            Uns32 TEMT : 1;
            Uns32 ERRF : 1;
        } bits;
    } LSR;
    union { 
        Uns32 value;
    } MSR;
    union { 
        Uns32 value;
    } SCR;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          reset;
    ppmNetHandle          intOut;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NBYTE_READ_CB(defaultMemRead);

PPM_NBYTE_WRITE_CB(defaultMemWrite);

PPM_REG_READ_CB(rdIER_DLM);
PPM_REG_READ_CB(rdIIR);
PPM_REG_READ_CB(rdLSR);
PPM_REG_READ_CB(rdRBR_DLL);
PPM_NET_CB(resetCB);
PPM_REG_WRITE_CB(wrFCR);
PPM_REG_WRITE_CB(wrIER_DLM);
PPM_REG_WRITE_CB(wrLCR);
PPM_REG_WRITE_CB(wrTHR_DLL);
PPM_NET_CB(reset_reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_IDREV_WIDTH           32
#define BPORT1_AB_CFG_WIDTH             32
#define BPORT1_AB_OSCR_WRMASK           0x1f
#define BPORT1_AB_OSCR_WRNMASK          (0xffffffe0)
#define BPORT1_AB_OSCR_WIDTH            32
#define BPORT1_AB_RBR_DLL_WIDTH         32
#define BPORT1_AB_THR_DLL_WIDTH         32
#define BPORT1_AB_IER_DLM_WIDTH         32
#define BPORT1_AB_IIR_WIDTH             32
#define BPORT1_AB_FCR_WIDTH             32
#define BPORT1_AB_LCR_WIDTH             32
#define BPORT1_AB_MCR_WIDTH             32
#define BPORT1_AB_LSR_WIDTH             32
#define BPORT1_AB_MSR_WIDTH             32
#define BPORT1_AB_SCR_WRMASK            0xff
#define BPORT1_AB_SCR_WRNMASK           (0xffffff00)
#define BPORT1_AB_SCR_WIDTH             32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
