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
    } CCM_ANALOG_PLL_ARM;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_ARM_SET;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_ARM_CLR;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_ARM_TOG;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_USB1;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_USB1_SET;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_USB1_CLR;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_USB1_TOG;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_USB2;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_USB2_SET;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_USB2_CLR;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_USB2_TOG;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_SYS;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_SYS_SET;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_SYS_CLR;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_SYS_TOG;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_SYS_SS;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_SYS_SYS_NUM;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_SYS_SYS_DENOM;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_AUDIO;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_AUDIO_SET;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_AUDIO_CLR;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_AUDIO_TOG;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_AUDIO_NUM;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_AUDIO_NUM_SET;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_AUDIO_NUM_CLR;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_AUDIO_NUM_TOG;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_AUDIO_DENOM;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_AUDIO_DENOM_SET;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_AUDIO_DENOM_CLR;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_AUDIO_DENOM_TOG;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_VIDEO;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_VIDEO_SET;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_VIDEO_CLR;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_VIDEO_TOG;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_VIDEO_NUM;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_VIDEO_NUM_SET;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_VIDEO_NUM_CLR;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_VIDEO_NUM_TOG;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_VIDEO_DENOM;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_VIDEO_DENOM_SET;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_VIDEO_DENOM_CLR;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_VIDEO_DENOM_TOG;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_MLB;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_MLB_SET;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_MLB_CLR;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_MLB_TOG;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_ENET;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_ENET_SET;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_ENET_CLR;
    union { 
        Uns32 value;
    } CCM_ANALOG_PLL_ENET_TOG;
    union { 
        Uns32 value;
    } CCM_ANALOG_PFD_480;
    union { 
        Uns32 value;
    } CCM_ANALOG_PFD_480_SET;
    union { 
        Uns32 value;
    } CCM_ANALOG_PFD_480_CLR;
    union { 
        Uns32 value;
    } CCM_ANALOG_PFD_480_TOG;
    union { 
        Uns32 value;
    } CCM_ANALOG_PFD_528;
    union { 
        Uns32 value;
    } CCM_ANALOG_PFD_528_SET;
    union { 
        Uns32 value;
    } CCM_ANALOG_PFD_528_CLR;
    union { 
        Uns32 value;
    } CCM_ANALOG_PFD_528_TOG;
    union { 
        Uns32 value;
    } PMU_REG_1P1;
    union { 
        Uns32 value;
    } PMU_REG_1P1_SET;
    union { 
        Uns32 value;
    } PMU_REG_1P1_CLR;
    union { 
        Uns32 value;
    } PMU_REG_1P1_TOG;
    union { 
        Uns32 value;
    } PMU_REG_3P0;
    union { 
        Uns32 value;
    } PMU_REG_3P0_SET;
    union { 
        Uns32 value;
    } PMU_REG_3P0_CLR;
    union { 
        Uns32 value;
    } PMU_REG_3P0_TOG;
    union { 
        Uns32 value;
    } PMU_REG_2P5;
    union { 
        Uns32 value;
    } PMU_REG_2P5_SET;
    union { 
        Uns32 value;
    } PMU_REG_2P5_CLR;
    union { 
        Uns32 value;
    } PMU_REG_2P5_TOG;
    union { 
        Uns32 value;
    } PMU_REG_CORE;
    union { 
        Uns32 value;
    } PMU_REG_CORE_SET;
    union { 
        Uns32 value;
    } PMU_REG_CORE_CLR;
    union { 
        Uns32 value;
    } PMU_REG_CORE_TOG;
    union { 
        Uns32 value;
    } MISC0;
    union { 
        Uns32 value;
    } MISC0_SET;
    union { 
        Uns32 value;
    } MISC0_CLR;
    union { 
        Uns32 value;
    } MISC0_TOG;
    union { 
        Uns32 value;
    } MISC1;
    union { 
        Uns32 value;
    } MISC1_SET;
    union { 
        Uns32 value;
    } MISC1_CLR;
    union { 
        Uns32 value;
    } MISC1_TOG;
    union { 
        Uns32 value;
    } MISC2;
    union { 
        Uns32 value;
    } MISC2_SET;
    union { 
        Uns32 value;
    } MISC2_CLR;
    union { 
        Uns32 value;
    } MISC2_TOG;
    union { 
        Uns32 value;
    } USB_ANALOG_USB1_VBUS_DETECT;
    union { 
        Uns32 value;
    } USB_ANALOG_USB1_VBUS_DETECT_SET;
    union { 
        Uns32 value;
    } USB_ANALOG_USB1_VBUS_DETECT_CLR;
    union { 
        Uns32 value;
    } USB_ANALOG_USB1_VBUS_DETECT_TOG;
    union { 
        Uns32 value;
    } USB_ANALOG_USB1_CHRG_DETECT;
    union { 
        Uns32 value;
    } USB_ANALOG_USB1_CHRG_DETECT_SET;
    union { 
        Uns32 value;
    } USB_ANALOG_USB1_CHRG_DETECT_CLR;
    union { 
        Uns32 value;
    } USB_ANALOG_USB1_CHRG_DETECT_TOG;
    union { 
        Uns32 value;
    } USB_ANALOG_USB1_VBUS_DETECT_STAT;
    union { 
        Uns32 value;
    } USB_ANALOG_USB1_CHRG_DETECT_STAT;
    union { 
        Uns32 value;
    } USB_ANALOG_USB1_MISC;
    union { 
        Uns32 value;
    } USB_ANALOG_USB1_MISC_SET;
    union { 
        Uns32 value;
    } USB_ANALOG_USB1_MISC_CLR;
    union { 
        Uns32 value;
    } USB_ANALOG_USB1_MISC_TOG;
    union { 
        Uns32 value;
    } USB_ANALOG_USB2_VBUS_DETECT;
    union { 
        Uns32 value;
    } USB_ANALOG_USB2_VBUS_DETECT_SET;
    union { 
        Uns32 value;
    } USB_ANALOG_USB2_VBUS_DETECT_CLR;
    union { 
        Uns32 value;
    } USB_ANALOG_USB2_VBUS_DETECT_TOG;
    union { 
        Uns32 value;
    } USB_ANALOG_USB2_CHRG_DETECT;
    union { 
        Uns32 value;
    } USB_ANALOG_USB2_CHRG_DETECT_SET;
    union { 
        Uns32 value;
    } USB_ANALOG_USB2_CHRG_DETECT_CLR;
    union { 
        Uns32 value;
    } USB_ANALOG_USB2_CHRG_DETECT_TOG;
    union { 
        Uns32 value;
    } USB_ANALOG_USB2_VBUS_DETECT_STAT;
    union { 
        Uns32 value;
    } USB_ANALOG_USB2_CHRG_DETECT_STAT;
    union { 
        Uns32 value;
    } USB_ANALOG_USB2_MISC;
    union { 
        Uns32 value;
    } USB_ANALOG_USB2_MISC_SET;
    union { 
        Uns32 value;
    } USB_ANALOG_USB2_MISC_CLR;
    union { 
        Uns32 value;
    } USB_ANALOG_USB2_MISC_TOG;
    union { 
        Uns32 value;
    } USB_ANALOG_DIGPROG;
    union { 
        Uns32 value;
    } USB_ANALOG_DIGPROG_SET;
    union { 
        Uns32 value;
    } USB_ANALOG_DIGPROG_CLR;
    union { 
        Uns32 value;
    } USB_ANALOG_DIGPROG_TOG;
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

