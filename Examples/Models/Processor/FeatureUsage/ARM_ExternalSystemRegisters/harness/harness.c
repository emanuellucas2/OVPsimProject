/*
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * The contents of this file are provided under the Software License
 * Agreement that you accepted before downloading this file.
 *
 * This source forms part of the Software and can be used for educational,
 * training, and demonstration purposes but cannot be used for derivative
 * works except in cases where the derivative works require OVP technology
 * to run.
 *
 * For open source models released under licenses that you can use for
 * derivative works, please visit www.OVPworld.org or www.imperas.com
 * for the location of the open source models.
 *
 */


////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                           Imperas/OVP Generated
//
////////////////////////////////////////////////////////////////////////////////


// This file declares functions to be implemented by the user.
// Be careful to avoid overwriting any edits should igen be re-run.


#include <string.h>
#include <stdlib.h>

#include "op/op.h"

#define HARNESS_NAME "HARNESS"
#define MODULE_NAME  "ARMv8-A-FMv1"

////////////////////////////////////////////////////////////////////////////////
//     T I M E R   C O N T E X T
////////////////////////////////////////////////////////////////////////////////

typedef struct armTimerCxtS {

    // associated processor
    optProcessorP processor;

    // timer registers
    optRegP CNTFRQ_EL0;
    optRegP CNTPCT_EL0;
    optRegP CNTVCT_EL0;
    optRegP CNTP_TVAL_EL0;
    optRegP CNTP_CTL_EL0;
    optRegP CNTP_CVAL_EL0;
    optRegP CNTPS_TVAL_EL1;
    optRegP CNTPS_CTL_EL1;
    optRegP CNTPS_CVAL_EL1;
    optRegP CNTV_TVAL_EL0;
    optRegP CNTV_CTL_EL0;
    optRegP CNTV_CVAL_EL0;
    optRegP CNTHP_TVAL_EL2;
    optRegP CNTHP_CTL_EL2;
    optRegP CNTHP_CVAL_EL2;
    optRegP CNTKCTL_EL1;
    optRegP CNTHCTL_EL2;
    optRegP CNTVOFF_EL2;

} armTimerCxt, *armTimerCxtP;

static armTimerCxt CPU0_cxt;

//
// Get register, validating it is present
//
static optRegP getReg(optProcessorP processor, const char *name) {

    optRegP result = opProcessorRegByName(processor, name);

    if(!result) {
        opPrintf("Register %s not found\n", name);
    }

    return result;
}

//
// Get register handles for all timer registers for the processor
//
static void seedTimerCxt(optProcessorP processor, armTimerCxtP cxt) {

    // save context processor
    cxt->processor = processor;

    // save timer registers
    cxt->CNTFRQ_EL0     = getReg(processor, "CNTFRQ_EL0");
    cxt->CNTPCT_EL0     = getReg(processor, "CNTPCT_EL0");
    cxt->CNTVCT_EL0     = getReg(processor, "CNTVCT_EL0");
    cxt->CNTP_TVAL_EL0  = getReg(processor, "CNTP_TVAL_EL0");
    cxt->CNTP_CTL_EL0   = getReg(processor, "CNTP_CTL_EL0");
    cxt->CNTP_CVAL_EL0  = getReg(processor, "CNTP_CVAL_EL0");
    cxt->CNTPS_TVAL_EL1 = getReg(processor, "CNTPS_TVAL_EL1");
    cxt->CNTPS_CTL_EL1  = getReg(processor, "CNTPS_CTL_EL1");
    cxt->CNTPS_CVAL_EL1 = getReg(processor, "CNTPS_CVAL_EL1");
    cxt->CNTV_TVAL_EL0  = getReg(processor, "CNTV_TVAL_EL0");
    cxt->CNTV_CTL_EL0   = getReg(processor, "CNTV_CTL_EL0");
    cxt->CNTV_CVAL_EL0  = getReg(processor, "CNTV_CVAL_EL0");
    cxt->CNTHP_TVAL_EL2 = getReg(processor, "CNTHP_TVAL_EL2");
    cxt->CNTHP_CTL_EL2  = getReg(processor, "CNTHP_CTL_EL2");
    cxt->CNTHP_CVAL_EL2 = getReg(processor, "CNTHP_CVAL_EL2");
    cxt->CNTKCTL_EL1    = getReg(processor, "CNTKCTL_EL1");
    cxt->CNTHCTL_EL2    = getReg(processor, "CNTHCTL_EL2");
    cxt->CNTVOFF_EL2    = getReg(processor, "CNTVOFF_EL2");
}


