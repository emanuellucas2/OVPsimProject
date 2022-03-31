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
    } TZPCR0SIZE;
    union { 
        Uns32 value;
    } TZPCDECPROT0Stat;
    union { 
        Uns32 value;
    } TZPCDECPROT0Set;
    union { 
        Uns32 value;
    } TZPCDECPROT0Clr;
    union { 
        Uns32 value;
    } TZPCDECPROT1Stat;
    union { 
        Uns32 value;
    } TZPCDECPROT1Set;
    union { 
        Uns32 value;
    } TZPCDECPROT1Clr;
    union { 
        Uns32 value;
    } TZPCDECPROT2Stat;
    union { 
        Uns32 value;
    } TZPCDECPROT2Set;
    union { 
        Uns32 value;
    } TZPCDECPROT2Clr;
    union { 
        Uns32 value;
    } TZPCPERIPHID0;
    union { 
        Uns32 value;
    } TZPCPERIPHID1;
    union { 
        Uns32 value;
    } TZPCPERIPHID2;
    union { 
        Uns32 value;
    } TZPCPERIPHID3;
    union { 
        Uns32 value;
    } TZPCPCELLID0;
    union { 
        Uns32 value;
    } TZPCPCELLID1;
    union { 
        Uns32 value;
    } TZPCPCELLID2;
    union { 
        Uns32 value;
    } TZPCPCELLID3;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          resetNet;
    ppmNetHandle          TZPCR0SIZE;
    ppmNetHandle          TZPCDECPROT0_0;
    ppmNetHandle          TZPCDECPROT0_1;
    ppmNetHandle          TZPCDECPROT0_2;
    ppmNetHandle          TZPCDECPROT0_3;
    ppmNetHandle          TZPCDECPROT0_4;
    ppmNetHandle          TZPCDECPROT0_5;
    ppmNetHandle          TZPCDECPROT0_6;
    ppmNetHandle          TZPCDECPROT0_7;
    ppmNetHandle          TZPCDECPROT0_8;
    ppmNetHandle          TZPCDECPROT0_9;
    ppmNetHandle          TZPCDECPROT0_10;
    ppmNetHandle          TZPCDECPROT0_11;
    ppmNetHandle          TZPCDECPROT0_12;
    ppmNetHandle          TZPCDECPROT0_13;
    ppmNetHandle          TZPCDECPROT0_14;
    ppmNetHandle          TZPCDECPROT0_15;
    ppmNetHandle          TZPCDECPROT1_0;
    ppmNetHandle          TZPCDECPROT1_1;
    ppmNetHandle          TZPCDECPROT1_2;
    ppmNetHandle          TZPCDECPROT1_3;
    ppmNetHandle          TZPCDECPROT1_4;
    ppmNetHandle          TZPCDECPROT1_5;
    ppmNetHandle          TZPCDECPROT1_6;
    ppmNetHandle          TZPCDECPROT1_7;
    ppmNetHandle          TZPCDECPROT1_8;
    ppmNetHandle          TZPCDECPROT1_9;
    ppmNetHandle          TZPCDECPROT1_10;
    ppmNetHandle          TZPCDECPROT1_11;
    ppmNetHandle          TZPCDECPROT1_12;
    ppmNetHandle          TZPCDECPROT1_13;
    ppmNetHandle          TZPCDECPROT1_14;
    ppmNetHandle          TZPCDECPROT1_15;
    ppmNetHandle          TZPCDECPROT2_0;
    ppmNetHandle          TZPCDECPROT2_1;
    ppmNetHandle          TZPCDECPROT2_2;
    ppmNetHandle          TZPCDECPROT2_3;
    ppmNetHandle          TZPCDECPROT2_4;
    ppmNetHandle          TZPCDECPROT2_5;
    ppmNetHandle          TZPCDECPROT2_6;
    ppmNetHandle          TZPCDECPROT2_7;
    ppmNetHandle          TZPCDECPROT2_8;
    ppmNetHandle          TZPCDECPROT2_9;
    ppmNetHandle          TZPCDECPROT2_10;
    ppmNetHandle          TZPCDECPROT2_11;
    ppmNetHandle          TZPCDECPROT2_12;
    ppmNetHandle          TZPCDECPROT2_13;
    ppmNetHandle          TZPCDECPROT2_14;
    ppmNetHandle          TZPCDECPROT2_15;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_WRITE_CB(WriteTZPCDECPROT0Clr);
PPM_REG_WRITE_CB(WriteTZPCDECPROT0Set);
PPM_REG_WRITE_CB(WriteTZPCDECPROT1Clr);
PPM_REG_WRITE_CB(WriteTZPCDECPROT1Set);
PPM_REG_WRITE_CB(WriteTZPCDECPROT2Clr);
PPM_REG_WRITE_CB(WriteTZPCDECPROT2Set);
PPM_REG_WRITE_CB(WriteTZPCR0SIZE);
PPM_NET_CB(reset_resetNet);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_TZPCR0SIZE_WIDTH      32
#define BPORT1_AB_TZPCDECPROT0STAT_WIDTH  32
#define BPORT1_AB_TZPCDECPROT0SET_WIDTH  32
#define BPORT1_AB_TZPCDECPROT0CLR_WIDTH  32
#define BPORT1_AB_TZPCDECPROT1STAT_WIDTH  32
#define BPORT1_AB_TZPCDECPROT1SET_WIDTH  32
#define BPORT1_AB_TZPCDECPROT1CLR_WIDTH  32
#define BPORT1_AB_TZPCDECPROT2STAT_WIDTH  32
#define BPORT1_AB_TZPCDECPROT2SET_WIDTH  32
#define BPORT1_AB_TZPCDECPROT2CLR_WIDTH  32
#define BPORT1_AB_TZPCPERIPHID0_WIDTH   32
#define BPORT1_AB_TZPCPERIPHID1_WIDTH   32
#define BPORT1_AB_TZPCPERIPHID2_WIDTH   32
#define BPORT1_AB_TZPCPERIPHID3_WIDTH   32
#define BPORT1_AB_TZPCPCELLID0_WIDTH    32
#define BPORT1_AB_TZPCPCELLID1_WIDTH    32
#define BPORT1_AB_TZPCPCELLID2_WIDTH    32
#define BPORT1_AB_TZPCPCELLID3_WIDTH    32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
