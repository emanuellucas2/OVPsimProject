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



////////////////////////////////////////////////////////////////////////////////
// This API is deprecated. Please refer to the documentation.
////////////////////////////////////////////////////////////////////////////////

#ifndef ICMCPUMANAGER_H
#define ICMCPUMANAGER_H

#define ICM_VERSION "2.5.0"


////////////////////////////////////////////////////////////////////////////////
// Opaque Structure References
////////////////////////////////////////////////////////////////////////////////

/// @struct icmProcessorS
/// Opaque type pointer to processor object
typedef struct icmProcessorS            *icmProcessorP          , **icmProcessorPP;
/// @struct icmAttrListS
/// Opaque type pointer to processor user attributes object
typedef struct icmAttrListS             *icmAttrListP           , **icmAttrListPP;
/// @struct icmBusS
/// Opaque type pointer to bus object
typedef struct icmBusS                  *icmBusP                , **icmBusPP;
/// @struct icmNetS
/// Opaque type pointer to net object
typedef struct icmNetS                  *icmNetP                , **icmNetPP;
/// @struct icmNetPortS
/// Opaque type pointer to netPort object
typedef struct icmNetPortS              *icmNetPortP            , **icmNetPortPP;
/// @struct icmConnS
/// Opaque type pointer to connection object (e.g. a fifo)
typedef struct icmConnS                 *icmConnP               , **icmConnPP;
/// @struct icmMemoryS
/// Opaque type pointer to memory object
typedef struct icmMemoryS               *icmMemoryP             , **icmMemoryPP;
/// @struct icmPacketnetS
/// Opaque type pointer to packetnet object
typedef struct icmPacketnetS            *icmPacketnetP          , **icmPacketnetPP;
/// @struct icmPacketnetPortS
/// Opaque type pointer to packetnet port
typedef struct icmPacketnetPortS        *icmPacketnetPortP      , **icmPacketnetPortPP;
/// @struct icmPseS
/// Opaque type pointer to PSE object
typedef struct icmPseS                  *icmPseP                , **icmPsePP;
/// @struct icmRedirectS
/// Opaque type pointer to redirection object
typedef struct icmRedirectS             *icmRedirectP           , **icmRedirectPP;
/// @struct icmRegGroupS
/// Opaque type pointer to register group descriptor
typedef struct icmRegGroupS             *icmRegGroupP           , **icmRegGroupPP;
/// @struct icmRegInfoS
/// Opaque type pointer to register descriptor
typedef struct icmRegInfoS              *icmRegInfoP            , **icmRegInfoPP;
/// @struct icmMMRegInfoS
/// Opaque type pointer to memory mapped register descriptor
typedef struct icmMMRegInfoS            *icmMMRegInfoP          , **icmMMRegInfoPP;
/// @struct icmMmcS
/// Opaque type pointer to MMC object
typedef struct icmMmcS                  *icmMmcP                , **icmMmcPP;
/// @struct icmImagefileS
/// Opaque type pointer to loaded image (or program) file
typedef struct icmImagefileS            *icmImagefileP          , **icmImagefilePP;
/// @struct icmBusBridgeS
/// Opaque type pointer to bus bridge
typedef struct icmBusBridgeS            *icmBusBridgeP          , **icmBusBridgePP;
/// @struct icmWatchPointS
/// Opaque type pointer to watchpoint object
typedef struct icmWatchPointS           *icmWatchPointP         , **icmWatchPointPP;
/// @struct icmInterceptS
/// Opaque type pointer to intercept object
typedef struct icmInterceptS            *icmInterceptP          , **icmInterceptPP;
/// @struct icmTriggerEventS
/// Opaque type pointer to trigger event
typedef struct icmTriggerEventS         *icmTriggerEventP       , **icmTriggerEventPP;
/// @struct icmExceptionInfoS
/// Opaque type pointer to exception descriptor
typedef struct icmExceptionInfoS        *icmExceptionInfoP      , **icmExceptionInfoPP;
/// @struct icmNetPortInfoS
/// Opaque type pointer to net port descriptor
typedef struct icmNetPortInfoS          *icmNetPortInfoP        , **icmNetPortInfoPP;
/// @struct icmFifoPortInfoS
/// Opaque type pointer to FIFO port descriptor
typedef struct icmFifoPortInfoS         *icmFifoPortInfoP       , **icmFifoPortInfoPP;
/// @struct icmDocNodeS
/// Opaque type pointer to documentation node
typedef struct icmDocNodeS              *icmDocNodeP            , **icmDocNodePP;
/// @struct icmCLPS
/// Opaque type pointer to command line parser
typedef struct icmCLPS                  *icmCLPP                , **icmCLPPP;
/// @struct icmParamInfoS
/// Opaque type pointer to model parameter
typedef struct icmParamInfoS            *icmParamInfoP          , **icmParamInfoPP;
/// @struct icmParamEnumS
/// Opaque type pointer to parameter enum value
typedef struct icmParamEnumS            *icmParamEnumP          , **icmParamEnumPP;
/// @struct icmBusPortInfoS
/// Opaque type pointer to bus port descriptor
typedef struct icmBusPortInfoS          *icmBusPortInfoP        , **icmBusPortInfoPP;
/// @struct icmModeInfoS
/// Opaque type pointer to processor mode descriptor
typedef struct icmModeInfoS             *icmModeInfoP           , **icmModeInfoPP;


////////////////////////////////////////////////////////////////////////////////
// Public structure forward references
////////////////////////////////////////////////////////////////////////////////

typedef struct icmVlnvS                  *icmVlnvP               , **icmVlnvPP;
typedef struct icmRepeatedArgS           *icmRepeatedArgP        , **icmRepeatedArgPP;
typedef struct icmDebugNotifierS         *icmDebugNotifierP      , **icmDebugNotifierPP;

#include <stdarg.h>
#include "hostapi/impTypes.h"
#include "ord/ordObjAttrs.h"


////////////////////////////////////////////////////////////////////////////////
// Types
////////////////////////////////////////////////////////////////////////////////

/// Simulator time (in seconds)
typedef long double  icmTime;


////////////////////////////////////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////////////////////////////////////

/// Supplementary information (for time advance callback)
typedef enum icmAdvanceTimeInfoE {
    ICM_TA_NONE = 0x00, ///< No supplementary information
    ICM_TA_SIM  = 0x01, ///< Simulator stop time reached
    ICM_TA_DBG  = 0x02, ///< Debug stop time reached
    ICM_TA_END  = 0x04  ///< End of simulation
} icmAdvanceTimeInfo;

/// Bus port type
typedef enum icmBusPortTypeE {
    ICM_BPT_UNSET       , ///< Port type is not set.
    ICM_BPT_MASTER      , ///< Bus master port.
    ICM_BPT_SLAVE       , ///< Bus slave port.
    ICM_BPT_MASTERSLAVE   ///< Bus master and slave port.
} icmBusPortType;

/// Bus domain type
typedef enum icmDomainTypeE {
    ICM_DOM_CODE  , ///< Bus domain used to fetch instructions.
    ICM_DOM_DATA  , ///< Bus domain used to read/write data.
    ICM_DOM_OTHER   ///< Bus domain of other uses.
} icmDomainType;

/// Command line parser argument type. See CLPA_*_FN definitions.
typedef enum icmCLPArgTypeE {
    ICM_AT_NONE        , ///< Do not use
    ICM_AT_BOOLVAL     , ///< Argument sets variable of type Boolean
    ICM_AT_INT32VAL    , ///< Argument sets variable of type Int32
    ICM_AT_INT64VAL    , ///< Argument sets variable of type Int64
    ICM_AT_UNS32VAL    , ///< Argument sets variable of type Uns32
    ICM_AT_UNS64VAL    , ///< Argument sets variable of type Uns64
    ICM_AT_DOUBLEVAL   , ///< Argument sets variable of type Double
    ICM_AT_STRINGVAL   , ///< Argument sets variable of type String
    ICM_AT_STRINGLIST  , ///< One list element for each use of the argument
    ICM_AT_STRINGSLAST , ///< This flag must be last. Builds list of all args
                         ///  following
    ICM_AT_PAIRLIST    , ///< One name=value pair for each use of the argument
    ICM_AT_GLOB_STRING , ///< One list element for each use of the argument.
                         ///  Strings are file-glob expanded
    ICM_AT_FC_BOOLEAN  , ///< Function called each time flag is specified
    ICM_AT_FC_INT32    , ///< Function called each time Int32 argument is
                         ///  specified
    ICM_AT_FC_INT64    , ///< Function called each time Int64 argument is
                         ///  specified
    ICM_AT_FC_UNS32    , ///< Function called each time Uns32 argument is
                         ///  specified
    ICM_AT_FC_UNS64    , ///< Function called each time Uns64 argument is
                         ///  specified
    ICM_AT_FC_DOUBLE   , ///< Function called each time double argument is
                         ///  specified
    ICM_AT_FC_STRING   , ///< Function called each time string argument is
                         ///  specified
    ICM_AT_FC_PAIR     , ///< Function called each time name=value is specified
    ICM_AT_FC_ARGV     , ///< Function called with a list of arguments
    ICM_AT_FC_ARGVLAST , ///< This flag must be last. Function called with a
                         ///  list of all following arguments.
    ICM_AT_FC_ARGVPAIR   ///< Function called with each list of name=value
                         ///  arguments
} icmCLPArgType;

/// Command line parser argument class. Use to select what standard arguments to
/// a parser
typedef enum icmCLPArgClassE {
    ICM_AC_NONE  = 0x00, ///< No standard arguments
    ICM_AC_BASIC = 0x01, ///< Basic arguments
    ICM_AC_EXT1  = 0x02, ///< Basic demo arguments
    ICM_AC_EXT2  = 0x04, ///< Extended demo arguments
    ICM_AC_SIM   = 0x08, ///< Simulator arguments
    ICM_AC_LIB   = 0x10, ///< Library arguments
    ICM_AC_ENG   = 0x20, ///< (do not use)
    ICM_AC_ALL   = 0x18  ///< Simulator and Library
} icmCLPArgClass;

/// Direction
typedef enum icmDirectionE {
    ICM_ANY    = 0x0, ///< For internal use - DO NOT USE
    ICM_INPUT  = 0x1, ///< Slave bus port, input net port or input FIFO port
    ICM_OUTPUT = 0x2, ///< Master bus port, output net port or output FIFO port
    ICM_INOUT  = 0x3  ///< input net port (not FIFO or bus)
} icmDirection;

/// Imagefile endian-ness
typedef enum icmEndianE {
    ICM_ENDIAN_NONE   = 0x0, ///< No endian specified
    ICM_ENDIAN_LITTLE = 0x1, ///< Definitely little
    ICM_ENDIAN_BIG    = 0x2, ///< Definitely big
    ICM_ENDIAN_EITHER = 0x3  ///< Could be either (not used in this release)
} icmEndian;

/// FIFO port type
typedef enum icmFifoPortTypeE {
    ICM_FPT_NODIR  , ///< FIFO Port direction is unset
    ICM_FPT_INPUT  , ///< FIFO Port used for input
    ICM_FPT_OUTPUT   ///< FIFO Port used for output.
} icmFifoPortType;

/// How data is presented in the host buffer
typedef enum icmHostEndianE {
    ICM_HOSTENDIAN_HOST   = 0x0, ///< Buffer is same endian as host (LE on X86)
    ICM_HOSTENDIAN_TARGET = 0x1, ///< Buffer is same endian as target (ie, not
                                 ///  converted)
    ICM_HOSTENDIAN_BIG    = 0x2, ///< Buffer is big endian
    ICM_HOSTENDIAN_LITTLE = 0x3  ///< Buffer is little endian
} icmHostEndian;

/// Use these values in a bit mask to specify simulation attributes to
/// icmInitPlatform()
typedef enum icmInitAttrsE {
    ICM_INIT_DEFAULT              = 0        , ///< Default behavior
    ICM_ENABLE_IMPERAS_INTERCEPTS = (1 <<  0), ///< Enable Imperas intercepts
    ICM_STOP_ON_CTRLC             = (1 <<  1), ///< Stop simulation when Ctrl-C
    ICM_VERBOSE                   = (1 <<  2), ///< Enable verbose reporting
    ICM_WALLCLOCK                 = (1 <<  3), ///< Sleep if inactive
    ICM_VERBOSE_DICT              = (1 <<  4), ///< Enable dictionary statistics
    ICM_DISASSEMBLE_LABELS        = (1 <<  5), ///< Deprecated (now always on)
    ICM_PRINT_USER_ATTRIBUTES     = (1 <<  6), ///< Print user attributes, set or not
    ICM_TRACE_SHARED_DATA         = (1 <<  7), ///< Trace activity of
                                               ///  vmirtWriteListeners
    ICM_MPD_EGUI                  = (1 <<  8), ///< Pop up MPD in EGUI.
    ICM_PRINT_COMMANDS            = (1 <<  9), ///< Print available plugin commands
    ICM_SUPPRESS_BANNER           = (1 << 10), ///< No banner at start-up - only
                                               ///  available in CpuManager
    ICM_PARALLEL_PERIPHERALS      = (1 << 11), ///< Enable parallel peripheral
                                               ///  simulation using any number of
                                               ///  concurrent host threads
    ICM_NO_RSP_WAIT               = (1 << 12), ///< Do not wait for RSP connection -
                                               ///  only available in CpuManager.
    ICM_GDB_CONSOLE               = (1 << 13), ///< Pop up gdb in console window.
    ICM_GDB_EGUI                  = (1 << 14), ///< Pop up gdb in EGUI.
    ICM_GDB_GUI                   = (1 << 15), ///< Pop up gdb in GUI.
    ICM_MPD_CONSOLE               = (1 << 16), ///< Pop up MPD in console window.
    ICM_MPD_GUI                   = (1 << 17), ///< Pop up MPD in GUI.
    ICM_NO_OPTIMIZE               = (1 << 18), ///< Turn off aggressive optimization.
    ICM_PRINT_BUSES               = (1 << 19), ///< Print a summary of bus connections.
    ICM_DEBUG_CONSTRUCTORS        = (1 << 20), ///< Stop for debug before PSE
                                               ///  constructors have run.
    ICM_PARALLEL                  = (1 << 21), ///< Run simulator in limited parallel
                                               ///  mode.
    ICM_PARALLEL_MAX              = (1 << 22), ///< Run simulator in maximum parallel
                                               ///  mode.
    ICM_MEM_STATS                 = (1 << 23), ///< Show memory statistics.
    ICM_YIELD_ON_TIMER_RESTART    = (1 << 24), ///< Simulator will return to called
                                               ///  when timer restarts
    ICM_LEGACY_SCHEDULING         = (1 << 25), ///< Use legacy scheduling algorithm
                                               ///  (PSE events before processors in
                                               ///  each quantum)
    ICM_DEFER_HALTED_PROCESSORS   = (1 << 26), ///< Update halted processors only in a
                                               ///  quantum delta cycle (so all
                                               ///  non-halted processors execute
                                               ///  first)
    ICM_RESERVED                  = (1 << 27)  ///< Reserved for internal use.
} icmInitAttrs;

/// Attributes passed to object file loader
typedef enum icmLoaderAttrsE {
    ICM_LOAD_DEFAULT     = 0x00, ///< Default options
    ICM_LOAD_PHYSICAL    = 0x01, ///< Use physical rather than virtual addresses
    ICM_LOAD_VERBOSE     = 0x02, ///< Report each section loaded
    ICM_NO_ZERO_BSS      = 0x04, ///< Do not zero the BSS segment
    ICM_SET_START        = 0x08, ///< Set processor start address to entry
                                 ///  address
    ICM_LOAD_SYMBOL_ONLY = 0x10, ///< Read the symbols but do not modify the
                                 ///  memory
    ICM_ELF_USE_VMA      = 0x20, ///< Load ELF files using VMA addresses instead
                                 ///  of LMA
    ICM_SIGN_EXTEND_ADDR = 0x40  ///< Sign-extend addresses from 32b to 64b
} icmLoaderAttrs;

/// Net port type
typedef enum icmNetPortTypeE {
    ICM_NPT_INPUT  , ///< Pin used for input
    ICM_NPT_OUTPUT , ///< Pin used for output.
    ICM_NPT_INOUT    ///< Pin used for input and output.
} icmNetPortType;

/// Use these values in a bitmask to specify required processor attributes to
/// icmNewProcessor()
typedef enum icmNewProcAttrsE {
    ICM_ATTR_DEFAULT            = 0x00000000, ///< Default behavior
    ICM_ATTR_TRACE              = 0x00000001, ///< Enable instruction trace
    ICM_ATTR_TRACE_ICOUNT       = 0x00000002, ///< Print count with trace
    ICM_ATTR_TRACE_REGS_BEFORE  = 0x00000004, ///< Dump registers before trace
    ICM_ATTR_TRACE_BUFFER       = 0x00000008, ///< Enable 256-entry trace buffer
    ICM_ATTR_TRACE_MODE         = 0x00000010, ///< Print processor mode with trace
    ICM_ATTR_SIMEX              = 0x00000020, ///< Simulate exceptions
    ICM_ATTR_FETCH_VALIDATE     = 0x00000100, ///< Fetch address validation
    ICM_ATTR_TRACE_REGS_AFTER   = 0x00000200, ///< Dump registers after trace
    ICM_ATTR_LOAD_PHYSICAL      = 0x00000400, ///< Use physical addresses
    ICM_ATTR_NOTRACE_ANNUL      = 0x00000800, ///< Don't trace annulled instructions
    ICM_ATTR_TRACE_CHANGE       = 0x00001000, ///< Dump changed registers
    ICM_ATTR_RESERVED           = 0x00002000, ///< Reserved for internal use
    ICM_ATTR_DEBUG_BASIC        = 0x00004000, ///< Do not use GDB with this processor
    ICM_ATTR_DEFAULT_SEMIHOST   = 0x00008000, ///< Install the default semihost
                                              ///  library for this processor
    ICM_ATTR_IMPERAS_INTERCEPTS = 0x00010000, ///< Enable Imperas intercepts
    ICM_ATTR_SYSTEMC            = 0x80000000, ///< Reserved for internal use
    ICM_ATTR_DEBUG              = 0x00000000, ///< (deprecated)
    ICM_ATTR_RELAXED_SCHED      = 0x00000000, ///< (deprecated)
    ICM_ATTR_APPROX_TIMER       = 0x00000000  ///< (deprecated)
} icmNewProcAttrs;

/// Parameter type
typedef enum icmParamTypeE {
    ICM_PT_BOOL   , ///< Boolean parameter, can be 1,0,t,f,y,n, etc.
    ICM_PT_INT32  , ///< 32bit signed integer parameter.
    ICM_PT_INT64  , ///< 64bit signed integer parameter.
    ICM_PT_UNS32  , ///< 32bit unsigned integer parameter.
    ICM_PT_UNS64  , ///< 64bit unsigned integer parameter.
    ICM_PT_DOUBLE , ///< Floating point parameter
    ICM_PT_STRING , ///< String parameter
    ICM_PT_ENUM   , ///< Enumerated type parameter (one of a set of valid
                    ///  strings).
    ICM_PT_ENDIAN , ///< Special enumerated type parameter (big or little).
    ICM_PT_PTR      ///< Pointer parameter.
} icmParamType;

/// Memory access privilege
typedef enum icmPrivE {
    ICM_PRIV_NONE  = 0x0, ///< No access permitted
    ICM_PRIV_R     = 0x1, ///< Read permitted
    ICM_PRIV_W     = 0x2, ///< Write permitted
    ICM_PRIV_RW    = 0x3, ///< Read and write permitted
    ICM_PRIV_X     = 0x4, ///< Execute permitted
    ICM_PRIV_RX    = 0x5, ///< Read and execute permitted
    ICM_PRIV_WX    = 0x6, ///< Write and execute permitted
    ICM_PRIV_RWX   = 0x7, ///< Read, write and execute permitted
    ICM_PRIV_ALIGN = 0x8  ///< Force accesses to be aligned
} icmPriv;

/// Platform Purpose
typedef enum icmPurposeE {
    ICM_BAREMETAL , ///< Processor and memory
    ICM_FIX       , ///< A fixed platform
    ICM_EPK       , ///< Extensible Platform Kit
    ICM_OEM         ///< For use only by specific OEM. Not for general release
} icmPurpose;

/// CPU Register classification
typedef enum icmRegUsageE {
    ICM_REG_NONE = 0x0, ///< No special usage for this register (GP)
    ICM_REG_PC   = 0x1, ///< Register is the program counter
    ICM_REG_SP   = 0x2, ///< Register is the stack pointer
    ICM_REG_FP   = 0x3, ///< Register is the frame pointer
    ICM_REG_LR   = 0x4  ///< Register is the link register
} icmRegUsage;

/// CPU Register read/write accessibility
typedef enum icmRegAccessE {
    ICM_RA_NONE = 0x0, ///< Register not accessible
    ICM_RA_R    = 0x1, ///< Register is read-only
    ICM_RA_W    = 0x2, ///< Register is write-only
    ICM_RA_RW   = 0x3  ///< Register is read/write
} icmRegAccess;

/// Model release status
typedef enum icmReleaseStatusE {
    ICM_UNSET      , ///< Not specified
    ICM_INTERNAL   , ///< For internal use only
    ICM_RESTRICTED , ///< Restricted release
    ICM_IMPERAS    , ///< Imperas only
    ICM_OVP          ///< Freely available
} icmReleaseStatus;

/// Return status from save or restore
typedef enum icmSaveRestoreStatusE {
    ICM_SAVE_OK    , ///< Successful save or restore
    ICM_SAVE_ERROR   ///< Error during save or restore
} icmSaveRestoreStatus;

