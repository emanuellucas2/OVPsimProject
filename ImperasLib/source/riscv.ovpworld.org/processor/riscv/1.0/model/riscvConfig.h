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

#pragma once

// Imperas header files
#include "hostapi/impTypes.h"

// VMI header files
#include "vmi/vmiTyperefs.h"

// model header files
#include "riscvCSR.h"
#include "riscvFeatures.h"
#include "riscvTypeRefs.h"
#include "riscvVariant.h"

//
// This default value indicates all bits writable in arch except E, S and U
//
#define RV_ARCH_MASK_DEFAULT (~(ISA_XLEN_ANY|ISA_E|ISA_S|ISA_U))

//
// Function type for adding documentation
//
#define RV_DOC_FN(_NAME) void _NAME(riscvP riscv, vmiDocNodeP node)
typedef RV_DOC_FN((*riscvDocFn));

//
// value indicating numHarts is 0 but configurable
//
#define RV_NUMHARTS_0 -1

//
// This is used to specify documentation and configuration for mandatory
// extensions
//
typedef struct riscvExtConfigS {
    Uns32        id;                    // unique extension ID
    const void  *userData;              // extension-specific constant data
} riscvExtConfig;

//
// This is used to define a processor configuration option
//
typedef struct riscvConfigS {

    const char       *name;             // variant name

    // fundamental variant configuration
    riscvArchitecture arch;             // variant architecture
    riscvArchitecture archImplicit;     // implicit feature bits (not in misa)
    riscvArchitecture archMask;         // read/write bits in architecture
    riscvArchitecture archFixed;        // fixed bits in architecture
    riscvUserVer      user_version;     // user-level ISA version
    riscvPrivVer      priv_version;     // privileged architecture version
    riscvVectVer      vect_version;     // vector architecture version
    riscvVectorSet    vect_profile;     // vector architecture profile
    riscvBitManipVer  bitmanip_version; // bitmanip architecture version
    riscvBitManipSet  bitmanip_absent;  // bitmanip absent extensions
    riscvCryptoVer    crypto_version;   // cryptographic architecture version
    riscvCryptoSet    crypto_absent;    // cryptographic absent extensions
    riscvDSPVer       dsp_version;      // DSP architecture version
    riscvDSPSet       dsp_absent;       // DSP absent extensions
    riscvCompressSet  compress_present; // compressed present extensions
    riscvHypVer       hyp_version;      // hypervisor architecture version
    riscvDebugVer     dbg_version;      // debugger architecture version
    riscvRNMIVer      rnmi_version;     // rnmi version
    riscvSmepmpVer    Smepmp_version;   // Smepmp version
    riscvCLICVer      CLIC_version;     // CLIC version
    riscvZfinxVer     Zfinx_version;    // Zfinx version
    riscvZceaVer      Zcea_version;     // Zcea version
    riscvZcebVer      Zceb_version;     // Zceb version
    riscvZceeVer      Zcee_version;     // Zcee version
    riscvFP16Ver      fp16_version;     // 16-bit floating point version
    riscvFSMode       mstatus_fs_mode;  // mstatus.FS update mode
    riscvDMMode       debug_mode;       // is Debug mode implemented?
    riscvDERETMode    debug_eret_mode;  // debug mode MRET, SRET or DRET action
    const char      **members;          // cluster member variants

    // configuration not visible in CSR state
    Uns64 reset_address;                // reset vector address
    Uns64 nmi_address;                  // NMI address
    Uns64 nmiexc_address;               // RNMI exception address
    Uns64 debug_address;                // debug vector address
    Uns64 dexc_address;                 // debug exception address
    Uns64 CLINT_address;                // internally-implemented CLINT address
    Flt64 mtime_Hz;                     // clock frequency of CLINT mtime
    Uns64 unimp_int_mask;               // mask of unimplemented interrupts
    Uns64 force_mideleg;                // always-delegated M-mode interrupts
    Uns64 force_sideleg;                // always-delegated S-mode interrupts
    Uns64 no_ideleg;                    // non-delegated interrupts
    Uns64 no_edeleg;                    // non-delegated exceptions
    Uns64 ecode_mask;                   // implemented bits in xcause.ecode
    Uns64 ecode_nmi;                    // exception code for NMI
    Uns64 ecode_nmi_mask;               // implemented bits in mncause.ecode
    Uns64 Svnapot_page_mask;            // implemented Svnapot page sizes
    Uns32 counteren_mask;               // counter-enable implemented mask
    Uns32 noinhibit_mask;               // counter no-inhibit mask
    Uns32 local_int_num;                // number of local interrupts
    Uns32 lr_sc_grain;                  // LR/SC region grain size
#if(ENABLE_SSMPU)
    Uns32 MPU_grain;                    // MPU region grain size
#endif
    Uns32 PMP_grain;                    // PMP region grain size
#if(ENABLE_SSMPU)
    Uns32 MPU_registers;                // number of implemented MPU regions
#endif
    Uns32 PMP_registers;                // number of implemented PMP regions
    Uns32 PMP_max_page;                 // maximum size of PMP page to map
    Uns32 Sv_modes;                     // bit mask of valid Sv modes
    Uns32 numHarts;                     // number of hart contexts if MPCore
    Uns32 tvec_align;                   // trap vector alignment (vectored mode)
    Uns32 ELEN;                         // ELEN (vector extension)
    Uns32 SLEN;                         // SLEN (vector extension)
    Uns32 VLEN;                         // VLEN (vector extension)
    Uns32 EEW_index;                    // maximum index EEW (vector extension)
    Uns32 SEW_min;                      // minimum SEW (vector extension)
    Uns32 ASID_cache_size;              // ASID cache size
    Uns16 tinfo;                        // tinfo default value (all triggers)
    Uns16 cmomp_bytes;                  // cache block bytes (management/prefetch)
    Uns16 cmoz_bytes;                   // cache block bytes (zero)
    Uns8  ASID_bits;                    // number of implemented ASID bits
    Uns8  VMID_bits;                    // number of implemented VMID bits
    Uns8  trigger_num;                  // number of implemented triggers
    Uns8  mcontext_bits;                // implemented bits in mcontext
    Uns8  scontext_bits;                // implemented bits in scontext
    Uns8  mvalue_bits;                  // implemented bits in textra.mvalue
    Uns8  svalue_bits;                  // implemented bits in textra.svalue
    Uns8  mcontrol_maskmax;             // configured value of mcontrol.maskmax
    Uns8  dcsr_ebreak_mask;             // mask of writable dcsr.ebreak* bits
    Uns8  mtvec_sext;                   // mtvec sign-extended bit count
    Uns8  stvec_sext;                   // stvec sign-extended bit count
    Uns8  utvec_sext;                   // utvec sign-extended bit count
    Uns8  mtvt_sext;                    // mtvec sign-extended bit count
    Uns8  stvt_sext;                    // stvec sign-extended bit count
    Uns8  utvt_sext;                    // utvec sign-extended bit count
    Bool  isPSE                : 1;     // whether a PSE (internal use only)
    Bool  enable_expanded      : 1;     // enable expanded instructions
    Bool  endianFixed          : 1;     // endianness is fixed (UBE/SBE/MBE r/o)
    Bool  use_hw_reg_names     : 1;     // use hardware names for X/F registers
    Bool  ABI_d                : 1;     // ABI uses D registers for parameters
    Bool  agnostic_ones        : 1;     // when agnostic elements set to 1
    Bool  MXL_writable         : 1;     // writable bits in misa.MXL
    Bool  SXL_writable         : 1;     // writable bits in mstatus.SXL
    Bool  UXL_writable         : 1;     // writable bits in mstatus.UXL
    Bool  VSXL_writable        : 1;     // writable bits in mstatus.VSXL
    Bool  Svpbmt               : 1;     // Svpbmt implemented?
    Bool  Svinval              : 1;     // Svinval implemented?
    Bool  Zmmul                : 1;     // Zmmul implemented?
    Bool  Zfhmin               : 1;     // Zfhmin implemented?
    Bool  Zvlsseg              : 1;     // Zvlsseg implemented?
    Bool  Zvamo                : 1;     // Zvamo implemented?
    Bool  Zvediv               : 1;     // Zvediv implemented?
    Bool  Zvqmac               : 1;     // Zvqmac implemented?
    Bool  unitStrideOnly       : 1;     // only unit-stride operations supported
    Bool  noFaultOnlyFirst     : 1;     // fault-only-first instructions absent?
    Bool  Zicbom               : 1;     // whether Zicbom is present
    Bool  Zicbop               : 1;     // whether Zicbop is present
    Bool  Zicboz               : 1;     // whether Zicboz is present
    Bool  noZicsr              : 1;     // whether Zicsr is absent
    Bool  noZifencei           : 1;     // whether Zifencei is absent
    Bool  updatePTEA           : 1;     // hardware update of PTE A bit?
    Bool  updatePTED           : 1;     // hardware update of PTE D bit?
    Bool  unaligned            : 1;     // whether unaligned accesses supported
    Bool  unalignedAMO         : 1;     // whether AMO supports unaligned
    Bool  wfi_is_nop           : 1;     // whether WFI is treated as NOP
    Bool  mtvec_is_ro          : 1;     // whether mtvec is read-only
    Bool  cycle_undefined      : 1;     // whether cycle CSR is undefined
    Bool  time_undefined       : 1;     // whether time CSR is undefined
    Bool  instret_undefined    : 1;     // whether instret CSR is undefined
    Bool  hpmcounter_undefined : 1;     // whether hpmcounter* CSRs undefined
    Bool  tinfo_undefined      : 1;     // whether tinfo CSR is undefined
    Bool  tcontrol_undefined   : 1;     // whether tcontrol CSR is undefined
    Bool  mcontext_undefined   : 1;     // whether mcontext CSR is undefined
    Bool  scontext_undefined   : 1;     // whether scontext CSR is undefined
    Bool  mscontext_undefined  : 1;     // whether mscontext CSR is undefined
    Bool  hcontext_undefined   : 1;     // whether hcontext CSR is undefined
    Bool  mnoise_undefined     : 1;     // whether mnoise CSR is undefined
    Bool  amo_trigger          : 1;     // whether triggers used with AMO
    Bool  no_hit               : 1;     // whether tdata1.hit is unimplemented
    Bool  no_sselect_2         : 1;     // whether textra.sselect=2 is illegal
    Bool  d_requires_f         : 1;     // whether misa D requires F to be set
    Bool  enable_fflags_i      : 1;     // whether fflags_i register present
    Bool  mstatus_FS_zero      : 1;     // whether mstatus.FS hardwired to zero
    Bool  trap_preserves_lr    : 1;     // whether trap preserves active LR/SC
    Bool  xret_preserves_lr    : 1;     // whether xret preserves active LR/SC
    Bool  require_vstart0      : 1;     // require vstart 0 if uninterruptible?
    Bool  align_whole          : 1;     // whole register load aligned to hint?
    Bool  vill_trap            : 1;     // trap instead of setting vill?
    Bool  enable_CSR_bus       : 1;     // enable CSR implementation bus
    Bool  mcounteren_present   : 1;     // force mcounteren to be present
#if(ENABLE_SSMPU)
    Bool  MPU_decompose        : 1;     // decompose unaligned MPU accesses
#endif
    Bool  PMP_decompose        : 1;     // decompose unaligned PMP accesses
    Bool  PMP_undefined        : 1;     // force all PMP registers undefined
    Bool  external_int_id      : 1;     // enable external interrupt ID ports
    Bool  tval_zero            : 1;     // whether [smu]tval are always zero
    Bool  tval_zero_ebreak     : 1;     // whether [smu]tval always zero on ebreak
    Bool  tval_ii_code         : 1;     // instruction bits in [smu]tval for
                                        // illegal instruction exception?
    Bool  defer_step_bug       : 1;     // defer step breakpoint for one
                                        // instruction when interrupt on return
                                        // from debug mode (hardware bug)
    // CLIC configuration
    Bool  CLICANDBASIC         : 1;     // whether implements basic mode also
    Bool  CLICSELHVEC          : 1;     // selective hardware vectoring?
    Bool  CLICXNXTI            : 1;     // *nxti CSRs implemented?
    Bool  CLICXCSW             : 1;     // *scratchcs* CSRs implemented?
    Bool  externalCLIC         : 1;     // is CLIC externally implemented?
    Bool  tvt_undefined        : 1;     // whether *tvt CSRs are undefined
    Bool  intthresh_undefined  : 1;     // whether *intthresh CSRs undefined
    Bool  mclicbase_undefined  : 1;     // whether mclicbase CSR is undefined
    Bool  posedge_other        : 1;     // fixed int[64:N] positive edge
    Bool  poslevel_other       : 1;     // fixed int[64:N] positive level
    Uns64 posedge_0_63;                 // fixed int[63:0] positive edge
    Uns64 poslevel_0_63;                // fixed int[63:0] positive level
    Uns32 CLICLEVELS;                   // number of CLIC interrupt levels
    Uns8  CLICVERSION;                  // CLIC version
    Uns8  CLICINTCTLBITS;               // bits implemented in clicintctl[i]
    Uns8  CLICCFGMBITS;                 // bits implemented for cliccfg.nmbits
    Uns8  CLICCFGLBITS;                 // bits implemented for cliccfg.nlbits

    // Hypervisor configuration
    Uns8  GEILEN;                       // number of guest external interrupts
    Bool  xtinst_basic;                 // only pseudo-instruction in xtinst

    // CSR register values
    struct {
        CSR_REG_DECL (mvendorid);       // mvendorid value
        CSR_REG_DECL (marchid);         // marchid value
        CSR_REG_DECL (mimpid);          // mimpid value
        CSR_REG_DECL (mhartid);         // mhartid value
        CSR_REG_DECL (mconfigptr);      // mconfigptr value
        CSR_REG_DECL (mtvec);           // mtvec value
        CSR_REG_DECL (mstatus);         // mstatus reset value
        CSR_REG_DECL (mclicbase);       // mclicbase value
    } csr;

    // CSR register masks
    struct {
        CSR_REG_DECL (mtvec);           // mtvec mask
        CSR_REG_DECL (stvec);           // stvec mask
        CSR_REG_DECL (utvec);           // utvec mask
        CSR_REG_DECL (mtvt);            // mtvec mask
        CSR_REG_DECL (stvt);            // stvec mask
        CSR_REG_DECL (utvt);            // utvec mask
        CSR_REG_DECL (tdata1);          // tdata1 mask
        CSR_REG_DECL (mip);             // mip mask
        CSR_REG_DECL (sip);             // sip mask
        CSR_REG_DECL (uip);             // uip mask
        CSR_REG_DECL (hip);             // hip mask
        CSR_REG_DECL (envcfg);          // envcfg mask
    } csrMask;

    // custom documentation
    const char      **specificDocs;     // custom documentation
    riscvDocFn        restrictionsCB;   // custom restrictions

    // extension configuration information
    riscvExtConfigCPP extensionConfigs; // null-terminated list of extension
                                        // configurations

} riscvConfig;

//
// This returns the supported configuration list
//
riscvConfigCP riscvGetConfigList(riscvP riscv);

