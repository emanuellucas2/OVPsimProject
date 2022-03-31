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

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_WRITE_CB(PIO_CODR_wcb) {
    // YOUR CODE HERE (PIO_CODR_wcb)
    bp1_REG_data.PIO_CODR.value = data;
}

PPM_REG_WRITE_CB(PIO_IDR_wcb) {
    // YOUR CODE HERE (PIO_IDR_wcb)
    bp1_REG_data.PIO_IDR.value = data;
}

PPM_REG_WRITE_CB(PIO_IER_wcb) {
    // YOUR CODE HERE (PIO_IER_wcb)
    bp1_REG_data.PIO_IER.value = data;
}

PPM_REG_WRITE_CB(PIO_IFDR_wcb) {
    // YOUR CODE HERE (PIO_IFDR_wcb)
    bp1_REG_data.PIO_IFDR.value = data;
}

PPM_REG_WRITE_CB(PIO_IFER_wcb) {
    // YOUR CODE HERE (PIO_IFER_wcb)
    bp1_REG_data.PIO_IFER.value = data;
}

PPM_REG_WRITE_CB(PIO_ODR_wcb) {
    // YOUR CODE HERE (PIO_ODR_wcb)
    bp1_REG_data.PIO_ODR.value = data;
}

PPM_REG_WRITE_CB(PIO_OER_wcb) {
    // YOUR CODE HERE (PIO_OER_wcb)
    bp1_REG_data.PIO_OER.value = data;
}

PPM_REG_WRITE_CB(PIO_PDR_wcb) {
    // YOUR CODE HERE (PIO_PDR_wcb)
    bp1_REG_data.PIO_PDR.value = data;
}

PPM_REG_WRITE_CB(PIO_PER_wcb) {
    // YOUR CODE HERE (PIO_PER_wcb)
    bp1_REG_data.PIO_PER.value = data;
}

PPM_REG_WRITE_CB(PIO_SODR_wcb) {
    // YOUR CODE HERE (PIO_SODR_wcb)
    bp1_REG_data.PIO_SODR.value = data;
}

PPM_NET_CB(P_wcb) {
    // YOUR CODE HERE (P_wcb)
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

