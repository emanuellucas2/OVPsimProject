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

#include "vmi/vmiAttrs.h"
#include "vmi/vmiDbg.h"
#include "vmi/vmiParameters.h"
#include "vmi/vmiPorts.h"
#include "vmi/vmiTyperefs.h"


////////////////////////////////////////////////////////////////////////////////
// VMIOS CONSTRUCTOR AND DESTRUCTOR
////////////////////////////////////////////////////////////////////////////////

//
// Model constructor
//
#define VMIOS_CONSTRUCTOR_FN(_NAME) void _NAME( \
    vmiProcessorP processor,      \
    vmiosObjectP  object,         \
    vmiosObjectP  parent,         \
    void         *parameterValues \
)
typedef VMIOS_CONSTRUCTOR_FN((*vmiosConstructorFn));

//
// Model post constructor callback
//
#define VMIOS_POST_CONSTRUCTOR_FN(_NAME) void _NAME( \
    vmiProcessorP processor,      \
    vmiosObjectP  object          \
)
typedef VMIOS_POST_CONSTRUCTOR_FN((*vmiosPostConstructorFn));

//
// Model post simulate callback
//
#define VMIOS_POST_SIMULATE_FN(_NAME) void _NAME( \
    vmiProcessorP processor,    \
    vmiosObjectP  object        \
)
typedef VMIOS_POST_SIMULATE_FN((*vmiosPostSimulateFn));

//
// Model destructor
//
#define VMIOS_DESTRUCTOR_FN(_NAME) void _NAME( \
    vmiProcessorP processor,    \
    vmiosObjectP  object        \
)
typedef VMIOS_DESTRUCTOR_FN((*vmiosDestructorFn));


////////////////////////////////////////////////////////////////////////////////
// SAVE / RESTORE
////////////////////////////////////////////////////////////////////////////////

//
// This callback function type is used to implement model save
//
#define VMIOS_SAVE_STATE_FN(_NAME) void _NAME( \
    vmiosObjectP    object,         \
    vmiSaveContextP cxt,            \
    Uns32           srVersion       \
)
typedef VMIOS_SAVE_STATE_FN((*vmiosSaveStateFn));

//
// This callback function type is used to implement model restore
//
#define VMIOS_RESTORE_STATE_FN(_NAME) void _NAME( \
    vmiosObjectP       object,      \
    vmiRestoreContextP cxt,         \
    Uns32              srVersion    \
)
typedef VMIOS_RESTORE_STATE_FN((*vmiosRestoreStateFn));


////////////////////////////////////////////////////////////////////////////////
// TYPES USED TO DEFINE INTERCEPTIONS
////////////////////////////////////////////////////////////////////////////////

//
// This defines the function type called for an intercepted function.
// 'atOpaqueIntercept' is True if the current address is opaquely intercepted
// (not necessarily by this callback) - useful for transparent intercepts that
// decode instructions and therefore need to know whether the current
// instruction is truly going to be executed
//
#define VMIOS_INTERCEPT_FN(_NAME) void _NAME( \
    vmiProcessorP processor,        \
    vmiosObjectP  object,           \
    Addr          thisPC,           \
    const char   *context,          \
    void         *userData,         \
    Bool          atOpaqueIntercept \
)
typedef VMIOS_INTERCEPT_FN((*vmiosInterceptFn));

//
// Intercept attributes (bitmask)
//
typedef enum vmiosInterceptAttrE {
    OSIA_NONE   = 0x0,              // no special attributes
    OSIA_OPAQUE = 0x1,              // opaque intercept (otherwise transparent)
    OSIA_THREAD = 0x2,              // run in thread (otherwise synchronous)
} vmiosInterceptAttr;

