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
//
////////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "pse.igen.h"

#define PREFIX "SDHC"

#define STR(_name)      (bport1_ab_data. _name)

// Common naming here and in semihost
#define control    STR(uSDHC_SYS_CTRL)
#define protocol   STR(uSDHC_PROT_CTRL)
#define state      STR(uSDHC_PRES_STATE)
#define watermark  STR(uSDHC_WTMK_LVL)

#define cmdarg     STR(uSDHC_CMD_ARG)
#define command    STR(uSDHC_CMD_XFR_TYP)
#define response0  STR(uSDHC_CMD_RSP0)
#define response1  STR(uSDHC_CMD_RSP1)
#define response2  STR(uSDHC_CMD_RSP2)
#define response3  STR(uSDHC_CMD_RSP3)

#define dbaddr     STR(uSDHC_DS_ADDR)

#define status     STR(uSDHC_INT_STATUS)
#define enable     STR(uSDHC_INT_STATUS_EN)
#define mask       STR(uSDHC_INT_SIGNAL_EN)


////////////////////////////// Native functions  ///////////////////////////////

// Intercepted functions

FUNCTOHOST(Uns32, initNative,
    void        *addressRegisters,
    void        *fifoBase,
    Uns32        fifoSize,
    const char  *driveName,
    Uns32        driveNameLen,
    Uns32        delta,
    ppmNetHandle irq,
    ppmNetHandle cardin,
    ppmNetHandle wprot
)

FUNCTOHOST(void, startSDNative, void)

FUNCTOHOST(void, setNativeDiagnostics, Uns32 *diagP, Uns32 currentDiag)

FUNCTOHOST(void, sendCommandNative, void)

FUNCTOHOST(void, writeDCNative, void)

FUNCTOHOST(void, setupDMABufferInfo, void)

FUNCTOHOST(void, updateBytCnt, Uns32 val)


////////////////////////////// Utility functions  //////////////////////////////

static void updateInterrupts() {
    static Bool currentInterrupt = False;

    // clear bits that are not enabled
    status.value &= enable.value;

    // generate any interupts
    Bool interrupt = (status.value & enable.value) && True;

    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX, "%s: Status = %08x, enable = %08x, signal = %08x, int = %u",
                __FUNCTION__, status.value, enable.value, mask.value, interrupt);
    }

    if(interrupt != currentInterrupt) {
        ppmWriteNet(handles.interrupt, interrupt);
        currentInterrupt = interrupt;
    }

}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_READ_CB(regNoDefinitionRead) {
    Uns32 offset = addr - handles.bport1;
    bhmMessage("W", PREFIX, "No Read Register Defined at offset 0x%04x", offset);
    return 0;
}

PPM_WRITE_CB(regNoDefinitionWrite) {
    Uns32 offset = addr - handles.bport1;
    bhmMessage("W", PREFIX, "No Write Register Defined at offset 0x%04x", offset);
}

PPM_NET_CB(resetFunction) {
    if(PSE_DIAG_HIGH) {
      bhmMessage("I", PREFIX, "Reset uSDHC");
    }

    reset_resetNet(1,0);
}

PPM_REG_READ_CB(ReaduSDHC_SYS_CTRL) {
    Uns32 data  = *(Uns32*)user;
    Uns32 shift = (PTR_TO_UNS32(addr) & 3) * 8;
    switch(bytes){
    case 4:
        // no shift
        break;
    case 2:
        // TODO: check valid shift?
    case 1:
        // shift data into lower part
        data  = data >> shift;
        break;
    default:
        bhmMessage("W", PREFIX, "%s: unsupported access size %u bytes",
                __FUNCTION__, bytes);
        break;
    }
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_RD", "%s: bytes %u shift %u 0x%08x",
                __FUNCTION__, bytes, shift, data);
    }
    return data;
}

PPM_REG_WRITE_CB(WriteuSDHC_CMD_ARG) {
    if(state.bits.CIHB) {
        bhmMessage("W", PREFIX "_WRI", "%s: Attempt to write CMD ARG 0x%08x when inhibit active",
                        __FUNCTION__, data);
    } else {
        *(Uns32*)user = data;
        if(PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX "_WR", "%s: 0x%08x",
                    __FUNCTION__, *(Uns32*)user);
        }
    }
}

