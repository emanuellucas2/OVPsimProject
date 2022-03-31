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
#include "vmi/vmiCxt.h"
#include "ppc32Functions.h"
#include "ppc32Decode.h"
#include "ppc32Instructions.h"
#include "ppc32Utils.h"
#include "ppc32MorphFP.h"

#define TRC 0

VMI_ENDIAN_FN(ppc32GetEndian) {
    ppc32P ppc32 = (ppc32P)processor;
    if (isFetch) {
        return ppc32->iendian;
    } else {
        return ppc32->dendian;
    }
}

VMI_NEXT_PC_FN(ppc32nextPC) {
    ppc32InstructionInfo info = {0};
    ppc32Decode((ppc32P)processor, thisPC, &info);
    ppc32Addr nextAddress = info.nextPC;
    return nextAddress;
}

/*
 * Forward reference
 */
static void updateExclusiveAccessCallback(ppc32P ppc32, Bool install);

static VMI_MEM_WATCH_FN(abortEA) {
    if (processor) {
        ppc32P ppc32 = (ppc32P)userData;
        ppc32->RESERVE = False;
//        vmiPrintf("abortEA at executing %s PC=0x%08x aborting %s PC=0x%08x\n",
//                vmirtProcessorName(processor), (Uns32)vmirtGetPC(processor),
//                vmirtProcessorName(userData),  (Uns32)vmirtGetPC(userData));
        updateExclusiveAccessCallback(ppc32, False);
    }
}

static void updateExclusiveAccessCallback(ppc32P ppc32, Bool install) {
    memDomainP domain  = vmirtGetProcessorDataDomain((vmiProcessorP)ppc32);
    Uns32      simLow  = ppc32->RESERVE_ADDR;
    Uns32      simHigh = ppc32->RESERVE_ADDR + ppc32->RESERVE_LENGTH - 1;

    if (install) {
        vmirtAddWriteCallback(domain, 0, simLow, simHigh, abortEA, ppc32);
    } else {
        vmirtRemoveWriteCallback(domain, 0, simLow, simHigh, abortEA, ppc32);
    }
}

VMI_IASSWITCH_FN(ppc32Switch) {
    ppc32P ppc32 = (ppc32P)processor;
    if (ppc32->RESERVE) {
        updateExclusiveAccessCallback(ppc32, (state==RS_SUSPEND));
    }
}

//
// Packing and Unpacking Functions
//
void ppc32PackCR(ppc32P ppc32) {
    ppc32->CR.bits.CR0 = ((ppc32->LT[0] & 0x1) << 3) | ((ppc32->GT[0] & 0x1) << 2) | ((ppc32->EQ[0] & 0x1) << 1) | ((ppc32->SO[0] & 0x1) << 0) ;
    ppc32->CR.bits.CR1 = ((ppc32->LT[1] & 0x1) << 3) | ((ppc32->GT[1] & 0x1) << 2) | ((ppc32->EQ[1] & 0x1) << 1) | ((ppc32->SO[1] & 0x1) << 0) ;
    ppc32->CR.bits.CR2 = ((ppc32->LT[2] & 0x1) << 3) | ((ppc32->GT[2] & 0x1) << 2) | ((ppc32->EQ[2] & 0x1) << 1) | ((ppc32->SO[2] & 0x1) << 0) ;
    ppc32->CR.bits.CR3 = ((ppc32->LT[3] & 0x1) << 3) | ((ppc32->GT[3] & 0x1) << 2) | ((ppc32->EQ[3] & 0x1) << 1) | ((ppc32->SO[3] & 0x1) << 0) ;
    ppc32->CR.bits.CR4 = ((ppc32->LT[4] & 0x1) << 3) | ((ppc32->GT[4] & 0x1) << 2) | ((ppc32->EQ[4] & 0x1) << 1) | ((ppc32->SO[4] & 0x1) << 0) ;
    ppc32->CR.bits.CR5 = ((ppc32->LT[5] & 0x1) << 3) | ((ppc32->GT[5] & 0x1) << 2) | ((ppc32->EQ[5] & 0x1) << 1) | ((ppc32->SO[5] & 0x1) << 0) ;
    ppc32->CR.bits.CR6 = ((ppc32->LT[6] & 0x1) << 3) | ((ppc32->GT[6] & 0x1) << 2) | ((ppc32->EQ[6] & 0x1) << 1) | ((ppc32->SO[6] & 0x1) << 0) ;
    ppc32->CR.bits.CR7 = ((ppc32->LT[7] & 0x1) << 3) | ((ppc32->GT[7] & 0x1) << 2) | ((ppc32->EQ[7] & 0x1) << 1) | ((ppc32->SO[7] & 0x1) << 0) ;
}

