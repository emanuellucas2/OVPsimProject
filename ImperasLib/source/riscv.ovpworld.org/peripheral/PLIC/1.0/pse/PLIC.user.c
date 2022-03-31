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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pse.igen.h"

#define PREFIX "PLIC"

#define WORDBYTES  4
#define WORDBITS  32

// Maximum sizes supported in RiscV PLIC architecture specification
#define ARCH_S_MAX 1023
#define ARCH_T_MAX 15872

////////////////////////////////////////////////////////////////////////////////
// CONFIGURATION DEFINES
////////////////////////////////////////////////////////////////////////////////

// Maximum number of targets supported by implementation (valid target numbers are 0..T_MAX-1)
#ifndef T_MAX
#define T_MAX  ARCH_T_MAX
#endif
#if T_MAX > ARCH_T_MAX
#error T_MAX is larger than the architectural maximum
#endif

// Number of registers needed for T_MAX bits in packed arrays for each target:
#define T_PACK ((T_MAX + (WORDBITS-1)) / WORDBITS)

// Maximum number of interrupt sources supported by implementation (valid source numbers are 1..S_MAX)
#ifndef S_MAX
#define S_MAX  ARCH_S_MAX
#endif
#if S_MAX > ARCH_S_MAX
#error S_MAX is larger than the architectural maximum
#endif

// Number of registers needed for S_MAX+1 bits in packed arrays for each source:
#define S_PACK ((S_MAX + WORDBITS) / WORDBITS)

// Maximum number of priorities supported by implementation (valid priority numbers are 1..P_MAX)
#ifndef P_MAX
// No architectural maximum on number of priorities so default to any value that fits in register
#define P_MAX  ((Uns32)-1)
#endif

// Are the Pending registers writable?
#ifndef PENDING_WRITABLE
#define PENDING_WRITABLE False
#endif

// Should accesses to Reserved regions be ignored?
#ifndef IGNORE_RESERVED_ACCESS
#define IGNORE_RESERVED_ACCESS True
#endif

// Are interrupt inputs level sensitive (True) or edge triggered (False)
// Note: This setting is not used when ANDES_EXTENSIONS is True
#ifndef LEVEL_SENSITIVE
#define LEVEL_SENSITIVE True
#endif

// Are interrupt inputs active high/positive edge (True) or active low/negative edge (False)
#ifndef ACTIVE_VALUE
#define ACTIVE_VALUE True
#endif

// Are Andes PLIC extensions present?
#ifndef ANDES_EXTENSIONS
#define ANDES_EXTENSIONS False
#endif

// Are SiFive PLIC extensions present?
#ifndef SIFIVE_EXTENSIONS
#define SIFIVE_EXTENSIONS False
#endif

////////////////////////////////////////////////////////////////////////////////
// STRUCTURES AND STATIC VARIABLES
////////////////////////////////////////////////////////////////////////////////

// Net handle array (Note irqS[0] corresponds to net irqS1
ppmNetHandle *irqS, *irqT, *iid, *iack;

/*
 * Architectural Memory Map
 * ------------------------
 * 0x0000_0000 - 0x0000_0003    - *** Reserved/Andes Feature Register ***
 * 0x0000_0004 - 0x0000_0FFF    - Priority (num)
 * 0x0000_1000 - 0x0000_107F    - Pending (num)
 * 0x0000_1080 - 0x0000_10FF    - *** Reserved/Andes Trigger Types ***
 * 0x0000_1100 - 0x0000_1FFF    - *** Reserved ***
 * 0x0000_2000 - 0x0000_207F    - Enables for context 0 (num)
 * 0x0000_2080 - 0x0000_21FF    - Enables for context 1 (num)
 * ...
 * 0x001F_1F80 - 0x001F_1FFF    - Enables for context 15871 (num)
 * 0x001F_2000 - 0x001F_1FFF    - *** Reserved ***
 * 0x0020_0000 - 0x0020_0003    - Priority Threshold for context 0 (num)
 * 0x0020_0004 - 0x0020_0007    - Claim/Complete for context 0 (num)
 * 0x0020_0008 - 0x0020_0FFF    - *** Reserved ***
 * 0x0020_1000 - 0x0020_1003    - Priority Threshold for context 1 (num)
 * 0x0020_1004 - 0x0020_1007    - Claim/Complete for context 1 (num)
 * 0x0020_1008 - 0x0020_1FFF    - *** Reserved ***
 * ....
 * 0x03FF_E000 - 0x03FF_E003    - Priority Threshold for context 15871 (num)
 * 0x03FF_E004 - 0x03FF_E007    - Claim/Complete for context 15871 (num)
 * 0x03FF_E008 - 0x03FF_FFFF    - *** Reserved ***
 *
 * Shown for default 4K alignment of Enables and Priority Threshold registers
 * - This is configurable with the enable_stride and context_stride parameters
 */

struct {
    Uns32 sources;
    Uns32 targets;
    Uns32 priorities;
    Uns32 PriorityBase;
    Uns32 PendingBase;
    Uns32 EnablesBase;
    Uns32 EnablesStride;
    Uns32 ContextBase;
    Uns32 ContextStride;
} config;

// T=TARGETS (aka contexts), S=SOURCES

// Input  IRQS[1..S_MAX], 0 is reserved
Bool  IRQS[S_MAX+1] = { 0 };

// Output IRQT[0..T_MAX-1]
Bool  IRQT[T_MAX] = { 0 };

// Input IACK[0..T_MAX-1]
Bool  IACK[T_MAX] = { 0 };

// Priority of input IRQS (0=disable, 1-config.priorities, 1 lowest)
Uns32 PRIORITY[S_MAX+1] = { 0 };

// Pending array - 1 bit per source
Uns32 PENDING[S_PACK] = { 0 };

// Enable bits - each target has array with 1 bit per source
Uns32 ENABLE[T_MAX][S_PACK] = { { 0 } };

// Priority Threshold - 1 per target
Uns32 THRESHOLD[T_MAX] = { 0 };

// Claim/Complete - 1 per target
Uns32 CLAIM[T_MAX] = { 0 };

// Internal flag: Claim is in progress for source - 1 bit per source
Uns32 SRC_CLAIM_ACTIVE[S_PACK] = { 0 };

// Internal flag: Claim is in progress by target - 1 bit per target
Uns32 TGT_CLAIM_ACTIVE[T_PACK] = { 0 };

