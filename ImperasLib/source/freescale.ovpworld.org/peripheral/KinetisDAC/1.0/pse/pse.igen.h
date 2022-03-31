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
            Uns8 DATA : 8;
        } bits;
    } DAT0L;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 4;
        } bits;
    } DAT0H;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 8;
        } bits;
    } DAT1L;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 4;
        } bits;
    } DAT1H;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 8;
        } bits;
    } DAT2L;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 4;
        } bits;
    } DAT2H;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 8;
        } bits;
    } DAT3L;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 4;
        } bits;
    } DAT3H;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 8;
        } bits;
    } DAT4L;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 4;
        } bits;
    } DAT4H;
    union { 
        Uns8 value;
    } DAT5L;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 4;
        } bits;
    } DAT5H;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 8;
        } bits;
    } DAT6L;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 4;
        } bits;
    } DAT6H;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 8;
        } bits;
    } DAT7L;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 4;
        } bits;
    } DAT7H;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 8;
        } bits;
    } DAT8L;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 4;
        } bits;
    } DAT8H;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 8;
        } bits;
    } DAT9L;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 4;
        } bits;
    } DAT9H;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 8;
        } bits;
    } DAT10L;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 4;
        } bits;
    } DAT10H;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 8;
        } bits;
    } DAT11L;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 4;
        } bits;
    } DAT11H;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 8;
        } bits;
    } DAT12L;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 4;
        } bits;
    } DAT12H;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 8;
        } bits;
    } DAT13L;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 4;
        } bits;
    } DAT13H;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 8;
        } bits;
    } DAT14L;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 4;
        } bits;
    } DAT14H;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 8;
        } bits;
    } DAT15L;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 4;
        } bits;
    } DAT15H;
    union { 
        Uns8 value;
        struct {
            Uns8 DACBFRPBF : 1;
            Uns8 DACBFRPTF : 1;
            Uns8 DACBFWMF : 1;
        } bits;
    } SR;
    union { 
        Uns8 value;
        struct {
            Uns8 DACBBIEN : 1;
            Uns8 DACBTIEN : 1;
            Uns8 DACBWIEN : 1;
            Uns8 LPEN : 1;
            Uns8 DACSWTRG : 1;
            Uns8 DACTRGSEL : 1;
            Uns8 DACRFS : 1;
            Uns8 DACEN : 1;
        } bits;
    } C0;
    union { 
        Uns8 value;
        struct {
            Uns8 DACBFEN : 1;
            Uns8 DACBFMD : 2;
            Uns8 DACBFWM : 2;
            Uns8 __pad5 : 2;
            Uns8 DMAEN : 1;
        } bits;
    } C1;
    union { 
        Uns8 value;
        struct {
            Uns8 DACBFUP : 4;
            Uns8 DACBFRP : 4;
        } bits;
    } C2;
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

