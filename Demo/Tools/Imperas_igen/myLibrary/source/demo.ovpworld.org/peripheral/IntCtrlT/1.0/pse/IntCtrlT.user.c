
////////////////////////////////////////////////////////////////////////////////
//
//                W R I T T E N   B Y   I M P E R A S   I G E N
//
//                           Imperas/OVP Generated
//
////////////////////////////////////////////////////////////////////////////////

#include <string.h>

#include "pse.igen.h"

//////////////////////////////// Callback stubs ////////////////////////////////

PPM_REG_READ_CB(readIen) {
    bhmMessage("I", "PERIPHERAL", "%s: Model does not include behavior", __FUNCTION__);

    return *(Uns32*)user;
}

PPM_REG_READ_CB(readScan) {
    bhmMessage("I", "PERIPHERAL", "%s: Model does not include behavior", __FUNCTION__);

    return *(Uns32*)user;
}

PPM_REG_WRITE_CB(writeIen) {
    bhmMessage("I", "PERIPHERAL", "%s: Model does not include behavior", __FUNCTION__);

    *(Uns32*)user = data;
}

PPM_REG_WRITE_CB(writeLevel) {
    bhmMessage("I", "PERIPHERAL", "%s: Model does not include behavior", __FUNCTION__);

    *(Uns32*)user = data;
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}


