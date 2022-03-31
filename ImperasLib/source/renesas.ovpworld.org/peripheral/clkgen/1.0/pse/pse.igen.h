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

typedef struct CLKGENP0_reg0_dataS { 
    union { 
        Uns8 value;
        struct {
            Uns8 CANCK0 : 1;
        } bits;
    } CANCKSEL;
} CLKGENP0_reg0_dataT, *CLKGENP0_reg0_dataTP;

typedef struct CLKGENP1_reg0_dataS { 
    union { 
        Uns8 value;
        struct {
            Uns8 CLME : 1;
            Uns8 CLMD : 1;
        } bits;
    } CLM;
} CLKGENP1_reg0_dataT, *CLKGENP1_reg0_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern CLKGENP0_reg0_dataT CLKGENP0_reg0_data;

extern CLKGENP1_reg0_dataT CLKGENP1_reg0_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *CLKGENP0;
    void                 *CLKGENP1;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_WRITE_CB(writeCANCKSEL);
PPM_REG_WRITE_CB(writeCLM);
PPM_NET_CB(reset_IRESET);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define CLKGENP0_REG0_CANCKSEL_WRMASK   0x1
#define CLKGENP0_REG0_CANCKSEL_WRNMASK  (0xfe)
#define CLKGENP0_REG0_CANCKSEL_WIDTH    8
#define CLKGENP1_REG0_CLM_WRMASK        0x3
#define CLKGENP1_REG0_CLM_WRNMASK       (0xfc)
#define CLKGENP1_REG0_CLM_WIDTH         8

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
