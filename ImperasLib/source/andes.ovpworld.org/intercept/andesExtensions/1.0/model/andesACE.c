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


// Standard header files
#include <string.h>

// Imperas header files
#include "hostapi/impTypes.h"

// VMI header files
#include "vmi/vmiMt.h"
#include "vmi/vmiRt.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiTypes.h"

// model header files
#include "andesACE.h"
#include "andesACEInterface.h"
#include "andesACEInterfaceTypeRefs.h"
#include "andesStructure.h"
#include "andesMessage.h"
#include "andesUtils.h"

// base model header files
#include "riscvStructure.h"


////////////////////////////////////////////////////////////////////////////////
// UTILITIES
////////////////////////////////////////////////////////////////////////////////

//
// Convert to ace_cpu from vmiosObjectP
//
inline static ace_cpuP to_ace_cpu(vmiosObjectP object) {
    return (ace_cpuP)object;
}

//
// Convert from ace_cpu to vmiosObjectP
//
inline static vmiosObjectP from_ace_cpu(ace_cpuP cpu) {
    return (vmiosObjectP)cpu;
}

//
// Get vector register size in 32-bit words
//
inline static Uns32 getVRegWords(riscvP riscv) {
    return riscv->configInfo.VLEN/32;
}

//
// Get vector register memory
//
inline static void *getVReg(riscvP riscv, Uns32 index) {
    return &riscv->v[index*getVRegWords(riscv)];
}

//
// Get processor data domain
//
inline static memDomainP getDataDomain(riscvP riscv) {
    return vmirtGetProcessorDataDomain((vmiProcessorP)riscv);
}

//
// Get processor ACM domain (bypassing all memory management)
//
inline static memDomainP getACMDomain(riscvP riscv) {
    return riscv->extDomains[0];
}

//
// Return ACM status for memMapped status
//
inline static acm_status getACMStatus(memMapped mapped) {
    return (mapped==MEM_MAP_FULL) ? ACMS_OK : ACMS_ERROR;
}

//
// Get current cycle count
//
inline static Uns64 getCycleCount(riscvP riscv) {
    return vmirtGetICount((vmiProcessorP)riscv);
}

//
// Get current instruction count
//
inline static Uns64 getInstructionCount(riscvP riscv) {
    return vmirtGetExecutedICount((vmiProcessorP)riscv);
}

//
// Get current PC
//
inline static Uns64 getCurrentPC(riscvP riscv) {
    return vmirtGetPC((vmiProcessorP)riscv);
}


////////////////////////////////////////////////////////////////////////////////
// CPU AGENT CALLBACKS
////////////////////////////////////////////////////////////////////////////////

//
// Get X register
//
static Uns64 get_XRF(ace_cpuP cpu, Uns32 index) {

    vmiosObjectP object = from_ace_cpu(cpu);
    riscvP       riscv  = object->riscv;

    return riscv->x[index];
}

//
// Set X register
//
static void set_XRF(ace_cpuP cpu, Uns32 index, Uns64 value) {

    vmiosObjectP object = from_ace_cpu(cpu);
    riscvP       riscv  = object->riscv;

    if(index) {
        riscv->x[index] = value;
    }
}

//
// Get F register
//
static Uns64 get_FRF(ace_cpuP cpu, Uns32 index) {

    vmiosObjectP object = from_ace_cpu(cpu);
    riscvP       riscv  = object->riscv;

    return riscv->f[index];
}

//
// Set F register
//
static void set_FRF(ace_cpuP cpu, Uns32 index, Uns64 value) {

    vmiosObjectP object = from_ace_cpu(cpu);
    riscvP       riscv  = object->riscv;

    riscv->f[index] = value;
}

//
// Get V register memory
//
static unsigned char *get_VRF(ace_cpuP cpu, Uns32 index) {

    vmiosObjectP object = from_ace_cpu(cpu);
    riscvP       riscv  = object->riscv;

    return getVReg(riscv, index);
}

//
// Set V register memory
//
static void set_VRF(ace_cpuP cpu, Uns32 index, unsigned char *value) {

    vmiosObjectP object = from_ace_cpu(cpu);
    riscvP       riscv  = object->riscv;

    memcpy(getVReg(riscv, index), value, getVRegWords(riscv)*4);
}

