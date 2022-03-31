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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "zynq_7000-slcr", "Example");
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

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_MIO_PIN_00_maskWrite) {
    bport1_ab_data.MIO_PIN_00.value = (bport1_ab_data.MIO_PIN_00.value & BPORT1_AB_MIO_PIN_00_WRNMASK) | (data & BPORT1_AB_MIO_PIN_00_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_01_maskWrite) {
    bport1_ab_data.MIO_PIN_01.value = (bport1_ab_data.MIO_PIN_01.value & BPORT1_AB_MIO_PIN_01_WRNMASK) | (data & BPORT1_AB_MIO_PIN_01_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_02_maskWrite) {
    bport1_ab_data.MIO_PIN_02.value = (bport1_ab_data.MIO_PIN_02.value & BPORT1_AB_MIO_PIN_02_WRNMASK) | (data & BPORT1_AB_MIO_PIN_02_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_03_maskWrite) {
    bport1_ab_data.MIO_PIN_03.value = (bport1_ab_data.MIO_PIN_03.value & BPORT1_AB_MIO_PIN_03_WRNMASK) | (data & BPORT1_AB_MIO_PIN_03_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_04_maskWrite) {
    bport1_ab_data.MIO_PIN_04.value = (bport1_ab_data.MIO_PIN_04.value & BPORT1_AB_MIO_PIN_04_WRNMASK) | (data & BPORT1_AB_MIO_PIN_04_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_05_maskWrite) {
    bport1_ab_data.MIO_PIN_05.value = (bport1_ab_data.MIO_PIN_05.value & BPORT1_AB_MIO_PIN_05_WRNMASK) | (data & BPORT1_AB_MIO_PIN_05_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_06_maskWrite) {
    bport1_ab_data.MIO_PIN_06.value = (bport1_ab_data.MIO_PIN_06.value & BPORT1_AB_MIO_PIN_06_WRNMASK) | (data & BPORT1_AB_MIO_PIN_06_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_07_maskWrite) {
    bport1_ab_data.MIO_PIN_07.value = (bport1_ab_data.MIO_PIN_07.value & BPORT1_AB_MIO_PIN_07_WRNMASK) | (data & BPORT1_AB_MIO_PIN_07_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_08_maskWrite) {
    bport1_ab_data.MIO_PIN_08.value = (bport1_ab_data.MIO_PIN_08.value & BPORT1_AB_MIO_PIN_08_WRNMASK) | (data & BPORT1_AB_MIO_PIN_08_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_09_maskWrite) {
    bport1_ab_data.MIO_PIN_09.value = (bport1_ab_data.MIO_PIN_09.value & BPORT1_AB_MIO_PIN_09_WRNMASK) | (data & BPORT1_AB_MIO_PIN_09_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_10_maskWrite) {
    bport1_ab_data.MIO_PIN_10.value = (bport1_ab_data.MIO_PIN_10.value & BPORT1_AB_MIO_PIN_10_WRNMASK) | (data & BPORT1_AB_MIO_PIN_10_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_11_maskWrite) {
    bport1_ab_data.MIO_PIN_11.value = (bport1_ab_data.MIO_PIN_11.value & BPORT1_AB_MIO_PIN_11_WRNMASK) | (data & BPORT1_AB_MIO_PIN_11_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_12_maskWrite) {
    bport1_ab_data.MIO_PIN_12.value = (bport1_ab_data.MIO_PIN_12.value & BPORT1_AB_MIO_PIN_12_WRNMASK) | (data & BPORT1_AB_MIO_PIN_12_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_13_maskWrite) {
    bport1_ab_data.MIO_PIN_13.value = (bport1_ab_data.MIO_PIN_13.value & BPORT1_AB_MIO_PIN_13_WRNMASK) | (data & BPORT1_AB_MIO_PIN_13_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_14_maskWrite) {
    bport1_ab_data.MIO_PIN_14.value = (bport1_ab_data.MIO_PIN_14.value & BPORT1_AB_MIO_PIN_14_WRNMASK) | (data & BPORT1_AB_MIO_PIN_14_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_15_maskWrite) {
    bport1_ab_data.MIO_PIN_15.value = (bport1_ab_data.MIO_PIN_15.value & BPORT1_AB_MIO_PIN_15_WRNMASK) | (data & BPORT1_AB_MIO_PIN_15_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_16_maskWrite) {
    bport1_ab_data.MIO_PIN_16.value = (bport1_ab_data.MIO_PIN_16.value & BPORT1_AB_MIO_PIN_16_WRNMASK) | (data & BPORT1_AB_MIO_PIN_16_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_17_maskWrite) {
    bport1_ab_data.MIO_PIN_17.value = (bport1_ab_data.MIO_PIN_17.value & BPORT1_AB_MIO_PIN_17_WRNMASK) | (data & BPORT1_AB_MIO_PIN_17_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_18_maskWrite) {
    bport1_ab_data.MIO_PIN_18.value = (bport1_ab_data.MIO_PIN_18.value & BPORT1_AB_MIO_PIN_18_WRNMASK) | (data & BPORT1_AB_MIO_PIN_18_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_19_maskWrite) {
    bport1_ab_data.MIO_PIN_19.value = (bport1_ab_data.MIO_PIN_19.value & BPORT1_AB_MIO_PIN_19_WRNMASK) | (data & BPORT1_AB_MIO_PIN_19_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_20_maskWrite) {
    bport1_ab_data.MIO_PIN_20.value = (bport1_ab_data.MIO_PIN_20.value & BPORT1_AB_MIO_PIN_20_WRNMASK) | (data & BPORT1_AB_MIO_PIN_20_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_21_maskWrite) {
    bport1_ab_data.MIO_PIN_21.value = (bport1_ab_data.MIO_PIN_21.value & BPORT1_AB_MIO_PIN_21_WRNMASK) | (data & BPORT1_AB_MIO_PIN_21_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_22_maskWrite) {
    bport1_ab_data.MIO_PIN_22.value = (bport1_ab_data.MIO_PIN_22.value & BPORT1_AB_MIO_PIN_22_WRNMASK) | (data & BPORT1_AB_MIO_PIN_22_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_23_maskWrite) {
    bport1_ab_data.MIO_PIN_23.value = (bport1_ab_data.MIO_PIN_23.value & BPORT1_AB_MIO_PIN_23_WRNMASK) | (data & BPORT1_AB_MIO_PIN_23_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_24_maskWrite) {
    bport1_ab_data.MIO_PIN_24.value = (bport1_ab_data.MIO_PIN_24.value & BPORT1_AB_MIO_PIN_24_WRNMASK) | (data & BPORT1_AB_MIO_PIN_24_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_25_maskWrite) {
    bport1_ab_data.MIO_PIN_25.value = (bport1_ab_data.MIO_PIN_25.value & BPORT1_AB_MIO_PIN_25_WRNMASK) | (data & BPORT1_AB_MIO_PIN_25_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_26_maskWrite) {
    bport1_ab_data.MIO_PIN_26.value = (bport1_ab_data.MIO_PIN_26.value & BPORT1_AB_MIO_PIN_26_WRNMASK) | (data & BPORT1_AB_MIO_PIN_26_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_27_maskWrite) {
    bport1_ab_data.MIO_PIN_27.value = (bport1_ab_data.MIO_PIN_27.value & BPORT1_AB_MIO_PIN_27_WRNMASK) | (data & BPORT1_AB_MIO_PIN_27_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_28_maskWrite) {
    bport1_ab_data.MIO_PIN_28.value = (bport1_ab_data.MIO_PIN_28.value & BPORT1_AB_MIO_PIN_28_WRNMASK) | (data & BPORT1_AB_MIO_PIN_28_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_29_maskWrite) {
    bport1_ab_data.MIO_PIN_29.value = (bport1_ab_data.MIO_PIN_29.value & BPORT1_AB_MIO_PIN_29_WRNMASK) | (data & BPORT1_AB_MIO_PIN_29_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_30_maskWrite) {
    bport1_ab_data.MIO_PIN_30.value = (bport1_ab_data.MIO_PIN_30.value & BPORT1_AB_MIO_PIN_30_WRNMASK) | (data & BPORT1_AB_MIO_PIN_30_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_31_maskWrite) {
    bport1_ab_data.MIO_PIN_31.value = (bport1_ab_data.MIO_PIN_31.value & BPORT1_AB_MIO_PIN_31_WRNMASK) | (data & BPORT1_AB_MIO_PIN_31_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_32_maskWrite) {
    bport1_ab_data.MIO_PIN_32.value = (bport1_ab_data.MIO_PIN_32.value & BPORT1_AB_MIO_PIN_32_WRNMASK) | (data & BPORT1_AB_MIO_PIN_32_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_33_maskWrite) {
    bport1_ab_data.MIO_PIN_33.value = (bport1_ab_data.MIO_PIN_33.value & BPORT1_AB_MIO_PIN_33_WRNMASK) | (data & BPORT1_AB_MIO_PIN_33_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_34_maskWrite) {
    bport1_ab_data.MIO_PIN_34.value = (bport1_ab_data.MIO_PIN_34.value & BPORT1_AB_MIO_PIN_34_WRNMASK) | (data & BPORT1_AB_MIO_PIN_34_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_35_maskWrite) {
    bport1_ab_data.MIO_PIN_35.value = (bport1_ab_data.MIO_PIN_35.value & BPORT1_AB_MIO_PIN_35_WRNMASK) | (data & BPORT1_AB_MIO_PIN_35_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_36_maskWrite) {
    bport1_ab_data.MIO_PIN_36.value = (bport1_ab_data.MIO_PIN_36.value & BPORT1_AB_MIO_PIN_36_WRNMASK) | (data & BPORT1_AB_MIO_PIN_36_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_37_maskWrite) {
    bport1_ab_data.MIO_PIN_37.value = (bport1_ab_data.MIO_PIN_37.value & BPORT1_AB_MIO_PIN_37_WRNMASK) | (data & BPORT1_AB_MIO_PIN_37_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_38_maskWrite) {
    bport1_ab_data.MIO_PIN_38.value = (bport1_ab_data.MIO_PIN_38.value & BPORT1_AB_MIO_PIN_38_WRNMASK) | (data & BPORT1_AB_MIO_PIN_38_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_39_maskWrite) {
    bport1_ab_data.MIO_PIN_39.value = (bport1_ab_data.MIO_PIN_39.value & BPORT1_AB_MIO_PIN_39_WRNMASK) | (data & BPORT1_AB_MIO_PIN_39_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_40_maskWrite) {
    bport1_ab_data.MIO_PIN_40.value = (bport1_ab_data.MIO_PIN_40.value & BPORT1_AB_MIO_PIN_40_WRNMASK) | (data & BPORT1_AB_MIO_PIN_40_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_41_maskWrite) {
    bport1_ab_data.MIO_PIN_41.value = (bport1_ab_data.MIO_PIN_41.value & BPORT1_AB_MIO_PIN_41_WRNMASK) | (data & BPORT1_AB_MIO_PIN_41_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_42_maskWrite) {
    bport1_ab_data.MIO_PIN_42.value = (bport1_ab_data.MIO_PIN_42.value & BPORT1_AB_MIO_PIN_42_WRNMASK) | (data & BPORT1_AB_MIO_PIN_42_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_43_maskWrite) {
    bport1_ab_data.MIO_PIN_43.value = (bport1_ab_data.MIO_PIN_43.value & BPORT1_AB_MIO_PIN_43_WRNMASK) | (data & BPORT1_AB_MIO_PIN_43_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_44_maskWrite) {
    bport1_ab_data.MIO_PIN_44.value = (bport1_ab_data.MIO_PIN_44.value & BPORT1_AB_MIO_PIN_44_WRNMASK) | (data & BPORT1_AB_MIO_PIN_44_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_45_maskWrite) {
    bport1_ab_data.MIO_PIN_45.value = (bport1_ab_data.MIO_PIN_45.value & BPORT1_AB_MIO_PIN_45_WRNMASK) | (data & BPORT1_AB_MIO_PIN_45_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_46_maskWrite) {
    bport1_ab_data.MIO_PIN_46.value = (bport1_ab_data.MIO_PIN_46.value & BPORT1_AB_MIO_PIN_46_WRNMASK) | (data & BPORT1_AB_MIO_PIN_46_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_47_maskWrite) {
    bport1_ab_data.MIO_PIN_47.value = (bport1_ab_data.MIO_PIN_47.value & BPORT1_AB_MIO_PIN_47_WRNMASK) | (data & BPORT1_AB_MIO_PIN_47_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_48_maskWrite) {
    bport1_ab_data.MIO_PIN_48.value = (bport1_ab_data.MIO_PIN_48.value & BPORT1_AB_MIO_PIN_48_WRNMASK) | (data & BPORT1_AB_MIO_PIN_48_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_49_maskWrite) {
    bport1_ab_data.MIO_PIN_49.value = (bport1_ab_data.MIO_PIN_49.value & BPORT1_AB_MIO_PIN_49_WRNMASK) | (data & BPORT1_AB_MIO_PIN_49_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_50_maskWrite) {
    bport1_ab_data.MIO_PIN_50.value = (bport1_ab_data.MIO_PIN_50.value & BPORT1_AB_MIO_PIN_50_WRNMASK) | (data & BPORT1_AB_MIO_PIN_50_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_51_maskWrite) {
    bport1_ab_data.MIO_PIN_51.value = (bport1_ab_data.MIO_PIN_51.value & BPORT1_AB_MIO_PIN_51_WRNMASK) | (data & BPORT1_AB_MIO_PIN_51_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_52_maskWrite) {
    bport1_ab_data.MIO_PIN_52.value = (bport1_ab_data.MIO_PIN_52.value & BPORT1_AB_MIO_PIN_52_WRNMASK) | (data & BPORT1_AB_MIO_PIN_52_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MIO_PIN_53_maskWrite) {
    bport1_ab_data.MIO_PIN_53.value = (bport1_ab_data.MIO_PIN_53.value & BPORT1_AB_MIO_PIN_53_WRNMASK) | (data & BPORT1_AB_MIO_PIN_53_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TZ_DDR_RAM_maskWrite) {
    bport1_ab_data.TZ_DDR_RAM.value = (bport1_ab_data.TZ_DDR_RAM.value & BPORT1_AB_TZ_DDR_RAM_WRNMASK) | (data & BPORT1_AB_TZ_DDR_RAM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TZ_DMA_IRQ_NS_maskWrite) {
    bport1_ab_data.TZ_DMA_IRQ_NS.value = (bport1_ab_data.TZ_DMA_IRQ_NS.value & BPORT1_AB_TZ_DMA_IRQ_NS_WRNMASK) | (data & BPORT1_AB_TZ_DMA_IRQ_NS_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TZ_DMA_NS_maskWrite) {
    bport1_ab_data.TZ_DMA_NS.value = (bport1_ab_data.TZ_DMA_NS.value & BPORT1_AB_TZ_DMA_NS_WRNMASK) | (data & BPORT1_AB_TZ_DMA_NS_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TZ_DMA_PERIPH_NS_maskWrite) {
    bport1_ab_data.TZ_DMA_PERIPH_NS.value = (bport1_ab_data.TZ_DMA_PERIPH_NS.value & BPORT1_AB_TZ_DMA_PERIPH_NS_WRNMASK) | (data & BPORT1_AB_TZ_DMA_PERIPH_NS_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TZ_FPGA_AFI_maskWrite) {
    bport1_ab_data.TZ_FPGA_AFI.value = (bport1_ab_data.TZ_FPGA_AFI.value & BPORT1_AB_TZ_FPGA_AFI_WRNMASK) | (data & BPORT1_AB_TZ_FPGA_AFI_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TZ_FPGA_M_maskWrite) {
    bport1_ab_data.TZ_FPGA_M.value = (bport1_ab_data.TZ_FPGA_M.value & BPORT1_AB_TZ_FPGA_M_WRNMASK) | (data & BPORT1_AB_TZ_FPGA_M_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TZ_GEM_maskWrite) {
    bport1_ab_data.TZ_GEM.value = (bport1_ab_data.TZ_GEM.value & BPORT1_AB_TZ_GEM_WRNMASK) | (data & BPORT1_AB_TZ_GEM_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TZ_SDIO_maskWrite) {
    bport1_ab_data.TZ_SDIO.value = (bport1_ab_data.TZ_SDIO.value & BPORT1_AB_TZ_SDIO_WRNMASK) | (data & BPORT1_AB_TZ_SDIO_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TZ_USB_maskWrite) {
    bport1_ab_data.TZ_USB.value = (bport1_ab_data.TZ_USB.value & BPORT1_AB_TZ_USB_WRNMASK) | (data & BPORT1_AB_TZ_USB_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 3072);
    if (!handles.bport1) {
        bhmMessage("E", "PPM_SPNC", "Could not connect port 'bport1'");
    }

    ppmInstallReadCallback(regNoDefinitionRead, (void*)0 , handles.bport1 + 0x0, 0xc00);
    ppmInstallWriteCallback(regNoDefinitionWrite, (void*)0 , handles.bport1 + 0x0, 0xc00);
}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abSCL_reg = ppmCreateRegister(
            "ab_SCL",
            "Secure Configuration Lock",
            handles.bport1,
            0x0,
            4,
            read_32,
            WriteSCL,
            view32,
            &(bport1_ab_data.SCL.value),
            True
        );

        ppmCreateRegisterField(abSCL_reg, "LOCK", 0, 0, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_SLCR_LOCK",
            "SLCR Write Protection Lock",
            handles.bport1,
            0x4,
            4,
            ReadSLCR_LOCK,
            WriteSLCR_LOCK,
            view32,
            &(bport1_ab_data.SLCR_LOCK.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_SLCR_UNLOCK",
            "SLCR Write Protection Unlock",
            handles.bport1,
            0x8,
            4,
            ReadSLCR_UNLOCK,
            WriteSLCR_UNLOCK,
            view32,
            &(bport1_ab_data.SLCR_UNLOCK.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_SLCR_LOCKSTA",
            "SLCR Write Protection Status",
            handles.bport1,
            0xc,
            4,
            ReadSLCR_LOCKSTA,
            0,
            view32,
            &(bport1_ab_data.SLCR_LOCKSTA.value),
            True
        );
    }
    {
        registerHandle abARM_PLL_CTRL_reg = ppmCreateRegister(
            "ab_ARM_PLL_CTRL",
            "ARM PLL Control",
            handles.bport1,
            0x100,
            4,
            ReadARM_PLL_CTRL,
            WriteARM_PLL_CTRL,
            view32,
            &(bport1_ab_data.ARM_PLL_CTRL.value),
            True
        );

        ppmCreateRegisterField(abARM_PLL_CTRL_reg, "PLL_FDIV", 0, 12, 7, 1, 1);
        ppmCreateRegisterField(abARM_PLL_CTRL_reg, "PLL_BYPASS_FORCE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abARM_PLL_CTRL_reg, "PLL_BYPASS_QUAL", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abARM_PLL_CTRL_reg, "PLL_PWRDWN", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abARM_PLL_CTRL_reg, "PLL_RESET", 0, 0, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_DDR_PLL_CTRL",
            "DDR PLL Control",
            handles.bport1,
            0x104,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DDR_PLL_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_IO_PLL_CTRL",
            "IO PLL Control",
            handles.bport1,
            0x108,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.IO_PLL_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_PLL_STATUS",
            "PLL Status",
            handles.bport1,
            0x10c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.PLL_STATUS.value),
            True
        );
    }
    {
        registerHandle abARM_PLL_CFG_reg = ppmCreateRegister(
            "ab_ARM_PLL_CFG",
            "ARM PLL Configuration",
            handles.bport1,
            0x110,
            4,
            ReadARM_PLL_CFG,
            WriteARM_PLL_CFG,
            view32,
            &(bport1_ab_data.ARM_PLL_CFG.value),
            True
        );

        ppmCreateRegisterField(abARM_PLL_CFG_reg, "LOC_CNT", 0, 12, 10, 1, 1);
        ppmCreateRegisterField(abARM_PLL_CFG_reg, "PLL_CP", 0, 8, 4, 1, 1);
        ppmCreateRegisterField(abARM_PLL_CFG_reg, "PLL_RES", 0, 4, 4, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_DDR_PLL_CFG",
            "DDR PLL Configuration",
            handles.bport1,
            0x114,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DDR_PLL_CFG.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_IO_PLL_CFG",
            "IO PLL Configuration",
            handles.bport1,
            0x118,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.IO_PLL_CFG.value),
            True
        );
    }
    {
        registerHandle abARM_CLK_CTRL_reg = ppmCreateRegister(
            "ab_ARM_CLK_CTRL",
            "CPU Clock Control",
            handles.bport1,
            0x120,
            4,
            ReadARM_CLK_CTRL,
            WriteARM_CLK_CTRL,
            view32,
            &(bport1_ab_data.ARM_CLK_CTRL.value),
            True
        );

        ppmCreateRegisterField(abARM_CLK_CTRL_reg, "CPU_PERICLKACT", 0, 28, 1, 1, 1);
        ppmCreateRegisterField(abARM_CLK_CTRL_reg, "CPU_1XCLKACT", 0, 27, 1, 1, 1);
        ppmCreateRegisterField(abARM_CLK_CTRL_reg, "CPU_2XCLKACT", 0, 26, 1, 1, 1);
        ppmCreateRegisterField(abARM_CLK_CTRL_reg, "CPU_6OR3XCLKACT", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abARM_CLK_CTRL_reg, "CPU_4OR4XCLKACT", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abARM_CLK_CTRL_reg, "DIVISOR", 0, 8, 6, 1, 1);
        ppmCreateRegisterField(abARM_CLK_CTRL_reg, "SRCSEL", 0, 4, 2, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_DDR_CLK_CTRL",
            "DDR Clock Control",
            handles.bport1,
            0x124,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DDR_CLK_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DCI_CLK_CTRL",
            "DCI clock control",
            handles.bport1,
            0x128,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DCI_CLK_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_APER_CLK_CTRL",
            "AMBA Peripheral Clock Control",
            handles.bport1,
            0x12c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.APER_CLK_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_USB0_CLK_CTRL",
            "USB 0 ULPI Clock Control",
            handles.bport1,
            0x130,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.USB0_CLK_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_USB1_CLK_CTRL",
            "USB 1 ULPI Clock Control",
            handles.bport1,
            0x134,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.USB1_CLK_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_GEM0_RCLK_CTRL",
            "GigE 0 Rx Clock and Rx Signals Select",
            handles.bport1,
            0x138,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.GEM0_RCLK_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_GEM1_RCLK_CTRL",
            "GigE 1 Rx Clock and Rx Signals Select",
            handles.bport1,
            0x13c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.GEM1_RCLK_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_GEM0_CLK_CTRL",
            "GigE 0 Ref Clock Control",
            handles.bport1,
            0x140,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.GEM0_CLK_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_GEM1_CLK_CTRL",
            "GigE 1 Ref Clock Control",
            handles.bport1,
            0x144,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.GEM1_CLK_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_SMC_CLK_CTRL",
            "SMC Ref Clock Control",
            handles.bport1,
            0x148,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.SMC_CLK_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_LQSPI_CLK_CTRL",
            "Quad SPI Ref Clock Control",
            handles.bport1,
            0x14c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.LQSPI_CLK_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_SDIO_CLK_CTRL",
            "SDIO Ref Clock Control",
            handles.bport1,
            0x150,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.SDIO_CLK_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_UART_CLK_CTRL",
            "UART Ref Clock Control",
            handles.bport1,
            0x154,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.UART_CLK_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_SPI_CLK_CTRL",
            "SPI Ref Clock Control",
            handles.bport1,
            0x158,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.SPI_CLK_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CAN_CLK_CTRL",
            "CAN Ref Clock Control",
            handles.bport1,
            0x15c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CAN_CLK_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CAN_MIOCLK_CTRL",
            "CAN MIO Clock Control",
            handles.bport1,
            0x160,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CAN_MIOCLK_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DBG_CLK_CTRL",
            "SoC Debug Clock Control",
            handles.bport1,
            0x164,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DBG_CLK_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_PCAP_CLK_CTRL",
            "PCAP Clock Control",
            handles.bport1,
            0x168,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.PCAP_CLK_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TOPSW_CLK_CTRL",
            "Central Interconnect Clock Control",
            handles.bport1,
            0x16c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.TOPSW_CLK_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_FPGA0_CLK_CTRL",
            "PL Clock 0 Output control",
            handles.bport1,
            0x170,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.FPGA0_CLK_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_FPGA0_THR_CTRL",
            "PL Clock 0 Throttle control",
            handles.bport1,
            0x174,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.FPGA0_THR_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_FPGA0_THR_CNT",
            "PL Clock 0 Throttle Count control",
            handles.bport1,
            0x178,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.FPGA0_THR_CNT.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_FPGA0_THR_STA",
            "PL Clock 0 Throttle Status read",
            handles.bport1,
            0x17c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.FPGA0_THR_STA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_FPGA1_CLK_CTRL",
            "PL Clock 1 Output control",
            handles.bport1,
            0x180,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.FPGA1_CLK_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_FPGA1_THR_CTRL",
            "PL Clock 1 Throttle control",
            handles.bport1,
            0x184,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.FPGA1_THR_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_FPGA1_THR_CNT",
            "PL Clock 1 Throttle Count",
            handles.bport1,
            0x188,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.FPGA1_THR_CNT.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_FPGA1_THR_STA",
            "PL Clock 1 Throttle Status control",
            handles.bport1,
            0x18c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.FPGA1_THR_STA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_FPGA2_CLK_CTRL",
            "PL Clock 2 output control",
            handles.bport1,
            0x190,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.FPGA2_CLK_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_FPGA2_THR_CTRL",
            "PL Clock 2 Throttle Control",
            handles.bport1,
            0x194,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.FPGA2_THR_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_FPGA2_THR_CNT",
            "PL Clock 2 Throttle Count",
            handles.bport1,
            0x198,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.FPGA2_THR_CNT.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_FPGA2_THR_STA",
            "PL Clock 2 Throttle Status",
            handles.bport1,
            0x19c,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.FPGA2_THR_STA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_FPGA3_CLK_CTRL",
            "PL Clock 3 output control",
            handles.bport1,
            0x1a0,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.FPGA3_CLK_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_FPGA3_THR_CTRL",
            "PL Clock 3 Throttle Control",
            handles.bport1,
            0x1a4,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.FPGA3_THR_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_FPGA3_THR_CNT",
            "PL Clock 3 Throttle Count",
            handles.bport1,
            0x1a8,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.FPGA3_THR_CNT.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_FPGA3_THR_STA",
            "PL Clock 3 Throttle Status",
            handles.bport1,
            0x1ac,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.FPGA3_THR_STA.value),
            True
        );
    }
    {
        registerHandle abCLK_621_TRUE_reg = ppmCreateRegister(
            "ab_CLK_621_TRUE",
            "CPU Clock Ratio Mode select",
            handles.bport1,
            0x1c4,
            4,
            read_32,
            WriteCLK_621_TRUE,
            view32,
            &(bport1_ab_data.CLK_621_TRUE.value),
            True
        );

        ppmCreateRegisterField(abCLK_621_TRUE_reg, "CLK_621", 0, 0, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_PSS_RST_CTRL",
            "PS Software Reset Control",
            handles.bport1,
            0x200,
            4,
            read_32,
            WritePSS_RST_CTRL,
            view32,
            &(bport1_ab_data.PSS_RST_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DDR_RST_CTRL",
            "DDR Software Reset Control",
            handles.bport1,
            0x204,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DDR_RST_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TOPSW_RST_CTRL",
            "Central Interconnect Reset Control",
            handles.bport1,
            0x208,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.TOPSW_RST_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DMAC_RST_CTRL",
            "DMAC Software Reset Control",
            handles.bport1,
            0x20c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DMAC_RST_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_USB_RST_CTRL",
            "USB Software Reset Control",
            handles.bport1,
            0x210,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.USB_RST_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_GEM_RST_CTRL",
            "Gigabit Ethernet SW Reset Control",
            handles.bport1,
            0x214,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.GEM_RST_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_SDIO_RST_CTRL",
            "SDIO Software Reset Control",
            handles.bport1,
            0x218,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.SDIO_RST_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_SPI_RST_CTRL",
            "SPI Software Reset Control",
            handles.bport1,
            0x21c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.SPI_RST_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_CAN_RST_CTRL",
            "CAN Software Reset Control",
            handles.bport1,
            0x220,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.CAN_RST_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_I2C_RST_CTRL",
            "I2C Software Reset Control",
            handles.bport1,
            0x224,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.I2C_RST_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_UART_RST_CTRL",
            "UART Software Reset Control",
            handles.bport1,
            0x228,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.UART_RST_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_GPIO_RST_CTRL",
            "GPIO Software Reset Control",
            handles.bport1,
            0x22c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.GPIO_RST_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_LQSPI_RST_CTRL",
            "Quad SPI Software Reset Control",
            handles.bport1,
            0x230,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.LQSPI_RST_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_SMC_RST_CTRL",
            "SMC Software Reset Control",
            handles.bport1,
            0x234,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.SMC_RST_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_OCM_RST_CTRL",
            "OCM Software Reset Control",
            handles.bport1,
            0x238,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.OCM_RST_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_FPGA_RST_CTRL",
            "FPGA Software Reset Control",
            handles.bport1,
            0x240,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.FPGA_RST_CTRL.value),
            True
        );
    }
    {
        registerHandle abA9_CPU_RST_CTRL_reg = ppmCreateRegister(
            "ab_A9_CPU_RST_CTRL",
            "CPU Reset and Clock control",
            handles.bport1,
            0x244,
            4,
            ReadA9_CPU_RST_CTRL,
            WriteA9_CPU_RST_CTRL,
            view32,
            &(bport1_ab_data.A9_CPU_RST_CTRL.value),
            True
        );

        ppmCreateRegisterField(abA9_CPU_RST_CTRL_reg, "PERI_RST", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abA9_CPU_RST_CTRL_reg, "A9_CLKSTOP1", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abA9_CPU_RST_CTRL_reg, "A9_CLKSTOP0", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abA9_CPU_RST_CTRL_reg, "A9_RST1", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abA9_CPU_RST_CTRL_reg, "A9_RST0", 0, 0, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_RS_AWDT_CTRL",
            "Watchdog Timer Reset Control",
            handles.bport1,
            0x24c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.RS_AWDT_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_REBOOT_STATUS",
            "Reboot Status, persistent",
            handles.bport1,
            0x258,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.REBOOT_STATUS.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_BOOT_MODE",
            "Boot Mode Strapping Pins",
            handles.bport1,
            0x25c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.BOOT_MODE.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_APU_CTRL",
            "APU Control",
            handles.bport1,
            0x300,
            4,
            read_32,
            WriteAPU_CTRL,
            view32,
            &(bport1_ab_data.APU_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_WDT_CLK_SEL",
            "SWDT clock source select",
            handles.bport1,
            0x304,
            4,
            read_32,
            WriteWDT_CLK_SEL,
            view32,
            &(bport1_ab_data.WDT_CLK_SEL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZ_OCM_RAM0",
            "OCM RAM TrustZone Config 0",
            handles.bport1,
            0x400,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.TZ_OCM_RAM0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZ_OCM_RAM1",
            "OCM RAM TrustZone Config 1",
            handles.bport1,
            0x404,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.TZ_OCM_RAM1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZ_OCM",
            "OCM ROM TrustZone Config",
            handles.bport1,
            0x408,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.TZ_OCM.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZ_DDR_RAM",
            "DDR RAM TrustZone Config",
            handles.bport1,
            0x430,
            4,
            read_32,
            bport1_ab_TZ_DDR_RAM_maskWrite,
            view32,
            &(bport1_ab_data.TZ_DDR_RAM.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZ_DMA_NS",
            "DMAC TrustZone Config",
            handles.bport1,
            0x440,
            4,
            read_32,
            bport1_ab_TZ_DMA_NS_maskWrite,
            view32,
            &(bport1_ab_data.TZ_DMA_NS.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZ_DMA_IRQ_NS",
            "DMAC TrustZone Config for Interrupts",
            handles.bport1,
            0x444,
            4,
            read_32,
            bport1_ab_TZ_DMA_IRQ_NS_maskWrite,
            view32,
            &(bport1_ab_data.TZ_DMA_IRQ_NS.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZ_DMA_PERIPH_NS",
            "DMAC TrustZone Config for Peripherals",
            handles.bport1,
            0x448,
            4,
            read_32,
            bport1_ab_TZ_DMA_PERIPH_NS_maskWrite,
            view32,
            &(bport1_ab_data.TZ_DMA_PERIPH_NS.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZ_GEM",
            "Ethernet TrustZone Config",
            handles.bport1,
            0x450,
            4,
            read_32,
            bport1_ab_TZ_GEM_maskWrite,
            view32,
            &(bport1_ab_data.TZ_GEM.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZ_SDIO",
            "SDIO TrustZone Config",
            handles.bport1,
            0x454,
            4,
            read_32,
            bport1_ab_TZ_SDIO_maskWrite,
            view32,
            &(bport1_ab_data.TZ_SDIO.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZ_USB",
            "USB TrustZone Config",
            handles.bport1,
            0x458,
            4,
            read_32,
            bport1_ab_TZ_USB_maskWrite,
            view32,
            &(bport1_ab_data.TZ_USB.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZ_FPGA_M",
            "FPGA master ports TrustZone Disable",
            handles.bport1,
            0x484,
            4,
            read_32,
            bport1_ab_TZ_FPGA_M_maskWrite,
            view32,
            &(bport1_ab_data.TZ_FPGA_M.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TZ_FPGA_AFI",
            "FPGA AFI AXI ports TrustZone Disable",
            handles.bport1,
            0x488,
            4,
            read_32,
            bport1_ab_TZ_FPGA_AFI_maskWrite,
            view32,
            &(bport1_ab_data.TZ_FPGA_AFI.value),
            True
        );
    }
    {
        registerHandle abPSS_IDCODE_reg = ppmCreateRegister(
            "ab_PSS_IDCODE",
            "PS IDCODE (REVISION=1 FAMILY=0x1b SUBFAMILY=0x9 DEVICE=0x11 (7z045) MANUFACTURE_ID=0x49",
            handles.bport1,
            0x530,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.PSS_IDCODE.value),
            True
        );

        ppmCreateRegisterField(abPSS_IDCODE_reg, "REV", 0, 28, 4, 1, 0);
        ppmCreateRegisterField(abPSS_IDCODE_reg, "FAM", 0, 21, 7, 1, 0);
        ppmCreateRegisterField(abPSS_IDCODE_reg, "SUB", 0, 17, 4, 1, 0);
        ppmCreateRegisterField(abPSS_IDCODE_reg, "DEV", 0, 12, 5, 1, 0);
        ppmCreateRegisterField(abPSS_IDCODE_reg, "MAN", 0, 1, 11, 1, 0);
    }
    {
        ppmCreateRegister(
            "ab_DDR_URGENT",
            "DDR Urgent Control",
            handles.bport1,
            0x600,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DDR_URGENT.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DDR_CAL_START",
            "DDR Calibration Start Triggers",
            handles.bport1,
            0x60c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DDR_CAL_START.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DDR_REF_START",
            "DDR Refresh Start Triggers",
            handles.bport1,
            0x614,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DDR_REF_START.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DDR_CMD_STA",
            "DDR Command Store Status",
            handles.bport1,
            0x618,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DDR_CMD_STA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DDR_URGENT_SEL",
            "DDR Urgent Select",
            handles.bport1,
            0x61c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DDR_URGENT_SEL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DDR_DFI_STATUS",
            "DDR DFI status",
            handles.bport1,
            0x620,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DDR_DFI_STATUS.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_00",
            "MIO Pin 0 Control",
            handles.bport1,
            0x700,
            4,
            read_32,
            bport1_ab_MIO_PIN_00_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_00.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_01",
            "MIO Pin 1 Control",
            handles.bport1,
            0x704,
            4,
            read_32,
            bport1_ab_MIO_PIN_01_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_01.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_02",
            "MIO Pin 2 Control",
            handles.bport1,
            0x708,
            4,
            read_32,
            bport1_ab_MIO_PIN_02_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_02.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_03",
            "MIO Pin 3 Control",
            handles.bport1,
            0x70c,
            4,
            read_32,
            bport1_ab_MIO_PIN_03_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_03.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_04",
            "MIO Pin 4 Control",
            handles.bport1,
            0x710,
            4,
            read_32,
            bport1_ab_MIO_PIN_04_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_04.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_05",
            "MIO Pin 5 Control",
            handles.bport1,
            0x714,
            4,
            read_32,
            bport1_ab_MIO_PIN_05_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_05.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_06",
            "MIO Pin 6 Control",
            handles.bport1,
            0x718,
            4,
            read_32,
            bport1_ab_MIO_PIN_06_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_06.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_07",
            "MIO Pin 7 Control",
            handles.bport1,
            0x71c,
            4,
            read_32,
            bport1_ab_MIO_PIN_07_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_07.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_08",
            "MIO Pin 8 Control",
            handles.bport1,
            0x720,
            4,
            read_32,
            bport1_ab_MIO_PIN_08_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_08.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_09",
            "MIO Pin 9 Control",
            handles.bport1,
            0x724,
            4,
            read_32,
            bport1_ab_MIO_PIN_09_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_09.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_10",
            "MIO Pin 10 Control",
            handles.bport1,
            0x728,
            4,
            read_32,
            bport1_ab_MIO_PIN_10_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_10.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_11",
            "MIO Pin 11 Control",
            handles.bport1,
            0x72c,
            4,
            read_32,
            bport1_ab_MIO_PIN_11_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_11.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_12",
            "MIO Pin 12 Control",
            handles.bport1,
            0x730,
            4,
            read_32,
            bport1_ab_MIO_PIN_12_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_12.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_13",
            "MIO Pin 13 Control",
            handles.bport1,
            0x734,
            4,
            read_32,
            bport1_ab_MIO_PIN_13_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_13.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_14",
            "MIO Pin 14 Control",
            handles.bport1,
            0x738,
            4,
            read_32,
            bport1_ab_MIO_PIN_14_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_14.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_15",
            "MIO Pin 15 Control",
            handles.bport1,
            0x73c,
            4,
            read_32,
            bport1_ab_MIO_PIN_15_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_15.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_16",
            "MIO Pin 16 Control",
            handles.bport1,
            0x740,
            4,
            read_32,
            bport1_ab_MIO_PIN_16_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_16.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_17",
            "MIO Pin 17 Control",
            handles.bport1,
            0x744,
            4,
            read_32,
            bport1_ab_MIO_PIN_17_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_17.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_18",
            "MIO Pin 18 Control",
            handles.bport1,
            0x748,
            4,
            read_32,
            bport1_ab_MIO_PIN_18_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_18.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_19",
            "MIO Pin 19 Control",
            handles.bport1,
            0x74c,
            4,
            read_32,
            bport1_ab_MIO_PIN_19_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_19.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_20",
            "MIO Pin 20 Control",
            handles.bport1,
            0x750,
            4,
            read_32,
            bport1_ab_MIO_PIN_20_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_20.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_21",
            "MIO Pin 21 Control",
            handles.bport1,
            0x754,
            4,
            read_32,
            bport1_ab_MIO_PIN_21_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_21.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_22",
            "MIO Pin 22 Control",
            handles.bport1,
            0x758,
            4,
            read_32,
            bport1_ab_MIO_PIN_22_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_22.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_23",
            "MIO Pin 23 Control",
            handles.bport1,
            0x75c,
            4,
            read_32,
            bport1_ab_MIO_PIN_23_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_23.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_24",
            "MIO Pin 24 Control",
            handles.bport1,
            0x760,
            4,
            read_32,
            bport1_ab_MIO_PIN_24_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_24.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_25",
            "MIO Pin 25 Control",
            handles.bport1,
            0x764,
            4,
            read_32,
            bport1_ab_MIO_PIN_25_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_25.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_26",
            "MIO Pin 26 Control",
            handles.bport1,
            0x768,
            4,
            read_32,
            bport1_ab_MIO_PIN_26_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_26.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_27",
            "MIO Pin 27 Control",
            handles.bport1,
            0x76c,
            4,
            read_32,
            bport1_ab_MIO_PIN_27_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_27.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_28",
            "MIO Pin 28 Control",
            handles.bport1,
            0x770,
            4,
            read_32,
            bport1_ab_MIO_PIN_28_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_28.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_29",
            "MIO Pin 29 Control",
            handles.bport1,
            0x774,
            4,
            read_32,
            bport1_ab_MIO_PIN_29_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_29.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_30",
            "MIO Pin 30 Control",
            handles.bport1,
            0x778,
            4,
            read_32,
            bport1_ab_MIO_PIN_30_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_30.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_31",
            "MIO Pin 31 Control",
            handles.bport1,
            0x77c,
            4,
            read_32,
            bport1_ab_MIO_PIN_31_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_31.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_32",
            "MIO Pin 32 Control",
            handles.bport1,
            0x780,
            4,
            read_32,
            bport1_ab_MIO_PIN_32_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_32.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_33",
            "MIO Pin 33 Control",
            handles.bport1,
            0x784,
            4,
            read_32,
            bport1_ab_MIO_PIN_33_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_33.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_34",
            "MIO Pin 34 Control",
            handles.bport1,
            0x788,
            4,
            read_32,
            bport1_ab_MIO_PIN_34_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_34.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_35",
            "MIO Pin 35 Control",
            handles.bport1,
            0x78c,
            4,
            read_32,
            bport1_ab_MIO_PIN_35_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_35.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_36",
            "MIO Pin 36 Control",
            handles.bport1,
            0x790,
            4,
            read_32,
            bport1_ab_MIO_PIN_36_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_36.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_37",
            "MIO Pin 37 Control",
            handles.bport1,
            0x794,
            4,
            read_32,
            bport1_ab_MIO_PIN_37_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_37.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_38",
            "MIO Pin 38 Control",
            handles.bport1,
            0x798,
            4,
            read_32,
            bport1_ab_MIO_PIN_38_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_38.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_39",
            "MIO Pin 39 Control",
            handles.bport1,
            0x79c,
            4,
            read_32,
            bport1_ab_MIO_PIN_39_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_39.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_40",
            "MIO Pin 40 Control",
            handles.bport1,
            0x7a0,
            4,
            read_32,
            bport1_ab_MIO_PIN_40_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_40.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_41",
            "MIO Pin 41 Control",
            handles.bport1,
            0x7a4,
            4,
            read_32,
            bport1_ab_MIO_PIN_41_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_41.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_42",
            "MIO Pin 42 Control",
            handles.bport1,
            0x7a8,
            4,
            read_32,
            bport1_ab_MIO_PIN_42_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_42.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_43",
            "MIO Pin 43 Control",
            handles.bport1,
            0x7ac,
            4,
            read_32,
            bport1_ab_MIO_PIN_43_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_43.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_44",
            "MIO Pin 44 Control",
            handles.bport1,
            0x7b0,
            4,
            read_32,
            bport1_ab_MIO_PIN_44_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_44.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_45",
            "MIO Pin 45 Control",
            handles.bport1,
            0x7b4,
            4,
            read_32,
            bport1_ab_MIO_PIN_45_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_45.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_46",
            "MIO Pin 46 Control",
            handles.bport1,
            0x7b8,
            4,
            read_32,
            bport1_ab_MIO_PIN_46_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_46.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_47",
            "MIO Pin 47 Control",
            handles.bport1,
            0x7bc,
            4,
            read_32,
            bport1_ab_MIO_PIN_47_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_47.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_48",
            "MIO Pin 48 Control",
            handles.bport1,
            0x7c0,
            4,
            read_32,
            bport1_ab_MIO_PIN_48_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_48.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_49",
            "MIO Pin 49 Control",
            handles.bport1,
            0x7c4,
            4,
            read_32,
            bport1_ab_MIO_PIN_49_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_49.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_50",
            "MIO Pin 50 Control",
            handles.bport1,
            0x7c8,
            4,
            read_32,
            bport1_ab_MIO_PIN_50_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_50.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_51",
            "MIO Pin 51 Control",
            handles.bport1,
            0x7cc,
            4,
            read_32,
            bport1_ab_MIO_PIN_51_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_51.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_52",
            "MIO Pin 52 Control",
            handles.bport1,
            0x7d0,
            4,
            read_32,
            bport1_ab_MIO_PIN_52_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_52.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_PIN_53",
            "MIO Pin 53 Control",
            handles.bport1,
            0x7d4,
            4,
            read_32,
            bport1_ab_MIO_PIN_53_maskWrite,
            view32,
            &(bport1_ab_data.MIO_PIN_53.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_LOOPBACK",
            "Loopback function within MIO",
            handles.bport1,
            0x804,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MIO_LOOPBACK.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_MST_TRI0",
            "MIO pin Tri-state Enables, 31:0",
            handles.bport1,
            0x80c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MIO_MST_TRI0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_MIO_MST_TRI1",
            "MIO pin Tri-state Enables, 53:32",
            handles.bport1,
            0x810,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.MIO_MST_TRI1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_SD0_WP_CD_SEL",
            "SDIO 0 WP CD select",
            handles.bport1,
            0x830,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.SD0_WP_CD_SEL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_SD1_WP_CD_SEL",
            "SDIO 1 WP CD select",
            handles.bport1,
            0x834,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.SD1_WP_CD_SEL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_LVL_SHFTR_EN",
            "Level Shifters Enable",
            handles.bport1,
            0x900,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.LVL_SHFTR_EN.value),
            True
        );
    }
    {
        registerHandle abOCM_CFG_reg = ppmCreateRegister(
            "ab_OCM_CFG",
            "OCM Address Mapping (user mode reset config)",
            handles.bport1,
            0x910,
            4,
            read_32,
            WriteOCM_CFG,
            view32,
            &(bport1_ab_data.OCM_CFG.value),
            True
        );

        ppmCreateRegisterField(abOCM_CFG_reg, "OCM3", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abOCM_CFG_reg, "OCM2", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abOCM_CFG_reg, "OCM1", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abOCM_CFG_reg, "OCM0", 0, 0, 1, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_Reserved",
            "Reserved",
            handles.bport1,
            0xa1c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.Reserved.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_GPIOB_CTRL",
            "PS IO Buffer Control",
            handles.bport1,
            0xb00,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.GPIOB_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_GPIOB_CFG_CMOS18",
            "MIO GPIOB CMOS 1.8V config",
            handles.bport1,
            0xb04,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.GPIOB_CFG_CMOS18.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_GPIOB_CFG_CMOS25",
            "MIO GPIOB CMOS 2.5V config",
            handles.bport1,
            0xb08,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.GPIOB_CFG_CMOS25.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_GPIOB_CFG_CMOS33",
            "MIO GPIOB CMOS 3.3V config",
            handles.bport1,
            0xb0c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.GPIOB_CFG_CMOS33.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_GPIOB_CFG_HSTL",
            "MIO GPIOB HSTL config",
            handles.bport1,
            0xb14,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.GPIOB_CFG_HSTL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_GPIOB_DRVR_BIAS_CTRL",
            "MIO GPIOB Driver Bias Control",
            handles.bport1,
            0xb18,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.GPIOB_DRVR_BIAS_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DDRIOB_ADDR0",
            "DDR IOB Config for A[14:0], CKE and DRST_B",
            handles.bport1,
            0xb40,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DDRIOB_ADDR0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DDRIOB_ADDR1",
            "DDR IOB Config for BA[2:0], ODT, CS_B, WE_B, RAS_B and CAS_B",
            handles.bport1,
            0xb44,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DDRIOB_ADDR1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DDRIOB_DATA0",
            "DDR IOB Config for Data 15:0",
            handles.bport1,
            0xb48,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DDRIOB_DATA0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DDRIOB_DATA1",
            "DDR IOB Config for Data 31:16",
            handles.bport1,
            0xb4c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DDRIOB_DATA1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DDRIOB_DIFF0",
            "DDR IOB Config for DQS 1:0",
            handles.bport1,
            0xb50,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DDRIOB_DIFF0.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DDRIOB_DIFF1",
            "DDR IOB Config for DQS 3:2",
            handles.bport1,
            0xb54,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DDRIOB_DIFF1.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DDRIOB_CLOCK",
            "DDR IOB Config for Clock Output",
            handles.bport1,
            0xb58,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DDRIOB_CLOCK.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DDRIOB_DRIVE_SLEW_ADDR",
            "Drive and Slew controls for Address and Command pins of the DDR Interface",
            handles.bport1,
            0xb5c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DDRIOB_DRIVE_SLEW_ADDR.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DDRIOB_DRIVE_SLEW_DATA",
            "Drive and Slew controls for DQ pins of the DDR Interface",
            handles.bport1,
            0xb60,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DDRIOB_DRIVE_SLEW_DATA.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DDRIOB_DRIVE_SLEW_DIFF",
            "Drive and Slew controls for DQS pins of the DDR Interface",
            handles.bport1,
            0xb64,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DDRIOB_DRIVE_SLEW_DIFF.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DDRIOB_DRIVE_SLEW_CLOCK",
            "Drive and Slew controls for Clock pins of the DDR Interface",
            handles.bport1,
            0xb68,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DDRIOB_DRIVE_SLEW_CLOCK.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DDRIOB_DDR_CTRL",
            "DDR IOB Buffer Control",
            handles.bport1,
            0xb6c,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DDRIOB_DDR_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DDRIOB_DCI_CTRL",
            "DDR IOB DCI Config",
            handles.bport1,
            0xb70,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DDRIOB_DCI_CTRL.value),
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_DDRIOB_DCI_STATUS",
            "DDR IO Buffer DCI Status",
            handles.bport1,
            0xb74,
            4,
            read_32,
            write_32,
            view32,
            &(bport1_ab_data.DDRIOB_DCI_STATUS.value),
            True
        );
    }


}

/////////////////////////////// Bus Master Ports ///////////////////////////////

static void installMasterPorts(void) {
    handles.mpOCM = ppmOpenAddressSpace("mpOCM");
    if (!handles.mpOCM) {
        bhmMessage("E", "PPM_MPNC", "Could not connect port 'mpOCM'");
    }
    handles.mpDDR = ppmOpenAddressSpace("mpDDR");
    if (!handles.mpDDR) {
        bhmMessage("E", "PPM_MPNC", "Could not connect port 'mpDDR'");
    }
}

PPM_NET_CB(reset_resetNet) {
    if(value != 0 ) {
        bport1_ab_data.DDRIOB_DCI_STATUS.value = (Uns32)(bport1_ab_data.DDRIOB_DCI_STATUS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DDRIOB_DCI_CTRL.value = (Uns32)(bport1_ab_data.DDRIOB_DCI_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000020));
        bport1_ab_data.DDRIOB_DDR_CTRL.value = (Uns32)(bport1_ab_data.DDRIOB_DDR_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DDRIOB_DRIVE_SLEW_CLOCK.value = (Uns32)(bport1_ab_data.DDRIOB_DRIVE_SLEW_CLOCK.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DDRIOB_DRIVE_SLEW_DIFF.value = (Uns32)(bport1_ab_data.DDRIOB_DRIVE_SLEW_DIFF.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DDRIOB_DRIVE_SLEW_DATA.value = (Uns32)(bport1_ab_data.DDRIOB_DRIVE_SLEW_DATA.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DDRIOB_DRIVE_SLEW_ADDR.value = (Uns32)(bport1_ab_data.DDRIOB_DRIVE_SLEW_ADDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DDRIOB_CLOCK.value = (Uns32)(bport1_ab_data.DDRIOB_CLOCK.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000800));
        bport1_ab_data.DDRIOB_DIFF1.value = (Uns32)(bport1_ab_data.DDRIOB_DIFF1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000800));
        bport1_ab_data.DDRIOB_DIFF0.value = (Uns32)(bport1_ab_data.DDRIOB_DIFF0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000800));
        bport1_ab_data.DDRIOB_DATA1.value = (Uns32)(bport1_ab_data.DDRIOB_DATA1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000800));
        bport1_ab_data.DDRIOB_DATA0.value = (Uns32)(bport1_ab_data.DDRIOB_DATA0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000800));
        bport1_ab_data.DDRIOB_ADDR1.value = (Uns32)(bport1_ab_data.DDRIOB_ADDR1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000800));
        bport1_ab_data.DDRIOB_ADDR0.value = (Uns32)(bport1_ab_data.DDRIOB_ADDR0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000800));
        bport1_ab_data.GPIOB_DRVR_BIAS_CTRL.value = (Uns32)(bport1_ab_data.GPIOB_DRVR_BIAS_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPIOB_CFG_HSTL.value = (Uns32)(bport1_ab_data.GPIOB_CFG_HSTL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPIOB_CFG_CMOS33.value = (Uns32)(bport1_ab_data.GPIOB_CFG_CMOS33.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPIOB_CFG_CMOS25.value = (Uns32)(bport1_ab_data.GPIOB_CFG_CMOS25.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPIOB_CFG_CMOS18.value = (Uns32)(bport1_ab_data.GPIOB_CFG_CMOS18.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPIOB_CTRL.value = (Uns32)(bport1_ab_data.GPIOB_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.Reserved.value = (Uns32)(bport1_ab_data.Reserved.value & ~(0xffffffff)) | ((0xffffffff) & (0x00010101));
        bport1_ab_data.OCM_CFG.value = (Uns32)(bport1_ab_data.OCM_CFG.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000000f));
        bport1_ab_data.LVL_SHFTR_EN.value = (Uns32)(bport1_ab_data.LVL_SHFTR_EN.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SD1_WP_CD_SEL.value = (Uns32)(bport1_ab_data.SD1_WP_CD_SEL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SD0_WP_CD_SEL.value = (Uns32)(bport1_ab_data.SD0_WP_CD_SEL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MIO_MST_TRI1.value = (Uns32)(bport1_ab_data.MIO_MST_TRI1.value & ~(0xffffffff)) | ((0xffffffff) & (0x003FFFFF));
        bport1_ab_data.MIO_MST_TRI0.value = (Uns32)(bport1_ab_data.MIO_MST_TRI0.value & ~(0xffffffff)) | ((0xffffffff) & (0xFFFFFFFF));
        bport1_ab_data.MIO_LOOPBACK.value = (Uns32)(bport1_ab_data.MIO_LOOPBACK.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MIO_PIN_53.value = (Uns32)(bport1_ab_data.MIO_PIN_53.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_52.value = (Uns32)(bport1_ab_data.MIO_PIN_52.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_51.value = (Uns32)(bport1_ab_data.MIO_PIN_51.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_50.value = (Uns32)(bport1_ab_data.MIO_PIN_50.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_49.value = (Uns32)(bport1_ab_data.MIO_PIN_49.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_48.value = (Uns32)(bport1_ab_data.MIO_PIN_48.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_47.value = (Uns32)(bport1_ab_data.MIO_PIN_47.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_46.value = (Uns32)(bport1_ab_data.MIO_PIN_46.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_45.value = (Uns32)(bport1_ab_data.MIO_PIN_45.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_44.value = (Uns32)(bport1_ab_data.MIO_PIN_44.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_43.value = (Uns32)(bport1_ab_data.MIO_PIN_43.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_42.value = (Uns32)(bport1_ab_data.MIO_PIN_42.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_41.value = (Uns32)(bport1_ab_data.MIO_PIN_41.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_40.value = (Uns32)(bport1_ab_data.MIO_PIN_40.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_39.value = (Uns32)(bport1_ab_data.MIO_PIN_39.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_38.value = (Uns32)(bport1_ab_data.MIO_PIN_38.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_37.value = (Uns32)(bport1_ab_data.MIO_PIN_37.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_36.value = (Uns32)(bport1_ab_data.MIO_PIN_36.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_35.value = (Uns32)(bport1_ab_data.MIO_PIN_35.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_34.value = (Uns32)(bport1_ab_data.MIO_PIN_34.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_33.value = (Uns32)(bport1_ab_data.MIO_PIN_33.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_32.value = (Uns32)(bport1_ab_data.MIO_PIN_32.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_31.value = (Uns32)(bport1_ab_data.MIO_PIN_31.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_30.value = (Uns32)(bport1_ab_data.MIO_PIN_30.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_29.value = (Uns32)(bport1_ab_data.MIO_PIN_29.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_28.value = (Uns32)(bport1_ab_data.MIO_PIN_28.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_27.value = (Uns32)(bport1_ab_data.MIO_PIN_27.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_26.value = (Uns32)(bport1_ab_data.MIO_PIN_26.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_25.value = (Uns32)(bport1_ab_data.MIO_PIN_25.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_24.value = (Uns32)(bport1_ab_data.MIO_PIN_24.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_23.value = (Uns32)(bport1_ab_data.MIO_PIN_23.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_22.value = (Uns32)(bport1_ab_data.MIO_PIN_22.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_21.value = (Uns32)(bport1_ab_data.MIO_PIN_21.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_20.value = (Uns32)(bport1_ab_data.MIO_PIN_20.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_19.value = (Uns32)(bport1_ab_data.MIO_PIN_19.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_18.value = (Uns32)(bport1_ab_data.MIO_PIN_18.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_17.value = (Uns32)(bport1_ab_data.MIO_PIN_17.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_16.value = (Uns32)(bport1_ab_data.MIO_PIN_16.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_15.value = (Uns32)(bport1_ab_data.MIO_PIN_15.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_14.value = (Uns32)(bport1_ab_data.MIO_PIN_14.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_13.value = (Uns32)(bport1_ab_data.MIO_PIN_13.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_12.value = (Uns32)(bport1_ab_data.MIO_PIN_12.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_11.value = (Uns32)(bport1_ab_data.MIO_PIN_11.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_10.value = (Uns32)(bport1_ab_data.MIO_PIN_10.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_09.value = (Uns32)(bport1_ab_data.MIO_PIN_09.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_08.value = (Uns32)(bport1_ab_data.MIO_PIN_08.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000601));
        bport1_ab_data.MIO_PIN_07.value = (Uns32)(bport1_ab_data.MIO_PIN_07.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000601));
        bport1_ab_data.MIO_PIN_06.value = (Uns32)(bport1_ab_data.MIO_PIN_06.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000601));
        bport1_ab_data.MIO_PIN_05.value = (Uns32)(bport1_ab_data.MIO_PIN_05.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000601));
        bport1_ab_data.MIO_PIN_04.value = (Uns32)(bport1_ab_data.MIO_PIN_04.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000601));
        bport1_ab_data.MIO_PIN_03.value = (Uns32)(bport1_ab_data.MIO_PIN_03.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000601));
        bport1_ab_data.MIO_PIN_02.value = (Uns32)(bport1_ab_data.MIO_PIN_02.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000601));
        bport1_ab_data.MIO_PIN_01.value = (Uns32)(bport1_ab_data.MIO_PIN_01.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.MIO_PIN_00.value = (Uns32)(bport1_ab_data.MIO_PIN_00.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001601));
        bport1_ab_data.DDR_DFI_STATUS.value = (Uns32)(bport1_ab_data.DDR_DFI_STATUS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DDR_URGENT_SEL.value = (Uns32)(bport1_ab_data.DDR_URGENT_SEL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DDR_CMD_STA.value = (Uns32)(bport1_ab_data.DDR_CMD_STA.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DDR_REF_START.value = (Uns32)(bport1_ab_data.DDR_REF_START.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DDR_CAL_START.value = (Uns32)(bport1_ab_data.DDR_CAL_START.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DDR_URGENT.value = (Uns32)(bport1_ab_data.DDR_URGENT.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PSS_IDCODE.value = (Uns32)(bport1_ab_data.PSS_IDCODE.value & ~(0xffffffff)) | ((0xffffffff) & (0x13747093));
        bport1_ab_data.TZ_FPGA_AFI.value = (Uns32)(bport1_ab_data.TZ_FPGA_AFI.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TZ_FPGA_M.value = (Uns32)(bport1_ab_data.TZ_FPGA_M.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TZ_USB.value = (Uns32)(bport1_ab_data.TZ_USB.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TZ_SDIO.value = (Uns32)(bport1_ab_data.TZ_SDIO.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TZ_GEM.value = (Uns32)(bport1_ab_data.TZ_GEM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TZ_DMA_PERIPH_NS.value = (Uns32)(bport1_ab_data.TZ_DMA_PERIPH_NS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TZ_DMA_IRQ_NS.value = (Uns32)(bport1_ab_data.TZ_DMA_IRQ_NS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TZ_DMA_NS.value = (Uns32)(bport1_ab_data.TZ_DMA_NS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TZ_DDR_RAM.value = (Uns32)(bport1_ab_data.TZ_DDR_RAM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TZ_OCM.value = (Uns32)(bport1_ab_data.TZ_OCM.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TZ_OCM_RAM1.value = (Uns32)(bport1_ab_data.TZ_OCM_RAM1.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TZ_OCM_RAM0.value = (Uns32)(bport1_ab_data.TZ_OCM_RAM0.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.WDT_CLK_SEL.value = (Uns32)(bport1_ab_data.WDT_CLK_SEL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.APU_CTRL.value = (Uns32)(bport1_ab_data.APU_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.BOOT_MODE.value = (Uns32)(bport1_ab_data.BOOT_MODE.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.REBOOT_STATUS.value = (Uns32)(bport1_ab_data.REBOOT_STATUS.value & ~(0xffffffff)) | ((0xffffffff) & (0x00400000));
        bport1_ab_data.RS_AWDT_CTRL.value = (Uns32)(bport1_ab_data.RS_AWDT_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.A9_CPU_RST_CTRL.value = (Uns32)(bport1_ab_data.A9_CPU_RST_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.FPGA_RST_CTRL.value = (Uns32)(bport1_ab_data.FPGA_RST_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x01F33F0F));
        bport1_ab_data.OCM_RST_CTRL.value = (Uns32)(bport1_ab_data.OCM_RST_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SMC_RST_CTRL.value = (Uns32)(bport1_ab_data.SMC_RST_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.LQSPI_RST_CTRL.value = (Uns32)(bport1_ab_data.LQSPI_RST_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GPIO_RST_CTRL.value = (Uns32)(bport1_ab_data.GPIO_RST_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.UART_RST_CTRL.value = (Uns32)(bport1_ab_data.UART_RST_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.I2C_RST_CTRL.value = (Uns32)(bport1_ab_data.I2C_RST_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CAN_RST_CTRL.value = (Uns32)(bport1_ab_data.CAN_RST_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SPI_RST_CTRL.value = (Uns32)(bport1_ab_data.SPI_RST_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SDIO_RST_CTRL.value = (Uns32)(bport1_ab_data.SDIO_RST_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.GEM_RST_CTRL.value = (Uns32)(bport1_ab_data.GEM_RST_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.USB_RST_CTRL.value = (Uns32)(bport1_ab_data.USB_RST_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DMAC_RST_CTRL.value = (Uns32)(bport1_ab_data.DMAC_RST_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TOPSW_RST_CTRL.value = (Uns32)(bport1_ab_data.TOPSW_RST_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.DDR_RST_CTRL.value = (Uns32)(bport1_ab_data.DDR_RST_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PSS_RST_CTRL.value = (Uns32)(bport1_ab_data.PSS_RST_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CLK_621_TRUE.value = (Uns32)(bport1_ab_data.CLK_621_TRUE.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000001));
        bport1_ab_data.FPGA3_THR_STA.value = (Uns32)(bport1_ab_data.FPGA3_THR_STA.value & ~(0xffffffff)) | ((0xffffffff) & (0x00010000));
        bport1_ab_data.FPGA3_THR_CNT.value = (Uns32)(bport1_ab_data.FPGA3_THR_CNT.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.FPGA3_THR_CTRL.value = (Uns32)(bport1_ab_data.FPGA3_THR_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.FPGA3_CLK_CTRL.value = (Uns32)(bport1_ab_data.FPGA3_CLK_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00101800));
        bport1_ab_data.FPGA2_THR_STA.value = (Uns32)(bport1_ab_data.FPGA2_THR_STA.value & ~(0xffffffff)) | ((0xffffffff) & (0x00010000));
        bport1_ab_data.FPGA2_THR_CNT.value = (Uns32)(bport1_ab_data.FPGA2_THR_CNT.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.FPGA2_THR_CTRL.value = (Uns32)(bport1_ab_data.FPGA2_THR_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.FPGA2_CLK_CTRL.value = (Uns32)(bport1_ab_data.FPGA2_CLK_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00101800));
        bport1_ab_data.FPGA1_THR_STA.value = (Uns32)(bport1_ab_data.FPGA1_THR_STA.value & ~(0xffffffff)) | ((0xffffffff) & (0x00010000));
        bport1_ab_data.FPGA1_THR_CNT.value = (Uns32)(bport1_ab_data.FPGA1_THR_CNT.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.FPGA1_THR_CTRL.value = (Uns32)(bport1_ab_data.FPGA1_THR_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.FPGA1_CLK_CTRL.value = (Uns32)(bport1_ab_data.FPGA1_CLK_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00101800));
        bport1_ab_data.FPGA0_THR_STA.value = (Uns32)(bport1_ab_data.FPGA0_THR_STA.value & ~(0xffffffff)) | ((0xffffffff) & (0x00010000));
        bport1_ab_data.FPGA0_THR_CNT.value = (Uns32)(bport1_ab_data.FPGA0_THR_CNT.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.FPGA0_THR_CTRL.value = (Uns32)(bport1_ab_data.FPGA0_THR_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.FPGA0_CLK_CTRL.value = (Uns32)(bport1_ab_data.FPGA0_CLK_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00101800));
        bport1_ab_data.TOPSW_CLK_CTRL.value = (Uns32)(bport1_ab_data.TOPSW_CLK_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.PCAP_CLK_CTRL.value = (Uns32)(bport1_ab_data.PCAP_CLK_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000F01));
        bport1_ab_data.DBG_CLK_CTRL.value = (Uns32)(bport1_ab_data.DBG_CLK_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000F03));
        bport1_ab_data.CAN_MIOCLK_CTRL.value = (Uns32)(bport1_ab_data.CAN_MIOCLK_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.CAN_CLK_CTRL.value = (Uns32)(bport1_ab_data.CAN_CLK_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00501903));
        bport1_ab_data.SPI_CLK_CTRL.value = (Uns32)(bport1_ab_data.SPI_CLK_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00003F03));
        bport1_ab_data.UART_CLK_CTRL.value = (Uns32)(bport1_ab_data.UART_CLK_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00003F03));
        bport1_ab_data.SDIO_CLK_CTRL.value = (Uns32)(bport1_ab_data.SDIO_CLK_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00001E03));
        bport1_ab_data.LQSPI_CLK_CTRL.value = (Uns32)(bport1_ab_data.LQSPI_CLK_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00002821));
        bport1_ab_data.SMC_CLK_CTRL.value = (Uns32)(bport1_ab_data.SMC_CLK_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00003C21));
        bport1_ab_data.GEM1_CLK_CTRL.value = (Uns32)(bport1_ab_data.GEM1_CLK_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00003C01));
        bport1_ab_data.GEM0_CLK_CTRL.value = (Uns32)(bport1_ab_data.GEM0_CLK_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00003C01));
        bport1_ab_data.GEM1_RCLK_CTRL.value = (Uns32)(bport1_ab_data.GEM1_RCLK_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000001));
        bport1_ab_data.GEM0_RCLK_CTRL.value = (Uns32)(bport1_ab_data.GEM0_RCLK_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000001));
        bport1_ab_data.USB1_CLK_CTRL.value = (Uns32)(bport1_ab_data.USB1_CLK_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00101941));
        bport1_ab_data.USB0_CLK_CTRL.value = (Uns32)(bport1_ab_data.USB0_CLK_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00101941));
        bport1_ab_data.APER_CLK_CTRL.value = (Uns32)(bport1_ab_data.APER_CLK_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x01FFCCCD));
        bport1_ab_data.DCI_CLK_CTRL.value = (Uns32)(bport1_ab_data.DCI_CLK_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x01E03201));
        bport1_ab_data.DDR_CLK_CTRL.value = (Uns32)(bport1_ab_data.DDR_CLK_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x18400003));
        bport1_ab_data.ARM_CLK_CTRL.value = (Uns32)(bport1_ab_data.ARM_CLK_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x1F000400));
        bport1_ab_data.IO_PLL_CFG.value = (Uns32)(bport1_ab_data.IO_PLL_CFG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00177EA0));
        bport1_ab_data.DDR_PLL_CFG.value = (Uns32)(bport1_ab_data.DDR_PLL_CFG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00177EA0));
        bport1_ab_data.ARM_PLL_CFG.value = (Uns32)(bport1_ab_data.ARM_PLL_CFG.value & ~(0xffffffff)) | ((0xffffffff) & (0x00177EA0));
        bport1_ab_data.PLL_STATUS.value = (Uns32)(bport1_ab_data.PLL_STATUS.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000003F));
        bport1_ab_data.IO_PLL_CTRL.value = (Uns32)(bport1_ab_data.IO_PLL_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x0001A008));
        bport1_ab_data.DDR_PLL_CTRL.value = (Uns32)(bport1_ab_data.DDR_PLL_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x0001A008));
        bport1_ab_data.ARM_PLL_CTRL.value = (Uns32)(bport1_ab_data.ARM_PLL_CTRL.value & ~(0xffffffff)) | ((0xffffffff) & (0x0001A008));
        bport1_ab_data.SLCR_LOCKSTA.value = (Uns32)(bport1_ab_data.SLCR_LOCKSTA.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000001));
        bport1_ab_data.SLCR_UNLOCK.value = (Uns32)(bport1_ab_data.SLCR_UNLOCK.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SLCR_LOCK.value = (Uns32)(bport1_ab_data.SLCR_LOCK.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.SCL.value = (Uns32)(bport1_ab_data.SCL.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Zynq 7000 Platform System Level Control Registers (SLCR)");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "This model implements the full set of registers. Only behavior required for processor reset control is included.");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "Zynq-7000 TRM (https://www.xilinx.com/support/documentation/user_guides/ug585-Zynq-7000-TRM.pdf)");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    installMasterPorts();
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

