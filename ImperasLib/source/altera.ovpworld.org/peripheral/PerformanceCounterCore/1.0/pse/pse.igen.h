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

typedef struct sp1_reg0_dataS { 
    union { 
        Uns32 value;
    } t0lo;
    union { 
        Uns32 value;
    } t0hi;
    union { 
        Uns32 value;
    } t0ev;
    union { 
        Uns32 value;
    } t1lo;
    union { 
        Uns32 value;
    } t1hi;
    union { 
        Uns32 value;
    } t1ev;
    union { 
        Uns32 value;
    } t2lo;
    union { 
        Uns32 value;
    } t2hi;
    union { 
        Uns32 value;
    } t2ev;
    union { 
        Uns32 value;
    } t3lo;
    union { 
        Uns32 value;
    } t3hi;
    union { 
        Uns32 value;
    } t3ev;
    union { 
        Uns32 value;
    } t4lo;
    union { 
        Uns32 value;
    } t4hi;
    union { 
        Uns32 value;
    } t4ev;
    union { 
        Uns32 value;
    } t5lo;
    union { 
        Uns32 value;
    } t5hi;
    union { 
        Uns32 value;
    } t5ev;
} sp1_reg0_dataT, *sp1_reg0_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern sp1_reg0_dataT sp1_reg0_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *sp1;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(read_ev);
PPM_REG_READ_CB(read_hi);
PPM_REG_READ_CB(read_lo);
PPM_REG_WRITE_CB(write_ev);
PPM_REG_WRITE_CB(write_hi);
PPM_REG_WRITE_CB(write_lo);
PPM_NET_CB(reset_IRESET);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define SP1_REG0_T0LO_WIDTH             32
#define SP1_REG0_T0HI_WIDTH             32
#define SP1_REG0_T0EV_WIDTH             32
#define SP1_REG0_T1LO_WIDTH             32
#define SP1_REG0_T1HI_WIDTH             32
#define SP1_REG0_T1EV_WIDTH             32
#define SP1_REG0_T2LO_WIDTH             32
#define SP1_REG0_T2HI_WIDTH             32
#define SP1_REG0_T2EV_WIDTH             32
#define SP1_REG0_T3LO_WIDTH             32
#define SP1_REG0_T3HI_WIDTH             32
#define SP1_REG0_T3EV_WIDTH             32
#define SP1_REG0_T4LO_WIDTH             32
#define SP1_REG0_T4HI_WIDTH             32
#define SP1_REG0_T4EV_WIDTH             32
#define SP1_REG0_T5LO_WIDTH             32
#define SP1_REG0_T5HI_WIDTH             32
#define SP1_REG0_T5EV_WIDTH             32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
