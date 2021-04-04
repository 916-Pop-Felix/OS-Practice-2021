#!/usr/bin/bash

if [ ! -d $1 ]; then
	echo Invalid directory name
	exit 1
fi


for F in `find $1`
do
	if [ -f $F ]; then
		echo `ls $F -l`
		chmod o-w $F
		echo `ls $F -l`
	fi	
done
