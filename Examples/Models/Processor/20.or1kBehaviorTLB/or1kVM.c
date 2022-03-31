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
#include "vmi/vmiMessage.h"
#include "vmi/vmiRt.h"

// model header files
#include "or1kStructure.h"
#include "or1kFunctions.h"
#include "or1kVM.h"

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

    // save physicalDomain and userDomain on the OR1K structure for TLB usage
    or1kP or1k = (or1kP)processor;
    or1k->physicalDomain = physicalDomain;
    or1k->tlbDomain      = userDomain;
}

//
// Set TLB entry 'tlbIndex' with a mapping from va to pa
//
void or1kSetTLBEntry(or1kP or1k, Uns32 tlbIndex, Uns32 va, Uns32 pa) {

    // get the current instruction count (for messages)
    Uns64 iCount = vmirtGetICount((vmiProcessorP)or1k);

    // clip tlbIndex, va and pa to valid values
    tlbIndex &= (OR1K_TLB_SIZE-1);
    va       &= ~(OR1K_PAGE_SIZE-1);
    pa       &= ~(OR1K_PAGE_SIZE-1);

    // get the TLB entry to update and the memory domain affected
    tlbEntryP  entry          = &or1k->tlb[tlbIndex];
    memDomainP physicalDomain = or1k->physicalDomain;
    memDomainP tlbDomain      = or1k->tlbDomain;

    // if TLB entry is already mapped, unmap it
    if(entry->valid) {

        vmiPrintf(
            FMT_64u": DELETE entry %u mapping (va:0x%08x pa:0x%08x)\n",
            iCount, tlbIndex, entry->va, entry->pa
        );

        vmirtUnaliasMemoryVM(
            tlbDomain, entry->va, entry->va+OR1K_PAGE_SIZE-1, True, 0
        );
    }

    // update the TLB entry
    entry->va    = va;
    entry->pa    = pa;
    entry->valid = True;

    vmiPrintf(
        FMT_64u": CREATE entry %u mapping (va:0x%08x pa:0x%08x)\n",
        iCount, tlbIndex, va, pa
    );

    // establish the new page mapping with read/write permissions
    vmirtAliasMemoryVM(
        physicalDomain, tlbDomain, pa, pa+OR1K_PAGE_SIZE-1, va, 0,
        MEM_PRIV_RW, True, 0
    );
}


