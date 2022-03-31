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
            Uns32 DATA : 8;
            Uns32 __pad8 : 2;
            Uns32 PRERR : 1;
            Uns32 BRK : 1;
            Uns32 FRMERR : 1;
            Uns32 OVRRUN : 1;
            Uns32 ERR : 1;
            Uns32 CHARRDY : 1;
        } bits;
    } UART_URXD;
    union { 
        Uns32 value;
        struct {
            Uns32 DATA : 8;
        } bits;
    } UART_UTXD;
    union { 
        Uns32 value;
        struct {
            Uns32 UARTEN : 1;
            Uns32 DOZE : 1;
            Uns32 ATDMAEN : 1;
            Uns32 TXDMAEN : 1;
            Uns32 SNDBRK : 1;
            Uns32 RTSDEN : 1;
            Uns32 TXMPTYEN : 1;
            Uns32 IREN : 1;
            Uns32 RXDMAEN : 1;
            Uns32 RRDYEN : 1;
            Uns32 ICD : 2;
            Uns32 IDEN : 1;
            Uns32 TRDYEN : 1;
            Uns32 ADBR : 1;
            Uns32 ADEN : 1;
        } bits;
    } UART_UCR1;
    union { 
        Uns32 value;
        struct {
            Uns32 SRST : 1;
            Uns32 RXEN : 1;
            Uns32 TXEN : 1;
            Uns32 ATEN : 1;
            Uns32 RTSEN : 1;
            Uns32 WS : 1;
            Uns32 STPB : 1;
            Uns32 PROE : 1;
            Uns32 PREN : 1;
            Uns32 RTEC : 2;
            Uns32 ESCEN : 1;
            Uns32 CTS : 1;
            Uns32 CTSC : 1;
            Uns32 IRTS : 1;
            Uns32 ESCI : 1;
        } bits;
    } UART_UCR2;
    union { 
        Uns32 value;
        struct {
            Uns32 ACIEN : 1;
            Uns32 INVT : 1;
            Uns32 RXDMUXSEL : 1;
            Uns32 DTRDEN : 1;
            Uns32 AWAKEN : 1;
            Uns32 AIRINTEN : 1;
            Uns32 RXDSEN : 1;
            Uns32 ADNIMP : 1;
            Uns32 RI : 1;
            Uns32 DCD : 1;
            Uns32 DSR : 1;
            Uns32 FRAERREN : 1;
            Uns32 PARERREN : 1;
            Uns32 DTREN : 1;
            Uns32 DPEC : 2;
        } bits;
    } UART_UCR3;
    union { 
        Uns32 value;
        struct {
            Uns32 DREN : 1;
            Uns32 OREN : 1;
            Uns32 BKEN : 1;
            Uns32 TCEN : 1;
            Uns32 LPBYP : 1;
            Uns32 IRSC : 1;
            Uns32 IDDMAEN : 1;
            Uns32 WKEN : 1;
            Uns32 ENIRI : 1;
            Uns32 INVR : 1;
            Uns32 CTSTL : 6;
        } bits;
    } UART_UCR4;
    union { 
        Uns32 value;
        struct {
            Uns32 RXTL : 6;
            Uns32 DCEDTE : 1;
            Uns32 RFDIV : 3;
            Uns32 TXTL : 6;
        } bits;
    } UART_UFCR;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 3;
            Uns32 SAD : 1;
            Uns32 AWAKE : 1;
            Uns32 AIRINT : 1;
            Uns32 RXDS : 1;
            Uns32 DTRD : 1;
            Uns32 AGTIM : 1;
            Uns32 RRDY : 1;
            Uns32 FRAMERR : 1;
            Uns32 ESCF : 1;
            Uns32 RTSD : 1;
            Uns32 TRDY : 1;
            Uns32 RTSS : 1;
            Uns32 PARITYERR : 1;
        } bits;
    } UART_USR1;
    union { 
        Uns32 value;
        struct {
            Uns32 RDR : 1;
            Uns32 ORE : 1;
            Uns32 BRCD : 1;
            Uns32 TXDC : 1;
            Uns32 RTSF : 1;
            Uns32 DCDIN : 1;
            Uns32 DCDDELT : 1;
            Uns32 WAKE : 1;
            Uns32 IRINT : 1;
            Uns32 RIIN : 1;
            Uns32 RIDELT : 1;
            Uns32 ACST : 1;
            Uns32 IDLE : 1;
            Uns32 DTRF : 1;
            Uns32 TXFE : 1;
            Uns32 ADET : 1;
        } bits;
    } UART_USR2;
    union { 
        Uns32 value;
        struct {
            Uns32 ESC_CHAR : 8;
        } bits;
    } UART_UESC;
    union { 
        Uns32 value;
        struct {
            Uns32 TIM : 12;
        } bits;
    } UART_UTIM;
    union { 
        Uns32 value;
        struct {
            Uns32 INC : 16;
        } bits;
    } UART_UBIR;
    union { 
        Uns32 value;
        struct {
            Uns32 MOD : 16;
        } bits;
    } UART_UBMR;
    union { 
        Uns32 value;
        struct {
            Uns32 BCNT : 16;
        } bits;
    } UART_UBRC;
    union { 
        Uns32 value;
        struct {
            Uns32 ONEMS : 24;
        } bits;
    } UART_ONEMS;
    union { 
        Uns32 value;
        struct {
            Uns32 SOFTRST : 1;
            Uns32 __pad1 : 2;
            Uns32 RXFULL : 1;
            Uns32 TXFULL : 1;
            Uns32 RXEMPTY : 1;
            Uns32 TXEMPTY : 1;
            Uns32 __pad7 : 2;
            Uns32 RXDBG : 1;
            Uns32 LOOPIR : 1;
            Uns32 DBGEN : 1;
            Uns32 LOOP : 1;
            Uns32 FRCPERR : 1;
        } bits;
    } UART_UTS;
    union { 
        Uns32 value;
        struct {
            Uns32 MDEN : 1;
            Uns32 SLAM : 1;
            Uns32 TXB8 : 1;
            Uns32 SADEN : 1;
            Uns32 __pad4 : 4;
            Uns32 SLADDR : 8;
        } bits;
    } UART_UMCR;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    void                 *bport1;
    ppmNetHandle          irq;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(ReadUART_URXD);
