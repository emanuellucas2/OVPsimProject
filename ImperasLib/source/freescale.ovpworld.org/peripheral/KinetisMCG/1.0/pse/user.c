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
//                          Thu Sep 19 18:45:10 2013
//
////////////////////////////////////////////////////////////////////////////////

#include "pse.igen.h"
//////////////////////////////// Callback stubs ////////////////////////////////

#define PREFIX "KinetisMCG"

//
// Get the current value for the MCG Status register
//
static Uns8 getMCG_s() {

    // Get values to return from control registers
    Uns32 clks = bport1_ab_data.C1.bits.CLKS;
    Uns32 ircs = bport1_ab_data.C2.bits.IRCS;
    Uns32 plls = bport1_ab_data.C6.bits.PLLS;

    // Return appropriate values for current configuration
    // pll always indicates locked, osc always indicates initialized
    bport1_ab_data.S.bits.LOLS0    = 0;
    bport1_ab_data.S.bits.LOCK0    = 1;
    bport1_ab_data.S.bits.PLLST   = plls;
    bport1_ab_data.S.bits.IREFST  = clks;
    bport1_ab_data.S.bits.CLKST   = (clks==0 && plls) ? 3 : clks;
    bport1_ab_data.S.bits.OSCINIT0 = 1;
    bport1_ab_data.S.bits.IRCST   = ircs;

    return bport1_ab_data.S.value;

}

PPM_REG_READ_CB(readS) {
    return getMCG_s();
}

PPM_REG_VIEW_CB(viewS) {
    *(Uns8 *)data = getMCG_s();
}

PPM_CONSTRUCTOR_CB(constructor) {
    // YOUR CODE HERE (pre constructor)
    periphConstructor();
    // YOUR CODE HERE (post constructor)
}



// Save / restore callbacks

PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}

