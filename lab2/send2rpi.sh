#!/bin/bash

#ip_Do_Rpi= 172.16.158.68 //lab 2
ip_Do_Rpi="192.168.0.24" #casa

if [ "$#" -ne 1 ]
then
	scp batata_driver.c pi@$ip_Do_Rpi:~/DeviceDriverLab2/
	ssh root@$ip_Do_Rpi  '/home/pi/DeviceDriverLab2/makeNprobe.sh'
else
	scp $1 pi@192.168.0.24:~/DeviceDriverLab2/
fi
