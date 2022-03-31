/*
 * Copyright (c) 2011-2014 Posedge Software Inc., www.posedgesoft.com
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


#ifndef M16C_MORPHENTRIES_H
#define M16C_MORPHENTRIES_H


#include "m16cStructure.h"


#define M16C_MT_BINOP M16C_MT_BINOP_R_R
#define M16C_MT_BITOP M16C_MT_BITOP_R

#define M16C_MT_DIV M16C_MT_DIV_R


#define M16C_MT_UNOP M16C_MT_UNOP_R
#define M16C_MT_MOVE M16C_MT_MOVE_R_R
#define M16C_MT_MOVEC M16C_MT_MOVEC_R_R
#define M16C_MT_POP M16C_MT_POP_R
#define M16C_MT_PUSH M16C_MT_PUSH_R

#define M16C_MT_EXTS M16C_MT_EXTS_R

#define M16C_MT_JMPI M16C_MT_JMPI_R

#define M16C_MT_ROT M16C_MT_ROT_R_R
#define M16C_MT_SBJNZ M16C_MT_SBJNZ_R_C
#define M16C_MT_XCHG M16C_MT_XCHG_R_R



// Instruction type enumeration
//
typedef enum m16cMorphTypeE {
        M16C_MT_BOGUS,
        M16C_MT_BINOP_R_R,
        M16C_MT_BINOP_R_C,
        M16C_MT_BINOP_R_O,
        M16C_MT_BINOP_O_R,
        M16C_MT_BINOP_O_C,
        M16C_MT_BINOP_O_O,
        M16C_MT_BITOP_R,
        M16C_MT_BITOP_O,


        M16C_MT_UNOP_R,
        M16C_MT_UNOP_O,
        M16C_MT_UNOP_R_R,
        M16C_MT_UNOP_R_C,
        M16C_MT_UNOP_R_O,
        M16C_MT_UNOP_O_R,
        M16C_MT_UNOP_O_C,
        M16C_MT_UNOP_O_O,

        M16C_MT_DIV_R,
        M16C_MT_DIV_C,
        M16C_MT_DIV_O,

        M16C_MT_EXTS_R,
        M16C_MT_EXTS_C,
        M16C_MT_EXTS_O,

        M16C_MT_JMPI_R,
        M16C_MT_JMPI_C,
        M16C_MT_JMPI_O,

        M16C_MT_MOVE_R_R,
        M16C_MT_MOVE_R_C,
        M16C_MT_MOVE_R_O,
        M16C_MT_MOVE_O_R,
        M16C_MT_MOVE_O_C,
        M16C_MT_MOVE_O_O,
        M16C_MT_MOVEC_R_R,
        M16C_MT_MOVEC_R_C,
        M16C_MT_MOVEC_R_O,
        M16C_MT_MOVEC_O_R,
        M16C_MT_MOVEC_O_C,
        M16C_MT_MOVEC_O_O,
        M16C_MT_POP_R,
        M16C_MT_POP_O,

        M16C_MT_PUSH_R,
        M16C_MT_PUSH_C,
        M16C_MT_PUSH_O,

        M16C_MT_ROT_R_R,
        M16C_MT_ROT_R_C,
        M16C_MT_ROT_R_O,
        M16C_MT_ROT_O_R,
        M16C_MT_ROT_O_C,
        M16C_MT_ROT_O_O,

        M16C_MT_SBJNZ_R_R,
        M16C_MT_SBJNZ_R_C,
        M16C_MT_SBJNZ_R_O,
        M16C_MT_SBJNZ_O_R,
        M16C_MT_SBJNZ_O_C,
        M16C_MT_SBJNZ_O_O,

        M16C_MT_XCHG_R_R,
        M16C_MT_XCHG_R_C,
        M16C_MT_XCHG_R_O,
        M16C_MT_XCHG_O_R,
        M16C_MT_XCHG_O_C,
        M16C_MT_XCHG_O_O,
        M16C_MT_BRK,
        M16C_MT_BITOPC,
        M16C_MT_ENTER,
        M16C_MT_EXIT,
        M16C_MT_INT,
        M16C_MT_INTO,
        M16C_MT_JMP,
        M16C_MT_JMPU,
        M16C_MT_JSR,
        M16C_MT_JSRI,
        M16C_MT_JSRS,
        M16C_MT_LDCTX,
        M16C_MT_LDIPL,
        M16C_MT_MOVEF,
        M16C_MT_MOVEA,
        M16C_MT_NOP,
        M16C_MT_POP_M,
        M16C_MT_PUSH_M,
        M16C_MT_REIT,
        M16C_MT_RMPA,
        M16C_MT_RTS,
        M16C_MT_SMOV,
        M16C_MT_SSTR,
        M16C_MT_STCTX,
        M16C_MT_STZX_R,
        M16C_MT_STZX_O,
        M16C_MT_UND,
        M16C_MT_WAIT,
                // KEEP LAST: for sizing the array
        M16C_MT_LAST
} m16cMorphType;


static const vmiFlags flagsNONE = VMI_NOFLAGS;

static const vmiFlags flagsS = {
    VMI_NOFLAG_CONST,           // offset to carry in flag (unused)
    {
        VMI_NOFLAG_CONST,       // offset to carry flag (unused)
        VMI_NOFLAG_CONST,       // offset to parity flag (unused)
        VMI_NOFLAG_CONST,        // offset to zero flag
        M16C_SIGN_CONST,        // offset to sign flag
        VMI_NOFLAG_CONST        // offset to overflow flag (unused)
    }
};


//
// Update zero, sign
//
static const vmiFlags flagsZS = {
    VMI_NOFLAG_CONST,           // offset to carry in flag (unused)
    {
        VMI_NOFLAG_CONST,       // offset to carry flag (unused)
        VMI_NOFLAG_CONST,       // offset to parity flag (unused)
        M16C_ZERO_CONST,        // offset to zero flag
        M16C_SIGN_CONST,        // offset to sign flag
        VMI_NOFLAG_CONST        // offset to overflow flag (unused)
    }
};

//
// Update overflow
//
static const vmiFlags flagsO = {
    VMI_NOFLAG_CONST,           // offset to carry in flag (unused)
    {
        VMI_NOFLAG_CONST,       // offset to carry flag (unused)
        VMI_NOFLAG_CONST,       // offset to parity flag (unused)
        VMI_NOFLAG_CONST,        // offset to zero flag
        VMI_NOFLAG_CONST,      // offset to sign flag
        M16C_OVERFLOW_CONST     // offset to overflow flag (unused)
    }
};

//
// Update zero, sign
//
static const vmiFlags flagsCZS = {
    VMI_NOFLAG_CONST,           // offset to carry in flag (unused)
    {
        M16C_CARRY_CONST,       // offset to carry flag
        VMI_NOFLAG_CONST,       // offset to parity flag (unused)
        M16C_ZERO_CONST,        // offset to zero flag
        M16C_SIGN_CONST,        // offset to sign flag
        VMI_NOFLAG_CONST        // offset to overflow flag (unused)
    }
};

//
// Update zero, sign
//
static const vmiFlags flagsCZSO = {
    VMI_NOFLAG_CONST,           // offset to carry in flag (unused)
    {
        M16C_CARRY_CONST,       // offset to carry flag
        VMI_NOFLAG_CONST,       // offset to parity flag (unused)
        M16C_ZERO_CONST,        // offset to zero flag
        M16C_SIGN_CONST,        // offset to sign flag
        M16C_OVERFLOW_CONST     // offset to overflow flag
    }
};

static const vmiFlags flagsC_CZSO = {
    M16C_CARRY_CONST,           // offset to carry in flag
    {
        M16C_CARRY_CONST,       // offset to carry flag
        VMI_NOFLAG_CONST,       // offset to parity flag (unused)
        M16C_ZERO_CONST,        // offset to zero flag
        M16C_SIGN_CONST,        // offset to sign flag
        M16C_OVERFLOW_CONST     // offset to overflow flag
    }
};


static const vmiFlags flagsC_CZS = {
    M16C_CARRY_CONST,           // offset to carry in flag
    {
        M16C_CARRY_CONST,       // offset to carry flag
        VMI_NOFLAG_CONST,       // offset to parity flag (unused)
        M16C_ZERO_CONST,        // offset to zero flag
        M16C_SIGN_CONST,        // offset to sign flag
        VMI_NOFLAG_CONST     // offset to overflow flag
    }
};


#endif

