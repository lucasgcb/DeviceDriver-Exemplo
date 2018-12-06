#!/bin/bash

if [ -z "$I2C_ATIVADO" ]
then
	echo "Probing I2C modules"
	modprobe i2c-bcm2708
	modprobe i2c-dev
	lsmod | grep i2c
	i2cdetect -y 1
	export I2C_ATIVADO=1
fi


cd /home/pi/DeviceDriverLab2/
rmmod batata_driver.ko
rmmod industrialio
make clean
make all
modprobe industrialio
insmod /home/pi/DeviceDriverLab2/batata_driver.ko
dmesg | tail -n 30
