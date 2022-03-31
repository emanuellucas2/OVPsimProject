/*
 * Copyright (c) 2011-2014 Posedge Software Inc., www.posedgesoft.com
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


#ifndef m16c_FUNCTIONS_H
#define m16c_FUNCTIONS_H

// VMI header files
#include "vmi/vmiAttrs.h"

// constructor & destructor
VMI_CONSTRUCTOR_FN(m16cConstructor);
VMI_DESTRUCTOR_FN(m16cDestructor);

// morph function
VMI_MORPH_FN(m16cMorphInstruction);

// simulation support functions
VMI_ENDIAN_FN(m16cGetEndian);
VMI_NEXT_PC_FN(m16cNextInstruction);
VMI_DISASSEMBLE_FN(m16cDisassemble);

// register access
VMI_REG_INFO_FN(m16cRegInfo);
VMI_DEBUG_FN(m16cDumpRegisters);

// Arithmetic exception
VMI_ARITH_EXCEPT_FN(m16cArithExceptionCB);
VMI_RD_ALIGN_EXCEPT_FN(m16cRdAlignExceptionCB);
VMI_WR_ALIGN_EXCEPT_FN(m16cWrAlignExceptionCB);

// Fetch exception
VMI_IFETCH_FN(m16cIFetchExceptionCB);

// parameter support functions
VMI_PROC_PARAM_SPECS_FN(m16cGetParamSpec);
VMI_PROC_PARAM_TABLE_SIZE_FN(m16cParamValueSize);

// port functions
VMI_BUS_PORT_SPECS_FN(m16cGetBusPortSpec);
VMI_NET_PORT_SPECS_FN(m16cGetNetPortSpec);


// Exception Info support
VMI_EXCEPTION_INFO_FN(m16cExceptionInfo);
VMI_GET_EXCEPTION_FN(m16cGetException);

// Processor information support
VMI_PROC_INFO_FN(m16cProcInfo);

// Imperas intercpted function support
VMI_INT_RETURN_FN(m16cIntReturnCB);
VMI_INT_RESULT_FN(m16cIntResultCB);
VMI_INT_PAR_FN(m16cIntParCB);

#endif


