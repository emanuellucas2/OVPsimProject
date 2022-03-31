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

//#define DEBUG_TLB

#include "hostapi/impAlloc.h"
#include "vmi/vmiMessage.h"
#include "vmi/vmiRt.h"

#include "microblazeTLB.h"
#include "microblazeExceptions.h"
#include "microblazeUtils.h"

static void allocTableTLB(TLBtableP table, Uns8 size) {
    table->entry = STYPE_CALLOC_N(TLBentry, size);
    table->size  = size;
}

static void freeTableTLB(TLBtableP table) {
    STYPE_FREE(table->entry);
}

static void flushTLBEntry(microblazeP microblaze, TLBentryP entry) {

    microblazeVMMode mode;

    for(mode=VM_MODE_FIRST_VIRTUAL; mode<=VM_MODE_LAST_VIRTUAL; mode++) {

        if(entry->simPriv[mode]) {

            Uns32 size   = 1<<(10+entry->HI.SIZE*2);
            Uns32 lowVA  = entry->HI.reg & ~(size-1);
            Uns32 highVA = lowVA + size - 1;
            Uns32 TID    = entry->TID;

            vmirtUnaliasMemoryVM(
                microblaze->vDomain[mode],
                lowVA,
                highVA,
                TID==0,
                TID
            );
#if defined(DEBUG_TLB)
            vmiMessage("I", "TLB_UNMAP", "%u VAL=%08x VAH=%08x TID=%u",
                mode, lowVA, highVA, TID);
#endif
            entry->simPriv[mode] = MEM_PRIV_NONE;
        }
    }
}
void microblazeConstructMMU(microblazeP microblaze) {
    //
    // If the MMU is enabled
    //
    if (microblaze->SPR_PVR0.MMU) {
        allocTableTLB(&microblaze->utlb, UTLBENTRIES);
    }
}

void microblazeDestructMMU(microblazeP microblaze) {
    //
    // If the MMU is enabled
    //
    if (microblaze->SPR_PVR0.MMU) {
        freeTableTLB(&microblaze->utlb);
    }
}

static Uns32 getTLBindex(microblazeP microblaze) {
    return microblaze->SPR_TLBX.INDEX;
}

void microblazeWriteTLBHI(microblazeP microblaze) {
    TLBtableP table = &microblaze->utlb;
    TLBentryP entry = &table->entry[getTLBindex(microblaze)];
    flushTLBEntry(microblaze, entry);

#if defined(DEBUG_TLB)
    vmiMessage("I", "MB_TLB", "microblazeWriteTLBHI idx=%d value=0x%08x pid=%d\n",
            getTLBindex(microblaze), microblaze->SPR_TLBHI.reg, microblaze->SPR_PID.PID);
#endif

    entry->HI.reg = microblaze->SPR_TLBHI.reg;
    entry->TID    = microblaze->SPR_PID.PID;
#if defined(DEBUG_TLB)
    microblazePrintTLB(microblaze, False);
#endif
}

void microblazeWriteTLBLO(microblazeP microblaze) {
    TLBtableP table = &microblaze->utlb;
    TLBentryP entry = &table->entry[getTLBindex(microblaze)];

    flushTLBEntry(microblaze, entry);

#if defined(DEBUG_TLB)
    vmiMessage("I", "MB_TLB", "microblazeWriteTLBLO idx=%d value=0x%08x\n", getTLBindex(microblaze), microblaze->SPR_TLBLO.reg);
#endif

    entry->LO.reg = microblaze->SPR_TLBLO.reg;
#if defined(DEBUG_TLB)
    microblazePrintTLB(microblaze, False);
#endif
}

void microblazeReadTLBHI(microblazeP microblaze) {
    TLBtableP table = &microblaze->utlb;

    microblaze->SPR_TLBHI.reg    = table->entry[getTLBindex(microblaze)].HI.reg;
    if (microblaze->SPR_MSR.UM == 0) {
        microblaze->SPR_PID.PID = table->entry[getTLBindex(microblaze)].TID;
    }

#if defined(DEBUG_TLB)
    vmiMessage("I", "MB_TLB", "microblazeReadTLBHI idx=%d value=0x%08x pid=%d\n",
            getTLBindex(microblaze), table->entry[getTLBindex(microblaze)].HI.reg,
            microblaze->SPR_PID.PID);
#endif
}

void microblazeReadTLBLO(microblazeP microblaze) {
    TLBtableP table = &microblaze->utlb;

#if defined(DEBUG_TLB)
    vmiMessage("I", "MB_TLB", "microblazeReadTLBLO idx=%d value=0x%08x\n", getTLBindex(microblaze), table->entry[getTLBindex(microblaze)].LO.reg);
#endif
    microblaze->SPR_TLBLO.reg = table->entry[getTLBindex(microblaze)].LO.reg;
}

void microblazeTLBFlush (microblazeP microblaze) {
    TLBtableP table = &microblaze->utlb;
    Uns8  index;
    for(index=0; index<table->size; index++) {
        flushTLBEntry(microblaze, &table->entry[index]);
    }
}

