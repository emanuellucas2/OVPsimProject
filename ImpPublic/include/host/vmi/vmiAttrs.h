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
#include "vmi/vmiDbg.h"
#include "vmi/vmiCxt.h"
#include "vmi/vmiCacheAttrs.h"
#include "vmi/vmiModelInfo.h"
#include "vmi/vmiParameters.h"
#include "vmi/vmiPorts.h"
#include "vmi/vmiTypes.h"
#include "vmi/vmiTyperefs.h"
#include "vmi/vmiVersion.h"


////////////////////////////////////////////////////////////////////////////////
// PROCESSOR CONSTRUCTOR & DESTRUCTOR
////////////////////////////////////////////////////////////////////////////////

//
// This callback function should full the buffer 'name' with the name to use
// for the child with index number 'smpIndex' of the given parent processor.
// The name must not exceed 1024 characters.
//
#define VMI_SMP_NAME_FN(_NAME) void _NAME( \
    char         *name,     \
    vmiProcessorP parent,   \
    Uns32         smpIndex  \
)
typedef VMI_SMP_NAME_FN((*vmiSMPNameFn));

//
// Processor constructor
//
#define VMI_CONSTRUCTOR_FN(_NAME) void _NAME( \
    vmiProcessorP  processor,           \
    Bool           simulateExceptions,  \
    vmiSMPContextP smpContext,          \
    void          *parameterValues      \
)
typedef VMI_CONSTRUCTOR_FN((*vmiConstructorFn));

//
// Processor post-constructor
//
#define VMI_POST_CONSTRUCTOR_FN(_NAME) void _NAME( \
    vmiProcessorP  processor            \
)
typedef VMI_POST_CONSTRUCTOR_FN((*vmiPostConstructorFn));

//
// Processor virtual memory initialization
//
#define VMI_VMINIT_FN(_NAME) void _NAME( \
    vmiProcessorP  processor,            \
    memDomainPP    codeDomains,          \
    memDomainPP    dataDomains           \
)
typedef VMI_VMINIT_FN((*vmiVMInitFn));

//
// Post simulate callback
// (called after simulation  but before tear-down begins)
//
#define VMI_POST_SIMULATE_FN(_NAME) void _NAME(vmiProcessorP processor)
typedef VMI_POST_SIMULATE_FN((*vmiPostSimulateFn));

//
// Processor destructor
//
#define VMI_DESTRUCTOR_FN(_NAME) void _NAME(vmiProcessorP processor)
typedef VMI_DESTRUCTOR_FN((*vmiDestructorFn));


////////////////////////////////////////////////////////////////////////////////
// SAVE / RESTORE
////////////////////////////////////////////////////////////////////////////////

//
// This callback function type is used to implement processor save
//
#define VMI_SAVE_STATE_FN(_NAME) void _NAME( \
    vmiProcessorP       processor,  \
    vmiSaveContextP     cxt,        \
    vmiSaveRestorePhase phase,      \
    Uns32               srVersion   \
)
typedef VMI_SAVE_STATE_FN((*vmiSaveStateFn));

//
// This callback function type is used to implement processor restore
//
#define VMI_RESTORE_STATE_FN(_NAME) void _NAME( \
    vmiProcessorP       processor,  \
    vmiRestoreContextP  cxt,        \
    vmiSaveRestorePhase phase,      \
    Uns32               srVersion   \
)
typedef VMI_RESTORE_STATE_FN((*vmiRestoreStateFn));


////////////////////////////////////////////////////////////////////////////////
// SIMULATED PROCESSOR ACTION CALLBACKS
////////////////////////////////////////////////////////////////////////////////

//
// This callback function type defines functions that are called just before
// a code block translation starts (startBlockCB) and just after a block
// translation completes (endBlockCB). The callbacks may be used to initialize
// and finalize data structures required by the translation function below.
// 'thisPC' and 'inDelaySlot' arguments have the same meanings as for the code
// translation function of type vmiMorphFn, documented below. 'blockState'
// is passed a pointer to a model-defined structure of size given by the
// 'blockStateSize' field in the vmiIASAttr structure definition for the
// processor; the 'blockState' structure is initialized to zero and should be
// used to hold state required while the translation of a single code block
// is in progress. 'reason' indicates the reason for the translation: see the
// comment associated with the vmiMorphReason type definition for more
// information
//
#define VMI_START_END_BLOCK_FN(_NAME) void _NAME( \
    vmiProcessorP  processor,   \
    Addr           thisPC,      \
    Uns8           inDelaySlot, \
    vmiMorphReason reason,      \
    void          *blockState   \
)
typedef VMI_START_END_BLOCK_FN((*vmiStartEndBlockFn));

