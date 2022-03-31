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


// VMI header files
#include "vmi/vmiRt.h"

// model header files
#include "or1kStructure.h"
#include "or1kFunctions.h"

//
// OR1K virtual memory initialisation
//
VMI_VMINIT_FN(or1kVMInit) {

    // for this example, the SUPERVISOR memory domain will be the physical
    // domain; the USER memory domain will be a derived virtual domain
    memDomainP physicalDomain   = codeDomains[0];
    memDomainP supervisorDomain = physicalDomain;
    memDomainP userDomain       = vmirtNewDomain("user", 32);

    // create an initial mapping that makes physical addresses 0x80000000:
    // 0x8fffffff visible at 0x00000000:0x0fffffff in the USER memory space
    vmirtAliasMemory(
        physicalDomain,
        userDomain,
        0x80000000,
        0x8fffffff,
        0x00000000,
        0
    );

    // remove write permissions from addresses 0x00000000:0x0fffffff in the
    // user address space
    vmirtProtectMemory(
        userDomain,
        0x00000000,
        0x0fffffff,
        MEM_PRIV_RX,
        MEM_PRIV_SET
    );

    // create an initial mapping that makes physical addresses 0x90000000:
    // 0x9fffffff visible at 0xf0000000:0xffffffff in the USER memory space
    vmirtAliasMemory(
        physicalDomain,
        userDomain,
        0x90000000,
        0x9fffffff,
        0xf0000000,
        0
    );

    // remove execute permissions from addresses 0xf0000000:0xffffffff in the
    // USER memory space
    vmirtProtectMemory(
        userDomain,
        0xf0000000,
        0xffffffff,
        MEM_PRIV_RW,
        MEM_PRIV_SET
    );

    // supervisorDomain should be used for both instruction and data in
    // SUPERVISOR mode
    codeDomains[OR1K_MODE_SUPERVISOR] = supervisorDomain;
    dataDomains[OR1K_MODE_SUPERVISOR] = supervisorDomain;

    // userDomain should be used for both instruction and data in USER mode
    codeDomains[OR1K_MODE_USER] = userDomain;
    dataDomains[OR1K_MODE_USER] = userDomain;
}
