#!/usr/bin/bash

#7. Să se scrie un script bash care are ca argumente triplete formate dintr-un nume de fisier, un cuvant si un numar k. Pentru fiecare astfel de triplet, se vor afişa toate liniile fişierului care contin cuvăntul respectiv exact de k ori.
#(comenzi: shift, awk)

if [ `expr $# % 3` != 0 ];then
	echo Invalid num of args
	exit 1
fi

for  ((i=1;i<=$#/3;i++));do
	if [ -f $1 ];then
		cat $1 | while read line;do
			if [ $(echo $line  | grep -E -o "$2" | wc -l) -eq $3  ];then
				echo $line
			fi
		done
	fi
	shift 3
done
