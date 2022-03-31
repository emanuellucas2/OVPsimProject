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

typedef struct bp1_REG_dataS { 
    union { 
        Uns32 value;
        struct {
            Uns32 CPU : 1;
        } bits;
    } PS_CR;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 2;
            Uns32 US0 : 1;
            Uns32 US1 : 1;
            Uns32 TC0 : 1;
            Uns32 TC1 : 1;
            Uns32 TC2 : 1;
            Uns32 __pad7 : 1;
            Uns32 PIO : 1;
        } bits;
    } PS_PCER;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 2;
            Uns32 US0 : 1;
            Uns32 US1 : 1;
            Uns32 TC0 : 1;
            Uns32 TC1 : 1;
            Uns32 TC2 : 1;
            Uns32 __pad7 : 1;
            Uns32 PIO : 1;
        } bits;
    } PS_PCDR;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 2;
            Uns32 US0 : 1;
            Uns32 US1 : 1;
            Uns32 TC0 : 1;
            Uns32 TC1 : 1;
            Uns32 TC2 : 1;
            Uns32 __pad7 : 1;
            Uns32 PIO : 1;
        } bits;
    } PS_PCSR;
} bp1_REG_dataT, *bp1_REG_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bp1_REG_dataT bp1_REG_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bp1;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_WRITE_CB(PS_CR_wcb);
PPM_REG_WRITE_CB(PS_PCDR_wcb);
PPM_REG_WRITE_CB(PS_PCER_wcb);
PPM_NET_CB(reset_resetNet);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BP1_REG_PS_CR_WIDTH             32
#define BP1_REG_PS_PCER_WIDTH           32
#define BP1_REG_PS_PCDR_WIDTH           32
#define BP1_REG_PS_PCSR_WIDTH           32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
