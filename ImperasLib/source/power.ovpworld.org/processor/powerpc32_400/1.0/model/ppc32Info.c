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

#include "vmi/vmiAttrs.h"
#include "vmi/vmiModelInfo.h"
#include "hostapi/impAlloc.h"

#include "ppc32Functions.h"

VMI_PROC_INFO_FN(ppc32ProcInfo) {
    static vmiProcessorInfo info;
    info.vlnv.vendor      = "power.ovpworld.org";
    info.vlnv.library     = "processor";
    info.vlnv.name        = "powerpc32_400";
    info.vlnv.version     = "1.0";

    info.semihost.vendor  = "power.ovpworld.org";
    info.semihost.library = "semihosting";
    info.semihost.name    = "powerpc32Newlib";
    info.semihost.version = "1.0";

    info.helper.vendor    = "imperas.com";
    info.helper.library   = "intercept";
    info.helper.name      = "powerpc32CpuHelper";
    info.helper.version   = "1.0";

    info.elfCode          = 20;
    info.defaultModel     = False;
    info.endianFixed      = False;
    info.endian           = MEM_ENDIAN_BIG;
    info.gdbPath          = "$IMPERAS_HOME/lib/$IMPERAS_ARCH/gdb/powerpc-elf-gdb" VMI_EXE_SUFFIX;
    info.family           = "powerpc";
    info.defaultModel     = True;
    info.QLQualified      = True;

    return &info;
}

