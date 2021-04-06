#!/usr/bin/bash

#4. Să se scrie un script bash care afișează numele fișierelor dintr-un director dat ca parametru care conțin numere de
# peste 5 cifre.

if [ $# -gt 1 ];then
	echo Too many args, srry 
	exit 1
fi

if [ ! -d $1 ];then
	echo $1 is not a valid directory name
	exit 1
fi

for file in `find $1`;do
	if [ -f $file ];then
	if grep -E -q "[0-9]{5,}" $file;then
		echo $file
	fi
	fi
done
