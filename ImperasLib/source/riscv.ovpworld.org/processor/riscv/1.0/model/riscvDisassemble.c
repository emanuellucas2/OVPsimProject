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

// standard includes
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// VMI header files
#include "vmi/vmiMessage.h"

// model header files
#include "riscvCSR.h"
#include "riscvDecode.h"
#include "riscvDecodeTypes.h"
#include "riscvDisassemble.h"
#include "riscvDisassembleFormats.h"
#include "riscvFunctions.h"
#include "riscvModelCallbackTypes.h"
#include "riscvUtils.h"


//
// Prefix for messages from this module
//
#define CPU_PREFIX "RISCV_DISASS"


////////////////////////////////////////////////////////////////////////////////
// UTILITY FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

//
// Append the character to the result
//
static void putChar(char **result, char ch) {

    // get the tail pointer
    char *tail = *result;

    // do the append
    *tail++ = ch;

    // add null terminator
    *tail = 0;

    // update the tail pointer
    *result = tail;
}

//
// Append the string to the result
//
static void putString(char **result, const char *string) {

    // get the tail pointer
    char *tail = *result;
    char  ch;

    // do the append
    while((ch=*string++)) {
        *tail++ = ch;
    }

    // add null terminator
    *tail = 0;

    // update the tail pointer
    *result = tail;
}

//
// Emit key for uncooked value if required
//
static void putUncookedKey(char **result, const char *key, Bool uncooked) {
    if(uncooked) {
        putString(result, key);
        putChar(result, ':');
    }
}

//
// Return number of members of an array
//
#define NUM_MEMBERS(_A) (sizeof(_A)/sizeof((_A)[0]))

//
// This defines the minimum string width to use for the opcode
//
#define OP_WIDTH 7

//
// Return mask for the given number of bits
//
inline static Uns64 getMask(Uns32 bits) {
    return (bits==64) ? -1 : ((1ULL<<bits)-1);
}

//
// Emit instruction format if required
//
static void putInstruction(riscvInstrInfoP info, char **result) {

    const char *fmt;

    // select format string
    if(info->bytes==2) {
        fmt = FMT_6404x"     ";
    } else {
        fmt = FMT_6408x" ";
    }

    // mask raw instruction pattern to instruction byte size (prevents
    // misleading disassembly when compressed instruction encountered by
    // processor that does not support such instructions)
    Uns64 instruction = info->instruction & getMask(info->bytes*8);

    // emit basic opcode string
    *result += sprintf(*result, fmt, instruction);
}

//
// Append comma separator, unless previous character is space or comma (allows
// for omitted optional arguments)
//
static void putComma(char **result, Bool uncooked) {

    if(!uncooked) {

        char *tail = *result;

        switch(tail[-1]) {
            case ',':
            case ' ':
                break;
            default:
                putChar(result, ',');
                break;
        }
    }
}

//
// Emit signed argument
//
static void putD(char **result, Uns64 value) {
    *result += sprintf(*result, FMT_Ad, value);
}

//
// Emit hexadeximal argument
//
static void putX(char **result, Uns64 value) {
    *result += sprintf(*result, "0x"FMT_Ax, value);
}

//
// Emit target address argument
//
static void putTarget(char **result, Uns64 value) {
    *result += sprintf(*result, FMT_Ax, value);
}

//
// Emit register argument
//
static void putReg(
    char       **result,
    riscvP       riscv,
    riscvRegDesc r,
    Bool         opt,
    Bool         uncooked
) {
    Uns32 index = getRIndex(r);

    if(opt && !uncooked && !index && isXReg(r)) {
        // omit zero register
    } else if(isXReg(r) || isZfinxReg(r)) {
        putString(result, riscvGetXRegName(riscv, index));
    } else if(isFReg(r)) {
        putString(result, riscvGetFRegName(riscv, index));
    } else if(isVReg(r)) {
        putString(result, riscvGetVRegName(riscv, index));
    } else {
        VMI_ABORT("Bad register specifier 0x%x", r); // LCOV_EXCL_LINE
    }
}

