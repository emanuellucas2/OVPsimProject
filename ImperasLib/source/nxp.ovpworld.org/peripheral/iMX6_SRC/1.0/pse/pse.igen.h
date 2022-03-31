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
            Uns32 WARM_RST_EN : 1;
            Uns32 SW_GPU_RST : 1;
            Uns32 SW_VPU_RST : 1;
            Uns32 SW_IPU1_RST : 1;
            Uns32 SW_OPVG_RST : 1;
            Uns32 WRM_RST_BYPASS : 2;
            Uns32 MSK_WDG_RST : 4;
            Uns32 EIM_RST : 1;
            Uns32 __pad12 : 1;
            Uns32 CORE0_RST : 1;
            Uns32 CORE1_RST : 1;
            Uns32 __pad15 : 2;
            Uns32 CORE0_DBG_RST : 1;
            Uns32 CORE1_DBG_RST : 1;
            Uns32 __pad19 : 2;
            Uns32 CORES_DBG_RST : 1;
            Uns32 CORE1EN : 1;
            Uns32 __pad23 : 2;
            Uns32 DBG_RST_MSK : 1;
        } bits;
    } SRC_SCR;
    union { 
        Uns32 value;
        struct {
            Uns32 BOOT_CFG1 : 8;
            Uns32 BOOT_CFG2 : 8;
            Uns32 BOOT_CFG3 : 8;
            Uns32 BOOT_CFG4 : 8;
        } bits;
    } SRC_SBMR1;
    union { 
        Uns32 value;
        struct {
            Uns32 IPP_RST : 1;
            Uns32 __pad1 : 1;
            Uns32 CSU_RST : 1;
            Uns32 IPP_USER_RST : 1;
            Uns32 WDOG_RST : 1;
            Uns32 JTAG_RST : 1;
            Uns32 JTAG_SW_RST : 1;
            Uns32 __pad7 : 9;
            Uns32 WARM_BOOT : 1;
        } bits;
    } SRC_SRSR;
    union { 
        Uns32 value;
        struct {
            Uns32 GPU_PASS : 1;
            Uns32 VPU_PASS : 1;
            Uns32 IPU1_PASS : 1;
            Uns32 OP_VG_PASS : 1;
            Uns32 __pad4 : 1;
            Uns32 CORE0_WDOG : 1;
            Uns32 CORE1_WDOG : 1;
        } bits;
    } SRC_SISR;
    union { 
        Uns32 value;
        struct {
            Uns32 GPU_PASS : 1;
            Uns32 VPU_PASS : 1;
            Uns32 IPU1_PASS : 1;
            Uns32 OP_VG_PASS : 1;
        } bits;
    } SRC_SIMR;
    union { 
        Uns32 value;
        struct {
            Uns32 SEC_CONFIG : 2;
            Uns32 __pad2 : 1;
            Uns32 DIR_BT_DIS : 1;
            Uns32 BT_FUSE_SEL : 1;
            Uns32 __pad5 : 19;
            Uns32 BMOD : 2;
        } bits;
    } SRC_SBMR2;
    union { 
        Uns32 value;
    } SRC_GPR1;
    union { 
        Uns32 value;
    } SRC_GPR2;
    union { 
        Uns32 value;
    } SRC_GPR3;
    union { 
        Uns32 value;
    } SRC_GPR4;
    union { 
        Uns32 value;
    } SRC_GPR5;
    union { 
        Uns32 value;
    } SRC_GPR6;
    union { 
        Uns32 value;
    } SRC_GPR7;
    union { 
        Uns32 value;
    } SRC_GPR8;
    union { 
        Uns32 value;
    } SRC_GPR9;
    union { 
        Uns32 value;
    } SRC_GPR10;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          resetCore0;
    ppmNetHandle          resetCore1;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(ReadSRC_SCR);
PPM_REG_READ_CB(ReadSRC_SIMR);
PPM_REG_READ_CB(ReadSRC_SISR);
PPM_REG_READ_CB(ReadSRC_SRSR);
PPM_REG_WRITE_CB(WriteSRC_SCR);
PPM_REG_WRITE_CB(WriteSRC_SIMR);
PPM_REG_WRITE_CB(WriteSRC_SRSR);
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

#define BPORT1_AB_SRC_SCR_WRMASK        0x2666fff
#define BPORT1_AB_SRC_SCR_WRNMASK       (0xfd999000)
#define BPORT1_AB_SRC_SCR_WIDTH         32
#define BPORT1_AB_SRC_SBMR1_WIDTH       32
#define BPORT1_AB_SRC_SRSR_WRMASK       0x10007d
#define BPORT1_AB_SRC_SRSR_WRNMASK      (0xffefff82)
#define BPORT1_AB_SRC_SRSR_WIDTH        32
#define BPORT1_AB_SRC_SISR_WIDTH        32
#define BPORT1_AB_SRC_SIMR_WRMASK       0xf
#define BPORT1_AB_SRC_SIMR_WRNMASK      (0xfffffff0)
#define BPORT1_AB_SRC_SIMR_WIDTH        32
#define BPORT1_AB_SRC_SBMR2_WIDTH       32
#define BPORT1_AB_SRC_GPR1_WIDTH        32
#define BPORT1_AB_SRC_GPR2_WIDTH        32
#define BPORT1_AB_SRC_GPR3_WIDTH        32
#define BPORT1_AB_SRC_GPR4_WIDTH        32
#define BPORT1_AB_SRC_GPR5_WIDTH        32
#define BPORT1_AB_SRC_GPR6_WIDTH        32
#define BPORT1_AB_SRC_GPR7_WIDTH        32
#define BPORT1_AB_SRC_GPR8_WIDTH        32
#define BPORT1_AB_SRC_GPR9_WIDTH        32
#define BPORT1_AB_SRC_GPR10_WIDTH       32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
