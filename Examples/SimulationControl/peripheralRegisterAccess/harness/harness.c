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


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "op/op.h"

int main(int argc, const char *argv[]) {
    opSessionInit(OP_VERSION);

    opCmdParseStd(argv[0], OP_AC_ALL, argc, argv);

    optModuleP mr = opRootModuleNew(0, "top", 0);

    optModuleP mi = opModuleNew(
        mr,                 // parent module
        "module",           // modelfile
        "m1",               // name
        0,
        0
    );

    opRootModulePreSimulate(mr);

    // get the handle for the processor in the module
    optPeripheralP uart1 = opObjectByName(mi, "uart1", OP_PERIPHERAL_EN).Peripheral;

    if(uart1) {
        optBusPortP busPort = opObjectByName(uart1, "bport1", OP_BUSPORT_EN).BusPort;
#ifdef REPORT_ALL_REGISTERS
        optMMRegisterP reg;
        while((reg = opBusPortMMRegisterNext(busPort, reg))) {
            opMessage("I", "HAR_BP", "Found register %s\n", opObjectName(reg));
        }
#endif
        optMMRegisterP msr = opObjectByName(busPort, "ab_msr", OP_MMREGISTER_EN).MMRegister;
        if(msr) {

            // This is how to view a peripiheral register without changing the state of the peripheral
            Uns8 v = 0;
            opMMRegisterView(msr, &v);
            opMessage("I", "HAR_RV", "ab_msr value=0x%x", v);

            v = 0xff;
            opMessage("I", "HAR_WR", "writing ab_msr value=0x%x", v);

            // This is how to write to a peripheral register.
            // Note that this will possibly change the state of the peripheral.
            // The same effect can be achieved in OP by writing to the correct address on the appropriate bus.
            opMMRegisterWrite(msr, &v);

            // This is how to view to a peripheral register.
            // Note that if the peripheral register has a view function, or it otherwise correctly designed,
            // this should not affect the state of the peripheral.
            opMMRegisterView(msr, &v);
            opMessage("I", "HAR_RV", "ab_msr VIEW value=0x%x", v);
        } else {
            opMessage("E", "HAR_NR", "Found no register called ab_msr");
        }

        optMMRegisterP iir = opObjectByName(busPort, "ab_iir", OP_MMREGISTER_EN).MMRegister;
        if(iir) {
            Uns8 v = 0;
            // This is how to read to a peripheral register.
            // Note that this will possibly change the state of the peripheral.
            opMMRegisterRead(iir, &v);
            opMessage("I", "HAR_RD", "ab_iir READ value=0x%x", v);
            opMMRegisterView(iir, &v);
            opMessage("I", "HAR_RV", "ab_iir READ value=0x%x", v);
        }

    } else {
        opMessage("E", "HAR_NP", "Found no peripheral called uart1");
    }
    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

