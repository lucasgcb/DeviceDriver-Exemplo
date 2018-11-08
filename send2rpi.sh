#!/bin/bash

if [ "$#" -ne 1 ]
then
	scp batata_driver.c pi@172.16.158.68:~/DeviceDriver/
	ssh root@172.16.158.68 '/home/pi/DeviceDriver/makeNprobe.sh'
else
	scp $1 pi@172.16.158.68:~/DeviceDriver/
fi
