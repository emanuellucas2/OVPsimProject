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

////////////////////////////////////////////////////////////////////////////////

class myCommandArgs : public commandArgs {

public:
    void eachCommandArg(commandArg *c);

public:
    myCommandArgs() {}
    message m;
};

void myCommandArgs::eachCommandArg(commandArg *c) {
    m.print("I", "MWP",  "    Command arg %s : %s (%s)", c->name(), c->typeString(), c->desc());
}

///////////////////////////////////////////////////////////////////////////////

class myCommands : public commands {

public:
    void eachCommand(command *c);

public:
    myCommands() {}
    message m;
    myCommandArgs ma;
};

void myCommands::eachCommand(command *c) {
    m.print("I", "MWP",  "Command %s (%s)", c->name(), c->helpC());
    ma.all(c);
    m.print("I", "MWP",  "");
}

class simplePlatform {

  private:
    Addr      maxAddress;
    session   s;
    parser    p;

    params paramsForP1(void) {
        params p;
        p.set("variant", "ARM7TDMI");
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

    myCommands    mc;

    simplePlatform(int argc, const char *argv[]);
};

simplePlatform::simplePlatform(int argc, const char *argv[]) :
    maxAddress(0xffffffff)
   ,p(argc, argv)
   ,p1(root, v.string( "arm.ovpworld.org", "processor", "arm", "1.0", OP_PROCESSOR), "p1", paramsForP1() )
   ,m1(root,"m1", maxAddress, OP_PRIV_RWX)
   ,b1(root, "b1", 32)
   ,mc()
{
    b1.connect(p1,"DATA");
    b1.connect(p1,"INSTRUCTION");
    b1.connect(m1,"sp1", 0, maxAddress);

    root.preSimulate();

    // report all the commands
    mc.all(p1);

    // turn on tracing
    const char *cmd[3] = {
        "itrace",
        "-on",
        "-instructioncount"
    };
    root.commandCall("p1/itrace", 3, cmd);

    p1.simulate(10);
}

int main(int argc, const char *argv[]) {

    simplePlatform s(argc, argv);
    return (s.m.errors() ? 1 : 0);
}

