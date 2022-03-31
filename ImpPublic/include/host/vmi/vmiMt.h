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
#include "vmi/vmiTypes.h"
#include "vmi/vmiTyperefs.h"


////////////////////////////////////////////////////////////////////////////////
// INTEGER OPCODES
////////////////////////////////////////////////////////////////////////////////

//
// rd = c
//
void vmimtMoveRC(
    Uns32  bits,
    vmiReg rd,
    Uns64  c
);

//
// rd = simPC
//
void vmimtMoveRSimPC(
    Uns32  bits,
    vmiReg rd
);

//
// rd = ra
//
void vmimtMoveRR(
    Uns32  bits,
    vmiReg rd,
    vmiReg ra
);

//
// rd<destBits> = ra<srcBits>
//
void vmimtMoveExtendRR(
    Uns32  destBits,
    vmiReg rd,
    Uns32  srcBits,
    vmiReg ra,
    Bool   signExtend
);

//
// rd = (flag==select1) ? ra : rb
//
void vmimtCondMoveRRR(
    Uns32  bits,
    vmiReg flag,
    Bool   select1,
    vmiReg rd,
    vmiReg ra,
    vmiReg rb
);

//
// rd = (flag==select1) ? ra : c
//
void vmimtCondMoveRRC(
    Uns32  bits,
    vmiReg flag,
    Bool   select1,
    vmiReg rd,
    vmiReg ra,
    Uns64  c
);

//
// rd = (flag==select1) ? c : rb
//
void vmimtCondMoveRCR(
    Uns32  bits,
    vmiReg flag,
    Bool   select1,
    vmiReg rd,
    Uns64  c,
    vmiReg rb
);

//
// rd = (flag==select1) ? c1 : c2
//
void vmimtCondMoveRCC(
    Uns32  bits,
    vmiReg flag,
    Bool   select1,
    vmiReg rd,
    Uns64  c1,
    Uns64  c2
);

//
// rd = <unop> rd
//
void vmimtUnopR(
    Uns32      bits,
    vmiUnop    op,
    vmiReg     rd,
    vmiFlagsCP flags
);

//
// rd = <unop> ra
//
void vmimtUnopRR(
    Uns32      bits,
    vmiUnop    op,
    vmiReg     rd,
    vmiReg     ra,
    vmiFlagsCP flags
);

//
// rd = <unop> c
//
void vmimtUnopRC(
    Uns32      bits,
    vmiUnop    op,
    vmiReg     rd,
    Uns64      c,
    vmiFlagsCP flags
);

//
// rd = rd <binop> ra
//
void vmimtBinopRR(
    Uns32      bits,
    vmiBinop   op,
    vmiReg     rd,
    vmiReg     ra,
    vmiFlagsCP flags
);

//
// rd = ra <binop> rb
//
void vmimtBinopRRR(
    Uns32      bits,
    vmiBinop   op,
    vmiReg     rd,
    vmiReg     ra,
    vmiReg     rb,
    vmiFlagsCP flags
);

//
// rd = rd <binop> c
//
void vmimtBinopRC(
    Uns32      bits,
    vmiBinop   op,
    vmiReg     rd,
    Uns64      c,
    vmiFlagsCP flags
);

//
// rd = c1 <binop> c2
//
void vmimtBinopRCC(
    Uns32      bits,
    vmiBinop   op,
    vmiReg     rd,
    Uns64      c1,
    Uns64      c2,
    vmiFlagsCP flags
);

//
// rd = ra <binop> c
//
void vmimtBinopRRC(
    Uns32      bits,
    vmiBinop   op,
    vmiReg     rd,
    vmiReg     ra,
    Uns64      c,
    vmiFlagsCP flags
);

//
// rd = c <binop> rb
//
void vmimtBinopRCR(
    Uns32      bits,
    vmiBinop   op,
    vmiReg     rd,
    Uns64      c,
    vmiReg     rb,
    vmiFlagsCP flags
);

//
// rdh:rdl = ra*rb
//
// This special form of multiply is used to produce a double-width result
// in rdh:rdl. If a single-width result is required, use vmimtBinopRRR.
//
// Notes:
// 1. 'op' must be vmi_MUL, vmi_IMUL, vmi_IMULSU, vmi_IMULUS or vmi_PMUL
// 2. 'rdh' and/or 'rdl' may be VMI_NOREG (to discard that part of the result)
//
void vmimtMulopRRR(
    Uns32      bits,
    vmiBinop   op,
    vmiReg     rdh,
    vmiReg     rdl,
    vmiReg     ra,
    vmiReg     rb,
    vmiFlagsCP flags
);

//
// rdd = rah:ral/rb; rdr = rah:ral%rb
//
// This special form of divide is used to divide a double-width dividend
// preserving result or remainder or both. If a single-width result without
// remainder is required, use vmimtBinopRRR.
//
// Notes:
// 1. 'op' must be vmi_DIV or vmi_IDIV
// 2. 'rdd' and/or 'rdr' may be VMI_NOREG (to discard that part of the result)
// 3. 'rah' may be VMI_NOREG - in this case, it defaults to 0 for vmi_DIV and
//    the sign extension of 'ral' for vmi_IDIV
//
void vmimtDivopRRR(
    Uns32      bits,
    vmiBinop   op,
    vmiReg     rdd,
    vmiReg     rdr,
    vmiReg     rah,
    vmiReg     ral,
    vmiReg     rb,
    vmiFlagsCP flags
);

