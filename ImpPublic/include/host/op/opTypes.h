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


#ifndef OPTYPES_H
#define OPTYPES_H

#include <stdarg.h>
#include "hostapi/impTypes.h"
#include "ord/ordObjAttrs.h"
#include "ocl/ocliaTyperefs.h"
#include "ocl/oclhttpTypes.h"
#include "ocl/oclASTypes.h"
#include "op/opTyperefs.h"


////////////////////////////////////////////////////////////////////////////////
// Types
////////////////////////////////////////////////////////////////////////////////

/// Simulator time (in seconds) 64 bits precision with MSVC, 80 bits otherwise
typedef externalTime  optTime;


////////////////////////////////////////////////////////////////////////////////
// Enums
////////////////////////////////////////////////////////////////////////////////

/// Types of bus port
typedef enum optBusPortTypeE {
    OP_UNKNOWN_TYPE , ///< Connection type unknown or not yet set
    OP_MASTER       , ///< Bus Master (e.g. processor instruction port)
    OP_SLAVE        , ///< Bus Slave (e.g. memory port)
    OP_MASTERSLAVE    ///< Bus Master and Slave
} optBusPortType;

/// Types of documentation node
typedef enum optDocNodeTypeE {
    OP_DOC_NODE_TITLE  , ///< Node is a section title or heading
    OP_DOC_NODE_TEXT   , ///< Node is body text
    OP_DOC_NODE_FIELDS , ///< Node describes a group of bit-fields
    OP_DOC_NODE_FIELD    ///< Node describes a single bit-field
} optDocNodeType;

/// Types of bus port domain
typedef enum optDomainTypeE {
    OP_CODE_DOMAIN  , ///< Bus port is connected to the code domain of the model
    OP_DATA_DOMAIN  , ///< Bus port is connected to the data domain of the model
    OP_OTHER_DOMAIN   ///< Bus port is connected to another type of domain of
                      ///  the model
} optDomainType;

/// How to disassemble
typedef enum optDisassAttrsE {
    OP_DSA_NORMAL   = 0x00000000, ///< normal disassembly
    OP_DSA_UNCOOKED = 0x00000001, ///< model-specific uncooked format
    OP_DSA_BASE     = 0x00000002, ///< use base model disassembly (not
                                  ///  intercept)
    OP_DSA_MODEL    = 0x80000000  ///< model-specific mask
} optDisassAttrs;

/// The endian-ness of an image (program) file
typedef enum optEndianE {
    OP_ENDIAN_NONE   = 0, ///< No endian specified
    OP_ENDIAN_LITTLE = 1, ///< Definitely little
    OP_ENDIAN_BIG    = 2, ///< Definitely big
    OP_ENDIAN_EITHER = 3  ///< Could be either (not used in this release)
} optEndian;

/// The endian-ness of host memory
typedef enum optHostEndianE {
    OP_HOSTENDIAN_HOST   = 0, ///< Buffer is same endian as host
    OP_HOSTENDIAN_TARGET = 1, ///< Buffer is same endian as the target processor
    OP_HOSTENDIAN_BIG    = 2, ///< Buffer is big endian
    OP_HOSTENDIAN_LITTLE = 3  ///< Buffer is little endian
} optHostEndian;

/// Types of flag accepted by the command line parser. See opCmdParserAdd and
/// for example the optFlagBoolFn prototype definitions.
typedef enum optFlagTypeE {
    OP_FT_NONE        , ///< Do not use
    OP_FT_BOOLVAL     , ///< The argument sets a variable of type Bool
    OP_FT_INT32VAL    , ///< The argument sets a variable of type Int32
    OP_FT_INT64VAL    , ///< The argument sets a variable of type Int64
    OP_FT_UNS32VAL    , ///< The argument sets a variable of type Uns32
    OP_FT_UNS64VAL    , ///< The argument sets a variable of type Uns64
    OP_FT_DOUBLEVAL   , ///< The argument sets a variable of type double
    OP_FT_STRINGVAL   , ///< The argument sets a variable of type char*
    OP_FT_STRINGLIST  , ///< One list element is created for each use of the
                        ///  argument
    OP_FT_STRINGSLAST , ///< This flag must be the last on the command line. All
                        ///  the following text is absorbed by this flag.
    OP_FT_PAIRLIST    , ///< One [name=value] pair is created for each use of
                        ///  the argument. If the = is missing, then the name is
                        ///  assumed to be null.
    OP_FT_GLOBSTRING  , ///< One list element is created for each use of the
                        ///  argument. Strings are file-glob expanded
    OP_FT_FC_BOOLEAN  , ///< The specified function is called each time the flag
                        ///  is specified
    OP_FT_FC_INT32    , ///< The specified function is called each time the
                        ///  Int32 argument is specified
    OP_FT_FC_INT64    , ///< The specified function is called each time the
                        ///  Int64 argument is specified
    OP_FT_FC_UNS32    , ///< The specified function is called each time the
                        ///  Uns32 argument is specified
    OP_FT_FC_UNS64    , ///< The specified function is called each time the
                        ///  Uns64 argument is specified
    OP_FT_FC_DOUBLE   , ///< The specified function is called each time the
                        ///  double argument is specified
    OP_FT_FC_STRING   , ///< The specified function is called each time string
                        ///  argument is specified
    OP_FT_FC_PAIR     , ///< The specified function is called each time the
                        ///  [name=value] argument is specified. If the = is
                        ///  missing, then the name is assumed to be null.
    OP_FT_FC_ARGV     , ///< The specified function is called with each list of
                        ///  arguments
    OP_FT_FC_ARGVLAST , ///< This flag must be the last on the command line. All
                        ///  the following text is absorbed by this flag. The
                        ///  specified function is called for each argument
    OP_FT_FC_ARGVPAIR , ///< The specified function is called with each list of
                        ///  name=value pairs
    OP_FT_FC_ATPAIR     ///< The specified function is called with value AT
                        ///  option
} optFlagType;

/// Command line parser argument class. Use as an argument to opCmdParserNew to
/// select which of the standard simulator arguments are supported.
typedef enum optArgClassE {
    OP_AC_NONE  = 0x00, ///< No standard arguments are supported. The user must
                        ///  define their own arguments.
    OP_AC_BASIC = 0x01, ///< Enable the basic arguments
    OP_AC_EXT1  = 0x02, ///< Enable the basic demo arguments
    OP_AC_EXT2  = 0x04, ///< Enable the extended demo arguments
    OP_AC_SIM   = 0x08, ///< Enable the simulator arguments (this includes basic
                        ///  and extended arguments)
    OP_AC_LIB   = 0x10, ///< Enable the library management arguments
    OP_AC_ENG   = 0x20, ///< Engineering mode only. Do not use.
    OP_AC_ALL   = 0x18  ///< All available arguments are supported.
} optArgClass;

/// Types of FIFO port
typedef enum optFIFOPortTypeE {
    OP_FIFO_INPUT  , ///< Input which receives from a FIFO
    OP_FIFO_OUTPUT   ///< Output which drives a FIFO
} optFIFOPortType;

/// Use as an argument to opProcessorApplicationLoad to control the application
/// loader features.
typedef enum optLoaderControlsE {
    OP_LDR_DEFAULT          = 0x0000, ///< No special features
    OP_LDR_PHYSICAL         = 0x0001, ///< The loader will use physical as
                                      ///  opposed to logical addresses
    OP_LDR_VERBOSE          = 0x0002, ///< The loader will report sections as
                                      ///  they are loaded
    OP_LDR_NO_ZERO_BSS      = 0x0004, ///< The loader will not zero the BSS
                                      ///  section
    OP_LDR_SET_START        = 0x0008, ///< The loader will set the PC of the
                                      ///  target processor (where known) to the
                                      ///  start address
    OP_LDR_SYMBOLS_ONLY     = 0x0010, ///< The loader will read the symbols but
                                      ///  not load the program
    OP_LDR_ELF_USE_VMA      = 0x0020, ///< The loader will load ELF files using
                                      ///  VMA addresses rather than LMA
    OP_LDR_FAIL_IS_ERROR    = 0x0040, ///< Failure to load will report an error
                                      ///  and prevent the simulation from
                                      ///  running
    OP_LDR_SIGN_EXTEND_ADDR = 0x0080, ///< Sign-extend addresses from 32b to 64b
    OP_LDR_READ_FRAME_INFO  = 0x0100, ///< Read DWARF frame information
    OP_LDR_LIMIT_32         = 0x0200, ///< Limited to 32 bits per write
                                      ///  (required when loading via TLM)
    OP_LDR_LIMIT_64         = 0x0400, ///< Limited to 64 bits per write
                                      ///  (required when loading via TLM)
    OP_LDR_SET_PROTECTION   = 0x0800  ///< The loader will set memory protection
                                      ///  according to the loaded program
} optLoaderControls;

/// Types of model
typedef enum optModelTypeE {
    OP_PROCESSOR    , ///< Processor (shared object using Processor VMI API)
    OP_EXTENSION    , ///< Extension (shared object using Extension VMI API)
    OP_MMC          , ///< MMC (shared object using MMC VMI API)
    OP_MODULE       , ///< Module (shared object using OP API)
    OP_PERIPHERAL   , ///< Peripheral (PSE executable using BHM/PPM API)
    OP_PLATFORM     , ///< Platform (host executable using ICM or OP API)
    OP_XML_PLATFORM , ///< Platform (host executable using ICM or OP API)
    OP_NOT_VALID      ///< Do not use
} optModelType;

/// Types of net port
typedef enum optNetPortTypeE {
    OP_NODIR  , ///< Direction is not set
    OP_INPUT  , ///< Input port : receives from a wire or FIFO
    OP_OUTPUT , ///< Output port : drives a wire or FIFO
    OP_INOUT    ///< Net port which can function as an input and output
} optNetPortType;

/// Parameter and Formal types
typedef enum optParamTypeE {
    OP_PARAM_NONE   , ///< dummy type for list head
    OP_PARAM_BOOL   , ///< boolean
    OP_PARAM_INT32  , ///< 32bit signed integer
    OP_PARAM_INT64  , ///< 64bit signed integer
    OP_PARAM_UNS32  , ///< 32bit unsigned integer
    OP_PARAM_UNS64  , ///< 64bit unsigned integer
    OP_PARAM_DOUBLE , ///< double precision floating point
    OP_PARAM_STRING , ///< text string
    OP_PARAM_ENUM   , ///< enumerated type
    OP_PARAM_ENDIAN , ///< special enumerated type: big, little or either
    OP_PARAM_PTR      ///< anonymous pointer
} optParamType;

/// Used to select which kind of formal parameters to view
typedef enum optParamClassE {
    OP_PARAM_SYSTEM = 1, ///< System parameters
    OP_PARAM_MODEL  = 2, ///< Model-specific parameters
    OP_PARAM_ALL    = 3  ///< Model-specific parameters
} optParamClass;

/// Memory access privilege
typedef enum optPrivE {
    OP_PRIV_NONE  = 0x0, ///< No access permitted
    OP_PRIV_R     = 0x1, ///< Read permitted
    OP_PRIV_W     = 0x2, ///< Write permitted
    OP_PRIV_RW    = 0x3, ///< Read and write permitted
    OP_PRIV_X     = 0x4, ///< Execute permitted
    OP_PRIV_RX    = 0x5, ///< Read and execute permitted
    OP_PRIV_WX    = 0x6, ///< Write and execute permitted
    OP_PRIV_RWX   = 0x7, ///< Read, write and execute permitted
    OP_PRIV_ALIGN = 0x8  ///< Force accesses to be aligned
} optPriv;

/// Platform purpose, used by product packaging tools to classify the platform.
/// See opModulePurpose()
typedef enum optPurposeE {
    OP_PP_BAREMETAL , ///< A processor with memory
    OP_PP_FIX       , ///< A fixed platform
    OP_PP_EPK       , ///< Extensible Platform Kit
    OP_PP_MODULE    , ///< This is a module - part of another platform
    OP_PP_OEM         ///< For use only by specific OEM. Not for general release
} optPurpose;

/// CPU Register classification
typedef enum optRegUsageE {
    OP_REG_NONE = 0, ///< No special usage for this register
    OP_REG_PC   = 1, ///< Register is the program counter
    OP_REG_SP   = 2, ///< Register is the stack pointer
    OP_REG_FP   = 3, ///< Register is the frame pointer
    OP_REG_LR   = 4  ///< The link register
} optRegUsage;

/// CPU Register access modes
typedef enum optRegAccessE {
    OP_RA_NONE = 0, ///< No access
    OP_RA_R    = 1, ///< Register is read-only
    OP_RA_W    = 2, ///< Register is write-only
    OP_RA_RW   = 3  ///< Register is read-write
} optRegAccess;

/// Model release status, used by product packaging tools. See
/// opObjectReleaseStatus()
typedef enum optReleaseStatusE {
    OP_UNSET      , ///< Not specified
    OP_INTERNAL   , ///< For internal use only
    OP_RESTRICTED , ///< Restricted release
    OP_IMPERAS    , ///< Imperas only
    OP_OVP          ///< Freely available
} optReleaseStatus;

/// Error status returned by opSessionInit()
typedef enum optSessionStatusE {
    OP_SESSION_OK           , ///< Session started correctly
    OP_SESSION_IMPERAS_HOME , ///< IMPERAS_HOME was not set
    OP_SESSION_VERSION      , ///< Simulator incompatible with client
    OP_SESSION_RUNTIME      , ///< IMPERAS_RUNTIME set incorrectly
    OP_SESSION_PERSONALITY  , ///< IMPERAS_PERSONALITY or Licensing error
    OP_SESSION_CONTROL_FILE   ///< Error reading a control file
} optSessionStatus;

/// Simulator and API module phase descriptions. See opObjectSimulatorPhase()
/// and opObjectSimulatorPhaseString()
typedef enum optSimulatorPhaseE {
    OP_PH_UNKNOWN       = 0x00, ///< Unknown phase (invalid module hierarchy).
    OP_PH_CONSTRUCT     = 0x01, ///< In the constructor callback or in main()
    OP_PH_PRE_SIMULATE  = 0x02, ///< All modules have been constructed,
                                ///  simulation has not started. Processor VM
                                ///  constructors are called in this phase.
    OP_PH_SIMULATE      = 0x04, ///< Simulation is in progress, time is
                                ///  advancing.
    OP_PH_POST_SIMULATE = 0x08, ///< Simulation is complete. The platform is
                                ///  still intact.
    OP_PH_REPORT        = 0x10, ///< The post simulation phase is complete. The
                                ///  platform is still intact.
    OP_PH_DESTRUCT      = 0x20, ///< Other objects cannot be guaranteed to
                                ///  exist.
    OP_PHS_QUERY        = 0x1F  ///< This is not a phase. It represents all
                                ///  phases except destruction.
} optSimulatorPhase;

/// This is used to qualify the count returned by opProcessorSkipCycles.
typedef enum optCycleSkipTypeE {
    OP_ST_COMMITTED , ///< Return a count of skipped cycles which have been
                      ///  committed and will be included in the return value
                      ///  from opProcessorCycleCount.
    OP_ST_PENDING   , ///< Return a count of skipped cycles which are pending
                      ///  and will not yet be included in the return value from
                      ///  opProcessorCycleCount. Pending skipped cycles are
                      ///  committed at a quantum boundary or by a call to
                      ///  opProcessorSkipCyclesAdd with immediate effect.
    OP_ST_ALL         ///< Return the total of committed and pending skipped
                      ///  cycles.
} optCycleSkipType;

