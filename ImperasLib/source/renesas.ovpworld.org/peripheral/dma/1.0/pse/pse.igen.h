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

typedef struct DMAP0_abc_dataS { 
    union { 
        Uns16 value;
    } DMAWC0;
    union { 
        Uns16 value;
    } DMAWC1;
} DMAP0_abc_dataT, *DMAP0_abc_dataTP;

typedef struct DMAP1_abw_dataS { 
    union { 
        Uns16 value;
    } MAR[10];
} DMAP1_abw_dataT, *DMAP1_abw_dataTP;

typedef struct DMAP1_abb_dataS { 
    union { 
        Uns8 value;
        struct {
            Uns8 SAR : 4;
        } bits;
    } SAR[2];
    union { 
        Uns8 value;
        struct {
            Uns8 IFCn : 3;
        } bits;
    } DTFR[4];
    union { 
        Uns8 value;
    } DTCR[10];
    union { 
        Uns8 value;
        struct {
            Uns8 DMAS0 : 1;
            Uns8 DMAS1 : 1;
            Uns8 DMAS2 : 1;
            Uns8 DMAS3 : 1;
            Uns8 DMAS4 : 1;
            Uns8 DMAS5 : 1;
            Uns8 DMAS6 : 1;
            Uns8 DMAS7 : 1;
        } bits;
    } DMASL;
    union { 
        Uns8 value;
        struct {
            Uns8 DE0 : 1;
            Uns8 DE1 : 1;
            Uns8 DE2 : 1;
            Uns8 DE3 : 1;
            Uns8 DE4 : 1;
            Uns8 DE5 : 1;
            Uns8 DE6 : 1;
            Uns8 DE7 : 1;
        } bits;
    } DMAMCL;
    union { 
        Uns8 value;
        struct {
            Uns8 __pad0 : 4;
            Uns8 DMADCS4 : 1;
            Uns8 DMADCS5 : 1;
            Uns8 DMADCS6 : 1;
            Uns8 DMADCS7 : 1;
        } bits;
    } DMADSCL;
} DMAP1_abb_dataT, *DMAP1_abb_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern DMAP0_abc_dataT DMAP0_abc_data;

extern DMAP1_abw_dataT DMAP1_abw_data;

extern DMAP1_abb_dataT DMAP1_abb_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    ppmAddressSpaceHandle DMAPM;
    void                 *DMAP0;
    void                 *DMAP1;
    ppmNetHandle          INTDMA[10];
    ppmNetHandle          DMA0EN;
    ppmNetHandle          DMA1EN;
    ppmNetHandle          ADDMARQ0;
    ppmNetHandle          ADDMARQ1;
    ppmNetHandle          INTTS0CD;
    ppmNetHandle          INTTS1CD;
    ppmNetHandle          INTCE0C;
    ppmNetHandle          INTCE1C;
    ppmNetHandle          INTBE0R;
    ppmNetHandle          INTBE1R;
    ppmNetHandle          INTUC0R;
    ppmNetHandle          INTUC1R;
    ppmNetHandle          INTUC2R;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(readDMADSCL);
PPM_REG_READ_CB(readDMAMCL);
PPM_REG_READ_CB(readDMASL);
PPM_REG_READ_CB(readDMAWC0);
PPM_REG_READ_CB(readDMAWC1);
PPM_NBYTE_READ_CB(readDTCR);
PPM_NBYTE_READ_CB(readDTFR);
PPM_NBYTE_READ_CB(readMAR);
PPM_NBYTE_READ_CB(readSAR);
PPM_NET_CB(triggerADDMARQ0);
PPM_NET_CB(triggerADDMARQ1);
PPM_NET_CB(triggerINTBE0R);
PPM_NET_CB(triggerINTBE1R);
PPM_NET_CB(triggerINTCE0C);
PPM_NET_CB(triggerINTCE1C);
PPM_NET_CB(triggerINTTS0CD);
PPM_NET_CB(triggerINTTS1CD);
PPM_NET_CB(triggerINTUC0R);
PPM_NET_CB(triggerINTUC1R);
PPM_NET_CB(triggerINTUC2R);
PPM_REG_WRITE_CB(writeDMADSCL);
PPM_REG_WRITE_CB(writeDMAMCL);
PPM_REG_WRITE_CB(writeDMASL);
PPM_REG_WRITE_CB(writeDMAWC0);
PPM_REG_WRITE_CB(writeDMAWC1);
PPM_NBYTE_WRITE_CB(writeDTCR);
PPM_NBYTE_WRITE_CB(writeDTFR);
PPM_NBYTE_WRITE_CB(writeMAR);
PPM_NBYTE_WRITE_CB(writeSAR);
PPM_NET_CB(reset_reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define DMAP0_ABC_DMAWC0_WIDTH          16
#define DMAP0_ABC_DMAWC1_WIDTH          16
#define DMAP1_ABW_MAR_WIDTH             16
#define DMAP1_ABB_SAR_WRMASK            0xf
#define DMAP1_ABB_SAR_WRNMASK           (0xf0)
#define DMAP1_ABB_SAR_WIDTH             8
#define DMAP1_ABB_DTFR_WIDTH            8
#define DMAP1_ABB_DTCR_WIDTH            8
#define DMAP1_ABB_DMASL_WIDTH           8
#define DMAP1_ABB_DMAMCL_WIDTH          8
#define DMAP1_ABB_DMADSCL_WRMASK        0xf0
#define DMAP1_ABB_DMADSCL_WRNMASK       (0xf)
#define DMAP1_ABB_DMADSCL_WIDTH         8

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
