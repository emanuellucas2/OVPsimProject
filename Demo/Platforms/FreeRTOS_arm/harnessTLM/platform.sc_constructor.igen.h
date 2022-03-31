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
//                             Version 20211118.0
//
////////////////////////////////////////////////////////////////////////////////

// This file constructs the platform.
// This file should NOT need to be edited.

#include "tlm/tlmMemory.hpp"
#include "tlm/tlmDecoder.hpp"
#include "tlm/tlmProcessor.hpp"
#include "tlm/tlmPeripheral.hpp"
#include "tlm/tlmBusPort.hpp"
#include "tlm/tlmNetPort.hpp"


using namespace sc_core;
using namespace cw;
////////////////////////////////////////////////////////////////////////////////
//                          ArmCortexMFreeRTOS Class
////////////////////////////////////////////////////////////////////////////////

class ArmCortexMFreeRTOS : public sc_module {
// Bus port pBusP cannot be written in SystemC

  public:
    ArmCortexMFreeRTOS (sc_module_name name);

    tlmRam                memory1;
    tlmRam                memory2;
    tlmModule             Platform;
    tlmDecoder            bus1;
    tlmDecoder            pBusMapped;
    tlmProcessor          cpu1;
    tlmPeripheral         led;
    tlmPeripheral         sw;
    tlmPeripheral         UART0;

    const char *pathForcpu1(void) {
        return opVLNVString(0, "arm.ovpworld.org", "processor", "armm", "1.0", OP_PROCESSOR, OP_VLNV_FATAL);
    }

    const char *pathForled(void) {
        return opVLNVString(0, "ovpworld.org", "peripheral", "ledRegister", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

    const char *pathForsw(void) {
        return opVLNVString(0, "ovpworld.org", "peripheral", "switchRegister", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }

    const char *pathForUART0(void) {
        return opVLNVString(0, "ti.ovpworld.org", "peripheral", "UartInterface", "1.0", OP_PERIPHERAL, OP_VLNV_FATAL);
    }


    params paramsForArmCortexMFreeRTOS() {
        params p;
        p.set("stoponcontrolc", true);
        return p;
    }

    params paramsForcpu1() {
        params p;
        p.set("variant", "Cortex-M3");
        p.set("UAL", true);
        p.set("simulateexceptions", true);
        p.set("endian", "little");
        return p;
    }

    params paramsForled() {
        params p;
        p.set("availableLEDS", (Uns32)8);
        return p;
    }

    params paramsForUART0() {
        params p;
        p.set("console", true);
        p.set("finishOnDisconnect", true);
        p.set("loopback", true);
        return p;
    }
}; /* ArmCortexMFreeRTOS */

////////////////////////////////////////////////////////////////////////////////
//                       ArmCortexMFreeRTOS Constructor
////////////////////////////////////////////////////////////////////////////////

ArmCortexMFreeRTOS::ArmCortexMFreeRTOS (sc_module_name name)
    : sc_module (name)
    , memory1 (Platform, "memory1", 0x3fffffff)
    , memory2 (Platform, "memory2", 0xbeffffff)
    , Platform ("", paramsForArmCortexMFreeRTOS())
    , bus1(Platform, "bus1", 2, 6)
    , pBusMapped(Platform, "pBusMapped", 1, 0)
    , cpu1 ( Platform, pathForcpu1(), "cpu1", paramsForcpu1())
    , led (Platform, pathForled(), "led", paramsForled())
    , sw (Platform, pathForsw(), "sw")
    , UART0 (Platform, pathForUART0(), "UART0", paramsForUART0())
{

    // bus1 masters
    bus1.connect(cpu1, "INSTRUCTION", 32);
    bus1.connect(cpu1, "DATA", 32);

    // bus1 slaves
    led.connect(bus1, "busPort", 0x40004000, 0x40004007); // Peripheral  (0)
    sw.connect(bus1, "busPort", 0x40006000, 0x40006007); // Peripheral  (1)
    UART0.connect(bus1, "bport1", 0x4000c000, 0x4000cfff); // Peripheral  (2)
    bus1.connect(memory1.sp1,0x0, 0x3fffffff); // Memory (3)
    bus1.connect(memory2.sp1,0x41000000, 0xffffffff); // Memory (4)
    bus1.connect(pBusMapped, 0x40100000, 0x4010ffff, 0x0); // Bridge (5)

    // Net connections
    UART0.connect( "irq", cpu1, "_int");

}
