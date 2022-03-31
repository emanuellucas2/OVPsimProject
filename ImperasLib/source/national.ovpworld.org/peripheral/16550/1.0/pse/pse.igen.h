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
    } rbr_dll;
    union { 
        Uns8 value;
    } thr_dll;
    union { 
        Uns8 value;
        struct {
            Uns8 erbfi : 1;
            Uns8 etbei : 1;
            Uns8 elsi : 1;
            Uns8 edssi : 1;
        } bits;
    } ier_dlh;
    union { 
        Uns8 value;
        struct {
            Uns8 intid : 4;
            Uns8 __pad4 : 2;
            Uns8 fifoen : 2;
        } bits;
    } iir;
    union { 
        Uns8 value;
        struct {
            Uns8 fifoEn : 1;
            Uns8 fifoRcvrRst : 1;
            Uns8 fifoXmitRst : 1;
            Uns8 dmaModeSel : 1;
            Uns8 fifoXmitTrig : 2;
            Uns8 fifoRcvrTrig : 2;
        } bits;
    } fcr;
    union { 
        Uns8 value;
        struct {
            Uns8 dls : 2;
            Uns8 stop : 1;
            Uns8 pen : 1;
            Uns8 eps : 1;
            Uns8 stick : 1;
            Uns8 brk : 1;
            Uns8 dlab : 1;
        } bits;
    } lcr;
    union { 
        Uns8 value;
    } mcr;
    union { 
        Uns8 value;
        struct {
            Uns8 dr : 1;
            Uns8 oe : 1;
            Uns8 pe : 1;
            Uns8 fe : 1;
            Uns8 bi : 1;
            Uns8 thre : 1;
            Uns8 temt : 1;
            Uns8 rfe : 1;
        } bits;
    } lsr;
    union { 
        Uns8 value;
    } msr;
    union { 
        Uns8 value;
    } scr;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          reset_uart;
    ppmNetHandle          intOut;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(readIER_DLH);
PPM_REG_READ_CB(readIIR);
PPM_REG_READ_CB(readLSR);
PPM_REG_READ_CB(readRBR_DLL);
PPM_NET_CB(resetCB);
PPM_REG_VIEW_CB(viewIER_DLH);
PPM_REG_VIEW_CB(viewIIR);
PPM_REG_VIEW_CB(viewLSR);
PPM_REG_VIEW_CB(viewRBR_DLL);
PPM_REG_VIEW_CB(viewTHR_DLL);
PPM_REG_WRITE_CB(writeFCR);
PPM_REG_WRITE_CB(writeIER_DLH);
PPM_REG_WRITE_CB(writeLCR);
PPM_REG_WRITE_CB(writeTHR_DLL);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_RBR_DLL_WIDTH         8
#define BPORT1_AB_THR_DLL_WIDTH         8
#define BPORT1_AB_IER_DLH_WIDTH         8
#define BPORT1_AB_IIR_WIDTH             8
#define BPORT1_AB_FCR_WIDTH             8
#define BPORT1_AB_LCR_WIDTH             8
#define BPORT1_AB_MCR_WRMASK            0x1f
#define BPORT1_AB_MCR_WRNMASK           (0xe0)
#define BPORT1_AB_MCR_WIDTH             8
#define BPORT1_AB_LSR_WIDTH             8
#define BPORT1_AB_MSR_WIDTH             8
#define BPORT1_AB_SCR_WIDTH             8

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
