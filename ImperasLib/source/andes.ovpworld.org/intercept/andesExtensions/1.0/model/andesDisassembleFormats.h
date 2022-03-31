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

#pragma once

//
// These are placeholders in disassembly decoder
//
#define EMIT_R1         '\001'
#define EMIT_R2         '\002'
#define EMIT_R3         '\003'
#define EMIT_R4         '\004'
#define EMIT_CS1        '\005'
#define EMIT_CX1        '\006'
#define EMIT_CS2        '\007'
#define EMIT_CX2        '\010'
#define EMIT_TGT        '\011'
#define EMIT_RM         '\012'

//
// These are placeholders in disassembly format strings
//
#define EMIT_R1_S       "\001"
#define EMIT_R2_S       "\002"
#define EMIT_R3_S       "\003"
#define EMIT_R4_S       "\004"
#define EMIT_CS1_S      "\005"
#define EMIT_CX1_S      "\006"
#define EMIT_CS2_S      "\007"
#define EMIT_CX2_S      "\010"
#define EMIT_TGT_S      "\011"
#define EMIT_RM_S       "\012"

//
// These are disassembly format strings
//
#define FMT_NONE            ""
#define FMT_R1_SIMM         EMIT_R1_S "," EMIT_CS1_S
#define FMT_R1_UIMM_TGT     EMIT_R1_S "," EMIT_CS2_S "," EMIT_TGT_S
#define FMT_R1_R2_UIMM_UIMM EMIT_R1_S "," EMIT_R2_S "," EMIT_CS1_S "," EMIT_CS2_S
#define FMT_R1_R2           EMIT_R1_S "," EMIT_R2_S
#define FMT_R1_R2_R3        EMIT_R1_S "," EMIT_R2_S "," EMIT_R3_S
#define FMT_R1_R2_R3_RM     EMIT_R1_S "," EMIT_R2_S "," EMIT_R3_S "," EMIT_RM_S
#define FMT_R1_OFF          EMIT_R1_S ",[" EMIT_CS1_S "]"
#define FMT_UIMM            EMIT_CS1_S
#define FMT_R1_OFF_R2       EMIT_R1_S "," EMIT_CS1_S "(" EMIT_R2_S ")"
#define FMT_R1_MEM2_RM      EMIT_R1_S ",(" EMIT_R2_S ")," EMIT_RM_S
