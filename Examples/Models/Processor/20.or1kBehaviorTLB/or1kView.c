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



void or1kCreateView(or1kP or1k) {

    // get the base processor view object
    vmiProcessorP  processor       = (vmiProcessorP)or1k;
    vmiViewObjectP processorObject = vmirtGetProcessorViewObject(processor);

    // add new view object
    or1k->exObject  = vmirtAddViewObject(
        processorObject, "addressException", "Address exception"
    );

    // Create an event to be generated on an address exception
    or1k->addrExEvent = vmirtAddViewEvent(
        or1k->exObject, "address", "Address exception event trigger"
    );

    // Create an object to access the EEAR
    vmiViewObjectP eearObject = vmirtAddViewObject(or1k->exObject, "eear", "");
    vmirtSetViewObjectRefValue(eearObject, VMI_VVT_UNS32, &or1k->EEAR);

    // Create an object to access the EPC
    vmiViewObjectP epcObject = vmirtAddViewObject(or1k->exObject, "epc", "");
    vmirtSetViewObjectRefValue(epcObject, VMI_VVT_UNS32, &or1k->EPC);

    // Create an object to access the ESR
    vmiViewObjectP esrObject = vmirtAddViewObject(or1k->exObject, "esr", "");
    vmirtSetViewObjectRefValue(esrObject, VMI_VVT_UNS32, &or1k->ESR);
}
