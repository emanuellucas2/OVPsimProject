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

typedef struct TMSP0_reg0_dataS { 
    union { 
        Uns8 value;
        struct {
            Uns8 CKS : 3;
            Uns8 __pad3 : 4;
            Uns8 CE : 1;
        } bits;
    } CTL0;
    union { 
        Uns8 value;
        struct {
            Uns8 MD : 4;
            Uns8 __pad4 : 1;
            Uns8 EEE : 1;
            Uns8 EST : 1;
        } bits;
    } CTL1;
} TMSP0_reg0_dataT, *TMSP0_reg0_dataTP;

typedef struct TMSP0_reg1_dataS { 
    union { 
        Uns16 value;
        struct {
            Uns16 OE0 : 1;
            Uns16 OL0 : 1;
            Uns16 OE1 : 1;
            Uns16 OL1 : 1;
            Uns16 OE2 : 1;
            Uns16 OL2 : 1;
            Uns16 OE3 : 1;
            Uns16 OL3 : 1;
            Uns16 OE4 : 1;
            Uns16 OL4 : 1;
            Uns16 OE5 : 1;
            Uns16 OL5 : 1;
            Uns16 OE6 : 1;
            Uns16 OL6 : 1;
            Uns16 OE7 : 1;
            Uns16 OL7 : 1;
        } bits;
    } IOC0;
} TMSP0_reg1_dataT, *TMSP0_reg1_dataTP;

typedef struct TMSP0_reg2_dataS { 
    union { 
        Uns8 value;
        struct {
            Uns8 ETS : 2;
            Uns8 EES : 2;
        } bits;
    } IOC2;
    union { 
        Uns8 value;
        struct {
            Uns8 EOC : 1;
            Uns8 __pad1 : 1;
            Uns8 WOC : 1;
            Uns8 __pad3 : 1;
            Uns8 BA : 3;
        } bits;
    } IOC4;
    union { 
        Uns8 value;
        struct {
            Uns8 OVF : 1;
            Uns8 CUF : 1;
            Uns8 CMS : 1;
            Uns8 DSE : 1;
        } bits;
    } OPT0;
    union { 
        Uns8 value;
        struct {
            Uns8 IPC : 3;
            Uns8 PSC : 1;
            Uns8 __pad4 : 3;
            Uns8 SOC : 1;
        } bits;
    } OPT4;
    union { 
        Uns8 value;
        struct {
            Uns8 OPF : 3;
            Uns8 TSF : 1;
            Uns8 PTS : 1;
            Uns8 PSS : 1;
            Uns8 POT : 1;
            Uns8 ADC : 1;
        } bits;
    } OPT5;
    union { 
        Uns8 value;
        struct {
            Uns8 TOS : 1;
            Uns8 PTC : 2;
            Uns8 TDC : 1;
            Uns8 PPC : 1;
            Uns8 IDC : 1;
        } bits;
    } OPT7;
} TMSP0_reg2_dataT, *TMSP0_reg2_dataTP;

typedef struct TMSP0_reg3_dataS { 
    union { 
        Uns16 value;
        struct {
            Uns16 ID : 5;
            Uns16 RDE : 1;
            Uns16 IOE : 1;
            Uns16 ICE : 1;
            Uns16 RBE : 1;
            Uns16 RTE : 1;
        } bits;
    } OPT1;
    union { 
        Uns16 value;
        struct {
            Uns16 AT00 : 1;
            Uns16 AT01 : 1;
            Uns16 AT02 : 1;
            Uns16 AT03 : 1;
            Uns16 AT04 : 1;
            Uns16 AT05 : 1;
            Uns16 AT06 : 1;
            Uns16 AT07 : 1;
            Uns16 ACC0 : 1;
            Uns16 ACC1 : 1;
        } bits;
    } OPT2;
    union { 
        Uns16 value;
        struct {
            Uns16 AT00 : 1;
            Uns16 AT01 : 1;
            Uns16 AT02 : 1;
            Uns16 AT03 : 1;
            Uns16 AT04 : 1;
            Uns16 AT05 : 1;
            Uns16 AT06 : 1;
            Uns16 AT07 : 1;
            Uns16 ACC2 : 1;
            Uns16 ACC3 : 1;
        } bits;
    } OPT3;
    union { 
        Uns16 value;
        struct {
            Uns16 RSF : 1;
            Uns16 SUF : 1;
            Uns16 TBF : 1;
            Uns16 PEF : 1;
            Uns16 PRF : 1;
            Uns16 NDF : 1;
            Uns16 TDF : 1;
            Uns16 PTF : 1;
            Uns16 PPF : 1;
        } bits;
    } OPT6;
    union { 
        Uns16 value;
        struct {
            Uns16 __pad0 : 1;
            Uns16 DTV : 9;
        } bits;
    } DTC0;
    union { 
        Uns16 value;
        struct {
            Uns16 __pad0 : 1;
            Uns16 DTV : 9;
        } bits;
    } DTC1;
    union { 
        Uns16 value;
        struct {
            Uns16 SP0 : 4;
            Uns16 SP1 : 4;
            Uns16 SP2 : 4;
            Uns16 SP3 : 4;
        } bits;
    } PAT0;
    union { 
        Uns16 value;
        struct {
            Uns16 SP4 : 4;
            Uns16 SP5 : 4;
            Uns16 SP6 : 4;
            Uns16 SP7 : 4;
        } bits;
    } PAT1;
    union { 
        Uns16 value;
    } CCR0;
    union { 
        Uns16 value;
    } CCR1;
    union { 
        Uns16 value;
    } CCR2;
    union { 
        Uns16 value;
    } CCR3;
    union { 
        Uns16 value;
    } CCR4;
    union { 
        Uns16 value;
    } CCR5;
    union { 
        Uns16 value;
        struct {
            Uns16 MODE : 1;
            Uns16 VAL : 15;
        } bits;
    } CNT;
    union { 
        Uns16 value;
        struct {
            Uns16 MODE : 1;
            Uns16 SVAL : 15;
        } bits;
    } SBC;
} TMSP0_reg3_dataT, *TMSP0_reg3_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern TMSP0_reg0_dataT TMSP0_reg0_data;