/// Stop reason code returned by opProcessorStopReason() and
/// opRootModuleStopReason(). Also, see opProcessorSimulate() and
/// opRootModuleSimulate(). Note that stop reasons with 'exception' in their
/// description will NOT occur if the model has 'simulateexceptions' enabled
/// (the processor will take the exception, the simulator will not stop)
typedef enum optStopReasonE {
    OP_SR_SCHED      = 0x00, ///< Scheduler expired
    OP_SR_YIELD      = 0x01, ///< Yield encountered
    OP_SR_HALT       = 0x02, ///< CPU is halted
    OP_SR_EXIT       = 0x03, ///< CPU has exited
    OP_SR_FINISH     = 0x04, ///< Simulation finish
    OP_SR_RD_PRIV    = 0x05, ///< Read privilege exception
    OP_SR_WR_PRIV    = 0x06, ///< Write privilege exception
    OP_SR_RD_ALIGN   = 0x07, ///< Read align exception
    OP_SR_WR_ALIGN   = 0x08, ///< Write align exception
    OP_SR_FE_PRIV    = 0x09, ///< Fetch privilege exception
    OP_SR_ARITH      = 0x0a, ///< Arithmetic exception
    OP_SR_INTERRUPT  = 0x0b, ///< Interrupt simulation
    OP_SR_FREEZE     = 0x0c, ///< Frozen (by opProcessorFreeze)
    OP_SR_WATCHPOINT = 0x0d, ///< Memory watchpoint is pending
    OP_SR_BP_ICOUNT  = 0x0e, ///< Instruction count breakpoint is pending
    OP_SR_BP_ADDRESS = 0x0f, ///< Address breakpoint is pending
    OP_SR_RD_ABORT   = 0x10, ///< Read abort exception
    OP_SR_WR_ABORT   = 0x11, ///< Write abort exception
    OP_SR_FE_ABORT   = 0x12, ///< Fetch abort exception
    OP_SR_INVALID    = 0x13  ///< (invalid entry)
} optStopReason;

/// Supplementary information passed by the time advance callback. See
/// optSimulateTimeAdvanceFn
typedef enum optAdvanceTimeInfoE {
    OP_TA_NONE = 0x00, ///< No supplementary information
    OP_TA_SIM  = 0x01, ///< Simulator stop time reached
    OP_TA_DBG  = 0x02, ///< Debug stop time reached
    OP_TA_END  = 0x04  ///< End of simulation
} optAdvanceTimeInfo;

/// Types of memory storage
typedef enum optStorageTypeE {
    OP_RAM  , ///< Read/Write memory
    OP_ROM  , ///< Read-only memory
    OP_TRAP   ///< Unwritable region (for internal use)
} optStorageType;

/// Visibility of platform in debugger, introspection etc
typedef enum optVisibilityE {
    OP_VISIBLE   , ///< visible in all tools
    OP_INVISIBLE   ///< invisible in all tools
} optVisibility;

/// Types of watchpoint. See opWatchpointType
typedef enum optWatchpointTypeE {
    OP_WP_MEM_READ   , ///< Memory read watchpoint
    OP_WP_MEM_WRITE  , ///< Memory write watchpoint
    OP_WP_MEM_ACCESS , ///< Memory access watchpoint
    OP_WP_REG        , ///< Register watchpoint
    OP_WP_MODE       , ///< Mode change watchpoint
    OP_WP_EXCEPTION    ///< Exception watchpoint
} optWatchpointType;

/// Register watchpoint mode.
typedef enum optRegWatchpointModeE {
    OP_RWP_NONE    = 0, ///< Default value
    OP_RWP_CHANGE  = 1, ///< Watchpoint triggered if the register changes value
    OP_RWP_WRITTEN = 2  ///< Watchpoint triggered if the register is written
} optRegWatchpointMode;

/// Status returned by the save and restore functions.
typedef enum optSaveRestoreStatusE {
    OP_SAVE_OK    , ///< Save or restore was successful
    OP_SAVE_ERROR   ///< Save or restore was not successful
} optSaveRestoreStatus;

/// Where a parameter value comes from
typedef enum optParameterValueOriginE {
    OP_PARAM_DEFAULT  , ///< The default value from the model
    OP_PARAM_OVERRIDE , ///< Value comes from a command-line or control file
                        ///  override
    OP_PARAM_PLATFORM   ///< Value was set in the platform
} optParameterValueOrigin;

/// Conditions required for a processor to end the simulation
typedef enum optExitModeE {
    OP_EM_FIRST = 0, ///< The first processor core to call vmirtExit will finish
                     ///  the simulation
    OP_EM_ALL   = 1  ///< The last processor core of a cluster to call vmirtExit
                     ///  will finish the simulation
} optExitMode;

/// Action to take when a VLNV lookup fails to find a model
typedef enum optVLNVErrorE {
    OP_VLNV_QUIET = 0, ///< Return null but print nothing
    OP_VLNV_PRINT = 1, ///< Return null and print what failed and why
    OP_VLNV_FATAL = 2  ///< Raise a fatal error (no return)
} optVLNVError;


////////////////////////////////////////////////////////////////////////////////
// Structure References
////////////////////////////////////////////////////////////////////////////////

/// @struct optApplicationS
/// Application program object file
typedef struct optApplicationS          *optApplicationP        , **optApplicationPP;
/// @struct optBridgeS
/// Instance of a bridge
typedef struct optBridgeS               *optBridgeP             , **optBridgePP;
/// @struct optBusS
/// Bus interconnect instance
typedef struct optBusS                  *optBusP                , **optBusPP;
/// @struct optBusSlaveS
/// Pair of read/write callbacks on a bus region
typedef struct optBusSlaveS             *optBusSlaveP           , **optBusSlavePP;
/// @struct optBusPortS
/// Bus port specification
typedef struct optBusPortS              *optBusPortP            , **optBusPortPP;
/// @struct optBusPortConnS
/// Bus port instance
typedef struct optBusPortConnS          *optBusPortConnP        , **optBusPortConnPP;
/// @struct optCommandS
/// Model or plugin command
typedef struct optCommandS              *optCommandP            , **optCommandPP;
/// @struct optExtensionS
/// Instance of an extension applied to a model
typedef struct optExtensionS            *optExtensionP          , **optExtensionPP;
/// @struct optExtElabS
/// An elaborated extension
typedef struct optExtElabS              *optExtElabP            , **optExtElabPP;
/// @struct optFIFOS
/// The FIFO instance
typedef struct optFIFOS                 *optFIFOP               , **optFIFOPP;
/// @struct optFIFOPortS
/// FIFO port definition
typedef struct optFIFOPortS             *optFIFOPortP           , **optFIFOPortPP;
/// @struct optFIFOPortConnS
/// FIFO port instance
typedef struct optFIFOPortConnS         *optFIFOPortConnP       , **optFIFOPortConnPP;
/// @struct optFormalS
/// The formal parameter specifying a legal parameter of a model
typedef struct optFormalS               *optFormalP             , **optFormalPP;
/// @struct optFormalGroupS
/// A group of formals
typedef struct optFormalGroupS          *optFormalGroupP        , **optFormalGroupPP;
/// @struct optFormalEnumS
/// A name and value pair
typedef struct optFormalEnumS           *optFormalEnumP         , **optFormalEnumPP;
/// @struct optMemoryS
/// Instance of a memory
typedef struct optMemoryS               *optMemoryP             , **optMemoryPP;
/// @struct optMMCS
/// Instance of an MMC
typedef struct optMMCS                  *optMMCP                , **optMMCPP;
/// @struct optMMRegisterS
/// Memory Mapped Register
typedef struct optMMRegisterS           *optMMRegisterP         , **optMMRegisterPP;
/// @struct optMMRegisterFieldS
/// Memory Mapped Register Bitfield
typedef struct optMMRegisterFieldS      *optMMRegisterFieldP    , **optMMRegisterFieldPP;
/// @struct optModuleS
/// Instance of a module
typedef struct optModuleS               *optModuleP             , **optModulePP;
/// @struct optNetS
/// Net instance
typedef struct optNetS                  *optNetP                , **optNetPP;
/// @struct optNetMonitorS
/// Net callback installed before the platform is built
typedef struct optNetMonitorS           *optNetMonitorP         , **optNetMonitorPP;
/// @struct optNetPortS
/// Net port definition, used when querying the model
typedef struct optNetPortS              *optNetPortP            , **optNetPortPP;
/// @struct optNetPortConnS
/// Net port connection instance
typedef struct optNetPortConnS          *optNetPortConnP        , **optNetPortConnPP;
/// @struct optPacketnetS
/// Interconnect used to model packet networks such as Ethernet or CAN bus
typedef struct optPacketnetS            *optPacketnetP          , **optPacketnetPP;
/// @struct optPacketnetMonitorS
/// Packetnet callback installed before the platform is built
typedef struct optPacketnetMonitorS     *optPacketnetMonitorP   , **optPacketnetMonitorPP;
/// @struct optPacketnetPortS
/// Packetnet port definition, used when querying the model
typedef struct optPacketnetPortS        *optPacketnetPortP      , **optPacketnetPortPP;
/// @struct optPacketnetPortConnS
/// Packetnet port instance
typedef struct optPacketnetPortConnS    *optPacketnetPortConnP  , **optPacketnetPortConnPP;
/// @struct optParamS
/// Parameter of module or component instance
typedef struct optParamS                *optParamP              , **optParamPP;
/// @struct optPeripheralS
/// Instance of a peripheral model
typedef struct optPeripheralS           *optPeripheralP         , **optPeripheralPP;
/// @struct optProcessorS
/// Instance of a processor model
typedef struct optProcessorS            *optProcessorP          , **optProcessorPP;

#if defined(__cplusplus)
typedef void *optObjectP;
#else
#ifndef TRANSPARENT_UNION
    #define TRANSPARENT_UNION __attribute__((transparent_union))
#endif
/// The type optObjectP is a union of all the platform objects. It is returned
/// by functions that can return more than one object type and passed to
/// functions that can accept more than one type. Use opObjectType() to
/// determine the current type of an optObjectP. When the type is known, if
/// required, use the member operator to convert to that type (members are
/// listed above).
/// @par Example:
/// @code
///optObjectP obj = opObjectParent(thing);
///if(opObjectType(obj) == OP_MODULE_EN) {
///	// now the union type is certain, convert to that type
///	optModuleP mod = obj.Module;
///    ...
///}
/// @endcode
/// Functions accepting an optObjectP can be passed any other member of the
/// union.
/// If a function returns an optObjectP then the union operator can be used to
/// extract the required type, so long as it is safe to do so.
/// @par Example:
/// @code
///optModuleP mod = opObjectByName(parent, "u1", OP_MODULE_EN).Module;
///if(mod) {
///	// pass optModuleP to optObjectP
///	const char *name = opObjectHierName(mod);
///    opPrintf("This module is called '%s'\n", name);
///}
/// @endcode
typedef union optObjectU {
    optApplicationP       Application;
    optBridgeP            Bridge;
    optBusP               Bus;
    optBusSlaveP          BusSlave;
    optBusPortP           BusPort;
    optBusPortConnP       BusPortConn;
    optCommandP           Command;
    optExtensionP         Extension;
    optExtElabP           ExtElab;
    optFIFOP              FIFO;
    optFIFOPortP          FIFOPort;
    optFIFOPortConnP      FIFOPortConn;
    optFormalP            Formal;
    optFormalGroupP       FormalGroup;
    optFormalEnumP        FormalEnum;
    optMemoryP            Memory;
    optMMCP               MMC;
    optMMRegisterP        MMRegister;
    optMMRegisterFieldP   MMRegisterField;
    optModuleP            Module;
    optNetP               Net;
    optNetMonitorP        NetMonitor;
    optNetPortP           NetPort;
    optNetPortConnP       NetPortConn;
    optPacketnetP         Packetnet;
    optPacketnetMonitorP  PacketnetMonitor;
    optPacketnetPortP     PacketnetPort;
    optPacketnetPortConnP PacketnetPortConn;
    optParamP             Param;
    optPeripheralP        Peripheral;
    optProcessorP         Processor;
} optObjectP TRANSPARENT_UNION;
#endif

/// Enumeration for each object type. See opObjectType()
typedef enum optStrTypeE {
    OP_NIL_EN             = 0x0,
    OP_APPLICATION_EN         = 0x1       , ///< Application program object file
    OP_BRIDGE_EN              = 0x2       , ///< Instance of a bridge
    OP_BUS_EN                 = 0x4       , ///< Bus interconnect instance
    OP_BUSSLAVE_EN            = 0x8       , ///< Pair of read/write callbacks on a bus region
    OP_BUSPORT_EN             = 0x10      , ///< Bus port specification
    OP_BUSPORTCONN_EN         = 0x20      , ///< Bus port instance
    OP_COMMAND_EN             = 0x40      , ///< Model or plugin command
    OP_EXTENSION_EN           = 0x80      , ///< Instance of an extension applied to a model
    OP_EXTELAB_EN             = 0x100     , ///< An elaborated extension
    OP_FIFO_EN                = 0x200     , ///< The FIFO instance
    OP_FIFOPORT_EN            = 0x400     , ///< FIFO port definition
    OP_FIFOPORTCONN_EN        = 0x800     , ///< FIFO port instance
    OP_FORMAL_EN              = 0x1000    , ///< The formal parameter specifying a legal parameter of a model
    OP_FORMALGROUP_EN         = 0x2000    , ///< A group of formals
    OP_FORMALENUM_EN          = 0x4000    , ///< A name and value pair
    OP_MEMORY_EN              = 0x8000    , ///< Instance of a memory
    OP_MMC_EN                 = 0x10000   , ///< Instance of an MMC
    OP_MMREGISTER_EN          = 0x20000   , ///< Memory Mapped Register
    OP_MMREGISTERFIELD_EN     = 0x40000   , ///< Memory Mapped Register Bitfield
    OP_MODULE_EN              = 0x80000   , ///< Instance of a module
    OP_NET_EN                 = 0x100000  , ///< Net instance
    OP_NETMONITOR_EN          = 0x200000  , ///< Net callback installed before the platform is built
    OP_NETPORT_EN             = 0x400000  , ///< Net port definition, used when querying the model
    OP_NETPORTCONN_EN         = 0x800000  , ///< Net port connection instance
    OP_PACKETNET_EN           = 0x1000000 , ///< Interconnect used to model packet networks such as Ethernet or CAN bus
    OP_PACKETNETMONITOR_EN    = 0x2000000 , ///< Packetnet callback installed before the platform is built
    OP_PACKETNETPORT_EN       = 0x4000000 , ///< Packetnet port definition, used when querying the model
    OP_PACKETNETPORTCONN_EN   = 0x8000000 , ///< Packetnet port instance
    OP_PARAM_EN               = 0x10000000, ///< Parameter of module or component instance
    OP_PERIPHERAL_EN          = 0x20000000, ///< Instance of a peripheral model
    OP_PROCESSOR_EN           = 0x40000000, ///< Instance of a processor model
} optStrType;


