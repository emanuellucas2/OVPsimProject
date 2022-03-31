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

#ifndef V850_EXCEPTIONS_H
#define V850_EXCEPTIONS_H

#include "vmi/vmiDbg.h"

#include "v850TypeRefs.h"
#include "v850Structure.h"

//
// Exception vectors
//
typedef enum ExceptVectorE {
    v850_VECTOR_reset    = 0x00000000,
    v850_VECTOR_nmi0     = 0x00000010,
    v850_VECTOR_nmi1     = 0x00000020,
    v850_VECTOR_nmi2     = 0x00000030,
    v850_VECTOR_fetrap   = 0x00000030,
    v850_VECTOR_trap0    = 0x00000040,
    v850_VECTOR_trap1    = 0x00000050,
    v850_VECTOR_ilgop    = 0x00000060,
    v850_VECTOR_rie      = 0x00000030,
    v850_VECTOR_intp     = 0x00000080,

    rh850_VECTOR_reset   = 0x00000000,
    rh850_VECTOR_syserr  = 0x00000010,
    rh850_VECTOR_fetrap  = 0x00000030,
    rh850_VECTOR_trap0   = 0x00000040,
    rh850_VECTOR_trap1   = 0x00000050,
    rh850_VECTOR_rie     = 0x00000060,
    rh850_VECTOR_fpp     = 0x00000070,
    rh850_VECTOR_fpi     = 0x00000070,
    rh850_VECTOR_ucpop   = 0x00000080,
    rh850_VECTOR_mip     = 0x00000090,
    rh850_VECTOR_mdp     = 0x00000090,
    rh850_VECTOR_pie     = 0x000000A0,
    rh850_VECTOR_debug   = 0x000000B0,
    rh850_VECTOR_mae     = 0x000000C0,
    rh850_VECTOR_fenmi   = 0x000000E0,
    rh850_VECTOR_feint   = 0x000000F0,
    rh850_VECTOR_eiint   = 0x00000100,
    rh850_VECTOR_syscall = 0x00008000,
} ExceptVector;

#define V850_EXCEPTION_VECTOR(_N)  [v850_E_##_N]  = v850_VECTOR_##_N
#define RH850_EXCEPTION_VECTOR(_N) [rh850_E_##_N] = rh850_VECTOR_##_N

static const Uns32 V850_Vectors[v850_E_LAST] = {
    V850_EXCEPTION_VECTOR(reset),
    V850_EXCEPTION_VECTOR(nmi0),
    V850_EXCEPTION_VECTOR(nmi1),
    V850_EXCEPTION_VECTOR(nmi2),
    V850_EXCEPTION_VECTOR(intp),
    V850_EXCEPTION_VECTOR(fetrap),
    V850_EXCEPTION_VECTOR(trap0),
    V850_EXCEPTION_VECTOR(trap1),
    V850_EXCEPTION_VECTOR(ilgop),
    V850_EXCEPTION_VECTOR(rie),
};

static const Uns32 RH850_Vectors[rh850_E_LAST] = {
    RH850_EXCEPTION_VECTOR(reset),
    RH850_EXCEPTION_VECTOR(syserr),
    RH850_EXCEPTION_VECTOR(fetrap),
    RH850_EXCEPTION_VECTOR(trap0),
    RH850_EXCEPTION_VECTOR(trap1),
    RH850_EXCEPTION_VECTOR(rie),
    RH850_EXCEPTION_VECTOR(fpp),
    RH850_EXCEPTION_VECTOR(fpi),
    RH850_EXCEPTION_VECTOR(ucpop),
    RH850_EXCEPTION_VECTOR(mip),
    RH850_EXCEPTION_VECTOR(mdp),
    RH850_EXCEPTION_VECTOR(pie),
    RH850_EXCEPTION_VECTOR(debug),
    RH850_EXCEPTION_VECTOR(mae),
    RH850_EXCEPTION_VECTOR(fenmi),
    RH850_EXCEPTION_VECTOR(feint),
    RH850_EXCEPTION_VECTOR(eiint),
    RH850_EXCEPTION_VECTOR(syscall),
};

typedef enum {
    EXC_TERMINATING,
    EXC_RESUMABLE,
    EXC_PENDING
} v850ExceptionType;

typedef struct v850ExceptionInfoS {
    vmiExceptionInfo  info;     // This must be the first structure member for the iterators to work correctly
    v850ExceptionType type;
} v850ExceptionInfoT, *v850ExceptionInfoP;

DEFINE_CS(v850ExceptionInfo);

#define V850_EXCEPTION_INFO(_T,_N,_OFF,_D)   [v850_E_##_N]  = {{name:#_N, code:(v850_VECTOR_##_N  + _OFF), description:_D}, type:_T}
#define RH850_EXCEPTION_INFO(_T,_N,_OFF,_D)  [rh850_E_##_N] = {{name:#_N, code:(rh850_VECTOR_##_N + _OFF), description:_D}, type:_T}

