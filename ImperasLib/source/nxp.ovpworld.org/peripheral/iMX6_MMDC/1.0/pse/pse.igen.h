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
    } MMDC_MDCTL;
    union { 
        Uns32 value;
    } MMDC_MDPDC;
    union { 
        Uns32 value;
    } MMDC_MDOTC;
    union { 
        Uns32 value;
    } MMDC_MDCFG0;
    union { 
        Uns32 value;
    } MMDC_MDCFG1;
    union { 
        Uns32 value;
    } MMDC_MDCFG2;
    union { 
        Uns32 value;
    } MMDC_MDMISC;
    union { 
        Uns32 value;
    } MMDC_MDSCR;
    union { 
        Uns32 value;
    } MMDC_MDREF;
    union { 
        Uns32 value;
    } MMDC_MDRWD;
    union { 
        Uns32 value;
    } MMDC_MDOR;
    union { 
        Uns32 value;
    } MMDC_MDMRR;
    union { 
        Uns32 value;
    } MMDC_MDCFG3LP;
    union { 
        Uns32 value;
    } MMDC_MDMR4;
    union { 
        Uns32 value;
    } MMDC_MDASP;
    union { 
        Uns32 value;
    } MMDC_MAARCR;
    union { 
        Uns32 value;
        struct {
            Uns32 PSD : 1;
            Uns32 __pad1 : 3;
            Uns32 PSS : 1;
            Uns32 RIS : 1;
            Uns32 WIS : 1;
            Uns32 __pad7 : 1;
            Uns32 PST : 8;
            Uns32 __pad16 : 4;
            Uns32 LPMD : 1;
            Uns32 DVFS : 1;
            Uns32 __pad22 : 2;
            Uns32 LPACK : 1;
            Uns32 DVACK : 1;
        } bits;
    } MMDC_MAPSR;
    union { 
        Uns32 value;
    } MMDC_MAEXIDR0;
    union { 
        Uns32 value;
    } MMDC_MAEXIDR1;
    union { 
        Uns32 value;
    } MMDC_MADPCR0;
    union { 
        Uns32 value;
    } MMDC_MADPCR1;
    union { 
        Uns32 value;
    } MMDC_MADPSR0;
    union { 
        Uns32 value;
    } MMDC_MADPSR1;
    union { 
        Uns32 value;
    } MMDC_MADPSR2;
    union { 
        Uns32 value;
    } MMDC_MADPSR3;
    union { 
        Uns32 value;
    } MMDC_MADPSR4;
    union { 
        Uns32 value;
    } MMDC_MADPSR5;
    union { 
        Uns32 value;
    } MMDC_MASBS0;
    union { 
        Uns32 value;
    } MMDC_MASBS1;
    union { 
        Uns32 value;
    } MMDC_MAGENP;
    union { 
        Uns32 value;
    } MMDC_MPZQHWCTRL;
    union { 
        Uns32 value;
    } MMDC_MPZQSWCTRL;
    union { 
        Uns32 value;
    } MMDC_MPWLGCR;
    union { 
        Uns32 value;
    } MMDC_MPWLDECTRL0;
    union { 
        Uns32 value;
    } MMDC_MPWLDECTRL1;
    union { 
        Uns32 value;
    } MMDC_MPWLDLST;
    union { 
        Uns32 value;
    } MMDC_MPODTCTRL;
    union { 
        Uns32 value;
    } MMDC_MPRDDQBY0DL;
    union { 
        Uns32 value;
    } MMDC_MPRDDQBY1DL;
    union { 
        Uns32 value;
    } MMDC_MPRDDQBY2DL;
    union { 
        Uns32 value;
    } MMDC_MPRDDQBY3DL;
    union { 
        Uns32 value;
    } MMDC_MPWRDQBY0DL;
    union { 
        Uns32 value;
    } MMDC_MPWRDQBY1DL;
    union { 
        Uns32 value;
    } MMDC_MPWRDQBY2DL;
    union { 
        Uns32 value;
    } MMDC_MPWRDQBY3DL;
    union { 
        Uns32 value;
    } MMDC_MPDGCTRL0;
    union { 
        Uns32 value;
    } MMDC_MPDGCTRL1;
    union { 
        Uns32 value;
    } MMDC_MPDGDLST0;
    union { 
        Uns32 value;
    } MMDC_MPRDDLCTL;
    union { 
        Uns32 value;
    } MMDC_MPRDDLST;
    union { 
        Uns32 value;
    } MMDC_MPWRDLCTL;
    union { 
        Uns32 value;
    } MMDC_MPWRDLST;
    union { 
        Uns32 value;
    } MMDC_MPSDCTRL;
    union { 
        Uns32 value;
    } MMDC_MPZQLP2CTL;
    union { 
        Uns32 value;
    } MMDC_MPRDDLHWCTL;
    union { 
        Uns32 value;
    } MMDC_MPWRDLHWCTL;
    union { 
        Uns32 value;
    } MMDC_MPRDDLHWST0;
    union { 
        Uns32 value;
    } MMDC_MPRDDLHWST1;
    union { 
        Uns32 value;
    } MMDC_MPWRDLHWST0;
    union { 
        Uns32 value;
    } MMDC_MPWRDLHWST1;
    union { 
        Uns32 value;
    } MMDC_MPWLHWERR;
    union { 
        Uns32 value;
    } MMDC_MPDGHWST0;
    union { 
        Uns32 value;
    } MMDC_MPDGHWST1;
    union { 
        Uns32 value;
    } MMDC_MPDGHWST2;
    union { 
        Uns32 value;
    } MMDC_MPDGHWST3;
    union { 
        Uns32 value;
    } MMDC_MPPDCMPR1;
    union { 
        Uns32 value;
    } MMDC_MPPDCMPR2;
    union { 
        Uns32 value;
    } MMDC_MPSWDAR0;
    union { 
        Uns32 value;
    } MMDC_MPSWDRDR0;
    union { 
        Uns32 value;
    } MMDC_MPSWDRDR1;
    union { 
        Uns32 value;
    } MMDC_MPSWDRDR2;
    union { 
        Uns32 value;
    } MMDC_MPSWDRDR3;
    union { 
        Uns32 value;
    } MMDC_MPSWDRDR4;
    union { 
        Uns32 value;
    } MMDC_MPSWDRDR5;
    union { 
        Uns32 value;
    } MMDC_MPSWDRDR6;
    union { 
        Uns32 value;
    } MMDC_MPSWDRDR7;
    union { 
        Uns32 value;
    } MMDC_MPMUR0;
    union { 
        Uns32 value;
    } MMDC_MPWRCADL;
    union { 
        Uns32 value;
    } MMDC_MPDCCR;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_WRITE_CB(WriteMMDC_MAPSR);