////////////////////////////////////////////////////////////////////////////////
// Callbacks
////////////////////////////////////////////////////////////////////////////////

/// This function is called during platform construction. Use this callback to
/// create structure including model and sub-module instances, interconnect,
/// permanent (static) bridges and callbacks. This callback will call the
/// construction function of each sub-module, in definition order, depth first.

/// @par Parameters:
/// @par
/// @a mi This module instance
/// @par
/// @a object Pointer to space allocated for persistent data in this module.
/// Refer to the objectSize field in the modelAttrs structure.

#define OP_CONSTRUCT_FN(_name) \
void _name ( \
    optModuleP       mi, \
    optModuleObjectP object)

/// This is a pointer to a function of the type defined by OP_CONSTRUCT_FN

typedef OP_CONSTRUCT_FN((*optConstructFn));

/// This function is called after the construction of this and all other
/// modules. Use this callback for any operation that requires the complete
/// platform to be constructed, but no simulation to have started.

/// @par Parameters:
/// @par
/// @a mi This module instance
/// @par
/// @a object Pointer to space allocated for persistent data in this module.
/// Refer to the objectSize field in the modelAttrs structure.

#define OP_POST_CONSTRUCT_FN(_name) \
void _name ( \
    optModuleP       mi, \
    optModuleObjectP object)

/// This is a pointer to a function of the type defined by OP_POST_CONSTRUCT_FN

typedef OP_POST_CONSTRUCT_FN((*optPostConstructFn));

/// This function is called only once before simulation is about to begin.

/// @par Parameters:
/// @par
/// @a mi This module instance
/// @par
/// @a object Pointer to space allocated for persistent data in this module.
/// Refer to the objectSize field in the modelAttrs structure.

#define OP_PRE_SIMULATE_FN(_name) \
void _name ( \
    optModuleP       mi, \
    optModuleObjectP object)

/// This is a pointer to a function of the type defined by OP_PRE_SIMULATE_FN

typedef OP_PRE_SIMULATE_FN((*optPreSimulateFn));

/// This function is called each time the top-level simulation is started after
/// pre-simulation or at restart after a stop-event.

/// @par Parameters:
/// @par
/// @a mi This module instance
/// @par
/// @a object Pointer to space allocated for persistent data in this module.
/// Refer to the objectSize field in the modelAttrs structure.

#define OP_SIMULATE_STARTING_FN(_name) \
void _name ( \
    optModuleP       mi, \
    optModuleObjectP object)

/// This is a pointer to a function of the type defined by
/// OP_SIMULATE_STARTING_FN

typedef OP_SIMULATE_STARTING_FN((*optSimulateStartingFn));

/// This function is called only once, when simulation has finished, before any
/// destruction. Use this call-back to gather and report simulation statistics.

/// @par Parameters:
/// @par
/// @a mi This module instance
/// @par
/// @a object Pointer to space allocated for persistent data in this module.
/// Refer to the objectSize field in the modelAttrs structure.

#define OP_POST_SIMULATE_FN(_name) \
void _name ( \
    optModuleP       mi, \
    optModuleObjectP object)

/// This is a pointer to a function of the type defined by OP_POST_SIMULATE_FN

typedef OP_POST_SIMULATE_FN((*optPostSimulateFn));

/// This function is called during platform destruction. Use this call-back to
/// free resources unknown to the simulator. It should not rely on existence of
/// other modules.

/// @par Parameters:
/// @par
/// @a mi This module instance
/// @par
/// @a object Pointer to space allocated for persistent data in this module.
/// Refer to the objectSize field in the modelAttrs structure.

#define OP_DESTRUCT_FN(_name) \
void _name ( \
    optModuleP       mi, \
    optModuleObjectP object)

/// This is a pointer to a function of the type defined by OP_DESTRUCT_FN

typedef OP_DESTRUCT_FN((*optDestructFn));

/// This function is called when system save is invoked. Use this call-back to
/// save module data unknown to the simulator

/// @par Parameters:
/// @par
/// @a mi This module instance
/// @par
/// @a object Pointer to space allocated for persistent data in this module.
/// Refer to the objectSize field in the modelAttrs structure.
/// @par
/// @a context Context to be passed to restore function

#define OP_MODULE_SAVE_FN(_name) \
void _name ( \
    optModuleP       mi, \
    optModuleObjectP object, \
    optSaveContextP  context)

/// This is a pointer to a function of the type defined by OP_MODULE_SAVE_FN

typedef OP_MODULE_SAVE_FN((*optModuleSaveFn));

/// This function is called when system restore is invoked. Use this call-back
/// to restore module data unknown to the simulator

/// @par Parameters:
/// @par
/// @a mi This module instance
/// @par
/// @a object Pointer to space allocated for persistent data in this module.
/// Refer to the objectSize field in the modelAttrs structure.
/// @par
/// @a context Context to be passed to restore function

#define OP_MODULE_RESTORE_FN(_name) \
void _name ( \
    optModuleP         mi, \
    optModuleObjectP   object, \
    optRestoreContextP context)

/// This is a pointer to a function of the type defined by OP_MODULE_RESTORE_FN

typedef OP_MODULE_RESTORE_FN((*optModuleRestoreFn));

/// Callback used when a processor accesses a memory region (see
/// opBusFetchMonitorAdd)

/// @par Parameters:
/// @par
/// @a processor The processor instance
/// @par
/// @a addr The address being accessed
/// @par
/// @a bytes Number of bytes in the transaction
/// @par
/// @a data Pointer to the data being transferred
/// @par
/// @a userData The user data supplied the the MonitorAdd function
/// @par
/// @a VA The processor virtual address

#define OP_MONITOR_FN(_name) \
void _name ( \
    optProcessorP processor, \
    Addr          addr, \
    Uns32         bytes, \
    const void*   data, \
    void*         userData, \
    Addr          VA)

/// This is a pointer to a function of the type defined by OP_MONITOR_FN

typedef OP_MONITOR_FN((*optMonitorFn));

/// Callback used when a processor stops execution because of an exception
/// (access fault, alignment fault, memory abort or arithmetic exception)

/// @par Parameters:
/// @par
/// @a processor The processor instance
/// @par
/// @a stopReason Exception reason
/// @par
/// @a userData User data supplied to opProcessorStopHandlerAdd

/// @par Returns:
/// Return True if the callback handled the stop reason (so the simulator can
/// continue) or False if the stop reason was not handled. On resumption, the
/// processor will re-execute the faulting instruction.
#define OP_STOP_HANDLER_FN(_name) \
Bool _name ( \
    optProcessorP processor, \
    optStopReason stopReason, \
    void*         userData)

/// This is a pointer to a function of the type defined by OP_STOP_HANDLER_FN

typedef OP_STOP_HANDLER_FN((*optStopHandlerFn));

/// Callback for a command definition, called once for every command from
/// opCommandIterAll and opProcessorCommandIterAll

/// @par Parameters:
/// @par
/// @a command The current command instance
/// @par
/// @a userData The user data passed to opCommandIterAll and
/// opProcessorCommandIterAll

#define OP_COMMAND_FN(_name) \
void _name ( \
    optCommandP command, \
    void*       userData)

/// This is a pointer to a function of the type defined by OP_COMMAND_FN

typedef OP_COMMAND_FN((*optCommandFn));

/// Callback for a command argument definition, called once for every command
/// argument from opCommandArgIterAll

/// @par Parameters:
/// @par
/// @a arg The current command argument
/// @par
/// @a userData The user data passed to opCommandArgIterAll

#define OP_COMMAND_ARG_FN(_name) \
void _name ( \
    optCommandArgP arg, \
    void*          userData)

/// This is a pointer to a function of the type defined by OP_COMMAND_ARG_FN

typedef OP_COMMAND_ARG_FN((*optCommandArgFn));

/// Command parser callback called when a boolean flag is parsed.

/// @par Parameters:
/// @par
/// @a value The boolean value
/// @par
/// @a userData The user data passed to the parser

/// @sa
/// opCmdParserAdd
#define OP_FLAG_BOOL_FN(_name) \
void _name ( \
    Bool  value, \
    Uns32 userData)

/// This is a pointer to a function of the type defined by OP_FLAG_BOOL_FN

typedef OP_FLAG_BOOL_FN((*optFlagBoolFn));

/// Command parser callback called when a double (floating point) flag is
/// parsed.

/// @par Parameters:
/// @par
/// @a value The boolean value
/// @par
/// @a userData The user data passed to opCmdParserAdd

/// @sa
/// opCmdParserAdd
#define OP_FLAG_DOUBLE_FN(_name) \
void _name ( \
    double value, \
    Uns32  userData)

/// This is a pointer to a function of the type defined by OP_FLAG_DOUBLE_FN

typedef OP_FLAG_DOUBLE_FN((*optFlagDoubleFn));

/// Command parser callback called when an integer flag is parsed

/// @par Parameters:
/// @par
/// @a value The Int32 value
/// @par
/// @a userData The user data passed to opCmdParserAdd

/// @sa
/// opCmdParserAdd
#define OP_FLAG_INT32_FN(_name) \
void _name ( \
    Int32 value, \
    Uns32 userData)

/// This is a pointer to a function of the type defined by OP_FLAG_INT32_FN

typedef OP_FLAG_INT32_FN((*optFlagInt32Fn));

/// Command parser callback called when a string flag is parsed.

/// @par Parameters:
/// @par
/// @a value The string value
/// @par
/// @a userData The user data passed to opCmdParserAdd

/// @sa
/// opCmdParserAdd
#define OP_FLAG_STRING_FN(_name) \
void _name ( \
    const char * value, \
    Uns32        userData)

/// This is a pointer to a function of the type defined by OP_FLAG_STRING_FN

typedef OP_FLAG_STRING_FN((*optFlagStringFn));

/// Command parser callback called when a name=value flag is parsed.

/// @par Parameters:
/// @par
/// @a name The name
/// @par
/// @a value The string value
/// @par
/// @a userData The user data passed to opCmdParserAdd

/// @sa
/// opCmdParserAdd
#define OP_FLAG_PAIR_FN(_name) \
void _name ( \
    const char * name, \
    const char * value, \
    Uns32        userData)

/// This is a pointer to a function of the type defined by OP_FLAG_PAIR_FN

typedef OP_FLAG_PAIR_FN((*optFlagPairFn));

/// Command parser callback called when a variable number of arguments is parsed

/// @par Parameters:
/// @par
/// @a argc The number of arguments parsed
/// @par
/// @a argv Array of pointers to the parsed arguments
/// @par
/// @a userData The user data passed to opCmdParserAdd

/// @sa
/// opCmdParserAdd
#define OP_FLAG_ARGV_FN(_name) \
void _name ( \
    Uns32         argc, \
    const char ** argv, \
    Uns32         userData)

/// This is a pointer to a function of the type defined by OP_FLAG_ARGV_FN

typedef OP_FLAG_ARGV_FN((*optFlagArgvFn));

/// Command parser callback called for name=value list flag

/// @par Parameters:
/// @par
/// @a argc The number of arguments parsed
/// @par
/// @a argn Array of pointers to the parsed names
/// @par
/// @a argv Array of pointers to the parsed values
/// @par
/// @a userData The user data passed to opCmdParserAdd

/// @sa
/// opCmdParserAdd
#define OP_FLAG_ARGV_PAIR_FN(_name) \
void _name ( \
    Uns32         argc, \
    const char ** argn, \
    const char ** argv, \
    Uns32         userData)

/// This is a pointer to a function of the type defined by OP_FLAG_ARGV_PAIR_FN

typedef OP_FLAG_ARGV_PAIR_FN((*optFlagArgvPairFn));

/// Command parser callback called for an unsigned 64 integer flag (also used
/// for an address).

/// @par Parameters:
/// @par
/// @a value The Uns64 value
/// @par
/// @a userData The user data passed to opCmdParserAdd

/// @sa
/// opCmdParserAdd
#define OP_FLAG_UNS64_FN(_name) \
void _name ( \
    Uns64 value, \
    Uns32 userData)

/// This is a pointer to a function of the type defined by OP_FLAG_UNS64_FN

typedef OP_FLAG_UNS64_FN((*optFlagUns64Fn));

/// Called for each file found that matches the given VLNV pattern passed to
/// opVLNVIter

/// @par Parameters:
/// @par
/// @a path Fully expanded path to the file
/// @par
/// @a vendor Vendor component of the file
/// @par
/// @a library Library component of the file
/// @par
/// @a name Name component of the file
/// @par
/// @a version Version component of the file
/// @par
/// @a userData The user data passed to opVLNVIter

/// @sa
/// opVLNVIter
#define OP_FILE_FN(_name) \
void _name ( \
    const char * path, \
    const char * vendor, \
    const char * library, \
    const char * name, \
    const char * version, \
    void*        userData)

/// This is a pointer to a function of the type defined by OP_FILE_FN

typedef OP_FILE_FN((*optFileFn));

/// Notifier function called for register changes. Use this function to filter
/// or refine a watchpoint condition.

/// @par Parameters:
/// @par
/// @a watchpoint The processor with the register change
/// @par
/// @a processor The processor with the register change
/// @par
/// @a userData The user data passed to opProcessorRegWatchpointNew

/// @par Returns:
/// If this function returns true, simulation will continue, otherwise the
/// simulator will return to its caller.
/// @sa
/// opProcessorRegWatchpointNew
#define OP_PROC_WATCHPOINT_CONDITION_FN(_name) \
Bool _name ( \
    optWatchpointP watchpoint, \
    optProcessorP  processor, \
    void*          userData)

/// This is a pointer to a function of the type defined by
/// OP_PROC_WATCHPOINT_CONDITION_FN

typedef OP_PROC_WATCHPOINT_CONDITION_FN((*optProcWatchpointConditionFn));

/// Memory watchpoint notification callback. Use this function to filter or
/// refine a watchpoint condition.

/// @par Parameters:
/// @par
/// @a processor The active processor
/// @par
/// @a watchpoint Handle to the watchpoint
/// @par
/// @a PA The processor physical address
/// @par
/// @a VA The processor virtual address
/// @par
/// @a bytes Number of bytes in the transaction
/// @par
/// @a userData The user data passed to the function that installed the callback
/// @par
/// @a value Pointer to the data

/// @par Returns:
/// If this function returns true, simulation will continue, otherwise the
/// simulator will return to its caller.
/// @sa
/// opProcessorAccessWatchpointNew
/// opProcessorWriteWatchpointNew
/// opProcessorReadWatchpointNew
#define OP_ADDR_WATCHPOINT_CONDITION_FN(_name) \
Bool _name ( \
    optProcessorP  processor, \
    optWatchpointP watchpoint, \
    Addr           PA, \
    Addr           VA, \
    Uns32          bytes, \
    void*          userData, \
    void*          value)

/// This is a pointer to a function of the type defined by
/// OP_ADDR_WATCHPOINT_CONDITION_FN

typedef OP_ADDR_WATCHPOINT_CONDITION_FN((*optAddrWatchpointConditionFn));

/// Command parser error handler function. Called when a flag or argument is not
/// recognized

