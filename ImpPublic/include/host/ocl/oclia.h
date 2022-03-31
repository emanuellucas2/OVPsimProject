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


#ifndef OCLIA_H
#define OCLIA_H

#define OCL_VERSION "1.1.0"

#include "ocl/ocliaTyperefs.h"
#include "ocl/ocliaTypes.h"

////////////////////////////////////////////////////////////////////////////////
// OCL Functions
////////////////////////////////////////////////////////////////////////////////

/// Evaluate the given expression using the current register state of the
/// processor, writing the result in the buffer.
/// @return Returns true if the expression was successfully evaluated
/// @param attrs  The instruction attribute object
/// @param exp    The expression object
/// @param result Place to put the resulting value

Bool ocliaEvaluate (
    octiaAttrP    attrs,
    octiaAddrExpP exp,
    void*         result
);

/// Return a Boolean indicating whether the instruction should be executed
/// @return Whether instruction should be executed
/// @param attrs The instruction attribute object

Bool ocliaEvaluateInstructionCondition (
    octiaAttrP attrs
);

/// Free the given instruction attribute object
/// @param attrs The instruction attribute object

void ocliaFreeAttrs (
    octiaAttrP attrs
);

/// Get client-specific attributes for the given instruction attribute object
/// @return Client-specific userData
/// @param attrs The instruction attribute object

void * ocliaGetAttrsUserData (
    octiaAttrP attrs
);

/// Get the high address from given fetch record
/// @return The fetched bytes
/// @param fr The fetch record

Uns8* ocliaGetFetchRecordBytes (
    octiaFetchRecordP fr
);

/// Get the high address from given fetch record
/// @return The high address
/// @param fr The fetch record

Addr ocliaGetFetchRecordHigh (
    octiaFetchRecordP fr
);

/// Get the low address from given fetch record
/// @return The low address
/// @param fr The fetch record

Addr ocliaGetFetchRecordLow (
    octiaFetchRecordP fr
);

/// Get client-specific attributes for the given fetch record
/// @return Client-specific userData
/// @param fr The fetch record

void * ocliaGetFetchRecordUserData (
    octiaFetchRecordP fr
);

/// Get the first fetch record for an instruction
/// @return The first fetch record
/// @param attrs The instruction attribute object

octiaFetchRecordP ocliaGetFirstFetchRecord (
    octiaAttrP attrs
);

/// Get the first memory access record for an instruction
/// @return The memory access record
/// @param attrs The instruction attribute object

octiaMemAccessP ocliaGetFirstMemAccess (
    octiaAttrP attrs
);

/// Get the first nextPC record for an instruction
/// @return The first nextPC object
/// @param attrs The instruction attribute object

octiaNextPCP ocliaGetFirstNextPC (
    octiaAttrP attrs
);

/// Get first raw read register range for an instruction (a raw range is a byte
/// range in a processor structure that is accessed but is not matched with a
/// register described as a vmiRegInfoCP in the processor debug interface)
/// @return The fetched bytes
/// @param attrs The instruction attribute object

octiaRawRangeP ocliaGetFirstReadRange (
    octiaAttrP attrs
);

/// Get the first entry in list of registers read by this instruction
/// @return The register list object
/// @param attrs The instruction attribute object

octiaRegListP ocliaGetFirstReadReg (
    octiaAttrP attrs
);

/// Get first raw written register range for an instruction (a raw range is a
/// byte range in a processor structure that is accessed but is not matched with
/// a register described as a vmiRegInfoCP in the processor debug interface)
/// @return The range object
/// @param attrs The instruction attribute object

octiaRawRangeP ocliaGetFirstWrittenRange (
    octiaAttrP attrs
);

/// Get the first entry in list of registers written by this instruction
/// @return The register list object
/// @param attrs The instruction attribute object

octiaRegListP ocliaGetFirstWrittenReg (
    octiaAttrP attrs
);

/// Get the instruction class from the given instruction attribute object
/// @return The instruction class (refer to the description of this type)
/// @param attrs The instruction attribute object

octiaInstructionClass ocliaGetInstructionClass (
    octiaAttrP attrs
);

/// If instruction is conditional, return an implementation-specific condition;
/// otherwise, return 0
/// @return Condition index (or 0 if instruction is unconditional)
/// @param attrs The instruction attribute object

Uns32 ocliaGetInstructionCondition (
    octiaAttrP attrs
);

/// Get the address expression for the memory access
/// @return The memory address expression
/// @param ma The memory access record

octiaAddrExpP ocliaGetMemAccessAddrExp (
    octiaMemAccessP ma
);

/// Get the domain for the memory access
/// @return The memory domain
/// @param ma The memory access record

memDomainP ocliaGetMemAccessDomain (
    octiaMemAccessP ma
);

