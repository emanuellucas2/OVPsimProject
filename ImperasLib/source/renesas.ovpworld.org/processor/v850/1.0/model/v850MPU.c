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
#include "vmi/vmiRt.h"

#include "v850Structure.h"
#include "v850Exceptions.h"
#include "v850MPU.h"
#include "v850Utils.h"

//
// Invalidate the MPU on any write to the
// Config or address registers
//
static void mpuInvalidate(v850P v850) {
    v850Mode mode = v850GetVMMode(v850);

    Uns32 lo = 0;
    Uns32 hi = -1;

    Bool MPUMode = (mode==RH850_M_USER_MPU) || (mode==RH850_M_SUPERVISOR_MPU);

    if (MPUMode) {
        vmirtProtectMemory(v850->virtDomainD[mode], lo, hi, MEM_PRIV_NONE, MEM_PRIV_SET);
        vmirtProtectMemory(v850->virtDomainC[mode], lo, hi, MEM_PRIV_NONE, MEM_PRIV_SET);

        if (V850_DEBUG_MPU(v850)) {
            // LCOV_EXCL_START
            vmiPrintf("MPU Invalidate\n");
            // LCOV_EXCL_STOP
        }
    }
}

static void memoryMapping(v850P v850) {
    if (V850_DEBUG_MPU(v850)) {
        // LCOV_EXCL_START
        //
        // Print mapping for simulator
        //
        vmiPrintf("Code Domain");
        vmirtDebugDomain(vmirtGetProcessorCodeDomain((vmiProcessorP)v850));
        vmiPrintf("Data Domain");
        vmirtDebugDomain(vmirtGetProcessorDataDomain((vmiProcessorP)v850));
        vmiPrintf("\n");
        // LCOV_EXCL_STOP
    }
}


Bool v850HasMPU(v850P v850) {
    if (v850->configInfo.arch == RH850G3M) {
        return True;
    }
    return False;
}

void v850WriteMPU_MCC(v850P v850, Uns32 value) {
    Uns32 lo = v850->SPR_MCA.MCA;
    Uns32 hi = lo + v850->SPR_MCS.MCS;

    v850->SPR_MCR.reg = 0;

    //
    // if the range crosses 0x00000000 or 0x7FFFFFFF
    // Overflow
    //
    if ((hi < lo) || ((hi > 0x7FFFFFFF) && (lo < 0x7FFFFFFF))) {
        v850->SPR_MCR.OV = 1;
    }

    Uns8 sxe = 0;
    Uns8 swe = 0;
    Uns8 sre = 0;
    Uns8 uxe = 0;
    Uns8 uwe = 0;
    Uns8 ure = 0;

    Uns8 mpu_size = v850->SPR_MPTRGN.MPTRGN;
    v850PrintMPU(v850, mpu_size);
    Int8 i;
    for (i=(mpu_size-1); i>=0; i--) {
        TYPE_SPR_MPLA MPLA = v850->SPR_MPLA[i];
        TYPE_SPR_MPUA MPUA = v850->SPR_MPUA[i];
        TYPE_SPR_MPAT MPAT = v850->SPR_MPAT[i];

        MPUA.RSV0 = 0x3; // Bottom two bits are implicitly set for address (0 for read)

        //
        // If not enabled continue
        //
        if (!MPAT.E) {
            continue;
        }

        //
        // Is not (G)lobal and not ASID
        //
        if (!MPAT.G) {
            if (MPAT.ASID != v850->SPR_ASID.ASID) {
                continue;
            }
        }

        //
        // Illegal range
        //
        if (MPLA.reg > MPUA.reg) {
            vmiMessage("W", "MPU_REGION", "Illegal Range [%d] MPLA=0x%08x MPUA=0x%08x",
                i, MPLA.reg, MPUA.reg);
            continue;
        }

        //
        // Range check
        //
        if ((lo < MPLA.reg) || (hi > MPUA.reg)) {
            continue;
        }

        //
        // Match
        //
        sxe += MPAT.SX;
        swe += MPAT.SW;
        sre += MPAT.SR;
        uxe += MPAT.UX;
        uwe += MPAT.UW;
        ure += MPAT.UR;
    }

    //
    // if 1 and only 1
    //
    if (sxe==1) v850->SPR_MCR.SXE = 1;
    if (swe==1) v850->SPR_MCR.SWE = 1;
    if (sre==1) v850->SPR_MCR.SRE = 1;
    if (uxe==1) v850->SPR_MCR.UXE = 1;
    if (uwe==1) v850->SPR_MCR.UWE = 1;
    if (ure==1) v850->SPR_MCR.URE = 1;
}