/// @par Parameters:
/// @par
/// @a flag The name of the flag being parsed when the error was encountered
/// @par
/// @a userData The user data passed to the function that installed the callback

/// @par Returns:
/// If this function returns true, the handler has processed the flag, so the
/// parser will be quiet. If not, the default error message will be printed
/// @sa
/// opCmdErrorHandler
#define OP_CMD_ERROR_HANDLER_FN(_name) \
Bool _name ( \
    const char * flag, \
    void*        userData)

/// This is a pointer to a function of the type defined by
/// OP_CMD_ERROR_HANDLER_FN

typedef OP_CMD_ERROR_HANDLER_FN((*optCmdErrorHandlerFn));

/// Callback for each processor.

/// @par Parameters:
/// @par
/// @a processor The processor instance
/// @par
/// @a userData The user data passed to the function that installed the callback

/// @sa
/// opProcessorIterChildren
/// opProcessorIterDescendants
/// opProcessorIterAll
#define OP_PROCESSOR_ITERATOR_FN(_name) \
void _name ( \
    optProcessorP processor, \
    void*         userData)

/// This is a pointer to a function of the type defined by
/// OP_PROCESSOR_ITERATOR_FN

typedef OP_PROCESSOR_ITERATOR_FN((*optProcessorIteratorFn));

/// This function is called when opSessionExit is called.

/// @sa
/// opSessionAtExit
#define OP_EXIT_FN(_name) \
void _name ( void)

/// This is a pointer to a function of the type defined by OP_EXIT_FN

typedef OP_EXIT_FN((*optExitFn));

/// Callback implementing memory read.

/// @par Parameters:
/// @par
/// @a initiator The model that is initiating the read
/// @par
/// @a addr The physical address being accessed
/// @par
/// @a bytes Number of bytes in this transaction
/// @par
/// @a data Pointer to the data being read or written
/// @par
/// @a userData The user data passed to opBusSlaveNew
/// @par
/// @a VA Virtual address being accessed
/// @par
/// @a isFetch True if the processor is fetching code

/// @sa
/// opBusSlaveNew
#define OP_BUS_SLAVE_READ_FN(_name) \
void _name ( \
    optObjectP initiator, \
    Addr       addr, \
    Uns32      bytes, \
    void*      data, \
    void*      userData, \
    Addr       VA, \
    Bool       isFetch)

/// This is a pointer to a function of the type defined by OP_BUS_SLAVE_READ_FN

typedef OP_BUS_SLAVE_READ_FN((*optBusSlaveReadFn));

/// Callback implementing memory write

/// @par Parameters:
/// @par
/// @a initiator The model that is initiating the write
/// @par
/// @a addr The physical address being accessed
/// @par
/// @a bytes Number of bytes in this transaction
/// @par
/// @a data Pointer to the data being read or written
/// @par
/// @a userData The user data passed to opBusSlaveNew
/// @par
/// @a VA Virtual address being accessed

#define OP_BUS_SLAVE_WRITE_FN(_name) \
void _name ( \
    optObjectP  initiator, \
    Addr        addr, \
    Uns32       bytes, \
    const void* data, \
    void*       userData, \
    Addr        VA)

/// This is a pointer to a function of the type defined by OP_BUS_SLAVE_WRITE_FN

typedef OP_BUS_SLAVE_WRITE_FN((*optBusSlaveWriteFn));

/// Return each bus port definition

/// @par Parameters:
/// @par
/// @a module current module
/// @par
/// @a object Pointer to space allocated for persistent data in this module.
/// @par
/// @a prev current port

/// @par Returns:
/// Must return the next object (null if there are no more)
#define OP_BUS_PORT_FN(_name) \
optBusPortInfoP _name ( \
    optModuleP       module, \
    optModuleObjectP object, \
    optBusPortInfoP  prev)

/// This is a pointer to a function of the type defined by OP_BUS_PORT_FN

typedef OP_BUS_PORT_FN((*optBusPortFn));

/// Set the module diagnostics

/// @par Parameters:
/// @par
/// @a mi This module instance
/// @par
/// @a object Pointer to space allocated for persistent data in this module.
/// @par
/// @a level New diagnostic level (values > 15 will turn on system diagnostics)

#define OP_DIAG_SET_FN(_name) \
void _name ( \
    optModuleP       mi, \
    optModuleObjectP object, \
    Uns32            level)

/// This is a pointer to a function of the type defined by OP_DIAG_SET_FN

typedef OP_DIAG_SET_FN((*optDiagSetFn));

/// Return each FIFO port definition

/// @par Parameters:
/// @par
/// @a module current module
/// @par
/// @a object Pointer to space allocated for persistent data in this module.
/// @par
/// @a prev current port

/// @par Returns:
/// Must return the next object (null if there are no more)
#define OP_FIFOPORT_FN(_name) \
optFIFOPortInfoP _name ( \
    optModuleP       module, \
    optModuleObjectP object, \
    optFIFOPortInfoP prev)

/// This is a pointer to a function of the type defined by OP_FIFOPORT_FN

typedef OP_FIFOPORT_FN((*optFIFOPortFn));

/// Return the next net port definition

/// @par Parameters:
/// @par
/// @a module current module
/// @par
/// @a object Pointer to space allocated for persistent data in this module.
/// @par
/// @a prev current port information structure

/// @par Returns:
/// Must return the next object (null if there are no more)
#define OP_NET_PORT_FN(_name) \
optNetPortInfoP _name ( \
    optModuleP       module, \
    optModuleObjectP object, \
    optNetPortInfoP  prev)

/// This is a pointer to a function of the type defined by OP_NET_PORT_FN

typedef OP_NET_PORT_FN((*optNetPortFn));

/// Return the next packetnet port definition

/// @par Parameters:
/// @par
/// @a module current module
/// @par
/// @a object Pointer to space allocated for persistent data in this module.
/// @par
/// @a prev current port information structure

/// @par Returns:
/// Must return the next object (null if there are no more)
#define OP_PACKETNET_PORT_FN(_name) \
optPacketnetPortInfoP _name ( \
    optModuleP            module, \
    optModuleObjectP      object, \
    optPacketnetPortInfoP prev)

/// This is a pointer to a function of the type defined by OP_PACKETNET_PORT_FN

typedef OP_PACKETNET_PORT_FN((*optPacketnetPortFn));

/// Return each formal parameter specification

/// @par Parameters:
/// @par
/// @a module current module
/// @par
/// @a prev current parameter

/// @par Returns:
/// Must return the next object (null if there are no more)
#define OP_PARAM_SPEC_FN(_name) \
optParamSpecP _name ( \
    optModuleP    module, \
    optParamSpecP prev)

/// This is a pointer to a function of the type defined by OP_PARAM_SPEC_FN

typedef OP_PARAM_SPEC_FN((*optParamSpecFn));

/// Callback for quitting the simulator.

/// @par Parameters:
/// @par
/// @a status The reason for quitting
/// @par
/// @a userData The user data passed to opSessionTextRedirect

/// @sa
/// opSessionTextRedirect
#define OP_QUIT_FN(_name) \
void _name ( \
    Int32 status, \
    void* userData)

/// This is a pointer to a function of the type defined by OP_QUIT_FN

typedef OP_QUIT_FN((*optQuitFn));

/// Callback used in a debugger integration. Called when simulation starts for
/// the first time

/// @par Parameters:
/// @par
/// @a module The current root module
/// @par
/// @a userData The user data passed to opSessionDebuggerNotifiersAdd

/// @sa
/// opSessionDebuggerNotifiersAdd
#define OP_SIMULATE_START_FN(_name) \
void _name ( \
    optModuleP module, \
    void*      userData)

/// This is a pointer to a function of the type defined by OP_SIMULATE_START_FN

typedef OP_SIMULATE_START_FN((*optSimulateStartFn));

/// Callback used in a debugger integration. Called after the execution of each
/// processor slice

/// @par Parameters:
/// @par
/// @a processor The current processor
/// @par
/// @a userData The user data passed to opSessionDebuggerNotifiersAdd

/// @par Returns:
/// Return True if simulation is to continue, False if it is to finish
/// @sa
/// opSessionDebuggerNotifiersAdd
#define OP_SIMULATE_POST_PROCESSOR_FN(_name) \
Bool _name ( \
    optProcessorP processor, \
    void*         userData)

/// This is a pointer to a function of the type defined by
/// OP_SIMULATE_POST_PROCESSOR_FN

typedef OP_SIMULATE_POST_PROCESSOR_FN((*optSimulatePostProcessorFn));

/// Callback used in a debugger integration. Called after each PSE execution

/// @par Parameters:
/// @par
/// @a peripheral The current peripheral
/// @par
/// @a userData The user data passed to opSessionDebuggerNotifiersAdd

/// @par Returns:
/// Must return True if simulation is to continue, False if it is to finish
/// @sa
/// opSessionDebuggerNotifiersAdd
#define OP_SIMULATE_POST_PERIPH_FN(_name) \
Bool _name ( \
    optPeripheralP peripheral, \
    void*          userData)

/// This is a pointer to a function of the type defined by
/// OP_SIMULATE_POST_PERIPH_FN

typedef OP_SIMULATE_POST_PERIPH_FN((*optSimulatePostPeriphFn));

/// Callback used in a debugger integration. Called at the end of simulation

/// @par Parameters:
/// @par
/// @a processor The current processor
/// @par
/// @a userData The user data passed to opSessionDebuggerNotifiersAdd

/// @sa
/// opSessionDebuggerNotifiersAdd
#define OP_SIMULATE_END_FN(_name) \
void _name ( \
    optProcessorP processor, \
    void*         userData)

/// This is a pointer to a function of the type defined by OP_SIMULATE_END_FN

typedef OP_SIMULATE_END_FN((*optSimulateEndFn));

/// Callback used in a debugger integration. Called each time simulation time is
/// advanced

/// @par Parameters:
/// @par
/// @a info The reason for time being advanced
/// @par
/// @a userData The user data passed to opSessionDebuggerNotifiersAdd

/// @par Returns:
/// Must return True if simulation is to continue, False if it is to finish
/// @sa
/// opSessionDebuggerNotifiersAdd
#define OP_SIMULATE_TIME_ADVANCE_FN(_name) \
Bool _name ( \
    optAdvanceTimeInfo info, \
    void*              userData)

/// This is a pointer to a function of the type defined by
/// OP_SIMULATE_TIME_ADVANCE_FN

typedef OP_SIMULATE_TIME_ADVANCE_FN((*optSimulateTimeAdvanceFn));

/// Callback for text output (opMessage etc).

/// @par Parameters:
/// @par
/// @a text The text being sent
/// @par
/// @a userData The user data passed to opSessionTextRedirect

/// @sa
/// opSessionTextRedirect
#define OP_TEXT_OUTPUT_FN(_name) \
void _name ( \
    const char * text, \
    void*        userData)

/// This is a pointer to a function of the type defined by OP_TEXT_OUTPUT_FN

typedef OP_TEXT_OUTPUT_FN((*optTextOutputFn));

/// Callback for timed trigger.

/// @par Parameters:
/// @par
/// @a now The current simulation time
/// @par
/// @a mi The current root module
/// @par
/// @a userData The user data passed to opModuleTriggerAdd

/// @sa
/// opModuleTriggerAdd
#define OP_TRIGGER_FN(_name) \
void _name ( \
    optTime    now, \
    optModuleP mi, \
    void*      userData)

/// This is a pointer to a function of the type defined by OP_TRIGGER_FN

typedef OP_TRIGGER_FN((*optTriggerFn));

/// Called when a net is written.

/// @par Parameters:
/// @par
/// @a userData The user data passed to opNetWriteMonitorAdd
/// @par
/// @a value The value being written to the net.

/// @sa
/// opNetWriteMonitorAdd
#define OP_NET_WRITE_FN(_name) \
void _name ( \
    void* userData, \
    Uns64 value)

/// This is a pointer to a function of the type defined by OP_NET_WRITE_FN

typedef OP_NET_WRITE_FN((*optNetWriteFn));

/// Called when a packetnet is written.

/// @par Parameters:
/// @par
/// @a data Pointer to the data passed from transmitter
/// @par
/// @a bytes Number of bytes sent
/// @par
/// @a userData The user data pointer passed to opPacketnetWriteMonitorAdd

/// @sa
/// opPacketnetWriteMonitorAdd
#define OP_PACKETNET_WRITE_FN(_name) \
void _name ( \
    void* data, \
    Uns32 bytes, \
    void* userData)

/// This is a pointer to a function of the type defined by OP_PACKETNET_WRITE_FN

typedef OP_PACKETNET_WRITE_FN((*optPacketnetWriteFn));

/// Called to save a model state.

/// @par Parameters:
/// @par
/// @a data Pointer to data to be saved (written to the storage medium).
/// @par
/// @a bytes Number of bytes to be saved
/// @par
/// @a userData The user data passed to the SaveState function

/// @par Returns:
/// This callback should return True if the data was saved successfully
#define OP_SAVE_FN(_name) \
Bool _name ( \
    void* data, \
    Uns32 bytes, \
    void* userData)

/// This is a pointer to a function of the type defined by OP_SAVE_FN

typedef OP_SAVE_FN((*optSaveFn));

/// Called when shared data object is triggered

/// @par Parameters:
/// @par
/// @a userObject Handle of object
/// @par
/// @a ret Write a return value to this, if required
/// @par
/// @a id Shared data ID
/// @par
/// @a userData The user data passed to the installer

#define OP_SHARED_DATA_LISTENER_FN(_name) \
void _name ( \
    void*  userObject, \
    Int32* ret, \
    Int32  id, \
    void*  userData)

/// This is a pointer to a function of the type defined by
/// OP_SHARED_DATA_LISTENER_FN

typedef OP_SHARED_DATA_LISTENER_FN((*optSharedDataListenerFn));

/// Called to restore a model state.

/// @par Parameters:
/// @par
/// @a data Pointer to data to be restored (read back from the storage medium).
/// @par
/// @a bytes Number of bytes to be restored.
/// @par
/// @a userData The user data passed to the RestoreState function

/// @par Returns:
/// This callback should return True if the data was restored successfully
#define OP_RESTORE_FN(_name) \
Bool _name ( \
    void* data, \
    Uns32 bytes, \
    void* userData)

/// This is a pointer to a function of the type defined by OP_RESTORE_FN

typedef OP_RESTORE_FN((*optRestoreFn));

/// Notifier function called when a dynamic port is mapped or unmapped.

/// @par Parameters:
/// @par
/// @a userData The user data passed to opBusPortConnMapNotify
/// @par
/// @a addrLo The lower address limit of the region being mapped
/// @par
/// @a addrHi The upper address limit of the region being mapped
/// @par
/// @a map True if the region is being mapped, false if the region is being
/// unmapped

/// @sa
/// opBusPortConnMapNotify
#define OP_PORT_MAP_FN(_name) \
void _name ( \
    void* userData, \
    Addr  addrLo, \
    Addr  addrHi, \
    Bool  map)

/// This is a pointer to a function of the type defined by OP_PORT_MAP_FN

typedef OP_PORT_MAP_FN((*optPortMapFn));

/// Notifier function called when a serial port is opened.

