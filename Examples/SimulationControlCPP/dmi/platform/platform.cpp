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

//
// This OP C++ platform demonstrates the use of a Direct Memory Interface (DMI)
// scheme to accelerate accesses to memory regions. Without the use of DMI all
// accesses will be performed using memory callbacks on regions.
//

#include <iostream>
#include <string.h>

using namespace std;

#include "op/op.hpp"
using namespace op;

#include "memory.hpp"

#include "or1k.hpp"

//
// This slave device implements most of the memory space.
// The region C0000000-C0000fff is a peripheral device, always implemented as callbacks.
// The region C0001000-C0001fff is not implemented, but used to demonstrate how this is handled
// The rest is memory, implemented initially as callbacks which access pages
// of native memory, but then negotiated as DMI.
// Memory pages are maintained by the memory manager. Used pages can be
// disconnected from DMI using the DMI invalidate method, then reconnected
// when DMI renegotiates.
//

/////////////////////////////////////////// PERIPHERAL ////////////////////////////////////////////

class periphSlave : public decode {

    Addr lo, hi;

    bool read(
        object       *initiator,
        Addr          addr,
        Uns32         bytes,
        void*         data,
        void*         userData,
        Addr          VA,
        bool          isFetch
    ) {

        Uns64 value = 0x12345678;
        bool  ok;

        switch(bytes) {
            case 1:    *(Uns8* )data = value;       ok = true;   break;
            case 2:    *(Uns16*)data = value;       ok = true;   break;
            case 4:    *(Uns32*)data = value;       ok = true;   break;
            default:                                ok = false;  break;
        }

        cout << "periphSlave: Read at 0x" << addr << endl;
        return ok;
    }

    bool write(
        object       *initiator,
        Addr          addr,
        Uns32         bytes,
        const void*   data,
        void*         userData,
        Addr          VA
    )  {
        Uns32 v = 0;
        bool  ok;

        switch(bytes) {
            case 1:    v = *(Uns8* )data;            ok = true;  break;
            case 2:    v = *(Uns16*)data;            ok = true;  break;
            case 4:    v = *(Uns32*)data;            ok = true;  break;
            default:                                 ok = false; break;
        }

        cout << "periphSlave: Write at 0x" << addr << ":" << v << endl;
        return ok;
    }


    void *getDMI(
        Addr        addr,
        Uns32       bytes,
        Addr       &addrLo,
        Addr       &addrHi,
        DMIaccess  &rw
    ) {
        cout << "periphSlave: DMI REJECTED  0x" << hex << lo << ":0x" << hi << endl;
        addrLo = lo;
        addrHi = hi;
        return 0;
    }

  public:
    periphSlave(Addr lo, Addr hi, decode *prev)
       : decode(lo, hi,prev)
       ,lo(lo)
       ,hi(hi)
    { }

    ~periphSlave() {

    }

};

//////////////////////////////////////////////// RAM //////////////////////////////////////////////

class ramSlave : public decode {

    Addr         pageSize;
    Addr         mask;

    nativeMemory mem;

    //
    // Return the segment that contains the given address.
    // Also return the limits of the segment and the offset of address from the base
    // of the segment.
    //
    memorySegment *getSeg(Addr addr, Uns32 bytes, Addr &lo, Addr &hi, Addr &offset) {

        memorySegment *seg = mem.findSeg(addr, bytes);
        if(!seg) {
            // Need to make a new segment

            // top of region
            Addr last = addr + bytes - 1;

            // base of two pages
            Addr basePage  = addr & mask;
            Addr highPage  = last & mask;

            Addr topPage   = highPage + pageSize - 1;

            seg    = mem.addSeg(basePage, topPage);
            offset = addr - basePage;

            cout << "ramSlave: New segment     : lo:0x" << hex << seg->base() << " hi:" << seg->top() << endl;
        } else {
            offset = addr - seg->base();

            cout << "ramSlave: Existing segment: lo:0x" << hex << seg->base() << " hi:" << seg->top() << endl;
        }

        lo     = seg->base();
        hi     = seg->top();
        return seg;
    }

    //
    // Return the base of the page containing the native address
    // of the requested simulated address, allocating the space if required
    //
    Uns8 *getPageBase(Addr addr, Uns32 bytes, Addr &lo, Addr &hi) {

        Addr offset;
        memorySegment *seg = getSeg(addr, bytes, lo, hi, offset);
        return seg->native();
    }

    //
    // Return the native address of the requested simulated address,
    // allocating the space if required
    //
    Uns8 *getInPage(Addr addr, Uns32 bytes) {

        Addr lo, hi, offset;
        memorySegment *seg = getSeg(addr, bytes, lo, hi, offset);
        return offset + seg->native();
    }

    bool read(
        object       *initiator,
        Addr          addr,
        Uns32         bytes,
        void*         data,
        void*         userData,
        Addr          VA,
        bool          isFetch
    ) {
        cout << "ramSlave: Read at 0x" << hex << addr << ":0x" << addr + bytes -1 << endl;
        Uns8  *native = getInPage(addr, bytes);

        // If we get to here, there's been a read from uninitialized memory
        switch(bytes) {
            case 1:    *(Uns8* )data = *(Uns8 *)native;    break;
            case 2:    *(Uns16*)data = *(Uns16*)native;    break;
            case 4:    *(Uns32*)data = *(Uns32*)native;    break;
            default:   memcpy(data, native, bytes);        break;
        }
        return true;
    }

