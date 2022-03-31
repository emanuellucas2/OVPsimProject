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

#include <stdlib.h>
#include "pse.igen.h"

#define PORT_SIZE 4

static void portMap(void) {
    ppmCreateDynamicSlavePort(
        "hostif",
        hostif_ab_data.remap.value,
        PORT_SIZE,
        handles.hostif
    );
}

PPM_NBYTE_WRITE_CB(writeRemap) {

    bhmMessage("I", "MAP", "Old Mapping 0x%0x", hostif_ab_data.remap.value);

    // Delete previous mapping
    ppmDeleteDynamicSlavePort("hostif", hostif_ab_data.remap.value, PORT_SIZE);


    hostif_ab_data.remap.value = *(Uns32*)data;

    bhmMessage("I", "MAP", "New Mapping 0x%0x", hostif_ab_data.remap.value);

    portMap();
}

PPM_CONSTRUCTOR_CB(constructor) {

    handles.hostif = malloc(PORT_SIZE);

    periphConstructor();

    portMap();
}

PPM_DESTRUCTOR_CB(destructor) {
}


PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}


