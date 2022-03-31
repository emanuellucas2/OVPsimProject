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

/*! \file rvvi.h
 *  \brief RVVI interface, C API header.
**/

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*! \brief RVVI API major version.
 *
 *  \note This should be passed into the rvviCheckVersion() function.
 */
#define RVVI_API_VERSION_MAJOR 0

/*! \brief RVVI API minor version.
 *
 *  \note This should be passed into the rvviCheckVersion() function.
 */
#define RVVI_API_VERSION_MINOR 3

// ---------------------------------------------------------------------------
// RVVI REFERENCE API
// ---------------------------------------------------------------------------

/*! \brief Check the compiled RVVI API version.
 *         Makes sure the linked implementation matches the versions defined in
 *         this header file. This should be called before any other RVVI API
 *         function.
 *
 *  \param major Should be set to RVVI_API_VERSION_MAJOR.
 *  \param minor Should be set to RVVI_API_VERSION_MINOR.
 *
 *  \return returns 1 if versions matches otherwise 0.
**/
extern uint32_t rvviCheckVersion(
    uint32_t major,
    uint32_t minor);

/*! \brief Notify the reference that a CSR is considered volatile.
 *
 *  \param address Address of the CSR register to be considered volatile.
**/
extern void rvviRefSetVolatileCSR(
    uint32_t address);

/*! \brief Notify the reference that a DUT GPR has been written to.
 *
 *  \param hart  The hart that has updated its GPR.
 *  \param index The GPR index within the register file.
 *  \param value The value that has been written.
**/
extern void rvviRefOnSetGPR(
    uint32_t hart,
    uint32_t index,
    uint64_t value);

/*! \brief Notify the reference that a DUT CSR has been written to.
 *
 *  \param hart    The hart that has updated its CSR.
 *  \param address The CSR address (0x000 to 0xfff).
 *  \param value   The value that has been written.
**/
extern void rvviRefOnSetCSR(
    uint32_t hart,
    uint32_t address,
    uint64_t value);

/*! \brief Notify the reference that a DUT instruction has retired.
 *
 *  \param hart  The hart that has retired an instruction.
 *  \param pc    The address of the instruction that has retired.
 *  \param insn  The binary instruction representation.
 *
 * During execution of a rvviDutStep() an instruction has been retired from
 * the DUT pipeline.
 *
 * If an instruction was unable to retire due to an exception rvviRefException()
 * may be issued instead.
 *
 * \sa rvviDutStep()
 * \sa rvviRefOnException()
**/
extern void rvviRefOnRetire(
    uint32_t hart,
    uint64_t pc,
    uint64_t insn);

/*! \brief Notify the reference that the DUT raised an exception.
 *
 *  \param hart The hart that has received the exception.
 *  \param pc   The address of the faulting instruction.
 *
 * During execution of a rvviDutStep() the DUT encountered an exception and
 * the instruction was not retired but rather an exception was raised.
 *
 * \sa rvviDutStep()
 * \sa rvviRefOnRetire()
**/
extern void rvviRefOnException(
    uint32_t hart,
    uint64_t pc);

/*! \brief Notify the reference that the DUT has been written to memory.
 *
 *  \param hart    The hart that issued the data bus write.
 *  \param addr    The address the hart is writing to.
 *  \param value   The value placed on the data bus.
 *  \param bEnMask The byte enable mask provided for this write.
 *
 *  \note Bus writes larger than 64bits should be reported using multiple
 *        calls to this function.
 *  \note bEnMask bit 0 corresponds to addr+0, bEnMask bit 1 corresponds to
 *        addr+1, etc.
**/
extern void rvviRefOnBusWrite(
    uint32_t hart,
    uint64_t addr,
    uint64_t value,
    uint32_t bEnMask);

/*! \brief Lookup a net on the reference model and return its index.
 *
 *  \param hart The hart associated with the net look-up.
 *  \param name The net name to locate.
 *
 *  \return Unique index for this net or -1 if it was not found.
 * 
 *  \note Please consult the model documentation for a list of valid net names.
**/
extern uint64_t rvviRefNetFind(
    uint32_t    hart,
    const char *name);

