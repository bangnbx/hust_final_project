# OS
- Install Raspbian (Debian 8 Jessie) Lite without PIXEL
- Install awesome WM

# Oct 27
- Manually build driver, add module for 4.8.3.1-ARCH x64
  + Run install script as root
  + Extract corresponding files in `/opt/DigitalPersone/UareUSDK/redist` and point `$LD_LIBRARY_PATH` to the extracted directory
  + Maybe need to update `linux-headers`
  + Make kernel module in `/opt/DigitalPersona/drivers/souce/usbdpfp` and copy the `.ko` file to `/lib/modules/4.8.3.1-ARCH/kernel/drivers/biomectric`
  + Copy `/opt/DigitalPersona/redist/40-usbdpfp.rules` to `/etc/udev/rules.d`
  + `/sbin/depmod`
  + `su -c "insmod ./mod_usbdpfp.ko`, verify with `lsmod | grep mod_usbdpfp`

