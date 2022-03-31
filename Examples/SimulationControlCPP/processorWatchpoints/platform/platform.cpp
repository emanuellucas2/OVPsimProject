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

class myWatchpoint : public watchpoint {

  public:
    myWatchpoint(processor &p, const char *label, optWatchpointType type);
    myWatchpoint(processor &p, const char *label, reg &r);
    ~myWatchpoint() { }
  private:
    bool triggered();
    const char *label;
    message   m;
};


bool myWatchpoint::triggered() {
    m.print("I", "MWP",  "Triggered %s\n", label);
    return 1;
}

myWatchpoint::myWatchpoint (processor &parent, const char *l, optWatchpointType type)
    : watchpoint(parent, type)
    , label(l) {
}

myWatchpoint::myWatchpoint (processor &parent, const char *l, reg &r)
    : watchpoint(parent, OP_RWP_CHANGE, r)
    , label(l) {
}

class simplePlatform {

  private:
    Addr      maxAddress;
    session   s;
    parser    p;

    params paramsForP1(void) {
        params p;
        p.set("defaultsemihost", (bool)1);
        p.set("simulateexceptions", (bool)1);
        return p;
    }

  public:
    message   m;
    module    root;
    vlnv      v;
    processor p1;
    memory    m1;
    bus       b1;
    net       rs;

    myWatchpoint *we, *wm, *wr;

    simplePlatform(int argc, const char *argv[]);
};

simplePlatform::simplePlatform(int argc, const char *argv[])
   : maxAddress(0xffffffff)
   , p(argc, argv)
   , p1(root, v.string( "ovpworld.org", "processor", "or1k", "1.0", OP_PROCESSOR), "p1", paramsForP1() )
   , m1(root,"m1", maxAddress, OP_PRIV_RWX)
   , b1(root, "b1", 32)
   , rs(root, "rs")
{
    b1.connect(p1,"DATA");
    b1.connect(p1,"INSTRUCTION");
    b1.connect(m1,"sp1", 0, maxAddress);
    rs.connect(p1, "reset");

    root.preSimulate();

    m.print("I", "SP", "Constructing  watchpoints");

    // Note: cannot construct watchpoints until pre-simulation phase
    we = new myWatchpoint(p1, "watch execption", OP_WP_EXCEPTION);
    wm = new myWatchpoint(p1, "watch mode",     OP_WP_MODE);

    reg *r8 = p1.regByName("r8");
    wr = new myWatchpoint(p1, "watch register", *r8);

    // two breakpoints
    p1.breakpointAddrSet(0x10030);

    // run the program
    m.print("I", "SP", "Run program");
    processor *p = root.simulate();
    m.print("I", "SP", "Stop reason #1 %u", p->stopReason());
    p1.breakpointAddrClear(0x10030);
    p1.breakpointAddrSet(0x10038);

    // Delete the register watch point
    delete wr;

    m.print("I", "SP", "Run on");

    p =root.simulate();
    m.print("I", "SP", "Stop reason #2 %u", p->stopReason());
}

int main(int argc, const char *argv[]) {

    simplePlatform s(argc, argv);

    s.m.print("I", "MAIN", "Finished running C++ harness\n");

    return (s.m.errors() ? 1 : 0);
}

