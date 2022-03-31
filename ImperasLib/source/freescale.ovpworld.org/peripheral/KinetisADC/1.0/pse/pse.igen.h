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
            Uns32 ADCH : 5;
            Uns32 DIFF : 1;
            Uns32 AIEN : 1;
            Uns32 COCO : 1;
        } bits;
    } SC1A;
    union { 
        Uns32 value;
        struct {
            Uns32 ADCH : 5;
            Uns32 DIFF : 1;
            Uns32 AIEN : 1;
            Uns32 COCO : 1;
        } bits;
    } SC1B;
    union { 
        Uns32 value;
        struct {
            Uns32 ADICLK : 2;
            Uns32 MODE : 2;
            Uns32 ADLSMP : 1;
            Uns32 ADIV : 2;
            Uns32 ADLPC : 1;
        } bits;
    } CFG1;
    union { 
        Uns32 value;
        struct {
            Uns32 ADLSTS : 2;
            Uns32 ADHSC : 1;
            Uns32 ADACKEN : 1;
            Uns32 MUXSEL : 1;
        } bits;
    } CFG2;
    union { 
        Uns32 value;
        struct {
            Uns32 D : 16;
        } bits;
    } RA;
    union { 
        Uns32 value;
        struct {
            Uns32 D : 16;
        } bits;
    } RB;
    union { 
        Uns32 value;
        struct {
            Uns32 CV : 16;
        } bits;
    } CV1;
    union { 
        Uns32 value;
        struct {
            Uns32 CV : 16;
        } bits;
    } CV2;
    union { 
        Uns32 value;
        struct {
            Uns32 REFSEL : 2;
            Uns32 DMAEN : 1;
            Uns32 ACREN : 1;
            Uns32 ACFGT : 1;
            Uns32 ACFE : 1;
            Uns32 ADTRG : 1;
            Uns32 ADACT : 1;
        } bits;
    } SC2;
    union { 
        Uns32 value;
        struct {
            Uns32 AVGS : 2;
            Uns32 AVGE : 1;
            Uns32 ADCO : 1;
            Uns32 __pad4 : 2;
            Uns32 CALF : 1;
            Uns32 CAL : 1;
        } bits;
    } SC3;
    union { 
        Uns32 value;
        struct {
            Uns32 OFS : 16;
        } bits;
    } OFS;
    union { 
        Uns32 value;
        struct {
            Uns32 PG : 16;
        } bits;
    } PG;
    union { 
        Uns32 value;
        struct {
            Uns32 MG : 16;
        } bits;
    } MG;
    union { 
        Uns32 value;
        struct {
            Uns32 CLPD : 6;
        } bits;
    } CLPD;
    union { 
        Uns32 value;
        struct {
            Uns32 CLPS : 6;
        } bits;
    } CLPS;
    union { 
        Uns32 value;
        struct {
            Uns32 CLP4 : 10;
        } bits;
    } CLP4;
    union { 
        Uns32 value;
        struct {
            Uns32 CLP3 : 9;
        } bits;
    } CLP3;
    union { 
        Uns32 value;
        struct {
            Uns32 CLP2 : 8;
        } bits;
    } CLP2;
    union { 
        Uns32 value;
        struct {
            Uns32 CLP1 : 7;
        } bits;
    } CLP1;
    union { 
        Uns32 value;
        struct {
            Uns32 CLP0 : 6;
        } bits;
    } CLP0;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 14;
            Uns32 PGAOFSM : 1;
            Uns32 __pad15 : 1;
            Uns32 PGAG : 4;
            Uns32 PGALPb : 1;
            Uns32 PGACHPb : 1;
            Uns32 __pad22 : 1;
            Uns32 PGAEN : 1;
        } bits;
    } PGA;
    union { 
        Uns32 value;
        struct {
            Uns32 CLMD : 6;
        } bits;
    } CLMD;
    union { 
        Uns32 value;
        struct {
            Uns32 CLMS : 6;
        } bits;
    } CLMS;
    union { 
        Uns32 value;
        struct {
            Uns32 CLM4 : 10;
        } bits;
    } CLM4;
    union { 
        Uns32 value;
        struct {
            Uns32 CLM3 : 9;
        } bits;
    } CLM3;
    union { 
        Uns32 value;
        struct {
            Uns32 CLM2 : 8;
        } bits;
    } CLM2;
    union { 
        Uns32 value;
        struct {
            Uns32 CLM1 : 7;
        } bits;
    } CLM1;
    union { 
        Uns32 value;
        struct {
            Uns32 CLM0 : 6;
        } bits;
    } CLM0;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          Reset;
    ppmNetHandle          AltClk;
    ppmNetHandle          HwTrig;
    ppmNetHandle          AdIn;
    ppmNetHandle          Vrefsh;
    ppmNetHandle          Vrefsl;
    ppmNetHandle          AdInId;
    ppmNetHandle          Interrupt;
    ppmNetHandle          DmaReq;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(altClkCB);
