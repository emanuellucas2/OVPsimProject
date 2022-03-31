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
#include <math.h>

#include "pse.igen.h"

#define PREFIX "SLCR"

// Code for unlocking register access
#define LOCKPARAM   "lockcode"
#define UNLOCKPARAM "unlockcode"
Uns32 lockcode, unlockcode;
Bool  lockedState = True;   // lock for all registers
Bool  sclLock     = False;  // configuration lock (SCL, PSS_RST_CTRL, APU_CTRL, WDT_CLK_SEL)

// Define the device Id
#define DEVICEID     "deviceid"
Uns32 deviceId;
#define DEVICEREV    "devicerev"
Uns32 deviceRev;

// parameter names
#define PSCLKPARAM              "psclock"
#define CPUMIPSPARAM            "armmips"
#define BOOTMODE                "bootmode"
#define ARMCLOCKCONTROLPARAM    "clockcontroldisable"
Bool inputARMCLOCKCONTROL;

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

inline static void displayA9_CPU_RST_CTRL() {
    bhmMessage("I", PREFIX, "A9_CPU_RST_CTRL:"
                            "\n   : PERI_RST    %d"
                            "\n   : A9_CLKSTOP1 %d"
                            "\n   : A9_CLKSTOP0 %d"
                            "\n   : A9_RST1     %d"
                            "\n   : A9_RST0     %d",
         bport1_ab_data.A9_CPU_RST_CTRL.bits.PERI_RST,
         bport1_ab_data.A9_CPU_RST_CTRL.bits.A9_CLKSTOP1,
         bport1_ab_data.A9_CPU_RST_CTRL.bits.A9_CLKSTOP0,
         bport1_ab_data.A9_CPU_RST_CTRL.bits.A9_RST1,
         bport1_ab_data.A9_CPU_RST_CTRL.bits.A9_RST0
    );
}

PPM_REG_READ_CB(ReadA9_CPU_RST_CTRL) {
    if(PSE_DIAG_HIGH) {
        displayA9_CPU_RST_CTRL();
    }
    return *(Uns32*)user;
}

// forward declaration
void setArmCpuClockDeration(void);

PPM_REG_WRITE_CB(WriteA9_CPU_RST_CTRL) {
    if(!lockedState) {
        Uns32 oldRst0 = bport1_ab_data.A9_CPU_RST_CTRL.bits.A9_RST0;
        Uns32 oldRst1 = bport1_ab_data.A9_CPU_RST_CTRL.bits.A9_RST1;
        *(Uns32*)user = data;
        Uns32 newRst0 = bport1_ab_data.A9_CPU_RST_CTRL.bits.A9_RST0;
        Uns32 newRst1 = bport1_ab_data.A9_CPU_RST_CTRL.bits.A9_RST1;
        if (oldRst0 != newRst0) {
            if(PSE_DIAG_LOW)
                bhmMessage("I", PREFIX, "Change to A9 CPU0 reset request %d->%d", oldRst0, newRst0);
            ppmWriteNet(handles.A9_RST0, newRst0 ? 1 : 0);
        }
        if (oldRst1 != newRst1) {
            if(PSE_DIAG_LOW)
                bhmMessage("I", PREFIX, "Change to A9 CPU1 reset request %d->%d", oldRst1, newRst1);

            ppmWriteNet(handles.A9_RST1, newRst1 ? 1 : 0);
        }

        if(PSE_DIAG_HIGH) {
            displayA9_CPU_RST_CTRL();
        }
        setArmCpuClockDeration();

    } else {
        if(PSE_DIAG_LOW)
            bhmMessage("W", PREFIX"_LOCKED", "Attempt to modify A9_CPU_RST_CTRL when SLCR locked");
    }
}

#define OCM0LOW   0x00000000
#define OCM1LOW   0x00010000
#define OCM2LOW   0x00020000
#define OCM3LOW   0x00030000
#define OCM0HI    0xfffc0000
#define OCM1HI    0xfffd0000
#define OCM2HI    0xfffe0000
#define OCM3HI    0xffff0000

#define OCMALIAS  0x000c0000

#define OCMSIZE 0x00010000

void mapLow (Uns32 low, Uns32 high) {
    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX"_MAP", "OCM Low mapping 0x%08x to 0x%08x OCM",
                                      low,  low+OCMSIZE-1
                  );
    // Remove OCM high mapping
    ppmDeleteDynamicBridge("spOCMDDR", high, OCMSIZE);
    // Enable low mapping OCM (replaces DDR mapping)
    ppmCreateDynamicBridge("spOCMDDR", low,  OCMSIZE, "mpOCM", low);
}

