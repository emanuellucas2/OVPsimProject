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

#ifndef OR1K_STRUCTURE_H
#define OR1K_STRUCTURE_H

// VMI header files
#include "hostapi/impTypes.h"

// prefix string (for error messages)
#define CPU_PREFIX "OR1K"

#define OR1K_REGS 32            // basic OR1K registers
#define OR1K_BITS 32            // register size in bits

// processor structure
typedef struct or1kS {
    Uns32       regs[OR1K_REGS];    // basic registers
    vmiBusPortP busPorts;           // bus port descriptions
} or1k, *or1kP;

// macros to specify target registers in VARIABLE expressions
#define OR1K_CPU_REG(_F)        VMI_CPU_REG(or1kP, _F)
#define OR1K_REG(_R)            OR1K_CPU_REG(regs[_R])

#endif

