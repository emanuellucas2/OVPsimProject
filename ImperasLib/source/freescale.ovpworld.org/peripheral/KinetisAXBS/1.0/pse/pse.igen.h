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
        struct {
            Uns32 M0 : 3;
            Uns32 __pad3 : 1;
            Uns32 M1 : 3;
            Uns32 __pad7 : 1;
            Uns32 M2 : 3;
            Uns32 __pad11 : 1;
            Uns32 M3 : 3;
            Uns32 __pad15 : 1;
            Uns32 M4 : 3;
            Uns32 __pad19 : 1;
            Uns32 M5 : 3;
            Uns32 __pad23 : 1;
            Uns32 M6 : 3;
            Uns32 __pad27 : 1;
            Uns32 M7 : 3;
        } bits;
    } PRS;
    union { 
        Uns32 value;
        struct {
            Uns32 PARK : 3;
            Uns32 __pad3 : 1;
            Uns32 PCTL : 2;
            Uns32 __pad6 : 2;
            Uns32 ARB : 2;
            Uns32 __pad10 : 20;
            Uns32 HLP : 1;
            Uns32 RO : 1;
        } bits;
    } CRS;
} bport1_ab_dataT, *bport1_ab_dataTP;

typedef struct bport1_ac_dataS { 
    union { 
        Uns32 value;
        struct {
            Uns32 AULB : 3;
        } bits;
    } MGPCR0;
    union { 
        Uns32 value;
        struct {
            Uns32 AULB : 3;
        } bits;
    } MGPCR1;
    union { 
        Uns32 value;
        struct {
            Uns32 AULB : 3;
        } bits;
    } MGPCR2;
    union { 
        Uns32 value;
        struct {
            Uns32 AULB : 3;
        } bits;
    } MGPCR3;
    union { 
        Uns32 value;
        struct {
            Uns32 AULB : 3;
        } bits;
    } MGPCR6;
    union { 
        Uns32 value;
        struct {
            Uns32 AULB : 3;
        } bits;
    } MGPCR7;
} bport1_ac_dataT, *bport1_ac_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data[8];

extern bport1_ac_dataT bport1_ac_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          Reset;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_PRS_WRMASK            0x77777777
#define BPORT1_AB_PRS_WRNMASK           (0x88888888)
#define BPORT1_AB_PRS_WIDTH             32
#define BPORT1_AB_CRS_WRMASK            0x77777777
#define BPORT1_AB_CRS_WRNMASK           (0x88888888)
#define BPORT1_AB_CRS_WIDTH             32
#define BPORT1_AC_MGPCR0_WRMASK         0x7
#define BPORT1_AC_MGPCR0_WRNMASK        (0xfffffff8)
#define BPORT1_AC_MGPCR0_WIDTH          32
#define BPORT1_AC_MGPCR1_WRMASK         0x7
#define BPORT1_AC_MGPCR1_WRNMASK        (0xfffffff8)
#define BPORT1_AC_MGPCR1_WIDTH          32
#define BPORT1_AC_MGPCR2_WRMASK         0x7
#define BPORT1_AC_MGPCR2_WRNMASK        (0xfffffff8)
#define BPORT1_AC_MGPCR2_WIDTH          32
#define BPORT1_AC_MGPCR3_WRMASK         0x7
#define BPORT1_AC_MGPCR3_WRNMASK        (0xfffffff8)
#define BPORT1_AC_MGPCR3_WIDTH          32
#define BPORT1_AC_MGPCR6_WRMASK         0x7
#define BPORT1_AC_MGPCR6_WRNMASK        (0xfffffff8)
#define BPORT1_AC_MGPCR6_WIDTH          32
#define BPORT1_AC_MGPCR7_WRMASK         0x7
#define BPORT1_AC_MGPCR7_WRNMASK        (0xfffffff8)
#define BPORT1_AC_MGPCR7_WIDTH          32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