PPM_NET_CB(hwTrigCB);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_SC1A_WRMASK           0x7f
#define BPORT1_AB_SC1A_WRNMASK          (0xffffff80)
#define BPORT1_AB_SC1A_WIDTH            32
#define BPORT1_AB_SC1B_WRMASK           0x7f
#define BPORT1_AB_SC1B_WRNMASK          (0xffffff80)
#define BPORT1_AB_SC1B_WIDTH            32
#define BPORT1_AB_CFG1_WRMASK           0xff
#define BPORT1_AB_CFG1_WRNMASK          (0xffffff00)
#define BPORT1_AB_CFG1_WIDTH            32
#define BPORT1_AB_CFG2_WRMASK           0x1f
#define BPORT1_AB_CFG2_WRNMASK          (0xffffffe0)
#define BPORT1_AB_CFG2_WIDTH            32
#define BPORT1_AB_RA_WIDTH              32
#define BPORT1_AB_RB_WIDTH              32
#define BPORT1_AB_CV1_WRMASK            0xffff
#define BPORT1_AB_CV1_WRNMASK           (0xffff0000)
#define BPORT1_AB_CV1_WIDTH             32
#define BPORT1_AB_CV2_WRMASK            0xffff
#define BPORT1_AB_CV2_WRNMASK           (0xffff0000)
#define BPORT1_AB_CV2_WIDTH             32
#define BPORT1_AB_SC2_WRMASK            0x7f
#define BPORT1_AB_SC2_WRNMASK           (0xffffff80)
#define BPORT1_AB_SC2_WIDTH             32
#define BPORT1_AB_SC3_WRMASK            0x8f
#define BPORT1_AB_SC3_WRNMASK           (0xffffff70)
#define BPORT1_AB_SC3_WIDTH             32
#define BPORT1_AB_OFS_WRMASK            0xffff
#define BPORT1_AB_OFS_WRNMASK           (0xffff0000)
#define BPORT1_AB_OFS_WIDTH             32
#define BPORT1_AB_PG_WRMASK             0xffff
#define BPORT1_AB_PG_WRNMASK            (0xffff0000)
#define BPORT1_AB_PG_WIDTH              32
#define BPORT1_AB_MG_WRMASK             0xffff
#define BPORT1_AB_MG_WRNMASK            (0xffff0000)
#define BPORT1_AB_MG_WIDTH              32
#define BPORT1_AB_CLPD_WRMASK           0x3f
#define BPORT1_AB_CLPD_WRNMASK          (0xffffffc0)
#define BPORT1_AB_CLPD_WIDTH            32
#define BPORT1_AB_CLPS_WRMASK           0x3f
#define BPORT1_AB_CLPS_WRNMASK          (0xffffffc0)
#define BPORT1_AB_CLPS_WIDTH            32
#define BPORT1_AB_CLP4_WRMASK           0x3ff
#define BPORT1_AB_CLP4_WRNMASK          (0xfffffc00)
#define BPORT1_AB_CLP4_WIDTH            32
#define BPORT1_AB_CLP3_WRMASK           0x1ff
#define BPORT1_AB_CLP3_WRNMASK          (0xfffffe00)
#define BPORT1_AB_CLP3_WIDTH            32
#define BPORT1_AB_CLP2_WRMASK           0xff
#define BPORT1_AB_CLP2_WRNMASK          (0xffffff00)
#define BPORT1_AB_CLP2_WIDTH            32
#define BPORT1_AB_CLP1_WRMASK           0x7f
#define BPORT1_AB_CLP1_WRNMASK          (0xffffff80)
#define BPORT1_AB_CLP1_WIDTH            32
#define BPORT1_AB_CLP0_WRMASK           0x3f
#define BPORT1_AB_CLP0_WRNMASK          (0xffffffc0)
#define BPORT1_AB_CLP0_WIDTH            32
#define BPORT1_AB_PGA_WRMASK            0xbf4000
#define BPORT1_AB_PGA_WRNMASK           (0xff40bfff)
#define BPORT1_AB_PGA_WIDTH             32
#define BPORT1_AB_CLMD_WRMASK           0x3f
#define BPORT1_AB_CLMD_WRNMASK          (0xffffffc0)
#define BPORT1_AB_CLMD_WIDTH            32
#define BPORT1_AB_CLMS_WRMASK           0x3f
#define BPORT1_AB_CLMS_WRNMASK          (0xffffffc0)
#define BPORT1_AB_CLMS_WIDTH            32
#define BPORT1_AB_CLM4_WRMASK           0x3ff
#define BPORT1_AB_CLM4_WRNMASK          (0xfffffc00)
#define BPORT1_AB_CLM4_WIDTH            32
#define BPORT1_AB_CLM3_WRMASK           0x1ff
#define BPORT1_AB_CLM3_WRNMASK          (0xfffffe00)
#define BPORT1_AB_CLM3_WIDTH            32
#define BPORT1_AB_CLM2_WRMASK           0xff
#define BPORT1_AB_CLM2_WRNMASK          (0xffffff00)
#define BPORT1_AB_CLM2_WIDTH            32
#define BPORT1_AB_CLM1_WRMASK           0x7f
#define BPORT1_AB_CLM1_WRNMASK          (0xffffff80)
#define BPORT1_AB_CLM1_WIDTH            32
#define BPORT1_AB_CLM0_WRMASK           0x3f
#define BPORT1_AB_CLM0_WRNMASK          (0xffffffc0)
#define BPORT1_AB_CLM0_WIDTH            32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
