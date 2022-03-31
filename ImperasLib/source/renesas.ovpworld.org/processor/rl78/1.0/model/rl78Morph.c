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

// VMI header files
#include "vmi/vmiMt.h"
#include "vmi/vmiRt.h"

// model header files
#include "rl78Decode.h"
#include "rl78Functions.h"
#include "rl78Structure.h"
#include "rl78Utils.h"            // rl78SetPSW_BIT
#include "rl78Message.h"        // MY_ASSERT
#include "rl78Parameters.h"        // enum en_variant



#define UNUSED   __attribute__((unused))

#define    PRE()    \
    UNUSED Uns32    cur = rl78->len_instPrefix + rl78->len_instMnem;    \
    UNUSED Uns32    op1 = 0;    /* operand in instruction bytes */        \
    UNUSED Uns32    op2 = 0;    /* operand in instruction bytes */        \
    UNUSED Uns32    ix1 = 0;    /* bit number of processing */            \
    UNUSED Uns32    dis = 0;    /* displacement */                        \
    UNUSED vmiReg    rg1;        /* register object for processing */    \
    UNUSED vmiReg    rg2;        /* register object for processing */    \
    UNUSED vmiReg    tmp = RL78_TMP;                                        \
    rl78->flagUpdate = en_flag____;                                \
    rl78->bol_setTo4bit = 0;                                    \
    vmiLabelP lbl_skip = vmimtNewLabel();                        \
    doSkip(rl78, lbl_skip)                                        \

#define PST()                                                    \
    MY_ASSERT((cur == rl78->len_instByte), "PST");                \
    vmimtInsertLabel(lbl_skip);


#define IMM1(opx)        /* 1 means 1 byte fetch */                \
    MY_ASSERT((cur < rl78->len_instByte), "IMM1");                \
    opx = instr[cur];                                            \
    cur += 1;

#define IMM2(opx)        /* 2 means 2 bytes fetch */                \
    MY_ASSERT(((cur + 1) < rl78->len_instByte), "IMM2");        \
    opx = instr[cur] + (instr[cur + 1] << 8);                    \
    cur += 2;

#define IMM3(opx)        /* 3 means 3 bytes fetch */                \
    MY_ASSERT(((cur + 2) < rl78->len_instByte), "IMM3");        \
    opx = instr[cur] + (instr[cur + 1] << 8) + (instr[cur + 2] << 16);    \
    cur += 3;

#define GETBIT(lsb, len)    ( (instr[cur - 1] >> lsb) & ((1 << len) - 1) )

#define IDX3(idx)        /* 3 means decode 3 bits */            \
    idx = GETBIT(4, 3);

#define IDX4(idx)        /* 4 means decode 4 bits */            \
    idx = GETBIT(4, 4);

#define BIT3(opx)        /* 3 means decode 3 bits */            \
    opx = GETBIT(0, 3);

#define BIT2(opx)        /* 2 means decode 2 bits */            \
    opx = GETBIT(1, 2);

#define BIT(opx, lsb, len)                                        \
    opx = GETBIT(lsb, len);

#define FLG(flg)    \
    rl78->flagUpdate = en_flag_##flg;


static vmiReg reg_read_8(rl78P rl78, Uns32 ireg) {
    vmiReg reg_D = VMI_NOREG;

    if (ireg < 100) {
        reg_D = RL78_REG(8 * rl78->PSW_RBS + ireg);
    } else {
        switch (ireg) {
            case R_ES : reg_D = RL78_ES   ; break;
            case R_CS : reg_D = RL78_CS   ; break;
            case R_PSW: reg_D = RL78_PSW  ; break;
            case R_CY : reg_D = RL78_CARRY; break;
            default: MY_ASSERT(0, "reg_read_8");
        }
    }
    return reg_D;
}

static vmiReg reg_read_16(rl78P rl78, Uns32 ireg) {

    vmiReg reg_D = VMI_NOREG;

    switch (ireg) {
        case R_AX: reg_D = RL78_REG(8 * rl78->PSW_RBS + R_X); break;
        case R_BC: reg_D = RL78_REG(8 * rl78->PSW_RBS + R_C); break;
        case R_DE: reg_D = RL78_REG(8 * rl78->PSW_RBS + R_E); break;
        case R_HL: reg_D = RL78_REG(8 * rl78->PSW_RBS + R_L); break;
        case R_SP: reg_D = RL78_SP; break;
        default: MY_ASSERT(0, "reg_read_16");
    }

    return reg_D;
}

static void reg_write_16(rl78P rl78, Uns32 ireg) {

    // stack pointer is 2-byte aligned
    if(ireg==R_SP) {
        vmimtBinopRC(16, vmi_AND, RL78_SP, 0xfffe, 0);
    }
}

static vmiReg reg_read_32(rl78P rl78, Uns32 ireg) {

    vmiReg reg_D = VMI_NOREG;

    switch (ireg) {
        case R_BCAX: reg_D = RL78_REG(8 * rl78->PSW_RBS + R_X); break;
        case R_HLDE: reg_D = RL78_REG(8 * rl78->PSW_RBS + R_E); break;
        default: MY_ASSERT(0, "reg_read_32");
    }

    return reg_D;
}

static vmiReg reg_read_x8(rl78P rl78, Uns32 ireg) {

    vmiReg reg_D = RL78_THL;

    vmimtMoveExtendRR(16, RL78_THL, 8, reg_read_8(rl78, ireg), False);

    return reg_D;
}

static void prepareTHL(rl78P rl78, Uns32 ra, vmiReg rb) {

    vmimtMoveExtendRR(16, RL78_THL, 8, rb, False);
    vmimtBinopRR(16, vmi_ADD, RL78_THL, reg_read_16(rl78, ra), 0);
}



const vmiFlags flag_A_ = {        // When decision of PSW.AC, only input is applied, output will be ignored.
    RL78_CARRY_CONST,           // offset to carry in flag
    {
        [vmi_CF] = VMI_NOFLAG_CONST,       // offset to carry out flag
        [vmi_PF] = VMI_NOFLAG_CONST,       // parity flag not used
        [vmi_ZF] = VMI_NOFLAG_CONST,       // zero flag not used
        [vmi_SF] = VMI_NOFLAG_CONST,       // sign flag not used
        [vmi_OF] = VMI_NOFLAG_CONST        // offset to overflow flag
    }
};
const vmiFlags flagZ_C = {
    RL78_CARRY_CONST,           // offset to carry in flag
    {
        [vmi_CF] = RL78_CARRY_CONST,       // offset to carry out flag
        [vmi_PF] = VMI_NOFLAG_CONST,       // parity flag not used
        [vmi_ZF] = RL78_ZERO_CONST ,       // zero flag not used
        [vmi_SF] = VMI_NOFLAG_CONST,       // sign flag not used
        [vmi_OF] = VMI_NOFLAG_CONST        // offset to overflow flag
    }
};
const vmiFlags flagZ__ = {
    RL78_CARRY_CONST,           // offset to carry in flag
    {
        [vmi_CF] = VMI_NOFLAG_CONST,       // offset to carry out flag
        [vmi_PF] = VMI_NOFLAG_CONST,       // parity flag not used
        [vmi_ZF] = RL78_ZERO_CONST ,       // zero flag not used
        [vmi_SF] = VMI_NOFLAG_CONST,       // sign flag not used
        [vmi_OF] = VMI_NOFLAG_CONST        // offset to overflow flag
    }
};
const vmiFlags flag__C = {
    RL78_CARRY_CONST,           // offset to carry in flag
    {
        [vmi_CF] = RL78_CARRY_CONST,       // offset to carry out flag
        [vmi_PF] = VMI_NOFLAG_CONST,       // parity flag not used
        [vmi_ZF] = VMI_NOFLAG_CONST,       // zero flag not used
        [vmi_SF] = VMI_NOFLAG_CONST,       // sign flag not used
        [vmi_OF] = VMI_NOFLAG_CONST        // offset to overflow flag
    }
};

const vmiFlags* getFlagset(enum FlagUpdate flagUpdate) {

    const vmiFlags* pflag = 0;

    switch (flagUpdate) {
        case en_flag____: pflag = 0;        break;
        case en_flag_Z__: pflag = &flagZ__; break;
        case en_flag_ZA_: pflag = &flagZ__; break;
        case en_flag___C: pflag = &flag__C; break;
        case en_flag__AC: pflag = &flag__C; break;
        case en_flag_Z_C: pflag = &flagZ_C; break;
        case en_flag_ZAC: pflag = &flagZ_C; break;
        default: MY_ASSERT(0, "getFlagset");
    }
    return pflag;
}




void doMoveRC(rl78P rl78, Uns32 bits, vmiReg rd, Uns32 c) {

    if (rl78->bol_setTo4bit == 1) {
        c = c & 0x0F;
    }

    // rd = c

    vmimtMoveRC(                //void vmimtMoveRC(
        bits,                    //    Uns32  bits,
        rd,                        //    vmiReg rd,
        c);                        //    Uns64  c
}

void doMoveRR(rl78P rl78, Uns32 bits, vmiReg rd, vmiReg ra) {

    if (rl78->bol_setTo4bit == 1) {
        vmimtBinopRRC(bits, vmi_AND, RL78_T4BIT_RA, ra, 0x0F, 0);    // 4bit
        ra = RL78_T4BIT_RA;
    }

    // rd = ra

    vmimtMoveRR(                //void vmimtMoveRR(
        bits,                    //    Uns32  bits,
        rd,                        //    vmiReg rd,
        ra);                    //    vmiReg ra
}


static void doAuxCarryRR(rl78P rl78, Uns32 bits, vmiBinop op, vmiReg rd, vmiReg ra) {

    if (rl78->sim_ac_flag != 0) {

        if (rl78->flagUpdate & 0x010) {

            vmiReg rdT = RL78_T4BIT_RD;
            vmiReg raT = RL78_T4BIT_RA;
            vmiReg rbT = RL78_T4BIT_RB;

            vmimtBinopRRC(bits, vmi_AND, raT, rd, 0x0F, 0);    // 4bit

            if (VMI_REG_EQUAL(rd, ra)) {
                rbT = raT;
            } else {
                vmimtBinopRRC(bits, vmi_AND, rbT, ra, 0x0F, 0);    // 4bit
            }

            vmimtBinopRRR(bits, op, rdT, raT, rbT, &flag_A_);
            vmimtCompareRC(bits, vmi_COND_NB, rdT, 0x10, RL78_AUXCARRY);        // not below (unsigned) : RD >= 0x10
        }
    }
}

static void doAuxCarryRC(rl78P rl78, Uns32 bits, vmiBinop op, vmiReg rd, Uns32 c) {

    if (rl78->sim_ac_flag != 0) {

        if (rl78->flagUpdate & 0x010) {

            vmiReg rdT = RL78_T4BIT_RD;
            vmiReg raT = RL78_T4BIT_RA;

            vmimtBinopRRC(bits, vmi_AND, raT, rd, 0x0F, 0);    // 4bit
            vmimtBinopRRC(bits, op, rdT, raT, c & 0x0F, &flag_A_);
            vmimtCompareRC(bits, vmi_COND_NB, rdT, 0x10, RL78_AUXCARRY);        // not below (unsigned) : RD >= 0x10
        }
    }
}

void doMulopRRR(rl78P rl78, Uns32 bits, vmiBinop op, vmiReg rd, vmiReg ra, vmiReg rb) {

    // PSW.AC flag
    doAuxCarryRR(rl78, bits, op, ra, rb);

    const vmiFlags* pflag = getFlagset(rl78->flagUpdate);

    // rd = ra <mulop> rb
    vmimtMulopRRR(            //void vmimtMulopRRR(
        bits,                    //    Uns32      bits,
        op,                        //    vmiBinop   op,
        VMI_REG_DELTA(rd,1),    //    vmiReg     rdh,
        VMI_REG_DELTA(rd,0),    //    vmiReg     rdl,
        ra,                        //    vmiReg     ra,
        rb,                        //    vmiReg     rb,
        pflag);                    //    vmiFlagsCP flags
}

void doBinopRR(rl78P rl78, Uns32 bits, vmiBinop op, vmiReg rd, vmiReg ra) {

    // PSW.AC flag
    doAuxCarryRR(rl78, bits, op, rd, ra);

    const vmiFlags* pflag = getFlagset(rl78->flagUpdate);

    // rd = rd <binop> ra
    vmimtBinopRR(                //void vmimtBinopRR(
        bits,                    //    Uns32      bits,
        op,                        //    vmiBinop   op,
        rd,                        //    vmiReg     rd,
        ra,                        //    vmiReg     ra,
        pflag);                    //    vmiFlagsCP flags
}

void doBinopRC(rl78P rl78, Uns32 bits, vmiBinop op, vmiReg rd, Uns32 c) {

    // PSW.AC flag
    doAuxCarryRC(rl78, bits, op, rd, c);

    const vmiFlags* pflag = getFlagset(rl78->flagUpdate);

    // rd = rd <binop> c
    vmimtBinopRC(                //void vmimtBinopRC(
        bits,                    //    Uns32      bits,
        op,                        //    vmiBinop   op,
        rd,                        //    vmiReg     rd,
        c,                        //    Uns64      c,
        pflag);                    //    vmiFlagsCP flags
}

void doCompareRR(rl78P rl78, Uns32 bits, vmiReg rd, vmiReg ra) {

    // using vmimtBinopRRR(), instead of vmimtCompareRR()

    // PSW.AC flag
    doAuxCarryRR(rl78, bits, vmi_SUB, rd, ra);

    const vmiFlags* pflag = getFlagset(rl78->flagUpdate);

    // rd = ra <binop> rb
    vmimtBinopRRR(                //void vmimtBinopRRR(
        bits,                    //    Uns32      bits,
        vmi_SUB,                //    vmiBinop   op,
        VMI_NOREG,                //    vmiReg     rd,
        rd,                        //    vmiReg     ra,
        ra,                        //    vmiReg     rb,
        pflag);                    //    vmiFlagsCP flags
}

void doCompareRC(rl78P rl78, Uns32 bits, vmiReg rd, Uns32 c) {

    // using vmimtBinopRRC(), instead of vmimtCompareRC()

    // PSW.AC flag
    doAuxCarryRC(rl78, bits, vmi_SUB, rd, c);

    const vmiFlags* pflag = getFlagset(rl78->flagUpdate);

    // rd = ra <binop> c
    vmimtBinopRRC(                //void vmimtBinopRRC(
        bits,                    //    Uns32      bits,
        vmi_SUB,                //    vmiBinop   op,
        VMI_NOREG,                //    vmiReg     rd,
        rd,                        //    vmiReg     ra,
        c,                        //    Uns64      c,
        pflag);                    //    vmiFlagsCP flags
}

//
// Should ES-extended address be used for load/store operation?
//
inline static Bool useESAddress(rl78P rl78) {
    return rl78->len_instPrefix == 1;
}

//
// Refine address and offset for load or store
//
static vmiReg getLoadStoreAddrRegOffset(rl78P rl78, Uns32 *offsetP, vmiReg ra) {

    if (useESAddress(rl78)) {

        // ES-based address
        *offsetP &= 0xFFFF;
        vmimtMoveRR(16, RL78_ES_ADDR, ra);
        ra = RL78_ES_ADDR;

    } else {

        // 16-bit address, starting at 0xF0000
        *offsetP |= 0xF0000;
    }

    return ra;
}

//
// Refine address and offset depending on whether load/store uses ES-extended
// address
//
static memDomainP getLoadStoreDomainAndOffset(rl78P rl78, Uns32 *offsetP) {

    if(useESAddress(rl78)) {

        // ES-based address: use default data domain
        return 0;

    } else {

        // use 16-bit data domain and mask offset to 16 bits (an additional
        // offset of 0xF0000 is implied by this domain)
        *offsetP &= 0xFFFF;

        return rl78->dataDomain16;
    }
}

//
// If this memory access is actually an access to a memory-mapped GPR, return
// the GPR index, or -1 if it is not such an access
//
static Uns32 getMemMappedRegIndex(rl78P rl78, Uns32 bits, Uns32 offset, vmiReg ra) {

    Uns32 align = bits/8;

    if(VMI_ISNOREG(ra) && (offset>=0xFFEE0) && (offset<=0xFFEFF) && !(offset&(align-1))) {

        offset -= 0xFFEE0;

        Uns32 reg  = offset&7;
        Uns32 bank = 3-(offset/8);

        return (bank*8) + reg;

    } else {

        return -1;
    }
}


void doStoreRRO(rl78P rl78, Uns32 bits, Uns32 offset, vmiReg ra, vmiReg rb) {

    ra = getLoadStoreAddrRegOffset(rl78, &offset, ra);

    Uns32 alias = getMemMappedRegIndex(rl78, bits, offset, ra);

    if(alias!=-1) {

        // implement aligned access to GPR memory alias as register move
        vmimtMoveRR(bits, RL78_REG(alias), rb);

    } else {

        // get target domain and offset
        memDomainP domain = getLoadStoreDomainAndOffset(rl78, &offset);

        // mem[ra+offset] = rb  (when ra!=VMI_NOREG)
        // mem[offset]    = rb  (when ra==VMI_NOREG)

        memConstraint constraint = (bits == 32) ? MEM_CONSTRAINT_NONE : MEM_CONSTRAINT_ALIGNED;

        vmimtStoreRRODomain(            //void vmimtStoreRRODomain(
            domain,                     //    memDomainP    domain,
            bits,                        //    Uns32         bits,
            offset,                        //    Addr          offset,
            ra,                            //    vmiReg        ra,
            rb,                            //    vmiReg        rb,
            MEM_ENDIAN_LITTLE,            //    memEndian     endian,
            constraint);                //    memConstraint constraint        // checked by unit test MOVW_21
    }
}

void doStoreRCO(rl78P rl78, Uns32 bits, Uns32 offset, vmiReg ra, Uns32 c) {

    ra = getLoadStoreAddrRegOffset(rl78, &offset, ra);

    Uns32 alias = getMemMappedRegIndex(rl78, bits, offset, ra);

    if(alias!=-1) {

        // implement aligned access to GPR memory alias as register move
        vmimtMoveRC(bits, RL78_REG(alias), c);

    } else {

        // get target domain and offset
        memDomainP domain = getLoadStoreDomainAndOffset(rl78, &offset);

        // mem[ra+offset] = c  (when ra!=VMI_NOREG)
        // mem[offset]    = c  (when ra==VMI_NOREG)

        memConstraint constraint = (bits == 32) ? MEM_CONSTRAINT_NONE : MEM_CONSTRAINT_ALIGNED;

        vmimtStoreRCODomain(            //void vmimtStoreRCO(
            domain,                     //    memDomainP    domain,
            bits,                        //    Uns32         bits,
            offset,                        //    Addr          offset,
            ra,                            //    vmiReg        ra,
            c,                            //    Uns64         c,
            MEM_ENDIAN_LITTLE,            //    memEndian     endian,
            constraint);                //    memConstraint constraint        // checked by unit test MOVW_21
    }
}

void doLoadRRO(rl78P rl78, Uns32 bits, vmiReg rd, Uns32 offset, vmiReg ra) {

    ra = getLoadStoreAddrRegOffset(rl78, &offset, ra);

    Uns32 alias = getMemMappedRegIndex(rl78, bits, offset, ra);

    if(alias!=-1) {

        // implement aligned access to GPR memory alias as register move
        vmimtMoveRR(bits, rd, RL78_REG(alias));

    } else {

        // get target domain and offset
        memDomainP domain = getLoadStoreDomainAndOffset(rl78, &offset);

        // rd = mem[ra+offset]  (when ra!=VMI_NOREG)
        // rd = mem[offset]     (when ra==VMI_NOREG)

        // The size of the calculated address (and the size in bits of the address register
        // in the processor structure) is the specified with the processor is created (in
        // an OVP platform, this is the addressBits parameter to icmCreateProcessor; in the
        // Imperas Simulator (imperas.exe) product, this is the addresswidth attribute of
        // the DATA busmasterport entity in the XML processor description).

        memConstraint constraint = (bits == 32) ? MEM_CONSTRAINT_NONE : MEM_CONSTRAINT_ALIGNED;

        vmimtLoadRRODomain(                //void vmimtLoadRRO(
            domain,                     //    memDomainP    domain,
            bits,                        //    Uns32         destBits,
            bits,                         //    Uns32         memBits,
            offset,                         //    Addr          offset,
            rd,                            //    vmiReg        rd,
            ra,                            //    vmiReg        ra,
            MEM_ENDIAN_LITTLE,             //    memEndian     endian,
            0,                             //    Bool          signExtend,
            constraint);                //    memConstraint constraint        // checked by unit test MOVW_21
    }
}


void doSwap(Uns32 bits, vmiReg ra, vmiReg rb) {

    vmiReg rt = RL78_SWAP;
    vmimtMoveRR(bits, rt, ra);
    vmimtMoveRR(bits, ra, rb);
    vmimtMoveRR(bits, rb, rt);
}

void doJumpDir(Uns32 addr, vmiJumpHint hint) {

//    vmiMessage("I", "RL78", "doJumpDir: %08x\n", addr);

    vmimtUncondJump(            //void vmimtUncondJump(
        0,                        //    Addr        linkPC,
        addr,                    //    Addr        toAddress,
        VMI_NOREG,                //    vmiReg      linkReg,
        hint);                    //    vmiJumpHint hint
}

void doCallDir(Uns32 addr, Uns32 linkPC) {

//    vmiMessage("I", "RL78", "doCallDir: %08x\n", addr);

    vmimtUncondJump(            //void vmimtUncondJump(
        linkPC,                    //    Addr        linkPC,
        addr,                    //    Addr        toAddress,
        VMI_NOREG,                //    vmiReg      linkReg,
        vmi_JH_CALL);            //    vmiJumpHint hint
}

#define DOJUMPREL(bits, offset, hint)    doJumpRel(rl78, thisPC, bits, offset, hint)
#define DOCALLREL(bits, offset, linkPC)    doCallRel(rl78, thisPC, bits, offset, linkPC)

void doJumpRel(rl78P rl78, Uns32 thisPC, Uns32 bits, Uns32 offset, vmiJumpHint hint) {

    Uns32 addr = 0;

    if (bits == 8) {
        addr = thisPC + rl78->len_instByte + (Int8) offset;        // sign extension
    } else if (bits == 16) {
        addr = thisPC + rl78->len_instByte + (Int16) offset;    // sign extension
    } else {
        MY_ASSERT(0, "doJumpRel");
    }

    MY_MESSAGE(rl78, "I", "doJumpRel: %08x\n", addr);

    vmimtUncondJump(            //void vmimtUncondJump(
        0,                        //    Addr        linkPC,
        addr,                    //    Addr        toAddress,
        VMI_NOREG,                //    vmiReg      linkReg,
        vmi_JH_RELATIVE | hint);    //    vmiJumpHint hint
}

void doCallRel(rl78P rl78, Uns32 thisPC, Uns32 bits, Uns32 offset, Uns32 linkPC) {

    Uns32 addr = 0;

    if (bits == 8) {
        addr = thisPC + rl78->len_instByte + (Int8) offset;        // sign extension
    } else if (bits == 16) {
        addr = thisPC + rl78->len_instByte + (Int16) offset;    // sign extension
    } else {
        MY_ASSERT(0, "doCallRel");
    }

    MY_MESSAGE(rl78, "I", "doCallRel: %08x\n", addr);

    vmimtUncondJump(            //void vmimtUncondJump(
        linkPC,                    //    Addr        linkPC,
        addr,                    //    Addr        toAddress,
        VMI_NOREG,                //    vmiReg      linkReg,
        vmi_JH_RELATIVE | vmi_JH_CALL);//    vmiJumpHint hint
}

