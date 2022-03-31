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
#include "vmi/vmiDoc.h"

#include "or1kDoc.h"
#include "or1kParameters.h"

VMI_DOC_FN(or1kDoc) {
    vmiDocNodeP root = vmidocAddSection(0, "Root");
    vmiDocNodeP desc = vmidocAddSection(root, "Description");
    vmidocAddText(desc, "OR1K 32Bit processor model.");

    vmiDocNodeP lic  = vmidocAddSection(root, "Licensing");
    vmidocAddText(lic,  "Open Source Apache 2.0");

    vmiDocNodeP lim  = vmidocAddSection(root, "Limitations");
    vmidocAddText(lim, "Core instruction set only. Does not support MMU & TLB.");

    vmidocProcessor(processor, root);
}

