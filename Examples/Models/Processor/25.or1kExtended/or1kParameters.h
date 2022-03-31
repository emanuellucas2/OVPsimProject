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


#ifndef OR1K_PARAMETERS_H
#define OR1K_PARAMETERS_H

// VMI header files
#include "vmi/vmiAttrs.h"
#include "vmi/vmiParameters.h"

//
// Define the attributes value structure
//
typedef struct or1kParamValuesS {

    VMI_BOOL_PARAM(verbose);
    VMI_UNS32_PARAM(extinterrupts);
    VMI_STRING_PARAM(extintlogfile);

} or1kParamValues, *or1kParamValuesP;

#endif
