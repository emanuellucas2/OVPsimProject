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

#include "tlm/tlmModule.hpp"
#include "tlm/tlmDecoder.hpp"
#include "tlm/tlmMemory.hpp"

// Processor configuration
#ifdef RISCV32
#include "riscv.ovpworld.org/processor/riscv/1.0/tlm/riscv_RV32I.igen.hpp"
#endif
#ifdef ARM7TDMI
#include "arm.ovpworld.org/processor/arm/1.0/tlm/arm_ARM7TDMI.igen.hpp"
#endif
#ifdef IMG_MIPS32R2
#include "mips.ovpworld.org/processor/mips32_r1r5/1.0/tlm/mips32_r1r5_4KEm.igen.hpp"
#endif

using namespace sc_core;

////////////////////////////////////////////////////////////////////////////////
//                      BareMetal Class                                       //
////////////////////////////////////////////////////////////////////////////////

class BareMetal : public sc_module {

  public:
    BareMetal (sc_module_name name);

    tlmModule             Platform;
    tlmDecoder            bus1;
    tlmRam                ram1;
#ifdef RISCV32
    riscv_RV32I           cpu1;
#endif
#ifdef ARM7TDMI
    arm_ARM7TDMI          cpu1;
#endif
#ifdef IMG_MIPS32R2
    mips32_r1r5_4KEm      cpu1;
#endif

  private:

    params paramsForcpu1() {
        params p;
        p.set("defaultsemihost", true);
        return p;
    }

}; /* BareMetal */

BareMetal::BareMetal (sc_module_name name)
    : sc_module (name)
    , Platform ("")
    , bus1 (Platform, "bus1", 2, 1)
    , ram1 (Platform, "ram1", 0xffffffff)
    , cpu1 ( Platform, "cpu1",  paramsForcpu1())
{
    bus1.connect(cpu1.INSTRUCTION);
    bus1.connect(cpu1.DATA);
    bus1.connect(ram1.sp1, 0x0, 0xffffffff);
}

int sc_main (int argc, char *argv[]) {

    // start the CpuManager session
    session s;

    // create a standard command parser and parse the command line
    parser  p(argc, (const char**) argv);

    // create an instance of the platform
    BareMetal top ("top");

    // start SystemC
    sc_start();
    return 0;
}