void doJumpReg(vmiReg toReg, vmiJumpHint hint) {

    vmimtUncondJumpReg(            //void vmimtUncondJumpReg(
        0,                        //    Addr        linkPC,
        toReg,                    //    vmiReg      toReg,
        VMI_NOREG,                //    vmiReg      linkReg,
        hint);                    //    vmiJumpHint hint
}

void doCallReg(vmiReg toReg, Uns32 linkPC) {

    vmimtUncondJumpReg(            //void vmimtUncondJumpReg(
        linkPC,                    //    Addr        linkPC,
        toReg,                    //    vmiReg      toReg,
        VMI_NOREG,                //    vmiReg      linkReg,
        vmi_JH_CALL);            //    vmiJumpHint hint
}

void doCondJumpRel(rl78P rl78, Uns32 thisPC, Uns32 offset, en_Cond cond) {

    Uns32    addr = thisPC + rl78->len_instByte + (Int8) offset;
    vmiReg    flagReg = VMI_NOREG;
    Bool    jumpIfTrue = False;

    MY_MESSAGE(rl78, "I", "doCondJumpRel: %08x\n", addr);

    switch (cond) {
        case en_Cond_C    : jumpIfTrue = True ; flagReg = RL78_CARRY ; break;
        case en_Cond_Z    : jumpIfTrue = True ; flagReg = RL78_ZERO  ; break;
        case en_Cond_NC   : jumpIfTrue = False; flagReg = RL78_CARRY ; break;
        case en_Cond_NZ   : jumpIfTrue = False; flagReg = RL78_ZERO  ; break;
        case en_Cond_H    : jumpIfTrue = False; flagReg = RL78_BRANCH; break;
        case en_Cond_NH   : jumpIfTrue = True ; flagReg = RL78_BRANCH; break;
        case en_Cond_T    : jumpIfTrue = True ; flagReg = RL78_BRANCH; break;
        case en_Cond_F    : jumpIfTrue = False; flagReg = RL78_BRANCH; break;
        case en_Cond_TCLR : jumpIfTrue = True ; flagReg = RL78_BRANCH; break;
    }

    if ((cond == en_Cond_H) || (cond == en_Cond_NH)) {
        vmimtBinopRRR(                //void vmimtBinopRRR(
            8,                        //    Uns32      bits,
            vmi_OR,                    //    vmiBinop   op,
            RL78_BRANCH,            //    vmiReg     rd,
            RL78_CARRY,                //    vmiReg     ra,
            RL78_ZERO,                //    vmiReg     rb,
            0);                        //    vmiFlagsCP flags
    }

    vmimtCondJump(                //void vmimtCondJump(
        flagReg,                //    vmiReg      flag,   // byte
        jumpIfTrue,                //    Bool        jumpIfTrue,
        0,                        //    Addr        linkPC,
        addr,                    //    Addr        toAddress,
        VMI_NOREG,                //    vmiReg      linkReg,
        vmi_JH_RELATIVE);        //    vmiJumpHint hint
}


void doBitTest(en_Cond cond, vmiReg ra, Uns32 idx) {

    vmimtBinopRRC(                //void vmimtBinopRRC(
        8,                        //    Uns32      bits,
        vmi_AND,                //    vmiBinop   op,
        RL78_BRANCH,            //    vmiReg     rd,    // @@@ it may be not reasonable to set 8 bit value to Bool type.
        ra,                        //    vmiReg     ra,
        (1 << idx),                //    Uns64      c,
        0);                        //    vmiFlagsCP flags

    if (cond == en_Cond_TCLR) {
        vmiLabelP lbl_notset = vmimtNewLabel();

        Uns8 byte = ~(1 << idx);
        vmimtCondJumpLabel(RL78_BRANCH, False, lbl_notset);
        vmimtBinopRC(8, vmi_AND, ra, byte, 0);

        vmimtInsertLabel(lbl_notset);
    }
}


static void doSkip(rl78P rl78, vmiLabelP lbl_skip) {

    en_Cond cond = rl78->skipCondition;

    if (cond != en_Cond_T) {

        vmiReg    flagReg = VMI_NOREG;
        Bool    jumpIfTrue = False;

        switch (cond) {
            case en_Cond_C    : jumpIfTrue = True ; flagReg = RL78_CARRY ; break;
            case en_Cond_Z    : jumpIfTrue = True ; flagReg = RL78_ZERO  ; break;
            case en_Cond_NC   : jumpIfTrue = False; flagReg = RL78_CARRY ; break;
            case en_Cond_NZ   : jumpIfTrue = False; flagReg = RL78_ZERO  ; break;
            case en_Cond_H    : jumpIfTrue = False; flagReg = RL78_BRANCH; break;    // skip if (Z V CY) == 0    // 'V' is logical sum
            case en_Cond_NH   : jumpIfTrue = True ; flagReg = RL78_BRANCH; break;    // skip if (Z V CY) == 1
            default           : VMI_ABORT("Unexpected SKIP condition %u\n", cond);
        }

        if ((cond == en_Cond_H) || (cond == en_Cond_NH)) {
            vmimtBinopRRR(                //void vmimtBinopRRR(
                8,                        //    Uns32      bits,
                vmi_OR,                    //    vmiBinop   op,
                RL78_BRANCH,            //    vmiReg     rd,
                RL78_CARRY,                //    vmiReg     ra,
                RL78_ZERO,                //    vmiReg     rb,
                0);                        //    vmiFlagsCP flags
        }

        vmimtCondJumpLabel(flagReg, jumpIfTrue, lbl_skip);
    }
}


static void badSkip(rl78P rl78) {
    VMI_ABORT("SKIP instruction should have been merged with following instruction");
}


void doMOV1_R_IM(vmiReg rd, Uns32 idx, Uns32 val) {

    Uns8 byte;

    if (val == 0) {        // clr
        byte = ~(1 << idx);
//        vmiMessage("I", "RL78", "vmimtBinopRC: %s:%d:%08x\n", __FILE__, __LINE__, byte);
        vmimtBinopRC(8, vmi_AND, rd, byte, 0);

    } else {            // set
        byte = (1 << idx);
//        vmiMessage("I", "RL78", "vmimtBinopRC: %s:%d:%08x\n", __FILE__, __LINE__, byte);
        vmimtBinopRC(8, vmi_OR, rd, byte, 0);
    }
}

void doMOV1_R_CY(vmiReg rd, Uns32 idx, vmiReg flag) {

    vmiLabelP lbl_set  = vmimtNewLabel();
    vmiLabelP lbl_exit = vmimtNewLabel();

    vmimtCondJumpLabel(flag, True, lbl_set);

    // clr
    Uns8 byte = ~(1 << idx);
    vmimtBinopRC(8, vmi_AND, rd, byte, 0);
    vmimtUncondJumpLabel(lbl_exit);

    // set
    vmimtInsertLabel(lbl_set);
    vmimtBinopRC(8, vmi_OR, rd, (1 << idx), 0);

    // exit
    vmimtInsertLabel(lbl_exit);
}

void doMOV1_CY_R(vmiReg flag, vmiReg rb, Uns32 idx) {

    vmimtBinopRRC(8, vmi_SHR, RL78_TBIT, rb, idx, 0);    // tmp = tmp >> idx
    vmimtBinopRC (8, vmi_AND, RL78_TBIT,     1  , 0);    // tmp = tmp & 1

    vmimtMoveRR(8, flag, RL78_TBIT);
}

void doBinop_CY_R(vmiReg flag, vmiBinop op, vmiReg rb, Uns32 idx) {

    vmimtBinopRRC(8, vmi_SHR, RL78_TBIT, rb, idx, 0);    // tmp = tmp >> idx
    vmimtBinopRC (8, vmi_AND, RL78_TBIT,     1  , 0);    // tmp = tmp & 1

    vmimtBinopRR(8, op, flag, RL78_TBIT, 0);            // Fatal (NMI_UO) 'vmimtBinopRR' unimplemented for bits=1
}


static void doPushReg(rl78P rl78, Uns32 bits, vmiReg ra) {

    vmimtBinopRC(16, vmi_SUB, RL78_SP, 2, 0);            // Fatal (NMI_UO) 'vmimtBinopRC' unimplemented for bits=20

    switch (bits) {
        case 16:
            doStoreRRO(rl78, 16, 0, RL78_SP, ra);
            break;
        case 8:
            vmimtMoveExtendRR(16, RL78_TMP, 8, ra, False);
            vmimtBinopRC(16, vmi_SHL, RL78_TMP, 8, 0);    // PSW must be stored to higher address of 2 byte area.        // checked by unit test PUSH_2
            doStoreRRO(rl78, 16, 0, RL78_SP, RL78_TMP);
            break;
    }
}

static void doPopReg(rl78P rl78, Uns32 bits, vmiReg ra) {

    switch (bits) {
        case 16:
            doLoadRRO(rl78, 16, ra, 0, RL78_SP);
            break;
        case 8:
            doLoadRRO(rl78,  8, ra, 1, RL78_SP);
            break;
    }
    vmimtBinopRC(16, vmi_ADD, RL78_SP, 2, 0);
}

static void doPushPC(rl78P rl78, Uns32 nextPC) {

    vmimtBinopRC(16, vmi_SUB, RL78_SP, 4, 0);

    // In OVP_VMI_Morph_Time_Function_Reference.pdf page.70,
    // >> Argument bits can be any multiple of eight between 8 (i.e. 1 byte) and 1024 (i.e. 128 bytes).
    // However, if bits arg is 24, an error below will happen.
    // >> Internal Abort (ABRT) /home/release/build/20150901.0/Imperas/SimCommon/source/i86/i86Emit.h:588 : Abort reached. invalid class

    doStoreRCO(rl78, 32, 0, RL78_SP, nextPC & 0xfffff);
}

static void doReset() {
    Addr offset = exceptions[RL78_EXCPT_TRP].code;
    vmimtLoadRRO(                //void vmimtLoadRRO(
        16,                        //    Uns32         destBits,
        16,                     //    Uns32         memBits,
        offset,                    //    Addr          offset,
        RL78_TMP,                //    vmiReg        rd,
        VMI_NOREG,                //    vmiReg        ra,
        MEM_ENDIAN_LITTLE,         //    memEndian     endian,
        0,                         //    Bool          signExtend,
        MEM_CONSTRAINT_NONE);    //    memConstraint constraint

    doJumpReg(RL78_TMP, vmi_JH_INT);

    vmimtEndBlock();
}

static Uns32 chkVariant(rl78P rl78, enum en_variant cond, const char* pszMnem) {

    if (rl78->variant < cond) {
//        vmiMessage("W", "RL78", "%s instruction is not supported in this variant. Reset will happen.\n", pszMnem);

        vmimtArgNatAddress((void*) "%s instruction is not supported in this variant. Reset will happen.\n");
        vmimtArgNatAddress((void*) pszMnem);
        vmimtCall((vmiCallFn) vmiPrintf);        // void vmiPrintf(const char *fmt, ...)

        doReset();
        return 1;
    } else {
        return 0;
    }
}
#define CHKVARI(cond, mnem)    if (chkVariant(rl78, en_RL78_##cond, mnem) == 1) { return; }    // return from RL78_DISPATCH_FN()

static void doBRK(rl78P rl78, Uns32 nextPC, vmiReg psw) {                        // specific function for BRK instruction

    // > If a software interrupt request is acknowledged, the contents are saved into the stacks in the order of
    // > - the program status word (PSW),
    // > - then program counter (PC),

    vmimtBinopRC(16, vmi_SUB, RL78_SP, 4, 0);

    doStoreRCO(rl78, 32, 0, RL78_SP, nextPC & 0xfffff);
    doStoreRRO(rl78,  8, 3, RL78_SP, psw);

    // > the IE flag is reset (0),
    vmimtMoveRC(8, RL78_IE, 0);

    // > and the contents of the vector table (0007EH, 0007FH) are loaded into the PC and branched.

    // call vmimtLoadRRO directly, due to not offset 0xF0000 by using doLoadRRO.
    Addr offset = exceptions[RL78_EXCPT_BRK].code;
    vmimtLoadRRO(                //void vmimtLoadRRO(
        16,                        //    Uns32         destBits,
        16,                     //    Uns32         memBits,
        offset,                    //    Addr          offset,
        RL78_TMP,                //    vmiReg        rd,
        VMI_NOREG,                //    vmiReg        ra,
        MEM_ENDIAN_LITTLE,         //    memEndian     endian,
        0,                         //    Bool          signExtend,
        MEM_CONSTRAINT_NONE);    //    memConstraint constraint

    doJumpReg(RL78_TMP, vmi_JH_CALLINT);

    vmimtEndBlock();
}

static void doPopPC(rl78P rl78) {

    doLoadRRO(rl78, 32, RL78_TMP  , 0, RL78_SP);
    vmimtBinopRC(32, vmi_AND, RL78_TMP, 0xFFFFF, 0);

    vmimtBinopRC(16, vmi_ADD, RL78_SP, 4, 0);
}

static void doSetPSW() {
    vmimtArgProcessor();
    vmimtCall((vmiCallFn) rl78SetPSW_BIT);                // Update BIT members from PSW vari.
}

static void doGetPSW(vmiReg rd) {
    vmimtArgProcessor();
    vmimtCallResult((vmiCallFn) rl78GetPSW_REG, 8, rd);    // Update PSW vari from BIT members.
}

static void doRETI(rl78P rl78) {

    doLoadRRO(rl78, 32, RL78_TMP  , 0, RL78_SP);

    vmimtMoveRR(8, RL78_PSW, RL78_TMP_B3);
    doSetPSW();                        // Update BIT members from PSW vari.

    vmimtBinopRC(32, vmi_AND, RL78_TMP, 0xFFFFF, 0);

    vmimtBinopRC(16, vmi_ADD, RL78_SP, 4, 0);

    vmimtArgNatAddress((void*) rl78);
    vmimtCall((vmiCallFn) rl78InterruptNext);        // process pending interrupt.
}
static void doRETB(rl78P rl78) { doRETI(rl78); }

static void doEI(rl78P rl78) {
    vmimtArgNatAddress((void*) rl78);
    vmimtCall((vmiCallFn) rl78InterruptNext);        // process pending interrupt.
}


static void doCMPS(rl78P rl78, vmiReg dst, vmiReg src) {                    // specific function for CMPS instruction

    vmiReg reg_A = reg_read_8(rl78, R_A);

    // PSW.Z, PSW.AC
    doCompareRR(rl78, 8, dst, src);

    // PSW.CY = (PSW.Z == 0) or (A == 0) or (dst == 0)
    vmimtCompareRC(8, vmi_COND_EQ, RL78_ZERO, 0, RL78_CARRY);    // PSW.CY <- (PSW.Z == 0)

    vmimtCompareRC(8, vmi_COND_EQ, reg_A    , 0, RL78_TCMPS);    // (A == 0)
    vmimtBinopRR(8, vmi_OR, RL78_CARRY, RL78_TCMPS, 0);

    vmimtCompareRC(8, vmi_COND_EQ, dst      , 0, RL78_TCMPS);    // (dst == 0)
    vmimtBinopRR(8, vmi_OR, RL78_CARRY, RL78_TCMPS, 0);
}

static void doMOVS(rl78P rl78, Uns32 offset, vmiReg dst, vmiReg src) {        // specific function for MOVS instruction

    vmiReg reg_A = reg_read_8(rl78, R_A);

    // PSW.Z = (src == 0)
    vmimtCompareRC(8, vmi_COND_EQ, src, 0, RL78_ZERO);

    // PSW.CY = (A == 0) or (src == 0)
    vmimtCompareRC(8, vmi_COND_EQ, reg_A    , 0, RL78_CARRY);    // (A == 0)
    vmimtBinopRR(8, vmi_OR, RL78_CARRY, RL78_ZERO, 0);

    doStoreRRO(rl78, 8, offset, dst, src);
}

static void doSEL(rl78P rl78, Uns32 op1) {                                    // specific function for SEL instruction

    if(op1!=rl78->PSW_RBS) {

        vmimtMoveRC(8, RL78_RBS, op1);

        vmimtArgProcessor();
        vmimtArgUns32(op1);
        vmimtCall((vmiCallFn) vmirtSetMode);    // Bool vmirtSetMode(vmiProcessorP processor, Uns32 dictionaryIndex);

        vmimtEndBlock();
    }
}

static void doHALT(rl78P rl78) {                                            // specific function for HALT instruction

    if (rl78->exit_on_halt == 0) {
        vmimtArgProcessor();
        vmimtCall((vmiCallFn) vmirtHalt);

    } else {
        vmimtArgNatAddress((void*) "HALT instruction executed.\n");
        vmimtCall((vmiCallFn) vmiPrintf);        // void vmiPrintf(const char *fmt, ...)

        vmimtArgProcessor();
        vmimtCall((vmiCallFn) dumpRAM);

        vmimtArgProcessor();
        vmimtCall((vmiCallFn) vmirtExit);        // void vmirtExit(vmiProcessorP processor);
    }

    vmimtEndBlock();
}

static void doSTOP(rl78P rl78) {

    vmimtHalt();
}

static void doCALLT(Uns32 op2, Uns32 op1, Uns32 linkPC) {                // specific function for CALLT instruction

    Uns32 tbladr = 0x0080 + (op2 << 4) + (op1 << 1);    // 0080h - 00BEh

    // call vmimtLoadRRO directly, due to not offset 0xF0000 by using doLoadRRO.
    vmimtLoadRRO(                //void vmimtLoadRRO(
        16,                        //    Uns32         destBits,
        16,                     //    Uns32         memBits,
        tbladr,                     //    Addr          offset,
        RL78_TMP,                //    vmiReg        rd,
        VMI_NOREG,                //    vmiReg        ra,
        MEM_ENDIAN_LITTLE,         //    memEndian     endian,
        0,                         //    Bool          signExtend,
        MEM_CONSTRAINT_NONE);    //    memConstraint constraint

    doCallReg(RL78_TMP, linkPC);
}

#if 0
static void doNotImpl() {

    vmimtArgNatAddress((void*) "not implemented.\n");
    vmimtCall((vmiCallFn) vmiPrintf);        // void vmiPrintf(const char *fmt, ...)

    vmimtArgProcessor();
    vmimtCall((vmiCallFn) vmirtExit);        // void vmirtExit(vmiProcessorP processor);
}
#endif


// address adjustment
#define    SADDR(opx)                    IMM1(opx); opx += (opx < 0x20) ? 0xFFF00 : 0xFFE00;        // FFE20h-FFF1Fh
#define    SFR(opx)                    IMM1(opx); opx += 0xFFF00;

// short naming
#define READ_16(ireg)                reg_read_16(rl78, ireg)
#define WRIT_16(ireg)                reg_write_16(rl78, ireg)
#define WRIT_32(ireg)                /* no action */
#define LOAD_A(bits, addr)            doLoadRRO(rl78, bits, tmp, addr, VMI_NOREG);
#define LOAD_R(bits, offset, ra)    doLoadRRO(rl78, bits, tmp, offset, ra);
#define    LOAD_W(bits, op3, rb)        { prepareTHL(rl78, op3, rb); doLoadRRO(rl78, bits, tmp, 0, RL78_THL); }
#define    STOR_A(bits, addr)            doStoreRRO(rl78, bits, addr, VMI_NOREG, tmp);
#define    STOR_R(bits, offset, rd)    doStoreRRO(rl78, bits, offset, rd, tmp);
#define    STOR_W(bits, op3, rb)        { prepareTHL(rl78, op3, rb); doStoreRRO(rl78, bits, 0, RL78_THL, tmp); }
#define ADDR_CS(reg)                { vmimtMoveRR (16, RL78_CS_ADDR, reg); }


// prepare for operand register
#define    PRE_REG_16_16()                rg1 = reg_read_16(rl78, op1); rg2 = reg_read_16(rl78, op2);
#define    PRE_REG_16__8()                rg1 = reg_read_16(rl78, op1); rg2 = reg_read_8 (rl78, op2);
#define    PRE_REG_16_x8()                rg1 = reg_read_16(rl78, op1); rg2 = reg_read_x8(rl78, op2);
#define    PRE_REG_16_no()                rg1 = reg_read_16(rl78, op1); rg2 = VMI_NOREG;
#define    PRE_REG__8_16()                rg1 = reg_read_8 (rl78, op1); rg2 = reg_read_16(rl78, op2); if ((op1 == R_ES) || (op1 == R_CS)) { rl78->bol_setTo4bit = 1; };
#define    PRE_REG_x8_16()                rg1 = reg_read_x8(rl78, op1); rg2 = reg_read_16(rl78, op2); if ((op1 == R_ES) || (op1 == R_CS)) { rl78->bol_setTo4bit = 1; };
#define    PRE_REG__8__8()                rg1 = reg_read_8 (rl78, op1); rg2 = reg_read_8 (rl78, op2); if ((op1 == R_ES) || (op1 == R_CS)) { rl78->bol_setTo4bit = 1; };
#define    PRE_REG_x8__8()                rg1 = reg_read_x8(rl78, op1); rg2 = reg_read_8 (rl78, op2); if ((op1 == R_ES) || (op1 == R_CS)) { rl78->bol_setTo4bit = 1; };
#define    PRE_REG__8_x8()                rg1 = reg_read_8 (rl78, op1); rg2 = reg_read_x8(rl78, op2); if ((op1 == R_ES) || (op1 == R_CS)) { rl78->bol_setTo4bit = 1; };
#define    PRE_REG__8_no()                rg1 = reg_read_8 (rl78, op1); rg2 = VMI_NOREG;              if ((op1 == R_ES) || (op1 == R_CS)) { rl78->bol_setTo4bit = 1; };
#define    PRE_REG_x8_no()                rg1 = reg_read_x8(rl78, op1); rg2 = VMI_NOREG;              if ((op1 == R_ES) || (op1 == R_CS)) { rl78->bol_setTo4bit = 1; };
#define    PRE_REG_no_16()                rg1 = VMI_NOREG;              rg2 = reg_read_16(rl78, op2);
#define    PRE_REG_no__8()                rg1 = VMI_NOREG;              rg2 = reg_read_8 (rl78, op2);
#define    PRE_REG_no_no()                rg1 = VMI_NOREG;              rg2 = VMI_NOREG;
#define    PRE_REG_32_32()                rg1 = reg_read_32(rl78, op1); rg2 = reg_read_32(rl78, op2);


#include "rl78Morph_S3ext.h"


//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wunused-variable"
//#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