// Internal flag: Claim has been posted on the vector t<n>_eiid port so may not change
Uns32 TGT_VECTOR_CLAIM_POSTED[T_PACK] = { 0 };

///////////////////////////////////////////////////////////////////////////////
// ANDES-SPECIFIC FEATURES
///////////////////////////////////////////////////////////////////////////////

// Andes Preempt bits - each target has array with 1 bit per priority level
#define ANDES_PREEMPT_OFFSET 0x400
#define ANDES_PREEMPT_NUM_PRIORITIES 255
#define ANDES_PREEMPT_NUM_REGS ((ANDES_PREEMPT_NUM_PRIORITIES + (WORDBITS-1)) / WORDBITS)
Uns32 ANDES_PREEMPT[T_MAX][ANDES_PREEMPT_NUM_REGS] = { { 0 } };

// Andes Feature Register
Uns32 andesFeature = 0;
#define ANDES_FEATURE_MASK 0x3
#define ANDES_FEATURE_PREMPT_MASK 0x1
#define ANDES_FEATURE_VECTOR_MASK 0x2
#define ANDES_FEATURE_ENABLED(_R, _F) (((_R) & ANDES_FEATURE_##_F##_MASK) != 0)

// Andes Trigger type array - edge (1) or level (0) triggered
#define ANDES_TRIGGER_BASE 0x1080
Uns32 ANDES_TRIGGER[S_PACK]  = { 0 };      // Andes Trigger type array [1..S_MAX], 0 is reserved

// Andes number of interrupt and target configuration register
union {
    Uns32 value;
    struct {
        Uns32 num_interrupt : 16;
        Uns32 num_target    : 16;
    } bits;
} num_interrupts_targets;
#define ANDES_NUM_INTERRUPTS_TARGETS_ADDR 0x1100

// Andes version and max priority configuration register
union {
    Uns32 value;
    struct {
        Uns32 version      : 16;
        Uns32 max_priority : 16;
    } bits;
} version_max_priority;
#define ANDES_VERSION_MAX_PRIORITY_ADDR 0x1104

Bool andesVectoredIntSupported;

///////////////////////////////////////////////////////////////////////////////
// SIFIVE-SPECIFIC FEATURES
///////////////////////////////////////////////////////////////////////////////

// SiFive Clock Gate Disable
Uns32 clockGateDisable = 1;
#define SIFIVE_CLOCK_GATE_DISABLE_OFFSET 0x1ff000

////////////////////////////////////////////////////////////////////////////////
// UTILITY FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

#define IS_READ  1
#define IS_WRITE 0

static ppmNetPortP getNetPortsUser() {

    static ppmNetPort *netPortsUser = NULL;

    if (!netPortsUser) {

        Uns32 numSources = 0;
        Uns32 numTargets = 0;
        Bool  vectorSupport = False;

        bhmUns32ParamValue("num_sources", &numSources);
        bhmUns32ParamValue("num_targets", &numTargets);

        // Note: netports for first source and first target are added by iGen
        Int32 numNetPorts = numSources + numTargets - 2;

        if (ANDES_EXTENSIONS) {
            bhmBoolParamValue ("vector_plic_support", &vectorSupport);
            if (vectorSupport) {
                // vector support mode adds eiid and eiack net ports per target
                numNetPorts += 2 * numTargets;
            }
        }

        if (numNetPorts > 0 ) {
            // Allocate array with one entry for each netport + a terminating empty entry
            netPortsUser = (ppmNetPortP) calloc(numNetPorts+1, sizeof(ppmNetPort));

            Uns32 id;
            char name[32];
            ppmNetPortP ptr = netPortsUser;

            // Sources numbered from 1 to numSources (1 created by iGen)
            for(id=2; id<=numSources; id++, ptr++) {
                snprintf(name, sizeof(name), "irqS%d", id);
                ptr->name = strdup(name);
                ptr->type = PPM_INPUT_PORT;
                ptr->description = "Input Interrupt Port";
            }

            // Targets numbered from 0 to numTargets-1  (0 created by iGen)
            for(id=1; id<numTargets; id++, ptr++) {
                snprintf(name, sizeof(name), "irqT%d", id);
                ptr->name = strdup(name);
                ptr->type = PPM_OUTPUT_PORT;
                ptr->description = "Output Interrupt Port, to Hart/Context";
            }

            // Vector support adds t<x>_eiid and t<x>_eack ports per target when enabled
            if (ANDES_EXTENSIONS && vectorSupport) {
                for(id=0; id<numTargets; id++, ptr++) {
                    snprintf(name, sizeof(name), "t%d_eiid", id);
                    ptr->name = strdup(name);
                    ptr->type = PPM_OUTPUT_PORT;
                    ptr->description = "Vectored Interrupt ID port";
                }

                for(id=0; id<numTargets; id++, ptr++) {
                    snprintf(name, sizeof(name), "t%d_eiack", id);
                    ptr->name = strdup(name);
                    ptr->type = PPM_INPUT_PORT;
                    ptr->description = "Vectored Interrupt Acknowledge port";
                }
            }

            // Terminating entry
            ptr->name = NULL;
        }
    }
    return netPortsUser;
}

PPM_NET_PORT_FN(nextNetPortUser) {
    if(!netPort) {
        netPort = getNetPortsUser();
    } else {
        netPort++;
    }
    return (netPort && netPort->name) ? netPort : 0;
}

static Bool getPackedBit(Uns32 id, Uns32 *array) {
    Uns32 posn = id & 0x1F;
    Uns32 word = id >> 5;
    return (array[word] & (1 << posn)) != 0;
}

static void setPackedBit(Uns32 id, Uns32 *array, Bool value) {
    Uns32 posn = id & 0x1F;
    Uns32 word = id >> 5;
    if (value) {
        array[word] |= (1 << posn);
    } else {
        array[word] &= ~(1 << posn);
    }
}

static Uns32 highestPackedBit(Uns32 *array, Uns32 maxBit) {
    Uns32 i;
    for (i = maxBit; i >= 0; i--) {
        if (getPackedBit(i, array)) {
            return i;
        }
    }
    return 0;
}

