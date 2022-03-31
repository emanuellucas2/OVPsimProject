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

#ifndef OR1KDISASSEMBLE_H
#define OR1KDISASSEMBLE_H

// VMI header files
#include "vmi/vmiCxt.h"

// model header files
#include "or1kDecode.h"

// Handle movhi instruction
OR1K_DISPATCH_FN(or1kDisMOVHI);

//
// Handle arithmetic instructions (second argument constant)
//
OR1K_DISPATCH_FN(or1kDisADDI);
OR1K_DISPATCH_FN(or1kDisADDIC);
OR1K_DISPATCH_FN(or1kDisANDI);
OR1K_DISPATCH_FN(or1kDisORI);
OR1K_DISPATCH_FN(or1kDisXORI);
OR1K_DISPATCH_FN(or1kDisMULI);

//
// Handle arithmetic instructions (second argument register)
//
OR1K_DISPATCH_FN(or1kDisADD);
OR1K_DISPATCH_FN(or1kDisADDC);
OR1K_DISPATCH_FN(or1kDisSUB);
OR1K_DISPATCH_FN(or1kDisAND);
OR1K_DISPATCH_FN(or1kDisOR);
OR1K_DISPATCH_FN(or1kDisXOR);
OR1K_DISPATCH_FN(or1kDisMUL);
OR1K_DISPATCH_FN(or1kDisDIV);
OR1K_DISPATCH_FN(or1kDisDIVU);

//
// Handle shift/rotate instructions (second argument constant)
//
OR1K_DISPATCH_FN(or1kDisSLLI);
OR1K_DISPATCH_FN(or1kDisSRLI);
OR1K_DISPATCH_FN(or1kDisSRAI);
OR1K_DISPATCH_FN(or1kDisRORI);

//
// Handle shift/rotate instructions (second argument register)
//
OR1K_DISPATCH_FN(or1kDisSLL);
OR1K_DISPATCH_FN(or1kDisSRL);
OR1K_DISPATCH_FN(or1kDisSRA);
OR1K_DISPATCH_FN(or1kDisROR);

//
// Handle branch instructions
//
OR1K_DISPATCH_FN(or1kDisBF);
OR1K_DISPATCH_FN(or1kDisBNF);
OR1K_DISPATCH_FN(or1kDisJ);
OR1K_DISPATCH_FN(or1kDisJR);
OR1K_DISPATCH_FN(or1kDisJAL);
OR1K_DISPATCH_FN(or1kDisJALR);

//
// Handle sys and rfe instructions
//
OR1K_DISPATCH_FN(or1kDisSYS);
OR1K_DISPATCH_FN(or1kDisRFE);

//
// Handle mtspr and mfspr instructions
//
OR1K_DISPATCH_FN(or1kDisMTSPR);
OR1K_DISPATCH_FN(or1kDisMFSPR);

//
// Handle load instructions
//
OR1K_DISPATCH_FN(or1kDisLWZ);
OR1K_DISPATCH_FN(or1kDisLWS);
OR1K_DISPATCH_FN(or1kDisLBZ);
OR1K_DISPATCH_FN(or1kDisLBS);
OR1K_DISPATCH_FN(or1kDisLHZ);
OR1K_DISPATCH_FN(or1kDisLHS);

//
// Handle store instructions
//
OR1K_DISPATCH_FN(or1kDisSW);
OR1K_DISPATCH_FN(or1kDisSB);
OR1K_DISPATCH_FN(or1kDisSH);

//
// Handle comparison instructions
//
OR1K_DISPATCH_FN(or1kDisSF);
OR1K_DISPATCH_FN(or1kDisSFI);

//
// Handle nop instruction
//
OR1K_DISPATCH_FN(or1kDisNOP);

//
// Default disassembler callback
//
OR1K_DISPATCH_FN(or1kDisDefault);

#endif