    bool write(
        object       *initiator,
        Addr          addr,
        Uns32         bytes,
        const void*   data,
        void*         userData,
        Addr          VA
    ) {
        cout << "ramSlave: Write at 0x" << hex << addr <<  ":0x" << addr + bytes -1 << endl;
        Uns8 *native = getInPage(addr, bytes);

        switch(bytes) {
           case 1:    *(Uns8* )native = *(Uns8* )data;    break;
           case 2:    *(Uns16*)native = *(Uns16*)data;    break;
           case 4:    *(Uns32*)native = *(Uns32*)data;    break;
           default:   memcpy(native, data, bytes);        break;
        }
        return true;
    }

    void *getDMI(
        Addr        addr,
        Uns32       bytes,
        Addr       &addrLo,
        Addr       &addrHi,
        DMIaccess  &rw
    ) {
        rw = RW;
        cout << "ramSlave: DMI at 0x"  << hex << addr << " ACCEPTED" << endl;
        return getPageBase(addr, bytes, addrLo, addrHi);
    }

  public:
    ramSlave(Addr loAddr, Addr hiAddr, Addr ps, decode *prev)
      : decode(loAddr, hiAddr, prev)
      , pageSize(ps)
      , mem(ps)
    {
        mask = ~(ps - 1);
    }

    ~ramSlave() {
    }

};

class slaveDevice : public busDMISlave {

  private:
    periphSlave *p1;
    ramSlave    *r1;
    ramSlave    *head;

  public:

    slaveDevice(bus &b, const char *name, Addr lo, Addr hi, Addr ps)
       : busDMISlave(b, name, 0, OP_PRIV_RWX, lo, hi, true, 0)
    {
        p1   = new periphSlave(0xc0000000, 0xc0000FFF, 0);
        r1   = new ramSlave   (0         , 0xBFFFFFFF, 4096, p1);
        head = new ramSlave   (0xC0003000, 0xFFFFFFFF, 4096, r1);
    }

    ~slaveDevice() {
        delete head;
        delete p1;
        delete r1;
    }

    //
    // Overload virtual read function with a decoder
    //
    bool read(
            object       *inititator,
            Addr          addr,
            Uns32         bytes,
            void*         data,
            void*         userData,
            Addr          VA,
            bool          isFetch,
            bool         &dmi
    ) {
        decode *tgt = head->find(addr);
        if(tgt) {
            dmi = true;
            return tgt->read(inititator,addr,bytes,data,userData,VA,isFetch);
        } else {
            inititator->readAbort(addr);
            return false;
        }
    }
    
    //
    // Overload virtual write function with a decoder
    //
    bool write(
            object       *inititator,
            Addr          addr,
            Uns32         bytes,
            const void*   data,
            void*         userData,
            Addr          VA,
            bool         &dmi
    ) {
        decode *tgt = head->find(addr);
        if(tgt) {
            dmi = true;
            return tgt->write(inititator,addr,bytes,data,userData,VA);
        } else {
            inititator->writeAbort(addr);
            return false;
        }
    }
    
    //
    // Overload virtual DMI function. Return the base of the native memory
    // that is mapped into the DMI region and set the limits of the region
    //
    void *getDMI(Addr addr, Uns32 bytes, Addr &lo, Addr &hi, DMIaccess &d, void *userData) {

        decode *tgt = head->find(addr);
        if(tgt) {
            return tgt->getDMI(addr,bytes, lo, hi, d);
        } else {
            return 0;
        }
    }
};


/////////////////////////////////////////////////////////////////////
//
// Top level of platform. Consists of:
//   OR1K processor
//   One bus
//   One Slave device that implements the whole memory space.

class top : public module {

    private:

        params paramsForRoot(void) {
            params p;
            p.set("verbose", true);
            return p;
        }

        params paramsForCpu(void) {
            params p;
            p.set("defaultsemihost", true);
            return p;
        }

    public:
        bus           bus1;
        or1k          cpu;
        slaveDevice   system;

        top(const char *name="top")
          : module (name,paramsForRoot())
          , bus1   (*this, "b1",    32)
          , cpu    (*this, "cpu",   paramsForCpu())
          , system (bus1,  "system" ,0x0, 0xffffffff, 4096)
        {
            // connections
            bus1.connect(cpu, "INSTRUCTION");
            bus1.connect(cpu, "DATA");

            cpu.applicationLoad("application/hello.OR1K.elf", OP_LDR_SET_START|OP_LDR_FAIL_IS_ERROR);
        }
};

////////////////////////////////// MAIN ///////////////////////////////////////////////

int main(int argc, const char *argv[]) {

    // session control
    session ses;
    
    // standard command line parser
    parser  par(argc, argv);
    
    // platform
    top     top;
    
    cout << "Harness: simulate some instructions" << endl;
    // Run until past the peripheral accesses are complete
    // Message "periphSlave: Write at 0xc0000fff:78"
    top.cpu.simulate(3758);

    cout << "Harness: Invalidate region (0xffff0000 to 0xffffffff)" << endl;
    // invalidate the STACK
    top.system.invalidateDMI(0xffff0000, 0xffffffff);

    cout << "Harness: simulate until exit" << endl;
    optStopReason sr = top.cpu.simulate(10000);

    cout << "Harness: stopped with reason:" << sr << endl;
}