PPM_REG_WRITE_CB(WriteUART_UCR1);
PPM_REG_WRITE_CB(WriteUART_UCR2);
PPM_REG_WRITE_CB(WriteUART_UCR3);
PPM_REG_WRITE_CB(WriteUART_UCR4);
PPM_REG_WRITE_CB(WriteUART_UFCR);
PPM_REG_WRITE_CB(WriteUART_UMCR);
PPM_REG_WRITE_CB(WriteUART_USR1);
PPM_REG_WRITE_CB(WriteUART_USR2);
PPM_REG_WRITE_CB(WriteUART_UTXD);
PPM_WRITE_CB(regNoDefinitionRead);
PPM_READ_CB(regNoDefinitionWrite);
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
#define BPORT1_AB_BUFFER_SIZE           0x4000

////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_UART_URXD_WIDTH       32
#define BPORT1_AB_UART_UTXD_WRMASK      0xff
#define BPORT1_AB_UART_UTXD_WRNMASK     (0xffffff00)
#define BPORT1_AB_UART_UTXD_WIDTH       32
#define BPORT1_AB_UART_UCR1_WRMASK      0xffff
#define BPORT1_AB_UART_UCR1_WRNMASK     (0xffff0000)
#define BPORT1_AB_UART_UCR1_WIDTH       32
#define BPORT1_AB_UART_UCR2_WRMASK      0xffff
#define BPORT1_AB_UART_UCR2_WRNMASK     (0xffff0000)
#define BPORT1_AB_UART_UCR2_WIDTH       32
#define BPORT1_AB_UART_UCR3_WRMASK      0xffff
#define BPORT1_AB_UART_UCR3_WRNMASK     (0xffff0000)
#define BPORT1_AB_UART_UCR3_WIDTH       32
#define BPORT1_AB_UART_UCR4_WRMASK      0xffff
#define BPORT1_AB_UART_UCR4_WRNMASK     (0xffff0000)
#define BPORT1_AB_UART_UCR4_WIDTH       32
#define BPORT1_AB_UART_UFCR_WRMASK      0xffff
#define BPORT1_AB_UART_UFCR_WRNMASK     (0xffff0000)
#define BPORT1_AB_UART_UFCR_WIDTH       32
#define BPORT1_AB_UART_USR1_WRMASK      0x9db8
#define BPORT1_AB_UART_USR1_WRNMASK     (0xffff6247)
#define BPORT1_AB_UART_USR1_WIDTH       32
#define BPORT1_AB_UART_USR2_WRMASK      0xbdd6
#define BPORT1_AB_UART_USR2_WRNMASK     (0xffff4229)
#define BPORT1_AB_UART_USR2_WIDTH       32
#define BPORT1_AB_UART_UESC_WRMASK      0xff
#define BPORT1_AB_UART_UESC_WRNMASK     (0xffffff00)
#define BPORT1_AB_UART_UESC_WIDTH       32
#define BPORT1_AB_UART_UTIM_WRMASK      0xfff
#define BPORT1_AB_UART_UTIM_WRNMASK     (0xfffff000)
#define BPORT1_AB_UART_UTIM_WIDTH       32
#define BPORT1_AB_UART_UBIR_WRMASK      0xffff
#define BPORT1_AB_UART_UBIR_WRNMASK     (0xffff0000)
#define BPORT1_AB_UART_UBIR_WIDTH       32
#define BPORT1_AB_UART_UBMR_WRMASK      0xffff
#define BPORT1_AB_UART_UBMR_WRNMASK     (0xffff0000)
#define BPORT1_AB_UART_UBMR_WIDTH       32
#define BPORT1_AB_UART_UBRC_WIDTH       32
#define BPORT1_AB_UART_ONEMS_WRMASK     0xffffff
#define BPORT1_AB_UART_ONEMS_WRNMASK    (0xff000000)
#define BPORT1_AB_UART_ONEMS_WIDTH      32
#define BPORT1_AB_UART_UTS_WRMASK       0x3e79
#define BPORT1_AB_UART_UTS_WRNMASK      (0xffffc186)
#define BPORT1_AB_UART_UTS_WIDTH        32
#define BPORT1_AB_UART_UMCR_WRMASK      0xff0f
#define BPORT1_AB_UART_UMCR_WRNMASK     (0xffff00f0)
#define BPORT1_AB_UART_UMCR_WIDTH       32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
