/*
 * QEMU PC keyboard emulation
 *
 * Copyright (c) 2003 Fabrice Bellard
 * Copyright (c) 2006 Openedhand Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * Copyright (c) 2005-2021 Imperas Software Ltd., www.imperas.com
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied.
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "pse.igen.h"

#include "ps2Interface.c.h"

///////////////////////////////// Keyboard Controller Commands //////////////////////////

#define KBD_CCMD_READ_MODE      0x20    /* Read mode bits */
#define KBD_CCMD_WRITE_MODE        0x60    /* Write mode bits */
#define KBD_CCMD_GET_VERSION    0xA1    /* Get controller version */
#define KBD_CCMD_MOUSE_DISABLE  0xA7    /* Disable mouse interface */
#define KBD_CCMD_MOUSE_ENABLE   0xA8    /* Enable mouse interface */
#define KBD_CCMD_TEST_MOUSE     0xA9    /* Mouse interface test */
#define KBD_CCMD_SELF_TEST      0xAA    /* Controller self test */
#define KBD_CCMD_KBD_TEST       0xAB    /* Keyboard interface test */
#define KBD_CCMD_KBD_DISABLE    0xAD    /* Keyboard interface disable */
#define KBD_CCMD_KBD_ENABLE     0xAE    /* Keyboard interface enable */
#define KBD_CCMD_READ_INPORT    0xC0    /* read input port */
#define KBD_CCMD_READ_OUTPORT   0xD0    /* read output port */
#define KBD_CCMD_WRITE_OUTPORT  0xD1    /* write output port */
#define KBD_CCMD_WRITE_OBUF     0xD2
#define KBD_CCMD_WRITE_AUX_OBUF 0xD3    /* Write to output buffer as if
                                           initiated by the auxiliary device */
#define KBD_CCMD_WRITE_MOUSE    0xD4    /* Write the following byte to the mouse */
#define KBD_CCMD_DISABLE_A20    0xDD    /* HP vectra only ? */
#define KBD_CCMD_ENABLE_A20     0xDF    /* HP vectra only ? */
#define KBD_CCMD_RESET          0xFE

/* Keyboard Commands */
#define KBD_CMD_SET_LEDS        0xED    /* Set keyboard leds */
#define KBD_CMD_ECHO            0xEE
#define KBD_CMD_GET_ID          0xF2    /* get keyboard ID */
#define KBD_CMD_SET_RATE        0xF3    /* Set typematic rate */
#define KBD_CMD_ENABLE          0xF4    /* Enable scanning */
#define KBD_CMD_RESET_DISABLE   0xF5    /* reset and disable scanning */
#define KBD_CMD_RESET_ENABLE    0xF6    /* reset and enable scanning */
#define KBD_CMD_RESET           0xFF    /* Reset */

/* Keyboard Replies */
#define KBD_REPLY_POR       0xAA    /* Power on reset */
#define KBD_REPLY_ACK       0xFA    /* Command ACK */
#define KBD_REPLY_RESEND    0xFE    /* Command NACK, send the cmd again */

/* Status Register Bits */
#define KBD_STAT_OBF        0x01    /* Keyboard output buffer full */
#define KBD_STAT_IBF        0x02    /* Keyboard input buffer full */
#define KBD_STAT_SELFTEST   0x04    /* Self test successful */
#define KBD_STAT_CMD        0x08    /* Last write was a command write (0=data) */
#define KBD_STAT_UNLOCKED   0x10    /* Zero if keyboard locked */
#define KBD_STAT_MOUSE_OBF  0x20    /* Mouse output buffer full */
#define KBD_STAT_GTO        0x40    /* General receive/xmit timeout */
#define KBD_STAT_PERR       0x80    /* Parity error */

/* Controller Mode Register Bits */
#define KBD_MODE_KBD_INT        0x01    /* Keyboard data generate IRQ1 */
#define KBD_MODE_MOUSE_INT      0x02    /* Mouse data generate IRQ12 */
#define KBD_MODE_SYS            0x04    /* The system flag (?) */
#define KBD_MODE_NO_KEYLOCK     0x08    /* The keylock doesn't affect the keyboard if set */
#define KBD_MODE_DISABLE_KBD    0x10    /* Disable keyboard interface */
#define KBD_MODE_DISABLE_MOUSE    0x20    /* Disable mouse interface */
#define KBD_MODE_KCC            0x40    /* Scan code conversion to PC format */
#define KBD_MODE_RFU            0x80