static Bool irqAsserted(Bool pending, Bool old, Bool new, Uns32 id) {
    Bool levelSensitive = LEVEL_SENSITIVE;

    if (ANDES_EXTENSIONS) {
        // On Andes PLIC trigger type for each source comes from registers
        // 0 = level sensitive, 1 = edge triggered
        levelSensitive = getPackedBit(id, ANDES_TRIGGER) != 1;
    }

    if (levelSensitive) {
        return new == ACTIVE_VALUE;
    } else {
        return pending || ((old != ACTIVE_VALUE) && (new == ACTIVE_VALUE));
    }
}

//
// Sanity check the current CLAIM value for target:
// - the pending bit for a non-zero CLAIM source must be set
// - the gateway bit for a non-zero CLAIM source must not be set
//
static void checkClaimIsValid(Uns32 target) {
    Uns32 source = CLAIM[target];
    if (source) {
        if (!getPackedBit(source, PENDING)) {
            bhmMessage("F", PREFIX,
                    "CLAIM[%d] = %d, but PENDING bit for irqS%d not set",
                    target, source, source);
        }
        if (getPackedBit(source, SRC_CLAIM_ACTIVE)) {
            bhmMessage("F", PREFIX,
                    "CLAIM[%d] = %d, but SRC_CLAIM_ACTIVE bit for irqS%d is set",
                    target, source, source);
        }
    }
}

//
// check that target enables are valid
// - When in vector mode only a single target may be enabled for an interrupt source
//
static void checkTargetEnablesValid() {

    if (!ANDES_FEATURE_ENABLED(andesFeature, VECTOR)) {
        // Check only made when the vectored interrupts are enabled
    } else {
        Uns32 source;

        for (source = 1; source <= config.sources; source++) {
            Uns32 numEnabled=0;
            Uns32 target;

            for (target = 0; target < config.targets; target++) {
                if (getPackedBit(source, ENABLE[target])) {
                    numEnabled++;
                }
            }

            if (numEnabled > 1) {
                bhmMessage("F", PREFIX,
                           "Multiple targets enabled for interrupt source %d "
                           "while vectored interrupt mode enabled",
                           source);
            }
        }
    }
}

//
// check that the eiid and eiack ports for the target are connected to nets
//
static void checkVectorPortsConnected(Uns32 target) {
    if (iid[target] == PPM_INVALID_HANDLE) {
        bhmMessage("F", PREFIX,
                "Vectored interrupt occurred on target %d but t%d_eiid port not connected",
                target, target);
    }
    if (iack[target] == PPM_INVALID_HANDLE) {
        bhmMessage("F", PREFIX,
                "Vectored interrupt occurred on target %d but t%d_eiack port not connected",
                target, target);
    }
}

static void throwBusError(Bool accessType) {
    if (accessType == IS_READ) {
        ppmReadAbort();
    } else {
        ppmWriteAbort();
    }
}

//
// Check for valid size and alignment
// - if error then signal a bus error and return False
// - if no error return True
//
static Bool validAccess(Uns32 offset, Uns32 bytes, Bool accessType, Bool artifactAccess) {

    if (bytes != 4) {
        if (!artifactAccess) {
            bhmMessage("W", PREFIX,
                       "Invalid register access size %d bytes at offset 0x%08x. "
                       "Only 4 byte accesses supported",
                       bytes, offset);
            throwBusError(accessType);
        }
        return False;
    }

    if (offset & 0x3) {
        if (!artifactAccess) {
            bhmMessage("W", PREFIX,
                       "Unaligned register access at offset 0x%08x. "
                       "Only 4 byte accesses supported",
                       offset);
            throwBusError(accessType);
        }
        return False;
    }

    return True;
}

static Uns32 indexFromUserData(void *userData, Uns32 arraySize) {
    Uns32 index = PTR_TO_UNS32(userData);
    if (index >= arraySize) {
        bhmMessage("F", PREFIX,
                "Invalid userData %d (>= %d)", index, arraySize);
    }
    return index;
}

static Uns32 bitIndexFromWordOffset(Uns32 offset, Uns32 maxIndex) {
    Uns32 index = (offset & 0x7f) >> 2;
    if (index >= maxIndex) {
        bhmMessage("F", PREFIX,
                "Invalid index %d (> %d) encoded in offset",
                index, maxIndex);
    }
    return index;
}

////////////////////////////////////////////////////////////////////////////////
// INTERRUPTS
////////////////////////////////////////////////////////////////////////////////

static void writeNet(ppmNetHandle net, ppmNetValue value) {
    if (net != PPM_INVALID_HANDLE) {
        ppmWriteNet(net, value);
    }
}

static void irqTSet(Uns32 target, Uns32 claim) {
    if (IRQT[target]) {
        // already set - nothing to do
    } else {
        if (ANDES_FEATURE_ENABLED(andesFeature, VECTOR)) {
            // when in vector mode send the claim number on the iid net
            // and set the flag that claim has been posted,
            // to prevent changes until acknowledged or claimed
            checkVectorPortsConnected(target);
            setPackedBit(target, TGT_VECTOR_CLAIM_POSTED, 1);
            writeNet(iid[target], claim);
        }

        if (PSE_DIAG_MEDIUM) bhmMessage("I", PREFIX, "irqT%d 0->1\n", target);
        IRQT[target] = True;
        writeNet(irqT[target], 1);
    }
}

static void irqTClr(Uns32 target) {
    if (IRQT[target]) {

        if (PSE_DIAG_MEDIUM) bhmMessage("I", PREFIX, "irqT%d 1->0\n", target);

        IRQT[target] = False;
        writeNet(irqT[target], 0);

        if (ANDES_FEATURE_ENABLED(andesFeature, VECTOR)) {
            // In vector mode, clear the claim posted on the iid net
            setPackedBit(target, TGT_VECTOR_CLAIM_POSTED, 0);
            writeNet(iid[target], 0);
        }
    } else {
        // already clear - nothing to do
    }
}

