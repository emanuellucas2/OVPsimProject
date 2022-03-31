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

// Common area includes
#include "hostapi/impTypes.h"

// VMI area includes
#include "vmi/vmiTyperefs.h"

//
// Command argument types
//
typedef enum vmiArgTypeE {
    VMI_CA_NONE  = 0, // do not use
    VMI_CA_BOOL     , // Boolean
    VMI_CA_INT32    , // Signed 32-bit integer
    VMI_CA_INT64    , // Signed 64-bit integer
    VMI_CA_UNS32    , // Unsigned 32-bit integer
    VMI_CA_UNS64    , // Unsigned 64-bit integer
    VMI_CA_DOUBLE   , // C double precision floating point
    VMI_CA_STRING   , // String (see vmirtAddArg)
    VMI_CA_ENUM     , // Types are defined using vmirtAddArgEnum
    VMI_CA_ENDIAN   , // Pre-defined enumerated types big, little, either
    VMI_CA_PTR      , // Pointer type
} vmiArgType;

//
// Deprecated types. Please use those above.
//
#define  VMI_CA_ADDRESS      VMI_CA_UNS64
#define  VMI_CA_ENUMERATION  VMI_CA_ENUM
#define  VMI_CA_FLAG         VMI_CA_BOOL
#define  VMI_CA_FLOAT        VMI_CA_DOUBLE
#define  VMI_CA_INTEGER      VMI_CA_INT32

//
// Command argument attributes
// Attributes influence how these arguments appear in a menu.
// They are under development
//
typedef enum vmiArgAttrsE {

    VMI_CAA_DEFAULT        = 0x0000, // Not used in a menu
    VMI_CAA_MENU           = 0x0001, // Appears in a menu
    VMI_CAA_ENABLE         = 0x0010, // This argument enables the command
    VMI_CAA_VALUE_CALLBACK = 0x0020, // If true, the pointer points to a
                                     // function to get the value
} vmiArgAttrs;

//
// union of value types
//
typedef union argValueUnionU {

    Bool        flag;     // used with VMI_CA_BOOL
    Int32       int32;    // used with VMI_CA_INT32
    Int64       int64;    // used with VMI_CA_INT64
    Uns32       uns32;    // used with VMI_CA_UNS32, VMI_CA_ENUM, VMI_CA_ENDIAN
    Uns64       uns64;    // used with VMI_CA_UNS64
    Flt64       flt;      // used with VMI_CA_DOUBLE
    const char *string;   // used with VMI_CA_STRING
    void       *ptr;      // used with VMI_CA_PTR

    // These names are deprecated.
    // Please use those above.
    Uns64       addr;
    Int32       integer;

} argValueUnion;

//
// An array of these can be passed to the callback.
// This array is also passed to the -get_tcl_arguments callback if the
// value pointers are set in the vmirtAddArg call.
//

typedef struct argValueS {
    const char   *name;
    vmiArgType    type;
    Bool          isSet;
    Bool          changed;
    argValueUnion u;

} vmiArgValue, *vmiArgValueP;

//
// Type of function called when the command is called.
// The raw command arguments are passed to the callback in argv.
//
#define VMIRT_COMMAND_FN(_NAME) const char *_NAME( \
    vmiProcessorP processor,    \
    Int32         argc,         \
    const char   *argv[]        \
)
typedef VMIRT_COMMAND_FN((*vmirtCommandFn));

//
// Type of function called when processor command is evaluated
// The arguments are parsed using the standard parser, then this
// function is called with an array of parsed values.
// argc is the number of elements in argv[], not the number of arguments
// supplied to the command.
//
#define VMIRT_COMMAND_PARSE_FN(_NAME) const char *_NAME( \
    vmiProcessorP processor,    \
    Int32         argc,         \
    vmiArgValue   argv[]        \
)
typedef VMIRT_COMMAND_PARSE_FN((*vmirtCommandParseFn));

//
// Type of function called when the command is evaluated
// The function is passed the raw arguments
//
#define VMIOS_COMMAND_FN(_NAME) const char *_NAME( \
    vmiosObjectP object,    \
    Int32        argc,      \
    const char  *argv[]     \
)
typedef VMIOS_COMMAND_FN((*vmiosCommandFn));

//
// Type of function called when processor command is evaluated
// The arguments are parsed using the standard parser, then this
// function is called with an array of parsed values.
//
#define VMIOS_COMMAND_PARSE_FN(_NAME) const char *_NAME( \
    vmiosObjectP  object,     \
    Int32         argc,       \
    vmiArgValue   argv[]      \
)
typedef VMIOS_COMMAND_PARSE_FN((*vmiosCommandParseFn));


