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

#include "v850Config.h"
#include "v850Variant.h"

const struct v850ConfigS v850ConfigTable[] = {
    ////////////////////////////////////////////////////////////////////////////
    // ISA CONFIGURATIONS
    ////////////////////////////////////////////////////////////////////////////
    {.name = "RH850G3M", .arch = RH850G3M},
    {0} // null terminator
};