static void evaluate() {
    Uns32 target;
    Uns32 pending_word;
    Uns32 prevCLAIM[config.targets];
    Bool  preempt = ANDES_FEATURE_ENABLED(andesFeature, PREMPT);
    Bool  vector  = ANDES_FEATURE_ENABLED(andesFeature, VECTOR);

    // Record previous CLAIM values and clear them
    memcpy(prevCLAIM, CLAIM, config.targets * sizeof(*CLAIM));
    memset(CLAIM, 0, config.targets * sizeof(*CLAIM));

    // Iterate over all interrupt sources looking for active pending bits
    for(pending_word = 0; pending_word * WORDBITS <= config.sources; pending_word++) {
        Uns32 i;
        Uns32 pending = PENDING[pending_word];

        // Optimization when all bits in pending word are inactive
        if (pending == 0) continue;

        // Iterate each bit in this pending word
        for (i = 0; i < WORDBITS; i++) {
            Uns32 source   = (pending_word * WORDBITS) + i;
            Uns32 irqSPRIO = PRIORITY[source];

            if (source > config.sources) {
                // Skip bits beyond number of sources configured
            } else if (!getPackedBit(source, PENDING)) {
                // Skip if interrupt is not pending
            } else if (!preempt && getPackedBit(source, SRC_CLAIM_ACTIVE)) {
                // Skip if a claim is currently active for this source
                // unless preemptive interrupts are active
            } else {
                // evaluate if pending is propagated to any targets:
                for (target=0; target<config.targets; target++) {
                    if (vector && getPackedBit(target, TGT_VECTOR_CLAIM_POSTED)) {
                        // If claim is currently posted then do not change it
                        CLAIM[target] = prevCLAIM[target];
                    } else if (!getPackedBit(source, ENABLE[target])) {
                        // Source not enabled for this target
                    } else if ((irqSPRIO <= THRESHOLD[target])) {
                        // Source priority does not exceed target threshold
                    } else if (!preempt && getPackedBit(target, TGT_CLAIM_ACTIVE)) {
                        // If not in preempt mode do not process interrupts while claim is active
                    } else {
                        Uns32 claim         = CLAIM[target];
                        Uns32 claimPriority = claim ? PRIORITY[claim] : 0;

                        // Is this the first claim or is this a higher priority claim?
                        if (!claim || claimPriority < irqSPRIO) {
                            CLAIM[target] = source;
                        }
                    }
                }
            }
        }
    }

    // Update target interrupts based on current state:
    // - claim != 0 means an enabled interrupt of sufficient priority
    //   to cause an interrupt is pending
    for (target=0; target<config.targets; target++) {

        if (!preempt && getPackedBit(target, TGT_CLAIM_ACTIVE)) {
            // Do not update target's interrupt while claim is active
            // unless preemptive interrupts are active
        } else {
            Uns32 claim = CLAIM[target];

            if (PSE_DIAG_MEDIUM) {
                if (claim && (claim != prevCLAIM[target])) {
                    bhmMessage("I", PREFIX,
                            "new CLAIM[Target=%d]=irqS%d\n", target, claim);
                }
            }

            // Update interrupt signal for target
            if (claim) {
                irqTSet(target, claim);
            } else {
                irqTClr(target);
            }
        }

        // Sanity check the target's pending claim state is valid
        checkClaimIsValid(target);
    }
}

//
// Claim an interrupt form either:
// - read from claim register
// - leading edge on t<x>_eiack net in Andes vector mode
//
static void claimInterrupt(Uns32 source, Uns32 target) {

    if (source != 0) {
        // Atomically clear pending bit for claimed source
        setPackedBit(source, PENDING, 0);

        // Set the claimed but not completed flag for the source and target
        setPackedBit(source, SRC_CLAIM_ACTIVE, 1);
        setPackedBit(target, TGT_CLAIM_ACTIVE, 1);

        // Is Andes Preemptive Priority Interrupt feature active?
        if (ANDES_FEATURE_ENABLED(andesFeature, PREMPT)) {
            Uns32 priority   = PRIORITY[source];
            Uns32 threshhold = THRESHOLD[target];

            // Limit thresholds to maximum supported
            if (threshhold > ANDES_PREEMPT_NUM_PRIORITIES) {
                threshhold = ANDES_PREEMPT_NUM_PRIORITIES;
            }

            // Update threshold to claimed sources value and save previous
            THRESHOLD[target] = priority;
            setPackedBit(threshhold, ANDES_PREEMPT[target], 1);
        }

        if (ANDES_EXTENSIONS) {
            // Andes spec states that target interrupt is guaranteed
            // to be deasserted when a claim is made (other specs don't
            // mention this so only done for Andes)
            irqTClr(target);
        }

        evaluate();
    }
}


////////////////////////////////////////////////////////////////////////////////
// CALLBACKS
////////////////////////////////////////////////////////////////////////////////

//
// Called when interrupt acknowledge net value changes
// - active for Andes Vector mode only
// - on leading edge claim any interrupted posted
//
PPM_NET_CB(iackUpdate) {
    Uns32 target  = indexFromUserData(userData, S_MAX+1);
    Bool newValue = value != 0;
    Bool oldValue = IACK[target];

    IACK[target] = newValue;

    if (ANDES_FEATURE_ENABLED(andesFeature, VECTOR)) {
        Uns32 source = CLAIM[target];

        if (newValue != oldValue) {
            if (source) {
                if (PSE_DIAG_LOW) {
                    bhmMessage("I", PREFIX, "t%d_eiack %d => %d (source=%d)\n", target, oldValue, newValue, source);
                }

                if (oldValue == 0 && newValue == 1) {
                    // Target has acknowledged reading this value, so can clear it
                    setPackedBit(target, TGT_VECTOR_CLAIM_POSTED, 0);
                    // Claim the source interrupt on leading edge
                    claimInterrupt(source, target);
                } else  if (oldValue == 1 && newValue == 0) {
                    // allow target to process new interrupts on trailing edge
                    setPackedBit(target, TGT_CLAIM_ACTIVE, 0);
                }
            }
        }
    }
}

//
// Called when interrupt source net value changes
// - If the IRQ is asserted by this change, set the bit in the PENDING Register
//   (what defines asserted depends on whether this is level sensitive or edge triggered)
// - The pending bit is cleared in claimRD
//
PPM_NET_CB(irqUpdate) {
    Uns32 source   = indexFromUserData(userData, S_MAX+1);
    Bool  old      = IRQS[source];
    Bool  new      = (value != 0);

    if (old != new) {
        Bool  pending  = getPackedBit(source, PENDING);
        Bool  asserted = irqAsserted(pending, old, new, source);

        // Track most recent value seen on net
        IRQS[source] = new;

        if (PSE_DIAG_LOW) {
            bhmMessage("I", PREFIX, "irqS%d %d->%d (asserted=%d, pending=%d)\n",
                       source, old, new, asserted, pending);
        }

        if (asserted) {
            if (!pending) {
                // Asserted and pending bit not set - set pending bit
                setPackedBit(source, PENDING, 1);
                if (PSE_DIAG_LOW) {
                    bhmMessage("I", PREFIX, "irqS%d Pending bit set by active irq input\n", source);
                }
                evaluate();
            }
        } else {
            if (pending) {
                // Not asserted and pending bit set - clear pending bit
                setPackedBit(source, PENDING, 0);
                if (PSE_DIAG_LOW) {
                    bhmMessage("I", PREFIX, "irqS%d Pending bit cleared by inactive irq input\n", source);
                }
                evaluate();
            }
        }
    }
}

