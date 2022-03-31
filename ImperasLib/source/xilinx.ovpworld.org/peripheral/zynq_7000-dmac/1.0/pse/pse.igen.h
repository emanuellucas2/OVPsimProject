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

typedef struct bportS_abS_dataS { 
    union { 
        Uns32 value;
    } DSR;
    union { 
        Uns32 value;
    } DPC;
    union { 
        Uns32 value;
    } INTEN;
    union { 
        Uns32 value;
    } INT_EVENT_RIS;
    union { 
        Uns32 value;
    } INTMIS;
    union { 
        Uns32 value;
    } INTCLR;
    union { 
        Uns32 value;
    } FSRD;
    union { 
        Uns32 value;
    } FSRC;
    union { 
        Uns32 value;
    } FTRD;
    union { 
        Uns32 value;
    } FTR0;
    union { 
        Uns32 value;
    } FTR1;
    union { 
        Uns32 value;
    } FTR2;
    union { 
        Uns32 value;
    } FTR3;
    union { 
        Uns32 value;
    } FTR4;
    union { 
        Uns32 value;
    } FTR5;
    union { 
        Uns32 value;
    } FTR6;
    union { 
        Uns32 value;
    } FTR7;
    union { 
        Uns32 value;
    } CSR0;
    union { 
        Uns32 value;
    } CPC0;
    union { 
        Uns32 value;
    } CSR1;
    union { 
        Uns32 value;
    } CPC1;
    union { 
        Uns32 value;
    } CSR2;
    union { 
        Uns32 value;
    } CPC2;
    union { 
        Uns32 value;
    } CSR3;
    union { 
        Uns32 value;
    } CPC3;
    union { 
        Uns32 value;
    } CSR4;
    union { 
        Uns32 value;
    } CPC4;
    union { 
        Uns32 value;
    } CSR5;
    union { 
        Uns32 value;
    } CPC5;
    union { 
        Uns32 value;
    } CSR6;
    union { 
        Uns32 value;
    } CPC6;
    union { 
        Uns32 value;
    } CSR7;
    union { 
        Uns32 value;
    } CPC7;
    union { 
        Uns32 value;
    } SAR0;
    union { 
        Uns32 value;
    } DAR0;
    union { 
        Uns32 value;
    } CCR0;
    union { 
        Uns32 value;
    } LC0_0;
    union { 
        Uns32 value;
    } LC1_0;
    union { 
        Uns32 value;
    } SAR1;
    union { 
        Uns32 value;
    } DAR1;
    union { 
        Uns32 value;
    } CCR1;
    union { 
        Uns32 value;
    } LC0_1;
    union { 
        Uns32 value;
    } LC1_1;
    union { 
        Uns32 value;
    } SAR2;
    union { 
        Uns32 value;
    } DAR2;
    union { 
        Uns32 value;
    } CCR2;
    union { 
        Uns32 value;
    } LC0_2;
    union { 
        Uns32 value;
    } LC1_2;
    union { 
        Uns32 value;
    } SAR3;
    union { 
        Uns32 value;
    } DAR3;
    union { 
        Uns32 value;
    } CCR3;
    union { 
        Uns32 value;
    } LC0_3;
    union { 
        Uns32 value;
    } LC1_3;
    union { 
        Uns32 value;
    } SAR4;
    union { 
        Uns32 value;
    } DAR4;
    union { 
        Uns32 value;
    } CCR4;
    union { 
        Uns32 value;
    } LC0_4;
    union { 
        Uns32 value;
    } LC1_4;
    union { 
        Uns32 value;
    } SAR5;
    union { 
        Uns32 value;
    } DAR5;
    union { 
        Uns32 value;
    } CCR5;
    union { 
        Uns32 value;
    } LC0_5;
    union { 
        Uns32 value;
    } LC1_5;
    union { 
        Uns32 value;
    } SAR6;
    union { 
        Uns32 value;
    } DAR6;
    union { 
        Uns32 value;
    } CCR6;
    union { 
        Uns32 value;
    } LC0_6;
    union { 
        Uns32 value;
    } LC1_6;
    union { 
        Uns32 value;
    } SAR7;
    union { 
        Uns32 value;
    } DAR7;
    union { 
        Uns32 value;
    } CCR7;
    union { 
        Uns32 value;
    } LC0_7;
    union { 
        Uns32 value;
    } LC1_7;
    union { 
        Uns32 value;
    } DBGSTATUS;
    union { 
        Uns32 value;
    } DBGCMD;
    union { 
        Uns32 value;
    } DBGINST0;
    union { 
        Uns32 value;
    } DBGINST1;
    union { 
        Uns32 value;
    } CR0;
    union { 
        Uns32 value;
    } CR1;
    union { 
        Uns32 value;
    } CR2;
    union { 
        Uns32 value;
    } CR3;
    union { 
        Uns32 value;
    } CR4;
    union { 
        Uns32 value;
    } CRD;
    union { 
        Uns32 value;
    } WD;
    union { 
        Uns32 value;
    } periph_id_0;
    union { 
        Uns32 value;
    } periph_id_1;
    union { 
        Uns32 value;
    } periph_id_2;
    union { 
        Uns32 value;
    } periph_id_3;
    union { 
        Uns32 value;
    } pcell_id_0;
    union { 
        Uns32 value;
    } pcell_id_1;
    union { 
        Uns32 value;
    } pcell_id_2;
    union { 
        Uns32 value;
    } pcell_id_3;
} bportS_abS_dataT, *bportS_abS_dataTP;

