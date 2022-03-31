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

#pragma once

#include <iostream>
#include <string.h>

using namespace std;

//
// This memory manager is inefficient but illustrates
// how a memory manager might be interfaced to OP.
// The page size is small (4096) for this example.
// In a real memory manager the host machine page size is a reasonable compromise.
//

//
// This memory manager will FAIL if a smaller block is later re-requested as a larger block.
//

/////////////////////////////////////// NATIVE RAM ////////////////////////////////////////////////

//
// A linked list of allocated segments
//
class memorySegment {

  private:
    Addr           segBase;
    Addr           segTop;
    Uns8          *segNative;
    memorySegment *next;

  public:
    memorySegment(Addr base, Addr top)
       : segBase(base)
       , segTop (top)
       , next(0)
    {
        segNative = new Uns8[top - base + 1];
    }

    void link(memorySegment *n) {
        next = n;
    }

    memorySegment *link(void) {
        return next;
    }

    Addr  base (void)  { return segBase;   }
    Addr  top  (void)  { return segTop;  }
    Uns8 *native(void) { return segNative; }
};


//
// Memory is allocated in whole pages.
// A segment is a contiguous block of pages.
//
class nativeMemory {

  private:
    Uns32           pageSize;
    memorySegment  *head;
    memorySegment **tailp;

  public:
    nativeMemory(Uns32 ps)
        : pageSize(ps)
        , head(0)
    {
        tailp = &head;
    }

    memorySegment *addSeg(Addr base, Addr top) {
        memorySegment *seg = new memorySegment(base, top);
        seg->link(*tailp);
        *tailp = seg;
        return seg;
    }

    ~nativeMemory() {
        memorySegment *seg, *next;

        for(seg = head; seg; seg = next) {
            next = seg->link();
            delete seg;
        }
    }
    //
    // Find the segment that this address fits in
    //
    memorySegment *findSeg(Addr addr, Uns32 n) {
        memorySegment *seg;
        for(seg = head; seg; seg = seg->link()) {
            if( addr >= seg->base() && (addr + n - 1) <=  seg->top()) {
                return seg;
            }
        }
        return 0;
    }
};
