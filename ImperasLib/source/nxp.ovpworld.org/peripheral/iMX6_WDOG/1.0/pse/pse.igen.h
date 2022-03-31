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
        Uns16 value;
        struct {
            Uns16 WDZST : 1;
            Uns16 WDBG : 1;
            Uns16 WDE : 1;
            Uns16 WDT : 1;
            Uns16 SRS : 1;
            Uns16 WDA : 1;
            Uns16 SRE : 1;
            Uns16 WDW : 1;
            Uns16 WT : 8;
        } bits;
    } WDOG_WCR;
    union { 
        Uns16 value;
    } WDOG_WSR;
    union { 
        Uns16 value;
        struct {
            Uns16 SFTW : 1;
            Uns16 TOUT : 1;
            Uns16 __pad2 : 2;
            Uns16 POR : 1;
        } bits;
    } WDOG_WRSR;
    union { 
        Uns16 value;
        struct {
            Uns16 WICT : 8;
            Uns16 __pad8 : 6;
            Uns16 WTIS : 1;
            Uns16 WIE : 1;
        } bits;
    } WDOG_WICR;
    union { 
        Uns16 value;
        struct {
            Uns16 PDE : 1;
        } bits;
    } WDOG_WMCR;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          WDOG;
    ppmNetHandle          interrupt;
    ppmNetHandle          wdog_rst;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_WRITE_CB(WriteWDOG_WCR);
PPM_REG_WRITE_CB(WriteWDOG_WICR);
PPM_REG_WRITE_CB(WriteWDOG_WMCR);
PPM_REG_WRITE_CB(WriteWDOG_WSR);
PPM_WRITE_CB(regNoDefinitionRead);
PPM_READ_CB(regNoDefinitionWrite);
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
#define BPORT1_AB_BUFFER_SIZE           0x4000

////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_WDOG_WCR_WIDTH        16
#define BPORT1_AB_WDOG_WSR_WIDTH        16
#define BPORT1_AB_WDOG_WRSR_WIDTH       16
#define BPORT1_AB_WDOG_WICR_WRMASK      0x80ff
#define BPORT1_AB_WDOG_WICR_WRNMASK     (0x7f00)
#define BPORT1_AB_WDOG_WICR_WIDTH       16
#define BPORT1_AB_WDOG_WMCR_WRMASK      0x1
#define BPORT1_AB_WDOG_WMCR_WRNMASK     (0xfffe)
#define BPORT1_AB_WDOG_WMCR_WIDTH       16

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
