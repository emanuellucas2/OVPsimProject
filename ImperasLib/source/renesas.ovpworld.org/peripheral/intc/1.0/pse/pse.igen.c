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

INTCP0_reg0_dataT INTCP0_reg0_data;

INTCP0_reg1_dataT INTCP0_reg1_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "intc", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

static PPM_VIEW_CB(view16) {  *(Uns16*)data = *(Uns16*)user; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.INTCP0 = ppmCreateSlaveBusPort("INTCP0", 252);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "reg0_IMR0",
            0,
            handles.INTCP0,
            0x0,
            2,
            readIMR,
            writeIMR,
            view16,
            &(INTCP0_reg0_data.IMR0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_IMR1",
            0,
            handles.INTCP0,
            0x2,
            2,
            readIMR,
            writeIMR,
            view16,
            &(INTCP0_reg0_data.IMR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_IMR2",
            0,
            handles.INTCP0,
            0x4,
            2,
            readIMR,
            writeIMR,
            view16,
            &(INTCP0_reg0_data.IMR2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_IMR3",
            0,
            handles.INTCP0,
            0x6,
            2,
            readIMR,
            writeIMR,
            view16,
            &(INTCP0_reg0_data.IMR3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_IMR4",
            0,
            handles.INTCP0,
            0x8,
            2,
            readIMR,
            writeIMR,
            view16,
            &(INTCP0_reg0_data.IMR4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_IMR5",
            0,
            handles.INTCP0,
            0xa,
            2,
            readIMR,
            writeIMR,
            view16,
            &(INTCP0_reg0_data.IMR5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_IMR6",
            0,
            handles.INTCP0,
            0xc,
            2,
            readIMR,
            writeIMR,
            view16,
            &(INTCP0_reg0_data.IMR6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "reg0_IMR7",
            0,
            handles.INTCP0,
            0xe,
            2,
            readIMR,
            writeIMR,
            view16,
            &(INTCP0_reg0_data.IMR7.value),
            True
        );
    }
    {
        registerHandle reg1IC000_reg = ppmCreateRegister(
            "reg1_IC000",
            0,
            handles.INTCP0,
            0x10,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC000.value),
            True
        );

        ppmCreateRegisterField(reg1IC000_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC000_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC000_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC001_reg = ppmCreateRegister(
            "reg1_IC001",
            0,
            handles.INTCP0,
            0x12,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC001.value),
            True
        );

        ppmCreateRegisterField(reg1IC001_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC001_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC001_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC002_reg = ppmCreateRegister(
            "reg1_IC002",
            0,
            handles.INTCP0,
            0x14,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC002.value),
            True
        );

        ppmCreateRegisterField(reg1IC002_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC002_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC002_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC003_reg = ppmCreateRegister(
            "reg1_IC003",
            0,
            handles.INTCP0,
            0x16,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC003.value),
            True
        );

        ppmCreateRegisterField(reg1IC003_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC003_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC003_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC004_reg = ppmCreateRegister(
            "reg1_IC004",
            0,
            handles.INTCP0,
            0x18,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC004.value),
            True
        );

        ppmCreateRegisterField(reg1IC004_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC004_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC004_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC005_reg = ppmCreateRegister(
            "reg1_IC005",
            0,
            handles.INTCP0,
            0x1a,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC005.value),
            True
        );

        ppmCreateRegisterField(reg1IC005_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC005_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC005_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC006_reg = ppmCreateRegister(
            "reg1_IC006",
            0,
            handles.INTCP0,
            0x1c,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC006.value),
            True
        );

        ppmCreateRegisterField(reg1IC006_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC006_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC006_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC007_reg = ppmCreateRegister(
            "reg1_IC007",
            0,
            handles.INTCP0,
            0x1e,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC007.value),
            True
        );

        ppmCreateRegisterField(reg1IC007_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC007_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC007_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC008_reg = ppmCreateRegister(
            "reg1_IC008",
            0,
            handles.INTCP0,
            0x20,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC008.value),
            True
        );

        ppmCreateRegisterField(reg1IC008_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC008_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC008_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC009_reg = ppmCreateRegister(
            "reg1_IC009",
            0,
            handles.INTCP0,
            0x22,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC009.value),
            True
        );

        ppmCreateRegisterField(reg1IC009_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC009_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC009_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC010_reg = ppmCreateRegister(
            "reg1_IC010",
            0,
            handles.INTCP0,
            0x24,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC010.value),
            True
        );

        ppmCreateRegisterField(reg1IC010_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC010_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC010_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC011_reg = ppmCreateRegister(
            "reg1_IC011",
            0,
            handles.INTCP0,
            0x26,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC011.value),
            True
        );

        ppmCreateRegisterField(reg1IC011_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC011_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC011_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC012_reg = ppmCreateRegister(
            "reg1_IC012",
            0,
            handles.INTCP0,
            0x28,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC012.value),
            True
        );

        ppmCreateRegisterField(reg1IC012_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC012_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC012_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC013_reg = ppmCreateRegister(
            "reg1_IC013",
            0,
            handles.INTCP0,
            0x2a,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC013.value),
            True
        );

        ppmCreateRegisterField(reg1IC013_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC013_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC013_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC014_reg = ppmCreateRegister(
            "reg1_IC014",
            0,
            handles.INTCP0,
            0x2c,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC014.value),
            True
        );

        ppmCreateRegisterField(reg1IC014_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC014_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC014_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC015_reg = ppmCreateRegister(
            "reg1_IC015",
            0,
            handles.INTCP0,
            0x2e,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC015.value),
            True
        );

        ppmCreateRegisterField(reg1IC015_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC015_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC015_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC016_reg = ppmCreateRegister(
            "reg1_IC016",
            0,
            handles.INTCP0,
            0x30,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC016.value),
            True
        );

        ppmCreateRegisterField(reg1IC016_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC016_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC016_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC017_reg = ppmCreateRegister(
            "reg1_IC017",
            0,
            handles.INTCP0,
            0x32,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC017.value),
            True
        );

        ppmCreateRegisterField(reg1IC017_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC017_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC017_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC018_reg = ppmCreateRegister(
            "reg1_IC018",
            0,
            handles.INTCP0,
            0x34,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC018.value),
            True
        );

        ppmCreateRegisterField(reg1IC018_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC018_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC018_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC019_reg = ppmCreateRegister(
            "reg1_IC019",
            0,
            handles.INTCP0,
            0x36,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC019.value),
            True
        );

        ppmCreateRegisterField(reg1IC019_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC019_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC019_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC020_reg = ppmCreateRegister(
            "reg1_IC020",
            0,
            handles.INTCP0,
            0x38,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC020.value),
            True
        );

        ppmCreateRegisterField(reg1IC020_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC020_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC020_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC021_reg = ppmCreateRegister(
            "reg1_IC021",
            0,
            handles.INTCP0,
            0x3a,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC021.value),
            True
        );

        ppmCreateRegisterField(reg1IC021_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC021_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC021_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC022_reg = ppmCreateRegister(
            "reg1_IC022",
            0,
            handles.INTCP0,
            0x3c,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC022.value),
            True
        );

        ppmCreateRegisterField(reg1IC022_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC022_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC022_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC023_reg = ppmCreateRegister(
            "reg1_IC023",
            0,
            handles.INTCP0,
            0x3e,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC023.value),
            True
        );

        ppmCreateRegisterField(reg1IC023_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC023_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC023_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC024_reg = ppmCreateRegister(
            "reg1_IC024",
            0,
            handles.INTCP0,
            0x40,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC024.value),
            True
        );

        ppmCreateRegisterField(reg1IC024_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC024_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC024_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC025_reg = ppmCreateRegister(
            "reg1_IC025",
            0,
            handles.INTCP0,
            0x42,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC025.value),
            True
        );

        ppmCreateRegisterField(reg1IC025_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC025_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC025_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC026_reg = ppmCreateRegister(
            "reg1_IC026",
            0,
            handles.INTCP0,
            0x44,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC026.value),
            True
        );

        ppmCreateRegisterField(reg1IC026_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC026_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC026_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC027_reg = ppmCreateRegister(
            "reg1_IC027",
            0,
            handles.INTCP0,
            0x46,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC027.value),
            True
        );

        ppmCreateRegisterField(reg1IC027_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC027_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC027_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC028_reg = ppmCreateRegister(
            "reg1_IC028",
            0,
            handles.INTCP0,
            0x48,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC028.value),
            True
        );

        ppmCreateRegisterField(reg1IC028_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC028_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC028_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC029_reg = ppmCreateRegister(
            "reg1_IC029",
            0,
            handles.INTCP0,
            0x4a,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC029.value),
            True
        );

        ppmCreateRegisterField(reg1IC029_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC029_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC029_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC030_reg = ppmCreateRegister(
            "reg1_IC030",
            0,
            handles.INTCP0,
            0x4c,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC030.value),
            True
        );

        ppmCreateRegisterField(reg1IC030_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC030_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC030_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC031_reg = ppmCreateRegister(
            "reg1_IC031",
            0,
            handles.INTCP0,
            0x4e,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC031.value),
            True
        );

        ppmCreateRegisterField(reg1IC031_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC031_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC031_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC032_reg = ppmCreateRegister(
            "reg1_IC032",
            0,
            handles.INTCP0,
            0x50,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC032.value),
            True
        );

        ppmCreateRegisterField(reg1IC032_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC032_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC032_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC033_reg = ppmCreateRegister(
            "reg1_IC033",
            0,
            handles.INTCP0,
            0x52,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC033.value),
            True
        );

        ppmCreateRegisterField(reg1IC033_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC033_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC033_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC034_reg = ppmCreateRegister(
            "reg1_IC034",
            0,
            handles.INTCP0,
            0x54,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC034.value),
            True
        );

        ppmCreateRegisterField(reg1IC034_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC034_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC034_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC035_reg = ppmCreateRegister(
            "reg1_IC035",
            0,
            handles.INTCP0,
            0x56,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC035.value),
            True
        );

        ppmCreateRegisterField(reg1IC035_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC035_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC035_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC036_reg = ppmCreateRegister(
            "reg1_IC036",
            0,
            handles.INTCP0,
            0x58,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC036.value),
            True
        );

        ppmCreateRegisterField(reg1IC036_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC036_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC036_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC037_reg = ppmCreateRegister(
            "reg1_IC037",
            0,
            handles.INTCP0,
            0x5a,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC037.value),
            True
        );

        ppmCreateRegisterField(reg1IC037_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC037_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC037_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC038_reg = ppmCreateRegister(
            "reg1_IC038",
            0,
            handles.INTCP0,
            0x5c,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC038.value),
            True
        );

        ppmCreateRegisterField(reg1IC038_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC038_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC038_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC039_reg = ppmCreateRegister(
            "reg1_IC039",
            0,
            handles.INTCP0,
            0x5e,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC039.value),
            True
        );

        ppmCreateRegisterField(reg1IC039_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC039_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC039_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC040_reg = ppmCreateRegister(
            "reg1_IC040",
            0,
            handles.INTCP0,
            0x60,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC040.value),
            True
        );

        ppmCreateRegisterField(reg1IC040_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC040_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC040_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC041_reg = ppmCreateRegister(
            "reg1_IC041",
            0,
            handles.INTCP0,
            0x62,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC041.value),
            True
        );

        ppmCreateRegisterField(reg1IC041_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC041_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC041_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC042_reg = ppmCreateRegister(
            "reg1_IC042",
            0,
            handles.INTCP0,
            0x64,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC042.value),
            True
        );

        ppmCreateRegisterField(reg1IC042_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC042_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC042_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC043_reg = ppmCreateRegister(
            "reg1_IC043",
            0,
            handles.INTCP0,
            0x66,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC043.value),
            True
        );

        ppmCreateRegisterField(reg1IC043_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC043_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC043_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC044_reg = ppmCreateRegister(
            "reg1_IC044",
            0,
            handles.INTCP0,
            0x68,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC044.value),
            True
        );

        ppmCreateRegisterField(reg1IC044_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC044_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC044_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC045_reg = ppmCreateRegister(
            "reg1_IC045",
            0,
            handles.INTCP0,
            0x6a,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC045.value),
            True
        );

        ppmCreateRegisterField(reg1IC045_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC045_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC045_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC046_reg = ppmCreateRegister(
            "reg1_IC046",
            0,
            handles.INTCP0,
            0x6c,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC046.value),
            True
        );

        ppmCreateRegisterField(reg1IC046_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC046_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC046_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC047_reg = ppmCreateRegister(
            "reg1_IC047",
            0,
            handles.INTCP0,
            0x6e,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC047.value),
            True
        );

        ppmCreateRegisterField(reg1IC047_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC047_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC047_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC048_reg = ppmCreateRegister(
            "reg1_IC048",
            0,
            handles.INTCP0,
            0x70,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC048.value),
            True
        );

        ppmCreateRegisterField(reg1IC048_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC048_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC048_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC049_reg = ppmCreateRegister(
            "reg1_IC049",
            0,
            handles.INTCP0,
            0x72,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC049.value),
            True
        );

        ppmCreateRegisterField(reg1IC049_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC049_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC049_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC050_reg = ppmCreateRegister(
            "reg1_IC050",
            0,
            handles.INTCP0,
            0x74,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC050.value),
            True
        );

        ppmCreateRegisterField(reg1IC050_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC050_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC050_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC051_reg = ppmCreateRegister(
            "reg1_IC051",
            0,
            handles.INTCP0,
            0x76,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC051.value),
            True
        );

        ppmCreateRegisterField(reg1IC051_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC051_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC051_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC052_reg = ppmCreateRegister(
            "reg1_IC052",
            0,
            handles.INTCP0,
            0x78,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC052.value),
            True
        );

        ppmCreateRegisterField(reg1IC052_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC052_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC052_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC053_reg = ppmCreateRegister(
            "reg1_IC053",
            0,
            handles.INTCP0,
            0x7a,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC053.value),
            True
        );

        ppmCreateRegisterField(reg1IC053_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC053_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC053_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC054_reg = ppmCreateRegister(
            "reg1_IC054",
            0,
            handles.INTCP0,
            0x7c,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC054.value),
            True
        );

        ppmCreateRegisterField(reg1IC054_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC054_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC054_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC055_reg = ppmCreateRegister(
            "reg1_IC055",
            0,
            handles.INTCP0,
            0x7e,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC055.value),
            True
        );

        ppmCreateRegisterField(reg1IC055_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC055_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC055_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC056_reg = ppmCreateRegister(
            "reg1_IC056",
            0,
            handles.INTCP0,
            0x80,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC056.value),
            True
        );

        ppmCreateRegisterField(reg1IC056_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC056_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC056_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC057_reg = ppmCreateRegister(
            "reg1_IC057",
            0,
            handles.INTCP0,
            0x82,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC057.value),
            True
        );

        ppmCreateRegisterField(reg1IC057_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC057_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC057_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC058_reg = ppmCreateRegister(
            "reg1_IC058",
            0,
            handles.INTCP0,
            0x84,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC058.value),
            True
        );

        ppmCreateRegisterField(reg1IC058_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC058_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC058_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC059_reg = ppmCreateRegister(
            "reg1_IC059",
            0,
            handles.INTCP0,
            0x86,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC059.value),
            True
        );

        ppmCreateRegisterField(reg1IC059_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC059_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC059_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC060_reg = ppmCreateRegister(
            "reg1_IC060",
            0,
            handles.INTCP0,
            0x88,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC060.value),
            True
        );

        ppmCreateRegisterField(reg1IC060_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC060_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC060_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC061_reg = ppmCreateRegister(
            "reg1_IC061",
            0,
            handles.INTCP0,
            0x8a,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC061.value),
            True
        );

        ppmCreateRegisterField(reg1IC061_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC061_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC061_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC062_reg = ppmCreateRegister(
            "reg1_IC062",
            0,
            handles.INTCP0,
            0x8c,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC062.value),
            True
        );

        ppmCreateRegisterField(reg1IC062_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC062_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC062_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC063_reg = ppmCreateRegister(
            "reg1_IC063",
            0,
            handles.INTCP0,
            0x8e,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC063.value),
            True
        );

        ppmCreateRegisterField(reg1IC063_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC063_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC063_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC064_reg = ppmCreateRegister(
            "reg1_IC064",
            0,
            handles.INTCP0,
            0x90,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC064.value),
            True
        );

        ppmCreateRegisterField(reg1IC064_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC064_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC064_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC065_reg = ppmCreateRegister(
            "reg1_IC065",
            0,
            handles.INTCP0,
            0x92,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC065.value),
            True
        );

        ppmCreateRegisterField(reg1IC065_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC065_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC065_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC066_reg = ppmCreateRegister(
            "reg1_IC066",
            0,
            handles.INTCP0,
            0x94,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC066.value),
            True
        );

        ppmCreateRegisterField(reg1IC066_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC066_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC066_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC067_reg = ppmCreateRegister(
            "reg1_IC067",
            0,
            handles.INTCP0,
            0x96,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC067.value),
            True
        );

        ppmCreateRegisterField(reg1IC067_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC067_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC067_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC068_reg = ppmCreateRegister(
            "reg1_IC068",
            0,
            handles.INTCP0,
            0x98,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC068.value),
            True
        );

        ppmCreateRegisterField(reg1IC068_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC068_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC068_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC069_reg = ppmCreateRegister(
            "reg1_IC069",
            0,
            handles.INTCP0,
            0x9a,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC069.value),
            True
        );

        ppmCreateRegisterField(reg1IC069_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC069_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC069_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC070_reg = ppmCreateRegister(
            "reg1_IC070",
            0,
            handles.INTCP0,
            0x9c,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC070.value),
            True
        );

        ppmCreateRegisterField(reg1IC070_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC070_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC070_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC071_reg = ppmCreateRegister(
            "reg1_IC071",
            0,
            handles.INTCP0,
            0x9e,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC071.value),
            True
        );

        ppmCreateRegisterField(reg1IC071_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC071_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC071_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC072_reg = ppmCreateRegister(
            "reg1_IC072",
            0,
            handles.INTCP0,
            0xa0,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC072.value),
            True
        );

        ppmCreateRegisterField(reg1IC072_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC072_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC072_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC073_reg = ppmCreateRegister(
            "reg1_IC073",
            0,
            handles.INTCP0,
            0xa2,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC073.value),
            True
        );

        ppmCreateRegisterField(reg1IC073_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC073_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC073_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC074_reg = ppmCreateRegister(
            "reg1_IC074",
            0,
            handles.INTCP0,
            0xa4,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC074.value),
            True
        );

        ppmCreateRegisterField(reg1IC074_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC074_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC074_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC075_reg = ppmCreateRegister(
            "reg1_IC075",
            0,
            handles.INTCP0,
            0xa6,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC075.value),
            True
        );

        ppmCreateRegisterField(reg1IC075_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC075_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC075_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC076_reg = ppmCreateRegister(
            "reg1_IC076",
            0,
            handles.INTCP0,
            0xa8,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC076.value),
            True
        );

        ppmCreateRegisterField(reg1IC076_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC076_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC076_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC077_reg = ppmCreateRegister(
            "reg1_IC077",
            0,
            handles.INTCP0,
            0xaa,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC077.value),
            True
        );

        ppmCreateRegisterField(reg1IC077_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC077_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC077_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC078_reg = ppmCreateRegister(
            "reg1_IC078",
            0,
            handles.INTCP0,
            0xac,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC078.value),
            True
        );

        ppmCreateRegisterField(reg1IC078_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC078_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC078_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC079_reg = ppmCreateRegister(
            "reg1_IC079",
            0,
            handles.INTCP0,
            0xae,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC079.value),
            True
        );

        ppmCreateRegisterField(reg1IC079_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC079_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC079_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC080_reg = ppmCreateRegister(
            "reg1_IC080",
            0,
            handles.INTCP0,
            0xb0,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC080.value),
            True
        );

        ppmCreateRegisterField(reg1IC080_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC080_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC080_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC081_reg = ppmCreateRegister(
            "reg1_IC081",
            0,
            handles.INTCP0,
            0xb2,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC081.value),
            True
        );

        ppmCreateRegisterField(reg1IC081_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC081_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC081_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC082_reg = ppmCreateRegister(
            "reg1_IC082",
            0,
            handles.INTCP0,
            0xb4,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC082.value),
            True
        );

        ppmCreateRegisterField(reg1IC082_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC082_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC082_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC083_reg = ppmCreateRegister(
            "reg1_IC083",
            0,
            handles.INTCP0,
            0xb6,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC083.value),
            True
        );

        ppmCreateRegisterField(reg1IC083_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC083_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC083_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC084_reg = ppmCreateRegister(
            "reg1_IC084",
            0,
            handles.INTCP0,
            0xb8,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC084.value),
            True
        );

        ppmCreateRegisterField(reg1IC084_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC084_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC084_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC085_reg = ppmCreateRegister(
            "reg1_IC085",
            0,
            handles.INTCP0,
            0xba,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC085.value),
            True
        );

        ppmCreateRegisterField(reg1IC085_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC085_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC085_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC086_reg = ppmCreateRegister(
            "reg1_IC086",
            0,
            handles.INTCP0,
            0xbc,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC086.value),
            True
        );

        ppmCreateRegisterField(reg1IC086_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC086_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC086_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC087_reg = ppmCreateRegister(
            "reg1_IC087",
            0,
            handles.INTCP0,
            0xbe,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC087.value),
            True
        );

        ppmCreateRegisterField(reg1IC087_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC087_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC087_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC088_reg = ppmCreateRegister(
            "reg1_IC088",
            0,
            handles.INTCP0,
            0xc0,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC088.value),
            True
        );

        ppmCreateRegisterField(reg1IC088_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC088_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC088_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC089_reg = ppmCreateRegister(
            "reg1_IC089",
            0,
            handles.INTCP0,
            0xc2,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC089.value),
            True
        );

        ppmCreateRegisterField(reg1IC089_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC089_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC089_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC090_reg = ppmCreateRegister(
            "reg1_IC090",
            0,
            handles.INTCP0,
            0xc4,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC090.value),
            True
        );

        ppmCreateRegisterField(reg1IC090_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC090_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC090_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC091_reg = ppmCreateRegister(
            "reg1_IC091",
            0,
            handles.INTCP0,
            0xc6,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC091.value),
            True
        );

        ppmCreateRegisterField(reg1IC091_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC091_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC091_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC092_reg = ppmCreateRegister(
            "reg1_IC092",
            0,
            handles.INTCP0,
            0xc8,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC092.value),
            True
        );

        ppmCreateRegisterField(reg1IC092_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC092_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC092_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC093_reg = ppmCreateRegister(
            "reg1_IC093",
            0,
            handles.INTCP0,
            0xca,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC093.value),
            True
        );

        ppmCreateRegisterField(reg1IC093_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC093_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC093_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC094_reg = ppmCreateRegister(
            "reg1_IC094",
            0,
            handles.INTCP0,
            0xcc,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC094.value),
            True
        );

        ppmCreateRegisterField(reg1IC094_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC094_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC094_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC095_reg = ppmCreateRegister(
            "reg1_IC095",
            0,
            handles.INTCP0,
            0xce,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC095.value),
            True
        );

        ppmCreateRegisterField(reg1IC095_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC095_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC095_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC096_reg = ppmCreateRegister(
            "reg1_IC096",
            0,
            handles.INTCP0,
            0xd0,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC096.value),
            True
        );

        ppmCreateRegisterField(reg1IC096_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC096_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC096_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC097_reg = ppmCreateRegister(
            "reg1_IC097",
            0,
            handles.INTCP0,
            0xd2,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC097.value),
            True
        );

        ppmCreateRegisterField(reg1IC097_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC097_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC097_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC098_reg = ppmCreateRegister(
            "reg1_IC098",
            0,
            handles.INTCP0,
            0xd4,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC098.value),
            True
        );

        ppmCreateRegisterField(reg1IC098_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC098_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC098_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC099_reg = ppmCreateRegister(
            "reg1_IC099",
            0,
            handles.INTCP0,
            0xd6,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC099.value),
            True
        );

        ppmCreateRegisterField(reg1IC099_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC099_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC099_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC100_reg = ppmCreateRegister(
            "reg1_IC100",
            0,
            handles.INTCP0,
            0xd8,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC100.value),
            True
        );

        ppmCreateRegisterField(reg1IC100_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC100_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC100_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC101_reg = ppmCreateRegister(
            "reg1_IC101",
            0,
            handles.INTCP0,
            0xda,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC101.value),
            True
        );

        ppmCreateRegisterField(reg1IC101_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC101_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC101_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC102_reg = ppmCreateRegister(
            "reg1_IC102",
            0,
            handles.INTCP0,
            0xdc,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC102.value),
            True
        );

        ppmCreateRegisterField(reg1IC102_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC102_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC102_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC103_reg = ppmCreateRegister(
            "reg1_IC103",
            0,
            handles.INTCP0,
            0xde,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC103.value),
            True
        );

        ppmCreateRegisterField(reg1IC103_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC103_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC103_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC104_reg = ppmCreateRegister(
            "reg1_IC104",
            0,
            handles.INTCP0,
            0xe0,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC104.value),
            True
        );

        ppmCreateRegisterField(reg1IC104_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC104_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC104_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC105_reg = ppmCreateRegister(
            "reg1_IC105",
            0,
            handles.INTCP0,
            0xe2,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC105.value),
            True
        );

        ppmCreateRegisterField(reg1IC105_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC105_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC105_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC106_reg = ppmCreateRegister(
            "reg1_IC106",
            0,
            handles.INTCP0,
            0xe4,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC106.value),
            True
        );

        ppmCreateRegisterField(reg1IC106_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC106_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC106_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC107_reg = ppmCreateRegister(
            "reg1_IC107",
            0,
            handles.INTCP0,
            0xe6,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC107.value),
            True
        );

        ppmCreateRegisterField(reg1IC107_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC107_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC107_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC108_reg = ppmCreateRegister(
            "reg1_IC108",
            0,
            handles.INTCP0,
            0xe8,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC108.value),
            True
        );

        ppmCreateRegisterField(reg1IC108_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC108_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC108_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC109_reg = ppmCreateRegister(
            "reg1_IC109",
            0,
            handles.INTCP0,
            0xea,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC109.value),
            True
        );

        ppmCreateRegisterField(reg1IC109_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC109_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC109_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC110_reg = ppmCreateRegister(
            "reg1_IC110",
            0,
            handles.INTCP0,
            0xec,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC110.value),
            True
        );

        ppmCreateRegisterField(reg1IC110_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC110_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC110_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC111_reg = ppmCreateRegister(
            "reg1_IC111",
            0,
            handles.INTCP0,
            0xee,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC111.value),
            True
        );

        ppmCreateRegisterField(reg1IC111_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC111_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC111_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC112_reg = ppmCreateRegister(
            "reg1_IC112",
            0,
            handles.INTCP0,
            0xf0,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC112.value),
            True
        );

        ppmCreateRegisterField(reg1IC112_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC112_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC112_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC113_reg = ppmCreateRegister(
            "reg1_IC113",
            0,
            handles.INTCP0,
            0xf2,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC113.value),
            True
        );

        ppmCreateRegisterField(reg1IC113_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC113_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC113_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC114_reg = ppmCreateRegister(
            "reg1_IC114",
            0,
            handles.INTCP0,
            0xf4,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC114.value),
            True
        );

        ppmCreateRegisterField(reg1IC114_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC114_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC114_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC115_reg = ppmCreateRegister(
            "reg1_IC115",
            0,
            handles.INTCP0,
            0xf6,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC115.value),
            True
        );

        ppmCreateRegisterField(reg1IC115_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC115_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC115_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1IC116_reg = ppmCreateRegister(
            "reg1_IC116",
            0,
            handles.INTCP0,
            0xf8,
            1,
            readIC,
            writeIC,
            view8,
            &(INTCP0_reg1_data.IC116.value),
            True
        );

        ppmCreateRegisterField(reg1IC116_reg, "IF", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(reg1IC116_reg, "MK", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(reg1IC116_reg, "PR", 0, 0, 3, 1, 1);
    }
    {
        registerHandle reg1ISPR_reg = ppmCreateRegister(
            "reg1_ISPR",
            0,
            handles.INTCP0,
            0xfa,
            1,
            read_8,
            0,
            view8,
            &(INTCP0_reg1_data.ISPR.value),
            True
        );

        ppmCreateRegisterField(reg1ISPR_reg, "ISPR0", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(reg1ISPR_reg, "ISPR1", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(reg1ISPR_reg, "ISPR2", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(reg1ISPR_reg, "ISPR3", 0, 3, 1, 1, 0);
        ppmCreateRegisterField(reg1ISPR_reg, "ISPR4", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(reg1ISPR_reg, "ISPR5", 0, 5, 1, 1, 0);
        ppmCreateRegisterField(reg1ISPR_reg, "ISPR6", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(reg1ISPR_reg, "ISPR7", 0, 7, 1, 1, 0);
    }

}

PPM_NET_CB(reset_IRESET) {
    if(value != 0 ) {
        INTCP0_reg1_data.IC116.value = (Uns8)(INTCP0_reg1_data.IC116.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC115.value = (Uns8)(INTCP0_reg1_data.IC115.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC114.value = (Uns8)(INTCP0_reg1_data.IC114.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC113.value = (Uns8)(INTCP0_reg1_data.IC113.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC112.value = (Uns8)(INTCP0_reg1_data.IC112.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC111.value = (Uns8)(INTCP0_reg1_data.IC111.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC110.value = (Uns8)(INTCP0_reg1_data.IC110.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC109.value = (Uns8)(INTCP0_reg1_data.IC109.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC108.value = (Uns8)(INTCP0_reg1_data.IC108.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC107.value = (Uns8)(INTCP0_reg1_data.IC107.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC106.value = (Uns8)(INTCP0_reg1_data.IC106.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC105.value = (Uns8)(INTCP0_reg1_data.IC105.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC104.value = (Uns8)(INTCP0_reg1_data.IC104.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC103.value = (Uns8)(INTCP0_reg1_data.IC103.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC102.value = (Uns8)(INTCP0_reg1_data.IC102.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC101.value = (Uns8)(INTCP0_reg1_data.IC101.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC100.value = (Uns8)(INTCP0_reg1_data.IC100.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC099.value = (Uns8)(INTCP0_reg1_data.IC099.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC098.value = (Uns8)(INTCP0_reg1_data.IC098.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC097.value = (Uns8)(INTCP0_reg1_data.IC097.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC096.value = (Uns8)(INTCP0_reg1_data.IC096.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC095.value = (Uns8)(INTCP0_reg1_data.IC095.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC094.value = (Uns8)(INTCP0_reg1_data.IC094.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC093.value = (Uns8)(INTCP0_reg1_data.IC093.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC092.value = (Uns8)(INTCP0_reg1_data.IC092.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC091.value = (Uns8)(INTCP0_reg1_data.IC091.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC090.value = (Uns8)(INTCP0_reg1_data.IC090.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC089.value = (Uns8)(INTCP0_reg1_data.IC089.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC088.value = (Uns8)(INTCP0_reg1_data.IC088.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC087.value = (Uns8)(INTCP0_reg1_data.IC087.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC086.value = (Uns8)(INTCP0_reg1_data.IC086.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC085.value = (Uns8)(INTCP0_reg1_data.IC085.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC084.value = (Uns8)(INTCP0_reg1_data.IC084.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC083.value = (Uns8)(INTCP0_reg1_data.IC083.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC082.value = (Uns8)(INTCP0_reg1_data.IC082.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC081.value = (Uns8)(INTCP0_reg1_data.IC081.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC080.value = (Uns8)(INTCP0_reg1_data.IC080.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC079.value = (Uns8)(INTCP0_reg1_data.IC079.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC078.value = (Uns8)(INTCP0_reg1_data.IC078.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC077.value = (Uns8)(INTCP0_reg1_data.IC077.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC076.value = (Uns8)(INTCP0_reg1_data.IC076.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC075.value = (Uns8)(INTCP0_reg1_data.IC075.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC074.value = (Uns8)(INTCP0_reg1_data.IC074.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC073.value = (Uns8)(INTCP0_reg1_data.IC073.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC072.value = (Uns8)(INTCP0_reg1_data.IC072.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC071.value = (Uns8)(INTCP0_reg1_data.IC071.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC070.value = (Uns8)(INTCP0_reg1_data.IC070.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC069.value = (Uns8)(INTCP0_reg1_data.IC069.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC068.value = (Uns8)(INTCP0_reg1_data.IC068.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC067.value = (Uns8)(INTCP0_reg1_data.IC067.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC066.value = (Uns8)(INTCP0_reg1_data.IC066.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC065.value = (Uns8)(INTCP0_reg1_data.IC065.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC064.value = (Uns8)(INTCP0_reg1_data.IC064.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC063.value = (Uns8)(INTCP0_reg1_data.IC063.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC062.value = (Uns8)(INTCP0_reg1_data.IC062.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC061.value = (Uns8)(INTCP0_reg1_data.IC061.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC060.value = (Uns8)(INTCP0_reg1_data.IC060.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC059.value = (Uns8)(INTCP0_reg1_data.IC059.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC058.value = (Uns8)(INTCP0_reg1_data.IC058.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC057.value = (Uns8)(INTCP0_reg1_data.IC057.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC056.value = (Uns8)(INTCP0_reg1_data.IC056.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC055.value = (Uns8)(INTCP0_reg1_data.IC055.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC054.value = (Uns8)(INTCP0_reg1_data.IC054.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC053.value = (Uns8)(INTCP0_reg1_data.IC053.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC052.value = (Uns8)(INTCP0_reg1_data.IC052.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC051.value = (Uns8)(INTCP0_reg1_data.IC051.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC050.value = (Uns8)(INTCP0_reg1_data.IC050.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC049.value = (Uns8)(INTCP0_reg1_data.IC049.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC048.value = (Uns8)(INTCP0_reg1_data.IC048.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC047.value = (Uns8)(INTCP0_reg1_data.IC047.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC046.value = (Uns8)(INTCP0_reg1_data.IC046.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC045.value = (Uns8)(INTCP0_reg1_data.IC045.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC044.value = (Uns8)(INTCP0_reg1_data.IC044.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC043.value = (Uns8)(INTCP0_reg1_data.IC043.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC042.value = (Uns8)(INTCP0_reg1_data.IC042.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC041.value = (Uns8)(INTCP0_reg1_data.IC041.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC040.value = (Uns8)(INTCP0_reg1_data.IC040.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC039.value = (Uns8)(INTCP0_reg1_data.IC039.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC038.value = (Uns8)(INTCP0_reg1_data.IC038.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC037.value = (Uns8)(INTCP0_reg1_data.IC037.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC036.value = (Uns8)(INTCP0_reg1_data.IC036.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC035.value = (Uns8)(INTCP0_reg1_data.IC035.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC034.value = (Uns8)(INTCP0_reg1_data.IC034.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC033.value = (Uns8)(INTCP0_reg1_data.IC033.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC032.value = (Uns8)(INTCP0_reg1_data.IC032.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC031.value = (Uns8)(INTCP0_reg1_data.IC031.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC030.value = (Uns8)(INTCP0_reg1_data.IC030.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC029.value = (Uns8)(INTCP0_reg1_data.IC029.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC028.value = (Uns8)(INTCP0_reg1_data.IC028.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC027.value = (Uns8)(INTCP0_reg1_data.IC027.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC026.value = (Uns8)(INTCP0_reg1_data.IC026.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC025.value = (Uns8)(INTCP0_reg1_data.IC025.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC024.value = (Uns8)(INTCP0_reg1_data.IC024.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC023.value = (Uns8)(INTCP0_reg1_data.IC023.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC022.value = (Uns8)(INTCP0_reg1_data.IC022.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC021.value = (Uns8)(INTCP0_reg1_data.IC021.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC020.value = (Uns8)(INTCP0_reg1_data.IC020.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC019.value = (Uns8)(INTCP0_reg1_data.IC019.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC018.value = (Uns8)(INTCP0_reg1_data.IC018.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC017.value = (Uns8)(INTCP0_reg1_data.IC017.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC016.value = (Uns8)(INTCP0_reg1_data.IC016.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC015.value = (Uns8)(INTCP0_reg1_data.IC015.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC014.value = (Uns8)(INTCP0_reg1_data.IC014.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC013.value = (Uns8)(INTCP0_reg1_data.IC013.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC012.value = (Uns8)(INTCP0_reg1_data.IC012.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC011.value = (Uns8)(INTCP0_reg1_data.IC011.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC010.value = (Uns8)(INTCP0_reg1_data.IC010.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC009.value = (Uns8)(INTCP0_reg1_data.IC009.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC008.value = (Uns8)(INTCP0_reg1_data.IC008.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC007.value = (Uns8)(INTCP0_reg1_data.IC007.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC006.value = (Uns8)(INTCP0_reg1_data.IC006.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC005.value = (Uns8)(INTCP0_reg1_data.IC005.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC004.value = (Uns8)(INTCP0_reg1_data.IC004.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC003.value = (Uns8)(INTCP0_reg1_data.IC003.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC002.value = (Uns8)(INTCP0_reg1_data.IC002.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC001.value = (Uns8)(INTCP0_reg1_data.IC001.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg1_data.IC000.value = (Uns8)(INTCP0_reg1_data.IC000.value & ~(0xff)) | ((0xff) & (0x47));
        INTCP0_reg0_data.IMR7.value = (Uns16)(INTCP0_reg0_data.IMR7.value & ~(0xffff)) | ((0xffff) & (0x001f));
        INTCP0_reg0_data.IMR6.value = (Uns16)(INTCP0_reg0_data.IMR6.value & ~(0xffff)) | ((0xffff) & (0xffff));
        INTCP0_reg0_data.IMR5.value = (Uns16)(INTCP0_reg0_data.IMR5.value & ~(0xffff)) | ((0xffff) & (0xffff));
        INTCP0_reg0_data.IMR4.value = (Uns16)(INTCP0_reg0_data.IMR4.value & ~(0xffff)) | ((0xffff) & (0xffff));
        INTCP0_reg0_data.IMR3.value = (Uns16)(INTCP0_reg0_data.IMR3.value & ~(0xffff)) | ((0xffff) & (0xffff));
        INTCP0_reg0_data.IMR2.value = (Uns16)(INTCP0_reg0_data.IMR2.value & ~(0xffff)) | ((0xffff) & (0xffff));
        INTCP0_reg0_data.IMR1.value = (Uns16)(INTCP0_reg0_data.IMR1.value & ~(0xffff)) | ((0xffff) & (0xffff));
        INTCP0_reg0_data.IMR0.value = (Uns16)(INTCP0_reg0_data.IMR0.value & ~(0xffff)) | ((0xffff) & (0xffff));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc2_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc_12_node, "Renesas INTC Interrupt Controller");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "Register View Model Only");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "R01UH0128ED0700, Rev. 7.00, Oct 06, 2010");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    reset_IRESET(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

