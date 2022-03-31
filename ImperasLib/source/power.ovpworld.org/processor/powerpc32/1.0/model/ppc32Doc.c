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

// VMI header files
#include "vmi/vmiAttrs.h"
#include "vmi/vmiModelInfo.h"
#include "vmi/vmiDoc.h"

#include "ppc32Doc.h"
#include "ppc32Variant.h"
#include "ppc32Structure.h"
void ppc32Doc(vmiProcessorP processor, ppc32ParamValuesP parameters) {


    vmiDocNodeP Root = vmidocAddSection(0, "Root");
    vmiDocNodeP Description = vmidocAddSection(Root, "Description");
    vmiDocNodeP Licensing = vmidocAddSection(Root, "Licensing");

    vmidocAddText(Description, "PPC32 Family Processor Model.");
    vmidocAddText(Licensing, "Open Source Apache 2.0");

    vmiDocNodeP Limitations  = vmidocAddSection(Root, "Limitations");
    vmiDocNodeP Verification = vmidocAddSection(Root, "Verification");
    vmiDocNodeP Features     = vmidocAddSection(Root, "Features");

    vmidocAddText(Limitations, "This model is currently under development. The FPU is incomplete.");
    vmidocAddText(Verification, "Basic verification of ISA against reference has been performed.");
    vmidocAddText(Features, "");

    vmidocProcessor(processor, Root);
}

