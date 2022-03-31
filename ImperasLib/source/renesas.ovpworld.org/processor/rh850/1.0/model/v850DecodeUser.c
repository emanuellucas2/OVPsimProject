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

#include "vmi/vmiCxt.h"
#include "vmi/vmiDecode.h"
#include "vmi/vmiMessage.h"
#include "v850Decode.h"
#include "v850Instructions.h"
#include "v850Structure.h"

//
// Decoder function for a given address
//
void v850Decode(
    v850P v850,
    v850Addr thisPC,
    v850InstructionInfoP info
) {
    //
    // Initialize the following info fields before table creation
    //
    info->thisPC = thisPC;
    info->arch = v850->configInfo.arch;
    vmiProcessorP processor = (vmiProcessorP)v850;

    //
    // Initialize the RH850G3M_16Bit decoder table
    //
    static vmidDecodeTableP decodeTable_RH850G3M_16Bit;
    if(!decodeTable_RH850G3M_16Bit && (info->arch == RH850G3M)) {
        decodeTable_RH850G3M_16Bit = v850CreateDecodeTable_ISA_E0_16Bit(decodeTable_RH850G3M_16Bit);
        decodeTable_RH850G3M_16Bit = v850CreateDecodeTable_ISA_E1_16Bit(decodeTable_RH850G3M_16Bit);
        decodeTable_RH850G3M_16Bit = v850CreateDecodeTable_ISA_E2_16Bit(decodeTable_RH850G3M_16Bit);
        decodeTable_RH850G3M_16Bit = v850CreateDecodeTable_ISA_E3_16Bit(decodeTable_RH850G3M_16Bit);
    }

    //
    // Initialize the RH850G3M_32Bit decoder table
    //
    static vmidDecodeTableP decodeTable_RH850G3M_32Bit;
    if(!decodeTable_RH850G3M_32Bit && (info->arch == RH850G3M)) {
        decodeTable_RH850G3M_32Bit = v850CreateDecodeTable_ISA_E0_32Bit(decodeTable_RH850G3M_32Bit);
        decodeTable_RH850G3M_32Bit = v850CreateDecodeTable_ISA_E1_32Bit(decodeTable_RH850G3M_32Bit);
        decodeTable_RH850G3M_32Bit = v850CreateDecodeTable_ISA_E2_32Bit(decodeTable_RH850G3M_32Bit);
        decodeTable_RH850G3M_32Bit = v850CreateDecodeTable_ISA_E3_32Bit(decodeTable_RH850G3M_32Bit);
        decodeTable_RH850G3M_32Bit = v850CreateDecodeTable_ISA_E2_FP_32Bit(decodeTable_RH850G3M_32Bit);
        decodeTable_RH850G3M_32Bit = v850CreateDecodeTable_ISA_E3_FP_32Bit(decodeTable_RH850G3M_32Bit);
    }

    //
    // Initialize the RH850G3M_48Bit decoder table
    //
    static vmidDecodeTableP decodeTable_RH850G3M_48Bit;
    if(!decodeTable_RH850G3M_48Bit && (info->arch == RH850G3M)) {
        decodeTable_RH850G3M_48Bit = v850CreateDecodeTable_ISA_E1_48Bit(decodeTable_RH850G3M_48Bit);
        decodeTable_RH850G3M_48Bit = v850CreateDecodeTable_ISA_E2_48Bit(decodeTable_RH850G3M_48Bit);
        decodeTable_RH850G3M_48Bit = v850CreateDecodeTable_ISA_E3_48Bit(decodeTable_RH850G3M_48Bit);
    }

    //
    // Initialize the RH850G3M_64Bit decoder table
    //
    static vmidDecodeTableP decodeTable_RH850G3M_64Bit;
    if(!decodeTable_RH850G3M_64Bit && (info->arch == RH850G3M)) {
        decodeTable_RH850G3M_64Bit = v850CreateDecodeTable_ISA_E1_64Bit(decodeTable_RH850G3M_64Bit);
    }

    //
    // Initialize the following info fields before lookup
    //

    info->instrsize = 0;
    info->type = V850_IT_LAST;
    Uns64 instruction = 0;

    if (info->arch == RH850G3M) {
        if (info->type == V850_IT_LAST) info->type = V850_IT_INSTR16;
        //
        // Attempt to match a RH850G3M 16 Bit instruction
        //
        if (info->type == V850_IT_INSTR16) {
            instruction  = ((Uns64)vmicxtFetch2Byte(processor, thisPC+0) << 0) | instruction;
            info->type = V850_IT_LAST;
            info->type = vmidDecode(decodeTable_RH850G3M_16Bit, instruction);
            info->nextPC = info->thisPC + 2;
            info->instrsize = 2;
            info->instruction = instruction;
        }
        //
        // Attempt to match a RH850G3M 32 Bit instruction
        //
        if (info->type == V850_IT_INSTR32) {
            instruction  = ((Uns64)vmicxtFetch2Byte(processor, thisPC+2) << 16) | instruction;
            info->type = V850_IT_LAST;
            info->type = vmidDecode(decodeTable_RH850G3M_32Bit, instruction);
            info->nextPC = info->thisPC + 4;
            info->instrsize = 4;
            info->instruction = instruction;
        }
        //
        // Attempt to match a RH850G3M 48 Bit instruction
        //
        if (info->type == V850_IT_INSTR48) {
            instruction  = ((Uns64)vmicxtFetch2Byte(processor, thisPC+4) << 32) | instruction;
            info->type = V850_IT_LAST;
            info->type = vmidDecode(decodeTable_RH850G3M_48Bit, instruction);
            info->nextPC = info->thisPC + 6;
            info->instrsize = 6;
            info->instruction = instruction;
        }
        //
        // Attempt to match a RH850G3M 64 Bit instruction
        //
        if (info->type == V850_IT_INSTR64) {
            instruction  = ((Uns64)vmicxtFetch2Byte(processor, thisPC+6) << 48) | instruction;
            info->type = V850_IT_LAST;
            info->type = vmidDecode(decodeTable_RH850G3M_64Bit, instruction);
            info->nextPC = info->thisPC + 8;
            info->instrsize = 8;
            info->instruction = instruction;
        }
    }

    v850GenInstructionInfo(info);
}
