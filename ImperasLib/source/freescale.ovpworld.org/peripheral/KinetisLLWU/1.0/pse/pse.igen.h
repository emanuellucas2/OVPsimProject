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
            Uns8 WUPE0 : 2;
            Uns8 WUPE1 : 2;
            Uns8 WUPE2 : 2;
            Uns8 WUPE3 : 2;
        } bits;
    } PE1;
    union { 
        Uns8 value;
        struct {
            Uns8 WUPE4 : 2;
            Uns8 WUPE5 : 2;
            Uns8 WUPE6 : 2;
            Uns8 WUPE7 : 2;
        } bits;
    } PE2;
    union { 
        Uns8 value;
        struct {
            Uns8 WUPE8 : 2;
            Uns8 WUPE9 : 2;
            Uns8 WUPE10 : 2;
            Uns8 WUPE11 : 2;
        } bits;
    } PE3;
    union { 
        Uns8 value;
        struct {
            Uns8 WUPE12 : 2;
            Uns8 WUPE13 : 2;
            Uns8 WUPE14 : 2;
            Uns8 WUPE15 : 2;
        } bits;
    } PE4;
    union { 
        Uns8 value;
        struct {
            Uns8 WUME0 : 1;
            Uns8 WUME1 : 1;
            Uns8 WUME2 : 1;
            Uns8 WUME3 : 1;
            Uns8 WUME4 : 1;
            Uns8 WUME5 : 1;
            Uns8 WUME6 : 1;
            Uns8 WUME7 : 1;
        } bits;
    } ME;
    union { 
        Uns8 value;
        struct {
            Uns8 WUF0 : 1;
            Uns8 WUF1 : 1;
            Uns8 WUF2 : 1;
            Uns8 WUF3 : 1;
            Uns8 WUF4 : 1;
            Uns8 WUF5 : 1;
            Uns8 WUF6 : 1;
            Uns8 WUF7 : 1;
        } bits;
    } F1;
    union { 
        Uns8 value;
        struct {
            Uns8 WUF8 : 1;
            Uns8 WUF9 : 1;
            Uns8 WUF10 : 1;
            Uns8 WUF11 : 1;
            Uns8 WUF12 : 1;
            Uns8 WUF13 : 1;
            Uns8 WUF14 : 1;
            Uns8 WUF15 : 1;
        } bits;
    } F2;
    union { 
        Uns8 value;
        struct {
            Uns8 MWUF0 : 1;
            Uns8 MWUF1 : 1;
            Uns8 MWUF2 : 1;
            Uns8 MWUF3 : 1;
            Uns8 MWUF4 : 1;
            Uns8 MWUF5 : 1;
            Uns8 MWUF6 : 1;
            Uns8 MWUF7 : 1;
        } bits;
    } F3;
    union { 
        Uns8 value;
        struct {
            Uns8 FILTSEL : 4;
            Uns8 __pad4 : 1;
            Uns8 FILTE : 2;
            Uns8 FILTF : 1;
        } bits;
    } FILT1;
    union { 
        Uns8 value;
        struct {
            Uns8 FILTSEL : 4;
            Uns8 __pad4 : 1;
            Uns8 FILTE : 2;
            Uns8 FILTF : 1;
        } bits;
    } FILT2;
    union { 
        Uns8 value;
        struct {
            Uns8 RSTFILT : 1;
            Uns8 LLRSTE : 1;
        } bits;
    } RST;
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

#define BPORT1_AB_PE1_WRMASK            0xff
#define BPORT1_AB_PE1_WRNMASK           (0x0)
#define BPORT1_AB_PE1_WIDTH             8
#define BPORT1_AB_PE2_WRMASK            0xff
#define BPORT1_AB_PE2_WRNMASK           (0x0)
#define BPORT1_AB_PE2_WIDTH             8
#define BPORT1_AB_PE3_WRMASK            0xff
#define BPORT1_AB_PE3_WRNMASK           (0x0)
#define BPORT1_AB_PE3_WIDTH             8
#define BPORT1_AB_PE4_WRMASK            0xff
#define BPORT1_AB_PE4_WRNMASK           (0x0)
#define BPORT1_AB_PE4_WIDTH             8
#define BPORT1_AB_ME_WRMASK             0xff
#define BPORT1_AB_ME_WRNMASK            (0x0)
#define BPORT1_AB_ME_WIDTH              8
#define BPORT1_AB_F1_WRMASK             0xff
#define BPORT1_AB_F1_WRNMASK            (0x0)
#define BPORT1_AB_F1_WIDTH              8
#define BPORT1_AB_F2_WRMASK             0xff
#define BPORT1_AB_F2_WRNMASK            (0x0)
#define BPORT1_AB_F2_WIDTH              8
#define BPORT1_AB_F3_WIDTH              8
#define BPORT1_AB_FILT1_WRMASK          0xef
#define BPORT1_AB_FILT1_WRNMASK         (0x10)
#define BPORT1_AB_FILT1_WIDTH           8
#define BPORT1_AB_FILT2_WRMASK          0xef
#define BPORT1_AB_FILT2_WRNMASK         (0x10)
#define BPORT1_AB_FILT2_WIDTH           8
#define BPORT1_AB_RST_WRMASK            0x3
#define BPORT1_AB_RST_WRNMASK           (0xfc)
#define BPORT1_AB_RST_WIDTH             8

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
