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

#include "pse.igen.h"
#define FUNC_NAME __FUNCTION__
#define INFO bhmMessage("I", FUNC_NAME, "val=0x%08x", data)

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_WRITE_CB(WD_CMR_wcb) {
    // YOUR CODE HERE (WD_CMR_wcb)
    bp1_REG_data.WD_CMR.value = data;
    INFO;
}

PPM_REG_WRITE_CB(WD_CR_wcb) {
    // YOUR CODE HERE (WD_CR_wcb)
    bp1_REG_data.WD_CR.value = data;
    INFO;
}

PPM_REG_WRITE_CB(WD_OMR_wcb) {
    // YOUR CODE HERE (WD_OMR_wcb)
    bp1_REG_data.WD_OMR.value = data;
    INFO;
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