//
// compare(ra, rb); flag = <cond>
//
void vmimtCompareRR(
    Uns32        bits,
    vmiCondition cond,
    vmiReg       ra,
    vmiReg       rb,
    vmiReg       flag
);

//
// compare(ra, c); flag = <cond>
//
void vmimtCompareRC(
    Uns32        bits,
    vmiCondition cond,
    vmiReg       ra,
    Uns64        c,
    vmiReg       flag
);

//
// compare(c, rb); flag = <cond>
//
void vmimtCompareCR(
    Uns32        bits,
    vmiCondition cond,
    Uns64        c,
    vmiReg       rb,
    vmiReg       flag
);

//
// test(ra, rb); flag = <cond>
//
void vmimtTestRR(
    Uns32        bits,
    vmiCondition cond,
    vmiReg       ra,
    vmiReg       rb,
    vmiReg       flag
);

//
// test(ra, c); flag = <cond>
//
void vmimtTestRC(
    Uns32        bits,
    vmiCondition cond,
    vmiReg       ra,
    Uns64        c,
    vmiReg       flag
);

//
// test(c, rb); flag = <cond>
//
void vmimtTestCR(
    Uns32        bits,
    vmiCondition cond,
    Uns64        c,
    vmiReg       rb,
    vmiReg       flag
);

//
// Use this prefix operation immediately prior to vmimtBinop* call with a
// shift/rotate operation (any of vmi_ROL, vmi_ROR, vmi_RCL, vmi_RCR, vmi_SHL,
// vmi_SHR or vmi_SAR) to override the default shift mask for that operation.
//
// By default, register shift/rotate amounts are masked to the size of the
// shifted argument minus 1 (i.e. 1-byte shifts are masked to 0..7, 2-byte
// shifts to 0..15, 4-byte shifts to 0..31 and 8-byte shifts to 0..63). Using
// this prefix allows the mask to be overridden. For example, the ARM processor
// can handle shifts in the range 0..255, which can be specified using a shift
// mask of 255 immediately prior to a shift operation.
//
void vmimtSetShiftMask(Uns8 mask);


////////////////////////////////////////////////////////////////////////////////
// FLOATING POINT OPCODES
////////////////////////////////////////////////////////////////////////////////

//
// fd = fa
//
void vmimtFConvertRR(
    vmiFType      destType,
    vmiReg        fd,
    vmiFType      srcType,
    vmiReg        fa,
    vmiFPRC       rc,
    vmiReg        flags,
    vmiFPConfigCP config
);

//
// fd = <unop> fa
//
void vmimtFUnopRR(
    vmiFType      type,
    vmiFUnop      op,
    vmiReg        fd,
    vmiReg        fa,
    vmiReg        flags,
    vmiFPConfigCP config
);

//
// fd = fa <binop> fb
//
void vmimtFBinopRRR(
    vmiFType      type,
    vmiFBinop     op,
    vmiReg        fd,
    vmiReg        fa,
    vmiReg        fb,
    vmiReg        flags,
    vmiFPConfigCP config
);

//
// fd = <ternop>(fa, fb, fc)
//
void vmimtFTernopRRRR(
    vmiFType      type,
    vmiFTernop    op,
    vmiReg        fd,
    vmiReg        fa,
    vmiReg        fb,
    vmiReg        fc,
    vmiReg        flags,
    Bool          roundInt,
    vmiFPConfigCP config
);

//
// relation = <compare>(fa, fb)
//
void vmimtFCompareRR(
    vmiFType      type,
    vmiReg        relation,
    vmiReg        fa,
    vmiReg        fb,
    vmiReg        flags,
    Bool          allowQNaN,
    vmiFPConfigCP config
);

//
// rd = <compare>(fa, fb, <codes>)
//
void vmimtFCompareRRC(
    Uns8          rdBits,
    vmiFType      type,
    vmiReg        rd,
    vmiReg        fa,
    vmiReg        fb,
    vmiReg        flags,
    Bool          allowQNaN,
    Uns32         valueUN,
    Uns32         valueEQ,
    Uns32         valueLT,
    Uns32         valueGT,
    vmiFPConfigCP config
);


////////////////////////////////////////////////////////////////////////////////
// SIMD FLOATING POINT OPCODES
////////////////////////////////////////////////////////////////////////////////

//
// fd[0..num-1] = fa[0..num-1]
//
void vmimtFConvertSimdRR(
    Uns32         num,
    vmiFType      destType,
    vmiReg        fd,
    vmiFType      srcType,
    vmiReg        fa,
    vmiFPRC       rc,
    vmiReg        flags,
    vmiFPConfigCP config
);

//
// fd[0..num-1] = <unop> fa[0..num-1]
//
void vmimtFUnopSimdRR(
    vmiFType      type,
    Uns32         num,
    vmiFUnop      op,
    vmiReg        fd,
    vmiReg        fa,
    vmiReg        flags,
    vmiFPConfigCP config
);

//
// fd[0..num-1] = fa[0..num-1] <binop> fb[0..num-1]
//
void vmimtFBinopSimdRRR(
    vmiFType      type,
    Uns32         num,
    vmiFBinop     op,
    vmiReg        fd,
    vmiReg        fa,
    vmiReg        fb,
    vmiReg        flags,
    vmiFPConfigCP config
);

