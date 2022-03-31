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

#ifndef V850_SPR_H
#define V850_SPR_H

#include "v850TypeRefs.h"
#include "v850Structure.h"
#include "v850Functions.h"

typedef enum v850PrivS {
    PRIV_SV     = 0x00000001,
    PRIV_UM     = 0x00000002,
    PRIV_CU0    = 0x00000010,
    PRIV_CU1    = 0x00000020,
    PRIV_CU2    = 0x00000040,

    PRIV_PSW    = 0x00000080,   // Special access permissions for PSW

    PRIV_CU0_SV = PRIV_SV | PRIV_CU0,
} v850PrivE;

typedef struct v850SystemRegisterS {
    const char      *name;
    v850Architecture arch;
    Uns16            GRP;
    Uns16            BNK;
    Uns8             regID;
    Uns8             selID;
    Uns8             arrIDX;    // This is only used for the MPU Address registers

    v850RegReadFn    readCB;
    v850RegWriteFn   writeCB;

    v850PrivE        priv;

    vmiReg           raw;
    IntPS            rMask;
    IntPS            wMask;
    Bool             endBlock;
} v850SystemRegisterT, *v850SystemRegisterP;

//
// _GRP/_BNK used by v850E2R
//
#define BANKREG(_ARCH, _REG, _NAME, _GRP, _BNK, _PRIV, _END_BLOCK, _READCB, _WRITECB) \
    {                                                \
        arch     : _ARCH,                            \
        name     : #_NAME,                           \
        regID    : V850_SPR_ ##_REG,                 \
        GRP      : _GRP,                             \
        BNK      : _BNK,                             \
        priv     : _PRIV,                            \
        readCB   : _READCB,                          \
        writeCB  : _WRITECB,                         \
        raw      : V850_SPR_ ##_REG## _RD,           \
        rMask    : V850_SPR_ ##_REG## _RMASK,        \
        wMask    : V850_SPR_ ##_REG## _WMASK,        \
        endBlock : _END_BLOCK                        \
    }

// _SEL      used by RH850
#define SELREG(_ARCH, _REG, _NAME, _SEL, _PRIV, _READCB, _WRITECB) \
    {                                                \
        arch     : _ARCH,                            \
        name     : #_NAME,                           \
        regID    : V850_SPR_SEL_ ##_REG,             \
        selID    : _SEL,                             \
        readCB   : _READCB,                          \
        writeCB  : _WRITECB,                         \
        priv     : _PRIV,                            \
        raw      : V850_SPR_ ##_REG## _RD,           \
        rMask    : V850_SPR_ ##_REG## _RMASK,        \
        wMask    : V850_SPR_ ##_REG## _WMASK         \
    }

// _SEL      used by RH850
#define SELREGIDX(_ARCH, _REG, _NAME, _IDX, _SEL, _PRIV, _READCB, _WRITECB) \
    {                                                \
        arch     : _ARCH,                            \
        name     : #_NAME #_IDX,                     \
        regID    : V850_SPR_SEL_ ##_REG## _IDX,      \
        selID    : _SEL,                             \
        readCB   : _READCB,                          \
        writeCB  : _WRITECB,                         \
        priv     : _PRIV,                            \
        raw      : V850_SPR_ ##_REG## _RD(_IDX),     \
        rMask    : V850_SPR_ ##_REG## _RMASK(_IDX),  \
        wMask    : V850_SPR_ ##_REG## _WMASK(_IDX),  \
        arrIDX   : _IDX                              \
    }

v850SystemRegisterP v850GetSystemRegister(v850P v850, Uns8 regID, Uns8 selID, Bool isMorph);

#endif // V850_SPR_H
