# Philips USB Model

## Model Source Code
The source code for the USB model is not currently available in the general release.
If you feel that you require the source code for this model, this may be
  1) To use as a basis for a new model
  2) To debug a problem
Please contact Imperas info@imperas.com 

## Specifications

## Supported Backends
The model aims to provide tunneling between USB SW on the target machine and USB devices on the host machine, so that
SW working with the real driver for Linux, can work unmodified on the virtual target machine,
and access real USB devices on the host.  Currently this is achieved by using a libusb backend.


## Limitations
- Only host mode is supported.
- DMA modes are not supported for the moment, only the mandatory slave mode is implemented.
- Control and bulk transfer types are currently implemented.  No interrupt and isochronous transfers yet.
- Tested only the attachment of a single host device.  The HSOTG controller's root hub has a single port, so only one
  device can be attached to it.  This device could be a hub, though.  Currently we support only one non-hub device.
- Hot plug events are currently unsupported.

The first four steps to use a USB host device from the target differ based on
the host operating system.  The last two steps are the same regardless of the host.

###############################################################################
## Accessing Host Devices on Linux
 1. The device has to be attached to the host before starting simulation.  To check that it was successfully
    attached to a Linux host, and to see some parameters, do:
      host> lsusb                                                               # find bus, dev, vid, pid
      host> lsusb -v -d <vid>:<pid>                                             # find port, check device is BOMS (e.g. bInterfaceClass/SubClass/Protocol = 8/6/80)

 2. Stop using the device from host, e.g.
      host> umount /dev/sdb1                                                    # release device resources

 3. Give regular users access rights to the corresponding device file (actual path may differ), e.g.
      host> chmod a+w /dev/bus/usb/<bus>/<dev>

 4. Manually unbind the auto-bound USB protocol drivers.  This step is optional.  The model is doing this automatically
    if the host OS supports it.  On Linux try:
      host> tree /sys/bus/usb/devices/<bus>-<port>                              # see what protocol drivers are bound to device (e.g. usb-storage)
      host> tree /sys/bus/usb/drivers/usb-storage                               # see what is bound to usb-storage (e.g. 1-3:1.0)
      host> echo -n "1-3:1.0" > /sys/bus/usb/drivers/usb-storage/unbind         # unbind 1-3:1.0 from usb-storage

###############################################################################
## Accessing Host Devices on Windows
 1. Plug in the device and then eject it to safely disconnect so a USB driver supported
    by libusb can be installed. 

 2.    Per www.libusb.org/wiki/windows_backend, to access your USB devices with the Windows
    backend you need to install the relevant driver.  Two  options are available:
      + The easiest is to use the most recent version of the Automated Driver Installaller GUI
        application Zadig.exe, which is part of libwdi, the Windows Driver Installer library.

        The current version, which is compatible with both 32 and 64 bit Windows platforms starting
        with Windows XP, can install a WinUSB driver for any USB device.  The installer needs to
        run with administrative privileges, so you are strongly encouraged to use a version that has
        been digitally signed, such as any official version from v2.0.0.151.  You can also recompile
        your own version from the source.  Zadig also allows the selection and installation of the 
        latest libusb-win32 and libusbK drivers.
      + Or you can download the WinUSB driver files, then customize the .inf for your device and
        install the driver by following the instructions that are in the README file that comes with
        the driver archive.

 3. To use the Zadig utility, download it from zadig.akeo.ie and run it with an account having
    Administrator priviledges - no installation is needed.  Follow these steps:
      + When the "User Account Control" dialog appears, indicate "Yes" to allow it to
        make changes to your computer.
      + Execute "Options - List All Devices".  The USB devices on the computer are now listed
        in the drop-down list button.  Choose the device to be accessed from the virtual platform.
      + Record the vendor id and group id that appear in the "USB ID" fields.
      + To the right of the "Driver" lable, replace "USBSTOR" with either "WinUSB" or "libusbK",
        and then push the "Replace Driver" button.
      + Indicate "Yes" in the "Warning - System Driver" dialog to confirm that you want to
        modify a system driver.
      + If prompted to restart the system, do so.


4. After making the driver change it will no longer appear in the "Device Manager" under "Portable Devices".
   If you chose "WinUSB", it will appear under "Universal Serial Bus devices".  If you chose "libusbK",
   it will appear under "libusbK USB Devices".  In either case, you can confirm you are looking at the
   correct device by hovering over the device, executing "Properties" from the right-mouse button menu,
   choosing "Details", and then selecting "Hardware Ids".

   If later you want to use the device from Windows again, hover over the device and execute "Uninstall".
   In the "Confirm Device Uninstall" dialog, check "Delete the driver software for this device" and then
   push "OK".  The "USBSTOR" driver will be automatically installed by unplugging the device and then plugging
   it back in.


###############################################################################
## Common Steps for Accessing Host Devices
 5. Find out the USB instances that will be used by target kernel.  For example, if the 
    platform has two instances of the USB model: iUSB0 and iUSB1.  The default configuration
    in vanilla Linux kernels enables only the second instance, iUSB1.

 6. Start simulation, specifying the desired host USB device for each USB instance, e.g.
      host> platform.exe --override platform/iUSB1/usbDevice=host:<VID>:<PID>
    When specifying VID and PID, make sure to use the right prefix (0x - hex, 0 - oct).  Current lsusb
    prints them as hexadecimal numbers without prefix.


## Example Uses

### Disconnected
```
  host> platform.<ARCH>.exe                                                     # start simulation (no device specified)
  target>       # observe that controller was initialized, an USB bus registered, no devices connected
```

### Bulk Only Mass Storage (BOMS) Device Attached
- The example assumes using a BOMS device and a Linux target.

# Linux host steps
  host>                                                                         # attach device to host
  host> lsusb                                                                   # find bus, port, dev, vid, pid (e.g. 1, 3, 7, 0951:1603)
  host> chmod a+w /dev/bus/usb/001/007                                          # allow regular users to access the device
  host> umount /dev/sdb1                                                        # stop using the device from host (optional)
  host> echo -n "1-3:1.0" > /sys/bus/usb/drivers/usb-storage/unbind             # detach host protocol drivers from device's interfaces (optionsl)

# Windows host steps
  host> # eject or otherwise prepare device for save removal (but do not unplug)
  host> # use zadig to install either the winUSB or libusbK driver for the device (restart if needed)


# Common steps on host and Linux target
  host> platform.<ARCH>.exe --override platform/iUSB1/usbDevice=host:0x0951:0x1603     # start simulation, host device 0951:1603
  target>       # observe that controller was initialized, an USB bus registered, a mass storage device discovered and initialized
  target> cat /proc/partitions                                                  # find device's partitions (say sda1)
  target> mkdir /mnt                                                            # create a mount point
  target> mount /dev/sda1 /mnt                                                  # mount FS from first partiotion
  target> ls /mnt                                                               # use the drive
  target> umount /mnt                                                           # release the FS
```

