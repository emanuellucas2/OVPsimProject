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

class arm_ARM1176JZ_S : public tlmProcessor
{
  private:
    params paramsForProc(params p) {
        p.set("variant", "ARM1176JZ-S");
        return p;
    }

    params paramsForProc() {
        params p;
        p.set("variant", "ARM1176JZ-S");
        return p;
    }

    const char *getModel() {
        return opVLNVString (NULL, "arm.ovpworld.org", "processor", "arm", "1.0", OP_PROCESSOR, OP_VLNV_FATAL);
    }

  public:
    tlmBusMasterPort     ITCM0;
    tlmBusMasterPort     ITCM1;
    tlmBusMasterPort     DTCM0;
    tlmBusMasterPort     DTCM1;
    tlmBusMasterPort     INSTRUCTION;
    tlmBusMasterPort     DATA;
    tlmNetInputPort      EVENTI;
    tlmNetOutputPort     EVENTO;
    tlmNetInputPort      reset;
    tlmNetInputPort      fiq;
    tlmNetInputPort      irq;
    tlmNetInputPort      sei;
    tlmNetInputPort      AXI_SLVERR;
    tlmNetInputPort      CP15SDISABLE;
    tlmNetOutputPort     DMAIRQ;
    tlmNetOutputPort     DMASIRQ;
    tlmNetOutputPort     DMAEXTERRIRQ;
    tlmNetOutputPort     PMUIRQ;
    tlmNetOutputPort     VALRESET;
    tlmNetOutputPort     VALIRQ;
    tlmNetOutputPort     VALFIQ;
    tlmNetOutputPort     VALDEBUG;
    tlmNetOutputPort     VICACK;
    tlmNetInputPort      VICADDR;

    arm_ARM1176JZ_S(tlmModule &parent, sc_module_name name)
    : tlmProcessor(parent, getModel(), name, paramsForProc())
    , ITCM0 (parent, this, "ITCM0", 32)
    , ITCM1 (parent, this, "ITCM1", 32)
    , DTCM0 (parent, this, "DTCM0", 32)
    , DTCM1 (parent, this, "DTCM1", 32)
    , INSTRUCTION (parent, this, "INSTRUCTION", 32)
    , DATA (parent, this, "DATA", 32)
    , EVENTI(parent, this, "EVENTI")
    , EVENTO(parent, this, "EVENTO")
    , reset(parent, this, "reset")
    , fiq(parent, this, "fiq")
    , irq(parent, this, "irq")
    , sei(parent, this, "sei")
    , AXI_SLVERR(parent, this, "AXI_SLVERR")
    , CP15SDISABLE(parent, this, "CP15SDISABLE")
    , DMAIRQ(parent, this, "DMAIRQ")
    , DMASIRQ(parent, this, "DMASIRQ")
    , DMAEXTERRIRQ(parent, this, "DMAEXTERRIRQ")
    , PMUIRQ(parent, this, "PMUIRQ")
    , VALRESET(parent, this, "VALRESET")
    , VALIRQ(parent, this, "VALIRQ")
    , VALFIQ(parent, this, "VALFIQ")
    , VALDEBUG(parent, this, "VALDEBUG")
    , VICACK(parent, this, "VICACK")
    , VICADDR(parent, this, "VICADDR")
    {
    }

    arm_ARM1176JZ_S(tlmModule &parent, sc_module_name name, params p, Uns32 ITCM0Width=32, Uns32 ITCM1Width=32, Uns32 DTCM0Width=32, Uns32 DTCM1Width=32, Uns32 INSTRUCTIONWidth=32, Uns32 DATAWidth=32)
    : tlmProcessor(parent, getModel(), name, paramsForProc(p))
    , ITCM0 (parent, this, "ITCM0", ITCM0Width)
    , ITCM1 (parent, this, "ITCM1", ITCM1Width)
    , DTCM0 (parent, this, "DTCM0", DTCM0Width)
    , DTCM1 (parent, this, "DTCM1", DTCM1Width)
    , INSTRUCTION (parent, this, "INSTRUCTION", INSTRUCTIONWidth)
    , DATA (parent, this, "DATA", DATAWidth)
    , EVENTI(parent, this, "EVENTI")
    , EVENTO(parent, this, "EVENTO")
    , reset(parent, this, "reset")
    , fiq(parent, this, "fiq")
    , irq(parent, this, "irq")
    , sei(parent, this, "sei")
    , AXI_SLVERR(parent, this, "AXI_SLVERR")
    , CP15SDISABLE(parent, this, "CP15SDISABLE")
    , DMAIRQ(parent, this, "DMAIRQ")
    , DMASIRQ(parent, this, "DMASIRQ")
    , DMAEXTERRIRQ(parent, this, "DMAEXTERRIRQ")
    , PMUIRQ(parent, this, "PMUIRQ")
    , VALRESET(parent, this, "VALRESET")
    , VALIRQ(parent, this, "VALIRQ")
    , VALFIQ(parent, this, "VALFIQ")
    , VALDEBUG(parent, this, "VALDEBUG")
    , VICACK(parent, this, "VICACK")
    , VICADDR(parent, this, "VICADDR")
    {
    }

    void before_end_of_elaboration() {
        ITCM0.bindIfNotBound();
        ITCM1.bindIfNotBound();
        DTCM0.bindIfNotBound();
        DTCM1.bindIfNotBound();
        DATA.bindIfNotBound();
    }

    void dmi(bool on) {
        ITCM0.dmi(on);
        ITCM1.dmi(on);
        DTCM0.dmi(on);
        DTCM1.dmi(on);
        INSTRUCTION.dmi(on);
        DATA.dmi(on);
    }
}; /* class arm_ARM1176JZ_S */

