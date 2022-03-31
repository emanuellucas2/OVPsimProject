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
//                          Fri Jan  6 11:38:59 2012
//
////////////////////////////////////////////////////////////////////////////////

#include <string.h>

#include "pse.igen.h"

#define PREFIX "DEVCFG"

// Locked state for registers
static Bool DEVCI_Locked = False;
#define UNLOCKCODE 0x757BDF0D

typedef enum {
    ZC706,
    ZC702
} boardE;

boardE board;   // initialized in constructor

// include common pmbus access functions

#include "xadc_pm.user.h"

// create the monitor structure
vmonT vmon;

// required rail indexes for monitored voltages
#define VCCINT_RAIL     0
#define VCCPINT_RAIL    1

// include common powermonitor functions
#include "ovpworld.org/modelSupport/powermonitor/1.0/pse/powermonitor.user.c.h"

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

PPM_REG_READ_CB(ReadCFG) {
    // YOUR CODE HERE (ReadCFG)
    return *(Uns32*)user;
}

PPM_REG_READ_CB(ReadCTRL) {
    // YOUR CODE HERE (ReadCTRL)
    return *(Uns32*)user;
}

PPM_REG_READ_CB(ReadDMA_DEST_LEN) {
    // YOUR CODE HERE (ReadDMA_DEST_LEN)
    return *(Uns32*)user;
}

PPM_REG_READ_CB(ReadDMA_DST_ADDR) {
    // YOUR CODE HERE (ReadDMA_DST_ADDR)
    return *(Uns32*)user;
}

PPM_REG_READ_CB(ReadDMA_SRC_ADDR) {
    // YOUR CODE HERE (ReadDMA_SRC_ADDR)
    return *(Uns32*)user;
}

PPM_REG_READ_CB(ReadDMA_SRC_LEN) {
    // YOUR CODE HERE (ReadDMA_SRC_LEN)
    return *(Uns32*)user;
}

PPM_REG_READ_CB(ReadINT_MASK) {
    // YOUR CODE HERE (ReadINT_MASK)
    return *(Uns32*)user;
}

PPM_REG_READ_CB(ReadINT_STS) {
    // YOUR CODE HERE (ReadINT_STS)
    return *(Uns32*)user;
}

PPM_REG_READ_CB(ReadLOCK) {
    // YOUR CODE HERE (ReadLOCK)
    return *(Uns32*)user;
}

PPM_REG_READ_CB(ReadMCTRL) {
    // YOUR CODE HERE (ReadMCTRL)
    return *(Uns32*)user;
}

PPM_REG_READ_CB(ReadMULTIBOOT_ADDR) {
    // YOUR CODE HERE (ReadMULTIBOOT_ADDR)
    return *(Uns32*)user;
}

PPM_REG_READ_CB(ReadROM_SHADOW) {
    // YOUR CODE HERE (ReadROM_SHADOW)
    return *(Uns32*)user;
}

PPM_REG_READ_CB(ReadSTATUS) {
    // YOUR CODE HERE (ReadSTATUS)
    return *(Uns32*)user;
}

PPM_REG_READ_CB(ReadUNLOCK) {
    // YOUR CODE HERE (ReadUNLOCK)
    return *(Uns32*)user;
}

PPM_REG_WRITE_CB(WriteCFG) {
    // YOUR CODE HERE (WriteCFG)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(WriteCTRL) {
    bport1_ab_dataT localNew, localCurrent;

    localCurrent.CTRL.value = *(Uns32*)user;
    localNew.CTRL.value     = data;
    // Check for locked bits and revert to current settings
    if(bport1_ab_data.LOCK.bits.AES_FUSE_LOCK) {
        localNew.CTRL.bits.PCFG_AES_FUSE = localCurrent.CTRL.bits.PCFG_AES_FUSE;
    }
    if(bport1_ab_data.LOCK.bits.AES_EN_LOCK) {
        localNew.CTRL.bits.PCFG_AES_EN = localCurrent.CTRL.bits.PCFG_AES_EN;
    }
    if(bport1_ab_data.LOCK.bits.SEU_LOCK) {
        localNew.CTRL.bits.SEU_EN = localCurrent.CTRL.bits.SEU_EN;
    }
    if(bport1_ab_data.LOCK.bits.SEC_LOCK) {
        localNew.CTRL.bits.SEC_EN = localCurrent.CTRL.bits.SEC_EN;
    }
    if(bport1_ab_data.LOCK.bits.DBG_LOCK) {
        localNew.CTRL.bits.SPNIDEN = localCurrent.CTRL.bits.SPNIDEN;
        localNew.CTRL.bits.SPIDEN  = localCurrent.CTRL.bits.SPIDEN;
        localNew.CTRL.bits.NIDEN   = localCurrent.CTRL.bits.NIDEN;
        localNew.CTRL.bits.DBGEN   = localCurrent.CTRL.bits.DBGEN;
        localNew.CTRL.bits.DAP_EN  = localCurrent.CTRL.bits.DAP_EN;
    }

    *(Uns32*)user = localNew.CTRL.value;
}

