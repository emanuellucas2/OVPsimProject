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

#include "pse.igen.h"

#define FUNC_NAME __FUNCTION__
#define INFO if (PSE_DIAG_HIGH) {bhmMessage("I", "US", "val=0x%08x", data);}

struct {
    Uns32 pins;
    Uns32 activeInt;
    Uns32 irq;
    Int32 channel;
    Bool rxen, txen, writeError;
} state;

#define DEFAULT_RX_DELAY 2000
#define PREFIX "US"

//
// Write the irq if the value changes
//
void write_irq(Uns32 value) {
    if (state.irq != value) {
        state.irq = value;
        if (PSE_DIAG_HIGH) bhmMessage("I", "US", "Setting Interrupt IRQ=%d\n", state.irq);
        ppmWriteNet(handles.IRQ, state.irq);
    }
}

#define MAXREAD 256
static void getChars(void *user)
{
    while(1) {
        //
        // Blocking read
        //
        Uns8 buffer[MAXREAD];
        Uns8 bytes = bhmSerReadB(state.channel, buffer, MAXREAD);
        Uns32 i;
        for(i=0; i<bytes; i++) {
            bhmWaitDelay(DEFAULT_RX_DELAY);
            Uns8 c = buffer[i];

            if (apb_REG_data.US_RPR.value) {
                apb_REG_data.US_CSR.bits.ENDRX = 1;

                apb_REG_data.US_RHR.value = c;
                apb_REG_data.US_CSR.value |= 0x1;   // set the RXRDY bit

                ppmWriteAddressSpace(handles.asb, apb_REG_data.US_RPR.value, 1, &c);
                apb_REG_data.US_RCR.value--;
                apb_REG_data.US_RPR.value++;
            }
        }

        // Test for generating an interrupt
        if (apb_REG_data.US_CSR.bits.ENDRX && apb_REG_data.US_IMR.bits.ENDRX) {
            write_irq(1);
            write_irq(0);
        }
    }
}

static Uns32 writeOutput(Uns8 *buffer, Uns32 length)
{
    Uns32 rc = 0;

    if (state.channel >= 0) {

        rc = bhmSerWriteN(state.channel, buffer, length);

        if (rc != length) {
            if (!state.writeError) {
                bhmMessage("W", "US", "Channel write error (%u). Channel closed?", bhmSerLastError(state.channel));
                state.writeError = True;
            }
        } else {
            state.writeError = False;
        }
    }

    return rc;
}

static void openFiles(void)
{
    state.channel = bhmSerOpenAuto();
}

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_WRITE_CB(US_BRGR_wcb) {
    // YOUR CODE HERE (US_BRGR_wcb)
    apb_REG_data.US_BRGR.value = data;
    INFO;
}

PPM_REG_WRITE_CB(US_CR_wcb) {
    // YOUR CODE HERE (US_CR_wcb)
    apb_REG_data.US_CR.value = data;

    if (PSE_DIAG_HIGH) bhmMessage("I", "US", "RSTRX=%d\n", apb_REG_data.US_CR.bits.RSTRX);
    if (PSE_DIAG_HIGH) bhmMessage("I", "US", "RSTTX=%d\n", apb_REG_data.US_CR.bits.RSTTX);

    if (PSE_DIAG_HIGH) bhmMessage("I", "US", "RXEN=%d\n", apb_REG_data.US_CR.bits.RXEN);
    if (PSE_DIAG_HIGH) bhmMessage("I", "US", "RXDIS=%d\n", apb_REG_data.US_CR.bits.RXDIS);
    if (apb_REG_data.US_CR.bits.RXEN == 1) state.rxen = True;
    if (apb_REG_data.US_CR.bits.RXDIS == 1) state.rxen = False;

    if (PSE_DIAG_HIGH) bhmMessage("I", "US", "TXEN=%d\n", apb_REG_data.US_CR.bits.TXEN);
    if (PSE_DIAG_HIGH) bhmMessage("I", "US", "TXDIS=%d\n", apb_REG_data.US_CR.bits.TXDIS);
    if (apb_REG_data.US_CR.bits.TXEN == 1) state.txen = True;
    if (apb_REG_data.US_CR.bits.TXDIS == 1) state.txen = False;

    if (PSE_DIAG_HIGH) bhmMessage("I", "US", "RSTSTA=%d\n", apb_REG_data.US_CR.bits.RSTSTA);
    if (PSE_DIAG_HIGH) bhmMessage("I", "US", "STTBRK=%d\n", apb_REG_data.US_CR.bits.STTBRK);
    if (PSE_DIAG_HIGH) bhmMessage("I", "US", "STPBRK=%d\n", apb_REG_data.US_CR.bits.STPBRK);
    if (PSE_DIAG_HIGH) bhmMessage("I", "US", "STTTO=%d\n", apb_REG_data.US_CR.bits.STTTO);
    if (PSE_DIAG_HIGH) bhmMessage("I", "US", "SENDA=%d\n", apb_REG_data.US_CR.bits.STPBRK);

    INFO;
}

