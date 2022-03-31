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

#ifndef OR1KEXCEPTIONTYPES_H
#define OR1KEXCEPTIONTYPES_H

//
// Exception types
//
typedef enum or1kExceptionE {
    OR1K_EXCPT_RST,         // reset
    OR1K_EXCPT_BUS,         // alignment
    OR1K_EXCPT_DPF,         // data privilege
    OR1K_EXCPT_IPF,         // instruction privilege
    OR1K_EXCPT_TTI,         // tick timer
    OR1K_EXCPT_ILL,         // illegal instruction
    OR1K_EXCPT_EXI,         // external interrupt
    OR1K_EXCPT_SYS,         // system call
    OR1K_EXCPT_LAST         // KEEP LAST: for sizing
} or1kException;

//
// Exception vector addresses
//
#define RST_ADDRESS 0x100   // reset exception vector
#define BUS_ADDRESS 0x200   // alignment exception vector
#define DPF_ADDRESS 0x300   // data privilege exception vector
#define IPF_ADDRESS 0x400   // instruction privilege exception vector
#define TTI_ADDRESS 0x500   // tick timer exception vector
#define ILL_ADDRESS 0x700   // illegal instruction exception vector
#define EXI_ADDRESS 0x800   // external interrupt exception vector
#define SYS_ADDRESS 0xc00   // sys exception vector

#endif