PPM_REG_WRITE_CB(WriteDMA_DEST_LEN) {
    // YOUR CODE HERE (WriteDMA_DEST_LEN)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(WriteDMA_DST_ADDR) {
    // YOUR CODE HERE (WriteDMA_DST_ADDR)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(WriteDMA_SRC_ADDR) {
    // YOUR CODE HERE (WriteDMA_SRC_ADDR)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(WriteDMA_SRC_LEN) {
    // YOUR CODE HERE (WriteDMA_SRC_LEN)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(WriteINT_MASK) {
    // YOUR CODE HERE (WriteINT_MASK)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(WriteINT_STS) {
    // YOUR CODE HERE (WriteINT_STS)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(WriteLOCK) {
    *(Uns32*)user |= data;
}

PPM_REG_WRITE_CB(WriteMCTRL) {
    // YOUR CODE HERE (WriteMCTRL)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(WriteMULTIBOOT_ADDR) {
    // YOUR CODE HERE (WriteMULTIBOOT_ADDR)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(WriteROM_SHADOW) {
    // YOUR CODE HERE (WriteROM_SHADOW)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(WriteSTATUS) {
    // YOUR CODE HERE (WriteSTATUS)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(WriteUNLOCK) {
    if (data == UNLOCKCODE) {
        if(PSE_DIAG_LOW)
            bhmMessage("I", PREFIX "_UNLCK", "DEVCI Unlock code (0x%08x)", data);
        DEVCI_Locked = False;
    } else {
        if(PSE_DIAG_LOW)
            bhmMessage("I", PREFIX "_UNLCK", "DEVCI Failed to Unlock code 0x%08x", data);
    }
    *(Uns32*)user = 0;
}

//
// XADC Interface
//

Uns32 xadcMux = 0;
PPM_NET_CB(xadcMuxSelect) {
    // Select the XADC MUX
    xadcMux = value;
    if(PSE_DIAG_LOW)
        bhmMessage("I", PREFIX "_XADCMUX", "Select %d", xadcMux);

}

// Internal XADC Registers
#define XADCPS_TEMP_OFFSET    0x00
#define XADCPS_VCCINT_OFFSET  0x01
#define XADCPS_VCCAUX_OFFSET  0x02
#define XADCPS_VNVP_OFFSET    0x03
#define XADCPS_VREFP_OFFSET   0x04
#define XADCPS_VREFN_OFFSET   0x05
#define XADCPS_VBRAM_OFFSET   0x06
#define XADCPS_VCCPINT_OFFSET 0x0D
#define XADCPS_VCCPAUX_OFFSET 0x0E
// zc702 external MUX selected
#define XADCPS_AUX01_OFFSET   0x11
// zc702 jumper selected input
#define XADCPS_AUX00_OFFSET   0x10
#define XADCPS_AUX08_OFFSET   0x17
// min/max
#define XADCPS_MAX_TEMP_OFFSET     0x20
#define XADCPS_MAX_VCCINT_OFFSET   0x21
#define XADCPS_MAX_VCCAUX_OFFSET   0x22
#define XADCPS_MAX_VBRAM_OFFSET    0x23
#define XADCPS_MIN_TEMP_OFFSET     0x24
#define XADCPS_MIN_VCCINT_OFFSET   0x25
#define XADCPS_MIN_VCCAUX_OFFSET   0x26
#define XADCPS_MIN_VBRAM_OFFSET    0x27
#define XADCPS_MAX_VCCPINT_OFFSET  0x28
#define XADCPS_MAX_VCCPAUX_OFFSET  0x29
#define XADCPS_MIN_VCCPINT_OFFSET  0x2C
#define XADCPS_MIN_VCCPAUX_OFFSET  0x2D
#define XADCPS_FLAG_OFFSET         0x3F

