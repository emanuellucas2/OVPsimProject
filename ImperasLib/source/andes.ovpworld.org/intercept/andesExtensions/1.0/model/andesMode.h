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
// This enumerates Andes operating modes
//
typedef enum andesModeE {
    ANM_NA      = 0,
    ANM_RVCOMPM = (1<<0),   // whether RV compatibility mode enabled
    ANM_MSA_UNA = (1<<1),   // whether unaligned accesses enabled
    ANM_MHSP    = (1<<2),   // whether M-mode HSP enabled
    ANM_SHSP    = (1<<3),   // whether S-mode HSP enabled
    ANM_UHSP    = (1<<4),   // whether U-mode HSP enabled
} andesMode;

