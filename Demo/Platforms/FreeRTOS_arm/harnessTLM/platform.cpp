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

////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                             Version 20211118.0
//
////////////////////////////////////////////////////////////////////////////////

// This file declares sc_main and functions to be implemented by the user.
// This file will not be overwritten by subsequent igen runs
// unless --overwrite is specified.
// To conditionally set model attributes, use
// opOverride("instance-path", "<value>");

#include "tlm.h"
#include "tlm/tlmModule.hpp"
extern "C" {
#include "platform.sc_options.igen.h"
}
#include "platform.sc_constructor.igen.h"

////////////////////////////////////////////////////////////////////////////////
//                         U S E R   F U N C T I O N S
////////////////////////////////////////////////////////////////////////////////

static Bool postCmdParser(void) {
    // postCmdParser code goes here
    return True;
}


#include "platform.sc_clp.igen.h"

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int sc_main (int argc, char *argv[]) {
    session s;
    if(!cmdParser(argc, (const char **)argv)) {
        return 1;
    }
    if(!postCmdParser())  {
        return 1;
    }
    ArmCortexMFreeRTOS ArmCortexMFreeRTOS ("ArmCortexMFreeRTOS");

    sc_start();
    return 0;
}

