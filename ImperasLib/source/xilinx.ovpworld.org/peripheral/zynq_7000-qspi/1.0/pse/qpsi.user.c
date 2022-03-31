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

#include "pse.igen.h"

#define PREFIX "QUAD-SPI"

#include "flash.h"
#include "flashSpansionS25FL.h"
#include "flashMicronN25Q.h"

// Enum to select flash configured
typedef enum {
    MICRON_FLASH    = 0x0,
    SPANSION_FLASH  = 0x1,
    NO_FLASH        = 0x2
} flashE;

flashE flashType;

// write image back out
char imageFileString[BHM_MAX_PATH];
char *imageFileP = NULL;

//
// Tx and Rx FIFO
//

// Enum to track current operating state
typedef enum {
    IDLE  = 0x0,
    IO    = 0x1,
    AXI   = 0x2
} stateE;


struct {
    Uns32     fifoSize;         // Number of entries available in fifo
    Uns32     rxTrigLvl;        // Number of entries in Rx FIFO to trigger interrupt
    Uns32     txTrigLvl;        // Number of entries in Tx FIFO to trigger interrupt
} state;

#define FIFO_SIZE   63

typedef struct {
    Uns32     data;             // data word
    Uns32     size;             // number of valid data/command bytes in word
} fifoBuffer;

typedef struct fifoBufferS {
    fifoBuffer  buffer[FIFO_SIZE];  // fifo buffer
    Uns32       rdp, wrp;           // pointers to read and write points
    Uns32       used;               // number of used entries
    Bool        full, empty;        // flags when full or empty
} fifoBufferT, *fifoBufferP;

static fifoBufferT Rx, Tx;


//
// Thread functions
//
static void flashAccessThread(void *user);

bhmThreadHandle flashAccessThreadHandle = 0;

static void stopFlashAccessThread() {
    if (flashAccessThreadHandle) {
        bhmDeleteThread(flashAccessThreadHandle);
        flashAccessThreadHandle = 0;
    }
}
static void startFlashAccessThread() {
    if (!flashAccessThreadHandle) {
        if (PSE_DIAG_HIGH) {
            bhmMessage("I", PREFIX "_FA","Start Flash Access Thread");
        }
        flashAccessThreadHandle = bhmCreateThread(flashAccessThread, NULL, "flashAccessThread", 0);
    }
}


/////////////////////
// FIFO OPERATIONS //
/////////////////////

//
// Set the fifoSize, adjusting if out of range
//
static void setFifoSize(Uns32 size) {
    state.fifoSize = FIFO_SIZE;
}

//
// Return size of the fifo
//
static Uns32 getFifoSize() {
    return state.fifoSize;
}

//
// Reset the indicated fifo buffer
//
static void resetFifo(fifoBufferP fifo) {
    fifo->rdp   = 0;
    fifo->wrp   = 0;
    fifo->used  = 0;
    fifo->full  = False;
    fifo->empty = True;
}

//
// Push element onto fifo buffer and update full and empty flags
// Return False if unable to complete because fifo is full
//
static Bool pushFifo (fifoBufferP fifo, Uns32 value, Uns32 size) {
    if (fifo->full) {
        return False;
    } else {
        fifo->buffer[fifo->wrp].data = value;
        fifo->buffer[fifo->wrp].size = size;
        fifo->wrp = (fifo->wrp + 1) % getFifoSize();

        // Test for buffer now being full
        fifo->full  = (fifo->rdp == fifo->wrp);
        fifo->empty = False;

        fifo->used += size;

        return True;
    }
}

static Bool pushRxFifo(Uns32 value, Uns32 size) {
    return pushFifo(&Rx, value, size);
}

static Bool pushTxFifo(Uns32 value, Uns32 size) {

    Bool ok = pushFifo(&Tx, value, size);
    if (ok)
        startFlashAccessThread();

    return ok;
}

//
// View element on top of fifo buffer
// Return False if unable to complete because fifo is empty
//
static Bool viewFifo (fifoBufferP fifo, Uns32 *value, Uns32 *size) {
    if (fifo->empty) {
        return False;
    } else {
        *value = fifo->buffer[fifo->rdp].data;
        *size  = fifo->buffer[fifo->rdp].size;
        return True;
    }
}