//
// The vmiosInterceptDesc structure describes a single intercept. If 'name' is
// non-NULL, the intercept will apply when the processor executes at that
// symbol; otherwise, the intercept applies when the processor executes at
// virtual address 'simAddress'. The intercept can be either raw or abstract,
// as described below.
//
// RAW INTERCEPT
// -------------
// For a raw intercept, 'interceptCB' is non-NULL and specifies a function of
// type vmiosInterceptFn that is called when executing at the intercept address,
// as described above. The callback will typically use calls to vmirtRegRead and
// vmirtRegWrite to directly access processor registers, and will therefore be
// processor-specific.
//
// ABI INTERCEPT
// -------------
// For an ABI (application binary interface) intercept, 'abiCB' and 'format'
// must be non-NULL. The 'format' string is a list of characters describing
// arguments that are supplied in order to 'abiCB', as follows, with the
// corresponding type required for the intercept function parameter:
//
//      'p':    the current processor                   vmiProcessorP
//      'o':    the current intercept object            vmiosObjectP
//      'c':    name of the intercepted function        const char *
//      'b':    Boolean argument using standard ABI     Bool
//      '4':    4-byte argument using standard ABI      Uns32 or Int32
//      '8':    8-byte argument using standard ABI      Uns64 or Int64
//      'a':    pointer argument using standard ABI     Addr
//      'd':    double argument using standard ABI      double
//
// 'p', 'o' and 'c' arguments are implicit and must precede all standard ABI
// arguments; all others are passed from the intercepted application function
// using the standard processor ABI. If 'returnType' is non-zero, it specifies
// the function return type using the standard application binary interface. It
// must be one of 'b', '4', '8', 'a' or 'd'.
//
// As an example, this function in application code:
//
//      Uns32 testFunc(void *a, double b, Uns64 c) {}
//
// could be intercepted using this ABI intercept description:
//
//       Name        Address Opaque Callback
//      {"testFunc", 0,      True,  VMIOS_ABI_INT('4', "poad8", testFuncInt)}
//
// with the host code ABI intercept function defined as:
//
//      static Uns32 testFuncInt(
//          vmiProcessorP processor,
//          vmiosObjectP  object,
//          Addr          a,
//          double        b,
//          Uns64         c
//      );
//
// ABI INTERCEPT RESTRICTIONS
// --------------------------
// 1. ABI intercepts are supported for PSEs, but not all processor models
//    currently support them;
// 2. A maximum of 16 function parameters is supported;
// 3. Threaded intercepts are not supported.
//
typedef struct vmiosInterceptDescS {

    // INTERCEPT DESCRIPTION
    const char        *name;        // for interception by name
    Addr               simAddress;  // for interception by address
    vmiosInterceptAttr attrs;       // intercepted function attributes

    // RAW INTERCEPT SUPPORT
    vmiosInterceptFn   interceptCB; // interception callback
    void              *userData;    // client-specific data pointer

    // ABI INTERCEPT SUPPORT
    vmiCallFn          abiCB;       // ABI callback
    const char        *format;      // arguments to ABI callback
    char               returnType;  // return type from ABI callback

} vmiosInterceptDesc;

//
// Use this macro to fill ABI intercept details
//
#define VMIOS_ABI_INT(_RETURN, _FORMAT, _CB) \
    abiCB      : (vmiCallFn)(_CB),  \
    format     : _FORMAT,           \
    returnType : _RETURN


////////////////////////////////////////////////////////////////////////////////
// INSTRUCTION INTERCEPT CALLBACKS
////////////////////////////////////////////////////////////////////////////////

//
// This routine may be used to override the default behavior of the morpher for
// a particular instruction. If the instruction should be overridden, the
// function should return a vmiosInterceptFn function for the required
// interception and set byref arguments 'opaque' (True->opaque, False->
// transparent) 'context' (a user-defined context string) and 'userData'
// (an application-specific argument passed uninterpreted to the intercept
// function); otherwise, it should return NULL.
//
#define VMIOS_MORPH_FN(_NAME) vmiosInterceptFn _NAME( \
    vmiProcessorP processor,    \
    vmiosObjectP  object,       \
    Addr          thisPC,       \
    Uns8          inDelaySlot,  \
    Bool          firstInBlock, \
    Bool          emitTrace,    \
    Bool         *opaque,       \
    const char  **context,      \
    void        **userData      \
)
typedef VMIOS_MORPH_FN((*vmiosMorphFn));

//
// This routine may be used to override the default size of an instruction. If
// the size should be overridden, the function should supply the next program
// counter using the 'nextPC' byref argument and return True; otherwise, it
// should return False.
//
#define VMIOS_NEXT_PC_FN(_NAME) Bool _NAME( \
    vmiProcessorP processor,    \
    vmiosObjectP  object,       \
    Addr          thisPC,       \
    Addr         *nextPC        \
)
typedef VMIOS_NEXT_PC_FN((*vmiosNextPCFn));