/*! \brief Propagate a DUT net change to the reference model.
 *
 *  \param hart     The hart that should receive the net write.
 *  \param netIndex The net index returned prior by rvviRefNetFind().
 *  \param value    The new value to set the net state to.
**/
extern void rvviRefOnSetNet(
    uint32_t hart,
    uint64_t netIndex,
    uint64_t value);

/*! \brief Initialize reference.
 *
 *  \param program Path to the ELF file the reference model will execute.  This
 *                 parameter can be NULL.
 *  \param vendor  Vendor string that the reference model will use.
 *  \param variant Variant string that the reference model will use.
 *
 *  \note The reference model will begin execution from the entry point of the
 *        provided ELF file by the program parameter. This can however be
 *        overridden by the rvviRefPCSet() function.
 * 
 *  \return Returns 1 if the reference was initalized successfully else 0.
**/
extern uint32_t rvviRefInit(
    const char *program,
    const char *vendor,
    const char *variant);

/*! \brief Compare all GPR register values between reference and DUT.
 *
 *  \return 0 if there are any mismatches, otherwise 1.
**/
extern uint32_t rvviRefCompareGPR(void);

/*! \brief Compare GPR registers that have been written to between the reference
 *         and DUT. This can be seen as a super set of the rvviRefCompareGPR
 *         function. This comparator will also flag differences in the set of
 *         registers that have been written to.
 *
 *  \param ignoreX0 1 to not compare writes to the x0 register, which may be
 *         treated as a special case.
 *
 *  \return 0 if there are any mismatches, otherwise 1.
**/
extern uint32_t rvviRefCompareGPRWritten(uint32_t ignoreX0);

/*! \brief Compare retired instruction bytes between reference and DUT.
 *
 *  \return 0 if there are any mismatches, otherwise 1.
**/
extern uint32_t rvviRefCompareInsBin(void);

/*! \brief Compare program counter for the retired instructions between DUT and
 *         the the reference model.
 *
 *  \return 0 if there are any mismatches, otherwise 1.
**/
extern uint32_t rvviRefComparePC(void);

/*! \brief Step the reference model until the next event.
 *
 *  \return Returns 1 if the step was successful else 0.
**/
extern uint32_t rvviRefEventStep(void);

/*! \brief Shutdown the reference releasing any used resources.
 *
**/
extern void rvviRefShutdown(void);

/*! \brief Force the reference PC to be particular value.
 *
 *  \param hart The hart to change the PC register of.
 *  \param addr The address to change the PC register to.
**/
extern void rvviRefPCSet(uint32_t hart, uint64_t addr);

/*! \brief Write data to the reference models physical memory space.
 *
 *  \param hart The hart to write from the perspective of.
 *  \param addr The address being written to.
 *  \param data The data byte being written into memory.
 *  \param size Size of the data being written in bytes (max 8).
**/
extern void rvviRefMemoryWrite(uint32_t hart, uint64_t addr, uint64_t data,
                               uint32_t size);

/*! \brief Read data from the reference models physical memory space.
 *
 *  \param hart The hart to read from the perspective of.
 *  \param addr The address being read from.
 *  \param size Size of the data being written in bytes (max 8).
**/
extern uint64_t rvviRefMemoryRead(uint32_t hart, uint64_t addr, uint32_t size);

/*! \brief Return the program counter of a hart in the reference model.
 *
 *  \param hart The hart to retrieve the PC of.
 *
 *  \return The program counter of the specified hart.
**/
extern uint64_t rvviRefPCGet(uint32_t hart);

/*! \brief Read a GPR value from a hart in the reference model.
 *
 *  \param hart The hart to retrieve the GPR of.
 *  \param index Index of the GPR register to read.
 *
 *  \return The GPR register value read from the specified hart.
**/
extern uint64_t rvviRefGPRGet(uint32_t hart, uint32_t index);

/*! \brief Read a CSR value from a hart in the reference model.
 *
 *  \param hart The hart to retrieve the CSR of.
 *  \param addr Address of the CSR register to read.
 *
 *  \return The CSR register value read from the specified hart.
**/
extern uint64_t rvviRefCSRGet(uint32_t hart, uint32_t addr);