// #define RL78_DISPATCH_FN(_NAME) void _NAME( 
//     rl78P rl78,         
//     Uns32 thisPC,       
//     Uns8* instr,        
//     void *userData      
// )
//                                                       | decoding operand                             prepare operand                          upd PSW   do execute                              output                |
static RL78_DISPATCH_FN(rl78Morph_1_00_NOP      ) { PRE();                                                                                       FLG(___);                                                                 PST(); }    // NOP
static RL78_DISPATCH_FN(rl78Morph_1_02_ADDW     ) { PRE();            op1=R_AX ;            IMM2(op2);  PRE_REG_16_no(); LOAD_A(16, op2);        FLG(ZAC); doBinopRR(rl78, 16, vmi_ADD, rg1, tmp); WRIT_16(op1);        PST(); }    // ADDW    AX, !addr16
static RL78_DISPATCH_FN(rl78Morph_1_04_ADDW     ) { PRE();            op1=R_AX ;            IMM2(op2);  PRE_REG_16_no();                         FLG(ZAC); doBinopRC(rl78, 16, vmi_ADD, rg1, op2); WRIT_16(op1);        PST(); }    // ADDW    AX, #word
static RL78_DISPATCH_FN(rl78Morph_1_06_ADDW     ) { PRE();            op1=R_AX ;            SADDR(op2); PRE_REG_16_no(); LOAD_A(16, op2);        FLG(ZAC); doBinopRR(rl78, 16, vmi_ADD, rg1, tmp); WRIT_16(op1);        PST(); }    // ADDW    AX, saddrp
static RL78_DISPATCH_FN(rl78Morph_1_0X_ADDW     ) { PRE();            op1=R_AX ;            BIT2(op2);  PRE_REG_16_16();                         FLG(ZAC); doBinopRR(rl78, 16, vmi_ADD, rg1, rg2); WRIT_16(op1);        PST(); }    // ADDW    AX, ??
static RL78_DISPATCH_FN(rl78Morph_1_08_XCH      ) { PRE();            op1=R_A  ;            op2=R_X  ;  PRE_REG__8__8();                         FLG(___); doSwap(8, rg1, rg2);                                            PST(); }    // XCH     A, X
static RL78_DISPATCH_FN(rl78Morph_1_09_MOV      ) { PRE();            op1=R_A  ; IMM2(dis); op2=R_B  ;  PRE_REG__8_x8(); LOAD_R(8, dis, rg2);    FLG(___); doMoveRR(rl78, 8, rg1, tmp);                                    PST(); }    // MOV     A, word[B]
static RL78_DISPATCH_FN(rl78Morph_1_0A_ADD      ) { PRE();            SADDR(op1);           IMM1(op2);  PRE_REG_no_no(); LOAD_A(8, op1);         FLG(ZAC); doBinopRC(rl78, 8, vmi_ADD, tmp, op2);  STOR_A(8, op1);        PST(); }    // ADD     saddr, #byte
static RL78_DISPATCH_FN(rl78Morph_1_0B_ADD      ) { PRE();            op1=R_A  ;            SADDR(op2); PRE_REG__8_no(); LOAD_A(8, op2);         FLG(ZAC); doBinopRR(rl78, 8, vmi_ADD, rg1, tmp);                          PST(); }    // ADD     A, saddr
static RL78_DISPATCH_FN(rl78Morph_1_0C_ADD      ) { PRE();            op1=R_A  ;            IMM1(op2);  PRE_REG__8_no();                         FLG(ZAC); doBinopRC(rl78, 8, vmi_ADD, rg1, op2);                          PST(); }    // ADD     A, #byte
static RL78_DISPATCH_FN(rl78Morph_1_0D_ADD      ) { PRE();            op1=R_A  ;            op2=R_HL ;  PRE_REG__8_16(); LOAD_R(8,   0, rg2);    FLG(ZAC); doBinopRR(rl78, 8, vmi_ADD, rg1, tmp);                          PST(); }    // ADD     A, [HL]
static RL78_DISPATCH_FN(rl78Morph_1_0E_ADD      ) { PRE();            op1=R_A  ; IMM1(dis); op2=R_HL ;  PRE_REG__8_16(); LOAD_R(8, dis, rg2);    FLG(ZAC); doBinopRR(rl78, 8, vmi_ADD, rg1, tmp);                          PST(); }    // ADD     A, [HL+byte]
static RL78_DISPATCH_FN(rl78Morph_1_0F_ADD      ) { PRE();            op1=R_A  ;            IMM2(op2);  PRE_REG__8_no(); LOAD_A(8, op2);         FLG(ZAC); doBinopRR(rl78, 8, vmi_ADD, rg1, tmp);                          PST(); }    // ADD     A, !addr16
static RL78_DISPATCH_FN(rl78Morph_1_10_ADDW     ) { PRE();            op1=R_SP ;            IMM1(op2);  PRE_REG_16_no();                         FLG(___); doBinopRC(rl78, 16, vmi_ADD, rg1, op2); /* NO flg update */    PST(); }    // ADDW    SP, #byte
static RL78_DISPATCH_FN(rl78Morph_1_11_PREFIX   ) { PRE();                                                                                                                                                                 PST(); }    // PREFIX
static RL78_DISPATCH_FN(rl78Morph_1_1X_MOVW     ) { PRE();            BIT2(op1);            op2=R_AX ;  PRE_REG_16_16();                         FLG(___); doMoveRR(rl78, 16, rg1, rg2);           WRIT_16(op1);        PST(); }    // MOVW    ??, AX
static RL78_DISPATCH_FN(rl78Morph_1_1Y_MOVW     ) { PRE();            op1=R_AX ;            BIT2(op2);  PRE_REG_16_16();                         FLG(___); doMoveRR(rl78, 16, rg1, rg2);           WRIT_16(op1);        PST(); }    // MOVW    AX, ??
static RL78_DISPATCH_FN(rl78Morph_1_18_MOV      ) { PRE(); IMM2(dis); op1=R_B  ;            op2=R_A  ;  PRE_REG_x8__8();                         FLG(___); doStoreRRO(rl78, 8, dis, rg1, rg2);                             PST(); }    // MOV     word[B], A
static RL78_DISPATCH_FN(rl78Morph_1_19_MOV      ) { PRE(); IMM2(dis); op1=R_B  ;            IMM1(op2);  PRE_REG_x8_no();                         FLG(___); doStoreRCO(rl78, 8, dis, rg1, op2);                             PST(); }    // MOV     word[B], #byte
static RL78_DISPATCH_FN(rl78Morph_1_1A_ADDC     ) { PRE();            SADDR(op1);           IMM1(op2);  PRE_REG_no_no(); LOAD_A(8, op1);         FLG(ZAC); doBinopRC(rl78, 8, vmi_ADC, tmp, op2);  STOR_A(8, op1);        PST(); }    // ADDC    saddr, #byte
static RL78_DISPATCH_FN(rl78Morph_1_1B_ADDC     ) { PRE();            op1=R_A  ;            SADDR(op2); PRE_REG__8_no(); LOAD_A(8, op2);         FLG(ZAC); doBinopRR(rl78, 8, vmi_ADC, rg1, tmp);                          PST(); }    // ADDC    A, saddr
static RL78_DISPATCH_FN(rl78Morph_1_1C_ADDC     ) { PRE();            op1=R_A  ;            IMM1(op2);  PRE_REG__8_no();                         FLG(ZAC); doBinopRC(rl78, 8, vmi_ADC, rg1, op2);                          PST(); }    // ADDC    A, #byte
static RL78_DISPATCH_FN(rl78Morph_1_1D_ADDC     ) { PRE();            op1=R_A  ;            op2=R_HL ;  PRE_REG__8_16(); LOAD_R(8,   0, rg2);    FLG(ZAC); doBinopRR(rl78, 8, vmi_ADC, rg1, tmp);                          PST(); }    // ADDC    A, [HL]
static RL78_DISPATCH_FN(rl78Morph_1_1E_ADDC     ) { PRE();            op1=R_A  ; IMM1(dis); op2=R_HL ;  PRE_REG__8_16(); LOAD_R(8, dis, rg2);    FLG(ZAC); doBinopRR(rl78, 8, vmi_ADC, rg1, tmp);                          PST(); }    // ADDC    A, [HL+byte]
static RL78_DISPATCH_FN(rl78Morph_1_1F_ADDC     ) { PRE();            op1=R_A  ;            IMM2(op2);  PRE_REG__8_no(); LOAD_A(8, op2);         FLG(ZAC); doBinopRR(rl78, 8, vmi_ADC, rg1, tmp);                          PST(); }    // ADDC    A, !addr16
static RL78_DISPATCH_FN(rl78Morph_1_20_SUBW     ) { PRE();            op1=R_SP ;            IMM1(op2);  PRE_REG_16_no();                         FLG(___); doBinopRC(rl78, 16, vmi_SUB, rg1, op2); /* NO flg update */    PST(); }    // SUBW    SP, #byte
static RL78_DISPATCH_FN(rl78Morph_1_22_SUBW     ) { PRE();            op1=R_AX ;            IMM2(op2);  PRE_REG_16_no(); LOAD_A(16, op2);        FLG(ZAC); doBinopRR(rl78, 16, vmi_SUB, rg1, tmp); WRIT_16(op1);        PST(); }    // SUBW    AX, !addr16
static RL78_DISPATCH_FN(rl78Morph_1_24_SUBW     ) { PRE();            op1=R_AX ;            IMM2(op2);  PRE_REG_16_no();                         FLG(ZAC); doBinopRC(rl78, 16, vmi_SUB, rg1, op2); WRIT_16(op1);        PST(); }    // SUBW    AX, #word
static RL78_DISPATCH_FN(rl78Morph_1_26_SUBW     ) { PRE();            op1=R_AX ;            SADDR(op2); PRE_REG_16_no(); LOAD_A(16, op2);        FLG(ZAC); doBinopRR(rl78, 16, vmi_SUB, rg1, tmp); WRIT_16(op1);        PST(); }    // SUBW    AX, saddrp
static RL78_DISPATCH_FN(rl78Morph_1_2X_SUBW     ) { PRE();            op1=R_AX ;            BIT2(op2);  PRE_REG_16_16();                         FLG(ZAC); doBinopRR(rl78, 16, vmi_SUB, rg1, rg2); WRIT_16(op1);        PST(); }    // SUBW    AX, ??                // 0x21 'SUBW AX,AX'�͖���`����
static RL78_DISPATCH_FN(rl78Morph_1_28_MOV      ) { PRE(); IMM2(dis); op1=R_C  ;            op2=R_A  ;  PRE_REG_x8__8();                         FLG(___); doStoreRRO(rl78, 8, dis, rg1, rg2);                             PST(); }    // MOV     word[C] ,A
static RL78_DISPATCH_FN(rl78Morph_1_29_MOV      ) { PRE();            op1=R_A  ; IMM2(dis); op2=R_C  ;  PRE_REG__8_x8(); LOAD_R(8, dis, rg2);    FLG(___); doMoveRR(rl78, 8, rg1, tmp);                                    PST(); }    // MOV     A, word[C]
static RL78_DISPATCH_FN(rl78Morph_1_2A_SUB      ) { PRE();            SADDR(op1);           IMM1(op2);  PRE_REG_no_no(); LOAD_A(8, op1);         FLG(ZAC); doBinopRC(rl78, 8, vmi_SUB, tmp, op2);  STOR_A(8, op1);        PST(); }    // SUB     saddr, #byte
static RL78_DISPATCH_FN(rl78Morph_1_2B_SUB      ) { PRE();            op1=R_A  ;            SADDR(op2); PRE_REG__8_no(); LOAD_A(8, op2);         FLG(ZAC); doBinopRR(rl78, 8, vmi_SUB, rg1, tmp);                          PST(); }    // SUB     A, saddr
static RL78_DISPATCH_FN(rl78Morph_1_2C_SUB      ) { PRE();            op1=R_A  ;            IMM1(op2);  PRE_REG__8_no();                         FLG(ZAC); doBinopRC(rl78, 8, vmi_SUB, rg1, op2);                          PST(); }    // SUB     A, #byte
static RL78_DISPATCH_FN(rl78Morph_1_2D_SUB      ) { PRE();            op1=R_A  ;            op2=R_HL ;  PRE_REG__8_16(); LOAD_R(8,   0, rg2);    FLG(ZAC); doBinopRR(rl78, 8, vmi_SUB, rg1, tmp);                          PST(); }    // SUB     A, [HL]
static RL78_DISPATCH_FN(rl78Morph_1_2E_SUB      ) { PRE();            op1=R_A  ; IMM1(dis); op2=R_HL ;  PRE_REG__8_16(); LOAD_R(8, dis, rg2);    FLG(ZAC); doBinopRR(rl78, 8, vmi_SUB, rg1, tmp);                          PST(); }    // SUB     A, [HL+byte]
static RL78_DISPATCH_FN(rl78Morph_1_2F_SUB      ) { PRE();            op1=R_A  ;            IMM2(op2);  PRE_REG__8_no(); LOAD_A(8, op2);         FLG(ZAC); doBinopRR(rl78, 8, vmi_SUB, rg1, tmp);                          PST(); }    // SUB     A, !addr16
static RL78_DISPATCH_FN(rl78Morph_1_31_4thmap   ) { PRE();                                                                                                                                                                 PST(); }    // 4thmap
static RL78_DISPATCH_FN(rl78Morph_1_3X_XCHW     ) { PRE();            op1=R_AX ;            BIT2(op2);  PRE_REG_16_16();                         FLG(___); doSwap(16, rg1, rg2);     WRIT_16(op1); WRIT_16(op2);        PST(); }    // XCHW    AX, ??
static RL78_DISPATCH_FN(rl78Morph_1_3Y_MOVW     ) { PRE();            BIT2(op1);            IMM2(op2);  PRE_REG_16_no();                         FLG(___); doMoveRC(rl78, 16, rg1, op2);           WRIT_16(op1);        PST(); }    // MOVW    ??, #word
static RL78_DISPATCH_FN(rl78Morph_1_38_MOV      ) { PRE(); IMM2(dis); op1=R_C  ;            IMM1(op2);  PRE_REG_x8_no();                         FLG(___); doStoreRCO(rl78, 8, dis, rg1, op2);                             PST(); }    // MOV     word[C], #byte
static RL78_DISPATCH_FN(rl78Morph_1_39_MOV      ) { PRE(); IMM2(dis); op1=R_BC ;            IMM1(op2);  PRE_REG_16_no();                         FLG(___); doStoreRCO(rl78, 8, dis, rg1, op2);                             PST(); }    // MOV     word[BC], #byte
static RL78_DISPATCH_FN(rl78Morph_1_3A_SUBC     ) { PRE();            SADDR(op1);           IMM1(op2);  PRE_REG_no_no(); LOAD_A(8, op1);         FLG(ZAC); doBinopRC(rl78, 8, vmi_SBB, tmp, op2);  STOR_A(8, op1);        PST(); }    // SUBC    saddr, #byte            //d <- a - b - C
static RL78_DISPATCH_FN(rl78Morph_1_3B_SUBC     ) { PRE();            op1=R_A  ;            SADDR(op2); PRE_REG__8_no(); LOAD_A(8, op2);         FLG(ZAC); doBinopRR(rl78, 8, vmi_SBB, rg1, tmp);                          PST(); }    // SUBC    A, saddr
static RL78_DISPATCH_FN(rl78Morph_1_3C_SUBC     ) { PRE();            op1=R_A  ;            IMM1(op2);  PRE_REG__8_no();                         FLG(ZAC); doBinopRC(rl78, 8, vmi_SBB, rg1, op2);                          PST(); }    // SUBC    A, #byte
static RL78_DISPATCH_FN(rl78Morph_1_3D_SUBC     ) { PRE();            op1=R_A  ;            op2=R_HL ;  PRE_REG__8_16(); LOAD_R(8,   0, rg2);    FLG(ZAC); doBinopRR(rl78, 8, vmi_SBB, rg1, tmp);                          PST(); }    // SUBC    A, [HL]
static RL78_DISPATCH_FN(rl78Morph_1_3E_SUBC     ) { PRE();            op1=R_A  ; IMM1(dis); op2=R_HL ;  PRE_REG__8_16(); LOAD_R(8, dis, rg2);    FLG(ZAC); doBinopRR(rl78, 8, vmi_SBB, rg1, tmp);                          PST(); }    // SUBC    A, [HL+byte]
static RL78_DISPATCH_FN(rl78Morph_1_3F_SUBC     ) { PRE();            op1=R_A  ;            IMM2(op2);  PRE_REG__8_no(); LOAD_A(8, op2);         FLG(ZAC); doBinopRR(rl78, 8, vmi_SBB, rg1, tmp);                          PST(); }    // SUBC    A, !addr16
static RL78_DISPATCH_FN(rl78Morph_1_40_CMP      ) { PRE();            IMM2(op1);            IMM1(op2);  PRE_REG_no_no(); LOAD_A(8, op1);         FLG(ZAC); doCompareRC(rl78, 8, tmp, op2);                                 PST(); }    // CMP     !addr16, #byte
static RL78_DISPATCH_FN(rl78Morph_1_41_MOV      ) { PRE();            op1=R_ES ;            IMM1(op2);  PRE_REG__8_no();                         FLG(___); doMoveRC(rl78, 16, rg1, op2);                                   PST(); }    // MOV     ES, #byte
static RL78_DISPATCH_FN(rl78Morph_1_42_CMPW     ) { PRE();            op1=R_AX ;            IMM2(op2);  PRE_REG_16_no(); LOAD_A(16, op2);        FLG(ZAC); doCompareRR(rl78, 16, rg1, tmp);                                PST(); }    // CMPW    AX, !addr16
static RL78_DISPATCH_FN(rl78Morph_1_44_CMPW     ) { PRE();            op1=R_AX ;            IMM2(op2);  PRE_REG_16_no();                         FLG(ZAC); doCompareRC(rl78, 16, rg1, op2);                                PST(); }    // CMPW    AX, #word
static RL78_DISPATCH_FN(rl78Morph_1_46_CMPW     ) { PRE();            op1=R_AX ;            SADDR(op2); PRE_REG_16_no(); LOAD_A(16, op2);        FLG(ZAC); doCompareRR(rl78, 16, rg1, tmp);                                PST(); }    // CMPW    AX, saddrp
static RL78_DISPATCH_FN(rl78Morph_1_4X_CMPW     ) { PRE();            op1=R_AX ;            BIT2(op2);  PRE_REG_16_16();                         FLG(ZAC); doCompareRR(rl78, 16, rg1, rg2);                                PST(); }    // CMPW    AX, ??
static RL78_DISPATCH_FN(rl78Morph_1_48_MOV      ) { PRE(); IMM2(dis); op1=R_BC ;            op2=R_A  ;  PRE_REG_16__8();                         FLG(___); doStoreRRO(rl78, 8, dis, rg1, rg2);                             PST(); }    // MOV     word[BC], A
static RL78_DISPATCH_FN(rl78Morph_1_49_MOV      ) { PRE();            op1=R_A  ; IMM2(dis); op2=R_BC ;  PRE_REG__8_16(); LOAD_R(8, dis, rg2);    FLG(___); doMoveRR(rl78, 8, rg1, tmp);                                    PST(); }    // MOV     A, word[BC]
static RL78_DISPATCH_FN(rl78Morph_1_4A_CMP      ) { PRE();            SADDR(op1);           IMM1(op2);  PRE_REG_no_no(); LOAD_A(8, op1);         FLG(ZAC); doCompareRC(rl78, 8, tmp, op2);                                 PST(); }    // CMP     saddr, #byte
static RL78_DISPATCH_FN(rl78Morph_1_4B_CMP      ) { PRE();            op1=R_A  ;            SADDR(op2); PRE_REG__8_no(); LOAD_A(8, op2);         FLG(ZAC); doCompareRR(rl78, 8, rg1, tmp);                                 PST(); }    // CMP     A, saddr
static RL78_DISPATCH_FN(rl78Morph_1_4C_CMP      ) { PRE();            op1=R_A  ;            IMM1(op2);  PRE_REG__8_no();                         FLG(ZAC); doCompareRC(rl78, 8, rg1, op2);                                 PST(); }    // CMP     A, #byte
static RL78_DISPATCH_FN(rl78Morph_1_4D_CMP      ) { PRE();            op1=R_A  ;            op2=R_HL ;  PRE_REG__8_16(); LOAD_R(8,   0, rg2);    FLG(ZAC); doCompareRR(rl78, 8, rg1, tmp);                                 PST(); }    // CMP     A, [HL]
static RL78_DISPATCH_FN(rl78Morph_1_4E_CMP      ) { PRE();            op1=R_A  ; IMM1(dis); op2=R_HL ;  PRE_REG__8_16(); LOAD_R(8, dis, rg2);    FLG(ZAC); doCompareRR(rl78, 8, rg1, tmp);                                 PST(); }    // CMP     A, [HL+byte]
static RL78_DISPATCH_FN(rl78Morph_1_4F_CMP      ) { PRE();            op1=R_A  ;            IMM2(op2);  PRE_REG__8_no(); LOAD_A(8, op2);         FLG(ZAC); doCompareRR(rl78, 8, rg1, tmp);                                 PST(); }    // CMP     A, !addr16
static RL78_DISPATCH_FN(rl78Morph_1_5X_MOV      ) { PRE();            BIT3(op1);            IMM1(op2);  PRE_REG__8_no();                         FLG(___); doMoveRC(rl78, 8, rg1, op2);                                    PST(); }    // MOV     ?, #byte
static RL78_DISPATCH_FN(rl78Morph_1_58_MOVW     ) { PRE(); IMM2(dis); op1=R_B  ;            op2=R_AX ;  PRE_REG_x8_16();                         FLG(___); doStoreRRO(rl78, 16, dis, rg1, rg2);                            PST(); }    // MOVW    word[B], AX
static RL78_DISPATCH_FN(rl78Morph_1_59_MOVW     ) { PRE();            op1=R_AX ; IMM2(dis); op2=R_B  ;  PRE_REG_16_x8(); LOAD_R(16, dis, rg2);   FLG(___); doMoveRR(rl78, 16, rg1, tmp);           WRIT_16(op1);        PST(); }    // MOVW    AX, word[B]
static RL78_DISPATCH_FN(rl78Morph_1_5A_AND      ) { PRE();            SADDR(op1);           IMM1(op2);  PRE_REG_no_no(); LOAD_A(8, op1);         FLG(Z__); doBinopRC(rl78, 8, vmi_AND, tmp, op2);  STOR_A(8, op1);        PST(); }    // AND     saddr, #byte
static RL78_DISPATCH_FN(rl78Morph_1_5B_AND      ) { PRE();            op1=R_A  ;            SADDR(op2); PRE_REG__8_no(); LOAD_A(8, op2);         FLG(Z__); doBinopRR(rl78, 8, vmi_AND, rg1, tmp);                          PST(); }    // AND     A, saddr
static RL78_DISPATCH_FN(rl78Morph_1_5C_AND      ) { PRE();            op1=R_A  ;            IMM1(op2);  PRE_REG__8_no();                         FLG(Z__); doBinopRC(rl78, 8, vmi_AND, rg1, op2);                          PST(); }    // AND     A, #byte
static RL78_DISPATCH_FN(rl78Morph_1_5D_AND      ) { PRE();            op1=R_A  ;            op2=R_HL ;  PRE_REG__8_16(); LOAD_R(8,   0, rg2);    FLG(Z__); doBinopRR(rl78, 8, vmi_AND, rg1, tmp);                          PST(); }    // AND     A, [HL]
static RL78_DISPATCH_FN(rl78Morph_1_5E_AND      ) { PRE();            op1=R_A  ; IMM1(dis); op2=R_HL ;  PRE_REG__8_16(); LOAD_R(8, dis, rg2);    FLG(Z__); doBinopRR(rl78, 8, vmi_AND, rg1, tmp);                          PST(); }    // AND     A, [HL+byte]
static RL78_DISPATCH_FN(rl78Morph_1_5F_AND      ) { PRE();            op1=R_A  ;            IMM2(op2);  PRE_REG__8_no(); LOAD_A(8, op2);         FLG(Z__); doBinopRR(rl78, 8, vmi_AND, rg1, tmp);                          PST(); }    // AND     A, !addr16
static RL78_DISPATCH_FN(rl78Morph_1_61_2ndmap   ) { PRE();                                                                                                                                                                 PST(); }    // 2ndmap
static RL78_DISPATCH_FN(rl78Morph_1_6X_MOV      ) { PRE();            op1=R_A  ;            BIT3(op2);  PRE_REG__8__8();                         FLG(___); doMoveRR(rl78, 8, rg1, rg2);                                    PST(); }    // MOV     A, ?
static RL78_DISPATCH_FN(rl78Morph_1_68_MOVW     ) { PRE(); IMM2(dis); op1=R_C  ;            op2=R_AX ;  PRE_REG_x8_16();                         FLG(___); doStoreRRO(rl78, 16, dis, rg1, rg2);                            PST(); }    // MOVW    word[C], AX
static RL78_DISPATCH_FN(rl78Morph_1_69_MOVW     ) { PRE();            op1=R_AX ; IMM2(dis); op2=R_C  ;  PRE_REG_16_x8(); LOAD_R(16, dis, rg2);   FLG(___); doMoveRR(rl78, 16, rg1, tmp);           WRIT_16(op1);        PST(); }    // MOVW    AX, word[C]
static RL78_DISPATCH_FN(rl78Morph_1_6A_OR       ) { PRE();            SADDR(op1);           IMM1(op2);  PRE_REG_no_no(); LOAD_A(8, op1);         FLG(Z__); doBinopRC(rl78, 8, vmi_OR , tmp, op2);  STOR_A(8, op1);        PST(); }    // OR      saddr, #byte
static RL78_DISPATCH_FN(rl78Morph_1_6B_OR       ) { PRE();            op1=R_A  ;            SADDR(op2); PRE_REG__8_no(); LOAD_A(8, op2);         FLG(Z__); doBinopRR(rl78, 8, vmi_OR , rg1, tmp);                          PST(); }    // OR      A, saddr
static RL78_DISPATCH_FN(rl78Morph_1_6C_OR       ) { PRE();            op1=R_A  ;            IMM1(op2);  PRE_REG__8_no();                         FLG(Z__); doBinopRC(rl78, 8, vmi_OR , rg1, op2);                          PST(); }    // OR      A, #byte
static RL78_DISPATCH_FN(rl78Morph_1_6D_OR       ) { PRE();            op1=R_A  ;            op2=R_HL ;  PRE_REG__8_16(); LOAD_R(8,   0, rg2);    FLG(Z__); doBinopRR(rl78, 8, vmi_OR , rg1, tmp);                          PST(); }    // OR      A, [HL]
static RL78_DISPATCH_FN(rl78Morph_1_6E_OR       ) { PRE();            op1=R_A  ; IMM1(dis); op2=R_HL ;  PRE_REG__8_16(); LOAD_R(8, dis, rg2);    FLG(Z__); doBinopRR(rl78, 8, vmi_OR , rg1, tmp);                          PST(); }    // OR      A, [HL+byte]
static RL78_DISPATCH_FN(rl78Morph_1_6F_OR       ) { PRE();            op1=R_A  ;            IMM2(op2);  PRE_REG__8_no(); LOAD_A(8, op2);         FLG(Z__); doBinopRR(rl78, 8, vmi_OR , rg1, tmp);                          PST(); }    // OR      A, !addr16
static RL78_DISPATCH_FN(rl78Morph_1_71_3rdmap   ) { PRE();                                                                                                                                                                 PST(); }    // 3rdmap
static RL78_DISPATCH_FN(rl78Morph_1_7X_MOV      ) { PRE();            BIT3(op1);            op2=R_A  ;  PRE_REG__8__8();                         FLG(___); doMoveRR(rl78, 8, rg1, rg2);                                    PST(); }    // MOV     ?, A
static RL78_DISPATCH_FN(rl78Morph_1_78_MOVW     ) { PRE(); IMM2(dis); op1=R_BC ;            op2=R_AX ;  PRE_REG_16_16();                         FLG(___); doStoreRRO(rl78, 16, dis, rg1, rg2);                            PST(); }    // MOVW    word[BC], AX
static RL78_DISPATCH_FN(rl78Morph_1_79_MOVW     ) { PRE();            op1=R_AX ; IMM2(dis); op2=R_BC ;  PRE_REG_16_16(); LOAD_R(16, dis, rg2);   FLG(___); doMoveRR(rl78, 16, rg1, tmp);           WRIT_16(op1);        PST(); }    // MOVW    AX, word[BC]
static RL78_DISPATCH_FN(rl78Morph_1_7A_XOR      ) { PRE();            SADDR(op1);           IMM1(op2);  PRE_REG_no_no(); LOAD_A(8, op1);         FLG(Z__); doBinopRC(rl78, 8, vmi_XOR, tmp, op2);  STOR_A(8, op1);        PST(); }    // XOR     saddr, #byte
static RL78_DISPATCH_FN(rl78Morph_1_7B_XOR      ) { PRE();            op1=R_A  ;            SADDR(op2); PRE_REG__8_no(); LOAD_A(8, op2);         FLG(Z__); doBinopRR(rl78, 8, vmi_XOR, rg1, tmp);                          PST(); }    // XOR     A, saddr
static RL78_DISPATCH_FN(rl78Morph_1_7C_XOR      ) { PRE();            op1=R_A  ;            IMM1(op2);  PRE_REG__8_no();                         FLG(Z__); doBinopRC(rl78, 8, vmi_XOR, rg1, op2);                          PST(); }    // XOR     A, #byte
static RL78_DISPATCH_FN(rl78Morph_1_7D_XOR      ) { PRE();            op1=R_A  ;            op2=R_HL ;  PRE_REG__8_16(); LOAD_R(8,   0, rg2);    FLG(Z__); doBinopRR(rl78, 8, vmi_XOR, rg1, tmp);                          PST(); }    // XOR     A, [HL]
static RL78_DISPATCH_FN(rl78Morph_1_7E_XOR      ) { PRE();            op1=R_A  ; IMM1(dis); op2=R_HL ;  PRE_REG__8_16(); LOAD_R(8, dis, rg2);    FLG(Z__); doBinopRR(rl78, 8, vmi_XOR, rg1, tmp);                          PST(); }    // XOR     A, [HL+byte]
static RL78_DISPATCH_FN(rl78Morph_1_7F_XOR      ) { PRE();            op1=R_A  ;            IMM2(op2);  PRE_REG__8_no(); LOAD_A(8, op2);         FLG(Z__); doBinopRR(rl78, 8, vmi_XOR, rg1, tmp);                          PST(); }    // XOR     A, !addr16
static RL78_DISPATCH_FN(rl78Morph_1_8X_INC      ) { PRE();            BIT3(op1);                        PRE_REG__8_no();                         FLG(ZA_); doBinopRC(rl78, 8, vmi_ADD, rg1, 1);                            PST(); }    // INC     ?
static RL78_DISPATCH_FN(rl78Morph_1_88_MOV      ) { PRE();            op1=R_A  ; IMM1(dis); op2=R_SP ;  PRE_REG__8_16(); LOAD_R(8, dis, rg2);    FLG(___); doMoveRR(rl78, 8, rg1, tmp);                                    PST(); }    // MOV     A, [SP+byte]
static RL78_DISPATCH_FN(rl78Morph_1_89_MOV      ) { PRE();            op1=R_A  ;            op2=R_DE ;  PRE_REG__8_16(); LOAD_R(8,   0, rg2);    FLG(___); doMoveRR(rl78, 8, rg1, tmp);                                    PST(); }    // MOV     A, [DE]
static RL78_DISPATCH_FN(rl78Morph_1_8A_MOV      ) { PRE();            op1=R_A  ; IMM1(dis); op2=R_DE ;  PRE_REG__8_16(); LOAD_R(8, dis, rg2);    FLG(___); doMoveRR(rl78, 8, rg1, tmp);                                    PST(); }    // MOV     A, [DE+byte]
static RL78_DISPATCH_FN(rl78Morph_1_8B_MOV      ) { PRE();            op1=R_A  ;            op2=R_HL ;  PRE_REG__8_16(); LOAD_R(8,   0, rg2);    FLG(___); doMoveRR(rl78, 8, rg1, tmp);                                    PST(); }    // MOV     A, [HL]
static RL78_DISPATCH_FN(rl78Morph_1_8C_MOV      ) { PRE();            op1=R_A  ; IMM1(dis); op2=R_HL ;  PRE_REG__8_16(); LOAD_R(8, dis, rg2);    FLG(___); doMoveRR(rl78, 8, rg1, tmp);                                    PST(); }    // MOV     A, [HL+byte]
static RL78_DISPATCH_FN(rl78Morph_1_8D_MOV      ) { PRE();            op1=R_A  ;            SADDR(op2); PRE_REG__8_no(); LOAD_A(8, op2);         FLG(___); doMoveRR(rl78, 8, rg1, tmp);                                    PST(); }    // MOV     A, saddr
static RL78_DISPATCH_FN(rl78Morph_1_8E_MOV      ) { PRE();            op1=R_A  ;            SFR(op2) ;  PRE_REG__8_no(); LOAD_A(8, op2);         FLG(___); doMoveRR(rl78, 8, rg1, tmp);                                    PST(); }    // MOV     A, sfr
static RL78_DISPATCH_FN(rl78Morph_1_8F_MOV      ) { PRE();            op1=R_A  ;            IMM2(op2);  PRE_REG__8_no(); LOAD_A(8, op2);         FLG(___); doMoveRR(rl78, 8, rg1, tmp);                                    PST(); }    // MOV     A, !addr16
static RL78_DISPATCH_FN(rl78Morph_1_9X_DEC      ) { PRE();            BIT3(op1);                        PRE_REG__8_no();                         FLG(ZA_); doBinopRC(rl78, 8, vmi_SUB, rg1, 1);                            PST(); }    // DEC     ?
static RL78_DISPATCH_FN(rl78Morph_1_98_MOV      ) { PRE(); IMM1(dis); op1=R_SP ;            op2=R_A  ;  PRE_REG_16__8();                         FLG(___); doStoreRRO(rl78, 8, dis, rg1, rg2);                             PST(); }    // MOV     [SP+byte], A
static RL78_DISPATCH_FN(rl78Morph_1_99_MOV      ) { PRE();            op1=R_DE ;            op2=R_A  ;  PRE_REG_16__8();                         FLG(___); doStoreRRO(rl78, 8,   0, rg1, rg2);                             PST(); }    // MOV     [DE], A
static RL78_DISPATCH_FN(rl78Morph_1_9A_MOV      ) { PRE(); IMM1(dis); op1=R_DE ;            op2=R_A  ;  PRE_REG_16__8();                         FLG(___); doStoreRRO(rl78, 8, dis, rg1, rg2);                             PST(); }    // MOV     [DE+byte], A
static RL78_DISPATCH_FN(rl78Morph_1_9B_MOV      ) { PRE();            op1=R_HL ;            op2=R_A  ;  PRE_REG_16__8();                         FLG(___); doStoreRRO(rl78, 8,   0, rg1, rg2);                             PST(); }    // MOV     [HL], A
static RL78_DISPATCH_FN(rl78Morph_1_9C_MOV      ) { PRE(); IMM1(dis); op1=R_HL ;            op2=R_A  ;  PRE_REG_16__8();                         FLG(___); doStoreRRO(rl78, 8, dis, rg1, rg2);                             PST(); }    // MOV     [HL+byte], A
static RL78_DISPATCH_FN(rl78Morph_1_9D_MOV      ) { PRE();            SADDR(op1);           op2=R_A  ;  PRE_REG_no__8();                         FLG(___); doStoreRRO(rl78, 8, op1, rg1, rg2);                             PST(); }    // MOV     saddr, A
static RL78_DISPATCH_FN(rl78Morph_1_9E_MOV      ) { PRE();            SFR(op1) ;            op2=R_A  ;  PRE_REG_no__8();                         FLG(___); doStoreRRO(rl78, 8, op1, rg1, rg2);                             PST(); }    // MOV     sfr, A
static RL78_DISPATCH_FN(rl78Morph_1_9F_MOV      ) { PRE();            IMM2(op1);            op2=R_A  ;  PRE_REG_no__8();                         FLG(___); doStoreRRO(rl78, 8, op1, rg1, rg2);                             PST(); }    // MOV     !addr16, A
static RL78_DISPATCH_FN(rl78Morph_1_A0_INC      ) { PRE();            IMM2(op1);                        PRE_REG_no_no(); LOAD_A(8, op1);         FLG(ZA_); doBinopRC(rl78, 8, vmi_ADD, tmp, 1);    STOR_A(8, op1);        PST(); }    // INC     !addr16
static RL78_DISPATCH_FN(rl78Morph_1_A2_INCW     ) { PRE();            IMM2(op1);                        PRE_REG_no_no(); LOAD_A(16, op1);        FLG(___); doBinopRC(rl78, 16, vmi_ADD, tmp, 1);   STOR_A(16, op1);        PST(); }    // INCW    !addr16
static RL78_DISPATCH_FN(rl78Morph_1_A4_INC      ) { PRE();            SADDR(op1);                       PRE_REG_no_no(); LOAD_A(8, op1);         FLG(ZA_); doBinopRC(rl78, 8, vmi_ADD, tmp, 1);    STOR_A(8, op1);        PST(); }    // INC     saddr
static RL78_DISPATCH_FN(rl78Morph_1_A6_INCW     ) { PRE();            SADDR(op1);                       PRE_REG_no_no(); LOAD_A(16, op1);        FLG(___); doBinopRC(rl78, 16, vmi_ADD, tmp, 1);   STOR_A(16, op1);        PST(); }    // INCW    saddrp
static RL78_DISPATCH_FN(rl78Morph_1_AX_INCW     ) { PRE();            BIT2(op1);                        PRE_REG_16_no();                         FLG(___); doBinopRC(rl78, 16, vmi_ADD, rg1, 1);   WRIT_16(op1);        PST(); }    // INCW    ??
static RL78_DISPATCH_FN(rl78Morph_1_A8_MOVW     ) { PRE();            op1=R_AX ; IMM1(dis); op2=R_SP ;  PRE_REG_16_16(); LOAD_R(16, dis, rg2);   FLG(___); doMoveRR(rl78, 16, rg1, tmp);           WRIT_16(op1);        PST(); }    // MOVW    AX, [SP+byte]
static RL78_DISPATCH_FN(rl78Morph_1_A9_MOVW     ) { PRE();            op1=R_AX ;            op2=R_DE ;  PRE_REG_16_16(); LOAD_R(16,   0, rg2);   FLG(___); doMoveRR(rl78, 16, rg1, tmp);           WRIT_16(op1);        PST(); }    // MOVW    AX, [DE]
static RL78_DISPATCH_FN(rl78Morph_1_AA_MOVW     ) { PRE();            op1=R_AX ; IMM1(dis); op2=R_DE ;  PRE_REG_16_16(); LOAD_R(16, dis, rg2);   FLG(___); doMoveRR(rl78, 16, rg1, tmp);           WRIT_16(op1);        PST(); }    // MOVW    AX, [DE+byte]
static RL78_DISPATCH_FN(rl78Morph_1_AB_MOVW     ) { PRE();            op1=R_AX ;            op2=R_HL ;  PRE_REG_16_16(); LOAD_R(16,   0, rg2);   FLG(___); doMoveRR(rl78, 16, rg1, tmp);           WRIT_16(op1);        PST(); }    // MOVW    AX, [HL]
static RL78_DISPATCH_FN(rl78Morph_1_AC_MOVW     ) { PRE();            op1=R_AX ; IMM1(dis); op2=R_HL ;  PRE_REG_16_16(); LOAD_R(16, dis, rg2);   FLG(___); doMoveRR(rl78, 16, rg1, tmp);           WRIT_16(op1);        PST(); }    // MOVW    AX, [HL+byte]
static RL78_DISPATCH_FN(rl78Morph_1_AD_MOVW     ) { PRE();            op1=R_AX ;            SADDR(op2); PRE_REG_16_no(); LOAD_A(16, op2);        FLG(___); doMoveRR(rl78, 16, rg1, tmp);           WRIT_16(op1);        PST(); }    // MOVW    AX, saddrp
static RL78_DISPATCH_FN(rl78Morph_1_AE_MOVW     ) { PRE();            op1=R_AX ;            SFR(op2) ;  PRE_REG_16_no(); LOAD_A(16, op2);        FLG(___); doMoveRR(rl78, 16, rg1, tmp);           WRIT_16(op1);        PST(); }    // MOVW    AX, sfrp
static RL78_DISPATCH_FN(rl78Morph_1_AF_MOVW     ) { PRE();            op1=R_AX ;            IMM2(op2);  PRE_REG_16_no(); LOAD_A(16, op2);        FLG(___); doMoveRR(rl78, 16, rg1, tmp);           WRIT_16(op1);        PST(); }    // MOVW    AX, !addr16
static RL78_DISPATCH_FN(rl78Morph_1_B0_DEC      ) { PRE();            IMM2(op1);                        PRE_REG_no_no(); LOAD_A(8, op1);         FLG(ZA_); doBinopRC(rl78, 8, vmi_SUB, tmp, 1);    STOR_A(8, op1);        PST(); }    // DEC     !addr16
static RL78_DISPATCH_FN(rl78Morph_1_B2_DECW     ) { PRE();            IMM2(op1);                        PRE_REG_no_no(); LOAD_A(16, op1);        FLG(___); doBinopRC(rl78, 16, vmi_SUB, tmp, 1);   STOR_A(16, op1);        PST(); }    // DECW    !addr16
static RL78_DISPATCH_FN(rl78Morph_1_B4_DEC      ) { PRE();            SADDR(op1);                       PRE_REG_no_no(); LOAD_A(8, op1);         FLG(ZA_); doBinopRC(rl78, 8, vmi_SUB, tmp, 1);    STOR_A(8, op1);        PST(); }    // DEC     saddr
static RL78_DISPATCH_FN(rl78Morph_1_B6_DECW     ) { PRE();            SADDR(op1);                       PRE_REG_no_no(); LOAD_A(16, op1);        FLG(___); doBinopRC(rl78, 16, vmi_SUB, tmp, 1);   STOR_A(16, op1);        PST(); }    // DECW    saddrp
static RL78_DISPATCH_FN(rl78Morph_1_BX_DECW     ) { PRE();            BIT2(op1);                        PRE_REG_16_no();                         FLG(___); doBinopRC(rl78, 16, vmi_SUB, rg1, 1);   WRIT_16(op1);        PST(); }    // DECW    ??
static RL78_DISPATCH_FN(rl78Morph_1_B8_MOVW     ) { PRE(); IMM1(dis); op1=R_SP ;            op2=R_AX ;  PRE_REG_16_16();                         FLG(___); doStoreRRO(rl78, 16, dis, rg1, rg2);                            PST(); }    // MOVW    [SP+byte], AX
static RL78_DISPATCH_FN(rl78Morph_1_B9_MOVW     ) { PRE();            op1=R_DE ;            op2=R_AX ;  PRE_REG_16_16();                         FLG(___); doStoreRRO(rl78, 16,   0, rg1, rg2);                            PST(); }    // MOVW    [DE], AX
static RL78_DISPATCH_FN(rl78Morph_1_BA_MOVW     ) { PRE(); IMM1(dis); op1=R_DE ;            op2=R_AX ;  PRE_REG_16_16();                         FLG(___); doStoreRRO(rl78, 16, dis, rg1, rg2);                            PST(); }    // MOVW    [DE+byte], AX
static RL78_DISPATCH_FN(rl78Morph_1_BB_MOVW     ) { PRE();            op1=R_HL ;            op2=R_AX ;  PRE_REG_16_16();                         FLG(___); doStoreRRO(rl78, 16,   0, rg1, rg2);                            PST(); }    // MOVW    [HL], AX
static RL78_DISPATCH_FN(rl78Morph_1_BC_MOVW     ) { PRE(); IMM1(dis); op1=R_HL ;            op2=R_AX ;  PRE_REG_16_16();                         FLG(___); doStoreRRO(rl78, 16, dis, rg1, rg2);                            PST(); }    // MOVW    [HL+byte], AX
static RL78_DISPATCH_FN(rl78Morph_1_BD_MOVW     ) { PRE();            SADDR(op1);           op2=R_AX ;  PRE_REG_no_16();                         FLG(___); doStoreRRO(rl78, 16, op1, rg1, rg2);                            PST(); }    // MOVW    saddrp, AX
static RL78_DISPATCH_FN(rl78Morph_1_BE_MOVW     ) { PRE();            SFR(op1) ;            op2=R_AX ;  PRE_REG_no_16();                         FLG(___); doStoreRRO(rl78, 16, op1, rg1, rg2);                            PST(); }    // MOVW    sfrp, AX
static RL78_DISPATCH_FN(rl78Morph_1_BF_MOVW     ) { PRE();            IMM2(op1);            op2=R_AX ;  PRE_REG_no_16();                         FLG(___); doStoreRRO(rl78, 16, op1, rg1, rg2);                            PST(); }    // MOVW    !addr16, AX
static RL78_DISPATCH_FN(rl78Morph_1_CX_POP      ) { PRE();            BIT2(op1);                        PRE_REG_16_no();                         FLG(___); doPopReg(rl78, 16, rg1);                WRIT_16(op1);        PST(); }    // POP     ??
static RL78_DISPATCH_FN(rl78Morph_1_CY_PUSH     ) { PRE();            BIT2(op1);                        PRE_REG_16_no();                         FLG(___); doPushReg(rl78, 16, rg1);                                     PST(); }    // PUSH    ??
static RL78_DISPATCH_FN(rl78Morph_1_C8_MOV      ) { PRE(); IMM1(dis); op1=R_SP ;            IMM1(op2);  PRE_REG_16_no();                         FLG(___); doStoreRCO(rl78, 8, dis, rg1, op2);                             PST(); }    // MOV     [SP+byte], #byte
static RL78_DISPATCH_FN(rl78Morph_1_C9_MOVW     ) { PRE();            SADDR(op1);           IMM2(op2);  PRE_REG_no_no();                         FLG(___); doStoreRCO(rl78, 16, op1, rg1, op2);                            PST(); }    // MOVW    saddrp, #word
static RL78_DISPATCH_FN(rl78Morph_1_CA_MOV      ) { PRE(); IMM1(dis); op1=R_DE ;            IMM1(op2);  PRE_REG_16_no();                         FLG(___); doStoreRCO(rl78, 8, dis, rg1, op2);                             PST(); }    // MOV     [DE+byte], #byte
static RL78_DISPATCH_FN(rl78Morph_1_CB_MOVW     ) { PRE();            SFR(op1) ;            IMM2(op2);  PRE_REG_no_no();                         FLG(___); doStoreRCO(rl78, 16, op1, rg1, op2);                            PST(); }    // MOVW    sfrp, #word
static RL78_DISPATCH_FN(rl78Morph_1_CC_MOV      ) { PRE(); IMM1(dis); op1=R_HL ;            IMM1(op2);  PRE_REG_16_no();                         FLG(___); doStoreRCO(rl78, 8, dis, rg1, op2);                             PST(); }    // MOV     [HL+byte], #byte
static RL78_DISPATCH_FN(rl78Morph_1_CD_MOV      ) { PRE();            SADDR(op1);           IMM1(op2);  PRE_REG_no_no();                         FLG(___); doStoreRCO(rl78, 8, op1, rg1, op2);                             PST(); }    // MOV     saddr, #byte
static RL78_DISPATCH_FN(rl78Morph_1_CE_MOV_SFR  ) { PRE();            SFR(op1) ;            IMM1(op2);  PRE_REG_no_no();                         FLG(___); doStoreRCO(rl78, 8, op1, rg1, op2);                             PST(); }    // MOV     sfr, #byte
static RL78_DISPATCH_FN(rl78Morph_1_CE_MOV_PSW  ) { PRE();            op1=R_PSW;            IMM1(op2);  PRE_REG__8_no();                         FLG(___); doMoveRC(rl78, 8, rg1, op2); doSetPSW();                        PST(); }    // MOV     PSW, #byte
static RL78_DISPATCH_FN(rl78Morph_1_CE_MOV_CS   ) { PRE();            op1=R_CS ;            IMM1(op2);  PRE_REG__8_no();                         FLG(___); doMoveRC(rl78, 8, rg1, op2);                                    PST(); }    // MOV     CS, #byte
static RL78_DISPATCH_FN(rl78Morph_1_CE_MULHU    ) { PRE();            op1=R_AX ;            op2=R_BC ;  PRE_REG_16_16(); CHKVARI(S3, "MULHU");   FLG(___); doMulopRR(16, vmi_MUL , rg1, rg2); WRIT_16(op1);WRIT_16(op2);PST(); }    // MULHU                   // BCAX �� AX * BC
static RL78_DISPATCH_FN(rl78Morph_1_CE_MULH     ) { PRE();            op1=R_AX ;            op2=R_BC ;  PRE_REG_16_16(); CHKVARI(S3, "MULH");    FLG(___); doMulopRR(16, vmi_IMUL, rg1, rg2); WRIT_16(op1);WRIT_16(op2);PST(); }    // MULH                    // BCAX �� sext(AX) * sext(BC)
static RL78_DISPATCH_FN(rl78Morph_1_CE_DIVHU    ) { PRE();            op1=R_AX ;            op2=R_DE ;  PRE_REG_16_16(); CHKVARI(S3, "DIVHU");   FLG(___); doDivopRR(16, vmi_DIV , rg1, rg2); WRIT_16(op1);WRIT_16(op2);PST(); }    // DIVHU                   // AX(��), DE(�]��) �� AX / DE
static RL78_DISPATCH_FN(rl78Morph_1_CE_DIVWU    ) { PRE();            op1=R_BCAX;           op2=R_HLDE; PRE_REG_32_32(); CHKVARI(S3, "DIVWU");   FLG(___); doDivopRR(32, vmi_DIV , rg1, rg2); WRIT_32(op1);WRIT_32(op2);PST(); }    // DIVWU                   // BCAX(��), HLDE(�]��) �� BCAX / HLDE
static RL78_DISPATCH_FN(rl78Morph_1_CE_MACHU    ) { PRE();            op1=R_AX ;            op2=R_BC ;  PRE_REG_16_16(); CHKVARI(S3, "MACHU");   FLG(_AC); doMACH(vmi_MUL , rg1, rg2);                                     PST(); }    // MACHU                   // MACR �� MACR + AX * BC
static RL78_DISPATCH_FN(rl78Morph_1_CE_MACH     ) { PRE();            op1=R_AX ;            op2=R_BC ;  PRE_REG_16_16(); CHKVARI(S3, "MACH");    FLG(_AC); doMACH(vmi_IMUL, rg1, rg2);                                     PST(); }    // MACH                    // MACR �� MACR + sext(AX) * sext(BC)    /* ��Z���ʂ̃e���|�����̈����ƁA�t���O�̍X�V���ʓ| */
static RL78_DISPATCH_FN(rl78Morph_1_CF_MOV      ) { PRE();            IMM2(op1);            IMM1(op2);  PRE_REG_no_no();                         FLG(___); doStoreRCO(rl78, 8, op1, rg1, op2);                             PST(); }    // MOV     !addr16, #byte
static RL78_DISPATCH_FN(rl78Morph_1_DX_CMP0     ) { PRE();            BIT3(op1);                        PRE_REG__8_no();                         FLG(ZAC); doCompareRC(rl78, 8, rg1, 0); /* set 0 to AC and CY */        PST(); }    // CMP0    ?
static RL78_DISPATCH_FN(rl78Morph_1_D4_CMP0     ) { PRE();            SADDR(op1);                       PRE_REG_no_no(); LOAD_A(8, op1);         FLG(ZAC); doCompareRC(rl78, 8, tmp, 0); /* set 0 to AC and CY */        PST(); }    // CMP0    saddr
static RL78_DISPATCH_FN(rl78Morph_1_D5_CMP0     ) { PRE();            IMM2(op1);                        PRE_REG_no_no(); LOAD_A(8, op1);         FLG(ZAC); doCompareRC(rl78, 8, tmp, 0); /* set 0 to AC and CY */        PST(); }    // CMP0    !addr16
static RL78_DISPATCH_FN(rl78Morph_1_D6_MULU     ) { PRE();            op1=R_A  ;            op2=R_X  ;  PRE_REG__8__8();                          FLG(___); doMulopRRR(rl78, 8, vmi_MUL, rg2, rg1, rg2); WRIT_16(R_AX);    PST(); }    // MULU    X
static RL78_DISPATCH_FN(rl78Morph_1_D7_RET      ) { PRE();                                              PRE_REG_no_no();                         FLG(___); doPopPC(rl78); doJumpReg(tmp, vmi_JH_RETURN);                PST(); }    // RET
static RL78_DISPATCH_FN(rl78Morph_1_D8_MOV      ) { PRE();            op1=R_X  ;            SADDR(op2); PRE_REG__8_no(); LOAD_A(8, op2);         FLG(___); doMoveRR(rl78, 8, rg1, tmp);                                    PST(); }    // MOV     X, saddr
static RL78_DISPATCH_FN(rl78Morph_1_D9_MOV      ) { PRE();            op1=R_X  ;            IMM2(op2);  PRE_REG__8_no(); LOAD_A(8, op2);         FLG(___); doMoveRR(rl78, 8, rg1, tmp);                                    PST(); }    // MOV     X, !addr16
static RL78_DISPATCH_FN(rl78Morph_1_DC_BC       ) { PRE();            IMM1(op1);                        PRE_REG_no_no();                         FLG(___); doCondJumpRel(rl78, thisPC, op1, en_Cond_C);                    PST(); }    // BC      $addr20
static RL78_DISPATCH_FN(rl78Morph_1_DD_BZ       ) { PRE();            IMM1(op1);                        PRE_REG_no_no();                         FLG(___); doCondJumpRel(rl78, thisPC, op1, en_Cond_Z);                    PST(); }    // BZ      $addr20
static RL78_DISPATCH_FN(rl78Morph_1_DE_BNC      ) { PRE();            IMM1(op1);                        PRE_REG_no_no();                         FLG(___); doCondJumpRel(rl78, thisPC, op1, en_Cond_NC);                PST(); }    // BNC     $addr20
static RL78_DISPATCH_FN(rl78Morph_1_DF_BNZ      ) { PRE();            IMM1(op1);                        PRE_REG_no_no();                         FLG(___); doCondJumpRel(rl78, thisPC, op1, en_Cond_NZ);                PST(); }    // BNZ     $addr20
static RL78_DISPATCH_FN(rl78Morph_1_EX_ONEB     ) { PRE();            BIT3(op1);                        PRE_REG__8_no();                         FLG(___); doMoveRC(rl78, 8, rg1, 1);                                      PST(); }    // ONEB    ?
static RL78_DISPATCH_FN(rl78Morph_1_E4_ONEB     ) { PRE();            SADDR(op1);                       PRE_REG_no_no();                         FLG(___); doStoreRCO(rl78, 8, op1, rg1, 1);                               PST(); }    // ONEB    saddr
static RL78_DISPATCH_FN(rl78Morph_1_E5_ONEB     ) { PRE();            IMM2(op1);                        PRE_REG_no_no();                         FLG(___); doStoreRCO(rl78, 8, op1, rg1, 1);                               PST(); }    // ONEB    !addr16
static RL78_DISPATCH_FN(rl78Morph_1_E6_ONEW     ) { PRE();            op1=R_AX ;                        PRE_REG_16_no();                         FLG(___); doMoveRC(rl78, 16, rg1, 1);             WRIT_16(op1);        PST(); }    // ONEW    AX
static RL78_DISPATCH_FN(rl78Morph_1_E7_ONEW     ) { PRE();            op1=R_BC ;                        PRE_REG_16_no();                         FLG(___); doMoveRC(rl78, 16, rg1, 1);             WRIT_16(op1);        PST(); }    // ONEW    BC
static RL78_DISPATCH_FN(rl78Morph_1_E8_MOV      ) { PRE();            op1=R_B  ;            SADDR(op2); PRE_REG__8_no(); LOAD_A(8, op2);         FLG(___); doMoveRR(rl78, 8, rg1, tmp);                                    PST(); }    // MOV     B, saddr
static RL78_DISPATCH_FN(rl78Morph_1_E9_MOV      ) { PRE();            op1=R_B  ;            IMM2(op2);  PRE_REG__8_no(); LOAD_A(8, op2);         FLG(___); doMoveRR(rl78, 8, rg1, tmp);                                    PST(); }    // MOV     B, !addr16
static RL78_DISPATCH_FN(rl78Morph_1_EC_BR       ) { PRE();            IMM3(op1);                        PRE_REG_no_no();                         FLG(___); doJumpDir(op1, vmi_JH_NONE);                                    PST(); }    // BR      !!addr20
static RL78_DISPATCH_FN(rl78Morph_1_ED_BR       ) { PRE();            IMM2(op1);                        PRE_REG_no_no();                         FLG(___); doJumpDir(op1, vmi_JH_NONE);                                    PST(); }    // BR      !addr16
static RL78_DISPATCH_FN(rl78Morph_1_EE_BR       ) { PRE();            IMM2(op1);                        PRE_REG_no_no();                         FLG(___); DOJUMPREL(16, op1, vmi_JH_NONE);                                PST(); }    // BR      $!addr20        // �P�U�r�b�g����
static RL78_DISPATCH_FN(rl78Morph_1_EF_BR       ) { PRE();            IMM1(op1);                        PRE_REG_no_no();                         FLG(___); DOJUMPREL(8, op1, vmi_JH_NONE);                                 PST(); }    // BR      $addr20        // �W�r�b�g����
static RL78_DISPATCH_FN(rl78Morph_1_FX_CLRB     ) { PRE();            BIT3(op1);                        PRE_REG__8_no();                         FLG(___); doMoveRC(rl78, 8, rg1, 0);                                      PST(); }    // CLRB    ?
static RL78_DISPATCH_FN(rl78Morph_1_F4_CLRB     ) { PRE();            SADDR(op1);                       PRE_REG_no_no();                         FLG(___); doStoreRCO(rl78, 8, op1, rg1, 0);                               PST(); }    // CLRB    saddr
static RL78_DISPATCH_FN(rl78Morph_1_F5_CLRB     ) { PRE();            IMM2(op1);                        PRE_REG_no_no();                         FLG(___); doStoreRCO(rl78, 8, op1, rg1, 0);                               PST(); }    // CLRB    !addr16
static RL78_DISPATCH_FN(rl78Morph_1_F6_CLRW     ) { PRE();            op1=R_AX ;                        PRE_REG_16_no();                         FLG(___); doMoveRC(rl78, 16, rg1, 0);             WRIT_16(op1);        PST(); }    // CLRW    AX
static RL78_DISPATCH_FN(rl78Morph_1_F7_CLRW     ) { PRE();            op1=R_BC ;                        PRE_REG_16_no();                         FLG(___); doMoveRC(rl78, 16, rg1, 0);             WRIT_16(op1);        PST(); }    // CLRW    BC
static RL78_DISPATCH_FN(rl78Morph_1_F8_MOV      ) { PRE();            op1=R_C  ;            SADDR(op2); PRE_REG__8_no(); LOAD_A(8, op2);         FLG(___); doMoveRR(rl78, 8, rg1, tmp);                                    PST(); }    // MOV     C, saddr
static RL78_DISPATCH_FN(rl78Morph_1_F9_MOV      ) { PRE();            op1=R_C  ;            IMM2(op2);  PRE_REG__8_no(); LOAD_A(8, op2);         FLG(___); doMoveRR(rl78, 8, rg1, tmp);                                    PST(); }    // MOV     C, !addr16
static RL78_DISPATCH_FN(rl78Morph_1_FC_CALL     ) { PRE();            IMM3(op1);                        PRE_REG_no_no();                         FLG(___); doPushPC(rl78, thisPC + 4); doCallDir(op1, thisPC + 4);        PST(); }    // CALL    !!addr20
static RL78_DISPATCH_FN(rl78Morph_1_FD_CALL     ) { PRE();            IMM2(op1);                        PRE_REG_no_no();                         FLG(___); doPushPC(rl78, thisPC + 3); doCallDir(op1, thisPC + 3);        PST(); }    // CALL    !addr16
static RL78_DISPATCH_FN(rl78Morph_1_FE_CALL     ) { PRE();            IMM2(op1);                        PRE_REG_no_no();                         FLG(___); doPushPC(rl78, thisPC + 3); DOCALLREL(16, op1, thisPC + 3);    PST(); }    // CALL    $!addr20        // �P�U�r�b�g����
static RL78_DISPATCH_FN(rl78Morph_1_XA_MOVW     ) { PRE();            BIT(op1,4,2);         SADDR(op2); PRE_REG_16_no(); LOAD_A(16, op2);        FLG(___); doMoveRR(rl78, 16, rg1, tmp);           WRIT_16(op1);        PST(); }    // MOVW    ??, saddrp
static RL78_DISPATCH_FN(rl78Morph_1_XB_MOVW     ) { PRE();            BIT(op1,4,2);         IMM2(op2);  PRE_REG_16_no(); LOAD_A(16, op2);        FLG(___); doMoveRR(rl78, 16, rg1, tmp);           WRIT_16(op1);        PST(); }    // MOVW    ??, !addr16