extern TMSP0_reg1_dataT TMSP0_reg1_data;

extern TMSP0_reg2_dataT TMSP0_reg2_data;

extern TMSP0_reg3_dataT TMSP0_reg3_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *TMSP0;
    ppmNetHandle          TOS0;
    ppmNetHandle          TOS1;
    ppmNetHandle          TOS2;
    ppmNetHandle          TOS3;
    ppmNetHandle          TOS4;
    ppmNetHandle          TOS5;
    ppmNetHandle          TOS6;
    ppmNetHandle          TOS7;
    ppmNetHandle          TSADTRG0;
    ppmNetHandle          TSADTRG1;
    ppmNetHandle          TSAEDO;
    ppmNetHandle          TSESG;
    ppmNetHandle          TSTSF;
    ppmNetHandle          INTTSCC0;
    ppmNetHandle          INTTSCC1;
    ppmNetHandle          INTTSCC2;
    ppmNetHandle          INTTSCC3;
    ppmNetHandle          INTTSCC4;
    ppmNetHandle          INTTSCC5;
    ppmNetHandle          INTTSCD0;
    ppmNetHandle          INTTSOD;
    ppmNetHandle          INTTSOV;
    ppmNetHandle          INTTSER;
    ppmNetHandle          INTTSWN;
    ppmNetHandle          TTRGS;
    ppmNetHandle          TEVTS;
    ppmNetHandle          TAPTS0;
    ppmNetHandle          TAPTS1;
    ppmNetHandle          TAPTS2;
    ppmNetHandle          ESO;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_NET_CB(P_ESO);