//
// fd[0..num-1] = <ternop>(fa[0..num-1], fb[0..num-1], fc[0..num-1])
//
void vmimtFTernopSimdRRRR(
    vmiFType      type,
    Uns32         num,
    vmiFTernop    op,
    vmiReg        fd,
    vmiReg        fa,
    vmiReg        fb,
    vmiReg        fc,
    vmiReg        flags,
    Bool          roundInt,
    vmiFPConfigCP config
);

//
// relation[0..num-1] = <compare>(fa[0..num-1], fb[0..num-1])
//
void vmimtFCompareSimdRR(
    vmiFType      type,
    Uns32         num,
    vmiReg        relation,
    vmiReg        fa,
    vmiReg        fb,
    vmiReg        flags,
    Bool          allowQNaN,
    vmiFPConfigCP config
);

//
// rd[0..num-1] = <compare>(fa[0..num-1], fb[0..num-1], <codes>)
//
void vmimtFCompareSimdRRC(
    Uns8          rdBits,
    vmiFType      type,
    Uns32         num,
    vmiReg        rd,
    vmiReg        fa,
    vmiReg        fb,
    vmiReg        flags,
    Bool          allowQNaN,
    Uns32         valueUN,
    Uns32         valueEQ,
    Uns32         valueLT,
    Uns32         valueGT,
    vmiFPConfigCP config
);


////////////////////////////////////////////////////////////////////////////////
// FLOATING POINT COMPOUND OPERATIONS
////////////////////////////////////////////////////////////////////////////////

//
// Start floating point compound operation. No state changes implied by
// morph-time operations after this point and before the matching vmimtFEnd
// will be committed if enabled floating point exceptions are taken.
//
void vmimtFStart(void);

//
// End floating point compound operation. If the compound operation flags are
// not sticky (config->stickyFlags is False), then accumulated operation flags
// are written to 'flags'. If there are consequently enabled floating point
// exceptions, the processor exception handler is called without committing
// any other operation results; otherwise, operation results are written to the
// processor structure. If the compound operation flags are sticky
// (config->stickyFlags is True), then operation flags are combined with the
// current flags in the 'flags' register using bitwise-or only if exceptions are
// not taken.
//
void vmimtFEnd(Uns32 num, vmiReg flags, vmiFPConfigCP config);


////////////////////////////////////////////////////////////////////////////////
// FLOATING POINT OPERATION ROUNDING CONTROL
////////////////////////////////////////////////////////////////////////////////

//
// Use this prefix operation immediately prior to function vmimtFUnopRR,
// vmimtFBinopRRR, vmimtFTernopRRRR, vmimtFUnopSimdRR, vmimtFBinopSimdRRR or
// vmimtFTernopSimdRRRR to override the default rounding mode to use with that
// operation (vmi_FPR_CURRENT)
//
void vmimtFSetRounding(vmiFPRC rc);


////////////////////////////////////////////////////////////////////////////////
// LOAD AND STORE OPCODES
////////////////////////////////////////////////////////////////////////////////

//
// mem[ra+offset] = rb  (when ra!=VMI_NOREG)
// mem[offset]    = rb  (when ra==VMI_NOREG)
//
void vmimtStoreRRO(
    Uns32         bits,
    Addr          offset,
    vmiReg        ra,
    vmiReg        rb,
    memEndian     endian,
    memConstraint constraint
);

//
// mem[ra+offset] = c  (when ra!=VMI_NOREG)
// mem[offset]    = c  (when ra==VMI_NOREG)
//
void vmimtStoreRCO(
    Uns32         bits,
    Addr          offset,
    vmiReg        ra,
    Uns64         c,
    memEndian     endian,
    memConstraint constraint
);

//
// rd = mem[ra+offset]  (when ra!=VMI_NOREG)
// rd = mem[offset]     (when ra==VMI_NOREG)
// NB rd is destBits, memory is memBits
//
void vmimtLoadRRO(
    Uns32         destBits,
    Uns32         memBits,
    Addr          offset,
    vmiReg        rd,
    vmiReg        ra,
    memEndian     endian,
    Bool          signExtend,
    memConstraint constraint
);

//
// trystore mem[ra+offset]  (when ra!=VMI_NOREG)
// trystore mem[offset]     (when ra==VMI_NOREG)
//
void vmimtTryStoreRC(
    Uns32         bits,
    Addr          offset,
    vmiReg        ra,
    memConstraint constraint
);

//
// tryload mem[ra+offset]  (when ra!=VMI_NOREG)
// tryload mem[offset]     (when ra==VMI_NOREG)
//
void vmimtTryLoadRC(
    Uns32         bits,
    Addr          offset,
    vmiReg        ra,
    memConstraint constraint
);

//
// preload mem[ra+offset]  (when ra!=VMI_NOREG)
// preload mem[offset]     (when ra==VMI_NOREG)
//
void vmimtPreLoadRC(
    Addr           offset,
    vmiReg         ra,
    memPreloadType type
);


////////////////////////////////////////////////////////////////////////////////
// LOAD AND STORE OPCODES WITH EXPLICIT DOMAIN
////////////////////////////////////////////////////////////////////////////////

