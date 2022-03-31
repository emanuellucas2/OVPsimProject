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

// standard includes
#include <stdio.h>
#include <string.h>                // strcpy, strstr

// VMI header files
#include "vmi/vmiCxt.h"

// model header files
#include "rl78Decode.h"
#include "rl78Functions.h"
#include "rl78Structure.h"        // R_A
#include "rl78Utils.h"            // snprint_hex
#include "rl78Message.h"        // MY_ASSERT

static void        fillInstructionBytes(rl78P rl78, Uns32 n, Uns32 thisPC, char *buf);
static const char* skipPrefix(rl78P rl78);

static const char* REGNAME_H[4] = { "AX", "BC", "DE", "HL" };
static const char* REGNAME_B[8] = { "X", "A", "C", "B", "E", "D", "L", "H" };

static char hex[32 + 1];

#define UNUSED   __attribute__((unused))

#define    PRE()    \
    UNUSED Uns32    cur = rl78->len_instPrefix + rl78->len_instMnem;    \
    UNUSED Uns32    op1 = 0;    /* operand in instruction bytes */        \
    UNUSED Uns32    op2 = 0;    /* operand in instruction bytes */        \
    UNUSED Uns32    ix1 = 0;    /* bit number of processing */            \
    UNUSED Uns32    dis = 0;    /* displacement */                        \
    UNUSED Uns32    dmy = 0;                                            \
    fillInstructionBytes(rl78, 32, thisPC, hex);


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

#define IDX3(idx)        /* 3 means decode 3 bits */                \
    idx = GETBIT(4, 3);

#define IDX4(idx)        /* 4 means decode 4 bits */                \
    idx = GETBIT(4, 4);

#define BIT3(opx)        /* 3 means decode 3 bits */                \
    opx = GETBIT(0, 3);

#define BIT2(opx)        /* 2 means decode 2 bits */                \
    opx = GETBIT(1, 2);

#define BIT(opx, lsb, len)                                        \
    opx = GETBIT(lsb, len);


// address adjustment
#define    SADDR(opx)                    IMM1(opx); opx += (opx < 0x20) ? 0xFFF00 : 0xFFE00;        // FFE20h-FFF1Fh
#define    SFR(opx)                    IMM1(opx); opx += 0xFFF00;
#define    DMY1(opx)                    IMM1(opx);


static inline       char* t_abs20(Uns32 val) { static char buf_abs20[16]; sprintf(buf_abs20, "!!0x%05x", val); return buf_abs20; }
static inline       char* t_abs16(Uns32 val) { static char buf_abs16[16]; sprintf(buf_abs16, "!0x%05x" , val); return buf_abs16; }
static inline       char* t_adr8 (Uns32 val) { static char buf_adr8 [16]; sprintf(buf_adr8 , "0x%05x"  , val); return buf_adr8 ; }
static inline       char* t_rel16(Uns32 val) { static char buf_rel16[16]; sprintf(buf_rel16, "$!0x%04x", val); return buf_rel16; }
static inline       char* t_rel8 (Uns32 val) { static char buf_rel8 [16]; sprintf(buf_rel8 , "$0x%02x" , val); return buf_rel8 ; }
static inline       char* t_imm16(Uns32 val) { static char buf_imm16[16]; sprintf(buf_imm16, "#0x%04x" , val); return buf_imm16; }
static inline       char* t_imm8 (Uns32 val) { static char buf_imm8 [16]; sprintf(buf_imm8 , "#0x%02x" , val); return buf_imm8 ; }
static inline       char* t_dis16(Uns32 val) { static char buf_dis16[16]; sprintf(buf_dis16, "0x%04x"  , val); return buf_dis16; }
static inline       char* t_dis8 (Uns32 val) { static char buf_dis8 [16]; sprintf(buf_dis8 , "0x%02x"  , val); return buf_dis8 ; }

static inline const char* t_reg16(Uns32 val) { return REGNAME_H[val]; }
static inline const char* t_reg8 (Uns32 val) { return REGNAME_B[val]; }

static const char* replace_es(rl78P rl78, const char* txt_tmpl) {

    static char txt_fmt[100 + 1];

    strcpy(txt_fmt, txt_tmpl);

    if (rl78->len_instPrefix == 0) {        // no prefix
        char* pidx = strstr(txt_fmt, "ES:");

        if (pidx != NULL) {
            Uns32 idx = pidx - txt_fmt;
            strcpy(&txt_fmt[idx], &txt_tmpl[idx + 3]);
        }
    }

    return txt_fmt;
}

#define PREFIX_FORMAT                "%s\t%d\t%s"
#define REP(tmpl)                    replace_es(rl78, tmpl)

//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wunused-variable"
//#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