void ppc32UnpackCR(ppc32P ppc32) {
    ppc32->LT[0] = (ppc32->CR.bits.CR0 >> 3) & 0x1;
    ppc32->GT[0] = (ppc32->CR.bits.CR0 >> 2) & 0x1;
    ppc32->EQ[0] = (ppc32->CR.bits.CR0 >> 1) & 0x1;
    ppc32->SO[0] = (ppc32->CR.bits.CR0 >> 0) & 0x1;
    ppc32->LT[1] = (ppc32->CR.bits.CR1 >> 3) & 0x1;
    ppc32->GT[1] = (ppc32->CR.bits.CR1 >> 2) & 0x1;
    ppc32->EQ[1] = (ppc32->CR.bits.CR1 >> 1) & 0x1;
    ppc32->SO[1] = (ppc32->CR.bits.CR1 >> 0) & 0x1;
    ppc32->LT[2] = (ppc32->CR.bits.CR2 >> 3) & 0x1;
    ppc32->GT[2] = (ppc32->CR.bits.CR2 >> 2) & 0x1;
    ppc32->EQ[2] = (ppc32->CR.bits.CR2 >> 1) & 0x1;
    ppc32->SO[2] = (ppc32->CR.bits.CR2 >> 0) & 0x1;
    ppc32->LT[3] = (ppc32->CR.bits.CR3 >> 3) & 0x1;
    ppc32->GT[3] = (ppc32->CR.bits.CR3 >> 2) & 0x1;
    ppc32->EQ[3] = (ppc32->CR.bits.CR3 >> 1) & 0x1;
    ppc32->SO[3] = (ppc32->CR.bits.CR3 >> 0) & 0x1;
    ppc32->LT[4] = (ppc32->CR.bits.CR4 >> 3) & 0x1;
    ppc32->GT[4] = (ppc32->CR.bits.CR4 >> 2) & 0x1;
    ppc32->EQ[4] = (ppc32->CR.bits.CR4 >> 1) & 0x1;
    ppc32->SO[4] = (ppc32->CR.bits.CR4 >> 0) & 0x1;
    ppc32->LT[5] = (ppc32->CR.bits.CR5 >> 3) & 0x1;
    ppc32->GT[5] = (ppc32->CR.bits.CR5 >> 2) & 0x1;
    ppc32->EQ[5] = (ppc32->CR.bits.CR5 >> 1) & 0x1;
    ppc32->SO[5] = (ppc32->CR.bits.CR5 >> 0) & 0x1;
    ppc32->LT[6] = (ppc32->CR.bits.CR6 >> 3) & 0x1;
    ppc32->GT[6] = (ppc32->CR.bits.CR6 >> 2) & 0x1;
    ppc32->EQ[6] = (ppc32->CR.bits.CR6 >> 1) & 0x1;
    ppc32->SO[6] = (ppc32->CR.bits.CR6 >> 0) & 0x1;
    ppc32->LT[7] = (ppc32->CR.bits.CR7 >> 3) & 0x1;
    ppc32->GT[7] = (ppc32->CR.bits.CR7 >> 2) & 0x1;
    ppc32->EQ[7] = (ppc32->CR.bits.CR7 >> 1) & 0x1;
    ppc32->SO[7] = (ppc32->CR.bits.CR7 >> 0) & 0x1;
}

