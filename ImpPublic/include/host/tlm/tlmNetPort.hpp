/**********************************************************************
  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2008 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 3.0 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.
 *********************************************************************/

/* Derived from SimpleBusLT by Imperas Software Ltd. */

#pragma once

#include <assert.h>
#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"
#include "tlm_utils/simple_initiator_socket.h"

#include "op/op.hpp"

using namespace op;
using namespace std;
using namespace sc_core;
using namespace tlm;

namespace cw {

class tlmProcessor;
class tlmPeripheral;
class tlmModule;

////////////////////////////////////////// NET INPUT PORT /////////////////////////////////////////

class tlmNetInputPort : public tlm_analysis_port<Uns32> {

  private:
    tlmProcessor  *proc;
    tlmPeripheral *periph;
    net            n1;

  public:
    tlmNetInputPort(tlmModule &parent, tlmProcessor  *p, string name);
    tlmNetInputPort(tlmModule &parent, tlmPeripheral *p, string name);

    virtual void write(const Uns32 &value);
};


////////////////////////////////////////// NET OUTPUT PORT ////////////////////////////////////////

class tlmNetOutputPort : public tlm_analysis_port<Uns32>, netWithCallback {

  private:
    tlmPeripheral   *periph;
    tlmProcessor    *proc;

  public:
    tlmNetOutputPort(tlmModule &parent, tlmPeripheral *p, string name);
    tlmNetOutputPort(tlmModule &parent, tlmProcessor  *p, string name);

    // overload virtual func
    void written(Uns32 value) {
        // analysis port
        this->tlm_analysis_port<Uns32>::write(value);
    }
};

////////////////////////////////////////// NET INOUT PORT /////////////////////////////////////////


class tlmNetInoutPort : public tlm_analysis_port<Uns32>, netWithCallback {

  private:
    tlmPeripheral   *periph;

  public:
    tlmNetInoutPort(tlmModule &parent, tlmPeripheral *p, string name);

    // overload virtual func
    void written(Uns32 value) {
        // analysis port
        this->tlm_analysis_port<Uns32>::write(value);
    }


  public:

    void update(void *user, Uns32 value);
};

}