typedef struct bportNS_abNS_dataS { 
    union { 
        Uns32 value;
    } DSR;
    union { 
        Uns32 value;
    } DPC;
    union { 
        Uns32 value;
    } INTEN;
    union { 
        Uns32 value;
    } INT_EVENT_RIS;
    union { 
        Uns32 value;
    } INTMIS;
    union { 
        Uns32 value;
    } INTCLR;
    union { 
        Uns32 value;
    } FSRD;
    union { 
        Uns32 value;
    } FSRC;
    union { 
        Uns32 value;
    } FTRD;
    union { 
        Uns32 value;
    } FTR0;
    union { 
        Uns32 value;
    } FTR1;
    union { 
        Uns32 value;
    } FTR2;
    union { 
        Uns32 value;
    } FTR3;
    union { 
        Uns32 value;
    } FTR4;
    union { 
        Uns32 value;
    } FTR5;
    union { 
        Uns32 value;
    } FTR6;
    union { 
        Uns32 value;
    } FTR7;
    union { 
        Uns32 value;
    } CSR0;
    union { 
        Uns32 value;
    } CPC0;
    union { 
        Uns32 value;
    } CSR1;
    union { 
        Uns32 value;
    } CPC1;
    union { 
        Uns32 value;
    } CSR2;
    union { 
        Uns32 value;
    } CPC2;
    union { 
        Uns32 value;
    } CSR3;
    union { 
        Uns32 value;
    } CPC3;
    union { 
        Uns32 value;
    } CSR4;
    union { 
        Uns32 value;
    } CPC4;
    union { 
        Uns32 value;
    } CSR5;
    union { 
        Uns32 value;
    } CPC5;
    union { 
        Uns32 value;
    } CSR6;
    union { 
        Uns32 value;
    } CPC6;
    union { 
        Uns32 value;
    } CSR7;
    union { 
        Uns32 value;
    } CPC7;
    union { 
        Uns32 value;
    } SAR0;
    union { 
        Uns32 value;
    } DAR0;
    union { 
        Uns32 value;
    } CCR0;
    union { 
        Uns32 value;
    } LC0_0;
    union { 
        Uns32 value;
    } LC1_0;
    union { 
        Uns32 value;
    } SAR1;
    union { 
        Uns32 value;
    } DAR1;
    union { 
        Uns32 value;
    } CCR1;
    union { 
        Uns32 value;
    } LC0_1;
    union { 
        Uns32 value;
    } LC1_1;
    union { 
        Uns32 value;
    } SAR2;
    union { 
        Uns32 value;
    } DAR2;
    union { 
        Uns32 value;
    } CCR2;
    union { 
        Uns32 value;
    } LC0_2;
    union { 
        Uns32 value;
    } LC1_2;
    union { 
        Uns32 value;
    } SAR3;
    union { 
        Uns32 value;
    } DAR3;
    union { 
        Uns32 value;
    } CCR3;
    union { 
        Uns32 value;
    } LC0_3;
    union { 
        Uns32 value;
    } LC1_3;
    union { 
        Uns32 value;
    } SAR4;
    union { 
        Uns32 value;
    } DAR4;
    union { 
        Uns32 value;
    } CCR4;
    union { 
        Uns32 value;
    } LC0_4;
    union { 
        Uns32 value;
    } LC1_4;
    union { 
        Uns32 value;
    } SAR5;
    union { 
        Uns32 value;
    } DAR5;
    union { 
        Uns32 value;
    } CCR5;
    union { 
        Uns32 value;
    } LC0_5;
    union { 
        Uns32 value;
    } LC1_5;
    union { 
        Uns32 value;
    } SAR6;
    union { 
        Uns32 value;
    } DAR6;
    union { 
        Uns32 value;
    } CCR6;
    union { 
        Uns32 value;
    } LC0_6;
    union { 
        Uns32 value;
    } LC1_6;
    union { 
        Uns32 value;
    } SAR7;
    union { 
        Uns32 value;
    } DAR7;
    union { 
        Uns32 value;
    } CCR7;
    union { 
        Uns32 value;
    } LC0_7;
    union { 
        Uns32 value;
    } LC1_7;
    union { 
        Uns32 value;
    } DBGSTATUS;
    union { 
        Uns32 value;
    } DBGCMD;
    union { 
        Uns32 value;
    } DBGINST0;
    union { 
        Uns32 value;
    } DBGINST1;
    union { 
        Uns32 value;
    } CR0;
    union { 
        Uns32 value;
    } CR1;
    union { 
        Uns32 value;
    } CR2;
    union { 
        Uns32 value;
    } CR3;
    union { 
        Uns32 value;
    } CR4;
    union { 
        Uns32 value;
    } CRD;
    union { 
        Uns32 value;
    } WD;
    union { 
        Uns32 value;
    } periph_id_0;
    union { 
        Uns32 value;
    } periph_id_1;
    union { 
        Uns32 value;
    } periph_id_2;
    union { 
        Uns32 value;
    } periph_id_3;
    union { 
        Uns32 value;
    } pcell_id_0;
    union { 
        Uns32 value;
    } pcell_id_1;
    union { 
        Uns32 value;
    } pcell_id_2;
    union { 
        Uns32 value;
    } pcell_id_3;
} bportNS_abNS_dataT, *bportNS_abNS_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bportS_abS_dataT bportS_abS_data;

extern bportNS_abNS_dataT bportNS_abNS_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bportS;
    void                 *bportNS;
    ppmNetHandle          Int[8];
    ppmNetHandle          inta;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_READ_CB(regNoDefinitionReadNS);
PPM_READ_CB(regNoDefinitionReadS);
PPM_WRITE_CB(regNoDefinitionWriteNS);
PPM_WRITE_CB(regNoDefinitionWriteS);
PPM_NET_CB(reset_resetNet);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


///////////////////////////////// Local memory /////////////////////////////////

// To access local memory bportS/abS/buffer : (for example)
// char value = ((char*)handles.bportS)[BPORTS_ABS_BUFFER_OFFSET + myAddress];

#define BPORTS_ABS_BUFFER_OFFSET        0x0
#define BPORTS_ABS_BUFFER_SIZE          0x1000

// To access local memory bportNS/abNS/buffer : (for example)
// char value = ((char*)handles.bportNS)[BPORTNS_ABNS_BUFFER_OFFSET + myAddress];

#define BPORTNS_ABNS_BUFFER_OFFSET      0x0
#define BPORTNS_ABNS_BUFFER_SIZE        0x1000

////////////////////////////////// Mask macros /////////////////////////////////

