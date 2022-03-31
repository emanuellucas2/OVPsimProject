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
            Uns32 __pad0 : 16;
            Uns32 BA : 16;
        } bits;
    } CSAR0;
    union { 
        Uns32 value;
        struct {
            Uns32 V : 1;
            Uns32 __pad1 : 7;
            Uns32 WP : 1;
            Uns32 __pad9 : 7;
            Uns32 BAM : 16;
        } bits;
    } CSMR0;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 3;
            Uns32 BSTW : 1;
            Uns32 BSTR : 1;
            Uns32 BEM : 1;
            Uns32 PS : 2;
            Uns32 AA : 1;
            Uns32 BLS : 1;
            Uns32 WS : 6;
            Uns32 WRAH : 2;
            Uns32 RDAH : 2;
            Uns32 ASET : 2;
            Uns32 EXTS : 1;
            Uns32 SWSEN : 1;
            Uns32 __pad24 : 2;
            Uns32 SWS : 6;
        } bits;
    } CSCR0;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 16;
            Uns32 BA : 16;
        } bits;
    } CSAR1;
    union { 
        Uns32 value;
        struct {
            Uns32 V : 1;
            Uns32 __pad1 : 7;
            Uns32 WP : 1;
            Uns32 __pad9 : 7;
            Uns32 BAM : 16;
        } bits;
    } CSMR1;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 3;
            Uns32 BSTW : 1;
            Uns32 BSTR : 1;
            Uns32 BEM : 1;
            Uns32 PS : 2;
            Uns32 AA : 1;
            Uns32 BLS : 1;
            Uns32 WS : 6;
            Uns32 WRAH : 2;
            Uns32 RDAH : 2;
            Uns32 ASET : 2;
            Uns32 EXTS : 1;
            Uns32 SWSEN : 1;
            Uns32 __pad24 : 2;
            Uns32 SWS : 6;
        } bits;
    } CSCR1;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 16;
            Uns32 BA : 16;
        } bits;
    } CSAR2;
    union { 
        Uns32 value;
        struct {
            Uns32 V : 1;
            Uns32 __pad1 : 7;
            Uns32 WP : 1;
            Uns32 __pad9 : 7;
            Uns32 BAM : 16;
        } bits;
    } CSMR2;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 3;
            Uns32 BSTW : 1;
            Uns32 BSTR : 1;
            Uns32 BEM : 1;
            Uns32 PS : 2;
            Uns32 AA : 1;
            Uns32 BLS : 1;
            Uns32 WS : 6;
            Uns32 WRAH : 2;
            Uns32 RDAH : 2;
            Uns32 ASET : 2;
            Uns32 EXTS : 1;
            Uns32 SWSEN : 1;
            Uns32 __pad24 : 2;
            Uns32 SWS : 6;
        } bits;
    } CSCR2;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 16;
            Uns32 BA : 16;
        } bits;
    } CSAR3;
    union { 
        Uns32 value;
        struct {
            Uns32 V : 1;
            Uns32 __pad1 : 7;
            Uns32 WP : 1;
            Uns32 __pad9 : 7;
            Uns32 BAM : 16;
        } bits;
    } CSMR3;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 3;
            Uns32 BSTW : 1;
            Uns32 BSTR : 1;
            Uns32 BEM : 1;
            Uns32 PS : 2;
            Uns32 AA : 1;
            Uns32 BLS : 1;
            Uns32 WS : 6;
            Uns32 WRAH : 2;
            Uns32 RDAH : 2;
            Uns32 ASET : 2;
            Uns32 EXTS : 1;
            Uns32 SWSEN : 1;
            Uns32 __pad24 : 2;
            Uns32 SWS : 6;
        } bits;
    } CSCR3;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 16;
            Uns32 BA : 16;
        } bits;
    } CSAR4;
    union { 
        Uns32 value;
        struct {
            Uns32 V : 1;
            Uns32 __pad1 : 7;
            Uns32 WP : 1;
            Uns32 __pad9 : 7;
            Uns32 BAM : 16;
        } bits;
    } CSMR4;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 3;
            Uns32 BSTW : 1;
            Uns32 BSTR : 1;
            Uns32 BEM : 1;
            Uns32 PS : 2;
            Uns32 AA : 1;
            Uns32 BLS : 1;
            Uns32 WS : 6;
            Uns32 WRAH : 2;
            Uns32 RDAH : 2;
            Uns32 ASET : 2;
            Uns32 EXTS : 1;
            Uns32 SWSEN : 1;
            Uns32 __pad24 : 2;
            Uns32 SWS : 6;
        } bits;
    } CSCR4;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 16;
            Uns32 BA : 16;
        } bits;
    } CSAR5;
    union { 
        Uns32 value;
        struct {
            Uns32 V : 1;
            Uns32 __pad1 : 7;
            Uns32 WP : 1;
            Uns32 __pad9 : 7;
            Uns32 BAM : 16;
        } bits;
    } CSMR5;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 3;
            Uns32 BSTW : 1;
            Uns32 BSTR : 1;
            Uns32 BEM : 1;
            Uns32 PS : 2;
            Uns32 AA : 1;
            Uns32 BLS : 1;
            Uns32 WS : 6;
            Uns32 WRAH : 2;
            Uns32 RDAH : 2;
            Uns32 ASET : 2;
            Uns32 EXTS : 1;
            Uns32 SWSEN : 1;
            Uns32 __pad24 : 2;
            Uns32 SWS : 6;
        } bits;
    } CSCR5;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 12;
            Uns32 GROUP5 : 4;
            Uns32 GROUP4 : 4;
            Uns32 GROUP3 : 4;
            Uns32 GROUP2 : 4;
            Uns32 GROUP1 : 4;
        } bits;
    } CSPMCR;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          Reset;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_CSAR0_WRMASK          0xffff0000
