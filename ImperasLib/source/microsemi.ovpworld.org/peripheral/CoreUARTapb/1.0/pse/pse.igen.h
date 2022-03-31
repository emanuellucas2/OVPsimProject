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

typedef struct port0_Reg_dataS { 
    union { 
        Uns32 value;
    } TxData;
    union { 
        Uns32 value;
    } RxData;
    union { 
        Uns32 value;
        struct {
            Uns32 BAUD_VALUE : 8;
        } bits;
    } Ctrl1;
    union { 
        Uns32 value;
        struct {
            Uns32 BIT8 : 1;
            Uns32 PARITY_EN : 1;
            Uns32 ODD_N_EVEN : 1;
            Uns32 BAUD_VALUE : 5;
        } bits;
    } Ctrl2;
    union { 
        Uns32 value;
        struct {
            Uns32 TXRDY : 1;
            Uns32 RXRDY : 1;
            Uns32 PARITY_ERR : 1;
            Uns32 OVERFLOW : 1;
            Uns32 FRAMING_ERR : 1;
        } bits;
    } Status;
    union { 
        Uns32 value;
        struct {
            Uns32 BAUD_VALUE_FRACTION : 3;
        } bits;
    } Ctrl3;
} port0_Reg_dataT, *port0_Reg_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern port0_Reg_dataT port0_Reg_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *port0;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(Ctrl1Read);
PPM_REG_WRITE_CB(Ctrl1Write);
PPM_REG_READ_CB(Ctrl2Read);
PPM_REG_WRITE_CB(Ctrl2Write);
PPM_REG_READ_CB(Ctrl3Read);
PPM_REG_WRITE_CB(Ctrl3Write);
PPM_REG_READ_CB(RxDataRead);
PPM_REG_READ_CB(StatusRead);
PPM_REG_WRITE_CB(TxDataWrite);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define PORT0_REG_TXDATA_WIDTH          32
#define PORT0_REG_RXDATA_WIDTH          32
#define PORT0_REG_CTRL1_WIDTH           32
#define PORT0_REG_CTRL2_WIDTH           32
#define PORT0_REG_STATUS_WIDTH          32
#define PORT0_REG_CTRL3_WIDTH           32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