// Set the external values above the internals in memory (zc706 only)
#define XADCPS_LAST_OFFSET 0x40

#define XADCPS_VCCINT_CURRENT_OFFSET    XADCPS_LAST_OFFSET+0
#define XADCPS_VCCAUX_CURRENT_OFFSET    XADCPS_LAST_OFFSET+1
#define XADCPS_VCC1V5_OFFSET            XADCPS_LAST_OFFSET+2
#define XADCPS_VCC1V5_CURRENT_OFFSET    XADCPS_LAST_OFFSET+3
#define XADCPS_VADJFPGA_OFFSET          XADCPS_LAST_OFFSET+4
#define XADCPS_VADJFPGA_CURRENT_OFFSET  XADCPS_LAST_OFFSET+5
#define XADCPS_VCC3V3_OFFSET            XADCPS_LAST_OFFSET+6
#define XADCPS_VCC3V3_CURRENT_OFFSET    XADCPS_LAST_OFFSET+7
#define XADCPS_MUX_LAST_OFFSET          XADCPS_LAST_OFFSET+8

// ADC init default values (written to ADC memory)
Uns16 xadcInitData[] = {
        // Internal Measurements
    [XADCPS_TEMP_OFFSET   ] = 39680,    // should result in temp of about 32oC
    [XADCPS_VCCINT_OFFSET ] = 21845,    // voltage max 0xfff0 (65520) = 3V
    [XADCPS_VNVP_OFFSET   ] = 32768,
    [XADCPS_VCCAUX_OFFSET ] = 32768,
    [XADCPS_VBRAM_OFFSET  ] = 39322,
    [XADCPS_VCCPINT_OFFSET] = 21855,
    [XADCPS_VCCPAUX_OFFSET] = 32768,
    [XADCPS_AUX00_OFFSET  ] =    66,
    [XADCPS_AUX01_OFFSET  ] =    66,
    [XADCPS_AUX08_OFFSET  ] =    66,
    // Min/Max defaults
    // TODO: Should these be updated when values read?
    [XADCPS_MAX_TEMP_OFFSET   ] = 0x0000,
    [XADCPS_MAX_VCCINT_OFFSET ] = 0x0000,
    [XADCPS_MAX_VCCAUX_OFFSET ] = 0x0000,
    [XADCPS_MAX_VBRAM_OFFSET  ] = 0x0000,
    [XADCPS_MIN_TEMP_OFFSET   ] = 0xfff0,
    [XADCPS_MIN_VCCINT_OFFSET ] = 0xfff0,
    [XADCPS_MIN_VCCAUX_OFFSET ] = 0xfff0,
    [XADCPS_MIN_VBRAM_OFFSET  ] = 0xfff0,
    [XADCPS_MAX_VCCPINT_OFFSET] = 0xfff0,
    [XADCPS_MAX_VCCPAUX_OFFSET] = 0xfff0,
    [XADCPS_MIN_VCCPINT_OFFSET] = 0xfff0,
    [XADCPS_MIN_VCCPAUX_OFFSET] = 0xfff0,
    // External Measurements (zc706) via XADCPS_AUX01_OFFSET
    // TODO: Add real values for initialization
    [XADCPS_VCCINT_CURRENT_OFFSET  ] = 21845,
    [XADCPS_VCCAUX_CURRENT_OFFSET  ] = 21745,
    [XADCPS_VCC1V5_OFFSET          ] = 21645,
    [XADCPS_VCC1V5_CURRENT_OFFSET  ] = 21545,
    [XADCPS_VADJFPGA_OFFSET        ] = 21445,
    [XADCPS_VADJFPGA_CURRENT_OFFSET] = 21345,
    [XADCPS_VCC3V3_OFFSET          ] = 21245,
    [XADCPS_VCC3V3_CURRENT_OFFSET  ] = 21145
    // External Measurements (zc702) on header
    // TODO: Add mechanism to define values specified on header
};


