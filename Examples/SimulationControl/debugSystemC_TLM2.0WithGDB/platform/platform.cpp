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
#include "tlm/tlmProcessor.hpp"

using namespace sc_core;
using namespace cw;

class TLM2Platform : public sc_core::sc_module {

  public:
    TLM2Platform (sc_core::sc_module_name name);

    tlmModule        Platform;
    tlmDecoder       bus1;
    tlmRam           ram1;
    tlmRam           ram2;
    tlmProcessor     cpu1;
    extension        semihostlib;

  private:
    params platformParams() {
        params p;
        p.set("gdbconsole", (bool)1);
        return p;
    }

    const char *pathForcpu1(void) {
        return opVLNVString(0, "ovpworld.org", "processor", "or1k", "1.0", OP_PROCESSOR, OP_VLNV_FATAL);
    }

}; /* TLM2Platform */

////////////////////////////////////////////////////////////////////////////////
//                          TLM2Platform Constructor                         //
////////////////////////////////////////////////////////////////////////////////

TLM2Platform::TLM2Platform ( sc_core::sc_module_name name)
    : sc_module (name)
    , Platform ("", platformParams())
    , bus1     (Platform, "bus1", 2, 2)
    , ram1     (Platform, "ram1", 0x000FFFFF)
    , ram2     (Platform, "ram2", 0x0000FFFF)
    , cpu1     (Platform, pathForcpu1(), "cpu1")
    , semihostlib (cpu1, opVLNVString (NULL, "ovpworld.org", "semihosting", "or1kNewlib", "1.0", OP_EXTENSION, OP_VLNV_FATAL), "semihostlib")
{

    // bus1 masters
    bus1.connect(cpu1, "INSTRUCTION", 32);
    bus1.connect(cpu1, "DATA",        32);

    // bus1 slaves
    bus1.connect(ram1.sp1,0x00000000, 0x000fffff); // Memory
    bus1.connect(ram2.sp1,0xffff0000, 0xffffffff); // Memory
}

int sc_main (int argc, char *argv[] )
{
    session s;

    const char *app = "application.elf";

    sc_time stop(0,SC_MS);

    if (argc > 1 && argc <= 3) {
        app = argv[1];
    } else {
        cout << "Usage: " << argv[0] << " <application> [stop time]" << endl;
        cout << "     :   stop time is in milliseconds" << endl;
        return 0;
    }

    // Ignore some of the Warning messages
    opMessageDisable ("OP_NPF");

    TLM2Platform top("top");             // instantiate example top module

    // Use the TLM code memory. It needs to be loaded with the program.
    top.cpu1.applicationLoad(app, (optLoaderControls)(OP_LDR_VERBOSE | OP_LDR_SET_START), 0);

    // Specify the debug processor.
    top.cpu1.debug();

    if (argc > 2) {
        stop = sc_time(atoi(argv[2]), SC_MS);

        sc_start(stop);                  // start the simulation
    } else {
        sc_start();                      // start the simulation
    }

    cout << "Finished sc_main." << endl;
    return 0;                             // return okay status
}
