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


#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
teq   rD, rA, rB :: (rA == rB) ? pc = rD
tgt   rD, rA, rB :: (rA > rB)  ? pc = rD
tlt   rD, rA, rB :: (rA < rB)  ? pc = rD
halt             ::

*/

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

typedef struct labelEntryS {
    char *name;
    unsigned int address;
} labelEntry, *labelEntryP;

static labelEntry labels[1024];
static int labelHi = 0;

void labelInsert (char *name, unsigned int address) {
    labels[labelHi].name = strdup(name);
    labels[labelHi].address = address;
    labelHi++;
    return;
}

unsigned int labelGetAddress(char *name) {
    int this = 0;
    while (this < labelHi) {
        if (strcmp(name, labels[this].name) == 0) {
            return labels[this].address;
        }
        this++;
    }
    return 0;
}

void assemble(FILE *ip, FILE *op) {
    char line[256];
    char *pline = line;
    char *line0 = line;
    int rD, rA, rB;
    int imm16;

    unsigned int origin;
    char label[256];

    unsigned int address = 0x0;

    while (fgets(line0, 256, ip)) {
        pline  = line0;

//        printf("\nLINE[%d]: %s", strlen(line0), pline);

        // ignore leading whitespace
        while((*pline==' ') || (*pline=='\t')) {
            pline++;
        }

        // Parse various formats

        // parse origin
        // .org <origin>
        //
        if (sscanf(pline, ".org %x", &origin) == 1) {
//            printf("ORIGIN: 0x%x\n", origin);
            address = origin;

        // parse label
        // .label <string>
        //
        } else if (sscanf(pline, ".label %s", (char*)&label) == 1) {
//            printf("LABEL: 0x%08x: %s\n", address, label);
            labelInsert(label, address);

            if (strcmp(label, "_start")==0) {
                fprintf(op, "_start: %08x\n", address);
            }
        //
        // parse movlo
        //
        } else if (sscanf(pline, "movlo r%d, %x", &rD, &imm16) == 2) {
//            printf("INSTRUCTION: 0x%08x: movlo REG(%d) = 0x%x\n", address, rD, imm16);
            fprintf(op, "%08x: %02x%02x%04x\n", address, MOVLO, rD, imm16);
            address+=4;

        //
        // parse movlo
        //
        } else if (sscanf(pline, "movlo r%d, LO(%[0-9,a-z,A-Z])", &rD, label) == 2) {
            imm16 = labelGetAddress(label) & 0xffff;
//            printf("INSTRUCTION: 0x%08x: movlo REG(%d) = LO(%s=0x%x)\n", address, rD, label, imm16);
            fprintf(op, "%08x: %02x%02x%04x\n", address, MOVLO, rD, imm16);
            address+=4;

        //
        // parse movhi
        //
        } else if (sscanf(pline, "movhi r%d, %x", &rD, &imm16) == 2) {
//            printf("INSTRUCTION: 0x%08x: movhi REG(%d) = 0x%x\n", address, rD, imm16);
            fprintf(op, "%08x: %02x%02x%04x\n", address, MOVHI, rD, imm16);
            address+=4;

        //
        // parse movlo
        //
        } else if (sscanf(pline, "movhi r%d, HI(%[0-9,a-z,A-Z])", &rD, label) == 2) {
            imm16 = labelGetAddress(label) >> 16;
//            printf("INSTRUCTION: 0x%08x: movhi REG(%d) = HI(%s=0x%x)\n", address, rD, label, imm16);
            fprintf(op, "%08x: %02x%02x%04x\n", address, MOVHI, rD, imm16);
            address+=4;

        //
        // parse movr
        //
        } else if (sscanf(pline, "movr r%d, r%d", &rD, &rA) == 2) {
//            printf("INSTRUCTION: 0x%08x: movr REG(%d) = REG(%d)\n", address, rD, rA);
            fprintf(op, "%08x: %02x%02x%02x%02x\n", address, MOVR, rD, rA, 0);
            address+=4;

        //
        // parse add
        //
        } else if (sscanf(pline, "add r%d, r%d, r%d", &rD, &rA, &rB) == 3) {
//            printf("INSTRUCTION: 0x%08x: add REG(%d) = REG(%d) + REG(%d)\n", address, rD, rA, rB);
            fprintf(op, "%08x: %02x%02x%02x%02x\n", address, ADD, rD, rA, rB);
            address+=4;

        //
        // parse sub
        //
        } else if (sscanf(pline, "sub r%d, r%d, r%d", &rD, &rA, &rB) == 3) {
//            printf("INSTRUCTION: 0x%08x: sub REG(%d) = REG(%d) - REG(%d)\n", address, rD, rA, rB);
            fprintf(op, "%08x: %02x%02x%02x%02x\n", address, SUB, rD, rA, rB);
            address+=4;

        //
        // parse ld
        //
        } else if (sscanf(pline, "ld r%d, r%d", &rD, &rA) == 2) {
//            printf("INSTRUCTION: 0x%08x: ld REG(%d) = MEM(REG(%d))\n", address, rD, rA);
            fprintf(op, "%08x: %02x%02x%02x%02x\n", address, LD, rD, rA, 0);
            address+=4;
        //
        // parse st
        //
        } else if (sscanf(pline, "st r%d, r%d", &rD, &rA) == 2) {
//            printf("INSTRUCTION: 0x%08x: st MEM(REG(%d)) = REG(%d)\n", address, rD, rA);
            fprintf(op, "%08x: %02x%02x%02x%02x\n", address, ST, rD, rA, 0);
            address+=4;

        //
        // parse jmp
        //
        } else if (sscanf(pline, "jmp r%d", &rA) == 1) {
//            printf("INSTRUCTION: 0x%08x: jmp REG(%d)\n", address, rA);
            fprintf(op, "%08x: %02x%02x%02x%02x\n", address, JMP, 0, rA, 0);
            address+=4;

        //
        // parse beq
        //
        } else if (sscanf(pline, "beq r%d, r%d, r%d", &rD, &rA, &rB) == 3) {
//            printf("INSTRUCTION: 0x%08x: beq REG(%d), REG(%d), REG(%d)\n", address, rD, rA, rB);
            fprintf(op, "%08x: %02x%02x%02x%02x\n", address, BEQ, rD, rA, rB);
            address+=4;

        //
        // parse bgt
        //
        } else if (sscanf(pline, "bgt r%d, r%d, r%d", &rD, &rA, &rB) == 3) {
//            printf("INSTRUCTION: 0x%08x: bgt REG(%d), REG(%d), REG(%d)\n", address, rD, rA, rB);
            fprintf(op, "%08x: %02x%02x%02x%02x\n", address, BGT, rD, rA, rB);
            address+=4;

        //
        // parse blt
        //
        } else if (sscanf(pline, "blt r%d, r%d, r%d", &rD, &rA, &rB) == 3) {
//            printf("INSTRUCTION: 0x%08x: blt REG(%d), REG(%d), REG(%d)\n", address, rD, rA, rB);
            fprintf(op, "%08x: %02x%02x%02x%02x\n", address, BLT, rD, rA, rB);
            address+=4;

        //
        // parse halt
        //
        } else if (strncmp(pline, "halt", 4) == 0) {
//            printf("INSTRUCTION: 0x%08x: halt\n", address);
            fprintf(op, "%08x: %02x%02x%02x%02x\n", address, HALT, 0, 0, 0);
            address+=4;

        // parse empty line
        // \n
        //
        } else if (pline[0] == '\n' || pline[0] == '#') {
//            printf("EMPTY:\n");

        } else {
            fprintf(stderr, "Error, cannot parse %s", pline);
            exit(1);
        }
    }

}

int main (int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage, %s <file.s> <file.hex>\n", argv[0]);
        exit(1);
    }
    FILE *ip, *op;

    ip = fopen(argv[1], "r");
    if (ip == NULL) {
        fprintf(stderr, "Error, cannot open %s for reading\n", argv[1]);
    }

    op = fopen(argv[2], "w");
    if (op == NULL) {
        fprintf(stderr, "Error, cannot open %s for writing\n", argv[2]);
    }

    assemble(ip, op);
    fclose(ip);
    fclose(op);

    return 0;
}