PPM_NET_CB(P_TAPTS0);
PPM_NET_CB(P_TAPTS1);
PPM_NET_CB(P_TAPTS2);
PPM_NET_CB(P_TEVTS);
PPM_NET_CB(P_TTRGS);
PPM_REG_READ_CB(readCNT);
PPM_REG_READ_CB(readIOC0);
PPM_REG_READ_CB(readOPT1);
PPM_REG_READ_CB(readOPT2);
PPM_REG_READ_CB(readOPT3);
PPM_REG_READ_CB(readOPT6);
PPM_REG_READ_CB(readSBC);
PPM_REG_WRITE_CB(writeCCR0);
PPM_REG_WRITE_CB(writeCCR1);
PPM_REG_WRITE_CB(writeCCR2);
PPM_REG_WRITE_CB(writeCCR3);
PPM_REG_WRITE_CB(writeCCR4);
PPM_REG_WRITE_CB(writeCCR5);
PPM_REG_WRITE_CB(writeCTL0);
PPM_REG_WRITE_CB(writeCTL1);
PPM_REG_WRITE_CB(writeDTC0);
PPM_REG_WRITE_CB(writeDTC1);
PPM_REG_WRITE_CB(writeIOC0);
PPM_REG_WRITE_CB(writeIOC2);
PPM_REG_WRITE_CB(writeIOC4);
PPM_REG_WRITE_CB(writeOPT0);
PPM_REG_WRITE_CB(writeOPT1);
PPM_REG_WRITE_CB(writeOPT2);
PPM_REG_WRITE_CB(writeOPT3);
PPM_REG_WRITE_CB(writeOPT4);
PPM_REG_WRITE_CB(writeOPT5);
PPM_REG_WRITE_CB(writeOPT6);
PPM_REG_WRITE_CB(writeOPT7);
PPM_REG_WRITE_CB(writePAT0);
PPM_REG_WRITE_CB(writePAT1);
PPM_NET_CB(reset_IRESET);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define TMSP0_REG0_CTL0_WRMASK          0x87
#define TMSP0_REG0_CTL0_WRNMASK         (0x78)
#define TMSP0_REG0_CTL0_WIDTH           8
#define TMSP0_REG0_CTL1_WRMASK          0x6f
#define TMSP0_REG0_CTL1_WRNMASK         (0x90)
#define TMSP0_REG0_CTL1_WIDTH           8
#define TMSP0_REG1_IOC0_WRMASK          0xffff
#define TMSP0_REG1_IOC0_WRNMASK         (0x0)
#define TMSP0_REG1_IOC0_WIDTH           16
#define TMSP0_REG2_IOC2_WRMASK          0xf
#define TMSP0_REG2_IOC2_WRNMASK         (0xf0)
#define TMSP0_REG2_IOC2_WIDTH           8
#define TMSP0_REG2_IOC4_WRMASK          0x75
#define TMSP0_REG2_IOC4_WRNMASK         (0x8a)
#define TMSP0_REG2_IOC4_WIDTH           8
#define TMSP0_REG2_OPT0_WRMASK          0xf
#define TMSP0_REG2_OPT0_WRNMASK         (0xf0)
#define TMSP0_REG2_OPT0_WIDTH           8
#define TMSP0_REG2_OPT4_WRMASK          0x8f
#define TMSP0_REG2_OPT4_WRNMASK         (0x70)
#define TMSP0_REG2_OPT4_WIDTH           8
#define TMSP0_REG2_OPT5_WRMASK          0xff
#define TMSP0_REG2_OPT5_WRNMASK         (0x0)
#define TMSP0_REG2_OPT5_WIDTH           8
#define TMSP0_REG2_OPT7_WRMASK          0x3f
#define TMSP0_REG2_OPT7_WRNMASK         (0xc0)
#define TMSP0_REG2_OPT7_WIDTH           8
#define TMSP0_REG3_OPT1_WRMASK          0x1fff
#define TMSP0_REG3_OPT1_WRNMASK         (0xe000)
#define TMSP0_REG3_OPT1_WIDTH           16
#define TMSP0_REG3_OPT2_WRMASK          0xffff
#define TMSP0_REG3_OPT2_WRNMASK         (0x0)
#define TMSP0_REG3_OPT2_WIDTH           16
#define TMSP0_REG3_OPT3_WRMASK          0x3ff
#define TMSP0_REG3_OPT3_WRNMASK         (0xfc00)
#define TMSP0_REG3_OPT3_WIDTH           16
#define TMSP0_REG3_OPT6_WRMASK          0x1ff
#define TMSP0_REG3_OPT6_WRNMASK         (0xfe00)
#define TMSP0_REG3_OPT6_WIDTH           16
#define TMSP0_REG3_DTC0_WRMASK          0x3fe
#define TMSP0_REG3_DTC0_WRNMASK         (0xfc01)
#define TMSP0_REG3_DTC0_WIDTH           16
#define TMSP0_REG3_DTC1_WRMASK          0x3fe
#define TMSP0_REG3_DTC1_WRNMASK         (0xfc01)
#define TMSP0_REG3_DTC1_WIDTH           16
#define TMSP0_REG3_PAT0_WRMASK          0xffff
#define TMSP0_REG3_PAT0_WRNMASK         (0x0)
#define TMSP0_REG3_PAT0_WIDTH           16
#define TMSP0_REG3_PAT1_WRMASK          0xffff
#define TMSP0_REG3_PAT1_WRNMASK         (0x0)
#define TMSP0_REG3_PAT1_WIDTH           16
#define TMSP0_REG3_CCR0_WRMASK          0xffff
#define TMSP0_REG3_CCR0_WRNMASK         (0x0)
#define TMSP0_REG3_CCR0_WIDTH           16
#define TMSP0_REG3_CCR1_WRMASK          0xffff
#define TMSP0_REG3_CCR1_WRNMASK         (0x0)
#define TMSP0_REG3_CCR1_WIDTH           16
#define TMSP0_REG3_CCR2_WRMASK          0xffff
#define TMSP0_REG3_CCR2_WRNMASK         (0x0)
#define TMSP0_REG3_CCR2_WIDTH           16
#define TMSP0_REG3_CCR3_WRMASK          0xffff
#define TMSP0_REG3_CCR3_WRNMASK         (0x0)
#define TMSP0_REG3_CCR3_WIDTH           16
#define TMSP0_REG3_CCR4_WRMASK          0xffff
#define TMSP0_REG3_CCR4_WRNMASK         (0x0)
#define TMSP0_REG3_CCR4_WIDTH           16
#define TMSP0_REG3_CCR5_WRMASK          0xffff
#define TMSP0_REG3_CCR5_WRNMASK         (0x0)
#define TMSP0_REG3_CCR5_WIDTH           16
#define TMSP0_REG3_CNT_WIDTH            16
#define TMSP0_REG3_SBC_WIDTH            16

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
