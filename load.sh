#!/bin/bash

SYS_MAP=`ls /boot/System.map-*-generic`
SYS_CALL_ADDR=0x`cat $SYS_MAP | grep sys_call_table | cut -f1 -d' '`
MP3='/home/husseincoder/Desktop/hijack-linux-sys-calls/mp3/amr.mp3'

if [ 'X$SYS_CALL_ADDR' == 'X' ]
then
	echo "Can't find the system call table address."
	exit 1
fi

echo 'System call table address = $SYS_CALL_ADDR'

echo 'Building..'
make &> /dev/null

echo 'Loading..'
insmod hijack-syscall.ko syscall_table=$SYS_CALL_ADDR my_path=$MP3

if [ $? -eq 0 ]
then
	echo "Module loaded."
fi
