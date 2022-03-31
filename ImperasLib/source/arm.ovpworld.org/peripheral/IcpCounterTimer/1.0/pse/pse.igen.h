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
    } load0;
    union { 
        Uns32 value;
    } limit0;
    union { 
        Uns32 value;
        struct {
            Uns32 ONESHOT : 1;
            Uns32 M32BIT : 1;
            Uns32 DIV : 2;
            Uns32 __pad4 : 1;
            Uns32 IE : 1;
            Uns32 PERIODIC : 1;
            Uns32 ENABLE : 1;
        } bits;
    } control0;
    union { 
        Uns32 value;
    } intclr0;
    union { 
        Uns32 value;
    } intlevel0;
    union { 
        Uns32 value;
    } mis0;
    union { 
        Uns32 value;
    } bgload0;
    union { 
        Uns32 value;
    } load1;
    union { 
        Uns32 value;
    } limit1;
    union { 
        Uns32 value;
        struct {
            Uns32 ONESHOT : 1;
            Uns32 M32BIT : 1;
            Uns32 DIV : 2;
            Uns32 __pad4 : 1;
            Uns32 IE : 1;
            Uns32 PERIODIC : 1;
            Uns32 ENABLE : 1;
        } bits;
    } control1;
    union { 
        Uns32 value;
    } intclr1;
    union { 
        Uns32 value;
    } intlevel1;
    union { 
        Uns32 value;
    } mis1;
    union { 
        Uns32 value;
    } bgload1;
    union { 
        Uns32 value;
    } load2;
    union { 
        Uns32 value;
    } limit2;
    union { 
        Uns32 value;
        struct {
            Uns32 ONESHOT : 1;
            Uns32 M32BIT : 1;
            Uns32 DIV : 2;
            Uns32 __pad4 : 1;
            Uns32 IE : 1;
            Uns32 PERIODIC : 1;
            Uns32 ENABLE : 1;
        } bits;
    } control2;
    union { 
        Uns32 value;
    } intclr2;
    union { 
        Uns32 value;
    } intlevel2;
    union { 
        Uns32 value;
    } mis2;
    union { 
        Uns32 value;
    } bgload2;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          irq0;
    ppmNetHandle          irq1;
    ppmNetHandle          irq2;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(readControl);
PPM_REG_READ_CB(readLimit);
PPM_REG_READ_CB(readMIS);
PPM_REG_READ_CB(readValue);
PPM_REG_WRITE_CB(writeBG);
PPM_REG_WRITE_CB(writeClear);
PPM_REG_WRITE_CB(writeControl);
PPM_REG_WRITE_CB(writeLimit);
PPM_REG_WRITE_CB(writeValue);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_LOAD0_WIDTH           32
#define BPORT1_AB_LIMIT0_WIDTH          32
#define BPORT1_AB_CONTROL0_WIDTH        32
#define BPORT1_AB_INTCLR0_WIDTH         32
#define BPORT1_AB_INTLEVEL0_WIDTH       32
#define BPORT1_AB_MIS0_WIDTH            32
#define BPORT1_AB_BGLOAD0_WIDTH         32
#define BPORT1_AB_LOAD1_WIDTH           32
#define BPORT1_AB_LIMIT1_WIDTH          32
#define BPORT1_AB_CONTROL1_WIDTH        32
#define BPORT1_AB_INTCLR1_WIDTH         32
#define BPORT1_AB_INTLEVEL1_WIDTH       32
#define BPORT1_AB_MIS1_WIDTH            32
#define BPORT1_AB_BGLOAD1_WIDTH         32
#define BPORT1_AB_LOAD2_WIDTH           32
#define BPORT1_AB_LIMIT2_WIDTH          32
#define BPORT1_AB_CONTROL2_WIDTH        32
#define BPORT1_AB_INTCLR2_WIDTH         32
#define BPORT1_AB_INTLEVEL2_WIDTH       32
#define BPORT1_AB_MIS2_WIDTH            32
#define BPORT1_AB_BGLOAD2_WIDTH         32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