//
// Pop element from fifo buffer and update full and empty flags
// Return False if unable to complete because fifo is empty
//
static Bool popFifo (fifoBufferP fifo, Uns32 *value, Uns32 *size) {

    if (!viewFifo(fifo, value, size)) {

        return False;

    } else {

        fifo->rdp = (fifo->rdp + 1) % getFifoSize();

        // Test for buffer now being empty
        fifo->empty = (fifo->rdp == fifo->wrp);
        fifo->full  = False;

        fifo->used -= *size;

        return True;
    }
}

//
// Interrupt and Status register update
//
static void updateStatus() {

    bpAPB_ab_data.Intr_status_REG.bits.RXFULL = 0;
    if (Rx.full) {
        bpAPB_ab_data.Intr_status_REG.bits.RXFULL = 1;
    }

    bpAPB_ab_data.Intr_status_REG.bits.RXNEMPTY = 0;
    if(Rx.used >= (4*bpAPB_ab_data.RX_thres_REG.value)) {
        bpAPB_ab_data.Intr_status_REG.bits.RXNEMPTY = 1;
    }
    bpAPB_ab_data.Intr_status_REG.bits.TXFULL = 0;
    if (Tx.full) {
        bpAPB_ab_data.Intr_status_REG.bits.TXFULL = 1;
    }
    bpAPB_ab_data.Intr_status_REG.bits.TXOW = 1;
    if(Tx.used >= (4*bpAPB_ab_data.TX_thres_REG.value)) {
        bpAPB_ab_data.Intr_status_REG.bits.TXOW = 0;
    }

    Uns32 intState = bpAPB_ab_data.Intr_status_REG.value & bpAPB_ab_data.Intrpt_mask_REG.value;
    static Uns32 intStatePin  = 0;		// hold previous pin state, only change net if required

    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX"_INT","Update Interrupt (status 0x%04x / mask 0x%04x / pin %d)",
                                bpAPB_ab_data.Intr_status_REG.value,
                                bpAPB_ab_data.Intrpt_mask_REG.value,
								intStatePin);

    if(intState && !intStatePin) {
        intStatePin  = 1;
        if(PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX"_INT","Set");
        ppmWriteNet(handles.interrupt, intStatePin);
    } else if (!intState && intStatePin) {
    	intStatePin = 0;
        if(PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX"_INT","Clear");
        ppmWriteNet(handles.interrupt, intStatePin);
    }
}

//
// write and read flash
//
static void flashAccessThread(void *user) {

    Uns32 bufferTxWord;     // a single byte (command or data) from the Tx FIFO
    Uns32 size;             // how many valid entries
    Uns32 bufferRxWord;     // a word from the flash

    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX "_FATS", "Start Flash Access Thread (Tx %d Rx %d)",
                                           Tx.used, Rx.used);

    // use all the data/commands from the Tx FIFO
    while(popFifo(&Tx, &bufferTxWord, &size)) {

        // perform the Flash access and return data or return dummy data
        switch(flashType) {
            case MICRON_FLASH:
                bufferRxWord = flashMicronN25QAccess(bufferTxWord, size);
                break;
            case SPANSION_FLASH:
                bufferRxWord = flashSpansionS25FLAccess(bufferTxWord, size);
                break;
            case NO_FLASH:
            default:
                // do nothing
                bufferRxWord = 0;
                break;
        }

        pushRxFifo(bufferRxWord, size);

        if(PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX "_FA", "Tx Word 0x%08x Rx Word 0x%08x Size %d",
                    bufferTxWord, bufferRxWord, size);

        // set the interrupt status bits and interrupt if required
        updateStatus();

        // may need to slow interface down - depends on software expectation
        // bhmWaitDelay(1);
    }

    flashAccessThreadHandle = 0;
    if(PSE_DIAG_MEDIUM)
        bhmMessage("I", PREFIX "_FATC", "Completed Flash Access Thread");

}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_READ_CB(regNoDefinitionRead) {
    Uns32 offset = addr - handles.bpAPB;
    bhmMessage("W", PREFIX, "No Read Register Defined at offset 0x%04x", offset);
    return 0;
}

