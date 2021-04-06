#!/usr/bin/bash

# Write a shell script that reads N directories and displays files .c or .cpp files ordered by size

S=$1
shift

for dir in $@;do
	if [ -d $dir ];then
		ls -S  $dir | grep -E ".c$|.cpp$"
	fi
done
