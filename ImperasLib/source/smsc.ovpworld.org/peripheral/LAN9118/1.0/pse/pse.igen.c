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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "LAN9118", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

//////////////////////////////// View callbacks ////////////////////////////////

static PPM_VIEW_CB(view_bport1_ab_RX_DATA_FIFO) {
    *(Uns32*)data = bport1_ab_data.RX_DATA_FIFO.value;
}

static PPM_VIEW_CB(view_bport1_ab_RX_DATA_FIFO_1) {
    *(Uns32*)data = bport1_ab_data.RX_DATA_FIFO_1.value;
}

static PPM_VIEW_CB(view_bport1_ab_RX_DATA_FIFO_2) {
    *(Uns32*)data = bport1_ab_data.RX_DATA_FIFO_2.value;
}

static PPM_VIEW_CB(view_bport1_ab_RX_DATA_FIFO_3) {
    *(Uns32*)data = bport1_ab_data.RX_DATA_FIFO_3.value;
}

static PPM_VIEW_CB(view_bport1_ab_RX_DATA_FIFO_4) {
    *(Uns32*)data = bport1_ab_data.RX_DATA_FIFO_4.value;
}

static PPM_VIEW_CB(view_bport1_ab_RX_DATA_FIFO_5) {
    *(Uns32*)data = bport1_ab_data.RX_DATA_FIFO_5.value;
}

static PPM_VIEW_CB(view_bport1_ab_RX_DATA_FIFO_6) {
    *(Uns32*)data = bport1_ab_data.RX_DATA_FIFO_6.value;
}

static PPM_VIEW_CB(view_bport1_ab_RX_DATA_FIFO_7) {
    *(Uns32*)data = bport1_ab_data.RX_DATA_FIFO_7.value;
}

static PPM_VIEW_CB(view_bport1_ab_TX_DATA_FIFO) {
    *(Uns32*)data = bport1_ab_data.TX_DATA_FIFO.value;
}

static PPM_VIEW_CB(view_bport1_ab_TX_DATA_FIFO_1) {
    *(Uns32*)data = bport1_ab_data.TX_DATA_FIFO_1.value;
}

static PPM_VIEW_CB(view_bport1_ab_TX_DATA_FIFO_2) {
    *(Uns32*)data = bport1_ab_data.TX_DATA_FIFO_2.value;
}

static PPM_VIEW_CB(view_bport1_ab_TX_DATA_FIFO_3) {
    *(Uns32*)data = bport1_ab_data.TX_DATA_FIFO_3.value;
}

static PPM_VIEW_CB(view_bport1_ab_TX_DATA_FIFO_4) {
    *(Uns32*)data = bport1_ab_data.TX_DATA_FIFO_4.value;
}

static PPM_VIEW_CB(view_bport1_ab_TX_DATA_FIFO_5) {
    *(Uns32*)data = bport1_ab_data.TX_DATA_FIFO_5.value;
}

static PPM_VIEW_CB(view_bport1_ab_TX_DATA_FIFO_6) {
    *(Uns32*)data = bport1_ab_data.TX_DATA_FIFO_6.value;
}

static PPM_VIEW_CB(view_bport1_ab_TX_DATA_FIFO_7) {
    *(Uns32*)data = bport1_ab_data.TX_DATA_FIFO_7.value;
}

static PPM_VIEW_CB(view_bport1_ab_RX_STATUS_FIFO) {
    *(Uns32*)data = bport1_ab_data.RX_STATUS_FIFO.value;
}

static PPM_VIEW_CB(view_bport1_ab_RX_STATUS_FIFO_PEEK) {
    *(Uns32*)data = bport1_ab_data.RX_STATUS_FIFO_PEEK.value;
}

static PPM_VIEW_CB(view_bport1_ab_TX_STATUS_FIFO) {
    *(Uns32*)data = bport1_ab_data.TX_STATUS_FIFO.value;
}

static PPM_VIEW_CB(view_bport1_ab_TX_STATUS_FIFO_PEEK) {
    *(Uns32*)data = bport1_ab_data.TX_STATUS_FIFO_PEEK.value;
}

static PPM_VIEW_CB(view_bport1_ab_ID_REV) {
    *(Uns32*)data = bport1_ab_data.ID_REV.value;
}