//
// Return a string representing the disassembled instruction at the passed
// address
//
#define VMIOS_DISASSEMBLE_FN(_NAME) const char *_NAME( \
    vmiProcessorP  processor,   \
    vmiosObjectP   object,      \
    Addr           thisPC,      \
    vmiDisassAttrs attrs        \
)
typedef VMIOS_DISASSEMBLE_FN((*vmiosDisassFn));


////////////////////////////////////////////////////////////////////////////////
// FORMALS
////////////////////////////////////////////////////////////////////////////////

#define VMIOS_PARAM_SPEC_FN(_NAME) vmiParameterP _NAME( \
    vmiProcessorP processor,    \
    vmiosObjectP  object,       \
    vmiosObjectP  parent,       \
    vmiParameterP prev          \
)
typedef VMIOS_PARAM_SPEC_FN((*vmiosParamSpecFn));

//
// Type of function called by simulator to get the size of the parameter value
// table
//
#define VMIOS_PARAM_TABLE_SIZE_FN(_NAME) Uns32 _NAME ( \
    vmiProcessorP processor,    \
    vmiosAttrCP   attrs,       	\
    vmiosObjectP  parent        \
)
typedef VMIOS_PARAM_TABLE_SIZE_FN((*vmiosParamValueSizeFn));


////////////////////////////////////////////////////////////////////////////////
// DEBUGGER SUPPORT
//
// The following functions are used by the Imperas multiprocessor debugger when
// no gdb is available for the processor being debugged
////////////////////////////////////////////////////////////////////////////////

//
// This function is called when the 'next' or 'step' command is issued
// to the MPD. It has two purposes:
//  1. for the debugger to determine if the operation is supported.
//  2. for the intercept library to store the current context.
//
// It should return true if the operation can be supported, false otherwise.
// Typically, for 'step' (step into) it should store the current line and file.
// For 'next' (step over) it should also store any registers required to
// determine when the program has reached the original call frame.
//
#define VMIOS_STEP_LINE_BEGIN_FN(_NAME) Bool _NAME ( \
    vmiProcessorP    processor,   \
    vmiosObjectP     object,      \
    vmiStepOperation operation,   \
    const char      *currentFile, \
    Uns32            currentLine  \
)
typedef VMIOS_STEP_LINE_BEGIN_FN((*vmiosStepLineBeginFn));

//
// This function is called when the 'next' or 'step' command is issued, but
// after each instruction step. It should return True if more instruction steps
// are required, False if the program has reached the desired location.
// Typically, for 'step' (step into) it should compare the current line and file
// with the stored values.
// For 'next' (step over) it should also compare any registers required to
// determine when the program has reached the original call frame.
//
// These functions will depend on the ABI used by the current program.
//
#define VMIOS_STEP_LINE_ITERATE_FN(_NAME) Bool _NAME ( \
    vmiProcessorP    processor,   \
    vmiosObjectP     object,      \
    vmiStepOperation operation,   \
    const char      *currentFile, \
    Uns32            currentLine  \
)
typedef VMIOS_STEP_LINE_ITERATE_FN((*vmiosStepLineIterateFn));

//
// This function is called to get the list of return values on the stack.
// The first is the current address, subsequent addresses follow.
// The number of entries is returned,
//
#define VMIOS_STACK_FN(_NAME) Uns32 _NAME ( \
    vmiProcessorP processor,    \
    vmiosObjectP  object,       \
    Addr         *array,        \
    Uns32         maxEntries    \
)
typedef VMIOS_STACK_FN((*vmiosStackFn));

//
// This function is called to evaluate an expression.
//
#define VMIOS_EXPRESSION_FN(_NAME) Uns32 _NAME ( \
    vmiProcessorP processor,    \
    vmiosObjectP  object,       \
    const char   *expression,   \
    Uns32         maxLength,    \
    char         *result        \
)
typedef VMIOS_EXPRESSION_FN((*vmiosExpressionFn));


////////////////////////////////////////////////////////////////////////////////
// DOCUMENTATION CALLBACKS
////////////////////////////////////////////////////////////////////////////////

