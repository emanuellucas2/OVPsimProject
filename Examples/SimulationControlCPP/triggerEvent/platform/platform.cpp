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

class repeater : public  moduleTrigger {
  private:
    Uns32     max, count;
    message   m;

    void triggered(optTime now);
  public:
    repeater(module &parent, optTime period, Uns32 max);

};

repeater::repeater(module &parent, optTime period, Uns32 max)
    : moduleTrigger(parent, period)
    , max(max)
    , count(0)
{
}

void repeater::triggered(optTime now)  {

    if( max ==0 || ++count < max ) {
        m.print("I", "REP", "repeater::triggered: %u Retrigger\n", count);
        retrigger();
    } else {
        m.print("I", "REP", "repeater::triggered: %u Finished\n", count);
    }
}

class platformTrigger  {

  private:
    session   s;
    parser    p;

  public:
    module    root;
    repeater  t;
    message   m;

    platformTrigger(int argc, const char *argv[]);
};

platformTrigger::platformTrigger(int argc, const char *argv[])
    : p(argc, argv)
    , t(root, 0.1, 5)
{
    root.simulate();
}

int main(int argc, const char *argv[]) {

    platformTrigger s(argc, argv);

    s.m.print("I", "MAIN", "Finished running C++ harness\n");

    return (s.m.errors() ? 1 : 0);
}

