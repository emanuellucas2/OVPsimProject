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

typedef struct busPortGR_GR1_dataS { 
    union { 
        Uns16 value;
    } GMCTRL;
    union { 
        Uns8 value;
    } GMCS;
    union { 
        Uns16 value;
    } GMABT;
    union { 
        Uns8 value;
    } GMABTD;
    union { 
        Uns16 value;
    } MASK1L;
    union { 
        Uns16 value;
    } MASK1H;
    union { 
        Uns16 value;
    } MASK2L;
    union { 
        Uns16 value;
    } MASK2H;
    union { 
        Uns16 value;
    } MASK3L;
    union { 
        Uns16 value;
    } MASK3H;
    union { 
        Uns16 value;
    } MASK4L;
    union { 
        Uns16 value;
    } MASK4H;
    union { 
        Uns16 value;
    } CTRL;
} busPortGR_GR1_dataT, *busPortGR_GR1_dataTP;

typedef struct busPortGR_GR2_dataS { 
    union { 
        Uns8 value;
    } LEC;
    union { 
        Uns8 value;
    } INFO;
} busPortGR_GR2_dataT, *busPortGR_GR2_dataTP;

typedef struct busPortGR_GR3_dataS { 
    union { 
        Uns16 value;
    } ERC;
    union { 
        Uns16 value;
    } IE;
    union { 
        Uns16 value;
    } INTS;
    union { 
        Uns8 value;
    } BRP;
    union { 
        Uns16 value;
    } BTR;
    union { 
        Uns8 value;
    } LIPT;
    union { 
        Uns16 value;
    } RGPT;
    union { 
        Uns8 value;
    } LOPT;
    union { 
        Uns16 value;
    } TGPT;
    union { 
        Uns16 value;
    } TS;
} busPortGR_GR3_dataT, *busPortGR_GR3_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern busPortGR_GR1_dataT busPortGR_GR1_data;

extern busPortGR_GR2_dataT busPortGR_GR2_data;

extern busPortGR_GR3_dataT busPortGR_GR3_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *busPortGR;
    ppmNetHandle          INTTRX;
    ppmNetHandle          INTREC;
    ppmNetHandle          INTERR;
    ppmNetHandle          INTWUP;
    ppmPacketnetHandle    CAN;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_PACKETNET_CB(canrx);
PPM_REG_READ_CB(readBRP);
PPM_REG_READ_CB(readBTR);
PPM_REG_READ_CB(readCTRL);
PPM_REG_READ_CB(readERC);
PPM_REG_READ_CB(readGMABT);
PPM_REG_READ_CB(readGMABTD);
PPM_REG_READ_CB(readGMCS);
PPM_REG_READ_CB(readGMCTRL);
PPM_REG_READ_CB(readIE);
PPM_REG_READ_CB(readINFO);
PPM_REG_READ_CB(readINTS);
PPM_REG_READ_CB(readLEC);
PPM_REG_READ_CB(readLIPT);
PPM_REG_READ_CB(readLOPT);
PPM_REG_READ_CB(readMASKH);
PPM_REG_READ_CB(readMASKL);
PPM_REG_READ_CB(readRGPT);
PPM_REG_READ_CB(readTGPT);
PPM_REG_READ_CB(readTS);
PPM_REG_VIEW_CB(viewBRP);
PPM_REG_VIEW_CB(viewBTR);
PPM_REG_VIEW_CB(viewCTRL);
PPM_REG_VIEW_CB(viewERC);
PPM_REG_VIEW_CB(viewGMABT);
PPM_REG_VIEW_CB(viewGMABTD);
PPM_REG_VIEW_CB(viewGMCS);
PPM_REG_VIEW_CB(viewGMCTRL);
PPM_REG_VIEW_CB(viewIE);
PPM_REG_VIEW_CB(viewINFO);
PPM_REG_VIEW_CB(viewINTS);
PPM_REG_VIEW_CB(viewLEC);
PPM_REG_VIEW_CB(viewLIPT);
PPM_REG_VIEW_CB(viewLOPT);
PPM_REG_VIEW_CB(viewMASKH);
PPM_REG_VIEW_CB(viewMASKL);
PPM_REG_VIEW_CB(viewRGPT);
PPM_REG_VIEW_CB(viewTGPT);
PPM_REG_VIEW_CB(viewTS);
PPM_REG_WRITE_CB(writeBRP);
PPM_REG_WRITE_CB(writeBTR);
PPM_REG_WRITE_CB(writeCTRL);
PPM_REG_WRITE_CB(writeGMABT);
PPM_REG_WRITE_CB(writeGMABTD);
PPM_REG_WRITE_CB(writeGMCS);
PPM_REG_WRITE_CB(writeGMCTRL);
PPM_REG_WRITE_CB(writeIE);
PPM_REG_WRITE_CB(writeINTS);
PPM_REG_WRITE_CB(writeLEC);
PPM_REG_WRITE_CB(writeMASKH);
PPM_REG_WRITE_CB(writeMASKL);
PPM_REG_WRITE_CB(writeRGPT);
PPM_REG_WRITE_CB(writeTGPT);
PPM_REG_WRITE_CB(writeTS);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BUSPORTGR_GR1_GMCTRL_WIDTH      16
#define BUSPORTGR_GR1_GMCS_WIDTH        8
#define BUSPORTGR_GR1_GMABT_WIDTH       16
#define BUSPORTGR_GR1_GMABTD_WIDTH      8
#define BUSPORTGR_GR1_MASK1L_WIDTH      16
#define BUSPORTGR_GR1_MASK1H_WIDTH      16
#define BUSPORTGR_GR1_MASK2L_WIDTH      16
#define BUSPORTGR_GR1_MASK2H_WIDTH      16
#define BUSPORTGR_GR1_MASK3L_WIDTH      16
#define BUSPORTGR_GR1_MASK3H_WIDTH      16
#define BUSPORTGR_GR1_MASK4L_WIDTH      16
#define BUSPORTGR_GR1_MASK4H_WIDTH      16
#define BUSPORTGR_GR1_CTRL_WIDTH        16
#define BUSPORTGR_GR2_LEC_WIDTH         8
#define BUSPORTGR_GR2_INFO_WIDTH        8
#define BUSPORTGR_GR3_ERC_WIDTH         16
#define BUSPORTGR_GR3_IE_WIDTH          16
#define BUSPORTGR_GR3_INTS_WIDTH        16
#define BUSPORTGR_GR3_BRP_WIDTH         8
#define BUSPORTGR_GR3_BTR_WIDTH         16
#define BUSPORTGR_GR3_LIPT_WIDTH        8
#define BUSPORTGR_GR3_RGPT_WIDTH        16
#define BUSPORTGR_GR3_LOPT_WIDTH        8
#define BUSPORTGR_GR3_TGPT_WIDTH        16
#define BUSPORTGR_GR3_TS_WIDTH          16

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
