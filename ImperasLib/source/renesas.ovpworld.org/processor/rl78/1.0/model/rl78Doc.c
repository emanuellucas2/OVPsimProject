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
#include "vmi/vmiAttrs.h"
#include "vmi/vmiModelInfo.h"
#include "vmi/vmiDoc.h"

#include "rl78Doc.h"
#include "rl78Structure.h"
#include "rl78Parameters.h"

VMI_DOC_FN(rl78Doc) {

    vmiDocNodeP Root = vmidocAddSection(0, "Root");
    vmiDocNodeP Description = vmidocAddSection(Root, "Description");
    vmiDocNodeP Licensing = vmidocAddSection(Root, "Licensing");
    vmiDocNodeP Reference  = vmidocAddSection(Root, "Reference");

    vmidocAddText(Description, "RL78 Family Processor Model.");
    vmidocAddText(Licensing,   "Open Source Apache 2.0");
    vmidocAddText(Reference,   "RL78 User Manual: Software, Single-Chip microcontrollers, "
                               "http://documentation.renesas.com/doc/products/mpumcu/doc/rl78/r01us0015ej0220_rl78.pdf");

    vmiDocNodeP Limitations  = vmidocAddSection(Root, "Limitations");
    vmiDocNodeP Verification = vmidocAddSection(Root, "Verification");
    vmiDocNodeP Features     = vmidocAddSection(Root, "Features");

    rl78P rl78 = (rl78P)processor;

    switch (rl78->variant) {
    case en_RL78_S1:
        vmidocAddText(Limitations,
            "All instructions are supported "
            "except the MULU, MULHU, MULH, DIVHU, MACHU and MACH instructions that are not implemented."
        );
        vmidocAddText(Limitations, "Banked registers are not supported");
        break;
    case en_RL78_S2:
        vmidocAddText(Limitations,
            "All instructions are supported "
            "except the MULU, MULHU, MULH, DIVHU, MACHU, MACH and SEL instructions that are not implemented."
        );
        vmidocAddText(Features,"Banked registers are supported");
        break;
    case en_RL78_S3:
        vmidocAddText(Features,"All instructions are supported");
        vmidocAddText(Features,"Banked registers are supported");
        break;
    default:
        break;
    }

    vmidocAddText(Features,"External exceptions are supported");
    vmidocAddText(Features,"The BRK instruction (internal trap) is supported");
    vmidocAddText(Features,"Memory mirroring is supported");
    vmidocAddText(Features,"Memory mapped registers is supported");

    vmidocAddText(Limitations,
        "The PMC (Processor Model Control) register behavior is not modeled."
    );
    vmidocAddText(Limitations,
        "This processor model requires that RAM is available at the address range of the memory mapped registers"
    );
    vmidocAddText(Limitations,
        "Address ranges 0xFFEE0 to 0xFFEFF for General purpose registers (e.g. X, A)"
    );
    vmidocAddText(Limitations,
        "Address ranges 0xFFFF0 to 0xFFFFF for special function registers (e.g. SP)"
    );

    vmidocAddText(Limitations,
        "This processor model should be started with a reset signal. "
        "The processor reads from the reset vector 0x0000 on reset and uses this value for the initial PC"
    );

    vmidocAddText(Verification,
        "Models have been tested by eSOL TRINITY and Imperas"
    );


    vmidocProcessor(processor, Root);
}

