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
            Uns32 M0AP : 2;
            Uns32 M1AP : 2;
            Uns32 M2AP : 2;
            Uns32 M3AP : 2;
            Uns32 M4AP : 2;
            Uns32 M5AP : 2;
            Uns32 M6AP : 2;
            Uns32 M7AP : 2;
            Uns32 M0PFD : 1;
            Uns32 M1PFD : 1;
            Uns32 M2PFD : 1;
            Uns32 M3PFD : 1;
            Uns32 M4PFD : 1;
            Uns32 M5PFD : 1;
            Uns32 M6PFD : 1;
            Uns32 M7PFD : 1;
        } bits;
    } PFAPR;
    union { 
        Uns32 value;
        struct {
            Uns32 B01SEBE : 1;
            Uns32 B01IPE : 1;
            Uns32 B01DPE : 1;
            Uns32 B01ICE : 1;
            Uns32 B01DCE : 1;
            Uns32 CRC : 3;
            Uns32 __pad8 : 9;
            Uns32 B01MW : 2;
            Uns32 S_B_INV : 1;
            Uns32 CINV_WAY : 4;
            Uns32 CLCK_WAY : 4;
            Uns32 B01RWSC : 4;
        } bits;
    } PFB01CR;
    union { 
        Uns32 value;
        struct {
            Uns32 B23SEBE : 1;
            Uns32 B23IPE : 1;
            Uns32 B23DPE : 1;
            Uns32 B23ICE : 1;
            Uns32 B23DCE : 1;
            Uns32 __pad5 : 12;
            Uns32 B23MW : 2;
            Uns32 __pad19 : 9;
            Uns32 B23RWSC : 4;
        } bits;
    } PFB23CR;
    union { 
        Uns32 value;
        struct {
            Uns32 valid : 1;
            Uns32 __pad1 : 5;
            Uns32 tag : 14;
        } bits;
    } TAGVDW0S0;
    union { 
        Uns32 value;
        struct {
            Uns32 valid : 1;
            Uns32 __pad1 : 5;
            Uns32 tag : 14;
        } bits;
    } TAGVDW0S1;
    union { 
        Uns32 value;
        struct {
            Uns32 valid : 1;
            Uns32 __pad1 : 5;
            Uns32 tag : 14;
        } bits;
    } TAGVDW0S2;
    union { 
        Uns32 value;
        struct {
            Uns32 valid : 1;
            Uns32 __pad1 : 5;
            Uns32 tag : 14;
        } bits;
    } TAGVDW0S3;
    union { 
        Uns32 value;
        struct {
            Uns32 valid : 1;
            Uns32 __pad1 : 5;
            Uns32 tag : 14;
        } bits;
    } TAGVDW1S0;
    union { 
        Uns32 value;
        struct {
            Uns32 valid : 1;
            Uns32 __pad1 : 5;
            Uns32 tag : 14;
        } bits;
    } TAGVDW1S1;
    union { 
        Uns32 value;
        struct {
            Uns32 valid : 1;
            Uns32 __pad1 : 5;
            Uns32 tag : 14;
        } bits;
    } TAGVDW1S2;
    union { 
        Uns32 value;
        struct {
            Uns32 valid : 1;
            Uns32 __pad1 : 5;
            Uns32 tag : 14;
        } bits;
    } TAGVDW1S3;
    union { 
        Uns32 value;
        struct {
            Uns32 valid : 1;
            Uns32 __pad1 : 5;
            Uns32 tag : 14;
        } bits;
    } TAGVDW2S0;
    union { 
        Uns32 value;
        struct {
            Uns32 valid : 1;
            Uns32 __pad1 : 5;
            Uns32 tag : 14;
        } bits;
    } TAGVDW2S1;
    union { 
        Uns32 value;
        struct {
            Uns32 valid : 1;
            Uns32 __pad1 : 5;
            Uns32 tag : 14;
        } bits;
    } TAGVDW2S2;
    union { 
        Uns32 value;
        struct {
            Uns32 valid : 1;
            Uns32 __pad1 : 5;
            Uns32 tag : 14;
        } bits;
    } TAGVDW2S3;
    union { 
        Uns32 value;
        struct {
            Uns32 valid : 1;
            Uns32 __pad1 : 5;
            Uns32 tag : 14;
        } bits;
    } TAGVDW3S0;
    union { 
        Uns32 value;
        struct {
            Uns32 valid : 1;
            Uns32 __pad1 : 5;
            Uns32 tag : 14;
        } bits;
    } TAGVDW3S1;
    union { 
        Uns32 value;
        struct {
            Uns32 valid : 1;
            Uns32 __pad1 : 5;
            Uns32 tag : 14;
        } bits;
    } TAGVDW3S2;
    union { 
        Uns32 value;
        struct {
            Uns32 valid : 1;
            Uns32 __pad1 : 5;
            Uns32 tag : 14;
        } bits;
    } TAGVDW3S3;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW0S0UM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW0S0MU;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW0S0ML;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW0S0LM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW0S1UM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW0S1MU;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW0S1ML;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW0S1LM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW0S2UM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW0S2MU;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW0S2ML;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW0S2LM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW0S3UM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW0S3MU;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW0S3ML;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW0S3LM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW1S0UM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW1S0MU;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW1S0ML;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW1S0LM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW1S1UM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW1S1MU;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW1S1ML;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW1S1LM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW1S2UM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW1S2MU;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW1S2ML;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW1S2LM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW1S3UM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW1S3MU;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW1S3ML;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW1S3LM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW2S0UM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW2S0MU;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW2S0ML;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW2S0LM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW2S1UM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW2S1MU;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW2S1ML;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW2S1LM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW2S2UM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW2S2MU;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW2S2ML;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW2S2LM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW2S3UM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW2S3MU;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW2S3ML;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW2S3LM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW3S0UM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW3S0MU;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW3S0ML;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW3S0LM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW3S1UM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW3S1MU;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW3S1ML;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW3S1LM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW3S2UM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW3S2MU;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW3S2ML;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW3S2LM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW3S3UM;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW3S3MU;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW3S3ML;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 32;
        } bits;
    } DATAW3S3LM;
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

