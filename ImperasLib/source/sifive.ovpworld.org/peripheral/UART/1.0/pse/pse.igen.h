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
            Uns32 DATA : 8;
            Uns32 __pad8 : 23;
            Uns32 FULL : 1;
        } bits;
    } txdata;
    union { 
        Uns32 value;
        struct {
            Uns32 DATA : 8;
            Uns32 __pad8 : 23;
            Uns32 EMPTY : 1;
        } bits;
    } rxdata;
    union { 
        Uns32 value;
        struct {
            Uns32 TXEN : 1;
            Uns32 NSTOP : 1;
            Uns32 __pad2 : 14;
            Uns32 TXCNT : 3;
        } bits;
    } txctrl;
    union { 
        Uns32 value;
        struct {
            Uns32 RXEN : 1;
            Uns32 __pad1 : 15;
            Uns32 RXCNT : 3;
        } bits;
    } rxctrl;
    union { 
        Uns32 value;
        struct {
            Uns32 TXWM : 1;
            Uns32 RXWM : 1;
        } bits;
    } ie;
    union { 
        Uns32 value;
        struct {
            Uns32 TXWM : 1;
            Uns32 RXWM : 1;
        } bits;
    } ip;
    union { 
        Uns32 value;
        struct {
            Uns32 DIV : 20;
        } bits;
    } div;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          intOut;
    ppmNetHandle          reset;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_WRITE_CB(divWrite);
PPM_REG_WRITE_CB(ieWrite);
PPM_REG_READ_CB(ipRead);
PPM_NET_CB(resetCB);
PPM_REG_WRITE_CB(rxctrlWrite);
PPM_REG_READ_CB(rxdataRead);
PPM_REG_WRITE_CB(txctrlWrite);
PPM_REG_READ_CB(txdataRead);
PPM_REG_VIEW_CB(txdataView);
PPM_REG_WRITE_CB(txdataWrite);
PPM_NET_CB(reset_reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_TXDATA_WRMASK         0x800000ff
#define BPORT1_AB_TXDATA_WRNMASK        (0x7fffff00)
#define BPORT1_AB_TXDATA_WIDTH          32
#define BPORT1_AB_RXDATA_WIDTH          32
#define BPORT1_AB_TXCTRL_WRMASK         0x70003
#define BPORT1_AB_TXCTRL_WRNMASK        (0xfff8fffc)
#define BPORT1_AB_TXCTRL_WIDTH          32
#define BPORT1_AB_RXCTRL_WRMASK         0x70001
#define BPORT1_AB_RXCTRL_WRNMASK        (0xfff8fffe)
#define BPORT1_AB_RXCTRL_WIDTH          32
#define BPORT1_AB_IE_WIDTH              32
#define BPORT1_AB_IP_WIDTH              32
#define BPORT1_AB_DIV_WIDTH             32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
