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



// VMI header files
#include "vmi/vmiAttrs.h"
#include "vmi/vmiModelInfo.h"
#include "vmi/vmiDoc.h"

#include "m16cDoc.h"
#include "m16cVariant.h"

void m16cDoc(vmiProcessorP processor, m16cParamValuesP parameters) {
    vmiDocNodeP root = vmidocAddSection(0, "Root");
    vmiDocNodeP desc = vmidocAddSection(root, "Description");
    vmidocAddText(desc, "M16c Family 16Bit CISC processor model.");

    vmiDocNodeP lic  = vmidocAddSection(root, "Licensing");
    vmidocAddText(lic,  "Copyright Posedge Software, Licensed as Open Source Apache 2.0");

    vmiDocNodeP lim  = vmidocAddSection(root, "Limitations");
    vmidocAddText(lim, "Core Instruction Set Architecture only.");
    vmidocAddText(lim, "Interrupt and Reset Signals are TBD.");

    vmiDocNodeP verif = vmidocAddSection(root, "Verification");
    vmidocAddText(verif, "Model has been validated correct by "
                         "running through extensive instruction level tests");

    vmiDocNodeP ref = vmidocAddSection(root, "Reference");
    vmidocAddText(ref, "Renesas 16-bit Single-Chip MicroComputer"
                       "M16C/60, M16C/20, M16C/Tiny Series Software Manual Rev 4.00 2004.01"
                       "(rej09b0137_m16csm.pdf)");

    vmidocProcessor(processor, root);
}

