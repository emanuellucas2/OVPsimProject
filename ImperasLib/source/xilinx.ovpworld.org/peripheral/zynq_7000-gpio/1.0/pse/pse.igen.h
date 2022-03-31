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
            Uns32 DATA : 16;
            Uns32 MASK : 16;
        } bits;
    } MASK_DATA_0_LSW;
    union { 
        Uns32 value;
        struct {
            Uns32 DATA : 16;
            Uns32 MASK : 16;
        } bits;
    } MASK_DATA_0_MSW;
    union { 
        Uns32 value;
        struct {
            Uns32 DATA : 16;
            Uns32 MASK : 16;
        } bits;
    } MASK_DATA_1_LSW;
    union { 
        Uns32 value;
        struct {
            Uns32 DATA : 16;
            Uns32 MASK : 16;
        } bits;
    } MASK_DATA_1_MSW;
    union { 
        Uns32 value;
        struct {
            Uns32 DATA : 16;
            Uns32 MASK : 16;
        } bits;
    } MASK_DATA_2_LSW;
    union { 
        Uns32 value;
        struct {
            Uns32 DATA : 16;
            Uns32 MASK : 16;
        } bits;
    } MASK_DATA_2_MSW;
    union { 
        Uns32 value;
        struct {
            Uns32 DATA : 16;
            Uns32 MASK : 16;
        } bits;
    } MASK_DATA_3_LSW;
    union { 
        Uns32 value;
        struct {
            Uns32 DATA : 16;
            Uns32 MASK : 16;
        } bits;
    } MASK_DATA_3_MSW;
    union { 
        Uns32 value;
        struct {
            Uns32 LOW : 16;
            Uns32 HIGH : 16;
        } bits;
    } DATA_0;
    union { 
        Uns32 value;
        struct {
            Uns32 LOW : 16;
            Uns32 HIGH : 16;
        } bits;
    } DATA_1;
    union { 
        Uns32 value;
        struct {
            Uns32 LOW : 16;
            Uns32 HIGH : 16;
        } bits;
    } DATA_2;
    union { 
        Uns32 value;
        struct {
            Uns32 LOW : 16;
            Uns32 HIGH : 16;
        } bits;
    } DATA_3;
    union { 
        Uns32 value;
    } DIRM_0;
    union { 
        Uns32 value;
    } OEN_0;
    union { 
        Uns32 value;
    } INT_MASK_0;
    union { 
        Uns32 value;
    } INT_EN_0;
    union { 
        Uns32 value;
    } INT_DIS_0;
    union { 
        Uns32 value;
    } INT_STAT_0;
    union { 
        Uns32 value;
    } INT_TYPE_0;
    union { 
        Uns32 value;
    } INT_POLARITY_0;
    union { 
        Uns32 value;
    } INT_ANY_0;
    union { 
        Uns32 value;
    } DIRM_1;
    union { 
        Uns32 value;
    } OEN_1;
    union { 
        Uns32 value;
    } INT_MASK_1;
    union { 
        Uns32 value;
    } INT_EN_1;
    union { 
        Uns32 value;
    } INT_DIS_1;
    union { 
        Uns32 value;
    } INT_STAT_1;
    union { 
        Uns32 value;
    } INT_TYPE_1;
    union { 
        Uns32 value;
    } INT_POLARITY_1;
    union { 
        Uns32 value;
    } INT_ANY_1;
    union { 
        Uns32 value;
    } DIRM_2;
    union { 
        Uns32 value;
    } OEN_2;
    union { 
        Uns32 value;
    } INT_MASK_2;
    union { 
        Uns32 value;
    } INT_EN_2;
    union { 
        Uns32 value;
    } INT_DIS_2;
    union { 
        Uns32 value;
    } INT_STAT_2;
    union { 
        Uns32 value;
    } INT_TYPE_2;
    union { 
        Uns32 value;
    } INT_POLARITY_2;
    union { 
        Uns32 value;
    } INT_ANY_2;
    union { 
        Uns32 value;
    } DIRM_3;
    union { 
        Uns32 value;
    } OEN_3;
    union { 
        Uns32 value;
    } INT_MASK_3;
    union { 
        Uns32 value;
    } INT_EN_3;
    union { 
        Uns32 value;
    } INT_DIS_3;
    union { 
        Uns32 value;
    } INT_STAT_3;
    union { 
        Uns32 value;
    } INT_TYPE_3;
    union { 
        Uns32 value;
    } INT_POLARITY_3;
    union { 
        Uns32 value;
    } INT_ANY_3;
} bport1_REG_dataT, *bport1_REG_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_REG_dataT bport1_REG_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          interrupt;
    ppmNetHandle          gpio_bank0_in;
    ppmNetHandle          gpio_bank0_out;
    ppmNetHandle          gpio_bank1_in;
    ppmNetHandle          gpio_bank1_out;
    ppmNetHandle          gpio_bank2_in;
    ppmNetHandle          gpio_bank2_out;
    ppmNetHandle          gpio_bank2_oen_out;
    ppmNetHandle          gpio_bank3_in;
    ppmNetHandle          gpio_bank3_out;
    ppmNetHandle          gpio_bank3_oen_out;
    ppmNetHandle          intOut;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(gpio_in_change);
