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

    vmidocAddText(Description, "V850 Family Processor Model.");
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
    case V850:
        vmidocAddText(Features, "All v850 Instructions are supported.");
        vmidocAddText(Features, "All Program and System Registers are supported.");
        break;

    case V850E1F:
        vmidocAddText(Features, "All v850e1 single precision FPU Instructions are supported.");
    case V850E1:
        vmidocAddText(Limitations,
            "The following Debug Registers are non-functional "
            "DIR, BPC0, BPC1, ASID "
            "BPAV0, BPAV1, BPAM0, BPAM1 "
            "BPDV0, BPDV1, BPDM0, BPDM1 "
            );
        vmidocAddText(Features, "All v850e1 Instructions are supported.");
        vmidocAddText(Features, "All Program and System Registers are supported.");
        break;

    case V850ES:
        vmidocAddText(Limitations,
            "The following Debug Registers are non-functional "
            "DIR, DBPC, DBPSW"
            );
        vmidocAddText(Features, "All v850es Instructions are supported.");
        break;

    case V850E2M:
        vmidocAddText(Limitations, "This variant is does not have the FPU instructions implemented.");
        vmidocAddText(Limitations, "This variant is currently under development.");
        break;

    case V850E2:
    case V850E2R:
        vmidocAddText(Limitations, "This variant is currently under development.");
        break;

    default:
        break;
    }

    vmidocProcessor(processor, Root);
}