#define BPORT1_AB_DAT0L_WRMASK          0xff
#define BPORT1_AB_DAT0L_WRNMASK         (0x0)
#define BPORT1_AB_DAT0L_WIDTH           8
#define BPORT1_AB_DAT0H_WRMASK          0xf
#define BPORT1_AB_DAT0H_WRNMASK         (0xf0)
#define BPORT1_AB_DAT0H_WIDTH           8
#define BPORT1_AB_DAT1L_WRMASK          0xff
#define BPORT1_AB_DAT1L_WRNMASK         (0x0)
#define BPORT1_AB_DAT1L_WIDTH           8
#define BPORT1_AB_DAT1H_WRMASK          0xf
#define BPORT1_AB_DAT1H_WRNMASK         (0xf0)
#define BPORT1_AB_DAT1H_WIDTH           8
#define BPORT1_AB_DAT2L_WRMASK          0xff
#define BPORT1_AB_DAT2L_WRNMASK         (0x0)
#define BPORT1_AB_DAT2L_WIDTH           8
#define BPORT1_AB_DAT2H_WRMASK          0xf
#define BPORT1_AB_DAT2H_WRNMASK         (0xf0)
#define BPORT1_AB_DAT2H_WIDTH           8
#define BPORT1_AB_DAT3L_WRMASK          0xff
#define BPORT1_AB_DAT3L_WRNMASK         (0x0)
#define BPORT1_AB_DAT3L_WIDTH           8
#define BPORT1_AB_DAT3H_WRMASK          0xf
#define BPORT1_AB_DAT3H_WRNMASK         (0xf0)
#define BPORT1_AB_DAT3H_WIDTH           8
#define BPORT1_AB_DAT4L_WRMASK          0xff
#define BPORT1_AB_DAT4L_WRNMASK         (0x0)
#define BPORT1_AB_DAT4L_WIDTH           8
#define BPORT1_AB_DAT4H_WRMASK          0xf
#define BPORT1_AB_DAT4H_WRNMASK         (0xf0)
#define BPORT1_AB_DAT4H_WIDTH           8
#define BPORT1_AB_DAT5L_WRMASK          0xff
#define BPORT1_AB_DAT5L_WRNMASK         (0x0)
#define BPORT1_AB_DAT5L_WIDTH           8
#define BPORT1_AB_DAT5H_WRMASK          0xf
#define BPORT1_AB_DAT5H_WRNMASK         (0xf0)
#define BPORT1_AB_DAT5H_WIDTH           8
#define BPORT1_AB_DAT6L_WRMASK          0xff
#define BPORT1_AB_DAT6L_WRNMASK         (0x0)
#define BPORT1_AB_DAT6L_WIDTH           8
#define BPORT1_AB_DAT6H_WRMASK          0xf
#define BPORT1_AB_DAT6H_WRNMASK         (0xf0)
#define BPORT1_AB_DAT6H_WIDTH           8
#define BPORT1_AB_DAT7L_WRMASK          0xff
#define BPORT1_AB_DAT7L_WRNMASK         (0x0)
#define BPORT1_AB_DAT7L_WIDTH           8
#define BPORT1_AB_DAT7H_WRMASK          0xf
#define BPORT1_AB_DAT7H_WRNMASK         (0xf0)
#define BPORT1_AB_DAT7H_WIDTH           8
#define BPORT1_AB_DAT8L_WRMASK          0xff
#define BPORT1_AB_DAT8L_WRNMASK         (0x0)
#define BPORT1_AB_DAT8L_WIDTH           8
#define BPORT1_AB_DAT8H_WRMASK          0xf
#define BPORT1_AB_DAT8H_WRNMASK         (0xf0)
#define BPORT1_AB_DAT8H_WIDTH           8
#define BPORT1_AB_DAT9L_WRMASK          0xff
#define BPORT1_AB_DAT9L_WRNMASK         (0x0)
#define BPORT1_AB_DAT9L_WIDTH           8
#define BPORT1_AB_DAT9H_WRMASK          0xf
#define BPORT1_AB_DAT9H_WRNMASK         (0xf0)
#define BPORT1_AB_DAT9H_WIDTH           8
#define BPORT1_AB_DAT10L_WRMASK         0xff
#define BPORT1_AB_DAT10L_WRNMASK        (0x0)
#define BPORT1_AB_DAT10L_WIDTH          8
#define BPORT1_AB_DAT10H_WRMASK         0xf
#define BPORT1_AB_DAT10H_WRNMASK        (0xf0)
#define BPORT1_AB_DAT10H_WIDTH          8
#define BPORT1_AB_DAT11L_WRMASK         0xff
#define BPORT1_AB_DAT11L_WRNMASK        (0x0)
#define BPORT1_AB_DAT11L_WIDTH          8
#define BPORT1_AB_DAT11H_WRMASK         0xf
#define BPORT1_AB_DAT11H_WRNMASK        (0xf0)
#define BPORT1_AB_DAT11H_WIDTH          8
#define BPORT1_AB_DAT12L_WRMASK         0xff
#define BPORT1_AB_DAT12L_WRNMASK        (0x0)
#define BPORT1_AB_DAT12L_WIDTH          8
#define BPORT1_AB_DAT12H_WRMASK         0xf
#define BPORT1_AB_DAT12H_WRNMASK        (0xf0)
#define BPORT1_AB_DAT12H_WIDTH          8
#define BPORT1_AB_DAT13L_WRMASK         0xff
#define BPORT1_AB_DAT13L_WRNMASK        (0x0)
#define BPORT1_AB_DAT13L_WIDTH          8
#define BPORT1_AB_DAT13H_WRMASK         0xf
#define BPORT1_AB_DAT13H_WRNMASK        (0xf0)
#define BPORT1_AB_DAT13H_WIDTH          8
#define BPORT1_AB_DAT14L_WRMASK         0xff
#define BPORT1_AB_DAT14L_WRNMASK        (0x0)
#define BPORT1_AB_DAT14L_WIDTH          8
#define BPORT1_AB_DAT14H_WRMASK         0xf
#define BPORT1_AB_DAT14H_WRNMASK        (0xf0)
#define BPORT1_AB_DAT14H_WIDTH          8
#define BPORT1_AB_DAT15L_WRMASK         0xff
#define BPORT1_AB_DAT15L_WRNMASK        (0x0)
#define BPORT1_AB_DAT15L_WIDTH          8
#define BPORT1_AB_DAT15H_WRMASK         0xf
#define BPORT1_AB_DAT15H_WRNMASK        (0xf0)
#define BPORT1_AB_DAT15H_WIDTH          8
#define BPORT1_AB_SR_WRMASK             0x7
#define BPORT1_AB_SR_WRNMASK            (0xf8)
#define BPORT1_AB_SR_WIDTH              8
#define BPORT1_AB_C0_WRMASK             0xff
#define BPORT1_AB_C0_WRNMASK            (0x0)
#define BPORT1_AB_C0_WIDTH              8
#define BPORT1_AB_C1_WRMASK             0x9f
#define BPORT1_AB_C1_WRNMASK            (0x60)
#define BPORT1_AB_C1_WIDTH              8
#define BPORT1_AB_C2_WRMASK             0xff
#define BPORT1_AB_C2_WRNMASK            (0x0)
#define BPORT1_AB_C2_WIDTH              8

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
