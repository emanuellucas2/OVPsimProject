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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisUSB", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view8) {  *(Uns8*)data = *(Uns8*)user; }

static PPM_READ_CB(read_8) {  return *(Uns8*)user; }

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_ADDR_maskWrite) {
    bport1_ab_data.ADDR.value = (bport1_ab_data.ADDR.value & BPORT1_AB_ADDR_WRNMASK) | (data & BPORT1_AB_ADDR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_BDTPAGE1_maskWrite) {
    bport1_ab_data.BDTPAGE1.value = (bport1_ab_data.BDTPAGE1.value & BPORT1_AB_BDTPAGE1_WRNMASK) | (data & BPORT1_AB_BDTPAGE1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_BDTPAGE2_maskWrite) {
    bport1_ab_data.BDTPAGE2.value = (bport1_ab_data.BDTPAGE2.value & BPORT1_AB_BDTPAGE2_WRNMASK) | (data & BPORT1_AB_BDTPAGE2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_BDTPAGE3_maskWrite) {
    bport1_ab_data.BDTPAGE3.value = (bport1_ab_data.BDTPAGE3.value & BPORT1_AB_BDTPAGE3_WRNMASK) | (data & BPORT1_AB_BDTPAGE3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CONTROL_maskWrite) {
    bport1_ab_data.CONTROL.value = (bport1_ab_data.CONTROL.value & BPORT1_AB_CONTROL_WRNMASK) | (data & BPORT1_AB_CONTROL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_CTL_maskWrite) {
    bport1_ab_data.CTL.value = (bport1_ab_data.CTL.value & BPORT1_AB_CTL_WRNMASK) | (data & BPORT1_AB_CTL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT0_maskWrite) {
    bport1_ab_data.ENDPOINT0.value = (bport1_ab_data.ENDPOINT0.value & BPORT1_AB_ENDPOINT0_WRNMASK) | (data & BPORT1_AB_ENDPOINT0_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT10_maskWrite) {
    bport1_ab_data.ENDPOINT10.value = (bport1_ab_data.ENDPOINT10.value & BPORT1_AB_ENDPOINT10_WRNMASK) | (data & BPORT1_AB_ENDPOINT10_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT11_maskWrite) {
    bport1_ab_data.ENDPOINT11.value = (bport1_ab_data.ENDPOINT11.value & BPORT1_AB_ENDPOINT11_WRNMASK) | (data & BPORT1_AB_ENDPOINT11_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT12_maskWrite) {
    bport1_ab_data.ENDPOINT12.value = (bport1_ab_data.ENDPOINT12.value & BPORT1_AB_ENDPOINT12_WRNMASK) | (data & BPORT1_AB_ENDPOINT12_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT13_maskWrite) {
    bport1_ab_data.ENDPOINT13.value = (bport1_ab_data.ENDPOINT13.value & BPORT1_AB_ENDPOINT13_WRNMASK) | (data & BPORT1_AB_ENDPOINT13_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT14_maskWrite) {
    bport1_ab_data.ENDPOINT14.value = (bport1_ab_data.ENDPOINT14.value & BPORT1_AB_ENDPOINT14_WRNMASK) | (data & BPORT1_AB_ENDPOINT14_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT15_maskWrite) {
    bport1_ab_data.ENDPOINT15.value = (bport1_ab_data.ENDPOINT15.value & BPORT1_AB_ENDPOINT15_WRNMASK) | (data & BPORT1_AB_ENDPOINT15_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT1_maskWrite) {
    bport1_ab_data.ENDPOINT1.value = (bport1_ab_data.ENDPOINT1.value & BPORT1_AB_ENDPOINT1_WRNMASK) | (data & BPORT1_AB_ENDPOINT1_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT2_maskWrite) {
    bport1_ab_data.ENDPOINT2.value = (bport1_ab_data.ENDPOINT2.value & BPORT1_AB_ENDPOINT2_WRNMASK) | (data & BPORT1_AB_ENDPOINT2_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT3_maskWrite) {
    bport1_ab_data.ENDPOINT3.value = (bport1_ab_data.ENDPOINT3.value & BPORT1_AB_ENDPOINT3_WRNMASK) | (data & BPORT1_AB_ENDPOINT3_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT4_maskWrite) {
    bport1_ab_data.ENDPOINT4.value = (bport1_ab_data.ENDPOINT4.value & BPORT1_AB_ENDPOINT4_WRNMASK) | (data & BPORT1_AB_ENDPOINT4_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT5_maskWrite) {
    bport1_ab_data.ENDPOINT5.value = (bport1_ab_data.ENDPOINT5.value & BPORT1_AB_ENDPOINT5_WRNMASK) | (data & BPORT1_AB_ENDPOINT5_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT6_maskWrite) {
    bport1_ab_data.ENDPOINT6.value = (bport1_ab_data.ENDPOINT6.value & BPORT1_AB_ENDPOINT6_WRNMASK) | (data & BPORT1_AB_ENDPOINT6_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT7_maskWrite) {
    bport1_ab_data.ENDPOINT7.value = (bport1_ab_data.ENDPOINT7.value & BPORT1_AB_ENDPOINT7_WRNMASK) | (data & BPORT1_AB_ENDPOINT7_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT8_maskWrite) {
    bport1_ab_data.ENDPOINT8.value = (bport1_ab_data.ENDPOINT8.value & BPORT1_AB_ENDPOINT8_WRNMASK) | (data & BPORT1_AB_ENDPOINT8_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ENDPOINT9_maskWrite) {
    bport1_ab_data.ENDPOINT9.value = (bport1_ab_data.ENDPOINT9.value & BPORT1_AB_ENDPOINT9_WRNMASK) | (data & BPORT1_AB_ENDPOINT9_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ERREN_maskWrite) {
    bport1_ab_data.ERREN.value = (bport1_ab_data.ERREN.value & BPORT1_AB_ERREN_WRNMASK) | (data & BPORT1_AB_ERREN_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ERRSTAT_maskWrite) {
    bport1_ab_data.ERRSTAT.value = (bport1_ab_data.ERRSTAT.value & BPORT1_AB_ERRSTAT_WRNMASK) | (data & BPORT1_AB_ERRSTAT_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FRMNUMH_maskWrite) {
    bport1_ab_data.FRMNUMH.value = (bport1_ab_data.FRMNUMH.value & BPORT1_AB_FRMNUMH_WRNMASK) | (data & BPORT1_AB_FRMNUMH_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_FRMNUML_maskWrite) {
    bport1_ab_data.FRMNUML.value = (bport1_ab_data.FRMNUML.value & BPORT1_AB_FRMNUML_WRNMASK) | (data & BPORT1_AB_FRMNUML_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_INTEN_maskWrite) {
    bport1_ab_data.INTEN.value = (bport1_ab_data.INTEN.value & BPORT1_AB_INTEN_WRNMASK) | (data & BPORT1_AB_INTEN_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_ISTAT_maskWrite) {
    bport1_ab_data.ISTAT.value = (bport1_ab_data.ISTAT.value & BPORT1_AB_ISTAT_WRNMASK) | (data & BPORT1_AB_ISTAT_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_OTGCTL_maskWrite) {
    bport1_ab_data.OTGCTL.value = (bport1_ab_data.OTGCTL.value & BPORT1_AB_OTGCTL_WRNMASK) | (data & BPORT1_AB_OTGCTL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_OTGICR_maskWrite) {
    bport1_ab_data.OTGICR.value = (bport1_ab_data.OTGICR.value & BPORT1_AB_OTGICR_WRNMASK) | (data & BPORT1_AB_OTGICR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_OTGISTAT_maskWrite) {
    bport1_ab_data.OTGISTAT.value = (bport1_ab_data.OTGISTAT.value & BPORT1_AB_OTGISTAT_WRNMASK) | (data & BPORT1_AB_OTGISTAT_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_OTGSTAT_maskWrite) {
    bport1_ab_data.OTGSTAT.value = (bport1_ab_data.OTGSTAT.value & BPORT1_AB_OTGSTAT_WRNMASK) | (data & BPORT1_AB_OTGSTAT_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SOFTHLD_maskWrite) {
    bport1_ab_data.SOFTHLD.value = (bport1_ab_data.SOFTHLD.value & BPORT1_AB_SOFTHLD_WRNMASK) | (data & BPORT1_AB_SOFTHLD_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TOKEN_maskWrite) {
    bport1_ab_data.TOKEN.value = (bport1_ab_data.TOKEN.value & BPORT1_AB_TOKEN_WRNMASK) | (data & BPORT1_AB_TOKEN_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_USBCTRL_maskWrite) {
    bport1_ab_data.USBCTRL.value = (bport1_ab_data.USBCTRL.value & BPORT1_AB_USBCTRL_WRNMASK) | (data & BPORT1_AB_USBCTRL_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_USBFRMADJUST_maskWrite) {
    bport1_ab_data.USBFRMADJUST.value = (bport1_ab_data.USBFRMADJUST.value & BPORT1_AB_USBFRMADJUST_WRNMASK) | (data & BPORT1_AB_USBFRMADJUST_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_USBTRC0_maskWrite) {
    bport1_ab_data.USBTRC0.value = (bport1_ab_data.USBTRC0.value & BPORT1_AB_USBTRC0_WRNMASK) | (data & BPORT1_AB_USBTRC0_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abPERID_reg = ppmCreateRegister(
            "ab_PERID",
            "Peripheral ID Register, offset: 0x0 ",
            handles.bport1,
            0x0,
            1,
            read_8,
            0,
            view8,
            &(bport1_ab_data.PERID.value),
            True
        );

        ppmCreateRegisterField(abPERID_reg, "ID", 0, 0, 6, 1, 0);
    }
    {
        registerHandle abIDCOMP_reg = ppmCreateRegister(
            "ab_IDCOMP",
            "Peripheral ID Complement Register, offset: 0x4 ",
            handles.bport1,
            0x4,
            1,
            read_8,
            0,
            view8,
            &(bport1_ab_data.IDCOMP.value),
            True
        );

        ppmCreateRegisterField(abIDCOMP_reg, "NID", 0, 0, 6, 1, 0);
    }
    {
        registerHandle abREV_reg = ppmCreateRegister(
            "ab_REV",
            "Peripheral Revision Register, offset: 0x8 ",
            handles.bport1,
            0x8,
            1,
            read_8,
            0,
            view8,
            &(bport1_ab_data.REV.value),
            True
        );

        ppmCreateRegisterField(abREV_reg, "REV", 0, 0, 8, 1, 0);
    }
    {
        registerHandle abADDINFO_reg = ppmCreateRegister(
            "ab_ADDINFO",
            "Peripheral Additional Info Register, offset: 0xC ",
            handles.bport1,
            0xc,
            1,
            read_8,
            0,
            view8,
            &(bport1_ab_data.ADDINFO.value),
            True
        );

        ppmCreateRegisterField(abADDINFO_reg, "IEHOST", 0, 0, 1, 1, 0);
        ppmCreateRegisterField(abADDINFO_reg, "IRQNUM", 0, 3, 5, 1, 0);
    }
    {
        registerHandle abOTGISTAT_reg = ppmCreateRegister(
            "ab_OTGISTAT",
            "OTG Interrupt Status Register, offset: 0x10 ",
            handles.bport1,
            0x10,
            1,
            read_8,
            bport1_ab_OTGISTAT_maskWrite,
            view8,
            &(bport1_ab_data.OTGISTAT.value),
            True
        );

        ppmCreateRegisterField(abOTGISTAT_reg, "AVBUSCHG", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abOTGISTAT_reg, "B_SESS_CHG", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abOTGISTAT_reg, "IDCHG", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abOTGISTAT_reg, "LINE_STATE_CHG", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abOTGISTAT_reg, "ONEMSEC", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abOTGISTAT_reg, "SESSVLDCHG", 0, 3, 1, 1, 1);
    }
    {
        registerHandle abOTGICR_reg = ppmCreateRegister(
            "ab_OTGICR",
            "OTG Interrupt Control Register, offset: 0x14 ",
            handles.bport1,
            0x14,
            1,
            read_8,
            bport1_ab_OTGICR_maskWrite,
            view8,
            &(bport1_ab_data.OTGICR.value),
            True
        );

        ppmCreateRegisterField(abOTGICR_reg, "AVBUSEN", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abOTGICR_reg, "BSESSEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abOTGICR_reg, "IDEN", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abOTGICR_reg, "LINESTATEEN", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abOTGICR_reg, "ONEMSECEN", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abOTGICR_reg, "SESSVLDEN", 0, 3, 1, 1, 1);
    }
    {
        registerHandle abOTGSTAT_reg = ppmCreateRegister(
            "ab_OTGSTAT",
            "OTG Status Register, offset: 0x18 ",
            handles.bport1,
            0x18,
            1,
            read_8,
            bport1_ab_OTGSTAT_maskWrite,
            view8,
            &(bport1_ab_data.OTGSTAT.value),
            True
        );

        ppmCreateRegisterField(abOTGSTAT_reg, "AVBUSVLD", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abOTGSTAT_reg, "BSESSEND", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abOTGSTAT_reg, "ID", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abOTGSTAT_reg, "LINESTATESTABLE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abOTGSTAT_reg, "ONEMSECEN", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abOTGSTAT_reg, "SESS_VLD", 0, 3, 1, 1, 1);
    }
    {
        registerHandle abOTGCTL_reg = ppmCreateRegister(
            "ab_OTGCTL",
            "OTG Control Register, offset: 0x1C ",
            handles.bport1,
            0x1c,
            1,
            read_8,
            bport1_ab_OTGCTL_maskWrite,
            view8,
            &(bport1_ab_data.OTGCTL.value),
            True
        );

        ppmCreateRegisterField(abOTGCTL_reg, "DMLOW", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abOTGCTL_reg, "DPHIGH", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abOTGCTL_reg, "DPLOW", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abOTGCTL_reg, "OTGEN", 0, 2, 1, 1, 1);
    }
    {
        registerHandle abISTAT_reg = ppmCreateRegister(
            "ab_ISTAT",
            "Interrupt Status Register, offset: 0x80 ",
            handles.bport1,
            0x80,
            1,
            read_8,
            bport1_ab_ISTAT_maskWrite,
            view8,
            &(bport1_ab_data.ISTAT.value),
            True
        );

        ppmCreateRegisterField(abISTAT_reg, "ATTACH", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abISTAT_reg, "ERROR", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abISTAT_reg, "RESUME", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abISTAT_reg, "SLEEP", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abISTAT_reg, "SOFTOK", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abISTAT_reg, "STALL", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abISTAT_reg, "TOKDNE", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abISTAT_reg, "USBRST", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abINTEN_reg = ppmCreateRegister(
            "ab_INTEN",
            "Interrupt Enable Register, offset: 0x84 ",
            handles.bport1,
            0x84,
            1,
            read_8,
            bport1_ab_INTEN_maskWrite,
            view8,
            &(bport1_ab_data.INTEN.value),
            True
        );

        ppmCreateRegisterField(abINTEN_reg, "ATTACHEN", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abINTEN_reg, "ERROREN", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abINTEN_reg, "RESUMEEN", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abINTEN_reg, "SLEEPEN", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abINTEN_reg, "SOFTOKEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abINTEN_reg, "STALLEN", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abINTEN_reg, "TOKDNEEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abINTEN_reg, "USBRSTEN", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abERRSTAT_reg = ppmCreateRegister(
            "ab_ERRSTAT",
            "Error Interrupt Status Register, offset: 0x88 ",
            handles.bport1,
            0x88,
            1,
            read_8,
            bport1_ab_ERRSTAT_maskWrite,
            view8,
            &(bport1_ab_data.ERRSTAT.value),
            True
        );

        ppmCreateRegisterField(abERRSTAT_reg, "BTOERR", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abERRSTAT_reg, "BTSERR", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abERRSTAT_reg, "CRC16", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abERRSTAT_reg, "CRC5EOF", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abERRSTAT_reg, "DFN8", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abERRSTAT_reg, "DMAERR", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abERRSTAT_reg, "PIDERR", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abERREN_reg = ppmCreateRegister(
            "ab_ERREN",
            "Error Interrupt Enable Register, offset: 0x8C ",
            handles.bport1,
            0x8c,
            1,
            read_8,
            bport1_ab_ERREN_maskWrite,
            view8,
            &(bport1_ab_data.ERREN.value),
            True
        );

        ppmCreateRegisterField(abERREN_reg, "BTOERREN", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abERREN_reg, "BTSERREN", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abERREN_reg, "CRC16EN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abERREN_reg, "CRC5EOFEN", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abERREN_reg, "DFN8EN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abERREN_reg, "DMAERREN", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abERREN_reg, "PIDERREN", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abSTAT_reg = ppmCreateRegister(
            "ab_STAT",
            "Status Register, offset: 0x90 ",
            handles.bport1,
            0x90,
            1,
            read_8,
            0,
            view8,
            &(bport1_ab_data.STAT.value),
            True
        );

        ppmCreateRegisterField(abSTAT_reg, "ENDP", 0, 4, 4, 1, 0);
        ppmCreateRegisterField(abSTAT_reg, "ODD", 0, 2, 1, 1, 0);
        ppmCreateRegisterField(abSTAT_reg, "TX", 0, 3, 1, 1, 0);
    }
    {
        registerHandle abCTL_reg = ppmCreateRegister(
            "ab_CTL",
            "Control Register, offset: 0x94 ",
            handles.bport1,
            0x94,
            1,
            read_8,
            bport1_ab_CTL_maskWrite,
            view8,
            &(bport1_ab_data.CTL.value),
            True
        );

        ppmCreateRegisterField(abCTL_reg, "HOSTMODEEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abCTL_reg, "JSTATE", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abCTL_reg, "ODDRST", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abCTL_reg, "RESET", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abCTL_reg, "RESUME", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abCTL_reg, "SE0", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abCTL_reg, "TXSUSPENDTOKENBUSY", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abCTL_reg, "USBENSOFEN", 0, 0, 1, 1, 1);
    }
    {
        registerHandle abADDR_reg = ppmCreateRegister(
            "ab_ADDR",
            "Address Register, offset: 0x98 ",
            handles.bport1,
            0x98,
            1,
            read_8,
            bport1_ab_ADDR_maskWrite,
            view8,
            &(bport1_ab_data.ADDR.value),
            True
        );

        ppmCreateRegisterField(abADDR_reg, "ADDR", 0, 0, 7, 1, 1);
        ppmCreateRegisterField(abADDR_reg, "LSEN", 0, 7, 1, 1, 1);
    }
    {
        registerHandle abBDTPAGE1_reg = ppmCreateRegister(
            "ab_BDTPAGE1",
            "BDT Page Register 1, offset: 0x9C ",
            handles.bport1,
            0x9c,
            1,
            read_8,
            bport1_ab_BDTPAGE1_maskWrite,
            view8,
            &(bport1_ab_data.BDTPAGE1.value),
            True
        );

        ppmCreateRegisterField(abBDTPAGE1_reg, "BDTBA", 0, 1, 7, 1, 1);
    }
    {
        registerHandle abFRMNUML_reg = ppmCreateRegister(
            "ab_FRMNUML",
            "Frame Number Register Low, offset: 0xA0 ",
            handles.bport1,
            0xa0,
            1,
            read_8,
            bport1_ab_FRMNUML_maskWrite,
            view8,
            &(bport1_ab_data.FRMNUML.value),
            True
        );

        ppmCreateRegisterField(abFRMNUML_reg, "FRM", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abFRMNUMH_reg = ppmCreateRegister(
            "ab_FRMNUMH",
            "Frame Number Register High, offset: 0xA4 ",
            handles.bport1,
            0xa4,
            1,
            read_8,
            bport1_ab_FRMNUMH_maskWrite,
            view8,
            &(bport1_ab_data.FRMNUMH.value),
            True
        );

        ppmCreateRegisterField(abFRMNUMH_reg, "FRM", 0, 0, 3, 1, 1);
    }
    {
        registerHandle abTOKEN_reg = ppmCreateRegister(
            "ab_TOKEN",
            "Token Register, offset: 0xA8 ",
            handles.bport1,
            0xa8,
            1,
            read_8,
            bport1_ab_TOKEN_maskWrite,
            view8,
            &(bport1_ab_data.TOKEN.value),
            True
        );

        ppmCreateRegisterField(abTOKEN_reg, "TOKENENDPT", 0, 0, 4, 1, 1);
        ppmCreateRegisterField(abTOKEN_reg, "TOKENPID", 0, 4, 4, 1, 1);
    }
    {
        registerHandle abSOFTHLD_reg = ppmCreateRegister(
            "ab_SOFTHLD",
            "SOF Threshold Register, offset: 0xAC ",
            handles.bport1,
            0xac,
            1,
            read_8,
            bport1_ab_SOFTHLD_maskWrite,
            view8,
            &(bport1_ab_data.SOFTHLD.value),
            True
        );

        ppmCreateRegisterField(abSOFTHLD_reg, "CNT", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abBDTPAGE2_reg = ppmCreateRegister(
            "ab_BDTPAGE2",
            "BDT Page Register 2, offset: 0xB0 ",
            handles.bport1,
            0xb0,
            1,
            read_8,
            bport1_ab_BDTPAGE2_maskWrite,
            view8,
            &(bport1_ab_data.BDTPAGE2.value),
            True
        );

        ppmCreateRegisterField(abBDTPAGE2_reg, "BDTBA", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abBDTPAGE3_reg = ppmCreateRegister(
            "ab_BDTPAGE3",
            "BDT Page Register 3, offset: 0xB4 ",
            handles.bport1,
            0xb4,
            1,
            read_8,
            bport1_ab_BDTPAGE3_maskWrite,
            view8,
            &(bport1_ab_data.BDTPAGE3.value),
            True
        );

        ppmCreateRegisterField(abBDTPAGE3_reg, "BDTBA", 0, 0, 8, 1, 1);
    }
    {
        registerHandle abENDPOINT0_reg = ppmCreateRegister(
            "ab_ENDPOINT0",
            "Endpoint Control Register 0, offset 0xc0",
            handles.bport1,
            0xc0,
            1,
            read_8,
            bport1_ab_ENDPOINT0_maskWrite,
            view8,
            &(bport1_ab_data.ENDPOINT0.value),
            True
        );

        ppmCreateRegisterField(abENDPOINT0_reg, "EPCTLDIS", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT0_reg, "EPHSHK", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT0_reg, "EPRXEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT0_reg, "EPSTALL", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT0_reg, "EPTXEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT0_reg, "HOSTWOHUB", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT0_reg, "RETRYDIS", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abENDPOINT1_reg = ppmCreateRegister(
            "ab_ENDPOINT1",
            "Endpoint Control Register 1, offset 0xc4",
            handles.bport1,
            0xc4,
            1,
            read_8,
            bport1_ab_ENDPOINT1_maskWrite,
            view8,
            &(bport1_ab_data.ENDPOINT1.value),
            True
        );

        ppmCreateRegisterField(abENDPOINT1_reg, "EPCTLDIS", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT1_reg, "EPHSHK", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT1_reg, "EPRXEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT1_reg, "EPSTALL", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT1_reg, "EPTXEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT1_reg, "HOSTWOHUB", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT1_reg, "RETRYDIS", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abENDPOINT2_reg = ppmCreateRegister(
            "ab_ENDPOINT2",
            "Endpoint Control Register 2, offset 0xc8",
            handles.bport1,
            0xc8,
            1,
            read_8,
            bport1_ab_ENDPOINT2_maskWrite,
            view8,
            &(bport1_ab_data.ENDPOINT2.value),
            True
        );

        ppmCreateRegisterField(abENDPOINT2_reg, "EPCTLDIS", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT2_reg, "EPHSHK", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT2_reg, "EPRXEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT2_reg, "EPSTALL", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT2_reg, "EPTXEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT2_reg, "HOSTWOHUB", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT2_reg, "RETRYDIS", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abENDPOINT3_reg = ppmCreateRegister(
            "ab_ENDPOINT3",
            "Endpoint Control Register 3, offset 0xcc",
            handles.bport1,
            0xcc,
            1,
            read_8,
            bport1_ab_ENDPOINT3_maskWrite,
            view8,
            &(bport1_ab_data.ENDPOINT3.value),
            True
        );

        ppmCreateRegisterField(abENDPOINT3_reg, "EPCTLDIS", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT3_reg, "EPHSHK", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT3_reg, "EPRXEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT3_reg, "EPSTALL", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT3_reg, "EPTXEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT3_reg, "HOSTWOHUB", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT3_reg, "RETRYDIS", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abENDPOINT4_reg = ppmCreateRegister(
            "ab_ENDPOINT4",
            "Endpoint Control Register 4, offset 0xd0",
            handles.bport1,
            0xd0,
            1,
            read_8,
            bport1_ab_ENDPOINT4_maskWrite,
            view8,
            &(bport1_ab_data.ENDPOINT4.value),
            True
        );

        ppmCreateRegisterField(abENDPOINT4_reg, "EPCTLDIS", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT4_reg, "EPHSHK", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT4_reg, "EPRXEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT4_reg, "EPSTALL", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT4_reg, "EPTXEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT4_reg, "HOSTWOHUB", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT4_reg, "RETRYDIS", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abENDPOINT5_reg = ppmCreateRegister(
            "ab_ENDPOINT5",
            "Endpoint Control Register 5, offset 0xd4",
            handles.bport1,
            0xd4,
            1,
            read_8,
            bport1_ab_ENDPOINT5_maskWrite,
            view8,
            &(bport1_ab_data.ENDPOINT5.value),
            True
        );

        ppmCreateRegisterField(abENDPOINT5_reg, "EPCTLDIS", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT5_reg, "EPHSHK", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT5_reg, "EPRXEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT5_reg, "EPSTALL", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT5_reg, "EPTXEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT5_reg, "HOSTWOHUB", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT5_reg, "RETRYDIS", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abENDPOINT6_reg = ppmCreateRegister(
            "ab_ENDPOINT6",
            "Endpoint Control Register 6, offset 0xd8",
            handles.bport1,
            0xd8,
            1,
            read_8,
            bport1_ab_ENDPOINT6_maskWrite,
            view8,
            &(bport1_ab_data.ENDPOINT6.value),
            True
        );

        ppmCreateRegisterField(abENDPOINT6_reg, "EPCTLDIS", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT6_reg, "EPHSHK", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT6_reg, "EPRXEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT6_reg, "EPSTALL", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT6_reg, "EPTXEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT6_reg, "HOSTWOHUB", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT6_reg, "RETRYDIS", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abENDPOINT7_reg = ppmCreateRegister(
            "ab_ENDPOINT7",
            "Endpoint Control Register 7, offset 0xdc",
            handles.bport1,
            0xdc,
            1,
            read_8,
            bport1_ab_ENDPOINT7_maskWrite,
            view8,
            &(bport1_ab_data.ENDPOINT7.value),
            True
        );

        ppmCreateRegisterField(abENDPOINT7_reg, "EPCTLDIS", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT7_reg, "EPHSHK", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT7_reg, "EPRXEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT7_reg, "EPSTALL", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT7_reg, "EPTXEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT7_reg, "HOSTWOHUB", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT7_reg, "RETRYDIS", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abENDPOINT8_reg = ppmCreateRegister(
            "ab_ENDPOINT8",
            "Endpoint Control Register 8, offset 0xe0",
            handles.bport1,
            0xe0,
            1,
            read_8,
            bport1_ab_ENDPOINT8_maskWrite,
            view8,
            &(bport1_ab_data.ENDPOINT8.value),
            True
        );

        ppmCreateRegisterField(abENDPOINT8_reg, "EPCTLDIS", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT8_reg, "EPHSHK", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT8_reg, "EPRXEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT8_reg, "EPSTALL", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT8_reg, "EPTXEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT8_reg, "HOSTWOHUB", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT8_reg, "RETRYDIS", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abENDPOINT9_reg = ppmCreateRegister(
            "ab_ENDPOINT9",
            "Endpoint Control Register 9, offset 0xe4",
            handles.bport1,
            0xe4,
            1,
            read_8,
            bport1_ab_ENDPOINT9_maskWrite,
            view8,
            &(bport1_ab_data.ENDPOINT9.value),
            True
        );

        ppmCreateRegisterField(abENDPOINT9_reg, "EPCTLDIS", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT9_reg, "EPHSHK", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT9_reg, "EPRXEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT9_reg, "EPSTALL", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT9_reg, "EPTXEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT9_reg, "HOSTWOHUB", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT9_reg, "RETRYDIS", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abENDPOINT10_reg = ppmCreateRegister(
            "ab_ENDPOINT10",
            "Endpoint Control Register 10, offset 0xe8",
            handles.bport1,
            0xe8,
            1,
            read_8,
            bport1_ab_ENDPOINT10_maskWrite,
            view8,
            &(bport1_ab_data.ENDPOINT10.value),
            True
        );

        ppmCreateRegisterField(abENDPOINT10_reg, "EPCTLDIS", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT10_reg, "EPHSHK", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT10_reg, "EPRXEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT10_reg, "EPSTALL", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT10_reg, "EPTXEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT10_reg, "HOSTWOHUB", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT10_reg, "RETRYDIS", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abENDPOINT11_reg = ppmCreateRegister(
            "ab_ENDPOINT11",
            "Endpoint Control Register 11, offset 0xec",
            handles.bport1,
            0xec,
            1,
            read_8,
            bport1_ab_ENDPOINT11_maskWrite,
            view8,
            &(bport1_ab_data.ENDPOINT11.value),
            True
        );

        ppmCreateRegisterField(abENDPOINT11_reg, "EPCTLDIS", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT11_reg, "EPHSHK", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT11_reg, "EPRXEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT11_reg, "EPSTALL", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT11_reg, "EPTXEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT11_reg, "HOSTWOHUB", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT11_reg, "RETRYDIS", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abENDPOINT12_reg = ppmCreateRegister(
            "ab_ENDPOINT12",
            "Endpoint Control Register 12, offset 0xf0",
            handles.bport1,
            0xf0,
            1,
            read_8,
            bport1_ab_ENDPOINT12_maskWrite,
            view8,
            &(bport1_ab_data.ENDPOINT12.value),
            True
        );

        ppmCreateRegisterField(abENDPOINT12_reg, "EPCTLDIS", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT12_reg, "EPHSHK", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT12_reg, "EPRXEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT12_reg, "EPSTALL", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT12_reg, "EPTXEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT12_reg, "HOSTWOHUB", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT12_reg, "RETRYDIS", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abENDPOINT13_reg = ppmCreateRegister(
            "ab_ENDPOINT13",
            "Endpoint Control Register 13, offset 0xf4",
            handles.bport1,
            0xf4,
            1,
            read_8,
            bport1_ab_ENDPOINT13_maskWrite,
            view8,
            &(bport1_ab_data.ENDPOINT13.value),
            True
        );

        ppmCreateRegisterField(abENDPOINT13_reg, "EPCTLDIS", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT13_reg, "EPHSHK", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT13_reg, "EPRXEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT13_reg, "EPSTALL", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT13_reg, "EPTXEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT13_reg, "HOSTWOHUB", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT13_reg, "RETRYDIS", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abENDPOINT14_reg = ppmCreateRegister(
            "ab_ENDPOINT14",
            "Endpoint Control Register 14, offset 0xf8",
            handles.bport1,
            0xf8,
            1,
            read_8,
            bport1_ab_ENDPOINT14_maskWrite,
            view8,
            &(bport1_ab_data.ENDPOINT14.value),
            True
        );

        ppmCreateRegisterField(abENDPOINT14_reg, "EPCTLDIS", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT14_reg, "EPHSHK", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT14_reg, "EPRXEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT14_reg, "EPSTALL", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT14_reg, "EPTXEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT14_reg, "HOSTWOHUB", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT14_reg, "RETRYDIS", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abENDPOINT15_reg = ppmCreateRegister(
            "ab_ENDPOINT15",
            "Endpoint Control Register 15, offset 0xfc",
            handles.bport1,
            0xfc,
            1,
            read_8,
            bport1_ab_ENDPOINT15_maskWrite,
            view8,
            &(bport1_ab_data.ENDPOINT15.value),
            True
        );

        ppmCreateRegisterField(abENDPOINT15_reg, "EPCTLDIS", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT15_reg, "EPHSHK", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT15_reg, "EPRXEN", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT15_reg, "EPSTALL", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT15_reg, "EPTXEN", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT15_reg, "HOSTWOHUB", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abENDPOINT15_reg, "RETRYDIS", 0, 6, 1, 1, 1);
    }
    {
        registerHandle abUSBCTRL_reg = ppmCreateRegister(
            "ab_USBCTRL",
            "USB Control Register, offset: 0x100 ",
            handles.bport1,
            0x100,
            1,
            read_8,
            bport1_ab_USBCTRL_maskWrite,
            view8,
            &(bport1_ab_data.USBCTRL.value),
            True
        );

        ppmCreateRegisterField(abUSBCTRL_reg, "PDE", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abUSBCTRL_reg, "SUSP", 0, 7, 1, 1, 1);
    }
    {
        registerHandle abOBSERVE_reg = ppmCreateRegister(
            "ab_OBSERVE",
            "USB OTG Observe Register, offset: 0x104 ",
            handles.bport1,
            0x104,
            1,
            read_8,
            0,
            view8,
            &(bport1_ab_data.OBSERVE.value),
            True
        );

        ppmCreateRegisterField(abOBSERVE_reg, "DMPD", 0, 4, 1, 1, 0);
        ppmCreateRegisterField(abOBSERVE_reg, "DPPD", 0, 6, 1, 1, 0);
        ppmCreateRegisterField(abOBSERVE_reg, "DPPU", 0, 7, 1, 1, 0);
    }
    {
        registerHandle abCONTROL_reg = ppmCreateRegister(
            "ab_CONTROL",
            "USB OTG Control Register, offset: 0x108 ",
            handles.bport1,
            0x108,
            1,
            read_8,
            bport1_ab_CONTROL_maskWrite,
            view8,
            &(bport1_ab_data.CONTROL.value),
            True
        );

        ppmCreateRegisterField(abCONTROL_reg, "DPPULLUPNONOTG", 0, 4, 1, 1, 1);
    }
    {
        registerHandle abUSBTRC0_reg = ppmCreateRegister(
            "ab_USBTRC0",
            "USB Transceiver Control Register 0, offset: 0x10C ",
            handles.bport1,
            0x10c,
            1,
            read_8,
            bport1_ab_USBTRC0_maskWrite,
            view8,
            &(bport1_ab_data.USBTRC0.value),
            True
        );

        ppmCreateRegisterField(abUSBTRC0_reg, "SYNC_DET", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abUSBTRC0_reg, "USB_RESUME_INT", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abUSBTRC0_reg, "USBRESET", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abUSBTRC0_reg, "USBRESMEN", 0, 5, 1, 1, 1);
    }
    {
        registerHandle abUSBFRMADJUST_reg = ppmCreateRegister(
            "ab_USBFRMADJUST",
            "Frame Adjust Register, offset: 0x114 ",
            handles.bport1,
            0x114,
            1,
            read_8,
            bport1_ab_USBFRMADJUST_maskWrite,
            view8,
            &(bport1_ab_data.USBFRMADJUST.value),
            True
        );

        ppmCreateRegisterField(abUSBFRMADJUST_reg, "ADJ", 0, 0, 8, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.USBFRMADJUST.value = (Uns8)(bport1_ab_data.USBFRMADJUST.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.USBTRC0.value = (Uns8)(bport1_ab_data.USBTRC0.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.CONTROL.value = (Uns8)(bport1_ab_data.CONTROL.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.OBSERVE.value = (Uns8)(bport1_ab_data.OBSERVE.value & ~(0xff)) | ((0xff) & (0x50));
        bport1_ab_data.USBCTRL.value = (Uns8)(bport1_ab_data.USBCTRL.value & ~(0xff)) | ((0xff) & (0xc0));
        bport1_ab_data.ENDPOINT15.value = (Uns8)(bport1_ab_data.ENDPOINT15.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.ENDPOINT14.value = (Uns8)(bport1_ab_data.ENDPOINT14.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.ENDPOINT13.value = (Uns8)(bport1_ab_data.ENDPOINT13.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.ENDPOINT12.value = (Uns8)(bport1_ab_data.ENDPOINT12.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.ENDPOINT11.value = (Uns8)(bport1_ab_data.ENDPOINT11.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.ENDPOINT10.value = (Uns8)(bport1_ab_data.ENDPOINT10.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.ENDPOINT9.value = (Uns8)(bport1_ab_data.ENDPOINT9.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.ENDPOINT8.value = (Uns8)(bport1_ab_data.ENDPOINT8.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.ENDPOINT7.value = (Uns8)(bport1_ab_data.ENDPOINT7.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.ENDPOINT6.value = (Uns8)(bport1_ab_data.ENDPOINT6.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.ENDPOINT5.value = (Uns8)(bport1_ab_data.ENDPOINT5.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.ENDPOINT4.value = (Uns8)(bport1_ab_data.ENDPOINT4.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.ENDPOINT3.value = (Uns8)(bport1_ab_data.ENDPOINT3.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.ENDPOINT2.value = (Uns8)(bport1_ab_data.ENDPOINT2.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.ENDPOINT1.value = (Uns8)(bport1_ab_data.ENDPOINT1.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.ENDPOINT0.value = (Uns8)(bport1_ab_data.ENDPOINT0.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.BDTPAGE3.value = (Uns8)(bport1_ab_data.BDTPAGE3.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.BDTPAGE2.value = (Uns8)(bport1_ab_data.BDTPAGE2.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.SOFTHLD.value = (Uns8)(bport1_ab_data.SOFTHLD.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.TOKEN.value = (Uns8)(bport1_ab_data.TOKEN.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.FRMNUMH.value = (Uns8)(bport1_ab_data.FRMNUMH.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.FRMNUML.value = (Uns8)(bport1_ab_data.FRMNUML.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.BDTPAGE1.value = (Uns8)(bport1_ab_data.BDTPAGE1.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.ADDR.value = (Uns8)(bport1_ab_data.ADDR.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.CTL.value = (Uns8)(bport1_ab_data.CTL.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.STAT.value = (Uns8)(bport1_ab_data.STAT.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.ERREN.value = (Uns8)(bport1_ab_data.ERREN.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.ERRSTAT.value = (Uns8)(bport1_ab_data.ERRSTAT.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.INTEN.value = (Uns8)(bport1_ab_data.INTEN.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.ISTAT.value = (Uns8)(bport1_ab_data.ISTAT.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.OTGCTL.value = (Uns8)(bport1_ab_data.OTGCTL.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.OTGSTAT.value = (Uns8)(bport1_ab_data.OTGSTAT.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.OTGICR.value = (Uns8)(bport1_ab_data.OTGICR.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.OTGISTAT.value = (Uns8)(bport1_ab_data.OTGISTAT.value & ~(0xff)) | ((0xff) & (0x00));
        bport1_ab_data.ADDINFO.value = (Uns8)(bport1_ab_data.ADDINFO.value & ~(0xff)) | ((0xff) & (0x01));
        bport1_ab_data.REV.value = (Uns8)(bport1_ab_data.REV.value & ~(0xff)) | ((0xff) & (0x33));
        bport1_ab_data.IDCOMP.value = (Uns8)(bport1_ab_data.IDCOMP.value & ~(0xff)) | ((0xff) & (0xfb));
        bport1_ab_data.PERID.value = (Uns8)(bport1_ab_data.PERID.value & ~(0xff)) | ((0xff) & (0x04));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the USB peripheral used on the Freescale Kinetis platform");
        ppmDocNodeP doc_12_node = ppmDocAddSection(Root1_node, "Limitations");
        ppmDocAddText(doc_12_node, "Provides the base behaviour for the OVP Freescale Kinetis platforms");
        ppmDocNodeP doc_22_node = ppmDocAddSection(Root1_node, "Reference");
        ppmDocAddText(doc_22_node, "www.freescale.com/Kinetis");
        ppmDocNodeP doc_32_node = ppmDocAddSection(Root1_node, "Licensing");
        ppmDocAddText(doc_32_node, "Open Source Apache 2.0");
    }
}
////////////////////////////////// Constructor /////////////////////////////////

PPM_CONSTRUCTOR_CB(periphConstructor) {
    installSlavePorts();
    installRegisters();
    reset_Reset(1,0);
}

///////////////////////////////////// Main /////////////////////////////////////

int main(int argc, char *argv[]) {

    diagnosticLevel = 0;
    bhmInstallDiagCB(setDiagLevel);
    constructor();

    bhmWaitEvent(bhmGetSystemEvent(BHM_SE_END_OF_SIMULATION));
    return 0;
}