//
// Trap Memory RD/Write
//
PPM_NBYTE_READ_CB(reservedRD) {

    if (!artifactAccess) {
        if (!IGNORE_RESERVED_ACCESS || PSE_DIAG_LOW) {
            bhmMessage("W", PREFIX,
                       "Read from reserved location at offset 0x%08x ignored\n",
                       offset);
        }
        if (!IGNORE_RESERVED_ACCESS) {
            throwBusError(IS_READ);
        }
    }

    memset(data, 0, bytes);
    return;
}

PPM_NBYTE_WRITE_CB(reservedWR) {
    if (!artifactAccess) {
        if (!IGNORE_RESERVED_ACCESS || PSE_DIAG_LOW) {
            bhmMessage("W", PREFIX,
                       "Write to reserved location at offset 0x%08x ignored\n",
                       offset);
        }
        if (!IGNORE_RESERVED_ACCESS && !artifactAccess) {
            throwBusError(IS_WRITE);
        }
    }
}

PPM_NBYTE_VIEW_CB(claimVIEW) {
    Uns32 target = indexFromUserData(userData, T_MAX);
    *(Uns32 *)data = CLAIM[target];
}

PPM_NBYTE_READ_CB(claimRD) {
    Uns32 source = 0;

    if (validAccess(offset, bytes, IS_READ, artifactAccess)) {

        // Get highest priority pending source for target
        Uns32 target = indexFromUserData(userData, T_MAX);
        source = CLAIM[target];

        // Sanity check the target's pending claim state is valid
        checkClaimIsValid(target);

        if (!source) {
            // Silently ignore inactive claims
        } else {
            claimInterrupt(source, target);
        }
    }

    *(Uns32 *)data = source;
}

PPM_NBYTE_WRITE_CB(claimWR) {

    if (validAccess(offset, bytes, IS_WRITE, artifactAccess)) {
        Uns32 target = PTR_TO_UNS32(userData);
        Uns32 source = *(Uns32 *)data;

        if (!source) {
            // ignore writes of 0
        } else if (source > config.sources) {
            bhmMessage("W", PREFIX,
                "Ignoring write of %d to claim[%d]: Exceeds number of sources=%d",
                source, target, config.sources);
        } else if (!getPackedBit(source, ENABLE[target])) {
            bhmMessage("W", PREFIX,
                "Ignoring write of %d to claim[%d]: Source %d is not enabled on target %d",
                source, target, source, target);
        } else {

            // Clear the claimed but not completed flag for the source and target
            setPackedBit(source, SRC_CLAIM_ACTIVE, 0);
            setPackedBit(target, TGT_CLAIM_ACTIVE, 0);
            setPackedBit(target, TGT_VECTOR_CLAIM_POSTED, 0);

            // Is Andes Preemptive Priority Interrupt feature active?
            if (ANDES_EXTENSIONS && ANDES_FEATURE_ENABLED(andesFeature, PREMPT)) {
                Uns32 priority = highestPackedBit(ANDES_PREEMPT[target], ANDES_PREEMPT_NUM_REGS);

                // Restore threshold to highest saved and clear that bit
                THRESHOLD[target] = priority;
                setPackedBit(priority, ANDES_PREEMPT[target], 0);
            }

            evaluate();
        }
    }
}

PPM_NBYTE_READ_CB(priorityRD) {
    Uns32 priority = 0;

    if (validAccess(offset, bytes, IS_READ, artifactAccess)) {
        Uns32 id = indexFromUserData(userData, S_MAX+1);

        priority = PRIORITY[id];
    }

    *(Uns32 *)data = priority;
}

PPM_NBYTE_WRITE_CB(priorityWR) {

    if (validAccess(offset, bytes, IS_WRITE, artifactAccess)) {
        Uns32 id       = indexFromUserData(userData, S_MAX+1);
        Uns32 priority = *(Uns32 *)data;

        if (priority > config.priorities) {
            // Mask priority value to highest supported value
            priority = config.priorities;
        }

        if (PRIORITY[id] != priority) {
            PRIORITY[id] = priority;
            evaluate();
        }
    }
}

PPM_NBYTE_READ_CB(pendingRD) {
    Uns32 pending = 0;

    if (validAccess(offset, bytes, IS_READ, artifactAccess)) {
        Uns32 id = indexFromUserData(userData, S_PACK);
        pending = PENDING[id];
    }

    *(Uns32 *)data =  pending;
}

PPM_NBYTE_WRITE_CB(pendingWR) {

    if (!PENDING_WRITABLE) {

        // Pending is RO: treat writes same as writes to reserved
        reservedWR(offset, data, bytes, userData, artifactAccess);

    } else if (validAccess(offset, bytes, IS_WRITE, artifactAccess)) {

        Uns32 id          = indexFromUserData(userData, S_PACK);
        Uns32 pendingMask = *(Uns32 *)data;
        Uns32 oldPending  = PENDING[id];

        if (id == 0) {
            // bit 0 of first register is hardwired to 0
            pendingMask &= ~1;
        }

        // Writes to pending can only set bits, not clear them
        PENDING[id] |= pendingMask;

        if (PENDING[id] != oldPending) {

            if (PSE_DIAG_LOW) {
                Uns32 i;
                Uns32 mask = 1;
                for (i = 0; i < 32; i++, mask <<= 1) {
                    if (!(oldPending & mask) && (PENDING[id] & mask)) {
                        bhmMessage(
                            "I", PREFIX,
                            "irqS%d Pending bit set by write to pending[%d]\n",
                            (id << 5) | i, id);
                    }
                }
            }

            evaluate();
        }
    }
}