//
// mem[ra+offset] = rb  (when ra!=VMI_NOREG)
// mem[offset]    = rb  (when ra==VMI_NOREG)
//
void vmimtStoreRRODomain(
    memDomainP    domain,
    Uns32         bits,
    Addr          offset,
    vmiReg        ra,
    vmiReg        rb,
    memEndian     endian,
    memConstraint constraint
);

//
// mem[ra+offset] = c  (when ra!=VMI_NOREG)
// mem[offset]    = c  (when ra==VMI_NOREG)
//
void vmimtStoreRCODomain(
    memDomainP    domain,
    Uns32         bits,
    Addr          offset,
    vmiReg        ra,
    Uns64         c,
    memEndian     endian,
    memConstraint constraint
);

//
// rd = mem[ra+offset]  (when ra!=VMI_NOREG)
// rd = mem[offset]     (when ra==VMI_NOREG)
// NB rd is given by destBits
//    mem is given by memBits
//
void vmimtLoadRRODomain(
    memDomainP    domain,
    Uns32         destBits,
    Uns32         memBits,
    Addr          offset,
    vmiReg        rd,
    vmiReg        ra,
    memEndian     endian,
    Bool          signExtend,
    memConstraint constraint
);

//
// trystore mem[ra+offset]  (when ra!=VMI_NOREG)
// trystore mem[offset]     (when ra==VMI_NOREG)
//
void vmimtTryStoreRCDomain(
    memDomainP    domain,
    Uns32         bits,
    Addr          offset,
    vmiReg        ra,
    memConstraint constraint
);

//
// tryload mem[ra+offset]  (when ra!=VMI_NOREG)
// tryload mem[offset]     (when ra==VMI_NOREG)
//
void vmimtTryLoadRCDomain(
    memDomainP    domain,
    Uns32         bits,
    Addr          offset,
    vmiReg        ra,
    memConstraint constraint
);

//
// preload mem[ra+offset]  (when ra!=VMI_NOREG)
// preload mem[offset]     (when ra==VMI_NOREG)
//
void vmimtPreLoadRCDomain(
    memDomainP     domain,
    Addr           offset,
    vmiReg         ra,
    memPreloadType type
);


////////////////////////////////////////////////////////////////////////////////
// INTER-INSTRUCTION CONDITIONAL AND UNCONDITIONAL JUMPS
////////////////////////////////////////////////////////////////////////////////

//
// This prefix operation can be used immediately prior to jump, load or store
// morph-time operations to specify masking of addresses.
//
// When used immediately prior to vmimt*Jump* calls, this specifies required
// masking of target and link addresses. For example, specifying an address mask
// of -2 will cause the least significant bit of target and return addresses to
// be discarded.
//
// When used immediately prior to vmimt*Load* or vmimt*Store* calls, this
// specifies the effective number of bits used to calculate the load/store
// address. Any computed address will be modified so that all bits above the
// most-significant non-zero bit in the mask are zeroed.
//
// More advanced load/store address masking is possible using run-time function
// vmirtSetLoadStoreMask.
//
void vmimtSetAddressMask(Uns64 mask);

//
// Perform an unconditional direct jump to 'toAddress'. If 'linkReg' is not
// VMI_NOREG, then 'linkPC' should be placed in this register. This
// variant is for jumps with no delay slot instructions.
//
void vmimtUncondJump(
    Addr        linkPC,
    Addr        toAddress,
    vmiReg      linkReg,
    vmiJumpHint hint
);

//
// Perform an unconditional direct jump to 'toAddress'. If 'linkReg' is not
// VMI_NOREG, then 'linkPC' should be placed in this register. This
// variant is for jumps with 'slotOps' delay slot instructions.
//
void vmimtUncondJumpDelaySlot(
    Uns32         slotOps,
    Addr          linkPC,
    Addr          toAddress,
    vmiReg        linkReg,
    vmiJumpHint   hint,
    vmiPostSlotFn slotCB
);

//
// Perform an unconditional indirect jump. The target location is in register
// 'toReg'. If 'linkReg' is not VMI_NOREG, then 'linkPC' should be placed
// in this register. This variant is for jumps with no delay slot instructions.
//
void vmimtUncondJumpReg(
    Addr        linkPC,
    vmiReg      toReg,
    vmiReg      linkReg,
    vmiJumpHint hint
);

//
// Perform an unconditional indirect jump. The target location is in register
// 'toReg'. If 'linkReg' is not VMI_NOREG, then 'linkPC' should be placed
// in this register. This variant is for jumps with 'slotOps' delay slot
// instructions.
//
void vmimtUncondJumpRegDelaySlot(
    Uns32         slotOps,
    Addr          linkPC,
    vmiReg        toReg,
    vmiReg        linkReg,
    vmiJumpHint   hint,
    vmiPostSlotFn slotCB
);

//
// Perform a conditional jump if the condition flag is non-zero (jumpIfTrue)
// or zero (not jumpIfTrue). The target location is pointed at by toAddress.
// This variant is for jumps with no delay slot instructions.
//
void vmimtCondJump(
    vmiReg      flag,   // byte
    Bool        jumpIfTrue,
    Addr        linkPC,
    Addr        toAddress,
    vmiReg      linkReg,
    vmiJumpHint hint
);

