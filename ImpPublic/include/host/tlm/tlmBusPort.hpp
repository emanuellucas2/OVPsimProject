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

/* Derived from SimpleBusLT by Imperas Software Ltd. */

#pragma once

#include <assert.h>
#include "tlm.h"
#include "tlm_utils/simple_target_socket.h"
#include "tlm_utils/simple_initiator_socket.h"
#include "op/op.hpp"

using namespace op;
using namespace sc_core;
using namespace tlm;
using namespace tlm_utils;

namespace cw {

class tlmModule;
class tlmProcessor;
class tlmPeripheral;
class tlmMMC;

class tlmDiagnostics {

public:
    static void printBytes(Uns8 *ptr, Uns32 bytes) {
        opPrintf("{");
        Uns32 i;
        for(i = 0; i < bytes; i++, ptr++) {
            if(i == 0) {
                opPrintf("%02x", *ptr);
            } else {
                opPrintf(",%02x", *ptr);
            }
        }
        opPrintf("}");
    }

};


class tlmBusStub : public bus {
  private:

  public:
    tlmBusStub(tlmModule &parent, std::string name, Uns32 addrBits);
    ~tlmBusStub() { }
};


class tlmDummySlavePort
{
    typedef simple_target_socket <tlmDummySlavePort> socketType;

public:
    socketType socket;
};


class tlmInitiatorExtension: public tlm_extension<tlmInitiatorExtension> {

private:
    // member variables
    object *initiator;

public:


    /// constructor with processor
    tlmInitiatorExtension(object *p) : initiator(p) { }

    /// constructor without processor (used by peripheral)
    tlmInitiatorExtension(void) : initiator(0) { }

    /// destructor
    ~tlmInitiatorExtension() {}

    /// copy
    void copy_from(const tlm_extension_base &extension) {
        initiator = static_cast<tlmInitiatorExtension const &>(extension).initiator;
    }

    /// clone
    tlm_extension_base* clone() const {
        return new tlmInitiatorExtension(*this);
    }

    processor  *getProcessor () { return static_cast<processor* >(initiator);  }
    peripheral *getPeripheral() { return static_cast<peripheral*>(initiator);  }

};

//
// specific DMI slave to field all callbacks from master
//
class tlmDMIslave : public busDMISlave {

    typedef simple_initiator_socket<tlmDMIslave> socketType;

  private:

    socketType          &sock;
    sc_time              delay;
    tlmProcessor        *processorParent;
    tlmPeripheral       *peripheralParent;
    tlmMMC              *mmcParent;
    tlm_dmi              tmpr;
    tlm_dmi              tmpw;

    bool traceBuses(void);

  public:

    tlmDMIslave(bus &b, std::string name, tlmProcessor *proc, socketType &s);

    tlmDMIslave(bus &b, std::string name, tlmPeripheral *periph, socketType &s);

    tlmDMIslave(bus &b, std::string name, tlmMMC *mmc, socketType &s);

    ~tlmDMIslave(){ }

    void *getDMI(
        Addr        addr,
        Uns32       bytes,
        Addr       &addrLo,
        Addr       &addrHi,
        DMIaccess  &rw,
        void       *userData
    );

    void killDMI(long long unsigned int lo, long long unsigned int hi);

    bool read(
        object       *initiator,
        Addr          addr,
        Uns32         bytes,
        void*         data,
        void*         userData,
        Addr          VA,
        Bool          isFetch,
        bool          &dmiAllowed
    );

    bool write(
        object       *initiator,
        Addr          addr,
        Uns32         bytes,
        const void*   data,
        void*         userData,
        Addr          VA,
        bool          &dmiAllowed
    );
};

class tlmBusMasterPort {

    typedef simple_initiator_socket      <tlmDMIslave> socketType;

private:
    tlmBusStub                busStub;   // class to provide connection
    tlmDMIslave               slave;     // class to provide callbacks
    tlmBusMasterPort         *dflt;      // alternative port for if this is unbound.

public:
    socketType socket;

    /// Constructor
    tlmBusMasterPort(tlmModule &parent, tlmProcessor  *p, std::string name, Uns32 addrBits);
    tlmBusMasterPort(tlmModule &parent, tlmPeripheral *p, std::string name, Uns32 addrBits);
    tlmBusMasterPort(tlmModule &parent, tlmMMC        *p, std::string name, Uns32 addrBits);

