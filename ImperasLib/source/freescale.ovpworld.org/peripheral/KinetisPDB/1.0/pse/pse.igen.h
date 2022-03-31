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
            Uns32 LDOK : 1;
            Uns32 CONT : 1;
            Uns32 MULT : 2;
            Uns32 __pad4 : 1;
            Uns32 PDBIE : 1;
            Uns32 PDBIF : 1;
            Uns32 PDBEN : 1;
            Uns32 TRGSEL : 4;
            Uns32 PRESCALER : 3;
            Uns32 DMAEN : 1;
            Uns32 SWTRIG : 1;
            Uns32 PDBEIE : 1;
            Uns32 LDMOD : 2;
        } bits;
    } SC;
    union { 
        Uns32 value;
        struct {
            Uns32 MOD : 16;
        } bits;
    } MOD;
    union { 
        Uns32 value;
        struct {
            Uns32 CNT : 16;
        } bits;
    } CNT;
    union { 
        Uns32 value;
        struct {
            Uns32 IDLY : 16;
        } bits;
    } IDLY;
    union { 
        Uns32 value;
        struct {
            Uns32 EN : 8;
            Uns32 TOS : 8;
            Uns32 BB : 8;
        } bits;
    } CH0C1;
    union { 
        Uns32 value;
        struct {
            Uns32 ERR : 8;
            Uns32 __pad8 : 8;
            Uns32 CF : 8;
        } bits;
    } CH0S;
    union { 
        Uns32 value;
        struct {
            Uns32 DLY : 16;
        } bits;
    } CH0DLY0;
    union { 
        Uns32 value;
        struct {
            Uns32 DLY : 16;
        } bits;
    } CH0DLY1;
    union { 
        Uns32 value;
        struct {
            Uns32 EN : 8;
            Uns32 TOS : 8;
            Uns32 BB : 8;
        } bits;
    } CH1C1;
    union { 
        Uns32 value;
        struct {
            Uns32 ERR : 8;
            Uns32 __pad8 : 8;
            Uns32 CF : 8;
        } bits;
    } CH1S;
    union { 
        Uns32 value;
        struct {
            Uns32 DLY : 16;
        } bits;
    } CH1DLY0;
    union { 
        Uns32 value;
        struct {
            Uns32 DLY : 16;
        } bits;
    } CH1DLY1;
    union { 
        Uns32 value;
        struct {
            Uns32 EN : 8;
            Uns32 TOS : 8;
            Uns32 BB : 8;
        } bits;
    } CH2C1;
    union { 
        Uns32 value;
        struct {
            Uns32 ERR : 8;
            Uns32 __pad8 : 8;
            Uns32 CF : 8;
        } bits;
    } CH2S;
    union { 
        Uns32 value;
        struct {
            Uns32 DLY : 16;
        } bits;
    } CH2DLY0;
    union { 
        Uns32 value;
        struct {
            Uns32 DLY : 16;
        } bits;
    } CH2DLY1;
    union { 
        Uns32 value;
        struct {
            Uns32 EN : 8;
            Uns32 TOS : 8;
            Uns32 BB : 8;
        } bits;
    } CH3C1;
    union { 
        Uns32 value;
        struct {
            Uns32 ERR : 8;
            Uns32 __pad8 : 8;
            Uns32 CF : 8;
        } bits;
    } CH3S;
    union { 
        Uns32 value;
        struct {
            Uns32 DLY : 16;
        } bits;
    } CH3DLY0;
    union { 
        Uns32 value;
        struct {
            Uns32 DLY : 16;
        } bits;
    } CH3DLY1;
    union { 
        Uns32 value;
        struct {
            Uns32 TOE : 1;
            Uns32 EXT : 1;
        } bits;
    } DACINTC0;
    union { 
        Uns32 value;
        struct {
            Uns32 INT : 16;
        } bits;
    } DACINT0;
    union { 
        Uns32 value;
        struct {
            Uns32 TOE : 1;
            Uns32 EXT : 1;
        } bits;
    } DACINTC1;
    union { 
        Uns32 value;
        struct {
            Uns32 INT : 16;
        } bits;
    } DACINT1;
    union { 
        Uns32 value;
        struct {
            Uns32 POEN : 8;
        } bits;
    } POEN;
    union { 
        Uns32 value;
        struct {
            Uns32 DLY2 : 16;
            Uns32 DLY1 : 16;
        } bits;
    } PO0DLY;
    union { 
        Uns32 value;
        struct {
            Uns32 DLY2 : 16;
            Uns32 DLY1 : 16;
        } bits;
    } PO1DLY;
    union { 
        Uns32 value;
        struct {
            Uns32 DLY2 : 16;
            Uns32 DLY1 : 16;
        } bits;
    } PO2DLY;
    union { 
        Uns32 value;
        struct {
            Uns32 DLY2 : 16;
            Uns32 DLY1 : 16;
        } bits;
    } PO3DLY;
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

