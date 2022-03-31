/*
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


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                           Imperas/OVP Generated
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "op/op.h"
#include "ocl/oclhttp.h"

#define MODULE_NAME "zc706"

#include "httpConfig.c.h"

// forward declaration of component constructor
static OP_CONSTRUCT_FN(instantiateComponents);

static OP_CONSTRUCT_FN(moduleConstructor) {

    // instantiate module components
    instantiateComponents(mi, object);

    // insert constructor code here
}

#define ZYNQ_PS "Zynq/Zynq_PS"
#define ZYNQ_PL "Zynq/Zynq_PL"


static OP_PRE_SIMULATE_FN(modulePreSimulate) {
    Uns32 httpvisportnum  = opObjectParamUns32Value (mi,   "httpvisportnum" , 0);
    octHTTPMethods m = { get, post, object };
    opModuleHTTPOpen(mi, &m, httpvisportnum, "httpviszc706");

    object->mi = mi;

    if(object->diag)
        opMessage("I", MODULE_NAME, "%s diag level=%u", opObjectHierName(mi), object->diag);

    object->mps = opObjectByName(mi, ZYNQ_PS, OP_MODULE_EN).Module;
    if(!object->mps)
        opMessage("E", MODULE_NAME, "Did not find module '%s'", ZYNQ_PS);
    object->mpl = opObjectByName(mi, ZYNQ_PL, OP_MODULE_EN).Module;
    if(!object->mpl)
        opMessage("E", MODULE_NAME, "Did not find module '%s'", ZYNQ_PL);

    // get configfile parameter and set SW and LED visualization
    const char *configfile;
    configfile = opObjectParamStringValue((optObjectP) mi, "configfile");
    if(configfile) {
        // The LEDs and Switches may be using PS or PL
        configFileRead (object, configfile);
    }
}

static OP_SIMULATE_STARTING_FN(moduleSimulateStart) {
    // insert simulation starting code here
}

static OP_POST_SIMULATE_FN(modulePostSimulate) {
    // insert post simulation code here
}

static OP_DESTRUCT_FN(moduleDestruct) {
    // insert destructor code here
}

static OP_DIAG_SET_FN(moduleDiagSet) {
    object->diag = level;
}

#include "module.igen.h"