static PPM_VIEW_CB(view_bport1_ab_IRQ_CFG) {
    *(Uns32*)data = bport1_ab_data.IRQ_CFG.value;
}

static PPM_VIEW_CB(view_bport1_ab_INT_STS) {
    *(Uns32*)data = bport1_ab_data.INT_STS.value;
}

static PPM_VIEW_CB(view_bport1_ab_INT_EN) {
    *(Uns32*)data = bport1_ab_data.INT_EN.value;
}

static PPM_VIEW_CB(view_bport1_ab_BYTE_TEST) {
    *(Uns32*)data = bport1_ab_data.BYTE_TEST.value;
}

static PPM_VIEW_CB(view_bport1_ab_FIFO_INT) {
    *(Uns32*)data = bport1_ab_data.FIFO_INT.value;
}

static PPM_VIEW_CB(view_bport1_ab_RX_CFG) {
    *(Uns32*)data = bport1_ab_data.RX_CFG.value;
}

static PPM_VIEW_CB(view_bport1_ab_TX_CFG) {
    *(Uns32*)data = bport1_ab_data.TX_CFG.value;
}

static PPM_VIEW_CB(view_bport1_ab_HW_CFG) {
    *(Uns32*)data = bport1_ab_data.HW_CFG.value;
}

static PPM_VIEW_CB(view_bport1_ab_RX_DP_CTRL) {
    *(Uns32*)data = bport1_ab_data.RX_DP_CTRL.value;
}

static PPM_VIEW_CB(view_bport1_ab_RX_FIFO_INF) {
    *(Uns32*)data = bport1_ab_data.RX_FIFO_INF.value;
}

static PPM_VIEW_CB(view_bport1_ab_TX_FIFO_INF) {
    *(Uns32*)data = bport1_ab_data.TX_FIFO_INF.value;
}

static PPM_VIEW_CB(view_bport1_ab_PMT_CTRL) {
    *(Uns32*)data = bport1_ab_data.PMT_CTRL.value;
}

static PPM_VIEW_CB(view_bport1_ab_GPIO_CFG) {
    *(Uns32*)data = bport1_ab_data.GPIO_CFG.value;
}

static PPM_VIEW_CB(view_bport1_ab_GPT_CFG) {
    *(Uns32*)data = bport1_ab_data.GPT_CFG.value;
}

static PPM_VIEW_CB(view_bport1_ab_GPT_CNT) {
    *(Uns32*)data = bport1_ab_data.GPT_CNT.value;
}

static PPM_VIEW_CB(view_bport1_ab_WORD_SWAP) {
    *(Uns32*)data = bport1_ab_data.WORD_SWAP.value;
}

static PPM_VIEW_CB(view_bport1_ab_FREE_RUN) {
    *(Uns32*)data = bport1_ab_data.FREE_RUN.value;
}

static PPM_VIEW_CB(view_bport1_ab_RX_DROP) {
    *(Uns32*)data = bport1_ab_data.RX_DROP.value;
}

static PPM_VIEW_CB(view_bport1_ab_MAC_CSR_CMD) {
    *(Uns32*)data = bport1_ab_data.MAC_CSR_CMD.value;
}

static PPM_VIEW_CB(view_bport1_ab_MAC_CSR_DATA) {
    *(Uns32*)data = bport1_ab_data.MAC_CSR_DATA.value;
}

static PPM_VIEW_CB(view_bport1_ab_AFC_CFG) {
    *(Uns32*)data = bport1_ab_data.AFC_CFG.value;
}

static PPM_VIEW_CB(view_bport1_ab_E2P_CMD) {
    *(Uns32*)data = bport1_ab_data.E2P_CMD.value;
}

