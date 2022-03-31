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
#include "vmi/vmiMessage.h"
#include "vmi/vmiMt.h"

// model header files
#include "v850Functions.h"
#include "v850Structure.h"
#include "v850TypeRefs.h"

//
// Morph return from an opaque intercepted function
//
VMI_INT_RETURN_FN(v850IntReturn) {

    vmimtUncondJumpReg(0, V850_GPR_WR(V850_GPR_LP), VMI_NOREG, vmi_JH_RETURN);
}

//
// This callback should create code to assign function result to the standard
// return result register
//
VMI_INT_RESULT_FN(v850IntResult) {

    vmimtMoveRR(32, V850_GPR_WR(10), VMI_FUNCRESULT);
}

//
// This callback should create code to push 32-bit function parameter 'paramNum'
//
static Uns32 push4ByteArg(vmiProcessorP processor, Uns32 paramNum) {

    if(paramNum<=5) {

        // argument in a register
        vmimtArgReg(32, V850_GPR_RD(3+paramNum));

    } else {

        // argument on the stack - fetch into a temporary
        vmimtLoadRRO(
            32,                         // destBits
            32,                         // memBits
            (paramNum-6)*4,             // offset
            V850_TMP_WR(0),             // destination (rd)
            V850_GPR_RD(1),             // stack address (ra)
            MEM_ENDIAN_BIG,             // endian
            False,                      // signExtend
            False                       // checkAlign
        );

        // push temporary argument
        vmimtArgReg(32, V850_TMP_WR(0));
    }

    return paramNum+1;
}

//
// This callback should create code to push 64-bit function parameter 'paramNum'
//
static Uns32 push8ByteArg(vmiProcessorP processor, Uns32 paramNum) {

    // align parameter number to an even word
    if((paramNum)&1) {
        paramNum += 1;
    }

    if(paramNum<=5) {

        // argument in a register
        vmimtArgReg(32, V850_GPR_RD(4+paramNum));    // LSW
        vmimtArgReg(32, V850_GPR_RD(3+paramNum));    // MSW

    } else {

        // argument on the stack - fetch into a temporary
        vmimtLoadRRO(
            64,                         // destBits
            64,                         // memBits
            (paramNum-6)*4,             // offset
            V850_TMP_WR(0),             // destination (rd)
            V850_GPR_RD(1),             // stack address (ra)
            MEM_ENDIAN_BIG,             // endian
            False,                      // signExtend
            False                       // checkAlign
        );

        // push temporary argument
        vmimtArgReg(64, V850_TMP_RD(0));
    }

    return paramNum+2;
}

//
// This callback should create code to push address function parameter 'paramNum'
//
static Uns32 pushAddressArg(vmiProcessorP processor, Uns32 paramNum) {

    if(paramNum<=5) {

        // argument in a register
        vmimtArgRegSimAddress(32, V850_GPR_RD(3+paramNum));

    } else {

        // argument on the stack - fetch into a temporary
        vmimtLoadRRO(
            32,                         // destBits
            32,                         // memBits
            (paramNum-6)*4,             // offset
            V850_TMP_WR(0),             // destination (rd)
            V850_GPR_RD(1),             // stack address (ra)
            MEM_ENDIAN_BIG,             // endian
            False,                      // signExtend
            False                       // checkAlign
        );

        // push temporary argument
        vmimtArgRegSimAddress(32, V850_TMP_RD(0));
    }

    return paramNum+1;
}

//
// This callback should create code to push function arguments prior to an
// Imperas standard intercept
//
VMI_INT_PAR_FN(v850IntPar) {

    Uns32 paramNum = 0;
    char  ch;

    while((ch=*format++)) {

        switch(ch) {

            case '4':
                paramNum = push4ByteArg(processor, paramNum);
                break;

            case '8':
                paramNum = push8ByteArg(processor, paramNum);
                break;

            case 'a':
                paramNum = pushAddressArg(processor, paramNum);
                break;

            default:
                VMI_ABORT("Unrecognised format character '%c'", ch);
                break;
        }
    }
}