static RL78_DISPATCH_FN(rl78Morph_2_0X_ADD      ) { PRE();            BIT3(op1);            op2=R_A  ;  PRE_REG__8__8();                         FLG(ZAC); doBinopRR(rl78, 8, vmi_ADD, rg1, rg2);                          PST(); }    // ADD     ?, A
static RL78_DISPATCH_FN(rl78Morph_2_09_ADDW     ) { PRE();            op1=R_AX ; IMM1(dis); op2=R_HL ;  PRE_REG_16_16(); LOAD_R(16, dis, rg2);   FLG(ZAC); doBinopRR(rl78, 16, vmi_ADD, rg1, tmp); WRIT_16(op1);        PST(); }    // ADDW    AX, [HL+byte]
static RL78_DISPATCH_FN(rl78Morph_2_0Y_ADD      ) { PRE();            op1=R_A  ;            BIT3(op2);  PRE_REG__8__8();                         FLG(ZAC); doBinopRR(rl78, 8, vmi_ADD, rg1, rg2);                          PST(); }    // ADD     A, ?
static RL78_DISPATCH_FN(rl78Morph_2_1X_ADDC     ) { PRE();            BIT3(op1);            op2=R_A  ;  PRE_REG__8__8();                         FLG(ZAC); doBinopRR(rl78, 8, vmi_ADC, rg1, rg2);                          PST(); }    // ADDC    ?, A
static RL78_DISPATCH_FN(rl78Morph_2_1Y_ADDC     ) { PRE();            op1=R_A  ;            BIT3(op2);  PRE_REG__8__8();                         FLG(ZAC); doBinopRR(rl78, 8, vmi_ADC, rg1, rg2);                          PST(); }    // ADDC    A, ?
static RL78_DISPATCH_FN(rl78Morph_2_2X_SUB      ) { PRE();            BIT3(op1);            op2=R_A  ;  PRE_REG__8__8();                         FLG(ZAC); doBinopRR(rl78, 8, vmi_SUB, rg1, rg2);                          PST(); }    // SUB     ?, A
static RL78_DISPATCH_FN(rl78Morph_2_29_SUBW     ) { PRE();            op1=R_AX ; IMM1(dis); op2=R_HL ;  PRE_REG_16_16(); LOAD_R(16, dis, rg2);   FLG(ZAC); doBinopRR(rl78, 16, vmi_SUB, rg1, tmp); WRIT_16(op1);        PST(); }    // SUBW    AX, [HL+byte]
static RL78_DISPATCH_FN(rl78Morph_2_2Y_SUB      ) { PRE();            op1=R_A  ;            BIT3(op2);  PRE_REG__8__8();                         FLG(ZAC); doBinopRR(rl78, 8, vmi_SUB, rg1, rg2);                          PST(); }    // SUB     A, ?
static RL78_DISPATCH_FN(rl78Morph_2_3X_SUBC     ) { PRE();            BIT3(op1);            op2=R_A  ;  PRE_REG__8__8();                         FLG(ZAC); doBinopRR(rl78, 8, vmi_SBB, rg1, rg2);                          PST(); }    // SUBC    ?, A
static RL78_DISPATCH_FN(rl78Morph_2_3Y_SUBC     ) { PRE();            op1=R_A  ;            BIT3(op2);  PRE_REG__8__8();                         FLG(ZAC); doBinopRR(rl78, 8, vmi_SBB, rg1, rg2);                          PST(); }    // SUBC    A, ?
static RL78_DISPATCH_FN(rl78Morph_2_4X_CMP      ) { PRE();            BIT3(op1);            op2=R_A  ;  PRE_REG__8__8();                         FLG(ZAC); doCompareRR(rl78, 8, rg1, rg2);                                 PST(); }    // CMP     ?, A
static RL78_DISPATCH_FN(rl78Morph_2_49_CMPW     ) { PRE();            op1=R_AX ; IMM1(dis); op2=R_HL ;  PRE_REG_16_16(); LOAD_R(16, dis, rg2);   FLG(ZAC); doCompareRR(rl78, 16, rg1, tmp);                                PST(); }    // CMPW    AX, [HL+byte]
static RL78_DISPATCH_FN(rl78Morph_2_4Y_CMP      ) { PRE();            op1=R_A  ;            BIT3(op2);  PRE_REG__8__8();                         FLG(ZAC); doCompareRR(rl78, 8, rg1, rg2);                                 PST(); }    // CMP     A, ?
static RL78_DISPATCH_FN(rl78Morph_2_5X_AND      ) { PRE();            BIT3(op1);            op2=R_A  ;  PRE_REG__8__8();                         FLG(Z__); doBinopRR(rl78, 8, vmi_AND, rg1, rg2);                          PST(); }    // AND     ?, A
static RL78_DISPATCH_FN(rl78Morph_2_59_INC      ) { PRE(); IMM1(dis); op1=R_HL ;                        PRE_REG_16_no(); LOAD_R(8, dis, rg1);    FLG(ZA_); doBinopRC(rl78, 8, vmi_ADD, tmp, 1);    STOR_R(8, dis, rg1);    PST(); }    // INC     [HL+byte]
static RL78_DISPATCH_FN(rl78Morph_2_5Y_AND      ) { PRE();            op1=R_A  ;            BIT3(op2);  PRE_REG__8__8();                         FLG(Z__); doBinopRR(rl78, 8, vmi_AND, rg1, rg2);                          PST(); }    // AND     A, ?
static RL78_DISPATCH_FN(rl78Morph_2_6X_OR       ) { PRE();            BIT3(op1);            op2=R_A  ;  PRE_REG__8__8();                         FLG(Z__); doBinopRR(rl78, 8, vmi_OR , rg1, rg2);                          PST(); }    // OR      ?, A
static RL78_DISPATCH_FN(rl78Morph_2_69_DEC      ) { PRE(); IMM1(dis); op1=R_HL ;                        PRE_REG_16_no(); LOAD_R(8, dis, rg1);    FLG(ZA_); doBinopRC(rl78, 8, vmi_SUB, tmp, 1);    STOR_R(8, dis, rg1);    PST(); }    // DEC     [HL+byte]
static RL78_DISPATCH_FN(rl78Morph_2_6Y_OR       ) { PRE();            op1=R_A  ;            BIT3(op2);  PRE_REG__8__8();                         FLG(Z__); doBinopRR(rl78, 8, vmi_OR, rg1, rg2);                           PST(); }    // OR      A, ?
static RL78_DISPATCH_FN(rl78Morph_2_7X_XOR      ) { PRE();            BIT3(op1);            op2=R_A  ;  PRE_REG__8__8();                         FLG(Z__); doBinopRR(rl78, 8, vmi_XOR, rg1, rg2);                          PST(); }    // XOR     ?, A
static RL78_DISPATCH_FN(rl78Morph_2_79_INCW     ) { PRE(); IMM1(dis); op1=R_HL ;                        PRE_REG_16_no(); LOAD_R(16, dis, rg1);   FLG(___); doBinopRC(rl78, 16, vmi_ADD, tmp, 1);   STOR_R(16, dis, rg1);PST(); }    // INCW    [HL+byte]
static RL78_DISPATCH_FN(rl78Morph_2_7Y_XOR      ) { PRE();            op1=R_A  ;            BIT3(op2);  PRE_REG__8__8();                         FLG(Z__); doBinopRR(rl78, 8, vmi_XOR, rg1, rg2);                          PST(); }    // XOR     A, ?
static RL78_DISPATCH_FN(rl78Morph_2_80_ADD      ) { PRE();            op1=R_A  ;            op2=R_B  ;  PRE_REG__8__8(); LOAD_W(8, R_HL, rg2);   FLG(ZAC); doBinopRR(rl78, 8, vmi_ADD, rg1, tmp);                          PST(); }    // ADD     A, [HL+B]
static RL78_DISPATCH_FN(rl78Morph_2_82_ADD      ) { PRE();            op1=R_A  ;            op2=R_C  ;  PRE_REG__8__8(); LOAD_W(8, R_HL, rg2);   FLG(ZAC); doBinopRR(rl78, 8, vmi_ADD, rg1, tmp);                          PST(); }    // ADD     A, [HL+C]
static RL78_DISPATCH_FN(rl78Morph_2_89_DECW     ) { PRE(); IMM1(dis); op1=R_HL ;                        PRE_REG_16_no(); LOAD_R(16, dis, rg1);   FLG(___); doBinopRC(rl78, 16, vmi_SUB, tmp, 1);   STOR_R(16, dis, rg1);PST(); }    // DECW    [HL+byte]
static RL78_DISPATCH_FN(rl78Morph_2_8X_XCH      ) { PRE();            op1=R_A  ;            BIT3(op2);  PRE_REG__8__8();                         FLG(___); doSwap(8, rg1, rg2);                                            PST(); }    // XCH     A, ?
static RL78_DISPATCH_FN(rl78Morph_2_90_ADDC     ) { PRE();            op1=R_A  ;            op2=R_B  ;  PRE_REG__8__8(); LOAD_W(8, R_HL, rg2);   FLG(ZAC); doBinopRR(rl78, 8, vmi_ADC, rg1, tmp);                          PST(); }    // ADDC    A, [HL+B]
static RL78_DISPATCH_FN(rl78Morph_2_92_ADDC     ) { PRE();            op1=R_A  ;            op2=R_C  ;  PRE_REG__8__8(); LOAD_W(8, R_HL, rg2);   FLG(ZAC); doBinopRR(rl78, 8, vmi_ADC, rg1, tmp);                          PST(); }    // ADDC    A, [HL+C]
static RL78_DISPATCH_FN(rl78Morph_2_A0_SUB      ) { PRE();            op1=R_A  ;            op2=R_B  ;  PRE_REG__8__8(); LOAD_W(8, R_HL, rg2);   FLG(ZAC); doBinopRR(rl78, 8, vmi_SUB, rg1, tmp);                          PST(); }    // SUB     A, [HL+B]
static RL78_DISPATCH_FN(rl78Morph_2_A2_SUB      ) { PRE();            op1=R_A  ;            op2=R_C  ;  PRE_REG__8__8(); LOAD_W(8, R_HL, rg2);   FLG(ZAC); doBinopRR(rl78, 8, vmi_SUB, rg1, tmp);                          PST(); }    // SUB     A, [HL+C]
static RL78_DISPATCH_FN(rl78Morph_2_A8_XCH      ) { PRE();            op1=R_A  ;            SADDR(op2); PRE_REG__8_no(); LOAD_A(8, op2);         FLG(___); doSwap(8, rg1, tmp);                    STOR_A(8, op2);        PST(); }    // XCH     A, saddr
static RL78_DISPATCH_FN(rl78Morph_2_A9_XCH      ) { PRE();            op1=R_A  ;            op2=R_C  ;  PRE_REG__8__8(); LOAD_W(8, R_HL, rg2);   FLG(___); doSwap(8, rg1, tmp);                    STOR_W(8, R_HL, rg2);PST(); }    // XCH     A, [HL+C]
static RL78_DISPATCH_FN(rl78Morph_2_AA_XCH      ) { PRE();            op1=R_A  ;            IMM2(op2);  PRE_REG__8_no(); LOAD_A(8, op2);         FLG(___); doSwap(8, rg1, tmp);                    STOR_A(8, op2);        PST(); }    // XCH     A, !addr16
static RL78_DISPATCH_FN(rl78Morph_2_AB_XCH      ) { PRE();            op1=R_A  ;            SFR(op2) ;  PRE_REG__8_no(); LOAD_A(8, op2);         FLG(___); doSwap(8, rg1, tmp);                    STOR_A(8, op2);        PST(); }    // XCH     A, sfr
static RL78_DISPATCH_FN(rl78Morph_2_AC_XCH      ) { PRE();            op1=R_A  ;            op2=R_HL ;  PRE_REG__8_16(); LOAD_R(8,   0, rg2);    FLG(___); doSwap(8, rg1, tmp);                    STOR_R(8,   0, rg2);    PST(); }    // XCH     A, [HL]
static RL78_DISPATCH_FN(rl78Morph_2_AD_XCH      ) { PRE();            op1=R_A  ; IMM1(dis); op2=R_HL ;  PRE_REG__8_16(); LOAD_R(8, dis, rg2);    FLG(___); doSwap(8, rg1, tmp);                    STOR_R(8, dis, rg2);    PST(); }    // XCH     A, [HL+byte]
static RL78_DISPATCH_FN(rl78Morph_2_AE_XCH      ) { PRE();            op1=R_A  ;            op2=R_DE ;  PRE_REG__8_16(); LOAD_R(8,   0, rg2);    FLG(___); doSwap(8, rg1, tmp);                    STOR_R(8,   0, rg2);    PST(); }    // XCH     A, [DE]
static RL78_DISPATCH_FN(rl78Morph_2_AF_XCH      ) { PRE();            op1=R_A  ; IMM1(dis); op2=R_DE ;  PRE_REG__8_16(); LOAD_R(8, dis, rg2);    FLG(___); doSwap(8, rg1, tmp);                    STOR_R(8, dis, rg2);    PST(); }    // XCH     A, [DE+byte]
static RL78_DISPATCH_FN(rl78Morph_2_B0_SUBC     ) { PRE();            op1=R_A  ;            op2=R_B  ;  PRE_REG__8__8(); LOAD_W(8, R_HL, rg2);   FLG(ZAC); doBinopRR(rl78, 8, vmi_SBB, rg1, tmp);                          PST(); }    // SUBC    A, [HL+B]
static RL78_DISPATCH_FN(rl78Morph_2_B2_SUBC     ) { PRE();            op1=R_A  ;            op2=R_C  ;  PRE_REG__8__8(); LOAD_W(8, R_HL, rg2);   FLG(ZAC); doBinopRR(rl78, 8, vmi_SBB, rg1, tmp);                          PST(); }    // SUBC    A, [HL+C]
static RL78_DISPATCH_FN(rl78Morph_2_B8_MOV      ) { PRE();            op1=R_ES ;            SADDR(op2); PRE_REG__8_no(); LOAD_A(8, op2);         FLG(___); doMoveRR(rl78, 8, rg1, tmp);                                    PST(); }    // MOV     ES, saddr
static RL78_DISPATCH_FN(rl78Morph_2_B9_XCH      ) { PRE();            op1=R_A  ;            op2=R_B  ;  PRE_REG__8__8(); LOAD_W(8, R_HL, rg2);   FLG(___); doSwap(8, rg1, tmp);                    STOR_W(8, R_HL, rg2);PST(); }    // XCH     A, [HL+B]
static RL78_DISPATCH_FN(rl78Morph_2_C0_CMP      ) { PRE();            op1=R_A  ;            op2=R_B  ;  PRE_REG__8__8(); LOAD_W(8, R_HL, rg2);   FLG(ZAC); doCompareRR(rl78, 8, rg1, tmp);                                 PST(); }    // CMP     A, [HL+B]
static RL78_DISPATCH_FN(rl78Morph_2_C2_CMP      ) { PRE();            op1=R_A  ;            op2=R_C  ;  PRE_REG__8__8(); LOAD_W(8, R_HL, rg2);   FLG(ZAC); doCompareRR(rl78, 8, rg1, tmp);                                 PST(); }    // CMP     A, [HL+C]
static RL78_DISPATCH_FN(rl78Morph_2_C3_BH       ) { PRE();            IMM1(op1);                        PRE_REG_no_no();                         FLG(___); doCondJumpRel(rl78, thisPC, op1, en_Cond_H);                    PST(); }    // BH      $addr20
static RL78_DISPATCH_FN(rl78Morph_2_C8_SKC      ) { PRE();                                              PRE_REG_no_no();                         FLG(___); badSkip(rl78);                                                PST(); }    // SKC
static RL78_DISPATCH_FN(rl78Morph_2_C9_MOV      ) { PRE();            op1=R_A  ;            op2=R_B  ;  PRE_REG__8__8(); LOAD_W(8, R_HL, rg2);   FLG(___); doMoveRR(rl78, 8, rg1, tmp);                                    PST(); }    // MOV     A, [HL+B]
static RL78_DISPATCH_FN(rl78Morph_2_CB_BR       ) { PRE();            op1=R_AX ;                        PRE_REG_16_no(); ADDR_CS(rg1);           FLG(___); doJumpReg(RL78_CS_ADDR, vmi_JH_NONE);                          PST(); }    // BR      AX
static RL78_DISPATCH_FN(rl78Morph_2_CC_BRK      ) { PRE();                                              PRE_REG_no_no();                         FLG(___); doGetPSW(tmp); doBRK(rl78, thisPC + 2, tmp);                  PST(); }    // BRK
static RL78_DISPATCH_FN(rl78Morph_2_CD_POP      ) { PRE();            op1=R_PSW;                        PRE_REG__8_no();                         FLG(___); doPopReg(rl78, 8, rg1); doSetPSW();                           PST(); }    // POP     PSW
static RL78_DISPATCH_FN(rl78Morph_2_CE_MOVS     ) { PRE(); IMM1(dis); op1=R_HL ;            op2=R_X  ;  PRE_REG_16__8();                         FLG(Z_C); doMOVS(rl78, dis, rg1, rg2);                                    PST(); }    // MOVS    [HL+byte], X
static RL78_DISPATCH_FN(rl78Morph_2_D0_AND      ) { PRE();            op1=R_A  ;            op2=R_B  ;  PRE_REG__8__8(); LOAD_W(8, R_HL, rg2);   FLG(Z__); doBinopRR(rl78, 8, vmi_AND, rg1, tmp);                          PST(); }    // AND     A, [HL+B]
static RL78_DISPATCH_FN(rl78Morph_2_D2_AND      ) { PRE();            op1=R_A  ;            op2=R_C  ;  PRE_REG__8__8(); LOAD_W(8, R_HL, rg2);   FLG(Z__); doBinopRR(rl78, 8, vmi_AND, rg1, tmp);                          PST(); }    // AND     A, [HL+C]
static RL78_DISPATCH_FN(rl78Morph_2_D3_BNH      ) { PRE();            IMM1(op1);                        PRE_REG_no_no();                         FLG(___); doCondJumpRel(rl78, thisPC, op1, en_Cond_NH);                PST(); }    // BNH     $addr20
static RL78_DISPATCH_FN(rl78Morph_2_D8_SKNC     ) { PRE();                                              PRE_REG_no_no();                         FLG(___); badSkip(rl78);                                               PST(); }    // SKNC
static RL78_DISPATCH_FN(rl78Morph_2_D9_MOV      ) { PRE();            op1=R_B  ;            op2=R_A  ;  PRE_REG__8__8();                         FLG(___); doMoveRR(rl78, 8, tmp, rg2);            STOR_W(8, R_HL, rg1);PST(); }    // MOV     [HL+B], A
static RL78_DISPATCH_FN(rl78Morph_2_DB_ROR      ) { PRE();            op1=R_A  ;                        PRE_REG__8_no();                         FLG(__C); doBinopRC(rl78, 8, vmi_ROR, rg1, 1);                            PST(); }    // ROR     A, 1
static RL78_DISPATCH_FN(rl78Morph_2_DC_ROLC     ) { PRE();            op1=R_A  ;                        PRE_REG__8_no();                         FLG(__C); doBinopRC(rl78, 8, vmi_RCL, rg1, 1);                            PST(); }    // ROLC    A, 1
static RL78_DISPATCH_FN(rl78Morph_2_DD_PUSH     ) { PRE();                                              PRE_REG_no_no();                         FLG(___); doGetPSW(tmp); doPushReg(rl78, 8, tmp);                       PST(); }    // PUSH    PSW
static RL78_DISPATCH_FN(rl78Morph_2_DE_CMPS     ) { PRE();            op1=R_X  ; IMM1(dis); op2=R_HL ;  PRE_REG__8_16(); LOAD_R(8, dis, rg2);    FLG(ZAC); doCMPS(rl78, rg1, tmp);                                         PST(); }    // CMPS    X, [HL+byte]
static RL78_DISPATCH_FN(rl78Morph_2_E0_OR       ) { PRE();            op1=R_A  ;            op2=R_B  ;  PRE_REG__8__8(); LOAD_W(8, R_HL, rg2);   FLG(Z__); doBinopRR(rl78, 8, vmi_OR, rg1, tmp);                           PST(); }    // OR      A, [HL+B]
static RL78_DISPATCH_FN(rl78Morph_2_E2_OR       ) { PRE();            op1=R_A  ;            op2=R_C  ;  PRE_REG__8__8(); LOAD_W(8, R_HL, rg2);   FLG(Z__); doBinopRR(rl78, 8, vmi_OR, rg1, tmp);                           PST(); }    // OR      A, [HL+C]
static RL78_DISPATCH_FN(rl78Morph_2_E3_SKH      ) { PRE();                                              PRE_REG_no_no();                         FLG(___); badSkip(rl78);                                                PST(); }    // SKH
static RL78_DISPATCH_FN(rl78Morph_2_E8_SKZ      ) { PRE();                                              PRE_REG_no_no();                         FLG(___); badSkip(rl78);                                                PST(); }    // SKZ
static RL78_DISPATCH_FN(rl78Morph_2_E9_MOV      ) { PRE();            op1=R_A  ;            op2=R_C  ;  PRE_REG__8__8(); LOAD_W(8, R_HL, rg2);   FLG(___); doMoveRR(rl78, 8, rg1, tmp);                                    PST(); }    // MOV     A, [HL+C]
static RL78_DISPATCH_FN(rl78Morph_2_EB_ROL      ) { PRE();            op1=R_A  ;                        PRE_REG__8_no();                         FLG(__C); doBinopRC(rl78, 8, vmi_ROL, rg1, 1);                            PST(); }    // ROL     A, 1
static RL78_DISPATCH_FN(rl78Morph_2_EC_RETB     ) { PRE();                                              PRE_REG_no_no();                         FLG(___); doRETB(rl78 /* ,tmp */ ); doJumpReg(tmp, vmi_JH_RETURNINT);    PST(); }    // RETB
static RL78_DISPATCH_FN(rl78Morph_2_ED_HALT     ) { PRE();                                              PRE_REG_no_no();                         FLG(___); doHALT(rl78);                                                   PST(); }    // HALT
static RL78_DISPATCH_FN(rl78Morph_2_F0_XOR      ) { PRE();            op1=R_A  ;            op2=R_B  ;  PRE_REG__8__8(); LOAD_W(8, R_HL, rg2);   FLG(Z__); doBinopRR(rl78, 8, vmi_XOR, rg1, tmp);                          PST(); }    // XOR     A, [HL+B]
static RL78_DISPATCH_FN(rl78Morph_2_F2_XOR      ) { PRE();            op1=R_A  ;            op2=R_C  ;  PRE_REG__8__8(); LOAD_W(8, R_HL, rg2);   FLG(Z__); doBinopRR(rl78, 8, vmi_XOR, rg1, tmp);                          PST(); }    // XOR     A, [HL+C]
static RL78_DISPATCH_FN(rl78Morph_2_F3_SKNH     ) { PRE();                                              PRE_REG_no_no();                         FLG(___); badSkip(rl78);                                               PST(); }    // SKNH
static RL78_DISPATCH_FN(rl78Morph_2_F8_SKNZ     ) { PRE();                                              PRE_REG_no_no();                         FLG(___); badSkip(rl78);                                               PST(); }    // SKNZ
static RL78_DISPATCH_FN(rl78Morph_2_F9_MOV      ) { PRE();            op1=R_C  ;            op2=R_A  ;  PRE_REG__8__8();                         FLG(___); doMoveRR(rl78, 8, tmp, rg2);            STOR_W(8, R_HL, rg1);PST(); }    // MOV     [HL+C], A
static RL78_DISPATCH_FN(rl78Morph_2_FB_RORC     ) { PRE();            op1=R_A  ;                        PRE_REG__8_no();                         FLG(__C); doBinopRC(rl78, 8, vmi_RCR, rg1, 1);                            PST(); }    // RORC    A, 1
static RL78_DISPATCH_FN(rl78Morph_2_FC_RETI     ) { PRE();                                              PRE_REG_no_no();                         FLG(___); doRETI(rl78 /* ,tmp */ ); doJumpReg(tmp, vmi_JH_RETURNINT);    PST(); }    // RETI
static RL78_DISPATCH_FN(rl78Morph_2_FD_STOP     ) { PRE();                                              PRE_REG_no_no();                         FLG(___); doSTOP(rl78);                                                   PST(); }    // STOP
static RL78_DISPATCH_FN(rl78Morph_2_XE_ROLWC    ) { PRE();            BIT(op1,4,1);                     PRE_REG_16_no();                         FLG(__C); doBinopRC(rl78, 16, vmi_RCL, rg1, 1);   WRIT_16(op1);        PST(); }    // ROLWC   ??, 1
static RL78_DISPATCH_FN(rl78Morph_2_XF_SEL      ) { PRE();            BIT(op1,4,2);                     PRE_REG_no_no(); CHKVARI(S2, "SEL");     FLG(___); doSEL(rl78, op1);                                             PST(); }    // SEL     RBn
static RL78_DISPATCH_FN(rl78Morph_2_XA_CALL     ) { PRE();            BIT(op1,4,2);                     PRE_REG_16_no(); ADDR_CS(rg1);           FLG(___); doPushPC(rl78, thisPC + 2); doCallReg(RL78_CS_ADDR, thisPC + 2);    PST(); }    // CALL    ??
static RL78_DISPATCH_FN(rl78Morph_2_XX_CALLT    ) { PRE();            BIT(op1,4,3); BIT(op2,0,2);       PRE_REG_no_no();                         FLG(___); doPushPC(rl78, thisPC + 2); doCALLT(op2, op1, thisPC + 2);    PST(); }    // CALLT   [00nnh]