//
// Perform a conditional jump if the condition flag is non-zero (jumpIfTrue)
// or zero (not jumpIfTrue). The target location is pointed at by toAddress.
// This variant is for jumps with 'slotOps' delay slot instructions.
//
void vmimtCondJumpDelaySlot(
    Uns32         slotOps,
    vmiReg        flag, // byte
    Bool          jumpIfTrue,
    Addr          linkPC,
    Addr          toAddress,
    vmiReg        linkReg,
    vmiJumpHint   hint,
    vmiPostSlotFn slotCB
);

//
// Perform a conditional jump if the condition flag is non-zero (jumpIfTrue)
// or zero (not jumpIfTrue). The target location is pointed at by toAddress.
// The absolute value of 'slotOps' gives the number of delay slot instructions.
// If 'slotOps' is positive, delay slot instructions are annulled if the branch
// is taken; if 'slotOps' is negative, delay slot instructions are annulled if
// the branch is not taken. See also function vmimtSkipIfAnnul.
//
void vmimtCondJumpDelaySlotAnnul(
    Int32         slotOps,
    vmiReg        flag, // byte
    Bool          jumpIfTrue,
    Addr          linkPC,
    Addr          toAddress,
    vmiReg        linkReg,
    vmiJumpHint   hint,
    vmiPostSlotFn slotCB
);

//
// Perform a conditional jump if the condition flag is non-zero (jumpIfTrue)
// or zero (not jumpIfTrue). The target location is in register 'toReg'.
// This variant is for jumps with no delay slot instructions.
//
void vmimtCondJumpReg(
    vmiReg      flag,   // byte
    Bool        jumpIfTrue,
    Addr        linkPC,
    vmiReg      toReg,
    vmiReg      linkReg,
    vmiJumpHint hint
);

//
// Perform a conditional jump if the condition flag is non-zero (jumpIfTrue)
// or zero (not jumpIfTrue). The target location is in register 'toReg'.
// This variant is for jumps with 'slotOps' delay slot instructions.
//
void vmimtCondJumpRegDelaySlot(
    Uns32         slotOps,
    vmiReg        flag, // byte
    Bool          jumpIfTrue,
    Addr          linkPC,
    vmiReg        toReg,
    vmiReg        linkReg,
    vmiJumpHint   hint,
    vmiPostSlotFn slotCB
);

//
// Perform a conditional jump if the condition flag is non-zero (jumpIfTrue)
// or zero (not jumpIfTrue). The target location is in register 'toReg'.
// The absolute value of 'slotOps' gives the number of delay slot instructions.
// If 'slotOps' is positive, delay slot instructions are annulled if the branch
// is taken; if 'slotOps' is negative, delay slot instructions are annulled if
// the branch is not taken. See also function vmimtSkipIfAnnul.
//
void vmimtCondJumpRegDelaySlotAnnul(
    Int32         slotOps,
    vmiReg        flag, // byte
    Bool          jumpIfTrue,
    Addr          linkPC,
    vmiReg        toReg,
    vmiReg        linkReg,
    vmiJumpHint   hint,
    vmiPostSlotFn slotCB
);

//
// Perform an unconditional direct jump to 'simPC1', execute 'slotOps'
// instructions at that address, and then jump to 'simPC2'. If 'slotCB' is
// non-null, it will be executed on completion of the instruction sequence at
// address 'simPC1'
//
void vmimtEnterDelaySlotC(
    Uns32         slotOps,
    Addr          simPC1,
    Addr          simPC2,
    vmiPostSlotFn slotCB
);

//
// Perform an unconditional indirect jump to 'toReg', execute 'slotOps'
// instructions at that address, and then jump to 'simPC2'. If 'slotCB' is
// non-null, it will be executed on completion of the instruction sequence at
// address 'toReg'
//
void vmimtEnterDelaySlotR(
    Uns32         slotOps,
    vmiReg        toReg,
    Addr          simPC2,
    vmiPostSlotFn slotCB
);

//
// Valid in delay slot only.
// If getNextPC is True, move the program counter of the instruction to be
// executed immediately after the delay slot instruction into targetReg.
// If getNextPC is False, move the target address from the preceding jump
// instruction into targetReg (this differs after vmimtCondJumpDelaySlot for a
// branch that is not taken).
//
void vmimtGetDelaySlotNextPC(vmiReg targetReg, Bool getNextPC);

//
// Skip remaining actions for the current instruction if it is being annulled.
//
void vmimtSkipIfAnnul(void);


////////////////////////////////////////////////////////////////////////////////
// INTRA-INSTRUCTION CONDITIONAL AND UNCONDITIONAL JUMPS
////////////////////////////////////////////////////////////////////////////////

//
// Allocate a new label. Insert it where required using vmimtInsertLabel below.
//
vmiLabelP vmimtNewLabel(void);

//
// Insert a label previously created by vmimtNewLabel at the current location.
//
void vmimtInsertLabel(vmiLabelP label);

//
// Perform an unconditional jump to the passed local label.
//
void vmimtUncondJumpLabel(vmiLabelP toLabel);

//
// Perform a conditional jump if the condition flag is non-zero (jumpIfTrue)
// or zero (not jumpIfTrue). The target location is the passed local label.
//
void vmimtCondJumpLabel(vmiReg flag, Bool jumpIfTrue, vmiLabelP toLabel);

