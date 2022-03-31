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

#include "v850Doc.h"
#include "v850Variant.h"
#include "v850Structure.h"
VMI_DOC_FN(v850Doc) {


    vmiDocNodeP Root = vmidocAddSection(0, "Root");
    vmiDocNodeP Description = vmidocAddSection(Root, "Description");
    vmiDocNodeP Licensing = vmidocAddSection(Root, "Licensing");

    vmidocAddText(Description, "RH850 Family Processor Model.");
    vmidocAddText(Description, "Reference Document : RH850G3M Rev 1.00, Aug. 2014");
    vmidocAddText(Licensing, "Open Source Apache 2.0");

    v850P v850 = (v850P)processor;

    vmiDocNodeP Limitations  = vmidocAddSection(Root, "Limitations");
    vmiDocNodeP Verification = vmidocAddSection(Root, "Verification");
    vmiDocNodeP Features     = vmidocAddSection(Root, "Features");

    vmidocAddText(Verification,
        "Models have been extensively tested by Imperas, "
        "In addition Verification suites have been supplied by Renesas for Feature Set validation"
    );

    //
    // ISA Differences
    //
    switch (v850->configInfo.arch) {
    case RH850G3M:
        vmidocAddText(Limitations, "No FPU Exceptions");
    
        vmidocAddText(Features, "RH850 Support for MPU");
        vmidocAddText(Features, "RH850 Vector based Exceptions.");
        vmidocAddText(Features, "RH850 Integer Instructions.");
        vmidocAddText(Features, "RH850 Floating Point Instructions.");
        vmidocAddText(Features, "Supervisor & User Execution Modes");
        break;

    default:
        break;
    }

    vmidocProcessor(processor, Root);
}

