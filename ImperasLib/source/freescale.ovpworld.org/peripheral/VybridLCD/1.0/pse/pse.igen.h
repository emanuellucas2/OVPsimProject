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
            Uns32 LCDBPS : 3;
            Uns32 __pad3 : 1;
            Uns32 LCDBPA : 2;
            Uns32 __pad6 : 2;
            Uns32 NOF : 8;
            Uns32 EOF : 1;
            Uns32 LCDINT : 1;
            Uns32 LCDOCS : 1;
            Uns32 BSTAO : 1;
            Uns32 BSTSEL : 1;
            Uns32 BSTEN : 1;
            Uns32 PWR : 2;
            Uns32 VLCDS : 1;
            Uns32 BIAS : 1;
            Uns32 DUTY : 3;
            Uns32 LCDRCS : 1;
            Uns32 LCDRST : 1;
            Uns32 LCDEN : 1;
        } bits;
    } LCDCR;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 24;
            Uns32 LCLK : 4;
        } bits;
    } LCDPCR;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 16;
            Uns32 LCC : 11;
            Uns32 __pad27 : 4;
            Uns32 CCEN : 1;
        } bits;
    } LCDCCR;
    union { 
        Uns32 value;
        struct {
            Uns32 ENFP : 32;
        } bits;
    } ENFPR0;
    union { 
        Uns32 value;
        struct {
            Uns32 ENFP : 32;
        } bits;
    } ENFPR1;
    union { 
        Uns32 value;
        struct {
            Uns32 FP3_BP : 8;
            Uns32 FP2_BP : 8;
            Uns32 FP1_BP : 8;
            Uns32 FP0_BP : 8;
        } bits;
    } LCDRAM0;
    union { 
        Uns32 value;
        struct {
            Uns32 FP7_BP : 8;
            Uns32 FP6_BP : 8;
            Uns32 FP5_BP : 8;
            Uns32 FP4_BP : 8;
        } bits;
    } LCDRAM1;
    union { 
        Uns32 value;
        struct {
            Uns32 FP11_BP : 8;
            Uns32 FP10_BP : 8;
            Uns32 FP9_BP : 8;
            Uns32 FP8_BP : 8;
        } bits;
    } LCDRAM2;
    union { 
        Uns32 value;
        struct {
            Uns32 FP15_BP : 8;
            Uns32 FP14_BP : 8;
            Uns32 FP13_BP : 8;
            Uns32 FP12_BP : 8;
        } bits;
    } LCDRAM3;
    union { 
        Uns32 value;
        struct {
            Uns32 FP19_BP : 8;
            Uns32 FP18_BP : 8;
            Uns32 FP17_BP : 8;
            Uns32 FP16_BP : 8;
        } bits;
    } LCDRAM4;
    union { 
        Uns32 value;
        struct {
            Uns32 FP23_BP : 8;
            Uns32 FP22_BP : 8;
            Uns32 FP21_BP : 8;
            Uns32 FP20_BP : 8;
        } bits;
    } LCDRAM5;
    union { 
        Uns32 value;
        struct {
            Uns32 FP27_BP : 8;
            Uns32 FP26_BP : 8;
            Uns32 FP25_BP : 8;
            Uns32 FP24_BP : 8;
        } bits;
    } LCDRAM6;
    union { 
        Uns32 value;
        struct {
            Uns32 FP31_BP : 8;
            Uns32 FP30_BP : 8;
            Uns32 FP29_BP : 8;
            Uns32 FP28_BP : 8;
        } bits;
    } LCDRAM7;
    union { 
        Uns32 value;
        struct {
            Uns32 FP35_BP : 8;
            Uns32 FP34_BP : 8;
            Uns32 FP33_BP : 8;
            Uns32 FP32_BP : 8;
        } bits;
    } LCDRAM8;
    union { 
        Uns32 value;
        struct {
            Uns32 FP39_BP : 8;
            Uns32 FP38_BP : 8;
            Uns32 FP37_BP : 8;
            Uns32 FP36_BP : 8;
        } bits;
    } LCDRAM9;
    union { 
        Uns32 value;
        struct {
            Uns32 FP43_BP : 8;
            Uns32 FP42_BP : 8;
            Uns32 FP41_BP : 8;
            Uns32 FP40_BP : 8;
        } bits;
    } LCDRAM10;
    union { 
        Uns32 value;
        struct {
            Uns32 FP47_BP : 8;
            Uns32 FP46_BP : 8;
            Uns32 FP45_BP : 8;
            Uns32 FP44_BP : 8;
        } bits;
    } LCDRAM11;
    union { 
        Uns32 value;
        struct {
            Uns32 FP51_BP : 8;
            Uns32 FP50_BP : 8;
            Uns32 FP49_BP : 8;
            Uns32 FP48_BP : 8;
        } bits;
    } LCDRAM12;
    union { 
        Uns32 value;
        struct {
            Uns32 FP55_BP : 8;
            Uns32 FP54_BP : 8;
            Uns32 FP53_BP : 8;
            Uns32 FP52_BP : 8;
        } bits;
    } LCDRAM13;
    union { 
        Uns32 value;
        struct {
            Uns32 FP59_BP : 8;
            Uns32 FP58_BP : 8;
            Uns32 FP57_BP : 8;
            Uns32 FP56_BP : 8;
        } bits;
    } LCDRAM14;
    union { 
        Uns32 value;
        struct {
            Uns32 FP63_BP : 8;
            Uns32 FP62_BP : 8;
            Uns32 FP61_BP : 8;
            Uns32 FP60_BP : 8;
        } bits;
    } LCDRAM15;
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

