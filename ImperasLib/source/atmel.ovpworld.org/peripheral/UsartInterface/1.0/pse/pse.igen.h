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

typedef struct apb_REG_dataS { 
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 2;
            Uns32 RSTRX : 1;
            Uns32 RSTTX : 1;
            Uns32 RXEN : 1;
            Uns32 RXDIS : 1;
            Uns32 TXEN : 1;
            Uns32 TXDIS : 1;
            Uns32 RSTSTA : 1;
            Uns32 STTBRK : 1;
            Uns32 STPBRK : 1;
            Uns32 STTTO : 1;
            Uns32 SENDA : 1;
        } bits;
    } US_CR;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 4;
            Uns32 HSCLKS : 2;
            Uns32 CHRL : 2;
            Uns32 SYNC : 1;
            Uns32 PAR : 3;
            Uns32 NBSTOP : 2;
            Uns32 CHMODE : 2;
            Uns32 __pad16 : 1;
            Uns32 MODE9 : 1;
            Uns32 CLKO : 1;
        } bits;
    } US_MR;
    union { 
        Uns32 value;
        struct {
            Uns32 RXRDY : 1;
            Uns32 TXRDY : 1;
            Uns32 RXBRK : 1;
            Uns32 ENDRX : 1;
            Uns32 ENDTX : 1;
            Uns32 OVRE : 1;
            Uns32 FRAME : 1;
            Uns32 PARE : 1;
            Uns32 TIMEOUT : 1;
            Uns32 TXEMPTY : 1;
        } bits;
    } US_IER;
    union { 
        Uns32 value;
        struct {
            Uns32 RXRDY : 1;
            Uns32 TXRDY : 1;
            Uns32 RXBRK : 1;
            Uns32 ENDRX : 1;
            Uns32 ENDTX : 1;
            Uns32 OVRE : 1;
            Uns32 FRAME : 1;
            Uns32 PARE : 1;
            Uns32 TIMEOUT : 1;
            Uns32 TXEMPTY : 1;
        } bits;
    } US_IDR;
    union { 
        Uns32 value;
        struct {
            Uns32 RXRDY : 1;
            Uns32 TXRDY : 1;
            Uns32 RXBRK : 1;
            Uns32 ENDRX : 1;
            Uns32 ENDTX : 1;
            Uns32 OVRE : 1;
            Uns32 FRAME : 1;
            Uns32 PARE : 1;
            Uns32 TIMEOUT : 1;
            Uns32 TXEMPTY : 1;
        } bits;
    } US_IMR;
    union { 
        Uns32 value;
        struct {
            Uns32 RXRDY : 1;
            Uns32 TXRDY : 1;
            Uns32 RXBRK : 1;
            Uns32 ENDRX : 1;
            Uns32 ENDTX : 1;
            Uns32 OVRE : 1;
            Uns32 FRAME : 1;
            Uns32 PARE : 1;
            Uns32 TIMEOUT : 1;
            Uns32 TXEMPTY : 1;
        } bits;
    } US_CSR;
    union { 
        Uns32 value;
        struct {
            Uns32 RXCHR : 8;
        } bits;
    } US_RHR;
    union { 
        Uns32 value;
        struct {
            Uns32 TXCHR : 8;
        } bits;
    } US_THR;
    union { 
        Uns32 value;
        struct {
            Uns32 CD : 16;
        } bits;
    } US_BRGR;
    union { 
        Uns32 value;
        struct {
            Uns32 TO : 8;
        } bits;
    } US_RTOR;
    union { 
        Uns32 value;
        struct {
            Uns32 TG : 8;
        } bits;
    } US_TTGR;
    union { 
        Uns32 value;
        struct {
            Uns32 RXPTR : 32;
        } bits;
    } US_RPR;
    union { 
        Uns32 value;
        struct {
            Uns32 RXCTR : 16;
        } bits;
    } US_RCR;
    union { 
        Uns32 value;
        struct {
            Uns32 TXPTR : 32;
        } bits;
    } US_TPR;
    union { 
        Uns32 value;
        struct {
            Uns32 TXCTR : 16;
        } bits;
    } US_TCR;
} apb_REG_dataT, *apb_REG_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern apb_REG_dataT apb_REG_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    ppmAddressSpaceHandle asb;
    void                 *apb;
    ppmNetHandle          IRQ;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_WRITE_CB(US_BRGR_wcb);
PPM_REG_WRITE_CB(US_CR_wcb);
PPM_REG_WRITE_CB(US_IDR_wcb);
PPM_REG_WRITE_CB(US_IER_wcb);
PPM_REG_WRITE_CB(US_MR_wcb);
PPM_REG_WRITE_CB(US_RCR_wcb);
PPM_REG_READ_CB(US_RHR_rcb);
PPM_REG_WRITE_CB(US_RPR_wcb);
PPM_REG_WRITE_CB(US_RTOR_wcb);
PPM_REG_WRITE_CB(US_TCR_wcb);
PPM_REG_WRITE_CB(US_THR_wcb);
PPM_REG_WRITE_CB(US_TPR_wcb);
PPM_REG_WRITE_CB(US_TTGR_wcb);
PPM_NET_CB(reset_resetNet);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define APB_REG_US_CR_WIDTH             32
#define APB_REG_US_MR_WIDTH             32
#define APB_REG_US_IER_WIDTH            32
#define APB_REG_US_IDR_WIDTH            32
#define APB_REG_US_IMR_WIDTH            32
#define APB_REG_US_CSR_WIDTH            32
#define APB_REG_US_RHR_WIDTH            32
#define APB_REG_US_THR_WIDTH            32
#define APB_REG_US_BRGR_WIDTH           32
#define APB_REG_US_RTOR_WIDTH           32
#define APB_REG_US_TTGR_WIDTH           32
#define APB_REG_US_RPR_WIDTH            32
#define APB_REG_US_RCR_WIDTH            32
#define APB_REG_US_TPR_WIDTH            32
#define APB_REG_US_TCR_WIDTH            32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