void mapHigh (Uns32 low, Uns32 high) {
    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX"_MAP", "OCM High mapping 0x%08x to 0x%08x "
                                      "DDR Low mapping 0x%08x to 0x%08x",
                                      high,  high+OCMSIZE-1,
                                      low,   low +OCMSIZE-1
                  );
    // Enable OCM high mapping
    ppmCreateDynamicBridge("spOCMDDR", high, OCMSIZE, "mpOCM", low);
    // Enable DDR low mapping
    ppmCreateDynamicBridge("spOCMDDR", low,  OCMSIZE, "mpDDR", low);
}

void updateMapping() {

    if(PSE_DIAG_HIGH)
        bhmMessage("I", PREFIX"_MAP", "Updating OCM/DDR mappings 0x%x",
               bport1_ab_data.OCM_CFG.value);

    if (bport1_ab_data.OCM_CFG.bits.OCM0) {
        mapHigh(OCM0LOW, OCM0HI);
    } else {
        mapLow(OCM0LOW, OCM0HI);
    }
    if (bport1_ab_data.OCM_CFG.bits.OCM1) {
        mapHigh(OCM1LOW, OCM1HI);
    } else {
        mapLow(OCM1LOW, OCM1HI);
    }
    if (bport1_ab_data.OCM_CFG.bits.OCM2) {
        mapHigh(OCM2LOW, OCM2HI);
    } else {
        mapLow(OCM2LOW, OCM2HI);
    }
    if (bport1_ab_data.OCM_CFG.bits.OCM3) {
        mapHigh(OCM3LOW, OCM3HI);
    } else {
        mapLow(OCM3LOW, OCM3HI);
    }

}
PPM_REG_WRITE_CB(WriteOCM_CFG) {
    if(!lockedState) {
        Uns32 oldCfg = bport1_ab_data.OCM_CFG.value;
        *(Uns32*)user = data;
        Uns32 newCfg = bport1_ab_data.OCM_CFG.value;

        if (oldCfg != newCfg) {
            if(PSE_DIAG_LOW)
                bhmMessage("I", PREFIX, "Change to OCM CFG %d->%d", oldCfg, newCfg);

            updateMapping();

        }
    } else {
        if(PSE_DIAG_LOW)
            bhmMessage("W", PREFIX"_LOCKED", "Attempt to modify OCM_CFG when SLCR locked");
    }
}


PPM_REG_WRITE_CB(WriteSCL) {
    if(!sclLock) {
        *(Uns32*)user = (*(Uns32*)user & 0xfffffffe) | (data & 0x1);
        if(bport1_ab_data.SCL.bits.LOCK) {
            if(PSE_DIAG_LOW)
                bhmMessage("I", PREFIX, "SCL Lock active");
            sclLock = True;
        }
    } else {
        if(PSE_DIAG_LOW)
            bhmMessage("W", PREFIX"_SCLLOCK", "Attempt to modify SCL when SCL lock active");
    }
}

PPM_REG_WRITE_CB(WritePSS_RST_CTRL) {
    if(!sclLock) {
        *(Uns32*)user = data;
    } else {
        if(PSE_DIAG_LOW)
            bhmMessage("W", PREFIX"_SCLLOCK", "Attempt to modify PSS_RST_CTRL when SCL lock active");
    }
}

PPM_REG_WRITE_CB(WriteAPU_CTRL) {
    if(!sclLock) {
        *(Uns32*)user = data;
    } else {
        if(PSE_DIAG_LOW)
            bhmMessage("W", PREFIX"_SCLLOCK", "Attempt to modify APU_CTRL when SCL lock active");
    }
}

PPM_REG_WRITE_CB(WriteWDT_CLK_SEL) {
    if(!sclLock) {
        *(Uns32*)user = data;
    } else {
        if(PSE_DIAG_LOW)
            bhmMessage("W", PREFIX"_SCLLOCK", "Attempt to modify WDT_CLK_SEL when SCL lock active");
    }
}

PPM_REG_WRITE_CB(WriteSLCR_LOCK) {
    if(PSE_DIAG_LOW)
        bhmMessage("I", PREFIX, "SLCR Lock data/code 0x%x/0x%x", data, lockcode);
    if (lockcode == data) {
        lockedState = True;
    }

}
PPM_REG_WRITE_CB(WriteSLCR_UNLOCK) {
    if(PSE_DIAG_LOW)
        bhmMessage("I", PREFIX, "SLCR Unlock data/code 0x%x/0x%x", data, unlockcode);
    if (unlockcode == data) {
        lockedState = False;
    }
}

