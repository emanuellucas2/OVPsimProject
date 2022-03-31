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
            Uns32 PS : 3;
            Uns32 CLKS : 2;
            Uns32 CPWMS : 1;
            Uns32 TOIE : 1;
            Uns32 TOF : 1;
        } bits;
    } SC;
    union { 
        Uns32 value;
        struct {
            Uns32 COUNT : 16;
        } bits;
    } CNT;
    union { 
        Uns32 value;
        struct {
            Uns32 MOD : 16;
        } bits;
    } MOD;
    union { 
        Uns32 value;
        struct {
            Uns32 DMA : 1;
            Uns32 __pad1 : 1;
            Uns32 ELSA : 1;
            Uns32 ELSB : 1;
            Uns32 MSA : 1;
            Uns32 MSB : 1;
            Uns32 CHIE : 1;
            Uns32 CHF : 1;
        } bits;
    } C0SC;
    union { 
        Uns32 value;
        struct {
            Uns32 VAL : 16;
        } bits;
    } C0V;
    union { 
        Uns32 value;
        struct {
            Uns32 DMA : 1;
            Uns32 __pad1 : 1;
            Uns32 ELSA : 1;
            Uns32 ELSB : 1;
            Uns32 MSA : 1;
            Uns32 MSB : 1;
            Uns32 CHIE : 1;
            Uns32 CHF : 1;
        } bits;
    } C1SC;
    union { 
        Uns32 value;
        struct {
            Uns32 VAL : 16;
        } bits;
    } C1V;
    union { 
        Uns32 value;
        struct {
            Uns32 DMA : 1;
            Uns32 __pad1 : 1;
            Uns32 ELSA : 1;
            Uns32 ELSB : 1;
            Uns32 MSA : 1;
            Uns32 MSB : 1;
            Uns32 CHIE : 1;
            Uns32 CHF : 1;
        } bits;
    } C2SC;
    union { 
        Uns32 value;
        struct {
            Uns32 VAL : 16;
        } bits;
    } C2V;
    union { 
        Uns32 value;
        struct {
            Uns32 DMA : 1;
            Uns32 __pad1 : 1;
            Uns32 ELSA : 1;
            Uns32 ELSB : 1;
            Uns32 MSA : 1;
            Uns32 MSB : 1;
            Uns32 CHIE : 1;
            Uns32 CHF : 1;
        } bits;
    } C3SC;
    union { 
        Uns32 value;
        struct {
            Uns32 VAL : 16;
        } bits;
    } C3V;
    union { 
        Uns32 value;
    } C4SC;
    union { 
        Uns32 value;
        struct {
            Uns32 VAL : 16;
        } bits;
    } C4V;
    union { 
        Uns32 value;
    } C5SC;
    union { 
        Uns32 value;
        struct {
            Uns32 VAL : 16;
        } bits;
    } C5V;
    union { 
        Uns32 value;
    } C6SC;
    union { 
        Uns32 value;
        struct {
            Uns32 VAL : 16;
        } bits;
    } C6V;
    union { 
        Uns32 value;
    } C7SC;
    union { 
        Uns32 value;
        struct {
            Uns32 VAL : 16;
        } bits;
    } C7V;
    union { 
        Uns32 value;
        struct {
            Uns32 INIT : 16;
        } bits;
    } CNTIN;
    union { 
        Uns32 value;
        struct {
            Uns32 CH0F : 1;
            Uns32 CH1F : 1;
            Uns32 CH2F : 1;
            Uns32 CH3F : 1;
            Uns32 CH4F : 1;
            Uns32 CH5F : 1;
            Uns32 CH6F : 1;
            Uns32 CH7F : 1;
        } bits;
    } STATUS;
    union { 
        Uns32 value;
        struct {
            Uns32 FTMEN : 1;
            Uns32 INIT : 1;
            Uns32 WPDIS : 1;
            Uns32 PWMSYNC : 1;
            Uns32 CAPTEST : 1;
            Uns32 FAULTM : 2;
            Uns32 FAULTIE : 1;
        } bits;
    } MODE;
    union { 
        Uns32 value;
        struct {
            Uns32 CNTMIN : 1;
            Uns32 CNTMAX : 1;
            Uns32 REINIT : 1;
            Uns32 SYNCHOM : 1;
            Uns32 TRIG0 : 1;
            Uns32 TRIG1 : 1;
            Uns32 TRIG2 : 1;
            Uns32 SWSYNC : 1;
        } bits;
    } SYNC;
    union { 
        Uns32 value;
        struct {
            Uns32 CH0OI : 1;
            Uns32 CH1OI : 1;
            Uns32 CH2OI : 1;
            Uns32 CH3OI : 1;
            Uns32 CH4OI : 1;
            Uns32 CH5OI : 1;
            Uns32 CH6OI : 1;
            Uns32 CH7OI : 1;
        } bits;
    } OUTINIT;
    union { 
        Uns32 value;
        struct {
            Uns32 CH0OM : 1;
            Uns32 CH1OM : 1;
            Uns32 CH2OM : 1;
            Uns32 CH3OM : 1;
            Uns32 CH4OM : 1;
            Uns32 CH5OM : 1;
            Uns32 CH6OM : 1;
            Uns32 CH7OM : 1;
        } bits;
    } OUTMASK;
    union { 
        Uns32 value;
        struct {
            Uns32 COMBINE0 : 1;
            Uns32 COMP0 : 1;
            Uns32 DECAPEN0 : 1;
            Uns32 DECAP0 : 1;
            Uns32 DTEN0 : 1;
            Uns32 SYNCEN0 : 1;
            Uns32 FAULTEN0 : 1;
            Uns32 __pad7 : 1;
            Uns32 COMBINE1 : 1;
            Uns32 COMP1 : 1;
            Uns32 DECAPEN1 : 1;
            Uns32 DECAP1 : 1;
            Uns32 DTEN1 : 1;
            Uns32 SYNCEN1 : 1;
            Uns32 FAULTEN1 : 1;
            Uns32 __pad15 : 1;
            Uns32 COMBINE2 : 1;
            Uns32 COMP2 : 1;
            Uns32 DECAPEN2 : 1;
            Uns32 DECAP2 : 1;
            Uns32 DTEN2 : 1;
            Uns32 SYNCEN2 : 1;
            Uns32 FAULTEN2 : 1;
            Uns32 __pad23 : 1;
            Uns32 COMBINE3 : 1;
            Uns32 COMP3 : 1;
            Uns32 DECAPEN3 : 1;
            Uns32 DECAP3 : 1;
            Uns32 DTEN3 : 1;
            Uns32 SYNCEN3 : 1;
            Uns32 FAULTEN3 : 1;
        } bits;
    } COMBINE;
    union { 
        Uns32 value;
        struct {
            Uns32 DTVAL : 6;
            Uns32 DTPS : 2;
        } bits;
    } DEADTIME;
    union { 
        Uns32 value;
        struct {
            Uns32 CH2TRIG : 1;
            Uns32 CH3TRIG : 1;
            Uns32 CH4TRIG : 1;
            Uns32 CH5TRIG : 1;
            Uns32 CH0TRIG : 1;
            Uns32 CH1TRIG : 1;
            Uns32 INITTRIGEN : 1;
            Uns32 TRIGF : 1;
        } bits;
    } EXTTRIG;
    union { 
        Uns32 value;
        struct {
            Uns32 POL0 : 1;
            Uns32 POL1 : 1;
            Uns32 POL2 : 1;
            Uns32 POL3 : 1;
            Uns32 POL4 : 1;
            Uns32 POL5 : 1;
            Uns32 POL6 : 1;
            Uns32 POL7 : 1;
        } bits;
    } POL;
    union { 
        Uns32 value;
        struct {
            Uns32 FAULTF0 : 1;
            Uns32 FAULTF1 : 1;
            Uns32 FAULTF2 : 1;
            Uns32 FAULTF3 : 1;
            Uns32 __pad4 : 1;
            Uns32 FAULTIN : 1;
            Uns32 WPEN : 1;
            Uns32 FAULTF : 1;
        } bits;
    } FMS;
    union { 
        Uns32 value;
        struct {
            Uns32 CH0FVAL : 4;
            Uns32 CH1FVAL : 4;
            Uns32 CH2FVAL : 4;
            Uns32 CH3FVAL : 4;
        } bits;
    } FILTER;
    union { 
        Uns32 value;
        struct {
            Uns32 FAULT0EN : 1;
            Uns32 FAULT1EN : 1;
            Uns32 FAULT2EN : 1;
            Uns32 FAULT3EN : 1;
            Uns32 FFLTR0EN : 1;
            Uns32 FFLTR1EN : 1;
            Uns32 FFLTR2EN : 1;
            Uns32 FFLTR3EN : 1;
            Uns32 FFVAL : 4;
        } bits;
    } FLTCTRL;
    union { 
        Uns32 value;
        struct {
            Uns32 QUADEN : 1;
            Uns32 TOFDIR : 1;
            Uns32 QUADIR : 1;
            Uns32 QUADMODE : 1;
            Uns32 PHBPOL : 1;
            Uns32 PHAPOL : 1;
            Uns32 PHBFLTREN : 1;
            Uns32 PHAFLTREN : 1;
        } bits;
    } QDCTRL;
    union { 
        Uns32 value;
        struct {
            Uns32 NUMTOF : 5;
            Uns32 __pad5 : 1;
            Uns32 BDMMODE : 2;
            Uns32 __pad8 : 1;
            Uns32 GTBEEN : 1;
            Uns32 GTBEOUT : 1;
        } bits;
    } CONF;
    union { 
        Uns32 value;
        struct {
            Uns32 FLT0POL : 1;
            Uns32 FLT1POL : 1;
            Uns32 FLT2POL : 1;
            Uns32 FLT3POL : 1;
        } bits;
    } FLTPOL;
    union { 
        Uns32 value;
        struct {
            Uns32 HWTRIGMODE : 1;
            Uns32 __pad1 : 1;
            Uns32 CNTINC : 1;
            Uns32 __pad3 : 1;
            Uns32 INVC : 1;
            Uns32 SWOC : 1;
            Uns32 __pad6 : 1;
            Uns32 SYNCMODE : 1;
            Uns32 SWRSTCNT : 1;
            Uns32 SWWRBUF : 1;
            Uns32 SWOM : 1;
            Uns32 SWINVC : 1;
            Uns32 SWSOC : 1;
            Uns32 __pad13 : 3;
            Uns32 HWRSTCNT : 1;
            Uns32 HWWRBUF : 1;
            Uns32 HWOM : 1;
            Uns32 HWINVC : 1;
            Uns32 HWSOC : 1;
        } bits;
    } SYNCONF;
    union { 
        Uns32 value;
        struct {
            Uns32 INV0EN : 1;
            Uns32 INV1EN : 1;
            Uns32 INV2EN : 1;
            Uns32 INV3EN : 1;
        } bits;
    } INVCTRL;
    union { 
        Uns32 value;
        struct {
            Uns32 CH0OC : 1;
            Uns32 CH1OC : 1;
            Uns32 CH2OC : 1;
            Uns32 CH3OC : 1;
            Uns32 CH4OC : 1;
            Uns32 CH5OC : 1;
            Uns32 CH6OC : 1;
            Uns32 CH7OC : 1;
            Uns32 CH0OCV : 1;
            Uns32 CH1OCV : 1;
            Uns32 CH2OCV : 1;
            Uns32 CH3OCV : 1;
            Uns32 CH4OCV : 1;
            Uns32 CH5OCV : 1;
            Uns32 CH6OCV : 1;
            Uns32 CH7OCV : 1;
        } bits;
    } SWOCTRL;
    union { 
        Uns32 value;
        struct {
            Uns32 CH0SEL : 1;
            Uns32 CH1SEL : 1;
            Uns32 CH2SEL : 1;
            Uns32 CH3SEL : 1;
            Uns32 CH4SEL : 1;
            Uns32 CH5SEL : 1;
            Uns32 CH6SEL : 1;
            Uns32 CH7SEL : 1;
            Uns32 __pad8 : 1;
            Uns32 LDOK : 1;
        } bits;
    } PWMLOAD;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          PhaseA;
    ppmNetHandle          PhaseB;
    ppmNetHandle          Interrupt;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(phaseACB);