// #define RL78_DISPATCH_FN(_NAME) void _NAME( 
//     rl78P rl78,         
//     Uns32 thisPC,       
//     Uns8* instr,        
//     void *userData      
// )
static RL78_DISPATCH_FN(rl78Dis_1_00_NOP        ) { PRE();                                              sprintf(userData, REP(PREFIX_FORMAT "NOP     "                    ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // NOP
static RL78_DISPATCH_FN(rl78Dis_1_02_ADDW       ) { PRE();            op1=R_AX ;            IMM2(op2);  sprintf(userData, REP(PREFIX_FORMAT "ADDW    AX, ES:%s"            ), hex, __LINE__, skipPrefix(rl78),                    t_abs16(op2) ); }    // ADDW    AX, !addr16
static RL78_DISPATCH_FN(rl78Dis_1_04_ADDW       ) { PRE();            op1=R_AX ;            IMM2(op2);  sprintf(userData, REP(PREFIX_FORMAT "ADDW    AX, %s"            ), hex, __LINE__, skipPrefix(rl78),                    t_imm16(op2) ); }    // ADDW    AX, #word
static RL78_DISPATCH_FN(rl78Dis_1_06_ADDW       ) { PRE();            op1=R_AX ;            SADDR(op2); sprintf(userData, REP(PREFIX_FORMAT "ADDW    AX, %s"            ), hex, __LINE__, skipPrefix(rl78),                    t_adr8 (op2) ); }    // ADDW    AX, saddrp
static RL78_DISPATCH_FN(rl78Dis_1_0X_ADDW       ) { PRE();            op1=R_AX ;            BIT2(op2);  sprintf(userData, REP(PREFIX_FORMAT "ADDW    AX, %s"            ), hex, __LINE__, skipPrefix(rl78),                    t_reg16(op2) ); }    // ADDW    AX, ??
static RL78_DISPATCH_FN(rl78Dis_1_08_XCH        ) { PRE();            op1=R_A  ;            op2=R_X  ;  sprintf(userData, REP(PREFIX_FORMAT "XCH     A, X"                ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // XCH     A, X
static RL78_DISPATCH_FN(rl78Dis_1_09_MOV        ) { PRE();            op1=R_A  ; IMM2(dis); op2=R_B  ;  sprintf(userData, REP(PREFIX_FORMAT "MOV     A, ES:%s[B]"        ), hex, __LINE__, skipPrefix(rl78),                    t_dis16(dis) ); }    // MOV     A, word[B]
static RL78_DISPATCH_FN(rl78Dis_1_0A_ADD        ) { PRE();            SADDR(op1);           IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "ADD     %s, %s"            ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1),      t_imm8 (op2) ); }    // ADD     saddr, #byte
static RL78_DISPATCH_FN(rl78Dis_1_0B_ADD        ) { PRE();            op1=R_A  ;            SADDR(op2); sprintf(userData, REP(PREFIX_FORMAT "ADD     A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_adr8 (op2) ); }    // ADD     A, saddr
static RL78_DISPATCH_FN(rl78Dis_1_0C_ADD        ) { PRE();            op1=R_A  ;            IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "ADD     A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_imm8 (op2) ); }    // ADD     A, #byte
static RL78_DISPATCH_FN(rl78Dis_1_0D_ADD        ) { PRE();            op1=R_A  ;            op2=R_HL ;  sprintf(userData, REP(PREFIX_FORMAT "ADD     A, ES:[HL]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // ADD     A, [HL]
static RL78_DISPATCH_FN(rl78Dis_1_0E_ADD        ) { PRE();            op1=R_A  ; IMM1(dis); op2=R_HL ;  sprintf(userData, REP(PREFIX_FORMAT "ADD     A, ES:[HL+%s]"        ), hex, __LINE__, skipPrefix(rl78),                    t_dis8 (dis) ); }    // ADD     A, [HL+byte]
static RL78_DISPATCH_FN(rl78Dis_1_0F_ADD        ) { PRE();            op1=R_A  ;            IMM2(op2);  sprintf(userData, REP(PREFIX_FORMAT "ADD     A, ES:%s"            ), hex, __LINE__, skipPrefix(rl78),                    t_abs16(op2) ); }    // ADD     A, !addr16
static RL78_DISPATCH_FN(rl78Dis_1_10_ADDW       ) { PRE();            op1=R_SP ;            IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "ADDW    SP, %s"            ), hex, __LINE__, skipPrefix(rl78),                    t_imm8 (op2) ); }    // ADDW    SP, #byte
static RL78_DISPATCH_FN(rl78Dis_1_11_PREFIX     ) { PRE();                                              sprintf(userData, REP(PREFIX_FORMAT "PREFIX  "                    ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // PREFIX
static RL78_DISPATCH_FN(rl78Dis_1_1X_MOVW       ) { PRE();            BIT2(op1);            op2=R_AX ;  sprintf(userData, REP(PREFIX_FORMAT "MOVW    %s, AX"            ), hex, __LINE__, skipPrefix(rl78), t_reg16(op1)                    ); }    // MOVW    ??, AX
static RL78_DISPATCH_FN(rl78Dis_1_1Y_MOVW       ) { PRE();            op1=R_AX ;            BIT2(op2);  sprintf(userData, REP(PREFIX_FORMAT "MOVW    AX, %s"            ), hex, __LINE__, skipPrefix(rl78),                    t_reg16(op2) ); }    // MOVW    AX, ??
static RL78_DISPATCH_FN(rl78Dis_1_18_MOV        ) { PRE(); IMM2(dis); op1=R_B  ;            op2=R_A  ;  sprintf(userData, REP(PREFIX_FORMAT "MOV     ES:%s[B], A"        ), hex, __LINE__, skipPrefix(rl78), t_dis16(dis)                    ); }    // MOV     word[B], A
static RL78_DISPATCH_FN(rl78Dis_1_19_MOV        ) { PRE(); IMM2(dis); op1=R_B  ;            IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "MOV     ES:%s[B], %s"        ), hex, __LINE__, skipPrefix(rl78), t_dis16(dis),      t_imm8 (op2) ); }    // MOV     word[B], #byte
static RL78_DISPATCH_FN(rl78Dis_1_1A_ADDC       ) { PRE();            SADDR(op1);           IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "ADDC    %s, %s"            ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1),      t_imm8 (op2) ); }    // ADDC    saddr, #byte
static RL78_DISPATCH_FN(rl78Dis_1_1B_ADDC       ) { PRE();            op1=R_A  ;            SADDR(op2); sprintf(userData, REP(PREFIX_FORMAT "ADDC    A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_adr8 (op2) ); }    // ADDC    A, saddr
static RL78_DISPATCH_FN(rl78Dis_1_1C_ADDC       ) { PRE();            op1=R_A  ;            IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "ADDC    A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_imm8 (op2) ); }    // ADDC    A, #byte
static RL78_DISPATCH_FN(rl78Dis_1_1D_ADDC       ) { PRE();            op1=R_A  ;            op2=R_HL ;  sprintf(userData, REP(PREFIX_FORMAT "ADDC    A, ES:[HL]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // ADDC    A, [HL]
static RL78_DISPATCH_FN(rl78Dis_1_1E_ADDC       ) { PRE();            op1=R_A  ; IMM1(dis); op2=R_HL ;  sprintf(userData, REP(PREFIX_FORMAT "ADDC    A, ES:[HL+%s]"        ), hex, __LINE__, skipPrefix(rl78),                    t_dis8 (dis) ); }    // ADDC    A, [HL+byte]
static RL78_DISPATCH_FN(rl78Dis_1_1F_ADDC       ) { PRE();            op1=R_A  ;            IMM2(op2);  sprintf(userData, REP(PREFIX_FORMAT "ADDC    A, ES:%s"            ), hex, __LINE__, skipPrefix(rl78),                    t_abs16(op2) ); }    // ADDC    A, !addr16
static RL78_DISPATCH_FN(rl78Dis_1_20_SUBW       ) { PRE();            op1=R_SP ;            IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "SUBW    SP, %s"            ), hex, __LINE__, skipPrefix(rl78),                    t_imm8 (op2) ); }    // SUBW    SP, #byte
static RL78_DISPATCH_FN(rl78Dis_1_22_SUBW       ) { PRE();            op1=R_AX ;            IMM2(op2);  sprintf(userData, REP(PREFIX_FORMAT "SUBW    AX, ES:%s"            ), hex, __LINE__, skipPrefix(rl78),                    t_abs16(op2) ); }    // SUBW    AX, !addr16
static RL78_DISPATCH_FN(rl78Dis_1_24_SUBW       ) { PRE();            op1=R_AX ;            IMM2(op2);  sprintf(userData, REP(PREFIX_FORMAT "SUBW    AX, %s"            ), hex, __LINE__, skipPrefix(rl78),                    t_imm16(op2) ); }    // SUBW    AX, #word
static RL78_DISPATCH_FN(rl78Dis_1_26_SUBW       ) { PRE();            op1=R_AX ;            SADDR(op2); sprintf(userData, REP(PREFIX_FORMAT "SUBW    AX, %s"            ), hex, __LINE__, skipPrefix(rl78),                    t_adr8 (op2) ); }    // SUBW    AX, saddrp
static RL78_DISPATCH_FN(rl78Dis_1_2X_SUBW       ) { PRE();            op1=R_AX ;            BIT2(op2);  sprintf(userData, REP(PREFIX_FORMAT "SUBW    AX, %s"            ), hex, __LINE__, skipPrefix(rl78),                    t_reg16(op2) ); }    // SUBW    AX, ??
static RL78_DISPATCH_FN(rl78Dis_1_28_MOV        ) { PRE(); IMM2(dis); op1=R_C  ;            op2=R_A  ;  sprintf(userData, REP(PREFIX_FORMAT "MOV     ES:%s[C], A"        ), hex, __LINE__, skipPrefix(rl78), t_dis16(dis)                    ); }    // MOV     word[C] ,A
static RL78_DISPATCH_FN(rl78Dis_1_29_MOV        ) { PRE();            op1=R_A  ; IMM2(dis); op2=R_C  ;  sprintf(userData, REP(PREFIX_FORMAT "MOV     A, ES:%s[C]"        ), hex, __LINE__, skipPrefix(rl78),                    t_dis16(dis) ); }    // MOV     A, word[C]
static RL78_DISPATCH_FN(rl78Dis_1_2A_SUB        ) { PRE();            SADDR(op1);           IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "SUB     %s, %s"            ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1),      t_imm8 (op2) ); }    // SUB     saddr, #byte
static RL78_DISPATCH_FN(rl78Dis_1_2B_SUB        ) { PRE();            op1=R_A  ;            SADDR(op2); sprintf(userData, REP(PREFIX_FORMAT "SUB     A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_adr8 (op2) ); }    // SUB     A, saddr
static RL78_DISPATCH_FN(rl78Dis_1_2C_SUB        ) { PRE();            op1=R_A  ;            IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "SUB     A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_imm8 (op2) ); }    // SUB     A, #byte
static RL78_DISPATCH_FN(rl78Dis_1_2D_SUB        ) { PRE();            op1=R_A  ;            op2=R_HL ;  sprintf(userData, REP(PREFIX_FORMAT "SUB     A, ES:[HL]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // SUB     A, [HL]
static RL78_DISPATCH_FN(rl78Dis_1_2E_SUB        ) { PRE();            op1=R_A  ; IMM1(dis); op2=R_HL ;  sprintf(userData, REP(PREFIX_FORMAT "SUB     A, ES:[HL+%s]"        ), hex, __LINE__, skipPrefix(rl78),                    t_dis8 (dis) ); }    // SUB     A, [HL+byte]
static RL78_DISPATCH_FN(rl78Dis_1_2F_SUB        ) { PRE();            op1=R_A  ;            IMM2(op2);  sprintf(userData, REP(PREFIX_FORMAT "SUB     A, ES:%s"            ), hex, __LINE__, skipPrefix(rl78),                    t_abs16(op2) ); }    // SUB     A, !addr16
static RL78_DISPATCH_FN(rl78Dis_1_31_4thmap     ) { PRE();                                              sprintf(userData, REP(PREFIX_FORMAT "4thmap  "                    ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // 4thmap
static RL78_DISPATCH_FN(rl78Dis_1_3X_XCHW       ) { PRE();            op1=R_AX ;            BIT2(op2);  sprintf(userData, REP(PREFIX_FORMAT "XCHW    AX, %s"            ), hex, __LINE__, skipPrefix(rl78),                    t_reg16(op2) ); }    // XCHW    AX, ??
static RL78_DISPATCH_FN(rl78Dis_1_3Y_MOVW       ) { PRE();            BIT2(op1);            IMM2(op2);  sprintf(userData, REP(PREFIX_FORMAT "MOVW    %s, %s"            ), hex, __LINE__, skipPrefix(rl78), t_reg16(op1),      t_imm16(op2) ); }    // MOVW    ??, #word
static RL78_DISPATCH_FN(rl78Dis_1_38_MOV        ) { PRE(); IMM2(dis); op1=R_C  ;            IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "MOV     ES:%s[C], %s"        ), hex, __LINE__, skipPrefix(rl78), t_dis16(dis),      t_imm8 (op2) ); }    // MOV     word[C], #byte
static RL78_DISPATCH_FN(rl78Dis_1_39_MOV        ) { PRE(); IMM2(dis); op1=R_BC ;            IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "MOV     ES:%s[BC], %s"        ), hex, __LINE__, skipPrefix(rl78), t_dis16(dis),      t_imm8 (op2) ); }    // MOV     word[BC], #byte
static RL78_DISPATCH_FN(rl78Dis_1_3A_SUBC       ) { PRE();            SADDR(op1);           IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "SUBC    %s, %s"            ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1),      t_imm8 (op2) ); }    // SUBC    saddr, #byte
static RL78_DISPATCH_FN(rl78Dis_1_3B_SUBC       ) { PRE();            op1=R_A  ;            SADDR(op2); sprintf(userData, REP(PREFIX_FORMAT "SUBC    A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_adr8 (op2) ); }    // SUBC    A, saddr
static RL78_DISPATCH_FN(rl78Dis_1_3C_SUBC       ) { PRE();            op1=R_A  ;            IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "SUBC    A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_imm8 (op2) ); }    // SUBC    A, #byte
static RL78_DISPATCH_FN(rl78Dis_1_3D_SUBC       ) { PRE();            op1=R_A  ;            op2=R_HL ;  sprintf(userData, REP(PREFIX_FORMAT "SUBC    A, ES:[HL]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // SUBC    A, [HL]
static RL78_DISPATCH_FN(rl78Dis_1_3E_SUBC       ) { PRE();            op1=R_A  ; IMM1(dis); op2=R_HL ;  sprintf(userData, REP(PREFIX_FORMAT "SUBC    A, ES:[HL+%s]"        ), hex, __LINE__, skipPrefix(rl78),                    t_dis8 (dis) ); }    // SUBC    A, [HL+byte]
static RL78_DISPATCH_FN(rl78Dis_1_3F_SUBC       ) { PRE();            op1=R_A  ;            IMM2(op2);  sprintf(userData, REP(PREFIX_FORMAT "SUBC    A, ES:%s"            ), hex, __LINE__, skipPrefix(rl78),                    t_abs16(op2) ); }    // SUBC    A, !addr16
static RL78_DISPATCH_FN(rl78Dis_1_40_CMP        ) { PRE();            IMM2(op1);            IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "CMP     ES:%s, %s"            ), hex, __LINE__, skipPrefix(rl78), t_abs16(op1),      t_imm8 (op2) ); }    // CMP     !addr16, #byte
static RL78_DISPATCH_FN(rl78Dis_1_41_MOV        ) { PRE();            op1=R_ES ;            IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "MOV     ES, %s"            ), hex, __LINE__, skipPrefix(rl78),                    t_imm8 (op2) ); }    // MOV     ES, #byte
static RL78_DISPATCH_FN(rl78Dis_1_42_CMPW       ) { PRE();            op1=R_AX ;            IMM2(op2);  sprintf(userData, REP(PREFIX_FORMAT "CMPW    AX, ES:%s"            ), hex, __LINE__, skipPrefix(rl78),                    t_abs16(op2) ); }    // CMPW    AX, !addr16
static RL78_DISPATCH_FN(rl78Dis_1_44_CMPW       ) { PRE();            op1=R_AX ;            IMM2(op2);  sprintf(userData, REP(PREFIX_FORMAT "CMPW    AX, %s"            ), hex, __LINE__, skipPrefix(rl78),                    t_imm16(op2) ); }    // CMPW    AX, #word
static RL78_DISPATCH_FN(rl78Dis_1_46_CMPW       ) { PRE();            op1=R_AX ;            SADDR(op2); sprintf(userData, REP(PREFIX_FORMAT "CMPW    AX, %s"            ), hex, __LINE__, skipPrefix(rl78),                    t_adr8 (op2) ); }    // CMPW    AX, saddrp
static RL78_DISPATCH_FN(rl78Dis_1_4X_CMPW       ) { PRE();            op1=R_AX ;            BIT2(op2);  sprintf(userData, REP(PREFIX_FORMAT "CMPW    AX, %s"            ), hex, __LINE__, skipPrefix(rl78),                    t_reg16(op2) ); }    // CMPW    AX, ??
static RL78_DISPATCH_FN(rl78Dis_1_48_MOV        ) { PRE(); IMM2(dis); op1=R_BC ;            op2=R_A  ;  sprintf(userData, REP(PREFIX_FORMAT "MOV     ES:%s[BC], A"        ), hex, __LINE__, skipPrefix(rl78), t_dis16(dis)                    ); }    // MOV     word[BC], A
static RL78_DISPATCH_FN(rl78Dis_1_49_MOV        ) { PRE();            op1=R_A  ; IMM2(dis); op2=R_BC ;  sprintf(userData, REP(PREFIX_FORMAT "MOV     A, ES:%s[BC]"        ), hex, __LINE__, skipPrefix(rl78),                    t_dis16(dis) ); }    // MOV     A, word[BC]
static RL78_DISPATCH_FN(rl78Dis_1_4A_CMP        ) { PRE();            SADDR(op1);           IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "CMP     %s, %s"            ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1),      t_imm8 (op2) ); }    // CMP     saddr, #byte
static RL78_DISPATCH_FN(rl78Dis_1_4B_CMP        ) { PRE();            op1=R_A  ;            SADDR(op2); sprintf(userData, REP(PREFIX_FORMAT "CMP     A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_adr8 (op2) ); }    // CMP     A, saddr
static RL78_DISPATCH_FN(rl78Dis_1_4C_CMP        ) { PRE();            op1=R_A  ;            IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "CMP     A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_imm8 (op2) ); }    // CMP     A, #byte
static RL78_DISPATCH_FN(rl78Dis_1_4D_CMP        ) { PRE();            op1=R_A  ;            op2=R_HL ;  sprintf(userData, REP(PREFIX_FORMAT "CMP     A, ES:[HL]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // CMP     A, [HL]
static RL78_DISPATCH_FN(rl78Dis_1_4E_CMP        ) { PRE();            op1=R_A  ; IMM1(dis); op2=R_HL ;  sprintf(userData, REP(PREFIX_FORMAT "CMP     A, ES:[HL+%s]"        ), hex, __LINE__, skipPrefix(rl78),                    t_dis8 (dis) ); }    // CMP     A, [HL+byte]
static RL78_DISPATCH_FN(rl78Dis_1_4F_CMP        ) { PRE();            op1=R_A  ;            IMM2(op2);  sprintf(userData, REP(PREFIX_FORMAT "CMP     A, ES:%s"            ), hex, __LINE__, skipPrefix(rl78),                    t_abs16(op2) ); }    // CMP     A, !addr16
static RL78_DISPATCH_FN(rl78Dis_1_5X_MOV        ) { PRE();            BIT3(op1);            IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "MOV     %s, %s"            ), hex, __LINE__, skipPrefix(rl78), t_reg8 (op1),      t_imm8 (op2) ); }    // MOV     ?, #byte
static RL78_DISPATCH_FN(rl78Dis_1_58_MOVW       ) { PRE(); IMM2(dis); op1=R_B  ;            op2=R_AX ;  sprintf(userData, REP(PREFIX_FORMAT "MOVW    ES:%s[B], AX"        ), hex, __LINE__, skipPrefix(rl78), t_dis16(dis)                    ); }    // MOVW    word[B], AX
static RL78_DISPATCH_FN(rl78Dis_1_59_MOVW       ) { PRE();            op1=R_AX ; IMM2(dis); op2=R_B  ;  sprintf(userData, REP(PREFIX_FORMAT "MOVW    AX, ES:%s[B]"        ), hex, __LINE__, skipPrefix(rl78),                    t_dis16(dis) ); }    // MOVW    AX, word[B]
static RL78_DISPATCH_FN(rl78Dis_1_5A_AND        ) { PRE();            SADDR(op1);           IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "AND     %s, %s"            ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1),      t_imm8 (op2) ); }    // AND     saddr, #byte
static RL78_DISPATCH_FN(rl78Dis_1_5B_AND        ) { PRE();            op1=R_A  ;            SADDR(op2); sprintf(userData, REP(PREFIX_FORMAT "AND     A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_adr8 (op2) ); }    // AND     A, saddr
static RL78_DISPATCH_FN(rl78Dis_1_5C_AND        ) { PRE();            op1=R_A  ;            IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "AND     A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_imm8 (op2) ); }    // AND     A, #byte
static RL78_DISPATCH_FN(rl78Dis_1_5D_AND        ) { PRE();            op1=R_A  ;            op2=R_HL ;  sprintf(userData, REP(PREFIX_FORMAT "AND     A, ES:[HL]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // AND     A, [HL]
static RL78_DISPATCH_FN(rl78Dis_1_5E_AND        ) { PRE();            op1=R_A  ; IMM1(dis); op2=R_HL ;  sprintf(userData, REP(PREFIX_FORMAT "AND     A, ES:[HL+%s]"        ), hex, __LINE__, skipPrefix(rl78),                    t_dis8 (dis) ); }    // AND     A, [HL+byte]
static RL78_DISPATCH_FN(rl78Dis_1_5F_AND        ) { PRE();            op1=R_A  ;            IMM2(op2);  sprintf(userData, REP(PREFIX_FORMAT "AND     A, ES:%s"            ), hex, __LINE__, skipPrefix(rl78),                    t_abs16(op2) ); }    // AND     A, !addr16
static RL78_DISPATCH_FN(rl78Dis_1_61_2ndmap     ) { PRE();                                              sprintf(userData, REP(PREFIX_FORMAT "2ndmap  "                    ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // 2ndmap
static RL78_DISPATCH_FN(rl78Dis_1_6X_MOV        ) { PRE();            op1=R_A  ;            BIT3(op2);  sprintf(userData, REP(PREFIX_FORMAT "MOV     A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_reg8 (op2) ); }    // MOV     A, ?
static RL78_DISPATCH_FN(rl78Dis_1_68_MOVW       ) { PRE(); IMM2(dis); op1=R_C  ;            op2=R_AX ;  sprintf(userData, REP(PREFIX_FORMAT "MOVW    ES:%s[C], AX"        ), hex, __LINE__, skipPrefix(rl78), t_dis16(dis)                    ); }    // MOVW    word[C], AX
static RL78_DISPATCH_FN(rl78Dis_1_69_MOVW       ) { PRE();            op1=R_AX ; IMM2(dis); op2=R_C  ;  sprintf(userData, REP(PREFIX_FORMAT "MOVW    AX, ES:%s[C]"        ), hex, __LINE__, skipPrefix(rl78),                    t_dis16(dis) ); }    // MOVW    AX, word[C]
static RL78_DISPATCH_FN(rl78Dis_1_6A_OR         ) { PRE();            SADDR(op1);           IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "OR      %s, %s"            ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1),      t_imm8 (op2) ); }    // OR      saddr, #byte
static RL78_DISPATCH_FN(rl78Dis_1_6B_OR         ) { PRE();            op1=R_A  ;            SADDR(op2); sprintf(userData, REP(PREFIX_FORMAT "OR      A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_adr8 (op2) ); }    // OR      A, saddr
static RL78_DISPATCH_FN(rl78Dis_1_6C_OR         ) { PRE();            op1=R_A  ;            IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "OR      A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_imm8 (op2) ); }    // OR      A, #byte
static RL78_DISPATCH_FN(rl78Dis_1_6D_OR         ) { PRE();            op1=R_A  ;            op2=R_HL ;  sprintf(userData, REP(PREFIX_FORMAT "OR      A, ES:[HL]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // OR      A, [HL]
static RL78_DISPATCH_FN(rl78Dis_1_6E_OR         ) { PRE();            op1=R_A  ; IMM1(dis); op2=R_HL ;  sprintf(userData, REP(PREFIX_FORMAT "OR      A, ES:[HL+%s]"        ), hex, __LINE__, skipPrefix(rl78),                    t_dis8 (dis) ); }    // OR      A, [HL+byte]
static RL78_DISPATCH_FN(rl78Dis_1_6F_OR         ) { PRE();            op1=R_A  ;            IMM2(op2);  sprintf(userData, REP(PREFIX_FORMAT "OR      A, ES:%s"            ), hex, __LINE__, skipPrefix(rl78),                    t_abs16(op2) ); }    // OR      A, !addr16
static RL78_DISPATCH_FN(rl78Dis_1_71_3rdmap     ) { PRE();                                              sprintf(userData, REP(PREFIX_FORMAT "3rdmap  "                    ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // 3rdmap
static RL78_DISPATCH_FN(rl78Dis_1_7X_MOV        ) { PRE();            BIT3(op1);            op2=R_A  ;  sprintf(userData, REP(PREFIX_FORMAT "MOV     %s, A"                ), hex, __LINE__, skipPrefix(rl78), t_reg8 (op1)                    ); }    // MOV     ?, A
static RL78_DISPATCH_FN(rl78Dis_1_78_MOVW       ) { PRE(); IMM2(dis); op1=R_BC ;            op2=R_AX ;  sprintf(userData, REP(PREFIX_FORMAT "MOVW    ES:%s[BC], AX"        ), hex, __LINE__, skipPrefix(rl78), t_dis16(dis)                    ); }    // MOVW    word[BC], AX
static RL78_DISPATCH_FN(rl78Dis_1_79_MOVW       ) { PRE();            op1=R_AX ; IMM2(dis); op2=R_BC ;  sprintf(userData, REP(PREFIX_FORMAT "MOVW    AX, ES:%s[BC]"        ), hex, __LINE__, skipPrefix(rl78),                    t_dis16(dis) ); }    // MOVW    AX, word[BC]
static RL78_DISPATCH_FN(rl78Dis_1_7A_XOR        ) { PRE();            SADDR(op1);           IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "XOR     %s, %s"            ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1),      t_imm8 (op2) ); }    // XOR     saddr, #byte
static RL78_DISPATCH_FN(rl78Dis_1_7B_XOR        ) { PRE();            op1=R_A  ;            SADDR(op2); sprintf(userData, REP(PREFIX_FORMAT "XOR     A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_adr8 (op2) ); }    // XOR     A, saddr
static RL78_DISPATCH_FN(rl78Dis_1_7C_XOR        ) { PRE();            op1=R_A  ;            IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "XOR     A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_imm8 (op2) ); }    // XOR     A, #byte
static RL78_DISPATCH_FN(rl78Dis_1_7D_XOR        ) { PRE();            op1=R_A  ;            op2=R_HL ;  sprintf(userData, REP(PREFIX_FORMAT "XOR     A, ES:[HL]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // XOR     A, [HL]
static RL78_DISPATCH_FN(rl78Dis_1_7E_XOR        ) { PRE();            op1=R_A  ; IMM1(dis); op2=R_HL ;  sprintf(userData, REP(PREFIX_FORMAT "XOR     A, ES:[HL+%s]"        ), hex, __LINE__, skipPrefix(rl78),                    t_dis8 (dis) ); }    // XOR     A, [HL+byte]
static RL78_DISPATCH_FN(rl78Dis_1_7F_XOR        ) { PRE();            op1=R_A  ;            IMM2(op2);  sprintf(userData, REP(PREFIX_FORMAT "XOR     A, ES:%s"            ), hex, __LINE__, skipPrefix(rl78),                    t_abs16(op2) ); }    // XOR     A, !addr16
static RL78_DISPATCH_FN(rl78Dis_1_8X_INC        ) { PRE();            BIT3(op1);                        sprintf(userData, REP(PREFIX_FORMAT "INC     %s"                ), hex, __LINE__, skipPrefix(rl78), t_reg8 (op1)                    ); }    // INC     ?
static RL78_DISPATCH_FN(rl78Dis_1_88_MOV        ) { PRE();            op1=R_A  ; IMM1(dis); op2=R_SP ;  sprintf(userData, REP(PREFIX_FORMAT "MOV     A, ES:[SP+%s]"        ), hex, __LINE__, skipPrefix(rl78),                    t_dis8 (dis) ); }    // MOV     A, [SP+byte]
static RL78_DISPATCH_FN(rl78Dis_1_89_MOV        ) { PRE();            op1=R_A  ;            op2=R_DE ;  sprintf(userData, REP(PREFIX_FORMAT "MOV     A, ES:[DE]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // MOV     A, [DE]
static RL78_DISPATCH_FN(rl78Dis_1_8A_MOV        ) { PRE();            op1=R_A  ; IMM1(dis); op2=R_DE ;  sprintf(userData, REP(PREFIX_FORMAT "MOV     A, ES:[DE+%s]"        ), hex, __LINE__, skipPrefix(rl78),                    t_dis8 (dis) ); }    // MOV     A, [DE+byte]
static RL78_DISPATCH_FN(rl78Dis_1_8B_MOV        ) { PRE();            op1=R_A  ;            op2=R_HL ;  sprintf(userData, REP(PREFIX_FORMAT "MOV     A, ES:[HL]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // MOV     A, [HL]
static RL78_DISPATCH_FN(rl78Dis_1_8C_MOV        ) { PRE();            op1=R_A  ; IMM1(dis); op2=R_HL ;  sprintf(userData, REP(PREFIX_FORMAT "MOV     A, ES:[HL+%s]"        ), hex, __LINE__, skipPrefix(rl78),                    t_dis8 (dis) ); }    // MOV     A, [HL+byte]
static RL78_DISPATCH_FN(rl78Dis_1_8D_MOV        ) { PRE();            op1=R_A  ;            SADDR(op2); sprintf(userData, REP(PREFIX_FORMAT "MOV     A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_adr8 (op2) ); }    // MOV     A, saddr
static RL78_DISPATCH_FN(rl78Dis_1_8E_MOV        ) { PRE();            op1=R_A  ;            SFR(op2) ;  sprintf(userData, REP(PREFIX_FORMAT "MOV     A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_adr8 (op2) ); }    // MOV     A, sfr
static RL78_DISPATCH_FN(rl78Dis_1_8F_MOV        ) { PRE();            op1=R_A  ;            IMM2(op2);  sprintf(userData, REP(PREFIX_FORMAT "MOV     A, ES:%s"            ), hex, __LINE__, skipPrefix(rl78),                    t_abs16(op2) ); }    // MOV     A, !addr16
static RL78_DISPATCH_FN(rl78Dis_1_9X_DEC        ) { PRE();            BIT3(op1);                        sprintf(userData, REP(PREFIX_FORMAT "DEC     %s"                ), hex, __LINE__, skipPrefix(rl78), t_reg8 (op1)                    ); }    // DEC     ?
static RL78_DISPATCH_FN(rl78Dis_1_98_MOV        ) { PRE(); IMM1(dis); op1=R_SP ;            op2=R_A  ;  sprintf(userData, REP(PREFIX_FORMAT "MOV     ES:[SP+%s], A"        ), hex, __LINE__, skipPrefix(rl78), t_dis8 (dis)                    ); }    // MOV     [SP+byte], A
static RL78_DISPATCH_FN(rl78Dis_1_99_MOV        ) { PRE();            op1=R_DE ;            op2=R_A  ;  sprintf(userData, REP(PREFIX_FORMAT "MOV     ES:[DE], A"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // MOV     [DE], A
static RL78_DISPATCH_FN(rl78Dis_1_9A_MOV        ) { PRE(); IMM1(dis); op1=R_DE ;            op2=R_A  ;  sprintf(userData, REP(PREFIX_FORMAT "MOV     ES:[DE+%s], A"        ), hex, __LINE__, skipPrefix(rl78), t_dis8 (dis)                    ); }    // MOV     [DE+byte], A
static RL78_DISPATCH_FN(rl78Dis_1_9B_MOV        ) { PRE();            op1=R_HL ;            op2=R_A  ;  sprintf(userData, REP(PREFIX_FORMAT "MOV     ES:[HL], A"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // MOV     [HL], A
static RL78_DISPATCH_FN(rl78Dis_1_9C_MOV        ) { PRE(); IMM1(dis); op1=R_HL ;            op2=R_A  ;  sprintf(userData, REP(PREFIX_FORMAT "MOV     ES:[HL+%s], A"        ), hex, __LINE__, skipPrefix(rl78), t_dis8 (dis)                    ); }    // MOV     [HL+byte], A
static RL78_DISPATCH_FN(rl78Dis_1_9D_MOV        ) { PRE();            SADDR(op1);           op2=R_A  ;  sprintf(userData, REP(PREFIX_FORMAT "MOV     %s, A"                ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1)                    ); }    // MOV     saddr, A
static RL78_DISPATCH_FN(rl78Dis_1_9E_MOV        ) { PRE();            SFR(op1) ;            op2=R_A  ;  sprintf(userData, REP(PREFIX_FORMAT "MOV     %s, A"                ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1)                    ); }    // MOV     sfr, A
static RL78_DISPATCH_FN(rl78Dis_1_9F_MOV        ) { PRE();            IMM2(op1);            op2=R_A  ;  sprintf(userData, REP(PREFIX_FORMAT "MOV     ES:%s, A"            ), hex, __LINE__, skipPrefix(rl78), t_abs16(op1)                    ); }    // MOV     !addr16, A
static RL78_DISPATCH_FN(rl78Dis_1_A0_INC        ) { PRE();            IMM2(op1);                        sprintf(userData, REP(PREFIX_FORMAT "INC     ES:%s"                ), hex, __LINE__, skipPrefix(rl78), t_abs16(op1)                    ); }    // INC     !addr16
static RL78_DISPATCH_FN(rl78Dis_1_A2_INCW       ) { PRE();            IMM2(op1);                        sprintf(userData, REP(PREFIX_FORMAT "INCW    ES:%s"                ), hex, __LINE__, skipPrefix(rl78), t_abs16(op1)                    ); }    // INCW    !addr16
static RL78_DISPATCH_FN(rl78Dis_1_A4_INC        ) { PRE();            SADDR(op1);                       sprintf(userData, REP(PREFIX_FORMAT "INC     %s"                ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1)                    ); }    // INC     saddr
static RL78_DISPATCH_FN(rl78Dis_1_A6_INCW       ) { PRE();            SADDR(op1);                       sprintf(userData, REP(PREFIX_FORMAT "INCW    %s"                ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1)                    ); }    // INCW    saddrp
static RL78_DISPATCH_FN(rl78Dis_1_AX_INCW       ) { PRE();            BIT2(op1);                        sprintf(userData, REP(PREFIX_FORMAT "INCW    %s"                ), hex, __LINE__, skipPrefix(rl78), t_reg16(op1)                    ); }    // INCW    ??
static RL78_DISPATCH_FN(rl78Dis_1_A8_MOVW       ) { PRE();            op1=R_AX ; IMM1(dis); op2=R_SP ;  sprintf(userData, REP(PREFIX_FORMAT "MOVW    AX, ES:[SP+%s]"    ), hex, __LINE__, skipPrefix(rl78),                    t_dis8 (dis) ); }    // MOVW    AX, [SP+byte]
static RL78_DISPATCH_FN(rl78Dis_1_A9_MOVW       ) { PRE();            op1=R_AX ;            op2=R_DE ;  sprintf(userData, REP(PREFIX_FORMAT "MOVW    AX, ES:[DE]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // MOVW    AX, [DE]
static RL78_DISPATCH_FN(rl78Dis_1_AA_MOVW       ) { PRE();            op1=R_AX ; IMM1(dis); op2=R_DE ;  sprintf(userData, REP(PREFIX_FORMAT "MOVW    AX, ES:[DE+%s]"    ), hex, __LINE__, skipPrefix(rl78),                    t_dis8 (dis) ); }    // MOVW    AX, [DE+byte]
static RL78_DISPATCH_FN(rl78Dis_1_AB_MOVW       ) { PRE();            op1=R_AX ;            op2=R_HL ;  sprintf(userData, REP(PREFIX_FORMAT "MOVW    AX, ES:[HL]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // MOVW    AX, [HL]
static RL78_DISPATCH_FN(rl78Dis_1_AC_MOVW       ) { PRE();            op1=R_AX ; IMM1(dis); op2=R_HL ;  sprintf(userData, REP(PREFIX_FORMAT "MOVW    AX, ES:[HL+%s]"    ), hex, __LINE__, skipPrefix(rl78),                    t_dis8 (dis) ); }    // MOVW    AX, [HL+byte]
static RL78_DISPATCH_FN(rl78Dis_1_AD_MOVW       ) { PRE();            op1=R_AX ;            SADDR(op2); sprintf(userData, REP(PREFIX_FORMAT "MOVW    AX, %s"            ), hex, __LINE__, skipPrefix(rl78),                    t_adr8 (op2) ); }    // MOVW    AX, saddrp
static RL78_DISPATCH_FN(rl78Dis_1_AE_MOVW       ) { PRE();            op1=R_AX ;            SFR(op2) ;  sprintf(userData, REP(PREFIX_FORMAT "MOVW    AX, %s"            ), hex, __LINE__, skipPrefix(rl78),                    t_adr8 (op2) ); }    // MOVW    AX, sfrp
static RL78_DISPATCH_FN(rl78Dis_1_AF_MOVW       ) { PRE();            op1=R_AX ;            IMM2(op2);  sprintf(userData, REP(PREFIX_FORMAT "MOVW    AX, ES:%s"            ), hex, __LINE__, skipPrefix(rl78),                    t_abs16(op2) ); }    // MOVW    AX, !addr16
static RL78_DISPATCH_FN(rl78Dis_1_B0_DEC        ) { PRE();            IMM2(op1);                        sprintf(userData, REP(PREFIX_FORMAT "DEC     ES:%s"                ), hex, __LINE__, skipPrefix(rl78), t_abs16(op1)                    ); }    // DEC     !addr16
static RL78_DISPATCH_FN(rl78Dis_1_B2_DECW       ) { PRE();            IMM2(op1);                        sprintf(userData, REP(PREFIX_FORMAT "DECW    ES:%s"                ), hex, __LINE__, skipPrefix(rl78), t_abs16(op1)                    ); }    // DECW    !addr16
static RL78_DISPATCH_FN(rl78Dis_1_B4_DEC        ) { PRE();            SADDR(op1);                       sprintf(userData, REP(PREFIX_FORMAT "DEC     %s"                ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1)                    ); }    // DEC     saddr
static RL78_DISPATCH_FN(rl78Dis_1_B6_DECW       ) { PRE();            SADDR(op1);                       sprintf(userData, REP(PREFIX_FORMAT "DECW    %s"                ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1)                    ); }    // DECW    saddrp
static RL78_DISPATCH_FN(rl78Dis_1_BX_DECW       ) { PRE();            BIT2(op1);                        sprintf(userData, REP(PREFIX_FORMAT "DECW    %s"                ), hex, __LINE__, skipPrefix(rl78), t_reg16(op1)                    ); }    // DECW    ??
static RL78_DISPATCH_FN(rl78Dis_1_B8_MOVW       ) { PRE(); IMM1(dis); op1=R_SP ;            op2=R_AX ;  sprintf(userData, REP(PREFIX_FORMAT "MOVW    ES:[SP+%s], AX"    ), hex, __LINE__, skipPrefix(rl78), t_dis8 (dis)                    ); }    // MOVW    [SP+byte], AX
static RL78_DISPATCH_FN(rl78Dis_1_B9_MOVW       ) { PRE();            op1=R_DE ;            op2=R_AX ;  sprintf(userData, REP(PREFIX_FORMAT "MOVW    ES:[DE], AX"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // MOVW    [DE], AX
static RL78_DISPATCH_FN(rl78Dis_1_BA_MOVW       ) { PRE(); IMM1(dis); op1=R_DE ;            op2=R_AX ;  sprintf(userData, REP(PREFIX_FORMAT "MOVW    ES:[DE+%s], AX"    ), hex, __LINE__, skipPrefix(rl78), t_dis8 (dis)                    ); }    // MOVW    [DE+byte], AX
static RL78_DISPATCH_FN(rl78Dis_1_BB_MOVW       ) { PRE();            op1=R_HL ;            op2=R_AX ;  sprintf(userData, REP(PREFIX_FORMAT "MOVW    ES:[HL], AX"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // MOVW    [HL], AX
static RL78_DISPATCH_FN(rl78Dis_1_BC_MOVW       ) { PRE(); IMM1(dis); op1=R_HL ;            op2=R_AX ;  sprintf(userData, REP(PREFIX_FORMAT "MOVW    ES:[HL+%s], AX"    ), hex, __LINE__, skipPrefix(rl78), t_dis8 (dis)                    ); }    // MOVW    [HL+byte], AX
static RL78_DISPATCH_FN(rl78Dis_1_BD_MOVW       ) { PRE();            SADDR(op1);           op2=R_AX ;  sprintf(userData, REP(PREFIX_FORMAT "MOVW    %s, AX"            ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1)                    ); }    // MOVW    saddrp, AX
static RL78_DISPATCH_FN(rl78Dis_1_BE_MOVW       ) { PRE();            SFR(op1) ;            op2=R_AX ;  sprintf(userData, REP(PREFIX_FORMAT "MOVW    %s, AX"            ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1)                    ); }    // MOVW    sfrp, AX
static RL78_DISPATCH_FN(rl78Dis_1_BF_MOVW       ) { PRE();            IMM2(op1);            op2=R_AX ;  sprintf(userData, REP(PREFIX_FORMAT "MOVW    ES:%s, AX"            ), hex, __LINE__, skipPrefix(rl78), t_abs16(op1)                    ); }    // MOVW    !addr16, AX
static RL78_DISPATCH_FN(rl78Dis_1_CX_POP        ) { PRE();            BIT2(op1);                        sprintf(userData, REP(PREFIX_FORMAT "POP     %s"                ), hex, __LINE__, skipPrefix(rl78), t_reg16(op1)                    ); }    // POP     ??
static RL78_DISPATCH_FN(rl78Dis_1_CY_PUSH       ) { PRE();            BIT2(op1);                        sprintf(userData, REP(PREFIX_FORMAT "PUSH    %s"                ), hex, __LINE__, skipPrefix(rl78), t_reg16(op1)                    ); }    // PUSH    ??
static RL78_DISPATCH_FN(rl78Dis_1_C8_MOV        ) { PRE(); IMM1(dis); op1=R_SP ;            IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "MOV     ES:[SP+%s], %s"    ), hex, __LINE__, skipPrefix(rl78), t_dis8 (dis),      t_imm8 (op2) ); }    // MOV     [SP+byte], #byte
static RL78_DISPATCH_FN(rl78Dis_1_C9_MOVW       ) { PRE();            SADDR(op1);           IMM2(op2);  sprintf(userData, REP(PREFIX_FORMAT "MOVW    %s, %s"            ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1),      t_imm16(op2) ); }    // MOVW    saddrp, #word
static RL78_DISPATCH_FN(rl78Dis_1_CA_MOV        ) { PRE(); IMM1(dis); op1=R_DE ;            IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "MOV     ES:[DE+%s], %s"    ), hex, __LINE__, skipPrefix(rl78), t_dis8 (dis),      t_imm8 (op2) ); }    // MOV     [DE+byte], #byte
static RL78_DISPATCH_FN(rl78Dis_1_CB_MOVW       ) { PRE();            SFR(op1) ;            IMM2(op2);  sprintf(userData, REP(PREFIX_FORMAT "MOVW    %s, %s"            ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1),      t_imm16(op2) ); }    // MOVW    sfrp, #word
static RL78_DISPATCH_FN(rl78Dis_1_CC_MOV        ) { PRE(); IMM1(dis); op1=R_HL ;            IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "MOV     ES:[HL+%s], %s"    ), hex, __LINE__, skipPrefix(rl78), t_dis8 (dis),      t_imm8 (op2) ); }    // MOV     [HL+byte], #byte
static RL78_DISPATCH_FN(rl78Dis_1_CD_MOV        ) { PRE();            SADDR(op1);           IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "MOV     %s, %s"            ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1),      t_imm8 (op2) ); }    // MOV     saddr, #byte
static RL78_DISPATCH_FN(rl78Dis_1_CE_MOV_SFR    ) { PRE();            SFR(op1) ;            IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "MOV     %s, %s"            ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1),      t_imm8 (op2) ); }    // MOV     sfr, #byte
static RL78_DISPATCH_FN(rl78Dis_1_CE_MOV_PSW    ) { PRE();            op1=R_PSW;            IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "MOV     PSW, %s"            ), hex, __LINE__, skipPrefix(rl78),                    t_imm8 (op2) ); }    // MOV     PSW, #byte
static RL78_DISPATCH_FN(rl78Dis_1_CE_MOV_CS     ) { PRE();            op1=R_CS ;            IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "MOV     CS, %s"            ), hex, __LINE__, skipPrefix(rl78),                    t_imm8 (op2) ); }    // MOV     CS, #byte
static RL78_DISPATCH_FN(rl78Dis_1_CE_MULHU      ) { PRE();            op1=R_AX ;            op2=R_BC ;  sprintf(userData, REP(PREFIX_FORMAT "MULHU   "                    ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // MULHU
static RL78_DISPATCH_FN(rl78Dis_1_CE_MULH       ) { PRE();            op1=R_AX ;            op2=R_BC ;  sprintf(userData, REP(PREFIX_FORMAT "MULH    "                    ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // MULH
static RL78_DISPATCH_FN(rl78Dis_1_CE_DIVHU      ) { PRE();            op1=R_AX ;            op2=R_DE ;  sprintf(userData, REP(PREFIX_FORMAT "DIVHU   "                    ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // DIVHU
static RL78_DISPATCH_FN(rl78Dis_1_CE_DIVWU      ) { PRE();            op1=R_BCAX;           op2=R_HLDE; sprintf(userData, REP(PREFIX_FORMAT "DIVWU   "                    ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // DIVWU
static RL78_DISPATCH_FN(rl78Dis_1_CE_MACHU      ) { PRE();            op1=R_AX ;            op2=R_BC ;  sprintf(userData, REP(PREFIX_FORMAT "MACHU   "                    ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // MACHU
static RL78_DISPATCH_FN(rl78Dis_1_CE_MACH       ) { PRE();            op1=R_AX ;            op2=R_BC ;  sprintf(userData, REP(PREFIX_FORMAT "MACH    "                    ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // MACH
static RL78_DISPATCH_FN(rl78Dis_1_CF_MOV        ) { PRE();            IMM2(op1);            IMM1(op2);  sprintf(userData, REP(PREFIX_FORMAT "MOV     ES:%s, %s"            ), hex, __LINE__, skipPrefix(rl78), t_abs16(op1),      t_imm8 (op2) ); }    // MOV     !addr16, #byte
static RL78_DISPATCH_FN(rl78Dis_1_DX_CMP0       ) { PRE();            BIT3(op1);                        sprintf(userData, REP(PREFIX_FORMAT "CMP0    %s"                ), hex, __LINE__, skipPrefix(rl78), t_reg8 (op1)                    ); }    // CMP0    ?
static RL78_DISPATCH_FN(rl78Dis_1_D4_CMP0       ) { PRE();            SADDR(op1);                       sprintf(userData, REP(PREFIX_FORMAT "CMP0    %s"                ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1)                    ); }    // CMP0    saddr
static RL78_DISPATCH_FN(rl78Dis_1_D5_CMP0       ) { PRE();            IMM2(op1);                        sprintf(userData, REP(PREFIX_FORMAT "CMP0    ES:%s"                ), hex, __LINE__, skipPrefix(rl78), t_abs16(op1)                    ); }    // CMP0    !addr16
static RL78_DISPATCH_FN(rl78Dis_1_D6_MULU       ) { PRE();            op1=R_A  ;            op2=R_X  ;  sprintf(userData, REP(PREFIX_FORMAT "MULU    X"                    ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // MULU    X
static RL78_DISPATCH_FN(rl78Dis_1_D7_RET        ) { PRE();                                              sprintf(userData, REP(PREFIX_FORMAT "RET     "                    ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // RET
static RL78_DISPATCH_FN(rl78Dis_1_D8_MOV        ) { PRE();            op1=R_X  ;            SADDR(op2); sprintf(userData, REP(PREFIX_FORMAT "MOV     X, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_adr8 (op2) ); }    // MOV     X, saddr
static RL78_DISPATCH_FN(rl78Dis_1_D9_MOV        ) { PRE();            op1=R_X  ;            IMM2(op2);  sprintf(userData, REP(PREFIX_FORMAT "MOV     X, ES:%s"            ), hex, __LINE__, skipPrefix(rl78),                    t_abs16(op2) ); }    // MOV     X, !addr16
static RL78_DISPATCH_FN(rl78Dis_1_DC_BC         ) { PRE();            IMM1(op1);                        sprintf(userData, REP(PREFIX_FORMAT "BC      %s"                ), hex, __LINE__, skipPrefix(rl78), t_rel8 (op1)                    ); }    // BC      $addr20
static RL78_DISPATCH_FN(rl78Dis_1_DD_BZ         ) { PRE();            IMM1(op1);                        sprintf(userData, REP(PREFIX_FORMAT "BZ      %s"                ), hex, __LINE__, skipPrefix(rl78), t_rel8 (op1)                    ); }    // BZ      $addr20
static RL78_DISPATCH_FN(rl78Dis_1_DE_BNC        ) { PRE();            IMM1(op1);                        sprintf(userData, REP(PREFIX_FORMAT "BNC     %s"                ), hex, __LINE__, skipPrefix(rl78), t_rel8 (op1)                    ); }    // BNC     $addr20
static RL78_DISPATCH_FN(rl78Dis_1_DF_BNZ        ) { PRE();            IMM1(op1);                        sprintf(userData, REP(PREFIX_FORMAT "BNZ     %s"                ), hex, __LINE__, skipPrefix(rl78), t_rel8 (op1)                    ); }    // BNZ     $addr20
static RL78_DISPATCH_FN(rl78Dis_1_EX_ONEB       ) { PRE();            BIT3(op1);                        sprintf(userData, REP(PREFIX_FORMAT "ONEB    %s"                ), hex, __LINE__, skipPrefix(rl78), t_reg8 (op1)                    ); }    // ONEB    ?
static RL78_DISPATCH_FN(rl78Dis_1_E4_ONEB       ) { PRE();            SADDR(op1);                       sprintf(userData, REP(PREFIX_FORMAT "ONEB    %s"                ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1)                    ); }    // ONEB    saddr
static RL78_DISPATCH_FN(rl78Dis_1_E5_ONEB       ) { PRE();            IMM2(op1);                        sprintf(userData, REP(PREFIX_FORMAT "ONEB    ES:%s"                ), hex, __LINE__, skipPrefix(rl78), t_abs16(op1)                    ); }    // ONEB    !addr16
static RL78_DISPATCH_FN(rl78Dis_1_E6_ONEW       ) { PRE();            op1=R_AX ;                        sprintf(userData, REP(PREFIX_FORMAT "ONEW    AX"                ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // ONEW    AX
static RL78_DISPATCH_FN(rl78Dis_1_E7_ONEW       ) { PRE();            op1=R_BC ;                        sprintf(userData, REP(PREFIX_FORMAT "ONEW    BC"                ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // ONEW    BC
static RL78_DISPATCH_FN(rl78Dis_1_E8_MOV        ) { PRE();            op1=R_B  ;            SADDR(op2); sprintf(userData, REP(PREFIX_FORMAT "MOV     B, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_adr8 (op2) ); }    // MOV     B, saddr
static RL78_DISPATCH_FN(rl78Dis_1_E9_MOV        ) { PRE();            op1=R_B  ;            IMM2(op2);  sprintf(userData, REP(PREFIX_FORMAT "MOV     B, ES:%s"            ), hex, __LINE__, skipPrefix(rl78),                    t_abs16(op2) ); }    // MOV     B, !addr16
static RL78_DISPATCH_FN(rl78Dis_1_EC_BR         ) { PRE();            IMM3(op1);                        sprintf(userData, REP(PREFIX_FORMAT "BR      %s"                ), hex, __LINE__, skipPrefix(rl78), t_abs20(op1)                    ); }    // BR      !!addr20
static RL78_DISPATCH_FN(rl78Dis_1_ED_BR         ) { PRE();            IMM2(op1);                        sprintf(userData, REP(PREFIX_FORMAT "BR      %s"                ), hex, __LINE__, skipPrefix(rl78), t_abs16(op1)                    ); }    // BR      !addr16
static RL78_DISPATCH_FN(rl78Dis_1_EE_BR         ) { PRE();            IMM2(op1);                        sprintf(userData, REP(PREFIX_FORMAT "BR      %s"                ), hex, __LINE__, skipPrefix(rl78), t_rel16(op1)                    ); }    // BR      $!addr20
static RL78_DISPATCH_FN(rl78Dis_1_EF_BR         ) { PRE();            IMM1(op1);                        sprintf(userData, REP(PREFIX_FORMAT "BR      %s"                ), hex, __LINE__, skipPrefix(rl78), t_rel8 (op1)                    ); }    // BR      $addr20
static RL78_DISPATCH_FN(rl78Dis_1_FX_CLRB       ) { PRE();            BIT3(op1);                        sprintf(userData, REP(PREFIX_FORMAT "CLRB    %s"                ), hex, __LINE__, skipPrefix(rl78), t_reg8 (op1)                    ); }    // CLRB    ?
static RL78_DISPATCH_FN(rl78Dis_1_F4_CLRB       ) { PRE();            SADDR(op1);                       sprintf(userData, REP(PREFIX_FORMAT "CLRB    %s"                ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1)                    ); }    // CLRB    saddr
static RL78_DISPATCH_FN(rl78Dis_1_F5_CLRB       ) { PRE();            IMM2(op1);                        sprintf(userData, REP(PREFIX_FORMAT "CLRB    ES:%s"                ), hex, __LINE__, skipPrefix(rl78), t_abs16(op1)                    ); }    // CLRB    !addr16
static RL78_DISPATCH_FN(rl78Dis_1_F6_CLRW       ) { PRE();            op1=R_AX ;                        sprintf(userData, REP(PREFIX_FORMAT "CLRW    AX"                ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // CLRW    AX
static RL78_DISPATCH_FN(rl78Dis_1_F7_CLRW       ) { PRE();            op1=R_BC ;                        sprintf(userData, REP(PREFIX_FORMAT "CLRW    BC"                ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // CLRW    BC
static RL78_DISPATCH_FN(rl78Dis_1_F8_MOV        ) { PRE();            op1=R_C  ;            SADDR(op2); sprintf(userData, REP(PREFIX_FORMAT "MOV     C, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_adr8 (op2) ); }    // MOV     C, saddr
static RL78_DISPATCH_FN(rl78Dis_1_F9_MOV        ) { PRE();            op1=R_C  ;            IMM2(op2);  sprintf(userData, REP(PREFIX_FORMAT "MOV     C, ES:%s"            ), hex, __LINE__, skipPrefix(rl78),                    t_abs16(op2) ); }    // MOV     C, !addr16
static RL78_DISPATCH_FN(rl78Dis_1_FC_CALL       ) { PRE();            IMM3(op1);                        sprintf(userData, REP(PREFIX_FORMAT "CALL    %s"                ), hex, __LINE__, skipPrefix(rl78), t_abs20(op1)                    ); }    // CALL    !!addr20
static RL78_DISPATCH_FN(rl78Dis_1_FD_CALL       ) { PRE();            IMM2(op1);                        sprintf(userData, REP(PREFIX_FORMAT "CALL    %s"                ), hex, __LINE__, skipPrefix(rl78), t_abs16(op1)                    ); }    // CALL    !addr16
static RL78_DISPATCH_FN(rl78Dis_1_FE_CALL       ) { PRE();            IMM2(op1);                        sprintf(userData, REP(PREFIX_FORMAT "CALL    %s"                ), hex, __LINE__, skipPrefix(rl78), t_rel16(op1)                    ); }    // CALL    $!addr20
static RL78_DISPATCH_FN(rl78Dis_1_XA_MOVW       ) { PRE();            BIT(op1,4,2);         SADDR(op2); sprintf(userData, REP(PREFIX_FORMAT "MOVW    %s, %s"            ), hex, __LINE__, skipPrefix(rl78), t_reg16(op1),      t_adr8 (op2) ); }    // MOVW    ??, saddrp
static RL78_DISPATCH_FN(rl78Dis_1_XB_MOVW       ) { PRE();            BIT(op1,4,2);         IMM2(op2);  sprintf(userData, REP(PREFIX_FORMAT "MOVW    %s, ES:%s"            ), hex, __LINE__, skipPrefix(rl78), t_reg16(op1),      t_abs16(op2) ); }    // MOVW    ??, !addr16

static RL78_DISPATCH_FN(rl78Dis_2_0X_ADD        ) { PRE();            BIT3(op1);            op2=R_A  ;  sprintf(userData, REP(PREFIX_FORMAT "ADD     %s, A"                ), hex, __LINE__, skipPrefix(rl78), t_reg8 (op1)                    ); }    // ADD     ?, A
static RL78_DISPATCH_FN(rl78Dis_2_09_ADDW       ) { PRE();            op1=R_AX ; IMM1(dis); op2=R_HL ;  sprintf(userData, REP(PREFIX_FORMAT "ADDW    AX, ES:[HL+%s]"    ), hex, __LINE__, skipPrefix(rl78),                    t_dis8 (dis) ); }    // ADDW    AX, [HL+byte]
static RL78_DISPATCH_FN(rl78Dis_2_0Y_ADD        ) { PRE();            op1=R_A  ;            BIT3(op2);  sprintf(userData, REP(PREFIX_FORMAT "ADD     A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_reg8 (op2) ); }    // ADD     A, ?
static RL78_DISPATCH_FN(rl78Dis_2_1X_ADDC       ) { PRE();            BIT3(op1);            op2=R_A  ;  sprintf(userData, REP(PREFIX_FORMAT "ADDC    %s, A"                ), hex, __LINE__, skipPrefix(rl78), t_reg8 (op1)                    ); }    // ADDC    ?, A
static RL78_DISPATCH_FN(rl78Dis_2_1Y_ADDC       ) { PRE();            op1=R_A  ;            BIT3(op2);  sprintf(userData, REP(PREFIX_FORMAT "ADDC    A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_reg8 (op2) ); }    // ADDC    A, ?
static RL78_DISPATCH_FN(rl78Dis_2_2X_SUB        ) { PRE();            BIT3(op1);            op2=R_A  ;  sprintf(userData, REP(PREFIX_FORMAT "SUB     %s, A"                ), hex, __LINE__, skipPrefix(rl78), t_reg8 (op1)                    ); }    // SUB     ?, A
static RL78_DISPATCH_FN(rl78Dis_2_29_SUBW       ) { PRE();            op1=R_AX ; IMM1(dis); op2=R_HL ;  sprintf(userData, REP(PREFIX_FORMAT "SUBW    AX, ES:[HL+%s]"    ), hex, __LINE__, skipPrefix(rl78),                    t_dis8 (dis) ); }    // SUBW    AX, [HL+byte]
static RL78_DISPATCH_FN(rl78Dis_2_2Y_SUB        ) { PRE();            op1=R_A  ;            BIT3(op2);  sprintf(userData, REP(PREFIX_FORMAT "SUB     A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_reg8 (op2) ); }    // SUB     A, ?
static RL78_DISPATCH_FN(rl78Dis_2_3X_SUBC       ) { PRE();            BIT3(op1);            op2=R_A  ;  sprintf(userData, REP(PREFIX_FORMAT "SUBC    %s, A"                ), hex, __LINE__, skipPrefix(rl78), t_reg8 (op1)                    ); }    // SUBC    ?, A
static RL78_DISPATCH_FN(rl78Dis_2_3Y_SUBC       ) { PRE();            op1=R_A  ;            BIT3(op2);  sprintf(userData, REP(PREFIX_FORMAT "SUBC    A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_reg8 (op2) ); }    // SUBC    A, ?
static RL78_DISPATCH_FN(rl78Dis_2_4X_CMP        ) { PRE();            BIT3(op1);            op2=R_A  ;  sprintf(userData, REP(PREFIX_FORMAT "CMP     %s, A"                ), hex, __LINE__, skipPrefix(rl78), t_reg8 (op1)                    ); }    // CMP     ?, A
static RL78_DISPATCH_FN(rl78Dis_2_49_CMPW       ) { PRE();            op1=R_AX ; IMM1(dis); op2=R_HL ;  sprintf(userData, REP(PREFIX_FORMAT "CMPW    AX, ES:[HL+%s]"    ), hex, __LINE__, skipPrefix(rl78),                    t_dis8 (dis) ); }    // CMPW    AX, [HL+byte]
static RL78_DISPATCH_FN(rl78Dis_2_4Y_CMP        ) { PRE();            op1=R_A  ;            BIT3(op2);  sprintf(userData, REP(PREFIX_FORMAT "CMP     A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_reg8 (op2) ); }    // CMP     A, ?
static RL78_DISPATCH_FN(rl78Dis_2_5X_AND        ) { PRE();            BIT3(op1);            op2=R_A  ;  sprintf(userData, REP(PREFIX_FORMAT "AND     %s, A"                ), hex, __LINE__, skipPrefix(rl78), t_reg8 (op1)                    ); }    // AND     ?, A
static RL78_DISPATCH_FN(rl78Dis_2_59_INC        ) { PRE(); IMM1(dis); op1=R_HL ;                        sprintf(userData, REP(PREFIX_FORMAT "INC     ES:[HL+%s]"        ), hex, __LINE__, skipPrefix(rl78), t_dis8 (dis)                    ); }    // INC     [HL+byte]
static RL78_DISPATCH_FN(rl78Dis_2_5Y_AND        ) { PRE();            op1=R_A  ;            BIT3(op2);  sprintf(userData, REP(PREFIX_FORMAT "AND     A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_reg8 (op2) ); }    // AND     A, ?
static RL78_DISPATCH_FN(rl78Dis_2_6X_OR         ) { PRE();            BIT3(op1);            op2=R_A  ;  sprintf(userData, REP(PREFIX_FORMAT "OR      %s, A"                ), hex, __LINE__, skipPrefix(rl78), t_reg8 (op1)                    ); }    // OR      ?, A
static RL78_DISPATCH_FN(rl78Dis_2_69_DEC        ) { PRE(); IMM1(dis); op1=R_HL ;                        sprintf(userData, REP(PREFIX_FORMAT "DEC     ES:[HL+%s]"        ), hex, __LINE__, skipPrefix(rl78), t_dis8 (dis)                    ); }    // DEC     [HL+byte]
static RL78_DISPATCH_FN(rl78Dis_2_6Y_OR         ) { PRE();            op1=R_A  ;            BIT3(op2);  sprintf(userData, REP(PREFIX_FORMAT "OR      A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_reg8 (op2) ); }    // OR      A, ?
static RL78_DISPATCH_FN(rl78Dis_2_7X_XOR        ) { PRE();            BIT3(op1);            op2=R_A  ;  sprintf(userData, REP(PREFIX_FORMAT "XOR     %s, A"                ), hex, __LINE__, skipPrefix(rl78), t_reg8 (op1)                    ); }    // XOR     ?, A
static RL78_DISPATCH_FN(rl78Dis_2_79_INCW       ) { PRE(); IMM1(dis); op1=R_HL ;                        sprintf(userData, REP(PREFIX_FORMAT "INCW    ES:[HL+%s]"        ), hex, __LINE__, skipPrefix(rl78), t_dis8 (dis)                    ); }    // INCW    [HL+byte]
static RL78_DISPATCH_FN(rl78Dis_2_7Y_XOR        ) { PRE();            op1=R_A  ;            BIT3(op2);  sprintf(userData, REP(PREFIX_FORMAT "XOR     A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_reg8 (op2) ); }    // XOR     A, ?
static RL78_DISPATCH_FN(rl78Dis_2_80_ADD        ) { PRE();            op1=R_A  ;            op2=R_B  ;  sprintf(userData, REP(PREFIX_FORMAT "ADD     A, ES:[HL+B]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // ADD     A, [HL+B]
static RL78_DISPATCH_FN(rl78Dis_2_82_ADD        ) { PRE();            op1=R_A  ;            op2=R_C  ;  sprintf(userData, REP(PREFIX_FORMAT "ADD     A, ES:[HL+C]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // ADD     A, [HL+C]
static RL78_DISPATCH_FN(rl78Dis_2_89_DECW       ) { PRE(); IMM1(dis); op1=R_HL ;                        sprintf(userData, REP(PREFIX_FORMAT "DECW    ES:[HL+%s]"        ), hex, __LINE__, skipPrefix(rl78), t_dis8 (dis)                    ); }    // DECW    [HL+byte]
static RL78_DISPATCH_FN(rl78Dis_2_8X_XCH        ) { PRE();            op1=R_A  ;            BIT3(op2);  sprintf(userData, REP(PREFIX_FORMAT "XCH     A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_reg8 (op2) ); }    // XCH     A, ?
static RL78_DISPATCH_FN(rl78Dis_2_90_ADDC       ) { PRE();            op1=R_A  ;            op2=R_B  ;  sprintf(userData, REP(PREFIX_FORMAT "ADDC    A, ES:[HL+B]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // ADDC    A, [HL+B]
static RL78_DISPATCH_FN(rl78Dis_2_92_ADDC       ) { PRE();            op1=R_A  ;            op2=R_C  ;  sprintf(userData, REP(PREFIX_FORMAT "ADDC    A, ES:[HL+C]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // ADDC    A, [HL+C]
static RL78_DISPATCH_FN(rl78Dis_2_A0_SUB        ) { PRE();            op1=R_A  ;            op2=R_B  ;  sprintf(userData, REP(PREFIX_FORMAT "SUB     A, ES:[HL+B]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // SUB     A, [HL+B]
static RL78_DISPATCH_FN(rl78Dis_2_A2_SUB        ) { PRE();            op1=R_A  ;            op2=R_C  ;  sprintf(userData, REP(PREFIX_FORMAT "SUB     A, ES:[HL+C]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // SUB     A, [HL+C]
static RL78_DISPATCH_FN(rl78Dis_2_A8_XCH        ) { PRE();            op1=R_A  ;            SADDR(op2); sprintf(userData, REP(PREFIX_FORMAT "XCH     A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_adr8 (op2) ); }    // XCH     A, saddr
static RL78_DISPATCH_FN(rl78Dis_2_A9_XCH        ) { PRE();            op1=R_A  ;            op2=R_C  ;  sprintf(userData, REP(PREFIX_FORMAT "XCH     A, ES:[HL+C]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // XCH     A, [HL+C]
static RL78_DISPATCH_FN(rl78Dis_2_AA_XCH        ) { PRE();            op1=R_A  ;            IMM2(op2);  sprintf(userData, REP(PREFIX_FORMAT "XCH     A, ES:%s"            ), hex, __LINE__, skipPrefix(rl78),                    t_abs16(op2) ); }    // XCH     A, !addr16
static RL78_DISPATCH_FN(rl78Dis_2_AB_XCH        ) { PRE();            op1=R_A  ;            SFR(op2) ;  sprintf(userData, REP(PREFIX_FORMAT "XCH     A, %s"                ), hex, __LINE__, skipPrefix(rl78),                    t_adr8 (op2) ); }    // XCH     A, sfr
static RL78_DISPATCH_FN(rl78Dis_2_AC_XCH        ) { PRE();            op1=R_A  ;            op2=R_HL ;  sprintf(userData, REP(PREFIX_FORMAT "XCH     A, ES:[HL]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // XCH     A, [HL]
static RL78_DISPATCH_FN(rl78Dis_2_AD_XCH        ) { PRE();            op1=R_A  ; IMM1(dis); op2=R_HL ;  sprintf(userData, REP(PREFIX_FORMAT "XCH     A, ES:[HL+%s]"        ), hex, __LINE__, skipPrefix(rl78),                    t_dis8 (dis) ); }    // XCH     A, [HL+byte]
static RL78_DISPATCH_FN(rl78Dis_2_AE_XCH        ) { PRE();            op1=R_A  ;            op2=R_DE ;  sprintf(userData, REP(PREFIX_FORMAT "XCH     A, ES:[DE]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // XCH     A, [DE]
static RL78_DISPATCH_FN(rl78Dis_2_AF_XCH        ) { PRE();            op1=R_A  ; IMM1(dis); op2=R_DE ;  sprintf(userData, REP(PREFIX_FORMAT "XCH     A, ES:[DE+%s]"        ), hex, __LINE__, skipPrefix(rl78),                    t_dis8 (dis) ); }    // XCH     A, [DE+byte]
static RL78_DISPATCH_FN(rl78Dis_2_B0_SUBC       ) { PRE();            op1=R_A  ;            op2=R_B  ;  sprintf(userData, REP(PREFIX_FORMAT "SUBC    A, ES:[HL+B]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // SUBC    A, [HL+B]
static RL78_DISPATCH_FN(rl78Dis_2_B2_SUBC       ) { PRE();            op1=R_A  ;            op2=R_C  ;  sprintf(userData, REP(PREFIX_FORMAT "SUBC    A, ES:[HL+C]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // SUBC    A, [HL+C]
static RL78_DISPATCH_FN(rl78Dis_2_B8_MOV        ) { PRE();            op1=R_ES ;            SADDR(op2); sprintf(userData, REP(PREFIX_FORMAT "MOV     ES, %s"            ), hex, __LINE__, skipPrefix(rl78),                    t_adr8 (op2) ); }    // MOV     ES, saddr
static RL78_DISPATCH_FN(rl78Dis_2_B9_XCH        ) { PRE();            op1=R_A  ;            op2=R_B  ;  sprintf(userData, REP(PREFIX_FORMAT "XCH     A, ES:[HL+B]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // XCH     A, [HL+B]
static RL78_DISPATCH_FN(rl78Dis_2_C0_CMP        ) { PRE();            op1=R_A  ;            op2=R_B  ;  sprintf(userData, REP(PREFIX_FORMAT "CMP     A, ES:[HL+B]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // CMP     A, [HL+B]
static RL78_DISPATCH_FN(rl78Dis_2_C2_CMP        ) { PRE();            op1=R_A  ;            op2=R_C  ;  sprintf(userData, REP(PREFIX_FORMAT "CMP     A, ES:[HL+C]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // CMP     A, [HL+C]
static RL78_DISPATCH_FN(rl78Dis_2_C3_BH         ) { PRE();            IMM1(op1);                        sprintf(userData, REP(PREFIX_FORMAT "BH      %s"                ), hex, __LINE__, skipPrefix(rl78), t_rel8 (op1)                    ); }    // BH      $addr20
static RL78_DISPATCH_FN(rl78Dis_2_C8_SKC        ) { PRE();                                              sprintf(userData, REP(PREFIX_FORMAT "SKC     "                    ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // SKC
static RL78_DISPATCH_FN(rl78Dis_2_C9_MOV        ) { PRE();            op1=R_A  ;            op2=R_B  ;  sprintf(userData, REP(PREFIX_FORMAT "MOV     A, ES:[HL+B]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // MOV     A, [HL+B]
static RL78_DISPATCH_FN(rl78Dis_2_CB_BR         ) { PRE();            op1=R_AX ;                        sprintf(userData, REP(PREFIX_FORMAT "BR      AX"                ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // BR      AX
static RL78_DISPATCH_FN(rl78Dis_2_CC_BRK        ) { PRE();                                              sprintf(userData, REP(PREFIX_FORMAT "BRK     "                    ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // BRK
static RL78_DISPATCH_FN(rl78Dis_2_CD_POP        ) { PRE();            op1=R_PSW;                        sprintf(userData, REP(PREFIX_FORMAT "POP     PSW"                ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // POP     PSW
static RL78_DISPATCH_FN(rl78Dis_2_CE_MOVS       ) { PRE(); IMM1(dis); op1=R_HL ;            op2=R_X  ;  sprintf(userData, REP(PREFIX_FORMAT "MOVS    ES:[HL+%s], X"        ), hex, __LINE__, skipPrefix(rl78), t_dis8 (dis)                    ); }    // MOVS    [HL+byte], X
static RL78_DISPATCH_FN(rl78Dis_2_D0_AND        ) { PRE();            op1=R_A  ;            op2=R_B  ;  sprintf(userData, REP(PREFIX_FORMAT "AND     A, ES:[HL+B]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // AND     A, [HL+B]
static RL78_DISPATCH_FN(rl78Dis_2_D2_AND        ) { PRE();            op1=R_A  ;            op2=R_C  ;  sprintf(userData, REP(PREFIX_FORMAT "AND     A, ES:[HL+C]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // AND     A, [HL+C]
static RL78_DISPATCH_FN(rl78Dis_2_D3_BNH        ) { PRE();            IMM1(op1);                        sprintf(userData, REP(PREFIX_FORMAT "BNH     %s"                ), hex, __LINE__, skipPrefix(rl78), t_rel8 (op1)                    ); }    // BNH     $addr20
static RL78_DISPATCH_FN(rl78Dis_2_D8_SKNC       ) { PRE();                                              sprintf(userData, REP(PREFIX_FORMAT "SKNC    "                    ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // SKNC
static RL78_DISPATCH_FN(rl78Dis_2_D9_MOV        ) { PRE();            op1=R_B  ;            op2=R_A  ;  sprintf(userData, REP(PREFIX_FORMAT "MOV     ES:[HL+B], A"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // MOV     [HL+B], A
static RL78_DISPATCH_FN(rl78Dis_2_DB_ROR        ) { PRE();            op1=R_A  ;                        sprintf(userData, REP(PREFIX_FORMAT "ROR     A, 1"                ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // ROR     A, 1
static RL78_DISPATCH_FN(rl78Dis_2_DC_ROLC       ) { PRE();            op1=R_A  ;                        sprintf(userData, REP(PREFIX_FORMAT "ROLC    A, 1"                ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // ROLC    A, 1
static RL78_DISPATCH_FN(rl78Dis_2_DD_PUSH       ) { PRE();                                              sprintf(userData, REP(PREFIX_FORMAT "PUSH    PSW"                ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // PUSH    PSW
static RL78_DISPATCH_FN(rl78Dis_2_DE_CMPS       ) { PRE();            op1=R_X  ; IMM1(dis); op2=R_HL ;  sprintf(userData, REP(PREFIX_FORMAT "CMPS    X, ES:[HL+%s]"        ), hex, __LINE__, skipPrefix(rl78),                    t_dis8 (dis) ); }    // CMPS    X, [HL+byte]
static RL78_DISPATCH_FN(rl78Dis_2_E0_OR         ) { PRE();            op1=R_A  ;            op2=R_B  ;  sprintf(userData, REP(PREFIX_FORMAT "OR      A, ES:[HL+B]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // OR      A, [HL+B]
static RL78_DISPATCH_FN(rl78Dis_2_E2_OR         ) { PRE();            op1=R_A  ;            op2=R_C  ;  sprintf(userData, REP(PREFIX_FORMAT "OR      A, ES:[HL+C]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // OR      A, [HL+C]
static RL78_DISPATCH_FN(rl78Dis_2_E3_SKH        ) { PRE();                                              sprintf(userData, REP(PREFIX_FORMAT "SKH     "                    ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // SKH
static RL78_DISPATCH_FN(rl78Dis_2_E8_SKZ        ) { PRE();                                              sprintf(userData, REP(PREFIX_FORMAT "SKZ     "                    ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // SKZ
static RL78_DISPATCH_FN(rl78Dis_2_E9_MOV        ) { PRE();            op1=R_A  ;            op2=R_C  ;  sprintf(userData, REP(PREFIX_FORMAT "MOV     A, ES:[HL+C]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // MOV     A, [HL+C]
static RL78_DISPATCH_FN(rl78Dis_2_EB_ROL        ) { PRE();            op1=R_A  ;                        sprintf(userData, REP(PREFIX_FORMAT "ROL     A, 1"                ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // ROL     A, 1
static RL78_DISPATCH_FN(rl78Dis_2_EC_RETB       ) { PRE();                                              sprintf(userData, REP(PREFIX_FORMAT "RETB    "                    ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // RETB
static RL78_DISPATCH_FN(rl78Dis_2_ED_HALT       ) { PRE();                                              sprintf(userData, REP(PREFIX_FORMAT "HALT    "                    ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // HALT
static RL78_DISPATCH_FN(rl78Dis_2_F0_XOR        ) { PRE();            op1=R_A  ;            op2=R_B  ;  sprintf(userData, REP(PREFIX_FORMAT "XOR     A, ES:[HL+B]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // XOR     A, [HL+B]
static RL78_DISPATCH_FN(rl78Dis_2_F2_XOR        ) { PRE();            op1=R_A  ;            op2=R_C  ;  sprintf(userData, REP(PREFIX_FORMAT "XOR     A, ES:[HL+C]"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // XOR     A, [HL+C]
static RL78_DISPATCH_FN(rl78Dis_2_F3_SKNH       ) { PRE();                                              sprintf(userData, REP(PREFIX_FORMAT "SKNH    "                    ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // SKNH
static RL78_DISPATCH_FN(rl78Dis_2_F8_SKNZ       ) { PRE();                                              sprintf(userData, REP(PREFIX_FORMAT "SKNZ    "                    ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // SKNZ
static RL78_DISPATCH_FN(rl78Dis_2_F9_MOV        ) { PRE();            op1=R_C  ;            op2=R_A  ;  sprintf(userData, REP(PREFIX_FORMAT "MOV     ES:[HL+C], A"        ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // MOV     [HL+C], A
static RL78_DISPATCH_FN(rl78Dis_2_FB_RORC       ) { PRE();            op1=R_A  ;                        sprintf(userData, REP(PREFIX_FORMAT "RORC    A, 1"                ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // RORC    A, 1
static RL78_DISPATCH_FN(rl78Dis_2_FC_RETI       ) { PRE();                                              sprintf(userData, REP(PREFIX_FORMAT "RETI    "                    ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // RETI
static RL78_DISPATCH_FN(rl78Dis_2_FD_STOP       ) { PRE();                                              sprintf(userData, REP(PREFIX_FORMAT "STOP    "                    ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // STOP
static RL78_DISPATCH_FN(rl78Dis_2_XE_ROLWC      ) { PRE();            BIT(op1,4,1);                     sprintf(userData, REP(PREFIX_FORMAT "ROLWC   %s, 1"                ), hex, __LINE__, skipPrefix(rl78), t_reg16(op1)                    ); }    // ROLWC   ??, 1
static RL78_DISPATCH_FN(rl78Dis_2_XF_SEL        ) { PRE();            BIT(op1,4,2);                     sprintf(userData, REP(PREFIX_FORMAT "SEL     RB%d"                ), hex, __LINE__, skipPrefix(rl78),         op1                     ); }    // SEL     RBn
static RL78_DISPATCH_FN(rl78Dis_2_XA_CALL       ) { PRE();            BIT(op1,4,2);                     sprintf(userData, REP(PREFIX_FORMAT "CALL    %s"                ), hex, __LINE__, skipPrefix(rl78), t_reg16(op1)                    ); }    // CALL    ??
static RL78_DISPATCH_FN(rl78Dis_2_XX_CALLT      ) { PRE();            BIT(op1,4,3); BIT(op2,0,2);       sprintf(userData, REP(PREFIX_FORMAT "CALLT   [00%01x%01xh]"        ), hex, __LINE__, skipPrefix(rl78), op2 + 8,  op1 << 1              ); }    // CALLT   [00nnh]

static RL78_DISPATCH_FN(rl78Dis_3_X0_SET1       ) { PRE(); IDX3(ix1); IMM2(op1);                        sprintf(userData, REP(PREFIX_FORMAT "SET1    ES:%s.%d"            ), hex, __LINE__, skipPrefix(rl78), t_abs16(op1), ix1               ); }    // SET1    !addr16.n
static RL78_DISPATCH_FN(rl78Dis_3_X1_MOV1       ) { PRE(); IDX3(ix1); SADDR(op1);           op2=R_CY ;  sprintf(userData, REP(PREFIX_FORMAT "MOV1    %s.%d, CY"            ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1), ix1               ); }    // MOV1    saddr.n, CY
static RL78_DISPATCH_FN(rl78Dis_3_X2_SET1       ) { PRE(); IDX3(ix1); SADDR(op1);                       sprintf(userData, REP(PREFIX_FORMAT "SET1    %s.%d"                ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1), ix1               ); }    // SET1    saddr.n
static RL78_DISPATCH_FN(rl78Dis_3_X3_CLR1       ) { PRE(); IDX3(ix1); SADDR(op1);                       sprintf(userData, REP(PREFIX_FORMAT "CLR1    %s.%d"                ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1), ix1               ); }    // CLR1    saddr.n
static RL78_DISPATCH_FN(rl78Dis_3_X4_MOV1       ) { PRE(); IDX3(ix1); op1=R_CY ; SADDR(op2);            sprintf(userData, REP(PREFIX_FORMAT "MOV1    CY, %s.%d"            ), hex, __LINE__, skipPrefix(rl78),               t_adr8 (op2), ix1 ); }    // MOV1    CY, saddr.n
static RL78_DISPATCH_FN(rl78Dis_3_X5_AND1       ) { PRE(); IDX3(ix1); op1=R_CY ; SADDR(op2);            sprintf(userData, REP(PREFIX_FORMAT "AND1    CY, %s.%d"            ), hex, __LINE__, skipPrefix(rl78),               t_adr8 (op2), ix1 ); }    // AND1    CY, saddr.n
static RL78_DISPATCH_FN(rl78Dis_3_X6_OR1        ) { PRE(); IDX3(ix1); op1=R_CY ; SADDR(op2);            sprintf(userData, REP(PREFIX_FORMAT "OR1     CY, %s.%d"            ), hex, __LINE__, skipPrefix(rl78),               t_adr8 (op2), ix1 ); }    // OR1     CY, saddr.n
static RL78_DISPATCH_FN(rl78Dis_3_X7_XOR1       ) { PRE(); IDX3(ix1); op1=R_CY ; SADDR(op2);            sprintf(userData, REP(PREFIX_FORMAT "XOR1    CY, %s.%d"            ), hex, __LINE__, skipPrefix(rl78),               t_adr8 (op2), ix1 ); }    // XOR1    CY, saddr.n
static RL78_DISPATCH_FN(rl78Dis_3_X8_CLR1       ) { PRE(); IDX3(ix1); IMM2(op1);                        sprintf(userData, REP(PREFIX_FORMAT "CLR1    ES:%s.%d"            ), hex, __LINE__, skipPrefix(rl78), t_abs16(op1), ix1               ); }    // CLR1    !addr16.n
static RL78_DISPATCH_FN(rl78Dis_3_X9_MOV1       ) { PRE(); IDX3(ix1); SFR(op1) ;            op2=R_CY ;  sprintf(userData, REP(PREFIX_FORMAT "MOV1    %s.%d, CY"            ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1), ix1               ); }    // MOV1    sfr.n, CY
static RL78_DISPATCH_FN(rl78Dis_3_XA_SET1       ) { PRE(); IDX3(ix1); SFR(op1) ;                        sprintf(userData, REP(PREFIX_FORMAT "SET1    %s.%d"                ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1), ix1               ); }    // SET1    sfr.n
static RL78_DISPATCH_FN(rl78Dis_3_XB_CLR1       ) { PRE(); IDX3(ix1); SFR(op1) ;                        sprintf(userData, REP(PREFIX_FORMAT "CLR1    %s.%d"                ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1), ix1               ); }    // CLR1    sfr.n
static RL78_DISPATCH_FN(rl78Dis_3_XC_MOV1       ) { PRE(); IDX3(ix1); op1=R_CY ; SFR(op2) ;             sprintf(userData, REP(PREFIX_FORMAT "MOV1    CY, %s.%d"            ), hex, __LINE__, skipPrefix(rl78),               t_adr8 (op2), ix1 ); }    // MOV1    CY, sfr.n
static RL78_DISPATCH_FN(rl78Dis_3_XD_AND1       ) { PRE(); IDX3(ix1); op1=R_CY ; SFR(op2) ;             sprintf(userData, REP(PREFIX_FORMAT "AND1    CY, %s.%d"            ), hex, __LINE__, skipPrefix(rl78),               t_adr8 (op2), ix1 ); }    // AND1    CY, sfr.n
static RL78_DISPATCH_FN(rl78Dis_3_XE_OR1        ) { PRE(); IDX3(ix1); op1=R_CY ; SFR(op2) ;             sprintf(userData, REP(PREFIX_FORMAT "OR1     CY, %s.%d"            ), hex, __LINE__, skipPrefix(rl78),               t_adr8 (op2), ix1 ); }    // OR1     CY, sfr.n
static RL78_DISPATCH_FN(rl78Dis_3_XF_XOR1       ) { PRE(); IDX3(ix1); op1=R_CY ; SFR(op2) ;             sprintf(userData, REP(PREFIX_FORMAT "XOR1    CY, %s.%d"            ), hex, __LINE__, skipPrefix(rl78),               t_adr8 (op2), ix1 ); }    // XOR1    CY, sfr.n
static RL78_DISPATCH_FN(rl78Dis_3_7A_EI         ) { PRE();                                              sprintf(userData, REP(PREFIX_FORMAT "EI      "                    ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // EI
static RL78_DISPATCH_FN(rl78Dis_3_7B_DI         ) { PRE();                                              sprintf(userData, REP(PREFIX_FORMAT "DI      "                    ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // DI
static RL78_DISPATCH_FN(rl78Dis_3_80_SET1       ) { PRE();            op1=R_CY ;                        sprintf(userData, REP(PREFIX_FORMAT "SET1    CY"                ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // SET1    CY
static RL78_DISPATCH_FN(rl78Dis_3_88_CLR1       ) { PRE();            op1=R_CY ;                        sprintf(userData, REP(PREFIX_FORMAT "CLR1    CY"                ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // CLR1    CY
static RL78_DISPATCH_FN(rl78Dis_3_C0_NOT1       ) { PRE();            op1=R_CY ;                        sprintf(userData, REP(PREFIX_FORMAT "NOT1    CY"                ), hex, __LINE__, skipPrefix(rl78)                                  ); }    // NOT1    CY
static RL78_DISPATCH_FN(rl78Dis_3_Y1_MOV1       ) { PRE(); IDX3(ix1); op1=R_HL ;            op2=R_CY;   sprintf(userData, REP(PREFIX_FORMAT "MOV1    ES:[HL].%d, CY"    ), hex, __LINE__, skipPrefix(rl78),               ix1               ); }    // MOV1    [HL].n, CY
static RL78_DISPATCH_FN(rl78Dis_3_Y2_SET1       ) { PRE(); IDX3(ix1); op1=R_HL ;                        sprintf(userData, REP(PREFIX_FORMAT "SET1    ES:[HL].%d"        ), hex, __LINE__, skipPrefix(rl78),               ix1               ); }    // SET1    [HL].n
static RL78_DISPATCH_FN(rl78Dis_3_Y3_CLR1       ) { PRE(); IDX3(ix1); op1=R_HL ;                        sprintf(userData, REP(PREFIX_FORMAT "CLR1    ES:[HL].%d"        ), hex, __LINE__, skipPrefix(rl78),               ix1               ); }    // CLR1    [HL].n
static RL78_DISPATCH_FN(rl78Dis_3_Y4_MOV1       ) { PRE(); IDX3(ix1);            op2=R_HL ;             sprintf(userData, REP(PREFIX_FORMAT "MOV1    CY, ES:[HL].%d"    ), hex, __LINE__, skipPrefix(rl78),                             ix1 ); }    // MOV1    CY, [HL].n
static RL78_DISPATCH_FN(rl78Dis_3_Y5_AND1       ) { PRE(); IDX3(ix1);            op2=R_HL ;             sprintf(userData, REP(PREFIX_FORMAT "AND1    CY, ES:[HL].%d"    ), hex, __LINE__, skipPrefix(rl78),                             ix1 ); }    // AND1    CY, [HL].n
static RL78_DISPATCH_FN(rl78Dis_3_Y6_OR1        ) { PRE(); IDX3(ix1);            op2=R_HL ;             sprintf(userData, REP(PREFIX_FORMAT "OR1     CY, ES:[HL].%d"    ), hex, __LINE__, skipPrefix(rl78),                             ix1 ); }    // OR1     CY, [HL].n
static RL78_DISPATCH_FN(rl78Dis_3_Y7_XOR1       ) { PRE(); IDX3(ix1);            op2=R_HL ;             sprintf(userData, REP(PREFIX_FORMAT "XOR1    CY, ES:[HL].%d"    ), hex, __LINE__, skipPrefix(rl78),                             ix1 ); }    // XOR1    CY, [HL].n
static RL78_DISPATCH_FN(rl78Dis_3_Y9_MOV1       ) { PRE(); IDX3(ix1); op1=R_A  ;            op2=R_CY;   sprintf(userData, REP(PREFIX_FORMAT "MOV1    A.%d, CY"            ), hex, __LINE__, skipPrefix(rl78),               ix1               ); }    // MOV1    A.n, CY
static RL78_DISPATCH_FN(rl78Dis_3_YA_SET1       ) { PRE(); IDX3(ix1); op1=R_A  ;                        sprintf(userData, REP(PREFIX_FORMAT "SET1    A.%d"                ), hex, __LINE__, skipPrefix(rl78),               ix1               ); }    // SET1    A.n
static RL78_DISPATCH_FN(rl78Dis_3_YB_CLR1       ) { PRE(); IDX3(ix1); op1=R_A  ;                        sprintf(userData, REP(PREFIX_FORMAT "CLR1    A.%d"                ), hex, __LINE__, skipPrefix(rl78),               ix1               ); }    // CLR1    A.n
static RL78_DISPATCH_FN(rl78Dis_3_YC_MOV1       ) { PRE(); IDX3(ix1); op1=R_CY ; op2=R_A  ;             sprintf(userData, REP(PREFIX_FORMAT "MOV1    CY, A.%d"            ), hex, __LINE__, skipPrefix(rl78),                             ix1 ); }    // MOV1    CY, A.n
static RL78_DISPATCH_FN(rl78Dis_3_YD_AND1       ) { PRE(); IDX3(ix1); op1=R_CY ; op2=R_A  ;             sprintf(userData, REP(PREFIX_FORMAT "AND1    CY, A.%d"            ), hex, __LINE__, skipPrefix(rl78),                             ix1 ); }    // AND1    CY, A.n
static RL78_DISPATCH_FN(rl78Dis_3_YE_OR1        ) { PRE(); IDX3(ix1); op1=R_CY ; op2=R_A  ;             sprintf(userData, REP(PREFIX_FORMAT "OR1     CY, A.%d"            ), hex, __LINE__, skipPrefix(rl78),                             ix1 ); }    // OR1     CY, A.n
static RL78_DISPATCH_FN(rl78Dis_3_YF_XOR1       ) { PRE(); IDX3(ix1); op1=R_CY ; op2=R_A  ;             sprintf(userData, REP(PREFIX_FORMAT "XOR1    CY, A.%d"            ), hex, __LINE__, skipPrefix(rl78),                             ix1 ); }    // XOR1    CY, A.n

static RL78_DISPATCH_FN(rl78Dis_4_X0_BTCLR      ) { PRE(); IDX3(ix1); SADDR(op1);IMM1(op2);             sprintf(userData, REP(PREFIX_FORMAT "BTCLR   %s.%d, %s"            ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1), ix1, t_rel8 (op2) ); }    // BTCLR   saddr.n, $addr20
static RL78_DISPATCH_FN(rl78Dis_4_X1_BTCLR      ) { PRE(); IDX3(ix1); op1=R_A  ; IMM1(op2);             sprintf(userData, REP(PREFIX_FORMAT "BTCLR   A.%d, %s"            ), hex, __LINE__, skipPrefix(rl78),               ix1, t_rel8 (op2) ); }    // BTCLR   A.n, $addr20
static RL78_DISPATCH_FN(rl78Dis_4_X2_BT         ) { PRE(); IDX3(ix1); SADDR(op1);IMM1(op2);             sprintf(userData, REP(PREFIX_FORMAT "BT      %s.%d, %s"            ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1), ix1, t_rel8 (op2) ); }    // BT      saddr.n, $addr20
static RL78_DISPATCH_FN(rl78Dis_4_X3_BT         ) { PRE(); IDX3(ix1); op1=R_A  ; IMM1(op2);             sprintf(userData, REP(PREFIX_FORMAT "BT      A.%d, %s"            ), hex, __LINE__, skipPrefix(rl78),               ix1, t_rel8 (op2) ); }    // BT      A.n, $addr20
static RL78_DISPATCH_FN(rl78Dis_4_X4_BF         ) { PRE(); IDX3(ix1); SADDR(op1);IMM1(op2);             sprintf(userData, REP(PREFIX_FORMAT "BF      %s.%d, %s"            ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1), ix1, t_rel8 (op2) ); }    // BF      saddr.n, $addr20
static RL78_DISPATCH_FN(rl78Dis_4_X5_BF         ) { PRE(); IDX3(ix1); op1=R_A  ; IMM1(op2);             sprintf(userData, REP(PREFIX_FORMAT "BF      A.%d, %s"            ), hex, __LINE__, skipPrefix(rl78),               ix1, t_rel8 (op2) ); }    // BF      A.n, $addr20
static RL78_DISPATCH_FN(rl78Dis_4_X7_SHL        ) { PRE(); IDX3(ix1); op1=R_C  ;                        sprintf(userData, REP(PREFIX_FORMAT "SHL     C, %d"                ), hex, __LINE__, skipPrefix(rl78),               ix1               ); }    // SHL     C, n
static RL78_DISPATCH_FN(rl78Dis_4_X8_SHL        ) { PRE(); IDX3(ix1); op1=R_B  ;                        sprintf(userData, REP(PREFIX_FORMAT "SHL     B, %d"                ), hex, __LINE__, skipPrefix(rl78),               ix1               ); }    // SHL     B, n
static RL78_DISPATCH_FN(rl78Dis_4_X9_SHL        ) { PRE(); IDX3(ix1); op1=R_A  ;                        sprintf(userData, REP(PREFIX_FORMAT "SHL     A, %d"                ), hex, __LINE__, skipPrefix(rl78),               ix1               ); }    // SHL     A, n
static RL78_DISPATCH_FN(rl78Dis_4_XA_SHR        ) { PRE(); IDX3(ix1); op1=R_A  ;                        sprintf(userData, REP(PREFIX_FORMAT "SHR     A, %d"                ), hex, __LINE__, skipPrefix(rl78),               ix1               ); }    // SHR     A, n
static RL78_DISPATCH_FN(rl78Dis_4_XB_SAR        ) { PRE(); IDX3(ix1); op1=R_A  ;                        sprintf(userData, REP(PREFIX_FORMAT "SAR     A, %d"                ), hex, __LINE__, skipPrefix(rl78),               ix1               ); }    // SAR     A, n
static RL78_DISPATCH_FN(rl78Dis_4_Y0_BTCLR      ) { PRE(); IDX3(ix1); SFR(op1) ; IMM1(op2);             sprintf(userData, REP(PREFIX_FORMAT "BTCLR   %s.%d, %s"            ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1), ix1, t_rel8 (op2) ); }    // BTCLR   sfr.n, $addr20
static RL78_DISPATCH_FN(rl78Dis_4_Y1_BTCLR      ) { PRE(); IDX3(ix1); op1=R_HL ; IMM1(op2);             sprintf(userData, REP(PREFIX_FORMAT "BTCLR   ES:[HL].%d, %s"    ), hex, __LINE__, skipPrefix(rl78),               ix1, t_rel8 (op2) ); }    // BTCLR   [HL].n, $addr20
static RL78_DISPATCH_FN(rl78Dis_4_Y2_BT         ) { PRE(); IDX3(ix1); SFR(op1) ; IMM1(op2);             sprintf(userData, REP(PREFIX_FORMAT "BT      %s.%d, %s"            ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1), ix1, t_rel8 (op2) ); }    // BT      sfr.n, $addr20
static RL78_DISPATCH_FN(rl78Dis_4_Y3_BT         ) { PRE(); IDX3(ix1); op1=R_HL ; IMM1(op2);             sprintf(userData, REP(PREFIX_FORMAT "BT      ES:[HL].%d, %s"    ), hex, __LINE__, skipPrefix(rl78),               ix1, t_rel8 (op2) ); }    // BT      [HL].n, $addr20
static RL78_DISPATCH_FN(rl78Dis_4_Y4_BF         ) { PRE(); IDX3(ix1); SFR(op1) ; IMM1(op2);             sprintf(userData, REP(PREFIX_FORMAT "BF      %s.%d, %s"            ), hex, __LINE__, skipPrefix(rl78), t_adr8 (op1), ix1, t_rel8 (op2) ); }    // BF      sfr.n, $addr20
static RL78_DISPATCH_FN(rl78Dis_4_Y5_BF         ) { PRE(); IDX3(ix1); op1=R_HL ; IMM1(op2);             sprintf(userData, REP(PREFIX_FORMAT "BF      ES:[HL].%d, %s"    ), hex, __LINE__, skipPrefix(rl78),               ix1, t_rel8 (op2) ); }    // BF      [HL].n, $addr20
static RL78_DISPATCH_FN(rl78Dis_4_XC_SHLW       ) { PRE(); IDX4(ix1); op1=R_BC ;                        sprintf(userData, REP(PREFIX_FORMAT "SHLW    BC, %d"            ), hex, __LINE__, skipPrefix(rl78),               ix1               ); }    // SHLW    BC, nn
static RL78_DISPATCH_FN(rl78Dis_4_XD_SHLW       ) { PRE(); IDX4(ix1); op1=R_AX ;                        sprintf(userData, REP(PREFIX_FORMAT "SHLW    AX, %d"            ), hex, __LINE__, skipPrefix(rl78),               ix1               ); }    // SHLW    AX, nn
static RL78_DISPATCH_FN(rl78Dis_4_XE_SHRW       ) { PRE(); IDX4(ix1); op1=R_AX ;                        sprintf(userData, REP(PREFIX_FORMAT "SHRW    AX, %d"            ), hex, __LINE__, skipPrefix(rl78),               ix1               ); }    // SHRW    AX, nn
static RL78_DISPATCH_FN(rl78Dis_4_XF_SARW       ) { PRE(); IDX4(ix1); op1=R_AX ;                        sprintf(userData, REP(PREFIX_FORMAT "SARW    AX, %d"            ), hex, __LINE__, skipPrefix(rl78),               ix1               ); }    // SARW    AX, nn

//#pragma GCC diagnostic pop



//
// RL78 disassembler dispatch table
//
static rl78DispatchTableC dispatchTable = {

    [RL78_IT_1_00_NOP      ] = rl78Dis_1_00_NOP      ,
    [RL78_IT_1_02_ADDW     ] = rl78Dis_1_02_ADDW     ,
    [RL78_IT_1_04_ADDW     ] = rl78Dis_1_04_ADDW     ,
    [RL78_IT_1_06_ADDW     ] = rl78Dis_1_06_ADDW     ,
    [RL78_IT_1_0X_ADDW     ] = rl78Dis_1_0X_ADDW     ,
    [RL78_IT_1_08_XCH      ] = rl78Dis_1_08_XCH      ,
    [RL78_IT_1_09_MOV      ] = rl78Dis_1_09_MOV      ,
    [RL78_IT_1_0A_ADD      ] = rl78Dis_1_0A_ADD      ,
    [RL78_IT_1_0B_ADD      ] = rl78Dis_1_0B_ADD      ,
    [RL78_IT_1_0C_ADD      ] = rl78Dis_1_0C_ADD      ,
    [RL78_IT_1_0D_ADD      ] = rl78Dis_1_0D_ADD      ,
    [RL78_IT_1_0E_ADD      ] = rl78Dis_1_0E_ADD      ,
    [RL78_IT_1_0F_ADD      ] = rl78Dis_1_0F_ADD      ,
    [RL78_IT_1_10_ADDW     ] = rl78Dis_1_10_ADDW     ,
    [RL78_IT_1_11_PREFIX   ] = rl78Dis_1_11_PREFIX   ,
    [RL78_IT_1_1X_MOVW     ] = rl78Dis_1_1X_MOVW     ,
    [RL78_IT_1_1Y_MOVW     ] = rl78Dis_1_1Y_MOVW     ,
    [RL78_IT_1_18_MOV      ] = rl78Dis_1_18_MOV      ,
    [RL78_IT_1_19_MOV      ] = rl78Dis_1_19_MOV      ,
    [RL78_IT_1_1A_ADDC     ] = rl78Dis_1_1A_ADDC     ,
    [RL78_IT_1_1B_ADDC     ] = rl78Dis_1_1B_ADDC     ,
    [RL78_IT_1_1C_ADDC     ] = rl78Dis_1_1C_ADDC     ,
    [RL78_IT_1_1D_ADDC     ] = rl78Dis_1_1D_ADDC     ,
    [RL78_IT_1_1E_ADDC     ] = rl78Dis_1_1E_ADDC     ,
    [RL78_IT_1_1F_ADDC     ] = rl78Dis_1_1F_ADDC     ,
    [RL78_IT_1_20_SUBW     ] = rl78Dis_1_20_SUBW     ,
    [RL78_IT_1_22_SUBW     ] = rl78Dis_1_22_SUBW     ,
    [RL78_IT_1_24_SUBW     ] = rl78Dis_1_24_SUBW     ,
    [RL78_IT_1_26_SUBW     ] = rl78Dis_1_26_SUBW     ,
    [RL78_IT_1_2X_SUBW     ] = rl78Dis_1_2X_SUBW     ,
    [RL78_IT_1_28_MOV      ] = rl78Dis_1_28_MOV      ,
    [RL78_IT_1_29_MOV      ] = rl78Dis_1_29_MOV      ,
    [RL78_IT_1_2A_SUB      ] = rl78Dis_1_2A_SUB      ,
    [RL78_IT_1_2B_SUB      ] = rl78Dis_1_2B_SUB      ,
    [RL78_IT_1_2C_SUB      ] = rl78Dis_1_2C_SUB      ,
    [RL78_IT_1_2D_SUB      ] = rl78Dis_1_2D_SUB      ,
    [RL78_IT_1_2E_SUB      ] = rl78Dis_1_2E_SUB      ,
    [RL78_IT_1_2F_SUB      ] = rl78Dis_1_2F_SUB      ,
    [RL78_IT_1_31_4thmap   ] = rl78Dis_1_31_4thmap   ,
    [RL78_IT_1_3X_XCHW     ] = rl78Dis_1_3X_XCHW     ,
    [RL78_IT_1_3Y_MOVW     ] = rl78Dis_1_3Y_MOVW     ,
    [RL78_IT_1_38_MOV      ] = rl78Dis_1_38_MOV      ,
    [RL78_IT_1_39_MOV      ] = rl78Dis_1_39_MOV      ,
    [RL78_IT_1_3A_SUBC     ] = rl78Dis_1_3A_SUBC     ,
    [RL78_IT_1_3B_SUBC     ] = rl78Dis_1_3B_SUBC     ,
    [RL78_IT_1_3C_SUBC     ] = rl78Dis_1_3C_SUBC     ,
    [RL78_IT_1_3D_SUBC     ] = rl78Dis_1_3D_SUBC     ,
    [RL78_IT_1_3E_SUBC     ] = rl78Dis_1_3E_SUBC     ,
    [RL78_IT_1_3F_SUBC     ] = rl78Dis_1_3F_SUBC     ,
    [RL78_IT_1_40_CMP      ] = rl78Dis_1_40_CMP      ,
    [RL78_IT_1_41_MOV      ] = rl78Dis_1_41_MOV      ,
    [RL78_IT_1_42_CMPW     ] = rl78Dis_1_42_CMPW     ,
    [RL78_IT_1_44_CMPW     ] = rl78Dis_1_44_CMPW     ,
    [RL78_IT_1_46_CMPW     ] = rl78Dis_1_46_CMPW     ,
    [RL78_IT_1_4X_CMPW     ] = rl78Dis_1_4X_CMPW     ,
    [RL78_IT_1_48_MOV      ] = rl78Dis_1_48_MOV      ,
    [RL78_IT_1_49_MOV      ] = rl78Dis_1_49_MOV      ,
    [RL78_IT_1_4A_CMP      ] = rl78Dis_1_4A_CMP      ,
    [RL78_IT_1_4B_CMP      ] = rl78Dis_1_4B_CMP      ,
    [RL78_IT_1_4C_CMP      ] = rl78Dis_1_4C_CMP      ,
    [RL78_IT_1_4D_CMP      ] = rl78Dis_1_4D_CMP      ,
    [RL78_IT_1_4E_CMP      ] = rl78Dis_1_4E_CMP      ,
    [RL78_IT_1_4F_CMP      ] = rl78Dis_1_4F_CMP      ,
    [RL78_IT_1_5X_MOV      ] = rl78Dis_1_5X_MOV      ,
    [RL78_IT_1_58_MOVW     ] = rl78Dis_1_58_MOVW     ,
    [RL78_IT_1_59_MOVW     ] = rl78Dis_1_59_MOVW     ,
    [RL78_IT_1_5A_AND      ] = rl78Dis_1_5A_AND      ,
    [RL78_IT_1_5B_AND      ] = rl78Dis_1_5B_AND      ,
    [RL78_IT_1_5C_AND      ] = rl78Dis_1_5C_AND      ,
    [RL78_IT_1_5D_AND      ] = rl78Dis_1_5D_AND      ,
    [RL78_IT_1_5E_AND      ] = rl78Dis_1_5E_AND      ,
    [RL78_IT_1_5F_AND      ] = rl78Dis_1_5F_AND      ,
    [RL78_IT_1_61_2ndmap   ] = rl78Dis_1_61_2ndmap   ,
    [RL78_IT_1_6X_MOV      ] = rl78Dis_1_6X_MOV      ,
    [RL78_IT_1_68_MOVW     ] = rl78Dis_1_68_MOVW     ,
    [RL78_IT_1_69_MOVW     ] = rl78Dis_1_69_MOVW     ,
    [RL78_IT_1_6A_OR       ] = rl78Dis_1_6A_OR       ,
    [RL78_IT_1_6B_OR       ] = rl78Dis_1_6B_OR       ,
    [RL78_IT_1_6C_OR       ] = rl78Dis_1_6C_OR       ,
    [RL78_IT_1_6D_OR       ] = rl78Dis_1_6D_OR       ,
    [RL78_IT_1_6E_OR       ] = rl78Dis_1_6E_OR       ,
    [RL78_IT_1_6F_OR       ] = rl78Dis_1_6F_OR       ,
    [RL78_IT_1_71_3rdmap   ] = rl78Dis_1_71_3rdmap   ,
    [RL78_IT_1_7X_MOV      ] = rl78Dis_1_7X_MOV      ,
    [RL78_IT_1_78_MOVW     ] = rl78Dis_1_78_MOVW     ,
    [RL78_IT_1_79_MOVW     ] = rl78Dis_1_79_MOVW     ,
    [RL78_IT_1_7A_XOR      ] = rl78Dis_1_7A_XOR      ,
    [RL78_IT_1_7B_XOR      ] = rl78Dis_1_7B_XOR      ,
    [RL78_IT_1_7C_XOR      ] = rl78Dis_1_7C_XOR      ,
    [RL78_IT_1_7D_XOR      ] = rl78Dis_1_7D_XOR      ,
    [RL78_IT_1_7E_XOR      ] = rl78Dis_1_7E_XOR      ,
    [RL78_IT_1_7F_XOR      ] = rl78Dis_1_7F_XOR      ,
    [RL78_IT_1_8X_INC      ] = rl78Dis_1_8X_INC      ,
    [RL78_IT_1_88_MOV      ] = rl78Dis_1_88_MOV      ,
    [RL78_IT_1_89_MOV      ] = rl78Dis_1_89_MOV      ,
    [RL78_IT_1_8A_MOV      ] = rl78Dis_1_8A_MOV      ,
    [RL78_IT_1_8B_MOV      ] = rl78Dis_1_8B_MOV      ,
    [RL78_IT_1_8C_MOV      ] = rl78Dis_1_8C_MOV      ,
    [RL78_IT_1_8D_MOV      ] = rl78Dis_1_8D_MOV      ,
    [RL78_IT_1_8E_MOV      ] = rl78Dis_1_8E_MOV      ,
    [RL78_IT_1_8F_MOV      ] = rl78Dis_1_8F_MOV      ,
    [RL78_IT_1_9X_DEC      ] = rl78Dis_1_9X_DEC      ,
    [RL78_IT_1_98_MOV      ] = rl78Dis_1_98_MOV      ,
    [RL78_IT_1_99_MOV      ] = rl78Dis_1_99_MOV      ,
    [RL78_IT_1_9A_MOV      ] = rl78Dis_1_9A_MOV      ,
    [RL78_IT_1_9B_MOV      ] = rl78Dis_1_9B_MOV      ,
    [RL78_IT_1_9C_MOV      ] = rl78Dis_1_9C_MOV      ,
    [RL78_IT_1_9D_MOV      ] = rl78Dis_1_9D_MOV      ,
    [RL78_IT_1_9E_MOV      ] = rl78Dis_1_9E_MOV      ,
    [RL78_IT_1_9F_MOV      ] = rl78Dis_1_9F_MOV      ,
    [RL78_IT_1_A0_INC      ] = rl78Dis_1_A0_INC      ,
    [RL78_IT_1_A2_INCW     ] = rl78Dis_1_A2_INCW     ,
    [RL78_IT_1_A4_INC      ] = rl78Dis_1_A4_INC      ,
    [RL78_IT_1_A6_INCW     ] = rl78Dis_1_A6_INCW     ,
    [RL78_IT_1_AX_INCW     ] = rl78Dis_1_AX_INCW     ,
    [RL78_IT_1_A8_MOVW     ] = rl78Dis_1_A8_MOVW     ,
    [RL78_IT_1_A9_MOVW     ] = rl78Dis_1_A9_MOVW     ,
    [RL78_IT_1_AA_MOVW     ] = rl78Dis_1_AA_MOVW     ,
    [RL78_IT_1_AB_MOVW     ] = rl78Dis_1_AB_MOVW     ,
    [RL78_IT_1_AC_MOVW     ] = rl78Dis_1_AC_MOVW     ,
    [RL78_IT_1_AD_MOVW     ] = rl78Dis_1_AD_MOVW     ,
    [RL78_IT_1_AE_MOVW     ] = rl78Dis_1_AE_MOVW     ,
    [RL78_IT_1_AF_MOVW     ] = rl78Dis_1_AF_MOVW     ,
    [RL78_IT_1_B0_DEC      ] = rl78Dis_1_B0_DEC      ,
    [RL78_IT_1_B2_DECW     ] = rl78Dis_1_B2_DECW     ,
    [RL78_IT_1_B4_DEC      ] = rl78Dis_1_B4_DEC      ,
    [RL78_IT_1_B6_DECW     ] = rl78Dis_1_B6_DECW     ,
    [RL78_IT_1_BX_DECW     ] = rl78Dis_1_BX_DECW     ,
    [RL78_IT_1_B8_MOVW     ] = rl78Dis_1_B8_MOVW     ,
    [RL78_IT_1_B9_MOVW     ] = rl78Dis_1_B9_MOVW     ,
    [RL78_IT_1_BA_MOVW     ] = rl78Dis_1_BA_MOVW     ,
    [RL78_IT_1_BB_MOVW     ] = rl78Dis_1_BB_MOVW     ,
    [RL78_IT_1_BC_MOVW     ] = rl78Dis_1_BC_MOVW     ,
    [RL78_IT_1_BD_MOVW     ] = rl78Dis_1_BD_MOVW     ,
    [RL78_IT_1_BE_MOVW     ] = rl78Dis_1_BE_MOVW     ,
    [RL78_IT_1_BF_MOVW     ] = rl78Dis_1_BF_MOVW     ,
    [RL78_IT_1_CX_POP      ] = rl78Dis_1_CX_POP      ,
    [RL78_IT_1_CY_PUSH     ] = rl78Dis_1_CY_PUSH     ,
    [RL78_IT_1_C8_MOV      ] = rl78Dis_1_C8_MOV      ,
    [RL78_IT_1_C9_MOVW     ] = rl78Dis_1_C9_MOVW     ,
    [RL78_IT_1_CA_MOV      ] = rl78Dis_1_CA_MOV      ,
    [RL78_IT_1_CB_MOVW     ] = rl78Dis_1_CB_MOVW     ,
    [RL78_IT_1_CC_MOV      ] = rl78Dis_1_CC_MOV      ,
    [RL78_IT_1_CD_MOV      ] = rl78Dis_1_CD_MOV      ,
    [RL78_IT_1_CE_MOV_SFR  ] = rl78Dis_1_CE_MOV_SFR  ,
    [RL78_IT_1_CE_MOV_PSW  ] = rl78Dis_1_CE_MOV_PSW  ,
    [RL78_IT_1_CE_MOV_CS   ] = rl78Dis_1_CE_MOV_CS   ,
    [RL78_IT_1_CE_MULHU    ] = rl78Dis_1_CE_MULHU    ,
    [RL78_IT_1_CE_MULH     ] = rl78Dis_1_CE_MULH     ,
    [RL78_IT_1_CE_DIVHU    ] = rl78Dis_1_CE_DIVHU    ,
    [RL78_IT_1_CE_DIVWU    ] = rl78Dis_1_CE_DIVWU    ,
    [RL78_IT_1_CE_MACHU    ] = rl78Dis_1_CE_MACHU    ,
    [RL78_IT_1_CE_MACH     ] = rl78Dis_1_CE_MACH     ,
    [RL78_IT_1_CF_MOV      ] = rl78Dis_1_CF_MOV      ,
    [RL78_IT_1_DX_CMP0     ] = rl78Dis_1_DX_CMP0     ,
    [RL78_IT_1_D4_CMP0     ] = rl78Dis_1_D4_CMP0     ,
    [RL78_IT_1_D5_CMP0     ] = rl78Dis_1_D5_CMP0     ,
    [RL78_IT_1_D6_MULU     ] = rl78Dis_1_D6_MULU     ,
    [RL78_IT_1_D7_RET      ] = rl78Dis_1_D7_RET      ,
    [RL78_IT_1_D8_MOV      ] = rl78Dis_1_D8_MOV      ,
    [RL78_IT_1_D9_MOV      ] = rl78Dis_1_D9_MOV      ,
    [RL78_IT_1_DC_BC       ] = rl78Dis_1_DC_BC       ,
    [RL78_IT_1_DD_BZ       ] = rl78Dis_1_DD_BZ       ,
    [RL78_IT_1_DE_BNC      ] = rl78Dis_1_DE_BNC      ,
    [RL78_IT_1_DF_BNZ      ] = rl78Dis_1_DF_BNZ      ,
    [RL78_IT_1_EX_ONEB     ] = rl78Dis_1_EX_ONEB     ,
    [RL78_IT_1_E4_ONEB     ] = rl78Dis_1_E4_ONEB     ,
    [RL78_IT_1_E5_ONEB     ] = rl78Dis_1_E5_ONEB     ,
    [RL78_IT_1_E6_ONEW     ] = rl78Dis_1_E6_ONEW     ,
    [RL78_IT_1_E7_ONEW     ] = rl78Dis_1_E7_ONEW     ,
    [RL78_IT_1_E8_MOV      ] = rl78Dis_1_E8_MOV      ,
    [RL78_IT_1_E9_MOV      ] = rl78Dis_1_E9_MOV      ,
    [RL78_IT_1_EC_BR       ] = rl78Dis_1_EC_BR       ,
    [RL78_IT_1_ED_BR       ] = rl78Dis_1_ED_BR       ,
    [RL78_IT_1_EE_BR       ] = rl78Dis_1_EE_BR       ,
    [RL78_IT_1_EF_BR       ] = rl78Dis_1_EF_BR       ,
    [RL78_IT_1_FX_CLRB     ] = rl78Dis_1_FX_CLRB     ,
    [RL78_IT_1_F4_CLRB     ] = rl78Dis_1_F4_CLRB     ,
    [RL78_IT_1_F5_CLRB     ] = rl78Dis_1_F5_CLRB     ,
    [RL78_IT_1_F6_CLRW     ] = rl78Dis_1_F6_CLRW     ,
    [RL78_IT_1_F7_CLRW     ] = rl78Dis_1_F7_CLRW     ,
    [RL78_IT_1_F8_MOV      ] = rl78Dis_1_F8_MOV      ,
    [RL78_IT_1_F9_MOV      ] = rl78Dis_1_F9_MOV      ,
    [RL78_IT_1_FC_CALL     ] = rl78Dis_1_FC_CALL     ,
    [RL78_IT_1_FD_CALL     ] = rl78Dis_1_FD_CALL     ,
    [RL78_IT_1_FE_CALL     ] = rl78Dis_1_FE_CALL     ,
    [RL78_IT_1_XA_MOVW     ] = rl78Dis_1_XA_MOVW     ,
    [RL78_IT_1_XB_MOVW     ] = rl78Dis_1_XB_MOVW     ,

    [RL78_IT_2_0X_ADD      ] = rl78Dis_2_0X_ADD      ,
    [RL78_IT_2_09_ADDW     ] = rl78Dis_2_09_ADDW     ,
    [RL78_IT_2_0Y_ADD      ] = rl78Dis_2_0Y_ADD      ,
    [RL78_IT_2_1X_ADDC     ] = rl78Dis_2_1X_ADDC     ,
    [RL78_IT_2_1Y_ADDC     ] = rl78Dis_2_1Y_ADDC     ,
    [RL78_IT_2_2X_SUB      ] = rl78Dis_2_2X_SUB      ,
    [RL78_IT_2_29_SUBW     ] = rl78Dis_2_29_SUBW     ,
    [RL78_IT_2_2Y_SUB      ] = rl78Dis_2_2Y_SUB      ,
    [RL78_IT_2_3X_SUBC     ] = rl78Dis_2_3X_SUBC     ,
    [RL78_IT_2_3Y_SUBC     ] = rl78Dis_2_3Y_SUBC     ,
    [RL78_IT_2_4X_CMP      ] = rl78Dis_2_4X_CMP      ,
    [RL78_IT_2_49_CMPW     ] = rl78Dis_2_49_CMPW     ,
    [RL78_IT_2_4Y_CMP      ] = rl78Dis_2_4Y_CMP      ,
    [RL78_IT_2_5X_AND      ] = rl78Dis_2_5X_AND      ,
    [RL78_IT_2_59_INC      ] = rl78Dis_2_59_INC      ,
    [RL78_IT_2_5Y_AND      ] = rl78Dis_2_5Y_AND      ,
    [RL78_IT_2_6X_OR       ] = rl78Dis_2_6X_OR       ,
    [RL78_IT_2_69_DEC      ] = rl78Dis_2_69_DEC      ,
    [RL78_IT_2_6Y_OR       ] = rl78Dis_2_6Y_OR       ,
    [RL78_IT_2_7X_XOR      ] = rl78Dis_2_7X_XOR      ,
    [RL78_IT_2_79_INCW     ] = rl78Dis_2_79_INCW     ,
    [RL78_IT_2_7Y_XOR      ] = rl78Dis_2_7Y_XOR      ,
    [RL78_IT_2_80_ADD      ] = rl78Dis_2_80_ADD      ,
    [RL78_IT_2_82_ADD      ] = rl78Dis_2_82_ADD      ,
    [RL78_IT_2_89_DECW     ] = rl78Dis_2_89_DECW     ,
    [RL78_IT_2_8X_XCH      ] = rl78Dis_2_8X_XCH      ,
    [RL78_IT_2_90_ADDC     ] = rl78Dis_2_90_ADDC     ,
    [RL78_IT_2_92_ADDC     ] = rl78Dis_2_92_ADDC     ,
    [RL78_IT_2_A0_SUB      ] = rl78Dis_2_A0_SUB      ,
    [RL78_IT_2_A2_SUB      ] = rl78Dis_2_A2_SUB      ,
    [RL78_IT_2_A8_XCH      ] = rl78Dis_2_A8_XCH      ,
    [RL78_IT_2_A9_XCH      ] = rl78Dis_2_A9_XCH      ,
    [RL78_IT_2_AA_XCH      ] = rl78Dis_2_AA_XCH      ,
    [RL78_IT_2_AB_XCH      ] = rl78Dis_2_AB_XCH      ,
    [RL78_IT_2_AC_XCH      ] = rl78Dis_2_AC_XCH      ,
    [RL78_IT_2_AD_XCH      ] = rl78Dis_2_AD_XCH      ,
    [RL78_IT_2_AE_XCH      ] = rl78Dis_2_AE_XCH      ,
    [RL78_IT_2_AF_XCH      ] = rl78Dis_2_AF_XCH      ,
    [RL78_IT_2_B0_SUBC     ] = rl78Dis_2_B0_SUBC     ,
    [RL78_IT_2_B2_SUBC     ] = rl78Dis_2_B2_SUBC     ,
    [RL78_IT_2_B8_MOV      ] = rl78Dis_2_B8_MOV      ,
    [RL78_IT_2_B9_XCH      ] = rl78Dis_2_B9_XCH      ,
    [RL78_IT_2_C0_CMP      ] = rl78Dis_2_C0_CMP      ,
    [RL78_IT_2_C2_CMP      ] = rl78Dis_2_C2_CMP      ,
    [RL78_IT_2_C3_BH       ] = rl78Dis_2_C3_BH       ,
    [RL78_IT_2_C8_SKC      ] = rl78Dis_2_C8_SKC      ,
    [RL78_IT_2_C9_MOV      ] = rl78Dis_2_C9_MOV      ,
    [RL78_IT_2_CB_BR       ] = rl78Dis_2_CB_BR       ,
    [RL78_IT_2_CC_BRK      ] = rl78Dis_2_CC_BRK      ,
    [RL78_IT_2_CD_POP      ] = rl78Dis_2_CD_POP      ,
    [RL78_IT_2_CE_MOVS     ] = rl78Dis_2_CE_MOVS     ,
    [RL78_IT_2_D0_AND      ] = rl78Dis_2_D0_AND      ,
    [RL78_IT_2_D2_AND      ] = rl78Dis_2_D2_AND      ,
    [RL78_IT_2_D3_BNH      ] = rl78Dis_2_D3_BNH      ,
    [RL78_IT_2_D8_SKNC     ] = rl78Dis_2_D8_SKNC     ,
    [RL78_IT_2_D9_MOV      ] = rl78Dis_2_D9_MOV      ,
    [RL78_IT_2_DB_ROR      ] = rl78Dis_2_DB_ROR      ,
    [RL78_IT_2_DC_ROLC     ] = rl78Dis_2_DC_ROLC     ,
    [RL78_IT_2_DD_PUSH     ] = rl78Dis_2_DD_PUSH     ,
    [RL78_IT_2_DE_CMPS     ] = rl78Dis_2_DE_CMPS     ,
    [RL78_IT_2_E0_OR       ] = rl78Dis_2_E0_OR       ,
    [RL78_IT_2_E2_OR       ] = rl78Dis_2_E2_OR       ,
    [RL78_IT_2_E3_SKH      ] = rl78Dis_2_E3_SKH      ,
    [RL78_IT_2_E8_SKZ      ] = rl78Dis_2_E8_SKZ      ,
    [RL78_IT_2_E9_MOV      ] = rl78Dis_2_E9_MOV      ,
    [RL78_IT_2_EB_ROL      ] = rl78Dis_2_EB_ROL      ,
    [RL78_IT_2_EC_RETB     ] = rl78Dis_2_EC_RETB     ,
    [RL78_IT_2_ED_HALT     ] = rl78Dis_2_ED_HALT     ,
    [RL78_IT_2_F0_XOR      ] = rl78Dis_2_F0_XOR      ,
    [RL78_IT_2_F2_XOR      ] = rl78Dis_2_F2_XOR      ,
    [RL78_IT_2_F3_SKNH     ] = rl78Dis_2_F3_SKNH     ,
    [RL78_IT_2_F8_SKNZ     ] = rl78Dis_2_F8_SKNZ     ,
    [RL78_IT_2_F9_MOV      ] = rl78Dis_2_F9_MOV      ,
    [RL78_IT_2_FB_RORC     ] = rl78Dis_2_FB_RORC     ,
    [RL78_IT_2_FC_RETI     ] = rl78Dis_2_FC_RETI     ,
    [RL78_IT_2_FD_STOP     ] = rl78Dis_2_FD_STOP     ,
    [RL78_IT_2_XE_ROLWC    ] = rl78Dis_2_XE_ROLWC    ,
    [RL78_IT_2_XF_SEL      ] = rl78Dis_2_XF_SEL      ,
    [RL78_IT_2_XA_CALL     ] = rl78Dis_2_XA_CALL     ,
    [RL78_IT_2_XX_CALLT    ] = rl78Dis_2_XX_CALLT    ,

    [RL78_IT_3_X0_SET1     ] = rl78Dis_3_X0_SET1     ,
    [RL78_IT_3_X1_MOV1     ] = rl78Dis_3_X1_MOV1     ,
    [RL78_IT_3_X2_SET1     ] = rl78Dis_3_X2_SET1     ,
    [RL78_IT_3_X3_CLR1     ] = rl78Dis_3_X3_CLR1     ,
    [RL78_IT_3_X4_MOV1     ] = rl78Dis_3_X4_MOV1     ,
    [RL78_IT_3_X5_AND1     ] = rl78Dis_3_X5_AND1     ,
    [RL78_IT_3_X6_OR1      ] = rl78Dis_3_X6_OR1      ,
    [RL78_IT_3_X7_XOR1     ] = rl78Dis_3_X7_XOR1     ,
    [RL78_IT_3_X8_CLR1     ] = rl78Dis_3_X8_CLR1     ,
    [RL78_IT_3_X9_MOV1     ] = rl78Dis_3_X9_MOV1     ,
    [RL78_IT_3_XA_SET1     ] = rl78Dis_3_XA_SET1     ,
    [RL78_IT_3_XB_CLR1     ] = rl78Dis_3_XB_CLR1     ,
    [RL78_IT_3_XC_MOV1     ] = rl78Dis_3_XC_MOV1     ,
    [RL78_IT_3_XD_AND1     ] = rl78Dis_3_XD_AND1     ,
    [RL78_IT_3_XE_OR1      ] = rl78Dis_3_XE_OR1      ,
    [RL78_IT_3_XF_XOR1     ] = rl78Dis_3_XF_XOR1     ,
    [RL78_IT_3_7A_EI       ] = rl78Dis_3_7A_EI       ,
    [RL78_IT_3_7B_DI       ] = rl78Dis_3_7B_DI       ,
    [RL78_IT_3_80_SET1     ] = rl78Dis_3_80_SET1     ,
    [RL78_IT_3_88_CLR1     ] = rl78Dis_3_88_CLR1     ,
    [RL78_IT_3_C0_NOT1     ] = rl78Dis_3_C0_NOT1     ,
    [RL78_IT_3_Y1_MOV1     ] = rl78Dis_3_Y1_MOV1     ,
    [RL78_IT_3_Y2_SET1     ] = rl78Dis_3_Y2_SET1     ,
    [RL78_IT_3_Y3_CLR1     ] = rl78Dis_3_Y3_CLR1     ,
    [RL78_IT_3_Y4_MOV1     ] = rl78Dis_3_Y4_MOV1     ,
    [RL78_IT_3_Y5_AND1     ] = rl78Dis_3_Y5_AND1     ,
    [RL78_IT_3_Y6_OR1      ] = rl78Dis_3_Y6_OR1      ,
    [RL78_IT_3_Y7_XOR1     ] = rl78Dis_3_Y7_XOR1     ,
    [RL78_IT_3_Y9_MOV1     ] = rl78Dis_3_Y9_MOV1     ,
    [RL78_IT_3_YA_SET1     ] = rl78Dis_3_YA_SET1     ,
    [RL78_IT_3_YB_CLR1     ] = rl78Dis_3_YB_CLR1     ,
    [RL78_IT_3_YC_MOV1     ] = rl78Dis_3_YC_MOV1     ,
    [RL78_IT_3_YD_AND1     ] = rl78Dis_3_YD_AND1     ,
    [RL78_IT_3_YE_OR1      ] = rl78Dis_3_YE_OR1      ,
    [RL78_IT_3_YF_XOR1     ] = rl78Dis_3_YF_XOR1     ,

    [RL78_IT_4_X0_BTCLR    ] = rl78Dis_4_X0_BTCLR    ,
    [RL78_IT_4_X1_BTCLR    ] = rl78Dis_4_X1_BTCLR    ,
    [RL78_IT_4_X2_BT       ] = rl78Dis_4_X2_BT       ,
    [RL78_IT_4_X3_BT       ] = rl78Dis_4_X3_BT       ,
    [RL78_IT_4_X4_BF       ] = rl78Dis_4_X4_BF       ,
    [RL78_IT_4_X5_BF       ] = rl78Dis_4_X5_BF       ,
    [RL78_IT_4_X7_SHL      ] = rl78Dis_4_X7_SHL      ,
    [RL78_IT_4_X8_SHL      ] = rl78Dis_4_X8_SHL      ,
    [RL78_IT_4_X9_SHL      ] = rl78Dis_4_X9_SHL      ,
    [RL78_IT_4_XA_SHR      ] = rl78Dis_4_XA_SHR      ,
    [RL78_IT_4_XB_SAR      ] = rl78Dis_4_XB_SAR      ,
    [RL78_IT_4_Y0_BTCLR    ] = rl78Dis_4_Y0_BTCLR    ,
    [RL78_IT_4_Y1_BTCLR    ] = rl78Dis_4_Y1_BTCLR    ,
    [RL78_IT_4_Y2_BT       ] = rl78Dis_4_Y2_BT       ,
    [RL78_IT_4_Y3_BT       ] = rl78Dis_4_Y3_BT       ,
    [RL78_IT_4_Y4_BF       ] = rl78Dis_4_Y4_BF       ,
    [RL78_IT_4_Y5_BF       ] = rl78Dis_4_Y5_BF       ,
    [RL78_IT_4_XC_SHLW     ] = rl78Dis_4_XC_SHLW     ,
    [RL78_IT_4_XD_SHLW     ] = rl78Dis_4_XD_SHLW     ,
    [RL78_IT_4_XE_SHRW     ] = rl78Dis_4_XE_SHRW     ,
    [RL78_IT_4_XF_SARW     ] = rl78Dis_4_XF_SARW

};

static void fillInstructionBytes(rl78P rl78, Uns32 n, Uns32 thisPC, char *buf) {

    Uns32 i;
    Uns32 len = 0;

    // calculate size of skip instruction prefix
    Uns32 skipPrefixBytes = rl78->len_instByteAndSkip - rl78->len_instByte;

    // include prefix hex bytes
    thisPC -= skipPrefixBytes;

    for (i=0; i<rl78->len_instByteAndSkip; i++) {
        len += snprintf(&buf[len], (n - len), "%02x ", vmicxtFetch1Byte((vmiProcessorP)rl78, thisPC + i));
    }
}

static const char* skipPrefix(rl78P rl78) {

    if (rl78->skipCondition != en_Cond_T) {

        static const char *map[] = {
            [en_Cond_C]  = "SKC ; ",
            [en_Cond_NC] = "SKNC ; ",
            [en_Cond_H]  = "SKH ; ",
            [en_Cond_Z]  = "SKZ ; ",
            [en_Cond_NH] = "SKNH ; ",
            [en_Cond_NZ] = "SKNZ ; "
        };

        return map[rl78->skipCondition];

    } else {

        return "";
    }
}

//
// Default disassembler callback
//
static RL78_DISPATCH_FN(rl78DisDefault) {

    // get output buffer for disassembly
    char *result = (char *)userData;

    // default disassembly just shows instruction pattern
    sprintf(result, "??? instruction:0x%02x 0x%02x 0x%02x 0x%02x 0x%02x", instr[0], instr[1], instr[2], instr[3], instr[4]);
}

//
// RL78 disassembler
//
VMI_DISASSEMBLE_FN(rl78Disassemble) {

    // static buffer to hold disassembly result
    static char result[256];

    // disassemble, filling the result buffer
    rl78Decode((rl78P) processor, thisPC, &dispatchTable, rl78DisDefault, &result);

    // return the result
    return result;
}

