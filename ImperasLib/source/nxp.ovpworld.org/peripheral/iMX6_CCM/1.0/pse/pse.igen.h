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
    } CCM_CCR;
    union { 
        Uns32 value;
    } CCM_CCDR;
    union { 
        Uns32 value;
    } CCM_CSR;
    union { 
        Uns32 value;
    } CCM_CCSR;
    union { 
        Uns32 value;
    } CCM_CACRR;
    union { 
        Uns32 value;
    } CCM_CBCDR;
    union { 
        Uns32 value;
    } CCM_CBCMR;
    union { 
        Uns32 value;
    } CCM_CSCMR1;
    union { 
        Uns32 value;
    } CCM_CSCMR2;
    union { 
        Uns32 value;
    } CCM_CSCDR1;
    union { 
        Uns32 value;
    } CCM_CS1CDR;
    union { 
        Uns32 value;
    } CCM_CS2CDR;
    union { 
        Uns32 value;
    } CCM_CDCDR;
    union { 
        Uns32 value;
    } CCM_CHSCCDR;
    union { 
        Uns32 value;
    } CCM_CSCDR2;
    union { 
        Uns32 value;
    } CCM_CSCDR3;
    union { 
        Uns32 value;
    } CCM_CDHIPR;
    union { 
        Uns32 value;
    } CCM_CLPCR;
    union { 
        Uns32 value;
    } CCM_CISR;
    union { 
        Uns32 value;
    } CCM_CIMR;
    union { 
        Uns32 value;
    } CCM_CCOSR;
    union { 
        Uns32 value;
    } CCM_CGPR;
    union { 
        Uns32 value;
    } CCM_CCGR0;
    union { 
        Uns32 value;
    } CCM_CCGR1;
    union { 
        Uns32 value;
    } CCM_CCGR2;
    union { 
        Uns32 value;
    } CCM_CCGR3;
    union { 
        Uns32 value;
    } CCM_CCGR4;
    union { 
        Uns32 value;
    } CCM_CCGR5;
    union { 
        Uns32 value;
    } CCM_CCGR6;
    union { 
        Uns32 value;
    } CCM_CMEOR;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

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

#define BPORT1_AB_CCM_CCR_WIDTH         32
#define BPORT1_AB_CCM_CCDR_WIDTH        32
#define BPORT1_AB_CCM_CSR_WIDTH         32
#define BPORT1_AB_CCM_CCSR_WIDTH        32
#define BPORT1_AB_CCM_CACRR_WIDTH       32
#define BPORT1_AB_CCM_CBCDR_WIDTH       32
#define BPORT1_AB_CCM_CBCMR_WIDTH       32
#define BPORT1_AB_CCM_CSCMR1_WIDTH      32
#define BPORT1_AB_CCM_CSCMR2_WIDTH      32
#define BPORT1_AB_CCM_CSCDR1_WIDTH      32
#define BPORT1_AB_CCM_CS1CDR_WIDTH      32
#define BPORT1_AB_CCM_CS2CDR_WIDTH      32
#define BPORT1_AB_CCM_CDCDR_WIDTH       32
#define BPORT1_AB_CCM_CHSCCDR_WIDTH     32
#define BPORT1_AB_CCM_CSCDR2_WIDTH      32
#define BPORT1_AB_CCM_CSCDR3_WIDTH      32
#define BPORT1_AB_CCM_CDHIPR_WIDTH      32
#define BPORT1_AB_CCM_CLPCR_WIDTH       32
#define BPORT1_AB_CCM_CISR_WIDTH        32
#define BPORT1_AB_CCM_CIMR_WIDTH        32
#define BPORT1_AB_CCM_CCOSR_WIDTH       32
#define BPORT1_AB_CCM_CGPR_WIDTH        32
#define BPORT1_AB_CCM_CCGR0_WIDTH       32
#define BPORT1_AB_CCM_CCGR1_WIDTH       32
#define BPORT1_AB_CCM_CCGR2_WIDTH       32
#define BPORT1_AB_CCM_CCGR3_WIDTH       32
#define BPORT1_AB_CCM_CCGR4_WIDTH       32
#define BPORT1_AB_CCM_CCGR5_WIDTH       32
#define BPORT1_AB_CCM_CCGR6_WIDTH       32
#define BPORT1_AB_CCM_CMEOR_WIDTH       32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
