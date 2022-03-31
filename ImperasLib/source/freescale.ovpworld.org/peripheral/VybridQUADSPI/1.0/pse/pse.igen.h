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
            Uns32 SWRSTSD : 1;
            Uns32 SWRSTHD : 1;
            Uns32 END_CFG : 2;
            Uns32 __pad4 : 2;
            Uns32 DQS_EN : 1;
            Uns32 DDR_EN : 1;
            Uns32 __pad8 : 2;
            Uns32 CLR_RXF : 1;
            Uns32 CLR_TXF : 1;
            Uns32 __pad12 : 2;
            Uns32 MDIS : 1;
            Uns32 __pad15 : 9;
            Uns32 SCLKCFG : 8;
        } bits;
    } MCR;
    union { 
        Uns32 value;
        struct {
            Uns32 IDATSZ : 16;
            Uns32 PAR_EN : 1;
            Uns32 __pad17 : 7;
            Uns32 SEQID : 4;
        } bits;
    } IPCR;
    union { 
        Uns32 value;
        struct {
            Uns32 TCSS : 4;
            Uns32 __pad4 : 4;
            Uns32 TCSH : 4;
        } bits;
    } FLSHCR;
    union { 
        Uns32 value;
        struct {
            Uns32 MSTRID : 4;
            Uns32 __pad4 : 4;
            Uns32 ADATSZ : 8;
            Uns32 __pad16 : 15;
            Uns32 HP_EN : 1;
        } bits;
    } BUF0CR;
    union { 
        Uns32 value;
        struct {
            Uns32 MSTRID : 4;
            Uns32 __pad4 : 4;
            Uns32 ADATSZ : 8;
        } bits;
    } BUF1CR;
    union { 
        Uns32 value;
        struct {
            Uns32 MSTRID : 4;
            Uns32 __pad4 : 4;
            Uns32 ADATSZ : 8;
        } bits;
    } BUF2CR;
    union { 
        Uns32 value;
        struct {
            Uns32 MSTRID : 4;
            Uns32 __pad4 : 4;
            Uns32 ADATSZ : 8;
            Uns32 __pad16 : 15;
            Uns32 ALLMST : 1;
        } bits;
    } BUF3CR;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 12;
            Uns32 SEQID : 4;
            Uns32 PAR_EN : 1;
        } bits;
    } BFGENCR;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 3;
            Uns32 TPINDX0 : 29;
        } bits;
    } BUF0IND;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 3;
            Uns32 TPINDX1 : 29;
        } bits;
    } BUF1IND;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 3;
            Uns32 TPINDX2 : 29;
        } bits;
    } BUF2IND;
    union { 
        Uns32 value;
        struct {
            Uns32 SFADR : 32;
        } bits;
    } SFAR;
    union { 
        Uns32 value;
        struct {
            Uns32 HSENA : 1;
            Uns32 HSPHS : 1;
            Uns32 HSDLY : 1;
            Uns32 __pad3 : 2;
            Uns32 FSPHS : 1;
            Uns32 FSDLY : 1;
            Uns32 __pad7 : 9;
            Uns32 DDRSMP : 3;
        } bits;
    } SMPR;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 8;
            Uns32 RDBFL : 6;
            Uns32 __pad14 : 2;
            Uns32 RDCTR : 16;
        } bits;
    } RBSR;
    union { 
        Uns32 value;
        struct {
            Uns32 WMRK : 5;
            Uns32 __pad5 : 3;
            Uns32 RXBRD : 1;
        } bits;
    } RBCT;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 8;
            Uns32 TRBFL : 5;
            Uns32 __pad13 : 3;
            Uns32 TRCTR : 16;
        } bits;
    } TBSR;
    union { 
        Uns32 value;
        struct {
            Uns32 TXDATA : 32;
        } bits;
    } TBDR;
    union { 
        Uns32 value;
        struct {
            Uns32 BUSY : 1;
            Uns32 IP_ACC : 1;
            Uns32 AHB_ACC : 1;
            Uns32 __pad3 : 2;
            Uns32 AHBGNT : 1;
            Uns32 AHBTRN : 1;
            Uns32 AHB0NE : 1;
            Uns32 AHB1NE : 1;
            Uns32 AHB2NE : 1;
            Uns32 AHB3NE : 1;
            Uns32 AHB0FUL : 1;
            Uns32 AHB1FUL : 1;
            Uns32 AHB2FUL : 1;
            Uns32 AHB3FUL : 1;
            Uns32 __pad15 : 1;
            Uns32 RXWE : 1;
            Uns32 __pad17 : 2;
            Uns32 RXFULL : 1;
            Uns32 __pad20 : 3;
            Uns32 RXDMA : 1;
            Uns32 TXNE : 1;
            Uns32 __pad25 : 2;
            Uns32 TXFULL : 1;
            Uns32 __pad28 : 1;
            Uns32 DLPSMP : 3;
        } bits;
    } SR;
    union { 
        Uns32 value;
        struct {
            Uns32 TFF : 1;
            Uns32 __pad1 : 3;
            Uns32 IPGEF : 1;
            Uns32 __pad5 : 1;
            Uns32 IPIEF : 1;
            Uns32 IPAEF : 1;
            Uns32 __pad8 : 3;
            Uns32 IUEF : 1;
            Uns32 ABOF : 1;
            Uns32 __pad13 : 2;
            Uns32 ABSEF : 1;
            Uns32 RBDF : 1;
            Uns32 RBOF : 1;
            Uns32 __pad18 : 5;
            Uns32 ILLINE : 1;
            Uns32 __pad24 : 2;
            Uns32 TBUF : 1;
            Uns32 TBFF : 1;
            Uns32 __pad28 : 3;
            Uns32 DLPFF : 1;
        } bits;
    } FR;
    union { 
        Uns32 value;
        struct {
            Uns32 TFIE : 1;
            Uns32 __pad1 : 3;
            Uns32 IPGEIE : 1;
            Uns32 __pad5 : 1;
            Uns32 IPIEIE : 1;
            Uns32 IPAEIE : 1;
            Uns32 __pad8 : 3;
            Uns32 IUEIE : 1;
            Uns32 ABOIE : 1;
            Uns32 __pad13 : 2;
            Uns32 ABSEIE : 1;
            Uns32 RBDIE : 1;
            Uns32 RBOIE : 1;
            Uns32 __pad18 : 3;
            Uns32 RBDDE : 1;
            Uns32 __pad22 : 1;
            Uns32 ILLINIE : 1;
            Uns32 __pad24 : 2;
            Uns32 TBUIE : 1;
            Uns32 TBFIE : 1;
            Uns32 __pad28 : 3;
            Uns32 DLPFIE : 1;
        } bits;
    } RSER;
    union { 
        Uns32 value;
        struct {
            Uns32 SUSPND : 1;
            Uns32 __pad1 : 5;
            Uns32 SPDBUF : 2;
            Uns32 __pad8 : 1;
            Uns32 DATLFT : 7;
        } bits;
    } SPNDST;
    union { 
        Uns32 value;
        struct {
            Uns32 BFPTRC : 1;
            Uns32 __pad1 : 7;
            Uns32 IPPTRC : 1;
        } bits;
    } SPTRCLR;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 10;
            Uns32 TPADA1 : 22;
        } bits;
    } SFA1AD;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 10;
            Uns32 TPADA2 : 22;
        } bits;
    } SFA2AD;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 10;
            Uns32 TPADB1 : 22;
        } bits;
    } SFB1AD;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 10;
            Uns32 TPADB2 : 22;
        } bits;
    } SFB2AD;
    union { 
        Uns32 value;
        struct {
            Uns32 KEY : 32;
        } bits;
    } LUTKEY;
    union { 
        Uns32 value;
        struct {
            Uns32 LOCK : 1;
            Uns32 UNLOCK : 1;
        } bits;
    } LCKCR;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR0;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR1;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR2;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR3;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR4;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR5;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR6;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR7;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR8;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR9;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR10;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR11;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR12;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR13;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR14;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR15;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR16;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR17;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR18;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR19;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR20;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR21;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR22;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR23;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR24;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR25;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR26;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR27;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR28;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR29;
    union { 
        Uns32 value;
        struct {
            Uns32 RXDATA : 32;
        } bits;
    } RBDR30;
    union { 
        Uns32 value;
    } RBDR31;
    union { 
        Uns32 value;
    } RBDR32;
    union { 
        Uns32 value;
    } RBDR33;
    union { 
        Uns32 value;
    } RBDR34;
    union { 
        Uns32 value;
    } RBDR35;
    union { 
        Uns32 value;
    } RBDR36;
    union { 
        Uns32 value;
    } RBDR37;
    union { 
        Uns32 value;
    } RBDR38;
    union { 
        Uns32 value;
    } RBDR39;
    union { 
        Uns32 value;
    } RBDR40;
    union { 
        Uns32 value;
    } RBDR41;
    union { 
        Uns32 value;
    } RBDR42;
    union { 
        Uns32 value;
    } RBDR43;
    union { 
        Uns32 value;
    } RBDR44;
    union { 
        Uns32 value;
    } RBDR45;
    union { 
        Uns32 value;
    } RBDR46;
    union { 
        Uns32 value;
    } RBDR47;
    union { 
        Uns32 value;
    } RBDR48;
    union { 
        Uns32 value;
    } RBDR49;
    union { 
        Uns32 value;
    } RBDR50;
    union { 
        Uns32 value;
    } RBDR51;
    union { 
        Uns32 value;
    } RBDR52;
    union { 
        Uns32 value;
    } RBDR53;
    union { 
        Uns32 value;
    } RBDR54;
    union { 
        Uns32 value;
    } RBDR55;
    union { 
        Uns32 value;
    } RBDR56;
    union { 
        Uns32 value;
    } RBDR57;
    union { 
        Uns32 value;
    } RBDR58;
    union { 
        Uns32 value;
    } RBDR59;
    union { 
        Uns32 value;
    } RBDR60;
    union { 
        Uns32 value;
    } RBDR61;
    union { 
        Uns32 value;
    } RBDR62;
    union { 
        Uns32 value;
    } RBDR63;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT0;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT1;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT2;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT3;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT4;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT5;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT6;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT7;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT8;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT9;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT10;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT11;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT12;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT13;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT14;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT15;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT16;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT17;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT18;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT19;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT20;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT21;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT22;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT23;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT24;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT25;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT26;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT27;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT28;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT29;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT30;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT31;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT32;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT33;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT34;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT35;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT36;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT37;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT38;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT39;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT40;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT41;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT42;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT43;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT44;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT45;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT46;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT47;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT48;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT49;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT50;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT51;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT52;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT53;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT54;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT55;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT56;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT57;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT58;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT59;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT60;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT61;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT62;
    union { 
        Uns32 value;
        struct {
            Uns32 OPRND0 : 8;
            Uns32 PAD0 : 2;
            Uns32 INSTR0 : 6;
            Uns32 OPRND1 : 8;
            Uns32 PAD1 : 2;
            Uns32 INSTR1 : 6;
        } bits;
    } LUT63;
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