//
// This callback function type defines a function used to translate a single
// processor instruction at address 'thisPC'. On processors that support delay
// slots, a non-zero value of 'inDelaySlot' indicates that this is a delay
// slot instruction at the specified offset from the jump instruction for which
// this delay slot instruction applies. 'firstInBlock' is True if this
// instruction is the first in a code block. 'emitTrace' is True if the current
// code block has trace enabled.
//
// 'blockState' is passed a pointer to a model-defined structure of size given
// by the 'blockStateSize' field in the vmiIASAttr structure definition for the
// processor. The 'blockState' structure is initialized to zero at the start
// of each code block and should be used to hold state common to all
// instructions in a code block.
//
// 'instrState' is passed a pointer to a model-defined structure of size given
// by the 'instrStateSize' field in the vmiIASAttr structure definition for the
// processor. The 'instrState' structure is initialized to zero before each
// instruction and should be used to hold state for that instruction.
//
// Processors may define up to three functions of this type, with the following
// field names in the vmiIASAttr structure:
//
// preMorphCB
// ----------
// This function is called *before* an instruction is translated. Typically, it
// will initialize fields in the blockState and instrState structures for later
// use in the morphCB callback. The function is called whether or not the
// instruction is opaquely intercepted; it may be omitted (set to zero) if no
// special pre-instruction actions are required.
//
// morphCB
// -------
// This function implements behavior for the current instruction, unless it is
// opaquely intercepted. It should not be omitted.
//
// postMorphCB
// -----------
// This function is called *after* an instruction is translated. Typically, it
// will perform common actions required at the end of all instructions. The
// function is called whether or not the instruction is opaquely intercepted;
// it may be omitted (set to zero) if no special post-instruction actions are
// required.
//
#define VMI_MORPH_FN(_NAME) void _NAME( \
    vmiProcessorP processor,    \
    Addr          thisPC,       \
    Uns8          inDelaySlot,  \
    Bool          firstInBlock, \
    Bool          emitTrace,    \
    void         *blockState,   \
    void         *instrState    \
)
typedef VMI_MORPH_FN((*vmiMorphFn));

//
// This callback function type defines a function that is called instead of the
// vmiMorphFn above for instructions that have been opaquely intercepted. The
// purpose of the function is to allow processor state to be updated even if
// the instruction implementation is elsewhere.
//
#define VMI_POST_OPAQUE_FN(_NAME) void _NAME( \
    vmiProcessorP processor,    \
    Addr          thisPC,       \
    Uns8          inDelaySlot   \
)
typedef VMI_POST_OPAQUE_FN((*vmiPostOpaqueFn));

//
// This callback function type defines a routine that is called to snap
// instruction fetch addresses if required
//
#define VMI_FETCH_SNAP_FN(_NAME) Addr _NAME( \
    vmiProcessorP processor,    \
    Addr          thisPC        \
)
typedef VMI_FETCH_SNAP_FN((*vmiFetchSnapFn));

//
// Callback to handle misaligned read or write accesses when these should either
// cause the read/write address to be snapped or cause the read/written value to
// be rotated, or both. The return value should be constructed using the
// MEM_SNAP macro defined in vmiTypes.h. A return value of zero indicates no
// address snapping or rotation is required and that the read alignment
// exception handler should be called.
//
#define VMI_RD_WR_SNAP_FN(_NAME) Uns32 _NAME( \
    vmiProcessorP processor,    \
    memDomainP    domain,       \
    Addr          address,      \
    Uns32         bytes         \
)
typedef VMI_RD_WR_SNAP_FN((*vmiRdWrSnapFn));

