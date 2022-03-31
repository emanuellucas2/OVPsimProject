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

// hostapi area includes
#include "hostapi/simAddrTypes.h"

// ORD area includes
#include "ord/ordTypes.h"

// VMI area includes
#include "vmi/vmiCommand.h"
#include "vmi/vmiTypes.h"
#include "vmi/vmiTyperefs.h"


////////////////////////////////////////////////////////////////////////////////
// SIMULATOR CONTROL
////////////////////////////////////////////////////////////////////////////////

//
// Explicitly suspend simulation of the passed processor on completion of the
// current simulated instruction to allow other processors in a multiprocessor
// simulation to run. Simulation of the processor will restart when all other
// runnable processors have executed.
//
void vmirtYield(vmiProcessorP processor);

//
// Halt the passed processor on completion of the current simulated instruction.
// The processor will remain halted until restarted by a call to
// vmirtRestartNext or vmirtRestartNow.
//
void vmirtHalt(vmiProcessorP processor);

//
// Interrupt simulation of the passed processor on completion of the current
// simulated instruction and return from simulator invocation, with stop reason
// OP_SR_INTERRUPT (when using the OP interface) or stop reason ICM_SR_INTERRUPT
// (when using the legacy ICM interface)
//
void vmirtInterrupt(vmiProcessorP processor);

//
// Interrupt simulation of the passed processor on completion of the current
// simulated instruction and return from simulator invocation, with stop reason
// OP_SR_YIELD (when using the OP interface) or stop reason ICM_SR_YIELD (when
// using the legacy ICM interface)
//
void vmirtYieldControl(vmiProcessorP processor);

//
// Immediately end simulation of the passed processor. Simulation of other
// processors in a multiprocessor platform will continue.
//
void vmirtExit(vmiProcessorP processor);

//
// Immediately end simulation of any current processor. Simulation of other
// processors in a multiprocessor platform will also end on completion of the
// current time slice.
//
void vmirtFinish(Int32 status);

//
// Interrupt simulation and enter debugger shell (if Imperas debugger attached).
// If Imperas debugger is not attached, return from simulator invocation, with
// stop reason OP_SR_INTERRUPT (when using the OP interface) or stop reason
// ICM_SR_INTERRUPT (when using the legacy ICM interface)
//
void vmirtStop(void);

//
// Indicate that following code should be executed atomically in a
// multiprocessor simulation
//
void vmirtAtomic(void);

//
// Halt the passed processor, aborting any currently-executing instruction. The
// processor will remain halted until restarted by a call to vmirtRestartNext or
// vmirtRestartNow. On restart, re-execute the currently-executing instruction.
//
void vmirtBlock(vmiProcessorP processor);

//
// Terminate execution of the current instruction and restart it
//
void vmirtAbortRepeat(vmiProcessorP processor);

//
// Is the passed processor halted?
//
Bool vmirtIsHalted(vmiProcessorP processor);

//
// Restart a previously-halted processor at the start of the next time slice
//
void vmirtRestartNext(vmiProcessorP processor);

//
// Restart a previously-halted processor immediately
//
void vmirtRestartNow(vmiProcessorP processor);

//
// Turn on instruction tracing after a given number of instructions
//
void vmirtTraceOnAfter(vmiProcessorP processor, Uns64 iDelta);

//
// Turn off instruction tracing after a given number of instructions
//
void vmirtTraceOffAfter(vmiProcessorP processor, Uns64 iDelta);


////////////////////////////////////////////////////////////////////////////////
// INTERRUPTS
////////////////////////////////////////////////////////////////////////////////

//
// Process any pending interrupts. This routine should be used when an interrupt
// needs to be scheduled because of simulated processor state changes (e.g.
// simulated processor interrupts have been enabled by some instruction and
// there are pending interrupts that have now been enabled). This will interrupt
// the processor after the next instruction.
//
void vmirtDoSynchronousInterrupt(vmiProcessorP processor);


////////////////////////////////////////////////////////////////////////////////
// NETS
////////////////////////////////////////////////////////////////////////////////

//
// Find the handle for a processor net given a net port name.
//
Uns32 vmirtGetNetPortHandle(vmiProcessorP processor, const char *netPortName);

//
// Write a value to a processor net port
//
void vmirtWriteNetPort(vmiProcessorP processor, Uns32 handle, Uns64 value);

//
// Read a value from a processor net port
//
Uns64 vmirtReadNetPort(vmiProcessorP processor, Uns32 handle);

//
// Install a notifier, called when a net port changes state.
// This is only for use in an intercept library. To install a notifier in a
// model, use the net port specification methodology described in the VMI Run
// Time Function Reference manual.
//
void vmirtInstallNetCallback(
    vmiProcessorP  processor,
    const char    *netPortName,
    vmiNetChangeFn netChangeCB,
    void          *userData
);


////////////////////////////////////////////////////////////////////////////////
// GENERIC LOAD/STORE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

//
// Read 1 byte value from the passed address
//
Uns8 vmirtRead1ByteDomain(
    memDomainP     domain,
    Addr           simAddress,
    memAccessAttrs attrs
);

//
// Read 2 byte value from the passed address with the passed endianness
//
Uns16 vmirtRead2ByteDomain(
    memDomainP     domain,
    Addr           simAddress,
    memEndian      endian,
    memAccessAttrs attrs
);

//
// Read 4 byte value from the passed address with the passed endianness
//
Uns32 vmirtRead4ByteDomain(
    memDomainP     domain,
    Addr           simAddress,
    memEndian      endian,
    memAccessAttrs attrs
);

//
// Read 8 byte value from the passed address with the passed endianness
//
Uns64 vmirtRead8ByteDomain(
    memDomainP     domain,
    Addr           simAddress,
    memEndian      endian,
    memAccessAttrs attrs
);

//
// Write 1 byte value to the passed address
//
void vmirtWrite1ByteDomain(
    memDomainP     domain,
    Addr           simAddress,
    Uns8           value,
    memAccessAttrs attrs
);

//
// Write 2 byte value to the passed address with the passed endianness
//
void vmirtWrite2ByteDomain(
    memDomainP     domain,
    Addr           simAddress,
    memEndian      endian,
    Uns16          value,
    memAccessAttrs attrs
);

//
// Write 4 byte value to the passed address with the passed endianness
//
void vmirtWrite4ByteDomain(
    memDomainP     domain,
    Addr           simAddress,
    memEndian      endian,
    Uns32          value,
    memAccessAttrs attrs
);

//
// Write 8 byte value to the passed address with the passed endianness
//
void vmirtWrite8ByteDomain(
    memDomainP     domain,
    Addr           simAddress,
    memEndian      endian,
    Uns64          value,
    memAccessAttrs attrs
);

//
// Utility function for N-byte loads from the passed address in the domain.
// If 'cachedRegion' is non-NULL, it should point to a null-initialized memory
// region cache that is used by the simulator to store a hint region to improve
// performance when multiple accesses are made to to the same area of memory.
//
memMapped vmirtReadNByteDomain(
    memDomainP     domain,
    Addr           simAddress,
    void          *buffer,
    Addr           size,
    memRegionPP    cachedRegion,
    memAccessAttrs attrs
);

//
// Utility function for N-byte loads from the passed address in the domain.
// If 'cachedRegion' is non-NULL, it should point to a null-initialized memory
// region cache that is used by the simulator to store a hint region to improve
// performance when multiple accesses are made to to the same area of memory.
// Argument 'VA' is a virtual address that will be passed as the VA argument of
// any callback function of type vmiMemReadFn, vmiMemWriteFn or vmiMemWatchFn
// that is activated as a result of this call.
//
memMapped vmirtReadNByteDomainVA(
    memDomainP     domain,
    Addr           simAddress,
    void          *buffer,
    Addr           size,
    memRegionPP    cachedRegion,
    Addr           VA,
    memAccessAttrs attrs
);

//
// Utility function for N-byte stores to the passed address in the domain.
// If 'cachedRegion' is non-NULL, it should point to a null-initialized memory
// region cache that is used by the simulator to store a hint region to improve
// performance when multiple accesses are made to to the same area of memory.
//
memMapped vmirtWriteNByteDomain(
    memDomainP     domain,
    Addr           simAddress,
    const void    *buffer,
    Addr           size,
    memRegionPP    cachedRegion,
    memAccessAttrs attrs
);

//
// Utility function for N-byte stores to the passed address in the domain.
// If 'cachedRegion' is non-NULL, it should point to a null-initialized memory
// region cache that is used by the simulator to store a hint region to improve
// performance when multiple accesses are made to to the same area of memory.
// Argument 'VA' is a virtual address that will be passed as the VA argument of
// any callback function of type vmiMemReadFn, vmiMemWriteFn or vmiMemWatchFn
// that is activated as a result of this call.
//
memMapped vmirtWriteNByteDomainVA(
    memDomainP     domain,
    Addr           simAddress,
    const void    *buffer,
    Addr           size,
    memRegionPP    cachedRegion,
    Addr           VA,
    memAccessAttrs attrs
);

//
// If the region can support and optimized N-byte write to address simLow,
// return a native pointer to use for that write; otherwise return NULL.
// This can be used in combination with the cached region maintained by
// vmirtReadNByteDomain to optimist reads. 'trueAccess' indicates whether the
// read is a true processor read or whether it is a simulation artifact (for
// example, to model semi-hosting).
//
void *vmirtGetReadNByteSrc(
    memRegionP region,
    Addr       simAddress,
    Addr       size,
    Bool       trueAccess
);