//
// Documentation constructor
//
#define VMIOS_DOC_FN(_NAME) void _NAME( \
    vmiProcessorP processor, \
    vmiosObjectP  object     \
)
typedef VMIOS_DOC_FN((*vmiosDocFn));


//
// This structure defines attributes for semihosting support
//
typedef struct vmiosAttrS {

    ////////////////////////////////////////////////////////////////////////
    // VERSION & TYPE
    ////////////////////////////////////////////////////////////////////////

    const char         *versionString;      // version string (THIS MUST BE FIRST)
    vmiModelType        modelType;          // type of model (enum)
    const char         *packageName;        // package name
    Uns32               objectSize;         // size in bytes of VMIOS object
    Bool                allLevels;          // apply at all levels (leaf if False)

    ////////////////////////////////////////////////////////////////////////
    // MODEL STATUS
    ////////////////////////////////////////////////////////////////////////

    vmiVisibility       visibility;         // model visibility (enum)
    vmiReleaseStatus    releaseStatus;      // model release status (enum)

    ////////////////////////////////////////////////////////////////////////
    // SAVE/RESTORE ROUTINES
    ////////////////////////////////////////////////////////////////////////

    vmiosSaveStateFn    saveCB;             // model state save callback
    vmiosRestoreStateFn restoreCB;          // model state restore callback
    Uns32               srVersion;          // model save/restore version

    ////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////

    vmiosConstructorFn     constructorCB;      // constructor
    vmiosPostConstructorFn postConstructorCB;  // post-constructor
    vmiosPostSimulateFn    postSimulateCB;     // post-simulation, pre-destruction
    vmiosDestructorFn      destructorCB;       // destructor

    ////////////////////////////////////////////////////////////////////////
    // INSTRUCTION INTERCEPT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    vmiosMorphFn        morphCB;            // morph override callback
    vmiosNextPCFn       nextPCCB;           // get next instruction address
    vmiosDisassFn       disCB;              // disassemble instruction

    ////////////////////////////////////////////////////////////////////////
    // DEBUGGER INTEGRATION SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////

    vmiosRegGroupFn     regGroupCB;         // regGroup callback
    vmiosRegInfoFn      regInfoCB;          // regInfo callback
    vmiosRegImplFn      regImplCB;          // vmiReg-to-vmiRegInfoCP callback

    ////////////////////////////////////////////////////////////////////////
    // FORMAL PARAMETERS iterators to find parameters accepted by this model
    ////////////////////////////////////////////////////////////////////////

    vmiosParamSpecFn      paramSpecsCB;     // callback for next formal param
    vmiosParamValueSizeFn paramValueSizeCB; // callback to get size of table

    ////////////////////////////////////////////////////////////////////////
    // PORT ACCESS ROUTINES iterators to find the bus and net ports
    ////////////////////////////////////////////////////////////////////////

    vmiosBusPortSpecsFn   busPortSpecsCB;   // callback for next bus port
    vmiosNetPortSpecsFn   netPortSpecsCB;   // callback for next net port
    vmiosFifoPortSpecsFn  fifoPortSpecsCB;  // callback for next fifo port

    ////////////////////////////////////////////////////////////////////////
    // DEBUGGER ASSISTANCE
    ////////////////////////////////////////////////////////////////////////

    vmiosStepLineBeginFn   stepLineBeginCB;  // callback to begin next operation
    vmiosStepLineIterateFn stepLineIterateCB;// callback to see if next is done
    vmiosStackFn           stackCB;          // callback to get return addresses
    vmiosExpressionFn      expressionCB;     // callback to evaluate an expression

    ////////////////////////////////////////////////////////////////////////
    // MODEL VLNV
    ////////////////////////////////////////////////////////////////////////

    vmiVlnvInfo         vlnv;               // vendor/library/name/version

    ////////////////////////////////////////////////////////////////////////////
    // DOCUMENTATION CALLBACKS
    ////////////////////////////////////////////////////////////////////////////

    vmiosDocFn          docCB;              // construct documentation

    ////////////////////////////////////////////////////////////////////////
    // ADDRESS INTERCEPT DEFINITIONS
    ////////////////////////////////////////////////////////////////////////

    vmiosInterceptDesc  intercepts[];       // null-terminated intercept list

} vmiosAttr;