//
// Callback to handle memory read privilege exceptions
//
#define VMI_RD_PRIV_EXCEPT_FN(_NAME) void _NAME( \
    vmiProcessorP       processor,  \
    memDomainP          domain,     \
    Addr                address,    \
    Uns32               bytes,      \
    void               *value,      \
    memAccessAttrs      attrs,      \
    vmiLoadStoreAction *action      \
)
typedef VMI_RD_PRIV_EXCEPT_FN((*vmiRdPrivExceptFn));

//
// Callback to handle memory write privilege exceptions
//
#define VMI_WR_PRIV_EXCEPT_FN(_NAME) void _NAME( \
    vmiProcessorP       processor,  \
    memDomainP          domain,     \
    Addr                address,    \
    Uns32               bytes,      \
    const void         *value,      \
    memAccessAttrs      attrs,      \
    vmiLoadStoreAction *action      \
)
typedef VMI_WR_PRIV_EXCEPT_FN((*vmiWrPrivExceptFn));

//
// Callback to handle memory read alignment exceptions.
//
#define VMI_RD_ALIGN_EXCEPT_FN(_NAME) Uns32 _NAME( \
    vmiProcessorP processor,    \
    memDomainP    domain,       \
    Addr          address,      \
    Uns32         bytes,        \
    void         *value         \
)
typedef VMI_RD_ALIGN_EXCEPT_FN((*vmiRdAlignExceptFn));

//
// Callback to handle memory write alignment exceptions.
//
#define VMI_WR_ALIGN_EXCEPT_FN(_NAME) Uns32 _NAME( \
    vmiProcessorP processor,    \
    memDomainP    domain,       \
    Addr          address,      \
    Uns32         bytes,        \
    const void   *value         \
)
typedef VMI_WR_ALIGN_EXCEPT_FN((*vmiWrAlignExceptFn));

//
// Callback to handle memory read abort exceptions (generated by calls to
// icmAbortRead in memory read callbacks). isFetch is True if this is an
// instruction fetch and False otherwise.
//
#define VMI_RD_ABORT_EXCEPT_FN(_NAME) void _NAME( \
    vmiProcessorP processor,    \
    Addr          address,      \
    Bool          isFetch       \
)
typedef VMI_RD_ABORT_EXCEPT_FN((*vmiRdAbortExceptFn));

//
// Callback to handle memory write abort exceptions (generated by calls to
// icmAbortWrite in memory read callbacks).
//
#define VMI_WR_ABORT_EXCEPT_FN(_NAME) void _NAME( \
    vmiProcessorP processor,    \
    Addr          address       \
)
typedef VMI_WR_ABORT_EXCEPT_FN((*vmiWrAbortExceptFn));

//
// Callback to handle illegal device memory read exceptions.
//
#define VMI_RD_DEVICE_EXCEPT_FN(_NAME) Bool _NAME( \
    vmiProcessorP processor,    \
    memDomainP    domain,       \
    Addr          address,      \
    Uns32         bytes,        \
    void         *value         \
)
typedef VMI_RD_DEVICE_EXCEPT_FN((*vmiRdDeviceExceptFn));

//
// Callback to handle illegal device memory write exceptions.
//
#define VMI_WR_DEVICE_EXCEPT_FN(_NAME) Bool _NAME( \
    vmiProcessorP processor,    \
    memDomainP    domain,       \
    Addr          address,      \
    Uns32         bytes,        \
    const void   *value         \
)
typedef VMI_WR_DEVICE_EXCEPT_FN((*vmiWrDeviceExceptFn));

//
// Callback to handle divide-by-zero and integer overflow errors resulting from
// JIT code divide and remainder operations (i.e. morph-time primitives using
// vmi_IDIV, vmi_DIV, vmi_IREM or vmi_REM binary operations). The callback can
// either override the results (by assigning fields within the 'divideResults'
// structure) or invoke code to take an exception. Argument 'divideInfo' gives
// details of the operands causing the error (note that for a divide-by-zero
// error, divideInfo->divisor is zero; for integer overflow, divideInfo->divisor
// is -1).
//
#define VMI_ARITH_RESULT_FN(_NAME) void _NAME( \
    vmiProcessorP    processor,     \
    vmiDivideInfoCP  divideInfo,    \
    vmiDivideResultP divideResults  \
)
typedef VMI_ARITH_RESULT_FN((*vmiArithResultFn));

