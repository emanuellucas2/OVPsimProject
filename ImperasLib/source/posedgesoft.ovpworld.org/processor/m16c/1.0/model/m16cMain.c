/*
 * Copyright (c) 2011-2014 Posedge Software Inc., www.posedgesoft.com
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
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




// standard include files
#include <string.h>

// VMI header files
#include "vmi/vmiAttrs.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiRt.h"

// model header files
#include "m16cBus.h"
#include "m16cDoc.h"
#include "m16cExceptions.h"
#include "m16cStructure.h"
#include "m16cFunctions.h"
#include "m16cParameters.h"
#include "m16cTypeRefs.h"
#include "m16cDecode.h"


//
// m16c processor constructor
//
VMI_CONSTRUCTOR_FN(m16cConstructor) {
    m16cP m16c = (m16cP)processor;
    m16cParamValuesP params = (m16cParamValuesP)parameterValues;
    Uns32 i;

    m16c->verbose = params->verbose;
    m16c->compat  = params->compatibility;
    m16c->variant = params->variant;
    m16c->decoderCB = m16cDecode;

    m16c->carryFlag = False;
    m16c->debugFlag = False;
    m16c->zeroFlag = False;
    m16c->signFlag = False;
    m16c->regBankSelectFlag = False;
    m16c->overflowFlag = False;
    m16c->intEnableFlag = False;
    m16c->spSelectFlag = False;
    m16c->intPriorityLevel = 0;
    //
    // In GDB mode this powers up as False
    // The Silicon however says it powers up as True
    //
    //   m16c->interruptDisableFlag = (m16c->compat == COMPAT_GDB) ? False : True;
    // m16c->exceptionPendingFlag = False;
    // m16c->nmiPendingFlag = False;

    //
    // Initialize the General Purpose Registers
    //
    for (i = 1; i < M16C_REGS; i++) {
        m16c->regs[i] = 0x0;
    }

    // save flags on processor structure
    m16c->flags = vmirtProcessorFlags(processor);

    // external intp, nmi, intack, mireti and reset
    // m16cConnectSignals(m16c);
    m16cNewNetPorts(m16c);

    // create bus port descriptions
    m16cNewBusPorts(m16c);

    m16cDoc(processor, params);
}

//
// m16c processor destructor
//
VMI_DESTRUCTOR_FN(m16cDestructor) {
    m16cP m16c = (m16cP)processor;

    // free net port descriptions
    m16cFreeNetPorts(m16c);

    // free bus port descriptions
    m16cFreeBusPorts(m16c);
}