//
// Emit optional mask register argument
//
static void putOptMask(
    char       **result,
    riscvP       riscv,
    riscvRegDesc mask,
    const char  *suffix,
    Bool         uncooked
) {
    if(mask) {

        putUncookedKey(result, " MASK", uncooked);

        putString(result, riscvGetVRegName(riscv, getRIndex(mask)));

        if(!uncooked) {
            putString(result, suffix);
        }
    }
}

//
// Emit rlist argument
//
static void putRlist(char **result, riscvRListDesc rlist) {

    static const char *map[] = {
        [RV_RL_x_RA]           = "{ra}",
        [RV_RL_x_RA_S0]        = "{ra,s0}",
        [RV_RL_x_RA_S0_1]      = "{ra,s0-s1}",
        [RV_RL_U_RA_S0_2]      = "{ra,s0-s2}",
        [RV_RL_U_RA_S0_3]      = "{ra,s0-s3}",
        [RV_RL_U_RA_S0_4]      = "{ra,s0-s4}",
        [RV_RL_U_RA_S0_5]      = "{ra,s0-s5}",
        [RV_RL_U_RA_S0_6]      = "{ra,s0-s6}",
        [RV_RL_U_RA_S0_7]      = "{ra,s0-s7}",
        [RV_RL_U_RA_S0_8]      = "{ra,s0-s8}",
        [RV_RL_U_RA_S0_9]      = "{ra,s0-s9}",
        [RV_RL_U_RA_S0_10]     = "{ra,s0-s10}",
        [RV_RL_U_RA_S0_11]     = "{ra,s0-s11}",
        [RV_RL_E_RA_S0_2]      = "{ra,s0-s2}",
        [RV_RL_E_RA_S3_S0_2]   = "{ra,s3,s0-s2}",
        [RV_RL_E_RA_S3_4_S0_2] = "{ra,s3-s4,s0-s2}",
    };

    putString(result, map[rlist]);
}

//
// Emit alist argument
//
static void putAList(char **result, riscvAListDesc alist) {

    static const char *map[] = {
        [RV_AL_NA]   = "{}",
        [RV_AL_A0]   = "{a0}",
        [RV_AL_A0_1] = "{a0-a1}",
        [RV_AL_A0_2] = "{a0-a2}",
        [RV_AL_A0_3] = "{a0-a3}",
    };

    putString(result, map[alist]);
}

//
// Emit retval argument
//
static void putRetVal(char **result, riscvRetValDesc retval) {

    static const char *map[] = {
        [RV_RV_NA] = "{}",
        [RV_RV_0]  = "{0}",
        [RV_RV_P1] = "{1}",
        [RV_RV_M1] = "{-1}"
    };

    putString(result, map[retval]);
}

//
// Emit CSR argument
//
static void putCSR(char **result, riscvP riscv, Uns32 csr) {

    const char *name = riscvGetCSRName(riscv, csr);

    if(name) {
        putString(result, name);
    } else {
        *result += sprintf(*result, "0x%03x", csr);
    }
}

//
// Emit fence argument
//
static void putFence(
    char         **result,
    riscvFenceDesc fence,
    riscvFenceDesc other,
    Bool           uncooked
) {
    if(!fence) {
        putString(result, "unknown");
    } else if(uncooked || (fence!=RV_FENCE_IOWR) || (other!=RV_FENCE_IOWR)) {
        if(fence & RV_FENCE_I) putChar(result, 'i');
        if(fence & RV_FENCE_O) putChar(result, 'o');
        if(fence & RV_FENCE_R) putChar(result, 'r');
        if(fence & RV_FENCE_W) putChar(result, 'w');
    }
}

//
// Emit rounding mode argument
//
static void putOptRM(
    char      **result,
    riscvRMDesc rm,
    Bool        explicitRM,
    Bool        uncooked
) {
    if(rm && (rm!=RV_RM_CURRENT)) {

        putUncookedKey(result, " RM", uncooked);

        if(!uncooked && explicitRM) {

            // rounding mode in opcode (not consistent with base architecture)

        } else {

            static const char *map[] = {
                [RV_RM_RNE]  = "rne",
                [RV_RM_RTZ]  = "rtz",
                [RV_RM_RDN]  = "rdn",
                [RV_RM_RUP]  = "rup",
                [RV_RM_RMM]  = "rmm",
                [RV_RM_ROD]  = "rod",
                [RV_RM_BAD5] = "rm5",
                [RV_RM_BAD6] = "rm6",
            };

            putString(result, map[rm]);
        }
    }
}

