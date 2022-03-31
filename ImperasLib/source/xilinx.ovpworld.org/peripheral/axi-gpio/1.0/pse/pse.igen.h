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

typedef struct sp1_reg_dataS { 
    union { 
        Uns32 value;
    } gpio_tri;
    union { 
        Uns32 value;
    } gpio2_tri;
    union { 
        Uns32 value;
    } gier;
    union { 
        Uns32 value;
    } ip_ier;
    union { 
        Uns32 value;
    } ip_isr;
} sp1_reg_dataT, *sp1_reg_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern sp1_reg_dataT sp1_reg_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *sp1;
    ppmNetHandle          gpio_out;
    ppmNetHandle          gpio_in;
    ppmNetHandle          gpio2_out;
    ppmNetHandle          gpio2_in;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(gpio2Input);
PPM_NET_CB(gpioInput);
PPM_REG_READ_CB(readGier);
PPM_REG_READ_CB(readIer);
PPM_REG_READ_CB(readIsr);
PPM_REG_WRITE_CB(writeGier);
PPM_REG_WRITE_CB(writeIer);
PPM_REG_WRITE_CB(writeIsr);
PPM_REG_WRITE_CB(writeTri);
PPM_REG_WRITE_CB(writeTri2);
PPM_WRITE_CB(writeData);
PPM_WRITE_CB(writeData2);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


///////////////////////////////// Local memory /////////////////////////////////

// To access local memory sp1/reg/gpio_data : (for example)
// char value = ((char*)handles.sp1)[SP1_REG_GPIO_DATA_OFFSET + myAddress];

#define SP1_REG_GPIO_DATA_OFFSET        0x0
#define SP1_REG_GPIO_DATA_SIZE          0x4

// To access local memory sp1/reg/gpio2_data : (for example)
// char value = ((char*)handles.sp1)[SP1_REG_GPIO2_DATA_OFFSET + myAddress];

#define SP1_REG_GPIO2_DATA_OFFSET       0x8
#define SP1_REG_GPIO2_DATA_SIZE         0x4

////////////////////////////////// Mask macros /////////////////////////////////

#define SP1_REG_GPIO_TRI_WIDTH          32
#define SP1_REG_GPIO2_TRI_WIDTH         32
#define SP1_REG_GIER_WIDTH              32
#define SP1_REG_IP_IER_WIDTH            32
#define SP1_REG_IP_ISR_WIDTH            32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
