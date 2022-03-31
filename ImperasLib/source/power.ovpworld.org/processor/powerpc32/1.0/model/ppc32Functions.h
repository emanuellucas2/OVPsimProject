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

#ifndef PPC32_FUNCTIONS_H
#define PPC32_FUNCTIONS_H
#include "vmi/vmiAttrs.h"

// constructor & destructor
VMI_CONSTRUCTOR_FN(ppc32Constructor);
VMI_VMINIT_FN(ppc32VMInit);
VMI_DESTRUCTOR_FN(ppc32Destructor);

// morph function
VMI_MORPH_FN(ppc32Morph);
VMI_FETCH_SNAP_FN(ppc32FetchSnap);
VMI_RD_WR_SNAP_FN(ppc32RdSnap);
VMI_RD_WR_SNAP_FN(ppc32WrSnap);

// simulation support functions
VMI_ENDIAN_FN(ppc32GetEndian);
VMI_NEXT_PC_FN(ppc32nextPC);
VMI_DISASSEMBLE_FN(ppc32Dis);
VMI_IASSWITCH_FN(ppc32Switch);

// debugger integration support routines
VMI_REG_GROUP_FN(ppc32RegGroup);
VMI_REG_INFO_FN(ppc32RegInfo);
VMI_EXCEPTION_INFO_FN(ppc32ExceptionInfo);
VMI_MODE_INFO_FN(ppc32ModeInfo);
VMI_GET_EXCEPTION_FN(ppc32GetException);
VMI_GET_MODE_FN(ppc32GetMode);
VMI_DEBUG_FN(ppc32Debug);

// exception functions
VMI_RD_PRIV_EXCEPT_FN(ppc32RdPrivExcept);
VMI_WR_PRIV_EXCEPT_FN(ppc32WrPrivExcept);
VMI_RD_ALIGN_EXCEPT_FN(ppc32RdAlignExcept);
VMI_WR_ALIGN_EXCEPT_FN(ppc32WrAlignExcept);
VMI_RD_ABORT_EXCEPT_FN(ppc32RdAbortExcept);
VMI_WR_ABORT_EXCEPT_FN(ppc32WrAbortExcept);
VMI_IFETCH_FN(ppc32IfetchExcept);
VMI_ARITH_EXCEPT_FN(ppc32ArithExcept);
VMI_FP_ARITH_EXCEPT_FN(ppc32FPArithExcept);
VMI_ICOUNT_FN(ppc32IcountExcept);

// parameter support functions
VMI_PROC_PARAM_SPECS_FN(ppc32ParamSpecs);
VMI_PROC_PARAM_TABLE_SIZE_FN(ppc32ParamValueSize);

// port/net functions
VMI_BUS_PORT_SPECS_FN(ppc32BusPortSpecs);
VMI_NET_PORT_SPECS_FN(ppc32NetPortSpecs);

// Imperas intercepted function support
VMI_INT_RETURN_FN(ppc32IntReturn);
VMI_INT_RESULT_FN(ppc32IntResult);
VMI_INT_PAR_FN(ppc32IntPar);

// Processor information support
VMI_PROC_INFO_FN(ppc32ProcInfo);
#endif // PPC32_FUNCTIONS_H