/* Mouse Commands */
#define AUX_SET_SCALE11 0xE6    /* Set 1:1 scaling */
#define AUX_SET_SCALE21 0xE7    /* Set 2:1 scaling */
#define AUX_SET_RES     0xE8    /* Set resolution */
#define AUX_GET_SCALE   0xE9    /* Get scaling factor */
#define AUX_SET_STREAM  0xEA    /* Set stream mode */
#define AUX_POLL        0xEB    /* Poll */
#define AUX_RESET_WRAP  0xEC    /* Reset wrap mode */
#define AUX_SET_WRAP    0xEE    /* Set wrap mode */
#define AUX_SET_REMOTE  0xF0    /* Set remote mode */
#define AUX_GET_TYPE    0xF2    /* Get type */
#define AUX_SET_SAMPLE  0xF3    /* Set sample rate */
#define AUX_ENABLE_DEV  0xF4    /* Enable aux device */
#define AUX_DISABLE_DEV 0xF5    /* Disable aux device */
#define AUX_SET_DEFAULT 0xF6
#define AUX_RESET        0xFF    /* Reset aux device */
#define AUX_ACK            0xFA    /* Command byte ACK. */

#define MOUSE_STATUS_REMOTE     0x40
#define MOUSE_STATUS_ENABLED    0x20
#define MOUSE_STATUS_SCALE21    0x10

#define KBD_QUEUE_SIZE 256

#define KBD_PENDING_KBD         1
#define KBD_PENDING_AUX         2

ppmLocalBusHandle configPortHandle;
ppmNetHandle      resetNetHandle;
ppmNetHandle      kbdIntNetHandle;
ppmNetHandle      mouseIntNetHandle;

Uns32             diagnosticLevel = 0;

static void addressError(void *add, Uns32 attempt, Uns32 actual) {
    bhmMessage("E", "PS2",
        "Attempting %u byte(s) access on a %u byte(s) register",
        attempt, actual
    );
}

typedef struct KBDState {
    Uns8 write_cmd; /* if non zero, write data to port 60 is expected */
    Uns8 status;
    Uns8 mode;
    /* Bitmask of devices with data available.  */
    Uns8 pending;

} KBDState, *KBDStateP;

//
// State of keyboard model.
//
static KBDState    kbd_state;


static void kbd_update_irq(KBDState *s)
{
    static Bool irq_kbd_level_last = False;
    static Bool irq_mouse_level_last = False;
    Bool irq_kbd_level = False;
    Bool irq_mouse_level = False;

    s->status &= ~(KBD_STAT_OBF | KBD_STAT_MOUSE_OBF);
    if(PSE_DIAG_HIGH)
        bhmMessage("I", "PS2", "kbd: update irq status=0x%x pending=%d", s->status, s->pending);

    if (s->pending) {
        s->status |= KBD_STAT_OBF;
        /* kbd data takes priority over aux data.  */
        if (s->pending == KBD_PENDING_AUX) {
            s->status |= KBD_STAT_MOUSE_OBF;
            if (s->mode & KBD_MODE_MOUSE_INT){
                irq_mouse_level = True;
            }
        } else {
            if ((s->mode & KBD_MODE_KBD_INT) && !(s->mode & KBD_MODE_DISABLE_KBD)){
                irq_kbd_level = True;
            }
        }
    }
    if(mouseIntNetHandle && (irq_mouse_level != irq_mouse_level_last)){
        irq_mouse_level_last = irq_mouse_level;
        if(PSE_DIAG_HIGH)
            bhmMessage("I", "PS2", "kbd: mouse int %sasserted", irq_mouse_level ? "" : "de-");
        ppmWriteNet(mouseIntNetHandle, irq_mouse_level);
    }
    if(kbdIntNetHandle && (irq_kbd_level != irq_kbd_level_last)){
        irq_kbd_level_last = irq_kbd_level;
        if(PSE_DIAG_HIGH)
            bhmMessage("I", "PS2", "kbd: kbd int %sasserted", irq_kbd_level ? "" : "de-");
        ppmWriteNet(kbdIntNetHandle, irq_kbd_level);
    }
}

static void kbd_update_kbd_irq(Bool level)
{
    KBDState *s = &kbd_state;

    if(PSE_DIAG_HIGH)
        bhmMessage("I", "PS2", "kbd: update kbd irq level=%d pending=%d\n", level, s->pending);

    if (level)
        s->pending |= KBD_PENDING_KBD;
    else
        s->pending &= ~KBD_PENDING_KBD;

    kbd_update_irq(s);
}

static void kbd_update_aux_irq(Bool level)
{
    KBDState *s = &kbd_state;

    if(PSE_DIAG_HIGH)
        bhmMessage("I", "PS2", "kbd: update aux irq level=%d pending=%d\n", level, s->pending);

    if (level)
        s->pending |= KBD_PENDING_AUX;
    else
        s->pending &= ~KBD_PENDING_AUX;

    kbd_update_irq(s);
}