/// Stop reason codes on return from icmSimulate
typedef enum icmStopReasonE {
    ICM_SR_SCHED      = 0x00, ///< Scheduler expired
    ICM_SR_YIELD      = 0x01, ///< Yield encountered
    ICM_SR_HALT       = 0x02, ///< CPU is halted
    ICM_SR_EXIT       = 0x03, ///< CPU has exited
    ICM_SR_FINISH     = 0x04, ///< Simulation finish
    ICM_SR_RD_PRIV    = 0x05, ///< Read privilege exception
    ICM_SR_WR_PRIV    = 0x06, ///< Write privilege exception
    ICM_SR_RD_ALIGN   = 0x07, ///< Read align exception
    ICM_SR_WR_ALIGN   = 0x08, ///< Write align exception
    ICM_SR_FE_PRIV    = 0x09, ///< Fetch privilege exception
    ICM_SR_ARITH      = 0x0a, ///< Arithmetic exception
    ICM_SR_INTERRUPT  = 0x0b, ///< Interrupt simulation
    ICM_SR_FREEZE     = 0x0c, ///< Frozen (by icmFreeze)
    ICM_SR_WATCHPOINT = 0x0d, ///< Memory watchpoint is pending
    ICM_SR_BP_ICOUNT  = 0x0e, ///< Instruction count breakpoint is pending
    ICM_SR_BP_ADDRESS = 0x0f, ///< Address breakpoint is pending
    ICM_SR_RD_ABORT   = 0x10, ///< Read abort exception
    ICM_SR_WR_ABORT   = 0x11, ///< Write abort exception
    ICM_SR_FE_ABORT   = 0x12, ///< Fetch abort exception
    ICM_SR_INVALID    = 0x13  ///< (invalid entry)
} icmStopReason;

/// Visibility of platform in debugger, introspection etc
typedef enum icmVisibilityE {
    ICM_VISIBLE   , ///< visible in all tools
    ICM_INVISIBLE   ///< invisible in all tools
} icmVisibility;

/// Watchpoint type
typedef enum icmWatchpointTypeE {
    ICMWP_MEM_READ    , ///< Memory read watchpoint
    ICMWP_MEM_WRITE   , ///< Memory write watchpoint
    ICMWP_MEM_ACCESS  , ///< Memory access watchpoint
    ICMWP_REGISTER    , ///< Register watchpoint
    ICMWP_MODE        , ///< Mode change watchpoint
    ICMWP_EXCEPTION     ///< Exception watchpoint
} icmWatchpointType;


////////////////////////////////////////////////////////////////////////////////
// Callbacks
////////////////////////////////////////////////////////////////////////////////

/// Prototype of function called when a flag is parsed

#define CLPA_BOOL_FN(_name) \
void _name ( \
    Uns32 userData)

/// This is a pointer to a function of the type defined by CLPA_BOOL_FN

typedef CLPA_BOOL_FN((*icmArgBoolFn));

/// Type of function called when an Int32 argument is parsed

#define CLPA_INT32_FN(_name) \
void _name ( \
    Int32 value, \
    Uns32 userData)

/// This is a pointer to a function of the type defined by CLPA_INT32_FN

typedef CLPA_INT32_FN((*icmArgInt32Fn));

/// Type of function called when an Int64 argument is parsed

#define CLPA_INT64_FN(_name) \
void _name ( \
    Int64 value, \
    Uns32 userData)

/// This is a pointer to a function of the type defined by CLPA_INT64_FN

typedef CLPA_INT64_FN((*icmArgInt64Fn));

/// Type of function called when an Uns32 argument is parsed

#define CLPA_UNS32_FN(_name) \
void _name ( \
    Uns32 value, \
    Uns32 userData)

/// This is a pointer to a function of the type defined by CLPA_UNS32_FN

typedef CLPA_UNS32_FN((*icmArgUns32Fn));

/// Type of function called when an Uns64 argument is parsed

#define CLPA_UNS64_FN(_name) \
void _name ( \
    Uns64 value, \
    Uns32 userData)

/// This is a pointer to a function of the type defined by CLPA_UNS64_FN

typedef CLPA_UNS64_FN((*icmArgUns64Fn));

/// Type of function called when a double argument is parsed

#define CLPA_DOUBLE_FN(_name) \
void _name ( \
    double value, \
    Uns32  userData)

/// This is a pointer to a function of the type defined by CLPA_DOUBLE_FN

typedef CLPA_DOUBLE_FN((*icmArgDoubleFn));

/// Type of function called when a string argument is parsed

#define CLPA_STRING_FN(_name) \
void _name ( \
    const char * value, \
    Uns32        userData)

/// This is a pointer to a function of the type defined by CLPA_STRING_FN

typedef CLPA_STRING_FN((*icmArgStringFn));

/// Type of function called when a name=value argument is parsed

#define CLPA_PAIR_FN(_name) \
void _name ( \
    const char * name, \
    const char * value, \
    Uns32        userData)

/// This is a pointer to a function of the type defined by CLPA_PAIR_FN

typedef CLPA_PAIR_FN((*icmArgStringPairFn));

/// Type of function called when a repeated string is parsed

/// @par Parameters:
/// @par
/// @a argv values

#define CLPA_ARGV_FN(_name) \
void _name ( \
    Uns32         argc, \
    const char ** argv, \
    Uns32         userData)

/// This is a pointer to a function of the type defined by CLPA_ARGV_FN

typedef CLPA_ARGV_FN((*icmArgVFn));

/// Type of function called when a repeated name=value is parsed

/// @par Parameters:
/// @par
/// @a argn names
/// @par
/// @a argv values

#define CLPA_ARGV_PAIR_FN(_name) \
void _name ( \
    Uns32         argc, \
    const char ** argn, \
    const char ** argv, \
    Uns32         userData)

/// This is a pointer to a function of the type defined by CLPA_ARGV_PAIR_FN

typedef CLPA_ARGV_PAIR_FN((*icmArgVPairFn));

/// Memory read callback function

#define ICM_MEM_READ_FN(_name) \
void _name ( \
    icmProcessorP processor, \
    Addr          address, \
    Uns32         bytes, \
    void*         value, \
    void*         userData, \
    Addr          VA, \
    Bool          isFetch)

/// This is a pointer to a function of the type defined by ICM_MEM_READ_FN

typedef ICM_MEM_READ_FN((*icmMemReadFn));

/// Memory write callback function

#define ICM_MEM_WRITE_FN(_name) \
void _name ( \
    icmProcessorP processor, \
    Addr          address, \
    Uns32         bytes, \
    const void*   value, \
    void*         userData, \
    Addr          VA)

/// This is a pointer to a function of the type defined by ICM_MEM_WRITE_FN

typedef ICM_MEM_WRITE_FN((*icmMemWriteFn));

/// Memory read/write notification callback

#define ICM_MEM_WATCH_FN(_name) \
void _name ( \
    icmProcessorP processor, \
    Addr          address, \
    Uns32         bytes, \
    const void*   value, \
    void*         userData, \
    Addr          VA)

/// This is a pointer to a function of the type defined by ICM_MEM_WATCH_FN

typedef ICM_MEM_WATCH_FN((*icmMemWatchFn));

/// Callback used by icmIterAllUserAttributes

#define USER_ATTR_FN(_name) \
void _name ( \
    const char * owner, \
    const char * name, \
    const char * value, \
    Bool         set, \
    Bool         used, \
    Bool         numeric, \
    void*        userData)

/// This is a pointer to a function of the type defined by USER_ATTR_FN

typedef USER_ATTR_FN((*icmAttrFn));

/// Callback used for model parameters

#define ICM_PARAM_FN(_name) \
void _name ( \
    const char * owner, \
    const char * name, \
    void*        userData)

/// This is a pointer to a function of the type defined by ICM_PARAM_FN

typedef ICM_PARAM_FN((*icmParamFn));

/// Prototype of on-exit function

#define ICM_EXIT_FN(_name) \
void _name ( void)

/// This is a pointer to a function of the type defined by ICM_EXIT_FN

typedef ICM_EXIT_FN((*icmExitFn));

/// Callback for text output (icmMessage etc)

#define ICM_TEXT_OUTPUT_FN(_name) \
void _name ( \
    const char * text, \
    void*        userData)

/// This is a pointer to a function of the type defined by ICM_TEXT_OUTPUT_FN

typedef ICM_TEXT_OUTPUT_FN((*icmTextOutputFn));

/// Callback of callback for quitting the simulator

#define ICM_QUIT_FN(_name) \
void _name ( \
    Int32 status, \
    void* userData)

/// This is a pointer to a function of the type defined by ICM_QUIT_FN

typedef ICM_QUIT_FN((*icmQuitFn));

/// Iterator callback function for SMPs

#define ICM_SMP_ITERATOR_FN(_name) \
void _name ( \
    icmProcessorP processor, \
    void*         userData)

/// This is a pointer to a function of the type defined by ICM_SMP_ITERATOR_FN

typedef ICM_SMP_ITERATOR_FN((*icmSMPIteratorFn));

/// Callback function when processor stops

#define ICM_STOP_HANDLER_FN(_name) \
Bool _name ( \
    icmProcessorP processor, \
    icmStopReason stopReason, \
    void*         userData)

/// This is a pointer to a function of the type defined by ICM_STOP_HANDLER_FN

typedef ICM_STOP_HANDLER_FN((*icmStopHandlerFn));

/// Prototype of callback for each installed command

#define ICM_INSTALLED_COMMAND_FN(_name) \
void _name ( \
    const char * platform, \
    const char * model, \
    const char * plugin, \
    const char * command, \
    const char * shortHelp, \
    void*        user)

/// This is a pointer to a function of the type defined by
/// ICM_INSTALLED_COMMAND_FN

typedef ICM_INSTALLED_COMMAND_FN((*icmInstalledCommandFn));

/// Prototype of callback for vlnv files

#define ICM_VLNV_FOUND_CB(_name) \
void _name ( \
    const char * file, \
    void*        userData)

/// This is a pointer to a function of the type defined by ICM_VLNV_FOUND_CB

typedef ICM_VLNV_FOUND_CB((*icmFoundFileFn));

/// Prototype of callback used by icmAddNetCallback

#define NET_WRITE_FN(_name) \
void _name ( \
    void* userData, \
    Uns64 value)

/// This is a pointer to a function of the type defined by NET_WRITE_FN

typedef NET_WRITE_FN((*icmNetFn));

/// Prototype of callback used by icmTriggerAfter

#define TRIGGER_AFTER_FN(_name) \
void _name ( \
    icmTime currentTime, \
    void*   userData)

/// This is a pointer to a function of the type defined by TRIGGER_AFTER_FN

typedef TRIGGER_AFTER_FN((*icmTriggerFn));

/// Prototype of callback when a PSE maps a dynamic port.

#define ICM_PSE_PORT_MAP_FN(_name) \
void _name ( \
    void* userData, \
    Addr  loAddress, \
    Addr  hiAddress, \
    Bool  add)

/// This is a pointer to a function of the type defined by ICM_PSE_PORT_MAP_FN

typedef ICM_PSE_PORT_MAP_FN((*icmPsePortMapFn));

/// Callback to save simulation data.

#define ICM_SAVE_FN(_name) \
Bool _name ( \
    const void * buffer, \
    Uns32        bytes, \
    void*        userData)

/// This is a pointer to a function of the type defined by ICM_SAVE_FN

typedef ICM_SAVE_FN((*icmSaveFn));

/// Callback to restore simulation data.

#define ICM_RESTORE_FN(_name) \
Bool _name ( \
    void * buffer, \
    Uns32  bytes, \
    void*  userData)

/// This is a pointer to a function of the type defined by ICM_RESTORE_FN

typedef ICM_RESTORE_FN((*icmRestoreFn));

/// Callback when simulation is about to start.

#define ICM_START_SIM_FN(_name) \
void _name ( \
    void* userData)

/// This is a pointer to a function of the type defined by ICM_START_SIM_FN

typedef ICM_START_SIM_FN((*icmStartSimFn));

/// Callback when peripheral constructors have finished, when application
/// processors are about to start.

#define ICM_END_CONSTRUCTORS_FN(_name) \
void _name ( \
    void* userData)

/// This is a pointer to a function of the type defined by
/// ICM_END_CONSTRUCTORS_FN

typedef ICM_END_CONSTRUCTORS_FN((*icmEndConstructorsFn));

/// Callback when platform constructor has finished, before simulation.

#define ICM_END_PLT_CONSTRUCTOR_FN(_name) \
void _name ( \
    void* userData)

/// This is a pointer to a function of the type defined by
/// ICM_END_PLT_CONSTRUCTOR_FN

typedef ICM_END_PLT_CONSTRUCTOR_FN((*icmEndPltConstructorFn));

/// Callback when each processor slice (quantum) has finished. Should return
/// true if simulation is to continue, false if not.

/// @par Returns:
/// Return False if simulation must finish.
#define ICM_END_SCHED_FN(_name) \
Bool _name ( \
    icmProcessorP processor, \
    void*         userData)

/// This is a pointer to a function of the type defined by ICM_END_SCHED_FN

typedef ICM_END_SCHED_FN((*icmEndSchedFn));

/// Callback when time advances. Should return true if simulation is to
/// continue, false if not.

/// @par Returns:
/// Return False if simulation must finish.
#define ICM_TIME_ADVANCE_FN(_name) \
Bool _name ( \
    icmAdvanceTimeInfo info, \
    void*              userData)

/// This is a pointer to a function of the type defined by ICM_TIME_ADVANCE_FN

typedef ICM_TIME_ADVANCE_FN((*icmTimeAdvanceFn));

/// Callback when simulation is finishing.

#define ICM_FINISH_FN(_name) \
void _name ( \
    icmProcessorP processor, \
    void*         userData)

/// This is a pointer to a function of the type defined by ICM_FINISH_FN

typedef ICM_FINISH_FN((*icmFinishFn));

/// Callback when simulation is finishing.

/// @par Returns:
/// True if this function handled the value change.
#define ICM_MEM_NOTIFIER_FN(_name) \
Bool _name ( \
    icmProcessorP  processor, \
    icmWatchPointP watchpoint, \
    Addr           PA, \
    Addr           VA, \
    Uns32          bytes, \
    void*          userData, \
    void*          value)

/// This is a pointer to a function of the type defined by ICM_MEM_NOTIFIER_FN

typedef ICM_MEM_NOTIFIER_FN((*icmMemNotifierFn));

/// Register watchpoint notification callback.

/// @par Parameters:
/// @par
/// @a watchpoint Triggered watchpoint object
/// @par
/// @a processor Processor triggering the watchpoint
/// @par
/// @a userData User data pointer passed to installer

/// @par Returns:
/// True if this function handled the value change.
#define ICM_REG_NOTIFIER_FN(_name) \
Bool _name ( \
    icmWatchPointP watchpoint, \
    icmProcessorP  processor, \
    void*          userData)

/// This is a pointer to a function of the type defined by ICM_REG_NOTIFIER_FN

typedef ICM_REG_NOTIFIER_FN((*icmRegNotifierFn));

/// Notification when a packetnet is written.

/// @par Parameters:
/// @par
/// @a data Data passed from transmitter
/// @par
/// @a bytes Number of bytes sent
/// @par
/// @a userData User data pointer passed to installer

#define ICM_PACKETNET_NOTIFIER_FN(_name) \
void _name ( \
    void* data, \
    Uns32 bytes, \
    void* userData)

/// This is a pointer to a function of the type defined by
/// ICM_PACKETNET_NOTIFIER_FN

typedef ICM_PACKETNET_NOTIFIER_FN((*icmPacketnetNotifierFn));

/// Called for each loaded region

/// @par Parameters:
/// @par
/// @a name Optional region name
/// @par
/// @a address Base address
/// @par
/// @a bytes Number of bytes in region
/// @par
/// @a executable True if executable, rather than data
/// @par
/// @a userData User data from call

#define ICM_OBJECT_LIST_REGION_FN(_name) \
void _name ( \
    const char * name, \
    Addr         address, \
    Addr         bytes, \
    Bool         executable, \
    void*        userData)

/// This is a pointer to a function of the type defined by
/// ICM_OBJECT_LIST_REGION_FN

typedef ICM_OBJECT_LIST_REGION_FN((*icmObjectListRegionFn));



////////////////////////////////////////////////////////////////////////////////
// Public structures
////////////////////////////////////////////////////////////////////////////////

/// @struct icmVlnvS
/// VLNV specification.

typedef struct icmVlnvS {
    const char * vendor ; 
    const char * library; 
    const char * name   ; 
    const char * version; 
} icmVlnv;

/// @struct icmRepeatedArgS
/// Linked list of command line arguments.

typedef struct icmRepeatedArgS {
    struct icmRepeatedArgS * next  ; 
    const char *             string; 
    const char *             name  ; 
} icmRepeatedArg;

/// @struct icmDebugNotifierS
/// Debugger notification callbacks. Each can be NULL if not required

typedef struct icmDebugNotifierS {
    icmStartSimFn          start     ; 
    icmEndPltConstructorFn endPSECons; 
    icmEndPltConstructorFn endPltCons; 
    icmEndConstructorsFn   endCons   ; 
    icmEndSchedFn          sched     ; 
    icmEndSchedFn          schedPSE  ; 
    icmTimeAdvanceFn       advance   ; 
    icmFinishFn            finish    ; 
    void*                  userData  ; 
} icmDebugNotifier;



////////////////////////////////////////////////////////////////////////////////
// Macros
////////////////////////////////////////////////////////////////////////////////

/// Deprecated - use ICM_ATTR_TRACE_REGS_BEFORE or ICM_ATTR_TRACE_REGS_AFTER


#define ICM_ATTR_TRACE_REGS        ICM_ATTR_TRACE_REGS_AFTER
        

/// Initialize ICM package - call this before any other icm functions.


#define icmInit(simAttrs,protocol,dbgPort) \
     icmInitInternal(ICM_VERSION,simAttrs,protocol,dbgPort)
        

/// Legacy names


#define icmGetNextParamInfo    icmGetNextProcessorParamInfo
#define icmGetNextBusPortInfo  icmGetNextProcessorBusPortInfo
#define icmGetNextNetPortInfo  icmGetNextProcessorNetPortInfo
#define icmGetNextFifoPortInfo icmGetNextProcessorFifoPortInfo
        


////////////////////////////////////////////////////////////////////////////////
// ICM Functions
////////////////////////////////////////////////////////////////////////////////

/// This API is deprecated. Please refer to the documentation
/// When called in a memory read callback, indicates that the read has been
/// aborted.
/// @param processor The current processor.
/// @param address   The bad address.

void icmAbortRead (
    icmProcessorP processor,
    Addr          address
);

/// This API is deprecated. Please refer to the documentation
/// When called in a memory write callback, indicates that the write has been
/// aborted.
/// @param processor The current processor or null.
/// @param address   The bad address.

void icmAbortWrite (
    icmProcessorP processor,
    Addr          address
);

/// This API is deprecated. Please refer to the documentation
/// Add a Bool attribute to the given attributes list
/// @param attrs Attribute list
/// @param name  Name of new attribute (must be unique in this list)
/// @param value Boolean value.

void icmAddBoolAttr (
    icmAttrListP attrs,
    const char*  name,
    Bool         value
);

/// This API is deprecated. Please refer to the documentation
/// Install a callback on fetch accesses using the bus
/// @param bus      Bus object.
/// @param scope    If non-null, restrict sensitivity to this processor.
/// @param lowAddr  Lowest address of the region to be sensitized.
/// @param highAddr Highest address of the region to be sensitized.
/// @param writeCB  Function to be called.
/// @param userData Passed to the callback function.

void icmAddBusFetchCallback (
    icmBusP       bus,
    icmProcessorP scope,
    Addr          lowAddr,
    Addr          highAddr,
    icmMemWatchFn writeCB,
    void*         userData
);

/// This API is deprecated. Please refer to the documentation
/// Install a callback on read accesses using the bus
/// @param bus      Bus object.
/// @param scope    If non-null, restrict sensitivity to this processor.
/// @param lowAddr  Lowest address of the region to be sensitized.
/// @param highAddr Highest address of the region to be sensitized.
/// @param readCB   Function to be called.
/// @param userData Passed to the callback function.

void icmAddBusReadCallback (
    icmBusP       bus,
    icmProcessorP scope,
    Addr          lowAddr,
    Addr          highAddr,
    icmMemWatchFn readCB,
    void*         userData
);

/// This API is deprecated. Please refer to the documentation
/// Install a callback on write accesses using the bus
/// @param bus      Bus object.
/// @param scope    If non-null, restrict sensitivity to this processor.
/// @param lowAddr  Lowest address of the region to be sensitized.
/// @param highAddr Highest address of the region to be sensitized.
/// @param writeCB  Function to be called.
/// @param userData Passed to the callback function.

void icmAddBusWriteCallback (
    icmBusP       bus,
    icmProcessorP scope,
    Addr          lowAddr,
    Addr          highAddr,
    icmMemWatchFn writeCB,
    void*         userData
);

/// This API is deprecated. Please refer to the documentation
/// Add a control file to be read before simulation starts.
/// @param filename The control file.

void icmAddControlFile (
    const char* filename
);

/// This API is deprecated. Please refer to the documentation
/// Add a double attribute to the attributes list.
/// @param attrs Attribute list.
/// @param name  Name of new attribute (must be unique in this list).
/// @param value Double value.

void icmAddDoubleAttr (
    icmAttrListP attrs,
    const char*  name,
    double       value
);

/// This API is deprecated. Please refer to the documentation
/// Install a callback activated by fetches on the processor external code bus
/// @param processor Processor object.
/// @param lowAddr   Lowest address of the region to be sensitized.
/// @param highAddr  Highest address of the region to be sensitized.
/// @param writeCB   Function to be called.
/// @param userData  Passed to the callback function.

void icmAddFetchCallback (
    icmProcessorP processor,
    Addr          lowAddr,
    Addr          highAddr,
    icmMemWatchFn writeCB,
    void*         userData
);

/// This API is deprecated. Please refer to the documentation
/// Add an Int32 attribute to the given attributes list
/// @param attrs Attribute list
/// @param name  Name of new attribute (must be unique in this list)
/// @param value 32-bit signed integer value.

void icmAddInt32Attr (
    icmAttrListP attrs,
    const char*  name,
    Int32        value
);

