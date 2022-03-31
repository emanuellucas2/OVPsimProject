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

bport1_ab_dataT bport1_ab_data;

handlesT handles;

/////////////////////////////// Diagnostic level ///////////////////////////////

// Test this variable to determine what diagnostics to output.
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "iMX6_MMDC", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

static PPM_WRITE_CB(write_32) { *(Uns32*)user = data; }

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 16384);
    if (!handles.bport1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bport1'");
    }

    ppmInstallReadCallback(regNoDefinitionRead, (void*)0 , handles.bport1 + 0x0, 0x4000);
    ppmInstallWriteCallback(regNoDefinitionWrite, (void*)0 , handles.bport1 + 0x0, 0x4000);
}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "ab_MMDC_MDCTL",
            "MMDC Core Control Register",
            handles.bport1,
            0x0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MDCTL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MDPDC",
            "MMDC Core Power Down Control Register",
            handles.bport1,
            0x4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MDPDC.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MDOTC",
            "MMDC Core ODT Timing Control Register",
            handles.bport1,
            0x8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MDOTC.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MDCFG0",
            "MMDC Core Timing Configuration Register 0",
            handles.bport1,
            0xc,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MDCFG0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MDCFG1",
            "MMDC Core Timing Configuration Register 1",
            handles.bport1,
            0x10,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MDCFG1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MDCFG2",
            "MMDC Core Timing Configuration Register 2",
            handles.bport1,
            0x14,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MDCFG2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MDMISC",
            "MMDC Core Miscellaneous Register",
            handles.bport1,
            0x18,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MDMISC.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MDSCR",
            "MMDC Core Special Command Register",
            handles.bport1,
            0x1c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MDSCR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MDREF",
            "MMDC Core Refresh Control Register",
            handles.bport1,
            0x20,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MDREF.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MDRWD",
            "MMDC Core Read/Write Command Delay Register",
            handles.bport1,
            0x2c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MDRWD.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MDOR",
            "MMDC Core Out of Reset Delays Register",
            handles.bport1,
            0x30,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MDOR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MDMRR",
            "MMDC Core MRR Data Register",
            handles.bport1,
            0x34,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MDMRR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MDCFG3LP",
            "MMDC Core Timing Configuration Register 3",
            handles.bport1,
            0x38,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MDCFG3LP.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MDMR4",
            "MMDC Core MR4 Derating Register",
            handles.bport1,
            0x3c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MDMR4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MDASP",
            "MMDC Core Address Space Partition Register",
            handles.bport1,
            0x40,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MDASP.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MAARCR",
            "MMDC Core AXI Reordering Control Register",
            handles.bport1,
            0x400,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MAARCR.value),
            True
        );
    }
    {
        registerHandle abMMDC_MAPSR_reg = ppmCreateRegister(
            "ab_MMDC_MAPSR",
            "Description\nMMDC Core Power Saving Control and Status Register\nDVFS/Self-Refresh acknowledge\nGeneral low-power acknowledge\nDVFS/Self-Refresh request\nGeneral LPMD request\nAutomatic Power saving timer.\nWrite Idle Status.\nRead Idle Status\nPower Saving Status\nAutomatic Power Saving Disable\n",
            handles.bport1,
            0x404,
            4,
            read_32,
            WriteMMDC_MAPSR,
            view32,
            &(bport1_ab_data.MMDC_MAPSR.value),
            True
        );

        ppmCreateRegisterField(abMMDC_MAPSR_reg, "DVACK", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abMMDC_MAPSR_reg, "LPACK", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abMMDC_MAPSR_reg, "DVFS", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abMMDC_MAPSR_reg, "LPMD", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abMMDC_MAPSR_reg, "PST", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abMMDC_MAPSR_reg, "WIS", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abMMDC_MAPSR_reg, "RIS", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abMMDC_MAPSR_reg, "PSS", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abMMDC_MAPSR_reg, "PSD", 0, 0, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MAEXIDR0",
            "MMDC Core Exclusive ID Monitor Register0",
            handles.bport1,
            0x408,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MAEXIDR0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MAEXIDR1",
            "MMDC Core Exclusive ID Monitor Register1",
            handles.bport1,
            0x40c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MAEXIDR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MADPCR0",
            "MMDC Core Debug and Profiling Control Register 0",
            handles.bport1,
            0x410,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MADPCR0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MADPCR1",
            "MMDC Core Debug and Profiling Control Register 1",
            handles.bport1,
            0x414,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MADPCR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MADPSR0",
            "MMDC Core Debug and Profiling Status Register 0",
            handles.bport1,
            0x418,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MADPSR0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MADPSR1",
            "MMDC Core Debug and Profiling Status Register 1",
            handles.bport1,
            0x41c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MADPSR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MADPSR2",
            "MMDC Core Debug and Profiling Status Register 2",
            handles.bport1,
            0x420,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MADPSR2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MADPSR3",
            "MMDC Core Debug and Profiling Status Register 3",
            handles.bport1,
            0x424,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MADPSR3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MADPSR4",
            "MMDC Core Debug and Profiling Status Register 4",
            handles.bport1,
            0x428,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MADPSR4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MADPSR5",
            "MMDC Core Debug and Profiling Status Register 5",
            handles.bport1,
            0x42c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MADPSR5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MASBS0",
            "MMDC Core Step By Step Address Register",
            handles.bport1,
            0x430,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MASBS0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MASBS1",
            "MMDC Core Step By Step Address Attributes Register",
            handles.bport1,
            0x434,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MASBS1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MAGENP",
            "MMDC Core General Purpose Register",
            handles.bport1,
            0x440,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MAGENP.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPZQHWCTRL",
            "MMDC PHY ZQ HW control register",
            handles.bport1,
            0x800,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPZQHWCTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPZQSWCTRL",
            "MMDC PHY ZQ SW control register",
            handles.bport1,
            0x804,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPZQSWCTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPWLGCR",
            "MMDC PHY Write Leveling Configuration and Error Status Register",
            handles.bport1,
            0x808,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPWLGCR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPWLDECTRL0",
            "MMDC PHY Write Leveling Delay Control Register 0",
            handles.bport1,
            0x80c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPWLDECTRL0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPWLDECTRL1",
            "MMDC PHY Write Leveling Delay Control Register 1",
            handles.bport1,
            0x810,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPWLDECTRL1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPWLDLST",
            "MMDC PHY Write Leveling delay-line Status Register",
            handles.bport1,
            0x814,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MPWLDLST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPODTCTRL",
            "MMDC PHY ODT control register",
            handles.bport1,
            0x818,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPODTCTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPRDDQBY0DL",
            "MMDC PHY Read DQ Byte0 Delay Register",
            handles.bport1,
            0x81c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPRDDQBY0DL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPRDDQBY1DL",
            "MMDC PHY Read DQ Byte1 Delay Register",
            handles.bport1,
            0x820,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPRDDQBY1DL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPRDDQBY2DL",
            "MMDC PHY Read DQ Byte2 Delay Register",
            handles.bport1,
            0x824,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPRDDQBY2DL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPRDDQBY3DL",
            "MMDC PHY Read DQ Byte3 Delay Register",
            handles.bport1,
            0x828,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPRDDQBY3DL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPWRDQBY0DL",
            "MMDC PHY Write DQ Byte0 Delay Register",
            handles.bport1,
            0x82c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPWRDQBY0DL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPWRDQBY1DL",
            "MMDC PHY Write DQ Byte1 Delay Register",
            handles.bport1,
            0x830,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPWRDQBY1DL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPWRDQBY2DL",
            "MMDC PHY Write DQ Byte2 Delay Register",
            handles.bport1,
            0x834,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPWRDQBY2DL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPWRDQBY3DL",
            "MMDC PHY Write DQ Byte3 Delay Register",
            handles.bport1,
            0x838,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPWRDQBY3DL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPDGCTRL0",
            "MMDC PHY Read DQS Gating Control Register 0",
            handles.bport1,
            0x83c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPDGCTRL0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPDGCTRL1",
            "MMDC PHY Read DQS Gating Control Register 1",
            handles.bport1,
            0x840,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPDGCTRL1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPDGDLST0",
            "MMDC PHY Read DQS Gating delay-line Status Register",
            handles.bport1,
            0x844,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MPDGDLST0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPRDDLCTL",
            "MMDC PHY Read delay-lines Configuration Register",
            handles.bport1,
            0x848,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPRDDLCTL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPRDDLST",
            "MMDC PHY Read delay-lines Status Register",
            handles.bport1,
            0x84c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MPRDDLST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPWRDLCTL",
            "MMDC PHY Write delay-lines Configuration Register",
            handles.bport1,
            0x850,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPWRDLCTL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPWRDLST",
            "MMDC PHY Write delay-lines Status Register",
            handles.bport1,
            0x854,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MPWRDLST.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPSDCTRL",
            "MMDC PHY CK Control Register",
            handles.bport1,
            0x858,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPSDCTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPZQLP2CTL",
            "MMDC ZQ LPDDR2 HW Control Register",
            handles.bport1,
            0x85c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPZQLP2CTL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPRDDLHWCTL",
            "MMDC PHY Read Delay HW Calibration Control Register",
            handles.bport1,
            0x860,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPRDDLHWCTL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPWRDLHWCTL",
            "MMDC PHY Write Delay HW Calibration Control Register",
            handles.bport1,
            0x864,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPWRDLHWCTL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPRDDLHWST0",
            "MMDC PHY Read Delay HW Calibration Status Register 0",
            handles.bport1,
            0x868,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MPRDDLHWST0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPRDDLHWST1",
            "MMDC PHY Read Delay HW Calibration Status Register 1",
            handles.bport1,
            0x86c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MPRDDLHWST1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPWRDLHWST0",
            "MMDC PHY Write Delay HW Calibration Status Register 0",
            handles.bport1,
            0x870,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MPWRDLHWST0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPWRDLHWST1",
            "MMDC PHY Write Delay HW Calibration Status Register 1",
            handles.bport1,
            0x874,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MPWRDLHWST1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPWLHWERR",
            "MMDC PHY Write Leveling HW Error Register",
            handles.bport1,
            0x878,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPWLHWERR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPDGHWST0",
            "MMDC PHY Read DQS Gating HW Status Register 0",
            handles.bport1,
            0x87c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MPDGHWST0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPDGHWST1",
            "MMDC PHY Read DQS Gating HW Status Register 1",
            handles.bport1,
            0x880,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MPDGHWST1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPDGHWST2",
            "MMDC PHY Read DQS Gating HW Status Register 2",
            handles.bport1,
            0x884,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MPDGHWST2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPDGHWST3",
            "MMDC PHY Read DQS Gating HW Status Register 3",
            handles.bport1,
            0x888,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MPDGHWST3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPPDCMPR1",
            "MMDC PHY Pre-defined Compare Register 1",
            handles.bport1,
            0x88c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPPDCMPR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPPDCMPR2",
            "MMDC PHY Pre-defined Compare and CA delay-line Configuration Register",
            handles.bport1,
            0x890,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPPDCMPR2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPSWDAR0",
            "MMDC PHY SW Dummy Access Register",
            handles.bport1,
            0x894,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPSWDAR0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPSWDRDR0",
            "MMDC PHY SW Dummy Read Data Register 0",
            handles.bport1,
            0x898,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MPSWDRDR0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPSWDRDR1",
            "MMDC PHY SW Dummy Read Data Register 1",
            handles.bport1,
            0x89c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MPSWDRDR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPSWDRDR2",
            "MMDC PHY SW Dummy Read Data Register 2",
            handles.bport1,
            0x8a0,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MPSWDRDR2.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPSWDRDR3",
            "MMDC PHY SW Dummy Read Data Register 3",
            handles.bport1,
            0x8a4,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MPSWDRDR3.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPSWDRDR4",
            "MMDC PHY SW Dummy Read Data Register 4",
            handles.bport1,
            0x8a8,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MPSWDRDR4.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPSWDRDR5",
            "MMDC PHY SW Dummy Read Data Register 5",
            handles.bport1,
            0x8ac,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MPSWDRDR5.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPSWDRDR6",
            "MMDC PHY SW Dummy Read Data Register 6",
            handles.bport1,
            0x8b0,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MPSWDRDR6.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPSWDRDR7",
            "MMDC PHY SW Dummy Read Data Register 7",
            handles.bport1,
            0x8b4,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.MMDC_MPSWDRDR7.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPMUR0",
            "MMDC PHY Measure Unit Register",
            handles.bport1,
            0x8b8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPMUR0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPWRCADL",
            "MMDC Write CA delay-line controller",
            handles.bport1,
            0x8bc,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPWRCADL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MMDC_MPDCCR",
            "MMDC Duty Cycle Control Register",
            handles.bport1,
            0x8c0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MMDC_MPDCCR.value),
            True
        );
    }

}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_ab_data.MMDC_MPDCCR.value = (Uns32)(bport1_ab_data.MMDC_MPDCCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x24922492));
        bport1_ab_data.MMDC_MPWRCADL.value = (Uns32)(bport1_ab_data.MMDC_MPWRCADL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPMUR0.value = (Uns32)(bport1_ab_data.MMDC_MPMUR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPSWDRDR7.value = (Uns32)(bport1_ab_data.MMDC_MPSWDRDR7.value & ~(0xffffffff)) | ((0xffffffff) & (0xFFFFFFFF));
        bport1_ab_data.MMDC_MPSWDRDR6.value = (Uns32)(bport1_ab_data.MMDC_MPSWDRDR6.value & ~(0xffffffff)) | ((0xffffffff) & (0xFFFFFFFF));
        bport1_ab_data.MMDC_MPSWDRDR5.value = (Uns32)(bport1_ab_data.MMDC_MPSWDRDR5.value & ~(0xffffffff)) | ((0xffffffff) & (0xFFFFFFFF));
        bport1_ab_data.MMDC_MPSWDRDR4.value = (Uns32)(bport1_ab_data.MMDC_MPSWDRDR4.value & ~(0xffffffff)) | ((0xffffffff) & (0xFFFFFFFF));
        bport1_ab_data.MMDC_MPSWDRDR3.value = (Uns32)(bport1_ab_data.MMDC_MPSWDRDR3.value & ~(0xffffffff)) | ((0xffffffff) & (0xFFFFFFFF));
        bport1_ab_data.MMDC_MPSWDRDR2.value = (Uns32)(bport1_ab_data.MMDC_MPSWDRDR2.value & ~(0xffffffff)) | ((0xffffffff) & (0xFFFFFFFF));
        bport1_ab_data.MMDC_MPSWDRDR1.value = (Uns32)(bport1_ab_data.MMDC_MPSWDRDR1.value & ~(0xffffffff)) | ((0xffffffff) & (0xFFFFFFFF));
        bport1_ab_data.MMDC_MPSWDRDR0.value = (Uns32)(bport1_ab_data.MMDC_MPSWDRDR0.value & ~(0xffffffff)) | ((0xffffffff) & (0xFFFFFFFF));
        bport1_ab_data.MMDC_MPSWDAR0.value = (Uns32)(bport1_ab_data.MMDC_MPSWDAR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPPDCMPR2.value = (Uns32)(bport1_ab_data.MMDC_MPPDCMPR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00400000));
        bport1_ab_data.MMDC_MPPDCMPR1.value = (Uns32)(bport1_ab_data.MMDC_MPPDCMPR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPDGHWST3.value = (Uns32)(bport1_ab_data.MMDC_MPDGHWST3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPDGHWST2.value = (Uns32)(bport1_ab_data.MMDC_MPDGHWST2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPDGHWST1.value = (Uns32)(bport1_ab_data.MMDC_MPDGHWST1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPDGHWST0.value = (Uns32)(bport1_ab_data.MMDC_MPDGHWST0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPWLHWERR.value = (Uns32)(bport1_ab_data.MMDC_MPWLHWERR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPWRDLHWST1.value = (Uns32)(bport1_ab_data.MMDC_MPWRDLHWST1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPWRDLHWST0.value = (Uns32)(bport1_ab_data.MMDC_MPWRDLHWST0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPRDDLHWST1.value = (Uns32)(bport1_ab_data.MMDC_MPRDDLHWST1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPRDDLHWST0.value = (Uns32)(bport1_ab_data.MMDC_MPRDDLHWST0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPWRDLHWCTL.value = (Uns32)(bport1_ab_data.MMDC_MPWRDLHWCTL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPRDDLHWCTL.value = (Uns32)(bport1_ab_data.MMDC_MPRDDLHWCTL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPZQLP2CTL.value = (Uns32)(bport1_ab_data.MMDC_MPZQLP2CTL.value & ~(0xffffffff)) | ((0xffffffff) & (0x1B5F0109));
        bport1_ab_data.MMDC_MPSDCTRL.value = (Uns32)(bport1_ab_data.MMDC_MPSDCTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPWRDLST.value = (Uns32)(bport1_ab_data.MMDC_MPWRDLST.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPWRDLCTL.value = (Uns32)(bport1_ab_data.MMDC_MPWRDLCTL.value & ~(0xffffffff)) | ((0xffffffff) & (0x40404040));
        bport1_ab_data.MMDC_MPRDDLST.value = (Uns32)(bport1_ab_data.MMDC_MPRDDLST.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPRDDLCTL.value = (Uns32)(bport1_ab_data.MMDC_MPRDDLCTL.value & ~(0xffffffff)) | ((0xffffffff) & (0x40404040));
        bport1_ab_data.MMDC_MPDGDLST0.value = (Uns32)(bport1_ab_data.MMDC_MPDGDLST0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPDGCTRL1.value = (Uns32)(bport1_ab_data.MMDC_MPDGCTRL1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPDGCTRL0.value = (Uns32)(bport1_ab_data.MMDC_MPDGCTRL0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPWRDQBY3DL.value = (Uns32)(bport1_ab_data.MMDC_MPWRDQBY3DL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPWRDQBY2DL.value = (Uns32)(bport1_ab_data.MMDC_MPWRDQBY2DL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPWRDQBY1DL.value = (Uns32)(bport1_ab_data.MMDC_MPWRDQBY1DL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPWRDQBY0DL.value = (Uns32)(bport1_ab_data.MMDC_MPWRDQBY0DL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPRDDQBY3DL.value = (Uns32)(bport1_ab_data.MMDC_MPRDDQBY3DL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPRDDQBY2DL.value = (Uns32)(bport1_ab_data.MMDC_MPRDDQBY2DL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPRDDQBY1DL.value = (Uns32)(bport1_ab_data.MMDC_MPRDDQBY1DL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPRDDQBY0DL.value = (Uns32)(bport1_ab_data.MMDC_MPRDDQBY0DL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPODTCTRL.value = (Uns32)(bport1_ab_data.MMDC_MPODTCTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPWLDLST.value = (Uns32)(bport1_ab_data.MMDC_MPWLDLST.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPWLDECTRL1.value = (Uns32)(bport1_ab_data.MMDC_MPWLDECTRL1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPWLDECTRL0.value = (Uns32)(bport1_ab_data.MMDC_MPWLDECTRL0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPWLGCR.value = (Uns32)(bport1_ab_data.MMDC_MPWLGCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPZQSWCTRL.value = (Uns32)(bport1_ab_data.MMDC_MPZQSWCTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MPZQHWCTRL.value = (Uns32)(bport1_ab_data.MMDC_MPZQHWCTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0xA1380000));
        bport1_ab_data.MMDC_MAGENP.value = (Uns32)(bport1_ab_data.MMDC_MAGENP.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MASBS1.value = (Uns32)(bport1_ab_data.MMDC_MASBS1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MASBS0.value = (Uns32)(bport1_ab_data.MMDC_MASBS0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MADPSR5.value = (Uns32)(bport1_ab_data.MMDC_MADPSR5.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MADPSR4.value = (Uns32)(bport1_ab_data.MMDC_MADPSR4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MADPSR3.value = (Uns32)(bport1_ab_data.MMDC_MADPSR3.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MADPSR2.value = (Uns32)(bport1_ab_data.MMDC_MADPSR2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MADPSR1.value = (Uns32)(bport1_ab_data.MMDC_MADPSR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MADPSR0.value = (Uns32)(bport1_ab_data.MMDC_MADPSR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MADPCR1.value = (Uns32)(bport1_ab_data.MMDC_MADPCR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MADPCR0.value = (Uns32)(bport1_ab_data.MMDC_MADPCR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MAEXIDR1.value = (Uns32)(bport1_ab_data.MMDC_MAEXIDR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00600040));
        bport1_ab_data.MMDC_MAEXIDR0.value = (Uns32)(bport1_ab_data.MMDC_MAEXIDR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00200000));
        bport1_ab_data.MMDC_MAPSR.value = (Uns32)(bport1_ab_data.MMDC_MAPSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001007));
        bport1_ab_data.MMDC_MAARCR.value = (Uns32)(bport1_ab_data.MMDC_MAARCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x514201F0));
        bport1_ab_data.MMDC_MDASP.value = (Uns32)(bport1_ab_data.MMDC_MDASP.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000003F));
        bport1_ab_data.MMDC_MDMR4.value = (Uns32)(bport1_ab_data.MMDC_MDMR4.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MDCFG3LP.value = (Uns32)(bport1_ab_data.MMDC_MDCFG3LP.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MDMRR.value = (Uns32)(bport1_ab_data.MMDC_MDMRR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MDOR.value = (Uns32)(bport1_ab_data.MMDC_MDOR.value & ~(0xffffffff)) | ((0xffffffff) & (0x009F0E0E));
        bport1_ab_data.MMDC_MDRWD.value = (Uns32)(bport1_ab_data.MMDC_MDRWD.value & ~(0xffffffff)) | ((0xffffffff) & (0x0F9F26D2));
        bport1_ab_data.MMDC_MDREF.value = (Uns32)(bport1_ab_data.MMDC_MDREF.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000C000));
        bport1_ab_data.MMDC_MDSCR.value = (Uns32)(bport1_ab_data.MMDC_MDSCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MMDC_MDMISC.value = (Uns32)(bport1_ab_data.MMDC_MDMISC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001600));
        bport1_ab_data.MMDC_MDCFG2.value = (Uns32)(bport1_ab_data.MMDC_MDCFG2.value & ~(0xffffffff)) | ((0xffffffff) & (0x00C70092));
        bport1_ab_data.MMDC_MDCFG1.value = (Uns32)(bport1_ab_data.MMDC_MDCFG1.value & ~(0xffffffff)) | ((0xffffffff) & (0xB6B18A23));
        bport1_ab_data.MMDC_MDCFG0.value = (Uns32)(bport1_ab_data.MMDC_MDCFG0.value & ~(0xffffffff)) | ((0xffffffff) & (0x323622D3));
        bport1_ab_data.MMDC_MDOTC.value = (Uns32)(bport1_ab_data.MMDC_MDOTC.value & ~(0xffffffff)) | ((0xffffffff) & (0x12272000));
        bport1_ab_data.MMDC_MDPDC.value = (Uns32)(bport1_ab_data.MMDC_MDPDC.value & ~(0xffffffff)) | ((0xffffffff) & (0x00030012));
        bport1_ab_data.MMDC_MDCTL.value = (Uns32)(bport1_ab_data.MMDC_MDCTL.value & ~(0xffffffff)) | ((0xffffffff) & (0x03110000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "NXP i.MX6 MMDC");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This is a register only model with acknowledgement of auto power saving");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "i.MX 6Solo/6DualLite Applications Processor Reference Manual (IMX6SDLRM_Ref_Manual.pdf");
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

