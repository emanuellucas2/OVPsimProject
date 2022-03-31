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



// VMI header files
#include "vmi/vmiAttrs.h"
#include "vmi/vmiModelInfo.h"
#include "hostapi/impAlloc.h"

#include "m16cFunctions.h"
#include "m16cStructure.h"

#define VENDOR  "posedgesoft.ovpworld.org"
#define LIBRARY "processor"
#define NAME    "m16c"
#define VERSION "1.0"

VMI_PROC_INFO_FN(m16cProcInfo) {

    static const Uns32 alternativeElfCodes[] = {120, 0};

    static const vmiProcessorInfo info = {
        .vlnv.vendor         = VENDOR,
        .vlnv.library        = LIBRARY,
        .vlnv.name           = NAME,
        .vlnv.version        = VERSION,

        .semihost.vendor     = VENDOR,
        .semihost.library    = "semihosting",
        .semihost.name       = "m16cNewlib",
        .semihost.version    = VERSION,

        .elfCode             = 117,
        .alternativeElfCodes = alternativeElfCodes,
        .endianFixed         = True,
        .endian              = MEM_ENDIAN_LITTLE,
        .gdbPath             = "$IMPERAS_HOME/lib/$IMPERAS_ARCH/gdb/m32c-elf-gdb" VMI_EXE_SUFFIX,
        .gdbInitCommands     = "set architecture m16c",
        .family              = "Renesas",
        .defaultModel        = True,
    };

    return &info;
}
