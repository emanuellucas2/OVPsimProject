/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */



/*
 * This demonstrates an example subset of required features provided by the foreign ISS model
 * Types, function names and exact prototypes will be different for every encapsulation
 */

typedef void* risc32Handle;

typedef union {
    int ivalue;
    double dvalue;
    long long int lvalue;
    // ... etc
} XT_Value;

#define BADBP -1
typedef int XT_Bphandle;
#define BADWP -1
typedef int XT_Wphandle;

typedef enum {
    XT_False,
    XT_True
} XT_Bool;

typedef unsigned long long XT_Icount;

typedef unsigned int XT_Reg32;

typedef int XT_Addr;

// Type of function used to fetch an instruction
typedef int(*XT_fetchMemFn)(void *userdata, XT_Addr memaddr, XT_Value *memvalue, XT_Bool trueaccess);

// Type of function used to read memory
typedef int(*XT_readMemFn) (void *userdata, XT_Addr memaddr, XT_Value *memvalue, XT_Bool trueaccess);

// Type of function used to write memory
typedef int(*XT_writeMemFn)(void *userdata, XT_Addr memaddr, XT_Value  memvalue, XT_Bool trueaccess);

typedef enum {
    XT_OK,
    XT_WATCHPOINT,
    XT_BREAKPOINT,
    XT_HALT
} XT_StopReason;

typedef enum {
    XT_R0        = 0,
    // ... etc
    XT_REGPC     = 8,
    XT_REGSP     = 9,
    XT_REGSTATUS = 10,
} XT_reg;

//
// Initialize the foreign model and return a handle
//
risc32Handle  XT_constructor(void *userdata);

//
// Free the foreign model
//
void          XT_destructor(risc32Handle handle);

//
// Run for a maximum number of instructions
// 1. this may return early, for reasons which can be inquired
// 2. For performance reasons the model may return early
// Return number of instructions executed
//
XT_Icount     XT_run(risc32Handle handle, XT_Icount maxcount);

//
// Read a processor register given some identifier, return value
//
XT_Value      XT_readReg(risc32Handle handle, XT_reg id);

//
// Write a processor register given some identifier and some value
//
void          XT_writeReg(risc32Handle handle, XT_reg id, XT_Value value);

//
// Allow memory to be modeled by a callback provided by Imperas simulator
// Memory could also be specified by ranges, or there may also be an interface
// to access memory directly using a pointer like DMI
//
void          XT_installReadMemCB (risc32Handle handle, XT_readMemFn  readCB);
void          XT_installFetchMemCB(risc32Handle handle, XT_fetchMemFn fetchCB);
void          XT_installWriteMemCB(risc32Handle handle, XT_writeMemFn writeCB);

//
// return reason for simulation stop
//
XT_StopReason XT_getReason(risc32Handle handle);

//
// Return total number of instructions executed, can be total or for last XT_run
//
XT_Icount     XT_getIcount(risc32Handle handle);

//
// Further functions required for Debug integration
//

//
// Set a breakpoint on an instruction address,
// return breakpoint number or BADBP on failure
//
XT_Bphandle   XT_setBreakpoint(risc32Handle handle, XT_Addr);

//
// Clear a breakpoint given a XT_Bphandle, return status
// 0 = fail
//
XT_Bool       XT_clrBreakpoint(risc32Handle handle, XT_Bphandle);

//
// Set a watchpoint on an instruction address,
// return watchpoint number or BADWP on failure
//
XT_Wphandle   XT_setWatchpoint(risc32Handle handle, XT_Addr lo, XT_Addr hi);

//
// Clear a watchpoint given a XT_Bphandle, return status
//
XT_Bool       XT_clrWatchpoint(risc32Handle handle, XT_Wphandle);

//
// Iterate activated watchpoint (initialize with prev BADWP)
//
XT_Wphandle   XT_nextActivatedWatchpoint(risc32Handle handle, XT_Wphandle prev);

//
// Reset an activated watchpoint given a XT_Bphandle, return status
//
XT_Bool       XT_resetActivatedWatchpoint(risc32Handle handle, XT_Wphandle wphandle);
