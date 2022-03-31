/**********************************************************************
  The following code is derived, directly or indirectly, from the SystemC
  source code Copyright (c) 1996-2008 by all Contributors.
  All Rights reserved.

  The contents of this file are subject to the restrictions and limitations
  set forth in the SystemC Open Source License Version 3.0 (the "License");
  You may not use this file except in compliance with such restrictions and
  limitations. You may obtain instructions on how to receive a copy of the
  License at http://www.systemc.org/. Software distributed by Contributors
  under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
  ANY KIND, either express or implied. See the License for the specific
  language governing rights and limitations under the License.
 *********************************************************************/



#pragma once

#include "tlm.h"                                // TLM headers
#include "tlm_utils/simple_target_socket.h"
#include <iostream>
#include <string.h>

#include "op/op.hpp"

using namespace std;
using namespace sc_core;
using namespace tlm;

namespace cw {

/////////////////////////////////////////// MEMORY SEGMENT ////////////////////////////////////////
//
// A linked list of allocated segments
//
class memorySegment {

    static    Uns32 segIndex;

  private:
    Addr           segBase;
    Addr           segTop;
    Uns8          *segNative;
    Uns32          segNumber;

  public:

    memorySegment *next;
    memorySegment *prev;

    memorySegment(Addr base, Addr top)
       : segBase(base)
       , segTop (top)
       , segNumber(segIndex++)
       , next(0)
       , prev(0)
    {
        Addr size = top - base + 1;
        segNative = new Uns8[size];
        memset(segNative,0,size);

        if(0) { opPrintf("memorySegment::memorySegment "); printRange(base, top); opPrintf("\n"); }
    }

    ~memorySegment() {
        delete segNative;
    }

    Addr  base      (void)  { return segBase;   }
    Addr  top       (void)  { return segTop;    }
    Addr  bytes     (void)  { return segTop - segBase + 1; }
    Uns8 *native    (void)  { return segNative; }

    // True if this range falls entirely in this segment
    bool fallsWithin(Addr bot, Addr top) {
        return (bot >= segBase && top <= segTop);
    }

    // True if this range overlaps this segment
    bool hasOverlap(Addr bot, Addr top) {
        if(top<segBase) {
            return false;
        } else if(bot>segTop) {
            return false;
        } else {
            return true;
        }
    }

    static void printRange(Addr lo, Addr hi) {
        opPrintf("range [0x" FMT_Ax ":0x" FMT_Ax "] (" FMT_64u " bytes)", lo, hi, hi-lo+1);
    }

    void print(void) {
        opPrintf("seg %u ", segNumber);
        printRange(segBase, segTop);
        opPrintf(": %p", segNative);
    }

};

////////////////////////////////////////// RAM ////////////////////////////////////////////////////

class tlmModule;

class tlmRam:  public sc_module  {
  private:
    bool            trace;
    Addr            maxAddress;  // upper limit (size-1)
    Addr            maxPage;     // page size -1
    Uns32           segments;    // accounting
    Addr            bytes;       // accounting
    memorySegment  *head;
    memorySegment  *cache;       // most recent
    Addr            addrMask;
    Uns32           memoryWidth; // bytes (not used)
    bool            dmiOn;

  private:
    Addr max(Addr a, Addr b) { return a > b ? a : b; }
    Addr min(Addr a, Addr b) { return a > b ? b : a; }

    // True if any segments are touch by this range
    bool overlapsAny(Addr bot, Addr top) {
        //opPrintf("  overlapsAny "); memorySegment::printRange(bot, top); opPrintf("\n");
        for (memorySegment *seg = head; seg; seg = seg->next) {
            if (seg->hasOverlap(bot, top)) {
                //opPrintf("  overlapsAny YES\n");
                return true;
            }
        }
        //opPrintf("  overlapsAny NO\n");
        return false;
    }

    //
    // For debug only; not normally used
    //
    void checkSegListOrder(void) {
        memorySegment *n;
        for (memorySegment *s = head; s; s = n) {

            assert(s->base() < s->top());

            n = s->next;
            if(n) {
                assert(s->top() < n->base());
            }
        }
    }

    void roundToPageBoundaries(Addr &bot, Addr &top) {
        bot = (bot & addrMask);
        top = (top & addrMask) + maxPage;
    }

