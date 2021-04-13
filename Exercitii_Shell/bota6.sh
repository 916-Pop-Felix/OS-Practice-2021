#!/usr/bin/bash

#9. Să se scrie un script bash care va afişa toate numele de fişiere dintr-un director dat ca parametru şi din subdirectoarele sale, care au numele mai scurte de 8 caractere. Pentru acestea, dacă sunt fişiere text, li se vor a
#fişa primele 10 linii.

if [ $# != 1 ];then
        echo Too many args
        exit 1
fi

if [ ! -d $1 ];then
        echo Arg not a directory
        exit 1
fi

for file in `find -type f`;do #adauga $1 dupa find stiu stiu
	if [ $(echo $file | wc -c) -lt 10 ];then
		echo $file
		if file $file | grep -E -q "ASCII";then
			cat $file | head -10
		fi
	fi
done
