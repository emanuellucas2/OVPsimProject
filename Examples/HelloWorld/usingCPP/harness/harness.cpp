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

#include <iostream>
using namespace std;

#include "op/op.hpp"
using namespace op;

#include "riscv_generic.hpp"

class top : public module {

    private:

        params paramsForRoot(void) {
            params p;
            p.set("verbose", true);
            return p;
        }

        params paramsForCpu(void) {
            params p;
            p.set("defaultsemihost", true);
            return p;
        }

    public:
        riscv         cpu;
        memory        mem;
        bus           bs;

        top(const char *name="top")
          : module(name,            paramsForRoot())
          , cpu  (*this,  "cpu",    paramsForCpu())
          , mem  (*this,  "mem",    0xffffffff)
          , bs   (*this,  "bs",     32)
        {
            bs.connect(cpu, "INSTRUCTION");
            bs.connect(cpu, "DATA");
            bs.connect(mem, "sp1", 0, 0xffffffff);
            cpu.applicationLoad("application/application.RISCV32.elf", OP_LDR_SET_START|OP_LDR_FAIL_IS_ERROR);
        }
};


int main(int argc, const char *argv[]) {

    // OP session control
    session    ses;

    // OP standard command line parser
    parser     par(argc, argv);

    top        t;
    t.simulate();
}
