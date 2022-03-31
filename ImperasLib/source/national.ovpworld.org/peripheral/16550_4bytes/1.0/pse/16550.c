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

#include <stdio.h>

#include "pse.igen.h"

#define PREFIX "16550"

// Default frequency of UART Reference clock
#define DEFAULT_REF_CLK_FREQ 18432000

// Maximum FIFO depth supported
#define MAXFIFO 128

// Default fifo depth
#define DEFAULT_FIFO_SIZE   16

// 16550 model support code - implements the base 16550 functionality
#include "16550.c.h"

PPM_CONSTRUCTOR_CB(constructor) {

    init16550();

}

PPM_DESTRUCTOR_CB(destructor) {

    if(state.channel >= 0) {
        bhmSerClose(state.channel);
    }

}

PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

