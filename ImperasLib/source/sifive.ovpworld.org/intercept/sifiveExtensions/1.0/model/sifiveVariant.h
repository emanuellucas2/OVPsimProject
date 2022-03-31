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
// This enumerates SiFive extension configurable architecture features
//
typedef enum sifiveVariantE {

    S5V_NA      = 0,

    // custom CSRs
    S5V_FDCP    = (1<<0),   // Feature Disable CSR present
    S5V_BPM     = (1<<1),   // Branch Prediction Mode CSR present
    S5V_PWRD    = (1<<2),   // PowerDial CSR present
    S5V_CSR     = S5V_FDCP|S5V_BPM|S5V_PWRD,

    // custom instructions
    S5V_CFLUSH  = (1<<3),   // CFLUSH instruction present
    S5V_CEASE   = (1<<4),   // CEASE instruction present
    S5V_INST    = S5V_CFLUSH|S5V_CEASE,

} sifiveVariant;

