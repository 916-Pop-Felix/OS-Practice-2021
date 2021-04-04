#!/usr/bin/bash

for F in `find -L $1`
do
	if [ ! -e $F ]; then
		echo $F
	fi
done
