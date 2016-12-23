# Environment
- Target machine
  + [Raspberry PI 3](https://www.raspberrypi.org/products/raspberry-pi-3-model-b/)
  + OS: Raspbian (Debian 8 Jessie) Lite without PIXEL
- Development machine
  + [Lenovo Thinkpad X220](https://support.lenovo.com/vn/en/documents/pd015812)
  + OS: x86_64 Linux 4.8.3-1-ARCH
  + Language: C/C++

# Oct 27
- Manually build driver, add module for 4.8.3.1-ARCH x64
  + Run install script as root
  + Extract corresponding files in `/opt/DigitalPersone/UareUSDK/redist` and point `$LD_LIBRARY_PATH` to the extracted directory
  + Maybe need to update `linux-headers`
  + Make kernel module in `/opt/DigitalPersona/drivers/source/usbdpfp` and copy the `.ko` file to `/lib/modules/4.8.3.1-ARCH/kernel/drivers/biomectric`
  + Copy `/opt/DigitalPersona/redist/40-usbdpfp.rules` to `/etc/udev/rules.d`
  + `/sbin/depmod`
  + `su -c "insmod ./mod_usbdpfp.ko`, verify with `lsmod | grep mod_usbdpfp`

- Build and run some samples at `/opt/DigitalPersona/UareUSDK/Linux/Samples/*`
  + UareUCaptureOnly: worked
  + UareUSample: worked

- Build driver for 4.4.21-v7+ Raspberry Pi3 (armv7l)
  + Update headers: download deb file and install it normally from [this source](https://www.niksula.hut.fi/~mhiienka/Rpi/linux-headers-rpi/)
  + Run install script as root, it will build driver module for Pi3
  + Install `fprint` library (include fprintd_demo)
  + Using [USBdetach](https://github.com/Lefinnois/USBdetach) to detach UareU 4500 from kernel, in order to use without DP SDK

