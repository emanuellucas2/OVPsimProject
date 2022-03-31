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
    } SRR;
    union { 
        Uns32 value;
    } MSR;
    union { 
        Uns32 value;
    } BRPR;
    union { 
        Uns32 value;
    } BTR;
    union { 
        Uns32 value;
    } ECR;
    union { 
        Uns32 value;
    } ESR;
    union { 
        Uns32 value;
    } SR;
    union { 
        Uns32 value;
    } ISR;
    union { 
        Uns32 value;
    } IER;
    union { 
        Uns32 value;
    } ICR;
    union { 
        Uns32 value;
    } TCR;
    union { 
        Uns32 value;
    } WIR;
    union { 
        Uns32 value;
    } TXFIFO_ID;
    union { 
        Uns32 value;
    } TXFIFO_DLC;
    union { 
        Uns32 value;
    } TXFIFO_DATA1;
    union { 
        Uns32 value;
    } TXFIFO_DATA2;
    union { 
        Uns32 value;
    } TXHPB_ID;
    union { 
        Uns32 value;
    } TXHPB_DLC;
    union { 
        Uns32 value;
    } TXHPB_DATA1;
    union { 
        Uns32 value;
    } TXHPB_DATA2;
    union { 
        Uns32 value;
    } RXFIFO_ID;
    union { 
        Uns32 value;
    } RXFIFO_DLC;
    union { 
        Uns32 value;
    } RXFIFO_DATA1;
    union { 
        Uns32 value;
    } RXFIFO_DATA2;
    union { 
        Uns32 value;
    } AFR;
    union { 
        Uns32 value;
    } AFMR1;
    union { 
        Uns32 value;
    } AFIR1;
    union { 
        Uns32 value;
    } AFMR2;
    union { 
        Uns32 value;
    } AFIR2;
    union { 
        Uns32 value;
    } AFMR3;
    union { 
        Uns32 value;
    } AFIR3;
    union { 
        Uns32 value;
    } AFMR4;
    union { 
        Uns32 value;
    } AFIR4;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          intOut;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(rxFIFOId);
PPM_REG_WRITE_CB(wrFIFOId);
PPM_REG_WRITE_CB(wrHPBId);
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

#define BPORT1_AB_SRR_WRMASK            0x3
#define BPORT1_AB_SRR_WRNMASK           (0xfffffffc)
#define BPORT1_AB_SRR_WIDTH             32
#define BPORT1_AB_MSR_WRMASK            0x7
#define BPORT1_AB_MSR_WRNMASK           (0xfffffff8)
#define BPORT1_AB_MSR_WIDTH             32
#define BPORT1_AB_BRPR_WRMASK           0xff
#define BPORT1_AB_BRPR_WRNMASK          (0xffffff00)
#define BPORT1_AB_BRPR_WIDTH            32
#define BPORT1_AB_BTR_WRMASK            0x1ff
#define BPORT1_AB_BTR_WRNMASK           (0xfffffe00)
#define BPORT1_AB_BTR_WIDTH             32
#define BPORT1_AB_ECR_WIDTH             32
#define BPORT1_AB_ESR_WRMASK            0x1f
#define BPORT1_AB_ESR_WRNMASK           (0xffffffe0)
#define BPORT1_AB_ESR_WIDTH             32
#define BPORT1_AB_SR_WRMASK             0xfff
#define BPORT1_AB_SR_WRNMASK            (0xfffff000)
#define BPORT1_AB_SR_WIDTH              32
#define BPORT1_AB_ISR_WRMASK            0x7fff
#define BPORT1_AB_ISR_WRNMASK           (0xffff8000)
#define BPORT1_AB_ISR_WIDTH             32
#define BPORT1_AB_IER_WRMASK            0x7fff
#define BPORT1_AB_IER_WRNMASK           (0xffff8000)
#define BPORT1_AB_IER_WIDTH             32
#define BPORT1_AB_ICR_WRMASK            0x7fff
#define BPORT1_AB_ICR_WRNMASK           (0xffff8000)
#define BPORT1_AB_ICR_WIDTH             32
#define BPORT1_AB_TCR_WRMASK            0x1
#define BPORT1_AB_TCR_WRNMASK           (0xfffffffe)
#define BPORT1_AB_TCR_WIDTH             32
#define BPORT1_AB_WIR_WRMASK            0xffff
#define BPORT1_AB_WIR_WRNMASK           (0xffff0000)
#define BPORT1_AB_WIR_WIDTH             32
#define BPORT1_AB_TXFIFO_ID_WIDTH       32
#define BPORT1_AB_TXFIFO_DLC_WIDTH      32
#define BPORT1_AB_TXFIFO_DATA1_WIDTH    32
#define BPORT1_AB_TXFIFO_DATA2_WIDTH    32
#define BPORT1_AB_TXHPB_ID_WIDTH        32
#define BPORT1_AB_TXHPB_DLC_WIDTH       32
#define BPORT1_AB_TXHPB_DATA1_WIDTH     32
#define BPORT1_AB_TXHPB_DATA2_WIDTH     32
#define BPORT1_AB_RXFIFO_ID_WIDTH       32
#define BPORT1_AB_RXFIFO_DLC_WRMASK     0xf000ffff
#define BPORT1_AB_RXFIFO_DLC_WRNMASK    (0xfff0000)
#define BPORT1_AB_RXFIFO_DLC_WIDTH      32
#define BPORT1_AB_RXFIFO_DATA1_WIDTH    32
#define BPORT1_AB_RXFIFO_DATA2_WIDTH    32
#define BPORT1_AB_AFR_WRMASK            0x7
#define BPORT1_AB_AFR_WRNMASK           (0xfffffff8)
#define BPORT1_AB_AFR_WIDTH             32
#define BPORT1_AB_AFMR1_WIDTH           32
#define BPORT1_AB_AFIR1_WIDTH           32
#define BPORT1_AB_AFMR2_WIDTH           32
#define BPORT1_AB_AFIR2_WIDTH           32
#define BPORT1_AB_AFMR3_WIDTH           32
#define BPORT1_AB_AFIR3_WIDTH           32
#define BPORT1_AB_AFMR4_WIDTH           32
#define BPORT1_AB_AFIR4_WIDTH           32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
