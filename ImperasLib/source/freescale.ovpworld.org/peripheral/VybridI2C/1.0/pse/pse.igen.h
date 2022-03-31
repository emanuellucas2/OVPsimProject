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
            Uns8 __pad0 : 1;
            Uns8 ADR : 7;
        } bits;
    } IBAD;
    union { 
        Uns8 value;
        struct {
            Uns8 IBC : 8;
        } bits;
    } IBFD;
    union { 
        Uns8 value;
        struct {
            Uns8 __pad0 : 1;
            Uns8 DMAEN : 1;
            Uns8 RSTA : 1;
            Uns8 NOACK : 1;
            Uns8 TXRX : 1;
            Uns8 MSSL : 1;
            Uns8 IBIE : 1;
            Uns8 MDIS : 1;
        } bits;
    } IBCR;
    union { 
        Uns8 value;
        struct {
            Uns8 RXAK : 1;
            Uns8 IBIF : 1;
            Uns8 SRW : 1;
            Uns8 __pad3 : 1;
            Uns8 IBAL : 1;
            Uns8 IBB : 1;
            Uns8 IAAS : 1;
            Uns8 TCF : 1;
        } bits;
    } IBSR;
    union { 
        Uns8 value;
        struct {
            Uns8 DATA : 8;
        } bits;
    } IBDR;
    union { 
        Uns8 value;
        struct {
            Uns8 __pad0 : 7;
            Uns8 BIIE : 1;
        } bits;
    } IBIC;
    union { 
        Uns8 value;
        struct {
            Uns8 IPG_DEBUG_EN : 1;
            Uns8 IPG_DEBUG_HALTED : 1;
        } bits;
    } IBDBG;
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

PPM_REG_WRITE_CB(BSRWrite1C);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_IBAD_WRMASK           0xfe
#define BPORT1_AB_IBAD_WRNMASK          (0x1)
#define BPORT1_AB_IBAD_WIDTH            8
#define BPORT1_AB_IBFD_WRMASK           0xff
#define BPORT1_AB_IBFD_WRNMASK          (0x0)
#define BPORT1_AB_IBFD_WIDTH            8
#define BPORT1_AB_IBCR_WRMASK           0xfe
#define BPORT1_AB_IBCR_WRNMASK          (0x1)
#define BPORT1_AB_IBCR_WIDTH            8
#define BPORT1_AB_IBSR_WRMASK           0x12
#define BPORT1_AB_IBSR_WRNMASK          (0xed)
#define BPORT1_AB_IBSR_WIDTH            8
#define BPORT1_AB_IBDR_WRMASK           0xff
#define BPORT1_AB_IBDR_WRNMASK          (0x0)
#define BPORT1_AB_IBDR_WIDTH            8
#define BPORT1_AB_IBIC_WRMASK           0x80
#define BPORT1_AB_IBIC_WRNMASK          (0x7f)
#define BPORT1_AB_IBIC_WIDTH            8
#define BPORT1_AB_IBDBG_WRMASK          0x1
#define BPORT1_AB_IBDBG_WRNMASK         (0xfe)
#define BPORT1_AB_IBDBG_WIDTH           8

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