#define FIFOBUFFERLENGTH 16
#define DUMMYACCESSCOUNT  1
Uns32 xadcReadData[FIFOBUFFERLENGTH];   // filled with data when commands received
Uns32 xadcReadPtrIn  = 0;               // position to add data (XADCIF_CMDFIFO)
Uns32 xadcReadPtrOut = 0;               // position to read data (XADCIF_RDFIFO)
Uns32 dummyAccess    = DUMMYACCESSCOUNT;
Bool  full           = False;
#define DUMMYWORD         0

Uns32 getFifoCount() {
    Uns32 count = 0;

    if ((xadcReadPtrIn == xadcReadPtrOut) && full) {

        count = FIFOBUFFERLENGTH;

    } else if (xadcReadPtrIn < xadcReadPtrOut) {

        count = FIFOBUFFERLENGTH - (xadcReadPtrOut - xadcReadPtrIn);

    } else if (xadcReadPtrIn > xadcReadPtrOut) {

        count = xadcReadPtrIn - xadcReadPtrOut;

    }
    if (PSE_DIAG_HIGH) {
        bhmMessage("I", PREFIX "_CNT","FIFO count %d", count);
    }

    return count;
}

void updateInterrupts() {
    Uns32 intState = bport1_ab_data.XADCIF_INT_STS.value & ~bport1_ab_data.XADCIF_INT_MASK.value;
    static Uns32 intStateLast = 0;

    if(intState != intStateLast) {
        intStateLast = intState;
        if (PSE_DIAG_MEDIUM) {
            bhmMessage("I", PREFIX "_INT","Write Interrupt (status 0x%04x / mask 0x%04x)",
                    bport1_ab_data.XADCIF_INT_STS.value,
                    bport1_ab_data.XADCIF_INT_MASK.value);
        }
        if(intState) {
            // set
            ppmWriteNet(handles.intOut, 1);
        } else {
            // clear
            ppmWriteNet(handles.intOut, 0);
        }
    }
}

PPM_REG_READ_CB(ReadXADCIF_CFG) {

    return *(Uns32*)user;
}

PPM_REG_READ_CB(ReadXADCIF_INT_MASK) {

    return *(Uns32*)user;
}

PPM_REG_READ_CB(ReadXADCIF_INT_STS) {

    return *(Uns32*)user;
}

PPM_REG_READ_CB(ReadXADCIF_MCTL) {

    return *(Uns32*)user;
}

PPM_REG_READ_CB(ReadXADCIF_MSTS) {

    return *(Uns32*)user;
}

PPM_REG_READ_CB(ReadXADCIF_RDFIFO) {
    // check how many dummy accesses at start
    if(dummyAccess) {
        dummyAccess--;
        *(Uns32*)user = DUMMYWORD;
    } else {
        *(Uns32*)user = xadcReadData[xadcReadPtrOut];

        if(PSE_DIAG_MEDIUM)
            bhmMessage("I", PREFIX "_RDF", "ADC Read %d Data 0x%04x (%d)",
                    xadcReadPtrOut,
                    (Uns16)xadcReadData[xadcReadPtrOut],
                    (Uns16)xadcReadData[xadcReadPtrOut]);

        xadcReadPtrOut++;
        if (xadcReadPtrOut >= FIFOBUFFERLENGTH) {
            xadcReadPtrOut = 0;
        }
        full = False;
    }
    Uns32 count = getFifoCount();
    if (count > bport1_ab_data.XADCIF_CFG.bits.DFIFOTH) {
        // Data FIFO Level Threshold
        bport1_ab_data.XADCIF_INT_STS.bits.DFIFO_GTH = 1;
        updateInterrupts();
    }
    return *(Uns32*)user;
}

