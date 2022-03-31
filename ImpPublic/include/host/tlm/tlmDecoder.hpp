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

#include <assert.h>
#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "tlmBusPort.hpp"

#include "op/op.hpp"

using namespace sc_core;

#define DMI_DEBUG 0

namespace cw {

class tlmModule;
class tlmRam;
class tlmMmc;

//
// One (of possibly several) mapping through a dynamic slave port
//
class portMapping {

private:
    Addr lo;
    Addr hi;
    Addr offset;
    portMapping *next;

public:
    portMapping(Addr lo_n, Addr hi_n, Addr offset_n)
        : lo(lo_n), hi(hi_n), offset(offset_n), next(0){
    }

    portMapping(Addr lo_n, Addr hi_n)
        : lo(lo_n), hi(hi_n), offset(0), next(0){
    }
    void setNext(portMapping *n) { next = n; }
    portMapping *getNext()   { return next;  }

    void getRegion(Addr &l, Addr &h, Addr &o) { l = lo; h = hi; o = offset; }

    Bool matches(Addr lo_s, Addr hi_s) {
        return lo == lo_s && hi == hi_s;
    }

    Bool inRegion(Addr a) {
        return a >= lo && a <= hi;
    }

    Addr offsetInto(Addr a) {
        return a - lo + offset;
    }
    Addr offsetOutOf(Addr a) {
        return a + lo - offset;
    }
};

class tlmDecoder : public sc_module
{

public:
    typedef tlm_generic_payload                           transaction_type;
    typedef simple_target_socket_tagged   <tlmDecoder>    targetSocketType;
    typedef simple_initiator_socket_tagged<tlmDecoder>    initiatorSocketType;
    typedef simple_target_socket          <tlmRam>        ramSocketType;

    Uns32 nextTargetPort(void)    {
        Uns32 r =  targetPortCount++;
        assert(r < NR_OF_TARGETS);
        return r;
    }

    Uns32 nextInitiatorPort(void) {
        Uns32 r = initiatorPortCount++;
        assert(r < NR_OF_INITIATORS);
        return r;
    }


private:
    Uns32 NR_OF_INITIATORS;
    Uns32 NR_OF_TARGETS;

    portMapping **decodes;
    bool  traceOn;
    Uns32 initiatorPortCount;
    Uns32 targetPortCount;

    tlmModule &parentModule;

    targetSocketType *nextTarget(void) {
        Uns32 port = nextTargetPort();
        return &target_socket[port];
    }

    initiatorSocketType *initiator_socket;
    targetSocketType    *target_socket   ;

public:
    //
    // Use this to connect to a non-Imperas initator socket;
    // e.g. myInstance.initiator_socket(*decoder.nextTargetSocket()
    //
    targetSocketType    *nextTargetSocket() { return nextTarget(); }

    //
    // Use this to connect to a non-Imperas target socket
    // e.g.  decoder.nextInitiatorSocket(0x10000000, 0x1fffffff)->bind(my.target_socket);
    //
    initiatorSocketType *nextInitiatorSocket(Addr lo, Addr hi);

    // constructor
    tlmDecoder (tlmModule &parent, sc_module_name name, Uns32 targets,  Uns32 initiators);

    //
    // legacy methods to set up a decoder. Better to use connect()
    // which connects and sets the decode at the same time
    //
    void setDecode(Uns32 portId, Addr lo, Addr hi, Addr offset);
    void setDecode(Uns32 portId, Addr lo, Addr hi) { setDecode(portId, lo, hi , 0); }

    // turn on/off tracing during simulation
    void trace(bool on) { traceOn = on; }

    // connect to Imperas bus slave
    void connect(tlmBusSlavePort &slave, Addr lo, Addr hi);

    // connect to Imperas bus slave without addresses
    void connect(tlmBusSlavePort &slave);

    // connect to Imperas bus slave
    void connect(tlmBusDynamicSlavePort &slave);

    // connect to tlm RAM
    void connect(ramSocketType &slave, Addr lo, Addr hi);

    // No address specified; plug-and-play
    void connect(ramSocketType &slave);

    // connect to another decoder
    void connect(tlmDecoder &targetDecoder, Addr lo, Addr hi);

    // connect to another decoder, with an output offset
    void connect(tlmDecoder &targetDecoder, Addr lo, Addr hi, Addr offset);

    // connect to another decoder
    void connect(tlmDecoder &targetDecoder);

    // connect to Imperas bus master port
    void connect(tlmBusMasterPort &master);

    // connect to processor bus master port by name
    void connect(tlmProcessor &processor, std::string portName, Uns32 addrBits);

    // connect to peripheral bus master port by name
    void connect(tlmPeripheral &peripheral, std::string portName, Uns32 addrBits);

    // connect to MMC bus master port by name
    void connect(tlmMMC &mmc, std::string portName, Uns32 addrBits);

    // connect to MMC bus slave port by name
    void connect(tlmMMC &mmc, std::string portName);
     // destructor
    ~tlmDecoder() {}

private:
    portMapping *getMapping(int port, Addr address);

    int getPortId(const Addr address, Addr& offset);
    //
    // LT protocol
    // - forward each call to the target/initiator
    //
    void initiatorBTransport(int SocketId, transaction_type& trans, sc_time& t);

    unsigned int transportDebug(int SocketId, transaction_type& trans);
    //
    // The range has come from the DMI device, but needs to be
    // adjusted by what the decoder does to the addresses.
    //
    void adjustRange(int portId, Addr orig, Addr& low, Addr& high);
    //
    // Cannot use DMI through plug & play devices. This is probably OK for present.
    //
    bool getDMIPointer(int SocketId, transaction_type& trans, tlm_dmi&  dmi_data);
    void invalidateDMIPointers(int port_id,  sc_dt::uint64 start_range,  sc_dt::uint64 end_range);
};

} // end namespace cw