PPM_REG_WRITE_CB(WriteuSDHC_CMD_XFR_TYP) {
    if(state.bits.CIHB) {
        bhmMessage("W", PREFIX "_WRI", "%s: Attempt to write CMD XFR TYP 0x%08x when inhibit active",
                        __FUNCTION__, data & 0x3ffb0000);
    } else {

        *(Uns32*)user = (*(Uns32*)user & 0xc004ffff) | (data & 0x3ffb0000);

        if(PSE_DIAG_HIGH) {
            const char *cmdType="Normal";
            switch (command.bits.CMDTYP) {
                case 3: cmdType="Abort CMD12 CND52"; break;
                case 2: cmdType="Resume CMD52"; break;
                case 1: cmdType="Suspend CMD52"; break;
            }
            const char *rspType="No Response";
            switch (command.bits.RSPTYP) {
                case 3: rspType="Response Length 48, check busy"; break;
                case 2: rspType="Response Length 48"; break;
                case 1: rspType="Response Length 136"; break;
            }
            bhmMessage("I", PREFIX "_WR", "%s: 0x%08x "
                    "CMDINX %u "
                    "CMDTYP %u (%s) "
                    "DPSEL %u "
                    "CICEN %u "
                    "CCCEN %u "
                    "RSPTYP %u (%s)",
                    __FUNCTION__, *(Uns32*)user,
                    command.bits.CMDINX,
                    command.bits.CMDTYP,
                    cmdType,
                    command.bits.DPSEL,
                    command.bits.CICEN,
                    command.bits.CCCEN,
                    command.bits.RSPTYP,
                    rspType);
        }
        // Set inhibit as soon as transfer type set and cleared on response
        state.bits.CIHB = 1;

        // Process the command
        sendCommandNative();
        updateInterrupts();

    }
}

PPM_REG_WRITE_CB(WriteuSDHC_FORCE_EVENT) {
    // YOUR CODE HERE (WriteuSDHC_FORCE_EVENT)
    *(Uns32*)user = (*(Uns32*)user & 0x6a80ff60) | (data & 0x957f009f);
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_WR", "%s: 0x%08x", __FUNCTION__, *(Uns32*)user);
    }
}

PPM_REG_WRITE_CB(WriteuSDHC_INT_SIGNAL_EN) {
    // YOUR CODE HERE (WriteuSDHC_INT_SIGNAL_EN)
    *(Uns32*)user = (*(Uns32*)user & 0xea80ae00) | (data & 0x157f51ff);
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_WR", "%s: 0x%08x", __FUNCTION__, *(Uns32*)user);
    }

    updateInterrupts();
}

PPM_REG_WRITE_CB(WriteuSDHC_INT_STATUS) {
    // YOUR CODE HERE (WriteuSDHC_INT_STATUS)
    *(Uns32*)user = (*(Uns32*)user & 0xea80ae00) | (data & 0x157f51ff);
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_WR", "%s: 0x%08x", __FUNCTION__, *(Uns32*)user);
    }

    updateInterrupts();
}

PPM_REG_WRITE_CB(WriteuSDHC_INT_STATUS_EN) {
    // YOUR CODE HERE (WriteuSDHC_INT_STATUS_EN)
    *(Uns32*)user = (*(Uns32*)user & 0xea80ae00) | (data & 0x157f51ff);
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_WR", "%s: 0x%08x", __FUNCTION__, *(Uns32*)user);
    }

    updateInterrupts();
}

PPM_REG_WRITE_CB(WriteuSDHC_PROT_CTRL) {
    *(Uns32*)user = (*(Uns32*)user & 0x80e0fc00) | (data & 0x7f1f03ff);

    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_WR", "%s: 0x%08x "
                "NON_EXACT_BLK_RD %u "
                "BURST_LEN_EN %u "
                "WECRM %u "
                "WECINS %u "
                "WECINT %u "
                "RD_DONE_NO_8CLK  %u "
                "IABG %u "
                "RWCTL %u "
                "CREQ %u "
                "SABGREQ %u "
                "DMASEL %u "
                "CDSS %u "
                "CDTL %u "
                "EMODE %u "
                "D3CD %u "
                "DTW %u "
                "LCTL %u ",
                __FUNCTION__, *(Uns32*)user,
                protocol.bits.NON_EXACT_BLK_RD,
                protocol.bits.BURST_LEN_EN,
                protocol.bits.WECRM,
                protocol.bits.WECINS,
                protocol.bits.WECINT,
                protocol.bits.RD_DONE_NO_8CLK,
                protocol.bits.IABG,
                protocol.bits.RWCTL,
                protocol.bits.CREQ,
                protocol.bits.SABGREQ,
                protocol.bits.DMASEL,
                protocol.bits.CDSS,
                protocol.bits.CDTL,
                protocol.bits.EMODE,
                protocol.bits.D3CD,
                protocol.bits.DTW,
                protocol.bits.LCTL);
    }
}

