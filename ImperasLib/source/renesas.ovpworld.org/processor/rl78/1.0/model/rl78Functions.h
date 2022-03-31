/*
 * Copyright (c)      2016 eSOL TRINITY, www.esol-trinity.co.jp
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

#ifndef RL78_FUNCTIONS_H
#define RL78_FUNCTIONS_H

// VMI header files
#include "vmi/vmiAttrs.h"

// CREATE/DELETE ROUTINES
VMI_CONSTRUCTOR_FN(rl78Constructor);          // rl78Main.c
VMI_VMINIT_FN(rl78VmInit);                    // rl78Main.c
VMI_DESTRUCTOR_FN(rl78Destructor);            // rl78Main.c

// MORPHER CORE ROUTINES
VMI_MORPH_FN(rl78MorphInstruction);            // rl78Morph.c
VMI_RD_WR_SNAP_FN(rl78RdSnapCB);               // rl78Morph.c
VMI_RD_WR_SNAP_FN(rl78WrSnapCB);               // rl78Morph.c

// SIMULATION SUPPORT ROUTINES
VMI_ENDIAN_FN(rl78GetEndian);                  // rl78Utils.c
VMI_NEXT_PC_FN(rl78NextInstruction);           // rl78Utils.c
VMI_DISASSEMBLE_FN(rl78Disassemble);           // rl78Disassemble.c

// EXCEPTION ROUTINES
VMI_IFETCH_FN(rl78IFetchExceptionCB);          // rl78Exceptions.c

// PORT ROUTINES
VMI_BUS_PORT_SPECS_FN(rl78GetBusPortSpec);     // rl78Main.c
VMI_NET_PORT_SPECS_FN(rl78GetNetPortSpec);     // rl78Exceptions.c

// PARAMETER SUPPORT ROUTINES
VMI_PROC_PARAM_SPECS_FN(rl78GetParamSpec);           // rl78Parameters.c
VMI_PROC_PARAM_TABLE_SIZE_FN(rl78ParamValueSize);    // rl78Parameters.c

// DEBUGGER INTEGRATION SUPPORT ROUTINES
VMI_REG_GROUP_FN(rl78RegGroup);                // rl78Registers.c
VMI_REG_INFO_FN(rl78RegInfo);                  // rl78Registers.c
VMI_EXCEPTION_INFO_FN(rl78ExceptionInfo);      // rl78Utils.c
VMI_MODE_INFO_FN(rl78ModeInfo);                // rl78Utils.c
VMI_GET_EXCEPTION_FN(rl78GetException);        // rl78Utils.c
VMI_GET_MODE_FN(rl78GetMode);                  // rl78Utils.c
VMI_DEBUG_FN(rl78DumpRegisters);               // rl78Utils.c

// PROCESSOR INFO ROUTINE
VMI_PROC_INFO_FN(rl78ProcInfo);                // rl78Info.c

// Imperas intercpted function support
VMI_INT_RETURN_FN(rl78IntReturnCB);            // rl78SemiHost.c
VMI_INT_RESULT_FN(rl78IntResultCB);            // rl78SemiHost.c
VMI_INT_PAR_FN(rl78IntParCB);                  // rl78SemiHost.c

// register access
VMI_MEM_WATCH_FN(rl78ReadReg);                 // rl78Utils.c
VMI_MEM_WATCH_FN(rl78WriteReg);                // rl78Utils.c
VMI_MEM_WATCH_FN(rl78ReadSfr);                 // rl78Utils.c
VMI_MEM_WATCH_FN(rl78WriteSfr);                // rl78Utils.c

void rl78InterruptNext(vmiProcessorP processor);

#endif