//
// Emit VType argument
//
static void putVType(char **result, riscvP riscv, riscvVType vtype) {

    Int32       svlmul    = getVTypeSVLMUL(vtype);
    const char *mulString = (svlmul<0) ? "mf" : "m";
    Uns32       vlmul     = (svlmul<0) ? -svlmul : svlmul;

    // put common fields
    putChar(result, 'e');
    putD(result, getVTypeSEW(vtype));
    putChar(result, ',');
    putString(result, mulString);
    putD(result, 1<<vlmul);

    // add agnostic indications if implemented
    if(riscvVFSupport(riscv, RVVF_AGNOSTIC)) {
        putChar(result, ',');
        putString(result, getVTypeVTA(vtype) ? "ta" : "tu");
        putChar(result, ',');
        putString(result, getVTypeVMA(vtype) ? "ma" : "mu");
    }
}

//
// Return size character for size index
//
static char getRBitsChar(Uns32 bits, const char *sizes) {

    Uns32 logBytes = 0;
    
    // sanity check input bits
    VMI_ASSERT(bits,     "require bits!=0");
    VMI_ASSERT(bits<=64, "require bits<=64");

    // convert from bits to log2(bytes)
    while(bits>8) {
        logBytes++;
        bits >>= 1;
    }

    return sizes[logBytes];
}

//
// Emit opcode modifier based on argument type
//
static riscvRegDesc putType(
    char          **result,
    riscvInstrInfoP info,
    Uns32           argIndex,
    riscvRegDesc    prev
) {
    riscvRegDesc this         = info->r[argIndex];
    Uns32        explicitType = info->explicitType;

    if(explicitType && (argIndex<(explicitType-1))) {

        // skip to the first operand for which type should be reported

    } else if(this && !isQReg(this) && (getRType(this)!=getRType(prev))) {

        Uns32 bits = getRBits(this);

        if(explicitType) {

            // emit dot before type
            if(info->explicitDot) {
                putChar(result, '.');
            }

            // show explicit operand types
            if(isFXReg(this)) {
                putChar(result, 'x');
            } else if(isWLReg(this)) {
                putChar(result, getRBitsChar(bits, "??wl"));
            } else if(isXReg(this)) {
                putChar(result, getRBitsChar(bits, "bhwd"));
            } else if(isFReg(this)) {
                putChar(result, getRBitsChar(bits/2, "hsdq"));
            } else {
                VMI_ABORT("Bad register specifier 0x%x", this); // LCOV_EXCL_LINE
            }

            // show explicit unsigned if required
            if(isUReg(this)) {
                putChar(result, 'u');
            }

        } else if(info->explicitW) {

            // indicate "w" type (with no dot)
            putChar(result, 'w');
        }

        prev = this;
    }

    return prev;
}

//
// Convert from bits to character/string index
//
static Uns32 bitsToIndex(Uns32 bits) {

    Uns32 index = -1;

    switch(bits) {
        case 4:   index = 0; break;
        case 8:   index = 1; break;
        case 16:  index = 2; break;
        case 32:  index = 3; break;
        case 64:  index = 4; break;
        case 128: index = 5; break;
        case -1:  index = 6; break;
        default:  VMI_ABORT("Unexpected bits %u", bits); // LCOV_EXCL_LINE
    }

    return index;
}

//
// Put standard character corresponding to the given bits
//
static void putBitsChar(char **result, Uns32 bits) {
    putChar(result, "nbhwdqe"[bitsToIndex(bits)]);
}

