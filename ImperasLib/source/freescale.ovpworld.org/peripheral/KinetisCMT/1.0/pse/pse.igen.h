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
            Uns8 PH : 8;
        } bits;
    } CGH1;
    union { 
        Uns8 value;
        struct {
            Uns8 PL : 8;
        } bits;
    } CGL1;
    union { 
        Uns8 value;
        struct {
            Uns8 SH : 8;
        } bits;
    } CGH2;
    union { 
        Uns8 value;
        struct {
            Uns8 SL : 8;
        } bits;
    } CGL2;
    union { 
        Uns8 value;
        struct {
            Uns8 __pad0 : 5;
            Uns8 IROPEN : 1;
            Uns8 CMTPOL : 1;
            Uns8 IROL : 1;
        } bits;
    } OC;
    union { 
        Uns8 value;
        struct {
            Uns8 MCGEN : 1;
            Uns8 EOCIE : 1;
            Uns8 FSK : 1;
            Uns8 BASE : 1;
            Uns8 EXSPC : 1;
            Uns8 CMTDIV : 2;
            Uns8 EOCF : 1;
        } bits;
    } MSC;
    union { 
        Uns8 value;
        struct {
            Uns8 MB : 8;
        } bits;
    } CMD1;
    union { 
        Uns8 value;
        struct {
            Uns8 MB : 8;
        } bits;
    } CMD2;
    union { 
        Uns8 value;
        struct {
            Uns8 SB : 8;
        } bits;
    } CMD3;
    union { 
        Uns8 value;
        struct {
            Uns8 SB : 8;
        } bits;
    } CMD4;
    union { 
        Uns8 value;
        struct {
            Uns8 PPSDIV : 4;
        } bits;
    } PPS;
    union { 
        Uns8 value;
        struct {
            Uns8 DMA : 1;
        } bits;
    } DMA;
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

#define BPORT1_AB_CGH1_WRMASK           0xff
#define BPORT1_AB_CGH1_WRNMASK          (0x0)
#define BPORT1_AB_CGH1_WIDTH            8
#define BPORT1_AB_CGL1_WRMASK           0xff
#define BPORT1_AB_CGL1_WRNMASK          (0x0)
#define BPORT1_AB_CGL1_WIDTH            8
#define BPORT1_AB_CGH2_WRMASK           0xff
#define BPORT1_AB_CGH2_WRNMASK          (0x0)
#define BPORT1_AB_CGH2_WIDTH            8
#define BPORT1_AB_CGL2_WRMASK           0xff
#define BPORT1_AB_CGL2_WRNMASK          (0x0)
#define BPORT1_AB_CGL2_WIDTH            8
#define BPORT1_AB_OC_WRMASK             0xe0
#define BPORT1_AB_OC_WRNMASK            (0x1f)
#define BPORT1_AB_OC_WIDTH              8
#define BPORT1_AB_MSC_WRMASK            0x7f
#define BPORT1_AB_MSC_WRNMASK           (0x80)
#define BPORT1_AB_MSC_WIDTH             8
#define BPORT1_AB_CMD1_WRMASK           0xff
#define BPORT1_AB_CMD1_WRNMASK          (0x0)
#define BPORT1_AB_CMD1_WIDTH            8
#define BPORT1_AB_CMD2_WRMASK           0xff
#define BPORT1_AB_CMD2_WRNMASK          (0x0)
#define BPORT1_AB_CMD2_WIDTH            8
#define BPORT1_AB_CMD3_WRMASK           0xff
#define BPORT1_AB_CMD3_WRNMASK          (0x0)
#define BPORT1_AB_CMD3_WIDTH            8
#define BPORT1_AB_CMD4_WRMASK           0xff
#define BPORT1_AB_CMD4_WRNMASK          (0x0)
#define BPORT1_AB_CMD4_WIDTH            8
#define BPORT1_AB_PPS_WRMASK            0xf
#define BPORT1_AB_PPS_WRNMASK           (0xf0)
#define BPORT1_AB_PPS_WIDTH             8
#define BPORT1_AB_DMA_WRMASK            0x1
#define BPORT1_AB_DMA_WRNMASK           (0xfe)
#define BPORT1_AB_DMA_WIDTH             8

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
