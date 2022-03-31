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

typedef struct plb_REG_dataS { 
    union { 
        Uns32 value;
        struct {
            Uns32 INT0 : 1;
            Uns32 INT1 : 1;
            Uns32 INT2 : 1;
            Uns32 INT3 : 1;
            Uns32 INT4 : 1;
            Uns32 INT5 : 1;
            Uns32 INT6 : 1;
            Uns32 INT7 : 1;
            Uns32 INT8 : 1;
            Uns32 INT9 : 1;
            Uns32 INT10 : 1;
            Uns32 INT11 : 1;
            Uns32 INT12 : 1;
            Uns32 INT13 : 1;
            Uns32 INT14 : 1;
            Uns32 INT15 : 1;
            Uns32 INT16 : 1;
            Uns32 INT17 : 1;
            Uns32 INT18 : 1;
            Uns32 INT19 : 1;
            Uns32 INT20 : 1;
            Uns32 INT21 : 1;
            Uns32 INT22 : 1;
            Uns32 INT23 : 1;
            Uns32 INT24 : 1;
            Uns32 INT25 : 1;
            Uns32 INT26 : 1;
            Uns32 INT27 : 1;
            Uns32 INT28 : 1;
            Uns32 INT29 : 1;
            Uns32 INT30 : 1;
            Uns32 INT31 : 1;
        } bits;
    } ISR;
    union { 
        Uns32 value;
        struct {
            Uns32 INT0 : 1;
            Uns32 INT1 : 1;
            Uns32 INT2 : 1;
            Uns32 INT3 : 1;
            Uns32 INT4 : 1;
            Uns32 INT5 : 1;
            Uns32 INT6 : 1;
            Uns32 INT7 : 1;
            Uns32 INT8 : 1;
            Uns32 INT9 : 1;
            Uns32 INT10 : 1;
            Uns32 INT11 : 1;
            Uns32 INT12 : 1;
            Uns32 INT13 : 1;
            Uns32 INT14 : 1;
            Uns32 INT15 : 1;
            Uns32 INT16 : 1;
            Uns32 INT17 : 1;
            Uns32 INT18 : 1;
            Uns32 INT19 : 1;
            Uns32 INT20 : 1;
            Uns32 INT21 : 1;
            Uns32 INT22 : 1;
            Uns32 INT23 : 1;
            Uns32 INT24 : 1;
            Uns32 INT25 : 1;
            Uns32 INT26 : 1;
            Uns32 INT27 : 1;
            Uns32 INT28 : 1;
            Uns32 INT29 : 1;
            Uns32 INT30 : 1;
            Uns32 INT31 : 1;
        } bits;
    } IPR;
    union { 
        Uns32 value;
        struct {
            Uns32 INT0 : 1;
            Uns32 INT1 : 1;
            Uns32 INT2 : 1;
            Uns32 INT3 : 1;
            Uns32 INT4 : 1;
            Uns32 INT5 : 1;
            Uns32 INT6 : 1;
            Uns32 INT7 : 1;
            Uns32 INT8 : 1;
            Uns32 INT9 : 1;
            Uns32 INT10 : 1;
            Uns32 INT11 : 1;
            Uns32 INT12 : 1;
            Uns32 INT13 : 1;
            Uns32 INT14 : 1;
            Uns32 INT15 : 1;
            Uns32 INT16 : 1;
            Uns32 INT17 : 1;
            Uns32 INT18 : 1;
            Uns32 INT19 : 1;
            Uns32 INT20 : 1;
            Uns32 INT21 : 1;
            Uns32 INT22 : 1;
            Uns32 INT23 : 1;
            Uns32 INT24 : 1;
            Uns32 INT25 : 1;
            Uns32 INT26 : 1;
            Uns32 INT27 : 1;
            Uns32 INT28 : 1;
            Uns32 INT29 : 1;
            Uns32 INT30 : 1;
            Uns32 INT31 : 1;
        } bits;
    } IER;
    union { 
        Uns32 value;
        struct {
            Uns32 INT0 : 1;
            Uns32 INT1 : 1;
            Uns32 INT2 : 1;
            Uns32 INT3 : 1;
            Uns32 INT4 : 1;
            Uns32 INT5 : 1;
            Uns32 INT6 : 1;
            Uns32 INT7 : 1;
            Uns32 INT8 : 1;
            Uns32 INT9 : 1;
            Uns32 INT10 : 1;
            Uns32 INT11 : 1;
            Uns32 INT12 : 1;
            Uns32 INT13 : 1;
            Uns32 INT14 : 1;
            Uns32 INT15 : 1;
            Uns32 INT16 : 1;
            Uns32 INT17 : 1;
            Uns32 INT18 : 1;
            Uns32 INT19 : 1;
            Uns32 INT20 : 1;
            Uns32 INT21 : 1;
            Uns32 INT22 : 1;
            Uns32 INT23 : 1;
            Uns32 INT24 : 1;
            Uns32 INT25 : 1;
            Uns32 INT26 : 1;
            Uns32 INT27 : 1;
            Uns32 INT28 : 1;
            Uns32 INT29 : 1;
            Uns32 INT30 : 1;
            Uns32 INT31 : 1;
        } bits;
    } IAR;
    union { 
        Uns32 value;
        struct {
            Uns32 INT0 : 1;
            Uns32 INT1 : 1;
            Uns32 INT2 : 1;
            Uns32 INT3 : 1;
            Uns32 INT4 : 1;
            Uns32 INT5 : 1;
            Uns32 INT6 : 1;
            Uns32 INT7 : 1;
            Uns32 INT8 : 1;
            Uns32 INT9 : 1;
            Uns32 INT10 : 1;
            Uns32 INT11 : 1;
            Uns32 INT12 : 1;
            Uns32 INT13 : 1;
            Uns32 INT14 : 1;
            Uns32 INT15 : 1;
            Uns32 INT16 : 1;
            Uns32 INT17 : 1;
            Uns32 INT18 : 1;
            Uns32 INT19 : 1;
            Uns32 INT20 : 1;
            Uns32 INT21 : 1;
            Uns32 INT22 : 1;
            Uns32 INT23 : 1;
            Uns32 INT24 : 1;
            Uns32 INT25 : 1;
            Uns32 INT26 : 1;
            Uns32 INT27 : 1;
            Uns32 INT28 : 1;
            Uns32 INT29 : 1;
            Uns32 INT30 : 1;
            Uns32 INT31 : 1;
        } bits;
    } SIE;
    union { 
        Uns32 value;
        struct {
            Uns32 INT0 : 1;
            Uns32 INT1 : 1;
            Uns32 INT2 : 1;
            Uns32 INT3 : 1;
            Uns32 INT4 : 1;
            Uns32 INT5 : 1;
            Uns32 INT6 : 1;
            Uns32 INT7 : 1;
            Uns32 INT8 : 1;
            Uns32 INT9 : 1;
            Uns32 INT10 : 1;
            Uns32 INT11 : 1;
            Uns32 INT12 : 1;
            Uns32 INT13 : 1;
            Uns32 INT14 : 1;
            Uns32 INT15 : 1;
            Uns32 INT16 : 1;
            Uns32 INT17 : 1;
            Uns32 INT18 : 1;
            Uns32 INT19 : 1;
            Uns32 INT20 : 1;
            Uns32 INT21 : 1;
            Uns32 INT22 : 1;
            Uns32 INT23 : 1;
            Uns32 INT24 : 1;
            Uns32 INT25 : 1;
            Uns32 INT26 : 1;
            Uns32 INT27 : 1;
            Uns32 INT28 : 1;
            Uns32 INT29 : 1;
            Uns32 INT30 : 1;
            Uns32 INT31 : 1;
        } bits;
    } CIE;
    union { 
        Uns32 value;
    } IVR;
    union { 
        Uns32 value;
        struct {
            Uns32 ME : 1;
            Uns32 HIE : 1;
        } bits;
    } MER;
} plb_REG_dataT, *plb_REG_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern plb_REG_dataT plb_REG_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *plb;
    ppmNetHandle          Irq;
    ppmNetHandle          Intr[32];
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(ReadIER);
PPM_REG_READ_CB(ReadIPR);
PPM_REG_READ_CB(ReadISR);
PPM_REG_READ_CB(ReadIVR);
PPM_REG_READ_CB(ReadMER);
PPM_REG_WRITE_CB(WriteCIE);
PPM_REG_WRITE_CB(WriteIAR);
PPM_REG_WRITE_CB(WriteIER);
PPM_REG_WRITE_CB(WriteISR);
PPM_NET_CB(WriteIntr);
PPM_REG_WRITE_CB(WriteMER);
PPM_REG_WRITE_CB(WriteSIE);
PPM_NET_CB(reset_resetNet);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define PLB_REG_ISR_WIDTH               32
#define PLB_REG_IPR_WIDTH               32
#define PLB_REG_IER_WIDTH               32
#define PLB_REG_IAR_WIDTH               32
#define PLB_REG_SIE_WIDTH               32
#define PLB_REG_CIE_WIDTH               32
#define PLB_REG_IVR_WIDTH               32
#define PLB_REG_MER_WIDTH               32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