//
// Perform a conditional jump if the result of a previous native function call
// (called with vmimtCall) is non-zero (jumpIfTrue) or zero (not jumpIfTrue).
// The target location is the passed local label.
//
void vmimtCondJumpLabelFunctionResult(Bool jumpIfTrue, vmiLabelP toLabel);

//
// Test the register values by performing bitwise AND, and jump to 'toLabel' if
// condition 'cond' is satisfied.
//
void vmimtTestRRJumpLabel(
    Uns32        bits,
    vmiCondition cond,
    vmiReg       ra,
    vmiReg       rb,
    vmiLabelP    toLabel
);

//
// Test the register value by performing bitwise AND with the passed constant
// value, and jump to 'toLabel' if condition 'cond' is satisfied.
//
void vmimtTestRCJumpLabel(
    Uns32        bits,
    vmiCondition cond,
    vmiReg       r,
    Uns64        c,
    vmiLabelP    toLabel
);

//
// Compare the register values and jump to 'toLabel' if condition 'cond' is
// satisfied.
//
void vmimtCompareRRJumpLabel(
    Uns32        bits,
    vmiCondition cond,
    vmiReg       ra,
    vmiReg       rb,
    vmiLabelP    toLabel
);

//
// Compare the register value with the passed constant and jump to 'toLabel'
// if condition 'cond' is satisfied.
//
void vmimtCompareRCJumpLabel(
    Uns32        bits,
    vmiCondition cond,
    vmiReg       r,
    Uns64        c,
    vmiLabelP    toLabel
);


////////////////////////////////////////////////////////////////////////////////
// INDEXED AND VECTOR REGISTER ACCESS
////////////////////////////////////////////////////////////////////////////////

//
// Prepare index register that can be used to access members of register 'r'.
// Base register 'base' is a pointer-sized base pointer that is modified to
// access individual members. 'bytes' is the total size of register 'r'.
//
void vmimtGetIndexedRegister(vmiReg *r, vmiReg *base, Uns32 bytes);

//
// Add 'bytes' to pointer-sized base register 'base'. If 'vectorBytes' is
// non-zero, wrap the pointer value if it addresses a value beyond this vector
// size (or, if 'bytes' is negative, addresses a value below the vector
// base). If 'vectorBytes' is zero, no vector limit check is performed.
//
void vmimtAddBaseC(vmiReg base, Int32 bytes, Uns32 vectorBytes);

//
// Write the current offset in bytes of the base register to 'offset'
//
void vmimtGetBaseOffset(Uns32 bits, vmiReg offset, vmiReg base);

//
// Add value of IntPS-valued register 'offset' multiplied by 'scale' to
// pointer-sized base pointer register 'base', which addresses a vector of
// size 'vectorBytes'. If 'checkWrapLow' is True, wrap the pointer value if it
// addresses a value below the vector base. If 'checkWrapHigh' is True, wrap the
// pointer value if it addresses a value beyond the vector size. If
// 'vectorBytes' is zero, no vector limit check is performed.
//
void vmimtAddBaseR(
    vmiReg base,
    vmiReg offset,
    Uns32  scale,
    Uns32  vectorBytes,
    Bool   checkWrapLow,
    Bool   checkWrapHigh
);

//
// rd[((count-countInc)*countScale)*8:0] = 0
//
void vmimtZeroRV(
    Uns32         destMaxBits,
    vmiReg        rd,
    Uns32         countBits,
    vmiReg        count,
    Int32         countInc,
    Uns32         countScale,
    vmiCheckCount checkCount
);

//
// rd[((count-countInc)*countScale)*8:0] = ra
//
void vmimtMoveRRV(
    Uns32         destMaxBits,
    vmiReg        rd,
    vmiReg        ra,
    Uns32         countBits,
    vmiReg        count,
    Int32         countInc,
    Uns32         countScale,
    vmiCheckCount checkCount
);

//
// Operate on the indexed bit in a bit vector register. The value of the
// indicated bit (before modification) is written to byte register 'set'. The
// size of the vector register is given by 'vBits' and the size of the index
// register by 'iBits'
//
void vmimtBitopVR(
    Uns32    vBits,
    Uns32    iBits,
    vmiBitop op,
    vmiReg   rv,
    vmiReg   ri,
    vmiReg   set
);

//
// Decrement the register value and jump to preceding label 'toLabel' if the
// result is non-zero
//
void vmimtDJNZLabel(Uns32 bits, vmiReg r, vmiLabelP toLabel);

//
// Test the indexed bit in a bit vector register and jump to the given label if
// the bit is set or clear. The size of the vector register is given by 'vBits'
// and the size of the index register by 'iBits'
//
void vmimtTestBitVRJumpLabel(
    Uns32     vBits,
    Uns32     iBits,
    Bool      jumpIfSet,
    vmiReg    rv,
    vmiReg    ri,
    vmiLabelP toLabel
);


////////////////////////////////////////////////////////////////////////////////
// MORPHED CODE CONTROL
////////////////////////////////////////////////////////////////////////////////

//
// Terminate the current code block by forcing a jump to the next instruction
//
void vmimtEndBlock(void);

//
// Get the processor built-in blockMask into the passed 32-bit register
//
void vmimtGetBlockMask(vmiReg blockMask);

