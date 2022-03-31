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

#include "vmi/vmiMessage.h"

#include "ppc32Structure.h"
#include "ppc32SPR.h"

DEFSPRIF(400)

void ppc32AllocSPR (ppc32P ppc32) {
    //
    // Test variant and call specific init
    //
    switch (ppc32->configInfo.arch) {
    case VARIANT_M440:
    case VARIANT_M460:
    case VARIANT_M470:
        break;
    case VARIANT_M476:
        ppc32AllocSPR_400(ppc32);
        break;
    default:
        vmiMessage("F", "SPR", "%s variant %s mismatch\n", __FUNCTION__, ppc32->configInfo.name);
        break;
    }
}

void ppc32InitSPR (ppc32P ppc32) {
    //
    // Test variant and call specific init
    //
    switch (ppc32->configInfo.arch) {
    case VARIANT_M440:
    case VARIANT_M460:
    case VARIANT_M470:
        break;
    case VARIANT_M476:
        ppc32InitSPR_400(ppc32);
        break;
    default:
        vmiMessage("F", "SPR", "%s variant %s mismatch\n", __FUNCTION__, ppc32->configInfo.name);
        break;
    }
}

void ppc32mtmsr(ppc32P ppc32, Uns8 l, vmiReg gpr_rs, Uns8 rs) {
    //
    // Test variant and call specific init
    //
    switch (ppc32->configInfo.arch) {
    case VARIANT_M440:
    case VARIANT_M460:
    case VARIANT_M470:
        break;
    case VARIANT_M476:
        ppc32mtmsr_400(ppc32, l, gpr_rs, rs);
        break;
    default:
        vmiMessage("F", "SPR", "%s variant %s mismatch\n", __FUNCTION__, ppc32->configInfo.name);
        break;
    }
}

void ppc32mfmsr(ppc32P ppc32, vmiReg gpr_rt, Uns8 rt) {
    //
    // Test variant and call specific init
    //
    switch (ppc32->configInfo.arch) {
    case VARIANT_M440:
    case VARIANT_M460:
    case VARIANT_M470:
        break;
    case VARIANT_M476:
        ppc32mfmsr_400(ppc32, gpr_rt, rt);
        break;
    default:
        vmiMessage("F", "SPR", "%s variant %s mismatch\n", __FUNCTION__, ppc32->configInfo.name);
        break;
    }
}

void ppc32mtspr(ppc32P ppc32, Uns16 spr, vmiReg gpr_rs, Uns8 rs) {
    //
    // Test variant and call specific init
    //
    switch (ppc32->configInfo.arch) {
    case VARIANT_M440:
    case VARIANT_M460:
    case VARIANT_M470:
        break;
    case VARIANT_M476:
        ppc32mtspr_400(ppc32, spr, gpr_rs, rs);
        break;
    default:
        vmiMessage("F", "SPR", "%s variant %s mismatch\n", __FUNCTION__, ppc32->configInfo.name);
        break;
    }
}

void ppc32mfspr(ppc32P ppc32, Uns8   rt, vmiReg gpr_rt, Uns16 spr) {
    //
    // Test variant and call specific init
    //
    switch (ppc32->configInfo.arch) {
    case VARIANT_M440:
    case VARIANT_M460:
    case VARIANT_M470:
        break;
    case VARIANT_M476:
        ppc32mfspr_400(ppc32,rt, gpr_rt, spr);
        break;
    default:
        vmiMessage("F", "SPR", "%s variant %s mismatch\n", __FUNCTION__, ppc32->configInfo.name);
        break;
    }
}

void ppc32wrteei(ppc32P ppc32, Uns8   E) {
    //
    // Test variant and call specific init
    //
    switch (ppc32->configInfo.arch) {
    case VARIANT_M440:
    case VARIANT_M460:
    case VARIANT_M470:
        break;
    case VARIANT_M476:
        ppc32wrteei_400(ppc32, E);
        break;
    default:
        vmiMessage("F", "SPR", "%s variant %s mismatch\n", __FUNCTION__, ppc32->configInfo.name);
        break;
    }
}

void ppc32wrtee(ppc32P ppc32, vmiReg gpr_rs, Uns8 rs) {
    //
    // Test variant and call specific init
    //
    switch (ppc32->configInfo.arch) {
    case VARIANT_M440:
    case VARIANT_M460:
    case VARIANT_M470:
        break;
    case VARIANT_M476:
        ppc32wrtee_400(ppc32, gpr_rs, rs);
        break;
    default:
        vmiMessage("F", "SPR", "%s variant %s mismatch\n", __FUNCTION__, ppc32->configInfo.name);
        break;
    }
}