PPM_REG_WRITE_CB(ClrBits);
PPM_REG_READ_CB(ReadZero);
PPM_REG_WRITE_CB(SetBits);
PPM_REG_WRITE_CB(TogBits);
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
#define BPORT1_AB_BUFFER_SIZE           0x1000

////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_CCM_ANALOG_PLL_ARM_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_ARM_SET_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_ARM_CLR_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_ARM_TOG_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_USB1_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_USB1_SET_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_USB1_CLR_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_USB1_TOG_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_USB2_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_USB2_SET_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_USB2_CLR_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_USB2_TOG_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_SYS_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_SYS_SET_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_SYS_CLR_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_SYS_TOG_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_SYS_SS_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_SYS_SYS_NUM_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_SYS_SYS_DENOM_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_SET_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_CLR_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_TOG_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_NUM_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_NUM_SET_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_NUM_CLR_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_NUM_TOG_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_DENOM_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_DENOM_SET_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_DENOM_CLR_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_AUDIO_DENOM_TOG_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_SET_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_CLR_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_TOG_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_NUM_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_NUM_SET_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_NUM_CLR_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_NUM_TOG_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_DENOM_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_DENOM_SET_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_DENOM_CLR_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_VIDEO_DENOM_TOG_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_MLB_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_MLB_SET_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_MLB_CLR_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_MLB_TOG_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_ENET_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_ENET_SET_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_ENET_CLR_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PLL_ENET_TOG_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PFD_480_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PFD_480_SET_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PFD_480_CLR_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PFD_480_TOG_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PFD_528_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PFD_528_SET_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PFD_528_CLR_WIDTH  32
#define BPORT1_AB_CCM_ANALOG_PFD_528_TOG_WIDTH  32
#define BPORT1_AB_PMU_REG_1P1_WIDTH     32
#define BPORT1_AB_PMU_REG_1P1_SET_WIDTH  32
#define BPORT1_AB_PMU_REG_1P1_CLR_WIDTH  32
#define BPORT1_AB_PMU_REG_1P1_TOG_WIDTH  32
#define BPORT1_AB_PMU_REG_3P0_WIDTH     32
#define BPORT1_AB_PMU_REG_3P0_SET_WIDTH  32
#define BPORT1_AB_PMU_REG_3P0_CLR_WIDTH  32
#define BPORT1_AB_PMU_REG_3P0_TOG_WIDTH  32
#define BPORT1_AB_PMU_REG_2P5_WIDTH     32
#define BPORT1_AB_PMU_REG_2P5_SET_WIDTH  32
#define BPORT1_AB_PMU_REG_2P5_CLR_WIDTH  32
#define BPORT1_AB_PMU_REG_2P5_TOG_WIDTH  32
#define BPORT1_AB_PMU_REG_CORE_WIDTH    32
#define BPORT1_AB_PMU_REG_CORE_SET_WIDTH  32
#define BPORT1_AB_PMU_REG_CORE_CLR_WIDTH  32
#define BPORT1_AB_PMU_REG_CORE_TOG_WIDTH  32
#define BPORT1_AB_MISC0_WIDTH           32
#define BPORT1_AB_MISC0_SET_WIDTH       32
#define BPORT1_AB_MISC0_CLR_WIDTH       32
#define BPORT1_AB_MISC0_TOG_WIDTH       32
#define BPORT1_AB_MISC1_WIDTH           32
#define BPORT1_AB_MISC1_SET_WIDTH       32
#define BPORT1_AB_MISC1_CLR_WIDTH       32
#define BPORT1_AB_MISC1_TOG_WIDTH       32
#define BPORT1_AB_MISC2_WIDTH           32
#define BPORT1_AB_MISC2_SET_WIDTH       32
#define BPORT1_AB_MISC2_CLR_WIDTH       32
#define BPORT1_AB_MISC2_TOG_WIDTH       32
#define BPORT1_AB_USB_ANALOG_USB1_VBUS_DETECT_WIDTH  32
#define BPORT1_AB_USB_ANALOG_USB1_VBUS_DETECT_SET_WIDTH  32
#define BPORT1_AB_USB_ANALOG_USB1_VBUS_DETECT_CLR_WIDTH  32
#define BPORT1_AB_USB_ANALOG_USB1_VBUS_DETECT_TOG_WIDTH  32
#define BPORT1_AB_USB_ANALOG_USB1_CHRG_DETECT_WIDTH  32
#define BPORT1_AB_USB_ANALOG_USB1_CHRG_DETECT_SET_WIDTH  32
#define BPORT1_AB_USB_ANALOG_USB1_CHRG_DETECT_CLR_WIDTH  32
#define BPORT1_AB_USB_ANALOG_USB1_CHRG_DETECT_TOG_WIDTH  32
#define BPORT1_AB_USB_ANALOG_USB1_VBUS_DETECT_STAT_WIDTH  32
#define BPORT1_AB_USB_ANALOG_USB1_CHRG_DETECT_STAT_WIDTH  32
#define BPORT1_AB_USB_ANALOG_USB1_MISC_WIDTH  32
#define BPORT1_AB_USB_ANALOG_USB1_MISC_SET_WIDTH  32
#define BPORT1_AB_USB_ANALOG_USB1_MISC_CLR_WIDTH  32
#define BPORT1_AB_USB_ANALOG_USB1_MISC_TOG_WIDTH  32
#define BPORT1_AB_USB_ANALOG_USB2_VBUS_DETECT_WIDTH  32
#define BPORT1_AB_USB_ANALOG_USB2_VBUS_DETECT_SET_WIDTH  32
#define BPORT1_AB_USB_ANALOG_USB2_VBUS_DETECT_CLR_WIDTH  32
#define BPORT1_AB_USB_ANALOG_USB2_VBUS_DETECT_TOG_WIDTH  32
#define BPORT1_AB_USB_ANALOG_USB2_CHRG_DETECT_WIDTH  32
#define BPORT1_AB_USB_ANALOG_USB2_CHRG_DETECT_SET_WIDTH  32
#define BPORT1_AB_USB_ANALOG_USB2_CHRG_DETECT_CLR_WIDTH  32
#define BPORT1_AB_USB_ANALOG_USB2_CHRG_DETECT_TOG_WIDTH  32
#define BPORT1_AB_USB_ANALOG_USB2_VBUS_DETECT_STAT_WIDTH  32
#define BPORT1_AB_USB_ANALOG_USB2_CHRG_DETECT_STAT_WIDTH  32
#define BPORT1_AB_USB_ANALOG_USB2_MISC_WIDTH  32
#define BPORT1_AB_USB_ANALOG_USB2_MISC_SET_WIDTH  32
#define BPORT1_AB_USB_ANALOG_USB2_MISC_CLR_WIDTH  32
#define BPORT1_AB_USB_ANALOG_USB2_MISC_TOG_WIDTH  32
#define BPORT1_AB_USB_ANALOG_DIGPROG_WIDTH  32
#define BPORT1_AB_USB_ANALOG_DIGPROG_SET_WIDTH  32
#define BPORT1_AB_USB_ANALOG_DIGPROG_CLR_WIDTH  32
#define BPORT1_AB_USB_ANALOG_DIGPROG_TOG_WIDTH  32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
