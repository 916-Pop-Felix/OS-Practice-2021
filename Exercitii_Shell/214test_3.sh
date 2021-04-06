#!/usr/bin/bash

N=$1
if [ ! -f cuvinte.txt ];then
	touch cuvinte.txt
fi
while true; do
	read X
	if [ $X = "stop" ]; then
		exit
	fi
	if [ ${#X} -ge $N ]; then
		echo $X >> cuvinte.txt
	fi
done
