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

int main(int argc, const char *argv[]) {

    cout << "\nRunning C++ harness..." << endl;

    session s;
    message m;
    parser  p(argc, argv);

    module mi;
    module u1(mi, "module", "u1");

    mi.simulate();

    cout << "\nFinished running C++ harness." << endl;

    return (m.errors() ? 1 : 0);
}

