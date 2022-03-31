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
            Uns16 WDOGEN : 1;
            Uns16 CLKSRC : 1;
            Uns16 IRQRSTEN : 1;
            Uns16 WINEN : 1;
            Uns16 ALLOWUPDATE : 1;
            Uns16 DBGEN : 1;
            Uns16 STOPEN : 1;
            Uns16 WAITEN : 1;
            Uns16 STNDBYEN : 1;
            Uns16 __pad9 : 1;
            Uns16 TESTWDOG : 1;
            Uns16 TESTSEL : 1;
            Uns16 BYTESEL : 2;
            Uns16 DISTESTWDOG : 1;
        } bits;
    } STCTRLH;
    union { 
        Uns16 value;
        struct {
            Uns16 __pad0 : 15;
            Uns16 INTFLG : 1;
        } bits;
    } STCTRLL;
    union { 
        Uns16 value;
        struct {
            Uns16 TOVALHIGH : 16;
        } bits;
    } TOVALH;
    union { 
        Uns16 value;
        struct {
            Uns16 TOVALLOW : 16;
        } bits;
    } TOVALL;
    union { 
        Uns16 value;
        struct {
            Uns16 WINHIGH : 16;
        } bits;
    } WINH;
    union { 
        Uns16 value;
        struct {
            Uns16 WINLOW : 16;
        } bits;
    } WINL;
    union { 
        Uns16 value;
        struct {
            Uns16 WDOGREFRESH : 16;
        } bits;
    } REFRESH;
    union { 
        Uns16 value;
        struct {
            Uns16 WDOGUNLOCK : 16;
        } bits;
    } UNLOCK;
    union { 
        Uns16 value;
        struct {
            Uns16 TIMEROUTHIGH : 16;
        } bits;
    } TMROUTH;
    union { 
        Uns16 value;
        struct {
            Uns16 TIMEROUTLOW : 16;
        } bits;
    } TMROUTL;
    union { 
        Uns16 value;
        struct {
            Uns16 RSTCNT : 16;
        } bits;
    } RSTCNT;
    union { 
        Uns16 value;
        struct {
            Uns16 __pad0 : 8;
            Uns16 PRESCVAL : 3;
        } bits;
    } PRESC;
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

PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_STCTRLH_WRMASK        0x7cff
#define BPORT1_AB_STCTRLH_WRNMASK       (0x8300)
#define BPORT1_AB_STCTRLH_WIDTH         16
#define BPORT1_AB_STCTRLL_WRMASK        0x8000
#define BPORT1_AB_STCTRLL_WRNMASK       (0x7fff)
#define BPORT1_AB_STCTRLL_WIDTH         16
#define BPORT1_AB_TOVALH_WRMASK         0xffff
#define BPORT1_AB_TOVALH_WRNMASK        (0x0)
#define BPORT1_AB_TOVALH_WIDTH          16
#define BPORT1_AB_TOVALL_WRMASK         0xffff
#define BPORT1_AB_TOVALL_WRNMASK        (0x0)
#define BPORT1_AB_TOVALL_WIDTH          16
#define BPORT1_AB_WINH_WRMASK           0xffff
#define BPORT1_AB_WINH_WRNMASK          (0x0)
#define BPORT1_AB_WINH_WIDTH            16
#define BPORT1_AB_WINL_WRMASK           0xffff
#define BPORT1_AB_WINL_WRNMASK          (0x0)
#define BPORT1_AB_WINL_WIDTH            16
#define BPORT1_AB_REFRESH_WRMASK        0xffff
#define BPORT1_AB_REFRESH_WRNMASK       (0x0)
#define BPORT1_AB_REFRESH_WIDTH         16
#define BPORT1_AB_UNLOCK_WRMASK         0xffff
#define BPORT1_AB_UNLOCK_WRNMASK        (0x0)
#define BPORT1_AB_UNLOCK_WIDTH          16
#define BPORT1_AB_TMROUTH_WRMASK        0xffff
#define BPORT1_AB_TMROUTH_WRNMASK       (0x0)
#define BPORT1_AB_TMROUTH_WIDTH         16
#define BPORT1_AB_TMROUTL_WRMASK        0xffff
#define BPORT1_AB_TMROUTL_WRNMASK       (0x0)
#define BPORT1_AB_TMROUTL_WIDTH         16
#define BPORT1_AB_RSTCNT_WRMASK         0xffff
#define BPORT1_AB_RSTCNT_WRNMASK        (0x0)
#define BPORT1_AB_RSTCNT_WIDTH          16
#define BPORT1_AB_PRESC_WRMASK          0x700
#define BPORT1_AB_PRESC_WRNMASK         (0xf8ff)
#define BPORT1_AB_PRESC_WIDTH           16

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
