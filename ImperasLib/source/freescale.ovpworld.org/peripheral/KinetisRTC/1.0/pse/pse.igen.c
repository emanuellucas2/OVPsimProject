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
// eg. if (diagnosticLevel >= 1) bhmMessage("I", "KinetisRTC", "Example");
//     Predefined macros PSE_DIAG_LOW, PSE_DIAG_MEDIUM and PSE_DIAG_HIGH may be used
Uns32 diagnosticLevel;

/////////////////////////// Diagnostic level callback //////////////////////////

static void setDiagLevel(Uns32 new) {
    diagnosticLevel = new;
}

///////////////////////////// MMR Generic callbacks ////////////////////////////

static PPM_VIEW_CB(view32) {  *(Uns32*)data = *(Uns32*)user; }

static PPM_READ_CB(read_32) {  return *(Uns32*)user; }

//////////////////////////////// Mask functions ////////////////////////////////

static PPM_WRITE_CB(bport1_ab_CR_maskWrite) {
    bport1_ab_data.CR.value = (bport1_ab_data.CR.value & BPORT1_AB_CR_WRNMASK) | (data & BPORT1_AB_CR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_IER_maskWrite) {
    bport1_ab_data.IER.value = (bport1_ab_data.IER.value & BPORT1_AB_IER_WRNMASK) | (data & BPORT1_AB_IER_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_LR_maskWrite) {
    bport1_ab_data.LR.value = (bport1_ab_data.LR.value & BPORT1_AB_LR_WRNMASK) | (data & BPORT1_AB_LR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MCHR_maskWrite) {
    bport1_ab_data.MCHR.value = (bport1_ab_data.MCHR.value & BPORT1_AB_MCHR_WRNMASK) | (data & BPORT1_AB_MCHR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MCLR_maskWrite) {
    bport1_ab_data.MCLR.value = (bport1_ab_data.MCLR.value & BPORT1_AB_MCLR_WRNMASK) | (data & BPORT1_AB_MCLR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_MER_maskWrite) {
    bport1_ab_data.MER.value = (bport1_ab_data.MER.value & BPORT1_AB_MER_WRNMASK) | (data & BPORT1_AB_MER_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_RAR_maskWrite) {
    bport1_ab_data.RAR.value = (bport1_ab_data.RAR.value & BPORT1_AB_RAR_WRNMASK) | (data & BPORT1_AB_RAR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_SR_maskWrite) {
    bport1_ab_data.SR.value = (bport1_ab_data.SR.value & BPORT1_AB_SR_WRNMASK) | (data & BPORT1_AB_SR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TAR_maskWrite) {
    bport1_ab_data.TAR.value = (bport1_ab_data.TAR.value & BPORT1_AB_TAR_WRNMASK) | (data & BPORT1_AB_TAR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TCR_maskWrite) {
    bport1_ab_data.TCR.value = (bport1_ab_data.TCR.value & BPORT1_AB_TCR_WRNMASK) | (data & BPORT1_AB_TCR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TDR_maskWrite) {
    bport1_ab_data.TDR.value = (bport1_ab_data.TDR.value & BPORT1_AB_TDR_WRNMASK) | (data & BPORT1_AB_TDR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TER_maskWrite) {
    bport1_ab_data.TER.value = (bport1_ab_data.TER.value & BPORT1_AB_TER_WRNMASK) | (data & BPORT1_AB_TER_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TIR_maskWrite) {
    bport1_ab_data.TIR.value = (bport1_ab_data.TIR.value & BPORT1_AB_TIR_WRNMASK) | (data & BPORT1_AB_TIR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TPR_maskWrite) {
    bport1_ab_data.TPR.value = (bport1_ab_data.TPR.value & BPORT1_AB_TPR_WRNMASK) | (data & BPORT1_AB_TPR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TSR_maskWrite) {
    bport1_ab_data.TSR.value = (bport1_ab_data.TSR.value & BPORT1_AB_TSR_WRNMASK) | (data & BPORT1_AB_TSR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_TTR_maskWrite) {
    bport1_ab_data.TTR.value = (bport1_ab_data.TTR.value & BPORT1_AB_TTR_WRNMASK) | (data & BPORT1_AB_TTR_WRMASK);
}

static PPM_WRITE_CB(bport1_ab_WAR_maskWrite) {
    bport1_ab_data.WAR.value = (bport1_ab_data.WAR.value & BPORT1_AB_WAR_WRNMASK) | (data & BPORT1_AB_WAR_WRMASK);
}

//////////////////////////////// Bus Slave Ports ///////////////////////////////

static void installSlavePorts(void) {
    handles.bport1 = ppmCreateSlaveBusPort("bport1", 4096);

}

//////////////////////////// Memory mapped registers ///////////////////////////

static void installRegisters(void) {

    {
        registerHandle abTSR_reg = ppmCreateRegister(
            "ab_TSR",
            "RTC Time Seconds Register, offset: 0x0 ",
            handles.bport1,
            0x0,
            4,
            read_32,
            bport1_ab_TSR_maskWrite,
            view32,
            &(bport1_ab_data.TSR.value),
            True
        );

        ppmCreateRegisterField(abTSR_reg, "TSR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abTPR_reg = ppmCreateRegister(
            "ab_TPR",
            "RTC Time Prescaler Register, offset: 0x4 ",
            handles.bport1,
            0x4,
            4,
            read_32,
            bport1_ab_TPR_maskWrite,
            view32,
            &(bport1_ab_data.TPR.value),
            True
        );

        ppmCreateRegisterField(abTPR_reg, "TPR", 0, 0, 16, 1, 1);
    }
    {
        registerHandle abTAR_reg = ppmCreateRegister(
            "ab_TAR",
            "RTC Time Alarm Register, offset: 0x8 ",
            handles.bport1,
            0x8,
            4,
            read_32,
            bport1_ab_TAR_maskWrite,
            view32,
            &(bport1_ab_data.TAR.value),
            True
        );

        ppmCreateRegisterField(abTAR_reg, "TAR", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abTCR_reg = ppmCreateRegister(
            "ab_TCR",
            "RTC Time Compensation Register, offset: 0xC ",
            handles.bport1,
            0xc,
            4,
            read_32,
            bport1_ab_TCR_maskWrite,
            view32,
            &(bport1_ab_data.TCR.value),
            True
        );

        ppmCreateRegisterField(abTCR_reg, "CIC", 0, 24, 8, 1, 1);
        ppmCreateRegisterField(abTCR_reg, "CIR", 0, 8, 8, 1, 1);
        ppmCreateRegisterField(abTCR_reg, "TCR", 0, 0, 8, 1, 1);
        ppmCreateRegisterField(abTCR_reg, "TCV", 0, 16, 8, 1, 1);
    }
    {
        registerHandle abCR_reg = ppmCreateRegister(
            "ab_CR",
            "RTC Control Register, offset: 0x10 ",
            handles.bport1,
            0x10,
            4,
            read_32,
            bport1_ab_CR_maskWrite,
            view32,
            &(bport1_ab_data.CR.value),
            True
        );

        ppmCreateRegisterField(abCR_reg, "CLKO", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abCR_reg, "OSCE", 0, 8, 1, 1, 1);
        ppmCreateRegisterField(abCR_reg, "SC16P", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abCR_reg, "SC2P", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abCR_reg, "SC4P", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abCR_reg, "SC8P", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abCR_reg, "SUP", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abCR_reg, "SWR", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abCR_reg, "UM", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abCR_reg, "WPE", 0, 1, 1, 1, 1);
    }
    {
        registerHandle abSR_reg = ppmCreateRegister(
            "ab_SR",
            "RTC Status Register, offset: 0x14 ",
            handles.bport1,
            0x14,
            4,
            read_32,
            bport1_ab_SR_maskWrite,
            view32,
            &(bport1_ab_data.SR.value),
            True
        );

        ppmCreateRegisterField(abSR_reg, "MOF", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abSR_reg, "TAF", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abSR_reg, "TCE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abSR_reg, "TIF", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abSR_reg, "TOF", 0, 1, 1, 1, 1);
    }
    {
        registerHandle abLR_reg = ppmCreateRegister(
            "ab_LR",
            "RTC Lock Register, offset: 0x18 ",
            handles.bport1,
            0x18,
            4,
            read_32,
            bport1_ab_LR_maskWrite,
            view32,
            &(bport1_ab_data.LR.value),
            True
        );

        ppmCreateRegisterField(abLR_reg, "CRL", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abLR_reg, "LRL", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abLR_reg, "MCHL", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abLR_reg, "MCLL", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abLR_reg, "MEL", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abLR_reg, "SRL", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abLR_reg, "TCL", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abLR_reg, "TDL", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abLR_reg, "TEL", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abLR_reg, "TIL", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abLR_reg, "TTL", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abLR_reg, "TTSL", 0, 8, 1, 1, 1);
    }
    {
        registerHandle abIER_reg = ppmCreateRegister(
            "ab_IER",
            "RTC Interrupt Enable Register, offset: 0x1C ",
            handles.bport1,
            0x1c,
            4,
            read_32,
            bport1_ab_IER_maskWrite,
            view32,
            &(bport1_ab_data.IER.value),
            True
        );

        ppmCreateRegisterField(abIER_reg, "MOIE", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abIER_reg, "TAIE", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abIER_reg, "TIIE", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abIER_reg, "TOIE", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abIER_reg, "TSIE", 0, 4, 1, 1, 1);
    }
    {
        registerHandle abTTSR_reg = ppmCreateRegister(
            "ab_TTSR",
            "RTC Tamper Time Seconds Register, offset: 0x20 ",
            handles.bport1,
            0x20,
            4,
            read_32,
            0,
            view32,
            &(bport1_ab_data.TTSR.value),
            True
        );

        ppmCreateRegisterField(abTTSR_reg, "TTS", 0, 0, 32, 1, 0);
    }
    {
        registerHandle abMER_reg = ppmCreateRegister(
            "ab_MER",
            "RTC Monotonic Enable Register, offset: 0x24 ",
            handles.bport1,
            0x24,
            4,
            read_32,
            bport1_ab_MER_maskWrite,
            view32,
            &(bport1_ab_data.MER.value),
            True
        );

        ppmCreateRegisterField(abMER_reg, "MCE", 0, 4, 1, 1, 1);
    }
    {
        registerHandle abMCLR_reg = ppmCreateRegister(
            "ab_MCLR",
            "RTC Monotonic Counter Low Register, offset: 0x28 ",
            handles.bport1,
            0x28,
            4,
            read_32,
            bport1_ab_MCLR_maskWrite,
            view32,
            &(bport1_ab_data.MCLR.value),
            True
        );

        ppmCreateRegisterField(abMCLR_reg, "MCL", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abMCHR_reg = ppmCreateRegister(
            "ab_MCHR",
            "RTC Monotonic Counter High Register, offset: 0x2C ",
            handles.bport1,
            0x2c,
            4,
            read_32,
            bport1_ab_MCHR_maskWrite,
            view32,
            &(bport1_ab_data.MCHR.value),
            True
        );

        ppmCreateRegisterField(abMCHR_reg, "MCH", 0, 0, 32, 1, 1);
    }
    {
        registerHandle abTER_reg = ppmCreateRegister(
            "ab_TER",
            "RTC Tamper Enable Register, offset: 0x30 ",
            handles.bport1,
            0x30,
            4,
            read_32,
            bport1_ab_TER_maskWrite,
            view32,
            &(bport1_ab_data.TER.value),
            True
        );

        ppmCreateRegisterField(abTER_reg, "CTE", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abTER_reg, "DTE", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abTER_reg, "FSE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abTER_reg, "TME", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abTER_reg, "TTE", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abTER_reg, "VTE", 0, 1, 1, 1, 1);
    }
    {
        registerHandle abTDR_reg = ppmCreateRegister(
            "ab_TDR",
            "RTC Tamper Detect Register, offset: 0x34 ",
            handles.bport1,
            0x34,
            4,
            read_32,
            bport1_ab_TDR_maskWrite,
            view32,
            &(bport1_ab_data.TDR.value),
            True
        );

        ppmCreateRegisterField(abTDR_reg, "CTF", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abTDR_reg, "DTF", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abTDR_reg, "FSF", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abTDR_reg, "TMF", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abTDR_reg, "TTF", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abTDR_reg, "VTF", 0, 1, 1, 1, 1);
    }
    {
        registerHandle abTTR_reg = ppmCreateRegister(
            "ab_TTR",
            "RTC Tamper Trim Register, offset: 0x38 ",
            handles.bport1,
            0x38,
            4,
            read_32,
            bport1_ab_TTR_maskWrite,
            view32,
            &(bport1_ab_data.TTR.value),
            True
        );

        ppmCreateRegisterField(abTTR_reg, "CDTH", 0, 6, 3, 1, 1);
        ppmCreateRegisterField(abTTR_reg, "CDTL", 0, 9, 3, 1, 1);
        ppmCreateRegisterField(abTTR_reg, "TDTH", 0, 12, 3, 1, 1);
        ppmCreateRegisterField(abTTR_reg, "TDTL", 0, 15, 3, 1, 1);
        ppmCreateRegisterField(abTTR_reg, "VDTH", 0, 3, 3, 1, 1);
        ppmCreateRegisterField(abTTR_reg, "VDTL", 0, 0, 3, 1, 1);
    }
    {
        registerHandle abTIR_reg = ppmCreateRegister(
            "ab_TIR",
            "RTC Tamper Interrupt Register, offset: 0x3C ",
            handles.bport1,
            0x3c,
            4,
            read_32,
            bport1_ab_TIR_maskWrite,
            view32,
            &(bport1_ab_data.TIR.value),
            True
        );

        ppmCreateRegisterField(abTIR_reg, "CTIE", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abTIR_reg, "DTIE", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abTIR_reg, "FSIE", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abTIR_reg, "TMIE", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abTIR_reg, "TTIE", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abTIR_reg, "VTIE", 0, 1, 1, 1, 1);
    }
    {
        registerHandle abWAR_reg = ppmCreateRegister(
            "ab_WAR",
            "RTC Write Access Register, offset: 0x800 ",
            handles.bport1,
            0x800,
            4,
            read_32,
            bport1_ab_WAR_maskWrite,
            view32,
            &(bport1_ab_data.WAR.value),
            True
        );

        ppmCreateRegisterField(abWAR_reg, "CRW", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abWAR_reg, "IERW", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abWAR_reg, "LRW", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abWAR_reg, "MCHW", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abWAR_reg, "MCLW", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abWAR_reg, "MERW", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abWAR_reg, "SRW", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abWAR_reg, "TARW", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abWAR_reg, "TCRW", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abWAR_reg, "TDRW", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abWAR_reg, "TERW", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abWAR_reg, "TIRW", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abWAR_reg, "TPRW", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abWAR_reg, "TSRW", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abWAR_reg, "TTRW", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abWAR_reg, "TTSW", 0, 8, 1, 1, 1);
    }
    {
        registerHandle abRAR_reg = ppmCreateRegister(
            "ab_RAR",
            "RTC Read Access Register, offset: 0x804 ",
            handles.bport1,
            0x804,
            4,
            read_32,
            bport1_ab_RAR_maskWrite,
            view32,
            &(bport1_ab_data.RAR.value),
            True
        );

        ppmCreateRegisterField(abRAR_reg, "CRR", 0, 4, 1, 1, 1);
        ppmCreateRegisterField(abRAR_reg, "IERR", 0, 7, 1, 1, 1);
        ppmCreateRegisterField(abRAR_reg, "LRR", 0, 6, 1, 1, 1);
        ppmCreateRegisterField(abRAR_reg, "MCHR", 0, 11, 1, 1, 1);
        ppmCreateRegisterField(abRAR_reg, "MCLR", 0, 10, 1, 1, 1);
        ppmCreateRegisterField(abRAR_reg, "MERR", 0, 9, 1, 1, 1);
        ppmCreateRegisterField(abRAR_reg, "SRR", 0, 5, 1, 1, 1);
        ppmCreateRegisterField(abRAR_reg, "TARR", 0, 2, 1, 1, 1);
        ppmCreateRegisterField(abRAR_reg, "TCRR", 0, 3, 1, 1, 1);
        ppmCreateRegisterField(abRAR_reg, "TDRR", 0, 13, 1, 1, 1);
        ppmCreateRegisterField(abRAR_reg, "TERR", 0, 12, 1, 1, 1);
        ppmCreateRegisterField(abRAR_reg, "TIRR", 0, 15, 1, 1, 1);
        ppmCreateRegisterField(abRAR_reg, "TPRR", 0, 1, 1, 1, 1);
        ppmCreateRegisterField(abRAR_reg, "TSRR", 0, 0, 1, 1, 1);
        ppmCreateRegisterField(abRAR_reg, "TTRR", 0, 14, 1, 1, 1);
        ppmCreateRegisterField(abRAR_reg, "TTSR", 0, 8, 1, 1, 1);
    }

}

PPM_NET_CB(reset_Reset) {
    if(value != 0 ) {
        bport1_ab_data.RAR.value = (Uns32)(bport1_ab_data.RAR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000ffff));
        bport1_ab_data.WAR.value = (Uns32)(bport1_ab_data.WAR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000ffff));
        bport1_ab_data.TIR.value = (Uns32)(bport1_ab_data.TIR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TTR.value = (Uns32)(bport1_ab_data.TTR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TDR.value = (Uns32)(bport1_ab_data.TDR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TER.value = (Uns32)(bport1_ab_data.TER.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MCHR.value = (Uns32)(bport1_ab_data.MCHR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MCLR.value = (Uns32)(bport1_ab_data.MCLR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.MER.value = (Uns32)(bport1_ab_data.MER.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TTSR.value = (Uns32)(bport1_ab_data.TTSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.IER.value = (Uns32)(bport1_ab_data.IER.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000007));
        bport1_ab_data.LR.value = (Uns32)(bport1_ab_data.LR.value & ~(0xffffffff)) | ((0xffffffff) & (0x0000ffff));
        bport1_ab_data.SR.value = (Uns32)(bport1_ab_data.SR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000001));
        bport1_ab_data.CR.value = (Uns32)(bport1_ab_data.CR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TCR.value = (Uns32)(bport1_ab_data.TCR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TAR.value = (Uns32)(bport1_ab_data.TAR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TPR.value = (Uns32)(bport1_ab_data.TPR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
        bport1_ab_data.TSR.value = (Uns32)(bport1_ab_data.TSR.value & ~(0xffffffff)) | ((0xffffffff) & (0x00000000));
    }
}

PPM_DOC_FN(installDocs){

    ppmDocNodeP Root1_node = ppmDocAddSection(0, "Root");
    {
        ppmDocNodeP doc2_node = ppmDocAddSection(Root1_node, "Description");
        ppmDocAddText(doc2_node, "Model of the RTC peripheral used on the Freescale Kinetis platform");
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