//
// If the region can support and optimized N-byte write to address simLow,
// return a native pointer to use for that write; otherwise return NULL.
// This can be used in combination with the cached region maintained by
// vmirtWriteNByteDomain to optimize writes. 'trueAccess' indicates whether the
// write is a true processor read or whether it is a simulation artifact (for
// example, to model semi-hosting).
//
void *vmirtGetWriteNByteDst(
    memRegionP region,
    Addr       simAddress,
    Addr       size,
    Bool       trueAccess
);

//
// Return a pointer to a null-terminated string extracted from simulated memory
// at the given address. The string remains valid for a limited period and a
// permanent copy should be allocated by the caller if required: see the VMI
// Run Time Function Reference manual for more information.
//
const char *vmirtGetString(memDomainP domain, Addr simAddress);


////////////////////////////////////////////////////////////////////////////////
// MEMORY CALLBACK MANAGEMENT
////////////////////////////////////////////////////////////////////////////////

//
// Add read callback on memory
//
void vmirtAddReadCallback(
    memDomainP    domain,
    vmiProcessorP scope,
    Addr          lowAddr,
    Addr          highAddr,
    vmiMemWatchFn watchCB,
    void         *userData
);

//
// Remove read callback on memory
//
void vmirtRemoveReadCallback(
    memDomainP    domain,
    vmiProcessorP scope,
    Addr          lowAddr,
    Addr          highAddr,
    vmiMemWatchFn watchCB,
    void         *userData
);

//
// Add write callback on memory
//
void vmirtAddWriteCallback(
    memDomainP    domain,
    vmiProcessorP scope,
    Addr          lowAddr,
    Addr          highAddr,
    vmiMemWatchFn watchCB,
    void         *userData
);

//
// Remove write callback on memory
//
void vmirtRemoveWriteCallback(
    memDomainP    domain,
    vmiProcessorP scope,
    Addr          lowAddr,
    Addr          highAddr,
    vmiMemWatchFn watchCB,
    void         *userData
);

//
// Add fetch callback on memory
//
void vmirtAddFetchCallback(
    memDomainP    domain,
    vmiProcessorP scope,
    Addr          lowAddr,
    Addr          highAddr,
    vmiMemWatchFn watchCB,
    void         *userData
);

//
// Remove fetch callback on memory
//
void vmirtRemoveFetchCallback(
    memDomainP    domain,
    vmiProcessorP scope,
    Addr          lowAddr,
    Addr          highAddr,
    vmiMemWatchFn watchCB,
    void         *userData
);


////////////////////////////////////////////////////////////////////////////////
// PROGRAM COUNTER AND CODE DICTIONARY OPERATIONS
////////////////////////////////////////////////////////////////////////////////

//
// Return the current program counter for a processor
//
Addr vmirtGetPC(vmiProcessorP processor);

//
// For processors without delay slots, or for a non-delay-slot instruction
// of a processor with delay slots, return the processor program counter and
// set 'delaySlotOffset' to zero. For a delay slot instruction, return the
// program counter of the preceding jump instruction and set 'delaySlotOffset'
// to the offset in bytes of the delay slot instruction.
//
Addr vmirtGetPCDS(vmiProcessorP processor, Uns8 *delaySlotOffset);

//
// Set the program counter for a processor. If vmirtSetPC is called from a
// function invoked with vmirtCall the new PC becomes effective when vmirtCall'd
// function returns. Any code following the vmirtCall is not executed.
//
void vmirtSetPC(vmiProcessorP processor, Addr newPC);

//
// Set the program counter and delay slot program counter for a processor. The
// instruction at address 'newPC1' will be executed, after which execution will
// continue at 'newPC2'. If 'slotCB' is non-null, it will be executed on
// completion of the instruction at address 'newPC1'. This function is useful
// when implementing processors that allow exceptions to return to delay slot
// instructions.
//
void vmirtSetPCDS(
    vmiProcessorP processor,
    Addr          newPC1,
    Addr          newPC2,
    vmiPostSlotFn slotCB
);

//
// Set the program counter for a processor, as for vmirtSetPC, indicating that
// the control flow update is caused by an exception.
//
void vmirtSetPCException(vmiProcessorP processor, Addr simPC);

//
// Set the program counter for a processor and flush the target address from the
// processor code dictionary. If vmirtSetPC is called from a function invoked
// with vmirtCall the new PC becomes effective when vmirtCall'd function returns.
// Any code following the vmirtCall is not executed.
//
void vmirtSetPCFlushTarget(vmiProcessorP processor, Addr newPC);

//
// Set the program counter for a processor and flush the entire processor
// current code dictionary. If vmirtSetPCFlushDict is called from a function
// invoked with vmirtCall the new PC becomes effective when vmirtCall'd function
// returns. Any code following the vmirtCall is not executed.
//
void vmirtSetPCFlushDict(vmiProcessorP processor, Addr newPC);

//
// Flush any code block containing the passed simulated address from the
// processor code dictionary
//
void vmirtFlushTarget(vmiProcessorP processor, Addr flushPC);

//
// Flush any code block containing the passed simulated address from the
// processor code dictionary for the passed processor mode
//
void vmirtFlushTargetMode(vmiProcessorP processor, Addr flushPC, Uns32 mode);

//
// Flush any code block containing the passed simulated address from the
// processor code dictionary for the passed processor mode, unless the block
// is tagged for preservation.
// If flushIfEqual is True, the block will be flushed if:
//      (blockTag & tagMask) == tagValue
// If flushIfEqual is False, the block will be flushed if:
//      (blockTag & tagMask) != tagValue
// Function vmimtTagBlock is used to mark code blocks with tags.
//
void vmirtFlushTargetModeTagged(
    vmiProcessorP processor,
    Addr          flushPC,
    Uns32         mode,
    vmiBlockTag   tagMask,
    vmiBlockTag   tagValue,
    Bool          flushIfEqual
);

//
// Flush the entire current processor code dictionary
//
void vmirtFlushDict(vmiProcessorP processor);

//
// Flush all processor code dictionaries
//
void vmirtFlushAllDicts(vmiProcessorP processor);

//
// Add fetch callback on processor simulated address
//
Bool vmirtAddPCCallback(
    vmiProcessorP processor,
    Addr          simPC,
    vmiPCWatchFn  watchCB,
    void         *userData
);

//
// Remove fetch callback on processor simulated address
//
Bool vmirtRemovePCCallback(
    vmiProcessorP processor,
    Addr          simPC,
    vmiPCWatchFn  watchCB,
    void         *userData
);

//
// Update the mode/ASID condition for a fetch callback (used to restrict
// callback activation to a particular mode/ASID combination)
//
Bool vmirtUpdatePCCallbackCondition(
    vmiProcessorP processor,
    Addr          simPC,
    vmiPCWatchFn  watchCB,
    void         *userData,
    const char   *condition
);

//
// Return any current mode/ASID condition for a fetch callback
//
const char *vmirtGetPCCallbackCondition(
    vmiProcessorP processor,
    Addr          simPC,
    vmiPCWatchFn  watchCB,
    void         *userData
);


////////////////////////////////////////////////////////////////////////////////
// DICTIONARY AND BLOCK MODES
////////////////////////////////////////////////////////////////////////////////

//
// Return the current processor dictionary index
//
Uns32 vmirtGetMode(vmiProcessorP processor);

//
// Change to the indexed processor dictionary before the next instruction
// starts. The return value indicates whether dictionary switch was successful
// (False implies the processor has no dictionary with the given index)
//
Bool vmirtSetMode(vmiProcessorP processor, Uns32 dictionaryIndex);

//
// Return the current processor block mask
//
Uns32 vmirtGetBlockMask(vmiProcessorP processor);

//
// Change the processor block mask before the next instruction starts - used
// in combination with vmimtValidateBlockMask to facilitate implementation of
// instructions that are enabled by processor mode bits. This variant modifies
// the built-in 32-bit processor block mask.
//
void vmirtSetBlockMask(vmiProcessorP processor, Uns32 blockMask);

//
// Change the processor block mask before the next instruction starts - used
// in combination with vmimtValidateBlockMaskR to facilitate implementation of
// instructions that are enabled by processor mode bits. This variant modifies
// a block mask implemented in a 32-bit processor field.
//
void vmirtSetBlockMask32(
    vmiProcessorP processor,
    Uns32        *blockMaskP,
    Uns32         blockMask
);

//
// Change the processor block mask before the next instruction starts - used
// in combination with vmimtValidateBlockMaskR to facilitate implementation of
// instructions that are enabled by processor mode bits. This variant modifies
// a block mask implemented in a 64-bit processor field.
//
void vmirtSetBlockMask64(
    vmiProcessorP processor,
    Uns64        *blockMaskP,
    Uns64         blockMask
);


////////////////////////////////////////////////////////////////////////////////
// PROCESSOR SCOPE
////////////////////////////////////////////////////////////////////////////////

//
// Return the current processor scope of the processor as a string. The
// processor specifies the mode and current ASID in a processor-specific way.
// See processor support functions vmiosUpdateScope, vmiosGetScope and
// vmiosMatchScope for information about scope usage.
//
const char *vmirtGetProcessorScope(vmiProcessorP processor);


////////////////////////////////////////////////////////////////////////////////
// INSTRUCTION COUNTING AND INTERRUPT AFTER COUNT
////////////////////////////////////////////////////////////////////////////////

//
// Return the processor speed in nominal instructions per second
//
Flt64 vmirtGetProcessorIPS(vmiProcessorP processor);