//
// Add opcode string to result
//
static void putOpcode(char **result, riscvP riscv, riscvInstrInfoP info) {

    riscvRegDesc type = RV_RD_NA;
    Uns32        i;

    // emit shift prefix if required
    if(info->shN) {
        putString(result, "sh");
        putD(result, info->shN);
    }

    // emit z/s prefix if required
    if(info->unsPfx) {
        putChar(result, info->unsExt ? 'z' : 's');
    }

    // emit basic opcode
    putString(result, info->opcode);

    // emit modifiers based on argument register types
    for(i=0; i<RV_MAX_AREGS; i++) {
        type = putType(result, info, i, type);
    }

    if(info->isWhole) {

        // whole register load/store or move
        putD(result, info->nf+1);
        putChar(result, 'r');

        // emit version 1.0 EEW hint if required
        if(info->eew && riscvVFSupport(riscv, RVVF_VLR_HINT)) {
            putChar(result, 'e');
            putD(result, info->eew);
        }

    } else {

        // emit number of fields if required
        if(info->nf) {
            putString(result, "seg");
            putD(result, info->nf+1);
        }

        if((info->eew==1) && riscvVFSupport(riscv, RVVF_VLM_VSM)) {

            // mask load or store
            putString(result, "m");

        } else if(info->eew) {

            // version 0.9 EEW
            putChar(result, 'e');
            if(info->memBits<=0) {putChar(result, 'i');}
            putD(result, info->eew);

        } else if(info->memBits) {

            // standard memBits
            putBitsChar(result, info->memBits);
        }
    }

    // emit unsigned modifier if required
    if(info->unsExt && !info->unsPfx) {
        putChar(result, 'u');
    }

    // emit element size modifier if required
    if(info->crossOp) {
        static const char *map[] = {
            [RV_CR_AS] = "as",
            [RV_CR_SA] = "sa"
        };
        putString(result, map[info->crossOp]);
    }

    // emit half modifier if required
    if(info->half) {
        static const char *map[] = {
            [RV_HA_B]  = "b",
            [RV_HA_T]  = "t",
            [RV_HA_BB] = "bb",
            [RV_HA_BT] = "bt",
            [RV_HA_TB] = "tb",
            [RV_HA_TT] = "tt"
        };
        putString(result, map[info->half]);
    }

    // emit soubling modifier if required
    if(info->doDouble) {
        putD(result, 2);
    }

    // emit element size modifier if required
    if(info->elemSize) {
        putD(result, info->elemSize);
    }

    // emit pack modifier if required
    if(info->pack) {
        static const char *map[] = {
            [RV_PD_10] = "10",
            [RV_PD_20] = "20",
            [RV_PD_30] = "30",
            [RV_PD_31] = "31",
            [RV_PD_32] = "32",
        };
        putString(result, map[info->pack]);
    }

    // emit round modifier if required
    if(info->round) {
        putString(result, ".u");
    }

    // emit return modifier if required
    if(info->doRet) {
        putString(result, "ret");
    }

    // emit embedded modifier if required
    if(info->rlist>=RV_RL_E_RA_S0_2) {
        putString(result, ".e");
    }

     // emit CSR as part of opcode if required
    if(info->csrInOp) {
        putCSR(result, riscv, info->csr);
    }

    // emit ff suffix if required
    if(info->isFF) {
        putString(result, "ff");
    }

    // type describing suffix actions
    typedef struct viDescInfoS {
        const char *suffix;     // initial suffix
        Bool        addMaskM;   // add m if mask is specified
    } viDescInfo;

    // vector suffixes
    static const viDescInfo viDescs[RV_VIT_LAST] = {
        [RV_VIT_NA]  = {"",     0},
        [RV_VIT_V]   = {".v",   0},
        [RV_VIT_W]   = {".w",   0},
        [RV_VIT_VV]  = {".vv",  0},
        [RV_VIT_VI]  = {".vi",  0},
        [RV_VIT_VX]  = {".vx",  0},
        [RV_VIT_WV]  = {".wv",  0},
        [RV_VIT_WI]  = {".wi",  0},
        [RV_VIT_WX]  = {".wx",  0},
        [RV_VIT_VF]  = {".vf",  0},
        [RV_VIT_WF]  = {".wf",  0},
        [RV_VIT_VS]  = {".vs",  0},
        [RV_VIT_M]   = {".m",   0},
        [RV_VIT_MM]  = {".mm",  0},
        [RV_VIT_VM]  = {".vm",  0},
        [RV_VIT_VVM] = {".vv",  1},
        [RV_VIT_VXM] = {".vx",  1},
        [RV_VIT_VIM] = {".vi",  1},
        [RV_VIT_VFM] = {".vf",  1},
        [RV_VIT_V_V] = {".v.v", 0},
    };

    // emit vector suffix
    VMI_ASSERT(info->VIType<NUM_MEMBERS(viDescs), "bad VIType (%u)", info->VIType);
    putString(result, viDescs[info->VIType].suffix);

    // add additional 'm' if mask is specified
    if(viDescs[info->VIType].addMaskM && info->mask) {
        putChar(result, 'm');
    }

    // add EEW divisor if specified
    if(info->eewDiv) {
        putChar(result, 'f');
        putD(result, info->eewDiv);
    }

    // acquire/release modifier suffixes
    static const char *aqrlDescs[] = {
        [RV_AQRL_NA]   = "",
        [RV_AQRL_RL]   = ".rl",
        [RV_AQRL_AQ]   = ".aq",
        [RV_AQRL_AQRL] = ".aqrl"
    };

    // emit acquire/release modifier
    VMI_ASSERT(info->aqrl<NUM_MEMBERS(aqrlDescs), "bad aqrl (%u)", info->aqrl);
    putString(result, aqrlDescs[info->aqrl]);

    // emit xperm size modifier
    if(info->xperm==RV_XP_NBHW) {
        putChar(result, '.');
        putBitsChar(result, info->c);
    } else if(info->xperm==RV_XP_BITS) {
        putD(result, info->c);
    }
}