/// @par Parameters:
/// @par
/// @a peripheral The peripheral
/// @par
/// @a port The new port number
/// @par
/// @a channel The serial channel
/// @par
/// @a userData User data supplied to the installer

#define OP_SERIAL_OPEN_FN(_name) \
void _name ( \
    optPeripheralP peripheral, \
    Uns32          port, \
    Uns32          channel, \
    void*          userData)

/// This is a pointer to a function of the type defined by OP_SERIAL_OPEN_FN

typedef OP_SERIAL_OPEN_FN((*optSerialOpenFn));

/// Notifier function called after a bus has been constructed or before it is
/// destroyed

/// @par Parameters:
/// @par
/// @a object The new bus
/// @par
/// @a userData The user data supplied to the installer

#define OP_DEST_BRIDGE_FN(_name) \
void _name ( \
    optBridgeP object, \
    void*      userData)

/// This is a pointer to a function of the type defined by OP_DEST_BRIDGE_FN

typedef OP_DEST_BRIDGE_FN((*optDestBridgeFn));

/// Notifier function called after a bridge has been constructed or before it is
/// destroyed

/// @par Parameters:
/// @par
/// @a object The new bridge
/// @par
/// @a userData The user data supplied to the installer

#define OP_DEST_BUS_FN(_name) \
void _name ( \
    optBusP object, \
    void*   userData)

/// This is a pointer to a function of the type defined by OP_DEST_BUS_FN

typedef OP_DEST_BUS_FN((*optDestBusFn));

/// Notifier function called after a FIFO has been constructed or before it is
/// destroyed

/// @par Parameters:
/// @par
/// @a object The new FIFO
/// @par
/// @a userData The user data supplied to the installer

#define OP_DEST_FIFOFN(_name) \
void _name ( \
    optFIFOP object, \
    void*    userData)

/// This is a pointer to a function of the type defined by OP_DEST_FIFOFN

typedef OP_DEST_FIFOFN((*optDestFIFOFn));

/// Notifier function called after a net has been constructed or before it is
/// destroyed

/// @par Parameters:
/// @par
/// @a object The new net
/// @par
/// @a userData The user data supplied to the installer

#define OP_DEST_NET_FN(_name) \
void _name ( \
    optNetP object, \
    void*   userData)

/// This is a pointer to a function of the type defined by OP_DEST_NET_FN

typedef OP_DEST_NET_FN((*optDestNetFn));

/// Notifier function called after a packetnet has been constructed or before it
/// is destroyed

/// @par Parameters:
/// @par
/// @a object The new packetnet
/// @par
/// @a userData The user data supplied to the installer

#define OP_DEST_PACKETNET_FN(_name) \
void _name ( \
    optPacketnetP object, \
    void*         userData)

/// This is a pointer to a function of the type defined by OP_DEST_PACKETNET_FN

typedef OP_DEST_PACKETNET_FN((*optDestPacketnetFn));

/// Notifier function called after a busPortConn has been constructed or before
/// it is destroyed

/// @par Parameters:
/// @par
/// @a object The new busPortConn
/// @par
/// @a userData The user data supplied to the installer

#define OP_DEST_BUS_PORT_CONN_FN(_name) \
void _name ( \
    optBusPortConnP object, \
    void*           userData)

/// This is a pointer to a function of the type defined by
/// OP_DEST_BUS_PORT_CONN_FN

typedef OP_DEST_BUS_PORT_CONN_FN((*optDestBusPortConnFn));

/// Notifier function called after a FIFOPortConn has been constructed or before
/// it is destroyed

/// @par Parameters:
/// @par
/// @a object The new FIFOPortConn
/// @par
/// @a userData The user data supplied to the installer

#define OP_DEST_FIFOPORT_CONN_FN(_name) \
void _name ( \
    optFIFOPortConnP object, \
    void*            userData)

/// This is a pointer to a function of the type defined by
/// OP_DEST_FIFOPORT_CONN_FN

typedef OP_DEST_FIFOPORT_CONN_FN((*optDestFIFOPortConnFn));

/// Notifier function called after a netPortConn has been constructed or before
/// it is destroyed

/// @par Parameters:
/// @par
/// @a object The new netPortConn
/// @par
/// @a userData The user data supplied to the installer

#define OP_DEST_NET_PORT_CONN_FN(_name) \
void _name ( \
    optNetPortConnP object, \
    void*           userData)

/// This is a pointer to a function of the type defined by
/// OP_DEST_NET_PORT_CONN_FN

typedef OP_DEST_NET_PORT_CONN_FN((*optDestNetPortConnFn));

/// Notifier function called after a packetnetPortConn has been constructed or
/// before it is destroyed

/// @par Parameters:
/// @par
/// @a object The new packetnetPortConn
/// @par
/// @a userData The user data supplied to the installer

#define OP_DEST_PACKETNET_PORT_CONN_FN(_name) \
void _name ( \
    optPacketnetPortConnP object, \
    void*                 userData)

/// This is a pointer to a function of the type defined by
/// OP_DEST_PACKETNET_PORT_CONN_FN

typedef OP_DEST_PACKETNET_PORT_CONN_FN((*optDestPacketnetPortConnFn));

/// Notifier function called after an memory has been constructed or before it
/// is destroyed

/// @par Parameters:
/// @par
/// @a object The new memory

#define OP_DEST_MEMORY_FN(_name) \
void _name ( \
    optMemoryP object, \
    void*      userData)

/// This is a pointer to a function of the type defined by OP_DEST_MEMORY_FN

typedef OP_DEST_MEMORY_FN((*optDestMemoryFn));

/// Notifier function called after an MMC has been constructed or before it is
/// destroyed

/// @par Parameters:
/// @par
/// @a object The new MMC

#define OP_DEST_MMCFN(_name) \
void _name ( \
    optMMCP object, \
    void*   userData)

/// This is a pointer to a function of the type defined by OP_DEST_MMCFN

typedef OP_DEST_MMCFN((*optDestMMCFn));

/// Notifier function called after a module has been constructed or before it is
/// destroyed

/// @par Parameters:
/// @par
/// @a object The new module
/// @par
/// @a userData The user data supplied to the installer

#define OP_DEST_MODULE_FN(_name) \
void _name ( \
    optModuleP object, \
    void*      userData)

/// This is a pointer to a function of the type defined by OP_DEST_MODULE_FN

typedef OP_DEST_MODULE_FN((*optDestModuleFn));

/// Notifier function called after a peripheral has been constructed or before
/// it is destroyed

/// @par Parameters:
/// @par
/// @a object The new peripheral
/// @par
/// @a userData The user data supplied to the installer

#define OP_DEST_PERIPHERAL_FN(_name) \
void _name ( \
    optPeripheralP object, \
    void*          userData)

/// This is a pointer to a function of the type defined by OP_DEST_PERIPHERAL_FN

typedef OP_DEST_PERIPHERAL_FN((*optDestPeripheralFn));

/// Notifier function called after a processor has been constructed or before it
/// is destroyed

/// @par Parameters:
/// @par
/// @a object The new processor
/// @par
/// @a userData The user data supplied to the installer

#define OP_DEST_PROCESSOR_FN(_name) \
void _name ( \
    optProcessorP object, \
    void*         userData)

/// This is a pointer to a function of the type defined by OP_DEST_PROCESSOR_FN

typedef OP_DEST_PROCESSOR_FN((*optDestProcessorFn));



////////////////////////////////////////////////////////////////////////////////
// Public structures
////////////////////////////////////////////////////////////////////////////////

/// @struct optDestCallbacksS
/// Structure containing object construction and destruction callbacks

typedef struct optDestCallbacksS {
    optDestProcessorFn         processor        ; ///< callback
    optDestBridgeFn            bridge           ; ///< callback
    optDestBusFn               bus              ; ///< callback
    optDestBusPortConnFn       busPortConn      ; ///< callback
    optDestFIFOFn              FIFO             ; ///< callback
    optDestFIFOPortConnFn      FIFOPortConn     ; ///< callback
    optDestMemoryFn            memory           ; ///< callback
    optDestMMCFn               MMC              ; ///< callback
    optDestModuleFn            module           ; ///< callback
    optDestNetFn               net              ; ///< callback
    optDestNetPortConnFn       netPortConn      ; ///< callback
    optDestPacketnetFn         packetnet        ; ///< callback
    optDestPacketnetPortConnFn packetnetPortConn; ///< callback
    optDestPeripheralFn        peripheral       ; ///< callback
} optDestCallbacks;

/// @struct optBusPortConnectS
/// Used in the Connection structure. Describes the connection of a bus port to a bus

typedef struct optBusPortConnectS {
    optBusP      bus     ; ///< The bus instance
    const char * portName; ///< The name of the bus port on the instance
    Addr         addrLo  ; ///< Optional lower address
    Addr         addrHi  ; ///< Optional upper address
    Bool         slave   ; ///< True if this is a slave port
    Bool         dynamic ; ///< True if this is a dynamic slave port (this this case addrLo and addrHi are not required)
} optBusPortConnect;

/// @struct optNetPortConnectS
/// Used in the Connection structure. Describes the connection of a net port to a net

typedef struct optNetPortConnectS {
    optNetP      net     ; ///< The net instance
    const char * portName; ///< The name of the net port on the instance
} optNetPortConnect;

/// @struct optPacketnetPortConnectS
/// Used in the Connection structure. Describes the connection of a packetnet port to a packetnet

typedef struct optPacketnetPortConnectS {
    optPacketnetP packetnet; ///< The packetnet instance
    const char *  portName ; ///< The name of the packetnet port on the instance
} optPacketnetPortConnect;

/// @struct optFIFOPortConnectS
/// Used in the Connection structure. Describes the connection of a FIFO port to a FIFO

typedef struct optFIFOPortConnectS {
    optFIFOP     FIFO    ; ///< The FIFO instance
    const char * portName; ///< The name of the FIFO port on the instance
} optFIFOPortConnect;

/// @struct optBusPortInfoS
/// Definition of a module bus port

typedef struct optBusPortInfoS {
    const char * name       ; ///< Bus port name
    const char * description; ///< Bus port description
    Bool         mustConnect; ///< True if this port must be connected
} optBusPortInfo;

/// @struct optFIFOPortInfoS
/// Definition of a module FIFO port

typedef struct optFIFOPortInfoS {
    const char *   name       ; ///< FIFO port name
    const char *   description; ///< FIFO port description
    optBusPortType type       ; ///< input or output
    Bool           mustConnect; ///< True if this port must be connected
    Uns32          width      ; ///< Number of bits in a FIFO word
} optFIFOPortInfo;

/// @struct optNetPortInfoS
/// Definition of a module net port

typedef struct optNetPortInfoS {
    const char *   name       ; ///< Net port name
    const char *   description; ///< Net port description
    optNetPortType type       ; ///< input, output or inout
    Bool           mustConnect; ///< True if this port must be connected
} optNetPortInfo;

/// @struct optEnumParamSpecS
/// Definition of a module formal parameter enumerated value

typedef struct optEnumParamSpecS {
    const char * name       ; ///< Enumeration name
    const char * description; ///< Enumeration description
    Uns32        value      ; ///< The enumeration value
} optEnumParamSpec;

/// @struct optMemorySpecS
/// Definition of a memory after parsing a memory spec string

typedef struct optMemorySpecS {
    char    name[32]; ///< Memory name
    Addr    addrLo  ; ///< The lower address limit
    Addr    addrHi  ; ///< The upper address limit
    optPriv priv    ; ///< Read/write execute privilege
    Bool    shared  ; ///< The memory should be shared
} optMemorySpec;

/// @struct optParamSpecS
/// Definition of a module formal parameter

typedef struct optParamSpecS {
    const char *       name       ; ///< Formal parameter name
    const char *       description; ///< Formal parameter  description
    optParamSpecGroupP group      ; ///< optional group structure
    optParamType       type       ; ///< Formal parameter  type
    union {
        struct {
            Bool defaultValue; 
        } boolSpec;

        struct {
            double defaultValue; ///< default value of a double parameter
            double min         ; ///< minimum allowed value of a double parameter
            double max         ; ///< maximum allowed value of a double parameter
        } doubleSpec;

        struct {
            optEnumParamSpecP legalValues ; ///< Array of enumerations
            optEnumParamSpecP defaultValue; ///< The default enumeration. If null, then the first enumeration if the default
        } enumSpec;

        struct {
            Int32 defaultValue; ///< default value of an int32 parameter
            Int32 min         ; ///< minimum allowed value of an int32 parameter
            Int32 max         ; ///< maximum allowed value of an int32 parameter
        } int32Spec;

        struct {
            Int64 defaultValue; ///< default value of an int64 parameter
            Int64 min         ; ///< minimum allowed value of an int64 parameter
            Int64 max         ; ///< maximum allowed value of an int64 parameter
        } int64Spec;

        struct {
            Uns32 defaultValue; ///< default value of an uns32 parameter
            Uns32 min         ; ///< minimum allowed value of an uns32 parameter
            Uns32 max         ; ///< maximum allowed value of an uns32 parameter
        } uns32Spec;

        struct {
            Uns64 defaultValue; ///< default value of an uns64 parameter
            Uns64 min         ; ///< minimum allowed value of an uns64 parameter
            Uns64 max         ; ///< maximum allowed value of an uns64 parameter
        } uns64Spec;

        struct {
            const char * defaultValue; 
            Uns32        maxLength   ; 
        } stringSpec;

    } spec;

} optParamSpec;

/// @struct optParamArrayS
/// Definition of a parameter

typedef struct optParamArrayS {
    const char * name; ///< Parameter name
    optParamType type; ///< Parameter type
    union {
        Bool         boolValue   ; 
        double       doubleValue ; 
        const char * enumValue   ; 
        optEndian    endianValue ; 
        void*        pointerValue; 
        const char * stringValue ; 
        Int32        int32Value  ; 
        Int64        int64Value  ; 
        Uns32        uns32Value  ; 
        Uns64        uns64Value  ; 
    } u;

} optParamArray;

/// @struct optPacketnetPortInfoS
/// Definition of a module packetnet port

typedef struct optPacketnetPortInfoS {
    const char *   name       ; ///< Packetnet port name
    const char *   description; ///< Packetnet port description
    optNetPortType type       ; ///< input, output or inout
    Bool           mustConnect; ///< True if this port must be connected
    Uns32          bytes      ; ///< Maximum number of bytes in a packet
} optPacketnetPortInfo;

/// @struct optConnectionsS
/// Structure used to pass lists of connections when creating an instance.

typedef struct optConnectionsS {
    optBusPortConnectP       busPortConns      ; ///< Pointer to a null terminated array of bus port connections
    optNetPortConnectP       netPortConns      ; ///< Pointer to a null terminated array of net port connections
    optPacketnetPortConnectP packetnetPortConns; ///< Pointer to a null terminated array of packetnet port connections
    optFIFOPortConnectP      fifoPortConns     ; ///< Pointer to a null terminated array of FIFO port connections
} optConnections;

/// @struct optDebuggerNotifiersS
/// Callbacks required by a debugger integration. By implementing and installing these functions, the user's code can take control of the simulator and support stepping, break and watch points, memory and register examination an modification.

