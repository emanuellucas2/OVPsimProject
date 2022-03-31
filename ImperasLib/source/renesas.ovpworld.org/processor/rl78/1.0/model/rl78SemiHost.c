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
#include "vmi/vmiMt.h"

#include "vmi/vmiMessage.h"

// model header files
#include "rl78Functions.h"
#include "rl78Structure.h"


//
// Morph return from an opaque intercepted function
//
VMI_INT_RETURN_FN(rl78IntReturnCB) {
    rl78P rl78 = (rl78P)processor;

    vmimtLoadRRODomain(            //void vmimtLoadRRO(
        rl78->dataDomain16,        //    memDomainP    domain,
        16,                        //    Uns32         destBits,
        16,                        //    Uns32         memBits,
        0x0,                       //    Addr          offset,
        RL78_TMP,                  //    vmiReg        rd,
        RL78_SP,                   //    vmiReg        ra,
        MEM_ENDIAN_LITTLE,         //    memEndian     endian,
        0,                         //    Bool          signExtend,
        MEM_CONSTRAINT_NONE);      //    memConstraint constraint

    vmimtBinopRC(32, vmi_AND, RL78_TMP, 0xFFFFF, 0);
    vmimtBinopRC(16, vmi_ADD, RL78_SP, 4, 0);

    vmimtUncondJumpReg(            //void vmimtUncondJumpReg(
        0,                         //    Addr        linkPC,
        RL78_TMP,                  //    vmiReg      toReg,
        VMI_NOREG,                 //    vmiReg      linkReg,
        vmi_JH_RETURN);            //    vmiJumpHint hint
}

//
// This callback should create code to assign function result to the standard
// return result register or stack entry
//
VMI_INT_RESULT_FN(rl78IntResultCB) {
    vmiMessage("W", "TODO", "rl78IntResultCB");
}

//
// This callback should create code to push 32-bit function parameter 'paramNum'
//
static Uns32 push4ByteArg(vmiProcessorP processor, Uns32 paramNum) {
    // TODO
    return 0;
}

//
// This callback should create code to push 64-bit function parameter 'paramNum'
//
static Uns32 push8ByteArg(vmiProcessorP processor, Uns32 paramNum) {
    // TODO
    return 0;
}

//
// This callback should create code to push address function parameter 'paramNum'
//
static Uns32 pushAddressArg(vmiProcessorP processor, Uns32 paramNum) {
    // TODO
    return 0;
}

//
// This callback should create code to push function arguments prior to an
// Imperas standard intercept
//
VMI_INT_PAR_FN(rl78IntParCB) {
    vmiMessage("F", "TODO", "rl78IntParCB");

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
