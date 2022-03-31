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

typedef struct I2C_Slave_dr_dataS { 
} I2C_Slave_dr_dataT, *I2C_Slave_dr_dataTP;

typedef struct bport1_ab_dataS { 
    union { 
        Uns32 value;
        struct {
            Uns32 RW : 1;
            Uns32 MS : 1;
            Uns32 NEA : 1;
            Uns32 ACKEN : 1;
            Uns32 HOLD : 1;
            Uns32 SLVMON : 1;
            Uns32 CLR_FIFO : 1;
            Uns32 __pad7 : 1;
            Uns32 DIV_B : 6;
            Uns32 DIV_A : 2;
        } bits;
    } Control;
    union { 
        Uns32 value;
        struct {
            Uns32 ADD : 9;
        } bits;
    } I2CAddress;
    union { 
        Uns32 value;
        struct {
            Uns32 DATA : 8;
        } bits;
    } I2CData;
    union { 
        Uns32 value;
        struct {
            Uns32 XFERSZ : 8;
        } bits;
    } TransferSize;
    union { 
        Uns32 value;
        struct {
            Uns32 PAUSE : 8;
        } bits;
    } SlaveMonPause;
    union { 
        Uns32 value;
        struct {
            Uns32 TO : 8;
        } bits;
    } TimeOut;
    union { 
        Uns32 value;
        struct {
            Uns32 COMP : 1;
            Uns32 DATA : 1;
            Uns32 NACK : 1;
            Uns32 TO : 1;
            Uns32 SLV_RDY : 1;
            Uns32 RX_OVF : 1;
            Uns32 TX_OVF : 1;
            Uns32 RX_UNF : 1;
            Uns32 __pad8 : 1;
            Uns32 ARB_LOST : 1;
        } bits;
    } InterruptMask;
    union { 
        Uns32 value;
        struct {
            Uns32 COMP : 1;
            Uns32 DATA : 1;
            Uns32 NACK : 1;
            Uns32 TO : 1;
            Uns32 SLV_RDY : 1;
            Uns32 RX_OVF : 1;
            Uns32 TX_OVF : 1;
            Uns32 RX_UNF : 1;
            Uns32 __pad8 : 1;
            Uns32 ARB_LOST : 1;
        } bits;
    } InterruptEnable;
    union { 
        Uns32 value;
        struct {
            Uns32 COMP : 1;
            Uns32 DATA : 1;
            Uns32 NACK : 1;
            Uns32 TO : 1;
            Uns32 SLV_RDY : 1;
            Uns32 RX_OVF : 1;
            Uns32 TX_OVF : 1;
            Uns32 RX_UNF : 1;
            Uns32 __pad8 : 1;
            Uns32 ARB_LOST : 1;
        } bits;
    } InterruptDisable;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern I2C_Slave_dr_dataT I2C_Slave_dr_data;

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    ppmAddressSpaceHandle I2C_Master;
    void                 *I2C_Slave;
    void                 *bport1;
    ppmNetHandle          intOut;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_WRITE_CB(intDisable);
PPM_REG_WRITE_CB(intEnable);
PPM_REG_READ_CB(rdData);
PPM_REG_READ_CB(rdXSz);
PPM_REG_READ_CB(rdZero);
PPM_REG_WRITE_CB(wrAddress);
PPM_REG_WRITE_CB(wrControl);
PPM_REG_WRITE_CB(wrData);
PPM_REG_WRITE_CB(wrXSz);
PPM_READ_CB(i2cSlaveRead);
PPM_WRITE_CB(i2cSlaveWrite);
PPM_WRITE_CB(intClear);
PPM_READ_CB(regNoDefinitionRead);
PPM_WRITE_CB(regNoDefinitionWrite);
PPM_WRITE_CB(wrStatus);
PPM_NET_CB(reset_resetNet);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


///////////////////////////////// Local memory /////////////////////////////////

// To access local memory I2C_Slave/dr/buff : (for example)
// char value = ((char*)handles.I2C_Slave)[I2C_SLAVE_DR_BUFF_OFFSET + myAddress];

#define I2C_SLAVE_DR_BUFF_OFFSET        0x0
#define I2C_SLAVE_DR_BUFF_SIZE          0x4

// To access local memory bport1/ab/buffer1 : (for example)
// char value = ((char*)handles.bport1)[BPORT1_AB_BUFFER1_OFFSET + myAddress];

#define BPORT1_AB_BUFFER1_OFFSET        0x2c
#define BPORT1_AB_BUFFER1_SIZE          0xfd4

// To access local memory bport1/ab/Status : (for example)
// char value = ((char*)handles.bport1)[BPORT1_AB_STATUS_OFFSET + myAddress];

#define BPORT1_AB_STATUS_OFFSET         0x4
#define BPORT1_AB_STATUS_SIZE           0x10

// To access local memory bport1/ab/InterruptStatus : (for example)
// char value = ((char*)handles.bport1)[BPORT1_AB_INTERRUPTSTATUS_OFFSET + myAddress];

#define BPORT1_AB_INTERRUPTSTATUS_OFFSET  0x10
#define BPORT1_AB_INTERRUPTSTATUS_SIZE  0x10

////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_CONTROL_WRMASK        0xff7f
#define BPORT1_AB_CONTROL_WRNMASK       (0xffff0080)
#define BPORT1_AB_CONTROL_WIDTH         32
#define BPORT1_AB_I2CADDRESS_WRMASK     0x3ff
#define BPORT1_AB_I2CADDRESS_WRNMASK    (0xfffffc00)
#define BPORT1_AB_I2CADDRESS_WIDTH      32
#define BPORT1_AB_I2CDATA_WRMASK        0xff
#define BPORT1_AB_I2CDATA_WRNMASK       (0xffffff00)
#define BPORT1_AB_I2CDATA_WIDTH         32
#define BPORT1_AB_TRANSFERSIZE_WRMASK   0xff
#define BPORT1_AB_TRANSFERSIZE_WRNMASK  (0xffffff00)
#define BPORT1_AB_TRANSFERSIZE_WIDTH    32
#define BPORT1_AB_SLAVEMONPAUSE_WRMASK  0xf
#define BPORT1_AB_SLAVEMONPAUSE_WRNMASK  (0xfffffff0)
#define BPORT1_AB_SLAVEMONPAUSE_WIDTH   32
#define BPORT1_AB_TIMEOUT_WRMASK        0xff
#define BPORT1_AB_TIMEOUT_WRNMASK       (0xffffff00)
#define BPORT1_AB_TIMEOUT_WIDTH         32
#define BPORT1_AB_INTERRUPTMASK_WIDTH   32
#define BPORT1_AB_INTERRUPTENABLE_WRMASK  0x2ff
#define BPORT1_AB_INTERRUPTENABLE_WRNMASK  (0xfffffd00)
#define BPORT1_AB_INTERRUPTENABLE_WIDTH  32
#define BPORT1_AB_INTERRUPTDISABLE_WRMASK  0x2ff
#define BPORT1_AB_INTERRUPTDISABLE_WRNMASK  (0xfffffd00)
#define BPORT1_AB_INTERRUPTDISABLE_WIDTH  32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
