/*
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

#ifndef OR1KEXCEPTIONS_H
#define OR1KEXCEPTIONS_H

// VMI header files
#include "vmi/vmiAttrs.h"

// model header files
#include "or1kStructure.h"

//
// Ensure any pending interrupt is taken before the next instruction
//
void or1kInterruptNext(or1kP or1k);

//
// Return the TTCR register
//
Uns32 or1kGetTTCR(or1kP or1k);

//
// Set the TTCR register
//
void or1kSetTTCR(or1kP or1k, Uns32 TTCR);

//
// Set the TTMR register
//
void or1kSetTTMR(or1kP or1k, Uns32 TTMR);

//
// Set the PICMR register
//
void or1kSetPICMR(or1kP or1k, Uns32 PICMR);

//
// Raise an interrupt request to the Programmable Interrupt Controller
// 'deviceId' should have one bit set to identify the interrupting device
// 'newValue' indicates if the interrupt is to be raised (if non-zero) or
// lowered (if zero)
//
VMI_NET_CHANGE_FN(or1kExternalInterrupt);

//
// Raise a reset interrupt request
//
VMI_NET_CHANGE_FN(or1kExternalReset);

#endif
