#!/usr/bin/bash

#1. Write a script shell that gets as an input (argumens) 3 directories followed by a list of files.
# The script will copy the files that contain at least 10 lines with more than 5 words in directory 1, 
#and the files that contain at least 10 lines with less than 5 words in directory 2.
# For the files that do not match any criteria, it will move them to directory 3.

DIR1=$1
DIR2=$2
DIR3=$3

shift 3

if [ ! -d $DIR1 ]; then
	echo Invalid directory
	exit 1
fi

if [ ! -d $DIR2 ]; then
        echo Invalid directory
        exit 1
fi
if [ ! -d $DIR3 ]; then
        echo Invalid directory
        exit 1
fi

for file in $@; do
	if [ ! -f $file ]; then
		echo Invalid file
		exit  1
	else
		o5w=0
		lt5w=0
		while read line;do
			words=$(echo $line | awk '{print NF}')
			if [ $words -ge 5 ];then
				o5w=$((o5w+1))
			else
				lt5w=$((lt5w+1))
			fi
		done < $file
		if [ $o5w -ge 10 ];then
			cp $file $DIR1
		elif [ $lt5w -ge 10 ];then
			cp $file $DIR2
		else
			cp $file $DIR3
		fi
	fi
done
