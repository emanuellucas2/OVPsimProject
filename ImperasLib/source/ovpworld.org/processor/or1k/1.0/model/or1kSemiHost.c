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
#include "or1kFunctions.h"
#include "or1kStructure.h"


//
// Return GPR size
//
inline static Uns32 getXLen(or1kP or1k) {
    return 32;
}

//
// Return number of argument registers
//
inline static Uns32 getARegNum(or1kP or1k) {
    return 6;
}

//
// Return the processor data endianness
//
inline static Uns32 getDataEndian(or1kP or1k) {
    return MEM_ENDIAN_BIG;
}

//
// Return next temporary, checking index for overflow
//
static vmiReg getTmp(Uns32 index) {

    VMI_ASSERT(index<OR1K_NUM_TEMPS, "Semihost register index overflow (%u)", index);

    return OR1K_CPU_TEMP(TMP[index]);
}

//
// Morph return from an opaque intercepted function
//
VMI_INT_RETURN_FN(or1kIntReturnCB) {

    vmimtUncondJumpReg(0, OR1K_REG(OR1K_LINK), VMI_NOREG, vmi_JH_RETURN);
}

//
// Return bit size for the given format character
//
static Uns32 getFormatBits(or1kP or1k, char format) {

    Uns32 resBits = 0;

    // decode return value format
    if((format=='4') || (format=='f')) {
        resBits = 32;
    } else if(format=='a') {
        resBits = getXLen(or1k);
    } else if((format=='8') || (format=='d')) {
        resBits = 64;
    } else {                                                    // LCOV_EXCL_LINE
        VMI_ABORT("Unrecognised format character '%c'", format);// LCOV_EXCL_LINE
    }

    return resBits;
}

//
// This callback should create code to assign function result to the standard
// return result register
//
VMI_INT_RESULT_FN(or1kIntResultCB) {

    or1kP or1k    = (or1kP)processor;
    Uns32 xlen    = getXLen(or1k);
    Uns32 resBits = getFormatBits(or1k, format);

    if(resBits<=xlen) {

        // assign result to register
        vmiReg rdL  = OR1K_REG(11);
        vmimtMoveRR(resBits, rdL, VMI_FUNCRESULT);
        vmimtMoveExtendRR(xlen, rdL, resBits, rdL, False);

    } else {

        // assign result using by-ref pointer
        memEndian endian = getDataEndian(or1k);
        vmiReg    tmp    = getTmp(0);
        vmiReg    rdA    = OR1K_REG(3);

        vmimtMoveRR(resBits, tmp, VMI_FUNCRESULT);
        vmimtStoreRRO(resBits, 0, rdA, tmp, endian, False);
    }
}

//
// This callback should create code to push function arguments prior to an
// Imperas standard intercept
//
VMI_INT_PAR_FN(or1kIntParCB) {

    or1kP     or1k      = (or1kP)processor;
    memEndian endian    = getDataEndian(or1k);
    Uns32     xlen      = getXLen(or1k);
    Uns32     aRegNum   = getARegNum(or1k);
    Uns32     memOffset = 0;
    Uns32     rNum      = 0;
    Uns32     tmpIdx    = 0;
    char      ch;

    // handle by-ref return if required
    if(formatResult && (getFormatBits(or1k, formatResult) > xlen)) {
        rNum++;
    }

    while((ch=*format++)) {

        vmiReg argReg;
        Uns32  argBits = getFormatBits(or1k, ch);

        // determine whether argument is passed in register pair
        Bool isPair = (argBits>xlen);

        // align double-width register arguments
        if(isPair && (rNum&1)) {
            rNum++;
        }

        if(rNum >= aRegNum) {

            // argument passed in memory
            argReg = getTmp(tmpIdx++);

            // load from stack into temporary
            vmimtLoadRRO(
                argBits,
                argBits,
                memOffset * (xlen/8),
                argReg,
                OR1K_REG(OR1K_SP),
                endian,
                False,
                False
            );

            memOffset += isPair ? 2 : 1;

        } else if(!isPair) {

            // argument passed in X register
            argReg = OR1K_REG(OR1K_A0+rNum);

        } else {

            // argument passed in X register pair
            argReg = getTmp(tmpIdx++);

            vmiReg loSrc = OR1K_REG(OR1K_A0+rNum);
            vmiReg hiSrc = OR1K_REG(OR1K_A0+rNum+1);
            vmiReg loDst = argReg;
            vmiReg hiDst = VMI_REG_DELTA(argReg, xlen/8);

            // move argument halves to wider temporary
            vmimtMoveRR(xlen, loDst, endian==MEM_ENDIAN_BIG ? hiSrc : loSrc);
            vmimtMoveRR(xlen, hiDst, endian==MEM_ENDIAN_BIG ? loSrc : hiSrc);
        }

        // adjust register indices
        rNum += isPair ? 2 : 1;

        if(ch=='4') {
            vmimtArgReg(32, argReg);
        } else if(ch=='a') {
            vmimtArgRegSimAddress(xlen, argReg);
        } else if(ch=='8') {
            vmimtArgReg(64, argReg);
        } else if(ch=='f') {
            vmimtArgReg(VPRRAT_FLT32, argReg);
        } else if(ch=='d') {
            vmimtArgReg(VPRRAT_FLT64, argReg);
        } else {                                                    // LCOV_EXCL_LINE
            VMI_ABORT("Unrecognised format character '%c'", ch);    // LCOV_EXCL_LINE
        }
    }
}

