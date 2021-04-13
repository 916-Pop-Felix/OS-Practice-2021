#!/usr/bin/bash

#3. Să se scrie un script bash care calculează numărul mediu de linii ale fișierelor de tip text dintr-un director dat ca parametru.
#(comenzi: find, file, wc)

if [ $# != 1 ];then
	echo Too many args
	exit 1
fi

if [ ! -d $1 ];then
	echo Arg not a directory
	exit 1
fi

S=0
C=0
for F in `find -type f`;do
	if file $F | grep -E -q "ASCII";then
		CS=$(wc -l $F | awk '{print $1}')
		S=$((S+CS))
		C=$((C+1))
	fi
done

echo $((S/CS))
