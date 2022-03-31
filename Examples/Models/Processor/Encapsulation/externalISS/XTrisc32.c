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



#include <stdio.h>
#include <stdlib.h>

#include "XTrisc32.h"

typedef struct simStructS {
    struct {
        XT_Reg32 r[8];
        XT_Reg32 pc, sp, status;
    } reg;

    XT_fetchMemFn fetch;
    XT_readMemFn  read;
    XT_writeMemFn write;
    XT_StopReason stopReason;
    XT_Icount     icount;

    void *userdata;

    char tracebuf[1024];
    XT_Bool traceon;
} simStruct, *simStructP;

/*
Instruction Format
[31:24] = Opcode

Reg Format
    [23:16] = rD
    [15:8]  = rA
    [7:0]   = rB

Imm Format
    [23:16] = rD
    [15:0]  = Imm16


movlo rD, Imm16  :: rD[15:0]  = Imm16
movhi rD, Imm16  :: rD[31:16] = Imm16
movr  rD, rA     :: rD = rA
add   rD, rA, rB :: rD = rA + rB;
sub   rD, rA, rB :: rD = rA - rB;
ld    rD, rA     :: rD = mem[rA]
st    rD, rA     :: mem[rD] = rA
jmp   pc, rA     :: pc = rA
beq   rD, rA, rB :: (rA == rB) ? pc = rD
bgt   rD, rA, rB :: (rA > rB)  ? pc = rD
blt   rD, rA, rB :: (rA < rB)  ? pc = rD
halt             ::

*/

// #define TRACE 0

#define MOVLO 0
#define MOVHI 1
#define MOVR  2
#define ADD   3
#define SUB   4
#define LD    5
#define ST    6
#define JMP   7
#define BEQ   8
#define BGT   9
#define BLT   10
#define HALT  11

static void disass (simStructP state) {
    int i;
    printf("%s", state->tracebuf);
    for (i=0; i<=3; i++) printf("r%d=0x%08x ", i, state->reg.r[i]); printf("\n");
    for (i=4; i<=7; i++) printf("r%d=0x%08x ", i, state->reg.r[i]); printf("\n");
    printf("pc=0x%08x sp=0x%08x status=0x%08x\n", state->reg.pc, state->reg.sp, state->reg.status);
}

static int fetchMem (simStructP state, XT_Addr addr) {
    XT_Value value;
    state->fetch(state->userdata, addr, &value, XT_True);
    return value.ivalue;
}

static int readMem (simStructP state, XT_Addr addr) {
    XT_Value value;
    state->read(state->userdata, addr, &value, XT_True);
    return value.ivalue;
}

static void writeMem (simStructP state, XT_Addr addr, XT_Value value) {
    state->write(state->userdata, addr, value, XT_True);
}

