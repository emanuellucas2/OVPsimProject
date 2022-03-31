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
            Uns32 EN : 1;
            Uns32 ENMOD : 1;
            Uns32 DBGEN : 1;
            Uns32 QAITEN : 1;
            Uns32 DOZEEN : 1;
            Uns32 STOPEN : 1;
            Uns32 CLKSRC : 3;
            Uns32 FRR : 1;
            Uns32 EN_24M : 1;
            Uns32 __pad11 : 4;
            Uns32 SWR : 1;
            Uns32 IM1 : 2;
            Uns32 IM2 : 2;
            Uns32 OM1 : 3;
            Uns32 OM2 : 3;
            Uns32 OM3 : 3;
            Uns32 FO1 : 1;
            Uns32 FO2 : 1;
            Uns32 FO3 : 1;
        } bits;
    } GPT_CR;
    union { 
        Uns32 value;
        struct {
            Uns32 PRESCALER : 12;
            Uns32 PRESCALER24M : 4;
        } bits;
    } GPT_PR;
    union { 
        Uns32 value;
        struct {
            Uns32 OF1 : 1;
            Uns32 OF2 : 1;
            Uns32 OF3 : 1;
            Uns32 IF1 : 1;
            Uns32 IF2 : 1;
            Uns32 ROV : 1;
        } bits;
    } GPT_SR;
    union { 
        Uns32 value;
        struct {
            Uns32 OF1IE : 1;
            Uns32 OF2IE : 1;
            Uns32 OF3IE : 1;
            Uns32 IF1IE : 1;
            Uns32 IF2IE : 1;
            Uns32 ROVIE : 1;
        } bits;
    } GPT_IR;
    union { 
        Uns32 value;
    } GPT_OCR1;
    union { 
        Uns32 value;
    } GPT_OCR2;
    union { 
        Uns32 value;
    } GPT_OCR3;
    union { 
        Uns32 value;
    } GPT_ICR1;
    union { 
        Uns32 value;
    } GPT_ICR2;
    union { 
        Uns32 value;
    } GPT_CNT;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          interrupt;
    ppmNetHandle          capture1;
    ppmNetHandle          capture2;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(ReadGPT_CNT);
PPM_REG_WRITE_CB(WriteGPT_CR);
PPM_REG_WRITE_CB(WriteGPT_IR);
PPM_REG_WRITE_CB(WriteGPT_OCR1);
PPM_REG_WRITE_CB(WriteGPT_OCR2);
PPM_REG_WRITE_CB(WriteGPT_OCR3);
PPM_REG_WRITE_CB(WriteGPT_PR);
PPM_REG_WRITE_CB(WriteGPT_SR);
PPM_NET_CB(inputCapure);
PPM_READ_CB(regNoDefinitionRead);
PPM_WRITE_CB(regNoDefinitionWrite);
PPM_NET_CB(reset_resetNet);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


///////////////////////////////// Local memory /////////////////////////////////

// To access local memory bport1/ab/buffer : (for example)
// char value = ((char*)handles.bport1)[BPORT1_AB_BUFFER_OFFSET + myAddress];

#define BPORT1_AB_BUFFER_OFFSET         0x0
#define BPORT1_AB_BUFFER_SIZE           0x1000

////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_GPT_CR_WRMASK         0xffff87ff
#define BPORT1_AB_GPT_CR_WRNMASK        (0x7800)
#define BPORT1_AB_GPT_CR_WIDTH          32
#define BPORT1_AB_GPT_PR_WRMASK         0xffff
#define BPORT1_AB_GPT_PR_WRNMASK        (0xffff0000)
#define BPORT1_AB_GPT_PR_WIDTH          32
#define BPORT1_AB_GPT_SR_WRMASK         0x3f
#define BPORT1_AB_GPT_SR_WRNMASK        (0xffffffc0)
#define BPORT1_AB_GPT_SR_WIDTH          32
#define BPORT1_AB_GPT_IR_WRMASK         0x3f
#define BPORT1_AB_GPT_IR_WRNMASK        (0xffffffc0)
#define BPORT1_AB_GPT_IR_WIDTH          32
#define BPORT1_AB_GPT_OCR1_WIDTH        32
#define BPORT1_AB_GPT_OCR2_WIDTH        32
#define BPORT1_AB_GPT_OCR3_WIDTH        32
#define BPORT1_AB_GPT_ICR1_WIDTH        32
#define BPORT1_AB_GPT_ICR2_WIDTH        32
#define BPORT1_AB_GPT_CNT_WIDTH         32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
