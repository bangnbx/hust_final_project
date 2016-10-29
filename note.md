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
  + Make kernel module in `/opt/DigitalPersona/drivers/souce/usbdpfp` and copy the `.ko` file to `/lib/modules/4.8.3.1-ARCH/kernel/drivers/biomectric`
  + Copy `/opt/DigitalPersona/redist/40-usbdpfp.rules` to `/etc/udev/rules.d`
  + `/sbin/depmod`
  + `su -c "insmod ./mod_usbdpfp.ko`, verify with `lsmod | grep mod_usbdpfp`

- Build and run some sample at `/opt/DigitalPersona/UareUSDK/Linux/Samples/*`
  + UareUCaptureOnly: worked
  + UareUSample: worked