PPM_WRITE_CB(regNoDefinitionWrite) {
    Uns32 offset = addr - handles.bpAPB;
    bhmMessage("W", PREFIX, "No Write Register Defined at offset 0x%04x", offset);
}

PPM_REG_READ_CB(rxData) {
    Uns32 data = 0;

    if(bpAPB_ab_data.LQSPI_CFG.bits.LQ_MODE) {
        if(PSE_DIAG_LOW)
            bhmMessage("W", PREFIX "_RXD", "Reading when LQSPI_CFG.LQ_MODE set has no effect");
    } else {
        Uns32 size;

        if(popFifo (&Rx, &data, &size)) {
            if(PSE_DIAG_HIGH)
                bhmMessage("I", PREFIX "_RXD", "FIFO 0x%08x (%d)", data, size);
        } else {
            if(PSE_DIAG_MEDIUM)
                bhmMessage("I", PREFIX "_RXDN", "No Data in Rx FIFO");
        }
    }
    return data;
}

PPM_READ_CB(rtnZero) {
    // some registers are write only but return zero on a read
    return 0;
}

PPM_REG_WRITE_CB(txData0) {

    if(bpAPB_ab_data.LQSPI_CFG.bits.LQ_MODE) {
        if(PSE_DIAG_LOW)
            bhmMessage("W", PREFIX "_TXD0", "Writing when LQSPI_CFG.LQ_MODE set has no effect");
    } else {
        Bool ok = pushTxFifo(data, 4);
        if(PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX "_TXD0", "0x%08x (%d)", data, ok);
    }
    updateStatus();
}

PPM_REG_WRITE_CB(txData1) {

    if(bpAPB_ab_data.LQSPI_CFG.bits.LQ_MODE) {
        if(PSE_DIAG_LOW)
            bhmMessage("W", PREFIX "_TXD1", "Writing when LQSPI_CFG.LQ_MODE set has no effect");
    } else {
        Bool ok = pushTxFifo(data, 1);
        if(PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX "_TXD1", "0x%08x (%d)", data, ok);
    }
    updateStatus();
}

PPM_REG_WRITE_CB(txData2) {

    if(bpAPB_ab_data.LQSPI_CFG.bits.LQ_MODE) {
        if(PSE_DIAG_LOW)
            bhmMessage("W", PREFIX "_TXD2", "Writing when LQSPI_CFG.LQ_MODE set has no effect");
    } else {
        Bool ok = pushTxFifo(data, 2);
        if(PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX "_TXD2", "0x%08x (%d)", data, ok);
    }
    updateStatus();
}

PPM_REG_WRITE_CB(txData3) {

    if(bpAPB_ab_data.LQSPI_CFG.bits.LQ_MODE) {
        if(PSE_DIAG_LOW)
            bhmMessage("W", PREFIX "_TXD3", "Writing when LQSPI_CFG.LQ_MODE set has no effect");
    } else {
        Bool ok = pushTxFifo(data, 3);
        if(PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX "_TXD3", "0x%08x (%d)", data, ok);
    }
    updateStatus();
}

#ifdef PROTECTAXI
//
// Memory protection when in AXI model
//
static PPM_NBYTE_WRITE_CB(axiWriteProtect) {
    bhmMessage("W", PREFIX "_AXI", "axiWriteProtect: Attempt to write to memory at offset 0x%04x", offset);
}

static PPM_NBYTE_READ_CB(axiReadDisabled) {
    bhmMessage("W", PREFIX "_AXI", "axiReadDisabled: Access Disabled and attempt to read memory at offset 0x%04x", offset);
    // dummy data
    *(Uns32 *) data = 0xabadacc5;
}