void microblazeTLBPrivReset (microblazeP microblaze) {
    TLBtableP table = &microblaze->utlb;
    Uns8  index;
    for(index=0; index<table->size; index++) {

        microblazeVMMode mode;
        for (mode=VM_MODE_FIRST; mode<VM_MODE_LAST; mode++) {
            table->entry[index].simPriv[mode] = MEM_PRIV_NONE;
        }
    }
}

static Int32 searchTLB(microblazeP microblaze, Uns32 virtualAddress) {
#if defined(DEBUG_TLB)
    vmiMessage("I", "MB_TLB", "Search TLB for VPN=0x%06x PID=0x%02x",
            microblaze->SPR_TLBSX.VPN,
            microblaze->SPR_PID.PID);
#endif
    Uns32 pid = microblaze->SPR_PID.PID;

    //
    // Search the table
    //
    Uns8  index;
    Uns8  matches = 0;
    Int32 match   = -1;

    TLBtableP table = &microblaze->utlb;

    for(index=0; index<table->size; index++) {
        //
        // The Tag and the EPN are under the control of the SIZE
        // so we need to ignore the lower bits
        //
        Uns32 shift = table->entry[index].HI.SIZE * 2;
        Uns32 tag   = table->entry[index].HI.TAG >> shift;
        Uns32 epn   = virtualAddress >> (10 + shift);
        Uns32 valid = table->entry[index].HI.V;
        Uns32 tid   = table->entry[index].TID;

        //
        // Lifted from Manual TLB Access
        //
        if (valid) {
        } else {
            continue;
        }

        if (tid == 0) {
        } else {
            if (tid == pid) {
            } else {
                continue;
            }
        }

        if (epn == tag) {
            //
            // This is now a valid match
            //
            match = index;
            matches++;
        } else {
        }
    }

    if (matches > 1) {
        //
        // This is a software error
        //
#if defined(DEBUG_TLB)
        microblazePrintTLB(microblaze, False);
#endif
        vmiMessage("F", "TLB_DUP", "TLB contains duplicate entries");
    }

    return match;
}

void microblazeSearchTLB(microblazeP microblaze) {

    Int32 index = searchTLB(microblaze, microblaze->SPR_TLBSX.reg & ~MICROBLAZE_SPR_TLBSX_VA_MASK);

    if(index>=0) {
        microblaze->SPR_TLBX.MISS = 0;
        microblaze->SPR_TLBX.INDEX = index;
    } else {
        microblaze->SPR_TLBX.INDEX = 0x3e; // Value based upon a miss
        microblaze->SPR_TLBX.MISS = 1;     // assume a miss unless a match
    }

#if defined(DEBUG_TLB)
    microblazePrintTLB(microblaze, False);
#endif
}

static memPriv accessPriv(microblazeP microblaze, TLBentryP entry, microblazeTLBAction action, Bool *DIZ) {

    microblazeVMMode mode    = microblazeGetVMMode(microblaze);
    Uns32            ZSEL    = entry->LO.ZSEL;
    Uns32            ZP      = (microblaze->SPR_ZPR.reg >> (15-ZSEL)*2) & 3;
    memPriv          priv    = MEM_PRIV_R;

    if(entry->LO.WR) priv |= MEM_PRIV_W;
    if(entry->LO.EX) priv |= MEM_PRIV_X;

    *DIZ = False;

    switch (mode) {
        case VM_MODE_REAL:
            VMI_ABORT("Unexpected mode VM_MODE_REAL");
            break;

        case VM_MODE_VIRTUAL_PRIV:
            switch(ZP) {
               case 2:
               case 3:
                   priv = MEM_PRIV_RWX;
                   break;
               default:
                   break;
            }
            break;

        case VM_MODE_VIRTUAL_USER:
            switch(ZP) {
               case 0:
                   *DIZ = True;
                   priv = MEM_PRIV_NONE;
                   break;
               case 3:
                   priv = MEM_PRIV_RWX;
                   break;
               default:
                   break;
            }
            break;

        default:
            VMI_ABORT("Unexpected mode");
    }

    Bool accessOK =
        ((action==TLBA_LOAD)  && (priv&MEM_PRIV_R)) ||
        ((action==TLBA_STORE) && (priv&MEM_PRIV_W)) ||
        ((action==TLBA_FETCH) && (priv&MEM_PRIV_X));

    return accessOK ? priv : MEM_PRIV_NONE;
}