/// This API is deprecated. Please refer to the documentation
/// Add an Int64 attribute to the given attributes list
/// @param attrs Attribute list
/// @param name  Name of new attribute (must be unique in this list)
/// @param value 64-bit signed integer value.

void icmAddInt64Attr (
    icmAttrListP attrs,
    const char*  name,
    Int64        value
);

/// This API is deprecated. Please refer to the documentation
/// Add a supplementary intercept shared object for a processor.
/// @return New intercept object.
/// @param processor       Processor to be intercepted.
/// @param instanceName    Unique name for this intercept (will be copied, so
///                        does not need to persist).
/// @param interceptFile   Path to the intercept object file.
/// @param interceptSymbol Not used. Set to null.
/// @param userAttrs       User defined attribute list for the intercept
///                        object (or null).

icmInterceptP icmAddInterceptObject (
    icmProcessorP processor,
    const char*   instanceName,
    const char*   interceptFile,
    const char*   interceptSymbol,
    icmAttrListP  userAttrs
);

/// This API is deprecated. Please refer to the documentation
/// Install a callback which will occur when a net is written.
/// @param net      The net object.
/// @param cb       Address of function to be called.
/// @param userData User data passed to callback.

void icmAddNetCallback (
    icmNetP  net,
    icmNetFn cb,
    void*    userData
);

/// This API is deprecated. Please refer to the documentation
/// Add a callback to a packetnet
/// @param packetnet Packetnet object
/// @param cb        callback function
/// @param userData  user data, passed to callback

void icmAddPacketnetCallback (
    icmPacketnetP          packetnet,
    icmPacketnetNotifierFn cb,
    void*                  userData
);

/// This API is deprecated. Please refer to the documentation
/// Ask for notification when a PSE maps an address port.
/// @param pse  The PSE.
/// @param port The PSE port name.
/// @param cb   The callback.
/// @param user User Data.

void icmAddPortMapCB (
    icmPseP         pse,
    const char*     port,
    icmPsePortMapFn cb,
    void*           user
);

/// This API is deprecated. Please refer to the documentation
/// This function indicates that the current processor should do nothing for a
/// number of clocks corresponding to the given delay. The purpose of this is to
/// enable after-the-event timing emulation.
/// @param processor Processor object.
/// @param time      Relative time.

void icmAddProcessorDelay (
    icmProcessorP processor,
    icmTime       time
);

/// This API is deprecated. Please refer to the documentation
/// Add a supplementary intercept shared object for a PSE.
/// @return New intercept object.
/// @param pse             PSE to be intercepted.
/// @param instanceName    Unique name for this intercept (will be copied, so
///                        does not need to persist).
/// @param interceptFile   Path to the intercept object file.
/// @param interceptSymbol Not used. Set to null
/// @param userAttrs       User defined attribute list for the intercept
///                        object (or null).

icmInterceptP icmAddPseInterceptObject (
    icmPseP      pse,
    const char*  instanceName,
    const char*  interceptFile,
    const char*  interceptSymbol,
    icmAttrListP userAttrs
);

/// This API is deprecated. Please refer to the documentation
/// Add a native host pointer attribute to the given attributes list
/// @param attrs Attribute list
/// @param name  Name of new attribute (must be unique in this list)
/// @param value Native host pointer value.

void icmAddPtrAttr (
    icmAttrListP attrs,
    const char*  name,
    void *       value
);

/// This API is deprecated. Please refer to the documentation
/// Install a callback activated by reads on the processor external data bus
/// @param processor Processor object.
/// @param lowAddr   Lowest address of the region to be sensitized.
/// @param highAddr  Highest address of the region to be sensitized.
/// @param readCB    Function to be called.
/// @param userData  Passed to the callback function.

void icmAddReadCallback (
    icmProcessorP processor,
    Addr          lowAddr,
    Addr          highAddr,
    icmMemWatchFn readCB,
    void*         userData
);

/// This API is deprecated. Please refer to the documentation
/// Install a callback to be called when a processor stops for an exception.
/// @param processor   The processor instance
/// @param stopHandler The handler function
/// @param userData    User data passed to the handler

void icmAddStopHandler (
    icmProcessorP    processor,
    icmStopHandlerFn stopHandler,
    void*            userData
);

/// This API is deprecated. Please refer to the documentation
/// Add a string attribute to the attributes list
/// @param attrs Attribute list.
/// @param name  Name of new attribute (must be unique in this list).
/// @param value String value

void icmAddStringAttr (
    icmAttrListP attrs,
    const char*  name,
    const char*  value
);

/// This API is deprecated. Please refer to the documentation
/// Add one symbol for address-symbol lookup.
/// @param processor Load into this processor's code address space.
/// @param symbol    The symbol.
/// @param value     Symbol address.
/// @param size      Symbol size in bytes (set to 1 if not known).
/// @param type      Symbol type: 2=function,1=object,0=other.
/// @param binding   Symbol binding: 2=weak,1=global,0=local.

void icmAddSymbol (
    icmProcessorP processor,
    const char*   symbol,
    Addr          value,
    Addr          size,
    int           type,
    int           binding
);

/// This API is deprecated. Please refer to the documentation
/// Add an Uns32 attribute to the given attributes list
/// @param attrs Attribute list
/// @param name  Name of new attribute (must be unique in this list)
/// @param value 32-bit unsigned integer value.

void icmAddUns32Attr (
    icmAttrListP attrs,
    const char*  name,
    Uns32        value
);

/// This API is deprecated. Please refer to the documentation
/// Add an Uns64 attribute to the given attributes list
/// @param attrs Attribute list
/// @param name  Name of new attribute (must be unique in this list)
/// @param value 64-bit unsigned integer value.

void icmAddUns64Attr (
    icmAttrListP attrs,
    const char*  name,
    Uns64        value
);

/// This API is deprecated. Please refer to the documentation
/// Install a callback activated by writes on the processor external data bus
/// @param processor Processor object.
/// @param lowAddr   Lowest address of the region to be sensitized.
/// @param highAddr  Highest address of the region to be sensitized.
/// @param writeCB   Function to be called.
/// @param userData  Passed to the callback function.

void icmAddWriteCallback (
    icmProcessorP processor,
    Addr          lowAddr,
    Addr          highAddr,
    icmMemWatchFn writeCB,
    void*         userData
);

/// This API is deprecated. Please refer to the documentation
/// Advance time processing any pending events due in the period. This will
/// cause PSEs and other timed models to process any pending events or delays.
/// The amount that time is advanced, vs. the number of instructions that each
/// processor executes, sets the effective processor speeds.
/// @return Returns True if simulation must continue, False if finish
///         requested.
/// @param time The new ABSOLUTE time (this is not relative).

Bool icmAdvanceTime (
    icmTime time
);

/// This API is deprecated. Please refer to the documentation
/// Advance time processing any pending events due in the period. This is the
/// same as icmAdvanceTime(), but takes a double (less precision). This is used
/// by the TLM integration (TLM uses double in MSVC).
/// @return Returns True if simulation must continue, False if finish
///         requested.
/// @param time The new ABSOLUTE time (this is not relative).

Bool icmAdvanceTimeDouble (
    double time
);

/// This API is deprecated. Please refer to the documentation
/// Call the given function on all files matching the VLNV specification.
/// @param vlnvroot Path or list of paths to root of directory(s) containing
///                 modelsT
/// @param vendor   Vendor directory e.g. yourcompany.com or '*'
/// @param library  Library directory e.g. processor or '*'
/// @param name     Name directory e.g. risc32 or '*'
/// @param version  Version directory e.g. 1.0 or '*'
/// @param objType  Filename in the version directory or 'pse' or 'model'
/// @param cb       Callback
/// @param userData User data passed to cb

void icmAllVlnvFiles (
    const char*    vlnvroot,
    const char*    vendor,
    const char*    library,
    const char*    name,
    const char*    version,
    const char*    objType,
    icmFoundFileFn cb,
    void*          userData
);

/// This API is deprecated. Please refer to the documentation
/// Call this function during exit
/// @param cb Function to be called (may be more than one)

void icmAtExit (
    icmExitFn cb
);

/// This API is deprecated. Please refer to the documentation
/// Print the simulator banner (unless --nobanner is specified)

void icmBanner (void);

/// This API is deprecated. Please refer to the documentation
/// Create dynamic bridge (not for static platforms).
/// @param slave         Bus with slave port; region which gets addressed.
/// @param master        Bus with master port; region which acts as a bus
///                      master.
/// @param lowAddrSlave  The lower end of the slave region.
/// @param highAddrSlave The higher end of the slave region.
/// @param lowAddrMaster The lower end of the master region.

void icmBridgeBuses (
    icmBusP slave,
    icmBusP master,
    Addr    lowAddrSlave,
    Addr    highAddrSlave,
    Addr    lowAddrMaster
);

/// This API is deprecated. Please refer to the documentation
/// Return the object file for a default platform, if one is specified.
/// @return Path to object file if exactly one is specified

const char * icmCLPDefaultObjectFile (void);

/// This API is deprecated. Please refer to the documentation
/// Return true if the named argument has been used on the command line.
/// @return Path to object file if exactly one is specified
/// @param parser Parser
/// @param name   name of the flag (without the '-')

Bool icmCLParseArgUsed (
    icmCLPP       parser,
    const char  * name
);

/// This API is deprecated. Please refer to the documentation
/// Parse an argv/argc array
/// @return True if parsed without errors
/// @param parser Parser
/// @param argc   Argument count
/// @param argv   Argument array

Bool icmCLParseArgs (
    icmCLPP       parser,
    Uns32         argc,
    const char ** argv
);

/// This API is deprecated. Please refer to the documentation
/// Parse a control file
/// @return True if parsed without errors
/// @param parser Parser
/// @param path   Path to file

Bool icmCLParseFile (
    icmCLPP       parser,
    const char  * path
);

/// This API is deprecated. Please refer to the documentation
/// Parse an argv/argc array using standard arguments. Exits if errors are
/// detected.
/// @param client Name of the client (for error reporting)
/// @param select Select which flags are installed.
/// @param argc   Argument count
/// @param argv   Argument array

void icmCLParseStd (
    const char *   client,
    icmCLPArgClass select,
    Uns32          argc,
    const char **  argv
);

/// This API is deprecated. Please refer to the documentation
/// Create a command line parser
/// @return Handle to the new parser
/// @param client    Name of the client (for error reporting)
/// @param argSelect Select which standard flags are installed.

icmCLPP icmCLParser (
    const char *   client,
    icmCLPArgClass argSelect
);

/// This API is deprecated. Please refer to the documentation
/// Add an argument to be accepted by this parser. The bit mask is used as
/// follows: If the mask is zero , this argument will always be in the parser.
/// If the mask is non-zero, the argument will be installed if the corresponding
/// bit is set in the parse constructor. The flags are allocated as follows: bit
/// 0 : reserved for internal use. bit 1 : for use in the standard product. bits
/// 2-4 : reserved for internal use. bits 5-31: for use by external tools.
/// @param parser      Parser
/// @param name        Argument name. Must be unique.
/// @param shortname   Optional argument short name. Must be unique.
/// @param argDesc     Optional description of the argument value (e.g.
///                    filename)
/// @param group       Optional argument group
/// @param type        Argument type
/// @param ptr         Pointer to data or function
/// @param description Appears with -help
/// @param useMask     Use Mask. See function description.
/// @param userData    Passed to function
/// @param mandatory   This argument must be specified

void icmCLParserAdd (
    icmCLPP       parser,
    const char *  name,
    const char *  shortname,
    const char *  argDesc,
    const char *  group,
    icmCLPArgType type,
    void*         ptr,
    const char *  description,
    Uns32         useMask,
    Uns32         userData,
    Bool          mandatory
);

/// This API is deprecated. Please refer to the documentation
/// Destroy the parser
/// @param parser Parser

void icmCLParserOld (
    icmCLPP parser
);

/// This API is deprecated. Please refer to the documentation
/// Print this message with -help or if errors are found
/// @param parser  Parser
/// @param message General help message

void icmCLParserUsageMessage (
    icmCLPP       parser,
    const char  * message
);

/// This API is deprecated. Please refer to the documentation
/// Call a command that was installed in an Intercept object or model.
/// @return The result string, or null
/// @param modelInstanceName  Instance name of processor or PSE
/// @param pluginInstanceName Instance name of plugin (intercept object).
///                           Zero if the command is in the model.
/// @param command            Name of the command
/// @param argc               Number of args to the command, plus one for the
///                           command name.
/// @param argv               Array of string arguments. The first element
///                           should be the command name.

const char* icmCallCommand (
    const char*  modelInstanceName,
    const char*  pluginInstanceName,
    const char*  command,
    Uns32        argc,
    const char** argv
);

/// This API is deprecated. Please refer to the documentation
/// Cancel text redirection.
/// @param redir Redirection object

void icmCancelTextOutputFn (
    icmRedirectP redir
);

/// This API is deprecated. Please refer to the documentation
/// Cancel the trigger event (before it triggers).
/// @param event The event.

void icmCancelTrigger (
    icmTriggerEventP event
);

/// This API is deprecated. Please refer to the documentation
/// Clear address breakpoint for the processor.
/// @param processor  Processor on which to clear breakpoint
/// @param simAddress Address at which break should no longer occur

void icmClearAddressBreakpoint (
    icmProcessorP processor,
    Addr          simAddress
);

/// This API is deprecated. Please refer to the documentation
/// Clear instruction count breakpoint for the processor
/// @param processor Processor handle.

