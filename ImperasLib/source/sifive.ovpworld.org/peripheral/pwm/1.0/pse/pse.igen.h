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

typedef struct bport1_REG_dataS { 
    union { 
        Uns32 value;
        struct {
            Uns32 pwmscale : 4;
            Uns32 __pad4 : 4;
            Uns32 pwmsticky : 1;
            Uns32 pwmzerocmp : 1;
            Uns32 pwmdeglitch : 1;
            Uns32 __pad11 : 1;
            Uns32 pwmenalways : 1;
            Uns32 pwmenoneshot : 1;
            Uns32 __pad14 : 2;
            Uns32 pwmcmp0center : 1;
            Uns32 pwmcmp1center : 1;
            Uns32 pwmcmp2center : 1;
            Uns32 pwmcmp3center : 1;
            Uns32 __pad20 : 4;
            Uns32 pwmcmp0gang : 1;
            Uns32 pwmcmp1gang : 1;
            Uns32 pwmcmp2gang : 1;
            Uns32 pwmcmp3gang : 1;
            Uns32 pwmcmp0ip : 1;
            Uns32 pwmcmp1ip : 1;
            Uns32 pwmcmp2ip : 1;
            Uns32 pwmcmp3ip : 1;
        } bits;
    } pwmcfg;
    union { 
        Uns32 value;
    } pwmcount;
    union { 
        Uns32 value;
    } pwms;
    union { 
        Uns32 value;
        struct {
            Uns32 cmp : 16;
        } bits;
    } pwmcmp0;
    union { 
        Uns32 value;
        struct {
            Uns32 cmp : 16;
        } bits;
    } pwmcmp1;
    union { 
        Uns32 value;
        struct {
            Uns32 cmp : 16;
        } bits;
    } pwmcmp2;
    union { 
        Uns32 value;
        struct {
            Uns32 cmp : 16;
        } bits;
    } pwmcmp3;
} bport1_REG_dataT, *bport1_REG_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_REG_dataT bport1_REG_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          resetNet;
    ppmNetHandle          int0;
    ppmNetHandle          int1;
    ppmNetHandle          int2;
    ppmNetHandle          int3;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NBYTE_READ_CB(defaultMemRead);

PPM_NBYTE_WRITE_CB(defaultMemWrite);

PPM_REG_READ_CB(rdCnt);
PPM_REG_READ_CB(rdPwms);
PPM_NET_CB(resetCB);
PPM_REG_WRITE_CB(wrCfg);
PPM_REG_WRITE_CB(wrCmp);
PPM_REG_WRITE_CB(wrCnt);
PPM_REG_WRITE_CB(wrPwms);
PPM_NET_CB(reset_resetNet);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_REG_PWMCFG_WRMASK        0xff0ff70f
#define BPORT1_REG_PWMCFG_WRNMASK       (0xf008f0)
#define BPORT1_REG_PWMCFG_WIDTH         32
#define BPORT1_REG_PWMCOUNT_WIDTH       32
#define BPORT1_REG_PWMS_WIDTH           32
#define BPORT1_REG_PWMCMP0_WRMASK       0xffff
#define BPORT1_REG_PWMCMP0_WRNMASK      (0xffff0000)
#define BPORT1_REG_PWMCMP0_WIDTH        32
#define BPORT1_REG_PWMCMP1_WRMASK       0xffff
#define BPORT1_REG_PWMCMP1_WRNMASK      (0xffff0000)
#define BPORT1_REG_PWMCMP1_WIDTH        32
#define BPORT1_REG_PWMCMP2_WRMASK       0xffff
#define BPORT1_REG_PWMCMP2_WRNMASK      (0xffff0000)
#define BPORT1_REG_PWMCMP2_WIDTH        32
#define BPORT1_REG_PWMCMP3_WRMASK       0xffff
#define BPORT1_REG_PWMCMP3_WRNMASK      (0xffff0000)
#define BPORT1_REG_PWMCMP3_WIDTH        32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