//
// Set the processor built-in blockMask to the passed constant value
//
void vmimtSetBlockMaskC(Uns32 blockMask);

//
// Set the processor built-in blockMask to the passed 32-bit register value
//
void vmimtSetBlockMaskR(vmiReg blockMask);

//
// 'modeMask' is a bitmask selecting a subset of bits from the processor
// built-in block mask (set using vmimtSetBlockMask* or vmirtSetBlockMask
// functions). When the code block is executed, this function validates that the
// bits selected by 'modeMask' match the processor block mask state when the
// code block was generated. If there is a mismatch, the code block is
// regenerated.
//
void vmimtValidateBlockMask(Uns32 modeMask);

//
// This function works exactly as vmimtValidateBlockMask except that the
// block mask register is a general processor register of up to 64 bits instead
// of the 32-bit built-in block mask.
//
void vmimtValidateBlockMaskR(Uns32 bits, vmiReg r, Uns64 modeMask);

//
// Mark the current code block with the given tag. Such blocks may be either
// deleted or preserved when blocks are flushed using function
// vmirtFlushTargetModeTagged. Tagging is cumulative: multiple calls to
// vmimtTagBlock combine tag values using bitwise-or.
//
void vmimtTagBlock(vmiBlockTag tag);

//
// Specify that the current code block is polymorphic, with variants selected
// by non-zero values in the 'key' register.
//
void vmimtPolymorphicBlock(Uns32 bits, vmiReg key);


////////////////////////////////////////////////////////////////////////////////
// CONNECTION OBJECTS
////////////////////////////////////////////////////////////////////////////////

//
// rd = get(ca)
//
// Perform blocking get from connection object 'connReg'. 'bits' must match the
// connection width. If no data is available, this processor will block until it
// becomes available, at which point 'updateCB' will be called.
// If 'peek' is True, data read will not be removed from the connection object.
// If 'rd' is VMI_NOREG, the current processor will stall until data becomes
// available but no data will be read.
//
void vmimtConnGetRB(
    Uns32           bits,
    vmiReg          rd,
    vmiReg          connReg,
    Bool            peek,
    vmiConnUpdateFn updateCB
);

//
// rd = get(ca)
//
// Perform non-blocking get from connection object 'connReg'. 'bits' must match
// the connection width. If no data is available, 'flag' will be set to False
// and 'rd' will be unchanged; otherwise, 'flag' will be set to True and 'rd'
// will hold the value read from the connection.
// If 'peek' is True, data read will not be removed from the connection object.
// If 'rd' is VMI_NOREG, 'flag' will indicate whether data is present but no
// data will be read.
//
void vmimtConnGetRNB(
    Uns32  bits,
    vmiReg rd,
    vmiReg connReg,
    Bool   peek,
    vmiReg flag      // byte
);

//
// put(ca, ra)
//
// Perform blocking put to connection object 'connReg'. 'bits' must match the
// connection width. If the connection object is full, this processor will block
// until space becomes available, at which point 'updateCB' will be called.
// If 'ra' is VMI_NOREG, the current processor will stall until there is space
// to put in the connection object but no data will be put.
//
void vmimtConnPutRB(
    Uns32           bits,
    vmiReg          connReg,
    vmiReg          ra,
    vmiConnUpdateFn updateCB
);

//
// put(ca, ra)
//
// Perform non-blocking put to connection object 'connReg'. 'bits' must match
// the connection width. If the connection object is full, 'flag' will be set to
// False; otherwise, 'flag' will be set to True.
// If 'ra' is VMI_NOREG, 'flag' will indicate whether there is space to put in
// the connection object but no data will be put.
//
void vmimtConnPutRNB(
    Uns32  bits,
    vmiReg connReg,
    vmiReg ra,
    vmiReg flag     // byte
);


////////////////////////////////////////////////////////////////////////////////
// SIMULATOR CONTROL
////////////////////////////////////////////////////////////////////////////////

//
// Explicitly suspend simulation of the current processor on completion of the
// current simulated instruction to allow other processors in a multiprocessor
// simulation to run. Simulation of the processor will restart when all other
// runnable processors have executed.
//
void vmimtYield(void);

//
// Halt the current processor on completion of the current simulated
// instruction. The processor will remain halted until restarted by a call to
// vmirtRestartNext or vmirtRestartNow.
//
void vmimtHalt(void);

//
// Interrupt simulation of the current processor on completion of the
// current simulated instruction and return from simulator invocation.
//
void vmimtInterrupt(void);

//
// Immediately end simulation of the current processor. Simulation of other
// processors in a multiprocessor platform will continue.
//
void vmimtExit(void);

//
// Immediately end simulation of the current processor. Simulation of other
// processors in a multiprocessor platform will also end on completion of the
// current time slice.
//
void vmimtFinish(void);

//
// Cause the processor to advance immediately to the end of its scheduled time
// slot or until the next timer event, as if it had executed nop instructions
// in the interim.
//
void vmimtIdle(void);

//
// Indicate that the current instruction should be executed atomically in a
// multiprocessor simulation
//
void vmimtAtomic(void);


////////////////////////////////////////////////////////////////////////////////
// INSTRUCTION COUNTING
////////////////////////////////////////////////////////////////////////////////

//
// rd = <instruction count>
//
void vmimtICount(Uns32 bits, vmiReg rd);


