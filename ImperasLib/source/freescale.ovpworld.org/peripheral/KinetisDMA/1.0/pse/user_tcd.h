/*
 * Copyright (c) 2011-2014 Posedge Software Inc., www.posedgesoft.com
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

#ifndef USER_TCD_H
#define USER_TCD_H

typedef struct dma_8bit_regs
{
    union { 
        Uns8 value;
        struct {
            unsigned SERQ : 5;
            unsigned __pad5 : 1;
            unsigned SAER : 1;
            unsigned NOP : 1;
        } bits;
    } DMA_SERQ;
    union {
        Uns8 value;
        struct {
            unsigned CERQ : 5;
            unsigned __pad13 : 1;
            unsigned CAER : 1;
            unsigned NOP : 1;
        } bits;
    } DMA_CERQ;
    union {
        Uns8 value;
        struct {
            unsigned SEEI : 5;
            unsigned __pad21 : 1;
            unsigned SAEE : 1;
            unsigned NOP : 1;
        } bits;
    } DMA_SEEI;
    union {
        Uns8 value;
        struct {
            unsigned CEEI : 5;
            unsigned __pad29 : 1;
            unsigned CAEE : 1;
            unsigned NOP : 1;
        } bits;
    } DMA_CEEI;
    union { 
        Uns8 value;
        struct {
            unsigned CINT : 5;
            unsigned __pad5 : 1;
            unsigned CAIR : 1;
            unsigned NOP : 1;
        } bits;
    } DMA_CINT;
    union {
        Uns8 value;
        struct {
            unsigned CERR : 5;
            unsigned __pad13 : 1;
            unsigned CAEI : 1;
            unsigned NOP : 1;
        } bits;
    } DMA_CERR;
    union {
        Uns8 value;
        struct {
            unsigned SSRT : 5;
            unsigned __pad21 : 1;
            unsigned SAST : 1;
            unsigned NOP : 1;
        } bits;
    } DMA_SSRT;
    union {
        Uns8 value;
        struct {    
            unsigned CDNE : 5;
            unsigned __pad29 : 1;
            unsigned CADN : 1;
            unsigned NOP : 1;
        } bits;
    } DMA_CDNE;
} dma_8bit_regsT, *dma_8bit_regsP;

typedef struct dma_tcd
{
    // Map this dma_tcd block to correct dmaIntterupt.
    ppmNetHandle    dmaInterrupt;

    // Channel Priority Register.
    union {
        Uns8 value;
        struct {
            unsigned CHPRI: 4;
            unsigned GRPPPRI: 2;
            unsigned DPA: 1;
            unsigned ECP: 1;
        } bits;
    } DMA_DCHPRI;

    // TCD Registers.
    union { 
        Uns32 value;
        struct {
            unsigned SADDR : 32;
        } bits;
    } TCD_SADDR;
    union { 
        Uns16 value;
        struct {
            unsigned SOFF : 16;
        } bits;
    } TCD_SOFF;
    union { 
        Uns16 value;
        struct {
            unsigned DSIZE : 3;
            unsigned DMOD : 5;
            unsigned SSIZE : 3;
            unsigned SMOD : 5;
        } bits;
    } TCD_ATTR;
    union { 
        Uns32 value;
        union {
            struct {
                unsigned NBYTES : 32;
            } MLNO;
            struct {
                unsigned NBYTES : 30;
                unsigned DMLOE : 1;
                unsigned SMLOE : 1;
            } MLOFFNO;
            struct {
                unsigned NBYTES : 10;
                unsigned MLOFF : 20;
                unsigned DMLOE : 1;
                unsigned SMLOE : 1;
            } MLOFFYES;
        } bits;
    } TCD_NBYTES;
    union { 
        Uns32 value;
        struct {
            unsigned SLAST : 32;
        } bits;
    } TCD_SLAST;
    union { 
        Uns32 value;
        struct {
            unsigned DADDR : 32;
        } bits;
    } TCD_DADDR;
    union { 
        Uns16 value;
        struct {
            unsigned DOFF : 16;
        } bits;
    } TCD_DOFF;
    union { 
        Uns16 value;
        union {
            struct {
                unsigned CITER : 15;
                unsigned ELINK : 1;
            } ELINKNO;
            struct {
                unsigned CITER : 9;
                unsigned LINKCH : 5;
                unsigned DUMMY : 1;
                unsigned ELINK : 1;
            } ELINKYES;
        } bits;
    } TCD_CITER;
    union { 
        Uns32 value;
        struct {
            unsigned DLASTSGA : 32;
        } bits;
    } TCD_DLASTSGA;
    union { 
        Uns16 value;
        union {
            struct {
                unsigned BITER : 15;
                unsigned ELINK : 1;
            } ELINK_NO;
            struct {
                unsigned BITER : 9;
                unsigned LINKCH : 5;
                unsigned DUMMY: 1;
                unsigned ELINK : 1;
            } ELINK_YES;
        } bits;
    } TCD_BITER;
    union { 
        Uns16 value;
        struct {
            unsigned START : 1;
            unsigned INTMAJOR : 1;
            unsigned INTHALF : 1;
            unsigned DREQ : 1;
            unsigned ESG : 1;
            unsigned MAJORELINK : 1;
            unsigned ACTIVE : 1;
            unsigned DONE : 1;
            unsigned MAJORLINKCH : 5;
            unsigned DUMMY : 1;
            unsigned BWC : 2;
        } bits;
    } TCD_CSR;
} dma_tcdT, *dma_tcdP;


#endif // USER_TCD_H