PPM_NBYTE_READ_CB(enableRD) {
    Uns32 enable = 0;

    if (validAccess(offset, bytes, IS_READ, artifactAccess)) {
        Uns32 target = indexFromUserData(userData, T_MAX);
        Uns32 id     = bitIndexFromWordOffset(offset, S_PACK);

        enable = ENABLE[target][id];
    }

    *(Uns32 *)data = enable;
}

PPM_NBYTE_WRITE_CB(enableWR) {

    if (validAccess(offset, bytes, IS_WRITE, artifactAccess)) {
        Uns32 target = indexFromUserData(userData, T_MAX);
        Uns32 id     = bitIndexFromWordOffset(offset, S_PACK);
        Uns32 enable = *(Uns32 *)data;

        // bit 0 of first register is hardwired to 0
        if (id == 0) {
            enable &= ~1;
        }

        // bits beyond number of sources are not writable, so mask them out
        Uns32 lastBit = ((id + 1) * WORDBITS) - 1;
        if (lastBit > config.sources) {
            Uns32 unwritableBits = lastBit - config.sources;
            Uns32 mask           = (Uns32)-1 >> unwritableBits;
            enable &= mask;
        }

        if (ENABLE[target][id] != enable) {
            ENABLE[target][id] = enable;
            checkTargetEnablesValid();
            evaluate();
        }
    }
}

PPM_NBYTE_READ_CB(thresholdRD) {
    Uns32 thresh = 0;

    if (validAccess(offset, bytes, IS_READ, artifactAccess)) {
        Uns32 target  = indexFromUserData(userData, T_MAX);
        thresh = THRESHOLD[target];
    }

    *(Uns32 *)data = thresh;
}

PPM_NBYTE_WRITE_CB(thresholdWR) {

    if (validAccess(offset, bytes, IS_WRITE, artifactAccess)) {
        Uns32 target = indexFromUserData(userData, T_MAX);
        Uns32 thresh = *(Uns32 *)data;

        if (thresh > config.priorities) {
            // Mask threshold value to highest supported value
            thresh = config.priorities;
        }

        if (THRESHOLD[target] != thresh) {
            THRESHOLD[target] = thresh;
            evaluate();
        }
    }
}

PPM_NBYTE_READ_CB(andesFeatureRD) {
    Uns32 feature = 0;

    if (validAccess(offset, bytes, IS_READ, artifactAccess)) {
        feature = andesFeature;
    }

    *(Uns32 *)data = feature;
}

PPM_NBYTE_WRITE_CB(andesFeatureWR) {

    if (validAccess(offset, bytes, IS_WRITE, artifactAccess)) {
        Uns32 feature = *(Uns32 *)data;

        if (ANDES_FEATURE_ENABLED(feature, VECTOR) && !andesVectoredIntSupported) {
            bhmMessage("W", PREFIX,
                    "Attempt to set FeatureEnable.VECTORED, but vector_plic_support parameter is false");
            feature &= ~ANDES_FEATURE_VECTOR_MASK;
        }

        andesFeature = feature & ANDES_FEATURE_MASK;

        checkTargetEnablesValid();
    }
}

PPM_NBYTE_READ_CB(andesPreemptRD) {
    Uns32 preempt = 0;

    if (validAccess(offset, bytes, IS_READ, artifactAccess)) {
        Uns32 target = indexFromUserData(userData, T_MAX);
        Uns32 id     = bitIndexFromWordOffset(offset, ANDES_PREEMPT_NUM_REGS);
        preempt = ANDES_PREEMPT[target][id];
    }

    *(Uns32 *)data = preempt;
}