    // page size must be a power of 2
    // maxPage is one less
    // onePage makes the whole memory into one page

    void calculatePageSize(Addr maxAddress, bool onePage) {

        Addr defaultPage = (1024 * 1024) - 1;

        maxPage = onePage
                ? maxAddress
                : min (maxAddress, defaultPage);

        // mask has all higher bits set
        addrMask = ~(maxPage);
    }

    // Expand the given boundaries to include any segments they overlap
    void coverRange(Addr &bot, Addr &top) {
        roundToPageBoundaries(bot, top);
        for (memorySegment *seg = head; seg; seg = seg->next) {
            if (seg->hasOverlap(bot, top)) {
                bot = min(bot, seg->base());
                top = max(top, seg->top());
            }
        }
    }

    // Link newSeg after n. Works if n is last or not
    void linkSegAfter(memorySegment *newSeg, memorySegment *n);

    // Link newSeg at start of list. Works if list empty or not
    void linkSegFirst(memorySegment *newSeg);

    void linkSeg(memorySegment *seg);

    // Remove from linked list
    void unlinkSeg(memorySegment *seg) {
        if(0) { printSegments("unlinkSeg:BEFORE"); }

        if(cache == seg) {
            cache = 0;
        }

        if(seg->next) {
            seg->next->prev = seg->prev;
        }

        if(seg->prev) {
            seg->prev->next = seg->next;
        } else if (head == seg) {
            head = seg->next;
        } else {
            abort();
        }

        delete seg;
        if(0) { printSegments("unlinkSeg:AFTER"); }
    }

    void printSegments(const char *s) {
        opPrintf("SEGMENTS:%s ", s);
        for (memorySegment *seg = head; seg; seg = seg->next) {
            seg->print();
            opPrintf(",");
        }
        opPrintf("\n");
    }

  public:
    void setTrace(bool on) { trace = on; }

    memorySegment *findAddSeg(Addr addr, Addr bytes);

    ~tlmRam() {
        memorySegment *seg, *next;

        for(seg = head; seg; seg = next) {
            next = seg->next;
            delete seg;
        }
    }

    Uns32 totalSegments(void) { return segments; }
    Addr  totalBytes   (void) { return bytes; }

  public:

    tlmRam (
        tlmModule      &parent
      , sc_module_name  module_name              ///< SC module name
      , Addr            high_address             ///< memory size (bytes-1)
      , Uns32           memory_width = 4         ///< memory width (bytes)
      , bool            dmi          = true      ///< allow DMI if requested
      , bool            onePage      = false     ///< allocate a single memory-sized page
      , bool            tracing      = false     ///< trace each transaction (pre DMI)
    );

  private:

    Uns8          *getInPage(Addr addr, Addr bytes);

    bool checkAddressRange ( Addr address, Addr bytes) {
        if  ( address + bytes - 1 > maxAddress ) {
            if(trace) {
                opPrintf("TLM: %s : address failure : 0x" FMT_64x " (" FMT_64x " bytes)\n", name(), address, bytes);
            }
            return 0;
        } else {
            return 1;
        }
    }

    bool checkPayloadAddress (tlm_generic_payload &gp) {
        return checkAddressRange(gp.get_address(), gp.get_data_length());
    }

    void  get_delay         (tlm_generic_payload  &gp);

    Uns8 *getDMI            (Addr addr, Uns32 bytes, Addr &addrLo, Addr &addrHi);
    void  custom_b_transport(tlm_generic_payload &payload, sc_time &delay_time);
    Uns32 debug_transport   (tlm_generic_payload &payload);
    bool  get_direct_mem_ptr(tlm_generic_payload &trans, tlm_dmi& dmi_data);
    bool  rwrite            (Addr addr, Uns32 bytes, void* data);
    bool  rread             (Addr addr, Uns32 bytes, void* data);

  public:
    tlm_utils::simple_target_socket<tlmRam>  sp1;

    void dmi(bool on) {   ///< If true, starts DMI, if false stops DMI and invalidates its region
        dmiOn = on;
        if(!on) {
            sp1->invalidate_direct_mem_ptr(0, maxAddress);
        }
    }

};

} // end namespace cw
