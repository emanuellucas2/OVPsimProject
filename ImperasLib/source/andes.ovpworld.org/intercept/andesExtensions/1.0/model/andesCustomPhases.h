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
// Phases for custom instruction code insertion
//
#define ANDES_CUSTOM_ITYPE                  0
#define ANDES_CUSTOM_DECODE32               1
#define ANDES_CUSTOM_INSTRUCTION_ATTRS      2
#define ANDES_CUSTOM_MORPH_FUNCTIONS        3
#define ANDES_CUSTOM_MORPH_TABLE            4
#define ANDES_CUSTOM_INIT                   5