PPM_REG_READ_CB(readLutKey);
PPM_REG_READ_CB(readLutLck);
PPM_REG_WRITE_CB(writeLutKey);
PPM_REG_WRITE_CB(writeLutLck);
PPM_NET_CB(reset_Reset);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_MCR_WRMASK            0xff004ccf
#define BPORT1_AB_MCR_WRNMASK           (0xffb330)
#define BPORT1_AB_MCR_WIDTH             32
#define BPORT1_AB_IPCR_WRMASK           0xf01ffff
#define BPORT1_AB_IPCR_WRNMASK          (0xf0fe0000)
#define BPORT1_AB_IPCR_WIDTH            32
#define BPORT1_AB_FLSHCR_WRMASK         0xf0f
#define BPORT1_AB_FLSHCR_WRNMASK        (0xfffff0f0)
#define BPORT1_AB_FLSHCR_WIDTH          32
#define BPORT1_AB_BUF0CR_WRMASK         0x8000ff0f
#define BPORT1_AB_BUF0CR_WRNMASK        (0x7fff00f0)
#define BPORT1_AB_BUF0CR_WIDTH          32
#define BPORT1_AB_BUF1CR_WRMASK         0xff0f
#define BPORT1_AB_BUF1CR_WRNMASK        (0xffff00f0)
#define BPORT1_AB_BUF1CR_WIDTH          32
#define BPORT1_AB_BUF2CR_WRMASK         0xff0f
#define BPORT1_AB_BUF2CR_WRNMASK        (0xffff00f0)
#define BPORT1_AB_BUF2CR_WIDTH          32
#define BPORT1_AB_BUF3CR_WRMASK         0x8000ff0f
#define BPORT1_AB_BUF3CR_WRNMASK        (0x7fff00f0)
#define BPORT1_AB_BUF3CR_WIDTH          32
#define BPORT1_AB_BFGENCR_WRMASK        0x1f000
#define BPORT1_AB_BFGENCR_WRNMASK       (0xfffe0fff)
#define BPORT1_AB_BFGENCR_WIDTH         32
#define BPORT1_AB_BUF0IND_WRMASK        0xfffffff8
#define BPORT1_AB_BUF0IND_WRNMASK       (0x7)
#define BPORT1_AB_BUF0IND_WIDTH         32
#define BPORT1_AB_BUF1IND_WRMASK        0xfffffff8
#define BPORT1_AB_BUF1IND_WRNMASK       (0x7)
#define BPORT1_AB_BUF1IND_WIDTH         32
#define BPORT1_AB_BUF2IND_WRMASK        0xfffffff8
#define BPORT1_AB_BUF2IND_WRNMASK       (0x7)
#define BPORT1_AB_BUF2IND_WIDTH         32
#define BPORT1_AB_SFAR_WRMASK           0xffffffff
#define BPORT1_AB_SFAR_WRNMASK          (0x0)
#define BPORT1_AB_SFAR_WIDTH            32
#define BPORT1_AB_SMPR_WRMASK           0x70067
#define BPORT1_AB_SMPR_WRNMASK          (0xfff8ff98)
#define BPORT1_AB_SMPR_WIDTH            32
#define BPORT1_AB_RBSR_WIDTH            32
#define BPORT1_AB_RBCT_WRMASK           0x11f
#define BPORT1_AB_RBCT_WRNMASK          (0xfffffee0)
#define BPORT1_AB_RBCT_WIDTH            32
#define BPORT1_AB_TBSR_WIDTH            32
#define BPORT1_AB_TBDR_WRMASK           0xffffffff
#define BPORT1_AB_TBDR_WRNMASK          (0x0)
#define BPORT1_AB_TBDR_WIDTH            32
#define BPORT1_AB_SR_WIDTH              32
#define BPORT1_AB_FR_WRMASK             0x8c8398d1
#define BPORT1_AB_FR_WRNMASK            (0x737c672e)
#define BPORT1_AB_FR_WIDTH              32
#define BPORT1_AB_RSER_WRMASK           0x8c8398d1
#define BPORT1_AB_RSER_WRNMASK          (0x737c672e)
#define BPORT1_AB_RSER_WIDTH            32
#define BPORT1_AB_SPNDST_WIDTH          32
#define BPORT1_AB_SPTRCLR_WRMASK        0x101
#define BPORT1_AB_SPTRCLR_WRNMASK       (0xfffffefe)
#define BPORT1_AB_SPTRCLR_WIDTH         32
#define BPORT1_AB_SFA1AD_WRMASK         0xfffffc00
#define BPORT1_AB_SFA1AD_WRNMASK        (0x3ff)
#define BPORT1_AB_SFA1AD_WIDTH          32
#define BPORT1_AB_SFA2AD_WRMASK         0xfffffc00
#define BPORT1_AB_SFA2AD_WRNMASK        (0x3ff)
#define BPORT1_AB_SFA2AD_WIDTH          32
#define BPORT1_AB_SFB1AD_WRMASK         0xfffffc00
#define BPORT1_AB_SFB1AD_WRNMASK        (0x3ff)
#define BPORT1_AB_SFB1AD_WIDTH          32
#define BPORT1_AB_SFB2AD_WRMASK         0xfffffc00
#define BPORT1_AB_SFB2AD_WRNMASK        (0x3ff)
#define BPORT1_AB_SFB2AD_WIDTH          32
#define BPORT1_AB_LUTKEY_WRMASK         0xffffffff
#define BPORT1_AB_LUTKEY_WRNMASK        (0x0)
#define BPORT1_AB_LUTKEY_WIDTH          32
#define BPORT1_AB_LCKCR_WRMASK          0x3
#define BPORT1_AB_LCKCR_WRNMASK         (0xfffffffc)
#define BPORT1_AB_LCKCR_WIDTH           32
#define BPORT1_AB_RBDR0_WRMASK          0xffffffff
#define BPORT1_AB_RBDR0_WRNMASK         (0x0)
#define BPORT1_AB_RBDR0_WIDTH           32
#define BPORT1_AB_RBDR1_WRMASK          0xffffffff
#define BPORT1_AB_RBDR1_WRNMASK         (0x0)
#define BPORT1_AB_RBDR1_WIDTH           32
#define BPORT1_AB_RBDR2_WRMASK          0xffffffff
#define BPORT1_AB_RBDR2_WRNMASK         (0x0)
#define BPORT1_AB_RBDR2_WIDTH           32
#define BPORT1_AB_RBDR3_WRMASK          0xffffffff
#define BPORT1_AB_RBDR3_WRNMASK         (0x0)
#define BPORT1_AB_RBDR3_WIDTH           32
#define BPORT1_AB_RBDR4_WRMASK          0xffffffff
#define BPORT1_AB_RBDR4_WRNMASK         (0x0)
#define BPORT1_AB_RBDR4_WIDTH           32
#define BPORT1_AB_RBDR5_WRMASK          0xffffffff
#define BPORT1_AB_RBDR5_WRNMASK         (0x0)
#define BPORT1_AB_RBDR5_WIDTH           32
#define BPORT1_AB_RBDR6_WRMASK          0xffffffff
#define BPORT1_AB_RBDR6_WRNMASK         (0x0)
#define BPORT1_AB_RBDR6_WIDTH           32
#define BPORT1_AB_RBDR7_WRMASK          0xffffffff
#define BPORT1_AB_RBDR7_WRNMASK         (0x0)
#define BPORT1_AB_RBDR7_WIDTH           32
#define BPORT1_AB_RBDR8_WRMASK          0xffffffff
#define BPORT1_AB_RBDR8_WRNMASK         (0x0)
#define BPORT1_AB_RBDR8_WIDTH           32
#define BPORT1_AB_RBDR9_WRMASK          0xffffffff
#define BPORT1_AB_RBDR9_WRNMASK         (0x0)
#define BPORT1_AB_RBDR9_WIDTH           32
#define BPORT1_AB_RBDR10_WRMASK         0xffffffff
#define BPORT1_AB_RBDR10_WRNMASK        (0x0)
#define BPORT1_AB_RBDR10_WIDTH          32
#define BPORT1_AB_RBDR11_WRMASK         0xffffffff
#define BPORT1_AB_RBDR11_WRNMASK        (0x0)
#define BPORT1_AB_RBDR11_WIDTH          32
#define BPORT1_AB_RBDR12_WRMASK         0xffffffff
#define BPORT1_AB_RBDR12_WRNMASK        (0x0)
#define BPORT1_AB_RBDR12_WIDTH          32
#define BPORT1_AB_RBDR13_WRMASK         0xffffffff
#define BPORT1_AB_RBDR13_WRNMASK        (0x0)
#define BPORT1_AB_RBDR13_WIDTH          32
#define BPORT1_AB_RBDR14_WRMASK         0xffffffff
#define BPORT1_AB_RBDR14_WRNMASK        (0x0)
#define BPORT1_AB_RBDR14_WIDTH          32
#define BPORT1_AB_RBDR15_WRMASK         0xffffffff
#define BPORT1_AB_RBDR15_WRNMASK        (0x0)
#define BPORT1_AB_RBDR15_WIDTH          32
#define BPORT1_AB_RBDR16_WRMASK         0xffffffff
#define BPORT1_AB_RBDR16_WRNMASK        (0x0)
#define BPORT1_AB_RBDR16_WIDTH          32
#define BPORT1_AB_RBDR17_WRMASK         0xffffffff
#define BPORT1_AB_RBDR17_WRNMASK        (0x0)
#define BPORT1_AB_RBDR17_WIDTH          32
#define BPORT1_AB_RBDR18_WRMASK         0xffffffff
#define BPORT1_AB_RBDR18_WRNMASK        (0x0)
#define BPORT1_AB_RBDR18_WIDTH          32
#define BPORT1_AB_RBDR19_WRMASK         0xffffffff
#define BPORT1_AB_RBDR19_WRNMASK        (0x0)
#define BPORT1_AB_RBDR19_WIDTH          32
#define BPORT1_AB_RBDR20_WRMASK         0xffffffff
#define BPORT1_AB_RBDR20_WRNMASK        (0x0)
#define BPORT1_AB_RBDR20_WIDTH          32
#define BPORT1_AB_RBDR21_WRMASK         0xffffffff
#define BPORT1_AB_RBDR21_WRNMASK        (0x0)
#define BPORT1_AB_RBDR21_WIDTH          32
#define BPORT1_AB_RBDR22_WRMASK         0xffffffff
#define BPORT1_AB_RBDR22_WRNMASK        (0x0)
#define BPORT1_AB_RBDR22_WIDTH          32
#define BPORT1_AB_RBDR23_WRMASK         0xffffffff
#define BPORT1_AB_RBDR23_WRNMASK        (0x0)
#define BPORT1_AB_RBDR23_WIDTH          32
#define BPORT1_AB_RBDR24_WRMASK         0xffffffff
#define BPORT1_AB_RBDR24_WRNMASK        (0x0)
#define BPORT1_AB_RBDR24_WIDTH          32
#define BPORT1_AB_RBDR25_WRMASK         0xffffffff
#define BPORT1_AB_RBDR25_WRNMASK        (0x0)
#define BPORT1_AB_RBDR25_WIDTH          32
#define BPORT1_AB_RBDR26_WRMASK         0xffffffff
#define BPORT1_AB_RBDR26_WRNMASK        (0x0)
#define BPORT1_AB_RBDR26_WIDTH          32
#define BPORT1_AB_RBDR27_WRMASK         0xffffffff
#define BPORT1_AB_RBDR27_WRNMASK        (0x0)
#define BPORT1_AB_RBDR27_WIDTH          32
#define BPORT1_AB_RBDR28_WRMASK         0xffffffff
#define BPORT1_AB_RBDR28_WRNMASK        (0x0)
#define BPORT1_AB_RBDR28_WIDTH          32
#define BPORT1_AB_RBDR29_WRMASK         0xffffffff
#define BPORT1_AB_RBDR29_WRNMASK        (0x0)
#define BPORT1_AB_RBDR29_WIDTH          32
#define BPORT1_AB_RBDR30_WRMASK         0xffffffff
#define BPORT1_AB_RBDR30_WRNMASK        (0x0)
#define BPORT1_AB_RBDR30_WIDTH          32
#define BPORT1_AB_RBDR31_WRMASK         0xffffffff
#define BPORT1_AB_RBDR31_WRNMASK        (0x0)
#define BPORT1_AB_RBDR31_WIDTH          32
#define BPORT1_AB_RBDR32_WRMASK         0xffffffff
#define BPORT1_AB_RBDR32_WRNMASK        (0x0)
#define BPORT1_AB_RBDR32_WIDTH          32
#define BPORT1_AB_RBDR33_WRMASK         0xffffffff
#define BPORT1_AB_RBDR33_WRNMASK        (0x0)
#define BPORT1_AB_RBDR33_WIDTH          32
#define BPORT1_AB_RBDR34_WRMASK         0xffffffff
#define BPORT1_AB_RBDR34_WRNMASK        (0x0)
#define BPORT1_AB_RBDR34_WIDTH          32
#define BPORT1_AB_RBDR35_WRMASK         0xffffffff
#define BPORT1_AB_RBDR35_WRNMASK        (0x0)
#define BPORT1_AB_RBDR35_WIDTH          32
#define BPORT1_AB_RBDR36_WRMASK         0xffffffff
#define BPORT1_AB_RBDR36_WRNMASK        (0x0)
#define BPORT1_AB_RBDR36_WIDTH          32
#define BPORT1_AB_RBDR37_WRMASK         0xffffffff
#define BPORT1_AB_RBDR37_WRNMASK        (0x0)
#define BPORT1_AB_RBDR37_WIDTH          32
#define BPORT1_AB_RBDR38_WRMASK         0xffffffff
#define BPORT1_AB_RBDR38_WRNMASK        (0x0)
#define BPORT1_AB_RBDR38_WIDTH          32
#define BPORT1_AB_RBDR39_WRMASK         0xffffffff
#define BPORT1_AB_RBDR39_WRNMASK        (0x0)
#define BPORT1_AB_RBDR39_WIDTH          32
#define BPORT1_AB_RBDR40_WRMASK         0xffffffff
#define BPORT1_AB_RBDR40_WRNMASK        (0x0)
#define BPORT1_AB_RBDR40_WIDTH          32
#define BPORT1_AB_RBDR41_WRMASK         0xffffffff
#define BPORT1_AB_RBDR41_WRNMASK        (0x0)
#define BPORT1_AB_RBDR41_WIDTH          32
#define BPORT1_AB_RBDR42_WRMASK         0xffffffff
#define BPORT1_AB_RBDR42_WRNMASK        (0x0)
#define BPORT1_AB_RBDR42_WIDTH          32
#define BPORT1_AB_RBDR43_WRMASK         0xffffffff
#define BPORT1_AB_RBDR43_WRNMASK        (0x0)
#define BPORT1_AB_RBDR43_WIDTH          32
#define BPORT1_AB_RBDR44_WRMASK         0xffffffff
#define BPORT1_AB_RBDR44_WRNMASK        (0x0)
#define BPORT1_AB_RBDR44_WIDTH          32
#define BPORT1_AB_RBDR45_WRMASK         0xffffffff
#define BPORT1_AB_RBDR45_WRNMASK        (0x0)
#define BPORT1_AB_RBDR45_WIDTH          32
#define BPORT1_AB_RBDR46_WRMASK         0xffffffff
#define BPORT1_AB_RBDR46_WRNMASK        (0x0)
#define BPORT1_AB_RBDR46_WIDTH          32
#define BPORT1_AB_RBDR47_WRMASK         0xffffffff
#define BPORT1_AB_RBDR47_WRNMASK        (0x0)
#define BPORT1_AB_RBDR47_WIDTH          32
#define BPORT1_AB_RBDR48_WRMASK         0xffffffff
#define BPORT1_AB_RBDR48_WRNMASK        (0x0)
#define BPORT1_AB_RBDR48_WIDTH          32
#define BPORT1_AB_RBDR49_WRMASK         0xffffffff
#define BPORT1_AB_RBDR49_WRNMASK        (0x0)
#define BPORT1_AB_RBDR49_WIDTH          32
#define BPORT1_AB_RBDR50_WRMASK         0xffffffff
#define BPORT1_AB_RBDR50_WRNMASK        (0x0)
#define BPORT1_AB_RBDR50_WIDTH          32
#define BPORT1_AB_RBDR51_WRMASK         0xffffffff
#define BPORT1_AB_RBDR51_WRNMASK        (0x0)
#define BPORT1_AB_RBDR51_WIDTH          32
#define BPORT1_AB_RBDR52_WRMASK         0xffffffff
#define BPORT1_AB_RBDR52_WRNMASK        (0x0)
#define BPORT1_AB_RBDR52_WIDTH          32
#define BPORT1_AB_RBDR53_WRMASK         0xffffffff
#define BPORT1_AB_RBDR53_WRNMASK        (0x0)
#define BPORT1_AB_RBDR53_WIDTH          32
#define BPORT1_AB_RBDR54_WRMASK         0xffffffff
#define BPORT1_AB_RBDR54_WRNMASK        (0x0)
#define BPORT1_AB_RBDR54_WIDTH          32
#define BPORT1_AB_RBDR55_WRMASK         0xffffffff
#define BPORT1_AB_RBDR55_WRNMASK        (0x0)
#define BPORT1_AB_RBDR55_WIDTH          32
#define BPORT1_AB_RBDR56_WRMASK         0xffffffff
#define BPORT1_AB_RBDR56_WRNMASK        (0x0)
#define BPORT1_AB_RBDR56_WIDTH          32
#define BPORT1_AB_RBDR57_WRMASK         0xffffffff
#define BPORT1_AB_RBDR57_WRNMASK        (0x0)
#define BPORT1_AB_RBDR57_WIDTH          32
#define BPORT1_AB_RBDR58_WRMASK         0xffffffff
#define BPORT1_AB_RBDR58_WRNMASK        (0x0)
#define BPORT1_AB_RBDR58_WIDTH          32
#define BPORT1_AB_RBDR59_WRMASK         0xffffffff
#define BPORT1_AB_RBDR59_WRNMASK        (0x0)
#define BPORT1_AB_RBDR59_WIDTH          32
#define BPORT1_AB_RBDR60_WRMASK         0xffffffff
#define BPORT1_AB_RBDR60_WRNMASK        (0x0)
#define BPORT1_AB_RBDR60_WIDTH          32
#define BPORT1_AB_RBDR61_WRMASK         0xffffffff
#define BPORT1_AB_RBDR61_WRNMASK        (0x0)
#define BPORT1_AB_RBDR61_WIDTH          32
#define BPORT1_AB_RBDR62_WRMASK         0xffffffff
#define BPORT1_AB_RBDR62_WRNMASK        (0x0)
#define BPORT1_AB_RBDR62_WIDTH          32
#define BPORT1_AB_RBDR63_WRMASK         0xffffffff
#define BPORT1_AB_RBDR63_WRNMASK        (0x0)
#define BPORT1_AB_RBDR63_WIDTH          32
#define BPORT1_AB_LUT0_WRMASK           0xffffffff
#define BPORT1_AB_LUT0_WRNMASK          (0x0)
#define BPORT1_AB_LUT0_WIDTH            32
#define BPORT1_AB_LUT1_WRMASK           0xffffffff
#define BPORT1_AB_LUT1_WRNMASK          (0x0)
#define BPORT1_AB_LUT1_WIDTH            32
#define BPORT1_AB_LUT2_WRMASK           0xffffffff
#define BPORT1_AB_LUT2_WRNMASK          (0x0)
#define BPORT1_AB_LUT2_WIDTH            32
#define BPORT1_AB_LUT3_WRMASK           0xffffffff
#define BPORT1_AB_LUT3_WRNMASK          (0x0)
#define BPORT1_AB_LUT3_WIDTH            32
#define BPORT1_AB_LUT4_WRMASK           0xffffffff
#define BPORT1_AB_LUT4_WRNMASK          (0x0)
#define BPORT1_AB_LUT4_WIDTH            32
#define BPORT1_AB_LUT5_WRMASK           0xffffffff
#define BPORT1_AB_LUT5_WRNMASK          (0x0)
#define BPORT1_AB_LUT5_WIDTH            32
#define BPORT1_AB_LUT6_WRMASK           0xffffffff
#define BPORT1_AB_LUT6_WRNMASK          (0x0)
#define BPORT1_AB_LUT6_WIDTH            32
#define BPORT1_AB_LUT7_WRMASK           0xffffffff
#define BPORT1_AB_LUT7_WRNMASK          (0x0)
#define BPORT1_AB_LUT7_WIDTH            32
#define BPORT1_AB_LUT8_WRMASK           0xffffffff
#define BPORT1_AB_LUT8_WRNMASK          (0x0)
#define BPORT1_AB_LUT8_WIDTH            32
#define BPORT1_AB_LUT9_WRMASK           0xffffffff
#define BPORT1_AB_LUT9_WRNMASK          (0x0)
#define BPORT1_AB_LUT9_WIDTH            32
#define BPORT1_AB_LUT10_WRMASK          0xffffffff
#define BPORT1_AB_LUT10_WRNMASK         (0x0)
#define BPORT1_AB_LUT10_WIDTH           32
#define BPORT1_AB_LUT11_WRMASK          0xffffffff
#define BPORT1_AB_LUT11_WRNMASK         (0x0)
#define BPORT1_AB_LUT11_WIDTH           32
#define BPORT1_AB_LUT12_WRMASK          0xffffffff
#define BPORT1_AB_LUT12_WRNMASK         (0x0)
#define BPORT1_AB_LUT12_WIDTH           32
#define BPORT1_AB_LUT13_WRMASK          0xffffffff
#define BPORT1_AB_LUT13_WRNMASK         (0x0)
#define BPORT1_AB_LUT13_WIDTH           32
#define BPORT1_AB_LUT14_WRMASK          0xffffffff
#define BPORT1_AB_LUT14_WRNMASK         (0x0)
#define BPORT1_AB_LUT14_WIDTH           32
#define BPORT1_AB_LUT15_WRMASK          0xffffffff
#define BPORT1_AB_LUT15_WRNMASK         (0x0)
#define BPORT1_AB_LUT15_WIDTH           32
#define BPORT1_AB_LUT16_WRMASK          0xffffffff
#define BPORT1_AB_LUT16_WRNMASK         (0x0)
#define BPORT1_AB_LUT16_WIDTH           32
#define BPORT1_AB_LUT17_WRMASK          0xffffffff
#define BPORT1_AB_LUT17_WRNMASK         (0x0)
#define BPORT1_AB_LUT17_WIDTH           32
#define BPORT1_AB_LUT18_WRMASK          0xffffffff
#define BPORT1_AB_LUT18_WRNMASK         (0x0)
#define BPORT1_AB_LUT18_WIDTH           32
#define BPORT1_AB_LUT19_WRMASK          0xffffffff
#define BPORT1_AB_LUT19_WRNMASK         (0x0)
#define BPORT1_AB_LUT19_WIDTH           32
#define BPORT1_AB_LUT20_WRMASK          0xffffffff
#define BPORT1_AB_LUT20_WRNMASK         (0x0)
#define BPORT1_AB_LUT20_WIDTH           32
#define BPORT1_AB_LUT21_WRMASK          0xffffffff
#define BPORT1_AB_LUT21_WRNMASK         (0x0)
#define BPORT1_AB_LUT21_WIDTH           32
#define BPORT1_AB_LUT22_WRMASK          0xffffffff
#define BPORT1_AB_LUT22_WRNMASK         (0x0)
#define BPORT1_AB_LUT22_WIDTH           32
#define BPORT1_AB_LUT23_WRMASK          0xffffffff
#define BPORT1_AB_LUT23_WRNMASK         (0x0)
#define BPORT1_AB_LUT23_WIDTH           32
#define BPORT1_AB_LUT24_WRMASK          0xffffffff
#define BPORT1_AB_LUT24_WRNMASK         (0x0)
#define BPORT1_AB_LUT24_WIDTH           32
#define BPORT1_AB_LUT25_WRMASK          0xffffffff
#define BPORT1_AB_LUT25_WRNMASK         (0x0)
#define BPORT1_AB_LUT25_WIDTH           32
#define BPORT1_AB_LUT26_WRMASK          0xffffffff
#define BPORT1_AB_LUT26_WRNMASK         (0x0)
#define BPORT1_AB_LUT26_WIDTH           32
#define BPORT1_AB_LUT27_WRMASK          0xffffffff
#define BPORT1_AB_LUT27_WRNMASK         (0x0)
#define BPORT1_AB_LUT27_WIDTH           32
#define BPORT1_AB_LUT28_WRMASK          0xffffffff
#define BPORT1_AB_LUT28_WRNMASK         (0x0)
#define BPORT1_AB_LUT28_WIDTH           32
#define BPORT1_AB_LUT29_WRMASK          0xffffffff
#define BPORT1_AB_LUT29_WRNMASK         (0x0)
#define BPORT1_AB_LUT29_WIDTH           32
#define BPORT1_AB_LUT30_WRMASK          0xffffffff
#define BPORT1_AB_LUT30_WRNMASK         (0x0)
#define BPORT1_AB_LUT30_WIDTH           32
#define BPORT1_AB_LUT31_WRMASK          0xffffffff
#define BPORT1_AB_LUT31_WRNMASK         (0x0)
#define BPORT1_AB_LUT31_WIDTH           32
#define BPORT1_AB_LUT32_WRMASK          0xffffffff
#define BPORT1_AB_LUT32_WRNMASK         (0x0)
#define BPORT1_AB_LUT32_WIDTH           32
#define BPORT1_AB_LUT33_WRMASK          0xffffffff
#define BPORT1_AB_LUT33_WRNMASK         (0x0)
#define BPORT1_AB_LUT33_WIDTH           32
#define BPORT1_AB_LUT34_WRMASK          0xffffffff
#define BPORT1_AB_LUT34_WRNMASK         (0x0)
#define BPORT1_AB_LUT34_WIDTH           32
#define BPORT1_AB_LUT35_WRMASK          0xffffffff
#define BPORT1_AB_LUT35_WRNMASK         (0x0)
#define BPORT1_AB_LUT35_WIDTH           32
#define BPORT1_AB_LUT36_WRMASK          0xffffffff
#define BPORT1_AB_LUT36_WRNMASK         (0x0)
#define BPORT1_AB_LUT36_WIDTH           32
#define BPORT1_AB_LUT37_WRMASK          0xffffffff
#define BPORT1_AB_LUT37_WRNMASK         (0x0)
#define BPORT1_AB_LUT37_WIDTH           32
#define BPORT1_AB_LUT38_WRMASK          0xffffffff
#define BPORT1_AB_LUT38_WRNMASK         (0x0)
#define BPORT1_AB_LUT38_WIDTH           32
#define BPORT1_AB_LUT39_WRMASK          0xffffffff
#define BPORT1_AB_LUT39_WRNMASK         (0x0)
#define BPORT1_AB_LUT39_WIDTH           32
#define BPORT1_AB_LUT40_WRMASK          0xffffffff
#define BPORT1_AB_LUT40_WRNMASK         (0x0)
#define BPORT1_AB_LUT40_WIDTH           32
#define BPORT1_AB_LUT41_WRMASK          0xffffffff
#define BPORT1_AB_LUT41_WRNMASK         (0x0)
#define BPORT1_AB_LUT41_WIDTH           32
#define BPORT1_AB_LUT42_WRMASK          0xffffffff
#define BPORT1_AB_LUT42_WRNMASK         (0x0)
#define BPORT1_AB_LUT42_WIDTH           32
#define BPORT1_AB_LUT43_WRMASK          0xffffffff
#define BPORT1_AB_LUT43_WRNMASK         (0x0)
#define BPORT1_AB_LUT43_WIDTH           32
#define BPORT1_AB_LUT44_WRMASK          0xffffffff
#define BPORT1_AB_LUT44_WRNMASK         (0x0)
#define BPORT1_AB_LUT44_WIDTH           32
#define BPORT1_AB_LUT45_WRMASK          0xffffffff
#define BPORT1_AB_LUT45_WRNMASK         (0x0)
#define BPORT1_AB_LUT45_WIDTH           32
#define BPORT1_AB_LUT46_WRMASK          0xffffffff
#define BPORT1_AB_LUT46_WRNMASK         (0x0)
#define BPORT1_AB_LUT46_WIDTH           32
#define BPORT1_AB_LUT47_WRMASK          0xffffffff
#define BPORT1_AB_LUT47_WRNMASK         (0x0)
#define BPORT1_AB_LUT47_WIDTH           32
#define BPORT1_AB_LUT48_WRMASK          0xffffffff
#define BPORT1_AB_LUT48_WRNMASK         (0x0)
#define BPORT1_AB_LUT48_WIDTH           32
#define BPORT1_AB_LUT49_WRMASK          0xffffffff
#define BPORT1_AB_LUT49_WRNMASK         (0x0)
#define BPORT1_AB_LUT49_WIDTH           32
#define BPORT1_AB_LUT50_WRMASK          0xffffffff
#define BPORT1_AB_LUT50_WRNMASK         (0x0)
#define BPORT1_AB_LUT50_WIDTH           32
#define BPORT1_AB_LUT51_WRMASK          0xffffffff
#define BPORT1_AB_LUT51_WRNMASK         (0x0)
#define BPORT1_AB_LUT51_WIDTH           32
#define BPORT1_AB_LUT52_WRMASK          0xffffffff
#define BPORT1_AB_LUT52_WRNMASK         (0x0)
#define BPORT1_AB_LUT52_WIDTH           32
#define BPORT1_AB_LUT53_WRMASK          0xffffffff
#define BPORT1_AB_LUT53_WRNMASK         (0x0)
#define BPORT1_AB_LUT53_WIDTH           32
#define BPORT1_AB_LUT54_WRMASK          0xffffffff
#define BPORT1_AB_LUT54_WRNMASK         (0x0)
#define BPORT1_AB_LUT54_WIDTH           32
#define BPORT1_AB_LUT55_WRMASK          0xffffffff
#define BPORT1_AB_LUT55_WRNMASK         (0x0)
#define BPORT1_AB_LUT55_WIDTH           32
#define BPORT1_AB_LUT56_WRMASK          0xffffffff
#define BPORT1_AB_LUT56_WRNMASK         (0x0)
#define BPORT1_AB_LUT56_WIDTH           32
#define BPORT1_AB_LUT57_WRMASK          0xffffffff
#define BPORT1_AB_LUT57_WRNMASK         (0x0)
#define BPORT1_AB_LUT57_WIDTH           32
#define BPORT1_AB_LUT58_WRMASK          0xffffffff
#define BPORT1_AB_LUT58_WRNMASK         (0x0)
#define BPORT1_AB_LUT58_WIDTH           32
#define BPORT1_AB_LUT59_WRMASK          0xffffffff
#define BPORT1_AB_LUT59_WRNMASK         (0x0)
#define BPORT1_AB_LUT59_WIDTH           32
#define BPORT1_AB_LUT60_WRMASK          0xffffffff
#define BPORT1_AB_LUT60_WRNMASK         (0x0)
#define BPORT1_AB_LUT60_WIDTH           32
#define BPORT1_AB_LUT61_WRMASK          0xffffffff
#define BPORT1_AB_LUT61_WRNMASK         (0x0)
#define BPORT1_AB_LUT61_WIDTH           32
#define BPORT1_AB_LUT62_WRMASK          0xffffffff
#define BPORT1_AB_LUT62_WRNMASK         (0x0)
#define BPORT1_AB_LUT62_WIDTH           32
#define BPORT1_AB_LUT63_WRMASK          0xffffffff
#define BPORT1_AB_LUT63_WRNMASK         (0x0)
#define BPORT1_AB_LUT63_WIDTH           32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