#define BPORT1_AB_LCDCR_WRMASK          0xffffff37
#define BPORT1_AB_LCDCR_WRNMASK         (0xc8)
#define BPORT1_AB_LCDCR_WIDTH           32
#define BPORT1_AB_LCDPCR_WRMASK         0xf000000
#define BPORT1_AB_LCDPCR_WRNMASK        (0xf0ffffff)
#define BPORT1_AB_LCDPCR_WIDTH          32
#define BPORT1_AB_LCDCCR_WRMASK         0x87ff0000
#define BPORT1_AB_LCDCCR_WRNMASK        (0x7800ffff)
#define BPORT1_AB_LCDCCR_WIDTH          32
#define BPORT1_AB_ENFPR0_WRMASK         0xffffffff
#define BPORT1_AB_ENFPR0_WRNMASK        (0x0)
#define BPORT1_AB_ENFPR0_WIDTH          32
#define BPORT1_AB_ENFPR1_WRMASK         0xffffffff
#define BPORT1_AB_ENFPR1_WRNMASK        (0x0)
#define BPORT1_AB_ENFPR1_WIDTH          32
#define BPORT1_AB_LCDRAM0_WRMASK        0xffffffff
#define BPORT1_AB_LCDRAM0_WRNMASK       (0x0)
#define BPORT1_AB_LCDRAM0_WIDTH         32
#define BPORT1_AB_LCDRAM1_WRMASK        0xffffffff
#define BPORT1_AB_LCDRAM1_WRNMASK       (0x0)
#define BPORT1_AB_LCDRAM1_WIDTH         32
#define BPORT1_AB_LCDRAM2_WRMASK        0xffffffff
#define BPORT1_AB_LCDRAM2_WRNMASK       (0x0)
#define BPORT1_AB_LCDRAM2_WIDTH         32
#define BPORT1_AB_LCDRAM3_WRMASK        0xffffffff
#define BPORT1_AB_LCDRAM3_WRNMASK       (0x0)
#define BPORT1_AB_LCDRAM3_WIDTH         32
#define BPORT1_AB_LCDRAM4_WRMASK        0xffffffff
#define BPORT1_AB_LCDRAM4_WRNMASK       (0x0)
#define BPORT1_AB_LCDRAM4_WIDTH         32
#define BPORT1_AB_LCDRAM5_WRMASK        0xffffffff
#define BPORT1_AB_LCDRAM5_WRNMASK       (0x0)
#define BPORT1_AB_LCDRAM5_WIDTH         32
#define BPORT1_AB_LCDRAM6_WRMASK        0xffffffff
#define BPORT1_AB_LCDRAM6_WRNMASK       (0x0)
#define BPORT1_AB_LCDRAM6_WIDTH         32
#define BPORT1_AB_LCDRAM7_WRMASK        0xffffffff
#define BPORT1_AB_LCDRAM7_WRNMASK       (0x0)
#define BPORT1_AB_LCDRAM7_WIDTH         32
#define BPORT1_AB_LCDRAM8_WRMASK        0xffffffff
#define BPORT1_AB_LCDRAM8_WRNMASK       (0x0)
#define BPORT1_AB_LCDRAM8_WIDTH         32
#define BPORT1_AB_LCDRAM9_WRMASK        0xffffffff
#define BPORT1_AB_LCDRAM9_WRNMASK       (0x0)
#define BPORT1_AB_LCDRAM9_WIDTH         32
#define BPORT1_AB_LCDRAM10_WRMASK       0xffffffff
#define BPORT1_AB_LCDRAM10_WRNMASK      (0x0)
#define BPORT1_AB_LCDRAM10_WIDTH        32
#define BPORT1_AB_LCDRAM11_WRMASK       0xffffffff
#define BPORT1_AB_LCDRAM11_WRNMASK      (0x0)
#define BPORT1_AB_LCDRAM11_WIDTH        32
#define BPORT1_AB_LCDRAM12_WRMASK       0xffffffff
#define BPORT1_AB_LCDRAM12_WRNMASK      (0x0)
#define BPORT1_AB_LCDRAM12_WIDTH        32
#define BPORT1_AB_LCDRAM13_WRMASK       0xffffffff
#define BPORT1_AB_LCDRAM13_WRNMASK      (0x0)
#define BPORT1_AB_LCDRAM13_WIDTH        32
#define BPORT1_AB_LCDRAM14_WRMASK       0xffffffff
#define BPORT1_AB_LCDRAM14_WRNMASK      (0x0)
#define BPORT1_AB_LCDRAM14_WIDTH        32
#define BPORT1_AB_LCDRAM15_WRMASK       0xffffffff
#define BPORT1_AB_LCDRAM15_WRNMASK      (0x0)
#define BPORT1_AB_LCDRAM15_WIDTH        32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