//
// Return the nominal cycle count for a processor, which is the number of
// instructions executed plus halted cycles and skipped cycles (because of
// clock deration or explicit skipped cycles)
//
Uns64 vmirtGetICount(vmiProcessorP processor);

//
// Return the exact number of processor instructions executed
//
Uns64 vmirtGetExecutedICount(vmiProcessorP processor);

//
// Schedule an interrupt after iDelta clocks using the processor implicit timer
// (callback specified as the icountExceptCB member of the processor vmiIASAttr
// structure).
//
void vmirtSetICountInterrupt(vmiProcessorP processor, Uns64 iDelta);

//
// Clear an instruction count interrupt using the processor implicit timer
//
void vmirtClearICountInterrupt(vmiProcessorP processor);

//
// Create a new processor model timer. Argument 'scale' gives a scale factor by
// which the timer will run slower than the processor MIPS rate. For example:
//     scale = 1:   timer increments once every cycle.
//     scale = 10:  timer increments once every 10 cycles.
// A scale factor of 0 is treated as 1.
//
vmiModelTimerP vmirtCreateModelTimer(
    vmiProcessorP processor,
    vmiICountFn   icountCB,
    Uns32         scale,
    void         *userData
);

//
// Create a new monotonic processor model timer. Monotonic timers behave exactly
// like normal model timers except that in a multiprocessor simulation
// monotonic timer values are guaranteed to present a consistent view of time
// that increases monotonically.
//
vmiModelTimerP vmirtCreateMonotonicModelTimer(
    vmiProcessorP processor,
    vmiICountFn   icountCB,
    Uns32         scale,
    void         *userData
);

//
// Delete a processor model timer
//
void vmirtDeleteModelTimer(vmiModelTimerP modelTimer);

//
// Set a model timer to schedule a callback after 'delta' timer ticks
//
void vmirtSetModelTimer(vmiModelTimerP modelTimer, Uns64 delta);

//
// Clear a model timer
//
void vmirtClearModelTimer(vmiModelTimerP modelTimer);

//
// Is the timer in an enabled state?
//
Bool vmirtIsModelTimerEnabled(vmiModelTimerP modelTimer);

//
// If 'ticks' is True, return the current tick count of the timer; if 'ticks' is
// False, return the current instruction count of the timer.
//
Uns64 vmirtGetModelTimerCurrentCount(vmiModelTimerP modelTimer, Bool ticks);

//
// If 'ticks' is True, return the number of ticks at which the counter is
// scheduled to expire; If 'ticks' is False, return the number of instructions
// at which the counter is scheduled to expire. If the counter is not currently
// enabled, -1 is returned.
//
Uns64 vmirtGetModelTimerExpiryCount(vmiModelTimerP modelTimer, Bool ticks);


////////////////////////////////////////////////////////////////////////////////
// SIMULATION TIME INTERFACE
////////////////////////////////////////////////////////////////////////////////

//
// Return the start time of the current quantum
//
vmiTime vmirtGetQuantumStartTime(vmiProcessorP processor);

//
// Return the end time of the current quantum
//
vmiTime vmirtGetQuantumEndTime(vmiProcessorP processor);

//
// Return the estimated time within the quantum, based on the processor nominal
// MIPS rate. In a multiprocessor simulation, the value returned may not
// increase monotonically.
//
vmiTime vmirtGetLocalTime(vmiProcessorP processor);

//
// Return the estimated time within the quantum, based on the processor nominal
// MIPS rate. In a multiprocessor simulation, the value returned is guaranteed
// to increase monotonically, although perhaps not smoothly.
//
vmiTime vmirtGetMonotonicTime(vmiProcessorP processor);

//
// Create a new processor quantum timer. The timer callback is called whenever
// a new quantum starts.
//
vmiQuantumTimerP vmirtCreateQuantumTimer(
    vmiProcessorP     processor,
    vmiQuantumTimerFn timerCB,
    void             *userData
);

//
// Delete a processor quantum timer
//
void vmirtDeleteQuantumTimer(vmiQuantumTimerP quantumTimer);


////////////////////////////////////////////////////////////////////////////////
// DELAY ESTIMATION
////////////////////////////////////////////////////////////////////////////////

//
// Set the deration factor for the processor, specified as a percentage
// (0.0 - 100.0). The deration factor specifies by how much the processor
// execution rate should be reduced from its nominal rate. For example, the
// default deration percentage (0.0) indicates that the processor should
// execute at full speed; a deration factor of 50.0 indicates that the processor
// should execute at half speed; a deration factor of 100.0 indicates that the
// processor should be stalled and execute no instructions.
//
void vmirtSetDerateFactor(vmiProcessorP processor, Flt64 factor);

//
// Return the processor deration factor
//
Flt64 vmirtGetDerateFactor(vmiProcessorP processor);

//
// Increment the count of skipped cycles for the processor. If the processor is
// currently inactive, this number of nominal cycles is added to the pending
// skipped cycles count for the processor. If the processor is currently active
// (this function is called within an embedded native call, for example) then
// behavior depends on the 'defer' argument, as follows:
//
// defer is True
// -------------
// This number of nominal cycles is added to the pending skipped cycles count
// for the processor.
//
// defer is False
// --------------
// Processor state is immediately updated to reflect the skipped cycles count
// (and any uncommitted pending skipped cycles).
//
// Immediate commit of skipped cycles may increase fidelity but reduces
// simulator performance. Deferred skipped cycles are committed at the start of
// each quantum.
//
// The intended use of this function is in intercept libraries used for timing
// approximation.
//
void vmirtAddSkipCount(vmiProcessorP processor, Uns64 skipCount, Bool defer);

//
// Return the count of skipped cycles for the processor. The type argument
// indicates whether the count should be committed skipped cycles, pending
// skipped cycles, or the total of committed and pending skipped cycles.
//
Uns64 vmirtGetSkipCount(vmiProcessorP processor, vmiSkipType type);


////////////////////////////////////////////////////////////////////////////////
// BASIC MEMORY OPERATIONS
////////////////////////////////////////////////////////////////////////////////

//
// Get the code and data endianness of a processor
//
memEndian vmirtGetProcessorCodeEndian(vmiProcessorP processor);
memEndian vmirtGetProcessorDataEndian(vmiProcessorP processor);

//
// Get code domain and data domain for processor (virtual address space)
//
memDomainP vmirtGetProcessorCodeDomain(vmiProcessorP processor);
memDomainP vmirtGetProcessorDataDomain(vmiProcessorP processor);

//
// Set current code domain and data domain for processor. The domain will remain
// active until reset by these functions or the processor switches mode. To
// permanently change the domain used for each processor mode, use functions
// vmirtSetProcessorCodeDomains and vmirtSetProcessorDataDomains below
//
void vmirtSetProcessorCodeDomain(vmiProcessorP processor, memDomainP domain);
void vmirtSetProcessorDataDomain(vmiProcessorP processor, memDomainP domain);

//
// Get domains associated with the externally-connected data and code busses
//
memDomainP vmirtGetProcessorExternalCodeDomain(vmiProcessorP processor);
memDomainP vmirtGetProcessorExternalDataDomain(vmiProcessorP processor);

//
// Deprecated names for external domain accessors
//
#define vmirtGetProcessorPhysicalCodeDomain vmirtGetProcessorExternalCodeDomain
#define vmirtGetProcessorPhysicalDataDomain vmirtGetProcessorExternalDataDomain

//
// Get domains associated with internal code and data busses (domains
// registered using vmirtSetProcessorInternalCodeDomain and
// vmirtSetProcessorInternalDataDomain when the processor is initialized)
//
memDomainP vmirtGetProcessorInternalCodeDomain(vmiProcessorP processor);
memDomainP vmirtGetProcessorInternalDataDomain(vmiProcessorP processor);

//
// Set internal code domain and internal data domain for processor. These
// functions should be called at most once, in the virtual memory constructor.
// The internal code domains should be associated with an address space after
// any virtual memory remapping has been performed but before any structures
// such as caches. If these functions are not called, the domains associated
// with externally-connected data and code busses are used.
//
void vmirtSetProcessorInternalCodeDomain(
    vmiProcessorP processor,
    memDomainP    domain
);
void vmirtSetProcessorInternalDataDomain(
    vmiProcessorP processor,
    memDomainP    domain
);

//
// Set code and data domains to be used henceforth by the processor for code
// and data accesses in each processor mode. 'domains' should be a pointer to an
// array of domain pointers with one entry for each processor mode (in other
// words, the same number of entries as there are dictionaries in the processor)
//
void vmirtSetProcessorCodeDomains(vmiProcessorP processor, memDomainPP domains);
void vmirtSetProcessorDataDomains(vmiProcessorP processor, memDomainPP domains);

//
// Is the code domain address executable?
//
Bool vmirtIsExecutable(vmiProcessorP processor, Addr simPC);

//
// Override context processor for domain creation. Domains subsequently created
// will be associated with this processor.
//
void vmirtSetCreateDomainContext(vmiProcessorP processor);

//
// Create a new memory domain addressable with addresses of the passed width
//
memDomainP vmirtNewDomain(const char *name, Uns8 addressBits);

//
// Get address width for the domain
//
Uns8 vmirtGetDomainAddressBits(memDomainP domain);

//
// Return access permissions for the passed domain address
//
memPriv vmirtGetDomainPrivileges(memDomainP domain, Addr simAddr);