//
// Table of exception mode descriptors
//
static const v850ExceptionInfoT V850_Exceptions[v850_E_LAST] = {
    V850_EXCEPTION_INFO(EXC_TERMINATING, reset,  0x0, "Reset Signal Exception"),
    V850_EXCEPTION_INFO(EXC_TERMINATING, nmi0,   0x0, "Non Maskable Interrupt(0) Exception"),
    V850_EXCEPTION_INFO(EXC_TERMINATING, nmi1,   0x0, "Non Maskable Interrupt(1) Exception"),
    V850_EXCEPTION_INFO(EXC_TERMINATING, nmi2,   0x0, "Non Maskable Interrupt(2) Exception"),
    V850_EXCEPTION_INFO(EXC_TERMINATING, intp,   0x0, "Maskable Interrupt Exception - Vector value = (0x0000ffff AND intp)"),
    V850_EXCEPTION_INFO(EXC_PENDING,     fetrap, 0x0, "FETRAP Exception"),
    V850_EXCEPTION_INFO(EXC_PENDING,     trap0,  0x0, "TRAP0 Exception"),
    V850_EXCEPTION_INFO(EXC_PENDING,     trap1,  0x0, "TRAP1 Exception"),
    V850_EXCEPTION_INFO(EXC_PENDING,     ilgop,  0x0, "Illegal OPCODE Exception"),
    V850_EXCEPTION_INFO(EXC_PENDING,     rie,    0x0, "Reserved Instruction Exception"),
};

//
// Table of exception mode descriptors
//
static const v850ExceptionInfoT RH850_Exceptions[rh850_E_LAST] = {
    RH850_EXCEPTION_INFO(EXC_TERMINATING, reset,   0x0, "Reset Signal Exception"),
    RH850_EXCEPTION_INFO(EXC_TERMINATING, fenmi,   0x0, "FENMI Interrupt"),
    RH850_EXCEPTION_INFO(EXC_TERMINATING, syserr,  0x0, "System Error"),
    RH850_EXCEPTION_INFO(EXC_TERMINATING, feint,   0x0, "FEINT Interrupt"),
    RH850_EXCEPTION_INFO(EXC_TERMINATING, fpi,     0x2, "FPU Exception (imprecise)"),
    RH850_EXCEPTION_INFO(EXC_TERMINATING, eiint,   0x0, "EIINT Interrupt"),
    RH850_EXCEPTION_INFO(EXC_RESUMABLE,   mip,     0x0, "Memory Protection Exception (execution privilege)"),
    RH850_EXCEPTION_INFO(EXC_RESUMABLE,   rie,     0x0, "Reserved Instruction Exception"),
    RH850_EXCEPTION_INFO(EXC_RESUMABLE,   ucpop,   0x0, "Coprocessor Unusable Exception"),
    RH850_EXCEPTION_INFO(EXC_RESUMABLE,   pie,     0x0, "Privileged Instruction Exception"),
    RH850_EXCEPTION_INFO(EXC_RESUMABLE,   mae,     0x0, "Misalignment Exception"),
    RH850_EXCEPTION_INFO(EXC_RESUMABLE,   mdp,     0x1, "Memory Protection Exception (access privilege)"),
    RH850_EXCEPTION_INFO(EXC_RESUMABLE,   fpp,     0x1, "FPU Exception (precise)"),
    RH850_EXCEPTION_INFO(EXC_PENDING,     syscall, 0x0, "System Call"),
    RH850_EXCEPTION_INFO(EXC_PENDING,     fetrap,  0x0, "FE Level Trap"),
    RH850_EXCEPTION_INFO(EXC_PENDING,     trap0,   0x0, "EI Level Trap 0"),
    RH850_EXCEPTION_INFO(EXC_PENDING,     trap1,   0x0, "EI Level Trap 1"),
    RH850_EXCEPTION_INFO(EXC_PENDING,     debug,   0x0, "Debug Exception"),
};

void v850MaskEnable(Uns32 *mask, Bool Enable, Uns32 left, Uns32 right);
void v850ProcessException(vmiProcessorP processor);
Bool v850InterruptPending(v850P v850);
void v850TestInterrupt(v850P v850);

void v850ProcessRESET(v850P v850);
void v850ProcessFENMI(v850P v850);
void v850ProcessSYSERR(v850P v850, Uns32 uimm);
void v850ProcessFEINT(v850P v850);
void v850ProcessFPI(v850P v850);
void v850ProcessEIINT(v850P v850, Uns32 uimm);
void v850ProcessMIP(v850P v850);
void v850ProcessRIE(v850P v850);
void v850ProcessUCPOP(v850P v850, Uns32 uimm);
void v850ProcessPIE(v850P v850);
void v850ProcessMAE(v850P v850);
void v850ProcessMDP(v850P v850);
void v850ProcessFPP(v850P v850);
void v850ProcessSYSCALL(v850P v850);
void v850ProcessFETRAP(v850P v850, Uns32 uimm);
void v850ProcessTRAP0(v850P v850, Uns32 uimm);
void v850ProcessTRAP1(v850P v850, Uns32 uimm);

//
// Modes Set/Get
//
v850Mode v850GetVMMode(v850P v850);
void v850SetVMMode(v850P v850);

//
// Halt the processor for the specified reason if it is running
//
void v850Halt(v850P v850, v850Disable reason);

//
// Restart the processor for the specified reason if it is halted
//
void v850Restart(v850P v850, v850Disable reason);

//
// Return the vector/Code for the given exception
//
Uns32 v850GetExceptionVector(v850P v850, Uns32 exception);
Uns32 v850GetExceptionCode(v850P v850, Uns32 exception);
v850ExceptionType v850GetExceptionType(v850P v850, Uns32 exception);

//
// Handler for MPU Exception
//
void v850MPUMissException(v850P v850, memPriv action, Uns32 VA);

#endif

