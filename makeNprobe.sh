#!/bin/bash
cd /home/pi/DeviceDriver/
rmmod batata_driver.ko
make clean
make all
insmod /home/pi/DeviceDriver/batata_driver.ko
lsmod
dmesg