//
// Return an enumeration describing whether the address range lowAddr:highAddr
// is mapped in the domain - it can be either unmapped (MEM_MAP_NONE), partially
// mapped (MEM_MAP_PART) or fully mapped (MEM_MAP_FULL)
//
memMapped vmirtGetDomainMapped(memDomainP domain, Addr lowAddr, Addr highAddr);

//
// Scan the domain starting from address *lowAddrP up to *highAddrP to find the
// next region of mapped memory. If a region is found, update *lowAddrP and
// *highAddrP with its bounds and return True. If no mapped region is found,
// return False.
//
Bool vmirtGetNextMappedRange(memDomainP domain, Addr *lowAddrP, Addr *highAddrP);

//
// Define an alias of a memory region in the physical domain within the
// virtual domain. The region to be aliased extends from 'physicalLowAddr' to
// 'physicalHighAddr' within the physical domain and should be located at
// 'virtualLowAddr' in the virtual domain. The region is specified to have
// read, write and execute privileges.
//
Bool vmirtAliasMemory(
    memDomainP physicalDomain,
    memDomainP virtualDomain,
    Addr       physicalLowAddr,
    Addr       physicalHighAddr,
    Addr       virtualLowAddr,
    memMRUSetP mruSet
);

//
// Define an alias of a memory region in the physical domain within the
// virtual domain. The region to be aliased extends from 'physicalLowAddr' to
// 'physicalHighAddr' within the physical domain and should be located at
// 'virtualLowAddr' in the virtual domain. The region protection is defined by
// the 'privilege' argument.
//
Bool vmirtAliasMemoryPriv(
    memDomainP physicalDomain,
    memDomainP virtualDomain,
    Addr       physicalLowAddr,
    Addr       physicalHighAddr,
    Addr       virtualLowAddr,
    memPriv    privilege
);

//
// Remove a previously-defined alias mapping of a region in the virtual domain
// (see vmirtAliasMemory and vmirtAliasMemoryVM above).
//
Bool vmirtUnaliasMemory(
    memDomainP virtualDomain,
    Addr       virtualLowAddr,
    Addr       virtualHighAddr
);

//
// Is address simAddr in domain within a region that is an alias defined by
// vmirtAliasMemory or vmirtAliasMemoryVM?
//
Bool vmirtIsAlias(memDomainP domain, Addr simAddr);

//
// Given an address in a virtual domain, set by-ref argument 'physicalDomain' to
// the memory domain to which that address is ultimately resolved and return
// the simulated address in that ultimate physical domain. If the address is not
// mapped, the original address is returned and argument 'physicalDomain' is
// set to NULL. If 'cachedRegion' is non-NULL, it should point to a
// null-initialized memory region cache that is used by the simulator to store a
// hint region to improve performance when multiple accesses are made to to the
// same area of memory.
//
Addr vmirtMapVAToPA(
    memDomainP  virtualDomain,
    Addr        virtualAddr,
    memDomainPP physicalDomain,
    memRegionPP cachedRegion
);

//
// Given an address in 'fromDomain', map that address to 'toDomain' if possible.
// Return value indicates whether mapping succeeded
//
Bool vmirtMapToDomain(
    memDomainP toDomain,
    memDomainP fromDomain,
    Addr      *simAddrP
);

//
// Change memory access privileges on the region from 'lowAddr' to 'highAddr'
// in the domain.
//
Bool vmirtProtectMemory(
    memDomainP    domain,
    Addr          lowAddr,
    Addr          highAddr,
    memPriv       privilege,
    memPrivAction action
);

//
// Map the simulated address range in the domain to use the passed native memory
// for underlying storage
//
Bool vmirtMapNativeMemory(
    memDomainP domain,
    Addr       lowAddr,
    Addr       highAddr,
    void      *memory
);

//
// Map the (previously unmapped) simulated address range in the domain as
// simulated memory
//
Bool vmirtMapMemory(
    memDomainP domain,
    Addr       lowAddr,
    Addr       highAddr,
    memType    type
);

//
// Map the (previously unmapped) simulated address range in the domain to use
// the passed callbacks for read and write
//
Bool vmirtMapCallbacks(
    memDomainP    domain,
    Addr          lowAddr,
    Addr          highAddr,
    vmiMemReadFn  readCB,
    vmiMemWriteFn writeCB,
    void         *userData
);

//
// Modify load/store addresses when loads and stores are applied to the given
// domain so that all bits above the indicated top address bit are either set
// to 0, set to 1, or sign-extended from the next lower bit.
// This function affects the behavior of loads and stores only - to modify the
// behavior of instruction fetches in a similar way, use vmimtSetAddressMask.
//
void vmirtSetLoadStoreMask(
    memDomainP   domain,
    Uns32        topBit,
    memLSMAction zeroAction,
    memLSMAction oneAction
);

//
// Emit debug information describing all regions in the passed domain
//
void vmirtDebugDomain(memDomainP domain);


////////////////////////////////////////////////////////////////////////////////
// ASID-BASED VIRTUAL MEMORY MANAGEMENT
////////////////////////////////////////////////////////////////////////////////

//
// Set processor current ASID - this affects accessibility of pages mapped with
// vmirtAliasMemoryVM
//
void vmirtSetProcessorASID(vmiProcessorP processor, Uns64 ASID);

//
// Get processor current ASID
//
Uns64 vmirtGetProcessorASID(vmiProcessorP processor);

//
// Define an alias of a memory region in the physical domain within the
// virtual domain, specifically for modeling paged virtual memory. Domain,
// address and mruSet set arguments are as for vmirtAliasMemory above.
// 'privilege' specifies the protections that should be applied to the mapped
// page. If 'ASIDMaskOrG' is True, the mapping applies to all processor ASIDs;
// otherwise, if 'ASIDMaskOrG' is False, 'ASID' specifies the particular ASID
// for which the mapping applies; otherwise, 'ASIDMaskOrG' specifies a *mask*
// selecting bits that must match the processor ASID for the page to match (see
// also vmirtUnaliasMemoryVM and vmirtSetProcessorASID)
//
Bool vmirtAliasMemoryVM(
    memDomainP physicalDomain,
    memDomainP virtualDomain,
    Addr       physicalLowAddr,
    Addr       physicalHighAddr,
    Addr       virtualLowAddr,
    memMRUSetP mruSet,
    memPriv    privilege,
    Uns64      ASIDMaskOrG,
    Uns64      ASID
);

//
// Remove a previously-defined alias mapping of a region in the virtual
// domain. If 'ASIDMaskOrG' is True, only a matching global mapping is removed;
// otherwise, if 'ASIDMaskOrG' is False, 'ASID' specifies the particular ASID
// for which the mapping should be removed; otherwise, 'ASIDMaskOrG' specifies a
// *mask* selecting bits that must match the ASID for the mapping to be removed
// (see also vmirtAliasMemoryVM and vmirtSetProcessorASID)
//
Bool vmirtUnaliasMemoryVM(
    memDomainP virtualDomain,
    Addr       virtualLowAddr,
    Addr       virtualHighAddr,
    Uns64      ASIDMaskOrG,
    Uns64      ASID
);

//
// Return an enumeration value indicating whether any address in the range is
// ASID-mapped in the domain with the passed ASID. Return values are:
//    ASID_MAP_NONE:        address not mapped with the passed ASID
//    ASID_MAP_INACTIVE:    address mapped with the passed ASID but not used
//                          since the last ASID switch in the domain
//    ASID_MAP_ACTIVE:      address mapped with the passed ASID and used since
//                          the last ASID switch in the domain
//
memMappedASID vmirtGetDomainMappedASID(
    memDomainP domain,
    Addr       lowAddr,
    Addr       highAddr,
    Uns64      ASID
);

//
// Return a state table object for management of a TLB with the passed number
// of entries. When indexed by the current state, the state table should give
// the next state.
//
const Uns32 *vmirtGetMRUStateTable(Uns32 numEntries, Uns32 entryIndex);

//
// Return the entry index for the passed position in the state. Position 0 will
// return the MRU entry index, and position numEntries-1 will return the LRU
// entry index.
//
Uns8 vmirtGetNthStateIndex(Uns32 numEntries, Uns32 state, Uns32 position);


////////////////////////////////////////////////////////////////////////////////
// FLOATING POINT OPERATION CONTROL
////////////////////////////////////////////////////////////////////////////////

//
// Specify the maximum number of SIMD operations to unroll when translating
// instructions defined with morph-time primitives such as vmimtFUnopSimdRR;
// operations with more than the specified limit will be implemented using
// loops.
//
void vmirtSetSIMDMaxUnroll(vmiProcessorP processor, Uns32 maxUnroll);

//
// This function is called to specify the default floating point unit
// configuration (used for all floating point operations that do not have an
// operation-specific configuration).
//
void vmirtConfigureFPU(vmiProcessorP processor, vmiFPConfigCP config);

//
// Get the processor floating point control word
//
vmiFPControlWord vmirtGetFPControlWord(vmiProcessorP processor);

//
// Set the processor floating point control word
//
void vmirtSetFPControlWord(vmiProcessorP processor, vmiFPControlWord fpcw);

//
// Restore the environment floating point state in an embedded call (required
// if the embedded call needs to execute floating-point instructions)
//
void vmirtRestoreFPState(vmiProcessorP _unused);


