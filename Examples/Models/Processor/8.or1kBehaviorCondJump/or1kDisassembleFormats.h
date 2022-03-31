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

#ifndef OR1K_DISASSEMBLE_FORMATS_H
#define OR1K_DISASSEMBLE_FORMATS_H

//
// These are placeholders in disassembly decoder
//
#define EMIT_R1             '\001'
#define EMIT_R2             '\002'
#define EMIT_R3             '\003'
#define EMIT_XIMM           '\004'
#define EMIT_TARGET         '\005'

//
// These are placeholders in disassembly format strings
//
#define EMIT_R1_S           "\001"
#define EMIT_R2_S           "\002"
#define EMIT_R3_S           "\003"
#define EMIT_XIMM_S         "\004"
#define EMIT_TARGET_S       "\005"

//
// These are disassembly format strings
//
#define FMT_XIMM            EMIT_XIMM_S
#define FMT_TARGET          EMIT_TARGET_S
#define FMT_R1              EMIT_R1_S
#define FMT_R1_R2           EMIT_R1_S "," EMIT_R2_S
#define FMT_R1_XIMM         EMIT_R1_S "," EMIT_XIMM_S
#define FMT_R1_R2_XIMM      EMIT_R1_S "," EMIT_R2_S "," EMIT_XIMM_S
#define FMT_R1_R2_R3        EMIT_R1_S "," EMIT_R2_S "," EMIT_R3_S

#endif

