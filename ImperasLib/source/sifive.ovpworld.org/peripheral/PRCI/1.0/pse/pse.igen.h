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

typedef struct bport1_REG_dataS { 
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 30;
            Uns32 XOSC_RDY : 1;
            Uns32 XOSCCFG_EN : 1;
        } bits;
    } hfxosccfg;
    union { 
        Uns32 value;
        struct {
            Uns32 DIVR : 6;
            Uns32 DIVF : 9;
            Uns32 DIVQ : 3;
            Uns32 RANGE : 3;
            Uns32 __pad21 : 3;
            Uns32 BYPASS : 1;
            Uns32 FSE : 1;
            Uns32 __pad26 : 5;
            Uns32 LOCK : 1;
        } bits;
    } corepllcfg0;
    union { 
        Uns32 value;
        struct {
            Uns32 DIVR : 6;
            Uns32 DIVF : 9;
            Uns32 DIVQ : 3;
            Uns32 RANGE : 3;
            Uns32 __pad21 : 3;
            Uns32 BYPASS : 1;
            Uns32 FSE : 1;
            Uns32 __pad26 : 5;
            Uns32 LOCK : 1;
        } bits;
    } ddrpllcfg0;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 31;
            Uns32 CKE : 1;
        } bits;
    } ddrpllcfg1;
    union { 
        Uns32 value;
        struct {
            Uns32 DIVR : 6;
            Uns32 DIVF : 9;
            Uns32 DIVQ : 3;
            Uns32 RANGE : 3;
            Uns32 __pad21 : 3;
            Uns32 BYPASS : 1;
            Uns32 FSE : 1;
            Uns32 __pad26 : 5;
            Uns32 LOCK : 1;
        } bits;
    } gemgxlpllcfg0;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 24;
            Uns32 CKE : 1;
        } bits;
    } gemgxlpllcfg1;
    union { 
        Uns32 value;
        struct {
            Uns32 CORECLKSEL : 1;
        } bits;
    } coreclksel;
    union { 
        Uns32 value;
        struct {
            Uns32 DDR_CTRL_RST_N : 1;
            Uns32 DDR_AXI_RST_N : 1;
            Uns32 DDR_AHB_RST_N : 1;
            Uns32 DDR_PHY_RST_N : 1;
            Uns32 __pad4 : 1;
            Uns32 GEMGXL_RST_N : 1;
        } bits;
    } devicesresetreg;
} bport1_REG_dataT, *bport1_REG_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_REG_dataT bport1_REG_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          reset;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_WRITE_CB(hfxosccfgWrite);
PPM_NET_CB(resetCB);
PPM_READ_CB(reservedRD);
PPM_WRITE_CB(reservedWR);
PPM_NET_CB(reset_reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


///////////////////////////////// Local memory /////////////////////////////////

// To access local memory bport1/REG/rsvd : (for example)
// char value = ((char*)handles.bport1)[BPORT1_REG_RSVD_OFFSET + myAddress];

#define BPORT1_REG_RSVD_OFFSET          0x0
#define BPORT1_REG_RSVD_SIZE            0x1000

////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_REG_HFXOSCCFG_WRMASK     0x80000000
#define BPORT1_REG_HFXOSCCFG_WRNMASK    (0x7fffffff)
#define BPORT1_REG_HFXOSCCFG_WIDTH      32
#define BPORT1_REG_COREPLLCFG0_WRMASK   0x31ffff
#define BPORT1_REG_COREPLLCFG0_WRNMASK  (0xffce0000)
#define BPORT1_REG_COREPLLCFG0_WIDTH    32
#define BPORT1_REG_DDRPLLCFG0_WRMASK    0x31ffff
#define BPORT1_REG_DDRPLLCFG0_WRNMASK   (0xffce0000)
#define BPORT1_REG_DDRPLLCFG0_WIDTH     32
#define BPORT1_REG_DDRPLLCFG1_WRMASK    0x1000000
#define BPORT1_REG_DDRPLLCFG1_WRNMASK   (0xfeffffff)
#define BPORT1_REG_DDRPLLCFG1_WIDTH     32
#define BPORT1_REG_GEMGXLPLLCFG0_WRMASK  0x31ffff
#define BPORT1_REG_GEMGXLPLLCFG0_WRNMASK  (0xffce0000)
#define BPORT1_REG_GEMGXLPLLCFG0_WIDTH  32
#define BPORT1_REG_GEMGXLPLLCFG1_WRMASK  0x80000000
#define BPORT1_REG_GEMGXLPLLCFG1_WRNMASK  (0x7fffffff)
#define BPORT1_REG_GEMGXLPLLCFG1_WIDTH  32
#define BPORT1_REG_CORECLKSEL_WRMASK    0x1
#define BPORT1_REG_CORECLKSEL_WRNMASK   (0xfffffffe)
#define BPORT1_REG_CORECLKSEL_WIDTH     32
#define BPORT1_REG_DEVICESRESETREG_WRMASK  0x2f
#define BPORT1_REG_DEVICESRESETREG_WRNMASK  (0xffffffd0)
#define BPORT1_REG_DEVICESRESETREG_WIDTH  32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
