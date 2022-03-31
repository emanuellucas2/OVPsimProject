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
        struct {
            Uns32 DAP_EN : 3;
            Uns32 DBGEN : 1;
            Uns32 NIDEN : 1;
            Uns32 SPIDEN : 1;
            Uns32 SPNIDEN : 1;
            Uns32 SEC_EN : 1;
            Uns32 SEU_EN : 1;
            Uns32 PCFG_AES_EN : 3;
            Uns32 PCFG_AES_FUSE : 1;
            Uns32 __pad13 : 10;
            Uns32 JTAG_CHAIN_DIS : 1;
            Uns32 MULTIBOOT_EN : 1;
            Uns32 PCAP_RATE_EN : 1;
            Uns32 PCAP_MODE : 1;
            Uns32 PCAP_PR : 1;
            Uns32 __pad28 : 1;
            Uns32 PCFG_POR_CNT_4K : 1;
            Uns32 PCFG_PROG_B : 1;
            Uns32 FORCE_RST : 1;
        } bits;
    } CTRL;
    union { 
        Uns32 value;
        struct {
            Uns32 DBG_LOCK : 1;
            Uns32 SEC_LOCK : 1;
            Uns32 SEU_LOCK : 1;
            Uns32 AES_EN_LOCK : 1;
            Uns32 AES_FUSE_LOCK : 1;
        } bits;
    } LOCK;
    union { 
        Uns32 value;
    } CFG;
    union { 
        Uns32 value;
    } INT_STS;
    union { 
        Uns32 value;
    } INT_MASK;
    union { 
        Uns32 value;
    } STATUS;
    union { 
        Uns32 value;
    } DMA_SRC_ADDR;
    union { 
        Uns32 value;
    } DMA_DST_ADDR;
    union { 
        Uns32 value;
    } DMA_SRC_LEN;
    union { 
        Uns32 value;
    } DMA_DEST_LEN;
    union { 
        Uns32 value;
    } ROM_SHADOW;
    union { 
        Uns32 value;
    } MULTIBOOT_ADDR;
    union { 
        Uns32 value;
    } UNLOCK;
    union { 
        Uns32 value;
    } MCTRL;
    union { 
        Uns32 value;
        struct {
            Uns32 IGAP : 5;
            Uns32 __pad5 : 3;
            Uns32 TCKARTE : 2;
            Uns32 __pad10 : 2;
            Uns32 REDGE : 1;
            Uns32 WEDGE : 1;
            Uns32 __pad14 : 2;
            Uns32 DFIFOTH : 4;
            Uns32 CFIFOTH : 4;
            Uns32 __pad24 : 7;
            Uns32 ENABLE : 1;
        } bits;
    } XADCIF_CFG;
    union { 
        Uns32 value;
        struct {
            Uns32 ALM : 7;
            Uns32 OT : 1;
            Uns32 DFIFO_GTH : 1;
            Uns32 CFIFO_LTH : 1;
        } bits;
    } XADCIF_INT_STS;
    union { 
        Uns32 value;
        struct {
            Uns32 ALM : 7;
            Uns32 OT : 1;
            Uns32 DFIFO_GTH : 1;
            Uns32 CFIFO_LTH : 1;
        } bits;
    } XADCIF_INT_MASK;
    union { 
        Uns32 value;
        struct {
            Uns32 ALM : 6;
            Uns32 __pad6 : 1;
            Uns32 OT : 1;
            Uns32 DFIFOE : 1;
            Uns32 DFIFOF : 1;
            Uns32 CFIFOE : 1;
            Uns32 CFIFOF : 1;
            Uns32 DFIFO_LVL : 4;
            Uns32 CFIFO_LVL : 4;
        } bits;
    } XADCIF_MSTS;
    union { 
        Uns32 value;
        struct {
            Uns32 DATA : 16;
            Uns32 ADDR : 10;
            Uns32 CMD : 4;
        } bits;
    } XADCIF_CMDFIFO;
    union { 
        Uns32 value;
        struct {
            Uns32 DATA : 16;
        } bits;
    } XADCIF_RDFIFO;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 4;
            Uns32 RESET : 1;
        } bits;
    } XADCIF_MCTL;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    ppmAddressSpaceHandle xadc;
    void                 *bport1;
    ppmNetHandle          intOut;
    ppmNetHandle          xadcmux;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(ReadCFG);