PPM_REG_READ_CB(rDATA);
PPM_REG_READ_CB(rDIRM);
PPM_REG_READ_CB(rINT_ANY);
PPM_REG_READ_CB(rINT_MASK);
PPM_REG_READ_CB(rINT_POLARITY);
PPM_REG_READ_CB(rINT_TYPE);
PPM_REG_READ_CB(rMASK);
PPM_REG_READ_CB(rOEN);
PPM_REG_WRITE_CB(wDATA);
PPM_REG_WRITE_CB(wDIRM);
PPM_REG_WRITE_CB(wINT_ANY);
PPM_REG_WRITE_CB(wINT_DIS);
PPM_REG_WRITE_CB(wINT_EN);
PPM_REG_WRITE_CB(wINT_POLARITY);
PPM_REG_WRITE_CB(wINT_STAT);
PPM_REG_WRITE_CB(wINT_TYPE);
PPM_REG_WRITE_CB(wMASK);
PPM_REG_WRITE_CB(wOEN);
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

// To access local memory bport1/REG/buffer0 : (for example)
// char value = ((char*)handles.bport1)[BPORT1_REG_BUFFER0_OFFSET + myAddress];

#define BPORT1_REG_BUFFER0_OFFSET       0x0
#define BPORT1_REG_BUFFER0_SIZE         0x3c

// To access local memory bport1/REG/buffer1 : (for example)
// char value = ((char*)handles.bport1)[BPORT1_REG_BUFFER1_OFFSET + myAddress];

#define BPORT1_REG_BUFFER1_OFFSET       0x70
#define BPORT1_REG_BUFFER1_SIZE         0xf90

// To access local memory bport1/REG/DATA_0_RO : (for example)
// char value = ((char*)handles.bport1)[BPORT1_REG_DATA_0_RO_OFFSET + myAddress];

#define BPORT1_REG_DATA_0_RO_OFFSET     0x60
#define BPORT1_REG_DATA_0_RO_SIZE       0x4

// To access local memory bport1/REG/DATA_1_RO : (for example)
// char value = ((char*)handles.bport1)[BPORT1_REG_DATA_1_RO_OFFSET + myAddress];

#define BPORT1_REG_DATA_1_RO_OFFSET     0x64
#define BPORT1_REG_DATA_1_RO_SIZE       0x4

// To access local memory bport1/REG/DATA_2_RO : (for example)
// char value = ((char*)handles.bport1)[BPORT1_REG_DATA_2_RO_OFFSET + myAddress];

#define BPORT1_REG_DATA_2_RO_OFFSET     0x68
#define BPORT1_REG_DATA_2_RO_SIZE       0x4

