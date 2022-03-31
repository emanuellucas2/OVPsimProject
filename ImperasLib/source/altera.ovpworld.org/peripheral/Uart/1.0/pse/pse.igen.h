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

typedef struct sp1_reg0_dataS { 
    union { 
        Uns32 value;
    } rxdata;
    union { 
        Uns32 value;
    } txdata;
    union { 
        Uns32 value;
        struct {
            Uns32 pe : 1;
            Uns32 fe : 1;
            Uns32 brk : 1;
            Uns32 roe : 1;
            Uns32 toe : 1;
            Uns32 tmt : 1;
            Uns32 trdy : 1;
            Uns32 rrdy : 1;
            Uns32 e : 2;
            Uns32 dcts : 1;
            Uns32 cts : 1;
            Uns32 eop : 1;
        } bits;
    } status;
    union { 
        Uns32 value;
        struct {
            Uns32 ipe : 1;
            Uns32 ife : 1;
            Uns32 ibrk : 1;
            Uns32 iroe : 1;
            Uns32 itoe : 1;
            Uns32 itmt : 1;
            Uns32 itrdy : 1;
            Uns32 irrdy : 1;
            Uns32 ie : 1;
            Uns32 trbk : 1;
            Uns32 idcts : 1;
            Uns32 rts : 1;
            Uns32 ieop : 1;
        } bits;
    } control;
    union { 
        Uns32 value;
    } divisor;
    union { 
        Uns32 value;
    } eop;
} sp1_reg0_dataT, *sp1_reg0_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern sp1_reg0_dataT sp1_reg0_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *sp1;
    ppmNetHandle          irq;
    ppmNetHandle          endofpacket;
    ppmNetHandle          dataavailable;
    ppmNetHandle          readyfordata;
    ppmNetHandle          RXD;
    ppmNetHandle          CTS;
    ppmNetHandle          TXD;
    ppmNetHandle          RTS;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(read_control);
PPM_REG_READ_CB(read_divisor);
PPM_REG_READ_CB(read_eop);
PPM_REG_READ_CB(read_rxdata);
PPM_REG_READ_CB(read_status);
PPM_REG_WRITE_CB(write_control);
PPM_REG_WRITE_CB(write_divisor);
PPM_REG_WRITE_CB(write_eop);
PPM_REG_WRITE_CB(write_status);
PPM_REG_WRITE_CB(write_txdata);
PPM_NET_CB(reset_IRESET);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define SP1_REG0_RXDATA_WIDTH           32
#define SP1_REG0_TXDATA_WIDTH           32
#define SP1_REG0_STATUS_WIDTH           32
#define SP1_REG0_CONTROL_WIDTH          32
#define SP1_REG0_DIVISOR_WIDTH          32
#define SP1_REG0_EOP_WIDTH              32

//////////////////////////// Parameters of enum type ///////////////////////////

typedef enum parityE {
    PARITY_NONE = 0,
    PARITY_EVEN = 1,
    PARITY_ODD = 2,
} parityT;

#endif

#endif
