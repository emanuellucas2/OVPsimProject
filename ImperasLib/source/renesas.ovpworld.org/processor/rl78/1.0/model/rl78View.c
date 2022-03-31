/*
 * Copyright (c)      2016 eSOL TRINITY, www.esol-trinity.co.jp
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


// VMI header files
#include "vmi/vmiRt.h"

// model header files
#include "rl78Structure.h"



// OVP_Processor_Modeling_Guide.pdf  page225
// Note that the processor also contains automaticallycreated modeswitch and 
// exception events. The modeswitch event is triggered when the processor 
// switches mode using vmirtSetMode. The exception event is triggered when 
// the processor updates its execution address using vmirtSetPCException.



void rl78CreateView(rl78P rl78) {

// get the base processor view object
//    vmiProcessorP  processor       = (vmiProcessorP) rl78;
//    vmiViewObjectP processorObject = vmirtGetProcessorViewObject(processor);

}
