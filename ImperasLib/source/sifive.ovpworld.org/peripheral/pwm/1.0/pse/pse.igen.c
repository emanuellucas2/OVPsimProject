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
//                             Version 20211118.0
//
////////////////////////////////////////////////////////////////////////////////


#include "pse.igen.h"
/////////////////////////////// Port Declarations //////////////////////////////

bport1_REG_dataT bport1_REG_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "pwm", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);
    if (!handles.bport1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bport1'");
    }

    ppmInstallNByteCallbacks(defaultMemRead, defaultMemWrite, 0, handles.bport1, 0x0, 0x1000, True, True, False, BHM_ENDIAN_LITTLE);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle REGpwmcfg_reg = ppmCreateRegister(
            "REG_pwmcfg",
            "Description\nPWM Configuration Register\nPWM Counter scale\nPWM Sticky - disallow clearing pwmcmpXip bits\nPWM Zero - counter resets to zero after match\nPWM Deglitch - latch pwmcmpXip within same cycle\nPWM enable always - run continuously\nPWM enable one shot - run one cycle\nPWM0 Compare Center\nPWM1 Compare Center\nPWM2 Compare Center\nPWM3 Compare Center\nPWM0/PWM1 Compare Gang\nPWM1/PWM2 Compare Gang\nPWM2/PWM3 Compare Gang\nPWM3/PWM0 Compare Gang\nPWM0 Interrupt Pending\nPWM1 Interrupt Pending\nPWM2 Interrupt Pending\nPWM3 Interrupt Pending\n",
            handles.bport1,
            0x0,
            4,
            read_32,
            wrCfg,
            view32,
            &(bport1_REG_data.pwmcfg.value),
            True
        );

        ppmCreateRegisterField(REGpwmcfg_reg, "pwmscale", 0, 0, 4, 1, 1);
        ppmCreateRegisterField(REGpwmcfg_reg, "pwmsticky", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(REGpwmcfg_reg, "pwmzerocmp", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(REGpwmcfg_reg, "pwmdeglitch", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(REGpwmcfg_reg, "pwmenalways", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(REGpwmcfg_reg, "pwmenoneshot", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(REGpwmcfg_reg, "pwmcmp0center", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(REGpwmcfg_reg, "pwmcmp1center", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(REGpwmcfg_reg, "pwmcmp2center", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(REGpwmcfg_reg, "pwmcmp3center", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(REGpwmcfg_reg, "pwmcmp0gang", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(REGpwmcfg_reg, "pwmcmp1gang", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(REGpwmcfg_reg, "pwmcmp2gang", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(REGpwmcfg_reg, "pwmcmp3gang", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(REGpwmcfg_reg, "pwmcmp0ip", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(REGpwmcfg_reg, "pwmcmp1ip", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(REGpwmcfg_reg, "pwmcmp2ip", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(REGpwmcfg_reg, "pwmcmp3ip", 0, 31, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "REG_pwmcount",
            0,
            handles.bport1,
            0x8,
            4,
            rdCnt,
            wrCnt,
            view32,
            &(bport1_REG_data.pwmcount.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "REG_pwms",
            0,
            handles.bport1,
            0x10,
            4,
            rdPwms,
            wrPwms,
            view32,
            &(bport1_REG_data.pwms.value),
            True
        );
    }
    {
        registerHandle REGpwmcmp0_reg = ppmCreateRegister(
            "REG_pwmcmp0",
            "Description\nPWM Compare Register\nPWM 0 Compare Value\n",
            handles.bport1,
            0x20,
            4,
            read_32,
            wrCmp,
            view32,
            &(bport1_REG_data.pwmcmp0.value),
            True
        );

        ppmCreateRegisterField(REGpwmcmp0_reg, "cmp", 0, 0, 16, 1, 1);
    }
    {
        registerHandle REGpwmcmp1_reg = ppmCreateRegister(
            "REG_pwmcmp1",
            "Description\nPWM Compare Register\nPWM 1 Compare Value\n",
            handles.bport1,
            0x24,
            4,
            read_32,
            wrCmp,
            view32,
            &(bport1_REG_data.pwmcmp1.value),
            True
        );

        ppmCreateRegisterField(REGpwmcmp1_reg, "cmp", 0, 0, 16, 1, 1);
    }
    {
        registerHandle REGpwmcmp2_reg = ppmCreateRegister(
            "REG_pwmcmp2",
            "Description\nPWM Compare Register\nPWM 2 Compare Value\n",
            handles.bport1,
            0x28,
            4,
            read_32,
            wrCmp,
            view32,
            &(bport1_REG_data.pwmcmp2.value),
            True
        );

        ppmCreateRegisterField(REGpwmcmp2_reg, "cmp", 0, 0, 16, 1, 1);
    }
    {
        registerHandle REGpwmcmp3_reg = ppmCreateRegister(
            "REG_pwmcmp3",
            "Description\nPWM Compare Register\nPWM 3 Compare Value\n",
            handles.bport1,
            0x2c,
            4,
            read_32,
            wrCmp,
            view32,
            &(bport1_REG_data.pwmcmp3.value),
            True
        );

        ppmCreateRegisterField(REGpwmcmp3_reg, "cmp", 0, 0, 16, 1, 1);
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_REG_data.pwmcmp3.value = (Uns32)(bport1_REG_data.pwmcmp3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.pwmcmp2.value = (Uns32)(bport1_REG_data.pwmcmp2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.pwmcmp1.value = (Uns32)(bport1_REG_data.pwmcmp1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.pwmcmp0.value = (Uns32)(bport1_REG_data.pwmcmp0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.pwms.value = (Uns32)(bport1_REG_data.pwms.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.pwmcount.value = (Uns32)(bport1_REG_data.pwmcount.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_REG_data.pwmcfg.value = (Uns32)(bport1_REG_data.pwmcfg.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "SiFive coreip-s51-arty PWM Registers (pwm)");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model implements only the registers and contains no behaviour.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "SiFive Freedom E SDK coreip-s51-arty Board Support Package details.");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    reset_resetNet(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    destructor();
    return 0;
}