//
// Callback to handle general divide-by-zero and integer overflow errors, either
// within JIT code (if exceptionContext is VMI_EXCEPT_CXT_CODE) or in an
// embedded function call (if exceptionContext is VMI_EXCEPT_CXT_CALL).
// The return value indicates how the simulator should handle any remaining
// portion of the current simulated instruction: if VMI_INTEGER_ABORT, then
// execution should resume at the start of the next simulated instruction; if
// VMI_INTEGER_CONTINUE, then the remaining part of this instruction should be
// executed. Argument 'divideInfo' gives details of the operands causing the
// error.
//
// Unless it is necessary to handle divide-by-zero and integer overflow errors
// within embedded function calls, use the simpler interface defined using a
// vmiArithResultFn function instead.
//
#define VMI_ARITH_EXCEPT_FN(_NAME) vmiIntegerExceptionResult _NAME( \
    vmiProcessorP           processor,          \
    vmiIntegerExceptionType exceptionType,      \
    vmiExceptionContext     exceptionContext,   \
    vmiDivideInfoCP         divideInfo          \
)
typedef VMI_ARITH_EXCEPT_FN((*vmiArithExceptFn));

//
// Callback for fetch exception handler for an instruction fetch at the passed
// address. If no exception is pending, return VMI_FETCH_NONE. If an exception
// is pending and the machine state has been modified to handle it, return
// VMI_FETCH_EXCEPTION_COMPLETE.
//
// If it is required that the register dump associated with the instruction
// causing the exception should show the processor state *before* it is updated,
// return VMI_FETCH_EXCEPTION_PENDING (without updating processor state) if
// 'complete' is False. The register dump will then be emitted and the fetch
// exception handler called a second time with the 'complete' argument set to
// True indicating that the machine state should be updated
//
#define VMI_IFETCH_FN(_NAME) vmiFetchAction _NAME( \
    vmiProcessorP processor,    \
    memDomainP    domain,       \
    Addr          address,      \
    Bool          complete,     \
    Bool          annulled      \
)
typedef VMI_IFETCH_FN((*vmiIFetchFn));

//
// Return the current processor endianness for instruction (if isFetch is True)
// or data (if isFetch is False)
//
#define VMI_ENDIAN_FN(_NAME) memEndian _NAME( \
    vmiProcessorP processor,    \
    Bool          isFetch       \
)
typedef VMI_ENDIAN_FN((*vmiEndianFn));

//
// Return the next instruction address after the current address
//
#define VMI_NEXT_PC_FN(_NAME) Addr _NAME(vmiProcessorP processor, Addr thisPC)
typedef VMI_NEXT_PC_FN((*vmiNextPCFn));

//
// Use processor model to fetch an instruction at the given address, filling
// by-ref argument 'value' with the fetched bytes and returning the number of
// bytes fetched. This is used by VMI function vmicxtFetch.
//
#define VMI_FETCH_FN(_NAME) Uns32 _NAME( \
    vmiProcessorP processor,    \
    Addr          thisPC,       \
    void         *value         \
)
typedef VMI_FETCH_FN((*vmiFetchFn));

//
// Return a string representing the disassembled instruction at the passed
// address
//
#define VMI_DISASSEMBLE_FN(_NAME) const char *_NAME( \
    vmiProcessorP  processor,   \
    Addr           thisPC,      \
    vmiDisassAttrs attrs        \
)
typedef VMI_DISASSEMBLE_FN((*vmiDisassFn));

//
// This callback is called on a processor context switch. 'state' describes the
// new state.
//
#define VMI_IASSWITCH_FN(_NAME) void _NAME( \
    vmiProcessorP  processor,   \
    vmiIASRunState state        \
)
typedef VMI_IASSWITCH_FN((*vmiIASSwitchFn));

//
// This callback should create code to cause a processor to return from an
// opaque intercept
//
#define VMI_INT_RETURN_FN(_NAME) void _NAME( \
    vmiProcessorP processor,    \
    Addr          thisPC        \
)
typedef VMI_INT_RETURN_FN((*vmiintReturnFn));