void v850WriteMPU_MPM(v850P v850, Uns32 value) {
    Uns32 wmask    = v850->SPR_MPM_wmask.reg;
    Uns32 prev     = v850->SPR_MPM.reg;
    Uns32 prevMASK = prev & ~wmask;
    Uns32 next     = value & wmask;

    v850->SPR_MPM.reg = prevMASK | next;

    if (prev != next) {
        if (V850_DEBUG_MPU(v850)) {
            // LCOV_EXCL_START
            vmiPrintf("MPM %08x -> %08x\n",  prev, next);
            vmiPrintf("  SVP=%d MPE=%d \n",
                v850->SPR_MPM.SVP, v850->SPR_MPM.MPE);
            // LCOV_EXCL_STOP
        }

        v850SetVMMode(v850);
        mpuInvalidate(v850);
    }
}

void v850WriteMPU_MPLA(v850P v850, Uns32 value, Uns32 idx) {
    Uns32 wmask    = v850->SPR_MPLA_wmask[idx].reg;
    Uns32 prev     = v850->SPR_MPLA[idx].reg;
    Uns32 prevMASK = prev & ~wmask;
    Uns32 next     = value & wmask;

    v850->SPR_MPLA[idx].reg = prevMASK | next;

    if (prev != next) {
        if (V850_DEBUG_MPU(v850)) {
            // LCOV_EXCL_START
            vmiPrintf("MPLA[%d] %08x -> %08x\n", idx, prev, next);
            // LCOV_EXCL_STOP
        }

        mpuInvalidate(v850);
    }
}
void v850WriteMPU_MPUA(v850P v850, Uns32 value, Uns32 idx) {
    Uns32 wmask    = v850->SPR_MPUA_wmask[idx].reg;
    Uns32 prev     = v850->SPR_MPUA[idx].reg;
    Uns32 prevMASK = prev & ~wmask;
    Uns32 next     = value & wmask;

    v850->SPR_MPUA[idx].reg = prevMASK | next;    // bits 1-0 implicitly set to 1

    if (prev != next) {
        if (V850_DEBUG_MPU(v850)) {
            // LCOV_EXCL_START
            vmiPrintf("MPUA[%d] %08x -> %08x\n", idx, prev, next);
            // LCOV_EXCL_STOP
        }

        mpuInvalidate(v850);
    }
}

void v850WriteMPU_MPAT(v850P v850, Uns32 value, Uns32 idx) {
    Uns32 wmask    = v850->SPR_MPAT_wmask[idx].reg;
    Uns32 prev     = v850->SPR_MPAT[idx].reg;
    Uns32 prevMASK = prev & ~wmask;
    Uns32 next     = value & wmask;

    v850->SPR_MPAT[idx].reg = prevMASK | next;

    if (prev != next) {
        if (V850_DEBUG_MPU(v850)) {
            // LCOV_EXCL_START
            vmiPrintf("MPAT[%d] %08x -> %08x\n", idx, prev, next);
            vmiPrintf("  ASID=%04d E=%d G=%d S[X=%d W=%d R=%d] U[X=%d W=%d R=%d]\n",
                v850->SPR_MPAT[idx].ASID, v850->SPR_MPAT[idx].E,  v850->SPR_MPAT[idx].G,
                v850->SPR_MPAT[idx].SX,   v850->SPR_MPAT[idx].SW, v850->SPR_MPAT[idx].SR,
                v850->SPR_MPAT[idx].UX,   v850->SPR_MPAT[idx].UW, v850->SPR_MPAT[idx].UR
                );
            // LCOV_EXCL_STOP
        }
        //
        // Copy to MPRC
        //
        Uns32 E = v850->SPR_MPAT[idx].E << idx;
        Uns32 mask = 1 << idx;
        mask = ~mask;
        v850->SPR_MPRC.E &= mask;
        v850->SPR_MPRC.E |= E;

        mpuInvalidate(v850);
    }
}