////////////////////////////////////////////////////////////////////////////////
//     R E G I S T E R   D E F I N I T I O N S
////////////////////////////////////////////////////////////////////////////////

//
// Structure defining system register artifact bus address format
//
typedef struct armSysArtifactAddrS {
    Uns32 align : 4;
    Uns32 op0   : 4;
    Uns32 op1   : 4;
    Uns32 op2   : 4;
    Uns32 CRn   : 4;
    Uns32 CRm   : 4;
    Bool  NS    : 1;
    Bool  AA64  : 1;
    Uns32 _u1   : 6;
} armSysArtifactAddr;

//
// Structure defining a system register of interest
//
typedef struct armSysRegDescS {
    const char        *name;        // system register name
    armSysArtifactAddr addrDesc;    // register address
    Uns32              size;        // word size (1 or 2)
    optBusSlaveReadFn  rcb;         // read callback
    optBusSlaveWriteFn wcb;         // write callback
} armSysRegDesc, *armSysRegDescP;

//
// Timer register callbacks (forward references)
//
static OP_BUS_SLAVE_READ_FN (r_CNTFRQ_EL0);
static OP_BUS_SLAVE_WRITE_FN(w_CNTFRQ_EL0);
static OP_BUS_SLAVE_READ_FN (r_CNTPCT_EL0);
static OP_BUS_SLAVE_WRITE_FN(w_CNTPCT_EL0);
static OP_BUS_SLAVE_READ_FN (r_CNTVCT_EL0);
static OP_BUS_SLAVE_WRITE_FN(w_CNTVCT_EL0);
static OP_BUS_SLAVE_READ_FN (r_CNTP_TVAL_EL0);
static OP_BUS_SLAVE_WRITE_FN(w_CNTP_TVAL_EL0);
static OP_BUS_SLAVE_READ_FN (r_CNTP_CTL_EL0);
static OP_BUS_SLAVE_WRITE_FN(w_CNTP_CTL_EL0);
static OP_BUS_SLAVE_READ_FN (r_CNTP_CVAL_EL0);
static OP_BUS_SLAVE_WRITE_FN(w_CNTP_CVAL_EL0);
static OP_BUS_SLAVE_READ_FN (r_CNTPS_TVAL_EL1);
static OP_BUS_SLAVE_WRITE_FN(w_CNTPS_TVAL_EL1);
static OP_BUS_SLAVE_READ_FN (r_CNTPS_CTL_EL1);
static OP_BUS_SLAVE_WRITE_FN(w_CNTPS_CTL_EL1);
static OP_BUS_SLAVE_READ_FN (r_CNTPS_CVAL_EL1);
static OP_BUS_SLAVE_WRITE_FN(w_CNTPS_CVAL_EL1);
static OP_BUS_SLAVE_READ_FN (r_CNTV_TVAL_EL0);
static OP_BUS_SLAVE_WRITE_FN(w_CNTV_TVAL_EL0);
static OP_BUS_SLAVE_READ_FN (r_CNTV_CTL_EL0);
static OP_BUS_SLAVE_WRITE_FN(w_CNTV_CTL_EL0);
static OP_BUS_SLAVE_READ_FN (r_CNTV_CVAL_EL0);
static OP_BUS_SLAVE_WRITE_FN(w_CNTV_CVAL_EL0);
static OP_BUS_SLAVE_READ_FN (r_CNTHP_TVAL_EL2);
static OP_BUS_SLAVE_WRITE_FN(w_CNTHP_TVAL_EL2);
static OP_BUS_SLAVE_READ_FN (r_CNTHP_CTL_EL2);
static OP_BUS_SLAVE_WRITE_FN(w_CNTHP_CTL_EL2);
static OP_BUS_SLAVE_READ_FN (r_CNTHP_CVAL_EL2);
static OP_BUS_SLAVE_WRITE_FN(w_CNTHP_CVAL_EL2);
static OP_BUS_SLAVE_READ_FN (r_CNTKCTL_EL1);
static OP_BUS_SLAVE_WRITE_FN(w_CNTKCTL_EL1);
static OP_BUS_SLAVE_READ_FN (r_CNTHCTL_EL2);
static OP_BUS_SLAVE_WRITE_FN(w_CNTHCTL_EL2);
static OP_BUS_SLAVE_READ_FN (r_CNTVOFF_EL2);
static OP_BUS_SLAVE_WRITE_FN(w_CNTVOFF_EL2);

