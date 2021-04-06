#!/usr/bin/bash

#C- caracter primul parametru
#Scriptul va citi cuvinte pana la stop si va afisa pozitia pe care se afla C in cuvant

C=$1
shift

while true
do
	read X
	if [ $X == "stop" ]; then
		exit
	else
		if echo $X | grep -q -E "$C"; then
			echo $X | awk 'END{print index($0,"\"$C\"")}'
		fi
	fi
done
