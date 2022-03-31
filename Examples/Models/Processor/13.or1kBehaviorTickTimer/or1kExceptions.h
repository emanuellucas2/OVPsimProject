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

#ifndef OR1KEXCEPTIONS_H
#define OR1KEXCEPTIONS_H

// model header files
#include "or1kStructure.h"

//
// Ensure any pending interrupt is taken before the next instruction
//
void or1kInterruptNext(or1kP or1k);

//
// Return the TTCR register
//
Uns32 or1kGetTTCR(or1kP or1k);

//
// Set the TTCR register
//
void or1kSetTTCR(or1kP or1k, Uns32 TTCR);

//
// Set the TTMR register
//
void or1kSetTTMR(or1kP or1k, Uns32 TTMR);

#endif
