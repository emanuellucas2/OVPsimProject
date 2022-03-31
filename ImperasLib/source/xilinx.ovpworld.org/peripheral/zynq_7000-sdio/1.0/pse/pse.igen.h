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
    } SDMA_system_address_register;
    union { 
        Uns32 value;
    } Block_Size_Block_Count;
    union { 
        Uns32 value;
    } Argument;
    union { 
        Uns32 value;
    } Transfer_Mode_Command;
    union { 
        Uns32 value;
    } Response0;
    union { 
        Uns32 value;
    } Response1;
    union { 
        Uns32 value;
    } Response2;
    union { 
        Uns32 value;
    } Response3;
    union { 
        Uns32 value;
    } Buffer_Data_Port;
    union { 
        Uns32 value;
    } Present_State;
    union { 
        Uns32 value;
        struct {
            Uns32 LED : 1;
        } bits;
    } Host_Power_Block_Gap_Wakeup_control;
    union { 
        Uns32 value;
        struct {
            Uns32 ICLKEN : 1;
            Uns32 ICLKST : 1;
            Uns32 __pad2 : 22;
            Uns32 SWRST_ALL : 1;
            Uns32 SWRST_CMD : 1;
            Uns32 SWRST_DAT : 1;
        } bits;
    } Clock_Timeout_control_Software_reset;
    union { 
        Uns32 value;
    } Interrupt_status;
    union { 
        Uns32 value;
    } Interrupt_status_enable;
    union { 
        Uns32 value;
    } Interrupt_signal_enable;
    union { 
        Uns32 value;
    } Auto_CMD12_error_status;
    union { 
        Uns32 value;
    } Capabilities;
    union { 
        Uns32 value;
    } Maximum_current_capabilities;
    union { 
        Uns32 value;
    } Force_event;
    union { 
        Uns32 value;
    } ADMA_error_status;
    union { 
        Uns32 value;
    } ADMA_system_address;
    union { 
        Uns32 value;
    } Boot_Timeout_control;
    union { 
        Uns32 value;
    } Debug_Selection;
    union { 
        Uns32 value;
    } SPI_interrupt_support;
    union { 
        Uns32 value;
    } Slot_status_Host_version;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          intOut;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_WRITE_CB(wrClkCtrl);
PPM_REG_WRITE_CB(wrDebugSel);
PPM_REG_WRITE_CB(wrPwrCtrl);
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

#define BPORT1_AB_SDMA_SYSTEM_ADDRESS_REGISTER_WIDTH  32
#define BPORT1_AB_BLOCK_SIZE_BLOCK_COUNT_WIDTH  32
#define BPORT1_AB_ARGUMENT_WIDTH        32
#define BPORT1_AB_TRANSFER_MODE_COMMAND_WIDTH  32
#define BPORT1_AB_RESPONSE0_WIDTH       32
#define BPORT1_AB_RESPONSE1_WIDTH       32
#define BPORT1_AB_RESPONSE2_WIDTH       32
#define BPORT1_AB_RESPONSE3_WIDTH       32
#define BPORT1_AB_BUFFER_DATA_PORT_WIDTH  32
#define BPORT1_AB_PRESENT_STATE_WIDTH   32
#define BPORT1_AB_HOST_POWER_BLOCK_GAP_WAKEUP_CONTROL_WRMASK  0x70f0fef
#define BPORT1_AB_HOST_POWER_BLOCK_GAP_WAKEUP_CONTROL_WRNMASK  (0xf8f0f010)
#define BPORT1_AB_HOST_POWER_BLOCK_GAP_WAKEUP_CONTROL_WIDTH  32
#define BPORT1_AB_CLOCK_TIMEOUT_CONTROL_SOFTWARE_RESET_WRMASK  0x70fff07
#define BPORT1_AB_CLOCK_TIMEOUT_CONTROL_SOFTWARE_RESET_WRNMASK  (0xf8f000f8)
#define BPORT1_AB_CLOCK_TIMEOUT_CONTROL_SOFTWARE_RESET_WIDTH  32
#define BPORT1_AB_INTERRUPT_STATUS_WRMASK  0x3fffffff
#define BPORT1_AB_INTERRUPT_STATUS_WRNMASK  (0xc0000000)
#define BPORT1_AB_INTERRUPT_STATUS_WIDTH  32
#define BPORT1_AB_INTERRUPT_STATUS_ENABLE_WRMASK  0x3fffffff
#define BPORT1_AB_INTERRUPT_STATUS_ENABLE_WRNMASK  (0xc0000000)
#define BPORT1_AB_INTERRUPT_STATUS_ENABLE_WIDTH  32
#define BPORT1_AB_INTERRUPT_SIGNAL_ENABLE_WRMASK  0x3fffffff
#define BPORT1_AB_INTERRUPT_SIGNAL_ENABLE_WRNMASK  (0xc0000000)
#define BPORT1_AB_INTERRUPT_SIGNAL_ENABLE_WIDTH  32
#define BPORT1_AB_AUTO_CMD12_ERROR_STATUS_WIDTH  32
#define BPORT1_AB_CAPABILITIES_WIDTH    32
#define BPORT1_AB_MAXIMUM_CURRENT_CAPABILITIES_WIDTH  32
#define BPORT1_AB_FORCE_EVENT_WIDTH     32
#define BPORT1_AB_ADMA_ERROR_STATUS_WRMASK  0x7
#define BPORT1_AB_ADMA_ERROR_STATUS_WRNMASK  (0xfffffff8)
#define BPORT1_AB_ADMA_ERROR_STATUS_WIDTH  32
#define BPORT1_AB_ADMA_SYSTEM_ADDRESS_WIDTH  32
#define BPORT1_AB_BOOT_TIMEOUT_CONTROL_WIDTH  32
#define BPORT1_AB_DEBUG_SELECTION_WRMASK  0x1
#define BPORT1_AB_DEBUG_SELECTION_WRNMASK  (0xfffffffe)
#define BPORT1_AB_DEBUG_SELECTION_WIDTH  32
#define BPORT1_AB_SPI_INTERRUPT_SUPPORT_WRMASK  0xff
#define BPORT1_AB_SPI_INTERRUPT_SUPPORT_WRNMASK  (0xffffff00)
#define BPORT1_AB_SPI_INTERRUPT_SUPPORT_WIDTH  32
#define BPORT1_AB_SLOT_STATUS_HOST_VERSION_WIDTH  32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