//
// Read memory
//
static Uns64 get_MEM(ace_cpuP cpu, Uns64 vaddr, Uns32 size) {

    vmiosObjectP object = from_ace_cpu(cpu);
    riscvP       riscv  = object->riscv;
    memDomainP   domain = getDataDomain(riscv);
    Uns64        result = 0;

    vmirtReadNByteDomain(domain, vaddr, &result, size, 0, MEM_AA_TRUE);

    return result;
}

//
// Write memory
//
static void set_MEM(ace_cpuP cpu, Uns64 vaddr, Uns64 value, Uns32 size) {

    vmiosObjectP object = from_ace_cpu(cpu);
    riscvP       riscv  = object->riscv;
    memDomainP   domain = getDataDomain(riscv);

    vmirtWriteNByteDomain(domain, vaddr, &value, size, 0, MEM_AA_TRUE);
}

//
// Read CSR
//
static Uns64 get_CSR(ace_cpuP cpu, Uns32 index, Uns64 mask) {

    vmiosObjectP object = from_ace_cpu(cpu);
    riscvP       riscv  = object->riscv;

    return riscv->cb.readCSR(riscv, index) & mask;
}

//
// Write CSR
//
static void set_CSR(ace_cpuP cpu, Uns32 index, Uns64 mask, Uns64 value) {

    vmiosObjectP object = from_ace_cpu(cpu);
    riscvP       riscv  = object->riscv;

    if(mask!=-1) {
        value = (value&mask) | (riscv->cb.readCSR(riscv, index)&~mask);
    }

    riscv->cb.writeCSR(riscv, index, value);
}

//
// Write CSR without mask
//
static void set_CSR_masked(ace_cpuP cpu, Uns32 index, Uns64 value) {

    vmiosObjectP object = from_ace_cpu(cpu);
    riscvP       riscv  = object->riscv;

    riscv->cb.writeCSR(riscv, index, value);
}

//
// Read ACM memory
//
static acm_status get_ACM(ace_cpuP cpu, Uns64 addr, Uns32 size, char *data) {

    vmiosObjectP object = from_ace_cpu(cpu);
    riscvP       riscv  = object->riscv;
    memDomainP   domain = getACMDomain(riscv);

    memMapped mapped = vmirtReadNByteDomain(
        domain, addr, data, size, 0, MEM_AA_TRUE
    );

    return getACMStatus(mapped);
}

//
// Write ACM memory
//
static acm_status set_ACM(ace_cpuP cpu, Uns64 addr, Uns32 size, char *data) {

    vmiosObjectP object = from_ace_cpu(cpu);
    riscvP       riscv  = object->riscv;
    memDomainP   domain = getACMDomain(riscv);

    memMapped mapped = vmirtWriteNByteDomain(
        domain, addr, data, size, 0, MEM_AA_TRUE
    );

    return getACMStatus(mapped);
}

//
// Get current data endian
//
static Bool is_big_endian(ace_cpuP cpu) {

    vmiosObjectP object = from_ace_cpu(cpu);
    riscvP       riscv  = object->riscv;

    return riscv->cb.getDataEndian(riscv, getCurrentMode5(riscv));
}

//
// TODO: Add register description
//
static void add_reg_desc(
    ace_cpuP          cpu,
    const char       *groupName,
    Uns32             groupIdx,
    Uns32             numOfEntry,
    Uns32             entryWidth,
    ace_register_type typeIn
) {
}

//
// Get current cycle count
//
static Uns64 get_current_cycle(ace_cpuP cpu) {

    vmiosObjectP object = from_ace_cpu(cpu);
    riscvP       riscv  = object->riscv;

    return getCycleCount(riscv);
}

//
// Get mstatus.XS
//
static Uns32 get_ACES(ace_cpuP cpu) {

    vmiosObjectP object = from_ace_cpu(cpu);
    riscvP       riscv  = object->riscv;

    return RD_CSR_FIELDC(riscv, mstatus, XS);
}

//
// Set mstatus.XS
//
static void set_ACES(ace_cpuP cpu, Uns32 value) {

    vmiosObjectP object = from_ace_cpu(cpu);
    riscvP       riscv  = object->riscv;

    WR_CSR_FIELDC(riscv, mstatus, XS, value);
}