//
// A9 Processor clock deration
// Maximum clock 667MHz
//
// CPU CLK = (PS_CLK * PLL_FDIV) / DIVISOR / (CLK_621 ? 1 : 2)
// PS_CLK (MHz)   =  33
// PLL_FDIV       =  40
// DIVISOR        =   2
// CLK_621        =   1
// CPU_CLK  (MHz) = 667  (Maximum MIPS Rate setting)

Uns32 inputPS_CLK;          // initialized in constructor
Uns32 inputCPUMIPSRATE;
typedef struct BootModeS {
    union {
        Uns32 value;
        struct {
            Uns32 bootDevice : 3;
            Uns32 jtagChain  : 1;
            Uns32 pllEnable  : 1;
        } bits;
    };
} BootModeT;

BootModeT bootMode;

static inline Bool getPLLEnableState() {

    Bool pllEnabled = False;
    if (bport1_ab_data.ARM_PLL_CTRL.bits.PLL_BYPASS_FORCE) {
        // Always bypassed
    } else if (!bport1_ab_data.ARM_PLL_CTRL.bits.PLL_BYPASS_QUAL) {
        pllEnabled = True;
    } else if (!bootMode.bits.pllEnable) {
        pllEnabled = True;
    }
    return pllEnabled;
}

void setArmCpuClockDeration() {

    // keep the current deration level
    static Uns32 deratePercent = 0;
    // get input clock
    double clock = (double)(inputPS_CLK);

    // Only when PLL being used and active
    if( getPLLEnableState() ) {
        // calculate the current clock from PLL
        clock = clock * bport1_ab_data.ARM_PLL_CTRL.bits.PLL_FDIV;
    }
    clock = clock / bport1_ab_data.ARM_CLK_CTRL.bits.DIVISOR;
    clock = clock / (bport1_ab_data.CLK_621_TRUE.bits.CLK_621 ? 1 : 2);
    Uns32 rndClock = (Uns32) clock;

    double derateRatio = 0;
    if (rndClock < inputCPUMIPSRATE) {
        derateRatio = 1 - ((double)rndClock / (double)inputCPUMIPSRATE);
    } else if(PSE_DIAG_LOW) {
        bhmMessage("W", PREFIX, "CPU_CLK %dMHz at or above max %dMHz, no deration applied", rndClock, inputCPUMIPSRATE);
    }

    // NOTE: Flt64 result must be *rounded* when converted to Uns32, not
    // *truncated* (the C default)
    Uns32 newDeratePercent = round(derateRatio * 100);

    // check clock is below the maximum MIPS rate set on the CPU in the platform
    static Bool lastClockStop = 0;
    Bool clockStop = ((bport1_ab_data.A9_CPU_RST_CTRL.bits.A9_CLKSTOP1 == 1 ) ||
                      (bport1_ab_data.A9_CPU_RST_CTRL.bits.A9_CLKSTOP0 == 1 ));

    // Only want to change the deration if it is modified or clock stop changed
    if ((deratePercent != newDeratePercent) || (clockStop != lastClockStop)) {
        deratePercent = newDeratePercent;
        lastClockStop = clockStop;
        if(PSE_DIAG_LOW)
            bhmMessage("I", PREFIX, "CPU_CLK %dMHz, deration %d%% %s%s%s",
                    rndClock, deratePercent,
                    inputARMCLOCKCONTROL ? " (Clock Control disabled by override)" : "",
                    bport1_ab_data.A9_CPU_RST_CTRL.bits.A9_CLKSTOP1 ? ": A9_CPU1 clock stopped" : "",
                    bport1_ab_data.A9_CPU_RST_CTRL.bits.A9_CLKSTOP0 ? ": A9_CPU0 clock stopped" : ""
            );
        if(!inputARMCLOCKCONTROL) {
            // Only perform the deration if not disabled
            ppmWriteNet(handles.ARM1Deration, bport1_ab_data.A9_CPU_RST_CTRL.bits.A9_CLKSTOP1 ? 100 : deratePercent);
            ppmWriteNet(handles.ARM0Deration, bport1_ab_data.A9_CPU_RST_CTRL.bits.A9_CLKSTOP0 ? 100 : deratePercent);
        }
    } else {
        if(PSE_DIAG_HIGH)
            bhmMessage("I", PREFIX, "CPU_CLK %dMHz, no deration applied", rndClock);
    }
}