//
// Writes to some of the register flags can either be direct
// using a move to FPSCR type of command
// or indirect via an arithmetic operation, in which case
// the values are held in FPU_REL, FPU_FLG and FLG_FP_SI
//
void ppc32PackFPSCR(ppc32P ppc32) {
    //
    // If we last performed an arith op, update these fields
    // from FPU_REL, FLG_FPF and FLG_FP_SI
    //
    Bool Infinity  =
            (ppc32->FPU_RES==0x7FF0000000000000ULL) ||
            (ppc32->FPU_RES==0xFFF0000000000000ULL);
    Bool Negzero  =
            (ppc32->FPU_RES==0x8000000000000000ULL);

    Bool UnorderedRel   = (ppc32->FPU_REL & FPUREL_UN) ? 1: 0; // Unordered (NaN)
    Bool LessThanRel    = (ppc32->FPU_REL & FPUREL_LT) ? 1: 0; // LessThan
    Bool GreaterThanRel = (ppc32->FPU_REL & FPUREL_GT) ? 1: 0; // GreaterThan
    Bool EqualToRel     = (ppc32->FPU_REL & FPUREL_EQ) ? 1: 0; // EqualTo

    Bool DenormalOutFlag= (ppc32->CMP_FLG & FPFLAGS_D) ? 1: 0; // Denormal Result flag

    // FPSCR bits
#if (TRC==1)
    Bool InvalidOpFlag  = (ppc32->FPU_FLG & FPFLAGS_I) ? 1: 0; // Invalid operation flag
    Bool DenormalInFlag = (ppc32->FPU_FLG & FPFLAGS_D) ? 1: 0; // Denormal operand flag
#endif
    Bool InexactFlag    = (ppc32->FPU_FLG & FPFLAGS_P) ? 1: 0; // Precision flag

    //
    // Set from Sticky Bits
    //
    ppc32->FPSCR.bits.VXCVI  = ppc32->FLG_FPSCR_VXCVI;
    ppc32->FPSCR.bits.VXSQRT = ppc32->FLG_FPSCR_VXSQRT;
    ppc32->FPSCR.bits.VXSOFT = ppc32->FLG_FPSCR_VXSOFT;
    ppc32->FPSCR.bits.VXVC   = ppc32->FLG_FPSCR_VXVC;
    ppc32->FPSCR.bits.VXIMZ  = ppc32->FLG_FPSCR_VXIMZ;
    ppc32->FPSCR.bits.VXZDZ  = ppc32->FLG_FPSCR_VXZDZ;
    ppc32->FPSCR.bits.VXIDI  = ppc32->FLG_FPSCR_VXIDI;
    ppc32->FPSCR.bits.VXISI  = ppc32->FLG_FPSCR_VXISI;
    ppc32->FPSCR.bits.VXSNAN = ppc32->FLG_FPSCR_VXSNAN;
    ppc32->FPSCR.bits.ZX     = (ppc32->FPU_FLG_STICKY & FPFLAGS_Z) ? 1: 0; // Divide-By-Zero flag
    ppc32->FPSCR.bits.UX     = (ppc32->FPU_FLG_STICKY & FPFLAGS_U) ? 1: 0; // Underflow flag
    ppc32->FPSCR.bits.OX     = (ppc32->FPU_FLG_STICKY & FPFLAGS_O) ? 1: 0; // Overflow flag

    //
    // Storage of the bits to indicate EQ/LT/GT
    // This should only be done when this is not
    // a direct write to the registers
    //
    ppc32->FPSCR.bits.FL = LessThanRel;
    ppc32->FPSCR.bits.FG = GreaterThanRel;
    ppc32->FPSCR.bits.FE = EqualToRel;
    ppc32->FPSCR.bits.FU = (UnorderedRel | Infinity) ? 1: 0;
    ppc32->FPSCR.bits.FI = InexactFlag;

    ppc32->FPSCR.bits.VX =
        ppc32->FPSCR.bits.VXCVI  |
        ppc32->FPSCR.bits.VXSQRT |
        ppc32->FPSCR.bits.VXSOFT |
        ppc32->FPSCR.bits.VXVC   |
        ppc32->FPSCR.bits.VXIMZ  |
        ppc32->FPSCR.bits.VXZDZ  |
        ppc32->FPSCR.bits.VXIDI  |
        ppc32->FPSCR.bits.VXISI  |
        ppc32->FPSCR.bits.VXSNAN;

    //
    // Flags which are only updated by other flags
    // set in non-move operations
    //
//    vmiFBinop       fbinOp = (ppc32->FPU_OP >>  8) & 0xff;
//    vmiFUnop         funOp = (ppc32->FPU_OP >>  8) & 0xff;
    ppc32fpuOpTypeE  fpuOp = (ppc32->FPU_OP >>  0) & 0xff;

    if (fpuOp == FPUOP_TernopRRRR || fpuOp == FPUOP_BinopRRR  || fpuOp == FPUOP_CompareRR ||
        fpuOp == FPUOP_ConvertRR  || fpuOp == FPUOP_FRSP      || fpuOp == FPUOP_UnopRR
        ) {
        //
        // This seems to contradict the documentation, but matches the reference model
        //
        ppc32->FPSCR.bits.XX = (ppc32->FPU_FLG_STICKY & FPFLAGS_P) ? 1: 0; // Precision flag

        //
        // Compound flags
        //
        ppc32->FPSCR.bits.FX =
            ppc32->FPSCR.bits.VX |
            ppc32->FPSCR.bits.OX |
            ppc32->FPSCR.bits.UX |
            ppc32->FPSCR.bits.ZX |
            ppc32->FPSCR.bits.XX;
    }

    //
    // C Bit only set on certain ops
    //
    if (fpuOp == FPUOP_TernopRRRR || fpuOp == FPUOP_BinopRRR || fpuOp == FPUOP_FRSP ||
        fpuOp == FPUOP_UnopRR
        ) {
        ppc32->FPSCR.bits.C   = // unordered, denormal(Output), -zero
            (UnorderedRel && !Infinity) |
            DenormalOutFlag |
            (ppc32->FLG_FP_SI & ppc32->FPSCR.bits.FE) |
            Negzero;
    }
    //
    // Reset the OP flag
    //
    ppc32->FPU_OP = FPUOP_None;

    ppc32->FPSCR.bits.FEX =
        (ppc32->FPSCR.bits.VX & ppc32->FPSCR.bits.VE) |
        (ppc32->FPSCR.bits.OX & ppc32->FPSCR.bits.OE) |
        (ppc32->FPSCR.bits.UX & ppc32->FPSCR.bits.UE) |
        (ppc32->FPSCR.bits.ZX & ppc32->FPSCR.bits.ZE) |
        (ppc32->FPSCR.bits.XX & ppc32->FPSCR.bits.XE);

    //
    // Dump Flags
    //
#if (TRC==1)
    vmiPrintf("FPU: ppc32PackFPSCR\n");
    vmiPrintf("FPU: FPU_FLG                = 0x%02x\n", ppc32->FPU_FLG);
    vmiPrintf("FPU: CNV32_FLG              = 0x%02x\n", ppc32->CNV32_FLG);
    vmiPrintf("FPU: CNV64_FLG              = 0x%02x\n", ppc32->CNV64_FLG);
    vmiPrintf("FPU: FPU_REL                = 0x%02x\n", ppc32->FPU_REL);
    vmiPrintf("FPU: FPU_RES                = 0x" FMT_640Nx "\n", ppc32->FPU_RES);
    vmiPrintf("FPU: CNV32_REL              = 0x%02x\n", ppc32->CNV32_REL);
    vmiPrintf("FPU: Invalid operation flag = %d\n", InvalidOpFlag);
    vmiPrintf("FPU: Denormal Input flag    = %d\n", DenormalInFlag);
    vmiPrintf("FPU: Denormal Output flag   = %d\n", DenormalOutFlag);
    vmiPrintf("FPU: Divide-By-Zero flag    = %d\n", ppc32->FPSCR.bits.ZX);
    vmiPrintf("FPU: Overflow flag          = %d\n", ppc32->FPSCR.bits.OX);
    vmiPrintf("FPU: Underflow flag         = %d\n", ppc32->FPSCR.bits.UX);
    vmiPrintf("FPU: Precision flag         = %d\n", ppc32->FPSCR.bits.FI);
    vmiPrintf("FPU: UnorderedRel           = %d\n", UnorderedRel);
    vmiPrintf("FPU: LessThanRel            = %d\n", LessThanRel);
    vmiPrintf("FPU: GreaterThanRel         = %d\n", GreaterThanRel);
    vmiPrintf("FPU: EqualToRel             = %d\n", EqualToRel);
    vmiPrintf("FPU: Infinity               = %d\n", Infinity);
    vmiPrintf("\n");
#endif

    ppc32UpdateFPControlWord(ppc32);
}

