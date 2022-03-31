/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License Agreement
 * that you accepted before downloading this file.
 *
 * This header forms part of the Software but may be included and used unaltered
 * in derivative works.
 *
 * For more information, please visit www.OVPworld.org or www.imperas.com
 */

#pragma once

#include "hostapi/simAddrTypes.h"
#include "vmi/vmiTypes.h"
#include "vmi/vmiTyperefs.h"


//
// Type of function called by the simulator to read a register
// Return code indicates whether the read succeeded.
//
// The endianness of the returned data should be that of the host.
//
#define VMI_REG_READ_FN(_NAME) Bool _NAME( \
    vmiProcessorP processor,    \
    vmiRegInfoCP  reg,          \
    void         *buffer        \
)
typedef VMI_REG_READ_FN((*vmiRegReadFn));

//
// Type of function called by the simulator to write a register
// Return code indicates whether the write succeeded
//
// The endianness of the supplied data should be that of the host.
//
#define VMI_REG_WRITE_FN(_NAME) Bool _NAME( \
    vmiProcessorP processor,    \
    vmiRegInfoCP  reg,          \
    const void   *buffer        \
)
typedef VMI_REG_WRITE_FN((*vmiRegWriteFn));

//
// Function type used to emit instruction trace for the passed simulated
// address
//
#define VMI_TRACE_FN(_NAME) Bool _NAME( \
    vmiProcessorP processor,        \
    Addr          simAddress,       \
    Bool          isException,      \
    Bool          isFirst,          \
    Bool          isRegisterIntro   \
)
typedef VMI_TRACE_FN((*vmiTraceFn));

//
// Function type used to return custom supplemental information in text form
// about a memory access. The access was initiated at address 'VA' in domain
// 'VAdomain' and terminated at address 'PA' in domain 'PAdomain' and was of
// size 'bytes'. The type of access is given by 'priv'. 'isMap' indicates
// whether the access was an implicit one for the purpose of updating memory
// map structures (for example, a memory read as part of a page table walk).
//
#define VMI_TRACE_MEM_ATTRS_FN(_NAME) const char *_NAME( \
    vmiProcessorP processor,        \
    memDomainP    VAdomain,         \
    Addr          VA,               \
    memDomainP    PAdomain,         \
    Addr          PA,               \
    Uns32         bytes,            \
    memPriv       priv,             \
    Bool          isMap             \
)
typedef VMI_TRACE_MEM_ATTRS_FN((*vmiTraceMemAttrsFn));

//
// Function type used to dump processor register state
//
#define VMI_DEBUG_FN(_NAME) void _NAME( \
    vmiProcessorP processor,    \
    Bool          isTrace,      \
    Bool          isException,  \
    Bool          isFirst       \
)
typedef VMI_DEBUG_FN((*vmiDebugFn));

//
// Type of function called by the simulator to obtain information about the
// register groups in the simulated processor
//
#define VMI_REG_GROUP_FN(_NAME) vmiRegGroupCP _NAME( \
    vmiProcessorP processor,    \
    vmiRegGroupCP prev          \
)
typedef VMI_REG_GROUP_FN((*vmiRegGroupFn));

//
// Type of function called by the simulator to obtain information about the
// supplemental register groups for an intercept library attached to a processor
//
#define VMIOS_REG_GROUP_FN(_NAME) vmiRegGroupCP _NAME( \
    vmiProcessorP processor,    \
    vmiosObjectP  object,       \
    vmiRegGroupCP prev          \
)
typedef VMIOS_REG_GROUP_FN((*vmiosRegGroupFn));

//
// Enumeration of register type for vmiRegInfoFn
//
typedef enum vmiRegInfoTypeE {
    VMIRIT_NORMAL,      // normal register request (not RSP)
    VMIRIT_GPACKET,     // RSP 'g' packet register request
    VMIRIT_PPACKET,     // RSP 'p' packet register request
    VMIRIT_LAST         // Keep this one last and do not use it
} vmiRegInfoType;

//
// Type of function called by the simulator to obtain information about the
// registers in the simulated processor
//
#define VMI_REG_INFO_FN(_NAME) vmiRegInfoCP _NAME( \
    vmiProcessorP  processor,   \
    vmiRegInfoCP   prev,        \
    vmiRegInfoType gdbFrame     \
)
typedef VMI_REG_INFO_FN((*vmiRegInfoFn));

//
// Given a register alias name, return the name which should be used to look up
// that register by name in the list of vmiRegInfoCP objects for the processor
//
#define VMI_REG_ALIAS_FN(_NAME) const char *_NAME( \
    vmiProcessorP processor,    \
    const char   *alias         \
)
typedef VMI_REG_ALIAS_FN((*vmiRegAliasFn));

//
// Type of function called by the simulator to obtain information about the
// supplemental registers for an intercept library attached to a processor
//
#define VMIOS_REG_INFO_FN(_NAME) vmiRegInfoCP _NAME( \
    vmiProcessorP  processor,   \
    vmiosObjectP   object,      \
    vmiRegInfoCP   prev,        \
    vmiRegInfoType type         \
)
typedef VMIOS_REG_INFO_FN((*vmiosRegInfoFn));

//
// Type of function called by the simulator to determine vmiReg-to-vmiRegInfoCP
// correspondence for processor registers when this cannot be derived implicitly
// from raw register definitions. Each register correspondence should be
// described by a call to vmirtRegImplRaw within the scope of this callback
//
#define VMI_REG_IMPL_FN(_NAME) void _NAME( \
    vmiProcessorP processor     \
)
typedef VMI_REG_IMPL_FN((*vmiRegImplFn));