//
// List of registers to be implemented externally
//
static armSysRegDesc timerRegs[] = {

    {"CNTFRQ_EL0",     {op0:3, op1:3, CRn:14, CRm:0, op2:0}, 1, r_CNTFRQ_EL0,     w_CNTFRQ_EL0    },
    {"CNTPCT_EL0",     {op0:3, op1:3, CRn:14, CRm:0, op2:1}, 2, r_CNTPCT_EL0,     w_CNTPCT_EL0    },
    {"CNTVCT_EL0",     {op0:3, op1:3, CRn:14, CRm:0, op2:2}, 2, r_CNTVCT_EL0,     w_CNTVCT_EL0    },
    {"CNTP_TVAL_EL0",  {op0:3, op1:3, CRn:14, CRm:2, op2:0}, 1, r_CNTP_TVAL_EL0,  w_CNTP_TVAL_EL0 },
    {"CNTP_CTL_EL0",   {op0:3, op1:3, CRn:14, CRm:2, op2:1}, 1, r_CNTP_CTL_EL0,   w_CNTP_CTL_EL0  },
    {"CNTP_CVAL_EL0",  {op0:3, op1:3, CRn:14, CRm:2, op2:2}, 2, r_CNTP_CVAL_EL0,  w_CNTP_CVAL_EL0 },
    {"CNTPS_TVAL_EL1", {op0:3, op1:7, CRn:14, CRm:2, op2:0}, 1, r_CNTPS_TVAL_EL1, w_CNTPS_TVAL_EL1},
    {"CNTPS_CTL_EL1",  {op0:3, op1:7, CRn:14, CRm:2, op2:1}, 1, r_CNTPS_CTL_EL1,  w_CNTPS_CTL_EL1 },
    {"CNTPS_CVAL_EL1", {op0:3, op1:7, CRn:14, CRm:2, op2:2}, 2, r_CNTPS_CVAL_EL1, w_CNTPS_CVAL_EL1},
    {"CNTV_TVAL_EL0",  {op0:3, op1:3, CRn:14, CRm:3, op2:0}, 1, r_CNTV_TVAL_EL0,  w_CNTV_TVAL_EL0 },
    {"CNTV_CTL_EL0",   {op0:3, op1:3, CRn:14, CRm:3, op2:1}, 1, r_CNTV_CTL_EL0,   w_CNTV_CTL_EL0  },
    {"CNTV_CVAL_EL0",  {op0:3, op1:3, CRn:14, CRm:3, op2:2}, 2, r_CNTV_CVAL_EL0,  w_CNTV_CVAL_EL0 },
    {"CNTHP_TVAL_EL2", {op0:3, op1:4, CRn:14, CRm:2, op2:0}, 1, r_CNTHP_TVAL_EL2, w_CNTHP_TVAL_EL2},
    {"CNTHP_CTL_EL2",  {op0:3, op1:4, CRn:14, CRm:2, op2:1}, 1, r_CNTHP_CTL_EL2,  w_CNTHP_CTL_EL2 },
    {"CNTHP_CVAL_EL2", {op0:3, op1:4, CRn:14, CRm:2, op2:2}, 2, r_CNTHP_CVAL_EL2, w_CNTHP_CVAL_EL2},
    {"CNTKCTL_EL1",    {op0:3, op1:0, CRn:14, CRm:1, op2:0}, 1, r_CNTKCTL_EL1,    w_CNTKCTL_EL1   },
    {"CNTHCTL_EL2",    {op0:3, op1:4, CRn:14, CRm:1, op2:0}, 1, r_CNTHCTL_EL2,    w_CNTHCTL_EL2   },
    {"CNTVOFF_EL2",    {op0:3, op1:4, CRn:14, CRm:0, op2:3}, 2, r_CNTVOFF_EL2,    w_CNTVOFF_EL2   },

    // KEEP LAST: terminator
    {0}
};

//
// Return register description for the given pseudo-address
//
static armSysRegDescP findRegDesc(Uns32 addr) {

    union {Uns32 u32; armSysArtifactAddr f;} u1 = {addr};

    u1.f.NS   = 0;
    u1.f.AA64 = 0;

    Uns32 i;

    for(i=0; timerRegs[i].name; i++) {

        union {armSysArtifactAddr f; Uns32 u32;} u2 = {timerRegs[i].addrDesc};

        if(u1.u32==u2.u32) {
            return &timerRegs[i];
        }
    }

    return 0;
}


