/*
 * Copyright (c) 2011-2014 Posedge Software Inc., www.posedgesoft.com
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


#ifndef M16C_VARIANT_H
#define M16C_VARIANT_H


typedef enum m16cVariantE {
    VAR_M16C = 0,
    VAR_M16C_TINY = VAR_M16C,
    VAR_M16C_20 = VAR_M16C,
    VAR_M16C_60 = VAR_M16C,
    VAR_R8C,
    VAR_M32C,
} m16cVariant;

#endif