static RL78_DISPATCH_FN(rl78Morph_3_X0_SET1     ) { PRE(); IDX3(ix1); IMM2(op1);                        PRE_REG_no_no(); LOAD_A(8, op1);         FLG(___); doMOV1_R_IM(tmp, ix1, 1);               STOR_A(8, op1);        PST(); }    // SET1    !addr16.n
static RL78_DISPATCH_FN(rl78Morph_3_X1_MOV1     ) { PRE(); IDX3(ix1); SADDR(op1);           op2=R_CY ;  PRE_REG_no__8(); LOAD_A(8, op1);         FLG(___); doMOV1_R_CY(tmp, ix1, rg2);             STOR_A(8, op1);        PST(); }    // MOV1    saddr.n, CY
static RL78_DISPATCH_FN(rl78Morph_3_X2_SET1     ) { PRE(); IDX3(ix1); SADDR(op1);                       PRE_REG_no_no(); LOAD_A(8, op1);         FLG(___); doMOV1_R_IM(tmp, ix1, 1);               STOR_A(8, op1);        PST(); }    // SET1    saddr.n
static RL78_DISPATCH_FN(rl78Morph_3_X3_CLR1     ) { PRE(); IDX3(ix1); SADDR(op1);                       PRE_REG_no_no(); LOAD_A(8, op1);         FLG(___); doMOV1_R_IM(tmp, ix1, 0);               STOR_A(8, op1);        PST(); }    // CLR1    saddr.n
static RL78_DISPATCH_FN(rl78Morph_3_X4_MOV1     ) { PRE(); IDX3(ix1); op1=R_CY ; SADDR(op2);            PRE_REG__8_no(); LOAD_A(8, op2);         FLG(___); doMOV1_CY_R(rg1, tmp, ix1);                                     PST(); }    // MOV1    CY, saddr.n
static RL78_DISPATCH_FN(rl78Morph_3_X5_AND1     ) { PRE(); IDX3(ix1); op1=R_CY ; SADDR(op2);            PRE_REG__8_no(); LOAD_A(8, op2);         FLG(___); doBinop_CY_R(rg1, vmi_AND, tmp, ix1);                           PST(); }    // AND1    CY, saddr.n
static RL78_DISPATCH_FN(rl78Morph_3_X6_OR1      ) { PRE(); IDX3(ix1); op1=R_CY ; SADDR(op2);            PRE_REG__8_no(); LOAD_A(8, op2);         FLG(___); doBinop_CY_R(rg1, vmi_OR , tmp, ix1);                           PST(); }    // OR1     CY, saddr.n
static RL78_DISPATCH_FN(rl78Morph_3_X7_XOR1     ) { PRE(); IDX3(ix1); op1=R_CY ; SADDR(op2);            PRE_REG__8_no(); LOAD_A(8, op2);         FLG(___); doBinop_CY_R(rg1, vmi_XOR, tmp, ix1);                           PST(); }    // XOR1    CY, saddr.n
static RL78_DISPATCH_FN(rl78Morph_3_X8_CLR1     ) { PRE(); IDX3(ix1); IMM2(op1);                        PRE_REG_no_no(); LOAD_A(8, op1);         FLG(___); doMOV1_R_IM(tmp, ix1, 0);               STOR_A(8, op1);        PST(); }    // CLR1    !addr16.n
static RL78_DISPATCH_FN(rl78Morph_3_X9_MOV1     ) { PRE(); IDX3(ix1); SFR(op1) ;            op2=R_CY ;  PRE_REG_no__8(); LOAD_A(8, op1);         FLG(___); doMOV1_R_CY(tmp, ix1, rg2);             STOR_A(8, op1);        PST(); }    // MOV1    sfr.n, CY
static RL78_DISPATCH_FN(rl78Morph_3_XA_SET1     ) { PRE(); IDX3(ix1); SFR(op1) ;                        PRE_REG_no_no(); LOAD_A(8, op1);         FLG(___); doMOV1_R_IM(tmp, ix1, 1);               STOR_A(8, op1);        PST(); }    // SET1    sfr.n
static RL78_DISPATCH_FN(rl78Morph_3_XB_CLR1     ) { PRE(); IDX3(ix1); SFR(op1) ;                        PRE_REG_no_no(); LOAD_A(8, op1);         FLG(___); doMOV1_R_IM(tmp, ix1, 0);               STOR_A(8, op1);        PST(); }    // CLR1    sfr.n
static RL78_DISPATCH_FN(rl78Morph_3_XC_MOV1     ) { PRE(); IDX3(ix1); op1=R_CY ; SFR(op2) ;             PRE_REG__8_no(); LOAD_A(8, op2);         FLG(___); doMOV1_CY_R(rg1, tmp, ix1);                                     PST(); }    // MOV1    CY, sfr.n
static RL78_DISPATCH_FN(rl78Morph_3_XD_AND1     ) { PRE(); IDX3(ix1); op1=R_CY ; SFR(op2) ;             PRE_REG__8_no(); LOAD_A(8, op2);         FLG(___); doBinop_CY_R(rg1, vmi_AND, tmp, ix1);                           PST(); }    // AND1    CY, sfr.n
static RL78_DISPATCH_FN(rl78Morph_3_XE_OR1      ) { PRE(); IDX3(ix1); op1=R_CY ; SFR(op2) ;             PRE_REG__8_no(); LOAD_A(8, op2);         FLG(___); doBinop_CY_R(rg1, vmi_OR , tmp, ix1);                           PST(); }    // OR1     CY, sfr.n
static RL78_DISPATCH_FN(rl78Morph_3_XF_XOR1     ) { PRE(); IDX3(ix1); op1=R_CY ; SFR(op2) ;             PRE_REG__8_no(); LOAD_A(8, op2);         FLG(___); doBinop_CY_R(rg1, vmi_XOR, tmp, ix1);                           PST(); }    // XOR1    CY, sfr.n
static RL78_DISPATCH_FN(rl78Morph_3_7A_EI       ) { PRE();                                              PRE_REG_no_no();                         FLG(___); doMoveRC(rl78, 8, RL78_IE, 1); doEI(rl78);                    PST(); }    // EI
static RL78_DISPATCH_FN(rl78Morph_3_7B_DI       ) { PRE();                                              PRE_REG_no_no();                         FLG(___); doMoveRC(rl78, 8, RL78_IE, 0);                                  PST(); }    // DI
static RL78_DISPATCH_FN(rl78Morph_3_80_SET1     ) { PRE();            op1=R_CY ;                        PRE_REG__8_no();                         FLG(___); doMoveRC(rl78, 8, rg1, 1);                                      PST(); }    // SET1    CY
static RL78_DISPATCH_FN(rl78Morph_3_88_CLR1     ) { PRE();            op1=R_CY ;                        PRE_REG__8_no();                         FLG(___); doMoveRC(rl78, 8, rg1, 0);                                      PST(); }    // CLR1    CY
static RL78_DISPATCH_FN(rl78Morph_3_C0_NOT1     ) { PRE();            op1=R_CY ;                        PRE_REG__8_no();                         FLG(___); doBinopRC(rl78, 8, vmi_XOR, rg1, 1);                            PST(); }    // NOT1    CY
static RL78_DISPATCH_FN(rl78Morph_3_Y1_MOV1     ) { PRE(); IDX3(ix1); op1=R_HL ;            op2=R_CY;   PRE_REG_16__8(); LOAD_R(8, 0, rg1);      FLG(___); doMOV1_R_CY(tmp, ix1, rg2);             STOR_R(8, 0, rg1);    PST(); }    // MOV1    [HL].n, CY
static RL78_DISPATCH_FN(rl78Morph_3_Y2_SET1     ) { PRE(); IDX3(ix1); op1=R_HL ;                        PRE_REG_16_no(); LOAD_R(8, 0, rg1);      FLG(___); doMOV1_R_IM(tmp, ix1, 1);               STOR_R(8, 0, rg1);    PST(); }    // SET1    [HL].n
static RL78_DISPATCH_FN(rl78Morph_3_Y3_CLR1     ) { PRE(); IDX3(ix1); op1=R_HL ;                        PRE_REG_16_no(); LOAD_R(8, 0, rg1);      FLG(___); doMOV1_R_IM(tmp, ix1, 0);               STOR_R(8, 0, rg1);    PST(); }    // CLR1    [HL].n
static RL78_DISPATCH_FN(rl78Morph_3_Y4_MOV1     ) { PRE(); IDX3(ix1); op1=R_CY ; op2=R_HL ;             PRE_REG__8_16(); LOAD_R(8, 0, rg2);      FLG(___); doMOV1_CY_R(rg1, tmp, ix1);                                     PST(); }    // MOV1    CY, [HL].n
static RL78_DISPATCH_FN(rl78Morph_3_Y5_AND1     ) { PRE(); IDX3(ix1); op1=R_CY ; op2=R_HL ;             PRE_REG__8_16(); LOAD_R(8, 0, rg2);      FLG(___); doBinop_CY_R(rg1, vmi_AND, tmp, ix1);                           PST(); }    // AND1    CY, [HL].n
static RL78_DISPATCH_FN(rl78Morph_3_Y6_OR1      ) { PRE(); IDX3(ix1); op1=R_CY ; op2=R_HL ;             PRE_REG__8_16(); LOAD_R(8, 0, rg2);      FLG(___); doBinop_CY_R(rg1, vmi_OR , tmp, ix1);                           PST(); }    // OR1     CY, [HL].n
static RL78_DISPATCH_FN(rl78Morph_3_Y7_XOR1     ) { PRE(); IDX3(ix1); op1=R_CY ; op2=R_HL ;             PRE_REG__8_16(); LOAD_R(8, 0, rg2);      FLG(___); doBinop_CY_R(rg1, vmi_XOR, tmp, ix1);                           PST(); }    // XOR1    CY, [HL].n
static RL78_DISPATCH_FN(rl78Morph_3_Y9_MOV1     ) { PRE(); IDX3(ix1); op1=R_A  ;            op2=R_CY;   PRE_REG__8__8();                         FLG(___); doMOV1_R_CY(rg1, ix1, rg2);                                     PST(); }    // MOV1    A.n, CY
static RL78_DISPATCH_FN(rl78Morph_3_YA_SET1     ) { PRE(); IDX3(ix1); op1=R_A  ;                        PRE_REG__8_no();                         FLG(___); doMOV1_R_IM(rg1, ix1, 1);                                       PST(); }    // SET1    A.n
static RL78_DISPATCH_FN(rl78Morph_3_YB_CLR1     ) { PRE(); IDX3(ix1); op1=R_A  ;                        PRE_REG__8_no();                         FLG(___); doMOV1_R_IM(rg1, ix1, 0);                                       PST(); }    // CLR1    A.n
static RL78_DISPATCH_FN(rl78Morph_3_YC_MOV1     ) { PRE(); IDX3(ix1); op1=R_CY ; op2=R_A  ;             PRE_REG__8__8();                         FLG(___); doMOV1_CY_R(rg1, rg2, ix1);                                     PST(); }    // MOV1    CY, A.n
static RL78_DISPATCH_FN(rl78Morph_3_YD_AND1     ) { PRE(); IDX3(ix1); op1=R_CY ; op2=R_A  ;             PRE_REG__8__8();                         FLG(___); doBinop_CY_R(rg1, vmi_AND, rg2, ix1);                           PST(); }    // AND1    CY, A.n
static RL78_DISPATCH_FN(rl78Morph_3_YE_OR1      ) { PRE(); IDX3(ix1); op1=R_CY ; op2=R_A  ;             PRE_REG__8__8();                         FLG(___); doBinop_CY_R(rg1, vmi_OR , rg2, ix1);                           PST(); }    // OR1     CY, A.n
static RL78_DISPATCH_FN(rl78Morph_3_YF_XOR1     ) { PRE(); IDX3(ix1); op1=R_CY ; op2=R_A  ;             PRE_REG__8__8();                         FLG(___); doBinop_CY_R(rg1, vmi_XOR, rg2, ix1);                           PST(); }    // XOR1    CY, A.n