inline static void displayARM_CLK_CTRL() {
    bhmMessage("I", PREFIX, "ARM_CLK_CTRL:"
                            "\n   : PERICLK %s"
                            "\n   : 1xCLK   %s"
                            "\n   : 2xCLK   %s"
                            "\n   : 3:2xCLK %s"
                            "\n   : 6:4xCLK %s"
                            "\n   : DIVISOR %d"
                            "\n   : SRC     %s",
         bport1_ab_data.ARM_CLK_CTRL.bits.CPU_PERICLKACT  ? "enable" : "disable",
         bport1_ab_data.ARM_CLK_CTRL.bits.CPU_1XCLKACT    ? "enable" : "disable",
         bport1_ab_data.ARM_CLK_CTRL.bits.CPU_2XCLKACT    ? "enable" : "disable",
         bport1_ab_data.ARM_CLK_CTRL.bits.CPU_6OR3XCLKACT ? "enable" : "disable",
         bport1_ab_data.ARM_CLK_CTRL.bits.CPU_4OR4XCLKACT ? "enable" : "disable",
         bport1_ab_data.ARM_CLK_CTRL.bits.DIVISOR,
         (bport1_ab_data.ARM_CLK_CTRL.bits.SRCSEL < 2)  ? "ARM PLL" :
         (bport1_ab_data.ARM_CLK_CTRL.bits.SRCSEL == 2) ? "DDR PLL" : "IO PLL"
    );
}

PPM_REG_READ_CB(ReadARM_CLK_CTRL) {
    if(PSE_DIAG_HIGH) {
        displayARM_CLK_CTRL();
    }
    return *(Uns32*)user;
}

PPM_REG_WRITE_CB(WriteARM_CLK_CTRL) {
    if(!lockedState) {
        *(Uns32*)user = (*(Uns32*)user & 0xe0ffc0cf) | (data & 0x1f003f30);

        if(PSE_DIAG_HIGH) {
            displayARM_CLK_CTRL();
        }
        if(bport1_ab_data.ARM_CLK_CTRL.bits.SRCSEL >= 2) {
            bhmMessage("W", PREFIX, "ARM_CLK_CTRL:SRCSEL Only ARM PLL Used, setting SRCSEL = 0");
            bport1_ab_data.ARM_CLK_CTRL.bits.SRCSEL = 0;
        }
        if ((!((bport1_ab_data.ARM_CLK_CTRL.bits.DIVISOR == 2) ||
             (bport1_ab_data.ARM_CLK_CTRL.bits.DIVISOR >= 4))) && PSE_DIAG_LOW) {
                bhmMessage("W", PREFIX"_CDE", "Clock Divisor Error %d not a permitted value, setting to 2",
                        bport1_ab_data.ARM_CLK_CTRL.bits.DIVISOR);
            // set to allowed (preferred value)
            bport1_ab_data.ARM_CLK_CTRL.bits.DIVISOR = 2;
        }
        setArmCpuClockDeration();

    } else {
        if(PSE_DIAG_LOW)
            bhmMessage("W", PREFIX"_LOCKED", "Attempt to modify ARM_CLK_CTRL when SLCR locked");
    }
}

inline static void displayARM_PLL_CFG() {
    bhmMessage("I", PREFIX, "ARM_PLL_CFG:"
                            "\n   : LOC_CNT  %d (0x02%x)"
                            "\n   : PLL_CP   %d (0x02%x)"
                            "\n   : PLL_RES  %d (0x02%x)",
         bport1_ab_data.ARM_PLL_CFG.bits.LOC_CNT, bport1_ab_data.ARM_PLL_CFG.bits.LOC_CNT,
         bport1_ab_data.ARM_PLL_CFG.bits.PLL_CP, bport1_ab_data.ARM_PLL_CFG.bits.PLL_CP,
         bport1_ab_data.ARM_PLL_CFG.bits.PLL_RES, bport1_ab_data.ARM_PLL_CFG.bits.PLL_RES
    );
}

PPM_REG_READ_CB(ReadARM_PLL_CFG) {
    if(PSE_DIAG_HIGH) {
        displayARM_PLL_CFG();
    }
    return *(Uns32*)user;
}

PPM_REG_WRITE_CB(WriteARM_PLL_CFG) {
    if(!lockedState) {
        *(Uns32*)user = (*(Uns32*)user & 0xffc0000f) | (data & 0x3ffff0);
        if(PSE_DIAG_HIGH) {
            displayARM_PLL_CFG();
        }
    } else {
        if(PSE_DIAG_LOW)
            bhmMessage("W", PREFIX"_LOCKED", "Attempt to modify ARM_PLL_CFG when SLCR locked");
    }
}

