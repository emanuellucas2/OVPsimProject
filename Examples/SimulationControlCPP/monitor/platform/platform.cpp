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

class myMonitor : public monitor {

  public:
    myMonitor(processor &p,                     const char *label, bool write, Addr lo, Addr hi);
    myMonitor(bus       &b,    processor &proc, const char *label, bool write, Addr lo, Addr hi);
    myMonitor(memory    &m,    processor &proc, const char *label, bool write, Addr lo, Addr hi);
    ~myMonitor() { }
  private:
    void triggered(processor *p, Addr PA, Addr VA, Uns32 bytes, const void *data);
    const char *label;
    message   m;
    bool write_;
    enum {procType, busType, memType} type_;
};


void myMonitor::triggered(processor *p, Addr PA, Addr VA, Uns32 bytes, const void *data) {
    const char *name = p ? p->name().c_str() : "<no proc>";
    m.print("I", "MWP",  "%s Triggered: processor=%s PA=0x"FMT_Ax" VA=0x"FMT_Ax" Bytes=%u\n",
            label, name, PA, VA, bytes);

    // On the memory write trigger call, cause the simulator to return to the caller
    if (p && type_ == memType && write_) {
        m.print("I", "MWP_HALT", "Yielding processor");
        p->yield();
    }
}

myMonitor::myMonitor (processor &parent, const char *l, bool write, Addr lo, Addr hi)
    : monitor(parent, write,  lo, hi)
    , label(l)
    , write_(write)
    , type_(procType)
{ }

myMonitor::myMonitor (bus &parent, processor &proc, const char *l, bool write, Addr lo, Addr hi)
    : monitor(parent, proc, write, lo, hi)
    , label(l)
    , write_(write)
    , type_(busType)
{ }

myMonitor::myMonitor (memory &parent, processor &proc, const char *l, bool write, Addr lo, Addr hi)
    : monitor(parent, proc, write, lo, hi)
    , label(l)
    , write_(write)
    , type_(memType)
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

    myMonitor *wpr, *wpw, *wbr, *wbw, *wmr, *wmw;

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

    // Note: cannot construct monitors until pre-simulation phase
    root.preSimulate();

    m.print("I", "SP", "Constructing  monitors\n");

    // These monitor reads/write by p1 to the selected region
    wpr = new myMonitor(p1, "p1RdMonitor", 0,  0x10000, 0x10003);
    wpw = new myMonitor(p1, "p1WrMonitor", 1,  0x10000, 0x10003);

    // These monitor reads/write to the selected region of bus b1 by p1 only
    wbr = new myMonitor(b1, p1, "b1p1RdMonitor", 0,  0x20000, 0x20003);
    wbw = new myMonitor(b1, p1, "b1p1WrMonitor", 1,  0x20000, 0x20003);

    // These monitor reads/write to the selected region of memory m1 by p1 only
    wmr = new myMonitor(m1, p1, "m1p1RdMonitor", 0,  0x30000, 0x30003);
    wmw = new myMonitor(m1, p1, "m1p1WrMonitor", 1,  0x30000, 0x30003);

    m.print("I", "SP",  "Run with monitors on\n");

    processor * p = root.simulate();

    if (p) {
        m.print("I", "SP", "First run returned proc %s, stop reason %u (%s)\n",
                p->name().c_str(), p->stopReason(), p->stopReasonString().c_str());
    } else{
        m.print("E", "SP", "First root.simulate() returned NULL processor\n");
    }

    m.print("I", "SP", "Deleting monitors\n");

    delete wpr;
    delete wpw;
    delete wbr;
    delete wbw;
    delete wmr;
    delete wmw;

    m.print("I", "SP",  "Run with no monitors\n");

    p = root.simulate();

    if (p) {
        m.print("I", "SP", "First run returned proc %s, stop reason %u (%s)\n",
                p->name().c_str(), p->stopReason(), p->stopReasonString().c_str());
    } else{
        m.print("E", "SP", "First root.simulate() returned NULL processor\n");
    }
}

int main(int argc, const char *argv[]) {

    simplePlatform s(argc, argv);

    s.m.print("I", "MAIN", "Finished running C++ harness\n");

    return (s.m.errors() ? 1 : 0);
}