typedef struct optDebuggerNotifiersS {
    optSimulateStartFn         start            ; ///< Callback into a debugger at the start of simulation
    optSimulateStartFn         endPeripheralCons; ///< Callback into a debugger before PSE constructors have run
    optSimulateStartFn         endPlatformCons  ; ///< Callback into a debugger after platform constructor has run
    optSimulateStartFn         endCons          ; ///< Callback into a debugger after all constructors have run
    optSimulatePostProcessorFn postProcessor    ; ///< Callback into a debugger after processor has executed a slice
    optSimulatePostPeriphFn    postPeripheral   ; ///< Callback into a debugger after peripheral has completed a callback or thread
    optSimulateTimeAdvanceFn   advance          ; ///< Callback into a debugger when time advances
    optSimulateEndFn           end              ; ///< Callback into a debugger at end of simulation
    void*                      userData         ; ///< The user data, passed to each callback
} optDebuggerNotifiers;

/// @struct optObjectInfoS
/// Object file information, filled by 

typedef struct optObjectInfoS {
    Addr        entry       ; ///< Program entry point
    Addr        loadAddress ; ///< Program load address
    Addr        headerOffset; ///< Offset of program header
    Uns32       headerEntry ; ///< Program header entry
    Uns32       headerNumber; ///< Number of program headers
    const char* interpreter ; ///< Path to required interpreter if required. String is not persistent
    Uns16       cpuType     ; ///< Processor architecture ELF code, COFF code, etc.
    Uns16       cpuSupp     ; ///< Processor supplementary type (not used yet).
    optEndian   endian      ; ///< Enumerated type; processor endian.
} optObjectInfo;

/// @struct optModuleAttrS
/// This in the module entry point. Each module must have one global instance of this structure called 'modelattrs'

typedef struct optModuleAttrS {
    const char*           versionString       ; ///< Version string. Must be set to the macro OP_VERSION
    optModelType          type                ; ///< MUST be set to the macro OP_MODULE
    const char*           name                ; ///< The default instance name for this module
    Uns32                 objectSize          ; ///< Number of bytes to allocate for private data for each instance
    optVisibility         visibility          ; ///< Controls the ability of to  introspect this model
    optReleaseStatus      releaseStatus       ; ///< Model release status, used by the packaging system
    optPurpose            purpose             ; ///< Model purpose, used by the packaging system
    Bool                  saveRestoreSupported; ///< Set to true if save/restore is fully supported
    struct {
        const char * vendor ; 
        const char * library; 
        const char * name   ; 
        const char * version; 
    } vlnv;

    optConstructFn        constructCB         ; ///< The module constructor which must be supplied.
    optPostConstructFn    postConstructCB     ; ///< Called after construction
    optPreSimulateFn      preSimulateCB       ; ///< Called immediately before simulation begins
    optSimulateStartingFn simulateCB          ; ///< Called each time simulation begins
    optPostSimulateFn     postSimulateCB      ; ///< Called after simulation, before destruction begins
    optDestructFn         destructCB          ; ///< Free any objects not known to the simulator
    optModuleSaveFn       saveCB              ; ///< Save the state of this module
    optModuleRestoreFn    restoreCB           ; ///< Restore the state of this module
    optBusPortFn          busPortSpecsCB      ; ///< Return (in turn) each bus port definition
    optFIFOPortFn         FIFOPortSpecsCB     ; ///< Return (in turn) each FIFO port definition
    optNetPortFn          netPortSpecsCB      ; ///< Return (in turn) each net port definition
    optPacketnetPortFn    packetnetPortSpecsCB; ///< Return (in turn) each packetnet port definition
    optParamSpecFn        paramSpecsCB        ; ///< Return (in turn) each formal parameter
    optDiagSetFn          diagSetCB           ; ///< Called after construction to change the diagnostic level of this module
} optModuleAttr;

/// @struct optArgStringListS
/// List of string arguments or name-value pairs

typedef struct optArgStringListS {
    optArgStringListP next ; ///< Linked list
    const char*       value; ///< mandatory value
    const char*       name ; ///< optional name
} optArgStringList;

/// @struct optParamSpecGroupS
/// Formal parameter group. A group of formals can point to this to form a group

typedef struct optParamSpecGroupS {
    const char* name       ; 
    const char* description; 
    void*       params     ; 
} optParamSpecGroup;

/// @struct optPersonalityS
/// Override the simulator personality with one of more of these

typedef struct optPersonalityS {
    const char* name             ; 
    const char* licenses         [4]; 
    const char* licenseFile      ; 
    const char* productName      ; 
    const char* vendor           ; 
    const char* advert           ; 
    const char* getLicenseString ; 
    const char* noLicenseString  ; 
    const char* licenseEnvVar    ; 
    const char* personalityEnvVar; ///< Must be in first personality
    const char* banner           ; 
    Bool        checkDate        ; 
    Uns32       expireDays       ; 
    Uns32       expireWarnDays   ; 
    Uns32       capabilityIndex  ; 
} optPersonality;

/// @struct optVFSS
/// Define a null terminated list of embedded models

typedef struct optVFSS {
    struct {
        const char * vendor ; 
        const char * library; 
        const char * name   ; 
        const char * version; 
        Bool         isPSE  ; 
    } ref;

    void* lo; 
    void* hi; 
} optVFS;



////////////////////////////////////////////////////////////////////////////////
// Macros
////////////////////////////////////////////////////////////////////////////////

/// @def OP_VFS_MODEL_EXTERNAL
/// Use this to import the addresses of an embedded model
/// @param _NAME () The label
#define OP_VFS_MODEL_EXTERNAL(_NAME)\
   extern void * _NAME ##_model_start; extern void * _NAME ##_model_end
        

/// @def OP_VFS_PSE_EXTERNAL
/// Use this to import the addresses of an embedded model
/// @param _NAME () The label
#define OP_VFS_PSE_EXTERNAL(_NAME)\
   extern void * _NAME ##_pse_start; extern void * _NAME ##_pse_end
        

/// @def OP_VFS_FUNCTION
/// Use this to import an embedded model entry point
/// @param _NAME () The function name
#define OP_VFS_FUNCTION(_NAME)\
   void _NAME (void)
        

/// @def OP_VFS_MODEL_SYMBOLS
/// Use this to set the addresses of an embedded model
/// @param _NAME () The label
#define OP_VFS_MODEL_SYMBOLS(_NAME)\
   .lo = & _NAME ##_model_start, .hi = & _NAME ##_model_end
        

/// @def OP_VFS_PSE_SYMBOLS
/// Use this to set the addresses of an embedded model
/// @param _NAME () The label
#define OP_VFS_PSE_SYMBOLS(_NAME)\
   .lo = & _NAME ##_pse_start, .hi = & _NAME ##_pse_end
        

/// @def OP_VFS_MODULE_SYMBOLS
/// Use this to set the address of an embedded module
/// @param _NAME () The label
#define OP_VFS_MODULE_SYMBOLS(_NAME)\
   .lo = & _NAME ##_module_modelAttrs
        