////////////////////////////////////////////////////////////////////////////////
// FLOATING POINT OPERATIONS
//
// These functions provide a run-time equivalent to the VMI floating point
// morph-time interface, This uses the SoftFloat IEEE Floating-Point Arithmetic
// Package, Release 3e, by John R. Hauser.
//
// Copyright 2011, 2012, 2013, 2014, 2015, 2016 The Regents of the University of
// California.  All Rights Reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//  1. Redistributions of source code must retain the above copyright notice,
//     this list of conditions, and the following disclaimer.
//
//  2. Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions, and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//  3. Neither the name of the University nor the names of its contributors may
//     be used to endorse or promote products derived from this software without
//     specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS "AS IS", AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE, ARE
// DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
////////////////////////////////////////////////////////////////////////////////

//
// Get floating point convert descriptor
//
vmiFPConvertDescCP vmirtGetFConvertRRDesc(
    vmiProcessorP processor,
    Uns32         num,
    vmiFType      destType,
    vmiFType      srcType,
    vmiFPConfigCP config,
    vmiFPRC       rc,
    Bool          inCompound
);

//
// Get floating point unop descriptor
//
vmiFPUnopDescCP vmirtGetFUnopRRDesc(
    vmiProcessorP processor,
    vmiFType      type,
    Uns32         num,
    vmiFUnop      op,
    vmiFPConfigCP config,
    vmiFPRC       rc,
    Bool          inCompound
);

//
// Get floating point binop descriptor
//
vmiFPBinopDescCP vmirtGetFBinopRRRDesc(
    vmiProcessorP processor,
    vmiFType      type,
    Uns32         num,
    vmiFBinop     op,
    vmiFPConfigCP config,
    vmiFPRC       rc,
    Bool          inCompound
);

//
// Get floating point ternop descriptor
//
vmiFPTernopDescCP vmirtGetFTernopRRRRDesc(
    vmiProcessorP processor,
    vmiFType      type,
    Uns32         num,
    vmiFTernop    op,
    vmiFPConfigCP config,
    vmiFPRC       rc,
    Bool          roundInt,
    Bool          inCompound
);

//
// Get floating point compare descriptor using standard compare codes
//
vmiFPCompareDescCP vmirtGetFCompareRRDesc(
    vmiProcessorP processor,
    Uns8          dBits,
    vmiFType      type,
    Uns32         num,
    Bool          allowQNaN,
    vmiFPConfigCP config,
    Bool          inCompound
);

//
// Get floating point compare descriptor using custom compare codes
//
vmiFPCompareDescCP vmirtGetFCompareRRCDesc(
    vmiProcessorP processor,
    Uns8          dBits,
    vmiFType      type,
    Uns32         num,
    Bool          allowQNaN,
    Uns32         valueUN,
    Uns32         valueEQ,
    Uns32         valueLT,
    Uns32         valueGT,
    vmiFPConfigCP config,
    Bool          inCompound
);

//
// fd[0..num-1] = fa[0..num-1]
//
Bool vmirtFConvertSimdRR(
    vmiProcessorP      processor,
    vmiFPConvertDescCP desc,
    void              *fd,
    const void        *fa,
    Uns8              *flags
);

//
// fd[0..num-1] = <unop> fa[0..num-1]
//
Bool vmirtFUnopSimdRR(
    vmiProcessorP   processor,
    vmiFPUnopDescCP desc,
    void           *fd,
    const void     *fa,
    Uns8           *flags
);

//
// fd[0..num-1] = fa[0..num-1] <binop> fb[0..num-1]
//
Bool vmirtFBinopSimdRRR(
    vmiProcessorP    processor,
    vmiFPBinopDescCP desc,
    void            *fd,
    const void      *fa,
    const void      *fb,
    Uns8            *flags
);

//
// fd[0..num-1] = <ternop>(fa[0..num-1], fb[0..num-1], fc[0..num-1])
//
Bool vmirtFTernopSimdRRRR(
    vmiProcessorP     processor,
    vmiFPTernopDescCP desc,
    void             *fd,
    const void       *fa,
    const void       *fb,
    const void       *fc,
    Uns8             *flags
);

//
// relation[0..num-1] = <compare>(fa[0..num-1], fb[0..num-1])
//
Bool vmirtFCompareSimdRR(
    vmiProcessorP      processor,
    vmiFPCompareDescCP desc,
    void              *rd,
    const void        *fa,
    const void        *fb,
    Uns8              *flags
);


////////////////////////////////////////////////////////////////////////////////
// CONNECTION OBJECTS
////////////////////////////////////////////////////////////////////////////////

//
// Get input connection by name
//
vmiConnInputP vmirtConnGetInput(
    vmiProcessorP processor,
    const char   *connPortName,
    Uns32         width
);

//
// Get output connection by name
//
vmiConnOutputP vmirtConnGetOutput(
    vmiProcessorP processor,
    const char   *connPortName,
    Uns32         width
);

//
// Fill the 'info' structure with information about the input connection
//
void vmirtConnGetInputInfo(vmiConnInputP conn, vmiConnInfoP info);

//
// Fill the 'info' structure with information about the output connection
//
void vmirtConnGetOutputInfo(vmiConnOutputP conn, vmiConnInfoP info);

//
// Perform get from connection object 'conn'. If no data is available, False
// will be returned; otherwise, True is returned and 'value' is filled with the
// bytes read from the connection. If 'peek' is True, data read will not be
// removed from the connection object.
//
Bool vmirtConnGet(vmiConnInputP conn, void *value, Bool peek);

//
// Perform put to connection object 'conn'. The return value indicates
// whether the put was successful.
//
Bool vmirtConnPut(vmiConnOutputP conn, const void *value);

//
// Call 'updateCB' when data is read from 'conn'.
//
void vmirtConnNotifyGet(
    vmiConnOutputP  conn,
    vmiConnUpdateFn updateCB,
    void           *userData
);

//
// Call 'updateCB' when data is written into 'conn'.
//
void vmirtConnNotifyPut(
    vmiConnInputP   conn,
    vmiConnUpdateFn updateCB,
    void           *userData
);


////////////////////////////////////////////////////////////////////////////////
// SIMULATION ENVIRONMENT
////////////////////////////////////////////////////////////////////////////////

//
// Get the currently-executing processor
//
vmiProcessorP vmirtGetCurrentProcessor(void);

//
// Get processor CPU Id
//
Uns32 vmirtCPUId(vmiProcessorP processor);

//
// Return a processor for the passed CPU Id
//
vmiProcessorP vmirtGetProcessorForCPUId(Uns32 cpuId);

//
// Should semi-hosting processors write to stdout?
//
Bool vmirtSuppressStdout(vmiProcessorP processor);

//
// Get processor-specific flags
//
Uns32 vmirtProcessorFlags(vmiProcessorP processor);

//
// Get processor instance name
//
const char *vmirtProcessorName(vmiProcessorP processor);

//
// Set processor instance name
//
void vmirtSetProcessorName(vmiProcessorP processor, const char *name);

//
// Get processor variant name
//
const char *vmirtProcessorVariant(vmiProcessorP processor);

//
// Set processor variant name
//
void vmirtSetProcessorVariant(vmiProcessorP processor, const char *variant);

//
// Get processor type name
//
const char *vmirtProcessorType(vmiProcessorP processor);

//
// Access to processor attribute as a string
//
const char *vmirtProcessorStringAttribute(
    vmiProcessorP processor,
    const char   *name
);

//
// Access to processor attribute as a Bool
//
Bool vmirtProcessorBoolAttribute(
    vmiProcessorP processor,
    const char   *name,
    Bool         *found
);

//
// Access to processor attribute as an Uns32
//
Uns32 vmirtProcessorUns32Attribute(
    vmiProcessorP processor,
    const char   *name,
    Bool         *found
);

//
// Access to processor attribute as an Uns64
//
Uns64 vmirtProcessorUns64Attribute(
    vmiProcessorP processor,
    const char   *name,
    Bool         *found
);

//
// Access to processor attribute as an Flt64
//
Flt64 vmirtProcessorFlt64Attribute(
    vmiProcessorP processor,
    const char   *name,
    Bool         *found
);

//
// Get the platform name
//
const char *vmirtPlatformName(vmiProcessorP processor);

//
// Deprecated names for processor attribute access functions
//
#define vmirtPlatformStringAttribute vmirtProcessorStringAttribute
#define vmirtPlatformUns64Attribute  vmirtProcessorUns64Attribute


////////////////////////////////////////////////////////////////////////////////
// SHARED DATA OBJECTS
////////////////////////////////////////////////////////////////////////////////

//
// Return a handle to a shared data object with global scope for the passed key
// (or NULL if no handle exists for that key)
//
vmiSharedDataHandleP vmirtFindSharedData(
   const char *version,
   const char *key
);

//
// Return a handle to a shared data object with global scope for the passed key,
// creating a new handle if one with that name does not yet exist, and set the
// shared data object value
//
vmiSharedDataHandleP vmirtFindAddSharedData(
    const char *version,
    const char *key,
    void       *value
);

//
// Return a handle to a shared data object with processor scope for the passed
// key (or NULL if no handle exists for that key)
//
vmiSharedDataHandleP vmirtFindProcessorSharedData(
   vmiProcessorP processor,
   const char   *version,
   const char   *key
);

//
// Return a handle to a shared data object with processor scope for the passed
// key, creating a new handle if one with that name does not yet exist, and set
// the shared data object value
//
vmiSharedDataHandleP vmirtFindAddProcessorSharedData(
    vmiProcessorP processor,
    const char   *version,
    const char   *key,
    void         *value
);

//
// Remove a shared data object and all its listeners
//
void vmirtRemoveSharedData(vmiSharedDataHandleP handle);

//
// Set value for a shared data object
//
void vmirtSetSharedDataValue(vmiSharedDataHandleP handle, void *value);

