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

#include "vmi/vmiPSETypes.h"
#include "vmi/vmiTyperefs.h"


////////////////////////////////////////////////////////////////////////////////
// PSE INTERCEPT LIBRARY SUPPORT ROUTINES
////////////////////////////////////////////////////////////////////////////////

//
// Write a value to a net
//
void vmipseWriteNet(vmipseNetHandle handle, Uns64 value);

//
// Immediately trigger an event, restarting any threads waiting for it
//
Bool vmipseTriggerEvent(vmipseEventHandle handle);

//
// Access attributes of the named platform port, returning the domain associated
// with the port (or NULL if no port of that name was found). Further attributes
// of the port are returned in byref arguments:
// lowAddr      : the low port address
// highAddr     : the high port address
// isMasterPort : whether the port is a master port
// isDynamicPort: whether the (slave)port is re-mappable
//
memDomainP vmipsePlatformPortAttributes(
    vmiProcessorP pse,
    const char   *name,
    Addr         *lowAddr,
    Addr         *highAddr,
    Bool         *isMasterPort,
    Bool         *isDynamicPort
);

//
// Map the simulated address range on the localDomain
// to the domain connected to this port.
//
void vmipseAliasMemory(
    memDomainP localDomain,
    const char *portName,
    Addr       lowAddr,
    Addr       highAddr
);