#define BPORTS_ABS_DSR_WRMASK           0x1ff
#define BPORTS_ABS_DSR_WRNMASK          (0xfffffe00)
#define BPORTS_ABS_DSR_WIDTH            32
#define BPORTS_ABS_DPC_WRMASK           0xffffffff
#define BPORTS_ABS_DPC_WRNMASK          (0x0)
#define BPORTS_ABS_DPC_WIDTH            32
#define BPORTS_ABS_INTEN_WRMASK         0xffffffff
#define BPORTS_ABS_INTEN_WRNMASK        (0x0)
#define BPORTS_ABS_INTEN_WIDTH          32
#define BPORTS_ABS_INT_EVENT_RIS_WRMASK  0xffffffff
#define BPORTS_ABS_INT_EVENT_RIS_WRNMASK  (0x0)
#define BPORTS_ABS_INT_EVENT_RIS_WIDTH  32
#define BPORTS_ABS_INTMIS_WRMASK        0xffffffff
#define BPORTS_ABS_INTMIS_WRNMASK       (0x0)
#define BPORTS_ABS_INTMIS_WIDTH         32
#define BPORTS_ABS_INTCLR_WRMASK        0xffffffff
#define BPORTS_ABS_INTCLR_WRNMASK       (0x0)
#define BPORTS_ABS_INTCLR_WIDTH         32
#define BPORTS_ABS_FSRD_WRMASK          0xffffffff
#define BPORTS_ABS_FSRD_WRNMASK         (0x0)
#define BPORTS_ABS_FSRD_WIDTH           32
#define BPORTS_ABS_FSRC_WRMASK          0xffffffff
#define BPORTS_ABS_FSRC_WRNMASK         (0x0)
#define BPORTS_ABS_FSRC_WIDTH           32
#define BPORTS_ABS_FTRD_WRMASK          0xffffffff
#define BPORTS_ABS_FTRD_WRNMASK         (0x0)
#define BPORTS_ABS_FTRD_WIDTH           32
#define BPORTS_ABS_FTR0_WRMASK          0xffffffff
#define BPORTS_ABS_FTR0_WRNMASK         (0x0)
#define BPORTS_ABS_FTR0_WIDTH           32
#define BPORTS_ABS_FTR1_WRMASK          0xffffffff
#define BPORTS_ABS_FTR1_WRNMASK         (0x0)
#define BPORTS_ABS_FTR1_WIDTH           32
#define BPORTS_ABS_FTR2_WRMASK          0xffffffff
#define BPORTS_ABS_FTR2_WRNMASK         (0x0)
#define BPORTS_ABS_FTR2_WIDTH           32
#define BPORTS_ABS_FTR3_WRMASK          0xffffffff
#define BPORTS_ABS_FTR3_WRNMASK         (0x0)
#define BPORTS_ABS_FTR3_WIDTH           32
#define BPORTS_ABS_FTR4_WRMASK          0xffffffff
#define BPORTS_ABS_FTR4_WRNMASK         (0x0)
#define BPORTS_ABS_FTR4_WIDTH           32
#define BPORTS_ABS_FTR5_WRMASK          0xffffffff
#define BPORTS_ABS_FTR5_WRNMASK         (0x0)
#define BPORTS_ABS_FTR5_WIDTH           32
#define BPORTS_ABS_FTR6_WRMASK          0xffffffff
#define BPORTS_ABS_FTR6_WRNMASK         (0x0)
#define BPORTS_ABS_FTR6_WIDTH           32
#define BPORTS_ABS_FTR7_WRMASK          0xffffffff
#define BPORTS_ABS_FTR7_WRNMASK         (0x0)
#define BPORTS_ABS_FTR7_WIDTH           32
#define BPORTS_ABS_CSR0_WRMASK          0xffffffff
#define BPORTS_ABS_CSR0_WRNMASK         (0x0)
#define BPORTS_ABS_CSR0_WIDTH           32
#define BPORTS_ABS_CPC0_WRMASK          0xffffffff
#define BPORTS_ABS_CPC0_WRNMASK         (0x0)
#define BPORTS_ABS_CPC0_WIDTH           32
#define BPORTS_ABS_CSR1_WRMASK          0xffffffff
#define BPORTS_ABS_CSR1_WRNMASK         (0x0)
#define BPORTS_ABS_CSR1_WIDTH           32
#define BPORTS_ABS_CPC1_WRMASK          0xffffffff
#define BPORTS_ABS_CPC1_WRNMASK         (0x0)
#define BPORTS_ABS_CPC1_WIDTH           32
#define BPORTS_ABS_CSR2_WRMASK          0xffffffff
#define BPORTS_ABS_CSR2_WRNMASK         (0x0)
#define BPORTS_ABS_CSR2_WIDTH           32
#define BPORTS_ABS_CPC2_WRMASK          0xffffffff
#define BPORTS_ABS_CPC2_WRNMASK         (0x0)
#define BPORTS_ABS_CPC2_WIDTH           32
#define BPORTS_ABS_CSR3_WRMASK          0xffffffff
#define BPORTS_ABS_CSR3_WRNMASK         (0x0)
#define BPORTS_ABS_CSR3_WIDTH           32
#define BPORTS_ABS_CPC3_WRMASK          0xffffffff
#define BPORTS_ABS_CPC3_WRNMASK         (0x0)
#define BPORTS_ABS_CPC3_WIDTH           32
#define BPORTS_ABS_CSR4_WRMASK          0xffffffff
#define BPORTS_ABS_CSR4_WRNMASK         (0x0)
#define BPORTS_ABS_CSR4_WIDTH           32
#define BPORTS_ABS_CPC4_WRMASK          0xffffffff
#define BPORTS_ABS_CPC4_WRNMASK         (0x0)
#define BPORTS_ABS_CPC4_WIDTH           32
#define BPORTS_ABS_CSR5_WRMASK          0xffffffff
#define BPORTS_ABS_CSR5_WRNMASK         (0x0)
#define BPORTS_ABS_CSR5_WIDTH           32
#define BPORTS_ABS_CPC5_WRMASK          0xffffffff
#define BPORTS_ABS_CPC5_WRNMASK         (0x0)
#define BPORTS_ABS_CPC5_WIDTH           32
#define BPORTS_ABS_CSR6_WRMASK          0xffffffff
#define BPORTS_ABS_CSR6_WRNMASK         (0x0)
#define BPORTS_ABS_CSR6_WIDTH           32
#define BPORTS_ABS_CPC6_WRMASK          0xffffffff
#define BPORTS_ABS_CPC6_WRNMASK         (0x0)
#define BPORTS_ABS_CPC6_WIDTH           32
#define BPORTS_ABS_CSR7_WRMASK          0xffffffff
#define BPORTS_ABS_CSR7_WRNMASK         (0x0)
#define BPORTS_ABS_CSR7_WIDTH           32
#define BPORTS_ABS_CPC7_WRMASK          0xffffffff
#define BPORTS_ABS_CPC7_WRNMASK         (0x0)
#define BPORTS_ABS_CPC7_WIDTH           32
#define BPORTS_ABS_SAR0_WRMASK          0xffffffff
#define BPORTS_ABS_SAR0_WRNMASK         (0x0)
#define BPORTS_ABS_SAR0_WIDTH           32
#define BPORTS_ABS_DAR0_WRMASK          0xffffffff
#define BPORTS_ABS_DAR0_WRNMASK         (0x0)
#define BPORTS_ABS_DAR0_WIDTH           32
#define BPORTS_ABS_CCR0_WRMASK          0xffffffff
#define BPORTS_ABS_CCR0_WRNMASK         (0x0)
#define BPORTS_ABS_CCR0_WIDTH           32
#define BPORTS_ABS_LC0_0_WRMASK         0xffffffff
#define BPORTS_ABS_LC0_0_WRNMASK        (0x0)
#define BPORTS_ABS_LC0_0_WIDTH          32
#define BPORTS_ABS_LC1_0_WRMASK         0xffffffff
#define BPORTS_ABS_LC1_0_WRNMASK        (0x0)
#define BPORTS_ABS_LC1_0_WIDTH          32
#define BPORTS_ABS_SAR1_WRMASK          0xffffffff
#define BPORTS_ABS_SAR1_WRNMASK         (0x0)
#define BPORTS_ABS_SAR1_WIDTH           32
#define BPORTS_ABS_DAR1_WRMASK          0xffffffff
#define BPORTS_ABS_DAR1_WRNMASK         (0x0)
#define BPORTS_ABS_DAR1_WIDTH           32
#define BPORTS_ABS_CCR1_WRMASK          0xffffffff
#define BPORTS_ABS_CCR1_WRNMASK         (0x0)
#define BPORTS_ABS_CCR1_WIDTH           32
#define BPORTS_ABS_LC0_1_WRMASK         0xffffffff
#define BPORTS_ABS_LC0_1_WRNMASK        (0x0)
#define BPORTS_ABS_LC0_1_WIDTH          32
#define BPORTS_ABS_LC1_1_WRMASK         0xffffffff
#define BPORTS_ABS_LC1_1_WRNMASK        (0x0)
#define BPORTS_ABS_LC1_1_WIDTH          32
#define BPORTS_ABS_SAR2_WRMASK          0xffffffff
#define BPORTS_ABS_SAR2_WRNMASK         (0x0)
#define BPORTS_ABS_SAR2_WIDTH           32
#define BPORTS_ABS_DAR2_WRMASK          0xffffffff
#define BPORTS_ABS_DAR2_WRNMASK         (0x0)
#define BPORTS_ABS_DAR2_WIDTH           32
#define BPORTS_ABS_CCR2_WRMASK          0xffffffff
#define BPORTS_ABS_CCR2_WRNMASK         (0x0)
#define BPORTS_ABS_CCR2_WIDTH           32
#define BPORTS_ABS_LC0_2_WRMASK         0xffffffff
#define BPORTS_ABS_LC0_2_WRNMASK        (0x0)
#define BPORTS_ABS_LC0_2_WIDTH          32
#define BPORTS_ABS_LC1_2_WRMASK         0xffffffff
#define BPORTS_ABS_LC1_2_WRNMASK        (0x0)
#define BPORTS_ABS_LC1_2_WIDTH          32
#define BPORTS_ABS_SAR3_WRMASK          0xffffffff
#define BPORTS_ABS_SAR3_WRNMASK         (0x0)
#define BPORTS_ABS_SAR3_WIDTH           32
#define BPORTS_ABS_DAR3_WRMASK          0xffffffff
#define BPORTS_ABS_DAR3_WRNMASK         (0x0)
#define BPORTS_ABS_DAR3_WIDTH           32
#define BPORTS_ABS_CCR3_WRMASK          0xffffffff
#define BPORTS_ABS_CCR3_WRNMASK         (0x0)
#define BPORTS_ABS_CCR3_WIDTH           32
#define BPORTS_ABS_LC0_3_WRMASK         0xffffffff
#define BPORTS_ABS_LC0_3_WRNMASK        (0x0)
#define BPORTS_ABS_LC0_3_WIDTH          32
#define BPORTS_ABS_LC1_3_WRMASK         0xffffffff
#define BPORTS_ABS_LC1_3_WRNMASK        (0x0)
#define BPORTS_ABS_LC1_3_WIDTH          32
#define BPORTS_ABS_SAR4_WRMASK          0xffffffff
#define BPORTS_ABS_SAR4_WRNMASK         (0x0)
#define BPORTS_ABS_SAR4_WIDTH           32
#define BPORTS_ABS_DAR4_WRMASK          0xffffffff
#define BPORTS_ABS_DAR4_WRNMASK         (0x0)
#define BPORTS_ABS_DAR4_WIDTH           32
#define BPORTS_ABS_CCR4_WRMASK          0xffffffff
#define BPORTS_ABS_CCR4_WRNMASK         (0x0)
#define BPORTS_ABS_CCR4_WIDTH           32
#define BPORTS_ABS_LC0_4_WRMASK         0xffffffff
#define BPORTS_ABS_LC0_4_WRNMASK        (0x0)
#define BPORTS_ABS_LC0_4_WIDTH          32
#define BPORTS_ABS_LC1_4_WRMASK         0xffffffff
#define BPORTS_ABS_LC1_4_WRNMASK        (0x0)
#define BPORTS_ABS_LC1_4_WIDTH          32
#define BPORTS_ABS_SAR5_WRMASK          0xffffffff
#define BPORTS_ABS_SAR5_WRNMASK         (0x0)
#define BPORTS_ABS_SAR5_WIDTH           32
#define BPORTS_ABS_DAR5_WRMASK          0xffffffff
#define BPORTS_ABS_DAR5_WRNMASK         (0x0)
#define BPORTS_ABS_DAR5_WIDTH           32
#define BPORTS_ABS_CCR5_WRMASK          0xffffffff
#define BPORTS_ABS_CCR5_WRNMASK         (0x0)
#define BPORTS_ABS_CCR5_WIDTH           32
#define BPORTS_ABS_LC0_5_WRMASK         0xffffffff
#define BPORTS_ABS_LC0_5_WRNMASK        (0x0)
#define BPORTS_ABS_LC0_5_WIDTH          32
#define BPORTS_ABS_LC1_5_WRMASK         0xffffffff
#define BPORTS_ABS_LC1_5_WRNMASK        (0x0)
#define BPORTS_ABS_LC1_5_WIDTH          32
#define BPORTS_ABS_SAR6_WRMASK          0xffffffff
#define BPORTS_ABS_SAR6_WRNMASK         (0x0)
#define BPORTS_ABS_SAR6_WIDTH           32
#define BPORTS_ABS_DAR6_WRMASK          0xffffffff
#define BPORTS_ABS_DAR6_WRNMASK         (0x0)
#define BPORTS_ABS_DAR6_WIDTH           32
#define BPORTS_ABS_CCR6_WRMASK          0xffffffff
#define BPORTS_ABS_CCR6_WRNMASK         (0x0)
#define BPORTS_ABS_CCR6_WIDTH           32
#define BPORTS_ABS_LC0_6_WRMASK         0xffffffff
#define BPORTS_ABS_LC0_6_WRNMASK        (0x0)
#define BPORTS_ABS_LC0_6_WIDTH          32
#define BPORTS_ABS_LC1_6_WRMASK         0xffffffff
#define BPORTS_ABS_LC1_6_WRNMASK        (0x0)
#define BPORTS_ABS_LC1_6_WIDTH          32
#define BPORTS_ABS_SAR7_WRMASK          0xffffffff
#define BPORTS_ABS_SAR7_WRNMASK         (0x0)
#define BPORTS_ABS_SAR7_WIDTH           32
#define BPORTS_ABS_DAR7_WRMASK          0xffffffff
#define BPORTS_ABS_DAR7_WRNMASK         (0x0)
#define BPORTS_ABS_DAR7_WIDTH           32
#define BPORTS_ABS_CCR7_WRMASK          0xffffffff
#define BPORTS_ABS_CCR7_WRNMASK         (0x0)
#define BPORTS_ABS_CCR7_WIDTH           32
#define BPORTS_ABS_LC0_7_WRMASK         0xffffffff
#define BPORTS_ABS_LC0_7_WRNMASK        (0x0)
#define BPORTS_ABS_LC0_7_WIDTH          32
#define BPORTS_ABS_LC1_7_WRMASK         0xffffffff
#define BPORTS_ABS_LC1_7_WRNMASK        (0x0)
#define BPORTS_ABS_LC1_7_WIDTH          32
#define BPORTS_ABS_DBGSTATUS_WRMASK     0xffffffff
#define BPORTS_ABS_DBGSTATUS_WRNMASK    (0x0)
#define BPORTS_ABS_DBGSTATUS_WIDTH      32
#define BPORTS_ABS_DBGCMD_WRMASK        0xffffffff
#define BPORTS_ABS_DBGCMD_WRNMASK       (0x0)
#define BPORTS_ABS_DBGCMD_WIDTH         32
#define BPORTS_ABS_DBGINST0_WRMASK      0xffffffff
#define BPORTS_ABS_DBGINST0_WRNMASK     (0x0)
#define BPORTS_ABS_DBGINST0_WIDTH       32
#define BPORTS_ABS_DBGINST1_WRMASK      0xffffffff
#define BPORTS_ABS_DBGINST1_WRNMASK     (0x0)
#define BPORTS_ABS_DBGINST1_WIDTH       32
#define BPORTS_ABS_CR0_WRMASK           0xffffffff
#define BPORTS_ABS_CR0_WRNMASK          (0x0)
#define BPORTS_ABS_CR0_WIDTH            32
#define BPORTS_ABS_CR1_WRMASK           0xffffffff
#define BPORTS_ABS_CR1_WRNMASK          (0x0)
#define BPORTS_ABS_CR1_WIDTH            32
#define BPORTS_ABS_CR2_WRMASK           0xffffffff
#define BPORTS_ABS_CR2_WRNMASK          (0x0)
#define BPORTS_ABS_CR2_WIDTH            32
#define BPORTS_ABS_CR3_WRMASK           0xffffffff
#define BPORTS_ABS_CR3_WRNMASK          (0x0)
#define BPORTS_ABS_CR3_WIDTH            32
#define BPORTS_ABS_CR4_WRMASK           0xffffffff
#define BPORTS_ABS_CR4_WRNMASK          (0x0)
#define BPORTS_ABS_CR4_WIDTH            32
#define BPORTS_ABS_CRD_WRMASK           0xffffffff
#define BPORTS_ABS_CRD_WRNMASK          (0x0)
#define BPORTS_ABS_CRD_WIDTH            32
#define BPORTS_ABS_WD_WRMASK            0xffffffff
#define BPORTS_ABS_WD_WRNMASK           (0x0)
#define BPORTS_ABS_WD_WIDTH             32
#define BPORTS_ABS_PERIPH_ID_0_WRMASK   0xffffffff
#define BPORTS_ABS_PERIPH_ID_0_WRNMASK  (0x0)
#define BPORTS_ABS_PERIPH_ID_0_WIDTH    32
#define BPORTS_ABS_PERIPH_ID_1_WRMASK   0xffffffff
#define BPORTS_ABS_PERIPH_ID_1_WRNMASK  (0x0)
#define BPORTS_ABS_PERIPH_ID_1_WIDTH    32
#define BPORTS_ABS_PERIPH_ID_2_WRMASK   0xffffffff
#define BPORTS_ABS_PERIPH_ID_2_WRNMASK  (0x0)
#define BPORTS_ABS_PERIPH_ID_2_WIDTH    32
#define BPORTS_ABS_PERIPH_ID_3_WRMASK   0xffffffff
#define BPORTS_ABS_PERIPH_ID_3_WRNMASK  (0x0)
#define BPORTS_ABS_PERIPH_ID_3_WIDTH    32
#define BPORTS_ABS_PCELL_ID_0_WRMASK    0xffffffff
#define BPORTS_ABS_PCELL_ID_0_WRNMASK   (0x0)
#define BPORTS_ABS_PCELL_ID_0_WIDTH     32
#define BPORTS_ABS_PCELL_ID_1_WRMASK    0xffffffff
#define BPORTS_ABS_PCELL_ID_1_WRNMASK   (0x0)
#define BPORTS_ABS_PCELL_ID_1_WIDTH     32
#define BPORTS_ABS_PCELL_ID_2_WRMASK    0xffffffff
#define BPORTS_ABS_PCELL_ID_2_WRNMASK   (0x0)
#define BPORTS_ABS_PCELL_ID_2_WIDTH     32
#define BPORTS_ABS_PCELL_ID_3_WRMASK    0xffffffff
#define BPORTS_ABS_PCELL_ID_3_WRNMASK   (0x0)
#define BPORTS_ABS_PCELL_ID_3_WIDTH     32
#define BPORTNS_ABNS_DSR_WRMASK         0x1ff
#define BPORTNS_ABNS_DSR_WRNMASK        (0xfffffe00)
#define BPORTNS_ABNS_DSR_WIDTH          32
#define BPORTNS_ABNS_DPC_WRMASK         0xffffffff
#define BPORTNS_ABNS_DPC_WRNMASK        (0x0)
#define BPORTNS_ABNS_DPC_WIDTH          32
#define BPORTNS_ABNS_INTEN_WRMASK       0xffffffff
#define BPORTNS_ABNS_INTEN_WRNMASK      (0x0)
#define BPORTNS_ABNS_INTEN_WIDTH        32
#define BPORTNS_ABNS_INT_EVENT_RIS_WRMASK  0xffffffff
#define BPORTNS_ABNS_INT_EVENT_RIS_WRNMASK  (0x0)
#define BPORTNS_ABNS_INT_EVENT_RIS_WIDTH  32
#define BPORTNS_ABNS_INTMIS_WRMASK      0xffffffff
#define BPORTNS_ABNS_INTMIS_WRNMASK     (0x0)
#define BPORTNS_ABNS_INTMIS_WIDTH       32
#define BPORTNS_ABNS_INTCLR_WRMASK      0xffffffff
#define BPORTNS_ABNS_INTCLR_WRNMASK     (0x0)
#define BPORTNS_ABNS_INTCLR_WIDTH       32
#define BPORTNS_ABNS_FSRD_WRMASK        0xffffffff
#define BPORTNS_ABNS_FSRD_WRNMASK       (0x0)
#define BPORTNS_ABNS_FSRD_WIDTH         32
#define BPORTNS_ABNS_FSRC_WRMASK        0xffffffff
#define BPORTNS_ABNS_FSRC_WRNMASK       (0x0)
#define BPORTNS_ABNS_FSRC_WIDTH         32
#define BPORTNS_ABNS_FTRD_WRMASK        0xffffffff
#define BPORTNS_ABNS_FTRD_WRNMASK       (0x0)
#define BPORTNS_ABNS_FTRD_WIDTH         32
#define BPORTNS_ABNS_FTR0_WRMASK        0xffffffff
#define BPORTNS_ABNS_FTR0_WRNMASK       (0x0)
#define BPORTNS_ABNS_FTR0_WIDTH         32
#define BPORTNS_ABNS_FTR1_WRMASK        0xffffffff
#define BPORTNS_ABNS_FTR1_WRNMASK       (0x0)
#define BPORTNS_ABNS_FTR1_WIDTH         32
#define BPORTNS_ABNS_FTR2_WRMASK        0xffffffff
#define BPORTNS_ABNS_FTR2_WRNMASK       (0x0)
#define BPORTNS_ABNS_FTR2_WIDTH         32
#define BPORTNS_ABNS_FTR3_WRMASK        0xffffffff
#define BPORTNS_ABNS_FTR3_WRNMASK       (0x0)
#define BPORTNS_ABNS_FTR3_WIDTH         32
#define BPORTNS_ABNS_FTR4_WRMASK        0xffffffff
#define BPORTNS_ABNS_FTR4_WRNMASK       (0x0)
#define BPORTNS_ABNS_FTR4_WIDTH         32
#define BPORTNS_ABNS_FTR5_WRMASK        0xffffffff
#define BPORTNS_ABNS_FTR5_WRNMASK       (0x0)
#define BPORTNS_ABNS_FTR5_WIDTH         32
#define BPORTNS_ABNS_FTR6_WRMASK        0xffffffff
#define BPORTNS_ABNS_FTR6_WRNMASK       (0x0)
#define BPORTNS_ABNS_FTR6_WIDTH         32
#define BPORTNS_ABNS_FTR7_WRMASK        0xffffffff
#define BPORTNS_ABNS_FTR7_WRNMASK       (0x0)
#define BPORTNS_ABNS_FTR7_WIDTH         32
#define BPORTNS_ABNS_CSR0_WRMASK        0xffffffff
#define BPORTNS_ABNS_CSR0_WRNMASK       (0x0)
#define BPORTNS_ABNS_CSR0_WIDTH         32
#define BPORTNS_ABNS_CPC0_WRMASK        0xffffffff
#define BPORTNS_ABNS_CPC0_WRNMASK       (0x0)
#define BPORTNS_ABNS_CPC0_WIDTH         32
#define BPORTNS_ABNS_CSR1_WRMASK        0xffffffff
#define BPORTNS_ABNS_CSR1_WRNMASK       (0x0)
#define BPORTNS_ABNS_CSR1_WIDTH         32
#define BPORTNS_ABNS_CPC1_WRMASK        0xffffffff
#define BPORTNS_ABNS_CPC1_WRNMASK       (0x0)
#define BPORTNS_ABNS_CPC1_WIDTH         32
#define BPORTNS_ABNS_CSR2_WRMASK        0xffffffff
#define BPORTNS_ABNS_CSR2_WRNMASK       (0x0)
#define BPORTNS_ABNS_CSR2_WIDTH         32
#define BPORTNS_ABNS_CPC2_WRMASK        0xffffffff
#define BPORTNS_ABNS_CPC2_WRNMASK       (0x0)
#define BPORTNS_ABNS_CPC2_WIDTH         32
#define BPORTNS_ABNS_CSR3_WRMASK        0xffffffff
#define BPORTNS_ABNS_CSR3_WRNMASK       (0x0)
#define BPORTNS_ABNS_CSR3_WIDTH         32
#define BPORTNS_ABNS_CPC3_WRMASK        0xffffffff
#define BPORTNS_ABNS_CPC3_WRNMASK       (0x0)
#define BPORTNS_ABNS_CPC3_WIDTH         32
#define BPORTNS_ABNS_CSR4_WRMASK        0xffffffff
#define BPORTNS_ABNS_CSR4_WRNMASK       (0x0)
#define BPORTNS_ABNS_CSR4_WIDTH         32
#define BPORTNS_ABNS_CPC4_WRMASK        0xffffffff
#define BPORTNS_ABNS_CPC4_WRNMASK       (0x0)
#define BPORTNS_ABNS_CPC4_WIDTH         32
#define BPORTNS_ABNS_CSR5_WRMASK        0xffffffff
#define BPORTNS_ABNS_CSR5_WRNMASK       (0x0)
#define BPORTNS_ABNS_CSR5_WIDTH         32
#define BPORTNS_ABNS_CPC5_WRMASK        0xffffffff
#define BPORTNS_ABNS_CPC5_WRNMASK       (0x0)
#define BPORTNS_ABNS_CPC5_WIDTH         32
#define BPORTNS_ABNS_CSR6_WRMASK        0xffffffff
#define BPORTNS_ABNS_CSR6_WRNMASK       (0x0)
#define BPORTNS_ABNS_CSR6_WIDTH         32
#define BPORTNS_ABNS_CPC6_WRMASK        0xffffffff
#define BPORTNS_ABNS_CPC6_WRNMASK       (0x0)
#define BPORTNS_ABNS_CPC6_WIDTH         32
#define BPORTNS_ABNS_CSR7_WRMASK        0xffffffff
#define BPORTNS_ABNS_CSR7_WRNMASK       (0x0)
#define BPORTNS_ABNS_CSR7_WIDTH         32
#define BPORTNS_ABNS_CPC7_WRMASK        0xffffffff
#define BPORTNS_ABNS_CPC7_WRNMASK       (0x0)
#define BPORTNS_ABNS_CPC7_WIDTH         32
#define BPORTNS_ABNS_SAR0_WRMASK        0xffffffff
#define BPORTNS_ABNS_SAR0_WRNMASK       (0x0)
#define BPORTNS_ABNS_SAR0_WIDTH         32
#define BPORTNS_ABNS_DAR0_WRMASK        0xffffffff
#define BPORTNS_ABNS_DAR0_WRNMASK       (0x0)
#define BPORTNS_ABNS_DAR0_WIDTH         32
#define BPORTNS_ABNS_CCR0_WRMASK        0xffffffff
#define BPORTNS_ABNS_CCR0_WRNMASK       (0x0)
#define BPORTNS_ABNS_CCR0_WIDTH         32
#define BPORTNS_ABNS_LC0_0_WRMASK       0xffffffff
#define BPORTNS_ABNS_LC0_0_WRNMASK      (0x0)
#define BPORTNS_ABNS_LC0_0_WIDTH        32
#define BPORTNS_ABNS_LC1_0_WRMASK       0xffffffff
#define BPORTNS_ABNS_LC1_0_WRNMASK      (0x0)
#define BPORTNS_ABNS_LC1_0_WIDTH        32
#define BPORTNS_ABNS_SAR1_WRMASK        0xffffffff
#define BPORTNS_ABNS_SAR1_WRNMASK       (0x0)
#define BPORTNS_ABNS_SAR1_WIDTH         32
#define BPORTNS_ABNS_DAR1_WRMASK        0xffffffff
#define BPORTNS_ABNS_DAR1_WRNMASK       (0x0)
#define BPORTNS_ABNS_DAR1_WIDTH         32
#define BPORTNS_ABNS_CCR1_WRMASK        0xffffffff
#define BPORTNS_ABNS_CCR1_WRNMASK       (0x0)
#define BPORTNS_ABNS_CCR1_WIDTH         32
#define BPORTNS_ABNS_LC0_1_WRMASK       0xffffffff
#define BPORTNS_ABNS_LC0_1_WRNMASK      (0x0)
#define BPORTNS_ABNS_LC0_1_WIDTH        32
#define BPORTNS_ABNS_LC1_1_WRMASK       0xffffffff
#define BPORTNS_ABNS_LC1_1_WRNMASK      (0x0)
#define BPORTNS_ABNS_LC1_1_WIDTH        32
#define BPORTNS_ABNS_SAR2_WRMASK        0xffffffff
#define BPORTNS_ABNS_SAR2_WRNMASK       (0x0)
#define BPORTNS_ABNS_SAR2_WIDTH         32
#define BPORTNS_ABNS_DAR2_WRMASK        0xffffffff
#define BPORTNS_ABNS_DAR2_WRNMASK       (0x0)
#define BPORTNS_ABNS_DAR2_WIDTH         32
#define BPORTNS_ABNS_CCR2_WRMASK        0xffffffff
#define BPORTNS_ABNS_CCR2_WRNMASK       (0x0)
#define BPORTNS_ABNS_CCR2_WIDTH         32
#define BPORTNS_ABNS_LC0_2_WRMASK       0xffffffff
#define BPORTNS_ABNS_LC0_2_WRNMASK      (0x0)
#define BPORTNS_ABNS_LC0_2_WIDTH        32
#define BPORTNS_ABNS_LC1_2_WRMASK       0xffffffff
#define BPORTNS_ABNS_LC1_2_WRNMASK      (0x0)
#define BPORTNS_ABNS_LC1_2_WIDTH        32
#define BPORTNS_ABNS_SAR3_WRMASK        0xffffffff
#define BPORTNS_ABNS_SAR3_WRNMASK       (0x0)
#define BPORTNS_ABNS_SAR3_WIDTH         32
#define BPORTNS_ABNS_DAR3_WRMASK        0xffffffff
#define BPORTNS_ABNS_DAR3_WRNMASK       (0x0)
#define BPORTNS_ABNS_DAR3_WIDTH         32
#define BPORTNS_ABNS_CCR3_WRMASK        0xffffffff
#define BPORTNS_ABNS_CCR3_WRNMASK       (0x0)
#define BPORTNS_ABNS_CCR3_WIDTH         32
#define BPORTNS_ABNS_LC0_3_WRMASK       0xffffffff
#define BPORTNS_ABNS_LC0_3_WRNMASK      (0x0)
#define BPORTNS_ABNS_LC0_3_WIDTH        32
#define BPORTNS_ABNS_LC1_3_WRMASK       0xffffffff
#define BPORTNS_ABNS_LC1_3_WRNMASK      (0x0)
#define BPORTNS_ABNS_LC1_3_WIDTH        32
#define BPORTNS_ABNS_SAR4_WRMASK        0xffffffff
#define BPORTNS_ABNS_SAR4_WRNMASK       (0x0)
#define BPORTNS_ABNS_SAR4_WIDTH         32
#define BPORTNS_ABNS_DAR4_WRMASK        0xffffffff
#define BPORTNS_ABNS_DAR4_WRNMASK       (0x0)
#define BPORTNS_ABNS_DAR4_WIDTH         32
#define BPORTNS_ABNS_CCR4_WRMASK        0xffffffff
#define BPORTNS_ABNS_CCR4_WRNMASK       (0x0)
#define BPORTNS_ABNS_CCR4_WIDTH         32
#define BPORTNS_ABNS_LC0_4_WRMASK       0xffffffff
#define BPORTNS_ABNS_LC0_4_WRNMASK      (0x0)
#define BPORTNS_ABNS_LC0_4_WIDTH        32
#define BPORTNS_ABNS_LC1_4_WRMASK       0xffffffff
#define BPORTNS_ABNS_LC1_4_WRNMASK      (0x0)
#define BPORTNS_ABNS_LC1_4_WIDTH        32
#define BPORTNS_ABNS_SAR5_WRMASK        0xffffffff
#define BPORTNS_ABNS_SAR5_WRNMASK       (0x0)
#define BPORTNS_ABNS_SAR5_WIDTH         32
#define BPORTNS_ABNS_DAR5_WRMASK        0xffffffff
#define BPORTNS_ABNS_DAR5_WRNMASK       (0x0)
#define BPORTNS_ABNS_DAR5_WIDTH         32
#define BPORTNS_ABNS_CCR5_WRMASK        0xffffffff
#define BPORTNS_ABNS_CCR5_WRNMASK       (0x0)
#define BPORTNS_ABNS_CCR5_WIDTH         32
#define BPORTNS_ABNS_LC0_5_WRMASK       0xffffffff
#define BPORTNS_ABNS_LC0_5_WRNMASK      (0x0)
#define BPORTNS_ABNS_LC0_5_WIDTH        32
#define BPORTNS_ABNS_LC1_5_WRMASK       0xffffffff
#define BPORTNS_ABNS_LC1_5_WRNMASK      (0x0)
#define BPORTNS_ABNS_LC1_5_WIDTH        32
#define BPORTNS_ABNS_SAR6_WRMASK        0xffffffff
#define BPORTNS_ABNS_SAR6_WRNMASK       (0x0)
#define BPORTNS_ABNS_SAR6_WIDTH         32
#define BPORTNS_ABNS_DAR6_WRMASK        0xffffffff
#define BPORTNS_ABNS_DAR6_WRNMASK       (0x0)
#define BPORTNS_ABNS_DAR6_WIDTH         32
#define BPORTNS_ABNS_CCR6_WRMASK        0xffffffff
#define BPORTNS_ABNS_CCR6_WRNMASK       (0x0)
#define BPORTNS_ABNS_CCR6_WIDTH         32
#define BPORTNS_ABNS_LC0_6_WRMASK       0xffffffff
#define BPORTNS_ABNS_LC0_6_WRNMASK      (0x0)
#define BPORTNS_ABNS_LC0_6_WIDTH        32
#define BPORTNS_ABNS_LC1_6_WRMASK       0xffffffff
#define BPORTNS_ABNS_LC1_6_WRNMASK      (0x0)
#define BPORTNS_ABNS_LC1_6_WIDTH        32
#define BPORTNS_ABNS_SAR7_WRMASK        0xffffffff
#define BPORTNS_ABNS_SAR7_WRNMASK       (0x0)
#define BPORTNS_ABNS_SAR7_WIDTH         32
#define BPORTNS_ABNS_DAR7_WRMASK        0xffffffff
#define BPORTNS_ABNS_DAR7_WRNMASK       (0x0)
#define BPORTNS_ABNS_DAR7_WIDTH         32
#define BPORTNS_ABNS_CCR7_WRMASK        0xffffffff
#define BPORTNS_ABNS_CCR7_WRNMASK       (0x0)
#define BPORTNS_ABNS_CCR7_WIDTH         32
#define BPORTNS_ABNS_LC0_7_WRMASK       0xffffffff
#define BPORTNS_ABNS_LC0_7_WRNMASK      (0x0)
#define BPORTNS_ABNS_LC0_7_WIDTH        32
#define BPORTNS_ABNS_LC1_7_WRMASK       0xffffffff
#define BPORTNS_ABNS_LC1_7_WRNMASK      (0x0)
#define BPORTNS_ABNS_LC1_7_WIDTH        32
#define BPORTNS_ABNS_DBGSTATUS_WRMASK   0xffffffff
#define BPORTNS_ABNS_DBGSTATUS_WRNMASK  (0x0)
#define BPORTNS_ABNS_DBGSTATUS_WIDTH    32
#define BPORTNS_ABNS_DBGCMD_WRMASK      0xffffffff
#define BPORTNS_ABNS_DBGCMD_WRNMASK     (0x0)
#define BPORTNS_ABNS_DBGCMD_WIDTH       32
#define BPORTNS_ABNS_DBGINST0_WRMASK    0xffffffff
#define BPORTNS_ABNS_DBGINST0_WRNMASK   (0x0)
#define BPORTNS_ABNS_DBGINST0_WIDTH     32
#define BPORTNS_ABNS_DBGINST1_WRMASK    0xffffffff
#define BPORTNS_ABNS_DBGINST1_WRNMASK   (0x0)
#define BPORTNS_ABNS_DBGINST1_WIDTH     32
#define BPORTNS_ABNS_CR0_WRMASK         0xffffffff
#define BPORTNS_ABNS_CR0_WRNMASK        (0x0)
#define BPORTNS_ABNS_CR0_WIDTH          32
#define BPORTNS_ABNS_CR1_WRMASK         0xffffffff
#define BPORTNS_ABNS_CR1_WRNMASK        (0x0)
#define BPORTNS_ABNS_CR1_WIDTH          32
#define BPORTNS_ABNS_CR2_WRMASK         0xffffffff
#define BPORTNS_ABNS_CR2_WRNMASK        (0x0)
#define BPORTNS_ABNS_CR2_WIDTH          32
#define BPORTNS_ABNS_CR3_WRMASK         0xffffffff
#define BPORTNS_ABNS_CR3_WRNMASK        (0x0)
#define BPORTNS_ABNS_CR3_WIDTH          32
#define BPORTNS_ABNS_CR4_WRMASK         0xffffffff
#define BPORTNS_ABNS_CR4_WRNMASK        (0x0)
#define BPORTNS_ABNS_CR4_WIDTH          32
#define BPORTNS_ABNS_CRD_WRMASK         0xffffffff
#define BPORTNS_ABNS_CRD_WRNMASK        (0x0)
#define BPORTNS_ABNS_CRD_WIDTH          32
#define BPORTNS_ABNS_WD_WRMASK          0xffffffff
#define BPORTNS_ABNS_WD_WRNMASK         (0x0)
#define BPORTNS_ABNS_WD_WIDTH           32
#define BPORTNS_ABNS_PERIPH_ID_0_WRMASK  0xffffffff
#define BPORTNS_ABNS_PERIPH_ID_0_WRNMASK  (0x0)
#define BPORTNS_ABNS_PERIPH_ID_0_WIDTH  32
#define BPORTNS_ABNS_PERIPH_ID_1_WRMASK  0xffffffff
#define BPORTNS_ABNS_PERIPH_ID_1_WRNMASK  (0x0)
#define BPORTNS_ABNS_PERIPH_ID_1_WIDTH  32
#define BPORTNS_ABNS_PERIPH_ID_2_WRMASK  0xffffffff
#define BPORTNS_ABNS_PERIPH_ID_2_WRNMASK  (0x0)
#define BPORTNS_ABNS_PERIPH_ID_2_WIDTH  32
#define BPORTNS_ABNS_PERIPH_ID_3_WRMASK  0xffffffff
#define BPORTNS_ABNS_PERIPH_ID_3_WRNMASK  (0x0)
#define BPORTNS_ABNS_PERIPH_ID_3_WIDTH  32
#define BPORTNS_ABNS_PCELL_ID_0_WRMASK  0xffffffff
#define BPORTNS_ABNS_PCELL_ID_0_WRNMASK  (0x0)
#define BPORTNS_ABNS_PCELL_ID_0_WIDTH   32
#define BPORTNS_ABNS_PCELL_ID_1_WRMASK  0xffffffff
#define BPORTNS_ABNS_PCELL_ID_1_WRNMASK  (0x0)
#define BPORTNS_ABNS_PCELL_ID_1_WIDTH   32
#define BPORTNS_ABNS_PCELL_ID_2_WRMASK  0xffffffff
#define BPORTNS_ABNS_PCELL_ID_2_WRNMASK  (0x0)
#define BPORTNS_ABNS_PCELL_ID_2_WIDTH   32
#define BPORTNS_ABNS_PCELL_ID_3_WRMASK  0xffffffff
#define BPORTNS_ABNS_PCELL_ID_3_WRNMASK  (0x0)
#define BPORTNS_ABNS_PCELL_ID_3_WIDTH   32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