// To access local memory bport1/REG/DATA_3_RO : (for example)
// char value = ((char*)handles.bport1)[BPORT1_REG_DATA_3_RO_OFFSET + myAddress];

#define BPORT1_REG_DATA_3_RO_OFFSET     0x6c
#define BPORT1_REG_DATA_3_RO_SIZE       0x4

////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_REG_MASK_DATA_0_LSW_WIDTH  32
#define BPORT1_REG_MASK_DATA_0_MSW_WIDTH  32
#define BPORT1_REG_MASK_DATA_1_LSW_WIDTH  32
#define BPORT1_REG_MASK_DATA_1_MSW_WIDTH  32
#define BPORT1_REG_MASK_DATA_2_LSW_WIDTH  32
#define BPORT1_REG_MASK_DATA_2_MSW_WIDTH  32
#define BPORT1_REG_MASK_DATA_3_LSW_WIDTH  32
#define BPORT1_REG_MASK_DATA_3_MSW_WIDTH  32
#define BPORT1_REG_DATA_0_WIDTH         32
#define BPORT1_REG_DATA_1_WIDTH         32
#define BPORT1_REG_DATA_2_WIDTH         32
#define BPORT1_REG_DATA_3_WIDTH         32
#define BPORT1_REG_DIRM_0_WIDTH         32
#define BPORT1_REG_OEN_0_WIDTH          32
#define BPORT1_REG_INT_MASK_0_WIDTH     32
#define BPORT1_REG_INT_EN_0_WIDTH       32
#define BPORT1_REG_INT_DIS_0_WIDTH      32
#define BPORT1_REG_INT_STAT_0_WIDTH     32
#define BPORT1_REG_INT_TYPE_0_WIDTH     32
#define BPORT1_REG_INT_POLARITY_0_WIDTH  32
#define BPORT1_REG_INT_ANY_0_WIDTH      32
#define BPORT1_REG_DIRM_1_WIDTH         32
#define BPORT1_REG_OEN_1_WIDTH          32
#define BPORT1_REG_INT_MASK_1_WIDTH     32
#define BPORT1_REG_INT_EN_1_WIDTH       32
#define BPORT1_REG_INT_DIS_1_WIDTH      32
#define BPORT1_REG_INT_STAT_1_WIDTH     32
#define BPORT1_REG_INT_TYPE_1_WIDTH     32
#define BPORT1_REG_INT_POLARITY_1_WIDTH  32
#define BPORT1_REG_INT_ANY_1_WIDTH      32
#define BPORT1_REG_DIRM_2_WIDTH         32
#define BPORT1_REG_OEN_2_WIDTH          32
#define BPORT1_REG_INT_MASK_2_WIDTH     32
#define BPORT1_REG_INT_EN_2_WIDTH       32
#define BPORT1_REG_INT_DIS_2_WIDTH      32
#define BPORT1_REG_INT_STAT_2_WIDTH     32
#define BPORT1_REG_INT_TYPE_2_WIDTH     32
#define BPORT1_REG_INT_POLARITY_2_WIDTH  32
#define BPORT1_REG_INT_ANY_2_WIDTH      32
#define BPORT1_REG_DIRM_3_WIDTH         32
#define BPORT1_REG_OEN_3_WIDTH          32
#define BPORT1_REG_INT_MASK_3_WIDTH     32
#define BPORT1_REG_INT_EN_3_WIDTH       32
#define BPORT1_REG_INT_DIS_3_WIDTH      32
#define BPORT1_REG_INT_STAT_3_WIDTH     32
#define BPORT1_REG_INT_TYPE_3_WIDTH     32
#define BPORT1_REG_INT_POLARITY_3_WIDTH  32
#define BPORT1_REG_INT_ANY_3_WIDTH      32

//////////////////////////// Parameters of enum type ///////////////////////////

typedef enum configE {
    CONFIG_ZC702 = 0,
    CONFIG_ZC706 = 1,
} configT;

#endif

#endif
