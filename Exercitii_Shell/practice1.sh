#!/usr/bin/bash

if [ ! -d $1 ];then
	echo No existing directory with name $1 found
	exit 1
fi
C=0
F=0
for file in `find $1`;do
	if [ -f $file ];then
		if echo $file | grep -E -q ".c$";then
                        C=$((C+1))
		elif file $file | grep -E -q " C ";then
			F=$((F+1))
		fi
	fi
done

echo $C, $F