PPM_NBYTE_WRITE_CB(andesPreemptWR) {

    if (validAccess(offset, bytes, IS_WRITE, artifactAccess)) {
        Uns32 preempt = *(Uns32 *)data;

        Uns32 target = indexFromUserData(userData, T_MAX);
        Uns32 id     = bitIndexFromWordOffset(offset, ANDES_PREEMPT_NUM_REGS);

        if (ANDES_PREEMPT[target][id] != preempt) {
            ANDES_PREEMPT[target][id] = preempt;
            evaluate();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// MODEL CONSTRUCTION
////////////////////////////////////////////////////////////////////////////////

static void netCallbacks() {
    //
    // Allocate the ports
    //
    irqS = (ppmNetHandle *) calloc(config.sources, sizeof(ppmNetHandle));
    irqT = (ppmNetHandle *) calloc(config.targets, sizeof(ppmNetHandle));

    Uns32 iter;
    char name[32];
    for (iter=0; iter<config.sources; iter++) {
        Uns32 irq = iter+1;
        sprintf(name, "irqS%d", irq);

        irqS[iter] = ppmOpenNetPort(name);
        ppmInstallNetCallback(irqS[iter], irqUpdate, UNS32_TO_PTR(irq));
    }

    for (iter=0; iter<config.targets; iter++) {
        sprintf(name, "irqT%d", iter);
        irqT[iter] = ppmOpenNetPort(name);
    }

    if (ANDES_EXTENSIONS) {
        if (andesVectoredIntSupported) {
            iid   = (ppmNetHandle *) calloc(config.targets, sizeof(ppmNetHandle));
            iack  = (ppmNetHandle *) calloc(config.targets, sizeof(ppmNetHandle));

            for (iter=0; iter<config.targets; iter++) {
                sprintf(name, "t%d_eiid", iter);
                iid[iter] = ppmOpenNetPort(name);

                sprintf(name, "t%d_eiack", iter);
                iack[iter] = ppmOpenNetPort(name);

                if (iack[iter] != PPM_INVALID_HANDLE) {
                    ppmInstallNetCallback(iack[iter], iackUpdate, UNS32_TO_PTR(iter));
                }
            }
        }
    }
}


//
// Add Priority registers
// - one word per interrupt source
// - Andes only: register at address for irqS0 is the FeatureEnable register
// - All others: register at address for irqS0 is reserved
//
static void addPriorityRegisters() {
    char name[32];
    char desc[128];
    Uns32 id;

    for(id = 0; id <= config.sources; id++) {
       Uns32 offset = config.PriorityBase + (id * WORDBYTES);

       if (id == 0) {
           if (ANDES_EXTENSIONS) {
               // Andes PLIC extension adds Feature Enable register at priority[0] reserved location
               sprintf(name, "FeatureEnable");
               sprintf(desc, "AndesCore PLIC Feature Enable Register");
               ppmCreateNByteRegister(name, desc, handles.port0, offset, WORDBYTES,
                       andesFeatureRD, andesFeatureWR, /*viewCB*/NULL,
                       &andesFeature,
                       /*userData*/NULL, /*isVolatile*/True, /*readable*/True, /*writable*/True,
                       BHM_ENDIAN_LITTLE);
           } else {
               // priority[0] is a reserved location in PLIC spec, so no register added
               // - Note: accesses will be ignored when IGNORE_RESERVED_ACCESS is enabled
           }
       } else {
           sprintf(name, "Priority%d", id);
           sprintf(desc, "Priority of Input Interrupt Source %d", id);
           ppmCreateNByteRegister(name, desc, handles.port0, offset, WORDBYTES,
                   priorityRD, priorityWR, /*viewCB*/NULL,
                   &PRIORITY[id],
                   UNS32_TO_PTR(id), /*isVolatile*/True, /*readable*/True, /*writable*/True,
                   BHM_ENDIAN_LITTLE);
       }
    }
}

//
// Add Pending registers
// - One bit per interrupt source
// - irqS numbered from 1..sources, with id 0, bit 0 hardwired to 0 by the write routine
//
static void addPendingRegisters() {
    char  name[32];
    char  desc[128];
    Uns32 id;

    for (id = 0; id * WORDBITS <= config.sources; id++) {
        Uns32 offset = config.PendingBase + (id * WORDBYTES);

        sprintf(name, "Pending%d", id);
        sprintf(desc, "Pending Interrupt Register for Interrupts %d downto %d",
                (id*WORDBITS)+WORDBITS-1, (id*WORDBITS));
        ppmCreateNByteRegister(name, desc, handles.port0, offset, WORDBYTES,
                pendingRD, pendingWR, /*viewCB*/NULL,
                &PENDING[id],
                UNS32_TO_PTR(id), /*isVolatile*/True, /*readable*/True, /*writable*/True,
                BHM_ENDIAN_LITTLE);
    }
}

//
// Add target enable registers
// - one bit per source for each target
// - parameter EnablesStride specifies stride between register blocks for each target
//
static void addTargetEnableRegisters() {
    char  name[32];
    char  desc[128];
    Uns32 target;
    Uns32 id;

    for (target=0; target < config.targets; target++) {
        Uns32 enableBase = config.EnablesBase + (target * config.EnablesStride);

        for (id = 0; id * WORDBITS <= config.sources; id++) {
            Uns32 offset = enableBase + (id * WORDBYTES);

            sprintf(name, "Target%d_Enable%d", target, id);
            sprintf(desc, "Target %d: Enable Register for Interrupts %d downto %d",
                    target, (id*WORDBITS)+WORDBITS-1, (id*WORDBITS));
            ppmCreateNByteRegister(name, desc, handles.port0, offset, WORDBYTES,
                    enableRD, enableWR, /*viewCB*/NULL, &ENABLE[target][id],
                    UNS32_TO_PTR(target),
                    /*isVolatile*/True,  /*readable*/True, /*writable*/True,
                    BHM_ENDIAN_LITTLE);
        }
    }
}

//
// Add target Threshold and Claim registers
// - each are one word per target
// - parameter ContextStride specifies stride between register blocks for each target
//
static void addTargetThreshClaimRegisters() {
    char  name[32];
    char  desc[128];
    Uns32 target;

    for (target=0; target < config.targets; target++) {
        Uns32 contextBase = config.ContextBase + (target * config.ContextStride);

        sprintf(name, "Target%d_Threshold", target);
        sprintf(desc, "Target %d Priority Threshold", target);
        ppmCreateNByteRegister(name, desc, handles.port0, contextBase, WORDBYTES,
                thresholdRD, thresholdWR, /*viewCB*/NULL,
                &THRESHOLD[target],
                UNS32_TO_PTR(target), /*isVolatile*/True,  /*readable*/True, /*writable*/True,
                BHM_ENDIAN_LITTLE);

        sprintf(name, "Target%d_Claim", target);
        sprintf(desc, "Target %d Claim for Source", target);
        ppmCreateNByteRegister(name, desc, handles.port0, contextBase+WORDBYTES, WORDBYTES,
                claimRD, claimWR, claimVIEW,
                &CLAIM[target],
                UNS32_TO_PTR(target), /*isVolatile*/True,  /*readable*/True, /*writable*/True,
                BHM_ENDIAN_LITTLE);
    }
}

//
// Add andes-specific preempted priority registers
// - One bit per priority level for each interrupt source
//
static void addAndesPreemptedPriorityRegisters() {
    char  name[32];
    char  desc[128];
    Uns32 target;
    Uns32 id;

    for (target=0; target < config.targets; target++) {
        Uns32 contextBase = config.ContextBase + (target * config.ContextStride);

        for (id = 0; id <= ANDES_PREEMPT_NUM_REGS; id++) {
            Uns32 offset = contextBase + ANDES_PREEMPT_OFFSET + (id * WORDBYTES);

            sprintf(name, "PreemptedPriorityStack%d", id);
            sprintf(desc, "Andes preempted priority stack Register for priorities %d downto %d",
                    (id*WORDBITS)+WORDBITS-1, (id*WORDBITS));
            ppmCreateNByteRegister(name, desc, handles.port0, offset, WORDBYTES,
                    andesPreemptRD, andesPreemptWR, /*viewCB*/NULL,
                    &ANDES_PREEMPT[target][id],
                    UNS32_TO_PTR(target), /*isVolatile*/True,  /*readable*/True, /*writable*/True,
                    BHM_ENDIAN_LITTLE);
        }
    }
}

//
// Add andes-specific trigger type read-only registers
// - One bit per interrupt source
// - parameter trigger_type<n> specifies the value
//
static void addAndesTriggerTypeRegisters() {
    char  name[32];
    char  desc[128];
    Uns32 id;

    for (id = 0; id * WORDBITS <= config.sources; id++) {
        Uns32 offset = ANDES_TRIGGER_BASE + (id * WORDBYTES);

        sprintf(name, "TriggerType%d", id);
        sprintf(desc, "Andes Trigger Type Register for Interrupts %d downto %d",
                (id*WORDBITS)+WORDBITS-1, (id*WORDBITS));
        ppmCreateNByteRegister(name, desc, handles.port0, offset, WORDBYTES,
                /*readCB*/NULL, /*writeCB*/NULL, /*viewCB*/NULL,
                &ANDES_TRIGGER[id],
                /*userData*/NULL, /*isVolatile*/True, /*readable*/True, /*writable*/False,
                BHM_ENDIAN_LITTLE);

        // Initialise register value from parameters
        sprintf(name, "trigger_type%d", id);
        bhmUns32ParamValue(name, &ANDES_TRIGGER[id]);
        if (id == 0) {
            // Bit 0 of word 0 is hard wired to 0
            ANDES_TRIGGER[0] &= 0xfffffffe;
        }
    }
}

//
// Add Andes-specific configuration registers
//
static void addAndesConfigRegisters() {
    Uns32 version;

    // Andes number of interrupts and targets register (read only)
    num_interrupts_targets.bits.num_interrupt = config.sources;
    num_interrupts_targets.bits.num_target    = config.targets;
    ppmCreateNByteRegister(
            "NumIntsAndTgts",
            "Andes number of interrupts and targets register",
            handles.port0, ANDES_NUM_INTERRUPTS_TARGETS_ADDR, WORDBYTES,
            /*readCB*/NULL, /*writeCB*/NULL, /*viewCB*/NULL,
            &num_interrupts_targets,
            /*userData*/NULL, /*isVolatile*/True, /*readable*/True, /*writable*/False,
            BHM_ENDIAN_LITTLE);

    // Andes version and max priority register register (read only)
    bhmUns32ParamValue("andes_version", &version);
    version_max_priority.bits.version      = version;
    version_max_priority.bits.max_priority = config.priorities;
    ppmCreateNByteRegister(
            "VersionMaxPriority",
            "Andes version and max priority register",
            handles.port0, ANDES_VERSION_MAX_PRIORITY_ADDR, WORDBYTES,
            /*readCB*/NULL, /*writeCB*/NULL, /*viewCB*/NULL,
            &version_max_priority,
            /*userData*/NULL, /*isVolatile*/True, /*readable*/True, /*writable*/False,
            BHM_ENDIAN_LITTLE);
}

static void addAndesVectoredIntPorts() {

}

//
// Add SiFive-specific configuration registers
//
static void addSifiveConfigRegisters() {
    // SiFive PLIC extension adds clock gating register at reserved location
    // at end of interrupt enable region
    ppmCreateNByteRegister(
            "disablePlicClockGateFeature",
            "PLIC Clock Gate Disable Register",
            handles.port0, SIFIVE_CLOCK_GATE_DISABLE_OFFSET, WORDBYTES,
            /*readCB*/NULL, /*writeCB*/NULL, /*viewCB*/NULL,
            &clockGateDisable,
            /*userData*/NULL, /*isVolatile*/True, /*readable*/True, /*writable*/True,
            BHM_ENDIAN_LITTLE);

}

static void modelInit () {

    bhmUns32ParamValue("num_sources",    &config.sources);
    bhmUns32ParamValue("num_targets",    &config.targets);
    bhmUns32ParamValue("num_priorities", &config.priorities);
    bhmUns32ParamValue("priority_base",  &config.PriorityBase);
    bhmUns32ParamValue("pending_base",   &config.PendingBase);
    bhmUns32ParamValue("enable_base",    &config.EnablesBase);
    bhmUns32ParamValue("enable_stride",  &config.EnablesStride);
    bhmUns32ParamValue("context_base",   &config.ContextBase);
    bhmUns32ParamValue("context_stride", &config.ContextStride);
    if (ANDES_EXTENSIONS) {
        bhmBoolParamValue("vector_plic_support", &andesVectoredIntSupported);
    }

    netCallbacks();

    // Check that parameters are legal (and arrays cannot be overflowed)
    if (config.sources > S_MAX) {
        bhmMessage("F", PREFIX, "num_sources=%d, must be <= %d", config.sources, S_MAX);
    }
    if (config.targets > T_MAX) {
        bhmMessage("F", PREFIX, "num_targets=%d, must be <= %d", config.targets, T_MAX);
    }
    if (config.priorities > P_MAX) {
        bhmMessage("F", PREFIX, "num_priorities=%d, must be <= %d", config.priorities, P_MAX);
    }

    addPriorityRegisters();
    addPendingRegisters();
    addTargetEnableRegisters();
    addTargetThreshClaimRegisters();

    if (ANDES_EXTENSIONS) {
        addAndesPreemptedPriorityRegisters();
        addAndesTriggerTypeRegisters();
        addAndesConfigRegisters();
        addAndesVectoredIntPorts();
    }

    //
    // SiFive PLIC extension clock gating register
    //
    if (SIFIVE_EXTENSIONS) {
        addSifiveConfigRegisters();
    }
}

///////////////
// RESET NET //
///////////////

//
// perform reset when net is written with a 1
// Note: Pending and Enable registers have no reset value defined in any specification
//
PPM_NET_CB(resetCB) {
    if(value != 0) {
        Uns32 i, j;

        if (PSE_DIAG_LOW) {
            bhmMessage(
                "I", PREFIX "_RST", "Reset PLIC device");
        }

        clockGateDisable = 1;
        andesFeature = 0;

        // Priority registers irqS[0..sources]
        for(i = 0; i <= config.sources; i++) {
            if (ANDES_EXTENSIONS) {
                // Priority registers have reset values defined only in
                // the Andes specification
                PRIORITY[i] = 1;
            }
        }

        for (i = 0; i < config.targets; i++) {
            if (ANDES_EXTENSIONS) {
                // Priority threshold and claim/complete registers have reset values
                // defined only in the Andes specification
                THRESHOLD[i] = 0;
                CLAIM[i]     = 0;
            }

            // Reset output net values
            writeNet(irqT[i], 0);
            if (ANDES_EXTENSIONS) {
                if (andesVectoredIntSupported) {
                    writeNet(iid[i], 0);
                }
            }
        }

        // Andes PLIC Extension preempted priority stack registers
        if (ANDES_EXTENSIONS) {
            for (i = 0; i < config.targets; i++) {
                for (j = 0; j < ANDES_PREEMPT_NUM_REGS; j++) {
                    ANDES_PREEMPT[i][j] = 0;
                }
            }
        }
    }
}


PPM_CONSTRUCTOR_CB(constructor) {
    periphConstructor();
    modelInit();
    resetCB(1, 0);
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
    bhmMessage("E", "PPM_RSNI", "Model does not implement save/restore");
}