#define BPORT1_AB_SC_WRMASK             0xfffef
#define BPORT1_AB_SC_WRNMASK            (0xfff00010)
#define BPORT1_AB_SC_WIDTH              32
#define BPORT1_AB_MOD_WRMASK            0xffff
#define BPORT1_AB_MOD_WRNMASK           (0xffff0000)
#define BPORT1_AB_MOD_WIDTH             32
#define BPORT1_AB_CNT_WIDTH             32
#define BPORT1_AB_IDLY_WRMASK           0xffff
#define BPORT1_AB_IDLY_WRNMASK          (0xffff0000)
#define BPORT1_AB_IDLY_WIDTH            32
#define BPORT1_AB_CH0C1_WRMASK          0xffffff
#define BPORT1_AB_CH0C1_WRNMASK         (0xff000000)
#define BPORT1_AB_CH0C1_WIDTH           32
#define BPORT1_AB_CH0S_WRMASK           0xff00ff
#define BPORT1_AB_CH0S_WRNMASK          (0xff00ff00)
#define BPORT1_AB_CH0S_WIDTH            32
#define BPORT1_AB_CH0DLY0_WRMASK        0xffff
#define BPORT1_AB_CH0DLY0_WRNMASK       (0xffff0000)
#define BPORT1_AB_CH0DLY0_WIDTH         32
#define BPORT1_AB_CH0DLY1_WRMASK        0xffff
#define BPORT1_AB_CH0DLY1_WRNMASK       (0xffff0000)
#define BPORT1_AB_CH0DLY1_WIDTH         32
#define BPORT1_AB_CH1C1_WRMASK          0xffffff
#define BPORT1_AB_CH1C1_WRNMASK         (0xff000000)
#define BPORT1_AB_CH1C1_WIDTH           32
#define BPORT1_AB_CH1S_WRMASK           0xff00ff
#define BPORT1_AB_CH1S_WRNMASK          (0xff00ff00)
#define BPORT1_AB_CH1S_WIDTH            32
#define BPORT1_AB_CH1DLY0_WRMASK        0xffff
#define BPORT1_AB_CH1DLY0_WRNMASK       (0xffff0000)
#define BPORT1_AB_CH1DLY0_WIDTH         32
#define BPORT1_AB_CH1DLY1_WRMASK        0xffff
#define BPORT1_AB_CH1DLY1_WRNMASK       (0xffff0000)
#define BPORT1_AB_CH1DLY1_WIDTH         32
#define BPORT1_AB_CH2C1_WRMASK          0xffffff
#define BPORT1_AB_CH2C1_WRNMASK         (0xff000000)
#define BPORT1_AB_CH2C1_WIDTH           32
#define BPORT1_AB_CH2S_WRMASK           0xff00ff
#define BPORT1_AB_CH2S_WRNMASK          (0xff00ff00)
#define BPORT1_AB_CH2S_WIDTH            32
#define BPORT1_AB_CH2DLY0_WRMASK        0xffff
#define BPORT1_AB_CH2DLY0_WRNMASK       (0xffff0000)
#define BPORT1_AB_CH2DLY0_WIDTH         32
#define BPORT1_AB_CH2DLY1_WRMASK        0xffff
#define BPORT1_AB_CH2DLY1_WRNMASK       (0xffff0000)
#define BPORT1_AB_CH2DLY1_WIDTH         32
#define BPORT1_AB_CH3C1_WRMASK          0xffffff
#define BPORT1_AB_CH3C1_WRNMASK         (0xff000000)
#define BPORT1_AB_CH3C1_WIDTH           32
#define BPORT1_AB_CH3S_WRMASK           0xff00ff
#define BPORT1_AB_CH3S_WRNMASK          (0xff00ff00)
#define BPORT1_AB_CH3S_WIDTH            32
#define BPORT1_AB_CH3DLY0_WRMASK        0xffff
#define BPORT1_AB_CH3DLY0_WRNMASK       (0xffff0000)
#define BPORT1_AB_CH3DLY0_WIDTH         32
#define BPORT1_AB_CH3DLY1_WRMASK        0xffff
#define BPORT1_AB_CH3DLY1_WRNMASK       (0xffff0000)
#define BPORT1_AB_CH3DLY1_WIDTH         32
#define BPORT1_AB_DACINTC0_WRMASK       0x3
#define BPORT1_AB_DACINTC0_WRNMASK      (0xfffffffc)
#define BPORT1_AB_DACINTC0_WIDTH        32
#define BPORT1_AB_DACINT0_WRMASK        0xffff
#define BPORT1_AB_DACINT0_WRNMASK       (0xffff0000)
#define BPORT1_AB_DACINT0_WIDTH         32
#define BPORT1_AB_DACINTC1_WRMASK       0x3
#define BPORT1_AB_DACINTC1_WRNMASK      (0xfffffffc)
#define BPORT1_AB_DACINTC1_WIDTH        32
#define BPORT1_AB_DACINT1_WRMASK        0xffff
#define BPORT1_AB_DACINT1_WRNMASK       (0xffff0000)
#define BPORT1_AB_DACINT1_WIDTH         32
#define BPORT1_AB_POEN_WRMASK           0xff
#define BPORT1_AB_POEN_WRNMASK          (0xffffff00)
#define BPORT1_AB_POEN_WIDTH            32
#define BPORT1_AB_PO0DLY_WRMASK         0xffffffff
#define BPORT1_AB_PO0DLY_WRNMASK        (0x0)
#define BPORT1_AB_PO0DLY_WIDTH          32
#define BPORT1_AB_PO1DLY_WRMASK         0xffffffff
#define BPORT1_AB_PO1DLY_WRNMASK        (0x0)
#define BPORT1_AB_PO1DLY_WIDTH          32
#define BPORT1_AB_PO2DLY_WRMASK         0xffffffff
#define BPORT1_AB_PO2DLY_WRNMASK        (0x0)
#define BPORT1_AB_PO2DLY_WIDTH          32
#define BPORT1_AB_PO3DLY_WRMASK         0xffffffff
#define BPORT1_AB_PO3DLY_WRNMASK        (0x0)
#define BPORT1_AB_PO3DLY_WIDTH          32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