//
// Get value for a shared data object
//
void *vmirtGetSharedDataValue(vmiSharedDataHandleP handle);

//
// Register a shared data listener
//
void vmirtRegisterListener(
    vmiSharedDataHandleP      handle,
    vmirtSharedDataListenerFn listenerCB,
    void                     *object
);

//
// Unregister a shared data listener
//
Bool vmirtUnregisterListener(
    vmiSharedDataHandleP      handle,
    vmirtSharedDataListenerFn listenerCB,
    void                     *object
);

//
// Write to any listeners.
// Return the status from any listeners.
//
Int32 vmirtWriteListeners(
    vmiSharedDataHandleP handle,
    Int32                id,
    void                *userData
);


////////////////////////////////////////////////////////////////////////////////
// SMP PROCESSORS
////////////////////////////////////////////////////////////////////////////////

//
// Return the parent of the passed SMP processor
//
vmiProcessorP vmirtGetSMPParent(vmiProcessorP processor);

//
// Set the parent of the passed SMP processor
//
void vmirtSetSMPParent(vmiProcessorP processor, vmiProcessorP parent);

//
// Return the first child of the passed SMP processor
//
vmiProcessorP vmirtGetSMPChild(vmiProcessorP processor);

//
// Return the previous sibling of the passed SMP processor
//
vmiProcessorP vmirtGetSMPPrevSibling(vmiProcessorP processor);

//
// Return the next sibling of the passed SMP processor
//
vmiProcessorP vmirtGetSMPNextSibling(vmiProcessorP processor);

//
// Return the active sibling of the passed SMP processor
//
vmiProcessorP vmirtGetSMPActiveSibling(vmiProcessorP processor);

//
// Return the SMP type of a processor
//
vmiSMPCpuType vmirtGetSMPCpuType(vmiProcessorP processor);

//
// Return the index number of an SMP processor
//
Uns32 vmirtGetSMPIndex(vmiProcessorP processor);

//
// Set the index number of an SMP processor (affects scheduled order for SMP
// group members)
//
void vmirtSetSMPIndex(vmiProcessorP processor, Uns32 index);

//
// Apply the callback to all children of the processor
//
void vmirtIterAllChildren(
    vmiProcessorP processor,
    vmiSMPIterFn  iterCB,
    void         *userData
);

//
// Apply the callback to all descendants of the processor
//
void vmirtIterAllDescendants(
    vmiProcessorP processor,
    vmiSMPIterFn  iterCB,
    void         *userData
);

//
// Apply the callback to the processor and all its descendants
//
void vmirtIterAllProcessors(
    vmiProcessorP processor,
    vmiSMPIterFn  iterCB,
    void         *userData
);


////////////////////////////////////////////////////////////////////////////////
// TRANSLATION BETWEEN OBJECT FILE ADDRESSES AND NAMES
////////////////////////////////////////////////////////////////////////////////

//
// Look for symbol 'name' in the symbol tables of the objects loaded onto the
// processor. If the symbol is found, return the physical code domain in which
// it is located and set 'simAddr' to the symbol address in that domain.
// Otherwise, return NULL.
//
memDomainP vmirtAddressLookup(
    vmiProcessorP processor,
    const char   *name,
    Addr         *simAddr
);

//
// Find the closest symbol to 'simAddr' in the symbol tables of the objects
// currently visible in the processor code domain. If a symbol is found then
// return the name and set 'offset' to the distance between the symbol and
// simAddr. Otherwise, return NULL.
//
const char *vmirtSymbolLookup(
    vmiProcessorP processor,
    Addr          simAddr,
    Offset       *offset
);


////////////////////////////////////////////////////////////////////////////////
// ADD AND RETRIEVE SYMBOL FILES
////////////////////////////////////////////////////////////////////////////////

//
// Associate the symbols in the passed object file with the processor and any
// children.
//
vmiSymbolFileCP vmirtAddSymbolFile(
    vmiProcessorP processor,
    const char   *filename,
    Addr          address,
    const char   *sections,
    Bool          privateTable
);

//
// Iterate all symbol files visible to the passed processor. Pass NULL to 'prev'
// to get the first symbol file.
//
vmiSymbolFileCP vmirtNextSymbolFile(
    vmiProcessorP   processor,
    vmiSymbolFileCP prev
);

//
// Get symbol file name
//
const char *vmirtGetSymbolFileName(vmiSymbolFileCP symbolFile);


////////////////////////////////////////////////////////////////////////////////
// QUERY SYMBOL INFORMATION IN SYMBOL FILES
////////////////////////////////////////////////////////////////////////////////

//
// Find symbol by name in the symbol files associated with the passed processor.
// Return NULL if no matching symbol is found.
//
vmiSymbolCP vmirtGetSymbolByName(vmiProcessorP processor, const char *name);

//
// Find symbol by name in the passed symbol file.
// Return NULL if no matching symbol is found.
//
vmiSymbolCP vmirtGetSymbolByNameFile(vmiSymbolFileCP symbolFile, const char *name);

//
// Find the closest symbol to 'simAddr' in the symbol files associated with the
// passed processor. Return NULL if no matching symbol is found.
//
vmiSymbolCP vmirtGetSymbolByAddr(vmiProcessorP processor, Addr simAddr);

//
// Find the closest symbol to 'simAddr' in the passed symbol file.
// Return NULL if no matching symbol is found.
//
vmiSymbolCP vmirtGetSymbolByAddrFile(vmiSymbolFileCP symbolFile, Addr simAddr);

//
// Iterate all symbols in the *first* symbol file associated with the processor
// in alphabetical order. Pass NULL to 'prev' to get the first symbol. Related
// functions vmirtGetNextSymbolFile/vmirtNextSymbolByNameFile allow iteration
// of symbols in *all* symbol files associated with the processor.
//
vmiSymbolCP vmirtNextSymbolByName(vmiProcessorP processor, vmiSymbolCP prev);

//
// Iterate all symbols in the *first* symbol file associated with the processor
// in address order. Pass NULL to 'prev' to get the first symbol. Related
// functions vmirtGetNextSymbolFile/vmirtNextSymbolByAddrFile allow iteration
// of symbols in *all* symbol files associated with the processor.
//
vmiSymbolCP vmirtNextSymbolByAddr(vmiProcessorP processor, vmiSymbolCP prev);

//
// Iterate all symbols in the *first* symbol file associated with the processor
// in reverse address order. Pass NULL to 'prev' to get the first symbol.
// Related functions vmirtGetNextSymbolFile/vmirtPrevSymbolByAddrFile allow
// iteration of symbols in *all* symbol files associated with the processor.
//
vmiSymbolCP vmirtPrevSymbolByAddr(vmiProcessorP processor, vmiSymbolCP prev);

//
// Iterate all symbols in the passed symbol file in alphabetical order. Pass
// NULL to 'prev' to get the first symbol.
//
vmiSymbolCP vmirtNextSymbolByNameFile(
    vmiSymbolFileCP symbolFile,
    vmiSymbolCP     prev
);

//
// Iterate all symbols in the passed symbol file in address order. Pass NULL to
// 'prev' to get the first symbol.
//
vmiSymbolCP vmirtNextSymbolByAddrFile(
    vmiSymbolFileCP symbolFile,
    vmiSymbolCP     prev
);

//
// Iterate all symbols in the passed symbol file in reverse address order. Pass
// NULL to 'prev' to get the first symbol.
//
vmiSymbolCP vmirtPrevSymbolByAddrFile(
    vmiSymbolFileCP symbolFile,
    vmiSymbolCP     prev
);

//
// Get symbol name
//
const char *vmirtGetSymbolName(vmiSymbolCP symbol);

//
// Get symbol address
//
Addr vmirtGetSymbolAddr(vmiSymbolCP symbol);

//
// Get symbol load address
//
Addr vmirtGetSymbolLoadAddr(vmiSymbolCP symbol);

//
// Get symbol type
//
ordSymbolType vmirtGetSymbolType(vmiSymbolCP symbol);

//
// Get symbol binding
//
ordSymbolBinding vmirtGetSymbolBinding(vmiSymbolCP symbol);

//
// Get symbol size
//
Addr vmirtGetSymbolSize(vmiSymbolCP symbol);


////////////////////////////////////////////////////////////////////////////////
// QUERY LINE NUMBER INFORMATION IN SYMBOL FILES
////////////////////////////////////////////////////////////////////////////////

//
// Look up file/line info by address
//
vmiFileLineCP vmirtGetFLByAddr(vmiProcessorP processor, Addr simAddr);

//
// Look up file/line info by address in the given object file
//
vmiFileLineCP vmirtGetFLByAddrFile(vmiSymbolFileCP symbolFile, Addr simAddr);

//
// Iterate all file/line entries in the *first* symbol file associated with the
// processor in address order. Pass NULL to 'prev' to get the first file/line.
// Related functions vmirtGetNextSymbolFile/vmirtNextFLByAddrFile allow
// iteration of file/line entries in *all* symbol files associated with the
// processor.
//
vmiFileLineCP vmirtNextFLByAddr(vmiProcessorP processor, vmiFileLineCP prev);

//
// Iterate all file/line entries in the *first* symbol file associated with the
// processor in reverse address order. Pass NULL to 'prev' to get the first
// file/line. Related functions vmirtGetNextSymbolFile/vmirtPrevFLByAddrFile
// allow iteration of file/line entries in *all* symbol files associated with
// the processor.
//
vmiFileLineCP vmirtPrevFLByAddr(vmiProcessorP processor, vmiFileLineCP prev);

