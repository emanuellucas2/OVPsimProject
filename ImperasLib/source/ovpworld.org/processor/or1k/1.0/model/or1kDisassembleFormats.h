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

#ifndef OR1K_DISASSEMBLE_FORMATS_H
#define OR1K_DISASSEMBLE_FORMATS_H

//
// These are placeholders in disassembly decoder
//
#define EMIT_R1             '\001'
#define EMIT_R2             '\002'
#define EMIT_R3             '\003'
#define EMIT_UIMM           '\004'
#define EMIT_XIMM           '\005'
#define EMIT_TARGET         '\006'

//
// These are placeholders in disassembly format strings
//
#define EMIT_R1_S           "\001"
#define EMIT_R2_S           "\002"
#define EMIT_R3_S           "\003"
#define EMIT_UIMM_S         "\004"
#define EMIT_XIMM_S         "\005"
#define EMIT_TARGET_S       "\006"

//
// These are disassembly format strings
//
#define FMT_NONE            ""
#define FMT_XIMM            EMIT_XIMM_S
#define FMT_TARGET          EMIT_TARGET_S
#define FMT_R1              EMIT_R1_S
#define FMT_R1_R2           EMIT_R1_S "," EMIT_R2_S
#define FMT_R1_XIMM         EMIT_R1_S "," EMIT_XIMM_S
#define FMT_R1_R2_UIMM      EMIT_R1_S "," EMIT_R2_S "," EMIT_UIMM_S
#define FMT_R1_R2_XIMM      EMIT_R1_S "," EMIT_R2_S "," EMIT_XIMM_S
#define FMT_R1_R2_R3        EMIT_R1_S "," EMIT_R2_S "," EMIT_R3_S
#define FMT_R1_OFFSET_R2    EMIT_R1_S "," EMIT_XIMM_S "(" EMIT_R2_S ")"
#define FMT_OFFSET_R1_R2    EMIT_XIMM_S "(" EMIT_R1_S ")," EMIT_R2_S

#endif