PPM_REG_WRITE_CB(WriteXADCIF_CFG) {
    // YOUR CODE HERE (WriteXADCIF_CFG)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(WriteXADCIF_CMDFIFO) {

    *(Uns32*)user = data;
    // command FIFO word definition
    // 29:26 CMD 0000 No Operation 0001 DRP Read 0010 DRP Write
    // 25:16 DRP Address
    // 15:00 DRP Data
    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX "_CMDF", "Command %s Address 0x%04x Data 0x%04x"
                ,bport1_ab_data.XADCIF_CMDFIFO.bits.CMD == 0 ? "NOP" :
                 bport1_ab_data.XADCIF_CMDFIFO.bits.CMD == 1 ? "RD" :
                 bport1_ab_data.XADCIF_CMDFIFO.bits.CMD == 2 ? "WR" : "UDEF"
                ,bport1_ab_data.XADCIF_CMDFIFO.bits.ADDR
                ,bport1_ab_data.XADCIF_CMDFIFO.bits.DATA);

    // Read ADC Data Channel
    Uns16 adcData = 0;
    Uns32 address = bport1_ab_data.XADCIF_CMDFIFO.bits.ADDR;
    if(bport1_ab_data.XADCIF_CMDFIFO.bits.CMD == 1) {
        // Only read data if this was a read command
        Bool ok = False;

        //
        // Some voltage rails can be configured to access power monitor library
        // Valid indexes are            supported config rail number
        //    XADCPS_TEMP_OFFSET
        //    XADCPS_VCCINT_OFFSET      0
        //    XADCPS_VCCAUX_OFFSET
        //    XADCPS_VBRAM_OFFSET
        //    XADCPS_VCCPINT_OFFSET     1
        //    XADCPS_VCCPAUX_OFFSET
        //    XADCPS_VNVP_OFFSET

        if ((address == XADCPS_VCCINT_OFFSET) && vmon.voltage[VCCINT_RAIL].poil) {
            adcData = getRailValue(vmon.voltage[VCCINT_RAIL].data.ref, vmon.voltage[VCCINT_RAIL].data.value, VOLTAGE, XADC_VOLTAGE_SUPPLY);
            if(PSE_DIAG_HIGH)
                bhmMessage("I", PREFIX "_VM0", "VCCINT %d -> %d",vmon.voltage[VCCINT_RAIL].data.value, adcData);
            ok = True;
            vmon.voltage[VCCINT_RAIL].data.value = adcData;
        } else if ((address == XADCPS_VCCPINT_OFFSET) && vmon.voltage[VCCPINT_RAIL].poil) {
            adcData = getRailValue(vmon.voltage[VCCPINT_RAIL].data.ref, vmon.voltage[VCCPINT_RAIL].data.value, VOLTAGE, XADC_VOLTAGE_SUPPLY);
            if(PSE_DIAG_HIGH)
                bhmMessage("I", PREFIX "_VM1", "VCCPINT %d -> %d",vmon.voltage[VCCPINT_RAIL].data.value, adcData);
            ok = True;
            vmon.voltage[VCCPINT_RAIL].data.value = adcData;

        } else if ((address == XADCPS_TEMP_OFFSET) && vmon.tempSensor.poil) {
            adcData = getRailValue(vmon.tempSensor.data.ref, vmon.tempSensor.data.value, TEMPERATURE, XADC_TEMPERATURE);
            if(PSE_DIAG_HIGH)
                bhmMessage("I", PREFIX "_VM2", "TEMP %d -> %d",vmon.tempSensor.data.value, adcData);
            ok = True;
            vmon.tempSensor.data.value = adcData;

        } else if (handles.xadc) {
            // Perform dummy access if ADC channel memory connected
            if((address == XADCPS_AUX01_OFFSET) && (board == ZC706)) {
                // external values (zc706 only)
                if(PSE_DIAG_HIGH) bhmMessage("I", PREFIX "_VD_AUX", "ADC MUX address %d adc %d", xadcMux, adcData);
                ok = ppmReadAddressSpace(handles.xadc, (XADCPS_LAST_OFFSET+xadcMux)*sizeof(Uns16), sizeof(Uns16), &adcData);
            } else {
                if(PSE_DIAG_HIGH) bhmMessage("I", PREFIX "_VD", "ADC address %d", address);
                ok = ppmReadAddressSpace(handles.xadc, address*sizeof(Uns16), sizeof(Uns16), &adcData);
            }
        }
        if(!ok && PSE_DIAG_LOW)
            bhmMessage("W", PREFIX "_CMDF", "Failed to read XADC data");
    }

    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX "_CMDF", "ADC Channel %d Read %d Data 0x%04x (%d)",
                            address, xadcReadPtrIn, adcData, adcData);

    xadcReadData[xadcReadPtrIn] = (Uns32)adcData;

    xadcReadPtrIn++;
    if (xadcReadPtrIn >= FIFOBUFFERLENGTH) {
        xadcReadPtrIn = 0;
    }

    Uns32 count = getFifoCount();
    if (count <= bport1_ab_data.XADCIF_CFG.bits.CFIFOTH) {
        // Data FIFO Level Threshold
        bport1_ab_data.XADCIF_INT_STS.bits.CFIFO_LTH = 1;
        updateInterrupts();
    }

    if (xadcReadPtrIn == xadcReadPtrOut) {
        full = True;
        if(PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX "_CMDF", "ADC Channel %d Full", address);
    }
}

