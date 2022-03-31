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



void doMulopRR(Uns32 bits, vmiBinop op, vmiReg ra, vmiReg rb) {

    // rdh:rdl = ra*rb

    vmimtMulopRRR(               //void vmimtMulopRRR(
        bits,                    //    Uns32      bits,
        op,                      //    vmiBinop   op,
        rb,                      //    vmiReg     rdh,
        ra,                      //    vmiReg     rdl,
        ra,                      //    vmiReg     ra,
        rb,                      //    vmiReg     rb,
        0 );                     //    vmiFlagsCP flags
}

void doDivopRR(Uns32 bits, vmiBinop op, vmiReg ra, vmiReg rb) {

    vmiLabelP lbl_divzero = vmimtNewLabel();
    vmiLabelP lbl_exit    = vmimtNewLabel();

    vmimtCompareRCJumpLabel(     // void vmimtCompareRCJumpLabel(
        bits,                    //    Uns32        bits,
        vmi_COND_EQ,             //    vmiCondition cond,
        rb,                      //    vmiReg       r,
        0,                       //    Uns64        c,
        lbl_divzero);            //    vmiLabelP    toLabel

    // rdd = rah:ral/rb; rdr = rah:ral%rb

    vmimtDivopRRR(               //void vmimtDivopRRR(
        bits,                    //    Uns32      bits,
        op,                      //    vmiBinop   op,
        ra,                      //    vmiReg     rdd,
        rb,                      //    vmiReg     rdr,
        VMI_NOREG,               //    vmiReg     rah,
        ra,                      //    vmiReg     ral,
        rb,                      //    vmiReg     rb,
        0 );                     //    vmiFlagsCP flags

    vmimtUncondJumpLabel(lbl_exit);

vmimtInsertLabel(lbl_divzero);
    vmimtMoveRR(bits, rb, ra);                // rb <- ra
    vmimtMoveRC(bits, ra, ((Uns64) 1 << bits) - 1);    // ra <- 0xFFFF

vmimtInsertLabel(lbl_exit);
    ;
}


const vmiFlags flag_MACH = {
    RL78_CARRY_CONST,           // offset to carry in flag
    {
        [vmi_CF] = VMI_NOFLAG_CONST,       // offset to carry out flag
        [vmi_PF] = VMI_NOFLAG_CONST,       // parity flag not used
        [vmi_ZF] = VMI_NOFLAG_CONST,       // zero flag not used
        [vmi_SF] = RL78_AUXCARRY_CONST,    // sign flag not used        // Set AC flag when calculation result is negative.
        [vmi_OF] = RL78_CARRY_CONST        // offset to overflow flag    // Set Carry flag when overflow
    }
};

void doMACH(vmiBinop op, vmiReg ra, vmiReg rb) {

    // rdh:rdl = ra*rb

    vmimtMulopRRR(               //void vmimtMulopRRR(
        16,                      //    Uns32      bits,
        op,                      //    vmiBinop   op,
        RL78_TMP_H,              //    vmiReg     rdh,
        RL78_TMP,                //    vmiReg     rdl,
        ra,                      //    vmiReg     ra,
        rb,                      //    vmiReg     rb,
        0 );                     //    vmiFlagsCP flags

    if (op == vmi_MUL ) {        // MACHU

        // - The content of AX register and the content of BC register are multiplied; the result and the content of MACR register
        //   are accumulated and then stored in MACR register.
        // - As a result of accumulation, when overflow occurs, CY flag is set (1), and when not, CY flag is cleared (0).
        // - AC flag becomes 0.
        // - Before multiplication and accumulation, set an initial value in MACR register. In addition since MACR register is fixed,
        //   if more than one result of multiplication and accumulation are needed, save the content of MACR register first.

        vmimtBinopRR(32, vmi_ADD, RL78_MACR, RL78_TMP, &flag__C);
        vmimtMoveRC(8, RL78_AUXCARRY, 0);
    }
    if (op == vmi_IMUL) {        // MACH

        // - The content of AX register and the content of BC register are multiplied; the result and the content of MACR register
        //   are accumulated and then stored in MACR register.
        // - As a result of accumulation, if overflow occurs, CY flag is set (1), and if not, CY flag is cleared (0). The overflow
        //   means cases that an added result of a plus accumulated value and a plus multiplied value has exceeded
        //   7FFFFFFFH and that an added result of a minus accumulated value and a minus multiplied value has exceeded
        //   80000000H.
        // - As a result of operations, when MACR register has a plus value, AC flag is cleared (0), and when it has a minus
        //   value, AC flag is set (1).
        // - Before multiplication and accumulation, set an initial value in MACR register. In addition since MACR register is fixed,
        //   if more than one result of multiplication and accumulation are needed, save the content of MACR register first.

        vmimtBinopRR(32, vmi_ADD, RL78_MACR, RL78_TMP, &flag_MACH);
    }

}