//
// Generate instruction disassembly using the format string
//
static void disassembleFormat(
    riscvP          riscv,
    riscvInstrInfoP info,
    char          **result,
    const char     *format,
    Bool            uncooked
) {
    // generate instruction pattern
    if(!uncooked) {
        putInstruction(info, result);
    }

    // get offset at opcode start
    const char *opcodeStart = *result;

    // add opcode string to result
    putOpcode(result, riscv, info);

    if(*format) {

        // calculate length of opcode text
        const char *opcodeEnd = *result;
        Uns32       len       = opcodeEnd-opcodeStart;
        char        ch;

        // emit formatted space if cooked output
        if(!uncooked)  {

            // pad to minimum width
            for(; len<OP_WIDTH; len++) {
                putChar(result, ' ');
            }

            // emit space before arguments
            putChar(result, ' ');
        }

        // this defines whether the next argument is optional
        Bool nextOpt = False;

        // generate arguments in appropriate format
        while((ch=*format++)) {

            // is this argument optional?
            Bool opt = nextOpt;

            // assume subsequent argument is mandatory
            nextOpt = False;

            switch(ch) {
                case EMIT_R1:
                    putUncookedKey(result, " R1", uncooked);
                    putReg(result, riscv, info->r[0], opt, uncooked);
                    break;
                case EMIT_R2:
                    putUncookedKey(result, " R2", uncooked);
                    putReg(result, riscv, info->r[1], opt, uncooked);
                    break;
                case EMIT_R3:
                    putUncookedKey(result, " R3", uncooked);
                    putReg(result, riscv, info->r[2], opt, uncooked);
                    break;
                case EMIT_R4:
                    putUncookedKey(result, " R4", uncooked);
                    putReg(result, riscv, info->r[3], opt, uncooked);
                    break;
                case EMIT_CS:
                    putUncookedKey(result, " C", uncooked);
                    putD(result, info->c);
                    break;
                case EMIT_CX:
                    putUncookedKey(result, " C", uncooked);
                    putX(result, info->c);
                    break;
                case EMIT_UI:
                    putUncookedKey(result, " C", uncooked);
                    putX(result, ((Uns32)info->c)>>12);
                    break;
                case EMIT_TGT:
                    putUncookedKey(result, " T", uncooked);
                    putTarget(result, info->tgt);
                    break;
                case EMIT_CSR:
                    putUncookedKey(result, " CSR", uncooked);
                    putCSR(result, riscv, info->csr);
                    break;
                case EMIT_PRED:
                    putUncookedKey(result, " PRED", uncooked);
                    putFence(result, info->pred, info->succ, uncooked);
                    break;
                case EMIT_SUCC:
                    putUncookedKey(result, " SUCC", uncooked);
                    putFence(result, info->succ, info->pred, uncooked);
                    break;
                case EMIT_VTYPE:
                    putUncookedKey(result, " VTYPE", uncooked);
                    putVType(result, riscv, info->vtype);
                    break;
                case EMIT_RM:
                    putOptMask(result, riscv, info->mask, ".t", uncooked);
                    break;
                case EMIT_RMR:
                    putOptMask(result, riscv, info->mask, "", uncooked);
                    break;
                case EMIT_RLIST:
                    putUncookedKey(result, " RLIST", uncooked);
                    putRlist(result, info->rlist);
                    break;
                case EMIT_ALIST:
                    putUncookedKey(result, " ALIST", uncooked);
                    putAList(result, info->alist);
                    break;
                case EMIT_RETVAL:
                    putUncookedKey(result, " RETVAL", uncooked);
                    putRetVal(result, info->retval);
                    break;
                case '*':
                    nextOpt = True;
                    break;
                case ',':
                    putComma(result, uncooked);
                    break;
                default:
                    if(!uncooked) {putChar(result, ch);}
                    break;
            }
        }

        // emit comma before optional rounding mode
        putComma(result, uncooked);
    }

    // emit optional rounding mode
    putOptRM(result, info->rm, info->explicitRM, uncooked);

    // strip trailing whitespace and commas
    char *tail = (*result)-1;
    while((*tail == ' ') || (*tail == ',')) {
        *tail-- = 0;
    }
}

