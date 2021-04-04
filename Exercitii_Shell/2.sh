#!/usr/bin/bash

dir=$1
count=0
for file in `find $dir -type f -name "*.c"`
do
	A=`wc -l $file | awk '{print $1}'`
	if [ $A -gt 500 ]
	then
		count=`expr $count + 1`
		echo $file
	fi
	if [ $count -gt 1 ]; then
		exit
	fi
done