//
// Iterate all file/line entries in the passed symbol file in address order.
// Pass NULL to 'prev' to get the first file/line.
//
vmiFileLineCP vmirtNextFLByAddrFile(
    vmiSymbolFileCP symbolFile,
    vmiFileLineCP   prev
);

//
// Iterate all file/line entries in the passed symbol file in reverse address
// order. Pass NULL to 'prev' to get the first file/line.
//
vmiFileLineCP vmirtPrevFLByAddrFile(
    vmiSymbolFileCP symbolFile,
    vmiFileLineCP   prev
);

//
// Get file/line file name
//
const char *vmirtGetFLFileName(vmiFileLineCP fl);

//
// Get file/line line number
//
Uns32 vmirtGetFLLineNumber(vmiFileLineCP fl);

//
// Get file/line address
//
Addr vmirtGetFLAddr(vmiFileLineCP fl);


////////////////////////////////////////////////////////////////////////////////
// ADDRESS RANGE HASH UTILITIES
////////////////////////////////////////////////////////////////////////////////

//
// Allocate an address range hash table
//
void vmirtNewRangeTable(vmiRangeTablePP table);

//
// Free a previously-allocated address range hash table
//
void vmirtFreeRangeTable(vmiRangeTablePP table);

//
// Create a new entry with the passed address range in the address range table.
// Multiple entries with the same or overlapping address ranges are allowed.
//
vmiRangeEntryP vmirtInsertRangeEntry(
    vmiRangeTablePP table,
    Addr            low,
    Addr            high,
    Uns64           userData
);

//
// Remove the passed entry from the address range table and delete it.
//
void vmirtRemoveRangeEntry(vmiRangeTablePP table, vmiRangeEntryP entry);

//
// Find the first entry in table that overlaps the range low:high. This function
// initiates a delete-safe iterator in which subsequent entries can be found
// using vmirtGetNextRangeEntry.
//
vmiRangeEntryP vmirtGetFirstRangeEntry(
    vmiRangeTablePP table,
    Addr            low,
    Addr            high
);

//
// Find the next entry in table that overlaps the range low:high.
//
vmiRangeEntryP vmirtGetNextRangeEntry(
    vmiRangeTablePP table,
    Addr            low,
    Addr            high
);

//
// Return the low address of the range entry
//
Addr vmirtGetRangeEntryLow(vmiRangeEntryP entry);

//
// Return the high address of the range entry
//
Addr vmirtGetRangeEntryHigh(vmiRangeEntryP entry);

//
// Return the userData of the range entry
//
Uns64 vmirtGetRangeEntryUserData(vmiRangeEntryP entry);

//
// Set the userData of the range entry
//
void vmirtSetRangeEntryUserData(vmiRangeEntryP entry, Uns64 userData);


////////////////////////////////////////////////////////////////////////////////
// LICENSING SUPPORT
////////////////////////////////////////////////////////////////////////////////

//
// Check out the model's license
// May only be called during model construction
//
Bool vmirtGetLicense(const char *name);

//
// Get any error message associated with the license checkout.
// May only be called during model construction
//
const char *vmirtGetLicenseErrString(const char *name);


////////////////////////////////////////////////////////////////////////////////
// SHARED OBJECT / DYNAMIC LINKED LIBRARY LOADING
////////////////////////////////////////////////////////////////////////////////

//
// Open a shared object and return a handle to it
//
vmiDLHandleP vmirtDLOpen(const char *fileName);

//
// Return any error message resulting from a failed attempt to open a shared
// object
//
const char *vmirtDLError(void);

//
// Return the address associated with a symbol in the loaded shared object
//
void *vmirtDLSymbol(vmiDLHandleP handle, const char *symbol);

//
// Close a previously-loaded shared object
//
Int32 vmirtDLClose(vmiDLHandleP handle);


////////////////////////////////////////////////////////////////////////////////
// COMMAND INTERPRETER INTEGRATION
////////////////////////////////////////////////////////////////////////////////

//
// Add a command for the passed processor. If the defined command
// is used, commandCB will be called with any supplied arguments.
//
vmiCommandP vmirtAddCommand(
    vmiProcessorP   processor,
    const char     *name,
    const char     *help,
    vmirtCommandFn  commandCB,
    vmiCommandAttrs attrs
);

//
// Add a command with command parser for the passed processor.
// command arguments will be parsed according to arguments specified by
// vmirtAddArg (see below)
// In addition to the arguments specified using vmirtAddArg, the flag -get is
// recognized.
// If attrs contains the bit VMI_CT_HELP, then -help is recognized.
// If the defined command is used, commandCB will be called with the arguments
// parsed into an argValue array. The array does not persist after the call.
//
vmiCommandP vmirtAddCommandParse(
    vmiProcessorP       processor,
    const char         *name,
    const char         *help,
    vmirtCommandParseFn commandCB,
    vmiCommandAttrs     attrs
);

//
// Add an argument to a command parser. If the command is called with an
// argument matching the given name, it will be parsed.
// If ptr is non-null, its value will be updated by the value parsed.
// Note that if ptr is pointing to a string, the old string will be free()'d
// before a new string is malloc()'d
//
vmiArgP vmirtAddArg(
    vmiCommandP     command,   // as returned by vmirtAddCommandParse
    const char     *name,      // argument name
    const char     *help,      // brief description
    vmiArgType      type,      // data type, validated before being accepted.
    vmiArgAttrs     attrs,     // used by the Imperas menu system - under development
    Bool            mandatory, // If true, this argument must be provided
    void           *ptr        // points to storage for the value
);

//
// Add an value name to an enumerated type argument to a command parser.
//
void vmirtAddArgEnum(
    vmiArgP         argument, // the argument returned by vmirtAddArg
    const char     *name,     // name of enumeration
    const char     *help,     // brief description
    Uns32           value     // value associated with the name
);

//
// Find an argument value in the argument value array passed to
// the vmirtCommandParseFn()
//
vmiArgValueP vmirtFindArgValue(Uns32 argc, vmiArgValue argv[], const char *name);


////////////////////////////////////////////////////////////////////////////////
// ENCAPSULATED PROCESSOR MODEL INTERCEPTED FUNCTION SUPPORT
////////////////////////////////////////////////////////////////////////////////

//
// Call the intercepted function at address 'thisPC', applying arguments from
// the 'args' list
//
Uns32 vmirtEncapIntercept(
    vmiProcessorP processor,
    Addr          thisPC,
    Uns32        *args
);


////////////////////////////////////////////////////////////////////////////////
// REGISTER ACCESS
////////////////////////////////////////////////////////////////////////////////

//
// Return descriptor for the named register group.
//
vmiRegGroupCP vmirtGetRegGroupByName(
    vmiProcessorP processor,
    const char   *name
);

//
// Return the next processor register group descriptor, given the previous
// descriptor. Pass NULL to get the first register group descriptor.
//
vmiRegGroupCP vmirtGetNextRegGroup(
    vmiProcessorP processor,
    vmiRegGroupCP previous
);

//
// Return descriptor for the named register.
//
vmiRegInfoCP vmirtGetRegByName(
    vmiProcessorP processor,
    const char   *name
);

//
// Return the next processor register descriptor, given the previous descriptor.
// Pass NULL to get the first register descriptor.
//
vmiRegInfoCP vmirtGetNextReg(
    vmiProcessorP processor,
    vmiRegInfoCP  previous
);

//
// Return the next processor register descriptor in the given group, given the
// previous descriptor. Pass NULL for argument 'previous' to get the first
// register descriptor in the group.
//
vmiRegInfoCP vmirtGetNextRegInGroup(
    vmiProcessorP processor,
    vmiRegGroupCP group,
    vmiRegInfoCP  previous
);

//
// Read register value into buffer.
//
Bool vmirtRegRead(
    vmiProcessorP processor,
    vmiRegInfoCP  regDesc,
    void         *result
);

//
// Write register value from buffer.
//
Bool vmirtRegWrite(
    vmiProcessorP processor,
    vmiRegInfoCP  regDesc,
    const void   *value
);


////////////////////////////////////////////////////////////////////////////////
// BUS PORT ACCESS
////////////////////////////////////////////////////////////////////////////////

//
// Return the named bus port.
//
vmiBusPortP vmirtGetBusPortByName(
    vmiProcessorP processor,
    const char   *name
);

//
// Return the next processor bus port, given the previous bus port. Pass NULL
// to get the first bus port.
//
vmiBusPortP vmirtGetNextBusPort(
    vmiProcessorP processor,
    vmiBusPortP   previous
);


////////////////////////////////////////////////////////////////////////////////
// NET PORT ACCESS
////////////////////////////////////////////////////////////////////////////////

//
// Return the named net port.
//
vmiNetPortP vmirtGetNetPortByName(
    vmiProcessorP processor,
    const char   *name
);

//
// Return the next processor net port, given the previous net port. Pass NULL
// to get the first net port.
//
vmiNetPortP vmirtGetNextNetPort(
    vmiProcessorP processor,
    vmiNetPortP   previous
);


////////////////////////////////////////////////////////////////////////////////
// FIFO PORT ACCESS
////////////////////////////////////////////////////////////////////////////////

//
// Return the named fifo port.
//
vmiFifoPortP vmirtGetFifoPortByName(
    vmiProcessorP processor,
    const char   *name
);

//
// Return the next processor fifo port, given the previous fifo port. Pass NULL
// to get the first fifo port.
//
vmiFifoPortP vmirtGetNextFifoPort(
    vmiProcessorP processor,
    vmiFifoPortP  previous
);