static RL78_DISPATCH_FN(rl78Morph_4_X0_BTCLR    ) { PRE(); IDX3(ix1); SADDR(op1);IMM1(op2);             PRE_REG_no_no(); LOAD_A(8, op1);         FLG(___); doBitTest(en_Cond_TCLR, tmp, ix1);      STOR_A(8, op1);        doCondJumpRel(rl78, thisPC, op2, en_Cond_TCLR);    PST(); }    // BTCLR   saddr.n, $addr20
static RL78_DISPATCH_FN(rl78Morph_4_X1_BTCLR    ) { PRE(); IDX3(ix1); op1=R_A  ; IMM1(op2);             PRE_REG__8_no();                         FLG(___); doBitTest(en_Cond_TCLR, rg1, ix1);                              doCondJumpRel(rl78, thisPC, op2, en_Cond_TCLR);    PST(); }    // BTCLR   A.n, $addr20
static RL78_DISPATCH_FN(rl78Morph_4_X2_BT       ) { PRE(); IDX3(ix1); SADDR(op1);IMM1(op2);             PRE_REG_no_no(); LOAD_A(8, op1);         FLG(___); doBitTest(en_Cond_T   , tmp, ix1);                              doCondJumpRel(rl78, thisPC, op2, en_Cond_T   );    PST(); }    // BT      saddr.n, $addr20
static RL78_DISPATCH_FN(rl78Morph_4_X3_BT       ) { PRE(); IDX3(ix1); op1=R_A  ; IMM1(op2);             PRE_REG__8_no();                         FLG(___); doBitTest(en_Cond_T   , rg1, ix1);                              doCondJumpRel(rl78, thisPC, op2, en_Cond_T   );    PST(); }    // BT      A.n, $addr20
static RL78_DISPATCH_FN(rl78Morph_4_X4_BF       ) { PRE(); IDX3(ix1); SADDR(op1);IMM1(op2);             PRE_REG_no_no(); LOAD_A(8, op1);         FLG(___); doBitTest(en_Cond_F   , tmp, ix1);                              doCondJumpRel(rl78, thisPC, op2, en_Cond_F   );    PST(); }    // BF      saddr.n, $addr20
static RL78_DISPATCH_FN(rl78Morph_4_X5_BF       ) { PRE(); IDX3(ix1); op1=R_A  ; IMM1(op2);             PRE_REG__8_no();                         FLG(___); doBitTest(en_Cond_F   , rg1, ix1);                              doCondJumpRel(rl78, thisPC, op2, en_Cond_F   );    PST(); }    // BF      A.n, $addr20
static RL78_DISPATCH_FN(rl78Morph_4_X7_SHL      ) { PRE(); IDX3(ix1); op1=R_C  ;                        PRE_REG__8_no();                         FLG(__C); doBinopRC(rl78, 8, vmi_SHL, rg1, ix1);                          PST(); }    // SHL     C, n
static RL78_DISPATCH_FN(rl78Morph_4_X8_SHL      ) { PRE(); IDX3(ix1); op1=R_B  ;                        PRE_REG__8_no();                         FLG(__C); doBinopRC(rl78, 8, vmi_SHL, rg1, ix1);                          PST(); }    // SHL     B, n
static RL78_DISPATCH_FN(rl78Morph_4_X9_SHL      ) { PRE(); IDX3(ix1); op1=R_A  ;                        PRE_REG__8_no();                         FLG(__C); doBinopRC(rl78, 8, vmi_SHL, rg1, ix1);                          PST(); }    // SHL     A, n
static RL78_DISPATCH_FN(rl78Morph_4_XA_SHR      ) { PRE(); IDX3(ix1); op1=R_A  ;                        PRE_REG__8_no();                         FLG(__C); doBinopRC(rl78, 8, vmi_SHR, rg1, ix1);                          PST(); }    // SHR     A, n
static RL78_DISPATCH_FN(rl78Morph_4_XB_SAR      ) { PRE(); IDX3(ix1); op1=R_A  ;                        PRE_REG__8_no();                         FLG(__C); doBinopRC(rl78, 8, vmi_SAR, rg1, ix1);                          PST(); }    // SAR     A, n
static RL78_DISPATCH_FN(rl78Morph_4_Y0_BTCLR    ) { PRE(); IDX3(ix1); SFR(op1) ; IMM1(op2);             PRE_REG_no_no(); LOAD_A(8, op1);         FLG(___); doBitTest(en_Cond_TCLR, tmp, ix1);      STOR_A(8, op1);        doCondJumpRel(rl78, thisPC, op2, en_Cond_TCLR);    PST(); }    // BTCLR   sfr.n, $addr20
static RL78_DISPATCH_FN(rl78Morph_4_Y1_BTCLR    ) { PRE(); IDX3(ix1); op1=R_HL ; IMM1(op2);             PRE_REG_16_no(); LOAD_R(8, 0, rg1);      FLG(___); doBitTest(en_Cond_TCLR, tmp, ix1);      STOR_R(8, 0, rg1);    doCondJumpRel(rl78, thisPC, op2, en_Cond_TCLR);    PST(); }    // BTCLR   [HL].n, $addr20
static RL78_DISPATCH_FN(rl78Morph_4_Y2_BT       ) { PRE(); IDX3(ix1); SFR(op1) ; IMM1(op2);             PRE_REG_no_no(); LOAD_A(8, op1);         FLG(___); doBitTest(en_Cond_T   , tmp, ix1);                              doCondJumpRel(rl78, thisPC, op2, en_Cond_T   );    PST(); }    // BT      sfr.n, $addr20
static RL78_DISPATCH_FN(rl78Morph_4_Y3_BT       ) { PRE(); IDX3(ix1); op1=R_HL ; IMM1(op2);             PRE_REG_16_no(); LOAD_R(8, 0, rg1);      FLG(___); doBitTest(en_Cond_T   , tmp, ix1);                              doCondJumpRel(rl78, thisPC, op2, en_Cond_T   );    PST(); }    // BT      [HL].n, $addr20
static RL78_DISPATCH_FN(rl78Morph_4_Y4_BF       ) { PRE(); IDX3(ix1); SFR(op1) ; IMM1(op2);             PRE_REG_no_no(); LOAD_A(8, op1);         FLG(___); doBitTest(en_Cond_F   , tmp, ix1);                              doCondJumpRel(rl78, thisPC, op2, en_Cond_F   );    PST(); }    // BF      sfr.n, $addr20
static RL78_DISPATCH_FN(rl78Morph_4_Y5_BF       ) { PRE(); IDX3(ix1); op1=R_HL ; IMM1(op2);             PRE_REG_16_no(); LOAD_R(8, 0, rg1);      FLG(___); doBitTest(en_Cond_F   , tmp, ix1);                              doCondJumpRel(rl78, thisPC, op2, en_Cond_F   );    PST(); }    // BF      [HL].n, $addr20
static RL78_DISPATCH_FN(rl78Morph_4_XC_SHLW     ) { PRE(); IDX4(ix1); op1=R_BC ;                        PRE_REG_16_no();                         FLG(__C); doBinopRC(rl78, 16, vmi_SHL, rg1, ix1); WRIT_16(op1);        PST(); }    // SHLW    BC, nn
static RL78_DISPATCH_FN(rl78Morph_4_XD_SHLW     ) { PRE(); IDX4(ix1); op1=R_AX ;                        PRE_REG_16_no();                         FLG(__C); doBinopRC(rl78, 16, vmi_SHL, rg1, ix1); WRIT_16(op1);        PST(); }    // SHLW    AX, nn
static RL78_DISPATCH_FN(rl78Morph_4_XE_SHRW     ) { PRE(); IDX4(ix1); op1=R_AX ;                        PRE_REG_16_no();                         FLG(__C); doBinopRC(rl78, 16, vmi_SHR, rg1, ix1); WRIT_16(op1);        PST(); }    // SHRW    AX, nn
static RL78_DISPATCH_FN(rl78Morph_4_XF_SARW     ) { PRE(); IDX4(ix1); op1=R_AX ;                        PRE_REG_16_no();                         FLG(__C); doBinopRC(rl78, 16, vmi_SAR, rg1, ix1); WRIT_16(op1);        PST(); }    // SARW    AX, nn

