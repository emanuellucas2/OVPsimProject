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
    } T0Load;
    union { 
        Uns32 value;
    } T0Value;
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
    } T0Control;
    union { 
        Uns32 value;
    } T0IntClr;
    union { 
        Uns32 value;
    } T0RIS;
    union { 
        Uns32 value;
    } T0MIS;
    union { 
        Uns32 value;
    } T0BGLoad;
    union { 
        Uns32 value;
    } T1Load;
    union { 
        Uns32 value;
    } T1Value;
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
    } T1Control;
    union { 
        Uns32 value;
    } T1IntClr;
    union { 
        Uns32 value;
    } T1RIS;
    union { 
        Uns32 value;
    } T1MIS;
    union { 
        Uns32 value;
    } T1BGLoad;
    union { 
        Uns32 value;
    } ITCR;
    union { 
        Uns32 value;
    } ITOP;
    union { 
        Uns32 value;
    } PeriphID0;
    union { 
        Uns32 value;
    } PeriphID1;
    union { 
        Uns32 value;
    } PeriphID2;
    union { 
        Uns32 value;
    } PeriphID3;
    union { 
        Uns32 value;
    } PCellID0;
    union { 
        Uns32 value;
    } PCellID1;
    union { 
        Uns32 value;
    } PCellID2;
    union { 
        Uns32 value;
    } PCellID3;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          irq;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(readControl);
PPM_REG_READ_CB(readLoad);
PPM_REG_READ_CB(readMIS);
PPM_REG_READ_CB(readPCellID0);
PPM_REG_READ_CB(readPCellID1);
PPM_REG_READ_CB(readPCellID2);
PPM_REG_READ_CB(readPCellID3);
PPM_REG_READ_CB(readPeriphID0);
PPM_REG_READ_CB(readPeriphID1);
PPM_REG_READ_CB(readPeriphID2);
PPM_REG_READ_CB(readPeriphID3);
PPM_REG_READ_CB(readRIS);
PPM_REG_READ_CB(readValue);
PPM_REG_WRITE_CB(writeBGLoad);
PPM_REG_WRITE_CB(writeControl);
PPM_REG_WRITE_CB(writeIntClr);
PPM_REG_WRITE_CB(writeLoad);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_T0LOAD_WIDTH          32
#define BPORT1_AB_T0VALUE_WIDTH         32
#define BPORT1_AB_T0CONTROL_WIDTH       32
#define BPORT1_AB_T0INTCLR_WIDTH        32
#define BPORT1_AB_T0RIS_WIDTH           32
#define BPORT1_AB_T0MIS_WIDTH           32
#define BPORT1_AB_T0BGLOAD_WIDTH        32
#define BPORT1_AB_T1LOAD_WIDTH          32
#define BPORT1_AB_T1VALUE_WIDTH         32
#define BPORT1_AB_T1CONTROL_WIDTH       32
#define BPORT1_AB_T1INTCLR_WIDTH        32
#define BPORT1_AB_T1RIS_WIDTH           32
#define BPORT1_AB_T1MIS_WIDTH           32
#define BPORT1_AB_T1BGLOAD_WIDTH        32
#define BPORT1_AB_ITCR_WIDTH            32
#define BPORT1_AB_ITOP_WIDTH            32
#define BPORT1_AB_PERIPHID0_WIDTH       32
#define BPORT1_AB_PERIPHID1_WIDTH       32
#define BPORT1_AB_PERIPHID2_WIDTH       32
#define BPORT1_AB_PERIPHID3_WIDTH       32
#define BPORT1_AB_PCELLID0_WIDTH        32
#define BPORT1_AB_PCELLID1_WIDTH        32
#define BPORT1_AB_PCELLID2_WIDTH        32
#define BPORT1_AB_PCELLID3_WIDTH        32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
