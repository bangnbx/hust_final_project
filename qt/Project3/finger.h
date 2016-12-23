#ifndef FINGER_H
#define FINGER_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libfprint/fprint.h>

struct fp_dscv_dev *discover_device(struct fp_dscv_dev **discovered_devs);
struct fp_print_data *enroll(struct fp_dev *dev);

#endif // FINGER_H
