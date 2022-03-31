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

#ifndef PSE_IGEN_H
#define PSE_IGEN_H                      

#ifdef _PSE_
#    include "peripheral/impTypes.h"
#    include "peripheral/bhm.h"
#    include "peripheral/bhmHttp.h"
#    include "peripheral/ppm.h"
#else
#    include "hostapi/impTypes.h"
#endif

#ifdef _PSE_
//////////////////////////////////// Externs ///////////////////////////////////

extern Uns32 diagnosticLevel;


/////////////////////////// Dynamic Diagnostic Macros //////////////////////////

// Bottom two bits of word used for PSE diagnostics
#define PSE_DIAG_LOW                    (BHM_DIAG_MASK_LOW(diagnosticLevel))
#define PSE_DIAG_MEDIUM                 (BHM_DIAG_MASK_MEDIUM(diagnosticLevel))

#define PSE_DIAG_HIGH                   (BHM_DIAG_MASK_HIGH(diagnosticLevel))
// Next two bits of word used for PSE semihost/intercept library diagnostics
#define PSE_DIAG_SEMIHOST               (BHM_DIAG_MASK_SEMIHOST(diagnosticLevel))

#endif
/////////////////////////// Register data declaration //////////////////////////

typedef struct bport1_ab_dataS { 
    union { 
        Uns32 value;
        struct {
            Uns32 LOCK : 1;
        } bits;
    } SCL;
    union { 
        Uns32 value;
    } SLCR_LOCK;
    union { 
        Uns32 value;
    } SLCR_UNLOCK;
    union { 
        Uns32 value;
    } SLCR_LOCKSTA;
    union { 
        Uns32 value;
        struct {
            Uns32 PLL_RESET : 1;
            Uns32 PLL_PWRDWN : 1;
            Uns32 __pad2 : 1;
            Uns32 PLL_BYPASS_QUAL : 1;
            Uns32 PLL_BYPASS_FORCE : 1;
            Uns32 __pad5 : 7;
            Uns32 PLL_FDIV : 7;
        } bits;
    } ARM_PLL_CTRL;
    union { 
        Uns32 value;
    } DDR_PLL_CTRL;
    union { 
        Uns32 value;
    } IO_PLL_CTRL;
    union { 
        Uns32 value;
    } PLL_STATUS;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 4;
            Uns32 PLL_RES : 4;
            Uns32 PLL_CP : 4;
            Uns32 LOC_CNT : 10;
        } bits;
    } ARM_PLL_CFG;
    union { 
        Uns32 value;
    } DDR_PLL_CFG;
    union { 
        Uns32 value;
    } IO_PLL_CFG;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 4;
            Uns32 SRCSEL : 2;
            Uns32 __pad6 : 2;
            Uns32 DIVISOR : 6;
            Uns32 __pad14 : 10;
            Uns32 CPU_4OR4XCLKACT : 1;
            Uns32 CPU_6OR3XCLKACT : 1;
            Uns32 CPU_2XCLKACT : 1;
            Uns32 CPU_1XCLKACT : 1;
            Uns32 CPU_PERICLKACT : 1;
        } bits;
    } ARM_CLK_CTRL;
    union { 
        Uns32 value;
    } DDR_CLK_CTRL;
    union { 
        Uns32 value;
    } DCI_CLK_CTRL;
    union { 
        Uns32 value;
    } APER_CLK_CTRL;
    union { 
        Uns32 value;
    } USB0_CLK_CTRL;
    union { 
        Uns32 value;
    } USB1_CLK_CTRL;
    union { 
        Uns32 value;
    } GEM0_RCLK_CTRL;
    union { 
        Uns32 value;
    } GEM1_RCLK_CTRL;
    union { 
        Uns32 value;
    } GEM0_CLK_CTRL;
    union { 
        Uns32 value;
    } GEM1_CLK_CTRL;
    union { 
        Uns32 value;
    } SMC_CLK_CTRL;
    union { 
        Uns32 value;
    } LQSPI_CLK_CTRL;
    union { 
        Uns32 value;
    } SDIO_CLK_CTRL;
    union { 
        Uns32 value;
    } UART_CLK_CTRL;
    union { 
        Uns32 value;
    } SPI_CLK_CTRL;
    union { 
        Uns32 value;
    } CAN_CLK_CTRL;
    union { 
        Uns32 value;
    } CAN_MIOCLK_CTRL;
    union { 
        Uns32 value;
    } DBG_CLK_CTRL;
    union { 
        Uns32 value;
    } PCAP_CLK_CTRL;
    union { 
        Uns32 value;
    } TOPSW_CLK_CTRL;
    union { 
        Uns32 value;
    } FPGA0_CLK_CTRL;
    union { 
        Uns32 value;
    } FPGA0_THR_CTRL;
    union { 
        Uns32 value;
    } FPGA0_THR_CNT;
    union { 
        Uns32 value;
    } FPGA0_THR_STA;
    union { 
        Uns32 value;
    } FPGA1_CLK_CTRL;
    union { 
        Uns32 value;
    } FPGA1_THR_CTRL;
    union { 
        Uns32 value;
    } FPGA1_THR_CNT;
    union { 
        Uns32 value;
    } FPGA1_THR_STA;
    union { 
        Uns32 value;
    } FPGA2_CLK_CTRL;
    union { 
        Uns32 value;
    } FPGA2_THR_CTRL;
    union { 
        Uns32 value;
    } FPGA2_THR_CNT;
    union { 
        Uns32 value;
    } FPGA2_THR_STA;
    union { 
        Uns32 value;
    } FPGA3_CLK_CTRL;
    union { 
        Uns32 value;
    } FPGA3_THR_CTRL;
    union { 
        Uns32 value;
    } FPGA3_THR_CNT;
    union { 
        Uns32 value;
    } FPGA3_THR_STA;
    union { 
        Uns32 value;
        struct {
            Uns32 CLK_621 : 1;
        } bits;
    } CLK_621_TRUE;
    union { 
        Uns32 value;
    } PSS_RST_CTRL;
    union { 
        Uns32 value;
    } DDR_RST_CTRL;
    union { 
        Uns32 value;
    } TOPSW_RST_CTRL;
    union { 
        Uns32 value;
    } DMAC_RST_CTRL;
    union { 
        Uns32 value;
    } USB_RST_CTRL;
    union { 
        Uns32 value;
    } GEM_RST_CTRL;
    union { 
        Uns32 value;
    } SDIO_RST_CTRL;
    union { 
        Uns32 value;
    } SPI_RST_CTRL;
    union { 
        Uns32 value;
    } CAN_RST_CTRL;
    union { 
        Uns32 value;
    } I2C_RST_CTRL;
    union { 
        Uns32 value;
    } UART_RST_CTRL;
    union { 
        Uns32 value;
    } GPIO_RST_CTRL;
    union { 
        Uns32 value;
    } LQSPI_RST_CTRL;
    union { 
        Uns32 value;
    } SMC_RST_CTRL;
    union { 
        Uns32 value;
    } OCM_RST_CTRL;
    union { 
        Uns32 value;
    } FPGA_RST_CTRL;
    union { 
        Uns32 value;
        struct {
            Uns32 A9_RST0 : 1;
            Uns32 A9_RST1 : 1;
            Uns32 __pad2 : 2;
            Uns32 A9_CLKSTOP0 : 1;
            Uns32 A9_CLKSTOP1 : 1;
            Uns32 __pad6 : 2;
            Uns32 PERI_RST : 1;
        } bits;
    } A9_CPU_RST_CTRL;
    union { 
        Uns32 value;
    } RS_AWDT_CTRL;
    union { 
        Uns32 value;
    } REBOOT_STATUS;
    union { 
        Uns32 value;
    } BOOT_MODE;
    union { 
        Uns32 value;
    } APU_CTRL;
    union { 
        Uns32 value;
    } WDT_CLK_SEL;
    union { 
        Uns32 value;
    } TZ_OCM_RAM0;
    union { 
        Uns32 value;
    } TZ_OCM_RAM1;
    union { 
        Uns32 value;
    } TZ_OCM;
    union { 
        Uns32 value;
    } TZ_DDR_RAM;
    union { 
        Uns32 value;
    } TZ_DMA_NS;
    union { 
        Uns32 value;
    } TZ_DMA_IRQ_NS;
    union { 
        Uns32 value;
    } TZ_DMA_PERIPH_NS;
    union { 
        Uns32 value;
    } TZ_GEM;
    union { 
        Uns32 value;
    } TZ_SDIO;
    union { 
        Uns32 value;
    } TZ_USB;
    union { 
        Uns32 value;
    } TZ_FPGA_M;
    union { 
        Uns32 value;
    } TZ_FPGA_AFI;
    union { 
        Uns32 value;
        struct {
            Uns32 __pad0 : 1;
            Uns32 MAN : 11;
            Uns32 DEV : 5;
            Uns32 SUB : 4;
            Uns32 FAM : 7;
            Uns32 REV : 4;
        } bits;
    } PSS_IDCODE;
    union { 
        Uns32 value;
    } DDR_URGENT;
    union { 
        Uns32 value;
    } DDR_CAL_START;
    union { 
        Uns32 value;
    } DDR_REF_START;
    union { 
        Uns32 value;
    } DDR_CMD_STA;
    union { 
        Uns32 value;
    } DDR_URGENT_SEL;
    union { 
        Uns32 value;
    } DDR_DFI_STATUS;
    union { 
        Uns32 value;
    } MIO_PIN_00;
    union { 
        Uns32 value;
    } MIO_PIN_01;
    union { 
        Uns32 value;
    } MIO_PIN_02;
    union { 
        Uns32 value;
    } MIO_PIN_03;
    union { 
        Uns32 value;
    } MIO_PIN_04;
    union { 
        Uns32 value;
    } MIO_PIN_05;
    union { 
        Uns32 value;
    } MIO_PIN_06;
    union { 
        Uns32 value;
    } MIO_PIN_07;
    union { 
        Uns32 value;
    } MIO_PIN_08;
    union { 
        Uns32 value;
    } MIO_PIN_09;
    union { 
        Uns32 value;
    } MIO_PIN_10;
    union { 
        Uns32 value;
    } MIO_PIN_11;
    union { 
        Uns32 value;
    } MIO_PIN_12;
    union { 
        Uns32 value;
    } MIO_PIN_13;
    union { 
        Uns32 value;
    } MIO_PIN_14;
    union { 
        Uns32 value;
    } MIO_PIN_15;
    union { 
        Uns32 value;
    } MIO_PIN_16;
    union { 
        Uns32 value;
    } MIO_PIN_17;
    union { 
        Uns32 value;
    } MIO_PIN_18;
    union { 
        Uns32 value;
    } MIO_PIN_19;
    union { 
        Uns32 value;
    } MIO_PIN_20;
    union { 
        Uns32 value;
    } MIO_PIN_21;
    union { 
        Uns32 value;
    } MIO_PIN_22;
    union { 
        Uns32 value;
    } MIO_PIN_23;
    union { 
        Uns32 value;
    } MIO_PIN_24;
    union { 
        Uns32 value;
    } MIO_PIN_25;
    union { 
        Uns32 value;
    } MIO_PIN_26;
    union { 
        Uns32 value;
    } MIO_PIN_27;
    union { 
        Uns32 value;
    } MIO_PIN_28;
    union { 
        Uns32 value;
    } MIO_PIN_29;
    union { 
        Uns32 value;
    } MIO_PIN_30;
    union { 
        Uns32 value;
    } MIO_PIN_31;
    union { 
        Uns32 value;
    } MIO_PIN_32;
    union { 
        Uns32 value;
    } MIO_PIN_33;
    union { 
        Uns32 value;
    } MIO_PIN_34;
    union { 
        Uns32 value;
    } MIO_PIN_35;
    union { 
        Uns32 value;
    } MIO_PIN_36;
    union { 
        Uns32 value;
    } MIO_PIN_37;
    union { 
        Uns32 value;
    } MIO_PIN_38;
    union { 
        Uns32 value;
    } MIO_PIN_39;
    union { 
        Uns32 value;
    } MIO_PIN_40;
    union { 
        Uns32 value;
    } MIO_PIN_41;
    union { 
        Uns32 value;
    } MIO_PIN_42;
    union { 
        Uns32 value;
    } MIO_PIN_43;
    union { 
        Uns32 value;
    } MIO_PIN_44;
    union { 
        Uns32 value;
    } MIO_PIN_45;
    union { 
        Uns32 value;
    } MIO_PIN_46;
    union { 
        Uns32 value;
    } MIO_PIN_47;
    union { 
        Uns32 value;
    } MIO_PIN_48;
    union { 
        Uns32 value;
    } MIO_PIN_49;
    union { 
        Uns32 value;
    } MIO_PIN_50;
    union { 
        Uns32 value;
    } MIO_PIN_51;
    union { 
        Uns32 value;
    } MIO_PIN_52;
    union { 
        Uns32 value;
    } MIO_PIN_53;
    union { 
        Uns32 value;
    } MIO_LOOPBACK;
    union { 
        Uns32 value;
    } MIO_MST_TRI0;
    union { 
        Uns32 value;
    } MIO_MST_TRI1;
    union { 
        Uns32 value;
    } SD0_WP_CD_SEL;
    union { 
        Uns32 value;
    } SD1_WP_CD_SEL;
    union { 
        Uns32 value;
    } LVL_SHFTR_EN;
    union { 
        Uns32 value;
        struct {
            Uns32 OCM0 : 1;
            Uns32 OCM1 : 1;
            Uns32 OCM2 : 1;
            Uns32 OCM3 : 1;
        } bits;
    } OCM_CFG;
    union { 
        Uns32 value;
    } Reserved;
    union { 
        Uns32 value;
    } GPIOB_CTRL;
    union { 
        Uns32 value;
    } GPIOB_CFG_CMOS18;
    union { 
        Uns32 value;
    } GPIOB_CFG_CMOS25;
    union { 
        Uns32 value;
    } GPIOB_CFG_CMOS33;
    union { 
        Uns32 value;
    } GPIOB_CFG_HSTL;
    union { 
        Uns32 value;
    } GPIOB_DRVR_BIAS_CTRL;
    union { 
        Uns32 value;
    } DDRIOB_ADDR0;
    union { 
        Uns32 value;
    } DDRIOB_ADDR1;
    union { 
        Uns32 value;
    } DDRIOB_DATA0;
    union { 
        Uns32 value;
    } DDRIOB_DATA1;
    union { 
        Uns32 value;
    } DDRIOB_DIFF0;
    union { 
        Uns32 value;
    } DDRIOB_DIFF1;
    union { 
        Uns32 value;
    } DDRIOB_CLOCK;
    union { 
        Uns32 value;
    } DDRIOB_DRIVE_SLEW_ADDR;
    union { 
        Uns32 value;
    } DDRIOB_DRIVE_SLEW_DATA;
    union { 
        Uns32 value;
    } DDRIOB_DRIVE_SLEW_DIFF;
    union { 
        Uns32 value;
    } DDRIOB_DRIVE_SLEW_CLOCK;
    union { 
        Uns32 value;
    } DDRIOB_DDR_CTRL;
    union { 
        Uns32 value;
    } DDRIOB_DCI_CTRL;
    union { 
        Uns32 value;
    } DDRIOB_DCI_STATUS;
} bport1_ab_dataT, *bport1_ab_dataTP;