     /// Destructor
    ~tlmBusMasterPort() {}

    void bindIfNotBound(void) {
        if (socket.size() == 0) {
            tlmDummySlavePort *dummy = new tlmDummySlavePort();
            socket(dummy->socket);
        }
    }

    void bindIfNotBound(tlmBusMasterPort *d) {
        if (socket.size() == 0) {
            tlmDummySlavePort *dummy=new tlmDummySlavePort();
            socket(dummy->socket);
            dflt = d;
        }
    }

    void dmi(bool on) {
        slave.dmi(on);
    }
};

///////////////////////////////////////// BUS SLAVE PORT //////////////////////////////////////////

class tlmBusSlavePort {

    typedef simple_target_socket<tlmBusSlavePort> socketType;

    private:
        bus            bus1;       // OVP address space for this port
        Addr           bytes;      // size of port (TODO cannot handle full space

        tlmPeripheral *peripheralParent;     // parent
        tlmMMC        *mmcParent;            // parent

        // internal
        void  transport      (tlm_generic_payload &payload);
        void  b_transport    (tlm_generic_payload &payload, sc_time &delay);
        Uns32 debug_transport(tlm_generic_payload &payload);

        bool        traceBuses(void);
        const char *hierCName (void);

    public:

        /// The constructor.
        /// @param parent   Containing module
        /// @param pse      Pointer to the peripheral object.
        /// @param name     Name of the slave port in the OVP model.
        /// @param b        Highest byte decoded by this slave port

        tlmBusSlavePort(tlmModule &parent, tlmPeripheral *pse, std::string name, Addr b);

        tlmBusSlavePort(tlmModule &parent, tlmPeripheral *p, std::string name);

        /// The constructor.
        /// @param parent   Containing module
        /// @param mmc      Pointer to the MMC object.
        /// @param name     Name of the slave port in the OVP model.

        tlmBusSlavePort(tlmModule &parent, tlmMMC *mmc, std::string name);

        /// Destructor (not usually called explicitly).
        ~tlmBusSlavePort() {}

        /// Target port for incoming data access.
        /// This name (socket) must be used in the platform to bind this port.
        socketType socket;
};

//////////////////////////////////////// DYNAMIC BUS SLAVE PORT ///////////////////////////////////

class tlmDynamicPortMapping {
  private:
    Addr lo;
    Addr hi;
    tlmDynamicPortMapping *next;

  public:
    tlmDynamicPortMapping(Addr lo_n, Addr hi_n)
        : lo(lo_n), hi(hi_n), next(0){
    }
    void setNext(tlmDynamicPortMapping *n) { next = n; }
    tlmDynamicPortMapping   *getNext() { return next;  }
    tlmDynamicPortMapping **getNextP() { return &next; }

    Bool matches(Addr lo_s, Addr hi_s) {
        return lo == lo_s && hi == hi_s;
    }

    Bool inRegion(Addr a) {
        return a >= lo && a <= hi;
    }
};

class tlmBusDynamicSlavePort {
    typedef simple_target_socket<tlmBusDynamicSlavePort> socketType;

private:
    bus                     bus1;        // OVP address space for this port
    tlmPeripheral          *peripheralParent;
    tlmMMC                 *mmcParent;
    tlmDynamicPortMapping  *mappings;

    // registered as callbacks on the port
    void         transport      (tlm_generic_payload &payload);
    void         b_transport    (tlm_generic_payload &payload, sc_time &delay);
    unsigned int debug_transport(tlm_generic_payload &payload);
    static void  staticSetPortAddress(void *userData, Addr lo, Addr hi, Bool map);
    void         setPortAddress(Addr lo, Addr hi, Bool map);

    bool traceBuses(void);
public:

    /// The constructor.
    /// @param pse      Pointer to the peripheral object.
    /// @param name     Name of the slave port in the OVP model.
    /// @param addrBits Number of bits is ignored. An artifact bus connection is always made for 64-bits.

    tlmBusDynamicSlavePort(tlmModule &parent, tlmPeripheral *pse, std::string name, Uns32 addrBitsIgnored);

    /// Destructor (not usually called explicitly).
    ~tlmBusDynamicSlavePort() {}

    /// Target port for incoming data access.
    /// This name (socket) must be used in the platform to bind this port.
    socketType socket;
};

} // end namespace cw