void ppc32UnpackFPSCR(ppc32P ppc32) {
    //
    // Flush the result to zero
    //
    ppc32->FPU_RES = 0;

    //
    // Store bits -> FPU_FLG/STICKY
    //
    ppc32->FPU_FLG = 0;
//    ppc32->FPU_FLG |= (ppc32->FPSCR.bits.?? == 1) ? FPFLAGS_I : 0; // Invalid
//    ppc32->FPU_FLG |= (ppc32->FPSCR.bits.?? == 1) ? FPFLAGS_D : 0; // Denormal
    ppc32->FPU_FLG        |= (ppc32->FPSCR.bits.ZX == 1) ? FPFLAGS_Z : 0; // Divide-By-Zero
    ppc32->FPU_FLG        |= (ppc32->FPSCR.bits.OX == 1) ? FPFLAGS_O : 0; // Overflow
    ppc32->FPU_FLG        |= (ppc32->FPSCR.bits.UX == 1) ? FPFLAGS_U : 0; // Underflow
    ppc32->FPU_FLG        |= (ppc32->FPSCR.bits.FI == 1) ? FPFLAGS_P : 0; // Precision
    ppc32->FPU_FLG_STICKY  =  ppc32->FPU_FLG;
    ppc32->FPU_FLG_STICKY |= (ppc32->FPSCR.bits.XX == 1) ? FPFLAGS_P : 0; // Precision (sticky)

    ppc32->FLG_FP_SI    = 0;

    //
    // Store bits -> FPU_REL
    //
    ppc32->FPU_REL = 0;
    ppc32->FPU_REL |= (ppc32->FPSCR.bits.FU == 1) ? FPUREL_UN : 0; // Unordered
    ppc32->FPU_REL |= (ppc32->FPSCR.bits.FE == 1) ? FPUREL_EQ : 0; // Zero
    ppc32->FPU_REL |= (ppc32->FPSCR.bits.FL == 1) ? FPUREL_LT : 0; // Less Than
    ppc32->FPU_REL |= (ppc32->FPSCR.bits.FG == 1) ? FPUREL_GT : 0; // Greater Than

    //
    // Set the remaining sticky Flags
    //
    ppc32->FLG_FPSCR_VXCVI  = ppc32->FPSCR.bits.VXCVI;
    ppc32->FLG_FPSCR_VXSQRT = ppc32->FPSCR.bits.VXSQRT;
    ppc32->FLG_FPSCR_VXSOFT = ppc32->FPSCR.bits.VXSOFT;
    ppc32->FLG_FPSCR_VXVC   = ppc32->FPSCR.bits.VXVC;
    ppc32->FLG_FPSCR_VXIMZ  = ppc32->FPSCR.bits.VXIMZ;
    ppc32->FLG_FPSCR_VXZDZ  = ppc32->FPSCR.bits.VXZDZ;
    ppc32->FLG_FPSCR_VXIDI  = ppc32->FPSCR.bits.VXIDI;
    ppc32->FLG_FPSCR_VXISI  = ppc32->FPSCR.bits.VXISI;
    ppc32->FLG_FPSCR_VXSNAN = ppc32->FPSCR.bits.VXSNAN;
}