#ifdef _PSE_
/////////////////////////////// Port Declarations //////////////////////////////

extern bport1_ab_dataT bport1_ab_data;

///////////////////////////////// Port handles /////////////////////////////////

typedef struct handlesS {
    ppmAddressSpaceHandle mpOCM;
    ppmAddressSpaceHandle mpDDR;
    void                 *bport1;
    void                 *spOCMDDR;
    ppmNetHandle          A9_RST0;
    ppmNetHandle          A9_RST1;
    ppmNetHandle          ARM1Deration;
    ppmNetHandle          ARM0Deration;
} handlesT, *handlesTP;

extern handlesT handles;

////////////////////////////// Callback prototypes /////////////////////////////

PPM_REG_READ_CB(ReadA9_CPU_RST_CTRL);
PPM_REG_READ_CB(ReadARM_CLK_CTRL);
PPM_REG_READ_CB(ReadARM_PLL_CFG);
PPM_REG_READ_CB(ReadARM_PLL_CTRL);
PPM_REG_READ_CB(ReadSLCR_LOCK);
PPM_REG_READ_CB(ReadSLCR_LOCKSTA);
PPM_REG_READ_CB(ReadSLCR_UNLOCK);
PPM_REG_WRITE_CB(WriteA9_CPU_RST_CTRL);
PPM_REG_WRITE_CB(WriteAPU_CTRL);
PPM_REG_WRITE_CB(WriteARM_CLK_CTRL);
PPM_REG_WRITE_CB(WriteARM_PLL_CFG);
PPM_REG_WRITE_CB(WriteARM_PLL_CTRL);
PPM_REG_WRITE_CB(WriteCLK_621_TRUE);
PPM_REG_WRITE_CB(WriteOCM_CFG);
PPM_REG_WRITE_CB(WritePSS_RST_CTRL);
PPM_REG_WRITE_CB(WriteSCL);
PPM_REG_WRITE_CB(WriteSLCR_LOCK);
PPM_REG_WRITE_CB(WriteSLCR_UNLOCK);
PPM_REG_WRITE_CB(WriteWDT_CLK_SEL);
PPM_READ_CB(regNoDefinitionRead);
PPM_WRITE_CB(regNoDefinitionWrite);
PPM_NET_CB(reset_resetNet);
PPM_CONSTRUCTOR_CB(periphConstructor);
PPM_DESTRUCTOR_CB(periphDestructor);
PPM_DOC_FN(installDocs);
PPM_CONSTRUCTOR_CB(constructor);
PPM_DESTRUCTOR_CB(destructor);
PPM_SAVE_STATE_FN(peripheralSaveState);
PPM_RESTORE_STATE_FN(peripheralRestoreState);


