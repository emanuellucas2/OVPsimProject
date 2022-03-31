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

#include "tlm.h"
#include "tlm/tlmModule.hpp"
#include "tlm/tlmDecoder.hpp"
#include "tlm/tlmMemory.hpp"
#include "ovpworld.org/processor/or1k/1.0/tlm/processor.igen.hpp"

using namespace sc_core;

class simple : public sc_module {

  public:
    simple (sc_module_name name);

    tlmModule             Platform;
    tlmDecoder            bus1;
    tlmRam                ram1;
    tlmRam                ram2;
    tlmRam                ram3;
    or1k                  cpu1;
    extension             or1kNewlib_0;

}; /* simple */

simple::simple (sc_module_name name)
    : sc_module (name)
    , Platform ("")
    , bus1(Platform, "bus1", 2, 3)
    , ram1 (Platform, "ram1", 0xfffff)
    , ram2 (Platform, "ram2", 0xffff)
    , ram3 (Platform, "ram3", 0xffff)
    , cpu1 ( Platform, "cpu1")
    , or1kNewlib_0(cpu1, opVLNVString (NULL, "ovpworld.org", "semihosting", "or1kNewlib", "1.0", OP_EXTENSION, OP_VLNV_FATAL), "or1kNewlib_0")
{

    // bus1 masters
    bus1.connect(cpu1.INSTRUCTION);
    bus1.connect(cpu1.DATA);

    // bus1 slaves
    bus1.connect(ram1.sp1,0x0, 0xfffff); // Memory (0)

    bus1.connect(ram2.sp1,0xffff0000, 0xffffffff); // Memory (1)

    bus1.connect(ram3.sp1,0xc0000000, 0xc000ffff); // Memory (2)

    sc_time q = sc_time(0.00001, SC_SEC);
    cpu1.quantum(q);
}

static Bool cmdParser(int argc, const char *argv[]) {
    optCmdParserP parser = opCmdParserNew("simple", OP_AC_EXT1);
    return opCmdParseArgs(parser, argc, argv);
}

class testHarness : public sc_core::sc_module {

  public:
    testHarness (sc_core::sc_module_name name);

    simple s1;

  private:
    // thread to drive pins.
    void harnessThread(void);

    sc_time delay;

}; /* testHarness */

SC_HAS_PROCESS(testHarness);

testHarness::testHarness (sc_core::sc_module_name name)
    : s1 ("s1")
    , delay  (0.00004, SC_SEC)
{
    SC_THREAD(harnessThread);
}

void testHarness::harnessThread(void) {

    cout << "Harness started" << endl;

    wait(delay);
    cout << "dmi off" << endl;
    s1.ram1.dmi(0);
    cout << "dmi on" << endl;
    s1.ram1.dmi(1);

    cout << "Harness finished" << endl;
}

////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int sc_main (int argc, char *argv[]) {
    session s;
    if(!cmdParser(argc, (const char **)argv)) {
        return 1;
    }

    testHarness top ("top");

    sc_start();
    return 0;
}