static void setAXIPortectionAllowReadWrite(Bool allowRead, Bool allowWrite) {
    // install callback(s)
    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX"_AXI", "Protection Read %s Write %s",
                allowRead  ? "    -    " : "Protected",
                allowWrite ? "    -    " : "Protected");

    ppmInstallNByteCallbacks(
        allowRead  ? 0 : axiReadDisabled,
        allowWrite ? 0 : axiWriteProtect,
        NULL,
        &(((char*)handles.bpAXI)[BPAXI_ABM_FLASH_OFFSET]),
        BPAXI_ABM_FLASH_SIZE,
        True,                   // Set to !allowRead if this should cause an exception if accessed
        True,                   // Set to !allowWrite if this should cause an exception if accessed
        False,
        BHM_ENDIAN_LITTLE);
}
#endif
//
// Check to see if the AXI memory was disabled or CS de-asserted
// If so protect memory from access
//
void checkEnabled() {
#ifdef PROTECTAXI
    static Uns32 callbackInstalled = 0;         // indicate callback installed 1: write only 2: read/write
#endif

    if(bpAPB_ab_data.Config_reg.bits.pcs) {           // chip select not active
        switch(flashType) {
            case MICRON_FLASH:
                flashMicronN25QDisable();
                break;
            case SPANSION_FLASH:
                flashSpansionS25FLDisable();
                break;
            case NO_FLASH:
            default:
                // do nothing
                break;
        }
    }

#ifdef PROTECTAXI
    // Not in AXI mode, disable protection callbacks if installed
    if(!bpAPB_ab_data.LQSPI_CFG.bits.LQ_MODE & callbackInstalled) {
        if(PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX"_AXI", "Remove Callbacks");
        // remove callbacks
        setAXIPortectionAllowReadWrite(True, True);
//        ppmInstallWriteCallback(NULL, NULL, &(((char*)handles.bpAXI)[BPAXI_ABM_FLASH_OFFSET]), BPAXI_ABM_FLASH_SIZE);
//        ppmInstallReadCallback (NULL, NULL, &(((char*)handles.bpAXI)[BPAXI_ABM_FLASH_OFFSET]), BPAXI_ABM_FLASH_SIZE);
        callbackInstalled = 0;
    }

    // when in AXI mode we need to protect
    if(bpAPB_ab_data.LQSPI_CFG.bits.LQ_MODE) {          // LQ_MODE set

        if(PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX"_AXI", "AXI Memory Mode Enabled");
        if(!callbackInstalled) {
            if(PSE_DIAG_HIGH)
                bhmMessage("I", PREFIX"_AXI", "Write Protection");
            setAXIPortectionAllowReadWrite(True, False);
//            ppmInstallWriteCallback(axiWriteProtect, NULL, &(((char*)handles.bpAXI)[BPAXI_ABM_FLASH_OFFSET]), BPAXI_ABM_FLASH_SIZE);
            callbackInstalled = 1;
        }

        // Check enabled
        if((!bpAPB_ab_data.Config_reg.bits.pcs &&           // chip select active (low)
             bpAPB_ab_data.En_REG.bits.ENABLE  &&           // enabled
             !bpAPB_ab_data.Config_reg.bits.man_start_com   // not manual start
          )) {

            if(PSE_DIAG_MEDIUM)
                bhmMessage("I", PREFIX"_AXI", "AXI Memory Access enabled");
            if(callbackInstalled == 2) {
                // remove callback - allowing access
                setAXIPortectionAllowReadWrite(True, False);
//                ppmInstallReadCallback(NULL, NULL, &(((char*)handles.bpAXI)[BPAXI_ABM_FLASH_OFFSET]), BPAXI_ABM_FLASH_SIZE);
                if(PSE_DIAG_HIGH)
                    bhmMessage("I", PREFIX"_AXI", "Read Protection removed");
                callbackInstalled = 1;
            }
        } else {
            if(PSE_DIAG_MEDIUM)
                bhmMessage("I", PREFIX "_AXI", "AXI Memory Access disabled");
            if(callbackInstalled != 2) {
                // install callback on reads
                setAXIPortectionAllowReadWrite(False, False);
//                ppmInstallReadCallback(axiReadDisabled, NULL, &(((char*)handles.bpAXI)[BPAXI_ABM_FLASH_OFFSET]), BPAXI_ABM_FLASH_SIZE);
                if(PSE_DIAG_HIGH)
                    bhmMessage("I", PREFIX"_AXI", "Read Protection");
                callbackInstalled = 2;
            }
        }
    }
#endif
}