//
// This callback should create code to assign the function result of an
// Imperas intercepted call to the result register of the processor, using the
// standard processor procedure call ABI. The function result type is described
// by the passed format argument, which can be any of the following:
//
//      '4':    4-byte result (e.g. Uns32 type)
//      '8':    8-byte result (e.g. Uns64 type)
//      'a':    address result (normally Uns32 or Uns64)
//      'd':    double result (Flt64)
//
#define VMI_INT_RESULT_FN(_NAME) void _NAME( \
    vmiProcessorP processor,    \
    char          format        \
)
typedef VMI_INT_RESULT_FN((*vmiintResultFn));

//
// This callback should create code to push function parameters before making
// an Imperas intercepted call. The function parameters are presented using the
// standard processor procedure call ABI. The function parameters are described
// by the passed format string. This string can contain a sequence of any of the
// following:
//
//      '4':    push Uns32 function argument using vmimtArgReg(32, ...)
//      '8':    push Uns64 function argument using vmimtArgReg(64, ...)
//      'a':    push address function argument using vmimtArgRegSimAddress(...)
//      'd':    push Flt64 function argument using vmimtArgFlt64(...)
//
// For example, a format string of "84a" requires arguments to be pushed for a
// function that takes an 8-byte argument followed by a 4-byte argument followed
// by an address argument.
//
#define VMI_INT_PAR_FN(_NAME) void _NAME( \
    vmiProcessorP processor,    \
    const char   *format,       \
    char          formatResult  \
)
typedef VMI_INT_PAR_FN((*vmiintParFn));

//
// Invoke encapsulated simulator to simulate for 'count' instructions. Return
// the number of instructions actually executed.
//
#define VMI_ENCAP_SIM_FN(_NAME) Uns32 _NAME( \
    vmiProcessorP processor,    \
    Uns32         count         \
)
typedef VMI_ENCAP_SIM_FN((*vmiEncapSimFn));

//
// Get program counter for encapsulated simulator processor
//
#define VMI_ENCAP_GET_PC_FN(_NAME) Addr _NAME( \
    vmiProcessorP processor,    \
    Uns8         *slotD         \
)
typedef VMI_ENCAP_GET_PC_FN((*vmiEncapGetPCFn));

//
// Get instruction count for encapsulated simulator processor
//
#define VMI_ENCAP_ICOUNT_FN(_NAME) Uns64 _NAME(vmiProcessorP processor)
typedef VMI_ENCAP_ICOUNT_FN((*vmiEncapICountFn));

//
// Type of function called by simulator to get the size of the parameter value
// table
//
#define VMI_PROC_PARAM_TABLE_SIZE_FN(_NAME) Uns32 _NAME ( \
    vmiProcessorP processor,    \
    const char   *variant       \
)
typedef VMI_PROC_PARAM_TABLE_SIZE_FN((*vmiParamValueSizeFn));

typedef struct vmiConstructValuesS *vmiConstructValuesP;

//
// Type of function called by simulator to get info about the parameters of this
// model
//
#define VMI_PROC_PARAM_SPECS_FN(_NAME) vmiParameterP _NAME ( \
    vmiProcessorP        processor,      \
    vmiParameterP        prev,           \
    vmiConstructValuesP *parameterValues \
)
typedef VMI_PROC_PARAM_SPECS_FN((*vmiParamSpecsFn));

//
// Type of function called by simulator to set a pointer to the pre-construction
// parameter table
//
#define VMI_SET_PARAM_VALUES_FN(_NAME) void _NAME ( \
    vmiProcessorP        processor,      \
    vmiConstructValuesP *parameterValues \
)
typedef VMI_SET_PARAM_VALUES_FN((*vmiSetParamValuesFn));

//
// Type of function called by simulator to get info about the parameters of this
// model
//
#define VMI_EVALUATE_CONDITION_FN(_NAME) Bool _NAME ( \
    vmiProcessorP processor,    \
    Uns32         condition     \
)
typedef VMI_EVALUATE_CONDITION_FN((*vmiEvaluateConditionFn));


////////////////////////////////////////////////////////////////////////////////
// DOCUMENTATION CALLBACKS
////////////////////////////////////////////////////////////////////////////////

//
// Processor documentation constructor
//
#define VMI_DOC_FN(_NAME) void _NAME(vmiProcessorP processor)
typedef VMI_DOC_FN((*vmiDocFn));