////////////////////////////////////////////////////////////////////////////////
// MODE ACCESS
////////////////////////////////////////////////////////////////////////////////

//
// Return the processor current mode descriptor.
//
vmiModeInfoCP vmirtGetCurrentMode(vmiProcessorP processor);

//
// Return the next processor mode descriptor, given the previous descriptor.
// Pass NULL to get the first mode descriptor.
//
vmiModeInfoCP vmirtGetNextMode(
    vmiProcessorP processor,
    vmiModeInfoCP previous
);


////////////////////////////////////////////////////////////////////////////////
// EXCEPTION ACCESS
////////////////////////////////////////////////////////////////////////////////

//
// Return the processor current mode descriptor.
//
vmiExceptionInfoCP vmirtGetCurrentException(vmiProcessorP processor);

//
// Return the next processor mode descriptor, given the previous descriptor.
// Pass NULL to get the first mode descriptor.
//
vmiExceptionInfoCP vmirtGetNextException(
    vmiProcessorP      processor,
    vmiExceptionInfoCP previous
);


////////////////////////////////////////////////////////////////////////////////
// GDB DEBUGGER ACCESS
////////////////////////////////////////////////////////////////////////////////

//
// Evaluate an expression using a GDB attached to the given processor.
// The returned result is only valid until this function is next called.
// NULL is returned if an error occurs while evaluating the expression.
//
const char *vmirtEvaluateGDBExpression(
    vmiProcessorP processor,
    const char   *expression,
    Bool          usePhysicalDomain,
    Bool          quiet
);

//
// Evaluate an expression used in the gdb 'break' command.
// Returns true if successful.
// Sets the address, source file and source line if possible.
//
Bool vmirtEvaluateCodeLocation(
    vmiProcessorP processor,
    const char   *expression,
    Addr         *address,
    const char  **sourceFile,
    const char  **fullFile,
    Uns32        *sourceLine
);

//
// Return disassembled instruction at the simulated address
//
const char *vmirtDisassemble(
    vmiProcessorP  processor,
    Addr           simPC,
    vmiDisassAttrs attrs
);

//
// Return instruction size at the simulated address, in bytes
//
Uns32 vmirtInstructionBytes(vmiProcessorP processor, Addr simPC);


////////////////////////////////////////////////////////////////////////////////
// REGISTER WATCH FUNCTION INTERFACE
////////////////////////////////////////////////////////////////////////////////

//
// Add a register watch function for the passed processor register. The watch
// function 'watchCB' is activated on completion of any instruction in which
// the register value changes
//
vmiWatchHandleP vmirtAddRegisterWatchCallback(
    vmiProcessorP processor,
    vmiRegInfoCP  reg,
    vmiRegValueFn valueCB,
    void         *userData
);

//
// Delete a register watch function
//
void vmirtDeleteRegisterWatchCallback(vmiWatchHandleP handle);


////////////////////////////////////////////////////////////////////////////////
// SAVE / RESTORE SUPPORT ROUTINES
////////////////////////////////////////////////////////////////////////////////

//
// Macros for save/restore of processor registers
//
#define VMIRT_SAVE_REG(_CXT, _NAME, _REG) \
    vmirtSave(_CXT, _NAME, _REG, sizeof(*(_REG)))
#define VMIRT_RESTORE_REG(_CXT, _NAME, _REG) \
    vmirtRestore(_CXT, _NAME, _REG, sizeof(*(_REG)))

//
// Macros for save/restore of processor fields
//
#define VMIRT_SAVE_FIELD(_CXT, _PROCESSOR, _FIELD) \
    VMIRT_SAVE_REG(_CXT, #_FIELD, &(_PROCESSOR)->_FIELD)
#define VMIRT_RESTORE_FIELD(_CXT, _PROCESSOR, _FIELD) \
    VMIRT_RESTORE_REG(_CXT, #_FIELD, &(_PROCESSOR)->_FIELD)

//
// Save a named value using the active save context
//
vmiSaveRestoreStatus vmirtSave(
    vmiSaveContextP cxt,
    const char     *name,
    const void     *value,
    Uns32           bytes
);

//
// Restore a named value using the active restore context
//
vmiSaveRestoreStatus vmirtRestore(
    vmiRestoreContextP cxt,
    const char        *name,
    void              *value,
    Uns32              bytes
);

//
// Save a list element using the active save context. Pass NULL to indicate the
// last element of the list
//
vmiSaveRestoreStatus vmirtSaveElement(
    vmiSaveContextP cxt,
    const char     *elementName,
    const char     *endName,
    const void     *value,
    Uns32           bytes
);

//
// Restore a list element using the active restore context. The return value
// is SRS_OK if an element is successfully restored, or SRS_END_LIST if the
// list terminator has been read.
//
vmiSaveRestoreStatus vmirtRestoreElement(
    vmiRestoreContextP cxt,
    const char        *elementName,
    const char        *endName,
    void              *value,
    Uns32              bytes
);

//
// Save a named timer using the active save context
//
vmiSaveRestoreStatus vmirtSaveModelTimer(
    vmiSaveContextP cxt,
    const char     *name,
    vmiModelTimerP  modelTimer
);

//
// Restore a named timer using the active restore context
//
vmiSaveRestoreStatus vmirtRestoreModelTimer(
    vmiRestoreContextP cxt,
    const char        *name,
    vmiModelTimerP     modelTimer
);

//
// Save a memory domain using the active save context
//
vmiSaveRestoreStatus vmirtSaveDomain(
    vmiSaveContextP cxt,
    memDomainP      domain
);

//
// Restore a memory domain using the active restore context
//
vmiSaveRestoreStatus vmirtRestoreDomain(
    vmiRestoreContextP cxt,
    memDomainP         domain
);

//
// Get any active processor post-delay-slot callback function
//
vmiPostSlotFn vmirtGetPostSlotCB(vmiProcessorP processor);

//
// Set the processor post-delay-slot callback function
//
void vmirtSetPostSlotCB(vmiProcessorP processor, vmiPostSlotFn slotCB);


////////////////////////////////////////////////////////////////////////////////
// VIEW PROVIDER INTERFACE
////////////////////////////////////////////////////////////////////////////////

//
// Return the base view object for a processor
//
vmiViewObjectP vmirtGetProcessorViewObject(vmiProcessorP processor);

//
// Set userData associated with the passed view object
//
void vmirtSetViewObjectUserData(vmiViewObjectP object, void *userData);

//
// Get userData associated with the passed view object
//
void *vmirtGetViewObjectUserData(vmiViewObjectP object);

//
// Create a view object
//
vmiViewObjectP vmirtAddViewObject(
    vmiViewObjectP parent,
    const char    *name,
    const char    *description
);

//
// Set constant value for view object (value copied at time of call)
//
void vmirtSetViewObjectConstValue(
    vmiViewObjectP   object,
    vmiViewValueType type,
    void            *pValue
);

//
// Set value pointer for view object (pointer de-referenced each time value is viewed).
// Use this to associate a view object with a C variable in the model such that the variable
// is automatically read when the view object is evaluated.
//
void vmirtSetViewObjectRefValue(
    vmiViewObjectP   object,
    vmiViewValueType type,
    void            *pValue
);

//
// Set value callback for view object
//
void vmirtSetViewObjectValueCallback(
    vmiViewObjectP object,
    vmiViewValueFn valueCB,
    void          *userData
);

//
// Add an action to a view object
//
void vmirtAddViewAction(
    vmiViewObjectP  object,
    const char     *name,
    const char     *description,
    vmiViewActionFn actionCB,
    void           *userData
);

//
// Add an event to a view object
//
vmiViewEventP vmirtAddViewEvent(
    vmiViewObjectP object,
    const char    *name,
    const char    *description
);

//
// Get next view event from a view object
//
vmiViewEventP vmirtNextViewEvent(vmiViewObjectP object, vmiViewEventP old);

//
// Trigger a view event
//
void vmirtTriggerViewEvent(vmiViewEventP event);

//
// Delete a view object
//
void vmirtDeleteViewObject(vmiViewObjectP object);


////////////////////////////////////////////////////////////////////////////////
// INSTRUCTION ATTRIBUTE QUERY SUPPORT
////////////////////////////////////////////////////////////////////////////////

//
// This function is used within the scope of the vmiReg-to-vmiRegInfoCP
// correspondence callback in (regImplCB field in the processor attributes
// structure) to specify that the processor raw register 'r' of size 'bits'
// implements all or part of the register described by 'regDesc'. The function
// is required only for use with the instruction attribute query API.
//
void vmirtRegImplRaw(
    vmiProcessorP processor,
    vmiRegInfoCP  regDesc,
    vmiReg        r,
    Uns32         bits
);

//
// Return the result of evaluating a model-specific condition code (returned
// by ocliaGetInstructionCondition) in the current processor state
//
Bool vmirtEvaluateCondition(vmiProcessorP processor, Uns32 condition);


////////////////////////////////////////////////////////////////////////////////
// REGISTRATION OF BRANCH REASON NOTIFIERS
////////////////////////////////////////////////////////////////////////////////

//
// Register a branch reason notifier function
//
void vmirtRegisterBranchNotifier(
    vmiProcessorP     processor,
    vmiBranchReasonFn notifier,
    void             *userData
);

//
// Unregister a branch reason notifier function
//
void vmirtUnregisterBranchNotifier(
    vmiProcessorP     processor,
    vmiBranchReasonFn notifier,
    void             *userData
);