///////////////////////////////// Local memory /////////////////////////////////

// To access local memory bport1/ab/buffer : (for example)
// char value = ((char*)handles.bport1)[BPORT1_AB_BUFFER_OFFSET + myAddress];

#define BPORT1_AB_BUFFER_OFFSET         0x0
#define BPORT1_AB_BUFFER_SIZE           0xc00

////////////////////////////////// Mask macros /////////////////////////////////

#define BPORT1_AB_SCL_WRMASK            0x1
#define BPORT1_AB_SCL_WRNMASK           (0xfffffffe)
#define BPORT1_AB_SCL_WIDTH             32
#define BPORT1_AB_SLCR_LOCK_WRMASK      0xffff
#define BPORT1_AB_SLCR_LOCK_WRNMASK     (0xffff0000)
#define BPORT1_AB_SLCR_LOCK_WIDTH       32
#define BPORT1_AB_SLCR_UNLOCK_WRMASK    0xffff
#define BPORT1_AB_SLCR_UNLOCK_WRNMASK   (0xffff0000)
#define BPORT1_AB_SLCR_UNLOCK_WIDTH     32
#define BPORT1_AB_SLCR_LOCKSTA_WIDTH    32
#define BPORT1_AB_ARM_PLL_CTRL_WRMASK   0x7f01b
#define BPORT1_AB_ARM_PLL_CTRL_WRNMASK  (0xfff80fe4)
#define BPORT1_AB_ARM_PLL_CTRL_WIDTH    32
#define BPORT1_AB_DDR_PLL_CTRL_WIDTH    32
#define BPORT1_AB_IO_PLL_CTRL_WIDTH     32
#define BPORT1_AB_PLL_STATUS_WIDTH      32
#define BPORT1_AB_ARM_PLL_CFG_WRMASK    0x3ffff0
#define BPORT1_AB_ARM_PLL_CFG_WRNMASK   (0xffc0000f)
#define BPORT1_AB_ARM_PLL_CFG_WIDTH     32
#define BPORT1_AB_DDR_PLL_CFG_WIDTH     32
#define BPORT1_AB_IO_PLL_CFG_WIDTH      32
#define BPORT1_AB_ARM_CLK_CTRL_WRMASK   0x1f003f30
#define BPORT1_AB_ARM_CLK_CTRL_WRNMASK  (0xe0ffc0cf)
#define BPORT1_AB_ARM_CLK_CTRL_WIDTH    32
#define BPORT1_AB_DDR_CLK_CTRL_WIDTH    32
#define BPORT1_AB_DCI_CLK_CTRL_WIDTH    32
#define BPORT1_AB_APER_CLK_CTRL_WIDTH   32
#define BPORT1_AB_USB0_CLK_CTRL_WIDTH   32
#define BPORT1_AB_USB1_CLK_CTRL_WIDTH   32
#define BPORT1_AB_GEM0_RCLK_CTRL_WIDTH  32
#define BPORT1_AB_GEM1_RCLK_CTRL_WIDTH  32
#define BPORT1_AB_GEM0_CLK_CTRL_WIDTH   32
#define BPORT1_AB_GEM1_CLK_CTRL_WIDTH   32
#define BPORT1_AB_SMC_CLK_CTRL_WIDTH    32
#define BPORT1_AB_LQSPI_CLK_CTRL_WIDTH  32
#define BPORT1_AB_SDIO_CLK_CTRL_WIDTH   32
#define BPORT1_AB_UART_CLK_CTRL_WIDTH   32
#define BPORT1_AB_SPI_CLK_CTRL_WIDTH    32
#define BPORT1_AB_CAN_CLK_CTRL_WIDTH    32
#define BPORT1_AB_CAN_MIOCLK_CTRL_WIDTH  32
#define BPORT1_AB_DBG_CLK_CTRL_WIDTH    32
#define BPORT1_AB_PCAP_CLK_CTRL_WIDTH   32
#define BPORT1_AB_TOPSW_CLK_CTRL_WIDTH  32
#define BPORT1_AB_FPGA0_CLK_CTRL_WIDTH  32
#define BPORT1_AB_FPGA0_THR_CTRL_WIDTH  32
#define BPORT1_AB_FPGA0_THR_CNT_WIDTH   32
#define BPORT1_AB_FPGA0_THR_STA_WIDTH   32
#define BPORT1_AB_FPGA1_CLK_CTRL_WIDTH  32
#define BPORT1_AB_FPGA1_THR_CTRL_WIDTH  32
#define BPORT1_AB_FPGA1_THR_CNT_WIDTH   32
#define BPORT1_AB_FPGA1_THR_STA_WIDTH   32
#define BPORT1_AB_FPGA2_CLK_CTRL_WIDTH  32
#define BPORT1_AB_FPGA2_THR_CTRL_WIDTH  32
#define BPORT1_AB_FPGA2_THR_CNT_WIDTH   32
#define BPORT1_AB_FPGA2_THR_STA_WIDTH   32
#define BPORT1_AB_FPGA3_CLK_CTRL_WIDTH  32
#define BPORT1_AB_FPGA3_THR_CTRL_WIDTH  32
#define BPORT1_AB_FPGA3_THR_CNT_WIDTH   32
#define BPORT1_AB_FPGA3_THR_STA_WIDTH   32
#define BPORT1_AB_CLK_621_TRUE_WRMASK   0x1
#define BPORT1_AB_CLK_621_TRUE_WRNMASK  (0xfffffffe)
#define BPORT1_AB_CLK_621_TRUE_WIDTH    32
#define BPORT1_AB_PSS_RST_CTRL_WIDTH    32
#define BPORT1_AB_DDR_RST_CTRL_WIDTH    32
#define BPORT1_AB_TOPSW_RST_CTRL_WIDTH  32
#define BPORT1_AB_DMAC_RST_CTRL_WIDTH   32
#define BPORT1_AB_USB_RST_CTRL_WIDTH    32
#define BPORT1_AB_GEM_RST_CTRL_WIDTH    32
#define BPORT1_AB_SDIO_RST_CTRL_WIDTH   32
#define BPORT1_AB_SPI_RST_CTRL_WIDTH    32
#define BPORT1_AB_CAN_RST_CTRL_WIDTH    32
#define BPORT1_AB_I2C_RST_CTRL_WIDTH    32
#define BPORT1_AB_UART_RST_CTRL_WIDTH   32
#define BPORT1_AB_GPIO_RST_CTRL_WIDTH   32
#define BPORT1_AB_LQSPI_RST_CTRL_WIDTH  32
#define BPORT1_AB_SMC_RST_CTRL_WIDTH    32
#define BPORT1_AB_OCM_RST_CTRL_WIDTH    32
#define BPORT1_AB_FPGA_RST_CTRL_WIDTH   32
#define BPORT1_AB_A9_CPU_RST_CTRL_WIDTH  32
#define BPORT1_AB_RS_AWDT_CTRL_WIDTH    32
#define BPORT1_AB_REBOOT_STATUS_WIDTH   32
#define BPORT1_AB_BOOT_MODE_WIDTH       32
#define BPORT1_AB_APU_CTRL_WIDTH        32
#define BPORT1_AB_WDT_CLK_SEL_WIDTH     32
#define BPORT1_AB_TZ_OCM_RAM0_WIDTH     32
#define BPORT1_AB_TZ_OCM_RAM1_WIDTH     32
#define BPORT1_AB_TZ_OCM_WIDTH          32
#define BPORT1_AB_TZ_DDR_RAM_WRMASK     0x1
#define BPORT1_AB_TZ_DDR_RAM_WRNMASK    (0xfffffffe)
#define BPORT1_AB_TZ_DDR_RAM_WIDTH      32
#define BPORT1_AB_TZ_DMA_NS_WRMASK      0xffff
#define BPORT1_AB_TZ_DMA_NS_WRNMASK     (0xffff0000)
#define BPORT1_AB_TZ_DMA_NS_WIDTH       32
#define BPORT1_AB_TZ_DMA_IRQ_NS_WRMASK  0xffff
#define BPORT1_AB_TZ_DMA_IRQ_NS_WRNMASK  (0xffff0000)
#define BPORT1_AB_TZ_DMA_IRQ_NS_WIDTH   32
#define BPORT1_AB_TZ_DMA_PERIPH_NS_WRMASK  0x1
#define BPORT1_AB_TZ_DMA_PERIPH_NS_WRNMASK  (0xfffffffe)
#define BPORT1_AB_TZ_DMA_PERIPH_NS_WIDTH  32
#define BPORT1_AB_TZ_GEM_WRMASK         0x3
#define BPORT1_AB_TZ_GEM_WRNMASK        (0xfffffffc)
#define BPORT1_AB_TZ_GEM_WIDTH          32
#define BPORT1_AB_TZ_SDIO_WRMASK        0x3
#define BPORT1_AB_TZ_SDIO_WRNMASK       (0xfffffffc)
#define BPORT1_AB_TZ_SDIO_WIDTH         32
#define BPORT1_AB_TZ_USB_WRMASK         0x3
#define BPORT1_AB_TZ_USB_WRNMASK        (0xfffffffc)
#define BPORT1_AB_TZ_USB_WIDTH          32
#define BPORT1_AB_TZ_FPGA_M_WRMASK      0x3
#define BPORT1_AB_TZ_FPGA_M_WRNMASK     (0xfffffffc)
#define BPORT1_AB_TZ_FPGA_M_WIDTH       32
#define BPORT1_AB_TZ_FPGA_AFI_WRMASK    0xf
#define BPORT1_AB_TZ_FPGA_AFI_WRNMASK   (0xfffffff0)
#define BPORT1_AB_TZ_FPGA_AFI_WIDTH     32
#define BPORT1_AB_PSS_IDCODE_WIDTH      32
#define BPORT1_AB_DDR_URGENT_WIDTH      32
#define BPORT1_AB_DDR_CAL_START_WIDTH   32
#define BPORT1_AB_DDR_REF_START_WIDTH   32
#define BPORT1_AB_DDR_CMD_STA_WIDTH     32
#define BPORT1_AB_DDR_URGENT_SEL_WIDTH  32
#define BPORT1_AB_DDR_DFI_STATUS_WIDTH  32
#define BPORT1_AB_MIO_PIN_00_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_00_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_00_WIDTH      32
#define BPORT1_AB_MIO_PIN_01_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_01_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_01_WIDTH      32
#define BPORT1_AB_MIO_PIN_02_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_02_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_02_WIDTH      32
#define BPORT1_AB_MIO_PIN_03_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_03_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_03_WIDTH      32
#define BPORT1_AB_MIO_PIN_04_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_04_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_04_WIDTH      32
#define BPORT1_AB_MIO_PIN_05_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_05_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_05_WIDTH      32
#define BPORT1_AB_MIO_PIN_06_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_06_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_06_WIDTH      32
#define BPORT1_AB_MIO_PIN_07_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_07_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_07_WIDTH      32
#define BPORT1_AB_MIO_PIN_08_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_08_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_08_WIDTH      32
#define BPORT1_AB_MIO_PIN_09_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_09_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_09_WIDTH      32
#define BPORT1_AB_MIO_PIN_10_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_10_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_10_WIDTH      32
#define BPORT1_AB_MIO_PIN_11_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_11_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_11_WIDTH      32
#define BPORT1_AB_MIO_PIN_12_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_12_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_12_WIDTH      32
#define BPORT1_AB_MIO_PIN_13_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_13_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_13_WIDTH      32
#define BPORT1_AB_MIO_PIN_14_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_14_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_14_WIDTH      32
#define BPORT1_AB_MIO_PIN_15_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_15_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_15_WIDTH      32
#define BPORT1_AB_MIO_PIN_16_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_16_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_16_WIDTH      32
#define BPORT1_AB_MIO_PIN_17_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_17_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_17_WIDTH      32
#define BPORT1_AB_MIO_PIN_18_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_18_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_18_WIDTH      32
#define BPORT1_AB_MIO_PIN_19_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_19_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_19_WIDTH      32
#define BPORT1_AB_MIO_PIN_20_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_20_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_20_WIDTH      32
#define BPORT1_AB_MIO_PIN_21_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_21_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_21_WIDTH      32
#define BPORT1_AB_MIO_PIN_22_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_22_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_22_WIDTH      32
#define BPORT1_AB_MIO_PIN_23_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_23_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_23_WIDTH      32
#define BPORT1_AB_MIO_PIN_24_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_24_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_24_WIDTH      32
#define BPORT1_AB_MIO_PIN_25_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_25_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_25_WIDTH      32
#define BPORT1_AB_MIO_PIN_26_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_26_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_26_WIDTH      32
#define BPORT1_AB_MIO_PIN_27_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_27_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_27_WIDTH      32
#define BPORT1_AB_MIO_PIN_28_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_28_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_28_WIDTH      32
#define BPORT1_AB_MIO_PIN_29_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_29_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_29_WIDTH      32
#define BPORT1_AB_MIO_PIN_30_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_30_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_30_WIDTH      32
#define BPORT1_AB_MIO_PIN_31_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_31_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_31_WIDTH      32
#define BPORT1_AB_MIO_PIN_32_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_32_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_32_WIDTH      32
#define BPORT1_AB_MIO_PIN_33_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_33_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_33_WIDTH      32
#define BPORT1_AB_MIO_PIN_34_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_34_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_34_WIDTH      32
#define BPORT1_AB_MIO_PIN_35_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_35_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_35_WIDTH      32
#define BPORT1_AB_MIO_PIN_36_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_36_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_36_WIDTH      32
#define BPORT1_AB_MIO_PIN_37_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_37_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_37_WIDTH      32
#define BPORT1_AB_MIO_PIN_38_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_38_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_38_WIDTH      32
#define BPORT1_AB_MIO_PIN_39_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_39_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_39_WIDTH      32
#define BPORT1_AB_MIO_PIN_40_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_40_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_40_WIDTH      32
#define BPORT1_AB_MIO_PIN_41_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_41_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_41_WIDTH      32
#define BPORT1_AB_MIO_PIN_42_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_42_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_42_WIDTH      32
#define BPORT1_AB_MIO_PIN_43_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_43_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_43_WIDTH      32
#define BPORT1_AB_MIO_PIN_44_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_44_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_44_WIDTH      32
#define BPORT1_AB_MIO_PIN_45_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_45_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_45_WIDTH      32
#define BPORT1_AB_MIO_PIN_46_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_46_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_46_WIDTH      32
#define BPORT1_AB_MIO_PIN_47_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_47_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_47_WIDTH      32
#define BPORT1_AB_MIO_PIN_48_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_48_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_48_WIDTH      32
#define BPORT1_AB_MIO_PIN_49_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_49_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_49_WIDTH      32
#define BPORT1_AB_MIO_PIN_50_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_50_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_50_WIDTH      32
#define BPORT1_AB_MIO_PIN_51_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_51_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_51_WIDTH      32
#define BPORT1_AB_MIO_PIN_52_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_52_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_52_WIDTH      32
#define BPORT1_AB_MIO_PIN_53_WRMASK     0x3fff
#define BPORT1_AB_MIO_PIN_53_WRNMASK    (0xffffc000)
#define BPORT1_AB_MIO_PIN_53_WIDTH      32
#define BPORT1_AB_MIO_LOOPBACK_WIDTH    32
#define BPORT1_AB_MIO_MST_TRI0_WIDTH    32
#define BPORT1_AB_MIO_MST_TRI1_WIDTH    32
#define BPORT1_AB_SD0_WP_CD_SEL_WIDTH   32
#define BPORT1_AB_SD1_WP_CD_SEL_WIDTH   32
#define BPORT1_AB_LVL_SHFTR_EN_WIDTH    32
#define BPORT1_AB_OCM_CFG_WIDTH         32
#define BPORT1_AB_RESERVED_WIDTH        32
#define BPORT1_AB_GPIOB_CTRL_WIDTH      32
#define BPORT1_AB_GPIOB_CFG_CMOS18_WIDTH  32
#define BPORT1_AB_GPIOB_CFG_CMOS25_WIDTH  32
#define BPORT1_AB_GPIOB_CFG_CMOS33_WIDTH  32
#define BPORT1_AB_GPIOB_CFG_HSTL_WIDTH  32
#define BPORT1_AB_GPIOB_DRVR_BIAS_CTRL_WIDTH  32
#define BPORT1_AB_DDRIOB_ADDR0_WIDTH    32
#define BPORT1_AB_DDRIOB_ADDR1_WIDTH    32
#define BPORT1_AB_DDRIOB_DATA0_WIDTH    32
#define BPORT1_AB_DDRIOB_DATA1_WIDTH    32
#define BPORT1_AB_DDRIOB_DIFF0_WIDTH    32
#define BPORT1_AB_DDRIOB_DIFF1_WIDTH    32
#define BPORT1_AB_DDRIOB_CLOCK_WIDTH    32
#define BPORT1_AB_DDRIOB_DRIVE_SLEW_ADDR_WIDTH  32
#define BPORT1_AB_DDRIOB_DRIVE_SLEW_DATA_WIDTH  32
#define BPORT1_AB_DDRIOB_DRIVE_SLEW_DIFF_WIDTH  32
#define BPORT1_AB_DDRIOB_DRIVE_SLEW_CLOCK_WIDTH  32
#define BPORT1_AB_DDRIOB_DDR_CTRL_WIDTH  32
#define BPORT1_AB_DDRIOB_DCI_CTRL_WIDTH  32
#define BPORT1_AB_DDRIOB_DCI_STATUS_WIDTH  32

//////////////////////////// Parameters of enum type ///////////////////////////


#endif

#endif