PPM_REG_READ_CB(ReadCTRL);
PPM_REG_READ_CB(ReadDMA_DEST_LEN);
PPM_REG_READ_CB(ReadDMA_DST_ADDR);
PPM_REG_READ_CB(ReadDMA_SRC_ADDR);
PPM_REG_READ_CB(ReadDMA_SRC_LEN);
PPM_REG_READ_CB(ReadINT_MASK);
PPM_REG_READ_CB(ReadINT_STS);
PPM_REG_READ_CB(ReadLOCK);
PPM_REG_READ_CB(ReadMCTRL);
PPM_REG_READ_CB(ReadMULTIBOOT_ADDR);
PPM_REG_READ_CB(ReadROM_SHADOW);
PPM_REG_READ_CB(ReadSTATUS);
PPM_REG_READ_CB(ReadUNLOCK);
PPM_REG_READ_CB(ReadXADCIF_CFG);
PPM_REG_READ_CB(ReadXADCIF_INT_MASK);
PPM_REG_READ_CB(ReadXADCIF_INT_STS);
PPM_REG_READ_CB(ReadXADCIF_MCTL);
PPM_REG_READ_CB(ReadXADCIF_MSTS);
PPM_REG_READ_CB(ReadXADCIF_RDFIFO);
PPM_REG_WRITE_CB(WriteCFG);
PPM_REG_WRITE_CB(WriteCTRL);
PPM_REG_WRITE_CB(WriteDMA_DEST_LEN);
PPM_REG_WRITE_CB(WriteDMA_DST_ADDR);
PPM_REG_WRITE_CB(WriteDMA_SRC_ADDR);
PPM_REG_WRITE_CB(WriteDMA_SRC_LEN);
PPM_REG_WRITE_CB(WriteINT_MASK);
PPM_REG_WRITE_CB(WriteINT_STS);
PPM_REG_WRITE_CB(WriteLOCK);
PPM_REG_WRITE_CB(WriteMCTRL);
PPM_REG_WRITE_CB(WriteMULTIBOOT_ADDR);
PPM_REG_WRITE_CB(WriteROM_SHADOW);
PPM_REG_WRITE_CB(WriteSTATUS);
PPM_REG_WRITE_CB(WriteUNLOCK);
PPM_REG_WRITE_CB(WriteXADCIF_CFG);
PPM_REG_WRITE_CB(WriteXADCIF_CMDFIFO);
PPM_REG_WRITE_CB(WriteXADCIF_INT_MASK);
PPM_REG_WRITE_CB(WriteXADCIF_INT_STS);
PPM_REG_WRITE_CB(WriteXADCIF_MCTL);
PPM_NET_CB(xadcMuxSelect);
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

#define BPORT1_AB_CTRL_WIDTH            32
#define BPORT1_AB_LOCK_WIDTH            32
#define BPORT1_AB_CFG_WIDTH             32
#define BPORT1_AB_INT_STS_WIDTH         32
#define BPORT1_AB_INT_MASK_WIDTH        32
#define BPORT1_AB_STATUS_WIDTH          32
#define BPORT1_AB_DMA_SRC_ADDR_WIDTH    32
#define BPORT1_AB_DMA_DST_ADDR_WIDTH    32
#define BPORT1_AB_DMA_SRC_LEN_WIDTH     32
#define BPORT1_AB_DMA_DEST_LEN_WIDTH    32
#define BPORT1_AB_ROM_SHADOW_WIDTH      32
#define BPORT1_AB_MULTIBOOT_ADDR_WIDTH  32
#define BPORT1_AB_UNLOCK_WIDTH          32
#define BPORT1_AB_MCTRL_WIDTH           32
#define BPORT1_AB_XADCIF_CFG_WRMASK     0x80ff331f
#define BPORT1_AB_XADCIF_CFG_WRNMASK    (0x7f00cce0)
#define BPORT1_AB_XADCIF_CFG_WIDTH      32
#define BPORT1_AB_XADCIF_INT_STS_WRMASK  0x3f
#define BPORT1_AB_XADCIF_INT_STS_WRNMASK  (0xffffffc0)
#define BPORT1_AB_XADCIF_INT_STS_WIDTH  32
#define BPORT1_AB_XADCIF_INT_MASK_WRMASK  0x3f
#define BPORT1_AB_XADCIF_INT_MASK_WRNMASK  (0xffffffc0)
#define BPORT1_AB_XADCIF_INT_MASK_WIDTH  32
#define BPORT1_AB_XADCIF_MSTS_WIDTH     32
#define BPORT1_AB_XADCIF_CMDFIFO_WIDTH  32
#define BPORT1_AB_XADCIF_RDFIFO_WIDTH   32
#define BPORT1_AB_XADCIF_MCTL_WRMASK    0x10
#define BPORT1_AB_XADCIF_MCTL_WRNMASK   (0xffffffef)
#define BPORT1_AB_XADCIF_MCTL_WIDTH     32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
