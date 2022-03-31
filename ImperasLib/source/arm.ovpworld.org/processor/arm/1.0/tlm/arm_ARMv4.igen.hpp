/*
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * YOU MAY USE THE SOFTWARE SUBJECT TO THE LICENSE TERMS BELOW
 * PROVIDED THAT YOU ENSURE THAT THIS NOTICE IS REPLICATED UNMODIFIED
 * AND IN ITS ENTIRETY IN ALL DISTRIBUTIONS OF THE SOFTWARE,
 * MODIFIED OR UNMODIFIED, IN SOURCE CODE OR IN BINARY FORM.
 *
 * In respect of all models:
 *   The license shall not be construed as granting a license to create a hardware
 *   implementation of the functionality of the software licensed hereunder.
 *
 * In respect of ARM related models:
 *   The license below extends only for your use of the software for the sole
 *   purpose of designing, developing, analyzing, debugging, testing,
 *   verifying, validating and optimizing software which: (a) (i) is for ARM
 *   based systems; and (ii) does not incorporate the ARM Models or any part
 *   thereof; and (b) such ARM Models may not be used to emulate an ARM based
 *   system to run application software in a production or live environment.
 *
 *   The license does not entitle you to use the ARM models for evaluating
 *   the validity of any ARM patent.
 *
 * The license is non-exclusive, worldwide, non-transferable and revocable.
 *
 * Licensed under an Imperas Modified Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.ovpworld.org/licenses/OVP_MODIFIED_1.1_APACHE_OPEN_SOURCE_LICENSE_2.0.pdf
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                             Version 20211118.0
//
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "tlm/tlmProcessor.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"

using namespace sc_core;
using namespace cw;

class arm_ARMv4 : public tlmProcessor
{
  private:
    params paramsForProc(params p) {
        p.set("variant", "ARMv4");
        return p;
    }

    params paramsForProc() {
        params p;
        p.set("variant", "ARMv4");
        return p;
    }

    const char *getModel() {
        return opVLNVString (NULL, "arm.ovpworld.org", "processor", "arm", "1.0", OP_PROCESSOR, OP_VLNV_FATAL);
    }

  public:
    tlmBusMasterPort     INSTRUCTION;
    tlmBusMasterPort     DATA;
    tlmNetInputPort      reset;
    tlmNetInputPort      fiq;
    tlmNetInputPort      irq;
    tlmNetInputPort      sei;

    arm_ARMv4(tlmModule &parent, sc_module_name name)
    : tlmProcessor(parent, getModel(), name, paramsForProc())
    , INSTRUCTION (parent, this, "INSTRUCTION", 32)
    , DATA (parent, this, "DATA", 32)
    , reset(parent, this, "reset")
    , fiq(parent, this, "fiq")
    , irq(parent, this, "irq")
    , sei(parent, this, "sei")
    {
    }

    arm_ARMv4(tlmModule &parent, sc_module_name name, params p, Uns32 INSTRUCTIONWidth=32, Uns32 DATAWidth=32)
    : tlmProcessor(parent, getModel(), name, paramsForProc(p))
    , INSTRUCTION (parent, this, "INSTRUCTION", INSTRUCTIONWidth)
    , DATA (parent, this, "DATA", DATAWidth)
    , reset(parent, this, "reset")
    , fiq(parent, this, "fiq")
    , irq(parent, this, "irq")
    , sei(parent, this, "sei")
    {
    }

    void before_end_of_elaboration() {
        DATA.bindIfNotBound();
    }

    void dmi(bool on) {
        INSTRUCTION.dmi(on);
        DATA.dmi(on);
    }
}; /* class arm_ARMv4 */