/// Get the first register in list of dependencies of the memory access. Use
/// vmiiaGetRegListNext and vmiiaGetRegListReg to iterate the list and obtain
/// corresponding vmiRegInfoCP object.
/// @return The first register in the list of dependencies
/// @param ma The memory access record

octiaRegListP ocliaGetMemAccessFirstDepend (
    octiaMemAccessP ma
);

/// Get the bit size of the memory access
/// @return Memory access size in bits
/// @param ma The memory access record

Uns32 ocliaGetMemAccessMemBits (
    octiaMemAccessP ma
);

/// Get the type for a memory access
/// @return The type of memory access
/// @param ma The memory access record

octiaMemAccessType ocliaGetMemAccessType (
    octiaMemAccessP ma
);

/// Get client-specific attributes for the given memory access
/// @return Client-specific userData
/// @param ma The memory access record

void * ocliaGetMemAccessUserData (
    octiaMemAccessP ma
);

/// Get the next fetch record for an instruction
/// @return The first fetch record
/// @param prev The previous fetch record

octiaFetchRecordP ocliaGetNextFetchRecord (
    octiaFetchRecordP prev
);

/// Get the next memory access record
/// @return The next memory access record
/// @param prev The previous memory access record

octiaMemAccessP ocliaGetNextMemAccess (
    octiaMemAccessP prev
);

/// Get the next nextPC record for an instruction
/// @return The next nextPC record
/// @param prev The previous nextPC record

octiaNextPCP ocliaGetNextNextPC (
    octiaNextPCP prev
);

/// Get the address expression for nextPC record
/// @return The address expression object
/// @param entry The nextPC record

octiaAddrExpP ocliaGetNextPCAddrExp (
    octiaNextPCP entry
);

/// Is the nextPC record describing a jump with delay slot?
/// @return True if the nextPC record is a jump with a delay slot
/// @param entry The nextPC record

Bool ocliaGetNextPCDS (
    octiaNextPCP entry
);

/// Get the jump hint for nextPC record
/// @return Jump hint
/// @param entry The nextPC record

octiaJumpHint ocliaGetNextPCHint (
    octiaNextPCP entry
);

/// For constant nextPC records which encode relative branches return the branch
/// displacement from the current PC. For other nextPC record types, return 0
/// @return The relative branch displacement
/// @param entry The nextPC record

Offset ocliaGetNextPCOffset (
    octiaNextPCP entry
);

/// Get client-specific attributes for the given nextPC record
/// @return Client-specific userData
/// @param entry The nextPC record

void * ocliaGetNextPCUserData (
    octiaNextPCP entry
);

/// Get the offset of the high byte of the range from the range object
/// @return The offset
/// @param range The range object

IntPS ocliaGetRangeHigh (
    octiaRawRangeP range
);

/// Get the offset of the low byte of the range from the range object
/// @return The offset
/// @param range The range object

IntPS ocliaGetRangeLow (
    octiaRawRangeP range
);

/// Get the next range from a list of range objects
/// @return The next range object
/// @param prev The previous range object

octiaRawRangeP ocliaGetRangeNext (
    octiaRawRangeP prev
);

/// Get the next entry in a list of registers
/// @return The next register object
/// @param prev The previous register object

octiaRegListP ocliaGetRegListNext (
    octiaRegListP prev
);

/// Get the octiaRegInfoP register for register list entry
/// @return The VMI register info object
/// @param entry The register object

octiaRegInfoP ocliaGetRegListReg (
    octiaRegListP entry
);

/// Get client-specific attributes for the given register list entry
/// @return Client-specific userData
/// @param entry The register object

void * ocliaGetRegListUserData (
    octiaRegListP entry
);

/// Print the given instruction attribute object
/// @param attrs The instruction attribute object

void ocliaPrintAttrs (
    octiaAttrP attrs
);

/// Set client-specific attributes for the given instruction attribute object
/// @param attrs    The instruction attribute object
/// @param userData Client-specific userData

void ocliaSetAttrsUserData (
    octiaAttrP attrs,
    void *     userData
);

/// Set client-specific attributes for the given fetch record
/// @param fr       The fetch record
/// @param userData Client-specific userData

void ocliaSetFetchRecordUserData (
    octiaFetchRecordP fr,
    void *            userData
);

/// Set client-specific attributes for the given memory access
/// @param ma       The memory access record
/// @param userData Client-specific userData

void ocliaSetMemAccessUserData (
    octiaMemAccessP ma,
    void *          userData
);

/// Set client-specific attributes for the given nextPC record
/// @param entry    The nextPC record
/// @param userData Client-specific userData

void ocliaSetNextPCUserData (
    octiaNextPCP entry,
    void *       userData
);

/// Set client-specific attributes for the given register list entry
/// @param entry    The register object
/// @param userData Client-specific userData

void ocliaSetRegListUserData (
    octiaRegListP entry,
    void *        userData
);


#endif /* OCLIA_H */