Uns32 ppc32ReadSPR (ppc32P ppc32, Uns32 index) {
    //
    // Test variant and call specific init
    //
    switch (ppc32->configInfo.arch) {
    case VARIANT_M440:
    case VARIANT_M460:
    case VARIANT_M470:
        break;
    case VARIANT_M476:
        return ppc32ReadSPR_400 (ppc32, index);
        break;
    default:
        vmiMessage("F", "SPR", "%s variant %s mismatch\n", __FUNCTION__, ppc32->configInfo.name);
        break;
    }

    return 0;
}

void ppc32WriteSPR (ppc32P ppc32, Uns32 index, Uns32 value) {

    //
    // Test variant and call specific init
    //
    switch (ppc32->configInfo.arch) {
    case VARIANT_M440:
    case VARIANT_M460:
    case VARIANT_M470:
        break;
    case VARIANT_M476:
        ppc32WriteSPR_400 (ppc32, index, value);
        break;
    default:
        vmiMessage("F", "SPR", "%s variant %s mismatch\n", __FUNCTION__, ppc32->configInfo.name);
        break;
    }
}

Uns32 ppc32ReadMSR (ppc32P ppc32) {
    //
    // Test variant and call specific init
    //
    switch (ppc32->configInfo.arch) {
    case VARIANT_M440:
    case VARIANT_M460:
    case VARIANT_M470:
        break;
    case VARIANT_M476:
        return ppc32ReadMSR_400 (ppc32);
        break;
    default:
        vmiMessage("F", "SPR", "%s variant %s mismatch\n", __FUNCTION__, ppc32->configInfo.name);
        break;
    }

    return 0;
}

void ppc32WriteMSR (ppc32P ppc32, Uns32 value) {

    //
    // Test variant and call specific init
    //
    switch (ppc32->configInfo.arch) {
    case VARIANT_M440:
    case VARIANT_M460:
    case VARIANT_M470:
        break;
    case VARIANT_M476:
        ppc32WriteMSR_400 (ppc32, value);
        break;
    default:
        vmiMessage("F", "SPR", "%s variant %s mismatch\n", __FUNCTION__, ppc32->configInfo.name);
        break;
    }
}

Uns8 ppc32ReadMSR_VMMode (ppc32P ppc32) {
    //
    // Test variant and call specific init
    //
    switch (ppc32->configInfo.arch) {
    case VARIANT_M440:
    case VARIANT_M460:
    case VARIANT_M470:
        break;
    case VARIANT_M476:
        return ppc32ReadMSR_VMMode_400(ppc32);
        break;
    default:
        vmiMessage("F", "SPR", "%s variant %s mismatch\n", __FUNCTION__, ppc32->configInfo.name);
        break;
    }

    return 0;
}

Bool ppc32IsUserMode(ppc32P ppc32) {
    //
    // Test variant and call specific init
    //
    switch (ppc32->configInfo.arch) {
    case VARIANT_M440:
    case VARIANT_M460:
    case VARIANT_M470:
        break;
    case VARIANT_M476:
        return ppc32IsUserMode_400(ppc32);
        break;
    default:
        vmiMessage("F", "SPR", "%s variant %s mismatch\n", __FUNCTION__, ppc32->configInfo.name);
        break;
    }

    return 0;
}

Bool ppc32IsPrivMode(ppc32P ppc32) {
    //
    // Test variant and call specific init
    //
    switch (ppc32->configInfo.arch) {
    case VARIANT_M440:
    case VARIANT_M460:
    case VARIANT_M470:
        break;
    case VARIANT_M476:
        return ppc32IsPrivMode_400(ppc32);
        break;
    default:
        vmiMessage("F", "SPR", "%s variant %s mismatch\n", __FUNCTION__, ppc32->configInfo.name);
        break;
    }

    return 0;
}

Bool ppc32IsHypvMode(ppc32P ppc32) {
    //
    // Test variant and call specific init
    //
    switch (ppc32->configInfo.arch) {
    case VARIANT_M440:
    case VARIANT_M460:
    case VARIANT_M470:
        break;
    case VARIANT_M476:
        return ppc32IsHypvMode_400(ppc32);
        break;
    default:
        vmiMessage("F", "SPR", "%s variant %s mismatch\n", __FUNCTION__, ppc32->configInfo.name);
        break;
    }

    return 0;
}
