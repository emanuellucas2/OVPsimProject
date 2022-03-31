/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., All Rights Reserved.
 *
 * THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND TRADE SECRETS
 * OF IMPERAS SOFTWARE LTD. USE, DISCLOSURE, OR REPRODUCTION IS PROHIBITED
 * EXCEPT AS MAY BE PROVIDED FOR IN A WRITTEN AGREEMENT WITH
 * IMPERAS SOFTWARE LTD.
 *
 */

#include "pse.igen.h"

#include "peripheral/ppm.h"
#include "peripheral/bhm.h"

#define STR(_member)  bport1_ab_data._member.value

#define      level          STR(level)
#define      irq_enabled    STR(enable)
#define      fiq_enabled    STR(fiqen)


static void updateIRQ(Bool v) {
    static Bool current = False;
    if (v != current) {
        current = v;
        ppmWriteNet(handles.irq, v);
    }
}

static void updateFIQ(Bool v) {
    static Bool current = False;
    if (v != current) {
        current = v;
        ppmWriteNet(handles.fiq, v);
    }
}

static void updateNets(void)
{
    Uns32 flags = (level & irq_enabled);
    updateIRQ(flags != 0);
    flags = (level & fiq_enabled);
    updateFIQ(flags != 0);
    if (PSE_DIAG_HIGH) {
        bhmMessage("I", "PIC",
            "level=0x%x  irq_en=0x%x  fiq_en=0x%x",
            level, irq_enabled, fiq_enabled
        );
    }
}

static void set_irq(int irq, int l)
{
    if (l)
        level |=  (1 << irq);
    else
        level &= ~(1 << irq);

    updateNets();
}

PPM_NET_CB(irqUpdate) {
    Uns32 irq = PTR_TO_UNS32(userData);
    if (PSE_DIAG_HIGH) {
        bhmMessage("I", "PIC", "irq %d = %d", irq, (Uns32)value);
    }
    set_irq(irq, value);
}

PPM_REG_READ_CB(readIRQ) {
    return level & irq_enabled;
}

PPM_REG_READ_CB(readFIQ) {
    return level & fiq_enabled;
}

PPM_REG_READ_CB(readLEV) {
    return level & 1;
}

PPM_REG_READ_CB(readLevel) {
    return level;
}


PPM_REG_WRITE_CB(writeCLR) {
    irq_enabled &= ~data;
    updateNets();
}

PPM_REG_WRITE_CB(writeFIQS) {
    fiq_enabled |= data;
    updateNets();
}

PPM_REG_WRITE_CB(writeFIQC) {
    fiq_enabled &= ~data;
    updateNets();
}

PPM_REG_WRITE_CB(writeSCL) {
    if(data & 1) {
        set_irq(0, 0);
    }
    updateNets();
}

PPM_REG_WRITE_CB(writeSST) {
    if(data & 1) {
        set_irq(0, 1);
    }
    updateNets();
}

PPM_REG_WRITE_CB(writeSET) {
    irq_enabled |= data;
    updateNets();
}


PPM_CONSTRUCTOR_CB(constructor) {
    // YOUR CODE HERE (pre constructor)
    periphConstructor();
    // YOUR CODE HERE (post constructor)
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    // YOUR CODE HERE (peripheralSaveState)
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    // YOUR CODE HERE (peripheralRestoreState)
}