//
// Type of function called by the simulator to determine vmiReg-to-vmiRegInfoCP
// correspondence when this cannot be derived implicitly from raw register
// definitions. Each register correspondence should be described by a call to
// vmirtRegImplRaw within the scope of this callback
//
#define VMIOS_REG_IMPL_FN(_NAME) void _NAME( \
    vmiProcessorP processor,    \
    vmiosObjectP  object        \
)
typedef VMIOS_REG_IMPL_FN((*vmiosRegImplFn));

//
// Type of function called by the simulator to obtain information about the
// exceptions in the simulated processor
//
#define VMI_EXCEPTION_INFO_FN(_NAME) vmiExceptionInfoCP _NAME( \
    vmiProcessorP      processor,   \
    vmiExceptionInfoCP prev         \
)
typedef VMI_EXCEPTION_INFO_FN((*vmiExceptionInfoFn));

//
// Type of function called by the simulator to obtain information about the
// current processor exception
//
#define VMI_GET_EXCEPTION_FN(_NAME) vmiExceptionInfoCP _NAME( \
    vmiProcessorP processor \
)
typedef VMI_GET_EXCEPTION_FN((*vmiGetExceptionFn));

//
// Type of function called by the simulator to obtain information about the
// modes in the simulated processor
//
#define VMI_MODE_INFO_FN(_NAME) vmiModeInfoCP _NAME( \
    vmiProcessorP processor,    \
    vmiModeInfoCP prev          \
)
typedef VMI_MODE_INFO_FN((*vmiModeInfoFn));

//
// Type of function called by the simulator to obtain information about the
// current processor mode
//
#define VMI_GET_MODE_FN(_NAME) vmiModeInfoCP _NAME(vmiProcessorP processor)
typedef VMI_GET_MODE_FN((*vmiGetModeFn));

//
// This type is used to indicate the group to which a register belongs (for
// organizational purposes in a debugger)
//
typedef struct vmiRegGroupS {
    const char *name;           // register group name
} vmiRegGroup;

//
// Enumeration of register usage
//
typedef enum {
    vmi_REG_NONE = 0,           // no special usage for this register
    vmi_REG_PC   = 1,           // register is the program counter
    vmi_REG_SP   = 2,           // register is the stack pointer
    vmi_REG_FP   = 3,           // register is the frame pointer
    vmi_REG_LR   = 4            // register is the link register
} vmiRegUsage;

//
// Enumeration of register access
//
typedef enum {
    vmi_RA_NONE = 0x0,          // no register access
    vmi_RA_R    = 0x1,          // register is read-only
    vmi_RA_W    = 0x2,          // register is write-only
    vmi_RA_RW   = 0x3           // register is read/write
} vmiRegAccess;

//
// Structure used to pass information about the registers in a simulated
// processor to the simulator
//
typedef struct vmiRegInfoS {
    const char   *name;                 // register identification name
    const char   *description;          // description string
    vmiRegGroupCP group;                // group for this register
    Uns32         gdbIndex;             // gdb ordinal index number
    vmiRegUsage   usage           :  3; // any special usage for this register
    vmiRegAccess  access          :  2; // allowed access
    Bool          noSaveRestore   :  1; // does not participate in save/restore
    Bool          noTraceChange   :  1; // does not participate in tracing
    Bool          instrAttrIgnore :  1; // ignore for instruction attributes
    Bool          isAlias         :  1; // register an alias of another?
    Bool          extension       :  1; // defined in an extension library?
    Uns32         unused          : 22; // unused fields
    Uns32         bits;                 // size of register in bits
    vmiRegReadFn  readCB;               // read callback function
    vmiRegWriteFn writeCB;              // write callback function
    vmiReg        raw;                  // raw register value (if no callback)
    void         *userData;             // model-specific data pointer
} vmiRegInfo;

//
// Special readCB and writeCB values specifying that read and write of raw
// register values is allowed (i.e. without callback), requiring that either:
// 1. the 'raw' field is set with the appropriate register; or:
// 2. the userData argument is set to the register offset in the processor
//    structure (deprecated backwards-compatible mode).
// With the introduction of the 'raw' field in the vmiRegInfo structure, these
// special values are not required (specify the 'raw' vmiReg and omit the the
// read/write callback to achieve the same effect).
//
#define VMI_REG_RAW_READ_CB  ((vmiRegReadFn)(-1))
#define VMI_REG_RAW_WRITE_CB ((vmiRegWriteFn)(-1))

//
// Define plain read/write register in processor
//
#define VMI_REG_RAW_RW(_TP, _F) { \
    name   : #_F,                       \
    access : vmi_RA_RW,                 \
    bits   : sizeof(((_TP)0)->_F)*8,    \
    raw    : VMI_CPU_REG(_TP, _F)       \
}

//
// Define plain read-only register in processor
//
#define VMI_REG_RAW_R(_TP, _F) { \
    name   : #_F,                       \
    access : vmi_RA_R,                  \
    bits   : sizeof(((_TP)0)->_F)*8,    \
    raw    : VMI_CPU_REG(_TP, _F)       \
}

//
// Structure used to pass information about an exception to the simulator
//
typedef struct vmiExceptionInfoS {
    const char *name;           // exception name
    Uns32       code;           // model-specific exception code
    const char *description;    // description string
} vmiExceptionInfo;

//
// Structure used to pass information about a processor mode to the simulator
//
typedef struct vmiModeInfoS {
    const char *name;           // mode name
    Uns32       code;           // model-specific mode code
    const char *description;    // description string
} vmiModeInfo;

//
// Function type used to find a processor's type
//
#define VMI_PROC_DESC_FN(_NAME) const char * _NAME( \
    vmiProcessorP processor \
)

typedef VMI_PROC_DESC_FN((*vmiProcDescFn));

