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

// Imperas header files
#include "hostapi/impAlloc.h"

// VMI header files
#include "vmi/vmiAttrs.h"
#include "vmi/vmiParameters.h"

#include "rl78Functions.h"
#include "rl78Parameters.h"


// OVP_VMI_Run_Time_Function_Reference.pdf
vmiEnumParameter variantList[] = {
    // name value description
    { .name="RL78-S1" , .value=en_RL78_S1, .description="RL78-S1" },
    { .name="RL78-S2" , .value=en_RL78_S2, .description="RL78-S2" },
    { .name="RL78-S3" , .value=en_RL78_S3, .description="RL78-S3" },

// Not real variants for the RL78 core processor
//    { "RL78G10", en_RL78_S1, "alias of RL78-S1" },    // NOTE: Removed '/' from variant alias name, not supported in names
//    { "RL78G12", en_RL78_S2, "alias of RL78-S2" },
//    { "RL78G13", en_RL78_S2, "alias of RL78-S2" },
//    { "RL78G1A", en_RL78_S2, "alias of RL78-S2" },
//    { "RL78G1E", en_RL78_S2, "alias of RL78-S2" },
//    { "RL78G1C", en_RL78_S2, "alias of RL78-S2" },
//    { "RL78I1A", en_RL78_S2, "alias of RL78-S2" },
//    { "RL78F12", en_RL78_S2, "alias of RL78-S2" },
//    { "RL78D1A", en_RL78_S2, "alias of RL78-S2" },
//    { "RL78L12", en_RL78_S2, "alias of RL78-S2" },
//    { "RL78L13", en_RL78_S2, "alias of RL78-S2" },
//    { "RL78G14", en_RL78_S3, "alias of RL78-S3" },

    {0} // null terminator
};

//
// Table of parameter specs
//
static vmiParameter formals[] = {

    //#define VMI_BOOL_PARAM_SPEC(_STR,_NAME,_DEFAULT,_DESC) {
    //    .name                     =  #_NAME,
    //    .type                     = vmi_PT_BOOL,
    //    .valueOffset              = VMI_PARAM_OFFSET(_STR, _NAME),
    //    .setBitOffset             = VMI_PARAM_OFFSET(_STR, SETBIT(_NAME)),
    //    .u.boolParam.defaultValue = _DEFAULT,
    //    .description              = _DESC,
    //    .sizeOf                   = sizeof(Bool)
    //}
    VMI_BOOL_PARAM_SPEC(rl78ParamValues, verbose, 0, "Verbose mode"),

    //#define VMI_ENUM_PARAM_SPEC(_STR,_NAME,_list,_DESC) {
    //    .name                    =  #_NAME,
    //    .type                    = vmi_PT_ENUM,
    //    .u.enumParam.legalValues = _list,
    //    .valueOffset             =  VMI_PARAM_OFFSET(_STR,_NAME),
    //    .setBitOffset            =  VMI_PARAM_OFFSET(_STR, SETBIT(_NAME)),
    //    .description             = _DESC,
    //    .sizeOf                  = sizeof(Uns32)
    //}
    VMI_ENUM_PARAM_SPEC(rl78ParamValues, variant, variantList, "processor variant"),

    VMI_BOOL_PARAM_SPEC(rl78ParamValues, sim_ac_flag, 1, "simulate PSW.AC flag"),
    VMI_BOOL_PARAM_SPEC(rl78ParamValues, exit_on_halt, 0, "simulation will exit on HALT instruction"),

    //#define VMI_UNS32_PARAM_SPEC(_STR,_NAME,_DEFAULT,_MIN,_MAX,_DESC)  {
    //    .name                      = #_NAME,
    //    .type                      = vmi_PT_UNS32,
    //    .u.uns32Param.defaultValue = _DEFAULT,
    //    .valueOffset               = VMI_PARAM_OFFSET(_STR,_NAME),
    //    .setBitOffset              = VMI_PARAM_OFFSET(_STR, SETBIT(_NAME)),
    //    .u.uns32Param.min          = _MIN,
    //    .u.uns32Param.max          = _MAX,
    //    .description               = _DESC,
    //    .sizeOf                    = sizeof(Uns32)
    //}
    VMI_UNS32_PARAM_SPEC(rl78ParamValues, mirror_rom_addr  , 0x02000, 0x00000, 0x0FFFF, "mirror rom addr"  ),
    VMI_UNS32_PARAM_SPEC(rl78ParamValues, mirror_start_addr, 0xF2000, 0xF0000, 0xFFFFF, "mirror start addr"),
    VMI_UNS32_PARAM_SPEC(rl78ParamValues, mirror_end_addr  , 0xFBFFF, 0xF0000, 0xFFFFF, "mirror end addr"  ),    // R5F109xD (x=6,A,B,G,L) mirror 40kb

    // End of list
    VMI_END_PARAM
};


//
// Function to iterate the parameter specs
//
VMI_PROC_PARAM_SPECS_FN(rl78GetParamSpec) {
    if(!prev) {
        return formals;
    } else {
        prev++;
        if (prev->name)
            return prev;
        else
            return 0;
    }
}

//
// Get the size of the parameter values table
//
VMI_PROC_PARAM_TABLE_SIZE_FN(rl78ParamValueSize) {
    return sizeof(rl78ParamValues);
}


