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
            Uns32 __pad0 : 16;
            Uns32 BYTE3 : 8;
            Uns32 BYTE2 : 8;
        } bits;
    } CMD1;
    union { 
        Uns32 value;
        struct {
            Uns32 BUSY_START : 1;
            Uns32 BUFNO : 2;
            Uns32 __pad3 : 5;
            Uns32 CODE : 16;
            Uns32 BYTE1 : 8;
        } bits;
    } CMD2;
    union { 
        Uns32 value;
        struct {
            Uns32 BYTE1 : 8;
            Uns32 BYTE2 : 8;
        } bits;
    } CAR;
    union { 
        Uns32 value;
        struct {
            Uns32 BYTE1 : 8;
            Uns32 BYTE2 : 8;
            Uns32 BYTE3 : 8;
            Uns32 RB0 : 1;
            Uns32 RB1 : 1;
            Uns32 __pad26 : 2;
            Uns32 CS0 : 1;
            Uns32 CS1 : 1;
        } bits;
    } RAR;
    union { 
        Uns32 value;
        struct {
            Uns32 COUNT : 16;
        } bits;
    } RPT;
    union { 
        Uns32 value;
        struct {
            Uns32 INC1 : 8;
            Uns32 INC2 : 8;
            Uns32 INC3 : 8;
        } bits;
    } RAI;
    union { 
        Uns32 value;
        struct {
            Uns32 ID4 : 8;
            Uns32 ID3 : 8;
            Uns32 ID2 : 8;
            Uns32 ID1 : 8;
        } bits;
    } SR1;
    union { 
        Uns32 value;
        struct {
            Uns32 STATUS1 : 8;
            Uns32 __pad8 : 16;
            Uns32 ID5 : 8;
        } bits;
    } SR2;
    union { 
        Uns32 value;
        struct {
            Uns32 ADDRESS : 32;
        } bits;
    } DMA1;
    union { 
        Uns32 value;
        struct {
            Uns32 ACT2 : 1;
            Uns32 ACT1 : 1;
            Uns32 __pad2 : 7;
            Uns32 OFFSET2 : 4;
            Uns32 COUNT2 : 7;
            Uns32 COUNT1 : 12;
        } bits;
    } DMACFG;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 1;
            Uns32 ADDR2 : 11;
            Uns32 __pad12 : 5;
            Uns32 ADDR1 : 11;
        } bits;
    } SWAP;
    union { 
        Uns32 value;
        struct {
            Uns32 SIZE : 13;
        } bits;
    } SECSZ;
    union { 
        Uns32 value;
        struct {
            Uns32 PAGECNT : 4;
            Uns32 AIBN : 1;
            Uns32 AIAD : 1;
            Uns32 BTMD : 1;
            Uns32 BITWIDTH : 1;
            Uns32 TIMEOUT : 5;
            Uns32 IDCNT : 3;
            Uns32 FAST : 1;
            Uns32 ECCMODE : 3;
            Uns32 DMAREQ : 1;
            Uns32 ECCSRAM : 1;
            Uns32 ECCAD : 9;
            Uns32 STOPWERR : 1;
        } bits;
    } CFG;
    union { 
        Uns32 value;
        struct {
            Uns32 ADDRESS : 32;
        } bits;
    } DMA2;
    union { 
        Uns32 value;
        struct {
            Uns32 DMABN : 2;
            Uns32 ECCBN : 2;
            Uns32 RESBN : 2;
            Uns32 __pad6 : 11;
            Uns32 IDLECLR : 1;
            Uns32 DONECLR : 1;
            Uns32 WERRCLR : 1;
            Uns32 IDLEEN : 1;
            Uns32 DONEEN : 1;
            Uns32 WERREN : 1;
            Uns32 DMABUSY : 1;
            Uns32 ECCBUSY : 1;
            Uns32 RESBUSY : 1;
            Uns32 CMDBUSY : 1;
            Uns32 WERRNS : 1;
            Uns32 __pad28 : 1;
            Uns32 IDLE : 1;
            Uns32 DONE : 1;
            Uns32 WERR : 1;
        } bits;
    } ISR;
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

#define BPORT1_AB_CMD1_WRMASK           0xffff0000
#define BPORT1_AB_CMD1_WRNMASK          (0xffff)
#define BPORT1_AB_CMD1_WIDTH            32
#define BPORT1_AB_CMD2_WRMASK           0xffffff07
#define BPORT1_AB_CMD2_WRNMASK          (0xf8)
#define BPORT1_AB_CMD2_WIDTH            32
#define BPORT1_AB_CAR_WRMASK            0xffff
#define BPORT1_AB_CAR_WRNMASK           (0xffff0000)
#define BPORT1_AB_CAR_WIDTH             32
#define BPORT1_AB_RAR_WRMASK            0x33ffffff
#define BPORT1_AB_RAR_WRNMASK           (0xcc000000)
#define BPORT1_AB_RAR_WIDTH             32
#define BPORT1_AB_RPT_WRMASK            0xffff
#define BPORT1_AB_RPT_WRNMASK           (0xffff0000)
#define BPORT1_AB_RPT_WIDTH             32
#define BPORT1_AB_RAI_WRMASK            0xffffff
#define BPORT1_AB_RAI_WRNMASK           (0xff000000)
#define BPORT1_AB_RAI_WIDTH             32
#define BPORT1_AB_SR1_WIDTH             32
#define BPORT1_AB_SR2_WIDTH             32
#define BPORT1_AB_DMA1_WRMASK           0xffffffff
#define BPORT1_AB_DMA1_WRNMASK          (0x0)
#define BPORT1_AB_DMA1_WIDTH            32
#define BPORT1_AB_DMACFG_WRMASK         0xfffffe03
#define BPORT1_AB_DMACFG_WRNMASK        (0x1fc)
#define BPORT1_AB_DMACFG_WIDTH          32
#define BPORT1_AB_SWAP_WRMASK           0xfff0ffe
#define BPORT1_AB_SWAP_WRNMASK          (0xf000f001)
#define BPORT1_AB_SWAP_WIDTH            32
#define BPORT1_AB_SECSZ_WRMASK          0x1fff
#define BPORT1_AB_SECSZ_WRNMASK         (0xffffe000)
#define BPORT1_AB_SECSZ_WIDTH           32
#define BPORT1_AB_CFG_WRMASK            0xffffffbf
#define BPORT1_AB_CFG_WRNMASK           (0x40)
#define BPORT1_AB_CFG_WIDTH             32
#define BPORT1_AB_DMA2_WRMASK           0xffffffff
#define BPORT1_AB_DMA2_WRNMASK          (0x0)
#define BPORT1_AB_DMA2_WIDTH            32
#define BPORT1_AB_ISR_WRMASK            0x7e0000
#define BPORT1_AB_ISR_WRNMASK           (0xff81ffff)
#define BPORT1_AB_ISR_WIDTH             32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