static void execute(simStructP state) {

    // Decode instruction
    int insn = fetchMem(state, state->reg.pc);
    int opcode = insn >> 24;
    int rD     = (insn >> 16) & 0xff;
    int rA     = (insn >> 8)  & 0xff;
    int rB     = (insn)       & 0xff;
    int imm16  = (insn)       & 0xffff;

    int r;
    XT_Value value;

    // Assume all is OK
    state->stopReason = XT_OK;

    if(state->traceon) printf("\nINFO %d : 0x%08x ", (int)state->icount, state->reg.pc);
    state->reg.pc += 4;
    switch (opcode) {
        case MOVLO:
            r = state->reg.r[rD];
            state->reg.r[rD] = (r & 0xffff0000) | imm16;
            if(state->traceon) sprintf(state->tracebuf, "movlo r%d, 0x%x\n", rD, imm16);
            break;

        case MOVHI:
            r = state->reg.r[rD];
            state->reg.r[rD] = (r & 0xffff) | (imm16 << 16);
            if(state->traceon) sprintf(state->tracebuf, "movhi r%d, 0x%x\n", rD, imm16);
            break;

        case MOVR:
            state->reg.r[rD] = state->reg.r[rA];
            if(state->traceon) sprintf(state->tracebuf, "movr r%d, r%d\n", rD, rA);
            break;

        case ADD:
            state->reg.r[rD] = state->reg.r[rA] + state->reg.r[rB];
            if(state->traceon) sprintf(state->tracebuf, "add r%d, r%d, r%d\n", rD, rA, rB);
            break;

        case SUB:
            state->reg.r[rD] = state->reg.r[rA] - state->reg.r[rB];
            if(state->traceon) sprintf(state->tracebuf, "sub r%d, r%d, r%d\n", rD, rA, rB);
            break;

        case LD:
            state->reg.r[rD] = readMem(state, state->reg.r[rA]);
            if(state->traceon) sprintf(state->tracebuf, "ld r%d, [r%d]\n", rD, rA);
            break;

        case ST:
            value.ivalue = state->reg.r[rA];
            writeMem(state, state->reg.r[rD], value);
            if(state->traceon) sprintf(state->tracebuf, "st [r%d], r%d", rD, rA);
            break;

        case JMP:
            state->reg.pc = state->reg.r[rA];
            if(state->traceon) sprintf(state->tracebuf, "jmp r%d\n", rA);
            break;

        case HALT:
            if(state->traceon) sprintf(state->tracebuf, "halt\n");
            state->reg.pc -= 4;
            state->stopReason = XT_HALT;
            break;

        case BEQ:
            if(state->traceon) sprintf(state->tracebuf, "beq r%d, r%d, r%d\n", rD, rA, rB);
            if (state->reg.r[rA] == state->reg.r[rB]) {
                state->reg.pc = state->reg.r[rD];
            }
            break;

        case BGT:
            if(state->traceon) sprintf(state->tracebuf, "bgt r%d, r%d, r%d\n", rD, rA, rB);
            if (state->reg.r[rA] > state->reg.r[rB]) {
                state->reg.pc = state->reg.r[rD];
            }
            break;

        case BLT:
            if(state->traceon) sprintf(state->tracebuf, "blt r%d, r%d, r%d\n", rD, rA, rB);
            if (state->reg.r[rA] < state->reg.r[rB]) {
                state->reg.pc = state->reg.r[rD];
            }
            break;

        default:
            if(state->traceon) sprintf(state->tracebuf, "Undecoded Instruction pc=%x\n", state->reg.pc);
            state->stopReason = XT_HALT;
            break;
    }
    if(state->traceon) disass(state);
}

risc32Handle XT_constructor(void *userdata) {
    simStructP state = (simStructP) calloc(1, sizeof(simStruct));
    state->userdata = userdata;

    state->reg.pc = 0x100;
    state->traceon = XT_True;;

    return state;
}

XT_Icount XT_run(risc32Handle handle, XT_Icount maxcount) {
    simStructP state = (simStructP) handle;
    XT_Icount icount;

    for (icount=0; (icount<maxcount) && (state->stopReason == XT_OK); icount++) {
        execute(state);
        state->icount++;
    }

    return (icount);
}

XT_Value XT_readReg(risc32Handle handle, XT_reg id) {
    simStructP state = (simStructP)handle;
    XT_Value value;

    value.ivalue = -1;

    if (id < 8)   value.ivalue = state->reg.r[id];
    if (id == 8)  value.ivalue = state->reg.pc;
    if (id == 9)  value.ivalue = state->reg.sp;
    if (id == 10) value.ivalue = state->reg.status;

    return value;
}

void XT_writeReg(risc32Handle handle, XT_reg id, XT_Value value) {
    simStructP state = (simStructP)handle;
    if (id < 8)   state->reg.r[id]  = value.ivalue;
    if (id == 8)  state->reg.pc     = value.ivalue;
    if (id == 9)  state->reg.sp     = value.ivalue;
    if (id == 10) state->reg.status = value.ivalue;
}

void XT_destructor(risc32Handle handle) {
    simStructP state = (simStructP)handle;
    free(state);
}

void XT_installFetchMemCB(risc32Handle handle, XT_fetchMemFn fetch) {
    simStructP state = (simStructP)handle;
    state->fetch = fetch;
}

void XT_installReadMemCB(risc32Handle handle, XT_readMemFn read) {
    simStructP state = (simStructP)handle;
    state->read = read;
}

void XT_installWriteMemCB(risc32Handle handle, XT_writeMemFn write) {
    simStructP state = (simStructP)handle;
    state->write = write;
}

XT_StopReason XT_getReason(risc32Handle handle) {
    simStructP state = (simStructP)handle;
    return state->stopReason;
}

XT_Icount XT_getIcount(risc32Handle handle) {
    simStructP state = (simStructP)handle;
    return state->icount;
}