//
// This structure describes attributes for instruction-accurate modeling for a
// particular processor
//
typedef struct vmiIASAttrS {

    ////////////////////////////////////////////////////////////////////////////
    // VERSION & TYPE
    ////////////////////////////////////////////////////////////////////////////

    const char      *versionString;     // version string (THIS MUST BE FIRST)
    vmiModelType     modelType;         // model type (THIS MUST BE SECOND)

    ////////////////////////////////////////////////////////////////////////////
    // MODEL STATUS
    ////////////////////////////////////////////////////////////////////////////

    vmiVisibility    visibility;        // model instance invisibility (enum)
    vmiReleaseStatus releaseStatus;     // model release status (enum)

    ////////////////////////////////////////////////////////////////////////////
    // SIZE ATTRIBUTES
    ////////////////////////////////////////////////////////////////////////////

    const char    **dictNames;          // null-terminated dictionary name list
    Uns32           cpuSize;            // full size of CPU object
    Uns32           blockStateSize;     // size of block state structure
    Uns32           instrStateSize;     // size of instruction state structure

    ////////////////////////////////////////////////////////////////////////////
    // SAVE/RESTORE ROUTINES
    ////////////////////////////////////////////////////////////////////////////

    vmiSaveStateFn    saveCB;           // processor state save callback
    vmiRestoreStateFn restoreCB;        // processor state restore callback
    Uns32             srVersion;        // model save/restore version

    ////////////////////////////////////////////////////////////////////////////
    // CONSTRUCTOR/DESTRUCTOR ROUTINES
    ////////////////////////////////////////////////////////////////////////////

    vmiSMPNameFn         smpNameCB;         // get SMP component name
    vmiConstructorFn     constructorCB;     // constructor
    vmiPostConstructorFn postConstructorCB; // post-constructor
    vmiVMInitFn          vmInitCB;          // virtual memory initialization
    vmiPostSimulateFn    postSimulateCB;    // post-simulate, pre-destruction
    vmiDestructorFn      destructorCB;      // destructor

    ////////////////////////////////////////////////////////////////////////////
    // MORPHER CORE ROUTINES
    ////////////////////////////////////////////////////////////////////////////

    vmiStartEndBlockFn startBlockCB;    // called before block translate
    vmiStartEndBlockFn endBlockCB;      // called after block translate
    vmiMorphFn         preMorphCB;      // called at start of each instruction
    vmiMorphFn         morphCB;         // morph callback
    vmiMorphFn         postMorphCB;     // called at end of each instruction
    vmiPostOpaqueFn    postOpaqueCB;    // called after opaque intercept
    vmiFetchSnapFn     fetchSnapCB;     // fetch address snap callback
    vmiRdWrSnapFn      rdSnapCB;        // read alignment snap function
    vmiRdWrSnapFn      wrSnapCB;        // write alignment snap function

    ////////////////////////////////////////////////////////////////////////////
    // SIMULATION SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////////

    vmiEndianFn    getEndianCB;         // get processor endianness
    vmiNextPCFn    nextPCCB;            // get next instruction address
    vmiFetchFn     fetchCB;             // fetch instruction
    vmiDisassFn    disCB;               // disassemble instruction
    vmiIASSwitchFn switchCB;            // call on simulator context switch

    ////////////////////////////////////////////////////////////////////////////
    // EXCEPTION ROUTINES
    ////////////////////////////////////////////////////////////////////////////

    vmiRdPrivExceptFn   rdPrivExceptCB;     // read privilege exception
    vmiWrPrivExceptFn   wrPrivExceptCB;     // write privilege exception
    vmiRdAlignExceptFn  rdAlignExceptCB;    // read alignment exception
    vmiWrAlignExceptFn  wrAlignExceptCB;    // write alignment exception
    vmiRdAbortExceptFn  rdAbortExceptCB;    // read abort exception
    vmiWrAbortExceptFn  wrAbortExceptCB;    // write abort exception
    vmiRdDeviceExceptFn rdDeviceExceptCB;   // read device exception
    vmiWrDeviceExceptFn wrDeviceExceptCB;   // write device exception
    vmiIFetchFn         ifetchExceptCB;     // execution privilege exception
    vmiArithResultFn    arithResultCB;      // JIT arithmetic exception
    vmiArithExceptFn    arithExceptCB;      // general arithmetic exception
    vmiICountFn         icountExceptCB;     // instruction count exception

    ////////////////////////////////////////////////////////////////////////////
    // INSTRUCTION ATTRIBUTES SUPPORT
    ////////////////////////////////////////////////////////////////////////////

    vmiEvaluateConditionFn evalConditionCB; // call to evaluate condition

    ////////////////////////////////////////////////////////////////////////////
    // DEBUGGER INTEGRATION SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////////

    vmiRegGroupFn      regGroupCB;      // register group iterator
    vmiRegInfoFn       regInfoCB;       // register iterator
    vmiRegAliasFn      regAliasCB;      // register alias-to-base-name mapping
    vmiRegImplFn       regImplCB;       // vmiReg-to-vmiRegInfoCP callback
    vmiExceptionInfoFn exceptionInfoCB; // exceptionInfo callback
    vmiModeInfoFn      modeInfoCB;      // modeInfo callback
    vmiGetExceptionFn  getExceptionCB;  // return current processor exception
    vmiGetModeFn       getModeCB;       // return current processor mode
    vmiRegReadFn       regReadCB;       // default regRead callback
    vmiRegWriteFn      regWriteCB;      // default regWrite callback
    vmiTraceFn         traceCB;         // model-specific instruction trace
    vmiTraceMemAttrsFn traceMemAttrsCB; // model-specific memory attributes
    vmiDebugFn         debugCB;         // model-specific register dump
    vmiProcDescFn      procDescCB;      // processor description callback
    Uns8               codeGrain;       // granularity of instruction address
    Uns8               dataGrain;       // granularity of data address

    ////////////////////////////////////////////////////////////////////////////
    // FORMAL PARAMETER ITERATION
    ////////////////////////////////////////////////////////////////////////////

    vmiParamValueSizeFn paramValueSizeCB;   // get parameter value table size
    vmiParamSpecsFn     preParamSpecsCB;    // iterate model  parameters
                                            // required before construction
    vmiParamSpecsFn     paramSpecsCB;       // iterator to get full list of
                                            // model parameters
    vmiSetParamValuesFn preParamValuesCB;   // called by simulator to set
                                            // pointer to table of values

    ////////////////////////////////////////////////////////////////////////////
    // PORT ACCESS ROUTINES
    ////////////////////////////////////////////////////////////////////////////

    vmiBusPortSpecsFn   busPortSpecsCB;     // callback for next bus port
    vmiNetPortSpecsFn   netPortSpecsCB;     // callback for next net port
    vmiFifoPortSpecsFn  fifoPortSpecsCB;    // callback for next fifo port

    ////////////////////////////////////////////////////////////////////////////
    // IMPERAS INTERCEPTED FUNCTION SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////////

    vmiintReturnFn   intReturnCB;       // morph return from opaque intercept
    vmiintResultFn   intResultCB;       // morph intercepted function result
    vmiintParFn      intParCB;          // morph function arguments

    ////////////////////////////////////////////////////////////////////////////
    // ENCAPSULATED EXTERNAL SIMULATOR SUPPORT
    ////////////////////////////////////////////////////////////////////////////

    vmiEncapSimFn    encapSimCB;        // simulate for a number of instructions
    vmiEncapGetPCFn  encapGetPCCB;      // get processor program counter
    vmiEncapICountFn encapICountCB;     // get processor instruction count

    ////////////////////////////////////////////////////////////////////////////
    // SIMULATOR ENVIRONMENT SUPPORT
    ////////////////////////////////////////////////////////////////////////////

    vmiProcessorInfoFn procInfoCB;      // get the procInfo structure

    ////////////////////////////////////////////////////////////////////////////
    // CACHE SUPPORT ROUTINES
    ////////////////////////////////////////////////////////////////////////////

    vmiCacheRegisterFn cacheRegisterCB; // register cache support functions

    ////////////////////////////////////////////////////////////////////////////
    // DOCUMENTATION CALLBACKS
    ////////////////////////////////////////////////////////////////////////////

    vmiDocFn docCB;                     // construct the documentation

    ////////////////////////////////////////////////////////////////////////////
    // PSE INTEGRATION SUPPORT
    ////////////////////////////////////////////////////////////////////////////

    vmipseAttrsCP pseAttrs;             // PSE support functions

} vmiIASAttr;

