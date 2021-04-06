#!/usr/bin/bash

#2. Write a shell script that it will iterate over the homedirectories of the users existing in 
# the system and it will display on the screen for each one of them,
# their username and the sum of the file sizes found in it (files needs to be searched recursively).

cd /home

for  F1 in `ls`;do
	sum=0
	for F in `find $1`;do
	if [ -f $F ]; then
		size=$(ls $F -l | awk '{print $5}')
		sum=$((sum+size))
	fi
	done
	echo $F1: $sum
done