void icmClearICountBreakpoint (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Restore the state of the given connection object (e.g. FIFO)
/// @return Success or failure.
/// @param conn     The connection object to restore
/// @param cb       The function used to restore data
/// @param userData User context, passed back in the callback

icmSaveRestoreStatus icmConnRestoreState (
    icmConnP     conn,
    icmRestoreFn cb,
    void *       userData
);

/// This API is deprecated. Please refer to the documentation
/// Restore the state of the given connection object (e.g. FIFO) from a file in
/// default format
/// @return Success or failure.
/// @param conn The connection object to restore
/// @param file File name from which to restore

icmSaveRestoreStatus icmConnRestoreStateFile (
    icmConnP     conn,
    const char * file
);

/// This API is deprecated. Please refer to the documentation
/// Save the state of the given connection object (e.g. FIFO)
/// @return Success or failure.
/// @param conn     The connection object to save
/// @param cb       The function used to save data
/// @param userData User context, passed back in the callback

icmSaveRestoreStatus icmConnSaveState (
    icmConnP  conn,
    icmSaveFn cb,
    void *    userData
);

/// This API is deprecated. Please refer to the documentation
/// Save the state of the given connection object (e.g. FIFO) to a file in
/// default format
/// @return Success or failure.
/// @param conn The connection object to save
/// @param file File name to which to save

icmSaveRestoreStatus icmConnSaveStateFile (
    icmConnP     conn,
    const char * file
);

/// This API is deprecated. Please refer to the documentation
/// Connect an MMC bus port to the bus. 'isMaster' specifies whether the port is
/// a bus master (i.e. written by the MMC) or a slave (read by the MMC).
/// @param mmc      The MMC to be connected.
/// @param bus      The bus to be connected.
/// @param portName The name of the port on the MMC.
/// @param isMaster If true, this is a bus master port, if false this is a
///                 slave port.

void icmConnectMMCBus (
    icmMmcP     mmc,
    icmBusP     bus,
    const char* portName,
    Bool        isMaster
);

/// This API is deprecated. Please refer to the documentation
/// Connect a memory object and a bus, using the named memory port
/// @param bus      The bus object.
/// @param portName Unique name of port created by this call.
/// @param memory   A memory object already created.
/// @param lowAddr  Base (decoded) address of the connected memory

void icmConnectMemoryToBus (
    icmBusP     bus,
    const char* portName,
    icmMemoryP  memory,
    Addr        lowAddr
);

/// This API is deprecated. Please refer to the documentation
/// Connect a PSE bus port to a bus.
/// @param pse      The PSE to be connected.
/// @param bus      The bus to be connected.
/// @param portName Name of the port on the PSE. This must exist in the PSE
///                 model.
/// @param isMaster If True, this is a bus master, otherwise a bus slave.
///                 This must match the semantics of the port in the model.
/// @param lowAddr  Base address on the bus where the port is connected.
/// @param highAddr Highest address on the bus where the port is connected.

void icmConnectPSEBus (
    icmPseP     pse,
    icmBusP     bus,
    const char* portName,
    Bool        isMaster,
    Addr        lowAddr,
    Addr        highAddr
);

/// This API is deprecated. Please refer to the documentation
/// Connect a PSE bus port to the bus with a range specified by the PSE at
/// run-time.
/// @param pse      The PSE to be connected.
/// @param bus      The bus to be connected.
/// @param portName Name of the port on the PSE. This must exist in the PSE
///                 model.
/// @param isMaster If True, this is a bus master, otherwise a bus slave.
///                 This must match the semantics of the port in the model.

void icmConnectPSEBusDynamic (
    icmPseP     pse,
    icmBusP     bus,
    const char* portName,
    Bool        isMaster
);

/// This API is deprecated. Please refer to the documentation
/// Connect a PSE instance port to a net
/// @param pse      The PSE to be connected.
/// @param net      The net to be connected.
/// @param portName Name of the port on the PSE. This must exist in the PSE
///                 model. It must be net port.
/// @param notUsed  Set to zero; this argument is not used

void icmConnectPSENet (
    icmPseP      pse,
    icmNetP      net,
    const char*  portName,
    icmDirection notUsed
);

/// This API is deprecated. Please refer to the documentation
/// Connect a PSE to a packetnet
/// @param pse       PSE object.
/// @param packetnet Packetnet object
/// @param portName  Name of the packetnet port on the peripheral

void icmConnectPSEPacketnet (
    icmPseP       pse,
    icmPacketnetP packetnet,
    const char *  portName
);

/// This API is deprecated. Please refer to the documentation
/// Connect the processor to a bus using the named port.
/// @param processor Processor to connect.
/// @param port      The port name.
/// @param bus       The bus (created with icmNewBus()).

void icmConnectProcessorBusByName (
    icmProcessorP processor,
    const char*   port,
    icmBusP       bus
);

/// This API is deprecated. Please refer to the documentation
/// Connect the processor to the passed instruction and data buses.
/// @param processor      Processor to connect.
/// @param instructionBus The instruction bus (created with icmNewBus()).
/// @param dataBus        The data bus (created with icmNewBus()).

void icmConnectProcessorBusses (
    icmProcessorP processor,
    icmBusP       instructionBus,
    icmBusP       dataBus
);

/// This API is deprecated. Please refer to the documentation
/// Connect a processor connection object port.
/// @param icmProcessor Processor to connect.
/// @param conn         The connection object (see icmNewFifo()).
/// @param portName     Name of the port on the processor (see VMI
///                     documentation).
/// @param direction    ICM_INPUT or ICM_OUTPUT.

void icmConnectProcessorConn (
    icmProcessorP icmProcessor,
    icmConnP      conn,
    const char*   portName,
    icmDirection  direction
);

/// This API is deprecated. Please refer to the documentation
/// Connect a processor net port with the passed name and direction to a net.
/// @param icmProcessor Processor to connect.
/// @param net          The net (created with icmNewNet())
/// @param portName     Name of the port on the processor (see VMI
///                     documentation).
/// @param notUsed      Set to zero; this argument is not used

void icmConnectProcessorNet (
    icmProcessorP icmProcessor,
    icmNetP       net,
    const char*   portName,
    icmDirection  notUsed
);

/// This API is deprecated. Please refer to the documentation
/// Read a region from the processor address space into native memory, without
/// side effects. When calculating the byte-swap requirements, it uses the
/// processor's DATA endian-ness.
/// @return True if access was successful. False if any part failed.
/// @param processor  Processor object.
/// @param simAddress Base address of the region to be read.
/// @param buffer     Pointer to host space to receive the data.
/// @param objectSize Number of bytes in each endian-corrected object.
/// @param objects    Number of objects.
/// @param hostEndian Endian-ness of data in host buffer.

Bool icmDebugReadProcessorMemory (
    icmProcessorP processor,
    Addr          simAddress,
    void*         buffer,
    Uns32         objectSize,
    Uns32         objects,
    icmHostEndian hostEndian
);

/// This API is deprecated. Please refer to the documentation
/// Add this to the list of processors to attach a debugger (max=1 in OVPsim).
/// @param processor Processor handle.

void icmDebugThisProcessor (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Write a region from native memory into processor address, without
/// side-effects. When calculating the byte-swap requirements, it uses the
/// processor's DATA endian-ness.
/// @return True if access was successful. False if any part failed.
/// @param processor  Processor object.
/// @param simAddress Base address of the region to be written
/// @param buffer     Pointer to host space containing the data.
/// @param objectSize Number of bytes in each endian-corrected object.
/// @param objects    Number of objects.
/// @param hostEndian Endian-ness of data in host buffer.

Bool icmDebugWriteProcessorMemory (
    icmProcessorP processor,
    Addr          simAddress,
    const void*   buffer,
    Uns32         objectSize,
    Uns32         objects,
    icmHostEndian hostEndian
);

/// This API is deprecated. Please refer to the documentation
/// Remove a callback that was called when a processor stops for an exception.
/// @param processor   The processor instance
/// @param stopHandler The handler function
/// @param userData    User data passed to the handler

void icmDeleteStopHandler (
    icmProcessorP    processor,
    icmStopHandlerFn stopHandler,
    void*            userData
);

/// This API is deprecated. Please refer to the documentation
/// Delete the passed watchpoint object
/// @param watchpoint Watchpoint to delete

void icmDeleteWatchPoint (
    icmWatchPointP watchpoint
);

/// This API is deprecated. Please refer to the documentation
/// This function sets an external de-rate factor for a processor (0-100%,
/// default 0%). This enables the simulation environment to indicate that the
/// processor should execute at a reduced percentage of its configured MIPS
/// rate. This is necessary for the platform to be able to simulate the effect
/// of reduced-rate clocking, for example.
/// @param processor Processor object.
/// @param factor    De-rating factor

void icmDerateProcessor (
    icmProcessorP processor,
    double        factor
);

/// This API is deprecated. Please refer to the documentation
/// Disable trace buffer for the passed processor
/// @param processor Turn off trace buffer for this processor

void icmDisableTraceBuffer (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Call the processor-specific register dump
/// @return Disassembly string. This is a static buffer, so will be
///         overwritten by the next call.
/// @param processor Processor object.
/// @param simAddr   Address of instruction to be disassembled. Must be
///                  correctly instruction-aligned for a meaningful result.

const char* icmDisassemble (
    icmProcessorP processor,
    Addr          simAddr
);

/// This API is deprecated. Please refer to the documentation
/// Get the child of this node.
/// @return Pointer to child document node, or null.
/// @param node Current document node, or null to get the root.

icmDocNodeP icmDocChildNode (
    icmDocNodeP node
);

/// This API is deprecated. Please refer to the documentation
/// Is this content or a title?
/// @return True if this is content, False it it's a title.
/// @param node Document node.

Bool icmDocIsText (
    icmDocNodeP node
);

/// This API is deprecated. Please refer to the documentation
/// Get the next node.
/// @return Pointer to next document node, or null.
/// @param node Current document node

icmDocNodeP icmDocNextNode (
    icmDocNodeP node
);

/// This API is deprecated. Please refer to the documentation
/// Attach a document section to the current platform, or to an existing
/// section.
/// @return Pointer to the new node
/// @param node        Existing parent node, or null to add to the platform.
/// @param sectionName Name of the new section.

icmDocNodeP icmDocSectionAdd (
    icmDocNodeP  node,
    const char * sectionName
);

/// This API is deprecated. Please refer to the documentation
/// Get title or content text from this node (use icmDocIsText to find which it
/// is).
/// @return Pointer to text.
/// @param node Document node.

const char * icmDocText (
    icmDocNodeP node
);

/// This API is deprecated. Please refer to the documentation
/// Attach text to an existing document section.
/// @param node Existing parent node, or null to add to the platform.
/// @param text A paragraph of new text.

void icmDocTextAdd (
    icmDocNodeP  node,
    const char * text
);

/// This API is deprecated. Please refer to the documentation
/// Call the processor-specific register dump
/// @param processor Processor object.

void icmDumpRegisters (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Dump the processor trace buffer
/// @param processor The processor of interest.

void icmDumpTraceBuffer (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Enable trace buffer for the passed processor The trace buffer records the
/// last few addresses the processor executed, so that when a problem occurs, a
/// short instruction history can be recovered.
/// @param processor Turn on trace buffer for this processor

void icmEnableTraceBuffer (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Returns how many errors have been reported so far
/// @return Number of errors reported by icmMessage(E)

Uns32 icmErrors (void);

/// This API is deprecated. Please refer to the documentation
/// Terminate execution of the current processor and return immediately from
/// icmSimulate with icmStopReason ICM_SR_EXIT (typically used within
/// icmMemReadFn or icmMemWriteFn callback).
/// @param processor The processor that was running.

void icmExit (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Use this in place of exit()
/// @param exitCode Process exit code

void icmExitSimulation (
    Uns32 exitCode
);

/// This API is deprecated. Please refer to the documentation
/// Find intercept shared object on a processor.
/// @return The intercept object.
/// @param processor    Processor holding the object.
/// @param instanceName Unique name for this intercept.

icmInterceptP icmFindInterceptObject (
    icmProcessorP processor,
    const char*   instanceName
);

/// This API is deprecated. Please refer to the documentation
/// Get the handle of an MMC instance from its name.
/// @return Handle of the MMC.
/// @param name The name of the MMC.

icmMmcP icmFindMMCByName (
    const char* name
);

/// This API is deprecated. Please refer to the documentation
/// Find intercept shared object on a PSE
/// @return New intercept object.
/// @param processor    PSE holding the object.
/// @param instanceName Unique name for this intercept.

icmInterceptP icmFindPSEInterceptObject (
    icmPseP     processor,
    const char* instanceName
);

/// This API is deprecated. Please refer to the documentation
/// Get handle to an existing processor object from the current platform.
/// @return Processor object.
/// @param name hierarchical name of processor instance.

icmProcessorP icmFindProcessorByName (
    const char* name
);

/// This API is deprecated. Please refer to the documentation
/// Find a double attribute by name
/// @return If found, the pointer is set and True returned.
/// @param attrList Processor object.
/// @param name     The attribute name.
/// @param valp     Pointer to attribute value.

Bool icmFindProcessorDoubleAttribute (
    icmProcessorP attrList,
    const char*   name,
    double*       valp
);

/// This API is deprecated. Please refer to the documentation
/// Find a net port by name. This can then be written.
/// @return Net Port object.
/// @param processor Processor to search.
/// @param name      Name of net port.

icmNetPortP icmFindProcessorNetPort (
    icmProcessorP processor,
    const char*   name
);

/// This API is deprecated. Please refer to the documentation
/// Find a string attribute by name
/// @return The value of the attribute (or null)
/// @param attrList Processor object.
/// @param name     The attribute name.

const char* icmFindProcessorStringAttribute (
    icmProcessorP attrList,
    const char*   name
);

/// This API is deprecated. Please refer to the documentation
/// Search for an existing PSE by name in the current platform.
/// @return PSE object.
/// @param name Instance name of PSE.

icmPseP icmFindPseByName (
    const char* name
);

/// This API is deprecated. Please refer to the documentation
/// Find a net port by name. This can then be written.
/// @return Net Port object.
/// @param pse  PSE to search.
/// @param name Name of net port.

icmNetPortP icmFindPseNetPort (
    icmPseP     pse,
    const char* name
);

/// This API is deprecated. Please refer to the documentation
/// Terminate execution of the current processor and return immediately from
/// icmSimulate with icmStopReason ICM_SR_FINISH (typically used within
/// icmMemReadFn or icmMemWriteFn callback).
/// @param processor The processor that was running, or null.
/// @param status    Status code.

void icmFinish (
    icmProcessorP processor,
    Int32         status
);

/// This API is deprecated. Please refer to the documentation
/// Inform the simulator that the memory range lowAddr:highAddr has been
/// modified
/// @param memory   Memory object.
/// @param lowAddr  Low address of range to flush.
/// @param highAddr High address of range to flush.

void icmFlushMemory (
    icmMemoryP memory,
    Addr       lowAddr,
    Addr       highAddr
);

/// This API is deprecated. Please refer to the documentation
/// Inform the simulator that the given mapped native region has been modified
/// @param base  Native memory region
/// @param bytes Number of bytes in the region

void icmFlushNativeMemory (
    const void* base,
    UnsPS       bytes
);

/// This API is deprecated. Please refer to the documentation
/// Inform a processor that it's code memory has been updated
/// @param processor Processor object
/// @param lowAddr   Lower extent of modified memory
/// @param highAddr  Upper extent of modified memory

void icmFlushProcessorMemory (
    icmProcessorP processor,
    Addr          lowAddr,
    Addr          highAddr
);

/// This API is deprecated. Please refer to the documentation
/// Free attributes list (call at end of simulation)
/// @param attrs The list to be freed.

void icmFreeAttrList (
    icmAttrListP attrs
);

/// This API is deprecated. Please refer to the documentation
/// Deprecated - Please use icmTerminate.
/// @param bus Bus object.

void icmFreeBus (
    icmBusP bus
);

/// This API is deprecated. Please refer to the documentation
/// Deprecated - Please use icmTerminate.
/// @param bridge The Bridge to Free

void icmFreeBusBridge (
    icmBusBridgeP bridge
);

/// This API is deprecated. Please refer to the documentation
/// Deprecated - Please use icmTerminate.
/// @param fifo The FIFO object.

void icmFreeFifo (
    icmConnP fifo
);

/// This API is deprecated. Please refer to the documentation
/// Deprecated - Please use icmTerminate.
/// @param mmc The MMC to be freed.

void icmFreeMMC (
    icmMmcP mmc
);

/// This API is deprecated. Please refer to the documentation
/// Deprecated - Please use icmTerminate.
/// @param memory The memory object.

void icmFreeMemory (
    icmMemoryP memory
);

/// This API is deprecated. Please refer to the documentation
/// Deprecated - Please use icmTerminate.
/// @param net The net object to be freed.

void icmFreeNet (
    icmNetP net
);

/// This API is deprecated. Please refer to the documentation
/// Deprecated - Please use icmTerminate.
/// @param pse The PSE to be freed.

void icmFreePSE (
    icmPseP pse
);

/// This API is deprecated. Please refer to the documentation
/// Deprecated - Please use icmTerminate.
/// @param processor Processor to free.

void icmFreeProcessor (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Freeze the processor (frozen processors will not be run by icmSimulate or
/// icmSimulatePlatform).
/// @param processor The processor that was running.

void icmFreeze (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Request a callback for each command in each processor and each plugin.
/// @param commandCB The callback.
/// @param userData  User data to be returned in callback.

void icmGetAllPlatformCommands (
    icmInstalledCommandFn commandCB,
    void*                 userData
);

/// This API is deprecated. Please refer to the documentation
/// Request a callback for each command in the given processor and each plugin.
/// @param processor Processor handle.
/// @param commandCB The callback.
/// @param userData  User data to be returned in callback.

void icmGetAllProcessorCommands (
    icmProcessorP         processor,
    icmInstalledCommandFn commandCB,
    void*                 userData
);

/// This API is deprecated. Please refer to the documentation
/// Return the application-specific handle associated with the bus
/// @return The user's handle.
/// @param bus The bus object.

void* icmGetBusHandle (
    icmBusP bus
);

/// This API is deprecated. Please refer to the documentation
/// Return the bus port number of address bits
/// @return Number of address bits.
/// @param busPort Handle to bus port descriptor.

Uns32 icmGetBusPortAddrBits (
    icmBusPortInfoP busPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the maximum supported number of address bits
/// @return Maximum number of address bits.
/// @param busPort Handle to bus port descriptor.

Uns32 icmGetBusPortAddrBitsMax (
    icmBusPortInfoP busPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the minimum supported number of address bits
/// @return Minimum number of address bits.
/// @param busPort Handle to bus port descriptor.

Uns32 icmGetBusPortAddrBitsMin (
    icmBusPortInfoP busPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the number of bytes addressed (less one) by the port (if a slave
/// port) or zero (if a master port)
/// @return One less than the number of bytes addressed
/// @param busPort Handle to bus port descriptor.

Addr icmGetBusPortBytes (
    icmBusPortInfoP busPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the bus port description descriptor
/// @return A short description.
/// @param busPort Handle to bus port descriptor.

const char* icmGetBusPortDesc (
    icmBusPortInfoP busPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the bus port domain type from the descriptor
/// @return The type.
/// @param busPort Handle to bus port descriptor.

icmDomainType icmGetBusPortDomainType (
    icmBusPortInfoP busPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the bus port domain type from the descriptor as a string
/// @return The type.
/// @param busPort Handle to bus port descriptor.

const char* icmGetBusPortDomainTypeString (
    icmBusPortInfoP busPort
);

/// This API is deprecated. Please refer to the documentation
/// Return if this port cannot be left unconnected.
/// @return True if this bus port cannot be left unconnected.
/// @param busPort Handle to bus port descriptor.

Bool icmGetBusPortMustBeConnected (
    icmBusPortInfoP busPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the bus port name from the descriptor
/// @return The bus port name (note that this string does not persist).
/// @param busPort Handle to bus port descriptor.

const char* icmGetBusPortName (
    icmBusPortInfoP busPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the bus port type from the descriptor
/// @return The type.
/// @param busPort Handle to bus port descriptor.

icmBusPortType icmGetBusPortType (
    icmBusPortInfoP busPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the bus port type from the descriptor as a string
/// @return The type.
/// @param busPort Handle to bus port descriptor.

const char* icmGetBusPortTypeString (
    icmBusPortInfoP busPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the current processor. This function should only be used from within
/// a callback.
/// @return The current processor context.

icmProcessorP icmGetCurrentProcessor (void);

/// This API is deprecated. Please refer to the documentation
/// Get the current simulated time
/// @return Current simulation time (see icmTime).

icmTime icmGetCurrentTime (void);

/// This API is deprecated. Please refer to the documentation
/// Returns the current processor exception description (NULL if the model does
/// not implement or expose exceptions).
/// @return Exception description
/// @param processor Processor object.

icmExceptionInfoP icmGetException (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Return the model-specific exception code from the descriptor
/// @return Exception code.
/// @param exceptionInfo Handle to exception object.

Uns32 icmGetExceptionInfoCode (
    icmExceptionInfoP exceptionInfo
);

/// This API is deprecated. Please refer to the documentation
/// Return the description of the exception from the descriptor
/// @return Exception description
/// @param exceptionInfo Handle to exception object.

const char* icmGetExceptionInfoDescription (
    icmExceptionInfoP exceptionInfo
);

/// This API is deprecated. Please refer to the documentation
/// Return the name of the exception from the descriptor
/// @return Exception name (note that this string does not persist).
/// @param exceptionInfo Handle to exception object.

const char* icmGetExceptionInfoName (
    icmExceptionInfoP exceptionInfo
);

/// This API is deprecated. Please refer to the documentation
/// Return fault address associated with the processor state if applicable.
/// @return Whether by-ref fault address is valid
/// @param processor    Processor object.
/// @param faultAddress Pointer filled with fault address

Bool icmGetFaultAddress (
    icmProcessorP processor,
    Addr *        faultAddress
);

/// This API is deprecated. Please refer to the documentation
/// Return application-specific handle associated with the FIFO
/// @return The user's handle.
/// @param fifo The FIFO object.

void* icmGetFifoHandle (
    icmConnP fifo
);

/// This API is deprecated. Please refer to the documentation
/// Return the FIFO port's description
/// @return Brief description
/// @param fifoPort Handle to FIFO port descriptor.

const char* icmGetFifoPortDesc (
    icmFifoPortInfoP fifoPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the FIFO port name from the descriptor
/// @return The FIFO port name (note that this string does not persist).
/// @param fifoPort Handle to FIFO port descriptor.

const char* icmGetFifoPortName (
    icmFifoPortInfoP fifoPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the FIFO port type (input or output) from the descriptor
/// @return The FIFO port type (direction of use)
/// @param fifoPort Handle to FIFO port descriptor.

icmFifoPortType icmGetFifoPortType (
    icmFifoPortInfoP fifoPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the FIFO port type (input or output) from the descriptor
/// @return The FIFO port type (direction of use) as a string
/// @param fifoPort Handle to FIFO port descriptor.

const char* icmGetFifoPortTypeString (
    icmFifoPortInfoP fifoPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the FIFO port width (in bits) from the descriptor
/// @return The FIFO port Width, in bits
/// @param fifoPort Handle to FIFO port descriptor.

Uns32 icmGetFifoPortWidth (
    icmFifoPortInfoP fifoPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the ELF code of a loaded file.
/// @return Returns the ELF processor architecture code.
/// @param file Handle of loaded object file.

Uns32 icmGetImagefileElfcode (
    icmImagefileP file
);

/// This API is deprecated. Please refer to the documentation
/// Return the endianness of a loaded file.
/// @return See icmEndian enumerated type.
/// @param file Handle of loaded object file.

icmEndian icmGetImagefileEndian (
    icmImagefileP file
);

/// This API is deprecated. Please refer to the documentation
/// Return the start address in the object file.
/// @return Return the start-address (entry point) of a loaded file.
/// @param file Handle of loaded object file.

Addr icmGetImagefileEntry (
    icmImagefileP file
);

/// This API is deprecated. Please refer to the documentation
/// Get the name of an intercept shared object.
/// @return Name of intercept object (note that this string does not
///         persist).
/// @param intercept Intercept object handle.

const char* icmGetInterceptObjectName (
    icmInterceptP intercept
);

/// This API is deprecated. Please refer to the documentation
/// Return the current release status of this intercept shared object
/// @return Release status (enumerated type)
/// @param intercept intercept object.

icmReleaseStatus icmGetInterceptObjectReleaseStatus (
    icmInterceptP intercept
);

/// This API is deprecated. Please refer to the documentation
/// Return the current visibility of this intercept shared object
/// @return Current visibility
/// @param intercept intercept object.

icmVisibility icmGetInterceptObjectVisibility (
    icmInterceptP intercept
);

/// This API is deprecated. Please refer to the documentation
/// Get the VLNV spec of this intercept object.
/// @return Pointer to VLNV structure.
/// @param intercept Intercept object handle.

icmVlnvP icmGetInterceptVlnv (
    icmInterceptP intercept
);

/// This API is deprecated. Please refer to the documentation
/// Get the instance name of this MMC.
/// @return The hierarchical name
/// @param mmc MMC object.

const char * icmGetMMCName (
    icmMmcP mmc
);

/// This API is deprecated. Please refer to the documentation
/// Return the current release status of this MMC
/// @return Release status (enumerated type)
/// @param mmc MMC object.

icmReleaseStatus icmGetMMCReleaseStatus (
    icmMmcP mmc
);

/// This API is deprecated. Please refer to the documentation
/// Return the visibility of the model
/// @return instance visibility
/// @param mmc MMC object.

icmVisibility icmGetMMCVisibility (
    icmMmcP mmc
);

/// This API is deprecated. Please refer to the documentation
/// Get the VLNV spec of this MMC.
/// @return Pointer to VLNV structure.
/// @param mmc MMC object.

icmVlnvP icmGetMMCVlnv (
    icmMmcP mmc
);

/// This API is deprecated. Please refer to the documentation
/// Return the user's handle associated with the memory
/// @return User's handle.
/// @param memory Return application-specific handle associated with the
///               memory.

void* icmGetMemoryHandle (
    icmMemoryP memory
);

/// This API is deprecated. Please refer to the documentation
/// Returns the current processor mode description (NULL if the model does not
/// implement or expose modes).
/// @return Mode description
/// @param processor Processor object.

icmModeInfoP icmGetMode (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Return the model-specific mode code from the descriptor
/// @return Mode code.
/// @param modeInfo Handle to mode object.

Uns32 icmGetModeInfoCode (
    icmModeInfoP modeInfo
);

/// This API is deprecated. Please refer to the documentation
/// Return the description of the mode from the descriptor
/// @return Mode description.
/// @param modeInfo Handle to mode object.

const char* icmGetModeInfoDescription (
    icmModeInfoP modeInfo
);

/// This API is deprecated. Please refer to the documentation
/// Return the name of the mode from the descriptor
/// @return Mode name (note that this string does not persist).
/// @param modeInfo Handle to mode object.

const char* icmGetModeInfoName (
    icmModeInfoP modeInfo
);

/// This API is deprecated. Please refer to the documentation
/// Return application-specific handle associated with the net
/// @return The user's handle
/// @param net The net object.

void* icmGetNetHandle (
    icmNetP net
);

/// This API is deprecated. Please refer to the documentation
/// Return the net port description
/// @return A short description.
/// @param netPort Handle to net port descriptor.

const char* icmGetNetPortDesc (
    icmNetPortInfoP netPort
);

/// This API is deprecated. Please refer to the documentation
/// Returns true if this netport must be connected for the model to function
/// @return True if must be connected.
/// @param netPort Handle to net port descriptor.

Bool icmGetNetPortMustBeConnected (
    icmNetPortInfoP netPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the net port name from the descriptor
/// @return The net port name (note that this string does not persist).
/// @param netPort Handle to net port descriptor.

const char* icmGetNetPortName (
    icmNetPortInfoP netPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the net port type from the descriptor
/// @return The type.
/// @param netPort Handle to net port descriptor.

icmNetPortType icmGetNetPortType (
    icmNetPortInfoP netPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the net port type from the descriptor, as a string
/// @return The type.
/// @param netPort Handle to net port descriptor.

const char* icmGetNetPortTypeString (
    icmNetPortInfoP netPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the time of the next scheduled event. Note that a new event could be
/// scheduled during this period
/// @return The absolute time of the next scheduled event.

icmTime icmGetNextEventTime (void);

/// This API is deprecated. Please refer to the documentation
/// Returns the next processor exception description, given the previous
/// description. Pass NULL to get the first description.
/// @return Next exception description
/// @param processor Processor object.
/// @param previous  Previous exception description, or null to start off.

icmExceptionInfoP icmGetNextException (
    icmProcessorP     processor,
    icmExceptionInfoP previous
);

/// This API is deprecated. Please refer to the documentation
/// Return the address of the next instruction, allowing for variable length
/// instructions.
/// @return Processor current instruction address
/// @param processor Processor object.
/// @param thisPC    The address of the current instruction

Addr icmGetNextInstructionAddress (
    icmProcessorP processor,
    Addr          thisPC
);

/// This API is deprecated. Please refer to the documentation
/// Return the next parameter description
/// @return Pointer to parameter info.
/// @param intercept Intercept object handle.
/// @param paramInfo Handle to previous parameter or null to begin.

icmParamInfoP icmGetNextInterceptParamInfo (
    icmInterceptP intercept,
    icmParamInfoP paramInfo
);

/// This API is deprecated. Please refer to the documentation
/// Return the next bus port description
/// @return Pointer to bus port info.
/// @param mmc     MMC object.
/// @param busPort Handle to previous bus port descriptor or null to start.

icmBusPortInfoP icmGetNextMMCBusPortInfo (
    icmMmcP         mmc,
    icmBusPortInfoP busPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the next parameter description
/// @return Pointer to parameter info.
/// @param mmc       MMC object.
/// @param paramInfo Handle to previous parameter or null to begin.

icmParamInfoP icmGetNextMMCParamInfo (
    icmMmcP       mmc,
    icmParamInfoP paramInfo
);

/// This API is deprecated. Please refer to the documentation
/// Returns the next processor mode description, given the previous description.
/// Pass NULL to get the first description.
/// @return Next mode description
/// @param processor Processor object.
/// @param previous  Previous mode description, or null to start off.

icmModeInfoP icmGetNextMode (
    icmProcessorP processor,
    icmModeInfoP  previous
);

/// This API is deprecated. Please refer to the documentation
/// Return the next bus port description
/// @return Pointer to bus port info.
/// @param pse     PSE object.
/// @param busPort Handle to previous bus port descriptor or null to start.

icmBusPortInfoP icmGetNextPSEBusPortInfo (
    icmPseP         pse,
    icmBusPortInfoP busPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the next bus port description
/// @return Pointer to net port info.
/// @param pse     PSE object.
/// @param netPort Handle to previous net port descriptor or null to start.

icmNetPortInfoP icmGetNextPSENetPortInfo (
    icmPseP         pse,
    icmNetPortInfoP netPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the next bus port description
/// @return Pointer to net port info.
/// @param pse     PSE object.
/// @param netPort Handle to previous packetnet port or null to start.

icmPacketnetPortP icmGetNextPSEPacketnetPort (
    icmPseP           pse,
    icmPacketnetPortP netPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the next parameter description
/// @return Pointer to parameter info.
/// @param pse       PSE object.
/// @param paramInfo Handle to previous parameter or null to begin.

icmParamInfoP icmGetNextPSEParamInfo (
    icmPseP       pse,
    icmParamInfoP paramInfo
);

/// This API is deprecated. Please refer to the documentation
/// Return the next enum value of a parameter descriptor
/// @return The enum
/// @param paramInfo Handle to parameter.
/// @param e         Handle to current enum, or null to begin.

icmParamEnumP icmGetNextParamEnum (
    icmParamInfoP paramInfo,
    icmParamEnumP e
);

/// This API is deprecated. Please refer to the documentation
/// Return the next bus port description.
/// @return The next bus port descriptor.
/// @param processor Processor object.
/// @param busPort   Handle to previous bus port descriptor or null to start.

icmBusPortInfoP icmGetNextProcessorBusPortInfo (
    icmProcessorP   processor,
    icmBusPortInfoP busPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the next FIFO port description.
/// @return The next FIFO port descriptor.
/// @param processor Processor object.
/// @param fifoPort  Handle to previous FIFO port descriptor or null to
///                  begin.

icmFifoPortInfoP icmGetNextProcessorFifoPortInfo (
    icmProcessorP    processor,
    icmFifoPortInfoP fifoPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the next net port description.
/// @return The next net port descriptor.
/// @param processor Processor object.
/// @param netPort   Handle to previous net port descriptor or null to begin.

icmNetPortInfoP icmGetNextProcessorNetPortInfo (
    icmProcessorP   processor,
    icmNetPortInfoP netPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the next parameter description.
/// @return The next parameter.
/// @param processor Processor object.
/// @param paramInfo Handle to previous parameter or null to begin.

icmParamInfoP icmGetNextProcessorParamInfo (
    icmProcessorP processor,
    icmParamInfoP paramInfo
);

/// This API is deprecated. Please refer to the documentation
/// Returns the next processor register description, given the previous
/// description. Pass NULL to get the first register description.
/// @return Next register object.
/// @param processor Processor object.
/// @param previous  Previous register object, or null to start off.

icmRegInfoP icmGetNextReg (
    icmProcessorP processor,
    icmRegInfoP   previous
);

/// This API is deprecated. Please refer to the documentation
/// Returns the next processor register group description, given the previous
/// description. Pass NULL to get the first register description.
/// @return Next register group object.
/// @param processor Processor object.
/// @param previous  Previous register group object, or null to start off.

icmRegGroupP icmGetNextRegGroup (
    icmProcessorP processor,
    icmRegGroupP  previous
);

/// This API is deprecated. Please refer to the documentation
/// Returns the next processor register description in the passed group, given
/// the previous description. Pass NULL to get the first register description.
/// @return Next register object.
/// @param processor Processor object.
/// @param group     Group object.
/// @param previous  Previous register object, or null to start off.

icmRegInfoP icmGetNextRegInGroup (
    icmProcessorP processor,
    icmRegGroupP  group,
    icmRegInfoP   previous
);

/// This API is deprecated. Please refer to the documentation
/// Return the next triggered watchpoint object that has not been reset.
/// @return Next triggered watchpoint

icmWatchPointP icmGetNextTriggeredWatchPoint (void);

/// This API is deprecated. Please refer to the documentation
/// Get the processor program counter
/// @return Value of the PC. This function is similar to icmReadReg, but does
///         not need to know the name of the PC.
/// @param processor Processor object.

Addr icmGetPC (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// For processors without delay slots, or for a non-delay-slot instruction of a
/// processor with delay slots, return the processor program counter and set
/// 'delaySlotOffset' to zero. For a delay slot instruction, return the program
/// counter of the preceding jump instruction and set 'delaySlotOffset' to the
/// offset in bytes of the delay slot instruction.
/// @return Processor program counter
/// @param processor       Processor object.
/// @param delaySlotOffset Set to offset (in bytes) of the delay slot
///                        instruction

Addr icmGetPCDS (
    icmProcessorP processor,
    Uns8 *        delaySlotOffset
);

/// This API is deprecated. Please refer to the documentation
/// Return the documentation for this PSE
/// @return The root documentation node
/// @param pse PSE object.

icmDocNodeP icmGetPSEDoc (
    icmPseP pse
);

/// This API is deprecated. Please refer to the documentation
/// Return application-specific handle associated with the PSE
/// @return The user's handle.
/// @param pse PSE object.

void* icmGetPSEHandle (
    icmPseP pse
);

/// This API is deprecated. Please refer to the documentation
/// Return the name of the PSE
/// @return The PSE name (note that this string does not persist).
/// @param pse PSE object.

const char* icmGetPSEName (
    icmPseP pse
);

/// This API is deprecated. Please refer to the documentation
/// Return the current release status of this PSE
/// @return Release status (enumerated type)
/// @param pse PSE object.

icmReleaseStatus icmGetPSEReleaseStatus (
    icmPseP pse
);

/// This API is deprecated. Please refer to the documentation
/// Return true if this model reports that it supports save/restore
/// @return True if supported
/// @param pse PSE object.

Bool icmGetPSESaveRestoreSupported (
    icmPseP pse
);

/// This API is deprecated. Please refer to the documentation
/// Is the PSE visible (models can choose to hide themselves).
/// @return PSE visibility.
/// @param pse PSE object.

icmVisibility icmGetPSEVisibility (
    icmPseP pse
);

/// This API is deprecated. Please refer to the documentation
/// Get the VLNV spec of this PSE.
/// @return Pointer to VLNV Structure.
/// @param pse PSE object.

icmVlnvP icmGetPSEVlnv (
    icmPseP pse
);

/// This API is deprecated. Please refer to the documentation
/// Return the minimum number of bytes allowed on a packetnet.
/// @return The name of the packetnet.
/// @param packetnet The packetnet object.

Uns32 icmGetPacketnetMaxBytes (
    icmPacketnetP packetnet
);

/// This API is deprecated. Please refer to the documentation
/// Return the name of a packetnet.
/// @return The name of the packetnet.
/// @param packetnet The packetnet object.

const char* icmGetPacketnetName (
    icmPacketnetP packetnet
);

/// This API is deprecated. Please refer to the documentation
/// Return the description of a packetnet port, if it exists
/// @return Description string
/// @param netPort Handle to packetnet port.

const char * icmGetPacketnetPortDesc (
    icmPacketnetPortP netPort
);

/// This API is deprecated. Please refer to the documentation
/// Return true if the model reports that this packetnetport must be connected
/// for the model to function
/// @return True if must be connected, false if optional
/// @param netPort Handle to packetnet port.

Bool icmGetPacketnetPortMustBeConnected (
    icmPacketnetPortP netPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the name of a packetnet port
/// @return Name string
/// @param netPort Handle to packetnet port.

const char * icmGetPacketnetPortName (
    icmPacketnetPortP netPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the net connected to this port
/// @return The connected net or null
/// @param netPort Handle to packetnet port.

icmPacketnetP icmGetPacketnetPortNet (
    icmPacketnetPortP netPort
);

/// This API is deprecated. Please refer to the documentation
/// Return the parameter description from the descriptor
/// @return A short description.
/// @param paramInfo Handle to parameter.

const char* icmGetParamDesc (
    icmParamInfoP paramInfo
);

/// This API is deprecated. Please refer to the documentation
/// Return the enum description
/// @return The enumeration description
/// @param e Handle to current enum.

const char* icmGetParamEnumDesc (
    icmParamEnumP e
);

/// This API is deprecated. Please refer to the documentation
/// Return the enum name
/// @return The name of enumeration
/// @param e Handle to current enum.

const char* icmGetParamEnumName (
    icmParamEnumP e
);

/// This API is deprecated. Please refer to the documentation
/// Return the enum value
/// @return The enumeration value
/// @param e Handle to current enum.

Uns32 icmGetParamEnumValue (
    icmParamEnumP e
);

/// This API is deprecated. Please refer to the documentation
/// Return the parameter name from the descriptor
/// @return The parameter name.
/// @param paramInfo Handle to parameter.

const char* icmGetParamName (
    icmParamInfoP paramInfo
);

/// This API is deprecated. Please refer to the documentation
/// Return the parameter type from the descriptor
/// @return The type.
/// @param paramInfo Handle to parameter.

icmParamType icmGetParamType (
    icmParamInfoP paramInfo
);

/// This API is deprecated. Please refer to the documentation
/// Return the parameter type from the descriptor as a string
/// @return The type.
/// @param paramInfo Handle to parameter.

const char* icmGetParamTypeString (
    icmParamInfoP paramInfo
);

/// This API is deprecated. Please refer to the documentation
/// Return the current platform name.
/// @return Name of platform.

const char* icmGetPlatformName (void);

/// This API is deprecated. Please refer to the documentation
/// Return the purpose of this platform
/// @return Platform purpose (enumerated type)

icmPurpose icmGetPlatformPurpose (void);

/// This API is deprecated. Please refer to the documentation
/// Return the current release status of this platform
/// @return Release status (enumerated type)

icmReleaseStatus icmGetPlatformReleaseStatus (void);

/// This API is deprecated. Please refer to the documentation
/// Return the stopReason for previous simulation using icmSimulate or
/// icmSimulatePlatform.
/// @return Reason why the simulation stopped (see icmStopReason enumerated
///         type).

icmStopReason icmGetPlatformStopReason (void);

/// This API is deprecated. Please refer to the documentation
/// True of this processor is an AMP
/// @return True if asymmetric
/// @param processor Processor handle.

Bool icmGetProcessorAMP (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Return the number of instructions and halted instructions executed by the
/// processor
/// @return Number of instructions and halted instructions executed, up to
///         now.
/// @param processor Processor object.

Uns64 icmGetProcessorClocks (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Return the number of instructions and halted instructions to run until this
/// absolute time
/// @return Number of instructions and halted instructions executed, up to
///         now.
/// @param processor Processor object.
/// @param time      Absolute time.

Uns64 icmGetProcessorClocksUntilTime (
    icmProcessorP processor,
    icmTime       time
);

/// This API is deprecated. Please refer to the documentation
/// Return the number of instructions and halted instructions to run until this
/// absolute time
/// @return Number of instructions and halted instructions executed, up to
///         now.
/// @param processor Processor object.
/// @param time      Absolute time.

Uns64 icmGetProcessorClocksUntilTimeDouble (
    icmProcessorP processor,
    double        time
);

/// This API is deprecated. Please refer to the documentation
/// Find the data bus connected to this processor
/// @return The data bus.
/// @param processor The bus object.

icmBusP icmGetProcessorDataBus (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Get the semihost library to be used by default with this processor.
/// @return Pointer to semihost library VLNV structure.
/// @param processor Processor handle.

icmVlnvP icmGetProcessorDefaultSemihost (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Return the cumulative delay for this processor
/// @return cumulative delay for this processor
/// @param processor Processor object.

icmTime icmGetProcessorDelay (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Return a description of this processor in the CPU model.
/// @return Single name indicating this processor's function in the model.
///         e.g. TC, VPE, CPU, CMP
/// @param processor Handle to this processor.

const char* icmGetProcessorDesc (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Get the root document node of this processor.
/// @return Pointer to root document node.
/// @param processor Processor handle.

icmDocNodeP icmGetProcessorDoc (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Get the ELF codes supported by this processor.
/// @return Number of elf codes supported by this processor.
/// @param processor  Processor handle.
/// @param codes      Array of codes to be filled in by this call
/// @param maxCodes   Size of the array to be filled
/// @param defaultElf This is the default processor for this ELF code (no
///                   longer used).

Uns32 icmGetProcessorElfcode (
    icmProcessorP processor,
    Uns32*        codes,
    Uns32         maxCodes,
    Bool*         defaultElf
);

/// This API is deprecated. Please refer to the documentation
/// Get the endian supported by this processor.
/// @return Endian supported by this processor.
/// @param processor Processor handle.

icmEndian icmGetProcessorEndian (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Get the Family name of this processor.
/// @return Family name of this processor or null if not defined.
/// @param processor Processor handle.

const char * icmGetProcessorFamily (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Get any flags required for this GDB.
/// @return GDB Flags.
/// @param processor Processor handle.

const char* icmGetProcessorGdbFlags (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Get the GDB to be used with this processor.
/// @return Path to GDB.
/// @param processor Processor handle.

const char* icmGetProcessorGdbPath (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Get the group name of this processor.
/// @return Group name (more significant) of this processor or null if not
///         defined.
/// @param processor Processor handle.

const char * icmGetProcessorGroupH (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Get the group name of this processor.
/// @return Group name (less significant) of this processor or null if not
///         defined.
/// @param processor Processor handle.

const char * icmGetProcessorGroupL (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Return application-specific handle associated with the processor
/// @return The user-supplied handle.
/// @param processor The processor return by icmNewProcessorWithHandle()

void* icmGetProcessorHandle (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Get the CPU Helper library to be used by the VAP tools with this processor.
/// @return Pointer to helper VLNV structure.
/// @param processor Processor handle.

icmVlnvP icmGetProcessorHelper (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Return the number of instructions executed by the processor
/// @return Number of instructions executed, up to now.
/// @param processor Processor object.

Uns64 icmGetProcessorICount (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Find the instruction bus connected to this processor
/// @return The instruction bus.
/// @param processor The bus object.

icmBusP icmGetProcessorInstructionBus (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Does this processor always require the use of physical addresses?
/// @return True if physical addresses required (legacy feature).
/// @param processor Processor handle.

Bool icmGetProcessorLoadPhysical (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Return the processor name
/// @return Processor name (note that this string does not persist).
/// @param processor Processor object.
/// @param delimiter Use this string to delimit platform hierarchy. The '/'
///                  forward slash is default.

const char* icmGetProcessorName (
    icmProcessorP processor,
    const char*   delimiter
);

/// This API is deprecated. Please refer to the documentation
/// Is this processor qualified to run in QL mode?
/// @return Processor supports QL Mode.
/// @param processor Processor handle.

Bool icmGetProcessorQLQualified (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Return the current release status of this processor
/// @return Release status (enumerated type)
/// @param processor Processor object.

icmReleaseStatus icmGetProcessorReleaseStatus (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Return the processor local view of time (configured MIPS rate * current
/// clocks)
/// @return Implied processor time
/// @param processor Processor object.

icmTime icmGetProcessorTime (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Get the current variant of this processor instance.
/// @return Current variant of this processor or null if not defined.
/// @param processor Processor handle.

const char * icmGetProcessorVariant (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Is the processor visible (models can choose to hide themselves).
/// @return Processor visibility.
/// @param processor Processor object.

icmVisibility icmGetProcessorVisibility (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Get the VLNV spec of this processor.
/// @return Pointer to VLNV structure.
/// @param processor Processor handle.

icmVlnvP icmGetProcessorVlnv (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Search for a register by its index
/// @return The register object
/// @param processor Processor object.
/// @param index     Register index (see VMI API).

icmRegInfoP icmGetRegByIndex (
    icmProcessorP processor,
    Uns32         index
);

/// This API is deprecated. Please refer to the documentation
/// Search for a register by its name
/// @return The register object
/// @param processor Processor object.
/// @param name      Register name.

icmRegInfoP icmGetRegByName (
    icmProcessorP processor,
    const char*   name
);

/// This API is deprecated. Please refer to the documentation
/// Search for a register by its usage
/// @return The register object
/// @param processor Processor object.
/// @param usage     Register usage

icmRegInfoP icmGetRegByUsage (
    icmProcessorP processor,
    icmRegUsage   usage
);

/// This API is deprecated. Please refer to the documentation
/// Search for a register group by its name
/// @return The register group object
/// @param processor Processor object.
/// @param name      Register name.

icmRegGroupP icmGetRegGroupByName (
    icmProcessorP processor,
    const char*   name
);

/// This API is deprecated. Please refer to the documentation
/// Return the name of the register group from the descriptor
/// @return Register name (note that this string does not persist).
/// @param group Handle to register group object.

const char* icmGetRegGroupName (
    icmRegGroupP group
);

/// This API is deprecated. Please refer to the documentation
/// Return the read/write accessibility of the register from the descriptor
/// @return Register accessibility enumerated type.
/// @param regInfo Handle to register object.

icmRegAccess icmGetRegInfoAccess (
    icmRegInfoP regInfo
);

/// This API is deprecated. Please refer to the documentation
/// Return the size of the register from the descriptor
/// @return Register size in bits.
/// @param regInfo Handle to register object.

Uns32 icmGetRegInfoBits (
    icmRegInfoP regInfo
);

/// This API is deprecated. Please refer to the documentation
/// Return the register description
/// @return Short description
/// @param regInfo Handle to register object.

const char * icmGetRegInfoDesc (
    icmRegInfoP regInfo
);

/// This API is deprecated. Please refer to the documentation
/// Return the register GDB index
/// @return Index number.
/// @param regInfo Handle to register object.

Uns32 icmGetRegInfoGdbIndex (
    icmRegInfoP regInfo
);

/// This API is deprecated. Please refer to the documentation
/// Return the register group for the register
/// @return Register group.
/// @param regInfo Handle to register object.

icmRegGroupP icmGetRegInfoGroup (
    icmRegInfoP regInfo
);

/// This API is deprecated. Please refer to the documentation
/// Return the name of the register from the descriptor
/// @return Register name (note that this string does not persist).
/// @param regInfo Handle to register object.

const char* icmGetRegInfoName (
    icmRegInfoP regInfo
);

/// This API is deprecated. Please refer to the documentation
/// Return if the register is read-only (deprecated: use icmGetRegInfoAccess)
/// @return Is read-only.
/// @param regInfo Handle to register object.

Bool icmGetRegInfoReadOnly (
    icmRegInfoP regInfo
);

/// This API is deprecated. Please refer to the documentation
/// Return the type of the register from the descriptor
/// @return Register usage enumerated type.
/// @param regInfo Handle to register object.

icmRegUsage icmGetRegInfoUsage (
    icmRegInfoP regInfo
);

/// This API is deprecated. Please refer to the documentation
/// Return the type of the register, as a string, from the descriptor
/// @return Register usage enumerated type.
/// @param regInfo Handle to register object.

const char* icmGetRegInfoUsageString (
    icmRegInfoP regInfo
);

/// This API is deprecated. Please refer to the documentation
/// Return the first child of the passed SMP processor
/// @return SMP first child.
/// @param processor The processor object.

icmProcessorP icmGetSMPChild (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Return a pointer to processor data. Use instead of casting the
/// vmiProcessorP.
/// @return Return a pointer to the processor data (beginning with registers)
/// @param processor The processor object.

void* icmGetSMPData (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Return the index number of the passed SMP processor
/// @return Unique (within this processor cluster) index number.
/// @param processor The processor object.

Uns32 icmGetSMPIndex (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Return the next sibling of the passed SMP processor
/// @return SMP next sibling.
/// @param processor The processor object.

icmProcessorP icmGetSMPNextSibling (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Return the parent of the passed SMP processor
/// @return SMP parent.
/// @param processor The processor object.

icmProcessorP icmGetSMPParent (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Return the previous sibling of the passed SMP processor
/// @return SMP previous sibling.
/// @param processor The processor object.

icmProcessorP icmGetSMPPrevSibling (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Return the finish status, if simulation was explicitly finished
/// @return Status, or zero if simulation was not explicitly finished.

Int32 icmGetStatus (void);

/// This API is deprecated. Please refer to the documentation
/// Return the reason why simulation stopped when this processor was previously
/// simulated using icmSimulate or icmSimulatePlatform. The stop reason is valid
/// only for leaf level processors or an MT group: processor objects that are
/// containers of independently-executable cores always return a stopReason of
/// ICM_SR_SCHED, because each of the sub-cores may have a different stopReason.
/// @return Reason why the simulation stopped (see icmStopReason enumerated
///         type).
/// @param processor Processor object.

icmStopReason icmGetStopReason (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Synthesize a VLNV path string given the vendor, library, name and version of
/// the library object you wish to load. If models are stored according to
/// Imperas guidelines, this should successfully locate any model. If all
/// arguments are plain strings, constructs a path such as
/// 'vlnvroot/vendor/library/name/version/objtype', otherwise the following
/// rules are used: If vlnvroot is NULL, the default installation path is used.
/// vlnvroot may be a ':' (Linux) or ';' (Windows) separated list of paths. If
/// vendor, library, or name are empty strings (0 is not allowed) or '*', they
/// are treated as wild-cards and all directories are searched. If version is a
/// wild-card, the latest version is taken (note that 1.2.1 is later than 1.2,
/// but FOO is later than both). For success the specification must yield
/// exactly one file. If objType is 'pse', the file pse.pse is used (this is the
/// convention used by Imperas). If objType is 'model' or 'intercept', the file
/// 'model.so' (Linux) or 'model.dll' (Windows) is used. Otherwise, the string
/// is used as is. Note that the name CVS or names that begin with a period are
/// ignored. This function is intended to be used be used by icmNewProcessor,
/// icmNewPSE and icmNewMMC
/// @return Null (reports an error) if no unique file is found, otherwise a
///         file path
/// @param vlnvroot Path or list of paths to root of directory(s) containing
///                 modelsT
/// @param vendor   Vendor directory e.g. yourcompany.com or '*'
/// @param library  Library directory e.g. processor or '*'
/// @param name     Name directory e.g. risc32 or '*'
/// @param version  Version directory e.g. 1.0 or '*'
/// @param objType  Filename in the version directory or 'pse' or 'model'

const char* icmGetVlnvString (
    const char* vlnvroot,
    const char* vendor,
    const char* library,
    const char* name,
    const char* version,
    const char* objType
);

/// This API is deprecated. Please refer to the documentation
/// Return current value for the passed register watchpoint (returns NULL for a
/// memory watchpoint)
/// @return Current value pointer
/// @param watchpoint Watchpoint for which to return current value

void* icmGetWatchPointCurrentValue (
    icmWatchPointP watchpoint
);

/// This API is deprecated. Please refer to the documentation
/// Return the high address bound of the passed watchpoint (returns zero for a
/// register watchpoint)
/// @return Watchpoint high address
/// @param watchpoint Watchpoint for which to return high address

Addr icmGetWatchPointHighAddress (
    icmWatchPointP watchpoint
);

/// This API is deprecated. Please refer to the documentation
/// Return the low address bound of the passed watchpoint (returns zero for a
/// register watchpoint)
/// @return Watchpoint low address
/// @param watchpoint Watchpoint for which to return low address

Addr icmGetWatchPointLowAddress (
    icmWatchPointP watchpoint
);

/// This API is deprecated. Please refer to the documentation
/// Return previous value for the passed register watchpoint (returns NULL for a
/// memory watchpoint)
/// @return Previous value pointer
/// @param watchpoint Watchpoint for which to return previous value

void* icmGetWatchPointPreviousValue (
    icmWatchPointP watchpoint
);

/// This API is deprecated. Please refer to the documentation
/// Return register for the passed watchpoint (returns NULL for a memory
/// watchpoint)
/// @return Watchpoint register
/// @param watchpoint Watchpoint for which to return register

icmRegInfoP icmGetWatchPointRegister (
    icmWatchPointP watchpoint
);

/// This API is deprecated. Please refer to the documentation
/// Return processor that triggered a watchpoint
/// @return The triggering processor
/// @param watchpoint Watchpoint for which to return processor

icmProcessorP icmGetWatchPointTriggeredBy (
    icmWatchPointP watchpoint
);

/// This API is deprecated. Please refer to the documentation
/// Return the type of the passed watchpoint object
/// @return Watchpoint type
/// @param watchpoint Watchpoint to query

icmWatchpointType icmGetWatchPointType (
    icmWatchPointP watchpoint
);

/// This API is deprecated. Please refer to the documentation
/// Return userData recorded with watchpoint
/// @return User data pointer
/// @param watchpoint Watchpoint for which to return userData

void* icmGetWatchPointUserData (
    icmWatchPointP watchpoint
);

/// This API is deprecated. Please refer to the documentation
/// Halt execution of the current processor and return immediately from
/// icmSimulate with icmStopReason ICM_SR_HALT (typically used within
/// icmMemReadFn or icmMemWriteFn callback).
/// @param processor The processor that was running.

void icmHalt (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Turn off messages with an ident beginning with the passed string
/// @param ident The start of the ident to be turned off. e.g. ICM_ turns off
///              messages beginning ICM_

void icmIgnoreMessage (
    const char* ident
);

/// This API is deprecated. Please refer to the documentation
/// When called in a memory read callback, indicates whether the current context
/// is a fetch (True) or a load (False) (deprecated - use isFetch argument to
/// icmMemReadFn instead)
/// @return Whether context is a fetch
/// @param processor The current processor.

Bool icmInFetchContext (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Initialize ICM package - call this before any other ICM functions. Please
/// use the macro icmInit().
/// @param versionString ICM Version. Checked before ICM is allowed to run.
/// @param simAttrs      Bit mask of simulation switches.
/// @param debugProtocol Specify debug protocol (or null if no debug)
/// @param dbgPort       Optional host port to connect to debug port.

void icmInitInternal (
    const char*  versionString,
    icmInitAttrs simAttrs,
    const char*  debugProtocol,
    Uns32        dbgPort
);

/// This API is deprecated. Please refer to the documentation
/// Initialize ICM package and create a named platform. Call this before any
/// other ICM functions.
/// @param versionString ICM Version. Checked before ICM is allowed to run.
///                      Use the macro ICM_VERSION
/// @param simAttrs      Bit mask of simulation switches.
/// @param debugProtocol Specify debug protocol (or null if no debug)
/// @param dbgPort       Optional host port to connect to debug port.
/// @param platformName  Platform name, appearing in hierarchical component
///                      names.

void icmInitPlatform (
    const char*  versionString,
    icmInitAttrs simAttrs,
    const char*  debugProtocol,
    Uns32        dbgPort,
    const char*  platformName
);

/// This API is deprecated. Please refer to the documentation
/// Install a new object file reader.
/// @return Returns non-zero if successful, zero otherwise.
/// @param filename Name of the loader file.

int icmInstallObjectReader (
    const char* filename
);

/// This API is deprecated. Please refer to the documentation
/// This and icmInterruptRSP are the only ICM functions that are safe to call in
/// a signal handler. This function causes any currently-executing simulation
/// thread to stop as soon as possible in a safe state so that other ICM
/// functions can be called. The stop is signalled by a return code stop reason
/// of ICM_SR_INTERRUPT. The thread stops just before the next code block is
/// executed; typically, this will be a few instructions on from the
/// icmInterrupt call. It is safe to use icmInterrupt in non-signal-handler
/// contexts (e.g. memory callbacks) but you may want to consider the use of
/// icmYield in this context.

void icmInterrupt (void);

/// This API is deprecated. Please refer to the documentation
/// This and icmInterrupt are the only ICM functions that are safe to call in a
/// signal handler. This function causes simulation to stop and return control
/// to a debugger connected through RSP. If no debugger is attached, simulation
/// continues.

void icmInterruptRSP (void);

/// This API is deprecated. Please refer to the documentation
/// Is the processor currently frozen?
/// @return Whether processor was frozen
/// @param processor The processor that was running.

Bool icmIsFrozen (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Apply the callback to all children of the processor object
/// @param processor The processor object.
/// @param iterCB    The function to call.
/// @param userData  Passed to the function.

void icmIterAllChildren (
    icmProcessorP    processor,
    icmSMPIteratorFn iterCB,
    void*            userData
);

/// This API is deprecated. Please refer to the documentation
/// Apply the callback to all descendants of the processor object
/// @param processor The processor object.
/// @param iterCB    The function to call.
/// @param userData  Passed to the function.

void icmIterAllDescendants (
    icmProcessorP    processor,
    icmSMPIteratorFn iterCB,
    void*            userData
);

/// This API is deprecated. Please refer to the documentation
/// Apply the callback to the processor and all its descendants
/// @param processor The processor object.
/// @param iterCB    The function to call.
/// @param userData  Passed to the function.

void icmIterAllProcessors (
    icmProcessorP    processor,
    icmSMPIteratorFn iterCB,
    void*            userData
);

/// This API is deprecated. Please refer to the documentation
/// Returns the last message to occur
/// @return String or empty string

const char* icmLastMessage (void);

/// This API is deprecated. Please refer to the documentation
/// Load an object directly onto a bus (actually, the memory on the bus)
/// @return A Handle to the objectFile.
/// @param bus        Bus object.
/// @param objectFile Path to the object file (must be a recognized format).
/// @param attrs      Attributes to control how a file is loaded
/// @param verbose    Output information about the loaded object and its
///                   sections.

icmImagefileP icmLoadBus (
    icmBusP        bus,
    const char*    objectFile,
    icmLoaderAttrs attrs,
    Bool           verbose
);

/// This API is deprecated. Please refer to the documentation
/// This hook function is called just after each model is loaded - set a
/// breakpoint on this to get control just after each model is loaded (allowing
/// further breakpoints to be set in model code if required).
/// @param modelFile   The name of model file being loaded
/// @param modelSymbol The entry symbol in the model being loaded

void icmLoadModelHook (
    const char* modelFile,
    const char* modelSymbol
);

/// This API is deprecated. Please refer to the documentation
/// Load the processor memory with an object file.
/// @return A Handle to the objectFile.
/// @param processor  Load into this processor's code address space.
/// @param objectFile Path to the object file (must be a recognized format).
/// @param attrs      Attributes to control how a file is loaded
/// @param verbose    Output information about the loaded object and its
///                   sections.
/// @param useEntry   Sets the PC of the related processor to the start
///                   address in the object file.

icmImagefileP icmLoadProcessorMemory (
    icmProcessorP  processor,
    const char*    objectFile,
    icmLoaderAttrs attrs,
    Bool           verbose,
    Bool           useEntry
);

/// This API is deprecated. Please refer to the documentation
/// Load with offset the processor memory with an object file.
/// @return A Handle to the objectFile.
/// @param processor  Load into this processor's code address space.
/// @param objectFile Path to the object file (must be a recognized format).
/// @param attrs      Attributes to control how a file is loaded
/// @param offset     Offset applied to all addresses

icmImagefileP icmLoadProcessorMemoryOffset (
    icmProcessorP  processor,
    const char*    objectFile,
    icmLoaderAttrs attrs,
    Addr           offset
);

/// This API is deprecated. Please refer to the documentation
/// Load the symbols from an object file.
/// @return True if successful.
/// @param processor    Load into this processor's code address space.
/// @param objectFile   Path to the object file (must be a recognized
///                     format).
/// @param loadPhysical If true, physical addresses from the ELF file are
///                     used; otherwise, virtual.

Bool icmLoadSymbols (
    icmProcessorP processor,
    const char*   objectFile,
    Bool          loadPhysical
);

/// This API is deprecated. Please refer to the documentation
/// Restore the state of the given MMC object
/// @return Success or failure.
/// @param mmc      The connection object to restore
/// @param cb       The function used to restore data
/// @param userData User context, passed back in the callback

icmSaveRestoreStatus icmMMCRestoreState (
    icmMmcP      mmc,
    icmRestoreFn cb,
    void *       userData
);

/// This API is deprecated. Please refer to the documentation
/// Restore the state of the given MMC object from a file in default format
/// @return Success or failure.
/// @param mmc  The connection object to restore
/// @param file File name from which to restore

icmSaveRestoreStatus icmMMCRestoreStateFile (
    icmMmcP      mmc,
    const char * file
);

/// This API is deprecated. Please refer to the documentation
/// Save the state of the given MMC object
/// @return Success or failure.
/// @param mmc      The MMC to save
/// @param cb       The function used to save data
/// @param userData User context, passed back in the callback

icmSaveRestoreStatus icmMMCSaveState (
    icmMmcP   mmc,
    icmSaveFn cb,
    void *    userData
);

/// This API is deprecated. Please refer to the documentation
/// Save the state of the given MMC object to a file in default format
/// @return Success or failure.
/// @param mmc  The connection object to save
/// @param file File name to which to save

icmSaveRestoreStatus icmMMCSaveStateFile (
    icmMmcP      mmc,
    const char * file
);

/// This API is deprecated. Please refer to the documentation
/// Returns the number of bits in a memory mapped register
/// @return Number of bits in the register (will be a multiple of 8)
/// @param info Register info

Uns32 icmMMRegBits (
    icmMMRegInfoP info
);

/// This API is deprecated. Please refer to the documentation
/// Returns the memory mapped register short description
/// @return A short description of the memory mapped register
/// @param info Register info

const char * icmMMRegDescription (
    icmMMRegInfoP info
);

/// This API is deprecated. Please refer to the documentation
/// Returns the memory mapped register name
/// @return Memory mapped register name
/// @param info Register info

const char * icmMMRegName (
    icmMMRegInfoP info
);

/// This API is deprecated. Please refer to the documentation
/// Returns the offset in bytes from the base of the bus port
/// @return Offset in bytes from the base of the bus port
/// @param info Register info

Addr icmMMRegOffset (
    icmMMRegInfoP info
);

/// This API is deprecated. Please refer to the documentation
/// Map the passed bus address range using the callbacks
/// @param bus      The bus object.
/// @param portName Unique name of port created by this call.
/// @param priv     Access permission on this memory (see icmPriv).
/// @param lowAddr  Low end of range.
/// @param highAddr High end of range.
/// @param readCB   If specified, will be called for each read.
/// @param writeCB  If specified, will be called for each write.
/// @param userData Passed to each read or write callback.

void icmMapExternalMemory (
    icmBusP       bus,
    const char*   portName,
    icmPriv       priv,
    Addr          lowAddr,
    Addr          highAddr,
    icmMemReadFn  readCB,
    icmMemWriteFn writeCB,
    void*         userData
);

/// This API is deprecated. Please refer to the documentation
/// Map the passed bus address range using the callbacks or locally allocated
/// memory if a callback is absent
/// @param bus      The bus object.
/// @param portName Unique name of port created by this call.
/// @param priv     Access permission on this memory (see icmPriv).
/// @param lowAddr  Low end of range.
/// @param highAddr High end of range.
/// @param readCB   If specified, will be called for each read.
/// @param writeCB  If specified, will be called for each write.
/// @param memory   Pointer to space allocated by user (Must be at least as
///                 large as 1+hiAddr-lowAddr)
/// @param userData Passed to each read or write callback.

void icmMapExternalNativeMemory (
    icmBusP       bus,
    const char*   portName,
    icmPriv       priv,
    Addr          lowAddr,
    Addr          highAddr,
    icmMemReadFn  readCB,
    icmMemWriteFn writeCB,
    void*         memory,
    void*         userData
);

/// This API is deprecated. Please refer to the documentation
/// Map the passed bus address range using a local anonymous memory
/// @param bus      The bus object.
/// @param portName Unique name of port created by this call.
/// @param priv     Access permission on this memory (see icmPriv).
/// @param lowAddr  Low end of range.
/// @param highAddr High end of range.

void icmMapLocalMemory (
    icmBusP     bus,
    const char* portName,
    icmPriv     priv,
    Addr        lowAddr,
    Addr        highAddr
);

/// This API is deprecated. Please refer to the documentation
/// Map locally allocated memory to a bus.
/// @param bus     Map the memory onto this bus.
/// @param priv    Access permission on this memory (see icmPriv).
/// @param lowAddr Low extent of the memory
/// @param hiAddr  High extent of the memory
/// @param memory  Pointer to space allocated by user (Must be at least as
///                large as 1+hiAddr-lowAddr)

void icmMapNativeMemory (
    icmBusP bus,
    icmPriv priv,
    Addr    lowAddr,
    Addr    hiAddr,
    void*   memory
);

/// This API is deprecated. Please refer to the documentation
/// Restore the state of the given memory
/// @return Success or failure.
/// @param memory   The memory to restore
/// @param cb       The function used to restore data
/// @param userData User context, passed back in the callback

icmSaveRestoreStatus icmMemoryRestoreState (
    icmMemoryP   memory,
    icmRestoreFn cb,
    void *       userData
);

/// This API is deprecated. Please refer to the documentation
/// Restore the state of the given memory from a file in default format
/// @return Success or failure.
/// @param memory The memory to restore
/// @param file   File name from which to restore

icmSaveRestoreStatus icmMemoryRestoreStateFile (
    icmMemoryP   memory,
    const char * file
);

/// This API is deprecated. Please refer to the documentation
/// Save the state of the given memory
/// @return Success or failure.
/// @param memory   The memory to save
/// @param cb       The function used to save data
/// @param userData User context, passed back in the callback

icmSaveRestoreStatus icmMemorySaveState (
    icmMemoryP memory,
    icmSaveFn  cb,
    void *     userData
);

/// This API is deprecated. Please refer to the documentation
/// Save the state of the given memory to a file in default format
/// @return Success or failure.
/// @param memory The memory to save
/// @param file   File name to which to save

icmSaveRestoreStatus icmMemorySaveStateFile (
    icmMemoryP   memory,
    const char * file
);

/// This API is deprecated. Please refer to the documentation
/// Send formatted text to the simulator output stream. The text is prefixed
/// with the severity, the prefix code and the model instance name. Use this for
/// user-level diagnostics.
/// @param severity I=Info W=Warning E=Error F=Fatal (aborts the simulator)
/// @param ident    A short code to identify this message. This makes the
///                 message easy to extract using text tools.
/// @param fmt      Printf format string (see gnu printf for details)
/// @param ...      This is a vararg function

void icmMessage (
    const char* severity,
    const char* ident,
    const char* fmt,
                ...
) __attribute__(( format (printf, 3,4)));

/// This API is deprecated. Please refer to the documentation
/// Use this to respond to the simulator -verbose flag
/// @return True if platform should be verbose

Bool icmMessageQuiet (void);

/// This API is deprecated. Please refer to the documentation
/// Turn warning messages on/off
/// @return old value
/// @param quiet Warning messages on

Bool icmMessageSetNoWarn (
    Bool quiet
);

/// This API is deprecated. Please refer to the documentation
/// Turn Info messages on/off
/// @return old value
/// @param quiet Info messages on

Bool icmMessageSetQuiet (
    Bool quiet
);

/// This API is deprecated. Please refer to the documentation
/// Use this to respond to the simulator -verbose flag
/// @return True if platform should be verbose

Bool icmMessageVerbose (void);

/// This API is deprecated. Please refer to the documentation
/// Return netPort direction
/// @return Direction
/// @param netPort The net port.

icmDirection icmNetPortDirection (
    icmNetPortP netPort
);

/// This API is deprecated. Please refer to the documentation
/// Return netPort name
/// @return Name of net port (note that this string does not persist).
/// @param netPort The net port.

const char* icmNetPortName (
    icmNetPortP netPort
);

/// This API is deprecated. Please refer to the documentation
/// Restore the state of the given net
/// @return Success or failure.
/// @param net      The net to restore
/// @param cb       The function used to restore data
/// @param userData User context, passed back in the callback

icmSaveRestoreStatus icmNetRestoreState (
    icmNetP      net,
    icmRestoreFn cb,
    void *       userData
);

/// This API is deprecated. Please refer to the documentation
/// Restore the state of the given net from a file in default format
/// @return Success or failure.
/// @param net  The net to restore
/// @param file File name from which to restore

icmSaveRestoreStatus icmNetRestoreStateFile (
    icmNetP      net,
    const char * file
);

/// This API is deprecated. Please refer to the documentation
/// Save the state of the given net
/// @return Success or failure.
/// @param net      The net to save
/// @param cb       The function used to save data
/// @param userData User context, passed back in the callback

icmSaveRestoreStatus icmNetSaveState (
    icmNetP   net,
    icmSaveFn cb,
    void *    userData
);

/// This API is deprecated. Please refer to the documentation
/// Save the state of the given net to a file in default format
/// @return Success or failure.
/// @param net  The net to save
/// @param file File name to which to save

icmSaveRestoreStatus icmNetSaveStateFile (
    icmNetP      net,
    const char * file
);

/// This API is deprecated. Please refer to the documentation
/// Create a new attributes list
/// @return New user-defined attributes list.

icmAttrListP icmNewAttrList (void);

/// This API is deprecated. Please refer to the documentation
/// Create a new bus object.
/// @return New bus object.
/// @param name        Unique name for this bus.
/// @param addressBits Width of the bus in bits.

icmBusP icmNewBus (
    const char* name,
    Uns8        addressBits
);

/// This API is deprecated. Please refer to the documentation
/// Create a bus bridge between the two buses so that the region starting at
/// lowAddrSlave on the slave bus is visible starting at lowAddrMaster in the
/// master bus.
/// @return Handle to new bridge.
/// @param slave          Bus on which the bridge receives an access.
/// @param master         Bus on which the bridge initiates an access.
/// @param bridgeName     Name of the new bridge
/// @param slavePortName  Name of the new bridge bus slave port
/// @param masterPortName Name of the new bridge bus master port
/// @param lowAddrMaster  The lowest address generated by the master port
/// @param highAddrMaster The highest address generated by the master port.
/// @param lowAddrSlave   The lowest address decoded by the slave port.

icmBusBridgeP icmNewBusBridge (
    icmBusP     slave,
    icmBusP     master,
    const char* bridgeName,
    const char* slavePortName,
    const char* masterPortName,
    Addr        lowAddrMaster,
    Addr        highAddrMaster,
    Addr        lowAddrSlave
);

/// This API is deprecated. Please refer to the documentation
/// Create a new bus object.
/// @return New bus object.
/// @param name        Unique name for this bus.
/// @param addressBits Width of the bus in bits.
/// @param handle      User-defined handle. The handle can be found later
///                    using icmGetBusHandle().

icmBusP icmNewBusWithHandle (
    const char* name,
    Uns8        addressBits,
    void*       handle
);

/// This API is deprecated. Please refer to the documentation
/// Create a FIFO object.
/// @return New FIFO object.
/// @param name  Name of the new FIFO object.
/// @param width Width of one input word in bits.
/// @param depth Number of words which can be held before overflow occurs.

icmConnP icmNewFifo (
    const char* name,
    Uns32       width,
    Uns32       depth
);

/// This API is deprecated. Please refer to the documentation
/// Create a FIFO object.
/// @return New FIFO object.
/// @param name   Name of the new FIFO object.
/// @param width  Width of one input word in bits.
/// @param depth  Number of words which can be held before overflow occurs.
/// @param handle User's handle (which can be found later using
///               icmGetFifoHandle()).

icmConnP icmNewFifoWithHandle (
    const char* name,
    Uns32       width,
    Uns32       depth,
    void*       handle
);

/// This API is deprecated. Please refer to the documentation
/// Create a new MMC instance running the passed shared object
/// @return MMC object.
/// @param name         New unique name for this MMC instance.
/// @param modelFile    Path to the MMC model file (see icmGetVlnvString()).
/// @param modelSymbol  Not unused: Set to null
/// @param initialAttrs List of user defined attributes created using
///                     icmNewAttrList() to be used by this model instance.
/// @param handle       Used by the client.
/// @param transparent  True if this MMC does not affect the bus traffic,
///                     only monitors it.

icmMmcP icmNewMMC (
    const char*  name,
    const char*  modelFile,
    const char*  modelSymbol,
    icmAttrListP initialAttrs,
    void*        handle,
    Bool         transparent
);

/// This API is deprecated. Please refer to the documentation
/// Create a memory object
/// @return New memory object.
/// @param name     Unique name for the memory.
/// @param priv     See icmPriv enumeration.
/// @param highAddr Highest byte address (lowest is zero).

icmMemoryP icmNewMemory (
    const char* name,
    icmPriv     priv,
    Addr        highAddr
);

/// This API is deprecated. Please refer to the documentation
/// Create a memory object, with user-defined handle.
/// @return New memory object.
/// @param name     Unique name for the memory.
/// @param priv     See icmPriv enumeration.
/// @param highAddr Highest byte address (lowest is zero).
/// @param handle   User's handle.

icmMemoryP icmNewMemoryWithHandle (
    const char* name,
    icmPriv     priv,
    Addr        highAddr,
    void*       handle
);

/// This API is deprecated. Please refer to the documentation
/// Create a net object
/// @return New net object handle.
/// @param name Name of new net.

icmNetP icmNewNet (
    const char* name
);

/// This API is deprecated. Please refer to the documentation
/// Create a net object
/// @return New net object handle.
/// @param name   Name of new net.
/// @param handle User's handle (which can be found later using
///               icmGetNetHandle()).

icmNetP icmNewNetWithHandle (
    const char* name,
    void*       handle
);

/// This API is deprecated. Please refer to the documentation
/// Create a new PSE instance.
/// @return New PSE object.
/// @param name           New unique name for this PSE instance
/// @param modelFile      Path to PSE executable file (see
///                       icmGetVlnvString()).
/// @param initialAttrs   List of user-defined attributes for this instance.
///                       In the PSE, routines including bhmStringAttribute
///                       can be used to retrieve the attributes.
/// @param semiHostFile   Path to an extension library for this PSE. This
///                       argument is not normally required; a PSE will load
///                       its own extension if required.
/// @param semiHostSymbol Not used. Set to null

icmPseP icmNewPSE (
    const char*  name,
    const char*  modelFile,
    icmAttrListP initialAttrs,
    const char*  semiHostFile,
    const char*  semiHostSymbol
);

/// This API is deprecated. Please refer to the documentation
/// Create a new PSE as above, associating the passed handle with the
/// newly-created PSE.
/// @return New PSE object.
/// @param name           New unique name for this PSE instance
/// @param modelFile      Path to PSE executable file.
/// @param initialAttrs   List of user-defined attributes for this instance.
///                       In the PSE, routines including bhmStringAttribute
///                       can be used to retrieve the attributes.
/// @param semiHostFile   Path to an extension library for this PSE. This
///                       argument is not normally required; a PSE will load
///                       its own extension if required.
/// @param semiHostSymbol Not used. Set to null.
/// @param handle         The handle which can be found later using
///                       icmGetPSEHandle().

icmPseP icmNewPSEWithHandle (
    const char*  name,
    const char*  modelFile,
    icmAttrListP initialAttrs,
    const char*  semiHostFile,
    const char*  semiHostSymbol,
    void*        handle
);

/// This API is deprecated. Please refer to the documentation
/// Create a packetnet
/// @return Handle to the new packetnet
/// @param name Name of the new packetnet.

icmPacketnetP icmNewPacketnet (
    const char * name
);

/// This API is deprecated. Please refer to the documentation
/// Create a new processor instance.
/// @return New processor object.
/// @param name           Name of new processor (string will be copied).
/// @param type           Type of new processor (string will be copied).
///                       Corresponds to the N in the VLNV
/// @param cpuId          A unique number in the platform for this CPU.
/// @param cpuFlags       Debug flags passed to the model.
/// @param addressBits    Width of the address buses (in bits).
/// @param modelFile      Path to the file containing the model's shared
///                       object (see icmGetVlnvString())
/// @param modelSymbol    Not used. Set to null.
/// @param procAttrs      Bit-mask of values from ICM_ATTR_... macros
/// @param userAttrs      List of user defined attributes, constructed using
///                       icmNewAttrList() etc.
/// @param semiHostFile   Path to first extension library or null
/// @param semiHostSymbol Not used. Set to null.

icmProcessorP icmNewProcessor (
    const char*     name,
    const char*     type,
    Uns32           cpuId,
    Uns32           cpuFlags,
    Uns8            addressBits,
    const char*     modelFile,
    const char*     modelSymbol,
    icmNewProcAttrs procAttrs,
    icmAttrListP    userAttrs,
    const char*     semiHostFile,
    const char*     semiHostSymbol
);

/// This API is deprecated. Please refer to the documentation
/// INTERNAL
/// @return The new processor handle.
/// @param name         Instance name.
/// @param type         Processor type. Should match the Name in the VLNV.
/// @param cpuId        A unique number in the platform for this CPU.
/// @param cpuFlags     Debug flags passed to the model.
/// @param addressBits  Width of the address buses (in bits).
/// @param iasAttrs     Pointer to attributes table.
/// @param vmiosAttrs   Pointer to attributes table of intercept library.
/// @param procAttrs    List of user-defined attributes for the model.
/// @param initialAttrs List of user-defined attributes
/// @param stubs        VMI stubs

icmProcessorP icmNewProcessorIASAttrs (
    const char*     name,
    const char*     type,
    Uns32           cpuId,
    Uns32           cpuFlags,
    Uns8            addressBits,
    const void*     iasAttrs,
    void*           vmiosAttrs,
    icmNewProcAttrs procAttrs,
    icmAttrListP    initialAttrs,
    void*           stubs
);

/// This API is deprecated. Please refer to the documentation
/// Create a new processor instance, associating the passed handle with the
/// newly created processor.
/// @return New processor object.
/// @param name           Name of new processor (string will be copied).
/// @param type           Type of new processor (string will be copied).
///                       Corresponds to the N in the VLNV
/// @param cpuId          A unique number in the platform for this CPU.
/// @param cpuFlags       Debug flags passed to the model.
/// @param addressBits    Width of the address buses (in bits)
/// @param modelFile      Path to the file containing the model's shared
///                       object(see icmGetVlnvString())
/// @param modelSymbol    Not used. Set to null.
/// @param procAttrs      Bit-mask of values from ICM_ATTR_... macros
/// @param userAttrs      List of user defined attributes, constructed using
///                       icmNewAttrList() etc.
/// @param semiHostFile   Path to first extension library or null
/// @param semiHostSymbol Not used. Set to null.
/// @param handle         User's handle which can be retrieved using
///                       icmGetProcessorHandle().

icmProcessorP icmNewProcessorWithHandle (
    const char*     name,
    const char*     type,
    Uns32           cpuId,
    Uns32           cpuFlags,
    Uns8            addressBits,
    const char*     modelFile,
    const char*     modelSymbol,
    icmNewProcAttrs procAttrs,
    icmAttrListP    userAttrs,
    const char*     semiHostFile,
    const char*     semiHostSymbol,
    void*           handle
);

/// This API is deprecated. Please refer to the documentation
/// Returns the next memory mapped register information given the previous. Pass
/// NULL to get the first register from a bus port.
/// @return Next register object.
/// @param busPort  Bus Port.
/// @param previous Previous register object, or null to start.

icmMMRegInfoP icmNextBusPortMMRegInfo (
    icmBusPortInfoP busPort,
    icmMMRegInfoP   previous
);

/// This API is deprecated. Please refer to the documentation
/// Get the next intercept shared object on a processor.
/// @return Next intercept object.
/// @param processor Processor holding the object.
/// @param previous  Previous intercept or null.

icmInterceptP icmNextInterceptObject (
    icmProcessorP processor,
    icmInterceptP previous
);

/// This API is deprecated. Please refer to the documentation
/// Iterate each of the MMCs in a platform.
/// @return Next MMC or null to begin
/// @param mmc The current MMC or null if starting.

icmMmcP icmNextMmc (
    icmMmcP mmc
);

/// This API is deprecated. Please refer to the documentation
/// Iterate each of the processors in a platform.
/// @return Next processor or null to begin
/// @param processor The current processor or null if starting.

icmProcessorP icmNextProcessor (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Get next netPort of a processor
/// @return Next port or null if last one.
/// @param processor The processor.
/// @param current   Current port or null if starting.

icmNetPortP icmNextProcessorNetPort (
    icmProcessorP processor,
    icmNetPortP   current
);

/// This API is deprecated. Please refer to the documentation
/// Iterate each of the PSEs in a platform.
/// @return The next PSE (or null if no more).
/// @param pse The current PSE or null if starting.

icmPseP icmNextPse (
    icmPseP pse
);

/// This API is deprecated. Please refer to the documentation
/// Get next netPort of a PSE
/// @return Next port or null if last one.
/// @param pse     The PSE.
/// @param current Current port or null if starting.

icmNetPortP icmNextPseNetPort (
    icmPseP     pse,
    icmNetPortP current
);

/// This API is deprecated. Please refer to the documentation
/// Return the state of the --nobanner flag
/// @return Returns true if no banner should be printed

Bool icmNoBanner (void);

/// This API is deprecated. Please refer to the documentation
/// Override the value of a model attribute. This function can be called before
/// the platform is constructed.
/// @return True if parsed without errors
/// @param target Full path to attribute including platform, instance and
///               attribute names
/// @param value  New value as a string which will be converted to the
///               correct type.

Bool icmOverride (
    const char* target,
    const char* value
);

/// This API is deprecated. Please refer to the documentation
/// Return the default value of a boolean parameter
/// @return The default value
/// @param paramInfo Handle to the parameter

Bool icmParamBoolDefaultValue (
    icmParamInfoP paramInfo
);

/// This API is deprecated. Please refer to the documentation
/// Return the min, max and default values of a double the parameter
/// @return True if the parameter is of the correct type
/// @param paramInfo Handle to the parameter
/// @param min       The minimum value (output)
/// @param max       The maximum value (output)
/// @param dflt      The default value (output)

Bool icmParamDoubleLimits (
    icmParamInfoP paramInfo,
    double*       min,
    double*       max,
    double*       dflt
);

/// This API is deprecated. Please refer to the documentation
/// Return the min, max and default values of an Int32 the parameter
/// @return True if the parameter is of the correct type
/// @param paramInfo Handle to the parameter
/// @param min       The minimum value (output)
/// @param max       The maximum value (output)
/// @param dflt      The default value (output)

Bool icmParamInt32Limits (
    icmParamInfoP paramInfo,
    Int32*        min,
    Int32*        max,
    Int32*        dflt
);

/// This API is deprecated. Please refer to the documentation
/// Return the min, max and default values of an Int64 the parameter
/// @return True if the parameter is of the correct type
/// @param paramInfo Handle to the parameter
/// @param min       The minimum value (output)
/// @param max       The maximum value (output)
/// @param dflt      The default value (output)

Bool icmParamInt64Limits (
    icmParamInfoP paramInfo,
    Int64*        min,
    Int64*        max,
    Int64*        dflt
);

/// This API is deprecated. Please refer to the documentation
/// Return the default value of a string parameter
/// @return The default value
/// @param paramInfo Handle to the parameter

const char * icmParamStringDefaultValue (
    icmParamInfoP paramInfo
);

/// This API is deprecated. Please refer to the documentation
/// Return the min, max and default values of an Uns32 the parameter
/// @return True if the parameter is of the correct type
/// @param paramInfo Handle to the parameter
/// @param min       The minimum value (output)
/// @param max       The maximum value (output)
/// @param dflt      The default value (output)

Bool icmParamUns32Limits (
    icmParamInfoP paramInfo,
    Uns32*        min,
    Uns32*        max,
    Uns32*        dflt
);

/// This API is deprecated. Please refer to the documentation
/// Return the min, max and default values of an Uns64 the parameter
/// @return True if the parameter is of the correct type
/// @param paramInfo Handle to the parameter
/// @param min       The minimum value (output)
/// @param max       The maximum value (output)
/// @param dflt      The default value (output)

Bool icmParamUns64Limits (
    icmParamInfoP paramInfo,
    Uns64*        min,
    Uns64*        max,
    Uns64*        dflt
);

/// This API is deprecated. Please refer to the documentation
/// Print the master and slave connections on a bus.

void icmPrintAllBusConnections (void);

/// This API is deprecated. Please refer to the documentation
/// Print the connections on all packetnets.

void icmPrintAllPacketnetConnections (void);

/// This API is deprecated. Please refer to the documentation
/// Print the master and slave connections on a bus.
/// @param bus The bus object.

void icmPrintBusConnections (
    icmBusP bus
);

/// This API is deprecated. Please refer to the documentation
/// Print a summary of nets and their connections

void icmPrintNetConnections (void);

/// This API is deprecated. Please refer to the documentation
/// Send formatted text to the simulator output stream. This sends output to the
/// simulator log without any prepended data. Only use this to produce tables,
/// xml or data of your own format.
/// @param fmt Printf format string (see gnu printf for details)
/// @param ... This is a vararg function

void icmPrintf (
    const char* fmt,
                ...
) __attribute__((format (printf, 1,2)));

/// This API is deprecated. Please refer to the documentation
/// Restore the state of the given processor
/// @return Success or failure.
/// @param processor The processor to restore as returned by icmNewProcessor
/// @param cb        The function used to restore data
/// @param userData  User context, passed back in the callback

icmSaveRestoreStatus icmProcessorRestoreState (
    icmProcessorP processor,
    icmRestoreFn  cb,
    void *        userData
);

/// This API is deprecated. Please refer to the documentation
/// Restore the state of the given processor from a file in default format
/// @return Success or failure.
/// @param processor The processor to restore as returned by icmNewProcessor
/// @param file      File name from which to restore

icmSaveRestoreStatus icmProcessorRestoreStateFile (
    icmProcessorP processor,
    const char *  file
);

/// This API is deprecated. Please refer to the documentation
/// Save the state of the given processor
/// @return Success or failure.
/// @param processor The processor to save, as returned by icmNewProcessor
/// @param cb        The function used to save data
/// @param userData  User context, passed back in the callback

icmSaveRestoreStatus icmProcessorSaveState (
    icmProcessorP processor,
    icmSaveFn     cb,
    void *        userData
);

/// This API is deprecated. Please refer to the documentation
/// Save the state of the given processor to a file in default format
/// @return Success or failure.
/// @param processor The processor to save, as returned by icmNewProcessor
/// @param file      File name to which to save

icmSaveRestoreStatus icmProcessorSaveStateFile (
    icmProcessorP processor,
    const char *  file
);

/// This API is deprecated. Please refer to the documentation
/// Read bytes from a bus into a buffer
/// @return True if access was successful.
/// @param proc       Processor object or null.
/// @param bus        Bus object.
/// @param simAddress Offset from base of memory.
/// @param buffer     Pointer to space the receive the data.
/// @param size       Number of bytes to transfer.

Bool icmReadBus (
    icmProcessorP proc,
    icmBusP       bus,
    Addr          simAddress,
    void*         buffer,
    Uns32         size
);

/// This API is deprecated. Please refer to the documentation
/// Read bytes from memory into a buffer
/// @return True if access was successful.
/// @param memory     Memory object.
/// @param simAddress Offset from base of memory.
/// @param buffer     Pointer to user's space to receive the data.
/// @param size       Number of bytes to transfer.

Bool icmReadMemory (
    icmMemoryP memory,
    Addr       simAddress,
    void*      buffer,
    Uns32      size
);

/// This API is deprecated. Please refer to the documentation
/// Read the header of an object file and find the architecture, endian-ness and
/// entry point
/// @return True if it was able to read it
/// @param filename Name of file to load.
/// @param cpuType  Type code (ELF or COFF)
/// @param endianp  Endian code
/// @param reset    Entry address

Bool icmReadObjectFileHeader (
    const char * filename,
    Uns16*       cpuType,
    icmEndian*   endianp,
    Addr*        reset
);

/// This API is deprecated. Please refer to the documentation
/// Read the header of an object file, returning comprehensive information
/// @return True if able to read it
/// @param filename Name of file to load.
/// @param info     Pointer to structure filled by this function and defined
///                 in ord/ordObjAttrs.h

Bool icmReadObjectFileHeaderInfo (
    const char *   filename,
    ordObjectInfoP info
);

/// This API is deprecated. Please refer to the documentation
/// Read an object file, making callbacks for each region
/// @return True if successful
/// @param processor  Processor
/// @param objectFile Path to the object file (must be a recognized format).
/// @param notifierCB Region callback
/// @param offset     Load offset
/// @param userData   User data

Bool icmReadObjectFileInfo (
    icmProcessorP processor,
    const char*   objectFile,
    ordSectionFn  notifierCB,
    Addr          offset,
    void*         userData
);

/// This API is deprecated. Please refer to the documentation
/// Read a region from the processor address space into native memory.
/// @return True if access was successful.
/// @param processor  Processor object.
/// @param simAddress Base address of the region to be read.
/// @param buffer     Pointer to space to receive the data.
/// @param bytes      Number of bytes to transfer.

Bool icmReadProcessorMemory (
    icmProcessorP processor,
    Addr          simAddress,
    void*         buffer,
    Uns32         bytes
);

/// This API is deprecated. Please refer to the documentation
/// Read a named register of a processor
/// @return True if the name was recognized.
/// @param processor Processor object.
/// @param name      Name of the register.
/// @param buffer    Space to receive the register contents. Must be large
///                  enough to accept the data.

Bool icmReadReg (
    icmProcessorP processor,
    const char*   name,
    void*         buffer
);

/// This API is deprecated. Please refer to the documentation
/// Read a processor register.
/// @return True if the register is readable.
/// @param icmProcessor Processor object.
/// @param reg          Register object.
/// @param buffer       Data to be written (must be the correct size).

Bool icmReadRegInfoValue (
    icmProcessorP icmProcessor,
    icmRegInfoP   reg,
    void*         buffer
);

/// This API is deprecated. Please refer to the documentation
/// Reset the error count
/// @return The old error count
/// @param old Old error count

Uns32 icmResetErrors (
    Uns32 old
);

/// This API is deprecated. Please refer to the documentation
/// Reset the passed watchpoint object so that it is no longer marked as
/// triggered.
/// @param watchpoint Watchpoint to reset

void icmResetWatchPoint (
    icmWatchPointP watchpoint
);

/// This API is deprecated. Please refer to the documentation
/// Return true if this processor can run code
/// @return True if can run code
/// @param processor The processor object.

Bool icmSMPIsLeaf (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Set address breakpoint for the processor. When breakpoint address is
/// executed, processor stops execution with stopReason ICM_SR_BP_ADDRESS
/// @param processor  Processor on which to set breakpoint
/// @param simAddress Address at which to break

void icmSetAddressBreakpoint (
    icmProcessorP processor,
    Addr          simAddress
);

/// This API is deprecated. Please refer to the documentation
/// Set access watchpoint on address range low:high in bus. When any processor
/// reads or writes an address in that range, it will stop execution with
/// stopReason ICM_SR_WATCHPOINT. Upon halt, all triggered watchpoints need to
/// be processed with icmGetNextTriggeredWatchPoint before simulation is
/// resumed.
/// @return Watchpoint object created
/// @param bus        Memory on which to set watchpoint
/// @param low        Low bound of watched range
/// @param high       High bound of watched range
/// @param userData   Client-specific data pointer
/// @param notifierCB Client-specific notifier

icmWatchPointP icmSetBusAccessWatchPoint (
    icmBusP          bus,
    Addr             low,
    Addr             high,
    void*            userData,
    icmMemNotifierFn notifierCB
);

/// This API is deprecated. Please refer to the documentation
/// Set read watchpoint on address range low:high in bus. When any processor
/// reads an address in that range, it will stop execution with stopReason
/// ICM_SR_WATCHPOINT. Upon halt, all triggered watchpoints need to be processed
/// with icmGetNextTriggeredWatchPoint before simulation is resumed.
/// @return Watchpoint object created
/// @param bus        Bus on which to set watchpoint
/// @param low        Low bound of watched range
/// @param high       High bound of watched range
/// @param userData   Client-specific data pointer
/// @param notifierCB Client-specific notifier

icmWatchPointP icmSetBusReadWatchPoint (
    icmBusP          bus,
    Addr             low,
    Addr             high,
    void*            userData,
    icmMemNotifierFn notifierCB
);

/// This API is deprecated. Please refer to the documentation
/// Set write watchpoint on address range low:high in bus. When any processor
/// reads an address in that range, it will stop execution with stopReason
/// ICM_SR_WATCHPOINT. Upon halt, all triggered watchpoints need to be processed
/// with icmGetNextTriggeredWatchPoint before simulation is resumed.
/// @return Watchpoint object created
/// @param bus        Bus on which to set watchpoint
/// @param low        Low bound of watched range
/// @param high       High bound of watched range
/// @param userData   Client-specific data pointer
/// @param notifierCB Client-specific notifier

icmWatchPointP icmSetBusWriteWatchPoint (
    icmBusP          bus,
    Addr             low,
    Addr             high,
    void*            userData,
    icmMemNotifierFn notifierCB
);

/// This API is deprecated. Please refer to the documentation
/// Call this before icmInitPlatform. Ask for callbacks for debugger
/// integration.
/// @param notifiers Pointer to structure containing notifiers

void icmSetDebugNotifiers (
    icmDebugNotifierP notifiers
);

/// This API is deprecated. Please refer to the documentation
/// Set the stop time (for icmSimulatePlatform) - takes effect at the end of any
/// current time slice. icmSimulatePlatform will not return when this stop time
/// is reached, an attached debugger will get control.
/// @return True if successful.
/// @param newStopTime The new stop time (see icmTime).

Bool icmSetDebugStopTime (
    icmTime newStopTime
);

/// This API is deprecated. Please refer to the documentation
/// Set exception watchpoint. When the processor takes an exception it will stop
/// execution with stopReason ICM_SR_WATCHPOINT. Upon halt, all triggered
/// watchpoints need to be processed with icmGetNextTriggeredWatchPoint before
/// simulation is resumed.
/// @return Watchpoint object created
/// @param processor  Processor on which to set watchpoint
/// @param userData   Client-specific data pointer
/// @param notifierCB Client-specific notifier

icmWatchPointP icmSetExceptionWatchPoint (
    icmProcessorP    processor,
    void*            userData,
    icmRegNotifierFn notifierCB
);

/// This API is deprecated. Please refer to the documentation
/// Set instruction count breakpoint for the processor that will expire after
/// 'delta' instructions. When instruction count has expired, processor stops
/// execution with stopReason ICM_SR_BP_ICOUNT.
/// @param processor Processor on which to set breakpoint
/// @param delta     Instruction count after which to stop

void icmSetICountBreakpoint (
    icmProcessorP processor,
    Uns64         delta
);

/// This API is deprecated. Please refer to the documentation
/// Set access watchpoint on address range low:high in memory. When any
/// processor reads or writes an address in that range, it will stop execution
/// with stopReason ICM_SR_WATCHPOINT. Upon halt, all triggered watchpoints need
/// to be processed with icmGetNextTriggeredWatchPoint before simulation is
/// resumed.
/// @return Watchpoint object created
/// @param memory     Memory on which to set watchpoint
/// @param low        Low bound of watched range
/// @param high       High bound of watched range
/// @param userData   Client-specific data pointer
/// @param notifierCB Client-specific notifier

icmWatchPointP icmSetMemoryAccessWatchPoint (
    icmMemoryP       memory,
    Addr             low,
    Addr             high,
    void*            userData,
    icmMemNotifierFn notifierCB
);

/// This API is deprecated. Please refer to the documentation
/// Set read watchpoint on address range low:high in memory. When any processor
/// reads an address in that range, it will stop execution with stopReason
/// ICM_SR_WATCHPOINT. Upon halt, all triggered watchpoints need to be processed
/// with icmGetNextTriggeredWatchPoint before simulation is resumed.
/// @return Watchpoint object created
/// @param memory     Memory on which to set watchpoint
/// @param low        Low bound of watched range
/// @param high       High bound of watched range
/// @param userData   Client-specific data pointer
/// @param notifierCB Client-specific notifier

icmWatchPointP icmSetMemoryReadWatchPoint (
    icmMemoryP       memory,
    Addr             low,
    Addr             high,
    void*            userData,
    icmMemNotifierFn notifierCB
);

/// This API is deprecated. Please refer to the documentation
/// Set write watchpoint on address range low:high in memory. When any processor
/// reads an address in that range, it will stop execution with stopReason
/// ICM_SR_WATCHPOINT. Upon halt, all triggered watchpoints need to be processed
/// with icmGetNextTriggeredWatchPoint before simulation is resumed.
/// @return Watchpoint object created
/// @param memory     Memory on which to set watchpoint
/// @param low        Low bound of watched range
/// @param high       High bound of watched range
/// @param userData   Client-specific data pointer
/// @param notifierCB Client-specific notifier

icmWatchPointP icmSetMemoryWriteWatchPoint (
    icmMemoryP       memory,
    Addr             low,
    Addr             high,
    void*            userData,
    icmMemNotifierFn notifierCB
);

/// This API is deprecated. Please refer to the documentation
/// Set mode change watchpoint. When the processor mode changes (the value
/// returned by icmGetMode differs) it will stop execution with stopReason
/// ICM_SR_WATCHPOINT. Upon halt, all triggered watchpoints need to be processed
/// with icmGetNextTriggeredWatchPoint before simulation is resumed.
/// @return Watchpoint object created
/// @param processor  Processor on which to set watchpoint
/// @param userData   Client-specific data pointer
/// @param notifierCB Client-specific notifier

icmWatchPointP icmSetModeWatchPoint (
    icmProcessorP    processor,
    void*            userData,
    icmRegNotifierFn notifierCB
);

/// This API is deprecated. Please refer to the documentation
/// Set the processor program counter
/// @param processor Processor object.
/// @param simAddr   Value loaded into the PC. This function is similar to
///                  icmWriteReg, but does not need to know the name of the
///                  PC.

void icmSetPC (
    icmProcessorP processor,
    Addr          simAddr
);

/// This API is deprecated. Please refer to the documentation
/// Set path to a gdb executable and gdb start-up arguments. This is only
/// required if debugging a PSE.
/// @param processor PSE object.
/// @param path      Path to the GDB executable.
/// @param flags     Any command line flags required by GDB.

void icmSetPSEGdbPath (
    icmPseP     processor,
    const char* path,
    const char* flags
);

/// This API is deprecated. Please refer to the documentation
/// Set PSE diagnostic level. This sets the return value of the deprecated
/// bhmGetDiagnosticLevel and also causes the PSEs 'setDiagnosticLevel' function
/// to be called if one was installed.
/// @param pse   The PSE.
/// @param level The new diagnostic level. Usually 0-4, but see the
///              peripheral modeling guide.

void icmSetPSEdiagnosticLevel (
    icmPseP pse,
    Uns32   level
);

/// This API is deprecated. Please refer to the documentation
/// This function is deprecated. Please use icmInitPlatform to create a named
/// platform.
/// @param name Name of platform.

void icmSetPlatformName (
    const char* name
);

/// This API is deprecated. Please refer to the documentation
/// Set the platform status.
/// @param releaseStatus Enumerated type for release status
/// @param purpose       Enumerated type for packaging
/// @param visibility    Controls visibility in debugger and introspection
///                      (zero = visible)

void icmSetPlatformStatus (
    icmReleaseStatus releaseStatus,
    icmPurpose       purpose,
    icmVisibility    visibility
);

/// This API is deprecated. Please refer to the documentation
/// Set access watchpoint on address range low:high in the processor physical or
/// virtual address space (depending on the setting of 'isPhysical'). When any
/// processor reads or writes an address in that range, it will stop execution
/// with stopReason ICM_SR_WATCHPOINT. Upon halt, all triggered watchpoints need
/// to be processed with icmGetNextTriggeredWatchPoint before simulation is
/// resumed.
/// @return Watchpoint object created
/// @param processor  Processor on which to set watchpoint
/// @param isPhysical True for physical, False for virtual
/// @param low        Low bound of watched range
/// @param high       High bound of watched range
/// @param userData   Client-specific data pointer
/// @param notifierCB Client-specific notifier

icmWatchPointP icmSetProcessorAccessWatchPoint (
    icmProcessorP    processor,
    Bool             isPhysical,
    Addr             low,
    Addr             high,
    void*            userData,
    icmMemNotifierFn notifierCB
);

/// This API is deprecated. Please refer to the documentation
/// Do not use an external GDB for this processor
/// @param processor Processor to use the basic debug functionality

void icmSetProcessorGdbBasic (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// Set path to a gdb executable and gdb start-up arguments
/// @param processor Processor to associate with this gdb.
/// @param path      Path to the GDB.
/// @param flags     Optional command line flags.

void icmSetProcessorGdbPath (
    icmProcessorP processor,
    const char*   path,
    const char*   flags
);

/// This API is deprecated. Please refer to the documentation
/// Set application-specific handle associated with the processor
/// @param processor The processor returned by icmNewProcessorWithHandle()
/// @param handle    The processor handle

void icmSetProcessorHandle (
    icmProcessorP processor,
    void *        handle
);

/// This API is deprecated. Please refer to the documentation
/// Set read watchpoint on address range low:high in the processor physical or
/// virtual address space (depending on the setting of 'isPhysical'). When any
/// processor reads an address in that range, it will stop execution with
/// stopReason ICM_SR_WATCHPOINT. Upon halt, all triggered watchpoints need to
/// be processed with icmGetNextTriggeredWatchPoint before simulation is
/// resumed.
/// @return Watchpoint object created
/// @param processor  Processor on which to set watchpoint
/// @param isPhysical True for physical, False for virtual
/// @param low        Low bound of watched range
/// @param high       High bound of watched range
/// @param userData   Client-specific data pointer
/// @param notifierCB Client-specific notifier

icmWatchPointP icmSetProcessorReadWatchPoint (
    icmProcessorP    processor,
    Bool             isPhysical,
    Addr             low,
    Addr             high,
    void*            userData,
    icmMemNotifierFn notifierCB
);

/// This API is deprecated. Please refer to the documentation
/// Set write watchpoint on address range low:high in the processor physical or
/// virtual address space (depending on the setting of 'isPhysical'). When any
/// processor reads an address in that range, it will stop execution with
/// stopReason ICM_SR_WATCHPOINT. Upon halt, all triggered watchpoints need to
/// be processed with icmGetNextTriggeredWatchPoint before simulation is
/// resumed.
/// @return Watchpoint object created
/// @param processor  Processor on which to set watchpoint
/// @param isPhysical True for physical, False for virtual
/// @param low        Low bound of watched range
/// @param high       High bound of watched range
/// @param userData   Client-specific data pointer
/// @param notifierCB Client-specific notifier

icmWatchPointP icmSetProcessorWriteWatchPoint (
    icmProcessorP    processor,
    Bool             isPhysical,
    Addr             low,
    Addr             high,
    void*            userData,
    icmMemNotifierFn notifierCB
);

/// This API is deprecated. Please refer to the documentation
/// For internal use only
/// @param p Parameter One

void icmSetProduct (
    const char* p
);

/// This API is deprecated. Please refer to the documentation
/// Set register change watchpoint. When the register value changes in the
/// passed processor, it will stop execution with stopReason ICM_SR_WATCHPOINT.
/// Upon halt, all triggered watchpoints need to be processed with
/// icmGetNextTriggeredWatchPoint before simulation is resumed.
/// @return Watchpoint object created
/// @param processor  Processor on which to set watchpoint
/// @param regInfo    Register to watch or null.
/// @param userData   Client-specific data pointer
/// @param notifierCB Client-specific notifier

icmWatchPointP icmSetRegisterWatchPoint (
    icmProcessorP    processor,
    icmRegInfoP      regInfo,
    void*            userData,
    icmRegNotifierFn notifierCB
);

/// This API is deprecated. Please refer to the documentation
/// Ask for a callback when each processor has finished its slice. Deprecated,
/// use icmSetDebugNotifiers
/// @param startcb  The start simulation function
/// @param endcb    The end schedule function
/// @param userData Pass this in the userData argument

void icmSetSchedFn (
    icmStartSimFn startcb,
    icmEndSchedFn endcb,
    void*         userData
);

/// This API is deprecated. Please refer to the documentation
/// Set a seed for randomizing the order in which processors are processed a
/// time slice. The default is no randomization (seed=0).
/// @param lfsrSeed New seed.

void icmSetSimulationRandomSeed (
    Uns32 lfsrSeed
);

/// This API is deprecated. Please refer to the documentation
/// Set the simulation stop time (for icmSimulatePlatform) - takes effect at the
/// end of any current time slice. icmSimulatePlatform will return when this
/// stop time is reached
/// @return True if successful.
/// @param newStopTime The new stop time (see icmTime).

Bool icmSetSimulationStopTime (
    icmTime newStopTime
);

/// This API is deprecated. Please refer to the documentation
/// Same as icmSetSimulationStopTime, accepting a double.
/// @return True if successful.
/// @param newStopTime The new stop time.

Bool icmSetSimulationStopTimeDouble (
    double newStopTime
);

/// This API is deprecated. Please refer to the documentation
/// Set the simulation time precision - all event times are rounded to this. Use
/// this if calling from MSVC.
/// @return True if successful.
/// @param precision The precision (see icmTime).

Bool icmSetSimulationTimePrecision (
    icmTime precision
);

/// This API is deprecated. Please refer to the documentation
/// Same as icmSetSimulationTimePrecision, accepting a double.
/// @return True if successful.
/// @param precision The precision (see icmTime).

Bool icmSetSimulationTimePrecisionDouble (
    double precision
);

/// This API is deprecated. Please refer to the documentation
/// Set the simulation time slice size (for icmSimulatePlatform) - takes effect
/// at the end of the current time slice.
/// @return True if successful.
/// @param newSliceSize The new slice duration (see icmTime).

Bool icmSetSimulationTimeSlice (
    icmTime newSliceSize
);

/// This API is deprecated. Please refer to the documentation
/// Same as icmSetSimulationTimeSlice, accepting a double. Use this if calling
/// from MSVC.
/// @return True if successful.
/// @param newSliceSize New slice duration.

Bool icmSetSimulationTimeSliceDouble (
    double newSliceSize
);

/// This API is deprecated. Please refer to the documentation
/// Call this function to intercept all text output from the simulator.
/// @return Returns pointer to a redirection object, used to cancel the
///         redirection.
/// @param outputcb The text output function
/// @param quitcb   Function to quit the simulator
/// @param userData Pass this in the userData argument

icmRedirectP icmSetTextOutputFn (
    icmTextOutputFn outputcb,
    icmQuitFn       quitcb,
    void*           userData
);

/// This API is deprecated. Please refer to the documentation
/// This specifies the maximum multiple of real time at which the simulation
/// should run. If this is not specified (and the ICM_WALLCLOCK attribute is not
/// specified) then the simulation will run as fast as possible. A value of 2.0
/// implies no faster than twice real time; a value of 0.5 implies no faster
/// than half real time. It may be necessary to specify this to keep interactive
/// prompts from going by too quickly or to get semi-hosted peripherals such as
/// UARTs or NICs to function properly.
/// @param factor Scale factor to apply.

void icmSetWallClockFactor (
    double factor
);

/// This API is deprecated. Please refer to the documentation
/// Simulate a processor for a number of clocks.
/// @return Why it stopped (see icmStopReason enumerated type).
/// @param processor Processor object
/// @param clocks    Maximum number of clocks for which to simulate

icmStopReason icmSimulate (
    icmProcessorP processor,
    Uns64         clocks
);

/// This API is deprecated. Please refer to the documentation
/// Simulate the platform using the default scheduling scheme, using time slice
/// and stop time set by icmSetSimulationTimeSlice and icmSetSimulationStopTime.
/// @return The processor that has caused simulation to stop, or null if no
///         processor has caused simulation to stop (e.g. the stop time has
///         been reached). The reason why a processor caused simulation to
///         stop can be found using icmGetPlatformStopReason.

icmProcessorP icmSimulatePlatform (void);

/// This API is deprecated. Please refer to the documentation
/// This can be called just as simulation is about to end, in order to activate
/// PSE end-of-simulation code. It is not required if icmSimulatePlatform() is
/// used.

void icmSimulationEnding (void);

/// This API is deprecated. Please refer to the documentation
/// This can be called after platform construction and before any processor or
/// PSE is due to run. It is not required if icmSimulatePlatform() or
/// icmSimulate() is used. It must be called if a platform has no processors
/// (just PSEs) or if PSEs are activated before processors.

void icmSimulationStarting (void);

/// This API is deprecated. Please refer to the documentation
/// Terminate ICM package - call this at end of simulation.

void icmTerminate (void);

/// This API is deprecated. Please refer to the documentation
/// Disable tracing for the processor after 'iDelta' more instructions
/// @param processor Turn off tracing for this processor
/// @param iDelta    Number of instructions before tracing is turned off.

void icmTraceOffAfter (
    icmProcessorP processor,
    Uns64         iDelta
);

/// This API is deprecated. Please refer to the documentation
/// Enable tracing for the processor after 'iDelta' more instructions Tracing
/// causes a single line of text to be output (including a disassembly of the
/// current instruction). Note that global simulation attributes control the
/// amount of extra detail that are added to the trace. This can include
/// converting addresses to labels by looking in the object file, or giving a
/// complete register dump after each instruction.
/// @param processor Turn on tracing for this processor
/// @param iDelta    Number of instructions before tracing is turned on.

void icmTraceOnAfter (
    icmProcessorP processor,
    Uns64         iDelta
);

/// This API is deprecated. Please refer to the documentation
/// Call a function after a given (simulated) time interval.
/// @return An event handle which can be used to cancel the event (before it
///         triggers)
/// @param delay Delay in microseconds.
/// @param cb    Address of function to call
/// @param user  Data passed to the callback

icmTriggerEventP icmTriggerAfter (
    icmTime      delay,
    icmTriggerFn cb,
    void*        user
);

/// This API is deprecated. Please refer to the documentation
/// Synthesize a VLNV path string given the vendor, library, name and version of
/// the library object you wish to load. Similar to icmGetVlnvString, but does
/// not report errors.
/// @return Null if no unique file is found, otherwise a file path
/// @param vlnvroot Path or list of paths to root of directory(s) containing
///                 modelsT
/// @param vendor   Vendor directory e.g. yourcompany.com or '*'
/// @param library  Library directory e.g. processor or '*'
/// @param name     Name directory e.g. risc32 or '*'
/// @param version  Version directory e.g. 1.0 or '*'
/// @param objType  Filename in the version directory or 'pse' or 'model'

const char* icmTryVlnvString (
    const char* vlnvroot,
    const char* vendor,
    const char* library,
    const char* name,
    const char* version,
    const char* objType
);

/// This API is deprecated. Please refer to the documentation
/// Remove a dynamic bridge. See icmBridgeBuses().
/// @param bus      Bus with slave port; this generates the addresses.
/// @param lowAddr  The lower end of the slave region.
/// @param highAddr The higher end of the slave region.

void icmUnbridgeBuses (
    icmBusP bus,
    Addr    lowAddr,
    Addr    highAddr
);

/// This API is deprecated. Please refer to the documentation
/// Unfreeze the processor (frozen processors will not be run by icmSimulate or
/// icmSimulatePlatform).
/// @param processor The processor that was running.

void icmUnfreeze (
    icmProcessorP processor
);

/// This API is deprecated. Please refer to the documentation
/// As for icmVMessage, but does not return. Use for internal errors.
/// @param ident A short code to identify this message.
/// @param fmt   Printf format string (see gnu printf for details)
/// @param ap    Varargs list

void icmVAbort (
    const char* ident,
    const char* fmt,
    va_list     ap
);

/// This API is deprecated. Please refer to the documentation
/// As for icmMessage, but using a va_list
/// @param severity I=Info W=Warning E=Error F=Fatal (aborts the simulator)
/// @param ident    A short code to identify this message. This makes the
///                 message easy to extract using text tools.
/// @param fmt      Printf format string (see gnu printf for details)
/// @param ap       Varargs list

void icmVMessage (
    const char* severity,
    const char* ident,
    const char* fmt,
    va_list     ap
);

/// This API is deprecated. Please refer to the documentation
/// Send formatted text to the simulator output stream
/// @param fmt Printf format string (see gnu printf for details)
/// @param ap  Varargs list header

void icmVPrintf (
    const char* fmt,
    va_list     ap
);

/// This API is deprecated. Please refer to the documentation
/// Write bytes to a bus from a buffer
/// @return True if access was successful.
/// @param proc       Processor object or null.
/// @param bus        Bus object.
/// @param simAddress Offset from base of memory.
/// @param buffer     Pointer to space containing the data.
/// @param size       Number of bytes to transfer.

Bool icmWriteBus (
    icmProcessorP proc,
    icmBusP       bus,
    Addr          simAddress,
    const void*   buffer,
    Uns32         size
);

/// This API is deprecated. Please refer to the documentation
/// Write bytes to memory from a buffer
/// @return True if access was successful.
/// @param memory     Memory object.
/// @param simAddress Offset from base of memory.
/// @param buffer     Pointer to user's space containing the data.
/// @param size       Number of bytes to transfer.

Bool icmWriteMemory (
    icmMemoryP  memory,
    Addr        simAddress,
    const void* buffer,
    Uns32       size
);

/// This API is deprecated. Please refer to the documentation
/// Write a value to a net.
/// @return True if the net is connected.
/// @param net      The net object.
/// @param netValue Value to be propagated.

Bool icmWriteNet (
    icmNetP net,
    Uns64   netValue
);

/// This API is deprecated. Please refer to the documentation
/// Write a value to a netPort.
/// @return True if the port is connected.
/// @param port     The netPort object.
/// @param netValue Value to be propagated.

Bool icmWriteNetPort (
    icmNetPortP port,
    Uns64       netValue
);

/// This API is deprecated. Please refer to the documentation
/// Write data to a packetnet
/// @param packetnet Packetnet object
/// @param data      Data
/// @param bytes     Number of data bytes to send

void icmWritePacketnet (
    icmPacketnetP packetnet,
    void*         data,
    Uns32         bytes
);

/// This API is deprecated. Please refer to the documentation
/// Write a region from native memory into processor address.
/// @return True if access was successful.
/// @param processor  Processor object.
/// @param simAddress Base address of the region to be written
/// @param buffer     Pointer to space containing the data.
/// @param bytes      Number of bytes to transfer.

Bool icmWriteProcessorMemory (
    icmProcessorP processor,
    Addr          simAddress,
    const void*   buffer,
    Uns32         bytes
);

/// This API is deprecated. Please refer to the documentation
/// Write a named register of a processor
/// @return True if the name was recognized and the register is readable.
/// @param processor Processor object.
/// @param name      Name of the register.
/// @param buffer    Buffer containing the register contents.

Bool icmWriteReg (
    icmProcessorP processor,
    const char*   name,
    const void*   buffer
);

/// This API is deprecated. Please refer to the documentation
/// Write to a processor register.
/// @return True if the register is writable
/// @param icmProcessor Processor object.
/// @param reg          Register object.
/// @param buffer       Space for data to read read (must be the correct
///                     size).

Bool icmWriteRegInfoValue (
    icmProcessorP icmProcessor,
    icmRegInfoP   reg,
    const void*   buffer
);

/// This API is deprecated. Please refer to the documentation
/// Suspend execution of the passed processor (this may be the current
/// processor) and return immediately from icmSimulate with icmStopReason
/// ICM_SR_YIELD (typically used within icmMemReadFn or icmMemWriteFn callback).
/// As with all other ICM functions this should not be called from a signal
/// handler to interrupt simulation (see icmInterrupt for this purpose)
/// @param processor The processor that was running.

void icmYield (
    icmProcessorP processor
);


#endif /* ICMCPUMANAGER_H */