//#pragma GCC diagnostic pop



//
// RL78 morpher dispatch table
//
static rl78DispatchTableC dispatchTable = {

    [RL78_IT_1_00_NOP      ] = rl78Morph_1_00_NOP      ,
    [RL78_IT_1_02_ADDW     ] = rl78Morph_1_02_ADDW     ,
    [RL78_IT_1_04_ADDW     ] = rl78Morph_1_04_ADDW     ,
    [RL78_IT_1_06_ADDW     ] = rl78Morph_1_06_ADDW     ,
    [RL78_IT_1_0X_ADDW     ] = rl78Morph_1_0X_ADDW     ,
    [RL78_IT_1_08_XCH      ] = rl78Morph_1_08_XCH      ,
    [RL78_IT_1_09_MOV      ] = rl78Morph_1_09_MOV      ,
    [RL78_IT_1_0A_ADD      ] = rl78Morph_1_0A_ADD      ,
    [RL78_IT_1_0B_ADD      ] = rl78Morph_1_0B_ADD      ,
    [RL78_IT_1_0C_ADD      ] = rl78Morph_1_0C_ADD      ,
    [RL78_IT_1_0D_ADD      ] = rl78Morph_1_0D_ADD      ,
    [RL78_IT_1_0E_ADD      ] = rl78Morph_1_0E_ADD      ,
    [RL78_IT_1_0F_ADD      ] = rl78Morph_1_0F_ADD      ,
    [RL78_IT_1_10_ADDW     ] = rl78Morph_1_10_ADDW     ,
    [RL78_IT_1_11_PREFIX   ] = rl78Morph_1_11_PREFIX   ,
    [RL78_IT_1_1X_MOVW     ] = rl78Morph_1_1X_MOVW     ,
    [RL78_IT_1_1Y_MOVW     ] = rl78Morph_1_1Y_MOVW     ,
    [RL78_IT_1_18_MOV      ] = rl78Morph_1_18_MOV      ,
    [RL78_IT_1_19_MOV      ] = rl78Morph_1_19_MOV      ,
    [RL78_IT_1_1A_ADDC     ] = rl78Morph_1_1A_ADDC     ,
    [RL78_IT_1_1B_ADDC     ] = rl78Morph_1_1B_ADDC     ,
    [RL78_IT_1_1C_ADDC     ] = rl78Morph_1_1C_ADDC     ,
    [RL78_IT_1_1D_ADDC     ] = rl78Morph_1_1D_ADDC     ,
    [RL78_IT_1_1E_ADDC     ] = rl78Morph_1_1E_ADDC     ,
    [RL78_IT_1_1F_ADDC     ] = rl78Morph_1_1F_ADDC     ,
    [RL78_IT_1_20_SUBW     ] = rl78Morph_1_20_SUBW     ,
    [RL78_IT_1_22_SUBW     ] = rl78Morph_1_22_SUBW     ,
    [RL78_IT_1_24_SUBW     ] = rl78Morph_1_24_SUBW     ,
    [RL78_IT_1_26_SUBW     ] = rl78Morph_1_26_SUBW     ,
    [RL78_IT_1_2X_SUBW     ] = rl78Morph_1_2X_SUBW     ,
    [RL78_IT_1_28_MOV      ] = rl78Morph_1_28_MOV      ,
    [RL78_IT_1_29_MOV      ] = rl78Morph_1_29_MOV      ,
    [RL78_IT_1_2A_SUB      ] = rl78Morph_1_2A_SUB      ,
    [RL78_IT_1_2B_SUB      ] = rl78Morph_1_2B_SUB      ,
    [RL78_IT_1_2C_SUB      ] = rl78Morph_1_2C_SUB      ,
    [RL78_IT_1_2D_SUB      ] = rl78Morph_1_2D_SUB      ,
    [RL78_IT_1_2E_SUB      ] = rl78Morph_1_2E_SUB      ,
    [RL78_IT_1_2F_SUB      ] = rl78Morph_1_2F_SUB      ,
    [RL78_IT_1_31_4thmap   ] = rl78Morph_1_31_4thmap   ,
    [RL78_IT_1_3X_XCHW     ] = rl78Morph_1_3X_XCHW     ,
    [RL78_IT_1_3Y_MOVW     ] = rl78Morph_1_3Y_MOVW     ,
    [RL78_IT_1_38_MOV      ] = rl78Morph_1_38_MOV      ,
    [RL78_IT_1_39_MOV      ] = rl78Morph_1_39_MOV      ,
    [RL78_IT_1_3A_SUBC     ] = rl78Morph_1_3A_SUBC     ,
    [RL78_IT_1_3B_SUBC     ] = rl78Morph_1_3B_SUBC     ,
    [RL78_IT_1_3C_SUBC     ] = rl78Morph_1_3C_SUBC     ,
    [RL78_IT_1_3D_SUBC     ] = rl78Morph_1_3D_SUBC     ,
    [RL78_IT_1_3E_SUBC     ] = rl78Morph_1_3E_SUBC     ,
    [RL78_IT_1_3F_SUBC     ] = rl78Morph_1_3F_SUBC     ,
    [RL78_IT_1_40_CMP      ] = rl78Morph_1_40_CMP      ,
    [RL78_IT_1_41_MOV      ] = rl78Morph_1_41_MOV      ,
    [RL78_IT_1_42_CMPW     ] = rl78Morph_1_42_CMPW     ,
    [RL78_IT_1_44_CMPW     ] = rl78Morph_1_44_CMPW     ,
    [RL78_IT_1_46_CMPW     ] = rl78Morph_1_46_CMPW     ,
    [RL78_IT_1_4X_CMPW     ] = rl78Morph_1_4X_CMPW     ,
    [RL78_IT_1_48_MOV      ] = rl78Morph_1_48_MOV      ,
    [RL78_IT_1_49_MOV      ] = rl78Morph_1_49_MOV      ,
    [RL78_IT_1_4A_CMP      ] = rl78Morph_1_4A_CMP      ,
    [RL78_IT_1_4B_CMP      ] = rl78Morph_1_4B_CMP      ,
    [RL78_IT_1_4C_CMP      ] = rl78Morph_1_4C_CMP      ,
    [RL78_IT_1_4D_CMP      ] = rl78Morph_1_4D_CMP      ,
    [RL78_IT_1_4E_CMP      ] = rl78Morph_1_4E_CMP      ,
    [RL78_IT_1_4F_CMP      ] = rl78Morph_1_4F_CMP      ,
    [RL78_IT_1_5X_MOV      ] = rl78Morph_1_5X_MOV      ,
    [RL78_IT_1_58_MOVW     ] = rl78Morph_1_58_MOVW     ,
    [RL78_IT_1_59_MOVW     ] = rl78Morph_1_59_MOVW     ,
    [RL78_IT_1_5A_AND      ] = rl78Morph_1_5A_AND      ,
    [RL78_IT_1_5B_AND      ] = rl78Morph_1_5B_AND      ,
    [RL78_IT_1_5C_AND      ] = rl78Morph_1_5C_AND      ,
    [RL78_IT_1_5D_AND      ] = rl78Morph_1_5D_AND      ,
    [RL78_IT_1_5E_AND      ] = rl78Morph_1_5E_AND      ,
    [RL78_IT_1_5F_AND      ] = rl78Morph_1_5F_AND      ,
    [RL78_IT_1_61_2ndmap   ] = rl78Morph_1_61_2ndmap   ,
    [RL78_IT_1_6X_MOV      ] = rl78Morph_1_6X_MOV      ,
    [RL78_IT_1_68_MOVW     ] = rl78Morph_1_68_MOVW     ,
    [RL78_IT_1_69_MOVW     ] = rl78Morph_1_69_MOVW     ,
    [RL78_IT_1_6A_OR       ] = rl78Morph_1_6A_OR       ,
    [RL78_IT_1_6B_OR       ] = rl78Morph_1_6B_OR       ,
    [RL78_IT_1_6C_OR       ] = rl78Morph_1_6C_OR       ,
    [RL78_IT_1_6D_OR       ] = rl78Morph_1_6D_OR       ,
    [RL78_IT_1_6E_OR       ] = rl78Morph_1_6E_OR       ,
    [RL78_IT_1_6F_OR       ] = rl78Morph_1_6F_OR       ,
    [RL78_IT_1_71_3rdmap   ] = rl78Morph_1_71_3rdmap   ,
    [RL78_IT_1_7X_MOV      ] = rl78Morph_1_7X_MOV      ,
    [RL78_IT_1_78_MOVW     ] = rl78Morph_1_78_MOVW     ,
    [RL78_IT_1_79_MOVW     ] = rl78Morph_1_79_MOVW     ,
    [RL78_IT_1_7A_XOR      ] = rl78Morph_1_7A_XOR      ,
    [RL78_IT_1_7B_XOR      ] = rl78Morph_1_7B_XOR      ,
    [RL78_IT_1_7C_XOR      ] = rl78Morph_1_7C_XOR      ,
    [RL78_IT_1_7D_XOR      ] = rl78Morph_1_7D_XOR      ,
    [RL78_IT_1_7E_XOR      ] = rl78Morph_1_7E_XOR      ,
    [RL78_IT_1_7F_XOR      ] = rl78Morph_1_7F_XOR      ,
    [RL78_IT_1_8X_INC      ] = rl78Morph_1_8X_INC      ,
    [RL78_IT_1_88_MOV      ] = rl78Morph_1_88_MOV      ,
    [RL78_IT_1_89_MOV      ] = rl78Morph_1_89_MOV      ,
    [RL78_IT_1_8A_MOV      ] = rl78Morph_1_8A_MOV      ,
    [RL78_IT_1_8B_MOV      ] = rl78Morph_1_8B_MOV      ,
    [RL78_IT_1_8C_MOV      ] = rl78Morph_1_8C_MOV      ,
    [RL78_IT_1_8D_MOV      ] = rl78Morph_1_8D_MOV      ,
    [RL78_IT_1_8E_MOV      ] = rl78Morph_1_8E_MOV      ,
    [RL78_IT_1_8F_MOV      ] = rl78Morph_1_8F_MOV      ,
    [RL78_IT_1_9X_DEC      ] = rl78Morph_1_9X_DEC      ,
    [RL78_IT_1_98_MOV      ] = rl78Morph_1_98_MOV      ,
    [RL78_IT_1_99_MOV      ] = rl78Morph_1_99_MOV      ,
    [RL78_IT_1_9A_MOV      ] = rl78Morph_1_9A_MOV      ,
    [RL78_IT_1_9B_MOV      ] = rl78Morph_1_9B_MOV      ,
    [RL78_IT_1_9C_MOV      ] = rl78Morph_1_9C_MOV      ,
    [RL78_IT_1_9D_MOV      ] = rl78Morph_1_9D_MOV      ,
    [RL78_IT_1_9E_MOV      ] = rl78Morph_1_9E_MOV      ,
    [RL78_IT_1_9F_MOV      ] = rl78Morph_1_9F_MOV      ,
    [RL78_IT_1_A0_INC      ] = rl78Morph_1_A0_INC      ,
    [RL78_IT_1_A2_INCW     ] = rl78Morph_1_A2_INCW     ,
    [RL78_IT_1_A4_INC      ] = rl78Morph_1_A4_INC      ,
    [RL78_IT_1_A6_INCW     ] = rl78Morph_1_A6_INCW     ,
    [RL78_IT_1_AX_INCW     ] = rl78Morph_1_AX_INCW     ,
    [RL78_IT_1_A8_MOVW     ] = rl78Morph_1_A8_MOVW     ,
    [RL78_IT_1_A9_MOVW     ] = rl78Morph_1_A9_MOVW     ,
    [RL78_IT_1_AA_MOVW     ] = rl78Morph_1_AA_MOVW     ,
    [RL78_IT_1_AB_MOVW     ] = rl78Morph_1_AB_MOVW     ,
    [RL78_IT_1_AC_MOVW     ] = rl78Morph_1_AC_MOVW     ,
    [RL78_IT_1_AD_MOVW     ] = rl78Morph_1_AD_MOVW     ,
    [RL78_IT_1_AE_MOVW     ] = rl78Morph_1_AE_MOVW     ,
    [RL78_IT_1_AF_MOVW     ] = rl78Morph_1_AF_MOVW     ,
    [RL78_IT_1_B0_DEC      ] = rl78Morph_1_B0_DEC      ,
    [RL78_IT_1_B2_DECW     ] = rl78Morph_1_B2_DECW     ,
    [RL78_IT_1_B4_DEC      ] = rl78Morph_1_B4_DEC      ,
    [RL78_IT_1_B6_DECW     ] = rl78Morph_1_B6_DECW     ,
    [RL78_IT_1_BX_DECW     ] = rl78Morph_1_BX_DECW     ,
    [RL78_IT_1_B8_MOVW     ] = rl78Morph_1_B8_MOVW     ,
    [RL78_IT_1_B9_MOVW     ] = rl78Morph_1_B9_MOVW     ,
    [RL78_IT_1_BA_MOVW     ] = rl78Morph_1_BA_MOVW     ,
    [RL78_IT_1_BB_MOVW     ] = rl78Morph_1_BB_MOVW     ,
    [RL78_IT_1_BC_MOVW     ] = rl78Morph_1_BC_MOVW     ,
    [RL78_IT_1_BD_MOVW     ] = rl78Morph_1_BD_MOVW     ,
    [RL78_IT_1_BE_MOVW     ] = rl78Morph_1_BE_MOVW     ,
    [RL78_IT_1_BF_MOVW     ] = rl78Morph_1_BF_MOVW     ,
    [RL78_IT_1_CX_POP      ] = rl78Morph_1_CX_POP      ,
    [RL78_IT_1_CY_PUSH     ] = rl78Morph_1_CY_PUSH     ,
    [RL78_IT_1_C8_MOV      ] = rl78Morph_1_C8_MOV      ,
    [RL78_IT_1_C9_MOVW     ] = rl78Morph_1_C9_MOVW     ,
    [RL78_IT_1_CA_MOV      ] = rl78Morph_1_CA_MOV      ,
    [RL78_IT_1_CB_MOVW     ] = rl78Morph_1_CB_MOVW     ,
    [RL78_IT_1_CC_MOV      ] = rl78Morph_1_CC_MOV      ,
    [RL78_IT_1_CD_MOV      ] = rl78Morph_1_CD_MOV      ,
    [RL78_IT_1_CE_MOV_SFR  ] = rl78Morph_1_CE_MOV_SFR  ,
    [RL78_IT_1_CE_MOV_PSW  ] = rl78Morph_1_CE_MOV_PSW  ,
    [RL78_IT_1_CE_MOV_CS   ] = rl78Morph_1_CE_MOV_CS   ,
    [RL78_IT_1_CE_MULHU    ] = rl78Morph_1_CE_MULHU    ,
    [RL78_IT_1_CE_MULH     ] = rl78Morph_1_CE_MULH     ,
    [RL78_IT_1_CE_DIVHU    ] = rl78Morph_1_CE_DIVHU    ,
    [RL78_IT_1_CE_DIVWU    ] = rl78Morph_1_CE_DIVWU    ,
    [RL78_IT_1_CE_MACHU    ] = rl78Morph_1_CE_MACHU    ,
    [RL78_IT_1_CE_MACH     ] = rl78Morph_1_CE_MACH     ,
    [RL78_IT_1_CF_MOV      ] = rl78Morph_1_CF_MOV      ,
    [RL78_IT_1_DX_CMP0     ] = rl78Morph_1_DX_CMP0     ,
    [RL78_IT_1_D4_CMP0     ] = rl78Morph_1_D4_CMP0     ,
    [RL78_IT_1_D5_CMP0     ] = rl78Morph_1_D5_CMP0     ,
    [RL78_IT_1_D6_MULU     ] = rl78Morph_1_D6_MULU     ,
    [RL78_IT_1_D7_RET      ] = rl78Morph_1_D7_RET      ,
    [RL78_IT_1_D8_MOV      ] = rl78Morph_1_D8_MOV      ,
    [RL78_IT_1_D9_MOV      ] = rl78Morph_1_D9_MOV      ,
    [RL78_IT_1_DC_BC       ] = rl78Morph_1_DC_BC       ,
    [RL78_IT_1_DD_BZ       ] = rl78Morph_1_DD_BZ       ,
    [RL78_IT_1_DE_BNC      ] = rl78Morph_1_DE_BNC      ,
    [RL78_IT_1_DF_BNZ      ] = rl78Morph_1_DF_BNZ      ,
    [RL78_IT_1_EX_ONEB     ] = rl78Morph_1_EX_ONEB     ,
    [RL78_IT_1_E4_ONEB     ] = rl78Morph_1_E4_ONEB     ,
    [RL78_IT_1_E5_ONEB     ] = rl78Morph_1_E5_ONEB     ,
    [RL78_IT_1_E6_ONEW     ] = rl78Morph_1_E6_ONEW     ,
    [RL78_IT_1_E7_ONEW     ] = rl78Morph_1_E7_ONEW     ,
    [RL78_IT_1_E8_MOV      ] = rl78Morph_1_E8_MOV      ,
    [RL78_IT_1_E9_MOV      ] = rl78Morph_1_E9_MOV      ,
    [RL78_IT_1_EC_BR       ] = rl78Morph_1_EC_BR       ,
    [RL78_IT_1_ED_BR       ] = rl78Morph_1_ED_BR       ,
    [RL78_IT_1_EE_BR       ] = rl78Morph_1_EE_BR       ,
    [RL78_IT_1_EF_BR       ] = rl78Morph_1_EF_BR       ,
    [RL78_IT_1_FX_CLRB     ] = rl78Morph_1_FX_CLRB     ,
    [RL78_IT_1_F4_CLRB     ] = rl78Morph_1_F4_CLRB     ,
    [RL78_IT_1_F5_CLRB     ] = rl78Morph_1_F5_CLRB     ,
    [RL78_IT_1_F6_CLRW     ] = rl78Morph_1_F6_CLRW     ,
    [RL78_IT_1_F7_CLRW     ] = rl78Morph_1_F7_CLRW     ,
    [RL78_IT_1_F8_MOV      ] = rl78Morph_1_F8_MOV      ,
    [RL78_IT_1_F9_MOV      ] = rl78Morph_1_F9_MOV      ,
    [RL78_IT_1_FC_CALL     ] = rl78Morph_1_FC_CALL     ,
    [RL78_IT_1_FD_CALL     ] = rl78Morph_1_FD_CALL     ,
    [RL78_IT_1_FE_CALL     ] = rl78Morph_1_FE_CALL     ,
    [RL78_IT_1_XA_MOVW     ] = rl78Morph_1_XA_MOVW     ,
    [RL78_IT_1_XB_MOVW     ] = rl78Morph_1_XB_MOVW     ,

    [RL78_IT_2_0X_ADD      ] = rl78Morph_2_0X_ADD      ,
    [RL78_IT_2_09_ADDW     ] = rl78Morph_2_09_ADDW     ,
    [RL78_IT_2_0Y_ADD      ] = rl78Morph_2_0Y_ADD      ,
    [RL78_IT_2_1X_ADDC     ] = rl78Morph_2_1X_ADDC     ,
    [RL78_IT_2_1Y_ADDC     ] = rl78Morph_2_1Y_ADDC     ,
    [RL78_IT_2_2X_SUB      ] = rl78Morph_2_2X_SUB      ,
    [RL78_IT_2_29_SUBW     ] = rl78Morph_2_29_SUBW     ,
    [RL78_IT_2_2Y_SUB      ] = rl78Morph_2_2Y_SUB      ,
    [RL78_IT_2_3X_SUBC     ] = rl78Morph_2_3X_SUBC     ,
    [RL78_IT_2_3Y_SUBC     ] = rl78Morph_2_3Y_SUBC     ,
    [RL78_IT_2_4X_CMP      ] = rl78Morph_2_4X_CMP      ,
    [RL78_IT_2_49_CMPW     ] = rl78Morph_2_49_CMPW     ,
    [RL78_IT_2_4Y_CMP      ] = rl78Morph_2_4Y_CMP      ,
    [RL78_IT_2_5X_AND      ] = rl78Morph_2_5X_AND      ,
    [RL78_IT_2_59_INC      ] = rl78Morph_2_59_INC      ,
    [RL78_IT_2_5Y_AND      ] = rl78Morph_2_5Y_AND      ,
    [RL78_IT_2_6X_OR       ] = rl78Morph_2_6X_OR       ,
    [RL78_IT_2_69_DEC      ] = rl78Morph_2_69_DEC      ,
    [RL78_IT_2_6Y_OR       ] = rl78Morph_2_6Y_OR       ,
    [RL78_IT_2_7X_XOR      ] = rl78Morph_2_7X_XOR      ,
    [RL78_IT_2_79_INCW     ] = rl78Morph_2_79_INCW     ,
    [RL78_IT_2_7Y_XOR      ] = rl78Morph_2_7Y_XOR      ,
    [RL78_IT_2_80_ADD      ] = rl78Morph_2_80_ADD      ,
    [RL78_IT_2_82_ADD      ] = rl78Morph_2_82_ADD      ,
    [RL78_IT_2_89_DECW     ] = rl78Morph_2_89_DECW     ,
    [RL78_IT_2_8X_XCH      ] = rl78Morph_2_8X_XCH      ,
    [RL78_IT_2_90_ADDC     ] = rl78Morph_2_90_ADDC     ,
    [RL78_IT_2_92_ADDC     ] = rl78Morph_2_92_ADDC     ,
    [RL78_IT_2_A0_SUB      ] = rl78Morph_2_A0_SUB      ,
    [RL78_IT_2_A2_SUB      ] = rl78Morph_2_A2_SUB      ,
    [RL78_IT_2_A8_XCH      ] = rl78Morph_2_A8_XCH      ,
    [RL78_IT_2_A9_XCH      ] = rl78Morph_2_A9_XCH      ,
    [RL78_IT_2_AA_XCH      ] = rl78Morph_2_AA_XCH      ,
    [RL78_IT_2_AB_XCH      ] = rl78Morph_2_AB_XCH      ,
    [RL78_IT_2_AC_XCH      ] = rl78Morph_2_AC_XCH      ,
    [RL78_IT_2_AD_XCH      ] = rl78Morph_2_AD_XCH      ,
    [RL78_IT_2_AE_XCH      ] = rl78Morph_2_AE_XCH      ,
    [RL78_IT_2_AF_XCH      ] = rl78Morph_2_AF_XCH      ,
    [RL78_IT_2_B0_SUBC     ] = rl78Morph_2_B0_SUBC     ,
    [RL78_IT_2_B2_SUBC     ] = rl78Morph_2_B2_SUBC     ,
    [RL78_IT_2_B8_MOV      ] = rl78Morph_2_B8_MOV      ,
    [RL78_IT_2_B9_XCH      ] = rl78Morph_2_B9_XCH      ,
    [RL78_IT_2_C0_CMP      ] = rl78Morph_2_C0_CMP      ,
    [RL78_IT_2_C2_CMP      ] = rl78Morph_2_C2_CMP      ,
    [RL78_IT_2_C3_BH       ] = rl78Morph_2_C3_BH       ,
    [RL78_IT_2_C8_SKC      ] = rl78Morph_2_C8_SKC      ,
    [RL78_IT_2_C9_MOV      ] = rl78Morph_2_C9_MOV      ,
    [RL78_IT_2_CB_BR       ] = rl78Morph_2_CB_BR       ,
    [RL78_IT_2_CC_BRK      ] = rl78Morph_2_CC_BRK      ,
    [RL78_IT_2_CD_POP      ] = rl78Morph_2_CD_POP      ,
    [RL78_IT_2_CE_MOVS     ] = rl78Morph_2_CE_MOVS     ,
    [RL78_IT_2_D0_AND      ] = rl78Morph_2_D0_AND      ,
    [RL78_IT_2_D2_AND      ] = rl78Morph_2_D2_AND      ,
    [RL78_IT_2_D3_BNH      ] = rl78Morph_2_D3_BNH      ,
    [RL78_IT_2_D8_SKNC     ] = rl78Morph_2_D8_SKNC     ,
    [RL78_IT_2_D9_MOV      ] = rl78Morph_2_D9_MOV      ,
    [RL78_IT_2_DB_ROR      ] = rl78Morph_2_DB_ROR      ,
    [RL78_IT_2_DC_ROLC     ] = rl78Morph_2_DC_ROLC     ,
    [RL78_IT_2_DD_PUSH     ] = rl78Morph_2_DD_PUSH     ,
    [RL78_IT_2_DE_CMPS     ] = rl78Morph_2_DE_CMPS     ,
    [RL78_IT_2_E0_OR       ] = rl78Morph_2_E0_OR       ,
    [RL78_IT_2_E2_OR       ] = rl78Morph_2_E2_OR       ,
    [RL78_IT_2_E3_SKH      ] = rl78Morph_2_E3_SKH      ,
    [RL78_IT_2_E8_SKZ      ] = rl78Morph_2_E8_SKZ      ,
    [RL78_IT_2_E9_MOV      ] = rl78Morph_2_E9_MOV      ,
    [RL78_IT_2_EB_ROL      ] = rl78Morph_2_EB_ROL      ,
    [RL78_IT_2_EC_RETB     ] = rl78Morph_2_EC_RETB     ,
    [RL78_IT_2_ED_HALT     ] = rl78Morph_2_ED_HALT     ,
    [RL78_IT_2_F0_XOR      ] = rl78Morph_2_F0_XOR      ,
    [RL78_IT_2_F2_XOR      ] = rl78Morph_2_F2_XOR      ,
    [RL78_IT_2_F3_SKNH     ] = rl78Morph_2_F3_SKNH     ,
    [RL78_IT_2_F8_SKNZ     ] = rl78Morph_2_F8_SKNZ     ,
    [RL78_IT_2_F9_MOV      ] = rl78Morph_2_F9_MOV      ,
    [RL78_IT_2_FB_RORC     ] = rl78Morph_2_FB_RORC     ,
    [RL78_IT_2_FC_RETI     ] = rl78Morph_2_FC_RETI     ,
    [RL78_IT_2_FD_STOP     ] = rl78Morph_2_FD_STOP     ,
    [RL78_IT_2_XE_ROLWC    ] = rl78Morph_2_XE_ROLWC    ,
    [RL78_IT_2_XF_SEL      ] = rl78Morph_2_XF_SEL      ,
    [RL78_IT_2_XA_CALL     ] = rl78Morph_2_XA_CALL     ,
    [RL78_IT_2_XX_CALLT    ] = rl78Morph_2_XX_CALLT    ,

    [RL78_IT_3_X0_SET1     ] = rl78Morph_3_X0_SET1     ,
    [RL78_IT_3_X1_MOV1     ] = rl78Morph_3_X1_MOV1     ,
    [RL78_IT_3_X2_SET1     ] = rl78Morph_3_X2_SET1     ,
    [RL78_IT_3_X3_CLR1     ] = rl78Morph_3_X3_CLR1     ,
    [RL78_IT_3_X4_MOV1     ] = rl78Morph_3_X4_MOV1     ,
    [RL78_IT_3_X5_AND1     ] = rl78Morph_3_X5_AND1     ,
    [RL78_IT_3_X6_OR1      ] = rl78Morph_3_X6_OR1      ,
    [RL78_IT_3_X7_XOR1     ] = rl78Morph_3_X7_XOR1     ,
    [RL78_IT_3_X8_CLR1     ] = rl78Morph_3_X8_CLR1     ,
    [RL78_IT_3_X9_MOV1     ] = rl78Morph_3_X9_MOV1     ,
    [RL78_IT_3_XA_SET1     ] = rl78Morph_3_XA_SET1     ,
    [RL78_IT_3_XB_CLR1     ] = rl78Morph_3_XB_CLR1     ,
    [RL78_IT_3_XC_MOV1     ] = rl78Morph_3_XC_MOV1     ,
    [RL78_IT_3_XD_AND1     ] = rl78Morph_3_XD_AND1     ,
    [RL78_IT_3_XE_OR1      ] = rl78Morph_3_XE_OR1      ,
    [RL78_IT_3_XF_XOR1     ] = rl78Morph_3_XF_XOR1     ,
    [RL78_IT_3_7A_EI       ] = rl78Morph_3_7A_EI       ,
    [RL78_IT_3_7B_DI       ] = rl78Morph_3_7B_DI       ,
    [RL78_IT_3_80_SET1     ] = rl78Morph_3_80_SET1     ,
    [RL78_IT_3_88_CLR1     ] = rl78Morph_3_88_CLR1     ,
    [RL78_IT_3_C0_NOT1     ] = rl78Morph_3_C0_NOT1     ,
    [RL78_IT_3_Y1_MOV1     ] = rl78Morph_3_Y1_MOV1     ,
    [RL78_IT_3_Y2_SET1     ] = rl78Morph_3_Y2_SET1     ,
    [RL78_IT_3_Y3_CLR1     ] = rl78Morph_3_Y3_CLR1     ,
    [RL78_IT_3_Y4_MOV1     ] = rl78Morph_3_Y4_MOV1     ,
    [RL78_IT_3_Y5_AND1     ] = rl78Morph_3_Y5_AND1     ,
    [RL78_IT_3_Y6_OR1      ] = rl78Morph_3_Y6_OR1      ,
    [RL78_IT_3_Y7_XOR1     ] = rl78Morph_3_Y7_XOR1     ,
    [RL78_IT_3_Y9_MOV1     ] = rl78Morph_3_Y9_MOV1     ,
    [RL78_IT_3_YA_SET1     ] = rl78Morph_3_YA_SET1     ,
    [RL78_IT_3_YB_CLR1     ] = rl78Morph_3_YB_CLR1     ,
    [RL78_IT_3_YC_MOV1     ] = rl78Morph_3_YC_MOV1     ,
    [RL78_IT_3_YD_AND1     ] = rl78Morph_3_YD_AND1     ,
    [RL78_IT_3_YE_OR1      ] = rl78Morph_3_YE_OR1      ,
    [RL78_IT_3_YF_XOR1     ] = rl78Morph_3_YF_XOR1     ,

    [RL78_IT_4_X0_BTCLR    ] = rl78Morph_4_X0_BTCLR    ,
    [RL78_IT_4_X1_BTCLR    ] = rl78Morph_4_X1_BTCLR    ,
    [RL78_IT_4_X2_BT       ] = rl78Morph_4_X2_BT       ,
    [RL78_IT_4_X3_BT       ] = rl78Morph_4_X3_BT       ,
    [RL78_IT_4_X4_BF       ] = rl78Morph_4_X4_BF       ,
    [RL78_IT_4_X5_BF       ] = rl78Morph_4_X5_BF       ,
    [RL78_IT_4_X7_SHL      ] = rl78Morph_4_X7_SHL      ,
    [RL78_IT_4_X8_SHL      ] = rl78Morph_4_X8_SHL      ,
    [RL78_IT_4_X9_SHL      ] = rl78Morph_4_X9_SHL      ,
    [RL78_IT_4_XA_SHR      ] = rl78Morph_4_XA_SHR      ,
    [RL78_IT_4_XB_SAR      ] = rl78Morph_4_XB_SAR      ,
    [RL78_IT_4_Y0_BTCLR    ] = rl78Morph_4_Y0_BTCLR    ,
    [RL78_IT_4_Y1_BTCLR    ] = rl78Morph_4_Y1_BTCLR    ,
    [RL78_IT_4_Y2_BT       ] = rl78Morph_4_Y2_BT       ,
    [RL78_IT_4_Y3_BT       ] = rl78Morph_4_Y3_BT       ,
    [RL78_IT_4_Y4_BF       ] = rl78Morph_4_Y4_BF       ,
    [RL78_IT_4_Y5_BF       ] = rl78Morph_4_Y5_BF       ,
    [RL78_IT_4_XC_SHLW     ] = rl78Morph_4_XC_SHLW     ,
    [RL78_IT_4_XD_SHLW     ] = rl78Morph_4_XD_SHLW     ,
    [RL78_IT_4_XE_SHRW     ] = rl78Morph_4_XE_SHRW     ,
    [RL78_IT_4_XF_SARW     ] = rl78Morph_4_XF_SARW

};

