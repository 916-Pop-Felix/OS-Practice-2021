#!/usr/bin/bash

if [ ! -f $1 ]; then
	echo Invalid file name
	exit 1
fi

filename=$1
count=0
string=''
while read myline
do
	if [ $count -eq 0 ];then
		string="${string}$myline@scs.ubbcluj.ro"
	else
		string="${string},$myline@scs.ubbcluj.ro"
	fi
	count=$((count+1))
done < $filename

echo $string
