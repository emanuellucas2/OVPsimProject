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


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                           Imperas/OVP Generated
//                          Tue Jul  2 00:49:23 2013
//
////////////////////////////////////////////////////////////////////////////////

#include "pse.igen.h"

#define PREFIX "TzpcBP147"

//////////////////////////////// Callback stubs ////////////////////////////////

static void updateProt(Uns32 *reg, Uns32 value, ppmNetHandle *net0, Bool set) {

    // Only low 8 bits are used
    Uns8 mask = value;
    Uns8 old  = *reg;
    Uns8 new  = set ? (old | mask) : (old & ~mask);

    if (new != old) {

        // Update stored value
        *reg = new;

        // Update nets
        Uns32 i;
        for (i = 0; i < 16; i++) {
            // Using net0[i] is cheating because net0 doesn't actually point to an array, but it should work
            mask = 1 << i;
            if ((old & mask) != (new & mask)) {
                ppmWriteNet(net0[i], (new & mask) ? 1 : 0);
            }
        }
    }
}

PPM_REG_WRITE_CB(WriteTZPCDECPROT0Clr) {
    updateProt(&bport1_ab_data.TZPCDECPROT0Stat.value, data, &handles.TZPCDECPROT0_0, 0);
}

PPM_REG_WRITE_CB(WriteTZPCDECPROT0Set) {
    updateProt(&bport1_ab_data.TZPCDECPROT0Stat.value, data, &handles.TZPCDECPROT0_0, 1);
}

PPM_REG_WRITE_CB(WriteTZPCDECPROT1Clr) {
    updateProt(&bport1_ab_data.TZPCDECPROT1Stat.value, data, &handles.TZPCDECPROT1_0, 0);
}

PPM_REG_WRITE_CB(WriteTZPCDECPROT1Set) {
    updateProt(&bport1_ab_data.TZPCDECPROT1Stat.value, data, &handles.TZPCDECPROT1_0, 1);
}

PPM_REG_WRITE_CB(WriteTZPCDECPROT2Clr) {
    updateProt(&bport1_ab_data.TZPCDECPROT2Stat.value, data, &handles.TZPCDECPROT2_0, 0);
}

PPM_REG_WRITE_CB(WriteTZPCDECPROT2Set) {
    updateProt(&bport1_ab_data.TZPCDECPROT2Stat.value, data, &handles.TZPCDECPROT2_0, 1);
}

PPM_REG_WRITE_CB(WriteTZPCR0SIZE) {
    bport1_ab_data.TZPCR0SIZE.value = data & 0x3ff;
    ppmWriteNet(handles.TZPCR0SIZE, bport1_ab_data.TZPCR0SIZE.value);
}

PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

