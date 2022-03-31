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
#include "vmi/vmiMessage.h"

// base model header files
#include "riscvStructure.h"

VMI_PROC_INFO_FN(riscvProcInfo) {

    riscvP riscv = (riscvP) processor;

    static const vmiVlnvInfo addCSRs = {
        .vendor      = "vendor.com",
        .library     = "intercept",
        .name        = "addCSRs",
        .version     = "1.0",
    };

    static const vmiVlnvInfo addInstructions = {
        .vendor      = "vendor.com",
        .library     = "intercept",
        .name        = "addInstructions",
        .version     = "1.0",
    };

    static const vmiVlnvInfo addExceptions = {
        .vendor      = "vendor.com",
        .library     = "intercept",
        .name        = "addExceptions",
        .version     = "1.0",
    };

    static const vmiVlnvInfo addLocalInterrupts = {
        .vendor      = "vendor.com",
        .library     = "intercept",
        .name        = "addLocalInterrupts",
        .version     = "1.0",
    };

    static const vmiVlnvInfo tmExtension = {
        .vendor      = "vendor.com",
        .library     = "intercept",
        .name        = "tmExtensions",
        .version     = "1.0",
    };

    static const vmiVlnvInfo fifoExtension = {
        .vendor      = "vendor.com",
        .library     = "intercept",
        .name        = "fifoExtensions",
        .version     = "1.0",
    };

    static const vmiVlnvInfoList addLocalInterruptsEntry = {
        next : 0,
        info : &addLocalInterrupts,
    };

    static const vmiVlnvInfoList addExceptionsEntry = {
        next : &addLocalInterruptsEntry,
        info : &addExceptions,
    };

    static const vmiVlnvInfoList addInstructionsEntry = {
        next : &addExceptionsEntry,
        info : &addInstructions,
    };

    static const vmiVlnvInfoList addCSRsEntry = {
        next : &addInstructionsEntry,
        info : &addCSRs,
    };

    static const vmiVlnvInfoList tmEntry = {
        next : &addCSRsEntry,
        info : &tmExtension,
    };

    static const vmiVlnvInfoList fifoEntry = {
        next : &tmEntry,
        info : &fifoExtension
    };

    static const vmiProcessorInfo info32 = {
        .vlnv.vendor      = "vendor.com",
        .vlnv.library     = "processor",
        .vlnv.name        = "riscv",
        .vlnv.version     = "1.0",

        .semihost.vendor  = "riscv.ovpworld.org",
        .semihost.library = "semihosting",
        .semihost.name    = "pk",
        .semihost.version = "1.0",

        .helper.vendor    = "imperas.com",
        .helper.library   = "intercept",
        .helper.name      = "riscv32CpuHelper",
        .helper.version   = "1.0",

        .mandatoryExtensions = &fifoEntry,

        .elfCode          = 243,
        .endianFixed      = True,
        .endian           = MEM_ENDIAN_LITTLE,
        .gdbPath          = "$IMPERAS_HOME/lib/$IMPERAS_ARCH/gdb/riscv-none-embed-gdb" VMI_EXE_SUFFIX,
        .gdbInitCommands  = "set architecture riscv:rv32",
        .family           = "Vendor",
        .QLQualified      = True
    };

    static const vmiProcessorInfo info64 = {
        .vlnv.vendor      = "vendor.com",
        .vlnv.library     = "processor",
        .vlnv.name        = "riscv",
        .vlnv.version     = "1.0",

        .semihost.vendor  = "riscv.ovpworld.org",
        .semihost.library = "semihosting",
        .semihost.name    = "pk",
        .semihost.version = "1.0",

        .helper.vendor    = "imperas.com",
        .helper.library   = "intercept",
        .helper.name      = "riscv64CpuHelper",
        .helper.version   = "1.0",

        .mandatoryExtensions = &fifoEntry,

        .elfCode          = 243,
        .endianFixed      = True,
        .endian           = MEM_ENDIAN_LITTLE,
        .gdbPath          = "$IMPERAS_HOME/lib/$IMPERAS_ARCH/gdb/riscv-none-embed-gdb" VMI_EXE_SUFFIX,
        .gdbInitCommands  = "set architecture riscv:rv64",
        .family           = "Vendor",
        .QLQualified      = True
    };

    return (riscv->configInfo.arch & ISA_XLEN_64) ? &info64 : &info32;
}

