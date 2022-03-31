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

// model header files
#include "riscvConfig.h"
#include "riscvVariant.h"
#include "riscvVMConstants.h"

/*
 * Priv, 1.11
 * User, 2.3
 * XLEN, 32
 * MISA, WARL, hardwired
 *   misa_MXL_mask=0x0
 *   misa_Extensions_mask=0x0
 * MVENDORID, not-implemented
 * MARCHID, not-implemented
 * MIMPID, not-implemented
 * MHARTID, not-implemented
 *     mhartid=N RTL_DEFINED
 * MTVEC, WARL, hardwire, MODE=2'b01, VECTOR=Fixed
 *   mtvec_mask=0
 *   mtvec=RTL_DEFINED BOOTADDR(+0x80) ?
 * MTIME, not-implemented
 * MCYCLE, RW
 * MINSTRET, RW
 * MTVAL, Insrtuction bit pattern, faulting addr for LSU
 * ResetVector BootAddress+0x80
 * Local Int = 16
 * NMI = 1
 * NMI_VecAddress, Unkown
 *     nmi_address=X
 * Physical Addr Range = 32
 *     cpu/addrbits=32
 * PMP, not-implemented
 * VirtualMemory, not-implemented
 * Atomics, unsupported
 * WFI, true
 * Unaligned memory accesses, True
 *
 * MCAUSE can generate aborts for memory failed transaction
 * in the hardware this is indicated by data_err_i and data_rvalid_i
 */

//
// variant documentation
//
static const char *specificDocsRV32IC[] = {
    "---- lowRISC https://ibex-core.readthedocs.io/en/latest",
    0
};
static const char *specificDocsRV32IMC[] = {
    "---- lowRISC https://ibex-core.readthedocs.io/en/latest",
    0
};
static const char *specificDocsRV32EC[] = {
    "---- lowRISC https://ibex-core.readthedocs.io/en/latest",
    0
};
static const char *specificDocsRV32EMC[] = {
    "---- lowRISC https://ibex-core.readthedocs.io/en/latest",
    0
};
static const char *specificDocsRV32IMCB[] = {
    "---- lowRISC https://ibex-core.readthedocs.io/en/latest",
    0
};

#define RV32IC   (ISA_XLEN_32|ISA_I      |ISA_C)
#define RV32IMC  (ISA_XLEN_32|ISA_I|ISA_M|ISA_C)
#define RV32IMCB (ISA_XLEN_32|ISA_I|ISA_M|ISA_C|ISA_B)
#define RV32CE   (ISA_XLEN_32|ISA_E      |ISA_C)
#define RV32MCE  (ISA_XLEN_32|ISA_E|ISA_M|ISA_C)

//
// Defined configurations
//
static const riscvConfig configList[] = {
    {
        .name            = "Ibex_RV32IC",
        .arch            = RV32IC,
        .archMask        = 0,
        .user_version    = RVUV_20190305,
        .priv_version    = RVPV_20190405,
        .specificDocs    = specificDocsRV32IC,
        .PMP_registers   = 0,
        .unaligned       = 1,
        .tval_ii_code    = True,
        .local_int_num   = 16,
        .time_undefined  = True,
        .tvec_align      = 256,
        .ecode_mask      = 0x1f,
        .counteren_mask  = -1,
        .csr = {
            .mtvec = {u32 : {bits : 0x00000001}},
        },
        .csrMask = {
            .mtvec = {u32 : {bits : 0xfffffffc}},
        }
    },
    {
        .name            = "Ibex_RV32IMC",
        .arch            = RV32IMC,
        .archMask        = 0,
        .user_version    = RVUV_20190305,
        .priv_version    = RVPV_20190405,
        .specificDocs    = specificDocsRV32IMC,
        .PMP_registers   = 0,
        .unaligned       = 1,
        .tval_ii_code    = True,
        .local_int_num   = 16,
        .time_undefined  = True,
        .tvec_align      = 256,
        .ecode_mask      = 0x1f,
        .counteren_mask  = -1,
        .csr = {
            .mtvec = {u32 : {bits : 0x00000001}},
        },
        .csrMask = {
            .mtvec = {u32 : {bits : 0xfffffffc}},
        }
    },
    {
        .name            = "Ibex_RV32EC",
        .arch            = RV32CE,
        .archMask        = 0,
        .user_version    = RVUV_20190305,
        .priv_version    = RVPV_20190405,
        .specificDocs    = specificDocsRV32EC,
        .PMP_registers   = 0,
        .unaligned       = 1,
        .tval_ii_code    = True,
        .local_int_num   = 16,
        .time_undefined  = True,
        .tvec_align      = 256,
        .ecode_mask      = 0x1f,
        .counteren_mask  = -1,
        .csr = {
            .mtvec = {u32 : {bits : 0x00000001}},
        },
        .csrMask = {
            .mtvec = {u32 : {bits : 0xfffffffc}},
        }
    },
    {
        .name            = "Ibex_RV32EMC",
        .arch            = RV32MCE,
        .archMask        = 0,
        .user_version    = RVUV_20190305,
        .priv_version    = RVPV_20190405,
        .specificDocs    = specificDocsRV32EMC,
        .PMP_registers   = 0,
        .unaligned       = 1,
        .tval_ii_code    = True,
        .local_int_num   = 16,
        .time_undefined  = True,
        .tvec_align      = 256,
        .ecode_mask      = 0x1f,
        .counteren_mask  = -1,
        .csr = {
            .mtvec = {u32 : {bits : 0x00000001}},
        },
        .csrMask = {
            .mtvec = {u32 : {bits : 0xfffffffc}},
        }
    },
    {
        .name               = "Ibex_RV32IMCB",
        .arch               = RV32IMCB,
        .archMask           = 0,
        .user_version       = RVUV_20190305,
        .priv_version       = RVPV_20190405,
        .bitmanip_version   = RVBV_0_92,
        .specificDocs       = specificDocsRV32IMCB,
        .PMP_registers      = 0,
        .unaligned          = 1,
        .tval_ii_code       = True,
        .local_int_num      = 16,
        .time_undefined     = True,
        .tvec_align      = 256,
        .ecode_mask         = 0x1f,
        .counteren_mask     = -1,
        .csr = {
            .mtvec = {u32 : {bits : 0x00000001}},
        },
        .csrMask = {
            .mtvec = {u32 : {bits : 0xfffffffc}},
        }
    },

    {0} // null terminator
};

//
// This returns the supported configuration list
//
riscvConfigCP riscvGetConfigList(riscvP riscv) {
    return configList;
}