PPM_REG_WRITE_CB(US_IDR_wcb) {
    // YOUR CODE HERE (US_IDR_wcb)
    apb_REG_data.US_IDR.value = data;
    apb_REG_data.US_IMR.value &= ~apb_REG_data.US_IDR.value;
}

PPM_REG_WRITE_CB(US_IER_wcb) {
    // YOUR CODE HERE (US_IER_wcb)
    apb_REG_data.US_IER.value = data;
    apb_REG_data.US_IMR.value |= apb_REG_data.US_IER.value;
}

PPM_REG_READ_CB(US_RHR_rcb) {
    // YOUR CODE HERE (US_RHR_rcb)
    apb_REG_data.US_CSR.value &= ~0x1;   // reset the RXRDY bit
    return *(Uns32*)user;
}

PPM_REG_WRITE_CB(US_MR_wcb) {
    // YOUR CODE HERE (US_MR_wcb)
    apb_REG_data.US_MR.value = data;
    INFO;
}

PPM_REG_WRITE_CB(US_RCR_wcb) {
    // YOUR CODE HERE (US_RCR_wcb)
    apb_REG_data.US_RCR.value = data;
    apb_REG_data.US_CSR.bits.ENDRX = 0;
    INFO;
}

PPM_REG_WRITE_CB(US_RPR_wcb) {
    // YOUR CODE HERE (US_RPR_wcb)
    apb_REG_data.US_RPR.value = data;
    INFO;
}

PPM_REG_WRITE_CB(US_RTOR_wcb) {
    // YOUR CODE HERE (US_RTOR_wcb)
    apb_REG_data.US_RTOR.value = data;
    INFO;
}

PPM_REG_WRITE_CB(US_TCR_wcb) {
    // YOUR CODE HERE (US_TCR_wcb)
    apb_REG_data.US_TCR.value = data;

    // Test value of count and transmit accordingly
    while (apb_REG_data.US_TCR.value) {
        // read from pointer
        Uns8 tmp;
        Bool success = ppmReadAddressSpace(handles.asb, apb_REG_data.US_TPR.value, 1, &tmp);
        if (success) {
            writeOutput(&tmp, 1);
        } else {
            bhmMessage("F", "US", "Read from US_TPR");
        }
        apb_REG_data.US_TCR.value--;
        apb_REG_data.US_TPR.value++;
    }
    apb_REG_data.US_CSR.bits.TXEMPTY = 1;

    INFO;
}

PPM_REG_WRITE_CB(US_THR_wcb) {
    // YOUR CODE HERE (US_THR_wcb)
    apb_REG_data.US_THR.value = data;
    INFO;
}

PPM_REG_WRITE_CB(US_TPR_wcb) {
    // YOUR CODE HERE (US_TPR_wcb)
    apb_REG_data.US_TPR.value = data;
    INFO;
}

PPM_REG_WRITE_CB(US_TTGR_wcb) {
    // YOUR CODE HERE (US_TTGR_wcb)
    apb_REG_data.US_TTGR.value = data;
    INFO;
}


PPM_DESTRUCTOR_CB(destructor) {
    if(state.channel >= 0) {
        bhmSerClose(state.channel);
    }
}

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    openFiles();
    bhmCreateThread(getChars, NULL, "getchars", 0);

    write_irq(0);
}




PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