PPM_REG_WRITE_CB(WriteuSDHC_SYS_CTRL) {
    *(Uns32*)user = (*(Uns32*)user & 0xf070000f) | (data & 0xf8ffff0);
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_WR", "%s: 0x%08x "
                "INITA %u "
                "RSTD %u "
                "RSTC %u "
                "RSTA %u "
                "IPP_RST_N %u "
                "DTOCV %u "
                "SDCLKFS %u "
                "DVS %u",
                __FUNCTION__, *(Uns32*)user,
                control.bits.INITA,
                control.bits.RSTD,
                control.bits.RSTC,
                control.bits.RSTA,
                control.bits.IPP_RST_N,
                control.bits.DTOCV,
                control.bits.SDCLKFS,
                control.bits.DVS);
    }

    // INTA self clears after 80 clocks (clear immediately TODO: Check ok)
    if (control.bits.INITA){
        control.bits.INITA = 0;

    }

    // TODO: Do we need to delay before clearing bits e.g. clock stable after changes etc
    if(control.bits.RSTA) {
        control.bits.RSTA = 0;
        status.value = 0;
        enable.value = 0;
        mask.value = 0;

    } else if(control.bits.RSTD) {
        control.bits.RSTD = 0;
        state.value = 0;
        // TODO: Other registers/bits cleared

    } else if(control.bits.RSTC) {
        control.bits.RSTC = 0;
        state.bits.CIHB = 0;
        status.bits.CC = 0;
    }

}

PPM_REG_WRITE_CB(WriteuSDHC_WTMK_LVL) {
    // YOUR CODE HERE (WriteuSDHC_WTMK_LVL)
    *(Uns32*)user = (*(Uns32*)user & 0xe000e000) | (data & 0x1fff1fff);
    if(PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_WR", "%s: 0x%08x "
                    "WR_BRST_LEN %u "
                    "WR_WML %u "
                    "RD_BRST_LEN %u "
                    "RD_WML %u",
                    __FUNCTION__, *(Uns32*)user,
                    watermark.bits.WR_BRST_LEN,
                    watermark.bits.WR_WML,
                    watermark.bits.RD_BRST_LEN,
                    watermark.bits.RD_WML);
    }

}

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    char driveName[BHM_MAX_PATH];
    if(bhmStringParamValue("SD_DRIVE", driveName, sizeof(driveName))) {
        bhmMessage("I", PREFIX, "SD Drive '%s' (%d) %x", driveName, (Uns32)strlen(driveName), PTR_TO_UNS32(handles.bport1));
    }

    Bool delta;
    bhmBoolParamValue("SD_DRIVE_DELTA", &delta);
    if (delta == True) {
        bhmMessage("I", PREFIX, "SD Drive Delta Enabled");
    }

    // 128 word temporary buffer
    char* buffer = malloc(128*sizeof(Uns32));

    setNativeDiagnostics(&diagnosticLevel, diagnosticLevel);
    initNative(
        &bport1_ab_data,
        buffer, 128*sizeof(Uns32),
        driveName, strlen(driveName), delta,
        handles.interrupt, handles.CD, handles.WP
    );

    // Perform a reset as native memory mapping will overwrite
    reset_resetNet(1,0);

    // Indicate Card available and writable
    state.bits.WPSPL = 1 ;    // write enabled
    state.bits.CDPL = 1;      // card present
    state.bits.CINST = 1;     // card inserted

    startSDNative();

}

PPM_DESTRUCTOR_CB(destructor) {
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}

