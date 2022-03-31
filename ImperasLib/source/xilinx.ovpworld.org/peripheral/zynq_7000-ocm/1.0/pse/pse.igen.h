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
            Uns32 PCD : 1;
            Uns32 RR : 1;
            Uns32 SP : 1;
            Uns32 MP : 1;
            Uns32 LF : 1;
            Uns32 OP : 15;
        } bits;
    } OCM_PARITY_CTRL;
    union { 
        Uns32 value;
        struct {
            Uns32 PEA : 14;
        } bits;
    } OCM_PARITY_ERRADDRESS;
    union { 
        Uns32 value;
        struct {
            Uns32 SP : 1;
            Uns32 MP : 1;
            Uns32 LF : 1;
        } bits;
    } OCM_IRQ_STS;
    union { 
        Uns32 value;
        struct {
            Uns32 ScuWrPri : 1;
            Uns32 __pad1 : 1;
            Uns32 ArbShare : 1;
        } bits;
    } OCM_CONTROL;
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

#define BPORT1_AB_OCM_PARITY_CTRL_WRMASK  0x3fffff
#define BPORT1_AB_OCM_PARITY_CTRL_WRNMASK  (0xffc00000)
#define BPORT1_AB_OCM_PARITY_CTRL_WIDTH  32
#define BPORT1_AB_OCM_PARITY_ERRADDRESS_WRMASK  0x7fff
#define BPORT1_AB_OCM_PARITY_ERRADDRESS_WRNMASK  (0xffff8000)
#define BPORT1_AB_OCM_PARITY_ERRADDRESS_WIDTH  32
#define BPORT1_AB_OCM_IRQ_STS_WRMASK    0x7
#define BPORT1_AB_OCM_IRQ_STS_WRNMASK   (0xfffffff8)
#define BPORT1_AB_OCM_IRQ_STS_WIDTH     32
#define BPORT1_AB_OCM_CONTROL_WRMASK    0x7
#define BPORT1_AB_OCM_CONTROL_WRNMASK   (0xfffffff8)
#define BPORT1_AB_OCM_CONTROL_WIDTH     32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
