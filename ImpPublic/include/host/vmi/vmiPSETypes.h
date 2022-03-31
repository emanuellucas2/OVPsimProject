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

// basic types
#include "hostapi/impTypes.h"
#include "hostapi/typeMacros.h"

// VMI area includes
#include "vmi/vmiTyperefs.h"

//
// PSE net handle
//
typedef Uns32 vmipseNetHandle;

//
// PSE event handle
//
typedef Uns32 vmipseEventHandle;

//
// Return initialised argument block for the given PSE using the supplied stack
// pointer and link address. If sp is -1, the current stack pointer is used.
//
#define VMIPSE_INIT_ARGS_FN(_NAME) vmipseArgBlockP _NAME( \
    vmiProcessorP pse,  \
    Uns32         sp,   \
    Uns32         lr    \
)
typedef VMIPSE_INIT_ARGS_FN((*vmipseInitArgsFn));

//
// Finalise arguments to create stack frame
//
#define VMIPSE_END_ARGS_FN(_NAME) void _NAME(vmipseArgBlockP block)
typedef VMIPSE_END_ARGS_FN((*vmipseEndArgsFn));

//
// Get 32-bit result register
//
#define VMIPSE_GET_RESULT32_FN(_NAME) Uns32 _NAME(vmiProcessorP pse)
typedef VMIPSE_GET_RESULT32_FN((*vmipseGetResult32Fn));

//
// Set 32-bit result register
//
#define VMIPSE_SET_RESULT32_FN(_NAME) void _NAME(vmiProcessorP pse, Uns32 value)
typedef VMIPSE_SET_RESULT32_FN((*vmipseSetResult32Fn));

//
// Get pointer-sized result register
//
#define VMIPSE_GET_RESULTP_FN(_NAME) Addr _NAME(vmiProcessorP pse)
typedef VMIPSE_GET_RESULTP_FN((*vmipseGetResultPFn));

//
// Get stack pointer register
//
#define VMIPSE_GET_SP_FN(_NAME) Addr _NAME(vmiProcessorP pse)
typedef VMIPSE_GET_SP_FN((*vmipseGetSPFn));

//
// Set stack pointer register
//
#define VMIPSE_SET_SP_FN(_NAME) void _NAME(vmiProcessorP pse, Addr sp)
typedef VMIPSE_SET_SP_FN((*vmipseSetSPFn));

//
// Add Uns32 argument to argument block
//
#define VMIPSE_ARG32_FN(_NAME) void _NAME(vmipseArgBlockP block, Uns32 arg)
typedef VMIPSE_ARG32_FN((*vmipseArg32Fn));

//
// Add Uns64 argument to argument block
//
#define VMIPSE_ARG64_FN(_NAME) void _NAME(vmipseArgBlockP block, Uns64 arg)
typedef VMIPSE_ARG64_FN((*vmipseArg64Fn));

//
// Add address argument to argument block
//
#define VMIPSE_ARGA_FN(_NAME) void _NAME(vmipseArgBlockP block, Addr arg)
typedef VMIPSE_ARGA_FN((*vmipseArgAFn));

//
// Return the address of a buffer capable of holding 'bytes' on the stack above
// the pending synthesized call argument block
//
#define VMIPSE_ALLOCA_FN(_NAME) Uns32 _NAME(vmipseArgBlockP block, Uns32 bytes)
typedef VMIPSE_ALLOCA_FN((*vmipseAllocAFn));

//
// PSE support callbacks (when processor is used to implement a PSE)
//
typedef struct vmipseAttrsS {
    vmipseInitArgsFn    initArgs;       // initialise arguments
    vmipseEndArgsFn     endArgs;        // finalise arguments
    vmipseGetResult32Fn getResult32;    // get 32-bit result register
    vmipseSetResult32Fn setResult32;    // set 32-bit result register
    vmipseGetResultPFn  getResultP;     // get pointer result register
    vmipseGetSPFn       getSP;          // get SP register
    vmipseSetSPFn       setSP;          // set SP register
    vmipseArg32Fn       arg32;          // add Uns32 argument
    vmipseArg64Fn       arg64;          // add Uns64 argument
    vmipseArgAFn        argAddr;        // add Addr argument
    vmipseAllocAFn      allocA;         // allocate space in frame
    Int32               initialSP;      // initial stack pointer
    Uns32               ptrSize;        // PSE pointer size in bytes (4 or 8)
} vmipseAttrs;