////////////////////////////////////////////////////////////////////////////////
//     T I M E R   R E G I S T E R   C A L L B A C K S
////////////////////////////////////////////////////////////////////////////////

// report callback function execution
#define REPORT(_f) \
    opMessage("I", HARNESS_NAME, "Called function '%s'" \
                                 " to re-implement timer register", _f);

static OP_BUS_SLAVE_READ_FN (r_CNTFRQ_EL0) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegRead(cxt->processor, cxt->CNTFRQ_EL0, data);
}

static OP_BUS_SLAVE_WRITE_FN(w_CNTFRQ_EL0) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegWrite(cxt->processor, cxt->CNTFRQ_EL0, data);
}

static OP_BUS_SLAVE_READ_FN (r_CNTPCT_EL0) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegRead(cxt->processor, cxt->CNTPCT_EL0, data);
}

static OP_BUS_SLAVE_WRITE_FN(w_CNTPCT_EL0) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegWrite(cxt->processor, cxt->CNTPCT_EL0, data);
}

static OP_BUS_SLAVE_READ_FN (r_CNTVCT_EL0) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegRead(cxt->processor, cxt->CNTVCT_EL0, data);
}

static OP_BUS_SLAVE_WRITE_FN(w_CNTVCT_EL0) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegWrite(cxt->processor, cxt->CNTVCT_EL0, data);
}

static OP_BUS_SLAVE_READ_FN (r_CNTP_TVAL_EL0) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegRead(cxt->processor, cxt->CNTP_TVAL_EL0, data);
}

static OP_BUS_SLAVE_WRITE_FN(w_CNTP_TVAL_EL0) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegWrite(cxt->processor, cxt->CNTP_TVAL_EL0, data);
}

static OP_BUS_SLAVE_READ_FN (r_CNTP_CTL_EL0) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegRead(cxt->processor, cxt->CNTP_CTL_EL0, data);
}

static OP_BUS_SLAVE_WRITE_FN(w_CNTP_CTL_EL0) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegWrite(cxt->processor, cxt->CNTP_CTL_EL0, data);
}

static OP_BUS_SLAVE_READ_FN (r_CNTP_CVAL_EL0) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegRead(cxt->processor, cxt->CNTP_CVAL_EL0, data);
}

static OP_BUS_SLAVE_WRITE_FN(w_CNTP_CVAL_EL0) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegWrite(cxt->processor, cxt->CNTP_CVAL_EL0, data);
}

static OP_BUS_SLAVE_READ_FN (r_CNTPS_TVAL_EL1) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegRead(cxt->processor, cxt->CNTPS_TVAL_EL1, data);
}

static OP_BUS_SLAVE_WRITE_FN(w_CNTPS_TVAL_EL1) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegWrite(cxt->processor, cxt->CNTPS_TVAL_EL1, data);
}

static OP_BUS_SLAVE_READ_FN (r_CNTPS_CTL_EL1) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegRead(cxt->processor, cxt->CNTPS_CTL_EL1, data);
}

static OP_BUS_SLAVE_WRITE_FN(w_CNTPS_CTL_EL1) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegWrite(cxt->processor, cxt->CNTPS_CTL_EL1, data);
}

static OP_BUS_SLAVE_READ_FN (r_CNTPS_CVAL_EL1) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegRead(cxt->processor, cxt->CNTPS_CVAL_EL1, data);
}

static OP_BUS_SLAVE_WRITE_FN(w_CNTPS_CVAL_EL1) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegWrite(cxt->processor, cxt->CNTPS_CVAL_EL1, data);
}

static OP_BUS_SLAVE_READ_FN (r_CNTV_TVAL_EL0) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegRead(cxt->processor, cxt->CNTV_TVAL_EL0, data);
}

static OP_BUS_SLAVE_WRITE_FN(w_CNTV_TVAL_EL0) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegWrite(cxt->processor, cxt->CNTV_TVAL_EL0, data);
}

static OP_BUS_SLAVE_READ_FN (r_CNTV_CTL_EL0) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegRead(cxt->processor, cxt->CNTV_CTL_EL0, data);
}

