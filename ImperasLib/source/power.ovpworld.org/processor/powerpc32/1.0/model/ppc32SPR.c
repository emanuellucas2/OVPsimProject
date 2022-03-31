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

#include "ppc32Structure.h"
#include "ppc32SPR.h"

DEFSPRIF(isa)

void ppc32AllocSPR (ppc32P ppc32) {
    //
    // Test variant and call specific init
    //
    ppc32AllocSPR_isa(ppc32);
}

void ppc32InitSPR (ppc32P ppc32) {
    //
    // Test variant and call specific init
    //
    ppc32InitSPR_isa(ppc32);
}

void ppc32mtmsr(ppc32P ppc32, Uns8 l, vmiReg gpr_rs, Uns8 rs) {
    //
    // Test variant and call specific init
    //
    ppc32mtmsr_isa(ppc32, l, gpr_rs, rs);
}

void ppc32mfmsr(ppc32P ppc32, vmiReg gpr_rt, Uns8 rt) {
    //
    // Test variant and call specific init
    //
    ppc32mfmsr_isa(ppc32, gpr_rt, rt);
}

void ppc32mtspr(ppc32P ppc32, Uns16 spr, vmiReg gpr_rs, Uns8 rs) {
    //
    // Test variant and call specific init
    //
    ppc32mtspr_isa(ppc32, spr, gpr_rs, rs);
}

void ppc32mfspr(ppc32P ppc32, Uns8 rt, vmiReg gpr_rt, Uns16 spr) {
    //
    // Test variant and call specific init
    //
    ppc32mfspr_isa(ppc32, rt, gpr_rt, spr);
}

void ppc32wrteei(ppc32P ppc32, Uns8 e) {
    //
    // Test variant and call specific init
    //
    ppc32wrteei_isa(ppc32, e);
}

void ppc32wrtee(ppc32P ppc32, vmiReg gpr_rs, Uns8 rs) {
    //
    // Test variant and call specific init
    //
    ppc32wrtee_isa(ppc32, gpr_rs, rs);
}

Uns32 ppc32ReadSPR (ppc32P ppc32, Uns32 index) {
    //
    // Test variant and call specific init
    //
    return ppc32ReadSPR_isa (ppc32, index);
}

void ppc32WriteSPR (ppc32P ppc32, Uns32 index, Uns32 value) {

    //
    // Test variant and call specific init
    //
    ppc32WriteSPR_isa (ppc32, index, value);
}

Uns32 ppc32ReadMSR (ppc32P ppc32) {
    //
    // Test variant and call specific init
    //
    return ppc32ReadMSR_isa (ppc32);
}

void ppc32WriteMSR (ppc32P ppc32, Uns32 value) {

    //
    // Test variant and call specific init
    //
    ppc32WriteMSR_isa (ppc32, value);
}

Uns8 ppc32ReadMSR_VMMode (ppc32P ppc32) {
    //
    // Test variant and call specific init
    //
    return ppc32ReadMSR_VMMode_isa(ppc32);
}

Bool ppc32IsUserMode(ppc32P ppc32) {
    //
    // Test variant and call specific init
    //
    return ppc32IsUserMode_isa(ppc32);
}

Bool ppc32IsPrivMode(ppc32P ppc32) {
    //
    // Test variant and call specific init
    //
    return ppc32IsPrivMode_isa(ppc32);
}

Bool ppc32IsHypvMode(ppc32P ppc32) {
    //
    // Test variant and call specific init
    //
    return ppc32IsHypvMode_isa(ppc32);
}