//
// Type of function called when memory model component command is evaluated
//
#define VMIMMC_COMMAND_FN(_NAME) const char *_NAME( \
    vmimmcComponentP component, \
    Int32            argc,      \
    const char      *argv[]     \
)
typedef VMIMMC_COMMAND_FN((*vmimmcCommandFn));

//
// Type of function called when processor command is evaluated
// The arguments are parsed using the standard parser, then this
// function is called with an array of parsed values.
//
#define VMIMMC_COMMAND_PARSE_FN(_NAME) const char *_NAME( \
    vmimmcComponentP component, \
    Int32            argc,      \
    vmiArgValue      argv[]     \
)
typedef VMIMMC_COMMAND_PARSE_FN((*vmimmcCommandParseFn));

//
// Opaque command handle
//
typedef struct vmiCommandS  *vmiCommandP;

//
// Opaque command argument handle
//
typedef struct vmiArgS  *vmiArgP;

//
// Attributes describing the type of a command to be installed
//
typedef Uns32 vmiCommandAttrs;

#define VMI_CT_DEFAULT        0x00000000

// Command type : describes how the command is used
#define VMI_CT_MASK           0x0000000F   // Bits used for the command type
#define VMI_CT_QUERY          0x00000001   // Command used to query something
#define VMI_CT_STATUS         0x00000002   // Called when the simulator stops
#define VMI_CT_MODE           0x00000003   // Command that changes simulator behavior

// Command object : describes what the command operates on
#define VMI_CO_MASK           0x00000FF0   // Bits used for the command group
#define VMI_CO_CACHE          0x00000010   // cache
#define VMI_CO_CPU            0x00000020   // processor
#define VMI_CO_CONTEXT        0x00000030   // stack trace
#define VMI_CO_DIAG           0x00000040   // diagnostics
#define VMI_CO_FUNCTION       0x00000050   // Function
#define VMI_CO_GIC            0x00000060   // GIC
#define VMI_CO_LINE           0x00000070   // code source lines
#define VMI_CO_LKM            0x00000080   // Loadable kernel module
#define VMI_CO_MEMORY         0x00000090   // Memory
#define VMI_CO_OS             0x000000A0   // OS or scheduler
#define VMI_CO_TASK           0x000000B0   // OS task
#define VMI_CO_TLB            0x000000C0   // TLB
#define VMI_CO_SYMBOL         0x000000D0   // from a symbol table

// Command action : describes what the command does
#define VMI_CA_MASK           0x000FF000   // Bits used for the command object type
#define VMI_CA_CONTROL        0x00001000   // turn something on or off
#define VMI_CA_COVER          0x00002000   // code coverage tool
#define VMI_CA_PROFILE        0x00003000   // code profiling tool
#define VMI_CA_QUERY          0x00004000   // command queries the model
#define VMI_CA_REPORT         0x00005000   // general report
#define VMI_CA_TRACE          0x00006000   // trace to log

// The parser will handle -help so the user code should not attempt
// to parse -help itself.
// Note that if the command has no arguments, then the parser
// will ignore this flag and handle -help always.
#define VMI_CT_HELP           0x00100000

//
// Type of function called by the simulator when it needs the current
// value of an argument to a processor command. This is called when
// the VMI_CAA_VALUE_CALLBACK bit was set in the argument constructor.
// processor          processor context
// type               argument type
// index              order of argument definition
// valuePtr           function should write to this using the correct type
//
#define VMIRT_ARG_VALUE_FN(_NAME)  void _NAME( \
    vmiProcessorP processor,   \
    vmiArgType    type,        \
    Uns32         index,       \
    void         *valuePtr     \
)
typedef VMIRT_ARG_VALUE_FN((*vmirtArgValueFn));

//
// Type of function called by the simulator when it needs the current
// value of an plug-in library command argument. This is called when
// the VMI_CAA_VALUE_CALLBACK bit was set in the argument constructor.
// processor          processor context
// type               argument type
// index              order of argument definition
// valuePtr           function should write to this using the correct type

#define VMIOS_ARG_VALUE_FN(_NAME)  void _NAME( \
    vmiosObjectP  object,      \
    vmiArgType    type,        \
    Uns32         index,       \
    void         *valuePtr     \
)
typedef VMIOS_ARG_VALUE_FN((*vmiosArgValueFn));

//
// Type of function called by the simulator when it needs the current
// value of an MMC command argument. This is called when
// the VMI_CAA_VALUE_CALLBACK bit was set in the argument constructor.
// processor          processor context
// type               argument type
// index              order of argument definition
// valuePtr           function should write to this using the correct type

#define VMIMMC_ARG_VALUE_FN(_NAME)  void _NAME( \
    vmimmcComponentP mmc,         \
    vmiArgType       type,        \
    Uns32            index,       \
    void            *valuePtr     \
)
typedef VMIMMC_ARG_VALUE_FN((*vmimmcArgValueFn));