static PPM_VIEW_CB(view_bport1_ab_E2P_DATA) {
    *(Uns32*)data = bport1_ab_data.E2P_DATA.value;
}
//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        ppmCreateRegister(
            "ab_RX_DATA_FIFO",
            0,
            handles.bport1,
            0x0,
            4,
            rxFifoRd,
            0,
            view_bport1_ab_RX_DATA_FIFO,
            (void*)0x00,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RX_DATA_FIFO_1",
            0,
            handles.bport1,
            0x4,
            4,
            rxFifoRd,
            0,
            view_bport1_ab_RX_DATA_FIFO_1,
            (void*)0x04,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RX_DATA_FIFO_2",
            0,
            handles.bport1,
            0x8,
            4,
            rxFifoRd,
            0,
            view_bport1_ab_RX_DATA_FIFO_2,
            (void*)0x08,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RX_DATA_FIFO_3",
            0,
            handles.bport1,
            0xc,
            4,
            rxFifoRd,
            0,
            view_bport1_ab_RX_DATA_FIFO_3,
            (void*)0x0c,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RX_DATA_FIFO_4",
            0,
            handles.bport1,
            0x10,
            4,
            rxFifoRd,
            0,
            view_bport1_ab_RX_DATA_FIFO_4,
            (void*)0x10,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RX_DATA_FIFO_5",
            0,
            handles.bport1,
            0x14,
            4,
            rxFifoRd,
            0,
            view_bport1_ab_RX_DATA_FIFO_5,
            (void*)0x14,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RX_DATA_FIFO_6",
            0,
            handles.bport1,
            0x18,
            4,
            rxFifoRd,
            0,
            view_bport1_ab_RX_DATA_FIFO_6,
            (void*)0x18,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RX_DATA_FIFO_7",
            0,
            handles.bport1,
            0x1c,
            4,
            rxFifoRd,
            0,
            view_bport1_ab_RX_DATA_FIFO_7,
            (void*)0x1c,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TX_DATA_FIFO",
            0,
            handles.bport1,
            0x20,
            4,
            0,
            txFifoWr,
            view_bport1_ab_TX_DATA_FIFO,
            (void*)0x20,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TX_DATA_FIFO_1",
            0,
            handles.bport1,
            0x24,
            4,
            0,
            txFifoWr,
            view_bport1_ab_TX_DATA_FIFO_1,
            (void*)0x24,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TX_DATA_FIFO_2",
            0,
            handles.bport1,
            0x28,
            4,
            0,
            txFifoWr,
            view_bport1_ab_TX_DATA_FIFO_2,
            (void*)0x28,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TX_DATA_FIFO_3",
            0,
            handles.bport1,
            0x2c,
            4,
            0,
            txFifoWr,
            view_bport1_ab_TX_DATA_FIFO_3,
            (void*)0x2c,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TX_DATA_FIFO_4",
            0,
            handles.bport1,
            0x30,
            4,
            0,
            txFifoWr,
            view_bport1_ab_TX_DATA_FIFO_4,
            (void*)0x30,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TX_DATA_FIFO_5",
            0,
            handles.bport1,
            0x34,
            4,
            0,
            txFifoWr,
            view_bport1_ab_TX_DATA_FIFO_5,
            (void*)0x34,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TX_DATA_FIFO_6",
            0,
            handles.bport1,
            0x38,
            4,
            0,
            txFifoWr,
            view_bport1_ab_TX_DATA_FIFO_6,
            (void*)0x38,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TX_DATA_FIFO_7",
            0,
            handles.bport1,
            0x3c,
            4,
            0,
            txFifoWr,
            view_bport1_ab_TX_DATA_FIFO_7,
            (void*)0x3c,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RX_STATUS_FIFO",
            0,
            handles.bport1,
            0x40,
            4,
            rxStatusFifoRd,
            0,
            view_bport1_ab_RX_STATUS_FIFO,
            (void*)0x40,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_RX_STATUS_FIFO_PEEK",
            0,
            handles.bport1,
            0x44,
            4,
            rxStatusFifoPeek,
            0,
            view_bport1_ab_RX_STATUS_FIFO_PEEK,
            (void*)0x44,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TX_STATUS_FIFO",
            0,
            handles.bport1,
            0x48,
            4,
            txStatusFifoRd,
            0,
            view_bport1_ab_TX_STATUS_FIFO,
            (void*)0x48,
            True
        );
    }
    {
        ppmCreateRegister(
            "ab_TX_STATUS_FIFO_PEEK",
            0,
            handles.bport1,
            0x4c,
            4,
            txStatusFifoPeek,
            0,
            view_bport1_ab_TX_STATUS_FIFO_PEEK,
            (void*)0x4c,
            True
        );
    }
    {
        registerHandle abID_REV_reg = ppmCreateRegister(
            "ab_ID_REV",
            0,
            handles.bport1,
            0x50,
            4,
            idRev,
            0,
            view_bport1_ab_ID_REV,
            (void*)0x50,
            True
        );

        ppmCreateRegisterField(abID_REV_reg, "ID", 0, 16, 16, 1, 0);
        ppmCreateRegisterField(abID_REV_reg, "REV", 0, 0, 16, 1, 0);
    }
    {
        registerHandle abIRQ_CFG_reg = ppmCreateRegister(
            "ab_IRQ_CFG",
            0,
            handles.bport1,
            0x54,
            4,
            irqCfgRd,
            irqCfgWr,
            view_bport1_ab_IRQ_CFG,
            (void*)0x54,
            True
        );

        ppmCreateRegisterField(abIRQ_CFG_reg, "INT_DEAS", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abIRQ_CFG_reg, "INT_DEAS_CLR", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abIRQ_CFG_reg, "INT_DEAS_STS", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abIRQ_CFG_reg, "IRQ_INT", 0, 12, 1, 1, 0);
        ppmCreateRegisterField(abIRQ_CFG_reg, "IRQ_EN", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abIRQ_CFG_reg, "IRQ_POL", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abIRQ_CFG_reg, "IRQ_TYPE", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abINT_STS_reg = ppmCreateRegister(
            "ab_INT_STS",
            0,
            handles.bport1,
            0x58,
            4,
            intStsRd,
            intStsWr,
            view_bport1_ab_INT_STS,
            (void*)0x58,
            True
        );

        ppmCreateRegisterField(abINT_STS_reg, "SW_INT", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abINT_STS_reg, "TXSTOP_INT", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abINT_STS_reg, "RXSTOP_INT", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abINT_STS_reg, "RXDFH_INT", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abINT_STS_reg, "TX_IOC", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abINT_STS_reg, "RXD_INT", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abINT_STS_reg, "GPT_INT", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abINT_STS_reg, "PHY_INT", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abINT_STS_reg, "PME_INT", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abINT_STS_reg, "TXSO", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abINT_STS_reg, "RWT", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abINT_STS_reg, "RXE", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abINT_STS_reg, "TXE", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abINT_STS_reg, "TDFO", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abINT_STS_reg, "TDFA", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abINT_STS_reg, "TSFF", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abINT_STS_reg, "TSFL", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abINT_STS_reg, "RXDF_INT", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abINT_STS_reg, "RSFF", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abINT_STS_reg, "RSFL", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abINT_STS_reg, "GPIOx_INT", 0, 0, 3, 1, 1);
    }
    {
        registerHandle abINT_EN_reg = ppmCreateRegister(
            "ab_INT_EN",
            0,
            handles.bport1,
            0x5c,
            4,
            intEnRd,
            intEnWr,
            view_bport1_ab_INT_EN,
            (void*)0x5c,
            True
        );

        ppmCreateRegisterField(abINT_EN_reg, "SW_INT_EN", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abINT_EN_reg, "TXSTOP_INT_EN", 0, 25, 1, 1, 1);
        ppmCreateRegisterField(abINT_EN_reg, "RXSTOP_INT_EN", 0, 24, 1, 1, 1);
        ppmCreateRegisterField(abINT_EN_reg, "RXDFH_INT_EN", 0, 23, 1, 1, 1);
        ppmCreateRegisterField(abINT_EN_reg, "TIOC_INT_EN", 0, 21, 1, 1, 1);
        ppmCreateRegisterField(abINT_EN_reg, "RXD_INT", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abINT_EN_reg, "GPT_INT_EN", 0, 19, 1, 1, 1);
        ppmCreateRegisterField(abINT_EN_reg, "PHY_INT_EN", 0, 18, 1, 1, 1);
        ppmCreateRegisterField(abINT_EN_reg, "PME_INT_EN", 0, 17, 1, 1, 1);
        ppmCreateRegisterField(abINT_EN_reg, "TXSO_EN", 0, 16, 1, 1, 1);
        ppmCreateRegisterField(abINT_EN_reg, "RWT_INT_EN", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abINT_EN_reg, "RXE_INT_EN", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abINT_EN_reg, "TXE_INT_EN", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abINT_EN_reg, "TDFO_INT_EN", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abINT_EN_reg, "TDFA_INT_EN", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abINT_EN_reg, "TSFF_INT_EN", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abINT_EN_reg, "TSFL_INT_EN", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abINT_EN_reg, "RXDF_INT_EN", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abINT_EN_reg, "RSFF_INT_EN", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abINT_EN_reg, "RSFL_INT_EN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abINT_EN_reg, "GPIOx_INT_EN", 0, 0, 3, 1, 1);
    }
    {
        ppmCreateRegister(
            "ab_BYTE_TEST",
            0,
            handles.bport1,
            0x64,
            4,
            byteTest,
            0,
            view_bport1_ab_BYTE_TEST,
            (void*)0x64,
            True
        );
    }
    {
        registerHandle abFIFO_INT_reg = ppmCreateRegister(
            "ab_FIFO_INT",
            0,
            handles.bport1,
            0x68,
            4,
            defaultRdCB,
            defaultWrCB,
            view_bport1_ab_FIFO_INT,
            (void*)0x68,
            True
        );

        ppmCreateRegisterField(abFIFO_INT_reg, "TXDataAvailL", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abFIFO_INT_reg, "TXStatusL", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abFIFO_INT_reg, "RXStatusL", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abRX_CFG_reg = ppmCreateRegister(
            "ab_RX_CFG",
            0,
            handles.bport1,
            0x6c,
            4,
            rxCfgRd,
            rxCfgWr,
            view_bport1_ab_RX_CFG,
            (void*)0x6c,
            True
        );

        ppmCreateRegisterField(abRX_CFG_reg, "RXEndAlign", 0, 30, 2, 1, 1);
        ppmCreateRegisterField(abRX_CFG_reg, "RX_DMA_CNT", 0, 16, 12, 1, 1);
        ppmCreateRegisterField(abRX_CFG_reg, "RX_DUMP", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abRX_CFG_reg, "RXDOFF", 0, 8, 5, 1, 1);
    }
    {
        registerHandle abTX_CFG_reg = ppmCreateRegister(
            "ab_TX_CFG",
            0,
            handles.bport1,
            0x70,
            4,
            txCfgRd,
            txCfgWr,
            view_bport1_ab_TX_CFG,
            (void*)0x70,
            True
        );

        ppmCreateRegisterField(abTX_CFG_reg, "TXS_DUMP", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abTX_CFG_reg, "TXD_DUMP", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abTX_CFG_reg, "TXSAO", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abTX_CFG_reg, "TX_ON", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abTX_CFG_reg, "STOP_TX", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abHW_CFG_reg = ppmCreateRegister(
            "ab_HW_CFG",
            0,
            handles.bport1,
            0x74,
            4,
            hwCfgRd,
            hwCfgWr,
            view_bport1_ab_HW_CFG,
            (void*)0x74,
            True
        );

        ppmCreateRegisterField(abHW_CFG_reg, "MBO", 0, 20, 1, 1, 1);
        ppmCreateRegisterField(abHW_CFG_reg, "TX_FIF_SZ", 0, 16, 4, 1, 1);
        ppmCreateRegisterField(abHW_CFG_reg, "MODE1632", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(abHW_CFG_reg, "SRST_TO", 0, 1, 1, 1, 0);
        ppmCreateRegisterField(abHW_CFG_reg, "SRST", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abRX_DP_CTRL_reg = ppmCreateRegister(
            "ab_RX_DP_CTRL",
            0,
            handles.bport1,
            0x78,
            4,
            defaultRdCB,
            defaultWrCB,
            view_bport1_ab_RX_DP_CTRL,
            (void*)0x78,
            True
        );

        ppmCreateRegisterField(abRX_DP_CTRL_reg, "RX_FFWD", 0, 31, 1, 1, 1);
    }
    {
        registerHandle abRX_FIFO_INF_reg = ppmCreateRegister(
            "ab_RX_FIFO_INF",
            0,
            handles.bport1,
            0x7c,
            4,
            rxFifoInfRd,
            0,
            view_bport1_ab_RX_FIFO_INF,
            (void*)0x7c,
            True
        );

        ppmCreateRegisterField(abRX_FIFO_INF_reg, "RXSUSED", 0, 16, 8, 1, 0);
        ppmCreateRegisterField(abRX_FIFO_INF_reg, "RXDUSED", 0, 0, 16, 1, 0);
    }
    {
        registerHandle abTX_FIFO_INF_reg = ppmCreateRegister(
            "ab_TX_FIFO_INF",
            0,
            handles.bport1,
            0x80,
            4,
            txFifoInfRd,
            0,
            view_bport1_ab_TX_FIFO_INF,
            (void*)0x80,
            True
        );

        ppmCreateRegisterField(abTX_FIFO_INF_reg, "TXSUSED", 0, 16, 8, 1, 0);
        ppmCreateRegisterField(abTX_FIFO_INF_reg, "TXDFREE", 0, 0, 16, 1, 0);
    }
    {
        registerHandle abPMT_CTRL_reg = ppmCreateRegister(
            "ab_PMT_CTRL",
            0,
            handles.bport1,
            0x84,
            4,
            defaultRdCB,
            defaultWrCB,
            view_bport1_ab_PMT_CTRL,
            (void*)0x84,
            True
        );

        ppmCreateRegisterField(abPMT_CTRL_reg, "PM_MODE", 0, 12, 2, 1, 1);
        ppmCreateRegisterField(abPMT_CTRL_reg, "PHY_RST", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abPMT_CTRL_reg, "WOL_EN", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abPMT_CTRL_reg, "ED_EN", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abPMT_CTRL_reg, "PME_TYPE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abPMT_CTRL_reg, "WUPS", 0, 4, 2, 1, 1);
        ppmCreateRegisterField(abPMT_CTRL_reg, "PME_IND", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abPMT_CTRL_reg, "PME_POL", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abPMT_CTRL_reg, "PME_EN", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abPMT_CTRL_reg, "READY", 0, 0, 1, 1, 0);
    }
    {
        registerHandle abGPIO_CFG_reg = ppmCreateRegister(
            "ab_GPIO_CFG",
            0,
            handles.bport1,
            0x88,
            4,
            defaultRdCB,
            defaultWrCB,
            view_bport1_ab_GPIO_CFG,
            (void*)0x88,
            True
        );

        ppmCreateRegisterField(abGPIO_CFG_reg, "LEDx_EN", 0, 28, 3, 1, 1);
        ppmCreateRegisterField(abGPIO_CFG_reg, "GPIO_INT_POL", 0, 24, 3, 1, 1);
        ppmCreateRegisterField(abGPIO_CFG_reg, "EEPR_EN", 0, 20, 3, 1, 1);
        ppmCreateRegisterField(abGPIO_CFG_reg, "GPIOBUFn", 0, 16, 3, 1, 1);
        ppmCreateRegisterField(abGPIO_CFG_reg, "GPDIRn", 0, 8, 3, 1, 1);
        ppmCreateRegisterField(abGPIO_CFG_reg, "GPODn", 0, 3, 2, 1, 1);
        ppmCreateRegisterField(abGPIO_CFG_reg, "GPIODn", 0, 0, 3, 1, 1);
    }
    {
        registerHandle abGPT_CFG_reg = ppmCreateRegister(
            "ab_GPT_CFG",
            0,
            handles.bport1,
            0x8c,
            4,
            defaultRdCB,
            defaultWrCB,
            view_bport1_ab_GPT_CFG,
            (void*)0x8c,
            True
        );

        ppmCreateRegisterField(abGPT_CFG_reg, "TIMER_EN", 0, 29, 1, 1, 1);
        ppmCreateRegisterField(abGPT_CFG_reg, "GPT_LOAD", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abGPT_CNT_reg = ppmCreateRegister(
            "ab_GPT_CNT",
            0,
            handles.bport1,
            0x90,
            4,
            defaultRdCB,
            0,
            view_bport1_ab_GPT_CNT,
            (void*)0x90,
            True
        );

        ppmCreateRegisterField(abGPT_CNT_reg, "GPT_CNT", 0, 0, 16, 1, 0);
    }
    {
        ppmCreateRegister(
            "ab_WORD_SWAP",
            0,
            handles.bport1,
            0x98,
            4,
            defaultRdCB,
            defaultWrCB,
            view_bport1_ab_WORD_SWAP,
            (void*)0x98,
            True
        );
    }
    {
        registerHandle abFREE_RUN_reg = ppmCreateRegister(
            "ab_FREE_RUN",
            0,
            handles.bport1,
            0x9c,
            4,
            defaultRdCB,
            0,
            view_bport1_ab_FREE_RUN,
            (void*)0x9c,
            True
        );

        ppmCreateRegisterField(abFREE_RUN_reg, "FR_CNT", 0, 0, 32, 1, 0);
    }
    {
        registerHandle abRX_DROP_reg = ppmCreateRegister(
            "ab_RX_DROP",
            0,
            handles.bport1,
            0xa0,
            4,
            rxDropRd,
            0,
            view_bport1_ab_RX_DROP,
            (void*)0xA0,
            True
        );

        ppmCreateRegisterField(abRX_DROP_reg, "RX_DFC", 0, 0, 32, 1, 0);
    }
    {
        registerHandle abMAC_CSR_CMD_reg = ppmCreateRegister(
            "ab_MAC_CSR_CMD",
            0,
            handles.bport1,
            0xa4,
            4,
            macCsrCmdRd,
            macCsrCmdWr,
            view_bport1_ab_MAC_CSR_CMD,
            (void*)0xA4,
            True
        );

        ppmCreateRegisterField(abMAC_CSR_CMD_reg, "CSRBusy", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abMAC_CSR_CMD_reg, "RnW", 0, 30, 1, 1, 1);
        ppmCreateRegisterField(abMAC_CSR_CMD_reg, "CSRAddress", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abMAC_CSR_DATA_reg = ppmCreateRegister(
            "ab_MAC_CSR_DATA",
            0,
            handles.bport1,
            0xa8,
            4,
            macCsrDataRd,
            macCsrDataWr,
            view_bport1_ab_MAC_CSR_DATA,
            (void*)0xA8,
            True
        );

        ppmCreateRegisterField(abMAC_CSR_DATA_reg, "MACCSRData", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abAFC_CFG_reg = ppmCreateRegister(
            "ab_AFC_CFG",
            0,
            handles.bport1,
            0xac,
            4,
            defaultRdCB,
            defaultWrCB,
            view_bport1_ab_AFC_CFG,
            (void*)0xAc,
            True
        );

        ppmCreateRegisterField(abAFC_CFG_reg, "AFC_HI", 0, 16, 8, 1, 1);
        ppmCreateRegisterField(abAFC_CFG_reg, "AFC_LO", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abAFC_CFG_reg, "BACK_DUR", 0, 4, 4, 1, 1);
        ppmCreateRegisterField(abAFC_CFG_reg, "FCMULT", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abAFC_CFG_reg, "FCBRD", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abAFC_CFG_reg, "FCADD", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abAFC_CFG_reg, "FCANY", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abE2P_CMD_reg = ppmCreateRegister(
            "ab_E2P_CMD",
            0,
            handles.bport1,
            0xb0,
            4,
            defaultRdCB,
            defaultWrCB,
            view_bport1_ab_E2P_CMD,
            (void*)0xB0,
            True
        );

        ppmCreateRegisterField(abE2P_CMD_reg, "EPCBusy", 0, 31, 1, 1, 1);
        ppmCreateRegisterField(abE2P_CMD_reg, "EPCcommand", 0, 28, 3, 1, 1);
        ppmCreateRegisterField(abE2P_CMD_reg, "EPCTimeout", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abE2P_CMD_reg, "MACAddrLoaded", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abE2P_CMD_reg, "EPCAddr", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abE2P_DATA_reg = ppmCreateRegister(
            "ab_E2P_DATA",
            0,
            handles.bport1,
            0xb4,
            4,
            defaultRdCB,
            defaultWrCB,
            view_bport1_ab_E2P_DATA,
            (void*)0xB4,
            True
        );

        ppmCreateRegisterField(abE2P_DATA_reg, "EEPROMData", 0, 0, 8, 1, 1);
    }

}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Fully functional Model of SMSC LAN9118 for Arm Versatile Express platforms. For full details please consult README-EMAC.txt");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_12_node, "Open Source Apache 2.0");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_22_node, "See README-EMAC.txt");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_32_node, "SMSC LAN9118 High Performance single-chip 10/100 Non-PCI Ethernet Controller Datasheet Revision 1.5 (07-11-08)");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
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