//
// TODO: Return exception cause
//
static Uns64 get_cause_code(ace_cpuP cpu) {

    vmiosObjectP object = from_ace_cpu(cpu);

    return object->aceCause;
}

//
// Get current PC
//
static Uns64 get_PC(ace_cpuP cpu) {

    vmiosObjectP object = from_ace_cpu(cpu);
    riscvP       riscv  = object->riscv;

    return getCurrentPC(riscv);
}

//
// Get hart id
//
static Uns64 get_hart_id(ace_cpuP cpu) {

    vmiosObjectP object = from_ace_cpu(cpu);
    riscvP       riscv  = object->riscv;

    return RD_CSR(riscv, mhartid);
}

//
// Get execution privilege
// TODO: what is the encoding?
//
static Uns64 get_cpu_priv(ace_cpuP cpu) {

    vmiosObjectP object = from_ace_cpu(cpu);
    riscvP       riscv  = object->riscv;

    return getCurrentMode3(riscv);
}

//
// Get instruction count
//
static Uns64 get_IS(ace_cpuP cpu) {

    vmiosObjectP object = from_ace_cpu(cpu);
    riscvP       riscv  = object->riscv;

    return getInstructionCount(riscv);
}

//
// Has an exception been caused by this instruction?
//
static Bool exception_exist(ace_cpuP cpu) {

    vmiosObjectP object = from_ace_cpu(cpu);

    return object->aceCause;
}


////////////////////////////////////////////////////////////////////////////////
// CPU AGENT FUNCTION TABLE
////////////////////////////////////////////////////////////////////////////////

static ace_cpu_agent cpuAgent = {

    ////////////////////////////////////////////////////////////////////////////
    // DATA ACCESS
    ////////////////////////////////////////////////////////////////////////////

    .get_XRF           = get_XRF,
    .set_XRF           = set_XRF,
    .get_FRF           = get_FRF,
    .set_FRF           = set_FRF,
    .get_VRF           = get_VRF,
    .set_VRF           = set_VRF,
    .get_MEM           = get_MEM,
    .set_MEM           = set_MEM,
    .get_CSR           = get_CSR,
    .set_CSR           = set_CSR,
    .set_CSR_masked    = set_CSR_masked,

    ////////////////////////////////////////////////////////////////////////////
    // ACM ACCESS BYPASSING MMU
    ////////////////////////////////////////////////////////////////////////////

    .get_ACM           = get_ACM,
    .set_ACM           = set_ACM,

    ////////////////////////////////////////////////////////////////////////////
    // INFORMATION ACCESS
    ////////////////////////////////////////////////////////////////////////////

    .is_big_endian     = is_big_endian,

    ////////////////////////////////////////////////////////////////////////////
    // GDB TARGET DESCRIPTION
    ////////////////////////////////////////////////////////////////////////////

    .add_reg_desc      = add_reg_desc,

    ////////////////////////////////////////////////////////////////////////////
    // CPU CURRENT CYCLE
    ////////////////////////////////////////////////////////////////////////////

    .get_current_cycle = get_current_cycle,

    ////////////////////////////////////////////////////////////////////////////
    // GET/SET MSTATUS ACES BITS
    ////////////////////////////////////////////////////////////////////////////

    .get_ACES          = get_ACES,

    .set_ACES          = set_ACES,

    ////////////////////////////////////////////////////////////////////////////
    // GET EXCEPTION CAUSE CODE
    ////////////////////////////////////////////////////////////////////////////

    .get_cause_code    = get_cause_code,

    ////////////////////////////////////////////////////////////////////////////
    // GET PC
    ////////////////////////////////////////////////////////////////////////////

    .get_PC            = get_PC,

    ////////////////////////////////////////////////////////////////////////////
    // GET HART ID
    ////////////////////////////////////////////////////////////////////////////

    .get_hart_id       = get_hart_id,

    ////////////////////////////////////////////////////////////////////////////
    // GET CPU PRIV MODE
    ////////////////////////////////////////////////////////////////////////////

    .get_cpu_priv      = get_cpu_priv,

    ////////////////////////////////////////////////////////////////////////////
    // GET INSTRUCTION COUNT
    ////////////////////////////////////////////////////////////////////////////

    .get_IS            = get_IS,

    ////////////////////////////////////////////////////////////////////////////
    // TEST FOR EXCEPTION
    ////////////////////////////////////////////////////////////////////////////

    .exception_exist   = exception_exist
};


