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

#include "op/op.h"

static OP_CONSTRUCT_FN(moduleConstruct) {

    optBusP bus1 = opBusNew(mi, "bus1", 32, 0, 0);

    optParamP  prParams =  opParamStringSet(0, "variant", "RV32I");
    prParams = opParamBoolSet(prParams, "defaultsemihost", 1);
    const char  *prpath   = opVLNVString(0, "riscv.ovpworld.org" , "processor", "riscv", "1.0", OP_PROCESSOR, OP_VLNV_FATAL);
    opProcessorNew (mi, prpath, "proc1",  OP_PROC_STD_BUS(bus1), prParams);

    const char  *p1path = "peripheral/pse.pse";

    opPeripheralNew(mi, p1path, "per1",
        OP_CONNECTIONS(
             OP_BUS_CONNECTIONS(
                 OP_BUS_CONNECT(bus1, "BS1", 0x80000000, 0x80000001, 1)
             )
        ),
        0
    );

    opMemoryNew(mi, "code", OP_PRIV_RWX, 0x7fffffff,
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1, "sp1", 0x00000000, 0x7fffffff, 1)
            )
        ),
        0
     );
     opMemoryNew(mi, "data", OP_PRIV_RWX, 0x0fffffff,
        OP_CONNECTIONS(
            OP_BUS_CONNECTIONS(
                OP_BUS_CONNECT(bus1, "sp1", 0xF0000000, 0xffffffff, 1)
            )
        ),
        0
     );
}

optModuleAttr modelAttrs = {
    .versionString  = OP_VERSION,
    .type           = OP_MODULE,
    .name           = "module1",
    .constructCB    = moduleConstruct
};

int main(int argc, const char *argv[]) {

    return 0;
}