static Uns32 kbd_read_status(void *user, Uns32 addr)
{
    KBDState *s = user;
    if(PSE_DIAG_HIGH)
        bhmMessage("I", "PS2", "kbd: read status=0x%02x\n", s->status);
    return s->status;
}


static void kbd_write_command(KBDState *s, Uns32 addr, Uns32 val)
{
    if (PSE_DIAG_HIGH)
        bhmMessage("I", "PS2", "kbd: write cmd=0x%02x\n", val);

    switch(val) {
        case KBD_CCMD_READ_MODE:
            ps2Queue(s->mode, 1);
            break;
        case KBD_CCMD_WRITE_MODE:
        case KBD_CCMD_WRITE_OBUF:
        case KBD_CCMD_WRITE_AUX_OBUF:
        case KBD_CCMD_WRITE_MOUSE:
        case KBD_CCMD_WRITE_OUTPORT:
            s->write_cmd = val;
            break;
        case KBD_CCMD_MOUSE_DISABLE:
            s->mode |= KBD_MODE_DISABLE_MOUSE;
            break;
        case KBD_CCMD_MOUSE_ENABLE:
            s->mode &= ~KBD_MODE_DISABLE_MOUSE;
            break;
        case KBD_CCMD_TEST_MOUSE:
            ps2Queue(0x00, 0);
            break;
        case KBD_CCMD_SELF_TEST:
            s->status |= KBD_STAT_SELFTEST;
            ps2Queue(0x55, 0);
            break;
        case KBD_CCMD_KBD_TEST:
            ps2Queue(0x00, 0);
            break;
        case KBD_CCMD_KBD_DISABLE:
            s->mode |= KBD_MODE_DISABLE_KBD;
            kbd_update_irq(s);
            break;
        case KBD_CCMD_KBD_ENABLE:
            s->mode &= ~KBD_MODE_DISABLE_KBD;
            kbd_update_irq(s);
            break;
        case KBD_CCMD_READ_INPORT:
            ps2Queue(0x00, 0);
            break;
        case KBD_CCMD_READ_OUTPORT:
            /* XXX: check that */
    #ifdef TARGET_I386
            val = 0x01 | (ioport_get_a20() << 1);
    #else
            val = 0x01;
    #endif
            if (s->status & KBD_STAT_OBF)
                val |= 0x10;
            if (s->status & KBD_STAT_MOUSE_OBF)
                val |= 0x20;
            ps2Queue(val, 0);
            break;
    #ifdef TARGET_I386
        case KBD_CCMD_ENABLE_A20:
            ioport_set_a20(1);
            break;
        case KBD_CCMD_DISABLE_A20:
            ioport_set_a20(0);
            break;
    #endif
        case KBD_CCMD_RESET:
            //qemu_system_reset_request();
            break;
        case 0xff:
            /* ignore that - I don't know what is its use */
            break;
        default:
            bhmMessage("W", "PS2", "Unsupported keyboard cmd=0x%02x\n", val);
            break;
    }
}

static Uns32 kbd_read_data(KBDState *s, Uns32 addr)
{
    Uns32 val;

    if (s->pending == KBD_PENDING_AUX) {
        val = ps2ReadByte(1);

        if(PSE_DIAG_HIGH)
            bhmMessage("I", "PS2", "kbd: (aux) read data=0x%02x [pending %d]\n", val, s->pending);
        return val;
    }

    val = ps2ReadByte(0);

    if(PSE_DIAG_HIGH)
        bhmMessage("I", "PS2", "kbd: read data=0x%02x [pending %d]\n", val, s->pending);

    return val;
}

static void kbd_write_data(KBDState *s, Uns32 addr, Uns32 val)
{
    if (PSE_DIAG_HIGH)
        bhmMessage("I", "PS2", "kbd: write data=0x%02x (write cmd 0x%x)\n", val, s->write_cmd);

    switch(s->write_cmd) {
    case 0:
        ps2WriteByte(val, 0);
        break;
    case KBD_CCMD_WRITE_MODE:
        s->mode = val;
        kbd_update_irq(s);
        break;
    case KBD_CCMD_WRITE_OBUF:
        ps2Queue(val, 0);
        break;
    case KBD_CCMD_WRITE_AUX_OBUF:
        ps2Queue(val, 1);
        break;
    case KBD_CCMD_WRITE_OUTPORT:
        bhmMessage("W", "PS2", "Unsupported write outport data=0x%02x\n", val);
        break;
    case KBD_CCMD_WRITE_MOUSE:
        ps2WriteByte(val, 1);
        break;
    default:
        break;
    }
    s->write_cmd = 0;
}

