    mfc0    $t4, $14, 0     # get c0_EPC
    addiu   $t4, $t4, 4     # increment return address
    mtc0    $t4, $14, 0     # update c0_EPC
    eret                    # return from exception
