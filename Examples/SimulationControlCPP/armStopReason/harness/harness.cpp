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


/* This C++ platform demonstrates some features of OVPsim */

#include <iostream>

using namespace std;

#include "op/op.hpp"
using namespace op;


#include "arm_Cortex-A57MPx1.hpp"

///////////////////////// NET WITh CALLBACK THAT WRITES TO ANOTHER NET ////////

class repeater : public netWithCallback {

  private:

    net &writeTo;

  public:
    void written(Uns32 value) {
        static Uns32 triggered;

        if(!triggered) {

            cout << "LOG: *** SEV DETECTED: raise reset ****" << endl;

            // raise reset initially
            writeTo.write(1);

            triggered = 1;
        }
    }

    repeater(module &parent, string name, net &other)
        : netWithCallback (parent, name)
        , writeTo(other)
    {
    }
};

//////////////////////////////////////// PLATFORM /////////////////////////////

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
            p.set("endian", "little");
            p.set("simulateexceptions", true);
            p.set("addrbits", (Uns32)44);
            return p;
        }

    public:
        arm_Cortex_A57MPx1  cpu;
        net                 reset;
        net                 fiq;
        net                 EVENTI;
        repeater            EVENTO;

        top(const char *name="top")
          : module (name,paramsForRoot())
          , cpu    (*this, "cpu",   paramsForCpu())
          , reset  (*this, "reset")
          , fiq    (*this, "fiq")
          , EVENTI (*this, "EVENTI")
          , EVENTO (*this, "EVENTO", reset)
        {
            fiq.connect    (cpu, "fiq_CPU0");
            reset.connect  (cpu, "reset_CPU0");
            EVENTI.connect (cpu, "EVENTI");
            EVENTO.connect (cpu, "EVENTO");

            cpu.applicationLoad("application/asm.AARCH64.elf", OP_LDR_SET_START|OP_LDR_FAIL_IS_ERROR);
        }
};

#define IMP_ARM_REASON_WFE     (1<<0)
#define IMP_ARM_REASON_WFI     (1<<1)
#define IMP_ARM_REASON_RESET   (1<<2)

static Uns8 getHaltReasonDetail(processor *p) {

    Uns8 result;

    if(p->regRead("HaltReason", &result)) {
        return result;
    } else {
        op::message::print("E", "HARNESS", "Unable to find HaltReason");
        return 0;
    }
}


////////////////////////////////// MAIN ///////////////////////////////////////////////

int main(int argc, const char *argv[]) {

    // session control
    session    ses;
    
    // standard command line parser
    parser     par(argc, argv);
    
    // platform
    top        t;
    
    t.preSimulate();

    // Find the processor in the platform
    processor *cpu = t.processorByName("top/cpu");
    processor *pe  = cpu->child();
    
    for(;;) {
        optStopReason SR = pe->simulate(100000);
        switch(SR) {
            case OP_SR_EXIT:
            case OP_SR_FINISH:
                goto end;
                break;

            case OP_SR_SCHED: {

                Uns32 detail = getHaltReasonDetail(pe);

                if(detail) {
                    cout << "LOG: *** EXPECTED ZERO HALT REASON: " << detail << " ****" << endl;
                }
                break;
            }

            case OP_SR_HALT: {

                Uns32 detail = getHaltReasonDetail(pe);

                cout << "LOG: *** DETAIL: " << detail << endl;

                if(detail & IMP_ARM_REASON_WFE) {
                    cout << "LOG: *** IN WFE: send event ****" << endl;
                    t.EVENTI.write(1);
                    t.EVENTI.write(0);
                }

                if(detail & IMP_ARM_REASON_WFI) {
                    cout << "LOG: *** IN WFI: raise interrupt ****" << endl;
                    t.fiq.write(1);
                    pe->simulate(1);
                    t.fiq.write(0);
                }

                if(detail & IMP_ARM_REASON_RESET) {
                    cout << "LOG: *** IN RESET: lower it ****" << endl;
                    t.reset.write(0);
                }

                break;
            }

            default:
                cout << "LOG: *** UNEXPECTED STOPREASON " << SR <<  " ****" << endl;
        }
    }
  end:
    cout << "LOG: done" << endl;
}