static OP_BUS_SLAVE_WRITE_FN(w_CNTV_CTL_EL0) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegWrite(cxt->processor, cxt->CNTV_CTL_EL0, data);
}

static OP_BUS_SLAVE_READ_FN (r_CNTV_CVAL_EL0) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegRead(cxt->processor, cxt->CNTV_CVAL_EL0, data);
}

static OP_BUS_SLAVE_WRITE_FN(w_CNTV_CVAL_EL0) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegWrite(cxt->processor, cxt->CNTV_CVAL_EL0, data);
}

static OP_BUS_SLAVE_READ_FN (r_CNTHP_TVAL_EL2) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegRead(cxt->processor, cxt->CNTHP_TVAL_EL2, data);
}

static OP_BUS_SLAVE_WRITE_FN(w_CNTHP_TVAL_EL2) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegWrite(cxt->processor, cxt->CNTHP_TVAL_EL2, data);
}

static OP_BUS_SLAVE_READ_FN (r_CNTHP_CTL_EL2) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegRead(cxt->processor, cxt->CNTHP_CTL_EL2, data);
}

static OP_BUS_SLAVE_WRITE_FN(w_CNTHP_CTL_EL2) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegWrite(cxt->processor, cxt->CNTHP_CTL_EL2, data);
}

static OP_BUS_SLAVE_READ_FN (r_CNTHP_CVAL_EL2) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegRead(cxt->processor, cxt->CNTHP_CVAL_EL2, data);
}

static OP_BUS_SLAVE_WRITE_FN(w_CNTHP_CVAL_EL2) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegWrite(cxt->processor, cxt->CNTHP_CVAL_EL2, data);
}

static OP_BUS_SLAVE_READ_FN (r_CNTKCTL_EL1) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegRead(cxt->processor, cxt->CNTKCTL_EL1, data);
}

static OP_BUS_SLAVE_WRITE_FN(w_CNTKCTL_EL1) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegWrite(cxt->processor, cxt->CNTKCTL_EL1, data);
}

static OP_BUS_SLAVE_READ_FN (r_CNTHCTL_EL2) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegRead(cxt->processor, cxt->CNTHCTL_EL2, data);
}

static OP_BUS_SLAVE_WRITE_FN(w_CNTHCTL_EL2) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegWrite(cxt->processor, cxt->CNTHCTL_EL2, data);
}

static OP_BUS_SLAVE_READ_FN (r_CNTVOFF_EL2) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegRead(cxt->processor, cxt->CNTVOFF_EL2, data);
}

static OP_BUS_SLAVE_WRITE_FN(w_CNTVOFF_EL2) {
    armTimerCxtP cxt = userData;
    REPORT (FUNC_NAME);
    opProcessorRegWrite(cxt->processor, cxt->CNTVOFF_EL2, data);
}


////////////////////////////////////////////////////////////////////////////////
//     S Y S T E M   R E G I S T E R   A C C E S S   M O N I T O R
////////////////////////////////////////////////////////////////////////////////

//
// Report system register access details. Fields are decoded from the address
// using the encoding scheme above.
//
static void reportSystemRegister(Uns32 addr) {

    union {Uns32 u32; armSysArtifactAddr f;} u = {addr};

    opPrintf(
        "    [op0:%-2u op1:%-2u op2:%-2u CRn:%-2u CRm:%-2u NS:%u AA64:%c]",
        u.f.op0,
        u.f.op1,
        u.f.op2,
        u.f.CRn,
        u.f.CRm,
        u.f.NS,
        u.f.AA64?'Y':'N'
    );
}

//
// This function is called whenever the processor READS a system register.
// Here, we just print details of the access.
//
static OP_MONITOR_FN(monitorReadCB) {

    armSysRegDescP rd = findRegDesc(addr);

    opPrintf("SYSTEM RD <= ");

    if(bytes==4) {
        opPrintf("0x%08x        ", *(Uns32*)data);
    } else {
        opPrintf("0x"FMT_640Nx, *(Uns64*)data);
    }

    reportSystemRegister(addr);

    if(rd) {
        opPrintf(" (%s)", rd->name);
    }

    opPrintf("\n");
}

//
// This function is called whenever the processor WRITES a system register
// Here, we just print details of the access.
//
static OP_MONITOR_FN(monitorWriteCB) {

    armSysRegDescP rd = findRegDesc(addr);

    opPrintf("SYSTEM WR => ");

    if(bytes==4) {
        opPrintf("0x%08x        ", *(Uns32*)data);
    } else {
        opPrintf("0x"FMT_640Nx, *(Uns64*)data);
    }

    reportSystemRegister(addr);

    if(rd) {
        opPrintf(" (%s)", rd->name);
    }

    opPrintf("\n");
}


