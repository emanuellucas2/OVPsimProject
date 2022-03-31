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

#ifndef OR1KUTILS_H
#define OR1KUTILS_H

// model header files
#include "or1kFunctions.h"
#include "or1kStructure.h"

//
// Return the current value of the SR register
//
Uns32 or1kGetSR(or1kP or1k);

//
// Set the current value of the SR register
//
void or1kSetSR(or1kP or1k, Uns32 value);

#endif