PPM_REG_WRITE_CB(wrEn) {
    *(Uns32*)user = (*(Uns32*)user & 0xfffffff7) | (data & 0x00000001);
    checkEnabled();
}

PPM_REG_WRITE_CB(wrConfig) {

    *(Uns32*)user = (*(Uns32*)user & 0x7bf60000) | (data & 0x8409ffff);
    if(bpAPB_ab_data.Config_reg.bits.fifo_width != 3) {
        if(PSE_DIAG_LOW)
            bhmMessage("W", PREFIX "_CFGFW", "Attempt to set FIFO width to illegal value %d",
                    bpAPB_ab_data.Config_reg.bits.fifo_width);

        bpAPB_ab_data.Config_reg.bits.fifo_width = 3;
    }
    checkEnabled();
}

PPM_REG_WRITE_CB(wrIntDis) {

    *(Uns32*)user = (*(Uns32*)user & 0xffffff82) | (data & 0x7d);

    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX "_INT_DIS", "0x%08x", *(Uns32*)user);

    // clear bit to disable corresponding interrupts
    bpAPB_ab_data.Intrpt_mask_REG.value &= ~bpAPB_ab_data.Intrpt_dis_REG.value;

    updateStatus();
}

PPM_REG_WRITE_CB(wrIntEn) {

    *(Uns32*)user = (*(Uns32*)user & 0xffffff82) | (data & 0x7d);

    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX "_INT_EN", "0x%08x", *(Uns32*)user);

    // set bit to enable corresponding interrupts
    bpAPB_ab_data.Intrpt_mask_REG.value |= bpAPB_ab_data.Intrpt_en_REG.value;

    updateStatus();
}

PPM_REG_WRITE_CB(wrIntStat) {

    Uns32 intClear = ~(data & 0x41);

    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX "_INT_CLR", "0x%08x", data & 0x41);

    bpAPB_ab_data.Intr_status_REG.value &= intClear;

    updateStatus();
}

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    // Initialize FIFOs
    setFifoSize(FIFO_SIZE);
    resetFifo(&Rx);
    resetFifo(&Tx);
    updateStatus();

    // Load image file(s), if specified
    if(bhmStringParamValue("imageout", (char *)imageFileString, sizeof(imageFileString))) {
        imageFileP = imageFileString;
    }

    char flashTypeString[32];
    if (bhmStringParamValue("flash", (char *)flashTypeString, sizeof(flashTypeString))) {
        if(strcmp(flashTypeString, "micron") == 0) {
            flashType = MICRON_FLASH;
        } else if(strcmp(flashTypeString, "spansion") == 0) {
            flashType = SPANSION_FLASH;
            bhmMessage("W", PREFIX, "The Spansion Flash memory is not fully verified");
        } else {
            bhmMessage("E", PREFIX, "The Flash memory selected '%s' is not recognized. Please select 'micron' or 'spansion'", flashTypeString);
            flashType = NO_FLASH;
        }
    }

    switch(flashType) {
        case MICRON_FLASH:
            flashMicronN25QInit();
            break;
        case SPANSION_FLASH:
            flashSpansionS25FLInit();
            break;
        case NO_FLASH:
        default:
            // do nothing
            break;
    }

    checkEnabled();

    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX, "Wait Simulation Start");

    bhmEventHandle simulationStarting = bhmGetSystemEvent(BHM_SE_START_OF_SIMULATION);
    bhmWaitEvent(simulationStarting);

}

PPM_DESTRUCTOR_CB(destructor) {
    stopFlashAccessThread();
    switch(flashType) {
        case MICRON_FLASH:
            flashMicronN25QFinish();
            break;
        case SPANSION_FLASH:
            flashSpansionS25FLFinish();
            break;
        case NO_FLASH:
        default:
            // do nothing
            break;
    }
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