//
// Called for an undecoded instruction
//
static void undecoded(
    vmiProcessorP processor,
    Uns32         thisPC,
    Uns32         instr0,
    Uns32         instr1,
    Uns32         instr2,
    Uns32         instr3,
    Uns32         instr4
) {
    // report that undecoded instruction was encountered
    vmiPrintf(
        "CPU '%s' 0x%08x:0x%02x 0x%02x 0x%02x 0x%02x 0x%02x *** undecoded instruction: exiting ***\n",
        vmirtProcessorName(processor),
        thisPC,
        instr0, instr1, instr2, instr3, instr4
    );

    // exit the CPU
    vmirtExit(processor);
}

//
// Default morpher callback
//
static RL78_DISPATCH_FN(morphDefault) {

    // print message warning about the undecoded instruction
    vmimtArgProcessor();
    vmimtArgUns32((Uns32)thisPC);
    vmimtArgUns32(instr[0]);
    vmimtArgUns32(instr[1]);
    vmimtArgUns32(instr[2]);
    vmimtArgUns32(instr[3]);
    vmimtArgUns32(instr[4]);
    vmimtCall((vmiCallFn) undecoded);
}

//
// Create code for the RL78 instruction at the simulated address referenced
// by 'thisPC'.
//
// #define VMI_MORPH_FN(_NAME) void _NAME( 
//     vmiProcessorP processor,    
//     Addr          thisPC,       
//     Uns8          inDelaySlot,  
//     Bool          firstInBlock, 
//     Bool          emitTrace     
// )
VMI_MORPH_FN(rl78MorphInstruction) {
    rl78Decode((rl78P)processor, thisPC, &dispatchTable, morphDefault, 0);
}


//#define VMI_RD_WR_SNAP_FN(_NAME) Uns32 _NAME( 
//    vmiProcessorP processor,    
//    Addr          address,      
//    Uns32         bytes         
//)
VMI_RD_WR_SNAP_FN(rl78RdSnapCB) {
    return bytes;
}

VMI_RD_WR_SNAP_FN(rl78WrSnapCB) {
    return bytes;
}