inline static void displayARM_PLL_CTRL() {
    bhmMessage("I", PREFIX, "ARM_PLL_CTRL:"
                            "\n   : PLL_FDIV          %d"
                            "\n   : PLL_BYPASS_FORCE  %d"
                            "\n   : PLL_BYPASS_QUAL   %d"
                            "\n   : BOOT_MODE[4]      %d"
                            "\n   : PLL_PWRDWN        %s"
                            "\n   : PLL_RESET         %s"
                            "\n   : PLL State         %s",
         bport1_ab_data.ARM_PLL_CTRL.bits.PLL_FDIV,
         bport1_ab_data.ARM_PLL_CTRL.bits.PLL_BYPASS_FORCE,
         bport1_ab_data.ARM_PLL_CTRL.bits.PLL_BYPASS_QUAL,
         bootMode.bits.pllEnable,
         bport1_ab_data.ARM_PLL_CTRL.bits.PLL_PWRDWN ? "PLL Powered Down" : "PLL Powered Up",
         bport1_ab_data.ARM_PLL_CTRL.bits.PLL_RESET ? "PLL Reset" : "PLL Operating",
         getPLLEnableState() ? "Enabled" : "bypass"
    );
}

PPM_REG_READ_CB(ReadARM_PLL_CTRL) {
    if(PSE_DIAG_HIGH) {
        displayARM_PLL_CTRL();
    }
    return *(Uns32*)user;
}

PPM_REG_WRITE_CB(WriteARM_PLL_CTRL) {
    if(!lockedState) {
        *(Uns32*)user = (*(Uns32*)user & 0xfff80fe4) | (data & 0x7f01b);
        if(PSE_DIAG_HIGH) {
            displayARM_PLL_CTRL();
        }
        setArmCpuClockDeration();
    } else {
        if(PSE_DIAG_LOW)
            bhmMessage("W", PREFIX"_LOCKED", "Attempt to modify ARM_PLL_CTRL when SLCR locked");
    }
}

PPM_REG_WRITE_CB(WriteCLK_621_TRUE) {
    if(!lockedState) {
        Uns32 clk621=bport1_ab_data.CLK_621_TRUE.bits.CLK_621;
        *(Uns32*)user = (*(Uns32*)user & 0xfffffffe) | (data & 0x1);
        if(clk621 != bport1_ab_data.CLK_621_TRUE.bits.CLK_621) {
            if(PSE_DIAG_LOW)
                bhmMessage("I", PREFIX, "CLK_621 clocking change");
            setArmCpuClockDeration();
        }
    } else {
        if(PSE_DIAG_LOW)
            bhmMessage("W", PREFIX"_LOCKED", "Attempt to modify CLK_621_TRUE when SLCR locked");
    }
}

PPM_READ_CB(ReadSLCR_LOCKSTA) {
    if(PSE_DIAG_LOW)
        bhmMessage("I", PREFIX, "SLCR Lock Status locked=%d", lockedState);
    return lockedState;
}

PPM_READ_CB(ReadSLCR_LOCK) {
    if(PSE_DIAG_LOW)
        bhmMessage("W", PREFIX, "SLCR LOCK register is being read");
    return 0;
}
PPM_READ_CB(ReadSLCR_UNLOCK) {
    if(PSE_DIAG_LOW)
        bhmMessage("W", PREFIX, "SLCR UNLOCK register is being read");
    return 0;
}

PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    bhmUns32ParamValue(DEVICEID, &deviceRev);
    bport1_ab_data.PSS_IDCODE.bits.REV = deviceRev & 0x0f;
    bhmUns32ParamValue(DEVICEID, &deviceId);
    bport1_ab_data.PSS_IDCODE.bits.DEV = deviceId & 0x1f;

    // update the lock and unlock codes
    bhmUns32ParamValue(LOCKPARAM,   &lockcode);
    bhmUns32ParamValue(UNLOCKPARAM, &unlockcode);

    // get input clock base value (typically 33 MHz)
    bhmUns32ParamValue(PSCLKPARAM, &inputPS_CLK);

    // get maximum CPU MIPS RATE (typically 667 MHz)
    bhmUns32ParamValue(CPUMIPSPARAM, &inputCPUMIPSRATE);

    // get sampled BOOT_MODE pin input setting
    bhmUns32ParamValue(BOOTMODE, &bootMode.value);

    // get disable for ARM processor clock control
    bhmBoolParamValue(ARMCLOCKCONTROLPARAM, &inputARMCLOCKCONTROL);

    // setup initial mappings
    if(handles.mpOCM && handles.mpDDR) {
        updateMapping();
    } else {
        bhmMessage("E", PREFIX, "Master ports not connected");
    }
}

PPM_DESTRUCTOR_CB(destructor) {
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}