////////////////////////////////////////////////////////////////////////////////
//                                   M A I N
////////////////////////////////////////////////////////////////////////////////

int main(int argc, const char *argv[]) {

    opSessionInit(OP_VERSION);
    optCmdParserP parser = opCmdParserNew(MODULE_NAME, OP_AC_ALL);

    opCmdParseArgs(parser, argc, argv);

    optModuleP mr = opRootModuleNew(0, 0, 0);

    //
    // Instance module
    //
    const char *moduleVLNV = opVLNVString(NULL, "arm.ovpworld.org", "module", MODULE_NAME, "1.0", OP_MODULE, OP_VLNV_FATAL);
    optModuleP mi = opModuleNew(
        mr,             // parent module
        moduleVLNV,     // model file
        MODULE_NAME,    // name
        0,              // connections
        0               // parameters
    );

    optProcessorP processor = 0;

    // -------------------------------------------------------------------------
    // Connect to bus port "SystemMonitor_CPU0", allowing system register
    // accesses by CPU0 to be observed externally
    // -------------------------------------------------------------------------

    while ((processor=opProcessorNext (mi, processor))) {

        optBusPortP port = 0;

        while ((port=opObjectBusPortNext(processor, port))) {

            const char *name = opObjectName(port);

            if(!strcmp(name, "SystemMonitor_CPU0")) {

                optBusP monitorBus = opBusNew(mr, "sysMonitor_CPU0", 32, 0, 0);

                opProcessorBusConnect(processor, monitorBus, name);

                // ------------------------------------------------------------
                // Add monitor callbacks to observe system register value
                // updates
                // ------------------------------------------------------------

                opBusReadMonitorAdd (
                    monitorBus, processor, 0, -1, monitorReadCB, 0
                );
                opBusWriteMonitorAdd (
                    monitorBus, processor, 0, -1, monitorWriteCB, 0
                );
            }
        }
    }

    // -------------------------------------------------------------------------
    // Connect to bus port "System_CPU0", allowing system register
    // accesses by CPU0 to be implemented externally
    // -------------------------------------------------------------------------

    while ((processor=opProcessorNext (mi, processor))) {

        optBusPortP port = 0;

        while ((port=opObjectBusPortNext(processor, port))) {

            const char *name = opObjectName(port);

            if(!strcmp(name, "System_CPU0")) {

                optBusP sysBus = opBusNew(mr, "sys_CPU0", 32, 0, 0);
                Uns32   i;
                optProcessorP child;

                opProcessorBusConnect(processor, sysBus, name);

                // ------------------------------------------------------------
                // Cache timer register handles for CPU0
                // ------------------------------------------------------------

                for (
                    child = opProcessorChild(processor);
                    child;
                    child = opProcessorSiblingNext(child)
                ) {
                    if(!strcmp(opObjectName(child), "cpu_CPU0")) {
                        seedTimerCxt(child, &CPU0_cxt);
                    }
                }

                // ------------------------------------------------------------
                // Add register implementation callbacks
                // ------------------------------------------------------------

                for(i=0; timerRegs[i].name; i++) {

                    Uns32 NS;
                    Uns32 AA64;

                    for(NS=0; NS<2; NS++) {

                        for(AA64=0; AA64<2; AA64++) {

                            union {armSysArtifactAddr f; Uns32 u32;} u = {
                                timerRegs[i].addrDesc
                            };

                            u.f.NS   = NS;
                            u.f.AA64 = AA64;

                            // op0 is used by AArch64 only
                            if(!AA64) {
                                u.f.op0 = 0;
                            }

                            Addr addrLo = u.u32;
                            Addr addrHi = addrLo + timerRegs[i].size*4 - 1;

                            opBusSlaveNew(
                                sysBus, timerRegs[i].name, processor, OP_PRIV_RW,
                                addrLo, addrHi, timerRegs[i].rcb, timerRegs[i].wcb,
                                0, &CPU0_cxt
                            );
                        }
                    }
                }
            }
        }
    }

    opRootModuleSimulate(mr);
    opSessionTerminate();

    return (opErrors() ? 1 : 0);    // set exit based upon any errors
}

