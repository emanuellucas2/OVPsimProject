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
#include "vmi/vmiModelInfo.h"

#include "or1kFunctions.h"

#define VENDOR  "ovpworld.org"
#define LIBRARY "processor"
#define NAME    "or1k"
#define VERSION "1.0"

VMI_PROC_INFO_FN(or1kProcInfo) {
    static const vmiProcessorInfo info = {
        .vlnv.vendor      = VENDOR            ,
        .vlnv.library     = LIBRARY           ,
        .vlnv.name        = NAME              ,
        .vlnv.version     = VERSION           ,

        .semihost.vendor  = VENDOR            ,
        .semihost.library = "semihosting"     ,
        .semihost.name    = "or1kNewlib"      ,
        .semihost.version = VERSION           ,

        .helper.vendor    = "imperas.com"     ,
        .helper.library   = "intercept"       ,
        .helper.name      = "or1kCpuHelper"   ,
        .helper.version   = "1.0"             ,

        .debugHelper.vendor  = "imperas.com"     ,
        .debugHelper.library = "intercept"       ,
        .debugHelper.name    = "or1kDebugHelper"   ,
        .debugHelper.version = "1.0"             ,

        .groupH           = "or1k",

        .elfCode          = 33906,
        .endianFixed      = True,
        .endian           = MEM_ENDIAN_BIG,
        .gdbPath          = "$IMPERAS_HOME/lib/$IMPERAS_ARCH/CrossCompiler/or32-elf/bin/or32-elf-gdb" VMI_EXE_SUFFIX,
        .family           = "openCores",
        .defaultModel     = True,
        .QLQualified      = True,
    };
    return &info;
}