PPM_NET_CB(phaseBCB);
PPM_REG_READ_CB(readSC);
PPM_REG_WRITE_CB(writeSC);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_SC_WRMASK             0x7f
#define BPORT1_AB_SC_WRNMASK            (0xffffff80)
#define BPORT1_AB_SC_WIDTH              32
#define BPORT1_AB_CNT_WRMASK            0xffff
#define BPORT1_AB_CNT_WRNMASK           (0xffff0000)
#define BPORT1_AB_CNT_WIDTH             32
#define BPORT1_AB_MOD_WRMASK            0xffffffff
#define BPORT1_AB_MOD_WRNMASK           (0x0)
#define BPORT1_AB_MOD_WIDTH             32
#define BPORT1_AB_C0SC_WRMASK           0x7d
#define BPORT1_AB_C0SC_WRNMASK          (0xffffff82)
#define BPORT1_AB_C0SC_WIDTH            32
#define BPORT1_AB_C0V_WRMASK            0xffff
#define BPORT1_AB_C0V_WRNMASK           (0xffff0000)
#define BPORT1_AB_C0V_WIDTH             32
#define BPORT1_AB_C1SC_WRMASK           0x7d
#define BPORT1_AB_C1SC_WRNMASK          (0xffffff82)
#define BPORT1_AB_C1SC_WIDTH            32
#define BPORT1_AB_C1V_WRMASK            0xffff
#define BPORT1_AB_C1V_WRNMASK           (0xffff0000)
#define BPORT1_AB_C1V_WIDTH             32
#define BPORT1_AB_C2SC_WRMASK           0x7d
#define BPORT1_AB_C2SC_WRNMASK          (0xffffff82)
#define BPORT1_AB_C2SC_WIDTH            32
#define BPORT1_AB_C2V_WRMASK            0xffff
#define BPORT1_AB_C2V_WRNMASK           (0xffff0000)
#define BPORT1_AB_C2V_WIDTH             32
#define BPORT1_AB_C3SC_WRMASK           0x7d
#define BPORT1_AB_C3SC_WRNMASK          (0xffffff82)
#define BPORT1_AB_C3SC_WIDTH            32
#define BPORT1_AB_C3V_WRMASK            0xffff
#define BPORT1_AB_C3V_WRNMASK           (0xffff0000)
#define BPORT1_AB_C3V_WIDTH             32
#define BPORT1_AB_C4SC_WRMASK           0x7d
#define BPORT1_AB_C4SC_WRNMASK          (0xffffff82)
#define BPORT1_AB_C4SC_WIDTH            32
#define BPORT1_AB_C4V_WRMASK            0xffff
#define BPORT1_AB_C4V_WRNMASK           (0xffff0000)
#define BPORT1_AB_C4V_WIDTH             32
#define BPORT1_AB_C5SC_WRMASK           0x7d
#define BPORT1_AB_C5SC_WRNMASK          (0xffffff82)
#define BPORT1_AB_C5SC_WIDTH            32
#define BPORT1_AB_C5V_WRMASK            0xffff
#define BPORT1_AB_C5V_WRNMASK           (0xffff0000)
#define BPORT1_AB_C5V_WIDTH             32
#define BPORT1_AB_C6SC_WRMASK           0x7d
#define BPORT1_AB_C6SC_WRNMASK          (0xffffff82)
#define BPORT1_AB_C6SC_WIDTH            32
#define BPORT1_AB_C6V_WRMASK            0xffff
#define BPORT1_AB_C6V_WRNMASK           (0xffff0000)
#define BPORT1_AB_C6V_WIDTH             32
#define BPORT1_AB_C7SC_WRMASK           0x7d
#define BPORT1_AB_C7SC_WRNMASK          (0xffffff82)
#define BPORT1_AB_C7SC_WIDTH            32
#define BPORT1_AB_C7V_WRMASK            0xffff
#define BPORT1_AB_C7V_WRNMASK           (0xffff0000)
#define BPORT1_AB_C7V_WIDTH             32
#define BPORT1_AB_CNTIN_WRMASK          0xffff
#define BPORT1_AB_CNTIN_WRNMASK         (0xffff0000)
#define BPORT1_AB_CNTIN_WIDTH           32
#define BPORT1_AB_STATUS_WIDTH          32
#define BPORT1_AB_MODE_WRMASK           0xff
#define BPORT1_AB_MODE_WRNMASK          (0xffffff00)
#define BPORT1_AB_MODE_WIDTH            32
#define BPORT1_AB_SYNC_WRMASK           0xff
#define BPORT1_AB_SYNC_WRNMASK          (0xffffff00)
#define BPORT1_AB_SYNC_WIDTH            32
#define BPORT1_AB_OUTINIT_WRMASK        0xff
#define BPORT1_AB_OUTINIT_WRNMASK       (0xffffff00)
#define BPORT1_AB_OUTINIT_WIDTH         32
#define BPORT1_AB_OUTMASK_WRMASK        0xff
#define BPORT1_AB_OUTMASK_WRNMASK       (0xffffff00)
#define BPORT1_AB_OUTMASK_WIDTH         32
#define BPORT1_AB_COMBINE_WRMASK        0x7f7f7f7f
#define BPORT1_AB_COMBINE_WRNMASK       (0x80808080)
#define BPORT1_AB_COMBINE_WIDTH         32
#define BPORT1_AB_DEADTIME_WRMASK       0xff
#define BPORT1_AB_DEADTIME_WRNMASK      (0xffffff00)
#define BPORT1_AB_DEADTIME_WIDTH        32
#define BPORT1_AB_EXTTRIG_WRMASK        0xff
#define BPORT1_AB_EXTTRIG_WRNMASK       (0xffffff00)
#define BPORT1_AB_EXTTRIG_WIDTH         32
#define BPORT1_AB_POL_WRMASK            0xff
#define BPORT1_AB_POL_WRNMASK           (0xffffff00)
#define BPORT1_AB_POL_WIDTH             32
#define BPORT1_AB_FMS_WRMASK            0x40
#define BPORT1_AB_FMS_WRNMASK           (0xffffffbf)
#define BPORT1_AB_FMS_WIDTH             32
#define BPORT1_AB_FILTER_WRMASK         0xffff
#define BPORT1_AB_FILTER_WRNMASK        (0xffff0000)
#define BPORT1_AB_FILTER_WIDTH          32
#define BPORT1_AB_FLTCTRL_WRMASK        0xfff
#define BPORT1_AB_FLTCTRL_WRNMASK       (0xfffff000)
#define BPORT1_AB_FLTCTRL_WIDTH         32
#define BPORT1_AB_QDCTRL_WRMASK         0xf9
#define BPORT1_AB_QDCTRL_WRNMASK        (0xffffff06)
#define BPORT1_AB_QDCTRL_WIDTH          32
#define BPORT1_AB_CONF_WRMASK           0x6df
#define BPORT1_AB_CONF_WRNMASK          (0xfffff920)
#define BPORT1_AB_CONF_WIDTH            32
#define BPORT1_AB_FLTPOL_WRMASK         0xf
#define BPORT1_AB_FLTPOL_WRNMASK        (0xfffffff0)
#define BPORT1_AB_FLTPOL_WIDTH          32
#define BPORT1_AB_SYNCONF_WRMASK        0x1f1fb5
#define BPORT1_AB_SYNCONF_WRNMASK       (0xffe0e04a)
#define BPORT1_AB_SYNCONF_WIDTH         32
#define BPORT1_AB_INVCTRL_WRMASK        0xf
#define BPORT1_AB_INVCTRL_WRNMASK       (0xfffffff0)
#define BPORT1_AB_INVCTRL_WIDTH         32
#define BPORT1_AB_SWOCTRL_WRMASK        0xffff
#define BPORT1_AB_SWOCTRL_WRNMASK       (0xffff0000)
#define BPORT1_AB_SWOCTRL_WIDTH         32
#define BPORT1_AB_PWMLOAD_WRMASK        0x2ff
#define BPORT1_AB_PWMLOAD_WRNMASK       (0xfffffd00)
#define BPORT1_AB_PWMLOAD_WIDTH         32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
