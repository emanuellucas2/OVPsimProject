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
    } power;
    union { 
        Uns32 value;
    } clock;
    union { 
        Uns32 value;
    } cmdarg;
    union { 
        Uns32 value;
        struct {
            Uns32 C_INDEX : 6;
            Uns32 C_RESPONSE : 1;
            Uns32 C_LONGRESP : 1;
            Uns32 C_INTERRUPT : 1;
            Uns32 C_PENDING : 1;
            Uns32 C_ENABLE : 1;
        } bits;
    } cmd;
    union { 
        Uns32 value;
    } respcmd;
    union { 
        Uns32 value;
    } response0;
    union { 
        Uns32 value;
    } response1;
    union { 
        Uns32 value;
    } response2;
    union { 
        Uns32 value;
    } response3;
    union { 
        Uns32 value;
    } datatimer;
    union { 
        Uns32 value;
    } datalength;
    union { 
        Uns32 value;
        struct {
            Uns32 D_ENABLE : 1;
            Uns32 D_DIRECTION : 1;
            Uns32 D_MODE : 1;
            Uns32 D_DMAENABLE : 1;
        } bits;
    } datactrl;
    union { 
        Uns32 value;
    } datacnt;
    union { 
        Uns32 value;
        struct {
            Uns32 S_CMDCRCFAIL : 1;
            Uns32 S_DATACRCFAIL : 1;
            Uns32 S_CMDTIMEOUT : 1;
            Uns32 S_DATATIMEOUT : 1;
            Uns32 S_TXUNDERRUN : 1;
            Uns32 S_RXOVERRUN : 1;
            Uns32 S_CMDRESPEND : 1;
            Uns32 S_CMDSENT : 1;
            Uns32 S_DATAEND : 1;
            Uns32 __pad9 : 1;
            Uns32 S_DATABLOCKEND : 1;
            Uns32 S_CMDACTIVE : 1;
            Uns32 S_TXACTIVE : 1;
            Uns32 S_RXACTIVE : 1;
            Uns32 S_TXFIFOHALFEMPTY : 1;
            Uns32 S_RXFIFOHALFFULL : 1;
            Uns32 S_TXFIFOFULL : 1;
            Uns32 S_RXFIFOFULL : 1;
            Uns32 S_TXFIFOEMPTY : 1;
            Uns32 S_RXFIFOEMPTY : 1;
            Uns32 S_TXDATAAVLBL : 1;
            Uns32 S_RXDATAAVLBL : 1;
        } bits;
    } status;
    union { 
        Uns32 value;
    } clear;
    union { 
        Uns32 value;
    } mask0;
    union { 
        Uns32 value;
    } mask1;
    union { 
        Uns32 value;
    } fifoCnt;
    union { 
        Uns32 value;
    } periphID0;
    union { 
        Uns32 value;
    } periphID1;
    union { 
        Uns32 value;
    } periphID2;
    union { 
        Uns32 value;
    } periphID3;
    union { 
        Uns32 value;
    } pCellID0;
    union { 
        Uns32 value;
    } pCellID1;
    union { 
        Uns32 value;
    } pCellID2;
    union { 
        Uns32 value;
    } pCellID3;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          irq0;
    ppmNetHandle          irq1;
    ppmNetHandle          cardin;
    ppmNetHandle          wprot;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(readFifoCnt);
PPM_REG_READ_CB(readStatus);
PPM_REG_WRITE_CB(write8);
PPM_REG_WRITE_CB(writeArg);
PPM_REG_WRITE_CB(writeClear);
PPM_REG_WRITE_CB(writeClock);
PPM_REG_WRITE_CB(writeCmd);
PPM_REG_WRITE_CB(writeDC);
PPM_REG_WRITE_CB(writeDL);
PPM_REG_WRITE_CB(writeMask0);
PPM_REG_WRITE_CB(writeMask1);
PPM_READ_CB(reservedRead);
PPM_WRITE_CB(reservedWrite);
PPM_NET_CB(reset_reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


///////////////////////////////// Local memory /////////////////////////////////

// To access local memory bport1/ab/RESERVED1 : (for example)
// char value = ((char*)handles.bport1)[BPORT1_AB_RESERVED1_OFFSET + myAddress];

#define BPORT1_AB_RESERVED1_OFFSET      0x4c
#define BPORT1_AB_RESERVED1_SIZE        0x34

// To access local memory bport1/ab/RESERVED2 : (for example)
// char value = ((char*)handles.bport1)[BPORT1_AB_RESERVED2_OFFSET + myAddress];

#define BPORT1_AB_RESERVED2_OFFSET      0xc0
#define BPORT1_AB_RESERVED2_SIZE        0xf20

// To access local memory bport1/ab/FIFO : (for example)
// char value = ((char*)handles.bport1)[BPORT1_AB_FIFO_OFFSET + myAddress];

#define BPORT1_AB_FIFO_OFFSET           0x80
#define BPORT1_AB_FIFO_SIZE             0x40

////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_POWER_WIDTH           32
#define BPORT1_AB_CLOCK_WIDTH           32
#define BPORT1_AB_CMDARG_WIDTH          32
#define BPORT1_AB_CMD_WIDTH             32
#define BPORT1_AB_RESPCMD_WIDTH         32
#define BPORT1_AB_RESPONSE0_WIDTH       32
#define BPORT1_AB_RESPONSE1_WIDTH       32
#define BPORT1_AB_RESPONSE2_WIDTH       32
#define BPORT1_AB_RESPONSE3_WIDTH       32
#define BPORT1_AB_DATATIMER_WIDTH       32
#define BPORT1_AB_DATALENGTH_WIDTH      32
#define BPORT1_AB_DATACTRL_WIDTH        32
#define BPORT1_AB_DATACNT_WIDTH         32
#define BPORT1_AB_STATUS_WIDTH          32
#define BPORT1_AB_CLEAR_WIDTH           32
#define BPORT1_AB_MASK0_WIDTH           32
#define BPORT1_AB_MASK1_WIDTH           32
#define BPORT1_AB_FIFOCNT_WIDTH         32
#define BPORT1_AB_PERIPHID0_WIDTH       32
#define BPORT1_AB_PERIPHID1_WIDTH       32
#define BPORT1_AB_PERIPHID2_WIDTH       32
#define BPORT1_AB_PERIPHID3_WIDTH       32
#define BPORT1_AB_PCELLID0_WIDTH        32
#define BPORT1_AB_PCELLID1_WIDTH        32
#define BPORT1_AB_PCELLID2_WIDTH        32
#define BPORT1_AB_PCELLID3_WIDTH        32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
