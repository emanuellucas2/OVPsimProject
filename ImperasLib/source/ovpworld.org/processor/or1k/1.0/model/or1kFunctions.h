/*
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef OR1K_FUNCTIONS_H
#define OR1K_FUNCTIONS_H

// VMI header files
#include "vmi/vmiAttrs.h"
#include "vmi/vmiPorts.h"


// save/restore functions
VMI_SAVE_STATE_FN(or1kSaveStateCB);
VMI_RESTORE_STATE_FN(or1kRestoreStateCB);

// constructor & destructor
VMI_CONSTRUCTOR_FN(or1kConstructor);
VMI_VMINIT_FN(or1kVMInit);
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

// Imperas intercepted function support
VMI_INT_RETURN_FN(or1kIntReturnCB);
VMI_INT_RESULT_FN(or1kIntResultCB);
VMI_INT_PAR_FN(or1kIntParCB);

// parameter support functions
VMI_PROC_PARAM_SPECS_FN(or1kGetParamSpec);
VMI_PROC_PARAM_TABLE_SIZE_FN(or1kParamValueSize);

// port functions
VMI_BUS_PORT_SPECS_FN(or1kGetBusPortSpec);
VMI_FIFO_PORT_SPECS_FN(or1kGetFifoPortSpec);
VMI_NET_PORT_SPECS_FN(or1kGetNetPortSpec);

// processor info routine
VMI_PROC_INFO_FN(or1kProcInfo);

#endif

