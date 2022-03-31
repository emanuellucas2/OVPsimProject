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

#ifndef OR1K_FUNCTIONS_H
#define OR1K_FUNCTIONS_H

// VMI header files
#include "vmi/vmiAttrs.h"

// constructor & destructor
VMI_CONSTRUCTOR_FN(or1kConstructor);
VMI_DESTRUCTOR_FN(or1kDestructor);

// morph function
VMI_MORPH_FN(or1kMorphInstruction);

// simulation support functions
VMI_ENDIAN_FN(or1kGetEndian);
VMI_NEXT_PC_FN(or1kNextInstruction);

// port functions
VMI_BUS_PORT_SPECS_FN(or1kGetBusPortSpec);

// Processor Info routine
VMI_PROC_INFO_FN(or1kProcInfo);

#endif