PPM_REG_WRITE_CB(WriteXADCIF_INT_MASK) {
    // YOUR CODE HERE (WriteXADCIF_INT_MASK)
    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(WriteXADCIF_INT_STS) {
    // Clear interrupt with bit set
    Uns32 currentStatus = *(Uns32*)user;

    *(Uns32*)user = currentStatus & ~data;
    updateInterrupts();
}

PPM_REG_WRITE_CB(WriteXADCIF_MCTL) {
    // YOUR CODE HERE (WriteXADCIF_MCTL)
    *(Uns32*)user = data;

    if(bport1_ab_data.XADCIF_MCTL.bits.RESET) {
        if(PSE_DIAG_LOW)
            bhmMessage("I", PREFIX "_MCTL", "XADC Reset");

        xadcReadPtrIn  = 0;                 // position to add data (XADCIF_CMDFIFO)
        xadcReadPtrOut = 0;                 // position to read data (XADCIF_RDFIFO)
        dummyAccess    = DUMMYACCESSCOUNT;  // count of dummy accesses to provide
    }
}



PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    // Read board being used (zc702, zc706)
    char boardParam[32];
    bhmStringParamValue("board", boardParam, sizeof(boardParam));
    // board parameter has been set
    if      (strcmp(boardParam, "zc706") == 0)              board = ZC706;
    else if (strcmp(boardParam, "zc702") == 0)              board = ZC702;
    else if (strcmp(boardParam, "PublicDemonstrator") == 0) board = ZC702;
    else {
        bhmMessage("W", PREFIX "_BP", "Parameter 'board' set to '%s' is not recognized."
                                      " Use 'zc706' or 'zc702' or 'PublicDemonstrator (zc702)'", boardParam);
        board = ZC706;
    }

    // memory containing dummy values for xADC values
    if(handles.xadc) {
        if(PSE_DIAG_LOW)
            bhmMessage("I", PREFIX "_CN", "Initializing XADC Data");
        Bool ok = True;

        Uns32 i;
        // Internal Temperature and Voltage to XADCPS_LAST_OFFSET
        Uns32 last = XADCPS_LAST_OFFSET;
        // External Temperature, Voltage and Current (zc706 only)
        if (board == ZC706) last = XADCPS_MUX_LAST_OFFSET;

        for (i=0 ; i<last ; i++) {
            Uns16 data = xadcInitData[i] ? xadcInitData[i] : (1<<(i%16));

            if(PSE_DIAG_HIGH)
                bhmMessage("I", PREFIX "_CND", "Init %2d (0x%04x) : 0x%04x (%d)",
                        i, (Uns32)(i*sizeof(Uns16)), data, data);

            ok &= ppmWriteAddressSpace(handles.xadc,
                                       i*sizeof(Uns16),
                                       sizeof(Uns16),
                                       &data);
        }

        if(!ok && PSE_DIAG_LOW) {
            bhmMessage("W", PREFIX "_CN", "Failure in XADC data initialization");
        }

    } else {
        if(PSE_DIAG_LOW)
            bhmMessage("W", PREFIX "_CN", "XADC Data Memory not connected");
    }

    char configfile[BHM_MAX_PATH];
    if (!bhmStringParamValue("config", configfile, sizeof(configfile))) {
        // not specified
    } else {
        // Read configuration information
        if(PSE_DIAG_LOW)
            bhmMessage("I", PREFIX "_CN", "Initializing Data");

        // setup using the configuration file
        // NOTE: xADC is read only so does not initialize Power Library
        //       must be initialized elsewhere e.g. PMBus
        readConfiguration(configfile);
    }

    // Configure native
    Uns32 nativeDiag = (diagnosticLevel & 0xc) >> 2;
    if(initNative(nativeDiag)){
        if (PSE_DIAG_LOW)
            bhmMessage("I", PREFIX ,"Native Initialised (diag %d)", nativeDiag);
    }
}

PPM_DESTRUCTOR_CB(destructor) {
    // YOUR CODE HERE (destructor)
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