////////////////////////////////////////////////////////////////////////////////
// EMBEDDED CALL INTERFACE
////////////////////////////////////////////////////////////////////////////////

//
// Add various argument types to the stack frame
//
void vmimtArgProcessor(void);
void vmimtArgUns32(Uns32 arg);
void vmimtArgUns64(Uns64 arg);
void vmimtArgFlt64(Flt64 arg);
void vmimtArgReg(vmiRegArgType argType, vmiReg r);
void vmimtArgRegP(vmiRegPArgUsage usage, Uns32 bits, vmiReg r);
void vmimtArgRegSimAddress(Uns32 bits, vmiReg r);
void vmimtArgSimAddress(Addr arg);
void vmimtArgSimPC(Uns32 bits);
void vmimtArgNatAddress(const void *arg);

//
// Deprecated name for argument type function
//
#define vmimtArgDouble vmimtArgFlt64

//
// Make a call with all current stack frame arguments. If 'rd' is not VMI_NOREG,
// the function result (of size bits) is assigned to this register. Argument
// 'attrs' is used to define optimization attributes of a called function
// (see the comment preceding the definition of that type).
//
void vmimtCallResultAttrs(
    vmiCallFn    arg,
    Uns32        bits,
    vmiReg       rd,
    vmiCallAttrs attrs
);

//
// Backwards-compatible vmimtCall
//
#define vmimtCall(_ARG) \
    vmimtCallResultAttrs(_ARG, 0, VMI_NOREG, VMCA_NA)

//
// Backwards-compatible vmimtCallResult
//
#define vmimtCallResult(_ARG, _BITS, _RD) \
    vmimtCallResultAttrs(_ARG, _BITS, _RD, VMCA_NA)

//
// Backwards-compatible vmimtCallAttrs
//
#define vmimtCallAttrs(_ARG, _ATTRS) \
    vmimtCallResultAttrs(_ARG, 0, VMI_NOREG, _ATTRS)


////////////////////////////////////////////////////////////////////////////////
// SMP PROCESSOR SUPPORT
////////////////////////////////////////////////////////////////////////////////

//
// Return the equivalent vmiReg of the passed VMI register object for the
// Nth-level SMP parent of the current processor (where level 0 is this
// processor, level 1 is the parent, level 2 is the grandparent etc).
//
// This function must be used to create VMI register descriptions when the
// current processor can change its Nth-level SMP parent processor at run time
// (see vmirtSetSMPParent in the VMI Run Time Function API).
//
vmiReg vmimtGetSMPParentRegister(vmiReg r, Uns32 level);


////////////////////////////////////////////////////////////////////////////////
// INSTRUCTION ATTRIBUTE QUERY SUPPORT
////////////////////////////////////////////////////////////////////////////////

//
// Specify that subsequent reads of the register in this instruction are model
// artifacts and not true read accesses. This is required if a write access
// updates only certain fields of a register and this is implemented using
// a sequence of vmi_ANDN/vmi_OR operations.
//
void vmimtRegNotReadR(Uns32 bits, vmiReg r);

//
// Specify that the current instruction implements a read of the named register
// in the processor debug API. The name must match the name of a vmiRegInfoCP
// object.
//
void vmimtRegReadImpl(const char *name);

//
// Specify that the current instruction implements a write of the named register
// in the processor debug API. The name must match the name of a vmiRegInfoCP
// object.
//
void vmimtRegWriteImpl(const char *name);

//
// Add non-zero bits in the given instruction class bit mask to the instruction
// class of the current instruction
//
void vmimtInstructionClassAdd(octiaInstructionClass value);

//
// Remove non-zero bits in the given instruction class bit mask from the
// instruction class of the current instruction
//
void vmimtInstructionClassSub(octiaInstructionClass value);

//
// Indicate that the current instruction is conditional using the given
// condition code (a value of 0 means unconditional)
//
void vmimtSetInstructionCondition(Uns32 condition);


////////////////////////////////////////////////////////////////////////////////
// EXTENSION LIBRARY MORPH-TIME UTILITIES
////////////////////////////////////////////////////////////////////////////////

//
// Get processor register, assigning result to rd
//
void vmimtGetR(
    vmiProcessorP processor,
    Uns32         bits,
    vmiReg        rd,
    vmiRegInfoCP  ra
);

//
// Set processor register from register ra
//
void vmimtSetR(
    vmiProcessorP processor,
    Uns32         bits,
    vmiRegInfoCP  rd,
    vmiReg        ra
);

//
// Utility function returning a vmiReg object to access the given address as
// a register when executing in the processor context
//
vmiReg vmimtGetExtReg(vmiProcessorP processor, void *pointer);

//
// Utility function returning a vmiReg object to access the given address as
// a temporary when executing in the processor context
//
vmiReg vmimtGetExtTemp(vmiProcessorP processor, void *pointer);


////////////////////////////////////////////////////////////////////////////////
// DELAY ESTIMATION
////////////////////////////////////////////////////////////////////////////////

//
// Add a constant to the count of skipped instructions for the processor
//
void vmimtAddSkipCountC(Uns64 skipCount);

//
// Add a variable to the count of skipped instructions for the processor
//
void vmimtAddSkipCountR(Uns32 bits, vmiReg skipCount);


