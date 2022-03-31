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

#ifndef OR1KMORPH_H
#define OR1KMORPH_H

// VMI header files
#include "vmi/vmiCxt.h"

// model header files
#include "or1kDecode.h"

// Handle movhi instruction
OR1K_DISPATCH_FN(or1kMorphMOVHI);

//
// Handle arithmetic instructions (second argument constant)
//
OR1K_DISPATCH_FN(or1kMorphADDI);
OR1K_DISPATCH_FN(or1kMorphADDIC);
OR1K_DISPATCH_FN(or1kMorphANDI);
OR1K_DISPATCH_FN(or1kMorphORI);
OR1K_DISPATCH_FN(or1kMorphXORI);
OR1K_DISPATCH_FN(or1kMorphMULI);

//
// Handle arithmetic instructions (second argument register)
//
OR1K_DISPATCH_FN(or1kMorphADD);
OR1K_DISPATCH_FN(or1kMorphADDC);
OR1K_DISPATCH_FN(or1kMorphSUB);
OR1K_DISPATCH_FN(or1kMorphAND);
OR1K_DISPATCH_FN(or1kMorphOR);
OR1K_DISPATCH_FN(or1kMorphXOR);
OR1K_DISPATCH_FN(or1kMorphMUL);
OR1K_DISPATCH_FN(or1kMorphDIV);
OR1K_DISPATCH_FN(or1kMorphDIVU);

//
// Handle shift/rotate instructions (second argument constant)
//
OR1K_DISPATCH_FN(or1kMorphSLLI);
OR1K_DISPATCH_FN(or1kMorphSRLI);
OR1K_DISPATCH_FN(or1kMorphSRAI);
OR1K_DISPATCH_FN(or1kMorphRORI);

//
// Handle shift/rotate instructions (second argument register)
//
OR1K_DISPATCH_FN(or1kMorphSLL);
OR1K_DISPATCH_FN(or1kMorphSRL);
OR1K_DISPATCH_FN(or1kMorphSRA);
OR1K_DISPATCH_FN(or1kMorphROR);

//
// Handle branch instructions
//
OR1K_DISPATCH_FN(or1kMorphBF);
OR1K_DISPATCH_FN(or1kMorphBNF);
OR1K_DISPATCH_FN(or1kMorphJ);
OR1K_DISPATCH_FN(or1kMorphJR);
OR1K_DISPATCH_FN(or1kMorphJAL);
OR1K_DISPATCH_FN(or1kMorphJALR);

//
// Handle sys and rfe instructions
//
OR1K_DISPATCH_FN(or1kMorphSYS);
OR1K_DISPATCH_FN(or1kMorphRFE);

//
// Handle mtspr and mfspr instructions
//
OR1K_DISPATCH_FN(or1kMorphMTSPR);
OR1K_DISPATCH_FN(or1kMorphMFSPR);

//
// Handle load instructions
//
OR1K_DISPATCH_FN(or1kMorphLWZ);
OR1K_DISPATCH_FN(or1kMorphLWS);
OR1K_DISPATCH_FN(or1kMorphLBZ);
OR1K_DISPATCH_FN(or1kMorphLBS);
OR1K_DISPATCH_FN(or1kMorphLHZ);
OR1K_DISPATCH_FN(or1kMorphLHS);

//
// Handle store instructions
//
OR1K_DISPATCH_FN(or1kMorphSW);
OR1K_DISPATCH_FN(or1kMorphSB);
OR1K_DISPATCH_FN(or1kMorphSH);

//
// Handle comparison instructions
//
OR1K_DISPATCH_FN(or1kMorphSF);
OR1K_DISPATCH_FN(or1kMorphSFI);

//
// NOP morpher callback
//
OR1K_DISPATCH_FN(or1kMorphNOP);

//
// Default morpher callback
//
OR1K_DISPATCH_FN(or1kMorphDefault);

#endif