/*! \brief Return the binary representation of the previously retired
 *         instruction.
 *
 *  \param hart The hart to retrieve the instruction from.
 *
 *  \return The instruction bytes.
**/
extern uint64_t rvviRefInsBinGet(uint32_t hart);

// ---------------------------------------------------------------------------
// RVVI DEVICE UNDER TEST API
// ---------------------------------------------------------------------------

/*! \brief Notify the testbench that a DUT GPR has been written to.
 *
 *  \param hart  The hart that has updated its GPR.
 *  \param index The GPR index within the register file.
 *  \param value The value that has been written.
 *
 *  \note Should only be called by the DUT during processing of a
 *        `rvviDutStep()` call.
**/
extern void rvviTbOnSetGPR(
    uint32_t hart,
    uint32_t index,
    uint64_t value);

/*! \brief Notify the testbench that a DUT CSR has been written to.
 *
 *  \param hart    The hart that has updated its CSR.
 *  \param address The CSR address.
 *  \param value   The value that has been written.
 *
 *  \note Should only be called by the DUT during processing of a
 *        `rvviDutStep()` call.
**/
extern void rvviTbOnSetCSR(
    uint32_t hart,
    uint32_t address,
    uint64_t value);

/*! \brief Notify the testbench that a DUT instruction has retired.
 *
 *  \param hart  The hart that has retired an instruction.
 *  \param pc    The address of the instruction that has retired.
 *  \param insn  The binary instruction representation.
 *  \param iSize The size in bytes of this instruction.
 *
 *  \note Should only be called by the DUT during processing of a
 *        `rvviDutStep()` call.
**/
extern void rvviTbOnRetire(
    uint32_t hart,
    uint64_t pc,
    uint64_t insn,
    uint32_t iSize);

/*! \brief Notify the testbench that the DUT encountered and exception.
 *
 *  \param hart The hart that has received the exception.
 *  \param pc   The address of the current program counter.
 *
 *  \note Should only be called by the DUT during processing of a
 *        `rvviDutStep()` call.
**/
extern void rvviTbOnException(
    uint32_t hart,
    uint64_t pc);

/*! \brief Initialize DUT.
 *
 *  \param program program Path to the ELF file the reference model will execute.
 *
 *  \return Returns 1 if the DUT was initalized successfully else 0.
 *
 *  \note Should only be called by the DUT during processing of a
 *        `rvviDutStep()` call.
**/
extern uint32_t rvviDutInit(
    const char *program);

/*! \brief Notify the testbench that the DUT has performed a bus write.
 *
 *  \param hart    The hart that issued the bus write.
 *  \param addr    The address the hart is writing to.
 *  \param value   The value placed on the data bus.
 *  \param bEnMask The byte enable mask provided for this write.
 *
 *  \note Bus writes larger than 64bits should be reported using multiple
 *        calls to this function.
 *
 *  \note bEnMask bit 0 corresponds to addr+0, bEnMask bit 1 corresponds to
 *        addr+1, etc.  Values from 0x00 to 0xff represent a 64bit bus write.
 *        Values in the range 0x0 to 0xf represent to a 32bit bus write.
 *
 *  \note There are no alignment restrictions for addr.
 *
 *  \note Should only be called by the DUT during processing of a
 *        `rvviDutStep()` call.
**/
extern void rvviTbOnBusWrite(
    uint32_t hart,
    uint64_t addr,
    uint64_t value,
    uint32_t bEnMask);

/*! \brief Step the DUT until the next event.
 *
 *  \return Return 1 if the step was successful else 0.
 *
 *  \note When handling this call, the DUT may call the `rvviTb ...` suite of
 *        functions to inform the testbench of DUT state change.
**/
extern uint32_t rvviDutEventStep(void);

/*! \brief Shutdown the DUT releasing any used resources.
 *
**/
extern void rvviDutShutdown(void);

#ifdef __cplusplus
}  // extern "C"
#endif
