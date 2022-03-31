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
        Uns8 value;
        struct {
            Uns8 HYSTCTR : 2;
            Uns8 __pad2 : 2;
            Uns8 FILTER_CNT : 3;
        } bits;
    } CR0;
    union { 
        Uns8 value;
        struct {
            Uns8 EN : 1;
            Uns8 OPE : 1;
            Uns8 COS : 1;
            Uns8 INV : 1;
            Uns8 PMODE : 1;
            Uns8 __pad5 : 1;
            Uns8 WE : 1;
            Uns8 SE : 1;
        } bits;
    } CR1;
    union { 
        Uns8 value;
        struct {
            Uns8 FILT_PER : 8;
        } bits;
    } FPR;
    union { 
        Uns8 value;
        struct {
            Uns8 COUT : 1;
            Uns8 CFF : 1;
            Uns8 CFR : 1;
            Uns8 IEF : 1;
            Uns8 IER : 1;
            Uns8 __pad5 : 1;
            Uns8 DMAEN : 1;
        } bits;
    } SCR;
    union { 
        Uns8 value;
        struct {
            Uns8 VOSEL : 6;
            Uns8 VRSEL : 1;
            Uns8 DACEN : 1;
        } bits;
    } DACCR;
    union { 
        Uns8 value;
        struct {
            Uns8 MSEL : 3;
            Uns8 PSEL : 3;
        } bits;
    } MUXCR;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          Reset;
    ppmNetHandle          ExtSample;
    ppmNetHandle          Vin1;
    ppmNetHandle          Vin2;
    ppmNetHandle          Input0;
    ppmNetHandle          Input1;
    ppmNetHandle          Input2;
    ppmNetHandle          Input3;
    ppmNetHandle          Input4;
    ppmNetHandle          Input5;
    ppmNetHandle          Input6;
    ppmNetHandle          Input7;
    ppmNetHandle          DacOutput;
    ppmNetHandle          CoutSoc;
    ppmNetHandle          Interrupt;
    ppmNetHandle          DmaReq;
    ppmNetHandle          CmpOPad;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(extSampleCB);
PPM_NET_CB(input0CB);
PPM_NET_CB(input1CB);
PPM_NET_CB(input2CB);
PPM_NET_CB(input3CB);
PPM_NET_CB(input4CB);
PPM_NET_CB(input5CB);
PPM_NET_CB(input6CB);
PPM_NET_CB(input7CB);
PPM_REG_WRITE_CB(writeCR1);
PPM_REG_WRITE_CB(writeDAC);
PPM_REG_WRITE_CB(writeMUX);
PPM_REG_WRITE_CB(writeSCR);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_CR0_WRMASK            0x73
#define BPORT1_AB_CR0_WRNMASK           (0x8c)
#define BPORT1_AB_CR0_WIDTH             8
#define BPORT1_AB_CR1_WRMASK            0xd7
#define BPORT1_AB_CR1_WRNMASK           (0x28)
#define BPORT1_AB_CR1_WIDTH             8
#define BPORT1_AB_FPR_WRMASK            0xff
#define BPORT1_AB_FPR_WRNMASK           (0x0)
#define BPORT1_AB_FPR_WIDTH             8
#define BPORT1_AB_SCR_WRMASK            0x5e
#define BPORT1_AB_SCR_WRNMASK           (0xa1)
#define BPORT1_AB_SCR_WIDTH             8
#define BPORT1_AB_DACCR_WRMASK          0xff
#define BPORT1_AB_DACCR_WRNMASK         (0x0)
#define BPORT1_AB_DACCR_WIDTH           8
#define BPORT1_AB_MUXCR_WRMASK          0x3f
#define BPORT1_AB_MUXCR_WRNMASK         (0xc0)
#define BPORT1_AB_MUXCR_WIDTH           8

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
