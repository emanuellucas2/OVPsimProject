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

#include "v850Functions.h"
#include "v850Structure.h"

VMI_PROC_INFO_FN(v850ProcInfo) {

    static const Uns32 alternativeElfCodes[] = {36, 28913, 28927, 29819, 0};

    static const vmiProcessorInfo info_rh850g3m = {
        .vlnv.vendor         = "renesas.ovpworld.org",
        .vlnv.library        = "processor",
        .vlnv.name           = "rh850",
        .vlnv.version        = "1.0",

        .semihost.vendor     = "renesas.ovpworld.org",
        .semihost.library    = "semihosting",
        .semihost.name       = "v850Newlib",
        .semihost.version    = "1.0",

        .helper.vendor       = "imperas.com",
        .helper.library      = "intercept",
        .helper.name         = "v850CpuHelper",
        .helper.version      = "1.0",

        .elfCode             = 87,
        .alternativeElfCodes = alternativeElfCodes,
        .defaultModel        = False,
        .endianFixed         = True,
        .endian              = MEM_ENDIAN_LITTLE,
        .gdbPath             = "$IMPERAS_HOME/lib/$IMPERAS_ARCH/gdb/v850-elf-gdb" VMI_EXE_SUFFIX,
        .gdbInitCommands     = "set architecture v850e3v5",
        .family              = "renesas_rh850",
        .defaultModel        = True,
        .QLQualified         = True,
    };

    vmiProcessorInfoCP cp;
    v850P v850 = (v850P)processor;

    if (v850->configInfo.arch  == RH850G3M) {
        cp = &info_rh850g3m;
    } else {
        cp = &info_rh850g3m;
    }

    return cp;
}