////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR, DESTRUCTOR AND RESET
////////////////////////////////////////////////////////////////////////////////

//
// Initialize ACE extension state
//
void andesACEInit(vmiosObjectP object) {

    vmiDLHandleP dlHandle;

    if(!object->aceFile) {

        // no ACE extension file

    } else if(!(dlHandle=vmirtDLOpen(object->aceFile))) {

        // bad ACE extension file
        vmiMessage("F", CPU_PREFIX "DLE1",
            "Error loading ACE file %s (%s)",
            object->aceFile, vmirtDLError()
        );

    } else if(!(object->aceAgent=vmirtDLSymbol(dlHandle, ACE_COPILOT_AGENT))) {

        // agent callback table not found
        vmiMessage("F", CPU_PREFIX "ACBE",
            "ACE copilot agent %s not found in ACE file %s",
            ACE_COPILOT_AGENT, object->aceFile
        );

    } else if(object->aceAgent->ext_version()!=ACE_VERSION) {

        // agent callback table not found
        vmiMessage("F", CPU_PREFIX "AVE",
            "ACE version mismatch: model:%x extension:%x",
            object->aceAgent->ext_version(),
            ACE_VERSION
        );

    } else {

        riscvP   riscv = object->riscv;
        ace_cpuP cpu   = to_ace_cpu(object);

        // mstatus.XS is writable if ACE instructions are configured
        WR_CSR_MASK_FIELDC(riscv, mstatus, XS, -1);

        // allocate extension
        ace_extP ext = object->aceExtension =
            object->aceAgent->ext_new(cpu, &cpuAgent);

        // initialize extension
        object->aceAgent->init(ext);

        // generate register descriptions
        if(object->aceAgent->generate_register_description) {
            object->aceAgent->generate_register_description(ext);
        }
    }
}

//
// Free ACE extension state
//
void andesACEFree(vmiosObjectP object) {

    ace_extP ext = object->aceExtension;

    if(ext) {
        object->aceAgent->ext_free(ext);
    }
}

//
// Reset ACE extension state
//
void andesACEReset(vmiosObjectP object) {

    ace_extP ext = object->aceExtension;

    if(ext && object->aceAgent->reset) {
        object->aceAgent->reset(ext);
    }
}


////////////////////////////////////////////////////////////////////////////////
// INSTRUCTION TRANSLATION AND DISASSEMBLY
////////////////////////////////////////////////////////////////////////////////

//
// TODO: Is the instruction an ACE instruction?
//
inline static Bool isACEInstruction(Uns32 insn_in) {

    switch(insn_in&0x7f) {
        case 0x0b:      // CUSTOM0 : 0001011
        case 0x2b:      // CUSTOM1 : 0101011
        case 0x6b:      // CUSTOM2 : 1011011
        case 0x7b:      // CUSTOM3 : 1111011
            return True;
        default:
            return False;
    }
}

//
// Run a single ACE instruction
//
static void runACE(vmiosObjectP object, Uns32 insn_in) {

    object->aceCause = 0;

    riscvP    riscv = object->riscv;
    ace_state state = object->aceAgent->run_insn(object->aceExtension, insn_in);

    if(state==ACES_RESERVED_INSN) {
        riscv->cb.illegalVerbose(riscv, "undecoded ACE instruction");
    }
}

//
// Emit code to handle an ACE instruction if required
//
Bool andesACEMorph(vmiosObjectP object, Uns32 insn_in) {

    ace_extP ext   = object->aceExtension;
    Bool     isACE = ext && isACEInstruction(insn_in);

    if(isACE) {
        vmimtArgNatAddress(object);
        vmimtArgUns32(insn_in);
        vmimtCallAttrs((vmiCallFn)runACE, VMCA_FP_RESTORE);
    }

    return isACE;
}

//
// Return ACE instruction disassembly
//
const char *andesACEDisassemble(vmiosObjectP object, Uns32 insn_in) {

    ace_extP    ext    = object->aceExtension;
    Bool        isACE  = ext && isACEInstruction(insn_in);
    const char *result = 0;

    if(isACE && object->aceAgent->get_insn_mnemonic) {
        result = object->aceAgent->get_insn_mnemonic(ext, insn_in);
    }

    return result;
}

