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

#ifndef OR1K_FUNCTIONS_H
#define OR1K_FUNCTIONS_H

// VMI header files
#include "vmi/vmiAttrs.h"

// save/restore functions
VMI_SAVE_STATE_FN(or1kSaveStateCB);
VMI_RESTORE_STATE_FN(or1kRestoreStateCB);

// constructor & destructor
VMI_CONSTRUCTOR_FN(or1kConstructor);
VMI_DESTRUCTOR_FN(or1kDestructor);

// morph function
VMI_MORPH_FN(or1kMorphInstruction);

// simulation support functions
VMI_ENDIAN_FN(or1kGetEndian);
VMI_NEXT_PC_FN(or1kNextInstruction);
VMI_DISASSEMBLE_FN(or1kDisassemble);

// exception functions
VMI_RD_PRIV_EXCEPT_FN(or1kRdPrivExceptionCB);
VMI_WR_PRIV_EXCEPT_FN(or1kWrPrivExceptionCB);
VMI_RD_ALIGN_EXCEPT_FN(or1kRdAlignExceptionCB);
VMI_WR_ALIGN_EXCEPT_FN(or1kWrAlignExceptionCB);
VMI_ARITH_EXCEPT_FN(or1kArithExceptionCB);
VMI_IFETCH_FN(or1kIFetchExceptionCB);
VMI_ICOUNT_FN(or1kICountPendingCB);

// debugger integration
VMI_REG_GROUP_FN(or1kRegGroup);
VMI_REG_INFO_FN(or1kRegInfo);
VMI_REG_IMPL_FN(or1kRegImpl);
VMI_EXCEPTION_INFO_FN(or1kExceptionInfo);
VMI_MODE_INFO_FN(or1kModeInfo);
VMI_GET_EXCEPTION_FN(or1kGetException);
VMI_GET_MODE_FN(or1kGetMode);
VMI_DEBUG_FN(or1kDumpRegisters);

// Imperas intercpted function support
VMI_INT_RETURN_FN(or1kIntReturnCB);

// port functions
VMI_BUS_PORT_SPECS_FN(or1kGetBusPortSpec);
VMI_NET_PORT_SPECS_FN(or1kGetNetPortSpec);

// Processor Info routine
VMI_PROC_INFO_FN(or1kProcInfo);

#endif

