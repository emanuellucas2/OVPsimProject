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
            Uns32 MDT0 : 1;
            Uns32 UDT0 : 1;
            Uns32 GENT0 : 1;
            Uns32 CAPT0 : 1;
            Uns32 ARHT0 : 1;
            Uns32 LOAD0 : 1;
            Uns32 ENIT0 : 1;
            Uns32 ENT0 : 1;
            Uns32 T0INT : 1;
            Uns32 PWMA0 : 1;
            Uns32 ENALL : 1;
        } bits;
    } TCSR0;
    union { 
        Uns32 value;
    } TLR0;
    union { 
        Uns32 value;
    } TCR0;
    union { 
        Uns32 value;
        struct {
            Uns32 MDT1 : 1;
            Uns32 UDT1 : 1;
            Uns32 GENT1 : 1;
            Uns32 CAPT1 : 1;
            Uns32 ARHT1 : 1;
            Uns32 LOAD1 : 1;
            Uns32 ENIT1 : 1;
            Uns32 ENT1 : 1;
            Uns32 T1INT : 1;
            Uns32 PWMA1 : 1;
            Uns32 ENALL : 1;
        } bits;
    } TCSR1;
    union { 
        Uns32 value;
    } TLR1;
    union { 
        Uns32 value;
    } TCR1;
} plb_REG_dataT, *plb_REG_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern plb_REG_dataT plb_REG_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *plb;
    ppmNetHandle          Interrupt;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(ReadTCR0);
PPM_REG_READ_CB(ReadTCR1);
PPM_REG_READ_CB(ReadTCSR0);
PPM_REG_READ_CB(ReadTCSR1);
PPM_REG_READ_CB(ReadTLR0);
PPM_REG_READ_CB(ReadTLR1);
PPM_REG_WRITE_CB(WriteTCSR0);
PPM_REG_WRITE_CB(WriteTCSR1);
PPM_REG_WRITE_CB(WriteTLR0);
PPM_REG_WRITE_CB(WriteTLR1);
PPM_NET_CB(reset_resetNet);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define PLB_REG_TCSR0_WIDTH             32
#define PLB_REG_TLR0_WIDTH              32
#define PLB_REG_TCR0_WIDTH              32
#define PLB_REG_TCSR1_WIDTH             32
#define PLB_REG_TLR1_WIDTH              32
#define PLB_REG_TCR1_WIDTH              32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