PPM_READ_CB(regNoDefinitionRead);
PPM_WRITE_CB(regNoDefinitionWrite);
PPM_NET_CB(reset_resetNet);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


///////////////////////////////// Local memory /////////////////////////////////

// To access local memory bport1/ab/buffer : (for example)
// char value = ((char*)handles.bport1)[BPORT1_AB_BUFFER_OFFSET + myAddress];

#define BPORT1_AB_BUFFER_OFFSET         0x0
#define BPORT1_AB_BUFFER_SIZE           0x4000

////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_MMDC_MDCTL_WIDTH      32
#define BPORT1_AB_MMDC_MDPDC_WIDTH      32
#define BPORT1_AB_MMDC_MDOTC_WIDTH      32
#define BPORT1_AB_MMDC_MDCFG0_WIDTH     32
#define BPORT1_AB_MMDC_MDCFG1_WIDTH     32
#define BPORT1_AB_MMDC_MDCFG2_WIDTH     32
#define BPORT1_AB_MMDC_MDMISC_WIDTH     32
#define BPORT1_AB_MMDC_MDSCR_WIDTH      32
#define BPORT1_AB_MMDC_MDREF_WIDTH      32
#define BPORT1_AB_MMDC_MDRWD_WIDTH      32
#define BPORT1_AB_MMDC_MDOR_WIDTH       32
#define BPORT1_AB_MMDC_MDMRR_WIDTH      32
#define BPORT1_AB_MMDC_MDCFG3LP_WIDTH   32
#define BPORT1_AB_MMDC_MDMR4_WIDTH      32
#define BPORT1_AB_MMDC_MDASP_WIDTH      32
#define BPORT1_AB_MMDC_MAARCR_WIDTH     32
#define BPORT1_AB_MMDC_MAPSR_WRMASK     0x330871
#define BPORT1_AB_MMDC_MAPSR_WRNMASK    (0xffccf78e)
#define BPORT1_AB_MMDC_MAPSR_WIDTH      32
#define BPORT1_AB_MMDC_MAEXIDR0_WIDTH   32
#define BPORT1_AB_MMDC_MAEXIDR1_WIDTH   32
#define BPORT1_AB_MMDC_MADPCR0_WIDTH    32
#define BPORT1_AB_MMDC_MADPCR1_WIDTH    32
#define BPORT1_AB_MMDC_MADPSR0_WIDTH    32
#define BPORT1_AB_MMDC_MADPSR1_WIDTH    32
#define BPORT1_AB_MMDC_MADPSR2_WIDTH    32
#define BPORT1_AB_MMDC_MADPSR3_WIDTH    32
#define BPORT1_AB_MMDC_MADPSR4_WIDTH    32
#define BPORT1_AB_MMDC_MADPSR5_WIDTH    32
#define BPORT1_AB_MMDC_MASBS0_WIDTH     32
#define BPORT1_AB_MMDC_MASBS1_WIDTH     32
#define BPORT1_AB_MMDC_MAGENP_WIDTH     32
#define BPORT1_AB_MMDC_MPZQHWCTRL_WIDTH  32
#define BPORT1_AB_MMDC_MPZQSWCTRL_WIDTH  32
#define BPORT1_AB_MMDC_MPWLGCR_WIDTH    32
#define BPORT1_AB_MMDC_MPWLDECTRL0_WIDTH  32
#define BPORT1_AB_MMDC_MPWLDECTRL1_WIDTH  32
#define BPORT1_AB_MMDC_MPWLDLST_WIDTH   32
#define BPORT1_AB_MMDC_MPODTCTRL_WIDTH  32
#define BPORT1_AB_MMDC_MPRDDQBY0DL_WIDTH  32
#define BPORT1_AB_MMDC_MPRDDQBY1DL_WIDTH  32
#define BPORT1_AB_MMDC_MPRDDQBY2DL_WIDTH  32
#define BPORT1_AB_MMDC_MPRDDQBY3DL_WIDTH  32
#define BPORT1_AB_MMDC_MPWRDQBY0DL_WIDTH  32
#define BPORT1_AB_MMDC_MPWRDQBY1DL_WIDTH  32
#define BPORT1_AB_MMDC_MPWRDQBY2DL_WIDTH  32
#define BPORT1_AB_MMDC_MPWRDQBY3DL_WIDTH  32
#define BPORT1_AB_MMDC_MPDGCTRL0_WIDTH  32
#define BPORT1_AB_MMDC_MPDGCTRL1_WIDTH  32
#define BPORT1_AB_MMDC_MPDGDLST0_WIDTH  32
#define BPORT1_AB_MMDC_MPRDDLCTL_WIDTH  32
#define BPORT1_AB_MMDC_MPRDDLST_WIDTH   32
#define BPORT1_AB_MMDC_MPWRDLCTL_WIDTH  32
#define BPORT1_AB_MMDC_MPWRDLST_WIDTH   32
#define BPORT1_AB_MMDC_MPSDCTRL_WIDTH   32
#define BPORT1_AB_MMDC_MPZQLP2CTL_WIDTH  32
#define BPORT1_AB_MMDC_MPRDDLHWCTL_WIDTH  32
#define BPORT1_AB_MMDC_MPWRDLHWCTL_WIDTH  32
#define BPORT1_AB_MMDC_MPRDDLHWST0_WIDTH  32
#define BPORT1_AB_MMDC_MPRDDLHWST1_WIDTH  32
#define BPORT1_AB_MMDC_MPWRDLHWST0_WIDTH  32
#define BPORT1_AB_MMDC_MPWRDLHWST1_WIDTH  32
#define BPORT1_AB_MMDC_MPWLHWERR_WIDTH  32
#define BPORT1_AB_MMDC_MPDGHWST0_WIDTH  32
#define BPORT1_AB_MMDC_MPDGHWST1_WIDTH  32
#define BPORT1_AB_MMDC_MPDGHWST2_WIDTH  32
#define BPORT1_AB_MMDC_MPDGHWST3_WIDTH  32
#define BPORT1_AB_MMDC_MPPDCMPR1_WIDTH  32
#define BPORT1_AB_MMDC_MPPDCMPR2_WIDTH  32
#define BPORT1_AB_MMDC_MPSWDAR0_WIDTH   32
#define BPORT1_AB_MMDC_MPSWDRDR0_WIDTH  32
#define BPORT1_AB_MMDC_MPSWDRDR1_WIDTH  32
#define BPORT1_AB_MMDC_MPSWDRDR2_WIDTH  32
#define BPORT1_AB_MMDC_MPSWDRDR3_WIDTH  32
#define BPORT1_AB_MMDC_MPSWDRDR4_WIDTH  32
#define BPORT1_AB_MMDC_MPSWDRDR5_WIDTH  32
#define BPORT1_AB_MMDC_MPSWDRDR6_WIDTH  32
#define BPORT1_AB_MMDC_MPSWDRDR7_WIDTH  32
#define BPORT1_AB_MMDC_MPMUR0_WIDTH     32
#define BPORT1_AB_MMDC_MPWRCADL_WIDTH   32
#define BPORT1_AB_MMDC_MPDCCR_WIDTH     32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
