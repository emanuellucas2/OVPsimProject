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
        struct {
            Uns8 IREFSTEN : 1;
            Uns8 IRCLKEN : 1;
            Uns8 IREFS : 1;
            Uns8 FRDIV : 3;
            Uns8 CLKS : 2;
        } bits;
    } C1;
    union { 
        Uns8 value;
        struct {
            Uns8 IRCS : 1;
            Uns8 LP : 1;
            Uns8 EREFS0 : 1;
            Uns8 HGO0 : 1;
            Uns8 RANGE0 : 2;
            Uns8 __pad6 : 1;
            Uns8 LOCRE0 : 1;
        } bits;
    } C2;
    union { 
        Uns8 value;
        struct {
            Uns8 SCTRIM : 8;
        } bits;
    } C3;
    union { 
        Uns8 value;
        struct {
            Uns8 SCFTRIM : 1;
            Uns8 FCTRIM : 4;
            Uns8 DRST_DRS : 2;
            Uns8 DMX32 : 1;
        } bits;
    } C4;
    union { 
        Uns8 value;
        struct {
            Uns8 PRDIV0 : 3;
            Uns8 __pad3 : 2;
            Uns8 PLLSTEN0 : 1;
            Uns8 PLLCLKEN0 : 1;
            Uns8 PLLREFSEL0 : 1;
        } bits;
    } C5;
    union { 
        Uns8 value;
        struct {
            Uns8 VDIV0 : 5;
            Uns8 CME0 : 1;
            Uns8 PLLS : 1;
            Uns8 LOLIE0 : 1;
        } bits;
    } C6;
    union { 
        Uns8 value;
        struct {
            Uns8 IRCST : 1;
            Uns8 OSCINIT0 : 1;
            Uns8 CLKST : 2;
            Uns8 IREFST : 1;
            Uns8 PLLST : 1;
            Uns8 LOCK0 : 1;
            Uns8 LOLS0 : 1;
        } bits;
    } S;
    union { 
        Uns8 value;
        struct {
            Uns8 LOCS0 : 1;
            Uns8 FCIRDIV : 3;
            Uns8 FLTPRSRV : 1;
            Uns8 ATMF : 1;
            Uns8 ATMS : 1;
            Uns8 ATME : 1;
        } bits;
    } SC;
    union { 
        Uns8 value;
        struct {
            Uns8 ATCVH : 8;
        } bits;
    } ATCVH;
    union { 
        Uns8 value;
        struct {
            Uns8 ATCVL : 8;
        } bits;
    } ATCVL;
    union { 
        Uns8 value;
        struct {
            Uns8 OSCSEL : 1;
        } bits;
    } C7;
    union { 
        Uns8 value;
        struct {
            Uns8 LOCS1 : 1;
            Uns8 __pad1 : 4;
            Uns8 CME1 : 1;
            Uns8 __pad6 : 1;
            Uns8 LOCRE1 : 1;
        } bits;
    } C8;
    union { 
        Uns8 value;
        struct {
            Uns8 __pad0 : 2;
            Uns8 EREFS1 : 1;
            Uns8 HGO1 : 1;
            Uns8 RANGE1 : 2;
            Uns8 __pad6 : 1;
            Uns8 LOCRE2 : 1;
        } bits;
    } C10;
    union { 
        Uns8 value;
        struct {
            Uns8 PRDIV1 : 3;
            Uns8 __pad3 : 1;
            Uns8 PLLCS : 1;
            Uns8 PLLSTEN1 : 1;
            Uns8 PLLCLKEN1 : 1;
            Uns8 PLLREFSEL1 : 1;
        } bits;
    } C11;
    union { 
        Uns8 value;
        struct {
            Uns8 VDIV1 : 5;
            Uns8 CME2 : 1;
            Uns8 __pad6 : 1;
            Uns8 LOLIE1 : 1;
        } bits;
    } C12;
    union { 
        Uns8 value;
        struct {
            Uns8 LOCS2 : 1;
            Uns8 OSCINIT2 : 1;
            Uns8 __pad2 : 2;
            Uns8 PLLCST : 1;
            Uns8 __pad5 : 1;
            Uns8 LOCK2 : 1;
            Uns8 LOLS2 : 1;
        } bits;
    } S2;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          Reset;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(readS);
PPM_REG_VIEW_CB(viewS);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_C1_WRMASK             0xff
#define BPORT1_AB_C1_WRNMASK            (0x0)
#define BPORT1_AB_C1_WIDTH              8
#define BPORT1_AB_C2_WRMASK             0xbf
#define BPORT1_AB_C2_WRNMASK            (0x40)
#define BPORT1_AB_C2_WIDTH              8
#define BPORT1_AB_C3_WRMASK             0xff
#define BPORT1_AB_C3_WRNMASK            (0x0)
#define BPORT1_AB_C3_WIDTH              8
#define BPORT1_AB_C4_WRMASK             0xff
#define BPORT1_AB_C4_WRNMASK            (0x0)
#define BPORT1_AB_C4_WIDTH              8
#define BPORT1_AB_C5_WRMASK             0xe7
#define BPORT1_AB_C5_WRNMASK            (0x18)
#define BPORT1_AB_C5_WIDTH              8
#define BPORT1_AB_C6_WRMASK             0xff
#define BPORT1_AB_C6_WRNMASK            (0x0)
#define BPORT1_AB_C6_WIDTH              8
#define BPORT1_AB_S_WIDTH               8
#define BPORT1_AB_SC_WRMASK             0x40
#define BPORT1_AB_SC_WRNMASK            (0xbf)
#define BPORT1_AB_SC_WIDTH              8
#define BPORT1_AB_ATCVH_WRMASK          0xff
#define BPORT1_AB_ATCVH_WRNMASK         (0x0)
#define BPORT1_AB_ATCVH_WIDTH           8
#define BPORT1_AB_ATCVL_WRMASK          0xff
#define BPORT1_AB_ATCVL_WRNMASK         (0x0)
#define BPORT1_AB_ATCVL_WIDTH           8
#define BPORT1_AB_C7_WRMASK             0x1
#define BPORT1_AB_C7_WRNMASK            (0xfe)
#define BPORT1_AB_C7_WIDTH              8
#define BPORT1_AB_C8_WRMASK             0xa0
#define BPORT1_AB_C8_WRNMASK            (0x5f)
#define BPORT1_AB_C8_WIDTH              8
#define BPORT1_AB_C10_WRMASK            0xbc
#define BPORT1_AB_C10_WRNMASK           (0x43)
#define BPORT1_AB_C10_WIDTH             8
#define BPORT1_AB_C11_WRMASK            0xf7
#define BPORT1_AB_C11_WRNMASK           (0x8)
#define BPORT1_AB_C11_WIDTH             8
#define BPORT1_AB_C12_WRMASK            0xbf
#define BPORT1_AB_C12_WRNMASK           (0x40)
#define BPORT1_AB_C12_WIDTH             8
#define BPORT1_AB_S2_WIDTH              8

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