#define BPORT1_AB_CSAR0_WRNMASK         (0xffff)
#define BPORT1_AB_CSAR0_WIDTH           32
#define BPORT1_AB_CSMR0_WRMASK          0xffff0100
#define BPORT1_AB_CSMR0_WRNMASK         (0xfeff)
#define BPORT1_AB_CSMR0_WIDTH           32
#define BPORT1_AB_CSCR0_WRMASK          0xfcfffff8
#define BPORT1_AB_CSCR0_WRNMASK         (0x3000007)
#define BPORT1_AB_CSCR0_WIDTH           32
#define BPORT1_AB_CSAR1_WRMASK          0xffff0000
#define BPORT1_AB_CSAR1_WRNMASK         (0xffff)
#define BPORT1_AB_CSAR1_WIDTH           32
#define BPORT1_AB_CSMR1_WRMASK          0xffff0100
#define BPORT1_AB_CSMR1_WRNMASK         (0xfeff)
#define BPORT1_AB_CSMR1_WIDTH           32
#define BPORT1_AB_CSCR1_WRMASK          0xfcfffff8
#define BPORT1_AB_CSCR1_WRNMASK         (0x3000007)
#define BPORT1_AB_CSCR1_WIDTH           32
#define BPORT1_AB_CSAR2_WRMASK          0xffff0000
#define BPORT1_AB_CSAR2_WRNMASK         (0xffff)
#define BPORT1_AB_CSAR2_WIDTH           32
#define BPORT1_AB_CSMR2_WRMASK          0xffff0100
#define BPORT1_AB_CSMR2_WRNMASK         (0xfeff)
#define BPORT1_AB_CSMR2_WIDTH           32
#define BPORT1_AB_CSCR2_WRMASK          0xfcfffff8
#define BPORT1_AB_CSCR2_WRNMASK         (0x3000007)
#define BPORT1_AB_CSCR2_WIDTH           32
#define BPORT1_AB_CSAR3_WRMASK          0xffff0000
#define BPORT1_AB_CSAR3_WRNMASK         (0xffff)
#define BPORT1_AB_CSAR3_WIDTH           32
#define BPORT1_AB_CSMR3_WRMASK          0xffff0100
#define BPORT1_AB_CSMR3_WRNMASK         (0xfeff)
#define BPORT1_AB_CSMR3_WIDTH           32
#define BPORT1_AB_CSCR3_WRMASK          0xfcfffff8
#define BPORT1_AB_CSCR3_WRNMASK         (0x3000007)
#define BPORT1_AB_CSCR3_WIDTH           32
#define BPORT1_AB_CSAR4_WRMASK          0xffff0000
#define BPORT1_AB_CSAR4_WRNMASK         (0xffff)
#define BPORT1_AB_CSAR4_WIDTH           32
#define BPORT1_AB_CSMR4_WRMASK          0xffff0100
#define BPORT1_AB_CSMR4_WRNMASK         (0xfeff)
#define BPORT1_AB_CSMR4_WIDTH           32
#define BPORT1_AB_CSCR4_WRMASK          0xfcfffff8
#define BPORT1_AB_CSCR4_WRNMASK         (0x3000007)
#define BPORT1_AB_CSCR4_WIDTH           32
#define BPORT1_AB_CSAR5_WRMASK          0xffff0000
#define BPORT1_AB_CSAR5_WRNMASK         (0xffff)
#define BPORT1_AB_CSAR5_WIDTH           32
#define BPORT1_AB_CSMR5_WRMASK          0xffff0100
#define BPORT1_AB_CSMR5_WRNMASK         (0xfeff)
#define BPORT1_AB_CSMR5_WIDTH           32
#define BPORT1_AB_CSCR5_WRMASK          0xfcfffff8
#define BPORT1_AB_CSCR5_WRNMASK         (0x3000007)
#define BPORT1_AB_CSCR5_WIDTH           32
#define BPORT1_AB_CSPMCR_WRMASK         0xfffff000
#define BPORT1_AB_CSPMCR_WRNMASK        (0xfff)
#define BPORT1_AB_CSPMCR_WIDTH          32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
