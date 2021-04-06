#!/usr/bin/bash

#Reads a succesion of directories and moves all files starting with a vowel in a dir named vowel_world

N=$1
shift
if [ $N > $# ];then
	N=$#
fi

if [ ! -d vowel_world ];then
	mkdir vowel_world
fi

for ((i=1;i<=$N;i++));do
	for file in `find $1`;do
		if [ -f $file ];then
			if head -1 $file | grep -E -q "$[aieouAEIOU]";then
				mv $file vowel_world
			fi
		fi
	done
	shift
done

