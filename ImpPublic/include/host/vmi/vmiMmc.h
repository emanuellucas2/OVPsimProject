/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License Agreement
 * that you accepted before downloading this file.
 *
 * This header forms part of the Software but may be included and used unaltered
 * in derivative works.
 *
 * For more information, please visit www.OVPworld.org or www.imperas.com
 */

#pragma once

// VMI area includes
#include "vmi/vmiCommand.h"
#include "vmi/vmiTypes.h"


//
// Return the component name
//
const char *vmimmcGetName(vmimmcComponentP component);

//
// Return the component full hierarchical name
//
const char *vmimmcGetHierarchicalName(vmimmcComponentP component);

//
// Get the next slave port connected to the named component output port (for
// TRANSPARENT MMC models)
//
vmimmcPortP vmimmcGetNextPort(vmimmcComponentP component, const char *portName);

//
// Get the domain for the named component output port (for FULL MMC models)
//
memDomainP vmimmcGetNextDomain(vmimmcComponentP component, const char *portName);

//
// Return attributes for a port
//
vmimmcAttrCP vmimmcGetPortAttrs(vmimmcPortP port);

//
// Refresh a subsequent transparent MMC model
//
void vmimmcRefreshTransparent(vmimmcPortP nextPort, vmiIASRunState state);

//
// Refresh a subsequent full MMC model
//
void vmimmcRefreshFull(memDomainP nextDomain, vmiIASRunState state);

//
// Add a command for the passed component
//
vmiCommandP vmimmcAddCommand(
    vmimmcComponentP component,
    const char      *name,
    const char      *exampleArguments,
    vmimmcCommandFn  commandCB,
    vmiCommandAttrs  attrs
);

//
// Add a command with command parser for the passed component
// Do not use this function.
//
vmiCommandP vmimmcAddCommandParse(
    vmimmcComponentP     component,
    const char          *name,
    const char          *exampleArguments,
    vmimmcCommandParseFn commandCB,
    vmiCommandAttrs      attrs
);