/// @def OP_VFS_MODEL_VLNV
/// Use this to import the address of an embedded model
/// @param VENDOR  () Vendor without quotes
/// @param LIBRARY () Library without quotes
/// @param NAME    () Name without quotes
/// @param VERSION () Version without quotes
#define OP_VFS_MODEL_VLNV(VENDOR,LIBRARY,NAME,VERSION)\
   .ref = { #VENDOR, #LIBRARY, #NAME, #VERSION, 0 }
        

/// @def OP_VFS_PSE_VLNV
/// Use this to import the address of an embedded model
/// @param VENDOR  () Vendor without quotes
/// @param LIBRARY () Library without quotes
/// @param NAME    () Name without quotes
/// @param VERSION () Version without quotes
#define OP_VFS_PSE_VLNV(VENDOR,LIBRARY,NAME,VERSION)\
   .ref = { #VENDOR, #LIBRARY, #NAME, #VERSION, 1 }
        

/// @def OP_BUS_CONNECT
/// Macro to connect a bus to a bus port on an instance of a MMC, module,
/// processor or peripheral. This is used in conjunction with the
/// OP_BUS_CONNECTIONS which creates a list of bus connections. By default the
/// connection will be a master port. To make a slave port connection specify
/// .slave=1 and also specify .addrLo and .addrHi. To make a dynamic slave port
/// specify .slave=1 and .dynamic=1.
/// @param _BUS       (optBusP) The bus instance to connect
/// @param _PORT_NAME (const char *) name of the bus port on the instance
/// @par
/// @e addrLo     (vararg Addr) Low end of decoded region.
/// @par
/// @e addrHi     (vararg Addr) High end of decoded region.
/// @par
/// @e slave      (vararg Bool) If true, makes a slave port connection (if false, makes
///                   a master port)
/// @par
/// @e dynamic    (vararg Bool) If true, and this is a slave port, the decoded address
///                   is set by the model, not the platform.
#define OP_BUS_CONNECT(_BUS,_PORT_NAME,...)\
(optBusPortConnect) {       \
    bus      : _BUS,        \
    portName : _PORT_NAME,  \
    __VA_ARGS__  \
}
        

/// @def OP_BUS_CONNECTIONS
/// Create a null-terminated array of bus port connections.
/// @param ... List of OP_BUS_CONNECT macros
#define OP_BUS_CONNECTIONS(...)\
.busPortConns = (optBusPortConnect[]){__VA_ARGS__, {0}}
        

/// @def OP_NET_CONNECT
/// Macro to connect a net to a net port on a module, processor or peripheral.
/// Used in conjunction with OP_NET_CONNECTIONS.
/// @param _NET       (optNetP) handle of net to connect
/// @param _PORT_NAME (const char *) name of the net port on the instance
#define OP_NET_CONNECT(_NET,_PORT_NAME)\
(optNetPortConnect){        \
    net      : _NET,        \
    portName : _PORT_NAME   \
}
        

/// @def OP_NET_CONNECTIONS
/// Create a null-terminated array of net port connections
/// @param ... List of OP_NET_CONNECT macros
#define OP_NET_CONNECTIONS(...)\
.netPortConns = (optNetPortConnect[]){__VA_ARGS__, {0}}
        

/// @def OP_FIFO_CONNECT
/// Macro used to connect a FIFO to a FIFO port on a module or processor. Used
/// in conjunction with OP_CONNECTIONS.
/// @param _FIFO      (optFIFOP) handle of FIFO to connect
/// @param _PORT_NAME (const char *) name of the FIFO port on the instance
#define OP_FIFO_CONNECT(_FIFO,_PORT_NAME)\
(optFIFOPortConnect){       \
    FIFO     : _FIFO,       \
    portName : _PORT_NAME   \
}
        

/// @def OP_FIFO_CONNECTIONS
/// Create a null-terminated array of FIFO port connections
/// @param ... List of OP_FIFO_CONNECT macros
#define OP_FIFO_CONNECTIONS(...)\
.fifoPortConns = (optFIFOPortConnect[]){__VA_ARGS__, {0}}
        

/// @def OP_PACKETNET_CONNECT
/// Macro used to connect a packetnet to packetnet port on a peripheral or
/// module. Used in conjunction with OP_CONNECTIONS.
/// @param _PACKETNET (optPacketnetP) handle of packetnet to connect
/// @param _PORT_NAME (const char *) name of the packetnet port on the instance
#define OP_PACKETNET_CONNECT(_PACKETNET,_PORT_NAME)\
(optPacketnetPortConnect){ \
    packetnet : _PACKETNET,  \
    portName  : _PORT_NAME   \
}
        

/// @def OP_PACKETNET_CONNECTIONS
/// Create a null-terminated array of packetnet port connections
/// @param ... List of OP_PACKETNET_CONNECT macros
#define OP_PACKETNET_CONNECTIONS(...)\
.packetnetPortConns = (optPacketnetPortConnect[]){__VA_ARGS__, {0}}
        

/// @def OP_CONNECTIONS
/// Assemble all the connections for an instance. This macro initializes the
/// optConnections structure and is used in conjunction with
/// OP_BUS_CONNECTIONS,OP_FIFO_CONNECTIONS,OP_NET_CONNECTIONS and
/// OP_PACKETNET_CONNECTIONS. Refer to opBridgeNew, opMemoryNew, opMMCNew,
/// opModuleNew, opProcessorNew, opPeripheralNew
/// @param ... List of connection macros
#define OP_CONNECTIONS(...)\
&(optConnections){__VA_ARGS__}
       

/// @def OP_PROC_STD_BUS
/// Macro to connect a bus to a processor that has two bus ports called CODE and
/// INSTRUCTION.
/// @param _BUS (optBusP) The bus instance
#define OP_PROC_STD_BUS(_BUS)\
OP_CONNECTIONS(OP_BUS_CONNECTIONS(OP_BUS_CONNECT(_BUS,"INSTRUCTION"),OP_BUS_CONNECT(_BUS, "DATA")))
       

/// @def OP_MEM_STD_BUS
/// Macro to connect a bus to a memory that has a bus port called sp1.
/// @param _BUS    (optBusP) The bus instance
/// @param _ADDRLO (Addr) The lower address limit
/// @param _ADDRHI (Addr) The upper address limit
#define OP_MEM_STD_BUS(_BUS,_ADDRLO,_ADDRHI)\
OP_CONNECTIONS(OP_BUS_CONNECTIONS(OP_BUS_CONNECT(_BUS,"sp1", _ADDRLO, _ADDRHI,1,0)))
       

/// @def OP_PARAM_BOOL_SET
/// Initialize a boolean parameter in a parameter list.
/// @param _NAME  (const char *) parameter name
/// @param _VALUE (Bool) parameter value
#define OP_PARAM_BOOL_SET(_NAME,_VALUE)\
        opParamBoolCreate(_NAME,_VALUE)
        

/// @def OP_PARAM_DOUBLE_SET
/// Initialize a double parameter in a parameter list.
/// @param _NAME  (const char *) parameter name
/// @param _VALUE (double) parameter value
#define OP_PARAM_DOUBLE_SET(_NAME,_VALUE)\
        opParamDoubleCreate (_NAME,_VALUE)
        

/// @def OP_PARAM_ENDIAN_SET
/// Initialize an endian parameter in a parameter list.
/// @param _NAME  (const char *) parameter name
/// @param _VALUE (optEndian) parameter value
#define OP_PARAM_ENDIAN_SET(_NAME,_VALUE)\
        opParamEndianCreate (_NAME,_VALUE)
        

/// @def OP_PARAM_ENUM_SET
/// Initialize an enum parameter in a parameter list.
/// @param _NAME  (const char *) parameter name
/// @param _VALUE (const char *) parameter value
#define OP_PARAM_ENUM_SET(_NAME,_VALUE)\
        opParamEnumCreate   (_NAME,_VALUE)
        

/// @def OP_PARAM_INT32_SET
/// Initialize an int32 parameter in a parameter list.
/// @param _NAME  (const char *) parameter name
/// @param _VALUE (Int32) parameter value
#define OP_PARAM_INT32_SET(_NAME,_VALUE)\
        opParamInt32Create  (_NAME,_VALUE)
        

/// @def OP_PARAM_INT64_SET
/// Initialize an int64 parameter in a parameter list.
/// @param _NAME  (const char *) parameter name
/// @param _VALUE (Int64) parameter value
#define OP_PARAM_INT64_SET(_NAME,_VALUE)\
        opParamInt64Create  (_NAME,_VALUE)
        

/// @def OP_PARAM_PTR_SET
/// Initialize a pointer parameter in a parameter list.
/// @param _NAME  (const char *) parameter name
/// @param _VALUE (void*) parameter value (any type of pointer)
#define OP_PARAM_PTR_SET(_NAME,_VALUE)\
            opParamPointerCreate(_NAME,_VALUE)
        

/// @def OP_PARAM_STRING_SET
/// Initialize a string parameter in a parameter list.
/// @param _NAME  (const char *) parameter name
/// @param _VALUE (const char *) parameter value
#define OP_PARAM_STRING_SET(_NAME,_VALUE)\
        opParamStringCreate (_NAME,_VALUE)
        

/// @def OP_PARAM_UNS32_SET
/// Initialize an uns32 parameter in a parameter list.
/// @param _NAME  (const char *) parameter name
/// @param _VALUE (Uns32) parameter value
#define OP_PARAM_UNS32_SET(_NAME,_VALUE)\
            opParamUns32Create  (_NAME,_VALUE)
        

/// @def OP_PARAM_UNS64_SET
/// Initialize an uns64 parameter in a parameter list.
/// @param _NAME  (const char *) parameter name
/// @param _VALUE (Uns64) parameter value
#define OP_PARAM_UNS64_SET(_NAME,_VALUE)\
        opParamUns64Create  (_NAME,_VALUE)
        

/// @def OP_PARAMS
/// Create a parameter list for a model instance
/// @param ... list of parameter macros, for example: OP_PARAM_BOOL_SET
#define OP_PARAMS(...)\
        opParamListFromArray((optParamArray[]){__VA_ARGS__, {0}})
        

/// Maximum number of bytes in one object accepted by opProcessorRead and
/// opProcessorWrite

#define OP_MAX_OBJECT_SIZE            32768
        

/// @def OP_ASSERT
/// Utility macro to abort if asserted condition is false
/// @param _COND (Bool) condition to be tested
/// @param _FMT  (const char *) format string
/// @par
/// @e ...   (vararg parameter list) list of parameters
#define OP_ASSERT(_COND,_FMT,...)\
    do {                                                                \
        if (!(_COND)) {                                                 \
            opMessage("a", "OP_ASSERT",                                 \
            "%s:%d:%s " _FMT,                                           \
            __FILE__, __LINE__, __FUNCTION__, ## __VA_ARGS__ );         \
        }                                                               \
    } while (0)        
        

/// Define the formal parameters used by the HTTP port

#define OP_HTTP_VIS_PORT_FORMALS { \
    .name = "httpvisportnum", \
    .type = OP_PARAM_UNS32, \
    .description = "Visualization HTTP port", \
    .spec.uns32Spec.min          = 0, \
    .spec.uns32Spec.max          = 32767, \
    .spec.uns32Spec.defaultValue = 8000, \
},{  \
    .name = "httpvisdir", \
    .type = OP_PARAM_STRING, \
    .description = "Visualization data directory", \
},{ \
    .name = "record", \
    .type = OP_PARAM_STRING, \
    .description = "file to record visualization inputs", \
},{ \
    .name = "replay", \
    .type = OP_PARAM_STRING, \
    .description = "file to replay visualization inputs", \
}
    


////////////////////////////////////////////////////////////////////////////////
// Simulator formal parameters
////////////////////////////////////////////////////////////////////////////////

/// @par  Simulator Parameter OP_FP_TRACE.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Enable instruction tracing.
/// @par  Can be applied to:
/// peripheral@n
/// processor@n

#define OP_FP_TRACE          "trace"

/// @par  Simulator Parameter OP_FP_TRACEBUFFER.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Enable 256-entry trace buffer
/// @par  Can be applied to:
/// processor@n

#define OP_FP_TRACEBUFFER    "tracebuffer"

/// @par  Simulator Parameter OP_FP_TRACECOUNT.
/// @par  Type.
/// Uns64
/// @par  Purpose.
/// Trace for this many instructions
/// @par  Can be applied to:
/// processor@n

#define OP_FP_TRACECOUNT     "tracecount"

/// @par  Simulator Parameter OP_FP_TRACEFILE.
/// @par  Type.
/// String
/// @par  Purpose.
/// Processor trace information goes into this file
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_TRACEFILE      "tracefile"

/// @par  Simulator Parameter OP_FP_TRACESTART.
/// @par  Type.
/// Uns64
/// @par  Purpose.
/// Turn tracing on after this many instructions
/// @par  Can be applied to:
/// processor@n

#define OP_FP_TRACESTART     "tracestart"

/// @par  Simulator Parameter OP_FP_TRACELOWPC.
/// @par  Type.
/// Uns64
/// @par  Purpose.
/// Trace only instructions with this PC or higher
/// @par  Can be applied to:
/// processor@n

#define OP_FP_TRACELOWPC     "tracelowpc"

/// @par  Simulator Parameter OP_FP_TRACEHIGHPC.
/// @par  Type.
/// Uns64
/// @par  Purpose.
/// Trace only instructions with this PC or lower
/// @par  Can be applied to:
/// processor@n

#define OP_FP_TRACEHIGHPC    "tracehighpc"

/// @par  Simulator Parameter OP_FP_TRACECHANGE.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Turn on the trace of register changes
/// @par  Can be applied to:
/// processor@n

#define OP_FP_TRACECHANGE    "tracechange"

/// @par  Simulator Parameter OP_FP_TRACEMODE.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Show the current processor mode when tracing instructions
/// @par  Can be applied to:
/// processor@n

#define OP_FP_TRACEMODE      "tracemode"

/// @par  Simulator Parameter OP_FP_TRACESHOWCPUNAME.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Include the CPU name with every trace line including register and memory
/// tracing
/// @par  Can be applied to:
/// processor@n

#define OP_FP_TRACESHOWCPUNAME "traceshowcpuname"

/// @par  Simulator Parameter OP_FP_TRACESHOWICOUNT.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Include a per-processor instruction count in the trace output
/// @par  Can be applied to:
/// processor@n

#define OP_FP_TRACESHOWICOUNT "traceshowicount"

/// @par  Simulator Parameter OP_FP_TRACEREGSAFTER.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Print processor register contents after each instruction
/// @par  Can be applied to:
/// processor@n

#define OP_FP_TRACEREGSAFTER "traceregsafter"

/// @par  Simulator Parameter OP_FP_TRACEREGSBEFORE.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Print processor register contents before each instruction
/// @par  Can be applied to:
/// processor@n

#define OP_FP_TRACEREGSBEFORE "traceregsbefore"

/// @par  Simulator Parameter OP_FP_TRACEMEM.
/// @par  Type.
/// String
/// @par  Purpose.
/// Print memory accesses by each instruction. Can include values X, S and A
/// @par  Can be applied to:
/// processor@n
/// rootmodule@n

#define OP_FP_TRACEMEM       "tracemem"

/// @par  Simulator Parameter OP_FP_TRACEINTERCEPT.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Trace calls of intercepted functions defined using processor ABI
/// @par  Can be applied to:
/// processor@n

#define OP_FP_TRACEINTERCEPT "traceintercept"

/// @par  Simulator Parameter OP_FP_TRACEWRITE.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Trace register writes even if the value does not change
/// @par  Can be applied to:
/// processor@n

#define OP_FP_TRACEWRITE     "tracewrite"

/// @par  Simulator Parameter OP_FP_MAXINSTRUCTIONS.
/// @par  Type.
/// Uns64
/// @par  Purpose.
/// Limit the maximum number of instructions to be executed before simulation
/// ends
/// @par  Can be applied to:
/// processor@n

#define OP_FP_MAXINSTRUCTIONS "maxinstructions"

/// @par  Simulator Parameter OP_FP_STARTADDRESS.
/// @par  Type.
/// Uns64
/// @par  Purpose.
/// Set the PC to start at this specified address instead of using the hardware
/// reset value, or the address found in the loaded program
/// @par  Can be applied to:
/// leaf@n

#define OP_FP_STARTADDRESS   "startaddress"

/// @par  Simulator Parameter OP_FP_WIRESHARKFILE.
/// @par  Type.
/// String
/// @par  Purpose.
/// Write wireshark file for this packetnet
/// @par  Can be applied to:
/// packetnet@n

#define OP_FP_WIRESHARKFILE  "wiresharkfile"

/// @par  Simulator Parameter OP_FP_WIRESHARKREALTIME.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Wireshark file has real time stamps
/// @par  Can be applied to:
/// packetnet@n

#define OP_FP_WIRESHARKREALTIME "wiresharkrealtime"

/// @par  Simulator Parameter OP_FP_DIAGNOSTICLEVEL.
/// @par  Type.
/// Uns32
/// @par  Purpose.
/// Set the peripheral model diagnostic level to this value
/// @par  Can be applied to:
/// module@n
/// peripheral@n

#define OP_FP_DIAGNOSTICLEVEL "diagnosticlevel"

/// @par  Simulator Parameter OP_FP_TRACEPSEINTERCEPT.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Trace calls of intercepted functions defined using PSE ABI
/// @par  Can be applied to:
/// peripheral@n

#define OP_FP_TRACEPSEINTERCEPT "tracepseintercept"

/// @par  Simulator Parameter OP_FP_ENABLETOOLSPSE.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Load VAP tools for this PSE
/// @par  Can be applied to:
/// peripheral@n

#define OP_FP_ENABLETOOLSPSE "enabletoolspse"

/// @par  Simulator Parameter OP_FP_DEBUGBASIC.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Tell the MDP to not use a gdb or debug helper with this processor. This
/// causes the MPD to work with reduced functionality with this processor
/// @par  Can be applied to:
/// processor@n

#define OP_FP_DEBUGBASIC     "debugbasic"

/// @par  Simulator Parameter OP_FP_DEFAULTSEMIHOST.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// This processor will load its default semihost library, specified in the
/// processor model.
/// @par  Can be applied to:
/// processor@n

#define OP_FP_DEFAULTSEMIHOST "defaultsemihost"

/// @par  Simulator Parameter OP_FP_ENABLEIMPERASINTERCEPTS.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// The simulator will intercept calls to Imperas special functions
/// @par  Can be applied to:
/// processor@n
/// rootmodule@n

#define OP_FP_ENABLEIMPERASINTERCEPTS "enableimperasintercepts"

/// @par  Simulator Parameter OP_FP_ENABLETOOLS.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Load VAP tools for this processor
/// @par  Can be applied to:
/// processor@n

#define OP_FP_ENABLETOOLS    "enabletools"

/// @par  Simulator Parameter OP_FP_ENABLESMPTOOLS.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Enable VAP tools to do SMP analysis
/// @par  Can be applied to:
/// processor@n

#define OP_FP_ENABLESMPTOOLS "enableSMPTools"

/// @par  Simulator Parameter OP_FP_EXITMODE.
/// @par  Type.
/// Enum
/// @par  Purpose.
/// Conditions required for a multicore processor to finish simulating: 'first'=
/// when any core exits, 'all'= when all cores have exited
/// @par  Can be applied to:
/// processor@n
/// @par  The enumerated type can take these values:
/// first : The first processor core to call vmirtExit will finish the
/// simulation@n
/// all : The last processor core of a cluster to call vmirtExit will finish the
/// simulation@n

#define OP_FP_EXITMODE       "exitmode"

/// @par  Simulator Parameter OP_FP_FETCHVALIDATE.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// For internal use
/// @par  Can be applied to:
/// processor@n

#define OP_FP_FETCHVALIDATE  "fetchvalidate"

/// @par  Simulator Parameter OP_FP_LOADPHYSICAL.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Load programs using the physical rather than logical addresses from the
/// program file
/// @par  Can be applied to:
/// processor@n

#define OP_FP_LOADPHYSICAL   "loadphysical"

/// @par  Simulator Parameter OP_FP_LOADSIGNEXTEND.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// When loading programs sign-extend 32 bit addresses from the ELF file to 64
/// bits
/// @par  Can be applied to:
/// processor@n

#define OP_FP_LOADSIGNEXTEND "loadsignextend"

/// @par  Simulator Parameter OP_FP_SIMULATEEXCEPTIONS.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// When the processor encounters an exception, it will execute the exception.
/// If this parameter is not set, the simulator will stop with the appropriate
/// stop reason
/// @par  Can be applied to:
/// processor@n

#define OP_FP_SIMULATEEXCEPTIONS "simulateexceptions"

/// @par  Simulator Parameter OP_FP_SYSTEMC.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// For internal use
/// @par  Can be applied to:
/// processor@n
/// rootmodule@n

#define OP_FP_SYSTEMC        "systemc"

/// @par  Simulator Parameter OP_FP_READFRAMEINFO.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// For internal use
/// @par  Can be applied to:
/// processor@n
/// rootmodule@n

#define OP_FP_READFRAMEINFO  "readframeinfo"

/// @par  Simulator Parameter OP_FP_TRACENOANNUL.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// For internal use
/// @par  Can be applied to:
/// processor@n

#define OP_FP_TRACENOANNUL   "tracenoannul"

/// @par  Simulator Parameter OP_FP_ELFUSEVMA.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// When loading an ELF file use VMA rather than LMA
/// @par  Can be applied to:
/// processor@n

#define OP_FP_ELFUSEVMA      "elfusevma"

/// @par  Simulator Parameter OP_FP_SETPROTECTION.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// When loading an ELF file set memory protection according to the program
/// headers
/// @par  Can be applied to:
/// processor@n

#define OP_FP_SETPROTECTION  "setprotection"

/// @par  Simulator Parameter OP_FP_ADDRBITS.
/// @par  Type.
/// Uns32
/// @par  Purpose.
/// If the processor is not connected to a bus, connect using this number of
/// address bits
/// @par  Can be applied to:
/// processor@n

#define OP_FP_ADDRBITS       "addrbits"

/// @par  Simulator Parameter OP_FP_CPUID.
/// @par  Type.
/// Uns32
/// @par  Purpose.
/// Set a unique ID for this CPU. The processor can read this value using
/// impProcessorId() from simulatorIntercepts.h
/// @par  Can be applied to:
/// processor@n

#define OP_FP_CPUID          "cpuid"

/// @par  Simulator Parameter OP_FP_GDBCOMMANDFILE.
/// @par  Type.
/// String
/// @par  Purpose.
/// specify a file to be a read by a gdb connected to this processor
/// @par  Can be applied to:
/// processor@n

#define OP_FP_GDBCOMMANDFILE "gdbcommandfile"

/// @par  Simulator Parameter OP_FP_ALTERNATEGDBFLAGS.
/// @par  Type.
/// String
/// @par  Purpose.
/// Additional command-line flags for the gdb connected to this processor
/// @par  Can be applied to:
/// processor@n

#define OP_FP_ALTERNATEGDBFLAGS "alternategdbflags"

/// @par  Simulator Parameter OP_FP_GDBINIT.
/// @par  Type.
/// String
/// @par  Purpose.
/// tell gdb to execute this file before the prompt is displayed
/// @par  Can be applied to:
/// processor@n

#define OP_FP_GDBINIT        "gdbinit"

/// @par  Simulator Parameter OP_FP_ALTERNATEGDBPATH.
/// @par  Type.
/// String
/// @par  Purpose.
/// override the default path to the gdb connected to this processor
/// @par  Can be applied to:
/// processor@n

#define OP_FP_ALTERNATEGDBPATH "alternategdbpath"

/// @par  Simulator Parameter OP_FP_MIPS.
/// @par  Type.
/// Double
/// @par  Purpose.
/// Specify the MIPS rate of this processor (in MHz)
/// @par  Can be applied to:
/// processor@n

#define OP_FP_MIPS           "mips"

/// @par  Simulator Parameter OP_FP_DEBUGFLAGS.
/// @par  Type.
/// Uns32
/// @par  Purpose.
/// Pass this debug value to the model (The model must be coded to accept it).
/// @par  Can be applied to:
/// processor@n

#define OP_FP_DEBUGFLAGS     "debugflags"

/// @par  Simulator Parameter OP_FP_USERARGV.
/// @par  Type.
/// String
/// @par  Purpose.
/// Array of user flags sent to the semihost library to pass to main()
/// @par  Can be applied to:
/// processor@n

#define OP_FP_USERARGV       "userargv"

/// @par  Simulator Parameter OP_FP_ENDIAN.
/// @par  Type.
/// String
/// @par  Purpose.
/// Set this processor endian (most processors with selectable endian use this
/// name).
/// @par  Can be applied to:
/// processor@n

#define OP_FP_ENDIAN         "endian"

/// @par  Simulator Parameter OP_FP_VARIANT.
/// @par  Type.
/// String
/// @par  Purpose.
/// Set the processor variant to this value
/// @par  Can be applied to:
/// processor@n

#define OP_FP_VARIANT        "variant"

/// @par  Simulator Parameter OP_FP_DEBUGPSECONSTRUCTORS.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Do not run the pse constructors before dropping into the debugger
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_DEBUGPSECONSTRUCTORS "debugpseconstructors"

/// @par  Simulator Parameter OP_FP_IDEBUG.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Discontinued integrated debugger. Please use mpdconsole
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_IDEBUG         "idebug"

/// @par  Simulator Parameter OP_FP_MIMODE.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Put the debugger command line interpreter into MI Mode
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_MIMODE         "mimode"

/// @par  Simulator Parameter OP_FP_INTERACTIVE.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Discontinued integrated debugger. Please use mpdconsole
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_INTERACTIVE    "interactive"

/// @par  Simulator Parameter OP_FP_CGEN.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// For internal use only
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_CGEN           "cgen"

/// @par  Simulator Parameter OP_FP_ICMMODE.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// For internal use only
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_ICMMODE        "icmmode"

/// @par  Simulator Parameter OP_FP_IGEN.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// For internal use only
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_IGEN           "igen"

/// @par  Simulator Parameter OP_FP_ISS.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// For internal use only
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_ISS            "iss"

/// @par  Simulator Parameter OP_FP_GDBCONSOLE.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// start a GDB in a console window
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_GDBCONSOLE     "gdbconsole"

/// @par  Simulator Parameter OP_FP_GDBEGUI.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Start GDB Eclipse GUI
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_GDBEGUI        "gdbegui"

/// @par  Simulator Parameter OP_FP_HTTPVIS.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Enable HTTP visualization
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_HTTPVIS        "httpvis"

/// @par  Simulator Parameter OP_FP_MPDCONSOLE.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Start the multiprocessor debugger in a console window
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_MPDCONSOLE     "mpdconsole"

/// @par  Simulator Parameter OP_FP_MPDFULLNAMES.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Do not truncate the processor names in the MPD
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_MPDFULLNAMES   "mpdfullnames"

/// @par  Simulator Parameter OP_FP_MPDEGUI.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Start the multiprocessor debugger with Eclipse GUI
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_MPDEGUI        "mpdegui"

/// @par  Simulator Parameter OP_FP_RSPNOWAIT.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Listen for, but do not wait for a debugger connection
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_RSPNOWAIT      "rspnowait"

/// @par  Simulator Parameter OP_FP_VOLATILENATIVEMEMCHECK.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Check that the JIT cache has not been left invalid when native memory is
/// changed without notification.
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_VOLATILENATIVEMEMCHECK "volatilenativememcheck"

/// @par  Simulator Parameter OP_FP_NOSIMULATION.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// The simulator will exit before simulation begins (use when checking the
/// design).
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_NOSIMULATION   "nosimulation"

/// @par  Simulator Parameter OP_FP_NOOPTIMIZE.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Turn off JIT code optimization
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_NOOPTIMIZE     "nooptimize"

/// @par  Simulator Parameter OP_FP_PARALLEL.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Enable limited parallel simulation
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_PARALLEL       "parallel"

/// @par  Simulator Parameter OP_FP_PARALLELPERIPHERALS.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Enable parallel peripheral simulation using any number of concurrent host
/// threads
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_PARALLELPERIPHERALS "parallelperipherals"

/// @par  Simulator Parameter OP_FP_PARALLELMAX.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Enable unlimited parallel simulation
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_PARALLELMAX    "parallelmax"

/// @par  Simulator Parameter OP_FP_SHOWBUSES.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Print all bus connections
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_SHOWBUSES      "showbuses"

/// @par  Simulator Parameter OP_FP_SHOWCOMMANDS.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Print all available model commands in all models in this design
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_SHOWCOMMANDS   "showcommands"

/// @par  Simulator Parameter OP_FP_SHOWDOMAINS.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Print a summary of all the memory domains in this design
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_SHOWDOMAINS    "showdomains"

/// @par  Simulator Parameter OP_FP_SHOWFORMALS.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Show all formal parameters in this design
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_SHOWFORMALS    "showformals"

/// @par  Simulator Parameter OP_FP_SHOWLOAD.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Show where each model is loaded from
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_SHOWLOAD       "showload"

/// @par  Simulator Parameter OP_FP_SHOWMODELFORMALS.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Show model-specific formal parameters in this design
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_SHOWMODELFORMALS "showmodelformals"

/// @par  Simulator Parameter OP_FP_SHOWSYSTEMFORMALS.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Show system formal parameters in this design
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_SHOWSYSTEMFORMALS "showsystemformals"

/// @par  Simulator Parameter OP_FP_MEMORYSTATS.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// For internal use
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_MEMORYSTATS    "memorystats"

/// @par  Simulator Parameter OP_FP_MULTIPROCESS.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Support multiple processes
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_MULTIPROCESS   "multiprocess"

/// @par  Simulator Parameter OP_FP_STOPONCONTROLC.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Allow the control-C signal to stop the simulator (note that under Windows
/// the correct behavior of this feature relies on the command shell)
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_STOPONCONTROLC "stoponcontrolc"

/// @par  Simulator Parameter OP_FP_TRACESHAREDDATA.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Enable tracing of simulator shared data
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_TRACESHAREDDATA "traceshareddata"

/// @par  Simulator Parameter OP_FP_SUPPRESSBANNER.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Suppress printing of the product banner (this feature is restricted to
/// certain products)
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_SUPPRESSBANNER "suppressbanner"

/// @par  Simulator Parameter OP_FP_SYSTEMCVERSION.
/// @par  Type.
/// Uns32
/// @par  Purpose.
/// For internal use
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_SYSTEMCVERSION "systemcversion"

/// @par  Simulator Parameter OP_FP_VERBOSE.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Enable verbose mode. The simulator will print more information during start
/// up and shutdown
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_VERBOSE        "verbose"

/// @par  Simulator Parameter OP_FP_VERBOSEDICTIONARY.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// For internal use
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_VERBOSEDICTIONARY "verbosedictionary"

/// @par  Simulator Parameter OP_FP_WALLCLOCK.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Set the simulator wallclock factor to 1.0
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_WALLCLOCK      "wallclock"

/// @par  Simulator Parameter OP_FP_RESTARTYIELD.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Yield to control API when awoken by timer expiry
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_RESTARTYIELD   "restartyield"

/// @par  Simulator Parameter OP_FP_LEGACYSCHEDULING.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Use legacy scheduling algorithm (PSE events before processors in each
/// quantum)
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_LEGACYSCHEDULING "legacyscheduling"

/// @par  Simulator Parameter OP_FP_DEFERHALTEDPROCESSORS.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Update halted processors only in a quantum delta cycle (so all non-halted
/// processors execute first)
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_DEFERHALTEDPROCESSORS "deferhaltedprocessors"

/// @par  Simulator Parameter OP_FP_DEBUGXCHARS.
/// @par  Type.
/// Uns32
/// @par  Purpose.
/// Number of character columns in mpd or GDB console window
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_DEBUGXCHARS    "debugxchars"

/// @par  Simulator Parameter OP_FP_DEBUGYCHARS.
/// @par  Type.
/// Uns32
/// @par  Purpose.
/// Number of character rows in mpd or GDB console window
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_DEBUGYCHARS    "debugychars"

/// @par  Simulator Parameter OP_FP_CONSOLEPORT.
/// @par  Type.
/// Uns32
/// @par  Purpose.
/// Integrated debugger listens for extra MI connections on this port number
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_CONSOLEPORT    "consoleport"

/// @par  Simulator Parameter OP_FP_CONSOLEPORTFILE.
/// @par  Type.
/// String
/// @par  Purpose.
/// Integrated debugger writes the new port number to this file
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_CONSOLEPORTFILE "consoleportfile"

/// @par  Simulator Parameter OP_FP_DICTSIZE.
/// @par  Type.
/// Uns32
/// @par  Purpose.
/// Override default dictionary size (in MBytes)
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_DICTSIZE       "dictsize"

/// @par  Simulator Parameter OP_FP_FINISHTIME.
/// @par  Type.
/// Double
/// @par  Purpose.
/// Set the simulation finish time (in seconds)
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_FINISHTIME     "finishtime"

/// @par  Simulator Parameter OP_FP_LOGFILE.
/// @par  Type.
/// String
/// @par  Purpose.
/// Specify the simulator log file
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_LOGFILE        "logfile"

/// @par  Simulator Parameter OP_FP_LOGFILEFLUSH.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Flush the log file after every write (slow on some systems)
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_LOGFILEFLUSH   "logfileflush"

/// @par  Simulator Parameter OP_FP_MPDCONSOLELOGFILE.
/// @par  Type.
/// String
/// @par  Purpose.
/// MPD writes its log to this file
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_MPDCONSOLELOGFILE "mpdconsolelogfile"

/// @par  Simulator Parameter OP_FP_PROFILE.
/// @par  Type.
/// Int32
/// @par  Purpose.
/// Enable profiling, showing this number of profile categories
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_PROFILE        "profile"

/// @par  Simulator Parameter OP_FP_QUANTUM.
/// @par  Type.
/// Double
/// @par  Purpose.
/// Set the simulator quantum (in seconds)
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_QUANTUM        "quantum"

/// @par  Simulator Parameter OP_FP_QUANTUMSEED.
/// @par  Type.
/// Uns32
/// @par  Purpose.
/// Specify a seed for random number generation
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_QUANTUMSEED    "quantumseed"

/// @par  Simulator Parameter OP_FP_QUANTUMTRACEFILE.
/// @par  Type.
/// String
/// @par  Purpose.
/// Output a VCD (value change dump) file of the quantum trace
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_QUANTUMTRACEFILE "quantumtracefile"

/// @par  Simulator Parameter OP_FP_QUANTUMDIFFTIME.
/// @par  Type.
/// Double
/// @par  Purpose.
/// Start of quantum in which to search for non-determinism
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_QUANTUMDIFFTIME "quantumdifftime"

/// @par  Simulator Parameter OP_FP_REMOTEDEBUGPORT.
/// @par  Type.
/// Uns32
/// @par  Purpose.
/// The simulator will allow a connection to this port by an RSP capable
/// debugger. If the port number is zero, a port will be chosen from the host
/// pool
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_REMOTEDEBUGPORT "remotedebugport"

/// @par  Simulator Parameter OP_FP_PARALLELOPT.
/// @par  Type.
/// Uns32
/// @par  Purpose.
/// Parallel simulation options
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_PARALLELOPT    "parallelopt"

/// @par  Simulator Parameter OP_FP_PARALLELTHREADS.
/// @par  Type.
/// Uns32
/// @par  Purpose.
/// Set number of parallel threads
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_PARALLELTHREADS "parallelthreads"

/// @par  Simulator Parameter OP_FP_TIMEPRECISION.
/// @par  Type.
/// Double
/// @par  Purpose.
/// Set the simulator time precision in seconds
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_TIMEPRECISION  "timeprecision"

/// @par  Simulator Parameter OP_FP_WALLCLOCKFACTOR.
/// @par  Type.
/// Double
/// @par  Purpose.
/// Specify set the simulator wallclock factor (a ratio)
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_WALLCLOCKFACTOR "wallclockfactor"

/// @par  Simulator Parameter OP_FP_BATCH.
/// @par  Type.
/// String
/// @par  Purpose.
/// Execute this list of batch files in the debugger
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_BATCH          "batch"

/// @par  Simulator Parameter OP_FP_RECORDDIR.
/// @par  Type.
/// String
/// @par  Purpose.
/// Models supporting record/replay will write to this directory a replay file
/// derived from the instance name
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_RECORDDIR      "recorddir"

/// @par  Simulator Parameter OP_FP_REPLAYDIR.
/// @par  Type.
/// String
/// @par  Purpose.
/// Models supporting record/replay will read from this directory a replay file
/// in derived from the instance name
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_REPLAYDIR      "replaydir"

/// @par  Simulator Parameter OP_FP_EGUIOPTIONS.
/// @par  Type.
/// String
/// @par  Purpose.
/// Pass these options onto the command line of GUI when started
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_EGUIOPTIONS    "eguioptions"

/// @par  Simulator Parameter OP_FP_EGUICOMMANDS.
/// @par  Type.
/// String
/// @par  Purpose.
/// Pass these commands to the GUI at startup
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_EGUICOMMANDS   "eguicommands"

/// @par  Simulator Parameter OP_FP_SYSTEMVERILOG.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// For internal use
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_SYSTEMVERILOG  "systemverilog"

/// @par  Simulator Parameter OP_FP_VALIDATE.
/// @par  Type.
/// Ptr
/// @par  Purpose.
/// For internal use
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_VALIDATE       "validate"

/// @par  Simulator Parameter OP_FP_SHOWENV.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Print a description of all the environment variables accepted by this
/// product
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_SHOWENV        "showenv"

/// @par  Simulator Parameter OP_FP_SHOWHIERARCHY.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Print the design hierarchy
/// @par  Can be applied to:
/// rootmodule@n

#define OP_FP_SHOWHIERARCHY  "showhierarchy"

/// @par  Simulator Parameter OP_FP_TRANSPARENT.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Put this MMC into transparent mode (see
/// OVP_VMI_Memory_Model_Component_Function_Reference)
/// @par  Can be applied to:
/// mmc@n

#define OP_FP_TRANSPARENT    "transparent"

/// @par  Simulator Parameter OP_FP_NOOVERLAPCHECK.
/// @par  Type.
/// Bool
/// @par  Purpose.
/// Suppress checking for devices with overlapping addresses
/// @par  Can be applied to:
/// bus@n

#define OP_FP_NOOVERLAPCHECK "nooverlapcheck"


#endif /* OPTYPES_H */

