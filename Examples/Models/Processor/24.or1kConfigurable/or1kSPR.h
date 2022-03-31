/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */

#ifndef OR1KSPR_H
#define OR1KSPR_H

// SPR groups
#define SPR_SYS     0x0
#define SPR_DMMU    0x1
#define SPR_IMMU    0x2
#define SPR_DC      0x3
#define SPR_IC      0x4
#define SPR_MAC     0x5
#define SPR_D       0x6
#define SPR_PC      0x7
#define SPR_PM      0x8
#define SPR_PIC     0x9
#define SPR_TT      0xA
#define SPR_FPU     0xB

// SPR SYS offsets
#define SYS_VR      0x00
#define SYS_UPR     0x01
#define SYS_SR      0x11
#define SYS_EPC     0x20
#define SYS_EEAR    0x30
#define SYS_ESR     0x40

// SPR DC offsets
#define DC_CR       0x0
#define DC_BPR      0x1
#define DC_BFR      0x2
#define DC_BIR      0x3
#define DC_BWR      0x4
#define DC_BLR      0x5

// SPR IC offsets
#define IC_CR       0x0
#define IC_BPR      0x1
#define IC_BIR      0x2
#define IC_BLR      0x3

// SPR Programmable Interrupt Controller offsets
#define PIC_MASK    0x0
#define PIC_STAT    0x2

// SPR Tick Timer offsets
#define TT_MR       0x000
#define TT_CR       0x100

#define SPR_OFF(_G,_R)  ((_G) << 11 | _R)

#endif
