#!/bin/bash
cd /home/pi/DeviceDriverLab2/
rmmod batata_driver.ko
rmmod industrialio
make clean
make all
modprobe industrialio
insmod /home/pi/DeviceDriverLab2/batata_driver.ko
lsmod
dmesg | tail -n 20