#define BPORT1_AB_PFAPR_WRMASK          0xffffff
#define BPORT1_AB_PFAPR_WRNMASK         (0xff000000)
#define BPORT1_AB_PFAPR_WIDTH           32
#define BPORT1_AB_PFB01CR_WRMASK        0xf0800ff
#define BPORT1_AB_PFB01CR_WRNMASK       (0xf0f7ff00)
#define BPORT1_AB_PFB01CR_WIDTH         32
#define BPORT1_AB_PFB23CR_WRMASK        0x1f
#define BPORT1_AB_PFB23CR_WRNMASK       (0xffffffe0)
#define BPORT1_AB_PFB23CR_WIDTH         32
#define BPORT1_AB_TAGVDW0S0_WRMASK      0xfffc1
#define BPORT1_AB_TAGVDW0S0_WRNMASK     (0xfff0003e)
#define BPORT1_AB_TAGVDW0S0_WIDTH       32
#define BPORT1_AB_TAGVDW0S1_WRMASK      0xfffc1
#define BPORT1_AB_TAGVDW0S1_WRNMASK     (0xfff0003e)
#define BPORT1_AB_TAGVDW0S1_WIDTH       32
#define BPORT1_AB_TAGVDW0S2_WRMASK      0xfffc1
#define BPORT1_AB_TAGVDW0S2_WRNMASK     (0xfff0003e)
#define BPORT1_AB_TAGVDW0S2_WIDTH       32
#define BPORT1_AB_TAGVDW0S3_WRMASK      0xfffc1
#define BPORT1_AB_TAGVDW0S3_WRNMASK     (0xfff0003e)
#define BPORT1_AB_TAGVDW0S3_WIDTH       32
#define BPORT1_AB_TAGVDW1S0_WRMASK      0xfffc1
#define BPORT1_AB_TAGVDW1S0_WRNMASK     (0xfff0003e)
#define BPORT1_AB_TAGVDW1S0_WIDTH       32
#define BPORT1_AB_TAGVDW1S1_WRMASK      0xfffc1
#define BPORT1_AB_TAGVDW1S1_WRNMASK     (0xfff0003e)
#define BPORT1_AB_TAGVDW1S1_WIDTH       32
#define BPORT1_AB_TAGVDW1S2_WRMASK      0xfffc1
#define BPORT1_AB_TAGVDW1S2_WRNMASK     (0xfff0003e)
#define BPORT1_AB_TAGVDW1S2_WIDTH       32
#define BPORT1_AB_TAGVDW1S3_WRMASK      0xfffc1
#define BPORT1_AB_TAGVDW1S3_WRNMASK     (0xfff0003e)
#define BPORT1_AB_TAGVDW1S3_WIDTH       32
#define BPORT1_AB_TAGVDW2S0_WRMASK      0xfffc1
#define BPORT1_AB_TAGVDW2S0_WRNMASK     (0xfff0003e)
#define BPORT1_AB_TAGVDW2S0_WIDTH       32
#define BPORT1_AB_TAGVDW2S1_WRMASK      0xfffc1
#define BPORT1_AB_TAGVDW2S1_WRNMASK     (0xfff0003e)
#define BPORT1_AB_TAGVDW2S1_WIDTH       32
#define BPORT1_AB_TAGVDW2S2_WRMASK      0xfffc1
#define BPORT1_AB_TAGVDW2S2_WRNMASK     (0xfff0003e)
#define BPORT1_AB_TAGVDW2S2_WIDTH       32
#define BPORT1_AB_TAGVDW2S3_WRMASK      0xfffc1
#define BPORT1_AB_TAGVDW2S3_WRNMASK     (0xfff0003e)
#define BPORT1_AB_TAGVDW2S3_WIDTH       32
#define BPORT1_AB_TAGVDW3S0_WRMASK      0xfffc1
#define BPORT1_AB_TAGVDW3S0_WRNMASK     (0xfff0003e)
#define BPORT1_AB_TAGVDW3S0_WIDTH       32
#define BPORT1_AB_TAGVDW3S1_WRMASK      0xfffc1
#define BPORT1_AB_TAGVDW3S1_WRNMASK     (0xfff0003e)
#define BPORT1_AB_TAGVDW3S1_WIDTH       32
#define BPORT1_AB_TAGVDW3S2_WRMASK      0xfffc1
#define BPORT1_AB_TAGVDW3S2_WRNMASK     (0xfff0003e)
#define BPORT1_AB_TAGVDW3S2_WIDTH       32
#define BPORT1_AB_TAGVDW3S3_WRMASK      0xfffc1
#define BPORT1_AB_TAGVDW3S3_WRNMASK     (0xfff0003e)
#define BPORT1_AB_TAGVDW3S3_WIDTH       32
#define BPORT1_AB_DATAW0S0UM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW0S0UM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW0S0UM_WIDTH      32
#define BPORT1_AB_DATAW0S0MU_WRMASK     0xffffffff
#define BPORT1_AB_DATAW0S0MU_WRNMASK    (0x0)
#define BPORT1_AB_DATAW0S0MU_WIDTH      32
#define BPORT1_AB_DATAW0S0ML_WRMASK     0xffffffff
#define BPORT1_AB_DATAW0S0ML_WRNMASK    (0x0)
#define BPORT1_AB_DATAW0S0ML_WIDTH      32
#define BPORT1_AB_DATAW0S0LM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW0S0LM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW0S0LM_WIDTH      32
#define BPORT1_AB_DATAW0S1UM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW0S1UM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW0S1UM_WIDTH      32
#define BPORT1_AB_DATAW0S1MU_WRMASK     0xffffffff
#define BPORT1_AB_DATAW0S1MU_WRNMASK    (0x0)
#define BPORT1_AB_DATAW0S1MU_WIDTH      32
#define BPORT1_AB_DATAW0S1ML_WRMASK     0xffffffff
#define BPORT1_AB_DATAW0S1ML_WRNMASK    (0x0)
#define BPORT1_AB_DATAW0S1ML_WIDTH      32
#define BPORT1_AB_DATAW0S1LM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW0S1LM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW0S1LM_WIDTH      32
#define BPORT1_AB_DATAW0S2UM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW0S2UM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW0S2UM_WIDTH      32
#define BPORT1_AB_DATAW0S2MU_WRMASK     0xffffffff
#define BPORT1_AB_DATAW0S2MU_WRNMASK    (0x0)
#define BPORT1_AB_DATAW0S2MU_WIDTH      32
#define BPORT1_AB_DATAW0S2ML_WRMASK     0xffffffff
#define BPORT1_AB_DATAW0S2ML_WRNMASK    (0x0)
#define BPORT1_AB_DATAW0S2ML_WIDTH      32
#define BPORT1_AB_DATAW0S2LM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW0S2LM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW0S2LM_WIDTH      32
#define BPORT1_AB_DATAW0S3UM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW0S3UM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW0S3UM_WIDTH      32
#define BPORT1_AB_DATAW0S3MU_WRMASK     0xffffffff
#define BPORT1_AB_DATAW0S3MU_WRNMASK    (0x0)
#define BPORT1_AB_DATAW0S3MU_WIDTH      32
#define BPORT1_AB_DATAW0S3ML_WRMASK     0xffffffff
#define BPORT1_AB_DATAW0S3ML_WRNMASK    (0x0)
#define BPORT1_AB_DATAW0S3ML_WIDTH      32
#define BPORT1_AB_DATAW0S3LM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW0S3LM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW0S3LM_WIDTH      32
#define BPORT1_AB_DATAW1S0UM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW1S0UM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW1S0UM_WIDTH      32
#define BPORT1_AB_DATAW1S0MU_WRMASK     0xffffffff
#define BPORT1_AB_DATAW1S0MU_WRNMASK    (0x0)
#define BPORT1_AB_DATAW1S0MU_WIDTH      32
#define BPORT1_AB_DATAW1S0ML_WRMASK     0xffffffff
#define BPORT1_AB_DATAW1S0ML_WRNMASK    (0x0)
#define BPORT1_AB_DATAW1S0ML_WIDTH      32
#define BPORT1_AB_DATAW1S0LM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW1S0LM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW1S0LM_WIDTH      32
#define BPORT1_AB_DATAW1S1UM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW1S1UM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW1S1UM_WIDTH      32
#define BPORT1_AB_DATAW1S1MU_WRMASK     0xffffffff
#define BPORT1_AB_DATAW1S1MU_WRNMASK    (0x0)
#define BPORT1_AB_DATAW1S1MU_WIDTH      32
#define BPORT1_AB_DATAW1S1ML_WRMASK     0xffffffff
#define BPORT1_AB_DATAW1S1ML_WRNMASK    (0x0)
#define BPORT1_AB_DATAW1S1ML_WIDTH      32
#define BPORT1_AB_DATAW1S1LM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW1S1LM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW1S1LM_WIDTH      32
#define BPORT1_AB_DATAW1S2UM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW1S2UM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW1S2UM_WIDTH      32
#define BPORT1_AB_DATAW1S2MU_WRMASK     0xffffffff
#define BPORT1_AB_DATAW1S2MU_WRNMASK    (0x0)
#define BPORT1_AB_DATAW1S2MU_WIDTH      32
#define BPORT1_AB_DATAW1S2ML_WRMASK     0xffffffff
#define BPORT1_AB_DATAW1S2ML_WRNMASK    (0x0)
#define BPORT1_AB_DATAW1S2ML_WIDTH      32
#define BPORT1_AB_DATAW1S2LM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW1S2LM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW1S2LM_WIDTH      32
#define BPORT1_AB_DATAW1S3UM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW1S3UM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW1S3UM_WIDTH      32
#define BPORT1_AB_DATAW1S3MU_WRMASK     0xffffffff
#define BPORT1_AB_DATAW1S3MU_WRNMASK    (0x0)
#define BPORT1_AB_DATAW1S3MU_WIDTH      32
#define BPORT1_AB_DATAW1S3ML_WRMASK     0xffffffff
#define BPORT1_AB_DATAW1S3ML_WRNMASK    (0x0)
#define BPORT1_AB_DATAW1S3ML_WIDTH      32
#define BPORT1_AB_DATAW1S3LM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW1S3LM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW1S3LM_WIDTH      32
#define BPORT1_AB_DATAW2S0UM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW2S0UM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW2S0UM_WIDTH      32
#define BPORT1_AB_DATAW2S0MU_WRMASK     0xffffffff
#define BPORT1_AB_DATAW2S0MU_WRNMASK    (0x0)
#define BPORT1_AB_DATAW2S0MU_WIDTH      32
#define BPORT1_AB_DATAW2S0ML_WRMASK     0xffffffff
#define BPORT1_AB_DATAW2S0ML_WRNMASK    (0x0)
#define BPORT1_AB_DATAW2S0ML_WIDTH      32
#define BPORT1_AB_DATAW2S0LM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW2S0LM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW2S0LM_WIDTH      32
#define BPORT1_AB_DATAW2S1UM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW2S1UM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW2S1UM_WIDTH      32
#define BPORT1_AB_DATAW2S1MU_WRMASK     0xffffffff
#define BPORT1_AB_DATAW2S1MU_WRNMASK    (0x0)
#define BPORT1_AB_DATAW2S1MU_WIDTH      32
#define BPORT1_AB_DATAW2S1ML_WRMASK     0xffffffff
#define BPORT1_AB_DATAW2S1ML_WRNMASK    (0x0)
#define BPORT1_AB_DATAW2S1ML_WIDTH      32
#define BPORT1_AB_DATAW2S1LM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW2S1LM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW2S1LM_WIDTH      32
#define BPORT1_AB_DATAW2S2UM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW2S2UM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW2S2UM_WIDTH      32
#define BPORT1_AB_DATAW2S2MU_WRMASK     0xffffffff
#define BPORT1_AB_DATAW2S2MU_WRNMASK    (0x0)
#define BPORT1_AB_DATAW2S2MU_WIDTH      32
#define BPORT1_AB_DATAW2S2ML_WRMASK     0xffffffff
#define BPORT1_AB_DATAW2S2ML_WRNMASK    (0x0)
#define BPORT1_AB_DATAW2S2ML_WIDTH      32
#define BPORT1_AB_DATAW2S2LM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW2S2LM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW2S2LM_WIDTH      32
#define BPORT1_AB_DATAW2S3UM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW2S3UM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW2S3UM_WIDTH      32
#define BPORT1_AB_DATAW2S3MU_WRMASK     0xffffffff
#define BPORT1_AB_DATAW2S3MU_WRNMASK    (0x0)
#define BPORT1_AB_DATAW2S3MU_WIDTH      32
#define BPORT1_AB_DATAW2S3ML_WRMASK     0xffffffff
#define BPORT1_AB_DATAW2S3ML_WRNMASK    (0x0)
#define BPORT1_AB_DATAW2S3ML_WIDTH      32
#define BPORT1_AB_DATAW2S3LM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW2S3LM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW2S3LM_WIDTH      32
#define BPORT1_AB_DATAW3S0UM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW3S0UM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW3S0UM_WIDTH      32
#define BPORT1_AB_DATAW3S0MU_WRMASK     0xffffffff
#define BPORT1_AB_DATAW3S0MU_WRNMASK    (0x0)
#define BPORT1_AB_DATAW3S0MU_WIDTH      32
#define BPORT1_AB_DATAW3S0ML_WRMASK     0xffffffff
#define BPORT1_AB_DATAW3S0ML_WRNMASK    (0x0)
#define BPORT1_AB_DATAW3S0ML_WIDTH      32
#define BPORT1_AB_DATAW3S0LM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW3S0LM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW3S0LM_WIDTH      32
#define BPORT1_AB_DATAW3S1UM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW3S1UM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW3S1UM_WIDTH      32
#define BPORT1_AB_DATAW3S1MU_WRMASK     0xffffffff
#define BPORT1_AB_DATAW3S1MU_WRNMASK    (0x0)
#define BPORT1_AB_DATAW3S1MU_WIDTH      32
#define BPORT1_AB_DATAW3S1ML_WRMASK     0xffffffff
#define BPORT1_AB_DATAW3S1ML_WRNMASK    (0x0)
#define BPORT1_AB_DATAW3S1ML_WIDTH      32
#define BPORT1_AB_DATAW3S1LM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW3S1LM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW3S1LM_WIDTH      32
#define BPORT1_AB_DATAW3S2UM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW3S2UM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW3S2UM_WIDTH      32
#define BPORT1_AB_DATAW3S2MU_WRMASK     0xffffffff
#define BPORT1_AB_DATAW3S2MU_WRNMASK    (0x0)
#define BPORT1_AB_DATAW3S2MU_WIDTH      32
#define BPORT1_AB_DATAW3S2ML_WRMASK     0xffffffff
#define BPORT1_AB_DATAW3S2ML_WRNMASK    (0x0)
#define BPORT1_AB_DATAW3S2ML_WIDTH      32
#define BPORT1_AB_DATAW3S2LM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW3S2LM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW3S2LM_WIDTH      32
#define BPORT1_AB_DATAW3S3UM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW3S3UM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW3S3UM_WIDTH      32
#define BPORT1_AB_DATAW3S3MU_WRMASK     0xffffffff
#define BPORT1_AB_DATAW3S3MU_WRNMASK    (0x0)
#define BPORT1_AB_DATAW3S3MU_WIDTH      32
#define BPORT1_AB_DATAW3S3ML_WRMASK     0xffffffff
#define BPORT1_AB_DATAW3S3ML_WRNMASK    (0x0)
#define BPORT1_AB_DATAW3S3ML_WIDTH      32
#define BPORT1_AB_DATAW3S3LM_WRMASK     0xffffffff
#define BPORT1_AB_DATAW3S3LM_WRNMASK    (0x0)
#define BPORT1_AB_DATAW3S3LM_WIDTH      32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
