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

// basic types
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// model header files
#include "andesACEInterfaceTypeRefs.h"

// state returned by copilot_agent
typedef enum ace_stateE {
    ACES_OK,
    ACES_RESERVED_INSN,
    ACES_EXCEPTION,
    ACES_INTERNAL_ERROR
} ace_state;

// status returned by ACM access
typedef enum acm_statusE {
    ACMS_OK,
    ACMS_ERROR
} acm_status;

// gdb target description
typedef enum ace_register_typeE {
    ACRT_UNSPECIFIED,
    ACRT_DATA_POINTER,
    ACRT_CODE_POINTER,
    ACRT_FLOAT,
    ACRT_DOUBLE,
    ACRT_UINT8
} ace_register_type;

//
// Copilot agent symbol
//
#define ACE_COPILOT_AGENT "modelAttrs"

//
// Implemented version of this interface
//
#define ACE_VERSION 0x20211101

//
// This structure defines functions that must be implemented by the ACE
// extension
//
typedef struct ace_copilot_agentS {

    ////////////////////////////////////////////////////////////////////////////
    // BASIC
    ////////////////////////////////////////////////////////////////////////////

    uint32_t (*ext_version)(void);

    ace_extP (*ext_new)(ace_cpuP cpu, ace_cpu_agentP cpu_agent);

    void (*ext_free)(ace_extP ext);

    ace_state (*run_insn)(ace_extP ext, uint32_t insn_in);

    ////////////////////////////////////////////////////////////////////////////
    // CONFIGURATION
    ////////////////////////////////////////////////////////////////////////////

    const char *(*set_option)(ace_extP ext, const char *option);

    void (*init)(ace_extP ext);

    void (*reset)(ace_extP ext);

    ////////////////////////////////////////////////////////////////////////////
    // GDB TARGET DESCRIPTION
    ////////////////////////////////////////////////////////////////////////////

    void (*generate_register_description)(ace_extP ext);

    uint64_t (*get_register)(
        ace_extP    ext,
        uint32_t    group,
        uint32_t    index,
        uint32_t   *value_len
    );

    void (*set_register)(
        ace_extP    ext,
        uint32_t    group,
        uint32_t    index,
        uint64_t    value,
        uint32_t   *value_len
    );

    ////////////////////////////////////////////////////////////////////////////
    // ACE PIN HANDLER
    ////////////////////////////////////////////////////////////////////////////

    // TODO: how does this work?
    void (*init_pin_handler)(ace_extP ext, void *handler_in);

    ////////////////////////////////////////////////////////////////////////////
    // ACE ACM HANDLER
    ////////////////////////////////////////////////////////////////////////////

    // TODO: how does this work?
    void (*init_acm_handler)(ace_extP ext, void *handler_in);

    ////////////////////////////////////////////////////////////////////////////
    // ACE MNEMONIC
    ////////////////////////////////////////////////////////////////////////////

    const char *(*get_insn_mnemonic)(ace_extP ext, uint32_t insn_in);

} ace_copilot_agent;

//
// This structure defines functions that must be implemented by the OVP Andes
// processor model
//
typedef struct ace_cpu_agentS {

    ////////////////////////////////////////////////////////////////////////////
    // DATA ACCESS
    ////////////////////////////////////////////////////////////////////////////

    uint64_t (*get_XRF)(ace_cpuP cpu, uint32_t index);

    void (*set_XRF)(ace_cpuP cpu, uint32_t index, uint64_t value);

    uint64_t (*get_FRF)(ace_cpuP cpu, uint32_t index);

    void (*set_FRF)(ace_cpuP cpu, uint32_t index, uint64_t value);

    uint8_t *(*get_VRF)(ace_cpuP cpu, uint32_t index);

    void (*set_VRF)(ace_cpuP cpu, uint32_t index, uint8_t *value);

    uint64_t (*get_MEM)(ace_cpuP cpu, uint64_t vaddr, uint32_t size);

    void (*set_MEM)(ace_cpuP cpu, uint64_t vaddr, uint64_t value, uint32_t size);

    uint64_t (*get_CSR)(ace_cpuP cpu, uint32_t index, uint64_t mask);

    void (*set_CSR)(ace_cpuP cpu, uint32_t index, uint64_t mask, uint64_t value);

    void (*set_CSR_masked)(ace_cpuP cpu, uint32_t index, uint64_t value);

    ////////////////////////////////////////////////////////////////////////////
    // ACM ACCESS BYPASSING MMU
    ////////////////////////////////////////////////////////////////////////////

    acm_status (*get_ACM)(ace_cpuP cpu, uint64_t addr, uint32_t size, char *data);

    acm_status (*set_ACM)(ace_cpuP cpu, uint64_t addr, uint32_t size, char *data);

    ////////////////////////////////////////////////////////////////////////////
    // INFORMATION ACCESS
    ////////////////////////////////////////////////////////////////////////////

    bool (*is_big_endian)(ace_cpuP cpu);

    ////////////////////////////////////////////////////////////////////////////
    // GDB TARGET DESCRIPTION
    ////////////////////////////////////////////////////////////////////////////

    void (*add_reg_desc)(
        ace_cpuP          cpu,
        const char       *groupName,
        uint32_t          groupIdx,
        uint32_t          numOfEntry,
        uint32_t          entryWidth,
        ace_register_type typeIn
    );

    ////////////////////////////////////////////////////////////////////////////
    // CPU CURRENT CYCLE
    ////////////////////////////////////////////////////////////////////////////

    uint64_t (*get_current_cycle)(ace_cpuP cpu);

    ////////////////////////////////////////////////////////////////////////////
    // GET/SET MSTATUS ACES BITS
    ////////////////////////////////////////////////////////////////////////////

    uint32_t (*get_ACES)(ace_cpuP cpu);

    void (*set_ACES)(ace_cpuP cpu, uint32_t value);

    ////////////////////////////////////////////////////////////////////////////
    // GET EXCEPTION CAUSE CODE
    ////////////////////////////////////////////////////////////////////////////

    // TODO: what is this?
    uint64_t (*get_cause_code)(ace_cpuP cpu);

    ////////////////////////////////////////////////////////////////////////////
    // GET PC
    ////////////////////////////////////////////////////////////////////////////

    uint64_t (*get_PC)(ace_cpuP cpu);

    ////////////////////////////////////////////////////////////////////////////
    // GET HART ID
    ////////////////////////////////////////////////////////////////////////////

    uint64_t (*get_hart_id)(ace_cpuP cpu);

    ////////////////////////////////////////////////////////////////////////////
    // GET CPU PRIV MODE
    ////////////////////////////////////////////////////////////////////////////

    uint64_t (*get_cpu_priv)(ace_cpuP cpu);

    ////////////////////////////////////////////////////////////////////////////
    // GET INSTRUCTION COUNT
    ////////////////////////////////////////////////////////////////////////////

    uint64_t (*get_IS)(ace_cpuP cpu);

    ////////////////////////////////////////////////////////////////////////////
    // TEST FOR EXCEPTION
    ////////////////////////////////////////////////////////////////////////////

    bool (*exception_exist)(ace_cpuP cpu);

} ace_cpu_agent;

#ifdef __cplusplus
}  // extern "C"
#endif
