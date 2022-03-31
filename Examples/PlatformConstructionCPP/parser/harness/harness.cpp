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

message *m;

class myParser : public parser {

private:
  bool  extra1V;
  Uns32 extra2V;
  bool error(const char *);

public:
    myParser(int argc, const char *argv[]);
    ~myParser() {}
    bool  extra1() { return extra1V; }
    Uns32 extra2() { return extra2V; }

};

myParser::myParser(int argc, const char *argv[])
    : parser("app", OP_AC_NONE)
    , extra1V(0)
    , extra2V(0)
{
    add("extra1", "X", 0, "platform", OP_FT_BOOLVAL,  &extra1V, "Extra argument #1");
    add("extra2", "Y", 0, "platform", OP_FT_UNS32VAL, &extra2V, "Extra argument #2");

    parse(argc, argv);
}

bool myParser::error(const char *message) {
    m->print("I", "APP_ERR", "Error parsing %s\n", message);
    return true;
}

int main(int argc, const char *argv[]) {

    session s;
    m = new message;

    myParser p(argc, argv);
    m->printf("\nAPP\n\n");

    m->print("I", "APP", "extra1=%u\n", p.extra1());
    m->print("I", "APP", "extra2=%u\n", p.extra2());

    return (m->errors() ? 1 : 0);
}

