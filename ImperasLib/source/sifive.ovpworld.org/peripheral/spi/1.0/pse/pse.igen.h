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

typedef struct mport1_MEM_dataS { 
} mport1_MEM_dataT, *mport1_MEM_dataTP;

typedef struct bport1_REG_dataS { 
    union { 
        Uns32 value;
        struct {
            Uns32 scale : 12;
        } bits;
    } sckdiv;
    union { 
        Uns32 value;
        struct {
            Uns32 pha : 1;
            Uns32 pol : 1;
        } bits;
    } sckmode;
    union { 
        Uns32 value;
    } csid;
    union { 
        Uns32 value;
    } csdef;
    union { 
        Uns32 value;
        struct {
            Uns32 mode : 2;
        } bits;
    } csmode;
    union { 
        Uns32 value;
        struct {
            Uns32 cssck : 8;
            Uns32 __pad8 : 8;
            Uns32 sckcs : 8;
        } bits;
    } delay0;
    union { 
        Uns32 value;
        struct {
            Uns32 intercs : 8;
            Uns32 __pad8 : 8;
            Uns32 interxfr : 8;
        } bits;
    } delay1;
    union { 
        Uns32 value;
        struct {
            Uns32 proto : 2;
            Uns32 endian : 1;
            Uns32 dir : 1;
            Uns32 __pad4 : 12;
            Uns32 len : 4;
        } bits;
    } fmt;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 8;
            Uns32 __pad8 : 23;
            Uns32 full : 1;
        } bits;
    } txdata;
    union { 
        Uns32 value;
        struct {
            Uns32 data : 8;
            Uns32 __pad8 : 23;
            Uns32 empty : 1;
        } bits;
    } rxdata;
    union { 
        Uns32 value;
        struct {
            Uns32 txmark : 3;
        } bits;
    } txmark;
    union { 
        Uns32 value;
        struct {
            Uns32 rxmark : 3;
        } bits;
    } rxmark;
    union { 
        Uns32 value;
        struct {
            Uns32 en : 1;
        } bits;
    } fctrl;
    union { 
        Uns32 value;
        struct {
            Uns32 cmd_en : 1;
            Uns32 addr_len : 3;
            Uns32 pad_cnt : 4;
            Uns32 cmd_proto : 2;
            Uns32 addr_proto : 2;
            Uns32 data_proto : 2;
            Uns32 __pad14 : 2;
            Uns32 cmd_code : 8;
            Uns32 pad_code : 8;
        } bits;
    } ffmt;
    union { 
        Uns32 value;
        struct {
            Uns32 txwm : 1;
            Uns32 rxwm : 1;
        } bits;
    } ie;
    union { 
        Uns32 value;
        struct {
            Uns32 txwm : 1;
            Uns32 rxwm : 1;
        } bits;
    } ip;
} bport1_REG_dataT, *bport1_REG_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern mport1_MEM_dataT mport1_MEM_data;

extern bport1_REG_dataT bport1_REG_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *mport1;
    void                 *bport1;
    ppmNetHandle          resetNet;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NBYTE_READ_CB(defaultMemRead);

PPM_NBYTE_WRITE_CB(defaultMemWrite);

PPM_REG_READ_CB(rdRx);
PPM_REG_READ_CB(rdTx);
PPM_NET_CB(resetCB);
PPM_REG_WRITE_CB(wrCsmode);
PPM_REG_WRITE_CB(wrRxMark);
PPM_REG_WRITE_CB(wrSckdiv);
PPM_REG_WRITE_CB(wrSckmode);
PPM_REG_WRITE_CB(wrTx);
PPM_REG_WRITE_CB(wrTxMark);
PPM_NET_CB(reset_resetNet);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


///////////////////////////////// Local memory /////////////////////////////////

// To access local memory mport1/MEM/mem : (for example)
// char value = ((char*)handles.mport1)[MPORT1_MEM_MEM_OFFSET + myAddress];

#define MPORT1_MEM_MEM_OFFSET           0x0
#define MPORT1_MEM_MEM_SIZE             0x20000000

////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_REG_SCKDIV_WRMASK        0xfff
#define BPORT1_REG_SCKDIV_WRNMASK       (0xfffff000)
#define BPORT1_REG_SCKDIV_WIDTH         32
#define BPORT1_REG_SCKMODE_WRMASK       0x3
#define BPORT1_REG_SCKMODE_WRNMASK      (0xfffffffc)
#define BPORT1_REG_SCKMODE_WIDTH        32
#define BPORT1_REG_CSID_WIDTH           32
#define BPORT1_REG_CSDEF_WIDTH          32
#define BPORT1_REG_CSMODE_WRMASK        0x3
#define BPORT1_REG_CSMODE_WRNMASK       (0xfffffffc)
#define BPORT1_REG_CSMODE_WIDTH         32
#define BPORT1_REG_DELAY0_WIDTH         32
#define BPORT1_REG_DELAY1_WIDTH         32
#define BPORT1_REG_FMT_WIDTH            32
#define BPORT1_REG_TXDATA_WRMASK        0xff
#define BPORT1_REG_TXDATA_WRNMASK       (0xffffff00)
#define BPORT1_REG_TXDATA_WIDTH         32
#define BPORT1_REG_RXDATA_WIDTH         32
#define BPORT1_REG_TXMARK_WRMASK        0x3
#define BPORT1_REG_TXMARK_WRNMASK       (0xfffffffc)
#define BPORT1_REG_TXMARK_WIDTH         32
#define BPORT1_REG_RXMARK_WRMASK        0x3
#define BPORT1_REG_RXMARK_WRNMASK       (0xfffffffc)
#define BPORT1_REG_RXMARK_WIDTH         32
#define BPORT1_REG_FCTRL_WIDTH          32
#define BPORT1_REG_FFMT_WIDTH           32
#define BPORT1_REG_IE_WIDTH             32
#define BPORT1_REG_IP_WIDTH             32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
