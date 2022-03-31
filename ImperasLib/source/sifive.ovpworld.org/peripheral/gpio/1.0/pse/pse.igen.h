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

typedef struct bport1_REG_dataS { 
    union { 
        Uns32 value;
    } VALUE;
    union { 
        Uns32 value;
    } INPUT_EN;
    union { 
        Uns32 value;
    } OUTPUT_EN;
    union { 
        Uns32 value;
    } PORT;
    union { 
        Uns32 value;
    } PUE;
    union { 
        Uns32 value;
    } DS;
    union { 
        Uns32 value;
    } RISE_IE;
    union { 
        Uns32 value;
    } RISE_IP;
    union { 
        Uns32 value;
    } FALL_IE;
    union { 
        Uns32 value;
    } FALL_IP;
    union { 
        Uns32 value;
    } HIGH_IE;
    union { 
        Uns32 value;
    } HIGH_IP;
    union { 
        Uns32 value;
    } LOW_IE;
    union { 
        Uns32 value;
    } LOW_IP;
    union { 
        Uns32 value;
    } IOF_EN;
    union { 
        Uns32 value;
    } IOF_SEL;
    union { 
        Uns32 value;
    } OUT_XOR;
} bport1_REG_dataT, *bport1_REG_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_REG_dataT bport1_REG_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          resetNet;
    ppmNetHandle          intOut0;
    ppmNetHandle          intOut1;
    ppmNetHandle          intOut2;
    ppmNetHandle          intOut3;
    ppmNetHandle          intOut4;
    ppmNetHandle          intOut5;
    ppmNetHandle          intOut6;
    ppmNetHandle          intOut7;
    ppmNetHandle          intOut8;
    ppmNetHandle          intOut9;
    ppmNetHandle          intOut10;
    ppmNetHandle          intOut11;
    ppmNetHandle          intOut12;
    ppmNetHandle          intOut13;
    ppmNetHandle          intOut14;
    ppmNetHandle          intOut15;
    ppmNetHandle          gpios0;
    ppmNetHandle          gpios1;
    ppmNetHandle          gpios2;
    ppmNetHandle          gpios3;
    ppmNetHandle          gpios4;
    ppmNetHandle          gpios5;
    ppmNetHandle          gpios6;
    ppmNetHandle          gpios7;
    ppmNetHandle          gpios8;
    ppmNetHandle          gpios9;
    ppmNetHandle          gpios10;
    ppmNetHandle          gpios11;
    ppmNetHandle          gpios12;
    ppmNetHandle          gpios13;
    ppmNetHandle          gpios14;
    ppmNetHandle          gpios15;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NBYTE_READ_CB(defaultMemRead);

PPM_NBYTE_WRITE_CB(defaultMemWrite);

PPM_NET_CB(gpioInCB);
PPM_NET_CB(resetCB);
PPM_REG_WRITE_CB(wrFIE);
PPM_REG_WRITE_CB(wrHIE);
PPM_REG_WRITE_CB(wrInputEn);
PPM_REG_WRITE_CB(wrLIE);
PPM_REG_WRITE_CB(wrOutputEn);
PPM_REG_WRITE_CB(wrPort);
PPM_REG_WRITE_CB(wrRIE);
PPM_NET_CB(reset_resetNet);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_REG_VALUE_WIDTH          32
#define BPORT1_REG_INPUT_EN_WIDTH       32
#define BPORT1_REG_OUTPUT_EN_WIDTH      32
#define BPORT1_REG_PORT_WIDTH           32
#define BPORT1_REG_PUE_WIDTH            32
#define BPORT1_REG_DS_WIDTH             32
#define BPORT1_REG_RISE_IE_WIDTH        32
#define BPORT1_REG_RISE_IP_WIDTH        32
#define BPORT1_REG_FALL_IE_WIDTH        32
#define BPORT1_REG_FALL_IP_WIDTH        32
#define BPORT1_REG_HIGH_IE_WIDTH        32
#define BPORT1_REG_HIGH_IP_WIDTH        32
#define BPORT1_REG_LOW_IE_WIDTH         32
#define BPORT1_REG_LOW_IP_WIDTH         32
#define BPORT1_REG_IOF_EN_WIDTH         32
#define BPORT1_REG_IOF_SEL_WIDTH        32
#define BPORT1_REG_OUT_XOR_WIDTH        32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