void ppc32PackMSR(ppc32P ppc32) {
}

void ppc32UnpackMSR(ppc32P ppc32) {
}

void ppc32PackXER(ppc32P ppc32) {
    ppc32->XER.bits.SO = ppc32->XER_SO;
    ppc32->XER.bits.OV = ppc32->XER_OV;
    ppc32->XER.bits.CA = ppc32->XER_CA;
}

void ppc32UnpackXER(ppc32P ppc32) {
    ppc32->XER_SO = ppc32->XER.bits.SO;
    ppc32->XER_OV = ppc32->XER.bits.OV;
    ppc32->XER_CA = ppc32->XER.bits.CA;
}

void ppc32PackRegs(ppc32P ppc32) {
    ppc32PackCR(ppc32);
    ppc32PackFPSCR(ppc32);
    ppc32PackMSR(ppc32);
    ppc32PackXER(ppc32);
}

void ppc32UnpackRegs(ppc32P ppc32) {
    ppc32UnpackCR(ppc32);
    ppc32UnpackFPSCR(ppc32);
    ppc32UnpackMSR(ppc32);
    ppc32UnpackXER(ppc32);
}

//
// mask is a pointer to the mask register in the structure
// left and right are the indices 0..31, so reverse format
//
void ppc32MaskEnable64(Uns64 *mask, Bool Enable, Uns64 left, Uns64 right) {
    //
    // set bits left downto right (inclusive) to be the value '1' in the mask
    //
    Uns64 l = 63 - left;
    Uns64 r = 63 - right;
    Uns64 addmask = 0xffffffffffffffffULL;

    if (Enable) {
        *mask |= VECINDEX(addmask, l, r, r);
    } else {
        *mask &= ~(VECINDEX(addmask, l, r, r));
    }
}
