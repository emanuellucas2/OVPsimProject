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

#include "op/op.hpp"

extern "C" {
#include "sharedData.h"
}

using namespace op;

#define KEY1        "key1"
#define KEY2        "key2"
#define API_VERSION "1.0.0"

//static OP_SHARED_DATA_LISTENER_FN(listen) {
//    const char *uo = (const char *)userObject;
//    const char *ud = (const char *)userData;
//    opPrintf("Platform: Listener triggered uo:%s ud:%s\n", uo, ud);
//    *ret = *ret + 3;
//}
//
//static void testSharedData(optModuleP  top) {
//
//     // use data shared with extensions
//     optSharedDataHandleP h = opSharedDataFind (top, API_VERSION, KEY1);
//     Int32 i;
//     if(h) {
//         opPrintf("Platform: Adding listener to %s\n", KEY1);
//         const char *obj = "obj";
//         opSharedDataListenerRegister(top, h, listen, (void*)obj);
//
//         opPrintf("Platform: Writing to %s\n", KEY1);
//         i = opSharedDataListenersWrite(h, 3, (void*)"plat");
//         opPrintf("Platform: opSharedDataListenersWrite returns %d\n", i);
//
//         opPrintf("Platform: Removing listener to %s\n", KEY1);
//         opSharedDataListenerUnregister(top, h, listen, (void*)obj);
//
//         opPrintf("Platform: Writing again to %s\n", KEY1);
//         i = opSharedDataListenersWrite(h, 3, (void*)"plat");
//         opPrintf("Platform: opSharedDataListenersWrite(h) returns %d\n", i);
//
//         opPrintf("Platform: opSharedDataGet(h) returns %s\n", (char*)opSharedDataValueGet(h));
//     } else {
//         opPrintf("Platform: key1 not found\n");
//     }
//
//     // check we can create our own
//     opPrintf("Platform: creating own shared data\n");
//     optSharedDataHandleP h2 = opSharedDataFindAdd (top, API_VERSION, KEY2, (void*)"h2");
//     const char *obj2 = "obj2";
//     opSharedDataListenerRegister(top, h2, listen, (void*)obj2);
//     opPrintf("Platform: opSharedDataGet(h2) returns %s\n", (char*)opSharedDataValueGet(h2));
//
//     opSharedDataValueSet(h2, (void*)"new");
//     opPrintf("Platform: opSharedDataGet(h2) returns %s\n", (char*)opSharedDataValueGet(h2));
//
//     opPrintf("Platform: writing own shared data\n");
//     i = opSharedDataListenersWrite(h2, 3, (void*)"plat2");
//     opPrintf("Platform: opSharedDataListenersWrite(h2) returns %d\n", i);
//
//     opPrintf("Platform: deleting own shared data\n");
//     opSharedDataListenerUnregister(top, h2, listen, (void*)obj2);
//     opSharedDataDelete(top, h2);
// }

//int main(int argc, const char *argv[]) {
//
//    opSessionInit(OP_VERSION);
//
//    opCmdParseStd(argv[0], OP_AC_ALL, argc, argv);
//
//    optModuleP       top  = opRootModuleNew(0, "top", 0);
//
//    const char     *path = opVLNVString(0, "ovpworld.org", "processor", "or1k", "1.0", OP_PROCESSOR, OP_VLNV_FATAL);
//    optProcessorP    cpu  = opProcessorNew(top, path, "cpu", 0, 0);
//
//    const char     *app  = "app/main.or32";
//    opProcessorApplicationLoad(cpu, app, OP_LDR_SET_START, 0);
//
//    const char     *plg1  = "plugin/model";
//    const char     *plg2  = "plugin/model";
//    const char     *sh1   = opVLNVString(0, "ovpworld.org", "semihosting", "or1kNewlib", "1.0", OP_EXTENSION, OP_VLNV_FATAL);
//
//    opProcessorExtensionNew(cpu, plg1, "plg1", 0);
//    opProcessorExtensionNew(cpu, plg2, "plg2", 0);
//    opProcessorExtensionNew(cpu, sh1,  "sh1",  0);
//
//    opRootModulePreSimulate(top);
//    testSharedData(top);
//    opRootModuleSimulate(top);
//    opSessionTerminate();
//    return 0;
//}
class simpleDataTrigger : public sharedDataTrigger {

public:
    simpleDataTrigger(sharedData &);
    virtual ~simpleDataTrigger();

private:
    message m;

    void triggered(Int32 id, void *userData) {
        sharedDataContainerP cont = (sharedDataContainerP)userData;
        m.print("I", "SDT", "Triggered id:%d  object1:%s  object2:%s", id, cont->object1, cont->object2);
    }
};

simpleDataTrigger::simpleDataTrigger(sharedData &sd)
    : sharedDataTrigger(sd)
{
}

simpleDataTrigger::~simpleDataTrigger()
{
}


class simplePlatform {

  private:
    Addr      maxAddress;
    session   s;
    parser    p;

    sharedDataContainer local;

    params paramsForP1(void) {
        params p;
        p.set("defaultsemihost", (bool)1);
        return p;
    }

  public:
    module    root;
    vlnv      v;
    processor p1;
    memory    m1;
    bus       b1;
    extension plg1;
    extension plg2;
    extension sh1;
    message   m;

    sharedData        *sd1;
    simpleDataTrigger *sdt1;

    simplePlatform(int argc, const char *argv[]);
};

simplePlatform::simplePlatform(int argc, const char *argv[])
   : maxAddress(0xffffffff)
   , p(argc, argv)
   , p1(root, v.string("ovpworld.org", "processor", "or1k", "1.0", OP_PROCESSOR), "p1", paramsForP1() )
   , m1(root,"m1", maxAddress, OP_PRIV_RWX)
   , b1(root, "b1", 32)
   , plg1(p1, "plugin/model", "plg1")
   , plg2(p1, "plugin/model", "plg2")
   , sh1 (p1, v.string("ovpworld.org", "semihosting", "or1kNewlib", "1.0", OP_EXTENSION, OP_VLNV_FATAL), "sh1")

{
    b1.connect(p1,"DATA");
    b1.connect(p1,"INSTRUCTION");
    b1.connect(m1,"sp1", 0, maxAddress);

    p1.applicationLoad("application/main.or32");

    root.preSimulate();

    local.object1 = "ob1";
    local.object2 = "ob2";

    sd1  = new sharedData(root, API_VERSION, KEY1, 1);
    sdt1 = new simpleDataTrigger(*sd1);

    root.simulate();

    m.print("I", "SDT", "Platform writing to shared data");
    Int32 ret = sd1->write(33, &local);
    m.print("I", "SDT", "Write returns %d", ret);

    root.postSimulate();
    delete sdt1;
    delete sd1;
}

int main(int argc, const char *argv[]) {

    simplePlatform s(argc, argv);

    s.m.print("I", "MAIN", "Finished running C++ harness\n");

    return (s.m.errors() ? 1 : 0);
}