void v850WriteMPU_MPRC(v850P v850, Uns32 value) {
    Uns32 wmask    = v850->SPR_MPRC_wmask.reg;
    Uns32 prev     = v850->SPR_MPRC.reg;
    Uns32 prevMASK = prev & ~wmask;
    Uns32 next     = value & wmask;

    v850->SPR_MPRC.reg = prevMASK | next;

    if (prev != next) {
        if (V850_DEBUG_MPU(v850)) {
            // LCOV_EXCL_START
           vmiPrintf("MPRC %08x -> %08x\n",  prev, next);
           // LCOV_EXCL_STOP
        }
        //
        // Copy to MPAT
        //
        Uns8 i;
        for(i=0; i<16; i++) {
            Uns8 E = (v850->SPR_MPRC.E >> i) & 0x1;
            v850->SPR_MPAT[i].E = E;
        }

        mpuInvalidate(v850);
    }
}


Bool v850MPUMiss(
    v850P          v850,
    memPriv        action,
    Uns32          VA,
    memAccessAttrs attrs
) {

    Bool isMapped = False;

    char R = (action & MEM_PRIV_R) ? 'r' : '-';
    char W = (action & MEM_PRIV_W) ? 'w' : '-';
    char X = (action & MEM_PRIV_X) ? 'x' : '-';

    //
    // Check Mode
    //
    v850Mode mode = v850GetVMMode(v850);
    // RH850_M_SUPERVISOR     =           um==0 && svp==0
    // RH850_M_USER           = mpe==0 && um==1
    // RH850_M_SUPERVISOR_MPU = mpe==1 && um==0 && svp==1
    // RH850_M_USER_MPU       = mpe==1 && um==1

    if ((mode==RH850_M_SUPERVISOR) || (mode==RH850_M_USER)) {
        isMapped = True;
    }

    //
    // Iterate the MPU for address Match
    // Highest priority usually 0
    //
    Uns8 mpu_size = v850->SPR_MPTRGN.MPTRGN;
    v850PrintMPU(v850, mpu_size);
    Int8 i;
    for (i=(mpu_size-1); i>=0; i--) {
        TYPE_SPR_MPLA MPLA = v850->SPR_MPLA[i];
        TYPE_SPR_MPUA MPUA = v850->SPR_MPUA[i];
        TYPE_SPR_MPAT MPAT = v850->SPR_MPAT[i];

        MPUA.RSV0 = 0x3; // Bottom two bits are implicitly set for address (0 for read)

        //
        // If not enabled continue
        //
        if (!MPAT.E) {
            continue;
        }

        //
        // Is not (G)lobal and not ASID
        //
        if (!MPAT.G) {
            if (MPAT.ASID != v850->SPR_ASID.ASID) {
                continue;
            }
        }

        //
        // Illegal range
        //
        if (MPLA.reg > MPUA.reg) {
            vmiMessage("W", "MPU_REGION", "Illegal Range [%d] MPLA=0x%08x MPUA=0x%08x",
                i, MPLA.reg, MPUA.reg);
            continue;
        }

        //
        // If not in range continue
        //
        if ((VA < MPLA.reg) || (VA > MPUA.reg)) {
            continue;
        }

        //
        // Generate privilege value
        //
        memPriv priv = MEM_PRIV_NONE;
        if (mode==RH850_M_SUPERVISOR_MPU) {
            priv |= MPAT.SR ? MEM_PRIV_R : 0;
            priv |= MPAT.SW ? MEM_PRIV_W : 0;
            priv |= MPAT.SX ? MEM_PRIV_X : 0;

        } else if (mode==RH850_M_USER_MPU) {
            priv |= MPAT.UR ? MEM_PRIV_R : 0;
            priv |= MPAT.UW ? MEM_PRIV_W : 0;
            priv |= MPAT.UX ? MEM_PRIV_X : 0;
        }

        //
        // If permissions Match
        //
        if ((action & MEM_PRIV_RW) && (action & priv)) {
            if (V850_DEBUG_MPU(v850)) {
                // LCOV_EXCL_START
                vmiPrintf("MPU Check Data VA=%08x %c%c%c - OK\n\n", VA, R, W, X);
                // LCOV_EXCL_STOP
            }
            vmirtProtectMemory(v850->virtDomainD[mode], MPLA.reg, MPUA.reg, priv, MEM_PRIV_SET);
            isMapped = True;

        } else if ((action & MEM_PRIV_X) && (action & priv)) {
            if (V850_DEBUG_MPU(v850)) {
                // LCOV_EXCL_START
                vmiPrintf("MPU Check Code VA=%08x %c%c%c - OK\n\n", VA, R, W, X);
                // LCOV_EXCL_STOP
            }
            vmirtProtectMemory(v850->virtDomainC[mode], MPLA.reg, MPUA.reg, priv, MEM_PRIV_SET);
            isMapped = True;
        }
        memoryMapping(v850);
    }

    if (isMapped) {
        return False;
    } else {
        //
        // If this is a real access
        //
        if(MEM_AA_IS_TRUE_ACCESS(attrs)) {
            v850MPUMissException(v850, action, VA);
        }
    }

    if (V850_DEBUG_MPU(v850)) {
        // LCOV_EXCL_START
        vmiPrintf("MPU Check VA=%08x %c%c%c - FAIL\n\n", VA, R, W, X);
        // LCOV_EXCL_STOP
    }

    return True;
}