static void hardwareReset(ppmNetValue v, void *nu)
{
    KBDStateP s  = &kbd_state;
    s->mode      = KBD_MODE_KBD_INT | KBD_MODE_MOUSE_INT;
    s->status    = KBD_STAT_CMD | KBD_STAT_UNLOCKED;
    s->pending   = 0;
    s->write_cmd = 0;

    if(PSE_DIAG_HIGH)
        bhmMessage("I", "PS2", "Hardware reset: status=0x%x\n", s->status);
}

static unsigned char config_Window  [0x8];

static PPM_READ_CB(configReadPort){
    if(bytes != 1) {
        addressError(addr, bytes, 1);
        return 0;
    }

    Uns32 data;
    Uns32 off = (unsigned char*)addr - &config_Window[0x0];

    switch (off){
        case 0:
            data = kbd_read_data(user, off);
        break;

        case 4:
            data = kbd_read_status(user, off);
        break;

        default:
            if(PSE_DIAG_HIGH)
                bhmMessage("W", "PS2", "Config Port Read Unrecognised off=0x%02x\n", off);
            return -1;
    }

    return data;
}

static PPM_WRITE_CB(configWritePort){
    if(bytes != 1) {
        addressError(addr, bytes, 1);
        return ;
    }

    Uns32 off  = (unsigned char*)addr - &config_Window[0x0];

    switch (off){
        case 0:
            kbd_write_data(user, off, data);
        break;

        case 4:
            kbd_write_command(user, off, data);
        break;

        default:
            if(PSE_DIAG_HIGH)
                bhmMessage("W", "PS2", "Config Port Write Unrecognised off=0x%02x\n", off);
    }
}

static void busPortConnections(void) {
    configPortHandle = ppmOpenSlaveBusPort(
        "config",
        config_Window,
        sizeof(config_Window)
    );
    ppmInstallReadCallback(
        configReadPort,
        &kbd_state,
        &config_Window[0x0],
        sizeof(config_Window)
    );
    ppmInstallWriteCallback(
        configWritePort,
        &kbd_state,
        &config_Window[0x0],
        sizeof(config_Window)
    );
}

static void netPortConnections(void)
{
    resetNetHandle = ppmOpenNetPort("reset");
    if(resetNetHandle) {
        ppmInstallNetCallback(resetNetHandle, hardwareReset, NULL);
    }
    kbdIntNetHandle   = ppmOpenNetPort("kbdInterrupt");
    mouseIntNetHandle = ppmOpenNetPort("mouseInterrupt");
}

static Uns32 polls;
static Uns32 pollPeriod;

static Bool disableInput;
static Bool grabDisable;
static Bool cursorEnable;

//
// This thread polls for input
//
static void ps2PollTask()
{
    while(1) {
    	// wait for poll period
        bhmWaitDelay(pollPeriod);
        // perform poll of input
        ps2Poll(disableInput);
        polls++;
    }
}


//
// Entry point to PSE model
//
PPM_CONSTRUCTOR_CB(constructor) {

    periphConstructor();

    bhmUns32ParamValue("pollPeriod",   &pollPeriod);
    if(pollPeriod == 0) {
        bhmMessage("E", "PS2", "pollPeriod must be non-zero");
    }

    // always fetch these attributes, even if not required in replay mode.
    bhmBoolParamValue("disableInput", &disableInput);
    bhmBoolParamValue("grabDisable", &grabDisable);
    bhmBoolParamValue("cursorEnable", &cursorEnable);

    bhmBoolParamValue("isMouse", &isMouse);
    bhmBoolParamValue("isKeyboard", &isKeyboard);
    kbMouse = (!isKeyboard & !isMouse) ? 0 : (isMouse ? 1 : 2);


    if (disableInput) {
        bhmMessage("W", "PS2", "Ignoring real mouse and keyboard input.");
    }
    ps2Init(grabDisable, cursorEnable, kbd_update_kbd_irq, kbd_update_aux_irq);

    hardwareReset(0, NULL);
    busPortConnections();
    netPortConnections();

    // start polling thread
    bhmCreateThread(ps2PollTask, NULL, "ps2PollTask", 0);

}


PPM_DESTRUCTOR_CB(destructor) {
    if(PSE_DIAG_LOW) {
        bhmMessage("I", "PS2", "Polls: %d", polls);
    }
    ps2Finish();
}

PPM_SAVE_STATE_FN(peripheralSaveState) {
}

PPM_RESTORE_STATE_FN(peripheralRestoreState) {
}