//
// This defines the size of the disassembly buffer
//
#define DISASS_BUFFER_SIZE 256

//
// riscv disassembler, decoded instruction interface
//
static const char *disassembleInfo(
    riscvP          riscv,
    riscvInstrInfoP info,
    vmiDisassAttrs  attrs
) {
    // static buffer to hold disassembly result
    static char result[DISASS_BUFFER_SIZE];
    const char *format = info->format;
    char       *tail   = result;

    // sanity check format is specified
    VMI_ASSERT(format, "null instruction format");

    // disassemble using the format for the type
    disassembleFormat(riscv, info, &tail, format, attrs==DSA_UNCOOKED);

    // validate disassembly buffer has not overflowed
    VMI_ASSERT(
        tail <= &result[DISASS_BUFFER_SIZE-1],
        "buffer overflow for instruction '%s'\n",
        result
    );

    // return the result
    return result;
}

//
// riscv disassembler, VMI interface
//
VMI_DISASSEMBLE_FN(riscvDisassemble) {

    riscvP         riscv = (riscvP)processor;
    riscvInstrInfo info;

    // decode instruction
    riscvDecode(riscv, thisPC, &info);

    // return disassembled instruction
    return disassembleInfo(riscv, &info, attrs);
}

//
// Disassemble unpacked instruction using the given format
//
const char *riscvDisassembleInstruction(
    riscvP             riscv,
    riscvExtInstrInfoP instrInfo,
    vmiDisassAttrs     attrs
) {
    riscvInstrInfo info = {0};

    // fill source from interpreted fields
    info.opcode      = instrInfo->opcode;
    info.format      = instrInfo->format;
    info.instruction = instrInfo->instruction;
    info.bytes       = instrInfo->bytes;
    info.arch        = instrInfo->arch;
    info.r[0]        = instrInfo->r[0];
    info.r[1]        = instrInfo->r[1];
    info.r[2]        = instrInfo->r[2];
    info.r[3]        = instrInfo->r[3];
    info.mask        = instrInfo->mask;
    info.rm          = instrInfo->rm;
    info.c           = instrInfo->c;

    // do disassembly
    return disassembleInfo(riscv, &info, attrs);
}