void v850PrintMPU(v850P v850, Uns8 mpu_size) {
    if (V850_DEBUG_MPU(v850)) {
        // LCOV_EXCL_START
        Int8 i;
        vmiPrintf("##################################################\n");
        vmiPrintf("################## MPU Settings ##################\n");
        vmiPrintf("##################################################\n");
        vmiPrintf("PSW.UM=%d\n", v850->SPR_PSW.UM);
        vmiPrintf("MPBRGN=%d MPTRGN=%d MCA=%08X MCS=%08X MCC=%08X\n",
            v850->SPR_MPBRGN.MPBRGN, v850->SPR_MPTRGN.MPTRGN,
            v850->SPR_MCA.MCA, v850->SPR_MCS.MCS, v850->SPR_MCC.MCC);
        vmiPrintf("MCR  URE=%d UWE=%d UXE=%d SRE=%d SWE=%d SXE=%d OV=%d\n",
            v850->SPR_MCR.URE, v850->SPR_MCR.UWE, v850->SPR_MCR.UXE,
            v850->SPR_MCR.SRE, v850->SPR_MCR.SWE, v850->SPR_MCR.SXE,
            v850->SPR_MCR.OV);
        vmiPrintf("MPM  MPE=%d SVP=%d DR=%d DW=%d DX=%d\n",
            v850->SPR_MPM.MPE,
            v850->SPR_MPM.SVP,
            v850->SPR_MPM.DR, v850->SPR_MPM.DW, v850->SPR_MPM.DX);
        vmiPrintf("MPBRGN=%d MPTRGN=%d\n", v850->SPR_MPBRGN.MPBRGN, v850->SPR_MPTRGN.MPTRGN);
        vmiPrintf("ASID=%-4d\n", v850->SPR_ASID.ASID);
        vmiPrintf("TABLE\n");
        vmiPrintf("  ID EN LO       HI       UR UW UX SR SW SX G  E  ASID\n");
        for (i=0; i<mpu_size; i++) {
            Uns32 lo = v850->SPR_MPLA[i].reg;
            Uns32 hi = v850->SPR_MPUA[i].reg;
            Uns8  en = (v850->SPR_MPRC.E >> i) & 0x1;
            vmiPrintf("  %-2d ", i); // 0-15
            vmiPrintf("%1d  ", en);
            vmiPrintf("%08X ", lo);
            vmiPrintf("%08X ", hi);
            vmiPrintf("%1d  ", v850->SPR_MPAT[i].UR);
            vmiPrintf("%1d  ", v850->SPR_MPAT[i].UW);
            vmiPrintf("%1d  ", v850->SPR_MPAT[i].UX);
            vmiPrintf("%1d  ", v850->SPR_MPAT[i].SR);
            vmiPrintf("%1d  ", v850->SPR_MPAT[i].SW);
            vmiPrintf("%1d  ", v850->SPR_MPAT[i].SX);
            vmiPrintf("%1d  ", v850->SPR_MPAT[i].G);
            vmiPrintf("%1d  ", v850->SPR_MPAT[i].E);
            vmiPrintf("%-4d ", v850->SPR_MPAT[i].ASID);
            vmiPrintf("\n");
        }
        vmiPrintf("\n");
        // LCOV_EXCL_STOP
    }
}
