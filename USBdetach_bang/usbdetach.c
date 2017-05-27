/*
Copyright (c) 2012, Denis Bodor
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met: 

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer. 
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/errno.h>
#include <getopt.h>
#include <regex.h>
#include <sys/stat.h>
#include <libudev.h>
#include <libusb.h>

#define OPT "rshfVvd:i:p:n:"
#define DAREGEX "^[0-9a-fA-F]{4}:[0-9a-fA-F]{4}$"

int verbose;

int chkusbid(const char *string) {
  regex_t re;

  if(regcomp(&re, DAREGEX, REG_EXTENDED|REG_NOSUB) != 0) {
    printf("regex compilation error\n");
    exit(EXIT_FAILURE);
  }

  if(regexec(&re, string, (size_t)0, NULL, 0) != 0) {
    regfree(&re);
    return(1);
  }

  regfree(&re);
  return(0);
}

void giveup(libusb_device_handle *devh, libusb_context *ctx) {
  libusb_close(devh);
  libusb_exit(ctx);
  fprintf(stderr,"Fatal error. Giving up ! Sorry.\n");
  exit(EXIT_FAILURE);
}

unsigned int udevstufftoint(const char *udevstring, int base) {
  char *endp;
  int ret;
  errno = 0;

  if(udevstring == NULL)
    return(-1);

  ret = (unsigned int)strtol(udevstring, &endp, base);
  if(errno) {
    fprintf(stderr,"udevstufftoint: Unable to parse number Error : %s (%d)\n",
        strerror(errno),errno);
    return(-2);
  }
  if (endp == optarg) {
    fprintf(stderr, "udevstufftoint: No digits were found\n");
    return(-3);
  }
  return(ret);
}

void badarg() {
  fprintf(stderr,"Bad syntaxe for USB ID. Please use -d idVendor:idProduct\n");
  exit(EXIT_FAILURE);
}

int printdesc (struct libusb_device_handle *handle, uint8_t idx) {
  unsigned char buffer[256];
  int ret = 0;

  // desc asked exist ?
  if(!idx) {
    printf("<none>\n");
    return(1);
  }

  if ((ret = libusb_get_string_descriptor_ascii(handle, idx, buffer, sizeof(buffer))) <= 0)
    return(1);

  if(ret > 1)
    printf("'%s'\n", buffer);

  return(0);
}

void printinfo() {
  printf("USBdetach v0.1\nCopyright (c) 2012 Denis Bodor <lefinnois@gmail.com>\nThis is free software: you are free to change and redistribute it.\nThere is NO WARRANTY, to the extent permitted by law.\n");
  printf("Syntaxe :\n");
  printf(" -h -V                     you read this right now\n");
  printf(" -d <idVendor:idProduct>   USB Vendor:Product ID to detach from kernel support as reported by lsusb\n");
  printf(" -i <interface number>     interface to detach from kernel support\n");
  printf(" -n <devnum>               device number\n");
  printf(" -f                        force if interface number or device number is missing\n");
  printf(" -p <file>                 full path to dev node of the device to detach (this cannot be used with -d, -i or -n)\n");
  printf(" -v                        be verbose\n");
  printf(" -s                        simulate (don't detach and claim)\n");
}

int main(int argc, char **argv) {
  int optch;

  char *endptr;

  int donothing = 0;
  int force = 0;
  int reattach = 0;

  libusb_context *ctx = NULL;

  struct libusb_device_handle *devhaccess;

  struct libusb_device **list;
  struct libusb_device *found = NULL;
  struct libusb_device_descriptor fdesc;

  ssize_t cnt;
  ssize_t i = 0;

  struct st_device {
    int vid;
    int pid;
    int iface;
    int devnum;
    int complete;
  } targetdevice = { 0, 0, 0, 0, 0 };

  char *filename = NULL;
  struct stat statinfo;
  char devtype;

  struct udev *udev;
  struct udev_device *dev, *usbifaceparent, *usbdeviceparent;

  while ((optch = getopt(argc, argv, OPT)) != -1) {
    switch (optch) {
      case 'r':
        reattach=1;
        break;
      case 's':
        donothing=1;
        break;
      case 'f':
        force = 1;
        break;
      case 'v':
        verbose = 1;
        break;
      case 'h':
      case 'V':
        printinfo();
        exit(EXIT_SUCCESS);
        break;
      case 'i':
        errno = 0;
         targetdevice.iface = (unsigned int)strtol(optarg, &endptr, 10);
         if(errno) {
           fprintf(stderr,"Unable to parse interface number Error : %s (%d)\n",
               strerror(errno),errno);
           exit(EXIT_FAILURE);
         }
         if (endptr == optarg) {
           fprintf(stderr, "No digits were found\n");
           exit(EXIT_FAILURE);
         }
         targetdevice.complete |= 4;
         break;
      case 'n':
        errno = 0;
         targetdevice.devnum = (unsigned int)strtol(optarg, &endptr, 10);
         if(errno) {
           fprintf(stderr,"Unable to parse device number Error : %s (%d)\n",
               strerror(errno),errno);
           exit(EXIT_FAILURE);
         }
         if (endptr == optarg) {
           fprintf(stderr, "No digits were found\n");
           exit(EXIT_FAILURE);
         }
         targetdevice.complete |= 8;
         break;
      case 'd':
        if(chkusbid(optarg)) badarg();
        targetdevice.pid = (unsigned int)strtol(optarg+5, NULL, 16);
        targetdevice.complete |= 2;
        targetdevice.vid = (unsigned int)strtol(optarg, NULL, 16);
        if(targetdevice.vid !=0) targetdevice.complete |= 1;
        break;
      case 'p':
        filename=optarg;
        break;
      default:
        fprintf(stderr,"Unknow option\n");
        exit(EXIT_FAILURE);
    }
  }

  if(optind <= 1 || optind < argc) {
    printinfo();
    exit(EXIT_FAILURE);
  }

  /* cannot work with vid/pid and /dev path at the same time (targetdevice partialy filled) */
  if(filename && targetdevice.complete) {
    fprintf(stderr, "You cannot use both -p and -d, -i or -n. Use a /dev file OR idVendor:idProduct/interface/devnum.\n");
    exit(EXIT_FAILURE);
  }

  /*** BEGIN OF UDEV STUFF ***/

  /* got path, fill targetdevice from that with udev */
  if(filename) {
    if (stat(filename, &statinfo) < 0) {
      fprintf(stderr, "Unable to stat file\n");
      exit(EXIT_FAILURE);
    }

    /* get device type */
    switch (statinfo.st_mode & S_IFMT) {
      case S_IFBLK:
        devtype='b';
        break;
      case S_IFCHR:
        devtype='c';
        break;
      default:
        printf("not char or block device\n");
        exit(EXIT_FAILURE);
    } 

    if(verbose) {
      printf("Using %s (UID=%ld GID=%ld perm=%lo)  %d:%d\n",
          filename, (long)statinfo.st_uid, (long)statinfo.st_gid,
          (unsigned long)statinfo.st_mode,
          major(statinfo.st_rdev), minor(statinfo.st_rdev));
    }

    /* Create the udev object */
    udev = udev_new();
    if (!udev) {
      printf("Can't create udev\n");
      exit(EXIT_FAILURE);
    }

    dev = udev_device_new_from_devnum(udev, devtype, statinfo.st_rdev);

    if (dev == NULL) {
      printf("no dev\n");
      udev_unref(udev);
      exit(EXIT_FAILURE);
    }

    if(verbose) {
      printf("Device node: '%s'\n", udev_device_get_devnode(dev));
    }

    /* Get closest usb interface parent (active interface for this device and /dev node) */
    usbifaceparent = udev_device_get_parent_with_subsystem_devtype(dev, "usb", NULL);
    if(!usbifaceparent) {
      printf("Unable to find parent usb interface! Is this actually an USB device ?\n");
      udev_device_unref(dev);
      udev_unref(udev);
      exit(EXIT_FAILURE);
    }

    /* fill targetdevice struct : interface */
    if((targetdevice.iface = udevstufftoint(udev_device_get_sysattr_value(usbifaceparent,"bInterfaceNumber"),10)) >= 0)
      targetdevice.complete |= 4;

    /* Get closest usb device parent (we need VIP/PID)  */
    usbdeviceparent = udev_device_get_parent_with_subsystem_devtype(dev, "usb", "usb_device");
    if(!usbdeviceparent) {
      printf("Unable to find parent usb device! Is this actually an USB device ?\n");
      udev_device_unref(dev);
      udev_unref(udev);
      exit(EXIT_FAILURE);
    }

    /* fill targetdevice struct : vid, pid and devnum */
    if((targetdevice.vid = udevstufftoint(udev_device_get_sysattr_value(usbdeviceparent,"idVendor"),16)) >= 0)
      targetdevice.complete |= 1;
    if((targetdevice.pid = udevstufftoint(udev_device_get_sysattr_value(usbdeviceparent,"idProduct"),16)) >= 0)
      targetdevice.complete |= 2;
    if((targetdevice.devnum = udevstufftoint(udev_device_get_sysattr_value(usbdeviceparent,"devnum"),10)) >= 0)
      targetdevice.complete |= 8;

    /* We're done. Giveup with udev */
    udev_device_unref(dev);
    udev_unref(udev);
  }

  /*** END OF UDEV STUFF ***/

  /* check what we have from getopt or udev */
  if(targetdevice.complete != 15) {
    fprintf(stderr,"Warning ! Device identification incomplete (%u):\n", targetdevice.complete);
    if(~targetdevice.complete & 1) fprintf(stderr,"  idVendor is missing (fatal)\n");
    if(~targetdevice.complete & 2) fprintf(stderr,"  idProduct is missing (fatal)\n");
    if(~targetdevice.complete & 4) fprintf(stderr,"  Interface is missing (default to 0 with -f)\n");
    if(~targetdevice.complete & 8) fprintf(stderr,"  Device number is missing (process without with -f)\n");
    if((targetdevice.complete & 3) != 3) {
      fprintf(stderr,"Not going further. Not enought information to complet\n");
      exit(EXIT_FAILURE);
    }
    if(!force) {
      fprintf(stderr,"Not going further. Not enought information to complet (too risky)\n");
      exit(EXIT_FAILURE);
    }
    fprintf(stderr,"but you ask me to proceed anynway (-f). I may detach a wrong device.\n");
    targetdevice.complete |= 4;
  } else {
    if(verbose)
      printf("USB device fully identified\n");
  }

  if(verbose) {
    printf("Let's try to find device %04x:%04x, interface %u, ", targetdevice.vid, targetdevice.pid, targetdevice.iface);
    if(targetdevice.complete & 8) {
      printf("device number %u\n", targetdevice.devnum);
    } else {
      printf("without device number\n");
    }
  }

  /* init */
  if(libusb_init(&ctx) != 0) {
    fprintf(stderr,"Can't init libUSB\n");
    fprintf(stderr,"libusb_init Error : %s (%d)\n",
        strerror(errno),errno);
    exit(EXIT_FAILURE);
  }

  libusb_set_debug(ctx, 3);

  // get all connected usb devices
  if((cnt = libusb_get_device_list(ctx, &list)) < 0) {
    fprintf(stderr,"Can't get devices list\n");
    fprintf(stderr,"libusb_get_device_list  Error : %s (%d)\n",
        strerror(errno),errno);
    libusb_exit(ctx);
    exit(EXIT_FAILURE);
  }

  // parse the list
  for (i = 0; i < cnt; i++) {
    struct libusb_device_descriptor desc;
    struct libusb_config_descriptor *config; 
    int nbrinterf=0;
    struct libusb_device *device = list[i];

    /* get device description */
    if (libusb_get_device_descriptor(device,&desc) != 0) {
      fprintf(stderr,"libusb_get_device_descriptor Error : %s (%d)\n",
          strerror(errno),errno);
      continue;
    }

    if(desc.idVendor == targetdevice.vid) {
      // got vid
      if(desc.idProduct == targetdevice.pid) {
        // got pid
        // nedd config description to check interface number
        if (libusb_get_active_config_descriptor(device, &config) != 0) {
          fprintf(stderr,"libusb_get_device_descriptor Error : %s (%d)\n",
              strerror(errno),errno);
          continue;
        }
        nbrinterf = config->bNumInterfaces;
        if(nbrinterf < 1) {
          fprintf(stderr, "Less than 1 interface. Too weird !\n");
          continue;
        }
        if(nbrinterf > targetdevice.iface) { 
          // got interface
          // need to check devnum ?
          if(targetdevice.complete & 8) {
            if(libusb_get_device_address(device) == targetdevice.devnum) {
              // got devnum
              if(verbose) printf("Complete Matching device found\n");
              found = device;
              memcpy (&fdesc, &desc, sizeof(fdesc));
              break;
            }
          } else {
            // devnum check not needed, we're ok with vid, pid and iface
            if(verbose) printf("Matching device found (without devnum)\n");
            found = device;
            memcpy (&fdesc, &desc, sizeof(fdesc));
            break;
          }
        }
      }
    }
  }

  // ok, we found the device
  if (found) {
    // get handle
    if(libusb_open(found, &devhaccess) != 0) {
      fprintf(stderr,"Unable to get handler on device\n");
      fprintf(stderr,"libusb_get_device_descriptor Error : %s (%d)\n",
          strerror(errno),errno);
      libusb_free_device_list(list, 1);
      libusb_exit(ctx);
      exit(EXIT_FAILURE);
    }

    if(verbose) {
      printf("  %04x:%04x\n", fdesc.idVendor, fdesc.idProduct);
      printf("  iManufacturer: ");
      printdesc(devhaccess, fdesc.iManufacturer);
      printf("  iProduct: ");
      printdesc(devhaccess, fdesc.iProduct);
      printf("  iSerialNumber: ");
      printdesc(devhaccess, fdesc.iSerialNumber);
      printf("  on bus number %u with address %u\n", libusb_get_bus_number(found), libusb_get_device_address(found));
    }

    // are we acting for real ?
    if(!donothing) {
      if(libusb_kernel_driver_active(devhaccess, targetdevice.iface) == 1) {
        if(verbose)
          printf("kernel driver (or something) is active on interface %u... trying to detach\n", targetdevice.iface);
        if(libusb_detach_kernel_driver(devhaccess, targetdevice.iface)) {
          fprintf(stderr,"Unable to detach kernel driver from interface %u.\n", targetdevice.iface);
          giveup(devhaccess,ctx);
        }
        if(verbose)
          printf("Kernel driver detached.\n");
      } else {
        if(verbose)
          printf("No kernel attached. Nothing to do. Claiming device for checking.\n");
      }

      // just checking
      if(verbose) printf("Check with claiming interface %u\n",targetdevice.iface);
      if(libusb_claim_interface(devhaccess, targetdevice.iface) != 0) {
        fprintf(stderr,"libusb_claim_interface  Error : %s (%d)\n",
            strerror(errno),errno);
        giveup(devhaccess,ctx);
      }

      if(verbose) printf("All interface %d are belong to me\n", targetdevice.iface);

      if(verbose) printf("Release interface %u...\n",targetdevice.iface);
      if(libusb_release_interface(devhaccess,targetdevice.iface) !=0)
        fprintf(stderr,"libusb_release_interface  Error : %s (%d)\n",
            strerror(errno),errno);

      if(reattach) {
        printf("Device detached. Press Enter to continue and reattach the device...\n");
        getchar();
        if(libusb_attach_kernel_driver(devhaccess, targetdevice.iface)) {
          fprintf(stderr,"Unable to attach kernel driver to interface %u.\n", targetdevice.iface);
        }
        // just checking
        if(verbose) printf("Check with claiming interface %u\n",targetdevice.iface);
        if(libusb_claim_interface(devhaccess, targetdevice.iface) != 0) {
          if(verbose) printf("Cannot claim device with interface %d. That's ok.\n", targetdevice.iface);
        }
      }
    }

    if(verbose) printf("Closing device...\n");
    libusb_close(devhaccess);
  } else {
    fprintf(stderr,"Device not found\n");
  }

  /* For convenience, the libusb_free_device_list() function includes 
   * a parameter to optionally unreference all the devices in the 
   * list before freeing the list itself */
  if(verbose)
    printf("Freeing devices list\n");
  libusb_free_device_list(list, 1);

  if(verbose)
    printf("LibUSB exit...\n");
  libusb_exit(ctx);

  return(EXIT_SUCCESS);
}


