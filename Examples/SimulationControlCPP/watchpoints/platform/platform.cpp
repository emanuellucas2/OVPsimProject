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
    myWatchpoint(processor &p, const char *label, optWatchpointType type, Addr lo, Addr hi);
    myWatchpoint(bus &b,       const char *label, optWatchpointType type, Addr lo, Addr hi);
    myWatchpoint(memory &m,    const char *label, optWatchpointType type, Addr lo, Addr hi);
    ~myWatchpoint() { }
  private:
    bool triggered(processor *p, Addr PA, Addr VA, Uns32 bytes, void *data);
    const char *label;
    message   m;
    bool     run;
};


bool myWatchpoint::triggered(processor *p, Addr PA, Addr VA, Uns32 bytes, void *data) {
    const char *name = p ?  p->name().c_str() : "<no proc>";
    m.print("I", "MWP",  "%s Triggered: processor=%s PA=0x"FMT_Ax" VA=0x"FMT_Ax" Bytes=%u Run=%u\n",
            label, name, PA, VA, bytes, run);
    if(run) {
        run = 0;
        return 1;   // Returning 1 tells simulator to continue
    } else {
        return 0;   // Returning 0 tells simulator to stop
    }
}

myWatchpoint::myWatchpoint (processor &parent, const char *l, optWatchpointType type, Addr lo, Addr hi)
    : watchpoint(parent, type, false, lo, hi)
    , label(l)
    , run(1) 
{ }

myWatchpoint::myWatchpoint (bus &parent, const char *l, optWatchpointType type, Addr lo, Addr hi)
    : watchpoint(parent, type, lo, hi)
    , label(l)
    , run(1) 
{ }

myWatchpoint::myWatchpoint (memory &parent, const char *l, optWatchpointType type, Addr lo, Addr hi)
    : watchpoint(parent, type, lo, hi)
    , label(l)
    , run(1) 
{ }

class simplePlatform {

  private:
    Addr      maxAddress;
    session   s;
    parser    p;

    params paramsForP1(void) {
        params p;
        p.set("defaultsemihost", (bool)1);
        return p;
    }

  public:
    message   m;
    module    root;
    vlnv      v;
    processor p1;
    memory    m1;
    bus       b1;

    myWatchpoint *wp, *wb, *wm;

    simplePlatform(int argc, const char *argv[]);
};

simplePlatform::simplePlatform(int argc, const char *argv[]) :
    maxAddress(0xffffffff)
   ,p(argc, argv)
   ,p1(root, v.string( "ovpworld.org", "processor", "or1k", "1.0", OP_PROCESSOR), "p1", paramsForP1() )
   ,m1(root,"m1", maxAddress, OP_PRIV_RWX)
   ,b1(root, "b1", 32)
{
    b1.connect(p1,"DATA");
    b1.connect(p1,"INSTRUCTION");
    b1.connect(m1,"sp1", 0, maxAddress);

    // Note: cannot construct watchpoints until pre-simulation phase
    root.preSimulate();

    m.print("I", "SP", "Constructing  watchpoints");

    // Watchpoint on reads/writes made by p1 to the selected region
    wp = new myWatchpoint(p1, "processorAccessWP", OP_WP_MEM_ACCESS, 0x10000, 0x10003);

    // Watchpoint on reads made by any initiator to the selected region of bus b1
    wb = new myWatchpoint(b1, "busReadWP",         OP_WP_MEM_READ,   0x20000, 0x20003);

    // Watchpoint on writes made by any initiator to the selected region of memory m1
    wm = new myWatchpoint(m1, "memoryWriteWP",     OP_WP_MEM_WRITE,  0x30000, 0x30003);

    processor * p = root.simulate();

    if (p) {
        m.print("I", "SP", "First run returned proc %s, stop reason %u (%s)\n",
                p->name().c_str(), p->stopReason(), p->stopReasonString().c_str());
    } else{
        m.print("E", "SP", "First root.simulate() returned NULL processor\n");
    }

    m.print("I", "SP", "Deleting watchpoints");

    delete wp;
    delete wb;
    delete wm;

    m.print("I", "SP",  "Run on with no watchpoints");
    p = root.simulate();

    if (p) {
        m.print("I", "SP", "Second run returned proc %s, stop reason %u (%s)\n",
                p->name().c_str(), p->stopReason(), p->stopReasonString().c_str());
    } else{
        m.print("E", "SP", "Second root.simulate() returned NULL processor\n");
    }
}

int main(int argc, const char *argv[]) {

    simplePlatform s(argc, argv);

    s.m.print("I", "MAIN", "Finished running C++ harness");

    return (s.m.errors() ? 1 : 0);
}