//
// Determine if the access using the passed virtual address misses the TLB,
// updating the processor state to take an appropriate exception if so.
//
Bool microblazeTLBMiss(
    microblazeP         microblaze,
    microblazeTLBAction action,
    Uns32               va,
    memAccessAttrs      attrs
) {
    Int32 index = searchTLB(microblaze, va);
#if defined(DEBUG_TLB)
    microblazePrintTLB(microblaze, False);
#endif

    if(index>=0) {

        microblazeVMMode mode   = microblazeGetVMMode(microblaze);
        TLBtableP        table  = &microblaze->utlb;
        TLBentryP        entry  = &table->entry[index];
        Uns32            size   = 1<<(10+entry->HI.SIZE*2);
        Uns32            lowVA  = entry->HI.reg & ~(size-1);
        Bool             DIZ;
        memPriv          priv   = accessPriv(microblaze, entry, action, &DIZ);
        Uns32            TID    = entry->TID;

        Uns32            lowPA;
        Uns32            highPA;

        if (microblaze->SPR_PVR11.MMU == 2) {
            lowPA = lowVA;
        } else if (microblaze->SPR_PVR11.MMU == 3){
            lowPA  = entry->LO.reg & ~(size-1);
        } else {
            VMI_ABORT("Unexpected MMU Mode");
        }
        highPA = lowPA + size - 1;

        if(!priv) {
            if(MEM_AA_IS_TRUE_ACCESS(attrs)) {
                microblazeMMUStorageException(microblaze, action, va, DIZ);
            }
            return True;
        }

        switch (mode) {
            case VM_MODE_REAL:
                VMI_ABORT("Unexpected mode VM_MODE_REAL");
                break;

            case VM_MODE_VIRTUAL_PRIV:
            case VM_MODE_VIRTUAL_USER:
                // create the alias
                vmirtAliasMemoryVM(
                    microblaze->pDomain,
                    microblaze->vDomain[mode],
                    lowPA,
                    highPA,
                    lowVA,
                    0,
                    priv,
                    TID==0,
                    TID
                );

#if defined(DEBUG_TLB)
                vmiMessage("I", "TLB_MAP", "%u VAL=%08x VAH=%08x PA=%08x TID=%u PRIV=%u",
                        mode, lowVA, lowVA+size-1, lowPA, TID, priv);
#endif
                // update simulated TLB state
                entry->simPriv[mode] = priv;

                return False;
                break;

            default:
                VMI_ABORT("Unexpected mode");
        }


    } else {

        //
        // call Handler TODO: is this correct
        //
        if(MEM_AA_IS_TRUE_ACCESS(attrs)) {
            microblazeTLBMissException(microblaze, action, va);
        }

        return True;
    }
}

void microblazePrintTLB(microblazeP microblaze, Bool onlyValid) {
    Uns8 index;
    TLBtableP table = &microblaze->utlb;
//    Uns8 indexMatch = microblaze->SPR_TLBX.INDEX;
//    Uns8 indexValid = (microblaze->SPR_TLBX.MISS == 0) ? 1 : 0;
    Bool doPrint;

    vmiPrintf("#######################################################################################\n");
    vmiPrintf("                 Unified TLB Contents\n");
    vmiPrintf("#######################################################################################\n");
    vmiPrintf("  id      TAG SIZE V E U0  TID      RPN EX WR ZSEL W I M G      lowVA     highVA      lowPA         LO         HI\n");
    for(index=0; index<table->size; index++) {
        TLBentryP entry = &table->entry[index];

        Uns32 size   = 1<<(10+entry->HI.SIZE*2);
        Uns32 lowVA  = entry->HI.reg & ~(size-1);
        Uns32 highVA = lowVA + size - 1;
        Uns32 lowPA  = entry->LO.reg & ~(size-1);

        doPrint = onlyValid ? entry->HI.V : True;
        if (doPrint) {
            vmiPrintf("0x%02x",   index);
            vmiPrintf(" 0x%06x",  entry->HI.TAG);
            vmiPrintf("    %1d",  entry->HI.SIZE);
            vmiPrintf(" %1d",     entry->HI.V);
            vmiPrintf(" %1d",     entry->HI.E);
            vmiPrintf("  %1d",    entry->HI.U0);

            vmiPrintf(" 0x%02x",  entry->TID);

            vmiPrintf(" 0x%06x",  entry->LO.RPN);
            vmiPrintf("  %1d",    entry->LO.EX);
            vmiPrintf("  %1d",    entry->LO.WR);
            vmiPrintf("   %2d",   entry->LO.ZSEL);
            vmiPrintf(" %1d",     entry->LO.W);
            vmiPrintf(" %1d",     entry->LO.I);
            vmiPrintf(" %1d",     entry->LO.M);
            vmiPrintf(" %1d",     entry->LO.G);

            if(entry->HI.V) {
                vmiPrintf(" 0x%08x",  lowVA);
                vmiPrintf(" 0x%08x",  highVA);
                vmiPrintf(" 0x%08x",  lowPA);
            }

            vmiPrintf(" 0x%08x",     entry->LO.reg);
            vmiPrintf(" 0x%08x",     entry->HI.reg);

//            if (indexValid && (indexMatch == index)) {
//                vmiPrintf(" *** MATCH ***");
//            }
            vmiPrintf("\n");
        }
    }
    vmiPrintf("\n");
}

