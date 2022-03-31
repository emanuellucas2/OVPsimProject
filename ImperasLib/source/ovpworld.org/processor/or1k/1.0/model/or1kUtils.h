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

#ifndef OR1KUTILS_H
#define OR1KUTILS_H

// model header files
#include "or1kExceptionTypes.h"
#include "or1kStructure.h"

//
// Return the current value of the SR register
//
Uns32 or1kGetSR(or1kP or1k);

//
// Set the current value of the SR register
//
void or1kSetSR(or1kP or1k, Uns32 value);

//
// Enter supervisor mode on OR1K
//
void or1kEnterSupervisorMode(or1kP or1k);

//
// Take an exception
//
void or1kTakeException(or1kP or1k, or1kException exception, Uns32 pcOffset);

#endif
